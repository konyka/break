# Plugins / MassRepresentation

- module root: `Plugins/Runtime/MassGameplay/Source/MassRepresentation`
- headers: 24; symbols: 703
- symbol kinds: class=20, delegate=1, enum=5, enumerator=11, externvar=8, function=173, macro=19, member=209, namespace=23, prototype=174, struct=43, typedef=13, variable=4
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassActors, MassCommon, MassCore, MassEntity, MassLOD, MassMovement, MassReplication, MassSignals, MassSimulation, MassSpawner, RHI, RenderCore

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Private/StationaryVisualizationTraitUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mass` (scope `UE`)
- L9 _namespace_ `namespace LOD` (scope `UE::Mass`)
- L9 _namespace_ `namespace Private` (scope `UE::Mass::LOD`)
- L11 _prototype_ `void SetUpStationaryVisualizationTrait(const UMassEntityTraitBase& Trait, FMassEntityTemplateBuildContext& BuildContext, FStaticMeshInstanceVisualizationDesc& StaticMeshInstanceDesc);` (scope `UE::Mass::LOD::Private`)

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/IMassRepresentationModule.h` (Public)


#### class `IMassRepresentationModule`  
`class IMassRepresentationModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassRepresentationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassDistanceLODProcessor.h` (Public)


#### struct `FMassDistanceLODProcessorTag`  
`struct FMassDistanceLODProcessorTag : public FMassTag`  
_L20-23_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag required by Distance LOD Processor to update LOD information. Removing the tag allows to support temporary disabling of processing for individual entities.

#### class `UMassDistanceLODProcessor`  
`class UMassDistanceLODProcessor : public UMassProcessor`  
_L26-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L31 _public prototype_ `UMassDistanceLODProcessor();`
- L36 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L43 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L49 _protected function_ `void ForceOffLOD(bool bForce)` — Forces Off LOD on all calculation @param bForce to whether force or not Off LOD
- L52 _protected member_ `FMassEntityQuery CloseEntityQuery;`
- L53 _protected member_ `FMassEntityQuery FarEntityQuery;`
- L54 _protected member_ `FMassEntityQuery DebugEntityQuery;`
- L56 _protected member_ `bool bForceOFFLOD = false;`
- L59 _protected member_ `TObjectPtr<const UScriptStruct> FilterTag = nullptr;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassDistanceVisualizationTrait.h` (Public)


#### class `UMassDistanceVisualizationTrait`  
`class UMassDistanceVisualizationTrait : public UMassEntityTraitBase`  
_L19-70_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="DEPRECATED DistanceVisualization"))`
- inherits: `UMassEntityTraitBase`
- desc: This class has been soft-deprecated. Use MassStationaryVisualizationTrait or MassMovableVisualizationTrait
- L23 _public prototype_ `UMassDistanceVisualizationTrait();`
- L25 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L26 _public prototype_ `virtual void DestroyTemplate(const UWorld& World) const override;`
- L30 _public member_ `mutable FStaticMeshInstanceVisualizationDesc StaticMeshInstanceDesc;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Instanced static mesh information for this agent
- L34 _public member_ `TSubclassOf<AActor> HighResTemplateActor;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Actor class of this agent when spawned in high resolution
- L38 _public member_ `TSubclassOf<AActor> LowResTemplateActor;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Actor class of this agent when spawned in low resolution
- L42 _public member_ `TSubclassOf<UMassRepresentationSubsystem> RepresentationSubsystemClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta = (EditCondition = "bCanModifyRepresentationSubsystemClass"))` — Allow subclasses to override the representation subsystem to use
- L46 _public member_ `FMassRepresentationParameters Params;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Configuration parameters for the representation processor
- L50 _public member_ `FMassDistanceLODParameters LODParams;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Configuration parameters for the Distance LOD processor
- L55 _public member_ `bool bAllowServerSideVisualization = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — If set to true will result in the visualization-related fragments being added to server-size entities as well. By default only the clients require visualization fragments
- L60 _public member_ `bool bCanModifyRepresentationSubsystemClass = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|Visual")` — the property is marked like this to ensure it won't show up in UI
- L69 _protected member_ `bool bRegisterStaticMeshDesc = true;` — Controls whether StaticMeshInstanceDesc gets registered via FindOrAddStaticMeshDesc call. Setting it to `false` can be useful for subclasses to avoid needlessly creating visualization data in RepresentationSubsystem, data that will never be used.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassMovableVisualizationTrait.h` (Public)


#### class `UMassMovableVisualizationTrait`  
`class UMassMovableVisualizationTrait : public UMassVisualizationTrait`  
_L12-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassVisualizationTrait`
- L16 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationActorManagement.h` (Public)


#### class `UMassRepresentationActorManagement`  
`class UMassRepresentationActorManagement : public UObject`  
_L23-138_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L33 _public prototype_ `virtual float GetSpawnPriority(const FMassRepresentationLODFragment& Representation) const;` — Returns the spawn priority from the LOD @param Representation is the type of enabling to do on this actor
- L47 _public prototype_ `virtual AActor* GetOrSpawnActor(UMassRepresentationSubsystem& RepresentationSubsystem, FMassEntityManager& EntityManager , const FMassEntityHandle MassAgent, const FTransform& Transform, const int16 TemplateActorIndex , FMassActorSpawnRequestHandle& InOutSpawnRequestHandle, const float Priority) const;` — Returns an actor of the template type and setup fragments values from it @param RepresentationSubsystem to use to get or spawn the actor @param EntityManager associated to the mass agent @param MassAgent is the handle to the associated mass agent @param ActorInfo is the fragment where we are going to store the actor pointer @param Transform is the spatial information about where to spawn the actor @param TemplateActorIndex is the index of the type fetched with UMassRepresentationSubsystem::FindOrAddTemplateActor() @param SpawnRequestHandle (in/out) In: previously requested spawn Out: newly requested spawn @param Priority of this spawn request in comparison with the others, lower value means higher priority @return the actor spawned
- L58 _public prototype_ `virtual void SetActorEnabled(const EMassActorEnabledType EnabledType, AActor& Actor, const int32 EntityIdx, FMassCommandBuffer& CommandBuffer) const;` — Enable/disable a spawned actor for a mass entity @param EnabledType is the type of enabling to do on this actor @param Actor is the actual actor to perform enabling type on @param EntityIdx is the entity index currently processing @param CommandBuffer to queue up anything that is thread sensitive
- L67 _public prototype_ `virtual void TeleportActor(const FTransform& Transform, AActor& Actor, FMassCommandBuffer& CommandBuffer) const;` — Teleports the actor at the specified transform by preserving its velocity and without collision. The destination will be adjusted to fit an existing capsule. @param Transform is the new actor's transform @param Actor is the actual actor to teleport @param CommandBuffer to queue up anything that is thread sensitive
- L94 _public prototype_ `virtual bool IsActorReadyForRepresentation(const AActor& Actor) const;` — Returns whether the given actor is ready to be used as the visual representation of a Mass entity. The default implementation always returns true, preserving the original behavior of switching the representation as soon as UWorld::SpawnActor returns. Game-side subclasses should override this to keep the entity on its non-actor representation (typically StaticMeshInstance) while an asynchronously streamed asset (SkeletalMesh, StaticMesh, ...) is still being loaded by the spawned actor. Called from UMassRepresentationProcessor::UpdateRepresentation: while this returns false the actor stays disabled and the ISM/SkinnedMesh instance remains visible (via bIsWaitingForActorVisualReadiness). The wait is bounded by the cvar ai.massrepresentation.MaxActorVisualReadinessWaitFrames; after that cap the processor force-enables and logs a warning, so a buggy override doesn't strand entities. The hook also fires for externally-owned actors (those hydrated by replication or other non-Mass spawners) on the frame Mass first commits CurrentRepresentation to an actor type; once committed those actors don't re-enter the spawn switch on subsequent frames, so post-commit streaming changes are not gated. Note on dedicated servers: signals like AActor::WasRecentlyRendered will never report true on a server. Implementations should short-circuit to true when IsNetMode(NM_DedicatedServer) is true, otherwise entities will never leave the default representation server-side. @param Actor the just-spawned (
- L102 _public prototype_ `virtual void OnPreActorSpawn(const FMassActorSpawnRequestHandle& SpawnRequestHandle, FConstStructView SpawnRequest, TSharedRef<FMassEntityManager> EntityManager) const;` — Method that will be bound to a delegate called before the spawning of an actor to let the requester prepare it @param SpawnRequestHandle the handle of the spawn request that is about to spawn @param SpawnRequest of the actor that is about to spawn @param EntityManager to use to retrieve the mass agent fragments
- L111 _public prototype_ `virtual EMassActorSpawnRequestAction OnPostActorSpawn(const FMassActorSpawnRequestHandle& SpawnRequestHandle, FConstStructView SpawnRequest, TSharedRef<FMassEntityManager> EntityManager) const;` — Method that will be bound to a delegate used post-spawn to notify and let the requester configure the actor @param SpawnRequestHandle the handle of the spawn request that was just spawned @param SpawnRequest of the actor that just spawned @param EntityManager to use to retrieve the mass agent fragments @return The action to take on the spawn request, either keep it there or remove it.
- L122 _public prototype_ `static void ReleaseAnyActorOrCancelAnySpawning(FMassEntityManager& EntityManager, const FMassEntityHandle MassAgent, bool bImmediate = false);` — Static methods to Release an actor or cancel its spawning (calls ReleaseAnyActorOrCancelAnySpawning) WARNING: This method will destroy the associated actor in any and by the same fact might also move the entity into a new archetype. So any reference to fragment might become invalid. @param EntityManager to use to retrieve the mass agent fragments @param MassAgent is the handle to the associated mass agent @param bImmediate whether to perform the actor destruction immediately, otherwise it will be queued for processing later @return True if actor was release or spawning request was canceled
- L136 _public prototype_ `static void ReleaseAnyActorOrCancelAnySpawning(UMassRepresentationSubsystem& RepresentationSubsystem, const FMassEntityHandle MassAgent , FMassActorFragment& ActorInfo, FMassRepresentationFragment& Representation, UMassActorSubsystem* ActorSubsystem = nullptr, bool bImmediate = false);` — static Release an actor or cancel its spawning WARNING: This method will destroy the associated actor in any and by the same fact might also move the entity into a new archetype. So any reference to fragment might become invalid if you are not within the pipe execution @param RepresentationSubsystem to use to release any actors or cancel spawning requests @param MassAgent is the handle to the associated mass agent @param ActorInfo is the fragment where we are going to store the actor pointer @param Representation fragment containing the current and previous visual state @param ActorSubsystem passed over to FMassActorFragment::ResetAndUpdateHandleMap, used to avoid fetching the subsystem from UWorld every time. @param bImmediate whether to perform the actor destruction immediately, otherwise it will be queued for processing later

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationAnimationProcessor.h` (Public)


#### class `UMassConsumeInstancedSkinnedMeshAnimationProcessor`  
`class UMassConsumeInstancedSkinnedMeshAnimationProcessor : public UMassProcessor`  
_L19-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor's responsibility is to consume Animation Data generated by end user processors and forward it onto the Skinned Mesh this data will be batch updated in the Instanced Skinned Mesh Component
- L24 _public prototype_ `UMassConsumeInstancedSkinnedMeshAnimationProcessor();`
- L26 _public prototype_ `static void UpdateMeshAnimation(FMassEntityHandle EntityHandle, FMassInstancedSkinnedMeshInfo& MeshInfo, FAnimSequenceTrackAutoPlayData AnimationData, const float LODSignificance, const float PrevLODSignificance = -1.0f);`
- L31 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — UMassProcessor overrides begin
- L33 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L36 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationDebug.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mass` (scope `UE`)
- L17 _namespace_ `namespace Representation` (scope `UE::Mass`)
- L17 _namespace_ `namespace Debug` (scope `UE::Mass::Representation`)
- L19 _externvar_ `extern FColor RepresentationColors[];` (scope `UE::Mass::Representation::Debug`)
- L21 _externvar_ `extern int32 DebugRepresentation;` (scope `UE::Mass::Representation::Debug`)
- L22 _externvar_ `extern float DebugRepresentationMaxSignificance;` (scope `UE::Mass::Representation::Debug`)
- L24 _externvar_ `extern int32 DebugRepresentationLOD;` (scope `UE::Mass::Representation::Debug`)
- L25 _externvar_ `extern float DebugRepresentationLODMaxSignificance;` (scope `UE::Mass::Representation::Debug`)
- L27 _prototype_ `void DebugDisplayRepresentation(FMassExecutionContext& Context, TConstArrayView<FMassRepresentationLODFragment> RepresentationLODList, TConstArrayView<FMassRepresentationFragment> RepresentationList, TConstArrayView<FTransformFragment> LocationList, UWorld* World);` (scope `UE::Mass::Representation::Debug`)
- L29 _prototype_ `void VisLogRepresentation(FMassExecutionContext& Context, TConstArrayView<FMassRepresentationLODFragment> RepresentationLODList, TConstArrayView<FMassRepresentationFragment> RepresentationList, TConstArrayView<FTransformFragment> LocationList, UObject* LogOwner);` (scope `UE::Mass::Representation::Debug`)

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationFragments.h` (Public)


