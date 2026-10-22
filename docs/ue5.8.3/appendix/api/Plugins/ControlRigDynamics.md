# Plugins / ControlRigDynamics

- module root: `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics`
- headers: 21; symbols: 1270
- symbol kinds: class=1, delegate=4, enum=5, enumerator=52, function=78, macro=18, member=678, namespace=1, prototype=237, struct=189, typedef=4, variable=3
- PrivateDependencyModuleNames: ControlRig, ControlRigDeveloper, CoreUObject, EditorStyle, Engine, RigVM, RigVMDeveloper, Slate, SlateCore
- PublicDependencyModuleNames: Core, PhysicsControl

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Private/RigDynamicsHelpers.h` (Private)


#### Free symbols / members of external scopes

- L15 _function_ `inline FRigDynamicsParticleComponent* GetParticle(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L21 _function_ `inline const FRigDynamicsParticleComponent* GetParticle(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L28 _function_ `inline const FRigDynamicsParticleComponent* GetParticle( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component
- L38 _function_ `inline FRigDynamicsParticleComponent* GetParticle(URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Mutable variant of the cached lookup. FCachedRigComponent::GetComponent returns a const pointer regardless of hierarchy constness; the const_cast is safe here because the caller holds a non-const URigHierarchy& and the underlying component lives in that hierarchy.
- L45 _function_ `inline FRigDynamicsSolverComponent* GetSolver(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L51 _function_ `inline const FRigDynamicsSolverComponent* GetSolver(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L58 _function_ `inline const FRigDynamicsSolverComponent* GetSolver( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component
- L65 _function_ `inline FRigDynamicsColliderComponent* GetCollider(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L71 _function_ `inline const FRigDynamicsColliderComponent* GetCollider(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L78 _function_ `inline const FRigDynamicsColliderComponent* GetCollider( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component
- L85 _function_ `inline FRigDynamicsConfinerComponent* GetConfiner(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L91 _function_ `inline const FRigDynamicsConfinerComponent* GetConfiner(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L98 _function_ `inline const FRigDynamicsConfinerComponent* GetConfiner( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component
- L105 _function_ `inline FRigDynamicsConstraintComponent* GetConstraint(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L111 _function_ `inline const FRigDynamicsConstraintComponent* GetConstraint(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L118 _function_ `inline const FRigDynamicsConstraintComponent* GetConstraint( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedRigComponent)` — Updates the cache if necessary and then returns the component
- L125 _function_ `inline FRigDynamicsConeLimitComponent* GetConeLimit(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L131 _function_ `inline const FRigDynamicsConeLimitComponent* GetConeLimit(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L138 _function_ `inline const FRigDynamicsConeLimitComponent* GetConeLimit( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedRigComponent)` — Updates the cache if necessary and then returns the component
- L146 _function_ `inline FTransform GetGlobalTransform(const URigHierarchy& Hierarchy, const FRigBaseComponent& Component)` — Gets the transform from the element that owns this component.
- L155 _function_ `inline FVector GetGlobalLocation(const URigHierarchy& Hierarchy, const FRigBaseComponent& Component)` — Gets the location from the element that owns this component.
- L164 _function_ `inline int32 GetElementIndex(const URigHierarchy& Hierarchy, FCachedRigComponent& CachedRigComponent)` — We assume that the cached rig component is fundamentally valid (i.e. exists), but we do ensure it is cached.
- L174 _function_ `inline FTransform GetGlobalTransform(const URigHierarchy& Hierarchy, FCachedRigComponent& CachedRigComponent)`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Private/RigDynamicsObjectVersion.h` (Private)


#### struct `FRigDynamicsObjectVersion`  
`struct FRigDynamicsObjectVersion`  
_L10-57_
- L53 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L56 _private function_ `FRigDynamicsObjectVersion()`

#### enum `FRigDynamicsObjectVersion::Type`  
`enum Type`  
_L12-50_
- L14 _public enumerator_ `FirstVersion`
- L15 _public enumerator_ `ParticleExtraDamping`
- L16 _public enumerator_ `DynamicsTargetMode`
- L17 _public enumerator_ `GravityMultiplier`
- L18 _public enumerator_ `PlaneDefinition`
- L19 _public enumerator_ `PlaneExtents`
- L20 _public enumerator_ `Constraints`
- L21 _public enumerator_ `HelperStructs`
- L22 _public enumerator_ `BonePositionAndOrientationSetting`
- L23 _public enumerator_ `NoCollisionColliders`
- L24 _public enumerator_ `CollisionParticles`
- L25 _public enumerator_ `TargetModeFloat`
- L26 _public enumerator_ `SimulationSpace`
- L27 _public enumerator_ `ConeLimits`
- L28 _public enumerator_ `AngleLimit`
- L29 _public enumerator_ `ResetDetection`
- L30 _public enumerator_ `ParticleValueDisplay`
- L31 _public enumerator_ `ConstraintVisualization`
- L32 _public enumerator_ `AngleLimitVisualization`
- L33 _public enumerator_ `CollideWithColliders`
- L34 _public enumerator_ `ParticleDrag`
- L35 _public enumerator_ `DragSettings`
- L36 _public enumerator_ `Confiners`
- L37 _public enumerator_ `RemoveSolverLevelColliders`
- L38 _public enumerator_ `ConeLimitVisualization`
- L39 _public enumerator_ `TeleportFlags`
- L40 _public enumerator_ `ResetFlags`
- L41 _public enumerator_ `SimulationSpaceRegrouping`
- L42 _public enumerator_ `InertialForcePerTermAmounts`
- L43 _public enumerator_ `SimulationAdditionalDrag`
- L44 _public enumerator_ `EvaluationIntervalReset`
- L45 _public enumerator_ `AccelerationModeAndDamping`
- L48 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-----
- L49 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Private/RigDynamicsSolver.h` (Private)


#### struct `FRigDynamicsSolver`  
`struct FRigDynamicsSolver`  
_L67-288_
- L70 _public prototype_ `FRigDynamicsSolver(const FName InOwnerName);`
- L73 _public prototype_ `void Instantiate( const FRigVMExecuteContext& ExecuteContext, const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent);` — This will initialise/create the simulation and then create everything we need in it.
- L82 _public prototype_ `void StepSimulation( const FRigVMExecuteContext& ExecuteContext, URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, const AActor* OwningActorPtr, const float DeltaTimeOverride, const float SimulationSpaceDeltaTimeOverride, const float Alpha, const bool bTrackVelocitiesDuringPassThrough);` — Integrates the simulation forwards. If DeltaTimeOverride is +ve, then that value is used. If it is zero, then delta time is taken from the execute context If it is negative, then the simulation isn't stepped.
- L93 _public prototype_ `void Draw( FRigVMDrawInterface* DI, const URigHierarchy& Hierarchy, const UWorld* DebugWorld, const FRigDynamicsVisualizationSettings& VisualizationSettings) const;` — Draws shapes etc.
- L101 _public function_ `const FRigDynamicsSimulationSpaceState& GetSimulationSpaceState() const` — Read-only access to the simulation-space state populated by the most recent StepSimulation (or tracking pass-through). Used by inspection nodes.
- L109 _public prototype_ `void AddFieldForcesToParticles( URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, const ERigDynamicsSimulationSpace FieldSpace, const FTransform& FieldTransform, const EPhysicsControlForceType Type, const float RadialForce, const FRichCurve* RadialMultiplier, const FVector& LinearForceDirection, const float LinearForce, const FRichCurve* LinearMultiplier, const FVector& RotationalForceAxis, const float RotationalForce, const FRichCurve* RotationalMultiplier, FRigVMDrawInterface* DrawInterface, const bool bDrawDebug, const float DebugForceScale);` — Adds a per-particle FRigDynamicsParticleForce on every simulated particle that lies inside the given ellipsoidal field, computed from a radial + linear + rotational contribution shaped by the supplied per-radius-fraction curves. The field's transform's translation+rotation gives the ellipsoid centre and orientation. The transform's scale gives the per-axis radii. Particles outside the ellipsoid are not affected. Passing nullptr for any curve makes that contribution a flat 1.0.
- L128 _public function_ `bool WasKinematicSpeedResetInLastStep() const` — True if KinematicSpeedThresholdForReset tripped during the most recent full StepSimulation.
- L131 _public function_ `bool WasPositionResetInLastStep() const` — True if PositionThresholdForReset tripped during the most recent full StepSimulation.
- L136 _public function_ `bool WasEvaluationIntervalResetInLastStep() const` — True if a long interval between solver evaluations was detected during the most recent full StepSimulation (gated by bResetFromEvaluationInterval / EvaluationIntervalThresholdForReset on the solver).
- L140 _private prototype_ `int32 GetParticleIndexSlow(const FRigBaseElement& Element, const URigHierarchy& Hierarchy);` — Returns the index into ComponentInfos/Particles for the given element, or INDEX_NONE
- L143 _private prototype_ `int32 GetParticleIndexSlow(const FRigComponentKey& ComponentKey) const;` — Returns the index into ComponentInfos/Particles for the given element, or INDEX_NONE
- L146 _private prototype_ `int32 GetParentParticleIndexSlow(const FRigBaseElement& Element, const URigHierarchy& Hierarchy);` — Returns the index into ComponentInfos/Particles for the parent of the given element, or INDEX_NONE
- L149 _private prototype_ `int32 GetParentParticleIndexSlow(int32 ParticleIndex, const URigHierarchy& Hierarchy);` — Returns the index into ComponentInfos/Particles for the parent of the given particle, or INDEX_NONE
- L154 _private prototype_ `void UpdatePreDynamics( URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, float DeltaTime);` — This will runs an update prior to the simulation update - e.g. read from the hierarchy target positions etc. Requires DeltaTime > 0. Hierarchy is non-const because the pending forces need to be cleared from the particle components' arrays.
- L160 _private prototype_ `void ClearParticlePendingForces(URigHierarchy& Hierarchy);` — Discards every particle's pending force queue without applying any of it. Called from StepSimulation on paths where UpdatePreDynamics will not run (pass-through frames, or frames with DeltaTime <= 0) so that queued forces do not accumulate into the next simulating frame.
- L163 _private prototype_ `void UpdatePostDynamics(URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, float Alpha);` — This will read back from the simulation into the hierarchy
- L168 _private prototype_ `void TrackParticlePositions(const URigHierarchy& Hierarchy, float DeltaTime);` — Lightweight position tracking for pass-through mode (Alpha <= 0). Snaps particles to their hierarchy targets so that implicit Verlet velocities remain valid for smooth resume. Requires DeltaTime > 0.
- L173 _private prototype_ `void ResetPoseFromAnimation(const URigHierarchy& Hierarchy);` — Snaps all particles to the current animation pose with zero velocity. Used when resuming from a non-tracking pass-through, or after a reset. Assumes the simulation space state has already been reset/updated for coordinate conversion.
- L176 _private prototype_ `void InstantiateColliders( const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, const FRigDynamicsSimulationSpaceState& SpaceState);` — Instantiate helpers, called by Instantiate() in order.
- L183 _private prototype_ `void InstantiateConfiners( const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, const FRigDynamicsSimulationSpaceState& SpaceState);` — Mirrors InstantiateColliders for confiners. Must run before InstantiateParticles so that particles can resolve their Confiners keys into simulation-state indices.
- L188 _private prototype_ `void InstantiateParticles( const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, const FRigDynamicsSimulationSpaceState& SpaceState);`
- L196 _private prototype_ `void ComputeParticleParents(const URigHierarchy& Hierarchy);` — Resolves each particle's parent particle index (walking the hierarchy), sets NumChildren and bParentParticleIsDirectParent on the parent info, and forces root-most particles to kinematic. Runs before SortParticles.
- L201 _private prototype_ `void SortParticles();` — Root-to-leaf BFS sort of particles, with remapping of the solver-owned parallel arrays (ParticleTargetTMs, ParticleOwnerComponents). Constraint / cone-limit / collision indices inside SimulationState are remapped by SortParticlesRootToLeaf itself.
- L205 _private prototype_ `void SetParticlesNoCollision(const URigHierarchy& Hierarchy);` — Post-sort: auto-disables collision between a particle and any collider on the same element or the parent element, and resolves the user-specified particle-to-particle collision pairs.
- L209 _private prototype_ `void InstantiateSkeletalConstraints(const URigHierarchy& Hierarchy);` — Creates one skeletal distance constraint per non-root particle (between the particle and its parent particle). Constraint indices are in post-sort order.
- L212 _private prototype_ `void InstantiateDistanceConstraints( const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent);` — Creates user-defined hard and soft distance constraints from the solver component.
- L216 _private prototype_ `void InstantiateConeLimits( const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent);` — Creates user-defined cone limits from the solver component.
- L220 _private prototype_ `void SortConeLimits();` — Sorts cone limits by child index (root-to-leaf) for better iterative convergence.
- L224 _private prototype_ `bool AnyKinematicExceedsSpeed(float Threshold) const;` — True if any particle with InvMass == 0 has Info.TargetVelocity.Size() > Threshold. Short-circuits on first match. Caller should only invoke when Threshold > 0.
- L228 _private prototype_ `bool AnyParticleExceedsDistanceFromOrigin(float Threshold) const;` — True if any particle's simulation-space distance from the origin exceeds Threshold. Short-circuits on first match. Caller should only invoke when Threshold > 0.
- L235 _private prototype_ `static void UpdateSimulationSpaceStateTransforms( const FRigVMExecuteContext& ExecuteContext, const URigHierarchy& Hierarchy, const FRigDynamicsSolverComponent& SolverComponent, float DeltaTime, FRigDynamicsSimulationSpaceState& OutState, bool bReset = false);` — Computes the component and simulation-space transforms from the solver settings and calls OutState.Update(). When DeltaTime > 0, velocities and accelerations are derived from the position change. When DeltaTime == 0, only the transforms are set. When bReset is true, the state is fully reset (zeroing velocities/accelerations) - used after teleports or when resuming from a pass-through that wasn't tracking.
- L246 _private member_ `FName OwnerName;` — A name that identifies what owns us - just used for debugging/logging
- L250 _private member_ `bool bNeedToInstantiate = true;` — Instantiation can be explicit, or triggered automatically on the StepSimulation call - track whether it is needed.
- L255 _private member_ `bool bNeedToResetPose = false;` — When true, the simulation state will be snapped to the current animation pose with zero velocity on the next step. Cheaper than a full re-instantiation. Set when resuming from a non-tracking pass-through, and will also be used for teleport handling.
- L259 _private member_ `bool bKinematicSpeedResetInLastStep = false;` — Observation flags set by the most recent full StepSimulation, cleared at the start of each. Exposed read-only via the Was*InLastStep accessors and surfaced through the Get-data node.
- L260 _private member_ `bool bPositionResetInLastStep = false;`
- L261 _private member_ `bool bEvaluationIntervalResetInLastStep = false;`
- L267 _private member_ `double LastEvaluationAbsoluteTime = -1.0;` — Absolute time (from the rig's ExecuteContext) at the end of the most recent StepSimulation call. A value < 0 means "no prior evaluation" - the interval test is skipped on the first frame after instantiation. Populated regardless of bResetFromEvaluationInterval so toggling the flag on doesn't have a one-frame priming delay.
- L276 _private member_ `TArray<FTransform> ParticleTargetTMs;` — Each array here here is paired with the relevant one in the simulation state. Infos contain data that refers to control rig, and is used to process inputs. The simulation state data are used by the simulation, and should be packed as tightly as possible. I have tried baking the arrays to pack them into contiguous memory, but it made no measurable improvement. Note that the simulation might have more objects than we have - but the indexing between these and those should still match.
- L277 _private member_ `TArray<FCachedRigComponent> ParticleOwnerComponents;`
- L278 _private member_ `TArray<FCachedRigComponent> HardDistanceConstraintOwnerComponents;`
- L279 _private member_ `TArray<FCachedRigComponent> SoftDistanceConstraintOwnerComponents;`
- L280 _private member_ `TArray<FCachedRigComponent> ColliderOwnerComponents;`
- L281 _private member_ `TArray<FCachedRigComponent> ConfinerOwnerComponents;`
- L282 _private member_ `TArray<FCachedRigComponent> ConeLimitOwnerComponents;`
- L284 _private member_ `RigParticleSimulation::FSimulationState SimulationState;`
- L286 _private member_ `FRigDynamicsSimulationSpaceState SimulationSpaceState;`
- L287 _private member_ `RigParticleSimulation::FSimulationSpaceMotion SimulationSpaceMotion;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigDynamics, Warning, Warning);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigDynamics, Warning, Warning);`
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigDynamics, Log, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigDynamics, Log, All);`
- L32 _prototype_ `bool RigDynamicsShouldVisualize(const FRigDynamicsVisualizationSettings& VisualizationSettings);`
- L38 _prototype_ `bool ShouldDrawForceFieldDebug(bool SettingsValue);`
- L44 _prototype_ `float GetForceFieldDebugScale(float SettingsValue);`
- L51 _prototype_ `void DrawForceFieldEllipsoid( FRigVMDrawInterface* DI, const FTransform& Pose, const FVector& Radii, float Thickness = 0.0f, int32 Detail = 24);`
- L59 _prototype_ `void DrawForceFieldArrow( FRigVMDrawInterface* DI, const FVector& Origin, const FVector& Vector, float Thickness = 0.0f);`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/ControlRigDynamicsModule.h` (Public)


#### class `FControlRigDynamicsModule`  
`class FControlRigDynamicsModule : public IModuleInterface`  
_L15-22_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigDynamics, Warning, Warning);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigDynamics, Warning, Warning);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigDynamics, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigDynamics, Log, All);`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsColliderComponent.h` (Public)


#### struct `FRigDynamicsColliderComponent`  
`struct FRigDynamicsColliderComponent : public FRigBaseComponent`  
_L18-32_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L22 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigDynamicsColliderComponent) UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes, meta = (ShowOnlyInnerProperties)) FRigDynamicsShapeCollection Shapes;`
- L27 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L28 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L30 _public function_ `virtual FName GetDefaultComponentName() const override`
- L31 _public function_ `static FName GetDefaultName()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsColliderExecution.h` (Public)


#### struct `FRigUnit_SpawnDynamicsCollider`  
`struct FRigUnit_SpawnDynamicsCollider : public FRigUnit_DynamicsBaseMutable`  
_L19-48_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Collider", Keywords = "Add,Construction,Create,New,Shape,Collision", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Spawns a new dynamics collider as a component on the owner element. These colliders track the input pose, but do not track the simulated pose - so don't expect good results if you enable collisions between particles and colliders that are attached to bones that are themselves simulated. Note: This node only runs as part of the construction event.
- L23 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L28 _public member_ `FRigElementKey Owner = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L32 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Optional solver - if set (and valid), it will be added to this solver component
- L39 _public member_ `FName ColliderComponentName = FRigDynamicsColliderComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the new collider component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsColliderComponentKey to find the name that was actually assigned.
- L43 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(meta = (Input))` — The collider shapes
- L47 _public member_ `FRigComponentKey DynamicsColliderComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Collider Component Key"))` — The Dynamics Collider component key that was created

#### struct `FRigUnit_GetDynamicsColliderExists`  
`struct FRigUnit_GetDynamicsColliderExists : public FRigUnit_DynamicsBase`  
_L53-68_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Exists", Keywords = "Query,Shape,Collision"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Indicates whether the component exists and is a Dynamics Collider
- L57 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L62 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The component key to check
- L67 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Dynamics Collider

#### struct `FRigUnit_HierarchySetDynamicsColliderShapes`  
`struct FRigUnit_HierarchySetDynamicsColliderShapes : public FRigUnit_DynamicsBaseMutable`  
_L75-90_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Shapes", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Replaces the entire shape collection on a Dynamics collider. Construction-event only because the solver's parallel arrays are sized at Instantiate time and cannot grow or shrink at runtime; for editing existing shapes during simulation use the per-shape Set nodes (by Name) instead.
- L79 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L84 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L89 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(meta = (Input))` — The new shape collection (replaces the existing one wholesale)

#### struct `FRigUnit_HierarchyGetDynamicsColliderShapes`  
`struct FRigUnit_HierarchyGetDynamicsColliderShapes : public FRigUnit_DynamicsBase`  
_L95-110_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Shapes", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Reads the entire shape collection from a Dynamics collider.
- L99 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L104 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L109 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(meta = (Output))` — The collider's shape collection. If the component is missing the output is left empty.

#### struct `FRigUnit_HierarchySetDynamicsColliderBox`  
`struct FRigUnit_HierarchySetDynamicsColliderBox : public FRigUnit_DynamicsBaseMutable`  
_L115-130_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Box", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the properties of a named box shape on a Dynamics collider. Name is used to find the shape.
- L119 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L124 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L129 _public member_ `FRigDynamicsShapeBox Box;` — `UPROPERTY(meta = (Input))` — The box shape data (Name is used to find the shape to update)

#### struct `FRigUnit_HierarchyGetDynamicsColliderBox`  
`struct FRigUnit_HierarchyGetDynamicsColliderBox : public FRigUnit_DynamicsBase`  
_L135-154_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Box", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the properties of a named box shape on a Dynamics collider. The shape is looked up by Name.
- L139 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L144 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L149 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to query
- L153 _public member_ `FRigDynamicsShapeBox Box;` — `UPROPERTY(meta = (Output))` — The box shape data. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderCapsule`  
`struct FRigUnit_HierarchySetDynamicsColliderCapsule : public FRigUnit_DynamicsBaseMutable`  
_L159-174_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Capsule", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the properties of a named capsule shape on a Dynamics collider. Name is used to find the shape.
- L163 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L168 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L173 _public member_ `FRigDynamicsShapeCapsule Capsule;` — `UPROPERTY(meta = (Input))` — The capsule shape data (Name is used to find the shape to update)

#### struct `FRigUnit_HierarchyGetDynamicsColliderCapsule`  
`struct FRigUnit_HierarchyGetDynamicsColliderCapsule : public FRigUnit_DynamicsBase`  
_L179-198_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Capsule", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the properties of a named capsule shape on a Dynamics collider. The shape is looked up by Name.
- L183 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L188 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L193 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L197 _public member_ `FRigDynamicsShapeCapsule Capsule;` — `UPROPERTY(meta = (Output))` — The capsule shape data. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderPlane`  
`struct FRigUnit_HierarchySetDynamicsColliderPlane : public FRigUnit_DynamicsBaseMutable`  
_L203-218_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Plane", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the properties of a named plane shape on a Dynamics collider. Name is used to find the shape.
- L207 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L212 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L217 _public member_ `FRigDynamicsShapePlane Plane;` — `UPROPERTY(meta = (Input))` — The plane shape data (Name is used to find the shape to update)

#### struct `FRigUnit_HierarchyGetDynamicsColliderPlane`  
`struct FRigUnit_HierarchyGetDynamicsColliderPlane : public FRigUnit_DynamicsBase`  
_L223-242_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Plane", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the properties of a named plane shape on a Dynamics collider. The shape is looked up by Name.
- L227 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L232 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L237 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to query
- L241 _public member_ `FRigDynamicsShapePlane Plane;` — `UPROPERTY(meta = (Output))` — The plane shape data. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderBoxTM`  
`struct FRigUnit_HierarchySetDynamicsColliderBoxTM : public FRigUnit_DynamicsBaseMutable`  
_L247-266_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Box TM", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the transform of a named box shape on a Dynamics collider
- L251 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L256 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L261 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to update
- L265 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Input))` — Position and orientation (scale is ignored)

#### struct `FRigUnit_HierarchyGetDynamicsColliderBoxTM`  
`struct FRigUnit_HierarchyGetDynamicsColliderBoxTM : public FRigUnit_DynamicsBase`  
_L271-291_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Box TM", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the transform of a named box shape on a Dynamics collider
- L275 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L280 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L285 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to query
- L290 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Output))` — Position and orientation (scale is ignored). If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderBoxExtents`  
`struct FRigUnit_HierarchySetDynamicsColliderBoxExtents : public FRigUnit_DynamicsBaseMutable`  
_L296-315_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Box Extents", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extents of a named box shape on a Dynamics collider
- L300 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L305 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L310 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to update
- L314 _public member_ `FVector Extents = FVector::OneVector * RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Input))` — Full extents of the box in each axis

#### struct `FRigUnit_HierarchyGetDynamicsColliderBoxExtents`  
`struct FRigUnit_HierarchyGetDynamicsColliderBoxExtents : public FRigUnit_DynamicsBase`  
_L320-340_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Box Extents", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extents of a named box shape on a Dynamics collider
- L324 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L329 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L334 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to query
- L339 _public member_ `FVector Extents = FVector::OneVector * RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Output))` — Full extents of the box in each axis. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderCapsuleTM`  
`struct FRigUnit_HierarchySetDynamicsColliderCapsuleTM : public FRigUnit_DynamicsBaseMutable`  
_L345-364_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Capsule TM", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the transform of a named capsule shape on a Dynamics collider
- L349 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L354 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L359 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to update
- L363 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Input))` — Position and orientation (scale is ignored), main axis along +Z

#### struct `FRigUnit_HierarchyGetDynamicsColliderCapsuleTM`  
`struct FRigUnit_HierarchyGetDynamicsColliderCapsuleTM : public FRigUnit_DynamicsBase`  
_L369-389_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Capsule TM", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the transform of a named capsule shape on a Dynamics collider
- L373 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L378 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L383 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L388 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Output))` — Position and orientation (scale is ignored), main axis along +Z. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderCapsuleRadius`  
`struct FRigUnit_HierarchySetDynamicsColliderCapsuleRadius : public FRigUnit_DynamicsBaseMutable`  
_L394-413_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Capsule Radius", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the radius of a named capsule shape on a Dynamics collider
- L398 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L403 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L408 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to update
- L412 _public member_ `float Radius = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Centimeters"))` — Capsule radius

