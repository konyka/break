# Plugins / MassReplication

- module root: `Plugins/Runtime/MassGameplay/Source/MassReplication`
- headers: 14; symbols: 466
- symbol kinds: class=16, delegate=2, enum=3, enumerator=6, function=133, macro=22, member=106, namespace=11, prototype=117, struct=33, typedef=14, variable=3
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD, MassMovement, MassSimulation, MassSpawner, NetCore, ZoneGraph

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/IMassReplicationModule.h` (Public)


#### class `IMassReplicationModule`  
`class IMassReplicationModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassReplicationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassClientBubbleHandler.h` (Public)


#### struct `FMassFastArrayItemBase`  
`struct FMassFastArrayItemBase : public FFastArraySerializerItem`  
_L45-60_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializerItem`
- desc: Base for fast array items. For replication of new entity types this type should be inherited from. FReplicatedAgentBase should also be inherited from and made a member variable of the FMassFastArrayItemBase derived struct, with the member variable called Agent.
- L49 _public prototype_ `FMassFastArrayItemBase() = default;`
- L50 _public function_ `FMassFastArrayItemBase(FMassReplicatedAgentHandle InHandle) : Handle(InHandle)`
- L54 _public function_ `FMassReplicatedAgentHandle GetHandle() const`
- L59 _protected member_ `FMassReplicatedAgentHandle Handle;` — `UPROPERTY(NotReplicated)` — Only to be used on a server

#### struct `FMassAgentLookupData`  
`struct FMassAgentLookupData`  
_L63-86_
- desc: Data that can be accessed from a FMassReplicatedAgentHandle on a server
- L65 _public function_ `FMassAgentLookupData(FMassEntityHandle InEntity, FMassNetworkID InNetID, int32 InAgentsIdx) : Entity(InEntity) , NetID(InNetID) , AgentsIdx(InAgentsIdx)`
- L71 _public function_ `void Invalidate()`
- L78 _public function_ `bool IsValid() const`
- L83 _public member_ `FMassEntityHandle Entity;`
- L84 _public member_ `FMassNetworkID NetID;`
- L85 _public member_ `int32 AgentsIdx = INDEX_NONE;`

#### struct `FMassAgentRemoveData`  
`struct FMassAgentRemoveData`  
_L92-100_
- desc: Data that is stored when an agent is removed from the bubble, when it times out its safe enough to remove entries in EntityInfoMap. The idea is that any out of order adds and removes will happen after this time.
- L94 _public prototype_ `FMassAgentRemoveData() = default;`
- L95 _public function_ `FMassAgentRemoveData(double InTimeLastRemoved) : TimeLastRemoved(InTimeLastRemoved)`
- L99 _public member_ `double TimeLastRemoved = 0.;`

