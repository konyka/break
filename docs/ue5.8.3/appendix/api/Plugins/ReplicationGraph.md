# Plugins / ReplicationGraph

- module root: `Plugins/Runtime/ReplicationGraph/Source`
- headers: 4; symbols: 1066
- symbol kinds: class=16, delegate=6, enum=5, enumerator=16, externvar=2, function=290, macro=20, member=327, namespace=3, prototype=314, struct=58, typedef=8, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, EngineSettings, NetCore, PerfCounters

### `Plugins/Runtime/ReplicationGraph/Source/Public/BasicReplicationGraph.h` (Public)


#### struct `FConnectionAlwaysRelevantNodePair`  
`struct FConnectionAlwaysRelevantNodePair`  
_L14-26_
- reflection: `USTRUCT()`
- L17 _public function_ `FConnectionAlwaysRelevantNodePair()`
- L18 _public function_ `FConnectionAlwaysRelevantNodePair(UNetConnection* InConnection, UReplicationGraphNode_AlwaysRelevant_ForConnection* InNode) : NetConnection(InConnection), Node(InNode)`
- L19 _public prototype_ `bool operator==(UNetConnection* InConnection) const;`
- L22 _public member_ `TObjectPtr<UNetConnection> NetConnection = nullptr;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<UReplicationGraphNode_AlwaysRelevant_ForConnection> Node = nullptr;` — `UPROPERTY()`

#### class `UBasicReplicationGraph`  
`class UBasicReplicationGraph :public UReplicationGraph`  
_L39-77_
- reflection: `UCLASS(transient, config=Engine)`
- inherits: `UReplicationGraph`
- desc: A basic implementation of replication graph. It only supports NetCullDistanceSquared, bAlwaysRelevant, bOnlyRelevantToOwner. These values cannot change per-actor at runtime. This is meant to provide a simple example implementation. More robust implementations will be required for more complex games. ShootGame is another example to check out. To enable this via ini: [/Script/OnlineSubsystemUtils.IpNetDriver] ReplicationDriverClassName="/Script/ReplicationGraph.BasicReplicationGraph"
- L45 _public prototype_ `UBasicReplicationGraph();`
- L47 _public prototype_ `virtual void InitGlobalActorClassSettings() override;`
- L48 _public prototype_ `virtual void InitGlobalGraphNodes() override;`
- L49 _public prototype_ `virtual void InitConnectionGraphNodes(UNetReplicationGraphConnection* RepGraphConnection) override;`
- L50 _public prototype_ `virtual void RouteAddNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalInfo) override;`
- L51 _public prototype_ `virtual void RouteRemoveNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo) override;`
- L54 _protected prototype_ `virtual void RouteRenameNetworkActorToNodes(const FRenamedReplicatedActorInfo& ActorInfo) override;`
- L57 _public prototype_ `virtual int32 ServerReplicateActors(float DeltaSeconds) override;`
- L60 _public member_ `TObjectPtr<UReplicationGraphNode_GridSpatialization2D> GridNode;` — `UPROPERTY()`
- L63 _public member_ `TObjectPtr<UReplicationGraphNode_ActorList> AlwaysRelevantNode;` — `UPROPERTY()`
- L66 _public member_ `TArray<FConnectionAlwaysRelevantNodePair> AlwaysRelevantForConnectionList;` — `UPROPERTY()`
- L70 _public member_ `TArray<TObjectPtr<AActor>> ActorsWithoutNetConnection;` — `UPROPERTY()` — Actors that are only supposed to replicate to their owning connection, but that did not have a connection on spawn
- L72 _public prototype_ `UReplicationGraphNode_AlwaysRelevant_ForConnection* GetAlwaysRelevantNodeForConnection(UNetConnection* Connection);`
- L75 _public prototype_ `void OnGameplayDebuggerOwnerChange(AGameplayDebuggerCategoryReplicator* Debugger, APlayerController* OldOwner);`

### `Plugins/Runtime/ReplicationGraph/Source/Public/ReplicationGraph.h` (Public)


#### class `UReplicationGraphNode`  
`class UReplicationGraphNode : public UObject`  
_L69-182_
- reflection: `UCLASS(MinimalAPI, abstract, transient, config=Engine)`
- inherits: `UObject`
- L75 _public prototype_ `UReplicationGraphNode();`
- L77 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L80 _public prototype_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& Actor ) PURE_VIRTUAL(UReplicationGraphNode::NotifyAddNetworkActor, );` — Called when a network actor is spawned or an actor changes replication status
- L83 _public prototype_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& Actor, bool bWarnIfNotFound=true) PURE_VIRTUAL(UReplicationGraphNode::NotifyRemoveNetworkActor, return false; );` — Called when a networked actor is being destroyed or no longer wants to replicate
- L90 _public prototype_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& Actor, bool bWarnIfNotFound=true) PURE_VIRTUAL(UReplicationGraphNode::NotifyActorRenamed, return false; );` — If Net.RepGraph.HandleDynamicActorRename is enabled, this is called when a dynamic actor is changing its outer. If the node maintains level information for actors, and if replicated actors may be renamed, the implementation needs to update its level info. Returns true if the actor was found & updated.
- L93 _public prototype_ `virtual void NotifyResetAllNetworkActors();` — Called when world changes or when all subclasses should dump any persistent data/lists about replicated actors here. (The new/next world will be set before this is called)
- L96 _public prototype_ `virtual void TearDown();` — Mark the node and all its children PendingKill
- L98 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) PURE_VIRTUAL(UReplicationGraphNode::GatherActorListsForConnection, );`
- L101 _public function_ `virtual void PrepareForReplication()` — Called once per frame prior to replication ONLY on root nodes (nodes created via UReplicationGraph::CreateNode) has RequiresPrepareForReplicationCall=true
- L104 _public prototype_ `virtual void GetAllActorsInNode_Debugging(TArray<FActorRepListType>& OutArray) const;` — Debugging only function to return a normal TArray of actor rep list (for logging, debug UIs, etc)
- L107 _public prototype_ `void VerifyActorReferences();` — Debugging only function to verify referenced actors (if any) are still valid.
- L111 _public function_ `bool GetRequiresPrepareForReplication() const`
- L113 _public function_ `void Initialize(const TSharedPtr<FReplicationGraphGlobalData>& InGraphGlobals)`
- L115 _public function_ `virtual UWorld* GetWorld() const override final`
- L117 _public prototype_ `virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const;`
- L119 _public function_ `virtual FString GetDebugString() const`
- L121 _public prototype_ `void DoCollectActorRepListStats(struct FActorRepListStatCollector& StatsCollector) const;`
- L125 _public function_ `template< class T > T* CreateChildNode()` — Allocates and initializes ChildNode of a specific type T. This is what you will want to call in your FCreateChildNodeFuncs.
- L135 _public function_ `template< class T > T* CreateChildNode(FName NodeBaseName)` — Allocates and initializes ChildNode of a specific type T with a given base name. This is what you will want to call in your FCreateChildNodeFuncs.
- L153 _public prototype_ `bool RemoveChildNode(UReplicationGraphNode* OutChildNode, UReplicationGraphNode::NodeOrdering NodeOrder=UReplicationGraphNode::NodeOrdering::IgnoreOrdering);` — Remove a child node from our list and flag it for destruction. Returns if the node was found or not
- L156 _public prototype_ `void CleanChildNodes(UReplicationGraphNode::NodeOrdering NodeOrder);` — Remove all null and about to be destroyed nodes from our list
- L163 _protected function_ `virtual void OnCollectActorRepListStats(struct FActorRepListStatCollector& StatsCollector) const` — Implement this to visit any FActorRepListRefView and FStreamingLevelActorListCollection your node implemented.
- L169 _protected function_ `virtual void VerifyActorReferencesInternal()` — Verify the validity of any potentially stale actor pointers. Used for debugging.
- L171 _protected prototype_ `bool VerifyActorReference(const FActorRepListType& Actor) const;`
- L176 _protected member_ `TArray< TObjectPtr<UReplicationGraphNode> > AllChildNodes;` — `UPROPERTY()`
- L178 _protected member_ `TSharedPtr<FReplicationGraphGlobalData> GraphGlobals;`
- L181 _protected member_ `bool bRequiresPrepareForReplicationCall = false;` — Determines if PrepareForReplication() is called. This currently must be set in the constructor, not dynamically.

#### enum `UReplicationGraphNode::NodeOrdering`  
`enum class NodeOrdering`  
_L146-150_
- desc: Node removal behavior
- L148 _public enumerator_ `IgnoreOrdering` — Use faster removal but may break node processing order
- L149 _public enumerator_ `KeepOrder` — Use slower removal but keep the node order intact

#### class `UReplicationGraphNode_ActorList`  
`class UReplicationGraphNode_ActorList : public UReplicationGraphNode`  
_L188-233_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode`
- desc: A Node that contains ReplicateActorLists. This contains 1 "base" list and a TArray of lists that are conditioned on a streaming level being loaded.
- L193 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L195 _public prototype_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& ActorInfo) override;`
- L197 _public prototype_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override;`
- L199 _public prototype_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override;`
- L201 _public prototype_ `virtual void NotifyResetAllNetworkActors() override;`
- L203 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L205 _public prototype_ `virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;`
- L207 _public prototype_ `virtual void GetAllActorsInNode_Debugging(TArray<FActorRepListType>& OutArray) const override;`
- L209 _public prototype_ `virtual void VerifyActorReferencesInternal() override;`
- L211 _public prototype_ `virtual void TearDown() override;`
- L214 _public prototype_ `bool RemoveNetworkActorFast(const FNewReplicatedActorInfo& ActorInfo);` — Removes the actor very quickly but breaks the list order
- L217 _public prototype_ `void DeepCopyActorListsFrom(const UReplicationGraphNode_ActorList* Source);` — Copies the contents of Source into this node. Note this does not copy child nodes, just the ReplicationActorList/StreamingLevelCollection lists on this node.
- L222 _protected prototype_ `void LogActorList(FReplicationGraphDebugInfo& DebugInfo) const;` — Just logs our ReplicationActorList and StreamingLevelCollection (not our child nodes). Useful when subclasses override LogNode
- L224 _protected prototype_ `virtual void OnCollectActorRepListStats(struct FActorRepListStatCollector& StatsCollector) const override;`
- L227 _protected member_ `FActorRepListRefView ReplicationActorList;` — The base list that most actors will go in
- L230 _protected member_ `FStreamingLevelActorListCollection StreamingLevelCollection;` — A collection of lists that streaming actors go in

#### class `UReplicationGraphNode_ActorListFrequencyBuckets`  
`class UReplicationGraphNode_ActorListFrequencyBuckets : public UReplicationGraphNode`  
_L239-315_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode`
- desc: A Node that contains ReplicateActorLists. This contains multiple buckets for non streaming level actors and will pull from each bucket on alternating frames. It is a way to broadly load balance.
- L269 _public member_ `static FSettings DefaultSettings;` — Default settings for all nodes. By being static, this allows games to easily override the settings are all nodes without having to subclass every graph node class
- L272 _public member_ `TSharedPtr<FSettings> Settings;` — Settings for this specific node. If not set we will fallback to the static/global DefaultSettings
- L274 _public function_ `const FSettings& GetSettings() const`
- L276 _public function_ `UReplicationGraphNode_ActorListFrequencyBuckets()`
- L278 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L280 _public prototype_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& ActorInfo) override;`
- L282 _public prototype_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override;`
- L284 _public prototype_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override;`
- L286 _public prototype_ `virtual void NotifyResetAllNetworkActors() override;`
- L288 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L290 _public prototype_ `virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;`
- L292 _public prototype_ `virtual void TearDown() override;`
- L294 _public prototype_ `virtual void GetAllActorsInNode_Debugging(TArray<FActorRepListType>& OutArray) const override;`
- L296 _public prototype_ `virtual void VerifyActorReferencesInternal() override;`
- L298 _public prototype_ `virtual void OnCollectActorRepListStats(struct FActorRepListStatCollector& StatsCollector) const override;`
- L300 _public prototype_ `void SetNonStreamingCollectionSize(const int32 NewSize);`
- L304 _protected prototype_ `void CheckRebalance();`
- L306 _protected member_ `int32 TotalNumNonStreamingActors = 0;`
- L309 _protected member_ `TArray<FActorRepListRefView, TInlineAllocator<2>> NonStreamingCollection;` — Non streaming actors go in one of these lists
- L312 _protected member_ `FStreamingLevelActorListCollection StreamingLevelCollection;` — A collection of lists that streaming actors go in

#### struct `UReplicationGraphNode_ActorListFrequencyBuckets::FSettings`  
`struct FSettings`  
_L245-266_
- L247 _public member_ `int32 NumBuckets = 3;`
- L248 _public member_ `int32 ListSize = 12;`
- L249 _public member_ `bool EnableFastPath = false;` — Whether to return lists as FastPath in "off frames". Defaults to false.
- L250 _public member_ `int32 FastPathFrameModulo = 1;` — Only do fast path if frame num % this = 0
- L260 _public member_ `TArray<FBucketThresholds, TInlineAllocator<4>> BucketThresholds;`
- L262 _public function_ `void CountBytes(FArchive& Ar) const`

#### struct `UReplicationGraphNode_ActorListFrequencyBuckets::FSettings::FBucketThresholds`  
`struct FBucketThresholds`  
_L253-258_
- desc: Threshold for dynamically balancing buckets bsaed on number of actors in this node. E.g, more buckets when there are more actors.
- L255 _public function_ `FBucketThresholds(int32 InMaxActors, int32 InNumBuckets) : MaxActors(InMaxActors), NumBuckets(InNumBuckets)`
- L256 _public member_ `int32 MaxActors;` — When num actors <= to MaxActors
- L257 _public member_ `int32 NumBuckets;` — use this NumBuckets