#### struct `FRigUnit_HierarchyGetDynamicsColliderCapsuleRadius`  
`struct FRigUnit_HierarchyGetDynamicsColliderCapsuleRadius : public FRigUnit_DynamicsBase`  
_L418-437_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Capsule Radius", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the radius of a named capsule shape on a Dynamics collider
- L422 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L427 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L432 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L436 _public member_ `float Radius = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Output, Units = "Centimeters"))` — Capsule radius. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderCapsuleLength`  
`struct FRigUnit_HierarchySetDynamicsColliderCapsuleLength : public FRigUnit_DynamicsBaseMutable`  
_L442-461_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Capsule Length", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the length of a named capsule shape on a Dynamics collider
- L446 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L451 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L456 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to update
- L460 _public member_ `float Length = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Centimeters"))` — Core length of the capsule (total length is Length + 2 * Radius)

#### struct `FRigUnit_HierarchyGetDynamicsColliderCapsuleLength`  
`struct FRigUnit_HierarchyGetDynamicsColliderCapsuleLength : public FRigUnit_DynamicsBase`  
_L466-486_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Capsule Length", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the length of a named capsule shape on a Dynamics collider
- L470 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L475 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L480 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L485 _public member_ `float Length = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Output, Units = "Centimeters"))` — Core length of the capsule (total length is Length + 2 * Radius). If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderPlaneTM`  
`struct FRigUnit_HierarchySetDynamicsColliderPlaneTM : public FRigUnit_DynamicsBaseMutable`  
_L491-510_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Plane TM", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the transform of a named plane shape on a Dynamics collider
- L495 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L500 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L505 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to update
- L509 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Input))` — Position defines a point on the plane, plane faces +Z

#### struct `FRigUnit_HierarchyGetDynamicsColliderPlaneTM`  
`struct FRigUnit_HierarchyGetDynamicsColliderPlaneTM : public FRigUnit_DynamicsBase`  
_L515-535_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Plane TM", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the transform of a named plane shape on a Dynamics collider
- L519 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L524 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L529 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to query
- L534 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Output))` — Position defines a point on the plane, plane faces +Z. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsColliderPlaneExtents`  
`struct FRigUnit_HierarchySetDynamicsColliderPlaneExtents : public FRigUnit_DynamicsBaseMutable`  
_L540-559_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Collider Plane Extents", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extents of a named plane shape on a Dynamics collider
- L544 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L549 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to be updated
- L554 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to update
- L558 _public member_ `FVector2D Extents = FVector2D(RigDynamicsDefaultShapeSize * 10.0f);` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — Extents of the plane

#### struct `FRigUnit_HierarchyGetDynamicsColliderPlaneExtents`  
`struct FRigUnit_HierarchyGetDynamicsColliderPlaneExtents : public FRigUnit_DynamicsBase`  
_L564-583_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Collider Plane Extents", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extents of a named plane shape on a Dynamics collider
- L568 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L573 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Dynamics Collider to query
- L578 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to query
- L582 _public member_ `FVector2D Extents = FVector2D(RigDynamicsDefaultShapeSize * 10.0f);` — `UPROPERTY(meta = (Output))` — Extents of the plane. If no matching shape is found, the output is left at its default.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsConeLimitComponent.h` (Public)


#### struct `FRigDynamicsConeLimitComponent`  
`struct FRigDynamicsConeLimitComponent : public FRigBaseComponent`  
_L17-60_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L21 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigDynamicsConeLimitComponent)`
- L30 _public member_ `FRigComponentKey ParentComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ConeLimit)` — The parent particle for the ConeLimit
- L35 _public member_ `FRigComponentKey ChildComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ConeLimit)` — The child particle for the ConeLimit
- L42 _public member_ `float Strength = 10.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", Units = "Hertz"))` — The strength which we drive towards the target limit (when outside). This is the oscillation frequency, so low values will be soft and springy, but values significantly above 1/timestep will impose the limit strongly.
- L46 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0"))` — DampingRatio for the ConeLimit
- L50 _public member_ `float Angle = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", Units = "Degrees"))` — The (full) cone angle in degrees
- L52 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L53 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L55 _public function_ `virtual FName GetDefaultComponentName() const override`
- L56 _public function_ `static FName GetDefaultName()`
- L59 _protected prototype_ `void Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsConeLimitExecution.h` (Public)


#### struct `FRigUnit_SpawnDynamicsConeLimit`  
`struct FRigUnit_SpawnDynamicsConeLimit : public FRigUnit_DynamicsBaseMutable`  
_L21-75_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Cone Limit", Keywords = "Add,Construction,Create,Angle,Angular", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- L25 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L30 _public member_ `FRigElementKey Owner = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L34 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Optional solver - if set, it will be added to this solver component
- L41 _public member_ `FName ConeLimitComponentName = FRigDynamicsConeLimitComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the new cone limit component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsConeLimitComponentKey to find the name that was actually assigned.
- L45 _public member_ `FRigComponentKey GrandparentComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The grandparent particle for the cone limit
- L50 _public member_ `FRigComponentKey ParentComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The parent particle for the cone limit
- L55 _public member_ `FRigComponentKey ChildComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The child particle for the cone limit
- L62 _public member_ `float Strength = 10.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — The strength which we drive towards the target limit (when outside). This is the oscillation frequency, so low values will be soft and springy, but values significantly above 1/timestep will impose the limit strongly.
- L66 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — DampingRatio for the cone limit
- L70 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Degrees"))` — The (full) cone angle in degrees
- L74 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit component key that was created

#### struct `FRigUnit_GetDynamicsConeLimitExists`  
`struct FRigUnit_GetDynamicsConeLimitExists : public FRigUnit_DynamicsBase`  
_L80-95_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Cone Limit Exists", Keywords = "Query,Angle,Angular"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Indicates whether the component exists and is a Dynamics Cone Limit
- L84 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L89 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The component key to check
- L94 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Dynamics Cone Limit

#### struct `FRigUnit_HierarchySetDynamicsConeLimitStrength`  
`struct FRigUnit_HierarchySetDynamicsConeLimitStrength : public FRigUnit_DynamicsBaseMutable`  
_L100-115_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Cone Limit Strength", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the strength of a Dynamics cone limit
- L104 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L109 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit to be updated
- L114 _public member_ `float Strength = 10.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — The strength which enforces the limit (oscillation frequency)

#### struct `FRigUnit_HierarchyGetDynamicsConeLimitStrength`  
`struct FRigUnit_HierarchyGetDynamicsConeLimitStrength : public FRigUnit_DynamicsBase`  
_L120-135_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Cone Limit Strength", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the strength of a Dynamics cone limit
- L124 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L129 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit to query
- L134 _public member_ `float Strength = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — The strength which enforces the limit (oscillation frequency)

#### struct `FRigUnit_HierarchySetDynamicsConeLimitDampingRatio`  
`struct FRigUnit_HierarchySetDynamicsConeLimitDampingRatio : public FRigUnit_DynamicsBaseMutable`  
_L140-155_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Cone Limit Damping Ratio", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the damping ratio of a Dynamics cone limit
- L144 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L149 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit to be updated
- L154 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — Damping ratio for the cone limit

#### struct `FRigUnit_HierarchyGetDynamicsConeLimitDampingRatio`  
`struct FRigUnit_HierarchyGetDynamicsConeLimitDampingRatio : public FRigUnit_DynamicsBase`  
_L160-175_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Cone Limit Damping Ratio", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the damping ratio of a Dynamics cone limit
- L164 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L169 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit to query
- L174 _public member_ `float DampingRatio = 0.0f;` — `UPROPERTY(meta = (Output))` — Damping ratio for the cone limit

#### struct `FRigUnit_HierarchySetDynamicsConeLimitAngle`  
`struct FRigUnit_HierarchySetDynamicsConeLimitAngle : public FRigUnit_DynamicsBaseMutable`  
_L180-195_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Cone Limit Angle", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the angle of a Dynamics cone limit
- L184 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L189 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit to be updated
- L194 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Degrees"))` — The (full) cone angle in degrees

#### struct `FRigUnit_HierarchyGetDynamicsConeLimitAngle`  
`struct FRigUnit_HierarchyGetDynamicsConeLimitAngle : public FRigUnit_DynamicsBase`  
_L200-215_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Cone Limit Angle", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the angle of a Dynamics cone limit
- L204 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L209 _public member_ `FRigComponentKey DynamicsConeLimitComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConeLimitComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Cone Limit Component Key"))` — The Dynamics Cone Limit to query
- L214 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Degrees"))` — The (full) cone angle in degrees

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsConfinerComponent.h` (Public)


#### struct `FRigDynamicsConfinerComponent`  
`struct FRigDynamicsConfinerComponent : public FRigBaseComponent`  
_L19-38_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L23 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigDynamicsConfinerComponent) UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes, meta = (ShowOnlyInnerProperties)) FRigDynamicsShapeCollection Shapes;`
- L31 _public member_ `float Strength = 2.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", Units = "Hertz"))` — The strength with which particles are pushed back inside the confiner shapes (oscillation frequency). High values confine rigidly, low values allow soft/springy escape before settling.
- L33 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L34 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L36 _public function_ `virtual FName GetDefaultComponentName() const override`
- L37 _public function_ `static FName GetDefaultName()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsConfinerExecution.h` (Public)


#### struct `FRigUnit_SpawnDynamicsConfiner`  
`struct FRigUnit_SpawnDynamicsConfiner : public FRigUnit_DynamicsBaseMutable`  
_L20-59_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Confiner", Keywords = "Add,Construction,Create,New,Shape,Confinement,Enclosure", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Spawns a new dynamics confiner as a component on the owner element. Confiners keep opted-in particles inside each of their shapes (intersection semantics). The confiner tracks the input pose, but does not track the simulated pose. Note: This node only runs as part of the construction event.
- L24 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L29 _public member_ `FRigElementKey Owner = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L33 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Optional solver - if set (and valid), it will be added to this solver component
- L40 _public member_ `FName ConfinerComponentName = FRigDynamicsConfinerComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the confiner component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsConfinerComponentKey to find the name that was actually assigned.
- L44 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(meta = (Input))` — The confiner shapes
- L48 _public member_ `float Strength = 2.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — Soft strength (oscillation frequency in Hz) with which particles are pushed back inside
- L54 _public member_ `TArray<FRigComponentKey> ConfinedParticles;` — `UPROPERTY(meta = (Input))` — Particles that should be confined by this confiner. Each listed particle has the new confiner key appended to its Confiners opt-in list, so no separate Enable call is needed. Missing/invalid keys warn and are skipped. Leave empty to wire particles up later.
- L58 _public member_ `FRigComponentKey DynamicsConfinerComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner component key that was created

#### struct `FRigUnit_GetDynamicsConfinerExists`  
`struct FRigUnit_GetDynamicsConfinerExists : public FRigUnit_DynamicsBase`  
_L64-79_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Exists", Keywords = "Query,Shape,Confinement,Enclosure"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Indicates whether the component exists and is a Dynamics Confiner
- L68 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L73 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The component key to check
- L78 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Dynamics Confiner

#### struct `FRigUnit_HierarchySetDynamicsConfinerShapes`  
`struct FRigUnit_HierarchySetDynamicsConfinerShapes : public FRigUnit_DynamicsBaseMutable`  
_L86-101_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Shapes", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Replaces the entire shape collection on a Dynamics confiner. Construction-event only because the solver's parallel arrays are sized at Instantiate time and cannot grow or shrink at runtime; for editing existing shapes during simulation use the per-shape Set nodes (by Name) instead.
- L90 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L95 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L100 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(meta = (Input))` — The new shape collection (replaces the existing one wholesale)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerShapes`  
`struct FRigUnit_HierarchyGetDynamicsConfinerShapes : public FRigUnit_DynamicsBase`  
_L106-121_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Shapes", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Reads the entire shape collection from a Dynamics confiner.
- L110 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L115 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L120 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(meta = (Output))` — The confiner's shape collection. If the component is missing the output is left empty.

#### struct `FRigUnit_HierarchySetDynamicsConfinerBox`  
`struct FRigUnit_HierarchySetDynamicsConfinerBox : public FRigUnit_DynamicsBaseMutable`  
_L126-141_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Box", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the properties of a named box shape on a Dynamics confiner. Name is used to find the shape.
- L130 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L135 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L140 _public member_ `FRigDynamicsShapeBox Box;` — `UPROPERTY(meta = (Input))` — The box shape data (Name is used to find the shape to update)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerBox`  
`struct FRigUnit_HierarchyGetDynamicsConfinerBox : public FRigUnit_DynamicsBase`  
_L146-165_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Box", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the properties of a named box shape on a Dynamics confiner. The shape is looked up by Name.
- L150 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L155 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L160 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to query
- L164 _public member_ `FRigDynamicsShapeBox Box;` — `UPROPERTY(meta = (Output))` — The box shape data. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerCapsule`  
`struct FRigUnit_HierarchySetDynamicsConfinerCapsule : public FRigUnit_DynamicsBaseMutable`  
_L170-185_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Capsule", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the properties of a named capsule shape on a Dynamics confiner. Name is used to find the shape.
- L174 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L179 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L184 _public member_ `FRigDynamicsShapeCapsule Capsule;` — `UPROPERTY(meta = (Input))` — The capsule shape data (Name is used to find the shape to update)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerCapsule`  
`struct FRigUnit_HierarchyGetDynamicsConfinerCapsule : public FRigUnit_DynamicsBase`  
_L190-209_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Capsule", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the properties of a named capsule shape on a Dynamics confiner. The shape is looked up by Name.
- L194 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L199 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L204 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L208 _public member_ `FRigDynamicsShapeCapsule Capsule;` — `UPROPERTY(meta = (Output))` — The capsule shape data. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerPlane`  
`struct FRigUnit_HierarchySetDynamicsConfinerPlane : public FRigUnit_DynamicsBaseMutable`  
_L214-229_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Plane", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the properties of a named plane shape on a Dynamics confiner. Name is used to find the shape.
- L218 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L223 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L228 _public member_ `FRigDynamicsShapePlane Plane;` — `UPROPERTY(meta = (Input))` — The plane shape data (Name is used to find the shape to update)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerPlane`  
`struct FRigUnit_HierarchyGetDynamicsConfinerPlane : public FRigUnit_DynamicsBase`  
_L234-253_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Plane", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the properties of a named plane shape on a Dynamics confiner. The shape is looked up by Name.
- L238 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L243 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L248 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to query
- L252 _public member_ `FRigDynamicsShapePlane Plane;` — `UPROPERTY(meta = (Output))` — The plane shape data. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerBoxTM`  
`struct FRigUnit_HierarchySetDynamicsConfinerBoxTM : public FRigUnit_DynamicsBaseMutable`  
_L258-277_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Box TM", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the transform of a named box shape on a Dynamics confiner
- L262 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L267 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L272 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to update
- L276 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Input))` — Position and orientation (scale is ignored)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerBoxTM`  
`struct FRigUnit_HierarchyGetDynamicsConfinerBoxTM : public FRigUnit_DynamicsBase`  
_L282-302_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Box TM", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the transform of a named box shape on a Dynamics confiner
- L286 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L291 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L296 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to query
- L301 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Output))` — Position and orientation (scale is ignored). If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerBoxExtents`  
`struct FRigUnit_HierarchySetDynamicsConfinerBoxExtents : public FRigUnit_DynamicsBaseMutable`  
_L307-326_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Box Extents", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extents of a named box shape on a Dynamics confiner
- L311 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L316 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L321 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to update
- L325 _public member_ `FVector Extents = FVector::OneVector * RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Input))` — Full extents of the box in each axis

