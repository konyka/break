# Plugins / MassAIBehavior

- module root: `Plugins/AI/MassAI/Source/MassAIBehavior`
- headers: 40; symbols: 741
- symbol kinds: class=21, delegate=1, enum=8, enumerator=25, externvar=1, function=83, macro=25, member=253, namespace=52, prototype=171, struct=68, typedef=18, variable=15
- PrivateDependencyModuleNames: EditorFramework, PropertyBindingUtils, UnrealEd
- PrivateIncludePathModuleNames: AIModule
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, GameplayTags, MassActors, MassCommon, MassCore, MassEntity, MassGameplayExternalTraits, MassLOD, MassMovement, MassNavMeshNavigation, MassNavigation, MassRepresentation, MassSignals, MassSimulation, MassSmartObjects, MassSpawner, MassZoneGraphNavigation, NavCorridor, NavigationSystem, SmartObjectsModule, StateTreeModule, ZoneGraph, ZoneGraphAnnotations

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Conditions/ZoneGraphTagConditions.h` (Public)


#### struct `FZoneGraphTagFilterConditionInstanceData`  
`struct FZoneGraphTagFilterConditionInstanceData`  
_L17-23_
- reflection: `USTRUCT()`
- L22 _public member_ `FZoneGraphTagMask Tags = FZoneGraphTagMask::None;` — `UPROPERTY(EditAnywhere, Category = Input)`

#### struct `FZoneGraphTagFilterCondition`  
`struct FZoneGraphTagFilterCondition : public FMassStateTreeConditionBase`  
_L26-42_
- reflection: `USTRUCT(DisplayName="ZoneGraphTagFilter Compare")`
- inherits: `FMassStateTreeConditionBase`
- L30 _public typedef_ `using FInstanceDataType = FZoneGraphTagFilterConditionInstanceData;`
- L32 _public prototype_ `FZoneGraphTagFilterCondition() = default;`
- L34 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L35 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L38 _public member_ `FZoneGraphTagFilter Filter;` — `UPROPERTY(EditAnywhere, Category = Condition)`
- L41 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### struct `FZoneGraphTagMaskConditionInstanceData`  
`struct FZoneGraphTagMaskConditionInstanceData`  
_L49-58_
- reflection: `USTRUCT()`
- L54 _public member_ `FZoneGraphTagMask Left = FZoneGraphTagMask::None;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L57 _public member_ `FZoneGraphTagMask Right = FZoneGraphTagMask::None;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FZoneGraphTagMaskCondition`  
`struct FZoneGraphTagMaskCondition : public FMassStateTreeConditionBase`  
_L61-77_
- reflection: `USTRUCT(DisplayName="ZoneGraphTagMask Compare")`
- inherits: `FMassStateTreeConditionBase`
- L65 _public typedef_ `using FInstanceDataType = FZoneGraphTagMaskConditionInstanceData;`
- L67 _public prototype_ `FZoneGraphTagMaskCondition() = default;`
- L69 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L70 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L73 _public member_ `EZoneLaneTagMaskComparison Operator = EZoneLaneTagMaskComparison::Any;` — `UPROPERTY(EditAnywhere, Category = Condition)`
- L76 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### struct `FZoneGraphTagConditionInstanceData`  
`struct FZoneGraphTagConditionInstanceData`  
_L84-93_
- reflection: `USTRUCT()`
- L89 _public member_ `FZoneGraphTag Left = FZoneGraphTag::None;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L92 _public member_ `FZoneGraphTag Right = FZoneGraphTag::None;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FZoneGraphTagCondition`  
`struct FZoneGraphTagCondition : public FMassStateTreeConditionBase`  
_L96-109_
- reflection: `USTRUCT(DisplayName="ZoneGraphTag Compare")`
- inherits: `FMassStateTreeConditionBase`
- L100 _public typedef_ `using FInstanceDataType = FZoneGraphTagConditionInstanceData;`
- L102 _public prototype_ `FZoneGraphTagCondition() = default;`
- L104 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L105 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L108 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Condition)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Evaluators/MassComponentHitEvaluator.h` (Public)


#### struct `FMassComponentHitEvaluatorInstanceData`  
`struct FMassComponentHitEvaluatorInstanceData`  
_L22-31_
- reflection: `USTRUCT()`
- L27 _public member_ `bool bGotHit = false;` — `UPROPERTY(VisibleAnywhere, Category = Output)`
- L30 _public member_ `FMassEntityHandle LastHitEntity;` — `UPROPERTY(VisibleAnywhere, Category = Output)`

#### struct `FMassComponentHitEvaluator`  
`struct FMassComponentHitEvaluator : public FMassStateTreeEvaluatorBase`  
_L34-47_
- reflection: `USTRUCT(meta = (DisplayName = "Mass ComponentHit Eval"))`
- inherits: `FMassStateTreeEvaluatorBase`
- L38 _public typedef_ `using FInstanceDataType = FMassComponentHitEvaluatorInstanceData;`
- L41 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L42 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L43 _protected prototype_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L44 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L46 _protected member_ `TStateTreeExternalDataHandle<UMassComponentHitSubsystem> ComponentHitSubsystemHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Evaluators/MassZoneGraphAnnotationEvaluator.h` (Public)


#### struct `FMassZoneGraphAnnotationEvaluatorInstanceData`  
`struct FMassZoneGraphAnnotationEvaluatorInstanceData`  
_L22-28_
- reflection: `USTRUCT()`
- desc: Evaluator to expose ZoneGraph Annotation Tags for decision-making.
- L27 _public member_ `FZoneGraphTagMask AnnotationTags = FZoneGraphTagMask::None;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMassZoneGraphAnnotationEvaluator`  
`struct FMassZoneGraphAnnotationEvaluator : public FMassStateTreeEvaluatorBase`  
_L31-46_
- reflection: `USTRUCT(meta = (DisplayName = "ZG Annotation Tags"))`
- inherits: `FMassStateTreeEvaluatorBase`
- L35 _public typedef_ `using FInstanceDataType = FMassZoneGraphAnnotationEvaluatorInstanceData;`
- L37 _public prototype_ `FMassZoneGraphAnnotationEvaluator();`
- L40 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L41 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L42 _protected prototype_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L43 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L45 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphAnnotationFragment> AnnotationTagsFragmentHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/IMassAIBehaviorModule.h` (Public)


#### class `IMassAIBehaviorModule`  
`class IMassAIBehaviorModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassAIBehaviorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassAIBehaviorTypes.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassBehavior, Warning, All);`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mass` (scope `UE`)
- L11 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L13 _variable_ `const FName UpdateAnnotationTags = FName(TEXT("Upda` (scope `UE::Mass::ProcessorGroupNames`)
- L31 _macro_ `#define MASSBEHAVIOR_LOG(Verbosity, Format, ...) UE_VLOG_UELOG(static_cast<const FMassStateTreeExecutionContext&>(Context).GetOwner(), LogMassBehavior, Verbosity, \`
- L33 _macro_ `#define MASSBEHAVIOR_CLOG(Condition, Verbosity, Format, ...) UE_CVLOG_UELOG((Condition), static_cast<const FMassStateTreeExecutionContext&>(Context).GetOwner(), LogMassBehavior, Verbosity, \`
- L36 _macro_ `#define MASSBEHAVIOR_LOG(Verbosity, Format, ...)`
- L37 _macro_ `#define MASSBEHAVIOR_CLOG(Condition, Verbosity, Format, ...)`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassBehaviorSettings.h` (Public)


#### class `UMassBehaviorSettings`  
`class UMassBehaviorSettings : public UMassModuleSettings`  
_L14-30_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, meta = (DisplayName = "Mass Behavior"))`
- inherits: `UMassModuleSettings`
- L19 _public prototype_ `UMassBehaviorSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public member_ `int32 MaxActivationsPerLOD[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)`
- L29 _public member_ `TSoftClassPtr<UMassStateTreeProcessor> DynamicStateTreeProcessorClass;` — `UPROPERTY(Config, EditAnywhere, Category="Mass|StateTree", NoClear)` — Class to use when creating dynamic processors to handle given StateTree assets. Can be also set via DefaultMass.ini file.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassComponentHitSubsystem.h` (Public)