#### class `UReplicationGraphNode_DynamicSpatialFrequency`  
`class UReplicationGraphNode_DynamicSpatialFrequency : public UReplicationGraphNode_ActorList`  
_L322-421_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode_ActorList`
- desc: A node intended for dynamic (moving) actors where replication frequency is based on distance to the connection's view location
- L328 _public prototype_ `UReplicationGraphNode_DynamicSpatialFrequency();`
- L330 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L332 _public prototype_ `virtual void VerifyActorReferencesInternal() override;`
- L376 _public member_ `static FSettings DefaultSettings;` — Default settings used by all instance
- L377 _public member_ `FSettings* Settings;` — per instance override settings (optional)
- L379 _public function_ `FSettings& GetSettings()`
- L381 _public member_ `const char* CSVStatName;` — Statname to use for tracking the gather/prioritizing phase of this node
- L406 _protected member_ `TArray<FDynamicSpatialFrequency_SortedItem> SortedReplicationList;` — Working area for our sorted replication list. Reset each frame for each connection as we build the list
- L409 _protected member_ `int32 NumExpectedReplicationsThisFrame = 0;` — Working ints for adaptive load balancing. Does not count actors that rep every frame
- L410 _protected member_ `int32 NumExpectedReplicationsNextFrame = 0;`
- L412 _protected member_ `bool IgnoreCullDistance = false;`
- L414 _protected prototype_ `virtual void GatherActors(const FActorRepListRefView& RepList, FGlobalActorReplicationInfoMap& GlobalMap, FPerConnectionActorInfoMap& ConnectionMap, const FConnectionGatherActorListParameters& Params, UNetConnection* NetConnection);`
- L415 _protected prototype_ `virtual void GatherActors_DistanceOnly(const FActorRepListRefView& RepList, FGlobalActorReplicationInfoMap& GlobalMap, FPerConnectionActorInfoMap& ConnectionMap, const FConnectionGatherActorListParameters& Params);`
- L418 _protected prototype_ `void CalcFrequencyForActor(AActor* Actor, UReplicationGraph* RepGraph, UNetConnection* NetConnection, FGlobalActorReplicationInfo& GlobalInfo, FPerConnectionActorInfoMap& ConnectionMap, FSettings& MySettings, const FNetViewerArray& Viewers, const uint32 FrameNum, int32 ExistingItemIndex);` — `UE_DEPRECATED(5.2, "This function was replaced with a version that needs to receive a UNetReplicationGraphConnection instead of a NetConnection")`
- L420 _protected prototype_ `void CalcFrequencyForActor(AActor* Actor, UReplicationGraph* RepGraph, const UNetReplicationGraphConnection& RepGraphConnection, FGlobalActorReplicationInfo& GlobalInfo, FPerConnectionActorInfoMap& ConnectionMap, FSettings& MySettings, const FNetViewerArray& Viewers, const uint32 FrameNum, int32 ExistingItemIndex);`

#### struct `UReplicationGraphNode_DynamicSpatialFrequency::FSpatializationZone`  
`struct FSpatializationZone`  
_L336-361_
- L339 _public function_ `FSpatializationZone(float InMinDotProduct, float InMinDistPct, float InMaxDistPct, uint32 InMinRepPeriod, uint32 InMaxRepPeriod, uint32 InMinRepPeriod_FastPath, uint32 InMaxRepPeriod_FastPath) : MinDotProduct(InMinDotProduct), MinDistPct(InMinDistPct), MaxDistPct(InMaxDistPct), MinRepPeriod(InMinRepPeriod), MaxRepPeriod(InMaxRepPeriod), FastPath_MinRepPeriod(InMinRepPeriod_FastPath), FastPath_MaxRepPeriod(InMaxRepPeriod_FastPath)` — Init directly
- L343 _public function_ `FSpatializationZone(float InMinDotProduct, float InMinDistPct, float InMaxDistPct, float InMinRepHz, float InMaxRepHz, float InMinRepHz_FastPath, float InMaxRepHz_FastPath, float TickRate) : MinDotProduct(InMinDotProduct), MinDistPct(InMinDistPct), MaxDistPct(InMaxDistPct), MinRepPeriod(HzToFrm(InMinRepHz,TickRate)), MaxRepPeriod(HzToFrm(InMaxRepHz,TickRate)), FastPath_MinRepPeriod(HzToFrm(InMinRepHz_FastPath,TickRate)), FastPath_MaxRepPeriod(HzToFrm(InMaxRepHz_FastPath,TickRate))` — Init based on target frame rate
- L347 _public member_ `float MinDotProduct = 1.f;` — Must have dot product >= to this to be in this zone
- L348 _public member_ `float MinDistPct = 0.f;` — Min distance as pct of per-connection culldistance, to map to MinRepPeriod
- L349 _public member_ `float MaxDistPct = 1.f;` — Max distance as pct of per-connection culldistance, to map to MaxRepPeriod
- L351 _public member_ `uint32 MinRepPeriod = 5;`
- L352 _public member_ `uint32 MaxRepPeriod = 10;`
- L354 _public member_ `uint32 FastPath_MinRepPeriod = 1;`
- L355 _public member_ `uint32 FastPath_MaxRepPeriod = 5;`
- L357 _public function_ `static uint32 HzToFrm(float Hz, float TargetFrameRate)`

#### struct `UReplicationGraphNode_DynamicSpatialFrequency::FSettings`  
`struct FSettings`  
_L363-374_
- L365 _public function_ `FSettings() :MaxBitsPerFrame(0), MaxNearestActors(-1)`
- L367 _public function_ `FSettings(TArrayView<FSpatializationZone> InZoneSettings, TArrayView<FSpatializationZone> InZoneSettings_NonFastSharedActors, int64 InMaxBitsPerFrame, int32 InMaxNearestActors = -1) : ZoneSettings(InZoneSettings), ZoneSettings_NonFastSharedActors(InZoneSettings_NonFastSharedActors), MaxBitsPerFrame(InMaxBitsPerFrame), MaxNearestActors(InMaxNearestActors)`
- L370 _public member_ `TArrayView<FSpatializationZone> ZoneSettings;`
- L371 _public member_ `TArrayView<FSpatializationZone> ZoneSettings_NonFastSharedActors;` — Zone Settings for actors that do not support FastShared replication.
- L372 _public member_ `int64 MaxBitsPerFrame;`
- L373 _public member_ `int32 MaxNearestActors;` — Only replicate the X nearest actors to a connection in this node. -1 = no limit.

#### struct `UReplicationGraphNode_DynamicSpatialFrequency::FDynamicSpatialFrequency_SortedItem`  
`struct FDynamicSpatialFrequency_SortedItem`  
_L385-403_
- L387 _public function_ `FDynamicSpatialFrequency_SortedItem()`
- L388 _public function_ `FDynamicSpatialFrequency_SortedItem(AActor* InActor, int32 InFramesTillReplicate, bool InEnableFastPath, FGlobalActorReplicationInfo* InGlobal, FConnectionReplicationActorInfo* InConnection ) : Actor(InActor), FramesTillReplicate(InFramesTillReplicate), EnableFastPath(InEnableFastPath), GlobalInfo(InGlobal), ConnectionInfo(InConnection)`
- L391 _public function_ `FDynamicSpatialFrequency_SortedItem(AActor* InActor, int32 InDistance, FGlobalActorReplicationInfo* InGlobal) : Actor(InActor), FramesTillReplicate(InDistance), GlobalInfo(InGlobal)`
- L394 _public function_ `bool operator<(const FDynamicSpatialFrequency_SortedItem& Other) const`
- L396 _public member_ `AActor* Actor = nullptr;`
- L398 _public member_ `int32 FramesTillReplicate = 0;` — Note this also serves as "Distance Sq" when doing the FSettings::MaxNearestActors pass.
- L399 _public member_ `bool EnableFastPath = false;`
- L401 _public member_ `FGlobalActorReplicationInfo* GlobalInfo = nullptr;`
- L402 _public member_ `FConnectionReplicationActorInfo* ConnectionInfo = nullptr;`

#### class `UReplicationGraphNode_ConnectionDormancyNode`  
`class UReplicationGraphNode_ConnectionDormancyNode : public UReplicationGraphNode_ActorList`  
_L428-480_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode_ActorList`
- desc: Removes dormant (on connection) actors from its rep lists
- L440 _public prototype_ `static void SetNumFramesUntilObsolete(uint32 NumFrames);` — This setting determines the number of frames from the last Gather call when we consider a node obsolete. The default value of 0 disables this condition. Enable this to reduce the memory footprint of the RepGraph and optimize the exponential cost of dormancy events (the more each connection moves around the grid cell the more each dormancy events is listened to). Inversely if clients go back and forth across the same cell multiple times the cost of the first Gather of newly created cell is very high (it rechecks all dormant actors in the cell before removing them). This means this optimization is ideal only if you know the clients can't go back to previously visited cells, or that they do so very infrequently.
- L444 _public function_ `void InitConnectionNode(const FRepGraphConnectionKey& InConnectionOwner, uint32 CurrentFrame)`
- L450 _public prototype_ `virtual void TearDown() override;`
- L452 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L453 _public prototype_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool WarnIfNotFound) override;`
- L454 _public prototype_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override;`
- L455 _public prototype_ `virtual void NotifyResetAllNetworkActors() override;`
- L456 _public prototype_ `virtual void VerifyActorReferencesInternal() override;`
- L458 _public prototype_ `void NotifyActorDormancyFlush(FActorRepListType Actor);`
- L460 _public prototype_ `void OnClientVisibleLevelNameAdd(FName LevelName, UWorld* World);`
- L462 _public prototype_ `bool IsNodeObsolete(uint32 CurrentFrame) const;`
- L466 _private member_ `static uint32 NumFramesUntilObsolete;`
- L470 _private member_ `FRepGraphConnectionKey ConnectionOwner;`
- L472 _private member_ `uint32 LastGatheredFrame = 0;`
- L474 _private prototype_ `void ConditionalGatherDormantActorsForConnection(FActorRepListRefView& ConnectionRepList, const FConnectionGatherActorListParameters& Params, FActorRepListRefView* RemovedList);`
- L476 _private member_ `int32 TrickleStartCounter = 10;`
- L479 _private member_ `FStreamingLevelActorListCollection RemovedStreamingLevelActorListCollection;` — Tracks actors we've removed in this per-connection node, so that we can restore them if the streaming level is unloaded and reloaded.

#### class `UReplicationGraphNode_DormancyNode`  
`class UReplicationGraphNode_DormancyNode : public UReplicationGraphNode_ActorList`  
_L485-532_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode_ActorList`
- desc: Stores per-connection copies of a main actor list. Skips and removes elements from per connection list that are fully dormant
- L492 _public member_ `static FVector::FReal MaxZForConnection;` — Connection Z location has to be < this for ConnectionsNodes to be made.
- L496 _public function_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& ActorInfo) override`
- L497 _public function_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override`
- L498 _public function_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override`
- L499 _public prototype_ `virtual void NotifyResetAllNetworkActors() override;`
- L501 _public prototype_ `void AddDormantActor(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalInfo);`
- L502 _public prototype_ `void RemoveDormantActor(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo);`
- L503 _public prototype_ `void RenameDormantActor(const FRenamedReplicatedActorInfo& ActorInfo);`
- L505 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L507 _public prototype_ `void OnActorDormancyFlush(FActorRepListType Actor, FGlobalActorReplicationInfo& GlobalInfo);`
- L509 _public prototype_ `void ConditionalGatherDormantDynamicActors(FActorRepListRefView& RepList, const FConnectionGatherActorListParameters& Params, FActorRepListRefView* RemovedList, bool bEnforceReplistUniqueness = false, FActorRepListRefView* RemoveFromList = nullptr);`
- L511 _public prototype_ `UReplicationGraphNode_ConnectionDormancyNode* GetExistingConnectionNode(const FConnectionGatherActorListParameters& Params);`
- L513 _public prototype_ `UReplicationGraphNode_ConnectionDormancyNode* GetConnectionNode(const FConnectionGatherActorListParameters& Params);`
- L517 _private prototype_ `UReplicationGraphNode_ConnectionDormancyNode* CreateConnectionNode(const FConnectionGatherActorListParameters& Params);`
- L520 _private typedef_ `typedef TFunction<void(UReplicationGraphNode_ConnectionDormancyNode*)> FConnectionDormancyNodeFunction;` — Function called on every ConnectionDormancyNode in our list
- L526 _private prototype_ `void CallFunctionOnValidConnectionNodes(FConnectionDormancyNodeFunction Function);` — Iterates over all ConnectionDormancyNodes and calls the function on those still valid. If the node is considered obsolete, the function will destroy or skip over the ConnectionDormancyNode
- L530 _private typedef_ `typedef TSortedMap<FRepGraphConnectionKey, UReplicationGraphNode_ConnectionDormancyNode*> FConnectionDormancyNodeMap;`
- L531 _private member_ `FConnectionDormancyNodeMap ConnectionNodes;`