#### class `TClientBubbleHandlerBase`  
`template<typename AgentArrayItem> class TClientBubbleHandlerBase : public IClientBubbleHandlerInterface`  
_L108-240_
- inherits: `IClientBubbleHandlerInterface`
- desc: Template client bubble functionality. Replication logic for specific agent types is provided by deriving from this class. Interaction with the FMassClientBubbleSerializerBase and derived classes should be done from this class
- L111 _public typedef_ `typedef TFunctionRef<void(FMassEntityQuery&)> FAddRequirementsForSpawnQueryFunction;`
- L112 _public typedef_ `typedef TFunctionRef<void(FMassExecutionContext&)> FCacheFragmentViewsForSpawnQueryFunction;`
- L113 _public typedef_ `typedef TFunctionRef<void(const FMassEntityView&, const typename AgentArrayItem::FReplicatedAgentType&, const int32)> FSetSpawnedEntityDataFunction;`
- L114 _public typedef_ `typedef TFunctionRef<void(const FMassEntityView&, const typename AgentArrayItem::FReplicatedAgentType&)> FSetModifiedEntityDataFunction;`
- L117 _public prototype_ `virtual void Initialize(TArray<AgentArrayItem>& InAgents, FMassClientBubbleSerializerBase& InSerializer);` — This must be called from outside before InitializeForWorld() is called. Its called from agent specific bubble implementations
- L119 _public prototype_ `virtual void InitializeForWorld(UWorld& InWorld) override;`
- L120 _public prototype_ `UWorld* GetWorld() const;`
- L123 _public prototype_ `FMassReplicatedAgentHandle AddAgent(FMassEntityHandle Entity, typename AgentArrayItem::FReplicatedAgentType& Agent);`
- L125 _public prototype_ `bool RemoveAgent(FMassNetworkID NetID);`
- L126 _public prototype_ `bool RemoveAgent(FMassReplicatedAgentHandle AgentHandle);`
- L127 _public prototype_ `void RemoveAgentChecked(FMassReplicatedAgentHandle AgentHandle);`
- L128 _public prototype_ `void MarkItemDirty(FFastArraySerializerItem& Item) const;`
- L129 _public prototype_ `AgentArrayItem& GetAgentItem(const FMassReplicatedAgentHandle Handle) const;`
- L132 _public prototype_ `const typename AgentArrayItem::FReplicatedAgentType* GetAgent(FMassReplicatedAgentHandle Handle) const;` — Gets an agent safely
- L135 _public prototype_ `const typename AgentArrayItem::FReplicatedAgentType& GetAgentChecked(FMassReplicatedAgentHandle Handle) const;` — Faster version to get an agent that performs check()s for debugging
- L136 _public function_ `const TArray<AgentArrayItem>& GetAgents() const`
- L139 _public function_ `template<typename TReplicatedDataType> void SetBubbleData(const FMassReplicatedAgentHandle Handle, const TReplicatedDataType& NewData)`
- L160 _protected prototype_ `virtual void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize) override;`
- L179 _protected prototype_ `template<typename TEventHandlers> void PostReplicatedAddHelper(const TArrayView<int32> AddedIndices, TEventHandlers& EventHandlers);` — Called from TClientBubbleHandlerBase derived classes in PostReplicatedAd()
- L181 _protected prototype_ `void PostReplicatedAddHelper(const TArrayView<int32> AddedIndices, FAddRequirementsForSpawnQueryFunction AddRequirementsForSpawnQuery , FCacheFragmentViewsForSpawnQueryFunction CacheFragmentViewsForSpawnQuery, FSetSpawnedEntityDataFunction SetSpawnedEntityData, FSetModifiedEntityDataFunction SetModifiedEntityData);`
- L186 _protected prototype_ `template<typename TEventHandlers> void PostReplicatedAddEntitiesHelper(const TArrayView<int32> AddedIndices, TEventHandlers& EventHandlers);` — used by PostReplicatedAddHelper
- L188 _protected prototype_ `void PostReplicatedAddEntitiesHelper(const TArrayView<int32> AddedIndices, FAddRequirementsForSpawnQueryFunction AddRequirementsForSpawnQuery , FCacheFragmentViewsForSpawnQueryFunction CacheFragmentViewsForSpawnQuery, FSetSpawnedEntityDataFunction SetSpawnedEntityData);`
- L193 _protected prototype_ `void PostReplicatedChangeHelper(const TArrayView<int32> ChangedIndices, FSetModifiedEntityDataFunction SetModifiedEntityData);` — Called from TClientBubbleHandlerBase derived classes in PostReplicatedChange()
- L197 _protected prototype_ `template<typename TEventHandlers> requires (!UE::Mass::Replication::TIsCallable<TEventHandlers>) void PostReplicatedChangeHelper(const TArrayView<int32> ChangedIndices, TEventHandlers& HandlersPack);`
- L201 _protected prototype_ `void RemoveAgentImpl(FMassReplicatedAgentHandle Handle);`
- L204 _protected prototype_ `virtual void SetClientHandle(FMassClientHandle InClientHandle) override;`
- L206 _protected prototype_ `virtual void Reset() override;`
- L207 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L209 _protected prototype_ `virtual void UpdateAgentsToRemove() override;`
- L211 _protected prototype_ `virtual void DebugValidateBubbleOnClient() override;`
- L212 _protected prototype_ `virtual void DebugValidateBubbleOnServer() override;`
- L216 _protected member_ `TArray<AgentArrayItem>* Agents = nullptr;` — Pointer to the Agents array in the associated Serializer class
- L218 _protected member_ `FMassClientHandle ClientHandle;`
- L221 _protected member_ `FMassReplicatedAgentHandleManager AgentHandleManager;`
- L224 _protected member_ `TArray<FMassAgentLookupData> AgentLookupArray;` — Used to look up Agent data from a FMassReplicatedAgentHandle, the AgentsIdx member will be the Idx in to the Agents array
- L226 _protected member_ `TMap<FMassNetworkID, FMassReplicatedAgentHandle> NetworkIDToAgentHandleMap;`
- L235 _protected member_ `TMap<FMassNetworkID, FMassAgentRemoveData> AgentsRemoveDataMap;` — Data that is stored when an agent is removed from the bubble, when it times out its safe enough to remove entries in EntityInfoMap The idea is that any out of order adds and subsequent removes for this NetID will normally happen before FAgentRemoveData::TimeLastRemoved, Those that happen after will be on such a bad connection that it doest matter.
- L239 _protected member_ `FMassClientBubbleSerializerBase* Serializer = nullptr;` — Base class pointer to the associated Serializer class
- L243 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::Initialize(TArray<AgentArrayItem>& InAgents, FMassClientBubbleSerializerBase& InSerializer)`
- L251 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::InitializeForWorld(UWorld& InWorld)`
- L260 _function_ `template <typename AgentArrayItem> UWorld* TClientBubbleHandlerBase<AgentArrayItem>::GetWorld() const`
- L267 _function_ `template<typename AgentArrayItem> FMassReplicatedAgentHandle TClientBubbleHandlerBase<AgentArrayItem>::AddAgent(FMassEntityHandle Entity, typename AgentArrayItem::FReplicatedAgentType& Agent)`
- L298 _function_ `template<typename AgentArrayItem> bool TClientBubbleHandlerBase<AgentArrayItem>::RemoveAgent(FMassNetworkID NetID)`
- L306 _function_ `template<typename AgentArrayItem> bool TClientBubbleHandlerBase<AgentArrayItem>::RemoveAgent(FMassReplicatedAgentHandle AgentHandle)`
- L320 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::RemoveAgentChecked(FMassReplicatedAgentHandle Handle)`
- L327 _function_ `template <typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::MarkItemDirty(FFastArraySerializerItem& Item) const`
- L333 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::RemoveAgentImpl(FMassReplicatedAgentHandle Handle)`
- L361 _function_ `template <typename AgentArrayItem> AgentArrayItem& TClientBubbleHandlerBase<AgentArrayItem>::GetAgentItem(const FMassReplicatedAgentHandle Handle) const`
- L371 _function_ `template<typename AgentArrayItem> const typename AgentArrayItem::FReplicatedAgentType* TClientBubbleHandlerBase<AgentArrayItem>::GetAgent(FMassReplicatedAgentHandle Handle) const`
- L383 _function_ `template<typename AgentArrayItem> const typename AgentArrayItem::FReplicatedAgentType& TClientBubbleHandlerBase<AgentArrayItem>::GetAgentChecked(FMassReplicatedAgentHandle Handle) const`
- L393 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::UpdateAgentsToRemove()`
- L426 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)`
- L463 _function_ `template<typename AgentArrayItem> template<typename TEventHandlers> void TClientBubbleHandlerBase<AgentArrayItem>::PostReplicatedAddHelper(const TArrayView<int32> AddedIndices, TEventHandlers& EventHandlers)`
- L536 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::PostReplicatedAddHelper(const TArrayView<int32> AddedIndices, FAddRequirementsForSpawnQueryFunction AddRequirementsForSpawnQuery , FCacheFragmentViewsForSpawnQueryFunction CacheFragmentViewsForSpawnQuery, FSetSpawnedEntityDataFunction SetSpawnedEntityData, FSetModifiedEntityDataFunction SetModifiedEntityData)`
- L560 _function_ `template<typename AgentArrayItem> template<typename TEventHandlers> void TClientBubbleHandlerBase<AgentArrayItem>::PostReplicatedAddEntitiesHelper(const TArrayView<int32> AddedIndices, TEventHandlers& EventHandlers)`
- L635 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::PostReplicatedAddEntitiesHelper(const TArrayView<int32> AddedIndices, FAddRequirementsForSpawnQueryFunction AddRequirementsForSpawnQuery , FCacheFragmentViewsForSpawnQueryFunction CacheFragmentViewsForSpawnQuery, FSetSpawnedEntityDataFunction SetSpawnedEntityData)`
- L658 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::PostReplicatedChangeHelper(const TArrayView<int32> ChangedIndices, FSetModifiedEntityDataFunction SetModifiedEntityData)`
- L687 _function_ `template<typename AgentArrayItem> template<typename TEventHandlers> requires (!UE::Mass::Replication::TIsCallable<TEventHandlers>) void TClientBubbleHandlerBase<AgentArrayItem>::PostReplicatedChangeHelper(const TArrayView<int32> ChangedIndices, TEventHandlers& HandlersPack)`
- L715 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::SetClientHandle(FMassClientHandle InClientHandle)`
- L721 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::Reset()`
- L733 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::Tick(float DeltaTime)`
- L753 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::DebugValidateBubbleOnClient()`
- L813 _function_ `template<typename AgentArrayItem> void TClientBubbleHandlerBase<AgentArrayItem>::DebugValidateBubbleOnServer()`

#### struct `TClientBubbleHandlerBase::PostReplicatedAddHelper::FEventHandlers`  
`struct FEventHandlers : UE::Mass::Replication::TCachedSpawnQuery<FEventHandlers>`  
_L539-546_
- inherits: `UE::Mass::Replication::TCachedSpawnQuery<FEventHandlers>`
- L542 _public member_ `FAddRequirementsForSpawnQueryFunction AddRequirementsForSpawnQuery;`
- L543 _public member_ `FCacheFragmentViewsForSpawnQueryFunction CacheFragmentViewsForSpawnQuery;`
- L544 _public member_ `FSetSpawnedEntityDataFunction SetSpawnedEntityData;`
- L545 _public member_ `FSetModifiedEntityDataFunction SetModifiedEntityData;`

#### struct `TClientBubbleHandlerBase::PostReplicatedAddEntitiesHelper::FEventHandlers`  
`struct FEventHandlers : UE::Mass::Replication::TCachedSpawnQuery<FEventHandlers>`  
_L638-644_
- inherits: `UE::Mass::Replication::TCachedSpawnQuery<FEventHandlers>`
- L641 _public member_ `FAddRequirementsForSpawnQueryFunction AddRequirementsForSpawnQuery;`
- L642 _public member_ `FCacheFragmentViewsForSpawnQueryFunction CacheFragmentViewsForSpawnQuery;`
- L643 _public member_ `FSetSpawnedEntityDataFunction SetSpawnedEntityData;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Mass` (scope `UE`)
- L28 _namespace_ `namespace Replication` (scope `UE::Mass`)
- L30 _variable_ `constexpr float AgentRemoveInterval = 5.f;` (scope `UE::Mass::Replication`)
- L610 _function_ `` (scope `TClientBubbleHandlerBase::PostReplicatedAddEntitiesHelper`)

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassClientBubbleHandlerInterface.h` (Public)