#### struct `FMassStaticRepresentationTag`  
`struct FMassStaticRepresentationTag : public FMassTag`  
_L22-25_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassRepresentationLODFragment`  
`struct FMassRepresentationLODFragment : public FMassFragment`  
_L28-49_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L34 _public member_ `TEnumAsByte<EMassLOD::Type> LOD = EMassLOD::Max;` — `UPROPERTY()` — LOD information
- L37 _public member_ `TEnumAsByte<EMassLOD::Type> PrevLOD = EMassLOD::Max;` — `UPROPERTY()`
- L41 _public member_ `EMassVisibility Visibility = EMassVisibility::Max;` — `UPROPERTY()` — Visibility Info
- L44 _public member_ `EMassVisibility PrevVisibility = EMassVisibility::Max;` — `UPROPERTY()`
- L48 _public member_ `float LODSignificance = 0.0f;` — `UPROPERTY()` — Value scaling from 0 to 3, 0 highest LOD we support and 3 being completely off LOD

#### struct `FMassRepresentationFragment`  
`struct FMassRepresentationFragment : public FMassFragment`  
_L52-130_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L56 _public member_ `static constexpr int32 MaxActorVisualReadinessWaitFrames = static_cast<int32>(TNumericLimits<uint8>::Max());`
- L59 _public member_ `EMassRepresentationType CurrentRepresentation = EMassRepresentationType::None;` — `UPROPERTY()`
- L62 _public member_ `EMassRepresentationType PrevRepresentation = EMassRepresentationType::None;` — `UPROPERTY()`
- L65 _public member_ `int16 HighResTemplateActorIndex = INDEX_NONE;` — `UPROPERTY()`
- L68 _public member_ `int16 LowResTemplateActorIndex = INDEX_NONE;` — `UPROPERTY()`
- L71 _public member_ `FStaticMeshInstanceVisualizationDescHandle StaticMeshDescHandle;` — `UPROPERTY()`
- L74 _public member_ `FSkinnedMeshInstanceVisualizationDescHandle SkinnedMeshDescHandle;` — `UPROPERTY()`
- L78 _public member_ `float PrevLODSignificance = -1.0f;` — `UPROPERTY()` — Value scaling from 0 to 3, 0 highest LOD we support and 3 being completely off LOD
- L81 _public member_ `uint8 bIsPendingDestruction : 1 = false;` — `UPROPERTY()`
- L92 _private member_ `uint8 bIsWaitingForActorVisualReadiness : 1 = false;` — `UPROPERTY()` — When true, the actor has been spawned (or re-used externally) but is kept disabled while the prior mesh representation (ISM/SkinnedMesh) covers the visual gap. Cleared once UMassRepresentationActorManagement::IsActorReadyForRepresentation reports true (or after the bDoWaitForActorVisualReadiness 1-frame delay). May span multiple frames when an override delays readiness for asset streaming.
- L100 _private member_ `uint8 ActorVisualReadinessWaitFrames = 0;` — `UPROPERTY()` — Counts consecutive frames bIsWaitingForActorVisualReadiness has been set, used by UpdateRepresentation to detect runaway readiness gates (e.g. an override that never returns true) and force-enable the actor after a configurable cap. Reset to 0 whenever bIsWaitingForActorVisualReadiness transitions to false. Saturates at 255.
- L104 _public member_ `FMassActorSpawnRequestHandle ActorSpawnRequestHandle;` — `UPROPERTY()`
- L107 _public member_ `FTransform PrevTransform;` — `UPROPERTY()`
- L109 _public function_ `bool IsWaitingForActorVisualReadiness() const`
- L115 _public function_ `void SetIsWaitingForActorVisualReadiness(const bool bNewValue)` — sets bIsWaitingForActorVisualReadiness and resets ActorVisualReadinessWaitFrames
- L121 _public function_ `void IncreaseActorVisualReadinessWaitFrames()`
- L126 _public function_ `bool IsActorVisualRedinessTimedOut(const int32 Limit) const`

#### struct `FMassRepresentationAnimationFragment`  
`struct FMassRepresentationAnimationFragment : public FMassFragment`  
_L133-139_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L138 _public member_ `FAnimSequenceTrackAutoPlayData AnimData;` — `UPROPERTY(Transient)`

#### struct `FMassRepresentationSubsystemSharedFragment`  
`struct FMassRepresentationSubsystemSharedFragment : public FMassSharedFragment`  
_L142-148_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L147 _public member_ `TObjectPtr<UMassRepresentationSubsystem> RepresentationSubsystem = nullptr;` — `UPROPERTY(Transient)`

#### struct `TMassSharedFragmentTraits`  
`template<> struct TMassSharedFragmentTraits<FMassRepresentationSubsystemSharedFragment> final`  
_L151-157_

#### enum `TMassSharedFragmentTraits::(anonymous)`  
``  
_L154-156_

#### struct `FMassRepresentationParameters`  
`struct FMassRepresentationParameters : public FMassConstSharedFragment`  
_L161-253_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L165 _public prototype_ `FMassRepresentationParameters() = default;`
- L169 _public member_ `TSubclassOf<UMassRepresentationActorManagement> RepresentationActorManagementClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta = (EditCondition = "bCanModifyRepresentationActorManagementClass"))` — Allow subclasses to override the representation actor management behavior
- L173 _public member_ `EMassRepresentationType LODRepresentation[EMassLOD::Max] = { EMassRepresentationType::HighResSpawnedActor, EMassRepresentationType::LowResSpawnedActor, EMassRepresentationType::StaticMeshInstance, EMassRepresentationType::None };` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — What should be the representation of this entity for each specific LOD
- L177 _public member_ `FName WorldPartitionGridNameContainingCollision;` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — World Partition grid name to test collision against, default None will be the main grid
- L181 _public member_ `float NotVisibleUpdateRate = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visualization", config)` — At what rate should the not visible entity be updated in seconds
- L194 _public member_ `uint8 bForceActorRepresentationForExternalActors : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — If true, forces UMassRepresentationProcessor to override the WantedRepresentationType to actor representation whenever an external (non Mass owned) actor is set on an entitie's FMassActorFragment fragment. If / when the actor fragment is reset, WantedRepresentationType resumes selecting the appropriate representation for the current representation LOD. Useful for server-authoritative actor spawning to force actor representation on clients for replicated actors.
- L198 _public member_ `uint8 bKeepLowResActors : 1 = true;` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — If true, LowRes actors will be kept around, disabled, whilst StaticMeshInstance representation is active
- L202 _public member_ `uint8 bKeepActorExtraFrame : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — When switching to ISM keep the actor an extra frame, helps cover rendering glitches (i.e. occlusion query being one frame late)
- L211 _public member_ `uint8 bWaitForActorVisualReadiness : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — When switching from ISM/SkinnedMesh to Actor, keep the mesh visible while the spawned actor reports not-ready (UMassRepresentationActorManagement::IsActorReadyForRepresentation) - typically because a soft-pointered SkeletalMesh / StaticMesh is still streaming in, or downstream init has not run yet on the freshly-spawned actor. Bounded by ai.massrepresentation.MaxActorVisualReadinessWaitFrames.
- L215 _public member_ `uint8 bSpreadFirstVisualizationUpdate : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Representation", config)` — If true, will spread the first visualization update over the period specified in NotVisibleUpdateRate member
- L220 _public member_ `uint8 bCanModifyRepresentationActorManagementClass : 1 = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|Visual")` — the property is marked like this to ensure it won't show up in UI
- L223 _public prototype_ `inline void ComputeCachedValues() const;`
- L227 _public member_ `mutable EMassRepresentationType CachedDefaultRepresentationType = EMassRepresentationType::None;` — `UPROPERTY(Transient)` — Default representation when unable to spawn an actor, gets calculated at initialization
- L230 _public member_ `mutable TObjectPtr<UMassRepresentationActorManagement> CachedRepresentationActorManagement = nullptr;` — `UPROPERTY(Transient)`
- L236 _public function_ `bool Identical(const FMassRepresentationParameters* InOtherValue, uint32 ) const` — The operation by design ignores CachedDefaultRepresentationType and CachedRepresentationActorManagement, since those two properties are fully rutime and are derived from the others.
- L274 _function_ `inline void FMassRepresentationParameters::ComputeCachedValues() const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMassRepresentationParameters> : public TStructOpsTypeTraitsBase2<FMassRepresentationParameters>`  
_L256-262_
- inherits: `TStructOpsTypeTraitsBase2<FMassRepresentationParameters>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L259-261_

#### struct `TMassSharedFragmentTraits`  
`template<> struct TMassSharedFragmentTraits<FMassRepresentationParameters> final`  
_L265-271_

#### enum `TMassSharedFragmentTraits::(anonymous)`  
``  
_L268-270_

#### struct `FMassVisualizationLODParameters`  
`struct FMassVisualizationLODParameters : public FMassConstSharedFragment`  
_L299-330_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L305 _public member_ `float BaseLODDistance[EMassLOD::Max] = { 0.f, 1000.f, 2500.f, 10000.f };` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Distances where each LOD becomes relevant
- L307 _public member_ `float VisibleLODDistance[EMassLOD::Max] = { 0.f, 2000.f, 4000.f, 15000.f };` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)`
- L309 _public member_ `float BufferHysteresisOnDistancePercentage = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)`
- L313 _public member_ `int32 LODMaxCount[EMassLOD::Max] = {50, 100, 500, MAX_int32};` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Maximum limit for each entity per LOD
- L317 _public member_ `float DistanceToFrustum = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)` — Entities within this distance from frustum will be considered visible. Expressed in Unreal Units.
- L325 _public member_ `float DistanceToFrustumHysteresis = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)` — Once an entity is visible how far away from frustum does it need to get to lose "visible" state. Expressed in Unreal Units and is added to DistanceToFrustum to arrive at the final value to be used for testing.
- L329 _public member_ `TObjectPtr<UScriptStruct> FilterTag = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (BaseStruct = "/Script/MassEntity.MassTag"))` — Filter these settings with specified tag

#### struct `FMassVisualizationLODSharedFragment`  
`struct FMassVisualizationLODSharedFragment : public FMassSharedFragment`  
_L333-345_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L337 _public prototype_ `FMassVisualizationLODSharedFragment() = default;`
- L338 _public prototype_ `FMassVisualizationLODSharedFragment(const FMassVisualizationLODParameters& LODParams);`
- L340 _public member_ `TMassLODCalculator<FMassRepresentationLODLogic> LODCalculator;`
- L341 _public member_ `bool bHasAdjustedDistancesFromCount = false;`
- L344 _public member_ `TObjectPtr<const UScriptStruct> FilterTag = nullptr;` — `UPROPERTY(Transient)`

#### struct `FMassDistanceLODParameters`  
`struct FMassDistanceLODParameters : public FMassConstSharedFragment`  
_L354-368_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Simplest version of LOD Calculation based strictly on Distance parameters Compared to FMassVisualizationLODParameters, we: * Only include a single set of LOD Distances (radial distance from viewer) * we do not care about distance to Frustum * we do not care about Max Count
- L360 _public member_ `float LODDistance[EMassLOD::Max] = { 0.f, 1000.f, 2500.f, 10000.f };` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Distances where each LOD becomes relevant
- L363 _public member_ `float BufferHysteresisOnDistancePercentage = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)`
- L367 _public member_ `TObjectPtr<UScriptStruct> FilterTag = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (BaseStruct = "/Script/MassEntity.MassTag"))` — Filter these settings with specified tag

#### struct `FMassDistanceLODSharedFragment`  
`struct FMassDistanceLODSharedFragment : public FMassSharedFragment`  
_L376-387_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- desc: Simplest version of LOD Calculation based strictly on Distance parameters Compared to FMassVisualizationLODSharedFragment, we: * Cannot Adjust the Distance from count * We care about a MassLODCalculator with a new LOD logic that excludes Visibility computation
- L380 _public prototype_ `FMassDistanceLODSharedFragment() = default;`
- L381 _public prototype_ `FMassDistanceLODSharedFragment(const FMassDistanceLODParameters& LODParams);`
- L383 _public member_ `TMassLODCalculator<FMassDistanceLODLogic> LODCalculator;`
- L386 _public member_ `TObjectPtr<const UScriptStruct> FilterTag = nullptr;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L155 _enumerator_ `GameThreadOnly = true` (scope `TMassSharedFragmentTraits::__anonb29fbc750103`)
- L260 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anonb29fbc750203`)
- L269 _enumerator_ `GameThreadOnly = true` (scope `TMassSharedFragmentTraits::__anonb29fbc750303`)

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationProcessor.h` (Public)


#### struct `FMassRepresentationUpdateParams`  
`struct FMassRepresentationUpdateParams`  
_L34-45_
- reflection: `USTRUCT()`
- L44 _public member_ `bool bTestCollisionAvailibilityForActorVisualization = true;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Mass")` — Controls whether UpdateRepresentation run will ask the RepresentationSubsystem whether the relevant world collision has been already loaded while considering switching an entity to a actor-level representation. Note that the test is unnecessary for static nor stationary entities.

#### class `UMassRepresentationProcessor`  
`class UMassRepresentationProcessor : public UMassProcessor`  
_L48-92_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMassProcessor`
- L53 _public prototype_ `UMassRepresentationProcessor();`
- L59 _public prototype_ `static void UpdateRepresentation(FMassExecutionContext& Context, const FMassRepresentationUpdateParams& Params);` — Update representation type for each entity, must be called within a ForEachEntityChunk @param Context of the execution from the entity sub system
- L64 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L71 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntityManager is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L84 _protected prototype_ `static bool ReleaseActorOrCancelSpawning(UMassRepresentationSubsystem& RepresentationSubsystem, UMassActorSubsystem* MassActorSubsystem , const FMassEntityHandle MassAgent, FMassActorFragment& ActorInfo, const int16 TemplateActorIndex, FMassActorSpawnRequestHandle& SpawnRequestHandle , FMassCommandBuffer& CommandBuffer, const bool bCancelSpawningOnly = false);` — Release the actor to the subsystem, will only release it the actor or spawn request matches the template actor @param RepresentationSubsystem to use to release the actor or cancel the spawning @param MassAgent is the handle to the associated mass agent @param ActorInfo is the fragment where we are going to store the actor pointer @param TemplateActorIndex is the index of the type to release @param SpawnRequestHandle (in/out) In: previously requested spawn to cancel if any @param CommandBuffer to queue up anything that is thread sensitive @param bCancelSpawningOnly tell to only cancel the existing spawning request and to not release the associated actor it any. @return if the actor was release or the spawning was canceled.
- L88 _protected member_ `FMassEntityQuery EntityQuery;`
- L91 _protected member_ `FMassRepresentationUpdateParams UpdateParams;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Mass")`

#### struct `FMassVisualizationProcessorTag`  
`struct FMassVisualizationProcessorTag : public FMassTag`  
_L100-103_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag required by Visualization Processor to process given archetype. Removing the tag allows to support temporary disabling of processing for individual entities of given archetype.

