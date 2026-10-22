# Plugins / MetaHumanCrowd

- module root: `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd`
- headers: 33; symbols: 479
- symbol kinds: class=24, delegate=2, function=13, macro=13, member=228, namespace=7, prototype=135, struct=51, typedef=2, variable=4
- PrivateDependencyModuleNames: Slate, SlateCore, SlateIM
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MassAIBehavior, MassActors, MassCharacterTrajectory, MassCommon, MassCore, MassCrowd, MassEntity, MassLOD, MassMovement, MassNavMeshNavigation, MassNavigation, MassRepresentation, MassSimulation, MassSmartObjects, MassSpawner, MeshDescription, MetaHumanCharacter, MetaHumanCharacterPalette, MetaHumanDefaultPipeline, Mover, MoverMassIntegration, NavigationSystem, PropertyBindingUtils, SmartObjectsModule, StateTreeModule

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassActorAnimationProcessor.h` (Private)


#### class `UMetaHumanMassActorProcessor`  
`class UMetaHumanMassActorProcessor : public UMassProcessor`  
_L18-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Mass processor that drives animation state for MetaHuman crowd entities on the Actor/Blueprint path. Runs only for entities that have a spawned actor that implements IMetahumanMassCrowdActorBlueprintInterface Game-thread only by default. Change bRequiresGameThreadExecution in INI if you're sure your logic is thread-safe/doesn't run in parallel with the animation update/double buffer parameters/etc.
- L23 _public prototype_ `UMetaHumanMassActorProcessor();`
- L28 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L34 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntityManager is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L36 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassCharacterTrajectoryToActorProcessor.h` (Private)


#### class `UMetaHumanMassCharacterTrajectoryToActorProcessor`  
`class UMetaHumanMassCharacterTrajectoryToActorProcessor : public UMassProcessor`  
_L18-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Mass processor that pipes trajectory data to MetaHuman crowd actors via IMetahumanMassCrowdActorBlueprintInterface::SetTrajectory. Runs only for entities that have a spawned actor implementing IMetahumanMassCrowdActorBlueprintInterface. Game-thread only by default. Change bRequiresGameThreadExecution in INI if you're sure your logic is thread-safe/doesn't run in parallel with the animation update/double buffer parameters/etc.
- L23 _public prototype_ `UMetaHumanMassCharacterTrajectoryToActorProcessor();`
- L26 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L27 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L29 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassCrowdRepresentationActorManagement.h` (Private)


#### class `UMetaHumanMassCrowdRepresentationActorManagement`  
`class UMetaHumanMassCrowdRepresentationActorManagement : public UMassCrowdRepresentationActorManagement`  
_L11-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassCrowdRepresentationActorManagement`
- L18 _protected prototype_ `virtual void SetActorEnabled(const EMassActorEnabledType EnabledType, AActor& Actor, const int32 EntityIdx, FMassCommandBuffer& CommandBuffer) const override;` — Override actor disabling / enabling as MetaHumans have a slightly different setup to normal UE Characters
- L21 _protected prototype_ `virtual void TeleportActor(const FTransform& Transform, AActor& Actor, FMassCommandBuffer& CommandBuffer) const override;` — MetaHuman crowd actors are driven by the Mover plugin, which owns position via its own simulation state. Override to also teleport the Mover's sim state.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassGameModePerf.h` (Private)


