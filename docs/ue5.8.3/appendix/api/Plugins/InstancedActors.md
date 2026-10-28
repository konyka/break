# Plugins / InstancedActors

- module root: `Plugins/Runtime/InstancedActors/Source/InstancedActors`
- headers: 30; symbols: 831
- symbol kinds: class=25, delegate=3, enum=10, enumerator=31, externvar=5, function=116, macro=18, member=215, namespace=20, prototype=340, struct=33, typedef=11, variable=4
- PrivateDependencyModuleNames: InputCore, MassGameplayDebug, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, GameFeatures, GameplayTags, MassActors, MassCommon, MassCore, MassEntity, MassLOD, MassRepresentation, MassSignals, MassSmartObjects, MassSpawner, NetCore

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/ClientInstancedActorsSpawnerSubsystem.h` (Public)


#### class `UClientInstancedActorsSpawnerSubsystem`  
`class UClientInstancedActorsSpawnerSubsystem : public UMassActorSpawnerSubsystem`  
_L17-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassActorSpawnerSubsystem`
- desc: Used on Clients to handle actor spawning synchronized with the Server. At the moment it boils down to storing actor spawning requests and putting them in Pending state until the server-spawned actor gets replicated over to the Client.
- L23 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L27 _protected prototype_ `virtual ESpawnRequestStatus SpawnActor(const FSpawnArgs& Args, FActorSpawnParameters& InOutSpawnParameters) const override;`
- L28 _protected prototype_ `virtual bool ReleaseActorToPool(AActor* Actor) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INSTANCEDACTORS_API`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/GameFeatureAction_ConfigureInstancedActors.h` (Public)


#### class `UGameFeatureAction_ConfigureInstancedActors`  
`class UGameFeatureAction_ConfigureInstancedActors : public UGameFeatureAction`  
_L14-28_
- reflection: `UCLASS(meta = (DisplayName = "Configure InstancedActors"))`
- inherits: `UGameFeatureAction`
- desc: GameplayFeature Action carrying overrides to InstancedActors settings
- L20 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;`
- L21 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L27 _private member_ `FInstancedActorsConfig ConfigOverride;` — `UPROPERTY(EditAnywhere, Category=InstancedActors)`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/GameplayDebuggerCategory_InstancedActors.h` (Public)


#### class `FGameplayDebuggerCategory_InstancedActors`  
`class FGameplayDebuggerCategory_InstancedActors : public FGameplayDebuggerCategory`  
_L18-53_
- inherits: `FGameplayDebuggerCategory`
- desc: Gameplay debugger used to debug Intanced Actors
- L21 _public prototype_ `FGameplayDebuggerCategory_InstancedActors();`
- L22 _public prototype_ `~FGameplayDebuggerCategory_InstancedActors();`
- L24 _public prototype_ `void SetCachedEntity(const FMassEntityHandle Entity, const FMassEntityManager& EntityManager);`
- L25 _public prototype_ `void OnEntitySelected(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L26 _public prototype_ `void ClearCachedEntity();`
- L28 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L30 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L34 _protected member_ `static TArray<FAutoConsoleCommandWithWorld> ConsoleCommands;`
- L35 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConsoleCommandBroadcastDelegate, UWorld*);`
- L36 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleDebugLocalIAMsBroadcast;`
- L38 _protected typedef_ `using FDelegateHandlePair = TPair<FOnConsoleCommandBroadcastDelegate*, FDelegateHandle>;`
- L39 _protected member_ `TArray<FDelegateHandlePair> ConsoleCommandHandles;`
- L41 _protected member_ `int32 ToggleDebugLocalIAMsInputIndex = INDEX_NONE;`
- L43 _protected prototype_ `void OnToggleDebugLocalIAMs();`
- L47 _private member_ `bool bDebugLocalIAMs = false;`
- L49 _private member_ `AActor* CachedDebugActor = nullptr;`
- L50 _private member_ `FMassEntityHandle CachedEntity;`
- L52 _private member_ `FDelegateHandle OnEntitySelectedHandle;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConsoleCommandBroadcastDelegate, UWorld*);`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/IInstancedActorsModule.h` (Public)


#### class `IInstancedActorsModule`  
`class IInstancedActorsModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IInstancedActorsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsCommands.h` (Public)


#### struct `UE::InstancedActors::FBulkLODTagsChangeCommandBase`  
`struct FBulkLODTagsChangeCommandBase : public FMassCommandChangeTags`  
_L18-28_
- inherits: `FMassCommandChangeTags`
- L21 _public typedef_ `using Super = FMassCommandChangeTags;`
- L22 _public prototype_ `void Add(TNotNull<UInstancedActorsData*> InstanceData, EInstancedActorsBulkLOD NewLOD);`
- L25 _protected prototype_ `virtual void Run(FMassEntityManager& EntityManager) override;`
- L26 _protected prototype_ `virtual void Reset() override;`
- L27 _protected member_ `mutable TArray<TPair<TWeakObjectPtr<UInstancedActorsData>, EInstancedActorsBulkLOD>> IADataToNotify;`

#### struct `UE::InstancedActors::FEnableDetailedLODCommand`  
`struct FEnableDetailedLODCommand : public FBulkLODTagsChangeCommandBase`  
_L31-35_
- inherits: `FBulkLODTagsChangeCommandBase`
- desc: Adds GetDetailedLODTags() to an entity, effectively enabling DetailedLOD processing on it
- L33 _public typedef_ `using Super = FBulkLODTagsChangeCommandBase;`
- L34 _public prototype_ `FEnableDetailedLODCommand();`

#### struct `UE::InstancedActors::FEnableBatchLODCommand`  
`struct FEnableBatchLODCommand : public FBulkLODTagsChangeCommandBase`  
_L38-42_
- inherits: `FBulkLODTagsChangeCommandBase`
- desc: Removes GetDetailedLODTags() from an entity, effectively enabling BatchLOD processing on it
- L40 _public typedef_ `using Super = FBulkLODTagsChangeCommandBase;`
- L41 _public prototype_ `FEnableBatchLODCommand();`

#### struct `FMassCommandAddFragmentInstancesAndResaveIAPersistence`  
`template<typename TManagerType, typename ... TOthers> struct FMassCommandAddFragmentInstancesAndResaveIAPersistence : public FMassCommandAddFragmentInstances<TOthers...>`  
_L50-92_
- inherits: `FMassCommandAddFragmentInstances<TOthers...>`
- desc: Note: TManagerType is always expected to be AInstancedActorsManager, but is declared as template's param to maintain uniform command adding interface via FMassCommandBuffer.PushCommand.
- L52 _public typedef_ `using Super = FMassCommandAddFragmentInstances<TOthers...>;`
- L54 _public function_ `void Add(FMassEntityHandle Entity, typename TRemoveReference<TManagerType>::Type& ManagerToResave, TOthers... InFragments)`
- L63 _protected function_ `virtual void Reset() override`
- L69 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L74 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L91 _protected member_ `TSet<TObjectPtr<AInstancedActorsManager>> ManagersToResave;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace InstancedActors` (scope `UE`)
- L16 _prototype_ `FMassTagBitSet& GetDetailedLODTags();` (scope `UE::InstancedActors`) — Returns the bitset indicating all the gate-tags of the processors we want to run on Detailed-LOD entities (i.e. not the Batched-LOD ones). These tags are switched by UInstancedActorsStationaryLODBatchProcessor Modifying the bitset is the way for project-specific code to influence what gets executed.

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsComponent.h` (Public)


#### class `UInstancedActorsComponent`  
`class UInstancedActorsComponent : public UActorComponent`  
_L28-190_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Instanced Actors", Meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Provides Mass Entity reference and interop functions for Actors spawned via Instanced Actors on both client & server.
- L34 _public prototype_ `UInstancedActorsComponent();`
- L41 _public prototype_ `virtual void OnServerPreSpawnInitForInstance(FInstancedActorsInstanceHandle InInstanceHandle);` — Called on servers before InitializeComponent & BeginPlay in UServerInstancedActorsSpawnerSubsystem::SpawnActor for Actors spawned by the Instanced Actor system. Note: This is *not* called for BP constructed components which aren't added until after PreSpawnInit.
- L48 _public prototype_ `virtual void InitializeComponentForInstance(FInstancedActorsInstanceHandle InInstanceHandle);` — Called on servers during InitializeComponent for Actors spawned by the Instanced Actor system. Note: This *is* called for both native *and* BP contructed components, as opposed to OnServerPreSpawnInitForInstance which is only called for natively added components.
- L62 _public function_ `virtual void ModifyMassEntityConfig(FMassEntityManager& InMassEntityManager, UInstancedActorsData* InstancedActorData, FMassEntityConfig& InOutMassEntityConfig) const` — Called on an 'exemplar' Actor's components for clients & servers during UInstancedActorsData::CreateEntityTemplate to provide UInstancedActorsComponent's an opportunity to extend Mass entity default traits. Note: The `exemplar' actor is an actor spawned into a separate inactive UWorld by UInstancedActorsSubsystem::GetOrCreateExemplarActor for data mining like this. @param InMassEntityManager	The MassEntityManager to use for shared fragment registration etc @param InstancedActorData	The instance data the mass entity config will be used to spawn entities for. This component will be a default constructed component in InstancedActorData.ActorClass. @param InOutMassEntityConfig The Mass Entity Config to modify, e.g: via InOutMassEntityConfig.AddTrait
- L76 _public function_ `virtual void ModifyMassEntityTemplate(FMassEntityManager& InMassEntityManager, UInstancedActorsData* InstancedActorData, FMassEntityTemplateData& InOutMassEntityTemplateData) const` — Called on ActorClass CDO components for clients & servers during UInstancedActorsData::CreateEntityTemplate to provide UInstancedActorsComponent's an opportunity to extend Mass entity default fragments. Called after ModifyMassEntityConfig, once the entity config has been resolved to a template using GetOrCreateEntityTemplate and copied to a transient FMassEntityTemplateData (InOutMassEntityTemplateData) for further modification. @param InMassEntityManager			The MassEntityManager to use for shared fragment registration etc @param InstancedActorData			The instance data the mass entity config will be used to spawn entities for. This component will be a default constructed component in InstancedActorData.ActorClass. @param InOutMassEntityTemplateData	The Mass Entity Template to modify, e.g: via InOutMassEntityTemplateData.AddFragment etc
- L82 _public function_ `virtual uint32 GetInstancePersistenceDataID() const` — Subclasses implementing SerializeInstancePersistenceData must implement this method and return a non-zero unique uint32 used to match serialized persistence records with this UInstancedActorsComponent's SerializeInstancePersistenceData implementation.
- L88 _public function_ `virtual bool ShouldSerializeInstancePersistenceData(const FArchive& Archive, UInstancedActorsData* InstanceData, int64 TimeDelta) const` — Called prior to SerializeInstancePersistenceData for both saving & loading persistence data, to check if we indeed have persistence data to write / want to read. @return true if SerializeInstancePersistenceData should be called. If false, no entry will be written.
- L102 _public function_ `virtual void SerializeInstancePersistenceData(FStructuredArchive::FRecord Record, UInstancedActorsData* InstanceData, int64 TimeDelta) const` — Called by AInstancedActorsManager::SerializeInstancePersistenceData for IAD's with an ActorClass containing this UInstancedActorsComponent, to save / load extended persistence data. Note: This is only called if ShouldSerializeInstancePersistenceData returns true, in which case GetInstancePersistenceDataID must also return a non-zero ID. @param Record			The archive record to read / write IAD save data to @param InstanceData		The InstanceData to serialize from / to @param TimeDelta	Real time in seconds since serialization (0 when saving) @see ShouldSerializeInstancePersistenceData, GetInstancePersistenceDataID
- L112 _public function_ `bool HasMassEntity() const` — `UFUNCTION(BlueprintPure, Category=InstancedActors)` — Returns true if this Actor was spawned by the Instanced Actor system for a Mass Entity. On servers, MassEntityHandle will be set in UInstancedActorsComponent::InitializeComponent (before component BeginPlay) On clients, MassEntityHandle will be set after component BeginPlay, as the link between Entity <-> Actor isn't made until both the actor has replicated to the client (recieving BeginPlay in the process) *and* the client Mass simulation attempts to spawn an actor itself, whereupon the replicated actor is then returned for the client spawn request.
- L119 _public prototype_ `FMassEntityHandle GetMassEntityHandle() const;` — Handle to this Instanced Actor's Mass Entity, if this components Actor owner was spawned by the Instanced Actor system, invalid handle otherwise. On servers, MassEntityHandle will be set in UInstancedActorsComponent::InitializeComponent (before component BeginPlay) On clients, MassEntityHandle will be set after component BeginPlay.
- L122 _public prototype_ `TSharedPtr<FMassEntityManager> GetMassEntityManager() const;` — If HasMassEntity(), the Mass Entity Manager for MassEntityHandle
- L124 _public prototype_ `FMassEntityManager& GetMassEntityManagerChecked() const;`
- L132 _public prototype_ `template<typename FragmentType> void AddFragmentDeferred();` — If HasMassEntity(), adds a new default constructed FragmentType to this Instanced Actor's Mass entity, if not already present (no-op otherwise) Performed deferred using FMassCommandBuffer to safely add fragments, as Mass may currently be performing parallel processing.
- L139 _public prototype_ `template<typename... FragmentTypes> void AddOrUpdateFragmentsDeferred(FragmentTypes&&... NewFragments);` — If HasMassEntity(), adds or updates existing FragmentTypes for this Instanced Actor's Mass entity. Performed deferred using FMassCommandBuffer to safely add fragments, as Mass may currently be performing parallel processing.
- L149 _public prototype_ `template<typename... FragmentTypes> void AddOrUpdatePersistentFragmentsDeferred(FragmentTypes&&... NewFragments);` — If HasMassEntity(), adds or updates existing FragmentTypes for this Instanced Actor's Mass entity, then requests a persistent data resave once the fragments are updated. Performed deferred using FMassCommandBuffer to safely add fragments, as Mass may currently be performing parallel processing. Note: The fragments are not automatically persisted (yet), it is assumed some other mechanism will read the new fragment values during the persistence resave, e.g: SerializeInstancePersistenceData
- L159 _public prototype_ `template<typename FragmentType> const FragmentType* GetVolatileFragment() const;` — If HasMassEntity(), returns existing FragmentType fragment for this Instanced Actor's Mass Entity, if any. Otherwise returns nullptr. Note: This is a synchronous call and whilst the returned fragment is guaranteed to be a valid pointer, the fragment may be getting written to by Mass processors on parallel threads, unless they have bRequiresGameThreadExecution = true. Thread-safety in this scenario is left to the caller to either implement thread locking or ensure *all* processors reading and writing to this fragment have bRequiresGameThreadExecution = true.
- L166 _public prototype_ `template<typename FragmentType> void RemoveFragmentDeferred();` — If HasMassEntity(), removes FragmentType from this Instanced Actor's Mass entity, if present (no-op otherwise) Performed deferred using FMassCommandBuffer to safely add fragments, as Mass may currently be performing parallel processing.
- L177 _protected member_ `FInstancedActorsInstanceHandle InstanceHandle;` — `UPROPERTY(ReplicatedUsing=OnRep_InstanceHandle, Transient, Meta=(AllowPrivateAccess="true"), BlueprintReadOnly, Category=InstancedActors)` — Handle to the instance that spawned this Instanced Actor, if this component's Actor owner was spawned by the Instanced Actor system, invalid handle otherwise. On servers, InstanceHandle will be set in UInstancedActorsComponent::InitializeComponent (before component BeginPlay) On clients, InstanceHandle will be set after component BeginPlay.
- L180 _protected prototype_ `void OnRep_InstanceHandle();` — `UFUNCTION()`
- L183 _protected prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L187 _protected prototype_ `virtual void InitializeComponent() override;`
- L188 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L194 _function_ `template<typename FragmentType> void UInstancedActorsComponent::AddFragmentDeferred()`
- L204 _function_ `template<typename... FragmentTypes> void UInstancedActorsComponent::AddOrUpdateFragmentsDeferred(FragmentTypes&&... NewFragments)`
- L214 _function_ `template<typename... FragmentTypes> void UInstancedActorsComponent::AddOrUpdatePersistentFragmentsDeferred(FragmentTypes&&... NewFragments)`
- L224 _function_ `template<typename FragmentType> const FragmentType* UInstancedActorsComponent::GetVolatileFragment() const`
- L236 _function_ `template<typename FragmentType> void UInstancedActorsComponent::RemoveFragmentDeferred()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API INSTANCEDACTORS_API`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsCustomVersion.h` (Public)


#### struct `FInstancedActorsCustomVersion`  
`struct FInstancedActorsCustomVersion`  
_L9-26_
- L22 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L25 _private function_ `FInstancedActorsCustomVersion()`

