# Plugins / PhysicsControl

- module root: `Plugins/Animation/PhysicsControl/Source/PhysicsControl`
- headers: 17; symbols: 979
- symbol kinds: class=6, delegate=1, enum=10, enumerator=63, externvar=3, function=95, macro=6, member=392, namespace=8, prototype=341, struct=52, typedef=1, variable=1
- PrivateDependencyModuleNames: AnimGraphRuntime, AnimationCore, Core, CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/AnimNode_RigidBodyWithControl.h` (Public)


#### struct `FSimulationSpaceData`  
`struct FSimulationSpaceData`  
_L34-41_
- L36 _public member_ `FTransform Transform;`
- L37 _public member_ `FVector LinearVel;`
- L38 _public member_ `FVector AngularVel;`
- L39 _public member_ `FVector LinearAcc;`
- L40 _public member_ `FVector AngularAcc;`

#### enum `MapConstraintsBehaviorType`  
`enum class MapConstraintsBehaviorType : uint8`  
_L44-49_
- reflection: `UENUM(BlueprintType)`
- L46 _public enumerator_ `AuthoredSkeleton UMETA(DisplayName = "From Authored Skeletal Mesh", ToolTip = "Apply any difference in the relative transform of the constraint's parent and child bones between the authored and current skeleton to the constraint's transform relative to the parent bone. This is normally the best option and should effectively keep the joint in the authored location relative to the parent bone.")`
- L47 _public enumerator_ `DefaultTransform UMETA(DisplayName = "From Child Bone Transform (default)", ToolTip = "Set constraints transform relative to the parent bone to match the child bone in the current skeleton.")`
- L48 _public enumerator_ `None UMETA(DisplayName = "Nothing", ToolTip = "Nothing")`

#### struct `FAnimNode_RigidBodyWithControl`  
`struct FAnimNode_RigidBodyWithControl : public FAnimNode_SkeletalControlBase`  
_L134-813_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Controller that simulates physics based on the physics asset of the skeletal mesh component
- L138 _public prototype_ `FAnimNode_RigidBodyWithControl();`
- L139 _public prototype_ `~FAnimNode_RigidBodyWithControl();`
- L142 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L143 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L147 _public prototype_ `virtual void UpdateComponentPose_AnyThread(const FAnimationUpdateContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L148 _public prototype_ `virtual void EvaluateComponentPose_AnyThread(FComponentSpacePoseContext& Output) override;`
- L149 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L150 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L151 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L152 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L153 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L154 _public function_ `virtual bool HasPreUpdate() const override`
- L155 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L156 _public prototype_ `virtual bool NeedsDynamicReset() const override;`
- L157 _public prototype_ `virtual void ResetDynamics(ETeleportType InTeleportType) override;`
- L158 _public prototype_ `virtual int32 GetLODThreshold() const override;`
- L161 _public prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None);`
- L164 _public function_ `virtual ImmediatePhysics::FSimulation* GetSimulation()` — TEMP: Exposed for use in PhAT as a quick way to get drag handles working with Chaos
- L171 _public prototype_ `void SetOverridePhysicsAsset(UPhysicsAsset* PhysicsAsset);` — Set the override physics asset. This will automatically trigger a physics re-init if the override physics asset changes. Users can get access to this in the Animation Blueprint via the Animation Node Functions.
- L177 _public prototype_ `void InvokeControlProfile(FName ControlProfileName);` — Invoke the profile stored in the control profile asset, and sets the current profile. Note that this produces permanent changes to the control and modifier values.
- L179 _public function_ `UPhysicsAsset* GetPhysicsAsset() const`
- L187 _public member_ `TObjectPtr<UPhysicsAsset> OverridePhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Physics asset to use. If empty use the skeletal mesh's default physics asset. Note that this can be changed at runtime using SetOverridePhysicsAsset in the Animation Node Functions
- L194 _public member_ `bool bDefaultToSkeletalMeshPhysicsAsset = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Use the skeletal mesh physics asset as default in case set to True. The Override Physics Asset will always have priority over this.
- L201 _private prototype_ `UPhysicsAsset* GetPhysicsAssetToBeUsed(const UAnimInstance* InAnimInstance) const;` — Get the physics asset candidate to be used while respecting the bDefaultToSkeletalMeshPhysicsAsset and the priority to the override physics asset.
- L203 _private member_ `FTransform PreviousCompWorldSpaceTM;`
- L204 _private member_ `FTransform CurrentTransform;`
- L205 _private member_ `FTransform PreviousTransform;`
- L207 _private member_ `UPhysicsAsset* PhysicsAssetToUse;`
- L212 _public member_ `FVector OverrideWorldGravity;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, editcondition = "bOverrideWorldGravity"))` — Override gravity
- L216 _public member_ `FVector ExternalForce;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))` — Applies a uniform external force in world space. This allows for easily faking inertia of movement while still simulating in component space for example
- L220 _public member_ `FVector ComponentLinearAccScale;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — When using non-world-space sim, this controls how much of the components world-space acceleration is passed on to the local-space simulation.
- L224 _public member_ `FVector ComponentLinearVelScale;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — When using non-world-space sim, this applies a 'drag' to the bodies in the local space simulation, based on the components world-space velocity.
- L228 _public member_ `FVector ComponentAppliedLinearAccClamp;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When using non-world-space sim, this is an overall clamp on acceleration derived from ComponentLinearAccScale and ComponentLinearVelScale, to ensure it is not too large.
- L241 _public member_ `FSimSpaceSettings SimSpaceSettings;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Settings for the system which passes motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way. This system is a superset of the functionality provided by ComponentLinearAccScale, ComponentLinearVelScale, and ComponentAppliedLinearAccClamp. In general you should not have both systems enabled.
- L249 _public member_ `float CachedBoundsScale;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (ClampMin="1.0", ClampMax="2.0"))` — Scale of cached bounds (vs. actual bounds) used for obtaining the list of objects we might collide with. Increasing this may improve performance, but overlaps may not work as well. (A value of 1.0 effectively disables cached bounds).
- L257 _public member_ `bool bUpdateCacheEveryFrame;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — This can be used to force the cached collision objects to be updated every frame, even when we are not moving. This can be expensive, but may be needed if we wish to detect collisions with objects that are moving, otherwise the cache will only be updated if/when we move.
- L261 _public member_ `FBoneReference BaseBoneRef;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Matters if SimulationSpace is BaseBone
- L265 _public member_ `TEnumAsByte<ECollisionChannel> OverlapChannel;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (editcondition = "bEnableWorldGeometry"))` — The channel we use to find static geometry to collide with
- L269 _public member_ `ESimulationSpace SimulationSpace;` — `UPROPERTY(EditAnywhere, Category = Settings)` — What space to simulate the bodies in. This affects how velocities are generated
- L278 _public member_ `uint8 bCalculateVelocitiesForWorldGeometry : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (editcondition = "bEnableWorldGeometry"))` — Whether or not to calculate velocities for world geometry. Note that if the simulation space is not set to world, then even static objects "should" have velocities calculated. There is a cost associated with calculating velocities, but without them there may be more penetration between the simulated objects and the world.
- L282 _public member_ `uint8 bForceDisableCollisionBetweenConstraintBodies : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — Whether to allow collisions between two bodies joined by a constraint
- L286 _public member_ `uint8 bUseExternalClothCollision : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — If true, kinematic objects will be added to the simulation at runtime to represent any cloth colliders defined for the parent object.
- L293 _public member_ `uint8 bMakeKinematicConstraints : 1;` — `UPROPERTY(EditAnywhere, Category = Settings)` — If true, constraints will be made even when both objects are kinematic, in case they are subsequently made dynamic. There may be a small performance benefit to disabling this if you know this won't happen.
- L296 _private member_ `ETeleportType ResetSimulatedTeleportType;`
- L300 _public member_ `uint8 bEnableWorldGeometry : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)`
- L303 _public member_ `uint8 bWorldGeometryCollisionEnabledHasPhysics : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)`
- L306 _public member_ `uint8 bWorldGeometryCollisionEnabledHasQuery : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)`
- L309 _public member_ `uint8 bWorldGeometryCollisionEnabledHasProbe : 1;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)`
- L312 _public member_ `uint8 bOverrideWorldGravity : 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L319 _public member_ `uint8 bTransferBoneVelocities : 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(PinHiddenByDefault))` — When simulation starts, transfer previous bone velocities (from animation) to make transition into simulation seamless.
- L327 _public member_ `uint8 bFreezeIncomingPoseOnStart : 1;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When simulation starts, freeze incoming pose. This is useful for ragdolls, when we want the simulation to take over. It prevents non simulated bones from animating.
- L333 _public member_ `MapConstraintsBehaviorType PhysicsAssetConditioningConstraintPosition;` — `UPROPERTY(EditAnywhere, Category = PhysicsAssetConditioning, meta = (DisplayName = "Set Position Relative to Parent", DisplayAfter = "PhysicsAssetAuthoredSkeletalMesh"))` — Configure the way constraint positions can be modified at runtime to match the current Skeletal Mesh.
- L339 _public member_ `MapConstraintsBehaviorType PhysicsAssetConditioningConstraintOrientation;` — `UPROPERTY(EditAnywhere, Category = PhysicsAssetConditioning, meta = (DisplayName = "Set Orientation Relative to Parent", DisplayAfter = "PhysicsAssetAuthoredSkeletalMesh"))` — Configure the way constraint orientations can be modified at runtime to match the current Skeletal Mesh.
- L343 _public member_ `uint8 bModifyConstraintTransformsToMatchSkeleton_DEPRECATED : 1;` — `UPROPERTY()`
- L352 _public member_ `float WorldSpaceMinimumScale;` — `UPROPERTY(EditAnywhere, Category = Settings)` — For world-space simulations, if the magnitude of the component's 3D scale is less than WorldSpaceMinimumScale, do not update the node.
- L360 _public member_ `float EvaluationResetTime;` — `UPROPERTY(EditAnywhere, Category = Settings)` — If the node is not evaluated for this amount of time (seconds), either because a lower LOD was in use for a while or the component was not visible, reset the simulation to the default pose on the next evaluation. Set to 0 to disable time-based reset.
- L367 _public member_ `bool bEnableControls;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (PinHiddenByDefault))` — If false, then controls will not be created. Note that this can be exposed as a pin/bound, and then control creation can be deferred to when the value is set to true as the node runs.
- L375 _public member_ `TObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — `UPROPERTY(EditAnywhere, Category = ControlSetup)` — Physics control asset to use. This is optional, but if it has been set, then it will be used during creation of controls/body modifiers. Note that this can be modified at runtime in the Animation Blueprint via the Animation Node functions.
- L385 _public member_ `TMap<FName, FName> BoneToBodyNameMap;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (PinHiddenByDefault))` — A map of bone names to "body" names, the latter being used to assign names to controls/modifiers. This is optional - so if there is no mapping for a bone, then its name will be used directly when creating controls. The two main benefits of this are (1) to generate consistently named controls even on different skeletons and (2) to make it easier to refer to individual controls, without needing to refer to the skeleton.
- L392 _public member_ `FPhysicsControlCharacterSetupData CharacterSetupData;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (PinHiddenByDefault, editcondition = "bEnableCharacterSetupData"))` — Setup data for creating the main controls (world- and parent-space) and modifiers, based on splitting the skeleton up into limbs.
- L395 _public member_ `bool bEnableCharacterSetupData = true;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (InlineEditConditionToggle))`
- L401 _public member_ `FPhysicsControlAndBodyModifierCreationDatas AdditionalControlsAndBodyModifiers;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (PinHiddenByDefault))` — Controls and modifiers that should be created, in addition to those made as part of the limb setup.
- L407 _public member_ `FPhysicsControlSetUpdates AdditionalSets;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (PinHiddenByDefault))` — Allows additional sets of controls or modifiers to be created, and existing sets to be modified
- L415 _public member_ `FPhysicsControlControlAndModifierParameters InitialControlAndBodyModifierUpdates;` — `UPROPERTY(EditAnywhere, Category = ControlSetup, meta = (PinHiddenByDefault))` — An initial set of controls that should be applied immediately after setup. This allows individual or sets of controls/modifiers etc to be adjusted. Note that these will then be "baked" into the controls.
- L422 _public member_ `FPhysicsControlControlAndModifierParameters ControlAndModifierParameters;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinShownByDefault))` — Controls that should be applied each frame, and can be expected to change. Note that if these stop being passed in then the controls and modifiers will return to their normal/original state.
- L428 _public member_ `FPhysicsControlControlAndModifierUpdates ControlAndModifierUpdates;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinShownByDefault))` — Updates to controls that can be applied. Note that these update the normal/original state.
- L434 _public member_ `FRigidBodyControlTargets ControlTargets;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinShownByDefault))` — Targets that should be applied to the controls.
- L440 _public member_ `FRigidBodyKinematicTargets KinematicTargets;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinShownByDefault))` — Targets that should be applied to kinematic bodies that are under the influence of a body modifier.
- L446 _public member_ `FRigidBodyForcesAndTorques ForcesAndTorques;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinShownByDefault))` — Forces/torques that should be applied to dynamic bodies that are under the influence of a body modifier.
- L472 _public member_ `TObjectPtr<USkeletalMesh> PhysicsAssetAuthoredSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = PhysicsAssetConditioning, meta = (DisplayName = "Authored Skeletal Mesh"))` — These options configure the way constraint transforms can be modified at runtime to match the current Skeletal Mesh. This can be useful when applying a single RBwC node to assets with different skeletons. When the "From authored skeletal mesh" option is selected, the Position and/or Orientation of each constraint relative to its parent bone will be changed to account for any difference in relative bone transforms between that Skeletal Mesh and the current one. This means that if bone positions or orientations have changed between the authored Skeletal Mesh and the one currently being animated then the constraint positions and orientations will be updated to match. The authored Skeletal Mesh should normally be set to the same skeletal mesh that was used when creating the physics asset. WARNING This option will do nothing if the authored skeleton is not defined or cannot be found when the node is initialized at runtime. When the "To default" option is selected the Position and/or Orientation of each constraint relative to its parent bone will be set to the Position and/or Orientation of the constraint's child bone relative to its parent bone. This is the same as the default transform applied in the Physics Asset editing tool when a constraint is created or 'snapped' to the default transform. [WARNING] The "To default" option can produce undesirable results and should be used with caution but may be useful for simple assets or to minimize sudden changes in bone positions that ma
- L479 _public member_ `FName ConstraintProfile;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinHiddenByDefault))` — The constraint profile to use on all the joints in the physics asset. Will be applied when the profile name changes.
- L486 _public member_ `FName ControlProfile;` — `UPROPERTY(EditAnywhere, Category = Controls, meta = (PinHiddenByDefault))` — The control profile to use. Will be applied when the profile name changes. To force it to be invoked again, either change the profile to something else for a frame, or call InvokeControlProfile.
- L494 _public member_ `float BoundsVelocityMultiplier = 0.0f;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (ClampMin = 0))` — Expands the shape bounds to detect potentially active contacts when moving. Increasing this (typically up to 1) will increase the number of inactive contacts, which will reduce the likelihood of penetration, but will also increase solver cost.
- L501 _public member_ `float MaxVelocityBoundsExpansion = 0.0f;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (ClampMin = 0))` — The maximum margin added due to movement. Reducing this can prevent excessive numbers of inactive contacts being generated.
- L507 _public member_ `bool bAllowCCD = false;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — Allows the solver to use the EnableCCD setting on the bodies
- L510 _private member_ `uint8 bEnabled : 1;`
- L511 _private member_ `uint8 bSimulationStarted : 1;`
- L512 _private member_ `uint8 bCheckForBodyTransformInit : 1;`
- L513 _private member_ `uint8 bHaveSetupControls : 1;`
- L516 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L518 _public prototype_ `const int32 GetNumBodies() const;`
- L520 _public function_ `const FPhysicsControlNameRecords& GetNameRecords() const`
- L525 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L528 _private prototype_ `void InitPhysics(const UAnimInstance* InAnimInstance);`
- L529 _private prototype_ `void UpdateWorldGeometry(const UWorld& World, const USkeletalMeshComponent& SKC);`
- L530 _private prototype_ `void UpdateWorldForces(const FTransform& ComponentToWorld, const FTransform& BaseBoneTM, const float DeltaSeconds);`
- L533 _public prototype_ `const FTransform GetBodyTransform(const int32 BodyIndex) const;`
- L535 _public prototype_ `bool CreateNamedControl( const FName ControlName, const FName ParentBoneName, const FName ChildBoneName, const FPhysicsControlData& ControlData);`
- L537 _public prototype_ `FName CreateControl(const FName ParentBoneName, const FName ChildBoneName, const FPhysicsControlData& ControlData);`
- L539 _public prototype_ `bool CreateNamedBodyModifier( const FName ModifierName, const FName BoneName, const FPhysicsControlModifierData& ModifierData);`
- L541 _public prototype_ `FName CreateBodyModifier(const FName BoneName, const FPhysicsControlModifierData& ModifierData);`
- L546 _protected prototype_ `int32 AddBody(ImmediatePhysics::FActorHandle* const BodyHandle);` — Add a new physics body and update the body name to index map
- L547 _protected prototype_ `int32 FindBodyIndexFromBoneName(const FName BoneName) const;`
- L548 _protected prototype_ `ImmediatePhysics::FActorHandle* FindBodyFromBoneName(const FName BoneName) const;`
- L549 _protected prototype_ `void UpdateBodyIndicesInControlRecord(FRigidBodyControlRecord& ControlRecord);`
- L551 _protected prototype_ `ImmediatePhysics::FJointHandle* CreateConstraint( ImmediatePhysics::FActorHandle* const ChildBodyHandle, ImmediatePhysics::FActorHandle* const ParentBodyHandle);`
- L553 _protected prototype_ `void CreateWorldSpaceControlRootBody(UPhysicsAsset* const PhysicsAsset);`
- L555 _protected prototype_ `void ApplyControl(FRigidBodyControlRecord& ControlRecord, float DeltaTime);`
- L556 _protected prototype_ `void ApplyModifier(const FRigidBodyModifierRecord& BodyModifierRecord, const FVector& SimSpaceGravity);`
- L558 _protected prototype_ `void ApplyControlsAndModifiers(const FVector& SimSpaceGravity, float DeltaTime);`
- L560 _protected prototype_ `void ApplyForcesAndTorques( const FTransform& ComponentToWorld, const FTransform& BaseBoneTM);`
- L563 _protected prototype_ `void ApplyForceAndTorque( const FPhysicsControlForceAndTorqueData& ForceAndTorqueData, const FRigidBodyModifierRecord& ModifierRecord, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM);`
- L570 _protected prototype_ `void ApplyKinematicTargets(const FTransform& CompWorldSpaceTM, const FTransform& BaseBoneTM);` — This applies kinematic targets to any that have been set through the body modifiers
- L573 _protected prototype_ `void ApplyCurrentConstraintProfile();` — This applies the desired constraint profile, if necessary
- L576 _protected prototype_ `void ApplyCurrentControlProfile();` — This applies the desired control profile, if necessary
- L578 _protected prototype_ `FName GetBodyFromBoneName(const FName BoneName) const;`
- L580 _protected prototype_ `FName GetUniqueBodyModifierName(const FName BoneName) const;`
- L582 _protected prototype_ `FName GetUniqueControlName(const FName ParentBoneName, const FName ChildBoneName) const;`
- L584 _protected prototype_ `void SetupControls(USkeletalMeshComponent* const SkeletalMeshComponent);`
- L587 _protected prototype_ `void InitControlsAndBodyModifiers(const FReferenceSkeleton& RefSkeleton);` — This will walk through the skeleton, create controls and body modifiers, and create the sets.
- L589 _protected prototype_ `void DestroyControlsAndBodyModifiers();`
- L592 _protected prototype_ `void LogControlsModifiersAndSets();` — Helper to log overything that has been created to help the user
- L595 _protected prototype_ `void ApplyControlAndBodyModifierDatas( const TArray<FPhysicsControlNamedControlParameters>& InControlParameters, const TArray<FPhysicsControlNamedControlMultiplierParameters>& InControlMultiplierParameters, const TArray<FPhysicsControlNamedModifierParameters>& InModifierParameters);` — Applies the overrides to the underlying controls and modifiers
- L601 _protected prototype_ `void ApplyControlAndModifierUpdatesAndParametersToRecords( const FPhysicsControlControlAndModifierUpdates& Updates, const FPhysicsControlControlAndModifierParameters& Parameters);` — Applies the parameters to control and modifier records
- L605 _protected prototype_ `void InitializeNewBodyTransformsDuringSimulation( FComponentSpacePoseContext& Output, const FTransform& ComponentTransform, const FTransform& BaseBoneTM);`
- L608 _protected prototype_ `void InitSimulationSpace(const FTransform& ComponentToWorld, const FTransform& BoneToComponent);`
- L611 _protected prototype_ `void CalculateSimulationSpaceMotion( const float Dt, const FSimSpaceSettings& Settings, FVector& SpaceLinearVel, FVector& SpaceAngularVel, FVector& SpaceLinearAcc, FVector& SpaceAngularAcc);` — Calculate simulation space transform, velocity etc to pass into the solver
- L620 _protected prototype_ `bool ShouldApplyPhysicsAssetConditioning() const;` — Returns true if constraint transforms in the physics asset should be modified to match the current skeleton.
- L624 _protected prototype_ `void TransformConstraintsToMatchSkeletalMesh( const USkeletalMesh* const SkeletalMeshAsset, const MapConstraintsBehaviorType PositionBehavior, const MapConstraintsBehaviorType OrientationBehavior, TArray<FConstraintInstance*>& ConstraintInstances);` — Modify Constraint transforms relative to the parent bone to correct for the difference between the Skeleton used to create the Physics asset and the current skeleton.
- L632 _protected prototype_ `void CollectClothColliderObjects(const USkeletalMeshComponent* SkeletalMeshComp);` — Gather cloth collision sources from the supplied Skeletal Mesh and add a kinematic actor representing each one of them to the sim.
- L635 _protected prototype_ `void RemoveClothColliderObjects();` — Remove all cloth collider objects from the sim.
- L638 _protected prototype_ `void UpdateClothColliderObjects();` — Update the sim-space transforms of all cloth collider objects.
- L641 _protected prototype_ `void CollectWorldObjects();` — Gather nearby world objects and add them to the sim
- L644 _protected prototype_ `void ExpireWorldObjects();` — Flag invalid world objects to be removed from the sim
- L647 _protected prototype_ `void PurgeExpiredWorldObjects();` — Remove simulation objects that are flagged as expired
- L650 _protected prototype_ `void UpdateWorldObjects(const FVector& LinearVel, const FVector& AngularVel, const float DeltaSeconds);` — Update sim-space transforms of world objects
- L653 _protected prototype_ `void RunPhysicsSimulation(float DeltaSeconds, const FVector& SimSpaceGravity);` — Advances the simulation by a given timestep
- L656 _protected prototype_ `void FlushDeferredSimulationTask();` — Waits for the deferred simulation task to complete if it's not already finished
- L659 _protected prototype_ `void DestroyPhysicsSimulation();` — Destroy the simulation and free related structures
- L670 _public member_ `ESimulationTiming SimulationTiming;` — `UPROPERTY(EditAnywhere, Category=Settings, AdvancedDisplay)` — Whether the physics simulation runs synchronously with the node's evaluation or is run in the background until the next frame. Note that running with deferred timing can improve performance, but there will be a frame's lag in the output (relative to the input animation), and there can be problems with handling collisions.
- L674 _private member_ `float WorldTimeSeconds;`
- L675 _private member_ `float LastEvalTimeSeconds;`
- L677 _private member_ `float AccumulatedDeltaTime;`
- L678 _private member_ `float AnimPhysicsMinDeltaTime;`
- L679 _private member_ `bool bSimulateAnimPhysicsAfterReset;`
- L681 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelMeshCompWeakPtr;` — This should only be used for removing the delegate during termination. Do NOT use this for any per frame work
- L683 _private member_ `ImmediatePhysics::FSimulation* Simulation;`
- L684 _private member_ `FPhysicsAssetSolverSettings SolverSettings;`
- L685 _private member_ `FSolverIterations SolverIterations;` — to be deprecated
- L688 _private member_ `UE::Tasks::FTask SimulationTask;`
- L690 _private member_ `TMap<FName, int32> BodyNameToIndexMap;`
- L691 _private member_ `ImmediatePhysics::FActorHandle* WorldSpaceControlActorHandle;`
- L724 _private member_ `TArray<UE::PhysicsControl::FOutputBoneData> OutputBoneData;`
- L728 _private member_ `TArray<ImmediatePhysics::FActorHandle*> Bodies;` — Note that the Bodies and Joints arrays will be the same size - i.e. there will be a correspondence between every joint and body. The joint will correspond to the parent of the body. Note that some joints will not be set.
- L729 _private member_ `TArray<ImmediatePhysics::FJointHandle*> Joints;`
- L730 _private member_ `TArray<int32> SkeletonBoneIndexToBodyIndex;`
- L731 _private member_ `TArray<FBodyAnimData> BodyAnimData;`
- L736 _private member_ `UE::PhysicsControl::FRigidBodyPoseData PoseData;` — Each update we cache the incoming pose transforms in whatever space the simulation is running in
- L739 _private member_ `TMap<FName, FRigidBodyControlRecord> ControlRecords;` — Map of control records - they will be referenced by name
- L742 _private member_ `TMap<FName, FRigidBodyModifierRecord> ModifierRecords;` — Map of body modifier records - they will be referenced by name
- L745 _private member_ `FPhysicsControlNameRecords NameRecords;` — Details about sets etc
- L747 _private member_ `FName CurrentConstraintProfile;`
- L749 _private member_ `FName CurrentControlProfile;`
- L751 _private member_ `TArray<USkeletalMeshComponent::FPendingRadialForces> PendingRadialForces;`
- L753 _private member_ `FPerSolverFieldSystem PerSolverField;`
- L773 _private member_ `TArray<FClothCollider> ClothColliders;` — List of cloth colliders in the sim that represent objects collected from other parts of this character.
- L779 _private member_ `TMap<const UPrimitiveComponent*, FWorldObject> ComponentsInSim;` — List of actors in the sim that represent objects collected from the world. Note that the key should never be dereferenced, as it is not a smart pointer, and might have been deleted. Instead it should just be used for comparisons, and the actual pointer to the component is stored in the WorldObject.
- L780 _private member_ `int32 ComponentsInSimTick;`
- L782 _private member_ `FVector WorldSpaceGravity;`
- L784 _private member_ `float TotalMass;`
- L787 _private member_ `FSphere CachedBounds;` — Bounds used to gather world objects copied into the simulation
- L789 _private member_ `FCollisionQueryParams QueryParams;`
- L794 _private member_ `const UWorld* UnsafeWorld;` — Used by CollectWorldObjects and UpdateWorldGeometry in the Task Thread. Typically, World should never be accessed off the Game Thread. However, since we're just doing overlaps this should be OK.
- L797 _private member_ `const AActor* UnsafeOwner;` — Used by CollectWorldObjects and UpdateWorldGeometry in Task Thread. Only used for a pointer comparison.
- L800 _private member_ `const USkeletalMesh* SkeletalMeshAtLastPhysicsInit = nullptr;` — The Skeletal Mesh parsed during the last physics initialization
- L802 _private member_ `FBoneContainer CapturedBoneVelocityBoneContainer;`
- L803 _private member_ `FCSPose<FCompactHeapPose> CapturedBoneVelocityPose;`
- L804 _private member_ `FCSPose<FCompactHeapPose> CapturedFrozenPose;`
- L805 _private member_ `FBlendedHeapCurve CapturedFrozenCurves;`
- L807 _private member_ `FVector PreviousComponentLinearVelocity;`
- L810 _private member_ `FTransform SimulationSpaceTransform;` — Used by the world-space to simulation-space motion transfer system in Component- or Bone-Space sims
- L811 _private member_ `FTransform PreviousSimulationSpaceTransform;`
- L812 _private member_ `FTransform PreviousPreviousSimulationSpaceTransform;`