#### class `UMassComponentHitSubsystem`  
`class UMassComponentHitSubsystem : public UMassTickableSubsystemBase`  
_L21-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTickableSubsystemBase`
- desc: Subsystem that keeps track of the latest component hits and allow mass entities to retrieve and handle them
- L26 _public prototype_ `const FMassHitResult* GetLastHit(const FMassEntityHandle Entity) const;`
- L29 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L30 _protected prototype_ `virtual void Deinitialize() override;`
- L31 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L32 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L34 _protected prototype_ `void RegisterForComponentHit(const FMassEntityHandle Entity, UCapsuleComponent& CapsuleComponent);`
- L35 _protected prototype_ `void UnregisterForComponentHit(FMassEntityHandle Entity, UCapsuleComponent& CapsuleComponent);`
- L38 _protected prototype_ `void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);` — `UFUNCTION()`
- L41 _protected member_ `TObjectPtr<UMassSignalSubsystem> SignalSubsystem;` — `UPROPERTY()`
- L44 _protected member_ `TObjectPtr<UMassAgentSubsystem> AgentSubsystem;` — `UPROPERTY()`
- L47 _protected member_ `TMap<FMassEntityHandle, FMassHitResult> HitResults;` — `UPROPERTY()`
- L50 _protected member_ `TMap<TObjectPtr<UActorComponent>, FMassEntityHandle> ComponentToEntityMap;` — `UPROPERTY()`
- L53 _protected member_ `TMap<FMassEntityHandle, TObjectPtr<UActorComponent>> EntityToComponentMap;` — `UPROPERTY()`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassComponentHitSubsystem>`  
_L57-64_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L60-63_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L61 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon1941e8a90103`)
- L62 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon1941e8a90103`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassComponentHitTypes.h` (Public)


#### struct `FMassHitResult`  
`struct FMassHitResult`  
_L19-41_
- reflection: `USTRUCT()`
- L23 _public prototype_ `FMassHitResult() = default;`
- L25 _public function_ `FMassHitResult(const FMassEntityHandle OtherEntity, const double Time) : OtherEntity(OtherEntity) , HitTime(Time) , LastFilteredHitTime(Time)`
- L32 _public function_ `bool IsValid() const`
- L34 _public member_ `FMassEntityHandle OtherEntity;`
- L37 _public member_ `double HitTime = 0.;` — Time when first hit was received.
- L40 _public member_ `double LastFilteredHitTime = 0.;` — Time used for filtering frequent hits.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mass` (scope `UE`)
- L13 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L15 _variable_ `const FName HitReceived = FName(TEXT("HitR` (scope `UE::Mass::Signals`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtFragments.h` (Public)


#### enum `EMassLookAtMode`  
`enum class EMassLookAtMode : uint8`  
_L17-25_
- reflection: `UENUM()`
- desc: Primary look at mode, gazing can be applied on top.
- L20 _public enumerator_ `LookForward` — Look forward
- L22 _public enumerator_ `LookAlongPath` — Look along the current path
- L24 _public enumerator_ `LookAtEntity` — Track specified entity

#### enum `EMassLookAtGazeMode`  
`enum class EMassLookAtGazeMode : uint8`  
_L29-37_
- reflection: `UENUM()`
- desc: Different gaze modes applied on top of the look at mode.
- L32 _public enumerator_ `None` — No gazing
- L34 _public enumerator_ `Constant` — Look constantly in gaze direction until next gaze target is picked.
- L36 _public enumerator_ `Glance` — Quick look at gaze target, ease in back to main look direction.

#### struct `FMassLookAtFragment`  
`struct FMassLookAtFragment : public FMassFragment`  
_L43-192_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Struct that holds all parameters of the current entity look at
- L48 _public function_ `void ResetGaze()` — Resets gaze related properties in the fragment to their default values
- L62 _public function_ `void ResetAll()` — Resets all properties in the fragment to their default values
- L69 _public function_ `void ResetMainLookAt()` — Resets main LookAt related properties in the fragment to their default values
- L79 _public function_ `void ResetSystemicLookAt()` — Resets gaze and main LookAt (if override not active) related properties in the fragment to their default values
- L104 _public member_ `FVector MainTargetLocation = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Current look at main target location.
- L108 _public member_ `FVector GazeTargetLocation = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Current gaze target location.
- L112 _public member_ `FVector Direction = FVector::ForwardVector;` — `UPROPERTY(Transient)` — Current look at direction (with gaze applied).
- L116 _public member_ `FVector GazeDirection = FVector::ForwardVector;` — `UPROPERTY(Transient)` — Current gaze direction, applied on top of look at direction based on gaze mode.
- L120 _public member_ `FMassEntityHandle TrackedEntity;` — `UPROPERTY(Transient)` — Specific entity that is being tracked as primary look at.
- L124 _public member_ `FMassEntityHandle GazeTrackedEntity;` — `UPROPERTY(Transient)` — Entity that is tracked as part of gazing.
- L128 _public member_ `double GazeStartTime = 0.;` — `UPROPERTY(Transient)` — Start time of the current gaze.
- L132 _public member_ `float GazeDuration = 0.0f;` — `UPROPERTY(Transient)` — Duration of the current gaze.
- L136 _public member_ `uint16 LastSeenActionID = 0;` — `UPROPERTY(Transient)` — Last seen action ID, used to check when look at trajectory needs to be updated.
- L140 _public member_ `EMassLookAtMode LookAtMode = EMassLookAtMode::LookForward;` — `UPROPERTY(Transient)` — Primary look at mode.
- L144 _public member_ `EMassLookAtInterpolationSpeed InterpolationSpeed = EMassLookAtInterpolationSpeed::Regular;` — `UPROPERTY(Transient)` — Primary look at interpolation speed (not used by the LookAt processor but can be forwarded to the animation system).
- L151 _public member_ `float CustomInterpolationSpeed = UE::Mass::LookAt::DefaultCustomInterpolationSpeed;` — `UPROPERTY(Transient)` — Primary look at custom interpolation speed used when 'InterpolationSpeed = EMassLookAtInterpolationSpeed::Custom' (not used by the LookAt processor but can be forwarded to the animation system).
- L155 _public member_ `EMassLookAtGazeMode RandomGazeMode = EMassLookAtGazeMode::None;` — `UPROPERTY(Transient)` — Gaze look at mode.
- L159 _public member_ `uint8 RandomGazeYawVariation = 0;` — `UPROPERTY(Transient)` — Random gaze angle yaw variation (in degrees).
- L163 _public member_ `uint8 RandomGazePitchVariation = 0;` — `UPROPERTY(Transient)` — Random gaze angle pitch variation (in degrees).
- L167 _public member_ `uint8 bRandomGazeEntities : 1 = false;` — `UPROPERTY(Transient)` — Whether random gaze can also pick interesting entities to look at.
- L191 _public member_ `EOverrideState OverrideState : 7 = EOverrideState::AllDisabled;` — Current state based on the systemic task and active overrides

#### enum `FMassLookAtFragment::EOverrideState`  
`enum class EOverrideState : uint8`  
_L169-188_
- L172 _public enumerator_ `AllDisabled` — No active task and no active override
- L175 _public enumerator_ `ActiveOverrideOnly` — No active task, only an active override
- L178 _public enumerator_ `ActiveSystemicOnly` — Active task only, no active override
- L181 _public enumerator_ `OverridenSystemic` — Active task overriden
- L187 _public enumerator_ `PendingSystemicReactivation` — Intermediate state used from 'OverridenSystemic' after removing last override request to allow active task to reapply its values and transition to 'ActiveSystemicOnly'

#### struct `FMassLookAtTargetTag`  
`struct UE_DEPRECATED(5.6, "Use FMassLookAtTargetFragment instead") FMassLookAtTargetTag : public FMassTag`  
_L198-201_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Special tag to mark an entity that could be tracked by the LookAt

#### struct `FMassLookAtRequestFragment`  
`struct FMassLookAtRequestFragment : public FMassFragment`  
_L207-265_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Struct that holds all parameters of a look at request
- L211 _public prototype_ `FMassLookAtRequestFragment() = default;`
- L212 _public function_ `FMassLookAtRequestFragment(const FMassEntityHandle ViewerEntity, const FMassLookAtPriority Priority, const EMassLookAtMode Mode) : ViewerEntity(ViewerEntity) , Priority(Priority) , LookAtMode(Mode)`
- L219 _public function_ `FMassLookAtRequestFragment( const FMassEntityHandle ViewerEntity , const FMassLookAtPriority Priority , const EMassLookAtMode Mode , const FMassEntityHandle Target , const EMassLookAtInterpolationSpeed InterpolationSpeed , const float CustomInterpolationSpeed) : FMassLookAtRequestFragment(ViewerEntity, Priority, Mode)`
- L234 _public member_ `FMassEntityHandle ViewerEntity;` — `UPROPERTY(Transient)`
- L237 _public member_ `FMassEntityHandle TargetEntity;` — `UPROPERTY(Transient)`
- L240 _public member_ `FMassLookAtPriority Priority{static_cast<uint8>(EMassLookAtPriorities::LowestPriority)};` — `UPROPERTY(Transient)`
- L243 _public member_ `EMassLookAtMode LookAtMode = EMassLookAtMode::LookForward;` — `UPROPERTY(Transient)`
- L246 _public member_ `EMassLookAtInterpolationSpeed InterpolationSpeed = EMassLookAtInterpolationSpeed::Regular;` — `UPROPERTY(Transient)`
- L249 _public member_ `float CustomInterpolationSpeed = UE::Mass::LookAt::DefaultCustomInterpolationSpeed;` — `UPROPERTY(Transient)`

#### struct `FMassLookAtTargetFragment`  
`struct FMassLookAtTargetFragment : public FMassFragment`  
_L272-285_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment to mark an entity that could be tracked by the LookAt processor and providing information that could be used to get more accurate locations.
- L278 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Offset in local space to add to the target transform to get the final location
- L282 _public member_ `FMassLookAtPriority Priority{static_cast<uint8>(EMassLookAtPriorities::LowestPriority)};` — `UPROPERTY(Transient)` — When a viewer is searching for a random target this priority will influence the selected target
- L284 _public member_ `UE::Mass::LookAt::FTargetHashGrid2D::FCellLocation CellLocation;`

#### struct `FMassInLookAtTargetGridTag`  
`struct FMassInLookAtTargetGridTag : public FMassTag`  
_L289-292_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag to tell if the entity is in the LookAt target grid

#### struct `FMassLookAtTrajectoryPoint`  
`struct FMassLookAtTrajectoryPoint`  
_L295-314_
- reflection: `USTRUCT()`
- L299 _public function_ `void Set(const FVector InPosition, const FVector2D InTangent, const float InDistanceAlongLane)`
- L307 _public member_ `FVector Position = FVector::ZeroVector;` — Position of the path.
- L310 _public member_ `FMassSnorm8Vector2D Tangent;` — Tangent direction of the path.
- L313 _public member_ `FMassInt16Real10 DistanceAlongLane = FMassInt16Real10(0.0f);` — Position of the point along the original path. (Could potentially be uint16 at 10cm accuracy)

#### struct `FMassLookAtTrajectoryFragment`  
`struct FMassLookAtTrajectoryFragment : public FMassFragment`  
_L317-353_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L321 _public prototype_ `FMassLookAtTrajectoryFragment() = default;`
- L323 _public member_ `static constexpr uint8 MaxPoints = 3;`
- L325 _public function_ `void Reset()`
- L330 _public function_ `bool AddPoint(const FVector Position, const FVector2D Tangent, const float DistanceAlongLane)`
- L341 _public prototype_ `FVector GetPointAtDistanceExtrapolated(const float DistanceAlongPath) const;`
- L344 _public member_ `TStaticArray<FMassLookAtTrajectoryPoint, MaxPoints> Points;` — Path points
- L347 _public member_ `FZoneGraphLaneHandle LaneHandle;` — Lane handle the trajectory was build for.
- L350 _public member_ `uint8 NumPoints = 0;` — Number of points on path.
- L352 _public member_ `bool bMoveReverse = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L251 _function_ `friend FString LexToString(const FMassLookAtRequestFragment& Fragment)`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtProcessors.h` (Public)


#### class `UMassLookAtProcessor`  
`class UMassLookAtProcessor : public UMassProcessor`  
_L27-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor to choose and assign LookAt configurations
- L31 _private prototype_ `UMassLookAtProcessor();`
- L35 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L36 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L39 _protected prototype_ `void FindNewGazeTarget(const UMassNavigationSubsystem& MassNavSystem , const UMassLookAtSubsystem& LookAtSystem , const FMassEntityManager& EntityManager , const double CurrentTime , const FTransform& Transform , FMassEntityHandle Entity , FMassLookAtFragment& LookAt) const;` — Selects a nearby target if possible or use a random fixed direction
- L48 _protected prototype_ `void UpdateLookAtTrajectory(const FTransform& Transform, const FMassZoneGraphLaneLocationFragment& ZoneGraphLocation, const FMassLookAtTrajectoryFragment& LookAtTrajectory, const bool bDisplayDebug, FMassLookAtFragment& LookAt) const;` — Updates look direction based on look at trajectory.
- L52 _protected prototype_ `void UpdateLookAtTrackedEntity(const FMassEntityManager& EntityManager, const FTransform& Transform, const bool bDisplayDebug, FMassLookAtFragment& LookAt) const;` — Updates look at based on tracked entity.
- L55 _protected prototype_ `bool UpdateGazeTrackedEntity(const FMassEntityManager& EntityManager, const FTransform& Transform, const bool bDisplayDebug, FMassLookAtFragment& LookAt) const;` — Updates gaze based on tracked entity.
- L58 _protected prototype_ `void BuildTrajectory(const UZoneGraphSubsystem& ZoneGraphSubsystem, const FMassZoneGraphLaneLocationFragment& LaneLocation, const FMassZoneGraphShortPathFragment& ShortPath, const FMassEntityHandle Entity, const bool bDisplayDebug, FMassLookAtTrajectoryFragment& LookAtTrajectory);` — Builds look at trajectory along the current path.
- L63 _protected member_ `float QueryExtent = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = LookAt, config, meta = (UIMin = 0.0, ClampMin = 0.0))` — Size of the query to find potential targets
- L67 _protected member_ `float Duration = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = LookAt, config, meta = (UIMin = 0.0, ClampMin = 0.0))` — Time an entity must use a random look at.
- L71 _protected member_ `float DurationVariation = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = LookAt, config, meta = (UIMin = 0.0, ClampMin = 0.0))` — Variation applied to a random look at duration [Duration-Variation : Duration+Variation]
- L75 _protected member_ `float DebugZOffset = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = LookAt, config, meta = (UIMin = 0.0, ClampMin = 0.0, DisplayName="Debug draw Z offset (cm)"))` — Height offset that will be added for debug draw of the look at vector. Useful to bring arrow near character's eyes
- L79 _protected member_ `float AngleThresholdInDegrees = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = LookAt, config, meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 180.0, ClampMax = 180.0, DisplayName="Angle Threshold (degrees)"))` — Tolerance in degrees between the forward direction and the look at duration to track an entity
- L81 _protected member_ `FMassEntityQuery EntityQuery_Conditional;`

#### class `UMassLookAtTargetGridProcessor`  
`class UMassLookAtTargetGridProcessor : public UMassProcessor`  
_L88-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor to maintain a list of LookAt targets in a spatial query structure in the subsystem
- L92 _private prototype_ `UMassLookAtTargetGridProcessor();`
- L96 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L97 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L99 _protected member_ `FMassEntityQuery AddToGridQuery;`
- L100 _protected member_ `FMassEntityQuery UpdateGridQuery;`
- L101 _protected member_ `FMassEntityQuery RemoveFromGridQuery;`

#### class `UMassLookAtTargetRemoverProcessor`  
`class UMassLookAtTargetRemoverProcessor : public UMassObserverProcessor`  
_L106-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Deinitializer processor to remove targets from the hash grid
- L110 _private prototype_ `UMassLookAtTargetRemoverProcessor();`
- L113 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L114 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L116 _protected member_ `FMassEntityQuery Query;`

#### class `UMassLookAtRequestInitializer`  
`class UMassLookAtRequestInitializer : public UMassObserverProcessor`  
_L121-133_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Initializer processing new LookAt requests
- L125 _private prototype_ `UMassLookAtRequestInitializer();`
- L128 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L129 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L132 _private member_ `FMassEntityQuery Query;`

#### class `UMassLookAtRequestDeinitializer`  
`class UMassLookAtRequestDeinitializer : public UMassObserverProcessor`  
_L138-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Deinitializer processing deleted LookAt requests
- L142 _private prototype_ `UMassLookAtRequestDeinitializer();`
- L145 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L146 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L149 _private member_ `FMassEntityQuery Query;`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtSettings.h` (Public)