#### enum `FInstancedActorsCustomVersion::Type`  
`enum Type`  
_L11-19_
- L14 _public enumerator_ `InitialVersion = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INSTANCEDACTORS_API`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsData.h` (Public)


#### struct `UE::InstancedActors::FExemplarActorData`  
`struct FExemplarActorData`  
_L28-43_
- L30 _public prototype_ `~FExemplarActorData();`
- L32 _public member_ `TObjectPtr<AActor> Actor;`
- L34 _private function_ `FExemplarActorData(AActor* InActor, UInstancedActorsSubsystem* InInstancedActorSubsystem) : Actor(InActor) , InstancedActorsSubsystem(InInstancedActorSubsystem)`
- L40 _private member_ `UInstancedActorsSubsystem* InstancedActorsSubsystem;`

#### class `UInstancedActorsData`  
`class UInstancedActorsData : public UObject`  
_L55-588_
- reflection: `UCLASS(MinimalAPI, DefaultToInstanced)`
- inherits: `UObject`
- desc: Instance data for all instances of a given AActor class. Provides 'stable' referral to instances by index via offline population of InstanceTransforms which is then consistently loaded on both client and server. @see AInstancedActorsManager
- L63 _public prototype_ `void Initialize();` — Called early in AInstancedActorsManager::InitializeModifyAndSpawnEntities to intitalize Settings, default visualization & Mass entity template
- L66 _public prototype_ `void SpawnEntities();` — Called in AInstancedActorsManager::InitializeModifyAndSpawnEntities to spawn Mass entities for each instance
- L71 _public prototype_ `void DespawnEntities();` — Called early in AInstancedActorsManager::EndPlay to reconstruct cooked data state from runtime Mass entities as best we can, then despawn all Mass entities and reset any other runtime instance data. Note: does NOT nullify the shared fragment, that is done in Deinitialize(), which is only called on true teardown and not on subsystem switch, allowing the fragment to be reused by an immediate respawn.
- L74 _public prototype_ `void DespawnEntities(bool bIsSwitchingSubsystems);` — `UE_DEPRECATED(5.8, "Using DespawnEntities with a parameter is deprecated.")`
- L78 _public prototype_ `void Deinitialize();` — Called from the parent's AInstancedActorsManager::EndPlay. Nullifies the shared fragment and can release the entity template and exemplar Actor from memory.
- L81 _public prototype_ `AInstancedActorsManager* GetManager() const;` — `UFUNCTION(BlueprintPure, Category = InstancedActors)`
- L83 _public prototype_ `AInstancedActorsManager& GetManagerChecked() const;`
- L87 _public prototype_ `static UInstancedActorsData* GetInstanceDataForEntity(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);` — Returns the 'owning' UInstancedActorsData for EntityHandle by checking it's FInstancedActorsFragment (if any) returning nullptr for unknown entities.
- L89 _public prototype_ `FInstancedActorsInstanceIndex GetInstanceIndexForEntity(const FMassEntityHandle EntityHandle) const;`
- L91 _public prototype_ `FMassEntityHandle GetEntity(FInstancedActorsInstanceIndex InstanceIndex) const;`
- L93 _public prototype_ `void SetSharedInstancedActorDataStruct(FSharedStruct InSharedStruct);`
- L96 _public function_ `EInstancedActorsBulkLOD GetBulkLOD() const` — @return current Bulk LOD of this InstancedActorData instance
- L109 _public member_ `uint16 ID;` — `UPROPERTY(VisibleAnywhere, Category=InstancedActors)` — Identifying integer, unique within outer IAM, used for identifying matching persistence records Incrementally assigned in GetOrCreateActorInstanceData
- L113 _public member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=InstancedActors)` — The fully realized actor type for these instances
- L115 _public function_ `const FInstancedActorsTagSet& GetAdditionalTags() const`
- L121 _public function_ `template<typename T> const std::remove_const_t<T>* GetSettingsPtr() const`
- L127 _public function_ `template<typename T> const std::remove_const_t<T>& GetSettings() const`
- L132 _public function_ `void SetSharedSettings(const FConstSharedStruct& InSharedSettings)`
- L138 _public function_ `virtual void OnBulkLODChanged(EInstancedActorsBulkLOD NewBulkLOD)` — This event virtual is public because it is called by InstancedActorsStationaryLODBatchProcessor
- L144 _protected function_ `virtual void OnInitialize()`
- L148 _protected function_ `virtual void OnSpawnEntities()`
- L152 _protected function_ `virtual void OnDespawnEntities()`
- L156 _protected function_ `virtual void OnDeinitialize()`
- L163 _protected function_ `virtual void OnEditorPreviewISMCsCreated()` — Called from GetOrCreateActorInstanceData after EditorPreviewISMComponents are first created, allowing subclasses to customize them (e.g. apply material overrides).
- L170 _protected member_ `FInstancedActorsTagSet AdditionalTags;` — `UPROPERTY(VisibleAnywhere, Category=InstancedActors)` — Delimiting tag set to group sets of instances
- L174 _protected member_ `FConstSharedStruct SharedSettings;` — Compiled settings for these instances, compiled and cached in BeginPlay. Note: Can also be refreshed on demand in PIE, using IA.RefreshSettings CVar
- L197 _public member_ `TArray<FTransform> InstanceTransforms;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=InstancedActors)` — Per-instance transforms. This essentially forms the 'instance list' until Entities are spawned from this. Note: This list can contain invalid 'removed' entries with 0'd values which will be skipped by UInstancedActorsInitializerProcessor
- L205 _public member_ `uint16 NumValidInstances = 0;` — `UPROPERTY()` — InstanceTransforms.Num() - number of invalid transforms Note: This is only valid prior to Entity spawning when InstanceTransforms is also valid, after which, spawned entities may be later removed / culled at runtime, invalidating this number. @todo Bundle this and InstanceTransforms, Bounds etc into a `SourceData` to separate them from runtime entity data @see InstanceTransforms
- L209 _public member_ `FBox Bounds = FBox(ForceInit);` — `UPROPERTY()` — Cumulative mesh bounds for all of InstanceTransfroms
- L214 _public member_ `uint16 NumInstances = 0;` — `UPROPERTY(Transient)` — InstanceTransforms.Num() cached in PostLoad so we can restore InstanceTransforms to this size in ResetInstanceData
- L219 _public member_ `TArray<FMassEntityHandle> Entities;` — `UPROPERTY(Transient)` — Runtime spawned mass instances @see AInstancedActorsManager::SpawnInstances
- L223 _public member_ `FMassEntityTemplateID EntityTemplateID;` — The entity template to spawn Mass entities from @see CreateEntityTemplate
- L226 _public member_ `float MaxDrawDistance = FLT_MAX;` — Distance from where the object will be culled out - auto computed from bounding box radius or can be set per via the settings
- L229 _public member_ `float LowLODDrawDistance = FLT_MAX;` — Distance from where the lowest LOD will be rendered - auto computed from bounding box and screen size data stored in the StaticMesh or can be set via the settings
- L232 _public prototype_ `bool HasSpawnedEntities() const;` — Returns true if InstanceTransforms has been consumed to spawn Mass entities
- L234 _public prototype_ `bool CanHydrate() const;`
- L238 _public prototype_ `int32 GetNumInstances() const;` — Returns the total instance count, including both valid & invalid instances e.g: GetNumFreeInstances() + NumValidInstances Useful for iterating by FInstancedActorsInstanceIndex or allocating same-sized instance data arrays
- L241 _public prototype_ `int32 GetNumFreeInstances() const;` — Returns the current invalid instance count, if any (i.e: GetNumInstances() - NumValidInstances)
- L245 _public prototype_ `bool IsValidInstance(const FInstancedActorsInstanceHandle& InstanceHandle) const;` — Returns true if InstanceHandle refers to this instance data and we have current information for an instance at InstanceHandle.InstanceIndex
- L249 _public prototype_ `void SetupLoadedInstances();` — Performs setup after all Instances have been loaded. Canonically called from PostLoad(), but may need to be called manually if this UInstancedActorsData is created at cook/runtime
- L254 _public prototype_ `FInstancedActorsInstanceHandle AddInstance(const FTransform& Transform, const bool bWorldSpace = false);` — Add's an instance of this actor type at Transform @see AInstancedActorsManager::AddActorInstance
- L259 _public prototype_ `bool SetInstanceTransform(const FInstancedActorsInstanceHandle& InstanceHandle, const FTransform& Transform, const bool bWorldSpace);` — `UFUNCTION(BlueprintCallable, Category = InstancedActors)` — Set/update the transform for an instance.
- L270 _public prototype_ `bool RemoveInstance(const FInstancedActorsInstanceHandle& InstanceToRemove);` — Removes all instance data for InstanceHandle. This simply adds this instance to a FreeList which incurs extra cost to process at runtime before instance spawning. Note: By default UInstancedActorsSubsystem::RemoveActorInstance will destroy empty managers on last instance removal, implicitly clearing this for subsequent instance adds which would create a fresh manager. @see IA.CompactInstances console command
- L274 _public prototype_ `void ForEachEditorPreviewISMC(TFunctionRef<bool(UInstancedStaticMeshComponent& )> InFunction) const;` — Iterates all ISMCs created in GetOrCreateActorInstanceData. @param InFunction						The function to call for each ISMC.
- L283 _public prototype_ `void RuntimeRemoveInstances(TConstArrayView<FInstancedActorsInstanceIndex> RuntimeRemoveInstances);` — Removes RuntimeRemoveInstances as if they were never present i.e: these removals are not persisted as if made by a player. Prior to entity spawning this simply invalidates InstanceTransforms entries, post entity spawning this destroys spawned entities. Note: Any RuntimeRemoveInstances that have already been removed are safely skipped.
- L291 _public prototype_ `void RuntimeRemoveAllInstances();` — Removes all instances as if they were never present i.e: these removals are not persisted as if made by a player. Prior to entity spawning this simply invalidates InstanceTransforms entries, post entity spawning this destroys spawned entities. Note: Any RuntimeRemoveInstances that have already been removed are safely skipped.
- L298 _public prototype_ `void DestroyInstance(FInstancedActorsInstanceIndex InstanceToDestroy);` — Authority: Permanently destroy InstanceToDestroy by adding it to the persistent DestroyedInstances list and deleting it's Mass entity (deleting any Mass-spawned actors in turn). DestroyedInstances modifications are then replicated to clients. Non-authority: 'Predict' replicated destruction by removing the instance to prevent ISMC instance addition once actor destruction completes.
- L304 _public prototype_ `virtual void EjectInstanceActor(FInstancedActorsInstanceIndex InstanceToEject, AActor& ActorToEject);` — Authority: `Eject` an instance by unlinking it's Actor from Mass, setting the actor to persist itself and then destroying the manager instance. This effectively transfers the actor to the persistence system. Non-authority: Perform the same unlinking and entity removal locally to release the Actor from Mass.
- L309 _public prototype_ `void SetReplicatedActor(FInstancedActorsInstanceIndex Instance, AActor& ReplicatedActor);` — Called in UInstancedActorsComponent::OnRep_InstanceHandle on clients to set ReplicatedActor as the current actor for Instance's mass entity. As we set bForceActorRepresentationWhileAvailable in UInstancedActorsVisualizationTrait this then forces the entity to switch to Actor representation on clients.
- L315 _public prototype_ `void ClearReplicatedActor(FInstancedActorsInstanceIndex Instance, AActor& ExpectedActor);` — Called in UInstancedActorsComponent::EndPlay on clients to clear / unset the current actor for Instance's mass entity. As we set bForceActorRepresentationWhileAvailable in UInstancedActorsVisualizationTrait this then allows the natural WantedRepresentationType (ISMC) to restore
- L319 _public function_ `const FInstancedActorsVisualizationInfo& GetDefaultVisualizationChecked() const` — Returns the default visualization auto-created in BeginPlay from ActorClass and used by default for all spawned entities in BeginPlay.
- L325 _public function_ `const FInstancedActorsVisualizationInfo& GetVisualizationChecked(uint8 VisualizationIndex) const` — Get runtime visualization info by index for visualizations added with AddVisualization. Asserts if VisualizationIndex doesn't correspond to a valid index, or the visualization at that index is invalid (has been removed) @param VisualizationIndex The index of the visualization previously returned by AddVisualization
- L338 _public function_ `const FInstancedActorsVisualizationInfo* GetVisualization(uint8 VisualizationIndex) const` — Get runtime visualization info by index for visualizations added with AddVisualization. If VisualizationIndex doesn't correspond to a valid index, or the visualization at that index is invalid (has been removed) nullptr is returned. @param VisualizationIndex The index of the visualization previously returned by AddVisualization
- L356 _public prototype_ `uint8 AddVisualization(FInstancedActorsVisualizationDesc& InOutVisualizationDesc);` — Register additional / alternate VisualizationDesc for instances to switch to, creating ISMC's for each VisualizationDesc.InstancedMeshes @warning No more than 254 visualizations may be registered at any time to allow for uint8 indexing. @return Index handle to refer to the registered visualization
- L362 _public prototype_ `uint8 AddVisualizationAsync(const FInstancedActorsSoftVisualizationDesc& SoftVisualizationDesc);` — Register additional / alternate VisualizationDesc for instances to switch to, creating ISMC's for each VisualizationDesc.InstancedMeshes @warning No more than 254 visualizations may be registered at any time to allow for uint8 indexing. @return Index handle to refer to the registered visualization
- L370 _public prototype_ `void ForEachVisualization(TFunctionRef<bool(uint8 , const FInstancedActorsVisualizationInfo& )> InFunction , bool bSkipAsyncLoadingVisualizations = true) const;` — Iterates all currently 'allocated' visualizations previously added with AddVisualization or AddVisualizationAsync @param InFunction						The function to call for each allocated visualization. @param bSkipAsyncLoadingVisualizations	If true, skips visualizations that are still async loading (FInstancedActorsVisualizationInfo::IsAsyncLoading() = true) which won't have been initialized yet i.e: won't yet have a valid Desc, ISMComponents or MassStaticMeshDescIndex yet.
- L381 _public prototype_ `void SwitchInstanceVisualization(FInstancedActorsInstanceIndex InstanceToSwitch, uint8 NewVisualizationIndex);` — Switches InstanceToSwitch to use the 'visualization' at NewVisualizationIndex, previoulsy added via AddVisualzation. ISMC instances will be removed from the current /former visualization for these instances and new instances will be added to the ISMC's of the new visualization. Note: This is performed via a mass deferred command to add a 'pending' FInstancedActorsMeshSwitchFragment to the instances entity. UInstancedActorsVisualizationSwitcherProcessor will then process this switch fragment to remove the current visualization's ISMC instances if any and setup NewVisualizationIndex to be instanced instead.
- L384 _public prototype_ `void RemoveVisualization(uint8 VisualizationIndex);` — Remove previously registered instance visualization, deleting all ISMC's
- L387 _public prototype_ `void RemoveAllVisualizations();` — Remove all previously registered instance visualization, deleting all ISMC's
- L390 _public prototype_ `void OnInstancedActorDestroyed(AActor& DestroyedActor, const FMassEntityHandle EntityHandle);` — Called by UInstancedActorsRepresentationActorManagement when a managed actor is destroyed
- L394 _public prototype_ `bool OnInstancedActorMoved(AActor& MovedActor, const FMassEntityHandle EntityHandle);` — Called by UInstancedActorsRepresentationActorManagement when a managed actor is moved @return true if MovedActor was ejected
- L397 _public prototype_ `void OnPersistentDataRestored();` — Called when persistent data has been applied / restored
- L399 _public function_ `inline FInstancedActorsDeltaList& GetMutableInstanceDeltaList()`
- L401 _public function_ `inline const FInstancedActorsDeltaList& GetInstanceDeltaList() const`
- L404 _public prototype_ `void OnRep_InstanceDeltas(TConstArrayView<int32> UpdatedInstanceDeltaIndices);` — Called by FInstancedActorsDeltaList::PostReplicatedAdd and PostReplicatedChanged on InstanceDelta replication
- L407 _public prototype_ `void OnRep_PreRemoveInstanceDeltas(TConstArrayView<int32> RemovedInstanceDeltaIndices);` — Called by FInstancedActorsDeltaList::PreReplicatedRemove on InstanceDelta removal replication (just before the actual array element removal)
- L413 _public prototype_ `void ApplyInstanceDeltas();` — Called on both server and client to apply instance delta changes to mass entities On servers: Called by OnPersistentDataRestored after persistence record has deserialized the delta data On clients: Called by OnRep_InstanceDeltas when new delta data has replicated from the server @param InstanceDeltaIndices Indices into InsanceDeltas.GetInstanceDeltas() of the upated deltas to apply
- L414 _public prototype_ `void ApplyInstanceDeltas(TConstArrayView<int32> InstanceDeltaIndices);`
- L418 _public prototype_ `void RollbackInstanceDeltas(TConstArrayView<int32> InstanceDeltaIndices);` — Called on clients by OnRep_PreRemoveInstanceDeltas to revert instance delta change to mass entities @param InstanceDeltaIndices Indices into InsanceDeltas.GetInstanceDeltas() of the deltas to revert
- L422 _public prototype_ `FString GetDebugName(bool bCompact = false) const;` — Returns a string useful for identifying this instance data object withing it's owning manager @param bCompact if true, this IAD's pointer is used, otherwise the full manager object path is included
- L424 _public prototype_ `virtual void UpdateCullDistance();`
- L429 _public prototype_ `void SetInstanceCurrentLifecyclePhase(FInstancedActorsInstanceIndex InstanceIndex, uint8 InCurrentLifecyclePhaseIndex);` — mz@todo IA: move this section back Server-only. Used by LifecycleComponent & LifecycleProcessor to replicate & persist lifecycle changes @todo Provide generic fragment persistence & replication
- L435 _public prototype_ `void RemoveInstanceLifecyclePhaseDelta(FInstancedActorsInstanceIndex InstanceIndex);` — mz@todo IA: move this section back Server-only. Used by LifecycleComponent & LifecycleProcessor to remove replicated & persisted lifecycle changes (triggering a rollback to default values on clients) @todo Provide generic fragment persistence & replication
- L441 _public prototype_ `void RemoveInstanceLifecyclePhaseTimeElapsedDelta(FInstancedActorsInstanceIndex InstanceIndex);` — mz@todo IA: move this section back Server-only. Used by LifecycleComponent & LifecycleProcessor to remove the lifecycle time elapsed delta record for InstanceIndex from InstanceDeltas (if any) @todo Provide generic fragment persistence & replication
- L443 _public function_ `int32 GetInstanceDataID() const`
- L445 _public function_ `const FBox& GetCachedLocalBounds() const`
- L447 _public function_ `FMassEntityHandle GetEntityHandleForIndex(const FInstancedActorsInstanceIndex Index) const`
- L452 _public prototype_ `FMassEntityManager& GetMassEntityManagerChecked() const;`
- L454 _public prototype_ `int32 GetEntityIndexFromCollisionIndex(const UInstancedStaticMeshComponent& ISMComponent, const int32 CollisionIndex) const;`
- L456 _public function_ `const FGameplayTagContainer& GetCombinedTags() const`
- L463 _public prototype_ `void PopAllEntitiesPendingDestruction(TArray<FMassEntityHandle>& InOutEntities);` — Moves the current list of entities pending destruction (added via QueueEntitiesForDestruction) to InOutEntities This 'consumes' these pending entities with the assumption they will get destroyed by next command flush. @see UInstancedActorsRuntimeRemovalProcessor, RuntimeRemoveInstances
- L466 _protected function_ `FMassEntityHandle GetEntityHandleForIndex(const int32 Index) const`
- L472 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L473 _protected prototype_ `virtual void PostLoad() override;`
- L474 _protected prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L475 _protected prototype_ `virtual void RegisterReplicationFragments(UE::Net::FFragmentRegistrationContext& Context, UE::Net::EFragmentRegistrationFlags RegistrationFlags) override;`
- L476 _protected function_ `virtual bool IsNameStableForNetworking() const override`
- L480 _protected prototype_ `void CreateEntityTemplate(const AActor& ExemplarActor);` — Called on BeginPlay to create default entity template
- L481 _protected prototype_ `virtual void ModifyEntityTemplate(FMassEntityTemplateData& ModifiedTemplate, const AActor& ExemplarActor);`
- L484 _protected prototype_ `void ReleaseEntityTemplate();` — Called from Deinitialize to destroy the owned FMassEntityTemplate
- L488 _protected prototype_ `virtual void ApplyInstanceDelta(FMassEntityManager& EntityManager, const FInstancedActorsDelta& InstanceDelta, TArray<FInstancedActorsInstanceIndex>& OutEntitiesToRemove);` — Helper function used in ApplyInstanceDeltas to apply a single delta @see ApplyInstanceDeltas
- L492 _protected prototype_ `virtual void RollbackInstanceDelta(FMassEntityManager& EntityManager, const FInstancedActorsDelta& InstanceDelta);` — Helper function used in RollbackInstanceDeltas to rollback a single delta @see RollbackInstanceDeltas
- L502 _protected prototype_ `AActor* UnlinkActor(FInstancedActorsInstanceIndex InstanceToUnlink);` — Unlink InstanceToUnlink's Actor (if any) from Mass by clearing the entities reference to it and disconnecting from any subscribed actor signals, essentially 'forgetting' about the actor. Called by EjectInstanceActor to transfer the actor's management to persistence system and OnInstancedActorDestroyed to allow the Actor to complete death process in the background after we've destroyed the Mass entity (which would have otherwise force-destroyed the associated actor) @return The unlinked actor (if one was currently linked, nullptr otherwise)
- L505 _protected member_ `bool bHasSetupLoadedInstances : 1 = false;` — True if SetupLoadedInstances has ever been called
- L508 _protected member_ `bool bHasEverInitialized : 1 = false;` — True if Initialize has ever been called
- L511 _protected member_ `bool bRemovingInstances : 1 = false;` — True during RuntimeRemoveInstances to prevent recursion via OnInstancedActorDestroyed
- L521 _protected member_ `TArray<FInstancedActorsVisualizationInfo> InstanceVisualizations;` — `UPROPERTY(Transient, VisibleAnywhere, Category=InstancedActors)` — Sets of ISMCs which instances can swap between to change 'visualization' e.g: 'with berries', 'without berries' InstanceVisualizations[0] is the default visualization, auto-created in BeginPlay from ActorClass and used by default for all spawned entities in BeginPlay. Additional visualizations can be registered at runtime with AddVisualization, for instances to switch to (@todo) @see AddVisualization, AddVisualizationAsync
- L527 _protected member_ `TBitArray<> InstanceVisualizationAllocationFlags;` — Allocation bit flags for InstanceVisualizations to allow for TSpareArray-like removal of visualization without affecting remaining visualization indices. Size-matched to InstanceVisualizations with a bit per visualization defining whether or not that visualization entry is actually allocated. Note: TSparseArray can't be used directly here as it's not a UPROPERTY type.
- L532 _protected prototype_ `uint8 AllocateVisualization();` — Adds or reuses a previously removed entry in InstanceVisualizations @return The 'visualization index` of the new or reused entry in InstanceVisualizations @see AddVisualization, AddVisualizationAsync
- L537 _protected prototype_ `void InitializeVisualization(uint8 AllocatedVisualizationIndex, const FInstancedActorsVisualizationDesc& VisualizationDesc);` — Creates ISMCs for VisualizationDesc.InstancedMeshes, registers them with Mass and sets FInstancedActorsVisualizationInfo::MassStaticMeshDescIndex with the newly registed ISMC decription index @see AddVisualization, AddVisualizationAsync
- L542 _protected member_ `TArray<TObjectPtr<UInstancedStaticMeshComponent>> EditorPreviewISMComponents;` — `UPROPERTY()` — ISMCs created in GetOrCreateActorInstanceData to match default visualizations ISMComponents for editor only preview of instances
- L546 _protected member_ `FBox CachedLocalBounds = FBox(ForceInit);` — `UPROPERTY()`
- L549 _private prototype_ `void QueueEntitiesForDestruction(TArray<FMassEntityHandle>&& EntitiesToDestroy);`
- L551 _private member_ `mutable FCriticalSection PendingDestructionCS;`
- L555 _private member_ `TArray<FMassEntityHandle> EntitiesPendingDestruction;` — These will get destroyed next time commands are flushed. @see QueueEntitiesForDestruction, PopAllEntitiesPendingDestruction
- L558 _private member_ `TStructView<FInstancedActorsDataSharedFragment> SharedInstancedActorDataStruct;` — Represents the shared fragment registered with MassEntityManager, that points back to this UInstancedActorsData instance
- L564 _private member_ `FInstancedActorsDeltaList InstanceDeltas;` — `UPROPERTY(Replicated, SaveGame, Transient)` — List of FInstancedActorsDelta's to apply to instances, replicated via fast array replication to clients. Formed at runtime via player actions and persisted / restored by game's persistence system @see Serialize
- L567 _private member_ `FMassEntityConfig EntityConfig;` — `UPROPERTY(Transient)`
- L571 _private member_ `FGameplayTagContainer CombinedTags;` — `UPROPERTY(Transient)` — Result of combining AdditionalTags with class-based FInstancedActorsSettings::GameplayTags
- L573 _private member_ `bool bCanHydrate = true;`
- L575 _private member_ `TSharedPtr<UE::InstancedActors::FExemplarActorData> ExemplarActorData;`
- L587 _private member_ `TArray<FSetReplicatedActorRequests> CachedSetReplicatedActorRequests;`
- L593 _function_ `inline bool UInstancedActorsData::CanHydrate() const`