#### class `AMetaHumanMassGameModePerf`  
`class AMetaHumanMassGameModePerf : public AGameModeBase`  
_L15-31_
- reflection: `UCLASS()`
- inherits: `AGameModeBase`
- desc: Game mode that is used for MetaHuman Mass Crowd testing.
- L20 _public prototype_ `AMetaHumanMassGameModePerf();`
- L23 _public prototype_ `virtual void BeginPlay() override;`
- L28 _protected prototype_ `void OnSpawnCompleted();` — `UFUNCTION()`
- L30 _protected member_ `FVector LastTargetLocation;`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassIdentityDeinitializer.h` (Private)


#### class `UMetaHumanMassIdentityDeinitializer`  
`class UMetaHumanMassIdentityDeinitializer : public UMassObserverProcessor`  
_L15-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Observer that fires when a MetaHuman crowd entity is destroyed.
- L20 _public prototype_ `UMetaHumanMassIdentityDeinitializer();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L26 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassIdentityInitializer.h` (Private)


#### class `UMetaHumanMassIdentityInitializer`  
`class UMetaHumanMassIdentityInitializer : public UMassObserverProcessor`  
_L15-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Processor for initializing MetaHuman appearance.
- L20 _public prototype_ `UMetaHumanMassIdentityInitializer();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L26 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassNavMeshFindPerpendicularFurthestPointTask.h` (Private)


#### struct `FMetaHumanMassNavMeshFindPerpendicularFurthestPointTaskInstanceData`  
`struct FMetaHumanMassNavMeshFindPerpendicularFurthestPointTaskInstanceData`  
_L15-35_
- reflection: `USTRUCT()`
- L23 _public member_ `FVector ReferenceDirection = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Reference direction vector. The task will find the furthest nav mesh point along this vector.
- L27 _public member_ `float MaxSearchDistance = 5000.f;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Maximum search distance along the perpendicular directions.
- L31 _public member_ `TSubclassOf<class UNavigationQueryFilter> FilterClass;` — `UPROPERTY(EditAnywhere, Category=Query)` — "None" will result in default filter being used.
- L34 _public member_ `FMassTargetLocation TargetLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMetaHumanMassNavMeshFindPerpendicularFurthestPointTask`  
`struct FMetaHumanMassNavMeshFindPerpendicularFurthestPointTask : public FMassStateTreeTaskBase`  
_L43-57_
- reflection: `USTRUCT(meta = (DisplayName = "MetaHuman NavMesh Find Furthest Perpendicular Point"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Updates TargetLocation to the furthest reachable point on the NavMesh along a direction directions are tested and the one that reaches furthest is chosen. An optional filter for nav mesh class can be used.
- L47 _public typedef_ `using FInstanceDataType = FMetaHumanMassNavMeshFindPerpendicularFurthestPointTaskInstanceData;`
- L50 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L51 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L52 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L54 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`
- L55 _protected member_ `TStateTreeExternalDataHandle<FAgentRadiusFragment> AgentRadiusHandle;`
- L56 _protected member_ `TStateTreeExternalDataHandle<FAgentHeightFragment> AgentHeightHandle;`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassResetMoverOnActorAcquireProcessor.h` (Private)


#### class `UMetaHumanMassResetMoverOnActorAcquireProcessor`  
`class UMetaHumanMassResetMoverOnActorAcquireProcessor : public UMassProcessor`  
_L21-34_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Detects entities that have just transitioned into an actor representation (PrevRepresentation was not an actor type, CurrentRepresentation is) and resets the bound actor's UMoverComponent + UMassMoverInputComponent state to match the entity's authoritative Mass fragments. Without this, a pooled actor reused for a new entity carries the previous occupant's residual values for one frame -- the sync state for GenerateMove and the input bridge for ProduceInput -- producing a one-frame capsule pop on the representation swap.
- L26 _public prototype_ `UMetaHumanMassResetMoverOnActorAcquireProcessor();`
- L29 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L30 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L33 _private member_ `FMassEntityQuery EntityQuery;`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassSharedAnimTrackPool.h` (Private)


#### struct `FSharedAnimTrackPool`  
`struct FSharedAnimTrackPool`  
_L30-118_
- desc: Manages shared ASTPD track allocation for ISKM animation. Instead of one track per entity, maintains: - Steady-state tracks: N looping tracks per sequence at fixed phase offsets (persistent) - Blend tracks: temporary per-entity tracks used during sequence transitions Entities in steady-state all share one of the N phase-offset tracks. During a blend, an entity gets its own track. When the blend completes, it switches to the nearest-phase steady-state track on the target sequence. Steady-state tracks are allocated on-demand per sequence — only sequences that entities actually use get GPU tracks allocated. Graceful degradation: when blend tracks are exhausted, snap directly to steady-state. Steady-state count is configurable (min 1 = full lockstep).
- L32 _public member_ `static constexpr int32 DefaultSteadyStateTracksPerSequence = 3;`
- L33 _public member_ `static constexpr int32 DefaultMaxBlendTracks = 50;`
- L69 _public member_ `TArray<FSequenceTracks> SequenceTracks;` — Steady-state tracks indexed by sequence index
- L72 _public member_ `TArray<FBlendTrack> ActiveBlendTracks;` — Active blend tracks (fixed-size pool)
- L73 _public member_ `TArray<int32> FreeBlendSlots;`
- L76 _public member_ `Experimental::TRobinHoodHashMap<FMassEntityHandle, FEntityTrackState> EntityStates;` — Per-entity state
- L79 _public member_ `int32 SteadyStateTracksPerSequence = DefaultSteadyStateTracksPerSequence;` — Configuration
- L80 _public member_ `int32 MaxBlendTracks = DefaultMaxBlendTracks;`
- L81 _public member_ `bool bInitialized = false;`
- L84 _public prototype_ `void Initialize(UAnimSequenceTransformProviderDataInstance* ASTPDI, double WorldTime);` — Initialize the pool structure for a given ASTPD. Does not allocate GPU tracks — those are on-demand.
- L87 _public prototype_ `int32 UpdateEntityTrack( UAnimSequenceTransformProviderDataInstance* ASTPDI, const FMassEntityHandle& EntityHandle, const FAnimSequenceTrackAutoPlayData& AnimData, double WorldTime);` — Get or assign a track for an entity. Returns the TrackIndex to use as AnimationIndex.
- L94 _public prototype_ `void RemoveEntity( UAnimSequenceTransformProviderDataInstance* ASTPDI, const FMassEntityHandle& EntityHandle);` — Remove an entity from the pool
- L99 _public prototype_ `void EnsureSteadyStateTracksForSequence( UAnimSequenceTransformProviderDataInstance* ASTPDI, int32 SequenceIndex, double WorldTime);` — Lazily allocate steady-state tracks for a sequence on first use
- L107 _public prototype_ `int32 FindBestSteadyStateTrack( UAnimSequenceTransformProviderDataInstance* ASTPDI, int32 SequenceIndex, const FMassEntityHandle& EntityHandle, double WorldTime);` — Find the best steady-state track for a given sequence. Deterministic per-entity: the same entity always maps to the same track. Allocates steady-state tracks on demand if they don't exist yet.
- L114 _public prototype_ `void ProcessCompletedBlends( UAnimSequenceTransformProviderDataInstance* ASTPDI, double WorldTime, TFunctionRef<void(const FMassEntityHandle&, int32 )> OnTrackChanged);` — Process completed blends — switch entities from blend tracks to steady-state

#### struct `FSharedAnimTrackPool::FSteadyStateTrack`  
`struct FSteadyStateTrack`  
_L36-41_
- desc: A steady-state looping track at a fixed phase offset
- L38 _public member_ `int32 TrackIndex = INDEX_NONE;`
- L39 _public member_ `double ReferenceTimestamp = 0.0;`
- L40 _public member_ `float PhaseOffset = 0.0f;` — 0.0 to 1.0 within the sequence duration

#### struct `FSharedAnimTrackPool::FBlendTrack`  
`struct FBlendTrack`  
_L44-50_
- desc: A temporary blend track for a single entity
- L46 _public member_ `int32 TrackIndex = INDEX_NONE;`
- L47 _public member_ `FMassEntityHandle OwnerEntity;`
- L48 _public member_ `int32 TargetSteadyStateIndex = INDEX_NONE;` — which steady-state track to join after blend
- L49 _public member_ `double BlendCompleteWorldTime = 0.0;` — when to switch to steady-state

#### struct `FSharedAnimTrackPool::FSequenceTracks`  
`struct FSequenceTracks`  
_L53-57_
- desc: Per-sequence steady-state tracks
- L55 _public member_ `TArray<FSteadyStateTrack> SteadyStateTracks;`
- L56 _public member_ `float SequenceLength = 0.0f;`

#### struct `FSharedAnimTrackPool::FEntityTrackState`  
`struct FEntityTrackState`  
_L60-66_
- desc: Per-entity tracking: which track (steady-state or blend) an entity is currently using
- L62 _public member_ `int32 CurrentTrackIndex = INDEX_NONE;`
- L63 _public member_ `int32 CurrentSequenceIndex = INDEX_NONE;`
- L64 _public member_ `bool bIsBlending = false;`
- L65 _public member_ `int32 BlendTrackSlot = INDEX_NONE;` — index into ActiveBlendTracks, or INDEX_NONE if steady-state

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassSimpleAnimationProcessor.h` (Private)


#### class `UMetaHumanMassSimpleAnimationProcessor`  
`class UMetaHumanMassSimpleAnimationProcessor : public UMassProcessor`  
_L12-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L17 _public prototype_ `UMetaHumanMassSimpleAnimationProcessor();`
- L22 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L28 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntityManager is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L30 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassSmartObjectFurthestCandidateTask.h` (Private)


#### struct `FMetaHumanMassSmartObjectFurthestCandidateTaskInstanceData`  
`struct FMetaHumanMassSmartObjectFurthestCandidateTaskInstanceData`  
_L19-44_
- reflection: `USTRUCT()`
- L28 _public member_ `FStateTreePropertyRef CandidateSlots;` — `UPROPERTY(VisibleAnywhere, Category = Input, meta = (RefType = "/Script/MassSmartObjects.MassSmartObjectCandidateSlots"))` — Candidate slots from a prior FindSmartObject task. The task will pick the furthest slot from the entity's current location. No claim is made.
- L36 _public member_ `bool bUseEntityLocationAsSearchLocation = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — When using the entrance location request with selection method 'NearestToSearchLocation', this property indicates whether the request will set the search location using the entity transform or use the request value (can be bound).
- L40 _public member_ `FSmartObjectSlotEntranceLocationRequest EntranceRequest;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Request parameters when using the entrance location request.
- L43 _public member_ `FMassTargetLocation SmartObjectLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMetaHumanMassSmartObjectFurthestCandidateTask`  
`struct FMetaHumanMassSmartObjectFurthestCandidateTask : public FMassStateTreeTaskBase`  
_L53-75_
- reflection: `USTRUCT(meta = (DisplayName = "MetaHuman Navigate To Furthest Smart Object Candidate (No Claim)"))`
- inherits: `FMassStateTreeTaskBase`
- desc: Picks the furthest Smart Object slot from a set of candidates and resolves its navigation target, without claiming the slot. Suitable for navigating toward a Smart Object as an unclaimed waypoint. Intended to be used after a FindSmartObject task that populates CandidateSlots.
- L57 _public typedef_ `using FInstanceDataType = FMetaHumanMassSmartObjectFurthestCandidateTaskInstanceData;`
- L60 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L61 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L62 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L64 _protected member_ `TStateTreeExternalDataHandle<FAgentRadiusFragment, EStateTreeExternalDataRequirement::Optional> AgentRadiusHandle;`
- L65 _protected member_ `TStateTreeExternalDataHandle<FAgentHeightFragment, EStateTreeExternalDataRequirement::Optional> AgentHeightHandle;`
- L66 _protected member_ `TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;`
- L67 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;`
- L74 _protected member_ `bool bUseEntranceLocationRequest = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Whether to use the entrance location request first. Falls back to raw slot transform if no entrance is found or the request is disabled.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassSpawner.h` (Private)


#### class `AMetaHumanMassSpawner`  
`class AMetaHumanMassSpawner : public AMassSpawner`  
_L14-27_
- reflection: `UCLASS()`
- inherits: `AMassSpawner`
- desc: Implementation of Mass Spawner that allows asset loading to be synchronous.
- L19 _public prototype_ `AMetaHumanMassSpawner();`
- L25 _public prototype_ `void WaitForStreamingAssets();` — `UFUNCTION(BlueprintCallable, Category=MassSpawner)` — If StreamingHandle is set, synchronously waits until all assets are streamed in.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassTargetLocationEvaluator.h` (Private)


#### struct `FMetaHumanMassTargetReaderInstanceData`  
`struct FMetaHumanMassTargetReaderInstanceData`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `FMassTargetLocation TargetLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMetaHumanMassTargetLocationEvaluator`  
`struct FMetaHumanMassTargetLocationEvaluator : public FMassStateTreeEvaluatorBase`  
_L19-29_
- reflection: `USTRUCT(meta = (DisplayName = "MetaHuman Mass Target Location Evaluator"))`
- inherits: `FMassStateTreeEvaluatorBase`
- L23 _public prototype_ `virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L25 _public function_ `virtual const UStruct* GetInstanceDataType() const override`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassUpdateActorIdentityProcessor.h` (Private)


#### class `UMetaHumanMassUpdateActorIdentityProcessor`  
`class UMetaHumanMassUpdateActorIdentityProcessor : public UMassProcessor`  
_L15-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor for updating Actors to use appropriate MHI.
- L20 _public prototype_ `UMetaHumanMassUpdateActorIdentityProcessor();`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L31 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntityManager is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L33 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/Mass/MetaHumanMassUpdateCustomDataProcessor.h` (Private)


#### class `UMetaHumanMassUpdateCustomDataProcessor`  
`class UMetaHumanMassUpdateCustomDataProcessor : public UMassProcessor`  
_L13-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Pushes per-appearance custom-data floats onto each visible MetaHuman crowd entity's matching ISKMs every frame.
- L18 _public prototype_ `UMetaHumanMassUpdateCustomDataProcessor();`
- L21 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L22 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L24 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/MetaHumanCrowdLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCrowd, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCrowd, Log, All);`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Private/MetaHumanCrowdMaterialUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MetaHuman` (scope `UE`)
- L17 _namespace_ `namespace MaterialUtils` (scope `UE::MetaHuman`)
- L28 _prototype_ `void SetInstanceParametersOnCustomData( const TArray<FMetaHumanMaterialParameter>& InMaterialParameters, const TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial>& InInstancedComponentOverrideMaterials, const FInstancedPropertyBag& InPropertyBag, TArrayView<float> OutCustomData);` (scope `UE::MetaHuman::MaterialUtils`) — Updates per-instance custom data floats for instanced mesh material slots. @param InMaterialParameters                   Parameter definitions from the source pipeline. @param InInstancedComponentOverrideMaterials  Per-slot instanced material configuration, keyed by material slot name. @param InPropertyBag                          Current parameter values. @param OutCustomData                          Custom data float array to write into.
- L43 _prototype_ `void SetInstanceParameterDefaultsOnCustomData( const TArray<FMetaHumanMaterialParameter>& InMaterialParameters, const TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial>& InInstancedComponentOverrideMaterials, TArrayView<float> OutCustomData);` (scope `UE::MetaHuman::MaterialUtils`) — Seeds OutCustomData with default parameter values read from each slot's InstancedComponentMaterial. @param InMaterialParameters                   Parameter definitions from the source pipeline. @param InInstancedComponentOverrideMaterials  Per-slot instanced material configuration, keyed by material slot name. @param OutCustomData                          Custom data float array to write into.
- L54 _prototype_ `TArray<FMetaHumanMaterialParameter> FilterToCrowdSupportedParameters( TConstArrayView<FMetaHumanMaterialParameter> InParameters, bool bLogWarningOnFilter = false, const FString& InContextForLogging = TEXT(""));` (scope `UE::MetaHuman::MaterialUtils`) — Returns a copy of InParameters containing only entries whose SlotTarget is supported by the crowd pipelines. If bLogWarningOnFilter is true, logs a warning for each parameter that is filtered out.
- L63 _prototype_ `int32 ComputeCustomDataSize( const TMap<FName, FMetaHumanCrowdOutfitCustomDataFormat>& InFormatMap);` (scope `UE::MetaHuman::MaterialUtils`) — Computes the number of custom data floats required to hold every parameter described by InFormatMap.
- L74 _prototype_ `int32 ComputeISKMCustomDataSize( const TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial>& InInstancedComponentOverrideMaterials);` (scope `UE::MetaHuman::MaterialUtils`) — Computes the total number of custom data floats needed to fit the authored custom data offsets for every material slot on a mesh. The returned size is large enough that an offset+channel write from any slot is in-range. Callers should also run ValidateNoOverlappingCustomDataOffsets to ensure two slots haven't authored offsets that step on each other.
- L86 _prototype_ `bool ValidateNoOverlappingCustomDataOffsets( const TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial>& InInstancedComponentOverrideMaterials, TConstArrayView<FName> InMeshSlotNames, const FString& InContextForLogging = TEXT(""));` (scope `UE::MetaHuman::MaterialUtils`) — Walks every slot's InstanceParameterNameToCustomDataFormat and warns if two slots write into overlapping float ranges of the ISKM-wide custom-data buffer. Validation is scoped to the slot names actually present on the mesh being assembled (InMeshSlotNames). Returns true if the layout is valid (no overlaps), false if collisions were found.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Item/MetaHumanCrowdCharacterPipeline.h` (Public)


#### struct `FMetaHumanCrowdCharacterBuildOutput`  
`struct FMetaHumanCrowdCharacterBuildOutput`  
_L14-33_
- reflection: `USTRUCT()`
- L20 _public member_ `TObjectPtr<USkeletalMesh> FaceMesh;` — `UPROPERTY()`
- L23 _public member_ `TObjectPtr<USkeletalMesh> BodyMesh;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBodyMesh;` — `UPROPERTY()`
- L29 _public member_ `TMap<FString, float> BodyMeasurements;` — `UPROPERTY()`
- L32 _public member_ `TObjectPtr<UMetaHumanCharacter> CompatibleBody;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdCharacterAssemblyOutput`  
`struct FMetaHumanCrowdCharacterAssemblyOutput`  
_L36-52_
- reflection: `USTRUCT(BlueprintType)`
- L42 _public member_ `TObjectPtr<USkeletalMesh> FaceMesh;` — `UPROPERTY()`
- L45 _public member_ `TObjectPtr<USkeletalMesh> BodyMesh;` — `UPROPERTY()`
- L48 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBodyMesh;` — `UPROPERTY()`
- L51 _public member_ `TMap<FString, float> BodyMeasurements;` — `UPROPERTY()`

#### class `UMetaHumanCrowdCharacterPipeline`  
`class UMetaHumanCrowdCharacterPipeline : public UMetaHumanItemPipeline`  
_L55-84_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L60 _public prototype_ `UMetaHumanCrowdCharacterPipeline();`
- L63 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L65 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L68 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L70 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L74 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L79 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanCrowdEditor.MetaHumanCrowdCharacterEditorPipeline"))`
- L83 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Item/MetaHumanCrowdGroomPipeline.h` (Public)


#### struct `FMetaHumanCrowdGroomBakedTextureEntry`  
`struct FMetaHumanCrowdGroomBakedTextureEntry`  
_L25-44_
- reflection: `USTRUCT()`
- desc: Pre-authored baked groom texture for a single (groom, head) pair, plus the wardrobe slot the groom lives in. The collection pipeline binds this onto the head's face material(s) at the face LODs listed in AppliesAtFaceLODs.
- L31 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY()` — Pre-authored baked groom texture, bound onto the face material's "{WardrobeSlot}AttributeMap" parameter.
- L35 _public member_ `FName PipelineSlotName;` — `UPROPERTY()` — Pipeline slot the groom lives in (e.g. "Hair", "Beard"); used as a parameter-name prefix.
- L39 _public member_ `TArray<int32> AppliesAtFaceLODs;` — `UPROPERTY()` — Face-LOD indices at which the baked texture is bound.
- L43 _public member_ `int32 GroomTextureMinLOD = INT32_MAX;` — `UPROPERTY()` — The effective GroomTextureMinLOD threshold.

#### struct `FMetaHumanCrowdGroomMaterialOverride`  
`struct FMetaHumanCrowdGroomMaterialOverride`  
_L50-59_
- reflection: `USTRUCT()`
- desc: Per-variant material override carried alongside the shared geometry bundle.
- L55 _public member_ `TArray<FSkeletalMaterial> Materials;` — `UPROPERTY()`
- L58 _public member_ `TArray<TArray<int32>> LODMaterialMaps;` — Per-LOD polygon-group-ID -> Materials-index map.

#### struct `FMetaHumanCrowdGroomBuildOutput`  
`struct FMetaHumanCrowdGroomBuildOutput`  
_L62-103_
- reflection: `USTRUCT()`
- L74 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdMeshGeometryBundle> ItemToGroomGeometryMap;` — `UPROPERTY()` — Per-(groom, head) shared geometry. The bundle's own Materials/LODMaterialMaps describe the actor variant's MICs (named for actor output-LOD positions, parented to CardsMaterial or HelmetsMaterial as appropriate). Runtime AssembleItem reads these directly when generating MIDs for the actor mesh.
- L86 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdGroomMaterialOverride> InstancedMaterialOverrides;` — `UPROPERTY()` — Per-key override of the bundle's Materials/LODMaterialMaps for the instanced variant. Geometry is shared with ItemToGroomGeometryMap; only the material set differs (each MIC named for instanced output-LOD positions, ensuring no MIC is shared between actor and instanced skeletal meshes). Keys parallel ItemToGroomGeometryMap, populated in lockstep. Note: FMetaHumanCrowdGroomMaterialOverride::LODMaterialMaps is non-UPROPERTY (matches FMetaHumanCrowdMeshGeometryBundle::LODMaterialMaps); won't survive reflection-based serialization.
- L94 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdGroomBakedTextureEntry> ItemToBakedGroomTexture;` — `UPROPERTY()` — Per-(groom, head) baked groom texture entries, populated when the editor groom pipeline has BakedGroomTexture set and at least one face LOD has no card/helmet geometry. Consumed by the collection pipeline when constructing face MICs.
- L98 _public member_ `FString GroomAssetName;` — `UPROPERTY()` — Source groom asset name, used for friendly mesh naming.
- L102 _public member_ `FName PipelineSlotName;` — `UPROPERTY()` — Pipeline slot the groom lives in (e.g. "Hair", "Beard").

#### struct `FMetaHumanCrowdGroomAssemblyInput`  
`struct FMetaHumanCrowdGroomAssemblyInput`  
_L106-113_
- reflection: `USTRUCT()`
- L112 _public member_ `FMetaHumanPaletteItemKey TargetItem;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdGroomAssemblyOutput`  
`struct FMetaHumanCrowdGroomAssemblyOutput`  
_L116-137_
- reflection: `USTRUCT(BlueprintType)`
- L123 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — MID overrides for actor mesh components, keyed by material slot name.
- L127 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> InstancedMaterialData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Per-slot ISKM material binding for instanced meshes.
- L136 _public member_ `TArray<float> InstancedMeshCustomDataFloats;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — ISKM-wide per-instance custom data float buffer. Sized once during assembly to fit every slot's authored offsets. Slots write into this via absolute CustomDataOffset values that must not overlap across slots on the same ISKM.

#### class `UMetaHumanCrowdGroomPipelineMaterialParameters`  
`class UMetaHumanCrowdGroomPipelineMaterialParameters : public UObject`  
_L140-162_
- reflection: `UCLASS()`
- inherits: `UObject`
- L146 _public member_ `float Melanin = 0.16f;` — `UPROPERTY(meta = (MaterialParamName = "Melanin", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L149 _public member_ `float Redness = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "Redness", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L152 _public member_ `float Roughness = 0.25f;` — `UPROPERTY(meta = (MaterialParamName = "Roughness", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L155 _public member_ `float Whiteness = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "WhiteAmount", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L158 _public member_ `float Lightness = 0.0f;` — `UPROPERTY(meta = (MaterialParamName = "LightAmount", Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L161 _public member_ `FLinearColor DyeColor = FLinearColor::White;` — `UPROPERTY(meta = (MaterialParamName = "DyeColor"))`

#### class `UMetaHumanCrowdGroomPipeline`  
`class UMetaHumanCrowdGroomPipeline : public UMetaHumanItemPipeline`  
_L165-222_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L170 _public prototype_ `UMetaHumanCrowdGroomPipeline();`
- L174 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L176 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L180 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L182 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L185 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L187 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L188 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L191 _public member_ `TObjectPtr<const UMetaHumanWardrobeItem> SourceGroomItem;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L195 _public member_ `TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial> InstancedComponentOverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Key is material slot name
- L203 _public member_ `bool bUseCustomRuntimeMaterialParameters = false;` — `UPROPERTY(EditAnywhere, Category = "Material")` — When enabled, RuntimeMaterialParameters array can be edited manually. When disabled, the array is automatically populated from the declared material parameter properties and any manual edits are disabled.
- L207 _public member_ `TArray<FMetaHumanMaterialParameter> RuntimeMaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (EditCondition = "bUseCustomRuntimeMaterialParameters"))`
- L211 _private prototype_ `void UpdateParameters();`
- L212 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L217 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanCrowdEditor.MetaHumanCrowdGroomEditorPipeline"))`
- L221 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Item/MetaHumanCrowdHeadPipeline.h` (Public)


#### struct `FMetaHumanCrowdHeadBuildOutput`  
`struct FMetaHumanCrowdHeadBuildOutput`  
_L16-27_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<USkeletalMesh> HeadMesh;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<UAnimSequenceTransformProviderData> BakedAnimRootProvider;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdHeadAssemblyOutput`  
`struct FMetaHumanCrowdHeadAssemblyOutput`  
_L30-41_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public member_ `TObjectPtr<USkeletalMesh> HeadMesh;` — `UPROPERTY()`
- L39 _public member_ `TObjectPtr<UAnimSequenceTransformProviderData> BakedAnimRootProvider;` — `UPROPERTY()`