#### class `UReplicationGraphNode_GridCell`  
`class UReplicationGraphNode_GridCell : public UReplicationGraphNode_ActorList`  
_L535-574_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode_ActorList`
- L541 _public function_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& ActorInfo) override`
- L542 _public function_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override`
- L543 _public prototype_ `virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;`
- L544 _public prototype_ `virtual void GetAllActorsInNode_Debugging(TArray<FActorRepListType>& OutArray) const override;`
- L546 _public prototype_ `void AddStaticActor(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalRepInfo, bool bParentNodeHandlesDormancyChange);`
- L547 _public prototype_ `void AddDynamicActor(const FNewReplicatedActorInfo& ActorInfo);`
- L549 _public prototype_ `void RemoveStaticActor(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo, bool bWasAddedAsDormantActor);`
- L550 _public prototype_ `void RemoveDynamicActor(const FNewReplicatedActorInfo& ActorInfo);`
- L552 _public prototype_ `void RenameStaticActor(const FRenamedReplicatedActorInfo& ActorInfo, bool bWasAddedAsDormantActor);`
- L553 _public prototype_ `void RenameDynamicActor(const FRenamedReplicatedActorInfo& ActorInfo);`
- L556 _public member_ `TFunction<UReplicationGraphNode*(UReplicationGraphNode_GridCell* Parent)> CreateDynamicNodeOverride;` — Allow graph to override function for creating the dynamic node in the cell
- L558 _public prototype_ `UReplicationGraphNode_DormancyNode* GetDormancyNode(bool bInCreateIfMissing = true);`
- L563 _private member_ `TObjectPtr<UReplicationGraphNode> DynamicNode = nullptr;` — `UPROPERTY()`
- L566 _private member_ `TObjectPtr<UReplicationGraphNode_DormancyNode> DormancyNode = nullptr;` — `UPROPERTY()`
- L568 _private prototype_ `UReplicationGraphNode* GetDynamicNode();`
- L570 _private prototype_ `void OnActorDormancyFlush(FActorRepListType Actor, FGlobalActorReplicationInfo& GlobalInfo, UReplicationGraphNode_DormancyNode* DormancyNode );`
- L572 _private prototype_ `void ConditionalCopyDormantActors(FActorRepListRefView& FromList, UReplicationGraphNode_DormancyNode* ToNode);`
- L573 _private prototype_ `void OnStaticActorNetDormancyChange(FActorRepListType Actor, FGlobalActorReplicationInfo& GlobalInfo, ENetDormancy NewVlue, ENetDormancy OldValue);`

#### class `UReplicationGraphNode_GridSpatialization2D`  
`class UReplicationGraphNode_GridSpatialization2D : public UReplicationGraphNode`  
_L579-765_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode`
- L585 _public prototype_ `UReplicationGraphNode_GridSpatialization2D();`
- L587 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L589 _public prototype_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& Actor) override;`
- L590 _public prototype_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override;`
- L591 _public prototype_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& Actor, bool bWarnIfNotFound=true) override;`
- L592 _public prototype_ `virtual void NotifyResetAllNetworkActors() override;`
- L593 _public prototype_ `virtual void PrepareForReplication() override;`
- L594 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L595 _public prototype_ `virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;`
- L596 _public prototype_ `virtual void VerifyActorReferencesInternal() override;`
- L598 _public function_ `void AddActor_Static(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo)`
- L599 _public function_ `void AddActor_Dynamic(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo)`
- L600 _public prototype_ `void AddActor_Dormancy(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo);`
- L602 _public prototype_ `void RemoveActor_Static(const FNewReplicatedActorInfo& ActorInfo);`
- L603 _public function_ `void RemoveActor_Dynamic(const FNewReplicatedActorInfo& ActorInfo)`
- L604 _public prototype_ `void RemoveActor_Dormancy(const FNewReplicatedActorInfo& ActorInfo);`
- L606 _public prototype_ `void RenameActor_Static(const FRenamedReplicatedActorInfo& ActorInfo);`
- L607 _public prototype_ `void RenameActor_Dynamic(const FRenamedReplicatedActorInfo& ActorInfo);`
- L608 _public prototype_ `void RenameActor_Dormancy(const FRenamedReplicatedActorInfo& ActorInfo);`
- L611 _public prototype_ `virtual void NotifyActorCullDistChange(AActor* Actor, FGlobalActorReplicationInfo& GlobalInfo, float OldDist);` — Called if cull distance changes. Note the caller must update Global/Connection actor rep infos. This just changes cached state within this node
- L613 _public member_ `float CellSize;`
- L614 _public member_ `FVector2D SpatialBias;`
- L615 _public member_ `double ConnectionMaxZ;` — Connection locations have to be <= to this to pull from the grid
- L621 _public prototype_ `void SetBiasAndGridBounds(const FBox& GridBox);` — When the GridBounds is set we limit the creation of cells to be exclusively inside the passed region. Viewers who gather nodes outside this region will be clamped to the closest cell inside the box. Actors whose location is outside the box will be clamped to the closest cell inside the box.
- L624 _public member_ `TFunction<UReplicationGraphNode_GridCell*(UReplicationGraphNode_GridSpatialization2D* Parent)> CreateCellNodeOverride;` — Allow graph to override function for creating cell nodes in this grid.
- L626 _public function_ `void ForceRebuild()`
- L629 _public function_ `void AddToClassRebuildDenyList(UClass* Class)` — Marks a class as preventing spatial rebuilds when an instance leaves the grid
- L632 _public member_ `TArray<FString> DebugActorNames;`
- L636 _public member_ `bool bDestroyDormantDynamicActors = true;` — When enabled the RepGraph tells clients to destroy dormant dynamic actors when they go out of relevancy.
- L638 _public member_ `int32 DestroyDormantDynamicActorsCellTTL = 1;` — How many frames dormant actors should be outside relevancy range to be destroyed
- L640 _public member_ `int32 ReplicatedDormantDestructionInfosPerFrame = MAX_int32;` — Optimization to spread cost over multiple frames
- L645 _protected prototype_ `virtual void AddActorInternal_Dynamic(const FNewReplicatedActorInfo& ActorInfo);` — For adding new actor to the graph
- L646 _protected prototype_ `virtual void AddActorInternal_Static(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo, bool IsDormancyDriven);` — Can differ the actual call to implementation if actor is not ready
- L647 _protected prototype_ `virtual void AddActorInternal_Static_Implementation(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo, bool IsDormancyDriven);`
- L649 _protected prototype_ `virtual void RemoveActorInternal_Dynamic(const FNewReplicatedActorInfo& Actor);`
- L650 _protected prototype_ `virtual void RemoveActorInternal_Static(const FNewReplicatedActorInfo& Actor, FGlobalActorReplicationInfo& ActorRepInfo, bool WasAddedAsDormantActor);`
- L654 _private prototype_ `bool WillActorLocationGrowSpatialBounds(const FVector& Location) const;`
- L657 _private prototype_ `void HandleActorOutOfSpatialBounds(AActor* Actor, const FVector& Location3D, const bool bStaticActor);` — Called when an actor is out of spatial bounds
- L660 _private member_ `FBox GridBounds;` — Optional value to limit the grid to a specific region
- L663 _private member_ `TClassMap<bool> ClassRebuildDenyList;` — Classmap of actor classes which CANNOT force a rebuild of the spatialization tree. They will be clamped instead. E.g, projectiles.
- L682 _private member_ `TMap<FActorRepListType, FCachedDynamicActorInfo> DynamicSpatializedActors;`
- L692 _private member_ `TMap<FActorRepListType, FCachedStaticActorInfo> StaticSpatializedActors;`
- L702 _private member_ `TArray<FPendingStaticActors> PendingStaticSpatializedActors;`
- L704 _private prototype_ `void OnNetDormancyChange(FActorRepListType Actor, FGlobalActorReplicationInfo& GlobalInfo, ENetDormancy NewVlue, ENetDormancy OldValue);`
- L706 _private prototype_ `void PutStaticActorIntoCell(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo, bool bDormancyDriven);`
- L708 _private function_ `UReplicationGraphNode_GridCell* GetCellNode(UReplicationGraphNode_GridCell*& NodePtr)`
- L725 _private member_ `TArray< TArray<UReplicationGraphNode_GridCell*> > Grid;`
- L727 _private function_ `TArray<UReplicationGraphNode_GridCell*>& GetGridX(int32 X)`
- L736 _private function_ `UReplicationGraphNode_GridCell*& GetCell(TArray<UReplicationGraphNode_GridCell*>& GridX, int32 Y)`
- L745 _private function_ `UReplicationGraphNode_GridCell*& GetCell(int32 X, int32 Y)`
- L751 _private member_ `bool bNeedsRebuild = false;`
- L753 _private prototype_ `void GetGridNodesForActor(FActorRepListType Actor, const FGlobalActorReplicationInfo& ActorRepInfo, TArray<UReplicationGraphNode_GridCell*>& OutNodes);`
- L754 _private prototype_ `void GetGridNodesForActor(FActorRepListType Actor, const UReplicationGraphNode_GridSpatialization2D::FActorCellInfo& CellInfo, TArray<UReplicationGraphNode_GridCell*>& OutNodes);`
- L756 _private prototype_ `FActorCellInfo GetCellInfoForActor(FActorRepListType Actor, const FVector& Location3D, float CullDistance);`
- L759 _private member_ `TArray<UReplicationGraphNode_GridCell*> GatheredNodes;` — This is a reused TArray for gathering actor nodes. Just to prevent using a stack based TArray everywhere or static/reset patten.
- L762 _private member_ `FActorRepListRefView GatheredActors;` — This is a reused FActorRepListRefView for gathering actors for dormancy cleanup. Just to prevent using a stack based FActorRepListRefView or static/reset patten.

#### struct `UReplicationGraphNode_GridSpatialization2D::FActorCellInfo`  
`struct FActorCellInfo`  
_L665-673_
- L667 _public function_ `bool IsValid() const`
- L668 _public function_ `void Reset()`
- L669 _public member_ `int32 StartX=-1;`
- L670 _public member_ `int32 StartY;`
- L671 _public member_ `int32 EndX;`
- L672 _public member_ `int32 EndY;`

#### struct `UReplicationGraphNode_GridSpatialization2D::FCachedDynamicActorInfo`  
`struct FCachedDynamicActorInfo`  
_L675-680_
- L677 _public function_ `FCachedDynamicActorInfo(const FNewReplicatedActorInfo& InInfo) : ActorInfo(InInfo)`
- L678 _public member_ `FNewReplicatedActorInfo ActorInfo;`
- L679 _public member_ `FActorCellInfo CellInfo;`

#### struct `UReplicationGraphNode_GridSpatialization2D::FCachedStaticActorInfo`  
`struct FCachedStaticActorInfo`  
_L685-690_
- L687 _public function_ `FCachedStaticActorInfo(const FNewReplicatedActorInfo& InInfo, bool bInDormDriven) : ActorInfo(InInfo), bDormancyDriven(bInDormDriven)`
- L688 _public member_ `FNewReplicatedActorInfo ActorInfo;`
- L689 _public member_ `bool bDormancyDriven = false;` — This actor will be removed from static actor list if it becomes non dormant.

#### struct `UReplicationGraphNode_GridSpatialization2D::FPendingStaticActors`  
`struct FPendingStaticActors`  
_L695-701_
- desc: Static spatialized actors that were not fully initialized when registering with this node. We differ their placement in the grid until the next frame
- L697 _public function_ `FPendingStaticActors(const FActorRepListType& InActor, const bool InDormancyDriven) : Actor(InActor), DormancyDriven(InDormancyDriven)`
- L698 _public function_ `bool operator==(const FActorRepListType& InActor) const`
- L699 _public member_ `FActorRepListType Actor;`
- L700 _public member_ `bool DormancyDriven;`

#### class `UReplicationGraphNode_AlwaysRelevant`  
`class UReplicationGraphNode_AlwaysRelevant : public UReplicationGraphNode`  
_L771-795_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode`
- L777 _public prototype_ `UReplicationGraphNode_AlwaysRelevant();`
- L779 _public function_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& Actor) override`
- L780 _public function_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override`
- L781 _public function_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& Actor, bool bWarnIfNotFound=true) override`
- L782 _public function_ `virtual void NotifyResetAllNetworkActors() override`
- L783 _public prototype_ `virtual void PrepareForReplication() override;`
- L784 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L786 _public prototype_ `void AddAlwaysRelevantClass(UClass* Class);`
- L791 _protected member_ `TObjectPtr<UReplicationGraphNode> ChildNode = nullptr;` — `UPROPERTY()`
- L794 _protected member_ `TArray<UClass*> AlwaysRelevantClasses;` — Explicit list of classes that are always relevant. This

#### struct `FAlwaysRelevantActorInfo`  
`struct UE_DEPRECATED(5.2, "No longer used") FAlwaysRelevantActorInfo`  
_L800-817_
- reflection: `USTRUCT()`
- L805 _public member_ `TObjectPtr<const UNetConnection> Connection = nullptr;` — `UPROPERTY()`
- L808 _public member_ `TObjectPtr<AActor> LastViewer = nullptr;` — `UPROPERTY()`
- L811 _public member_ `TObjectPtr<AActor> LastViewTarget = nullptr;` — `UPROPERTY()`
- L813 _public function_ `bool operator==(UNetConnection* Other) const`

#### struct `FCachedAlwaysRelevantActorInfo`  
`struct FCachedAlwaysRelevantActorInfo`  
_L819-823_
- L821 _public member_ `TWeakObjectPtr<AActor> LastViewer;`
- L822 _public member_ `TWeakObjectPtr<AActor> LastViewTarget;`

#### class `UReplicationGraphNode_AlwaysRelevant_ForConnection`  
`class UReplicationGraphNode_AlwaysRelevant_ForConnection : public UReplicationGraphNode_ActorList`  
_L827-866_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode_ActorList`
- desc: Adds actors that are always relevant for a connection. This engine version just adds the PlayerController and ViewTarget (usually the pawn)
- L833 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L835 _public prototype_ `virtual void TearDown() override;`
- L838 _public member_ `FActorRepListRefView ReplicationActorList;` — Rebuilt-every-frame list based on UNetConnection state
- L844 _public member_ `TArray<FAlwaysRelevantActorInfo> PastRelevantActors;` — `UE_DEPRECATED(5.2, "Please use PastRelevantActorMap instead")` — `UPROPERTY()` — List of previously (or currently if nothing changed last tick) focused actor data per connection
- L848 _public function_ `template<typename KeyType, typename ValueType> static void CleanupCachedRelevantActors(TMap<TObjectKey<KeyType>, ValueType>& ActorMap)`
- L860 _protected prototype_ `virtual void OnCollectActorRepListStats(struct FActorRepListStatCollector& StatsCollector) const override;`
- L862 _protected prototype_ `void AddCachedRelevantActor(const FConnectionGatherActorListParameters& Params, AActor* NewActor, TWeakObjectPtr<AActor>& LastActor);`
- L863 _protected prototype_ `void UpdateCachedRelevantActor(const FConnectionGatherActorListParameters& Params, AActor* NewActor, TWeakObjectPtr<AActor>& LastActor);`
- L865 _protected member_ `TMap<TObjectKey<UNetConnection>, FCachedAlwaysRelevantActorInfo> PastRelevantActorMap;`

#### struct `FTearOffActorInfo`  
`struct FTearOffActorInfo`  
_L872-884_
- reflection: `USTRUCT()`
- L875 _public function_ `FTearOffActorInfo() : TearOffFrameNum(0), Actor(nullptr), bHasReppedOnce(false)`
- L876 _public function_ `FTearOffActorInfo(AActor* InActor, uint32 InTearOffFrameNum) : TearOffFrameNum(InTearOffFrameNum), Actor(InActor), bHasReppedOnce(false)`
- L878 _public member_ `uint32 TearOffFrameNum;`
- L881 _public member_ `TObjectPtr<AActor> Actor;` — `UPROPERTY()`
- L883 _public member_ `bool bHasReppedOnce;`