#### class `UMassLookAtSettings`  
`class UMassLookAtSettings : public UDeveloperSettings`  
_L15-85_
- reflection: `UCLASS(MinimalAPI, config = Plugins, defaultconfig, DisplayName = "Mass LookAt")`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the MassLookAt module.
- L19 _public prototype_ `explicit UMassLookAtSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L25 _public prototype_ `void GetValidPriorityInfos(TArray<FMassLookAtPriorityInfo>& OutInfos) const;`
- L28 _public function_ `[[nodiscard]] FVector GetDefaultTargetLocationOffset() const` — @return Additional offset to add to the target location (aka eyes height)
- L39 _public function_ `[[nodiscard]] double GetTargetHeightRatio() const` — Specifies a modifier applied to the target height, if available, to adjust the final location to look at. Value of 0 represents the base location and a value of 1 the base location with the full target height offset. TargetHeightRatio is applied before FixedOffsetFromTargetHeight* @return Modifier applied on the target height to compute the final location to look at
- L49 _public function_ `[[nodiscard]] double GetFixedOffsetFromTargetHeight() const` — Specifies the offset to add to the target height, if available, to adjust the final location to look at. Negative value should be used to lower the target. @return Offset applied on the target height to compute the final location to look at
- L54 _public member_ `static FOnMassLookAtPrioritiesChanged OnMassLookAtPrioritiesChanged;`
- L59 _protected member_ `FMassLookAtPriorityInfo Priorities[static_cast<int32>(EMassLookAtPriorities::MaxPriorities)];` — `UPROPERTY(EditAnywhere, config, Category = LookAt)`
- L66 _protected member_ `FVector DefaultTargetLocationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, config, Category = LookAt)` — Additional offset added to the target base location (i.e., TransformFragment). This is used by default when no specific height information (i.e., LookAtTargetTrait initializer) is available.
- L75 _protected member_ `double TargetHeightRatio = 1.0;` — `UPROPERTY(EditAnywhere, config, Category = LookAt, meta = (EditCondition = bShouldUseCapsuleComponentToSetTargetOffset))` — Optional height modifier ratio applied to the target height, if available, to adjust the final location to look at. Value of 0 represents the base location and a value of 1 the base location with the full target height offset. TargetHeightRatio is applied before FixedOffsetFromTargetHeight @see FixedOffsetFromTargetHeight
- L84 _protected member_ `double FixedOffsetFromTargetHeight = 0;` — `UPROPERTY(EditAnywhere, config, Category = LookAt, meta = (EditCondition = bShouldUseCapsuleComponentToSetTargetOffset))` — Optional fixed offset (in cm) added to the target height, if available, to adjust the final location to look at. Negative value should be used to lower the target. TargetHeightRatio is applied before FixedOffsetFromTargetHeight @see TargetHeightRatio

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMassLookAtPrioritiesChanged);`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMassLookAtPrioritiesChanged);`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtSubsystem.h` (Public)


#### struct `FMassLookAtRequestHandle`  
`struct FMassLookAtRequestHandle`  
_L14-36_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public prototype_ `FMassLookAtRequestHandle() = default;`
- L20 _public function_ `FMassLookAtRequestHandle(const FMassEntityHandle& Request, const FMassEntityHandle& Target, const bool bTargetEntityOwnedByRequest) : Request(Request) , Target(Target) , bTargetEntityOwnedByRequest(bTargetEntityOwnedByRequest)`
- L28 _public member_ `FMassEntityHandle Request;` — `UPROPERTY()`
- L31 _public member_ `FMassEntityHandle Target;` — `UPROPERTY()`
- L35 _public member_ `bool bTargetEntityOwnedByRequest = false;` — `UPROPERTY()` — Indicates if the target entity was created for the request and must be destroyed when deleting the request (e.g. CreateLookAtPositionRequest)

#### class `UMassLookAtSubsystem`  
`class UMassLookAtSubsystem : public UMassTickableSubsystemBase`  
_L42-258_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTickableSubsystemBase`
- desc: Subsystem that keeps track of the LookAt targets
- L68 _public prototype_ `FMassLookAtRequestHandle CreateLookAtPositionRequest(AActor* ViewerActor , FMassLookAtPriority Priority , FVector TargetLocation , EMassLookAtInterpolationSpeed InterpolationSpeed = EMassLookAtInterpolationSpeed::Regular , float CustomInterpolationSpeed = 1.5f) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LookAt", meta = (ReturnDisplayName="Request Handle"))` — Creates a new LookAt request using the provided parameters for the mass entity associated to 'ViewerActor', if any. @param ViewerActor Actor associated to the mass entity that needs to perform the LookAt @param Priority Priority assigned to the request that will influence selected request when multiple requests are sent to the same entity @param TargetLocation Static location used as target @param InterpolationSpeed Optional parameter to use predefined interpolation speed @param CustomInterpolationSpeed Optional parameter to specify a custom interpolation speed when 'InterpolationSpeed' is set to EMassLookAtInterpolationSpeed::Custom Method will log an error if it fails (e.g., no associated mass entity).
- L85 _public prototype_ `FMassLookAtRequestHandle CreateLookAtActorRequest(AActor* ViewerActor , FMassLookAtPriority Priority , AActor* TargetActor , EMassLookAtInterpolationSpeed InterpolationSpeed = EMassLookAtInterpolationSpeed::Regular , float CustomInterpolationSpeed = 1.5f) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LookAt", meta = (ReturnDisplayName="Request Handle"))` — Creates a new LookAt request using the provided parameters for the mass entity associated to 'ViewerActor', if any. @param ViewerActor Actor associated to the mass entity that needs to perform the LookAt @param Priority Priority assigned to the request that will influence selected request when multiple requests are sent to the same entity @param TargetActor Actor used as reference for the target location. If the actor has an associated mass entity then the target location will be updated during the request lifetime. Otherwise, the actor location will be used to create a LookAt using a static target location @param InterpolationSpeed Optional parameter to use predefined interpolation speed @param CustomInterpolationSpeed Optional parameter to specify a custom interpolation speed when 'InterpolationSpeed' is set to EMassLookAtInterpolationSpeed::Custom Method will log an error if it fails (e.g., no associated mass entity for viewer)
- L96 _public prototype_ `void DeleteRequest(FMassLookAtRequestHandle RequestHandle) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LookAt")` — Removes given request from the active LookAt requests. Method will log an error if it fails (e.g., invalid request handle).
- L104 _public prototype_ `void RegisterRequests(const FMassExecutionContext& InContext, TArray<FRequest>&& InRequests);` — Appends the provided requests to the active ones, then updates the LookAt fragments of the referenced entity if required. @param InContext Context that is used to push deferred commands @param InRequests List of new request to register
- L112 _public prototype_ `void UnregisterRequests(const FMassExecutionContext& InContext, TConstArrayView<FMassEntityHandle> InRequests);` — Unregisters the provided requests from the list of active ones, then updates the LookAt fragments of the referenced entity if required. @param InContext Context that is used to push deferred commands @param InRequests List of request to unregister
- L121 _public function_ `[[nodiscard]] UE::Mass::LookAt::FTargetHashGrid2D::FCellLocation AddTarget(const FMassEntityHandle InEntity, const FMassLookAtTargetFragment& InTarget, const FBox& InBounds)` — Adds new item to the grid for a given entity handle representing a LookAt target. @param InEntity - Entity used to identify the item in the grid. @param InTarget - Fragment providing details about the target (i.e., priority) @param InBounds - Bounding box of the entity. @return The cell location where the item was added to, can be used later to move or remove the item.
- L134 _public function_ `[[nodiscard]] UE::Mass::LookAt::FTargetHashGrid2D::FCellLocation MoveTarget(const FMassEntityHandle InEntity, const FMassLookAtTargetFragment& InTarget, const FBox& InNewBounds)` — Moves item based on the entity handle, its previous cell location and its new bounding box. @param InEntity - Entity used to identify the item in the grid. @param InTarget - Fragment providing details about the target (i.e., cell location the item was previously added or moved with). @param InNewBounds - New bounds of the item @return The cell location where the item is now added to.
- L145 _public function_ `void BatchMoveTarget(const TArrayView<TTuple<const FMassEntityHandle, FMassLookAtTargetFragment&, const FBox>> InUpdates)` — Moves multiple items based on their entity handle, cell location and new bounding box. @param InUpdates - List of entity, cell location reference and new bounds to use for each item to update in the grid. @note Cell location provided in the tuple is a reference and will be updated in the process.
- L164 _public function_ `void RemoveTarget(const FMassEntityHandle InEntity, const FMassLookAtTargetFragment& InTarget)` — Removes item based on the entity handle and the cell location it was added with. @param InEntity - Entity used to identify the item in the grid. @param InTarget - Fragment providing details about the target (i.e., cell location the item was previously added or moved with).
- L176 _public function_ `template <typename OutT> bool Query(const FBox& InQueryBox, OutT& OutEntities) const` — Returns entity that potentially touch the bounds. Operates on grid level, can have false positives. @param InQueryBox - Query bounding box. @param OutEntities - Result of the query, entity handles of potentially overlapping items.
- L184 _public function_ `int32 DebugGetRegisteredTargetCount() const` — @return Number of entities currently registered in the grid.
- L190 _public function_ `const FMassArchetypeHandle& DebugGetRequestArchetype() const` — @return Mass archetype to create entities representing a LookAt request
- L196 _public function_ `const FMassArchetypeHandle& DebugGetTargetArchetype() const` — @return Mass archetype to create entities representing a LookAt target
- L203 _public prototype_ `FString DebugGetRequestsString(FMassEntityHandle InEntity) const;` — @return String detailing all requests registered for a given entity.
- L208 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L209 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L217 _private prototype_ `void UpdateLookAts(const FMassExecutionContext& Context, TConstArrayView<int32> DirtyViewers);` — Called after registering/unregistering requests to update the LookAtFragment of all viewer entities referenced in those requests
- L227 _private member_ `TArray<FRequest> RegisteredRequests;` — List of all currently registered requests as registered by external systems
- L230 _private member_ `TMap<FMassEntityHandle, int32> RequestHandleToIndexMap;` — Used for lookup in RegisteredRequests, since that array can get large, and linear search would kill performance rather quickly.
- L233 _private member_ `TArray<int32> ActiveRequestsFreeList;` — List of available indices in ActiveRequests (to preserve stable indices when unregistering requests)
- L239 _private member_ `TArray<FViewerRequest> PerViewerRequests;` — Per viewer entity representation of all the active requests @todo we never remove elements from this array, which means it can end up being HUGE. Needs fixing.
- L242 _private member_ `TMap<FMassEntityHandle, int32> ViewerHandleToIndexMap;` — Used for lookup in PerViewerRequests, since that array can get large, and linear search would kill performance rather quickly.
- L245 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(RequestsAccessDetector);` — Multithread access detector to detect threading issues with any list of requests
- L248 _private member_ `UE::Mass::LookAt::FTargetHashGrid2D TargetGrid;` — Hierarchical 2D hash grid of registered entities representing LookAt targets.
- L251 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(TargetGridAccessDetector);` — Multithread access detector to detect threading issues with the hash grid
- L254 _private member_ `FMassArchetypeHandle TargetArchetype;` — Cached archetype to create entities representing a LookAt target
- L257 _private member_ `FMassArchetypeHandle RequestArchetype;` — Cached archetype to create entities representing a LookAt request