#### class `UMetaHumanCrowdHeadPipeline`  
`class UMetaHumanCrowdHeadPipeline : public UMetaHumanItemPipeline`  
_L44-76_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L49 _public prototype_ `UMetaHumanCrowdHeadPipeline();`
- L52 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L54 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L57 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L59 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L62 _public member_ `TSoftObjectPtr<UMetaHumanCharacter> CompatibleBody;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L66 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L71 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanCrowdEditor.MetaHumanCrowdHeadEditorPipeline"))`
- L75 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Item/MetaHumanCrowdOutfitPipeline.h` (Public)


#### struct `FMetaHumanCrowdOutfitBuildOutput`  
`struct FMetaHumanCrowdOutfitBuildOutput`  
_L18-31_
- reflection: `USTRUCT()`
- L27 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdMeshGeometryBundle> BodyToOutfitGeometryMap;` — `UPROPERTY()` — Keyed by body item key -> geometry bundle for the fitted outfit.
- L30 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMap;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdOutfitAssemblyInput`  
`struct FMetaHumanCrowdOutfitAssemblyInput`  
_L34-41_
- reflection: `USTRUCT(BlueprintType)`
- L40 _public member_ `FMetaHumanPaletteItemKey BodyItem;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdOutfitCustomDataFormat`  
`struct FMetaHumanCrowdOutfitCustomDataFormat`  
_L44-69_
- reflection: `USTRUCT(BlueprintType)`
- L56 _public member_ `int32 CustomDataOffset = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Materials")` — Offset into the ISKM's per-instance custom-data float buffer. The custom-data buffer is shared across every material slot on a single ISKM, so the offsets authored here must not overlap each other across slots on the same mesh.
- L59 _public member_ `uint8 bUseChannelR : 1 = true;` — `UPROPERTY(EditAnywhere, Category = "Materials")`
- L62 _public member_ `uint8 bUseChannelG : 1 = true;` — `UPROPERTY(EditAnywhere, Category = "Materials")`
- L65 _public member_ `uint8 bUseChannelB : 1 = true;` — `UPROPERTY(EditAnywhere, Category = "Materials")`
- L68 _public member_ `uint8 bUseChannelA : 1 = true;` — `UPROPERTY(EditAnywhere, Category = "Materials")`

