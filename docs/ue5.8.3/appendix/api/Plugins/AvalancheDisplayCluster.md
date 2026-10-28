# Plugins / AvalancheDisplayCluster

- module root: `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster`
- headers: 6; symbols: 65
- symbol kinds: class=3, delegate=2, function=8, member=24, prototype=23, struct=5
- PrivateDependencyModuleNames: AvalancheMedia, DisplayCluster, Engine
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster/Private/AvaDisplayClusterLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaDisplayCluster, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaDisplayCluster, Log, All);`

### `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster/Private/AvaDisplayClusterModule.h` (Private)


#### class `FAvaDisplayClusterModule`  
`class FAvaDisplayClusterModule : public IModuleInterface`  
_L11-21_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `TUniquePtr<FAvaDisplayClusterSynchronizedEventsFeature> SyncEventsFeature;`

### `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster/Private/SynchronizedEvents/AvaDisplayClusterSyncEventsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaDisplayClusterSyncEvents, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaDisplayClusterSyncEvents, Log, All);`

### `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster/Private/SynchronizedEvents/AvaDisplayClusterSynchronizedEventsDispatcher.h` (Private)


#### struct `FAvaDisplayClusterClusterEventPayload`  
`struct FAvaDisplayClusterClusterEventPayload`  
_L13-34_
- L16 _public member_ `FString Dispatcher;` — Dispatcher Signature
- L18 _public member_ `FString Signature;` — Event Signature
- L19 _public member_ `FString NodeId;`
- L20 _public member_ `int32 EmitCount = 0;`
- L22 _public function_ `static void Serialize(FArchive& InArchive, FString& InOutDispatcher, FString& InOutSignature, FString& InOutNodeId, int32& InOutEmitCount)`
- L30 _public function_ `void Serialize(FArchive& InArchive)`

#### struct `FAvaDisplayClusterNodeInfo`  
`struct FAvaDisplayClusterNodeInfo`  
_L36-49_
- L38 _public function_ `void Mark(const FString& InNodeId)`
- L43 _public function_ `bool IsAllMarked(const TArray<FString>& InNodeIds) const`
- L48 _public member_ `TSet<FString> NodeIds;`

#### struct `FAvaDisplayClusterTrackedClusterEvent`  
`struct FAvaDisplayClusterTrackedClusterEvent`  
_L51-55_
- L53 _public member_ `FAvaDisplayClusterNodeInfo NodeInfo;`
- L54 _public member_ `FAvaDisplayClusterTimeStamp ReceivedTimeStamp;`

#### struct `FAvaDisplayClusterSynchronizedEvent`  
`struct FAvaDisplayClusterSynchronizedEvent : public FAvaMediaSynchronizedEvent`  
_L57-80_
- inherits: `FAvaMediaSynchronizedEvent`
- L59 _public function_ `FAvaDisplayClusterSynchronizedEvent(const FString& InSignature, TUniqueFunction<void()> InFunction) : FAvaMediaSynchronizedEvent(InSignature, MoveTemp(InFunction))`
- L64 _public function_ `FAvaDisplayClusterSynchronizedEvent(FString&& InSignature, TUniqueFunction<void()> InFunction) : FAvaMediaSynchronizedEvent(MoveTemp(InSignature), MoveTemp(InFunction))`
- L70 _public member_ `FAvaDisplayClusterNodeInfo NodeInfo;` — Tracks which node is marked.
- L73 _public member_ `FAvaDisplayClusterTimeStamp PushTimeStamp;` — Tracks time at which the event was pushed.
- L76 _public member_ `FAvaDisplayClusterTimeStamp LastEmitTimeStamp;` — Tracks last time the event was emitted.
- L79 _public member_ `int32 EmitCount = 0;` — Tracks number of times the event has been emitted.

#### class `FAvaDisplayClusterSynchronizedEventDispatcher`  
`class FAvaDisplayClusterSynchronizedEventDispatcher : public IAvaMediaSynchronizedEventDispatcher`  
_L82-123_
- inherits: `IAvaMediaSynchronizedEventDispatcher`
- L85 _public prototype_ `FAvaDisplayClusterSynchronizedEventDispatcher(const FString& InSignature);`
- L87 _public prototype_ `virtual ~FAvaDisplayClusterSynchronizedEventDispatcher() override = default;`
- L90 _public prototype_ `FString GetFrameInfo() const;` — Formatted frame info: time stamp and dispatcher's signature.
- L92 _public prototype_ `void OnClusterEventReceived(const FAvaDisplayClusterClusterEventPayload& InPayload);`
- L94 _public prototype_ `void EmitClusterEvent(FAvaDisplayClusterSynchronizedEvent& InEvent, const FAvaDisplayClusterTimeStamp& InNow, IDisplayClusterClusterManager* InClusterManager);`
- L96 _public prototype_ `void DispatchEvent(const FAvaDisplayClusterSynchronizedEvent* InEvent, const FAvaDisplayClusterTimeStamp& InNow ) const;`
- L99 _public prototype_ `virtual bool PushEvent(FString&& InEventSignature, TUniqueFunction<void()> InFunction) override;`
- L100 _public prototype_ `virtual EAvaMediaSynchronizedEventState GetEventState(const FString& InEventSignature) const override;`
- L101 _public prototype_ `virtual void DispatchEvents() override;`
- L105 _public member_ `FString Signature;` — Dispatcher's signature. (used for debugging purpose atm)
- L108 _public member_ `FString NodeId;` — Id of the current Cluster Node.
- L111 _public member_ `TArray<FString> AllNodeIds;` — All nodes in the cluster.
- L114 _public member_ `TMap<FString, TUniquePtr<FAvaDisplayClusterSynchronizedEvent>> PendingEvents;` — Pending events waiting on other node's signal.
- L117 _public member_ `TMap<FString, TUniquePtr<FAvaDisplayClusterTrackedClusterEvent>> TrackedEvents;` — Tracked Events that are received as cluster event prior to getting submitted locally.
- L120 _public member_ `TMap<FString, TUniquePtr<FAvaDisplayClusterSynchronizedEvent>> ReadyEvents;` — Events Ready to be locally dispatched.
- L122 _public member_ `static constexpr int32 SynchronizedEventsClusterEventId = 0xABCDEF01;`

### `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster/Private/SynchronizedEvents/AvaDisplayClusterSynchronizedEventsFeature.h` (Private)


#### class `FAvaDisplayClusterSynchronizedEventsFeature`  
`class FAvaDisplayClusterSynchronizedEventsFeature : public IAvaMediaSynchronizedEventsFeature`  
_L11-39_
- inherits: `IAvaMediaSynchronizedEventsFeature`
- L14 _public prototype_ `FAvaDisplayClusterSynchronizedEventsFeature();`
- L18 _public prototype_ `virtual FName GetName() const override;`
- L19 _public prototype_ `virtual FText GetDisplayName() const override;`
- L20 _public prototype_ `virtual FText GetDisplayDescription() const override;`
- L21 _public prototype_ `virtual int32 GetPriority() const override;`
- L22 _public prototype_ `virtual TSharedPtr<IAvaMediaSynchronizedEventDispatcher> CreateDispatcher(const FString& InSignature) override;`
- L27 _private prototype_ `void OnDisplayClusterStartSession();` — Event Handlers
- L28 _private prototype_ `void OnEndFrame();`
- L29 _private prototype_ `void OnBinaryClusterEventReceived(const FDisplayClusterClusterEventBinary& InClusterEvent);`
- L33 _private member_ `TMap<FString, TWeakPtr<FAvaDisplayClusterSynchronizedEventDispatcher>> DispatchersWeak;` — Keep track of the created dispatchers for routing the cluster events.
- L36 _private member_ `TMap<FString, TSharedPtr<FAvaDisplayClusterSynchronizedEventDispatcher>> TrackingDispatchers;` — Dispatchers only used for tracking cluster events when there is no active dispatcher created.
- L38 _private member_ `FOnClusterEventBinaryListener BinaryListener;`

### `Plugins/Experimental/AvalancheDisplayCluster/Source/AvalancheDisplayCluster/Private/Utils/AvaDisplayClusterTimeStamp.h` (Private)


#### struct `FAvaDisplayClusterTimeStamp`  
`struct FAvaDisplayClusterTimeStamp`  
_L10-30_
- desc: @brief TimeStamp utility for scheduling events, timeout, repeating, etc.
- L12 _public prototype_ `static FAvaDisplayClusterTimeStamp Now();`
- L14 _public function_ `double GetWaitTimeInMs(const FAvaDisplayClusterTimeStamp& InNow) const`
- L20 _public function_ `uint32 GetWaitTimeInFrames(const FAvaDisplayClusterTimeStamp& InNow) const`
- L26 _public member_ `FDateTime Time;` — Local System time. Not synchronized.
- L29 _public member_ `uint32 FrameNumber = 0;` — (Tentative) Keep track of synchronized frame number (for logging and detecting desyncs).
