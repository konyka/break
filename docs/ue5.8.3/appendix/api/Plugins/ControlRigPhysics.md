# Plugins / ControlRigPhysics

- module root: `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics`
- headers: 17; symbols: 960
- symbol kinds: class=2, delegate=4, enum=6, enumerator=28, function=133, macro=11, member=495, prototype=165, struct=114, typedef=1, variable=1
- PrivateDependencyModuleNames: ControlRig, ControlRigDeveloper, Core, CoreUObject, EditorStyle, Engine, RigVM, RigVMDeveloper, Slate, SlateCore
- PublicDependencyModuleNames: Core, PhysicsControl

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Private/ControlRigPhysicsEditorStyle.h` (Private)


#### class `FControlRigPhysicsEditorStyle`  
`class FControlRigPhysicsEditorStyle final : public FSlateStyleSet`  
_L13-49_
- inherits: `FSlateStyleSet`
- L17 _public function_ `FControlRigPhysicsEditorStyle() : FSlateStyleSet("ControlRigPhysicsEditorStyle")`
- L39 _public function_ `static FControlRigPhysicsEditorStyle& Get()`
- L45 _public function_ `~FControlRigPhysicsEditorStyle()`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Private/RigPhysicsHelpers.h` (Private)


#### Free symbols / members of external scopes