#### class `UMassVisualizationProcessor`  
`class UMassVisualizationProcessor : public UMassRepresentationProcessor`  
_L106-147_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRepresentationProcessor`
- L111 _public prototype_ `UMassVisualizationProcessor();`
- L116 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L123 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntityManager is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L130 _protected prototype_ `FMassVisualizationChunkFragment& UpdateChunkVisibility(FMassExecutionContext& Context) const;` — Updates chunk visibility info for later chunk logic optimization @param Context of the execution from the entity sub system @return The visualization chunk fragment
- L140 _protected prototype_ `static void UpdateEntityVisibility(const FMassEntityHandle Entity, const FMassRepresentationFragment& Representation, const FMassRepresentationLODFragment& RepresentationLOD, FMassVisualizationChunkFragment& ChunkData, FMassCommandBuffer& CommandBuffer);` — Updates entity visibility tag for later chunk logic optimization @param Entity of the entity to update visibility on @param Representation fragment containing the current and previous visual state @param RepresentationLOD fragment containing the visibility information @param ChunkData is the visualization chunk fragment @param CommandBuffer to queue up anything that is thread sensitive
- L146 _protected prototype_ `void UpdateVisualization(FMassExecutionContext& Context);` — Update representation and visibility for each entity, must be called within a ForEachEntityChunk @param Context of the execution from the entity sub system

#### class `UMassRepresentationFragmentDestructor`  
`class UMassRepresentationFragmentDestructor : public UMassObserverProcessor`  
_L151-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L156 _public prototype_ `UMassRepresentationFragmentDestructor();`
- L159 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L160 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L162 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSREPRESENTATION_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace Representation` (scope `UE::Mass`)
- L20 _externvar_ `extern int32 bAllowKeepActorExtraFrame;` (scope `UE::Mass::Representation`)
- L21 _externvar_ `extern int32 bAllowWaitForActorVisualReadiness;` (scope `UE::Mass::Representation`)
- L27 _function_ `inline bool ShouldKeepActorExtraFrame(const FMassRepresentationParameters& Params)` (scope `UE::Mass::Representation`) — Computes whether to keep the actor visible an extra frame across an actor->ISM transition. Combines the cvar kill-switch with the per-archetype params.

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationSubsystem.h` (Public)


#### class `UMassRepresentationSubsystem`  
`class UMassRepresentationSubsystem : public UMassSubsystemBase`  
_L32-262_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: Subsystem responsible for all visual of mass agents, will handle actors spawning and static mesh instances
- L42 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle FindOrAddStaticMeshDesc(const FStaticMeshInstanceVisualizationDesc& Desc);` — Get the index of the static mesh visual type, will add a new one if does not exist @param Desc is the information for the static mesh that will be instantiated later via AddStaticMeshInstance() @return The index of the static mesh type
- L49 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle AddVisualDescWithISMComponent(const FStaticMeshInstanceVisualizationDesc& Desc, UInstancedStaticMeshComponent& ISMComponent);` — Creates a dedicated visual type described by host Desc and ties ISMComponent to it. @note this is a helper function for a common "single ISMComponent" case. Calls AddVisualDescWithISMComponents under the hood. @return The index of the visual type
- L55 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle AddVisualDescWithISMComponents(const FStaticMeshInstanceVisualizationDesc& Desc, TArrayView<TObjectPtr<UInstancedStaticMeshComponent>> ISMComponents);` — Creates a dedicated visual type described by host Desc and ties given ISMComponents to it. @return The index of the visual type
- L60 _public prototype_ `const FMassISMCSharedData* GetISMCSharedDataForDescriptionIndex(const int32 DescriptionIndex) const;` — Fetches FMassISMCSharedData indicated by DescriptionIndex, or nullptr if it's not a valid index
- L65 _public prototype_ `const FMassISMCSharedData* GetISMCSharedDataForInstancedStaticMesh(const UInstancedStaticMeshComponent* ISMC) const;` — Fetches FMassISMCSharedData indicated by an ISMC, or nullptr if the ISMC is not represented by any shared data.
- L71 _public prototype_ `void RemoveVisualDesc(const FStaticMeshInstanceVisualizationDescHandle VisualizationHandle);` — Removes all data associated with a given VisualizationIndex. Note that this is safe to do only if there are no entities relying on this index. No entity data patching will take place.
- L76 _public prototype_ `FMassInstancedStaticMeshInfoArrayView GetMutableInstancedStaticMeshInfos();` — @return the array of all the static mesh instance component information
- L79 _public prototype_ `void DirtyStaticMeshInstances();` — Mark render state of the static mesh instances dirty
- L86 _public prototype_ `int16 FindOrAddTemplateActor(const TSubclassOf<AActor>& ActorClass);` — Store the template actor uniquely and return an index to it @param ActorClass is a template actor class we will need to spawn for an agent @return The index of the template actor type
- L99 _public prototype_ `AActor* GetOrRequestSpawnActorFromTemplate(const FMassEntityHandle MassAgent, const FTransform& Transform, const int16 TemplateActorIndex, FMassActorSpawnRequestHandle& InOutSpawnRequestHandle, float Priority = MAX_FLT, FMassActorPreSpawnDelegate ActorPreSpawnDelegate = FMassActorPreSpawnDelegate(), FMassActorPostSpawnDelegate ActorPostSpawnDelegate = FMassActorPostSpawnDelegate());` — Get or spawn an actor from the TemplateActorIndex @param MassAgent is the handle to the associated mass agent @param Transform where to create this actor @param TemplateActorIndex is the index of the type fetched with FindOrAddTemplateActor() @param SpawnRequestHandle [IN/OUT] IN: previously requested spawn OUT: newly requested spawn @param Priority of this spawn request in comparison with the others, lower value means higher priority (optional) @param ActorPreSpawnDelegate is an optional delegate called before the spawning of an actor @param ActorPostSpawnDelegate is an optional delegate called once the actor is spawned @return The spawned actor from the template actor type if ready
- L109 _public prototype_ `bool CancelSpawning(const FMassEntityHandle MassAgent, const int16 TemplateActorIndex, FMassActorSpawnRequestHandle & SpawnRequestHandle);` — Cancel spawning request that is matching the TemplateActorIndex @param MassAgent is the handle to the associated mass agent @param TemplateActorIndex is the template type of the actor to release in case it was successfully spawned @param SpawnRequestHandle [IN/OUT] previously requested spawn, gets invalidated as a result of this call. @return True if spawning request was canceled
- L119 _public prototype_ `bool ReleaseTemplateActor(const FMassEntityHandle MassAgent, const int16 TemplateActorIndex, AActor* ActorToRelease, bool bImmediate);` — Release an actor that is matching the TemplateActorIndex @param MassAgent is the handle to the associated mass agent @param TemplateActorIndex is the template type of the actor to release in case it was successfully spawned @param ActorToRelease is the actual actor to release if any @param bImmediate means it needs to be done immediately and not queue for later @return True if actor was released
- L130 _public prototype_ `bool ReleaseTemplateActorOrCancelSpawning(const FMassEntityHandle MassAgent, const int16 TemplateActorIndex, AActor* ActorToRelease, FMassActorSpawnRequestHandle& SpawnRequestHandle, bool bImmediate = false);` — Release an actor or cancel its spawning if it is matching the TemplateActorIndex @param MassAgent is the handle to the associated mass agent @param TemplateActorIndex is the template type of the actor to release in case it was successfully spawned @param ActorToRelease is the actual actor to release if any @param SpawnRequestHandle [IN/OUT] previously requested spawn, gets invalidated as a result of this call. @param bImmediate whether to perform the actor destruction immediately, otherwise it will be queued for processing later @return True if actor was released or spawning request was canceled
- L139 _public prototype_ `bool DoesActorMatchTemplate(const AActor& Actor, const int16 TemplateActorIndex) const;` — Compare if an actor matches the registered template actor @param Actor to compare its class against the template @param TemplateActorIndex is the template type of the actor to compare against @return True if actor matches the template
- L141 _public prototype_ `TSubclassOf<AActor> GetTemplateActorClass(const int16 TemplateActorIndex);`
- L143 _public prototype_ `bool IsCollisionLoaded(const FName TargetGrid, const FTransform& Transform) const;`
- L148 _public prototype_ `void ReleaseTemplate(const TSubclassOf<AActor>& ActorClass);` — Responds to the FMassEntityTemplate getting destroyed, and releases reference to corresponding Actor in TemplateActors
- L153 _public prototype_ `void ReleaseAllResources();` — Release all references to static meshes and template actors Use with caution, all entities using this representation subsystem must be destroy otherwise they will point to invalid resources
- L155 _public function_ `UMassActorSpawnerSubsystem* GetActorSpawnerSubsystem() const`
- L158 _public function_ `UMassVisualizationComponent* GetVisualizationComponent() const` — Access to the visualization component for animation state readback
- L162 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L163 _protected prototype_ `virtual void Deinitialize() override;`
- L166 _protected prototype_ `bool SpawnVisualizer(TNotNull<UWorld*> World);`
- L169 _protected prototype_ `void OnProcessingPhaseStarted(const float DeltaSeconds, const EMassProcessingPhase Phase) const;` — Needed for batching the update of static mesh transform
- L171 _protected prototype_ `void OnMassAgentComponentEntityAssociated(const UMassAgentComponent& AgentComponent);`
- L172 _protected prototype_ `void OnMassAgentComponentEntityDetaching(const UMassAgentComponent& AgentComponent);`
- L174 _protected prototype_ `bool ReleaseTemplateActorInternal(const int16 TemplateActorIndex, AActor* ActorToRelease, bool bImmediate);`
- L175 _protected prototype_ `bool CancelSpawningInternal(const int16 TemplateActorIndex, FMassActorSpawnRequestHandle& SpawnRequestHandle, bool bImmediateActorRelease = false);`
- L177 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L184 _public prototype_ `FMassInstancedSkinnedMeshInfoArrayView GetMutableInstancedSkinnedMeshInfos();` — @return the array of all the skinned mesh instance component information
- L191 _public prototype_ `FSkinnedMeshInstanceVisualizationDescHandle FindOrAddSkinnedMeshVisualizationDesc(const FSkinnedMeshInstanceVisualizationDesc& Desc);` — Get the index of the skinned mesh visual type, will add a new one if does not exist @param Desc is the information for the mesh that will be instantiated later when adding a skinned mesh instance @return The index of the mesh type
- L214 _protected member_ `TSparseArray<FTemplateActorData> TemplateActors;` — The array of all the template actors
- L215 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(TemplateActorsMTAccessDetector);`
- L219 _protected member_ `TObjectPtr<UMassVisualizationComponent> VisualizationComponent;` — `UPROPERTY(Transient)` — The component that handles all the static mesh instances
- L223 _protected member_ `TObjectPtr<AMassVisualizer> Visualizer;` — `UPROPERTY(Transient)` — The actor owning the above visualization component
- L226 _protected member_ `TObjectPtr<UMassActorSpawnerSubsystem> ActorSpawnerSubsystem;` — `UPROPERTY(Transient)`
- L228 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L231 _protected member_ `TObjectPtr<UWorldPartitionSubsystem> WorldPartitionSubsystem;` — `UPROPERTY(Transient)`
- L234 _protected member_ `float RetryMovedDistanceSq = 1000000.0f;` — The time to wait before retrying a to spawn actor that failed
- L237 _protected member_ `float RetryTimeInterval = 10.0f;` — The distance a failed spawned actor needs to move before we retry
- L240 _protected member_ `TMap<FMassEntityHandle, int32> HandledMassAgents;` — Keeping track of all the mass agent this subsystem is responsible for spawning actors
- L247 _public function_ `AActor* GetOrSpawnActorFromTemplate(const FMassEntityHandle MassAgent, const FTransform& Transform, const int16 TemplateActorIndex, FMassActorSpawnRequestHandle& InOutSpawnRequestHandle, float Priority = MAX_FLT, FMassActorPreSpawnDelegate ActorPreSpawnDelegate = FMassActorPreSpawnDelegate(), FMassActorPostSpawnDelegate ActorPostSpawnDelegate = FMassActorPostSpawnDelegate())` — `UE_DEPRECATED(5.8, "Use GetOrRequestSpawnActorFromTemplate instead.")`
- L255 _private prototype_ `void HandleVisualizerEndPlay(AActor* Actor, const EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L258 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(InstancedStaticMeshInfosDetector);` — Used for default return value from GetMutableInstancedStaticMeshInfos
- L261 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(InstancedSkinnedMeshInfosDetector);` — Used for default return value from GetMutableInstancedSkinedMeshInfos

#### struct `UMassRepresentationSubsystem::FTemplateActorData`  
`struct FTemplateActorData`  
_L195-199_
- L197 _public member_ `TSubclassOf<AActor> Actor;`
- L198 _public member_ `uint32 RefCount{0u};`

#### struct `UMassRepresentationSubsystem::FTemplateActorEqualsPredicate`  
`struct FTemplateActorEqualsPredicate`  
_L201-211_
- L203 _public member_ `const TSubclassOf<AActor>& ActorClass;`
- L205 _public function_ `FTemplateActorEqualsPredicate(const TSubclassOf<AActor>& ActorClass) : ActorClass(ActorClass)`
- L207 _public function_ `bool operator()(const FTemplateActorData& ActorData) const`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationTypes.h` (Public)


#### enum `EMassRepresentationType`  
`enum class EMassRepresentationType : uint8`  
_L36-43_
- reflection: `UENUM()`
- L38 _public enumerator_ `HighResSpawnedActor`
- L39 _public enumerator_ `LowResSpawnedActor`
- L40 _public enumerator_ `SkinnedMeshInstance`
- L41 _public enumerator_ `StaticMeshInstance`
- L42 _public enumerator_ `None`

#### enum `EMassActorEnabledType`  
`enum class EMassActorEnabledType : uint8`  
_L65-70_
- L67 _public enumerator_ `Disabled`
- L68 _public enumerator_ `LowRes`
- L69 _public enumerator_ `HighRes`

#### struct `FMassStaticMeshInstanceVisualizationMeshDesc`  
`struct FMassStaticMeshInstanceVisualizationMeshDesc`  
_L73-156_
- reflection: `USTRUCT()`
- L77 _public prototype_ `FMassStaticMeshInstanceVisualizationMeshDesc();`
- L81 _public member_ `FTransform LocalTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — A relative Transform from the parent, passed along to FMassISMCSharedData::LocalTransform
- L85 _public member_ `TObjectPtr<UStaticMesh> Mesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The static mesh visual representation
- L93 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialOverrides;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Material overrides for the static mesh visual representation. Array indices correspond to material slot indices on the static mesh.
- L97 _public member_ `float MinLODSignificance = float(EMassLOD::High);` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The minimum inclusive LOD significance to start using this static mesh
- L101 _public member_ `float MaxLODSignificance = float(EMassLOD::Max);` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The maximum exclusive LOD significance to stop using this static mesh
- L105 _public member_ `bool bCastShadows = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Controls whether the ISM can cast shadow or not
- L112 _public member_ `bool bRequiresExternalInstanceIDTracking = false;` — Determines the value of corresponding FMassISMCSharedData.bRequiresExternalInstanceIDTracking. Recommended enabled for stationary meshes. @see FMassISMCSharedData.bRequiresExternalInstanceIDTracking for details.
- L115 _public member_ `EComponentMobility::Type Mobility = EComponentMobility::Movable;` — Controls the mobility of the ISM
- L119 _public member_ `TSubclassOf<UInstancedStaticMeshComponent> ISMComponentClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — InstancedStaticMeshComponent class to use to manage instances described by this struct instance
- L121 _public function_ `bool operator==(const FMassStaticMeshInstanceVisualizationMeshDesc& Other) const`
- L150 _public function_ `void SetSignificanceRange(const EMassLOD::Type MinLOD, const EMassLOD::Type MaxLOD)` — convenience function for setting MinLODSinificance and MaxLODSinificance based on EMassLOD values

#### struct `FStaticMeshInstanceVisualizationDesc`  
`struct FStaticMeshInstanceVisualizationDesc : public FTableRowBase`  
_L159-197_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L168 _public member_ `TArray<FMassStaticMeshInstanceVisualizationMeshDesc> Meshes;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta=(TitleProperty="{Mesh}"))` — Mesh descriptions. These will be instanced together using the same transform for each, to visualize the given agent.
- L172 _public member_ `bool bUseTransformOffset = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Boolean to enable code to transform the static meshes if not align the mass agent transform
- L176 _public member_ `FTransform TransformOffset = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta=(EditCondition="bUseTransformOffset"))` — Transform to offset the static meshes if not align the mass agent transform
- L180 _public member_ `TArray<float> CustomDataFloats;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Custom data that can eventually be propagated to UInstancedStaticMeshComponent::PerInstanceSMCustomData
- L182 _public function_ `bool operator==(const FStaticMeshInstanceVisualizationDesc& Other) const`
- L187 _public function_ `void Reset()`
- L196 _public prototype_ `bool IsValid() const;` — @return whether any of descriptions in Meshes is valid. This implies that empty Meshes will be treated as not valid.

#### struct `FStaticMeshInstanceVisualizationDescHandle`  
`struct alignas(2) FStaticMeshInstanceVisualizationDescHandle`  
_L201-247_
- reflection: `USTRUCT()`
- desc: Handle for FStaticMeshInstanceVisualizationDesc's registered with UMassRepresentationSubsystem
- L205 _public member_ `static constexpr uint16 InvalidIndex = TNumericLimits<uint16>::Max();`
- L207 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle() = default;`
- L209 _public function_ `explicit FStaticMeshInstanceVisualizationDescHandle(uint16 InIndex) : Index(InIndex)`
- L213 _public function_ `explicit FStaticMeshInstanceVisualizationDescHandle(int32 InIndex)`
- L227 _public function_ `inline int32 ToIndex() const`
- L232 _public function_ `bool IsValid() const`
- L237 _public prototype_ `bool operator==(const FStaticMeshInstanceVisualizationDescHandle& Other) const = default;`
- L242 _private member_ `uint16 Index = InvalidIndex;` — `UPROPERTY()`