#### struct `FMetaHumanCrowdOutfitInstancedMaterial`  
`struct FMetaHumanCrowdOutfitInstancedMaterial`  
_L72-82_
- reflection: `USTRUCT(BlueprintType)`
- L78 _public member_ `TObjectPtr<UMaterialInterface> InstancedComponentMaterial;` — `UPROPERTY(EditAnywhere, Category = "Materials")`
- L81 _public member_ `TMap<FName, FMetaHumanCrowdOutfitCustomDataFormat> InstanceParameterNameToCustomDataFormat;` — `UPROPERTY(EditAnywhere, Category = "Materials")`

#### struct `FMetaHumanCrowdOutfitAssemblyOutput`  
`struct FMetaHumanCrowdOutfitAssemblyOutput`  
_L85-106_
- reflection: `USTRUCT(BlueprintType)`
- L92 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> MeshComponentOverrideMaterials;` — `UPROPERTY()` — MID overrides for actor mesh components, keyed by material slot name.
- L96 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> InstancedMaterialData;` — `UPROPERTY()` — Per-slot ISKM material binding for instanced meshes.
- L105 _public member_ `TArray<float> InstancedMeshCustomDataFloats;` — `UPROPERTY()` — ISKM-wide per-instance custom data float buffer. Sized once during assembly to fit every slot's authored offsets. Slots write into this via absolute CustomDataOffset values that must not overlap across slots on the same ISKM.

#### class `UMetaHumanCrowdOutfitPipeline`  
`class UMetaHumanCrowdOutfitPipeline : public UMetaHumanItemPipeline`  
_L109-147_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- L114 _public prototype_ `UMetaHumanCrowdOutfitPipeline();`
- L117 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L119 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L122 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L124 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L126 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L129 _public member_ `TObjectPtr<const UMetaHumanWardrobeItem> SourceOutfitItem;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L133 _public member_ `TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial> InstancedComponentOverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Key is material slot name
- L137 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L142 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanCrowdEditor.MetaHumanCrowdOutfitEditorPipeline"))`
- L146 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Item/MetaHumanCrowdSkeletalClothingPipeline.h` (Public)


#### class `UMetaHumanCrowdSkeletalClothingPipeline`  
`class UMetaHumanCrowdSkeletalClothingPipeline : public UMetaHumanItemPipeline`  
_L19-61_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanItemPipeline`
- desc: Crowd item pipeline for skeletal-mesh clothing.
- L24 _public prototype_ `UMetaHumanCrowdSkeletalClothingPipeline();`
- L27 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L29 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const override;`
- L32 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L34 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const override;`
- L36 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override;`
- L43 _public member_ `TObjectPtr<const UMetaHumanWardrobeItem> SourceSkeletalClothingItem;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — The source wardrobe item, whose pipeline must be a UMetaHumanSkeletalMeshPipeline. Override materials and runtime material parameters are read from this source pipeline.
- L47 _public member_ `TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial> InstancedComponentOverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — Key is material slot name
- L51 _private prototype_ `TSubclassOf<UMetaHumanItemEditorPipeline> GetEditorPipelineClass() const;`
- L56 _private member_ `TObjectPtr<UMetaHumanItemEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Pipeline", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanCrowdEditor.MetaHumanCrowdSkeletalClothingEditorPipeline"))`
- L60 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/IMetahumanMassCrowdActorBlueprintInterface.h` (Public)


#### class `UMetahumanMassCrowdActorBlueprintInterface`  
`class UMetahumanMassCrowdActorBlueprintInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI)`
- inherits: `UInterface`

#### class `IMetahumanMassCrowdActorBlueprintInterface`  
`class IMetahumanMassCrowdActorBlueprintInterface : public IInterface`  
_L26-42_
- inherits: `IInterface`
- desc: Blueprint interface for Actor classes used in the MetaHuman Mass crowd system on the Actor representation path. Implement this interface on any Actor Blueprint that should be driven by Mass. Each tick Mass read/writes animation state into the Actor for ISKM synchronization and locomotion.
- L32 _public prototype_ `void SetMetaHumanMassAnimDesc(const FMetahumanMassAnimDesc& NewAnimDesc);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")`
- L35 _public prototype_ `FMetahumanMassAnimDesc GetMetaHumanMassAnimDesc() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")`
- L38 _public prototype_ `void SetTrajectory(const FTransformTrajectory& NewTrajectory);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")`
- L41 _public prototype_ `void SetAnimations(const TMap<FName, UAnimSequence*>& Animations);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/MetaHumanCrowdAppearanceProvider.h` (Public)


#### struct `FMetaHumanCrowdAppearanceHandle`  
`struct FMetaHumanCrowdAppearanceHandle`  
_L20-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: Opaque handle to an appearance registered with UMetaHumanMassRepresentationSubsystem.
- L24 _public member_ `static constexpr uint32 InvalidIndex = TNumericLimits<uint32>::Max();`
- L26 _public prototype_ `FMetaHumanCrowdAppearanceHandle() = default;`
- L28 _public function_ `explicit FMetaHumanCrowdAppearanceHandle(uint32 InIndex) : Index(InIndex)`
- L33 _public function_ `bool IsValid() const`
- L38 _public function_ `uint32 GetIndex() const`
- L43 _public prototype_ `bool operator==(const FMetaHumanCrowdAppearanceHandle& Other) const = default;`
- L52 _private member_ `uint32 Index = InvalidIndex;` — `UPROPERTY()`

#### class `UMetaHumanCrowdAppearanceProvider`  
`class UMetaHumanCrowdAppearanceProvider : public UObject`  
_L87-137_
- reflection: `UCLASS(MinimalAPI, Blueprintable, EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: Base class for objects that decide which appearance is used for each spawned crowd entity. Subclass this (in C++ or Blueprint) and assign your subclass to the AppearanceProviderClass property on the MetaHuman Crowd Visualization trait. The same provider object handles every spawn/despawn for that class in that world, so it is safe to hold persistent state. Typical usage: 1. Override Initialize to inspect the pre-registered MHIs and assemble any extra MHIs you want to make available. Call Subsystem->RegisterInstance(MyAssembledInstance) for each new MHI. 2. Override AcquireAppearance to pick an appearance for a new entity. Use Subsystem->TryGetAppearanceHandleForInstance(MHI) to look up the handle for any MHI you already know about (whether pre-registered or registered by this provider). The world location of the spawn is provided so you can vary appearance by location. 3. Override OnEntityDespawned to update bookkeeping when an entity is destroyed. This fires on actual entity destruction, not on temporary LOD-driven invisibility. 4. To grow the pool at runtime, create a new MHI and call RegisterInstance. To shrink the pool, call UnregisterInstance(Handle). The subsystem refcounts handles, so a handle that is still in use by entities will be physically released only when the last such entity is destroyed.
- L104 _public prototype_ `void Initialize(UMetaHumanMassRepresentationSubsystem* Subsystem, const TArray<UMetaHumanInstance*>& PreRegisteredInstances);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MetaHuman|Crowd")` — Called once when this provider is first created for a world. The PreRegisteredInstances array contains the MetaHuman Instances that were already registered with the subsystem before this provider was created -- typically the contents of the trait's CharacterInstances property. To obtain their handles call Subsystem->TryGetAppearanceHandleForInstance(MHI). Use this opportunity to assemble any additional MHIs you want to add to the pool, and call Subsystem->RegisterInstance for each.
- L105 _public prototype_ `virtual void Initialize_Implementation(UMetaHumanMassRepresentationSubsystem* Subsystem, const TArray<UMetaHumanInstance*>& PreRegisteredInstances);`
- L118 _public prototype_ `FMetaHumanCrowdAppearanceHandle AcquireAppearance(UMetaHumanMassRepresentationSubsystem* Subsystem, const FVector& SpawnLocation);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MetaHuman|Crowd")` — Called for each new crowd entity to determine which appearance it should use. @param Subsystem    The owning representation subsystem, useful for registering more instances on demand. @param SpawnLocation World-space location at which the entity is being spawned. @return             A handle previously obtained from RegisterInstance. Returning an invalid handle falls back to the trait's CharacterInstances pool if one is set, or leaves the entity with no appearance otherwise.
- L119 _public prototype_ `virtual FMetaHumanCrowdAppearanceHandle AcquireAppearance_Implementation(UMetaHumanMassRepresentationSubsystem* Subsystem, const FVector& SpawnLocation);`
- L128 _public prototype_ `void OnEntityDespawned(UMetaHumanMassRepresentationSubsystem* Subsystem, FMetaHumanCrowdAppearanceHandle Handle);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MetaHuman|Crowd")` — Called when an entity that was assigned an appearance by this provider is despawned. Does not fire for temporary LOD-driven invisibility, only when the entity itself is destroyed.
- L129 _public prototype_ `virtual void OnEntityDespawned_Implementation(UMetaHumanMassRepresentationSubsystem* Subsystem, FMetaHumanCrowdAppearanceHandle Handle);`
- L135 _public prototype_ `void Shutdown(UMetaHumanMassRepresentationSubsystem* Subsystem);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MetaHuman|Crowd")` — Called when this provider's owning subsystem is being torn down.
- L136 _public prototype_ `virtual void Shutdown_Implementation(UMetaHumanMassRepresentationSubsystem* Subsystem);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCROWD_API`
- L45 _function_ `friend uint32 GetTypeHash(const FMetaHumanCrowdAppearanceHandle& Handle)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/MetaHumanMassAnimDesc.h` (Public)