- L13 _function_ `inline FRigPhysicsBodyComponent* GetPhysicsBody(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L19 _function_ `inline const FRigPhysicsBodyComponent* GetPhysicsBody(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L26 _function_ `inline const FRigPhysicsBodyComponent* GetPhysicsBody( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component.
- L36 _function_ `inline FRigPhysicsBodyComponent* GetPhysicsBody(URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Mutable variant of the cached lookup. FCachedRigComponent::GetComponent returns a const pointer regardless of hierarchy constness, so the const_cast is safe here because the caller holds a non-const URigHierarchy& and the underlying component lives in that hierarchy.
- L43 _function_ `inline FRigPhysicsJointComponent* GetPhysicsJoint(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L49 _function_ `inline const FRigPhysicsJointComponent* GetPhysicsJoint(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L56 _function_ `inline const FRigPhysicsJointComponent* GetPhysicsJoint( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component.
- L64 _function_ `inline FRigPhysicsJointComponent* GetPhysicsJoint(URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Mutable variant of the cached lookup. See the body equivalent for the const_cast rationale.
- L71 _function_ `inline FRigPhysicsControlComponent* GetPhysicsControl(URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L77 _function_ `inline const FRigPhysicsControlComponent* GetPhysicsControl(const URigHierarchy& Hierarchy, const FRigComponentKey& Key)`
- L84 _function_ `inline const FRigPhysicsControlComponent* GetPhysicsControl( const URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Updates the cache if necessary and then returns the component.
- L92 _function_ `inline FRigPhysicsControlComponent* GetPhysicsControl(URigHierarchy& Hierarchy, FCachedRigComponent& CachedComponent)` — Mutable variant of the cached lookup. See the body equivalent for the const_cast rationale.
- L101 _function_ `inline int32 GetElementIndex(const URigHierarchy& Hierarchy, FCachedRigComponent& CachedRigComponent)` — Returns the element index of the cached component's owning element, refreshing the cache first. Caller is responsible for ensuring the cached component has a seeded key.
- L113 _function_ `inline FTransform GetGlobalTransform(const URigHierarchy& Hierarchy, FCachedRigComponent& CachedRigComponent)` — Fetches the global transform of the cached component's owning element using the cached index, avoiding the FRigElementKey TMap lookup that Hierarchy.GetGlobalTransform(Key) performs.

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Private/RigPhysicsLegacyConversion.h` (Private)


#### Free symbols / members of external scopes

- L18 _prototype_ `void TranslateLegacyPhysicsSimulationSpaceSettings( FArchive& Ar, FRigPhysicsSimulationSpaceMotion& OutMotion, FRigPhysicsTeleportDetectionSettings& OutTeleport);` — Decomposes a pre-SimulationSpaceRegrouping FRigPhysicsSimulationSpaceSettings record into the new SpaceMotion + TeleportDetection layout. Reads bytes from the archive in the same order as FRigPhysicsSimulationSpaceSettings::operator<<.
- L26 _prototype_ `void ConvertLegacyPhysicsSimulationSpaceSettings( const FRigPhysicsSimulationSpaceSettings& In, FRigPhysicsSimulationSpaceMotion& OutMotion, FRigPhysicsTeleportDetectionSettings& OutTeleport);` — In-memory equivalent of TranslateLegacyPhysicsSimulationSpaceSettings (no archive read). Used by the deprecated rig units' Execute bodies to convert their input pin into the new component members.
- L35 _prototype_ `FRigPhysicsSimulationSpaceSettings BuildLegacyPhysicsSimulationSpaceSettingsView( const FRigPhysicsSimulationSpaceMotion& Motion, const FRigPhysicsTeleportDetectionSettings& Teleport);` — Inverse of ConvertLegacyPhysicsSimulationSpaceSettings - composes a legacy settings view from the new component members so the deprecated Get rig unit can present its output pin. Per-term inertial gains are dropped (the legacy struct doesn't hold them); a gate=false on a teleport detector translates to threshold=0 (the legacy "disabled" convention).

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Private/RigPhysicsObjectVersion.h` (Private)


#### struct `FRigPhysicsObjectVersion`  
`struct FRigPhysicsObjectVersion`  
_L10-32_
- L28 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L31 _private function_ `FRigPhysicsObjectVersion()`

#### enum `FRigPhysicsObjectVersion::Type`  
`enum Type`  
_L12-25_
- L14 _public enumerator_ `FirstVersion`
- L15 _public enumerator_ `SimulationSpaceRegrouping` — FRigPhysicsSimulationSpaceSettings split into 4 structs
- L16 _public enumerator_ `ResetGatesSplit` — bResetFromX gates added to FRigPhysicsSolverSettings
- L17 _public enumerator_ `WorldCollisionFilterFlags` — bWorldCollisionInclude{Physics,Query,Probe} now serialized
- L18 _public enumerator_ `EvaluationIntervalReset` — bResetFromEvaluationInterval + EvaluationIntervalThresholdForReset
- L19 _public enumerator_ `BodyDampingScaleByInverseMass` — bScaleDampingByInverseMass added to FRigPhysicsDynamics
- L20 _public enumerator_ `WorldCollisionExpiryFramesRemoved` — FRigPhysicsSolverSettings::WorldCollisionExpiryFrames removed
- L23 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-----
- L24 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Private/RigPhysicsSolver.h` (Private)


#### struct `FRigPhysicsIgnorePair`  
`struct FRigPhysicsIgnorePair`  
_L40-51_
- L42 _public function_ `FRigPhysicsIgnorePair(const FRigComponentKey& InA, const FRigComponentKey& InB) : A(InA), B(InB)`
- L44 _public member_ `FRigComponentKey A;`
- L45 _public member_ `FRigComponentKey B;`
- L47 _public function_ `bool operator==(const FRigPhysicsIgnorePair& Other) const`

#### struct `FWorldObjectKey`  
`struct FWorldObjectKey`  
_L62-74_
- L64 _public function_ `FWorldObjectKey(uint32 InComponentId, int32 InInstanceIndex) : ComponentId(InComponentId), InstanceIndex(InInstanceIndex)`
- L67 _public member_ `uint32 ComponentId;`
- L68 _public member_ `int32 InstanceIndex;`
- L70 _public function_ `bool operator==(const FWorldObjectKey& Other) const`

#### struct `FRigBodyRecord`  
`struct FRigBodyRecord`  
_L84-116_
- L87 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle = nullptr;` — Things that are set during instantiation
- L92 _public member_ `FCachedRigComponent CachedPhysicsBodyComponent;` — Cached component pointer so the per-tick solver loops can skip the hierarchy TMap lookup that Hierarchy.FindComponent(Key) performs. Auto-invalidated by the topology hash check inside FCachedRigComponent::UpdateCache.
- L95 _public member_ `FRigElementKey TargetElementKey;` — Cache the element key for where we will write the simulation result
- L99 _public member_ `FTransform FinalComponentSpaceTM;` — The final/simulated transform is stored before writing it into the output, so we can avoid corrupting the output if anything is bad and we need to reset.
- L104 _public member_ `FTransform SourceComponentSpaceTM;` — These source (i.e. bone/element) transforms are updated for all records in UpdatePrePhysics. The times/validity are determined by the CurrentDeltaTime, PrevDeltaTime and update counters in the simulation itself.
- L105 _public member_ `FVector SourceComponentSpaceVelocity = FVector::ZeroVector;`
- L106 _public member_ `FVector SourceComponentSpaceAngularVelocity = FVector::ZeroVector;`
- L108 _public member_ `FTransform PrevSourceComponentSpaceTM;`
- L109 _public member_ `FVector PrevSourceComponentSpaceVelocity = FVector::ZeroVector;`
- L110 _public member_ `FVector PrevSourceComponentSpaceAngularVelocity = FVector::ZeroVector;`
- L115 _public member_ `float PhysicsBlendWeight = 1.0f;` — Cached from PhysicsBodyComponent.BodyData.PhysicsBlendWeight inside UpdatePostPhysics so the hierarchy-writeback loop can compute EffectiveAlpha = Alpha * PhysicsBlendWeight without a second component lookup. Default 1.0 = fully physics.

#### struct `FRigJointRecord`  
`struct FRigJointRecord`  
_L121-142_
- L124 _public member_ `ImmediatePhysics::FJointHandle* JointHandle = nullptr;` — Things that are set during instantiation
- L127 _public member_ `FCachedRigComponent CachedPhysicsJointComponent;` — Cached joint component pointer (see FRigBodyRecord for rationale).
- L133 _public member_ `FCachedRigComponent CachedParentBodyComponent;` — Cached parent/child body components. These keys are filled in when the record is created, even if the original key is set to pick up the components automatically. Cached so the per-tick joint update can skip both the component TMap lookup and (via GetGlobalTransform on the cache) the element key TMap lookup.
- L134 _public member_ `FCachedRigComponent CachedChildBodyComponent;`
- L139 _public member_ `FTransform PreviousDriveTargetTM;` — The drive works with velocities so we store the previous target transform, and when it was stored.
- L141 _public member_ `int64 PreviousDriveTargetUpdateCounter = -999;` — This is stored from the main solver update counter, marking when the previous drive TM was valid.

#### struct `FRigControlRecord`  
`struct FRigControlRecord`  
_L147-171_
- L150 _public member_ `ImmediatePhysics::FJointHandle* JointHandle = nullptr;` — Things that are set during instantiation
- L153 _public member_ `FCachedRigComponent CachedPhysicsControlComponent;` — Cached control component pointer (see FRigBodyRecord for rationale).
- L157 _public member_ `FCachedRigComponent CachedParentBodyComponent;` — Cached parent/child body components (see FRigJointRecord for rationale). An invalid parent here indicates a sim-space control attached to the simulation actor.
- L158 _public member_ `FCachedRigComponent CachedChildBodyComponent;`
- L163 _public member_ `FTransform PreviousTargetTM;` — The control works with velocities so we store the previous target, and when it was stored.
- L165 _public member_ `int64 PreviousTargetUpdateCounter = -999;` — This is stored from the main solver update counter, marking when the previous target TM was valid.
- L170 _public member_ `bool bCachedHasStrengthOrDamping = true;` — When the FRigPhysicsControlComponent is dirty, this is calculated from the strengths etc, and then cached. Then if FRigPhysicsControlComponent is clean, we can see whether there is any strength/damping that would require the target to be updated.

#### struct `FRigPhysicsSolver`  
`struct FRigPhysicsSolver`  
_L183-583_
- reflection: `USTRUCT()`
- L188 _public function_ `FRigPhysicsSolver()`
- L189 _public prototype_ `FRigPhysicsSolver(const FRigComponentKey& SolverComponentKey);`
- L192 _public prototype_ `void Instantiate( const FRigVMExecuteContext& ExecuteContext, URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent);` — This will initialise/create the simulation and then create everything we need in it.
- L205 _public prototype_ `void StepSimulation( const UWorld* World, const AActor* OwningActorPtr, const FRigVMExecuteContext& ExecuteContext, URigHierarchy& Hierarchy, FRigPhysicsSolverComponent& SolverComponent, const float DeltaTimeOverride, const float SimulationSpaceDeltaTimeOverride, const float Alpha, const bool bTrackVelocitiesDuringPassThrough);` — Integrates the simulation forwards. If DeltaTimeOverride is +ve, then that value is used. If it is zero, then delta time is taken from the execute context If it is negative, then the simulation isn't stepped. When Alpha is <= 0 the simulation is bypassed entirely (pass-through). If bTrackVelocitiesDuringPassThrough is true the solver still updates source bone transforms and sim-space state each frame so velocities are valid on resume. Otherwise the resume schedules a brief kinematic warm-up via TrackInputCounter.
- L217 _public prototype_ `void Draw( FRigVMDrawInterface* DI, const FRigPhysicsSolverSettings& SolverSettings, const FRigPhysicsVisualizationSettings1& VisualizationSettings, const UWorld* DebugWorld) const;` — Draws shapes etc AND (potentially) enables the low-level Chaos debug draw
- L237 _public function_ `const FSimulationSpaceData& GetSimulationSpaceData() const` — Returns the simulation space data, as calculated at the start of the last step
- L240 _public function_ `const FRigComponentKey& GetSolverComponentKey() const` — Returns the component that we're associated with/owned by
- L261 _private prototype_ `void InitialiseSimulation();` — Creates the low level simulation
- L264 _private prototype_ `void InitialiseBodyRecords(const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent);` — This collects all the bodies associated with the solver and makes records for them
- L267 _private prototype_ `void InitialiseJointRecords(const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent);` — This collects all the joints associated with the solver and makes records for them
- L270 _private prototype_ `void InitialiseControlRecords(const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent);` — This collects all the controls associated with the solver and makes records for them
- L273 _private prototype_ `void InstantiatePhysicsBodies( URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, FRigPhysicsIgnorePairs& IgnorePairs);` — Creates low level bodies
- L279 _private prototype_ `void InstantiatePhysicsJoints( const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, FRigPhysicsIgnorePairs& IgnorePairs);` — Creates low level physics joints
- L285 _private prototype_ `void InstantiateControls( const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, FRigPhysicsIgnorePairs& IgnorePairs);` — Creates low level controls
- L291 _private prototype_ `void InstantiateSolverCollision( const FRigPhysicsSolverComponent& SolverComponent, FRigPhysicsIgnorePairs& IgnorePairs);` — Creates collision shapes associated with the solver. Also applies IgnorePairs
- L297 _private prototype_ `bool ShouldComponentBeInSimulation( const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, const FRigComponentKey& ComponentKey) const;` — Returns true if the component is physics, and its solver matches the/our solver component (directly, or automatically)
- L307 _private prototype_ `FRigComponentKey FindAncestorBodyInSimulation( const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, const FRigElementKey& InChildElementKey) const;` — Walks the parent-element chain starting from InChildElementKey's first parent and returns the first component on any ancestor that ShouldComponentBeInSimulation accepts. Returns an invalid key if no ancestor has a qualifying component. Used to auto-resolve the parent body for joint and control components when the user left the parent key blank - physics assets may skip bodies on intermediate joints, so we keep walking until we find one.
- L313 _private prototype_ `ImmediatePhysics::FActorHandle* CreateBody( const FName BodyName, const FRigPhysicsCollision& Collision, const FRigPhysicsDynamics* Dynamics, const FPhysicsControlModifierData* BodyData, const FTransform& BodyRelSimSpaceTM) const;` — Creates an actor with collision. This will be dynamic if Dynamics is valid, or otherwise kinematic
- L322 _private prototype_ `void DestroyPhysicsSimulation();` — This releases the actors etc in the simulation, destroys the simulation, and resets our internal records.
- L324 _private prototype_ `void UpdatePrePhysics( const FRigVMExecuteContext& ExecuteContext, const URigHierarchy& Hierarchy, FRigPhysicsSolverComponent& SolverComponent, const float DeltaTime);`
- L330 _private prototype_ `void UpdateBodyRecordPrePhysics( const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, const float DeltaTime, FRigBodyRecord& Record, const FRigPhysicsBodyComponent* PhysicsComponent);`
- L339 _private prototype_ `void UpdateBodyRecordsPrePhysics( const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, const float DeltaTime);` — Iterates all BodyRecords and calls UpdateBodyRecordPrePhysics on each. Used by UpdatePrePhysics and by the Alpha=0 pass-through path when velocity tracking is enabled.
- L347 _private prototype_ `void ClearBodyForceAndTorques(URigHierarchy& Hierarchy);` — Drops all queued ForceAndTorques entries across all bodies. Called on pass-through frames where ApplyForcesPrePhysics/UpdatePostPhysics won't run, so the queue cannot leak across the pause.
- L355 _private prototype_ `void ResetPoseFromAnimation( const FRigPhysicsSolverComponent& SolverComponent, const bool bUseSourceVelocity);` — Snaps every dynamic actor handle to the current Record.SourceComponentSpaceTM (after converting into simulation space). Used by the Alpha=0 pass-through path so that during (and on resume from) pass-through, the simulation is at the input animation pose rather than the last simulated pose. When bUseSourceVelocity is true, the actor velocities are set from Record.SourceComponent[Angular]Velocity (tracking mode - smooth resume). Otherwise they are zeroed (reset mode).
- L359 _private prototype_ `void UpdateBodyPrePhysics( const FRigVMExecuteContext& ExecuteContext, const FRigPhysicsSolverComponent& SolverComponent, const FRigBodyRecord& Record, const FRigPhysicsBodyComponent& PhysicsComponent);`
- L365 _private prototype_ `void ApplyForcesPrePhysics( const FRigVMExecuteContext& ExecuteContext, const FRigPhysicsSolverComponent& SolverComponent, const FRigBodyRecord& Record, const FRigPhysicsBodyComponent& PhysicsComponent);`
- L371 _private prototype_ `void UpdateJointPrePhysics( const URigHierarchy& Hierarchy, FRigJointRecord& JointRecord, const FRigPhysicsJointComponent& JointComponent, const float DeltaTime);`
- L377 _private prototype_ `void UpdateControlPrePhysics( FRigControlRecord& ControlRecord, const FRigPhysicsControlComponent& ControlComponent, const FRigPhysicsSolverComponent& SolverComponent, const URigHierarchy& Hierarchy, const float DeltaTime);`
- L384 _private prototype_ `void UpdatePostPhysics( URigHierarchy& Hierarchy, FRigPhysicsSolverComponent& SolverComponent, const float Alpha, const float DeltaTime, const bool bUsingFixedStep);`
- L392 _private prototype_ `void UpdateWorldObjectsPrePhysics(const FRigPhysicsSolverSettings& SolverSettings);` — This will walk through the WorldObjects, which should now be updated, and update the simulation
- L395 _private prototype_ `void UpdateWorldObjectsPostPhysics( const UWorld* World, const FRigPhysicsSolverSettings& SolverSetting, const AActor* OwningActorPtr);` — This will trigger a game-thread update of WorldObjects, ready for the next update
- L400 _private prototype_ `void InitSimulationSpace(const FTransform& ComponentToWorld, const FTransform& BoneToComponent);`
- L402 _private prototype_ `void CheckForResetsPrePhysics( const URigHierarchy& Hierarchy, FRigPhysicsSolverComponent& SolverComponent, const float DeltaTime);`
- L406 _private prototype_ `FSimulationSpaceData UpdateSimulationSpaceStateAndCalculateData( const FRigVMExecuteContext& ExecuteContext, const URigHierarchy& Hierarchy, const FRigPhysicsSolverComponent& SolverComponent, const float Dt, const double AbsoluteTime);` — AbsoluteTime is used for calculating turbulence when applying the "wind"
- L413 _private prototype_ `static FTransform GetSpaceTransform( ERigPhysicsSimulationSpace Space, const FTransform& ComponentTM, const FTransform& BoneTM);`
- L417 _private prototype_ `FTransform GetSimulationSpaceTransform(const FRigPhysicsSolverSettings& SolverSettings) const;` — Returns the simulation space transform, in world space
- L421 _private prototype_ `FTransform ConvertComponentSpaceTransformToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& ComponentSpaceTM) const;` — Converts a transform from component space (e.g. coming from the owning control rig) into the simulation space
- L425 _private prototype_ `FVector ConvertComponentSpacePositionToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& ComponentSpacePosition) const;` — Converts a component space position to simulation space, including translation
- L429 _private prototype_ `FVector ConvertComponentSpaceVectorToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& ComponentSpaceVector) const;` — Converts a component space vector to simulation space, ignoring translation
- L433 _private prototype_ `FTransform ConvertWorldTransformToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& WorldSpaceTM) const;` — Converts a transform specified in world space to the simulation space
- L437 _private prototype_ `FVector ConvertWorldPositionToSimSpaceNoScale( const FRigPhysicsSolverSettings& SolverSettings, const FVector& WorldSpacePosition) const;` — Converts a position specified in world space to the simulation space
- L441 _private prototype_ `FVector ConvertWorldVectorToSimSpaceNoScale( const FRigPhysicsSolverSettings& SolverSettings, const FVector& WorldSpaceVector) const;` — Converts a vector specified in world space to the simulation space (e.g. converting gravity)
- L446 _private prototype_ `FTransform ConvertSimSpaceTransformToComponentSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& SimSpaceTM) const;` — Converts a transform from the simulation space to component space (e.g. for writing back to the owning control rig)
- L450 _private prototype_ `FVector ConvertSimSpacePositionToComponentSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& SimSpacePosition) const;` — Converts a simulation space position to component space, including translation
- L454 _private prototype_ `FVector ConvertSimSpaceVectorToComponentSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& SimSpaceVector) const;` — Converts a simulation space vector to component space (ignoring translation)
- L458 _private prototype_ `FTransform ConvertCollisionSpaceTransformToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& TM) const;` — Converts a collision space transform to simulation space
- L463 _private prototype_ `ImmediatePhysics::FActorHandle* GetActor(const FRigComponentKey& ComponentKey) const;` — Gets the simulation actor handle for a component key. Note that the component key could be a body or a solver component. Can return nullptr
- L467 _private prototype_ `void SetPhysicsBodyComponentState( const FRigPhysicsSolverSettings& SolverSettings, FRigBodyRecord& Record, FRigPhysicsBodyComponent& PhysicsBodyComponent) const;` — Updates the PhysicsBodyComponent with the state of the rigid body from the record. Assumes that FinalComponentSpaceTM has been set.
- L473 _private member_ `FRigComponentKey PhysicsSolverComponentKey;`
- L476 _private member_ `TMap<FRigComponentKey, FRigBodyRecord> BodyRecords;` — All the bodies, but in no particular order
- L479 _private member_ `TArray<FRigComponentKey> SortedBodyComponentKeys;` — Ordering so that we can traverse from root to leaf bones
- L482 _private member_ `TMap<FRigComponentKey, FRigJointRecord> JointRecords;` — All the joints
- L485 _private member_ `TMap<FRigComponentKey, FRigControlRecord> ControlRecords;` — All the controls
- L487 _private member_ `TSharedPtr<ImmediatePhysics::FSimulation> Simulation;`
- L491 _private member_ `ImmediatePhysics::FActorHandle* CollisionActorHandle = nullptr;` — Used to store things the simulation collision shape. May be offset from the origin if collision is in a different space to the simulation.
- L495 _private member_ `ImmediatePhysics::FActorHandle* SimulationActorHandle = nullptr;` — Used to make controls when they're not attached to another simulated body. Will always be at the origin.
- L497 _private member_ `Chaos::FPBDJointSolverSettings ChaosJointSolverSettings;`
- L499 _private member_ `FSimulationSpaceState SimulationSpaceState;`
- L503 _private member_ `FSimulationSpaceData SimulationSpaceData;` — Retain the data - we don't actually need to but (a) it makes it available for debugging and (b) it avoids passing it through the functions.
- L507 _private member_ `int64 UpdateCounter = 0;` — This is incremented at the very beginning of each simulation step, used to identify when previously calculated values are valid. Note that the universe will roll over before a int64 does
- L510 _private member_ `int64 PreviousUpdateCounter = -999;` — The update counter when PrevSourceComponentSpaceTM etc were written. Check this before using them
- L514 _private member_ `bool bNeedToInstantiate = true;` — This will be set to false after instantiation, which can happen manually during construction, or be postponed until there is a simulation step.
- L520 _private member_ `bool bNeedToResetPose = false;` — Set true when StepSimulation ran in non-tracking pass-through mode (Alpha <= 0, bTrackVelocitiesDuringPassThrough false) on an already-instantiated sim. Consumed at the top of the next non-pass-through step by bumping SolverComponent.TrackInputCounter so all dynamic bodies warm up over a few frames.
- L526 _private member_ `double LastEvaluationAbsoluteTime = -1.0;` — Absolute time (from the rig's ExecuteContext) at the start of the most recent StepSimulation call. A value < 0 means "no prior evaluation" - the interval test is skipped on the first frame after instantiation. Populated regardless of bResetFromEvaluationInterval so toggling the flag on doesn't have a one-frame priming delay.
- L574 _private member_ `TSharedPtr<TMap<FWorldObjectKey, FWorldObject>> WorldObjects;` — The world objects we track for collision. Index uses a composite key composed of the PrimitiveComponent Id and, possibly, the overlap item index. Note that this is only guaranteed to be unique whilst the object exists, so it is possible (but hopefully unlikely) that an object will be replaced and have the same ID. This will be rectified on the next update, as the record's pointer to the primitive component will be invalid.
- L577 _private member_ `FBox WorldOverlapBox;` — The box used for overlap tests to find the world objects
- L582 _private member_ `TSharedPtr<FTransactionallySafeCriticalSection> SimulationMutex;` — Guard against access to the low level simulation. Note that this access may come from an async/spawned task, so the mutex itself needs to be shared, as we (as primary owners) may get deleted whilst the spawned task is in flight.

#### struct `FRigPhysicsSolver::FSimulationSpaceData`  
`struct FSimulationSpaceData`  
_L225-234_
- desc: Represents the properties of the simulation space - calculated near the beginning of the update. Note that all these are specified in the simulation space itself
- L227 _public member_ `FVector LinearVelocity;`
- L229 _public member_ `FVector AngularVelocity;` — Angular velocity is in rad/s
- L230 _public member_ `FVector LinearAcceleration;`
- L232 _public member_ `FVector AngularAcceleration;` — Angular acceleration is in rad/s/s
- L233 _public member_ `FVector Gravity;`

#### struct `FRigPhysicsSolver::FSimulationSpaceState`  
`struct FSimulationSpaceState`  
_L245-258_
- desc: Used by the world-space to simulation-space motion transfer system in Component- or Bone-Space sims, and preserved between updates.
- L247 _public member_ `FTransform ComponentTM;`
- L248 _public member_ `FTransform BoneRelComponentTM;`
- L251 _public member_ `FTransform SimulationSpaceTM;` — The world transform of the simulation space
- L252 _public member_ `FTransform PrevSimulationSpaceTM;`
- L253 _public member_ `FTransform PrevPrevSimulationSpaceTM;`
- L255 _public member_ `float Dt = 1.0f;` — The time between SimulationSpaceTM and PrevSimulationSpaceTM
- L257 _public member_ `float PrevDt = 1.0f;` — The time between PrevSimulationSpaceTM and PrevPrevSimulationSpaceTM

#### struct `FRigPhysicsSolver::FWorldObject`  
`struct FWorldObject`  
_L529-567_
- desc: Record of a world object that we want to track, and "import" into our simulation for collision.
- L531 _public function_ `FWorldObject() : ActorHandle(nullptr), LastSeenUpdateCounter(0)`
- L532 _public function_ `FWorldObject(ImmediatePhysics::FActorHandle* InActorHandle, int64 InLastSeenUpdateCounter) : ActorHandle(InActorHandle) , LastSeenUpdateCounter(InLastSeenUpdateCounter)`
- L538 _public member_ `TWeakObjectPtr<UPrimitiveComponent> WorldPrimitiveComponent;` — The object we are tracking
- L541 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle;` — The actor in our simulation
- L544 _public member_ `FTransform ComponentWorldTransform;` — The transform of the world object. This will be updated in the game-thread task.
- L548 _public member_ `int64 LastSeenUpdateCounter;` — When the world object was last seen (i.e. captured by an overlap), used to detect when we should expire/forget about it.
- L552 _public member_ `int32 InstanceBodyIndex = INDEX_NONE;` — For instanced static mesh components, the index of the specific instance this actor represents. INDEX_NONE for non-instanced components.
- L555 _public function_ `bool GetExpired(int64 InUpdateCounter) const` — This returns true if the object hasn't been seen recently, or is invalid

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigPhysics, Warning, Warning);`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigPhysics, Warning, Warning);`
- L34 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigPhysics, Log, All);`
- L34 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigPhysics, Log, All);`
- L53 _function_ `FORCEINLINE uint32 GetTypeHash(const FRigPhysicsIgnorePair& Pair)`
- L57 _typedef_ `typedef TSet<FRigPhysicsIgnorePair> FRigPhysicsIgnorePairs;`
- L76 _function_ `FORCEINLINE uint32 GetTypeHash(const FWorldObjectKey& Key)`
- L177 _prototype_ `bool RigPhysicsShouldVisualize(const FRigPhysicsVisualizationSettings1& VisualizationSettings);`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Private/RigPhysicsSolver_Space.inl` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `FORCEINLINE FTransform FRigPhysicsSolver::GetSpaceTransform( ERigPhysicsSimulationSpace Space, const FTransform& ComponentTM, const FTransform& BoneTM)` (scope `FRigPhysicsSolver`)
- L24 _function_ `FORCEINLINE FTransform FRigPhysicsSolver::GetSimulationSpaceTransform(const FRigPhysicsSolverSettings& SolverSettings) const` (scope `FRigPhysicsSolver`)
- L37 _function_ `FORCEINLINE FTransform FRigPhysicsSolver::ConvertComponentSpaceTransformToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& TM) const` (scope `FRigPhysicsSolver`)
- L50 _function_ `FORCEINLINE FVector FRigPhysicsSolver::ConvertComponentSpacePositionToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& P) const` (scope `FRigPhysicsSolver`)
- L63 _function_ `FORCEINLINE FVector FRigPhysicsSolver::ConvertComponentSpaceVectorToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& V) const` (scope `FRigPhysicsSolver`)
- L77 _function_ `FORCEINLINE FTransform FRigPhysicsSolver::ConvertSimSpaceTransformToComponentSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& TM) const` (scope `FRigPhysicsSolver`)
- L90 _function_ `FORCEINLINE FVector FRigPhysicsSolver::ConvertSimSpacePositionToComponentSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& Position) const` (scope `FRigPhysicsSolver`)
- L103 _function_ `FORCEINLINE FVector FRigPhysicsSolver::ConvertSimSpaceVectorToComponentSpace( const FRigPhysicsSolverSettings& SolverSettings, const FVector& Vector) const` (scope `FRigPhysicsSolver`)
- L116 _function_ `FORCEINLINE FVector ConvertWorldVectorToSimSpaceNoScale( ERigPhysicsSimulationSpace Space, const FVector& WorldVector, const FTransform& ComponentTM, const FTransform& BoneTM)`
- L131 _function_ `FORCEINLINE FVector FRigPhysicsSolver::ConvertWorldVectorToSimSpaceNoScale( const FRigPhysicsSolverSettings& SolverSettings, const FVector& WorldVector) const` (scope `FRigPhysicsSolver`)
- L147 _function_ `FORCEINLINE FVector FRigPhysicsSolver::ConvertWorldPositionToSimSpaceNoScale( const FRigPhysicsSolverSettings& SolverSettings, const FVector& WorldPosition) const` (scope `FRigPhysicsSolver`)
- L163 _function_ `FORCEINLINE FTransform FRigPhysicsSolver::ConvertWorldTransformToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& WorldTM) const` (scope `FRigPhysicsSolver`)
- L177 _function_ `FORCEINLINE FTransform FRigPhysicsSolver::ConvertCollisionSpaceTransformToSimSpace( const FRigPhysicsSolverSettings& SolverSettings, const FTransform& TM) const` (scope `FRigPhysicsSolver`)

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/ControlRigPhysicsModule.h` (Public)


#### class `FControlRigPhysicsModule`  
`class FControlRigPhysicsModule : public IModuleInterface`  
_L15-22_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigPhysics, Warning, Warning);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigPhysics, Warning, Warning);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigPhysics, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigPhysics, Log, All);`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsBodyComponent.h` (Public)


#### struct `FRigPhysicsBodyComponent`  
`struct FRigPhysicsBodyComponent : public FRigBaseComponent`  
_L13-84_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- desc: A component that can be added to a joint/element that defines how a physical body can be "attached" to it. The body supports dynamic movement, collision, and a physics joint with this body's parent in the hierarchy.
- L18 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigPhysicsBodyComponent)`
- L28 _public member_ `FRigPhysicsDynamics Dynamics;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics, meta = (ShowOnlyInnerProperties))` — Dynamics properties that should only be set during the control rig construction event, before the body is instantiated
- L33 _public member_ `FRigPhysicsCollision Collision;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics, meta = (ShowOnlyInnerProperties))` — Collision properties that should only be set during the control rig construction event, before the body is instantiated
- L37 _public member_ `FPhysicsControlModifierData BodyData;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics)` — Properties that can and will likely be modified at runtime
- L41 _public member_ `FTransform KinematicTarget;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics)` — The target for when this body is kinematic
- L47 _public member_ `TArray<FRigComponentKey> NoCollisionBodies;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics)` — A list of body components with which we should not collide. The solver component can also be included to prevent collisions against its shapes. This is typically/must only be set during the control rig construction event, before the body is instantiated
- L56 _public prototype_ `void AutoCalculateCollision(URigHierarchy* Hierarchy, float MinAspectRatio = 0.25f, float MinSize = 0.0f);` — Removes any existing collision, and replaces it with a shape calculated from the joint positions (if possible). The shape will be a single box when there are enough joints, but when there are only a few joints it may be a sphere or capsule, depending on what is most appropriate. @param Hierarchy The hierarchy - the joint positions will be used to calculate the shape. @param MinAspectRatio The minimum box extent, as a proportion of the maximum box extent. @param MinSize The minimum size (in each dimension) of the created shape.
- L58 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L59 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L62 _public prototype_ `virtual const FSlateIcon& GetIconForUI() const override;`
- L65 _public prototype_ `virtual void OnAddedToHierarchy(URigHierarchy* InHierarchy, URigHierarchyController* InController) override;`
- L67 _public prototype_ `virtual void OnRigHierarchyKeyChanged(const FRigHierarchyKey& InOldKey, const FRigHierarchyKey& InNewKey) override;`
- L69 _public function_ `virtual FName GetDefaultComponentName() const override`
- L71 _public function_ `static FName GetDefaultName()`
- L77 _public member_ `TArray<FPhysicsControlNamedForceAndTorqueData> ForceAndTorques;` — Forces (etc) that should be applied and then cleared at the next solver step.
- L80 _public member_ `FTransform Transform;` — Internal/runtime state, in component space
- L81 _public member_ `FTransform CoMTransform;`
- L82 _public member_ `FVector LinearVelocity = FVector::ZeroVector;`
- L83 _public member_ `FVector AngularVelocity = FVector::ZeroVector;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsBodyExecution.h` (Public)


#### struct `FRigUnit_AddPhysicsBody`  
`struct FRigUnit_AddPhysicsBody : public FRigUnit_PhysicsBaseMutable`  
_L15-52_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Physics Body", Keywords = "Add,Construction,Create,New,Body,Skeleton", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Adds a new physics body as a component on the owner element. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L19 _public function_ `FRigUnit_AddPhysicsBody()`
- L26 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L31 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L35 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Output))` — The Physics Body component key that was created
- L39 _public member_ `FRigPhysicsBodySolverSettings Solver;` — `UPROPERTY(meta = (Input))` — The solver to relate this new physics body should be added to
- L43 _public member_ `FRigPhysicsDynamics Dynamics;` — `UPROPERTY(meta = (Input))` — The dynamics properties of the new physics element
- L47 _public member_ `FRigPhysicsCollision Collision;` — `UPROPERTY(meta = (Input))` — The collision properties of the new physics element
- L51 _public member_ `FPhysicsControlModifierData BodyData;` — `UPROPERTY(meta = (Input))` — The runtime modifiable data

#### struct `FRigUnit_GetPhysicsBodyExists`  
`struct FRigUnit_GetPhysicsBodyExists : public FRigUnit_PhysicsBase`  
_L56-71_
- reflection: `USTRUCT(meta=(DisplayName="Get Physics Body Exists", Keywords="Query,Body"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Indicates whether the component exists and is a Physics Body
- L60 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L65 _public member_ `FRigComponentKey PhysicsBodyComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigPhysicsBodyComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The component key to check
- L70 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Physics Body

#### struct `FRigUnit_HierarchyAutoCalculateCollision`  
`struct FRigUnit_HierarchyAutoCalculateCollision : public FRigUnit_PhysicsBaseMutable`  
_L77-103_
- reflection: `USTRUCT(meta = (DisplayName = "Calculate Physics Collision", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Discards any existing collision data and replaces it with a shape based on the joint positions. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L81 _public function_ `FRigUnit_HierarchyAutoCalculateCollision()`
- L87 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L92 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L97 _public member_ `float MinAspectRatio = 0.25f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — For boxes: The minimum box extent, as a proportion of the maximum box extent. For capsules: The minimum radius, as a proportion of the length (not including the radius)
- L102 _public member_ `float MinSize = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — For boxes: The minimum side length. For capsules: The minimum radius

#### struct `FRigUnit_HierarchySetBodySolverSettings`  
`struct FRigUnit_HierarchySetBodySolverSettings : public FRigUnit_PhysicsBaseMutable`  
_L109-129_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Solver Settings", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the body solver settings etc for a physics component body. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L113 _public function_ `FRigUnit_HierarchySetBodySolverSettings()`
- L119 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L124 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L128 _public member_ `FRigPhysicsBodySolverSettings BodySolverSettings;` — `UPROPERTY(meta = (Input))` — Sets the body solver settings of the Physics Body

#### struct `FRigUnit_HierarchySetDynamics`  
`struct FRigUnit_HierarchySetDynamics : public FRigUnit_PhysicsBaseMutable`  
_L136-156_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Dynamics Properties", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the mass etc for a physics component body. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L140 _public function_ `FRigUnit_HierarchySetDynamics()`
- L146 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L151 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L155 _public member_ `FRigPhysicsDynamics Dynamics;` — `UPROPERTY(meta = (Input))` — Sets the properties describing the dynamics properties of the Physics Body

#### struct `FRigUnit_HierarchySetCollision`  
`struct FRigUnit_HierarchySetCollision : public FRigUnit_PhysicsBaseMutable`  
_L162-182_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Collision Properties", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the collision for a physics component body. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L166 _public function_ `FRigUnit_HierarchySetCollision()`
- L172 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L177 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L181 _public member_ `FRigPhysicsCollision Collision;` — `UPROPERTY(meta = (Input))` — Specifies the collision associated with the Physics Body

#### struct `FRigUnit_HierarchyDisableCollisionBetween`  
`struct FRigUnit_HierarchyDisableCollisionBetween : public FRigUnit_PhysicsBaseMutable`  
_L189-211_
- reflection: `USTRUCT(meta = (DisplayName = "Disable Collision Between", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Disables collision between two bodies. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L193 _public function_ `FRigUnit_HierarchyDisableCollisionBetween()`
- L201 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L206 _public member_ `FRigComponentKey PhysicsBodyComponentKey1;` — `UPROPERTY(meta = (Input))` — Component key for the first body
- L210 _public member_ `FRigComponentKey PhysicsBodyComponentKey2;` — `UPROPERTY(meta = (Input))` — Component key for the second body

#### struct `FRigUnit_HierarchySetPhysicsBodySourceBone`  
`struct FRigUnit_HierarchySetPhysicsBodySourceBone : public FRigUnit_PhysicsBaseMutable`  
_L220-241_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Source Bone", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets what bone is used as a source transform for the physics body. This is used as a kinematic target, and when initializing the simulation. Note: Although this can be changed after physics instantiation, doing so will produce a one-frame velocity spike because the source velocity is computed from the difference between the previous frame's source bone position and the new source bone position, which may produce undesirable simulation behaviour (including tripping the auto-reset thresholds).
- L224 _public function_ `FRigUnit_HierarchySetPhysicsBodySourceBone()`
- L231 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L236 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L240 _public member_ `FRigElementKey SourceBone;` — `UPROPERTY(meta = (Input))` — The bone to use as a source transform (kinematic target, and initialization) for the Physics Body.

#### struct `FRigUnit_HierarchySetPhysicsBodyTargetBone`  
`struct FRigUnit_HierarchySetPhysicsBodyTargetBone : public FRigUnit_PhysicsBaseMutable`  
_L247-268_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Target Bone", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets what bone is targeted by the simulation - i.e. where the simulation output is written to. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L251 _public function_ `FRigUnit_HierarchySetPhysicsBodyTargetBone()`
- L258 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L263 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L267 _public member_ `FRigElementKey TargetBone;` — `UPROPERTY(meta = (Input))` — The bone to use as a target for the Physics Body - i.e. where its transforms should be written to.

#### struct `FRigUnit_HierarchySetPhysicsBodySparseData`  
`struct FRigUnit_HierarchySetPhysicsBodySparseData : public FRigUnit_PhysicsBaseMutable`  
_L274-294_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Data", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets all the data on a body - but in a sparse way so you can decide which parameters get applied. Note that the sparse data does not get displayed correctly (the flags that enable/disable all end up getting reset if the user attempts to change them) so this should be used with caution until this is fixed.
- L278 _public function_ `FRigUnit_HierarchySetPhysicsBodySparseData()`
- L284 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L289 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L293 _public member_ `FPhysicsControlModifierSparseData Data;` — `UPROPERTY(meta = (Input))` — Sparse data to be set on the Physics Body

#### struct `FRigUnit_HierarchySetPhysicsBodyKinematicTarget`  
`struct FRigUnit_HierarchySetPhysicsBodyKinematicTarget : public FRigUnit_PhysicsBaseMutable`  
_L298-319_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Kinematic Target", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the kinematic target for a body - note that this won't actually make the body kinematic
- L302 _public function_ `FRigUnit_HierarchySetPhysicsBodyKinematicTarget()`
- L308 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L313 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L318 _public member_ `FTransform KinematicTarget;` — `UPROPERTY(meta = (Input))` — Kinematic target for the Physics Body. This will be combined with the animation pose, depending on the Kinematic Target Space.

#### struct `FRigUnit_HierarchySetPhysicsBodyKinematicTargetSpace`  
`struct FRigUnit_HierarchySetPhysicsBodyKinematicTargetSpace : public FRigUnit_PhysicsBaseMutable`  
_L323-343_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Kinematic Target Space", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the kinematic target space for a body - note that this won't actually make the body kinematic
- L327 _public function_ `FRigUnit_HierarchySetPhysicsBodyKinematicTargetSpace()`
- L333 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L338 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L342 _public member_ `EPhysicsControlKinematicTargetSpace KinematicTargetSpace = EPhysicsControlKinematicTargetSpace::OffsetInBoneSpace;` — `UPROPERTY(meta = (Input))` — The space for kinematic targets.

#### struct `FRigUnit_HierarchySetPhysicsBodyMovementType`  
`struct FRigUnit_HierarchySetPhysicsBodyMovementType : public FRigUnit_PhysicsBaseMutable`  
_L347-367_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Movement Mode", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the movement mode for this body.
- L351 _public function_ `FRigUnit_HierarchySetPhysicsBodyMovementType()`
- L357 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L362 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L366 _public member_ `EPhysicsMovementType MovementType = EPhysicsMovementType::Simulated;` — `UPROPERTY(meta = (Input))` — How the Physics Body should move when the Physics Solver is stepped.

#### struct `FRigUnit_HierarchySetPhysicsBodyCollisionType`  
`struct FRigUnit_HierarchySetPhysicsBodyCollisionType : public FRigUnit_PhysicsBaseMutable`  
_L371-391_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Collision Mode", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets what collision mode is used for this body
- L375 _public function_ `FRigUnit_HierarchySetPhysicsBodyCollisionType()`
- L381 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L386 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L390 _public member_ `TEnumAsByte<ECollisionEnabled::Type> CollisionType = ECollisionEnabled::QueryAndPhysics;` — `UPROPERTY(meta = (Input))` — What type of collision to use for the Physics Body

#### struct `FRigUnit_HierarchySetPhysicsBodyIncludeInChecksForReset`  
`struct FRigUnit_HierarchySetPhysicsBodyIncludeInChecksForReset : public FRigUnit_PhysicsBaseMutable`  
_L396-416_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Include In Checks For Reset", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets whether this body should be included in checks for resetting physics on the whole rig. Note: The flag is read by the solver each step, so this can be modified after physics instantiation.
- L400 _public function_ `FRigUnit_HierarchySetPhysicsBodyIncludeInChecksForReset()`
- L406 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L411 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L415 _public member_ `bool bInclude = true;` — `UPROPERTY(meta = (Input))` — Whether the Physics Body should be included when checking to see if the simulation should be reset.

#### struct `FRigUnit_HierarchySetPhysicsBodyMaterial`  
`struct FRigUnit_HierarchySetPhysicsBodyMaterial : public FRigUnit_PhysicsBaseMutable`  
_L422-442_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Material", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Applies the material settings to all the collision shapes. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L426 _public function_ `FRigUnit_HierarchySetPhysicsBodyMaterial()`
- L432 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L437 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L441 _public member_ `FRigPhysicsMaterial Material;` — `UPROPERTY(meta = (Input))` — The physics material to be used for collision on the Physics Body

#### struct `FRigUnit_HierarchySetPhysicsBodyGravityMultiplier`  
`struct FRigUnit_HierarchySetPhysicsBodyGravityMultiplier : public FRigUnit_PhysicsBaseMutable`  
_L446-466_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Gravity Multiplier", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the multiplier on gravity that should be applied to the body.
- L450 _public function_ `FRigUnit_HierarchySetPhysicsBodyGravityMultiplier()`
- L456 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L461 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L465 _public member_ `float GravityMultiplier = 1.0f;` — `UPROPERTY(meta = (Input))` — How much the Physics Body should respond to the gravity set in the Physics Solver

#### struct `FRigUnit_HierarchySetPhysicsBodyPhysicsBlendWeight`  
`struct FRigUnit_HierarchySetPhysicsBodyPhysicsBlendWeight : public FRigUnit_PhysicsBaseMutable`  
_L470-495_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Physics Blend Weight", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Controls the amount that the simulation is blended back into the target bones.
- L474 _public function_ `FRigUnit_HierarchySetPhysicsBodyPhysicsBlendWeight()`
- L480 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L485 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L494 _public member_ `float PhysicsBlendWeight = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — A per-body "alpha" on how much of the physics movement to apply to the target bone. The effective blend for this body is Alpha * PhysicsBlendWeight, applied at hierarchy writeback. A weight of zero leaves the bone at the input animation pose, but the body still simulates (and still affects neighbouring bodies through joints/contacts). Only the Step Physics Solver's Alpha pin triggers the cheap simulation-bypass pass-through. Setting every body's PhysicsBlendWeight to zero does not.

#### struct `FRigUnit_HierarchySetPhysicsBodyUpdateKinematicFromSimulation`  
`struct FRigUnit_HierarchySetPhysicsBodyUpdateKinematicFromSimulation : public FRigUnit_PhysicsBaseMutable`  
_L500-522_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Update Kinematic From Simulation", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: If true, then kinematic objects will be written back from simulation to the bones. This only necessary when either kinematic targets are being used, or when the target bone differs from the source bone.
- L504 _public function_ `FRigUnit_HierarchySetPhysicsBodyUpdateKinematicFromSimulation()`
- L510 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L515 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L521 _public member_ `bool bUpdateKinematicFromSimulation = true;` — `UPROPERTY(meta = (Input))` — When bodies are written back from simulation, if this is set to false, there is a small performance benefit to skipping bodies that are known to be kinematic, and when they are set to just track the input animation.

#### struct `FRigUnit_HierarchySetPhysicsBodyDamping`  
`struct FRigUnit_HierarchySetPhysicsBodyDamping : public FRigUnit_PhysicsBaseMutable`  
_L529-553_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Damping", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the linear and angular damping on the body. This will reduce the velocity, to make the body start tracking the simulation space. Note: Although damping is currently stored on Dynamics, the solver re-reads it each step, so this can be modified after physics instantiation.
- L533 _public function_ `FRigUnit_HierarchySetPhysicsBodyDamping()`
- L539 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L544 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L548 _public member_ `float LinearDamping = 0;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The desired linear damping
- L552 _public member_ `float AngularDamping = 0;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The desired angular damping

#### struct `FRigUnit_HierarchySetPhysicsBodyEnableCCD`  
`struct FRigUnit_HierarchySetPhysicsBodyEnableCCD : public FRigUnit_PhysicsBaseMutable`  
_L558-579_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Body Enable CCD", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Enable/disable CCD. Note that this can be expensive, so disable it when not needed! Requires CCD to be allowed in the solver.
- L562 _public function_ `FRigUnit_HierarchySetPhysicsBodyEnableCCD()`
- L568 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L573 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L578 _public member_ `bool bEnableCCD = false;` — `UPROPERTY(meta = (Input))` — Enable / disable CCD. Note that this can be expensive, so disable it when not needed! Requires CCD to be allowed in the solver.

#### struct `FRigUnit_HierarchyAddPhysicsBodyForce`  
`struct FRigUnit_HierarchyAddPhysicsBodyForce : public FRigUnit_PhysicsBaseMutable`  
_L586-611_
- reflection: `USTRUCT(meta = (DisplayName = "Add Force", Varying, Keywords = "Physics, Impulse, Torque, Acceleration, Velocity"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: This will add a force (or impulse, torque, velocity change etc) to the body. The force record will be stored in the physics body component, and then applied next time the solver is stepped, after which the record will be cleared.
- L590 _public function_ `FRigUnit_HierarchyAddPhysicsBodyForce()`
- L596 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L601 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L605 _public member_ `FPhysicsControlForceAndTorqueData ForceAndTorque;` — `UPROPERTY(meta = (Input))` — The desired force/torque to be applied
- L610 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The optional name of this force record. Used to identify the force records, and potentially delete it. Can be blank.

#### struct `FRigUnit_HierarchyRemovePhysicsBodyForce`  
`struct FRigUnit_HierarchyRemovePhysicsBodyForce : public FRigUnit_PhysicsBaseMutable`  
_L615-635_
- reflection: `USTRUCT(meta = (DisplayName = "Remove Force", Varying, Keywords = "Physics, Impulse, Torque, Acceleration, Velocity"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Removes all force records (assuming they hasn't been applied yet) with the given Name on the Body component.
- L619 _public function_ `FRigUnit_HierarchyRemovePhysicsBodyForce()`
- L625 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L630 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be updated
- L634 _public member_ `FName Name;` — `UPROPERTY(meta = (Input))` — The name of the force record to remove.

#### struct `FRigUnit_HierarchyGetPhysicsBodyTransform`  
`struct FRigUnit_HierarchyGetPhysicsBodyTransform : public FRigUnit_PhysicsBase`  
_L639-659_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Body Transform", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Retrieves the current simulation transform of the body.
- L643 _public function_ `FRigUnit_HierarchyGetPhysicsBodyTransform()`
- L649 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L654 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be queried
- L658 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Output))` — The current body transform.

#### struct `FRigUnit_HierarchyGetPhysicsBodyCoMTransform`  
`struct FRigUnit_HierarchyGetPhysicsBodyCoMTransform : public FRigUnit_PhysicsBase`  
_L663-683_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Body CoM Transform", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Retrieves the current simulation centre of mass transform of the body.
- L667 _public function_ `FRigUnit_HierarchyGetPhysicsBodyCoMTransform()`
- L673 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L678 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be queried
- L682 _public member_ `FTransform CoMTransform;` — `UPROPERTY(meta = (Output))` — The current centre of mass transform of the body.

#### struct `FRigUnit_HierarchyGetPhysicsBodyLinearVelocity`  
`struct FRigUnit_HierarchyGetPhysicsBodyLinearVelocity : public FRigUnit_PhysicsBase`  
_L687-707_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Body Linear Velocity", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Retrieves the current centre of mass linear velocity of the body.
- L691 _public function_ `FRigUnit_HierarchyGetPhysicsBodyLinearVelocity()`
- L697 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L702 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be queried
- L706 _public member_ `FVector LinearVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The current body linear velocity.

#### struct `FRigUnit_HierarchyGetPhysicsBodyAngularVelocity`  
`struct FRigUnit_HierarchyGetPhysicsBodyAngularVelocity : public FRigUnit_PhysicsBase`  
_L711-731_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Body Angular Velocity", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Retrieves the current centre of mass angular velocity of the body.
- L715 _public function_ `FRigUnit_HierarchyGetPhysicsBodyAngularVelocity()`
- L721 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L726 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be queried
- L730 _public member_ `FVector AngularVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The current body angular velocity.

#### struct `FRigUnit_HierarchyGetPhysicsBodyPointVelocity`  
`struct FRigUnit_HierarchyGetPhysicsBodyPointVelocity : public FRigUnit_PhysicsBase`  
_L735-763_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Body Point Velocity", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Retrieves the current linear velocity of the body at a point in space.
- L739 _public function_ `FRigUnit_HierarchyGetPhysicsBodyPointVelocity()`
- L745 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L750 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Body to be queried
- L754 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The position to calculate the velocity at.
- L758 _public member_ `EPhysicsControlSpace Space = EPhysicsControlSpace::Body;` — `UPROPERTY(meta = (Input))` — The space that Position is specified in.
- L762 _public member_ `FVector Velocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The current velocity at Position.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsControlComponent.h` (Public)


#### enum `ERigPhysicsControlComponentDirtyFlags`  
`enum class ERigPhysicsControlComponentDirtyFlags : uint8`  
_L12-18_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Data = 1 << 0` — Strength etc (not target)
- L16 _public enumerator_ `Target = 1 << 1`
- L17 _public enumerator_ `All = Data | Target`

#### struct `FRigPhysicsControlComponent`  
`struct FRigPhysicsControlComponent : public FRigBaseComponent`  
_L25-82_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- desc: A component that can be added to hierarchy elements (joints) to add the data required to control the simulation of them
- L32 _public function_ `FRigPhysicsControlComponent()`
- L43 _public member_ `FRigComponentKey ParentBodyComponentKey;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control)` — The body that controls the body being controlled. If this is dynamic, it will be affected too. If unset, then it implies a global control.
- L50 _public member_ `bool bUseParentBodyAsDefault = false;` — `UPROPERTY(BlueprintReadOnly, DisplayName = "Use Parent Body", EditAnywhere, Category = Control)` — If true, and if the parent body component key is not set, the parent body takes a default value, obtained by searching upwards in the hierarchy until a bone with a suitable physics body is found (if there is no body found, then the control will be inactive). If it is false, then this search is not done, so the control will be in simulation space.
- L54 _public member_ `FRigComponentKey ChildBodyComponentKey;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control)` — The body being controlled
- L58 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Control)` — Describes the initial strength etc of the new control
- L62 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Control)` — This is the currently active control multiplier.
- L66 _public member_ `FPhysicsControlTarget ControlTarget;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Control)` — Describes the initial target for the new control
- L69 _public member_ `mutable ERigPhysicsControlComponentDirtyFlags DirtyFlags = ERigPhysicsControlComponentDirtyFlags::All;` — Flags indicating what has been changed and needs to be set in the physics representation
- L71 _public prototype_ `virtual void Save(FArchive& A) override;`
- L72 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L74 _public prototype_ `virtual bool CanBeAddedTo( const FRigElementKey& InElementKey, const URigHierarchy* InHierarchy, FString* OutFailureReason) const override;`
- L77 _public prototype_ `virtual void OnRigHierarchyKeyChanged(const FRigHierarchyKey& InOldKey, const FRigHierarchyKey& InNewKey) override;`
- L79 _public function_ `virtual FName GetDefaultComponentName() const override`
- L81 _public function_ `static FName GetDefaultName()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`
- L19 _prototype_ `ENUM_CLASS_FLAGS(ERigPhysicsControlComponentDirtyFlags);`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsControlExecution.h` (Public)


#### struct `FRigUnit_AddPhysicsControl`  
`struct FRigUnit_AddPhysicsControl : public FRigUnit_PhysicsBaseMutable`  
_L16-67_
- reflection: `USTRUCT(meta = (Category = "RigPhysics", NodeColor = "1.0 0.6 0.3", DisplayName = "Spawn Physics Control", Keywords = "Add,Construction,Create,New,Control", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Adds a new physics control as a component on the owner element. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L20 _public function_ `FRigUnit_AddPhysicsControl()`
- L29 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L34 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L38 _public member_ `FRigComponentKey ControlComponentKey;` — `UPROPERTY(meta = (Output))` — The Physics Control component key that was created
- L42 _public member_ `FRigComponentKey ParentBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The optional body that "does" the controlling - though if it is dynamic then it can move too
- L46 _public member_ `bool bUseParentBodyAsDefault = false;` — `UPROPERTY(meta = (Input), DisplayName = "Use Parent Body")` — Whether or not to use the parent body (if one exists) as the Physics Control parent
- L50 _public member_ `FRigComponentKey ChildBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The body that is controlled
- L54 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(meta = (Input))` — Describes the initial strength etc of the new control
- L58 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — `UPROPERTY(meta = (Input))` — Fine control over the control strengths etc
- L62 _public member_ `FPhysicsControlTarget ControlTarget;` — `UPROPERTY(meta = (Input))` — The initial target for the new control

#### struct `FRigUnit_GetPhysicsControlExists`  
`struct FRigUnit_GetPhysicsControlExists : public FRigUnit_PhysicsBase`  
_L71-86_
- reflection: `USTRUCT(meta=(DisplayName="Get Physics Control Exists", Keywords="Query,Control"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Indicates whether the component exists and is a Physics Control
- L75 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L80 _public member_ `FRigComponentKey PhysicsControlComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigPhysicsControlComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The component key to check
- L85 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Physics Control

#### struct `FRigUnit_HierarchySetControlEnabled`  
`struct FRigUnit_HierarchySetControlEnabled : public FRigUnit_PhysicsBaseMutable`  
_L90-110_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Enabled", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets whether a control is enabled
- L94 _public function_ `FRigUnit_HierarchySetControlEnabled()`
- L100 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L105 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control that should be enabled or disabled
- L109 _public member_ `bool bEnabled = true;` — `UPROPERTY(meta = (Input))` — Whether or not the Physics Control should be enabled

#### struct `FRigUnit_HierarchySetControlCustomControlPoint`  
`struct FRigUnit_HierarchySetControlCustomControlPoint : public FRigUnit_PhysicsBaseMutable`  
_L114-138_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Custom Control Point", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the custom control point on a control
- L118 _public function_ `FRigUnit_HierarchySetControlCustomControlPoint()`
- L124 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L129 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L133 _public member_ `FVector CustomControlPoint = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The position of the control point relative to the child mesh, when using a custom control point.
- L137 _public member_ `bool bUseCustomControlPoint = true;` — `UPROPERTY(meta = (Input))` — Whether or not to use the custom control point position

#### struct `FRigUnit_HierarchySetControlData`  
`struct FRigUnit_HierarchySetControlData : public FRigUnit_PhysicsBaseMutable`  
_L143-163_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Data", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the control data for a physics control
- L147 _public function_ `FRigUnit_HierarchySetControlData()`
- L153 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L158 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L162 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(meta = (Input))` — The data (strengths etc) that should be set on the Physics Control

#### struct `FRigUnit_HierarchyGetControlData`  
`struct FRigUnit_HierarchyGetControlData : public FRigUnit_PhysicsBase`  
_L167-187_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Control Data", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Gets the control data for a physics control
- L171 _public function_ `FRigUnit_HierarchyGetControlData()`
- L177 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L182 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component from which to retrieve data
- L186 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(meta = (Output))` — The current control data (strengths etc)

#### struct `FRigUnit_HierarchySetControlLinearStrength`  
`struct FRigUnit_HierarchySetControlLinearStrength : public FRigUnit_PhysicsBaseMutable`  
_L191-215_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Linear Strength", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the Linear Strength of a Physics Control
- L195 _public function_ `FRigUnit_HierarchySetControlLinearStrength()`
- L201 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L206 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L214 _public member_ `float Strength = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The linear strength of the control. In the absence of any other influences, this is the frequency of oscillation when there is zero damping. For example, a strength of 2 would make the target oscillate twice per second (when there is no damping). Note that parent-space controls should this set to zero when they are controlling two bodies that are connected with a physics joint.

#### struct `FRigUnit_HierarchySetControlLinearDampingRatio`  
`struct FRigUnit_HierarchySetControlLinearDampingRatio : public FRigUnit_PhysicsBaseMutable`  
_L219-242_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Linear Damping Ratio", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the Linear Damping Ratio of a Physics Control
- L223 _public function_ `FRigUnit_HierarchySetControlLinearDampingRatio()`
- L229 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L234 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L241 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The linear damping ratio for the control. When this is 1, there is just enough damping to stop the control from oscillating about its target, due to the control strength (in the absence of any other influences). Values above this will add more damping, and values below will make the system tend to oscillate, as it will be under-ramped.

#### struct `FRigUnit_HierarchySetControlAngularStrength`  
`struct FRigUnit_HierarchySetControlAngularStrength : public FRigUnit_PhysicsBaseMutable`  
_L246-268_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Angular Strength", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the Angular Strength of a Physics Control
- L250 _public function_ `FRigUnit_HierarchySetControlAngularStrength()`
- L256 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L261 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L267 _public member_ `float Strength = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The angular strength of the control. In the absence of any other influences, this is the frequency of oscillation when there is zero damping. For example, a strength of 2 would make the target oscillate twice per second (when there is no damping).

#### struct `FRigUnit_HierarchySetControlAngularDampingRatio`  
`struct FRigUnit_HierarchySetControlAngularDampingRatio : public FRigUnit_PhysicsBaseMutable`  
_L272-295_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Angular Damping Ratio", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the Angular Damping Ratio of a Physics Control
- L276 _public function_ `FRigUnit_HierarchySetControlAngularDampingRatio()`
- L282 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L287 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L294 _public member_ `float DampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The angular damping ratio for the control. When this is 1, there is just enough damping to stop the control from oscillating about its target, due to the control strength (in the absence of any other influences). Values above this will add more damping, and values below will make the system tend to oscillate, as it will be under-ramped.

#### struct `FRigUnit_HierarchySetControlTargetVelocityMultipliers`  
`struct FRigUnit_HierarchySetControlTargetVelocityMultipliers : public FRigUnit_PhysicsBaseMutable`  
_L299-325_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Target Velocity Multipliers", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the Target velocity multipliers of a Physics Control
- L303 _public function_ `FRigUnit_HierarchySetControlTargetVelocityMultipliers()`
- L309 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L314 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L319 _public member_ `float LinearTargetVelocityMultiplier = 1.0f;` — `UPROPERTY(meta = (Input))` — The multiplier for the linear target velocity. Set this to zero to see sim-space damping. Set it to one to track the targets more closely.
- L324 _public member_ `float AngularTargetVelocityMultiplier = 1.0f;` — `UPROPERTY(meta = (Input))` — The multiplier for the angular target velocity. Set this to zero to see sim-space damping. Set it to one to track the targets more closely.

#### struct `FRigUnit_HierarchySetControlMultiplier`  
`struct FRigUnit_HierarchySetControlMultiplier : public FRigUnit_PhysicsBaseMutable`  
_L329-350_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Multiplier", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the multipliers for a physics control
- L333 _public function_ `FRigUnit_HierarchySetControlMultiplier()`
- L339 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L344 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L349 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — `UPROPERTY(meta = (Input))` — The multipliers to use on the control. These allow fine-grained control over the strengths (etc) in different directions.

#### struct `FRigUnit_HierarchySetControlDataAndMultiplier`  
`struct FRigUnit_HierarchySetControlDataAndMultiplier : public FRigUnit_PhysicsBaseMutable`  
_L354-378_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Data And Multiplier", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the control data and multiplier for a physics control
- L358 _public function_ `FRigUnit_HierarchySetControlDataAndMultiplier()`
- L364 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L369 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L373 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(meta = (Input))` — The control data (strengths etc) to use
- L377 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — `UPROPERTY(meta = (Input))` — Detail/per-direction multipliers on the control data

#### struct `FRigUnit_HierarchySetControlTarget`  
`struct FRigUnit_HierarchySetControlTarget : public FRigUnit_PhysicsBaseMutable`  
_L382-402_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Control Target", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the target for a physics control
- L386 _public function_ `FRigUnit_HierarchySetControlTarget()`
- L392 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L397 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L401 _public member_ `FPhysicsControlTarget ControlTarget;` — `UPROPERTY(meta = (Input))` — The target transform (etc) for the control

#### struct `FRigUnit_HierarchyUpdateControlTarget`  
`struct FRigUnit_HierarchyUpdateControlTarget : public FRigUnit_PhysicsBaseMutable`  
_L407-435_
- reflection: `USTRUCT(meta = (DisplayName = "Update Physics Control Target", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the target for a physics control and updates the target velocities based on the previous targets (which will be overwritten)
- L411 _public function_ `FRigUnit_HierarchyUpdateControlTarget()`
- L417 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L422 _public member_ `FRigComponentKey PhysicsControlComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Control component to be updated
- L426 _public member_ `FVector TargetPosition = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — The target position of the child body, relative to the parent body
- L430 _public member_ `FRotator TargetOrientation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — The target orientation of the child body, relative to the parent body
- L434 _public member_ `float DeltaTime = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The delta time used to calculate the target velocity

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsData.h` (Public)


#### struct `FRigPhysicsVisualizationSettings`  
`struct FRigPhysicsVisualizationSettings`  
_L33-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: Legacy visualization toggles for the rig's physics simulation. Enabling any bShow* flag activates the low-level Chaos debug draw - which has significant runtime cost - so disable everything before profiling.
- L42 _public member_ `bool bEnableVisualization = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Legacy master enable (has been replaced by FRigPhysicsVisualizationSettings1). Preserved so that nodes in existing assets keep their pin connections. Runtime gating is now done via CVar ControlRig.Physics.AllowVisualization combined with the per-element bShow* flags on FRigPhysicsVisualizationSettings1.
- L45 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))`
- L49 _public member_ `int32 ShapeSize = 1;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))` — Multiplier on the size things like limit shapes
- L52 _public member_ `int32 ShapeDetail = 16;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))`
- L55 _public member_ `bool bShowBodies = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L58 _public member_ `bool bShowCentreOfMass = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L61 _public member_ `bool bShowJoints = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L64 _public member_ `bool bShowControls = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L67 _public member_ `bool bShowWorldObjects = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L70 _public member_ `bool bShowWorldOverlapBox = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L75 _public member_ `bool bShowActiveContacts = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — If visualization is enabled, show active contacts. Note that this can be overridden using CVar ControlRig.Physics.ShowActiveContactsOverride
- L80 _public member_ `bool bShowInactiveContacts = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — If visualization is enabled, show inactive contacts. Note that this can be overridden using CVar ControlRig.Physics.ShowInactiveContactsOverride

#### struct `FRigPhysicsVisualizationSettings1`  
`struct FRigPhysicsVisualizationSettings1`  
_L88-134_
- reflection: `USTRUCT(BlueprintType)`
- desc: Visualization toggles for the rig's physics simulation. Enabling any bShow* flag activates the low-level Chaos debug draw - which has significant runtime cost - so disable everything before profiling. Visualization can also be globally suppressed at runtime via the CVar ControlRig.Physics.AllowVisualization (set to 0).
- L92 _public prototype_ `FRigPhysicsVisualizationSettings1() = default;`
- L95 _public prototype_ `FRigPhysicsVisualizationSettings1(const FRigPhysicsVisualizationSettings& Other);` — Does an "upgrade" from the old structure
- L98 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))`
- L102 _public member_ `int32 ShapeSize = 1;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))` — Multiplier on the size things like limit shapes
- L105 _public member_ `int32 ShapeDetail = 16;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (ClampMin = "0.0"))`
- L108 _public member_ `bool bShowBodies = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L111 _public member_ `bool bShowCentreOfMass = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L114 _public member_ `bool bShowJoints = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L117 _public member_ `bool bShowControls = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L120 _public member_ `bool bShowWorldObjects = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L123 _public member_ `bool bShowWorldOverlapBox = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L128 _public member_ `bool bShowActiveContacts = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — If visualization is enabled, show active contacts. Note that this can be overridden using CVar ControlRig.Physics.ShowActiveContactsOverride
- L133 _public member_ `bool bShowInactiveContacts = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — If visualization is enabled, show inactive contacts. Note that this can be overridden using CVar ControlRig.Physics.ShowInactiveContactsOverride

#### enum `ERigPhysicsWorldCollisionType`  
`enum class ERigPhysicsWorldCollisionType : uint8`  
_L138-149_
- reflection: `UENUM()`
- desc: Specifies whether/how simulation bodies should collide with the world
- L141 _public enumerator_ `None` — World collision is disabled
- L144 _public enumerator_ `Static` — Control rig simulation bodies will only collide against static (or kinematic, since they may move) objects in the world
- L146 _public enumerator_ `Dynamic` — Control rig simulation bodies will only collide against dynamic/simulated objects in the world
- L148 _public enumerator_ `All` — Control rig simulation bodies will collide against all objects in the world

#### enum `ERigPhysicsSimulationSpace`  
`enum class ERigPhysicsSimulationSpace : uint8`  
_L153-163_
- reflection: `UENUM()`
- desc: Specifies what space the simulation should run in
- L156 _public enumerator_ `World` — Simulate in world space. Moving the skeletal mesh will generate velocity changes
- L159 _public enumerator_ `Component` — Simulate in component space. Moving the entire skeletal mesh will have no affect on velocities unless this is explicitly enabled in the simulation space settings
- L162 _public enumerator_ `SpaceBone` — Simulate in the space of the specified bone. Moving the entire skeletal mesh and/or the Bone will have no affect on velocities unless this is explicitly enabled in the simulation space settings.

#### struct `FRigPhysicsCollisionShape`  
`struct FRigPhysicsCollisionShape`  
_L167-185_
- reflection: `USTRUCT(BlueprintType)`
- desc: Properties common to all collision shape types
- L174 _public member_ `float RestOffset = 0.0f;` — `UPROPERTY(Category = Shape, EditAnywhere, meta = (ClampMin = "0.0"))` — Offset used when generating contact points. This allows you to smooth out the Minkowski sum by radius R. Useful for making objects slide smoothly on top of irregularities
- L177 _public member_ `FName Name;` — `UPROPERTY(Category = Shape, EditAnywhere)`
- L182 _public member_ `bool bContributeToMass = true;` — `UPROPERTY(Category = Shape, EditAnywhere)` — True if this shape should contribute to the overall mass of the body it belongs to. This lets you create extra ollision volumes which do not affect the mass properties of an object.

#### struct `FRigPhysicsCollisionBox`  
`struct FRigPhysicsCollisionBox : public FRigPhysicsCollisionShape`  
_L189-205_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigPhysicsCollisionShape`
- desc: Box collision
- L193 _public function_ `FRigPhysicsCollisionBox(const FTransform& InTM, const FVector& InExtents) : TM(InTM), Extents(InExtents)`
- L195 _public function_ `FRigPhysicsCollisionBox()`
- L198 _public member_ `FTransform TM;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L202 _public member_ `FVector Extents = FVector::OneVector * RigPhysicsDefaultShapeSize;` — `UPROPERTY(EditAnywhere, Category = Shapes)` — These are the full extents of the box in each axis

#### struct `FRigPhysicsCollisionSphere`  
`struct FRigPhysicsCollisionSphere : public FRigPhysicsCollisionShape`  
_L209-225_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigPhysicsCollisionShape`
- desc: Sphere collision
- L213 _public function_ `FRigPhysicsCollisionSphere(const FTransform& InTM, const float InRadius) : TM(InTM), Radius(InRadius)`
- L216 _public function_ `FRigPhysicsCollisionSphere()`
- L219 _public member_ `FTransform TM;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L222 _public member_ `float Radius = RigPhysicsDefaultShapeSize;` — `UPROPERTY(EditAnywhere, Category = Shapes, meta = (ClampMin = "0.0"))`

#### struct `FRigPhysicsCollisionCapsule`  
`struct FRigPhysicsCollisionCapsule : public FRigPhysicsCollisionShape`  
_L229-248_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigPhysicsCollisionShape`
- desc: Capsule collision
- L233 _public function_ `FRigPhysicsCollisionCapsule(const FTransform& InTM, const float InRadius, const float InLength) : TM(InTM), Radius(InRadius), Length(InLength)`
- L235 _public function_ `FRigPhysicsCollisionCapsule()`
- L238 _public member_ `FTransform TM;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L241 _public member_ `float Radius = RigPhysicsDefaultShapeSize;` — `UPROPERTY(EditAnywhere, Category = Shapes, meta = (ClampMin = "0.0"))`
- L245 _public member_ `float Length = RigPhysicsDefaultShapeSize;` — `UPROPERTY(EditAnywhere, Category = Shapes, meta = (ClampMin = "0.0"))` — This is the length of the core part of the capsule. The total length will be Length + 2 * Radius

#### struct `FRigPhysicsCollisionConvex`  
`struct FRigPhysicsCollisionConvex : public FRigPhysicsCollisionShape`  
_L252-268_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigPhysicsCollisionShape`
- desc: Convex hull collision. VertexData holds the hull points in the element's local space
- L256 _public function_ `FRigPhysicsCollisionConvex(const FTransform& InTM, const TArray<FVector>& InVertexData) : TM(InTM), VertexData(InVertexData)`
- L258 _public function_ `FRigPhysicsCollisionConvex()`
- L261 _public member_ `FTransform TM;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L265 _public member_ `TArray<FVector> VertexData;` — `UPROPERTY(EditAnywhere, Category = Shapes)` — Hull vertices, in the element's local space.

#### enum `ERigPhysicsCombineMode`  
`enum class ERigPhysicsCombineMode : uint8`  
_L272-279_
- reflection: `UENUM(BlueprintType)`
- desc: How to combine friction/restitution values.
- L274 _public enumerator_ `Avg`
- L275 _public enumerator_ `Min`
- L276 _public enumerator_ `Multiply`
- L277 _public enumerator_ `Max`

#### struct `FRigPhysicsMaterial`  
`struct FRigPhysicsMaterial`  
_L283-305_
- reflection: `USTRUCT(BlueprintType)`
- desc: Material properties of a collision shapes.
- L291 _public member_ `float Friction = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (ClampMin = "0.0"))` — Friction is simplified here - just one value used for static and dynamic friction.
- L294 _public member_ `float Restitution = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (ClampMin = "0.0", ClampMax = "1.0"))`
- L299 _public member_ `ERigPhysicsCombineMode FrictionCombineMode = ERigPhysicsCombineMode::Multiply;` — `UPROPERTY(EditAnywhere, Category = Material)` — How to combine friction values. If the materials have different combine modes, then Max is used over Multiply, Multiply over Min and Min over Avg.
- L304 _public member_ `ERigPhysicsCombineMode RestitutionCombineMode = ERigPhysicsCombineMode::Multiply;` — `UPROPERTY(EditAnywhere, Category = Material)` — How to combine restitution values. If the materials have different combine modes, then Max is used over Multiply, Multiply over Min and Min over Avg.

#### struct `FRigPhysicsCollision`  
`struct FRigPhysicsCollision`  
_L309-332_
- reflection: `USTRUCT(BlueprintType)`
- desc: Collection of shapes that define the collision and (optionally) mass distribution of the body
- L316 _public member_ `TArray<FRigPhysicsCollisionBox> Boxes;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L319 _public member_ `TArray<FRigPhysicsCollisionSphere> Spheres;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L322 _public member_ `TArray<FRigPhysicsCollisionCapsule> Capsules;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L325 _public member_ `TArray<FRigPhysicsCollisionConvex> Convexes;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L328 _public member_ `FRigPhysicsMaterial Material;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L330 _public function_ `bool IsEmpty() const`
- L331 _public function_ `int32 NumShapes() const`

#### struct `FRigPhysicsSimulationSpaceSettings`  
`struct FRigPhysicsSimulationSpaceSettings`  
_L340-468_
- reflection: `USTRUCT(BlueprintType)`
- desc: Legacy bundled simulation-space settings. Retained as the input/output pin shape for the deprecated FRigUnit_AddPhysicsSolver, FRigUnit_SetPhysicsSolverSimulationSpaceSettings, and FRigUnit_GetPhysicsSolverSimulationSpaceSettings rig units only. New code should use FRigPhysicsSimulationSpaceMotion + FRigPhysicsTeleportDetectionSettings on FRigPhysicsSolverComponent instead.
- L348 _public member_ `float SpaceMovementAmount = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Overall multiplier on the effects of simulation space movement on the simulation
- L354 _public member_ `float VelocityScaleZ = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Multiplier on the components of vertical velocity of the simulation space that is passed to the simulation. Usually from 0.0 to 1.0 to reduce the effects of jumping and crouching on the simulation, but it can be higher than 1.0 if you need to exaggerate this motion for some reason.
- L357 _public member_ `bool bClampLinearVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L366 _public member_ `float MaxLinearVelocity = 10000;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearVelocity"))` — A clamp on the effective world-space velocity that is passed to the simulation. The default value effectively means "unlimited". It is not usually required to change this but you would reduce this to limit the effects of drag on the bodies in the simulation (if you have bodies that have LinearDrag set to non-zero in the physics asset). Expected values in this case would be somewhat less than the usual velocities of your object which is commonly a few hundred for a character.
- L369 _public member_ `bool bClampAngularVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L378 _public member_ `float MaxAngularVelocity = 10000;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularVelocity"))` — A clamp on the effective world-space angular velocity that is passed to the simulation. Units are radian/s, so a value of about 6.0 is one rotation per second. The default value effectively means "unlimited". You would reduce this (and MaxAngularAcceleration) to limit how much bodies "fly out" when the actor spins on the spot. This is especially useful if you have characters than can rotate very quickly and you would probably want values around or less than 10 in this case.
- L381 _public member_ `bool bClampLinearAcceleration = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L389 _public member_ `float MaxLinearAcceleration = 10000;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearAcceleration"))` — A clamp on the effective world-space acceleration that is passed to the simulation. The default value effectively means "unlimited". This property is used to stop the bodies of the simulation flying out when suddenly changing linear speed. It is useful when you have characters than can changes from stationary to running very quickly such as in an FPS. A common value for a character might be in the few hundreds.
- L392 _public member_ `bool bClampAngularAcceleration = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L399 _public member_ `float MaxAngularAcceleration = 10000;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularAcceleration"))` — A clamp on the effective world-space angular acceleration that is passed to the simulation. Units are radian/s/s. The default value effectively means "unlimited". This has a similar effect to MaxAngularVelocity, except that it is related to the flying out of bodies when the rotation speed suddenly changes. A typical value for a character might be around 100.
- L406 _public member_ `float LinearAccelerationThresholdForTeleport = 100000;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0"))` — If the linear acceleration is above this threshold, the movement is treated as a teleport. The calculated accelerations and velocities will be set to zero, without resetting the simulation state. A value of zero will disable this detection
- L413 _public member_ `float AngularAccelerationThresholdForTeleport = 100000;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0"))` — If the angular acceleration (deg/s/s) is above this threshold, the movement is treated as a teleport. The calculated accelerations and velocities will be set to zero, without resetting the simulation state. A value of zero will disable this detection
- L420 _public member_ `float PositionChangeThresholdForTeleport = 100;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0"))` — If the linear position change is above this threshold, the movement is treated as a teleport. The calculated accelerations and velocities will be set to zero, without resetting the simulation state. A value of zero will disable this detection
- L427 _public member_ `float OrientationChangeThresholdForTeleport = 30;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0"))` — If the angular change (degrees) is above this threshold, the movement is treated as a teleport. The calculated accelerations and velocities will be set to zero, without resetting the simulation state. A value of zero will disable this detection
- L433 _public member_ `float LinearDragMultiplier = 1.0;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation frame's linear velocity to pass onto the bodies (linear ether drag). This relies on there being drag authored on the bodies. If set to zero, the only drag will be from the body's local movement (in the simulation space).
- L439 _public member_ `float AngularDragMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation frame's angular velocity to pass onto the bodies (angular ether drag). This relies on there being drag authored on the bodies. If set to zero, the only drag will be from the body's local movement (in the simulation space).
- L448 _public member_ `FVector ExternalLinearDrag = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Additional linear drag from movement of the simulation space, applied to every body in addition to linear drag specified on them in the physics asset. When combined with ExternalLinearVelocity, this can be used to add a temporary wind-blown effect without having to tune linear drag on all the bodies in the physics asset. The result is that each body has a force equal to -ExternalLinearDrag * ExternalLinearVelocity applied to it, in addition to all other forces. The vector is in simulation local space.
- L455 _public member_ `FVector ExternalLinearVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Additional velocity that is added to the component velocity so the simulation acts as if the actor is moving at speed, even when stationary. The vector is in world space. This could be used for wind effects etc. Typical values are similar to the velocity of the object or effect, and usually around or less than 1000 for characters/wind.
- L462 _public member_ `FVector ExternalAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Additional angular velocity that is added to the component angular velocity. This can be used to make the simulation act as if the actor is rotating even when it is not. E.g., to apply physics to a character on a podium as the camera rotates around it, to emulate the podium itself rotating. Vector is in world space. Units are deg/s.
- L467 _public member_ `FVector ExternalTurbulenceVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — This will treat the external velocity like a wind field and add turbulence to it. Units are the same as velocity, so this is the approximate magnitude of the turbulence.

#### struct `FRigPhysicsInertialForceSettings`  
`struct FRigPhysicsInertialForceSettings`  
_L476-506_
- reflection: `USTRUCT(BlueprintType)`
- desc: Master gain plus per-term gains on the four pseudo-forces that Chaos Immediate Physics applies in non-world simulation space. The master Amount continues to act through input-vector pre-scaling (legacy Physics path); the per-term gains wire directly into the matching Chaos::FSimulationSpaceSettings::*Alpha fields. Field names mirror FRigDynamicsInertialForceSettings exactly. Effective gain on each pseudo-force term is Amount * <PerTerm>Amount.
- L485 _public member_ `float Amount = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Master multiplier on the effects of simulation space movement on the simulation. Acts as a uniform scalar applied alongside the per-term gains below.
- L490 _public member_ `float LinearEulerAmount = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Gain on the linear Euler pseudo-force (response to the actor's linear acceleration; -a_frame term). Wires to Chaos::FSimulationSpaceSettings::LinearAccelerationAlpha.
- L495 _public member_ `float AngularEulerAmount = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Gain on the angular Euler pseudo-force (alpha_frame x r term). Wires to Chaos::FSimulationSpaceSettings::EulerAlpha.
- L500 _public member_ `float CentrifugalAmount = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Gain on the centrifugal pseudo-force (-omega x (omega x r) term). Wires to Chaos::FSimulationSpaceSettings::CentrifugalAlpha.
- L505 _public member_ `float CoriolisAmount = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Gain on the Coriolis pseudo-force (-2 omega x v_p term). Wires to Chaos::FSimulationSpaceSettings::CoriolisAlpha.

#### struct `FRigPhysicsSimulationDragSettings`  
`struct FRigPhysicsSimulationDragSettings`  
_L513-558_
- reflection: `USTRUCT(BlueprintType)`
- desc: Drag-related settings applied to the whole simulation due to motion of the simulation space. Wraps the Chaos FSimulationSpaceSettings ether-drag fields plus the world-space wind/turbulence vectors. ExternalLinearDrag is a Chaos-only quantity in simulation-local space and has no Dynamics analogue.
- L523 _public member_ `float LinearDragMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation frame's linear velocity to pass onto the bodies (linear ether drag). This relies on there being drag authored on the bodies. If set to zero, the only drag will be from the body's local movement (in the simulation space).
- L529 _public member_ `float AngularDragMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation frame's angular velocity to pass onto the bodies (angular ether drag). This relies on there being drag authored on the bodies. If set to zero, the only drag will be from the body's local movement (in the simulation space).
- L538 _public member_ `FVector ExternalLinearDrag = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Additional linear drag from movement of the simulation space, applied to every body in addition to linear drag specified on them in the physics asset. When combined with ExternalLinearVelocity, this can be used to add a temporary wind-blown effect without having to tune linear drag on all the bodies in the physics asset. The result is that each body has a force equal to -ExternalLinearDrag * ExternalLinearVelocity applied to it, in addition to all other forces. The vector is in simulation local space.
- L545 _public member_ `FVector ExternalLinearVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Additional velocity that is added to the component velocity so the simulation acts as if the actor is moving at speed, even when stationary. The vector is in world space. This could be used for wind effects etc. Typical values are similar to the velocity of the object or effect, and usually around or less than 1000 for characters/wind.
- L552 _public member_ `FVector ExternalAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Additional angular velocity that is added to the component angular velocity. This can be used to make the simulation act as if the actor is rotating even when it is not. E.g., to apply physics to a character on a podium as the camera rotates around it, to emulate the podium itself rotating. Vector is in world space. Units are deg/s.
- L557 _public member_ `FVector ExternalTurbulenceVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings)` — This will treat the external velocity like a wind field and add turbulence to it. Units are the same as velocity, so this is the approximate magnitude of the turbulence.

#### struct `FRigPhysicsSimulationSpaceMotion`  
`struct FRigPhysicsSimulationSpaceMotion`  
_L564-620_
- reflection: `USTRUCT(BlueprintType)`
- desc: Conditioning of simulation-space velocity and acceleration before they reach the inertial-force and drag systems. Wraps the per-axis clamps and the vertical motion scale, and contains nested InertialForces and Drag substructs.
- L575 _public member_ `float VerticalMotionScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Multiplier on the vertical (Z) components of linear velocity AND acceleration of the simulation space that is passed to the simulation. Usually from 0.0 to 1.0 to reduce the effects of jumping and crouching on the simulation, but it can be higher than 1.0 if you need to exaggerate this motion for some reason.
- L578 _public member_ `bool bClampLinearVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L584 _public member_ `float MaxLinearVelocity = 10000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearVelocity"))` — A clamp on the effective world-space velocity that is passed to the simulation. The default value effectively means "unlimited". It is not usually required to change this but you would reduce this to limit the effects of drag on the bodies in the simulation.
- L587 _public member_ `bool bClampAngularVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L593 _public member_ `float MaxAngularVelocity = 10000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularVelocity"))` — A clamp on the effective world-space angular velocity that is passed to the simulation. Units are radian/s, so a value of about 6.0 is one rotation per second. The default value effectively means "unlimited".
- L596 _public member_ `bool bClampLinearAcceleration = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L602 _public member_ `float MaxLinearAcceleration = 10000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampLinearAcceleration"))` — A clamp on the effective world-space acceleration that is passed to the simulation. The default value effectively means "unlimited". This property is used to stop the bodies of the simulation flying out when suddenly changing linear speed.
- L605 _public member_ `bool bClampAngularAcceleration = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L610 _public member_ `float MaxAngularAcceleration = 10000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bClampAngularAcceleration"))` — A clamp on the effective world-space angular acceleration that is passed to the simulation. Units are radian/s/s. The default value effectively means "unlimited".
- L615 _public member_ `FRigPhysicsInertialForceSettings InertialForces;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ShowOnlyInnerProperties))` — Master and per-term gains on the simulation-space pseudo-forces (Linear-Euler, Angular-Euler, Centrifugal, Coriolis).
- L619 _public member_ `FRigPhysicsSimulationDragSettings Drag;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ShowOnlyInnerProperties))` — Drag and external-velocity settings (wind, turbulence, sim-local Chaos ether drag).

#### struct `FRigPhysicsTeleportDetectionSettings`  
`struct FRigPhysicsTeleportDetectionSettings`  
_L626-662_
- reflection: `USTRUCT(BlueprintType)`
- desc: Per-channel teleport-detection thresholds applied to raw simulation-space deltas. When any enabled threshold is crossed, the solver zeroes velocities/accelerations for the frame without resetting the simulation pose.
- L633 _public member_ `bool bFromPositionChange = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L638 _public member_ `float PositionChangeThreshold = 100.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromPositionChange"))` — If the linear position change (cm) is above this threshold, the movement is treated as a teleport.
- L641 _public member_ `bool bFromOrientationChange = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L646 _public member_ `float OrientationChangeThreshold = 30.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromOrientationChange"))` — If the angular change (degrees) is above this threshold, the movement is treated as a teleport.
- L649 _public member_ `bool bFromLinearAcceleration = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L653 _public member_ `float LinearAccelerationThreshold = 100000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromLinearAcceleration"))` — If the linear acceleration is above this threshold, the movement is treated as a teleport.
- L656 _public member_ `bool bFromAngularAcceleration = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L661 _public member_ `float AngularAccelerationThreshold = 100000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bFromAngularAcceleration"))` — If the angular acceleration (deg/s/s) is above this threshold, the movement is treated as a teleport.

#### struct `FRigPhysicsSolverSettings`  
`struct FRigPhysicsSolverSettings`  
_L666-836_
- reflection: `USTRUCT(BlueprintType)`
- desc: Configuration/settings for the physics solver
- L675 _public member_ `bool bAutomaticallyAddPhysicsBodyComponents = true;` — `UPROPERTY(EditAnywhere, Category = SolverSettings)` — If true, then any physics body component below (the element owning this one) will be automatically added to this solver, if its UseAutomaticSolver/AutoFindSolver flag is set.
- L678 _public member_ `ERigPhysicsSimulationSpace SimulationSpace = ERigPhysicsSimulationSpace::Component;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)`
- L682 _public member_ `ERigPhysicsSimulationSpace CollisionSpace = ERigPhysicsSimulationSpace::Component;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)` — The space in which collision shapes are defined
- L686 _public member_ `FRigElementKey SpaceBone;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings)` — The bone to use for the collision or simulation space (only relevant if one is set to BoneSpace)
- L690 _public member_ `FRigPhysicsCollision Collision;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SolverSettings, meta = (ShowOnlyInnerProperties))` — The collision shapes defined in the collision space - e.g. for representing a ground etc
- L693 _public member_ `FVector Gravity = FVector(0, 0, -981.0);` — `UPROPERTY(EditAnywhere, Category = SolverSettings)`
- L697 _public member_ `ERigPhysicsWorldCollisionType WorldCollisionType = ERigPhysicsWorldCollisionType::None;` — `UPROPERTY(EditAnywhere, Category = SolverSettings)` — Overlap type used to collect world objects. If set to None then there will be no world collisions.
- L702 _public member_ `bool bWorldCollisionIncludePhysics = true;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (EditCondition = "WorldCollisionType != ERigPhysicsWorldCollisionType::None"))` — Should world bodies with QueryAndPhysics collision type enabled be collided against. Only applies when WorldCollisionType is not none.
- L707 _public member_ `bool bWorldCollisionIncludeQuery = false;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (EditCondition = "WorldCollisionType != ERigPhysicsWorldCollisionType::None"))` — Should world bodies with Query collision types enabled be collided against. Only applies when WorldCollisionType is not none.
- L712 _public member_ `bool bWorldCollisionIncludeProbe = false;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (EditCondition = "WorldCollisionType != ERigPhysicsWorldCollisionType::None"))` — Should world bodies with Probe collision types enabled be collided against. Only applies when WorldCollisionType is not none.
- L716 _public member_ `float WorldCollisionBoundsExpansion = 1.1f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 1))` — Scales up the volume used to collect world objects for collision
- L721 _public member_ `int32 PositionIterations = 8;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — The number of position iterations to run. The position solve is responsible for de-penetration. Increasing this will improve simulation stability, but increase the cost.
- L726 _public member_ `int32 VelocityIterations = 4;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — The number of velocity iterations to run. The velocity solve is responsible for restitution (bounce) and friction. This should usually be a low value (even 1), but could be 0 if you don't care about friction and restitution.
- L734 _public member_ `int32 ProjectionIterations = 1;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — The number of projection iterations to run. The projection phase is a final pass over the constraints, applying a semi-physical correction to any joint errors remaining after the position and velocity solves. It can be very helpful to stabilize joint chains, but can cause issues with collision response. The projection magnitude can be controlled per-constraint in the constraint settings (assuming ProjectionIteration is not zero). This should be left as 1 in almost all cases.
- L739 _public member_ `int32 MaxNumRollingAverageStepTimes = 1;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 1))` — This sets how or if the step size should be smoothed. A value of one will disable smoothing, so that the physics simulation will match the Control Rig delta time.
- L745 _public member_ `float CollisionBoundsExpansion = 2.0f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — This is the distance margin around shapes used to detect collisions. Increasing this will increase the number of inactive contacts, which will reduce the likelihood of penetration, but will also increase solver cost.
- L751 _public member_ `float BoundsVelocityMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — Expands the shape bounds to detect potentially active contacts when moving. Increasing this (typically up to 1) will increase the number of inactive contacts, which will reduce the likelihood of penetration, but will also increase solver cost.
- L756 _public member_ `float MaxVelocityBoundsExpansion = 25.0f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — The maximum margin added due to movement. Reducing this can prevent excessive numbers of inactive contacts being generated.
- L760 _public member_ `float MaxDepenetrationVelocity = 0.0f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — When bodies are penetrating, this is the maximum velocity delta that can be applied in one frame.
- L768 _public member_ `float FixedTimeStep = 0.02f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — The recommended fixed timestep for the solver. Set to 0 to run with variable timestep, and set MaxDeltaTime to the desired sub-step time if you want to take sub-steps. NOTE: If this value is non-zero and less than the current frame time, the simulation will step multiple times which increases the cost.
- L772 _public member_ `int32 MaxTimeSteps = 10;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 1))` — The maximum number of solver steps that can be made
- L777 _public member_ `float MaxDeltaTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = SolverSettings, meta = (ClampMin = 0))` — If a variable timestep is in use, this is the maximum delta time that can be used. If this is smaller than the requested total delta time then multiple steps will be used.
- L784 _public member_ `bool bUseLinearJointSolver = true;` — `UPROPERTY(EditAnywhere, Category = SolverSettings)` — Whether to use the linear or non-linear solver for RBAN Joints. The linear solver is significantly cheaper than the non-linear solver when you are running multiple iterations, but is more likely to suffer from jitter. In general you should try to use the linear solver and increase the PositionIterations to improve stability if possible, only using the non-linear solver as a last resort.
- L788 _public member_ `bool bSolveJointPositionsLast = true;` — `UPROPERTY(EditAnywhere, Category = SolverSettings)` — When solving joints, whether to solve the positions last (as opposed to the orientations)
- L793 _public member_ `bool bUseManifolds = true;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — It enables the use of multi-point contact manifolds, which are created only once at the start of each tick. When disabled, a single-point contact is generated in each solver iteration which is more expensive.
- L797 _public member_ `bool bAllowCCD = false;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — Allows the solver to use the EnableCCD setting on the bodies
- L800 _public member_ `bool bResetFromPosition = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L805 _public member_ `float PositionThresholdForReset = 10000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bResetFromPosition"))` — If any object in the simulation exceeds this distance from the simulation origin, we will reset the pose and velocity of the entire simulation. This is to detect problems/explosions.
- L808 _public member_ `bool bResetFromKinematicSpeed = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L814 _public member_ `float KinematicSpeedThresholdForReset = 5000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bResetFromKinematicSpeed"))` — If any kinematic object in the simulation exceeds this speed, we will reset the velocities of all objects in the simulation. This is to detect problems - for example if the target animation has teleports etc.
- L817 _public member_ `bool bResetFromKinematicAcceleration = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L824 _public member_ `float KinematicAccelerationThresholdForReset = 100000.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bResetFromKinematicAcceleration"))` — If any kinematic object in the simulation exceeds this acceleration, we will reset the velocities of all objects in the simulation. This is to detect problems - for example if the target animation has teleports etc. A value of around 100000 will typically be a good place to start.
- L827 _public member_ `bool bResetFromEvaluationInterval = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L835 _public member_ `float EvaluationIntervalThresholdForReset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0", EditCondition = "bResetFromEvaluationInterval", Units = "Seconds"))` — If the time between successive solver evaluations (measured via the rig's absolute time) exceeds this value AND is also greater than the frame's delta time, the pose and velocities of all objects in the simulation are reset. This detects cases where evaluation was genuinely skipped - e.g. the rig stopped being ticked, or the editor was paused, without triggering just because the frame's delta time was rather large.

#### struct `FRigPhysicsDynamics`  
`struct FRigPhysicsDynamics`  
_L840-897_
- reflection: `USTRUCT(BlueprintType)`
- desc: Properties of a body affecting its dynamics (movement without regard to collision).
- L849 _public member_ `float Density = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Dynamics, meta = (EditCondition = "MassOverride <= 0"))` — Material density in g/cm^3, used to derive mass from the body's collision volume. Default 1.0 corresponds to water. Only used when MassOverride is zero or negative.
- L854 _public member_ `float MassOverride = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Dynamics)` — Explicit total mass for this body in kg. When positive this overrides the density-derived mass; when zero or negative the mass is computed from Density and the collision volume.
- L859 _public member_ `bool bOverrideCentreOfMass = false;` — `UPROPERTY(EditAnywhere, Category = Dynamics)` — When true, CentreOfMassOverride specifies the centre of mass position directly instead of computing it from the collision shapes.
- L863 _public member_ `FVector CentreOfMassOverride = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Dynamics, meta = (EditCondition = "bOverrideCentreOfMass"))` — Centre of mass in the body's local frame. Used only when bOverrideCentreOfMass is true.
- L867 _public member_ `FVector CentreOfMassNudge = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Dynamics)` — Offset added to the calculated (or overridden) centre of mass, in the body's local frame.
- L872 _public member_ `bool bOverrideMomentsOfInertia = false;` — `UPROPERTY(EditAnywhere, Category = Dynamics)` — When true, MomentsOfInertiaOverride specifies the diagonal of the inertia tensor directly instead of computing it from the collision shapes.
- L877 _public member_ `FVector MomentsOfInertiaOverride = FVector(1.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = Dynamics, meta = (EditCondition = "bOverrideMomentsOfInertia"))` — Diagonal moments of inertia (kg*cm^2) used when bOverrideMomentsOfInertia is true. Off-diagonal terms of the inertia tensor are assumed zero.
- L883 _public member_ `float LinearDamping = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0"))` — Linear velocity damping (1/s). Applied as exponential decay each frame and is mass- independent by default - the same setting produces identical decay for any mass. Set bScaleDampingByInverseMass to scale by inverse mass for drag-like behaviour.
- L889 _public member_ `float AngularDamping = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Dynamics, meta = (ClampMin = "0.0"))` — Angular velocity damping (1/s). Applied as exponential decay each frame and is mass- independent by default - the same setting produces identical decay for any mass. Set bScaleDampingByInverseMass to scale by inverse mass for drag-like behaviour.
- L896 _public member_ `bool bScaleDampingByInverseMass = false;` — `UPROPERTY(EditAnywhere, Category = Dynamics)` — When true, LinearDamping and AngularDamping are scaled by the body's inverse mass before being applied. This approximates aerodynamic drag where heavier bodies decelerate less under the same author setting. Not physically accurate for angular damping (true angular drag depends on inverse inertia, which is a tensor) but gives a reasonable effect.

#### struct `FRigPhysicsDriveData`  
`struct FRigPhysicsDriveData`  
_L902-922_
- reflection: `USTRUCT(BlueprintType)`
- desc: This represents the motor drive associated with a physics joint, that can drive the bodies towards a target pose.
- L909 _public member_ `FLinearDriveConstraint LinearDriveConstraint;` — `UPROPERTY(EditAnywhere, Category = LinearDrive)`
- L912 _public member_ `FAngularDriveConstraint AngularDriveConstraint;` — `UPROPERTY(EditAnywhere, Category = AngularDrive)`
- L917 _public member_ `bool bUseSkeletalAnimation = true;` — `UPROPERTY(EditAnywhere, Category = Drive)` — If true, then targets in the linear and angular drives will be applied on top of the pose from animation.
- L921 _public member_ `float SkeletalAnimationVelocityMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Drive)` — The amount of skeletal animation velocity to use in the targets

#### struct `FRigPhysicsLinearLimit`  
`struct FRigPhysicsLinearLimit`  
_L925-931_
- reflection: `USTRUCT(BlueprintType)`
- L930 _public member_ `FLinearConstraint LinearConstraint;` — `UPROPERTY(EditAnywhere, Category = Limit)`

#### struct `FRigPhysicsConeLimit`  
`struct FRigPhysicsConeLimit`  
_L934-940_
- reflection: `USTRUCT(BlueprintType)`
- L939 _public member_ `FConeConstraint ConeConstraint;` — `UPROPERTY(EditAnywhere, Category = Limit)`

#### struct `FRigPhysicsTwistLimit`  
`struct FRigPhysicsTwistLimit`  
_L943-949_
- reflection: `USTRUCT(BlueprintType)`
- L948 _public member_ `FTwistConstraint TwistConstraint;` — `UPROPERTY(EditAnywhere, Category = Limit)`

#### struct `FRigPhysicsJointData`  
`struct FRigPhysicsJointData`  
_L964-1018_
- reflection: `USTRUCT(BlueprintType)`
- desc: This represents an "articulation" - a general purpose "character joint" consisting of * A linear limit (a linear constraint), which is normally used to pin two bones together * An angular limit (an angular constraint), which is normally used to allow a limited range of rotational movement. The joint is defined by a parent frame, which is attached to the parent body, and a child frame which is attached to the child body. If the limits are all zero, then these two bodies will be held in a fixed pose. Normally the angular limit will be relaxed to allow rotational movement around the joint position. Most bodies in a character will have one Physics Joint which connects them to their parent in the hierarchy. However * The root of the hierarchy will not have an enabled Physics Joint * There may be times when a body has additional Physics Joints.
- L971 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Joint)`
- L976 _public member_ `bool bAutoCalculateParentOffset = true;` — `UPROPERTY(EditAnywhere, Category = Joint)` — The auto-calculated offset of the parent frame from the parent body places it at the location of the child body relative to the parent body in the initial pose.
- L980 _public member_ `FTransform ExtraParentOffset;` — `UPROPERTY(EditAnywhere, Category = Joint)` — The parent frame offset applied after any auto-calculation
- L984 _public member_ `bool bAutoCalculateChildOffset = true;` — `UPROPERTY(EditAnywhere, Category = Joint)` — The auto-calculated offset of the child frame is for it to be co-located with the child body.
- L988 _public member_ `FTransform ExtraChildOffset;` — `UPROPERTY(EditAnywhere, Category = Joint)` — The child frame offset applied after any auto-calculation
- L991 _public member_ `FLinearConstraint LinearConstraint;` — `UPROPERTY(EditAnywhere, Category = Joint)`
- L994 _public member_ `FConeConstraint ConeConstraint;` — `UPROPERTY(EditAnywhere, Category = Joint)`
- L997 _public member_ `FTwistConstraint TwistConstraint;` — `UPROPERTY(EditAnywhere, Category = Joint)`
- L1001 _public member_ `bool bDisableCollision = true;` — `UPROPERTY(EditAnywhere, Category = Joint)` — Disable collisions between the parent and child bodies
- L1006 _public member_ `float LinearProjectionAmount = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Joint, meta = (ClampMin = 0, ClampMax = 1))` — The amount of linear projection to reduce joint separation when the linear constraint is locked or has a hard limit. A value of one will apply full projection, but can introduce artefacts.
- L1012 _public member_ `float AngularProjectionAmount = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Joint, meta = (ClampMin = 0, ClampMax = 1))` — The amount of angular projection to reduce joint separation when the angular constraint is locked or has a hard limit. Note that projecting back to angular limits will often break the position projection, so it is normally better to disable this.
- L1017 _public member_ `float ParentInverseMassScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Joint, meta = (ClampMin = 0))` — As this is reduced to 0, the parent body becomes less affected by the motion of the child body, making the joint behave in one direction.

#### struct `FRigPhysicsBodySolverSettings`  
`struct FRigPhysicsBodySolverSettings`  
_L1022-1059_
- reflection: `USTRUCT(BlueprintType)`
- desc: Basic settings of the body in relation to the solver that are not covered elsewhere
- L1026 _public function_ `FRigPhysicsBodySolverSettings( FRigComponentKey InPhysicsSolverComponentKey = FRigComponentKey(), FRigElementKey InTargetBone = FRigElementKey()) : PhysicsSolverComponentKey(InPhysicsSolverComponentKey), TargetBone(InTargetBone)`
- L1035 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Note that setting the solver component, if known, has the benefit of avoiding the need to search for an automatic solver.
- L1041 _public member_ `bool bUseAutomaticSolver = true;` — `UPROPERTY(EditAnywhere, DisplayName="Auto Find Solver", Category = Solver)` — If true (and the physics solver is not explicitly set), then this component will be added to any physics solver that exists above it in the hierarchy, if that solver allows automatically adding physics components.
- L1046 _public member_ `FRigElementKey SourceBone;` — `UPROPERTY(EditAnywhere, Category = Solver)` — The bone that is used to initialize physics, as well as what to track when the body is set to be kinematic. Note that if this is unset, the it will default to the parent of our owner.
- L1051 _public member_ `FRigElementKey TargetBone;` — `UPROPERTY(EditAnywhere, Category = Solver)` — The bone that is written to following simulation. Note that if this is unset, the it will default to the parent of our owner.
- L1056 _public member_ `bool bIncludeInChecksForReset = true;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Whether to include this bone in checks for whether we should reset physics on the whole rig, using thresholds in the solver. Set to false for bodies you know may jump around safely when kinematic.
- L1058 _public prototype_ `void OnRigHierarchyKeyChanged(const FRigHierarchyKey& InOldKey, const FRigHierarchyKey& InNewKey);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`
- L23 _variable_ `const float RigPhysicsDefaultShapeSize = 10.0f;`
- L25 _prototype_ `FArchive& operator <<(FArchive& Ar, FConstraintDrive& Data);`
- L26 _prototype_ `FArchive& operator <<(FArchive& Ar, FLinearDriveConstraint& Data);`
- L27 _prototype_ `FArchive& operator <<(FArchive& Ar, FAngularDriveConstraint& Data);`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsExecution.h` (Public)


#### struct `FRigUnit_PhysicsBaseMutable`  
`struct FRigUnit_PhysicsBaseMutable: public FRigUnitMutable`  
_L17-20_
- reflection: `USTRUCT(meta = (Category = "RigPhysics", NodeColor = "1.0 0.6 0.3", Keywords = "Physics", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnitMutable`
- desc: Base struct for all other mutable physics nodes

#### struct `FRigUnit_PhysicsBase`  
`struct FRigUnit_PhysicsBase : public FRigUnit`  
_L24-27_
- reflection: `USTRUCT(meta = (Category = "RigPhysics", NodeColor = "1.0 0.6 0.3", Keywords = "Physics", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnit`
- desc: Base struct for all other non-mutable physics nodes

#### struct `FRigUnit_AddPhysicsComponents`  
`struct FRigUnit_AddPhysicsComponents : public FRigUnit_PhysicsBaseMutable`  
_L33-110_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Physics Components", Keywords = "Add,Construction,Create,New,Body,Joint,Control", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Adds a set of physics components including the body, joint and controls. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L37 _public function_ `FRigUnit_AddPhysicsComponents()`
- L44 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L49 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L53 _public member_ `bool bAddJoint = true;` — `UPROPERTY(meta = (Input))` — Whether to add a Physics Joint
- L57 _public member_ `bool bAddSimSpaceControl = true;` — `UPROPERTY(meta = (Input))` — Whether to add a simulation-space Physics Control
- L61 _public member_ `bool bAddParentSpaceControl = true;` — `UPROPERTY(meta = (Input))` — Whether to add a parent-space Physics Control
- L65 _public member_ `FRigComponentKey PhysicsBodyComponentKey;` — `UPROPERTY(meta = (Output))` — The component key of the Physics Body
- L69 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Output))` — The component key of the Physics Joint, if created
- L73 _public member_ `FRigComponentKey SimSpaceControlComponentKey;` — `UPROPERTY(meta = (Output))` — The component key of the simulation-space Physics Control, if created
- L77 _public member_ `FRigComponentKey ParentSpaceControlComponentKey;` — `UPROPERTY(meta = (Output))` — The component key of the parent-space Physics Control, if created
- L81 _public member_ `FRigPhysicsBodySolverSettings Solver;` — `UPROPERTY(meta = (Input))` — The solver to relate this new physics element to
- L85 _public member_ `FRigPhysicsDynamics Dynamics;` — `UPROPERTY(meta = (Input))` — The dynamics properties of the new physics body
- L89 _public member_ `FRigPhysicsCollision Collision;` — `UPROPERTY(meta = (Input))` — The collision properties of the new physics body
- L93 _public member_ `FPhysicsControlModifierData BodyData;` — `UPROPERTY(meta = (Input))` — The runtime modifiable data of the new physics body
- L97 _public member_ `FRigPhysicsJointData JointData;` — `UPROPERTY(meta = (Input))` — The properties of the joint
- L101 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(meta = (Input))` — Optional motor/drive associated with the physics joint
- L105 _public member_ `FPhysicsControlData SimSpaceControlData;` — `UPROPERTY(meta = (Input))` — Data for the simulation space control
- L109 _public member_ `FPhysicsControlData ParentSpaceControlData;` — `UPROPERTY(meta = (Input))` — Data for the parent space control

#### struct `FRigUnit_HierarchyImportCollisionFromPhysicsAsset`  
`struct FRigUnit_HierarchyImportCollisionFromPhysicsAsset : public FRigUnit_PhysicsBaseMutable`  
_L117-165_
- reflection: `USTRUCT(meta = (DisplayName = "Import Collision From Physics Asset", Keywords = "Construction,Create,New", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Imports/creates bones from the physics asset and creates collision for them. The bones will lose their hierarchy and be placed under the specified parent - ready to be moved around. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L121 _public function_ `FRigUnit_HierarchyImportCollisionFromPhysicsAsset()`
- L127 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L133 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — Note that setting the solver component, if known, has the benefit of avoiding the need to search for an automatic solver.
- L139 _public member_ `bool bUseAutomaticSolver = true;` — `UPROPERTY(meta = (Input))` — If true (and the physics solver is not explicitly set), then this component will be added to any physics solver that exists above it in the hierarchy, if that solver allows automatically adding physics components.
- L143 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(meta = (Input))` — The physics asset to import collision from
- L148 _public member_ `TArray<FName> BonesToUse;` — `UPROPERTY(meta = (Input, DisplayName = "Bone Mask"))` — If this is empty, then all bones with bodies in the physics asset will be created. Otherwise only bodies that relate to the specified bones will be created.
- L152 _public member_ `FName NameSpace = "Ph` — `UPROPERTY(meta = (Input))` — Prefix to the bone names
- L156 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input))` — Parent/owner for all the new bones
- L160 _public member_ `TArray<FRigElementKey> BoneKeys;` — `UPROPERTY(meta = (Output))` — The element keys of the bones that were created to own the physics bodies
- L164 _public member_ `TArray<FRigComponentKey> PhysicsBodyComponentKeys;` — `UPROPERTY(meta = (Output))` — The Physics Body component keys that were created

#### struct `FRigUnit_HierarchyInstantiateFromPhysicsAsset`  
`struct FRigUnit_HierarchyInstantiateFromPhysicsAsset : public FRigUnit_PhysicsBaseMutable`  
_L172-260_
- reflection: `USTRUCT(meta = (DisplayName = "Instantiate From Physics Asset", Keywords = "Construction,Create,New", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Creates multiple physics components based on the supplied physics asset. Note that the resulting simulation bodies may not precisely match the physics asset. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L176 _public function_ `FRigUnit_HierarchyInstantiateFromPhysicsAsset()`
- L182 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L188 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — Note that setting the solver component, if known, has the benefit of avoiding the need to search for an automatic solver.
- L194 _public member_ `bool bUseAutomaticSolver = true;` — `UPROPERTY(meta = (Input))` — If true (and the physics solver is not explicitly set), then this component will be added to any physics solver that exists above it in the hierarchy, if that solver allows automatically adding physics components.
- L198 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(meta = (Input))` — The Physics Asset to instantiate from
- L202 _public member_ `FName ConstraintProfileName;` — `UPROPERTY(meta = (Input))` — Name of the constraint profile to use. If empty (or invalid), the default profile will be used
- L207 _public member_ `TArray<FRigElementKey> BonesToUse;` — `UPROPERTY(meta = (Input, DisplayName = "Bone Mask"))` — If this is empty, then all bodies in the physics asset that match a bone in the hierarchy will be created. Otherwise only bodies that relate to the specified bones will be created.
- L212 _public member_ `bool bEnableJoints = true;` — `UPROPERTY(meta = (Input))` — Whether to enable the joints authored in the physics asset. Note that you can't have drives without joints.
- L217 _public member_ `bool bEnableDrives = true;` — `UPROPERTY(meta = (Input))` — Whether to enable the drives authored in the physics asset. Note that if you are creating parent space controls, you may not want the drives
- L221 _public member_ `bool bAddSimSpaceControl = false;` — `UPROPERTY(meta = (Input))` — Whether to create a simulation-space control for each body that was created
- L227 _public member_ `bool bAddParentSpaceControl = false;` — `UPROPERTY(meta = (Input))` — Whether to create a parent-space control for each body that was created. Note that if this is set to true, then it will be created for the root-most body in the physics asset too. This is often not needed, so make sure it isn't enabled if you don't want it to be.
- L235 _public member_ `bool bMakeHelperBodies = true;` — `UPROPERTY(meta = (Input))` — If true, and BonesToUse/BoneMask is being used to create a subset of the physics asset, then helper bodies will be created when needed: Kinematic bodies on bones that are connected by a physics joint to those in BonesToUse/BoneMask. This is used so that (a) instantiating individual chains can be done without explicitly including the parent (in the physics joint sense) body, and (b) entire physics assets can be made from multiple calls to instantiate individual chains.
- L239 _public member_ `FPhysicsControlData SimSpaceControlData;` — `UPROPERTY(meta = (Input))` — Data for the simulation space control
- L243 _public member_ `FPhysicsControlData ParentSpaceControlData;` — `UPROPERTY(meta = (Input))` — Data for the parent space control
- L247 _public member_ `TArray<FRigComponentKey> PhysicsBodyComponentKeys;` — `UPROPERTY(meta = (Output))` — The Physics Body component keys that were created
- L251 _public member_ `TArray<FRigComponentKey> PhysicsJointComponentKeys;` — `UPROPERTY(meta = (Output))` — The Physics Joint component keys that were created
- L255 _public member_ `TArray<FRigComponentKey> SimSpaceControlComponentKeys;` — `UPROPERTY(meta = (Output))` — The simulation-space Physics Control component keys that were created
- L259 _public member_ `TArray<FRigComponentKey> ParentSpaceControlComponentKeys;` — `UPROPERTY(meta = (Output))` — The parent-space Physics Control component keys that were created

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsJointComponent.h` (Public)


#### enum `ERigPhysicsJointComponentDirtyFlags`  
`enum class ERigPhysicsJointComponentDirtyFlags : uint8`  
_L12-18_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Joint = 1 << 0`
- L16 _public enumerator_ `Drive = 1 << 1`
- L17 _public enumerator_ `All = Joint | Drive`

#### struct `FRigPhysicsJointComponent`  
`struct FRigPhysicsJointComponent : public FRigBaseComponent`  
_L22-70_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L29 _public function_ `FRigPhysicsJointComponent()`
- L41 _public member_ `FRigComponentKey ParentBodyComponentKey;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control)` — The parent body of the joint. If unset, then the system will try to find a suitable body by looking for a parent/grandparent of the owner etc that contains a body that is in the same solver as the child body.
- L46 _public member_ `FRigComponentKey ChildBodyComponentKey;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Control)` — The child body of the joint. If unset, then the system will try to find a suitable body amongst the body components under owner.
- L50 _public member_ `FRigPhysicsJointData JointData;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics, meta = (ShowOnlyInnerProperties))` — The properties of the joint
- L54 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Physics, meta = (ShowOnlyInnerProperties))` — Optional motor/drive associated with the physics joint
- L57 _public member_ `mutable ERigPhysicsJointComponentDirtyFlags DirtyFlags = ERigPhysicsJointComponentDirtyFlags::All;` — Flags indicating what has been changed and needs to be set in the physics representation
- L59 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L60 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L62 _public prototype_ `virtual bool CanBeAddedTo( const FRigElementKey& InElementKey, const URigHierarchy* InHierarchy, FString* OutFailureReason) const override;`
- L65 _public prototype_ `virtual void OnRigHierarchyKeyChanged(const FRigHierarchyKey& InOldKey, const FRigHierarchyKey& InNewKey) override;`
- L67 _public function_ `virtual FName GetDefaultComponentName() const override`
- L69 _public function_ `static FName GetDefaultName()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`
- L19 _prototype_ `ENUM_CLASS_FLAGS(ERigPhysicsJointComponentDirtyFlags);`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsJointExecution.h` (Public)


#### struct `FRigUnit_AddPhysicsJoint`  
`struct FRigUnit_AddPhysicsJoint : public FRigUnit_PhysicsBaseMutable`  
_L16-58_
- reflection: `USTRUCT(meta = (DisplayName = "Spawn Physics Joint", Keywords = "Add,Construction,Create,New,Joint,Articulation,Constraint,Skeleton", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Adds a new Physics Joint as a component on the owner element. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L20 _public function_ `FRigUnit_AddPhysicsJoint()`
- L29 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L34 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L38 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Output))` — The Physics Joint component key that was created
- L44 _public member_ `FRigComponentKey ParentBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The parent body of the joint. If unset, then the system will try to find a suitable body by looking for a parent/grandparent of the owner etc that contains a body that is in the same solver as the child body.
- L49 _public member_ `FRigComponentKey ChildBodyComponentKey;` — `UPROPERTY(meta = (Input))` — The child body of the joint. If unset, then the system will try to find a suitable body amongst the body components under owner.
- L53 _public member_ `FRigPhysicsJointData JointData;` — `UPROPERTY(meta = (Input))` — The properties of the joint
- L57 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(meta = (Input))` — Optional motor/drive associated with the physics joint

#### struct `FRigUnit_GetPhysicsJointExists`  
`struct FRigUnit_GetPhysicsJointExists : public FRigUnit_PhysicsBase`  
_L62-77_
- reflection: `USTRUCT(meta=(DisplayName="Get Physics Joint Exists", Keywords="Query,Joint,Articulation,Constraint"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Indicates whether the component exists and is a Physics Joint
- L66 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L71 _public member_ `FRigComponentKey PhysicsJointComponentKey = FRigComponentKey( FRigElementKey(TEXT(""), ERigElementType::Bone), FRigPhysicsJointComponent::GetDefaultName());` — `UPROPERTY(meta = (Input))` — The component key to check
- L76 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Physics Joint

#### struct `FRigUnit_HierarchySetJointData`  
`struct FRigUnit_HierarchySetJointData : public FRigUnit_PhysicsBaseMutable`  
_L81-101_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Properties", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the joint data for a physics joint component
- L85 _public function_ `FRigUnit_HierarchySetJointData()`
- L91 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L96 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L100 _public member_ `FRigPhysicsJointData JointData;` — `UPROPERTY(meta = (Input))` — The physics joint data (limit and drive properties) to be used

#### struct `FRigUnit_HierarchyGetJointData`  
`struct FRigUnit_HierarchyGetJointData : public FRigUnit_PhysicsBase`  
_L105-125_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Joint Properties"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Gets the joint data for a physics joint component
- L109 _public function_ `FRigUnit_HierarchyGetJointData()`
- L115 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L120 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint from which to retrieve data
- L124 _public member_ `FRigPhysicsJointData JointData;` — `UPROPERTY(meta = (Output))` — The current Physics Joint data (state of limits and drives)

#### struct `FRigUnit_HierarchySetJointLinearLimit`  
`struct FRigUnit_HierarchySetJointLinearLimit : public FRigUnit_PhysicsBaseMutable`  
_L129-149_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Linear Constraint Limit", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the joint linear limit
- L133 _public function_ `FRigUnit_HierarchySetJointLinearLimit()`
- L139 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L144 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L148 _public member_ `FRigPhysicsLinearLimit LinearLimit;` — `UPROPERTY(meta = (Input))` — The linear constraint to be used

#### struct `FRigUnit_HierarchySetJointConeLimit`  
`struct FRigUnit_HierarchySetJointConeLimit : public FRigUnit_PhysicsBaseMutable`  
_L153-173_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Cone Constraint Limit", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the joint cone limit
- L157 _public function_ `FRigUnit_HierarchySetJointConeLimit()`
- L163 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L168 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L172 _public member_ `FRigPhysicsConeLimit ConeLimit;` — `UPROPERTY(meta = (Input))` — The cone limit

#### struct `FRigUnit_HierarchySetJointTwistLimit`  
`struct FRigUnit_HierarchySetJointTwistLimit : public FRigUnit_PhysicsBaseMutable`  
_L177-197_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Twist Constraint Limit", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the joint twist limit
- L181 _public function_ `FRigUnit_HierarchySetJointTwistLimit()`
- L187 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L192 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L196 _public member_ `FRigPhysicsTwistLimit TwistLimit;` — `UPROPERTY(meta = (Input))` — The twist limit

#### struct `FRigUnit_HierarchySetJointEnabled`  
`struct FRigUnit_HierarchySetJointEnabled : public FRigUnit_PhysicsBaseMutable`  
_L201-221_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Enabled", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Specifies whether a Physics Joint should be enabled or not
- L205 _public function_ `FRigUnit_HierarchySetJointEnabled()`
- L211 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L216 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L220 _public member_ `bool bEnabled = true;` — `UPROPERTY(meta = (Input))` — Whether or not the joint should be enabled. Disabling the joint will disable any limits and drives

#### struct `FRigUnit_HierarchySetJointDriveData`  
`struct FRigUnit_HierarchySetJointDriveData : public FRigUnit_PhysicsBaseMutable`  
_L225-245_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Drive Properties", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the joint drive for a physics component body
- L229 _public function_ `FRigUnit_HierarchySetJointDriveData()`
- L235 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L240 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L244 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(meta = (Input))` — The Physics Joint drive data that should be used

#### struct `FRigUnit_HierarchyGetJointDriveData`  
`struct FRigUnit_HierarchyGetJointDriveData : public FRigUnit_PhysicsBase`  
_L249-269_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Joint Drive Properties"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Gets the joint drive for a physics joint component
- L253 _public function_ `FRigUnit_HierarchyGetJointDriveData()`
- L259 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L264 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint from which to retrieve data
- L268 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(meta = (Output))` — The current Physics Joint Drive data

#### struct `FRigUnit_HierarchySetJointDriveUseSkeletalAnimation`  
`struct FRigUnit_HierarchySetJointDriveUseSkeletalAnimation : public FRigUnit_PhysicsBaseMutable`  
_L273-294_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Joint Drive Use Skeletal Animation", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the joint drive for a physics component body
- L277 _public function_ `FRigUnit_HierarchySetJointDriveUseSkeletalAnimation()`
- L283 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L288 _public member_ `FRigComponentKey PhysicsJointComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Joint to be updated
- L293 _public member_ `bool bUseSkeletalAnimation = true;` — `UPROPERTY(meta = (Input))` — Whether the drive targets should be relative to the incoming animation pose. If set to true (and the drive targets are zero), then the drives will track the target animation.

#### struct `FRigUnit_MakeArticulationJointData`  
`struct FRigUnit_MakeArticulationJointData : public FRigUnit_PhysicsBase`  
_L299-325_
- reflection: `USTRUCT(meta = (DisplayName = "Make Articulation Joint Data", Keywords = "Construction,Create,New,Body,Skeleton", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Helper to simplify creation of joint data for a typical articulation (i.e. locked linear motion, but with an angular limit)
- L303 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L309 _public member_ `FVector AngularLimit = FVector(-1, -1, -1);` — `UPROPERTY(meta = (Input, ClampMin = "-1.0"))` — The angular limit in Degrees (twist, swing1, swing2) -ve indicates the limit range is free
- L315 _public member_ `FVector SoftStrength = FVector(-1, -1, -1);` — `UPROPERTY(meta = (Input, ClampMin = "-1.0"))` — If limited, then this will be used to control the softness of the limit -ve indicates the limit is hard A value of 1 is reasonably soft
- L319 _public member_ `FVector SoftDampingRatio = FVector(1, 1, 1);` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — If limited, then this will be used to control the damping ratio of the limit
- L324 _public member_ `FRigPhysicsJointData JointData;` — `UPROPERTY(meta = (Output))` — Joint data that can be used in a Physics Joint, calculated according to the values set here, and configured to act as a "normal" articulation joint.

#### struct `FRigUnit_MakeArticulationDriveData`  
`struct FRigUnit_MakeArticulationDriveData : public FRigUnit_PhysicsBase`  
_L330-368_
- reflection: `USTRUCT(meta = (DisplayName = "Make Articulation Drive Data", Keywords = "Construction,Create,New,Body,Skeleton", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Helper to simplify creation of drive data for a typical articulation (i.e. no linear drive, but with an angular drive)
- L334 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L339 _public member_ `bool bEnableAngularDrive = true;` — Whether to enable the angular drive
- L347 _public member_ `float AngularStrength = 10.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The strength used to drive angular motion
- L354 _public member_ `float AngularDampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of damping associated with the angular strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L359 _public member_ `float AngularExtraDamping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of additional angular damping. This is added to the damping that comes from AngularDampingRatio and can be useful when you want damping even when AngularStrength is zero.
- L363 _public member_ `float SkeletalAnimationVelocityMultiplier = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of skeletal animation velocity to use in the targets
- L367 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(meta = (Output))` — The drive data that can be set in a Physics Joint, reflecting the setup specified here.

#### struct `FRigUnit_MakeDriveData`  
`struct FRigUnit_MakeDriveData : public FRigUnit_PhysicsBase`  
_L372-429_
- reflection: `USTRUCT(meta = (DisplayName = "Make Drive Data", Keywords = "Construction,Create,New,Body,Skeleton", Varying))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Helper to simplify creation of drive data
- L376 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L381 _public member_ `bool bEnableLinearDrive = false;` — `UPROPERTY(meta = (Input))` — Whether to enable the linear drive (not normally used for character joints)
- L385 _public member_ `float LinearStrength = 10.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The strength used to drive linear motion
- L392 _public member_ `float LinearDampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of damping associated with the linear strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L397 _public member_ `float LinearExtraDamping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of additional linear damping. This is added to the damping that comes from LinearDampingRatio and can be useful when you want damping even when LinearStrength is zero.
- L401 _public member_ `bool bEnableAngularDrive = true;` — `UPROPERTY(meta = (Input))` — Whether to enable the angular drive
- L409 _public member_ `float AngularStrength = 10.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The strength used to drive angular motion
- L415 _public member_ `float AngularDampingRatio = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of damping associated with the angular strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L420 _public member_ `float AngularExtraDamping = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of additional angular damping. This is added to the damping that comes from AngularDampingRatio and can be useful when you want damping even when AngularStrength is zero.
- L424 _public member_ `float SkeletalAnimationVelocityMultiplier = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — The amount of skeletal animation velocity to use in the targets
- L428 _public member_ `FRigPhysicsDriveData DriveData;` — `UPROPERTY(meta = (Output))` — The drive data, representing the properties specified here, that can be set on a Physics Joint

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsSolverComponent.h` (Public)


#### struct `FRigPhysicsSolverComponent`  
`struct FRigPhysicsSolverComponent : public FRigBaseComponent`  
_L19-68_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigBaseComponent`
- L24 _public prototype_ `DECLARE_RIG_COMPONENT_METHODS(FRigPhysicsSolverComponent) UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics, meta = (ShowOnlyInnerProperties)) FRigPhysicsSolverSettings SolverSettings;`
- L30 _public member_ `FRigPhysicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics, meta = (ShowOnlyInnerProperties))`
- L33 _public member_ `FRigPhysicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics, meta = (ShowOnlyInnerProperties))`
- L38 _public member_ `int32 TrackInputCounter = 0;` — If we have to reset, then we can be told to track the input kinematically for a number of frames - this will be set > 0 and will be decremented each update. When it reaches 0, things can go to the desired simulation state.
- L40 _public prototype_ `virtual void Save(FArchive& Ar) override;`
- L41 _public prototype_ `virtual void Load(FArchive& Ar) override;`
- L44 _public prototype_ `virtual const FSlateIcon& GetIconForUI() const override;`
- L47 _public prototype_ `virtual void OnAddedToHierarchy(URigHierarchy* InHierarchy, URigHierarchyController* InController) override;`
- L49 _public function_ `virtual FName GetDefaultComponentName() const override`
- L50 _public function_ `static FName GetDefaultName()`
- L55 _public prototype_ `FRigPhysicsSolver* GetPhysicsSolver() const;` — This will make the internally owned solver if necessary, and return it. Note that there's no danger of this being called concurrently from different threads, since each FRigPhysicsSolver is owned by just one rig.
- L67 _private member_ `mutable TSharedPtr<FRigPhysicsSolver> PhysicsSolverPtr;` — We use a TSharedPtr here to share access/ownership with the game-thread world collisions task. We make it mutable so that GetPhysicsSolver can be const - in practice the user shouldn't have to worry. Finally, UE's reflection system wants to be able to use the assignment operator. If it wasn't for that, we could just delete the copy operator etc and prevent duplicates containing a pointer to the same PhysicsSolver. In practice, this won't ever happen for a "live" component, so we're OK.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysics/Public/RigPhysicsSolverExecution.h` (Public)


#### struct `FRigUnit_AddPhysicsSolver`  
`struct FRigUnit_AddPhysicsSolver : public FRigUnit_PhysicsBaseMutable`  
_L21-64_
- reflection: `USTRUCT(meta=(DisplayName="Spawn Physics Solver", Keywords="Add,Construction,Create,New,Simulation", Varying, Deprecated="5.8"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Adds a new physics solver as a component on the owner element. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen). Deprecated in favour of FRigUnit_SpawnPhysicsSolver, which exposes the new SpaceMotion + TeleportDetection input pins separately. Existing graphs continue to work - the deprecated Execute body routes the legacy SimulationSpaceSettings into the new component members via ConvertLegacyPhysicsSimulationSpaceSettings; right-clicking the deprecated node offers a one-click upgrade to the new node via GetUpgradeInfo.
- L25 _public function_ `FRigUnit_AddPhysicsSolver()`
- L37 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L42 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L46 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Output))` — The component key of the solver that has been added
- L50 _public member_ `FRigPhysicsSolverSettings SolverSettings;` — `UPROPERTY(meta = (Input))` — Settings for the physics solver that will be added
- L56 _public member_ `FRigPhysicsSimulationSpaceSettings SimulationSpaceSettings;` — `UPROPERTY(meta = (Input))` — Settings for the solver that apply to when it uses a simulation space other than "world". These typically relate to the movement of the simulation space itself, and how that is used by the solver.
- L62 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;` — Maps the legacy SimulationSpaceSettings pin onto the FRigUnit_SpawnPhysicsSolver layout (SpaceMotion + TeleportDetection sub-pins). Lets users right-click and upgrade to the new node manually; the deprecated Execute body stays functional for graphs that haven't been upgraded yet.

#### struct `FRigUnit_SpawnPhysicsSolver`  
`struct FRigUnit_SpawnPhysicsSolver : public FRigUnit_PhysicsBaseMutable`  
_L70-108_
- reflection: `USTRUCT(meta=(DisplayName="Spawn Physics Solver", Keywords="Add,Construction,Create,New,Simulation", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Adds a new physics solver as a component on the owner element. Note: This node only runs during the construction event (before physics instantiation, after which this data is frozen).
- L74 _public function_ `FRigUnit_SpawnPhysicsSolver()`
- L86 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L91 _public member_ `FRigElementKey Owner;` — `UPROPERTY(meta = (Input, BoneName))` — The owner of the newly created component (must be set/valid)
- L95 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Output))` — The component key of the solver that has been added
- L99 _public member_ `FRigPhysicsSolverSettings SolverSettings;` — `UPROPERTY(meta = (Input))` — Settings for the physics solver that will be added
- L103 _public member_ `FRigPhysicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(meta = (Input))` — Per-channel teleport-detection thresholds applied to raw simulation-space deltas.
- L107 _public member_ `FRigPhysicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(meta = (Input))` — Conditioning of simulation-space velocity/acceleration plus nested inertial-force gain and drag.

#### struct `FRigUnit_GetPhysicsSolverExists`  
`struct FRigUnit_GetPhysicsSolverExists : public FRigUnit_PhysicsBase`  
_L112-127_
- reflection: `USTRUCT(meta=(DisplayName="Get Physics Solver Exists", Keywords="Query,Simulation"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Indicates whether the component exists and is a Physics Solver
- L116 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L121 _public member_ `FRigComponentKey PhysicsSolverComponentKey = FRigComponentKey( FRigElementKey(TEXT("Root"), ERigElementType::Bone), FRigPhysicsSolverComponent::GetDefaultName` — `UPROPERTY(meta = (Input))` — The component key to check
- L126 _public member_ `bool bExists = false;` — `UPROPERTY(meta = (Output))` — Whether the component exists and is a Physics Solver

#### struct `FRigUnit_InstantiatePhysics`  
`struct FRigUnit_InstantiatePhysics : public FRigUnit_PhysicsBaseMutable`  
_L134-150_
- reflection: `USTRUCT(meta = (DisplayName = "Instantiate physics"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Instantiates all the objects in the physics world. Some properties can't be modified after this happens. Note that it will happen automatically during the first simulation step if it hasn't been explicitly requested. Explicit instantiation allows the timing to be controlled, as allocations etc may cause some delays.
- L138 _public function_ `FRigUnit_InstantiatePhysics()`
- L144 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L149 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The solver that should be instantiated

#### struct `FRigUnit_StepPhysicsSolver`  
`struct FRigUnit_StepPhysicsSolver : public FRigUnit_PhysicsBaseMutable`  
_L154-195_
- reflection: `USTRUCT(meta = (DisplayName = "Step Physics Solver", Keywords = "Simulate", Deprecated="5.8"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Steps the specified physics solver
- L158 _public function_ `FRigUnit_StepPhysicsSolver()`
- L164 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L169 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver that should be stepped
- L175 _public member_ `float DeltaTimeOverride = 0.0f;` — `UPROPERTY(meta = (Input))` — If this is zero, then the execute context time will be used. If this is positive then it will override the delta time. A negative value will prevent the solver from stepping, but there will still be update costs associated with the node.
- L182 _public member_ `float SimulationSpaceDeltaTimeOverride = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — If this is zero, then the simulation delta time will be used for evaluating movement of the simulation space. If this is positive then it will override. This may be needed if the component movement is being done in parallel, in which case you might need to pass in the previous time delta here.
- L187 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation is combined with the input bone. This currently happens in component space. Note that the simulation will continue to run, even if alpha = 0
- L191 _public member_ `FRigPhysicsVisualizationSettings VisualizationSettings;` — `UPROPERTY(meta = (Input))` — Settings that specify how the solver state should be visualized during/after the step
- L193 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigUnit_StepPhysicsSolver1`  
`struct FRigUnit_StepPhysicsSolver1 : public FRigUnit_PhysicsBaseMutable`  
_L199-251_
- reflection: `USTRUCT(meta = (DisplayName = "Step Physics Solver", Keywords = "Simulate"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Steps the specified physics solver
- L203 _public function_ `FRigUnit_StepPhysicsSolver1()`
- L209 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L214 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver that should be stepped
- L220 _public member_ `float DeltaTimeOverride = 0.0f;` — `UPROPERTY(meta = (Input))` — If this is zero, then the execute context time will be used. If this is positive then it will override the delta time. A negative value will prevent the solver from stepping, but there will still be update costs associated with the node.
- L227 _public member_ `float SimulationSpaceDeltaTimeOverride = 0.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0"))` — If this is zero, then the simulation delta time will be used for evaluating movement of the simulation space. If this is positive then it will override. This may be needed if the component movement is being done in parallel, in which case you might need to pass in the previous time delta here.
- L239 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — How much of the simulation is combined with the input bone. This currently happens in component space. Each body additionally has its own PhysicsBlendWeight, and the effective blend per body is Alpha * PhysicsBlendWeight. When Alpha is zero the simulation is bypassed entirely (pass-through) - see bTrackVelocitiesDuringPassThrough for the resume behaviour. Note that only Alpha triggers the fast pass-through: setting every body's PhysicsBlendWeight to zero leaves the bones at the input animation pose (no hierarchy writeback), but the simulation still runs. Set Alpha to zero if you want to skip the simulation cost entirely.
- L246 _public member_ `bool bTrackVelocitiesDuringPassThrough = true;` — `UPROPERTY(meta = (Input))` — When true and Alpha is zero, the solver still tracks source bone transforms each frame so that velocities are valid when Alpha increases (smooth resume), at a small per-body cost. When false and Alpha is zero, the pass-through is near-zero cost but the simulation does a brief warm-up reset (forcing kinematic tracking for a few frames) when Alpha increases.
- L250 _public member_ `FRigPhysicsVisualizationSettings1 VisualizationSettings;` — `UPROPERTY(meta = (Input))` — Settings that specify how the solver state should be visualized during/after the step

#### struct `FRigUnit_SetPhysicsSolverSimulationSpaceSettings`  
`struct FRigUnit_SetPhysicsSolverSimulationSpaceSettings : public FRigUnit_PhysicsBaseMutable`  
_L261-286_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Solver Simulation Space Settings", Deprecated="5.8"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the solver's simulation space settings. Note: Solver settings are pushed to the simulation each step, so this can be modified after physics instantiation. Deprecated in favour of FRigUnit_SetPhysicsSolverSpaceMotion + FRigUnit_SetPhysicsSolverTeleportDetection. Existing graphs continue to work - the deprecated Execute body routes the legacy struct into the new component members via ConvertLegacyPhysicsSimulationSpaceSettings.
- L265 _public function_ `FRigUnit_SetPhysicsSolverSimulationSpaceSettings()`
- L271 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L276 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L280 _public member_ `FRigPhysicsSimulationSpaceSettings SimulationSpaceSettings;` — `UPROPERTY(meta = (Input))` — The new simulation space settings
- L284 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;` — Returns an invalid upgrade info so existing graphs keep this node in place rather than auto-swapping it. The Execute body remains functional.

#### struct `FRigUnit_GetPhysicsSolverSimulationSpaceSettings`  
`struct FRigUnit_GetPhysicsSolverSimulationSpaceSettings : public FRigUnit_PhysicsBase`  
_L293-318_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Solver Simulation Space Settings", Deprecated="5.8"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Gets the solver's simulation space settings. Deprecated in favour of FRigUnit_GetPhysicsSolverSpaceMotion + FRigUnit_GetPhysicsSolverTeleportDetection. Existing graphs continue to work - the deprecated Execute body builds a legacy view via BuildLegacyPhysicsSimulationSpaceSettingsView.
- L297 _public function_ `FRigUnit_GetPhysicsSolverSimulationSpaceSettings()`
- L303 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L308 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L312 _public member_ `FRigPhysicsSimulationSpaceSettings SimulationSpaceSettings;` — `UPROPERTY(meta = (Output))` — The current simulation space settings
- L316 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;` — Returns an invalid upgrade info so existing graphs keep this node in place rather than auto-swapping it. The Execute body remains functional.

#### struct `FRigUnit_SetPhysicsSolverSpaceMotion`  
`struct FRigUnit_SetPhysicsSolverSpaceMotion : public FRigUnit_PhysicsBaseMutable`  
_L323-343_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Solver Space Motion"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the solver's simulation space motion settings (conditioning + nested inertial-force / drag). Note: Solver settings are pushed to the simulation each step, so this can be modified after physics instantiation.
- L327 _public function_ `FRigUnit_SetPhysicsSolverSpaceMotion()`
- L333 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L338 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L342 _public member_ `FRigPhysicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(meta = (Input))` — The new simulation space motion settings

#### struct `FRigUnit_GetPhysicsSolverSpaceMotion`  
`struct FRigUnit_GetPhysicsSolverSpaceMotion : public FRigUnit_PhysicsBase`  
_L347-367_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Solver Space Motion"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Gets the solver's simulation space motion settings.
- L351 _public function_ `FRigUnit_GetPhysicsSolverSpaceMotion()`
- L357 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L362 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L366 _public member_ `FRigPhysicsSimulationSpaceMotion SpaceMotion;` — `UPROPERTY(meta = (Output))` — The current simulation space motion settings

#### struct `FRigUnit_SetPhysicsSolverTeleportDetection`  
`struct FRigUnit_SetPhysicsSolverTeleportDetection : public FRigUnit_PhysicsBaseMutable`  
_L372-392_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Solver Teleport Detection"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the solver's teleport-detection thresholds. Note: Solver settings are pushed to the simulation each step, so this can be modified after physics instantiation.
- L376 _public function_ `FRigUnit_SetPhysicsSolverTeleportDetection()`
- L382 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L387 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L391 _public member_ `FRigPhysicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(meta = (Input))` — The new teleport-detection thresholds

#### struct `FRigUnit_GetPhysicsSolverTeleportDetection`  
`struct FRigUnit_GetPhysicsSolverTeleportDetection : public FRigUnit_PhysicsBase`  
_L396-416_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Solver Teleport Detection"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Gets the solver's teleport-detection thresholds.
- L400 _public function_ `FRigUnit_GetPhysicsSolverTeleportDetection()`
- L406 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L411 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L415 _public member_ `FRigPhysicsTeleportDetectionSettings TeleportDetection;` — `UPROPERTY(meta = (Output))` — The current teleport-detection thresholds

#### struct `FRigUnit_SetPhysicsSolverExternalVelocity`  
`struct FRigUnit_SetPhysicsSolverExternalVelocity : public FRigUnit_PhysicsBaseMutable`  
_L421-456_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Solver External Velocity"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Sets the external velocity of the simulation - used for adding wind effects. Note: Solver settings are pushed to the simulation each step, so this can be modified after physics instantiation.
- L425 _public function_ `FRigUnit_SetPhysicsSolverExternalVelocity()`
- L431 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L436 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The physics solver
- L443 _public member_ `FVector ExternalLinearVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Additional velocity that is added to the component velocity so the simulation acts as if the actor is moving at speed, even when stationary. The vector is in world space. This could be used for wind effects etc. Typical values are similar to the velocity of the object or effect, and usually around or less than 1000 for characters/wind.
- L450 _public member_ `FVector ExternalAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Additional angular velocity that is added to the component angular velocity. This can be used to make the simulation act as if the actor is rotating even when it is not. E.g., to apply physics to a character on a podium as the camera rotates around it, to emulate the podium itself rotating. Vector is in world space. Units are deg/s.
- L455 _public member_ `FVector ExternalTurbulenceVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — This will treat the external velocity like a wind field and add turbulence to it. Units are the same as velocity, so this is the approximate magnitude of the turbulence.

#### struct `FRigUnit_TrackInputPose`  
`struct FRigUnit_TrackInputPose : public FRigUnit_PhysicsBaseMutable`  
_L465-495_
- reflection: `USTRUCT(meta = (DisplayName = "Set Solver Track Input Pose", Keywords = "Reset,Simulate", Deprecated="5.8"))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Forces tracking of the input animation (on all physics bodies) for the next N frames. Deprecated in favour of Step Physics Solver with Alpha = 0. Setting Alpha to 0 produces a cheaper pass-through and (when bTrackVelocitiesDuringPassThrough is false) automatically schedules the same warm-up tracking on resume that this node sets manually. Existing graphs continue to work - the Execute body still bumps TrackInputCounter as before.
- L469 _public function_ `FRigUnit_TrackInputPose()`
- L475 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L480 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The solver to relate this new physics element to
- L484 _public member_ `int NumberOfFrames = 1;` — `UPROPERTY(meta = (Input, ClampMin = "0"))` — The number of frames to track the input pose for
- L489 _public member_ `bool bForceNumberOfFrames = false;` — `UPROPERTY(meta = (Input))` — If true, then the number will be forced, potentially reducing the number. If false, then the NumberOfFrames will only be used to increase the number of frames remaining.
- L493 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;` — Returns an invalid upgrade info so existing graphs keep this node in place rather than auto-swapping it. The Execute body remains functional.

#### struct `FRigUnit_GetPhysicsSolverSpaceData`  
`struct FRigUnit_GetPhysicsSolverSpaceData : public FRigUnit_PhysicsBase`  
_L500-536_
- reflection: `USTRUCT(meta = (DisplayName = "Get Physics Solver Space Data", Keywords = "Debug"))`
- inherits: `FRigUnit_PhysicsBase`
- desc: Retrieves the simulation space data that were generated during the simulation step, so the values returned will relate to the previous update if the solver has not yet been stepped.
- L504 _public function_ `FRigUnit_GetPhysicsSolverSpaceData()`
- L510 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L515 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The solver to relate this new physics element to
- L519 _public member_ `FVector LinearVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The velocity of the simulation space (in world space)
- L523 _public member_ `FVector AngularVelocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The angular velocity of the simulation space (in world space)
- L527 _public member_ `FVector LinearAcceleration = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The linear acceleration of the simulation space (in world space)
- L531 _public member_ `FVector AngularAcceleration = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The angular acceleration of the simulation space (in world space)
- L535 _public member_ `FVector Gravity = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — The gravitational acceleration that will be applied (in simulation space)

#### struct `FRigUnit_HierarchySetPhysicsSolverAllowCCD`  
`struct FRigUnit_HierarchySetPhysicsSolverAllowCCD : public FRigUnit_PhysicsBaseMutable`  
_L541-561_
- reflection: `USTRUCT(meta = (DisplayName = "Set Physics Solver Allow CCD", Varying))`
- inherits: `FRigUnit_PhysicsBaseMutable`
- desc: Enables/disables support for CCD in the solver. Note: Solver settings are pushed to the simulation each step, so this can be modified after physics instantiation.
- L545 _public function_ `FRigUnit_HierarchySetPhysicsSolverAllowCCD()`
- L551 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L556 _public member_ `FRigComponentKey PhysicsSolverComponentKey;` — `UPROPERTY(meta = (Input))` — The Physics Solver to be updated
- L560 _public member_ `bool bAllowCCD = false;` — `UPROPERTY(meta = (Input))` — Whether or not the solver allows CCD to be used. CCD also needs to be enabled on individual bodies

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGPHYSICS_API`