#### class `IClientBubbleHandlerInterface`  
`class IClientBubbleHandlerInterface`  
_L16-38_
- desc: Interface for the bubble handler classes. All the outside interaction with the FastArray logic should be done via the Handler interface or derived classes where possible. These virtual functions are either only called once each per frame on the client for a few struct instances or called at startup / shutdown.
- L19 _public prototype_ `virtual ~IClientBubbleHandlerInterface() = default;`
- L21 _public prototype_ `virtual void InitializeForWorld(UWorld& InWorld) = 0;`
- L25 _public prototype_ `virtual void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize) = 0;` — These functions are processed internally by TClientBubbleHandlerBase
- L26 _public prototype_ `virtual void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize) = 0;`
- L27 _public prototype_ `virtual void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize) = 0;`
- L30 _public prototype_ `virtual void Reset() = 0;`
- L31 _public prototype_ `virtual void UpdateAgentsToRemove() = 0;`
- L33 _public prototype_ `virtual void Tick(float DeltaTime) = 0;`
- L34 _public prototype_ `virtual void SetClientHandle(FMassClientHandle InClientHandle) = 0;`
- L36 _public prototype_ `virtual void DebugValidateBubbleOnServer() = 0;`
- L37 _public prototype_ `virtual void DebugValidateBubbleOnClient() = 0;`

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassClientBubbleInfoBase.h` (Public)


#### class `AMassClientBubbleInfoBase`  
`class AMassClientBubbleInfoBase : public AInfo`  
_L16-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AInfo`
- desc: The info actor base class that provides the actual replication
- L21 _public prototype_ `AMassClientBubbleInfoBase(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `void SetClientHandle(FMassClientHandle InClientHandle);`
- L26 _protected prototype_ `virtual void PostInitProperties() override;`
- L29 _protected prototype_ `virtual void InitializeForWorld(UWorld& World);` — Called either on PostWorldInit() or PostInitProperties()
- L31 _protected prototype_ `virtual void BeginPlay() override;`
- L32 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L33 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L36 _private prototype_ `void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues);`
- L39 _protected member_ `FDelegateHandle OnPostWorldInitDelegateHandle;`
- L40 _protected member_ `TArray<FMassClientBubbleSerializerBase*> Serializers;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSREPLICATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassClientBubbleSerializerBase.h` (Public)


#### struct `FMassClientBubbleSerializerBase`  
`struct FMassClientBubbleSerializerBase : public FFastArraySerializer`  
_L23-61_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- desc: Classes derived from this will contain the IClientBubbleHandlerInterface derived class as well as the actual Fast Array. This class mainly provides the base automation with the IClientBubbleHandlerInterface
- L30 _public prototype_ `void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize) const;`
- L31 _public prototype_ `void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize) const;`
- L32 _public prototype_ `void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize) const;`
- L35 _public prototype_ `void InitializeForWorld(UWorld& InWorld);`
- L37 _public function_ `UWorld* GetWorld() const`
- L38 _public function_ `UMassSpawnerSubsystem* GetSpawnerSubsystem() const`
- L39 _public function_ `UMassReplicationSubsystem* GetReplicationSubsystem() const`
- L40 _public function_ `FMassEntityManager& GetEntityManagerChecked() const`
- L42 _public function_ `void SetClientHandler(IClientBubbleHandlerInterface& InClientHandler)`
- L43 _public function_ `IClientBubbleHandlerInterface* GetClientHandler() const`
- L45 _public prototype_ `void ShutDown();`
- L49 _private member_ `TObjectPtr<UWorld> World = nullptr;` — `UPROPERTY(Transient, NotReplicated)`
- L52 _private member_ `TObjectPtr<UMassSpawnerSubsystem> SpawnerSubsystem = nullptr;` — `UPROPERTY(Transient, NotReplicated)`
- L54 _private member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L57 _private member_ `TObjectPtr<UMassReplicationSubsystem> ReplicationSubsystem = nullptr;` — `UPROPERTY(Transient, NotReplicated)`
- L60 _private member_ `IClientBubbleHandlerInterface* ClientHandler = nullptr;` — Pointer to the IClientBubbleHandlerInterface derived class in the class derived from this one

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSREPLICATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationFragments.h` (Public)


#### struct `FMassNetworkIDFragment`  
`struct FMassNetworkIDFragment : public FMassFragment`  
_L21-26_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment type for the mass network id of a mass entity
- L25 _public member_ `FMassNetworkID NetID;`

#### struct `FMassReplicatedAgentFragment`  
`struct FMassReplicatedAgentFragment : public FMassFragment`  
_L32-37_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Agent handle per client, these will be at TArray indices of the Client handles indicies (used as a free list array)
- L36 _public member_ `FMassReplicatedAgentData AgentData;`