#### struct `UMassLookAtSubsystem::FRequest`  
`struct FRequest`  
_L51-56_
- desc: Struct representing a request for a given entity to perform a LookAt action
- L53 _public member_ `FMassEntityHandle RequestHandle;`
- L54 _public member_ `FMassLookAtRequestFragment Parameters;`
- L55 _public member_ `bool bActive = false;`

#### struct `UMassLookAtSubsystem::FViewerRequest`  
`struct FViewerRequest`  
_L220-224_
- desc: Struct to facilitate processing request per viewer entity.
- L222 _public member_ `FMassEntityHandle Viewer;`
- L223 _public member_ `TArray<int32> RequestIndices;`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassLookAtSubsystem>`  
_L261-268_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L264-267_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L265 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon0599077b0103`)
- L266 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon0599077b0103`) — hash grid not safe

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtTargetTrait.h` (Public)


#### class `UMassLookAtTargetTrait`  
`class UMassLookAtTargetTrait : public UMassEntityTraitBase`  
_L13-30_
- reflection: `UCLASS(meta=(DisplayName="Look At Target"))`
- inherits: `UMassEntityTraitBase`
- L19 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L25 _protected member_ `bool bShouldUseCapsuleComponentToSetTargetOffset = true;` — `UPROPERTY(EditAnywhere, config, Category = LookAt)` — Indicates whether the trait will use an initializer to set target offset using the height of the capsule component if available.
- L29 _protected member_ `FMassLookAtPriority Priority{static_cast<uint8>(EMassLookAtPriorities::LowestPriority)};` — `UPROPERTY(EditAnywhere, config, Category = LookAt)` — Priority assigned to the target to influence target selection

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtTrait.h` (Public)


#### class `UMassLookAtTrait`  
`class UMassLookAtTrait : public UMassEntityTraitBase`  
_L12-19_
- reflection: `UCLASS(meta=(DisplayName="Look At"))`
- inherits: `UMassEntityTraitBase`
- L18 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtTypes.h` (Public)


#### struct `UE::Mass::LookAt::FTargetHashGridItem`  
`struct FTargetHashGridItem`  
_L17-38_
- L19 _public function_ `FTargetHashGridItem(const FMassEntityHandle& TargetEntity, const uint8 Priority) : TargetEntity(TargetEntity) , Priority(Priority)`
- L25 _public function_ `bool operator==(const FTargetHashGridItem& RHS) const`
- L31 _public function_ `bool operator!=(const FTargetHashGridItem& RHS) const`
- L36 _public member_ `FMassEntityHandle TargetEntity;`
- L37 _public member_ `uint8 Priority = MAX_uint8;`

#### enum `EMassLookAtInterpolationSpeed`  
`enum class EMassLookAtInterpolationSpeed : uint8`  
_L47-54_
- reflection: `UENUM(BlueprintType)`
- desc: Enum representing the different interpolation speeds that can be used when assigning new LookAt targets
- L49 _public enumerator_ `Instant`
- L50 _public enumerator_ `Fast`
- L51 _public enumerator_ `Regular`
- L52 _public enumerator_ `Slow`
- L53 _public enumerator_ `Custom`

#### enum `EMassLookAtPriorities`  
`enum class EMassLookAtPriorities : uint8`  
_L60-65_
- reflection: `UENUM()`
- desc: Enum used to define the number of configurable priorities exposed by the MassLookAtSettings
- L62 _public enumerator_ `MaxPriorities = 16`
- L63 _public enumerator_ `MaxPriorityIndex = MaxPriorities - 1`
- L64 _public enumerator_ `LowestPriority = MaxPriorityIndex`

#### struct `FMassLookAtPriority`  
`struct FMassLookAtPriority`  
_L71-119_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used as a priority selector exposed to the Editor
- L75 _public prototype_ `FMassLookAtPriority() = default;`
- L77 _public function_ `explicit FMassLookAtPriority(const uint8 InBit) : Value(InBit)`
- L83 _public function_ `void Set(const uint8 InBit)`
- L89 _public function_ `uint8 Get() const`
- L94 _public function_ `void Reset()`
- L99 _public function_ `bool IsValid() const`
- L104 _public function_ `bool operator==(const FMassLookAtPriority& RHS) const`
- L109 _public function_ `bool operator!=(const FMassLookAtPriority& RHS) const`
- L115 _private member_ `static constexpr uint8 NoneValue = 0xFF;`
- L118 _private member_ `uint8 Value = NoneValue;` — `UPROPERTY(Category = LookAt, EditAnywhere)`