#### struct `FMetahumanMassAnimDesc`  
`struct FMetahumanMassAnimDesc`  
_L11-31_
- reflection: `USTRUCT(BlueprintType)`
- desc: Native struct used to pipe data from Mass Instance -> Actor -> Anim Blueprint system.
- L17 _public member_ `TObjectPtr<class UAnimSequence> AnimSequence = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mass)` — @TODO: Populate this from ISKM transform provider data
- L20 _public member_ `int32 AnimSequenceIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mass)`
- L23 _public member_ `float Position = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mass)`
- L26 _public member_ `float Significance = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mass)`
- L30 _public member_ `bool bJustSwapped = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mass)` — This can be used by animation to fire reset events and all kinds of other logic that's needed for a clean swap.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/MetaHumanMassCrowdTags.h` (Public)


#### struct `FMetahumanMassCrowdActorTag`  
`struct FMetahumanMassCrowdActorTag : public FMassTag`  
_L13-16_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag added to Mass entities whose high-res actor implements IMetahumanMassCrowdActorBlueprintInterface. Used to filter entities that have a player-controllable or interface-driven actor representation.

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/MetaHumanMassCrowdVisualizationTrait.h` (Public)


#### class `UMetaHumanMassCrowdVisualizationTrait`  
`class UMetaHumanMassCrowdVisualizationTrait : public UMassVisualizationTrait`  
_L15-55_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta=(DisplayName="MetaHuman Crowd Visualization"))`
- inherits: `UMassVisualizationTrait`
- L21 _public member_ `TArray<TObjectPtr<UMetaHumanInstance>> CharacterInstances;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — MetaHuman Instance descriptions to use. Entities will be assigned an instance to use for their appearance
- L34 _public member_ `TSubclassOf<UMetaHumanCrowdAppearanceProvider> AppearanceProviderClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Optional procedural appearance provider class. This allows you to generate MetaHuman Instances procedurally at runtime. If this is set, AcquireAppearance will be called on it before spawning each entity. If CharacterInstances contains any Instances, they will be pre-registered so AcquireAppearance can return handles to them without needing to register them first.
- L40 _public member_ `int32 SteadyStateTracksPerSequence = 3;` — `UPROPERTY(EditAnywhere, Category = "Mass|Animation Scalability", meta=(ClampMin="1", ClampMax="20"))` — Number of steady-state (phase-offset) tracks per animation sequence. More tracks = more phase variety in looping crowds, but more GPU memory. Min 1 = full lockstep.
- L45 _public member_ `int32 MaxBlendTracks = 50;` — `UPROPERTY(EditAnywhere, Category = "Mass|Animation Scalability", meta=(ClampMin="0", UIMin="0", UIMax="100"))` — Maximum number of temporary blend tracks across all entities for this ISKM. When exhausted, entities snap directly to steady-state (no blend).
- L49 _public member_ `float AnimBlendTime = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Mass|Animation Scalability", meta=(ClampMin="0.0", UIMin="0.0", UIMax="2.0"))` — Duration in seconds of the crossfade blend when an entity changes animation sequence.
- L51 _public prototype_ `UMetaHumanMassCrowdVisualizationTrait();`
- L53 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L54 _public prototype_ `virtual void SanitizeMeshParams(FMassRepresentationParameters& InOutParams, const bool bStaticMeshDeterminedInvalid = false, const bool bSkinnedMeshDeterminedInvalid = false) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/MetaHumanMassFragments.h` (Public)


#### struct `FMetaHumanAppearanceSharedFragment`  
`struct FMetaHumanAppearanceSharedFragment : public FMassSharedFragment`  
_L13-32_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L24 _public member_ `TArray<uint32> AssignedAppearanceIndices;` — `UPROPERTY(Transient)` — Pre-baked array of appearance indices, populated from UMetaHumanMassCrowdVisualizationTrait::CharacterInstances. Empty when the trait is using an AppearanceProviderClass instead.
- L27 _public member_ `uint32 CurrentIndex = 0;` — `UPROPERTY(Transient)`
- L31 _public member_ `TSubclassOf<UMetaHumanCrowdAppearanceProvider> ProviderClass;` — `UPROPERTY(Transient)` — Optional procedural appearance provider

#### struct `FMetaHumanMassIdentityFragment`  
`struct FMetaHumanMassIdentityFragment : public FMassFragment`  
_L35-44_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L40 _public member_ `static constexpr uint32 InvalidAppearanceIndex = TNumericLimits<uint32>::Max();` — Sentinel value for AppearanceIndex meaning "no appearance assigned".
- L43 _public member_ `uint32 AppearanceIndex = InvalidAppearanceIndex;` — `UPROPERTY(Transient)`

#### struct `FMetaHumanMassAnimationScalabilitySharedFragment`  
`struct FMetaHumanMassAnimationScalabilitySharedFragment : public FMassSharedFragment`  
_L52-84_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- desc: Shared fragment for animation track pool scalability parameters. Set by the visualization trait, consumed by processors and the visualization component. A scalability system could adjust these at runtime to trade quality for performance.
- L60 _public member_ `int32 SteadyStateTracksPerSequence = 3;` — `UPROPERTY(EditAnywhere, Category = "Animation|Scalability", meta=(ClampMin="1", ClampMax="20"))` — Number of steady-state (phase-offset) tracks per animation sequence. More tracks = more phase variety in looping crowds, but more GPU memory. Min 1 = full lockstep.
- L65 _public member_ `int32 MaxBlendTracks = 50;` — `UPROPERTY(EditAnywhere, Category = "Animation|Scalability", meta=(ClampMin="0"))` — Maximum number of temporary blend tracks across all entities for this ISKM. When exhausted, entities snap directly to steady-state (no blend).
- L69 _public member_ `float AnimBlendTime = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Animation|Scalability", meta=(ClampMin="0.0"))` — Duration in seconds of the crossfade blend when an entity changes animation sequence.
- L71 _public function_ `bool operator==(const FMetaHumanMassAnimationScalabilitySharedFragment& Other) const`