#### struct `FMassISMCSharedData`  
`struct FMassISMCSharedData`  
_L253-364_
- L256 _public function_ `FMassISMCSharedData() : bRequiresExternalInstanceIDTracking(false)`
- L261 _public function_ `explicit FMassISMCSharedData(UInstancedStaticMeshComponent* InISMC, bool bInRequiresExternalInstanceIDTracking = false, const FTransform& InTransformOffset = FTransform::Identity) : LocalTransform(InTransformOffset), ISMC(InISMC), bRequiresExternalInstanceIDTracking(bInRequiresExternalInstanceIDTracking)`
- L266 _public prototype_ `FMassISMCSharedData(const FMassISMCSharedData& Other) = default;`
- L267 _public prototype_ `FMassISMCSharedData& operator=(const FMassISMCSharedData& Other) = default;`
- L270 _public function_ `void SetISMComponent(UInstancedStaticMeshComponent& InISMC)`
- L276 _public function_ `UInstancedStaticMeshComponent* GetMutableISMComponent()`
- L277 _public function_ `const UInstancedStaticMeshComponent* GetISMComponent() const`
- L278 _public function_ `int32 OnISMComponentReferenceStored()`
- L279 _public function_ `int32 OnISMComponentReferenceReleased()`
- L281 _public function_ `void ResetAccumulatedData()`
- L291 _public function_ `void RemoveUpdatedInstanceIdsAtSwap(const int32 InstanceIDIndex)`
- L302 _public function_ `bool HasUpdatesToApply() const`
- L303 _public function_ `TConstArrayView<FMassEntityHandle> GetUpdateInstanceIds() const`
- L304 _public function_ `TConstArrayView<FTransform> GetStaticMeshInstanceTransforms() const`
- L309 _public function_ `const TArray<FTransform>& GetStaticMeshInstanceTransformsArray() const` — this function is a flavor we need to interact with older engine API that's using TArray references. Use GetStaticMeshInstanceTransforms instead whenever possible.
- L310 _public function_ `TConstArrayView<FTransform> GetStaticMeshInstancePrevTransforms() const`
- L311 _public function_ `TConstArrayView<FMassEntityHandle> GetRemoveInstanceIds() const`
- L312 _public function_ `TConstArrayView<float> GetStaticMeshInstanceCustomFloats() const`
- L314 _public function_ `bool RequiresExternalInstanceIDTracking() const`
- L316 _public function_ `void Reset()`
- L321 _public typedef_ `using FEntityToPrimitiveIdMap = Experimental::TRobinHoodHashMap<FMassEntityHandle, FPrimitiveInstanceId>;`
- L323 _public function_ `FEntityToPrimitiveIdMap& GetMutableEntityPrimitiveToIdMap()`
- L324 _public function_ `const FEntityToPrimitiveIdMap& GetEntityPrimitiveToIdMap() const`
- L326 _public function_ `int16 GetComponentInstanceIdTouchCounter() const`
- L332 _protected member_ `FTransform LocalTransform = FTransform::Identity;`
- L335 _protected member_ `TArray<FMassEntityHandle> UpdateInstanceIds;` — Buffer holding current frame transforms for the static mesh instances, used to batch update the transforms
- L336 _protected member_ `TArray<FTransform> StaticMeshInstanceTransforms;`
- L337 _protected member_ `TArray<FTransform> StaticMeshInstancePrevTransforms;`
- L338 _protected member_ `TArray<FMassEntityHandle> RemoveInstanceIds;`
- L341 _protected member_ `TArray<float> StaticMeshInstanceCustomFloats;` — Buffer holding current frame custom floats for the static mesh instances, used to batch update the ISMs custom data
- L344 _protected member_ `int32 WriteIterator = 0;` — When initially adding to StaticMeshInstanceCustomFloats, can use the size as the write iterator, but on subsequent processors, we need to know where to start writing
- L346 _protected member_ `UInstancedStaticMeshComponent* ISMC = nullptr;`
- L347 _protected member_ `int32 ISMComponentReferencesCount = 0;`
- L355 _protected member_ `uint8 bRequiresExternalInstanceIDTracking : 1;` — When set to true will result in MassVisualizationComponent manually perform Instance ID-related operations instead of relying on ISMComponent's internal ID operations. @note this mechanism has been added in preparation of changes to ISM component to change access to its internal instance ID logic. WIP as of Jun 17th 2023
- L360 _private member_ `uint16 ComponentInstanceIdTouchCounter = 0;` — Indicates that mutating changes, that can affect MassInstanceIdToComponentInstanceIdMap, have been performed. Can be used to validate whether cached data stored in other placed needs to be re-cached.
- L363 _protected member_ `FEntityToPrimitiveIdMap EntityHandleToPrimitiveIdMap;`

#### struct `FMassISMCSharedDataMap`  
`struct FMassISMCSharedDataMap`  
_L378-548_
- desc: The container type hosting FMassISMCSharedData instances and supplying functionality of marking entries that require instance-related operations (adding, removing). To get a FMassISMCSharedData instance to add operations to it call GetAndMarkDirty. Use FDirtyIterator to iterate over just the data that needs processing. @see UMassVisualizationComponent::EndVisualChanges for iteration @see FMassLODSignificanceRange methods for performing dirtying operations
- L423 _public function_ `FMassISMCSharedData& GetAndMarkDirtyChecked(const FISMCSharedDataKey OwnerKey)`
- L430 _public function_ `FMassISMCSharedData* GetAndMarkDirty(const FISMCSharedDataKey OwnerKey)`
- L442 _public function_ `template<typename... TArgs> FMassISMCSharedData& FindOrAdd(const FISMCSharedDataKey OwnerKey, TArgs&&... InNewInstanceArgs)`
- L453 _public function_ `FMassISMCSharedData* Find(const FISMCSharedDataKey OwnerKey)`
- L460 _public function_ `template<typename... TArgs> FMassISMCSharedData& Add(const FISMCSharedDataKey OwnerKey, TArgs&&... InNewInstanceArgs)`
- L479 _public function_ `void Remove(const FISMCSharedDataKey OwnerKey)`
- L490 _public function_ `FMassISMCSharedData& GetAtIndex(const int32 DataIndex)`
- L495 _public function_ `TBitArray<>& GetDirtyArray()`
- L501 _public function_ `int32 Num() const` — @return total number of entries in Data array. Note that some or all entries could be empty (i.e. already freed)
- L507 _public function_ `int32 NumValid() const` — @return number of non-empty entries in Data.
- L512 _public function_ `bool IsDirty(const int32 DataIndex) const`
- L517 _public function_ `bool IsEmpty() const`
- L522 _public function_ `void Reset()`
- L527 _public function_ `const FMassISMCSharedData* GetDataForIndex(const int32 Index) const`
- L532 _public function_ `const FMassISMCSharedData* GetDataForKey(const FISMCSharedDataKey Key) const`
- L541 _protected member_ `TArray<FMassISMCSharedData> Data;`
- L543 _protected member_ `TMap<FISMCSharedDataKey, int32> Map;` — Mapping from Owner (as FObjectKey) of data represented by FMassISMCSharedData to an index to Data
- L545 _protected member_ `TBitArray<> DirtyData;` — Indicates whether corresponding Data entry has any instance work assigned to it (instance addition or removal)
- L547 _protected member_ `TArray<int32> FreeIndices;` — Indices to Data that are available for reuse

#### struct `FMassISMCSharedDataMap::FDirtyIterator`  
`struct FDirtyIterator`  
_L380-421_
- L383 _public function_ `explicit FDirtyIterator(FMassISMCSharedDataMap& InContainer) : Container(InContainer), It(InContainer.GetDirtyArray())`
- L393 _public function_ `operator bool() const`
- L395 _public function_ `FDirtyIterator& operator++()`
- L407 _public function_ `FMassISMCSharedData& operator*() const`
- L412 _public function_ `void ClearDirtyFlag()`
- L418 _private member_ `FMassISMCSharedDataMap& Container;`
- L419 _private member_ `TBitArray<>::FIterator It;`
- L420 _private member_ `static constexpr bool bValueToCheck = true;`

#### struct `FMassLODSignificanceRange`  
`struct FMassLODSignificanceRange`  
_L552-599_
- reflection: `USTRUCT()`
- L557 _public prototype_ `void AddBatchedTransform(const FMassEntityHandle EntityHandle, const FTransform& Transform, const FTransform& PrevTransform, TConstArrayView<FISMCSharedDataKey> ExcludeStaticMeshRefs);`
- L562 _public function_ `template<typename InCustomDataType> void AddBatchedCustomData(InCustomDataType InCustomData, const TArray<FISMCSharedDataKey>& ExcludeStaticMeshRefs, int32 NumFloatsToPad = 0)` — Adds the specified struct reinterpreted as custom floats to our custom data. Individual members of the specified struct should always fit into a float. When adding any custom data, the custom data must be added for every instance.
- L582 _public prototype_ `void AddBatchedCustomDataFloats(const TArray<float>& CustomFloats, const TArray<FISMCSharedDataKey>& ExcludeStaticMeshRefs);`
- L585 _public prototype_ `void AddInstance(const FMassEntityHandle EntityHandle, const FTransform& Transform);` — Single-instance version of AddBatchedCustomData when called to add entities (as opposed to modify existing ones).
- L587 _public prototype_ `void RemoveInstance(const FMassEntityHandle EntityHandle);`
- L589 _public prototype_ `void WriteCustomDataFloatsAtStartIndex(int32 StaticMeshIndex, const TArrayView<float>& CustomFloats, const int32 FloatsPerInstance, const int32 StartIndex, const TArray<FISMCSharedDataKey>& ExcludeStaticMeshRefs);`
- L592 _public member_ `float MinSignificance = 0.0f;` — LOD Significance range
- L593 _public member_ `float MaxSignificance = 0.0f;`
- L596 _public member_ `TArray<FISMCSharedDataKey> StaticMeshRefs;` — The component handling these instances
- L598 _public member_ `FMassISMCSharedDataMap* ISMCSharedDataPtr = nullptr;`