#### struct `FMassLookAtPriorityInfo`  
`struct FMassLookAtPriorityInfo`  
_L125-139_
- reflection: `USTRUCT()`
- desc: Struct used to represent configurable priorities in MassLookAtSettings
- L129 _public function_ `bool IsValid() const`
- L135 _public member_ `FName Name;` — `UPROPERTY(Category = LookAt, EditAnywhere)`
- L138 _public member_ `FMassLookAtPriority Priority;` — `UPROPERTY(Category = LookAt, EditAnywhere)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mass` (scope `UE`)
- L10 _namespace_ `namespace LookAt` (scope `UE::Mass`)
- L12 _variable_ `constexpr float DefaultCustomInterpolationSpeed = 1.5f;` (scope `UE::Mass::LookAt`)
- L13 _variable_ `constexpr int32 HashGridLevelsOfHierarchy = 2;` (scope `UE::Mass::LookAt`)
- L14 _variable_ `constexpr int32 HashGridRatioBetweenLevels = 4;` (scope `UE::Mass::LookAt`)
- L15 _variable_ `constexpr int32 HashGridResultsSoftLimit = 16;` (scope `UE::Mass::LookAt`)
- L40 _typedef_ `using FTargetHashGrid2D = THierarchicalHashGrid2D<HashGridLevelsOfHierarchy, HashGridRatioBetweenLevels, FTargetHashGridItem>;` (scope `UE::Mass::LookAt`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeDependency.h` (Public)


#### struct `FMassStateTreeDependency`  
`struct FMassStateTreeDependency`  
_L12-27_
- reflection: `USTRUCT()`
- desc: A dependency the state tree has on other fragment or system used by mass.
- L16 _public prototype_ `FMassStateTreeDependency() = default;`
- L17 _public function_ `FMassStateTreeDependency(TNotNull<const UStruct*> InType, EMassFragmentAccess InAccess) : Type(InType) , Access(InAccess)`
- L23 _public member_ `TObjectPtr<const UStruct> Type;` — `UPROPERTY()`
- L26 _public member_ `EMassFragmentAccess Access = EMassFragmentAccess::None;` — `UPROPERTY()`

#### struct `UE::MassBehavior::FStateTreeDependencyBuilder`  
`struct FStateTreeDependencyBuilder`  
_L43-131_
- desc: FStateTreeDependencyBuilder is a utility struct to build a list of dependencies used by the state tree. The add dependency can be chain for ease of use. Example Usage: { FStateTreeDependencyBuilder Builder() .AddReadOnly<FTransformFragment>() .AddReadWrite(ComponentHitSubsystemHandle); Builder.AddReadOnly<FMassZoneGraphAnnotationFragment>(); }
- L53 _public prototype_ `FStateTreeDependencyBuilder(TArray<FMassStateTreeDependency>& Dependencies);`
- L57 _public function_ `template<typename T> FStateTreeDependencyBuilder& AddReadOnly() requires TIsDerivedFrom<T, UObject>::IsDerived` — Add a read only dependency.
- L65 _public function_ `template<UE::Mass::CNonTag T> FStateTreeDependencyBuilder& AddReadOnly()` — Add a read only dependency.
- L73 _public function_ `template<typename T> FStateTreeDependencyBuilder& AddReadOnly(const T& ) requires TIsDerivedFrom<typename T::DataType, UObject>::IsDerived` — Add a read only dependency from a handle.
- L81 _public function_ `template<typename T> FStateTreeDependencyBuilder& AddReadOnly(const T& ) requires UE::Mass::CNonTag<typename T::DataType>` — Add a read only dependency from a handle.
- L89 _public function_ `template<typename T> FStateTreeDependencyBuilder& AddReadWrite() requires TIsDerivedFrom<T, UObject>::IsDerived` — Add a read write dependency.
- L97 _public function_ `template<UE::Mass::CNonTag T> FStateTreeDependencyBuilder& AddReadWrite()` — Add a read write dependency.
- L105 _public function_ `template<typename T> FStateTreeDependencyBuilder& AddReadWrite(const T& ) requires TIsDerivedFrom<typename T::DataType, UObject>::IsDerived` — Add a read write dependency from a handle.
- L113 _public function_ `template<typename T> FStateTreeDependencyBuilder& AddReadWrite(const T& ) requires UE::Mass::CNonTag<typename T::DataType>` — Add a read write dependency from a handle.
- L120 _public prototype_ `void Add(TNotNull<const UStruct*> Struct, EAccessType Access);` — Add a dependency for a specific type.
- L123 _public function_ `const TConstArrayView<FMassStateTreeDependency> GetDependencies() const` — @return the list of dependencies.
- L130 _private member_ `TArray<FMassStateTreeDependency>& Dependencies;` — The list of dependencies.

#### enum `UE::MassBehavior::FStateTreeDependencyBuilder::EAccessType`  
`enum class EAccessType : uint8`  
_L46-50_
- L48 _public enumerator_ `ReadOnly = (uint8)EMassFragmentAccess::ReadOnly`
- L49 _public enumerator_ `ReadWrite = (uint8)EMassFragmentAccess::ReadWrite`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeExecutionContext.h` (Public)


#### struct `FMassExecutionExtension`  
`struct FMassExecutionExtension : public FStateTreeExecutionExtension`  
_L19-29_
- reflection: `USTRUCT()`
- inherits: `FStateTreeExecutionExtension`
- L24 _public prototype_ `virtual FString GetInstanceDescription(const FContextParameters& Context) const override;`
- L25 _public prototype_ `virtual void OnLinkedStateTreeOverridesSet(const FContextParameters& Context, const FStateTreeReferenceOverrides& Overrides) override;`
- L27 _public member_ `FMassEntityHandle Entity;`
- L28 _public member_ `uint32 LinkedStateTreeOverridesHash = 0;`

#### struct `FMassStateTreeExecutionContext`  
`struct FMassStateTreeExecutionContext : public FStateTreeExecutionContext`  
_L34-77_
- inherits: `FStateTreeExecutionContext`
- desc: Extends FStateTreeExecutionContext to provide additional data to Evaluators and Tasks related to MassSimulation
- L36 _public prototype_ `FMassStateTreeExecutionContext(UObject& InOwner , const UStateTree& InStateTree , FStateTreeInstanceData& InInstanceData , FMassExecutionContext& InContext);`
- L42 _public function_ `FMassStateTreeExecutionContext(UObject& InOwner , const UStateTree& InStateTree , FStateTreeInstanceData& InInstanceData , FMassEntityManager& InEntityManager , UMassSignalSubsystem& InSignalSubsystem , FMassExecutionContext& InContext) : FMassStateTreeExecutionContext(InOwner, InStateTree, InInstanceData, InContext)` — `UE_DEPRECATED(5.6, "Use the other constructor that doesn't require MassEntityManager and MassSignalSubSystem")`
- L53 _public prototype_ `EStateTreeRunStatus Start();` — Start executing.
- L54 _public prototype_ `EStateTreeRunStatus Start(const FInstancedPropertyBag* InitialParameters, int32 RandomSeed = -1);`
- L56 _public function_ `FMassEntityManager& GetEntityManager() const`
- L61 _public function_ `FMassExecutionContext& GetMassEntityExecutionContext() const`
- L66 _public function_ `FMassEntityHandle GetEntity() const`
- L71 _public prototype_ `void SetEntity(const FMassEntityHandle InEntity);`
- L74 _protected prototype_ `virtual void BeginDelayedTransition(const FStateTreeTransitionDelayedState& DelayedState) override;`
- L75 _protected member_ `FMassExecutionContext* MassEntityExecutionContext = nullptr;`
- L76 _protected member_ `FMassEntityHandle Entity;`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeFragments.h` (Public)


#### struct `FMassStateTreeInstanceFragment`  
`struct FMassStateTreeInstanceFragment : public FMassFragment`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L15 _public prototype_ `FMassStateTreeInstanceFragment() = default;`
- L18 _public member_ `FMassStateTreeInstanceHandle InstanceHandle;` — Handle to a StateTree instance data in MassStateTreeSubsystem.
- L21 _public member_ `double LastUpdateTimeInSeconds = 0.;` — The last update time use to calculate ticking delta time.

#### struct `FMassStateTreeSharedFragment`  
`struct FMassStateTreeSharedFragment : public FMassConstSharedFragment`  
_L26-34_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L30 _public prototype_ `FMassStateTreeSharedFragment() = default;`
- L33 _public member_ `TObjectPtr<UStateTree> StateTree = nullptr;` — `UPROPERTY()`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeProcessors.h` (Public)


#### class `UMassStateTreeFragmentDestructor`  
`class UMassStateTreeFragmentDestructor : public UMassObserverProcessor`  
_L25-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Processor to stop and uninitialize StateTrees on entities.
- L30 _public prototype_ `UMassStateTreeFragmentDestructor();`
- L33 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L34 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L35 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L37 _protected member_ `FMassEntityQuery EntityQuery;`
- L40 _protected member_ `TObjectPtr<UMassSignalSubsystem> SignalSubsystem = nullptr;` — `UPROPERTY(Transient)`

#### struct `FMassStateTreeActivatedTag`  
`struct FMassStateTreeActivatedTag : public FMassTag`  
_L47-50_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Special tag to know if the state tree has been activated

#### class `UMassStateTreeActivationProcessor`  
`class UMassStateTreeActivationProcessor : public UMassProcessor`  
_L54-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor to send the activation signal to the state tree which will execute the first tick
- L58 _public prototype_ `UMassStateTreeActivationProcessor();`
- L60 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L61 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L63 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassStateTreeProcessor`  
`class UMassStateTreeProcessor : public UMassSignalProcessorBase`  
_L72-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSignalProcessorBase`
- desc: The processor that the UMassStateTreeSubsystem will instantiate for every unique StateTree Mass-requirements. The user is not expected to instantiate these processors manually, but a project-specific extension can be implemented. It needs to derive from UMassStateTreeProcessor and set as the value of UMassStateTreeSubsystem.DynamicProcessorClass.
- L77 _public prototype_ `UMassStateTreeProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L84 _public prototype_ `void SetExecutionRequirements(const FMassFragmentRequirements& FragmentRequirements, const FMassSubsystemRequirements& SubsystemRequirements);` — Called to configure dynamic processor's additional requirements that will ensure its located properly within Mass's processing graph. Calling this function is allowed only until the processor is Initialized. The function will ensure that's the case.
- L89 _public prototype_ `void AddHandledStateTree(TNotNull<const UStateTree*> StateTree);` — Adds StateTree to the collection of the assets this specific processor instance will handle.
- L92 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L93 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L94 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;`
- L96 _protected prototype_ `virtual void ExportRequirements(FMassExecutionRequirements& OutRequirements) const override;`
- L103 _protected member_ `FMassExecutionRequirements ExecutionRequirements;` — Stores the additional requirements as configured by SetExecutionRequirements. These requirements ensure the processor will be placed at the right location in the processing graph to avoid data races.
- L107 _protected member_ `TArray<TObjectPtr<const UStateTree>> HandledStateTrees;` — `UPROPERTY()` — The assets handled by this processor - entities utilizing any of these assets will be processed by this processor
- L111 _protected member_ `bool bProcessEntitiesInParallel = false;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Configures whether parallel update for FMassArchetypeChunks should be used instead of the default single threaded update (i.e., ParallelForEachEntityChunk instead of ForEachEntityChunk).

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeSchema.h` (Public)


#### class `UMassStateTreeSchema`  
`class UMassStateTreeSchema : public UStateTreeSchema`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Mass Behavior", CommonSchema))`
- inherits: `UStateTreeSchema`
- desc: StateTree for Mass behaviors.
- L21 _public prototype_ `const TArray<FMassStateTreeDependency>& GetDependencies() const;` — Fetches a read-only view of the Mass-relevant requirements of the associated StateTee
- L24 _public function_ `virtual bool AllowQueuedCompilation() const override`
- L32 _protected prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L33 _protected prototype_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;`
- L34 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L43 _protected member_ `TArray<FMassStateTreeDependency> Dependencies;` — `UPROPERTY(Transient)` — The Mass-relevant requirements of the associated StateTee, collected during StateTree's linking @see UStateTree::Link @see UMassStateTreeSchema::Link
- L49 _function_ `inline const TArray<FMassStateTreeDependency>& UMassStateTreeSchema::GetDependencies() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeSubsystem.h` (Public)


#### struct `FMassStateTreeInstanceDataItem`  
`struct FMassStateTreeInstanceDataItem`  
_L28-37_
- reflection: `USTRUCT()`
- L33 _public member_ `FStateTreeInstanceData InstanceData;` — `UPROPERTY()`
- L36 _public member_ `int32 Generation = 0;` — `UPROPERTY()`

#### class `UMassStateTreeSubsystem`  
`class UMassStateTreeSubsystem : public UMassSubsystemBase`  
_L43-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: A subsystem managing StateTree assets in Mass
- L49 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L58 _public prototype_ `FMassStateTreeInstanceHandle AllocateInstanceData(const UStateTree* StateTree);` — Allocates new instance data for specified StateTree. @param StateTree StateTree to allocated the data for. @return Handle to the data.
- L64 _public prototype_ `void FreeInstanceData(const FMassStateTreeInstanceHandle Handle);` — Frees instance data. @param Handle Instance data handle to free.
- L67 _public function_ `FStateTreeInstanceData* GetInstanceData(const FMassStateTreeInstanceHandle Handle)` — @return Pointer to instance data held by the handle, or nullptr if handle is not valid.
- L74 _public function_ `bool IsValidHandle(const FMassStateTreeInstanceHandle Handle) const` — @return True if the handle points to active instance data.
- L86 _protected prototype_ `void CreateProcessorForStateTree(TNotNull<const UStateTree*> StateTree);` — Gathers Mass-relevant processing requirements from StateTree and spawns a dynamic processor to handle entities using this given asset
- L88 _protected member_ `TArray<int32> InstanceDataFreelist;`
- L91 _protected member_ `TArray<FMassStateTreeInstanceDataItem> InstanceDataArray;` — `UPROPERTY(Transient)`
- L99 _protected prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(InstanceDataMTDetector);` — Multithread access detector to prevent attempts to allocate new instance data from multiple threads, which is not supported by the current implementation. @see AllocateInstanceData, FreeInstanceData, CreateProcessorForStateTree @todo Instance data creation needs to be refactored in order to allow parallelization of StateTree activations
- L114 _protected member_ `TMap<uint32, TObjectPtr<UMassStateTreeProcessor>> RequirementsHashToProcessor;` — `UPROPERTY()` — The key represents a hash of mass requirements calculated from a StateTree assets. Using the hash rather than a StateTree asset pointer since multiple assets can have identical requirements, and we want just one dynamic processor to handle all of them. @note that might change if in practice it turns out that runtime entity chunk filtering turns out to be too expensive when multiple ST assets are used.
- L120 _protected member_ `TMap<TObjectKey<UStateTree>, TObjectPtr<UMassStateTreeProcessor>> StateTreeToProcessor;` — Mapping StateTree assets to the dynamic processors handling them. Note that it's not 1:1, a single processor can handle multiple assets.
- L124 _protected member_ `TObjectPtr<UMassSimulationSubsystem> SimulationSubsystem;` — `UPROPERTY()` — Cached SimulationSubsystem for registering dynamic processors.
- L131 _protected member_ `TSubclassOf<UMassStateTreeProcessor> DynamicProcessorClass;` — `UPROPERTY(Transient)` — Class to use when creating dynamic processors to handle given StateTree assets. Set based on UMassBehaviorSettings.DynamicStateTreeProcessorClass

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Mass` (scope `UE`)
- L22 _namespace_ `namespace StateTree` (scope `UE::Mass`)
- L24 _externvar_ `extern bool bDynamicSTProcessorsEnabled;` (scope `UE::Mass::StateTree`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeTrait.h` (Public)


#### class `UMassStateTreeTrait`  
`class UMassStateTreeTrait : public UMassEntityTraitBase`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="StateTree"))`
- inherits: `UMassEntityTraitBase`
- desc: Feature that adds StateTree execution functionality to a mass agent.
- L22 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L23 _protected prototype_ `virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const override;`
- L26 _protected member_ `TObjectPtr<UStateTree> StateTree;` — `UPROPERTY(Category="StateTree", EditAnywhere, meta=(RequiredAssetDataTags="Schema=/Script/MassAIBehavior.MassStateTreeSchema"))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassStateTreeTypes.h` (Public)


#### struct `FMassStateTreeEvaluatorBase`  
`struct FMassStateTreeEvaluatorBase : public FStateTreeEvaluatorBase`  
_L46-57_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Mass Evaluator Base"))`
- inherits: `FStateTreeEvaluatorBase`
- desc: Base struct for all Mass StateTree Evaluators.
- L54 _public function_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const` — Appends this evaluator's Mass dependencies to the given Builder. This is done once for every evaluator instance, when the state tree asset is loaded or compiled.

#### struct `FMassStateTreeTaskBase`  
`struct FMassStateTreeTaskBase : public FStateTreeTaskBase`  
_L63-74_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Mass Task Base"))`
- inherits: `FStateTreeTaskBase`
- desc: Base struct for all Mass StateTree Tasks.
- L71 _public function_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const` — Appends this task's Mass dependencies to the given Builder. This is done once for every task instance, when the state tree asset is loaded or compiled.

#### struct `FMassStateTreeConditionBase`  
`struct FMassStateTreeConditionBase : public FStateTreeConditionBase`  
_L80-91_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Mass Condition Base"))`
- inherits: `FStateTreeConditionBase`
- desc: Base struct for all Mass StateTree Conditions.
- L88 _public function_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const` — Appends this condition's Mass dependencies to the given Builder. This is done once for every condition instance, when the state tree asset is loaded or compiled.

#### struct `FMassStateTreePropertyFunctionBase`  
`struct FMassStateTreePropertyFunctionBase : public FStateTreePropertyFunctionBase`  
_L97-108_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Mass Property Function Base"))`
- inherits: `FStateTreePropertyFunctionBase`
- desc: Base struct for all Mass StateTree Property Functions.
- L105 _public function_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const` — Appends this property function's Mass dependencies to the given Builder. This is done once for every property function instance, when the state tree asset is loaded or compiled.

#### struct `FMassStateTreeInstanceHandle`  
`struct FMassStateTreeInstanceHandle`  
_L113-134_
- desc: A handle pointing to a StateTree instance data in UMassStateTreeSubsystem.
- L115 _public prototype_ `FMassStateTreeInstanceHandle() = default;`
- L118 _public function_ `static FMassStateTreeInstanceHandle Make(const int32 InIndex, const int32 InGeneration)` — Initializes new handle based on an index
- L121 _public function_ `int32 GetIndex() const` — @returns index the handle points to
- L124 _public function_ `int32 GetGeneration() const` — @returns generation of the handle, used to identify recycled indices.
- L127 _public function_ `bool IsValid() const` — @returns true if the handle is valid.
- L130 _protected function_ `FMassStateTreeInstanceHandle(const int32 InIndex, const int32 InGeneration) : Index(InIndex), Generation(InGeneration)`
- L132 _protected member_ `int32 Index = INDEX_NONE;`
- L133 _protected member_ `int32 Generation = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MassBehavior` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MassStateTree` (scope `UE`)
- L24 _variable_ `static constexpr EProcessorExecutionFlags ExecutionFlags(EProcessorExecutionFlags::Standalone | EProcessorExecutionFlags::Server);` (scope `UE::MassStateTree`) — Flags to indicates to the MassStateTree processors and traits in which contexts they can execute (e.g., Standalone, Server, etc.)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Mass` (scope `UE`)
- L30 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L32 _variable_ `const FName StateTreeActivate = FName(TEXT("Stat` (scope `UE::Mass::Signals`)
- L33 _variable_ `const FName LookAtFinished = FName(TEXT("Look` (scope `UE::Mass::Signals`)
- L34 _variable_ `const FName NewStateTreeTaskRequired = FName(TEXT("NewS` (scope `UE::Mass::Signals`)
- L35 _variable_ `const FName StandTaskFinished = FName(TEXT("Stan` (scope `UE::Mass::Signals`)
- L36 _variable_ `const FName AnimateTaskFinished = FName(TEXT("Anim` (scope `UE::Mass::Signals`)
- L37 _variable_ `const FName DelayedTransitionWakeup = FName(TEXT("Dela` (scope `UE::Mass::Signals`)
- L39 _variable_ `const FName ContextualAnimTaskFinished = FName(TEXT("Cont` (scope `UE::Mass::Signals`) — @todo MassStateTree: move this to its game plugin when possible

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassZoneGraphAnnotationFragments.h` (Public)


#### struct `FMassZoneGraphAnnotationFragment`  
`struct FMassZoneGraphAnnotationFragment : public FMassFragment`  
_L12-19_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L18 _public member_ `FZoneGraphTagMask Tags;` — `UPROPERTY()` — Behavior tags for current lane

#### struct `FMassZoneGraphAnnotationVariableTickChunkFragment`  
`struct FMassZoneGraphAnnotationVariableTickChunkFragment : public FMassChunkFragment`  
_L22-31_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L27 _public prototype_ `static bool UpdateChunk(FMassExecutionContext& Context);` — Update the ticking frequency of the chunk and return if this chunk should be process this frame
- L29 _public member_ `float TimeUntilNextTick = 0.0f;`
- L30 _public member_ `bool bInitialized = false;`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassZoneGraphAnnotationProcessors.h` (Public)


#### class `UMassZoneGraphAnnotationTagsInitializer`  
`class UMassZoneGraphAnnotationTagsInitializer : public UMassObserverProcessor`  
_L21-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Processor for initializing ZoneGraph annotation tags.
- L26 _public prototype_ `UMassZoneGraphAnnotationTagsInitializer();`
- L29 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L30 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L32 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassZoneGraphAnnotationTagUpdateProcessor`  
`class UMassZoneGraphAnnotationTagUpdateProcessor : public UMassSignalProcessorBase`  
_L39-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSignalProcessorBase`
- desc: Processor for update ZoneGraph annotation tags periodically and on lane changed signal.
- L44 _public prototype_ `UMassZoneGraphAnnotationTagUpdateProcessor();`
- L47 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L48 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L49 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L51 _protected prototype_ `void UpdateAnnotationTags(UZoneGraphAnnotationSubsystem& ZoneGraphAnnotationSubsystem, FMassZoneGraphAnnotationFragment& AnnotationTags, const FMassZoneGraphLaneLocationFragment& LaneLocation, FMassEntityHandle Entity);`
- L53 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& ) override;`
- L56 _protected member_ `TArray<FMassEntityHandle> TransientEntitiesToSignal;` — Frame buffer, it gets reset every frame.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassZoneGraphAnnotationTrait.h` (Public)


#### class `UMassZoneGraphAnnotationTrait`  
`class UMassZoneGraphAnnotationTrait : public UMassEntityTraitBase`  
_L11-17_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "ZoneGraph Annotation"))`
- inherits: `UMassEntityTraitBase`
- L16 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassZoneGraphAnnotationTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mass` (scope `UE`)
- L7 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L9 _variable_ `const FName AnnotationTagsChanged = FName(TEXT("Anno` (scope `UE::Mass::Signals`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassClaimSmartObjectTask.h` (Public)


#### struct `FMassClaimSmartObjectTaskInstanceData`  
`struct FMassClaimSmartObjectTaskInstanceData`  
_L32-45_
- reflection: `USTRUCT()`
- desc: Tasks to claim a smart object from search results and release it when done.
- L38 _public member_ `FStateTreePropertyRef CandidateSlots;` — `UPROPERTY(VisibleAnywhere, Category = Input, meta = (RefType = "/Script/MassSmartObjects.MassSmartObjectCandidateSlots"))` — Result of the candidates search request (Input)
- L41 _public member_ `FSmartObjectClaimHandle ClaimedSlot;` — `UPROPERTY(VisibleAnywhere, Category = Output)`
- L44 _public member_ `FTransform ClaimedSlotTransform;` — `UPROPERTY(VisibleAnywhere, Category = Output)`

#### struct `FMassClaimSmartObjectTask`  
`struct FMassClaimSmartObjectTask : public FMassStateTreeTaskBase`  
_L48-72_
- reflection: `USTRUCT(meta = (DisplayName = "Claim SmartObject"))`
- inherits: `FMassStateTreeTaskBase`
- L52 _public typedef_ `using FInstanceDataType = FMassClaimSmartObjectTaskInstanceData;`
- L54 _public prototype_ `FMassClaimSmartObjectTask();`
- L57 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L58 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L59 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L60 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L61 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L62 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L64 _protected member_ `TStateTreeExternalDataHandle<FMassSmartObjectUserFragment> SmartObjectUserHandle;`
- L65 _protected member_ `TStateTreeExternalDataHandle<UE::Mass::SmartObject::FMRUSlotsFragment, EStateTreeExternalDataRequirement::Optional> SmartObjectMRUSlotsHandle;`
- L66 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;`
- L67 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`
- L71 _protected member_ `float InteractionCooldown = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Delay in seconds before trying to use another smart object

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MassBehavior` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Mass` (scope `UE`)
- L23 _namespace_ `namespace SmartObject` (scope `UE::Mass`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassFindSmartObjectTargetTask.h` (Public)


#### struct `FMassFindSmartObjectTargetInstanceData`  
`struct FMassFindSmartObjectTargetInstanceData`  
_L19-40_
- reflection: `USTRUCT()`
- L29 _public member_ `bool bUseEntityLocationAsSearchLocation = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — When using the entrance location request with selection method 'NearestToSearchLocation', this property indicates whether the request will set the search location using the entity transform or use the request value (can be bound).
- L33 _public member_ `FSmartObjectSlotEntranceLocationRequest EntranceRequest;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Request parameters when using the entrance location request
- L36 _public member_ `FSmartObjectClaimHandle ClaimedSlot;` — `UPROPERTY(VisibleAnywhere, Category = Input)`
- L39 _public member_ `FMassTargetLocation SmartObjectLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMassFindSmartObjectTargetTask`  
`struct FMassFindSmartObjectTargetTask : public FMassStateTreeTaskBase`  
_L48-73_
- reflection: `USTRUCT(meta = (DisplayName = "Find Smart Object Target"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Computes move target to a smart object based on current location. The move target will use the entrance location found by the EntranceRequest if possible, otherwise the slot location will be used.
- L52 _public typedef_ `using FInstanceDataType = FMassFindSmartObjectTargetInstanceData;`
- L55 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L56 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L60 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L62 _protected member_ `TStateTreeExternalDataHandle<FAgentRadiusFragment, EStateTreeExternalDataRequirement::Optional> AgentRadiusHandle;`
- L63 _protected member_ `TStateTreeExternalDataHandle<FAgentHeightFragment, EStateTreeExternalDataRequirement::Optional> AgentHeightHandle;`
- L64 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`
- L65 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;`
- L72 _protected member_ `bool bUseEntranceLocationRequest = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Whether the entrance location request should be used first to find an entrance location to use instead of the slot location. Slot location will be used if not entrances can be found.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassFindSmartObjectTask.h` (Public)


#### struct `FMassFindSmartObjectTaskInstanceData`  
`struct FMassFindSmartObjectTaskInstanceData`  
_L27-49_
- reflection: `USTRUCT()`
- L33 _public member_ `FMassSmartObjectCandidateSlots FoundCandidateSlots;` — `UPROPERTY(VisibleAnywhere, Category = Output)` — Result of the candidates search request
- L36 _public member_ `bool bHasCandidateSlots = false;` — `UPROPERTY(VisibleAnywhere, Category = Output)`
- L40 _public member_ `FMassSmartObjectRequestID SearchRequestID;` — `UPROPERTY()` — The identifier of the search request send by the task to find candidates
- L44 _public member_ `double NextUpdate = 0.;` — `UPROPERTY()` — Next update time; task will not do anything when Tick gets called before that time
- L48 _public member_ `FZoneGraphLaneHandle LastLane;` — `UPROPERTY()` — Last lane where the smart objects were searched.

#### struct `FMassFindSmartObjectTask`  
`struct FMassFindSmartObjectTask : public FMassStateTreeTaskBase`  
_L52-86_
- reflection: `USTRUCT(meta = (DisplayName = "Find Smart Object"))`
- inherits: `FMassStateTreeTaskBase`
- L56 _public typedef_ `using FInstanceDataType = FMassFindSmartObjectTaskInstanceData;`
- L58 _public prototype_ `FMassFindSmartObjectTask();`
- L61 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L62 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L63 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L64 _protected prototype_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates) const override;`
- L65 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L66 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L68 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;`
- L69 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`
- L70 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> EntityTransformHandle;`
- L71 _protected member_ `TStateTreeExternalDataHandle<FMassSmartObjectUserFragment> SmartObjectUserHandle;`
- L72 _protected member_ `TStateTreeExternalDataHandle<UE::Mass::SmartObject::FMRUSlotsFragment, EStateTreeExternalDataRequirement::Optional> SmartObjectMRUSlotsHandle;`
- L73 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment, EStateTreeExternalDataRequirement::Optional> LocationHandle;`
- L77 _protected member_ `FGameplayTagQuery ActivityRequirements;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Gameplay tag query for finding matching smart objects.
- L81 _protected member_ `float SearchInterval = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — How frequently to search for new candidates.
- L85 _protected member_ `bool bFindFromLaneLocation = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If true, search smart objects using current lane position else, use world position.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MassBehavior` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mass` (scope `UE`)
- L21 _namespace_ `namespace SmartObject` (scope `UE::Mass`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassLookAtTask.h` (Public)


#### struct `FMassLookAtTaskInstanceData`  
`struct FMassLookAtTaskInstanceData`  
_L22-37_
- reflection: `USTRUCT()`
- desc: Task to assign a LookAt target for mass processing
- L28 _public member_ `FMassEntityHandle TargetEntity;` — `UPROPERTY(EditAnywhere, Category = Input, meta = (Optional))` — Entity to set as the target for the LookAt behavior.
- L32 _public member_ `float Duration = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Delay before the task ends. Default (0 or any negative) will run indefinitely so it requires a transition in the state tree to stop it.
- L36 _public member_ `float Time = 0.f;` — `UPROPERTY()` — Accumulated time used to stop task if duration is set

#### struct `FMassLookAtTask`  
`struct FMassLookAtTask : public FMassStateTreeTaskBase`  
_L40-97_
- reflection: `USTRUCT(meta = (DisplayName = "Mass LookAt Task"))`
- inherits: `FMassStateTreeTaskBase`
- L44 _public typedef_ `using FInstanceDataType = FMassLookAtTaskInstanceData;`
- L47 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L48 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L53 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L54 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L55 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L56 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L58 _protected prototype_ `bool TryActivateSystemicLookAt(const FStateTreeExecutionContext& Context, const FInstanceDataType& InstanceData, FMassLookAtFragment& Fragment) const;`
- L60 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`
- L61 _protected member_ `TStateTreeExternalDataHandle<FMassLookAtFragment, EStateTreeExternalDataRequirement::Optional> LookAtHandle;`
- L65 _protected member_ `FMassLookAtPriority Priority{static_cast<uint8>(EMassLookAtPriorities::LowestPriority)};` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Look At Priority
- L69 _protected member_ `EMassLookAtMode LookAtMode = EMassLookAtMode::LookForward;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Look At Mode
- L73 _protected member_ `EMassLookAtInterpolationSpeed InterpolationSpeed = EMassLookAtInterpolationSpeed::Regular;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Look at interpolation speed (not used by the LookAt processor but can be forwarded to the animation system).
- L80 _protected member_ `float CustomInterpolationSpeed = UE::Mass::LookAt::DefaultCustomInterpolationSpeed;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (EditCondition="InterpolationSpeed == EMassLookAtInterpolationSpeed::Custom", EditConditionHides))` — Look at custom interpolation speed used when 'InterpolationSpeed = EMassLookAtInterpolationSpeed::Custom' (not used by the LookAt processor but can be forwarded to the animation system).
- L84 _protected member_ `EMassLookAtGazeMode RandomGazeMode = EMassLookAtGazeMode::None;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Random gaze Mode
- L88 _protected member_ `uint8 RandomGazeYawVariation = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 180.0, ClampMax = 180.0))` — Random gaze yaw angle added to the look direction determined by the look at mode.
- L92 _protected member_ `uint8 RandomGazePitchVariation = 0;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 180.0, ClampMax = 180.0))` — Random gaze pitch angle added to the look direction determined by the look at mode.
- L96 _protected member_ `bool bRandomGazeEntities = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If true, allow random gaze to look at other entities too.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassNavMeshAnimateTask.h` (Public)


#### struct `FMassNavMeshAnimateTaskInstanceData`  
`struct FMassNavMeshAnimateTaskInstanceData`  
_L16-26_
- reflection: `USTRUCT()`
- L22 _public member_ `float Duration = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Delay before the task ends. Default (0 or any negative) will run indefinitely, so it requires a transition in the state tree to stop it.
- L25 _public member_ `float Time = 0.f;` — `UPROPERTY()`

#### struct `FMassNavMeshAnimateTask`  
`struct FMassNavMeshAnimateTask : public FMassStateTreeTaskBase`  
_L32-52_
- reflection: `USTRUCT(meta = (DisplayName = "NavMesh Animate"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Stop and animate on current navmesh location
- L36 _public typedef_ `using FInstanceDataType = FMassNavMeshAnimateTaskInstanceData;`
- L39 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L41 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L46 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L47 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L49 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`
- L50 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`
- L51 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassNavMeshFindReachablePointTask.h` (Public)


#### struct `FMassNavMeshFindReachablePointTaskInstanceData`  
`struct FMassNavMeshFindReachablePointTaskInstanceData`  
_L19-29_
- reflection: `USTRUCT()`
- L25 _public member_ `float SearchRadius = 500.f;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Radius around the current entity's location to finds a random reachable location
- L28 _public member_ `FMassTargetLocation TargetLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMassNavMeshFindReachablePointTask`  
`struct FMassNavMeshFindReachablePointTask : public FMassStateTreeTaskBase`  
_L35-52_
- reflection: `USTRUCT(meta = (DisplayName = "NavMesh Find Random Reachable Target"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Updates TargetLocation to a random reachable location based on the agents current location on NavMesh.
- L39 _public typedef_ `using FInstanceDataType = FMassNavMeshFindReachablePointTaskInstanceData;`
- L42 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L43 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L47 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L49 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`
- L50 _protected member_ `TStateTreeExternalDataHandle<FAgentRadiusFragment> AgentRadiusHandle;`
- L51 _protected member_ `TStateTreeExternalDataHandle<FAgentHeightFragment> AgentHeightHandle;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassNavMeshPathfollowTask.h` (Public)


#### struct `FMassNavMeshPathFollowTaskInstanceData`  
`struct FMassNavMeshPathFollowTaskInstanceData`  
_L23-52_
- reflection: `USTRUCT()`
- desc: FMassNavMeshPathFollowTask movement parameters
- L28 _public member_ `FMassTargetLocation TargetLocation;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L31 _public member_ `FMassMovementStyleRef MovementStyle;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L34 _public member_ `float SpeedScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L38 _public member_ `float CorridorWidth = 600.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Maximum width of the corridor to use.
- L42 _public member_ `float OffsetFromBoundaries = 10.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Amount to offset corridor sides from navmesh borders. Used to keep movement away for navmesh borders.
- L47 _public member_ `float OffsetCornersFromBoundaries = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (ClampMin = "0.0"))` — Offset applied at path corners that touch corridor walls. Unlike OffsetFromBoundaries (global string-pull bias), this only pushes corner points inward along their portal.
- L51 _public member_ `float EndDistanceThreshold = 20.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Distance from the end of path used to confirm that the destination is reached.

#### struct `FMassNavMeshPathFollowTask`  
`struct FMassNavMeshPathFollowTask : public FMassStateTreeTaskBase`  
_L56-81_
- reflection: `USTRUCT(meta = (DisplayName = "NavMesh Path Follow"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Finds a path to TargetLocation, requests a short path, starts a move action and follow the path by updating the short path when needed.
- L61 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L62 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L64 _protected prototype_ `bool RequestPath(FStateTreeExecutionContext& Context, const FMassTargetLocation& InTargetLocation) const;`
- L65 _protected prototype_ `bool UpdateShortPath(FStateTreeExecutionContext& Context) const;`
- L67 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L68 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L70 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`
- L71 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`
- L72 _protected member_ `TStateTreeExternalDataHandle<FAgentRadiusFragment> AgentRadiusHandle;`
- L73 _protected member_ `TStateTreeExternalDataHandle<FAgentHeightFragment> AgentHeightHandle;`
- L74 _protected member_ `TStateTreeExternalDataHandle<FMassDesiredMovementFragment> DesiredMovementHandle;`
- L75 _protected member_ `TStateTreeExternalDataHandle<FMassMovementParameters> MovementParamsHandle;`
- L78 _protected member_ `TStateTreeExternalDataHandle<FMassNavMeshShortPathFragment> ShortPathHandle;` — Hold a small part of a navmesh path
- L80 _protected member_ `TStateTreeExternalDataHandle<FMassNavMeshCachedPathFragment> CachedPathHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassNavMeshStandTask.h` (Public)


#### struct `FMassNavMeshStandTaskInstanceData`  
`struct FMassNavMeshStandTaskInstanceData`  
_L19-29_
- reflection: `USTRUCT()`
- L25 _public member_ `float Duration = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Delay before the task ends. Default (0 or any negative) will run indefinitely, so it requires a transition in the state tree to stop it.
- L28 _public member_ `float Time = 0.f;` — `UPROPERTY()`

#### struct `FMassNavMeshStandTask`  
`struct FMassNavMeshStandTask : public FMassStateTreeTaskBase`  
_L35-57_
- reflection: `USTRUCT(meta = (DisplayName = "NavMesh Stand"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Stop, and stand on current navmesh location
- L39 _public typedef_ `using FInstanceDataType = FMassNavMeshStandTaskInstanceData;`
- L42 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L44 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L49 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L50 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L52 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`
- L53 _protected member_ `TStateTreeExternalDataHandle<FMassNavMeshShortPathFragment> ShortPathHandle;`
- L54 _protected member_ `TStateTreeExternalDataHandle<FMassMovementParameters> MovementParamsHandle;`
- L55 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`
- L56 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSAIBEHAVIOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassUseSmartObjectTask.h` (Public)


#### struct `FMassUseSmartObjectTaskInstanceData`  
`struct FMassUseSmartObjectTaskInstanceData`  
_L27-33_
- reflection: `USTRUCT()`
- desc: Task to tell an entity to start using a claimed smart object.
- L32 _public member_ `FSmartObjectClaimHandle ClaimedSlot;` — `UPROPERTY(VisibleAnywhere, Category = Input)`

#### struct `FMassUseSmartObjectTask`  
`struct FMassUseSmartObjectTask : public FMassStateTreeTaskBase`  
_L36-57_
- reflection: `USTRUCT(meta = (DisplayName = "Mass Use SmartObject Task"))`
- inherits: `FMassStateTreeTaskBase`
- L40 _public typedef_ `using FInstanceDataType = FMassUseSmartObjectTaskInstanceData;`
- L42 _public prototype_ `FMassUseSmartObjectTask();`
- L45 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L46 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L47 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L48 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L49 _protected prototype_ `virtual void StateCompleted(FStateTreeExecutionContext& Context, const EStateTreeRunStatus CompletionStatus, const FStateTreeActiveStates& CompletedActiveStates) const override;`
- L50 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L51 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L53 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;`
- L54 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`
- L55 _protected member_ `TStateTreeExternalDataHandle<FMassSmartObjectUserFragment> SmartObjectUserHandle;`
- L56 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassZoneGraphFindEscapeTarget.h` (Public)


#### struct `FMassZoneGraphFindEscapeTargetInstanceData`  
`struct FMassZoneGraphFindEscapeTargetInstanceData`  
_L24-30_
- reflection: `USTRUCT()`
- desc: Updates TargetLocation to a escape target based on the agents current location on ZoneGraph, and disturbance annotation.
- L29 _public member_ `FMassZoneGraphTargetLocation EscapeTargetLocation;` — `UPROPERTY(VisibleAnywhere, Category = Output)`

#### struct `FMassZoneGraphFindEscapeTarget`  
`struct FMassZoneGraphFindEscapeTarget : public FMassStateTreeTaskBase`  
_L33-53_
- reflection: `USTRUCT(meta = (DisplayName = "ZG Find Escape Target"))`
- inherits: `FMassStateTreeTaskBase`
- L37 _public typedef_ `using FInstanceDataType = FMassZoneGraphFindEscapeTargetInstanceData;`
- L39 _public prototype_ `FMassZoneGraphFindEscapeTarget();`
- L42 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L43 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L44 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L45 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L47 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment> LocationHandle;`
- L48 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphSubsystem> ZoneGraphSubsystemHandle;`
- L49 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphAnnotationSubsystem> ZoneGraphAnnotationSubsystemHandle;`
- L52 _protected member_ `FZoneGraphTag DisturbanceAnnotationTag = FZoneGraphTag::None;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassZoneGraphFindSmartObjectTarget.h` (Public)


#### struct `FMassZoneGraphFindSmartObjectTargetInstanceData`  
`struct FMassZoneGraphFindSmartObjectTargetInstanceData`  
_L25-34_
- reflection: `USTRUCT()`
- desc: Computes move target to a smart object based on current location on ZoneGraph.
- L30 _public member_ `FSmartObjectClaimHandle ClaimedSlot;` — `UPROPERTY(VisibleAnywhere, Category = Input)`
- L33 _public member_ `FMassZoneGraphTargetLocation SmartObjectLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMassZoneGraphFindSmartObjectTarget`  
`struct FMassZoneGraphFindSmartObjectTarget : public FMassStateTreeTaskBase`  
_L37-52_
- reflection: `USTRUCT(meta = (DisplayName = "ZG Find Smart Object Target"))`
- inherits: `FMassStateTreeTaskBase`
- L41 _public typedef_ `using FInstanceDataType = FMassZoneGraphFindSmartObjectTargetInstanceData;`
- L44 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L45 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L46 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L47 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L49 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment> LocationHandle;`
- L50 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphAnnotationSubsystem> AnnotationSubsystemHandle;`
- L51 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassZoneGraphPathFollowTask.h` (Public)


#### struct `FMassZoneGraphTargetLocation`  
`struct FMassZoneGraphTargetLocation`  
_L30-72_
- reflection: `USTRUCT()`
- L34 _public function_ `void Reset()`
- L47 _public member_ `FZoneGraphLaneHandle LaneHandle;` — Current lane handle. (Could be debug only)
- L50 _public member_ `FZoneGraphLaneHandle NextLaneHandle;` — If valid, the this lane will be set as current lane after the path follow is completed.
- L53 _public member_ `float TargetDistance = 0.0f;` — Target distance along current lane.
- L56 _public member_ `TOptional<FVector> EndOfPathPosition;` — Optional end of path location.
- L59 _public member_ `TOptional<FVector> EndOfPathDirection;` — Optional end of path direction, used only if EndOfPathPosition is set.
- L62 _public member_ `FMassInt16Real AnticipationDistance = FMassInt16Real(50.0f);` — If start or end of path is off-lane, the distance along the lane is pushed forward/back along the lane to make smoother transition.
- L65 _public member_ `bool bMoveReverse = false;` — True, if we're moving reverse along the lane.
- L68 _public member_ `EMassMovementAction EndOfPathIntent = EMassMovementAction::Move;` — Movement intent at the end of the path
- L71 _public member_ `EZoneLaneLinkType NextExitLinkType = EZoneLaneLinkType::None;` — How the next lane handle is reached relative to the current lane.

#### struct `FMassZoneGraphPathFollowTaskInstanceData`  
`struct FMassZoneGraphPathFollowTaskInstanceData`  
_L78-90_
- reflection: `USTRUCT()`
- desc: Follows a path long the current lane to a specified point.
- L83 _public member_ `FStateTreePropertyRef TargetLocation;` — `UPROPERTY(EditAnywhere, Category = Input, meta=(RefType = "/Script/MassAIBehavior.MassZoneGraphTargetLocation"))`
- L86 _public member_ `FMassMovementStyleRef MovementStyle;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L89 _public member_ `float SpeedScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### struct `FMassZoneGraphPathFollowTask`  
`struct FMassZoneGraphPathFollowTask : public FMassStateTreeTaskBase`  
_L93-116_
- reflection: `USTRUCT(meta = (DisplayName = "ZG Path Follow"))`
- inherits: `FMassStateTreeTaskBase`
- L97 _public typedef_ `using FInstanceDataType = FMassZoneGraphPathFollowTaskInstanceData;`
- L100 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L101 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L102 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L103 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L104 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L106 _protected prototype_ `bool RequestPath(FMassStateTreeExecutionContext& Context, const FMassZoneGraphTargetLocation& TargetLocation) const;`
- L108 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment> LocationHandle;`
- L109 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`
- L110 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphPathRequestFragment> PathRequestHandle;`
- L111 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphShortPathFragment> ShortPathHandle;`
- L112 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphCachedLaneFragment> CachedLaneHandle;`
- L113 _protected member_ `TStateTreeExternalDataHandle<FAgentRadiusFragment> AgentRadiusHandle;`
- L114 _protected member_ `TStateTreeExternalDataHandle<FMassMovementParameters> MovementParamsHandle;`
- L115 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphSubsystem> ZoneGraphSubsystemHandle;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassAI/Source/MassAIBehavior/Public/Tasks/MassZoneGraphStandTask.h` (Public)


#### struct `FMassZoneGraphStandTaskInstanceData`  
`struct FMassZoneGraphStandTaskInstanceData`  
_L28-38_
- reflection: `USTRUCT()`
- L34 _public member_ `float Duration = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Delay before the task ends. Default (0 or any negative) will run indefinitely so it requires a transition in the state tree to stop it.
- L37 _public member_ `float Time = 0.0f;` — `UPROPERTY()`

#### struct `FMassZoneGraphStandTask`  
`struct FMassZoneGraphStandTask : public FMassStateTreeTaskBase`  
_L41-61_
- reflection: `USTRUCT(meta = (DisplayName = "ZG Stand"))`
- inherits: `FMassStateTreeTaskBase`
- L45 _public typedef_ `using FInstanceDataType = FMassZoneGraphStandTaskInstanceData;`
- L48 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L49 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L50 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L51 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L52 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L54 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment> LocationHandle;`
- L55 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`
- L56 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphShortPathFragment> ShortPathHandle;`
- L57 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphCachedLaneFragment> CachedLaneHandle;`
- L58 _protected member_ `TStateTreeExternalDataHandle<FMassMovementParameters> MovementParamsHandle;`
- L59 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphSubsystem> ZoneGraphSubsystemHandle;`
- L60 _protected member_ `TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSAIBEHAVIOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MassBehavior` (scope `UE`)