#### struct `UInstancedActorsData::FSetReplicatedActorRequests`  
`struct FSetReplicatedActorRequests`  
_L577-586_
- L579 _public function_ `FSetReplicatedActorRequests(FInstancedActorsInstanceIndex InInstanceIndex, TWeakObjectPtr<AActor> InActor) : InstanceIndex(InInstanceIndex), Actor(InActor)`
- L584 _public member_ `FInstancedActorsInstanceIndex InstanceIndex;`
- L585 _public member_ `TWeakObjectPtr<AActor> Actor;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace InstancedActors` (scope `UE`)
- L20 _namespace_ `namespace CVars` (scope `UE::InstancedActors`)
- L22 _externvar_ `extern bool bFlagSharedFragmentInsteadOfNullify;` (scope `UE::InstancedActors::CVars`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace InstancedActors` (scope `UE`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsDebug.h` (Public)


#### Free symbols / members of external scopes

- L13 _macro_ `#define WITH_INSTANCEDACTORS_DEBUG (!(UE_BUILD_SHIPPING || UE_BUILD_SHIPPING_WITH_EDITOR || UE_BUILD_TEST) && WITH_MASSGAMEPLAY_DEBUG && 1)`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace InstancedActors` (scope `UE`)
- L20 _namespace_ `namespace Debug` (scope `UE::InstancedActors`)
- L22 _namespace_ `namespace CVars` (scope `UE::InstancedActors::Debug`)
- L24 _externvar_ `extern int32 DebugModifiers;` (scope `UE::InstancedActors::Debug::CVars`)
- L25 _externvar_ `extern int32 DebugManagerLoading;` (scope `UE::InstancedActors::Debug::CVars`)
- L26 _externvar_ `extern int32 DebugInstanceLoading;` (scope `UE::InstancedActors::Debug::CVars`)
- L30 _namespace_ `namespace DrawMode` (scope `UE::InstancedActors::Debug`)
- L32 _variable_ `constexpr int32 None = 0;` (scope `UE::InstancedActors::Debug::DrawMode`)
- L33 _variable_ `constexpr int32 DebugDraw = 1;` (scope `UE::InstancedActors::Debug::DrawMode`)
- L34 _variable_ `constexpr int32 VisLog = 2;` (scope `UE::InstancedActors::Debug::DrawMode`)
- L35 _variable_ `constexpr int32 Both = 3;` (scope `UE::InstancedActors::Debug::DrawMode`)
- L38 _function_ `inline bool ShouldDebugDraw(const int32& DebugDrawMode)` (scope `UE::InstancedActors::Debug`)
- L39 _function_ `inline bool ShouldVisLog(const int32& DebugDrawMode)` (scope `UE::InstancedActors::Debug`)
- L41 _prototype_ `void DebugDrawManager(const int32& DebugDrawMode, const AInstancedActorsManager& Manager);` (scope `UE::InstancedActors::Debug`)
- L42 _prototype_ `void LogInstanceCountsOnScreen(const int32& DebugDrawMode, const AInstancedActorsManager& Manager, float TimeToDisplay = 4.0f, FColor Color = FColor::Magenta);` (scope `UE::InstancedActors::Debug`)
- L43 _prototype_ `void DebugDrawAllInstanceLocations(const int32& DebugDrawMode, ELogVerbosity::Type Verbosity, const AInstancedActorsManager& Manager, const TOptional<FColor> Color, const UObject* LogOwner, const FName& CategoryName = TEXT("LogI` (scope `UE::InstancedActors::Debug`)
- L44 _prototype_ `void DebugDrawModifierVolumeBounds(const int32& DebugDrawMode, const UInstancedActorsModifierVolumeComponent& ModifierVolume, const FColor& Color);` (scope `UE::InstancedActors::Debug`)
- L45 _prototype_ `void DebugDrawModifierVolumeAddedToManager(const int32& DebugDrawMode, const AInstancedActorsManager& Manager, const UInstancedActorsModifierVolumeComponent& AddedModifierVolume);` (scope `UE::InstancedActors::Debug`)
- L48 _function_ `template <typename CategoryType, typename FmtType, typename... Types> void DebugDrawLocation(const int32& DebugDrawMode, const UWorld* World, const UObject* LogOwner, const CategoryType& CategoryName, ELogVerbosity::Type Verbosity, const FVector& Location, float Size, const FColor& Color, const FmtType& Fmt, Types... Args)` (scope `UE::InstancedActors::Debug`)
- L66 _function_ `template <typename CategoryType, typename FmtType, typename... Types> void DebugDrawSphere(const int32& DebugDrawMode, const UWorld* World, const UObject* LogOwner, const CategoryType& CategoryName, ELogVerbosity::Type Verbosity, const FSphere& Sphere, const FColor& Color, const FmtType& Fmt, Types... Args)` (scope `UE::InstancedActors::Debug`)
- L84 _function_ `template <typename CategoryType, typename FmtType, typename... Types> void DrawDebugSolidBox(const int32& DebugDrawMode, const UWorld* World, const UObject* LogOwner, const CategoryType& CategoryName, ELogVerbosity::Type Verbosity, const FBox& Box, const FColor& Color, const FmtType& Fmt, Types... Args)` (scope `UE::InstancedActors::Debug`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsDebugProcessor.h` (Public)


#### class `UInstancedActorsDebugProcessor`  
`class UInstancedActorsDebugProcessor : public UMassProcessor`  
_L14-35_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L19 _protected prototype_ `UInstancedActorsDebugProcessor();`
- L21 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L23 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L30 _protected member_ `FMassEntityQuery DetailedLODEntityQuery;` — The query used when drawing instanced actors at Detailed batch LOD (see UE::InstancedActors::Debug::bDebugDrawDetailedCurrentRepresentation)
- L33 _protected member_ `FMassEntityQuery DebugAllEntityQuery;` — The query used when "debug all entities" is enabled (see UE::InstancedActors::Debug::bDebugDrawAllEntities)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsIndex.h` (Public)


#### struct `FInstancedActorsInstanceIndex`  
`struct FInstancedActorsInstanceIndex`  
_L18-84_
- reflection: `USTRUCT()`
- desc: This type is only valid to be used with the instance of UInstancedActorsData it applies to.
- L22 _public member_ `static constexpr uint16 INSTANCED_INDEX_NONE = MAX_uint16;`
- L23 _public member_ `static constexpr uint16 INSTANCED_INDEX_MAX = MAX_uint16 - 1;`
- L25 _public prototype_ `FInstancedActorsInstanceIndex() = default;`
- L26 _public function_ `explicit FInstancedActorsInstanceIndex(const int32 InIndex)`
- L48 _public function_ `bool IsValid() const`
- L51 _public prototype_ `FString GetDebugName() const;` — Returns a string suitable for debug logging to identify this instance.
- L53 _public prototype_ `bool operator==(const FInstancedActorsInstanceIndex&) const = default;`
- L55 _public function_ `int32 GetIndex() const`
- L57 _public function_ `static constexpr inline int32 BuildCompositeIndex(const uint16 InstanceDataID, const int32 InstanceIndex)`
- L67 _public function_ `static constexpr inline int32 ExtractInstanceDataID(const int32 CompositeIndex)`
- L72 _public function_ `static constexpr inline int32 ExtractInternalInstanceIndex(const int32 CompositeIndex)`
- L80 _private member_ `uint16 Index = INSTANCED_INDEX_NONE;` — `UPROPERTY()` — Stable(consistent between client and server) instance index into UInstancedActorsData
- L82 _private member_ `static constexpr int32 InstanceIndexBits = 16;`
- L83 _private member_ `static constexpr int32 InstanceIndexMask = (1 << InstanceIndexBits) - 1;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FInstancedActorsInstanceIndex> : public TStructOpsTypeTraitsBase2<FInstancedActorsInstanceIndex>`  
_L87-94_
- inherits: `TStructOpsTypeTraitsBase2<FInstancedActorsInstanceIndex>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L90-93_

#### struct `FInstancedActorsInstanceHandle`  
`struct FInstancedActorsInstanceHandle`  
_L97-139_
- reflection: `USTRUCT(BlueprintType)`
- L101 _public prototype_ `FInstancedActorsInstanceHandle() = default;`
- L102 _public prototype_ `FInstancedActorsInstanceHandle(UInstancedActorsData& InInstancedActorData, FInstancedActorsInstanceIndex InIndex);`
- L104 _public function_ `UInstancedActorsData* GetInstanceActorData() const`
- L105 _public prototype_ `UInstancedActorsData& GetInstanceActorDataChecked() const;`
- L107 _public prototype_ `AInstancedActorsManager* GetManager() const;`
- L108 _public prototype_ `AInstancedActorsManager& GetManagerChecked() const;`
- L110 _public prototype_ `bool IsValid() const;`
- L113 _public prototype_ `FString GetDebugName() const;` — Returns a string suitable for debug logging to identify this instance.
- L115 _public prototype_ `bool operator==(const FInstancedActorsInstanceHandle&) const = default;`
- L116 _public function_ `FInstancedActorsInstanceIndex GetInstanceIndex() const`
- L117 _public function_ `int32 GetIndex() const`
- L119 _public function_ `void Reset()`
- L134 _private member_ `TWeakObjectPtr<UInstancedActorsData> InstancedActorData = nullptr;` — `UPROPERTY()` — Specific UInstancedActorsData responsible for this instance.Can be used to get to it's owning Manager.
- L138 _private member_ `FInstancedActorsInstanceIndex Index;` — `UPROPERTY()` — Stable(consistent between client and server) instance index into UInstancedActorsData.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L32 _function_ `friend FArchive& operator<<(FArchive& Ar, FInstancedActorsInstanceIndex& InstanceIndex)`
- L38 _function_ `friend void operator<<(FStructuredArchive::FSlot Slot, FInstancedActorsInstanceIndex& InstanceIndex)`
- L43 _function_ `friend uint32 GetTypeHash(const FInstancedActorsInstanceIndex& InstanceIndex)`
- L91 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon4aee2a230103`)
- L92 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon4aee2a230103`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsInitializerProcessor.h` (Public)


#### struct `FInstancedActorsMassSpawnData`  
`struct FInstancedActorsMassSpawnData`  
_L13-18_
- reflection: `USTRUCT()`
- L17 _public member_ `TWeakObjectPtr<UInstancedActorsData> InstanceData;`

#### class `UInstancedActorsInitializerProcessor`  
`class UInstancedActorsInitializerProcessor : public UMassProcessor`  
_L22-34_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Initializes the fragments of all entities that fit the query specified in ConfigureQueries, which are all considered Instanced Actors.
- L27 _public prototype_ `UInstancedActorsInitializerProcessor();`
- L30 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L31 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L33 _protected member_ `FMassEntityQuery EntityQuery;`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsIteration.h` (Public)


#### struct `FInstancedActorsIterationContext`  
`struct FInstancedActorsIterationContext`  
_L25-70_
- reflection: `USTRUCT()`
- desc: Provides useful functionality while iterating instances like safe instance deletion. @see AInstancedActorsManager::ForEachInstance
- L30 _public prototype_ `~FInstancedActorsIterationContext();` — Destructor to ensure no pending actions remain
- L40 _public prototype_ `void RemoveInstanceDeferred(const FInstancedActorsInstanceHandle& InstanceHandle);` — Safely marks InstanceHandle for destruction at the end of iteration, to ensure iteration order isn't affected. Note: These deletions will NOT be be persisted as if a player had performed them, rather the deletions will make it as if the items were never present. Note: This is safe to call before entity spawning as source instance data will simply be invalidated, preventing later entity spawning.
- L50 _public prototype_ `void RemoveAllInstancesDeferred(UInstancedActorsData& InstanceData);` — Safely marks all instances in InstanceData for destruction at the end of iteration, to ensure iteration order isn't affected. Note: These deletions will NOT be be persisted as if a player had performed them, rather the deletions will make it as if the items were never present. Note: This is safe to call before entity spawning as source instance data will simply be invalidated, preventing later entity spawning.
- L60 _public prototype_ `void RemoveAllInstancesDeferred(AInstancedActorsManager& Manager);` — Safely marks all instances in Manager for destruction at the end of iteration, to ensure iteration order isn't affected. Note: These deletions will NOT be be persisted as if a player had performed them, rather the deletions will make it as if the items were never present. Note: This is safe to call before entity spawning as source instance data will simply be invalidated, preventing later entity spawning.
- L63 _public prototype_ `void FlushDeferredActions();` — Perform deferred instance removals
- L67 _private member_ `TMap<TObjectPtr<UInstancedActorsData>, TArray<FInstancedActorsInstanceIndex>> InstancesToRemove;`
- L68 _private member_ `TArray<TObjectPtr<UInstancedActorsData>> RemoveAllInstancesIADs;`
- L69 _private member_ `TArray<TObjectPtr<AInstancedActorsManager>> RemoveAllInstancesIAMs;`

#### struct `FScopedInstancedActorsIterationContext`  
`struct FScopedInstancedActorsIterationContext : public FInstancedActorsIterationContext`  
_L73-79_
- inherits: `FInstancedActorsIterationContext`
- desc: Subclass of FInstancedActorsIterationContext that calls FlushDeferredActions in it's destructor
- L75 _public function_ `~FScopedInstancedActorsIterationContext()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INSTANCEDACTORS_API`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsManager.h` (Public)


#### enum `UE::InstancedActors::EInsideBoundsTestResult`  
`enum class EInsideBoundsTestResult`  
_L30-35_
- L32 _public enumerator_ `NotInside`
- L33 _public enumerator_ `OverlapLocation`
- L34 _public enumerator_ `OverlapBounds`

#### enum `UE::InstancedActors::EBoundsTestType`  
`enum class EBoundsTestType`  
_L37-43_
- L39 _public enumerator_ `Intersect`
- L40 _public enumerator_ `Enclosed`
- L42 _public enumerator_ `Default = Intersect`

#### class `AInstancedActorsManager`  
`class AInstancedActorsManager : public APartitionActor, public ISMInstanceManager, public IActorInstanceManagerInterface`  
_L70-425_
- reflection: `UCLASS(MinimalAPI, Config = Mass)`
- inherits: `APartitionActor,ISMInstanceManager,IActorInstanceManagerInterface`
- desc: Regional manager of 'instanced actors'. Uses Mass to provide lightweight and efficient instancing of items in the distance, with server-authoritative actor spawning around players. AInstancedActorsManager's also provide replication and persistence for their managed instances. Spawned and populated *offline* by UInstancedActorsSubsystem::InstanceActor. Offline population ensures client & server both load the same stable instance data and can commonly refer to instances by index as such.
- L75 _public prototype_ `AInstancedActorsManager();`
- L83 _public prototype_ `void OnAddedToSubsystem(UInstancedActorsSubsystem& InInstancedActorSubsystem, FInstancedActorsManagerHandle InManagerHandle);` — Adds modifiers already registered with InInstancedActorSubsystem and either calls InitializeModifyAndSpawnEntities to spawn entities immediately, or schedules deferred call by InInstancedActorSubsystem if IA.DeferSpawnEntities is enabled. Called either in BeginPlay if InInstancedActorSubsystem was already initialized or latently once it is, in UInstancedActorsSubsystem::Initialize
- L85 _public prototype_ `FInstancedActorsManagerHandle GetManagerHandle() const;`
- L91 _public prototype_ `void SetupLoadedInstances();` — Performs setup after all Instances have been loaded. Canonically called from PostLoad(), but may need to be called manually if this AInstancedActorsManager is created at cook/runtime
- L99 _public prototype_ `void InitializeModifyAndSpawnEntities();` — Initializes all PerActorClassInstanceData, applies pre-spawn modifiers, spawns entities then applies post-spawn modifiers. Called either directly in OnAddedToSubsystem or deferred and time-sliced in UInstancedActorsSubsystem::Tick if IA.DeferSpawnEntities is enabled.
- L102 _public prototype_ `bool HasSpawnedEntities() const;` — @return true if InstanceTransforms have been consumed to spawn Mass entities in InitializeModifyAndSpawnEntities
- L106 _public prototype_ `FInstancedActorsInstanceHandle AddActorInstance(TSubclassOf<AActor> ActorClass, FTransform InstanceTransform, bool bWorldSpace = true, const FInstancedActorsTagSet& AdditionalInstanceTags = FInstancedActorsTagSet());` — Adds an instance of ActorClass at InstanceTransform location to instance data
- L119 _public prototype_ `bool RemoveActorInstance(const FInstancedActorsInstanceHandle& InstanceToRemove);` — Removes all instance data for InstanceHandle. This simply adds this instance to a FreeList which incurs extra cost to process at runtime before instance spawning. Note: By default UInstancedActorsSubsystem::RemoveActorInstance will destroy empty managers on last instance removal, implicitly clearing this for subsequent instance adds which would create a fresh manager. @see IA.CompactInstances console command
- L123 _public prototype_ `UInstancedActorsData* FindInstanceDataByID(uint16 InstanceDataID) const;` — Searches PerActorClassInstanceData, returning the IAD with matching UInstancedActorsData::ID, if any(nullptr otherwise)
- L126 _public prototype_ `TConstArrayView<TObjectPtr<UInstancedActorsData>> GetAllInstanceData() const;` — @return the full set of instance data for this manager
- L136 _public prototype_ `void RuntimeRemoveAllInstances();` — Removes all instances as if they were never present i.e: these removals are not persisted as if made by a player. Prior to entity spawning this simply invalidates InstanceTransforms entries, post entity spawning this destroys spawned entities. Note: Any RuntimeRemoveInstances that have already been removed are safely skipped.
- L139 _public prototype_ `int32 GetNumValidInstances() const;` — @return the current valid instance count (i.e: NumInstances - FreeList.Num()) sum for all instance datas
- L141 _public prototype_ `bool HasAnyValidInstances() const;`
- L147 _public prototype_ `bool IsValidInstance(const FInstancedActorsInstanceHandle& InstanceHandle) const;` — @return true if InstanceHandle refers to this manager and we have current information for an instance at InstanceHandle.InstanceIndex in InstanceHandle.InstancedActorData
- L150 _public prototype_ `FBox GetInstanceBounds() const;` — @return world space cumulative instance bounds. Only valid after BeginPlay.
- L159 _public typedef_ `using FInstanceOperationFunc = TFunctionRef<bool(const FInstancedActorsInstanceHandle& InstanceHandle, const FTransform& InstanceTransform, FInstancedActorsIterationContext& IterationContext)>;` — Iteration callback for ForEachInstance @param InstanceHandle	Handle to the current instance in the iteration @param InstanceTransform If entities have been spawned, this will be taken from the Mass transform fragment, else from UInstancedActorsData::InstanceTransforms @param InterationContext Provides useful functionality while iterating instances like safe instance deletion @return Return true to continue iteration to subsequent instances, false to break iteration.
- L164 _public typedef_ `using FInstancedActorDataPredicateFunc = TFunctionRef<bool(const UInstancedActorsData& InstancedActorData)>;` — Predicate taking a UInstancedActorsData and returns true if IAD matches search criteria, false otherwise.
- L172 _public prototype_ `bool ForEachInstance(FInstanceOperationFunc Operation) const;` — Call InOperation for each valid instance in this manager. Prior to entity spawning in BeginPlay, this iterates valid UInstancedActorsData::InstanceTransforms. Once entities have been spawned, UInstancedActorsData::Entities are iterated. @param Operation Function to call for each instance found within QueryBounds @return false if InOperation ever returned false to break iteration, true otherwise.
- L173 _public prototype_ `bool ForEachInstance(FInstanceOperationFunc Operation, FInstancedActorsIterationContext& IterationContext, TOptional<FInstancedActorDataPredicateFunc> InstancedActorDataPredicate = TOptional<FInstancedActorDataPredicateFunc>()) const;`
- L183 _public prototype_ `template <typename TBoundsType> bool ForEachInstance(const TBoundsType& QueryBounds, FInstanceOperationFunc InOperation) const;` — Call InOperation for each valid instance in this manager whose location falls within QueryBounds. Prior to entity spawning in BeginPlay, this iterates valid UInstancedActorsData::InstanceTransforms. Once entities have been spawned, UInstancedActorsData::Entities are iterated. @param QueryBounds A world space FBox or FSphere to test instance locations against using QueryBounds.IsInside(InstanceLocation) @param InOperation Function to call for each instance found within QueryBounds @return false if InOperation ever returned false to break iteration, true otherwise.
- L185 _public prototype_ `template <typename TBoundsType> bool ForEachInstance(const TBoundsType& QueryBounds, FInstanceOperationFunc InOperation, FInstancedActorsIterationContext& IterationContext , TOptional<FInstancedActorDataPredicateFunc> InstancedActorDataPredicate = TOptional<FInstancedActorDataPredicateFunc>()) const;`
- L195 _public prototype_ `bool HasInstancesOfClass(const FBox& QueryBounds, TSubclassOf<AActor> ActorClass, const bool bTestActorsIfSpawned = false , const EInstancedActorsBulkLODMask AllowedLODs = EInstancedActorsBulkLODMask::All) const;` — Checks whether there are any instanced actors within this manager, representing ActorClass or its subclasses inside QueryBounds. The check doesn't differentiate between hydrated and dehydrated actors (i.e. whether there's an actor instance associated with the instance or not). @param bTestActorsIfSpawned if true then when an instance is found to overlap given bounds, and it has an actor spawned associated with it, then the actor itself will be tested against the bounds for more precise test.
- L203 _public prototype_ `template <typename TBoundsType> static UE::InstancedActors::EInsideBoundsTestResult IsInstanceInsideBounds(const TBoundsType & QueryBounds , const FInstancedActorsInstanceHandle& InstanceHandle, const FTransform & InstanceTransform);` — Determines whether the actor instance given by InstanceHandle overlaps QueryBounds. The test involves calculating bounding box of the actor representation of the given instance (i.e. it's not only the transform that's being tested).
- L207 _public prototype_ `void AuditInstances(FOutputDevice& Ar, bool bDebugDraw = false, float DebugDrawDuration = 10.0f) const;` — Outputs instance metrics to Ar
- L210 _public prototype_ `void CompactInstances(FOutputDevice& Ar);` — Called by IA.CompactInstances console command to fully remove FreeList instances
- L212 _public prototype_ `void AddModifierVolume(UInstancedActorsModifierVolumeComponent& ModifierVolume);`
- L213 _public prototype_ `void RemoveModifierVolume(UInstancedActorsModifierVolumeComponent& ModifierVolume);`
- L214 _public prototype_ `void RemoveAllModifierVolumes();`
- L217 _public prototype_ `void RequestPersistentDataSave();` — Request the persistent data system to re-save this managers persistent data
- L220 _public prototype_ `static FBox CalculateBounds(TSubclassOf<AActor> ActorClass);` — Helper function to deduce appropriate instanced static mesh bounds for ActorClass
- L223 _public prototype_ `TSharedPtr<FMassEntityManager> GetMassEntityManager() const;` — @return the Mass entity manager used to spawn entities. Valid only after BeginPlay
- L224 _public prototype_ `FMassEntityManager& GetMassEntityManagerChecked() const;`
- L227 _public prototype_ `UInstancedActorsSubsystem* GetInstancedActorSubsystem() const;` — @return the Instanced Actor Subsystem this Manager is registered with. Valid only after BeginPlay
- L228 _public prototype_ `UInstancedActorsSubsystem& GetInstancedActorSubsystemChecked() const;`
- L232 _public prototype_ `virtual uint32 GetDefaultGridSize(UWorld* InWorld) const override;`
- L233 _public prototype_ `virtual FGuid GetGridGuid() const override;`
- L234 _public prototype_ `void SetGridGuid(const FGuid& InGuid);`
- L238 _public prototype_ `static void UpdateInstanceStats(int32 InstanceCount, EInstancedActorsBulkLOD LODMode, bool Increment);`
- L243 _public prototype_ `void RegisterInstanceDatasComponents(const UInstancedActorsData& InstanceData, TConstArrayView<TObjectPtr<UInstancedStaticMeshComponent>> Components);` — Registers Components as related to InstanceData for IActorInstanceManagerInterface-related purposes.
- L249 _public prototype_ `void UnregisterInstanceDatasComponent(UInstancedStaticMeshComponent& Component);` — Unregisters Component from IActorInstanceManagerInterface-related tracking. Note that the function will assert whether the Component has been registered in the first place
- L251 _public prototype_ `virtual void CreateISMComponents(const FInstancedActorsVisualizationDesc& VisualizationDesc, FConstSharedStruct SharedSettings , TArray<TObjectPtr<UInstancedStaticMeshComponent>>& OutComponents, const bool bEditorPreviewISMCs = false);`
- L255 _public prototype_ `virtual void Serialize(FStructuredArchive::FRecord Record) override;`
- L260 _protected function_ `virtual void RequestActorSave(AActor* Actor)` — mz@todo a temp glue to be removed once InstancedActors get moved out of original project for good. It's virtual and I don't like it.
- L262 _protected function_ `virtual void OnInitializeModifyAndSpawnEntities()`
- L265 _protected prototype_ `virtual void OnReplicationStartedForIris(const FOnReplicationStartedParams&) override;`
- L266 _protected prototype_ `virtual void BeginPlay() override;`
- L267 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L268 _protected prototype_ `virtual bool IsHLODRelevant() const override;`
- L269 _protected prototype_ `virtual void PostLoad() override;`
- L271 _protected function_ `virtual bool IsUserManaged() const override`
- L272 _protected prototype_ `virtual void GetStreamingBounds(FBox& OutRuntimeBounds, FBox& OutEditorBounds) const override;`
- L277 _protected prototype_ `virtual int32 ConvertCollisionIndexToInstanceIndex(int32 InIndex, const UPrimitiveComponent* RelevantComponent) const override;`
- L278 _protected prototype_ `virtual AActor* FindActor(const FActorInstanceHandle& Handle) override;`
- L279 _protected prototype_ `virtual AActor* FindOrCreateActor(const FActorInstanceHandle& Handle) override;`
- L280 _protected prototype_ `virtual UClass* GetRepresentedClass(const int32 InstanceIndex) const override;`
- L281 _protected prototype_ `virtual ULevel* GetLevelForInstance(const int32 InstanceIndex) const override;`
- L282 _protected prototype_ `virtual FTransform GetTransform(const FActorInstanceHandle& Handle) const override;`
- L292 _protected prototype_ `void SerializeInstancePersistenceData(FStructuredArchive::FRecord Record, UInstancedActorsData* InstanceData, int64 TimeDelta) const;` — Called by Serialize for SaveGame archives to save / load IAD persistence data @param Record		The archive record to read / write IAD save data to @param InstanceData	The InstanceData to serialize from / to. May be nullptr when loading if Record's IAD has been removed since saving. In this case, we still need to read Record to seek the archive past this IAD record consistently. @param TimeDelta		Real time in seconds since serialization (0 when saving)
- L295 _protected prototype_ `virtual void DespawnAllEntities();` — Despawns all entities spawned by individual UInstancedActorsData instances.
- L298 _protected prototype_ `void DespawnAllEntities(bool bIsSwitchingSubsystems);` — `UE_DEPRECATED(5.8, "Using DespawnAllEntities with a parameter is deprecated.")`
- L304 _protected prototype_ `void TryRunPendingModifiers();` — Attempts to run any 'pending' modifiers in ModifierVolumes where are appropriate to run given HasSpawnedEntities Called in BeginPlay prior to, and then again after SpawnEntities. Also called in AddModifierVolume. @see UInstancedActorsModifierBase::bRequiresSpawnedEntities
- L307 _protected prototype_ `void OnPersistentDataRestored();` — Called when persistent data has been applied / restored
- L310 _protected prototype_ `FBox CalculateLocalInstanceBounds() const;` — Calculate cumulative local space instance bounds for all PerActorClassInstanceData
- L315 _public prototype_ `UInstancedActorsData& GetOrCreateActorInstanceData(TSubclassOf<AActor> ActorClass, const FInstancedActorsTagSet& AdditionalInstanceTags, bool bCreateEditorPreviewISMCs = true);` — Helper function to create and initialize per-actor-class UInstancedActorsData's, optionally further partitioned by AdditionalInstanceTags
- L318 _protected prototype_ `virtual UInstancedActorsData* CreateNextInstanceActorData(TSubclassOf<AActor> ActorClass, const FInstancedActorsTagSet& AdditionalInstanceTags);`
- L321 _protected prototype_ `virtual void PreRegisterAllComponents() override;` — Used to set the right properties on the editor ISMCs so we can do per-instance selection.
- L325 _protected prototype_ `static void SetUpEditorPreviewISMComponent(TNotNull<UInstancedStaticMeshComponent*> ISMComponent);` — Configures given ISMComponent for editor-preview purposes
- L328 _protected member_ `TObjectPtr<UInstancedActorsSubsystem> InstancedActorSubsystem;` — `UPROPERTY(Transient)`
- L331 _protected member_ `FInstancedActorsManagerHandle ManagerHandle;` — `UPROPERTY(Transient)`
- L333 _protected member_ `TSharedPtr<FMassEntityManager> MassEntityManager;`
- L337 _protected member_ `FGuid SavedActorGuid = FGuid();` — `UPROPERTY(VisibleAnywhere, Category=InstancedActors)` — Saved Actor Guid. Initialized from the actor name in constructor
- L341 _protected member_ `bool bHasSpawnedEntities = false;` — `UPROPERTY(Transient)` — True if SpawnEntities has been called to spawn entities. Reset in EndPlay
- L344 _protected member_ `bool bHasSetupLoadedInstances : 1 = false;` — True if SetupLoadedInstances has ever been called
- L352 _protected member_ `uint16 NextInstanceDataID = 0;` — `UPROPERTY()` — Incremented in GetOrCreateActorInstanceData to provide IAD's with a stable, unique identifier within this IAM. @see UInstancedActorsData::ID
- L356 _protected member_ `TArray<TObjectPtr<UInstancedActorsData>> PerActorClassInstanceData;` — `UPROPERTY(Instanced, VisibleAnywhere, BlueprintReadOnly, Category=InstancedActors)` — Per-actor-class instance data populated by AddActorInstance
- L360 _protected member_ `FBox InstanceBounds = FBox(ForceInit);` — `UPROPERTY(Transient)` — World space cumulative instance bounds, calculated in BeginPlay
- L363 _protected member_ `TArray<TWeakObjectPtr<UInstancedActorsModifierVolumeComponent>> ModifierVolumes;` — Modifier volumes added via AddModifierVolume
- L371 _protected member_ `TBitArray<> PendingModifierVolumes;` — A bit flag per volume in ModifierVolumes for whether the volume has pending Modifiers to run on this manager i.e if PendingModifierVolumeModifiers[VolumeIndex] has any true flags. Some modifiers can run prior to entity spawning for efficiency purposes, others must be held 'pending' later execution after entities have spawned.
- L380 _protected member_ `TArray<TBitArray<>> PendingModifierVolumeModifiers;` — A set of bit flags per volume in ModifierVolumes, matching each modifiers Modifiers list, marking whether the Modifier has yet to run on this manager or not (true = needs running). Some modifiers can run prior to entity spawning for efficiency purposes, others must be held 'pending' later execution after entities have spawned.
- L383 _protected member_ `TMap<TObjectPtr<UInstancedStaticMeshComponent>, int32> ISMComponentToInstanceDataMap;` — `UPROPERTY(Transient)`
- L387 _protected member_ `TSubclassOf<UInstancedActorsData> InstancedActorsDataClass;` — `UPROPERTY(EditAnywhere, Category=InstancedActor)` — Class to be spawned to represent individual actor class instances.
- L389 _protected member_ `mutable FMassEntityQuery InstancedActorLocationQuery;`
- L394 _private member_ `FGuid ManagerGridGuid;` — `UPROPERTY()`
- L398 _private member_ `bool bLockInstanceLocation = true;` — `UPROPERTY(EditAnywhere, Transient, meta = (DisplayPriority = 1), Category = InstancedActors)` — Set this to false to be able to move the instances contained by this IAM.The property is not saved and will reset.
- L402 _private prototype_ `virtual FText GetSMInstanceDisplayName(const FSMInstanceId& InstanceId) const override;`
- L403 _private prototype_ `virtual FText GetSMInstanceTooltip(const FSMInstanceId& InstanceId) const override;`
- L404 _private prototype_ `virtual bool CanEditSMInstance(const FSMInstanceId& InstanceId) const override;`
- L405 _private prototype_ `virtual bool CanMoveSMInstance(const FSMInstanceId& InstanceId, const ETypedElementWorldType WorldType) const override;`
- L406 _private prototype_ `virtual bool GetSMInstanceTransform(const FSMInstanceId& InstanceId, FTransform& OutInstanceTransform, bool bWorldSpace = false) const override;`
- L407 _private prototype_ `virtual bool SetSMInstanceTransform(const FSMInstanceId& InstanceId, const FTransform& InstanceTransform, bool bWorldSpace = false, bool bMarkRenderStateDirty = false, bool bTeleport = false) override;`
- L408 _private prototype_ `virtual void NotifySMInstanceMovementStarted(const FSMInstanceId& InstanceId) override;`
- L409 _private prototype_ `virtual void NotifySMInstanceMovementOngoing(const FSMInstanceId& InstanceId) override;`
- L410 _private prototype_ `virtual void NotifySMInstanceMovementEnded(const FSMInstanceId& InstanceId) override;`
- L411 _private prototype_ `virtual void NotifySMInstanceSelectionChanged(const FSMInstanceId& InstanceId, const bool bIsSelected) override;`
- L412 _private prototype_ `virtual bool DeleteSMInstances(TArrayView<const FSMInstanceId> InstanceIds) override;`
- L413 _private prototype_ `virtual bool DuplicateSMInstances(TArrayView<const FSMInstanceId> InstanceIds, TArray<FSMInstanceId>& OutNewInstanceIds) override;`
- L420 _private prototype_ `AActor* FindActorInternal(const FActorInstanceHandle& Handle, FMassEntityView& OutEntityView, bool bEnsureOnMissingInstanceDataOrMassEntity) const;` — Try to extract the actor from the provided handle or from associated Mass Entity. When unable to retrieve it returns nullptr but also the associated EntityView so caller could reuse it to create the actor.
- L422 _private prototype_ `AActor* GetActorForInstance(const UInstancedActorsData& InstanceData, const int32 InstancedActorIndex) const;`
- L424 _private prototype_ `FInstancedActorsInstanceHandle ActorInstanceHandleFromFSMInstanceId(const FSMInstanceId& InstanceId) const;`
- L431 _function_ `inline FInstancedActorsManagerHandle AInstancedActorsManager::GetManagerHandle() const`
- L436 _function_ `inline FBox AInstancedActorsManager::GetInstanceBounds() const`
- L441 _function_ `inline bool AInstancedActorsManager::HasSpawnedEntities() const`
- L446 _function_ `inline TConstArrayView<TObjectPtr<UInstancedActorsData>> AInstancedActorsManager::GetAllInstanceData() const`
- L451 _function_ `inline TSharedPtr<FMassEntityManager> AInstancedActorsManager::GetMassEntityManager() const`
- L456 _function_ `inline FMassEntityManager& AInstancedActorsManager::GetMassEntityManagerChecked() const`
- L462 _function_ `inline UInstancedActorsSubsystem* AInstancedActorsManager::GetInstancedActorSubsystem() const`
- L467 _function_ `inline UInstancedActorsSubsystem& AInstancedActorsManager::GetInstancedActorSubsystemChecked() const`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace InstancedActors` (scope `UE`)
- L45 _namespace_ `namespace CVars` (scope `UE::InstancedActors`)
- L47 _externvar_ `extern bool bEnablePersistence;` (scope `UE::InstancedActors::CVars`)
- L51 _prototype_ `template <typename TBoundsType> bool PassesBoundsTest(const TBoundsType& QueryBounds, EBoundsTestType BoundsTestType, const FInstancedActorsInstanceHandle& InstanceHandle, const FTransform& InstanceTransform);` (scope `UE::InstancedActors`)
- L55 _delegate_ `DECLARE_STATS_GROUP(TEXT("InstanceActor Rendering"), STATGROUP_InstancedActorsRender`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsModifierVolume.h` (Public)


#### class `AInstancedActorsModifierVolume`  
`class AInstancedActorsModifierVolume : public AActor`  
_L16-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: A 3D volume with a list of Modifiers to execute against any Instanced Actor's found within the volume. @see UInstancedActorsModifierVolumeComponent
- L22 _public prototype_ `AInstancedActorsModifierVolume(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L24 _public function_ `inline UInstancedActorsModifierVolumeComponent* GetModifierVolumeComponent() const`
- L32 _protected member_ `TObjectPtr<UInstancedActorsModifierVolumeComponent> ModifierVolumeComponent;` — `UPROPERTY(Category = InstancedActorsModifierVolume, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Instanced Actor Modifier Volume", AllowPrivateAccess = "true"))`

#### class `AInstancedActorsRemovalModifierVolume`  
`class AInstancedActorsRemovalModifierVolume : public AInstancedActorsModifierVolume`  
_L40-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AInstancedActorsModifierVolume`
- desc: A 3D volume that performs filtered removal of Instanced Actor's found within the volume. @see URemoveInstancesModifierVolumeComponent
- L46 _public prototype_ `AInstancedActorsRemovalModifierVolume(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsModifierVolumeComponent.h` (Public)


#### enum `EInstancedActorsVolumeShape`  
`enum class EInstancedActorsVolumeShape : uint8`  
_L17-21_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Box`
- L20 _public enumerator_ `Sphere`

#### class `UInstancedActorsModifierVolumeComponent`  
`class UInstancedActorsModifierVolumeComponent : public UPrimitiveComponent`  
_L28-134_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Instanced Actors", HideCategories=(Object, HLOD, Lighting, VirtualTexture, Collision, TextureStreaming, Mobile, Physics, Tags, AssetUserData, Activation, Cooking, Navigation, Input, Mobility), Meta=(BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- desc: A 3D volume component with a list of Modifiers to execute against any Instanced Actor's found within the volume. @see UInstancedActorsModifierBase
- L34 _public prototype_ `UInstancedActorsModifierVolumeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L39 _public member_ `EInstancedActorsVolumeShape Shape = EInstancedActorsVolumeShape::Box;` — `UPROPERTY(Replicated, EditAnywhere, Category="Instanced Actor Modifier Volume")` — Volume bounds shape Note: Replicated only in the initial bunch
- L44 _public member_ `FVector Extent = FVector(1.0f);` — `UPROPERTY(Replicated, EditAnywhere, Category="Instanced Actor Modifier Volume", meta=(EditCondition="Shape==EInstancedActorsVolumeShape::Box", EditConditionHides))` — Local space volume half-extent (size along side = Extent * 2 * ComponentScale3D). Used if Shape == Box Note: Replicated only in the initial bunch
- L49 _public member_ `float Radius = 1.0f;` — `UPROPERTY(Replicated, EditAnywhere, Category="Instanced Actor Modifier Volume", meta=(EditCondition="Shape==EInstancedActorsVolumeShape::Sphere", EditConditionHides))` — Local space volume radius (diameter = Radius * 2 * ComponentScale3D). Used if Shape == Sphere Note: Replicated only in the initial bunch
- L52 _public member_ `TArray<TObjectPtr<UInstancedActorsModifierBase>> Modifiers;` — `UPROPERTY(EditAnywhere, Category="Instanced Actor Modifier Volume", Instanced)`
- L60 _public member_ `bool bIgnoreOwnLevelsInstances = false;` — `UPROPERTY(EditAnywhere, Category="Instanced Actor Modifier Volume")` — If true, instances within the same outer level as this modifier volume will be skipped for modification. Useful when placed in injected or streaming levels, to modify the root level they're place in e.g: to clear space for the injected level.
- L68 _public member_ `TArray<TSoftObjectPtr<UWorld>> LevelsToIgnore;` — `UPROPERTY(Replicated, EditAnywhere, AdvancedDisplay, Category="Instanced Actor Modifier Volume")` — If set, instances in IAMs which belong to these levels will be skipped (unaffected) by this modifier volume. Useful for putting a modifier volume in a sub-level to affect the outer level it's placed in, but skipping the sub-level content.
- L71 _public member_ `FColor Color = FColor::White;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L74 _public member_ `bool bDrawOnlyIfSelected = false;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L77 _public member_ `float LineThickness = 5.0f;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L83 _public prototype_ `void OnAddedToSubsystem(UInstancedActorsSubsystem& InstancedActorSubsystem, FInstancedActorsModifierVolumeHandle InModifierVolumeHandle);` — Finds managers already registered with InInstancedActorSubsystem and adds this modifier to them. Called either in BeginPlay if InInstancedActorSubsystem was already initialized or latently once it is, in UInstancedActorsSubsystem::Initialize
- L86 _public prototype_ `void OnAddedToManager(AInstancedActorsManager& Manager);` — Called on addition to Manager in AInstancedActorsManager::AddModifierVolume
- L89 _public prototype_ `void OnRemovedFromManager(AInstancedActorsManager& Manager);` — Called on removal from Manager in AInstancedActorsManager::RemoveModifierVolume
- L108 _public prototype_ `bool TryRunPendingModifiers(AInstancedActorsManager& Manager, TBitArray<>& InOutPendingModifiers);` — Executes Modifiers for all instances in Manager overlapped by this volume. If the entire Manager is enveloped by this volume, UInstancedActorsModifierBase::ModifyAllInstances will be called, providing a fast path opportunity for whole-manager modification. By default, this simply calls UInstancedActorsModifierBase::ModifyInstance for all instances. For partial overlaps, UInstancedActorsModifierBase::ModifyInstance will be called for only those instances in Manager whos instance locations are contained within this volume. @param Manager				The Manager to execute Modifiers on. @param InOutPendingModifiers	Bit-flag array with flag per Modifiers whether the modifier is pending execution for Manager. If the modifier can run (@see UInstancedActorsModifierBase::bRequiresSpawnedEntities) the bit-flag will be set false after execution. @return true if all pending modifiers were run, false if any remain pending.
- L111 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L115 _public prototype_ `virtual void BeginPlay() override;`
- L116 _public prototype_ `virtual void EndPlay(EEndPlayReason::Type Reason) override;`
- L120 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L124 _public prototype_ `FPrimitiveSceneProxy* CreateSceneProxy();`
- L130 _protected member_ `FInstancedActorsModifierVolumeHandle ModifierVolumeHandle;` — `UPROPERTY(Transient)`
- L133 _protected member_ `TArray<TWeakObjectPtr<AInstancedActorsManager>> ModifiedManagers;` — `UPROPERTY(Transient)`

#### class `URemoveInstancesModifierVolumeComponent`  
`class URemoveInstancesModifierVolumeComponent : public UInstancedActorsModifierVolumeComponent`  
_L138-143_
- reflection: `UCLASS(MinimalAPI, Meta=(BlueprintSpawnableComponent))`
- inherits: `UInstancedActorsModifierVolumeComponent`
- desc: A UInstancedActorsModifierVolumeComponent with a URemoveInstancedActorsModifier modifier pre-added to Modifiers
- L142 _private prototype_ `URemoveInstancesModifierVolumeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsModifiers.h` (Public)


#### class `UInstancedActorsModifierBase`  
`class UInstancedActorsModifierBase : public UObject`  
_L29-137_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Base class for 'modifier' operations to run against Instanced Actors within AInstancedActorsManager's Used by UInstancedActorsModifierVolumeComponent's to modify instances within their volumes. Subclasses must implement at least ModifyInstance but can also override ModifyAllInstances to provide a whole-manager fast path. @see UInstancedActorsModifierVolumeComponent
- L36 _public member_ `FGameplayTagQuery InstanceTagsQuery;` — `UPROPERTY(EditAnywhere, Category = InstancedActors)` — Optional tag query to filter instances to modify
- L44 _public function_ `bool DoesRequireSpawnedEntities() const` — If true, this modifier will wait to be called on Managers only after Mass entities have been spawned for all instances. @see bRequiresSpawnedEntities
- L56 _public prototype_ `virtual void ModifyAllInstances(AInstancedActorsManager& Manager, FInstancedActorsIterationContext& IterationContext);` — Callback to modify all instances in Manager, providing a 'fast path' opportunity for modifiers to perform whole-manager operations. By default this simply calls ModifyInstance for all instances. @param Manager			The whole manager to modify. If bRequiresSpawnedEntities = false, this Manager may or may not have spawned entities yet. @see bRequiresSpawnedEntities @param InterationContext Provides useful functionality while iterating instances like safe instance deletion @see AInstancedActorsManager::ForEachInstance
- L70 _public function_ `virtual bool ModifyInstance(const FInstancedActorsInstanceHandle& InstanceHandle, const FTransform& InstanceTransform, FInstancedActorsIterationContext& IterationContext) PURE_VIRTUAL(UInstancedActorsModifierBase::ModifyInstance, return false;) template<typename TBoundsType> void ModifyAllInstancesInBounds(const TBoundsType& Bounds, AInstancedActorsManager& Manager, FInstancedActorsIterationContext& IterationContext)` — Per-instance callback to modify single instances. Called by ModifyAllInstances & ModifyAllInstancesInBounds in their default implementations. @param InstanceHandle	Handle to the instance to Modify. @param InstanceTransform If entities have been spawned, this will be taken from the Mass transform fragment, else from UInstancedActorsData::InstanceTransforms. @param InterationContext Provides useful functionality while iterating instances like safe instance deletion. @return Return true to continue modification of subsequent instances, false to break iteration.
- L136 _protected member_ `bool bRequiresSpawnedEntities = true;` — If true, this modifier will wait to be called on Managers only after Mass entities have been spawned for all instances. If false, this modifier may be called on managers prior to entity spawning (i.e: Manager.HasSpawnedEntities() = false) where operations like RuntimeRemoveEntities are cheaper to run pre-entity spawning. However, as latently spawned UInstancedActorsModifierVolumeComponent's may be matched up with Managers that have already spawned entities, modifiers with bRequiresSpawnedEntities = false must also support execution on Managers with HasSpawnedEntities() = true and should check Managers state accordingly in Modify callbacks. Modification is tracked per manager though and is guaranteed to only run once per manager, so modifiers that are run pre-entity spawning will not try and run again post-spawn. @see AInstancedActorsManager::TryRunPendingModifiers

#### class `URemoveInstancedActorsModifier`  
`class URemoveInstancedActorsModifier : public UInstancedActorsModifierBase`  
_L144-152_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInstancedActorsModifierBase`
- desc: Modifier which removes all affected instances using AInstancedActorsManager::RuntimeRemoveInstances for individual instances. For whole-manager modification this simply destroys the Manager.
- L148 _public prototype_ `URemoveInstancedActorsModifier();`
- L150 _public prototype_ `virtual void ModifyAllInstances(AInstancedActorsManager& Manager, FInstancedActorsIterationContext& IterationContext) override;`
- L151 _public prototype_ `virtual bool ModifyInstance(const FInstancedActorsInstanceHandle& InstanceHandle, const FTransform& InstanceTransform, FInstancedActorsIterationContext& IterationContext) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L90 _function_ `` (scope `UInstancedActorsModifierBase::ModifyInstance`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsReplication.h` (Public)


#### struct `FInstancedActorsDelta`  
`struct FInstancedActorsDelta : public FFastArraySerializerItem`  
_L17-81_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializerItem`
- desc: Per-instance delta's against the cooked instance data, for persistence and replication
- L21 _public function_ `FInstancedActorsDelta(FInstancedActorsInstanceIndex InInstanceIndex) : InstanceIndex(InInstanceIndex)`
- L25 _public prototype_ `FInstancedActorsDelta() = default;`
- L31 _public function_ `inline bool HasAnyDeltas() const` — Returns true if this delta actually contains any non-default deltas / overrides to apply.
- L41 _public function_ `FInstancedActorsInstanceIndex GetInstanceIndex() const`
- L43 _public function_ `bool IsDestroyed() const`
- L45 _public function_ `const bool HasCurrentLifecyclePhase() const`
- L46 _public function_ `uint8 GetCurrentLifecyclePhaseIndex() const`
- L51 _public function_ `const bool HasCurrentLifecyclePhaseTimeElapsed() const` — mz@todo IA: move this section back
- L52 _public function_ `FFloat16 GetCurrentLifecyclePhaseTimeElapsed() const`
- L60 _private function_ `bool SetDestroyed(bool bInDestroyed)`
- L61 _private function_ `void SetCurrentLifecyclePhaseIndex(uint8 InCurrentLifecyclePhaseIndex)`
- L62 _private function_ `void ResetLifecyclePhaseIndex()`
- L65 _private member_ `FInstancedActorsInstanceIndex InstanceIndex;` — `UPROPERTY()`
- L68 _private member_ `uint8 bDestroyed : 1 = false;` — `UPROPERTY()`
- L71 _private member_ `uint8 CurrentLifecyclePhaseIndex = (uint8)INDEX_NONE;` — `UPROPERTY()`
- L74 _private function_ `void SetCurrentLifecyclePhaseTimeElapsed(FFloat16 InCurrentLifecyclePhaseTimeElapsed)`
- L75 _private function_ `void ResetLifecyclePhaseTimeElapsed()`
- L79 _private member_ `FFloat16 CurrentLifecyclePhaseTimeElapsed = -1.0f;` — Server-only (not replicated) time elapsed in current phase, saved & restored via persistence. Unrequired by client code which only needs to know about discrete phase changes for visual updates.

#### struct `FInstancedActorsDeltaList`  
`struct FInstancedActorsDeltaList : public FFastArraySerializer`  
_L84-151_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L88 _public prototype_ `void Initialize(UInstancedActorsData& InOwnerInstancedActorData);`
- L90 _public function_ `const TArray<FInstancedActorsDelta>& GetInstanceDeltas() const`
- L94 _public prototype_ `void Reset(bool bMarkDirty = true);` — Clear the InstanceDeltas list and resets InstancedActorData @param bMarkDirty If true, marks InstanceDeltas dirty for fast array replication
- L100 _public prototype_ `void SetInstanceDestroyed(FInstancedActorsInstanceIndex InstanceIndex);` — Adds or modifies a FInstancedActorsDelta for InstanceIndex, marking the instance as destroyed and marks the delta as dirty for replication and application on clients. This delta will also be persisted @see AInstancedActorsManager::SerializeInstancePersistenceData Note: This does not request a persistence re-save
- L102 _public prototype_ `void RemoveDestroyedInstanceDelta(FInstancedActorsInstanceIndex InstanceIndex);`
- L107 _public prototype_ `void SetCurrentLifecyclePhaseIndex(FInstancedActorsInstanceIndex InstanceIndex, uint8 InCurrentLifecyclePhaseIndex);` — Adds or modifies a FInstancedActorsDelta for InstanceIndex, specifying a new lifecycle phase to switch the instance to, and marks the delta as dirty for replication and application on clients Note: This does not request a persistence re-save
- L109 _public prototype_ `void RemoveLifecyclePhaseDelta(FInstancedActorsInstanceIndex InstanceIndex);`
- L115 _public prototype_ `void SetCurrentLifecyclePhaseTimeElapsed(FInstancedActorsInstanceIndex InstanceIndex, FFloat16 InCurrentLifecyclePhaseTimeElapsed);` — Adds or modifies a FInstancedActorsDelta for InstanceIndex, specifying a new elapse time for the current lifecycle phase. Note: This is a server-only delta and is NOT replicated to clients. It's simply stored in the delta list alongside the lifecycle phase index so they can be restored together from persistence and applied on the server in OnPersistentDataRestored -> ApplyInstanceDeltas
- L117 _public prototype_ `void RemoveLifecyclePhaseTimeElapsedDelta(FInstancedActorsInstanceIndex InstanceIndex);`
- L120 _public function_ `const uint16 GetNumDestroyedInstanceDeltas() const`
- L121 _public function_ `const uint16 GetNumLifecyclePhaseDeltas() const`
- L122 _public function_ `const uint16 GetNumLifecyclePhaseTimeElapsedDeltas() const`
- L125 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);` — UStruct overrides
- L128 _public prototype_ `void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);` — FFastArraySerializer overrides
- L129 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L130 _public prototype_ `void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize);`
- L134 _private prototype_ `FInstancedActorsDelta& FindOrAddInstanceDelta(FInstancedActorsInstanceIndex InstanceIndex);`
- L135 _private prototype_ `void RemoveInstanceDelta(uint16 DeltaIndex);`
- L139 _private member_ `TMap<FInstancedActorsInstanceIndex, uint16> InstanceIndexToDeltaIndex;` — Lookup the InstanceDeltas index from a FInstancedActorsInstanceIndex. Note: This is server only data, initialized in Initialize
- L142 _private member_ `uint16 NumDestroyedInstanceDeltas = 0;` — Cached counts for persistence serialization
- L143 _private member_ `uint16 NumLifecyclePhaseDeltas = 0;`
- L144 _private member_ `uint16 NumLifecyclePhaseTimeElapsedDeltas = 0;`
- L147 _private member_ `TArray<FInstancedActorsDelta> InstanceDeltas;` — `UPROPERTY(Transient)` — FastArray of Instance replication data.
- L150 _private member_ `UInstancedActorsData* InstancedActorData = nullptr;` — Raw pointer to the UInstancedActorsData this FInstancedActorsDeltaList instance is a member of

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FInstancedActorsDeltaList > : public TStructOpsTypeTraitsBase2< FInstancedActorsDeltaList >`  
_L154-160_
- inherits: `TStructOpsTypeTraitsBase2<FInstancedActorsDeltaList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L157-159_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L158 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anon59c774e50103`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsRepresentationActorManagement.h` (Public)


#### class `UInstancedActorsRepresentationActorManagement`  
`class UInstancedActorsRepresentationActorManagement : public UMassRepresentationActorManagement`  
_L14-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRepresentationActorManagement`
- L19 _public prototype_ `AActor* FindOrInstantlySpawnActor(UMassRepresentationSubsystem& RepresentationSubsystem, FMassEntityManager& EntityManager, FMassEntityView& EntityView);`
- L22 _public prototype_ `virtual void OnActorUnlinked(AActor& Actor);` — Called by UInstancedActorsData::UnlinkActor to cleanup actor delegate callbacks
- L26 _protected prototype_ `virtual EMassActorSpawnRequestAction OnPostActorSpawn(const FMassActorSpawnRequestHandle& SpawnRequestHandle , FConstStructView SpawnRequest, TSharedRef<FMassEntityManager> EntityManager) const override;`
- L31 _protected prototype_ `virtual void SetActorEnabled(const EMassActorEnabledType EnabledType, AActor& Actor, const int32 EntityIdx , FMassCommandBuffer& CommandBuffer) const override;` — Overriding to make sure ticking doesn't get enabled on spawned actors - we don't want that for handled actors
- L35 _protected prototype_ `virtual void TeleportActor(const FTransform& Transform, AActor& Actor, FMassCommandBuffer& CommandBuffer) const;` — Overridden to skip transform updates for replicated actors on clients
- L38 _protected prototype_ `void OnSpawnedActorDestroyed(AActor& DestroyedActor, FMassEntityHandle EntityHandle) const;`
- L39 _protected prototype_ `void OnSpawnedActorMoved(USceneComponent* MovedActorRootComponent, EUpdateTransformFlags TransformUpdateFlags, ETeleportType TeleportType, FMassEntityHandle EntityHandle) const;`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsRepresentationSubsystem.h` (Public)


#### class `UInstancedActorsRepresentationSubsystem`  
`class UInstancedActorsRepresentationSubsystem : public UMassRepresentationSubsystem`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UMassRepresentationSubsystem`
- L16 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L17 _protected prototype_ `virtual void Deinitialize() override;`
- L20 _protected prototype_ `void OnSettingsChanged();`
- L22 _protected member_ `FDelegateHandle OnSettingsChangedHandle;`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsRuntimeRemovalProcessor.h` (Public)


#### class `UInstancedActorsRuntimeRemovalProcessor`  
`class UInstancedActorsRuntimeRemovalProcessor : public UMassProcessor`  
_L17-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor's sole responsibility is to find all UInstancedActorsData containing entities pending destruction and to actually schedule their destruction. It also marks their FMassRepresentationFragment as bIsPendingDestruction in order to prevent downstream processors from running any unnecessary representation logic on them. @see UInstancedActorsData::RuntimeRemoveInstances, UInstancedActorsSubsystem::MarkIadDirtyWithEntitiesPendingDestruction
- L21 _public prototype_ `UInstancedActorsRuntimeRemovalProcessor();`
- L24 _protected function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L29 _protected member_ `FMassEntityQuery EntityQuery;` — Not directly used, but kept for the dependency solver

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsSettings.h` (Public)


#### struct `FInstancedActorsConfig`  
`struct FInstancedActorsConfig`  
_L17-32_
- reflection: `USTRUCT()`
- L22 _public member_ `TSubclassOf<UMassActorSpawnerSubsystem> ServerActorSpawnerSubsystemClass;` — `UPROPERTY(Config, EditAnywhere, Category = Subsystems, NoClear, meta = (MetaClass = "/Script/MassActors.MassActorSpawnerSubsystem"))`
- L25 _public member_ `TSubclassOf<UMassActorSpawnerSubsystem> ClientActorSpawnerSubsystemClass;` — `UPROPERTY(Config, EditAnywhere, Category = Subsystems, NoClear, meta = (MetaClass = "/Script/MassActors.MassActorSpawnerSubsystem"))`
- L28 _public member_ `TSubclassOf<UInstancedActorsSubsystem> InstancedActorsSubsystemClass;` — `UPROPERTY(Config, EditAnywhere, Category = Subsystems, NoClear, meta = (MetaClass = "/Script/InstancedActors.InstancedActorsSubsystem"))`
- L31 _public member_ `TSubclassOf<UMassStationaryDistanceVisualizationTrait> StationaryVisualizationTraitClass;` — `UPROPERTY(Config, EditAnywhere, Category = Subsystems, NoClear, meta = (MetaClass = "/Script/MassRepresentation.MassStationaryDistanceVisualizationTrait"))`

#### struct `FClassConfigOverrideEntry`  
`struct FClassConfigOverrideEntry`  
_L35-43_
- reflection: `USTRUCT()`
- L39 _public member_ `FObjectKey Owner;`
- L42 _public member_ `FInstancedActorsConfig ConfigOverride;` — `UPROPERTY()`

#### class `UInstancedActorsProjectSettings`  
`class UInstancedActorsProjectSettings : public UDeveloperSettings`  
_L51-114_
- reflection: `UCLASS(Config=InstancedActors, defaultconfig, DisplayName = "Instanced Actors", MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Configurable project settings for the Instanced Actors system. @see FInstancedActorsClassSettingsBase and FInstancedActorsClassSettings for per-class specific runtime settings. @see AInstancedActorsManager
- L56 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSettingsChanged);`
- L58 _public prototype_ `UInstancedActorsProjectSettings();`
- L60 _public prototype_ `TSubclassOf<UMassActorSpawnerSubsystem> GetServerActorSpawnerSubsystemClass() const;`
- L61 _public prototype_ `TSubclassOf<UMassActorSpawnerSubsystem> GetClientActorSpawnerSubsystemClass() const;`
- L62 _public prototype_ `TSubclassOf<UInstancedActorsSubsystem> GetInstancedActorsSubsystemClass() const;`
- L63 _public prototype_ `TSubclassOf<UMassStationaryDistanceVisualizationTrait> GetStationaryVisualizationTraitClass() const;`
- L65 _public prototype_ `void RegisterConfigOverride(UObject& Owner, const FInstancedActorsConfig& Config);`
- L66 _public prototype_ `void UnregisterConfigOverride(UObject& Owner);`
- L68 _public function_ `FOnSettingsChanged& GetOnSettingsUpdated()`
- L71 _protected prototype_ `virtual void PostInitProperties() override;`
- L73 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L76 _protected prototype_ `void CompileSettings();`
- L81 _public member_ `int32 GridSize = 24480;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta = (ClampMin="0", Units=cm), Category = Grid)` — 3D grid size (distance along side) for partitioned instanced actor managers
- L85 _public member_ `FDataRegistryType NamedSettingsRegistryType = "In` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ActorClassSettings)` — Data Registry to gather 'named' FInstancedActorsSettings from during UInstancedActorsSubsystem init
- L89 _public member_ `FDataRegistryType ActorClassSettingsRegistryType = "In` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ActorClassSettings)` — Data Registry to gather per-class FInstancedActorsClassSettingsBase-based settings from during UInstancedActorsSubsystem init
- L96 _public member_ `FName DefaultBaseSettingsName = NAME_None;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ActorClassSettings)` — If specified, these named settings will be applied to the default settings used as the base settings set for all others, with a lower precedence than any per-class overrides
- L100 _public member_ `FName EnforcedSettingsName = NAME_None;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ActorClassSettings)` — If specified, these named settings will be applied as a final set of overrides to all settings, overriding / taking precedence over all previous values
- L103 _public member_ `FInstancedActorsConfig DefaultConfig;` — `UPROPERTY(Config, EditAnywhere, Category = ActorClassSettings)`
- L106 _protected member_ `FOnSettingsChanged OnSettingsUpdated;`
- L110 _protected member_ `FInstancedActorsConfig CompiledActiveConfig;` — `UPROPERTY(Transient)` — Represents the current config combining DefaultConfig and all registered ClassConfigOverrides
- L113 _protected member_ `TArray<FClassConfigOverrideEntry> ClassConfigOverrides;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define GET_INSTANCEDACTORS_CONFIG_VALUE(a) (GetMutableDefault<UInstancedActorsProjectSettings>()->a)`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSettingsChanged);`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsSettingsTypes.h` (Public)


#### struct `FInstancedActorsSettings`  
`struct FInstancedActorsSettings : public FTableRowBase`  
_L67-254_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- desc: Settings for controlling Instanced Actor behavior. Applied by 'actor class' either in groups via 'named settings' e.g: "SmallThings", "Trees" or on a specific class basis. Named settings are FInstancedActorsSettings registered by name in UInstancedActorsProjectSettings::NamedSettingsRegistryType data registry. Class-specific settings are FInstancedActorsSettings registered by actor class via FInstancedActorsClassSettingsBase's in the UInstancedActorsProjectSettings::ActorClassSettingsRegistryType data registry. Named settings can be used as bases here via FInstancedActorsClassSettingsBase::BaseSettings. @see UInstancedActorsProjectSettings for settings registry info.
- L74 _public member_ `uint8 bOverride_bInstancesCastShadows : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L77 _public member_ `uint8 bOverride_MaxActorDistance : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L80 _public member_ `uint8 bOverride_bDisableAutoDistanceCulling : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle), Category=InstancedActors)`
- L84 _public member_ `uint8 bOverride_MaxInstanceDistance_DEPRECATED : 1 = false;` — `UE_DEPRECATED(5.4, "Layers Object no longer available.")` — `UPROPERTY(meta = (DeprecatedProperty), Transient)`
- L87 _public member_ `uint8 bOverride_MaxInstanceDistances : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L90 _public member_ `uint8 bOverride_LODDistanceScales : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle), Category=InstancedActors)`
- L93 _public member_ `uint8 bOverride_AffectDistanceFieldLighting : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle), Category=InstancedActors)`
- L96 _public member_ `uint8 bOverride_DetailedRepresentationLODDistance : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L99 _public member_ `uint8 bOverride_ForceLowRepresentationLODDistance : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L102 _public member_ `uint8 bOverride_WorldPositionOffsetDisableDistance : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle), Category=InstancedActors)`
- L105 _public member_ `uint8 bOverride_bEjectOnActorMoved : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L108 _public member_ `uint8 bOverride_ActorEjectionMovementThreshold : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L111 _public member_ `uint8 bOverride_bCanEverAffectNavigation : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L114 _public member_ `uint8 bOverride_OverrideWorldPartitionGrid : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L117 _public member_ `uint8 bOverride_ScaleEntityCount : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L120 _public member_ `uint8 bOverride_ActorClass : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L123 _public member_ `uint8 bOverride_bCanBeDamaged : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L126 _public member_ `uint8 bOverride_bIgnoreModifierVolumes : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L129 _public member_ `uint8 bOverride_bModifierVolumeCheckFullyEnclosed : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L132 _public member_ `uint8 bOverride_bControlPhysicsState : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L135 _public member_ `uint8 bOverride_GameplayTags : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(InlineEditConditionToggle), Category=InstancedActors)`
- L141 _public member_ `bool bInstancesCastShadows = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bInstancesCastShadows"), Category=InstancedActors)` — Optional shadow casting override applied to instance ISMC's if set (shadow casting settings from ActorClass will be used for ISMC's if unset)
- L145 _public member_ `double MaxActorDistance = 1000.0;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bOverride_MaxActorDistance"), Category=InstancedActors)` — Distance in cm from player to spawn actors within. Beyond this, Actors will be switched to ISMC instances up to MaxDrawDistance
- L149 _public member_ `bool bDisableAutoDistanceCulling = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bDisableAutoDistanceCulling"), Category=InstancedActors)` — Disable auto computed distance culling using the bounding box of the static mesh - instance will render upto MaxInstanceDistance
- L153 _public member_ `bool bControlPhysicsState = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bControlPhysicsState"), Category=InstancedActors)` — If false, collision will not be managed by the mass LODs for this instance
- L155 _public member_ `static constexpr double DefaultMaxInstanceDistance = 100000.0;`
- L159 _public member_ `double MaxInstanceDistance_DEPRECATED = 100000.0;` — `UPROPERTY(meta = (DeprecatedProperty), Transient)` — Final draw distance for ISMC instances
- L163 _public member_ `TArray<double> MaxInstanceDistances = { DefaultMaxInstanceDistance, DefaultMaxInstanceDistance, DefaultMaxInstanceDistance, DefaultMaxInstanceDistance };` — `UPROPERTY(EditAnywhere, EditFixedSize, Meta = (EditFixedOrder, EditCondition = "bOverride_MaxInstanceDistances"), Category=InstancedActors)` — Scale applied on MaxDrawDistance for low quality level, see IA.ViewDistanceQuality
- L167 _public member_ `TArray<float> LODDistanceScales = { 1.0f, 1.0f, 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, EditFixedSize, Meta = (EditFixedOrder, EditCondition = "bOverride_LODDistanceScales"), Category=InstancedActors)` — Sets LOD Distance Scale for low quality level, see IA.ViewDistanceQuality
- L171 _public member_ `TArray<bool> AffectDistanceFieldLighting = { true, true, true, true };` — `UPROPERTY(EditAnywhere, EditFixedSize, Meta = (EditFixedOrder, EditCondition = "bOverride_AffectDistanceFieldLighting"), Category=InstancedActors)` — If enabled, then asset will be used in distance field lighting
- L175 _public member_ `double DetailedRepresentationLODDistance = 7000.0;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bOverride_DetailedRepresentationLODDistance"), Category=InstancedActors)` — Perform per-entity 'detailed' representation LOD calculation up to this distance from a viewer
- L179 _public member_ `double ForceLowRepresentationLODDistance = 27500.0;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bOverride_ForceLowRepresentationLODDistance"), Category=InstancedActors)` — Force 'Low' representation LOD for all entities further than this distance from a viewer
- L183 _public member_ `int32 WorldPositionOffsetDisableDistance = 5000;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bOverride_WorldPositionOffsetDisableDistance"), Category=InstancedActors)` — Distance in cm from which WPO is disabled
- L191 _public member_ `bool bEjectOnActorMoved = false;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bOverride_bEjectOnActorMoved"), Category=InstancedActors)` — If bEjectOnActorMoved = true, spawned Actors will have their locations monitored and if moved further than ActorEjectionMovementThreshold from their spawn location, they will be 'ejected' from their manager / marked as destroyed and transferred to persistence system.
- L199 _public member_ `float ActorEjectionMovementThreshold = 1.0f;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bOverride_ActorEjectionMovementThreshold"), Category=InstancedActors)` — If bEjectOnActorMoved = true, spawned Actors will have their locations monitored and if moved further than ActorEjectionMovementThreshold from their spawn location, they will be 'ejected' from their manager / marked as destroyed and transferred to persistence system.
- L203 _public member_ `bool bCanEverAffectNavigation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bCanEverAffectNavigation"), Category=InstancedActors)` — Can this object ever affect the navigation graph generation for AI etc.
- L207 _public member_ `FName OverrideWorldPartitionGrid = TEXT("Mai` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_OverrideWorldPartitionGrid"), Category=InstancedActors)` — What world partition grid should this instance be placed into.
- L211 _public member_ `float ScaleEntityCount = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_ScaleEntityCount", ClampMin="0.0", ClampMax="1.0", UIMin="0.8", UIMax="1.0"), Category=InstancedActors)` — Scale the number of entities spawned. It must be between 0.0 and 1.0, for 0% and 100% respectively.
- L215 _public member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_ActorClass"), Category=InstancedActors)` — Wholesale replace this type of entity with this actor instead.
- L219 _public member_ `bool bCanBeDamaged = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bCanBeDamaged"), Category=InstancedActors)` — Turn on or off damage.
- L223 _public member_ `bool bIgnoreModifierVolumes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bIgnoreModifierVolumes"), Category=InstancedActors)` — Completely disable modifier volumes for this type of instance.
- L227 _public member_ `bool bModifierVolumeCheckFullyEnclosed = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_bModifierVolumeCheckFullyEnclosed"), Category=InstancedActors)` — By default, modifier volumes will do a bounds intersection test against instances. If this is true, modifiers will instead do a fully-enclosed bounds test
- L231 _public member_ `FGameplayTagContainer GameplayTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bOverride_GameplayTags"), Category=InstancedActors)` — Gameplay Tags that can be used in Modifier queries
- L235 _public member_ `TArray<FName> AppliedSettingsOverrides;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)` — Note: Don't forget to implement overriding for new settings in ApplyOverrides and Stringification in ToString
- L239 _public member_ `uint8 ObjectClassVersion = 0;` — `UPROPERTY()`
- L242 _public function_ `virtual void PostSerialize(const FArchive& Ar)` — Sets up the cached tag containers
- L245 _public prototype_ `void ComputeLODDistanceData(double& OutMaxInstanceDistance, double& MaxDrawDistanceScale, float& OutLODDistanceScale) const;`
- L247 _public prototype_ `bool GetAffectDistanceFieldLighting() const;`
- L251 _public prototype_ `virtual void OverrideIfDefault(FConstStructView OverrideSettings, const FName& OverrideSettingsName);` — Apply OverrideSettings to settings not already overridden Note: This is designed for applying settings in reverse order i.e: applying highest priority settings first.
- L253 _public prototype_ `virtual FString DebugToString(bool bOverridesOnly = true) const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FInstancedActorsSettings> : public TStructOpsTypeTraitsBase2<FInstancedActorsSettings>`  
_L258-264_
- inherits: `TStructOpsTypeTraitsBase2<FInstancedActorsSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L261-263_

#### struct `FInstancedActorsClassSettingsBase`  
`struct FInstancedActorsClassSettingsBase : public FTableRowBase`  
_L300-316_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- desc: Per-class settings for instanced actors. Per-class settings defined in UInstancedActorsProjectSettings::ActorClassSettingsRegistryType are automatically applied to all instances of ActorClass, or its subclasses at runtime. Defining settings separate to the actor class itself in this way allows actor classes to be instanced with customization, without requiring subclassing to override behavior. Final compiled settings order for ActorClass is: 1) Default construted FInstancedActorsSettings 2) UInstancedActorsProjectSettings::DefaultBaseSettingsName 3) ActorClass::Super's FInstancedActorsClassSettingsBase BaseSettings (if any) [0] [1] [2] ... 4) ActorClass::Super's OverrideSettings ..... for all Super's .... 5) ActorClass BaseSettings [0] [1] [2] ... 6) ActorClass OverrideSettings 7) UInstancedActorsProjectSettings::EnforcedSettingsName @see FInstancedActorsSettings
- L311 _public member_ `TArray<FName> BaseSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InstancedActors)` — Optional ordered list of 'named' settings to apply to instances of ActorClass before applying OverrideSettings. BaseSettings are applied in order, so the last setting wins (with OverrideSettings having final say). Note: UInstancedActorsProjectSettings::DefaultBaseSettingsName if specified is effectively inserted into this list at 0
- L314 _public function_ `virtual FInstancedStruct MakeOverrideSettings() const` — A virtual function to be overridden by child-types that provide an instance of their specific FInstancedActorsSettings flavor

#### struct `FInstancedActorsClassSettings`  
`struct FInstancedActorsClassSettings : public FInstancedActorsClassSettingsBase`  
_L325-337_
- reflection: `USTRUCT()`
- inherits: `FInstancedActorsClassSettingsBase`
- desc: Generic implementation of FInstancedActorsClassSettingsBase that's using the generic FInstancedActorsSettings to override existing settings. If you want to extend the per-actor-class settings for your project then inhering either from FInstancedActorsClassSettings and add extra logic and properties to the child type, or inherit from FInstancedActorsClassSettingsBase to provide a project-specific settings struct that inherits FInstancedActorsSettings.
- L334 _public member_ `FInstancedActorsSettings OverrideSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InstancedActors)` — Settings specific to ActorClass instances, applied after / overriding BaseSettings. Note: UInstancedActorsProjectSettings::EnforcedSettingsName if specified can still override these.
- L336 _public function_ `virtual FInstancedStruct MakeOverrideSettings() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L24 _macro_ `#define IASETTINGS_OVERRIDE_IF_DEFAULT(SettingName) if (OverrideSettings.bOverride_##SettingName && !bOverride_##SettingName) \` — Helper macro for FInstancedActorsSettings::OverrideIfDefault e.g: IASETTINGS_OVERRIDE_IF_DEFAULT(bInstancesCastShadows) produces: if (OverrideSettings.bOverride_bInstancesCastShadows && !bOverride_bInstancesCastShadows) { bOverride_bInstancesCastShadows = true; bInstancesCastShadows = OverrideSettings.bInstancesCastShadows; }
- L38 _macro_ `#define IASETTINGS_SETTING_TO_STRING(SettingName) if (!bOverridesOnly || bOverride_##SettingName) \` — Helper macro for FInstancedActorsSettings::ToString e.g: IASETTINGS_OVERRIDE_TO_STRING(bInstancesCastShadows) produces: if (!bOverridesOnly || bOverride_bInstancesCastShadows) { SettingsString << TEXT("bInstancesCastShadows: ") << bInstancesCastShadows << TEXT(" "); }
- L43 _macro_ `#define IASETTINGS_FLOAT_SETTING_TO_STRING(SettingName) if (!bOverridesOnly || bOverride_##SettingName) \`
- L48 _macro_ `#define IASETTINGS_UOBJECT_SETTING_TO_STRING(SettingName) if (!bOverridesOnly || bOverride_##SettingName) \`
- L262 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon1402f7f10103`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsStationaryLODBatchProcessor.h` (Public)