#### struct `FRigUnit_HierarchyGetDynamicsConfinerBoxExtents`  
`struct FRigUnit_HierarchyGetDynamicsConfinerBoxExtents : public FRigUnit_DynamicsBase`  
_L331-351_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Box Extents", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extents of a named box shape on a Dynamics confiner
- L335 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L340 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L345 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the box shape to query
- L350 _public member_ `FVector Extents = FVector::OneVector * RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Output))` — Full extents of the box in each axis. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerCapsuleTM`  
`struct FRigUnit_HierarchySetDynamicsConfinerCapsuleTM : public FRigUnit_DynamicsBaseMutable`  
_L356-375_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Capsule TM", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the transform of a named capsule shape on a Dynamics confiner
- L360 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L365 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L370 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to update
- L374 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Input))` — Position and orientation (scale is ignored), main axis along +Z

#### struct `FRigUnit_HierarchyGetDynamicsConfinerCapsuleTM`  
`struct FRigUnit_HierarchyGetDynamicsConfinerCapsuleTM : public FRigUnit_DynamicsBase`  
_L380-400_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Capsule TM", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the transform of a named capsule shape on a Dynamics confiner
- L384 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L389 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L394 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L399 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Output))` — Position and orientation (scale is ignored), main axis along +Z. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerCapsuleRadius`  
`struct FRigUnit_HierarchySetDynamicsConfinerCapsuleRadius : public FRigUnit_DynamicsBaseMutable`  
_L405-424_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Capsule Radius", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the radius of a named capsule shape on a Dynamics confiner
- L409 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L414 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L419 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to update
- L423 _public member_ `float Radius = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Centimeters"))` — Capsule radius

#### struct `FRigUnit_HierarchyGetDynamicsConfinerCapsuleRadius`  
`struct FRigUnit_HierarchyGetDynamicsConfinerCapsuleRadius : public FRigUnit_DynamicsBase`  
_L429-448_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Capsule Radius", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the radius of a named capsule shape on a Dynamics confiner
- L433 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L438 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L443 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L447 _public member_ `float Radius = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Output, Units = "Centimeters"))` — Capsule radius. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerCapsuleLength`  
`struct FRigUnit_HierarchySetDynamicsConfinerCapsuleLength : public FRigUnit_DynamicsBaseMutable`  
_L453-472_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Capsule Length", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the length of a named capsule shape on a Dynamics confiner
- L457 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L462 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L467 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to update
- L471 _public member_ `float Length = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Centimeters"))` — Core length of the capsule (total length is Length + 2 * Radius)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerCapsuleLength`  
`struct FRigUnit_HierarchyGetDynamicsConfinerCapsuleLength : public FRigUnit_DynamicsBase`  
_L477-497_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Capsule Length", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the length of a named capsule shape on a Dynamics confiner
- L481 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L486 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L491 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the capsule shape to query
- L496 _public member_ `float Length = RigDynamicsDefaultShapeSize;` — `UPROPERTY(meta = (Output, Units = "Centimeters"))` — Core length of the capsule (total length is Length + 2 * Radius). If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerPlaneTM`  
`struct FRigUnit_HierarchySetDynamicsConfinerPlaneTM : public FRigUnit_DynamicsBaseMutable`  
_L503-522_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Plane TM", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the transform of a named plane shape on a Dynamics confiner. Extents are used for visualization only - the confiner treats each plane as an infinite +Z half-space.
- L507 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L512 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L517 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to update
- L521 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Input))` — Position defines a point on the plane, plane faces +Z

#### struct `FRigUnit_HierarchyGetDynamicsConfinerPlaneTM`  
`struct FRigUnit_HierarchyGetDynamicsConfinerPlaneTM : public FRigUnit_DynamicsBase`  
_L527-547_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Plane TM", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the transform of a named plane shape on a Dynamics confiner
- L531 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L536 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L541 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to query
- L546 _public member_ `FTransform TM;` — `UPROPERTY(meta = (Output))` — Position defines a point on the plane, plane faces +Z. If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerPlaneExtents`  
`struct FRigUnit_HierarchySetDynamicsConfinerPlaneExtents : public FRigUnit_DynamicsBaseMutable`  
_L552-571_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Plane Extents", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extents of a named plane shape on a Dynamics confiner (visualization only)
- L556 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L561 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L566 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to update
- L570 _public member_ `FVector2D Extents = FVector2D(RigDynamicsDefaultShapeSize * 10.0f);` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — Plane extents (used for visualization only; the confiner treats the plane as infinite)

#### struct `FRigUnit_HierarchyGetDynamicsConfinerPlaneExtents`  
`struct FRigUnit_HierarchyGetDynamicsConfinerPlaneExtents : public FRigUnit_DynamicsBase`  
_L576-596_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Plane Extents", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extents of a named plane shape on a Dynamics confiner (visualization only)
- L580 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L585 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L590 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the plane shape to query
- L595 _public member_ `FVector2D Extents = FVector2D(RigDynamicsDefaultShapeSize * 10.0f);` — `UPROPERTY(meta = (Output))` — Plane extents (used for visualization only; the confiner treats the plane as infinite). If no matching shape is found, the output is left at its default.

#### struct `FRigUnit_HierarchySetDynamicsConfinerStrength`  
`struct FRigUnit_HierarchySetDynamicsConfinerStrength : public FRigUnit_DynamicsBaseMutable`  
_L601-616_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Confiner Strength", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the strength (oscillation frequency) of a Dynamics confiner
- L605 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L610 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to be updated
- L615 _public member_ `float Strength = 2.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — Confinement strength (oscillation frequency in Hz). Zero disables the confiner.

#### struct `FRigUnit_HierarchyGetDynamicsConfinerStrength`  
`struct FRigUnit_HierarchyGetDynamicsConfinerStrength : public FRigUnit_DynamicsBase`  
_L621-636_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Confiner Strength", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the strength (oscillation frequency) of a Dynamics confiner
- L625 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L630 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Dynamics Confiner to query
- L635 _public member_ `float Strength = 2.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — Confinement strength (oscillation frequency in Hz). Zero disables the confiner.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsConstraintComponent.h` (Public)


#### struct `FRigDynamicsConstraintComponent`  
`struct FRigDynamicsConstraintComponent : public FRigBaseComponent`  
_L17-74_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L21 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigDynamicsConstraintComponent)`
- L30 _public member_ `FRigComponentKey ChildComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Constraint)` — The child particle for the constraint
- L36 _public member_ `ERigParticleSimulationConstraintType ConstraintType = ERigParticleSimulationConstraintType::Hard;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Constraint)` — If the constraint is marked as "hard", then the system will try as hard as possible to enforce it. This will also be a little cheaper than making a soft constraint.
- L42 _public member_ `float Strength = 2.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard", Units = "Hertz"))` — The strength which we drive towards the target length. This is the oscillation frequency, so low values will be soft and springy, but values significantly above 1/timestep will track the target very accurately.
- L46 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard"))` — DampingRatio for the constraint
- L50 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard", Units = "Hertz"))` — Additional damping for the constraint
- L56 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard"))` — For soft constraints: When true, Strength is a mass-independent natural frequency. When false, the spring/damper acts as a true force, so heavier particles oscillate more slowly. For hard constraints, this has no effect.
- L60 _public member_ `float LengthMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0"))` — The target length will be calculated automatically, multiplied by this
- L64 _public member_ `float ExtraLength = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (Units = "Centimeters"))` — This will be added on to the target length after the automatic/multiplication
- L66 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L67 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L69 _public function_ `virtual FName GetDefaultComponentName() const override`
- L70 _public function_ `static FName GetDefaultName()`
- L73 _protected prototype_ `void Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsConstraintExecution.h` (Public)


#### struct `FRigUnit_SpawnDynamicsConstraint`  
`struct FRigUnit_SpawnDynamicsConstraint : public FRigUnit_DynamicsBaseMutable`  
_L21-89_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Constraint", Keywords = "Add,Construction,Create,New,Rod,Distance", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- L25 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L30 _public member_ `FRigElementKey Owner = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L34 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Optional solver - if set, it will be added to this solver component
- L41 _public member_ `FName ConstraintComponentName = FRigDynamicsConstraintComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the new constraint component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsConstraintComponentKey to find the name that was actually assigned.
- L45 _public member_ `FRigComponentKey ParentComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The parent particle for the constraint
- L50 _public member_ `FRigComponentKey ChildComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The child particle for the constraint
- L56 _public member_ `ERigParticleSimulationConstraintType ConstraintType = ERigParticleSimulationConstraintType::Hard;` — `UPROPERTY(meta = (Input))` — If the constraint is marked as "hard", then the system will try as hard as possible to enforce it. This will also be a little cheaper than making a soft constraint.
- L62 _public member_ `float Strength = 2.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard", Units = "Hertz"))` — The strength which we drive towards the target length. This is the oscillation frequency, so low values will be soft and springy, but values significantly above 1/timestep will track the target very accurately.
- L66 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard"))` — DampingRatio for the constraint
- L70 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard", Units = "Hertz"))` — Additional damping for the constraint
- L76 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(meta = (Input, EditCondition = "ConstraintType != ERigParticleSimulationConstraintType::Hard"))` — For soft constraints: When true, Strength is a mass-independent natural frequency. When false, the spring/damper acts as a true force, so heavier particles oscillate more slowly. For hard constraints, this has no effect.
- L80 _public member_ `float LengthMultiplier = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The target length will be calculated automatically, multiplied by this
- L84 _public member_ `float ExtraLength = 0.0f;` — `UPROPERTY(meta = (Input))` — This will be added on to the target length after the automatic/multiplication
- L88 _public member_ `FRigComponentKey DynamicsConstraintComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint component key that was created

#### struct `FRigUnit_GetDynamicsConstraintExists`  
`struct FRigUnit_GetDynamicsConstraintExists : public FRigUnit_DynamicsBase`  
_L94-109_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Exists", Keywords = "Query,Rod,Distance"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Indicates whether the component exists and is a Dynamics Constraint
- L98 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L103 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The component key to check
- L108 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Dynamics Constraint

#### struct `FRigUnit_HierarchySetDynamicsConstraintStrength`  
`struct FRigUnit_HierarchySetDynamicsConstraintStrength : public FRigUnit_DynamicsBaseMutable`  
_L114-129_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Constraint Strength", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the strength of a Dynamics constraint
- L118 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L123 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to be updated
- L128 _public member_ `float Strength = 2.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — The strength which drives towards the target length (oscillation frequency)

#### struct `FRigUnit_HierarchyGetDynamicsConstraintStrength`  
`struct FRigUnit_HierarchyGetDynamicsConstraintStrength : public FRigUnit_DynamicsBase`  
_L134-149_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Strength", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the strength of a Dynamics constraint
- L138 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L143 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to query
- L148 _public member_ `float Strength = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — The strength which drives towards the target length (oscillation frequency)

#### struct `FRigUnit_HierarchySetDynamicsConstraintDampingRatio`  
`struct FRigUnit_HierarchySetDynamicsConstraintDampingRatio : public FRigUnit_DynamicsBaseMutable`  
_L154-169_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Constraint Damping Ratio", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the damping ratio of a Dynamics constraint
- L158 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L163 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to be updated
- L168 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — Damping ratio for the constraint

#### struct `FRigUnit_HierarchyGetDynamicsConstraintDampingRatio`  
`struct FRigUnit_HierarchyGetDynamicsConstraintDampingRatio : public FRigUnit_DynamicsBase`  
_L174-189_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Damping Ratio", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the damping ratio of a Dynamics constraint
- L178 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L183 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to query
- L188 _public member_ `float DampingRatio = 0.0f;` — `UPROPERTY(meta = (Output))` — Damping ratio for the constraint

#### struct `FRigUnit_HierarchySetDynamicsConstraintExtraDamping`  
`struct FRigUnit_HierarchySetDynamicsConstraintExtraDamping : public FRigUnit_DynamicsBaseMutable`  
_L194-209_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Constraint Extra Damping", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extra damping of a Dynamics constraint
- L198 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L203 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to be updated
- L208 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — Additional damping for the constraint

#### struct `FRigUnit_HierarchyGetDynamicsConstraintExtraDamping`  
`struct FRigUnit_HierarchyGetDynamicsConstraintExtraDamping : public FRigUnit_DynamicsBase`  
_L214-229_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Extra Damping", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extra damping of a Dynamics constraint
- L218 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L223 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to query
- L228 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — Additional damping for the constraint

#### struct `FRigUnit_HierarchySetDynamicsConstraintLengthMultiplier`  
`struct FRigUnit_HierarchySetDynamicsConstraintLengthMultiplier : public FRigUnit_DynamicsBaseMutable`  
_L234-249_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Constraint Length Multiplier", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the length multiplier of a Dynamics constraint
- L238 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L243 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to be updated
- L248 _public member_ `float LengthMultiplier = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The target length will be calculated automatically, multiplied by this

#### struct `FRigUnit_HierarchyGetDynamicsConstraintLengthMultiplier`  
`struct FRigUnit_HierarchyGetDynamicsConstraintLengthMultiplier : public FRigUnit_DynamicsBase`  
_L254-269_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Length Multiplier", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the length multiplier of a Dynamics constraint
- L258 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L263 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to query
- L268 _public member_ `float LengthMultiplier = 0.0f;` — `UPROPERTY(meta = (Output))` — The target length will be calculated automatically, multiplied by this

#### struct `FRigUnit_HierarchySetDynamicsConstraintExtraLength`  
`struct FRigUnit_HierarchySetDynamicsConstraintExtraLength : public FRigUnit_DynamicsBaseMutable`  
_L274-289_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Constraint Extra Length", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extra length of a Dynamics constraint
- L278 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L283 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to be updated
- L288 _public member_ `float ExtraLength = 0.0f;` — `UPROPERTY(meta = (Input, Units = "Centimeters"))` — Added on to the target length after the automatic/multiplication

#### struct `FRigUnit_HierarchyGetDynamicsConstraintExtraLength`  
`struct FRigUnit_HierarchyGetDynamicsConstraintExtraLength : public FRigUnit_DynamicsBase`  
_L294-309_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Extra Length", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extra length of a Dynamics constraint
- L298 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L303 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to query
- L308 _public member_ `float ExtraLength = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Centimeters"))` — Added on to the target length after the automatic/multiplication

#### struct `FRigUnit_HierarchySetDynamicsConstraintAccelerationMode`  
`struct FRigUnit_HierarchySetDynamicsConstraintAccelerationMode : public FRigUnit_DynamicsBaseMutable`  
_L315-330_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Constraint Acceleration Mode", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets whether a Dynamics constraint is in acceleration mode (mass-independent natural frequency) or force mode (heavier particles oscillate slower). No effect on Hard constraints.
- L319 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L324 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to be updated
- L329 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(meta = (Input))` — True (default) for mass-independent natural frequency; false for a true force-mode spring.

#### struct `FRigUnit_HierarchyGetDynamicsConstraintAccelerationMode`  
`struct FRigUnit_HierarchyGetDynamicsConstraintAccelerationMode : public FRigUnit_DynamicsBase`  
_L335-350_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Constraint Acceleration Mode", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets whether a Dynamics constraint is in acceleration mode.
- L339 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L344 _public member_ `FRigComponentKey DynamicsConstraintComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConstraintComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Constraint Component Key"))` — The Dynamics Constraint to query
- L349 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(meta = (Output))` — True for mass-independent natural frequency; false for a true force-mode spring.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsData.h` (Public)


#### struct `FRigDynamicsShapeBox`  
`struct FRigDynamicsShapeBox`  
_L21-41_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public function_ `FRigDynamicsShapeBox()`
- L27 _public function_ `FRigDynamicsShapeBox(const FName InName, const FTransform& InTM, const FVector& InExtents) : Name(InName), TM(InTM), Extents(InExtents)`
- L32 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape)` — Shape name is optional/only used for identification
- L36 _public member_ `FTransform TM;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta=(MakeEditWidget=true))` — Position and orientation (scale is ignored)
- L40 _public member_ `FVector Extents = FVector::OneVector * RigDynamicsDefaultShapeSize;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta = (ClampMin = "0.0", Units = "Centimeters"))` — These are the full extents of the box in each axis

#### struct `FRigDynamicsShapeCapsule`  
`struct FRigDynamicsShapeCapsule`  
_L45-70_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public function_ `FRigDynamicsShapeCapsule()`
- L51 _public function_ `FRigDynamicsShapeCapsule(const FName InName, const FTransform& InTM, const float InRadius, const float InLength) : Name(InName), TM(InTM), Radius(InRadius), Length(InLength)`
- L56 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape)` — Shape name is optional/only used for identification
- L61 _public member_ `FTransform TM;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta=(MakeEditWidget=true))` — Position and orientation (scale is ignored) Main axis will be along +Z.
- L65 _public member_ `float Radius = RigDynamicsDefaultShapeSize;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta = (ClampMin = "0.0", Units = "Centimeters"))` — Capsule radius
- L69 _public member_ `float Length = RigDynamicsDefaultShapeSize;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta = (ClampMin = "0.0", Units = "Centimeters"))` — This is the length of the core part of the capsule. The total length will be Length + 2 * Radius

#### struct `FRigDynamicsShapePlane`  
`struct FRigDynamicsShapePlane`  
_L74-94_
- reflection: `USTRUCT(BlueprintType)`
- L78 _public function_ `FRigDynamicsShapePlane()`
- L80 _public function_ `FRigDynamicsShapePlane(const FName InName, const FTransform& InTM, const FVector2D& InExtents) : Name(InName), TM(InTM), Extents(InExtents)`
- L85 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape)` — Shape name is optional/only used for identification
- L89 _public member_ `FTransform TM;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta=(MakeEditWidget=true))` — Position defines a point on the plane. Plane faces in the +ve Z direction
- L93 _public member_ `FVector2D Extents = FVector2D(RigDynamicsDefaultShapeSize * 10.0f);` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shape, meta = (ClampMin = "0.0", Units = "Centimeters"))` — Extents of the plane

#### struct `FRigDynamicsShapeCollection`  
`struct FRigDynamicsShapeCollection`  
_L98-113_
- reflection: `USTRUCT(BlueprintType)`
- L103 _public member_ `TArray<FRigDynamicsShapeBox> Boxes;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes)`
- L106 _public member_ `TArray<FRigDynamicsShapeCapsule> Capsules;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes)`
- L109 _public member_ `TArray<FRigDynamicsShapePlane> Planes;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes)`
- L111 _public function_ `bool IsEmpty() const`
- L112 _public function_ `int32 NumShapes() const`

#### enum `ERigDynamicsSimulationSpace`  
`enum class ERigDynamicsSimulationSpace : uint8`  
_L118-131_
- reflection: `UENUM()`
- desc: Specifies what space the simulation should run in.
- L121 _public enumerator_ `World` — Simulate in world space. Moving the skeletal mesh will generate velocity changes
- L125 _public enumerator_ `Component` — Simulate in component space. Moving the entire skeletal mesh will have no effect on velocities unless this is explicitly enabled in the simulation space settings
- L130 _public enumerator_ `SpaceBone` — Simulate in the space of the specified bone. Moving the entire skeletal mesh and/or the Bone will have no effect on velocities unless this is explicitly enabled in the simulation space settings.