#### struct `FMassInstancedStaticMeshInfo`  
`struct FMassInstancedStaticMeshInfo`  
_L602-750_
- reflection: `USTRUCT()`
- L607 _public prototype_ `FMassInstancedStaticMeshInfo() = default;`
- L609 _public function_ `explicit FMassInstancedStaticMeshInfo(const FStaticMeshInstanceVisualizationDesc& InDesc) : Desc(InDesc)`
- L615 _public prototype_ `void Reset();` — Clears out contents so that a given FMassInstancedStaticMeshInfo instance can be reused
- L617 _public function_ `const FStaticMeshInstanceVisualizationDesc& GetDesc() const`
- L623 _public function_ `bool ShouldUseTransformOffset() const` — Whether or not to transform the static meshes if not align the mass agent transform
- L624 _public function_ `FTransform GetTransformOffset() const`
- L626 _public function_ `inline FMassLODSignificanceRange* GetLODSignificanceRange(float LODSignificance)`
- L638 _public function_ `void AddBatchedTransform(const FMassEntityHandle EntityHandle, const FTransform& Transform, const FTransform& PrevTransform, const float LODSignificance, const float PrevLODSignificance = -1.0f)`
- L655 _public function_ `inline void RemoveInstance(const FMassEntityHandle EntityHandle, const float LODSignificance)`
- L666 _public function_ `template<typename InCustomDataType> void AddBatchedCustomData(InCustomDataType InCustomData, const float LODSignificance, const float PrevLODSignificance = -1.0f, int32 NumFloatsToPad = 0)` — Adds the specified struct reinterpreted as custom floats to our custom data. Individual members of the specified struct should always fit into a float. When adding any custom data, the custom data must be added for every instance.
- L683 _public function_ `inline void AddBatchedCustomDataFloats(const TArray<float>& CustomFloats, const float LODSignificance, const float PrevLODSignificance = -1.0f)`
- L700 _public function_ `void WriteCustomDataFloatsAtStartIndex(int32 StaticMeshIndex, const TArrayView<float>& CustomFloats, const float LODSignificance, const int32 FloatsPerInstance, const int32 FloatStartIndex, const float PrevLODSignificance = -1.0f)`
- L717 _public function_ `void AddISMComponent(FMassISMCSharedData& SharedData)`
- L726 _public function_ `int32 GetLODSignificanceRangesNum() const`
- L728 _public function_ `bool IsValid() const`
- L736 _protected prototype_ `void ClearVisualInstance(UInstancedStaticMeshComponent& ISMComponent);` — Destroy the visual instance
- L740 _protected member_ `FStaticMeshInstanceVisualizationDesc Desc;` — `UPROPERTY(VisibleAnywhere, Category = "Mass/Debug")` — Information about this static mesh which will represent all instances
- L744 _protected member_ `TArray<TObjectPtr<UInstancedStaticMeshComponent>> InstancedStaticMeshComponents;` — `UPROPERTY(VisibleAnywhere, Category = "Mass/Debug")` — The components handling these instances
- L747 _protected member_ `TArray<FMassLODSignificanceRange> LODSignificanceRanges;` — `UPROPERTY(VisibleAnywhere, Category = "Mass/Debug")`

#### struct `FMassInstancedStaticMeshInfoArrayViewAccessDetector`  
`struct FMassInstancedStaticMeshInfoArrayViewAccessDetector`  
_L755-799_
- L757 _public function_ `FMassInstancedStaticMeshInfoArrayViewAccessDetector(TArrayView<FMassInstancedStaticMeshInfo> InInstancedStaticMeshInfos, const FRWAccessDetector& InAccessDetector) : InstancedStaticMeshInfos(InInstancedStaticMeshInfos) , AccessDetector(&InAccessDetector)`
- L764 _public function_ `FMassInstancedStaticMeshInfoArrayViewAccessDetector(FMassInstancedStaticMeshInfoArrayViewAccessDetector&& Other) : InstancedStaticMeshInfos(Other.InstancedStaticMeshInfos) , AccessDetector(Other.AccessDetector)`
- L770 _public prototype_ `FMassInstancedStaticMeshInfoArrayViewAccessDetector(const FMassInstancedStaticMeshInfoArrayViewAccessDetector& Other) = delete;`
- L771 _public prototype_ `void operator=(const FMassInstancedStaticMeshInfoArrayViewAccessDetector& Other) = delete;`
- L773 _public function_ `~FMassInstancedStaticMeshInfoArrayViewAccessDetector()`
- L781 _public function_ `inline FMassInstancedStaticMeshInfo& operator[](int32 Index) const`
- L786 _public function_ `bool IsValidIndex(const int32 Index) const`
- L791 _public function_ `int32 Num() const`
- L797 _private member_ `TArrayView<FMassInstancedStaticMeshInfo> InstancedStaticMeshInfos;`
- L798 _private member_ `const FRWAccessDetector* AccessDetector;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MASSREPRESENTATION_API`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassRepresentation, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassRepresentation, Log, All);`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Mass` (scope `UE`)
- L25 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L27 _variable_ `const FName Representation = FName(TEXT("Repr` (scope `UE::Mass::ProcessorGroupNames`)
- L30 _variable_ `const FName VisualizationProcessing = FName(TEXT("Repr` (scope `UE::Mass::ProcessorGroupNames`) — Sub-group of Representation containing every UMassVisualizationProcessor subclass. Consumers that depend on CurrentRepresentation being finalised should ExecuteAfter this.
- L33 _typedef_ `using FISMCSharedDataKey = TObjectKey<UInstancedStaticMeshComponent>;`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Mass` (scope `UE`)
- L45 _namespace_ `namespace Representation` (scope `UE::Mass`)
- L47 _function_ `inline bool IsValidMeshRepresentation(EMassRepresentationType RepresentationType)` (scope `UE::Mass::Representation`)
- L52 _function_ `inline bool IsValidActorRepresentation(EMassRepresentationType RepresentationType)` (scope `UE::Mass::Representation`)
- L62 _externvar_ `extern const FColor RepresentationTypeColors[];` (scope `UE::Mass::Representation`) — Debug-draw color per EMassRepresentationType, shared across Mass visualization debug paths. The array is sized to cover every enum value (including None); a static_assert in MassRepresentationTypes.cpp keeps it in sync with the enum.
- L132 _function_ `friend inline uint32 GetTypeHash(const FMassStaticMeshInstanceVisualizationMeshDesc& MeshDesc)`
- L754 _macro_ `#define MAKE_MASS_INSTANCED_STATIC_MESH_INFO_ARRAY_VIEW(ArrayView, AccessDetector) FMassInstancedStaticMeshInfoArrayView(ArrayView, AccessDetector)`
- L801 _typedef_ `using FMassInstancedStaticMeshInfoArrayView = FMassInstancedStaticMeshInfoArrayViewAccessDetector;`
- L805 _macro_ `#define MAKE_MASS_INSTANCED_STATIC_MESH_INFO_ARRAY_VIEW(ArrayView, AccessDetector) ArrayView`
- L807 _typedef_ `using FMassInstancedStaticMeshInfoArrayView = TArrayView<FMassInstancedStaticMeshInfo>;`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassRepresentationUtils.h` (Public)


#### struct `UE::Mass::Representation::TMassVisibilityTagForLevel`  
`template <EMassVisibility Level> struct TMassVisibilityTagForLevel`  
_L37-40_
- L39 _public typedef_ `typedef FMassTag FTag;`
- L45 _public typedef_ `typedef FMassVisibilityCanBeSeenTag FTag;`
- L51 _public typedef_ `typedef FMassVisibilityCulledByFrustumTag FTag;`
- L57 _public typedef_ `typedef FMassVisibilityCulledByDistanceTag FTag;`

#### struct `UE::Mass::Representation::TMassVisibilityTagForLevel`  
`template<> struct TMassVisibilityTagForLevel<EMassVisibility::CanBeSeen>`  
_L43-46_
- L39 _public typedef_ `typedef FMassTag FTag;`
- L45 _public typedef_ `typedef FMassVisibilityCanBeSeenTag FTag;`
- L51 _public typedef_ `typedef FMassVisibilityCulledByFrustumTag FTag;`
- L57 _public typedef_ `typedef FMassVisibilityCulledByDistanceTag FTag;`

#### struct `UE::Mass::Representation::TMassVisibilityTagForLevel`  
`template<> struct TMassVisibilityTagForLevel<EMassVisibility::CulledByFrustum>`  
_L49-52_
- L39 _public typedef_ `typedef FMassTag FTag;`
- L45 _public typedef_ `typedef FMassVisibilityCanBeSeenTag FTag;`
- L51 _public typedef_ `typedef FMassVisibilityCulledByFrustumTag FTag;`
- L57 _public typedef_ `typedef FMassVisibilityCulledByDistanceTag FTag;`

#### struct `UE::Mass::Representation::TMassVisibilityTagForLevel`  
`template<> struct TMassVisibilityTagForLevel<EMassVisibility::CulledByDistance>`  
_L55-58_
- L39 _public typedef_ `typedef FMassTag FTag;`
- L45 _public typedef_ `typedef FMassVisibilityCanBeSeenTag FTag;`
- L51 _public typedef_ `typedef FMassVisibilityCulledByFrustumTag FTag;`
- L57 _public typedef_ `typedef FMassVisibilityCulledByDistanceTag FTag;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mass` (scope `UE`)
- L16 _namespace_ `namespace Representation` (scope `UE::Mass`)
- L19 _function_ `inline EMassVisibility GetVisibilityFromArchetype(const FMassExecutionContext& Context)` (scope `UE::Mass::Representation`)
- L60 _function_ `inline const UScriptStruct* GetTagFromVisibility(EMassVisibility Visibility)` (scope `UE::Mass::Representation`)
- L77 _function_ `inline bool IsVisibilityTagSet(const FMassExecutionContext& Context, EMassVisibility Visibility)` (scope `UE::Mass::Representation`)
- L94 _prototype_ `void PushSwapTagsCommand(FMassCommandBuffer& CommandBuffer, const FMassEntityHandle Entity, const EMassVisibility PrevVisibility, const EMassVisibility NewVisibility);` (scope `UE::Mass::Representation`)

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassSkinnedMeshRepresentationTypes.h` (Public)


#### struct `FMassSkinnedMeshResolvedAnimState`  
`struct FMassSkinnedMeshResolvedAnimState`  
_L32-38_
- desc: * Resolved animation state read back from ISKM tracks. * Populated during EndVisualChanges() where the ASTPD track data is already hot in cache. * Consumed by processors that need to push animation state to UAF.
- L34 _public member_ `int32 SequenceIndex = INDEX_NONE;`
- L35 _public member_ `float Position = 0.0f;`
- L36 _public member_ `float PlayRate = 1.0f;`
- L37 _public member_ `TWeakObjectPtr<UAnimSequence> AnimSequence = nullptr;`

#### struct `FMassSkinnedMeshInstanceVisualizationMeshDesc`  
`struct FMassSkinnedMeshInstanceVisualizationMeshDesc`  
_L43-146_
- reflection: `USTRUCT()`
- L47 _public prototype_ `FMassSkinnedMeshInstanceVisualizationMeshDesc();`
- L51 _public member_ `FTransform LocalTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — A relative Transform from the parent, passed along to FMassInstancedSkinnedMeshComponentSharedData::LocalTransform
- L55 _public member_ `TObjectPtr<USkinnedAsset> Asset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The mesh visual representation
- L59 _public member_ `TObjectPtr<UTransformProviderData> TransformProvider = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The Animation Transform Provider when using this mesh
- L67 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialOverrides;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Material overrides for the mesh visual representation. Array indices correspond to material slot indices on the mesh.
- L71 _public member_ `float MinLODSignificance = float(EMassLOD::High);` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The minimum inclusive LOD significance to start using this mesh
- L75 _public member_ `float MaxLODSignificance = float(EMassLOD::Max);` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — The maximum exclusive LOD significance to stop using this mesh
- L79 _public member_ `bool bCastShadows = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Controls whether the ISM can cast shadow or not
- L86 _public member_ `bool bRequiresExternalInstanceIDTracking = false;` — Determines the value of corresponding FMassISMCSharedData.bRequiresExternalInstanceIDTracking. Recommended enabled for stationary meshes. @see FMassISMCSharedData.bRequiresExternalInstanceIDTracking for details.
- L89 _public member_ `EComponentMobility::Type Mobility = EComponentMobility::Movable;` — Controls the mobility of the ISM
- L93 _public member_ `TSubclassOf<UInstancedSkinnedMeshComponent> InstancedSkinnedMeshComponentClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — InstancedSkinnedMeshComponent class to use to manage instances described by this struct instance
- L101 _public member_ `float AnimationMinScreenSize = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Passed to UInstancedSkinnedMeshComponent::SetAnimationMinScreenSize. Values: < 0 = always animate, 0 = use r.Skinning.DefaultAnimationMinScreenSize, > 0 = custom threshold. @see UInstancedSkinnedMeshComponent::SetAnimationMinScreenSize
- L103 _public function_ `bool operator==(const FMassSkinnedMeshInstanceVisualizationMeshDesc& Other) const`
- L140 _public function_ `void SetSignificanceRange(const EMassLOD::Type MinLOD, const EMassLOD::Type MaxLOD)` — convenience function for setting MinLODSinificance and MaxLODSinificance based on EMassLOD values

#### struct `FSkinnedMeshInstanceVisualizationDesc`  
`struct FSkinnedMeshInstanceVisualizationDesc : public FTableRowBase`  
_L149-187_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L158 _public member_ `TArray<FMassSkinnedMeshInstanceVisualizationMeshDesc> Meshes;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta=(TitleProperty="{Mesh}"))` — Mesh descriptions. These will be instanced together using the same transform for each, to visualize the given agent.
- L162 _public member_ `bool bUseTransformOffset = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Boolean to enable code to transform the meshes if not align the mass agent transform
- L166 _public member_ `FTransform TransformOffset = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta=(EditCondition="bUseTransformOffset"))` — Transform to offset the meshes if not align the mass agent transform
- L170 _public member_ `TArray<float> CustomDataFloats;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Custom data that can eventually be propagated to UInstancedSkinnedMeshComponent::PerInstanceCustomData
- L172 _public function_ `bool operator==(const FSkinnedMeshInstanceVisualizationDesc& Other) const`
- L177 _public function_ `void Reset()`
- L186 _public prototype_ `bool IsValid() const;` — @return whether any of descriptions in Meshes is valid. This implies that empty Meshes will be treated as not valid.

#### struct `FSkinnedMeshInstanceVisualizationDescHandle`  
`struct alignas(2) FSkinnedMeshInstanceVisualizationDescHandle`  
_L191-237_
- reflection: `USTRUCT()`
- desc: Handle for FSkinnedMeshInstanceVisualizationDesc's registered with UMassRepresentationSubsystem
- L195 _public member_ `static constexpr uint16 InvalidIndex = TNumericLimits<uint16>::Max();`
- L197 _public prototype_ `FSkinnedMeshInstanceVisualizationDescHandle () = default;`
- L199 _public function_ `explicit FSkinnedMeshInstanceVisualizationDescHandle (uint16 InIndex) : Index(InIndex)`
- L203 _public function_ `explicit FSkinnedMeshInstanceVisualizationDescHandle (int32 InIndex)`
- L217 _public function_ `inline int32 ToIndex() const`
- L222 _public function_ `bool IsValid() const`
- L227 _public prototype_ `bool operator==(const FSkinnedMeshInstanceVisualizationDescHandle & Other) const = default;`
- L232 _private member_ `uint16 Index = InvalidIndex;` — `UPROPERTY()`