#### class `UReplicationGraphNode_TearOff_ForConnection`  
`class UReplicationGraphNode_TearOff_ForConnection : public UReplicationGraphNode`  
_L888-914_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UReplicationGraphNode`
- desc: Manages actors that are Tear Off. We will try to replicate these actors one last time to each connection.
- L893 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L895 _public function_ `virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& ActorInfo) override`
- L896 _public function_ `virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound=true) override`
- L897 _public function_ `virtual bool NotifyActorRenamed(const FRenamedReplicatedActorInfo& Actor, bool bWarnIfNotFound=true) override`
- L898 _public function_ `virtual void NotifyResetAllNetworkActors() override`
- L899 _public prototype_ `virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;`
- L900 _public prototype_ `virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;`
- L901 _public prototype_ `virtual void VerifyActorReferencesInternal() override;`
- L903 _public prototype_ `void NotifyTearOffActor(AActor* Actor, uint32 FrameNum);`
- L907 _public member_ `TArray<FTearOffActorInfo> TearOffActors;` — `UPROPERTY()` — Fixme: not safe to have persistent FActorRepListrefViews yet, so need a uproperty based list to hold the persistent items.
- L909 _public member_ `FActorRepListRefView ReplicationActorList;`
- L913 _protected prototype_ `virtual void OnCollectActorRepListStats(struct FActorRepListStatCollector& StatsCollector) const override;`

#### class `UReplicationGraph`  
`class UReplicationGraph : public UReplicationDriver`  
_L920-1231_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `UReplicationDriver`
- desc: Manages actor replication for an entire world / net driver
- L926 _public prototype_ `UReplicationGraph();`
- L928 _public prototype_ `virtual void BeginDestroy() override;`
- L932 _public member_ `TSubclassOf<UNetReplicationGraphConnection> ReplicationConnectionManagerClass;` — `UPROPERTY(Config)` — The per-connection manager class to instantiate. This will be read off the instantiated UNetReplicationManager.
- L935 _public member_ `TObjectPtr<UNetDriver> NetDriver;` — `UPROPERTY()`
- L939 _public member_ `TArray<TObjectPtr<UNetReplicationGraphConnection>> Connections;` — `UPROPERTY()` — List of connection managers. This list is not sorted and not stable.
- L943 _public member_ `TArray<TObjectPtr<UNetReplicationGraphConnection>> PendingConnections;` — `UPROPERTY()` — ConnectionManagers that we have created but haven't officially been added to the net driver's ClientConnection list. This is a  hack for silly order of initialization issues.
- L946 _public member_ `float DestructInfoMaxDistanceSquared = 15000.f * 15000.f;` — The max distance between an FActorDestructionInfo and a connection that we will replicate.
- L949 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L955 _public prototype_ `virtual void SetRepDriverWorld(UWorld* InWorld) override;`
- L956 _public prototype_ `virtual void InitForNetDriver(UNetDriver* InNetDriver) override;`
- L957 _public prototype_ `virtual void InitializeActorsInWorld(UWorld* InWorld) override;`
- L958 _public function_ `virtual void ResetGameWorldState() override`
- L959 _public prototype_ `virtual void TearDown() override;`
- L962 _public prototype_ `virtual void AddClientConnection(UNetConnection* NetConnection) override;` — Called by the NetDriver when the client connection is ready/added to the NetDriver's client connection list
- L963 _public prototype_ `virtual void RemoveClientConnection(UNetConnection* NetConnection) override;`
- L964 _public prototype_ `virtual void AddNetworkActor(AActor* Actor) override;`
- L965 _public prototype_ `virtual void RemoveNetworkActor(AActor* Actor) override;`
- L966 _public prototype_ `virtual void ForceNetUpdate(AActor* Actor) override;`
- L967 _public prototype_ `virtual void FlushNetDormancy(AActor* Actor, bool bWasDormInitial) override;`
- L968 _public prototype_ `virtual void NotifyActorTearOff(AActor* Actor) override;`
- L969 _public prototype_ `virtual void NotifyActorFullyDormantForConnection(AActor* Actor, UNetConnection* Connection) override;`
- L970 _public prototype_ `virtual void NotifyActorDormancyChange(AActor* Actor, ENetDormancy OldDormancyState) override;`
- L971 _public function_ `virtual void NotifyDestructionInfoCreated(AActor* Actor, FActorDestructionInfo& DestructionInfo) override`
- L972 _public prototype_ `virtual void NotifyActorRenamed(AActor* Actor, UObject* PreviousOuter, FName PreviousName) override;`
- L973 _public prototype_ `virtual void SetRoleSwapOnReplicate(AActor* Actor, bool bSwapRoles) override;`
- L974 _public prototype_ `virtual bool ProcessRemoteFunction(class AActor* Actor, UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack, class UObject* SubObject) override;`
- L975 _public prototype_ `virtual int32 ServerReplicateActors(float DeltaSeconds) override;`
- L976 _public prototype_ `virtual void PostTickDispatch() override;`
- L979 _public prototype_ `virtual void RouteAddNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalInfo);`
- L981 _public prototype_ `virtual void RouteRemoveNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo);`
- L983 _public prototype_ `bool IsConnectionReady(UNetConnection* Connection);`
- L985 _public prototype_ `void SetActorDiscoveryBudget(int32 ActorDiscoveryBudgetInKBytesPerSec);`
- L988 _public prototype_ `void SetAllCullDistanceSettingsForActor(const FActorRepListType& Actor, float CullDistanceSquared);` — Sets the global and connection-specific cull distance setting of this actor
- L991 _public function_ `virtual void PrintGraphDebugInfo_OnInvalidActor()` — Debugging facility called when invalid actor is being detected on one of many replication paths.
- L997 _public function_ `template< class T > T* CreateNewNode()` — Creates a new node for the graph. This and UReplicationNode::CreateChildNode should be the only things that create the graph node UObjects
- L1006 _public function_ `template< class T > T* CreateNewNode(FName NodeBaseName)` — Creates a new node for the graph with a given base name. This and UReplicationNode::CreateChildNode should be the only things that create the graph node UObjects
- L1015 _public prototype_ `void AddGlobalGraphNode(UReplicationGraphNode* GraphNode);` — Add a global node to the root that will have a chance to emit actor rep lists for all connections
- L1016 _public prototype_ `void RemoveGlobalGraphNode(UReplicationGraphNode* GraphNode);`
- L1019 _public prototype_ `void AddConnectionGraphNode(UReplicationGraphNode* GraphNode, UNetReplicationGraphConnection* ConnectionManager);` — Associate a node to a specific connection. When this connection replicates, this GraphNode will get a chance to add.
- L1020 _public function_ `void AddConnectionGraphNode(UReplicationGraphNode* GraphNode, UNetConnection* NetConnection)`
- L1022 _public prototype_ `void RemoveConnectionGraphNode(UReplicationGraphNode* GraphNode, UNetReplicationGraphConnection* ConnectionManager);`
- L1023 _public function_ `void RemoveConnectionGraphNode(UReplicationGraphNode* GraphNode, UNetConnection* NetConnection)`
- L1027 _public function_ `virtual UWorld* GetWorld() const override final`
- L1029 _public prototype_ `virtual void LogGraph(FReplicationGraphDebugInfo& DebugInfo) const;`
- L1030 _public prototype_ `virtual void LogGlobalGraphNodes(FReplicationGraphDebugInfo& DebugInfo) const;`
- L1031 _public prototype_ `virtual void LogConnectionGraphNodes(FReplicationGraphDebugInfo& DebugInfo) const;`
- L1033 _public prototype_ `virtual void CollectRepListStats(struct FActorRepListStatCollector& StatCollector) const;`
- L1035 _public prototype_ `void VerifyActorReferences();`
- L1037 _public function_ `const TSharedPtr<FReplicationGraphGlobalData>& GetGraphGlobals() const`
- L1039 _public function_ `uint32 GetReplicationGraphFrame() const`
- L1042 _public prototype_ `virtual class AReplicationGraphDebugActor* CreateDebugActor() const;`
- L1046 _public prototype_ `void DebugPrintCullDistances(UNetReplicationGraphConnection* SpecificConnection=nullptr) const;` — Print the Net Culling Distance of all actors in the RepGraph. When a connection is specified will also output the cull distance in the connection info list
- L1055 _public member_ `FPrioritizationConstants PrioritizationConstants;`
- L1063 _public member_ `FFastSharedPathConstants FastSharedPathConstants;`
- L1066 _public member_ `static TFunction<void(int32)> OnListRequestExceedsPooledSize;` — Invoked when a rep list is requested that exceeds the size of the preallocated lists
- L1070 _public prototype_ `virtual void ReplicateActorsForConnection(UNetConnection* NetConnection, FPerConnectionActorInfoMap& ConnectionActorInfoMap, UNetReplicationGraphConnection* ConnectionManager, const uint32 FrameNum);`
- L1072 _public prototype_ `int64 ReplicateSingleActor(const FActorRepListType& Actor, FConnectionReplicationActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalActorInfo, FPerConnectionActorInfoMap& ConnectionActorInfoMap, UNetReplicationGraphConnection& ConnectionManager, const uint32 FrameNum);`
- L1073 _public prototype_ `int64 ReplicateSingleActor_FastShared(AActor* Actor, FConnectionReplicationActorInfo& ConnectionData, FGlobalActorReplicationInfo& GlobalActorInfo, UNetReplicationGraphConnection& ConnectionManager, const uint32 FrameNum);`
- L1075 _public prototype_ `void UpdateActorChannelCloseFrameNum(AActor* Actor, FConnectionReplicationActorInfo& ConnectionData, const FGlobalActorReplicationInfo& GlobalData, const uint32 FrameNum, UNetConnection* NetConnection) const;`
- L1077 _public prototype_ `void NotifyConnectionSaturated(class UNetReplicationGraphConnection& Connection);`
- L1079 _public prototype_ `void NotifyConnectionFastPathSaturated();`
- L1081 _public prototype_ `void SetActorDestructionInfoToIgnoreDistanceCulling(AActor* DestroyedActor);`
- L1083 _public function_ `uint16 GetReplicationPeriodFrameForFrequency(float NetUpdateFrequency) const`
- L1095 _public prototype_ `UNetReplicationGraphConnection* FindConnectionManager(UNetConnection* NetConnection) const;`
- L1097 _public function_ `virtual void VerifyActorReferencesInternal()`
- L1101 _protected prototype_ `virtual void InitializeForWorld(UWorld* World);`
- L1103 _protected prototype_ `virtual void InitNode(UReplicationGraphNode* Node);`
- L1106 _protected prototype_ `virtual void InitGlobalActorClassSettings();` — Override this function to initialize the per-class data for replication
- L1109 _protected prototype_ `virtual void InitGlobalGraphNodes();` — Override this function to init/configure your project's Global Graph
- L1112 _protected prototype_ `virtual void InitConnectionGraphNodes(UNetReplicationGraphConnection* ConnectionManager);` — Override this function to init/configure graph for a specific connection. Note they do not all have to be unique: connections can share nodes (e.g, 2 nodes for 2 teams)
- L1114 _protected prototype_ `UNetReplicationGraphConnection* FindOrAddConnectionManager(UNetConnection* NetConnection);`
- L1117 _protected function_ `void HandleStarvedActorList(const FPrioritizedRepList& List, int32 StartIdx, FPerConnectionActorInfoMap& ConnectionActorInfoMap, uint32 FrameNum)` — `UE_DEPRECATED(5.2, "This function has been replaced with a version that needs to receive a UNetReplicationGraphConnection")`
- L1120 _protected prototype_ `void HandleStarvedActorList(const UNetReplicationGraphConnection& RepGraphConnection, const FPrioritizedRepList& List, int32 StartIdx, FPerConnectionActorInfoMap& ConnectionActorInfoMap, uint32 FrameNum);` — Sets the next timeout frame for the actors in the list along with their dependent actors
- L1123 _protected prototype_ `virtual void RouteRenameNetworkActorToNodes(const FRenamedReplicatedActorInfo& ActorInfo);` — Routes a rename/outer change to every global node. Subclasses will want a more direct routing function where possible.
- L1126 _protected member_ `uint32 GlobalActorChannelFrameNumTimeout;` — How long, in frames, without replicating before an actor channel is closed on a connection. This is a global value added to the individual actor's ActorChannelFrameTimeout
- L1128 _protected member_ `TSharedPtr<FReplicationGraphGlobalData> GraphGlobals;`
- L1131 _protected member_ `FPrioritizedRepList PrioritizedReplicationList;` — Temporary List we use while prioritizing actors
- L1135 _protected member_ `TArray<TObjectPtr<UReplicationGraphNode>> GlobalGraphNodes;` — `UPROPERTY()` — A list of nodes that can add actors to all connections. They don't necessarily *have to* add actors to each connection, but they will get a chance to. These are added via ::AddGlobalGraphNode
- L1139 _protected member_ `TArray<TObjectPtr<UReplicationGraphNode>> PrepareForReplicationNodes;` — `UPROPERTY()` — A list of nodes that want PrepareForReplication() to be called on them at the top of the replication frame.
- L1141 _protected member_ `FGlobalActorReplicationInfoMap GlobalActorReplicationInfoMap;`
- L1145 _protected member_ `TSet<TObjectPtr<AActor>> ActiveNetworkActors;` — `UPROPERTY()` — The authoritative set of "what actors are in the graph"
- L1148 _protected member_ `TMap<FObjectKey , FRPCSendPolicyInfo> RPCSendPolicyMap;` — Special case handling of specific RPCs. Currently supports immediate send/flush for multicasts
- L1149 _protected member_ `TClassMap<bool> RPC_Multicast_OpenChannelForClass;` — Set classes to true here to open channel for them when receiving multicast RPC (and within cull distance range)
- L1151 _protected member_ `FReplicationGraphCSVTracker CSVTracker;`
- L1153 _protected member_ `FOutBunch* FastSharedReplicationBunch = nullptr;`
- L1154 _protected member_ `class UActorChannel* FastSharedReplicationChannel = nullptr;`
- L1155 _protected member_ `FName FastSharedReplicationFuncName = NAME_None;`
- L1158 _protected member_ `bool bEnableFullActorPrioritizationDetailsAllConnections = false;`
- L1163 _private member_ `bool bWasConnectionSaturated = false;` — Whether or not a connection was saturated during an update.
- L1166 _private member_ `bool bWasConnectionFastPathSaturated = false;` — Whether or not all fast shared replication budget has been used during replication.
- L1170 _protected prototype_ `void ReplicateActorListsForConnections_Default(UNetReplicationGraphConnection* ConnectionManager, FGatheredReplicationActorLists& GatheredReplicationListsForConnection, FNetViewerArray& Viewers);` — Default Replication Path
- L1173 _protected prototype_ `void ReplicateActorListsForConnections_FastShared(UNetReplicationGraphConnection* ConnectionManager, FGatheredReplicationActorLists& GatheredReplicationListsForConnection, FNetViewerArray& Viewers);` — "FastShared" Replication Path
- L1176 _protected member_ `TArray<UNetConnection*> ConnectionsNeedingsPostTickDispatchFlush;` — Connections needing a FlushNet in PostTickDispatch
- L1178 _protected function_ `virtual void AddReplayViewers(UNetConnection* NetConnection, FNetViewerArray& Viewers)`
- L1202 _protected prototype_ `virtual void PostServerReplicateStats(const FFrameReplicationStats& Stats);` — Event called after ServerReplicateActors to dispatch the replication stats from this frame
- L1206 _private prototype_ `UNetReplicationGraphConnection* FixGraphConnectionList(TArray<UNetReplicationGraphConnection*>& OutList, int32& ConnectionId, UNetConnection* RemovedNetConnection);`
- L1211 _private member_ `FFrameReplicationStats FrameReplicationStats;` — Collect replication data during ServerReplicateActors
- L1214 _private member_ `uint32 ReplicationGraphFrame = 0;` — Internal frame counter for replication. This is only updated by us. The one of UNetDriver can be updated by RPC calls and is only used to invalidate shared property CLs/serialiation data.
- L1217 _private member_ `int32 ActorDiscoveryMaxBitsPerFrame;` — Separate bandwidth cap for traffic used when opening actor channels. Ignored if set to 0
- L1220 _private member_ `int32 HeavyComputationConnectionSelector = 0;` — Optimization to update only one connection each frame
- L1223 _private member_ `float TimeLeftUntilUpdate = 0.f;` — Internal time used to track when the next update should occur based on frequency settings.
- L1225 _private prototype_ `UNetReplicationGraphConnection* CreateClientConnectionManagerInternal(UNetConnection* Connection);`
- L1230 _private member_ `FDelegateHandle WorldCleanupDelegateHandle;` — Delegate to remove all network actors when a world is cleaned up.

#### struct `UReplicationGraph::FPrioritizationConstants`  
`struct FPrioritizationConstants`  
_L1049-1054_
- desc: Prioritization Constants: these affect how the final priority of an actor is calculated in the prioritize phase
- L1051 _public member_ `float MaxDistanceScaling = 60000.f * 60000.f;` — Distance scaling for prioritization scales up to this distance, everything passed this distance is the same or "capped"
- L1052 _public member_ `uint32 MaxFramesSinceLastRep = 20;` — Time since last rep scales up to this

#### struct `UReplicationGraph::FFastSharedPathConstants`  
`struct FFastSharedPathConstants`  
_L1057-1062_
- L1059 _public member_ `float DistanceRequirementPct = 0.1f;` — Must be this close, as a factor of cull distance *squared*, to use fast shared replication path
- L1060 _public member_ `int32 MaxBitsPerFrame = 2048;` — 5kBytes/sec @ 20hz
- L1061 _public member_ `int32 ListSkipPerFrame = 3;`

#### struct `UReplicationGraph::FFrameReplicationStats`  
`struct FFrameReplicationStats`  
_L1181-1199_
- desc: Collects basic stats on the replicated actors
- L1184 _public member_ `int32 NumReplicatedActors = 0;` — Total number of actors replicated.
- L1187 _public member_ `int32 NumReplicatedCleanActors = 0;` — Number of actors who did not send any data when ReplicateActor was called on them.
- L1190 _public member_ `int32 NumReplicatedFastPathActors = 0;` — Number of actors replicated using the fast path.
- L1193 _public member_ `int32 NumConnections = 0;` — Total connections replicated to during the tick including children (splitscreen) and replay connections.
- L1195 _public function_ `void Reset()`

#### struct `FLastLocationGatherInfo`  
`struct FLastLocationGatherInfo`  
_L1238-1258_
- reflection: `USTRUCT()`
- L1242 _public function_ `FLastLocationGatherInfo() : Connection(nullptr), LastLocation(ForceInitToZero), LastOutOfRangeLocationCheck(ForceInitToZero)`
- L1243 _public function_ `FLastLocationGatherInfo(const UNetConnection* InConnection, FVector InLastLocation) : Connection(InConnection), LastLocation(InLastLocation), LastOutOfRangeLocationCheck(InLastLocation)`
- L1246 _public member_ `TObjectPtr<const UNetConnection> Connection;` — `UPROPERTY()`
- L1249 _public member_ `FVector LastLocation;` — `UPROPERTY()`
- L1252 _public member_ `FVector LastOutOfRangeLocationCheck;` — `UPROPERTY()`
- L1254 _public function_ `bool operator==(UNetConnection* Other) const`

#### struct `FRepGraphConnectionSaturationAnalytics`  
`struct FRepGraphConnectionSaturationAnalytics`  
_L1260-1280_
- L1262 _public member_ `uint32 LongestRunOfSaturatedReplications = 0;`
- L1263 _public member_ `uint32 CurrentRunOfSaturatedReplications = 0;`
- L1265 _public function_ `void TrackReplication(bool bIsSaturated)`

#### class `UNetReplicationGraphConnection`  
`class UNetReplicationGraphConnection : public UReplicationConnectionDriver`  
_L1284-1505_
- reflection: `UCLASS(MinimalAPI, transient)`
- inherits: `UReplicationConnectionDriver`
- desc: Manages actor replication for a specific connection
- L1290 _public prototype_ `UNetReplicationGraphConnection();`
- L1293 _public member_ `TObjectPtr<UNetConnection> NetConnection;` — `UPROPERTY()`
- L1296 _public member_ `FPerConnectionActorInfoMap ActorInfoMap;` — A map of all of our per-actor data
- L1298 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostReplicatePrioritizedLists, UNetReplicationGraphConnection*, FPrioritizedRepList*);`
- L1299 _public member_ `FOnPostReplicatePrioritizedLists OnPostReplicatePrioritizeLists;`
- L1301 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClientVisibleLevelNamesAdd, FName, UWorld*);`
- L1302 _public member_ `FOnClientVisibleLevelNamesAdd OnClientVisibleLevelNameAdd;` — Global Delegate, will be called for every level
- L1303 _public member_ `TMap<FName, FOnClientVisibleLevelNamesAdd> OnClientVisibleLevelNameAddMap;` — LevelName lookup map delegates
- L1305 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClientVisibleLevelNamesRemove, FName);`
- L1306 _public member_ `FOnClientVisibleLevelNamesRemove OnClientVisibleLevelNameRemove;`
- L1314 _public member_ `bool bEnableFullActorPrioritizationDetails = false;`
- L1317 _public member_ `bool bEnableDebugging;`
- L1320 _public member_ `TWeakObjectPtr<class AReplicationGraphDebugActor> DebugActor;` — `UPROPERTY()`
- L1323 _public member_ `int32 ConnectionOrderNum;` — Index of the connection in the global list. Will be reassigned when any client disconnects so it is a key that can be referenced only during a single tick
- L1326 _public member_ `TArray<FLastLocationGatherInfo> LastGatherLocations;` — `UPROPERTY()`
- L1329 _public member_ `int32 QueuedBitsForActorDiscovery = 0;` — Nb of bits sent for actor channel creation when a dedicated budget is allocated for this
- L1332 _public function_ `const TArray<UReplicationGraphNode*>& GetConnectionGraphNodes() const` — Returns connection graph nodes. This is const so that you do not mutate the array itself. You should use AddConnectionGraphNode/RemoveConnectionGraphNode.
- L1335 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L1339 _public prototype_ `virtual void TearDown() override;`
- L1341 _public prototype_ `virtual void NotifyClientVisibleLevelNamesAdd(FName LevelName, UWorld* StreamingWorld) override;`
- L1343 _public function_ `virtual void NotifyClientVisibleLevelNamesRemove(FName LevelName) override`
- L1345 _public prototype_ `virtual void NotifyActorChannelAdded(AActor* Actor, class UActorChannel* Channel) override;`
- L1347 _public prototype_ `virtual void NotifyActorChannelRemoved(AActor* Actor) override;`
- L1349 _public prototype_ `virtual void NotifyActorChannelCleanedUp(UActorChannel* Channel) override;`
- L1351 _public prototype_ `virtual void NotifyAddDestructionInfo(FActorDestructionInfo* DestructInfo) override;`
- L1353 _public prototype_ `virtual void NotifyRemoveDestructionInfo(FActorDestructionInfo* DestructInfo) override;`
- L1355 _public prototype_ `virtual void NotifyAddDormantDestructionInfo(AActor* Actor) override;`
- L1357 _public prototype_ `virtual void NotifyResetDestructionInfo() override;`
- L1360 _public prototype_ `virtual void NotifyResetAllNetworkActors();`
- L1363 _public prototype_ `virtual void GetClientVisibleLevelNames(TSet<FName>& OutLevelNames) const;` — Generates a set of all the visible level names for this connection and its subconnections (if any)
- L1366 _public function_ `const TSet<FName>& GetCachedClientVisibleLevelNames() const` — Returns the list of visible levels cached at the start of the gather phase.
- L1368 _public prototype_ `FActorRepListRefView& GetPrevDormantActorListForNode(const UReplicationGraphNode* GridNode);`
- L1370 _public prototype_ `void RemoveActorFromAllPrevDormantActorLists(AActor* InActor);`
- L1378 _public function_ `friend bool operator==(const FVisibleCellInfo& Cell, const FIntPoint& Point)` — For FindByKey
- L1384 _public prototype_ `TArray<FVisibleCellInfo>& GetVisibleCellsForNode(const UReplicationGraphNode* GridNode);`
- L1386 _public prototype_ `void CleanupNodeCaches(const UReplicationGraphNode* Node);`
- L1388 _public function_ `virtual void NotifyDSFNodeSaturated(const UReplicationGraphNode_DynamicSpatialFrequency* Node)`
- L1390 _public prototype_ `virtual void TrackReplicationForAnalytics(bool bFastPathSaturated);`
- L1392 _public prototype_ `virtual void ResetSaturationAnalytics();`
- L1394 _public member_ `FRepGraphConnectionSaturationAnalytics FastPathSaturationAnalytics;`
- L1399 _private member_ `TMap<TObjectKey<UReplicationGraphNode>, FActorRepListRefView> PrevDormantActorListPerNode;` — Stored list of dormant actors in a previous cell when it's been left - this is for the dormant dynamic actor destruction feature.
- L1402 _private member_ `TMap<TObjectKey<UReplicationGraphNode>, TArray<FVisibleCellInfo>> NodesVisibleCells;` — History of visible cells per graph node used for defering dormant dynamic actors cleanup
- L1419 _private typedef_ `typedef TArray< FRepGraphDestructionViewerInfo, TInlineAllocator<REPGRAPH_VIEWERS_PER_CONNECTION> > FRepGraphDestructionViewerInfoArray;`
- L1424 _private prototype_ `void InitForGraph(UReplicationGraph* Graph);` — Called right after this is created to associate with the owning Graph
- L1427 _private prototype_ `void InitForConnection(UNetConnection* Connection);` — Called after InitForGraph is called to associate this connection manager with a net connection
- L1430 _private prototype_ `void AddConnectionGraphNode(UReplicationGraphNode* Node);` — Adds a node to this connection manager
- L1433 _private prototype_ `void RemoveConnectionGraphNode(UReplicationGraphNode* Node);` — Remove a node to this connection manager
- L1435 _private prototype_ `bool PrepareForReplication();`
- L1437 _private prototype_ `int64 ReplicateDestructionInfos(const FRepGraphDestructionViewerInfoArray& DestructionViewersInfo, const FReplicationGraphDestructionSettings& DestructionSettings);`
- L1439 _private prototype_ `int64 ReplicateDormantDestructionInfos();`
- L1442 _private prototype_ `void UpdateGatherLocationsForConnection(const FNetViewerArray& ConnectionViewers, const FReplicationGraphDestructionSettings& DestructionSettings);` — Update the last location for viewers on a connection
- L1445 _private prototype_ `void OnUpdateViewerLocation(FLastLocationGatherInfo* LocationInfo, const FNetViewer& Viewer, const FReplicationGraphDestructionSettings& DestructionSettings);` — Update the location info of a specific viewer
- L1447 _private prototype_ `void SetActorNotDormantOnConnection(AActor* InActor);`
- L1449 _private prototype_ `void BuildVisibleLevels();`
- L1452 _private member_ `TArray<TObjectPtr<UReplicationGraphNode>> ConnectionGraphNodes;` — `UPROPERTY()`
- L1455 _private member_ `TObjectPtr<UReplicationGraphNode_TearOff_ForConnection> TearOffNode;` — `UPROPERTY()`
- L1481 _private member_ `TArray<FCachedDestructInfo> OutOfRangeDestroyedActors;` — List of destroyed actors that were too far from the connection to be relevant. Is periodically evaluated when the viewer crosses a specific distance.
- L1484 _private member_ `TArray<FCachedDestructInfo> PendingDestructInfoList;` — List of destroyed actors that need to be replicated
- L1487 _private member_ `TSet<FActorDestructionInfo*> TrackedDestructionInfoPtrs;` — Set used to guard against double adds into PendingDestructInfoList
- L1498 _private member_ `TArray<FCachedDormantDestructInfo> PendingDormantDestructList;` — List of dormant actors that should be removed from the client
- L1501 _private member_ `TSet<FNetworkGUID> TrackedDormantDestructionInfos;` — Set used to guard against double adds into PendingDormantDestructList
- L1504 _private member_ `TSet<FName> CachedVisibleLevels;` — List of level names visible to this connection. Valid during the Gather phase