#### struct `FMassReplicationViewerInfoFragment`  
`struct FMassReplicationViewerInfoFragment : public FMassFragment`  
_L43-52_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Data fragment to store the calculated distances to viewers
- L48 _public member_ `float ClosestViewerDistanceSq;` — Closest viewer distance
- L51 _public member_ `TArray<float> DistanceToViewerSq;` — Distance between each viewer and entity

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassReplicationViewerInfoFragment> final`  
_L55-61_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L58-60_

#### struct `FMassReplicationLODFragment`  
`struct FMassReplicationLODFragment : public FMassFragment`  
_L64-73_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L69 _public member_ `TEnumAsByte<EMassLOD::Type> LOD = EMassLOD::Max;` — LOD information
- L72 _public member_ `TEnumAsByte<EMassLOD::Type> PrevLOD = EMassLOD::Max;` — Previous LOD information

#### class `UMassNetworkIDFragmentInitializer`  
`class UMassNetworkIDFragmentInitializer : public UMassObserverProcessor`  
_L76-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L80 _public prototype_ `UMassNetworkIDFragmentInitializer();`
- L83 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L84 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L86 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassReplicationParameters`  
`struct FMassReplicationParameters : public FMassConstSharedFragment`  
_L90-122_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L94 _public prototype_ `FMassReplicationParameters();`
- L98 _public member_ `float LODDistance[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Distance where each LOD becomes relevant
- L102 _public member_ `float BufferHysteresisOnDistancePercentage = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)` — Hysteresis percentage on delta between the LOD distances
- L106 _public member_ `int32 LODMaxCount[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Maximum limit of entity per LOD
- L110 _public member_ `int32 LODMaxCountPerViewer[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Maximum limit of entity per LOD per viewer
- L114 _public member_ `float UpdateInterval[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Distance where each LOD becomes relevant
- L117 _public member_ `TSubclassOf<AMassClientBubbleInfoBase> BubbleInfoClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Replication", config)`
- L120 _public member_ `TSubclassOf<UMassReplicatorBase> ReplicatorClass;` — `UPROPERTY(EditAnywhere, Category = "Mass|Replication", config)`

#### struct `FMassReplicationSharedFragment`  
`struct FMassReplicationSharedFragment : public FMassSharedFragment`  
_L125-168_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L129 _public prototype_ `FMassReplicationSharedFragment() = default;`
- L130 _public prototype_ `FMassReplicationSharedFragment(UMassReplicationSubsystem& ReplicationSubsystem, const FMassReplicationParameters& Params);`
- L132 _public member_ `FMassBubbleInfoClassHandle BubbleInfoClassHandle;`
- L134 _public member_ `FMassClientHandle CurrentClientHandle;`
- L135 _public member_ `TArray<FMassClientHandle> CachedClientHandles;`
- L140 _public member_ `TArray<TObjectPtr<AMassClientBubbleInfoBase>> BubbleInfos;` — `UPROPERTY()` — `UPROPERTY(Transient)` — TODO review if we need to have this as a UPROPERTY at all and also if we can make this use a TInlineAllocator
- L142 _public member_ `TMassLODCollector<FReplicationLODLogic> LODCollector;`
- L143 _public member_ `TMassLODCalculator<FReplicationLODLogic> LODCalculator;`
- L144 _public member_ `bool bHasAdjustedDistancesFromCount = false;`
- L146 _public member_ `bool bEntityQueryInitialized = false;`
- L147 _public member_ `FMassEntityQuery EntityQuery;`
- L150 _public member_ `mutable TObjectPtr<UMassReplicatorBase> CachedReplicator = nullptr;` — `UPROPERTY(Transient)`
- L152 _public function_ `bool IsValid() const`
- L158 _public function_ `template<typename T> T& GetTypedClientBubbleInfoChecked(FMassClientHandle Handle)`

#### struct `FMassReplicationGridCellLocationFragment`  
`struct FMassReplicationGridCellLocationFragment : public FMassFragment`  
_L172-176_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Cell location for replicated mass agents, used to fetch quickly the agents around each clients
- L175 _public member_ `FReplicationHashGrid2D::FCellLocation CellLoc;`

#### struct `FMassInReplicationGridTag`  
`struct FMassInReplicationGridTag : public FMassTag`  
_L180-183_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Component Tag to tell if the entity is in the replication grid

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSREPLICATION_API`
- L59 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon4021fee30103`)

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationGridProcessor.h` (Public)


#### class `UMassReplicationGridProcessor`  
`class UMassReplicationGridProcessor : public UMassProcessor`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor to update entity in the replication grid used to fetch entities close to clients
- L21 _public prototype_ `UMassReplicationGridProcessor();`
- L24 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L25 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L28 _private member_ `FMassEntityQuery AddToGridEntityQuery;`
- L29 _private member_ `FMassEntityQuery UpdateGridEntityQuery;`
- L30 _private member_ `FMassEntityQuery RemoveFromGridEntityQuery;`

#### class `UMassReplicationGridRemoverProcessor`  
`class UMassReplicationGridRemoverProcessor : public UMassObserverProcessor`  
_L35-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Deinitializer processor to remove entity from the replication grid
- L39 _private prototype_ `UMassReplicationGridRemoverProcessor();`
- L42 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L43 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L45 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSREPLICATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationProcessor.h` (Public)


#### class `UMassReplicationProcessor`  
`class UMassReplicationProcessor : public UMassProcessor`  
_L27-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Base processor that handles replication and only runs on the server. You should derive from this per entity type (that require different replication processing). It and its derived classes query Mass entity fragments and set those values for replication when appropriate, using the MassClientBubbleHandler.
- L32 _public prototype_ `UMassReplicationProcessor();`
- L35 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L36 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L37 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L39 _protected prototype_ `void PrepareExecution(FMassEntityManager& EntityManager);`
- L44 _protected member_ `TObjectPtr<UMassReplicationSubsystem> ReplicationSubsystem = nullptr;` — `UPROPERTY(Transient)`
- L46 _protected member_ `FMassEntityQuery SyncClientData;`
- L47 _protected member_ `FMassEntityQuery CollectViewerInfoQuery;`
- L48 _protected member_ `FMassEntityQuery CalculateLODQuery;`
- L49 _protected member_ `FMassEntityQuery AdjustLODDistancesQuery;`
- L50 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassReplicationEntityDestructionObserver`  
`class UMassReplicationEntityDestructionObserver : public UMassObserverProcessor`  
_L54-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L59 _public prototype_ `UMassReplicationEntityDestructionObserver();`
- L62 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L63 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L65 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassReplicationContext`  
`struct FMassReplicationContext`  
_L68-79_
- L70 _public function_ `FMassReplicationContext(UWorld& InWorld, const UMassLODSubsystem& InLODSubsystem, UMassReplicationSubsystem& InReplicationSubsystem) : World(InWorld) , LODSubsystem(InLODSubsystem) , ReplicationSubsystem(InReplicationSubsystem)`
- L76 _public member_ `UWorld& World;`
- L77 _public member_ `const UMassLODSubsystem& LODSubsystem;`
- L78 _public member_ `UMassReplicationSubsystem& ReplicationSubsystem;`

#### class `UMassReplicatorBase`  
`class UMassReplicatorBase : public UObject`  
_L82-106_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L91 _public prototype_ `virtual void AddRequirements(FMassEntityQuery& EntityQuery) PURE_VIRTUAL(UMassReplicatorBase::ConfigureQueries, );` — Must override to add specific entity query requirements for replication Usually we add replication processor handler requirements
- L97 _public prototype_ `virtual void ProcessClientReplication(FMassExecutionContext& Context, FMassReplicationContext& ReplicationContext) PURE_VIRTUAL(UMassReplicatorBase::ProcessClientReplication, );` — Must override to process the client replication This methods should call CalculateClientReplication with the appropriate callback implementation
- L105 _protected prototype_ `template<typename AgentArrayItem, typename CacheViewsCallback, typename AddEntityCallback, typename ModifyEntityCallback, typename RemoveEntityCallback> static void CalculateClientReplication(FMassExecutionContext& Context, FMassReplicationContext& ReplicationContext, CacheViewsCallback&& CacheViews, AddEntityCallback&& AddEntity, ModifyEntityCallback&& ModifyEntity, RemoveEntityCallback&& RemoveEntity);` — Implemented as straight template callbacks as when profiled this was faster than TFunctionRef. Its probably easier to pass Lamdas in to these but Functors can also be used as well as TFunctionRefs etc. Its also fairly straight forward to call member functions via some Lamda glue code
- L109 _function_ `template<typename AgentArrayItem, typename CacheViewsCallback, typename AddEntityCallback, typename ModifyEntityCallback, typename RemoveEntityCallback> void UMassReplicatorBase::CalculateClientReplication(FMassExecutionContext& Context, FMassReplicationContext& ReplicationContext, CacheViewsCallback&& CacheViews , AddEntityCallback&& AddEntity, ModifyEntityCallback&& ModifyEntity, RemoveEntityCallback&& RemoveEntity)`

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationSettings.h` (Public)


#### class `UMassReplicationSettings`  
`class UMassReplicationSettings : public UMassModuleSettings`  
_L9-28_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, meta = (DisplayName = "Mass Replication"))`
- inherits: `UMassModuleSettings`
- L14 _public function_ `static const UMassReplicationSettings* Get()`
- L19 _public function_ `float GetReplicationGridCellSize() const`
- L27 _private member_ `float ReplicationGridCellSize = 5000.0f;` — `UPROPERTY(EditAnywhere, config, Category = Replication)` — 50 meters;

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationSubsystem.h` (Public)


#### struct `FMassClientReplicationInfo`  
`struct FMassClientReplicationInfo`  
_L20-44_
- L22 _public function_ `void Reset()`
- L30 _public function_ `bool IsEmpty() const` — Note this struct is constructed IsEmpty() == true
- L36 _public member_ `TArray<FMassViewerHandle> Handles;` — Array of all the viewer of this client
- L40 _public member_ `TArray<FMassEntityHandle> HandledEntities;` — Array of all the entities handled by this client This array might contains duplicates if there is more than one viewer per client as this concatenates the entities from all viewer of a client)
- L43 _public member_ `FMassReplicationAgentDataMap AgentsData;` — The saved agent data of the entities handle by this client

#### struct `FViewerClientPair`  
`struct FViewerClientPair`  
_L46-62_
- L48 _public prototype_ `FViewerClientPair() = default;`
- L50 _public function_ `FViewerClientPair(FMassViewerHandle InViewerHandle, FMassClientHandle InClientHandle) : ViewerHandle(InViewerHandle) , ClientHandle(InClientHandle)`
- L55 _public function_ `bool operator== (FViewerClientPair Other) const`
- L57 _public function_ `bool IsValid() const`
- L58 _public function_ `void Invalidate()`
- L60 _public member_ `FMassViewerHandle ViewerHandle;`
- L61 _public member_ `FMassClientHandle ClientHandle;`

#### struct `FMassClientBubbleInfoData`  
`struct FMassClientBubbleInfoData`  
_L65-81_
- reflection: `USTRUCT()`
- L69 _public prototype_ `FMassClientBubbleInfoData() = default;`
- L71 _public function_ `FMassClientBubbleInfoData(TSubclassOf<AMassClientBubbleInfoBase> InBubbleClass) : BubbleClass(InBubbleClass)`
- L77 _public member_ `TArray<TObjectPtr<AMassClientBubbleInfoBase>> Bubbles;` — `UPROPERTY(Transient)` — A free list array of AMassClientBubbleInfos. This is organised so the index is that of the client FMassClientHandle
- L80 _public member_ `TSubclassOf<AMassClientBubbleInfoBase> BubbleClass;` — `UPROPERTY(Transient)`

#### class `UMassReplicationSubsystem`  
`class UMassReplicationSubsystem : public UMassSubsystemBase`  
_L96-344_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: Manages the creation of NetworkIDs, ClientBubbles and ClientReplicationInfo. NetworkIDs are per replicated Agent Entity and are unique and replicated between server and clients. ClientBubbles relate to the player controller that owns the parent UNetConnection to a Client machine. ClientReplicationInfo relate to all the player controllers that have a parent or child UNetConnection to a single Client machine (split screen etc).
- L102 _public prototype_ `UMassReplicationSubsystem();`
- L111 _public function_ `bool IsBubbleClassHandleValid(FMassBubbleInfoClassHandle Handle) const`
- L117 _public prototype_ `FMassNetworkID GetNetIDFromHandle(const FMassEntityHandle Handle) const;` — Retrieve network id from Mass handle.
- L119 _public function_ `static inline FMassNetworkID GetNextAvailableMassNetID()`
- L121 _public function_ `const TArray<FMassClientHandle>& GetClientReplicationHandles() const`
- L123 _public function_ `bool IsValidClientHandle(FMassClientHandle ClientHandle) const`
- L129 _public function_ `AMassClientBubbleInfoBase* GetClientBubble(FMassBubbleInfoClassHandle BubbleClassHandle, FMassClientHandle ClientHandle) const` — Gets the client bubble safely
- L142 _public function_ `AMassClientBubbleInfoBase* GetClientBubbleChecked(FMassBubbleInfoClassHandle BubbleClassHandle, FMassClientHandle ClientHandle) const` — Get the client bubble. Faster version using check()s
- L154 _public function_ `template<typename TType> TType* GetTypedClientBubble(FMassBubbleInfoClassHandle BubbleClassHandle, FMassClientHandle ClientHandle) const` — Gets the client bubble safely returning the template type
- L161 _public function_ `template<typename TType> TType* GetTypedClientBubbleChecked(FMassBubbleInfoClassHandle BubbleClassHandle, FMassClientHandle ClientHandle) const` — Gets the client bubble returning the template type. Faster version using check()s
- L170 _public function_ `const FMassClientReplicationInfo* GetClientReplicationInfo(FMassClientHandle Handle) const` — Gets the client replication info safely
- L176 _public function_ `const FMassClientReplicationInfo& GetClientReplicationInfoChecked(FMassClientHandle Handle) const` — Gets the client replication info. Faster version using check()s
- L184 _public function_ `FMassClientReplicationInfo* GetMutableClientReplicationInfo(FMassClientHandle Handle)` — Gets the client replication info. Faster version using check()s
- L190 _public function_ `FMassClientReplicationInfo& GetMutableClientReplicationInfoChecked(FMassClientHandle Handle)` — Gets the client replication info. Faster version using check()s
- L195 _public prototype_ `void SynchronizeClientsAndViewers();`
- L204 _public prototype_ `FMassBubbleInfoClassHandle RegisterBubbleInfoClass(const TSubclassOf<AMassClientBubbleInfoBase>& BubbleInfoClass);` — Registers BubbleInfoClass with the system. These are created one per client as clients join. This function can be called multiple times with different BubbleInfoClass types (but not the same type), in that case each client will get multiple BubbleInfoClasses. This can be useful for replicating different Entity types in different bubbles, although its also possible to have multiple TClientBubbleHandlerBase derived class instances per BubbleInfoClass. This must not be called after AddClient or SynchronizeClientsAndViewers is called @return FMassBubbleInfoClassHandle Handle to the BubbleInfoClass, this will be an invalid handle if its not been created
- L207 _public prototype_ `FMassBubbleInfoClassHandle GetBubbleInfoClassHandle(const TSubclassOf<AMassClientBubbleInfoBase>& BubbleInfoClass) const;` — @return FMassBubbleInfoClassHandle Handle to the BubbleInfoClass, this will be an invalid handle if BubbleInfoClass can not be found
- L209 _public function_ `const FReplicationHashGrid2D& GetGrid() const`
- L210 _public function_ `FReplicationHashGrid2D& GetGridMutable()`
- L213 _public prototype_ `void NotifyEntityDestroyed(FMassEntityHandle EntityHandle);`
- L221 _public prototype_ `void SetEntity(const FMassNetworkID NetworkID, const FMassEntityHandle Entity);` — Must be called immediately after an Entity is added to the simulation and after FindAndUpdateOrAddMassEntityInfo has been called
- L228 _public prototype_ `FMassEntityHandle ResetEntityIfValid(const FMassNetworkID NetworkID, int32 ReplicationID);` — Resets the item with NetworkID in the  EntityInfoMap if its currently Set / Valid and its the most recent ReplicationID. In this case the FMassEntityHandle that was reset is returned. Otherwise FMassEntityHandle::IsSet() will be false on the returned FMassEntityHandle Must be called after SetEntity and just before the Entity is removed on the client. This sets the Entity member of the AddToEntityInfoMap item to FMassEntityHandle so it will be not IsSet()
- L230 _public prototype_ `void RemoveFromEntityInfoMap(const FMassNetworkID NetworkID);`
- L241 _public prototype_ `EFindOrAddMassEntityInfo FindAndUpdateOrAddMassEntityInfo(const FMassNetworkID NetworkID, int32 ReplicationID, const FMassReplicationEntityInfo*& OutMassEntityInfo);` — Finds or adds an FMassReplicationEntityInfo to the EntityInfoMap for an Entity with NetWorkID. This will update the ReplicationID if an older one is found but it does not change the FMassReplicationEntityInfo::Entity member. Returns whether we added an entry in EntityInfoMap, or if the found item has an older or newer ReplicationID than that that is passed in. We shouldn't actually get an equal ReplicationID, but in this case we'll treat the existing EntityInfoMap entry as newer. SetEntity() must be called soon after this if the entity handle is !IsSet() @param NetworkID ID of the entity we are looking up OutMassEntityInfo for @param ReplicationID this is the ReplicationID of the FastArray item @param OutMassEntityInfo retrieved or added FMassReplicationEntityInfo @return EFindOrAddMassEntityInfo, result of the function call
- L247 _public prototype_ `const FMassReplicationEntityInfo* FindMassEntityInfo(const FMassNetworkID NetworkID) const;` — Finds the FMassReplicationEntityInfo for the Entity with NetworkID. NetworkID must be valid and nullptr is returned if we can't find it. Note FMassReplicationEntityInfo::IsSet() may be false, in which case this Entity has been removed from the client simulation (but we are still storing the ReplicationID between Removes and Adds!
- L249 _public prototype_ `FMassEntityHandle FindEntity(const FMassNetworkID NetworkID) const;`
- L251 _public function_ `const TMap<FMassNetworkID, FMassReplicationEntityInfo>& GetEntityInfoMap() const`
- L253 _public function_ `UE::MassReplication::FMassAgentDelegate& GetOnMassAgentAdded()`
- L258 _public function_ `UE::MassReplication::FMassAgentDelegate& GetOnRemovingMassAgent()`
- L267 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L268 _protected prototype_ `virtual void Deinitialize() override;`
- L272 _protected prototype_ `FMassReplicationEntityInfo* FindMassEntityInfoMutable(const FMassNetworkID NetworkID);`
- L280 _protected prototype_ `void AddClient(FMassViewerHandle ViewerHandle, APlayerController& InController);` — Adds a Client and sets up all the data relevant to the bubble. Where there are multiple viewers for one NetConnection only the parent net connection should be added here @param ViewerHandle handle to viewer to add as a client. This must be UMassLODSubsystem->IsValidViewer() @param InController associated with the viewer
- L285 _protected prototype_ `void RemoveClient(FMassClientHandle ClientHandle);` — Removes a Client and removes up all the data relevant to the bubble @param ClientHandle handle to client to remove. This must be ClientHandleManager.IsValidHandle()
- L288 _protected prototype_ `bool SynchronizeClients(const TArray<FViewerInfo>& Viewers);` — @return true if we should shrink the number of handles.
- L289 _protected prototype_ `void SynchronizeClientViewers(const TArray<FViewerInfo>& Viewers);`
- L291 _protected prototype_ `void DebugCheckArraysAreInSync();`
- L294 _protected member_ `static uint32 CurrentNetMassCounter;`
- L296 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L299 _protected member_ `FMassClientHandleManager ClientHandleManager;` — Clients free list FMassClientHandle manager, handles will to the indices of FMassClientReplicationData::ClientBubbles
- L302 _protected member_ `TArray<FMassClientBubbleInfoData> BubbleInfoArray;` — `UPROPERTY(Transient)`
- L308 _protected member_ `TArray<FMassClientReplicationInfo> ClientsReplicationInfo;` — An Array of each Clients viewer handles (split screen players sharing the same client connections). This will include both the parent and child NetConnections per client. The array is organized so the array index is the same as the index of the client FMassClientHandle.
- L313 _protected member_ `TArray<FViewerClientPair> ViewerToClientHandleArray;` — A free list array of FViewerClientPairs. This is organized so the index is that of the FMassViewerHandle for fast lookup of the related FMassClientHandle. This only contains viewers that are also clients (ie only parent NetConnections not child ones).
- L318 _protected member_ `TArray<FViewerClientPair> ClientToViewerHandleArray;` — A free list array of FViewerClientPairs. This is organized so the index is that of the FMassClientHandle. For fast lookup of the related FMassViewerHandle. This only contains viewers that are also clients (ie only parent NetConnections not child ones).
- L321 _protected member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()`
- L324 _protected member_ `TObjectPtr<UMassLODSubsystem> MassLODSubsystem;` — `UPROPERTY()`
- L327 _protected member_ `TMap<FMassNetworkID, FMassReplicationEntityInfo> EntityInfoMap;`
- L331 _protected member_ `UE::MassReplication::FMassAgentDelegate OnMassAgentAdded;` — Broadcast just after a mass agent is added to the client simulation
- L334 _protected member_ `UE::MassReplication::FMassAgentDelegate OnRemovingMassAgent;` — Broadcast just before a mass agent is removed from the client simulation
- L341 _protected member_ `uint64 LastSynchronizedFrame = 0;` — Used to make sure the FMassEntityHandle_ClientReplications are synchronized immediately before they are needed @todo this comment is no longer accurate, needs fixing
- L343 _protected member_ `FReplicationHashGrid2D ReplicationGrid;`

#### enum `UMassReplicationSubsystem::EFindOrAddMassEntityInfo`  
`enum class EFindOrAddMassEntityInfo : uint8`  
_L104-109_
- L106 _public enumerator_ `FoundOlderReplicationID`
- L107 _public enumerator_ `FoundNewerReplicationID`
- L108 _public enumerator_ `Added`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassReplicationSubsystem> final`  
_L347-354_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L350-353_

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSREPLICATION_API`
- L18 _typedef_ `typedef TMap<FMassEntityHandle, FMassReplicatedAgentData> FMassReplicationAgentDataMap;`
- L83 _namespace_ `namespace UE`
- L83 _namespace_ `namespace MassReplication` (scope `UE`)
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMassAgentDelegate, FMassNetworkID, FMassEntityHandle);`
- L85 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMassAgentDelegate, FMassNetworkID, FMassEntityHandle);` (scope `UE::MassReplication`)
- L351 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon5650a3cb0103`)
- L352 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon5650a3cb0103`)

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationTemplates.h` (Public)


#### struct `UE::Mass::Replication::TReplicationProcessorHandler`  
`template<typename TReplicatedDataType, typename... TFragments> struct TReplicationProcessorHandler`  
_L173-249_
- desc: Server-side fragment data handler template. Handles collections of fragments and converts fragment data to replication-friendly representation. Used in UMassReplicatorBase-derived classes. @param TReplicatedDataType - The replicated data struct @param TFragments - Fragment types that contribute to this replicated data
- L175 _public typedef_ `using FReplicatedDataType = TReplicatedDataType;`
- L178 _public typedef_ `template<typename TFragmentView> using TFragmentType = typename TRemoveReference<TFragmentView>::Type::ElementType;`
- L181 _public function_ `template<CFragment T> TArrayView<const T>& GetView()`
- L187 _public function_ `template<CFragment T> const TArrayView<const T>& GetView() const`
- L192 _public function_ `static void AddRequirements(FMassEntityQuery& InQuery)`
- L197 _public function_ `void CacheFragmentViews(FMassExecutionContext& ExecContext)`
- L207 _public function_ `void AddEntity(const int32 EntityIndex, FReplicatedDataType& OutReplicatedData) const`
- L221 _public function_ `template<typename TClientBubbleHandler> requires TIsDerivedFrom<TClientBubbleHandler, IClientBubbleHandlerInterface>::Value void ModifyEntity(const FMassReplicatedAgentHandle Handle, const int32 EntityIndex, TClientBubbleHandler& ClientBubble)` — Updates replicated data for an existing entity. Calls SetBubbleData on the client handler which performs dirty checking. Note that the function is a no-op if TReplicationTraits<FReplicatedDataType>::bSkipEntityModification == true.
- L235 _private function_ `template<CFragment TFragment> void ExtractSingleFragment(const int32 EntityIndex, FReplicatedDataType& OutReplicatedData) const`
- L248 _private member_ `std::tuple<TArrayView<const TFragments>...> FragmentViewLists;`

#### struct `UE::Mass::Replication::TClientBubbleFragmentHandler`  
`template<typename TReplicatedDataType, CFragment... TFragments> struct TClientBubbleFragmentHandler`  
_L264-357_
- desc: Client-side bubble handler for fragments. Automatically implements all client handler methods using TReplicationTraits. Used in TClientBubbleHandlerBase-derived types. @param TReplicatedDataType - The replicated data struct @param TFragments - Fragment types that receive this replicated data
- L267 _public typedef_ `using FReplicatedDataType = TReplicatedDataType;`
- L270 _public typedef_ `template<typename TFragmentView> using TFragmentType = typename TRemoveReference<TFragmentView>::Type::ElementType;`
- L273 _public function_ `template<CFragment T> TArrayView<T>& GetView()`
- L279 _public function_ `template<CFragment T> const TArrayView<T>& GetView() const`
- L285 _public function_ `static void AddRequirementsForSpawnQuery(FMassEntityQuery& InQuery)` — Adds fragment requirements for the spawn query
- L291 _public function_ `void CacheFragmentViewsForSpawnQuery(FMassExecutionContext& InExecContext)` — Caches mutable fragment views for spawning
- L302 _public function_ `void ClearFragmentViewsForSpawnQuery()` — Clears cached fragment views
- L313 _public function_ `void SetSpawnedEntityData(const int32 EntityIndex, const FReplicatedDataType& Data)` — Applies replicated data to a newly spawned entity
- L319 _public function_ `static void SetModifiedEntityData(const FMassEntityView& EntityView, const FReplicatedDataType& Data)` — Applies replicated data to an already-existing entity
- L329 _private function_ `template<CFragment TFragment> void ApplySingleFragment(const int32 EntityIndex, const FReplicatedDataType& Data)`
- L336 _private function_ `template<CFragment TFragment> static void ApplyModifiedFragment(const FMassEntityView& EntityView, const FReplicatedDataType& Data)`
- L343 _private function_ `template<CFragment TFragment> static void ApplyToFragment(TFragment& Fragment, const FReplicatedDataType& Data)`
- L355 _private member_ `std::tuple<TArrayView<TFragments>...> FragmentViewLists;`

#### struct `UE::Mass::Replication::TReplicationProcessorHandlerPack`  
`template<typename... TFragmentHandlers> struct TReplicationProcessorHandlerPack`  
_L368-414_
- desc: Server-side handler pack for multiple replicated data types. Orchestrates multiple TReplicationProcessorHandler instances.
- L371 _public typedef_ `template<typename TDataHandler> using TReplicatedData = typename TRemoveReference<TDataHandler>::Type::FReplicatedDataType;`
- L373 _public function_ `static void AddRequirements(FMassEntityQuery& InQuery)`
- L378 _public function_ `void CacheFragmentViews(FMassExecutionContext& InExecContext)`
- L389 _public function_ `template<typename TReplicatedEntityData> void AddEntity(const int32 EntityIndex, TReplicatedEntityData& ReplicatedEntity) const`
- L402 _public function_ `template<typename TClientBubbleHandler> requires TIsDerivedFrom<TClientBubbleHandler, IClientBubbleHandlerInterface>::Value void ModifyEntity(const FMassReplicatedAgentHandle Handle, const int32 EntityIndex, TClientBubbleHandler& ClientBubble)`
- L413 _private member_ `std::tuple<TFragmentHandlers...> FragmentHandlers;`

#### struct `UE::Mass::Replication::TCachedSpawnQuery`  
`template<typename THandlers> struct TCachedSpawnQuery`  
_L421-442_
- desc: Helper struct to be used as CRTP to supply types with SpawnQuery creation and caching functionality @param THandlers anything that implements AddRequirementsForSpawnQuery
- L428 _public function_ `FMassEntityQuery& GetSpawnQuery(const TSharedRef<FMassEntityManager>& EntityManager)` — Returns the cached SpawnQuery. If it's not initialized yet EntityManager will be used for the initialization, along with AddRequirementsForSpawnQuery member function
- L440 _private member_ `FMassEntityQuery SpawnQuery;` — Entity query used to configure entities added to the client

#### struct `UE::Mass::Replication::TClientBubbleDataHandlerPack`  
`template<typename... TFragmentHandlers> struct TClientBubbleDataHandlerPack : TCachedSpawnQuery<TClientBubbleDataHandlerPack<TFragmentHandlers...>>`  
_L449-503_
- inherits: `TCachedSpawnQuery<TClientBubbleDataHandlerPack<TFragmentHandlers...>>`
- desc: Client-side handler pack for multiple replicated data types. Orchestrates multiple TClientBubbleFragmentHandler instances.
- L452 _public typedef_ `template<typename TDataHandler> using TReplicatedData = typename TRemoveReference<TDataHandler>::Type::FReplicatedDataType;`
- L455 _public function_ `static void AddRequirementsForSpawnQuery(FMassEntityQuery& InQuery)`
- L460 _public function_ `void CacheFragmentViewsForSpawnQuery(FMassExecutionContext& InExecContext)`
- L470 _public function_ `void ClearFragmentViewsForSpawnQuery()`
- L481 _public function_ `template<typename TReplicatedEntityData> void SetSpawnedEntityData(const FMassEntityView& EntityView, const TReplicatedEntityData& ReplicatedEntity, const int32 EntityIndex)`
- L493 _public function_ `template<typename TReplicatedEntityData> void SetModifiedEntityData(const FMassEntityView& EntityView, const TReplicatedEntityData& ReplicatedEntity)`
- L502 _private member_ `std::tuple<TFragmentHandlers...> FragmentHandlers;`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace Mass` (scope `UE`)
- L54 _namespace_ `namespace Replication` (scope `UE::Mass`)
- L106 _prototype_ `TReplicationTraits<TReplicatedDataType>::ExtractData(Frag, Data);` (scope `UE::Mass::Replication::TReplicationTraits`)
- L114 _prototype_ `TReplicationTraits<TReplicatedDataType>::ApplyData(Frag, Data);` (scope `UE::Mass::Replication::TReplicationTraits`)
- L144 _function_ `template<typename TReplicatedDataType> bool CheckIsDirty(const TReplicatedDataType& OldData, const TReplicatedDataType& NewData)` (scope `UE::Mass::Replication`)
- L200 _function_ `` (scope `UE::Mass::Replication::TReplicationProcessorHandler::CacheFragmentViews`)
- L294 _function_ `` (scope `UE::Mass::Replication::TClientBubbleFragmentHandler::CacheFragmentViewsForSpawnQuery`)
- L305 _function_ `` (scope `UE::Mass::Replication::TClientBubbleFragmentHandler::ClearFragmentViewsForSpawnQuery`)
- L381 _function_ `` (scope `UE::Mass::Replication::TReplicationProcessorHandlerPack::CacheFragmentViews`)
- L392 _function_ `` (scope `UE::Mass::Replication::TReplicationProcessorHandlerPack::AddEntity`)
- L405 _function_ `` (scope `UE::Mass::Replication::TReplicationProcessorHandlerPack::ModifyEntity`)
- L463 _function_ `` (scope `UE::Mass::Replication::TClientBubbleDataHandlerPack::CacheFragmentViewsForSpawnQuery`)
- L473 _function_ `` (scope `UE::Mass::Replication::TClientBubbleDataHandlerPack::ClearFragmentViewsForSpawnQuery`)
- L484 _function_ `` (scope `UE::Mass::Replication::TClientBubbleDataHandlerPack::SetSpawnedEntityData`)
- L526 _macro_ `#define UE_MASSREPLICATION_DECLARE_HANDLERS(Name, ReplicatedDataType, ...) \` — Declares both server and client handler types for replication of fragments. Example: UE_MASSREPLICATION_DECLARE_HANDLERS(Health, FReplicatedHealthData, FHealthFragment); Declares: using FMassReplicationProcessorHealthHandler = TReplicationProcessorHandler<FReplicatedHealthData, FHealthFragment>; using FMassClientBubbleHealthHandler = TClientBubbleFragmentHandler<FReplicatedHealthData, FHealthFragment>; For multiple fragments: UE_MASSREPLICATION_DECLARE_HANDLERS(Character, FReplicatedCharacterData, FTransformFragment, FVelocityFragment); @see TReplicationTraits for trait specialization details.
- L544 _macro_ `#define UE_MASSREPLICATION_DECLARE_ACCESSORS() \` — Declares templated GetReplicatedData accessors in an agent struct. Use UE_MASSREPLICATION_IMPLEMENT_ACCESSOR to provide implementations. Usage: struct FMyAgent : public FReplicatedAgentBase { GENERATED_BODY() UE_MASSREPLICATION_DECLARE_ACCESSORS() private: UPROPERTY(Transient) FMyReplicatedData MyData; };
- L555 _macro_ `#define UE_MASSREPLICATION_IMPLEMENT_ACCESSOR(AgentType, DataType, MemberName) \` — Specializes the templated accessor for a specific data type. Must be placed outside of struct declaration body at namespace scope. Usage: UE_MASSREPLICATION_IMPLEMENT_ACCESSOR(FMyAgent, FMyReplicatedData, MyData)

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationTrait.h` (Public)