#### struct `FMassInstancedSkinnedMeshComponentSharedData`  
`struct FMassInstancedSkinnedMeshComponentSharedData`  
_L240-371_
- L242 _public function_ `FMassInstancedSkinnedMeshComponentSharedData() : bRequiresExternalInstanceIDTracking(false)`
- L247 _public function_ `explicit FMassInstancedSkinnedMeshComponentSharedData(UInstancedSkinnedMeshComponent* InInstancedSkinnedMeshComponent, bool bInRequiresExternalInstanceIDTracking = false, const FTransform& InTransformOffset = FTransform::Identity) : LocalTransform(InTransformOffset), InstancedSkinnedMeshComponent(InInstancedSkinnedMeshComponent), bRequiresExternalInstanceIDTracking(bInRequiresExternalInstanceIDTracking)`
- L252 _public prototype_ `FMassInstancedSkinnedMeshComponentSharedData(const FMassInstancedSkinnedMeshComponentSharedData& Other) = default;`
- L253 _public prototype_ `FMassInstancedSkinnedMeshComponentSharedData& operator=(const FMassInstancedSkinnedMeshComponentSharedData& Other) = default;`
- L256 _public function_ `void SetInstancedSkinnedMeshComponent(UInstancedSkinnedMeshComponent& InInstancedSkinnedMeshComponent)`
- L263 _public function_ `UInstancedSkinnedMeshComponent* GetMutableInstancedSkinnedMeshComponent()`
- L264 _public function_ `const UInstancedSkinnedMeshComponent* GetInstancedSkinnedMeshComponent() const`
- L265 _public function_ `int32 OnInstancedSkinnedMeshComponentReferenceStored()`
- L266 _public function_ `int32 OnInstancedSkinnedMeshComponentReferenceReleased()`
- L272 _public function_ `void ResetAccumulatedData()`
- L283 _public function_ `void RemoveUpdatedInstanceIdsAtSwap(const int32 InstanceIDIndex)`
- L295 _public function_ `bool HasUpdatesToApply() const`
- L296 _public function_ `TConstArrayView<FMassEntityHandle> GetEntitiesRequiringUpdate() const`
- L297 _public function_ `TConstArrayView<FTransform> GetMeshInstanceTransforms() const`
- L298 _public function_ `TConstArrayView<FAnimSequenceTrackAutoPlayData> GetMeshInstanceAnimationData() const`
- L303 _public function_ `const TArray<FTransform>& GetMeshInstanceTransformsArray() const` — this function is a flavor we need to interact with older engine API that's using TArray references. Use GetMeshInstanceTransforms instead whenever possible.
- L304 _public function_ `const TArray<FAnimSequenceTrackAutoPlayData>& GetMeshInstanceAnimatioDataArray() const`
- L306 _public function_ `TConstArrayView<FTransform> GetMeshInstancePrevTransforms() const`
- L307 _public function_ `TConstArrayView<FMassEntityHandle> GetEntitiesRequiringRemoval() const`
- L308 _public function_ `TConstArrayView<float> GetMeshInstanceCustomFloats() const`
- L310 _public function_ `bool RequiresExternalInstanceIDTracking() const`
- L312 _public function_ `void Reset()`
- L317 _public typedef_ `using FEntityToPrimitiveIdMap = Experimental::TRobinHoodHashMap<FMassEntityHandle, FPrimitiveInstanceId>;`
- L318 _public typedef_ `using FEntityToTrackIdMap = Experimental::TRobinHoodHashMap<FMassEntityHandle, int32>;`
- L320 _public function_ `FEntityToPrimitiveIdMap& GetMutableEntityPrimitiveToIdMap()`
- L321 _public function_ `const FEntityToPrimitiveIdMap& GetEntityPrimitiveToIdMap() const`
- L323 _public function_ `FEntityToTrackIdMap& GetMutableEntityToTrackMap()`
- L324 _public function_ `const FEntityToTrackIdMap& GetEntityToTrackMap() const`
- L326 _public function_ `FEntityToPrimitiveIdMap& GetMutableEntityToPrimitiveIdMap()`
- L327 _public function_ `const FEntityToPrimitiveIdMap& GetEntityToPrimitiveIdMap() const`
- L329 _public function_ `int16 GetComponentInstanceIdTouchCounter() const`
- L335 _protected member_ `FTransform LocalTransform = FTransform::Identity;`
- L338 _protected member_ `TArray<FMassEntityHandle> EntitiesRequiringUpdate;` — Buffer holding current frame transforms for the mesh instances, used to batch update the transforms
- L339 _protected member_ `TArray<FTransform> MeshInstanceTransforms;`
- L340 _protected member_ `TArray<FTransform> MeshInstancePrevTransforms;`
- L342 _protected member_ `TArray<FAnimSequenceTrackAutoPlayData> MeshInstanceAnimationData;` — Buffer holding animation data
- L343 _protected member_ `TArray<FMassEntityHandle> EntitiesRequiringRemoval;`
- L346 _protected member_ `TArray<float> MeshInstanceCustomFloats;` — Buffer holding current frame custom floats for the mesh instances, used to batch update the ISMs custom data
- L349 _protected member_ `int32 WriteIterator = 0;` — When initially adding to MeshInstanceCustomFloats, can use the size as the write iterator, but on subsequent processors, we need to know where to start writing
- L351 _protected member_ `UInstancedSkinnedMeshComponent* InstancedSkinnedMeshComponent = nullptr;`
- L353 _protected member_ `int32 InstancedSkinnedMeshComponentReferencesCount = 0;`
- L361 _protected member_ `uint8 bRequiresExternalInstanceIDTracking : 1;` — When set to true will result in MassVisualizationComponent manually perform Instance ID-related operations instead of relying on ISMComponent's internal ID operations. @note this mechanism has been added in preparation of changes to ISM component to change access to its internal instance ID logic. WIP as of Jun 17th 2023
- L366 _private member_ `uint16 ComponentInstanceIdTouchCounter = 0;` — Indicates that mutating changes, that can affect MassInstanceIdToComponentInstanceIdMap, have been performed. Can be used to validate whether cached data stored in other placed needs to be re-cached.
- L369 _protected member_ `FEntityToPrimitiveIdMap EntityHandleToPrimitiveIdMap;`
- L370 _protected member_ `FEntityToTrackIdMap EntityHandleToTrackIdMap;`

#### struct `FMassInstancedSkinnedMeshComponentSharedDataMap`  
`struct FMassInstancedSkinnedMeshComponentSharedDataMap`  
_L385-555_
- desc: The container type hosting FMassInstancedSkinnedMeshSharedData instances and supplying functionality of marking entries that require instance-related operations (adding, removing). To get a FMassInstance instance to add operations to it call GetAndMarkDirty. Use FDirtyIterator to iterate over just the data that needs processing. @see UMassVisualizationComponent::EndVisualChanges for iteration @see FMassLODSignificanceRange methods for performing dirtying operations
- L430 _public function_ `FMassInstancedSkinnedMeshComponentSharedData& GetAndMarkDirtyChecked(const FInstancedSkinnedMeshComponentSharedDataKey OwnerKey)`
- L437 _public function_ `FMassInstancedSkinnedMeshComponentSharedData* GetAndMarkDirty(const FInstancedSkinnedMeshComponentSharedDataKey OwnerKey)`
- L449 _public function_ `template<typename... TArgs> FMassInstancedSkinnedMeshComponentSharedData& FindOrAdd(const FInstancedSkinnedMeshComponentSharedDataKey OwnerKey, TArgs&&... InNewInstanceArgs)`
- L460 _public function_ `FMassInstancedSkinnedMeshComponentSharedData* Find(const FInstancedSkinnedMeshComponentSharedDataKey OwnerKey)`
- L467 _public function_ `template<typename... TArgs> FMassInstancedSkinnedMeshComponentSharedData& Add(const FInstancedSkinnedMeshComponentSharedDataKey OwnerKey, TArgs&&... InNewInstanceArgs)`
- L486 _public function_ `void Remove(const FInstancedSkinnedMeshComponentSharedDataKey OwnerKey)`
- L497 _public function_ `FMassInstancedSkinnedMeshComponentSharedData& GetAtIndex(const int32 DataIndex)`
- L502 _public function_ `TBitArray<>& GetDirtyArray()`
- L508 _public function_ `int32 Num() const` — @return total number of entries in Data array. Note that some or all entries could be empty (i.e. already freed)
- L514 _public function_ `int32 NumValid() const` — @return number of non-empty entries in Data.
- L519 _public function_ `bool IsDirty(const int32 DataIndex) const`
- L524 _public function_ `bool IsEmpty() const`
- L529 _public function_ `void Reset()`
- L534 _public function_ `const FMassInstancedSkinnedMeshComponentSharedData* GetDataForIndex(const int32 Index) const`
- L539 _public function_ `const FMassInstancedSkinnedMeshComponentSharedData* GetDataForKey(const FInstancedSkinnedMeshComponentSharedDataKey Key) const`
- L548 _protected member_ `TArray<FMassInstancedSkinnedMeshComponentSharedData> Data;`
- L550 _protected member_ `TMap<FInstancedSkinnedMeshComponentSharedDataKey, int32> Map;` — Mapping from Owner (as FObjectKey) of data represented by FMassISMCSharedData to an index to Data
- L552 _protected member_ `TBitArray<> DirtyData;` — Indicates whether corresponding Data entry has any instance work assigned to it (instance addition or removal)
- L554 _protected member_ `TArray<int32> FreeIndices;` — Indices to Data that are available for reuse

#### struct `FMassInstancedSkinnedMeshComponentSharedDataMap::FDirtyIterator`  
`struct FDirtyIterator`  
_L387-428_
- L390 _public function_ `explicit FDirtyIterator(FMassInstancedSkinnedMeshComponentSharedDataMap& InContainer) : Container(InContainer), It(InContainer.GetDirtyArray())`
- L400 _public function_ `operator bool() const`
- L402 _public function_ `FDirtyIterator& operator++()`
- L414 _public function_ `FMassInstancedSkinnedMeshComponentSharedData& operator*() const`
- L419 _public function_ `void ClearDirtyFlag()`
- L425 _private member_ `FMassInstancedSkinnedMeshComponentSharedDataMap& Container;`
- L426 _private member_ `TBitArray<>::FIterator It;`
- L427 _private member_ `static constexpr bool bValueToCheck = true;`

#### struct `FMassLODInstancedSkinnedMeshSignificanceRange`  
`struct FMassLODInstancedSkinnedMeshSignificanceRange`  
_L560-625_
- reflection: `USTRUCT()`
- L565 _public prototype_ `void AddBatchedTransform(const FMassEntityHandle EntityHandle, const FTransform& Transform, const FTransform& PrevTransform, TConstArrayView<FInstancedSkinnedMeshComponentSharedDataKey> ExcludeMeshRefs);`
- L566 _public prototype_ `void AddBatchedAnimationData(const FMassEntityHandle EntityHandle, FAnimSequenceTrackAutoPlayData AnimationData, TConstArrayView<FInstancedSkinnedMeshComponentSharedDataKey> ExcludeMeshRefs);`
- L571 _public function_ `template<typename InCustomDataType> void AddBatchedCustomData(InCustomDataType InCustomData, const TArray<FInstancedSkinnedMeshComponentSharedDataKey>& ExcludeMeshRefs, int32 NumFloatsToPad = 0)` — Adds the specified struct reinterpreted as custom floats to our custom data. Individual members of the specified struct should always fit into a float. When adding any custom data, the custom data must be added for every instance.
- L597 _public prototype_ `void AddBatchedCustomDataFloats(const TArray<float>& CustomFloats, const TArray<FInstancedSkinnedMeshComponentSharedDataKey>& ExcludeMeshRefs);` — Adds uniform custom data, CustomFloats is applied to all meshes in the SignificanceRange. Only safe to call from a Mass Processor. Requires: UMassRepresentationSubsystem (ReadWrite)
- L605 _public prototype_ `void AddBatchedCustomDataFloats(TConstArrayView<TArray<float>> PerMeshFloats, const TArray<FInstancedSkinnedMeshComponentSharedDataKey>& ExcludeMeshRefs);` — Adds per-mesh custom data, PerMeshFloats is indexed in source Desc.Meshes order. Only safe to call from a Mass Processor. Requires: UMassRepresentationSubsystem (ReadWrite)
- L608 _public prototype_ `void AddInstance(const FMassEntityHandle EntityHandle, const FTransform& Transform);` — Single-instance version of AddBatchedCustomData when called to add entities (as opposed to modify existing ones).
- L610 _public prototype_ `void RemoveInstance(const FMassEntityHandle EntityHandle);`
- L612 _public prototype_ `void WriteCustomDataFloatsAtStartIndex(int32 MeshIndex, const TArrayView<float>& CustomFloats, const int32 FloatsPerInstance, const int32 StartIndex, const TArray<FInstancedSkinnedMeshComponentSharedDataKey>& ExcludeMeshRefs);`
- L615 _public member_ `float MinSignificance = 0.0f;` — LOD Significance range
- L616 _public member_ `float MaxSignificance = 0.0f;`
- L619 _public member_ `TArray<FInstancedSkinnedMeshComponentSharedDataKey> SkinnedMeshComponentRefs;` — The component handling these instances
- L622 _public member_ `TArray<int32> SourceDescMeshIndices;` — Source Desc.Meshes index per SkinnedMeshComponentRefs entry.
- L624 _public member_ `FMassInstancedSkinnedMeshComponentSharedDataMap* InstancedSkinnedMeshSharedDataPtr = nullptr;`

