# Plugins / MassCharacterTrajectory

- module root: `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory`
- headers: 7; symbols: 51
- symbol kinds: class=7, enum=1, enumerator=1, externvar=4, function=2, macro=1, member=13, namespace=3, prototype=15, struct=4
- PrivateDependencyModuleNames: MassSpawner
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassMovement, PoseSearch

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/IMassCharacterTrajectoryModule.h` (Public)


#### class `IMassCharacterTrajectoryModule`  
`class IMassCharacterTrajectoryModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassCharacterTrajectoryModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/MassCharacterTrajectoryDebugProcessor.h` (Public)


#### class `UCharacterTrajectoryDebugProcessor`  
`class UCharacterTrajectoryDebugProcessor : public UMassProcessor`  
_L15-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Debug visualization processor for trajectory samples, velocities, and AABB bounds. Controlled by console variables Mass.CharacterTrajectory.Debug.*
- L20 _public prototype_ `UCharacterTrajectoryDebugProcessor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L27 _private member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define ENABLE_POSE_TRAJECTORY_DEBUG_DRAW (UE_ENABLE_DEBUG_DRAWING && ENABLE_ANIM_DEBUG)`

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/MassCharacterTrajectoryFragments.h` (Public)


#### struct `FCharacterTrajectoryParameters`  
`struct FCharacterTrajectoryParameters : public FMassConstSharedFragment`  
_L22-44_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Shared configuration for trajectory generation. Controls how many samples are recorded and predicted, and at what interval. The total trajectory has NumHistorySamples + 1 + NumPredictionSamples samples: - NumHistorySamples past positions (recorded each frame) - 1 "current" sample at t=DeltaTime (the predicted end-of-frame position) - NumPredictionSamples future positions spaced by PredictionSamplingInterval Added to entities by UCharacterTrajectoryTrait. Used by both USpringMovementToCharacterTrajectoryProcessor and UMovementToCharacterTrajectoryProcessor.
- L29 _public member_ `int32 NumHistorySamples = 30;` — `UPROPERTY(EditAnywhere, Category=Generation)` — Number of past positions to record. Each frame the oldest sample is discarded and the current position is pushed into history.
- L33 _public member_ `float PredictionSamplingInterval = 0.1f;` — `UPROPERTY(EditAnywhere, Category=Generation)` — Time in seconds between each prediction sample.
- L37 _public member_ `int32 NumPredictionSamples = 15;` — `UPROPERTY(EditAnywhere, Category=Generation)` — Number of future prediction samples to generate beyond the current frame.
- L43 _public member_ `FTransform Offset = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category=Generation)` — Additional transform offset applied when computing the trajectory. Useful in actor-less contexts where the mesh-to-world offset cannot be deduced automatically from a SkeletalMeshComponent.

#### struct `FCharacterTrajectoryFragment`  
`struct FCharacterTrajectoryFragment : public FMassFragment`  
_L60-68_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Per-entity trajectory data. Follows PoseSearch sample layout convention: Trajectory.Samples layout (total = NumHistorySamples + 1 + NumPredictionSamples): [0 .. NumHistory-2]  : older history samples (negative time values) [NumHistory-1]       : t=0, last frame's position (beginning of current frame) [NumHistory]         : t=DeltaTime, this frame's predicted position [NumHistory+1 .. end]: future prediction samples Trajectory generation always runs BEFORE movement processors, so it reads the start-of-frame transform from TransformFragment consistently.
- L64 _public member_ `FTransform MeshRelativeTransform = FTransform::Identity;`
- L65 _public member_ `FTransform MeshRootWorldTransform = FTransform::Identity;`
- L66 _public member_ `FQuat SteeringTarget = FQuat::Identity;`
- L67 _public member_ `FTransformTrajectory Trajectory;`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FCharacterTrajectoryFragment> final`  
_L71-77_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L74-76_

#### struct `FCharacterTrajectoryMovementTag`  
`struct FCharacterTrajectoryMovementTag : public FMassTag`  
_L83-86_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Enables trajectory-driven movement via UCharacterTrajectoryToMovementProcessor. Added by UCharacterTrajectoryMovementTrait, which also sets FMassCustomMovementTag to disable default movement processors.

#### Free symbols / members of external scopes

- L75 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anonb4c670d70103`)

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/MassCharacterTrajectoryGenerationProcessors.h` (Public)


#### class `USpringMovementToCharacterTrajectoryProcessor`  
`class USpringMovementToCharacterTrajectoryProcessor : public UMassProcessor`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor converts spring movement data to a generated trajectory. Entities must have FSpringMovementRuntime for this processor to match.
- L18 _public prototype_ `USpringMovementToCharacterTrajectoryProcessor();`
- L21 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L22 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L25 _private member_ `FMassEntityQuery CalculateTrajectoryEntityQuery;`

#### class `UMovementToCharacterTrajectoryProcessor`  
`class UMovementToCharacterTrajectoryProcessor : public UMassProcessor`  
_L34-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor generates a trajectory from standard Mass movement (no spring smoothing). Uses the current velocity and desired movement to predict future positions with constant velocity extrapolation. Matches entities that do NOT have FSpringMovementRuntime.
- L39 _public prototype_ `UMovementToCharacterTrajectoryProcessor();`
- L42 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L43 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L46 _private member_ `FMassEntityQuery CalculateTrajectoryEntityQuery;`

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/MassCharacterTrajectoryMovementProcessor.h` (Public)