#### class `UMassReplicationTrait`  
`class UMassReplicationTrait : public UMassEntityTraitBase`  
_L13-23_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Replication"))`
- inherits: `UMassEntityTraitBase`
- L19 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L22 _public member_ `FMassReplicationParameters Params;` — `UPROPERTY(EditAnywhere, Category = "Mass|Replication")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSREPLICATION_API`

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationTransformHandlers.h` (Public)


#### struct `FReplicatedAgentPositionYawData`  
`struct FReplicatedAgentPositionYawData`  
_L30-53_
- reflection: `USTRUCT()`
- desc: To replicate position and yaw make a member variable of this class in your FReplicatedAgentBase derived class. In the FReplicatedAgentBase derived class you must also provide an accessor function FReplicatedAgentPathData& GetReplicatedPositionYawDataMutable().
- L35 _public function_ `FReplicatedAgentPositionYawData() : Position(ForceInitToZero)`
- L39 _public function_ `void SetPosition(const FVector& InPosition)`
- L40 _public function_ `const FVector& GetPosition() const`
- L42 _public function_ `void SetYaw(const float InYaw)`
- L43 _public function_ `float GetYaw() const`
- L48 _private member_ `FVector Position;` — `UPROPERTY(Transient)`
- L52 _private member_ `float Yaw = 0;` — `UPROPERTY(Transient)` — Yaw in radians

#### class `TMassClientBubbleTransformHandler`  
`template<typename AgentArrayItem> class TMassClientBubbleTransformHandler`  
_L64-104_
- desc: To replicate Transforms make a member variable of this class in your TClientBubbleHandlerBase derived class. This class is a friend of TMassClientBubblePathHandler. It is meant to have access to the protected data declared there.
- L67 _public function_ `TMassClientBubbleTransformHandler(TClientBubbleHandlerBase<AgentArrayItem>& InOwnerHandler) : OwnerHandler(InOwnerHandler)`
- L73 _public prototype_ `void SetBubblePositionYawFromTransform(const FMassReplicatedAgentHandle Handle, const FTransform& Transform);` — Sets the position and yaw data in the client bubble on the server
- L83 _public prototype_ `static void AddRequirementsForSpawnQuery(FMassEntityQuery& InQuery);` — When entities are spawned in Mass by the replication system on the client, a spawn query is used to set the data on the spawned entities. The following functions are used to configure the query and then set the position and yaw data.
- L84 _public prototype_ `void CacheFragmentViewsForSpawnQuery(FMassExecutionContext& InExecContext);`
- L85 _public prototype_ `void ClearFragmentViewsForSpawnQuery();`
- L87 _public prototype_ `void SetSpawnedEntityData(const int32 EntityIdx, const FReplicatedAgentPositionYawData& ReplicatedPathData) const;`
- L90 _public prototype_ `static void SetModifiedEntityData(const FMassEntityView& EntityView, const FReplicatedAgentPositionYawData& ReplicatedPathData);` — Call this when an Entity that has already been spawned is modified on the client
- L97 _protected prototype_ `static void SetEntityData(FTransformFragment& TransformFragment, const FReplicatedAgentPositionYawData& ReplicatedPositionYawData);`
- L101 _protected member_ `TArrayView<FTransformFragment> TransformList;`
- L103 _protected member_ `TClientBubbleHandlerBase<AgentArrayItem>& OwnerHandler;`
- L108 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::SetBubblePositionYawFromTransform(const FMassReplicatedAgentHandle Handle, const FTransform& Transform)`
- L146 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::AddRequirementsForSpawnQuery(FMassEntityQuery& InQuery)`
- L154 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::CacheFragmentViewsForSpawnQuery(FMassExecutionContext& InExecContext)`
- L162 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::ClearFragmentViewsForSpawnQuery()`
- L170 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::SetSpawnedEntityData(const int32 EntityIdx, const FReplicatedAgentPositionYawData& ReplicatedPositionYawData) const`
- L180 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::SetModifiedEntityData(const FMassEntityView& EntityView, const FReplicatedAgentPositionYawData& ReplicatedPositionYawData)`
- L190 _function_ `template<typename AgentArrayItem> void TMassClientBubbleTransformHandler<AgentArrayItem>::SetEntityData(FTransformFragment& TransformFragment, const FReplicatedAgentPositionYawData& ReplicatedPositionYawData)`

#### class `FMassReplicationProcessorTransformHandlerBase`  
`class FMassReplicationProcessorTransformHandlerBase`  
_L200-208_
- L203 _public prototype_ `static void AddRequirements(FMassEntityQuery& InQuery);`
- L204 _public prototype_ `void CacheFragmentViews(FMassExecutionContext& ExecContext);`
- L207 _protected member_ `TArrayView<FTransformFragment> TransformList;`

#### class `FMassReplicationProcessorPositionYawHandler`  
`class FMassReplicationProcessorPositionYawHandler : public FMassReplicationProcessorTransformHandlerBase`  
_L217-224_
- inherits: `FMassReplicationProcessorTransformHandlerBase`
- desc: Used to replicate position and yaw by your UMassReplicationProcessorBase derived class. This class should only get used on the server. @todo add #if UE_REPLICATION_COMPILE_SERVER_CODE
- L220 _public prototype_ `void AddEntity(const int32 EntityIdx, FReplicatedAgentPositionYawData& InOUtReplicatedPathData) const;`
- L223 _public prototype_ `template<typename AgentArrayItem> void ModifyEntity(const FMassReplicatedAgentHandle Handle, const int32 EntityIdx, TMassClientBubbleTransformHandler<AgentArrayItem>& BubblePathHandler);`
- L227 _function_ `template<typename AgentArrayItem> void FMassReplicationProcessorPositionYawHandler::ModifyEntity(const FMassReplicatedAgentHandle Handle, const int32 EntityIdx, TMassClientBubbleTransformHandler<AgentArrayItem>& BubbleTransformHandler)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mass` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::Mass`)
- L18 _variable_ `constexpr float PositionReplicateTolerance = 1.f;` (scope `UE::Mass::Replication`)
- L19 _variable_ `constexpr float YawReplicateTolerance = 0.004363323f;` (scope `UE::Mass::Replication`)