#### struct `FMetaHumanMassTargetLocationFragment`  
`struct FMetaHumanMassTargetLocationFragment : public FMassFragment`  
_L94-101_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: This fragment is only used for MH Crowd Perf. This way it avoids any potential issues with traits that might read this data. We should consider using FMassMoveTargetFragment or similar existing fragments.
- L99 _public member_ `FVector TargetLocation = FVector::ZeroVector;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L78 _function_ `friend uint32 GetTypeHash(const FMetaHumanMassAnimationScalabilitySharedFragment& Fragment)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/Mass/MetaHumanMassRepresentationSubsystem.h` (Public)


#### struct `FMetaHumanMassInstanceRepresentation`  
`struct FMetaHumanMassInstanceRepresentation`  
_L33-58_
- reflection: `USTRUCT()`
- desc: Links a UMetaHumanInstance to its ISKM visualization description.
- L37 _public member_ `FSkinnedMeshInstanceVisualizationDescHandle DescHandle;`
- L40 _public member_ `TObjectPtr<UMetaHumanInstance> SourceInstance;` — `UPROPERTY()`
- L43 _public member_ `TArray<TArray<float>> CustomDataFloatsPerMesh;` — Per-instance custom-data float slices for this appearance, indexed in Desc.Meshes order.
- L48 _public member_ `int32 EntityRefCount = 0;` — Number of live entities currently using this appearance.
- L54 _public member_ `bool bPendingRelease = false;` — If true, the provider has called UnregisterInstance and the entry will be physically released as soon as EntityRefCount reaches zero.
- L57 _public member_ `bool bIsFreeSlot = false;` — True for slots that have been physically released and are awaiting reuse.

#### struct `FMetaHumanMassInstanceRegistryData`  
`struct FMetaHumanMassInstanceRegistryData`  
_L64-69_
- reflection: `USTRUCT()`
- desc: Registry of all MetaHuman instance-to-representation mappings.
- L68 _public member_ `TArray<FMetaHumanMassInstanceRepresentation> InstanceRepresentations;`

#### class `UMetaHumanMassRepresentationSubsystem`  
`class UMetaHumanMassRepresentationSubsystem : public UMassRepresentationSubsystem`  
_L78-202_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRepresentationSubsystem`
- desc: Subsystem responsible for all visual of MetaHuman Mass agents. Extends the engine MassRepresentationSubsystem (which now has native ISKM support) with MetaHuman-specific functionality: MHI registry, appearance management, etc.
- L83 _public prototype_ `virtual void Deinitialize() override;`
- L88 _public prototype_ `FSkinnedMeshInstanceVisualizationDescHandle GetSkinnedMeshInstanceByAppearanceId(uint32 AppearanceId) const;` — Get the matching ISKM visualization handle for a given appearance ID.
- L93 _public prototype_ `UMetaHumanInstance* GetMetaHumanInstanceByAppearanceId(uint32 AppearanceId) const;` — Get the matching MHI for a given appearance ID.
- L95 _public prototype_ `TArray<uint32> InitializeMetaHumanInstanceRegistry(const TArray<UMetaHumanInstance*>& InstanceData);`
- L105 _public prototype_ `const TArray<TArray<float>>& GetCustomDataFloatsPerMesh(uint32 AppearanceId) const;` — Per-mesh custom-data slices for the appearance, indexed in Desc.Meshes order. IMPORTANT: the returned reference points into registry storage. RegisterInstance and UnregisterInstance may reallocate that storage, invalidating the reference. Callers must not hold the reference across any subsystem mutation -- read it, use it immediately, and drop it. The empty-result reference points into a function-local static and is always safe.
- L115 _public prototype_ `FMetaHumanCrowdAppearanceHandle RegisterInstance(UMetaHumanInstance* Instance);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Crowd")` — Register a UMetaHumanInstance with the appearance registry. If the MHI hasn't been assembled yet, it will be assembled synchronously. Repeated calls with the same MHI return the same handle.
- L127 _public prototype_ `void UnregisterInstance(FMetaHumanCrowdAppearanceHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Crowd")` — Mark a handle obtained from RegisterInstance as no longer needed. If no entities are currently using this appearance the underlying registration is released immediately, otherwise release is deferred until the last entity carrying this appearance is destroyed. After this call the handle is no longer guaranteed to be valid.
- L131 _public prototype_ `bool IsValidAppearanceHandle(FMetaHumanCrowdAppearanceHandle Handle) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Crowd")` — True if Handle currently refers to a registered, non-released appearance entry.
- L135 _public prototype_ `UMetaHumanInstance* GetInstanceForHandle(FMetaHumanCrowdAppearanceHandle Handle) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Crowd")` — Returns the UMetaHumanInstance associated with Handle, or nullptr if Handle is invalid.
- L140 _public prototype_ `void OnEntityAssignedAppearance(uint32 AppearanceId);` — Internal: increment the entity refcount on the given appearance entry.
- L145 _public prototype_ `void OnEntityReleasedAppearance(uint32 AppearanceId);` — Internal: decrement the entity refcount on the given appearance entry.
- L150 _public prototype_ `UMetaHumanCrowdAppearanceProvider* GetOrCreateProvider( TSubclassOf<UMetaHumanCrowdAppearanceProvider> ProviderClass, const TArray<UMetaHumanInstance*>& PreRegisteredInstances = TArray<UMetaHumanInstance*>());` — Returns the provider object for the given class, owned by this subsystem.
- L155 _public prototype_ `UMetaHumanCrowdAppearanceProvider* GetExistingProvider(TSubclassOf<UMetaHumanCrowdAppearanceProvider> ProviderClass) const;` — Returns an existing provider for the given class without creating one.
- L164 _public prototype_ `FMetaHumanCrowdAppearanceHandle TryGetAppearanceHandleForInstance(UMetaHumanInstance* Instance) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Crowd")` — Look up the appearance handle for an already-registered MetaHuman Instance. Returns an invalid handle if the MHI is not currently registered with the subsystem, or if the registered entry has been marked for release.
- L168 _public prototype_ `TConstArrayView<FName> GetMeshRolesForDesc(FSkinnedMeshInstanceVisualizationDescHandle Handle) const;` — Role tag (Face / Body / Groom / Outfit) per Desc.Meshes entry; empty view for unknown handles.
- L173 _protected member_ `FMetaHumanMassInstanceRegistryData InstanceRegistryData;` — `UPROPERTY(Transient)`
- L176 _protected member_ `TMap<uint32, int32> NumCustomDataFloatsByMeshHash;` — Per-mesh-Desc-hash -> per-instance custom-data float count. Source of truth for the registry-time consistency assertion.
- L179 _protected member_ `TArray<int32> FreeRegistrySlots;` — Indices into InstanceRegistryData.InstanceRepresentations whose slots have been freed and are available for reuse.
- L183 _protected member_ `TMap<TObjectPtr<UClass>, TObjectPtr<UMetaHumanCrowdAppearanceProvider>> Providers;` — `UPROPERTY(Transient)` — Live providers, keyed by their UClass. Owned by this subsystem.
- L187 _protected member_ `TMap<int32, TArray<FName>> PerDescMeshRoles;` — Keyed by DescHandle.ToIndex() because FSkinnedMeshInstanceVisualizationDescHandle has no GetTypeHash.
- L195 _private prototype_ `int32 BuildAndAddInstanceRepresentation(UMetaHumanInstance* Instance);` — Append (or recycle) a registry entry for the given MHI. Returns the registry index, or INDEX_NONE on failure (invalid MHI / no assembly output).
- L198 _private prototype_ `int32 FindRegistryIndexForInstance(const UMetaHumanInstance* Instance) const;` — Locate an existing, non-free registry slot for the given MHI; INDEX_NONE if not found.
- L201 _private prototype_ `void ReleaseRegistryEntry(int32 RegistryIndex);` — Physically release the registry entry, removing the underlying ISKM visualization desc.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCROWD_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanMassRepresentation, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanMassRepresentation, Log, All);`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MetaHuman` (scope `UE`)
- L21 _namespace_ `namespace Crowd` (scope `UE::MetaHuman`)
- L21 _namespace_ `namespace ISKMRole` (scope `UE::MetaHuman::Crowd`)
- L23 _variable_ `inline const FName Face = TEXT("Fac` (scope `UE::MetaHuman::Crowd::ISKMRole`)
- L24 _variable_ `inline const FName Body = TEXT("Bod` (scope `UE::MetaHuman::Crowd::ISKMRole`)
- L25 _variable_ `inline const FName Groom = TEXT("Gro` (scope `UE::MetaHuman::Crowd::ISKMRole`)
- L26 _variable_ `inline const FName Outfit = TEXT("Out` (scope `UE::MetaHuman::Crowd::ISKMRole`)

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/MetaHumanCrowdModule.h` (Public)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/MetaHumanCrowdPipeline.h` (Public)


#### struct `FMetaHumanCrowdFaceSlotLODs`  
`struct FMetaHumanCrowdFaceSlotLODs`  
_L21-27_
- reflection: `USTRUCT()`
- L26 _public member_ `TArray<int32> SourceLODs;` — `UPROPERTY()`