#### struct `UNetReplicationGraphConnection::FVisibleCellInfo`  
`struct FVisibleCellInfo`  
_L1372-1382_
- L1374 _public member_ `FIntPoint Location = {};`
- L1375 _public member_ `int32 Lifetime = 0;`

#### struct `UNetReplicationGraphConnection::FRepGraphDestructionViewerInfo`  
`struct FRepGraphDestructionViewerInfo`  
_L1407-1417_
- desc: Holds relevant data when parsing deleted actors that could be sent to a viewer
- L1409 _public prototype_ `FRepGraphDestructionViewerInfo() = default;`
- L1410 _public function_ `FRepGraphDestructionViewerInfo(const FVector& InViewerLocation, const FVector& InOutOfRangeLocationCheck) : ViewerLocation(InViewerLocation) , LastOutOfRangeLocationCheck(InOutOfRangeLocationCheck)`
- L1415 _public member_ `FVector ViewerLocation;`
- L1416 _public member_ `FVector LastOutOfRangeLocationCheck;`

#### struct `UNetReplicationGraphConnection::FCachedDestructInfo`  
`struct FCachedDestructInfo`  
_L1458-1475_
- desc: DestructionInfo handling. This is how we send "delete this actor" to clients when the actor is deleted on the server (placed in map actors)
- L1460 _public function_ `FCachedDestructInfo(FActorDestructionInfo* InDestructInfo) : DestructionInfo(InDestructInfo), CachedPosition(InDestructInfo->DestroyedPosition)`
- L1461 _public function_ `bool operator==(const FCachedDestructInfo& rhs) const`
- L1462 _public function_ `bool operator==(const FActorDestructionInfo* InDestructInfo) const`
- L1464 _public member_ `FActorDestructionInfo* DestructionInfo;`
- L1465 _public member_ `FVector CachedPosition;`
- L1467 _public function_ `void CountBytes(FArchive& Ar) const`

#### struct `UNetReplicationGraphConnection::FCachedDormantDestructInfo`  
`struct FCachedDormantDestructInfo`  
_L1489-1495_
- L1491 _public member_ `TWeakObjectPtr<ULevel> Level;`
- L1492 _public member_ `TWeakObjectPtr<UObject> ObjOuter;`
- L1493 _public member_ `FNetworkGUID NetGUID;`
- L1494 _public member_ `FString PathName;`