### `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationTypes.h` (Public)


#### struct `FMassReplicatedAgentHandle`  
`struct FMassReplicatedAgentHandle : public FCompactIndexedHandleBase`  
_L74-84_
- reflection: `USTRUCT()`
- inherits: `FCompactIndexedHandleBase`
- desc: Handle of each Agent per Client (bubble), these handles are not consistent between different client bubbles. Using the compact handle here will make the memory footprint smaller and help the ECS system be more cache friendly. TODO: in the long run we can probably use a non serial number handle here, I'd like to stick with the serial number for now though
- L78 _public prototype_ `FMassReplicatedAgentHandle() = default;`
- L81 _public function_ `FMassReplicatedAgentHandle(int32 InIndex, uint32 InSerialNumber) : FCompactIndexedHandleBase(InIndex, InSerialNumber)` — @param InIndex - passing INDEX_NONE will make this handle Invalid

#### struct `FMassClientHandle`  
`struct FMassClientHandle : public FIndexedHandleBase`  
_L90-100_
- reflection: `USTRUCT()`
- inherits: `FIndexedHandleBase`
- desc: Handle of each Client on the server. A Client is defined as a player controller with a non nullptr parent NetConnection
- L94 _public prototype_ `FMassClientHandle() = default;`
- L97 _public function_ `FMassClientHandle(int32 InIndex, uint32 InSerialNumber) : FIndexedHandleBase(InIndex, InSerialNumber)` — @param InIndex - passing INDEX_NONE will make this handle Invalid