#### struct `FRigDynamicsSolverSettings`  
`struct FRigDynamicsSolverSettings`  
_L136-212_
- reflection: `USTRUCT(BlueprintType)`
- desc: Configuration/settings for the dynamics solver
- L141 _public member_ `ERigDynamicsSimulationSpace SimulationSpace = ERigDynamicsSimulationSpace::Component;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)`
- L145 _public member_ `FRigElementKey SpaceBone = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)` — The bone to use for the simulation space (only relevant if SimulationSpace is set to SpaceBone)
- L149 _public member_ `FVector Gravity = FVector(0.0f, 0.0f, -981.0f);` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)` — Gravity in world space. This can be scaled by each particle.
- L153 _public member_ `float MaxTimeStep = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0.0", Units = "Seconds"))` — The maximum timestep of any step.
- L158 _public member_ `int32 MaxNumSteps = 4;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0"))` — The maximum number of steps that the update can be divided into. If MaxNumSteps * MaxTimeStep is less than the update time, the simulation will run "slow".
- L163 _public member_ `int32 NumIterations = 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0"))` — This is the total number of iterations, including iterating over the particle targets. This can normally be 1, unless you want to track targets with very accurate spring behavior.
- L170 _public member_ `int32 NumConstraintSubIterations = 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0"))` — The number of constraint (distance and collision) sub-iterations. Along-chain constraints will be one-way on the last iteration, so if this is 1 (which is often enough), particles in a chain will never be able to affect their parents. Increasing will result in more realistic behavior that comes with a performance cost.
- L177 _public member_ `bool bReadBoneOrientations = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)` — If true, then the read-back from the solver is done by rotating bones to match the directions between particles. If there is no branching, then this will result in the final bones matching the simulated particles (depending on the skeletal bone constraints being fulfilled). However, when there is branching, there can be some deviation.
- L183 _public member_ `bool bReadBonePositions = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)` — If true the bone positions (translation) will be updated based on the particles. This will introduce stretching etc in the skeleton that is not there in the original animation, but it should result in better matching of the simulation and the bone positions.
- L186 _public member_ `bool bResetFromPosition = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (InlineEditConditionToggle))`
- L191 _public member_ `float PositionThresholdForReset = 10000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0.0", EditCondition = "bResetFromPosition", Units = "Centimeters"))` — If any object in the simulation exceeds this distance from the simulation origin, we will reset the pose and velocity of all objects in the simulation. This is to detect problems/explosions.
- L194 _public member_ `bool bResetFromKinematicSpeed = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (InlineEditConditionToggle))`
- L200 _public member_ `float KinematicSpeedThresholdForReset = 10000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0.0", EditCondition = "bResetFromKinematicSpeed", Units = "CentimetersPerSecond"))` — If any kinematic object in the simulation exceeds this speed, we will reset the pose and velocities of all objects in the simulation. This is to detect problems - for example if the target animation has teleports/jumps etc.
- L203 _public member_ `bool bResetFromEvaluationInterval = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (InlineEditConditionToggle))`
- L211 _public member_ `float EvaluationIntervalThresholdForReset = 0.1f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0.0", EditCondition = "bResetFromEvaluationInterval", Units = "Seconds"))` — If the time between successive solver evaluations (measured via the rig's absolute time) exceeds this value AND is also greater than the frame's delta time, the pose and velocities of all objects in the simulation are reset. This detects cases where evaluation was genuinely skipped - e.g. the rig stopped being ticked, or the editor was paused, without triggering just because the frame's delta time was rather large.

#### struct `FRigDynamicsSimulationDragSettings`  
`struct FRigDynamicsSimulationDragSettings`  
_L219-258_
- reflection: `USTRUCT(BlueprintType)`
- desc: Air/ether drag settings applied to the whole simulation, due to the movement of the simulation space (typically as a result of the actor/component moving). These act on top of the per-particle Damping. They describe the air/ether medium that particles are dragged toward.
- L230 _public member_ `float AdditionalDamping = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", Units = "Hertz"))` — Extra air/ether damping added to every dynamic particle's own Damping value. Use this when you want the wind (ExternalLinearVelocity, turbulence) to push every particle in the simulation, including ones that were authored with a per-particle Damping of zero. 0 disables it (only the per-particle Damping matters); higher values make every particle damp toward the air/ether more aggressively. Like the per-particle Damping, this is scaled by the particle's bScaleDampingByInverseMass flag so the global baseline shares the particle's mass-scaling choice.
- L236 _public member_ `float LinearDragMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation frame's linear velocity contributes to the air/ether target that particles are dragged toward. 0 means the sim-space linear motion does not affect drag. 1 means particles are pulled toward world-at-rest as the space moves.
- L241 _public member_ `float AngularDragMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation frame's angular velocity contributes to the air/ether target. As for LinearDragMultiplier but for the rotational part (rotation induced velocity at each particle position).
- L247 _public member_ `FVector ExternalLinearVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (Units = "cm/s"))` — Extra linear air/ether velocity in world space. Particles with non-zero Damping are pulled along with it, giving a wind-like effect. Typical values are similar to the velocity of the object or effect, and usually around or less than 1000 for characters/wind.
- L252 _public member_ `FVector ExternalAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (Units = "deg/s"))` — Extra angular air/ether velocity in world space, units deg/s. Produces a linear air/ether velocity of (AngVel x R) at each particle's sim-space position, on top of ExternalLinearVelocity.
- L257 _public member_ `FVector ExternalTurbulenceVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (Units = "cm/s"))` — Per-axis magnitude of Perlin turbulence added to ExternalLinearVelocity. Units are the same as velocity, so this is the approximate magnitude of the turbulence along each component axis.

#### struct `FRigDynamicsInertialForceSettings`  
`struct FRigDynamicsInertialForceSettings`  
_L265-297_
- reflection: `USTRUCT(BlueprintType)`
- desc: Master gain on the pseudo-forces (Coriolis, centrifugal, Euler, linear) caused by movement of the simulation space itself (typically, movement of the actor/component). 0 disables inertial-frame coupling entirely. These properties will not affect air/ether drag effects.
- L272 _public member_ `float Amount = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Master multiplier applied on top of the per-term multipliers below. Use this to scale all four inertial-frame effects together. Set to 0 to disable inertial effects entirely.
- L278 _public member_ `float LinearEulerAmount = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How strongly bodies react when the actor accelerates in a straight line - e.g. when the character starts running, brakes hard, or jumps. 0 disables this response; 1 is full strength. Multiplied with the overall Amount.
- L284 _public member_ `float AngularEulerAmount = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How strongly bodies react when the actor's rotation speed changes - e.g. when the character starts spinning or comes to a stop. Distinct from Centrifugal, which is about sustained rotation. 0 disables; 1 is full strength. Multiplied with the overall Amount.
- L290 _public member_ `float CentrifugalAmount = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Strength of the outward "fling" that bodies feel while the actor is rotating - this is what makes hair and cloth swing wide on a spinning character. 0 disables; 1 is full strength. Multiplied with the overall Amount.
- L296 _public member_ `float CoriolisAmount = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Strength of the sideways deflection that bodies experience as they move within a rotating actor. Usually a subtle effect - the least visually noticeable of the four. 0 disables; 1 is full strength. Multiplied with the overall Amount.

#### struct `FRigDynamicsSimulationSpaceMotion`  
`struct FRigDynamicsSimulationSpaceMotion`  
_L304-365_
- reflection: `USTRUCT(BlueprintType)`
- desc: How the simulation-space linear/angular velocity and acceleration are conditioned (vertical scale + clamps) before being passed to the inertial pseudo-forces and the air/ether drag effects. These do not affect teleport detection.
- L312 _public member_ `float VerticalMotionScale = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)` — Multiplier on the vertical (Z) component of linear velocity AND linear acceleration before clamping. Usually from 0.0 to 1.0 to reduce the effects of jumping and crouching on the simulation, but it can be higher than 1.0 if you need to exaggerate this motion.
- L315 _public member_ `bool bClampLinearVelocity = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L322 _public member_ `float MaxLinearVelocity = 10000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearVelocity", Units = "CentimetersPerSecond"))` — A clamp on the effective world-space velocity that is passed to the simulation. It is not usually required to change this but you would reduce this to limit the effects of drag on the bodies in the simulation, for example. Expected values would be somewhat less than the usual velocities of your object which is commonly a few hundred for a character.
- L325 _public member_ `bool bClampAngularVelocity = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L334 _public member_ `float MaxAngularVelocity = 720.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularVelocity", Units = "DegreesPerSecond"))` — A clamp on the effective world-space angular velocity that is passed to the simulation. Units are deg/s, so a value of 360 is one full rotation per second. You would reduce this (and MaxAngularAcceleration) to limit how much bodies "fly out" when the actor spins on the spot. Especially useful if you have characters that can rotate very quickly, but you do not want to see simulated objects flung outwards excessively. Values around or less than 720 are typical in that case.
- L337 _public member_ `bool bClampLinearAcceleration = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L345 _public member_ `float MaxLinearAcceleration = 10000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearAcceleration"))` — A clamp on the effective world-space acceleration that is passed to the simulation. Used to stop the bodies of the simulation flying out when suddenly changing linear speed. Useful when characters can change from stationary to running very quickly, to prevent simulated objects from being flung backwards. A common value for a character might be a few thousands (e.g. 10x gravity).
- L348 _public member_ `bool bClampAngularAcceleration = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L355 _public member_ `float MaxAngularAcceleration = 7200.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularAcceleration"))` — A clamp on the effective world-space angular acceleration that is passed to the simulation. Units are deg/s/s. Similar effect to MaxAngularVelocity but related to bodies flying out/backwards when the rotation speed suddenly changes. A typical value for a character might be around 7200.
- L360 _public member_ `FRigDynamicsInertialForceSettings InertialForces;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)` — Inertial pseudo-force properties. Uses the conditioned velocity/acceleration above and applies Coriolis / centrifugal / Euler / linear forces, scaled by Amount.
- L364 _public member_ `FRigDynamicsSimulationDragSettings Drag;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)` — Air/ether drag. Uses the conditioned linear and angular velocities above.

#### struct `FRigDynamicsTeleportDetectionSettings`  
`struct FRigDynamicsTeleportDetectionSettings`  
_L373-404_
- reflection: `USTRUCT(BlueprintType)`
- desc: Teleport-detection thresholds based on the movement of the simulation space. These operate on raw deltas in the simulation-space transform (not on the animation pose itself). When any threshold is crossed the solver zeroes velocities/accelerations for the frame without resetting the simulation pose.
- L378 _public member_ `bool bFromPositionChange = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L382 _public member_ `float PositionChangeThreshold = 100.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromPositionChange", Units = "Centimeters"))` — If the linear position change of the simulation space is above this threshold, the movement is treated as a teleport.
- L385 _public member_ `bool bFromOrientationChange = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L389 _public member_ `float OrientationChangeThreshold = 30.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromOrientationChange", Units = "Degrees"))` — If the angular change (degrees) of the simulation space is above this threshold, the movement is treated as a teleport.
- L392 _public member_ `bool bFromLinearAcceleration = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L396 _public member_ `float LinearAccelerationThreshold = 100000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromLinearAcceleration"))` — If the linear acceleration of the simulation space is above this threshold, the movement is treated as a teleport.
- L399 _public member_ `bool bFromAngularAcceleration = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L403 _public member_ `float AngularAccelerationThreshold = 100000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromAngularAcceleration"))` — If the angular acceleration (deg/s/s) of the simulation space is above this threshold, the movement is treated as a teleport.

#### struct `FRigDynamicsSimulationSpaceSettings`  
`struct FRigDynamicsSimulationSpaceSettings`  
_L413-474_
- reflection: `USTRUCT(BlueprintType)`
- L420 _public member_ `float SpaceMovementAmount = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Overall multiplier on the effects of simulation space movement on the simulation. Mapped onto the new master FRigDynamicsInertialForceSettings::Amount during conversion.
- L425 _public member_ `float VelocityScaleZ = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)` — Multiplier on the components of vertical velocity and acceleration of the simulation space that is passed to the simulation. Mapped onto FRigDynamicsSimulationSpaceMotion::VerticalMotionScale.
- L428 _public member_ `bool bClampLinearVelocity = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L431 _public member_ `float MaxLinearVelocity = 10000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearVelocity", Units = "CentimetersPerSecond"))`
- L434 _public member_ `bool bClampAngularVelocity = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L437 _public member_ `float MaxAngularVelocity = 720.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularVelocity", Units = "DegreesPerSecond"))`
- L440 _public member_ `bool bClampLinearAcceleration = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L443 _public member_ `float MaxLinearAcceleration = 10000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearAcceleration"))`
- L446 _public member_ `bool bClampAngularAcceleration = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L449 _public member_ `float MaxAngularAcceleration = 7200.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularAcceleration"))`
- L452 _public member_ `bool bTeleportFromLinearAcceleration = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L455 _public member_ `float LinearAccelerationThresholdForTeleport = 100000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bTeleportFromLinearAcceleration"))`
- L458 _public member_ `bool bTeleportFromAngularAcceleration = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L461 _public member_ `float AngularAccelerationThresholdForTeleport = 100000.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bTeleportFromAngularAcceleration"))`
- L464 _public member_ `bool bTeleportFromPositionChange = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L467 _public member_ `float PositionChangeThresholdForTeleport = 100.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bTeleportFromPositionChange", Units = "Centimeters"))`
- L470 _public member_ `bool bTeleportFromOrientationChange = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L473 _public member_ `float OrientationChangeThresholdForTeleport = 30.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bTeleportFromOrientationChange", Units = "Degrees"))`

#### enum `ERigDynamicsParticleValueDisplay`  
`enum class ERigDynamicsParticleValueDisplay : uint8`  
_L489-502_
- reflection: `UENUM()`
- desc: Selects which particle property to display numerically next to each particle in the debug draw.
- L491 _public enumerator_ `None`
- L492 _public enumerator_ `Radius`
- L493 _public enumerator_ `Mass`
- L494 _public enumerator_ `GravityMultiplier`
- L495 _public enumerator_ `Strength`
- L496 _public enumerator_ `DampingRatio`
- L497 _public enumerator_ `ExtraDamping`
- L498 _public enumerator_ `Damping`
- L499 _public enumerator_ `TargetMode`
- L500 _public enumerator_ `AngleLimit`
- L501 _public enumerator_ `AngleLimitStrength`

#### struct `FRigDynamicsVisualizationSettings`  
`struct FRigDynamicsVisualizationSettings`  
_L509-556_
- reflection: `USTRUCT(BlueprintType)`
- desc: Visualization toggles for the rig's dynamics simulation. Enabling any bShow* flag activates debug drawing - which has significant runtime cost - so disable everything before profiling. Visualization can also be globally suppressed at runtime via the CVar ControlRig.Dynamics.AllowVisualization.
- L514 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))`
- L517 _public member_ `int32 ShapeDetail = 16;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization, meta = (ClampMin = "6"))`
- L520 _public member_ `bool bShowParticles = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)`
- L523 _public member_ `bool bShowColliders = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)`
- L526 _public member_ `bool bShowConfiners = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)`
- L530 _public member_ `bool bShowSkeletalConstraints = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)` — Show the auto-generated skeletal distance constraints between each particle and its parent.
- L534 _public member_ `bool bShowHardConstraints = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)` — Show user-defined hard distance constraints.
- L538 _public member_ `bool bShowSoftConstraints = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)` — Show user-defined soft distance constraints.
- L544 _public member_ `bool bShowAngleLimits = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)` — Show the per-particle angle-limit cones (with green tint). Cone apex is at the parent particle, axis along the target direction, length = current bone length. Pale green when the simulated direction is within the limit, red-with-green-mixed-in when it has swung outside.
- L551 _public member_ `bool bShowConeLimits = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)` — Show the per-cone-limit cones (with blue tint). Cone apex is at the parent particle, axis along the incoming bone direction (grandparent->parent), length = current parent->child distance. Pale blue when the child direction is within the limit, red-with-blue-mixed-in when it has swung outside.
- L555 _public member_ `ERigDynamicsParticleValueDisplay ParticleValueDisplay = ERigDynamicsParticleValueDisplay::None;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Visualization)` — When not None, the selected particle property is drawn as text next to each particle.

#### struct `FRigDynamicsParticleProperties`  
`struct FRigDynamicsParticleProperties`  
_L560-651_
- reflection: `USTRUCT(BlueprintType)`
- L566 _public member_ `float Radius = RigDynamicsDefaultParticleRadius;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0", Units = "Centimeters"))` — The radius of the particle, used for collision
- L570 _public member_ `float Mass = RigDynamicsDefaultParticleMass;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0001", Units = "Kilograms"))` — The mass of the particle, affecting how it will respond to constraints (and external forces etc)
- L574 _public member_ `ERigParticleSimulationMovementType MovementType = ERigParticleSimulationMovementType::Simulated;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics)` — How the particle moves
- L578 _public member_ `float GravityMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics)` — Scales the solver gravity
- L584 _public member_ `float Strength = 2.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control, meta = (ClampMin = "0.0", Units = "Hertz"))` — The strength which we drive towards the target (when simulated). This is the oscillation frequency, so low values will be soft and springy, but values significantly above 1/timestep will track the target very accurately.
- L588 _public member_ `float DampingRatio = 0.5f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control, meta = (ClampMin = "0.0"))` — DampingRatio for the tracking particle target
- L592 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control, meta = (ClampMin = "0.0", Units = "Hertz"))` — Additional damping for tracking the particle target
- L599 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control)` — When true, Strength is a mass-independent natural frequency. When false, the spring/damper acts as a true force, so heavier particles oscillate more slowly. Applies to target tracking only - the per-particle angle limit is always acceleration-mode regardless of this flag.
- L604 _public member_ `float TargetVelocityInfluence = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control)` — If TargetVelocityInfluence = 1 then the target's velocity will be used for damping. If 0 then the damping is in simulation space (so acting more like drag)
- L609 _public member_ `float TargetMode = 0.5f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — 0 = SimSpace (child tracks absolute animation target), 1 = directional (child+parent track animation direction). Values between blend the two modes.
- L614 _public member_ `float AngleLimit = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AngleLimits, meta = (ClampMin = "0.0", Units = "Degrees"))` — Constrains this particle to align with the target direction from its parent, to within this angle (in degrees). This effectively gives us a limit on the deviation from the target pose.
- L620 _public member_ `float AngleLimitStrength = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AngleLimits, meta = (ClampMin = "0.0", Units = "Hertz"))` — The strength of the angle limit constraint (oscillation frequency). High values impose the limit more rigidly, low values allow soft/springy deviation before settling. Zero disables the angle limit.
- L628 _public member_ `float Damping = 0.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Drag, meta = (DisplayName = "Damping/Drag", ClampMin = "0.0", Units = "Hertz"))` — Air/ether damping (like drag). Particle velocity in simulation space is relaxed toward the local air/ether (world-at-rest, plus any simulation-space motion scaled by the solver's linear / angular drag multipliers). With bScaleDampingByInverseMass=false, the relaxation timescale is 1/Damping for any mass. With bScaleDampingByInverseMass=true, Damping is divided by mass so lighter particles damp faster, making this behave more like drag.
- L634 _public member_ `bool bScaleDampingByInverseMass = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Drag, meta = (DisplayName = "Treat damping as drag"))` — When true, Damping is divided by mass (drag-like - light particles damp faster). When false, Damping is mass-independent (same relaxation timescale for any mass). Matches the FRigPhysicsDynamics::bScaleDampingByInverseMass flag in ControlRigPhysics.
- L638 _public member_ `bool bCollideWithColliders = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Collision)` — If false, this particle ignores all colliders regardless of NoCollisionColliders.
- L642 _public member_ `TArray<FRigComponentKey> NoCollisionColliders;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Collision)` — A list of colliders we shouldn't collide with
- L646 _public member_ `TArray<FRigComponentKey> CollisionParticles;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Collision)` — A list of other particles we should collide with
- L650 _public member_ `TArray<FRigComponentKey> Confiners;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Collision)` — A list of confiners that will keep this particle inside their shapes (opt-in).

#### struct `FRigDynamicsParticleForce`  
`struct FRigDynamicsParticleForce`  
_L660-683_
- reflection: `USTRUCT(BlueprintType)`
- L664 _public prototype_ `FRigDynamicsParticleForce() = default;`
- L666 _public function_ `FRigDynamicsParticleForce( const FVector& InForce, EPhysicsControlSpace InSpace, EPhysicsControlForceType InType) : Force(InForce), Space(InSpace), Type(InType)`
- L672 _public member_ `FVector Force = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Force)` — Direction and magnitude. Interpretation (units etc) depends on Type.
- L677 _public member_ `EPhysicsControlSpace Space = EPhysicsControlSpace::World;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Force)` — Frame the Force is expressed in. Body means the space of the particle's owning bone in the input pose (animation pose at the time of the step, before simulation writeback).
- L682 _public member_ `EPhysicsControlForceType Type = EPhysicsControlForceType::Force;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Force)` — How Force is interpreted: Force (kg cm/s^2), Acceleration (cm/s^2, mass-independent), Impulse (kg cm/s, one-shot momentum change), VelocityChange (cm/s, one-shot, mass-independent).

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`
- L15 _variable_ `constexpr float RigDynamicsDefaultShapeSize = 10.0f;`
- L16 _variable_ `constexpr float RigDynamicsDefaultParticleRadius = 5.0f;`
- L17 _variable_ `constexpr float RigDynamicsDefaultParticleMass = 1.0f;`
- L481 _prototype_ `void ConvertLegacyDynamicsSimulationSpaceSettings( const FRigDynamicsSimulationSpaceSettings& In, FRigDynamicsSimulationSpaceMotion& OutMotion, FRigDynamicsTeleportDetectionSettings& OutTeleport);` — Translates the legacy combined struct (from the deprecated FRigUnit_SpawnDynamicsSolver pin layout) into the new SpaceMotion / TeleportDetection structs. SpaceMotion.Drag is left untouched - in the legacy layout drag fields lived on a separate FRigDynamicsSimulationDragSettings pin, so the caller is expected to assign that separately.
- L686 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsParticleProperties& Data);`
- L687 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsTeleportDetectionSettings& Data);`
- L688 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsInertialForceSettings& Data);`
- L689 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsSimulationSpaceMotion& Data);`
- L690 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsSimulationDragSettings& Data);`
- L691 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsSolverSettings& Data);`
- L692 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsShapeCollection& Data);`
- L693 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsShapePlane& Data);`
- L694 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsShapeCapsule& Data);`
- L695 _prototype_ `FArchive& operator <<(FArchive& Ar, FRigDynamicsShapeBox& Data);`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsExecution.h` (Public)


#### struct `FRigUnit_DynamicsBaseMutable`  
`struct FRigUnit_DynamicsBaseMutable : public FRigUnitMutable`  
_L15-18_
- reflection: `USTRUCT(meta = (Category = "RigDynamics", NodeColor = "1.0 0.9 0.0", Keywords = "Dynamics", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnitMutable`