#### class `AReplicationGraphDebugActor`  
`class AReplicationGraphDebugActor : public AActor`  
_L1514-1569_
- reflection: `UCLASS(MinimalAPI, NotPlaceable, Transient)`
- inherits: `AActor`
- desc: Specialized actor for replicating debug information about replication to specific connections. This actor is never spawned in shipping builds and never counts towards bandwidth limits
- L1520 _public function_ `AReplicationGraphDebugActor()`
- L1527 _public function_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override` — To prevent demo netdriver from replicating.
- L1528 _public function_ `virtual bool IsReplayRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation, const float CullDistanceSquared) const override`
- L1531 _public member_ `TObjectPtr<UReplicationGraph> ReplicationGraph;` — `UPROPERTY()`
- L1534 _public prototype_ `void ServerStartDebugging();` — `UFUNCTION(Server, Reliable)`
- L1537 _public prototype_ `void ServerStopDebugging();` — `UFUNCTION(Server, Reliable)`
- L1540 _public prototype_ `void ServerCellInfo();` — `UFUNCTION(Server, Reliable)`
- L1543 _public prototype_ `void ServerPrintAllActorInfo(const FString& Str);` — `UFUNCTION(Server, Reliable)`
- L1546 _public prototype_ `void ServerSetCullDistanceForClass(UClass* Class, float CullDistance);` — `UFUNCTION(Server, Reliable)`
- L1549 _public prototype_ `void ServerSetPeriodFrameForClass(UClass* Class, int32 PeriodFrame);` — `UFUNCTION(Server, Reliable)`
- L1552 _public prototype_ `void ServerSetConditionalActorBreakpoint(AActor* Actor);` — `UFUNCTION(Server, Reliable)`
- L1555 _public prototype_ `void ServerPrintCullDistances();` — `UFUNCTION(Server, Reliable)`
- L1558 _public prototype_ `void ClientCellInfo(FVector CellLocation, FVector CellExtent, const TArray<AActor*>& Actors);` — `UFUNCTION(Client, Reliable)`
- L1560 _public prototype_ `void PrintCullDistances();`
- L1562 _public prototype_ `void PrintAllActorInfo(FString MatchString);`
- L1566 _public member_ `TObjectPtr<UNetReplicationGraphConnection> ConnectionManager;` — `UPROPERTY()`
- L1568 _public prototype_ `virtual UNetConnection* GetNetConnection() const override;`

#### struct `FReplicationGraphDestructionSettings`  
`struct FReplicationGraphDestructionSettings`  
_L1574-1585_
- L1576 _public function_ `FReplicationGraphDestructionSettings(float InDestructInfoMaxDistanceSquared, float InOutOfRangeDistanceCheckThresholdSquared) : DestructInfoMaxDistanceSquared(InDestructInfoMaxDistanceSquared) , OutOfRangeDistanceCheckThresholdSquared(InOutOfRangeDistanceCheckThresholdSquared) , MaxPendingListDistanceSquared(DestructInfoMaxDistanceSquared + OutOfRangeDistanceCheckThresholdSquared)`
- L1582 _public member_ `float DestructInfoMaxDistanceSquared;`
- L1583 _public member_ `float OutOfRangeDistanceCheckThresholdSquared;`
- L1584 _public member_ `float MaxPendingListDistanceSquared;`

#### Free symbols / members of external scopes

- L58 _macro_ `#define UE_API REPLICATIONGRAPH_API`
- L62 _typedef_ `typedef TObjectKey<class UNetReplicationGraphConnection> FRepGraphConnectionKey;`
- L65 _macro_ `#define DO_ENABLE_REPGRAPH_DEBUG_ACTOR !(UE_BUILD_SHIPPING)`
- L1298 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostReplicatePrioritizedLists, UNetReplicationGraphConnection*, FPrioritizedRepList*);`
- L1301 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClientVisibleLevelNamesAdd, FName, UWorld*);`
- L1305 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClientVisibleLevelNamesRemove, FName);`

### `Plugins/Runtime/ReplicationGraph/Source/Public/ReplicationGraphModule.h` (Public)


#### class `FReplicationGraphModule`  
`class FReplicationGraphModule : public FDefaultModuleImpl`  
_L8-14_
- inherits: `FDefaultModuleImpl`
- desc: Module definition for replication graph

### `Plugins/Runtime/ReplicationGraph/Source/Public/ReplicationGraphTypes.h` (Public)


#### struct `FActorRepListType`  
`struct FActorRepListType`  
_L96-295_
- L107 _private member_ `TVariant<AActor*, FWeakObjectPtr> ActorUnion;` — Actor pointer (raw or weak). Most accesses should be via GetActor() or SetActor(). Type is set during construction depending on bUseWeakPointers: FWeakObjectPtr when true, AActor* when false. Most functions should depend on the actual type, only SetActor() depends on bUseWeakPointers so the configuration can change at runtime without breaking extant instances. Could be condensed to sizeof(AActor*) aka sizeof(FWeakObjectPtr) by storing the type flag in the high bit and masking it out.
- L111 _public member_ `FName ActorName;` — More info for debugging - ActorRaw's name
- L113 _public member_ `FName OwnerName;` — More info for debugging - ActorRaw's Owner name
- L115 _public member_ `FName OuterPackageName;` — More info for debugging - ActorRaw's Outer's package name
- L117 _public function_ `FActorRepListType()`
- L123 _public function_ `FActorRepListType(AActor* InActor)` — Permits implicit construction so FActorRepListType can be a drop-in substitute for `AActor*` depending on an ifdef.
- L129 _public prototype_ `FActorRepListType(const FActorRepListType& InActor) = default;` — Copies/moves are clones that don't need to validate the object.
- L130 _public prototype_ `FActorRepListType(FActorRepListType&& InActor) = default;`
- L131 _public prototype_ `FActorRepListType& operator=(const FActorRepListType& InActor) = default;`
- L132 _public prototype_ `FActorRepListType& operator=(FActorRepListType&& InActor) = default;`
- L139 _public function_ `FActorRepListType(const T& InActor)`
- L144 _public function_ `operator AActor* () const`
- L145 _public function_ `AActor* operator->() const`
- L146 _public function_ `explicit operator uint64() const`
- L147 _public function_ `FActorRepListType& operator=(AActor* InActor)`
- L152 _public function_ `FActorRepListType& operator=(TObjectPtr<AActor> InActor)`
- L217 _public function_ `bool IsValid() const`
- L227 _public function_ `inline AActor* GetActor() const`
- L255 _public function_ `uint32 GetTypeHash() const` — Get hash. Prefer this be a member function than standalone to avoid implicit conversions to FActorRepListType.
- L263 _private function_ `void SetActor(AActor* Actor)`
- L277 _private function_ `void SetDebugInfo()`

#### enum `EActorRepListTypeFlags`  
`enum class EActorRepListTypeFlags : uint8`  
_L309-314_
- desc: Generic flags that describe an actor list. Currently only used for "Default" vs "FastShared" path. These are for unsorted lists that are returned from the graph, merged together, sorted, and finally replicated until bandwidth limit is hit
- L311 _public enumerator_ `Default = 0`
- L312 _public enumerator_ `FastShared = 1`
- L313 _public enumerator_ `Max` — Always keep last

#### struct `FActorRepList`  
`struct FActorRepList : FNoncopyable`  
_L376-397_
- inherits: `FNoncopyable`
- desc: The actual underlying list type that the system uses for a list of replicated actors. These are never manually allocated or even really used. All Replication code interacts with the "View" types below
- L379 _public member_ `int32 RefCount;` — List Header
- L380 _public member_ `int32 Max;`
- L381 _public member_ `int32 Num;`
- L384 _public member_ `FBitReference UsedBitRef;` — the "used bit" from the block we came from, so that we can clear it fast
- L387 _public member_ `FActorRepListType Data[];` — Variable length Data segment
- L390 _public function_ `void AddRef()` — For TRefCountPtr usage
- L391 _public prototype_ `void Release();`
- L393 _public function_ `void CountBytes(FArchive& Ar) const`

#### struct `TActorRepListViewBase`  
`template<typename PointerType> struct TActorRepListViewBase`  
_L401-476_
- desc: This is a base templated type for the list "Views". This provides basic read only access between the two real views.
- L403 _public function_ `TActorRepListViewBase()`
- L404 _public function_ `TActorRepListViewBase(const PointerType& In) : RepList(In)`
- L406 _public function_ `inline int32 Num() const`
- L407 _public function_ `inline const FActorRepListType& operator[](int32 idx) const`
- L410 _public function_ `inline void ResetToNull()` — Resets the view to null - meaning it is not pointing to any list (as opposed to an empty list of some preallocated size)
- L411 _public function_ `inline bool IsValid() const`
- L413 _public function_ `int32 IndexOf(const FActorRepListType& Value) const`
- L428 _public function_ `bool Contains(const FActorRepListType& Value) const`
- L431 _public function_ `void AppendToTArray(TArray<FActorRepListType>& OutArray) const` — Add contents to TArray. this is intended for debugging/ease of use
- L442 _public function_ `void AppendToTSet(TSet<FActorRepListType>& OutSet) const`
- L453 _public member_ `PointerType RepList;`
- L455 _public function_ `FString BuildDebugString() const`
- L469 _public function_ `FActorRepListType* begin() const`
- L470 _public function_ `FActorRepListType* end() const`

#### struct `FActorRepListRefView`  
`struct FActorRepListRefView`  
_L481-603_
- desc: Holds a list of replicated actors that can be added/removed to.
- L483 _public function_ `FActorRepListRefView()`
- L488 _public function_ `void Reset(int32 ExpectedMaxSize=0)` — Empties the array but does not deallocate the internal memory. Will be resized if the specified max size is bigger than the current max.
- L494 _public function_ `void Reserve(int32 Size)` — Preallocate the array so it can hold the specified size
- L499 _public function_ `bool ConditionalAdd(const FActorRepListType& NewElement)`
- L509 _public function_ `void Add(const FActorRepListType& NewElement)`
- L515 _public function_ `bool RemoveFast(const FActorRepListType& ElementToRemove, EAllowShrinking AllowShrink = EAllowShrinking::Default)` — Removes the element quickly but changes the list order
- L521 _public function_ `bool RemoveSlow(const FActorRepListType& ElementToRemove)` — Removes the element but keeps the order intact. Generally not recommended for large lists.
- L526 _public function_ `void RemoveAtSwap(int32 idx)`
- L531 _public function_ `void CopyContentsFrom(const FActorRepListRefView& Source)`
- L536 _public function_ `void AppendContentsFrom(const FActorRepListRefView& Source)`
- L541 _public prototype_ `bool VerifyContents_Slow() const;`
- L544 _public function_ `void AppendToTArray(TArray<FActorRepListType>& OutArray) const` — Add contents to TArray/TSet. this is intended for debugging/ease of use
- L548 _public function_ `void AppendToTSet(TSet<FActorRepListType>& OutSet) const`
- L553 _public prototype_ `FString BuildDebugString() const;`
- L559 _public function_ `FActorRepListType& operator[](int32 idx)`
- L560 _public function_ `const FActorRepListType& operator[](int32 idx) const`
- L562 _public function_ `TArray<FActorRepListType>::RangedForIteratorType begin()`
- L563 _public function_ `TArray<FActorRepListType>::RangedForConstIteratorType begin() const`
- L564 _public function_ `TArray<FActorRepListType>::RangedForIteratorType end()`
- L565 _public function_ `TArray<FActorRepListType>::RangedForConstIteratorType end() const`
- L567 _public function_ `bool IsEmpty() const`
- L572 _public function_ `int32 Num() const`
- L578 _public function_ `void TearDown()` — Resets the container and returns the memory it held
- L583 _public function_ `int32 IndexOf(const FActorRepListType& Value) const`
- L588 _public function_ `bool Contains(const FActorRepListType& Value) const`
- L593 _public function_ `void CountBytes(FArchive& Ar) const`
- L602 _private member_ `TArray<FActorRepListType> RepList;`

#### struct `FActorRepListConstView`  
`FActorRepListConstView`  
_L611-632_
- reflection: `UE_DEPRECATED(5.5, "Use TArrayView<const FActorRepListType> instead")`
- L613 _public function_ `explicit FActorRepListConstView(const FActorRepListRefView& InListReferenced) : ListReferenced(InListReferenced)`
- L617 _public function_ `FActorRepListType operator[](int32 idx) const`
- L622 _public function_ `int32 Num() const`
- L627 _public function_ `TArray<FActorRepListType>::RangedForConstIteratorType begin() const`
- L628 _public function_ `TArray<FActorRepListType>::RangedForConstIteratorType end() const`
- L631 _private member_ `const FActorRepListRefView& ListReferenced;`

#### struct `FGatheredReplicationActorLists`  
`struct FGatheredReplicationActorLists`  
_L650-691_
- desc: This represents "the list of gathered actors". This is what we push down the Replication Graph and nodes will either Push/Pop List Categories or will add their Replication Lists.
- L652 _public function_ `void AddReplicationActorList(const FActorRepListRefView& List, EActorRepListTypeFlags Flags = EActorRepListTypeFlags::Default)`
- L661 _public function_ `inline void Reset()`
- L668 _public function_ `inline int32 NumLists() const`
- L675 _public prototype_ `inline const TArray<FActorRepListConstView>& GetLists(EActorRepListTypeFlags ListFlags) const;` — `UE_DEPRECATED(5.5, "Use ViewActors() instead")`
- L678 _public function_ `inline TArrayView<const FActorRepListType> ViewActors(EActorRepListTypeFlags ListFlags) const`
- L683 _public function_ `inline bool ContainsLists(EActorRepListTypeFlags Flags) const`
- L690 _private member_ `TStaticArray< TArray<FActorRepListType>, (uint32)EActorRepListTypeFlags::Max > ReplicationLists;`

#### struct `FNewReplicatedActorInfo`  
`struct FNewReplicatedActorInfo`  
_L700-721_
- desc: This is the struct we use to push new replication actors into the graph. "New" doesn't mean "newly spawned" it means "new to the graph". FIXME: Please suggest a better name!
- L702 _public function_ `explicit FNewReplicatedActorInfo(const FActorRepListType& InActor) : Actor(InActor), Class(InActor->GetClass())`
- L707 _public function_ `explicit FNewReplicatedActorInfo(const FActorRepListType& InActor, FName OverrideLevelName) : Actor(InActor) , StreamingLevelName(OverrideLevelName) , Class(InActor->GetClass())`
- L714 _public function_ `AActor* GetActor() const`
- L716 _public prototype_ `static FName GetStreamingLevelNameOfActor(const AActor* Actor);`
- L718 _public member_ `FActorRepListType Actor;`
- L719 _public member_ `FName StreamingLevelName;`
- L720 _public member_ `UClass* Class;`

#### struct `FRenamedReplicatedActorInfo`  
`struct FRenamedReplicatedActorInfo`  
_L730-743_
- desc: Used to update renamed (changed outer/level) actors in the graph.
- L732 _public function_ `explicit FRenamedReplicatedActorInfo(const FActorRepListType& InActor, FName InPreviousStreamingLevelName) : NewActorInfo(InActor) , OldActorInfo(InActor, InPreviousStreamingLevelName)`
- L739 _public member_ `FNewReplicatedActorInfo NewActorInfo;` — Info that stores the actor's new level name
- L742 _public member_ `FNewReplicatedActorInfo OldActorInfo;` — Info that stores the actor's old level name

#### struct `FStreamingLevelActorListCollection`  
`struct FStreamingLevelActorListCollection`  
_L754-825_
- desc: Holds a list of actors grouped by their streaming level
- L756 _public prototype_ `void AddActor(const FNewReplicatedActorInfo& ActorInfo);`
- L765 _public prototype_ `bool RemoveActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound, UObject* Outer=nullptr);` — Removes the actor but keep the actor order list intact @param ActorInfo  The actor to be removed @param bWarnIfNotFound When true we log a warning when the actor was not in any list @param Outer Optional pointer to the owner of the list if you want to output the owner name in any log messages
- L773 _public prototype_ `bool RemoveActorFast(const FNewReplicatedActorInfo& ActorInfo, UObject* Outer=nullptr);` — Removes the actor but using the faster swap operation that change the ordering of the list @param ActorInfo  The actor to be removed @param Outer Optional pointer to the owner of the list if you want to output the owner name in any log messages
- L779 _public prototype_ `bool RemoveActorFromLevelFast(AActor* Actor, FName LevelName);` — Attempts to remove the actor from the level explicitly provided. Can be used to update the list if the actor's level changes (by providing the actor's previous level).
- L781 _public prototype_ `void Reset();`
- L784 _public prototype_ `void Gather(const FConnectionGatherActorListParameters& Params) const;` — Add to the Params' gather list the list of actors for levels that are visible to that connection
- L787 _public prototype_ `void Gather(const UNetReplicationGraphConnection& ConnectionManager, FGatheredReplicationActorLists& OutGatheredList) const;` — Add to the passed gather list the list of actors that are visible to the connection
- L790 _public prototype_ `void AppendAllLists(FGatheredReplicationActorLists& OutGatheredList) const;` — Add to the passed gather list all list of actors held
- L793 _public prototype_ `bool Contains(const FNewReplicatedActorInfo& ActorInfo) const;` — Is this actor held in one of the actor lists
- L795 _public prototype_ `void DeepCopyFrom(const FStreamingLevelActorListCollection& Source);`
- L796 _public prototype_ `void GetAll_Debug(TArray<FActorRepListType>& OutArray) const;`
- L797 _public prototype_ `void Log(FReplicationGraphDebugInfo& DebugInfo) const;`
- L799 _public function_ `int32 NumLevels() const`
- L801 _public prototype_ `void TearDown();`
- L813 _public member_ `static const int32 NumInlineAllocations = 4;` — Lists for streaming levels. Actors that "came from" streaming levels go here. These lists are only returned if the connection has their streaming level loaded.
- L814 _public member_ `TArray<FStreamingLevelActors, TInlineAllocator<NumInlineAllocations>> StreamingLevelLists;`
- L816 _public function_ `void CountBytes(FArchive& Ar) const`

#### struct `FStreamingLevelActorListCollection::FStreamingLevelActors`  
`struct FStreamingLevelActors`  
_L803-810_
- L805 _public function_ `FStreamingLevelActors(FName InName) : StreamingLevelName(InName)`
- L807 _public member_ `FName StreamingLevelName;`
- L808 _public member_ `FActorRepListRefView ReplicationActorList;`
- L809 _public function_ `bool operator==(const FName& InName) const`

#### struct `FLevelBasedActorList`  
`struct FLevelBasedActorList`  
_L831-867_
- desc: Holds a list of actors grouped by the permanent level or their streaming level
- L833 _public prototype_ `void AddNetworkActor(AActor* NetActor);`
- L834 _public prototype_ `bool RemoveNetworkActor(const FNewReplicatedActorInfo& NetActor);`
- L835 _public function_ `bool RemoveNetworkActor(AActor* NetActor)`
- L841 _public prototype_ `bool RemoveNetworkActorOrdered(AActor* NetActor);`
- L843 _public prototype_ `void Reset();`
- L845 _public prototype_ `bool Contains(AActor* NetActor) const;`
- L848 _public prototype_ `void Gather(const FConnectionGatherActorListParameters& Params) const;` — Gather the list of actors visible to this connection and add them to the gather list
- L849 _public prototype_ `void Gather(const UNetReplicationGraphConnection& ConnectionManager, FGatheredReplicationActorLists& OutGatheredList) const;`
- L852 _public prototype_ `void AppendAllLists(FGatheredReplicationActorLists& OutGatheredList) const;` — Add a reference to all the lists held here to the gather list
- L855 _public prototype_ `void GetAllActors(TArray<AActor*>& OutAllActors) const;` — Returns the list of all actors held by the permenant and streaming level list. Prefer using AppendAllLists to prevent copying TArrays for nothing.
- L857 _public prototype_ `void CountBytes(FArchive& Ar) const;`
- L860 _public prototype_ `void UpdateActorLevel(AActor* NetActor, FName PreviousLevelName);` — Update actor to new level
- L864 _private member_ `FActorRepListRefView PermanentLevelActors;`
- L866 _private member_ `FStreamingLevelActorListCollection StreamingLevelActors;`

#### struct `FClassReplicationInfo`  
`struct FClassReplicationInfo`  
_L877-950_
- reflection: `USTRUCT()`
- desc: Per-Class actor data about how the actor replicates
- L882 _public member_ `float DistancePriorityScale = 1.f;` — `UPROPERTY()`
- L884 _public member_ `float StarvationPriorityScale = 1.f;` — `UPROPERTY()`
- L886 _public member_ `float AccumulatedNetPriorityBias = 0.f;` — `UPROPERTY()`
- L889 _public member_ `uint16 ReplicationPeriodFrame = 1;` — `UPROPERTY()`
- L891 _public member_ `uint16 FastPath_ReplicationPeriodFrame = 1;` — `UPROPERTY()`
- L893 _public member_ `uint16 ActorChannelFrameTimeout = 4;` — `UPROPERTY()`
- L895 _public member_ `TFunction<bool(AActor*)> FastSharedReplicationFunc = nullptr;`
- L896 _public member_ `FName FastSharedReplicationFuncName = NAME_None;`
- L898 _public function_ `void SetCullDistanceSquared(float InCullDistanceSquared)`
- L904 _public function_ `float GetCullDistance() const`
- L905 _public function_ `float GetCullDistanceSquared() const`
- L907 _public function_ `FString BuildDebugStringDelta() const`
- L946 _private member_ `float CullDistance = 0.0f;` — `UPROPERTY()`
- L948 _private member_ `float CullDistanceSquared = 0.f;` — `UPROPERTY()`

#### struct `FFastSharedReplicationInfo`  
`struct FFastSharedReplicationInfo`  
_L954-964_
- L956 _public member_ `uint32 LastAttemptBuildFrameNum = 0;` — the last frame we called FastSharedReplicationFunc on
- L957 _public member_ `uint32 LastBunchBuildFrameNum = 0;` — the last frame a new bunch was actually created
- L958 _public member_ `FOutBunch Bunch;`
- L960 _public function_ `void CountBytes(FArchive& Ar) const`

#### struct `FGlobalActorReplicationEvents`  
`struct FGlobalActorReplicationEvents`  
_L973-980_
- L975 _public member_ `FNotifyActorChangeDormancy DormancyChange;`
- L976 _public member_ `FNotifyActorFlushDormancy DormancyFlush;` — This delegate is cleared after broadcasting
- L978 _public member_ `FNotifyActorForceNetUpdate ForceNetUpdate;`

#### struct `FGlobalActorReplicationInfo`  
`struct FGlobalActorReplicationInfo`  
_L983-1072_
- desc: Per-Actor data that is global for the entire Replication Graph
- L985 _public function_ `FGlobalActorReplicationInfo(FClassReplicationInfo& ClassInfo) : LastPreReplicationFrame(0) , WorldLocation(ForceInitToZero) , bWantsToBeDormant(false) , bSwapRolesOnReplicate(false) , bWasWorldLocClamped(false) , Settings(ClassInfo)`
- L999 _public member_ `uint32 LastPreReplicationFrame = 0;` — The last time AActor::PreReplication was called. Used to track when we need to call it again.
- L1002 _public member_ `uint32 ForceNetUpdateFrame = 0;` — the last time game code called ForceNetUpdate on this actor
- L1005 _public member_ `FVector WorldLocation;` — Cached World Location of the actor
- L1008 _public member_ `uint32 bWantsToBeDormant : 1;` — Mirrors AActor::NetDormancy > DORM_Awake
- L1011 _public member_ `uint32 bSwapRolesOnReplicate : 1;` — True if we should swap the actor role and remote role before calling ReplicateActor()
- L1014 _public member_ `uint32 bWasWorldLocClamped : 1;` — Set when the object is found with an invalid world location
- L1017 _public member_ `FClassReplicationInfo Settings;` — Class default mirrors: state that is initialized directly from class defaults (and can be later changed on a per-actor basis)
- L1020 _public member_ `TUniquePtr<FFastSharedReplicationInfo> FastSharedReplicationInfo;` — Fast Shared path data
- L1023 _public member_ `uint32 LastFlushNetDormancyFrame = 0;` — Last frame FlushNetDormancy was called. Used to early out when it is called multiple times per frame
- L1028 _public member_ `FGlobalActorReplicationEvents Events;`
- L1030 _public prototype_ `void LogDebugString(FOutputDevice& Ar) const;`
- L1032 _public function_ `void CountBytes(FArchive& Ar) const`
- L1046 _public function_ `inline void GatherDependentActorLists(const UNetReplicationGraphConnection& ConnectionManager, FGatheredReplicationActorLists& OutGatheredList)` — Gather the list of dependent actors filtered by the connection's level visibility
- L1052 _public prototype_ `void NotifyActorRenamed(AActor* Actor, FName PreviousLevelName);` — Update actor to new level
- L1054 _public typedef_ `typedef TArray<FActorRepListType> FDependantListType;`
- L1057 _public function_ `const FGlobalActorReplicationInfo::FDependantListType& GetDependentActorList()` — `UE_DEPRECATED(5.2, "The dependent actors are exposed via GatherDependentActorLists now.")`
- L1068 _private member_ `FLevelBasedActorList DependentActorList;` — When this actor replicates, we replicate these actors immediately afterwards if the client has their level loaded too and the net updated frequency is not too quick
- L1071 _private member_ `TArray<AActor*> ParentActorList;` — When this actor is added to the dependent list of a parent, track the parent here

#### struct `TClassMap`  
`template<typename ValueType> struct TClassMap`  
_L1076-1194_
- desc: Templatd struct for mapping UClasses to some data type. The main things this provides is that if a UClass* was not explicitly added, it will climb the class heirachy and find the best match (and then store this for faster lookup next time)
- L1079 _public function_ `ValueType& GetChecked(UClass* Class)` — Returns ClassInfo for a given class.
- L1086 _public function_ `ValueType* Get(UClass* Class)`
- L1112 _public function_ `const ValueType* FindWithoutClassRecursion(UClass* Class) const` — Just finds element. Does not climb class hierarchy is explicit entry is not found.
- L1118 _public function_ `bool Contains(const UClass* Class, bool bIncludeSuperClasses) const` — Returns if class has data in the map.
- L1138 _public function_ `void Set(UClass* InClass, const ValueType& Value)` — Sets class info for a given class. Call this in your Replication Graphs setup
- L1154 _public function_ `void Emplace(UClass* InClass, ValueType&& Value)`
- L1159 _public function_ `inline typename TMap<FObjectKey, ValueType>::TIterator CreateIterator()`
- L1160 _public function_ `inline void Reset()`
- L1162 _public member_ `TFunction<bool(UClass*, ValueType&)> InitNewElement;`
- L1164 _public function_ `void CountBytes(FArchive& Ar) const`
- L1171 _private function_ `ValueType* GetClassInfoForNewClass_r(FObjectKey OriginalObjKey, const UClass* OriginalClass)`
- L1193 _private member_ `TMap<FObjectKey , ValueType> Map;`

#### struct `FGlobalActorReplicationInfoMap`  
`struct FGlobalActorReplicationInfoMap`  
_L1196-1390_
- L1198 _public function_ `FGlobalActorReplicationInfoMap()`
- L1206 _public function_ `FGlobalActorReplicationInfo& Get(const FActorRepListType& Actor)` — Returns data associated with the actor. Will create it with default class values if necessary
- L1226 _public function_ `FGlobalActorReplicationInfo& Get(const FActorRepListType& Actor, bool& bWasCreated)` — Same as above but outputs bool if it was created. This is uncommonly called. Don't want to slow down the frequently called version
- L1246 _public function_ `void SetInitClassInfoFunc(TFunction<bool(UClass*, FClassReplicationInfo&)> Func)`
- L1253 _public function_ `inline FGlobalActorReplicationInfo* Find(const FActorRepListType& Actor) const` — Finds data associated with the actor but does not create if its not there yet.
- L1264 _public prototype_ `int32 Remove(const FActorRepListType& RemovedActor);` — Removes actor data from map
- L1267 _public prototype_ `void NotifyActorRenamed(AActor* Actor, FName PreviousStreamingLevelName);` — Update actor to new level
- L1270 _public function_ `inline FClassReplicationInfo& GetClassInfo(UClass* Class)` — Returns ClassInfo for a given class.
- L1273 _public function_ `inline void SetClassInfo(UClass* InClass, const FClassReplicationInfo& Info)` — Sets class info for a given class and its derived classes if desired. Call this in your Replication Graphs setup
- L1275 _public function_ `inline TMap<FActorRepListType, TUniquePtr<FGlobalActorReplicationInfo>>::TIterator CreateActorMapIterator()`
- L1276 _public function_ `inline TMap<FActorRepListType, TUniquePtr<FGlobalActorReplicationInfo>>::TConstIterator CreateActorMapIterator() const`
- L1277 _public function_ `inline TMap<FObjectKey, FClassReplicationInfo>::TIterator CreateClassMapIterator()`
- L1279 _public function_ `int32 Num() const`
- L1281 _public function_ `inline void ResetActorMap()`
- L1283 _public function_ `void CountBytes(FArchive& Ar) const`
- L1317 _public prototype_ `void AddDependentActor(AActor* Parent, AActor* Child, FGlobalActorReplicationInfoMap::EWarnFlag WarnFlag = FGlobalActorReplicationInfoMap::EWarnFlag::None);` — AddDependentActor makes a dependent actor (the child) considered for replication whenever the parent actor is replicated to a client. When the parent is replicated, the child actor will be also replicated even if it is outside it's net cull distance. The child will NOT be replicated if it has no data to send or the net update frequency is too quick since the last netupdate. Note that this link is one way only, meaning if a child replicates by itself it will not force it's parents to be replicated at the same time. When setting a dependent link, it is the caller's responsibility to remove the dependency if one of the actor gets destroyed. @param Parent Actor that will try to also replicate the child. @param Child The actor that we will try to replicate when the parent actor is replicated. @param WarnFlag Set a flag to trigger an ensure and detect when two actors get set dependent multiple times.
- L1323 _public function_ `void RemoveDependentActor(AActor* Parent, AActor* Child)` — RemoveDependentActor will remove the given child actor from the parent's dependent list. This will stop making the child actor try to be replicated whenever the parent actor is
- L1339 _public function_ `void RemoveAllActorDependencies(AActor* MainActor, FGlobalActorReplicationInfo* MainActorInfo)`
- L1372 _public function_ `void RemoveAllActorDependancies(AActor* MainActor)` — `UE_DEPRECATED(5.2, "Fixed a typo. Use RemoveAllActorDependencies instead")`
- L1377 _public function_ `void RemoveAllActorDependencies(AActor* MainActor)`
- L1388 _private member_ `TMap<FActorRepListType, TUniquePtr<FGlobalActorReplicationInfo>> ActorMap;`
- L1389 _private member_ `TClassMap<FClassReplicationInfo> ClassMap;`

#### enum `FGlobalActorReplicationInfoMap::EWarnFlag`  
`enum class EWarnFlag : uint8`  
_L1298-1304_
- L1300 _public enumerator_ `None = 0`
- L1301 _public enumerator_ `WarnAlreadyDependant = 1 << 0`
- L1302 _public enumerator_ `WarnParentNotRegistered = 1 << 1`
- L1303 _public enumerator_ `AllWarnings = WarnAlreadyDependant | WarnParentNotRegistered`

#### struct `FConnectionReplicationActorInfo`  
`struct FConnectionReplicationActorInfo`  
_L1395-1467_
- desc: Per-Actor data that is stored per connection
- L1397 _public function_ `FConnectionReplicationActorInfo() : bDormantOnConnection(0), bTearOff(0), bGridSpatilization_AlreadyDormant(0), bForceCullDistanceToZero(0)`
- L1399 _public function_ `FConnectionReplicationActorInfo(const FGlobalActorReplicationInfo& GlobalInfo) : bDormantOnConnection(0), bTearOff(0), bGridSpatilization_AlreadyDormant(0), bForceCullDistanceToZero(0)`
- L1410 _public function_ `void ResetFrameCounters()` — Resets the data, except for the "settings" data that we pulled from GlobalInfo
- L1423 _public function_ `void SetCullDistanceSquared(float InCullDistanceSquared)`
- L1429 _public function_ `float GetCullDistance() const`
- L1430 _public function_ `float GetCullDistanceSquared() const`
- L1432 _public member_ `UActorChannel* Channel = nullptr;`
- L1435 _private member_ `float CullDistance = 0.f;`
- L1436 _private member_ `float CullDistanceSquared = 0.f;`
- L1441 _public member_ `uint32 NextReplicationFrameNum = 0;` — Default replication
- L1442 _public member_ `uint32 LastRepFrameNum = 0;` — uint32	NextReplicationFrameNum = 0;	  The next frame we are allowed to replicate on
- L1445 _public member_ `uint32 FastPath_NextReplicationFrameNum = 0;` — FastPath versions of the above
- L1446 _public member_ `uint32 FastPath_LastRepFrameNum = 0;`
- L1449 _public member_ `uint16 ReplicationPeriodFrame = 1;` — Min frames that have to pass between subsequent calls to ReplicateActor
- L1450 _public member_ `uint16 FastPath_ReplicationPeriodFrame = 1;`
- L1453 _public member_ `uint32 ActorChannelCloseFrameNum = 0;` — The frame num that we will close the actor channel. This will get updated/pushed anytime the actor replicates based on FGlobalActorReplicationInfo::ActorChannelFrameTimeout
- L1455 _public member_ `uint8 bDormantOnConnection:1;`
- L1456 _public member_ `uint8 bTearOff:1;`
- L1459 _public member_ `uint8 bGridSpatilization_AlreadyDormant:1;` — Used as an optimization when doing 2D Grid Spatilization, prevents replicating the dormancy of the same actor twice in splitscreen evaluations.
- L1464 _public member_ `uint8 bForceCullDistanceToZero:1;` — When enabled: GetCullDistance() and GetCullDistanceSquared() will return 0.0f. When disabled: GetCullDistance() and GetCullDistanceSquared() return CullDistance and CullDistanceSquared respectively. Useful for temporarily making the actor on this connection always relevant.
- L1466 _public prototype_ `void LogDebugString(FOutputDevice& Ar) const;`

#### struct `FPerConnectionActorInfoMap`  
`struct FPerConnectionActorInfoMap`  
_L1470-1570_
- desc: Map for Actor -> ConnectionActorInfo. This wraps the TMap mainly so we can do custom initialization in FindOrAdd.
- L1472 _public function_ `inline FConnectionReplicationActorInfo& FindOrAdd(const FActorRepListType& Actor)`
- L1484 _public function_ `inline FConnectionReplicationActorInfo* Find(const FActorRepListType& Actor)`
- L1494 _public function_ `inline FConnectionReplicationActorInfo* FindByChannel(UActorChannel* Channel)`
- L1504 _public function_ `inline void AddChannel(const FActorRepListType& Actor, UActorChannel* Channel)`
- L1512 _public function_ `inline void RemoveChannel(UActorChannel* Channel)`
- L1517 _public function_ `inline void RemoveActor(const FActorRepListType& Actor)`
- L1522 _public function_ `inline TMap<FActorRepListType, TSharedPtr<FConnectionReplicationActorInfo>>::TIterator CreateIterator()`
- L1527 _public function_ `inline void SetGlobalMap(FGlobalActorReplicationInfoMap* InGlobalMap)`
- L1532 _public function_ `inline TMap<UActorChannel*, TSharedPtr<FConnectionReplicationActorInfo>>::TIterator CreateChannelIterator()`
- L1537 _public function_ `void ResetActorMap()`
- L1543 _public function_ `int32 Num() const`
- L1545 _public function_ `void CountBytes(FArchive& Ar) const`
- L1567 _private member_ `TMap<FActorRepListType, TSharedPtr<FConnectionReplicationActorInfo>> ActorMap;`
- L1568 _private member_ `TMap<UActorChannel*, TSharedPtr<FConnectionReplicationActorInfo>> ChannelMap;`
- L1569 _private member_ `FGlobalActorReplicationInfoMap* GlobalMap;`

#### struct `FReplicationGraphGlobalData`  
`struct FReplicationGraphGlobalData`  
_L1573-1583_
- desc: Data that every replication graph has access to/is initialized with
- L1575 _public function_ `FReplicationGraphGlobalData()`
- L1576 _public function_ `FReplicationGraphGlobalData(FGlobalActorReplicationInfoMap* InRepMap, UWorld* InWorld, UReplicationGraph* InReplicationGraph) : GlobalActorReplicationInfoMap(InRepMap), World(InWorld), ReplicationGraph(InReplicationGraph)`
- L1578 _public member_ `FGlobalActorReplicationInfoMap* GlobalActorReplicationInfoMap = nullptr;`
- L1580 _public member_ `UWorld* World = nullptr;`
- L1582 _public member_ `UReplicationGraph* ReplicationGraph = nullptr;`

#### struct `FPrioritizedActorFullDebugDetails`  
`struct FPrioritizedActorFullDebugDetails`  
_L1592-1622_
- desc: Stores "full debug details" about how an actor was prioritized. This is not used in the actual replication code, just saved off for logging/debugging.
- L1594 _public function_ `explicit FPrioritizedActorFullDebugDetails(FActorRepListType InActor) : Actor(InActor)`
- L1600 _public member_ `FActorRepListType Actor;`
- L1601 _public member_ `FVector::FReal DistanceSq = 0.f;`
- L1602 _public member_ `float DistanceFactor = 0.f;`
- L1604 _public member_ `uint32 FramesSinceLastRap = 0;`
- L1605 _public member_ `float StarvationFactor = 0.f;`
- L1607 _public member_ `uint32 ForceNetUpdateDelta = 0;`
- L1608 _public member_ `float GameCodeScaling = 0.f;`
- L1610 _public function_ `FString BuildString() const`

#### struct `FSkippedActorFullDebugDetails`  
`struct FSkippedActorFullDebugDetails`  
_L1625-1632_
- desc: Debug data about an actor that was skipped during the prioritization phase
- L1627 _public function_ `explicit FSkippedActorFullDebugDetails(FActorRepListType InActor) : Actor(InActor)`
- L1628 _public member_ `FActorRepListType Actor;`
- L1629 _public member_ `bool bWasDormant = false;` — If set, was skipped because it is dormant on this connection
- L1630 _public member_ `float DistanceCulled = 0.f;` — If set, was skipped due to distance culling
- L1631 _public member_ `uint32 FramesTillNextReplication = 0;` — If set, was skipped due to not being ready for replication

#### struct `FPrioritizedRepList`  
`struct FPrioritizedRepList`  
_L1635-1705_
- desc: Prioritized List of actors to replicate. This is what we actually use to replicate actors.
- L1637 _public prototype_ `FPrioritizedRepList() = default;`
- L1638 _public function_ `explicit FPrioritizedRepList(const FPrioritizedRepList& Other)`
- L1653 _public member_ `TArray<FItem> Items;`
- L1655 _public function_ `void CountBytes(FArchive& Ar) const`
- L1674 _public function_ `void Reset()`
- L1684 _public function_ `FPrioritizedActorFullDebugDetails* GetNextFullDebugDetails(FActorRepListType Actor)`
- L1692 _public member_ `TUniquePtr<TArray<FPrioritizedActorFullDebugDetails> > FullDebugDetails;`
- L1695 _public function_ `FSkippedActorFullDebugDetails* GetNextSkippedDebugDetails(FActorRepListType Actor)`
- L1703 _public member_ `TUniquePtr<TArray<FSkippedActorFullDebugDetails> > SkippedDebugDetails;`

#### struct `FPrioritizedRepList::FItem`  
`struct FItem`  
_L1640-1651_
- L1642 _public function_ `FItem(float InPriority, FActorRepListType InActor, FGlobalActorReplicationInfo* InGlobal, FConnectionReplicationActorInfo* InConn) : Priority(InPriority), Actor(InActor) , GlobalData(InGlobal), ConnectionData(InConn)`
- L1644 _public function_ `bool operator<(const FItem& Other) const`
- L1646 _public member_ `float Priority;`
- L1647 _public member_ `FActorRepListType Actor;`
- L1649 _public member_ `FGlobalActorReplicationInfo* GlobalData;`
- L1650 _public member_ `FConnectionReplicationActorInfo* ConnectionData;`

#### struct `FConnectionGatherActorListParameters`  
`struct FConnectionGatherActorListParameters`  
_L1720-1769_
- desc: Parameter structure for what we actually pass down during the Gather phase.
- L1722 _public function_ `FConnectionGatherActorListParameters( FNetViewerArray& InViewers, UNetReplicationGraphConnection& InConnectionManager, const TSet<FName>& InClientVisibleLevelNamesRef, uint32 InReplicationFrameNum, FGatheredReplicationActorLists& InOutGatheredReplicationLists, bool bInSelectedForHeavyComputation) : Viewers(InViewers) , ConnectionManager(InConnectionManager) , ReplicationFrameNum(InReplicationFrameNum) , OutGatheredReplicationLists(InOutGatheredReplicationLists) , ClientVisibleLevelNamesRef(InClientVisibleLevelNamesRef) , bIsSelectedForHeavyComputation(bInSelectedForHeavyComputation)`
- L1738 _public member_ `FNetViewerArray Viewers;`
- L1739 _public member_ `UNetReplicationGraphConnection& ConnectionManager;`
- L1740 _public member_ `uint32 ReplicationFrameNum;`
- L1743 _public member_ `FGatheredReplicationActorLists& OutGatheredReplicationLists;` — Out: The data nodes are going to add to
- L1745 _public function_ `bool CheckClientVisibilityForLevel(const FName& StreamingLevelName) const`
- L1763 _public member_ `const TSet<FName>& ClientVisibleLevelNamesRef;` — Cached off reference for fast Level Visibility lookup
- L1764 _public member_ `const bool bIsSelectedForHeavyComputation;`
- L1768 _private member_ `mutable FName LastCheckedVisibleLevelName;`

#### struct `FRPCSendPolicyInfo`  
`struct FRPCSendPolicyInfo`  
_L1777-1795_
- L1779 _public function_ `FRPCSendPolicyInfo(const bool bInSendImmediately) : bSendImmediately(bInSendImmediately)`
- L1792 _public member_ `uint8 bSendImmediately:1;` — When true this will modify the send behavior of an RPC. If the RPC is called from inside NetDriver::TickDispatch (aka during packet reception and remote RPC execution) then the RPC will get immediately sent to remote clients at the end of TickDispatch before the regular game tick. This reduces latency since normally RPCs are sent alongside normal replicated data at the end of the frame during NetDriver::TickFlush. The drawbacks are extra bandwidth cost and higher CPU usage. Note that with Unreliable Multicasts, this flag changes their order when executed on the remote client. By default only Unreliable Multicasts are executed after replicated properties have been applied on the simulated actor. With this flag they get executed before any replicated properties are applied.

#### struct `FReplicationGraphDebugInfo`  
`struct FReplicationGraphDebugInfo`  
_L1803-1825_
- L1805 _public function_ `FReplicationGraphDebugInfo( FOutputDevice& InAr ) : Ar(InAr)`
- L1815 _public member_ `FOutputDevice& Ar;`
- L1816 _public member_ `EFlags Flags;`
- L1817 _public member_ `bool bShowEmptyNodes = false;`
- L1818 _public member_ `FString CurrentIndentString;`
- L1819 _public member_ `const FString IndentString = TEXT(" "`
- L1821 _public function_ `void Log(const FString& Str)`
- L1823 _public function_ `void PushIndent()`
- L1824 _public function_ `void PopIndent()`

#### enum `FReplicationGraphDebugInfo::EFlags`  
`enum EFlags`  
_L1807-1813_
- L1809 _public enumerator_ `ShowActors`
- L1810 _public enumerator_ `ShowClasses`
- L1811 _public enumerator_ `ShowNativeClasses`
- L1812 _public enumerator_ `ShowTotalCount`

#### struct `FPrioritizedActorDebugInfo`  
`struct FPrioritizedActorDebugInfo`  
_L1829-1836_
- L1831 _public member_ `int32 DormantCount = 0;`
- L1832 _public member_ `int32 NotReadyCount = 0;`
- L1833 _public member_ `int32 DistanceCulledCount = 0;`
- L1834 _public member_ `int32 ReplicatedCount = 0;`
- L1835 _public member_ `int32 StarvedCount = 0;`

#### struct `FNativeClassAccumulator`  
`struct FNativeClassAccumulator`  
_L1839-1874_
- L1841 _public function_ `void Increment(UClass* Class)`
- L1855 _public function_ `FString BuildString()`
- L1866 _public function_ `void CountBytes(FArchive& Ar) const`
- L1871 _public function_ `void Reset()`
- L1872 _public function_ `void Sort()`
- L1873 _public member_ `TMap<UClass*, int32> Map;`

#### struct `FReplicationGraphCSVTracker`  
`struct FReplicationGraphCSVTracker`  
_L1904-2313_
- desc: Helper struct for tracking finer grained ReplicationGraph stats through the CSV profiler. Intention is that it is setup/configured in the UReplicationGraph subclasses
- L1915 _public prototype_ `FReplicationGraphCSVTracker();`
- L1917 _public function_ `void TearDown()`
- L1935 _public function_ `void SetExplicitClassTracking(UClass* ExactActorClass, const FString& StatNamePrefix)` — Tracks an explicitly set class. This does NOT include child classes! This is the fastest stat and should be fine to enable in shipping/test builds.
- L1944 _public function_ `void SetExplicitClassTracking_FastPath(UClass* ExactActorClass, const FString& StatNamePrefix)` — Sets explicit class tracking for fast/shared path replication. Does not include base classes
- L1954 _public function_ `void SetImplicitClassTracking(UClass* BaseActorClass, const FString& StatNamePrefix)` — Tracks a class and all of its children (under a single stat set). This will be a little slower (TMap lookup) but still probably ok if used in moderation (only track your top 3 or so classes)
- L1962 _public function_ `bool VisibleLevelConnectionAdded(FName LevelName)` — Returns true when the level data is created for the first time
- L1984 _public function_ `void VisibleLevelConnectionRemoved(FName LevelName)`
- L1998 _public function_ `void SetVisibleLevelCustomName(FName LevelName, const FString& CustomReadableName)`
- L2021 _public function_ `void PostReplicateActor(UClass* ActorClass, const double Time, const int64 Bits, const bool bIsActorDiscovery)` — `UE_DEPRECATED(5.1, "Use the overload of PostReplicateActor that takes EActorFlags.")`
- L2028 _public function_ `void PostReplicateActor(UClass* ActorClass, const double Time, const int64 Bits, const EActorFlags Flags)`
- L2086 _public function_ `void PostFastPathReplication(UClass* ActorClass, const double Time, const int64 Bits)`
- L2109 _public function_ `void PostActorChannelCreated(UClass* ActorClass)`
- L2131 _public function_ `void PostActorForceUpdated(UClass* ActorClass)`
- L2153 _public function_ `void ResetTrackedClasses()`
- L2165 _public function_ `void EndReplicationFrame()`
- L2209 _public function_ `void CountBytes(FArchive& Ar) const`
- L2219 _public function_ `void SetReportUntrackedClasses(bool bReport)`
- L2237 _public function_ `const TArray<FReplicationGraphCSVTracker::FVisibleLevelData>& GetVisibleLevelsData() const`
- L2276 _private member_ `TMap<TObjectKey<UClass>, FTrackedData> ExplicitClassTracker;`
- L2277 _private member_ `TMap<TObjectKey<UClass>, FTrackedData> ExplicitClassTracker_FastPath;`
- L2279 _private member_ `TClassMap<TSharedPtr<FTrackedData>> ImplicitClassTracker;`
- L2281 _private member_ `TArray<TSharedPtr<FTrackedData>> UniqueImplicitTrackedData;`
- L2283 _private member_ `FTrackedData EverythingElse;`
- L2284 _private member_ `FTrackedData EverythingElse_FastPath;`
- L2285 _private member_ `FTrackedData ActorDiscovery;`
- L2287 _private member_ `TMap<TObjectKey<UClass>, uint32> UntrackedReplications;`
- L2290 _private member_ `TArray<FVisibleLevelData> VisibleLevelConnectionTracker;` — Counts the number of connections who are currently seeing each level name
- L2292 _private member_ `bool bIsCapturing = false;`
- L2293 _private member_ `bool bReportUntrackedClasses = false;`
- L2296 _private function_ `void PushStats(FCsvProfiler* Profiler, FTrackedData& Data)`

#### enum `FReplicationGraphCSVTracker::EActorFlags`  
`enum class EActorFlags : uint8`  
_L1906-1911_
- L1908 _public enumerator_ `None = 0`
- L1909 _public enumerator_ `IsInDiscovery = 1 << 0`
- L1910 _public enumerator_ `AlreadyReplicatedThisFrame = 1 << 1`

#### struct `FReplicationGraphCSVTracker::FVisibleLevelData`  
`struct FVisibleLevelData`  
_L2226-2234_
- L2228 _public member_ `FName LevelName;`
- L2229 _public member_ `int32 NbConnections;`
- L2230 _public member_ `FName CustomReadableName;`
- L2232 _public function_ `bool operator==(const FVisibleLevelData& Other) const`
- L2233 _public function_ `bool operator==(const FName& InLevelName) const`

#### struct `FReplicationGraphCSVTracker::FTrackedData`  
`struct FTrackedData`  
_L2241-2274_
- L2243 _public prototype_ `FTrackedData() = default;`
- L2245 _public function_ `explicit FTrackedData(FString Suffix)`
- L2252 _public member_ `double CPUTimeAccumulated = 0.0;`
- L2253 _public member_ `double CleanCPUTimeAccumulated = 0.0;`
- L2254 _public member_ `double RedundantRepCPUTimeAccumulated = 0.0;`
- L2255 _public member_ `int64 BitsAccumulated = 0;`
- L2256 _public member_ `int32 ChannelsOpened = 0;`
- L2257 _public member_ `int32 NumReplications = 0;`
- L2258 _public member_ `int32 CleanNumReplications = 0;`
- L2259 _public member_ `int32 ForcedUpdates = 0;`
- L2261 _public member_ `FName StatName;`
- L2263 _public function_ `void Reset()`

#### struct `FActorConnectionPair`  
`struct FActorConnectionPair`  
_L2318-2335_
- desc: Debug Actor/Connection pair that can be set by code for further narrowing down breakpoints/logging
- L2320 _public function_ `FActorConnectionPair()`
- L2321 _public prototype_ `FActorConnectionPair(AActor* InActor, UNetConnection* InConnection);`
- L2323 _public member_ `TWeakObjectPtr<AActor> Actor;`
- L2324 _public member_ `TWeakObjectPtr<UNetConnection> Connection;`
- L2331 _public function_ `inline bool operator==(const FActorConnectionPair& A) const`

#### struct `FActorRepListStatCollector`  
`struct FActorRepListStatCollector`  
_L2343-2384_
- desc: This struct will passed to all nodes in the repgraph and collect information on every ActorRepList
- L2346 _public function_ `FActorRepListStatCollector()`
- L2349 _public prototype_ `void VisitRepList(const UReplicationGraphNode* NodeToVisit, const FActorRepListRefView& RepList);` — Collect stats on a single FActorRepList
- L2352 _public prototype_ `void VisitStreamingLevelCollection(const UReplicationGraphNode* NodeToVisit, const struct FStreamingLevelActorListCollection& StreamingLevelList);` — Collect stats on a collection of FActorRepLists
- L2355 _public prototype_ `void VisitExplicitStreamingLevelList(FName ListOwnerName, FName StreamLevelName, const FActorRepListRefView& RepList);` — Collect stats for FActorRepLists not held by a node
- L2358 _public prototype_ `void FlagNodeVisited(const UReplicationGraphNode* NodeToVisit);` — Prevents the node from being visited twice in case it's shared multiple times
- L2361 _public prototype_ `void PrintCollectedData(FOutputDevice& Ar);` — Print the statistics previously collected
- L2365 _private prototype_ `bool WasNodeVisited(const UReplicationGraphNode* NodeToVisit);`
- L2378 _private member_ `TMap<FName, FRepListStats> PerClassStats;`
- L2380 _private member_ `TMap<FName, FRepListStats> PerStreamingLevelStats;`
- L2383 _private member_ `TMap<const UObject*, bool> VisitedNodes;` — Keeps track if a node was already collected since the same node can be shared across connections and visited multiple times

#### struct `FActorRepListStatCollector::FRepListStats`  
`struct FRepListStats`  
_L2369-2376_
- L2371 _public member_ `uint32 NumLists = 0;`
- L2372 _public member_ `uint32 NumActors = 0;`
- L2373 _public member_ `uint32 MaxListSize = 0;`
- L2374 _public member_ `uint32 NumSlack = 0;`
- L2375 _public member_ `uint64 NumBytes = 0;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API REPLICATIONGRAPH_API`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogReplicationGraph, Log, All );`
- L40 _macro_ `#define REPGRAPH_DETAILS 1`
- L41 _macro_ `#define DO_REPGRAPH_DETAILS(X) (X)`
- L42 _macro_ `#define repCheck(x) check(x)`
- L43 _macro_ `#define repCheckf(expr, format, ...) checkf(expr, format, ##__VA_ARGS__ )`
- L44 _macro_ `#define RG_QUICK_SCOPE_CYCLE_COUNTER(x) QUICK_SCOPE_CYCLE_COUNTER(x)`
- L45 _externvar_ `extern int32 CVar_RepGraph_Verify;`
- L47 _macro_ `#define REPGRAPH_DETAILS 0`
- L48 _macro_ `#define DO_REPGRAPH_DETAILS(X) 0`
- L49 _macro_ `#define repCheck(x)`
- L50 _macro_ `#define repCheckf(expr, format, ...)`
- L51 _macro_ `#define RG_QUICK_SCOPE_CYCLE_COUNTER(X)`
- L55 _macro_ `#define REPGRAPH_STR(x) #x`
- L56 _macro_ `#define REPGRAPH_DEVCVAR_SHIPCONST(Type,VarName,Var,Value,Help) \`
- L65 _macro_ `#define REPGRAPH_ENABLE_FORCENETUPDATE_DELEGATE 1`
- L80 _macro_ `#define UE_ENABLE_ACTOR_REPLIST_TRACKING 0`
- L83 _macro_ `#define UE_ACTOR_REPLIST_TYPE_EXTRA_SAFETY (UE_SERVER && UE_ENABLE_ACTOR_REPLIST_TRACKING)`
- L86 _typedef_ `typedef AActor* FActorRepListType;`
- L89 _namespace_ `namespace UE`
- L89 _namespace_ `namespace Net` (scope `UE`)
- L89 _namespace_ `namespace RepGraph` (scope `UE::Net`)
- L93 _variable_ `inline bool bUseWeakPointers = false;` (scope `UE::Net::RepGraph`) — Whether to store weak pointers in actor replication lists and validate them on use. When false, raw pointers are used instead.
- L158 _function_ `friend bool operator==(const FActorRepListType& Left, const FActorRepListType& Right)`
- L170 _function_ `friend bool operator!=(const FActorRepListType& Left, const FActorRepListType& Right)`
- L175 _function_ `friend bool operator==(const FActorRepListType& RepListActor, AActor* RawActor)`
- L179 _function_ `friend bool operator!=(const FActorRepListType& RepListActor, AActor* RawActor)`
- L184 _function_ `friend bool operator==(AActor* RawActor, const FActorRepListType& RepListActor)`
- L188 _function_ `friend bool operator!=(AActor* RawActor, const FActorRepListType& RepListActor)`
- L194 _function_ `friend bool operator==(const FActorRepListType& RepListActor, TYPE_OF_NULLPTR)` — comparison with nullptr without resolving weak pointer or implicitly constructing a new FActorRepListType(nullptr).
- L204 _function_ `friend bool operator!=(const FActorRepListType& RepListActor, TYPE_OF_NULLPTR)`
- L208 _function_ `friend bool operator==(TYPE_OF_NULLPTR, const FActorRepListType& RepListActor)`
- L212 _function_ `friend bool operator!=(TYPE_OF_NULLPTR, const FActorRepListType& RepListActor)`
- L297 _function_ `template< class T > inline T* Cast(const FActorRepListType& Src)`
- L298 _function_ `template< class T > inline T* Cast(const FActorRepListType& Src)`
- L299 _function_ `template< class T > inline T* Cast(const FActorRepListType& Src)`
- L305 _function_ `inline FString GetActorRepListTypeDebugString(const FActorRepListType& In)`
- L306 _function_ `inline UClass* GetActorRepListTypeClass(const FActorRepListType& In)`
- L317 _function_ `inline bool IsActorValidForReplication(const AActor* Actor)` — Tests if an actor is valid for replication: not pending kill, etc. Says nothing about wanting to replicate or should replicate, etc.
- L321 _function_ `inline bool IsActorValidForReplication(const FActorRepListType& In)`
- L326 _prototype_ `void LogMoreInfoOnIsActorValidFailure(const FActorRepListType& In);`
- L327 _function_ `inline bool IsActorValidForReplication_LogMoreInfo(const FActorRepListType& In)`
- L339 _function_ `inline bool IsActorValidForReplicationGather(const FActorRepListType& In)` — Tests if an actor is valid for replication gathering. Meaning, it can be gathered from the replication graph and considered for replication.
- L474 _function_ `inline friend FActorRepListType* begin(const TActorRepListViewBase<PointerType>& View)`
- L475 _function_ `inline friend FActorRepListType* end(const TActorRepListViewBase<PointerType>& View)`
- L636 _prototype_ `extern "C" DLLEXPORT void PrintRepListDetails(int32 PoolSize, int32 BlockIdx, int32 ListIdx)` — Intended to be called from immediate mode window while debugging
- L637 _prototype_ `extern "C" DLLEXPORT void PrintRepListStats(int32 mode=0)`
- L639 _prototype_ `void PrintRepListStatsAr(int32 mode, FOutputDevice& Ar=*GLog);`
- L966 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FNotifyActorChangeDormancy, FActorRepListType, FGlobalActorReplicationInfo&, ENetDormancy , ENetDormancy );`
- L966 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FNotifyActorChangeDormancy, FActorRepListType, FGlobalActorReplicationInfo&, ENetDormancy , ENetDormancy );`
- L967 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNotifyActorFlushDormancy, FActorRepListType, FGlobalActorReplicationInfo&);`
- L967 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNotifyActorFlushDormancy, FActorRepListType, FGlobalActorReplicationInfo&);`
- L970 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNotifyActorForceNetUpdate, FActorRepListType, FGlobalActorReplicationInfo&);`
- L970 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNotifyActorForceNetUpdate, FActorRepListType, FGlobalActorReplicationInfo&);`
- L1392 _prototype_ `ENUM_CLASS_FLAGS(FGlobalActorReplicationInfoMap::EWarnFlag);`
- L1595 _function_ `friend bool operator==(const FPrioritizedActorFullDebugDetails& Details, const FActorRepListType& InActor)`
- L1614 _function_ `auto Append = [&Str](FString InStr)` (scope `FPrioritizedActorFullDebugDetails::BuildString`)
- L1712 _macro_ `#define REPGRAPH_VIEWERS_PER_CONNECTION 4`
- L1716 _typedef_ `typedef TInlineAllocator<REPGRAPH_VIEWERS_PER_CONNECTION> FReplicationGraphConnectionsAllocator;` — Allocator for a connection and all of its sub connections
- L1717 _typedef_ `typedef TArray<FNetViewer, FReplicationGraphConnectionsAllocator> FNetViewerArray;`
- L1827 _prototype_ `void LogActorRepList(FReplicationGraphDebugInfo& DebugInfo, FString Prefix, const FActorRepListRefView& List);`
- L1877 _prototype_ `void ForEachClientPIEWorld(TFunction<void(UWorld*)> Func);`
- L1879 _function_ `inline void ForEachClientPIEWorld(TFunction<void(UWorld*)> Func)`
- L1889 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphMS);`
- L1890 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphKBytes);`
- L1891 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphChannelsOpened);`
- L1892 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphNumReps);`
- L1893 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphVisibleLevels);`
- L1894 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphForcedUpdates);`
- L1895 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphCleanMS);`
- L1896 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphCleanNumReps);`
- L1897 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(ReplicationGraphRedundantMS);`
- L1900 _macro_ `#define REPGRAPH_CSV_TRACKER (CSV_PROFILER_STATS && WITH_SERVER_CODE)`
- L2315 _prototype_ `ENUM_CLASS_FLAGS(FReplicationGraphCSVTracker::EActorFlags);`
- L2326 _function_ `friend uint32 GetTypeHash(const FActorConnectionPair& Pair)`
- L2338 _externvar_ `extern FActorConnectionPair DebugActorConnectionPair;` — Generic/global pair that can be set by debug commands etc for extra logging/debugging functionality