#### struct `FMassBubbleInfoClassHandle`  
`struct FMassBubbleInfoClassHandle : public FSimpleIndexedHandleBase`  
_L105-115_
- reflection: `USTRUCT()`
- inherits: `FSimpleIndexedHandleBase`
- L109 _public prototype_ `FMassBubbleInfoClassHandle() = default;`
- L112 _public function_ `FMassBubbleInfoClassHandle(int32 InIndex) : FSimpleIndexedHandleBase(InIndex)` — @param InIndex - passing INDEX_NONE will make this handle Invalid

#### struct `FReplicatedAgentBase`  
`struct FReplicatedAgentBase`  
_L118-141_
- reflection: `USTRUCT()`
- L122 _public prototype_ `FReplicatedAgentBase() = default;`
- L124 _public function_ `FReplicatedAgentBase(FMassNetworkID InNetID, FMassEntityTemplateID InTemplateID) : NetID(InNetID) , TemplateID(InTemplateID)`
- L129 _public function_ `void SetNetID(FMassNetworkID InNetID)`
- L130 _public function_ `FMassNetworkID GetNetID() const`
- L132 _public function_ `void SetTemplateID(FMassEntityTemplateID InTemplateID)`
- L133 _public function_ `FMassEntityTemplateID GetTemplateID() const`
- L137 _private member_ `FMassNetworkID NetID;` — `UPROPERTY()`
- L140 _private member_ `FMassEntityTemplateID TemplateID;` — `UPROPERTY()`