#### struct `FAnimNode_RigidBodyWithControl::FBodyAnimData`  
`struct FBodyAnimData`  
_L693-707_
- L695 _public function_ `FBodyAnimData() : TransferedBoneAngularVelocity(ForceInit) , TransferedBoneLinearVelocity(ForceInitToZero) , bIsSimulated(false) , bBodyTransformInitialized(false)`
- L702 _public member_ `FVector TransferedBoneAngularVelocity;`
- L703 _public member_ `FVector TransferedBoneLinearVelocity;`
- L705 _public member_ `bool bIsSimulated : 1;`
- L706 _public member_ `bool bBodyTransformInitialized : 1;`

#### struct `FAnimNode_RigidBodyWithControl::FWorldObject`  
`struct FWorldObject`  
_L709-722_
- L711 _public function_ `FWorldObject() : ActorHandle(nullptr), LastSeenTick(0), bExpired(false)`
- L712 _public function_ `FWorldObject( ImmediatePhysics::FActorHandle* InActorHandle, int32 InLastSeenTick, TWeakObjectPtr<UPrimitiveComponent> InComponent) : Component(InComponent), ActorHandle(InActorHandle), LastSeenTick(InLastSeenTick), bExpired(false)`
- L718 _public member_ `TWeakObjectPtr<UPrimitiveComponent> Component;`
- L719 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle;`
- L720 _public member_ `int32 LastSeenTick;`
- L721 _public member_ `bool bExpired;`

#### struct `FAnimNode_RigidBodyWithControl::FClothCollider`  
`struct FClothCollider`  
_L756-770_
- desc: Information required to identify and update a kinematic object representing a cloth collision source in the sim.
- L758 _public function_ `FClothCollider( ImmediatePhysics::FActorHandle* const InActorHandle, const USkeletalMeshComponent* const InSkeletalMeshComponent, const uint32 InBoneIndex) : ActorHandle(InActorHandle) , SkeletalMeshComponent(InSkeletalMeshComponent) , BoneIndex(InBoneIndex)`
- L767 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle;` — Identifies the physics actor in the sim.
- L768 _public member_ `TWeakObjectPtr<const USkeletalMeshComponent> SkeletalMeshComponent;` — Parent skeleton.
- L769 _public member_ `uint32 BoneIndex;` — Bone within parent skeleton that drives physics actors transform.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_RigidBodyWithControl> : public TStructOpsTypeTraitsBase2<FAnimNode_RigidBodyWithControl>`  
_L817-823_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_RigidBodyWithControl>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L820-822_

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API PHYSICSCONTROL_API`
- L30 _externvar_ `extern TAutoConsoleVariable<int32> CVarEnableRigidBodyNodeWithControl;`
- L31 _externvar_ `extern TAutoConsoleVariable<int32> CVarEnableRigidBodyNodeWithControlSimulation;`
- L32 _externvar_ `extern TAutoConsoleVariable<int32> CVarRigidBodyNodeWithControlLODThreshold;`
- L55 _prototype_ `void UpdateBodyFromModifierData( ImmediatePhysics::FActorHandle& ActorHandle, ImmediatePhysics::FSimulation& PhysicsSimulation, const FPhysicsControlModifierData& ModifierData, const FVector& SimSpaceGravity);` — A helper function that lets any immediate simulation user update their bodies in the same way that RigidBodyWithControl does.
- L64 _prototype_ `bool UpdateDriveSpringDamperSettings( ImmediatePhysics::FJointHandle& JointHandle, const Chaos::FPBDJointSettings& Settings, const FPhysicsControlData& Data, const FPhysicsControlMultiplier& Multiplier);` — Adjusts the constraint spring drive settings to reflect the control data. Also enabled or disables the underlying constraint based on whether there is any strength/damping. Returns true if there is some control, false if the drive has no effect
- L71 _prototype_ `ImmediatePhysics::FJointHandle* CreatePhysicsJoint( ImmediatePhysics::FSimulation& Simulation, ImmediatePhysics::FActorHandle& ChildActorHandle, ImmediatePhysics::FActorHandle& ParentActorHandle);` — Creates a physics joint in the form that's useful for controls.
- L76 _prototype_ `void SetPhysicsJointEnabled( ImmediatePhysics::FJointHandle& JointHandle, const bool bIsEnabled);`
- L82 _function_ `inline void UpdateBodyFromModifierData( ImmediatePhysics::FActorHandle* ActorHandle, ImmediatePhysics::FSimulation* PhysicsSimulation, const FPhysicsControlModifierData& ModifierData, const FVector& SimSpaceGravity)` — `UE_DEPRECATED(5.8, "Use the version of UpdateBodyFromModifierData taking references instead instead")`
- L95 _function_ `inline bool UpdateDriveSpringDamperSettings( ImmediatePhysics::FJointHandle* JointHandle, const Chaos::FPBDJointSettings& Settings, const FPhysicsControlData& Data, const FPhysicsControlMultiplier& Multiplier)` — `UE_DEPRECATED(5.8, "Use the version of UpdateDriveSpringDamperSettings taking references instead instead")`
- L109 _function_ `inline ImmediatePhysics::FJointHandle* CreatePhysicsJoint( ImmediatePhysics::FSimulation* Simulation, ImmediatePhysics::FActorHandle* ChildActorHandle, ImmediatePhysics::FActorHandle* ParentActorHandle)` — `UE_DEPRECATED(5.8, "Use the version of CreatePhysicsJoint taking references instead instead")`
- L122 _function_ `inline void SetPhysicsJointEnabled(ImmediatePhysics::FJointHandle* JointHandle, const bool bIsEnabled)` — `UE_DEPRECATED(5.8, "Use the version of SetPhysicsJointEnabled taking references instead instead")`
- L821 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon37d0e2240103`)

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlActor.h` (Public)


#### struct `FInitialPhysicsControl`  
`struct FInitialPhysicsControl`  
_L15-64_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that determines a Physics Control used during initialization of the physics control actor
- L19 _public function_ `FInitialPhysicsControl()`
- L23 _public member_ `TWeakObjectPtr<AActor> ParentActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The owner of the mesh that will be doing the driving. Blank/non-existent means it will happen in world space
- L28 _public member_ `FName ParentMeshComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The mesh that will be doing the driving. If this is blank but there is an actor, then we'll attempt to use the root component. If that doesn't work then it will happen in world space.
- L33 _public member_ `FName ParentBoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — If the parent mesh component is skeletal, then the name of the skeletal mesh bone that will be doing the driving.
- L37 _public member_ `TWeakObjectPtr<AActor> ChildActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The owner of the mesh that the control will be driving
- L42 _public member_ `FName ChildMeshComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The mesh that the control will be driving. If this is blank but there is an actor, then we'll attempt to use the root component
- L47 _public member_ `FName ChildBoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — If the child mesh component is skeletal, then the name of the skeletal mesh bone that the control will be driving.
- L52 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Strength and damping parameters. Can be modified at any time, but will sometimes have been set once during initialization
- L57 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Multiplier for the ControlData. This will typically be modified dynamically, and also expose the ability to set directional strengths
- L63 _public member_ `FPhysicsControlTarget ControlTarget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The position/orientation etc targets for the controls. These are procedural/explicit control targets - skeletal meshes have the option to use skeletal animation as well, in which case these targets are expressed as relative to that animation.

#### struct `FInitialBodyModifier`  
`struct FInitialBodyModifier`  
_L68-100_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that determines a Body Modifier used during initialization of the physics control actor
- L72 _public function_ `FInitialBodyModifier()`
- L76 _public member_ `TWeakObjectPtr<AActor> Actor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The owner of the mesh that that we will modify
- L81 _public member_ `FName MeshComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The mesh that will be modify. If this is blank but there is an actor, then we'll attempt to use the root component.
- L85 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — If the mesh component is skeletal, then the name of the skeletal mesh bone to modify
- L89 _public member_ `FPhysicsControlModifierData BodyModifierData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — How the body should move etc
- L94 _public member_ `FVector KinematicTargetPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target position when kinematic. Note that this is applied on top of any animation target if bUseSkeletalAnimation is set.
- L99 _public member_ `FRotator KinematicTargetOrientation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target orientation when kinematic. Note that this is applied on top of any animation target if bUseSkeletalAnimation is set.

#### struct `FInitialCharacterControls`  
`struct FInitialCharacterControls`  
_L104-131_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that holds the data necessary to set up a default set of limb controls for a character
- L108 _public prototype_ `FInitialCharacterControls();`
- L109 _public prototype_ `~FInitialCharacterControls();`
- L113 _public member_ `TWeakObjectPtr<AActor> CharacterActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The owner of the character skeletal mesh
- L118 _public member_ `FName SkeletalMeshComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The skeletal mesh that will have controls set up. If this is blank but there is an actor, then we'll attempt to use the root component.
- L121 _public member_ `TArray<FPhysicsControlLimbSetupData> LimbSetupData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L124 _public member_ `FPhysicsControlData WorldSpaceControlData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L127 _public member_ `FPhysicsControlData ParentSpaceControlData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L130 _public member_ `FPhysicsControlModifierData BodyModifierData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### class `UPhysicsControlInitializerComponent`  
`class UPhysicsControlInitializerComponent : public USceneComponent`  
_L135-172_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = Physics)`
- inherits: `USceneComponent`
- L140 _public prototype_ `virtual void BeginPlay() override;`
- L146 _public prototype_ `void CreateControls(UPhysicsControlComponent* PhysicsControlComponent);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — This creates all the controls specified in the Initial properties. You can call it explicitly, or you can opt to have it called at BeginPlay using CreateControlsAtBeginPlay.
- L151 _public member_ `FInitialCharacterControls InitialCharacterControls;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControls)` — This can be filled in to automatically create whole-character controls (by specifying limbs etc) for a skeletal mesh during the BeginPlay event.
- L156 _public member_ `TMap<FName, FInitialPhysicsControl> InitialControls;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControls)` — This can be filled in to automatically create controls during the BeginPlay event. If a control already exists with the name (e.g. created as part of InitialCharacterControls) then it will be updated.
- L161 _public member_ `TMap<FName, FInitialBodyModifier> InitialBodyModifiers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControls)` — This can be filled in to automatically create body modifiers during the BeginPlay event. If a body modifier already exists with the name (e.g. created as part of InitialCharacterControls) then it will be updated.
- L166 _public member_ `bool bCreateControlsAtBeginPlay = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControls)` — If set, then CreateControls will be called in our BeginPlay event, attempting to find a PhysicsControlComponent in our parent actor.
- L169 _private prototype_ `void CreateInitialCharacterControls(UPhysicsControlComponent* ControlComponent);`
- L170 _private prototype_ `void CreateOrUpdateInitialControls(UPhysicsControlComponent* ControlComponent);`
- L171 _private prototype_ `void CreateOrUpdateInitialBodyModifiers(UPhysicsControlComponent* ControlComponent);`