#### struct `FRigUnit_DynamicsBase`  
`struct FRigUnit_DynamicsBase : public FRigUnit`  
_L24-27_
- reflection: `USTRUCT(meta = (Category = "RigDynamics", NodeColor = "1.0 0.9 0.0", Keywords = "Dynamics", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnit`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsExecutionHelpers.h` (Public)


#### struct `FRigDynamicsShapeCollectionWithKey`  
`struct FRigDynamicsShapeCollectionWithKey`  
_L18-29_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `FRigElementKey Owner = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes)` — The bone that owns the colliders
- L28 _public member_ `FRigDynamicsShapeCollection Shapes;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Shapes, meta = (ShowOnlyInnerProperties))` — The collider properties

#### struct `FParticleChainCurves`  
`struct FParticleChainCurves`  
_L38-112_
- reflection: `USTRUCT(BlueprintType)`
- desc: Multiplier curves applied to particle properties along each chain. Each curve is evaluated at the particle's normalized along-chain position (0 at the chain root, 1 at the leaf) and multiplies the corresponding field of ParticleProperties. Default is a flat line at 1.0 (no change).
- L42 _public function_ `FParticleChainCurves()`
- L66 _public member_ `FRuntimeFloatCurve RadiusMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Radius Multiplier"))` — Multiplier on ParticleProperties.Radius along each chain.
- L71 _public member_ `FRuntimeFloatCurve MassMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Mass Multiplier"))` — Multiplier on ParticleProperties.Mass along each chain.
- L76 _public member_ `FRuntimeFloatCurve GravityMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Gravity Multiplier"))` — Multiplier on ParticleProperties.GravityMultiplier along each chain.
- L81 _public member_ `FRuntimeFloatCurve StrengthMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Strength Multiplier"))` — Multiplier on ParticleProperties.Strength along each chain.
- L86 _public member_ `FRuntimeFloatCurve DampingRatioMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Damping Ratio Multiplier"))` — Multiplier on ParticleProperties.DampingRatio along each chain.
- L91 _public member_ `FRuntimeFloatCurve ExtraDampingMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Extra Damping Multiplier"))` — Multiplier on ParticleProperties.ExtraDamping along each chain.
- L96 _public member_ `FRuntimeFloatCurve DampingMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Damping Multiplier"))` — Multiplier on ParticleProperties.Damping along each chain.
- L101 _public member_ `FRuntimeFloatCurve TargetModeMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Target Mode Multiplier"))` — Multiplier on ParticleProperties.TargetMode along each chain.
- L106 _public member_ `FRuntimeFloatCurve AngleLimitMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Angle Limit Multiplier"))` — Multiplier on ParticleProperties.AngleLimit along each chain.
- L111 _public member_ `FRuntimeFloatCurve AngleLimitStrengthMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ChainCurves, meta = (XAxisName = "Chain Position", YAxisName = "Angle Limit Strength Multiplier"))` — Multiplier on ParticleProperties.AngleLimitStrength along each chain.

#### struct `FRigDynamicsSolverCreationSettings`  
`struct FRigDynamicsSolverCreationSettings`  
_L119-135_
- reflection: `USTRUCT(BlueprintType)`
- desc: Bundle of settings used when a spawn helper needs to create a new solver. When the helper is pointed at an existing solver (the SolverElementKey/SolverComponentName already resolves to a component) these fields are ignored and the existing solver's settings are preserved.
- L125 _public member_ `FRigDynamicsSolverSettings SolverSettings;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverCreation)` — Solver settings (gravity, iteration counts, substepping, reset thresholds, ...).
- L130 _public member_ `FRigDynamicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverCreation)` — Simulation-space motion conditioning (vertical scale + clamps), with the inertial-force gain and air/ether drag settings nested inside.
- L134 _public member_ `FRigDynamicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverCreation)` — Teleport-detection thresholds (operates on raw simulation-space deltas).

#### struct `FRigUnit_SpawnDynamicsChains`  
`struct FRigUnit_SpawnDynamicsChains : public FRigUnit_DynamicsBaseMutable`  
_L141-217_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Chains", Keywords = "Add,Construction,Create,New,Simulation", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Spawns a new dynamics chain (or chains) Note: This node only runs as part of the construction event.
- L145 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L148 _public function_ `FRigUnit_SpawnDynamicsChains()`
- L155 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Optional solver - if valid then particles (etc) that are created will be added to this solver component
- L162 _public member_ `TArray<FRigElementKey> RootBones;` — `UPROPERTY(meta = (Input, BoneName))` — An array of root bones. Each one of these will start a chain, which includes all its children/descendants. If a bone is reachable from more than one root (e.g. one root is an ancestor of another), it will only have a single particle created for it.
- L167 _public member_ `TArray<FRigElementKey> ChainTerminatorBones;` — `UPROPERTY(meta = (Input))` — An array of bones that will terminate the chain search. Terminator bones will (if part of a chain) have particles created, but their children will not.
- L172 _public member_ `TArray<FRigElementKey> ElementIncludeMask;` — `UPROPERTY(meta = (Input))` — If this is empty, then particles will be created for every bone discovered by the chain search. Otherwise, only bones that are also in this list will receive particles.
- L177 _public member_ `TArray<FRigElementKey> ElementExcludeMask;` — `UPROPERTY(meta = (Input))` — If this is empty, then no discovered bones will be excluded. Otherwise, bones in this list will not receive particles even when reached by the chain search.
- L182 _public member_ `TArray<FRigElementKey> ExtraBones;` — `UPROPERTY(meta = (Input))` — Additional bones to be included (processed after other exclusions). Duplicates (bones already covered by RootBones or another ExtraBones entry) are ignored.
- L188 _public member_ `FName ParticleComponentName = FRigDynamicsParticleComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give each particle component created by this node. The same base name is used on every owner bone, so the hierarchy will append unique suffixes whenever a clash occurs. ParticleComponentKeys is the authoritative list of actual names.
- L193 _public member_ `FRigDynamicsParticleProperties ParticleProperties;` — `UPROPERTY(meta = (Input))` — Basic properties for all the particles that are created. Note that the curves can be used to vary these properties along the chains.
- L198 _public member_ `FParticleChainCurves ChainCurves;` — `UPROPERTY(meta = (Input))` — Multiplier curves applied along each chain (evaluated at the particle's normalized along-chain position). Defaults to flat lines at 1.0 - no change from ParticleProperties.
- L204 _public member_ `FName ColliderComponentName = FRigDynamicsColliderComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give each collider component created by this node. The same base name is used on every owner bone, so the hierarchy will append unique suffixes whenever a clash occurs. ColliderComponentKeys is the authoritative list of actual names.
- L208 _public member_ `TArray<FRigDynamicsShapeCollectionWithKey> Colliders;` — `UPROPERTY(meta = (Input))` — Additional Colliders that are attached to bones and track the incoming animation
- L212 _public member_ `TArray<FRigComponentKey> ParticleComponentKeys;` — `UPROPERTY(meta = (Output))` — The particle component keys that were created
- L216 _public member_ `TArray<FRigComponentKey> ColliderComponentKeys;` — `UPROPERTY(meta = (Output))` — The collider component keys that were created

#### struct `FRigUnit_HierarchyImportDynamicsCollidersFromPhysicsAsset`  
`struct FRigUnit_HierarchyImportDynamicsCollidersFromPhysicsAsset : public FRigUnit_DynamicsBaseMutable`  
_L222-255_
- reflection: `USTRUCT(meta = (DisplayName = "Import Dynamics Colliders From Physics Asset", Keywords = "Construction,Create,New", Varying, Deprecated = "5.8"))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Imports collision from a physics asset and assigns it as colliders in the dynamics system
- L226 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L229 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`
- L234 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Solver to add the colliders to
- L241 _public member_ `FName ColliderComponentName = FRigDynamicsColliderComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give each collider component created by this node. The same base name is used for every imported body, so the hierarchy will append unique suffixes whenever a clash occurs. DynamicsColliderComponentKeys is the authoritative list of actual names.
- L245 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(meta = (Input))` — The physics asset to import colliders from
- L250 _public member_ `TArray<FName> BoneMask;` — `UPROPERTY(meta = (Input))` — If this is empty, then all bones with bodies in the physics asset will be created. Otherwise only bodies that relate to the specified bones will be created.
- L254 _public member_ `TArray<FRigComponentKey> DynamicsColliderComponentKeys;` — `UPROPERTY(meta = (Output, DisplayName = "Collider Component Keys"))` — The dynamics collider component keys that were created