#### struct `FReplicationLODLogic`  
`struct FReplicationLODLogic : public FLODDefaultLogic`  
_L143-145_
- inherits: `FLODDefaultLogic`

#### struct `FMassReplicatedAgentData`  
`struct FMassReplicatedAgentData`  
_L147-161_
- L149 _public function_ `void Invalidate()`
- L157 _public member_ `FMassReplicatedAgentHandle Handle;`
- L158 _public member_ `double LastUpdateTime = 0.;`
- L159 _public member_ `EMassLOD::Type LOD = EMassLOD::Off;`
- L160 _public member_ `bool bPendingDestruction = false;`

#### struct `FMassReplicationEntityInfo`  
`struct FMassReplicationEntityInfo`  
_L165-178_
- desc: Data that can be accessed from a FMassNetworkID on a client
- L167 _public prototype_ `FMassReplicationEntityInfo() = default;`
- L168 _public function_ `FMassReplicationEntityInfo(FMassEntityHandle InEntity, int32 InReplicationID) : Entity(InEntity) , ReplicationID(InReplicationID)`
- L174 _public member_ `FMassEntityHandle Entity;` — If this is not IsSet() then the entity has been removed from the client simulation
- L177 _public member_ `int32 ReplicationID = INDEX_NONE;` — This is stored between removes and adds, however this item in the UMassReplicationSubsystem::EntityInfoMap will eventually get cleaned up if Entity.IsSet() == false for a fairly substantial length of time.

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_DEBUG_REPLICATION_BUBBLES_STANDALONE 0`
- L26 _macro_ `#define UE_ALLOW_DEBUG_REPLICATION_BUBBLES_STANDALONE 1`
- L28 _macro_ `#define UE_ALLOW_DEBUG_REPLICATION_BUBBLES_STANDALONE 0`
- L33 _macro_ `#define UE_REPLICATION_COMPILE_SERVER_CODE 1`
- L35 _macro_ `#define UE_REPLICATION_COMPILE_SERVER_CODE 0`
- L40 _macro_ `#define UE_REPLICATION_COMPILE_CLIENT_CODE 1`
- L42 _macro_ `#define UE_REPLICATION_COMPILE_CLIENT_CODE 0`
- L46 _macro_ `#define UE_DEBUG_SLOW_REPLICATION 0`
- L50 _macro_ `#define UE_ALLOW_DEBUG_SLOW_REPLICATION 1`
- L52 _macro_ `#define UE_ALLOW_DEBUG_SLOW_REPLICATION 0`
- L56 _macro_ `#define UE_DEBUG_REPLICATION 0`
- L60 _macro_ `#define UE_ALLOW_DEBUG_REPLICATION 1`
- L62 _macro_ `#define UE_ALLOW_DEBUG_REPLICATION 0`
- L67 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassReplication, Log, All);`
- L67 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassReplication, Log, All);`
- L86 _typedef_ `typedef FCompactIndexedHandleManager<FMassReplicatedAgentHandle> FMassReplicatedAgentHandleManager;`
- L102 _typedef_ `typedef FIndexedHandleManager<FMassClientHandle> FMassClientHandleManager;`
- L181 _typedef_ `typedef THierarchicalHashGrid2D<2, 4, FMassEntityHandle> FReplicationHashGrid2D;` — 2 levels of hierarchy, 4 ratio between levels