#### struct `FMassInstancedSkinnedMeshInfo`  
`struct FMassInstancedSkinnedMeshInfo`  
_L629-824_
- reflection: `USTRUCT()`
- L634 _public prototype_ `FMassInstancedSkinnedMeshInfo() = default;`
- L636 _public function_ `explicit FMassInstancedSkinnedMeshInfo(const FSkinnedMeshInstanceVisualizationDesc& InDesc) : Desc(InDesc)`
- L642 _public prototype_ `void Reset();` — Clears out contents so that a given FMassInstancedSkinnedMeshInfo instance can be reused
- L644 _public function_ `const FSkinnedMeshInstanceVisualizationDesc& GetDesc() const`
- L650 _public function_ `bool ShouldUseTransformOffset() const` — Whether or not to transform the  meshes if not align the mass agent transform
- L651 _public function_ `FTransform GetTransformOffset() const`
- L653 _public function_ `inline FMassLODInstancedSkinnedMeshSignificanceRange* GetLODSignificanceRange(float LODSignificance)`
- L665 _public function_ `void AddBatchedTransform(const FMassEntityHandle EntityHandle, const FTransform& Transform, const FTransform& PrevTransform, const float LODSignificance, const float PrevLODSignificance = -1.0f)`
- L682 _public function_ `void AddBatchedAnimationData(const FMassEntityHandle EntityHandle, FAnimSequenceTrackAutoPlayData AnimationData, const float LODSignificance, const float PrevLODSignificance = -1.0f)`
- L700 _public function_ `inline void RemoveInstance(const FMassEntityHandle EntityHandle, const float LODSignificance)`
- L711 _public function_ `template<typename InCustomDataType> void AddBatchedCustomData(InCustomDataType InCustomData, const float LODSignificance, const float PrevLODSignificance = -1.0f, int32 NumFloatsToPad = 0)` — Adds the specified struct reinterpreted as custom floats to our custom data. Individual members of the specified struct should always fit into a float. When adding any custom data, the custom data must be added for every instance.
- L734 _public function_ `inline void AddBatchedCustomDataFloats(const TArray<float>& CustomFloats, const float LODSignificance, const float PrevLODSignificance = -1.0f)` — Adds uniform custom data, CustomFloats is applied to all meshes of the given LODSignificance. Only safe to call from a Mass Processor. Requires: UMassRepresentationSubsystem (ReadWrite)
- L757 _public function_ `inline void AddBatchedCustomDataFloats(TConstArrayView<TArray<float>> PerMeshFloats, const float LODSignificance, const float PrevLODSignificance = -1.0f)` — Adds per-mesh custom data, PerMeshFloats is indexed in source Desc.Meshes order. Only safe to call from a Mass Processor. Requires: UMassRepresentationSubsystem (ReadWrite)
- L774 _public function_ `void WriteCustomDataFloatsAtStartIndex(int32 MeshIndex, const TArrayView<float>& CustomFloats, const float LODSignificance, const int32 FloatsPerInstance, const int32 FloatStartIndex, const float PrevLODSignificance = -1.0f)`
- L791 _public function_ `void AddInstancedSkinnedMeshComponent(FMassInstancedSkinnedMeshComponentSharedData& SharedData)`
- L800 _public function_ `int32 GetLODSignificanceRangesNum() const`
- L802 _public function_ `bool IsValid() const`
- L810 _protected prototype_ `void ClearVisualInstance(UInstancedSkinnedMeshComponent& ISMComponent);` — Destroy the visual instance
- L814 _protected member_ `FSkinnedMeshInstanceVisualizationDesc Desc;` — `UPROPERTY(VisibleAnywhere, Category = "Mass/Debug")` — Information about this  mesh which will represent all instances
- L818 _protected member_ `TArray<TObjectPtr<UInstancedSkinnedMeshComponent>> InstancedSkinnedMeshComponents;` — `UPROPERTY(VisibleAnywhere, Category = "Mass/Debug")` — The components handling these instances
- L821 _protected member_ `TArray<FMassLODInstancedSkinnedMeshSignificanceRange> LODSignificanceRanges;` — `UPROPERTY(VisibleAnywhere, Category = "Mass/Debug")`

#### struct `FMassInstancedSkinnedMeshInfoArrayViewAccessDetector`  
`struct FMassInstancedSkinnedMeshInfoArrayViewAccessDetector`  
_L830-874_
- L832 _public function_ `FMassInstancedSkinnedMeshInfoArrayViewAccessDetector(TArrayView<FMassInstancedSkinnedMeshInfo> InInstancedSkinnedMeshInfos, const FRWAccessDetector& InAccessDetector) : InstancedSkinnedMeshInfos(InInstancedSkinnedMeshInfos) , AccessDetector(&InAccessDetector)`
- L839 _public function_ `FMassInstancedSkinnedMeshInfoArrayViewAccessDetector(FMassInstancedSkinnedMeshInfoArrayViewAccessDetector&& Other) : InstancedSkinnedMeshInfos(Other.InstancedSkinnedMeshInfos) , AccessDetector(Other.AccessDetector)`
- L845 _public prototype_ `FMassInstancedSkinnedMeshInfoArrayViewAccessDetector(const FMassInstancedSkinnedMeshInfoArrayViewAccessDetector& Other) = delete;`
- L846 _public prototype_ `void operator=(const FMassInstancedSkinnedMeshInfoArrayViewAccessDetector& Other) = delete;`
- L848 _public function_ `~FMassInstancedSkinnedMeshInfoArrayViewAccessDetector()`
- L856 _public function_ `inline FMassInstancedSkinnedMeshInfo& operator[](int32 Index) const`
- L861 _public function_ `bool IsValidIndex(const int32 Index) const`
- L866 _public function_ `int32 Num() const`
- L872 _private member_ `TArrayView<FMassInstancedSkinnedMeshInfo> InstancedSkinnedMeshInfos;`
- L873 _private member_ `const FRWAccessDetector* AccessDetector;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MASSREPRESENTATION_API`
- L40 _typedef_ `using FInstancedSkinnedMeshComponentSharedDataKey = TObjectKey<UInstancedSkinnedMeshComponent>;`
- L118 _function_ `friend inline uint32 GetTypeHash(const FMassSkinnedMeshInstanceVisualizationMeshDesc& MeshDesc)`
- L829 _macro_ `#define MAKE_MASS_INSTANCED_SKINNED_MESH_INFO_ARRAY_VIEW(ArrayView, AccessDetector) FMassInstancedSkinnedMeshInfoArrayView(ArrayView, AccessDetector)`
- L876 _typedef_ `using FMassInstancedSkinnedMeshInfoArrayView = FMassInstancedSkinnedMeshInfoArrayViewAccessDetector;`
- L881 _macro_ `#define MAKE_MASS_INSTANCED_SKINNED_MESH_INFO_ARRAY_VIEW(ArrayView, AccessDetector) ArrayView`
- L882 _typedef_ `using FMassInstancedSkinnedMeshInfoArrayView = TArrayView<FMassInstancedSkinnedMeshInfo>;`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassStationaryDistanceVisualizationTrait.h` (Public)


#### class `UMassStationaryDistanceVisualizationTrait`  
`class UMassStationaryDistanceVisualizationTrait : public UMassDistanceVisualizationTrait`  
_L12-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassDistanceVisualizationTrait`
- L16 _public prototype_ `UMassStationaryDistanceVisualizationTrait(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L18 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L22 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassStationaryISMRepresentationFragmentDestructor.h` (Public)


#### class `UMassStationaryISMRepresentationFragmentDestructor`  
`class UMassStationaryISMRepresentationFragmentDestructor : public UMassObserverProcessor`  
_L16-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: This class is responsible for cleaning up ISM instances visualizing stationary entities
- L20 _public prototype_ `UMassStationaryISMRepresentationFragmentDestructor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L26 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassStationaryISMSwitcherProcessor.h` (Public)


#### struct `FMassStationaryISMSwitcherProcessorTag`  
`struct FMassStationaryISMSwitcherProcessorTag : public FMassTag`  
_L25-28_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag required by UMassStationaryISMSwitcherProcessor to process given archetype. Removing the tag allows to support temporary disabling of processing for individual entities of given archetype.