#### class `UCharacterTrajectoryToMovementProcessor`  
`class UCharacterTrajectoryToMovementProcessor : public UMassProcessor`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Moves the character along the generated trajectory. Requires FCharacterTrajectoryMovementTag (added by UCharacterTrajectoryMovementTrait).
- L18 _public prototype_ `UCharacterTrajectoryToMovementProcessor();`
- L21 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L22 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L25 _private member_ `FMassEntityQuery EntityQuery;`

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/MassCharacterTrajectoryTrait.h` (Public)


#### class `UCharacterTrajectoryTrait`  
`class UCharacterTrajectoryTrait : public UMassEntityTraitBase`  
_L31-40_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, CollapseCategories, meta = (DisplayName = "Character Trajectory Generation"))`
- inherits: `UMassEntityTraitBase`
- desc: Enables trajectory generation for this entity. Adds FCharacterTrajectoryFragment and configures trajectory sampling parameters (history size, prediction samples, sampling interval). The trajectory is generated each frame by one of two processors depending on configuration: - USpringMovementToCharacterTrajectoryProcessor: if USpringMovementTrait is also present, uses the spring runtime state to predict a smoothed trajectory. - UMovementToCharacterTrajectoryProcessor: if no spring is present, uses current velocity and desired movement with constant-velocity extrapolation. This trait can be combined with: - USpringMovementTrait: spring-damped movement with trajectory prediction for animation. - UCharacterTrajectoryMovementTrait: overrides default movement to drive the entity along the generated trajectory instead. - Both: spring update feeds trajectory generation, trajectory drives movement. Also initializes MeshRelativeTransform from the entity's SkeletalMeshComponent if present.
- L36 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L39 _protected member_ `FCharacterTrajectoryParameters PoseTrajectoryParameters;` — `UPROPERTY(Category = "Steering", EditAnywhere, meta = (EditInline))`

#### class `UCharacterTrajectoryMovementTrait`  
`class UCharacterTrajectoryMovementTrait : public UMassMovementTrait`  
_L57-64_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, CollapseCategories, meta = (DisplayName = "Character Trajectory Movement"))`
- inherits: `UMassMovementTrait`
- desc: Overrides default movement to drive the entity along the generated trajectory. Extends UMassMovementTrait to provide FMassMovementParameters for AI systems. Adds FCharacterTrajectoryMovementTag (matched by UCharacterTrajectoryToMovementProcessor) and FMassCustomMovementTag (disables UMassApplyMovementProcessor and USpringMovementApplyProcessor so that trajectory movement is the sole movement authority). Requires UCharacterTrajectoryTrait — validated at template build time. Execution flows with this trait: - With USpringMovementTrait: DesiredMovement -> UpdateSpring -> GenerateTrajectory -> MoveAlongTrajectory - Without spring:           DesiredMovement -> GenerateTrajectory -> MoveAlongTrajectory
- L62 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L63 _protected prototype_ `virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const override;`

### `Plugins/Runtime/MassGameplay/Source/MassCharacterTrajectory/Public/MassCharacterTrajectoryTypes.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mass` (scope `UE`)
- L8 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L10 _externvar_ `extern const FName CharacterTrajectoryGeneration;` (scope `UE::Mass::ProcessorGroupNames`)
- L11 _externvar_ `extern const FName CharacterTrajectoryCollision;` (scope `UE::Mass::ProcessorGroupNames`)
- L12 _externvar_ `extern const FName CharacterTrajectoryMovement;` (scope `UE::Mass::ProcessorGroupNames`)
- L13 _externvar_ `extern const FName CharacterTrajectoryDebug;` (scope `UE::Mass::ProcessorGroupNames`)