#### struct `FMetaHumanCrowdCollectionHeadBuildOutput`  
`struct FMetaHumanCrowdCollectionHeadBuildOutput`  
_L30-71_
- reflection: `USTRUCT()`
- L36 _public member_ `TObjectPtr<USkeletalMesh> ActorFaceMesh;` — `UPROPERTY()`
- L39 _public member_ `TObjectPtr<USkeletalMesh> InstancedFaceMesh;` — `UPROPERTY()`
- L43 _public member_ `TObjectPtr<UAnimSequenceTransformProviderData> InstancedFaceMeshTransformProvider;` — `UPROPERTY()` — Pre-built ASTPD for the instanced face mesh (SkinnedAsset = InstancedFaceMesh, Sequences/Layers from BakedAnimRootProvider).
- L46 _public member_ `TObjectPtr<UAnimSequenceTransformProviderData> BakedAnimRootProvider;` — `UPROPERTY()`
- L49 _public member_ `FMetaHumanPaletteItemKey CompatibleBody;` — `UPROPERTY()`
- L58 _public member_ `TMap<FName, FMetaHumanCrowdFaceSlotLODs> ActorFaceSlotSourceLODs;` — `UPROPERTY()` — Per-slot list of source face-LOD indices the slot serves on the actor face mesh. Computed at build time so AssembleCollection can decide whether a {WardrobeSlot}AttributeMap write actually applies to a given face MID (the AttributeMap binds at face LODs >= MinBakedGroom- LOD; slots whose LOD coverage doesn't intersect that range should skip the write).
- L62 _public member_ `TMap<FName, FMetaHumanCrowdFaceSlotLODs> InstancedFaceSlotSourceLODs;` — `UPROPERTY()` — See ActorFaceSlotSourceLODs; same meaning, instanced face mesh.
- L70 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> InstancedFaceSourceMICs;` — `UPROPERTY()` — Snapshot of the instanced face mesh's per-slot MIC after ApplySlotMaterialOverrides has reparented runtime-MID slots. Consumed by BuildFaceMICCombos as the parent for the generated combo MICs. Keys mirror FaceMaterialSlotsForRuntimeMID.

#### struct `FMetaHumanCrowdGroomFaceParameterBinding`  
`struct FMetaHumanCrowdGroomFaceParameterBinding`  
_L86-109_
- reflection: `USTRUCT()`
- desc: Per-(groom, head) face-side parameter binding emitted by the editor pipeline. At runtime the collection's AssembleCollection / SetPostAssemblyParameters reads these and writes the values onto the per-instance face MIDs (FMetaHumanCrowdAssemblyOutput::Actor/InstancedFaceMaterialOverrides), giving runtime control over hair color and the {WardrobeSlot}AttributeMap binding for grooms that use baked-groom textures on the face material. Each entry is a parallel of the groom's RuntimeMaterialParameters with MaterialParameter.Name rewritten to "{WardrobeSlot}{OriginalName}" (e.g. "HairMelanin") and SlotNames pointing at the face slots wrapped by FaceMaterialSlotsForRuntimeMID. The InstanceParameterName is unchanged so a single user-facing slider drives both the groom's own MID and the face MID.
- L93 _public member_ `FMetaHumanPaletteItemPath GroomItemPath;` — `UPROPERTY()` — Groom item path this binding belongs to.
- L97 _public member_ `FMetaHumanPaletteItemKey HeadItemKey;` — `UPROPERTY()` — Head item this groom binds to. Used to find the right face MID at runtime.
- L104 _public member_ `FName PipelineSlotName;` — `UPROPERTY()` — Pipeline slot the groom lives in (e.g. "Hair", "Beard"); used as a parameter-name prefix and to compute the {WardrobeSlot}AttributeMap parameter.
- L108 _public member_ `TArray<FMetaHumanMaterialParameter> Parameters;` — `UPROPERTY()` — Material parameters with prefixed names targeting the face slots.

#### struct `FMetaHumanCrowdFaceMICComboSlot`  
`struct FMetaHumanCrowdFaceMICComboSlot`  
_L115-135_
- reflection: `USTRUCT()`
- desc: Single (pipeline slot, equipped-groom key) entry inside FMetaHumanCrowdFaceMICComboKey.
- L121 _public member_ `FName PipelineSlotName;` — `UPROPERTY()`
- L124 _public member_ `FMetaHumanPaletteItemKey EquippedGroomKey;` — `UPROPERTY()`
- L126 _public function_ `bool operator==(const FMetaHumanCrowdFaceMICComboSlot& Other) const`

#### struct `FMetaHumanCrowdFaceMICComboKey`  
`struct FMetaHumanCrowdFaceMICComboKey`  
_L147-164_
- reflection: `USTRUCT()`
- desc: Identifies a (head, equipped-grooms) combination that drives a unique face MIC set. EquippedGrooms is sorted by slot name for stable hashing and equality. A default-constructed EquippedGroomKey means "no groom equipped in this slot". Built by the editor pipeline by enumerating across face-affecting slots, looked up at runtime by AssembleCollection to share face MaterialInterface pointers across UMetaHumanInstances.
- L153 _public member_ `FMetaHumanPaletteItemKey HeadKey;` — `UPROPERTY()`
- L156 _public member_ `TArray<FMetaHumanCrowdFaceMICComboSlot> EquippedGrooms;` — `UPROPERTY()`
- L158 _public function_ `bool operator==(const FMetaHumanCrowdFaceMICComboKey& Other) const`

#### struct `FMetaHumanCrowdFaceMICSet`  
`struct FMetaHumanCrowdFaceMICSet`  
_L171-182_
- reflection: `USTRUCT()`
- desc: Pre-baked face MICs for one (head, groom combo) pair. Actor and instanced variants are stored separately because each has its own source MIC identity (per ApplySlotMaterialOverrides).
- L181 _public member_ `TMap<FName, TObjectPtr<UMaterialInstanceConstant>> InstancedSlotToMIC;` — `UPROPERTY()` — Per-face-slot shared MIC for the instanced (ISKM) variant, assigned directly at AssembleCollection time.

#### struct `FMetaHumanCrowdCollectionBuildOutput`  
`struct FMetaHumanCrowdCollectionBuildOutput`  
_L186-253_
- reflection: `USTRUCT()`
- desc: Build output for the collection pipeline itself (not per-item).
- L193 _public member_ `bool bBodyGeometryMergedOntoClothing = false;` — `UPROPERTY()` — If true, body geometry has been merged onto clothing meshes during the collection build.
- L201 _public member_ `TMap<FName, TObjectPtr<UAnimSequence>> SharedAnimBPAnimations;` — `UPROPERTY()` — Merged animations (body bone tracks + face curves) shared across all characters. Keyed by FMetaHumanCrowdBakeAnimationData::Name from the animation config. Anim BPs read the equivalent map on FMetaHumanCrowdAssemblyOutput to drive character animation.
- L209 _public member_ `TArray<FName> FaceMaterialSlotsForRuntimeMID;` — `UPROPERTY()` — Face material slot names that the editor pipeline reparented during ApplyFaceMaterialOverrides. Runtime AssembleCollection wraps the face MIC at each of these slots in a UMaterialInstanceDynamic so per-MetaHuman parameter writes (hair color, etc.) can drive the face material.
- L217 _public member_ `TArray<FMetaHumanCrowdGroomFaceParameterBinding> GroomFaceParameterBindings;` — `UPROPERTY()` — Per-(groom, head) parameter bindings driving the face material at runtime. See FMetaHumanCrowdGroomFaceParameterBinding for the per-entry shape and the routing flow. Empty when no grooms target face slots in FaceMaterialSlotsForRuntimeMID.
- L232 _public member_ `TMap<FName, FMetaHumanCrowdOutfitInstancedMaterial> FaceSlotCustomDataLayout;` — `UPROPERTY()` — Per face slot, the parameter-name -> custom-data-offset format map authored on the editor pipeline's FaceMaterialOverrides[i].InstanceParameterNameToCustomDataFormat. Captured at build time so the runtime AssembleCollection can write per-instance face colour parameters into the face ISKM's custom-data buffer without round-tripping back to the editor pipeline. Keys are face material slot names (matching FaceMaterialSlotsForRuntimeMID). Values are the same shape as FMetaHumanCrowdOutfitInstancedMaterial::InstanceParameterNameToCustomDataFormat so the existing MaterialUtils::SetInstanceParametersOnCustomData path can be reused.
- L240 _public member_ `TArray<FName> FaceAffectingPipelineSlots;` — `UPROPERTY()` — Pipeline slot names that participate in the face-MIC combo enumeration, sorted alphabetically. Recorded at build time so the runtime knows which slots to read from Params.SlotSelections when constructing the FaceMICsByCombo lookup key.
- L252 _public member_ `TMap<FMetaHumanCrowdFaceMICComboKey, FMetaHumanCrowdFaceMICSet> FaceMICsByCombo;` — `UPROPERTY()` — Pre-baked face MICs keyed by (head, equipped-grooms) combo. Replaces the per-Assemble face MID creation: at runtime, AssembleCollection looks up the MIC set for the current selection and assigns it directly to {Actor,Instanced}FaceMaterialOverrides. The shared MaterialInterface pointer across UMetaHumanInstances with the same combo lets the Mass ISKM subsystem batch them into a single ISKMC. Populated by UMetaHumanCrowdEditorPipeline::BuildFaceMICCombos.

#### struct `FMetaHumanCrowdCollectionBodyBuildOutput`  
`struct FMetaHumanCrowdCollectionBodyBuildOutput`  
_L257-272_
- reflection: `USTRUCT()`
- desc: Collection-level build output for a body item.
- L263 _public member_ `TObjectPtr<USkeletalMesh> ActorBodyMesh;` — `UPROPERTY()`
- L267 _public member_ `TObjectPtr<USkeletalMesh> InstancedBodyMesh;` — `UPROPERTY()` — nullptr when body geometry has been merged onto clothing meshes.
- L271 _public member_ `TObjectPtr<UAnimSequenceTransformProviderData> InstancedBodyMeshTransformProvider;` — `UPROPERTY()` — Pre-built ASTPD for the instanced body mesh. nullptr when InstancedBodyMesh is nullptr.

#### struct `FMetaHumanCrowdCollectionOutfitBuildOutput`  
`struct FMetaHumanCrowdCollectionOutfitBuildOutput`  
_L276-290_
- reflection: `USTRUCT()`
- desc: Collection-level build output for an outfit item.
- L282 _public member_ `TMap<FMetaHumanPaletteItemKey, TObjectPtr<USkeletalMesh>> BodyToActorOutfitMeshMap;` — `UPROPERTY()`
- L285 _public member_ `TMap<FMetaHumanPaletteItemKey, TObjectPtr<USkeletalMesh>> BodyToInstancedOutfitMeshMap;` — `UPROPERTY()`
- L289 _public member_ `TMap<FMetaHumanPaletteItemKey, TObjectPtr<UAnimSequenceTransformProviderData>> BodyToInstancedOutfitTransformProviderMap;` — `UPROPERTY()` — Pre-built ASTPDs for the instanced outfit meshes, keyed by the same body item key as BodyToInstancedOutfitMeshMap.

#### struct `FMetaHumanCrowdCollectionGroomBuildOutput`  
`struct FMetaHumanCrowdCollectionGroomBuildOutput`  
_L294-325_
- reflection: `USTRUCT()`
- desc: Collection-level build output for a groom item.
- L300 _public member_ `TMap<FMetaHumanPaletteItemKey, TObjectPtr<USkeletalMesh>> ItemToActorGroomMeshMap;` — `UPROPERTY()`
- L303 _public member_ `TMap<FMetaHumanPaletteItemKey, TObjectPtr<USkeletalMesh>> ItemToInstancedGroomMeshMap;` — `UPROPERTY()`
- L307 _public member_ `TMap<FMetaHumanPaletteItemKey, TObjectPtr<UAnimSequenceTransformProviderData>> ItemToInstancedGroomTransformProviderMap;` — `UPROPERTY()` — Pre-built ASTPDs for the instanced groom meshes, keyed by the same head item key as ItemToInstancedGroomMeshMap.
- L316 _public member_ `TMap<FMetaHumanPaletteItemKey, FMetaHumanCrowdGroomBakedTextureEntry> ItemToBakedGroomTexture;` — `UPROPERTY()` — Per-(groom, head) baked groom texture entries surfaced from the item-level FMetaHumanCrowdGroomBuildOutput::ItemToBakedGroomTexture. Promoted to the collection-level output so runtime AssembleCollection can resolve the texture for each equipped groom; the item-level groom build data is consumed and discarded during integration.
- L324 _public member_ `FName PipelineSlotName;` — `UPROPERTY()` — Pipeline slot the groom lives in (e.g. "Hair", "Beard"). Surfaced from the item-level FMetaHumanCrowdGroomBuildOutput so runtime AssembleItem can scope the PostAssemblyParameters bag's keys with the slot suffix.

#### struct `FMetaHumanCrowdActorClothingAssemblyOutput`  
`struct FMetaHumanCrowdActorClothingAssemblyOutput`  
_L328-339_
- reflection: `USTRUCT(BlueprintType)`
- L334 _public member_ `TObjectPtr<class USkeletalMesh> OutfitMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L338 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — MID overrides, keyed by material slot name.

#### struct `FMetaHumanCrowdInstancedClothingAssemblyOutput`  
`struct FMetaHumanCrowdInstancedClothingAssemblyOutput`  
_L342-364_
- reflection: `USTRUCT(BlueprintType)`
- L348 _public member_ `TObjectPtr<class USkeletalMesh> OutfitMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L352 _public member_ `TObjectPtr<class UAnimSequenceTransformProviderData> TransformProvider;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Pre-built ASTPD for this outfit mesh.
- L355 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> InstancedMaterialData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L363 _public member_ `TArray<float> InstancedMeshCustomDataFloats;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — ISKM-wide per-instance custom data float buffer (single flat array shared across all material slots on this ISKM). See FMetaHumanCrowdOutfitAssemblyOutput::InstancedMeshCustomDataFloats for offset semantics.

#### struct `FMetaHumanCrowdActorGroomAssemblyOutput`  
`struct FMetaHumanCrowdActorGroomAssemblyOutput`  
_L367-378_
- reflection: `USTRUCT(BlueprintType)`
- L373 _public member_ `TObjectPtr<USkeletalMesh> CardsMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L377 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — MID overrides, keyed by material slot name.

#### struct `FMetaHumanCrowdInstancedGroomAssemblyOutput`  
`struct FMetaHumanCrowdInstancedGroomAssemblyOutput`  
_L381-403_
- reflection: `USTRUCT(BlueprintType)`
- L387 _public member_ `TObjectPtr<USkeletalMesh> CardsMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L391 _public member_ `TObjectPtr<class UAnimSequenceTransformProviderData> TransformProvider;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Pre-built ASTPD for this groom cards mesh.
- L394 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> InstancedMaterialData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L402 _public member_ `TArray<float> InstancedMeshCustomDataFloats;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — ISKM-wide per-instance custom data float buffer (single flat array shared across all material slots on this ISKM). See FMetaHumanCrowdOutfitAssemblyOutput::InstancedMeshCustomDataFloats for offset semantics.

#### struct `FMetaHumanCrowdAssemblyOutput`  
`struct FMetaHumanCrowdAssemblyOutput`  
_L406-487_
- reflection: `USTRUCT(BlueprintType)`
- L414 _public member_ `TObjectPtr<class USkeletalMesh> ActorFaceMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actor")`
- L417 _public member_ `TObjectPtr<class USkeletalMesh> ActorBodyMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actor")`
- L420 _public member_ `TArray<FMetaHumanCrowdActorClothingAssemblyOutput> ActorClothing;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actor")`
- L423 _public member_ `TArray<FMetaHumanCrowdActorGroomAssemblyOutput> ActorGrooms;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actor")`
- L428 _public member_ `TObjectPtr<class USkeletalMesh> InstancedFaceMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instanced")`
- L432 _public member_ `TObjectPtr<class UAnimSequenceTransformProviderData> InstancedFaceMeshTransformProvider;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instanced")` — Pre-built ASTPD for the instanced face mesh.
- L435 _public member_ `TObjectPtr<class USkeletalMesh> InstancedBodyMesh;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instanced")`
- L439 _public member_ `TObjectPtr<class UAnimSequenceTransformProviderData> InstancedBodyMeshTransformProvider;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instanced")` — Pre-built ASTPD for the instanced body mesh.
- L442 _public member_ `TArray<FMetaHumanCrowdInstancedClothingAssemblyOutput> InstancedClothing;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instanced")`
- L445 _public member_ `TArray<FMetaHumanCrowdInstancedGroomAssemblyOutput> InstancedGrooms;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instanced")`
- L451 _public member_ `bool bIsBodyMeshVisible = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — True if the body mesh needs to be shown, false if the body geometry has been merged onto the clothing meshes
- L454 _public member_ `TObjectPtr<class UAnimSequenceTransformProviderData> BakedAnimRootProvider;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")`
- L462 _public member_ `TMap<FName, TObjectPtr<UAnimSequence>> AnimBPAnimations;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Merged animations (body bone tracks + face curves) keyed by animation name. Counterpart to BakedAnimRootProvider for non-ISKM playback: Anim BPs read this map to drive the character with a full animation graph rather than GPU ISKM sequences. Shared across every character in the collection.
- L472 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> ActorFaceMaterialOverrides;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Per-instance face MIDs for the actor face mesh, keyed by face material slot name. Created by AssembleCollection by wrapping each MIC named in FMetaHumanCrowdCollectionBuildOutput::FaceMaterialSlotsForRuntimeMID; lets per-MetaHuman parameter writes (hair color, etc.) drive the face material at runtime. Empty when no face slots were reparented at build time.
- L476 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> InstancedFaceMaterialOverrides;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Per-instance face MIDs for the instanced face mesh. Same shape as ActorFaceMaterialOverrides.
- L486 _public member_ `TArray<float> InstancedFaceMeshCustomDataFloats;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Build")` — Per-instance custom-data float buffer for the instanced face ISKM. Single flat array shared across every face material slot; per-slot offsets defined by FMetaHumanCrowdCollectionBuildOutput::FaceSlotCustomDataLayout. Written by AssembleCollection from the equipped grooms' assembly parameter bags via FMetaHumanCrowdGroomFaceParameterBinding. Empty when no face slot has a custom-data layout.

#### class `UMetaHumanCrowdPipeline`  
`class UMetaHumanCrowdPipeline : public UMetaHumanCollectionPipeline`  
_L490-586_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew)`
- inherits: `UMetaHumanCollectionPipeline`
- L495 _public prototype_ `UMetaHumanCrowdPipeline();`
- L498 _public prototype_ `virtual void SetDefaultEditorPipeline() override;`
- L499 _public prototype_ `virtual const UMetaHumanCollectionEditorPipeline* GetEditorPipeline() const override;`
- L500 _public prototype_ `virtual UMetaHumanCollectionEditorPipeline* GetMutableEditorPipeline() override;`
- L503 _public prototype_ `virtual void AssembleCollection(const FAssembleCollectionParams& Params, const FOnAssemblyComplete& OnComplete) const override;`
- L505 _public prototype_ `virtual bool AreSlotSelectionsAllowed( TNotNull<const UMetaHumanCollection*> Collection, TArrayView<const FMetaHumanPipelineSlotSelection> SlotSelections, FText& OutDisallowedReason) const override;`
- L510 _public function_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const override`
- L515 _public prototype_ `virtual const UMetaHumanItemPipeline* GetFallbackItemPipelineForAssetType(const TSoftClassPtr<UObject>& InAssetClass) const override;`
- L517 _public prototype_ `virtual TSubclassOf<AActor> GetActorClass() const override;`
- L519 _public member_ `static const FName HeadSlotName;`
- L520 _public member_ `static const FName BodySlotName;`
- L521 _public member_ `static const FName OutfitsSlotName;`
- L522 _public member_ `static const FName TopGarmentSlotName;`
- L523 _public member_ `static const FName BottomGarmentSlotName;`
- L524 _public member_ `static const FName ShoesSlotName;`
- L526 _public prototype_ `virtual void SetPostAssemblyParameters( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, FInstancedStruct& InOutCollectionAssemblyOutput) const override;`
- L539 _protected prototype_ `void ApplyGroomFaceParameterBindings( const FAssembleCollectionParams& Params, const FMetaHumanPaletteItemKey& HeadItemKey, const FMetaHumanCrowdCollectionBuildOutput& CollectionBuildOutput, const FMetaHumanCrowdCollectionHeadBuildOutput& HeadBuildOutput, FMetaHumanCrowdAssemblyOutput& AssemblyOutput) const;` — Full sync pass: writes the AttributeMap texture and color parameters onto the per-instance face MIDs for every (groom, head) binding. Equipped grooms get their textures and colors applied; non-equipped grooms get their AttributeMap cleared.
- L553 _protected prototype_ `void ApplyGroomFaceParametersForBag( const FMetaHumanCrowdCollectionBuildOutput& CollectionBuildOutput, const FMetaHumanPaletteItemPath& GroomItemPath, const FInstancedPropertyBag& ParameterBag, FMetaHumanCrowdAssemblyOutput& AssemblyOutput) const;` — Parameter-only update: applies color parameters from the given property bag onto the face MIDs for a single groom binding. AttributeMap textures are not touched (equip state is unchanged from the last AssembleCollection). Called from SetPostAssemblyParameters when the user edits a groom's parameters.
- L559 _protected prototype_ `virtual FInstancedStruct GetItemAssemblyOutputValue( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, const FInstancedStruct& InCollectionAssemblyOutput) const override;`
- L566 _protected prototype_ `virtual void SetItemAssemblyOutputValue( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, FInstancedStruct&& ItemAssemblyOutput, FInstancedStruct& InOutCollectionAssemblyOutput) const override;`
- L577 _private member_ `TObjectPtr<UMetaHumanCollectionEditorPipeline> EditorPipeline;` — `UPROPERTY(EditAnywhere, NoClear, Instanced, Category = "Character", meta = (FullyExpand, AllowedClasses = "/Script/MetaHumanCrowdEditor.MetaHumanCrowdEditorPipeline"))`
- L582 _private member_ `TObjectPtr<UMetaHumanCharacterPipelineSpecification> Specification;` — `UPROPERTY(Transient)` — The specification that this pipeline implements
- L585 _private member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, Category = "Character", meta = (MustImplement = "/Script/MetaHumanCharacterPalette.MetaHumanCharacterActorInterface"))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANCROWD_API`
- L131 _function_ `friend uint32 GetTypeHash(const FMetaHumanCrowdFaceMICComboSlot& In)`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/MetaHumanCrowdStatsLibrary.h` (Public)