#### class `UInstancedActorsStationaryLODBatchProcessor`  
`class UInstancedActorsStationaryLODBatchProcessor : public UMassProcessor`  
_L13-30_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L18 _public prototype_ `UInstancedActorsStationaryLODBatchProcessor();`
- L21 _protected function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override`
- L22 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L23 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L25 _protected member_ `FMassEntityQuery LODChangingEntityQuery;`
- L26 _protected member_ `FMassEntityQuery DirtyVisualizationEntityQuery;`
- L29 _protected member_ `double DelayPerBulkLOD[(int)EInstancedActorsBulkLOD::MAX];` — `UPROPERTY(EditDefaultsOnly, Category="Mass", config)`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsSubsystem.h` (Public)


#### class `UInstancedActorsSubsystem`  
`class UInstancedActorsSubsystem : public UTickableWorldSubsystem`  
_L36-306_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UTickableWorldSubsystem`
- desc: Instanced Actor subsystem used to spawn AInstancedActorsManager's and populate their instance data. It also keeps track of all InstancedActorDatas and can be queried for them @see AInstancedActorsManager
- L41 _public prototype_ `UInstancedActorsSubsystem();`
- L43 _public prototype_ `static UInstancedActorsSubsystem* Get(UObject* WorldContextObject);`
- L45 _public prototype_ `static UInstancedActorsSubsystem& GetChecked(UObject* WorldContextObject);`
- L53 _public prototype_ `FInstancedActorsInstanceHandle InstanceActor(TSubclassOf<AActor> ActorClass, FTransform InstanceTransform, ULevel* Level , const FGameplayTagContainer& AdditionalInstanceTags = FGameplayTagContainer());` — Adds an instance of ActorClass at InstanceTransform location by spawning or reusing a AInstancedActorsManager at InstanceTransform's grid cell location. @param AdditionalInstanceTags Gameplay tags that will get appended to class-based FInstancedActorsSettings::GameplayTags @see UInstancedActorsProjectSettings::GridSize
- L62 _public prototype_ `FInstancedActorsInstanceHandle InstanceActor(TSubclassOf<AActor> ActorClass, FTransform InstanceTransform, ULevel* Level , const FGameplayTagContainer& AdditionalInstanceTags, TSubclassOf<AInstancedActorsManager> ManagerClass);` — `UFUNCTION(BlueprintCallable, Category = InstancedActors)` — Adds an instance of ActorClass at InstanceTransform location by spawning or reusing a AInstancedActorsManager at InstanceTransform's grid cell location. * @param AdditionalInstanceTags Gameplay tags that will get appended to class-based FInstancedActorsSettings::GameplayTags @see UInstancedActorsProjectSettings::GridSize
- L77 _public prototype_ `bool RemoveActorInstance(const FInstancedActorsInstanceHandle& InstanceHandle, bool bDestroyManagerIfEmpty = true);` — `UFUNCTION(BlueprintCallable, Category = InstancedActors)` — Removes all instance data for InstanceHandle. This simply adds this instance to a FreeList which incurs extra cost to process at runtime before instance spawning. @param InstanceHandle         Instance to remove @param bDestroyManagerIfEmpty If true, and InstanceHandle is the last instance in its manager, destroy the now-empty manager. This implicitly clears the FreeList which is stored per-manager. Any subsequent instance adds will then create a fresh manager. @see IA.CompactInstances console command
- L80 _public prototype_ `void ForEachManager(const FBox& QueryBounds, TFunctionRef<bool(AInstancedActorsManager&)> InOperation , TSubclassOf<AInstancedActorsManager> ManagerClass = AInstancedActorsManager::StaticClass()) const;`
- L82 _public prototype_ `void ForEachModifierVolume(const FBox& QueryBounds, TFunctionRef<bool(UInstancedActorsModifierVolumeComponent&)> InOperation) const;`
- L83 _public prototype_ `void ForEachInstance(const FBox& QueryBounds, TFunctionRef<bool(const FInstancedActorsInstanceHandle& , const FTransform&, FInstancedActorsIterationContext&)> InOperation) const;`
- L94 _public prototype_ `bool HasInstancesOfClass(const FBox& QueryBounds, TSubclassOf<AActor> ActorClass, const bool bTestActorsIfSpawned = false , const EInstancedActorsBulkLODMask AllowedLODs = EInstancedActorsBulkLODMask::All) const;` — Checks whether there are any instanced actors representing ActorClass or its subclasses inside QueryBounds. The check doesn't differentiate between hydrated and dehydrated actors (i.e. whether there's an actor instance associated with the instance or not). @param bTestActorsIfSpawned if true then when an instance is found to overlap given bounds, and it has an actor spawned associated with it, then the actor itself will be tested against the bounds for more precise test. @param AllowedLODs if provided will be used to filter out InstancedActorData that are at LOD not matching the flags in AllowedLODs
- L97 _public prototype_ `FInstancedActorsManagerHandle AddManager(AInstancedActorsManager& Manager);`
- L98 _public prototype_ `void RemoveManager(FInstancedActorsManagerHandle ManagerHandle);`
- L100 _public prototype_ `FInstancedActorsModifierVolumeHandle AddModifierVolume(UInstancedActorsModifierVolumeComponent& ModifierVolume);`
- L101 _public prototype_ `void RemoveModifierVolume(FInstancedActorsModifierVolumeHandle ModifierVolumeHandle);`
- L104 _public prototype_ `void RequestDeferredSpawnEntities(FInstancedActorsManagerHandle ManagerHandle);` — Adds ManagerHandle to PendingManagersToSpawnEntities for later processing in Tick -> ExecutePendingDeferredSpawnEntitiesRequests
- L111 _public prototype_ `bool CancelDeferredSpawnEntitiesRequest(FInstancedActorsManagerHandle ManagerHandle);` — Removes ManagerHandle from PendingManagersToSpawnEntities if present @return	true if ManagerHandle was present in PendingManagersToSpawnEntities and subsequently removed. False otherwise (list is empty or didn't contain ManagerHandle)
- L119 _public prototype_ `bool ExecutePendingDeferredSpawnEntitiesRequests(double StopAfterSeconds = INFINITY);` — Calls AInstancedActorsManager::InitializeModifyAndSpawnEntities for all pending managers in PendingManagersToSpawnEntities added via RequestDeferredSpawnEntities. @param	StopAfterSeconds	If < INFINITY, requests processing will stop after this time, leaving remaining requests for the next ExecutePendingDeferredSpawnEntitiesRequests to continue.
- L122 _public prototype_ `bool HasPendingDeferredSpawnEntitiesRequests() const;` — Return true if any deferred spawn entities requests are pending execution by the next ExecutePendingDeferredSpawnEntitiesRequests
- L132 _public prototype_ `TSharedRef<UE::InstancedActors::FExemplarActorData> GetOrCreateExemplarActor(TSubclassOf<AActor> ActorClass);` — Retrieves existing or spawns a new ActorClass for introspecting exemplary instance data. Actors are spawned into ExemplarActorWorld, a separated 'inactive' UWorld, to ensure no conflict or modifications in the main game world. These 'exemplar' actors are fully constructed, including BP construction scripts up to (but not including) BeginPlay.
- L137 _public prototype_ `void UnregisterExemplarActorClass(TSubclassOf<AActor> ActorClass);` — Removes exemplar actor class from the map
- L148 _public prototype_ `FSharedStruct GetOrCompileSettingsForActorClass(TSubclassOf<AActor> ActorClass);` — Compiles and caches finalized settings for ActorClass based off FInstancedActorsClassSettingsBase found in UInstancedActorsProjectSettings::ActorClassSettingsRegistryType data registry, for ActorClass and it's inherited super classes. Note: FInstancedActorsClassSettingsBase are indexed by class FName (*not* the full path) in the data registry, for quick lookup in CompileSettingsForActorClass. This means unique class names must be used for per-class settings.
- L158 _public prototype_ `bool DoesActorClassHaveRegisteredSettings(TSubclassOf<AActor> ActorClass, bool bIncludeSuperClasses = true);` — Returns true if ActorClass has a matching FInstancedActorsClassSettingsBase entry in UInstancedActorsProjectSettings::ActorClassSettingsRegistryType data registry. Note: This relies on the registry being loaded at the time of calling i.e: in editor the registry must be set to preload in editor. @param bIncludeSuperClasses	If true and ActorClass doesn't have a direct entry in ActorClassSettingsRegistryType, ActorClass's super classes will be successively tried instead.
- L166 _public prototype_ `void MarkInstanceRepresentationDirty(FInstancedActorsInstanceHandle InstanceHandle);` — Adds InstanceHandle to a list of pending instances that require an explicit representation update e.g: to remove/add ISMCs when a replicated actor is spawned / despawned. This ensures their representation is updated even if the are currently in a non-detailed bulk LOD. @see UInstancedActorsStationaryLODBatchProcessor
- L174 _public prototype_ `void PopAllDirtyRepresentationInstances(TArray<FInstancedActorsInstanceHandle>& OutInstances);` — Copies the current list of instances requiring explicit representation updates (added via MarkInstanceRepresentationDirty) to OutInstances and clears the internal list. This 'consumes' these pending instances with the assumption they will then receive a representation update by the calling code. @see MarkInstanceRepresentationDirty, UInstancedActorsStationaryLODBatchProcessor
- L176 _public prototype_ `virtual FInstancedActorsVisualizationDesc CreateVisualDescriptionFromActor(const AActor& ExemplarActor) const;`
- L180 _public function_ `virtual void ModifyVisualDescriptionForActor(const TNotNull<AActor*> ExemplarActor, FInstancedActorsVisualizationDesc& InOutVisualization) const` — Called when an additional/alternate VisualizationDesc is registered. Override to make custom modifications to the visual representation
- L183 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L184 _public prototype_ `virtual TStatId GetStatId() const override;`
- L188 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L189 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L190 _public prototype_ `virtual void Deinitialize() override;`
- L204 _public prototype_ `TArray<UInstancedActorsSubsystem::FNextTickSharedFragment>& GetTickableSharedFragments();`
- L205 _public prototype_ `void UpdateAndResetTickTime(TConstStructView<FInstancedActorsDataSharedFragment> InstancedActorsDataSharedFragment);`
- L207 _public function_ `TSubclassOf<AInstancedActorsManager> GetInstancedActorsManagerClass() const`
- L216 _public prototype_ `void MarkIADDirtyWithEntitiesPendingDestruction(UInstancedActorsData& InstancedActorsData);` — Adds InstancedActorsData to a list of pending IAD which contains entities that should be destroyed @see UInstancedActorsRuntimeRemovalProcessor, UInstancedActorsData::RuntimeRemoveInstances
- L223 _public prototype_ `void PopAllDirtyIADWithEntitiesPendingDestruction(TArray<TWeakObjectPtr<UInstancedActorsData>>& OutInstancedActorsData);` — Moves the current list of IAD with entities pending destruction (added via MarkIadDirtyWithEntitiesPendingDestruction) to OutInstancedActorsData and clears the internal list. This 'consumes' these pending IAD with the assumption the entities pending destruction it contains will get destroyed by next command flush. @see UInstancedActorsRuntimeRemovalProcessor, UInstancedActorsData::RuntimeRemoveInstances
- L224 _public function_ `bool ContainsDirtyIADWithEntitiesPendingDestruction() const`
- L236 _protected prototype_ `bool RegisterNewSharedFragmentsInternal(TConstStructView<FInstancedActorsDataSharedFragment> InstancedActorsDataSharedFragment = TConstStructView<FInstancedActorsDataSharedFragment>());` — Fetches all registered FInstancedActorsDataSharedFragment from the EntityManager and adds the missing ones to SortedSharedFragments @param InstancedActorsDataSharedFragment optionally the function can check if given shared fragment is amongst the newly added fragments @param returns whether InstancedActorsDataSharedFragment has been found, or `true` if that param is not provided.
- L239 _protected member_ `TArray<FNextTickSharedFragment> SortedSharedFragments;` — The container storing a sorted queue of FSharedStruct instances, ordered by the NextTickTime
- L241 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L244 _protected member_ `TObjectPtr<const UInstancedActorsProjectSettings> ProjectSettings;` — `UPROPERTY(Transient)`
- L247 _protected member_ `TObjectPtr<const UDataRegistrySubsystem> DataRegistrySubsystem;` — `UPROPERTY(Transient)`
- L250 _protected member_ `TObjectPtr<UActorPartitionSubsystem> ActorPartitionSubsystem;` — `UPROPERTY(Transient)`
- L253 _protected member_ `TSubclassOf<AInstancedActorsManager> InstancedActorsManagerClass;` — `UPROPERTY()`
- L258 _protected member_ `TSparseArray<TWeakObjectPtr<AInstancedActorsManager>> Managers;` — Spatially indexed managers. TSparseArray used for stable indices which can be spatially indexed by THierarchicalHashGrid2D @todo Managers should be indexable by cell coord hashes within their levels, we could leverage this for more efficient spatial indexing by keeping a cellcoord hash map per tile
- L259 _protected typedef_ `using FManagersHashGridType = THierarchicalHashGrid2D< 3, 4, FInstancedActorsManagerHandle>;`
- L260 _protected member_ `FManagersHashGridType ManagersHashGrid;`
- L263 _protected member_ `TSparseArray<TWeakObjectPtr<UInstancedActorsModifierVolumeComponent>> ModifierVolumes;` — Spatially indexed modifier volumes. TSparseArray used for stable indices which can be spatially indexed by THierarchicalHashGrid2D
- L264 _protected typedef_ `using FModifierVolumesHashGridType = THierarchicalHashGrid2D< 3, 4, FInstancedActorsModifierVolumeHandle>;`
- L265 _protected member_ `FModifierVolumesHashGridType ModifierVolumesHashGrid;`
- L268 _protected member_ `TArray<FInstancedActorsManagerHandle> PendingManagersToSpawnEntities;` — FIFO queue of Managers pending deferred entity spawning in Tick. Enqueued in RequestDeferredSpawnEntities
- L272 _protected member_ `TArray<FInstancedActorsInstanceHandle> DirtyRepresentationInstances;` — Instances whose representation is explicitly dirty, e.g: due to actor spawn / despawn replication, requiring immediate representation processing even out of 'detailed' representation processing range.
- L274 _protected member_ `mutable FCriticalSection DirtyIadWithEntitiesPendingDestructionCS;`
- L275 _protected member_ `TArray<TWeakObjectPtr<UInstancedActorsData>> DirtyIadWithEntitiesPendingDestruction;`
- L278 _protected member_ `TMap<TObjectKey<AInstancedActorsManager>, FBox> DebugManagerBounds;`
- L279 _protected member_ `TMap<TObjectKey<UInstancedActorsModifierVolumeComponent>, FBox> DebugModifierVolumeBounds;`
- L284 _protected member_ `TMap<TWeakObjectPtr<UClass>, FSharedStruct> PerActorClassSettings;` — Cached finalized / flattened FInstancedActorsClassSettingsBase for GetOrCompileSettingsForActorClass requested ActorClass. Built via CompileSettingsForActorClass and cached in GetOrCompileSettingsForActorClass
- L289 _protected prototype_ `FSharedStruct CompileSettingsForActorClass(TSubclassOf<AActor> ActorClass) const;` — Called in GetOrCompileSettingsForActorClass to compile finalized settings for ActorClass based off FInstancedActorsClassSettingsBase found in UInstancedActorsProjectSettings::ActorClassSettingsRegistryType data registry, for ActorClass and it's inherited super classes.
- L292 _protected prototype_ `void HandleRefreshSettings(IConsoleVariable* InCVar);`
- L298 _protected member_ `TObjectPtr<UWorld> ExemplarActorWorld;` — `UPROPERTY(Transient)` — Inactive UWorld housing lazily create exemplar actors for instance actor classes @see GetOrCreateExemplarActor
- L302 _protected member_ `TMap<TObjectKey<const UClass>, TWeakPtr<UE::InstancedActors::FExemplarActorData>> ExemplarActors;` — Lazily created exemplar actors for instance actor classes @see GetOrCreateExemplarActor
- L305 _protected member_ `TObjectPtr<const UScriptStruct> SettingsType;` — `UPROPERTY(Transient)`

#### struct `UInstancedActorsSubsystem::FNextTickSharedFragment`  
`struct FNextTickSharedFragment`  
_L193-202_
- L195 _public member_ `FSharedStruct SharedStruct;`
- L196 _public member_ `double NextTickTime = 0;`
- L198 _public function_ `bool operator<(const FNextTickSharedFragment& Other) const`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace InstancedActors` (scope `UE`)

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsTypes.h` (Public)


#### enum `EInstancedActorsBulkLOD`  
`enum class EInstancedActorsBulkLOD : uint8`  
_L29-36_
- L31 _public enumerator_ `Detailed` — this will make Mass calculate LOD individually for every instance
- L32 _public enumerator_ `Medium`
- L33 _public enumerator_ `Low`
- L34 _public enumerator_ `Off`
- L35 _public enumerator_ `MAX`

#### enum `EInstancedActorsBulkLODMask`  
`enum class EInstancedActorsBulkLODMask : uint8`  
_L38-49_
- L40 _public enumerator_ `None = 0`
- L42 _public enumerator_ `Detailed = 1 << int(EInstancedActorsBulkLOD::Detailed)`
- L43 _public enumerator_ `Medium = 1 << int(EInstancedActorsBulkLOD::Medium)`
- L44 _public enumerator_ `Low = 1 << int(EInstancedActorsBulkLOD::Low)`
- L45 _public enumerator_ `Off = 1 << int(EInstancedActorsBulkLOD::Off)`
- L47 _public enumerator_ `NotDetailed = Medium | Low | Off`
- L48 _public enumerator_ `All = 0xFF`

#### enum `EInstancedActorsFragmentFlags`  
`enum class EInstancedActorsFragmentFlags : uint8`  
_L51-59_
- L53 _public enumerator_ `None = 0`
- L55 _public enumerator_ `Replicated = 1 << 0`
- L56 _public enumerator_ `Persisted = 1 << 1`
- L58 _public enumerator_ `All = 0xFF`

#### struct `FInstancedActorsTagSet`  
`struct FInstancedActorsTagSet`  
_L78-122_
- reflection: `USTRUCT(BlueprintType)`
- desc: An immutable hashed tag container used to categorize / partition instances
- L82 _public prototype_ `FInstancedActorsTagSet() = default;`
- L83 _public prototype_ `FInstancedActorsTagSet(const FGameplayTagContainer& InTags);`
- L85 _public function_ `bool IsEmpty() const`
- L87 _public function_ `const FGameplayTagContainer& GetTags() const`
- L89 _public prototype_ `void CalcHash();`
- L91 _public function_ `bool operator==(const FInstancedActorsTagSet& OtherTagSet) const`
- L118 _private member_ `FGameplayTagContainer Tags;` — `UPROPERTY(VisibleAnywhere, Category=InstancedActors)`
- L121 _private member_ `TOptional<uint32> Hash;` — `UPROPERTY(Transient)`

#### struct `FInstancedActorsVisualizationDesc`  
`struct FInstancedActorsVisualizationDesc`  
_L130-175_
- reflection: `USTRUCT()`
- desc: ISMC descriptions for instances 'visualization', allowing instances to define multiple potential visualizations / ISMC sets: e.g: 'with berries', 'without berries'.
- L134 _public prototype_ `FInstancedActorsVisualizationDesc() = default;`
- L135 _public prototype_ `explicit FInstancedActorsVisualizationDesc(const FInstancedActorsSoftVisualizationDesc& SoftVisualizationDesc);`
- L143 _public member_ `TArray<FISMComponentDescriptor> ISMComponentDescriptors;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)` — Array of Instanced Static Mesh Component descriptors. An ISMC will be created for each of these, using the specified mesh, material, collision settings etc. Instanced Actors using this visualization will add an instance to each of these, allowing for composite mesh visualizations for a single actor instance e.g: a car with separate body and wheel meshes all instanced together.
- L146 _public member_ `TArray<float> CustomDataFloats;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)`
- L148 _public typedef_ `using FAdditionalSetupStepsFunction = TFunctionRef<void(const AActor& , FISMComponentDescriptor& , FInstancedActorsVisualizationDesc& )>;`
- L149 _public typedef_ `using FVisualizationDescSetupFunction = TFunctionRef<void(const AActor& , FInstancedActorsVisualizationDesc& )>;`
- L152 _public prototype_ `static FInstancedActorsVisualizationDesc FromActor(const AActor& ExemplarActor, const FAdditionalSetupStepsFunction& AdditionalSetupSteps);` — `UE_DEPRECATED(5.6, "Using FAdditionalSetupStepsFunction which takes a FISMComponentDescriptor& parameter is deprecated. Use FVisualizationDescSetupFunction instead, since FInstancedActorsVisualizationDesc already contains the built TArray of FISMComponentDescriptor")`
- L162 _public function_ `static FInstancedActorsVisualizationDesc FromActor(const AActor& ExemplarActor, const FVisualizationDescSetupFunction& AdditionalSetupFunction = [](const AActor& , FInstancedActorsVisualizationDesc& ){});` — Helper function to deduce appropriate instanced static mesh representation for an ActorClass exemplar actor. @param ExemplarActor A fully constructed exemplar actor, including BP construction scripts up to (but not including) BeginPlay. @param AdditionalSetupFunction function called once a new ISMComponentDescriptor is created, allowing custom code to perform additional set up steps. Note that this function will get called only if ExemplarActor has a StaticMeshComponent with a valid StaticMesh configured. @see UInstancedActorsSubsystem::GetOrCreateExemplarActor
- L162 _public prototype_ `static FInstancedActorsVisualizationDesc FromActor(const AActor& ExemplarActor, const FVisualizationDescSetupFunction& AdditionalSetupFunction = [](const AActor& , FInstancedActorsVisualizationDesc& ){});` — Helper function to deduce appropriate instanced static mesh representation for an ActorClass exemplar actor. @param ExemplarActor A fully constructed exemplar actor, including BP construction scripts up to (but not including) BeginPlay. @param AdditionalSetupFunction function called once a new ISMComponentDescriptor is created, allowing custom code to perform additional set up steps. Note that this function will get called only if ExemplarActor has a StaticMeshComponent with a valid StaticMesh configured. @see UInstancedActorsSubsystem::GetOrCreateExemplarActor
- L164 _public prototype_ `FStaticMeshInstanceVisualizationDesc ToMassVisualizationDesc() const;`

#### struct `FInstancedActorsSoftVisualizationDesc`  
`struct FInstancedActorsSoftVisualizationDesc`  
_L182-198_
- reflection: `USTRUCT()`
- desc: Soft-ptr variant of FInstancedActorsVisualizationDesc for defining visualization assets to async load.
- L186 _public prototype_ `FInstancedActorsSoftVisualizationDesc() = default;`
- L187 _public prototype_ `explicit FInstancedActorsSoftVisualizationDesc(const FInstancedActorsVisualizationDesc& VisualizationDesc);`
- L195 _public member_ `TArray<FSoftISMComponentDescriptor> ISMComponentDescriptors;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)` — Array of Instanced Static Mesh Component descriptors. An ISMC will be created for each of these, using the specified mesh, material, collision settings etc. Instanced Actors using this visualization will add an instance to each of these, allowing for composite mesh visualizations for a single actor instance e.g: a car with separate body and wheel meshes all instanced together.
- L197 _public prototype_ `void GetAssetsToLoad(TArray<FSoftObjectPath>& OutAssetsToLoad) const;`

#### struct `FInstancedActorsVisualizationInfo`  
`struct FInstancedActorsVisualizationInfo`  
_L203-251_
- reflection: `USTRUCT()`
- desc: Runtime ISMC tracking for a given 'visualization' (alternate ISMC set) for instances
- L212 _public function_ `inline bool IsAsyncLoading() const` — Returns true if this visualization was added view UInstancedActorsData::AddVisualizationAsync and streaming is still in-progress. Once streaming completes, Desc, ISMComponents and MassStaticMeshDescIndex will be valid and this returns false. Note: Until streaming completes, Desc, ISMComponents & MassStaticMeshDescIndex will all be defayult values / unset.
- L221 _public member_ `FInstancedActorsVisualizationDesc VisualizationDesc;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)` — Cached specification for this visualization, defining ISMCs to create. Note: For visualizations added via UInstancedActorsData::AddVisualizationAsync using an FInstancedActorsSoftVisualizationDesc soft pointer descriptor: whilst IsAsyncLoading() = true, this will be default constructed. Once the async load completes, the soft visualization decriptor will then be resolved to this hard pointer decriptor.
- L229 _public member_ `TArray<TObjectPtr<UInstancedStaticMeshComponent>> ISMComponents;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)` — Instanced Static Mesh Components created from VisualizationDesc.ISMComponentDescriptors specs. Note: If IsAsyncLoading() = true, this will be empty until the load completes and ISMCs are created.
- L238 _public member_ `FStaticMeshInstanceVisualizationDescHandle MassStaticMeshDescHandle;` — `UPROPERTY(VisibleAnywhere, Category = InstancedActors)` — Handle to registration of ISMComponents with UMassRepresentationSubsystem via UMassRepresentationSubsystem::AddVisualDescWithISMComponents. Note: If IsAsyncLoading() = true, this will be invalid until the load completes and ISMCs are created and registered.
- L242 _public member_ `TSharedPtr<FStreamableHandle> AssetLoadHandle;` — If this visualization was added with UInstancedActorsData::AddVisualizationAsync, this will be set to the async streaming request until streaming is complete, whereupon this handle is cleared.
- L245 _public member_ `mutable uint16 CachedTouchCounter = 0;` — Used to track version of data used to create CollisionIndexToEntityIndexMap
- L250 _public member_ `mutable TArray<int32> CollisionIndexToEntityIndexMap;` — Valid as long as Mass visualization data indicated by MassStaticMeshDescIndex has ComponentInstanceIdTouchCounter equal to CachedTouchCounter.

#### struct `FInstancedActorsMeshSwitchFragment`  
`struct FInstancedActorsMeshSwitchFragment : public FMassFragment`  
_L255-268_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L262 _public member_ `FStaticMeshInstanceVisualizationDescHandle NewStaticMeshDescHandle;` — `UPROPERTY()` — The pending Mass static mesh representation index we want to switch to. @see UInstancedActorsVisualizationSwitcherProcessor
- L267 _public member_ `FSkinnedMeshInstanceVisualizationDescHandle NewSkinnedMeshDescHandle;` — `UPROPERTY()` — The pending Mass skinned mesh representation index we want to switch to. @see UInstancedActorsVisualizationSwitcherProcessor

#### struct `FInstancedActorsManagerHandle`  
`struct FInstancedActorsManagerHandle`  
_L272-302_
- reflection: `USTRUCT(BlueprintType)`
- L278 _public prototype_ `FInstancedActorsManagerHandle() = default;`
- L279 _public function_ `FInstancedActorsManagerHandle(const int32 InManagerID) : ManagerID(InManagerID)`
- L281 _public function_ `inline bool IsValid() const`
- L286 _public function_ `inline void Reset()`
- L291 _public function_ `int32 GetManagerID() const`
- L296 _public prototype_ `bool operator==(const FInstancedActorsManagerHandle&) const = default;`
- L301 _private member_ `int32 ManagerID = INDEX_NONE;` — `UPROPERTY(Transient)`

#### struct `FInstancedActorsModifierVolumeHandle`  
`struct FInstancedActorsModifierVolumeHandle`  
_L305-325_
- reflection: `USTRUCT(BlueprintType)`
- L311 _public prototype_ `FInstancedActorsModifierVolumeHandle() = default;`
- L312 _public function_ `FInstancedActorsModifierVolumeHandle(const int32 InModifierVolumeID) : ModifierVolumeID(InModifierVolumeID)`
- L314 _public function_ `int32 GetModifierVolumeID() const`
- L319 _public prototype_ `bool operator==(const FInstancedActorsModifierVolumeHandle&) const = default;`
- L324 _private member_ `int32 ModifierVolumeID = INDEX_NONE;` — `UPROPERTY(Transient)`

#### struct `FInstancedActorsDataSharedFragment`  
`struct FInstancedActorsDataSharedFragment : public FMassSharedFragment`  
_L333-346_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- desc: Note that we don't really need this type to be a shared fragment. It's used to create FSharedStructs pointing at UInstancedActorsData and this data is fetched from MassEntityManager by UInstancedActorsStationaryLODBatchProcessor. @todo This will be addressed in the future by refactoring where this data is stored and how it's used.
- L338 _public member_ `TWeakObjectPtr<UInstancedActorsData> InstanceData;` — `UPROPERTY(Transient)`
- L340 _public member_ `EInstancedActorsBulkLOD BulkLOD = EInstancedActorsBulkLOD::MAX;`
- L343 _public member_ `bool bInstancedActorsDataDespawnedEntities = false;` — Set to true when the IAD has despawned its entities
- L345 _public member_ `double LastTickTime = 0.0;`

#### struct `FInstancedActorsFragment`  
`struct FInstancedActorsFragment : public FMassFragment`  
_L349-360_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L355 _public member_ `TWeakObjectPtr<UInstancedActorsData> InstanceData;` — `UPROPERTY(Transient)` — InstancedActorData owning the given entity
- L359 _public member_ `FInstancedActorsInstanceIndex InstanceIndex;` — `UPROPERTY()` — The fixed index of this 'instance' into InstanceData

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INSTANCEDACTORS_API`
- L60 _prototype_ `ENUM_CLASS_FLAGS(EInstancedActorsFragmentFlags);`
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace InstancedActors` (scope `UE`)
- L62 _namespace_ `namespace Utils` (scope `UE::InstancedActors`)
- L64 _prototype_ `TSubclassOf<UMassActorSpawnerSubsystem> DetermineActorSpawnerSubsystemClass(const UWorld& World);` (scope `UE::InstancedActors::Utils`)
- L65 _prototype_ `UServerInstancedActorsSpawnerSubsystem* GetServerInstancedActorsSpawnerSubsystem(const UWorld& World);` (scope `UE::InstancedActors::Utils`)
- L66 _prototype_ `UClientInstancedActorsSpawnerSubsystem* GetClientInstancedActorsSpawnerSubsystem(const UWorld& World);` (scope `UE::InstancedActors::Utils`)
- L71 _prototype_ `UMassActorSpawnerSubsystem* GetActorSpawnerSubsystem(const UWorld& World);` (scope `UE::InstancedActors::Utils`) — Calls either GetServerInstancedActorsSpawnerSubsystem or GetClientInstancedActorsSpawnerSubsystem, depending on given UWorld's net mode.
- L72 _prototype_ `UInstancedActorsSubsystem* GetInstancedActorsSubsystem(const UWorld& World);` (scope `UE::InstancedActors::Utils`)
- L166 _function_ `friend inline uint32 GetTypeHash(const FInstancedActorsVisualizationDesc& InDesc)`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsVisualizationProcessor.h` (Public)