#### class `UMassStationaryISMSwitcherProcessor`  
`class UMassStationaryISMSwitcherProcessor : public UMassProcessor`  
_L36-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor's sole responsibility is to process all entities tagged with FMassStaticRepresentationTag and check if they've switched to or away from EMassRepresentationType::StaticMeshInstance or EMassRepresentationType::SkinnedMeshInstance ; and acordingly add or remove the entity from the appropriate ArrayView.
- L41 _public prototype_ `UMassStationaryISMSwitcherProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L43 _public prototype_ `static void ProcessContext(FMassExecutionContext& Context);`
- L47 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — UMassProcessor overrides begin
- L51 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — UMassProcessor overrides end UMassRepresentationProcessor overrides begin
- L54 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSREPRESENTATION_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L14 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L16 _variable_ `const FName SwitchedToActor = FName(TEXT("Swit` (scope `UE::Mass::Signals`)
- L17 _variable_ `const FName SwitchedToISM = FName(TEXT("Swit` (scope `UE::Mass::Signals`)

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassStationaryVisualizationTrait.h` (Public)


#### class `UMassStationaryVisualizationTrait`  
`class UMassStationaryVisualizationTrait : public UMassVisualizationTrait`  
_L12-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassVisualizationTrait`
- L16 _public prototype_ `UMassStationaryVisualizationTrait(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L18 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L22 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassUpdateISMProcessor.h` (Public)


#### class `UMassUpdateISMProcessor`  
`class UMassUpdateISMProcessor : public UMassProcessor`  
_L16-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L21 _public prototype_ `UMassUpdateISMProcessor();`
- L23 _public prototype_ `static void UpdateISMTransform(FMassEntityHandle EntityHandle, FMassInstancedStaticMeshInfo& ISMInfo, const FTransform& Transform, const FTransform& PrevTransform, const float LODSignificance, const float PrevLODSignificance = -1.0f);`
- L28 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L34 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L36 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassUpdateSkinnedMeshProcessor.h` (Public)


#### class `UMassUpdateInstancedSkinnedMeshProcessor`  
`class UMassUpdateInstancedSkinnedMeshProcessor : public UMassProcessor`  
_L15-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L20 _public prototype_ `UMassUpdateInstancedSkinnedMeshProcessor();`
- L22 _public prototype_ `static void UpdateMeshTransform(FMassEntityHandle EntityHandle, FMassInstancedSkinnedMeshInfo& MeshInfo, const FTransform& Transform, const FTransform& PrevTransform, const float LODSignificance, const float PrevLODSignificance = -1.0f);`
- L27 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L33 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L35 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassVisualizationComponent.h` (Public)


#### class `UMassVisualizationComponent`  
`class UMassVisualizationComponent : public UActorComponent`  
_L21-236_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- desc: This component handles all the static mesh instances for a MassRepresentationProcessor and is an actor component off a MassVisualizer actor. Meant to be created at runtime and owned by an MassVisualizer actor. Will ensure if placed on a different type of actor.
- L31 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle FindOrAddVisualDesc(const FStaticMeshInstanceVisualizationDesc& Desc);` — Get the index of the visual type, will add a new one if does not exist @param Desc is the information for the visual that will be instantiated later via AddVisualInstance() @return The index of the visual type
- L38 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle AddVisualDescWithISMComponent(const FStaticMeshInstanceVisualizationDesc& Desc, UInstancedStaticMeshComponent& ISMComponent);` — Creates a dedicated visual type described by host Desc and ties ISMComponent to it. @note this is a helper function for a common "single ISMComponent" case. Calls AddVisualDescWithISMComponents under the hood. @return The index of the visual type
- L44 _public prototype_ `FStaticMeshInstanceVisualizationDescHandle AddVisualDescWithISMComponents(const FStaticMeshInstanceVisualizationDesc& Desc, TArrayView<TObjectPtr<UInstancedStaticMeshComponent>> ISMComponents);` — Creates a dedicated visual type described by host Desc and ties given ISMComponents to it. @return The index of the visual type
- L49 _public prototype_ `const FMassISMCSharedData* GetISMCSharedDataForDescriptionIndex(const int32 DescriptionIndex) const;` — Fetches FMassISMCSharedData indicated by DescriptionIndex, or nullptr if it's not a valid index
- L54 _public prototype_ `const FMassISMCSharedData* GetISMCSharedDataForInstancedStaticMesh(const UInstancedStaticMeshComponent* ISMC) const;` — Fetches FMassISMCSharedData indicated by an ISMC, or nullptr if the ISMC is not represented by any shared data.
- L60 _public prototype_ `void RemoveVisualDesc(const FStaticMeshInstanceVisualizationDescHandle VisualizationHandle);` — Removes all data associated with a given VisualizationIndex. Note that this is safe to do only if there are no entities relying on this index. No entity data patching will take place.
- L63 _public function_ `FMassInstancedStaticMeshInfoArrayView GetMutableVisualInfos()` — Get the array of all visual instance informations
- L70 _public prototype_ `void ClearAllVisualInstances();` — Destroy all visual instances
- L73 _public prototype_ `void DirtyVisuals();` — Dirty render state on all static mesh components
- L76 _public prototype_ `void BeginVisualChanges();` — Signal the beginning of the static mesh instance changes, used to prepare the batching update of the static mesh instance transforms
- L79 _public prototype_ `void EndVisualChanges();` — Signal the end of the static mesh instance changes, used to batch apply the transforms on the static mesh instances
- L85 _protected prototype_ `void ProcessRemoves(UInstancedStaticMeshComponent& ISMComponent, FMassISMCSharedData& SharedData, bool bUpdateNavigation = true);` — Process all removed IDs in FMassISMCSharedData and apply to the ISM component.
- L91 _protected prototype_ `void HandleChangesWithExternalIDTracking(UInstancedStaticMeshComponent& ISMComponent, FMassISMCSharedData& SharedData);` — Applies changes accumulated in SharedData while manually updating the Instance ID mapping. This approach is done in preparation to upcoming ISM changes to keep the mapping management more secure (by making mapping private and fully component-owned).
- L94 _protected prototype_ `void ConstructStaticMeshComponents();` — Recreate all the static mesh components from the InstancedStaticMeshInfos
- L97 _protected prototype_ `virtual void PostInitProperties() override;` — Overridden to make sure this component is only added to a MassVisualizer actor
- L104 _protected prototype_ `void BuildLODSignificanceForInfo(FMassInstancedStaticMeshInfo& Info, TConstArrayView<UInstancedStaticMeshComponent*> StaticMeshRefKeys);` — Creates LODSignificance ranges for all the meshes indicated by Info @param ForcedStaticMeshRefKeys if not empty will be used when adding individual FMassStaticMeshInstanceVisualizationMeshDesc instances to LOD significance ranges.
- L107 _protected prototype_ `FStaticMeshInstanceVisualizationDescHandle AddInstancedStaticMeshInfo(const FStaticMeshInstanceVisualizationDesc& Desc);` — Either adds an element to InstancedStaticMeshInfos or reuses an existing entry based on InstancedStaticMeshInfosFreeIndices
- L111 _protected member_ `TArray<FMassInstancedStaticMeshInfo> InstancedStaticMeshInfos;` — `UPROPERTY(Transient)` — The information of all the instanced static meshes. Make sure to use AddInstancedStaticMeshInfo to add elements to it
- L112 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(InstancedStaticMeshInfosDetector);`
- L115 _protected member_ `TArray<FStaticMeshInstanceVisualizationDescHandle> InstancedStaticMeshInfosFreeIndices;` — Indices to InstancedStaticMeshInfos that have been released and can be reused
- L118 _protected member_ `TMap<FISMCSharedDataKey, FStaticMeshInstanceVisualizationDescHandle> ISMComponentMap;` — Mapping from ISMComponent (indicated by FISMCSharedDataKey) to corresponding VisualDescHandle
- L120 _protected member_ `FMassISMCSharedDataMap ISMCSharedData;`
- L128 _protected member_ `TMap<uint32, FISMCSharedDataKey> MeshDescToISMCMap;` — Mapping FMassStaticMeshInstanceVisualizationMeshDesc hash to FMassISMCSharedData entries for all FMassStaticMeshInstanceVisualizationMeshDesc that didn't come with ISMC explicitly provided. Used only for initialization. Note that FMassStaticMeshInstanceVisualizationMeshDesc that were added with ISMComponents provided directly (via AddVisualDescWithISMComponents call) will never make it to this map.
- L131 _protected member_ `TArray<FStaticMeshInstanceVisualizationDescHandle> InstancedSMComponentsRequiringConstructing;` — Indices to InstancedStaticMeshInfos that need their SMComponent constructed
- L139 _public prototype_ `FSkinnedMeshInstanceVisualizationDescHandle FindOrAddSkinnedMeshInstanceVisualDesc(const FSkinnedMeshInstanceVisualizationDesc& Desc);` — Get the index of the visual type, will add a new one if does not exist @param Desc is the information for the visual that will be instantiated later via AddVisualInstance() @return The index of the visual type
- L146 _public prototype_ `FSkinnedMeshInstanceVisualizationDescHandle AddSkinnedMeshInstanceVisualDescWithComponent(const FSkinnedMeshInstanceVisualizationDesc& Desc, UInstancedSkinnedMeshComponent& InstancedSkinnedMeshComponent);` — Creates a dedicated visual type described by host Desc and ties InstancedSkinnedMeshComponent to it. @note this is a helper function for a common "single ISMComponent" case. Calls AddVisualDescWithComponents under the hood. @return The index of the visual type
- L152 _public prototype_ `FSkinnedMeshInstanceVisualizationDescHandle AddSkinnedMeshInstanceVisualDescWithComponents(const FSkinnedMeshInstanceVisualizationDesc& Desc, TArrayView<TObjectPtr<UInstancedSkinnedMeshComponent>> InstancedSkinnedMeshComponents);` — Creates a dedicated visual type described by host Desc and ties given InstancedSkinnedMeshComponents to it. @return The index of the visual type
- L157 _public prototype_ `const FMassInstancedSkinnedMeshComponentSharedData* GetSharedDataForDescriptionIndex(const int32 DescriptionIndex) const;` — Fetches FMassInstancedSkinnedMeshComponentSharedData indicated by DescriptionIndex, or nullptr if it's not a valid index
- L162 _public prototype_ `const FMassInstancedSkinnedMeshComponentSharedData* GetSharedDataForInstancedSkinnedMeshComponent(const UInstancedSkinnedMeshComponent* InstancedSkinnedMeshComponent) const;` — Fetches FMassInstancedSkinnedMeshComponentSharedData indicated by an InstancedSkinnedMeshComponent, or nullptr if the InstancedSkinnedMeshComponent is not represented by any shared data.
- L168 _public prototype_ `void RemoveSkinnedMeshInstanceVisualDesc(const FSkinnedMeshInstanceVisualizationDescHandle VisualizationHandle);` — Removes all data associated with a given VisualizationIndex. Note that this is safe to do only if there are no entities relying on this index. No entity data patching will take place.
- L171 _public function_ `FMassInstancedSkinnedMeshInfoArrayView GetMutableInstanceVisualInfos()` — Get the array of all visual instance informations
- L177 _public function_ `const FMassSkinnedMeshResolvedAnimState* FindResolvedAnimState(const FMassEntityHandle& EntityHandle) const`
- L186 _protected prototype_ `void ProcessRemovesForComponent(UInstancedSkinnedMeshComponent& InstancedSkinnedMeshComponent, FMassInstancedSkinnedMeshComponentSharedData& SharedData);` — Process all removed IDs in FMassInstancedSkinnedMeshComponentSharedData and apply to the Instanced Skinned Mesh component.
- L192 _protected prototype_ `void HandleChangesWithExternalIDTrackingForComponent(UInstancedSkinnedMeshComponent& InstancedSkinnedMeshComponent, FMassInstancedSkinnedMeshComponentSharedData& SharedData);` — Applies changes accumulated in SharedData while manually updating the Instance ID mapping. This approach is done in preparation to upcoming Instanced Mesh changes to keep the mapping management more secure (by making mapping private and fully component-owned).
- L195 _protected prototype_ `void ConstructSkinnedMeshComponents();` — Recreate all the instanced skinned mesh components from the InstancedSkinnedMeshInfos
- L202 _protected prototype_ `void BuildLODSignificanceForInstancedSkinnedMeshInfo(FMassInstancedSkinnedMeshInfo& Info, TConstArrayView<UInstancedSkinnedMeshComponent*> MeshRefKeys);` — Creates LODSignificance ranges for all the meshes indicated by Info @param MeshRefKeys if not empty will be used when adding individual FMassSkinnedMeshInstanceVisualizationMeshDesc instances to LOD significance ranges.
- L205 _protected prototype_ `FSkinnedMeshInstanceVisualizationDescHandle AddInstancedSkinnedMeshInfo(const FSkinnedMeshInstanceVisualizationDesc& Desc);` — Either adds an element to InstancedSkinnedMeshInfos or reuses an existing entry based on InstancedSkinnedMeshInfosFreeIndices
- L209 _protected member_ `TArray<FMassInstancedSkinnedMeshInfo> InstancedSkinnedMeshInfos;` — `UPROPERTY(Transient)` — The information of all the instanced skinned meshes. Make sure to use AddInstancedSkinnedMeshInfo to add elements to it
- L210 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(InstancedSkinnedMeshInfosDetector);`
- L213 _protected member_ `TArray<FSkinnedMeshInstanceVisualizationDescHandle> InstancedSkinnedMeshInfosFreeIndices;` — Indices to InstancedSkinnedMeshInfos that have been released and can be reused
- L216 _protected member_ `TMap<FInstancedSkinnedMeshComponentSharedDataKey, FSkinnedMeshInstanceVisualizationDescHandle> InstancedSkinnedMeshComponentMap;` — Mapping from InstancedSkinnedMeshComponent (indicated by FInstancedSkinnedMeshComponentSharedDataKey) to corresponding SkinnedMeshInstanceVisualizationDescHandle
- L218 _protected member_ `FMassInstancedSkinnedMeshComponentSharedDataMap InstancedSkinnedMeshComponentSharedData;`
- L226 _protected member_ `TMap<uint32, FInstancedSkinnedMeshComponentSharedDataKey> MeshDescToInstancedSkinnedMeshComponentMap;` — Mapping FMassSkinnedMeshInstanceVisualizationMeshDesc hash to FMassInstancedSkinnedMeshSharedData entries for all FMassSkinnedMeshInstanceVisualizationMeshDesc that didn't come with Instanced Skinned Mesh Component explicitly provided. Used only for initialization. Note that FMassSkinnedMeshInstanceVisualizationMeshDesc that were added with InstancedSkinnedMeshComponents provided directly (via AddVisualDescWithComponents call) will never make it to this map.
- L229 _protected member_ `TArray<FSkinnedMeshInstanceVisualizationDescHandle> InstancedSkinnedMeshComponentsRequiringConstructing;` — Indices to InstancedSkinnedMeshInfos that need their Skinned Mesh Component constructed
- L234 _protected member_ `Experimental::TRobinHoodHashMap<FMassEntityHandle, FMassSkinnedMeshResolvedAnimState> ResolvedAnimStates;` — Resolved animation state per entity, populated during EndVisualChanges(). Keyed by entity handle — one entry per entity regardless of how many ISKMs it has. Read by processors that need to push animation state to UAF during representation handoff.

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassVisualizationLODProcessor.h` (Public)


#### struct `FMassVisualizationLODProcessorTag`  
`struct FMassVisualizationLODProcessorTag : public FMassTag`  
_L19-22_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag required by Visualization LOD Processor to update LOD information. Removing the tag allows to support temporary disabling of processing for individual entities.

#### class `UMassVisualizationLODProcessor`  
`class UMassVisualizationLODProcessor : public UMassProcessor`  
_L25-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L30 _public prototype_ `UMassVisualizationLODProcessor();`
- L35 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L42 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L48 _protected function_ `void ForceOffLOD(bool bForce)` — Forces Off LOD on all calculation @param bForce to whether force or not Off LOD
- L51 _protected member_ `FMassEntityQuery CloseEntityQuery;`
- L52 _protected member_ `FMassEntityQuery CloseEntityAdjustDistanceQuery;`
- L53 _protected member_ `FMassEntityQuery FarEntityQuery;`
- L54 _protected member_ `FMassEntityQuery DebugEntityQuery;`
- L56 _protected member_ `bool bForceOFFLOD = false;`
- L59 _protected member_ `TObjectPtr<const UScriptStruct> FilterTag = nullptr;` — `UPROPERTY(Transient)`
- L62 _protected member_ `bool bDoAdjustmentFromCount = true;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Mass")`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassVisualizationTrait.h` (Public)


#### class `UMassVisualizationTrait`  
`class UMassVisualizationTrait : public UMassEntityTraitBase`  
_L20-110_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="DEPRECATED Visualization"))`
- inherits: `UMassEntityTraitBase`
- desc: This class has been soft-deprecated. Use MassStationaryVisualizationTrait or MassMovableVisualizationTrait
- L24 _public prototype_ `UMassVisualizationTrait();`
- L28 _public member_ `mutable FStaticMeshInstanceVisualizationDesc StaticMeshInstanceDesc;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Instanced static mesh information for this agent
- L32 _public member_ `mutable FSkinnedMeshInstanceVisualizationDesc SkinnedMeshInstanceDesc;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Instanced skinned mesh information for this agent
- L36 _public member_ `TSubclassOf<AActor> HighResTemplateActor;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Actor class of this agent when spawned in high resolution
- L40 _public member_ `TSubclassOf<AActor> LowResTemplateActor;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Actor class of this agent when spawned in low resolution
- L44 _public member_ `TSubclassOf<UMassRepresentationSubsystem> RepresentationSubsystemClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual", meta = (EditCondition = "bCanModifyRepresentationSubsystemClass"))` — Allow subclasses to override the representation subsystem to use
- L48 _public member_ `FMassRepresentationParameters Params;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Configuration parameters for the representation processor
- L52 _public member_ `FMassVisualizationLODParameters LODParams;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Configuration parameters for the visualization LOD processor
- L57 _public member_ `bool bAllowServerSideVisualization = false;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — If set to true will result in the visualization-related fragments being added to server-size entities as well. By default only the clients require visualization fragments
- L62 _public member_ `bool bCanModifyRepresentationSubsystemClass = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|Visual")` — the property is marked like this to ensure it won't show up in UI
- L73 _public member_ `bool bRequireValidStaticMeshInstanceDesc = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|Visual", AdvancedDisplay)` — When True, ValidateParams() will require a valid StaticMeshInstanceDesc. When False, ValidateParams() skips checking the StaticMeshInstanceDesc. Use False when you expect a given Trait to have invalid StaticMeshInstanceDesc settings, and you don't want errors logged when it occurs.
- L82 _protected member_ `bool bRegisterStaticMeshDesc = true;` — Controls whether StaticMeshInstanceDesc gets registered via FindOrAddStaticMeshDesc call. Setting it to `false` can be useful for subclasses to avoid needlessly creating visualization data in RepresentationSubsystem, data that will never be used.
- L84 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L85 _protected prototype_ `virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const override;`
- L94 _protected prototype_ `virtual void SanitizeParams(FMassRepresentationParameters& InOutParams, const bool bStaticMeshDeterminedInvalid = false) const;` — `UE_DEPRECATED(5.8, "Please use SanitizeMeshParams version for ISKM Support")` — Tests whether StaticMeshInstanceDesc is valid and if not cleans up InOutParamss of EMassRepresentationType::StaticMeshInstance occurrences. @param bStaticMeshDeterminedInvalid if StaticMeshInstanceDesc has already been determined invalid then bStaticMeshDeterminedInvalid can be set to `true` to skip the redundant check.
- L103 _protected prototype_ `virtual void SanitizeMeshParams(FMassRepresentationParameters& InOutParams, const bool bStaticMeshDeterminedInvalid = false, const bool bSkinnedMeshDeterminedInvalid = false) const;` — Tests whether StaticMeshInstanceDesc and SkinnedMeshInstanceDesc are valid and if not cleans up InOutParams for those occurrences. @param bStaticMeshDeterminedInvalid if StaticMeshInstanceDesc has already been determined invalid then bStaticMeshDeterminedInvalid can be set to `true` to skip the redundant check. @param bSkinnedMeshDeterminedInvalid if SkinnedMeshInstanceDesc has already been determined invalid then bSkinnedMeshDeterminedInvalid can be set to `true` to skip the redundant check.
- L105 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L107 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L108 _protected prototype_ `virtual bool ValidateParams() const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSREPRESENTATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassRepresentation/Public/MassVisualizer.h` (Public)


#### class `AMassVisualizer`  
`class AMassVisualizer : public AActor`  
_L18-30_
- reflection: `UCLASS(MinimalAPI, NotPlaceable, Transient)`
- inherits: `AActor`
- desc: Actor holding the mass visual component responsible to handle the representation of the mass agent as the static mesh instances There may be a separate instance of these for different types of Agents (Cars, NPC's etc)
- L22 _public prototype_ `AMassVisualizer();`
- L25 _public function_ `UMassVisualizationComponent& GetVisualizationComponent() const` — Visualization component is guaranteed to exist if this class is created
- L29 _protected member_ `TObjectPtr<UMassVisualizationComponent> VisComponent;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSREPRESENTATION_API`