#### class `APhysicsControlActor`  
`class APhysicsControlActor : public AActor`  
_L178-188_
- reflection: `UCLASS(ConversionRoot, MinimalAPI, ComponentWrapperClass)`
- inherits: `AActor`
- desc: Actor that holds a PhysicsControlComponent which is then used to apply controls/body modifiers to other actors from "outside", and a PhysicsControlInitializerComponent which provides the ability to create those controls automatically
- L184 _private member_ `TObjectPtr<UPhysicsControlComponent> ControlComponent;` — `UPROPERTY(Category = ControlActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L187 _private member_ `TObjectPtr<UPhysicsControlInitializerComponent> ControlInitializerComponent;` — `UPROPERTY(Category = ControlActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlAsset.h` (Public)


#### class `UPhysicsControlAsset`  
`class UPhysicsControlAsset : public UObject, public IInterface_PreviewMeshProvider`  
_L25-184_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IInterface_PreviewMeshProvider`
- desc: Asset for storing Physics Control Profiles. The asset will contain data that define: - Controls and body modifiers to be created on a mesh - Sets referencing those controls and body modifiers - Full profiles containing settings for all the controls/modifiers - Sparse profiles containing partial sets of settings for specific controls/modifiers It will also be desirable to support "inheritance" - so a generic profile can be made, and then customized for certain characters or scenarios.
- L30 _public prototype_ `UPhysicsControlAsset();`
- L36 _public member_ `FPhysicsControlCharacterSetupData CharacterSetupData;` — `UPROPERTY()` — We can define controls in the form of limbs etc here
- L41 _public member_ `FPhysicsControlAndBodyModifierCreationDatas AdditionalControlsAndModifiers;` — `UPROPERTY()` — Additional controls and modifiers. If these have the same name as one that's already created, they'll just override it.
- L45 _public member_ `FPhysicsControlSetUpdates AdditionalSets;` — `UPROPERTY()` — Additional control and body modifier sets
- L49 _public member_ `TArray<FPhysicsControlControlAndModifierUpdates> InitialControlAndModifierUpdates;` — `UPROPERTY()` — Initial updates to apply immediately after controls and modifiers are created
- L53 _public member_ `TMap<FName, FPhysicsControlControlAndModifierUpdates> Profiles;` — `UPROPERTY()` — The named profiles, which are essentially control and modifier updates
- L61 _public member_ `bool bAutoCompileProfiles = true;` — `UPROPERTY(EditAnywhere, Category = ProfileEditing)` — Whether editing the profiles will automatically compile.
- L65 _public member_ `bool bAutoInvokeProfiles = true;` — `UPROPERTY(EditAnywhere, Category = ProfileEditing, Meta = (EditCondition="AutoCompileProfiles"))` — Whether to automatically invoke profiles that have been edited (and have auto-compiled) when simulating
- L69 _public member_ `bool bAutoCompileSetup = true;` — `UPROPERTY(EditAnywhere, Category = SetupEditing)` — Whether editing the setup data will automatically compile.
- L73 _public member_ `bool bAutoReinitSetup = true;` — `UPROPERTY(EditAnywhere, Category = SetupEditing, Meta = (EditCondition="AutoCompileSetup"))` — Whether to automatically reinitialize following editing of setup data (when auto-compiling) when simulating
- L77 _public member_ `bool bAutoInvokeProfileAfterSetup = true;` — `UPROPERTY(EditAnywhere, Category = SetupEditing, Meta = (EditCondition="AutoCompileSetup"))` — Whether to automatically re-invoke the previously invoked profile after automatically running the setup
- L81 _public member_ `TSoftObjectPtr<UPhysicsControlAsset> ParentAsset;` — `UPROPERTY(EditAnywhere, Category = Inheritance)` — A profile asset to inherit from (can be null). If set, we will just add/modify data in that
- L86 _public member_ `TArray<TSoftObjectPtr<UPhysicsControlAsset>> AdditionalProfileAssets;` — `UPROPERTY(EditAnywhere, Category = Inheritance)` — Additional profile assets from which profiles (not the setup data, extra sets etc) will be added to this asset.
- L92 _public member_ `TSoftObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(AssetRegistrySearchable, EditAnywhere, Category = PreviewMesh)` — The PhysicsAsset that this control asset is targeting. This will also determine the preview mesh. You will need to close/re-open the Physics Control Asset editor in order to see the effect of changing it.
- L100 _public member_ `FPhysicsControlCharacterSetupData MyCharacterSetupData;` — `UPROPERTY(EditAnywhere, Category = Setup, meta=(DisplayName="Character Setup Data"))` — We can define controls in the form of limbs etc here
- L105 _public member_ `FPhysicsControlAndBodyModifierCreationDatas MyAdditionalControlsAndModifiers;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (DisplayName = "Additional Controls and Modifiers"))` — Additional controls and modifiers. If these have the same name as one that's already created, they'll just override it.
- L109 _public member_ `FPhysicsControlSetUpdates MyAdditionalSets;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (DisplayName = "Additional Sets"))` — Additional control and body modifier sets
- L113 _public member_ `TArray<FPhysicsControlControlAndModifierUpdates> MyInitialControlAndModifierUpdates;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (DisplayName = "Initial Control and Modifier Updates"))` — Initial updates to apply immediately after controls and modifiers are created
- L117 _public member_ `TMap<FName, FPhysicsControlControlAndModifierUpdates> MyProfiles;` — `UPROPERTY(EditAnywhere, Category = Profiles, meta = (DisplayName = "Profiles"))` — The named profiles, which are essentially control and modifier updates
- L124 _public prototype_ `DECLARE_EVENT_OneParam(FPhysicsControlAssetEditor, FOnControlAssetCompiled, bool);`
- L125 _public function_ `FOnControlAssetCompiled& OnControlAssetCompiled()`
- L129 _public prototype_ `void ShowCompiledData() const;` — `UFUNCTION(CallInEditor, Category = Actions)` — Shows all the controls etc that would be made
- L134 _public prototype_ `void Compile();` — `UFUNCTION(CallInEditor, Category = Actions)` — Collapses inherited and authored profiles etc to make a profile asset that can be read without need for subsequent processing.
- L139 _public prototype_ `bool IsCompilationNeeded() const;` — `UFUNCTION(CallInEditor, Category = Actions)` — Returns true if compilation would change any of our compiled data. Note that this is potentially slow as it simply compiles and compares the result with the data we already have.
- L143 _public prototype_ `TArray<FName> GetDirtyProfiles() const;` — `UFUNCTION(CallInEditor, Category = Actions)` — Returns a list of all the profiles that need compilation
- L147 _public prototype_ `bool IsSetupDirty() const;` — `UFUNCTION(CallInEditor, Category = Actions)` — Returns true if the setup data need compilation such that the controls etc need to be re-initialized.
- L151 _public prototype_ `FPhysicsControlCharacterSetupData GetCharacterSetupData() const;` — Combines and returns data from our parent and ourself
- L154 _public prototype_ `FPhysicsControlAndBodyModifierCreationDatas GetAdditionalControlsAndModifiers() const;` — Combines and returns data from our parent and ourself
- L157 _public prototype_ `FPhysicsControlSetUpdates GetAdditionalSets() const;` — Combines and returns data from our parent and ourself
- L160 _public prototype_ `TArray<FPhysicsControlControlAndModifierUpdates> GetInitialControlAndModifierUpdates() const;` — Combines and returns data from our parent and ourself
- L163 _public prototype_ `TMap<FName, FPhysicsControlControlAndModifierUpdates> GetProfiles() const;` — Combines and returns data from our parent and ourself
- L166 _protected member_ `FOnControlAssetCompiled OnControlAssetCompiledDelegate;`
- L173 _public prototype_ `virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true) override;` — IInterface_PreviewMeshProvider interface
- L174 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh() const override;`
- L179 _public prototype_ `UPhysicsAsset* GetPhysicsAsset() const;` — This loads the asset if necessary
- L180 _public prototype_ `void SetPhysicsAsset(UPhysicsAsset* InPhysicsAsset);`
- L182 _public prototype_ `static const FName GetPreviewMeshPropertyName();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PHYSICSCONTROL_API`
- L124 _delegate_ `DECLARE_EVENT_OneParam(FPhysicsControlAssetEditor, FOnControlAssetCompiled, bool);`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlBPLibrary.h` (Public)


#### struct `FRigidBodyWithControlReference`  
`struct FRigidBodyWithControlReference : public FAnimNodeReference`  
_L17-22_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L21 _public typedef_ `typedef FAnimNode_RigidBodyWithControl FInternalNodeType;`

#### class `UPhysicsControlBPLibrary`  
`class UPhysicsControlBPLibrary : public UBlueprintFunctionLibrary`  
_L26-199_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L33 _private prototype_ `UPARAM(ref, DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& InParameters, UPARAM(DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& OutParameters, const FName Name, const FPhysicsControlSparseData& ControlData);`
- L41 _private prototype_ `UPARAM(ref, DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& InParameters, UPARAM(DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& OutParameters, const TArray<FName>& Names, const FPhysicsControlSparseData& ControlData);`
- L66 _private prototype_ `UPARAM(ref, DisplayName = "From Parameters") FPhysicsControlControlAndModifierParameters& InParametersA, UPARAM(ref, DisplayName = "To Parameters") FPhysicsControlControlAndModifierParameters& InParametersB, UPARAM(DisplayName = "Weight") const float InInterpolationWeight, UPARAM(DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& OutPa`
- L78 _private prototype_ `UPARAM(ref, DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& InParameters, UPARAM(ref, DisplayName = "Start Parameters") const FPhysicsControlNamedControlParameters& InStartControlParameters, UPARAM(ref, DisplayName = "End Parameters") const FPhysicsControlNamedControlParameters& InEndControlParameters, const TArray<FName>& ControlNames, FPhysicsControlControlAndModifierParameters& OutParameters);`
- L91 _private prototype_ `UPARAM(ref) FPhysicsControlControlAndModifierParameters& InParameters, UPARAM(ref) const FPhysicsControlNamedModifierParameters& InStartModifierParameters, UPARAM(ref) const FPhysicsControlNamedModifierParameters& InEndModifierParameters, const TArray<FName>& ModifierNames, UPARAM(DisplayName = "Parameters") FPhysicsControlControlAndModifierParameters& OutPa`
- L99 _private prototype_ `static FRigidBodyWithControlReference ConvertToRigidBodyWithControl( const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PhysicsControl", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a Rigid Body With Control node reference from an anim node reference
- L105 _private function_ `static void ConvertToRigidBodyWithControlPure( const FAnimNodeReference& Node, FRigidBodyWithControlReference& RigidBodyWithControl, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|PhysicsControl", meta = (BlueprintThreadSafe, DisplayName = "Convert to Rigid Body With Control"))` — Get a Rigid Body With Control node from an anim node (pure)
- L117 _private prototype_ `static FRigidBodyWithControlReference SetOverridePhysicsAsset(const FRigidBodyWithControlReference& Node, UPhysicsAsset* PhysicsAsset);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PhysicsControl", meta = (BlueprintThreadSafe))` — Set the physics asset on the Rigid Body With Control anim graph node.
- L122 _private prototype_ `UPARAM(DisplayName = "Node") const FRigidBodyWithControlReference& RigidBodyWithControl, const FName SetName);`
- L146 _private prototype_ `static bool DisableCollisionBetweenBodies( UPrimitiveComponent* FirstComponent, const FName FirstBoneName, UPrimitiveComponent* SecondComponent, const FName SecondBoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Disables collision between two physics bodies at runtime. Works for two bones on the same skeletal mesh, a skeletal-mesh bone vs. a separate primitive, or two unrelated primitives. Notes: - Both bodies must be in the same physics scene / solver. - Both bodies must be dynamic or kinematic; static particles are not supported by the underlying Chaos ignore-collision manager. - The effect is transient: it does not survive body re-creation (LOD swap, SetSkeletalMesh, SetPhysicsAsset, physics-state teardown). To restore the disable after such an event, call the function again. Returns true on success; false on validation failure (null component, missing bone, mismatched solvers, static body, etc.) - a warning is logged in that case.
- L166 _private prototype_ `static bool EnableCollisionBetweenBodies( UPrimitiveComponent* FirstComponent, const FName FirstBoneName, UPrimitiveComponent* SecondComponent, const FName SecondBoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Re-enables collision between two physics bodies that was previously suppressed by DisableCollisionBetweenBodies. Works for two bones on the same skeletal mesh, a skeletal-mesh bone vs. a separate primitive, or two unrelated primitives. Calling this for a pair that is not currently disabled is a no-op. Notes: - Both bodies must be in the same physics scene / solver. - Both bodies must be dynamic or kinematic; static particles are not supported by the underlying Chaos ignore-collision manager. - Body re-creation (LOD swap, SetSkeletalMesh, SetPhysicsAsset, physics-state teardown) already restores default collision, so this call is only needed to undo a still-live DisableCollisionBetweenBodies. Returns true on success; false on validation failure (null component, missing bone, mismatched solvers, static body, etc.) - a warning is logged in that case.
- L181 _private prototype_ `static bool DisableCollisionBetweenBodyArrays( UPrimitiveComponent* FirstComponent, const TArray<FName>& FirstBoneNames, UPrimitiveComponent* SecondComponent, const TArray<FName>& SecondBoneNames);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Bulk variant of DisableCollisionBetweenBodies. Disables collision for every (FirstBoneNames[i], SecondBoneNames[j]) combination in a single call. An empty bone array, or if the bone name is blank/None, means "use the component's single body" (e.g. for a static-mesh component) and is treated as a one-element array of NAME_None. Self-pairs (the same body on both sides) are skipped. See DisableCollisionBetweenBodies for the constraints that apply per pair. Returns true only when every pair was applied successfully. Per-pair validation failures log a warning and are skipped. The remaining valid pairs are still applied, and the return value is false to signal partial application.
- L196 _private prototype_ `static bool EnableCollisionBetweenBodyArrays( UPrimitiveComponent* FirstComponent, const TArray<FName>& FirstBoneNames, UPrimitiveComponent* SecondComponent, const TArray<FName>& SecondBoneNames);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Bulk variant of EnableCollisionBetweenBodies. Re-enables collision for every (FirstBoneNames[i], SecondBoneNames[j]) combination in a single call. An empty bone array, or if the bone name is blank/None, means "use the component's single body" (e.g. for a static-mesh component) and is treated as a one-element array of NAME_None. Self-pairs and pairs that aren't currently disabled are no-ops. See EnableCollisionBetweenBodies for the constraints that apply per pair. Returns true only when every pair was applied successfully. Per-pair validation failures log a warning and are skipped. The remaining valid pairs are still applied, and the return value is false to signal partial application.

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlComponent.h` (Public)


#### enum `EResetToCachedTargetBehavior`  
`enum class EResetToCachedTargetBehavior : uint8`  
_L31-41_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies how any reset to cached target should work.
- L36 _public enumerator_ `ResetImmediately` — Reset of the associated physics bodies is done immediately, to whatever transforms are in the cache. These will reflect the previous or the upcoming animation targets, depending on what stage of the tick this is called.
- L40 _public enumerator_ `ResetDuringUpdateControls` — Reset of the associated physics bodies will be done during the next Tick (or UpdateControls). Note that this will reset the bodies to the updated animation targets, and then there will be a subsequent physics update, which will result in the final transforms.

#### class `UPhysicsControlComponent`  
`class UPhysicsControlComponent : public USceneComponent`  
_L56-1891_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent), ClassGroup = Physics)`
- inherits: `USceneComponent`
- desc: This is the main Physics Control Component class which manages Controls and Body Modifiers associated with one or more static or skeletal meshes. You can add this as a component to an actor containing a mesh and then use it to create, configure and destroy Controls/Body Modifiers: Controls are used to control one physics body relative to another (or the world). These controls are done through physical spring/damper drives. Body Modifiers are used to update the most important physical properties of physics bodies such as whether they are simulated vs kinematic, or whether they experience gravity. Note that Controls and Body Modifiers are given names (which are predictable). These names can then be stored (perhaps in arrays) to make it easy to quickly change multiple Controls/Body Modifiers.
- L70 _public prototype_ `void UpdateTargetCaches(float DeltaTime);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Allows manual ticking so that your code can run in between updating the target caches and updating the controls. This allows you to read the targets coming from animation and use those values to create your own controls etc. To use this function, you should disable ticking of the Physics Control Component, and ensure that the relevant Skeletal Mesh Component (if being used) has ticked, using a tick prerequisite. Then explicitly call (in order) UpdateTargetCaches and UpdateControls as you process your tick.
- L80 _public prototype_ `void UpdateControls(float DeltaTime);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Allows manual ticking so that your code can run in between updating the target caches and updating the controls and body modifiers. This allows you to read the targets coming from animation and use those values to create your own controls etc. To use this function, you should disable ticking of the Physics Control Component, and ensure that the relevant Skeletal Mesh Component (if being used) has ticked, using a tick prerequisite. Then explicitly call (in order) UpdateTargetCaches and UpdateControls as you process your tick.
- L91 _public prototype_ `FName CreateControl( UPrimitiveComponent* ParentComponent, FName ParentBoneName, UPrimitiveComponent* ChildComponent, const FName ChildBoneName, const FPhysicsControlData ControlData, const FPhysicsControlTarget ControlTarget, FName Set, FString NamePrefix = TEXT("") );` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a new control for mesh components @param ControlData   Describes the initial strength etc of the new control @param ControlTarget Describes the initial target for the new control @param Set Which set to include the control in (optional). Note that it automatically gets added to the set "All" @param NamePrefix Optional string that is prefixed to the control that is created. @return The name of the new control
- L111 _public prototype_ `bool CreateNamedControl( FName Name, UPrimitiveComponent* ParentComponent, const FName ParentBoneName, UPrimitiveComponent* ChildComponent, const FName ChildBoneName, const FPhysicsControlData ControlData, const FPhysicsControlTarget ControlTarget, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Creates a new control for mesh components @param Name The name of the control that will be created. Creation will fail if this name is already in use. @param ControlData   Describes the initial strength etc of the new control @param ControlTarget Describes the initial target for the new control @param Set Which set to include the control in (optional). Note that it automatically gets added to the set "All" @return True if a new control was created, false if a control of the specified name already exists
- L132 _public prototype_ `TArray<FName> CreateControlsFromSkeletalMeshBelow( USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName, const bool bIncludeSelf, const EPhysicsControlType ControlType, const FPhysicsControlData ControlData, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of controls controlling a skeletal mesh @param SkeletalMeshComponent The skeletal mesh which will have controls @param BoneName The name of the bone below which controls should be created. Each bone will be the child in a control @param bIncludeSelf Whether or not to include BoneName when creating controls @param ControlType What type of control to create. This determines what the parent will be for each control @param ControlData   Describes the initial strength etc of the new control @param Set Which set to include the control in (optional). Note that it automatically gets added to the set "All" @return An array of the controls that have been created
- L161 _public prototype_ `TArray<FName> CreateControlsFromSkeletalMeshAndConstraintProfileBelow( USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName, const bool bIncludeSelf, const FName ConstraintProfile, const FName Set, const bool bEnabled = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of ParentSpace controls controlling a skeletal mesh, initializing them with a constraint profile @param SkeletalMeshComponent The skeletal mesh which will have controls @param BoneName The name of the bone below which controls should be created. Each bone will be the child in a control @param bIncludeSelf Whether or not to include BoneName when creating controls @param ConstraintProfile The constraint profile to use for initializing the control strength and damping (etc) parameters. Note that the controls will all be created in "parent space" - i.e. with each part controlled relative to its parent. The strength and damping will be taken from the values that the relevant joint in the physics asset would have given the constraint profile (or the default profile if it can't be found) - though they will not match exactly if the linear drive and different x/y/z values, or if the angular drive was using twist/swing instead of slerp. Note also that the joint constraints do not use the animation velocity as a target, so when creating controls in this way the control will set the skeletal animation velocity multiplier to zero. @param Set Which set to include the control in (optional). Note that it automatically gets added to the set "All" @param bEnabled If true then the control will be enabled immediately. If false you will need to call SetControlEnabled(true) in order to enable it. @return An array of the controls that have been created
- L179 _public prototype_ `TArray<FName> CreateControlsFromSkeletalMesh( USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FName>& BoneNames, const EPhysicsControlType ControlType, const FPhysicsControlData ControlData, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of controls controlling a skeletal mesh @param SkeletalMeshComponent The skeletal mesh which will have controls @param BoneNames The names of bones for which controls should be created. Each bone will be the child in a control @param ControlType What type of control to create. This determines what the parent will be for each control @param ControlData   Describes the initial strength etc of the new control @param Set Which set to include the control in (optional). Note that it automatically gets added to the set "All" @return An array of the controls that have been created
- L206 _public prototype_ `TArray<FName> CreateControlsFromSkeletalMeshAndConstraintProfile( USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FName>& BoneNames, const FName ConstraintProfile, const FName Set, const bool bEnabled = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of ParentSpace controls controlling a skeletal mesh, initializing them with a constraint profile @param SkeletalMeshComponent The skeletal mesh which will have controls @param BoneNames The names of bones for which controls should be created. Each bone will be the child in a control @param ConstraintProfile The constraint profile to use for initializing the control strength and damping (etc) parameters. Note that the controls will all be created in "parent space" - i.e. with each part controlled relative to its parent. The strength and damping will be taken from the values that the relevant joint in the physics asset would have given the constraint profile (or the default profile if it can't be found) - though they will not match exactly if the linear drive and different x/y/z values, or if the angular drive was using twist/swing instead of slerp. Note also that the joint constraints do not use the animation velocity as a target, so when creating controls in this way the control will set the skeletal animation velocity multiplier to zero. @param Set Which set to include the control in (optional). Note that it automatically gets added to the set "All" @param bEnabled If true then the control will be enabled immediately. If false you will need to call SetControlEnabled(true) in order to enable it. @return An array of the controls that have been created
- L223 _public prototype_ `TMap<FName, FPhysicsControlLimbBones> GetLimbBonesFromSkeletalMesh( USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FPhysicsControlLimbSetupData>& LimbSetupData) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Calculates which bones belong to which limb in a skeletal mesh @param SkeletalMeshComponent The skeletal mesh which will be analyzed @param LimbSetupData This needs to be filled in with the list of limbs to "discover". Note that the limbs should be listed starting at the "leaf" (i.e. outer) parts of the skeleton first, typically finishing with the spine. In addition, the spine limb is typically specified using the first spine bone, but flagging it to include its parent (normally the pelvis). @return A map of limb names to bones
- L241 _public prototype_ `TMap<FName, FPhysicsControlNames> CreateControlsFromLimbBones( FPhysicsControlNames& AllControls, const TMap<FName, FPhysicsControlLimbBones>& LimbBones, const EPhysicsControlType ControlType, const FPhysicsControlData ControlData, UPrimitiveComponent* WorldComponent = nullptr, FName WorldBoneName = NAME_None, FString NamePrefix = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of controls controlling a skeletal mesh, grouped together in limbs @param AllControls A single container for all the controls that have been created @param LimbBones A map relating the limbs and the bones that they contain. Typically create this using GetLimbBonesFromSkeletalMesh @param ControlType What type of control to create. This determines what the parent will be for each control @param ControlData Describes the initial strength etc of the new control @param WorldComponent Optional component to use as the parent object for any "world-space" controls that are created. Will be ignored if the controls being created are not world-space. @param WorldBoneName Additional bone name to identify the world object if the WorldComponent is actually a skeletal mesh component. @param NamePrefix Optional string that is prefixed to each control that is created. @return A map containing the controls for each limb
- L269 _public prototype_ `TMap<FName, FPhysicsControlNames> CreateControlsFromLimbBonesAndConstraintProfile( FPhysicsControlNames& AllControls, const TMap<FName, FPhysicsControlLimbBones>& LimbBones, const FName ConstraintProfile, const bool bEnabled = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of ParentSpace controls controlling a skeletal mesh, grouped together in limbs, initializing them with a constraint profile @param AllControls A single container for all the controls that have been created @param LimbBones A map relating the limbs and the bones that they contain. Typically create this using GetLimbBonesFromSkeletalMesh @param ConstraintProfile The constraint profile to use for initializing the control strength and damping (etc) parameters. Note that the controls will all be created in "parent space" - i.e. with each part controlled relative to its parent. The strength and damping will be taken from the values that the relevant joint in the physics asset would have given the constraint profile (or the default profile if it can't be found) - though they will not match exactly if the linear drive and different x/y/z values, or if the angular drive was using twist/swing instead of slerp. Note also that the joint constraints do not use the animation velocity as a target, so when creating controls in this way the control will set the skeletal animation velocity multiplier to zero. @param bEnabled If true then the control will be enabled immediately. If false you will need to call SetControlEnabled(true) in order to enable it. @return A map containing the controls for each limb
- L277 _public prototype_ `void DestroyAllControlsAndBodyModifiers();` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Destroys all controls and body modifiers
- L287 _public prototype_ `bool DestroyControl( const FName Name, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Destroys a control or controls in a set Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to destroy. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L299 _public prototype_ `bool DestroyControls( const TArray<FName>& Names, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Destroys all controls or sets of controls Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to destroy. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L307 _public prototype_ `bool DestroyControlsInSet(const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Destroys all controls in a set @param Set The set of controls to use to destroy. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created.
- L317 _public prototype_ `bool SetControlParent( const FName Name, UPrimitiveComponent* ParentComponent, const FName ParentBoneName, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Updates the parent object part of a control or controls in a set. Note that this won't change the name of the control (which may subsequently be misleading), or any set it is included in, etc. Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L329 _public prototype_ `bool SetControlParents( const TArray<FName>& Names, UPrimitiveComponent* ParentComponent, const FName ParentBoneName, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Updates the parent object part of controls or controls in a set. Note that this won't change the name of the controls (which may subsequently be misleading), or any set they are included in, etc. Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L334 _public prototype_ `bool SetControlParentsInSet( const FName Set, UPrimitiveComponent* ParentComponent, const FName ParentBoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)`
- L349 _public prototype_ `bool SetControlData( const FName Name, const FPhysicsControlData ControlData, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing control data in a control or controls in a set - i.e. the strengths etc of the control driving towards the target Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param ControlData The new control data @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L364 _public prototype_ `bool SetControlDatas( const TArray<FName>& Names, const FPhysicsControlData ControlData, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data in controls or controls in sets - i.e. the strengths etc of the controls driving towards the targets Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ControlData The new control data @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L374 _public prototype_ `bool SetControlDatasInSet(const FName Set, const FPhysicsControlData ControlData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data - i.e. the strengths etc of the controls driving towards the targets @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param ControlData The new control data
- L386 _public prototype_ `bool SetControlSparseData( const FName Name, const FPhysicsControlSparseData ControlData, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing control data in a control or controls in a set - i.e. the strengths etc of the control driving towards the target Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param ControlData The new control data @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L401 _public prototype_ `bool SetControlSparseDatas( const TArray<FName>& Names, const FPhysicsControlSparseData ControlData, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data in controls or controls in sets - i.e. the strengths etc of the controls driving towards the targets Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ControlData The new control data @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L411 _public prototype_ `bool SetControlSparseDatasInSet(const FName Set, const FPhysicsControlSparseData ControlData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data - i.e. the strengths etc of the controls driving towards the targets @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param ControlData The new control data
- L423 _public prototype_ `bool SetControlMultiplier( const FName Name, const FPhysicsControlMultiplier ControlMultiplier, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies existing control data in a control or controls in a set using the multipliers Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param ControlMultipliers The new control multipliers @param bEnableControl Enables the control if it is currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L438 _public prototype_ `bool SetControlMultipliers( const TArray<FName>& Names, const FPhysicsControlMultiplier ControlMultiplier, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data in controls or controls in sets using the multipliers Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ControlMultiplier The new control multiplier @param bEnableControl Enables the controls if currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L449 _public prototype_ `bool SetControlMultipliersInSet( const FName Set, const FPhysicsControlMultiplier ControlMultiplier, const bool bEnableControl = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data using the multipliers @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param ControlMultiplier The new control multiplier @param bEnableControl Enables the controls if currently disabled
- L462 _public prototype_ `bool SetControlSparseMultiplier( const FName Name, const FPhysicsControlSparseMultiplier ControlMultiplier, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies existing control data in a control or controls in a set using the multipliers Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param ControlMultipliers The new control multipliers @param bEnableControl Enables the control if it is currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L477 _public prototype_ `bool SetControlSparseMultipliers( const TArray<FName>& Names, const FPhysicsControlSparseMultiplier ControlMultiplier, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data in controls or controls in sets using the multipliers Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ControlMultiplier The new control multiplier @param bEnableControl Enables the controls if currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L488 _public prototype_ `bool SetControlSparseMultipliersInSet( const FName Set, const FPhysicsControlSparseMultiplier ControlMultiplier, const bool bEnableControl = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control data using the multipliers @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param ControlMultiplier The new control multiplier @param bEnableControl Enables the controls if currently disabled
- L507 _public prototype_ `bool SetControlLinearData( const FName Name, const float Strength = 1.0f, const float DampingRatio = 1.0f, const float ExtraDamping = 0.0f, const float MaxForce = 0.0f, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies existing control's linear data in a control or controls in a set - i.e. the strengths etc of the control driving towards the target Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param Strength The strength used to drive linear motion @param DampingRatio The amount of damping associated with the linear strength. 1 Results in critically damped motion @param ExtraDamping The amount of additional linear damping @param MaxForce The maximum force used to drive the linear motion. Zero indicates no limit. @param bEnableControl Enables the control if it is currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L531 _public prototype_ `bool SetControlAngularData( const FName Name, const float Strength = 1.0f, const float DampingRatio = 1.0f, const float ExtraDamping = 0.0f, const float MaxTorque = 0.0f, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies existing control's angular data in a control or controls in a set - i.e. the strengths etc of the control driving towards the target Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param Strength The strength used to drive angular motion @param DampingRatio The amount of damping associated with the angular strength. 1 Results in critically damped motion @param ExtraDamping The amount of additional angular damping @param MaxTorque The maximum torque used to drive the angular motion. Zero indicates no limit. @param bEnableControl Enables the control if it is currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L547 _public prototype_ `bool SetControlPoint(const FName Name, const FVector Position);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets the point at which controls will "push" the child object. @param Name The name of the control to update. @param Position The position of the control point on the child mesh object (only relevant if that object is in use and is being simulated)
- L553 _public prototype_ `bool ResetControlPoint(const FName Name);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Resets the control point to the center of mass of the mesh @param Name The name of the control to update.
- L566 _public prototype_ `bool SetControlTarget( const FName Name, const FPhysicsControlTarget ControlTarget, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing control target in a control or controls in a set - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param ControlTarget The new target for the control @param bEnableControl Enables the control if it is currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L583 _public prototype_ `bool SetControlTargets( const TArray<FName>& Names, const FPhysicsControlTarget ControlTarget, const bool bEnableControl = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control targets in controls or controls in sets - i.e. what they are driving towards, relative to the parent objects Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ControlTarget The new target for the controls @param bEnableControl Enables the controls if currently disabled @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L594 _public prototype_ `bool SetControlTargetsInSet( const FName Set, const FPhysicsControlTarget ControlTarget, const bool bEnableControl = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control targets - i.e. what they are driving towards, relative to the parent objects @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param ControlTarget The new target for the controls @param bEnableControl Enables the controls if currently disabled
- L620 _public prototype_ `bool SetControlTargetPositionAndOrientation( const FName Name, const FVector Position, const FRotator Orientation, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing control target in a control or controls in a set - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param Position The new position target for the control @param Orientation The new orientation target for the control @param VelocityDeltaTime If non-zero, the target velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl Enables the control if it is currently disabled @param bApplyControlPointToTarget If true, then the target position/orientation is treated as a "virtual" object, where the system attempts to move the object to match the pose of this "virtual" object that has been placed at the target transform. Use this when you want to specify the target transform for the object as a whole. If false, then the target transform is used as is, and the system drives the control point towards this transform. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified @return Returns true if the control/set could be found
- L651 _public prototype_ `bool SetControlTargetPositionsAndOrientations( const TArray<FName>& Names, const FVector Position, const FRotator Orientation, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control targets in controls or controls in sets - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The name of the controls or sets of controls to update. @param Position The new position target for the control @param Orientation The new orientation target for the control @param VelocityDeltaTime If non-zero, the target velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl Enables the control if it is currently disabled @param bApplyControlPointToTarget If true, then the target position/orientation is treated as a "virtual" object, where the system attempts to move the object to match the pose of this "virtual" object that has been placed at the target transform. Use this when you want to specify the target transform for the object as a whole. If false, then the target transform is used as is, and the system drives the control point towards this transform. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified @return Returns true if all the control names were found
- L664 _public prototype_ `bool SetControlTargetPositionsAndOrientationsInSet( const FName SetName, const FVector Position, const FRotator Orientation, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Calls SetControlTargetPositionAndOrientation for each control in the set @return Returns true if the set was be found
- L693 _public prototype_ `bool SetControlTargetPosition( const FName Name, const FVector Position, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing control target of a control or controls in a set - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param Position          The new position target for the control @param VelocityDeltaTime If non-zero, the target velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl Enables the control if it is currently disabled @param bApplyControlPointToTarget If true, then the target position/orientation is treated as a "virtual" object, where the system attempts to move the object to match the pose of this "virtual" object that has been placed at the target transform. Use this when you want to specify the target transform for the object as a whole. If false, then the target transform is used as is, and the system drives the control point towards this transform. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified @return Returns true if the control/set can be found
- L722 _public prototype_ `bool SetControlTargetPositions( const TArray<FName>& Names, const FVector Position, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control targets in controls or controls in sets - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The name of the controls or sets of controls to update. @param Position The new position target for the control @param VelocityDeltaTime If non-zero, the target velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl Enables the control if it is currently disabled @param bApplyControlPointToTarget If true, then the target position/orientation is treated as a "virtual" object, where the system attempts to move the object to match the pose of this "virtual" object that has been placed at the target transform. Use this when you want to specify the target transform for the object as a whole. If false, then the target transform is used as is, and the system drives the control point towards this transform. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified @return Returns true if all the controls/sets can be found
- L734 _public prototype_ `bool SetControlTargetPositionsInSet( const FName SetName, const FVector Position, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Calls SetControlTargetPosition for each of the controls in the set @return Returns true if the set name and its controls can be found
- L762 _public prototype_ `bool SetControlTargetOrientation( const FName Name, const FRotator Orientation, const float AngularVelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing control target in a control or controls in a set - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param Orientation The new orientation target for the control @param AngularVelocityDeltaTime If non-zero, the target angular velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl Enables the control if it is currently disabled @param bApplyControlPointToTarget If true, then the target position/orientation is treated as a "virtual" object, where the system attempts to move the object to match the pose of this "virtual" object that has been placed at the target transform. Use this when you want to specify the target transform for the object as a whole. If false, then the target transform is used as is, and the system drives the control point towards this transform. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified @return Returns true if the control/set can be found
- L792 _public prototype_ `bool SetControlTargetOrientations( const TArray<FName>& Names, const FRotator Orientation, const float AngularVelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing control targets in controls or controls in sets - i.e. what it is driving towards, relative to the parent object Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param Orientation The new orientation target for the control @param AngularVelocityDeltaTime If non-zero, the target angular velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl Enables the control if it is currently disabled @param bApplyControlPointToTarget If true, then the target position/orientation is treated as a "virtual" object, where the system attempts to move the object to match the pose of this "virtual" object that has been placed at the target transform. Use this when you want to specify the target transform for the object as a whole. If false, then the target transform is used as is, and the system drives the control point towards this transform. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified @return Returns true if all the controls can be found
- L804 _public prototype_ `bool SetControlTargetOrientationsInSet( const FName SetName, const FRotator Orientation, const float AngularVelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Calls SetControlTargetOrientation for each of the controls in the set @return Returns true if the set and all the controls can be found
- L815 _public prototype_ `bool SetControlTargetPositionsFromArray( const TArray<FName>& Names, const TArray<FVector>& Positions, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Calls SetControlTargetPosition for each element of the control names and positions. These array should match in size. @return true if the control/position arrays match, false if they don't.
- L826 _public prototype_ `bool SetControlTargetOrientationsFromArray( const TArray<FName>& Names, const TArray<FRotator>& Orientations, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Calls SetControlTargetPosition for each element of the control names and positions. These array should match in size. @return true if the control/position arrays match, false if they don't.
- L837 _public prototype_ `bool SetControlTargetPositionsAndOrientationsFromArray( const TArray<FName>& Names, const TArray<FVector>& Positions, const TArray<FRotator>& Orientations, const float VelocityDeltaTime, const bool bEnableControl = true, const bool bApplyControlPointToTarget = false);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Calls SetControlTargetPositionAndOrientation for each element of the control names, positions and orientations. These array should match in size. @return true if the control/position/orientation arrays match, false if they don't.
- L858 _public prototype_ `bool SetControlTargetPoses( const FName Name, const FVector ParentPosition, const FRotator ParentOrientation, const FVector ChildPosition, const FRotator ChildOrientation, const float VelocityDeltaTime, const bool bEnableControl = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Calculates and sets an existing control target. This takes the "virtual" position/orientation of the parent and child and calculates the relative control. Note that this will set bApplyControlPointToTarget to true. @param Name              The name of the control to update. @param ParentPosition    The virtual/target parent position @param ParentOrientation The virtual/target parent orientation @param ChildPosition     The virtual/target child position @param ChildOrientation  The virtual/target child orientation @param VelocityDeltaTime If non-zero, the target velocity will be calculated using the current target position. If zero, the target velocity will be set to zero. @param bEnableControl    Enables the control if it is currently disabled @return                  Returns true if the control was found and modified, false if not
- L881 _public prototype_ `bool SetControlUseSkeletalAnimation( const FName Name, const bool bUseSkeletalAnimation = true, const float AngularTargetVelocityMultiplier = 1.0f, const float LinearTargetVelocityMultiplier = 1.0f, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets whether or not the control or controls in a set should use skeletal animation for the targets Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name The name of the control or set of controls to update. @param bUseSkeletalAnimation If true then the targets will be a combination of the skeletal animation (if there is any) and the control target that has been set @param AngularTargetVelocityMultiplier If skeletal animation is being used, then this determines the amount of angular velocity extracted from the animation that is used as targets for the controls @param LinearTargetVelocityMultiplier If skeletal animation is being used, then this determines the amount of linear velocity extracted from the animation that is used as targets for the controls @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L904 _public prototype_ `bool SetControlsUseSkeletalAnimation( const TArray<FName>& Names, const bool bUseSkeletalAnimation = true, const float AngularTargetVelocityMultiplier = 1.0f, const float LinearTargetVelocityMultiplier = 1.0f, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets whether or not the controls or controls in sets should use skeletal animation for the targets Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param bUseSkeletalAnimation If true then the targets will be a combination of the skeletal animation (if there is any) and the control target that has been set @param AngularTargetVelocityMultiplier If skeletal animation is being used, then this determines the amount of angular velocity extracted from the animation that is used as targets for the controls @param LinearTargetVelocityMultiplier If skeletal animation is being used, then this determines the amount of linear velocity extracted from the animation that is used as targets for the controls @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L923 _public prototype_ `bool SetControlsInSetUseSkeletalAnimation( const FName Set, const bool bUseSkeletalAnimation = true, const float AngularTargetVelocityMultiplier = 1.0f, const float LinearTargetVelocityMultiplier = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets whether or not the controls should use skeletal animation for the targets @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param bUseSkeletalAnimation If true then the targets will be a combination of the skeletal animation (if there is any) and the control target that has been set @param AngularTargetVelocityMultiplier If skeletal animation is being used, then this determines the amount of angular velocity extracted from the animation that is used as targets for the controls @param LinearTargetVelocityMultiplier If skeletal animation is being used, then this determines the amount of linear velocity extracted from the animation that is used as targets for the controls
- L938 _public prototype_ `bool SetControlEnabled( const FName Name, const bool bEnable = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Activates or deactivates a control or controls in a set. Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Name     The name of the control or set of controls to update. @param bEnable  Whether to enable/disable the control @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L952 _public prototype_ `bool SetControlsEnabled( const TArray<FName>& Names, const bool bEnable = true, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Activates or deactivates controls or sets of controls Standard set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param Names The names of the controls or sets of controls to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param bEnable  Whether to enable/disable the controls @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L963 _public prototype_ `bool SetControlsInSetEnabled(const FName Set, const bool bEnable = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)`
- L971 _public prototype_ `bool SetControlDisableCollision( const FName Name, const bool bDisableCollision, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — @param Name The name of the control or set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param bDisableCollision If set then the control will disable collision between the bodies it connects. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L981 _public prototype_ `bool SetControlsDisableCollision( const TArray<FName>& Names, const bool bDisableCollision, const bool bApplyToControlsWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — @param Names The names of the controls or sets of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param bDisableCollision If set then the control will disable collision between the bodies it connects. @param bApplyToControlsWithName If true, then controls with the name will be modified @param bApplyToSetsWithName If true, then controls in sets with the name will be modified
- L989 _public prototype_ `bool SetControlsInSetDisableCollision(const FName Set, const bool bDisableCollision);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — @param Set The set of controls to update. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. @param bDisableCollision If set then the control will disable collision between the bodies it connects.
- L999 _public prototype_ `bool SetControlsInSetDriveLimitViolationResponse(const FName Set, const EAngularDriveLimitViolationResponse Response);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the angular drive limit violation response on the live physics asset constraint for each control in the set. This controls how the drive target rotation is adjusted when it would violate the joint's angular limits, preventing the drive and the limit constraint from competing. Only has an effect when the control is using a skeletal mesh with a physics asset constraint. @param Set      The set of controls to update. @param Response The response to apply when the drive target violates a joint limit.
- L1005 _public prototype_ `bool GetControlData(const FName Name, FPhysicsControlData& ControlData) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — @param Name     The name of the control to access. @param Control  The control data that will be filled in if found @return         Returns true if the control was found, false if not
- L1011 _public prototype_ `bool GetControlMultiplier(const FName Name, FPhysicsControlMultiplier& ControlMultiplier) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — @param Name     The name of the control to access. @param Control  The control multipliers that will be filled in if found @return         Returns true if the control was found, false if not
- L1017 _public prototype_ `bool GetControlTarget(const FName Name, FPhysicsControlTarget& ControlTarget) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — @param Name     The name of the control to access. @param Control  The control target, if found @return         Returns true if the control was found, false if not
- L1022 _public prototype_ `bool GetControlEnabled(const FName Name) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — @param Name        The name of the control to access. @return            Returns true if the control is enabled
- L1032 _public prototype_ `FName CreateBodyModifier( UPrimitiveComponent* Component, const FName BoneName, const FName Set, const FPhysicsControlModifierData BodyModifierData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a new body modifier for mesh components @param Component The Mesh Component used as a target for the modifier @param BoneName The bone name, if a skeletal mesh is used @param Set Which set to include the body modifier in (optional). Note that it automatically gets added to the set "All" @param BodyModifierData The initial properties of the modifier
- L1047 _public prototype_ `bool CreateNamedBodyModifier( const FName Name, UPrimitiveComponent* Component, const FName BoneName, const FName Set, const FPhysicsControlModifierData BodyModifierData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Creates a new body modifier for mesh components @param The name of the body modifier that will be created. Creation will fail if this name is already in use. @param Component The Mesh Component used as a target for the modifier @param BoneName The bone name, if a skeletal mesh is used @param Set Which set to include the body modifier in (optional). Note that it automatically gets added to the set "All" @param BodyModifierData The initial properties of the modifier
- L1063 _public prototype_ `TArray<FName> CreateBodyModifiersFromSkeletalMeshBelow( USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName, const bool bIncludeSelf, const FName Set, const FPhysicsControlModifierData BodyModifierData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates new body modifiers for skeletal mesh components @param SkeletalMeshComponent The skeletal mesh which will have body modifiers @param BoneName The bone name below which modifiers should be created @param bIncludeSelf Whether or not to include BoneName when creating modifiers @param Set Which set to include the body modifier in (optional). Note that it automatically gets added to the set "All" @param BodyModifierData The initial properties of the modifier
- L1079 _public prototype_ `TMap<FName, FPhysicsControlNames> CreateBodyModifiersFromLimbBones( FPhysicsControlNames& AllBodyModifiers, const TMap<FName, FPhysicsControlLimbBones>& LimbBones, const FPhysicsControlModifierData BodyModifierData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Creates a collection of controls controlling a skeletal mesh, grouped together in limbs @param AllControls A single container for all the controls that have been created @param LimbBones A map relating the limbs and the bones that they contain. Typically create this using GetLimbBonesFromSkeletalMesh @param BodyModifierData The initial properties of the modifier @return A map containing the modifiers for each limb
- L1092 _public prototype_ `bool DestroyBodyModifier( const FName Name, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Destroys a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set of body modifiers to destroy. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified @return Returns true if the body modifier or set can found/destroyed
- L1104 _public prototype_ `bool DestroyBodyModifiers( const TArray<FName>& Names, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Destroys body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the body modifiers or sets of body modifiers to destroy. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified @return Returns true if all the body modifiers can be found/destroyed
- L1113 _public prototype_ `bool DestroyBodyModifiersInSet(const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Destroys body modifiers @param Set The set of body modifiers to destroy. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @return Returns true if the set and all its modifiers can be found/destroyed
- L1123 _public prototype_ `bool SetBodyModifierData( const FName Name, const FPhysicsControlModifierData ModifierData, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing Body Modifier Data in a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the modifier or set to update. @param ModifierData The new data @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1136 _public prototype_ `bool SetBodyModifierDatas( const TArray<FName>& Names, const FPhysicsControlModifierData ModifierData, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing body modifier data in body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ModifierData The new data @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1146 _public prototype_ `bool SetBodyModifierDatasInSet(const FName Set, const FPhysicsControlModifierData ModifierData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing Body Modifier Data @param Set The set of modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param ModifierData The new data
- L1155 _public prototype_ `bool SetBodyModifierSparseData( const FName Name, const FPhysicsControlModifierSparseData ModifierData, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Modifies an existing Body Modifier Data in a body modifier or body modifiers in a set @param Name The name of the modifier or set to update. @param ModifierData The new data @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1168 _public prototype_ `bool SetBodyModifierSparseDatas( const TArray<FName>& Names, const FPhysicsControlModifierSparseData ModifierData, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing Body Modifier Data in body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param ModifierData The new data @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1178 _public prototype_ `bool SetBodyModifierSparseDatasInSet(const FName Set, const FPhysicsControlModifierSparseData ModifierData);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Modifies existing Body Modifier Data @param Set The set of modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param ModifierData The new data
- L1190 _public prototype_ `bool SetBodyModifierKinematicTarget( const FName Name, const FVector KinematicTargetPosition, const FRotator KinematicTargetOrienation, const bool bMakeKinematic);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets the kinematic target transform for a body modifier. @param Name The name of the body modifier or set to update. @param KinematicTargetPosition The position to use as the kinematic target of the associated body, if it is kinematic @param KinematicTargetOrientation The orientation to use as the kinematic target of the associated body, if it is kinematic @param bMakeKinematic If set then the body will be made kinematic. If not set, then it won't be changed. @return true if the body modifier was found, false if not
- L1203 _public prototype_ `bool SetBodyModifierMovementType( const FName Name, const EPhysicsMovementType MovementType = EPhysicsMovementType::Simulated, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets the movement type for a body modifier or body modifiers in a set @param Name The name of the body modifier or set to update. @param MovementType Whether to enable/disable simulation on the body @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1215 _public prototype_ `bool SetBodyModifiersMovementType( const TArray<FName>& Names, const EPhysicsMovementType MovementType = EPhysicsMovementType::Simulated, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the movement type for body modifiers or body modifiers in sets @param Names The names of the body modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified @param MovementType Whether to enable/disable simulation on the bodies
- L1225 _public prototype_ `bool SetBodyModifiersInSetMovementType( const FName Set, const EPhysicsMovementType MovementType = EPhysicsMovementType::Simulated);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the movement type for body modifiers @param Set The set of body modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param MovementType Whether to enable/disable simulation on the bodies
- L1237 _public prototype_ `bool SetBodyModifierCollisionType( const FName Name, const ECollisionEnabled::Type CollisionType = ECollisionEnabled::QueryAndPhysics, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets the collision type for a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set to update. @param CollisionType Collision type to set on the body @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1250 _public prototype_ `bool SetBodyModifiersCollisionType( const TArray<FName>& Names, const ECollisionEnabled::Type CollisionType = ECollisionEnabled::QueryAndPhysics, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the collision type for body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the body modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param CollisionType Collision type to set on the bodies @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1260 _public prototype_ `bool SetBodyModifiersInSetCollisionType( const FName Set, const ECollisionEnabled::Type CollisionType = ECollisionEnabled::QueryAndPhysics);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the collision type for body modifiers @param Set The set of body modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param CollisionType Collision type to set on the bodies
- L1272 _public prototype_ `bool SetBodyModifierGravityMultiplier( const FName Name, const float GravityMultiplier = 1.0f, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets the gravity multiplier for a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set to update. @param GravityMultiplier The amount of gravity to apply when simulating @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1285 _public prototype_ `bool SetBodyModifiersGravityMultiplier( const TArray<FName>& Names, const float GravityMultiplier = 1.0f, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the gravity multiplier for body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the body modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param GravityMultiplier The amount of gravity to apply when simulating @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1295 _public prototype_ `bool SetBodyModifiersInSetGravityMultiplier( const FName Set, const float GravityMultiplier = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the gravity multiplier for body modifiers @param Set The set of body modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param GravityMultiplier The amount of gravity to apply when simulating
- L1308 _public prototype_ `bool SetBodyModifierPhysicsBlendWeight( const FName Name, const float PhysicsBlendWeight = 1.0f, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets the physics blend weight for a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set to update. @param PhysicsBlendWeight The blend weight between the body transform coming from animation and that coming from simulation. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1322 _public prototype_ `bool SetBodyModifiersPhysicsBlendWeight( const TArray<FName>& Names, const float PhysicsBlendWeight = 1.0f, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the physics blend weight for body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the body modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param PhysicsBlendWeight The blend weight between the body transform coming from animation and that coming from simulation. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1333 _public prototype_ `bool SetBodyModifiersInSetPhysicsBlendWeight( const FName Set, const float PhysicsBlendWeight = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets the physics blend weight for body modifiers @param Set The set of body modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param PhysicsBlendWeight The blend weight between the body transform coming from animation and that coming from simulation.
- L1345 _public prototype_ `bool SetBodyModifierKinematicTargetSpace( const FName Name, const EPhysicsControlKinematicTargetSpace KinematicTargetSpace, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets what space kinematic targets should be applied in for a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set to update. @param KinematicTargetSpace The space in which the kinematic target should be applied. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1358 _public prototype_ `bool SetBodyModifiersKinematicTargetSpace( const TArray<FName>& Names, const EPhysicsControlKinematicTargetSpace KinematicTargetSpace, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets what space kinematic targets should be applied in for body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the body modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param KinematicTargetSpace The space in which the kinematic target should be applied. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1368 _public prototype_ `bool SetBodyModifiersInSetKinematicTargetSpace( const FName Set, const EPhysicsControlKinematicTargetSpace KinematicTargetSpace);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets what space kinematic targets should be applied in @param Set The set of body modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param KinematicTargetSpace The space in which the kinematic target should be applied.
- L1384 _public prototype_ `bool SetBodyModifierUpdateKinematicFromSimulation( const FName Name, const bool bUpdateKinematicFromSimulation, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Sets whether a body modifier should update kinematics from the simulation results, for a body modifier or body modifiers in a set Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set to update. @param bUpdateKinematicFromSimulation Whether the body should be updated from the simulation when it is kinematic, or whether it should track the kinematic target directly. This will be most likely useful when using async physics, in order to make kinematic parts behave the same as dynamic ones. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1401 _public prototype_ `bool SetBodyModifiersUpdateKinematicFromSimulation( const TArray<FName>& Names, const bool bUpdateKinematicFromSimulation, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets whether body modifiers should update kinematics from the simulation results for body modifiers or body modifiers in sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Names The names of the body modifiers or sets to update. Note that if you have these in a FPhysicsControlNameArray then it can be split. @param bUpdateKinematicFromSimulation Whether the body should be updated from the simulation when it is kinematic, or whether it should track the kinematic target directly. This will be most likely useful when using async physics, in order to make kinematic parts behave the same as dynamic ones. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1414 _public prototype_ `bool SetBodyModifiersInSetUpdateKinematicFromSimulation( const FName Set, const bool bUpdateKinematicFromSimulation);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Sets whether body modifiers should update kinematics from the simulation results @param Set The set of body modifiers to update. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param bUpdateKinematicFromSimulation Whether the body should be updated from the simulation when it is kinematic, or whether it should track the kinematic target directly. This will be most likely useful when using async physics, in order to make kinematic parts behave the same as dynamic ones.
- L1432 _public prototype_ `bool CreateControlsAndBodyModifiersFromLimbBones( FPhysicsControlNames& AllWorldSpaceControls, TMap<FName, FPhysicsControlNames>& LimbWorldSpaceControls, FPhysicsControlNames& AllParentSpaceControls, TMap<FName, FPhysicsControlNames>& LimbParentSpaceControls, FPhysicsControlNames& AllBodyModifiers, TMap<FName, FPhysicsControlNames>& LimbBodyModifiers, USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FPhysicsControlLimbSetupData>& LimbSetupData, const FPhysicsControlData WorldSpaceControlData, const FPhysicsControlData ParentSpaceControlData, const FPhysicsControlModifierData BodyModifierData, UPrimitiveComponent* WorldComponent = nullptr, FName WorldBoneName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Creates a collections of controls and body modifiers for a character, based on the description passed in. This makes: - World-space controls - Parent-space controls - Body modifiers for all the body parts. In addition, they get added to sets, so they can be referenced later. Each control is added to three sets: - "All" - "ControlType - i.e. "WorldSpace" or "ParentSpace", each of which will end up containing all controls of that type - "ControlType_LimbName" - e.g. "WorldSpace_ArmLeft" or "ParentSpace_Head" Each body modifier is added to "All" and a set named after the limb - e.g. "Spine" or "LegRight". It is also possible to specify a mesh component to use for the "world" object - so that the world controls can be made to work in the space of another object (or a bone if that is a skeletal mesh component)
- L1452 _public prototype_ `bool CreateControlsAndBodyModifiersFromPhysicsControlAsset( USkeletalMeshComponent* SkeletalMeshComponent, UPrimitiveComponent* WorldComponent, FName WorldBoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — This uses the control profile asset (that should have already been assigned in our data) to create controls and body modifiers. It is also possible to specify a mesh component to use for the "world" object - so that the world controls can be made to work in the space of another object (or a bone if that is a skeletal mesh component)
- L1470 _public prototype_ `bool InvokeControlProfile( const FName ProfileName, const FName ControlSetMask = TEXT(""), const FName BodyModifierSetMask = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Looks up the profile which should exist in the registered control profile asset, and invokes it. @param ProfileName The name of the control profile to apply @param ControlSetMask The optional name of a control set to use as a mask, so only controls within that set will be modified. Standard control set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. If unset or invalid, no mask will be applied. @param BodyModifierSetMask The optional name of a body modifier set to use as a mask, so only body modifiers within that set will be modified. Standard body modifier sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. If unset or invalid, no mask will be applied. @return true if successful, and false if the profile cannot be found.
- L1481 _public prototype_ `void AddControlToSet(FPhysicsControlNames& NewSet, const FName Control, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Adds a Control to a Set. This will add a new set if necessary. For example, you might make a set of Controls called "ParentSpace_Feet" by calling this twice, passing in the left and right foot ParentSpace controls. @return The new/updated set of controls, in case you want to store it
- L1489 _public prototype_ `void AddControlsToSet(FPhysicsControlNames& NewSet, const TArray<FName>& Controls, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Adds Controls to a Set. This will add a new set if necessary. For example, you might make a set of ParentSpace Arm controls by calling this twice, passing in the left and right arm ParentSpace controls. @return The new/updated set of controls, in case you want to store it
- L1493 _public prototype_ `const TArray<FName>& GetAllControlNames() const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Returns a reference to all the control names that have been created.
- L1499 _public prototype_ `const TArray<FName>& GetControlNamesInSet(const FName Set) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Returns a reference to all the control names that have been created and are in the specified set, which could be a limb, or a subsequently created set. Standard sets will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created.
- L1503 _public prototype_ `const TArray<FName>& GetAllBodyModifierNames() const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Returns a reference to all the body modifier names that have been created.
- L1509 _public prototype_ `const TArray<FName>& GetBodyModifierNamesInSet(const FName Set) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Returns a reference to all the body modifier names that have been created and are in the specified set, which could be a limb, or a subsequently created set. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created.
- L1515 _public prototype_ `void AddBodyModifierToSet(FPhysicsControlNames& NewSet, const FName BodyModifier, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Adds a body modifier to a Set. This will add a new set if necessary. For example, you might make a set of body modifiers called "Feet" by calling this twice, passing in the left and right foot body modifiers.
- L1521 _public prototype_ `void AddBodyModifiersToSet(FPhysicsControlNames& NewSet, const TArray<FName>& BodyModifiers, const FName Set);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Adds body modifiers to a Set. This will add a new set if necessary. For example, you might make a set of Arm body modifiers by calling this twice, passing in the left and right arm body modifiers.
- L1525 _public prototype_ `TArray<FName> GetSetsContainingControl(const FName Control) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Returns the names of all sets containing the control (may be empty - e.g. if it doesn't exist)
- L1529 _public prototype_ `TArray<FName> GetSetsContainingBodyModifier(const FName Control) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Returns the names of all sets containing the body modifier (may be empty - e.g. if it doesn't exist)
- L1537 _public prototype_ `TArray<FTransform> GetCachedBoneTransforms( const USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Gets the transforms of the requested bones that will be used as targets (in world space). Targets for bones that are not found will be set to Identity. Note that these targets will have been calculated and cached at the start of the Physics Control Component, so if using the built in tick, may be too old to be useful. If you manually update the component then you can access these target transforms prior to applying your own targets.
- L1547 _public prototype_ `TArray<FVector> GetCachedBonePositions( const USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Gets the positions of the requested bones that will be used as targets (in world space). Targets for bones that are not found will be set to zero. Note that these targets will have been calculated and cached at the start of the Physics Control Component, so if using the built in tick, may be too old to be useful. If you manually update the component then you can access these target transforms prior to applying your own targets.
- L1557 _public prototype_ `TArray<FRotator> GetCachedBoneOrientations( const USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FName>& BoneNames);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Gets the orientations of the requested bones that will be used as targets (in world space). Targets for bones that are not found will be set to identity. Note that these targets will have been calculated and cached at the start of the Physics Control Component, so if using the built in tick, may be too old to be useful. If you manually update the component then you can access these target transforms prior to applying your own targets.
- L1567 _public prototype_ `FTransform GetCachedBoneTransform( const USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Gets the transforms of the requested bone that will be used as a target (in world space). Targets for bones that are not found will be set to Identity. Note that these targets will have been calculated and cached at the start of the Physics Control Component, so if using the built in tick, may be too old to be useful. If you manually update the component then you can access these target transforms prior to applying your own targets.
- L1577 _public prototype_ `FVector GetCachedBonePosition( const USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Gets the position of the requested bone that will be used as a target (in world space). Targets for bones that are not found will be set to zero. Note that these targets will have been calculated and cached at the start of the Physics Control Component, so if using the built in tick, may be too old to be useful. If you manually update the component then you can access these target transforms prior to applying your own targets.
- L1587 _public prototype_ `FRotator GetCachedBoneOrientation( const USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Gets the orientation of the requested bone that will be used as a target (in world space). Targets for bones that are not found will be set to Identity. Note that these targets will have been calculated and cached at the start of the Physics Control Component, so if using the built in tick, may be too old to be useful. If you manually update the component then you can access these target transforms prior to applying your own targets.
- L1598 _public prototype_ `bool SetCachedBoneData( const USkeletalMeshComponent* SkeletalMeshComponent, const FName BoneName, const FTransform& TM);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — This allows the caller to override the target that will have been calculated and cached at the start of the Physics Control Component update. This is unlikely to be useful when using the built in tick, but if you are manually updating the component then you may wish to call this after UpdateTargetCaches but before UpdateControls. @return true if successful, and false if no cached target can be found for the bone.
- L1606 _public prototype_ `void SetCachedBoneVelocitiesToZero();` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — This sets cached bone velocities to zero, by forgetting any previously used transform. This may be useful if the pose is changed suddenly and you don't want this change to show up in the simulated velocities.
- L1618 _public prototype_ `void ResetBodyModifierToCachedBoneTransform( const FName Name, const EResetToCachedTargetBehavior Behavior = EResetToCachedTargetBehavior::ResetImmediately, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — This flags the body associated with the modifier, or modifiers in a set, to set (using teleport) its position and velocity to the cached animation target. This will only affect skeletal mesh component bodies. Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param Name The name of the body modifier or set of body modifiers to use to identify the body/bodies to reset. @param Behavior When the reset should happen. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1627 _public prototype_ `void ResetBodyModifiersToCachedBoneTransforms( const TArray<FName>& Names, const EResetToCachedTargetBehavior Behavior = EResetToCachedTargetBehavior::ResetImmediately, const bool bApplyToModifiersWithName = true, const bool bApplyToSetsWithName = true);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Calls ResetBodyModifierToCachedTarget for each of the body modifiers or body modifiers in the sets Standard sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. @param bApplyToModifiersWithName If true, then body modifiers with the name will be modified @param bApplyToSetsWithName If true, then body modifiers in sets with the name will be modified
- L1633 _public prototype_ `void ResetBodyModifiersInSetToCachedBoneTransforms( const FName SetName, const EResetToCachedTargetBehavior Behavior = EResetToCachedTargetBehavior::ResetImmediately);` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Calls ResetBodyModifierToCachedTarget for each of the body modifiers in the set
- L1639 _public prototype_ `bool GetControlExists(const FName Name) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Indicates if a control with the name exists (doesn't produce a warning if it doesn't)
- L1643 _public prototype_ `bool GetBodyModifierExists(const FName Name) const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl, Meta = (ReturnDisplayName = "Success"))` — Indicates if a body modifier with the name exists (doesn't produce a warning if it doesn't)
- L1647 _public prototype_ `void LogControls() const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Logs all controls and control sets to console and log file
- L1651 _public prototype_ `void LogBodyModifiers() const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Logs all body modifiers and body modifier sets to console and log file
- L1655 _public prototype_ `void LogControlsAndBodyModifiers() const;` — `UFUNCTION(BlueprintCallable, Category = PhysicsControl)` — Logs all controls and body modifiers and their sets to console and log file
- L1663 _public member_ `TSoftObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControlAsset)` — Optional PhysicsControlAsset to use. If this is set, then controls can be instantiated from the asset. Individual profiles can subsequently be "invoked" referencing the named profiles in the asset.
- L1669 _public member_ `float TeleportDistanceThreshold = 300.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport)` — If the component moves by more than this distance then it is treated as a teleport, which prevents velocities being used for a frame. It is also used as the threshold for teleporting when moving kinematic objects. Zero or negative disables.
- L1675 _public member_ `float TeleportRotationThreshold = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport)` — If the component rotates by more than this angle (in degrees) then it is treated as a teleport, which prevents velocities being used for a frame. It is also used as the threshold for teleporting when moving kinematic objects. Zero or negative disables.
- L1679 _public member_ `bool bShowDebugVisualization = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Visualize the controls when this component is selected
- L1683 _public member_ `float VisualizationSizeScale = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Size of the gizmos etc used during visualization
- L1687 _public member_ `bool bShowDebugControlList = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Display all the controls and their basic properties when this component is selected
- L1691 _public member_ `FString DebugControlDetailFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Display detailed info for controls containing this string (if non-empty) when this component is selected
- L1695 _public member_ `bool bShowDebugBodyModifierList = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Display all the body modifiers and their basic properties when this component is selected
- L1699 _public member_ `FString DebugBodyModifierDetailFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Display detailed info for body modifiers containing this string (if non-empty) when this component is selected
- L1704 _public member_ `float VelocityPredictionTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — The time used when "predicting" the target position/orientation. Zero will disable the visualization of this.
- L1710 _public member_ `bool bWarnAboutInvalidNames = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)` — Warn if an an invalid control or body modifier name is used. This can happen quite easily since they're only referenced through names, which are likely auto-generated. However, it may happen for valid reasons, in which case you'll want to disable this.
- L1718 _public member_ `int32 MaxNumControlsOrModifiersPerName = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Upper limit on the number of controls or modifiers that will be created using the same name (which will get a numerical postfix). When this limit is reached a warning will be issued  and the control or modifier won't be created. This is to avoid problems if controls or modifiers are being created dynamically, and can generally be a "moderately large" number, depending on how many controls or modifiers you expect to create.
- L1723 _public member_ `bool bAttemptToRecreateDisabledControls = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — If set then controls that have been disabled due to the bodies being set to NoCollision (for example) will be reinitialized, if possible, when those bodies are returned to the simulation.
- L1727 _public prototype_ `virtual void OnRegister() override;`
- L1728 _public prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L1729 _public prototype_ `virtual void OnCreatePhysicsState() override;`
- L1730 _public prototype_ `virtual void OnDestroyPhysicsState() override;`
- L1735 _public prototype_ `virtual void DebugDraw(FPrimitiveDrawInterface* PDI) const;` — Used by the component visualizer
- L1736 _public prototype_ `virtual void DebugDrawControl(FPrimitiveDrawInterface* PDI, const FPhysicsControlRecord& Record, const FName ControlName) const;`
- L1742 _protected prototype_ `virtual void InitializeComponent() override;`
- L1743 _protected prototype_ `virtual void BeginDestroy() override;`
- L1744 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L1748 _protected prototype_ `void DestroyPhysicsState();` — Terminates everything we have made in physics
- L1757 _protected prototype_ `bool GetBoneData( UE::PhysicsControl::FBoneData& OutBoneData, const UE::PhysicsControl::FPhysicsControlPoseData*& OutPoseData, const USkeletalMeshComponent* InSkeletalMeshComponent, const FName InBoneName) const;` — Retrieves the bone data for the specified bone given the skeletal mesh component. @param OutBoneData If successful, this will contain the output bone data. @param OutPoseData If successful, this will contain the pose data structure, in case more info is required @param InSkeletalMeshComponent Required to be a valid pointer to a skeletal mesh component @param InBoneName The name of the bone to retrieve data for @return true if the bone and data were found, false if not (in which case warnings will be logged)
- L1769 _protected prototype_ `bool GetModifiableBoneData( UE::PhysicsControl::FBoneData*& OutBoneData, const USkeletalMeshComponent* InSkeletalMeshComponent, const FName InBoneName);` — Retrieves the bone data for the specified bone given the skeletal mesh component, for modification @param OutBoneData If successful, this will point to the bone data. @param InSkeletalMeshComponent Required to be a valid pointer to a skeletal mesh component @param InBoneName The name of the bone to retrieve data for @return true if the bone and data were found, false if not (in which case warnings will be logged)
- L1775 _protected prototype_ `FPhysicsControl* FindControl(const FName Name);` — Retrieves the control for the name. Returns a null pointer if the name cannot be found
- L1776 _protected prototype_ `const FPhysicsControl* FindControl(const FName Name) const;`
- L1779 _protected prototype_ `FPhysicsControlRecord* FindControlRecord(const FName Name);` — Retrieves the control record for the name. Returns a null pointer if the name cannot be found
- L1780 _protected prototype_ `const FPhysicsControlRecord* FindControlRecord(const FName Name) const;`
- L1783 _protected prototype_ `void UpdateCachedSkeletalBoneData(float DeltaTime);` — Updates the world-space bone positions etc for each skeleton we're tracking
- L1787 _protected prototype_ `void ResetControls(bool bKeepControlRecords);` — Terminates the underlying physical constraints, resets our internal stored state for each control, and optionally deletes all record of the controls.
- L1790 _protected prototype_ `void AddSkeletalMeshReferenceForCaching(USkeletalMeshComponent* SkeletalMeshComponent);` — Starts caching skeletal mesh poses, and registers for a tick pre-requisite
- L1794 _protected prototype_ `bool RemoveSkeletalMeshReferenceForCaching(USkeletalMeshComponent* SkeletalMeshComponent);` — Stops caching skeletal mesh poses (if this is the last one), and deregisters for a tick pre-requisite. Returns true if this was the last reference, false otherwise.
- L1797 _protected prototype_ `void AddSkeletalMeshReferenceForModifier(USkeletalMeshComponent* SkeletalMeshComponent);` — Records that a modifier is working with the skeletal mesh and stores original data if necessary
- L1801 _protected prototype_ `bool RemoveSkeletalMeshReferenceForModifier(USkeletalMeshComponent* SkeletalMeshComponent);` — Records that a modifier has stopped working with the skeletal mesh and restores original data if necessary. Returns true if this was the last reference, false otherwise.
- L1807 _protected prototype_ `void ApplyControl( FPhysicsControlRecord& Record, FConstraintInstance* PhysicsAssetConstraintInstance, const FConstraintInstance* DefaultConstraintInstance);` — Update the constraint based on the record. PhysicsAssetConstraintInstance and DefaultConstraintInstance are the live and authored constraint instances for this bone pair; both are null when the control does not use skeletal animation or no matching constraint was found in the physics asset.
- L1814 _protected prototype_ `bool ApplyControlStrengths(FPhysicsControlRecord& Record, FConstraintInstance* ConstraintInstance);` — Updates the constraint strengths. Returns true if there is some strength, false otherwise (e.g. to skip setting targets)
- L1818 _protected prototype_ `void CalculateControlTargetData( FTransform& OutTargetTM, FTransform& OutSkeletalTargetTM, FVector& OutTargetVelocity, FVector& OutTargetAngularVelocity, const FPhysicsControlRecord& Record, bool bUsePreviousSkeletalTargetTM) const;` — Calculates the Target TM and velocities that will get passed to the constraint - so this is a target that is defined in the space of the parent body (or in world space, if it doesn't exist).
- L1827 _protected prototype_ `void ApplyBodyModifier(FPhysicsBodyModifierRecord& BodyModifier);` — Updates the body based on the modifier
- L1831 _protected prototype_ `void ApplyKinematicTarget(const FPhysicsBodyModifierRecord& BodyModifier) const;` — This will set the kinematic target for the appropriate body based on the weighted target position and orientation (and whether any were found) for any controls that are related to the body modifier.
- L1835 _protected prototype_ `void ResetToCachedTarget(const FPhysicsBodyModifierRecord& BodyModifier) const;` — Sets the body (simulated or kinematic) to have the position/velocity etc state that has been cached. Has no effect if there is no cached target data.
- L1839 _protected prototype_ `FPhysicsBodyModifierRecord* FindBodyModifierRecord(const FName Name);` — Retrieves the body modifier for the name. Note that if Name is blank then the first modifier will be returned, assuming there is one.
- L1840 _protected prototype_ `const FPhysicsBodyModifierRecord* FindBodyModifierRecord(const FName Name) const;`
- L1851 _protected prototype_ `bool DestroyControl(const FName Name, const EDestroyBehavior DestroyBehavior);` — Destroys the control. It will optionally be removed from the array of records too
- L1854 _protected prototype_ `bool DestroyBodyModifier(const FName Name, const EDestroyBehavior DestroyBehavior);` — Destroys the modifier. It will optionally be removed from the array of records too
- L1867 _protected prototype_ `void ApplyControlAndModifierUpdates( const FPhysicsControlControlAndModifierUpdates& ControlAndModifierUpdates, const FName ControlSetMask = TEXT(""), const FName BodyModifierSetMask = TEXT(""));` — Applies the updates to controls and body modifiers @param ControlAndModifierUpdates The updates to apply @param ControlSetMask The optional name of a control set to use as a mask, so only controls within that set will be modified. Standard control set names will include "All", "WorldSpace", "ParentSpace" and things like "WorldSpace_ArmLeft", depending on how controls have been created. If unset or invalid, no mask will be applied. @param BodyModifierSetMask The optional name of a body modifier set to use as a mask, so only body modifiers within that set will be modified. Standard body modifier sets will include "All" and things like "ArmLeft", depending on how body modifiers have been created. If unset or invalid, no mask will be applied.
- L1876 _protected member_ `TMap<TWeakObjectPtr<USkeletalMeshComponent>, UE::PhysicsControl::FPhysicsControlPoseData> CachedPoseDatas;` — Cached transforms from each skeletal mesh we're working with. Will be updated at the beginning of each tick.
- L1880 _protected member_ `TMap<TWeakObjectPtr<USkeletalMeshComponent>, FModifiedSkeletalMeshData> ModifiedSkeletalMeshDatas;` — Track which skeletons have been affected by a body modifier - some settings get overridden and then need to be restored when the last body modifier is destroyed.
- L1882 _protected member_ `TMap<FName, FPhysicsControlRecord> ControlRecords;`
- L1883 _protected member_ `TMap<FName, FPhysicsBodyModifierRecord> BodyModifierRecords;`
- L1886 _protected member_ `FPhysicsControlNameRecords NameRecords;` — Keep track of the names of everything we have created
- L1890 _protected member_ `FGraphTraversalCounter CurrentUpdateCounter;` — Update counter - incremented every tick, and used to check whether previous targets etc are valid when calculating velocities.

#### enum `UPhysicsControlComponent::EDestroyBehavior`  
`enum class EDestroyBehavior : uint8`  
_L1844-1848_
- desc: When destroying a control or modifier, the record will normally be removed, but it can be retained if you will subsequently update the records
- L1846 _public enumerator_ `KeepRecord`
- L1847 _public enumerator_ `RemoveRecord`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API PHYSICSCONTROL_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlData.h` (Public)


#### enum `EPhysicsMovementType`  
`enum class EPhysicsMovementType : uint8`  
_L19-32_
- reflection: `UENUM(BlueprintType)`
- desc: Used by Body Modifiers to specify how the physical bodies should move.
- L23 _public enumerator_ `Static` — Static means that the object won't be simulated, and it won't be moved according to the kinematic target set in the Body Modifier (though something else might move it)
- L26 _public enumerator_ `Kinematic` — Kinematic means that the object won't be simulated, but will be moved according to the kinematic target set in the Body Modifier.
- L28 _public enumerator_ `Simulated` — Simulated means that the object will be controlled by the physics solver
- L31 _public enumerator_ `Default` — Default means that the movement type shouldn't be changed - for example, it will use the value in the physics asset

#### enum `EPhysicsControlType`  
`enum class EPhysicsControlType : uint8`  
_L54-60_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies the type of control that is created when making controls from a skeleton or a set of limbs. Note that if controls are made individually then other options are available - i.e. in a character, any body part can be controlled relative to any other part, or indeed any other object.
- L57 _public enumerator_ `WorldSpace` — Control is done in world space, so each object/part is driven independently
- L59 _public enumerator_ `ParentSpace` — Control is done in the space of the parent of each object

#### struct `FPhysicsControlSetUpdate`  
`struct FPhysicsControlSetUpdate`  
_L76-88_
- reflection: `USTRUCT(BlueprintType)`
- desc: Update an existing set, or add to it
- L80 _public prototype_ `bool operator==(const FPhysicsControlSetUpdate& other) const = default;`
- L83 _public member_ `FName SetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L87 _public member_ `TArray<FName> Names;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The names of either controls or body modifiers (depending on context), or sets of controls/body modifiers

#### struct `FPhysicsControlSetUpdates`  
`struct FPhysicsControlSetUpdates`  
_L92-105_
- reflection: `USTRUCT(BlueprintType)`
- desc: Combines updates for control and modifier sets
- L96 _public prototype_ `FPhysicsControlSetUpdates& operator+=(const FPhysicsControlSetUpdates& Other);`
- L98 _public prototype_ `bool operator==(const FPhysicsControlSetUpdates& other) const = default;`
- L101 _public member_ `TArray<FPhysicsControlSetUpdate> ControlSetUpdates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L104 _public member_ `TArray<FPhysicsControlSetUpdate> ModifierSetUpdates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### enum `EPhysicsControlKinematicTargetSpace`  
`enum class EPhysicsControlKinematicTargetSpace : uint8`  
_L109-131_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies what space a kinematic target is defined in.
- L113 _public enumerator_ `World` — Target is in world space. For a control rig, this is the space of the control rig, rather than the "real" world.
- L116 _public enumerator_ `Component` — If a skeleton/bone is being used, the target is in the space of that component. If not then it is in the space of the owning component (e.g. PhysicsControl, or ControlRig etc).
- L120 _public enumerator_ `OffsetInBoneSpace` — If a skeleton/bone is being used, the target is specified relative to the bone that controls the (kinematic) body, with the offset applied in the space of that body. If not, then this is the same as World.
- L124 _public enumerator_ `OffsetInWorldSpace` — If a skeleton/bone is being used, the target is specified relative to the bone that controls the (kinematic) body, with the offset applied in world space. If not, then this is the same as World.
- L128 _public enumerator_ `OffsetInComponentSpace` — If a skeleton/bone is being used, the target is specified relative to the bone that controls the (kinematic) body, with the offset applied in component space. If not, then this is the same as Component.
- L130 _public enumerator_ `IgnoreTarget` — Ignore the specified target, and just track the bone/object

#### struct `FPhysicsControlModifierSparseData`  
`struct FPhysicsControlModifierSparseData`  
_L136-222_
- reflection: `USTRUCT(BlueprintType)`
- desc: Analogous to the ControlData, this indicates how an individual controlled body should move, with flags indicating whether each element should get used.
- L140 _public function_ `FPhysicsControlModifierSparseData( const EPhysicsMovementType InMovementType = EPhysicsMovementType::Simulated, const ECollisionEnabled::Type InCollisionType = ECollisionEnabled::QueryAndPhysics, const float InGravityMultiplier = 1.0f, const float InPhysicsBlendWeight = 1.0f, const EPhysicsControlKinematicTargetSpace InKinematicTargetSpace = EPhysicsControlKinematicTargetSpace::OffsetInBoneSpace, const bool InUpdateKinematicFromSimulation = true, const bool InEnableCCD = false) : MovementType(InMovementType) , CollisionType(InCollisionType) , GravityMultiplier(InGravityMultiplier) , PhysicsBlendWeight(InPhysicsBlendWeight) , KinematicTargetSpace(InKinematicTargetSpace) , bUpdateKinematicFromSimulation(InUpdateKinematicFromSimulation) , bEnableCCD(InEnableCCD)`
- L166 _public prototype_ `bool operator==(const FPhysicsControlModifierSparseData& other) const = default;`
- L170 _public member_ `EPhysicsMovementType MovementType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnableMovementType"))` — How the body should move.
- L175 _public member_ `TEnumAsByte<ECollisionEnabled::Type> CollisionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnableCollisionType"))` — The collision type. Note that PhysicsControlComponent uses the full filtering, but RigidBodyWithControl just treats this as enable/disable collision
- L179 _public member_ `float GravityMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnableGravityMultiplier"))` — How much gravity to use when simulating - typically between 0 and 1
- L185 _public member_ `float PhysicsBlendWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnablePhysicsBlendWeight"))` — When converting back from simulation to animation, how much to use the simulation output versus the original animation input. Note - this is not used in RBWC
- L189 _public member_ `EPhysicsControlKinematicTargetSpace KinematicTargetSpace = EPhysicsControlKinematicTargetSpace::OffsetInBoneSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnableKinematicTargetSpace"))` — The space in which kinematic targets should operate
- L195 _public member_ `uint8 bUpdateKinematicFromSimulation : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnablebUpdateKinematicFromSimulation"))` — If true then the associated actor's transform will be updated from the simulation when it is kinematic. This is most likely useful when using async physics in order to prevent different parts of the skeleton from being torn apart. Note - this is not used in RBWC
- L200 _public member_ `uint8 bEnableCCD : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnablebEnableCCD"))` — Enable/disable CCD. Note that this can be expensive, so disable it when not needed! Requires CCD to be allowed in the solver.
- L203 _public member_ `uint8 bEnableMovementType : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L206 _public member_ `uint8 bEnableCollisionType : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L209 _public member_ `uint8 bEnableGravityMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L212 _public member_ `uint8 bEnablePhysicsBlendWeight : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L215 _public member_ `uint8 bEnableKinematicTargetSpace : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L218 _public member_ `uint8 bEnablebUpdateKinematicFromSimulation : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L221 _public member_ `uint8 bEnablebEnableCCD : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`

#### enum `EPhysicsControlSpace`  
`enum class EPhysicsControlSpace : uint8`  
_L226-236_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies a space for queries, forces etc
- L230 _public enumerator_ `World` — World space. For a control rig, this is the space of the control rig, rather than the "real" world, so is the same as Component.
- L233 _public enumerator_ `Component` — If a skeleton/bone is being used, the target is in the space of that component. If not then it is in the space of the owning component (e.g. PhysicsControl, or ControlRig etc).
- L235 _public enumerator_ `Body` — In the space of the body under consideration

#### struct `FPhysicsControlModifierData`  
`struct FPhysicsControlModifierData`  
_L240-303_
- reflection: `USTRUCT(BlueprintType)`
- desc: Analogous to the ControlData, this indicates how an individual controlled body should move
- L244 _public function_ `FPhysicsControlModifierData( const EPhysicsMovementType InMovementType = EPhysicsMovementType::Simulated, const ECollisionEnabled::Type InCollisionType = ECollisionEnabled::QueryAndPhysics, const float InGravityMultiplier = 1.0f, const float InPhysicsBlendWeight = 1.0f, const EPhysicsControlKinematicTargetSpace InKinematicTargetSpace = EPhysicsControlKinematicTargetSpace::OffsetInBoneSpace, const bool InUpdateKinematicFromSimulation = true, const bool InEnableCCD = false) : MovementType(InMovementType) , CollisionType(InCollisionType) , KinematicTargetSpace(InKinematicTargetSpace) , GravityMultiplier(InGravityMultiplier) , PhysicsBlendWeight(InPhysicsBlendWeight) , bUpdateKinematicFromSimulation(InUpdateKinematicFromSimulation) , bEnableCCD(InEnableCCD)`
- L262 _public prototype_ `bool operator==(const FPhysicsControlModifierData& other) const = default;`
- L266 _public prototype_ `void UpdateFromSparseData(const FPhysicsControlModifierSparseData& SparseData);`
- L270 _public member_ `EPhysicsMovementType MovementType = EPhysicsMovementType::Simulated;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — How the body should move.
- L275 _public member_ `TEnumAsByte<ECollisionEnabled::Type> CollisionType = ECollisionEnabled::QueryAndPhysics;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The collision type. Note that PhysicsControlComponent uses the full filtering, but RigidBodyWithControl just treats this as enable/disable collision
- L281 _public member_ `EPhysicsControlKinematicTargetSpace KinematicTargetSpace = EPhysicsControlKinematicTargetSpace::OffsetInBoneSpace;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Physics)` — The space in which kinematic targets should operate. Note that some target spaces are more expensive than others due to the calculations: IgnoreTarget is the cheapest, OffsetInBoneSpace and OffsetInComponentSpace are cheap, but OffsetInWorldSpace is relatively expensive.
- L285 _public member_ `float GravityMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — How much gravity to use when simulating - typically between 0 and 1
- L291 _public member_ `float PhysicsBlendWeight = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — When converting back from simulation to animation, how much to use the simulation output versus the original animation input. Note - this is not used in RBWC
- L297 _public member_ `bool bUpdateKinematicFromSimulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — If true then the associated actor's transform will be updated from the simulation when it is kinematic. This is most likely useful when using async physics in order to prevent different parts of the skeleton from being torn apart.
- L302 _public member_ `bool bEnableCCD;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Enable/disable CCD. Note that this can be expensive, so disable it when not needed! Requires CCD to be allowed in the solver.

#### struct `FPhysicsBodyModifier`  
`struct FPhysicsBodyModifier`  
_L307-323_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a single/individual body modifier, with the modifier data
- L311 _public function_ `FPhysicsBodyModifier()`
- L313 _public function_ `FPhysicsBodyModifier(FName InBoneName, const FPhysicsControlModifierData& InModifierData) : BoneName(InBoneName), ModifierData(InModifierData)`
- L316 _public prototype_ `bool operator==(const FPhysicsBodyModifier& other) const = default;`
- L319 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L322 _public member_ `FPhysicsControlModifierData ModifierData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### struct `FPhysicsBodyModifierCreationData`  
`struct FPhysicsBodyModifierCreationData`  
_L327-338_
- reflection: `USTRUCT(BlueprintType)`
- desc: Used on creation, to allow requesting the modifier to be in certain sets
- L331 _public prototype_ `bool operator==(const FPhysicsBodyModifierCreationData& other) const = default;`
- L334 _public member_ `FPhysicsBodyModifier Modifier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L337 _public member_ `TArray<FName> Sets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### struct `FPhysicsControlSparseData`  
`struct FPhysicsControlSparseData`  
_L343-524_
- reflection: `USTRUCT(BlueprintType)`
- desc: Strength and damping etc parameters that will affect a control, with flags indicating whether each element should get used.
- L347 _public function_ `FPhysicsControlSparseData() : LinearStrength(0) , LinearDampingRatio(1) , LinearExtraDamping(0) , MaxForce(0) , AngularStrength(0) , AngularDampingRatio(1) , AngularExtraDamping(0) , MaxTorque(0) , LinearTargetVelocityMultiplier(1) , AngularTargetVelocityMultiplier(1) , CustomControlPoint(FVector::ZeroVector) , bEnabled(true) , bUseCustomControlPoint(false) , bUseSkeletalAnimation(true) , bDisableCollision(false) , bOnlyControlChildObject(false) , bUseAccelerationDriveMode(true)`
- L386 _public prototype_ `bool operator==(const FPhysicsControlSparseData& other) const = default;`
- L390 _public member_ `float LinearStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearStrength"))` — The strength used to drive linear motion
- L396 _public member_ `float LinearDampingRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearDampingRatio"))` — The amount of damping associated with the linear strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L401 _public member_ `float LinearExtraDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearExtraDamping"))` — The amount of additional linear damping. This is added to the damping that comes from LinearDampingRatio and can be useful when you want damping even when LinearStrength is zero.
- L405 _public member_ `float MaxForce;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableMaxForce"))` — The maximum force used to drive the linear motion. Zero indicates no limit.
- L409 _public member_ `float AngularStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularStrength"))` — The strength used to drive angular motion
- L415 _public member_ `float AngularDampingRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularDampingRatio"))` — The amount of damping associated with the angular strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L420 _public member_ `float AngularExtraDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularExtraDamping"))` — The amount of additional angular damping. This is added to the damping that comes from AngularDampingRatio and can be useful when you want damping even when AngularStrength is zero.
- L424 _public member_ `float MaxTorque;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableMaxTorque"))` — The maximum torque used to drive the angular motion. Zero indicates no limit.
- L430 _public member_ `float LinearTargetVelocityMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearTargetVelocityMultiplier"))` — Multiplier on the linear velocity, which gets applied to the damping. A value of 1 means the animation target velocity is used, which helps it track the animation. A value of 0 means damping happens in "world space" - so damping acts like drag on the movement.
- L436 _public member_ `float AngularTargetVelocityMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularTargetVelocityMultiplier"))` — Multiplier on the angular velocity, which gets applied to the damping. A value of 1 means the animation target velocity is used, which helps it track the animation. A value of 0 means damping happens in "world space" - so damping acts like drag on the movement.
- L440 _public member_ `FVector CustomControlPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableCustomControlPoint"))` — The position of the control point relative to the child mesh, when using a custom control point.
- L444 _public member_ `uint8 bEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnablebEnabled"))` — Whether this control should be enabled
- L448 _public member_ `uint8 bUseCustomControlPoint : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnablebUseCustomControlPoint"))` — Whether or not to use the custom control point position
- L452 _public member_ `uint8 bUseSkeletalAnimation : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnablebUseSkeletalAnimation"))` — If true then the target will be applied on top of the skeletal animation (if there is any)
- L457 _public member_ `uint8 bDisableCollision : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnablebDisableCollision"))` — Whether or not this control should disable collision between the parent and child bodies (only has an effect if there is a parent body)
- L461 _public member_ `uint8 bOnlyControlChildObject : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnablebOnlyControlChildObject"))` — If true then the control will only affect the child object, not the parent
- L468 _public member_ `uint8 bUseAccelerationDriveMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (editcondition = "bEnablebUseAccelerationDriveMode"))` — When true (the default), strength values are interpreted as accelerations (mass-independent). When false they are interpreted as forces (heavier bodies respond more slowly).
- L475 _public member_ `uint8 bEnableLinearStrength : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L478 _public member_ `uint8 bEnableLinearDampingRatio : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L481 _public member_ `uint8 bEnableLinearExtraDamping : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L484 _public member_ `uint8 bEnableMaxForce : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L487 _public member_ `uint8 bEnableAngularStrength : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L490 _public member_ `uint8 bEnableAngularDampingRatio : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L493 _public member_ `uint8 bEnableAngularExtraDamping : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L496 _public member_ `uint8 bEnableMaxTorque : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L499 _public member_ `uint8 bEnableLinearTargetVelocityMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L502 _public member_ `uint8 bEnableAngularTargetVelocityMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L505 _public member_ `uint8 bEnableCustomControlPoint : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L508 _public member_ `uint8 bEnablebEnabled : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L511 _public member_ `uint8 bEnablebUseCustomControlPoint: 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L514 _public member_ `uint8 bEnablebUseSkeletalAnimation : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L517 _public member_ `uint8 bEnablebDisableCollision : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L520 _public member_ `uint8 bEnablebOnlyControlChildObject : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L523 _public member_ `uint8 bEnablebUseAccelerationDriveMode : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`

#### struct `FPhysicsControlData`  
`struct FPhysicsControlData`  
_L529-645_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains data associated with how physical bodies should be controlled/directed towards their targets. The underlying control is done through damped springs, so the parameters here relate to that.
- L533 _public function_ `FPhysicsControlData() : bEnabled(true) , LinearStrength(0.0f) , LinearDampingRatio(1.0f) , LinearExtraDamping(0.0f) , MaxForce(0.0f) , AngularStrength(0.0f) , AngularDampingRatio(1.0f) , AngularExtraDamping(0.0f) , MaxTorque(0.0f) , LinearTargetVelocityMultiplier(1.0f) , AngularTargetVelocityMultiplier(1.0f) , CustomControlPoint(FVector::ZeroVector) , bUseCustomControlPoint(false) , bUseSkeletalAnimation(true) , bDisableCollision(false) , bOnlyControlChildObject(false) , bUseAccelerationDriveMode(true)`
- L554 _public prototype_ `bool operator==(const FPhysicsControlData& other) const = default;`
- L559 _public prototype_ `void UpdateFromSparseData(const FPhysicsControlSparseData& SparseData);` — Applies the values that have been flagged as enabled from the sparse data
- L563 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether this control should be enabled
- L567 _public member_ `float LinearStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The strength used to drive linear motion
- L573 _public member_ `float LinearDampingRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The amount of damping associated with the linear strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L578 _public member_ `float LinearExtraDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The amount of additional linear damping. This is added to the damping that comes from LinearDampingRatio and can be useful when you want damping even when LinearStrength is zero.
- L582 _public member_ `float MaxForce;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The maximum force used to drive the linear motion. Zero indicates no limit.
- L586 _public member_ `float AngularStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The strength used to drive angular motion
- L592 _public member_ `float AngularDampingRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The amount of damping associated with the angular strength. A value of 1 Results in critically damped motion where the control drives as quickly as possible to the target without overshooting. Values > 1 result in more damped motion, and values below 1 result in faster, but more "wobbly" motion.
- L597 _public member_ `float AngularExtraDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The amount of additional angular damping. This is added to the damping that comes from AngularDampingRatio and can be useful when you want damping even when AngularStrength is zero.
- L601 _public member_ `float MaxTorque;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — The maximum torque used to drive the angular motion. Zero indicates no limit.
- L607 _public member_ `float LinearTargetVelocityMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Multiplier on the linear velocity, which gets applied to the damping. A value of 1 means the animation target velocity is used, which helps it track the animation. A value of 0 means damping happens in "world space" - so damping acts like drag on the movement.
- L613 _public member_ `float AngularTargetVelocityMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Multiplier on the angular velocity, which gets applied to the damping. A value of 1 means the animation target velocity is used, which helps it track the animation. A value of 0 means damping happens in "world space" - so damping acts like drag on the movement.
- L617 _public member_ `FVector CustomControlPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The position of the control point relative to the child mesh, when using a custom control point.
- L621 _public member_ `bool bUseCustomControlPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether or not to use the custom control point position
- L625 _public member_ `bool bUseSkeletalAnimation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — If true then the target will be applied on top of the skeletal animation (if there is any)
- L630 _public member_ `bool bDisableCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether or not this control should disable collision between the parent and child bodies (only has an effect if there is a parent body)
- L634 _public member_ `bool bOnlyControlChildObject;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — If true then the control will only affect the child object, not the parent
- L641 _public member_ `bool bUseAccelerationDriveMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — When true (the default), the strength values are interpreted as accelerations - so the same setting produces a comparable response regardless of body mass. When false, the strength values are interpreted as forces - so heavier bodies respond more slowly to the same setting. Switching this value changes the effective strength dramatically, so retune after toggling.
- L644 _public prototype_ `FVector GetControlPoint(const ImmediatePhysics::FActorHandle* ChildActorHandle) const;` — Returns the control point, which may be custom or automatic (centre of mass)

#### struct `FPhysicsControlSparseMultiplier`  
`struct FPhysicsControlSparseMultiplier`  
_L654-740_
- reflection: `USTRUCT(BlueprintType)`
- desc: These parameters allow modification of the parameters in FPhysicsControlData for two reasons: 1. They allow per-axis settings for the linear components (e.g. so you can drive an object horizontally but still let it fall under gravity) 2. They make it easy to create the controls with "default" strength/damping (e.g. taken from the physics asset) in FPhysicsControlData, and then the strength/damping etc can be scaled every tick (typically between 0 and 1, though that is up to the user).
- L658 _public function_ `FPhysicsControlSparseMultiplier() : LinearStrengthMultiplier(1.0) , LinearDampingRatioMultiplier(1.0) , LinearExtraDampingMultiplier(1.0) , MaxForceMultiplier(1.0) , AngularStrengthMultiplier(1.0) , AngularDampingRatioMultiplier(1.0) , AngularExtraDampingMultiplier(1.0) , MaxTorqueMultiplier(1.0)`
- L679 _public prototype_ `bool operator==(const FPhysicsControlSparseMultiplier& other) const = default;`
- L683 _public member_ `FVector LinearStrengthMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearStrengthMultiplier"))` — Per-direction multiplier on the linear strength.
- L687 _public member_ `FVector LinearDampingRatioMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearDampingRatioMultiplier"))` — Per-direction multiplier on the linear damping ratio.
- L691 _public member_ `FVector LinearExtraDampingMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableLinearExtraDampingMultiplier"))` — Per-direction multiplier on the linear extra damping.
- L695 _public member_ `FVector MaxForceMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableMaxForceMultiplier"))` — Per-direction multiplier on the maximum force that can be applied. Note that zero means zero force.
- L699 _public member_ `float AngularStrengthMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularStrengthMultiplier"))` — Multiplier on the angular strength.
- L703 _public member_ `float AngularDampingRatioMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularDampingRatioMultiplier"))` — Multiplier on the angular damping ratio.
- L707 _public member_ `float AngularExtraDampingMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableAngularExtraDampingMultiplier"))` — Multiplier on the angular extra damping.
- L711 _public member_ `float MaxTorqueMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0", editcondition = "bEnableMaxTorqueMultiplier"))` — Per-direction multiplier on the maximum torque that can be applied. Note that zero means zero torque.
- L718 _public member_ `uint8 bEnableLinearStrengthMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L721 _public member_ `uint8 bEnableLinearDampingRatioMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L724 _public member_ `uint8 bEnableLinearExtraDampingMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L727 _public member_ `uint8 bEnableMaxForceMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L730 _public member_ `uint8 bEnableAngularStrengthMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L733 _public member_ `uint8 bEnableAngularDampingRatioMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L736 _public member_ `uint8 bEnableAngularExtraDampingMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`
- L739 _public member_ `uint8 bEnableMaxTorqueMultiplier : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsControl, meta = (InlineEditConditionToggle))`

#### struct `FPhysicsControlMultiplier`  
`struct FPhysicsControlMultiplier`  
_L749-814_
- reflection: `USTRUCT(BlueprintType)`
- desc: These parameters allow modification of the parameters in FPhysicsControlData for two reasons: 1. They allow per-axis settings for the linear components (e.g. so you can drive an object horizontally but still let it fall under gravity) 2. They make it easy to create the controls with "default" strength/damping (e.g. taken from the physics asset) in FPhysicsControlData, and then the strength/damping etc can be scaled every tick (typically between 0 and 1, though that is up to the user).
- L753 _public function_ `FPhysicsControlMultiplier() : LinearStrengthMultiplier(1.0) , LinearDampingRatioMultiplier(1.0) , LinearExtraDampingMultiplier(1.0) , MaxForceMultiplier(1.0) , AngularStrengthMultiplier(1.0) , AngularDampingRatioMultiplier(1.0) , AngularExtraDampingMultiplier(1.0) , MaxTorqueMultiplier(1.0)`
- L778 _public prototype_ `bool operator==(const FPhysicsControlMultiplier& other) const = default;`
- L781 _public prototype_ `void UpdateFromSparseData(const FPhysicsControlSparseMultiplier& SparseData);` — Applies the values that have been flagged as enabled from the sparse data
- L785 _public member_ `FVector LinearStrengthMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Per-direction multiplier on the linear strength.
- L789 _public member_ `FVector LinearDampingRatioMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Per-direction multiplier on the linear damping ratio.
- L793 _public member_ `FVector LinearExtraDampingMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Per-direction multiplier on the linear extra damping.
- L797 _public member_ `FVector MaxForceMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Per-direction multiplier on the maximum force that can be applied. Note that zero means zero force.
- L801 _public member_ `float AngularStrengthMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Multiplier on the angular strength.
- L805 _public member_ `float AngularDampingRatioMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Multiplier on the angular damping ratio.
- L809 _public member_ `float AngularExtraDampingMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Multiplier on the angular extra damping.
- L813 _public member_ `float MaxTorqueMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl, meta = (ClampMin = "0.0"))` — Per-direction multiplier on the maximum torque that can be applied. Note that zero means zero torque.

#### struct `FPhysicsControlTarget`  
`struct FPhysicsControlTarget`  
_L822-868_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines a target position and orientation, and also the target velocity and angular velocity. In many cases the velocities will be calculated automatically (e.g. when setting the target position, the component will optionally calculate an implied velocity. However, the user can also specify a target velocity directly. Note that the velocity influences the control through the damping parameters in FPhysicsControlData
- L826 _public function_ `FPhysicsControlTarget() : TargetPosition(ForceInitToZero) , TargetVelocity(ForceInitToZero) , TargetOrientation(ForceInitToZero) , TargetAngularVelocity(ForceInitToZero) , bApplyControlPointToTarget(false)`
- L847 _public member_ `FVector TargetPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target position of the child body, relative to the parent body
- L851 _public member_ `FVector TargetVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target velocity of the child body, relative to the parent body
- L855 _public member_ `FRotator TargetOrientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target orientation of the child body, relative to the parent body
- L859 _public member_ `FVector TargetAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target angular velocity (revolutions per second) of the child body, relative to the parent body
- L867 _public member_ `bool bApplyControlPointToTarget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether to use the ControlPoint as an offset for the target transform, as well as the physical body. If true then the target TM is treated as a target transform for the actual object, though the control is still applied through the control point (which is at the center of mass by default). If false then it is treated as a target transform for the control point on the object.

#### struct `FPhysicsControl`  
`struct FPhysicsControl`  
_L873-912_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that determines a "control" - this contains all the information needed to drive (with spring-dampers) a child body relative to a parent body. These bodies will be associated with either a static or skeletal mesh.
- L877 _public function_ `FPhysicsControl()`
- L879 _public function_ `FPhysicsControl( const FName& InParentBoneName, const FName& InChildBoneName, const FPhysicsControlData& InControlData) : ParentBoneName(InParentBoneName) , ChildBoneName(InChildBoneName) , ControlData(InControlData)`
- L889 _public prototype_ `bool operator==(const FPhysicsControl& other) const = default;`
- L892 _public function_ `bool IsEnabled() const` — Indicates if the control is enabled
- L896 _public member_ `FName ParentBoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The name of the skeletal mesh bone or the name of the static mesh body that will be doing the driving.
- L901 _public member_ `FName ChildBoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The name of the skeletal mesh bone or the name of the static mesh body that the control will be driving.
- L906 _public member_ `FPhysicsControlData ControlData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Strength and damping parameters. Can be modified at any time, but will sometimes have been set once during initialization
- L911 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Multiplier for the ControlData. This will typically be modified dynamically, and also expose the ability to set directional strengths

#### struct `FPhysicsControlCreationData`  
`struct FPhysicsControlCreationData`  
_L916-927_
- reflection: `USTRUCT(BlueprintType)`
- desc: Used on creation, to allow requesting the control to be in certain sets
- L920 _public prototype_ `bool operator==(const FPhysicsControlCreationData& other) const = default;`
- L923 _public member_ `FPhysicsControl Control;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L926 _public member_ `TArray<FName> Sets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### struct `FPhysicsControlNamedControlParameters`  
`struct FPhysicsControlNamedControlParameters`  
_L931-948_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data that can be used to parameterize (modify/update) a control
- L935 _public function_ `FPhysicsControlNamedControlParameters()`
- L937 _public function_ `FPhysicsControlNamedControlParameters(FName InName, const FPhysicsControlSparseData& InData) : Name(InName), Data(InData)`
- L940 _public prototype_ `bool operator==(const FPhysicsControlNamedControlParameters& other) const = default;`
- L944 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The name of the control (or set of controls) to update
- L947 _public member_ `FPhysicsControlSparseData Data;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### struct `FPhysicsControlNamedControlMultiplierParameters`  
`struct FPhysicsControlNamedControlMultiplierParameters`  
_L952-969_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data that can be used to parameterize (modify/update) a control multiplier
- L956 _public function_ `FPhysicsControlNamedControlMultiplierParameters()`
- L958 _public function_ `FPhysicsControlNamedControlMultiplierParameters(FName InName, const FPhysicsControlSparseMultiplier& InData) : Name(InName), Data(InData)`
- L961 _public prototype_ `bool operator==(const FPhysicsControlNamedControlMultiplierParameters& other) const = default;`
- L965 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The name of the control (or set of controls) to update
- L968 _public member_ `FPhysicsControlSparseMultiplier Data;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### struct `FPhysicsControlNamedModifierParameters`  
`struct FPhysicsControlNamedModifierParameters`  
_L974-991_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data that can be used to parameterize(modify / update) a modifier
- L978 _public function_ `FPhysicsControlNamedModifierParameters()`
- L980 _public function_ `FPhysicsControlNamedModifierParameters(FName InName, const FPhysicsControlModifierSparseData& InData) : Name(InName), Data(InData)`
- L983 _public prototype_ `bool operator==(const FPhysicsControlNamedModifierParameters& other) const = default;`
- L987 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The name of the modifier (or set of modifiers) to update
- L990 _public member_ `FPhysicsControlModifierSparseData Data;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### struct `FPhysicsControlControlAndModifierParameters`  
`struct FPhysicsControlControlAndModifierParameters`  
_L995-1019_
- reflection: `USTRUCT(BlueprintType)`
- desc: These apply temporary/ephemeral changes to the controls that only persist for one tick.
- L1003 _public member_ `TArray<FPhysicsControlNamedControlParameters> ControlParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Parameters for existing controls. Each name can be the name of a control, or the name of a set of controls. They will only apply for one tick/update. They will be applied in order (so subsequent entries will override earlier ones if they apply to the same control).
- L1009 _public member_ `TArray<FPhysicsControlNamedControlMultiplierParameters> ControlMultiplierParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Multipliers for existing controls. Each name can be the name of a control, or the name of a set of controls. They will only apply for one tick/update. They will be applied in order (so subsequent entries will override earlier ones if they apply to the same control).
- L1014 _public member_ `TArray<FPhysicsControlNamedModifierParameters> ModifierParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Parameters for existing modifiers. Each name can be the name of a modifier, or the name of a set of modifiers. They will only apply for one tick/update.
- L1016 _public function_ `void Add(const FPhysicsControlNamedControlParameters& InParameters)`
- L1017 _public function_ `void Add(const FPhysicsControlNamedControlMultiplierParameters& InParameters)`
- L1018 _public function_ `void Add(const FPhysicsControlNamedModifierParameters& InParameters)`

#### struct `FPhysicsControlControlAndModifierUpdates`  
`struct FPhysicsControlControlAndModifierUpdates`  
_L1024-1041_
- reflection: `USTRUCT(BlueprintType)`
- desc: These apply permanent changes to the controls and modifiers, allowing all the settings to be changed (apart from the actual bodies that are being controlled/affected)
- L1028 _public prototype_ `bool operator==(const FPhysicsControlControlAndModifierUpdates& other) const = default;`
- L1032 _public member_ `TArray<FPhysicsControlNamedControlParameters> ControlUpdates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Modifications to the underlying controls
- L1036 _public member_ `TArray<FPhysicsControlNamedControlMultiplierParameters> ControlMultiplierUpdates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Modifications to the underlying control multipliers
- L1040 _public member_ `TArray<FPhysicsControlNamedModifierParameters> ModifierUpdates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Modifications to the underlying modifiers

#### struct `FPhysicsControlAndBodyModifierCreationDatas`  
`struct FPhysicsControlAndBodyModifierCreationDatas`  
_L1045-1058_
- reflection: `USTRUCT(BlueprintType)`
- desc: Collection of controls and body modifiers, used for creation
- L1049 _public prototype_ `FPhysicsControlAndBodyModifierCreationDatas& operator+=(const FPhysicsControlAndBodyModifierCreationDatas& other);`
- L1051 _public prototype_ `bool operator==(const FPhysicsControlAndBodyModifierCreationDatas& other) const;`
- L1054 _public member_ `TMap<FName, FPhysicsControlCreationData> Controls;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`
- L1057 _public member_ `TMap<FName, FPhysicsBodyModifierCreationData> Modifiers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)`

#### enum `EPhysicsControlForceType`  
`enum class EPhysicsControlForceType : uint8`  
_L1061-1067_
- reflection: `UENUM(BlueprintType)`
- L1063 _public enumerator_ `Force`
- L1064 _public enumerator_ `Acceleration`
- L1065 _public enumerator_ `Impulse`
- L1066 _public enumerator_ `VelocityChange`

#### struct `FPhysicsControlForceAndTorqueData`  
`struct FPhysicsControlForceAndTorqueData`  
_L1073-1097_
- reflection: `USTRUCT(BlueprintType)`
- L1078 _public member_ `EPhysicsControlSpace LocationSpace = EPhysicsControlSpace::Body;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)`
- L1081 _public member_ `EPhysicsControlSpace ForceAndTorqueSpace = EPhysicsControlSpace::World;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)`
- L1084 _public member_ `EPhysicsControlForceType Type = EPhysicsControlForceType::Force;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)`
- L1088 _public member_ `FVector Linear = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)` — The linear force/acceleration/impulse/velocity change
- L1092 _public member_ `FVector Angular = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)` — The angular torque/acceleration/impulse/velocity change
- L1096 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)` — The position at which the linear force will be applied

#### struct `FPhysicsControlNamedForceAndTorqueData`  
`struct FPhysicsControlNamedForceAndTorqueData`  
_L1100-1114_
- reflection: `USTRUCT(BlueprintType)`
- L1104 _public function_ `FPhysicsControlNamedForceAndTorqueData()`
- L1106 _public function_ `FPhysicsControlNamedForceAndTorqueData(const FName InName, const FPhysicsControlForceAndTorqueData& InData) : Name(InName), ForceAndTorqueData(InData)`
- L1110 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)`
- L1113 _public member_ `FPhysicsControlForceAndTorqueData ForceAndTorqueData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PHYSICSCONTROL_API`
- L34 _function_ `inline FName GetPhysicsMovementTypeName(const EPhysicsMovementType MovementType)`
- L62 _function_ `inline FName GetPhysicsControlTypeName(const EPhysicsControlType ControlType)`
- L765 _function_ `friend FArchive& operator<<(FArchive& Ar, FPhysicsControlMultiplier& Data)`
- L835 _function_ `friend FArchive& operator<<(FArchive& Ar, FPhysicsControlTarget& Data)`
- L1069 _prototype_ `EPhysicsControlForceType ConvertForceType(ImmediatePhysics_Shared::EForceType InForceType);`
- L1070 _prototype_ `ImmediatePhysics_Shared::EForceType ConvertForceType(EPhysicsControlForceType InForceType);`
- L1117 _prototype_ `FPhysicsControlData Interpolate( const FPhysicsControlData& A, const FPhysicsControlData& B, const float Weight);` — Functions to interpolate between various control/modifier datas
- L1119 _prototype_ `FPhysicsControlSparseData Interpolate( const FPhysicsControlSparseData& A, const FPhysicsControlSparseData& B, const float Weight);`
- L1122 _prototype_ `FPhysicsControlModifierData Interpolate( const FPhysicsControlModifierData& A, const FPhysicsControlModifierData& B, const float Weight);`
- L1124 _prototype_ `FPhysicsControlModifierSparseData Interpolate( const FPhysicsControlModifierSparseData& A, const FPhysicsControlModifierSparseData& B, const float Weight);`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlHelpers.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace PhysicsControl` (scope `UE`)
- L22 _prototype_ `void ConvertStrengthToSpringParams( FVector& OutSpring, FVector& OutDamping, const FVector& InStrength, const FVector& InDampingRatio, const FVector& InExtraDamping);` (scope `UE::PhysicsControl`) — Converts strength/damping ratio/extra damping into spring stiffness/damping
- L29 _prototype_ `void ConvertConstraintProfileToControlData( FPhysicsControlData& OutControlData, const FConstraintProfileProperties& InProfileProperties);` (scope `UE::PhysicsControl`) — Converts the drive settings from the constraint profile into the control data strength/damping etc. Approximations will be made if (a) the linear drive has different values for the x/y/z axes, or (b) the constraint profile is set to use twist/swing instead of slerp for the angular drive.
- L36 _prototype_ `FBodyInstance* GetBodyInstance(UPrimitiveComponent* Component, const FName BoneName);` (scope `UE::PhysicsControl`) — Attempts to find a BodyInstance from the component. If it is a primitive or static mesh component the single body instance will be returned. If it is a skeletal mesh then if BoneName can be found, the body instance corresponding to that bone will be returned. Otherwise it will return nullptr if the bone can't be found.
- L41 _prototype_ `FName GetPhysicalParentBone(USkeletalMeshComponent* SkeletalComponent, FName BoneName);` (scope `UE::PhysicsControl`) — Attempts to find the parent physical bone given a skeletal mesh and starting bone. This walks up the hierarchy, ignoring non-physical bones, until either a physical bone is found, or it has reached the root without finding a physical bone.
- L44 _function_ `FORCEINLINE FVector CalculateAngularVelocity(const FQuat& PrevQ, const FQuat& CurrentQ, float Dt)` (scope `UE::PhysicsControl`) — Calculates the angular velocity that would go from PrevQ to CurrentQ in Dt. Returns zero if Dt is invalid.
- L51 _function_ `FORCEINLINE FVector CalculateLinearVelocity(const FVector& PrevP, const FVector& CurrentP, float Dt)` (scope `UE::PhysicsControl`) — Calculates the linear velocity that would go from PrevP to CurrentP in Dt. Returns zero if Dt is invalid.
- L58 _function_ `template<typename TOut> void ConvertStrengthToSpringParams( TOut& OutSpring, TOut& OutDamping, double InStrength, double InDampingRatio, double InExtraDamping)` (scope `UE::PhysicsControl`) — Converts strength/damping ratio/extra damping into spring stiffness/damping. Clamps strength to >= 0.
- L73 _function_ `template<typename TOut> void ConvertSpringToStrengthParams( TOut& OutStrength, TOut& OutDampingRatio, TOut& OutExtraDamping, const double InSpring, const double InDamping)` (scope `UE::PhysicsControl`) — Converts spring/damping values into strength/damping ratio/extra damping. This tries to get as much damping into the damping ratio term as possible, without letting it go above 1.

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlLimbData.h` (Public)


#### struct `FPhysicsControlLimbSetupData`  
`struct FPhysicsControlLimbSetupData`  
_L21-58_
- reflection: `USTRUCT(BlueprintType)`
- desc: Setup data that are used to create the representation of a single limb. A limb is an array of contiguous bones (e.g. left arm, or the spine etc). We can define it has the set of bones that are children of a start bone (plus the start bone itself), plus optionally the parent of that start bone (this is useful when defining the spine, since you will want to include the pelvis, but you don't to include all the children of the pelvis since that would include the legs), but excluding any bones that are already part of another limb. This implies limbs should be constructed in order from leaf to root (in practice, that normally means defining the spine after other limbs such as the arms and legs).
- L25 _public function_ `FPhysicsControlLimbSetupData() : bIncludeParentBone(false), bCreateWorldSpaceControls(true) , bCreateParentSpaceControls(true), bCreateBodyModifiers(true)`
- L30 _public prototype_ `bool operator==(const FPhysicsControlLimbSetupData& other) const = default;`
- L34 _public member_ `FName LimbName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The name of the limb that this will be used to create
- L39 _public member_ `FName StartBone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Normally the root-most bone of the limb (e.g. left clavicle when defining the left arm) - so the limb will contain children of this bone (plus this bone itself).
- L45 _public member_ `uint8 bIncludeParentBone : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether or not to include the parent of the start bone. This is intended to be used for limbs like the spine, where you would set StartBone = spine_01 but also expect to include the pelvis (parent of spine_01) in the spine limb.
- L49 _public member_ `uint8 bCreateWorldSpaceControls : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether to create-world space controls for this limb
- L53 _public member_ `uint8 bCreateParentSpaceControls : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether to create parent-space controls for this limb
- L57 _public member_ `uint8 bCreateBodyModifiers : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Whether to create body modifiers for this limb

#### struct `FPhysicsControlLimbBones`  
`struct FPhysicsControlLimbBones`  
_L62-83_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper for the array of bone names, so that the limbs can we can work with a map of arrays of names.
- L66 _public function_ `FPhysicsControlLimbBones() : bFirstBoneIsAdditional(false), bCreateWorldSpaceControls(true) , bCreateParentSpaceControls(true), bCreateBodyModifiers(true)`
- L72 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — The Skeletal mesh that this limb is associated with
- L75 _public member_ `TArray<FName> BoneNames;` — The names of the bones in the limb
- L78 _public member_ `uint8 bFirstBoneIsAdditional : 1;` — Indicates if the first bone in this limb was included due to "IncludeParentBone".
- L80 _public member_ `uint8 bCreateWorldSpaceControls : 1;`
- L81 _public member_ `uint8 bCreateParentSpaceControls : 1;`
- L82 _public member_ `uint8 bCreateBodyModifiers : 1;`

#### struct `FPhysicsControlNames`  
`struct FPhysicsControlNames`  
_L88-95_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper for the array of names, so that the control/modifier sets can we work with a map of arrays of names. Note that in practice, the names will be of either controls or body modifiers.
- L94 _public member_ `TArray<FName> Names;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The names of either controls of body modifiers (depending on context)

#### struct `FPhysicsControlCharacterSetupData`  
`struct FPhysicsControlCharacterSetupData`  
_L98-117_
- reflection: `USTRUCT(BlueprintType)`
- L102 _public prototype_ `FPhysicsControlCharacterSetupData& operator+=(const FPhysicsControlCharacterSetupData& other);`
- L104 _public prototype_ `bool operator==(const FPhysicsControlCharacterSetupData& other) const = default;`
- L107 _public member_ `TArray<FPhysicsControlLimbSetupData> LimbSetupData;` — `UPROPERTY(EditAnywhere, Category = ControlSetup)`
- L110 _public member_ `FPhysicsControlData DefaultWorldSpaceControlData;` — `UPROPERTY(EditAnywhere, Category = ControlSetup)`
- L113 _public member_ `FPhysicsControlData DefaultParentSpaceControlData;` — `UPROPERTY(EditAnywhere, Category = ControlSetup)`
- L116 _public member_ `FPhysicsControlModifierData DefaultBodyModifierData;` — `UPROPERTY(EditAnywhere, Category = ControlSetup)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PHYSICSCONTROL_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsControl, Warning, Warning);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsControl, Log, All);`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlModule.h` (Public)


#### class `FPhysicsControlModule`  
`class FPhysicsControlModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlNameRecords.h` (Public)


#### struct `FPhysicsControlNameRecords`  
`struct FPhysicsControlNameRecords`  
_L13-45_
- desc: All the controls and body modifiers we create get given names, so we can keep a record in a form that will be useful to users. The three general uses are: 1. All controls or modifiers 2. The type of control - the obvious ones are "world space" and "parent space", but users might make others 3. Sets of control/modifiers - the obvious ones are limbs (e.g. a set of world-space controls on the leg) but users might want to make other sets - e.g. "UpperBody"
- L16 _public prototype_ `void AddControl(FName Name, FName SetName, bool bAddToAll = true);` — Adds Name to SetName as well as optionally adding it to the set "All"
- L18 _public prototype_ `void AddControl(FName Name, TConstArrayView<FName> SetNames, bool bAddToAll = true);` — Adds Name to SetNames as well as optionally adding it to the set "All"
- L20 _public prototype_ `void AddControls(TConstArrayView<FName> ControlNames, const FName SetName, bool bAddToAll = true);` — Adds a collection of Names to SetName as well as optionally adding them to the set "All"
- L22 _public prototype_ `void RemoveControl(FName Name);` — Removes Name from all Sets
- L23 _public prototype_ `const TArray<FName>& GetControlNamesInSet(FName SetName) const;`
- L26 _public prototype_ `void AddBodyModifier(FName Name, FName SetName, bool bAddToAll = true);` — Adds Name to SetName as well as optionally adding it to the set "All"
- L28 _public prototype_ `void AddBodyModifier(FName Name, TConstArrayView<FName> SetNames, bool bAddToAll = true);` — Adds Name to SetNames as well as optionally adding it to the set "All"
- L30 _public prototype_ `void AddBodyModifiers(TConstArrayView<FName> BodyModifierNames, const FName SetName, bool bAddToAll = true);` — Adds a collection of Names to SetName as well as optionally adding them to the set "All"
- L32 _public prototype_ `void RemoveBodyModifier(FName Name);` — Removes Name from all Sets
- L33 _public prototype_ `const TArray<FName>& GetBodyModifierNamesInSet(FName SetName) const;`
- L36 _public prototype_ `void Reset();` — Remove all control and modifier sets.
- L40 _public member_ `TMap<FName, TArray<FName>> ControlSets;` — All the control sets we've created, arranged by set name. Note that some controls will not necessarily have been added to a set.
- L44 _public member_ `TMap<FName, TArray<FName>> BodyModifierSets;` — All the body modifiers we've created, arranged by set name. Note that some modifiers will not necessarily have been added to a set.

#### Free symbols / members of external scopes

- L49 _prototype_ `TArray<FName> ExpandName(const FName InName, const TMap<FName, TArray<FName>>& Sets);` — Returns a copy of the supplied list of names in which any names that match keys in the supplied 'Sets' map are replaced with all the names in the array associated with that key.
- L50 _prototype_ `TArray<FName> ExpandNames(const TArray<FName>& InNames, const TMap<FName, TArray<FName>>& Sets);`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlObjectVersion.h` (Public)


#### struct `FPhysicsControlObjectVersion`  
`struct FPhysicsControlObjectVersion`  
_L8-58_
- L54 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L57 _private function_ `FPhysicsControlObjectVersion()`

#### enum `FPhysicsControlObjectVersion::Type`  
`enum Type`  
_L10-51_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded` — Before any version changes were made
- L14 _public enumerator_ `ControlRigIncludeDriveInJoint`
- L15 _public enumerator_ `ControlRigRemoveCurrentDataFromPhysicsComponent`
- L16 _public enumerator_ `ControlRigUseAutomaticSolver`
- L17 _public enumerator_ `ControlRigAutomaticallyAddPhysicsBodyComponents`
- L18 _public enumerator_ `ControlRigControlAddChildBodyComponentKey`
- L19 _public enumerator_ `ControlRigControlAddControlMultiplier`
- L20 _public enumerator_ `ControlRigSeparateOutJointFromBody`
- L21 _public enumerator_ `ControlRigSupportFullConstraintData`
- L22 _public enumerator_ `ControlRigSupportFullDriveConstraintData`
- L23 _public enumerator_ `ControlRigSupportNoCollisionBodies`
- L24 _public enumerator_ `ControlRigSupportBodyDamping`
- L25 _public enumerator_ `ControlRigCollisionHasMaterial`
- L26 _public enumerator_ `ControlRigBodyDynamicsHasDensity`
- L27 _public enumerator_ `ControlRigSolverSettingsIncludesCollisionBoundsExpansion`
- L28 _public enumerator_ `ControlRigDetectTeleportFromDistanceChange`
- L29 _public enumerator_ `ControlRigSpeedThresholdForReset`
- L30 _public enumerator_ `ControlRigResetCooldownFrames`
- L31 _public enumerator_ `ControlRigSimSpaceDragMultipliers`
- L32 _public enumerator_ `ControlRigAccelerationThresholdForReset`
- L33 _public enumerator_ `ControlRigRemoveResetCooldownFrames`
- L34 _public enumerator_ `ControlRigDriveRelativeToAnimation`
- L35 _public enumerator_ `ControlRigDetectExternalVelocityTurbulence`
- L36 _public enumerator_ `ControlRigBodyIncludeInChecksForReset`
- L37 _public enumerator_ `ControlRigWorldCollision`
- L38 _public enumerator_ `ControlRigCentreOfMassNudge`
- L39 _public enumerator_ `ControlRigJointEnabled`
- L40 _public enumerator_ `RemoveSkeletalAnimationVelocityMultiplier`
- L41 _public enumerator_ `RemoveUseSkeletalAnimation`
- L42 _public enumerator_ `ControlRigShapeData`
- L43 _public enumerator_ `EnableCCD`
- L44 _public enumerator_ `ControlRigAllowCCD`
- L45 _public enumerator_ `ControlRigConvexCollision`
- L46 _public enumerator_ `ControlDataDriveForceMode` — bUseAccelerationDriveMode added to FPhysicsControlData / FPhysicsControlSparseData
- L49 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-----
- L50 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API PHYSICSCONTROL_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlOperatorNameGeneration.h` (Public)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace PhysicsControl` (scope `UE`)
- L26 _variable_ `constexpr int32 MaxNumControlsOrModifiersPerName = 16;` (scope `UE::PhysicsControl`)
- L29 _prototype_ `TMap<FName, FPhysicsControlLimbBones> GetLimbBones( const TArray<FPhysicsControlLimbSetupData>& LimbSetupDatas, const FReferenceSkeleton& RefSkeleton, const UPhysicsAsset* PhysicsAsset);` (scope `UE::PhysicsControl`) — Parse the skeleton tree to figure out which bones are associated with which limbs.
- L36 _prototype_ `void CollectOperatorNames( const FPhysicsControlCharacterSetupData& CharacterSetupData, const FPhysicsControlAndBodyModifierCreationDatas& AdditionalControlsAndBodyModifiers, const TMap<FName, FPhysicsControlLimbBones> AllLimbBones, const FReferenceSkeleton& RefSkeleton, const UPhysicsAsset* PhysicsAsset, TSet<FName>& BodyModifierNames, TSet<FName>& ControlNames, FPhysicsControlNameRecords& NameRecords);` (scope `UE::PhysicsControl`) — Populates the supplied body modifier names, control names and name records structures with the names and sets that would be created for the supplied limb bones, skeleton and physics asset.
- L47 _prototype_ `void CreateOperatorsForNode( FAnimNode_RigidBodyWithControl* Node, const FPhysicsControlCharacterSetupData& CharacterSetupData, const FPhysicsControlAndBodyModifierCreationDatas& AdditionalControlsAndBodyModifiers, const TMap<FName, FPhysicsControlLimbBones> AllLimbBones, const FReferenceSkeleton& RefSkeleton, const UPhysicsAsset* PhysicsAsset, FPhysicsControlNameRecords& NameRecords);` (scope `UE::PhysicsControl`) — Creates the body modifiers, controls and sets for the supplied node, limb bones, skeleton and physics asset.
- L57 _prototype_ `void CreateAdditionalSets( const FPhysicsControlSetUpdates& AdditionalSets, const TSet<FName>& BodyModifierNames, const TSet<FName>& ControlNames, FPhysicsControlNameRecords& NameRecords);` (scope `UE::PhysicsControl`) — Adds the specified additional sets to the supplied Name Records structure.
- L64 _prototype_ `void CreateAdditionalSets( const FPhysicsControlSetUpdates& AdditionalSets, const TMap<FName, FRigidBodyModifierRecord>& BodyModifierRecords, const TMap<FName, FRigidBodyControlRecord>& Controls, FPhysicsControlNameRecords& NameRecords);` (scope `UE::PhysicsControl`) — Adds the specified additional sets to the supplied Name Records structure.
- L71 _prototype_ `void CreateAdditionalSets( const FPhysicsControlSetUpdates& AdditionalSets, const TMap<FName, FPhysicsBodyModifierRecord>& BodyModifierRecords, const TMap<FName, FPhysicsControlRecord>& Controls, FPhysicsControlNameRecords& NameRecords);` (scope `UE::PhysicsControl`) — Adds the specified additional sets to the supplied Name Records structure.
- L79 _function_ `inline bool DoesNameExist(const FName Name, const TArray<FName>& ExistingNames)` (scope `UE::PhysicsControl`) — Helper for GetUniqueName
- L87 _function_ `template<typename T> bool DoesNameExist(const FName Name, const TMap<FName, T>& ExistingNames)` (scope `UE::PhysicsControl`) — Helper for GetUniqueName
- L94 _function_ `inline bool DoesNameExist(const FName Name, const TSet<FName>& ExistingNames)` (scope `UE::PhysicsControl`) — Helper for GetUniqueName
- L106 _function_ `template<typename CollectionType> FName GetUniqueName(const FString& OriginalName, const CollectionType& ExistingNames, const int32 MaxNameIndex)` (scope `UE::PhysicsControl`) — Makes a unique version of OriginalName. Note that the convention elsewhere in UE when creating an object, and then a second identical one, is for the first object to have the original name, and then the next has a suffix _2, and so on.
- L140 _function_ `template<typename CollectionType> FName GetUniqueBodyModifierName(const FName BodyName, const CollectionType& ExistingNames, const FString& NamePrefix)` (scope `UE::PhysicsControl`)
- L157 _function_ `template<typename CollectionType> FName GetUniqueBodyModifierName( const UPrimitiveComponent* Component, const FName BoneName, const CollectionType& ExistingNames, const FString& NamePrefix)` (scope `UE::PhysicsControl`)
- L181 _function_ `template<typename CollectionType> FName GetUniqueControlName( const FName ParentName, const FName ChildName, const CollectionType& ExistingNames, const FString& NamePrefix)` (scope `UE::PhysicsControl`)
- L211 _function_ `template<typename CollectionType> FName GetUniqueControlName( const UPrimitiveComponent* ParentComponent, const FName ParentBoneName, const UPrimitiveComponent* ChildComponent, const FName ChildBoneName, const CollectionType& ExistingNames, const FString& NamePrefix)` (scope `UE::PhysicsControl`)

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlPoseData.h` (Public)


#### struct `UE::PhysicsControl::FPosQuat`  
`struct FPosQuat`  
_L26-73_
- desc: Simple minimal implementation of a "FTransform without scale"
- L28 _public function_ `FPosQuat(const FVector& Pos, const FQuat& Quat) : Translation(Pos), Rotation(Quat)`
- L29 _public function_ `FPosQuat(const FQuat& Quat, const FVector& Pos) : Translation(Pos), Rotation(Quat)`
- L30 _public function_ `FPosQuat(const FRotator& Rotator, const FVector& Pos) : Translation(Pos), Rotation(Rotator)`
- L31 _public function_ `FPosQuat() : Translation(EForceInit::ForceInitToZero), Rotation(EForceInit::ForceInit)`
- L32 _public function_ `FPosQuat(const FTransform& TM) : Translation(TM.GetTranslation()), Rotation(TM.GetRotation())`
- L33 _public function_ `FPosQuat(ENoInit)`
- L35 _public function_ `FVector GetTranslation() const`
- L36 _public function_ `FQuat GetRotation() const`
- L38 _public function_ `void SetTranslation(const FVector& T)`
- L39 _public function_ `void SetRotation(const FQuat& Q)`
- L41 _public function_ `FTransform ToTransform() const`
- L48 _public function_ `FPosQuat operator*(const FPosQuat& Other) const` — Note that multiplication operates in the same sense as FQuat - i.e. in reverse compared to FTransform WorldChildTM = WorldParentTM * ChildRelParentTM
- L55 _public function_ `FVector operator*(const FVector& Position) const`
- L60 _public function_ `FPosQuat Inverse() const`
- L66 _public function_ `bool ContainsNaN() const`
- L71 _public member_ `FVector Translation;`
- L72 _public member_ `FQuat Rotation;`

#### struct `UE::PhysicsControl::FBoneData`  
`struct FBoneData`  
_L76-87_
- L78 _public function_ `FBoneData()`
- L79 _public function_ `FBoneData(const FPosQuat& InCurrentTM, const FPosQuat& InPreviousTM) : CurrentTM(InCurrentTM), PreviousTM(InPreviousTM)`
- L82 _public prototype_ `FVector CalculateLinearVelocity(float Dt) const;`
- L83 _public prototype_ `FVector CalculateAngularVelocity(float Dt) const;`
- L85 _public member_ `FPosQuat CurrentTM;`
- L86 _public member_ `FPosQuat PreviousTM;`

#### struct `UE::PhysicsControl::FPhysicsControlPoseData`  
`struct FPhysicsControlPoseData`  
_L91-127_
- desc: Caches the pose for PhysicsControlComponent
- L94 _public function_ `FPhysicsControlPoseData() : ReferenceCount(0), bHasJustTeleported(true), DeltaTime(0)`
- L97 _public prototype_ `void Update( USkeletalMeshComponent* SkeletalMesh, const float Dt, const float TeleportDistanceThreshold, const float TeleportRotationThreshold);`
- L102 _public function_ `void Reset()`
- L104 _public function_ `const FBoneData& GetBoneData(int32 Index) const`
- L105 _public function_ `FPosQuat GetCurrentTM(int32 Index) const`
- L106 _public function_ `FPosQuat GetPreviousTM(int32 Index) const`
- L108 _public function_ `bool IsValidIndex(const int32 Index) const`
- L109 _public function_ `bool IsEmpty() const`
- L112 _public member_ `TArray<FBoneData> BoneDatas;` — The cached skeletal data, updated at the start of each tick
- L116 _public member_ `int32 ReferenceCount;` — Track when skeletal meshes are going to be used so this entry can be removed, and also so we can add a tick dependency.
- L119 _public member_ `FTransform ComponentTM;` — The component transform. This is only stored so we can detect teleports.
- L123 _public member_ `bool bHasJustTeleported;` — Whether the character has just teleported, in which case velocities should not be calculated based on deltas.
- L126 _public member_ `float DeltaTime;` — The DeltaTime used for the previous update (may be zero)

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PhysicsControl` (scope `UE`)
- L14 _prototype_ `bool DetectTeleport( const FVector& OldPosition, const FQuat& OldOrientation, const FVector& NewPosition, const FQuat& NewOrientation, float DistanceThreshold, float RotationThreshold);` (scope `UE::PhysicsControl`) — @return true if the difference between the old and new TMs exceeds the teleport translation/rotation thresholds
- L21 _prototype_ `bool DetectTeleport(const FTransform& OldTM, const FTransform& NewTM, float DistanceThreshold, float RotationThreshold);` (scope `UE::PhysicsControl`) — @return true if the difference between the old and new TMs exceeds the teleport translation/rotation thresholds

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/PhysicsControlRecord.h` (Public)


#### struct `FPhysicsControlRecord`  
`struct FPhysicsControlRecord`  
_L16-93_
- desc: There will be a PhysicsControlRecord created at runtime for every Control that has been created
- L18 _public function_ `FPhysicsControlRecord( const FPhysicsControl& InControl, const FPhysicsControlTarget& InControlTarget, UPrimitiveComponent* InParentComponent, UPrimitiveComponent* InChildComponent) : PhysicsControl(InControl) , ControlTarget(InControlTarget) , ParentComponent(InParentComponent) , ChildComponent(InChildComponent)`
- L30 _public prototype_ `void ResetConstraint();` — Removes any constraint and resets the state
- L33 _public prototype_ `FVector GetControlPoint() const;` — Returns the control point, which may be custom or automatic (centre of mass)
- L37 _public prototype_ `bool InitConstraint(UObject* ConstraintDebugOwner, FName ControlName, bool bWarnAboutInvalidNames);` — Creates the constraint if necessary and stores it. Then initializes the constraint with the bodies.
- L40 _public prototype_ `void UpdateConstraintControlPoint();` — Ensures the constraint frame matches the control point in the record.
- L43 _public prototype_ `void ResetControlPoint();` — Sets the control point to the center of mass of the child mesh (or to zero if that fails).
- L48 _public prototype_ `bool RefreshJointConstraintIndex(USkeletalMeshComponent* ChildSKM, UPhysicsAsset* PhysAsset);` — Ensures JointConstraintIndex is valid for PhysAsset. If the physics asset has changed since InitConstraint ran, re-resolves the index . Returns true if JointConstraintIndex is valid (not INDEX_NONE). ChildSKM must be non-null.
- L51 _public member_ `FPhysicsControl PhysicsControl;` — The configuration data
- L56 _public member_ `FPhysicsControlTarget ControlTarget;` — The position/orientation etc targets for the controls. These are procedural/explicit control targets - skeletal meshes have the option to use skeletal animation as well, in which case these targets are expressed as relative to that animation.
- L62 _public member_ `UE::PhysicsControl::FPosQuat PreviousSkeletalTargetTM;` — The previous skeletal control target. This will have been set at the end of a previous update (but only if the control was enabled etc), so to check if it is valid, check the update counter. Note that explicit control targets (which contain their own velocity) will be added onto this.
- L66 _public member_ `FGraphTraversalCounter ExpectedUpdateCounter;` — Only use the previous target TM if the current counter is equal to this expected counter. The expected update counter will be set when the control/previous target TM has just been updated.
- L69 _public member_ `TWeakObjectPtr<UPrimitiveComponent> ParentComponent;` — The mesh that will be doing the driving. Blank/non-existent means it will happen in world space
- L72 _public member_ `TWeakObjectPtr<UPrimitiveComponent> ChildComponent;` — The mesh that the control will be driving.
- L75 _public member_ `TSharedPtr<FConstraintInstance> ConstraintInstance;` — The drive (motor) constraint that implements the control, created and owned by PhysicsControl.
- L79 _public member_ `TWeakObjectPtr<UPhysicsAsset> JointConstraintPhysAsset;` — Physics asset whose ConstraintSetup was used to resolve JointConstraintIndex. Stored so that a SetPhysicsAsset call is detected each tick and triggers a re-resolve.
- L83 _public member_ `bool bJointLimitsWidened = false;` — True when WidenLimitsForDriveTarget has left at least one axis wider than its authored default. Used to skip RestoreAngularLimitsToDefault on frames where nothing was ever widened.
- L92 _public member_ `int32 JointConstraintIndex = INDEX_NONE;` — Index into UPhysicsAsset::ConstraintSetup for the ragdoll joint constraint connecting ChildBoneName to ParentBoneName. This is a separate constraint from ConstraintInstance above: it belongs to the SKM and defines the joint's angular limits (swing/twist). An index is stored rather than a pointer because RecreatePhysicsState invalidates FConstraintInstance* addresses without changing the physics asset; the index survives that. Resolved once in InitConstraint; each tick the live pointer is obtained via GetConstraintInstanceByIndex. INDEX_NONE when no matching constraint was found.

#### struct `FPhysicsBodyModifierRecord`  
`struct FPhysicsBodyModifierRecord`  
_L96-119_
- desc: There will be a PhysicsBodyModifier created at runtime for every BodyInstance involved in the component
- L98 _public function_ `FPhysicsBodyModifierRecord( TWeakObjectPtr<UPrimitiveComponent> InComponent, const FName& InBoneName, FPhysicsControlModifierData InBodyModifierData) : Component(InComponent) , BodyModifier(InBoneName, InBodyModifierData) , bResetToCachedTarget(false)`
- L108 _public member_ `TWeakObjectPtr<UPrimitiveComponent> Component;` — The mesh that will be modified.
- L111 _public member_ `FPhysicsBodyModifier BodyModifier;` — The core data
- L114 _public member_ `UE::PhysicsControl::FPosQuat KinematicTarget;` — The target transform when kinematic.
- L118 _public member_ `uint8 bResetToCachedTarget:1;` — If true then the body will be set to the transform/velocity stored in any cached target (if that exists), and then this flag will be cleared.

#### struct `FModifiedSkeletalMeshData`  
`struct FModifiedSkeletalMeshData`  
_L123-138_
- desc: Used internally/only at runtime to track when a SkeletalMeshComponent is being controlled through a modifier, and to restore settings when that stops.
- L126 _public function_ `FModifiedSkeletalMeshData() : ReferenceCount(0)`
- L131 _public member_ `uint8 bOriginalUpdateMeshWhenKinematic : 1;` — The original setting for restoration when we're deleted
- L134 _public member_ `EKinematicBonesUpdateToPhysics::Type OriginalKinematicBonesUpdateType;` — The original setting for restoration when we're deleted
- L137 _public member_ `int32 ReferenceCount;` — Track when skeletal meshes are going to be used so this entry can be removed

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/RigidBodyControlData.h` (Public)


#### struct `FRigidBodyControlTarget`  
`struct FRigidBodyControlTarget`  
_L21-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single target for a control, which may be defined as an offset from the (implicit) animation target.
- L25 _public function_ `FRigidBodyControlTarget() : TargetPosition(ForceInitToZero) , TargetOrientation(ForceInitToZero)`
- L33 _public member_ `FVector TargetPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target position of the child body, relative to the parent body
- L37 _public member_ `FRotator TargetOrientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target orientation of the child body, relative to the parent body

#### struct `FRigidBodyControlTargets`  
`struct FRigidBodyControlTargets`  
_L42-49_
- reflection: `USTRUCT(BlueprintType)`
- desc: A set of targets for controls
- L48 _public member_ `TMap<FName, FRigidBodyControlTarget> Targets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Targets to apply to the named control

#### struct `FRigidBodyKinematicTarget`  
`struct FRigidBodyKinematicTarget`  
_L53-70_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single kinematic target, which will be applied in the KinematicTargetSpace set in the relevant body modifier.
- L57 _public function_ `FRigidBodyKinematicTarget() : TargetPosition(ForceInitToZero) , TargetOrientation(ForceInitToZero)`
- L65 _public member_ `FVector TargetPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target position of the body
- L69 _public member_ `FRotator TargetOrientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — The target orientation of the body

#### struct `FRigidBodyKinematicTargets`  
`struct FRigidBodyKinematicTargets`  
_L74-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: A set of kinematic targets
- L80 _public member_ `TMap<FName, FRigidBodyKinematicTarget> Targets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Targets to apply to the named body modifier

#### struct `FRigidBodyForcesAndTorques`  
`struct FRigidBodyForcesAndTorques`  
_L85-92_
- reflection: `USTRUCT(BlueprintType)`
- desc: A set of forces and torques
- L91 _public member_ `TMap<FName, FPhysicsControlForceAndTorqueData> ForcesAndTorques;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsControl)` — Forces (etc) to apply to the named body modifier

#### struct `FRigidBodyControlRecord`  
`struct FRigidBodyControlRecord`  
_L97-140_
- desc: This is the record for a control. It stores the "original" data, which will normally stay fixed. In addition, it will also store some updates to these original data which will determine how the actual controls get used.
- L99 _public prototype_ `FRigidBodyControlRecord(const FPhysicsControl& InControl, ImmediatePhysics::FJointHandle* InJointHandle);`
- L101 _public prototype_ `void ResetCurrent(bool bResetTarget);`
- L104 _public function_ `bool IsEnabled() const` — Note that this is only correct when called during or after the update has been done
- L107 _public prototype_ `FVector GetControlPoint(const ImmediatePhysics::FActorHandle* ChildActorHandle) const;` — Returns the control point, which may be custom or automatic (centre of mass)
- L110 _public member_ `FPhysicsControl Control;` — The configuration data
- L113 _public member_ `FRigidBodyControlTarget ControlTarget;` — Contains any control target that has been set
- L117 _public member_ `UE::PhysicsControl::FPosQuat PreviousTargetTM;` — The previous control target. This will have been set at the end of a previous update (but only if the control was enabled etc), so to check if it is valid, check the update counter.
- L120 _public member_ `FGraphTraversalCounter ExpectedUpdateCounter;` — Update counter set when the control was last updated.
- L125 _public member_ `FPhysicsControlData ControlData;` — This is the currently active control data. It will be updated just prior to applying the controls, by setting it to the default, and then updating it with any parameters. This is so that control updates can be made ephemeral.
- L130 _public member_ `FPhysicsControlMultiplier ControlMultiplier;` — This is the currently active control multiplier. It will be updated just prior to applying the controls, by setting it to the default, and then updating it with any parameters. This is so that control multiplier updates can be made ephemeral.
- L133 _public member_ `int32 ChildBodyIndex;` — Cached child body index - needs to be updated whenever the bone name changes
- L136 _public member_ `int32 ParentBodyIndex;` — Cached parent body index - needs to be updated whenever the bone name changes
- L139 _public member_ `ImmediatePhysics::FJointHandle* JointHandle;` — The low-level physics representation

#### struct `FRigidBodyModifierRecord`  
`struct FRigidBodyModifierRecord`  
_L145-158_
- desc: This is the record for a modifier. It stores the "original" data, which will normally stay fixed. In addition, it will also store some updates to these original data which will determine how the actual body properties get set.
- L147 _public prototype_ `FRigidBodyModifierRecord(const FPhysicsBodyModifier& InModifier, ImmediatePhysics::FActorHandle* InActorHandle);`
- L149 _public prototype_ `void ResetCurrent();`
- L151 _public member_ `FPhysicsBodyModifier Modifier;`
- L155 _public member_ `FPhysicsControlModifierData ModifierData;` — This contains the currently active modifier data. It will be updated just prior to applying the controls, by setting it to the default, and then updating it with any parameters.
- L157 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControl/Public/RigidBodyPoseData.h` (Public)


#### struct `UE::PhysicsControl::FOutputBoneData`  
`struct FOutputBoneData`  
_L18-30_
- L20 _public function_ `FOutputBoneData() : CompactPoseBoneIndex(INDEX_NONE), CompactPoseParentBoneIndex(INDEX_NONE) , BodyIndex(0), ParentBodyIndex(0)`
- L25 _public member_ `TArray<FCompactPoseBoneIndex> BoneIndicesToParentBody;`
- L26 _public member_ `FCompactPoseBoneIndex CompactPoseBoneIndex;`
- L27 _public member_ `FCompactPoseBoneIndex CompactPoseParentBoneIndex;`
- L28 _public member_ `int32 BodyIndex;` — Index into Bodies - will be the same index as into the joints
- L29 _public member_ `int32 ParentBodyIndex;`

#### struct `UE::PhysicsControl::FRigidBodyPoseData`  
`struct FRigidBodyPoseData`  
_L35-64_
- desc: Caches the pose for RigidBodyWithControl
- L38 _public function_ `FRigidBodyPoseData()`
- L41 _public prototype_ `void Update( FComponentSpacePoseContext& ComponentSpacePoseContext, const TArray<FOutputBoneData>& OutputBoneData, const ESimulationSpace SimulationSpace, const FBoneReference& BaseBoneRef, const FGraphTraversalCounter& InUpdateCounter);`
- L48 _public function_ `UE::PhysicsControl::FPosQuat GetTM(int32 Index) const`
- L50 _public function_ `bool IsValidIndex(const int32 Index) const`
- L51 _public function_ `bool IsEmpty() const`
- L53 _public function_ `void SetSize(const int32 NumBones)`
- L56 _public member_ `TArray<UE::PhysicsControl::FPosQuat> BoneTMs;` — The cached skeletal data, updated at the start of each tick
- L60 _public member_ `FGraphTraversalCounter UpdateCounter;` — Track when we were currently/last updated so the user can detect missing updates if calculating velocity etc
- L63 _public member_ `FGraphTraversalCounter ExpectedUpdateCounter;` — When the update is called we'll take the current counter, increment it, and store here so it can be compared.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PhysicsControl` (scope `UE`)