#### struct `FInstancedActorsVisualizationProcessorTag`  
`struct FInstancedActorsVisualizationProcessorTag : public FMassTag`  
_L14-17_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag required by Instanced Actors Visualization Processor to process given archetype. Removing the tag allows to support disabling of processing for individual entities of given archetype.

#### class `UInstancedActorsVisualizationProcessor`  
`class UInstancedActorsVisualizationProcessor : public UMassVisualizationProcessor`  
_L20-27_
- reflection: `UCLASS()`
- inherits: `UMassVisualizationProcessor`
- L25 _protected prototype_ `UInstancedActorsVisualizationProcessor();`
- L26 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsVisualizationSwitcherProcessor.h` (Public)


#### class `UInstancedActorsVisualizationSwitcherProcessor`  
`class UInstancedActorsVisualizationSwitcherProcessor : public UMassProcessor`  
_L19-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Executes on entities with FInstancedActorsMeshSwitchFragment's, processing them as `pending requests` to switch to the specified NewStaticMeshDescHandle, then removing the fragments once complete
- L24 _public prototype_ `UInstancedActorsVisualizationSwitcherProcessor();`
- L29 _public prototype_ `static void SwitchEntityMeshDesc(FMassInstancedStaticMeshInfoArrayView& ISMInfosView, FMassRepresentationFragment& RepresentationFragment, FMassEntityHandle EntityHandle, FStaticMeshInstanceVisualizationDescHandle NewStaticMeshDescHandle);` — Switch EntityHandle to NewStaticMeshDescHandle by removing any current / previous ISMC instances for the current StaticMeshDescIHandle and setting RepresentationFragment.PrevRepresentation = EMassRepresentationType::None to let the subsequent UMassStationaryISMSwitcherProcessor see that a new instance needs to be added for the now set NewStaticMeshDescHandle
- L34 _public prototype_ `static void SwitchEntitySkinnedMeshDesc(FMassInstancedSkinnedMeshInfoArrayView& MeshInfosView, FMassRepresentationFragment& RepresentationFragment, FMassEntityHandle EntityHandle, FSkinnedMeshInstanceVisualizationDescHandle NewMeshDescHandle);` — Switch EntityHandle to NewMeshDescHandle by removing any current / previous ISMC instances for the current MeshDescIHandle and setting RepresentationFragment.PrevRepresentation = EMassRepresentationType::None to let the subsequent UMassStationaryISMSwitcherProcessor see that a new instance needs to be added for the now set NewMeshDescHandle
- L36 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L37 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L39 _protected member_ `FMassEntityQuery EntityQuery;`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsVisualizationTrait.h` (Public)