#### struct `FMetaHumanCrowdStats`  
`struct FMetaHumanCrowdStats`  
_L17-36_
- reflection: `USTRUCT(BlueprintType)`
- desc: Lightweight stats about a MetaHuman crowd
- L23 _public member_ `int32 NumEntities = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Crowd|Debug")` — Total number of MetaHuman crowd entities currently alive.
- L27 _public member_ `int32 NumVisible = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Crowd|Debug")` — Number of entities currently on screen: in LOD range AND inside the view frustum.
- L31 _public member_ `int32 NumActors = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Crowd|Debug")` — Number of entities currently visualized as a spawned actor.
- L35 _public member_ `int32 NumISKMs = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Crowd|Debug")` — Number of entities currently visualized as an instanced skinned mesh.

#### class `UMetaHumanCrowdStatsLibrary`  
`class UMetaHumanCrowdStatsLibrary : public UBlueprintFunctionLibrary`  
_L43-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for MetaHuman crowd statistics
- L54 _public prototype_ `static FMetaHumanCrowdStats GatherMetaHumanCrowdStats(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Crowd|Debug", meta = (WorldContext = "WorldContextObject"))` — Gather a snapshot of MetaHuman crowd statistics. Reads cached per-entity state already maintained by the Mass visualization pipeline.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCROWD_API`

### `Plugins/MetaHuman/MetaHumanCrowd/Source/MetaHumanCrowd/Public/MetaHumanCrowdTypes.h` (Public)


#### struct `FMetaHumanCrowdMeshGeometryBundle`  
`struct FMetaHumanCrowdMeshGeometryBundle`  
_L17-34_
- reflection: `USTRUCT()`
- desc: A geometry bundle containing the raw data needed to construct a USkeletalMesh. Item pipelines produce these; the collection pipeline constructs final meshes from them.
- L23 _public member_ `TArray<FMeshDescription> MeshDescriptions;` — Mesh descriptions, one per LOD. Indices match the source mesh LOD indices.
- L26 _public member_ `FReferenceSkeleton RefSkeleton;` — Reference skeleton. May differ from the source if fitting adjusted bone poses.
- L30 _public member_ `TArray<FSkeletalMaterial> Materials;` — `UPROPERTY()` — Materials from the source asset, used during mesh construction.
- L33 _public member_ `TArray<TArray<int32>> LODMaterialMaps;` — Per-LOD section->material remap, mirroring USkeletalMesh::FSkeletalMeshLODInfo::LODMaterialMap.