#### struct `FRigUnit_HierarchyImportDynamicsCollidersFromPhysicsAsset1`  
`struct FRigUnit_HierarchyImportDynamicsCollidersFromPhysicsAsset1 : public FRigUnit_DynamicsBaseMutable`  
_L260-300_
- reflection: `USTRUCT(meta = (DisplayName = "Import Dynamics Colliders From Physics Asset", Keywords = "Construction,Create,New", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Imports collision from a physics asset and assigns it as colliders in the dynamics system
- L264 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L269 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Solver to add the colliders to
- L276 _public member_ `FName ColliderComponentName = FRigDynamicsColliderComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give each collider component created by this node. The same base name is used for every imported body, so the hierarchy will append unique suffixes whenever a clash occurs. DynamicsColliderComponentKeys is the authoritative list of actual names.
- L280 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(meta = (Input))` — The physics asset to import colliders from
- L285 _public member_ `TArray<FRigElementKey> ElementIncludeMask;` — `UPROPERTY(meta = (Input))` — If this is empty, then all bones with bodies in the physics asset will be created. Otherwise, only bodies that relate to the specified elements will be created.
- L290 _public member_ `TArray<FRigElementKey> ElementExcludeMask;` — `UPROPERTY(meta = (Input))` — If this is empty, then no bodies will be excluded. Otherwise, bodies that relate to the specified elements will not be created.
- L295 _public member_ `bool bExcludeElementsWithParticles = true;` — `UPROPERTY(meta = (Input))` — If true, then elements that have particles associated with our solver will be excluded from having colliders made.
- L299 _public member_ `TArray<FRigComponentKey> DynamicsColliderComponentKeys;` — `UPROPERTY(meta = (Output, DisplayName = "Collider Component Keys"))` — The dynamics collider component keys that were created

#### struct `FRigDynamicsForceFieldCurves`  
`struct FRigDynamicsForceFieldCurves`  
_L307-339_
- reflection: `USTRUCT(BlueprintType)`
- desc: Multiplier curves applied to a force-field's three contributions. Each curve is evaluated at the particle's normalised radial position inside the field (0 at the centre, 1 at the surface) and multiplies the corresponding magnitude. Default is a ramp down to zero at the edge of the force field.
- L311 _public function_ `FRigDynamicsForceFieldCurves()`
- L328 _public member_ `FRuntimeFloatCurve RadialMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ForceFieldCurves, meta = (XAxisName = "Radius fraction", YAxisName = "Radial Force Multiplier"))` — Multiplier on the radial force magnitude.
- L333 _public member_ `FRuntimeFloatCurve LinearMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ForceFieldCurves, meta = (XAxisName = "Radius fraction", YAxisName = "Linear Force Multiplier"))` — Multiplier on the linear force magnitude.
- L338 _public member_ `FRuntimeFloatCurve RotationalMultiplier;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ForceFieldCurves, meta = (XAxisName = "Radius fraction", YAxisName = "Rotational Force Multiplier"))` — Multiplier on the rotational force magnitude.

#### struct `FRigUnit_HierarchyAddDynamicsParticleForceField`  
`struct FRigUnit_HierarchyAddDynamicsParticleForceField : public FRigUnit_DynamicsBaseMutable`  
_L350-418_
- reflection: `USTRUCT(meta = (DisplayName = "Add Dynamics Particle Force Field", Keywords = "Force,Impulse,Acceleration,Velocity", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Specifies forces on Dynamics particles to be applied in the next simulation step, based on the particle's location relative to the field. Multiple calls within the same frame accumulate. Forces queued during a pass-through frame (the next StepDynamicsSolver has Alpha <= 0) are discarded. Particles have no orientation, so there is no torque or location-offset variant. The force (which can be specified as a force, acceleration, impulse or velocity change) is made up of a radial, linear and rotational contribution.
- L354 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L357 _public function_ `FRigUnit_HierarchyAddDynamicsParticleForceField()`
- L366 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Solver to use
- L372 _public member_ `FTransform FieldTransform;` — `UPROPERTY(meta = (Input))` — The position, orientation and extents of the field shape. The scale specifies the radius (cm) in each direction, so the field ends up being an ellipsoid shape.
- L376 _public member_ `ERigDynamicsSimulationSpace Space = ERigDynamicsSimulationSpace::World;` — `UPROPERTY(meta = (Input))` — The space in which the field is specified.
- L381 _public member_ `EPhysicsControlForceType Type = EPhysicsControlForceType::Force;` — `UPROPERTY(meta = (Input))` — How Force is interpreted: Force (kg cm/s^2), Acceleration (cm/s^2, mass-independent), Impulse (kg cm/s, one-shot momentum change), VelocityChange (cm/s, one-shot, mass-independent).
- L385 _public member_ `float RadialForce = 0.0f;` — `UPROPERTY(meta = (Input))` — The magnitude of the radial contribution
- L390 _public member_ `FVector LinearForceDirection = FVector::XAxisVector;` — `UPROPERTY(meta = (Input))` — The direction of the linear contribution. Auto-normalised internally, so a non-unit vector does not double-encode the magnitude.
- L394 _public member_ `float LinearForce = 0.0f;` — `UPROPERTY(meta = (Input))` — The magnitude of the linear contribution
- L399 _public member_ `FVector RotationalForceAxis = FVector::ZAxisVector;` — `UPROPERTY(meta = (Input))` — The axis around which the rotational contribution is applied. Only the direction is used; magnitude comes from RotationalForce.
- L403 _public member_ `float RotationalForce = 0.0f;` — `UPROPERTY(meta = (Input))` — The magnitude of the rotational contribution
- L407 _public member_ `FRigDynamicsForceFieldCurves FieldCurves;` — `UPROPERTY(meta = (Input))` — Per-radius-fraction multiplier curves applied to each of the three contributions.
- L412 _public member_ `bool bDrawDebug = false;` — `UPROPERTY(meta = (Input))` — If true, the field draws its ellipsoid shape and an arrow per in-field particle showing this field's force contribution. Subject to the ControlRig.Dynamics.AllowVisualization CVar.
- L417 _public member_ `float DebugForceScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Multiplier on the debug arrow length. Force magnitudes (kg cm/s^2 for Force, kg cm/s for Impulse, etc.) are unwieldy as world-space lengths; tune until the arrows are legible.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`
- L46 _function_ `` (scope `FParticleChainCurves::FParticleChainCurves`)
- L315 _function_ `` (scope `FRigDynamicsForceFieldCurves::FRigDynamicsForceFieldCurves`)

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsParticleComponent.h` (Public)


#### struct `FRigDynamicsParticleComponent`  
`struct FRigDynamicsParticleComponent : public FRigBaseComponent`  
_L18-41_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L22 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigDynamicsParticleComponent) UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Dynamics, meta = (ShowOnlyInnerProperties)) FRigDynamicsParticleProperties ParticleProperties;`
- L31 _public member_ `TArray<FRigDynamicsParticleForce> PendingForces;` — `UPROPERTY(Transient)` — Per-frame queue of forces appended by AddDynamicsParticleForce nodes during the rig's forwards-execution event. Consumed by FRigDynamicsSolver::UpdatePreDynamics each step (or cleared when a step is skipped via Alpha <= 0).
- L33 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L34 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L36 _public function_ `virtual FName GetDefaultComponentName() const override`
- L37 _public function_ `static FName GetDefaultName()`
- L40 _protected prototype_ `void Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsParticleExecution.h` (Public)


#### struct `FRigUnit_SpawnDynamicsParticle`  
`struct FRigUnit_SpawnDynamicsParticle : public FRigUnit_DynamicsBaseMutable`  
_L19-48_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Particle", Keywords = "Add,Construction,Create,New,Body", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Spawns a new dynamics particle as a component on the owner element. Note: This node only runs as part of the construction event.
- L23 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L28 _public member_ `FRigElementKey Owner = FRigElementKey(TEXT(""), ERigElementType::Bone);` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L32 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — Optional solver - if set, it will be added to this solver component
- L39 _public member_ `FName ParticleComponentName = FRigDynamicsParticleComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the new particle component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsParticleComponentKey to find the name that was actually assigned.
- L43 _public member_ `FRigDynamicsParticleProperties ParticleProperties;` — `UPROPERTY(meta = (Input))` — Particle properties
- L47 _public member_ `FRigComponentKey DynamicsParticleComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Particle Component Key"))` — The Dynamics Particle component key that was created

#### struct `FRigUnit_GetDynamicsParticleExists`  
`struct FRigUnit_GetDynamicsParticleExists : public FRigUnit_DynamicsBase`  
_L53-68_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Exists", Keywords = "Query,Body"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Indicates whether the component exists and is a Dynamics Particle
- L57 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L62 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The component key to check
- L67 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Dynamics Particle

#### struct `FRigUnit_HierarchyDisableDynamicsCollisionWithCollider`  
`struct FRigUnit_HierarchyDisableDynamicsCollisionWithCollider : public FRigUnit_DynamicsBaseMutable`  
_L73-90_
- reflection: `USTRUCT(meta = (DisplayName = "Disable Dynamics Collision With Collider", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Disables collision between a particle and a collider
- L77 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L82 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated (which must exist)
- L88 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Collider to not collide with (which doesn't have to exist yet)

#### struct `FRigUnit_HierarchyAllowDynamicsCollisionWithCollider`  
`struct FRigUnit_HierarchyAllowDynamicsCollisionWithCollider : public FRigUnit_DynamicsBaseMutable`  
_L98-115_
- reflection: `USTRUCT(meta = (DisplayName = "Allow Dynamics Collision With Collider", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Allows collision between a particle and a specific collider, by removing it from the particle's NoCollisionColliders list. Silent no-op if the collider is not in the list. Note that bCollideWithColliders is still the master switch - allowing a specific collider does not override that.
- L102 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L107 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated (which must exist)
- L113 _public member_ `FRigComponentKey DynamicsColliderComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsColliderComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Collider Component Key"))` — The Collider to re-enable collision with (which doesn't have to exist yet)

#### struct `FRigUnit_HierarchySetDynamicsParticleNoCollisionColliders`  
`struct FRigUnit_HierarchySetDynamicsParticleNoCollisionColliders : public FRigUnit_DynamicsBaseMutable`  
_L120-135_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle No-Collision Colliders", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Replaces the entire NoCollisionColliders list on a particle.
- L124 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L129 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated (which must exist)
- L134 _public member_ `TArray<FRigComponentKey> NoCollisionColliders;` — `UPROPERTY(meta = (Input))` — The list of colliders that this particle should not collide with

#### struct `FRigUnit_HierarchyGetDynamicsParticleNoCollisionColliders`  
`struct FRigUnit_HierarchyGetDynamicsParticleNoCollisionColliders : public FRigUnit_DynamicsBase`  
_L140-155_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle No-Collision Colliders", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Returns the current NoCollisionColliders list on a particle.
- L144 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L149 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query (which must exist)
- L154 _public member_ `TArray<FRigComponentKey> NoCollisionColliders;` — `UPROPERTY(meta = (Output))` — The list of colliders that this particle does not collide with

#### struct `FRigUnit_HierarchyEnableDynamicsCollisionWithParticle`  
`struct FRigUnit_HierarchyEnableDynamicsCollisionWithParticle : public FRigUnit_DynamicsBaseMutable`  
_L163-182_
- reflection: `USTRUCT(meta = (DisplayName = "Enable Dynamics Collision With Particle", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Enables collision between a particle and another particle. The collision will actually be between segments, where the segment goes from a particle top its parent (if it has one), using the radius of the particles to define a capsule. TODO Note that implementation isn't yet complete, so currently it IS only sphere-sphere.
- L167 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L172 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated (which must exist)
- L180 _public member_ `FRigComponentKey OtherDynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Other Particle Component Key"))` — The other particle to collide with (which doesn't have to exist yet). Collision will be handled between segments going from each particle to its parent (if it has one). TODO Note that implementation isn't yet complete, so currently it IS only sphere-sphere.

#### struct `FRigUnit_HierarchyDisableDynamicsCollisionWithParticle`  
`struct FRigUnit_HierarchyDisableDynamicsCollisionWithParticle : public FRigUnit_DynamicsBaseMutable`  
_L189-206_
- reflection: `USTRUCT(meta = (DisplayName = "Disable Dynamics Collision With Particle", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Disables collision between a particle and another particle by removing each key from the other's CollisionParticles list. Silent no-op for either side if the particle is missing or the key is not present in its list.
- L193 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L198 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L204 _public member_ `FRigComponentKey OtherDynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Other Particle Component Key"))` — The other particle to stop colliding with

#### struct `FRigUnit_HierarchyEnableDynamicsConfinementWithConfiner`  
`struct FRigUnit_HierarchyEnableDynamicsConfinementWithConfiner : public FRigUnit_DynamicsBaseMutable`  
_L212-228_
- reflection: `USTRUCT(meta = (DisplayName = "Enable Dynamics Confinement With Confiner", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Opts a particle in to being confined by a confiner. The confiner will keep the particle inside each of its shapes.
- L216 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L221 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated (which must exist)
- L226 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Confiner that should confine the particle (it doesn't have to exist yet)

#### struct `FRigUnit_HierarchyDisableDynamicsConfinementWithConfiner`  
`struct FRigUnit_HierarchyDisableDynamicsConfinementWithConfiner : public FRigUnit_DynamicsBaseMutable`  
_L233-249_
- reflection: `USTRUCT(meta = (DisplayName = "Disable Dynamics Confinement With Confiner", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Opts a particle out of being confined by a confiner.
- L237 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L242 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated (which must exist)
- L247 _public member_ `FRigComponentKey DynamicsConfinerComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsConfinerComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Confiner Component Key"))` — The Confiner to remove from this particle's confinement list

#### struct `FRigUnit_HierarchySetDynamicsParticleMass`  
`struct FRigUnit_HierarchySetDynamicsParticleMass : public FRigUnit_DynamicsBaseMutable`  
_L254-269_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Mass", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the mass of a Dynamics particle
- L258 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L263 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L268 _public member_ `float Mass = RigDynamicsDefaultParticleMass;` — `UPROPERTY(meta = (Input, Units = "Kilograms", ClampMin = "0.0001"))` — The mass of the Dynamics Particle

#### struct `FRigUnit_HierarchyGetDynamicsParticleMass`  
`struct FRigUnit_HierarchyGetDynamicsParticleMass : public FRigUnit_DynamicsBase`  
_L274-289_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Mass", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the mass of a Dynamics particle
- L278 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L283 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L288 _public member_ `float Mass = RigDynamicsDefaultParticleMass;` — `UPROPERTY(meta = (Output, Units = "Kilograms"))` — The mass of the Dynamics Particle

#### struct `FRigUnit_HierarchySetDynamicsParticleRadius`  
`struct FRigUnit_HierarchySetDynamicsParticleRadius : public FRigUnit_DynamicsBaseMutable`  
_L294-309_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Radius", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the radius of a Dynamics particle
- L298 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L303 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L308 _public member_ `float Radius = RigDynamicsDefaultParticleRadius;` — `UPROPERTY(meta = (Input, Units = "Centimeters", ClampMin = "0.0"))` — The radius of the Dynamics Particle, used for collision

#### struct `FRigUnit_HierarchyGetDynamicsParticleRadius`  
`struct FRigUnit_HierarchyGetDynamicsParticleRadius : public FRigUnit_DynamicsBase`  
_L314-329_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Radius", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the radius of a Dynamics particle
- L318 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L323 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L328 _public member_ `float Radius = RigDynamicsDefaultParticleRadius;` — `UPROPERTY(meta = (Output, Units = "Centimeters"))` — The radius of the Dynamics Particle, used for collision

#### struct `FRigUnit_HierarchySetDynamicsParticleMovementType`  
`struct FRigUnit_HierarchySetDynamicsParticleMovementType : public FRigUnit_DynamicsBaseMutable`  
_L334-349_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Movement Type", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the movement type of a Dynamics particle
- L338 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L343 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L348 _public member_ `ERigParticleSimulationMovementType MovementType = ERigParticleSimulationMovementType::Simulated;` — `UPROPERTY(meta = (Input))` — How the particle should move

#### struct `FRigUnit_HierarchyGetDynamicsParticleMovementType`  
`struct FRigUnit_HierarchyGetDynamicsParticleMovementType : public FRigUnit_DynamicsBase`  
_L354-369_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Movement Type", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the movement type of a Dynamics particle
- L358 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L363 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L368 _public member_ `ERigParticleSimulationMovementType MovementType = ERigParticleSimulationMovementType::Kinematic;` — `UPROPERTY(meta = (Output))` — How the particle should move

#### struct `FRigUnit_HierarchySetDynamicsParticleGravityMultiplier`  
`struct FRigUnit_HierarchySetDynamicsParticleGravityMultiplier : public FRigUnit_DynamicsBaseMutable`  
_L374-389_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Gravity Multiplier", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the gravity multiplier of a Dynamics particle
- L378 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L383 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L388 _public member_ `float GravityMultiplier = 1.0f;` — `UPROPERTY(meta = (Input))` — Scales the solver gravity

#### struct `FRigUnit_HierarchyGetDynamicsParticleGravityMultiplier`  
`struct FRigUnit_HierarchyGetDynamicsParticleGravityMultiplier : public FRigUnit_DynamicsBase`  
_L394-409_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Gravity Multiplier", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the gravity multiplier of a Dynamics particle
- L398 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L403 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L408 _public member_ `float GravityMultiplier = 0.0f;` — `UPROPERTY(meta = (Output))` — Scales the solver gravity

#### struct `FRigUnit_HierarchySetDynamicsParticleStrength`  
`struct FRigUnit_HierarchySetDynamicsParticleStrength : public FRigUnit_DynamicsBaseMutable`  
_L414-429_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Strength", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the strength of a Dynamics particle
- L418 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L423 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L428 _public member_ `float Strength = 2.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — The strength which drives towards the target (oscillation frequency)

#### struct `FRigUnit_HierarchyGetDynamicsParticleStrength`  
`struct FRigUnit_HierarchyGetDynamicsParticleStrength : public FRigUnit_DynamicsBase`  
_L434-449_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Strength", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the strength of a Dynamics particle
- L438 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L443 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L448 _public member_ `float Strength = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — The strength which drives towards the target (oscillation frequency)

#### struct `FRigUnit_HierarchySetDynamicsParticleDampingRatio`  
`struct FRigUnit_HierarchySetDynamicsParticleDampingRatio : public FRigUnit_DynamicsBaseMutable`  
_L454-469_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Damping Ratio", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the damping ratio of a Dynamics particle
- L458 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L463 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L468 _public member_ `float DampingRatio = 0.5f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — Damping ratio for the particle

#### struct `FRigUnit_HierarchyGetDynamicsParticleDampingRatio`  
`struct FRigUnit_HierarchyGetDynamicsParticleDampingRatio : public FRigUnit_DynamicsBase`  
_L474-489_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Damping Ratio", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the damping ratio of a Dynamics particle
- L478 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L483 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L488 _public member_ `float DampingRatio = 0.0f;` — `UPROPERTY(meta = (Output))` — Damping ratio for the particle

#### struct `FRigUnit_HierarchySetDynamicsParticleExtraDamping`  
`struct FRigUnit_HierarchySetDynamicsParticleExtraDamping : public FRigUnit_DynamicsBaseMutable`  
_L494-509_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Extra Damping", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the extra damping of a Dynamics particle
- L498 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L503 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L508 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — Extra damping for the particle

#### struct `FRigUnit_HierarchyGetDynamicsParticleExtraDamping`  
`struct FRigUnit_HierarchyGetDynamicsParticleExtraDamping : public FRigUnit_DynamicsBase`  
_L514-529_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Extra Damping", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the extra damping of a Dynamics particle
- L518 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L523 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L528 _public member_ `float ExtraDamping = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — Extra damping for the particle

#### struct `FRigUnit_HierarchySetDynamicsParticleDrag`  
`struct FRigUnit_HierarchySetDynamicsParticleDrag : public FRigUnit_DynamicsBaseMutable`  
_L537-552_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Drag", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the particle into "drag" mode. Writes the Drag value to ParticleProperties.Damping and forces bScaleDampingByInverseMass = true, so the effective damping rate is Drag * InvMass (heavier particles damp slower, resulting in the drag-like behaviour). Use Set Damping instead for a mass-independent rate.
- L541 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L546 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L551 _public member_ `float Drag = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — Air/ether drag coefficient (1/time). Effective coupling rate = Drag * InvMass.

#### struct `FRigUnit_HierarchyGetDynamicsParticleDrag`  
`struct FRigUnit_HierarchyGetDynamicsParticleDrag : public FRigUnit_DynamicsBase`  
_L559-574_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Drag", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Reads the particle's air/ether drag value, converting from Damping if the particle is in mass-independent mode (Drag = Damping * Mass) so the output always carries the drag-mode interpretation regardless of how the particle was authored.
- L563 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L568 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L573 _public member_ `float Drag = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — Air/ether drag coefficient (1/time). Effective coupling rate = Drag * InvMass.

#### struct `FRigUnit_HierarchySetDynamicsParticleDamping`  
`struct FRigUnit_HierarchySetDynamicsParticleDamping : public FRigUnit_DynamicsBaseMutable`  
_L582-597_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Damping", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the particle into "damping" mode: writes the Damping value to ParticleProperties.Damping and forces bScaleDampingByInverseMass = false, so the effective coupling rate is Damping directly (mass-independent - every particle has the same relaxation timescale). Use Set Drag instead for the drag-like, mass-scaled behaviour.
- L586 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L591 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L596 _public member_ `float Damping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — Air/ether damping rate (1/time). Effective coupling rate = Damping, regardless of mass.

#### struct `FRigUnit_HierarchyGetDynamicsParticleDamping`  
`struct FRigUnit_HierarchyGetDynamicsParticleDamping : public FRigUnit_DynamicsBase`  
_L604-619_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Damping", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Reads the particle's air/ether damping value, converting from Drag if the particle is in drag mode (Damping = Damping_stored / Mass) so the output always carries the damping-mode interpretation regardless of how the particle was authored.
- L608 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L613 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L618 _public member_ `float Damping = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — Air/ether damping rate (1/time). Effective coupling rate = Damping, regardless of mass.

#### struct `FRigUnit_HierarchySetDynamicsParticleTargetVelocityInfluence`  
`struct FRigUnit_HierarchySetDynamicsParticleTargetVelocityInfluence : public FRigUnit_DynamicsBaseMutable`  
_L624-639_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Target Velocity Influence", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the target velocity influence of a Dynamics particle
- L628 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L633 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L638 _public member_ `float TargetVelocityInfluence = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — If 1 the target's velocity will be used for damping, if 0 damping is in sim space

#### struct `FRigUnit_HierarchyGetDynamicsParticleTargetVelocityInfluence`  
`struct FRigUnit_HierarchyGetDynamicsParticleTargetVelocityInfluence : public FRigUnit_DynamicsBase`  
_L644-659_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Target Velocity Influence", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the target velocity influence of a Dynamics particle
- L648 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L653 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L658 _public member_ `float TargetVelocityInfluence = 0.0f;` — `UPROPERTY(meta = (Output))` — If 1 the target's velocity will be used for damping, if 0 damping is in sim space

#### struct `FRigUnit_HierarchySetDynamicsParticleTargetMode`  
`struct FRigUnit_HierarchySetDynamicsParticleTargetMode : public FRigUnit_DynamicsBaseMutable`  
_L664-679_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Target Mode", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the target mode of a Dynamics particle
- L668 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L673 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L678 _public member_ `float TargetMode = 0.5f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — 0 = SimSpace, 1 = directional, values between blend the two modes

#### struct `FRigUnit_HierarchyGetDynamicsParticleTargetMode`  
`struct FRigUnit_HierarchyGetDynamicsParticleTargetMode : public FRigUnit_DynamicsBase`  
_L684-699_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Target Mode", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the target mode of a Dynamics particle
- L688 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L693 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L698 _public member_ `float TargetMode = 0.5f;` — `UPROPERTY(meta = (Output))` — 0 = SimSpace, 1 = directional, values between blend the two modes

#### struct `FRigUnit_HierarchySetDynamicsParticleAngleLimit`  
`struct FRigUnit_HierarchySetDynamicsParticleAngleLimit : public FRigUnit_DynamicsBaseMutable`  
_L704-721_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Angle Limit", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the angle limit of a Dynamics particle
- L708 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L713 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L720 _public member_ `float AngleLimit = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Degrees"))` — This applies a soft constraint to make this particle align with the target direction from its parent, to within this angle (in degrees). This effectively gives us a limit on the deviation from the target pose.

#### struct `FRigUnit_HierarchyGetDynamicsParticleAngleLimit`  
`struct FRigUnit_HierarchyGetDynamicsParticleAngleLimit : public FRigUnit_DynamicsBase`  
_L726-743_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Angle Limit", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the angle limit of a Dynamics particle
- L730 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L735 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L742 _public member_ `float AngleLimit = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Degrees"))` — This applies a soft constraint to make this particle align with the target direction from its parent, to within this angle (in degrees). This effectively gives us a limit on the deviation from the target pose.

#### struct `FRigUnit_HierarchySetDynamicsParticleAngleLimitStrength`  
`struct FRigUnit_HierarchySetDynamicsParticleAngleLimitStrength : public FRigUnit_DynamicsBaseMutable`  
_L748-765_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Angle Limit Strength", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the angle limit strength of a Dynamics particle
- L752 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L757 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L764 _public member_ `float AngleLimitStrength = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Hertz"))` — The strength of the angle limit constraint (oscillation frequency). High values impose the limit more rigidly, low values allow soft/springy deviation before settling. Zero disables the angle limit.

#### struct `FRigUnit_HierarchyGetDynamicsParticleAngleLimitStrength`  
`struct FRigUnit_HierarchyGetDynamicsParticleAngleLimitStrength : public FRigUnit_DynamicsBase`  
_L770-787_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Angle Limit Strength", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the angle limit strength of a Dynamics particle
- L774 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L779 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L786 _public member_ `float AngleLimitStrength = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Hertz"))` — The strength of the angle limit constraint (oscillation frequency). High values impose the limit more rigidly, low values allow soft/springy deviation before settling. Zero disables the angle limit.

#### struct `FRigUnit_HierarchySetDynamicsParticleCollideWithColliders`  
`struct FRigUnit_HierarchySetDynamicsParticleCollideWithColliders : public FRigUnit_DynamicsBaseMutable`  
_L792-807_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Collide With Colliders", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets whether a Dynamics particle participates in collider contacts
- L796 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L801 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L806 _public member_ `bool bCollideWithColliders = true;` — `UPROPERTY(meta = (Input))` — If false, this particle ignores all colliders regardless of NoCollisionColliders.

#### struct `FRigUnit_HierarchyGetDynamicsParticleCollideWithColliders`  
`struct FRigUnit_HierarchyGetDynamicsParticleCollideWithColliders : public FRigUnit_DynamicsBase`  
_L812-827_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Collide With Colliders", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets whether a Dynamics particle participates in collider contacts
- L816 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L821 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L826 _public member_ `bool bCollideWithColliders = true;` — `UPROPERTY(meta = (Output))` — If false, this particle ignores all colliders regardless of NoCollisionColliders.

#### struct `FRigUnit_HierarchySetDynamicsParticleAccelerationMode`  
`struct FRigUnit_HierarchySetDynamicsParticleAccelerationMode : public FRigUnit_DynamicsBaseMutable`  
_L834-849_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Acceleration Mode", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets whether the particle's target drive is interpreted in acceleration mode (mass-independent natural frequency) or force mode (heavier particles oscillate more slowly). Affects target tracking only - the per-particle angle limit is always acceleration-mode.
- L838 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L843 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L848 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(meta = (Input))` — True (default) for mass-independent natural frequency; false for a true force-mode spring.

#### struct `FRigUnit_HierarchyGetDynamicsParticleAccelerationMode`  
`struct FRigUnit_HierarchyGetDynamicsParticleAccelerationMode : public FRigUnit_DynamicsBase`  
_L854-869_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Acceleration Mode", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the acceleration-mode flag of a Dynamics particle.
- L858 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L863 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L868 _public member_ `bool bAccelerationMode = true;` — `UPROPERTY(meta = (Output))` — True for mass-independent natural frequency; false for a true force-mode spring.

#### struct `FRigUnit_HierarchySetDynamicsParticleScaleDampingByInverseMass`  
`struct FRigUnit_HierarchySetDynamicsParticleScaleDampingByInverseMass : public FRigUnit_DynamicsBaseMutable`  
_L874-889_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Particle Scale Damping By Inverse Mass", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets whether the particle's Damping is scaled by inverse mass (drag-like) or mass-independent.
- L878 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L883 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to be updated
- L888 _public member_ `bool bScaleDampingByInverseMass = false;` — `UPROPERTY(meta = (Input))` — True: Damping is divided by mass (drag-like). False (default): Damping is mass-independent.

#### struct `FRigUnit_HierarchyGetDynamicsParticleScaleDampingByInverseMass`  
`struct FRigUnit_HierarchyGetDynamicsParticleScaleDampingByInverseMass : public FRigUnit_DynamicsBase`  
_L894-909_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Particle Scale Damping By Inverse Mass", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the scale-damping-by-inverse-mass flag of a Dynamics particle.
- L898 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L903 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to query
- L908 _public member_ `bool bScaleDampingByInverseMass = false;` — `UPROPERTY(meta = (Output))` — True: Damping is divided by mass (drag-like). False: Damping is mass-independent.

#### struct `FRigUnit_HierarchyAddDynamicsParticleForce`  
`struct FRigUnit_HierarchyAddDynamicsParticleForce : public FRigUnit_DynamicsBaseMutable`  
_L917-942_
- reflection: `USTRUCT(meta = (DisplayName = "Add Dynamics Particle Force", Keywords = "Force,Impulse,Acceleration,Velocity", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Specifies a force on a Dynamics particle to be applied on the next simulation step. Multiple calls within the same frame accumulate. Forces queued during a pass-through frame (the next StepDynamicsSolver has Alpha <= 0) are discarded. Particles have no orientation, so there is no torque or location-offset variant.
- L921 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L926 _public member_ `FRigComponentKey DynamicsParticleComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigDynamicsParticleComponent::GetDefaultName());` — `UPROPERTY(meta = (Input, DisplayName = "Particle Component Key"))` — The Dynamics Particle to apply the force to.
- L931 _public member_ `FVector Force = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Direction and magnitude of the force, in the frame given by Space. Units depend on Type.
- L936 _public member_ `EPhysicsControlSpace Space = EPhysicsControlSpace::World;` — `UPROPERTY(meta = (Input))` — Frame the Force is expressed in. Body means the space of the particle's owning bone in the input pose.
- L941 _public member_ `EPhysicsControlForceType Type = EPhysicsControlForceType::Force;` — `UPROPERTY(meta = (Input))` — How Force is interpreted: Force (kg cm/s^2), Acceleration (cm/s^2, mass-independent), Impulse (kg cm/s, one-shot momentum change), VelocityChange (cm/s, one-shot, mass-independent).

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsSimulationSpace.h` (Public)


#### struct `FRigDynamicsSimulationSpaceState`  
`struct FRigDynamicsSimulationSpaceState`  
_L15-123_
- desc: This represents the simulation space, specified in world space. It will be associated with functions that allow conversion between the spaces.
- L23 _public prototype_ `void Update( const FRigDynamicsTeleportDetectionSettings& TeleportDetection, const FTransform& InComponentTM, const FTransform& InSimulationSpaceTM, float DeltaTime);` — If DeltaTime > 0 then this does a full update, calculating new velocities etc. If DeltaTime <= 0 then this just updates the current position and orientation - no changes to velocity etc. TeleportDetection is used to detect discontinuous simulation-space movement; when one is detected the newly-computed velocities/accelerations are zeroed and UpdatesSinceReset is reset so the following frame's acceleration is also suppressed via bAccelerationsValid.
- L30 _public prototype_ `void Reset(const FTransform& InComponentTM, const FTransform& InSimulationSpaceTM);` — This sets the position/orientation, and resets everything else.
- L35 _public prototype_ `RigParticleSimulation::FSimulationSpaceMotion CalculateMotion( const FRigDynamicsSimulationSpaceMotion& SpaceMotion, double AbsoluteTime) const;` — Calculates the simulation space motion data from the current state and SpaceMotion (which holds the conditioning, the inertial-force amount, and the nested air/ether drag settings), ready to be passed to RigParticleSimulation::Simulate.
- L41 _public prototype_ `RigParticleSimulation::FSimVector ConvertComponentSpacePositionToSimSpace(const FVector& ComponentSpacePosition) const;` — Convert a position from component space (where the hierarchy lives) into simulation space (where particles live). Identity when SimulationSpace=Component.
- L44 _public prototype_ `FVector ConvertSimSpacePositionToComponentSpace(const RigParticleSimulation::FSimVector& SimSpacePosition) const;` — Convert a position from simulation space back to component space.
- L47 _public prototype_ `RigParticleSimulation::FSimTransform ConvertComponentSpaceTransformToSimSpace(const FTransform& ComponentSpaceTransform) const;` — Convert a transform from component space into simulation space (rotation + translation, no scale).
- L50 _public prototype_ `FTransform ConvertSimSpaceTransformToComponentSpace(const RigParticleSimulation::FSimTransform& SimSpaceTransform) const;` — Convert a transform from simulation space back to component space.
- L53 _public prototype_ `RigParticleSimulation::FSimVector ConvertWorldVectorToSimSpace(const FVector& WorldVector) const;` — Convert a direction/velocity vector from world space into simulation space.
- L56 _public prototype_ `RigParticleSimulation::FSimVector ConvertComponentSpaceVectorToSimSpace(const FVector& ComponentSpaceVector) const;` — Convert a direction/velocity vector from component space into simulation space.
- L59 _public prototype_ `RigParticleSimulation::FSimTransform ConvertWorldSpaceTransformToSimSpace(const FTransform& WorldSpaceTransform) const;` — Convert a transform from world space into simulation space (rotation + translation, no scale).
- L63 _public function_ `const FTransform& GetComponentTM() const` — World-space transform of the rig's component (component-to-world). Tracked by the most recent Update() / Reset() call.
- L67 _public function_ `const FVector& GetLinearVelocity() const` — World-space linear velocity of the simulation space as computed by the most recent Update(). Zero on a frame where a teleport was detected.
- L70 _public function_ `const FVector& GetAngularVelocity() const` — World-space angular velocity (rad/s) of the simulation space as computed by the most recent Update().
- L73 _public function_ `const FVector& GetLinearAcceleration() const` — World-space linear acceleration of the simulation space as computed by the most recent Update().
- L76 _public function_ `const FVector& GetAngularAcceleration() const` — World-space angular acceleration (rad/s/s) of the simulation space as computed by the most recent Update().
- L81 _public function_ `bool WasTeleportDetectedInLastUpdate() const` — True if the most recent Update() call (with DeltaTime > 0) detected a teleport via the thresholds on FRigDynamicsTeleportDetectionSettings. Updates with DeltaTime <= 0 leave this value unchanged. Reset() clears it.
- L86 _private prototype_ `void RecomputeCompositeTransforms();` — Called when the component/simulation TMs have been updated
- L89 _private member_ `FTransform ComponentTM;` — The world-space component (owner of the simulation) transform
- L92 _private member_ `FVector LinearVelocity = FVector::ZeroVector;` — World-space linear velocity of the simulation space
- L94 _private member_ `FVector AngularVelocity = FVector::ZeroVector;` — World-space angular velocity of the simulation space
- L97 _private member_ `FVector LinearAcceleration = FVector::ZeroVector;` — World-space linear acceleration of the simulation space
- L99 _private member_ `FVector AngularAcceleration = FVector::ZeroVector;` — World-space angular acceleration of the simulation space
- L102 _private member_ `FTransform SimulationSpaceTM;` — The world-space simulation space TM
- L103 _private member_ `FTransform PrevSimulationSpaceTM;`
- L104 _private member_ `FTransform PrevPrevSimulationSpaceTM;`
- L108 _private member_ `FTransform ComponentToSimSpaceTM;` — Precomputed composite transforms so that each coordinate conversion is a single transform operation instead of two. Recomputed whenever ComponentTM or SimulationSpaceTM changes.
- L109 _private member_ `FTransform SimToComponentSpaceTM;`
- L112 _private member_ `float DeltaTime = 0.0f;` — The time between SimulationSpaceTM and PrevSimulationSpaceTM
- L114 _private member_ `float PrevDeltaTime = 0.0f;` — The time between PrevSimulationSpaceTM and PrevPrevSimulationSpaceTM
- L119 _private member_ `int64 UpdatesSinceReset = 0;` — When we are reset, then the position (and orientation) is correct On the next update (with a non-zero delta time), the velocity is correct (acceleration will be zero) On the next update, the acceleration will be correct
- L122 _private member_ `bool bTeleportDetectedInLastUpdate = false;` — Set by Update() when teleport thresholds are tripped; updated only when DeltaTime > 0.
- L130 _function_ `inline RigParticleSimulation::FSimVector FRigDynamicsSimulationSpaceState::ConvertComponentSpacePositionToSimSpace( const FVector& ComponentSpacePosition) const`
- L138 _function_ `inline FVector FRigDynamicsSimulationSpaceState::ConvertSimSpacePositionToComponentSpace( const RigParticleSimulation::FSimVector& SimSpacePosition) const`
- L145 _function_ `inline RigParticleSimulation::FSimTransform FRigDynamicsSimulationSpaceState::ConvertComponentSpaceTransformToSimSpace( const FTransform& ComponentSpaceTransform) const`
- L154 _function_ `inline FTransform FRigDynamicsSimulationSpaceState::ConvertSimSpaceTransformToComponentSpace( const RigParticleSimulation::FSimTransform& SimSpaceTransform) const`
- L163 _function_ `inline RigParticleSimulation::FSimVector FRigDynamicsSimulationSpaceState::ConvertWorldVectorToSimSpace( const FVector& WorldVector) const`
- L171 _function_ `inline RigParticleSimulation::FSimVector FRigDynamicsSimulationSpaceState::ConvertComponentSpaceVectorToSimSpace( const FVector& ComponentSpaceVector) const`
- L179 _function_ `inline RigParticleSimulation::FSimTransform FRigDynamicsSimulationSpaceState::ConvertWorldSpaceTransformToSimSpace( const FTransform& WorldSpaceTransform) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsSolverComponent.h` (Public)


#### struct `FRigDynamicsSolverComponent`  
`struct FRigDynamicsSolverComponent : public FRigBaseComponent`  
_L21-87_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L25 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigDynamicsSolverComponent)`
- L36 _public member_ `TArray<FRigComponentKey> Colliders;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Components)` — Collision shapes attached to bones in the hierarchy
- L40 _public member_ `TArray<FRigComponentKey> Constraints;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Components)` — Constraints apply forces to pairs of particles to maintain a target distance
- L44 _public member_ `TArray<FRigComponentKey> ConeLimits;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Components)` — Cone limits apply forces to triples of particles to limit the angle between them
- L49 _public member_ `TArray<FRigComponentKey> Confiners;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Components)` — Confinement shapes attached to bones in the hierarchy. Particles that opt in to a confiner will be kept inside its shapes.
- L52 _public member_ `FRigDynamicsSolverSettings Settings;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Solver)`
- L57 _public member_ `FRigDynamicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Solver)` — Simulation-space motion conditioning + the two consumers (inertial pseudo-forces and drag) nested inside it. The conditioned velocities/accelerations feed both consumers.
- L61 _public member_ `FRigDynamicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Solver)` — Teleport-detection thresholds. Independent of SpaceMotion - these read raw deltas.
- L63 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L64 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L66 _public function_ `virtual FName GetDefaultComponentName() const override`
- L67 _public function_ `static FName GetDefaultName()`
- L70 _public prototype_ `FRigDynamicsSolver* GetDynamicsSolver() const;` — This will make the internally owned solver if necessary, and return it
- L73 _protected prototype_ `void Serialize(FArchive& Ar);`
- L86 _private member_ `mutable TSharedPtr<FRigDynamicsSolver> DynamicsSolverPtr;` — We use a TSharedPtr here in anticipation of supporting world collisions (see Control Rig Physics). We make it mutable so that GetDynamicsSolver can be const - in practice the user shouldn't have to worry. Finally, UE's reflection system wants to be able to use the assignment operator. If it wasn't for that, we could just delete the copy operator etc and prevent duplicates containing a pointer to the same DynamicsSolver. In practice, this won't ever happen for a "live" component, so we're OK.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigDynamicsSolverExecution.h` (Public)


#### struct `FRigUnit_SpawnDynamicsSolver`  
`struct FRigUnit_SpawnDynamicsSolver : public FRigUnit_DynamicsBaseMutable`  
_L24-61_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Solver", Keywords = "Add,Construction,Create,New,Simulation", Varying, Deprecated = "5.8"))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Spawns a new dynamics solver as a component on the owner element. Note: This node only runs as part of the construction event. Deprecated in favour of FRigUnit_SpawnDynamicsSolver1, which exposes the new SpaceMotion + TeleportDetection input pins separately. Existing graphs continue to work - the deprecated Execute body routes the legacy SimulationSpaceSettings into the new component members via ConvertLegacyDynamicsSimulationSpaceSettings; right-clicking the deprecated node offers a one-click upgrade to the new node via GetUpgradeInfo.
- L28 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L31 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`
- L36 _public member_ `FRigElementKey Owner = FRigElementKey(FName(TEXT("Root")), ERigElementType::Bo` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L42 _public member_ `FName SolverComponentName = FRigDynamicsSolverComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the new solver component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsSolverComponentKey to find the name that was actually assigned.
- L46 _public member_ `FRigDynamicsSolverSettings Settings;` — `UPROPERTY(meta = (Input, DisplayName = "Solver Settings"))` — Solver settings
- L51 _public member_ `FRigDynamicsSimulationSpaceSettings SimulationSpaceSettings;` — `UPROPERTY(meta = (Input))` — Legacy combined simulation-space settings - now split into SpaceMotion + TeleportDetection on the replacement unit.
- L56 _public member_ `FRigDynamicsSimulationDragSettings DragSettings;` — `UPROPERTY(meta = (Input))` — Air/ether drag settings (drag multipliers, external air/ether velocity, turbulence). On the replacement unit these live nested inside SpaceMotion.Drag.
- L60 _public member_ `FRigComponentKey DynamicsSolverComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Solver Component Key"))` — The solver component key that was created

#### struct `FRigUnit_SpawnDynamicsSolver1`  
`struct FRigUnit_SpawnDynamicsSolver1 : public FRigUnit_DynamicsBaseMutable`  
_L67-104_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Dynamics Solver", Keywords = "Add,Construction,Create,New,Simulation", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Spawns a new dynamics solver as a component on the owner element. Note: This node only runs as part of the construction event.
- L71 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L76 _public member_ `FRigElementKey Owner = FRigElementKey(FName(TEXT("Root")), ERigElementType::Bo` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L82 _public member_ `FName SolverComponentName = FRigDynamicsSolverComponent::GetDefaultName();` — `UPROPERTY(meta = (Input))` — The name to give the new solver component. Only used as a starting point - if another component with this name already exists on the owner element, the hierarchy will append a unique suffix. Read DynamicsSolverComponentKey to find the name that was actually assigned.
- L86 _public member_ `FRigDynamicsSolverSettings Settings;` — `UPROPERTY(meta = (Input))` — Solver settings
- L93 _public member_ `FRigDynamicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(meta = (Input))` — Teleport-detection thresholds based on the movement of the simulation space. These operate on raw deltas in the simulation-space transform (not on the animation pose itself). When any threshold is crossed the solver zeroes velocities/accelerations for the frame without resetting the simulation pose.
- L99 _public member_ `FRigDynamicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(meta = (Input))` — How the simulation-space linear/angular velocity and acceleration are conditioned (vertical scale + clamps) before being passed to the inertial pseudo-forces and the air/ether drag effects. These do not affect teleport detection.
- L103 _public member_ `FRigComponentKey DynamicsSolverComponentKey;` — `UPROPERTY(meta = (Output, DisplayName = "Solver Component Key"))` — The solver component key that was created

#### struct `FRigUnit_GetDynamicsSolverExists`  
`struct FRigUnit_GetDynamicsSolverExists : public FRigUnit_DynamicsBase`  
_L109-124_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Exists", Keywords = "Query,Simulation"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Indicates whether the component exists and is a Dynamics Solver
- L113 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L118 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The component key to check
- L123 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Dynamics Solver

#### struct `FRigUnit_InstantiateDynamics`  
`struct FRigUnit_InstantiateDynamics : public FRigUnit_DynamicsBaseMutable`  
_L132-143_
- reflection: `USTRUCT(meta = (DisplayName = "Instantiate dynamics"))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Instantiates all the objects in the dynamics world. Some properties can't be modified after this happens. Note that it will happen automatically during the first simulation step if it hasn't been explicitly requested. Explicit instantiation allows the timing to be controlled, as allocations etc may cause some delays.
- L136 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L141 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The solver that should be instantiated

#### struct `FRigUnit_StepDynamicsSolver`  
`struct FRigUnit_StepDynamicsSolver : public FRigUnit_DynamicsBaseMutable`  
_L149-193_
- reflection: `USTRUCT(meta = (DisplayName = "Step Dynamics Solver", Keywords = "Simulate"))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Steps the dynamics solver
- L153 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L158 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The physics solver that should be stepped
- L164 _public member_ `float DeltaTimeOverride = 0.0f;` — `UPROPERTY(meta = (Input, Units = "Seconds"))` — If this is zero, then the execute context time will be used. If this is positive then it will override the delta time. A negative value will prevent the solver from stepping.
- L171 _public member_ `float SimulationSpaceDeltaTimeOverride = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Seconds"))` — If this is zero, then the simulation delta time will be used for evaluating movement of the simulation space. If this is positive then it will override. This may be needed if the component movement is being done in parallel, in which case you might need to pass in the previous time delta here.
- L176 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation is combined with the input bone. This currently happens in component space. When alpha <= zero, the simulation is bypassed entirely (pass-through).
- L183 _public member_ `bool bTrackVelocitiesDuringPassThrough = true;` — `UPROPERTY(meta = (Input))` — When true and Alpha is zero, the solver tracks particle positions each frame so that velocities are valid when Alpha increases (smooth resume). This has a small cost. When false and Alpha is zero, the pass-through is near-zero cost but the simulation re-initializes with zero velocity when Alpha increases.
- L187 _public member_ `FRigDynamicsVisualizationSettings VisualizationSettings;` — `UPROPERTY(meta = (Input))` — Settings that specify how the solver state should be visualized during/after the step
- L192 _public member_ `FCachedRigComponent CachedSolverComponent;` — `UPROPERTY()` — Doing a lookup to get the SolverComponent from the key is slow, so cache this. If it matches DynamicsSolverComponentKey we can use the cached value.

#### struct `FRigUnit_HierarchySetDynamicsSolverSettings`  
`struct FRigUnit_HierarchySetDynamicsSolverSettings : public FRigUnit_DynamicsBaseMutable`  
_L198-213_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Settings", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the complete settings of a Dynamics solver
- L202 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L207 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L212 _public member_ `FRigDynamicsSolverSettings Settings;` — `UPROPERTY(meta = (Input))` — The solver settings

#### struct `FRigUnit_HierarchyGetDynamicsSolverSettings`  
`struct FRigUnit_HierarchyGetDynamicsSolverSettings : public FRigUnit_DynamicsBase`  
_L218-233_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Settings", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the complete settings of a Dynamics solver
- L222 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L227 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L232 _public member_ `FRigDynamicsSolverSettings Settings;` — `UPROPERTY(meta = (Output))` — The solver settings

#### struct `FRigUnit_HierarchySetDynamicsSolverGravity`  
`struct FRigUnit_HierarchySetDynamicsSolverGravity : public FRigUnit_DynamicsBaseMutable`  
_L238-253_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Gravity", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the gravity of a Dynamics solver
- L242 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L247 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L252 _public member_ `FVector Gravity = FVector(0.0f, 0.0f, -981.0f);` — `UPROPERTY(meta = (Input))` — Gravity in world space, can be scaled per particle

#### struct `FRigUnit_HierarchyGetDynamicsSolverGravity`  
`struct FRigUnit_HierarchyGetDynamicsSolverGravity : public FRigUnit_DynamicsBase`  
_L258-273_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Gravity", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the gravity of a Dynamics solver
- L262 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L267 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L272 _public member_ `FVector Gravity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Gravity in world space, can be scaled per particle

#### struct `FRigUnit_HierarchySetDynamicsSolverMaxTimeStep`  
`struct FRigUnit_HierarchySetDynamicsSolverMaxTimeStep : public FRigUnit_DynamicsBaseMutable`  
_L278-293_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Max Time Step", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the max time step of a Dynamics solver
- L282 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L287 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L292 _public member_ `float MaxTimeStep = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", Units = "Seconds"))` — The maximum timestep of any step

#### struct `FRigUnit_HierarchyGetDynamicsSolverMaxTimeStep`  
`struct FRigUnit_HierarchyGetDynamicsSolverMaxTimeStep : public FRigUnit_DynamicsBase`  
_L298-313_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Max Time Step", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the max time step of a Dynamics solver
- L302 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L307 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L312 _public member_ `float MaxTimeStep = 0.0f;` — `UPROPERTY(meta = (Output, Units = "Seconds"))` — The maximum timestep of any step

#### struct `FRigUnit_HierarchySetDynamicsSolverMaxNumSteps`  
`struct FRigUnit_HierarchySetDynamicsSolverMaxNumSteps : public FRigUnit_DynamicsBaseMutable`  
_L318-333_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Max Num Steps", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the max number of steps of a Dynamics solver
- L322 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L327 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L332 _public member_ `int32 MaxNumSteps = 1;` — `UPROPERTY(meta = (Input, ClampMin = "0"))` — The maximum number of steps per update

#### struct `FRigUnit_HierarchyGetDynamicsSolverMaxNumSteps`  
`struct FRigUnit_HierarchyGetDynamicsSolverMaxNumSteps : public FRigUnit_DynamicsBase`  
_L338-353_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Max Num Steps", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the max number of steps of a Dynamics solver
- L342 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L347 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L352 _public member_ `int32 MaxNumSteps = 0;` — `UPROPERTY(meta = (Output))` — The maximum number of steps per update

#### struct `FRigUnit_HierarchySetDynamicsSolverNumIterations`  
`struct FRigUnit_HierarchySetDynamicsSolverNumIterations : public FRigUnit_DynamicsBaseMutable`  
_L358-373_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Num Iterations", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the number of iterations of a Dynamics solver
- L362 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L367 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L372 _public member_ `int32 NumIterations = 1;` — `UPROPERTY(meta = (Input, ClampMin = "0"))` — Total number of iterations including particle target tracking

#### struct `FRigUnit_HierarchyGetDynamicsSolverNumIterations`  
`struct FRigUnit_HierarchyGetDynamicsSolverNumIterations : public FRigUnit_DynamicsBase`  
_L378-393_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Num Iterations", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the number of iterations of a Dynamics solver
- L382 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L387 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L392 _public member_ `int32 NumIterations = 0;` — `UPROPERTY(meta = (Output))` — Total number of iterations including particle target tracking

#### struct `FRigUnit_HierarchySetDynamicsSolverNumConstraintSubIterations`  
`struct FRigUnit_HierarchySetDynamicsSolverNumConstraintSubIterations : public FRigUnit_DynamicsBaseMutable`  
_L398-413_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Num Constraint Sub-Iterations", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the number of constraint sub-iterations of a Dynamics solver
- L402 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L407 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L412 _public member_ `int32 NumConstraintSubIterations = 1;` — `UPROPERTY(meta = (Input, ClampMin = "0"))` — Number of constraint (distance and collision) sub-iterations

#### struct `FRigUnit_HierarchyGetDynamicsSolverNumConstraintSubIterations`  
`struct FRigUnit_HierarchyGetDynamicsSolverNumConstraintSubIterations : public FRigUnit_DynamicsBase`  
_L418-433_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Num Constraint Sub-Iterations", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the number of constraint sub-iterations of a Dynamics solver
- L422 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L427 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L432 _public member_ `int32 NumConstraintSubIterations = 0;` — `UPROPERTY(meta = (Output))` — Number of constraint (distance and collision) sub-iterations

#### struct `FRigUnit_HierarchySetDynamicsSolverSpaceMotion`  
`struct FRigUnit_HierarchySetDynamicsSolverSpaceMotion : public FRigUnit_DynamicsBaseMutable`  
_L439-454_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Space Motion", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the simulation-space motion settings (conditioning + nested inertial-force / drag) of a Dynamics solver.
- L443 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L448 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L453 _public member_ `FRigDynamicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(meta = (Input))` — The simulation-space motion conditioning, including the nested inertial-force gain and drag settings.

#### struct `FRigUnit_HierarchyGetDynamicsSolverSpaceMotion`  
`struct FRigUnit_HierarchyGetDynamicsSolverSpaceMotion : public FRigUnit_DynamicsBase`  
_L459-474_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Space Motion", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the simulation-space motion settings of a Dynamics solver.
- L463 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L468 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L473 _public member_ `FRigDynamicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(meta = (Output))` — The simulation-space motion conditioning, including the nested inertial-force gain and drag settings.

#### struct `FRigUnit_HierarchySetDynamicsSolverTeleportDetection`  
`struct FRigUnit_HierarchySetDynamicsSolverTeleportDetection : public FRigUnit_DynamicsBaseMutable`  
_L479-494_
- reflection: `USTRUCT(meta = (DisplayName = "Set Dynamics Solver Teleport Detection", Varying))`
- inherits: `FRigUnit_DynamicsBaseMutable`
- desc: Sets the teleport-detection thresholds of a Dynamics solver.
- L483 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L488 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to be updated
- L493 _public member_ `FRigDynamicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(meta = (Input))` — Per-channel teleport-detection thresholds applied to raw simulation-space deltas.

#### struct `FRigUnit_HierarchyGetDynamicsSolverTeleportDetection`  
`struct FRigUnit_HierarchyGetDynamicsSolverTeleportDetection : public FRigUnit_DynamicsBase`  
_L499-514_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Teleport Detection", Varying))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Gets the teleport-detection thresholds of a Dynamics solver.
- L503 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L508 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The Dynamics Solver to query
- L513 _public member_ `FRigDynamicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(meta = (Output))` — Per-channel teleport-detection thresholds applied to raw simulation-space deltas.

#### struct `FRigUnit_GetDynamicsSolverData`  
`struct FRigUnit_GetDynamicsSolverData : public FRigUnit_DynamicsBase`  
_L520-566_
- reflection: `USTRUCT(meta = (DisplayName = "Get Dynamics Solver Data", Keywords = "Debug"))`
- inherits: `FRigUnit_DynamicsBase`
- desc: Retrieves the data that were generated during the simulation step, so the values returned will relate to the previous update if the solver has not yet been stepped.
- L524 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L529 _public member_ `FRigComponentKey DynamicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigDynamicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input, DisplayName = "Solver Component Key"))` — The solver from which we'll get these data
- L534 _public member_ `FVector SimulationSpaceLinearVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The linear velocity of the simulation space, in world space (cm/s).
- L538 _public member_ `FVector SimulationSpaceAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The angular velocity of the simulation space, in world space (deg/s).
- L542 _public member_ `FVector SimulationSpaceLinearAcceleration = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The linear acceleration of the simulation space, in world space (cm/s/s).
- L546 _public member_ `FVector SimulationSpaceAngularAcceleration = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The angular acceleration of the simulation space, in world space (deg/s/s).
- L550 _public member_ `bool bTeleportDetected = false;` — `UPROPERTY(meta = (Output))` — Whether or not a teleport was detected
- L555 _public member_ `bool bKinematicSpeedResetTriggered = false;` — `UPROPERTY(meta = (Output))` — True if the most recent step reset all particle velocities because a kinematic particle's sim-space target speed exceeded KinematicSpeedThresholdForReset.
- L560 _public member_ `bool bPositionResetTriggered = false;` — `UPROPERTY(meta = (Output))` — True if the most recent step snapped the simulation back to the animation pose because a particle's sim-space distance from the origin exceeded PositionThresholdForReset.
- L565 _public member_ `bool bEvaluationIntervalResetTriggered = false;` — `UPROPERTY(meta = (Output))` — True if the most recent step snapped the simulation back to the animation pose because the interval between successive evaluations exceeded EvaluationIntervalThresholdForReset.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamics/Public/RigParticleSimulation.h` (Public)


#### enum `ERigParticleSimulationMovementType`  
`enum class ERigParticleSimulationMovementType : uint8`  
_L25-31_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Kinematic` — Kinematic means that the particle will track animation
- L30 _public enumerator_ `Simulated` — Simulated means that the particle will be controlled by dynamics

#### enum `ERigParticleSimulationConstraintType`  
`enum class ERigParticleSimulationConstraintType : uint8`  
_L36-42_
- reflection: `UENUM(BlueprintType)`
- desc: TODO support min, max and ranged length constraints
- L39 _public enumerator_ `Hard` — The target distance will be enforced as hard as possible
- L41 _public enumerator_ `Soft` — The target distance will be enforced softly, based on the strengths

#### struct `RigParticleSimulation::FParticleInfo`  
`struct FParticleInfo`  
_L70-101_
- desc: We have an "Info" structure that accompanies the simulation structure. The Info contains data that is "user-facing" (the user is control rig), and data that is helpful for updating the simulation structures.
- L73 _public member_ `int32 ParentParticleIndex = INDEX_NONE;` — Index into the Particles/ParticleInfos arrays to retrieve the parent particle
- L74 _public member_ `int32 NumChildren = 0;`
- L79 _public member_ `bool bParentParticleIsDirectParent = false;` — True when the parent particle's bone is the direct skeleton parent of this particle's bone (no intermediate bones skipped). Allows computing child global position from parent transform + child local.
- L82 _public member_ `FSimVector PreviousTargetPosition = FSimVector::ZeroVector;` — The previous/current update targets
- L83 _public member_ `FSimVector TargetPosition = FSimVector::ZeroVector;`
- L84 _public member_ `FSimVector PreviousTargetVelocity = FSimVector::ZeroVector;`
- L85 _public member_ `FSimVector TargetVelocity = FSimVector::ZeroVector;`
- L88 _public member_ `FSimVector TargetDirectionFromParent = FSimVector::ZeroVector;` — Normalized direction from parent particle to this particle in the target/animation pose
- L89 _public member_ `FSimVector PreviousTargetDirectionFromParent = FSimVector::ZeroVector;`
- L91 _public member_ `float GravityMultiplier = 1.0f;`
- L92 _public member_ `FSimVector ExternalForce = FSimVector::ZeroVector;`
- L93 _public member_ `ERigParticleSimulationMovementType MovementType = ERigParticleSimulationMovementType::Simulated;`
- L96 _public member_ `float Damping = 0.0f;` — Air/ether drag rate (1/time). Zero disables per-particle drag. See UpdateParticle.
- L100 _public member_ `bool bScaleDampingByInverseMass = false;` — When true, Damping is scaled by InvMass (drag-like - lighter particles damp faster). When false, Damping is mass-independent (same relaxation timescale for any mass).

#### struct `RigParticleSimulation::FParticle`  
`struct FParticle`  
_L104-114_
- L106 _public member_ `float InvMass = 0.0f;` — 0 means kinematic (and track the target)
- L108 _public member_ `FSimVector Position = FSimVector::ZeroVector;`
- L109 _public member_ `FSimVector PrevPosition = FSimVector::ZeroVector;`
- L112 _public member_ `FSimVector TargetPosition = FSimVector::ZeroVector;` — The target position is used for kinematic motion
- L113 _public member_ `FSimVector TargetVelocity = FSimVector::ZeroVector;`

#### struct `RigParticleSimulation::FParticleTarget`  
`struct FParticleTarget`  
_L117-138_
- L120 _public member_ `float Compliance = 0.0f;` — How we drive to the target
- L121 _public member_ `float Damping = 0.0f;` — beta
- L122 _public member_ `float TargetVelocityInfluence = 0.0f;`
- L125 _public member_ `float TargetMode = 0.5f;` — 0 = SimSpace (child tracks absolute target), 1 = directional (child+parent track animation direction). Values between blend the two modes.
- L128 _public member_ `FSimVector TargetDirectionFromParent = FSimVector::ZeroVector;` — The current interpolated direction from parent to child (unit vector, per substep)
- L132 _public member_ `float CosAngleLimit = 1.0f;` — Angle limit. Precomputed cos/sin so the solve loop avoids trig calls. AngleLimitCompliance zero means disabled.
- L133 _public member_ `float SinAngleLimit = 0.0f;`
- L134 _public member_ `float AngleLimitCompliance = 0.0f;`
- L137 _public member_ `FSimVector Lambda = FSimVector::ZeroVector;` — Accumulated

#### struct `RigParticleSimulation::FConeLimitInfo`  
`struct FConeLimitInfo`  
_L141-146_
- L143 _public member_ `int32 GrandparentIndex = -1;`
- L144 _public member_ `int32 ParentIndex = -1;`
- L145 _public member_ `int32 ChildIndex = -1;`

#### struct `RigParticleSimulation::FConeLimit`  
`struct FConeLimit`  
_L149-156_
- L151 _public member_ `float Angle = 0.0f;` — Radians
- L152 _public member_ `float Compliance = 0.0f;` — alpha
- L153 _public member_ `float Damping = 0.0f;` — beta
- L155 _public member_ `float Lambda = 0.0f;` — Accumulated

#### struct `RigParticleSimulation::FParticleCollider`  
`struct FParticleCollider`  
_L159-163_
- L161 _public member_ `float Radius = 0.0f;`
- L162 _public member_ `bool bCollideWithColliders = true;`

#### struct `RigParticleSimulation::FParticleNoCollision`  
`struct FParticleNoCollision`  
_L166-170_
- L169 _public member_ `TBitArray<> NoCollisionColliderIndices;` — Flag per simulation state colliders indicating whether they should collide with this particle

#### struct `RigParticleSimulation::FParticleToParticleCollision`  
`struct FParticleToParticleCollision`  
_L173-177_
- L176 _public member_ `TArray<int32> CollisionParticleIndices;` — Indices (into the simulation state particles) which this particle will collide with

#### struct `RigParticleSimulation::FParticleConfinement`  
`struct FParticleConfinement`  
_L180-185_
- L184 _public member_ `TArray<int32> ConfinerIndices;` — Indices (into the simulation state confiners) which keep this particle inside their shapes. Each listed confiner is enforced independently (intersection semantics).

#### struct `RigParticleSimulation::FHardDistanceConstraintInfo`  
`struct FHardDistanceConstraintInfo`  
_L188-192_
- L190 _public member_ `int32 ParentIndex = -1;`
- L191 _public member_ `int32 ChildIndex = -1;`

#### struct `RigParticleSimulation::FHardDistanceConstraint`  
`struct FHardDistanceConstraint`  
_L195-198_
- L197 _public member_ `float TargetDistance = 0.0f;`

#### struct `RigParticleSimulation::FSoftDistanceConstraintInfo`  
`struct FSoftDistanceConstraintInfo`  
_L201-205_
- L203 _public member_ `int32 ParentIndex = -1;`
- L204 _public member_ `int32 ChildIndex = -1;`

#### struct `RigParticleSimulation::FSoftDistanceConstraint`  
`struct FSoftDistanceConstraint`  
_L208-217_
- L210 _public member_ `float TargetDistance = 0.0f;`
- L212 _public member_ `float Compliance = 0.0f;` — alpha
- L213 _public member_ `float Damping = 0.0f;` — beta
- L216 _public member_ `float Lambda = 0.0f;` — Accumulated

#### struct `RigParticleSimulation::FBoxShape`  
`struct FBoxShape`  
_L221-232_
- desc: TODO investigate using the implicit shapes here (and for the others) - e.g. TBox/FImplicitBox3
- L224 _public function_ `void Update(const FSimTransform& InTM, const FSimVector& InExtents)` — Optionally call once per update, if the local data have changed
- L230 _public member_ `FSimTransform TM;`
- L231 _public member_ `FSimVector Extents = FSimVector::ZeroVector;` — Full extents

#### struct `RigParticleSimulation::FCapsuleShape`  
`struct FCapsuleShape`  
_L235-249_
- L238 _public function_ `void Update(const FSimTransform& InTM, float InLength, float InRadius)` — Optionally call once per update, if the local data have changed
- L246 _public member_ `FSimTransform TM;` — Axis is along +ve Z
- L247 _public member_ `float Length = 0.0f;` — Full length
- L248 _public member_ `float Radius = 0.0f;`

#### struct `RigParticleSimulation::FPlaneShape`  
`struct FPlaneShape`  
_L252-264_
- L255 _public function_ `void Update(const FSimTransform& InTM, const FSimVector2D& InExtents)` — Optionally call once per update, if the local data have changed
- L262 _public member_ `FSimTransform TM;` — Plane points in +ve Z
- L263 _public member_ `FSimVector2D Extents = FSimVector2D::ZeroVector;`

#### struct `RigParticleSimulation::FShapeCollection`  
`struct FShapeCollection`  
_L267-278_
- L269 _public member_ `FSimTransform PreviousTM;`
- L270 _public member_ `FSimTransform TargetTM;`
- L273 _public member_ `FSimTransform TM;` — This is the current/interpolated TM
- L275 _public member_ `TArray<FBoxShape> BoxShapes;`
- L276 _public member_ `TArray<FCapsuleShape> CapsuleShapes;`
- L277 _public member_ `TArray<FPlaneShape> PlaneShapes;`

#### struct `RigParticleSimulation::FSimulationState`  
`struct FSimulationState`  
_L301-333_
- L303 _public member_ `TArray<FParticleInfo> ParticleInfos;`
- L304 _public member_ `TArray<FParticle> Particles;`
- L305 _public member_ `TArray<FParticleTarget> ParticleTargets;`
- L306 _public member_ `TArray<FParticleCollider> ParticleColliders;`
- L307 _public member_ `TArray<FParticleNoCollision> ParticleNoCollision;`
- L308 _public member_ `TArray<FParticleToParticleCollision> ParticleToParticleCollision;`
- L309 _public member_ `TArray<FParticleConfinement> ParticleConfinement;` — Lists which confiners confine each particle (opt-in).
- L311 _public member_ `TArray<FHardDistanceConstraintInfo> SkeletalConstraintInfos;` — Along the bones
- L312 _public member_ `TArray<FHardDistanceConstraint> SkeletalConstraints;`
- L314 _public member_ `TArray<FHardDistanceConstraintInfo> HardDistanceConstraintInfos;` — User-specified
- L315 _public member_ `TArray<FHardDistanceConstraint> HardDistanceConstraints;`
- L317 _public member_ `TArray<FSoftDistanceConstraintInfo> SoftDistanceConstraintInfos;` — User-specified
- L318 _public member_ `TArray<FSoftDistanceConstraint> SoftDistanceConstraints;`
- L320 _public member_ `TArray<FConeLimitInfo> ConeLimitInfos;`
- L321 _public member_ `TArray<FConeLimit> ConeLimits;`
- L324 _public member_ `TArray<FShapeCollection> Colliders;` — Particles collide with colliders unless they opt out
- L328 _public member_ `TArray<FShapeCollection> Confiners;` — Confiners share the FShapeCollection layout with Colliders. Each confiner keeps opt-in particles inside every one of its box/capsule/plane shapes (intersection semantics).
- L329 _public member_ `TArray<float> ConfinerStrengths;`
- L332 _public member_ `float PrevStepTime = 0.0f;` — Previous substep time, used for time-corrected Verlet integration at frame boundaries

#### struct `RigParticleSimulation::FSolverSettings`  
`struct FSolverSettings`  
_L336-348_
- L338 _public member_ `FSimVector Gravity = FSimVector::ZeroVector;`
- L340 _public member_ `int32 NumIterations = 1;` — The total number of iterations, which includes the target solving and the constraint solving
- L342 _public member_ `int32 NumConstraintSubIterations = 1;` — The number of constraint (sub) iterations, processed for every one of the main iterations
- L345 _public member_ `float MaxTimeStep = 1.0f;` — The maximum timestep that will be applied, so if the desired step time is greater than this, substeps will be taken.
- L347 _public member_ `int32 MaxNumSteps = 1;` — The maximum number of steps. If this is not enough, then the simulation will run slow.

#### struct `RigParticleSimulation::FSimulationSpaceMotion`  
`struct FSimulationSpaceMotion`  
_L355-378_
- L357 _public member_ `FSimVector LinearVelocity = FSimVector::ZeroVector;`
- L358 _public member_ `FSimVector AngularVelocity = FSimVector::ZeroVector;` — rad/s
- L359 _public member_ `FSimVector LinearAcceleration = FSimVector::ZeroVector;`
- L360 _public member_ `FSimVector AngularAcceleration = FSimVector::ZeroVector;` — rad/s^2
- L365 _public member_ `FSimVector ExternalLinearVelocity = FSimVector::ZeroVector;` — Extra air/ether velocity in simulation space. Particles with non-zero Damping are pulled toward ExternalLinearVelocity + (ExternalAngularVelocity x R), in addition to the implicit air/ether velocity induced by the simulation space's own motion.
- L366 _public member_ `FSimVector ExternalAngularVelocity = FSimVector::ZeroVector;` — rad/s
- L368 _public member_ `float LinearDragMultiplier = 0.0f;` — Air/ether coupling for linear frame motion [typically 0,1]
- L369 _public member_ `float AngularDragMultiplier = 0.0f;` — Air/ether coupling for angular frame motion [typically 0,1]
- L370 _public member_ `float AdditionalDamping = 0.0f;` — Added to every dynamic particle's own Damping rate
- L371 _public member_ `float InertialForceAmount = 0.0f;` — Overall multiplier on inertial pseudo-forces [typically 0,1]
- L372 _public member_ `float LinearEulerAmount = 1.0f;` — Per-term gain on the -a_frame translational force [typically 0,1]
- L373 _public member_ `float AngularEulerAmount = 1.0f;` — Per-term gain on the -alpha x r Euler force [typically 0,1]
- L374 _public member_ `float CentrifugalAmount = 1.0f;` — Per-term gain on the -w x (w x r) centrifugal force [typically 0,1]
- L375 _public member_ `float CoriolisAmount = 1.0f;` — Per-term gain on the -2 w x v Coriolis force [typically 0,1]
- L377 _public member_ `bool bAccelerationsValid = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGDYNAMICS_API`
- L44 _namespace_ `namespace RigParticleSimulation`
- L48 _typedef_ `using FSimVector = FVector3f;` (scope `RigParticleSimulation`)
- L49 _typedef_ `using FSimTransform = FTransform3f;` (scope `RigParticleSimulation`)
- L50 _typedef_ `using FSimVector2D = FVector2f;` (scope `RigParticleSimulation`)
- L51 _typedef_ `using FSimScalar = float;` (scope `RigParticleSimulation`)
- L392 _prototype_ `void UpdateParticle( FSimulationState& State, int32 Index, float InMass, float InGravityMultiplier, float InRadius, float InDamping, bool bInScaleDampingByInverseMass, bool bInCollideWithColliders);` (scope `RigParticleSimulation`)
- L422 _prototype_ `void UpdateParticleTarget( FSimulationState& State, int32 Index, float InvDeltaTime, const FSimVector& InTargetPosition, float InStrength, float InDampingRatio, float InExtraDamping, float InTargetVelocityInfluence, float InTargetMode, float InAngleLimit, float InAngleLimitStrength, bool bInAccelerationMode);` (scope `RigParticleSimulation`)
- L440 _prototype_ `void UpdateCollider(FSimulationState& State, int32 Index, const FSimTransform& TM);` (scope `RigParticleSimulation`)
- L446 _prototype_ `void UpdateConfiner(FSimulationState& State, int32 Index, const FSimTransform& TM);` (scope `RigParticleSimulation`)
- L452 _prototype_ `void UpdateSkeletalConstraint(FSimulationState& State, int32 Index);` (scope `RigParticleSimulation`)
- L459 _prototype_ `void UpdateHardDistanceConstraint( FSimulationState& State, int32 Index, float InLengthMultiplier, float InExtraLength);` (scope `RigParticleSimulation`)
- L468 _prototype_ `void UpdateSoftDistanceConstraint( FSimulationState& State, int32 Index, float InLengthMultiplier, float InExtraLength, float InStrength, float InDampingRatio, float InExtraDamping, bool bInAccelerationMode);` (scope `RigParticleSimulation`)
- L477 _prototype_ `void UpdateConeLimit( FSimulationState& State, int32 Index, float InAngleDegrees, float InStrength, float InDampingRatio);` (scope `RigParticleSimulation`)
- L489 _prototype_ `void Simulate( FSimulationState& SimulationState, const FSolverSettings& SolverSettings, const FSimulationSpaceMotion& SimulationSpaceMotion, float DeltaTime);` (scope `RigParticleSimulation`)
- L504 _prototype_ `TArray<int32> SortParticlesRootToLeaf(FSimulationState& State);` (scope `RigParticleSimulation`)
- L511 _function_ `inline void UpdateSkeletalConstraint(FSimulationState& State, const int32 Index)` (scope `RigParticleSimulation`)
- L522 _function_ `inline void UpdateHardDistanceConstraint( FSimulationState& State, const int32 Index, const float InLengthMultiplier, const float InExtraLength)` (scope `RigParticleSimulation`)
- L535 _function_ `inline void UpdateSoftDistanceConstraint( FSimulationState& State, const int32 Index, const float InLengthMultiplier, const float InExtraLength, const float InStrength, const float InDampingRatio, const float InExtraDamping, const bool bInAccelerationMode)` (scope `RigParticleSimulation`)
- L569 _function_ `inline void UpdateConeLimit( FSimulationState& State, const int32 Index, const float InAngleDegrees, const float InStrength, const float InDampingRatio)` (scope `RigParticleSimulation`)
- L590 _function_ `inline void UpdateCollider(FSimulationState& State, int32 Index, const FSimTransform& TM)` (scope `RigParticleSimulation`)
- L599 _function_ `inline void UpdateConfiner(FSimulationState& State, int32 Index, const FSimTransform& TM)` (scope `RigParticleSimulation`)
- L608 _function_ `inline void UpdateParticle( FSimulationState& State, const int32 Index, const float InMass, const float InGravityMultiplier, const float InRadius, const float InDamping, const bool bInScaleDampingByInverseMass, const bool bInCollideWithColliders)` (scope `RigParticleSimulation`)