#### class `UInstancedActorsVisualizationTrait`  
`class UInstancedActorsVisualizationTrait : public UMassStationaryDistanceVisualizationTrait`  
_L20-38_
- reflection: `UCLASS(MinimalAPI, HideDropdown)`
- inherits: `UMassStationaryDistanceVisualizationTrait`
- desc: Subclass of UMassStationaryVisualizationTrait which forces required settings for instanced actor entities and overrides FMassRepresentationFragment.StaticMeshDescHandle to use a custom registered Visualization which reuses InstanceData's ISMComponents via UMassRepresentationSubsystem::AddVisualDescWithISMComponent. Note that the trait is marked to not show up in class selection drop-downs. The reason is that this trait is supposed to be used internally by InstancedActors and is never expected to be a part of a user-authored entity config.
- L26 _public prototype_ `UInstancedActorsVisualizationTrait(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L28 _public prototype_ `virtual void InitializeFromInstanceData(UInstancedActorsData& InInstanceData);`
- L31 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L37 _protected member_ `TWeakObjectPtr<UInstancedActorsData> InstanceData;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/ServerInstancedActorsSpawnerSubsystem.h` (Public)


#### class `UServerInstancedActorsSpawnerSubsystem`  
`class UServerInstancedActorsSpawnerSubsystem : public UMassActorSpawnerSubsystem`  
_L23-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassActorSpawnerSubsystem`
- desc: Dedicated UMassActorSpawnerSubsystem subclass handling server-side Actor spawning for InstancedActor. The main responsibility is InstancedActors-specific setup of newly spawned actors, including configuring UInstancedActorsComponent instanced a newly spawned actor hosts.
- L33 _public prototype_ `void OnInstancedActorComponentInitialize(UInstancedActorsComponent& InstancedActorComponent) const;` — Called by UInstancedActorsComponent::InitializeComponent to provide an opportunity, before BeginPlay, to catch Instanced Actors we're spawning, to set their FMassEntityHandle association.
- L38 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L39 _protected prototype_ `virtual void Deinitialize() override;`
- L40 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L41 _protected prototype_ `virtual bool ReleaseActorToPool(AActor* Actor) override;`
- L45 _protected prototype_ `virtual ESpawnRequestStatus SpawnActor(const FSpawnArgs& Args, FActorSpawnParameters& InOutSpawnParameters) const override;`
- L48 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L56 _protected member_ `mutable TObjectPtr<AActor> TransientActorBeingSpawned = nullptr;` — `UPROPERTY(Transient)` — Set during SpawnActor and cleared once complete, to 'catch' UInstancedActorComponents initializing during the actor spawn, matching their Owner to TransientActorBeingSpawned in OnInstancedActorComponentInitialize, to test if the component was 'spawned by Instanced Actors'. If so, we call UInstancedActorsComponent::InitializeComponentForInstance and pass along TransientActorSpawningEntity as the Mass entity 'owning' this spawned actor.
- L59 _protected member_ `mutable FInstancedActorsInstanceHandle TransientActorSpawningInstance;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INSTANCEDACTORS_API`
