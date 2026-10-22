# Plugins / DisplayCluster

- module root: `Plugins/Runtime/nDisplay/Source/DisplayCluster`
- headers: 301; symbols: 5638
- symbol kinds: class=253, delegate=66, enum=64, enumerator=293, externvar=84, function=944, macro=3, member=1201, namespace=65, prototype=2521, struct=91, typedef=16, variable=37
- PrivateDependencyModuleNames: CompositeCore, ConcertSyncClient, D3D11RHI, D3D12RHI, EditorWidgets, HeadMountedDisplay, InputCore, Json, JsonUtilities, LevelEditor, MediaAssets, MediaIOCore, Networking, OpenCV, OpenCVHelper, OpenColorIO, ProceduralMeshComponent, RHI, RenderCore, Renderer, SharedMemoryMedia, Slate, SlateCore, Sockets, UMG, UnrealEd
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, DisplayClusterConfiguration, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, Engine, EngineSettings, EnhancedInput, VirtualProduction
- PublicIncludePathModuleNames: DisplayClusterConfigurator

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Internal/IPDisplayCluster.h` (Internal)


#### class `IPDisplayCluster`  
`class IPDisplayCluster : public IDisplayCluster , public IPDisplayClusterManager`  
_L17-38_
- inherits: `IDisplayCluster,IPDisplayClusterManager`
- desc: Private module interface
- L23 _public prototype_ `virtual ~IPDisplayCluster() = default;`
- L28 _public prototype_ `virtual IPDisplayClusterRenderManager* GetPrivateRenderMgr() const = 0;` — Returns private render manager interface
- L31 _public prototype_ `virtual IPDisplayClusterClusterManager* GetPrivateClusterMgr() const = 0;` — Returns private cluster manager interface
- L34 _public prototype_ `virtual IPDisplayClusterConfigManager* GetPrivateConfigMgr() const = 0;` — Returns private config manager interface
- L37 _public prototype_ `virtual IPDisplayClusterGameManager* GetPrivateGameMgr() const = 0;` — Returns private game manager interface

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Internal/IPDisplayClusterManager.h` (Internal)


#### class `IPDisplayClusterManager`  
`class IPDisplayClusterManager`  
_L15-64_
- desc: Private manager interface
- L18 _public prototype_ `virtual ~IPDisplayClusterManager() = default;`
- L22 _public function_ `virtual bool Init(EDisplayClusterOperationMode OperationMode)` — Called at start to initialize internals
- L26 _public function_ `virtual void Release()` — Called before application/Editor exit to release internals
- L30 _public function_ `virtual bool StartSession(UDisplayClusterConfigurationData* InConfigData, const FString& InNodeId)` — Called on each session start before first level start (before the first tick)
- L34 _public function_ `virtual void EndSession()` — Called on each session end at early step before exit (before UGameEngine::Preexit)
- L38 _public function_ `virtual bool StartScene(UWorld* InWorld)` — Called each time a new game level starts
- L42 _public function_ `virtual void EndScene()` — Called when current level is going to be closed (i.e. when loading new map)
- L46 _public function_ `virtual void StartFrame(uint64 FrameNum)` — Called before start every frame
- L50 _public function_ `virtual void EndFrame(uint64 FrameNum)` — Called before start every frame
- L54 _public function_ `virtual void PreTick(float DeltaSeconds)` — Called every frame before world Tick
- L58 _public function_ `virtual void Tick(float DeltaSeconds)` — Called every frame during world Tick
- L62 _public function_ `virtual void PostTick(float DeltaSeconds)` — Called every frame during world Tick

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Blueprints/DisplayClusterBlueprintAPIImpl.h` (Private)


#### class `UDisplayClusterBlueprintAPIImpl`  
`class UDisplayClusterBlueprintAPIImpl : public UObject , public IDisplayClusterBlueprintAPI`  
_L15-97_
- reflection: `UCLASS()`
- inherits: `UObject,IDisplayClusterBlueprintAPI`
- desc: Blueprint API interface implementation
- L25 _public function_ `virtual bool IsModuleInitialized() const override` — `UE_DEPRECATED(5.4, "This function has been deprecated and will be removed soon.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and will be removed soon."))` — DisplayCluster module API
- L34 _public prototype_ `virtual EDisplayClusterOperationMode GetOperationMode() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Runtime Cluster API
- L38 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L43 _public prototype_ `virtual FString GetNodeId() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Runtime local node API
- L48 _public prototype_ `virtual void GetActiveNodeIds(TArray<FString>& OutNodeIds) const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns List of the active nodes in the runtime cluster node in a cluster.
- L54 _public prototype_ `virtual int32 GetActiveNodesAmount() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns amount of active nodes in a cluster.
- L58 _public prototype_ `virtual EDisplayClusterNodeRole GetClusterRole() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L62 _public prototype_ `virtual bool IsPrimary() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L66 _public prototype_ `virtual bool IsSecondary() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L71 _public prototype_ `virtual bool IsBackup() const override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns true if current node is a backup node in a cluster.
- L76 _public prototype_ `virtual void AddClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Cluster events API
- L80 _public prototype_ `virtual void RemoveClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L84 _public prototype_ `virtual void EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L88 _public prototype_ `virtual void EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L92 _public prototype_ `virtual void SendClusterEventJsonTo(const FString& Address, const int32 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`
- L96 _public prototype_ `virtual void SendClusterEventBinaryTo(const FString& Address, const int32 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) override;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Controller/DisplayClusterClusterNodeCtrlBase.h` (Private)


#### class `FDisplayClusterClusterNodeCtrlBase`  
`class FDisplayClusterClusterNodeCtrlBase : public IDisplayClusterClusterNodeController`  
_L21-81_
- inherits: `IDisplayClusterClusterNodeController`
- desc: Base node controller Encapsulates some common controller logic and data
- L26 _public prototype_ `FDisplayClusterClusterNodeCtrlBase(const FString& InControllerName, const FString& InClusterNodeId);`
- L28 _public prototype_ `virtual ~FDisplayClusterClusterNodeCtrlBase();`
- L33 _public function_ `virtual FString GetNodeId() const override final`
- L38 _public function_ `virtual FString GetControllerName() const override final`
- L43 _public prototype_ `virtual TWeakPtr<FDisplayClusterService> GetService(const FName& ServiceName) const override;`
- L45 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) override;`
- L46 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) override;`
- L52 _protected prototype_ `TMap<FName, TSharedPtr<FDisplayClusterService>> GetRegisteredServices();` — Provides accesss to the service register for children
- L55 _protected prototype_ `bool StartServerWithLogs(const TSharedPtr<IDisplayClusterServer>& Server, const FString& Address, const uint16 Port) const;` — A helper function to start a server with its own connection listener
- L58 _protected prototype_ `bool StartServerWithLogs(const TSharedPtr<IDisplayClusterServer>& Server, TSharedRef<FDisplayClusterTcpListener>& TcpListener);` — A helper function to start a connection listener provided
- L61 _protected prototype_ `bool StartClientWithLogs(IDisplayClusterClient* Client, const FString& Address, const uint16 Port, const uint32 ClientConnTriesAmount, const uint32 ClientConnRetryDelay);` — A helper function to initialize (connect) a specific client to a specific address
- L64 _protected prototype_ `void RegisterLocalService(const FName& ServiceName, const TSharedRef<FDisplayClusterService>& Service);` — Register local server so it can be reached via API
- L69 _private member_ `const FString ClusterNodeId;` — Cluster node ID
- L72 _private member_ `const FString ControllerName;` — Controller name/ID
- L77 _private member_ `TMap<FName, TSharedPtr<FDisplayClusterService>> RegisteredServices;` — Services that have been registered, and accessible from the outside via API
- L80 _private member_ `mutable FCriticalSection RegisteredServicesCS;` — A critical section to control access to the container of registered services

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Controller/DisplayClusterClusterNodeCtrlDisabled.h` (Private)


#### class `FDisplayClusterClusterNodeCtrlDisabled`  
`class FDisplayClusterClusterNodeCtrlDisabled : public IDisplayClusterClusterNodeController`  
_L14-86_
- inherits: `IDisplayClusterClusterNodeController`
- desc: Node controller for 'Disabled' operation mode. It's mostly a stub for public API that may be called in 'Disabled' mode. Additionally, it's a nullptr replacement for TSharedRef<IDisplayClusterClusterNodeController>.
- L19 _public prototype_ `FDisplayClusterClusterNodeCtrlDisabled();`
- L24 _public prototype_ `virtual bool Initialize() override;`
- L25 _public prototype_ `virtual void Shutdown() override;`
- L26 _public prototype_ `virtual FString GetNodeId() const override;`
- L27 _public prototype_ `virtual FString GetControllerName() const override;`
- L28 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) override;`
- L29 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) override;`
- L35 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L39 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L40 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L41 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L42 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L48 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L54 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L60 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L66 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L67 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L68 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L69 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L70 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L71 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L77 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L78 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L79 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`
- L85 _private member_ `const FString ControllerName;` — Controller name

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Controller/DisplayClusterClusterNodeCtrlEditor.h` (Private)


#### class `FDisplayClusterClusterNodeCtrlEditor`  
`class FDisplayClusterClusterNodeCtrlEditor : public FDisplayClusterClusterNodeCtrlBase`  
_L19-105_
- inherits: `FDisplayClusterClusterNodeCtrlBase`
- desc: Node controller for 'Editor' operation mode. This controller is used in PIE only, therefore it has a very limited functionality. So far, the following features are supported: - JSON and binary events processsing. This is useful for debugging event based logic in PIE. - JSON and binary events sending outside (inheriated from base controller).
- L24 _public prototype_ `FDisplayClusterClusterNodeCtrlEditor();`
- L25 _public prototype_ `virtual ~FDisplayClusterClusterNodeCtrlEditor();`
- L30 _public prototype_ `virtual bool Initialize() override;`
- L31 _public prototype_ `virtual void Shutdown() override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L39 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L40 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L41 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L42 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L43 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L44 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L50 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L56 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L62 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L68 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L69 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L70 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L71 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L72 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L73 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L79 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L80 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L81 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`
- L87 _private prototype_ `bool InitializeServers();` — Auxiliary function that initializes all the internal servers
- L90 _private prototype_ `bool StartServers();` — Auxiliary function that starts all the internal servers
- L93 _private prototype_ `void StopServers();` — Auxiliary function that stops all the internal servers
- L96 _private prototype_ `void ShutdownImpl();` — Non-virtual implementation of 'Shutdown' to prevent any potential issues when called from destrcutor
- L101 _private member_ `TSharedPtr<FDisplayClusterClusterEventsJsonService> ClusterEventsJsonServer;` — JSON events server
- L104 _private member_ `TSharedPtr<FDisplayClusterClusterEventsBinaryService> ClusterEventsBinaryServer;` — Binary events server

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Controller/DisplayClusterClusterNodeCtrlMain.h` (Private)


#### class `FDisplayClusterClusterNodeCtrlMain`  
`class FDisplayClusterClusterNodeCtrlMain : public FDisplayClusterClusterNodeCtrlBase , public TSharedFromThis<FDisplayClusterClusterNodeCtrlMain>`  
_L24-238_
- inherits: `FDisplayClusterClusterNodeCtrlBase,TSharedFromThis<FDisplayClusterClusterNodeCtrlMain>`
- desc: Node controller for 'Cluster' operation mode. Provides full set of features required in 'Cluster' operation mode.
- L30 _public prototype_ `FDisplayClusterClusterNodeCtrlMain(const FString& InClusterNodeId);`
- L31 _public prototype_ `virtual ~FDisplayClusterClusterNodeCtrlMain();`
- L36 _public prototype_ `virtual bool Initialize() override;`
- L37 _public prototype_ `virtual void Shutdown() override;`
- L38 _public prototype_ `virtual TSet<FName> GetInternalServiceNames() const override;`
- L39 _public prototype_ `int32 InitializeGeneralPurposeBarrierClients() override;`
- L40 _public prototype_ `virtual void ReleaseGeneralPurposeBarrierClients(int32 ClientSetId) override;`
- L41 _public prototype_ `virtual bool DropClusterNode(const FString& NodeId) override;`
- L47 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L48 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L49 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L50 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L51 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L52 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L53 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L54 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L60 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L66 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L72 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L78 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L79 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L80 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L81 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L82 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L83 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L89 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L90 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L91 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`
- L97 _private prototype_ `bool InitializeServers();` — Initialize node servers
- L100 _private prototype_ `bool StartServersInternal(const UDisplayClusterConfigurationData* const InConfigData, const UDisplayClusterConfigurationClusterNode* const InConfigNode);` — Start internal servers
- L103 _private prototype_ `bool StartServersExternal();` — Start external servers (no params)
- L106 _private prototype_ `bool StartServersExternal(const UDisplayClusterConfigurationData* const InConfigData, const UDisplayClusterConfigurationClusterNode* const InConfigNode);` — Start external servers
- L109 _private prototype_ `void RunBackgroundServersExternalStartTask();` — Start background async task that periodically tries to start the external servers
- L112 _private prototype_ `void StopServers();` — Stop internal servers
- L115 _private prototype_ `void StopServersInternal();` — Stop internal servers
- L118 _private prototype_ `void StopServersExternal();` — Stop external servers
- L121 _private prototype_ `void StopServersImpl(const TSet<FName>& ServiceNames);` — Stop servers
- L124 _private prototype_ `bool InitializeClients();` — Initialize internal clients
- L127 _private prototype_ `bool StartClients();` — Initialize and connect internal clients (enty point for the client start process)
- L130 _private prototype_ `bool StartClientsConnectPrimary(const UDisplayClusterConfigurationData* const ConfigData);` — Connect internal clients to the primary node only
- L133 _private prototype_ `bool StartClientsConnectRemaining(const UDisplayClusterConfigurationData* const ConfigData);` — Connect internal clients to the remaining nodes
- L136 _private prototype_ `void StopClients();` — Stop internal clients
- L144 _private prototype_ `void SubscribeToEvents();` — Subscribe to external events
- L147 _private prototype_ `void UnsubscribeFromEvents();` — Unsubscribe from external events
- L150 _private prototype_ `void FillThisNodeHostingInfo(FNodeServicesHostingInfo& OutHostingInfo);` — Outputs services hosting info of this cluster node
- L153 _private prototype_ `void ShutdownImpl();` — Non-virtual implementation of 'shutdown' to prevent any potential issues when called from virtual destructor
- L156 _private prototype_ `void HandleNodeFailed(const FDisplayClusterServiceFailureEvent& FailureInfo);` — Handle node failure callbacks
- L159 _private prototype_ `void HandlePrimaryNodeChanged(const FString& NewPrimaryId);` — Handles primary node change events
- L162 _private prototype_ `const TSharedPtr<FNodeClientSet> GetActiveClientSet();` — Returns a set of clients that is currently active.
- L165 _private prototype_ `const TSharedPtr<FDisplayClusterGenericBarrierClient> GetBarrierClientFromContext();` — Returns GPB client requested for a transaction.
- L191 _private member_ `TMap<FName, TSharedRef<FNodeClientSet>> Clients;` — Per-node clients. This node has a bunch of clients connected to each cluster node, including itself.
- L194 _private member_ `mutable FCriticalSection ClientsCS;` — A critical section to access the set of currently active clients.
- L211 _private member_ `TMap<int32, TSharedRef<FNodeGeneralPurposeBarrierClientSet>> GPBClients;` — Client ID to client set map
- L214 _private member_ `int32 GPBClientSetCounter = 0;` — GPB client set counter to keep client ID unique.
- L217 _private member_ `mutable FCriticalSection GPBClientsCS;` — A critical section to access the set GP barrier clients.
- L222 _private member_ `TSharedRef<FDisplayClusterTcpListener> TcpListener;` — Shared TCP connection listener for all internal services
- L225 _private member_ `const TSet<FName> InternalServiceNames;` — Holds internal service names
- L228 _private member_ `const TSet<FName> ExternalServiceNames;` — Holds external service names
- L231 _private member_ `FClusterServicesHostingInfo HostingInfo;` — Keeps connection information of every node in the cluster.
- L234 _private member_ `bool bExternalServersRunning = false;` — Whether external servers have started and running. Used for deferred ext servers start.
- L237 _private member_ `bool bIsTerminating = false;` — Used to ignore any session termination callbacks.

#### struct `FDisplayClusterClusterNodeCtrlMain::FNodeClientSet`  
`struct FNodeClientSet`  
_L172-188_
- desc: Auxiliary structure that contains local net clients
- L175 _public member_ `TUniquePtr<FDisplayClusterClusterSyncClient> ClusterSyncClient;` — ClusterSync client (used on 'Main' thread to synchronize world simulation)
- L178 _public member_ `TUniquePtr<FDisplayClusterRenderSyncClient> RenderSyncClient;` — RenderSync client (used on 'RHI' thread to synchronize presentation)
- L181 _public member_ `TUniquePtr<FDisplayClusterClusterEventsJsonClient> ClusterEventsJsonClient;` — JSON cluster events client (used on 'Any' thread to send JSON events to a P-node)
- L184 _public member_ `TUniquePtr<FDisplayClusterClusterEventsBinaryClient> ClusterEventsBinaryClient;` — Binary cluster events client (used on 'Any' thread to send binary events to a P-node)
- L187 _public member_ `TUniquePtr<FDisplayClusterInternalCommClient> InternalCommClient;` — InternalComm client (used on 'Any' thread for in-cluster communication)

#### struct `FDisplayClusterClusterNodeCtrlMain::FNodeGeneralPurposeBarrierClientSet`  
`struct FNodeGeneralPurposeBarrierClientSet`  
_L201-208_
- desc: Auxiliary structure that contains local GP barrier clients
- L204 _public prototype_ `bool Initialize(const IDisplayClusterProtocolInternalComm::FClusterServicesHostingInfo& InHostingInfo);` — Instantiates the client set, and establishes all neccessary connections. Returns true if everything is Ok.
- L207 _public member_ `TMap<FName, TSharedRef<FDisplayClusterGenericBarrierClient>> Clients;` — Per-node clients (used on 'Any' thread)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Controller/DisplayClusterCtrlContext.h` (Private)


#### struct `FDisplayClusterCtrlContext`  
`struct FDisplayClusterCtrlContext : public TThreadSingleton<FDisplayClusterCtrlContext>`  
_L15-23_
- inherits: `TThreadSingleton<FDisplayClusterCtrlContext>`
- desc: Per-thread communication context This container is used to pass any data from the failover controller to the cluster controller.
- L19 _public member_ `TOptional<FName> TargetNodeId;` — If set, this node must be addressed during the current request.
- L22 _public member_ `TOptional<int32> GPBClientId;` — Holds ID of a client set to use in the GP barrier sync transactions.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Controller/IDisplayClusterClusterNodeController.h` (Private)


#### class `IDisplayClusterClusterNodeController`  
`class IDisplayClusterClusterNodeController : public IDisplayClusterProtocolClusterSync , public IDisplayClusterProtocolEventsBinary , public IDisplayClusterProtocolEventsJson , public IDisplayClusterProtocolGenericBarrier , public IDisplayClusterProtocolInternalComm , public IDisplayClusterProtocolRenderSync`  
_L20-86_
- inherits: `IDisplayClusterProtocolClusterSync,IDisplayClusterProtocolEventsBinary,IDisplayClusterProtocolEventsJson,IDisplayClusterProtocolGenericBarrier,IDisplayClusterProtocolInternalComm,IDisplayClusterProtocolRenderSync`
- desc: Node controller interface
- L30 _public prototype_ `virtual ~IDisplayClusterClusterNodeController() = default;`
- L34 _public function_ `virtual bool Initialize()` — Initialize controller instance
- L40 _public function_ `virtual void Shutdown()` — Stop  clients/servers/etc
- L46 _public prototype_ `virtual FString GetNodeId() const = 0;` — Return node ID
- L49 _public prototype_ `virtual FString GetControllerName() const = 0;` — Return controller name
- L52 _public function_ `virtual TSet<FName> GetInternalServiceNames() const` — Returns a set of internal service names
- L58 _public function_ `virtual TWeakPtr<FDisplayClusterService> GetService(const FName& ServiceName) const` — Access to a specific service
- L64 _public function_ `virtual int32 InitializeGeneralPurposeBarrierClients()` — Initializes internal set of GB clients. Returns set ID for external referencing.
- L70 _public function_ `virtual void ReleaseGeneralPurposeBarrierClients(int32 ClientSetId)` — Releases requested clients set.
- L74 _public function_ `virtual bool DropClusterNode(const FString& NodeId)` — Drop specific cluster node
- L80 _public function_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly)` — Send binary event to a specific target outside of the cluster
- L84 _public function_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly)` — Send JSON event to a specific target outside of the cluster

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/CustomStates/DisplayClusterCustomStateHelpers.h` (Private)


#### class `UE::nDisplay::Cluster::Private::FCustomStateRequestBlob`  
`class FCustomStateRequestBlob`  
_L16-51_
- desc: Auxiliary class to pass custom state synchronization requests in binary
- L20 _public prototype_ `FCustomStateRequestBlob() = default;`
- L21 _public prototype_ `FCustomStateRequestBlob(const TSharedPtr<IDisplayClusterCustomState>& InState);`
- L22 _public prototype_ `~FCustomStateRequestBlob() = default;`
- L27 _public prototype_ `void Serialize(FArchive& Ar);` — Serialization implementation
- L32 _public member_ `FName StateName;` — State name
- L35 _public member_ `bool bCustomUpstream = false;` — Whether a state has custom upstream nodes configuration
- L41 _public member_ `TSet<FName> UpstreamNodes;` — When custom upstream configuration is used, this set contains node IDs that the state instance wants to get updates from.
- L44 _public member_ `bool bExposesData = false;` — Whether this state exposes any data outside during synchronization
- L47 _public member_ `FName StateType;` — Type ID of this state
- L50 _public member_ `TArray<uint8> StateData;` — Serialized state data

#### class `UE::nDisplay::Cluster::Private::FCustomStateResponseBlob`  
`class FCustomStateResponseBlob`  
_L57-83_
- desc: Auxiliary class to pass custom state synchronization responses in binary
- L61 _public prototype_ `FCustomStateResponseBlob() = default;`
- L63 _public function_ `FCustomStateResponseBlob(const FName& InStateName) : StateName(InStateName)`
- L70 _public prototype_ `void Serialize(FArchive& Ar);` — Serialization implementation
- L75 _public member_ `FName StateName;` — State name
- L82 _public member_ `TMap<FName, TPair<FName, TArray<uint8>>> NodeStates;` — Contains serialized state data in a form of <NodeId-to-{ StateType, StateData }> map. So any state may have multiple cluster nodes that it comes from, each one would provide its own serialized data.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace nDisplay` (scope `UE`)
- L11 _namespace_ `namespace Cluster` (scope `UE::nDisplay`)
- L11 _namespace_ `namespace Private` (scope `UE::nDisplay::Cluster`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/DisplayClusterClusterEventHandler.h` (Private)


#### class `FDisplayClusterClusterEventHandler`  
`class FDisplayClusterClusterEventHandler : public IDisplayClusterClusterEventListener`  
_L12-41_
- inherits: `IDisplayClusterClusterEventListener`
- desc: Internal handler for the system cluster events
- L17 _protected prototype_ `FDisplayClusterClusterEventHandler();`
- L22 _public function_ `static FDisplayClusterClusterEventHandler& Get()` — Singleton access
- L29 _public function_ `FOnClusterEventJsonListener& GetJsonListenerDelegate()` — Returns JSON event handler delegate
- L37 _protected prototype_ `void HandleClusterEvent(const FDisplayClusterClusterEventJson& InEvent);` — Cluster event processing function
- L40 _protected member_ `FOnClusterEventJsonListener ListenerDelegate;` — Cluster event listener delegate

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/DisplayClusterClusterManager.h` (Private)


#### class `FDisplayClusterClusterManager`  
`class FDisplayClusterClusterManager : public IPDisplayClusterClusterManager`  
_L22-275_
- inherits: `IPDisplayClusterClusterManager`
- desc: Cluster manager. Responsible for network communication and data replication.
- L27 _public prototype_ `FDisplayClusterClusterManager();`
- L28 _public prototype_ `virtual ~FDisplayClusterClusterManager();`
- L33 _public prototype_ `virtual bool Init(EDisplayClusterOperationMode OperationMode) override;`
- L34 _public prototype_ `virtual void Release() override;`
- L35 _public prototype_ `virtual bool StartSession(UDisplayClusterConfigurationData* InConfigData, const FString& NodeID) override;`
- L36 _public prototype_ `virtual void EndSession() override;`
- L37 _public prototype_ `virtual void EndScene() override;`
- L38 _public prototype_ `virtual void StartFrame(uint64 FrameNum) override;`
- L39 _public prototype_ `virtual void EndFrame(uint64 FrameNum) override;`
- L40 _public prototype_ `virtual void PreTick(float DeltaSeconds) override;`
- L41 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L42 _public prototype_ `virtual void PostTick(float DeltaSeconds) override;`
- L48 _public prototype_ `virtual bool IsPrimary() const override;`
- L49 _public prototype_ `virtual bool IsSecondary() const override;`
- L50 _public prototype_ `virtual bool IsBackup() const override;`
- L51 _public prototype_ `virtual EDisplayClusterNodeRole GetClusterRole() const override;`
- L52 _public prototype_ `virtual bool HasClusterRole(EDisplayClusterNodeRole Role) const override;`
- L54 _public prototype_ `virtual FString GetPrimaryNodeId() const override;`
- L56 _public prototype_ `virtual FString GetNodeId() const override;`
- L57 _public prototype_ `virtual uint32 GetNodesAmount() const override;`
- L58 _public prototype_ `virtual void GetNodeIds(TArray<FString>& OutNodeIds) const override;`
- L59 _public prototype_ `virtual void GetNodeIds(TSet<FString>& OutNodeIds) const override;`
- L61 _public prototype_ `virtual bool DropClusterNode(const FString& NodeId) override;`
- L63 _public prototype_ `virtual void RegisterSyncObject(IDisplayClusterClusterSyncObject* SyncObj, EDisplayClusterSyncGroup SyncGroup) override;`
- L64 _public prototype_ `virtual void UnregisterSyncObject(IDisplayClusterClusterSyncObject* SyncObj) override;`
- L66 _public prototype_ `virtual bool RegisterCustomState(const FName& UniqueStateName, TSharedPtr<IDisplayClusterCustomState>& StateVariable) override;`
- L67 _public prototype_ `virtual bool UnregisterCustomState(const FName& UniqueStateName) override;`
- L68 _public prototype_ `virtual TSet<FName> GetRegisteredCustomStateNames() const override;`
- L69 _public prototype_ `virtual bool IsCustomStateRegistered(const FName& UniqueStateName) const override;`
- L71 _public prototype_ `virtual TSharedRef<IDisplayClusterGenericBarriersClient> CreateGenericBarriersClient() override;`
- L73 _public prototype_ `virtual void AddClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener>) override;`
- L74 _public prototype_ `virtual void RemoveClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener>) override;`
- L76 _public prototype_ `virtual void AddClusterEventJsonListener(const FOnClusterEventJsonListener& Listener) override;`
- L77 _public prototype_ `virtual void RemoveClusterEventJsonListener(const FOnClusterEventJsonListener& Listener) override;`
- L79 _public prototype_ `virtual void AddClusterEventBinaryListener(const FOnClusterEventBinaryListener& Listener) override;`
- L80 _public prototype_ `virtual void RemoveClusterEventBinaryListener(const FOnClusterEventBinaryListener& Listener) override;`
- L82 _public prototype_ `virtual void EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) override;`
- L83 _public prototype_ `virtual void EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) override;`
- L85 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) override;`
- L86 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) override;`
- L93 _public prototype_ `virtual FDisplayClusterNetApiFacade& GetNetApi() override;`
- L94 _public prototype_ `virtual TSharedRef<IDisplayClusterClusterNodeController> GetNodeController() override;`
- L95 _public prototype_ `virtual TSharedRef<FDisplayClusterCommDataCache> GetDataCache() override;`
- L96 _public prototype_ `virtual TWeakPtr<FDisplayClusterService> GetNodeService(const FName& ServiceName) override;`
- L98 _public prototype_ `virtual bool DropNode(const FString& NodeId, ENodeDropReason DropReason) override;`
- L101 _public prototype_ `virtual void SyncTimeData() override;` — Sync time data
- L102 _public prototype_ `virtual void CacheTimeData() override;`
- L103 _public prototype_ `virtual void ExportTimeData( double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L104 _public prototype_ `virtual void ImportTimeData(const double& InDeltaTime, const double& InGameTime, const TOptional<FQualifiedFrameTime>& InFrameTime) override;`
- L107 _public prototype_ `virtual void SyncStates() override;` — Sync states
- L110 _public prototype_ `virtual void SyncObjects(EDisplayClusterSyncGroup SyncGroup) override;` — Sync objects
- L111 _public prototype_ `virtual void CacheObjects(EDisplayClusterSyncGroup SyncGroup) override;`
- L112 _public prototype_ `virtual void ExportObjectsData(const EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L113 _public prototype_ `virtual void ImportObjectsData(const EDisplayClusterSyncGroup InSyncGroup, const TMap<FString, TArray<uint8>>& InObjectsData) override;`
- L116 _public prototype_ `virtual void SyncEvents() override;` — Sync cluster events
- L117 _public prototype_ `virtual void CacheEvents() override;`
- L118 _public prototype_ `virtual void ExportEventsData( TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L119 _public prototype_ `virtual void ImportEventsData(const TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& InJsonEvents, const TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& InBinaryEvents) override;`
- L122 _public prototype_ `virtual void ExportNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;` — Sync native input
- L123 _public prototype_ `virtual void ImportNativeInputData(TMap<FString, TArray<uint8>>& InNativeInputData) override;`
- L130 _private prototype_ `bool InitializeNetworking(const UDisplayClusterConfigurationData* ConfigData);` — Performs initialization of networking subsystems
- L133 _private prototype_ `void ReleaseNetworking();` — Release networking subsystems
- L136 _private prototype_ `TSharedRef<IDisplayClusterClusterNodeController> CreateClusterNodeController() const;` — Factory method to instantiate a networking controller
- L139 _private prototype_ `TSharedRef<IDisplayClusterFailoverNodeController> CreateFailoverController(TSharedRef<IDisplayClusterClusterNodeController>& ClusterCtrl) const;` — Factory method to instantiate a failover controller
- L142 _private prototype_ `void SetInternalSyncObjectsReleaseState(bool bRelease);` — Auxiliary method for group set/reset of internal signals
- L145 _private prototype_ `void InitializeClusterRole(const FString& NodeId, const UDisplayClusterConfigurationData* ConfigData);` — Determines cluster role on session start.
- L148 _private prototype_ `void SetPrimaryNode(const FString& NewPrimaryNodeId);` — Changes current primary node ID. It doesn't do any actual role transition, just the ID variable.
- L151 _private prototype_ `void SetClusterRole(EDisplayClusterNodeRole NewRole);` — Changes current node role.
- L154 _private prototype_ `void HandleNodeDrop(const FString& NodeId);` — Performs node drop internal cleaning.
- L159 _private prototype_ `void OnClusterEventJsonHandler(const FDisplayClusterClusterEventJson& Event);` — JSON cluster event handler
- L162 _private prototype_ `void OnClusterEventBinaryHandler(const FDisplayClusterClusterEventBinary& Event);` — Binary cluster event handler
- L165 _private prototype_ `void OnPrimaryNodeChangedHandler(const FString& NewPrimaryId);` — Handles primary node change events
- L168 _private prototype_ `void OnClusterNodeFailed(const FString& FailedNodeId);` — Handles node failure events
- L172 _private typedef_ `using FClusterStateBlob = UE::nDisplay::Cluster::Private::FCustomStateResponseBlob;`
- L175 _private prototype_ `void AdvanceFrameOnCustomStates();` — Updates frame bound data on the state instances
- L182 _private prototype_ `void GenerateLocalStatesPropagationData(TArray<uint8>& OutLocalStatesData);` — Serializes local cluster states before propagation @param OutLocalStatesData - [out] Serialized state of all local state instanfces
- L189 _private prototype_ `void ProcessClusterStatesData(const TArray<uint8>& ClusterStatesData);` — Deserializes response data, and propagate the updates among local state instances @param ClusterStatesData - Serialized state of all states from every node
- L194 _private member_ `TSharedRef<IDisplayClusterClusterNodeController> NodeCtrl;` — Networking controller
- L197 _private member_ `TSharedRef<IDisplayClusterFailoverNodeController> FailoverCtrl;` — Failover controller
- L200 _private member_ `TUniquePtr<FDisplayClusterNetApiFacade> NetApi;` — Networking API
- L205 _private member_ `EDisplayClusterOperationMode CurrentOperationMode = EDisplayClusterOperationMode::Disabled;` — Current operation mode
- L209 _private member_ `FString PrimaryNodeId;` — Current primary node. It may change in runtime after failure handling.
- L212 _private member_ `mutable FCriticalSection PrimaryNodeIdCS;` — Safe access to the primary node ID
- L216 _private member_ `EDisplayClusterNodeRole CurrentNodeRole = EDisplayClusterNodeRole::None;` — Current role in the cluster
- L219 _private member_ `mutable FCriticalSection CurrentNodeRoleCS;` — Critical section to guard current role access
- L223 _private member_ `FString ClusterNodeId;` — This node ID
- L226 _private member_ `TSet<FString> InitialClusterNodeIds;` — A full set of cluster node IDs used on cluster start.
- L229 _private member_ `TSet<FString> ActiveClusterNodeIds;` — A subset of cluster node IDs that are currently active
- L232 _private member_ `mutable FCriticalSection ActiveClusterNodeIdsCS;` — A critical section to guard access to the set of active nodes
- L235 _private member_ `FEventRef TimeDataCacheReadySignal{ EEventMode::ManualReset };`
- L236 _private member_ `double DeltaTimeCache = 0.f;`
- L237 _private member_ `double GameTimeCache = 0.f;`
- L238 _private member_ `TOptional<FQualifiedFrameTime> FrameTimeCache;`
- L241 _private member_ `TMap<EDisplayClusterSyncGroup, TSet<IDisplayClusterClusterSyncObject*>> ObjectsToSync;` — Sync objects
- L242 _private member_ `mutable FCriticalSection ObjectsToSyncCS;`
- L244 _private member_ `TMap<EDisplayClusterSyncGroup, FEvent*> ObjectsToSyncCacheReadySignals;` — Sync objects - replication
- L245 _private member_ `TMap<EDisplayClusterSyncGroup, TMap<FString, TArray<uint8>>> ObjectsToSyncCache;`
- L248 _private member_ `FEventRef NativeInputCacheReadySignal{ EEventMode::ManualReset };` — Native input - replication
- L249 _private member_ `TMap<FString, TArray<uint8>> NativeInputCache;`
- L252 _private member_ `TMap<bool, TMap<FString, TSharedPtr<FDisplayClusterClusterEventJson>>> ClusterEventsJson;` — JSON events
- L253 _private member_ `TArray<TSharedPtr<FDisplayClusterClusterEventJson>> ClusterEventsJsonNonDiscarded;`
- L254 _private member_ `mutable FCriticalSection ClusterEventsJsonCS;`
- L255 _private member_ `FOnClusterEventJson OnClusterEventJson;`
- L258 _private member_ `TMap<bool, TMap<int32, TSharedPtr<FDisplayClusterClusterEventBinary>>> ClusterEventsBinary;` — Binary events
- L259 _private member_ `TArray<TSharedPtr<FDisplayClusterClusterEventBinary>> ClusterEventsBinaryNonDiscarded;`
- L260 _private member_ `mutable FCriticalSection ClusterEventsBinaryCS;`
- L261 _private member_ `FOnClusterEventBinary OnClusterEventBinary;`
- L264 _private member_ `FEventRef CachedEventsDataSignal{ EEventMode::ManualReset };` — JSON/Binary events - replication
- L265 _private member_ `TArray<TSharedPtr<FDisplayClusterClusterEventJson>> JsonEventsCache;`
- L266 _private member_ `TArray<TSharedPtr<FDisplayClusterClusterEventBinary>> BinaryEventsCache;`
- L269 _private member_ `mutable FCriticalSection ClusterEventListenersCS;` — Cluster event listeners
- L270 _private member_ `TArray<TScriptInterface<IDisplayClusterClusterEventListener>> ClusterEventListeners;`
- L273 _private member_ `mutable FCriticalSection CustomStatesCS;` — Custom states
- L274 _private member_ `TMap<FName, TSharedPtr<IDisplayClusterCustomState>> CustomStates;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/DisplayClusterGenericBarrierAPI.h` (Private)


#### class `FDisplayClusterGenericBarrierAPI`  
`class FDisplayClusterGenericBarrierAPI : public IDisplayClusterGenericBarriersClient`  
_L14-70_
- inherits: `IDisplayClusterGenericBarriersClient`
- desc: Generic barriers API
- L19 _public prototype_ `FDisplayClusterGenericBarrierAPI();`
- L20 _public prototype_ `~FDisplayClusterGenericBarrierAPI();`
- L25 _public prototype_ `virtual bool CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout) override;`
- L26 _public prototype_ `virtual bool WaitUntilBarrierIsCreated(const FString& BarrierId) override;`
- L27 _public prototype_ `virtual bool IsBarrierAvailable(const FString& BarrierId) override;`
- L28 _public prototype_ `virtual bool ReleaseBarrier(const FString& BarrierId) override;`
- L29 _public prototype_ `virtual bool Synchronize(const FString& BarrierId, const FString& CallerId) override;`
- L30 _public prototype_ `virtual bool Synchronize(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData) override;`
- L31 _public prototype_ `virtual FOnGenericBarrierSynchronizationDelegate* GetBarrierSyncDelegate(const FString& BarrierId) override;`
- L32 _public prototype_ `virtual FOnGenericBarrierTimeoutDelegate* GetBarrierTimeoutDelegate(const FString& BarrierId) override;`
- L38 _private prototype_ `TSharedPtr<FDisplayClusterGenericBarrierService> GetGenericBarrierService() const;` — Provides access to the GB service
- L41 _private prototype_ `bool ConfigureBarrierSyncDelegate(const FString& BarrierId, bool bSetup);` — Setup/release sync delegate for a specific barrier
- L44 _private prototype_ `void OnBarrierSync(FDisplayClusterBarrierPreSyncEndDelegateData& SyncData);` — Callback on barrier sync phase end
- L47 _private prototype_ `void OnBarrierTimeout(const FString& BarrierId, const TSet<FString>& NodesTimedOut);` — Callback on barrier timeout
- L64 _private member_ `TMap<FString, FBarrierCallbacksHolder> BarrierCallbacksMap;` — Holds per-barrier delegates/callbacks
- L69 _private member_ `int32 ClientSetId = INDEX_NONE;` — Holds client set ID allocated in the cluster controller, and bound to this GPB client.

#### struct `FDisplayClusterGenericBarrierAPI::FBarrierCallbacksHolder`  
`struct FBarrierCallbacksHolder`  
_L54-61_
- desc: Aux structure to keep all the delegates/events of a barrier
- L57 _public member_ `FOnGenericBarrierSynchronizationDelegate OnGenericBarrierSynchronizationDelegate;` — Synchronization delegate
- L60 _public member_ `FOnGenericBarrierTimeoutDelegate OnGenericBarrierTimeoutDelegate;` — Timeout delegate

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Failover/DisplayClusterCommDataCache.h` (Private)


#### class `FDisplayClusterCommDataCache`  
`class FDisplayClusterCommDataCache`  
_L26-450_
- desc: Communication data cache This class is a mediator in communication between cluster nodes. The main purpose of it: - To help the failover controller to deal with transactions - To cache data that will be exported to other nodes - To catch up missing data during failover
- L30 _public prototype_ `FDisplayClusterCommDataCache();`
- L31 _public prototype_ `virtual ~FDisplayClusterCommDataCache();`
- L36 _public typedef_ `using FOpIsCached = TFunction<bool(void)>;` — Common types
- L41 _public member_ `FOpIsCached GetTimeData_OpIsCached;` — Returns true if time data has been cached for current frame
- L44 _public member_ `TFunction<void(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime)> GetTimeData_OpLoad;` — Loads time data from cache
- L47 _public member_ `TFunction<void(double& InDeltaTime, double& InGameTime, TOptional<FQualifiedFrameTime>& InFrameTime)> GetTimeData_OpSave;` — Caches time data
- L52 _public member_ `TFunction<FOpIsCached(const EDisplayClusterSyncGroup InSyncGroup)> GetObjectsData_OpIsCached;` — Returns true if sync objects data has been cached for current frame
- L55 _public member_ `TFunction<void(const EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData)> GetObjectsData_OpLoad;` — Loads sync objects data from cache
- L58 _public member_ `TFunction<void(const EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& InObjectsData)> GetObjectsData_OpSave;` — Caches sync objects data
- L63 _public member_ `FOpIsCached GetEventsData_OpIsCached;` — Returns true if events data has been cached for current frame
- L66 _public member_ `TFunction<void(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents)> GetEventsData_OpLoad;` — Loads events data from cache
- L69 _public member_ `TFunction<void(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& InJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& InBinaryEvents)> GetEventsData_OpSave;` — Caches events data
- L74 _public member_ `FOpIsCached GetNativeInputData_OpIsCached;` — Returns true if input data has been cached for current frame
- L77 _public member_ `TFunction<void(TMap<FString, TArray<uint8>>& OutNativeInputData)> GetNativeInputData_OpLoad;` — Loads input data from cache
- L80 _public member_ `TFunction<void(TMap<FString, TArray<uint8>>& InNativeInputData)> GetNativeInputData_OpSave;` — Caches input data
- L85 _public member_ `TFunction<bool(const FName& BarrierName, const FName& SyncCallerName)> OpGetBarrierOpen;` — Returns true if specified barrier is considered open for a specific caller from the cluster POV
- L88 _public member_ `TFunction<void(const FName& BarrierName, const FName& SyncCallerName)> OpAdvanceBarrierCounter;` — Incrmements barrier sync counter
- L97 _public prototype_ `void TempWorkaround_ResetTimeDataCache();` — [Temporary Workaround] Reset time data cache manually
- L102 _protected prototype_ `void GenerateNodeSyncState(TArray<uint8>& OutNodeSyncState);` — Generates and exports the state of synchronization of this node
- L105 _protected prototype_ `void UpdateClusterSyncState(const TArray<uint8>& ClusterSyncState);` — Update cluster synchronization state after post-failure negotiation
- L108 _protected prototype_ `void BuildClusterSyncState(const TMap<FString, TArray<uint8>>& RequestData, TMap<FString, TArray<uint8>>& ResponseData);` — Summarizes abstract synchrnization state of the cluster based on the sync states of every node
- L113 _private prototype_ `void Initialize_Barriers();` — Initializes internal barrier cache
- L116 _private prototype_ `void Initialize_GetTimeData();` — Initializes internal GetTimeData function cache
- L119 _private prototype_ `void Initialize_GetObjectsData();` — Initializes internal GetObjectsData function cache
- L122 _private prototype_ `void Initialize_GetEventsData();` — Initializes internal GetEventsData function cache
- L125 _private prototype_ `void Initialize_GetNativeInputData();` — Initializes internal GetNativeInputData function cache
- L130 _private prototype_ `FName GetObjectsDataSlotName(const EDisplayClusterSyncGroup InSyncGroup) const;` — Returns GetObjectsData slot name based on sync group (each group is stored separately)
- L135 _private prototype_ `bool OpIsCachedImpl(const FName& SlotName) const;` — This is a generic implementation of "Is slot cached" algorithm
- L139 _private prototype_ `template <typename TSlotDataType, typename... Args> void OpLoadImpl(const FName& SlotName, Args&...);` — This is a generic implementation of "Load data from a slot" algorithm
- L143 _private prototype_ `template <typename TSlotDataType, typename... Args> void OpSaveImpl(const FName& SlotName, Args&...);` — This is a generic implementation of "Save data to a slot" algorithm
- L148 _private prototype_ `void SubscribeToCallbacks();` — Subscribes to external callbacks
- L151 _private prototype_ `void UnsubscribeFromCallbacks();` — Unsubscribes from external callbacks
- L154 _private prototype_ `void ProcessDCEndFrame(uint64 FrameNum);` — EndFrame callback handler to invalidate game thread bound cache
- L157 _private prototype_ `void OnPostFailureBarrierSync(FDisplayClusterBarrierPreSyncEndDelegateData& SyncData);` — PostFailure negotiation sync callback. Called from the corresponding barrier on P-nodes only.
- L234 _private function_ `friend FArchive& operator<<(FArchive& Ar, FCache_GetTimeData& Instance)` — Serialization
- L277 _private function_ `friend FArchive& operator<<(FArchive& Ar, FCache_GetObjectsData& Instance)` — Serialization
- L325 _private function_ `friend FArchive& operator<<(FArchive& Ar, FCache_GetEventsData& Instance)` — Serialization
- L368 _private function_ `friend FArchive& operator<<(FArchive& Ar, FCache_GetNativeInputData& Instance)` — Serialization
- L438 _private function_ `friend FArchive& operator<<(FArchive& Ar, FDataCacheHolder& Instance)` — Serialization
- L446 _private member_ `FDataCacheHolder LocalDataCache;` — Represents the synchronization state of this node
- L449 _private member_ `FDataCacheHolder ClusterDataCache;` — Represents the synchronization state of the whole cluster. It's generated during post-failure recovery.

#### struct `FDisplayClusterCommDataCache::FCyclicDataCacheBase`  
`struct FCyclicDataCacheBase`  
_L164-186_
- desc: Base class for thread cyclic cache data types
- L169 _public prototype_ `virtual ~FCyclicDataCacheBase() = default;` — Virtual destructor for proper resource cleaning
- L174 _public prototype_ `virtual FString ToLogString() const = 0;` — Generates log string
- L177 _public prototype_ `virtual void Serialize(FArchive& Ar);` — Serialization
- L180 _public prototype_ `virtual void Reset();` — Release internals and/or reset to default
- L185 _public member_ `bool bCached = false;` — Cache state flag (true => cached)

#### struct `FDisplayClusterCommDataCache::FCache_GetTimeData`  
`struct FCache_GetTimeData : public FCyclicDataCacheBase`  
_L195-239_
- inherits: `FCyclicDataCacheBase`
- desc: GetTimeData cache Caches time data for current frame
- L200 _public member_ `double DeltaTime = 0;` — GetTimeData parameter cache
- L203 _public member_ `double GameTime = 0;` — GetTimeData parameter cache
- L206 _public member_ `TOptional<FQualifiedFrameTime> FrameTime;` — GetTimeData parameter cache
- L211 _public function_ `void CopyData(bool bCopyOutside, double& DeltaTimeRef, double& GameTimeRef, TOptional<FQualifiedFrameTime>& FrameTimeRef)` — Copies data TO or FROM
- L228 _public prototype_ `virtual FString ToLogString() const override;`
- L229 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L230 _public prototype_ `virtual void Reset() override;`

#### struct `FDisplayClusterCommDataCache::FCache_GetObjectsData`  
`struct FCache_GetObjectsData : public FCyclicDataCacheBase`  
_L248-282_
- inherits: `FCyclicDataCacheBase`
- desc: GetObjectsData cache Caches custom objects data of a specified sync group for current frame
- L253 _public member_ `TMap<FString, TArray<uint8>> ObjData;` — Object data of a dedicated synchronization group
- L258 _public function_ `void CopyData(bool bCopyOutside, TMap<FString, TArray<uint8>>& ObjDataRef)` — Copies data TO or FROM
- L271 _public prototype_ `virtual FString ToLogString() const override;`
- L272 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L273 _public prototype_ `virtual void Reset() override;`

#### struct `FDisplayClusterCommDataCache::FCache_GetEventsData`  
`struct FCache_GetEventsData : public FCyclicDataCacheBase`  
_L291-330_
- inherits: `FCyclicDataCacheBase`
- desc: GetEventsData cache Caches cluster events data for current frame
- L296 _public member_ `TArray<TSharedPtr<FDisplayClusterClusterEventJson>> JsonEvents;` — JSON events cached
- L299 _public member_ `TArray<TSharedPtr<FDisplayClusterClusterEventBinary>> BinaryEvents;` — Binary events cached
- L304 _public function_ `void CopyData(bool bCopyOutside, TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& JsonEventsRef, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& BinaryEventsRef)` — Copies data TO or FROM
- L319 _public prototype_ `virtual FString ToLogString() const override;`
- L320 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L321 _public prototype_ `virtual void Reset() override;`

#### struct `FDisplayClusterCommDataCache::FCache_GetNativeInputData`  
`struct FCache_GetNativeInputData : public FCyclicDataCacheBase`  
_L339-373_
- inherits: `FCyclicDataCacheBase`
- desc: GetNativeInputData cache Caches native input data for current frame
- L344 _public member_ `TMap<FString, TArray<uint8>> NativeInputData;` — Native input data cached for current cycle (frame)
- L349 _public function_ `void CopyData(bool bCopyOutside, TMap<FString, TArray<uint8>>& NativeInputDataRef)` — Copies data TO or FROM
- L362 _public prototype_ `virtual FString ToLogString() const override;`
- L363 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L364 _public prototype_ `virtual void Reset() override;`

#### struct `FDisplayClusterCommDataCache::FDataCacheHolder`  
`struct FDataCacheHolder`  
_L382-443_
- desc: Data cache holder This is an auxiliary wrapper for data cache to simplify serialization during recovery
- L386 _public prototype_ `FDataCacheHolder() = default;`
- L389 _public function_ `FDataCacheHolder(int)` — Workaround to allow the usage of TMap::Emplace for uncopyable TUniquePtr members
- L401 _public member_ `TMap<FName, TUniquePtr<FCyclicDataCacheBase>> GameThreadDataCache;` — Game thread data cache. Contains the game thread data received from a P-node during the current frame. This data is stored only by the receiving side. If the P-node fails, other nodes can use this data to catch up with the simulation. Valid only until the next frame.
- L404 _public member_ `mutable FCriticalSection GameThreadDataCacheCS;` — Critical section for safe access
- L413 _public member_ `TMap<FName, TMap<FName, uint64>> BarrierSyncStates;` — Barrier synchronization state. Tracks the usage of the node barriers. Barrier-based synchronization requires all cluster nodes to maintain the same state between synchronization cycles. This is used to recover from a P-node failure.
- L416 _public member_ `mutable FCriticalSection BarrierSyncStatesCS;` — Critical section for safe access
- L421 _public prototype_ `void InvalidateGameThreadData(bool bReset = false);` — Invalidate game thread data
- L424 _public prototype_ `FCyclicDataCacheBase* GetGTSlotData(const FName& SlotName);` — Access to the game thread data slots
- L427 _public prototype_ `const FCyclicDataCacheBase* GetGTSlotData(const FName& SlotName) const;` — Access to the game thread data slots (const version)
- L432 _public prototype_ `FString ToLogString() const;` — Generates log string
- L435 _public prototype_ `void Serialize(FArchive& Ar);` — Serialization

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Failover/DisplayClusterFailoverNodeCtrlBase.h` (Private)


#### class `FDisplayClusterFailoverNodeCtrlBase`  
`class FDisplayClusterFailoverNodeCtrlBase : public IDisplayClusterFailoverNodeController`  
_L15-34_
- inherits: `IDisplayClusterFailoverNodeController`
- desc: Base failover node controller class
- L20 _public prototype_ `FDisplayClusterFailoverNodeCtrlBase(TSharedRef<IDisplayClusterClusterNodeController>& InNodeController);`
- L25 _protected function_ `const TSharedRef<IDisplayClusterClusterNodeController>& GetNodeController() const` — Access to the active node controller
- L33 _private member_ `TSharedRef<IDisplayClusterClusterNodeController> NodeController;` — Active node controller

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Failover/DisplayClusterFailoverNodeCtrlDisabled.h` (Private)


#### class `FDisplayClusterFailoverNodeCtrlDisabled`  
`class FDisplayClusterFailoverNodeCtrlDisabled : public FDisplayClusterFailoverNodeCtrlBase`  
_L13-79_
- inherits: `FDisplayClusterFailoverNodeCtrlBase`
- desc: Failover controller for 'Disabled' operation mode. It's mostly a stub for API calls.
- L18 _public function_ `FDisplayClusterFailoverNodeCtrlDisabled(TSharedRef<IDisplayClusterClusterNodeController>& InNodeController) : FDisplayClusterFailoverNodeCtrlBase(InNodeController)`
- L25 _public prototype_ `virtual bool Initialize(const UDisplayClusterConfigurationData* ConfigData) override;`
- L26 _public prototype_ `virtual TSharedRef<FDisplayClusterCommDataCache> GetDataCache() override;`
- L27 _public prototype_ `virtual bool HandleFailure(const FString& FailedNodeId) override;`
- L33 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L34 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L35 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L39 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L40 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L46 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L52 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L58 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L64 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L65 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L66 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L67 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L68 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L69 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L75 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L76 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L77 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Failover/DisplayClusterFailoverNodeCtrlEditor.h` (Private)


#### class `FDisplayClusterFailoverNodeCtrlEditor`  
`class FDisplayClusterFailoverNodeCtrlEditor : public FDisplayClusterFailoverNodeCtrlBase`  
_L14-86_
- inherits: `FDisplayClusterFailoverNodeCtrlBase`
- desc: Failover controller for 'Editor' operation mode. It's mostly a stub as we don't require any failover in PIE.
- L19 _public function_ `FDisplayClusterFailoverNodeCtrlEditor(TSharedRef<IDisplayClusterClusterNodeController>& InNodeController) : FDisplayClusterFailoverNodeCtrlBase(InNodeController) , DataCache(MakeShared<FDisplayClusterCommDataCache>())`
- L27 _public prototype_ `virtual bool Initialize(const UDisplayClusterConfigurationData* ConfigData) override;`
- L28 _public prototype_ `virtual TSharedRef<FDisplayClusterCommDataCache> GetDataCache() override;`
- L29 _public prototype_ `virtual bool HandleFailure(const FString& FailedNodeId) override;`
- L35 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L39 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L40 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L41 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L42 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L48 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L54 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L60 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L66 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L67 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L68 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L69 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L70 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L71 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L77 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L78 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L79 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`
- L85 _private member_ `TSharedRef<FDisplayClusterCommDataCache> DataCache;` — Stub cache to respect API

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Failover/DisplayClusterFailoverNodeCtrlMain.h` (Private)


#### class `FDisplayClusterFailoverNodeCtrlMain`  
`class FDisplayClusterFailoverNodeCtrlMain : public FDisplayClusterFailoverNodeCtrlBase , public FDisplayClusterCommDataCache , public TSharedFromThis<FDisplayClusterFailoverNodeCtrlMain>`  
_L25-226_
- inherits: `FDisplayClusterFailoverNodeCtrlBase,FDisplayClusterCommDataCache,TSharedFromThis<FDisplayClusterFailoverNodeCtrlMain>`
- desc: Failover controller for 'Cluster' operation mode. Provides full set of features required in 'Cluster' operation mode.
- L32 _public prototype_ `FDisplayClusterFailoverNodeCtrlMain(TSharedRef<IDisplayClusterClusterNodeController>& InNodeController);`
- L33 _public prototype_ `virtual ~FDisplayClusterFailoverNodeCtrlMain() = default;`
- L38 _public prototype_ `virtual bool Initialize(const UDisplayClusterConfigurationData* ConfigData) override;`
- L39 _public prototype_ `virtual TSharedRef<FDisplayClusterCommDataCache> GetDataCache() override;`
- L40 _public prototype_ `virtual bool HandleFailure(const FString& FailedNodeId) override;`
- L46 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L47 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L48 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L49 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L50 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L51 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L52 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L53 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L59 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L65 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L71 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L77 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L78 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L79 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L80 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L81 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L82 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, IDisplayClusterProtocolGenericBarrier::EBarrierControlResult& Result) override;`
- L88 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L89 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L90 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`
- L96 _private prototype_ `bool SetupFailoverConfiguration(const UDisplayClusterConfigurationData* ConfigData);` — An auxiliary initialization function to process failover configuration setup
- L99 _private prototype_ `void LogFailoverConfiguration(const FDisplayClusterConfigurationFailoverSettings& FailoverCfg);` — Reports configuration to the log stream
- L102 _private prototype_ `void SetupInternals();` — Initialize other internals
- L105 _private prototype_ `bool ProcessRecovery();` — Implements cluster recovery after primary failure
- L108 _private prototype_ `FString ElectNewPrimaryNode();` — Elects new primary node if possible
- L111 _private prototype_ `uint64 GetTransactionCounter(const FName& TransactionName);` — Returns current transaction count
- L114 _private prototype_ `uint64 GetAndIncrementTransactionCounter(const FName& TransactionName);` — Returns current transaction count, and increments it
- L117 _private prototype_ `void IncrementTransactionCounter(const FName& TransactionName);` — Increments transaction counter
- L122 _private typedef_ `using FOpSendReq = TFunction<EDisplayClusterCommResult()>;` — Basic transaction operation for remote data request
- L125 _private typedef_ `using FOpCacheWrapper = TFunction<void()>;` — Cache operation provider
- L134 _private prototype_ `EDisplayClusterCommResult ProcessTransactionGET( const FName& TransactionName, const FOpIsCached& OpIsCached, const FOpCacheWrapper& OpCacheLoad, const FOpCacheWrapper& OpCacheSave, const FOpSendReq& OpSendReq );` — GET type of transactions Retrieves data from the current P-node or the cache. Updates the local cache upon successfully receiving data from the P-node. Initiates the failure handling procedure if the P-node fails.
- L149 _private prototype_ `EDisplayClusterCommResult ProcessTransactionPUSH( const FName& TransactionName, const FOpSendReq& OpSendReq );` — PUSH type of transactions This type of transaction is used to send data to the P-node. It is also used for trivial communication messages that neither send any data nor expect to receive any in return.
- L161 _private prototype_ `EDisplayClusterCommResult ProcessTransactionSYNC( const FName& TransactionName, const FName& BarrierId, const FName& CallerId, const FOpSendReq& OpSendReq );` — SYNC type of transactions Used for barrier synchronzation. Remembers successfull synchronization attempts. It also uses the cluster synchronization state to decide whether synchronization on a specified barrier is necessary at the moment.
- L173 _private prototype_ `EDisplayClusterCommResult ProcessTransactionMCAST( const FName& TransactionName, const FOpSendReq& OpSendReq, const TSet<FString>& TargetNodes );` — MCAST type of transactions Used for multicast calls. Each node call is performed as a separate transaction.
- L186 _private prototype_ `EDisplayClusterCommResult ProcessTransactionRECOVERY( const FName& TransactionName, const FOpSendReq& OpSendReq );` — RECOVERY type of transactions The transactions of this type are used during failure handling procedure. Unlike any other transaction type, this one is performed in exclusive mode (Write Lock), therefore no other transaction allowed to run simultaneously.
- L194 _private member_ `const FString ThisNodeId;` — This cluster node Id
- L197 _private member_ `const FName ThisNodeIdName;` — This cluster node Id as FName
- L200 _private member_ `TUniquePtr<FDisplayClusterConfigurationFailoverSettings> FailoverSettings;` — Failover settings from cluster configuration
- L203 _private member_ `std::atomic<bool> bTerminateTransactionProcessingLoop = false;` — Prevents endless transaction working cycle
- L206 _private member_ `TSet<FString> FailedNodesProcessedAlready;` — Tracks nodes that have previously failed and have already undergone failure handling
- L213 _private member_ `FTransactionallySafeRWLock RecoveryLock;` — Safety lock to block any transactions during recovery. Here the SWMR concept "Single Writer Multiple Readers" is turned into "Single Recovery Multiple Transactions". We allow to run multiple transactions in parallel, but none of them allowed during recovery. Also, it's not allowed to run multiple recovery processes simultaneously.
- L219 _private member_ `mutable FCriticalSection FailoverCS;` — This one is used to safely operate on some failover internals before starting the actual post-failure recovery procedure which requires RecoveryLock in W-mode.
- L222 _private member_ `TMap<FName, uint64> TransactionCoutner;` — Keeps all the counters for transactions
- L225 _private member_ `mutable FCriticalSection TransactionCoutnerCS;` — Safe access to the transaction counters

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/Failover/IDisplayClusterFailoverNodeController.h` (Private)


#### class `IDisplayClusterFailoverNodeController`  
`class IDisplayClusterFailoverNodeController : public IDisplayClusterProtocolClusterSync , public IDisplayClusterProtocolEventsBinary , public IDisplayClusterProtocolEventsJson , public IDisplayClusterProtocolGenericBarrier , public IDisplayClusterProtocolInternalComm , public IDisplayClusterProtocolRenderSync`  
_L19-41_
- inherits: `IDisplayClusterProtocolClusterSync,IDisplayClusterProtocolEventsBinary,IDisplayClusterProtocolEventsJson,IDisplayClusterProtocolGenericBarrier,IDisplayClusterProtocolInternalComm,IDisplayClusterProtocolRenderSync`
- desc: Failover controller interface
- L29 _public prototype_ `virtual ~IDisplayClusterFailoverNodeController() = default;`
- L34 _public prototype_ `virtual bool Initialize(const UDisplayClusterConfigurationData* ConfigData) = 0;` — Initialize the controller
- L37 _public prototype_ `virtual TSharedRef<FDisplayClusterCommDataCache> GetDataCache() = 0;` — Provides access to the communication data cache
- L40 _public prototype_ `virtual bool HandleFailure(const FString& FailedNodeId) = 0;` — Process node failure

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/IPDisplayClusterClusterManager.h` (Private)


#### class `IPDisplayClusterClusterManager`  
`class IPDisplayClusterClusterManager : public IDisplayClusterClusterManager, public IPDisplayClusterManager`  
_L20-108_
- inherits: `IDisplayClusterClusterManager,IPDisplayClusterManager`
- desc: Cluster manager private interface
- L26 _public prototype_ `virtual ~IPDisplayClusterClusterManager() = default;`
- L40 _public prototype_ `virtual FDisplayClusterNetApiFacade& GetNetApi() = 0;` — Access to the networking API
- L43 _public prototype_ `virtual TSharedRef<IDisplayClusterClusterNodeController> GetNodeController() = 0;` — Access to the node controller
- L46 _public prototype_ `virtual TSharedRef<FDisplayClusterCommDataCache> GetDataCache() = 0;` — Access to the communication data cache
- L49 _public prototype_ `virtual TWeakPtr<FDisplayClusterService> GetNodeService(const FName& ServiceName) = 0;` — Access to the node services
- L52 _public prototype_ `virtual bool DropNode(const FString& NodeId, ENodeDropReason DropReason) = 0;` — Drop cluster node for a reason. This is the entry point for drop requests.
- L57 _public prototype_ `virtual void SyncTimeData() = 0;` — Time data synchronization (procedure entry point)
- L60 _public prototype_ `virtual void CacheTimeData() = 0;` — Cache current time data
- L63 _public prototype_ `virtual void ExportTimeData( double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) = 0;` — Export current time data
- L66 _public prototype_ `virtual void ImportTimeData(const double& InDeltaTime, const double& InGameTime, const TOptional<FQualifiedFrameTime>& InFrameTime) = 0;` — Import time data from external source
- L71 _public prototype_ `virtual void SyncStates() = 0;` — Custom states synchronization (procedure entry point)
- L76 _public prototype_ `virtual void SyncObjects(EDisplayClusterSyncGroup SyncGroup) = 0;` — Custom objects synchronization (procedure entry point)
- L79 _public prototype_ `virtual void CacheObjects(EDisplayClusterSyncGroup SyncGroup) = 0;` — Caches objects data
- L82 _public prototype_ `virtual void ExportObjectsData(const EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) = 0;` — Exports objects data from this node
- L85 _public prototype_ `virtual void ImportObjectsData(const EDisplayClusterSyncGroup InSyncGroup, const TMap<FString, TArray<uint8>>& InObjectsData) = 0;` — Imports objects data from the primary node
- L90 _public prototype_ `virtual void SyncEvents() = 0;` — Cluster events synchronization (procedure entry point)
- L93 _public prototype_ `virtual void CacheEvents() = 0;` — Cache events
- L96 _public prototype_ `virtual void ExportEventsData( TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) = 0;` — Exports events data from the current node (primary)
- L99 _public prototype_ `virtual void ImportEventsData(const TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& InJsonEvents, const TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& InBinaryEvents) = 0;` — Imports and processes the cluster events (come from the primary node)
- L104 _public prototype_ `virtual void ExportNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) = 0;` — Exports native input data from the local PlayerInput on the primary node
- L107 _public prototype_ `virtual void ImportNativeInputData(TMap<FString, TArray<uint8>>& InNativeInputData) = 0;` — Imports and applies the native input data from the the primary node

#### enum `IPDisplayClusterClusterManager::ENodeDropReason`  
`enum class ENodeDropReason : uint8`  
_L31-35_
- desc: A list of reasons why a node may leave the cluster
- L33 _public enumerator_ `UserRequest`
- L34 _public enumerator_ `Failed`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/NetAPI/DisplayClusterNetApiFacade.h` (Private)


#### class `FDisplayClusterNetApiFacade`  
`class FDisplayClusterNetApiFacade`  
_L22-82_
- desc: An auxiliary facade class that provides the networking API without any direct access to the networking internals. It encapsulates the in-cluster role based behavior, failover and networking subsystems, keeping the API transparent to the clients. This is the entry point for all networking requests. At this step, we route all the net calls to the current failover controller, which is the next step in the pipeline.
- L26 _public prototype_ `FDisplayClusterNetApiFacade(TSharedRef<IDisplayClusterFailoverNodeController>& InFailoverController);`
- L31 _public function_ `TSharedRef<IDisplayClusterProtocolClusterSync> GetClusterSyncAPI()` — Access to the cluster sync API (Game thread only)
- L38 _public function_ `TSharedRef<IDisplayClusterProtocolRenderSync> GetRenderSyncAPI()` — Access to the render sync API (RHI thread only)
- L44 _public function_ `TSharedRef<IDisplayClusterProtocolEventsBinary> GetBinaryEventsAPI()` — Access to binary events API (ANY thread)
- L50 _public function_ `TSharedRef<IDisplayClusterProtocolEventsJson> GetJsonEventsAPI()` — Access to JSON events API (ANY thread)
- L61 _protected function_ `TSharedRef<IDisplayClusterProtocolGenericBarrier> GetGenericBarrierAPI()` — Access to generic barrier API (ANY thread)
- L69 _private member_ `TSharedRef<IDisplayClusterProtocolClusterSync> ClusterSyncAPI;` — ClusterSync API
- L72 _private member_ `TSharedRef<IDisplayClusterProtocolRenderSync> RenderSyncAPI;` — RenderSync API
- L75 _private member_ `TSharedRef<IDisplayClusterProtocolEventsBinary> BinaryEventsAPI;` — Binary events API
- L78 _private member_ `TSharedRef<IDisplayClusterProtocolEventsJson> JsonEventsAPI;` — JSON events API
- L81 _private member_ `TSharedRef<IDisplayClusterProtocolGenericBarrier> GenericBarrierAPI;` — Generic barrier API

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/RequestHandler/DisplayClusterCommRequestHandlerBase.h` (Private)


#### class `FDisplayClusterCommRequestHandlerBase`  
`class FDisplayClusterCommRequestHandlerBase : public IDisplayClusterProtocolClusterSync`  
_L11-18_
- inherits: `IDisplayClusterProtocolClusterSync`
- desc: Base class for comm requests handling
- L16 _public prototype_ `FDisplayClusterCommRequestHandlerBase() = default;`
- L17 _public prototype_ `virtual ~FDisplayClusterCommRequestHandlerBase() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/RequestHandler/DisplayClusterCommRequestHandlerLocal.h` (Private)


#### class `FDisplayClusterCommRequestHandlerLocal`  
`class FDisplayClusterCommRequestHandlerLocal : public FDisplayClusterCommRequestHandlerBase`  
_L16-45_
- inherits: `FDisplayClusterCommRequestHandlerBase`
- desc: Local request handler Handles comm requests that were sent by this node. Also encapsulates interaction with cached synchronization data (failover/recovery).
- L26 _public prototype_ `static FDisplayClusterCommRequestHandlerLocal& Get();` — Singleton access
- L30 _private prototype_ `FDisplayClusterCommRequestHandlerLocal() = default;`
- L31 _private prototype_ `virtual ~FDisplayClusterCommRequestHandlerLocal() = default;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L39 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L40 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L41 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L42 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L43 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Cluster/RequestHandler/DisplayClusterCommRequestHandlerRemote.h` (Private)


#### class `FDisplayClusterCommRequestHandlerRemote`  
`class FDisplayClusterCommRequestHandlerRemote : public FDisplayClusterCommRequestHandlerBase`  
_L16-45_
- inherits: `FDisplayClusterCommRequestHandlerBase`
- desc: Remote request handler Handles comm requests that were sent by the nodes other than this. Also encapsulates interaction with cached synchronization data (failover/recovery).
- L26 _public prototype_ `static FDisplayClusterCommRequestHandlerRemote& Get();` — Singleton access
- L30 _private prototype_ `FDisplayClusterCommRequestHandlerRemote() = default;`
- L31 _private prototype_ `virtual ~FDisplayClusterCommRequestHandlerRemote() = default;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L39 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L40 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L41 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary>>& OutBinaryEvents) override;`
- L42 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L43 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Config/DisplayClusterConfigManager.h` (Private)


#### class `FDisplayClusterConfigManager`  
`class FDisplayClusterConfigManager : public IPDisplayClusterConfigManager`  
_L15-63_
- inherits: `IPDisplayClusterConfigManager`
- desc: Config manager. Responsible for loading data from config file and providing with it to any other classes.
- L19 _public prototype_ `FDisplayClusterConfigManager() = default;`
- L20 _public prototype_ `virtual ~FDisplayClusterConfigManager() = default;`
- L26 _public prototype_ `virtual bool Init(EDisplayClusterOperationMode OperationMode) override;`
- L27 _public prototype_ `virtual void Release() override;`
- L28 _public prototype_ `virtual bool StartSession(UDisplayClusterConfigurationData* InConfigData, const FString& NodeId) override;`
- L29 _public prototype_ `virtual void EndSession() override;`
- L35 _public function_ `virtual UDisplayClusterConfigurationData* GetConfig() const override`
- L40 _public function_ `virtual FString GetConfigPath() const override`
- L45 _public function_ `virtual FString GetLocalNodeId() const override`
- L50 _public prototype_ `virtual FString GetPrimaryNodeId() const override;`
- L52 _public prototype_ `virtual const UDisplayClusterConfigurationClusterNode* GetPrimaryNode() const override;`
- L53 _public prototype_ `virtual const UDisplayClusterConfigurationClusterNode* GetLocalNode() const override;`
- L54 _public prototype_ `virtual const UDisplayClusterConfigurationViewport* GetLocalViewport(const FString& ViewportId) const override;`
- L56 _public prototype_ `virtual bool GetLocalPostprocess(const FString& PostprocessId, FDisplayClusterConfigurationPostprocess& OutPostprocess) const override;`
- L57 _public prototype_ `virtual bool GetLocalProjection(const FString& ViewportId, FDisplayClusterConfigurationProjection& OutProjection) const override;`
- L60 _private member_ `FString ClusterNodeId;`
- L62 _private member_ `TStrongObjectPtr<UDisplayClusterConfigurationData> ConfigData;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Config/IPDisplayClusterConfigManager.h` (Private)


#### class `IPDisplayClusterConfigManager`  
`class IPDisplayClusterConfigManager : public IDisplayClusterConfigManager , public IPDisplayClusterManager`  
_L12-18_
- inherits: `IDisplayClusterConfigManager,IPDisplayClusterManager`
- desc: Config manager private interface
- L17 _public prototype_ `virtual ~IPDisplayClusterConfigManager() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/DisplayClusterCallbacks.h` (Private)


#### class `FDisplayClusterCallbacks`  
`class FDisplayClusterCallbacks : public IDisplayClusterCallbacks`  
_L11-210_
- inherits: `IDisplayClusterCallbacks`
- desc: DisplayCluster callbacks API implementation
- L15 _public function_ `virtual FDisplayClusterStartSessionEvent& OnDisplayClusterStartSession() override`
- L20 _public function_ `virtual FDisplayClusterEndSessionEvent& OnDisplayClusterEndSession() override`
- L25 _public function_ `virtual FDisplayClusterStartFrameEvent& OnDisplayClusterStartFrame() override`
- L30 _public function_ `virtual FDisplayClusterEndFrameEvent& OnDisplayClusterEndFrame() override`
- L35 _public function_ `virtual FDisplayClusterPreTickEvent& OnDisplayClusterPreTick() override`
- L40 _public function_ `virtual FDisplayClusterTickEvent& OnDisplayClusterTick() override`
- L45 _public function_ `virtual FDisplayClusterPostTickEvent& OnDisplayClusterPostTick() override`
- L50 _public function_ `virtual FDisplayClusterStartSceneEvent& OnDisplayClusterStartScene() override`
- L55 _public function_ `virtual FDisplayClusterEndSceneEvent& OnDisplayClusterEndScene() override`
- L60 _public function_ `virtual FDisplayClusterPreSubmitViewFamilies& OnDisplayClusterPreSubmitViewFamilies() override`
- L65 _public function_ `virtual FDisplayClusterCustomPresentSetEvent& OnDisplayClusterCustomPresentSet() override`
- L70 _public function_ `virtual FDisplayClusterPresentationPreSynchronization_RHIThread& OnDisplayClusterPresentationPreSynchronization_RHIThread() override`
- L75 _public function_ `virtual FDisplayClusterPresentationPostSynchronization_RHIThread& OnDisplayClusterPresentationPostSynchronization_RHIThread() override`
- L80 _public function_ `virtual FDisplayClusterFramePresentated_RHIThread& OnDisplayClusterFramePresented_RHIThread() override`
- L85 _public function_ `virtual FDisplayClusterFailoverNodeDown& OnDisplayClusterFailoverNodeDown() override`
- L90 _public function_ `virtual FDisplayClusterFailoverPrimaryNodeChanged& OnDisplayClusterFailoverPrimaryNodeChanged() override`
- L95 _public function_ `virtual FDisplayClusterPostTonemapPass_RenderThread& OnDisplayClusterPostTonemapPass_RenderThread() override`
- L100 _public function_ `virtual FDisplayClusterPostRenderViewFamily_RenderThread& OnDisplayClusterPostRenderViewFamily_RenderThread() override`
- L105 _public function_ `virtual FDisplayClusterPreWarp_RenderThread& OnDisplayClusterPreWarp_RenderThread() override`
- L110 _public function_ `virtual FDisplayClusterPreWarpViewport_RenderThread& OnDisplayClusterPreWarpViewport_RenderThread() override`
- L115 _public function_ `virtual FDisplayClusterPostWarp_RenderThread& OnDisplayClusterPostWarp_RenderThread() override`
- L120 _public function_ `virtual FDisplayClusterPostWarpViewport_RenderThread& OnDisplayClusterPostWarpViewport_RenderThread() override`
- L125 _public function_ `virtual FDisplayClusterPostCrossGpuTransfer_RenderThread& OnDisplayClusterPostCrossGpuTransfer_RenderThread() override`
- L130 _public function_ `virtual FDisplayClusterPassthroughMediaCapture_RenderThread& OnDisplayClusterPassthroughMediaCapture_RenderThread() override`
- L135 _public function_ `virtual FDisplayClusterPassthroughMediaInput_RenderThread& OnDisplayClusterPassthroughMediaInput_RenderThread() override`
- L140 _public function_ `virtual FDisplayClusterProcessLatency_RenderThread& OnDisplayClusterProcessLatency_RenderThread() override`
- L145 _public function_ `virtual FDisplayClusterPostResolveOverridden_RenderThread& OnDisplayClusterPostResolveOverridden_RenderThread() override`
- L150 _public function_ `virtual FDisplayClusterPostFrameRender_RenderThread& OnDisplayClusterPostFrameRender_RenderThread() override`
- L155 _public function_ `virtual FDisplayClusterPostBackbufferUpdate_RenderThread& OnDisplayClusterPostBackbufferUpdate_RenderThread() override`
- L160 _public function_ `virtual FDisplayClusterPostBackbufferUpdated_RenderThread& OnDisplayClusterPostBackbufferUpdated_RenderThread() override`
- L165 _public function_ `virtual FDisplayClusterPreProcessIcvfx_RenderThread& OnDisplayClusterPreProcessIcvfx_RenderThread() override`
- L170 _public function_ `virtual FDisplayClusterUpdateViewportMediaState& OnDisplayClusterUpdateViewportMediaState() override`
- L176 _private member_ `FDisplayClusterStartSessionEvent DisplayClusterStartSessionEvent;`
- L177 _private member_ `FDisplayClusterEndSessionEvent DisplayClusterEndSessionEvent;`
- L178 _private member_ `FDisplayClusterStartFrameEvent DisplayClusterStartFrameEvent;`
- L179 _private member_ `FDisplayClusterEndFrameEvent DisplayClusterEndFrameEvent;`
- L180 _private member_ `FDisplayClusterPreTickEvent DisplayClusterPreTickEvent;`
- L181 _private member_ `FDisplayClusterTickEvent DisplayClusterTickEvent;`
- L182 _private member_ `FDisplayClusterPostTickEvent DisplayClusterPostTickEvent;`
- L183 _private member_ `FDisplayClusterStartSceneEvent DisplayClusterStartSceneEvent;`
- L184 _private member_ `FDisplayClusterEndSceneEvent DisplayClusterEndSceneEvent;`
- L185 _private member_ `FDisplayClusterPreSubmitViewFamilies DisplayClusterPreSubmitViewFamiliesEvent;`
- L186 _private member_ `FDisplayClusterCustomPresentSetEvent DisplayClusterCustomPresentSetEvent;`
- L187 _private member_ `FDisplayClusterUpdateViewportMediaState DisplayClusterUpdateViewportMediaStateEvent;`
- L188 _private member_ `FDisplayClusterFailoverNodeDown DisplayClusterFailoverNodeDownEvent;`
- L189 _private member_ `FDisplayClusterFailoverPrimaryNodeChanged DisplayClusterFailoverPrimaryNodeChangedEvent;`
- L191 _private member_ `FDisplayClusterPresentationPreSynchronization_RHIThread DisplayClusterPresentationPreSynchronizationEvent;`
- L192 _private member_ `FDisplayClusterPresentationPostSynchronization_RHIThread DisplayClusterPresentationPostSynchronizationEvent;`
- L193 _private member_ `FDisplayClusterFramePresentated_RHIThread DisplayClusterFramePresentedEvent;`
- L195 _private member_ `FDisplayClusterPostTonemapPass_RenderThread DisplayClusterPostTonemapPassEvent;`
- L196 _private member_ `FDisplayClusterPostRenderViewFamily_RenderThread DisplayClusterPostRenderViewFamilyEvent;`
- L197 _private member_ `FDisplayClusterPreWarp_RenderThread DisplayClusterPreWarpEvent;`
- L198 _private member_ `FDisplayClusterPreWarpViewport_RenderThread DisplayClusterPreWarpViewportEvent;`
- L199 _private member_ `FDisplayClusterPostWarp_RenderThread DisplayClusterPostWarpEvent;`
- L200 _private member_ `FDisplayClusterPostWarpViewport_RenderThread DisplayClusterPostWarpViewportEvent;`
- L201 _private member_ `FDisplayClusterPostCrossGpuTransfer_RenderThread DisplayClusterPostCrossGpuTransferEvent;`
- L202 _private member_ `FDisplayClusterPassthroughMediaCapture_RenderThread DisplayClusterPassthroughMediaCaptureEvent;`
- L203 _private member_ `FDisplayClusterPassthroughMediaInput_RenderThread DisplayClusterPassthroughMediaInputEvent;`
- L204 _private member_ `FDisplayClusterProcessLatency_RenderThread DisplayClusterProcessLatencyEvent;`
- L205 _private member_ `FDisplayClusterPostResolveOverridden_RenderThread DisplayClusterPostResolveOverriddenEvent;`
- L206 _private member_ `FDisplayClusterPostFrameRender_RenderThread DisplayClusterPostFrameRenderEvent;`
- L207 _private member_ `FDisplayClusterPostBackbufferUpdate_RenderThread DisplayClusterPostBackbufferUpdateEvent;`
- L208 _private member_ `FDisplayClusterPostBackbufferUpdated_RenderThread DisplayClusterPostBackbufferUpdatedEvent;`
- L209 _private member_ `FDisplayClusterPreProcessIcvfx_RenderThread DisplayClusterPreProcessIcvfxEvent;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/DisplayClusterModule.h` (Private)


#### class `FDisplayClusterModule`  
`class FDisplayClusterModule : public IPDisplayCluster`  
_L19-95_
- inherits: `IPDisplayCluster`
- desc: Display Cluster module implementation
- L23 _public prototype_ `FDisplayClusterModule();`
- L24 _public prototype_ `virtual ~FDisplayClusterModule();`
- L30 _public function_ `virtual EDisplayClusterOperationMode GetOperationMode() const override`
- L35 _public function_ `virtual IDisplayClusterRenderManager* GetRenderMgr() const override`
- L36 _public function_ `virtual IDisplayClusterClusterManager* GetClusterMgr() const override`
- L37 _public function_ `virtual IDisplayClusterConfigManager* GetConfigMgr() const override`
- L38 _public function_ `virtual IDisplayClusterGameManager* GetGameMgr() const override`
- L40 _public function_ `virtual IDisplayClusterCallbacks& GetCallbacks() override`
- L49 _public function_ `virtual IPDisplayClusterRenderManager* GetPrivateRenderMgr() const override`
- L50 _public function_ `virtual IPDisplayClusterClusterManager* GetPrivateClusterMgr() const override`
- L51 _public function_ `virtual IPDisplayClusterConfigManager* GetPrivateConfigMgr() const override`
- L52 _public function_ `virtual IPDisplayClusterGameManager* GetPrivateGameMgr() const override`
- L58 _public prototype_ `virtual bool Init(EDisplayClusterOperationMode OperationMode) override;`
- L59 _public prototype_ `virtual void Release() override;`
- L60 _public prototype_ `virtual bool StartSession(UDisplayClusterConfigurationData* InConfigData, const FString& NodeId) override;`
- L61 _public prototype_ `virtual void EndSession() override;`
- L62 _public prototype_ `virtual bool StartScene(UWorld* InWorld) override;`
- L63 _public prototype_ `virtual void EndScene() override;`
- L64 _public prototype_ `virtual void StartFrame(uint64 FrameNum) override;`
- L65 _public prototype_ `virtual void PreTick(float DeltaSeconds) override;`
- L66 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L67 _public prototype_ `virtual void PostTick(float DeltaSeconds) override;`
- L68 _public prototype_ `virtual void EndFrame(uint64 FrameNum) override;`
- L74 _private prototype_ `virtual void StartupModule() override;`
- L75 _private prototype_ `virtual void ShutdownModule() override;`
- L78 _private prototype_ `void RegisterOutlinerFilters();`
- L83 _private member_ `IPDisplayClusterClusterManager* MgrCluster = nullptr;` — DisplayCluster subsystems
- L84 _private member_ `IPDisplayClusterRenderManager* MgrRender = nullptr;`
- L85 _private member_ `IPDisplayClusterConfigManager* MgrConfig = nullptr;`
- L86 _private member_ `IPDisplayClusterGameManager* MgrGame = nullptr;`
- L89 _private member_ `TArray<IPDisplayClusterManager*> Managers;` — Array of available managers
- L91 _private member_ `FDisplayClusterCallbacks Callbacks;`
- L94 _private member_ `EDisplayClusterOperationMode CurrentOperationMode = EDisplayClusterOperationMode::Disabled;` — Runtime

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/DisplayClusterVersion.h` (Private)


#### struct `FDisplayClusterCustomVersion`  
`struct FDisplayClusterCustomVersion`  
_L9-27_
- L11 _public prototype_ `FDisplayClusterCustomVersion() = delete;`
- L26 _public member_ `const static FGuid GUID;` — The GUID for this custom version number

#### enum `FDisplayClusterCustomVersion::Type`  
`enum Type`  
_L13-23_
- L16 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L18 _public enumerator_ `ComponentParentChange_4_27`
- L21 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>------
- L22 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Game/DisplayClusterGameManager.h` (Private)


#### class `FDisplayClusterGameManager`  
`class FDisplayClusterGameManager : public IPDisplayClusterGameManager`  
_L21-71_
- inherits: `IPDisplayClusterGameManager`
- desc: Game manager. Responsible for building VR object hierarchy from a config file. Implements some in-game logic.
- L25 _public prototype_ `FDisplayClusterGameManager();`
- L26 _public prototype_ `virtual ~FDisplayClusterGameManager();`
- L32 _public prototype_ `virtual bool Init(EDisplayClusterOperationMode OperationMode) override;`
- L33 _public prototype_ `virtual void Release() override;`
- L34 _public prototype_ `virtual bool StartSession(UDisplayClusterConfigurationData* InConfigData, const FString& InNodeId) override;`
- L35 _public prototype_ `virtual void EndSession() override;`
- L36 _public prototype_ `virtual bool StartScene(UWorld* World) override;`
- L37 _public prototype_ `virtual void EndScene() override;`
- L38 _public prototype_ `virtual void PreTick(float DeltaSeconds) override;`
- L44 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor() const override;`
- L45 _public prototype_ `virtual TArray<ADisplayClusterRootActor*> GetAllRootActorsFromWorld(UWorld* InWorld) override;`
- L46 _public function_ `virtual UWorld* GetWorld() const override`
- L51 _private prototype_ `ADisplayClusterRootActor* FindRootActor(UWorld* World, UDisplayClusterConfigurationData* ConfigData);` — The main function to look for a proper DCRA in a level and its sublevels
- L54 _private prototype_ `void FindRootActorsInWorld(UWorld* World, TArray<ADisplayClusterRootActor*>& OutActors);` — Auxiliary function that looks up for all DCRA instances in a level
- L57 _private prototype_ `bool DoesRootActorMatchTheAsset(ADisplayClusterRootActor* RootActorconst, const FString& AssetReference);` — Checks if a DCRA instance corresponds to a specified asset
- L61 _private member_ `FDisplayClusterActorRef DisplayClusterRootActorRef;` — Active DisplayCluster root
- L64 _private member_ `UDisplayClusterConfigurationData* ConfigData;` — Actual config data
- L66 _private member_ `EDisplayClusterOperationMode CurrentOperationMode;`
- L67 _private member_ `FString ClusterNodeId;`
- L68 _private member_ `UWorld* CurrentWorld;`
- L70 _private member_ `mutable FCriticalSection InternalsSyncScope;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Game/EngineClasses/Scene/DisplayClusterLabelWidget.h` (Private)


#### class `UDisplayClusterLabelWidget`  
`class UDisplayClusterLabelWidget : public UUserWidget`  
_L14-22_
- reflection: `UCLASS(Abstract)`
- inherits: `UUserWidget`
- desc: A base widget to display on actor labels.
- L20 _public prototype_ `void SetLabelText(const FText& InText);` — `UFUNCTION(BlueprintImplementableEvent, Category=Label)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Game/EngineClasses/Scene/DisplayClusterRootActorInitializer.h` (Private)


#### class `FDisplayClusterRootActorInitializer`  
`class FDisplayClusterRootActorInitializer`  
_L24-80_
- desc: This is a temporary class that is responsible for DCRA components initialization. In the future, we won't need it since the initialization will be performed in a native way in the DC configurator.
- L27 _public function_ `FDisplayClusterRootActorInitializer() : ProcessingActor(nullptr)`
- L31 _public prototype_ `~FDisplayClusterRootActorInitializer() = default;`
- L35 _public prototype_ `void Initialize(ADisplayClusterRootActor* Actor, UDisplayClusterConfigurationData* ConfigData);` — Main initialization function that manages the whole initialization process
- L38 _public prototype_ `void UpdateComponentTransformsOnly(ADisplayClusterRootActor* Actor, UDisplayClusterConfigurationData* ConfigData);` — Updates component transforms only based on the config settings
- L42 _private prototype_ `void ApplyConfigDataToComponents();` — Applies configuration data to the corresponding components
- L45 _private prototype_ `void ConfigureCameraComponent(UDisplayClusterCameraComponent* Component, UDisplayClusterConfigurationSceneComponentCamera* ComponentCfg);` — Helpers to configure component instances depending on their type
- L46 _private prototype_ `void ConfigureScreenComponent(UDisplayClusterScreenComponent* Component, UDisplayClusterConfigurationSceneComponentScreen* ComponentCfg);`
- L47 _private prototype_ `void ConfigureXformComponent(UDisplayClusterXformComponent* Component, UDisplayClusterConfigurationSceneComponentXform* ComponentCfg);`
- L48 _private prototype_ `void ConfigureComponentHierarchy(USceneComponent* Component, UDisplayClusterConfigurationSceneComponent* ComponentCfg);`
- L51 _private prototype_ `bool DoesComponentBelongToBlueprint(UActorComponent* Component) const;` — Checks if specified component belongs to the DCRA blueprint
- L54 _private prototype_ `void Cleanup();` — Cleanup internall temporary stuff
- L72 _private prototype_ `template <typename TComp, typename TCfgData, typename TCfgDataPtr> void SpawnComponents(const TMap<FString, TCfgDataPtr>& InConfigData, TMap<FString, FCompInitInfo<TComp, TCfgData>>& OutTypedMap);` — Spawns components listed in a config
- L75 _private member_ `ADisplayClusterRootActor* ProcessingActor;` — Internal component references
- L76 _private member_ `TMap<FString, USceneComponent*> AllComponents;`
- L77 _private member_ `TMap<FString, FCompInitInfo<UDisplayClusterXformComponent, UDisplayClusterConfigurationSceneComponentXform>> XformComponents;`
- L78 _private member_ `TMap<FString, FCompInitInfo<UDisplayClusterCameraComponent, UDisplayClusterConfigurationSceneComponentCamera>> CameraComponents;`
- L79 _private member_ `TMap<FString, FCompInitInfo<UDisplayClusterScreenComponent, UDisplayClusterConfigurationSceneComponentScreen>> ScreenComponents;`

#### struct `FDisplayClusterRootActorInitializer::FCompInitInfo`  
`template <typename TComp, typename TCfgData> struct FCompInitInfo`  
_L59-68_
- desc: Helper struct to bind a concrete component to its concrete config data type
- L61 _public function_ `FCompInitInfo(TComp* Comp, TCfgData* CfgData) : Component(Comp) , Config(CfgData)`
- L66 _public member_ `TComp* Component;`
- L67 _public member_ `TCfgData* Config;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Game/EngineClasses/Scene/DisplayClusterWidgetComponent.h` (Private)


#### class `UDisplayClusterWidgetComponent`  
`class UDisplayClusterWidgetComponent final : public UWidgetComponent`  
_L13-34_
- reflection: `UCLASS(transient, NotBlueprintable, NotBlueprintType)`
- inherits: `UWidgetComponent`
- desc: Extend the widget component to optimize when the widget is initialized and released.
- L17 _public prototype_ `UDisplayClusterWidgetComponent();`
- L20 _public prototype_ `void SetWidgetScale(float NewValue);`
- L21 _public function_ `float GetWidgetScale() const`
- L23 _private prototype_ `virtual void OnRegister() override;`
- L24 _private prototype_ `virtual void OnUnregister() override;`
- L26 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L29 _private prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);`
- L33 _private member_ `float WidgetScale = 1.f;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Game/IPDisplayClusterGameManager.h` (Private)


#### class `IPDisplayClusterGameManager`  
`class IPDisplayClusterGameManager : public IDisplayClusterGameManager , public IPDisplayClusterManager`  
_L12-18_
- inherits: `IDisplayClusterGameManager,IPDisplayClusterManager`
- desc: Game manager private interface
- L17 _public prototype_ `virtual ~IPDisplayClusterGameManager() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Misc/DisplayClusterAppExit.h` (Private)


#### class `FDisplayClusterAppExit`  
`class FDisplayClusterAppExit`  
_L11-24_
- desc: Auxiliary class. Responsible for terminating application.
- L23 _public prototype_ `static void ExitApplication(const FString& Msg, EExitType ExitType = FDisplayClusterAppExit::EExitType::Normal);`

#### enum `FDisplayClusterAppExit::EExitType`  
`enum class EExitType`  
_L14-20_
- L17 _public enumerator_ `Normal` — Delicate UE exit, full resource cleaning.
- L19 _public enumerator_ `KillImmediately` — Kills current process. No resource cleaning performed.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Misc/DisplayClusterGlobals.h` (Private)


#### Free symbols / members of external scopes

- L9 _externvar_ `extern IPDisplayCluster* GDisplayCluster;` — Internal global DisplayCluster module interface

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Misc/DisplayClusterLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterBarrier, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterBarrier, Log, All);` — Module-wide log categories
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterBarrierGP, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterBarrierGP, Log, All);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterBlueprint, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterBlueprint, Log, All);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterCluster, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterCluster, Log, All);`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterConfig, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterConfig, Log, All);`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterEngine, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterEngine, Log, All);`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterFailover, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterFailover, Log, All);`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterGame, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterGame, Log, All);`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterModule, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterModule, Log, All);`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterNetwork, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterNetwork, Log, All);`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterRender, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterRender, Log, All);`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterRenderSync, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterRenderSync, Log, All);`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterViewport, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterViewport, Log, All);`
- L24 _delegate_ `DECLARE_STATS_GROUP(TEXT("nDisplay"), STATGROUP_NDisplay, STATCAT_Advanced)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Misc/DisplayClusterTypesConverterPrivate.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const EDisplayClusterCommResult& From)` (scope `DisplayClusterTypesConverter`)
- L37 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const EDisplayClusterBarrierWaitResult& From)` (scope `DisplayClusterTypesConverter`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Misc/DisplayClusterWatchdogTimer.h` (Private)


#### class `FDisplayClusterWatchdogTimer`  
`class FDisplayClusterWatchdogTimer : protected FRunnable`  
_L15-74_
- inherits: `FRunnable`
- desc: Watchdog timer
- L19 _public prototype_ `FDisplayClusterWatchdogTimer(const FString& InTimerName);`
- L20 _public prototype_ `~FDisplayClusterWatchdogTimer();`
- L24 _public prototype_ `bool SetTimer(const uint32 InTimeout);` — Start watchdog timer with specified timeout duration (ms)
- L26 _public prototype_ `void ResetTimer();` — Reset timer before it's timed out
- L29 _public function_ `const FString& GetName() const` — Returns timer name
- L35 _public prototype_ `DECLARE_EVENT(FDisplayClusterWatchdogTimer, FWatchdogTimeoutEvent);` — Notification interface
- L36 _public function_ `FWatchdogTimeoutEvent& OnWatchdogTimeOut()`
- L45 _protected prototype_ `virtual uint32 Run() override;`
- L46 _protected prototype_ `virtual void Stop() override final;`
- L50 _private member_ `const FString TimerName;` — Timer name
- L53 _private member_ `bool bIsTimerSet = false;` — Timer state
- L55 _private member_ `bool bThreadExitRequested = false;` — Thread exit request flag
- L57 _private member_ `bool bTimerWasReset = false;` — Timer reset flag
- L59 _private member_ `uint32 Timeout = 0;` — Timer timeout
- L62 _private member_ `TUniquePtr<FRunnableThread> ThreadObj;` — Holds the thread object
- L65 _private member_ `FWatchdogTimeoutEvent WatchdogTimeOutEvent;` — Timeout notification
- L68 _private member_ `FEventRef EvtStartTimer { EEventMode::ManualReset };` — Working thread control events
- L69 _private member_ `FEventRef EvtWaitableObject { EEventMode::ManualReset };`
- L73 _private member_ `FCriticalSection InternalsCS;` — Critical section for access control

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_EVENT(FDisplayClusterWatchdogTimer, FWatchdogTimeoutEvent);` — Notification interface

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Barrier/DisplayClusterBarrier.h` (Private)


#### class `FDisplayClusterBarrier`  
`class FDisplayClusterBarrier : public IDisplayClusterBarrier`  
_L14-122_
- inherits: `IDisplayClusterBarrier`
- desc: Thread barrier v2
- L18 _public prototype_ `FDisplayClusterBarrier(const FString& Name, const TSet<FString>& CallersAllowed, const uint32 Timeout);`
- L19 _public prototype_ `virtual ~FDisplayClusterBarrier();`
- L23 _public function_ `virtual const FString& GetName() const override` — Barrier name
- L29 _public prototype_ `virtual bool Activate() override;` — Activate barrier
- L31 _public prototype_ `virtual void Deactivate() override;` — Deactivate barrier, no threads will be blocked
- L33 _public prototype_ `virtual bool IsActivated() const override;` — Returns true if the barrier has been activated
- L36 _public prototype_ `virtual EDisplayClusterBarrierWaitResult Wait(const FString& CallerId, double* OutThreadWaitTime = nullptr, double* OutBarrierWaitTime = nullptr) override;` — Wait until all caller threads arrived
- L39 _public prototype_ `virtual EDisplayClusterBarrierWaitResult WaitWithData(const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, double* OutThreadWaitTime = nullptr, double* OutBarrierWaitTime = nullptr) override;` — Wait until all threads arrive (with data)
- L42 _public prototype_ `virtual void UnregisterSyncCaller(const FString& CallerId) override;` — Remove specified caller from the sync pipeline
- L45 _public function_ `virtual FDisplayClusterBarrierPreSyncEndDelegate& GetPreSyncEndDelegate() override` — Returns barrier PreSyncEnd delegate
- L51 _public function_ `virtual FDisplayClusterBarrierTimeoutEvent& OnBarrierTimeout() override` — Barrier timout notification
- L58 _private prototype_ `void HandleBarrierPreSyncStart();` — Do some job before starting new sync iteration (opening the entrance gate)
- L61 _private prototype_ `void HandleBarrierPreSyncEnd();` — Do some job before opening the exit gate
- L64 _private prototype_ `void HandleBarrierTimeout();` — Handler for barrier timouts
- L68 _private member_ `const FString Name;` — Barrier name
- L70 _private member_ `bool bActive = false;` — Barrier state
- L74 _private member_ `TSet<FString> CallersAllowed;` — Caller that are allowed to join the barrier
- L77 _private member_ `TSet<FString> CallersAwaiting;` — Callers that are already waiting at the barrier
- L80 _private member_ `TSet<FString> CallersToForget;` — Callers that were dropped during synchronization cycle. Holds them temporary to provide correct cycle enclosure.
- L83 _private member_ `TSet<FString> CallersTimedout;` — Cluster Callers that have been timed out previously
- L86 _private member_ `TSet<FString> CallersDropped;` — Cluster Callers that have been detached from barrier synchronization
- L89 _private member_ `const uint32 Timeout = 0;` — Timeout for the barrier
- L92 _private member_ `uint64 SyncCycleCounter = 0;` — Synchronization cycles counter
- L95 _private member_ `FEventRef EventInputGateOpen { EEventMode::ManualReset };` — Events to control when threads can join (input) and leave (output) the barrier
- L96 _private member_ `FEventRef EventOutputGateOpen{ EEventMode::ManualReset };`
- L99 _private member_ `FDisplayClusterWatchdogTimer WatchdogTimer;` — Watchdog timer to detect barrier waiting timeouts
- L102 _private member_ `FDisplayClusterBarrierPreSyncEndDelegate BarrierPreSyncEndDelegate;` — PreSyncEnd delegate. It's called when all threads arrived before opening the gate.
- L104 _private member_ `FDisplayClusterBarrierTimeoutEvent BarrierTimeoutEvent;` — Barrier timeout event
- L107 _private member_ `TMap<FString, TArray<uint8>> ClientsRequestData;` — Request data from the callers
- L109 _private member_ `TMap<FString, TArray<uint8>> ClientsResponseData;` — Response data for the callers
- L112 _private member_ `double BarrierWaitTimeStart = 0;` — Diagnostics data
- L113 _private member_ `double BarrierWaitTimeFinish = 0;`
- L114 _private member_ `double BarrierWaitTimeOverall = 0;`
- L117 _private member_ `mutable FCriticalSection DataCS;` — Barrier state CS
- L119 _private member_ `mutable FCriticalSection EntranceCS;` — Barrier entrance CS
- L121 _private member_ `mutable FCriticalSection CommDataCS;` — Request/response data CS

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Barrier/DisplayClusterBarrierFactory.h` (Private)


#### class `FDisplayClusterBarrierFactory`  
`class FDisplayClusterBarrierFactory`  
_L13-23_
- desc: Barrier factory
- L17 _private prototype_ `FDisplayClusterBarrierFactory();`
- L22 _public prototype_ `static IDisplayClusterBarrier* CreateBarrier(const FString& BarrierId, const TSet<FString>& CallerIds, const uint32 Timeout);` — Factory method to instantiate a barrier based on the user settings

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Barrier/IDisplayClusterBarrier.h` (Private)


#### enum `EDisplayClusterBarrierWaitResult`  
`enum class EDisplayClusterBarrierWaitResult : uint8`  
_L13-19_
- desc: Barrier wait result
- L15 _public enumerator_ `Ok`
- L16 _public enumerator_ `NotActive`
- L17 _public enumerator_ `TimeOut`
- L18 _public enumerator_ `NotAllowed`

#### struct `FDisplayClusterBarrierPreSyncEndDelegateData`  
`struct FDisplayClusterBarrierPreSyncEndDelegateData`  
_L25-35_
- desc: Barrier PreSyncEnd callback data
- L28 _public member_ `const FString& BarrierId;` — Barrier ID
- L31 _public member_ `const TMap<FString, TArray<uint8>>& RequestData;` — Binary data provided on sync request (CallerId-to-Data mapping)
- L34 _public member_ `TMap<FString, TArray<uint8>>& ResponseData;` — Binary data to respond (CallerId-to-Data mapping)

#### class `IDisplayClusterBarrier`  
`class IDisplayClusterBarrier`  
_L41-77_
- desc: Thread barrier interface
- L45 _public prototype_ `virtual ~IDisplayClusterBarrier() = default;`
- L50 _public prototype_ `virtual const FString& GetName() const = 0;` — Barrier name
- L53 _public prototype_ `virtual bool Activate() = 0;` — Activate barrier
- L56 _public prototype_ `virtual void Deactivate() = 0;` — Deactivate barrier, no threads will be blocked
- L59 _public prototype_ `virtual bool IsActivated() const = 0;` — Returns true if the barrier has been activated
- L62 _public prototype_ `virtual EDisplayClusterBarrierWaitResult Wait(const FString& CallerId, double* OutThreadWaitTime = nullptr, double* OutBarrierWaitTime = nullptr) = 0;` — Wait until all threads arrive
- L65 _public prototype_ `virtual EDisplayClusterBarrierWaitResult WaitWithData(const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, double* OutThreadWaitTime = nullptr, double* OutBarrierWaitTime = nullptr) = 0;` — Wait until all threads arrive(with data)
- L68 _public prototype_ `virtual void UnregisterSyncCaller(const FString& CallerId) = 0;` — Remove specified caller from the sync pipeline
- L71 _public prototype_ `DECLARE_DELEGATE_OneParam(FDisplayClusterBarrierPreSyncEndDelegate, FDisplayClusterBarrierPreSyncEndDelegateData&);` — Barrier PreSyncEnd delegate. Called when all calling threads arrived right before opening the gate.
- L72 _public prototype_ `virtual FDisplayClusterBarrierPreSyncEndDelegate& GetPreSyncEndDelegate() = 0;`
- L75 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterBarrier, FDisplayClusterBarrierTimeoutEvent, const FString&, const TSet<FString>&);` — Barrier timout notification (provides BarrierName and CallersTimedOut in parameters)
- L76 _public prototype_ `virtual FDisplayClusterBarrierTimeoutEvent& OnBarrierTimeout() = 0;`

#### Free symbols / members of external scopes

- L71 _delegate_ `DECLARE_DELEGATE_OneParam(FDisplayClusterBarrierPreSyncEndDelegate, FDisplayClusterBarrierPreSyncEndDelegateData&);` — Barrier PreSyncEnd delegate. Called when all calling threads arrived right before opening the gate.
- L75 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterBarrier, FDisplayClusterBarrierTimeoutEvent, const FString&, const TSet<FString>&);` — Barrier timout notification (provides BarrierName and CallersTimedOut in parameters)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Configuration/DisplayClusterNetworkConfiguration.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace nDisplay` (scope `UE`)
- L8 _namespace_ `namespace Network` (scope `UE::nDisplay`)
- L8 _namespace_ `namespace Configuration` (scope `UE::nDisplay::Network`)
- L11 _variable_ `static constexpr int32 PacketBufferSize = 4 * 1024 * 1024;` (scope `UE::nDisplay::Network::Configuration`) — Networking buffer size
- L14 _externvar_ `extern const FName ClusterSyncClientName;` (scope `UE::nDisplay::Network::Configuration`) — ClusterSync client name
- L17 _externvar_ `extern const FName ClusterSyncServerName;` (scope `UE::nDisplay::Network::Configuration`) — ClusterSync server name
- L21 _externvar_ `extern const FName RenderSyncClientName;` (scope `UE::nDisplay::Network::Configuration`) — RenderSync client name
- L24 _externvar_ `extern const FName RenderSyncServerName;` (scope `UE::nDisplay::Network::Configuration`) — RenderSync server name
- L28 _externvar_ `extern const FName InternalCommClientName;` (scope `UE::nDisplay::Network::Configuration`) — InternalComm client name
- L31 _externvar_ `extern const FName InternalCommServerName;` (scope `UE::nDisplay::Network::Configuration`) — InternalComm server name
- L35 _externvar_ `extern const FName GenericBarrierClientName;` (scope `UE::nDisplay::Network::Configuration`) — GenericBarrier client name
- L38 _externvar_ `extern const FName GenericBarrierServerName;` (scope `UE::nDisplay::Network::Configuration`) — GenericBarrier server name
- L42 _externvar_ `extern const FName BinaryEventsClientName;` (scope `UE::nDisplay::Network::Configuration`) — Binary events client name
- L45 _externvar_ `extern const FName BinaryEventsServerName;` (scope `UE::nDisplay::Network::Configuration`) — Binary events server name
- L49 _externvar_ `extern const FName JsonEventsClientName;` (scope `UE::nDisplay::Network::Configuration`) — JSON events client name
- L52 _externvar_ `extern const FName JsonEventsServerName;` (scope `UE::nDisplay::Network::Configuration`) — JSON events server name
- L56 _externvar_ `extern const FName BinaryEventsExternalClientName;` (scope `UE::nDisplay::Network::Configuration`) — Binary events client name (external)
- L59 _externvar_ `extern const FName BinaryEventsExternalServerName;` (scope `UE::nDisplay::Network::Configuration`) — Binary events server name (external)
- L63 _externvar_ `extern const FName JsonEventsExternalClientName;` (scope `UE::nDisplay::Network::Configuration`) — JSON events client name (external)
- L66 _externvar_ `extern const FName JsonEventsExternalServerName;` (scope `UE::nDisplay::Network::Configuration`) — JSON events server name (external)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Conversion/DisplayClusterNetworkDataConversion.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace nDisplay` (scope `UE`)
- L17 _namespace_ `namespace DisplayClusterNetworkDataConversion` (scope `UE::nDisplay`)
- L20 _prototype_ `void JsonEventsFromInternalPacket(const TSharedPtr<FDisplayClusterPacketInternal>& Packet, TArray<TSharedPtr<FDisplayClusterClusterEventJson, ESPMode::ThreadSafe>>& JsonEvents);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [Internal] Extracts JSON events from binary objects (internal in-cluster replication only)
- L23 _prototype_ `void JsonEventsToInternalPacket(const TArray<TSharedPtr<FDisplayClusterClusterEventJson, ESPMode::ThreadSafe>>& JsonEvents, TSharedPtr<FDisplayClusterPacketInternal>& Packet);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [Internal] Converts JSON events into binary objects (internal in-cluster replication only)
- L26 _prototype_ `void BinaryEventsFromInternalPacket(const TSharedPtr<FDisplayClusterPacketInternal>& Packet, TArray<TSharedPtr<FDisplayClusterClusterEventBinary, ESPMode::ThreadSafe>>& BinaryEvents);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [Internal] Extracts Binary events from binary objects (internal in-cluster replication only)
- L29 _prototype_ `void BinaryEventsToInternalPacket(const TArray<TSharedPtr<FDisplayClusterClusterEventBinary, ESPMode::ThreadSafe>>& BinaryEvents, TSharedPtr<FDisplayClusterPacketInternal>& Packet);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [Internal] Converts Binary events into binary objects (internal in-cluster replication only)
- L33 _prototype_ `bool JsonPacketToJsonEvent(const TSharedPtr<FDisplayClusterPacketJson>& Packet, FDisplayClusterClusterEventJson& OutBinaryEvent);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [External] Extracts JSON event data from an external JSON packet
- L36 _prototype_ `TSharedPtr<FDisplayClusterPacketJson> JsonEventToJsonPacket(const FDisplayClusterClusterEventJson& BinaryEvent);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [External] Creates an external JSON packet with a specific JSON event set
- L39 _prototype_ `bool BinaryPacketToBinaryEvent(const TSharedPtr<FDisplayClusterPacketBinary>& Packet, FDisplayClusterClusterEventBinary& OutBinaryEvent);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [External] Extracts Binary event data from an external Binary packet
- L42 _prototype_ `TSharedPtr<FDisplayClusterPacketBinary> BinaryEventToBinaryPacket(FDisplayClusterClusterEventBinary& BinaryEvent);` (scope `UE::nDisplay::DisplayClusterNetworkDataConversion`) — [External] Creates an external Binary packet with a specific Binary event set

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/DisplayClusterClient.h` (Private)


#### class `FDisplayClusterClientBase`  
`class FDisplayClusterClientBase : public IDisplayClusterClient , public FDisplayClusterSocketOperations`  
_L14-48_
- inherits: `IDisplayClusterClient,FDisplayClusterSocketOperations`
- desc: Base DisplayCluster TCP client
- L20 _public function_ `FDisplayClusterClientBase(const FString& InName, int32 InLingerTime = 0) : FDisplayClusterSocketOperations(CreateSocket(InName, InLingerTime), UE::nDisplay::Network::Configuration::PacketBufferSize, InName)`
- L27 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;` — Connects to a server
- L30 _public prototype_ `virtual void Disconnect() override;` — Terminates current connection
- L33 _public function_ `virtual FString GetName() const override` — Returns client name
- L39 _public function_ `virtual bool IsConnected() const override` — Returns true if the client is currently connected
- L47 _protected prototype_ `FSocket* CreateSocket(const FString& InName, int32 LingerTime);` — Creates client socket

#### class `FDisplayClusterClient`  
`template <typename TPacketType> class FDisplayClusterClient : public FDisplayClusterClientBase , protected FDisplayClusterSocketOperationsHelper<TPacketType>`  
_L52-61_
- inherits: `FDisplayClusterClientBase,FDisplayClusterSocketOperationsHelper<TPacketType>`
- L57 _public function_ `FDisplayClusterClient(const FString& InName, int32 InLingerTime = 0) : FDisplayClusterClientBase(InName, InLingerTime) , FDisplayClusterSocketOperationsHelper<TPacketType>(*this, InName)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/DisplayClusterNetworkTypes.h` (Private)


#### enum `EDisplayClusterCommResult`  
`enum class EDisplayClusterCommResult : uint8`  
_L14-23_
- desc: Error codes for net communication
- L16 _public enumerator_ `Ok`
- L17 _public enumerator_ `WrongRequestData`
- L18 _public enumerator_ `WrongResponseData`
- L19 _public enumerator_ `NetworkError`
- L20 _public enumerator_ `NotImplemented`
- L21 _public enumerator_ `NotAllowed`
- L22 _public enumerator_ `InternalError`

#### struct `FDisplayClusterSessionInfo`  
`struct FDisplayClusterSessionInfo`  
_L29-62_
- desc: Represents session information
- L36 _public member_ `FSocket* Socket = nullptr;`
- L37 _public member_ `FIPv4Endpoint Endpoint;`
- L38 _public member_ `FString Protocol;`
- L39 _public member_ `uint64 SessionId = 0;`
- L40 _public member_ `FString SessionName;`
- L42 _public member_ `TOptional<FString> NodeId;`
- L44 _public member_ `double TimeStart = 0;`
- L45 _public member_ `double TimeEnd = 0;`
- L48 _public function_ `bool IsTerminatedByServer() const`
- L55 _protected member_ `bool bTerminatedByServer = false;` — Termination flag to simplify failover pipelines
- L58 _public function_ `FString ToString() const`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/DisplayClusterServer.h` (Private)


#### class `FDisplayClusterServer`  
`class FDisplayClusterServer : public IDisplayClusterServer`  
_L17-167_
- inherits: `IDisplayClusterServer`
- desc: Base DisplayCluster TCP server
- L23 _public member_ `static const double CleanSessionResourcesSafePeriod;` — Minimal time(seconds) before cleaning resources of the 'pending kill' sessions
- L27 _public prototype_ `FDisplayClusterServer(const FString& InstanceName);`
- L28 _public prototype_ `virtual ~FDisplayClusterServer();`
- L35 _public prototype_ `virtual bool Start(const FString& Address, const uint16 Port) override;` — Start server on a specific socket
- L38 _public prototype_ `virtual bool Start(TSharedRef<FDisplayClusterTcpListener>& ExternalListener) override;` — Start server with a specified listener
- L41 _public prototype_ `virtual void Shutdown() override;` — Stop server
- L44 _public prototype_ `virtual bool IsRunning() const override;` — Returns current server state
- L47 _public function_ `virtual FString GetName() const override` — Server name
- L53 _public prototype_ `virtual FString GetAddress() const override;` — Server address
- L56 _public prototype_ `virtual uint16 GetPort() const override;` — Server port
- L59 _public prototype_ `virtual void KillSession(const FString& NodeId) override;` — Kills all sessions of a specified cluster node
- L62 _public function_ `virtual FIsConnectionAllowedDelegate& OnIsConnectionAllowed() override` — Connection validation delegate
- L68 _public function_ `virtual FSessionOpenedEvent& OnSessionOpened() override` — Session opened event
- L74 _public function_ `virtual FSessionClosedEvent& OnSessionClosed() override` — Session closed event
- L80 _public function_ `virtual void NotifySessionOpened(const FDisplayClusterSessionInfo& SessionInfo) override` — Wraps SessionOpened to emit it safely from any thread.
- L87 _public function_ `virtual void NotifySessionClosed(const FDisplayClusterSessionInfo& SessionInfo) override` — Wraps SessionClosed to emit it safely from any thread.
- L98 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) = 0;` — Allow to specify custom session class
- L103 _private prototype_ `bool ConnectionHandler(FDisplayClusterSessionInfo& SessionInfo);` — Handle incoming connections
- L106 _private prototype_ `void ProcessSessionOpened(const FDisplayClusterSessionInfo& SessionInfo);` — Callback on session opened
- L109 _private prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback on session closed
- L112 _private prototype_ `void ShutdownImpl();` — Non-virtual shutdown implementation
- L115 _private prototype_ `void CleanPendingKillSessions();` — Free resources of the sessions that already finished their job
- L120 _private member_ `const FString InstanceName;` — Server instance name
- L123 _private member_ `bool bIsRunning = false;` — Server running state
- L126 _private member_ `TSharedPtr<FDisplayClusterTcpListener> Listener;` — Socket listener
- L129 _private member_ `FIsConnectionAllowedDelegate IsConnectionAllowedDelegate;` — Connection approval delegate
- L132 _private member_ `FSessionOpenedEvent SessionOpenedEvent;` — Session opened event
- L135 _private member_ `FSessionClosedEvent SessionClosedEvent;` — Session closed event
- L140 _private member_ `uint64 IncrementalSessionId = 0;` — Session counter used for session ID generation
- L144 _private member_ `TMap<uint64, TSharedPtr<IDisplayClusterSession>> PendingSessions;` — Pending sessions
- L147 _private member_ `TMap<uint64, TSharedPtr<IDisplayClusterSession>> ActiveSessions;` — Active sessions
- L150 _private member_ `TMap<uint64, TSharedPtr<IDisplayClusterSession>> PendingKillSessions;` — Closed sessions, awaiting for cleaning
- L155 _private member_ `mutable FCriticalSection ServerStateCritSec;` — Critical section to manipulate server states
- L158 _private member_ `mutable FCriticalSection SessionsCritSec;` — Critical section to manipulate the connection sessions
- L166 _private member_ `mutable FCriticalSection SessionNotifyCritSec;` — Critical section for safe session notifications. The same critical section is used for both SessionOpened and SessionClosed events because they don't really interfere in runtime. If there are new session events at some point, we might probably need separate critical sections for those.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/IDisplayClusterClient.h` (Private)


#### class `IDisplayClusterClient`  
`class IDisplayClusterClient`  
_L11-29_
- desc: DisplayCluster TCP client interface
- L14 _public prototype_ `virtual ~IDisplayClusterClient() = default;`
- L19 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount, const uint32 ConnectRetryDelay) = 0;` — Connects to a server
- L22 _public prototype_ `virtual void Disconnect() = 0;` — Terminates current connection
- L25 _public prototype_ `virtual bool IsConnected() const = 0;` — Returns connection status
- L28 _public prototype_ `virtual FString GetName() const = 0;` — Returns client name

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/IDisplayClusterServer.h` (Private)


#### class `IDisplayClusterServer`  
`class IDisplayClusterServer`  
_L13-67_
- desc: DisplayCluster TCP server interface
- L17 _public prototype_ `virtual ~IDisplayClusterServer() = default;`
- L22 _public prototype_ `virtual bool Start(const FString& Address, const uint16 Port) = 0;` — Start server on a specific socket
- L25 _public prototype_ `virtual bool Start(TSharedRef<FDisplayClusterTcpListener>& Listener) = 0;` — Start server with a specified listener
- L28 _public prototype_ `virtual void Shutdown() = 0;` — Stop server
- L31 _public prototype_ `virtual bool IsRunning() const = 0;` — Returns true if server is currently running
- L34 _public prototype_ `virtual FString GetName() const = 0;` — Returns server instance name
- L37 _public prototype_ `virtual FString GetAddress() const = 0;` — Returns server address
- L40 _public prototype_ `virtual uint16 GetPort() const = 0;` — Returns server port
- L43 _public prototype_ `virtual FString GetProtocolName() const = 0;` — Returns server protocol name
- L46 _public prototype_ `virtual void KillSession(const FString& NodeId) = 0;` — Kill all sessions of a specific node
- L51 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsConnectionAllowedDelegate, const FDisplayClusterSessionInfo&);` — Connection validation delegate
- L52 _public prototype_ `virtual FIsConnectionAllowedDelegate& OnIsConnectionAllowed() = 0;`
- L55 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterServer, FSessionOpenedEvent, const FDisplayClusterSessionInfo&);` — Session opened event
- L56 _public prototype_ `virtual FSessionOpenedEvent& OnSessionOpened() = 0;`
- L59 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterServer, FSessionClosedEvent, const FDisplayClusterSessionInfo&);` — Session closed event
- L60 _public prototype_ `virtual FSessionClosedEvent& OnSessionClosed() = 0;`
- L63 _public prototype_ `virtual void NotifySessionOpened(const FDisplayClusterSessionInfo& SessionInfo) = 0;` — Safe SessionOpened notification from a session thread
- L66 _public prototype_ `virtual void NotifySessionClosed(const FDisplayClusterSessionInfo& SessionInfo) = 0;` — Safe SessionClosed notification from a session thread

#### Free symbols / members of external scopes

- L51 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsConnectionAllowedDelegate, const FDisplayClusterSessionInfo&);` — Connection validation delegate
- L55 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterServer, FSessionOpenedEvent, const FDisplayClusterSessionInfo&);` — Session opened event
- L59 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterServer, FSessionClosedEvent, const FDisplayClusterSessionInfo&);` — Session closed event

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Listener/DisplayClusterHelloMessageStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterHelloMessageStrings`
- L13 _variable_ `constexpr static const TCHAR* ArgumentsDefaultCategory = TEXT("HC"` (scope `DisplayClusterHelloMessageStrings`)
- L15 _namespace_ `namespace Hello` (scope `DisplayClusterHelloMessageStrings`)
- L17 _variable_ `constexpr static const TCHAR* Name = TEXT("Hel` (scope `DisplayClusterHelloMessageStrings::Hello`)
- L18 _variable_ `constexpr static const TCHAR* TypeRequest = TEXT("Req` (scope `DisplayClusterHelloMessageStrings::Hello`)
- L19 _variable_ `constexpr static const TCHAR* ArgNodeId = TEXT("Nod` (scope `DisplayClusterHelloMessageStrings::Hello`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Listener/DisplayClusterTcpListener.h` (Private)


#### class `FDisplayClusterTcpListener`  
`class FDisplayClusterTcpListener : protected FRunnable`  
_L20-113_
- inherits: `FRunnable`
- desc: TCP connection listener. Listens for incoming connections and redirects the requests to specific server implementations. Can be shared by nDisplay services that use internal communication protocol.
- L25 _public prototype_ `FDisplayClusterTcpListener(bool bIsShared, const FString& InName);`
- L26 _public prototype_ `virtual ~FDisplayClusterTcpListener();`
- L31 _public prototype_ `bool StartListening(const FString& InAddr, const uint16 InPort);` — Start listening to address:port
- L34 _public prototype_ `bool StartListening(const FIPv4Endpoint& Endpoint);` — Start listening to an endpoint
- L37 _public prototype_ `void StopListening(bool bWaitForCompletion);` — Stop listening
- L40 _public prototype_ `void WaitForCompletion();` — Wait unless working thread is finished
- L43 _public function_ `bool IsListening() const` — Is currently listening
- L49 _public prototype_ `bool GetListeningParams(FString& OutAddr, uint16& OutPort);` — Returns listenting address & port
- L52 _public prototype_ `FString GetListeningHost() const;` — Returns listening host
- L55 _public prototype_ `uint16 GetListeningPort() const;` — Returns listening port
- L58 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FConnectionAcceptedDelegate, FDisplayClusterSessionInfo&);` — Delegate for processing incoming connections
- L61 _public function_ `FConnectionAcceptedDelegate& OnConnectionAccepted()` — Returns connection validation delegate
- L67 _public prototype_ `FConnectionAcceptedDelegate& OnConnectionAccepted(const FString& ProtocolName);` — Returns protocol - bound delegate
- L72 _protected prototype_ `virtual bool Init() override;`
- L73 _protected prototype_ `virtual uint32 Run() override;`
- L74 _protected prototype_ `virtual void Stop() override;`
- L75 _protected prototype_ `virtual void Exit() override;`
- L81 _protected prototype_ `bool GenIPv4Endpoint(const FString& Addr, const uint16 Port, FIPv4Endpoint& EP) const;` — Fills endpoint data with given address and port
- L86 _private member_ `FString Name;` — Socket name
- L89 _private member_ `FSocket* SocketObj = nullptr;` — Listening socket
- L92 _private member_ `FIPv4Endpoint Endpoint;` — Listening endpoint
- L95 _private member_ `TUniquePtr<FRunnableThread> ThreadObj;` — Holds the listening thread object
- L98 _private member_ `std::atomic<bool> bIsListening = false;` — Current listening state
- L101 _private member_ `FConnectionAcceptedDelegate ConnectionAcceptedDelegate;` — Holds a delegate to be invoked when an incoming connection has been accepted.
- L106 _private prototype_ `bool ProcessIncomingConnection(FDisplayClusterSessionInfo& SessionInfo);` — Handles incoming connections
- L109 _private member_ `TMap<FString, FConnectionAcceptedDelegate> ProtocolDispatchingMap;` — ProtocolName - to - ServiceDelegate map for transferring connection ownership to an appropriate server
- L112 _private member_ `FCriticalSection InternalsCS;` — Critical section for access control

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FConnectionAcceptedDelegate, FDisplayClusterSessionInfo&);` — Delegate for processing incoming connections

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Packet/DisplayClusterPacketBinary.h` (Private)


#### class `FDisplayClusterPacketBinary`  
`class FDisplayClusterPacketBinary : public IDisplayClusterPacket`  
_L11-51_
- inherits: `IDisplayClusterPacket`
- desc: Binary packet type for display cluster networking
- L15 _public function_ `TArray<uint8>& GetPacketData()`
- L20 _public function_ `const TArray<uint8>& GetPacketData() const`
- L25 _public function_ `void SetEventData(const TArray<uint8>& InPacketData)`
- L34 _public prototype_ `virtual bool SendPacket(FDisplayClusterSocketOperations& SocketOps) override;`
- L35 _public prototype_ `virtual bool RecvPacket(FDisplayClusterSocketOperations& SocketOps) override;`
- L36 _public prototype_ `virtual FString ToLogString(bool bDetailed = false) const override;`
- L50 _private member_ `TArray<uint8> PacketData;`

#### struct `FDisplayClusterPacketBinary::FPacketHeader`  
`struct FPacketHeader`  
_L39-47_
- L41 _public member_ `uint32 PacketBodyLength;`
- L43 _public function_ `FString ToString()`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Packet/DisplayClusterPacketInternal.h` (Private)


#### class `FDisplayClusterPacketInternal`  
`class FDisplayClusterPacketInternal : public IDisplayClusterPacket , public IDisplayClusterSerializable`  
_L18-270_
- inherits: `IDisplayClusterPacket,IDisplayClusterSerializable`
- desc: Internal packet type. Used for in-cluster synchronization and data replication.
- L23 _public function_ `FDisplayClusterPacketInternal()`
- L26 _public function_ `FDisplayClusterPacketInternal(const FString& InName, const FString& InType, const FString& InProtocol) : Name(InName) , Type(InType) , Protocol(InProtocol) , CommResult(EDisplayClusterCommResult::Ok)`
- L35 _public function_ `inline const FString& GetName() const` — Packet name
- L41 _public function_ `inline const FString& GetType() const` — Packet type
- L47 _public function_ `inline const FString& GetProtocol() const` — Packet protocol
- L52 _public function_ `inline EDisplayClusterCommResult GetCommResult() const`
- L57 _public function_ `inline void SetCommResult(EDisplayClusterCommResult InCommResult)`
- L65 _public function_ `template <typename ValType> bool GetTextArg(const FString& SectionName, const FString& ArgName, ValType& ArgVal) const` — Get specific text argument from the packet
- L85 _public function_ `template <typename ValType> void SetTextArg(const FString& SectionName, const FString& ArgName, const ValType& ArgVal)` — Set new text argument to the packet
- L97 _public function_ `void RemoveTextArg(const FString& SectionName, const FString& ArgName)` — Remove text argument
- L107 _public function_ `const TMap<FString, FString> GetTextArgs(const FString& SectionName) const` — Get all text arguments of a specified section
- L114 _public function_ `void SetTextArgs(const FString& SectionName, TMap<FString, FString> Data)` — Set all text arguments to a specified section
- L121 _public function_ `bool GetBinArg(const FString& SectionName, const FString& ArgName, TArray<uint8>& ArgVal, bool bKeepData = false)` — Get specific binary argument from the packet
- L142 _public function_ `void SetBinArg(const FString& SectionName, const FString& ArgName, TArray<uint8> ArgVal)` — Set new binary argument to the packet
- L148 _public function_ `void RemoveBinArg(const FString& SectionName, const FString& ArgName)` — Remove binary argument
- L158 _public function_ `TMap<FString, TArray<uint8>> GetBinArgs(const FString& SectionName, bool bKeepData = false)` — Get all binary arguments of a specified section
- L174 _public function_ `void SetBinArgs(const FString& SectionName, TMap<FString, TArray<uint8>> Data)` — Set all binary arguments to a specified section
- L181 _public function_ `void AddTextObject(const FString& SectionName, const FString& Object)` — Adds a text object to the packet
- L193 _public function_ `void GetTextObjects(const FString& SectionName, TArray<FString>& OutObjects, bool bKeepData = false)` — Get all text objects
- L208 _public function_ `void AddBinObject(const FString& SectionName, TArray<uint8> Object)` — Adds a binary object to the packet
- L214 _public function_ `void GetBinObjects(const FString& SectionName, TArray<TArray<uint8>>& OutObjects, bool bKeepData = false)` — Get all binary objects
- L230 _public prototype_ `virtual bool SendPacket(FDisplayClusterSocketOperations& SocketOps) override;`
- L231 _public prototype_ `virtual bool RecvPacket(FDisplayClusterSocketOperations& SocketOps) override;`
- L232 _public prototype_ `virtual FString ToLogString(bool bDetailed = false) const override;`
- L238 _public prototype_ `virtual void SerializeDC(FArchive& Ar) override;`
- L244 _protected prototype_ `FString ToString() const;` — Text representation of the whole meessage
- L245 _protected prototype_ `FString ArgsToString() const;`
- L259 _private member_ `FString Name;`
- L260 _private member_ `FString Type;`
- L261 _private member_ `FString Protocol;`
- L263 _private member_ `EDisplayClusterCommResult CommResult;`
- L265 _private member_ `TMap<FString, TMap<FString, FString>> TextArguments;`
- L266 _private member_ `TMap<FString, TMap<FString, TArray<uint8>>> BinaryArguments;`
- L268 _private member_ `TMap<FString, TArray<FString>> TextObjects;`
- L269 _private member_ `TMap<FString, TArray<TArray<uint8>>> BinaryObjects;`

#### struct `FDisplayClusterPacketInternal::FPacketHeader`  
`struct FPacketHeader`  
_L248-256_
- L250 _public member_ `uint32 PacketBodyLength;`
- L252 _public function_ `FString ToString()`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Packet/DisplayClusterPacketJson.h` (Private)


#### class `FDisplayClusterPacketJson`  
`class FDisplayClusterPacketJson : public IDisplayClusterPacket`  
_L12-52_
- inherits: `IDisplayClusterPacket`
- desc: JSON based packet type for display cluster networking
- L16 _public function_ `FDisplayClusterPacketJson() : JsonData(new FJsonObject)`
- L21 _public function_ `inline const TSharedPtr<FJsonObject> GetJsonData() const`
- L26 _public function_ `inline void SetJsonData(TSharedPtr<FJsonObject> InJsonData)`
- L35 _public prototype_ `virtual bool SendPacket(FDisplayClusterSocketOperations& SocketOps) override;`
- L36 _public prototype_ `virtual bool RecvPacket(FDisplayClusterSocketOperations& SocketOps) override;`
- L37 _public prototype_ `virtual FString ToLogString(bool bDetailed = false) const override;`
- L51 _private member_ `TSharedPtr<FJsonObject> JsonData;`

#### struct `FDisplayClusterPacketJson::FPacketHeader`  
`struct FPacketHeader`  
_L40-48_
- L42 _public member_ `uint32 PacketBodyLength = 0;`
- L44 _public function_ `FString ToString()`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Packet/IDisplayClusterPacket.h` (Private)


#### class `IDisplayClusterPacket`  
`class IDisplayClusterPacket`  
_L13-22_
- desc: Network packet interface
- L16 _public prototype_ `virtual ~IDisplayClusterPacket() = default;`
- L19 _public prototype_ `virtual bool SendPacket(FDisplayClusterSocketOperations& SocketOps) = 0;`
- L20 _public prototype_ `virtual bool RecvPacket(FDisplayClusterSocketOperations& SocketOps) = 0;`
- L21 _public prototype_ `virtual FString ToLogString(bool bDetailed = false) const = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Protocol/IDisplayClusterProtocolClusterSync.h` (Private)


#### class `IDisplayClusterProtocolClusterSync`  
`class IDisplayClusterProtocolClusterSync`  
_L19-50_
- desc: Cluster synchronization protocol. Used to synchronize/replicate any DisplayCluster data on the game thread.
- L23 _public prototype_ `virtual ~IDisplayClusterProtocolClusterSync() = default;`
- L28 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() = 0;` — Game start barrier syncrhonization
- L31 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() = 0;` — Frame start barrier syncrhonization
- L34 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() = 0;` — Frame end barrier syncrhonization
- L37 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) = 0;` — Engine time syncrhonization
- L40 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) = 0;` — Custom objects syncrhonization
- L43 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson, ESPMode::ThreadSafe>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary, ESPMode::ThreadSafe>>& OutBinaryEvents) = 0;` — Cluster events syncrhonization
- L46 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) = 0;` — Native UE input syncrhonization
- L49 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) = 0;` — Custom states synchronization

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Protocol/IDisplayClusterProtocolEventsBinary.h` (Private)


#### class `IDisplayClusterProtocolEventsBinary`  
`class IDisplayClusterProtocolEventsBinary`  
_L13-23_
- desc: Binary cluster events protocol.
- L17 _public prototype_ `virtual ~IDisplayClusterProtocolEventsBinary() = default;`
- L22 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) = 0;` — Emits binary cluster event

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Protocol/IDisplayClusterProtocolEventsJson.h` (Private)


#### class `IDisplayClusterProtocolEventsJson`  
`class IDisplayClusterProtocolEventsJson`  
_L13-23_
- desc: JSON cluster events protocol
- L17 _public prototype_ `virtual ~IDisplayClusterProtocolEventsJson() = default;`
- L22 _public prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) = 0;` — Emits JSON cluster event

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Protocol/IDisplayClusterProtocolGenericBarrier.h` (Private)


#### class `IDisplayClusterProtocolGenericBarrier`  
`class IDisplayClusterProtocolGenericBarrier`  
_L12-52_
- desc: Generic barriers protocol. Provides generic barrier sync mechanism.
- L16 _public prototype_ `virtual ~IDisplayClusterProtocolGenericBarrier() = default;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, EBarrierControlResult& Result) = 0;` — Creates new barrier
- L39 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, EBarrierControlResult& Result) = 0;` — Wait until a barrier with specific ID is created and ready to go
- L42 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, EBarrierControlResult& Result) = 0;` — Checks if a specific barrier exists
- L45 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, EBarrierControlResult& Result) = 0;` — Releases specific barrier
- L48 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, EBarrierControlResult& Result) = 0;` — Synchronize calling thread on a specific barrier
- L51 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, EBarrierControlResult& Result) = 0;` — Synchronize calling thread on a specific barrier(with custom data)

#### enum `IDisplayClusterProtocolGenericBarrier::EBarrierControlResult`  
`enum class EBarrierControlResult : uint8`  
_L23-31_
- desc: Just a union of different barrier control operation results to simplify the management API
- L25 _public enumerator_ `CreatedSuccessfully = 0`
- L26 _public enumerator_ `AlreadyExists`
- L27 _public enumerator_ `NotFound`
- L28 _public enumerator_ `ReleasedSuccessfully`
- L29 _public enumerator_ `SynchronizedSuccessfully`
- L30 _public enumerator_ `UnknownError`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Protocol/IDisplayClusterProtocolInternalComm.h` (Private)


#### class `IDisplayClusterProtocolInternalComm`  
`class IDisplayClusterProtocolInternalComm`  
_L12-65_
- desc: In-cluster communication protocol. Used to maintain cluster lifetime.
- L16 _public prototype_ `virtual ~IDisplayClusterProtocolInternalComm() = default;`
- L36 _public function_ `friend FArchive& operator << (FArchive& Ar, FNodeServicesHostingInfo& Struct)` — Serialization operator
- L58 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) = 0;` — Provides whole cluster hosting information
- L61 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) = 0;` — A synchronization/negotiation step to recover after failure
- L64 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) = 0;` — Primary-to-Secondary notification about secondary node losses

#### struct `IDisplayClusterProtocolInternalComm::FNodeServicesHostingInfo`  
`struct FNodeServicesHostingInfo`  
_L23-44_
- desc: Holds all the ports being listened on by a single node
- L26 _public member_ `uint16 ClusterSyncPort = 0;` — Cluster syncrhonization internal port
- L29 _public member_ `uint16 BinaryEventsPort = 0;` — Binary events external port
- L32 _public member_ `uint16 JsonEventsPort = 0;` — JSON events external port

#### struct `IDisplayClusterProtocolInternalComm::FClusterServicesHostingInfo`  
`struct FClusterServicesHostingInfo`  
_L49-53_
- desc: Holds per-node information about the ports being listened
- L52 _public member_ `TMap<FName, FNodeServicesHostingInfo> ClusterHostingInfo;` — NodeId-to-HostingInfo map

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Protocol/IDisplayClusterProtocolRenderSync.h` (Private)


#### class `IDisplayClusterProtocolRenderSync`  
`class IDisplayClusterProtocolRenderSync`  
_L12-22_
- desc: Rendering synchronization protocol. Used to synchronize frame presentation on RHI thread.
- L16 _public prototype_ `virtual ~IDisplayClusterProtocolRenderSync() = default;`
- L21 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() = 0;` — Synchronize RHI thread on a network barrier

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterEventsBinary/DisplayClusterClusterEventsBinaryClient.h` (Private)


#### class `FDisplayClusterClusterEventsBinaryClient`  
`class FDisplayClusterClusterEventsBinaryClient : public FDisplayClusterClient<FDisplayClusterPacketBinary> , public IDisplayClusterProtocolEventsBinary`  
_L15-39_
- inherits: `FDisplayClusterClient<FDisplayClusterPacketBinary>,IDisplayClusterProtocolEventsBinary`
- desc: Binary cluster events TCP client
- L21 _public prototype_ `FDisplayClusterClusterEventsBinaryClient(const FName& InName, bool bIsInternal = true);`
- L26 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;`
- L32 _public prototype_ `EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`
- L38 _private member_ `const bool bIsInternalClient;` — Whether this client is intended to be used with an internal server, and therefore greet on connection

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterEventsBinary/DisplayClusterClusterEventsBinaryService.h` (Private)


#### class `FDisplayClusterClusterEventsBinaryService`  
`class FDisplayClusterClusterEventsBinaryService : public FDisplayClusterService , public IDisplayClusterSessionPacketHandler<FDisplayClusterPacketBinary, false> , protected IDisplayClusterProtocolEventsBinary`  
_L14-50_
- inherits: `FDisplayClusterService,IDisplayClusterSessionPacketHandler<FDisplayClusterPacketBinary,false>,IDisplayClusterProtocolEventsBinary`
- desc: Binary cluster events server
- L21 _public prototype_ `FDisplayClusterClusterEventsBinaryService(const FName& InstanceName);`
- L23 _public prototype_ `virtual ~FDisplayClusterClusterEventsBinaryService();`
- L28 _public prototype_ `virtual FString GetProtocolName() const override;`
- L34 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) override;` — Creates session instance for this service
- L37 _protected prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback when a session is closed
- L42 _protected prototype_ `virtual typename IDisplayClusterSessionPacketHandler<FDisplayClusterPacketBinary, false>::ReturnType ProcessPacket(const TSharedPtr<FDisplayClusterPacketBinary>& Request, const FDisplayClusterSessionInfo& SessionInfo) override;`
- L48 _protected prototype_ `virtual EDisplayClusterCommResult EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterEventsBinary/DisplayClusterClusterEventsBinaryStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterClusterEventsBinaryStrings`
- L13 _externvar_ `extern const FString ProtocolName;` (scope `DisplayClusterClusterEventsBinaryStrings`)
- L14 _externvar_ `extern const FString TypeRequest;` (scope `DisplayClusterClusterEventsBinaryStrings`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterEventsJson/DisplayClusterClusterEventsJsonClient.h` (Private)


#### class `FDisplayClusterClusterEventsJsonClient`  
`class FDisplayClusterClusterEventsJsonClient : public FDisplayClusterClient<FDisplayClusterPacketJson> , public IDisplayClusterProtocolEventsJson`  
_L13-37_
- inherits: `FDisplayClusterClient<FDisplayClusterPacketJson>,IDisplayClusterProtocolEventsJson`
- desc: JSON cluster events TCP client
- L19 _public prototype_ `FDisplayClusterClusterEventsJsonClient(const FName& InName, bool bIsInternal = true);`
- L24 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;`
- L30 _public prototype_ `EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`
- L36 _private member_ `const bool bIsInternalClient;` — Whether this client is intended to be used with an internal server, and therefore greet on connection

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterEventsJson/DisplayClusterClusterEventsJsonService.h` (Private)


#### class `FDisplayClusterClusterEventsJsonService`  
`class FDisplayClusterClusterEventsJsonService : public FDisplayClusterService , public IDisplayClusterSessionPacketHandler<FDisplayClusterPacketJson, false> , protected IDisplayClusterProtocolEventsJson`  
_L15-53_
- inherits: `FDisplayClusterService,IDisplayClusterSessionPacketHandler<FDisplayClusterPacketJson,false>,IDisplayClusterProtocolEventsJson`
- desc: JSON cluster events server
- L22 _public prototype_ `FDisplayClusterClusterEventsJsonService(const FName& InInstanceName);`
- L24 _public prototype_ `virtual ~FDisplayClusterClusterEventsJsonService();`
- L29 _public prototype_ `virtual FString GetProtocolName() const override;`
- L35 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) override;` — Creates session instance for this service
- L40 _private prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback when a session is closed
- L45 _protected prototype_ `virtual typename IDisplayClusterSessionPacketHandler<FDisplayClusterPacketJson, false>::ReturnType ProcessPacket(const TSharedPtr<FDisplayClusterPacketJson>& Request, const FDisplayClusterSessionInfo& SessionInfo) override;`
- L51 _protected prototype_ `virtual EDisplayClusterCommResult EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterEventsJson/DisplayClusterClusterEventsJsonStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterClusterEventsJsonStrings`
- L13 _externvar_ `extern const FString ProtocolName;` (scope `DisplayClusterClusterEventsJsonStrings`)
- L14 _externvar_ `extern const FString TypeRequest;` (scope `DisplayClusterClusterEventsJsonStrings`)
- L16 _externvar_ `extern const FString ArgName;` (scope `DisplayClusterClusterEventsJsonStrings`)
- L17 _externvar_ `extern const FString ArgType;` (scope `DisplayClusterClusterEventsJsonStrings`)
- L18 _externvar_ `extern const FString ArgCategory;` (scope `DisplayClusterClusterEventsJsonStrings`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterSync/DisplayClusterClusterSyncClient.h` (Private)


#### class `FDisplayClusterClusterSyncClient`  
`class FDisplayClusterClusterSyncClient : public FDisplayClusterClient<FDisplayClusterPacketInternal> , public IDisplayClusterProtocolClusterSync`  
_L13-39_
- inherits: `FDisplayClusterClient<FDisplayClusterPacketInternal>,IDisplayClusterProtocolClusterSync`
- desc: Cluster synchronization TCP client
- L19 _public prototype_ `FDisplayClusterClusterSyncClient(const FName& InName);`
- L24 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;`
- L30 _public prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L31 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L32 _public prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L33 _public prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L34 _public prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L35 _public prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson, ESPMode::ThreadSafe>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary, ESPMode::ThreadSafe>>& OutBinaryEvents) override;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterSync/DisplayClusterClusterSyncService.h` (Private)


#### class `FDisplayClusterClusterSyncService`  
`class FDisplayClusterClusterSyncService : public FDisplayClusterService , public IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal, true> , protected IDisplayClusterProtocolClusterSync`  
_L16-97_
- inherits: `FDisplayClusterService,IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal,true>,IDisplayClusterProtocolClusterSync`
- desc: Cluster synchronization TCP server
- L23 _public prototype_ `FDisplayClusterClusterSyncService(const FName& InInstanceName);`
- L25 _public prototype_ `virtual ~FDisplayClusterClusterSyncService();`
- L30 _public prototype_ `virtual bool Start(const FString& Address, const uint16 Port) override;`
- L31 _public prototype_ `virtual bool Start(TSharedRef<FDisplayClusterTcpListener>& ExternalListener) override;`
- L32 _public prototype_ `virtual void Shutdown() override;`
- L33 _public prototype_ `virtual FString GetProtocolName() const override;`
- L34 _public prototype_ `virtual void KillSession(const FString& NodeId) override;`
- L40 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) override;` — Creates session instance for this service
- L45 _private prototype_ `void StartInternal();` — Performs internal initialization during server start
- L48 _private prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback when a session is closed
- L51 _private prototype_ `void ProcessBarrierTimeout(const FString& BarrierName, const TSet<FString>& NodesTimedOut);` — Callbck on barrier timeout
- L54 _private prototype_ `void ShutdownImpl();` — Non-virtual shutdown implementation
- L59 _private prototype_ `void OnStatesSync(FDisplayClusterBarrierPreSyncEndDelegateData& SyncData);` — Handles states synchronization. Generates and propagates data according to the propagation strategy.
- L65 _protected prototype_ `virtual TSharedPtr<FDisplayClusterPacketInternal> ProcessPacket(const TSharedPtr<FDisplayClusterPacketInternal>& Request, const FDisplayClusterSessionInfo& SessionInfo) override;`
- L71 _protected prototype_ `virtual EDisplayClusterCommResult WaitForGameStart() override;`
- L72 _protected prototype_ `virtual EDisplayClusterCommResult WaitForFrameStart() override;`
- L73 _protected prototype_ `virtual EDisplayClusterCommResult WaitForFrameEnd() override;`
- L74 _protected prototype_ `virtual EDisplayClusterCommResult GetTimeData(double& OutDeltaTime, double& OutGameTime, TOptional<FQualifiedFrameTime>& OutFrameTime) override;`
- L75 _protected prototype_ `virtual EDisplayClusterCommResult GetObjectsData(EDisplayClusterSyncGroup InSyncGroup, TMap<FString, TArray<uint8>>& OutObjectsData) override;`
- L76 _protected prototype_ `virtual EDisplayClusterCommResult GetEventsData(TArray<TSharedPtr<FDisplayClusterClusterEventJson, ESPMode::ThreadSafe>>& OutJsonEvents, TArray<TSharedPtr<FDisplayClusterClusterEventBinary, ESPMode::ThreadSafe>>& OutBinaryEvents) override;`
- L77 _protected prototype_ `virtual EDisplayClusterCommResult GetNativeInputData(TMap<FString, TArray<uint8>>& OutNativeInputData) override;`
- L78 _protected prototype_ `virtual EDisplayClusterCommResult PropagateStatesData(const TArray<uint8>& InLocalStatesData, TArray<uint8>& OutClusterStatesData) override;`
- L84 _private member_ `TUniquePtr<IDisplayClusterBarrier> BarrierGameStart;` — Game start sync barrier
- L87 _private member_ `TUniquePtr<IDisplayClusterBarrier> BarrierFrameStart;` — Frame start barrier
- L90 _private member_ `TUniquePtr<IDisplayClusterBarrier> BarrierFrameEnd;` — Frame end barrier
- L93 _private member_ `TUniquePtr<IDisplayClusterBarrier> BarrierStatesSync;` — Custom states sync barrier
- L96 _private member_ `TMap<FString, TUniquePtr<IDisplayClusterBarrier>*> ServiceBarriers;` — Auxiliary container that keeps all the barriers

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/ClusterSync/DisplayClusterClusterSyncStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterClusterSyncStrings`
- L13 _externvar_ `extern const FString ProtocolName;` (scope `DisplayClusterClusterSyncStrings`)
- L15 _externvar_ `extern const FString TypeRequest;` (scope `DisplayClusterClusterSyncStrings`)
- L16 _externvar_ `extern const FString TypeResponse;` (scope `DisplayClusterClusterSyncStrings`)
- L18 _externvar_ `extern const FString ArgumentsDefaultCategory;` (scope `DisplayClusterClusterSyncStrings`)
- L19 _externvar_ `extern const FString ArgumentsJsonEvents;` (scope `DisplayClusterClusterSyncStrings`)
- L20 _externvar_ `extern const FString ArgumentsBinaryEvents;` (scope `DisplayClusterClusterSyncStrings`)
- L22 _namespace_ `namespace WaitForGameStart` (scope `DisplayClusterClusterSyncStrings`)
- L24 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::WaitForGameStart`)
- L27 _namespace_ `namespace WaitForFrameStart` (scope `DisplayClusterClusterSyncStrings`)
- L29 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::WaitForFrameStart`)
- L32 _namespace_ `namespace WaitForFrameEnd` (scope `DisplayClusterClusterSyncStrings`)
- L34 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::WaitForFrameEnd`)
- L37 _namespace_ `namespace GetTimeData` (scope `DisplayClusterClusterSyncStrings`)
- L39 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::GetTimeData`)
- L41 _externvar_ `extern const FString ArgDeltaTime;` (scope `DisplayClusterClusterSyncStrings::GetTimeData`)
- L42 _externvar_ `extern const FString ArgGameTime;` (scope `DisplayClusterClusterSyncStrings::GetTimeData`)
- L43 _externvar_ `extern const FString ArgIsFrameTimeValid;` (scope `DisplayClusterClusterSyncStrings::GetTimeData`)
- L44 _externvar_ `extern const FString ArgFrameTime;` (scope `DisplayClusterClusterSyncStrings::GetTimeData`)
- L47 _namespace_ `namespace GetObjectsData` (scope `DisplayClusterClusterSyncStrings`)
- L49 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::GetObjectsData`)
- L51 _externvar_ `extern const FString ArgSyncGroup;` (scope `DisplayClusterClusterSyncStrings::GetObjectsData`)
- L54 _namespace_ `namespace GetEventsData` (scope `DisplayClusterClusterSyncStrings`)
- L56 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::GetEventsData`)
- L59 _namespace_ `namespace GetNativeInputData` (scope `DisplayClusterClusterSyncStrings`)
- L61 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::GetNativeInputData`)
- L63 _externvar_ `extern const FString ArgNativeInputData;` (scope `DisplayClusterClusterSyncStrings::GetNativeInputData`)
- L66 _namespace_ `namespace PropagateStatesData` (scope `DisplayClusterClusterSyncStrings`)
- L68 _externvar_ `extern const FString Name;` (scope `DisplayClusterClusterSyncStrings::PropagateStatesData`)
- L70 _externvar_ `extern const FString ArgLocalStatesData;` (scope `DisplayClusterClusterSyncStrings::PropagateStatesData`)
- L71 _externvar_ `extern const FString ArgClusterStatesData;` (scope `DisplayClusterClusterSyncStrings::PropagateStatesData`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/DisplayClusterService.h` (Private)


#### struct `FDisplayClusterServiceFailureEvent`  
`struct FDisplayClusterServiceFailureEvent`  
_L23-42_
- desc: A container to keep all the information about any potential networking failures
- L38 _public member_ `TOptional<FString> NodeFailed;` — The ID of the cluster node that failed
- L41 _public member_ `ENodeFailType FailureType = ENodeFailType::Unknown;` — Failure type

#### enum `FDisplayClusterServiceFailureEvent::ENodeFailType`  
`enum class ENodeFailType : uint8`  
_L28-33_
- desc: Cluster node lost
- L30 _public enumerator_ `Unknown`
- L31 _public enumerator_ `BarrierTimeOut`
- L32 _public enumerator_ `ConnectionLost`

#### class `FDisplayClusterService`  
`class FDisplayClusterService : public FDisplayClusterServer`  
_L48-99_
- inherits: `FDisplayClusterServer`
- desc: Abstract DisplayCluster service
- L54 _public prototype_ `FDisplayClusterService(const FString& Name);`
- L59 _public prototype_ `static EThreadPriority ConvertThreadPriorityFromCvarValue(int ThreadPriority);` — A helper function to convert a cvar integer into the thread priority EThreadPriority enum value
- L62 _public prototype_ `static EThreadPriority GetThreadPriority();` — Returns thread priority that is currently set by the corresponding CVar
- L67 _public prototype_ `DECLARE_EVENT_OneParam(FDisplayClusterService, FNodeFailedEvent, const FDisplayClusterServiceFailureEvent&);` — Networking failure notification event
- L68 _public function_ `FNodeFailedEvent& OnNodeFailed()`
- L76 _protected prototype_ `void SetSessionInfoCache(const FDisplayClusterSessionInfo& SessionInfo);` — Cache session info data (calling thread) if needed for child service implementations
- L79 _protected prototype_ `const FDisplayClusterSessionInfo& GetSessionInfoCache() const;` — Returns session info of the calling thread
- L82 _protected prototype_ `void ClearCache();` — Resets whole session info cache
- L85 _protected prototype_ `bool IsLocalRequest() const;` — Checks if an incoming request is local (was sent by this node)
- L90 _private member_ `TMap<uint32, FDisplayClusterSessionInfo> SessionInfoCache;` — Session info cache
- L93 _private member_ `mutable FCriticalSection SessionInfoCacheCS;` — A critical section to safely accesss the session info cache
- L98 _private member_ `FNodeFailedEvent NodeFailedEvent;` — Failure reporting event

#### Free symbols / members of external scopes

- L67 _delegate_ `DECLARE_EVENT_OneParam(FDisplayClusterService, FNodeFailedEvent, const FDisplayClusterServiceFailureEvent&);` — Networking failure notification event

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/GenericBarrier/DisplayClusterGenericBarrierClient.h` (Private)


#### class `FDisplayClusterGenericBarrierClient`  
`class FDisplayClusterGenericBarrierClient : public FDisplayClusterClient<FDisplayClusterPacketInternal> , public IDisplayClusterProtocolGenericBarrier`  
_L16-40_
- inherits: `FDisplayClusterClient<FDisplayClusterPacketInternal>,IDisplayClusterProtocolGenericBarrier`
- desc: Generic barriers TCP client
- L22 _public prototype_ `FDisplayClusterGenericBarrierClient(const FName& InName);`
- L27 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;`
- L33 _public prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, EBarrierControlResult& Result) override;`
- L34 _public prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, EBarrierControlResult& Result) override;`
- L35 _public prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, EBarrierControlResult& Result) override;`
- L36 _public prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, EBarrierControlResult& Result) override;`
- L37 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, EBarrierControlResult& Result) override;`
- L38 _public prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, EBarrierControlResult& Result) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/GenericBarrier/DisplayClusterGenericBarrierService.h` (Private)


#### class `FDisplayClusterGenericBarrierService`  
`class FDisplayClusterGenericBarrierService : public FDisplayClusterService , public IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal, true> , protected IDisplayClusterProtocolGenericBarrier`  
_L18-116_
- inherits: `FDisplayClusterService,IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal,true>,IDisplayClusterProtocolGenericBarrier`
- desc: Generic barriers TCP server
- L39 _public prototype_ `FDisplayClusterGenericBarrierService(const FName& InInstanceName);`
- L41 _public prototype_ `virtual ~FDisplayClusterGenericBarrierService();`
- L46 _public prototype_ `virtual void Shutdown() override;`
- L47 _public prototype_ `virtual FString GetProtocolName() const override;`
- L48 _public prototype_ `virtual void KillSession(const FString& NodeId) override;`
- L54 _public prototype_ `TSharedPtr<IDisplayClusterBarrier> GetBarrier(const FString& BarrierId);` — Returns barrier by ID
- L57 _public prototype_ `TSharedPtr<const FBarrierInfo> GetBarrierInfo(const FString& BarrierId) const;` — Returns barrier information
- L62 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) override;` — Creates session instance for this service
- L67 _protected prototype_ `virtual TSharedPtr<FDisplayClusterPacketInternal> ProcessPacket(const TSharedPtr<FDisplayClusterPacketInternal>& Request, const FDisplayClusterSessionInfo& SessionInfo) override;`
- L73 _protected prototype_ `virtual EDisplayClusterCommResult CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout, EBarrierControlResult& Result) override;`
- L74 _protected prototype_ `virtual EDisplayClusterCommResult WaitUntilBarrierIsCreated(const FString& BarrierId, EBarrierControlResult& Result) override;`
- L75 _protected prototype_ `virtual EDisplayClusterCommResult IsBarrierAvailable(const FString& BarrierId, EBarrierControlResult& Result) override;`
- L76 _protected prototype_ `virtual EDisplayClusterCommResult ReleaseBarrier(const FString& BarrierId, EBarrierControlResult& Result) override;`
- L77 _protected prototype_ `virtual EDisplayClusterCommResult SyncOnBarrier(const FString& BarrierId, const FString& CallerId, EBarrierControlResult& Result) override;`
- L78 _protected prototype_ `virtual EDisplayClusterCommResult SyncOnBarrierWithData(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData, EBarrierControlResult& Result) override;`
- L84 _private prototype_ `void ShutdownImpl();` — Non-virtual shutdown implementation
- L87 _private prototype_ `void InitializeBarrierInfo(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers);` — An auxiliary function that is responsible for barrier information slot initialization
- L90 _private prototype_ `void ReleaseBarrierInfo(const FString& BarrierId);` — An auxiliary function that is responsible for barrier information cleanup
- L93 _private prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback when a session is closed
- L96 _private prototype_ `void UnregisterClusterNode(const FString& NodeId);` — Unbinds specific cluster node and all its sync callers from all GP barriers
- L101 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterBarrier>> Barriers;` — The barriers managed by this server
- L104 _private member_ `TMap<FString, FEvent*> BarrierCreationEvents;` — Barrier creation events
- L107 _private member_ `mutable FCriticalSection BarriersCS;` — Critical section for internal data access synchronization
- L112 _private member_ `TMap<FString, TSharedRef<FBarrierInfo>> BarriersInfo;` — Holds extra information per - barrier
- L115 _private member_ `mutable FCriticalSection BarriersInfoCS;` — Critical section to synchronize access to the barriers information container

#### struct `FDisplayClusterGenericBarrierService::FBarrierInfo`  
`struct FBarrierInfo`  
_L28-35_
- desc: Additional barrier information that might be useful outside of the server
- L31 _public member_ `TMap<FString, TSet<FString>> NodeToThreadsMapping;` — Holds ClusterNodeId-to-CallerIDs mapping
- L34 _public member_ `TMap<FString, FString> ThreadToNodeMapping;` — Holds CallerID-to-ClusterNodeId mapping (reversed version of NodeToThreadsMapping)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/GenericBarrier/DisplayClusterGenericBarrierStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterGenericBarrierStrings`
- L13 _externvar_ `extern const FString ProtocolName;` (scope `DisplayClusterGenericBarrierStrings`)
- L15 _externvar_ `extern const FString TypeRequest;` (scope `DisplayClusterGenericBarrierStrings`)
- L16 _externvar_ `extern const FString TypeResponse;` (scope `DisplayClusterGenericBarrierStrings`)
- L18 _externvar_ `extern const FString ArgumentsDefaultCategory;` (scope `DisplayClusterGenericBarrierStrings`)
- L21 _externvar_ `extern const FString ArgBarrierId;` (scope `DisplayClusterGenericBarrierStrings`) — Shared arguments
- L22 _externvar_ `extern const FString ArgResult;` (scope `DisplayClusterGenericBarrierStrings`)
- L24 _namespace_ `namespace CreateBarrier` (scope `DisplayClusterGenericBarrierStrings`)
- L26 _externvar_ `extern const FString Name;` (scope `DisplayClusterGenericBarrierStrings::CreateBarrier`)
- L28 _externvar_ `extern const FString ArgCallers;` (scope `DisplayClusterGenericBarrierStrings::CreateBarrier`)
- L29 _externvar_ `extern const FString ArgTimeout;` (scope `DisplayClusterGenericBarrierStrings::CreateBarrier`)
- L32 _namespace_ `namespace WaitUntilBarrierIsCreated` (scope `DisplayClusterGenericBarrierStrings`)
- L34 _externvar_ `extern const FString Name;` (scope `DisplayClusterGenericBarrierStrings::WaitUntilBarrierIsCreated`)
- L37 _namespace_ `namespace IsBarrierAvailable` (scope `DisplayClusterGenericBarrierStrings`)
- L39 _externvar_ `extern const FString Name;` (scope `DisplayClusterGenericBarrierStrings::IsBarrierAvailable`)
- L42 _namespace_ `namespace ReleaseBarrier` (scope `DisplayClusterGenericBarrierStrings`)
- L44 _externvar_ `extern const FString Name;` (scope `DisplayClusterGenericBarrierStrings::ReleaseBarrier`)
- L47 _namespace_ `namespace SyncOnBarrier` (scope `DisplayClusterGenericBarrierStrings`)
- L49 _externvar_ `extern const FString Name;` (scope `DisplayClusterGenericBarrierStrings::SyncOnBarrier`)
- L51 _externvar_ `extern const FString ArgCallerId;` (scope `DisplayClusterGenericBarrierStrings::SyncOnBarrier`)
- L54 _namespace_ `namespace SyncOnBarrierWithData` (scope `DisplayClusterGenericBarrierStrings`)
- L56 _externvar_ `extern const FString Name;` (scope `DisplayClusterGenericBarrierStrings::SyncOnBarrierWithData`)
- L58 _externvar_ `extern const FString ArgCallerId;` (scope `DisplayClusterGenericBarrierStrings::SyncOnBarrierWithData`)
- L59 _externvar_ `extern const FString ArgRequestData;` (scope `DisplayClusterGenericBarrierStrings::SyncOnBarrierWithData`)
- L60 _externvar_ `extern const FString ArgResponseData;` (scope `DisplayClusterGenericBarrierStrings::SyncOnBarrierWithData`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/InternalComm/DisplayClusterInternalCommClient.h` (Private)


#### class `FDisplayClusterInternalCommClient`  
`class FDisplayClusterInternalCommClient : public FDisplayClusterClient<FDisplayClusterPacketInternal> , public IDisplayClusterProtocolInternalComm`  
_L13-34_
- inherits: `FDisplayClusterClient<FDisplayClusterPacketInternal>,IDisplayClusterProtocolInternalComm`
- desc: Cluster synchronization TCP client
- L19 _public prototype_ `FDisplayClusterInternalCommClient(const FName& InName);`
- L24 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;`
- L30 _public prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L31 _public prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L32 _public prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/InternalComm/DisplayClusterInternalCommService.h` (Private)


#### class `FDisplayClusterInternalCommService`  
`class FDisplayClusterInternalCommService : public FDisplayClusterService , public IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal, true> , protected IDisplayClusterProtocolInternalComm`  
_L16-93_
- inherits: `FDisplayClusterService,IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal,true>,IDisplayClusterProtocolInternalComm`
- desc: In-cluster communication TCP server
- L23 _public prototype_ `FDisplayClusterInternalCommService(const FName& InInstanceName);`
- L25 _public prototype_ `virtual ~FDisplayClusterInternalCommService();`
- L30 _public prototype_ `virtual bool Start(const FString& Address, const uint16 Port) override;`
- L31 _public prototype_ `virtual bool Start(TSharedRef<FDisplayClusterTcpListener>& ExternalListener) override;`
- L32 _public prototype_ `virtual void Shutdown() override;`
- L33 _public prototype_ `virtual FString GetProtocolName() const override;`
- L34 _public prototype_ `virtual void KillSession(const FString& NodeId) override;`
- L40 _public prototype_ `TSharedPtr<IDisplayClusterBarrier> GetPostFailureNegotiationBarrier();` — Returns PostFailureNegotiation barrier
- L45 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) override;` — Creates session instance for this service
- L50 _private prototype_ `void StartInternal();` — Performs internal initialization during server start
- L53 _private prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback when a session is closed
- L56 _private prototype_ `void UnregisterClusterNode(const FString& NodeId);` — Unregister cluster node from a barrier
- L59 _private prototype_ `void ProcessBarrierTimeout(const FString& BarrierName, const TSet<FString>& NodesTimedOut);` — Callbck on barrier timeout
- L62 _private prototype_ `void OnHostingInfoSynchronization(FDisplayClusterBarrierPreSyncEndDelegateData& SyncData);` — Hosting info synchronization delegate. It's used to generate barrier response data.
- L65 _private prototype_ `void ShutdownImpl();` — Non-virtual shutdown implementation
- L70 _protected prototype_ `virtual TSharedPtr<FDisplayClusterPacketInternal> ProcessPacket(const TSharedPtr<FDisplayClusterPacketInternal>& Request, const FDisplayClusterSessionInfo& SessionInfo) override;`
- L76 _protected prototype_ `virtual EDisplayClusterCommResult GatherServicesHostingInfo(const FNodeServicesHostingInfo& ThisNodeInfo, FClusterServicesHostingInfo& OutHostingInfo) override;`
- L77 _protected prototype_ `virtual EDisplayClusterCommResult PostFailureNegotiate(TArray<uint8>& InOutRecoveryData) override;`
- L78 _protected prototype_ `virtual EDisplayClusterCommResult RequestNodeDrop(const FString& NodeId, uint8 DropReason) override;`
- L84 _private prototype_ `EDisplayClusterCommResult GatherServicesHostingInfoImpl(const TArray<uint8>& RequestData, TArray<uint8>& ResponseData);` — Effective replacement of GatherServicesHostingInfo to prevent unnecessary deserialization/serialization.
- L89 _private member_ `TSharedPtr<IDisplayClusterBarrier> HostingInfoSyncBarrier;` — This barrier is used to synchronize nodes hosting information on start.
- L92 _private member_ `TSharedPtr<IDisplayClusterBarrier> PostFailureNegotiationBarrier;` — This barrier is used to synchronize all the cluster nodes during failover procedure.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/InternalComm/DisplayClusterInternalCommStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterInternalCommStrings`
- L13 _externvar_ `extern const FString ProtocolName;` (scope `DisplayClusterInternalCommStrings`)
- L15 _externvar_ `extern const FString TypeRequest;` (scope `DisplayClusterInternalCommStrings`)
- L16 _externvar_ `extern const FString TypeResponse;` (scope `DisplayClusterInternalCommStrings`)
- L18 _externvar_ `extern const FString ArgumentsDefaultCategory;` (scope `DisplayClusterInternalCommStrings`)
- L20 _namespace_ `namespace GatherServicesHostingInfo` (scope `DisplayClusterInternalCommStrings`)
- L22 _externvar_ `extern const FString Name;` (scope `DisplayClusterInternalCommStrings::GatherServicesHostingInfo`)
- L24 _externvar_ `extern const FString ArgNodeHostingInfo;` (scope `DisplayClusterInternalCommStrings::GatherServicesHostingInfo`)
- L25 _externvar_ `extern const FString ArgClusterHostingInfo;` (scope `DisplayClusterInternalCommStrings::GatherServicesHostingInfo`)
- L28 _namespace_ `namespace PostFailureNegotiate` (scope `DisplayClusterInternalCommStrings`)
- L30 _externvar_ `extern const FString Name;` (scope `DisplayClusterInternalCommStrings::PostFailureNegotiate`)
- L32 _externvar_ `extern const FString ArgSyncStateData;` (scope `DisplayClusterInternalCommStrings::PostFailureNegotiate`)
- L33 _externvar_ `extern const FString ArgRecoveryData;` (scope `DisplayClusterInternalCommStrings::PostFailureNegotiate`)
- L36 _namespace_ `namespace RequestNodeDrop` (scope `DisplayClusterInternalCommStrings`)
- L38 _externvar_ `extern const FString Name;` (scope `DisplayClusterInternalCommStrings::RequestNodeDrop`)
- L40 _externvar_ `extern const FString ArgNodeId;` (scope `DisplayClusterInternalCommStrings::RequestNodeDrop`)
- L41 _externvar_ `extern const FString ArgDropReason;` (scope `DisplayClusterInternalCommStrings::RequestNodeDrop`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/RenderSync/DisplayClusterRenderSyncClient.h` (Private)


#### class `FDisplayClusterRenderSyncClient`  
`class FDisplayClusterRenderSyncClient : public FDisplayClusterClient<FDisplayClusterPacketInternal> , public IDisplayClusterProtocolRenderSync`  
_L13-32_
- inherits: `FDisplayClusterClient<FDisplayClusterPacketInternal>,IDisplayClusterProtocolRenderSync`
- desc: Rendering synchronization TCP client
- L19 _public prototype_ `FDisplayClusterRenderSyncClient(const FName& InName);`
- L24 _public prototype_ `virtual bool Connect(const FString& Address, const uint16 Port, const uint32 ConnectRetriesAmount = 0, const uint32 ConnectRetryDelay = 0) override;`
- L30 _public prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/RenderSync/DisplayClusterRenderSyncService.h` (Private)


#### class `FDisplayClusterRenderSyncService`  
`class FDisplayClusterRenderSyncService : public FDisplayClusterService , public IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal, true> , protected IDisplayClusterProtocolRenderSync`  
_L17-97_
- inherits: `FDisplayClusterService,IDisplayClusterSessionPacketHandler<FDisplayClusterPacketInternal,true>,IDisplayClusterProtocolRenderSync`
- desc: Rendering synchronization TCP server
- L24 _public prototype_ `FDisplayClusterRenderSyncService(const FName& InInstanceName);`
- L26 _public prototype_ `virtual ~FDisplayClusterRenderSyncService();`
- L31 _public prototype_ `virtual bool Start(const FString& Address, const uint16 Port) override;`
- L32 _public prototype_ `virtual bool Start(TSharedRef<FDisplayClusterTcpListener>& ExternalListener) override;`
- L33 _public prototype_ `virtual void Shutdown() override;`
- L34 _public prototype_ `virtual FString GetProtocolName() const override;`
- L35 _public prototype_ `virtual void KillSession(const FString& NodeId) override;`
- L41 _protected prototype_ `virtual TSharedPtr<IDisplayClusterSession> CreateSession(FDisplayClusterSessionInfo& SessionInfo) override;` — Creates session instance for this service
- L44 _protected prototype_ `void ProcessSessionClosed(const FDisplayClusterSessionInfo& SessionInfo);` — Callback when a session is closed
- L47 _protected prototype_ `void ProcessBarrierTimeout(const FString& BarrierName, const TSet<FString>& NodesTimedOut);` — Callback on barrier timeout
- L52 _protected prototype_ `virtual TSharedPtr<FDisplayClusterPacketInternal> ProcessPacket(const TSharedPtr<FDisplayClusterPacketInternal>& Request, const FDisplayClusterSessionInfo& SessionInfo) override;`
- L58 _private prototype_ `virtual EDisplayClusterCommResult SynchronizeOnBarrier() override;`
- L64 _private prototype_ `void StartInternal();` — Performs internal initialization during server start
- L67 _private prototype_ `void InitializeBarriers();` — Initializes barriers based on available nodes and their sync policies
- L70 _private prototype_ `void ActivateAllBarriers();` — Activates all service barriers
- L73 _private prototype_ `void DeactivateAllBarriers();` — Deactivates all service barriers
- L76 _private prototype_ `void UnsubscribeFromAllBarrierEvents();` — Unsubscribe from all events of all internal barriers
- L79 _private prototype_ `IDisplayClusterBarrier* GetBarrierForNode(const FString& NodeId) const;` — Returns barrier of a node's sync group
- L82 _private prototype_ `void UnregisterClusterNode(const FString& NodeId);` — Unregister cluster node from a barrier
- L85 _private prototype_ `void ShutdownImpl();` — Non-virtual shutdown implementation
- L93 _private member_ `TMap<FString, TUniquePtr<IDisplayClusterBarrier>> PolicyToBarrierMap;` — We can now use different sync policies within the same cluster. Since each policy may have its own synchronization logic, mainly barriers utilization, we need to have individual sync barriers for every sync group. A sync group is a list of nodes that use the same sync policy.
- L96 _private member_ `TMap<FString, FString> NodeToPolicyMap;` — Node ID to sync policy ID(or sync group) mapping

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Service/RenderSync/DisplayClusterRenderSyncStrings.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterRenderSyncStrings`
- L13 _externvar_ `extern const FString ProtocolName;` (scope `DisplayClusterRenderSyncStrings`)
- L15 _externvar_ `extern const FString TypeRequest;` (scope `DisplayClusterRenderSyncStrings`)
- L16 _externvar_ `extern const FString TypeResponse;` (scope `DisplayClusterRenderSyncStrings`)
- L18 _externvar_ `extern const FString ArgumentsDefaultCategory;` (scope `DisplayClusterRenderSyncStrings`)
- L20 _namespace_ `namespace SynchronizeOnBarrier` (scope `DisplayClusterRenderSyncStrings`)
- L22 _externvar_ `extern const FString Name;` (scope `DisplayClusterRenderSyncStrings::SynchronizeOnBarrier`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Session/DisplayClusterSession.h` (Private)


#### class `FDisplayClusterSession`  
`template <typename TPacketType, bool bIsBidirectional> class FDisplayClusterSession : public IDisplayClusterSession , protected FRunnable , protected FDisplayClusterSocketOperations , protected FDisplayClusterSocketOperationsHelper<TPacketType>`  
_L26-205_
- inherits: `IDisplayClusterSession,FRunnable,FDisplayClusterSocketOperations,FDisplayClusterSocketOperationsHelper<TPacketType>`
- desc: Base server socket session class
- L33 _public function_ `FDisplayClusterSession( const FDisplayClusterSessionInfo& InSessionInfo, IDisplayClusterServer& InOwningServer, IDisplayClusterSessionPacketHandler<TPacketType, bIsBidirectional>& InPacketHandler, EThreadPriority InThreadPriority = EThreadPriority::TPri_Normal) : FDisplayClusterSocketOperations(InSessionInfo.Socket, UE::nDisplay::Network::Configuration::PacketBufferSize, InSessionInfo.SessionName) , FDisplayClusterSocketOperationsHelper<TPacketType>(*this, InSessionInfo.SessionName) , SessionInfo(InSessionInfo) , OwningServer(InOwningServer) , PacketHandler(InPacketHandler) , ThreadPriority(InThreadPriority)`
- L51 _public function_ `virtual ~FDisplayClusterSession()`
- L60 _public function_ `virtual const FDisplayClusterSessionInfo& GetSessionInfo() const override final`
- L65 _public function_ `virtual bool StartSession() override`
- L73 _public function_ `virtual void StopSession(bool bWaitForCompletion) override`
- L87 _public function_ `virtual void WaitForCompletion() override`
- L99 _protected function_ `virtual uint32 Run() override`
- L148 _protected function_ `virtual void Stop() override final`
- L155 _protected function_ `IDisplayClusterServer& GetOwner() const`
- L160 _protected function_ `IDisplayClusterSessionPacketHandler<TPacketType, bIsBidirectional>& GetPacketHandler() const`
- L167 _private function_ `template<typename TResponseType> bool HandleSendResponse(const TResponseType& Response)`
- L174 _private function_ `template<> bool HandleSendResponse<typename IDisplayClusterSessionPacketHandler<TPacketType, false>::ReturnType>(const typename IDisplayClusterSessionPacketHandler<TPacketType, false>::ReturnType& Response)`
- L181 _private function_ `template<> bool HandleSendResponse<typename IDisplayClusterSessionPacketHandler<TPacketType, true>::ReturnType>(const typename IDisplayClusterSessionPacketHandler<TPacketType, true>::ReturnType& Response)`
- L193 _private member_ `FDisplayClusterSessionInfo SessionInfo;` — Session info
- L196 _private member_ `IDisplayClusterServer& OwningServer;` — Session owner
- L198 _private member_ `IDisplayClusterSessionPacketHandler<TPacketType, bIsBidirectional>& PacketHandler = nullptr;` — Session packets processor
- L201 _private member_ `const EThreadPriority ThreadPriority;` — Working thread priority
- L204 _private member_ `TUniquePtr<FRunnableThread> ThreadObj;` — Session working thread

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Session/IDisplayClusterSession.h` (Private)


#### class `IDisplayClusterSession`  
`class IDisplayClusterSession`  
_L11-26_
- desc: Session interface
- L14 _public prototype_ `virtual ~IDisplayClusterSession() = default;`
- L18 _public prototype_ `virtual bool StartSession() = 0;` — Start processing of incoming events
- L20 _public prototype_ `virtual void StopSession(bool bWaitForCompletion) = 0;` — Stop  processing of incoming events
- L22 _public prototype_ `virtual void WaitForCompletion() = 0;` — Wait unless session conmpletely stopped and the working thread is release
- L25 _public prototype_ `virtual const FDisplayClusterSessionInfo& GetSessionInfo() const = 0;` — Session info

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Session/IDisplayClusterSessionPacketHandler.h` (Private)


#### class `IDisplayClusterSessionPacketHandler`  
`template <typename TPacketType, bool bIsBidirectional> class IDisplayClusterSessionPacketHandler`  
_L14-27_
- desc: Packet handler interface for all incoming packets
- L17 _public prototype_ `virtual ~IDisplayClusterSessionPacketHandler() = default;`
- L21 _public typedef_ `typedef struct{} NoResponse;` — Kind of hack to avoid any problems with 'void' in the templates
- L23 _public typedef_ `typedef typename std::conditional<bIsBidirectional, TSharedPtr<TPacketType>, NoResponse>::type ReturnType;` — Different return types for unidirectional and bidirectional communication
- L26 _public prototype_ `virtual typename IDisplayClusterSessionPacketHandler<TPacketType, bIsBidirectional>::ReturnType ProcessPacket(const TSharedPtr<TPacketType>& Request, const FDisplayClusterSessionInfo& SessionInfo) = 0;` — Process incoming packet and return response packet

#### struct `IDisplayClusterSessionPacketHandler::(anonymous)`  
`typedef struct`  
_L21-21_
- desc: Kind of hack to avoid any problems with 'void' in the templates

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Transport/DisplayClusterSocketOperations.h` (Private)


#### class `FDisplayClusterSocketOperations`  
`class FDisplayClusterSocketOperations`  
_L11-85_
- desc: Low-level socket operations
- L14 _public prototype_ `FDisplayClusterSocketOperations(FSocket* Socket, int32 PersistentBufferSize, const FString& ConnectionName, bool bReleaseSocketOnDestroy = true);`
- L15 _public prototype_ `virtual ~FDisplayClusterSocketOperations();`
- L19 _public function_ `inline bool IsOpen() const` — Returns true if the socket is valid and connected
- L25 _public function_ `inline FCriticalSection& GetSyncObj()` — Access to the socket synchronization object
- L31 _public function_ `inline bool ConnectSocket(const FInternetAddr& Addr)` — Connect
- L43 _public function_ `inline void CloseSocket()` — Close socket
- L52 _public function_ `inline const FString& GetConnectionName() const` — Access to the connection name
- L58 _public function_ `inline TArray<uint8>& GetPersistentBuffer()` — Access to the internal read/write buffer
- L65 _public prototype_ `static bool RecvChunk(FSocket* const InSocket, TArray<uint8>& ChunkBuffer, const uint32 ChunkSize, const FString& ChunkName = FString("Read` — Receive specified amount of bytes to custom buffer (external socket object)
- L67 _public prototype_ `static bool SendChunk(FSocket* const InSocket, const TArray<uint8>& ChunkBuffer, const uint32 ChunkSize, const FString& ChunkName = FString("Writ` — Send specified amount of bytes from specified buffer (external socket object)
- L70 _public prototype_ `bool RecvChunk(TArray<uint8>& ChunkBuffer, const uint32 ChunkSize, const FString& ChunkName = FString("Read` — Receive specified amount of bytes to custom buffer (internal socket object)
- L72 _public prototype_ `bool SendChunk(const TArray<uint8>& ChankBuffer, const uint32 ChunkSize, const FString& ChunkName = FString("Writ` — Send specified amount of bytes from specified buffer (internal socket object)
- L76 _private member_ `FSocket* Socket = nullptr;` — Socket
- L78 _private member_ `bool bReleaseSocket = false;` — Should the socket be released in .dtor
- L80 _private member_ `TArray<uint8> DataBuffer;` — Data buffer
- L82 _private member_ `FString ConnectionName;` — Connection name (basically for nice logging)
- L84 _private member_ `mutable FCriticalSection CritSecInternals;` — Sync access to internals

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Network/Transport/DisplayClusterSocketOperationsHelper.h` (Private)


#### class `FDisplayClusterSocketOperationsHelper`  
`template <typename TPacketType> class FDisplayClusterSocketOperationsHelper`  
_L15-90_
- desc: Socket operations helper. High level operations with specific packet types.
- L21 _public function_ `FDisplayClusterSocketOperationsHelper(FDisplayClusterSocketOperations& InSocketOps, const FString& InLogHeader = FString()) : SocketOps(InSocketOps) , LogHeader(InLogHeader)`
- L26 _public function_ `virtual ~FDisplayClusterSocketOperationsHelper()`
- L31 _public function_ `TSharedPtr<TPacketType> SendRecvPacket(const TSharedPtr<TPacketType>& Request)`
- L44 _public function_ `bool SendPacket(const TSharedPtr<IDisplayClusterPacket>& Packet)`
- L60 _public function_ `bool SendPacket(const TSharedPtr<TPacketType>& Packet)`
- L70 _public function_ `TSharedPtr<TPacketType> ReceivePacket()`
- L88 _private member_ `FDisplayClusterSocketOperations& SocketOps;`
- L89 _private member_ `FString LogHeader;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Containers/DisplayClusterRender_MeshComponent.h` (Private)


#### class `FDisplayClusterRender_MeshComponent`  
`class FDisplayClusterRender_MeshComponent : public IDisplayClusterRender_MeshComponent`  
_L13-65_
- inherits: `IDisplayClusterRender_MeshComponent`
- L17 _public prototype_ `FDisplayClusterRender_MeshComponent();`
- L18 _public prototype_ `virtual ~FDisplayClusterRender_MeshComponent();`
- L21 _public prototype_ `virtual void AssignStaticMeshComponentRefs(UStaticMeshComponent* InStaticMeshComponent, const FDisplayClusterMeshUVs& InUVs, USceneComponent* InOriginComponent = nullptr, int32 InLODIndex = 0) override;`
- L22 _public prototype_ `virtual void AssignProceduralMeshComponentRefs(UProceduralMeshComponent* InProceduralMeshComponent, const FDisplayClusterMeshUVs& InUVs, USceneComponent* InOriginComponent = nullptr, const int32 InSectionIndex = 0) override;`
- L23 _public prototype_ `virtual void AssignProceduralMeshSection(const FProcMeshSection& InProcMeshSection, const FDisplayClusterMeshUVs& InUVs) override;`
- L24 _public prototype_ `virtual void AssignStaticMesh(const UStaticMesh* InStaticMesh, const FDisplayClusterMeshUVs& InUVs, int32 InLODIndex = 0) override;`
- L25 _public prototype_ `virtual void AssignMeshGeometry(const FDisplayClusterRender_MeshGeometry* InMeshGeometry) override;`
- L27 _public prototype_ `virtual void AssignMeshGeometry_RenderThread(const FDisplayClusterRender_MeshGeometry* InMeshGeometry, const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc) const override;`
- L29 _public prototype_ `virtual void ReleaseMeshComponent() override;`
- L30 _public prototype_ `virtual void ReleaseProxyGeometry() override;`
- L32 _public prototype_ `virtual USceneComponent* GetOriginComponent() const override;`
- L33 _public prototype_ `virtual UMeshComponent* GetMeshComponent() const override;`
- L34 _public prototype_ `virtual UStaticMeshComponent* GetStaticMeshComponent() const override;`
- L35 _public prototype_ `virtual const UStaticMesh* GetStaticMesh() const override;`
- L36 _public prototype_ `virtual UProceduralMeshComponent* GetProceduralMeshComponent() const override;`
- L37 _public prototype_ `virtual const FStaticMeshLODResources* GetStaticMeshComponentLODResources(int32 InLODIndex = 0) const override;`
- L38 _public prototype_ `virtual const FProcMeshSection* GetProceduralMeshComponentSection(const int32 SectionIndex = 0) const override;`
- L40 _public prototype_ `virtual IDisplayClusterRender_MeshComponentProxy* GetMeshComponentProxy_RenderThread() const override;`
- L42 _public prototype_ `virtual void SetGeometryFunc(const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc) override;`
- L44 _public prototype_ `virtual bool IsMeshComponentRefGeometryDirty() const override;`
- L45 _public prototype_ `virtual void MarkMeshComponentRefGeometryDirty() const override;`
- L46 _public prototype_ `virtual void ResetMeshComponentRefGeometryDirty() const override;`
- L47 _public prototype_ `virtual bool EqualsMeshComponentName(const FName& InMeshComponentName) const override;`
- L49 _public prototype_ `virtual EDisplayClusterRender_MeshComponentGeometrySource GetGeometrySource() const override;`
- L52 _private member_ `EDisplayClusterRender_MeshComponentGeometrySource GeometrySource = EDisplayClusterRender_MeshComponentGeometrySource::Disabled;`
- L53 _private member_ `EDisplayClusterRender_MeshComponentProxyDataFunc DataFunc = EDisplayClusterRender_MeshComponentProxyDataFunc::Disabled;`
- L56 _private member_ `FDisplayClusterSceneComponentRef OriginComponentRef;` — Reference containers:
- L57 _private member_ `FDisplayClusterRender_StaticMeshComponentRef StaticMeshComponentRef;`
- L58 _private member_ `FDisplayClusterRender_ProceduralMeshComponentRef ProceduralMeshComponentRef;`
- L61 _private member_ `TWeakObjectPtr<const UStaticMesh> StaticMeshRef;` — store ref to the static mesh
- L64 _private member_ `TSharedPtr<FDisplayClusterRender_MeshComponentProxy, ESPMode::ThreadSafe> MeshComponentProxyPtr;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Containers/DisplayClusterRender_MeshComponentProxy.h` (Private)


#### class `FDisplayClusterRender_MeshComponentProxy`  
`class FDisplayClusterRender_MeshComponentProxy : public IDisplayClusterRender_MeshComponentProxy`  
_L7-32_
- inherits: `IDisplayClusterRender_MeshComponentProxy`
- L11 _public prototype_ `FDisplayClusterRender_MeshComponentProxy();`
- L12 _public prototype_ `virtual ~FDisplayClusterRender_MeshComponentProxy();`
- L15 _public prototype_ `virtual bool IsEnabled_RenderThread() const override;`
- L16 _public prototype_ `virtual bool BeginRender_RenderThread(FRHICommandListImmediate& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit) const override;`
- L17 _public prototype_ `virtual bool FinishRender_RenderThread(FRHICommandListImmediate& RHICmdList) const override;`
- L19 _public prototype_ `void UpdateRHI_RenderThread(FRHICommandListImmediate& RHICmdList, class FDisplayClusterRender_MeshComponentProxyData* InMeshData);`
- L20 _public prototype_ `void Release_RenderThread();`
- L23 _private prototype_ `void ImplRelease();`
- L27 _private member_ `FBufferRHIRef VertexBufferRHI;` — RenderThread resources
- L28 _private member_ `FBufferRHIRef IndexBufferRHI;`
- L30 _private member_ `uint32 NumTriangles = 0;`
- L31 _private member_ `uint32 NumVertices = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Containers/DisplayClusterRender_MeshComponentProxyData.h` (Private)


#### class `FDisplayClusterRender_MeshComponentProxyData`  
`class FDisplayClusterRender_MeshComponentProxyData`  
_L13-93_
- L23 _public prototype_ `FDisplayClusterRender_MeshComponentProxyData(const FString& InSourceGeometryName, const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc, const FStaticMeshLODResources& InStaticMeshLODResource, const FDisplayClusterMeshUVs& InUVs);` — Initialize geometry data from static mesh geometry @param InDataFunc              - Geometry function type @param InStaticMeshLODResource - Source of geometry @param InUVs                   - Map source geometry UVs to DCMeshComponent UVs
- L32 _public prototype_ `FDisplayClusterRender_MeshComponentProxyData(const FString& InSourceGeometryName, const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc, const FProcMeshSection& InProcMeshSection, const FDisplayClusterMeshUVs& InUVs);` — Initialize geometry data from procedural mesh geometry @param InDataFunc        - Geometry function type @param InProcMeshSection - Source of geometry @param InUVs             - Map source geometry UVs to DCMeshComponent UVs
- L40 _public prototype_ `FDisplayClusterRender_MeshComponentProxyData(const FString& InSourceGeometryName, const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc, const FDisplayClusterRender_MeshGeometry& InMeshGeometry);` — Initialize geometry data from nDisplay geometry container @param InDataFunc     - Geometry function type @param InMeshGeometry - Source of geometry
- L42 _public function_ `const TArray<uint32>& GetIndexData() const`
- L45 _public function_ `const TArray<FDisplayClusterMeshVertex>& GetVertexData() const`
- L48 _public function_ `uint32 GetNumTriangles() const`
- L51 _public function_ `uint32 GetNumVertices() const`
- L54 _public function_ `bool IsValid() const`
- L65 _private prototype_ `void UpdateData(const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc);` — Update geometry data with specified func @param InDataFunc     - Geometry function type
- L71 _private prototype_ `void ImplNormalizeToScreenSpace();` — Normalize geometry points to screen space [OutputRemapScreenSpace]
- L77 _private prototype_ `void ImplRemoveInvisibleFaces();` — Visual check: remove faces with UV off-screen [OutputRemapScreenSpace]
- L80 _private prototype_ `bool IsFaceVisible(int32 Face);`
- L81 _private prototype_ `bool IsUVVisible(int32 UVIndex);`
- L85 _public member_ `const FString SourceGeometryName;` — Purpose of logging
- L89 _private member_ `TArray<uint32> IndexData;`
- L90 _private member_ `TArray<FDisplayClusterMeshVertex> VertexData;`
- L91 _private member_ `uint32 NumTriangles = 0;`
- L92 _private member_ `uint32 NumVertices = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Containers/DisplayClusterRender_MeshResources.h` (Private)


#### struct `FDisplayClusterMeshVertexType`  
`struct FDisplayClusterMeshVertexType`  
_L12-25_
- desc: The vertex data used to filter a texture.
- L14 _public member_ `FVector4f Position;`
- L15 _public member_ `FVector2f UV;`
- L16 _public member_ `FVector2f UV_Chromakey;`
- L19 _public function_ `FORCEINLINE void SetVertexData(const FDisplayClusterMeshVertex& In)` — type conversion double -> float

#### class `FDisplayClusterMeshVertexDeclaration`  
`class FDisplayClusterMeshVertexDeclaration : public FRenderResource`  
_L28-37_
- inherits: `FRenderResource`
- desc: The filter vertex declaration resource type.
- L31 _public member_ `FVertexDeclarationRHIRef VertexDeclarationRHI;`
- L34 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L35 _public prototype_ `virtual void ReleaseRHI() override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Containers/DisplayClusterRender_Texture.h` (Private)


#### class `FDisplayClusterRender_Texture`  
`class FDisplayClusterRender_Texture : public IDisplayClusterRender_Texture , public TSharedFromThis<FDisplayClusterRender_Texture, ESPMode::ThreadSafe>`  
_L11-113_
- inherits: `IDisplayClusterRender_Texture,TSharedFromThis<FDisplayClusterRender_Texture,ESPMode::ThreadSafe>`
- desc: Implementation for runtime texture object Can be cached with TDisplayClusterDataCache: Multiple objects can get the same texture by name
- L16 _public prototype_ `FDisplayClusterRender_Texture(const FString& InUniqueTextureName);`
- L17 _public prototype_ `virtual ~FDisplayClusterRender_Texture();`
- L20 _public function_ `virtual TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> ToSharedPtr() override`
- L25 _public function_ `virtual TSharedPtr<const IDisplayClusterRender_Texture, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L30 _public prototype_ `virtual void CreateTexture(const void* InTextureData, const uint32 InComponentDepth, const uint32 InBitDepth, uint32_t InWidth, uint32_t InHeight, bool bInHasCPUAccess=false) override;`
- L32 _public function_ `virtual bool IsEnabled() const override`
- L38 _public function_ `virtual void* GetData() const override`
- L44 _public function_ `virtual uint32_t GetWidth() const override`
- L50 _public function_ `virtual uint32_t GetHeight() const override`
- L56 _public function_ `virtual EPixelFormat GetPixelFormat() const override`
- L62 _public function_ `virtual uint32 GetComponentDepth() const override`
- L68 _public function_ `virtual FRHITexture* GetRHITexture() const override`
- L76 _public prototype_ `static int32 GetDataCacheTimeOutInFrames();` — Return DataCache timeout in frames.
- L79 _public prototype_ `static bool IsDataCacheEnabled();` — Return true if DataCache is enabled.
- L82 _public function_ `inline const FString& GetDataCacheName() const` — Returns the unique name of this texture for DataCache.
- L88 _public function_ `inline void ReleaseDataCacheItem()` — Method for releasing a cached data item, called before its destructor.
- L97 _protected prototype_ `void SetTextureResource(const TSharedPtr<FDisplayClusterRender_TextureResource, ESPMode::ThreadSafe>& InTextureResourcePtr);` — Set new texture resource.
- L100 _protected prototype_ `const TSharedPtr<FDisplayClusterRender_TextureResource, ESPMode::ThreadSafe>& GetTextureResource() const;` — Get texture resource: supports both the game thread and the rendering thread.
- L104 _private member_ `TSharedPtr<FDisplayClusterRender_TextureResource, ESPMode::ThreadSafe> TextureResourcePtr;` — The texture's resource, can be NULL
- L109 _private member_ `TSharedPtr<FDisplayClusterRender_TextureResource, ESPMode::ThreadSafe> TextureResourceProxyPtr;` — Value updated and returned by the render-thread to allow fenceless update from the game-thread without causing potential crash in the render thread.
- L112 _private member_ `FString UniqueTextureName;` — Unique texture name

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Containers/DisplayClusterRender_TextureResource.h` (Private)


#### class `FDisplayClusterRender_TextureResource`  
`class FDisplayClusterRender_TextureResource : public FTextureResource , public TSharedFromThis<FDisplayClusterRender_TextureResource, ESPMode::ThreadSafe>`  
_L12-96_
- inherits: `FTextureResource,TSharedFromThis<FDisplayClusterRender_TextureResource,ESPMode::ThreadSafe>`
- desc: Creating a texture resource from memory data Also, this texture data will be stored in memory if bHasCPUAccess is true.
- L17 _public prototype_ `FDisplayClusterRender_TextureResource(const void* InTextureData, const uint32 InComponentDepth, const uint32 InBitDepth, uint32_t InWidth, uint32_t InHeight, bool bInHasCPUAccess);`
- L18 _public prototype_ `virtual ~FDisplayClusterRender_TextureResource();`
- L21 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L25 _public prototype_ `void ReleaseTextureData();` — Release texture data from memory.
- L28 _public prototype_ `void InitializeRenderResource();` — Initializes the render resource.
- L31 _public prototype_ `void ReleaseRenderResource();` — Prepares the resource for deletion.
- L34 _public function_ `bool HasCPUAccess() const` — Whether this texture resource has data in CPU memory.
- L40 _public function_ `bool IsRenderResourceInitialized() const` — Get ptr to resource data in memory. The variable bHasCPUAccess must be true.
- L46 _public function_ `void* GetTextureData() const` — Get ptr to resource data in memory. The variable bHasCPUAccess must be true.
- L52 _public function_ `uint32_t GetWidth() const` — Get texture width.
- L58 _public function_ `uint32_t GetHeight() const` — Get texture height.
- L64 _public function_ `EPixelFormat GetPixelFormat() const` — Get texture pixel format.
- L70 _public function_ `uint32 GetComponentDepth() const` — Get number of components.
- L77 _private member_ `void* TextureData = nullptr;` — RAW data of the texture. Mips not supported now
- L80 _private member_ `uint32_t Width = 0;` — Width of the texture.
- L83 _private member_ `uint32_t Height = 0;` — Height of the texture.
- L86 _private member_ `uint32 ComponentDepth = 0;` — Number of components
- L89 _private member_ `EPixelFormat PixelFormat = EPixelFormat::PF_Unknown;` — Format in which mip data is stored.
- L92 _private member_ `bool bHasCPUAccess = false;` — has CPU access to texture data, dont release from memory
- L95 _private member_ `bool bRenderResourceInitialized = false;` — Is render resource initialized

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/DisplayClusterDeviceBase.h` (Private)


#### class `FDisplayClusterDeviceBase`  
`class FDisplayClusterDeviceBase : public IStereoRenderTargetManager , public IDisplayClusterRenderDevice , public TSharedFromThis<FDisplayClusterDeviceBase, ESPMode::ThreadSafe>`  
_L28-127_
- inherits: `IStereoRenderTargetManager,IDisplayClusterRenderDevice,TSharedFromThis<FDisplayClusterDeviceBase,ESPMode::ThreadSafe>`
- desc: Abstract render device
- L34 _public prototype_ `FDisplayClusterDeviceBase() = delete;`
- L35 _public prototype_ `FDisplayClusterDeviceBase(EDisplayClusterRenderFrameMode InRenderFrameMode);`
- L36 _public prototype_ `virtual ~FDisplayClusterDeviceBase();`
- L42 _public prototype_ `virtual bool Initialize() override;`
- L43 _public prototype_ `virtual void StartScene(UWorld* InWorld) override;`
- L44 _public prototype_ `virtual void EndScene() override;`
- L46 _public prototype_ `virtual IDisplayClusterPresentation* GetPresentation() const override;`
- L48 _public prototype_ `virtual bool BeginNewFrame(FViewport* InViewport, UWorld* InWorld, FDisplayClusterRenderFrame& OutRenderFrame) override;`
- L50 _public prototype_ `virtual void InitializeNewFrame() override;`
- L51 _public prototype_ `virtual void FinalizeNewFrame() override;`
- L57 _public prototype_ `virtual bool IsStereoEnabled() const override;`
- L58 _public prototype_ `virtual bool IsStereoEnabledOnNextFrame() const override;`
- L59 _public prototype_ `virtual bool EnableStereo(bool bStereoEnabled = true) override;`
- L60 _public prototype_ `virtual void AdjustViewRect(int32 ViewIndex, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;`
- L61 _public prototype_ `virtual void CalculateStereoViewOffset(const int32 ViewIndex, FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override;`
- L62 _public prototype_ `virtual FMatrix GetStereoProjectionMatrix(const int32 ViewIndex) const override;`
- L64 _public prototype_ `virtual bool HasExternalViewState(const int32 ViewIndex) const override;`
- L65 _public prototype_ `virtual FSceneViewStateInterface* GetExternalViewState(const int32 ViewIndex) override;`
- L67 _public prototype_ `virtual void RenderTexture_RenderThread(class FRDGBuilder& GraphBuilder, FRDGTextureRef BackBuffer, FRDGTextureRef SrcTexture, FVector2f WindowSize) const override;`
- L70 _public function_ `virtual FVector2D GetTextSafeRegionBounds() const override` — So far, we don’t need any region bounds
- L75 _public function_ `virtual int32 GetDesiredNumberOfViews(bool bStereoRequested) const override`
- L80 _public prototype_ `virtual EStereoscopicPass GetViewPassForIndex(bool bStereoRequested, int32 ViewIndex) const override;`
- L82 _public function_ `virtual IStereoRenderTargetManager* GetRenderTargetManager() override`
- L89 _protected function_ `virtual bool ShouldUseSeparateRenderTarget() const override`
- L92 _protected prototype_ `virtual void CalculateRenderTargetSize(const class FViewport& Viewport, uint32& InOutSizeX, uint32& InOutSizeY) override;`
- L93 _protected prototype_ `virtual bool NeedReAllocateViewportRenderTarget(const class FViewport& Viewport) override;`
- L97 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) = 0;` — Factory method to instantiate an output presentation class implementation
- L100 _protected prototype_ `virtual void StartFinalPostprocessSettings(struct FPostProcessSettings* StartPostProcessingSettings, const enum EStereoscopicPass StereoPassType, const int32 StereoViewIndex) override;` — Checks if custom post processing settings is assigned for specific viewport and assign them to be used
- L101 _protected prototype_ `virtual bool OverrideFinalPostprocessSettings(struct FPostProcessSettings* OverridePostProcessingSettings, const enum EStereoscopicPass StereoPassType, const int32 StereoViewIndex, float& BlendWeight) override;`
- L102 _protected prototype_ `virtual void EndFinalPostprocessSettings(struct FPostProcessSettings* FinalPostProcessingSettings, const enum EStereoscopicPass StereoPassType, const int32 StereoViewIndex) override;`
- L105 _protected prototype_ `FDisplayClusterViewportManager* GetViewportManager() const;` — Get a pointer to the DC ViewportManager if it still exists.
- L108 _protected prototype_ `FDisplayClusterViewportManagerProxy* GetViewportManagerProxy_RenderThread() const;` — Get a pointer to the DC ViewportManagerProxy if it still exists.
- L111 _private prototype_ `void OnBackBufferReadyToPresent(SWindow& Window, ISlateViewportProvider& ViewportProvider);`
- L114 _private member_ `TWeakPtr<FDisplayClusterViewportManager, ESPMode::ThreadSafe> ViewportManagerWeakPtr;` — Pointer to the DC ViewportManager from the active DCRA that is currently being used for rendering.
- L117 _private member_ `mutable TWeakPtr<FDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ViewportManagerProxyWeakPtr;` — Pointer to the DC ViewportManagerProxy from the active DCRA that is currently being used for rendering.
- L119 _private member_ `EDisplayClusterRenderFrameMode RenderFrameMode = EDisplayClusterRenderFrameMode::Mono;`
- L120 _private member_ `int32 DesiredNumberOfViews = 0;`
- L123 _private member_ `mutable FCriticalSection InternalsSyncScope;` — Data access synchronization
- L126 _private member_ `FDisplayClusterPresentationBase* CustomPresentHandler = nullptr;` — Pointer to the current presentation handler

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/DisplayClusterRenderDeviceFactoryInternal.h` (Private)


#### class `FDisplayClusterRenderDeviceFactoryInternal`  
`class FDisplayClusterRenderDeviceFactoryInternal : public IDisplayClusterRenderDeviceFactory`  
_L11-20_
- inherits: `IDisplayClusterRenderDeviceFactory`
- desc: Factory for internal rendering devices
- L15 _public prototype_ `FDisplayClusterRenderDeviceFactoryInternal() = default;`
- L16 _public prototype_ `virtual ~FDisplayClusterRenderDeviceFactoryInternal() = default;`
- L19 _public prototype_ `virtual TSharedPtr<IDisplayClusterRenderDevice, ESPMode::ThreadSafe> Create(const FString& InDeviceType) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/Monoscopic/DisplayClusterDeviceMonoscopicVulkan.h` (Private)


#### class `FDisplayClusterDeviceMonoscopicVulkan`  
`class FDisplayClusterDeviceMonoscopicVulkan : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Monoscopic render device (Vulkan)
- L14 _public prototype_ `FDisplayClusterDeviceMonoscopicVulkan();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceMonoscopicVulkan() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/Monoscopic/Windows/DisplayClusterDeviceMonoscopicDX11.h` (Private)


#### class `FDisplayClusterDeviceMonoscopicDX11`  
`class FDisplayClusterDeviceMonoscopicDX11 : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Monoscopic render device (DirectX 11)
- L14 _public prototype_ `FDisplayClusterDeviceMonoscopicDX11();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceMonoscopicDX11() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/Monoscopic/Windows/DisplayClusterDeviceMonoscopicDX12.h` (Private)


#### class `FDisplayClusterDeviceMonoscopicDX12`  
`class FDisplayClusterDeviceMonoscopicDX12 : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Monoscopic render device (DirectX 12)
- L14 _public prototype_ `FDisplayClusterDeviceMonoscopicDX12();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceMonoscopicDX12() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/QuadBufferStereo/DisplayClusterDeviceQuadBufferStereoBase.h` (Private)


#### class `FDisplayClusterDeviceQuadBufferStereoBase`  
`class FDisplayClusterDeviceQuadBufferStereoBase : public FDisplayClusterDeviceBase`  
_L10-16_
- inherits: `FDisplayClusterDeviceBase`
- desc: Abstract frame sequenced active stereo device
- L14 _public prototype_ `FDisplayClusterDeviceQuadBufferStereoBase();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceQuadBufferStereoBase() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/QuadBufferStereo/DisplayClusterDeviceQuadBufferStereoVulkan.h` (Private)


#### class `FDisplayClusterDeviceQuadBufferStereoVulkan`  
`class FDisplayClusterDeviceQuadBufferStereoVulkan : public FDisplayClusterDeviceQuadBufferStereoBase`  
_L12-21_
- inherits: `FDisplayClusterDeviceQuadBufferStereoBase`
- desc: Frame sequenced active stereo (Vulkan)
- L16 _public prototype_ `FDisplayClusterDeviceQuadBufferStereoVulkan();`
- L17 _public prototype_ `virtual ~FDisplayClusterDeviceQuadBufferStereoVulkan() = default;`
- L20 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/QuadBufferStereo/Windows/DisplayClusterDeviceQuadBufferStereoDX11.h` (Private)


#### class `FDisplayClusterDeviceQuadBufferStereoDX11`  
`class FDisplayClusterDeviceQuadBufferStereoDX11 : public FDisplayClusterDeviceQuadBufferStereoBase`  
_L12-21_
- inherits: `FDisplayClusterDeviceQuadBufferStereoBase`
- desc: Frame sequenced active stereo (DirectX 11)
- L16 _public prototype_ `FDisplayClusterDeviceQuadBufferStereoDX11();`
- L17 _public prototype_ `virtual ~FDisplayClusterDeviceQuadBufferStereoDX11() = default;`
- L20 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/QuadBufferStereo/Windows/DisplayClusterDeviceQuadBufferStereoDX12.h` (Private)


#### class `FDisplayClusterDeviceQuadBufferStereoDX12`  
`class FDisplayClusterDeviceQuadBufferStereoDX12 : public FDisplayClusterDeviceQuadBufferStereoBase`  
_L12-21_
- inherits: `FDisplayClusterDeviceQuadBufferStereoBase`
- desc: Frame sequenced active stereo (DirectX 12)
- L16 _public prototype_ `FDisplayClusterDeviceQuadBufferStereoDX12();`
- L17 _public prototype_ `virtual ~FDisplayClusterDeviceQuadBufferStereoDX12() = default;`
- L20 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/SideBySide/DisplayClusterDeviceSideBySideVulkan.h` (Private)


#### class `FDisplayClusterDeviceSideBySideVulkan`  
`class FDisplayClusterDeviceSideBySideVulkan : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Side-by-side passive stereoscopic device (Vulkan RHI)
- L14 _public prototype_ `FDisplayClusterDeviceSideBySideVulkan();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceSideBySideVulkan() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/SideBySide/Windows/DisplayClusterDeviceSideBySideDX11.h` (Private)


#### class `FDisplayClusterDeviceSideBySideDX11`  
`class FDisplayClusterDeviceSideBySideDX11 : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Side-by-side passive stereoscopic device
- L14 _public prototype_ `FDisplayClusterDeviceSideBySideDX11();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceSideBySideDX11() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/SideBySide/Windows/DisplayClusterDeviceSideBySideDX12.h` (Private)


#### class `FDisplayClusterDeviceSideBySideDX12`  
`class FDisplayClusterDeviceSideBySideDX12 : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Side-by-side passive stereoscopic device
- L14 _public prototype_ `FDisplayClusterDeviceSideBySideDX12();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceSideBySideDX12() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/TopBottom/DisplayClusterDeviceTopBottomVulkan.h` (Private)


#### class `FDisplayClusterDeviceTopBottomVulkan`  
`class FDisplayClusterDeviceTopBottomVulkan : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Top-bottom passive stereoscopic device (Vulkan RHI)
- L14 _public prototype_ `FDisplayClusterDeviceTopBottomVulkan();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceTopBottomVulkan() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/TopBottom/Windows/DisplayClusterDeviceTopBottomDX11.h` (Private)


#### class `FDisplayClusterDeviceTopBottomDX11`  
`class FDisplayClusterDeviceTopBottomDX11 : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Top-bottom passive stereoscopic device
- L14 _public prototype_ `FDisplayClusterDeviceTopBottomDX11();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceTopBottomDX11() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Device/TopBottom/Windows/DisplayClusterDeviceTopBottomDX12.h` (Private)


#### class `FDisplayClusterDeviceTopBottomDX12`  
`class FDisplayClusterDeviceTopBottomDX12 : public FDisplayClusterDeviceBase`  
_L10-19_
- inherits: `FDisplayClusterDeviceBase`
- desc: Top-bottom passive stereoscopic device
- L14 _public prototype_ `FDisplayClusterDeviceTopBottomDX12();`
- L15 _public prototype_ `virtual ~FDisplayClusterDeviceTopBottomDX12() = default;`
- L18 _protected prototype_ `virtual FDisplayClusterPresentationBase* CreatePresentationObject(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/DisplayClusterRenderManager.h` (Private)


#### class `FDisplayClusterRenderManager`  
`class FDisplayClusterRenderManager : public IPDisplayClusterRenderManager`  
_L24-135_
- inherits: `IPDisplayClusterRenderManager`
- desc: Render manager. Responsible for everything related to the visuals.
- L28 _public prototype_ `FDisplayClusterRenderManager();`
- L29 _public prototype_ `virtual ~FDisplayClusterRenderManager();`
- L35 _public prototype_ `virtual bool Init(EDisplayClusterOperationMode OperationMode) override;`
- L36 _public prototype_ `virtual void Release() override;`
- L37 _public prototype_ `virtual bool StartSession(UDisplayClusterConfigurationData* InConfigData, const FString& InNodeId) override;`
- L38 _public prototype_ `virtual void EndSession() override;`
- L39 _public prototype_ `virtual bool StartScene(UWorld* InWorld) override;`
- L40 _public prototype_ `virtual void EndScene() override;`
- L41 _public prototype_ `virtual void PreTick(float DeltaSeconds) override;`
- L48 _public prototype_ `virtual IDisplayClusterRenderDevice* GetRenderDevice() const override;` — Device
- L49 _public prototype_ `virtual bool RegisterRenderDeviceFactory(const FString& InDeviceType, TSharedPtr<IDisplayClusterRenderDeviceFactory>& InFactory) override;`
- L50 _public prototype_ `virtual bool UnregisterRenderDeviceFactory(const FString& InDeviceType) override;`
- L52 _public prototype_ `virtual bool RegisterSynchronizationPolicyFactory(const FString& InSyncPolicyType, TSharedPtr<IDisplayClusterRenderSyncPolicyFactory>& InFactory) override;` — Synchronization
- L53 _public prototype_ `virtual bool UnregisterSynchronizationPolicyFactory(const FString& InSyncPolicyType) override;`
- L54 _public prototype_ `virtual TSharedPtr<IDisplayClusterRenderSyncPolicy> GetCurrentSynchronizationPolicy() override;`
- L56 _public prototype_ `virtual bool RegisterProjectionPolicyFactory(const FString& InProjectionType, TSharedPtr<IDisplayClusterProjectionPolicyFactory>& InFactory) override;` — Projection
- L57 _public prototype_ `virtual bool UnregisterProjectionPolicyFactory(const FString& InProjectionType) override;`
- L58 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicyFactory> GetProjectionPolicyFactory(const FString& InProjectionType) override;`
- L59 _public prototype_ `virtual void GetRegisteredProjectionPolicies(TArray<FString>& OutPolicyIDs) const override;`
- L61 _public prototype_ `virtual bool RegisterPostProcessFactory(const FString& InPostProcessType, TSharedPtr<IDisplayClusterPostProcessFactory>& InFactory) override;` — Post-process
- L62 _public prototype_ `virtual bool UnregisterPostProcessFactory(const FString& InPostProcessType) override;`
- L63 _public prototype_ `virtual TSharedPtr<IDisplayClusterPostProcessFactory> GetPostProcessFactory(const FString& InPostProcessType) override;`
- L64 _public prototype_ `virtual void GetRegisteredPostProcess(TArray<FString>& OutPostProcessIDs) const override;`
- L66 _public prototype_ `virtual bool RegisterWarpPolicyFactory(const FString& InWarpPolicyType, TSharedPtr<IDisplayClusterWarpPolicyFactory>& Factory) override;` — Warp policy
- L67 _public prototype_ `virtual bool UnregisterWarpPolicyFactory(const FString& InWarpPolicyType) override;`
- L68 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpPolicyFactory> GetWarpPolicyFactory(const FString& InWarpPolicyType) override;`
- L69 _public prototype_ `virtual void GetRegisteredWarpPolicies(TArray<FString>& OutWarpPolicyIDs) const override;`
- L71 _public prototype_ `virtual TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> CreateMeshComponent() const override;` — Resources
- L72 _public prototype_ `virtual TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> GetOrCreateCachedTexture(const FString& InUniqueTextureName) const override;`
- L73 _public prototype_ `virtual IDisplayClusterGUILayerController& GetGuiLayerController() const override;`
- L75 _public function_ `virtual TSharedPtr<IDisplayClusterVblankMonitor, ESPMode::ThreadSafe> GetVblankMonitor() override`
- L80 _public prototype_ `virtual IDisplayClusterViewportManager* GetViewportManager() const override;`
- L91 _private prototype_ `void ResizeWindow(int32 WinX, int32 WinY, int32 ResX, int32 ResY);`
- L92 _private prototype_ `void OnBackBufferReadyToPresent_SetCustomPresent(class SWindow& Window, class ISlateViewportProvider& ViewportProvider) const;`
- L93 _private prototype_ `void OnViewportCreatedHandler_CheckViewportClass() const;`
- L96 _private member_ `EDisplayClusterOperationMode CurrentOperationMode;`
- L99 _private member_ `IDisplayClusterRenderDevice* RenderDevicePtr = nullptr;` — Interface pointer to avoid type casting
- L101 _private member_ `mutable FCustomPresentRHIRef NativePresentHandler = nullptr;`
- L105 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterRenderDeviceFactory>> RenderDeviceFactories;` — Rendering device factories
- L107 _private prototype_ `TSharedPtr<IDisplayClusterRenderDevice, ESPMode::ThreadSafe> CreateRenderDevice() const;` — Helper function to instantiate a rendering device
- L111 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterRenderSyncPolicyFactory>> SyncPolicyFactories;` — Synchronization internals
- L112 _private prototype_ `TSharedPtr<IDisplayClusterRenderSyncPolicy> CreateRenderSyncPolicy() const;`
- L113 _private member_ `mutable TSharedPtr<IDisplayClusterRenderSyncPolicy> SyncPolicy;`
- L117 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterProjectionPolicyFactory>> ProjectionPolicyFactories;` — Projection internals
- L120 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterPostProcessFactory>> PostProcessFactories;` — Postprocess internals
- L123 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterWarpPolicyFactory>> WarpPolicyFactories;` — Warp internals
- L127 _private member_ `mutable FCriticalSection CritSecInternals;` — Internal data access synchronization
- L130 _private member_ `bool bWasWindowFocused = false;` — This flag is used to auto-focus the UE window once on start
- L134 _private member_ `TSharedPtr<IDisplayClusterVblankMonitor, ESPMode::ThreadSafe> VBlankMonitor;` — V-blank monitor

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/DisplayDevice/DisplayClusterDisplayDeviceStrings.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DisplayClusterDisplayDeviceStrings` (scope `UE`)
- L9 _namespace_ `namespace material` (scope `UE::DisplayClusterDisplayDeviceStrings`)
- L11 _namespace_ `namespace asset` (scope `UE::DisplayClusterDisplayDeviceStrings::material`)
- L13 _variable_ `static constexpr const TCHAR* mesh = TEXT("/nD` (scope `UE::DisplayClusterDisplayDeviceStrings::material::asset`)
- L15 _variable_ `static constexpr const TCHAR* preview_mesh = TEXT("/nD` (scope `UE::DisplayClusterDisplayDeviceStrings::material::asset`)
- L16 _variable_ `static constexpr const TCHAR* preview_techvis_mesh = TEXT("/nD` (scope `UE::DisplayClusterDisplayDeviceStrings::material::asset`)
- L19 _namespace_ `namespace attr` (scope `UE::DisplayClusterDisplayDeviceStrings::material`)
- L21 _variable_ `static constexpr const TCHAR* Preview = TEXT("Pre` (scope `UE::DisplayClusterDisplayDeviceStrings::material::attr`)
- L22 _variable_ `static constexpr const TCHAR* Opacity = TEXT("Opa` (scope `UE::DisplayClusterDisplayDeviceStrings::material::attr`)
- L23 _variable_ `static constexpr const TCHAR* Exposure = TEXT("Exp` (scope `UE::DisplayClusterDisplayDeviceStrings::material::attr`)
- L24 _variable_ `static constexpr const TCHAR* Gamma = TEXT("Gam` (scope `UE::DisplayClusterDisplayDeviceStrings::material::attr`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/DisplayDevice/Proxy/DisplayClusterDisplayDeviceProxy_OpenColorIO.h` (Private)


#### class `FDisplayClusterDisplayDeviceProxy_OpenColorIO`  
`class FDisplayClusterDisplayDeviceProxy_OpenColorIO : public IDisplayClusterDisplayDeviceProxy`  
_L13-35_
- inherits: `IDisplayClusterDisplayDeviceProxy`
- desc: Display Device Proxy object (OCIO render pass) [rendering thread]
- L17 _public function_ `FDisplayClusterDisplayDeviceProxy_OpenColorIO(const FString& InOCIOPassId, FOpenColorIORenderPassResources& InOCIOPassResources) : OCIOPassId(InOCIOPassId) , OCIOPassResources(InOCIOPassResources)`
- L22 _public prototype_ `virtual ~FDisplayClusterDisplayDeviceProxy_OpenColorIO() = default;`
- L26 _public prototype_ `virtual bool HasFinalPass_RenderThread() const override;`
- L27 _public prototype_ `virtual bool AddFinalPass_RenderThread(const FDisplayClusterShadersTextureUtilsSettings& InTextureUtilsSettings, const TSharedRef<IDisplayClusterShadersTextureUtils, ESPMode::ThreadSafe>& InTextureUtils) const override;`
- L31 _public member_ `const FString OCIOPassId;`
- L34 _private member_ `FOpenColorIORenderPassResources OCIOPassResources;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Features/AutoExposure/DisplayClusterAutoExposure.h` (Private)


#### struct `FDisplayClusterViewportAutoExposureData`  
`struct FDisplayClusterViewportAutoExposureData : public FDisplayClusterViewport_EyeAdaptationData`  
_L19-38_
- inherits: `FDisplayClusterViewport_EyeAdaptationData`
- desc: Auto-exposure data for a single nDisplay viewport.
- L22 _public prototype_ `FDisplayClusterViewportAutoExposureData() = default;`
- L23 _public function_ `FDisplayClusterViewportAutoExposureData( const FDisplayClusterViewport_EyeAdaptationData& In, const int32 InNumVisiblePixels, const uint32 InFrameNumber) : FDisplayClusterViewport_EyeAdaptationData(In) , NumVisiblePixels(InNumVisiblePixels) , FrameNumber(InFrameNumber)`
- L34 _public member_ `int32 NumVisiblePixels = 0;` — Number of visible pixels covered by this viewport. Used as an input when computing the eye-adaptation weight for this viewport.
- L37 _public member_ `uint32 FrameNumber = 0;` — RT frame number of this data

#### struct `FDisplayClusterNodeAutoExposureData`  
`struct FDisplayClusterNodeAutoExposureData`  
_L41-51_
- desc: Auto-exposure data for all viewports on a single nDisplay node.
- L43 _public prototype_ `FDisplayClusterNodeAutoExposureData() = default;`
- L45 _public function_ `FDisplayClusterNodeAutoExposureData(const TArray<FDisplayClusterViewportAutoExposureData>& InViewports) : Viewports(InViewports)`
- L50 _public member_ `TArray<FDisplayClusterViewportAutoExposureData> Viewports;` — Per-viewport auto-exposure data for this node.

#### class `FDisplayClusterAutoExposure`  
`class FDisplayClusterAutoExposure : public TSharedFromThis<FDisplayClusterAutoExposure, ESPMode::ThreadSafe>`  
_L77-245_
- inherits: `TSharedFromThis<FDisplayClusterAutoExposure,ESPMode::ThreadSafe>`
- desc: Implements the nDisplay multi-viewport AutoExposure feature. Collects exposure data from all viewports across the cluster, synchronizes the result via the cluster network, and applies a unified exposure state to each node’s viewports.
- L81 _public function_ `FDisplayClusterAutoExposure(const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration) : Configuration(InConfiguration) , Settings(MakeShared<FDisplayClusterAutoExposureSettings, ESPMode::ThreadSafe>()) , SettingsProxy(MakeShared<FDisplayClusterAutoExposureSettings, ESPMode::ThreadSafe>())`
- L87 _public prototype_ `~FDisplayClusterAutoExposure() = default;`
- L95 _public prototype_ `void ApplyAutoExposureSettings(const FDisplayClusterConfiguration_AutoExposureSettings& InAutoExposureSettings);` — Apply new auto-exposure settings to the current viewport configuration. @param InAutoExposureSettings  The auto-exposure settings to apply.
- L104 _public prototype_ `void ConfigureAutoExposureForSceneView( const FDisplayClusterViewport& InViewport, uint32 InContextNum, FSceneView& InOutView);` — Configures AutoExposure settings for a given viewport scene view. @param InViewport   The nDisplay viewport to configure. @param InContextNum View context index within the viewport. @param InOutView    Scene view to apply AutoExposure settings to.
- L119 _public prototype_ `void GatherMeterViewportsAutoExposureDataAndSync_RenderThread( const TArray<TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>>& InViewportProxies);` — Collects Auto Exposure (AE) metering data from the given viewport proxies on this node and forwards it to SyncAndComputeAutoExposure() for cluster-wide synchronization and global exposure computation. Executed on the render thread once per frame. @param InViewportProxies  The viewport proxies on this node that provide AE metering input.
- L136 _public prototype_ `void SyncAndComputeAutoExposure();` — Synchronizes Auto Exposure (AE) data across the nDisplay cluster and computes a unified global exposure value. Process: - For cluster: call UpdatePerNodeAutoExposureDataForCluster() - For preview: call UpdatePerNodeAutoExposureDataForPreview() - Compute the global exposure by averaging contributions from the selected viewports (or all, depending on settings). The resulting exposure value is consistent across the cluster, preventing brightness mismatches between displays.
- L139 _public prototype_ `void Release();` — Release inner data.
- L142 _public prototype_ `void OnEntireClusterPreviewRendered();` — Called every time previews for all cluster nodes are rendered.
- L149 _protected prototype_ `void ComputeAutoExposure();` — Compute the global exposure by averaging contributions from the selected viewports (or all, depending on settings).
- L160 _protected prototype_ `bool UpdatePerNodeAutoExposureDataForCluster(const FDisplayClusterNodeAutoExposureData& CurrentNodeAutoExposureData);` — Synchronizes Auto Exposure (AE) data across the nDisplay cluster and update ClusterData. Process: 1. Publish this node's AE data (NodeId + viewports) to the cluster. 2. Receive AE data from other nodes. @param CurrentNodeAutoExposureData  The viewports on this node that contribute AE metrics.
- L167 _protected prototype_ `void UpdatePerNodeAutoExposureDataForPreview(const FDisplayClusterNodeAutoExposureData& CurrentNodeAutoExposureData);` — Update ClusterData for preview rendering. @param CurrentNodeAutoExposureData  The viewports on this node that contribute AE metrics.
- L175 _protected prototype_ `bool EnsureAutoExposureStateUsable();` — Ensures the AutoExposureState exists and is usable. Creates the AutoExposureState instance if it does not already exist. @return true if AutoExposureState is available after this call, false otherwise.
- L178 _protected prototype_ `void ReleaseAutoExposureState();` — Release AutoExposureState instance.
- L196 _private member_ `TArray<FPrevFrameBrightnessCacheEntry> PrevFrameBrightnessCache;` — Cache of previous-frame brightness values per viewport/context. This variable is exclusively used only by ComputeViewportAutoExposureBrightness()
- L208 _private prototype_ `float ComputeViewportAutoExposureBrightness( const FDisplayClusterViewport& InViewport, const uint32 InContextNum, FSceneView& View);` — Computes the viewport brightness. Call only once per frame per viewport context. @param InViewport    nDisplay viewport to evaluate. @param InContextNum  Viewport context index (eye/view pass) within the nDisplay viewport. @param View          Scene view associated with the specified viewport context. @return Computed brightness value used by the auto-exposure update.
- L215 _private member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L218 _private member_ `TOptional<float> TargetBrightness;` — Target Brightness for the current frame.
- L221 _private member_ `TMap<FName, FDisplayClusterNodeAutoExposureData> PerNodeAutoExposureData;` — Per-node AutoExposure data collected from all cluster viewports.
- L224 _private member_ `TSharedRef<FDisplayClusterAutoExposureSettings, ESPMode::ThreadSafe> Settings;` — Runtime settings for Game thread
- L227 _private member_ `TSharedRef<FDisplayClusterAutoExposureSettings, ESPMode::ThreadSafe> SettingsProxy;` — Runtime settings for Rendering thread
- L231 _private member_ `TArray<FDisplayClusterNodeAutoExposureData> DataQueue;` — RT->GT AE data queue
- L233 _private member_ `FCriticalSection DataQueueCS;`
- L237 _private typedef_ `using FAutoExposureState = TDistributedCustomState<FDisplayClusterNodeAutoExposureData>;` — Declare distribute state type
- L241 _private member_ `TSharedPtr<FAutoExposureState> AutoExposureState;` — API to distribute auto exposure data between nodes. Note: Use TDistributedCustomState<> only for cluster
- L244 _private member_ `bool bDisableAutoExposureState = false;` — This flag disables the use of AutoExposureState.

#### struct `FDisplayClusterAutoExposure::FPrevFrameBrightnessCacheEntry`  
`struct FPrevFrameBrightnessCacheEntry`  
_L182-192_
- desc: Cached brightness value from the previous frame, keyed by (Viewport, ContextIndex).
- L185 _public member_ `TWeakPtr<const FDisplayClusterViewport, ESPMode::ThreadSafe> ViewportWeakPtr;` — Weak reference to the viewport this entry belongs to (no ownership).
- L188 _public member_ `uint32 ContextIndex = 0;` — Viewport context index within the viewport (e.g. stereo eye / context).
- L191 _public member_ `TOptional<float> PrevFrameBrightness;` — Previous frame brightness for this viewport/context. Unset until a value is produced.

#### Free symbols / members of external scopes

- L54 _function_ `inline FArchive& operator<<(FArchive& Ar, FDisplayClusterViewportAutoExposureData& In)` — Custom serialization for FDisplayClusterViewportAutoExposureData
- L64 _function_ `inline FArchive& operator<<(FArchive& Ar, FDisplayClusterNodeAutoExposureData& In)` — Custom serialization for FDisplayClusterNodeAutoExposureData

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Features/AutoExposure/DisplayClusterAutoExposureSettings.h` (Private)


#### struct `FDisplayClusterAutoExposureSettings`  
`struct FDisplayClusterAutoExposureSettings`  
_L15-83_
- desc: Runtime AutoExposure settings.
- L17 _public prototype_ `FDisplayClusterAutoExposureSettings() = default;`
- L18 _public prototype_ `FDisplayClusterAutoExposureSettings( const FDisplayClusterConfiguration_AutoExposureSettings& InAutoExposureSettings);`
- L28 _public prototype_ `bool IsNodeAllowedForMetering(const FString& NodeId) const;` — Checks whether the specified cluster node is allowed to contribute its viewports to auto-exposure metering, based on the given settings. @param NodeId     The identifier of the cluster node being tested. @return           True if viewports from this node can be used for metering.
- L39 _public prototype_ `bool IsNodeExcludedFromAutoExposure(const FString& NodeId) const;` — Checks whether the specified cluster node is excluded from auto-exposure. A node marked as excluded prevents all of its viewports from participating in auto-exposure metering and from receiving auto-exposure customization. @param NodeId  Identifier of the cluster node to check. @return        True if the node is excluded from auto-exposure.
- L48 _public prototype_ `bool IsViewportEligibleForMetering(const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags) const;` — Checks whether the specified viewport is eligible to contribute to auto-exposure metering. @param InViewportBaseId  Base viewport identifier (shared across derived/tiled viewports). @param InViewportFlags   Viewport usage flags (e.g. Regular, InCamera, Chromakey, LightCard). @return                  True if this viewport is allowed to participate in AE metering.
- L60 _public prototype_ `bool IsViewportExcludedFromAutoExposure(const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags) const;` — Checks whether the specified viewport is excluded from auto-exposure. A viewport marked as excluded will not contribute to auto-exposure metering and will not receive auto-exposure customization. @param InViewportBaseId  Base viewport identifier (shared across derived/tiled viewports). @param InViewportFlags   Viewport usage flags (e.g. Regular, InCamera, Chromakey, LightCard). @return                  True if the viewport is excluded from auto-exposure.
- L64 _public member_ `bool bEnable = false;` — Enables or disables the AutoExposure feature at runtime.
- L67 _public member_ `TArray<FString> OuterViewportsForMetering;` — Outer viewport names used for auto - exposure metering.
- L70 _public member_ `TArray<FString> ICVFXCamerasForMetering;` — ICVFX camera Id's used for auto-exposure metering.
- L73 _public member_ `TArray<FString> ClusterNodesForMetering;` — Only viewports from these nodes can be used for metering.
- L76 _public member_ `TArray<FString> ExcludedOuterViewports;` — Outer viewpots excluded from auto-exposure.
- L79 _public member_ `TArray<FString> ExcludedICVFXCameras;` — ICVFX cameras excluded from auto-exposure.
- L82 _public member_ `TArray<FString> ExcludedClusterNodes;` — Cluster nodes excluded from auto-exposure.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Features/DisplayClusterUpscaler.h` (Private)


#### class `FDisplayClusterUpscaler`  
`class FDisplayClusterUpscaler`  
_L17-53_
- desc: nDisplay upscaling implementation.
- L24 _public prototype_ `static void InitializeNewFrame();` — Prepares all registered upscaler modular features for the new frame. Should be called at the start of each frame.
- L34 _public prototype_ `static FName PostConfigureViewFamily( const FDisplayClusterUpscalerSettings& InUpscalerSettings, const float InScreenPercentage, const float InDPIScale, FSceneViewFamilyContext& InOutViewFamily, const TArray<FSceneView*>& InOutViews);` — Configure upscaler and viewfamily for ertain settings. @param InUpscalerSettings - (in) the settings to apply for viewport @param InScreenPercentage - (inj screen percentage of the viewport @param InDPIScale         - (in) The DPI scale of the window @param InOutViewFamily    - (in, out) The view family that will be configured. @param InOutViews         - (in, out) The views in the family that will be configured.
- L48 _public prototype_ `static void SetupSceneView( const FDisplayClusterViewport& InViewport, const FDisplayClusterUpscalerSettings& InUpscalerSettings, const FSceneViewFamily& InViewFamily, FSceneView& InOutView);` — Configure scene view for upscalers. @param InViewport         - (in) the viewport who ask for this setup @param InUpscalerSettings - (in) the settings to apply for view @param InViewFamily       - (in) ViewFamily that own this view. @param InOutView          - (in, out) The view that will be configured.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/GUILayer/DisplayClusterGuiLayerController.h` (Private)


#### class `FDisplayClusterGuiLayerController`  
`class FDisplayClusterGuiLayerController : public IDisplayClusterGUILayerController`  
_L26-152_
- inherits: `IDisplayClusterGUILayerController`
- desc: GUI layer controller singleton This class is responsible for propagation of the GUI layer (includes canvases + UMG) across all nDisplay viewports. It also exposes the GUI layer texture to external users.
- L31 _protected prototype_ `FDisplayClusterGuiLayerController();`
- L32 _protected prototype_ `~FDisplayClusterGuiLayerController() = default;`
- L37 _public prototype_ `static FDisplayClusterGuiLayerController& Get();` — Singleton access
- L40 _public prototype_ `static IDisplayClusterGUILayerController::EGuiOutputMode GetOutputModeFromInt(int32 InOutputMode);` — Converts output mode index to the enum value
- L47 _public prototype_ `virtual EGuiOutputMode GetOutputMode() const override;` — Return current operation mode
- L50 _public prototype_ `virtual bool IsEnabled() const override;` — Returns true if GUI controller is currently enabled
- L53 _public prototype_ `virtual FIntPoint GetGuiLayerTextureSize() const override;` — Returns current GUI layer texture size or {0, 0} if disabled
- L56 _public function_ `virtual FTextureRHIRef GetGuiLayerTexture_RenderThread() override` — Returns current GUI layer texture if available, otherwise invalid reference
- L71 _public prototype_ `FRDGTextureRef ProcessFinalTexture_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef FinalTexture);` — Called before copying the final output to the backbuffer. It's used to substitute the current viewport's buffer to its original one stored on SlatePreTick (refer corresponding method). @param FinalTexture - The final Slate outcome that is passed for copying to the backbuffer
- L80 _public prototype_ `void ProcessPostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamiliy, const IDisplayClusterViewportProxy* ViewportProxy);` — Called for each nDisplay view family once rendering is finished. Responsible for drawing the GUI layer on top of every nDisplay viewport. @param ViewFamily - View family that was just rendered @param ViewProxy  - nDisplay viewport (render thread obj)
- L85 _private prototype_ `EGuiOutputMode ExtractOutputModeFromCvar() const;` — Extracts operation mode from the cvar
- L91 _private prototype_ `void HandleSlatePreTick(float InDeltaTime);` — Slate pre-Tick callback, used to substitute original game viewport buffer with our custom texture to store whole Slate rendering output separately, and with high-precision alpha.
- L94 _private prototype_ `FIntPoint ComputeGuiTextureSize() const;` — Computes the size of the UI layer texture
- L99 _private prototype_ `FTextureRHIRef GetViewportRTT_RenderThread();` — Returns current game viewport buffer
- L102 _private prototype_ `void SetViewportRTT_RenderThread(FTextureRHIRef& NewRTT);` — Sets up new game viewport bufer (stays there until end of the frame)
- L113 _private prototype_ `void UpdateTempTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& StorageTexture, FTextureRHIRef& FromTexture, const TCHAR* Name, EPixelFormat PixelFormat);` — Creates or re-creates a texture duplicate from a referenced texture. Allows to override some texture parameters. If some parameters of the referenced texture are different, a new internal texture will be created. @param StorageTexture - An internal "duplicate" of the referenced texture @param FromTexture    - The referenced texture @param Name           - Name of the new texture @param PixelFormat    - Pixel format of the new texture
- L116 _private prototype_ `FTextureRHIRef CreateTextureFrom_RenderThread(FRHICommandListImmediate& RHICmdList, const TCHAR* Name, EPixelFormat PixelFormat, const FIntPoint& InSize);` — Auxiliary function to create an RHI texture.
- L119 _private prototype_ `FRDGTextureRef CreateTextureFrom_RenderThread(FRDGBuilder& GraphBuilder, const TCHAR* Name, const FIntPoint& Size, EPixelFormat PixelFormat, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding);` — Auxiliary function to create an RDG texture.
- L122 _private prototype_ `FRDGTextureRef CreateTextureFrom_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef& FromTexture, const TCHAR* Name, const FIntPoint& Size = FIntPoint::ZeroValue);` — Auxiliary function to create an RDG texture from an RDG texture template, overriding some of the reference parameters.
- L125 _private prototype_ `FRDGTextureRef CreateTextureFrom_RenderThread(FRDGBuilder& GraphBuilder, FRHITexture* FromTexture, const TCHAR* Name, const FIntPoint& Size = FIntPoint::ZeroValue);` — Auxiliary function to create an RDG texture from an RHI texture template, overriding some of the reference parameters.
- L130 _private member_ `const bool bEnabled;` — Whether GUI layer operation is allowed
- L133 _private member_ `EGuiOutputMode OutputMode = EGuiOutputMode::Whole;` — Current GUI output mode (game thread)
- L136 _private member_ `EGuiOutputMode OutputModeRT = EGuiOutputMode::Whole;` — Current GUI output mode (render thread)
- L139 _private member_ `FIntPoint TextureResolution = FIntPoint::ZeroValue;` — Current GUI texture resolution (game thread)
- L142 _private member_ `FIntPoint TextureResolutionRT = FIntPoint::ZeroValue;` — Current GUI texture resolution (render thread)
- L145 _private member_ `FTextureRHIRef TextureViewport;` — The RHI texture reference to the original game viewport buffer
- L148 _private member_ `FTextureRHIRef TextureGUI;` — Internal RHI texture used to redirect GUI rendering to
- L151 _private member_ `TRefCountPtr<IPooledRenderTarget> TextureRotatedGUI;` — Internal RDG texture used to share the rotated GUI among different graph builders (post-render callbacks)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/IPDisplayClusterRenderManager.h` (Private)


#### class `IPDisplayClusterRenderManager`  
`class IPDisplayClusterRenderManager : public IDisplayClusterRenderManager , public IPDisplayClusterManager`  
_L12-18_
- inherits: `IDisplayClusterRenderManager,IPDisplayClusterManager`
- desc: Render manager interface
- L17 _public prototype_ `virtual ~IPDisplayClusterRenderManager() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Monitoring/DisplayClusterVblankMonitor.h` (Private)


#### class `FDisplayClusterVBlankMonitor`  
`class FDisplayClusterVBlankMonitor : public IDisplayClusterVblankMonitor , protected FRunnable`  
_L14-68_
- inherits: `IDisplayClusterVblankMonitor,FRunnable`
- desc: V-blank monitor. It continuously polls the current sync policy for V-blanks and reports the time data to utraces.
- L19 _public prototype_ `FDisplayClusterVBlankMonitor();`
- L20 _public prototype_ `virtual ~FDisplayClusterVBlankMonitor();`
- L24 _public prototype_ `virtual bool StartMonitoring() override;`
- L25 _public prototype_ `virtual bool StopMonitoring() override;`
- L26 _public prototype_ `virtual bool IsMonitoring() override;`
- L27 _public prototype_ `virtual bool IsVblankTimeDataAvailable() override;`
- L28 _public prototype_ `virtual double GetLastVblankTime() override;`
- L29 _public prototype_ `virtual double GetNextVblankTime() override;`
- L34 _protected prototype_ `virtual uint32 Run() override;`
- L39 _private prototype_ `void ResetData();` — Resets internal data
- L43 _private member_ `TUniquePtr<FRunnableThread> WorkingThread;` — Holds the thread object
- L46 _private member_ `bool bIsRunning = false;` — Keeps monitoring status (true if running)
- L49 _private member_ `uint64 VBlankCounter = 0;` — V - blank counter
- L52 _private member_ `bool bThreadExitRequested = false;` — Flag to ask working thread to terminate
- L55 _private member_ `bool bTimedataAvailable = false;` — It's set to true when time data is available (last vblank, period)
- L58 _private member_ `double LastVblankTime = 0;` — A timestamp of the last V-blank
- L61 _private member_ `double VblankPeriod = 0;` — V-blank period (approximate)
- L64 _private member_ `mutable FCriticalSection ControlCS;` — CritSec for control
- L67 _private member_ `mutable FCriticalSection DataCS;` — CritSec for data

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Presentation/DisplayClusterPresentationBase.h` (Private)


#### class `FDisplayClusterPresentationBase`  
`class FDisplayClusterPresentationBase : public FRHICustomPresent , public IDisplayClusterPresentation`  
_L14-59_
- inherits: `FRHICustomPresent,IDisplayClusterPresentation`
- L19 _public prototype_ `FDisplayClusterPresentationBase(FViewport* const InViewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& InSyncPolicy);`
- L20 _public prototype_ `virtual ~FDisplayClusterPresentationBase();`
- L24 _public prototype_ `uint32 GetSwapInt() const;` — Returns internal swap interval
- L30 _protected function_ `virtual bool NeedsNativePresent() override`
- L35 _protected function_ `virtual bool NeedsAdvanceBackbuffer() override`
- L40 _protected prototype_ `virtual bool Present(FRHIViewport* RHIViewport, IRHICommandContext& RHICmdContext, int32& InOutSyncInterval) override;`
- L41 _protected prototype_ `virtual bool PresentOnSubmissionThread(int32& InOutSyncInterval) override;`
- L42 _protected prototype_ `virtual void PostPresent() override;`
- L43 _protected prototype_ `virtual void OnBackBufferResize() override;`
- L46 _protected function_ `FViewport* const GetViewport() const`
- L51 _protected function_ `const TSharedPtr<IDisplayClusterRenderSyncPolicy>& GetSyncPolicyObject() const`
- L57 _private member_ `FViewport* const Viewport;`
- L58 _private member_ `TSharedPtr<IDisplayClusterRenderSyncPolicy> SyncPolicy;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Presentation/DisplayClusterPresentationNative.h` (Private)


#### class `FDisplayClusterPresentationNative`  
`class FDisplayClusterPresentationNative : public FDisplayClusterPresentationBase`  
_L11-19_
- inherits: `FDisplayClusterPresentationBase`
- desc: Present stub to allow to synchronize a cluster with native rendering pipeline (no nDisplay stereo devices used)
- L14 _public function_ `FDisplayClusterPresentationNative(FViewport* const Viewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& SyncPolicy) : FDisplayClusterPresentationBase(Viewport, SyncPolicy)`
- L18 _public prototype_ `virtual ~FDisplayClusterPresentationNative() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Presentation/DisplayClusterPresentationVulkan.h` (Private)


#### class `FDisplayClusterPresentationVulkan`  
`class FDisplayClusterPresentationVulkan : public FDisplayClusterPresentationBase`  
_L11-19_
- inherits: `FDisplayClusterPresentationBase`
- desc: Helper class to encapsulate Vulkan frame presentation
- L14 _public function_ `FDisplayClusterPresentationVulkan(FViewport* const InViewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& InSyncPolicy) : FDisplayClusterPresentationBase(InViewport, InSyncPolicy)`
- L18 _public prototype_ `virtual ~FDisplayClusterPresentationVulkan() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Presentation/Windows/DisplayClusterPresentationDX11.h` (Private)


#### class `FDisplayClusterPresentationDX11`  
`class FDisplayClusterPresentationDX11 : public FDisplayClusterPresentationBase`  
_L11-19_
- inherits: `FDisplayClusterPresentationBase`
- desc: Helper class to encapsulate DX11 frame presentation
- L14 _public function_ `FDisplayClusterPresentationDX11(FViewport* const InViewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& InSyncPolicy) : FDisplayClusterPresentationBase(InViewport, InSyncPolicy)`
- L18 _public prototype_ `virtual ~FDisplayClusterPresentationDX11() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Presentation/Windows/DisplayClusterPresentationDX12.h` (Private)


#### class `FDisplayClusterPresentationDX12`  
`class FDisplayClusterPresentationDX12 : public FDisplayClusterPresentationBase`  
_L11-19_
- inherits: `FDisplayClusterPresentationBase`
- desc: Helper class to encapsulate DX12 frame presentation
- L14 _public function_ `FDisplayClusterPresentationDX12(FViewport* const InViewport, TSharedPtr<IDisplayClusterRenderSyncPolicy>& InSyncPolicy) : FDisplayClusterPresentationBase(InViewport, InSyncPolicy)`
- L18 _public prototype_ `virtual ~FDisplayClusterPresentationDX12() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncHelper.h` (Private)


#### class `IDisplayClusterRenderSyncHelper`  
`class IDisplayClusterRenderSyncHelper`  
_L11-36_
- desc: RHI agnostic helper interface
- L14 _public prototype_ `virtual ~IDisplayClusterRenderSyncHelper() = default;`
- L17 _public function_ `virtual bool WaitForVBlank(FRHIViewport* ViewportRHI)`
- L22 _public function_ `virtual bool IsWaitForVBlankSupported()`
- L27 _public function_ `virtual bool GetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32& OutMaximumFrameLatency)`
- L32 _public function_ `virtual bool SetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32 MaximumFrameLatency)`

#### class `FDisplayClusterRenderSyncHelper`  
`class FDisplayClusterRenderSyncHelper`  
_L44-91_
- desc: Synchronization helper implementation. The main purpose of this class is to solve the combinatoric complexity Platform/RHI/SyncPolicy without making the whole sync policies hierarchy overcomplicated.
- L47 _private prototype_ `FDisplayClusterRenderSyncHelper();`
- L51 _public prototype_ `static IDisplayClusterRenderSyncHelper& Get();` — Singleton access
- L55 _protected prototype_ `static TUniquePtr<IDisplayClusterRenderSyncHelper> CreateHelper();` — Factory method to instantiate helper instance of proper type
- L87 _private member_ `static TUniquePtr<IDisplayClusterRenderSyncHelper> Instance;` — Helper instance
- L90 _private member_ `static FCriticalSection CritSecInternals;` — Singleton access mutex

#### struct `FDisplayClusterRenderSyncHelper::FDCRSHelperDX`  
`struct FDCRSHelperDX : public IDisplayClusterRenderSyncHelper`  
_L60-66_
- inherits: `IDisplayClusterRenderSyncHelper`
- desc: DX helper implementation
- L62 _public prototype_ `virtual bool WaitForVBlank(FRHIViewport* ViewportRHI) override;`
- L63 _public prototype_ `virtual bool IsWaitForVBlankSupported() override;`
- L64 _public prototype_ `virtual bool GetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32& OutMaximumFrameLatency) override;`
- L65 _public prototype_ `virtual bool SetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32 MaximumFrameLatency) override;`

#### struct `FDisplayClusterRenderSyncHelper::FDCRSHelperVulkan`  
`struct FDCRSHelperVulkan : public IDisplayClusterRenderSyncHelper`  
_L71-77_
- inherits: `IDisplayClusterRenderSyncHelper`
- desc: Vulkan helper implementation
- L73 _public prototype_ `virtual bool WaitForVBlank(FRHIViewport* ViewportRHI) override;`
- L74 _public prototype_ `virtual bool IsWaitForVBlankSupported() override;`
- L75 _public prototype_ `virtual bool GetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32& OutMaximumFrameLatency) override;`
- L76 _public prototype_ `virtual bool SetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32 MaximumFrameLatency) override;`

#### struct `FDisplayClusterRenderSyncHelper::FDCRSHelperNull`  
`struct FDCRSHelperNull : public IDisplayClusterRenderSyncHelper`  
_L81-83_
- inherits: `IDisplayClusterRenderSyncHelper`
- desc: Stub implementation for unknown RHI

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyBase.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyBase`  
`class FDisplayClusterRenderSyncPolicyBase : public IDisplayClusterRenderSyncPolicy`  
_L11-56_
- inherits: `IDisplayClusterRenderSyncPolicy`
- desc: Base synchronization policy
- L15 _public function_ `FDisplayClusterRenderSyncPolicyBase(const TMap<FString, FString>& InParameters) : Parameters(InParameters)`
- L19 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyBase() = default;`
- L25 _public prototype_ `virtual bool Initialize() override;` — Non-constructor initialization
- L28 _public prototype_ `virtual bool IsWaitForVBlankFeatureSupported() override;` — VBlank related functions
- L29 _public prototype_ `virtual bool WaitForVBlank(FRHIViewport* ViewportRHI) override;`
- L35 _public prototype_ `void SyncOnBarrier();` — Performs Ethernet barrier synchronization with other nodes in the cluster
- L38 _public function_ `const TMap<FString, FString>& GetParameters() const` — Returns policy configuration parameters
- L45 _protected prototype_ `virtual void WaitForFrameCompletion(FRHIViewport* ViewportRHI);` — Wait for frame rendering completion using a GPU fence
- L48 _protected prototype_ `bool GetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32& OutMaximumFrameLatency);` — Get maximum frame latency
- L51 _protected prototype_ `bool SetMaximumFrameLatency(FRHIViewport* ViewportRHI, uint32 MaximumFrameLatency);` — Set maximum frame latency
- L55 _private member_ `TMap<FString, FString> Parameters;` — Sync policy configuration parameters

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyEthernet.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyEthernet`  
`class FDisplayClusterRenderSyncPolicyEthernet : public FDisplayClusterRenderSyncPolicyBase`  
_L12-74_
- inherits: `FDisplayClusterRenderSyncPolicyBase`
- desc: Base Ethernet synchronization policy
- L16 _public prototype_ `FDisplayClusterRenderSyncPolicyEthernet(const TMap<FString, FString>& Parameters);`
- L18 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyEthernet() = default;`
- L24 _public function_ `virtual FName GetName() const override`
- L30 _public prototype_ `virtual bool SynchronizeClusterRendering(FRHIViewport* ViewportRHI, int32& InOutSyncInterval) override;`
- L33 _protected prototype_ `virtual void Procedure_SynchronizePresent(FRHIViewport* ViewportRHI);`
- L34 _protected prototype_ `virtual void Step_InitializeFrameSynchronization(FRHIViewport* ViewportRHI);`
- L35 _protected prototype_ `virtual void Step_WaitForFrameCompletion(FRHIViewport* ViewportRHI);`
- L36 _protected prototype_ `virtual void Step_WaitForEthernetBarrierSignal_1();`
- L37 _protected prototype_ `virtual void Step_SkipPresentationOnClosestVBlank();`
- L38 _protected prototype_ `virtual void Step_WaitForEthernetBarrierSignal_2();`
- L39 _protected prototype_ `virtual void Step_Present(FRHIViewport* ViewportRHI);`
- L40 _protected prototype_ `virtual void Step_FinalizeFrameSynchronization();`
- L42 _protected prototype_ `double GetVBlankTimestamp(FRHIViewport* ViewportRHI);`
- L43 _protected prototype_ `double GetRefreshPeriod();`
- L47 _private member_ `double B1B = 0.f;` — Sync math
- L48 _private member_ `double B1A = 0.f;` — Barrier 1 after
- L49 _private member_ `double TToB = 0.f;` — Time to VBlank
- L50 _private member_ `double SB = 0.f;` — Sleep before
- L51 _private member_ `double SA = 0.f;` — Sleep after
- L52 _private member_ `double B2B = 0.f;` — Barrier 2 before
- L53 _private member_ `double B2A = 0.f;` — Barrier 2 after
- L54 _private member_ `double PB = 0.f;` — Present before
- L55 _private member_ `double PA = 0.f;` — Present after
- L58 _private member_ `const bool bSimpleSync = false;` — Sync logic (cvars)
- L59 _private member_ `const bool bUseCustomRefreshRate = false;`
- L60 _private member_ `const float CustomRefreshRate = 0.f;`
- L61 _private member_ `const float VBlankFrontEdgeThreshold = 0.f;`
- L62 _private member_ `const float VBlankBackEdgeThreshold = 0.f;`
- L63 _private member_ `const float VBlankThresholdSleepMultiplier = 0.f;`
- L64 _private member_ `const bool VBlankBasisUpdate = false;`
- L65 _private member_ `const float VBlankBasisUpdatePeriod = 0.f;`
- L66 _private member_ `const bool bRiseThreadPriority = false;`
- L69 _private member_ `int SyncIntervalToUse = 1;` — Sync internals
- L70 _private member_ `bool bInternalsInitialized = false;`
- L71 _private member_ `double VBlankBasis = 0;`
- L72 _private member_ `double RefreshPeriod = 0;`
- L73 _private member_ `uint32 FrameCounter = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyEthernetBarrier.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyEthernetBarrier`  
`class FDisplayClusterRenderSyncPolicyEthernetBarrier : public FDisplayClusterRenderSyncPolicyBase`  
_L11-27_
- inherits: `FDisplayClusterRenderSyncPolicyBase`
- desc: Simple version of Ethernet based synchronization (barrier only)
- L15 _public function_ `FDisplayClusterRenderSyncPolicyEthernetBarrier(const TMap<FString, FString>& Parameters) : FDisplayClusterRenderSyncPolicyBase(Parameters)`
- L19 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyEthernetBarrier() = default;`
- L25 _public prototype_ `virtual FName GetName() const override;`
- L26 _public prototype_ `virtual bool SynchronizeClusterRendering(FRHIViewport* ViewportRHI, int32& InOutSyncInterval) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyFactoryInternal.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyFactoryInternal`  
`class FDisplayClusterRenderSyncPolicyFactoryInternal : public IDisplayClusterRenderSyncPolicyFactory`  
_L11-20_
- inherits: `IDisplayClusterRenderSyncPolicyFactory`
- desc: Factory for internal synchronization policies
- L15 _public prototype_ `FDisplayClusterRenderSyncPolicyFactoryInternal() = default;`
- L16 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyFactoryInternal() = default;`
- L19 _public prototype_ `virtual TSharedPtr<IDisplayClusterRenderSyncPolicy> Create(const FString& InPolicyType, const TMap<FString, FString>& Parameters) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyNone.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyNone`  
`class FDisplayClusterRenderSyncPolicyNone : public FDisplayClusterRenderSyncPolicyBase`  
_L11-28_
- inherits: `FDisplayClusterRenderSyncPolicyBase`
- desc: Synchronization policy - None (no synchronization)
- L15 _public function_ `FDisplayClusterRenderSyncPolicyNone(const TMap<FString, FString>& Parameters) : FDisplayClusterRenderSyncPolicyBase(Parameters)`
- L19 _public function_ `virtual ~FDisplayClusterRenderSyncPolicyNone()`
- L26 _public prototype_ `virtual bool SynchronizeClusterRendering(FRHIViewport* ViewportRHI, int32& InOutSyncInterval) override;`
- L27 _public prototype_ `virtual FName GetName() const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyNvidiaBase.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyNvidiaBase`  
`class FDisplayClusterRenderSyncPolicyNvidiaBase : public FDisplayClusterRenderSyncPolicyBase`  
_L20-67_
- inherits: `FDisplayClusterRenderSyncPolicyBase`
- desc: Abstract NVIDIA synchronization policy. It's used as a base class for all NVIDIA sync policies. Encapsulates common NVIDIA synchronization features.
- L24 _private typedef_ `using Super = FDisplayClusterRenderSyncPolicyBase;`
- L27 _public prototype_ `FDisplayClusterRenderSyncPolicyNvidiaBase(const TMap<FString, FString>& Parameters);`
- L28 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyNvidiaBase();`
- L34 _public prototype_ `virtual bool Initialize() override;` — Initialization
- L40 _protected member_ `bool bNvLibraryInitialized = false;` — Whether NVIDIA API library was initialized
- L43 _protected member_ `bool bNvSyncInitializationCalled = false;` — Whether NVIDIA sync initialization function was called (to prevent multiple initialization calls)
- L46 _protected member_ `bool bNvSyncInitializedSuccessfully = false;` — Whether NVIDIA sync initialization succeeded
- L50 _protected member_ `const bool bCfgPreInitAlignment;` — CVar config: synchronous initialization (alignment on a barrier before initializing NVIDIA synchronization)
- L53 _protected member_ `const float CfgPostBarrierJoinSleep;` — CVar config: Force delay after joining the barrier
- L56 _protected member_ `const int32 CfgPrePresentAlignmentLimit;` — CVar config: pre-present threads alignment on a network barrier
- L58 _protected member_ `int32 PrePresentAlignmentCounter = 0;` — Pre-present sync counter
- L61 _protected member_ `const int32 CfgFrameCompletionLimit;` — CVar config: frame completion limit
- L63 _protected member_ `int32 FrameCompletionCounter = 0;` — Frame completion counter
- L66 _protected member_ `const bool bCfgPostPresentAlignment;` — CVar config: post-present threads alignment on a network barrier

#### Free symbols / members of external scopes

- L11 _externvar_ `extern TAutoConsoleVariable<bool> CVarNvidiaSyncForceLatencyUpdateEveryFrame;` — CVars available for change in runtime
- L12 _externvar_ `extern TAutoConsoleVariable<bool> CVarNvidiaSyncPrintStatsEveryFrame;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyNvidiaPresentBarrier.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyNvidiaPresentBarrier`  
`class FDisplayClusterRenderSyncPolicyNvidiaPresentBarrier : public FDisplayClusterRenderSyncPolicyNvidiaBase`  
_L12-49_
- inherits: `FDisplayClusterRenderSyncPolicyNvidiaBase`
- desc: NVIDIA Present Barrier synchronization policy (new NVDIA sync approach)
- L16 _private typedef_ `using Super = FDisplayClusterRenderSyncPolicyNvidiaBase;`
- L19 _public prototype_ `FDisplayClusterRenderSyncPolicyNvidiaPresentBarrier(const TMap<FString, FString>& Parameters);`
- L20 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyNvidiaPresentBarrier();`
- L26 _public function_ `virtual FName GetName() const override` — Returns name of this policy implementation
- L32 _public prototype_ `virtual bool SynchronizeClusterRendering(FRHIViewport* ViewportRHI, int32& InOutSyncInterval) override;` — Performs rendering and frame output synchronization
- L38 _private prototype_ `void OnFramePresented(bool bNativePresent);` — Handles frame presentation events
- L41 _private prototype_ `void LogPresentBarrierStats();` — Prints present barrier stats to the log
- L45 _private prototype_ `bool InitializePresentBarrier(FRHIViewport* ViewportRHI);` — Initializes NVIDIA present barrier
- L48 _private member_ `TPimplPtr<FData> Data;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Synchronization/DisplayClusterRenderSyncPolicyNvidiaSwapBarrier.h` (Private)


#### class `FDisplayClusterRenderSyncPolicyNvidiaSwapBarrier`  
`class FDisplayClusterRenderSyncPolicyNvidiaSwapBarrier : public FDisplayClusterRenderSyncPolicyNvidiaBase`  
_L12-49_
- inherits: `FDisplayClusterRenderSyncPolicyNvidiaBase`
- desc: NVIDIA Swap Barrier synchronization policy (old NVDIA sync approach)
- L16 _private typedef_ `using Super = FDisplayClusterRenderSyncPolicyNvidiaBase;`
- L19 _public prototype_ `FDisplayClusterRenderSyncPolicyNvidiaSwapBarrier(const TMap<FString, FString>& Parameters);`
- L20 _public prototype_ `virtual ~FDisplayClusterRenderSyncPolicyNvidiaSwapBarrier();`
- L26 _public function_ `virtual FName GetName() const override` — Returns name of this policy implementation
- L32 _public prototype_ `virtual bool SynchronizeClusterRendering(FRHIViewport* ViewportRHI, int32& InOutSyncInterval) override;` — Performs rendering and frame output synchronization
- L38 _private prototype_ `bool InitializeNvidiaSwapLock(FRHIViewport* ViewportRHI);` — Initializes NVIDIA internals
- L42 _private member_ `uint32 RequestedGroup = 1;` — Policy config parameter: Swap group ID
- L45 _private member_ `uint32 RequestedBarrier = 1;` — Policy config parameter: Swap barrier ID
- L48 _private member_ `TPimplPtr<FData> Data;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration.h` (Private)


#### class `FDisplayClusterViewportConfiguration`  
`class FDisplayClusterViewportConfiguration : public IDisplayClusterViewportConfiguration , public TSharedFromThis<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>`  
_L26-443_
- inherits: `IDisplayClusterViewportConfiguration,TSharedFromThis<FDisplayClusterViewportConfiguration,ESPMode::ThreadSafe>`
- desc: Implementation of the viewport manager configuration.
- L31 _public prototype_ `FDisplayClusterViewportConfiguration();`
- L32 _public prototype_ `virtual ~FDisplayClusterViewportConfiguration();`
- L34 _public prototype_ `void Initialize(FDisplayClusterViewportManager& InViewportManager);`
- L38 _public function_ `virtual void SetExclusiveLockOnRootActors(const bool bLocked) override`
- L39 _public function_ `virtual bool IsRootActorLockedByThis(const ADisplayClusterRootActor* InRootActor) const override`
- L41 _public prototype_ `virtual void SetRootActor(const EDisplayClusterRootActorType InRootActorType, const ADisplayClusterRootActor* InRootActor) override;`
- L43 _public function_ `virtual void SetPreviewSettings(const FDisplayClusterViewport_PreviewSettings& InPreviewSettings) override`
- L48 _public function_ `virtual const FDisplayClusterViewport_PreviewSettings& GetPreviewSettings() const override`
- L53 _public function_ `virtual void SetExternalOverscan(bool bInEnable, const float* InOverscanOverride = nullptr) override`
- L59 _public function_ `virtual void SetRenderResolutionScale(const float InScale) override`
- L64 _public function_ `virtual bool UpdateConfigurationForClusterNode(EDisplayClusterRenderFrameMode InRenderMode, const UWorld* InWorld, const FString& InClusterNodeId, const uint32* InFrameNumberOverride = nullptr) override`
- L69 _public function_ `virtual bool UpdateConfigurationForViewportsList(EDisplayClusterRenderFrameMode InRenderMode, const UWorld* InWorld, const TArray<FString>& InViewportNames, const uint32* InFrameNumberOverride = nullptr) override`
- L74 _public prototype_ `virtual void ReleaseConfiguration() override;`
- L76 _public prototype_ `virtual UWorld* GetCurrentWorld() const override;`
- L77 _public prototype_ `virtual float GetRootActorWorldDeltaSeconds(const EDisplayClusterRootActorType InRootActorType = EDisplayClusterRootActorType::Scene) const override;`
- L78 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor(const EDisplayClusterRootActorType InRootActorType) const override;`
- L79 _public prototype_ `virtual IDisplayClusterViewportManager* GetViewportManager() const override;`
- L80 _public prototype_ `virtual const UDisplayClusterConfigurationData* GetConfigurationData() const override;`
- L81 _public prototype_ `virtual const FDisplayClusterConfigurationICVFX_StageSettings* GetStageSettings() const override;`
- L82 _public prototype_ `virtual const FDisplayClusterConfigurationRenderFrame* GetConfigurationRenderFrameSettings() const override;`
- L84 _public prototype_ `virtual EDisplayClusterRenderFrameMode GetRenderModeForPIE() const override;`
- L85 _public prototype_ `virtual bool IsCurrentWorldHasAnyType(const EWorldType::Type InWorldType1, const EWorldType::Type InWorldType2 = EWorldType::None, const EWorldType::Type InWorldType3 = EWorldType::None) const override;`
- L86 _public prototype_ `virtual bool IsRootActorWorldHasAnyType(const EDisplayClusterRootActorType InRootActorType, const EWorldType::Type InWorldType1, const EWorldType::Type InWorldType2 = EWorldType::None, const EWorldType::Type InWorldType3 = EWorldType::None) const override;`
- L88 _public function_ `virtual const IDisplayClusterViewportConfigurationProxy& GetProxy() const override`
- L93 _public function_ `virtual bool IsSceneOpened() const override`
- L98 _public function_ `virtual bool IsICVFXEnabled() const override`
- L103 _public prototype_ `virtual bool IsClusterNodeRenderingOffscreen() const override;`
- L104 _public prototype_ `virtual bool IsMediaAvailable() const override;`
- L106 _public function_ `virtual const FString& GetClusterNodeId() const override`
- L111 _public function_ `virtual bool IsPreviewRendering() const override`
- L116 _public function_ `virtual bool IsClusterRendering() const override`
- L121 _public function_ `virtual bool IsMoviePipelineRendering() const override`
- L138 _public function_ `virtual bool IsTechvisEnabled() const override`
- L143 _public function_ `virtual bool IsPreviewInGameEnabled() const override`
- L148 _public prototype_ `virtual bool IsRootActorExclusivelyLocked() const override;`
- L150 _public prototype_ `virtual const float GetWorldToMeters() const override;`
- L152 _public function_ `virtual int32 GetViewPerViewportAmount() const override`
- L173 _public prototype_ `FString BuildViewportName( const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags, const FIntPoint* InOptTilePos = nullptr);` — Builds a viewport name that is unique within the cluster. The name is composed from the current cluster node ID(from this configuration), the base viewport ID, the viewport usage type, and optionally a tile position to disambiguate tiled viewports. @param InViewportBaseId Base viewport identifier. @param InViewportFlags  Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @param InOptTilePos     Optional parameter for tile viewport position @return A viewport name string unique within the cluster.
- L186 _public prototype_ `TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> CreateProjectionPolicy_ICVFXViewport( const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags);` — Creates a projection policy instance with type "link" or "camera" for ICVFX viewport. @param InViewportBaseId The base viewport identifier (before ICVFX unique naming). @param InViewportFlags  Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @return A thread-safe shared pointer to the created projection policy.
- L199 _public prototype_ `TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> CreateProjectionPolicy_TileViewport( const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags, const FIntPoint& InTilePos);` — Creates a projection policy instance with type "link" for Tile viewport. @param InViewportBaseId The base viewport identifier (before ICVFX unique naming). @param InViewportFlags  Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @param InTilePos        Tile viewport position @return A thread-safe shared pointer to the created projection policy.
- L214 _public prototype_ `FDisplayClusterViewport* CreateViewport( const FString& InViewportBaseId, const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InProjectionPolicy, const EDisplayClusterViewportFlags InViewportFlags, const FIntPoint* InOptTilePos = nullptr);` — Creates and initializes a new nDisplay viewport. @param InViewportBaseId   The base viewport identifier (before ICVFX unique naming). @param InProjectionPolicy Projection policy assigned to the viewport @param InViewportFlags    Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @param InOptTilePos       Optional parameter for tile viewport position @return A raw pointer to the created FDisplayClusterViewport or nullptr in case of failure.
- L230 _public prototype_ `FDisplayClusterViewport* FindViewport( const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags = EDisplayClusterViewportFlags::None, const FIntPoint* InOptTilePos = nullptr) const;` — Finds a viewport instance by identifier and usage type. @param InViewportBaseId The base viewport identifier (before ICVFX unique naming). @param InViewportFlags  Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @param InOptTilePos     Optional parameter for tile viewport position @return A pointer to the matching FDisplayClusterViewport, or nullptr if no viewport matches the given criteria.
- L237 _public function_ `FDisplayClusterViewportManager* GetViewportManagerImpl() const` — Get a pointer to the DC ViewportManager if it still exists.
- L243 _public function_ `const FDisplayClusterRenderFrameSettings& GetRenderFrameSettings() const` — Gets the rendering frame settings.
- L253 _public prototype_ `bool ShouldOptimizeOutOffscreenNodeResources() const;` — Returns true if unused resources on offscreen nodes should be optimized.
- L257 _public function_ `void SetRenderFrameSettings(const FDisplayClusterRenderFrameSettings& InRenderFrameSettings)` — Sets the rendering frame settings.
- L268 _public function_ `inline bool IsCurrentRenderFrameViewportsOutOfDate() const` — Returns true if the current frame's viewport list is out of date and needs to be refreshed.
- L274 _public function_ `inline void ClearCurrentRenderFrameViewportsOutOfDate()` — Clears the stale flag, marking the current frame's viewport list as up to date.
- L280 _public function_ `inline void MarkCurrentRenderFrameViewportsOutOfDate()` — Raises the stale flag, marking the current frame's viewport list as needing an update.
- L286 _public function_ `void SetClusterNodeId(const FString& InClusterNodeId)` — Set the name of the current cluster node.
- L299 _public prototype_ `void OnHandleStartScene();`
- L300 _public prototype_ `void OnHandleEndScene();`
- L303 _public prototype_ `FString GetRootActorName() const;` — Returns the DCRA name or an empty string.
- L306 _public function_ `const TSet<FPrimitiveComponentId>& GetRootActorHidePrimitivesList() const` — Returns a list of hidden RootActor primitives.
- L320 _private prototype_ `bool ImplUpdateConfiguration( EDisplayClusterRenderFrameMode InRenderMode, const UWorld* InWorld, const FString& InClusterNodeId, const TArray<FString>* InViewportNames, const uint32* InFrameNumberOverride);` — Update configuration implementation. @param InRenderMode          - rendering mode. @param InWorld               - ptr to the world to be rendered @param InClusterNodeId       - (opt) Configuring rendering for a cluster node. @param InViewportNames       - (opt) Configuring rendering for a list of viewports. @param InFrameNumberOverride - (opt) If set, use this value instead of GFrameNumber.
- L328 _private prototype_ `void ImplUpdateConfigurationVisibility();` — Hide DCRA components for nDisplay rendering.
- L331 _private prototype_ `void SetCurrentWorldImpl(const UWorld* InWorld);` — Set current world.
- L335 _private prototype_ `TSet<ADisplayClusterRootActor*> GatherRootActorsImpl() const;` — Returns all DCRAs currently referenced by this configuration.
- L338 _private prototype_ `void UpdateExclusiveLockOnRootActorsImpl(const bool bExclusivelyLocked) const;` — Applies or releases the exclusive lock on all referenced DCRAs to match bExclusiveLockOnRootActors.
- L347 _private function_ `inline void UpdateExclusiveLockOnRootActors() const` — Applies the current lock state to any new or recreated DCRAs. Called from SetRootActor/GetRootActor so the lock follows actor recreation automatically. Re-applies if: (a) any previously locked actor's weak pointer expired (DCRA was destroyed/recreated), or (b) the gathered actor set contains an actor not present in the last locked set.
- L369 _private function_ `inline void SetExclusiveLockOnRootActorsImpl(const bool bExclusivelyLocked)` — Applies or releases the exclusive lock on all referenced root actors. No-op if the lock state is already set to the requested value. @param bExclusivelyLocked  true to acquire the exclusive lock; false to release it.
- L389 _private function_ `inline bool IsRootActorLockedByThisImpl(const ADisplayClusterRootActor* InRootActor) const` — Returns true if this configuration currently holds an exclusive lock on InRootActor. Counterpart to ADisplayClusterRootActor::IsRootActorExclusivelyLocked(), which queries all its holders. @param InRootActor  The root actor to test.
- L400 _private member_ `mutable TOptional<bool> bExclusiveLockOnRootActors;` — Desired exclusive lock state for all referenced DCRAs. Unset means SetExclusiveLockOnRootActors() has never been called; true/false is applied to each DCRA via UpdateExclusiveLockOnRootActors().
- L404 _private member_ `mutable TSet<TWeakObjectPtr<ADisplayClusterRootActor>> LockedRootActorsCache;` — Weak pointers to the DCRAs that were locked on the last UpdateExclusiveLockOnRootActorsImpl() call. An expired entry means the DCRA was destroyed and a re-lock is needed for its successor.
- L408 _public member_ `const TSharedRef<FDisplayClusterViewportConfigurationProxy, ESPMode::ThreadSafe> Proxy;` — Reference to configuration proxy object
- L412 _private member_ `uint8 bCurrentRenderFrameViewportsOutOfDate : 1 = 0;` — Whether the list of viewports of the current frame needs to be updated
- L415 _private member_ `uint8 bCurrentSceneActive : 1 = 0;` — Is current scene started
- L418 _private member_ `FDisplayClusterRenderFrameSettings RenderFrameSettings;` — Current render frame settings
- L421 _private member_ `TWeakPtr<FDisplayClusterViewportManager, ESPMode::ThreadSafe> ViewportManagerWeakPtr;` — A reference to the owning viewport manager
- L429 _private member_ `FDisplayClusterActorRef PreviewRootActorRef;` — This DCRA will be used to render previews. The meshes and preview materials are created at runtime.
- L433 _private member_ `FDisplayClusterActorRef SceneRootActorRef;` — (Optional) A reference to DCRA in the scene, used as a source for math calculations and references. Locations in the scene and math data are taken from this DCRA.
- L436 _private member_ `FDisplayClusterActorRef ConfigurationRootActorRef;` — (Optional) Reference to DCRA, used as a source of configuration data from DCRA and its components.
- L439 _private member_ `TWeakObjectPtr<UWorld> CurrentWorldRef;` — Pointer to the current world to be rendered in.
- L442 _private member_ `TSet<FPrimitiveComponentId> RootActorHidePrimitivesList;` — Additional hide primitives list from root actor

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers.h` (Private)


#### class `FDisplayClusterViewportConfigurationHelpers`  
`class FDisplayClusterViewportConfigurationHelpers`  
_L17-28_
- desc: Base configuration helper class.
- L21 _public prototype_ `static bool IsForceMonoscopicRendering(const EDisplayClusterConfigurationViewport_StereoMode StereoMode);` — Returns true if this viewport should be rendered in monoscopic mode.
- L24 _public prototype_ `static void UpdateBaseViewportSetting(FDisplayClusterViewport& DstViewport, const UDisplayClusterConfigurationViewport& InConfigurationViewport);` — Update base settings of DC viewport.
- L27 _public prototype_ `static FDisplayClusterViewport_OverscanSettings GetViewportOverscanSettings(const FDisplayClusterConfigurationViewport_Overscan& InOverscan);` — Get viewport overscan settings.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers_ICVFX.h` (Private)


#### class `FDisplayClusterViewportConfigurationHelpers_ICVFX`  
`class FDisplayClusterViewportConfigurationHelpers_ICVFX`  
_L23-77_
- desc: ICVFX configuration helper class.
- L27 _public prototype_ `static FDisplayClusterViewport* GetOrCreateCameraViewport(FDisplayClusterViewportConfiguration& InConfiguration, UDisplayClusterICVFXCameraComponent& InCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Return the new or existing InnerFrustum viewport.
- L30 _public prototype_ `static FDisplayClusterViewport* GetOrCreateChromakeyViewport(FDisplayClusterViewportConfiguration& InConfiguration, UDisplayClusterICVFXCameraComponent& InCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Return the new or existing Chromakey viewport.
- L33 _public prototype_ `static FDisplayClusterViewport* GetOrCreateLightcardViewport(FDisplayClusterViewport& BaseViewport, const bool bOverInFrustum);` — Return the new or existing LightCard viewport.
- L36 _public prototype_ `static FDisplayClusterViewport* GetOrCreateUVLightcardViewport(FDisplayClusterViewport& BaseViewport, const bool bOverInFrustum);` — Return the new or existing UVLightCard viewport.
- L42 _public prototype_ `static void ReuseUVLightCardViewportWithinClusterNode(FDisplayClusterViewport& InUVLightCardViewport, const bool bOverInFrustum);` — Because UVLightCard viewports share the same outer texture (from LightCardManager), they can clone each other. Except when the OCIO settings are not equal. This function sets the InUVLightCardViewport rendering settings to minimize rendering costs.
- L45 _public prototype_ `static TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>> GetAllVisibleInnerCameraViewports(FDisplayClusterViewportConfiguration& InConfiguration, bool bGetChromakey = false);` — Returns all visible InnerCamera viewports.
- L47 _public prototype_ `static TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>> PreviewGetRenderedInCameraViewports(FDisplayClusterViewportConfiguration& InConfiguration, const FString& InICVFXCameraId, bool bGetChromakey = false);`
- L48 _public prototype_ `static bool PreviewReuseInnerFrustumViewportWithinClusterNodes(FDisplayClusterViewport& InCameraViewport, UDisplayClusterICVFXCameraComponent& InCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L49 _public prototype_ `static bool PreviewReuseChromakeyViewportWithinClusterNodes(FDisplayClusterViewport& InChromakeyViewport, const FString& InICVFXCameraId);`
- L51 _public prototype_ `static void UpdateCameraViewportSettings(FDisplayClusterViewport& DstViewport, UDisplayClusterICVFXCameraComponent& InCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L52 _public prototype_ `static void UpdateChromakeyViewportSettings(FDisplayClusterViewport& DstViewport, FDisplayClusterViewport& InCameraViewport, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L53 _public prototype_ `static void UpdateLightcardViewportSetting(FDisplayClusterViewport& DstViewport, FDisplayClusterViewport& BaseViewport);`
- L55 _public prototype_ `static bool IsCameraUsed(const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L57 _public prototype_ `static TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> CreateProjectionPolicyCameraICVFX(FDisplayClusterViewportConfiguration& InConfiguration, UDisplayClusterICVFXCameraComponent& CameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L58 _public prototype_ `static bool UpdateCameraProjectionSettingsICVFX(FDisplayClusterViewportConfiguration& InConfiguration, UDisplayClusterICVFXCameraComponent& CameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings, const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InProjectionPolicy);`
- L61 _public prototype_ `static void UpdateCameraSettings_Chromakey( FDisplayClusterShaderParameters_ICVFX::FCameraSettings& InOutCameraSettings, const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings, const bool bEnableChromakey, const bool bEnableChromakeyMarkers, const FString& InChromakeyViewportId);` — Configures the camera's chromakey render settings to match the specified configuration settings
- L68 _public prototype_ `static void UpdateCameraSettings_OverlapChromakey(FDisplayClusterShaderParameters_ICVFX::FCameraSettings& InOutCameraSettings, const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings, bool bEnableChromakeyMarkers);`
- L70 _public prototype_ `static void UpdateCameraCustomFrustum(const FDisplayClusterConfigurationICVFX_CameraCustomFrustum& InCameraCustomFrustumConfiguration, FDisplayClusterViewport_CustomFrustumSettings& OutCustomFrustumSettings);`
- L76 _public prototype_ `static void UpdateLegacyRuntimeICVFXFlagsFromViewportFlags(FDisplayClusterViewport& InOutViewport);` — Backward-compatibility bridge: derive legacy EDisplayClusterViewportRuntimeICVFXFlags from the new EDisplayClusterViewportFlags until the legacy runtime enum is removed.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers_OpenColorIO.h` (Private)


#### class `FDisplayClusterViewportConfigurationHelpers_OpenColorIO`  
`class FDisplayClusterViewportConfigurationHelpers_OpenColorIO`  
_L16-96_
- desc: OCIO configuration helper class.
- L27 _public prototype_ `static bool UpdateBaseViewportOCIO(FDisplayClusterViewport& DstViewport, const UDisplayClusterConfigurationViewport& InViewportConfiguration);` — Update OCIO for base viewport (Outer). @param DstViewport             - Dest viewport object. @param RootActor               - DCRA object. @param InViewportConfiguration - Actual viewport configuration. @return - true if success.
- L37 _public prototype_ `static bool UpdateLightcardViewportOCIO(FDisplayClusterViewport& DstViewport, FDisplayClusterViewport& BaseViewport);` — Update OCIO for LightCard viewport. @param DstViewport  - Dest LightCard viewport object. @param BaseViewport - Base (Outer) viewport object. @param RootActor    - DCRA object. @return - true if success.
- L47 _public prototype_ `static bool UpdateCameraViewportOCIO(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Update OCIO for InnerFrustum(InCamera) viewport. @param DstViewport       - Dest InCamera viewport object @param RootActor         - DCRA object @param InCameraComponent - InCamera component with configuration @return - true if success
- L57 _public prototype_ `static bool UpdateChromakeyViewportOCIO(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Update OCIO for Chromakey viewport. @param DstViewport       - Dest InCamera viewport object @param RootActor         - DCRA object @param InCameraComponent - InCamera component with configuration @return - true if success
- L67 _public prototype_ `static bool IsInnerFrustumViewportOCIOSettingsEqual(const FDisplayClusterViewport& InViewport1, const FDisplayClusterViewport& InViewport2, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Compare InnerFrustum OCIO configuration for input viewports @param InViewport1       - Viewport #1 @param InViewport2       - Viewport #2 @param InCameraComponent - InCamera component with configuration @return - true if OCIO is equals
- L77 _public prototype_ `static bool IsChromakeyViewportOCIOSettingsEqual(const FDisplayClusterViewport& InViewport1, const FDisplayClusterViewport& InViewport2, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Compare Chromakey OCIO configuration for input viewports @param InViewport1       - Viewport #1 @param InViewport2       - Viewport #2 @param InCameraComponent - InCamera component with configuration @return - true if OCIO is equals
- L87 _private prototype_ `static void ApplyOCIOConfiguration(FDisplayClusterViewport& DstViewport, const FOpenColorIOColorConversionSettings& InConversionSettings);` — Apply OCIO to viewport. @param DstViewport       - Dest viewport object @param InConversionSettings   - OCIO conversion settings @return - none
- L95 _private prototype_ `static void DisableOCIOConfiguration(FDisplayClusterViewport& DstViewport);` — Reset OCIO for viewport. @param DstViewport       - Dest viewport object @return - none

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers_Postprocess.h` (Private)


#### class `FDisplayClusterViewportConfigurationHelpers_Postprocess`  
`class FDisplayClusterViewportConfigurationHelpers_Postprocess`  
_L25-66_
- desc: Postprocess configuration helper class.
- L28 _public prototype_ `static void UpdateCustomPostProcessSettings(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationViewport_CustomPostprocess& InCustomPostprocessConfiguration);`
- L29 _public prototype_ `static void UpdatePerViewportPostProcessSettings(FDisplayClusterViewport& DstViewport);`
- L31 _public prototype_ `static bool UpdateLightcardPostProcessSettings(FDisplayClusterViewport& DstViewport, FDisplayClusterViewport& BaseViewport);`
- L34 _public prototype_ `static bool IsInnerFrustumViewportSettingsEqual(const FDisplayClusterViewport& InViewport1, const FDisplayClusterViewport& InViewport2, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — return true when same settings used for both viewports
- L37 _public prototype_ `static void BlendPostProcessSettings(FPostProcessSettings& OutputPP, const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings& ClusterPPSettings, const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings& ViewportPPSettings);`
- L38 _public prototype_ `static void CopyPPSStructConditional(FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings* OutViewportPPSettings, FPostProcessSettings* InPPS);`
- L39 _public prototype_ `static void CopyPPSStruct(FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings* OutViewportPPSettings, FPostProcessSettings* InPPS);`
- L41 _public prototype_ `static void CopyBlendPostProcessSettings(FPostProcessSettings& OutputPP, const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings& InPPSettings);`
- L42 _public prototype_ `static void PerNodeBlendPostProcessSettings(FPostProcessSettings& OutputPP, const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings& ClusterPPSettings, const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings& ViewportPPSettings, const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings& PerNodePPSettings);`
- L46 _public prototype_ `static void ImplApplyICVFXCameraPostProcessesToViewport(FDisplayClusterViewport& DstViewport, UDisplayClusterICVFXCameraComponent& InSceneCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCfgCameraSettings, const EDisplayClusterViewportCameraPostProcessFlags InPostProcessingFlags);` — Initialize PP settings for the viewport from the ICVFX camera component.
- L51 _public prototype_ `static void FilterPostProcessSettings(FPostProcessSettings& InOutPostProcessSettings, const EDisplayClusterViewportCameraPostProcessFlags InPostProcessingFlags);` — Applies a filter to the post-processing settings. Note: If DoF is disabled in InPostProcessingFlags, this causes it to be removed from the PP settings as well.
- L54 _private prototype_ `static bool ImplUpdateInnerFrustumColorGrading(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L55 _private prototype_ `static bool ImplUpdateInnerFrustumColorGradingForOuterViewport(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);`
- L56 _private prototype_ `static bool ImplUpdateViewportColorGrading(FDisplayClusterViewport& DstViewport, const FString& InClusterViewportId);`
- L59 _private prototype_ `static FDisplayClusterViewport_CameraMotionBlur GetICVFXCameraMotionBlurParameters(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, UDisplayClusterICVFXCameraComponent& InSceneCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCfgCameraSettings);` — Gets the MotionBlur parameters of camera
- L62 _private prototype_ `static FDisplayClusterViewport_CameraDepthOfField GetICVFXCameraDepthOfFieldParameters(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, UDisplayClusterICVFXCameraComponent& InSceneCameraComponent, const FDisplayClusterConfigurationICVFX_CameraSettings& InCfgCameraSettings);` — Gets the depth of field parameters to store on the display cluster viewport
- L65 _private prototype_ `static bool ImplUpdateFinalPerViewportPostProcessList(FDisplayClusterViewport& DstViewport, const TArray<const FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings*>& InPostProcessList);` — Blend input list of postprocess and set as a FinalPerViewport.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers_RenderFrameSettings.h` (Private)


#### enum `ECVarDisplayClusterAlphaChannelCaptureMode`  
`enum class ECVarDisplayClusterAlphaChannelCaptureMode : uint8`  
_L15-50_
- desc: This enum is for CVar values only and is used to process the logic that converts the values to the runtime enum in GetAlphaChannelCaptureMode().
- L20 _public enumerator_ `Disabled` — [Disabled] Disable alpha channel saving.
- L27 _public enumerator_ `ThroughTonemapper` — [ThroughTonemapper] When rendering with the PropagateAlpha experimental mode turned on, the alpha channel is forwarded to post-processes. In this case, the alpha channel is anti-aliased along with the color. Since some post-processing may change the alpha, it is copied at the beginning of the PP and restored after all post-processing is completed.
- L35 _public enumerator_ `FXAA` — [FXAA] Otherwise, if the PropagateAlpha mode is disabled in the project settings, we need to save the alpha before it becomes invalid. The alpha is valid until the scene color is resolved (on the ResolvedSceneColor callback). Therefore, it is copied to a temporary resource on this cb. Since we need to remove AA jittering (because alpha copied before AA), anti-aliasing is turned off for this viewport. And finally the FXAA is used for smoothing.
- L41 _public enumerator_ `Copy` — [Copy] Disable AA and TAA, Copy alpha from scenecolor texture to final. These experimental (temporary) modes for the performance tests.
- L47 _public enumerator_ `CopyAA` — [CopyAA] Use AA, disable TAA, Copy alpha from scenecolor texture to final. These experimental (temporary) modes for the performance tests.
- L49 _public enumerator_ `COUNT`

#### class `FDisplayClusterViewportConfigurationHelpers_RenderFrameSettings`  
`class FDisplayClusterViewportConfigurationHelpers_RenderFrameSettings`  
_L55-65_
- desc: RenderFrameSettings configuration helper class.
- L59 _public prototype_ `static bool UpdateRenderFrameConfiguration(EDisplayClusterRenderFrameMode InRenderMode, const FString& InClusterNodeId, FDisplayClusterViewportConfiguration& InOutConfiguration);` — Update RenderFrameSettings
- L60 _public prototype_ `static void PostUpdateRenderFrameConfiguration(FDisplayClusterViewportConfiguration& InOutConfiguration);`
- L64 _private prototype_ `static EDisplayClusterRenderFrameAlphaChannelCaptureMode GetAlphaChannelCaptureMode();` — Get alpha channel capture mode (for LightCard, ChromaKey).

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers_Tile.h` (Private)


#### class `FDisplayClusterViewportConfigurationHelpers_Tile`  
`class FDisplayClusterViewportConfigurationHelpers_Tile`  
_L17-32_
- desc: Tile configuration helper class.
- L21 _public prototype_ `static FDisplayClusterViewport* GetOrCreateTileViewport(FDisplayClusterViewport& InSourceViewport, const FIntPoint& TilePos);` — Get or create a new tile viewport from source.
- L25 _public prototype_ `static void UpdateICVFXCameraViewportTileSettings(FDisplayClusterViewport& InSourceViewport, const FDisplayClusterConfigurationMediaICVFX& InCameraMediaSettings);` — Get tile settings for the camera viewport.
- L28 _public prototype_ `static FIntRect GetDestRect(const FDisplayClusterViewport_TileSettings& InTileSettings, const FIntRect& InSourceRect);` — Get a tile viewport rect inside the rect of the source viewport.
- L31 _public prototype_ `static FDisplayClusterViewport_OverscanSettings GetTileOverscanSettings(const FDisplayClusterConfigurationTile_Overscan& InTileOverscan);` — Get tile overscan settings.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationHelpers_Visibility.h` (Private)


#### class `FDisplayClusterViewportConfigurationHelpers_Visibility`  
`class FDisplayClusterViewportConfigurationHelpers_Visibility`  
_L17-37_
- desc: Visibility configuration helper class.
- L21 _public prototype_ `static void UpdateShowOnlyList_ICVFX(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationICVFX_VisibilityList& InVisibilityList, const FDisplayClusterConfigurationICVFX_CameraSettings* InCameraSettings = nullptr);` — Update ShowOnly list for 3D-LC and CK viewports
- L24 _public prototype_ `static void UpdateHideList_ICVFX(FDisplayClusterViewportConfiguration& InConfiguration, TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& DstViewports);` — Update hide lists for DstViewports (lightcards, chromakey, stage settings hide list, outer viewports hide list, etc)
- L27 _public prototype_ `static void AppendHideList_ICVFX(FDisplayClusterViewport& DstViewport, const FDisplayClusterConfigurationICVFX_VisibilityList& InHideList);` — Append to exist hide list (must be call after UpdateHideList_ICVFX)
- L33 _public prototype_ `static bool IsActorVisibleForViewport(const FDisplayClusterViewport& InViewport, AActor& InActor);` — Returns true if this actor can be rendered for the viewport. For Example: The LightCard actor has a property that determines which of the two LightCard viewports it should be rendered in.
- L36 _public prototype_ `static bool IsLightcardViewportRenderable(const FDisplayClusterViewport& InViewport, const EDisplayClusterConfigurationICVFX_PerLightcardRenderMode PerLightcardRenderMode = EDisplayClusterConfigurationICVFX_PerLightcardRenderMode::Default);` — Returns true if the viewport is of type lightcard and can be rendered.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfigurationProxy.h` (Private)


#### class `FDisplayClusterViewportConfigurationProxy`  
`class FDisplayClusterViewportConfigurationProxy : public IDisplayClusterViewportConfigurationProxy , public TSharedFromThis<FDisplayClusterViewportConfigurationProxy, ESPMode::ThreadSafe>`  
_L13-82_
- inherits: `IDisplayClusterViewportConfigurationProxy,TSharedFromThis<FDisplayClusterViewportConfigurationProxy,ESPMode::ThreadSafe>`
- desc: Implementation of the IDisplayClusterViewportConfigurationProxy
- L18 _public prototype_ `FDisplayClusterViewportConfigurationProxy() = default;`
- L19 _public prototype_ `virtual ~FDisplayClusterViewportConfigurationProxy() = default;`
- L23 _public prototype_ `virtual IDisplayClusterViewportManagerProxy* GetViewportManagerProxy_RenderThread() const override;`
- L25 _public function_ `virtual bool IsPreviewRendering_RenderThread() const override`
- L32 _public function_ `virtual bool IsICVFXEnabled_RenderThread() const override`
- L39 _public function_ `virtual EDisplayClusterRenderFrameMode GetRenderMode_RenderThread() const override`
- L46 _public function_ `virtual const FString& GetClusterNodeId_RenderThread() const override`
- L56 _public function_ `void Initialize_GameThread(const TSharedPtr<FDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe>& InViewportManagerProxy)` — One-time callable initializer.
- L62 _public prototype_ `void UpdateConfigurationProxy_GameThread(const class FDisplayClusterViewportConfiguration& InConfiguration);` — Send data to proxy object on rendering thread.
- L65 _public function_ `FDisplayClusterViewportManagerProxy* GetViewportManagerProxyImpl() const` — Get a pointer to the DC ViewportManagerProxy if it still exists.
- L71 _public function_ `const FDisplayClusterRenderFrameSettings& GetRenderFrameSettings() const` — Get render frame settings.
- L78 _private member_ `TWeakPtr<FDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ViewportManagerProxyWeakPtr;` — A reference to the owning viewport manager proxy
- L81 _private member_ `FDisplayClusterRenderFrameSettings RenderFrameSettings;` — The render frame settings (Copy from game thread)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_ICVFX.h` (Private)


#### class `FDisplayClusterViewportConfiguration_ICVFX`  
`class FDisplayClusterViewportConfiguration_ICVFX`  
_L12-60_
- desc: A helper class that configure ICVFX.
- L15 _public function_ `FDisplayClusterViewportConfiguration_ICVFX(FDisplayClusterViewportConfiguration& InConfiguration) : Configuration(InConfiguration)`
- L19 _public prototype_ `~FDisplayClusterViewportConfiguration_ICVFX() = default;`
- L23 _public prototype_ `void Update();` — Update ICVFX viewports for a new frame.
- L26 _public prototype_ `void PostUpdate();` — Post-Update ICVFX viewports for a new frame.
- L30 _private prototype_ `void GetAndUpdateStageCameras(const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>* InTargetViewports = nullptr);` — Get and Update stage cameras.
- L33 _private prototype_ `void ImplBeginReallocateViewports();` — Mark all ICVFX viewports as unused before upgrading.
- L36 _private prototype_ `void ImplFinishReallocateViewports();` — Delete unused ICVFX viewports.
- L39 _private prototype_ `bool ImplGetStageCameras();` — Search for ICVFX cameras inside DCRA and populate the StageCameras variable.
- L43 _private prototype_ `bool ImplGetTargetViewports(TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& OutTargets, EDisplayClusterViewportICVFXFlags& OutMergedICVFXFlags);` — Searches for OuterViewports within DCRA and returns them to the OutTargets variable.
- L46 _private prototype_ `bool CreateLightcardViewport(FDisplayClusterViewport& BaseViewport, const bool bOverInFrustum);` — Create a LightCard viewport for the  BaseViewport.
- L49 _private prototype_ `bool CreateUVLightcardViewport(FDisplayClusterViewport& BaseViewport, const bool bOverInFrustum);` — Create an UVLightCard viewport for the BaseViewport.
- L52 _private prototype_ `void ImplUpdateVisibility();` — Update a visibility for the ICVFX viewports and cameras.
- L56 _private member_ `FDisplayClusterViewportConfiguration& Configuration;` — Viewport configuration API
- L59 _private member_ `TArray<FDisplayClusterViewportConfiguration_ICVFXCamera> StageCameras;` — ICVFX cameras

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_ICVFXCamera.h` (Private)


#### class `FDisplayClusterViewportConfiguration_ICVFXCamera`  
`class FDisplayClusterViewportConfiguration_ICVFXCamera`  
_L15-102_
- desc: ICVFX Configurator: InCamera instance
- L18 _public function_ `FDisplayClusterViewportConfiguration_ICVFXCamera(FDisplayClusterViewportConfiguration& InConfiguration, UDisplayClusterICVFXCameraComponent& InCameraComponent, UDisplayClusterICVFXCameraComponent& InConfigurationCameraComponent) : Configuration(InConfiguration), CameraComponent(InCameraComponent), ConfigurationCameraComponent(InConfigurationCameraComponent)`
- L23 _public prototype_ `bool Initialize();` — Initialize CameraContext.
- L26 _public prototype_ `void Update();` — Creates camera and chromakey viewports and initializes their target OuterViewports.
- L29 _public prototype_ `bool IsCameraProjectionVisibleOnViewport(FDisplayClusterViewport* TargetViewport);` — Returns true if the camera frustum is visible on the TargetViewport geometry.
- L32 _public prototype_ `const FDisplayClusterConfigurationICVFX_CameraSettings& GetCameraSettings() const;` — Gets a ICVFX camera settings.
- L35 _public prototype_ `FString GetCameraUniqueId() const;` — Gets the name of the ICVFX camera.
- L43 _public prototype_ `bool HasAnyMediaBindings() const;` — Returns true if this camera has media bindings (assigned to a media input or output). Note: Media is available only in cluster mode.
- L47 _protected prototype_ `bool GetOrCreateAndSetupInnerCameraViewport();` — Gets or creates an In-Camera viewport and configures it for use in the ICVFX rendering stack.
- L50 _protected prototype_ `bool UpdateChromakeyViewport();` — Updates the Chromakey viewport and configures it for use in the ICVFX rendering stack.
- L58 _protected prototype_ `void UpdateICVFXSettingsForTargetViewports();` — Updates ICVFX settings for all target viewports. Applies the necessary ICVFX configuration (e.g., In-Camera, Chromakey, and related parameters) so that target viewports are correctly prepared for the ICVFX rendering stack.
- L70 _public member_ `FICVFXCameraContext CameraContext;` — Camera context, used for visibility test vs outer
- L73 _public member_ `TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe> CameraViewport;` — The inner camera viewport ref
- L76 _public member_ `TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe> ChromakeyViewport;` — The inner camera chromakey viewport ref
- L92 _public member_ `TArray<FTargetViewport> TargetViewports;` — List of OuterViewports for this camera
- L95 _private member_ `FDisplayClusterViewportConfiguration& Configuration;`
- L98 _private member_ `UDisplayClusterICVFXCameraComponent& CameraComponent;` — Camera component in scene DCRA
- L101 _private member_ `UDisplayClusterICVFXCameraComponent& ConfigurationCameraComponent;` — Camera component in configuration DCRA

#### struct `FDisplayClusterViewportConfiguration_ICVFXCamera::FICVFXCameraContext`  
`struct FICVFXCameraContext`  
_L61-67_
- L64 _public member_ `FRotator ViewRotation;` — @todo: add stereo context support
- L65 _public member_ `FVector ViewLocation;`
- L66 _public member_ `FMatrix PrjMatrix;`

#### struct `FDisplayClusterViewportConfiguration_ICVFXCamera::FTargetViewport`  
`struct FTargetViewport`  
_L78-89_
- L80 _public function_ `FTargetViewport(const TSharedRef<FDisplayClusterViewport, ESPMode::ThreadSafe>& InViewport) : Viewport(InViewport)`
- L85 _public member_ `const TSharedRef<FDisplayClusterViewport, ESPMode::ThreadSafe> Viewport;` — The reference to the viewport
- L88 _public member_ `EDisplayClusterShaderParametersICVFX_ChromakeySource ChromakeySource = EDisplayClusterShaderParametersICVFX_ChromakeySource::Disabled;` — The camera chromakey type from this viewport.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_Postprocess.h` (Private)


#### struct `FDisplayClusterViewportConfiguration_Postprocess`  
`struct FDisplayClusterViewportConfiguration_Postprocess`  
_L11-53_
- desc: A helper class that configure postprocess.
- L14 _public function_ `FDisplayClusterViewportConfiguration_Postprocess(FDisplayClusterViewportConfiguration& InConfiguration) : Configuration(InConfiguration)`
- L23 _public prototype_ `void UpdateClusterNodePostProcess(const FString& ClusterNodeId);` — Update postprocess for cluster node. @param ClusterNodeId - cluster node name (special names are supported)
- L34 _protected prototype_ `void AddInternalPostprocess(const FString& InPostprocessName);` — By default, all postprocess parameters are defined in the FDisplayClusterConfigurationPostprocess structure. But some post-processes may use their own logic to enable or disable. For example, TextureSharePP will only be enabled with a special condition: 1. The EnableTextureShare checkbox is checked in the cluster node settings 2. The TextureShare plugin is enabled for this project.
- L38 _private member_ `FDisplayClusterViewportConfiguration& Configuration;` — The configuration api
- L47 _private member_ `static TArray<FString> DisabledPostprocessNames;` — The PP is updated from the configuration every frame. If the post process name is unknown or initialization fails, an error message appears in the log. To prevent duplicate log error messages in subsequent frames, this PP name is added to the DisabledPostprocessNames list. All PPs with names from this list will be ignored.
- L52 _private member_ `TArray<FString> InternalPostprocessNames;` — This post-processing list is updated at runtime. See AddInternalPostprocess()

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_ProjectionPolicy.h` (Private)


#### struct `FDisplayClusterViewportConfiguration_ProjectionPolicy`  
`struct FDisplayClusterViewportConfiguration_ProjectionPolicy`  
_L13-57_
- desc: A helper class that configure projection policyes for viewports.
- L16 _public function_ `FDisplayClusterViewportConfiguration_ProjectionPolicy(FDisplayClusterViewportConfiguration& InConfiguration) : Configuration(InConfiguration)`
- L24 _public prototype_ `void Update();` — Special logic to additionally perform some updates within projection policies. Currently, only the advanced logic for the "camera" projection policy is implemented.
- L28 _private prototype_ `bool UpdateCameraPolicy(FDisplayClusterViewport& DstViewport);` — Basic implementation of extended logic for projection policy "camera
- L39 _private prototype_ `bool UpdateCameraPolicyForCameraComponent(FDisplayClusterViewport& DstViewport, const FString& CameraComponentId);` — Updates the projection policy of a regular (outer) viewport using settings from the specified CameraComponent. @param DstViewport       The outer (regular) viewport to update. @param CameraComponentId The identifier of the CameraComponent whose settings will be applied. @return true if the camera policy was successfully updated, false otherwise.
- L53 _private prototype_ `bool UpdateCameraPolicyForICVFXCameraComponent(FDisplayClusterViewport& DstViewport, const FString& ICVFXCameraComponentId);` — Updates the projection policy of a regular (outer) viewport using settings from the specified ICVFX CameraComponent. This is used when the input viewport has the 'camera' projection policy and must be configured to match the ICVFX camera component. @param DstViewport              The outer (regular) viewport to update. @param ICVFXCameraComponentId   The identifier of the ICVFX CameraComponent whose settings will be applied. @return true if the projection policy was successfully updated, false otherwise.
- L56 _private member_ `FDisplayClusterViewportConfiguration& Configuration;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_Tile.h` (Private)


#### class `FDisplayClusterViewportConfiguration_Tile`  
`class FDisplayClusterViewportConfiguration_Tile`  
_L13-36_
- desc: A helper class that configure Tile render.
- L16 _public function_ `FDisplayClusterViewportConfiguration_Tile(const FDisplayClusterViewportConfiguration& InConfiguration) : Configuration(InConfiguration)`
- L20 _public prototype_ `~FDisplayClusterViewportConfiguration_Tile() = default;`
- L24 _public prototype_ `void Update();` — Update Tile viewports for a new frame.
- L28 _private prototype_ `void ImplBeginReallocateViewports() const;` — Mark all Tile viewports as unused before updating.
- L31 _private prototype_ `void ImplFinishReallocateViewports() const;` — Delete unused Tile viewports.
- L35 _private member_ `const FDisplayClusterViewportConfiguration& Configuration;` — Viewport configuration API

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_Viewport.h` (Private)


#### struct `FDisplayClusterViewportConfiguration_Viewport`  
`struct FDisplayClusterViewportConfiguration_Viewport`  
_L19-60_
- desc: Container with information related to viewport: configuration and references to some class instances.
- L21 _public function_ `FDisplayClusterViewportConfiguration_Viewport(const FString& InClusterNodeId, const FString& InViewportId, const UDisplayClusterConfigurationViewport& InConfigurationViewport) : ClusterNodeId(InClusterNodeId) , ViewportId(InViewportId) , ConfigurationViewport(InConfigurationViewport)`
- L30 _public prototype_ `void CreateOrUpdateViewportInstance(FDisplayClusterViewportConfiguration& InOutConfiguration);` — Create or update DC viewport instance from configuration
- L33 _public prototype_ `void PostUpdateViewportInstance(FDisplayClusterViewportConfiguration& InOutConfiguration);` — Post update viewport.
- L38 _public prototype_ `static bool UpdateViewportConfiguration(FDisplayClusterViewport& DstViewport, const UDisplayClusterConfigurationViewport& InConfigurationViewport);` — Update exists viewport runtime settings from configuration
- L43 _public prototype_ `static void SetViewportWarpPolicy(const TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>& InViewport, IDisplayClusterWarpPolicy* InWarpPolicy);` — Assign warp policy instance to given viewport
- L47 _public member_ `const FString& ClusterNodeId;` — Cluster name, who own this viewport
- L50 _public member_ `const FString& ViewportId;` — Viewport unique name
- L53 _public member_ `const UDisplayClusterConfigurationViewport& ConfigurationViewport;` — Reference to the configuration used to create or update the viewport instance
- L56 _public member_ `TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe> Viewport;` — The viewport instance
- L59 _public member_ `UDisplayClusterCameraComponent* ViewPointCameraComponent = nullptr;` — Pointer to the view point component, used by this viewport instance.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Configuration/DisplayClusterViewportConfiguration_ViewportManager.h` (Private)


#### struct `FDisplayClusterViewportConfiguration_ViewportManager`  
`struct FDisplayClusterViewportConfiguration_ViewportManager`  
_L12-57_
- desc: A helper class that creates/updates/deletes viewports for the current rendering frame.
- L15 _public function_ `FDisplayClusterViewportConfiguration_ViewportManager(FDisplayClusterViewportConfiguration& InConfiguration) : Configuration(InConfiguration)`
- L24 _public prototype_ `void UpdateClusterNodeViewports(const FString& ClusterNodeId);` — Updates the list of viewports for the specified cluster node name, using ConfigurationData. @param ClusterNodeId - cluster node name (special names are supported)
- L30 _public prototype_ `void UpdateCustomViewports(const TArray<FString>& InViewportNames);` — Updates only the viewports for the specified list with the names of the viewports using ConfigurationData. @param InViewportNames - a list of viewport names to create or update.
- L34 _private prototype_ `void ImplUpdateViewports();` — Update viewports instances in ViewportManager.
- L37 _private prototype_ `void ImplUpdateViewportsWarpPolicy();` — Update all viewports warp policies.
- L40 _private prototype_ `void ImplInitializeEntireClusterViewportsList();` — Initialize variable EntireClusterViewports from configuration.
- L43 _private prototype_ `FDisplayClusterViewportConfiguration_Viewport const* ImplFindViewportInEntireCluster(const FString& InViewportId) const;` — Find the data of the viewport instance by name in the entire cluster.
- L46 _private prototype_ `FDisplayClusterViewportConfiguration_Viewport const* ImplFindCurrentFrameViewports(const FString& InViewportId) const;` — Find the viewport instance data by name in the current rendering frame.
- L50 _private member_ `FDisplayClusterViewportConfiguration& Configuration;` — The configuration api
- L53 _private member_ `TArray<FDisplayClusterViewportConfiguration_Viewport> EntireClusterViewports;` — The entire cluster viewports
- L56 _private member_ `TArray<FDisplayClusterViewportConfiguration_Viewport> CurrentFrameViewports;` — the viewports of the current rendering frame (determined from the cluster node name or from the user's list of viewport names)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewportPreview_InternalEnums.h` (Private)


#### enum `EDisplayClusterViewportPreviewShowLogMsgOnce`  
`enum class EDisplayClusterViewportPreviewShowLogMsgOnce : uint8`  
_L11-20_
- L13 _public enumerator_ `None = 0`
- L16 _public enumerator_ `CalculateViewIsFailed = 1 << 0` — When CalculateStereoViewOffset() function has an error
- L18 _public enumerator_ `StereoProjectionMatrixIsInvalid = 1 << 1`

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportPreviewShowLogMsgOnce);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewportProxyData.h` (Private)


#### class `FDisplayClusterViewportProxyData`  
`class FDisplayClusterViewportProxyData`  
_L26-66_
- desc: Container for data exchange game->render threads
- L29 _public function_ `FDisplayClusterViewportProxyData(const TSharedRef<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>& InDestViewportProxy) : DestViewportProxy(InDestViewportProxy)`
- L32 _public prototype_ `~FDisplayClusterViewportProxyData() = default;`
- L36 _public member_ `const TSharedRef<FDisplayClusterViewportProxy, ESPMode::ThreadSafe> DestViewportProxy;` — Dest viewport proxy
- L40 _public member_ `TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> RemapMesh;`
- L42 _public member_ `FDisplayClusterViewport_OverscanRuntimeSettings OverscanRuntimeSettings;`
- L45 _public member_ `FDisplayClusterViewport_RenderSettings RenderSettings;` — Viewport render params
- L46 _public member_ `FDisplayClusterViewport_RenderSettingsICVFX RenderSettingsICVFX;`
- L47 _public member_ `FDisplayClusterViewport_PostRenderSettings PostRenderSettings;`
- L50 _public member_ `TSharedPtr<FDisplayClusterViewport_OpenColorIO, ESPMode::ThreadSafe> OpenColorIO;` — OpenColorIO
- L53 _public member_ `TSharedPtr<IDisplayClusterDisplayDeviceProxy, ESPMode::ThreadSafe> DisplayDeviceProxy;` — Display Device
- L56 _public member_ `TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> ProjectionPolicy;` — Projection policy instance that serves this viewport
- L59 _public member_ `FDisplayClusterViewportFrameData CurrentFrameData;` — Frame data snapshot for the current frame (contexts, cached view info).
- L62 _public member_ `FDisplayClusterViewportResources Resources;` — Unified repository of viewport resources
- L65 _public member_ `TArray<TSharedPtr<FSceneViewStateReference, ESPMode::ThreadSafe>> ViewStates;` — Used ViewStates

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewportRemap.h` (Private)


#### class `FDisplayClusterViewportRemap`  
`class FDisplayClusterViewportRemap`  
_L15-68_
- desc: Helper class that computes the render geometry needed to display a viewport's output remapping
- L24 _public prototype_ `bool UpdateViewportRemap(const FDisplayClusterViewport& InViewport, const FDisplayClusterConfigurationViewport_Remap& InRemapConfiguration);` — Updates the configuration to match the specified viewport's output remapping configuration @param InViewport - The viewport whose remapping configuration is being updated @param InRemapConfiguration - The remapping configuration to update to @returns true if the render geometry needs updating after the configuration has been updated; otherwise, false
- L27 _public prototype_ `TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> GetRemapMesh() const;` — Gets a pointer to the mesh geometry to use for rendering the remapped regions
- L30 _public function_ `bool IsUsed() const` — Gets whether there are any remapped regions to render
- L37 _public prototype_ `void Update(const FDisplayClusterViewport& InViewport, const FIntPoint& InRenderFrameSize);` — Updates the render geometry used to render the remapped regions for the specified viewport @param InViewport - The viewport whose remapping configuration is being updated @param InRenderFrameSize - The size of the render frame the viewports are being rendered to
- L41 _protected prototype_ `void Empty();` — Empies all configured remapping regions and resets the mesh geometry
- L45 _private prototype_ `void ImplUpdateRemapMesh(const FDisplayClusterViewport& InViewport);` — Updates the mesh used to render the remapped regions of the specified viewport
- L48 _private prototype_ `bool ImplBuildGeometry(FDisplayClusterRender_MeshGeometry& OutGeometry) const;` — Builds the mesh geometry needed to display the remapped regions
- L51 _private prototype_ `FDisplayClusterViewportRemapData CreateRemapData(const FDisplayClusterConfigurationViewport_RemapData& CfgRemapData) const;` — Creates a data structure to store a remapped region from the configuration data structure
- L55 _private member_ `TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> RemapMesh;` — The mesh used to render the remapped regions
- L58 _private member_ `TArray<FDisplayClusterViewportRemapData> RemapRegions;` — A list of all the remapped regions to render
- L61 _private member_ `FIntRect ViewportRegion;` — The native size of the viewport whose remapped regions are being managed
- L64 _private member_ `FIntPoint RenderFrameSize;` — The size of the render frame the viewports are being rendered to
- L67 _private member_ `bool bIsNeedUpdateRemapMesh = false;` — Indicates if the mesh needs to be updated in the next update pass

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewportRemapData.h` (Private)


#### struct `FDisplayClusterViewportRemapData`  
`struct FDisplayClusterViewportRemapData`  
_L7-37_
- L10 _public member_ `FIntRect SrcRect;` — The viewport source region.
- L13 _public member_ `bool bSrcFlipH = false;` — flip source region horizontal
- L16 _public member_ `bool bSrcFlipV = false;` — flip source region vertical
- L19 _public member_ `FIntRect DstRect;` — The backbuffer destination region
- L22 _public member_ `float DstAngle = 0;` — Rotate angle in degree, Rotate origin is center of DstRect
- L24 _public function_ `FORCEINLINE bool operator==(const FDisplayClusterViewportRemapData& In) const`
- L33 _public function_ `FORCEINLINE bool operator!=(const FDisplayClusterViewportRemapData& In) const`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewport_CustomFrustumRuntimeSettings.h` (Private)


#### struct `FDisplayClusterViewport_CustomFrustumRuntimeSettings`  
`struct FDisplayClusterViewport_CustomFrustumRuntimeSettings`  
_L11-101_
- desc: Runtime custom frustum settings
- L22 _public prototype_ `static void UpdateCustomFrustumSettings( const FString& InViewportId, const FDisplayClusterViewport_CustomFrustumSettings& InCustomFrustumSettings, FDisplayClusterViewport_CustomFrustumRuntimeSettings& InOutRuntimeSettings, FIntRect& InOutRenderTargetRect, const TCHAR* InCustomResourceName = nullptr);` — Update custom frustum settings @param InViewportId            - owner viewport name @param InCustomFrustumSettings - CustomFrustum settings @param InOutRuntimeSettings    - CustomFrustum runtime settings. @param InOutRenderTargetRect   - Viewport rect, changeable during CustomFrustum @param InCustomResourceName    - (opt) The unique resource name used for log messages. Use a new custom resource name for each new location from which this function is called.
- L37 _public prototype_ `static bool UpdateProjectionAngles( const FDisplayClusterViewport_CustomFrustumRuntimeSettings& InCustomFrustumSettings, double& InOutLeft, double& InOutRight, double& InOutTop, double& InOutBottom);` — Update projection angles by custom frustum @param InCustomFrustumSettings   - the CustomFrustum runtime settings. @param InOutLeft                 - the value of the left projection plane that you want to change @param InOutRight                - the value of the right projection plane that you want to change @param InOutTop                  - the value of the top projection plane that you want to change @param InOutBottom               - the value of the bottom projection plane that you want to change
- L94 _public member_ `bool bIsEnabled = false;` — Enable custom frustum
- L97 _public member_ `FCustomFrustumPercent CustomFrustumPercent;` — CustomFrustum sides in percent
- L100 _public member_ `FCustomFrustumPixels CustomFrustumPixels;` — CustomFrustum sides in pixels

#### struct `FDisplayClusterViewport_CustomFrustumRuntimeSettings::FCustomFrustumPercent`  
`struct FCustomFrustumPercent : public FMarginSet`  
_L53-71_
- inherits: `FMarginSet`
- desc: These are frustum modifiers, where 1 means 100% of the frustum size. Positive values mean frustum expansion: FrustumAngles.Left   -= FrustumAngles.Width * Left. FrustumAngles.Right  += FrustumAngles.Width * Right. FrustumAngles.Top    += FrustumAngles.Height * Top. FrustumAngles.Bottom -= FrustumAngles.Height * Bottom.
- L57 _public function_ `inline double GetAspectRatioMult() const` — Returns the aspect ratio multiplier.

#### struct `FDisplayClusterViewport_CustomFrustumRuntimeSettings::FCustomFrustumPixels`  
`struct FCustomFrustumPixels : public FIntMarginSet`  
_L76-91_
- inherits: `FIntMarginSet`
- desc: Values in pixels
- L79 _public function_ `inline FIntRect GetInnerRect(const FIntRect& InRect) const`
- L87 _public function_ `inline FIntPoint Size() const`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewport_InternalEnums.h` (Private)


#### enum `EDisplayClusterViewportShowLogMsgOnce`  
`enum class EDisplayClusterViewportShowLogMsgOnce : uint16`  
_L10-34_
- desc: Special flags for nDisplay viewport log
- L12 _public enumerator_ `None = 0`
- L15 _public enumerator_ `HandleStartScene_InvalidProjectionPolicy = 1 << 0` — No projection policy assigned for Viewports
- L17 _public enumerator_ `UpdateFrameContexts_FrameTargetRectHasZeroSize = 1 << 1`
- L18 _public enumerator_ `UpdateFrameContexts_RenderTargetRectHasZeroSize = 1 << 2`
- L19 _public enumerator_ `UpdateFrameContexts_TileSizeNotEqualContextSize = 1 << 3`
- L20 _public enumerator_ `UpdateFrameContexts =UpdateFrameContexts_FrameTargetRectHasZeroSize | UpdateFrameContexts_RenderTargetRectHasZeroSize | UpdateFrameContexts_TileSizeNotEqualContextSize`
- L24 _public enumerator_ `UpdateCameraPolicy_ReferencedCameraNameIsEmpty = 1 << 7`
- L25 _public enumerator_ `UpdateCameraPolicy_ReferencedCameraNotFound = 1 << 8`
- L26 _public enumerator_ `UpdateCameraPolicy = UpdateCameraPolicy_ReferencedCameraNameIsEmpty | UpdateCameraPolicy_ReferencedCameraNotFound`
- L28 _public enumerator_ `GetViewPointCameraComponent_NoRootActorFound = 1 << 9`
- L29 _public enumerator_ `GetViewPointCameraComponent_HasAssignedViewPoint = 1 << 10`
- L30 _public enumerator_ `GetViewPointCameraComponent_NotFound = 1 << 11`
- L31 _public enumerator_ `GetViewPointCameraComponent = GetViewPointCameraComponent_NoRootActorFound | GetViewPointCameraComponent_NotFound`
- L33 _public enumerator_ `ChromakeyViewportHasZeroSize = 1 << 15`

#### Free symbols / members of external scopes

- L35 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportShowLogMsgOnce);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/DisplayClusterViewport_OverscanRuntimeSettings.h` (Private)


#### struct `FDisplayClusterViewport_OverscanRuntimeSettings`  
`struct FDisplayClusterViewport_OverscanRuntimeSettings : public FMarginSet`  
_L13-82_
- inherits: `FMarginSet`
- desc: Runtime overscan settings
- L22 _public prototype_ `static void UpdateOverscanSettings(const FString& InViewportId, const FDisplayClusterViewport_OverscanSettings& InOverscanSettings, FDisplayClusterViewport_OverscanRuntimeSettings& InOutOverscanRuntimeSettings, FIntRect& InOutRenderTargetRect);` — Update overscan settings @param InViewport            - owner viewport @param InOutRuntimeSettings  - the overscan runtime settings. @param InOutRenderTargetRect - Viewport rect, changeable during overscanning
- L32 _public prototype_ `static bool UpdateProjectionAngles(const FDisplayClusterViewport_OverscanRuntimeSettings& InOverscanRuntimeSettings, double& InOutLeft, double& InOutRight, double& InOutTop, double& InOutBottom);` — Update projection angles by overscan @param InOverscanRuntimeSettings - the overscan runtime settings. @param InOutLeft                 - the value of the left projection plane that you want to change @param InOutRight                - the value of the right projection plane that you want to change @param InOutTop                  - the value of the top projection plane that you want to change @param InOutBottom               - the value of the bottom projection plane that you want to change
- L63 _public member_ `uint8 bIsEnabled : 1 = 0;` — Enable overscan
- L66 _public member_ `uint8 bOversize : 1 = 0;` — Set to True to render at the overscan resolution, set to false to render at the resolution in the configuration and scale for overscan
- L71 _public member_ `FMarginSet OverscanPercent;` — Overscan size per side, expressed as a percentage of the viewport size. 0.0 = no overscan, 1.0 = 100% overscan (equal to the full viewport dimension).
- L75 _public member_ `FOverscanPixels OverscanPixels;` — Overscan size per side (in pixels) after applying resolution adjustments to match the overscan settings. See bOversize for details on how resolution adjustments are applied.
- L81 _public member_ `FOverscanPixels BaseOverscanPixels;` — Original overscan size per side (in pixels) before any resolution adjustments.

#### struct `FDisplayClusterViewport_OverscanRuntimeSettings::FOverscanPixels`  
`struct FOverscanPixels : public FIntMarginSet`  
_L44-59_
- inherits: `FIntMarginSet`
- desc: Overscan values in pixels: +--------------------------+ |           Top            | |        +-------+         | |   Left |       |  Right  | |        +-------+         | |         Bottom           | +--------------------------+
- L47 _public function_ `inline FIntRect GetInnerRect(const FIntRect& InRect) const`
- L55 _public function_ `inline FIntPoint Size() const`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Containers/ImplDisplayClusterViewport_CameraMotionBlur.h` (Private)


#### class `FImplDisplayClusterViewport_CameraMotionBlur`  
`class FImplDisplayClusterViewport_CameraMotionBlur`  
_L11-86_
- L14 _public function_ `inline void SetupSceneView(const FDisplayClusterViewport_Context& ViewportContext, FSceneView& InOutView) const`
- L76 _public function_ `void BeginUpdateSettings()`
- L82 _public member_ `FDisplayClusterViewport_CameraMotionBlur BlurSetup;`
- L85 _private member_ `mutable TArray<FViewMatrices> CameraMatrices;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewport.h` (Private)


#### class `FDisplayClusterViewport`  
`class FDisplayClusterViewport : public IDisplayClusterViewport , public TSharedFromThis<FDisplayClusterViewport, ESPMode::ThreadSafe>`  
_L38-611_
- inherits: `IDisplayClusterViewport,TSharedFromThis<FDisplayClusterViewport,ESPMode::ThreadSafe>`
- desc: Rendering viewport (sub-region of the main viewport)
- L53 _public prototype_ `FDisplayClusterViewport( const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration, const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags, const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InProjectionPolicy, const FIntPoint* InOptTilePos = nullptr);` — Constructs a new nDisplay viewport. @param InConfiguration      Viewport configuration object (thread-safe). @param InViewportBaseId     The base viewport identifier (before ICVFX unique naming). @param InViewportFlags      Usage type of the viewport (e.g. InCamera, Chromakey, LightCard). @param InProjectionPolicy   Projection policy assigned to the viewport (defines how the scene is projected/rendered). @param InOptTilePos         Optional parameter for tile viewport position
- L60 _public prototype_ `virtual ~FDisplayClusterViewport();`
- L66 _public function_ `virtual TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedPtr() override`
- L71 _public function_ `virtual TSharedPtr<const IDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L76 _public function_ `virtual TSharedRef<class FDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedRef() override`
- L81 _public function_ `virtual TSharedRef<const class FDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedRef() const override`
- L86 _public function_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() override`
- L91 _public function_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const override`
- L96 _public function_ `virtual const TSharedRef<IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() override`
- L100 _public function_ `virtual const TSharedRef<const IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() const override`
- L106 _public prototype_ `virtual IDisplayClusterViewportPreview& GetViewportPreview() const override;` — Get viewport preview API
- L107 _public prototype_ `virtual TSharedRef<IDisplayClusterViewportProxy, ESPMode::ThreadSafe> GetViewportProxy() const override;`
- L109 _public function_ `virtual EDisplayClusterViewportFlags GetViewportFlags() const override`
- L114 _public function_ `virtual FString GetBaseId() const override`
- L119 _public function_ `virtual FString GetId() const override`
- L124 _public function_ `virtual FString GetClusterNodeId() const override`
- L129 _public function_ `virtual const FDisplayClusterViewport_RenderSettings& GetRenderSettings() const override`
- L135 _public function_ `virtual void SetRenderSettings(const FDisplayClusterViewport_RenderSettings& InRenderSettings) override`
- L141 _public function_ `virtual void SetContexts(TArray<FDisplayClusterViewport_Context>& InContexts) override`
- L148 _public prototype_ `virtual FVector2D GetClippingPlanes() const override;`
- L151 _public prototype_ `virtual bool GetOCIOConversionSettings(FOpenColorIOColorConversionSettings& OutOCIOConversionSettings) const override;` — Provides current OCIO settings
- L153 _public prototype_ `virtual void CalculateProjectionMatrix(const uint32 InContextNum, float Left, float Right, float Top, float Bottom, float ZNear, float ZFar, bool bIsAnglesInput) override;`
- L155 _public prototype_ `virtual bool CalculateView(const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const float WorldToMeters) override;`
- L156 _public prototype_ `virtual bool GetProjectionMatrix(const uint32 InContextNum, FMatrix& OutPrjMatrix) override;`
- L158 _public prototype_ `virtual bool CalculateViewData(const uint32 InContextNum, const FVector& InViewLocation, const FRotator& InViewRotation, const float WorldToMeters) override;`
- L160 _public prototype_ `virtual bool SetupViewPoint(const uint32 InContextNum, FMinimalViewInfo& InOutViewInfo) override;`
- L161 _public prototype_ `virtual float GetStereoEyeOffsetDistance(const uint32 InContextNum) override;`
- L162 _public prototype_ `virtual class UDisplayClusterCameraComponent* GetViewPointCameraComponent(const EDisplayClusterRootActorType InRootActorType) const override;`
- L163 _public prototype_ `virtual class UDisplayClusterDisplayDeviceBaseComponent* GetDisplayDeviceComponent(const EDisplayClusterRootActorType InRootActorType) const override;`
- L164 _public prototype_ `virtual bool GetViewPointCameraEye(const uint32 InContextNum, FVector& OutViewLocation, FRotator& OutViewRotation, FVector& OutViewOffset) override;`
- L166 _public function_ `virtual const FDisplayClusterViewport_RenderSettingsICVFX& GetRenderSettingsICVFX() const override`
- L172 _public function_ `virtual const FDisplayClusterViewport_PostRenderSettings& GetPostRenderSettings() const override`
- L178 _public function_ `virtual const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& GetProjectionPolicy() const override`
- L184 _public function_ `virtual const TArray<FDisplayClusterViewport_Context>& GetContexts() const override`
- L190 _public function_ `virtual const TArray<FDisplayClusterViewport_Context>& GetPrevFrameContexts() const override`
- L196 _public function_ `virtual const FDisplayClusterViewportFrameData& GetFrameData() const override`
- L202 _public function_ `virtual const FDisplayClusterViewportFrameData& GetPrevFrameData() const override`
- L208 _public prototype_ `virtual TSharedPtr<FSceneViewStateReference, ESPMode::ThreadSafe> GetOrCreateViewState(uint32 InContextNum) override;`
- L210 _public function_ `virtual const IDisplayClusterViewport_CustomPostProcessSettings& GetViewport_CustomPostProcessSettings() const override`
- L216 _public function_ `virtual IDisplayClusterViewport_CustomPostProcessSettings& GetViewport_CustomPostProcessSettings() override`
- L222 _public prototype_ `virtual bool UseSameOCIO(const IDisplayClusterViewport* InViewportPtr) const override;`
- L225 _public prototype_ `virtual void SetupSceneView(uint32 ContextNum, class UWorld* World, class FSceneViewFamily& InViewFamily, FSceneView& InView) const override;` — Setup scene view for rendering specified Context
- L231 _public prototype_ `void Initialize();`
- L234 _public prototype_ `void ReleaseAllResources();` — Release all viewport resources: textures and ViewState.
- L238 _public prototype_ `bool ShouldUseFullSizeFrameTargetableResource() const;` — Get from logic request for additional targetable resource
- L240 _public prototype_ `void SetViewportBufferRatio(const float InBufferRatio);`
- L242 _public function_ `inline bool FindContext(const int32 ViewIndex, uint32* OutContextNum)`
- L263 _public prototype_ `bool GetCameraViewPoint(FMinimalViewInfo& InOutViewInfo);` — Returns the raw ViewInfo from the camera, before stereo or warp-blend modification.
- L265 _public prototype_ `void OnHandleStartScene();`
- L266 _public prototype_ `void OnHandleEndScene();`
- L268 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L271 _public prototype_ `void ResetRuntimeParameters(const UDisplayClusterConfigurationViewport* InConfigurationViewport = nullptr);` — This function MUST always be called before configuring the viewport at the beginning of each frame.
- L277 _public prototype_ `const TArray<FSceneViewExtensionRef> GatherActiveExtensions(const int32 ViewIndex, FViewport* InViewport) const;` — Collect the view extension active for the desired context of this viewport @param ViewIndex - view index @param InViewport - the viewport display
- L285 _public prototype_ `bool UpdateFrameContexts(const uint32 InStereoViewIndex);` — Initialize viewport contexts and resources for new frame @param InStereoViewIndex - initial StereoViewIndex for this viewport @return - true, if success
- L288 _public prototype_ `void ResetFrameContexts();` — Reset viewport contexts and resources.
- L291 _public prototype_ `bool IsOpenColorIOEquals(const FDisplayClusterViewport& InViewport) const;` — Compare OCIO with another viewport, return true if they are equal.
- L294 _public function_ `const TSharedPtr<FDisplayClusterViewport_OpenColorIO, ESPMode::ThreadSafe>& GetOpenColorIO() const` — Get viewport OCIO instance.
- L301 _public function_ `void SetOpenColorIO(const TSharedPtr<FDisplayClusterViewport_OpenColorIO, ESPMode::ThreadSafe>& InOpenColorIO)` — Set viewport OCIO instance.
- L309 _public function_ `const TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>>& GetViewportResources(const EDisplayClusterViewportResource InResourceType) const` — Get viewport const resources for all contexts by type.
- L316 _public function_ `TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>>& GetViewportResourcesImpl(const EDisplayClusterViewportResource InResourceType)` — Get viewport const resources for all contexts by type.
- L323 _public prototype_ `class FDisplayClusterViewportProxyData* CreateViewportProxyData();` — Create proxy data from this viewport internals.
- L327 _public function_ `FDisplayClusterViewport_RenderSettings& GetRenderSettingsImpl()` — Gain direct access to internal data of the viewport.
- L334 _public function_ `FDisplayClusterViewport_RenderSettingsICVFX& GetRenderSettingsICVFXImpl()` — Gain direct access to internal data of the viewport.
- L341 _public function_ `FDisplayClusterViewport_PostRenderSettings& GetPostRenderSettingsImpl()` — Gain direct access to internal data of the viewport.
- L348 _public function_ `FDisplayClusterViewport_VisibilitySettings& GetVisibilitySettingsImpl()` — Gain direct access to internal visibility data of the viewport.
- L355 _public function_ `FImplDisplayClusterViewport_CameraMotionBlur& GetCameraMotionBlurImpl()` — Gain direct access to internal camera motion blur data of the viewport.
- L362 _public function_ `FDisplayClusterViewport_CameraDepthOfField& GetCameraDepthOfFieldImpl()` — Gain direct access to internal depth of field data of the viewport.
- L369 _public function_ `FDisplayClusterViewport_CustomPostProcessSettings& GetCustomPostProcessSettings()` — Gain direct access to internal PostProcess data of the viewport.
- L379 _public prototype_ `bool IsInternalViewport() const;` — Some viewports are used as internal and skip some logic steps. These viewports are handled separately from regular viewports. Context: icvfx, tile
- L383 _public prototype_ `bool IsOuterViewport() const;` — Return true if this Outer viewport.
- L389 _public prototype_ `bool IsExternalRendering() const;` — Returns true if the RTT of this viewport is changed externally. This means that this viewport will not be rendered. This function is used as the basis for many others. Be careful when making changes to it.
- L392 _public prototype_ `bool IsRenderEnabled() const;` — Returns true if this viewport should be rendered.
- L395 _public prototype_ `bool IsRenderEnabledByMedia() const;` — Returns true if the rendering of this viewport is allowed by external media objects.
- L402 _public prototype_ `bool ShouldDisableViewportResources() const;` — Returns true if this viewport should not allocate resources. Note: This function also disables rendering, since rendering requires resources.
- L405 _public prototype_ `bool IsUsedByMedia() const;` — Returns true if this viewport used by external media objects.
- L408 _public prototype_ `bool CanSplitIntoTiles() const;` — Returns true if this viewport is to be used as a tile source.
- L411 _public prototype_ `bool ShouldUseLumenPerView() const;` — Returns true if per-view Lumen scene is enabled.
- L414 _public prototype_ `bool ShouldFreezeRender() const;` — Return true if this viewport should freeze render.
- L417 _public prototype_ `bool ShouldUseViewStates() const;` — Return true if ViewState should be used by this viewport.
- L422 _public prototype_ `bool ShouldApplyMaxTextureConstraints() const;` — Returns true if textures in this viewport with an area larger than the MaxTextureArea limit must be reduced to stay within that limit with the same aspect ratio.
- L425 _public prototype_ `bool IsResourceUsed(const EDisplayClusterViewportResource InResourceType) const;` — Returns true if this viewport should use this type of resource.
- L428 _public prototype_ `void BeginNewFrame(const FIntPoint& InRenderFrameSize);` — Start a new frame with the specified size. The associated objects and geometries will be updated accordingly.
- L431 _public prototype_ `void FinalizeNewFrame();` — Finalize new frame .
- L434 _public function_ `void ReleaseProjectionPolicy()` — Release the projection policy assigned to this viewport.
- L441 _public prototype_ `void UpdateConfiguration_ProjectionPolicy(const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy = nullptr);` — Update projection policy from configuration.
- L444 _public prototype_ `void UpdateConfiguration_OverlayRenderSettings(const struct FDisplayClusterConfigurationICVFX_OverlayAdvancedRenderSettings& InOverlaySettings);` — setup overlay configuration for this viewport.
- L447 _public prototype_ `void UpdateConfiguration_Overscan(const struct FDisplayClusterViewport_OverscanSettings& InOverscanSettings);` — setup overscan configuration for this viewport.
- L450 _public prototype_ `void UpdateConfiguration_CameraMotionBlur(const struct FDisplayClusterViewport_CameraMotionBlur& InCameraMotionBlur);` — setup CameraMotionBlur configuration for this viewport.
- L453 _public prototype_ `void UpdateConfiguration_CameraDepthOfField(const class FDisplayClusterViewport_CameraDepthOfField& InCameraDepthOfField);` — setup camera depth of field configuration for this viewport.
- L456 _public prototype_ `void UpdateConfiguration_PostRenderGenerateMips(const struct FDisplayClusterConfigurationPostRender_GenerateMips& InGenerateMips);` — setup PostRender mips configuration for this viewport.
- L459 _public prototype_ `void UpdateConfiguration_PostRenderOverride(const struct FDisplayClusterConfigurationPostRender_Override& InOverride);` — setup PostRender override configuration for this viewport.
- L462 _public prototype_ `void UpdateConfiguration_PostRenderBlur(const struct FDisplayClusterConfigurationPostRender_BlurPostprocess& InBlurPostprocess);` — setup PostRender blur configuration for this viewport.
- L465 _public prototype_ `bool UpdateConfiguration_ViewportRemap(const struct FDisplayClusterConfigurationViewport_Remap& InRemapConfiguration);` — setup viewport remap configuration for this viewport.
- L468 _public prototype_ `const UDisplayClusterConfigurationViewport* GetViewportConfigurationData() const;` — Returns viewport configuration data.
- L471 _public prototype_ `void SetViewportConfigurationData(const UDisplayClusterConfigurationViewport* InConfigurationData);` — Sets viewport configuration data.
- L474 _public prototype_ `void CleanupViewState();` — Cleanup view states.
- L477 _public function_ `bool CanShowLogMsgOnce(const EDisplayClusterViewportShowLogMsgOnce& InLogState) const` — Returns true once if this type of log message can be displayed for the first time.
- L490 _public function_ `void ResetShowLogMsgOnce(const EDisplayClusterViewportShowLogMsgOnce& InLogState) const` — Reset viewport log states.
- L498 _public prototype_ `uint8 GetPriority() const;` — Viewports should be processed in the appropriate order. Viewports with lower priority values will be processed earlier.
- L501 _private prototype_ `float GetClusterRenderTargetRatioMult(const FDisplayClusterRenderFrameSettings& InFrameSettings) const;`
- L502 _private prototype_ `FIntPoint GetDesiredContextSize(const FIntPoint& InSize, const FDisplayClusterRenderFrameSettings& InFrameSettings) const;`
- L503 _private prototype_ `float GetCustomBufferRatio(const FDisplayClusterRenderFrameSettings& InFrameSettings) const;`
- L508 _private prototype_ `bool IsResourceUsedImpl(const EDisplayClusterViewportResource InResourceType) const;` — Returns true if this viewport should use this type of resource. This is function can be used only by the IsResourceUsed();
- L515 _private prototype_ `void ImplGatherActiveExtensions(const int32 ViewIndex, FViewport* InViewport, TArray<FSceneViewExtensionRef>& OutExtensions) const;` — Collect the view extension active for the desired context of this viewport @param ViewIndex     - view index @param InViewport    - the viewport display @param OutExtensions - (out) Extension that can be used by this viewport context
- L526 _private prototype_ `bool PreCalculateViewData(const uint32 InContextNum, const FVector& InViewLocation, const FRotator& InViewRotation, const float WorldToMeters);` — Initialize View data @param InContextNum      - (in) viewport eye context index @param InOutViewLocation - (in) View location @param InOutViewRotation - (in) View rotator @param WorldToMeters     - UE world scale @return true on success
- L530 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L534 _public member_ `const FString ViewportBaseId;` — Base viewport identifier. May not be unique across ICVFX viewports (multiple viewports can share the same base ID).
- L537 _public member_ `const EDisplayClusterViewportFlags ViewportFlags;` — Usage flags of the viewport (e.g. InCamera, Chromakey, LightCard, Tile).
- L541 _public member_ `const FString ViewportId;` — Final unique viewport identifier. Guaranteed to be unique across the entire cluster (includes node ID and usage type if needed).
- L544 _public member_ `const FString ClusterNodeId;` — Owner cluster node name
- L547 _public member_ `const TSharedRef<FDisplayClusterViewportProxy, ESPMode::ThreadSafe> ViewportProxy;` — viewport proxy (render thread data)
- L550 _public member_ `const TSharedRef<FDisplayClusterViewportPreview, ESPMode::ThreadSafe> ViewportPreview;` — Viewport preview
- L554 _private member_ `FDisplayClusterViewportResources Resources;` — Unified repository of viewport resources
- L557 _private member_ `TSharedPtr<FDisplayClusterViewport_OpenColorIO, ESPMode::ThreadSafe> OpenColorIO;` — nDisplay OpenColorIO object.
- L560 _private member_ `TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> ProjectionPolicy;` — Projection policy instance that serves this viewport
- L561 _private member_ `TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> UninitializedProjectionPolicy;`
- L564 _private member_ `FDisplayClusterViewport_CustomPostProcessSettings CustomPostProcessSettings;` — Postprocess
- L567 _private member_ `FDisplayClusterViewport_VisibilitySettings VisibilitySettings;` — Visibility settings
- L570 _private member_ `FImplDisplayClusterViewport_CameraMotionBlur CameraMotionBlur;` — Additional features
- L573 _private member_ `FDisplayClusterViewport_CameraDepthOfField CameraDepthOfField;` — Depth of field settings
- L576 _private member_ `FDisplayClusterViewport_OverscanRuntimeSettings OverscanRuntimeSettings;` — Overscan rendering feature
- L579 _private member_ `FDisplayClusterViewport_CustomFrustumRuntimeSettings CustomFrustumRuntimeSettings;` — Custom frustum rendering feature
- L582 _private member_ `FDisplayClusterViewportRemap ViewportRemap;` — viewport OutputRemap feature
- L585 _private member_ `FDisplayClusterViewport_RenderSettings RenderSettings;` — Viewport render params
- L586 _private member_ `FDisplayClusterViewport_RenderSettingsICVFX RenderSettingsICVFX;`
- L587 _private member_ `FDisplayClusterViewport_PostRenderSettings PostRenderSettings;`
- L590 _private member_ `FDisplayClusterViewportFrameData CurrentFrameData;` — Frame data snapshot for the current frame (contexts, cached view info).
- L593 _private member_ `TArray<FDisplayClusterViewport_Context>& Contexts;` — Legacy reference alias to the current frame's viewport contexts stored in CurrentFrameData.Contexts.
- L596 _private member_ `FDisplayClusterViewportFrameData PreviousFrameData;` — Frame data snapshot from the previous frame; used for motion blur and temporal effects.
- L599 _private member_ `TArray<TSharedPtr<FSceneViewStateReference, ESPMode::ThreadSafe>> ViewStates;` — View states (preview only)
- L602 _private member_ `TWeakObjectPtr<const UDisplayClusterConfigurationViewport> ConfigurationData;` — The soft ptr to the configuration data of this viewport. Updated every frame.
- L605 _private member_ `mutable EDisplayClusterViewportShowLogMsgOnce ShowLogMsgOnceFlags = EDisplayClusterViewportShowLogMsgOnce::None;` — A recurring message in the log will be shown only once
- L610 _private member_ `float CustomNearClippingPlane = -1;` — Near clipping plane value (obtained from the GetDesiredView() functions). If the value is less than zero, it does not apply to this viewport. This value is changed in the SetupViewPoint() function, called at the beginning from LocalPlayer.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportFrameStatsViewExtension.h` (Private)


#### class `FDisplayClusterViewportFrameStatsViewExtension`  
`class FDisplayClusterViewportFrameStatsViewExtension : public FSceneViewExtensionBase`  
_L12-42_
- inherits: `FSceneViewExtensionBase`
- desc: DC-specific view extension to display frame stats
- L15 _public prototype_ `FDisplayClusterViewportFrameStatsViewExtension(const FAutoRegister& AutoRegister, const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L16 _public prototype_ `virtual ~FDisplayClusterViewportFrameStatsViewExtension() = default;`
- L20 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L22 _public prototype_ `void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled);`
- L23 _public prototype_ `FScreenPassTexture PostProcessPassAfterTonemap_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& InOutInputs);`
- L25 _public function_ `virtual int32 GetPriority() const override`
- L28 _protected prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L32 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L36 _private prototype_ `bool IsActive() const;` — True, if VE can be used at the moment.
- L41 _private member_ `uint32 EncodedTimecode_RenderThread;` — Encoded timecode

#### Free symbols / members of external scopes

- L7 _macro_ `#define DISPLAYCLUSTER_SCENE_DEBUG_VIEW_EXTENSION_PRIORITY 999`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportHelpers.h` (Private)


#### class `FDisplayClusterViewportHelpers`  
`class FDisplayClusterViewportHelpers`  
_L10-104_
- desc: Helper class for DC viewports
- L14 _public prototype_ `static int32 GetMinTextureDimension();` — Get the maximum allowable texture size used for the nDisplay viewport.
- L17 _public prototype_ `static int32 GetMaxTextureDimension();` — Get the minimum allowable texture size used for the nDisplay viewport.
- L20 _public prototype_ `static int32 GetMaxTextureArea();` — Get the maximum allowable texture area that can be used for the nDisplay viewport.
- L30 _public prototype_ `static FIntRect GetValidViewportRect(const FIntRect& InRect, const FString& InViewportId, const TCHAR* InResourceName = nullptr);` — Get the valid viewport size. @param InRect         - source region @param InViewportId   - The viewport name (debug purpose) @param InResourceName - The resource name (debug purpose) @return the region of the viewport that can be used
- L38 _public prototype_ `static bool IsValidTextureSize(const FIntPoint& InSize);` — Return true, if size is valid. @param InSize - the size to be checked. @return true, if the size is within the minimum and maximum dimensions
- L47 _public prototype_ `static FIntPoint ScaleTextureSize(const FIntPoint& InSize, float InMult);` — Scaling texture size with a multiplier @param InSize - the input texture size @param InMult - texture size multiplier @return - scaled texture size
- L56 _public prototype_ `static FIntRect ScaleViewportRect(const FIntRect& InRect, const FVector2D& InPerAxisMult);` — Scale a viewport rect by a per-axis multiplier. @param InRect        - the input rect @param InPerAxisMult - per-axis size multiplier @return - scaled viewport rect
- L66 _public prototype_ `static float GetValidSizeMultiplier(const FIntPoint& InSize, const float InSizeMult, const float InBaseSizeMult);` — Find an acceptable multiplier for the texture size @param InSize - in texture size @param InSizeMult - the target multiplier @param InBaseSizeMult - the base multiplier @return - a multiplier that gives the valid size of the texture
- L75 _public prototype_ `static int32 GetMaxTextureNumMips(const struct FDisplayClusterRenderFrameSettings& InRenderFrameSettings, const int32 InNumMips);` — Getting the maximum allowable mips value for the rendering frame settings @param InRenderFrameSettings  -the current render frame settings @param InNumMips - texture mips value from the settings @return - the mips value to be used.
- L80 _public prototype_ `static EPixelFormat GetPreviewDefaultPixelFormat();` — Getting the default pixel format for preview rendering
- L85 _public prototype_ `static EPixelFormat GetDefaultPixelFormat();` — Getting the default pixel format
- L99 _public prototype_ `static bool GetValidResourceRectsForResolve( const FIntPoint& InSourceTextureExtent, const FIntPoint& InDestTextureExtent, FIntRect& InOutSourceRect, FIntRect& InOutDestRect);` — Check if resources with the specified regions can be resolved. If any rect exceeds the texture size, RHI will crash. This function adjusts the rects to the size of the textures. @param InSourceTextureExtent - (in) Source RHI texture size @param InDestTextureExtent   - (in) Destination RHI texture size @param InOutSourceRect - (in, out) src rect @param InOutDestRect   - (in, out) dest rect @return false, if it isn't possible

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportManager.h` (Private)


#### class `FDisplayClusterViewportManager`  
`class FDisplayClusterViewportManager : public IDisplayClusterViewportManager , public TSharedFromThis<FDisplayClusterViewportManager, ESPMode::ThreadSafe>`  
_L26-333_
- inherits: `IDisplayClusterViewportManager,TSharedFromThis<FDisplayClusterViewportManager,ESPMode::ThreadSafe>`
- desc: Implementation of the nDisplay IDisplayClusterViewportManager
- L31 _public prototype_ `FDisplayClusterViewportManager();`
- L32 _public prototype_ `virtual ~FDisplayClusterViewportManager();`
- L36 _public prototype_ `void HandleStartScene();` — Game thread funcs
- L37 _public prototype_ `void HandleEndScene();`
- L39 _public prototype_ `void Initialize();`
- L46 _public prototype_ `void ReleaseAllResources();` — Release all resources. After that, the BeginNewFrame() function should be called for a new resource allocation. Note: This function has been renamed; its previous name was 'ReleaseTextures'.
- L50 _public prototype_ `virtual void Release() override;`
- L52 _public function_ `virtual TSharedPtr<IDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedPtr() override`
- L57 _public function_ `virtual TSharedPtr<const IDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L62 _public function_ `virtual TSharedRef<FDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedRef() override`
- L67 _public function_ `virtual TSharedRef<const FDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedRef() const override`
- L73 _public prototype_ `virtual IDisplayClusterViewportManagerPreview& GetViewportManagerPreview() override;` — Get viewport manager preview API
- L74 _public prototype_ `virtual const IDisplayClusterViewportManagerPreview& GetViewportManagerPreview() const override;`
- L77 _public prototype_ `virtual const IDisplayClusterViewportManagerProxy* GetProxy() const override;`
- L78 _public prototype_ `virtual IDisplayClusterViewportManagerProxy* GetProxy() override;`
- L80 _public function_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() override`
- L84 _public function_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const override`
- L89 _public function_ `virtual const TSharedRef<IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() override`
- L93 _public function_ `virtual const TSharedRef<const IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() const override`
- L98 _public prototype_ `virtual bool BeginNewFrame(FViewport* InViewport, FDisplayClusterRenderFrame& OutRenderFrame) override;`
- L99 _public prototype_ `virtual void InitializeNewFrame() override;`
- L100 _public prototype_ `virtual void FinalizeNewFrame() override;`
- L102 _public prototype_ `virtual FSceneViewFamily::ConstructionValues CreateViewFamilyConstructionValues( const FDisplayClusterRenderFrameTarget& InFrameTarget, FSceneInterface* InScene, FEngineShowFlags InEngineShowFlags, const bool bInAdditionalViewFamily ) const override;`
- L109 _public prototype_ `virtual void ConfigureViewFamily( const FDisplayClusterRenderFrameTarget& InFrameTarget, const FDisplayClusterRenderFrameTargetViewFamily& InFrameViewFamily, FSceneViewFamilyContext& InOutViewFamily ) override;`
- L115 _public prototype_ `virtual void PostConfigureViewFamily( const FDisplayClusterRenderFrameTarget& InFrameTarget, const FDisplayClusterRenderFrameTargetViewFamily& InFrameViewFamily, FSceneViewFamilyContext& InOutViewFamily, const TArray<FSceneView*>& InOutViews, const EDisplayClusterViewportRenderingFlags InRenderingFlags = EDisplayClusterViewportRenderingFlags::None, const float InDPIScale = 1.f ) override;`
- L124 _public prototype_ `virtual void RenderFrame(FViewport* InViewport) override;`
- L128 _private prototype_ `void OnPreGarbageCollect();` — Called before garbage collection is run
- L131 _public prototype_ `virtual IDisplayClusterViewport* FindViewport(const FString& InViewportId) const override;`
- L132 _public function_ `virtual IDisplayClusterViewport* FindViewport(const int32 ViewIndex, uint32* OutContextNum = nullptr) const override`
- L137 _public function_ `virtual const TArrayView<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>> GetCurrentRenderFrameViewports() const override`
- L143 _public function_ `virtual const TArrayView<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>> GetEntireClusterViewports() const override`
- L148 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>> GetEntireClusterViewportsForWarpPolicy(const TSharedPtr<IDisplayClusterWarpPolicy>& InWarpPolicy) const override;`
- L150 _public prototype_ `virtual void MarkComponentGeometryDirty(const FName InComponentName = NAME_None) override;`
- L151 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L153 _public prototype_ `virtual class FSceneView* CalcSceneView(class ULocalPlayer* LocalPlayer, class FSceneViewFamily* ViewFamily, FVector& OutViewLocation, FRotator& OutViewRotation, class FViewport* Viewport, class FViewElementDrawer* ViewDrawer, int32 StereoViewIndex) override;`
- L158 _public function_ `inline const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& ImplGetCurrentRenderFrameViewports() const` — Getting the viewports of the current rendering frame (viewports from the current node or from a special named list).
- L169 _public function_ `inline const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& ImplGetEntireClusterViewports() const`
- L175 _public prototype_ `FDisplayClusterViewport* CreateViewport(const FString& InViewportBaseId, const class UDisplayClusterConfigurationViewport& ConfigurationViewport);` — internal use only
- L176 _public prototype_ `FDisplayClusterViewport* CreateViewport(const FString& InViewportBaseId, const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InProjectionPolicy);`
- L177 _public prototype_ `bool DeleteViewport(const FString& ViewportId);`
- L179 _public prototype_ `FDisplayClusterViewport* ImplFindViewport(const int32 ViewIndex, uint32* OutContextNum = nullptr) const;`
- L191 _public prototype_ `TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe> ImplCreateViewport( const FString& InViewportBaseId, const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InProjectionPolicy, const EDisplayClusterViewportFlags InViewportFlags = EDisplayClusterViewportFlags::None, const FIntPoint* InOptTilePos = nullptr);` — Creates and initializes a new nDisplay viewport instance. @param InViewportBaseId    The base viewport identifier (before ICVFX unique naming). @param InProjectionPolicy  Projection policy assigned to the viewport (defines how the scene is projected/rendered). @param InViewportFlags     Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @param InOptTilePos        Optional parameter for tile viewport position @return A thread-safe shared pointer to the created FDisplayClusterViewport.
- L207 _public prototype_ `TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe> ImplFindViewport( const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags = EDisplayClusterViewportFlags::None, const FIntPoint* InOptTilePos = nullptr) const;` — Finds a viewport instance by identifier and usage type. @param InViewportBaseId The base viewport identifier (before ICVFX unique naming). @param InViewportFlags  Usage flags of the viewport (e.g. InCamera/LightCard/Tile, etc.). @param InOptTilePos     Optional parameter for tile viewport position @return A thread-safe shared pointer to the matching FDisplayClusterViewport, or nullptr if no viewport matches the given criteria.
- L212 _public prototype_ `void ImplDeleteViewport(const TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>& InExistViewport);`
- L214 _public prototype_ `static TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> CreateProjectionPolicy( const FString& InViewportId, const FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy);`
- L219 _public function_ `TSharedPtr<FDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> GetViewportManagerProxy() const` — Get DC viewport manager proxy.
- L233 _public prototype_ `int32 GetViewportStereoViewIndexBase(const TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>& InViewport) const;` — Gets the unique StereoViewIndex base for the viewport. Each StereoViewIndexBase has a distance to others equal to ViewPerViewportAmount. Note: This function has been renamed. Its previous name was FindFirstViewportStereoViewIndex(). @param InViewport - viewport asked for a StereoViewIndex base @return StereoViewIndex base or INDEX_NONE, if the viewport cannot be rendered.
- L236 _public prototype_ `bool ShouldRenderFinalColor() const;` — Returns true if the final color is renderable (to support preview in scene).
- L239 _public function_ `const TSharedPtr<class FDisplayClusterViewportManagerViewExtension, ESPMode::ThreadSafe>& GetViewportManagerViewExtension() const` — Return nDisplay VE object.
- L243 _public function_ `const TSharedPtr<class FDisplayClusterViewportManagerViewPointExtension, ESPMode::ThreadSafe>& GetViewportManagerViewPointExtension() const` — Return ViewPoint VE instance.
- L247 _public prototype_ `void SetCurrentStereoViewIndexForViewPointExtension(const int32 InStereoViewIndex) const;` — Set current view index for FDisplayClusterViewportManagerViewPointExtension
- L250 _public prototype_ `bool ShouldUseOutputFrameTargetableResources() const;` — Returns true if at least one of the viewports are visible on the frame RTT.
- L251 _public prototype_ `bool ShouldUseAdditionalFrameTargetableResource() const;`
- L252 _public prototype_ `bool ShouldUseFullSizeFrameTargetableResource() const;`
- L254 _public prototype_ `void ResetSceneRenderTargetSize();`
- L257 _public prototype_ `void OnEntireClusterPreviewRendered();` — Called every time previews for all cluster nodes are rendered.
- L261 _private prototype_ `void UpdateCurrentRenderFrameViewports() const;` — This function updates CurrentRenderFrameViewports according to the current rendering settings.
- L263 _private prototype_ `void UpdateSceneRenderTargetSize();`
- L264 _private prototype_ `void HandleViewportRTTChanges(const TArray<FDisplayClusterViewport_Context>& PrevContexts, const TArray<FDisplayClusterViewport_Context>& Contexts);`
- L267 _private prototype_ `void RegisterCallbacks();` — Register any callbacks
- L270 _private prototype_ `void UnregisterCallbacks();` — Unregister any callbacks used
- L274 _public member_ `const TSharedRef<class FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L277 _public member_ `const TSharedRef<class FDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe> ViewportManagerPreview;` — Viewport preview
- L280 _public member_ `const TSharedRef<class FDisplayClusterRenderTargetManager, ESPMode::ThreadSafe> RenderTargetManager;` — Resource manager
- L283 _public member_ `const TSharedRef<class FDisplayClusterViewportPostProcessManager, ESPMode::ThreadSafe> PostProcessManager;` — Postprocess manager
- L286 _public member_ `const TSharedRef<class FDisplayClusterViewportLightCardManager, ESPMode::ThreadSafe> LightCardManager;` — LC manager
- L289 _public member_ `const TSharedRef<class FDisplayClusterRenderFrameManager> RenderFrameManager;` — Manager for creating the render frame stucture
- L292 _public member_ `const TSharedRef<class FDisplayClusterAutoExposure> AutoExposure;` — nDisplay multi-viewport AutoExposure feature.
- L296 _private member_ `TSharedPtr<FDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ViewportManagerProxy;` — Render thread proxy manager. Deleted on render thread
- L299 _private member_ `TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>> EntireClusterViewports;` — Viewports of the entire cluster
- L302 _private member_ `TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>> CurrentRenderFrameViewports;` — Viewports of the current render frame (viewports from the current node or from a special named list)
- L314 _private member_ `ESceneRenderTargetResizeMethod SceneRenderTargetResizeMethod = ESceneRenderTargetResizeMethod::None;` — Support for resetting RTT size (GROW method always grows and does not recover FPS when the viewport size or buffer ratio is changed)
- L315 _private member_ `int32 FrameHistoryCounter = 0;`
- L318 _private member_ `TSharedPtr<class FDisplayClusterViewportManagerViewExtension, ESPMode::ThreadSafe> ViewportManagerViewExtension;` — Handle special features
- L321 _private member_ `TSharedPtr<class FDisplayClusterViewportManagerViewPointExtension, ESPMode::ThreadSafe> ViewportManagerViewPointExtension;` — This VE is used for LocalPlayer::GetViewPoint(). It calls the ISceneViewExtension::SetupViewPoint() function of this VE.
- L324 _private member_ `TSharedPtr<class FDisplayClusterViewportFrameStatsViewExtension, ESPMode::ThreadSafe> FrameStatsViewExtension;` — This VE is used to display frame information such as timecode and frame number.
- L327 _private member_ `bool bReleaseFunctionCalledBeforeDestructor = false;` — This is a flag to check in the destructor that Release() has been called before.
- L331 _private member_ `FDelegateHandle PreGarbageCollectHandle;` — The handle for FCoreUObjectDelegates::GetPreGarbageCollectDelegate

#### enum `FDisplayClusterViewportManager::ESceneRenderTargetResizeMethod`  
`enum class ESceneRenderTargetResizeMethod : uint8`  
_L305-311_
- desc: Scene RTT resize method.
- L307 _public enumerator_ `None = 0`
- L308 _public enumerator_ `Reset`
- L309 _public enumerator_ `WaitFrameSizeHistory`
- L310 _public enumerator_ `Restore`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportManagerProxy.h` (Private)


#### class `FDisplayClusterViewportManagerProxy`  
`class FDisplayClusterViewportManagerProxy : public IDisplayClusterViewportManagerProxy , public TSharedFromThis<FDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe>`  
_L31-185_
- inherits: `IDisplayClusterViewportManagerProxy,TSharedFromThis<FDisplayClusterViewportManagerProxy,ESPMode::ThreadSafe>`
- desc: ViewportManagerProxy implementation. This is a proxy object for the rendering thread. The data is copied every frame from the ViewportManager on the game thread.
- L36 _public prototype_ `FDisplayClusterViewportManagerProxy(const FDisplayClusterViewportManager& InViewportManager);`
- L37 _public prototype_ `virtual ~FDisplayClusterViewportManagerProxy();`
- L41 _public function_ `virtual TSharedPtr<IDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ToSharedPtr() override`
- L46 _public function_ `virtual TSharedPtr<const IDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L52 _public function_ `virtual const IDisplayClusterViewportConfigurationProxy& GetConfigurationProxy() const override` — Get viewport manager proxy configuration interface.
- L57 _public function_ `virtual IDisplayClusterViewportProxy* FindViewport_RenderThread(const FString& InViewportId) const override`
- L62 _public function_ `virtual IDisplayClusterViewportProxy* FindViewport_RenderThread(const int32 StereoViewIndex, uint32* OutContextNum = nullptr) const override`
- L67 _public function_ `virtual const TArrayView<TSharedPtr<IDisplayClusterViewportProxy, ESPMode::ThreadSafe>> GetViewports_RenderThread() const override`
- L72 _public prototype_ `virtual bool GetFrameTargets_RenderThread(TArray<FRHITexture*>& OutFrameResources, TArray<FIntPoint>& OutTargetOffsets, TArray<FRHITexture*>* OutAdditionalFrameResources = nullptr) const override;`
- L73 _public prototype_ `virtual bool ResolveFrameTargetToBackBuffer_RenderThread(FRHICommandListImmediate& RHICmdList, const uint32 InContextNum, const int32 DestArrayIndex, FRHITexture* DestTexture, FVector2D WindowSize) const override;`
- L88 _public prototype_ `bool ImplResolveFrameTargetToBackBuffer_RenderThread(FRDGBuilder& GraphBuilder, const uint32 InContextNum, const int32 DestArrayIndex, FRDGTextureRef DestTexture, FVector2f WindowSize) const;` — Resolve to backbuffer [RDG version] @param GraphBuilder   - Render Graph interface @param InContextNum   - renderframe source context num @param DestArrayIndex - dest array index on backbuffer @param DestTexture    - dest RDG texture @param WindowSize     - dest backbuffer window size @return - true if success
- L94 _public prototype_ `void ReleaseAllResources_RenderThread();` — Release all resources on render thread. Note: This function has been renamed; its previous name was 'ReleaseTextures_RenderThread()'
- L97 _public prototype_ `void DoCrossGPUTransfers_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — Custom cross-GPU implementation for mGPU. Applyed for viewports with bOverrideCrossGPUTransfer=true.
- L100 _public prototype_ `void UpdateDeferredResources_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — UpdateDeferredResources for all viewports (OCIO, PP, mips, etc).
- L103 _public prototype_ `void UpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — Apply WarpBlend and resolve to frame resources.
- L109 _public prototype_ `void CleanupResources_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — Called at the end of the frame, after all callbacks. At the end, some resources may be filled with black, etc. This is useful because the resources are reused and the image from the previous frame goes into the new one.
- L112 _public prototype_ `void Release_RenderThread();` — Release all referenced objects and resources.
- L115 _public prototype_ `void CreateViewport_RenderThread(const TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>& InViewportProxy);` — Register new viewport proxy.
- L118 _public prototype_ `void DeleteViewport_RenderThread(const TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>& InViewportProxy);` — Unregister exist viewport proxy.
- L121 _public function_ `inline TSharedPtr<FDisplayClusterViewportLightCardManagerProxy, ESPMode::ThreadSafe> GetLightCardManagerProxy_RenderThread() const` — Get LightCardManager proxy object.
- L125 _public function_ `inline const TArray<TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>>& ImplGetCurrentRenderFrameViewportProxies_RenderThread() const` — Geting the viewport proxies of the current rendering frame. (viewports from the current node or from a special named list)
- L129 _public function_ `inline const TArray<TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>>& ImplGetEntireClusterViewportProxies_RenderThread() const` — Get the viewport proxies  of the whole cluster on the render thread.
- L133 _public prototype_ `FDisplayClusterViewportProxy* ImplFindViewportProxy_RenderThread(const FString& InViewportId) const;` — Find viewport by name.
- L136 _public prototype_ `FDisplayClusterViewportProxy* ImplFindViewportProxy_RenderThread(const int32 StereoViewIndex, uint32* OutContextNum = nullptr) const;` — Find viewport and context index by StereoViewIndex.
- L139 _public prototype_ `void ImplUpdateViewportProxies_GameThread(const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& InCurrentRenderFrameViewports);` — Sending viewport data from the game stream to the viewport proxy that is in the rendering stream.
- L142 _public prototype_ `void ImplUpdateViewportManagerProxy_GameThread(const FDisplayClusterViewportManager& InViewportManager);` — Sending viewport manager data from the game stream to the viewport manager proxy that is in the rendering stream.
- L145 _public prototype_ `void ImplRenderFrame_GameThread(FViewport* InViewport);` — Rendering the final frame of nDisplay. Called after all viewports have been rendered in RTT.
- L148 _public prototype_ `void ImplClearFrameTargets_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — Rendering black color in all frame textures.
- L152 _private prototype_ `void ImplUpdateClusterNodeViewportProxies_RenderThread();` — Update ClusterNodeViewportProxies from ViewportProxies for the current cluster node.
- L156 _public member_ `const TSharedRef<FDisplayClusterViewportConfigurationProxy, ESPMode::ThreadSafe> ConfigurationProxy;` — Configuration for proxy
- L159 _public member_ `const TSharedRef<FDisplayClusterRenderTargetManager, ESPMode::ThreadSafe> RenderTargetManager;` — RenderTarget manager object. Used to remove related objects in order.
- L162 _public member_ `const TSharedRef<FDisplayClusterViewportPostProcessManager, ESPMode::ThreadSafe> PostProcessManager;` — PostProcess manager object. Used to remove related objects in order.
- L165 _public member_ `const TSharedRef<FDisplayClusterViewportLightCardManagerProxy, ESPMode::ThreadSafe> LightCardManagerProxy;` — LightCard manager proxy object.
- L168 _public member_ `const TSharedRef<FDisplayClusterAutoExposure> AutoExposure;` — nDisplay multi-viewport AutoExposure feature.
- L172 _private member_ `TArray<TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>> EntireClusterViewportProxies;` — Viewport proxies of the entire cluster.
- L175 _private member_ `TArray<TSharedPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>> CurrentRenderFrameViewportProxies;` — Viewport proxies of the current rendering frame (viewports from the current node or from a special named list).
- L178 _private member_ `TSharedPtr<class FDisplayClusterViewportManagerViewExtension, ESPMode::ThreadSafe> ViewportManagerViewExtension;` — nDisplay VE object. Used to remove related objects in order.
- L183 _private member_ `mutable uint8 bHasLoggedBackbufferStereoUnsupported : 1 = 0;` — True if the "Backbuffer does not support stereo" error has already been logged. Used to ensure the error is only written to the log once.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportManagerViewExtension.h` (Private)


#### class `FDisplayClusterViewportManagerViewExtension`  
`class FDisplayClusterViewportManagerViewExtension : public FSceneViewExtensionBase`  
_L16-120_
- inherits: `FSceneViewExtensionBase`
- desc: View extension applying an DC Viewport features
- L19 _public prototype_ `FDisplayClusterViewportManagerViewExtension(const FAutoRegister& AutoRegister, const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L20 _public prototype_ `virtual ~FDisplayClusterViewportManagerViewExtension();`
- L24 _public function_ `virtual int32 GetPriority() const override`
- L29 _public prototype_ `virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L31 _public prototype_ `virtual void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L33 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L35 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L36 _public prototype_ `virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L40 _public prototype_ `void Release_RenderThread();` — Release from render thread.
- L50 _private prototype_ `void OnResolvedSceneColor_RenderThread(FRDGBuilder& GraphBuilder, const FSceneTextures& SceneTextures);` — nDisplay VE Callback [subscribed to Renderer:ResolvedSceneColorCallbacks]. @param GraphBuilder   - RDG interface @param SceneTextures  - Scene textures (SceneColor, Depth, etc) @return - none
- L60 _private prototype_ `FScreenPassTexture PostProcessPassAfterFXAA_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);` — Callback OnPostProcessPassAfterFXAA. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @return - Screen pass texture
- L70 _private prototype_ `FScreenPassTexture PostProcessPassAfterSSRInput_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);` — Callback OnPostProcessPassAfterSSRInput. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @return - Screen pass texture
- L80 _private prototype_ `FScreenPassTexture PostProcessPassAfterTonemap_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);` — Callback OnPostProcessPassAfterTonemap. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @return - Screen pass texture
- L83 _private prototype_ `void RegisterCallbacks();` — Register callbacks to external modules (Renderer:ResolvedSceneColor).
- L86 _private prototype_ `void UnregisterCallbacks();` — UnRegister callbacks to external modules (Renderer:ResolvedSceneColor).
- L89 _private prototype_ `bool IsActive() const;` — Return true if the VE is safe to use.
- L93 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L96 _private member_ `FDelegateHandle ResolvedSceneColorCallbackHandle;`
- L116 _private member_ `TArray<FViewportProxy> ViewportProxies;` — RenderThreadData:. Viewport proxies from rendered view family.
- L119 _private member_ `bool bReleased = false;` — Is this VE released

#### struct `FDisplayClusterViewportManagerViewExtension::FViewportProxy`  
`struct FViewportProxy`  
_L98-113_
- L100 _public function_ `inline FDisplayClusterViewportProxy* GetViewportProxy() const`
- L106 _public member_ `TWeakPtr<FDisplayClusterViewportProxy, ESPMode::ThreadSafe> ViewportProxyWeakPtr;` — The ViewportProxy must exist until this object is removed.
- L109 _public member_ `int32 ViewIndex = 0;` — The index of view in viewfamily collection
- L112 _public member_ `FDisplayClusterViewportProxy_Context ViewportProxyContext;` — Context for viewport proxy object

#### Free symbols / members of external scopes

- L11 _macro_ `#define DISPLAYCLUSTER_SCENE_VIEW_EXTENSION_PRIORITY -1`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportManagerViewPointExtension.h` (Private)


#### class `FDisplayClusterViewportManagerViewPointExtension`  
`class FDisplayClusterViewportManagerViewPointExtension : public FSceneViewExtensionBase`  
_L13-50_
- inherits: `FSceneViewExtensionBase`
- desc: View extension applying an DC Viewport features
- L16 _public prototype_ `FDisplayClusterViewportManagerViewPointExtension(const FAutoRegister& AutoRegister, const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L17 _public prototype_ `virtual ~FDisplayClusterViewportManagerViewPointExtension() = default;`
- L21 _public prototype_ `virtual void SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InOutViewInfo) override;`
- L22 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L24 _public function_ `virtual int32 GetPriority() const override`
- L31 _public function_ `void SetCurrentStereoViewIndex(const int32 InStereoViewIndex)` — Set current view index for this VE: This function must be used because LocalPlayer::GetViewPoint() calls the ISceneViewExtension::SetupViewPoint() function from this VE. And at this point the VE must know the current StereoViewIndex value in order to understand which viewport will be used for this SetupViewPoint() call. Set INDEX_NONE when this VE no longer needs to be used.
- L37 _protected prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L41 _private prototype_ `bool IsActive() const;` — True, if VE can be used at the moment.
- L45 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L49 _private member_ `int32 CurrentStereoViewIndex = INDEX_NONE;` — Current StereoViewIndex for rendered viewport

#### Free symbols / members of external scopes

- L8 _macro_ `#define DISPLAYCLUSTER_SCENE_VIEWPOINT_EXTENSION_PRIORITY 1000` — This VE should be used before all others.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportProxy.h` (Private)


#### enum `EDisplayClusterViewportOpenColorIOMode`  
`enum class EDisplayClusterViewportOpenColorIOMode : uint8`  
_L34-43_
- desc: OCIO is applied in different ways. It depends on the rendering workflow
- L36 _public enumerator_ `None = 0`
- L39 _public enumerator_ `PostProcess` — When the viewport renders with a postprocess, OCIO must be done in between
- L42 _public enumerator_ `Resolved` — When the viewport is rendered without postprocessing, OCIO is applied last, to the RTT texture of the viewport

#### class `FDisplayClusterViewportProxy`  
`class FDisplayClusterViewportProxy : public IDisplayClusterViewportProxy , public TSharedFromThis<FDisplayClusterViewportProxy, ESPMode::ThreadSafe>`  
_L48-454_
- inherits: `IDisplayClusterViewportProxy,TSharedFromThis<FDisplayClusterViewportProxy,ESPMode::ThreadSafe>`
- desc: nDisplay viewport proxy implementation.
- L63 _public prototype_ `FDisplayClusterViewportProxy( const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration, const FString& InViewportBaseId, const EDisplayClusterViewportFlags InViewportFlags, const FString& InViewportId, const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& InProjectionPolicy);` — Creates a viewport proxy instance. @param InConfiguration    Viewport configuration object (thread-safe). @param InViewportBaseId   The base viewport identifier (before ICVFX unique naming). @param InViewportFlags    Usage type of the viewport (e.g. InCamera, Chromakey, LightCard). @param InViewportId       A viewport name string unique within the cluster. @param InProjectionPolicy Projection policy assigned to the viewport (defines how the scene is projected/rendered).
- L70 _public prototype_ `virtual ~FDisplayClusterViewportProxy();`
- L74 _public function_ `virtual TSharedPtr<IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedPtr() override`
- L79 _public function_ `virtual TSharedPtr<const IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L84 _public function_ `virtual TSharedRef<IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedRef() override`
- L89 _public function_ `virtual TSharedRef<const IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedRef() const override`
- L94 _public function_ `virtual const IDisplayClusterViewportConfigurationProxy& GetConfigurationProxy() const override`
- L99 _public function_ `virtual EDisplayClusterViewportFlags GetViewportFlags() const override`
- L104 _public function_ `virtual FString GetBaseId() const override`
- L109 _public function_ `virtual FString GetId() const override`
- L115 _public function_ `virtual FString GetClusterNodeId() const override`
- L121 _public function_ `virtual const FDisplayClusterViewport_RenderSettings& GetRenderSettings_RenderThread() const override`
- L127 _public function_ `virtual const FDisplayClusterViewport_RenderSettingsICVFX& GetRenderSettingsICVFX_RenderThread() const override`
- L133 _public function_ `virtual const FDisplayClusterViewport_PostRenderSettings& GetPostRenderSettings_RenderThread() const override`
- L139 _public function_ `virtual const TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& GetProjectionPolicy_RenderThread() const override`
- L145 _public function_ `virtual const TArray<FDisplayClusterViewport_Context>& GetContexts_RenderThread() const override`
- L151 _public function_ `virtual const FDisplayClusterViewportFrameData& GetFrameData_RenderThread() const override`
- L157 _public function_ `virtual const FDisplayClusterViewportFrameData& GetPrevFrameData_RenderThread() const override`
- L163 _public function_ `virtual void SetRenderSettings_RenderThread(const FDisplayClusterViewport_RenderSettings& InRenderSettings) const override`
- L169 _public function_ `virtual void SetContexts_RenderThread(const TArray<FDisplayClusterViewport_Context>& InContexts) const override`
- L176 _public prototype_ `virtual FDisplayClusterColorEncoding GetResourceColorEncoding_RenderThread(const EDisplayClusterViewportResourceType InResourceType) const override;`
- L179 _public prototype_ `virtual bool GetResources_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources) const override;` — Return viewport scene proxy resources by type
- L180 _public prototype_ `virtual bool GetResourcesWithRects_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources, TArray<FIntRect>& OutRects) const override;`
- L183 _public prototype_ `virtual bool SetResourcesOverride_RenderThread(const EDisplayClusterViewportResourceType InResourceType, const TArray<FRHITexture*>& InResources, const TArray<FIntRect>* InOptRects = nullptr) const override;` — Per-frame resource overrides; shadow the normal resource-fetch path and are cleared each frame.
- L184 _public prototype_ `virtual bool GetResourcesOverride_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources, TArray<FIntRect>* OutOptRects = nullptr) const override;`
- L187 _public prototype_ `virtual bool ResolveResources_RenderThread(FRHICommandListImmediate& RHICmdList, const EDisplayClusterViewportResourceType InputResourceType, const EDisplayClusterViewportResourceType OutputResourceType, const int32 InContextNum = INDEX_NONE) const override;` — Resolve resource contexts
- L188 _public prototype_ `virtual bool ResolveResources_RenderThread(FRHICommandListImmediate& RHICmdList, IDisplayClusterViewportProxy* InputResourceViewportProxy, const EDisplayClusterViewportResourceType InputResourceType, const EDisplayClusterViewportResourceType OutputResourceType, const int32 InContextNum = INDEX_NONE) const override;`
- L199 _public prototype_ `static void FillTextureWithColor_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture* InRenderTargetTexture, const FLinearColor& InColor);` — Fill the entire texture with the specified color. @param InRenderTargetTexture - texture,  must be RTT. @param InColor - the texture will be filled with this color.
- L207 _public prototype_ `EDisplayClusterViewportResourceType GetResourceType_RenderThread(const EDisplayClusterViewportResourceType& InResourceType) const;` — Get valid resource type @param InResourceType - the requested resource type from the entire namespace @return - the type of resource actually used, depending on the current configuration of the rendering pipeline
- L216 _public prototype_ `FIntRect GetResourceRect_RenderThread(const EDisplayClusterViewportResourceType InResourceType, const uint32 InContextNum) const;` — Get actual region for viewport context @param InResourceType - the requested resource type from the entire namespace @param InContextNum - context num (eye) @return - InRect with applied overscan for RTT
- L224 _public prototype_ `void UpdateDeferredResources(FRHICommandListImmediate& RHICmdList) const;` — Resolve viewport RTT: render OCIO, PP, generate MIPS, etc. @param RHICmdList - RHI interface @return - none
- L230 _public prototype_ `void CleanupResources_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — Called at the end of the frame, after all callbacks. At the end, some resources may be filled with black, etc. This is useful because the resources are reused and the image from the previous frame goes into the new one.
- L240 _public prototype_ `void OnResolvedSceneColor_RenderThread(FRDGBuilder& GraphBuilder, const FSceneTextures& SceneTextures, const FDisplayClusterViewportProxy_Context& InProxyContext);` — nDisplay VE Callback [subscribed to Renderer:ResolvedSceneColorCallbacks]. @param GraphBuilder   - RDG interface @param SceneTextures  - Scene textures (SceneColor, Depth, etc) @param InProxyContext - Saved from game thread context for this proxy @return - none
- L251 _public prototype_ `void OnPostRenderViewFamily_RenderThread(FRDGBuilder& InGraphBuilder, FSceneViewFamily& InViewFamily, const FSceneView& InSceneView, const FDisplayClusterViewportProxy_Context& InProxyContext);` — nDisplay VE Callback [PostRenderViewFamily_RenderThread()]. @param GraphBuilder   - RDG interface @param InViewFamily   - Scene View Family @param InSceneView    - Scene View @param InProxyContext - Saved from game thread context for this proxy @return - none
- L254 _public prototype_ `bool ShouldUsePostProcessPassAfterFXAA() const;` — Allow callback OnPostProcessPassAfterFXAA.
- L265 _public prototype_ `FScreenPassTexture OnPostProcessPassAfterFXAA_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum);` — Callback OnPostProcessPassAfterFXAA. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @param ContextNum   - viewport context index @return - Screen pass texture
- L268 _public prototype_ `bool ShouldUsePostProcessPassAfterSSRInput() const;` — Allow callback OnPostProcessPassAfterSSRInput.
- L279 _public prototype_ `FScreenPassTexture OnPostProcessPassAfterSSRInput_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum);` — Callback OnPostProcessPassAfterSSRInput. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @param ContextNum   - viewport context index @return - Screen pass texture
- L282 _public prototype_ `bool ShouldUsePostProcessPassTonemap() const;` — Allow callback OnPostProcessPassAfterTonemap.
- L293 _public prototype_ `FScreenPassTexture OnPostProcessPassAfterTonemap_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum);` — Callback OnPostProcessPassAfterTonemap. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @param ContextNum   - viewport context index @return - Screen pass texture
- L296 _public prototype_ `bool ShouldUseAlphaChannel_RenderThread() const;` — Enable alpha channel for this viewport (useful for overlays with alpha channel: ChromaKey, LightCard).
- L304 _public prototype_ `void PostResolveViewport_RenderThread(FRHICommandListImmediate& RHICmdList) const;` — Finally, resolve the viewport to the output RTT and apply the last PPs (ViewportRemap, etc.) @param RHICmdList - RHI interface @return - none
- L307 _public prototype_ `void ReleaseAllResources_RenderThread();` — Release all resources on the rendering thread.
- L309 _public function_ `inline bool FindContext_RenderThread(const int32 ViewIndex, uint32* OutContextNum)`
- L331 _public prototype_ `bool ShouldApplyWarpBlend_RenderThread() const;` — Returns true if the warp can be applied to this viewport.
- L333 _public function_ `const FDisplayClusterViewportResources& GetResources_RenderThread() const`
- L338 _public prototype_ `void UpdateViewportProxyData_RenderThread(const class FDisplayClusterViewportProxyData& InViewportProxyData);`
- L343 _public prototype_ `uint8 GetPriority_RenderThread() const;` — Viewports should be processed in the appropriate order. Viewports with lower priority values will be processed earlier.
- L346 _public prototype_ `EDisplayClusterViewportOpenColorIOMode GetOpenColorIOMode() const;` — Returns the OCIO rendering type for the given viewport.
- L349 _public prototype_ `static class IDisplayClusterShaders& GetShadersAPI();` — Return shaders API.
- L352 _private prototype_ `bool ImplGetResourcesWithRects_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources, TArray<FIntRect>& OutResourceRects, const int32 InRecursionDepth) const;`
- L353 _private prototype_ `bool ImplGetResources_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources, const int32 InRecursionDepth) const;`
- L355 _private prototype_ `void ImplViewportRemap_RenderThread(FRHICommandListImmediate& RHICmdList) const;`
- L357 _private prototype_ `bool ImplResolveResources_RenderThread(FRHICommandListImmediate& RHICmdList, FDisplayClusterViewportProxy const* SourceProxy, const EDisplayClusterViewportResourceType InputResourceType, const EDisplayClusterViewportResourceType OutputResourceType, const int32 InContextNum = INDEX_NONE) const;`
- L360 _private prototype_ `void ImplResolveTileResource_RenderThread(FRHICommandListImmediate& RHICmdList, FDisplayClusterViewportProxy const* InDestViewportProxy) const;` — Copy the tile to the target viewport.
- L366 _private prototype_ `bool ShouldApplyFXAA_RenderThread(EFXAAQuality& OutFXAAQuality) const;` — Returns true if this viewport requires FXAA to be applied. @param OutFXAAQuality - (out) FXAA shader parameter that define quality level.
- L369 _private prototype_ `bool ShouldOverrideViewportResource(const EDisplayClusterViewportResourceType InResourceType) const;` — When a resource by type can be overridden from another viewport, true is returned.
- L375 _private prototype_ `const FDisplayClusterViewportProxy& GetRenderingViewportProxy() const;` — Return viewport used to render RTT (support ViewportOverride) @return - viewport proxy with valid render resources
- L378 _private prototype_ `bool IsInputRenderTargetResourceExists() const;` — Check if there is an RTT source (internal or external) in this viewport proxy.
- L381 _private prototype_ `bool IsPostProcessDisabled() const;` — Return true if postprocess is disbled for this viewport.
- L384 _private prototype_ `const FDisplayClusterViewport_Context::FRenderThreadData& GetEffectiveRenderThreadData(const int32 InContextNum) const;` — Returns the render thread data for the given context, preferring captured data over current frame data.
- L388 _public member_ `const TSharedRef<FDisplayClusterViewportConfigurationProxy, ESPMode::ThreadSafe> ConfigurationProxy;` — Configuration for proxy
- L392 _public member_ `const FString ViewportBaseId;` — Base viewport identifier. May not be unique across ICVFX viewports (multiple viewports can share the same base ID).
- L395 _public member_ `const EDisplayClusterViewportFlags ViewportFlags;` — Usage type of the viewport (e.g. InCamera, Chromakey, LightCard).
- L399 _public member_ `const FString ViewportId;` — Final unique viewport identifier. Guaranteed to be unique across the entire cluster (includes node ID and usage type if needed).
- L402 _public member_ `const FString ClusterNodeId;` — Cluster node name.
- L406 _protected member_ `TSharedPtr<FDisplayClusterViewport_OpenColorIO, ESPMode::ThreadSafe> OpenColorIO;` — OpenColorIO nDisplay interface ref.
- L409 _protected member_ `TSharedPtr<IDisplayClusterDisplayDeviceProxy, ESPMode::ThreadSafe> DisplayDeviceProxy;` — Display Device Proxy.
- L412 _protected member_ `mutable FDisplayClusterViewport_RenderSettings RenderSettings;` — Viewport render params
- L414 _protected member_ `FDisplayClusterViewport_RenderSettingsICVFX RenderSettingsICVFX;`
- L415 _protected member_ `FDisplayClusterViewport_PostRenderSettings PostRenderSettings;`
- L418 _protected member_ `FDisplayClusterViewport_OverscanRuntimeSettings OverscanRuntimeSettings;` — Additional parameters
- L420 _protected member_ `TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> RemapMesh;`
- L423 _protected member_ `TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> ProjectionPolicy;` — Projection policy instance that serves this viewport
- L426 _protected member_ `FDisplayClusterViewportFrameData CurrentFrameData;` — Frame data snapshot for the current frame (contexts, cached view info).
- L429 _protected member_ `TArray<FDisplayClusterViewport_Context>& Contexts;` — Legacy reference alias to the current frame's viewport contexts stored in CurrentFrameData.Contexts.
- L432 _protected member_ `FDisplayClusterViewportFrameData PreviousFrameData;` — Frame data snapshot from the previous frame; used for motion blur and temporal effects.
- L435 _protected member_ `TMap<int32, FDisplayClusterViewport_Context::FRenderThreadData> CapturedRenderThreadData;` — Per-context render-thread data (eye adaptation, etc.) captured in OnPostRenderViewFamily_RenderThread().
- L438 _protected member_ `FDisplayClusterViewportResources Resources;` — Unified repository of viewport resources
- L441 _protected member_ `TArray<TSharedPtr<FSceneViewStateReference, ESPMode::ThreadSafe>> ViewStates;` — Used ViewStates
- L453 _private member_ `mutable TMap<EDisplayClusterViewportResourceType, TArray<FResourceWithRect>> TransientRHIOverrides;` — Per-frame external resource overrides set via SetResourcesOverride_RenderThread(). Entries shadow the normal resource-fetch path for the current frame only and are cleared at the start of the next frame.

#### struct `FDisplayClusterViewportProxy::FResourceWithRect`  
`struct FResourceWithRect`  
_L445-449_
- desc: A raw RHI texture paired with the subrect it occupies within that texture.
- L447 _public member_ `FRHITexture* Texture = nullptr;`
- L448 _public member_ `FIntRect Rect;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportResources.h` (Private)


#### enum `EDisplayClusterViewportResource`  
`enum class EDisplayClusterViewportResource : uint8`  
_L17-48_
- desc: Internal types of DC viewport resources These types are used to point to actual instances of the resources in the viewport.
- L23 _public enumerator_ `RenderTargets` — View family render to this resources This is the resource that can be pointed to using the enum values: - 'EDisplayClusterViewportResourceType::InternalRenderTargetEntireRectResource' - 'EDisplayClusterViewportResourceType::InternalRenderTargetResource'
- L27 _public enumerator_ `InputShaderResources` — unique viewport resources This is the resource that can be pointed to using the enum 'EDisplayClusterViewportResourceType::InputShaderResource' value.
- L31 _public enumerator_ `AdditionalTargetableResources` — unique viewport resources This is the resource that can be pointed to using the enum 'EDisplayClusterViewportResourceType::AdditionalTargetableResource' value.
- L35 _public enumerator_ `MipsShaderResources` — unique viewport resources This is the resource that can be pointed to using the enum 'EDisplayClusterViewportResourceType::MipsShaderResource' value.
- L39 _public enumerator_ `OutputPreviewTargetableResources` — Projection policy output resources This is the resource that can be pointed to using the enum 'EDisplayClusterViewportResourceType::OutputPreviewTargetableResource' value.
- L43 _public enumerator_ `OutputFrameTargetableResources` — Projection policy output resources This is the resource that can be pointed to using the enum 'EDisplayClusterViewportResourceType::OutputFrameTargetableResource' value.
- L47 _public enumerator_ `AdditionalFrameTargetableResources` — Projection policy output resources This is the resource that can be pointed to using the enum 'EDisplayClusterViewportResourceType::AdditionalFrameTargetableResource' value.

#### class `FDisplayClusterViewportResources`  
`class FDisplayClusterViewportResources`  
_L51-129_
- desc: Helper class for unified viewport resource repository.
- L54 _public prototype_ `FDisplayClusterViewportResources() = default;`
- L55 _public prototype_ `~FDisplayClusterViewportResources() = default;`
- L59 _public function_ `TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>>& operator[](const EDisplayClusterViewportResource InResourceType)` — Get viewport resources for all contexts by type.
- L70 _public function_ `const TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>>& operator[](const EDisplayClusterViewportResource InResourceType) const` — Get viewport const resources for all contexts by type.
- L82 _public function_ `void ReleaseAllResources()` — Release refs to all viewport resources.
- L91 _public function_ `void ReleaseNotSharedResources()` — Release only part of the resources, leaving resources that can be used by other viewports(viewport override feature) Discard resources that are not used in frame composition
- L101 _public prototype_ `void FreezeRendering(const EDisplayClusterViewportResource InResourceType);` — Raise DisableReallocate flag for all viewport resources of specified type. Support render freeze feature
- L111 _public prototype_ `bool GetRHIResources_RenderThread(const EDisplayClusterViewportResource InResourceType, TArray<FRHITexture*>& OutResources) const;` — Get viewport RHI resources @param InResourceType - The type of resources you want to retrieve. @param OutResources - Array with RHI resources @return true, if all resources are valid
- L115 _protected function_ `inline void ImplRelease(const EDisplayClusterViewportResource InResourceType)` — Release specified type of resources.
- L125 _private member_ `TMap<EDisplayClusterViewportResource, TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>>> ViewportResources;` — Unified repository of viewport resources
- L128 _private member_ `const static TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>> EmptyResources;` — This value is used for const-functions when resources are not defined

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportStereoscopicPass.h` (Private)


#### struct `FDisplayClusterViewportStereoscopicPass`  
`struct FDisplayClusterViewportStereoscopicPass`  
_L9-60_
- L12 _public member_ `static constexpr int32 StereoViewIndexBase = 100;` — Base of the reserved StereoViewIndex range for nDisplay; engine indices are below this.
- L17 _public function_ `inline static bool IsValidStereoViewIndex(const int32 ViewIndex)` — True if this view index falls in the nDisplay-reserved range.
- L26 _public function_ `inline static EStereoscopicPass EncodeStereoscopicPass(const uint32 ContextNum, const uint32 ContextAmount, const FDisplayClusterRenderFrameSettings& InFrameSettings)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewport_CustomPostProcessSettings.h` (Private)


#### class `FDisplayClusterViewport_CustomPostProcessSettings`  
`class FDisplayClusterViewport_CustomPostProcessSettings : public IDisplayClusterViewport_CustomPostProcessSettings`  
_L11-64_
- inherits: `IDisplayClusterViewport_CustomPostProcessSettings`
- L15 _public prototype_ `FDisplayClusterViewport_CustomPostProcessSettings() = default;`
- L16 _public prototype_ `virtual ~FDisplayClusterViewport_CustomPostProcessSettings() = default;`
- L20 _public prototype_ `virtual void AddCustomPostProcess(const ERenderPass InRenderPass, const FPostProcessSettings& InSettings, float BlendWeight, bool bSingleFrame) override;`
- L21 _public prototype_ `virtual void RemoveCustomPostProcess(const ERenderPass InRenderPass) override;`
- L23 _public prototype_ `virtual bool ApplyCustomPostProcess(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const ERenderPass InRenderPass, FPostProcessSettings& InOutPPSettings, float* InOutBlendWeight = nullptr) const override;`
- L26 _public prototype_ `void FinalizeFrame();`
- L32 _private prototype_ `bool GetCustomPostProcess(const ERenderPass InRenderPass, FPostProcessSettings& OutSettings, float* OutBlendWeight) const;` — Get the custom postprocess settings for the specified rendering pass. Returns false if no custom post process exists for the specified InRenderPass.
- L43 _private prototype_ `bool ConfigurePostProcessSettingsForViewport(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const ERenderPass InRenderPass, FPostProcessSettings& InOutPostProcessSettings) const;` — Applies changes to some postprocessing parameters depending on the viewport context. (DoF, etc.) @param InViewport       - DC viewport that is rendered with these settings. @param InContextNum     - Index of view that is being processed for this viewport @param InRenderPass     - PP rendering pass to be used. (The value of 'FinalPerViewport' is ignored.) @param InOutPPSettings  - (in,out) PostProcess settings that need to be changed. @return true, if the postprocess settings have been modified.
- L63 _private member_ `TMap<ERenderPass, FPostprocessData> PostprocessAsset;` — Custom post processing settings

#### struct `FDisplayClusterViewport_CustomPostProcessSettings::FPostprocessData`  
`struct FPostprocessData`  
_L46-60_
- L48 _public member_ `FPostProcessSettings Settings;`
- L50 _public member_ `float BlendWeight = 1.f;`
- L52 _public member_ `bool bIsEnabled = true;`
- L53 _public member_ `bool bIsSingleFrame = false;`
- L55 _public function_ `FPostprocessData(const FPostProcessSettings& InSettings, float InBlendWeight, bool bInSingleFrame) : Settings(InSettings) , BlendWeight(InBlendWeight) , bIsSingleFrame(bInSingleFrame)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewport_OpenColorIO.h` (Private)


#### class `FDisplayClusterViewport_OpenColorIO`  
`class FDisplayClusterViewport_OpenColorIO : public TSharedFromThis<FDisplayClusterViewport_OpenColorIO, ESPMode::ThreadSafe>`  
_L28-91_
- inherits: `TSharedFromThis<FDisplayClusterViewport_OpenColorIO,ESPMode::ThreadSafe>`
- desc: nDisplay OCIO implementation.
- L32 _public prototype_ `FDisplayClusterViewport_OpenColorIO(const FOpenColorIOColorConversionSettings& InDisplayConfiguration);`
- L33 _public prototype_ `virtual ~FDisplayClusterViewport_OpenColorIO();`
- L43 _public prototype_ `void SetupSceneView(FSceneViewFamily& InOutViewFamily, FSceneView& InOutView);` — Setup view for OCIO. @param InOutViewFamily - [In,Out] ViewFamily. @param InOutView       - [In,Out] View. @return - none.
- L51 _public prototype_ `bool AddPass_RenderThread( const struct FDisplayClusterShadersTextureUtilsSettings& InTextureUtilsSettings, const TSharedRef<class IDisplayClusterShadersTextureUtils>& TextureUtils) const;` — Add OCIO render pass. @param TextureUtils   - resolving data @return - true if success.
- L56 _public prototype_ `FScreenPassTexture PostProcessPassAfterTonemap_RenderThread(FRDGBuilder& GraphBuilder, const FDisplayClusterColorEncoding& InColorEncoding, const FSceneView& View, const FPostProcessMaterialInputs& InOutInputs);` — This is a copy of FOpenColorIODisplayExtension::PostProcessPassAfterTonemap_RenderThread()
- L65 _public prototype_ `bool IsConversionSettingsEqual(const FOpenColorIOColorConversionSettings& InConversionSettings) const;` — Compare two OCIO configurations. @param InConversionSettings - configuration to compare with. @return - true if equal.
- L68 _public function_ `const FOpenColorIOColorConversionSettings& GetConversionSettings() const` — Get current OCIO conversion settings.
- L74 _public function_ `bool IsValid_RenderThread() const` — Returns true if OCIO can be used in the rendering thread.
- L80 _public prototype_ `static float GetGammaCorrection(const FDisplayClusterColorEncoding& InColorEncoding);` — Gets the gamma correction for the OCIO shader from the InColorEncoding parameter.
- L83 _public prototype_ `static EOpenColorIOTransformAlpha GetTransformAlpha(const FDisplayClusterColorEncoding& InColorEncoding);` — Gets transform alpha value from the InColorEncoding parameter.
- L87 _private member_ `FOpenColorIORenderPassResources CachedResourcesRenderThread;` — Cached pass resources required to apply conversion for render thread.
- L90 _private member_ `FOpenColorIOColorConversionSettings ConversionSettings;` — Configuration to apply during post render callback.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewport_VisibilitySettings.h` (Private)


#### enum `EDisplayClusterViewport_VisibilityMode`  
`enum class EDisplayClusterViewport_VisibilityMode : uint8`  
_L14-19_
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `ShowOnly`
- L18 _public enumerator_ `Hide`

#### class `FDisplayClusterViewport_VisibilitySettings`  
`class FDisplayClusterViewport_VisibilitySettings`  
_L22-89_
- desc: GameThread-only data
- L25 _public prototype_ `virtual ~FDisplayClusterViewport_VisibilitySettings() = default;`
- L29 _public function_ `void BeginUpdateSettings()` — Reset actor layers visibility rules
- L37 _public function_ `const TSet<FPrimitiveComponentId>& GetComponentsList() const` — Return components list.
- L43 _public function_ `void SetVisibilityModeAndComponentsList(EDisplayClusterViewport_VisibilityMode InVisibilityMode, const TSet<FPrimitiveComponentId>& InComponentsList)` — Sets the visibility mode and component list.
- L51 _public function_ `bool AppendVisibilityComponentsList(EDisplayClusterViewport_VisibilityMode InVisibilityMode, const TSet<FPrimitiveComponentId>& InComponentsList)` — Adds components to the list. Must be called after SetVisibilityModeAndComponentsList().
- L64 _public function_ `void AddExcludedComponents(const TSet<FPrimitiveComponentId>& InComponentsList)` — Exclude these components from the output list.
- L70 _public function_ `bool IsVisible() const` — Returns true if this viewport contains any geometry and can be rendered.
- L81 _public prototype_ `void SetupSceneView(const FDisplayClusterViewport& Owner, FSceneView& InOutView) const;` — Configure InOutView using the viewport settings.
- L84 _private member_ `EDisplayClusterViewport_VisibilityMode VisibilityMode = EDisplayClusterViewport_VisibilityMode::None;`
- L85 _private member_ `TSet<FPrimitiveComponentId> ComponentsList;`
- L88 _private member_ `TSet<FPrimitiveComponentId> ExcludedComponents;` — Exclude this components from ComponentsList

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/LightCard/DisplayClusterViewportLightCardEnums.h` (Private)


#### enum `EDisplayClusterUVLightCardRenderMode`  
`enum class EDisplayClusterUVLightCardRenderMode : uint8`  
_L8-21_
- desc: Consolidated UV light card rendering mode for the current cluster node.
- L11 _public enumerator_ `Default` — Use light card render mode from the StageSettings
- L14 _public enumerator_ `AlwaysOver` — The lightcard will always be displayed only "Over the In-Camera".
- L17 _public enumerator_ `AlwaysUnder` — The lightcard will always be displayed only "Under the In-Camera".
- L20 _public enumerator_ `Disabled` — Lighting maps are not used.

#### enum `EDisplayClusterUVLightCardType`  
`enum class EDisplayClusterUVLightCardType: uint8`  
_L24-31_
- desc: The UV lightcards have 2 type: 'Under' and 'Over'.
- L27 _public enumerator_ `Under` — The UV lightcards that are displayed under inner frustum.
- L30 _public enumerator_ `Over` — The UV lightcards that are displayed over inner frustum.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/LightCard/DisplayClusterViewportLightCardManager.h` (Private)


#### class `FDisplayClusterViewportLightCardManager`  
`class FDisplayClusterViewportLightCardManager : public FGCObject`  
_L19-117_
- inherits: `FGCObject`
- desc: Manages the rendering of UV light cards for the viewport manager (Game Thread object)
- L23 _public prototype_ `FDisplayClusterViewportLightCardManager(const TSharedRef<const FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L24 _public prototype_ `virtual ~FDisplayClusterViewportLightCardManager();`
- L26 _public prototype_ `void Release();`
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L30 _public function_ `virtual FString GetReferencerName() const override`
- L35 _public prototype_ `bool IsUVLightCardEnabled(const EDisplayClusterUVLightCardType InUVLightCardType) const;` — Return true if UV LightCard is used in this frame.
- L38 _public prototype_ `FIntPoint GetUVLightCardResourceSize(const EDisplayClusterUVLightCardType InUVLightCardType) const;` — Get UV LightCard texture size.
- L42 _public prototype_ `void OnHandleStartScene();` — Handle StartScene event: created and update internal resources.
- L45 _public prototype_ `void OnHandleEndScene();` — Handle EndScene event: release internal resources.
- L48 _public prototype_ `void RenderFrame();` — Render internal resoures for current frame.
- L52 _private prototype_ `void RenderUVLightCard(const EDisplayClusterUVLightCardType InUVLightCardType);` — Render UVLightCard
- L55 _private prototype_ `void UpdateUVLightCardResource(const EDisplayClusterUVLightCardType InUVLightCardType);` — Update the UV light card map texture
- L58 _private prototype_ `void ReleaseUVLightCardResource(const EDisplayClusterUVLightCardType InUVLightCardType);` — Releases the UV light card map texture
- L61 _private prototype_ `void CreateUVLightCardResource(const FIntPoint& InResourceSize, const EDisplayClusterUVLightCardType InUVLightCardType);` — Create the UV light card map texture
- L64 _private prototype_ `void UpdateUVLightCardData(const EDisplayClusterUVLightCardType InUVLightCardType);` — Update UVLightCard data game thread
- L67 _private prototype_ `void ReleaseUVLightCardData(const EDisplayClusterUVLightCardType InUVLightCardType);` — Release UVLightCard data game thread
- L76 _private prototype_ `EDisplayClusterUVLightCardRenderMode GetUVLightCardRenderMode() const;` — Returns the consolidated UV-light card rendering mode for the current cluster node. If the light card override mode is the same for all viewports of the current cluster node, return this value. Or returns 'None' if they do not.
- L78 _private function_ `TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe>& GetUVLightCardResource(const EDisplayClusterUVLightCardType InUVLightCardType)`
- L83 _private function_ `const TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe>& GetUVLightCardResource(const EDisplayClusterUVLightCardType InUVLightCardType) const`
- L88 _private function_ `TArray<UPrimitiveComponent*>& GetUVLightCardPrimitiveComponents(const EDisplayClusterUVLightCardType InUVLightCardType)`
- L93 _private function_ `const TArray<UPrimitiveComponent*>& GetUVLightCardPrimitiveComponents(const EDisplayClusterUVLightCardType InUVLightCardType) const`
- L100 _public member_ `const TSharedRef<const FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L103 _public member_ `const TSharedRef<FDisplayClusterViewportLightCardManagerProxy, ESPMode::ThreadSafe> LightCardManagerProxy;` — RenderThread Proxy object
- L107 _private member_ `TArray<UPrimitiveComponent*> UVLightCardUnderPrimitiveComponents;` — A list of primitive components that have been added to the preview scene for rendering in the current frame
- L110 _private member_ `TArray<UPrimitiveComponent*> UVLightCardOverPrimitiveComponents;` — A list of primitive components that have been added to the preview scene for rendering in the current frame
- L113 _private member_ `TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe> UVLightCardUnderResource;` — The render target to which the UV light card map is rendered
- L116 _private member_ `TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe> UVLightCardOverResource;` — The render target to which the UV light card map is rendered

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/LightCard/DisplayClusterViewportLightCardManagerProxy.h` (Private)


#### class `FDisplayClusterViewportLightCardManagerProxy`  
`class FDisplayClusterViewportLightCardManagerProxy : public TSharedFromThis<FDisplayClusterViewportLightCardManagerProxy, ESPMode::ThreadSafe>`  
_L19-60_
- inherits: `TSharedFromThis<FDisplayClusterViewportLightCardManagerProxy,ESPMode::ThreadSafe>`
- desc: Manages the rendering of UV light cards for the viewport manager (Render Thread proxy object)
- L23 _public prototype_ `virtual ~FDisplayClusterViewportLightCardManagerProxy();`
- L26 _public prototype_ `void UpdateUVLightCardResource(const TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe>& InUVLightCardMapResource, const EDisplayClusterUVLightCardType InUVLightCardType);` — Update UVLightCard resource.
- L29 _public prototype_ `void ReleaseUVLightCardResource(const EDisplayClusterUVLightCardType InUVLightCardType);` — Release UVLightCard resource.
- L32 _public prototype_ `void RenderUVLightCard(FSceneInterface* InSceneInterface, const FDisplayClusterShaderParameters_UVLightCards& InParameters, const EDisplayClusterUVLightCardType InUVLightCardType) const;` — Render UVLightCard.
- L35 _public prototype_ `FRHITexture* GetUVLightCardRHIResource_RenderThread(const EDisplayClusterUVLightCardType InUVLightCardType) const;` — Get current UVLightCard RHI resource on rendering thread.
- L38 _protected prototype_ `void ImplUpdateUVLightCardResource_RenderThread(const TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe>& InUVLightCardMapResource, const EDisplayClusterUVLightCardType InUVLightCardType);`
- L39 _protected prototype_ `void ImplReleaseUVLightCardResource_RenderThread(const EDisplayClusterUVLightCardType InUVLightCardType);`
- L42 _protected prototype_ `void ImplRenderUVLightCard_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneInterface* InScene, const FDisplayClusterShaderParameters_UVLightCards& InParameters, const EDisplayClusterUVLightCardType InUVLightCardType) const;` — Render UV-lightcards to texture (the layer is defined by the bOverInFrustum parameter.).
- L44 _protected function_ `TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe>& GetUVLightCardMapResource(const EDisplayClusterUVLightCardType InUVLightCardType)`
- L49 _protected function_ `const TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe>& GetUVLightCardMapResource(const EDisplayClusterUVLightCardType InUVLightCardType) const`
- L56 _private member_ `TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe> UVLightCardUnderMapResource;` — The render thread copy of the pointer to the UV light card map
- L59 _private member_ `TSharedPtr<FDisplayClusterViewportLightCardResource, ESPMode::ThreadSafe> UVLightCardOverMapResource;` — The render thread copy of the pointer to the UV light card map

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/LightCard/DisplayClusterViewportLightCardResource.h` (Private)


#### class `FDisplayClusterViewportLightCardResource`  
`class FDisplayClusterViewportLightCardResource : public FTexture , public FRenderTarget`  
_L12-33_
- inherits: `FTexture,FRenderTarget`
- desc: A render targetable texture resource used to render the light cards to.
- L17 _public function_ `FDisplayClusterViewportLightCardResource(const FIntPoint& InLightCardResourceSize) : LightCardResourceSize(InLightCardResourceSize)`
- L21 _public prototype_ `virtual ~FDisplayClusterViewportLightCardResource() = default;`
- L23 _public function_ `virtual uint32 GetSizeX() const override`
- L24 _public function_ `virtual uint32 GetSizeY() const override`
- L25 _public function_ `virtual FIntPoint GetSizeXY() const override`
- L27 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L29 _public function_ `virtual FString GetFriendlyName() const override`
- L32 _private member_ `FIntPoint LightCardResourceSize;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Postprocess/DisplayClusterViewportPostProcessManager.h` (Private)


#### class `FDisplayClusterViewportPostProcessManager`  
`class FDisplayClusterViewportPostProcessManager : public TSharedFromThis<FDisplayClusterViewportPostProcessManager, ESPMode::ThreadSafe>`  
_L18-107_
- inherits: `TSharedFromThis<FDisplayClusterViewportPostProcessManager,ESPMode::ThreadSafe>`
- L22 _public prototype_ `FDisplayClusterViewportPostProcessManager(const TSharedRef<const FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L23 _public prototype_ `virtual ~FDisplayClusterViewportPostProcessManager();`
- L25 _public prototype_ `void Release_GameThread();`
- L28 _public prototype_ `bool IsPostProcessViewBeforeWarpBlendRequired(const TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>& PostprocessInstance) const;`
- L29 _public prototype_ `bool IsPostProcessViewAfterWarpBlendRequired(const TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>& PostprocessInstance) const;`
- L30 _public prototype_ `bool IsPostProcessFrameAfterWarpBlendRequired(const TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>& PostprocessInstance) const;`
- L32 _public prototype_ `bool IsAnyPostProcessRequired(const TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>& PostprocessInstance) const;`
- L34 _public prototype_ `bool ShouldUseAdditionalFrameTargetableResource() const;`
- L35 _public prototype_ `bool ShouldUseFullSizeFrameTargetableResource() const;`
- L37 _public prototype_ `void PerformPostProcessViewBeforeWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy) const;`
- L38 _public prototype_ `void PerformPostProcessViewAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy) const;`
- L39 _public prototype_ `void PerformPostProcessFrameAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy) const;`
- L41 _public prototype_ `void Tick();`
- L43 _public prototype_ `bool OnHandleStartScene();`
- L44 _public prototype_ `void OnHandleEndScene();`
- L46 _public prototype_ `void HandleSetupNewFrame();`
- L47 _public prototype_ `void HandleBeginNewFrame(FDisplayClusterRenderFrame& InOutRenderFrame);`
- L49 _public prototype_ `void HandleRenderFrameSetup_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy);`
- L51 _public prototype_ `void HandleBeginUpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy);`
- L52 _public prototype_ `void HandleUpdateFrameResourcesAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy);`
- L53 _public prototype_ `void HandleEndUpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy);`
- L56 _public prototype_ `void FinalizeNewFrame();` — Send data to render thread
- L58 _public function_ `TSharedPtr<FDisplayClusterViewportPostProcessOutputRemap, ESPMode::ThreadSafe>& GetOutputRemap()`
- L74 _public prototype_ `bool CanBeCreated(const FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess) const;` — Special rules for creating a PP instance. Note: This function must be called before Create() on the nDisplay side. (useful to avoid unnecessary nDisplay log messages). For example, some postprocess types may use an instance as a singleton. In this case, Create() returns nullptr if the PP instance already exists, and as a result nDisplay issues an error message to the log, and then avoids creating this PP in the future. @param InConfigurationPostProcess - postprocess configuration @return true if a postprocess with this type can be created at this time.
- L76 _public prototype_ `bool CreatePostprocess(const FString& InPostprocessId, const FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess);`
- L77 _public prototype_ `bool RemovePostprocess(const FString& InPostprocessId);`
- L78 _public prototype_ `bool UpdatePostprocess(const FString& InPostprocessId, const FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess);`
- L80 _public prototype_ `const TArray<FString> GetPostprocess() const;`
- L81 _public function_ `TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe> FindPostProcess(const FString& InPostprocessId) const`
- L87 _private prototype_ `TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe> ImplFindPostProcess(const FString& InPostprocessId) const;`
- L90 _protected prototype_ `void ImplPerformPostProcessViewBeforeWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy) const;`
- L91 _protected prototype_ `void ImplPerformPostProcessViewAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy) const;`
- L92 _protected prototype_ `void ImplPerformPostProcessFrameAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const FDisplayClusterViewportManagerProxy* InViewportManagerProxy) const;`
- L96 _public member_ `const TSharedRef<const FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L100 _private member_ `TArray<TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>> Postprocess;` — Game thread instances
- L103 _private member_ `TArray<TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>> PostprocessProxy;` — Render thread instances
- L106 _private member_ `TSharedPtr<FDisplayClusterViewportPostProcessOutputRemap, ESPMode::ThreadSafe> OutputRemap;` — Output remap implementation

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Postprocess/DisplayClusterViewportPostProcessOutputRemap.h` (Private)


#### class `FDisplayClusterViewportPostProcessOutputRemap`  
`class FDisplayClusterViewportPostProcessOutputRemap`  
_L19-48_
- desc: Display Cluster Viewport PostProcess OutputRemap
- L23 _public prototype_ `bool UpdateConfiguration_ExternalFile(const FString& InExternalFile);` — Game thread update calls
- L24 _public prototype_ `bool UpdateConfiguration_StaticMesh(UStaticMesh* InStaticMesh);`
- L25 _public prototype_ `bool UpdateConfiguration_StaticMeshComponent(UStaticMeshComponent* InStaticMeshComponent);`
- L26 _public prototype_ `bool UpdateConfiguration_ProceduralMeshComponent(UProceduralMeshComponent* InProceduralMeshComponent);`
- L27 _public prototype_ `void UpdateConfiguration_Disabled();`
- L29 _public prototype_ `bool MarkProceduralMeshComponentGeometryDirty(const FName& InComponentName);`
- L31 _public function_ `bool IsEnabled() const`
- L37 _public prototype_ `void PerformPostProcessFrame_RenderThread(FRHICommandListImmediate& RHICmdList, const TArray<FRHITexture*>* InFrameTargets = nullptr, const TArray<FRHITexture*>* InAdditionalFrameTargets = nullptr) const;`
- L40 _private prototype_ `bool ImplInitializeOutputRemap();`
- L44 _private member_ `FString ExternalFile;` — Name of the external file used for remapping. Empty if not used.
- L47 _private member_ `TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> OutputRemapMesh;` — Reference to the mesh component that is used for remapping.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Preview/DisplayClusterViewportManagerPreview.h` (Private)


#### class `FDisplayClusterViewportManagerPreview`  
`class FDisplayClusterViewportManagerPreview : public IDisplayClusterViewportManagerPreview , public TSharedFromThis<FDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe>`  
_L17-120_
- inherits: `IDisplayClusterViewportManagerPreview,TSharedFromThis<FDisplayClusterViewportManagerPreview,ESPMode::ThreadSafe>`
- desc: Store and manage preview resources of the viewport
- L22 _public prototype_ `FDisplayClusterViewportManagerPreview(const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L23 _public prototype_ `virtual ~FDisplayClusterViewportManagerPreview() = default;`
- L27 _public function_ `virtual TSharedPtr<IDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe> ToSharedPtr() override`
- L32 _public function_ `virtual TSharedPtr<const IDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L37 _public function_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() override`
- L42 _public function_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const override`
- L47 _public prototype_ `virtual void UpdateEntireClusterPreviewRender(bool bEnablePreviewRendering) override;`
- L48 _public prototype_ `virtual void ResetEntireClusterPreviewRendering() override;`
- L50 _public prototype_ `virtual bool InitializeClusterNodePreview(const EDisplayClusterRenderFrameMode InRenderMode, UWorld* InWorld, const FString& InClusterNodeId, FViewport* InViewport) override;`
- L51 _public prototype_ `virtual int32 RenderClusterNodePreview(const int32 InViewportsAmmount, FViewport* InViewport = nullptr, FCanvas* SceneCanvas = nullptr) override;`
- L53 _public prototype_ `virtual const TArray<TSharedPtr<IDisplayClusterViewportPreview, ESPMode::ThreadSafe>> GetEntireClusterPreviewViewports() const override;`
- L55 _public function_ `virtual FOnOnClusterNodePreviewGenerated& GetOnClusterNodePreviewGenerated() override`
- L60 _public function_ `virtual FOnOnEntireClusterPreviewGenerated& GetOnEntireClusterPreviewGenerated() override`
- L68 _public prototype_ `void RegisterPreviewRendering();` — Register this class with the preview rendering pipeline.
- L71 _public prototype_ `void UnregisterPreviewRendering();` — Remove this class from the preview rendering pipeline.
- L74 _public prototype_ `void OnPreviewRenderTick();` — Rendering multiple viewports from the entire cluster. These numbers are in the preview settings.
- L77 _public prototype_ `void OnPostRenderPreviewTick();` — Rendering of special debug objects after preview (Frustum, etc.).
- L80 _public prototype_ `void Update();` — Update viewports preview.
- L83 _public prototype_ `void Release();` — Release viewports preview.
- L87 _protected prototype_ `const TArray<TSharedPtr<FDisplayClusterViewportPreview, ESPMode::ThreadSafe>> GetEntireClusterPreviewViewportsImpl() const;` — Retrieve viewport preview instances for the entire cluster.
- L90 _protected prototype_ `void RenderFrustumPreviewForViewport(IDisplayClusterViewport* InViewport);` — Render frustum for viewport.
- L93 _protected prototype_ `FString GetClusterNodeId() const;` — Getting the cluster node ID for preview.
- L96 _protected prototype_ `void RenderPreviewFrustums();` — Render preview frustums.
- L99 _protected prototype_ `bool RenderViewportPreview(FViewport* InViewport, FCanvas* InSceneCanvas);` — Render ViewFamily with viewport.
- L103 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L106 _private member_ `FOnOnEntireClusterPreviewGenerated OnEntireClusterPreviewGenerated;`
- L107 _private member_ `FOnOnClusterNodePreviewGenerated OnClusterNodePreviewGenerated;`
- L110 _private member_ `bool bEntireClusterPreview = false;` — Is entire cluster preview in scene is used
- L113 _private member_ `bool bEntireClusterRendered = false;` — true when entire cluster was rendered
- L116 _private member_ `int32 TickPerFrameCounter = 0;` — The OnPreviewRenderTick() function may be executed only once per multiple frames depending on the settings.
- L119 _private member_ `TUniquePtr<FDisplayClusterRenderFrame> PreviewRenderFrame;` — This render frame created for a cluster node

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Preview/DisplayClusterViewportManagerPreviewRendering.h` (Private)


#### enum `EDisplayClusteViewportManagerPreviewRenderingEvent`  
`enum class EDisplayClusteViewportManagerPreviewRenderingEvent : uint8`  
_L13-27_
- desc: Preview manager receive events from DCRAs
- L16 _public enumerator_ `Create = 0` — Viewport manager preview was created
- L19 _public enumerator_ `Remove` — Viewport manager preview was removed
- L23 _public enumerator_ `Render` — Request from viewport manager for one time preview rendering. This event must be called many times to render the entire cluster.
- L26 _public enumerator_ `Stop` — Request from viewport manager for stop preview rendering.

#### class `FDisplayClusterViewportManagerPreviewRenderingInstance`  
`class FDisplayClusterViewportManagerPreviewRenderingInstance`  
_L32-96_
- desc: Container for ViewportManagerPreview instances that are used for preview rendering.
- L35 _public prototype_ `FDisplayClusterViewportManagerPreviewRenderingInstance() = default;`
- L36 _public function_ `FDisplayClusterViewportManagerPreviewRenderingInstance(const TSharedRef<FDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe>& InViewportManagerPreview) : ViewportManagerPreviewWeakPtr(InViewportManagerPreview)`
- L42 _public function_ `inline bool ShouldRenderPreview() const` — Returns true if the ViewportManager preview can be performed right now.
- L48 _public function_ `inline void MarkAsRendered()` — Changes the internal flags of this ViewportManager container to a state indicating that the preview rendering is complete.
- L55 _public function_ `inline void MarkAsNotRendered()` — Changes the internal flags of this ViewportManager container to a state that allows render previews.
- L61 _public function_ `inline bool IsEqual(const FDisplayClusterViewportManagerPreview* InViewportManagerPreview) const` — Returns true if the InRootActor is the same as the one used inside this container.
- L67 _public function_ `inline FDisplayClusterViewportManagerPreview* GetViewportManagerPreview() const` — Return the pointer to the ViewportManager preview.
- L73 _public prototype_ `void HandleRenderRequest();` — When ViewportManager tries to call the preview rendering, this function will be called.
- L75 _public function_ `void HandleStopRenderRequest()`
- L82 _public prototype_ `void RenderPreview() const;` — Performs a preview of the rendering for ViewportManager in this container.
- L85 _public prototype_ `void PostRenderPreviewTick() const;` — This function is called every tick after rendering the preview.
- L89 _private member_ `TWeakPtr<FDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe> ViewportManagerPreviewWeakPtr;` — Weak pointer to the ViewportManager
- L92 _private member_ `bool bPreviewRenderingCompleted = false;` — Preview is already rendered for this actor
- L95 _private member_ `bool bRenderPreviewRequested = false;` — Preview render request from DCRA

#### class `FDisplayClusterViewportManagerPreviewRenderingSingleton`  
`class FDisplayClusterViewportManagerPreviewRenderingSingleton`  
_L101-132_
- desc: This is a singleton class that controls the preview rendering of multiple ViewportManager preview instances.
- L105 _public prototype_ `static void HandleEvent(const EDisplayClusteViewportManagerPreviewRenderingEvent InPreviewEvent, FDisplayClusterViewportManagerPreview* InViewportManagerPreview);` — The entry point for ViewportManager, which is used to handle all workflow events related to preview rendering.
- L111 _protected prototype_ `void Tick(float DeltaTime);` — This function is used to perform delayed ViewportManager preview rendering requests.
- L114 _protected prototype_ `void UpdateTickableGameObject();` — Creating or deleting a Tickable object depends on whether the ViewportManagers list is not empty.
- L117 _protected prototype_ `void HandleEventImpl(const EDisplayClusteViewportManagerPreviewRenderingEvent InPreviewEvent, FDisplayClusterViewportManagerPreview* InViewportManagerPreview);` — Implementation of the static HandleEvent() function.
- L120 _protected prototype_ `int32 GetNextPreviewObject();` — Gets the index of the next ViewportManager container, which can be used for rendering the preview.
- L123 _protected prototype_ `void BeginNewRenderCycle();` — When all registered DCRA objects are drawn, you must call this function to reset the internal flags.
- L127 _private member_ `TArray<FDisplayClusterViewportManagerPreviewRenderingInstance> PreviewObjects;` — List of existing ViewportManagers
- L131 _private member_ `TUniquePtr<FDisplayClusterTickableGameObject> TickableGameObject;` — When CachedObjects is not empty, this ticking object will be created. Also, this object will be deleted when CachedObjects becomes empty.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Preview/DisplayClusterViewportPreview.h` (Private)


#### class `FDisplayClusterViewportPreview`  
`class FDisplayClusterViewportPreview : public IDisplayClusterViewportPreview , public TSharedFromThis<FDisplayClusterViewportPreview, ESPMode::ThreadSafe>`  
_L18-164_
- inherits: `IDisplayClusterViewportPreview,TSharedFromThis<FDisplayClusterViewportPreview,ESPMode::ThreadSafe>`
- desc: Store and manage preview resources of the viewport
- L23 _public prototype_ `FDisplayClusterViewportPreview(const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration, const FString& ViewportId);`
- L24 _public prototype_ `virtual ~FDisplayClusterViewportPreview();`
- L28 _public function_ `virtual TSharedPtr<IDisplayClusterViewportPreview, ESPMode::ThreadSafe> ToSharedPtr() override`
- L33 _public function_ `virtual TSharedPtr<const IDisplayClusterViewportPreview, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L38 _public function_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() override`
- L43 _public function_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const override`
- L48 _public function_ `virtual FString GetId() const override`
- L53 _public function_ `virtual FString GetClusterNodeId() const override`
- L58 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> GetOwningViewport() const override;`
- L60 _public prototype_ `virtual UTextureRenderTarget2D* GetPreviewTextureRenderTarget2D() const override;`
- L62 _public function_ `virtual UMeshComponent* GetPreviewMeshComponent() const override`
- L66 _public function_ `virtual UMeshComponent* GetPreviewEditableMeshComponent() const override`
- L71 _public function_ `virtual bool HasAnyFlags(const EDisplayClusterViewportPreviewFlags InPreviewFlags) const override`
- L80 _public prototype_ `void Update(TSet<const UMeshComponent*>& MeshComponentsVisited);` — Update preview resources for this viewport.
- L83 _public prototype_ `void Release();` — Release preview resources and materials for this viewport.
- L86 _public prototype_ `void Initialize(FDisplayClusterViewport& InViewport);` — Initialize reference to viewport.
- L99 _public prototype_ `FSceneView* CalcSceneView(class FSceneViewFamilyContext& InOutViewFamily, uint32 ContextNum, TSharedPtr<FSceneViewStateReference, ESPMode::ThreadSafe>& OutViewState);` — Creates an FSceneView for the viewport. This function is based on similar LocalPlayer logic. @param InOutViewFamily View family used to render this viewport. @param ContextNum      Rendering context index. @param OutViewState    Receives the ViewState used by the SceneView. This must be passed to the render thread to ensure it is not destroyed before rendering is complete. @return A pointer to the created FSceneView, or nullptr if creation fails.
- L103 _public function_ `bool CanShowLogMsgOnce(const EDisplayClusterViewportPreviewShowLogMsgOnce& InLogState)` — Returns true once if this type of log message can be displayed for the first time.
- L116 _public function_ `void ResetShowLogMsgOnce(const EDisplayClusterViewportPreviewShowLogMsgOnce& InLogState)` — Reset log states.
- L123 _protected prototype_ `TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe> GetOutputPreviewTargetableResources() const;` — Return output preview resource.
- L126 _protected prototype_ `bool CalculateStereoViewOffset( const TSharedRef<FDisplayClusterViewport, ESPMode::ThreadSafe>& InViewport, const uint32 InContextNum, FRotator& ViewRotation, FVector& ViewLocation, FVector& StereoViewLocation);` — Calculating stereoviewer offset for preview.
- L134 _protected prototype_ `FMatrix GetStereoProjectionMatrix(FDisplayClusterViewport& InViewport, const uint32 InContextNum);` — Get viewport context projection matrix.
- L138 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L141 _public member_ `const FString ViewportId;` — Unique viewport name
- L144 _public member_ `const FString ClusterNodeId;` — Owner cluster node name
- L148 _private member_ `TWeakPtr<FDisplayClusterViewport, ESPMode::ThreadSafe> OwningViewportWeakPtr;` — Weak pointer to the owning DC viewport currently used for rendering.
- L151 _private member_ `TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe> PreviewRTT;` — Preview RTT
- L154 _private member_ `FDisplayClusterViewportPreviewMesh PreviewMesh;` — Preview mesh
- L157 _private member_ `FDisplayClusterViewportPreviewMesh PreviewEditableMesh;` — Preview editable mesh
- L160 _private member_ `EDisplayClusterViewportPreviewFlags RuntimeFlags = EDisplayClusterViewportPreviewFlags::None;` — Runtime flags
- L163 _private member_ `EDisplayClusterViewportPreviewShowLogMsgOnce ShowLogMsgOnceFlags = EDisplayClusterViewportPreviewShowLogMsgOnce::None;` — A recurring message in the log will be shown only once

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Preview/DisplayClusterViewportPreviewMesh.h` (Private)


#### enum `EDisplayClusterViewportPreviewMeshFlags`  
`enum class EDisplayClusterViewportPreviewMeshFlags : uint8`  
_L22-40_
- desc: Runtime configuration of preview mesh.
- L24 _public enumerator_ `None = 0`
- L27 _public enumerator_ `HasDeletedMeshComponent = 1 << 0` — The Mesh component has been removed
- L30 _public enumerator_ `HasChangedMeshComponent = 1 << 1` — the Mesh component has been modified
- L33 _public enumerator_ `HasDeletedMaterialInstance = 1 << 2` — The MaterialInstance has been removed
- L36 _public enumerator_ `HasChangedMaterialInstance = 1 << 3` — The MaterialInstance has been modified
- L39 _public enumerator_ `HasRestoredDefaultMaterial = 1 << 4` — Default Material is restored on the Mesh

#### class `FDisplayClusterViewportPreviewMesh`  
`class FDisplayClusterViewportPreviewMesh`  
_L46-134_
- desc: Manage preview mesh of the viewport
- L49 _public function_ `FDisplayClusterViewportPreviewMesh(const EDisplayClusterDisplayDeviceMeshType InMeshType, const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> InConfiguration) : Configuration(InConfiguration), MeshType(InMeshType)`
- L53 _public prototype_ `~FDisplayClusterViewportPreviewMesh() = default;`
- L57 _public prototype_ `UMeshComponent* GetMeshComponent() const;` — Get preview mesh component.
- L60 _public prototype_ `UMaterialInstanceDynamic* GetMaterialInstance() const;` — Get MID used on preview mesh.
- L63 _public prototype_ `EDisplayClusterDisplayDeviceMaterialType GetCurrentMaterialType() const;` — Return current material type that used on this mesh.
- L66 _public prototype_ `void Update(FDisplayClusterViewport* InViewport, UDisplayClusterDisplayDeviceBaseComponent* InDisplayDeviceComponent, UDisplayClusterCameraComponent* ViewPointComponent);` — Update mesh component and materials for viewport.
- L69 _public function_ `void Release(FDisplayClusterViewport* InViewport)` — Restore default material and release mesh component with materials for viewport.
- L76 _public function_ `bool HasAnyFlag(const EDisplayClusterViewportPreviewMeshFlags InMeshFlags) const` — Returns true if the runtime flags have any of the input flags.
- L83 _private prototype_ `bool ShouldUseMeshComponent(FDisplayClusterViewport* InViewport) const;` — Returns true if this mesh type is supported by the viewport projection policy and DCRA.
- L86 _private prototype_ `void ReleaseMaterialInstance();` — Release material instance
- L89 _private prototype_ `void ReleaseMeshComponent(FDisplayClusterViewport* InViewport);` — Release mesh component.
- L92 _private prototype_ `void UpdateOverlayMaterial(FDisplayClusterViewport* InViewport);` — Update overlay materials on mesh.
- L95 _private prototype_ `void SetCustomOverlayMaterial(UMeshComponent* InMeshComponent, UMaterialInterface* InOverlayMaterial);` — Set custom overlay materials on mesh.
- L98 _private prototype_ `void RestoreOverlayMaterial(UMeshComponent* InMeshComponent);` — Restore overlay material on mesh.
- L101 _private prototype_ `UMeshComponent* GetOrCreatePreviewMeshComponent(FDisplayClusterViewport* InViewport, bool& bOutIsRootActorComponent) const;` — Get mesh component.
- L105 _public member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node
- L108 _public member_ `const EDisplayClusterDisplayDeviceMeshType MeshType;` — the type of mesh
- L112 _private member_ `EDisplayClusterViewportPreviewMeshFlags RuntimeFlags;` — runtime flags
- L115 _private member_ `FDisplayClusterSceneComponentRef MeshComponentBinding;` — Persistent by-name binding to the mesh component used for preview.
- L118 _private member_ `TWeakObjectPtr<UMeshComponent> MeshComponentPtr;` — Resolved weak handle from the binding above.
- L121 _private member_ `bool bIsRootActorMeshComponent = false;` — This mesh component exists in DCRA and does not need to be deleted.
- L124 _private member_ `TWeakObjectPtr<UMaterialInterface> OrigOverlayMaterialPtr;` — Overlay materials for the mesh can be customized when using preview rendering.
- L127 _private member_ `TWeakObjectPtr<UMaterialInstanceDynamic> MaterialInstancePtr;` — Preview material used on the mesh
- L130 _private member_ `TWeakObjectPtr<UMaterial> CurrentMaterialPtr;` — The current material assigned to the preview mesh
- L133 _private member_ `TWeakObjectPtr<UMaterial> DefaultMaterialPtr;` — The default material defined in the DisplayDevice

#### Free symbols / members of external scopes

- L41 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportPreviewMeshFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/RenderFrame/DisplayClusterRenderFrameManager.h` (Private)


#### class `FDisplayClusterRenderFrameManager`  
`class FDisplayClusterRenderFrameManager`  
_L12-29_
- L15 _public function_ `FDisplayClusterRenderFrameManager(const TSharedRef<const FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration) : Configuration(InConfiguration)`
- L20 _public prototype_ `bool BuildRenderFrame(FViewport* InViewport, const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, FDisplayClusterRenderFrame& OutRenderFrame);`
- L23 _private prototype_ `bool FindFrameTargetRect(FViewport* InViewport, const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, FIntRect& OutFrameTargetRect) const;`
- L24 _private prototype_ `bool BuildSimpleFrame(FViewport* InViewport, const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, FDisplayClusterRenderFrame& OutRenderFrame);`
- L28 _private member_ `const TSharedRef<const FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/RenderFrame/DisplayClusterRenderFrameSettings.h` (Private)


#### struct `FDisplayClusterRenderFrameSettings`  
`struct FDisplayClusterRenderFrameSettings`  
_L12-203_
- desc: Settings for render frame builder
- L15 _public member_ `TOptional<uint32> FrameNumberOverride;` — If set, use this value instead of GFrameNumber.
- L18 _public member_ `EDisplayClusterRenderFrameMode RenderMode = EDisplayClusterRenderFrameMode::Unknown;` — customize mono\stereo render modes
- L21 _public member_ `EDisplayClusterRenderFrameAlphaChannelCaptureMode AlphaChannelCaptureMode = EDisplayClusterRenderFrameAlphaChannelCaptureMode::None;` — Alpha channel capture mode for viewports (Lightcard, chromakey)
- L39 _public member_ `} CrossGPUTransfer;`
- L42 _public member_ `uint8 bShouldUseOutputFrameTargetableResources : 1 = 0;` — This rendering frame uses OutputFrameTargetable resources.
- L45 _public member_ `uint8 bShouldUseAdditionalFrameTargetableResource : 1 = 0;` — This rendering frame uses AdditionalFrameTargetable resources.
- L48 _public member_ `uint8 bShouldUseFullSizeFrameTargetableResource : 1 = 0;` — This rendering frame uses full size for the FrameTargetable resources.
- L51 _public member_ `uint8 bUseAdditionalFrameTargetableForPostprocess : 1 = 0;` — Use an AdditionalFrameTargetable for postprocess in this frame.
- L54 _public member_ `uint8 bUseFullSizeFrameTargetableForPostprocess : 1 = 0;` — Use an full-size FrameTargetable resources for postprocess in this frame.
- L57 _public member_ `uint8 bAllowWarpBlend : 1 = 1;` — Allow warpblend render
- L61 _public member_ `uint8 bEnableAlphaOutput : 1 = 0;` — True if alpha channel should be written to all viewport outputs. Note: Controlled by "DC.EnableAlphaChannelRendering" and "r.PostProcessing.PropagateAlpha".
- L64 _public member_ `uint8 bUseDisplayClusterRenderDevice : 1 = 1;` — Use DC render device for rendering
- L67 _public member_ `uint8 bEnableStereoscopicRenderingOptimization : 1 = 0;` — Performance: Stereoscopic rendering uses a single viewfamily(RTT) for both eyes
- L70 _public member_ `uint8 bUseExternalOverscan : 1 = 0;` — When set, nDisplay's own overscan settings are ignored and this external value is used instead.
- L74 _public member_ `uint8 bExternalOverscanOversize : 1 = 1;` — When external overscan is active, controls whether viewports render at the overscan resolution (true) or at the configured resolution with post-render scaling (false).
- L78 _public member_ `TOptional<float> ExternalOverscanOverride;` — Overrides the camera overscan value when bUseExternalOverscan is true. When not set, the overscan is read from FMinimalViewInfo.GetOverscan().
- L93 _public member_ `} CurrentNode;`
- L98 _public member_ `float RenderResolutionScale = 1.f;` — Scales the render resolution of all viewports uniformly. Set via IDisplayClusterViewportConfiguration::SetRenderResolutionScale().
- L101 _public member_ `float ClusterRenderTargetRatioMult = 1.f;` — Multiply all viewports RTT size's for whole cluster by this value
- L104 _public member_ `float ClusterICVFXInnerViewportRenderTargetRatioMult = 1.f;` — Multiply inner frustum RTT size's for whole cluster by this value
- L107 _public member_ `float ClusterICVFXOuterViewportRenderTargetRatioMult = 1.f;` — Multiply outer viewports RTT size's for whole cluster by this value
- L110 _public member_ `float ClusterBufferRatioMult = 1.f;` — Multiply all buffer ratios for whole cluster by this value
- L113 _public member_ `float ClusterICVFXInnerFrustumBufferRatioMult = 1.f;` — Multiply inner frustums buffer ratios for whole cluster by this value
- L116 _public member_ `float ClusterICVFXOuterViewportBufferRatioMult = 1.f;` — Multiply outer viewports buffer ratios for whole cluster by this value
- L119 _public member_ `FDisplayClusterViewport_PreviewSettings PreviewSettings;` — Settings for preview rendering
- L123 _public member_ `TOptional<FIntPoint> PreviewMultiGPURendering;` — [Experimental] Render preview in multi-GPU Specifies the mGPU index range for rendering the DCRA preview.
- L127 _public prototype_ `bool IsICVFXEnabled() const;` — Returns true if ICVFX rendering can be used.
- L130 _public prototype_ `bool IsPreviewRendering() const;` — Current frame is preview.
- L133 _public prototype_ `bool IsClusterRendering() const;` — Returns true if this DCRA is using cluster rendering.
- L136 _public prototype_ `bool IsTechvisEnabled() const;` — Returns true, if Techvis is used.
- L139 _public prototype_ `bool IsPreviewInGameEnabled() const;` — Returns true if the DCRA preview feature in Standalone/Package builds is used.
- L142 _public prototype_ `bool IsPreviewFreezeRender() const;` — returns true if the preview rendering has been updated.If this function returns false, the DCRA preview image should be frozen.
- L147 _public prototype_ `const FIntPoint* GetPreviewMultiGPURendering() const;` — [Experimental] Get the GPU range used for rendering preview. returns nullptr if this rendering function is disabled on mGPU
- L150 _public prototype_ `bool IsEnabledOpenColorIO() const;` — True if OCIO is enabled for nDisplay.
- L153 _public prototype_ `bool IsPostProcessDisabled() const;` — PostProcess should be disabled for the current frame.
- L156 _public prototype_ `bool ShouldUseLinearGamma() const;` — Should use linear gamma.
- L159 _public prototype_ `bool ShouldUseHoldout() const;` — Should use Holdout.
- L162 _public prototype_ `bool ShouldUseStereoRenderingOnMonoscopicDisplay() const;` — Is stereo rendering on monoscopic display (sbs, tb) .
- L165 _public prototype_ `FVector2D GetDesiredFrameMult() const;` — Getting the desired frame size multipliers.
- L168 _public prototype_ `FVector2D GetDesiredRTTSize(const FVector2D& InSize) const;` — Obtain the desired RTT size (for sbs and tb this is half the size in one of the dimensions).
- L169 _public prototype_ `FIntPoint GetDesiredRTTSize(const FIntPoint& InSize) const;`
- L179 _public prototype_ `FIntPoint ApplyViewportSizeConstraint(const class FDisplayClusterViewport& InViewport, const FIntPoint& InSize) const;` — Limit viewport size within: 1. MaxArea - for main viewports only, controlled by ShouldApplyMaxTextureConstraints(). 2. Maximum texture size based on hardware limitations	* The output size will have the same aspect ratio as the input size. @param InViewport - the nDisplay viewport for which the size is used. @param InSize     - The base size of the viewport.
- L182 _public function_ `inline bool ShouldUseCrossGPUTransfers() const` — Should use Cross-GPU transfers.
- L188 _public prototype_ `bool CanReuseViewportWithinClusterNodes() const;` — Ability to reuse the viewport across all nodes in the cluster (DCRA Preview).
- L191 _public prototype_ `int32 GetViewPerViewportAmount() const;` — Return number of views per viewport.
- L194 _public function_ `inline uint32 GetFrameNumber() const` — Return current frame number.

#### struct `FDisplayClusterRenderFrameSettings::FCrossGPUTransfer`  
`struct FCrossGPUTransfer`  
_L24-39_
- desc: nDisplay has its own implementation of cross-GPU transfer.
- L28 _public member_ `uint8 bEnable : 1 = 0;` — Enable cross-GPU transfers using nDisplay That replaces the default cross-GPU transfers using UE Core for the nDisplay viewports viewfamilies.
- L33 _public member_ `uint8 bLockSteps : 1 = 0;` — The bLockSteps parameter is simply passed to the FTransferResourceParams structure. Whether the GPUs must handshake before and after the transfer. Required if the texture rect is being written to in several render passes. Otherwise, minimal synchronization will be used.
- L37 _public member_ `uint8 bPullData : 1 = 1;` — The bPullData parameter is simply passed to the FTransferResourceParams structure. Whether the data is read by the dest GPU, or written by the src GPU (not allowed if the texture is a backbuffer)

#### struct `FDisplayClusterRenderFrameSettings::FCurrentClusterNodeSettings`  
`struct FCurrentClusterNodeSettings`  
_L81-93_
- desc: Settings for the current cluster node.
- L85 _public member_ `uint8 bRenderHeadless : 1 = 0;` — True if this cluster node is configured to render headless. Mirrors UDisplayClusterConfigurationClusterNode::bRenderHeadless.
- L88 _public member_ `uint8 bHasBackbufferMediaOutput : 1 = 0;` — True if this cluster node has a backbuffer media output assigned.
- L91 _public member_ `FString Id;` — Cluster node name for render

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/RenderFrame/DisplayClusterRenderFrameSettingsEnums.h` (Private)


#### enum `EDisplayClusterRenderFrameAlphaChannelCaptureMode`  
`enum class EDisplayClusterRenderFrameAlphaChannelCaptureMode: uint8`  
_L10-43_
- desc: Select the method to save the alpha channel for nDisplay rendering.
- L13 _public enumerator_ `None = 0` — [None]- Do not capture alpha.
- L21 _public enumerator_ `ThroughTonemapper` — [ThroughTonemapper] - Render alpha Through Tonemapper, Copy alpha from PP input texture to final. When rendering with the PropagateAlpha experimental mode turned on, the alpha channel is forwarded to post-processes. In this case, the alpha channel is anti-aliased along with the color. Since some post-processing may change the alpha, it is copied at the beginning of the PP and restored after all post-processing is completed.
- L30 _public enumerator_ `FXAA` — [FXAA] - Disable AA and TAA, Use FXAA for RGB, Copy alpha from scenecolor texture to final. Otherwise, if the PropagateAlpha mode is disabled in the project settings, we need to save the alpha before it becomes invalid. The alpha is valid until the scene color is resolved (on the ResolvedSceneColor callback). Therefore, it is copied to a temporary resource on this cb. Since we need to remove AA jittering (because alpha copied before AA), anti-aliasing is turned off for this viewport. And finally the FXAA is used for smoothing.
- L36 _public enumerator_ `CopyAA` — [CopyAA] - Use AA, disable TAA, Copy alpha from scenecolor texture to final These experimental (temporary) modes for the performance tests.
- L42 _public enumerator_ `Copy` — [Copy] - Disable AA and TAA, Copy alpha from scenecolor texture to final These experimental (temporary) modes for the performance tests.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/RenderTarget/DisplayClusterRenderTargetManager.h` (Private)


#### class `FDisplayClusterRenderTargetManager`  
`class FDisplayClusterRenderTargetManager`  
_L13-32_
- L16 _public prototype_ `FDisplayClusterRenderTargetManager(const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe>& InConfiguration);`
- L17 _public prototype_ `~FDisplayClusterRenderTargetManager();`
- L19 _public prototype_ `void Release();`
- L22 _public prototype_ `bool AllocateRenderFrameResources(FViewport* InViewport, const TArray<TSharedPtr<FDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, FDisplayClusterRenderFrame& InOutRenderFrame);`
- L25 _protected prototype_ `bool AllocateFrameTargets(const FIntPoint& InViewportSize, FDisplayClusterRenderFrame& InOutRenderFrame);`
- L28 _private member_ `TUniquePtr<FDisplayClusterRenderTargetResourcesPool> ResourcesPool;`
- L31 _private member_ `const TSharedRef<FDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> Configuration;` — Configuration of the current cluster node

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/RenderTarget/DisplayClusterRenderTargetResource.h` (Private)


#### class `FDisplayClusterViewportTextureResource`  
`class FDisplayClusterViewportTextureResource : public FDisplayClusterViewportResource , public FTexture`  
_L14-78_
- inherits: `FDisplayClusterViewportResource,FTexture`
- desc: Viewport texture resource
- L19 _public prototype_ `FDisplayClusterViewportTextureResource(const FDisplayClusterViewportResourceSettings& InResourceSettings);`
- L21 _public function_ `virtual ~FDisplayClusterViewportTextureResource()`
- L26 _public function_ `virtual FRHITexture* GetViewportResourceRHI_RenderThread() const override`
- L33 _public function_ `virtual FIntPoint GetBackbufferFrameOffset() const override`
- L38 _public function_ `virtual void SetBackbufferFrameOffset(const FIntPoint& InBackbufferFrameOffset) override`
- L43 _public function_ `virtual void InitializeViewportResource_RenderThread(FRHICommandListBase& RHICmdList) override`
- L49 _public function_ `virtual void ReleaseViewportResource_RenderThread(FRHICommandListBase& RHICmdList) override`
- L57 _public function_ `virtual uint32 GetSizeX() const override`
- L62 _public function_ `virtual uint32 GetSizeY() const override`
- L67 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L69 _public function_ `virtual FString GetFriendlyName() const override`
- L77 _public member_ `FIntPoint BackbufferFrameOffset = FIntPoint::ZeroValue;` — OutputFrameTargetableResources frame offset on backbuffer (special for 'side_by_side' and 'top_bottom' DCRenderDevices)

#### class `FDisplayClusterViewportRenderTargetResource`  
`class FDisplayClusterViewportRenderTargetResource : public FDisplayClusterViewportTextureResource , public FRenderTarget`  
_L83-121_
- inherits: `FDisplayClusterViewportTextureResource,FRenderTarget`
- desc: Viewport RTT resource
- L88 _public function_ `FDisplayClusterViewportRenderTargetResource(const FDisplayClusterViewportResourceSettings& InResourceSettings) : FDisplayClusterViewportTextureResource(InResourceSettings)`
- L92 _public function_ `virtual ~FDisplayClusterViewportRenderTargetResource()`
- L97 _public function_ `virtual FRenderTarget* GetViewportResourceRenderTarget() override`
- L104 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L106 _public function_ `virtual FIntPoint GetSizeXY() const override`
- L111 _public function_ `virtual float GetDisplayGamma() const override`
- L116 _public function_ `virtual FString GetFriendlyName() const override`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/RenderTarget/DisplayClusterRenderTargetResourcesPool.h` (Private)


#### class `FDisplayClusterRenderTargetResourcesPool`  
`class FDisplayClusterRenderTargetResourcesPool`  
_L11-66_
- desc: DC viewport resources pool
- L14 _public prototype_ `~FDisplayClusterRenderTargetResourcesPool();`
- L16 _public prototype_ `void Release();`
- L26 _public prototype_ `bool BeginReallocateResources(class FViewport* InViewport, const struct FDisplayClusterRenderFrameSettings& InRenderFrameSettings);` — Begin reallocate resources for the specified cluster node. @param InRenderFrameSettings - default resource settings @param InViewport - the window that uses these resources @return true, if success
- L38 _public prototype_ `TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe> AllocateResource(const FString InViewportId, const FIntPoint& InSize, EPixelFormat CustomPixelFormat, const EDisplayClusterViewportResourceSettingsFlags InResourceFlags, int32 NumMips = 1);` — Allocate a new resource or reuse exists @param InViewportId      - This resource belongs to this viewport only. Empty string if not used @param InSize            - resource dimensions @param CustomPixelFormat - resource pixel format @param InResourceFlags   - These flags define the behavior of the resource. @param NumMips           - number of mips in the texture @return ref to the resource instance
- L41 _public prototype_ `void EndReallocateResources();` — End reallocate resources for the specified cluster node.
- L58 _private prototype_ `void ImplUpdateResources(TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>>& InOutViewportResources, const EResourceUpdateMode InUpdateMode);` — Update resources from array @param InOutViewportResources - resources to update @param InUpdateMode           - initialize or release
- L62 _private member_ `FDisplayClusterViewportResourceSettings* ResourceSettings = nullptr;` — Current render resource settings
- L65 _private member_ `TArray<TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe>> ViewportResources;` — Viewport render resources

#### enum `FDisplayClusterRenderTargetResourcesPool::EResourceUpdateMode`  
`enum class EResourceUpdateMode : uint8`  
_L47-51_
- desc: Resource update mode
- L49 _public enumerator_ `Initialize = 0`
- L50 _public enumerator_ `Release`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Resource/DisplayClusterViewportPreviewResource.h` (Private)


#### class `FDisplayClusterViewportPreviewResource`  
`class FDisplayClusterViewportPreviewResource : public FDisplayClusterViewportResource`  
_L14-37_
- inherits: `FDisplayClusterViewportResource`
- desc: Viewport preview texture resource
- L18 _public prototype_ `FDisplayClusterViewportPreviewResource(const FDisplayClusterViewportResourceSettings& InResourceSettings);`
- L19 _public prototype_ `virtual ~FDisplayClusterViewportPreviewResource();`
- L23 _public prototype_ `virtual void InitializeViewportResource() override;`
- L24 _public prototype_ `virtual void ReleaseViewportResource() override;`
- L26 _public function_ `virtual UTextureRenderTarget2D* GetTextureRenderTarget2D() const override`
- L31 _public prototype_ `virtual FRHITexture* GetViewportResourceRHI_RenderThread() const override;`
- L36 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTargetTexture = nullptr;` — Preview RTT resource

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Resource/DisplayClusterViewportResource.h` (Private)


#### enum `EDisplayClusterViewportResourceState`  
`enum class EDisplayClusterViewportResourceState : uint8`  
_L18-34_
- desc: Runtime state of the viewport resource
- L21 _public enumerator_ `None = 0` — empty state, without flags
- L24 _public enumerator_ `Initialized = 1 << 0` — This resource was initialized in the rendering thread
- L27 _public enumerator_ `Unused = 1 << 1` — This resource is not used for the current frame
- L30 _public enumerator_ `DisableReallocate = 1 << 3` — Disable reallocation of this resource for the current frame
- L33 _public enumerator_ `UpdatedOnRenderingThread = 1 << 4` — This resource was updated in the rendering thread

#### class `FDisplayClusterViewportResource`  
`class FDisplayClusterViewportResource : public TSharedFromThis<FDisplayClusterViewportResource, ESPMode::ThreadSafe>`  
_L40-134_
- inherits: `TSharedFromThis<FDisplayClusterViewportResource,ESPMode::ThreadSafe>`
- desc: Viewport resource texture base class
- L44 _public function_ `FDisplayClusterViewportResource(const FDisplayClusterViewportResourceSettings& InResourceSettings) : ResourceSettings(InResourceSettings)`
- L48 _public prototype_ `virtual ~FDisplayClusterViewportResource();`
- L52 _public function_ `inline EDisplayClusterViewportResourceState& GetResourceState()` — Get the current state of the resource.
- L58 _public function_ `inline const EDisplayClusterViewportResourceState& GetResourceState() const` — Get the current const state of the resource.
- L64 _public function_ `inline const FDisplayClusterViewportResourceSettings& GetResourceSettings() const` — Get the current settings of the resource.
- L71 _public function_ `virtual void SetExternalViewportResourceRHI(FTextureRHIRef& InExternalViewportResourceRHI)` — Assign external RHI resource.
- L75 _public function_ `virtual FRHITexture* GetViewportResourceRHI_RenderThread() const` — Get current RHI resource.
- L81 _public function_ `virtual FRenderTarget* GetViewportResourceRenderTarget()` — Get RenderTarget resource.
- L86 _public function_ `virtual UTextureRenderTarget2D* GetTextureRenderTarget2D() const`
- L92 _public function_ `virtual FIntPoint GetBackbufferFrameOffset() const` — Getting the viewport rect offset in the backbuffer.
- L98 _public function_ `virtual void SetBackbufferFrameOffset(const FIntPoint& InBackbufferFrameOffset)` — Settings the viewport rect offset in the backbuffer.
- L102 _public function_ `virtual void InitializeViewportResource()` — Initialize this resource in the game thread.
- L108 _public function_ `virtual void ReleaseViewportResource()` — Release this resource in the game thread
- L114 _public function_ `virtual void InitializeViewportResource_RenderThread(FRHICommandListBase& RHICmdList)` — RHI initialization for this resource in the rendering thread.
- L118 _public function_ `virtual void ReleaseViewportResource_RenderThread(FRHICommandListBase& RHICmdList)` — RHI release for this resource in the rendering thread
- L123 _protected prototype_ `void ImplInitDynamicRHI_RenderTargetResource2D(FRHICommandListBase& RHICmdList, FTextureRHIRef& OutRenderTargetTextureRHI, FTextureRHIRef& OutTextureRHI);` — Helper function: create RTT texture.
- L126 _protected prototype_ `void ImplInitDynamicRHI_TextureResource2D(FRHICommandListBase& RHICmdList, FTextureRHIRef& OutTextureRHI);` — Helper function: create 2D texture.
- L130 _protected member_ `const FDisplayClusterViewportResourceSettings ResourceSettings;` — Settings used by this resource
- L133 _protected member_ `EDisplayClusterViewportResourceState ResourceState = EDisplayClusterViewportResourceState::None;` — Resource states

#### Free symbols / members of external scopes

- L35 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportResourceState);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/Resource/DisplayClusterViewportResourceSettings.h` (Private)


#### enum `EDisplayClusterViewportResourceSettingsFlags`  
`enum class EDisplayClusterViewportResourceSettingsFlags : uint8`  
_L14-40_
- desc: Runtime state of the viewport resource Depending on the flags used, different child classes will be used.
- L17 _public enumerator_ `None = 0` — Default value, no flags
- L20 _public enumerator_ `ShouldUseSRGB = 1 << 0` — The resource will use the 'ETextureCreateFlags::SRGB' flag.
- L23 _public enumerator_ `RenderTarget = 1 << 1` — This is the RenderTarget resource used in the viewfamily (not the usual texture).
- L27 _public enumerator_ `RenderTargetableTexture = 1 << 3` — This is the texture. The render resource will be created with the 'ETextureCreateFlags::RenderTargetable' flag.
- L31 _public enumerator_ `ResolveTargetableTexture = 1 << 4` — This is the texture. The render resource will be created with the 'ETextureCreateFlags::ResolveTargetable' flag.
- L35 _public enumerator_ `PreviewTargetableTexture = 1 << 5` — This is the texture that is used to render the DCRA preview (contains the UTexture that is used for UMaterialInstanceDynamic).
- L39 _public enumerator_ `LinearColorSpace = 1 << 6` — This texture is in linear color space DisplayGamma should be set to 1.0f

#### struct `FDisplayClusterViewportResourceSettings`  
`struct FDisplayClusterViewportResourceSettings`  
_L46-156_
- desc: nDisplay viewport render resource settings
- L53 _public prototype_ `FDisplayClusterViewportResourceSettings(const FDisplayClusterRenderFrameSettings& InRenderFrameSettings, class FViewport* InViewport);` — Create default resource settings @param InRenderFrameSettings - render frame settings used (preview or normal rendering, etc.) @param InViewport - the window viewport interface (used display gamma, format, etc.)
- L63 _public prototype_ `FDisplayClusterViewportResourceSettings(const FDisplayClusterViewportResourceSettings& InBaseSettings, const FString InViewportId, const FIntPoint& InSize, const EPixelFormat InFormat, const EDisplayClusterViewportResourceSettingsFlags InResourceFlags = EDisplayClusterViewportResourceSettingsFlags::None, const int32 InNumMips = 1);` — Create a custom resource setting based on another one. @param InBaseSettings  -  basic settings, if no values are defined, the values from them will be used. @param InSize          - resource size @param InFormat        - resource format @param InResourceFlags - these flags determine what type of resource will be created. @param InNumMips       - the number of mips that will be created. This value is only supported by a certain type of resource.
- L67 _public function_ `inline bool IsResourceSettingsEqual(const FDisplayClusterViewportResourceSettings& In) const` — Returns true if the input resource settings match the local values.
- L88 _public function_ `inline bool IsClusterNodeNameEqual(const FDisplayClusterViewportResourceSettings& In) const` — Returns true if the resource settings are used in the same cluster node.
- L94 _public function_ `inline const FIntPoint& GetSizeXY() const` — Get the X and Y dimensions of the resource.
- L100 _public function_ `inline const int32 GetSizeX() const` — Get the width of the resource.
- L106 _public function_ `inline const int32 GetSizeY() const` — Get the height of the resource.
- L112 _public function_ `inline EPixelFormat GetFormat() const` — Get the pixel format of the resource.
- L118 _public function_ `inline float GetDisplayGamma() const` — Get the display gamma used by this resource
- L124 _public function_ `inline int32 GetNumMips() const` — Get the number of resource mips.
- L130 _public function_ `inline EDisplayClusterViewportResourceSettingsFlags GetResourceFlags() const` — Retrieving resource flags.
- L137 _private member_ `const FString ClusterNodeId;` — This is a resource belonging to the cluster node
- L140 _private member_ `const FString ViewportId;` — The preview resource is always used by the same Outer viewport
- L143 _private member_ `FIntPoint Size;` — Resource width and height
- L146 _private member_ `EPixelFormat Format = EPixelFormat::PF_Unknown;` — The pixel format of the resource.
- L149 _private member_ `float DisplayGamma = 2.2f;` — The display gamma used by this resource
- L152 _private member_ `int32 NumMips = 0;` — Number of resource mips.
- L155 _private member_ `EDisplayClusterViewportResourceSettingsFlags ResourceFlags = EDisplayClusterViewportResourceSettingsFlags::None;` — Resource flags.

#### Free symbols / members of external scopes

- L41 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportResourceSettingsFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Version/DisplayClusterICVFXCameraCustomVersion.h` (Private)


#### struct `FDisplayClusterICVFXCameraCustomVersion`  
`struct FDisplayClusterICVFXCameraCustomVersion`  
_L9-27_
- desc: Custom serialization version for UDisplayClusterICVFXCameraComponent
- L23 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L26 _private function_ `FDisplayClusterICVFXCameraCustomVersion()`

#### enum `FDisplayClusterICVFXCameraCustomVersion::Type`  
`enum Type`  
_L11-20_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L15 _public enumerator_ `UpdateChromakeyConfig = 1`
- L18 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L19 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Blueprints/DisplayClusterBlueprint.h` (Public)


#### class `UDisplayClusterBlueprint`  
`class UDisplayClusterBlueprint : public UBlueprint`  
_L22-104_
- reflection: `UCLASS(BlueprintType, DisplayName = "nDisplay Blueprint")`
- inherits: `UBlueprint`
- desc: Display Cluster Configuration Asset Asset containing the full nDisplay cluster setup and settings. Can also contain any blueprint logic like any other actor blueprints. @see UBlueprint
- L27 _public prototype_ `UDisplayClusterBlueprint();`
- L32 _public member_ `uint8 bRunConstructionScriptOnInteractiveChange : 1;` — `UPROPERTY(EditAnywhere, Category=BlueprintOptions)` — Whether or not you want to continuously rerun the construction script while dragging a slider
- L37 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override` — UBlueprint
- L38 _public prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L39 _public prototype_ `virtual void GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const override;`
- L44 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L45 _public prototype_ `virtual void PostLoad() override;`
- L46 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L49 _public prototype_ `class UDisplayClusterBlueprintGeneratedClass* GetGeneratedClass() const;`
- L51 _public prototype_ `UDisplayClusterConfigurationData* GetOrLoadConfig();`
- L52 _public function_ `UDisplayClusterConfigurationData* GetConfig() const`
- L61 _public prototype_ `void SetConfigData(UDisplayClusterConfigurationData* InConfigData, bool bForceRecreate = false);` — Set the config data on the CDO and update the config file path. When bForceRecreate is false this only updates the config path after initial creation. @param InConfigData New config data to set. This will be a template for the CDO to use if being created initially or force recreated. @param bForceRecreate Force recreate the config data on the CDO. This will break instance sync and only recommended for importing.
- L63 _public prototype_ `const FString& GetConfigPath() const;`
- L64 _public prototype_ `void SetConfigPath(const FString& InPath);`
- L67 _public prototype_ `void PrepareConfigForExport();` — Configure the config with needed blueprint data for an export.
- L70 _public prototype_ `void UpdateConfigExportProperty();` — /  Updates the ConfigExport property. Called when saving the asset.
- L73 _public prototype_ `void UpdateSummaryProperty();` — /  Updates the Summary property. Called when saving the asset.
- L78 _public member_ `FString ConfigExport;` — `UPROPERTY()` — Holds the last saved config export. Added to the AssetRegistry to allow parsing without loading.
- L82 _public member_ `FString Summary;` — `UPROPERTY(AssetRegistrySearchable)` — Cache of the summary of this asset. Will be used as asset registry tag and show up in the asset tooltip.
- L87 _private prototype_ `FString GetObjectNameFromSCSNode(const UObject* const Object) const;` — Returns normal component name. We get component name from a SCS component template which has _GEN_VARIABLE postfix.
- L90 _private prototype_ `void GatherParentComponentsInfo(const USCS_Node* const InNode, TMap<UActorComponent*, FString>& OutParentsMap) const;` — Auxiliary recursive function that builds child-parentId components map
- L93 _private prototype_ `void CleanupConfigMaps(UDisplayClusterConfigurationData* Data) const;` — Auxiliary function to remove invalid pairs from the TMap containers in the config
- L97 _protected member_ `TObjectPtr<UDisplayClusterConfigurationData> ConfigData;` — `UPROPERTY()`
- L103 _private member_ `int32 AssetVersion;` — `UPROPERTY(AssetRegistrySearchable)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Blueprints/DisplayClusterBlueprintContainers.h` (Public)


#### struct `FDisplayClusterViewportContext`  
`struct FDisplayClusterViewportContext`  
_L13-45_
- reflection: `USTRUCT()`
- L20 _public member_ `FString ViewportID;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Viewport Name
- L24 _public member_ `FIntPoint RectLocation = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Location on a backbuffer.
- L28 _public member_ `FIntPoint RectSize = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Size on a backbuffer.
- L32 _public member_ `FVector ViewLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Camera view location
- L36 _public member_ `FRotator ViewRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Camera view rotation
- L40 _public member_ `FMatrix ProjectionMatrix = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Camera projection Matrix
- L44 _public member_ `bool bIsRendering = true;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Rendering status for this viewport (Overlay and other configuration rules can disable rendering for this viewport.)

#### struct `FDisplayClusterViewportStereoContext`  
`struct FDisplayClusterViewportStereoContext`  
_L48-80_
- reflection: `USTRUCT()`
- L55 _public member_ `FString ViewportID;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Viewport Name
- L59 _public member_ `FIntPoint RectLocation = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Location on a backbuffer.
- L63 _public member_ `FIntPoint RectSize = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Size on a backbuffer.
- L67 _public member_ `TArray<FVector> ViewLocation;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Camera view location
- L71 _public member_ `TArray<FRotator> ViewRotation;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Camera view rotation
- L75 _public member_ `TArray<FMatrix> ProjectionMatrix;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Camera projection Matrix
- L79 _public member_ `bool bIsRendering = true;` — `UPROPERTY(EditAnywhere, Category = "NDisplay")` — Rendering status for this viewport (Overlay and other configuration rules can disable rendering for this viewport.)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Blueprints/DisplayClusterBlueprintGeneratedClass.h` (Public)


#### class `UDisplayClusterBlueprintGeneratedClass`  
`class UDisplayClusterBlueprintGeneratedClass : public UBlueprintGeneratedClass`  
_L9-14_
- reflection: `UCLASS()`
- inherits: `UBlueprintGeneratedClass`
- L13 _private prototype_ `UDisplayClusterBlueprintGeneratedClass();`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Blueprints/DisplayClusterBlueprintLib.h` (Public)


#### class `UDisplayClusterBlueprintLib`  
`class UDisplayClusterBlueprintLib : public UBlueprintFunctionLibrary`  
_L23-120_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint API function library
- L33 _public prototype_ `static void GetAPI(TScriptInterface<IDisplayClusterBlueprintAPI>& OutAPI);` — `UE_DEPRECATED(5.4, "GetAPI function has been deprecated. All functions are now available in UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "GetAPI has been deprecated. All functions are now available in the main blueprint functions list under 'nDisplay' category."))` — [DEPRECATED] Return Display Cluster API interface.
- L39 _public prototype_ `static EDisplayClusterOperationMode GetOperationMode();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Operation Mode"), Category = "NDisplay")` — Returns current operation mode.
- L43 _public prototype_ `static ADisplayClusterRootActor* GetRootActor();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Active Root Actor"), Category = "NDisplay")` — Returns currently active root actor.
- L49 _public prototype_ `static FString GetNodeId();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Node ID"), Category = "NDisplay|Cluster")` — Returns Id of the current node in a cluster.
- L53 _public prototype_ `static void GetActiveNodeIds(TArray<FString>& OutNodeIds);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Cluster Node IDs"), Category = "NDisplay|Cluster")` — Returns List of the active nodes in the runtime cluster node in a cluster.
- L57 _public prototype_ `static int32 GetActiveNodesAmount();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Cluster Nodes Amount"), Category = "NDisplay|Cluster")` — Returns amount of active nodes in a cluster.
- L61 _public prototype_ `static bool IsPrimary();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Primary Node"), Category = "NDisplay|Cluster")` — Returns true if current node is a primary node in a cluster.
- L65 _public prototype_ `static bool IsSecondary();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Secondary Node"), Category = "NDisplay|Cluster")` — Returns true if current node is a secondary node in a cluster.
- L69 _public prototype_ `static bool IsBackup();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Backup Node"), Category = "NDisplay|Cluster")` — Returns true if current node is a backup node in a cluster.
- L73 _public prototype_ `static bool HasClusterRole(EDisplayClusterNodeRole Role);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Has a Role"), Category = "NDisplay|Cluster")` — Checks if the node has a specific role.
- L77 _public prototype_ `static EDisplayClusterNodeRole GetClusterRole();` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Cluster Node Role"), Category = "NDisplay|Cluster")` — Returns the role of the current cluster node.
- L81 _public prototype_ `static void AddClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Cluster Event Listener"), Category = "NDisplay|Cluster|Events")` — Adds cluster event listener.
- L85 _public prototype_ `static void RemoveClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove Cluster Event Listener"), Category = "NDisplay|Cluster|Events")` — Removes cluster event listener.
- L89 _public prototype_ `static void EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Emit JSON Cluster Event"), Category = "NDisplay|Cluster|Events")` — Emits JSON cluster event.
- L93 _public prototype_ `static void EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Emit Binary Cluster Event"), Category = "NDisplay|Cluster|Events")` — Emits binary cluster event.
- L97 _public prototype_ `static void SendClusterEventJsonTo(const FString& Address, const int32 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send JSON Event To Host"), Category = "NDisplay|Cluster|Events")` — Sends JSON cluster event to a specific target (may be outside of the cluster).
- L101 _public prototype_ `static void SendClusterEventBinaryTo(const FString& Address, const int32 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send Binary Event To Host"), Category = "NDisplay|Cluster|Events")` — Sends binary cluster event to a specific target (may be outside of the cluster).
- L107 _public prototype_ `static ADisplayClusterLightCardActor* CreateLightCard(ADisplayClusterRootActor* RootActor);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Create Light Card"), Category = "NDisplay|LC & CK")` — Create a new light card parented to the given nDisplay root actor.
- L111 _public prototype_ `static void DuplicateLightCards(TArray<ADisplayClusterLightCardActor*> OriginalLightcards, TArray<ADisplayClusterLightCardActor*>& OutNewLightCards);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Duplicate Light Cards"), Category = "NDisplay|LC & CK")` — Create duplicates of a list of existing light cards.
- L115 _public prototype_ `static void FindLightCardsForRootActor(const ADisplayClusterRootActor* RootActor, TSet<ADisplayClusterLightCardActor*>& OutLightCards);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Find Light Cards"), Category = "NDisplay|LC & CK")` — Gets a list of all light card actors on the level linked to the specified root actor.
- L119 _public prototype_ `static void FindChromakeyCardsForRootActor(const ADisplayClusterRootActor* RootActor, TSet<ADisplayClusterChromakeyCardActor*>& OutChromakeyCards);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Find Chromakey Cards"), Category = "NDisplay|LC & CK")` — Gets a list of all chromakey card actors on the level linked to the specified root actor.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Blueprints/IDisplayClusterBlueprintAPI.h` (Public)


#### class `UDisplayClusterBlueprintAPI`  
`class UDisplayClusterBlueprintAPI : public UInterface`  
_L30-33_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IDisplayClusterBlueprintAPI`  
`class IDisplayClusterBlueprintAPI`  
_L38-127_
- desc: Blueprint API interface
- L46 _public prototype_ `virtual bool IsModuleInitialized() const = 0;` — `UE_DEPRECATED(5.4, "This function has been deprecated and will be removed soon.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function has been deprecated and will be removed soon."))` — Returns true if the module has been initialized.
- L51 _public prototype_ `virtual EDisplayClusterOperationMode GetOperationMode() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns current operation mode.
- L57 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns DisplayCluster root actor.
- L64 _public prototype_ `virtual FString GetNodeId() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns Id of the current node in a cluster.
- L69 _public prototype_ `virtual void GetActiveNodeIds(TArray<FString>& OutNodeIds) const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns List of the active nodes in the runtime cluster node in a cluster.
- L74 _public prototype_ `virtual int32 GetActiveNodesAmount() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns amount of active nodes in a cluster.
- L79 _public prototype_ `virtual bool IsPrimary() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns true if current node is a primary node in a cluster.
- L84 _public prototype_ `virtual bool IsSecondary() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns true if current node is a secondary node in a cluster.
- L89 _public prototype_ `virtual bool IsBackup() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns true if current node is a backup node in a cluster.
- L94 _public prototype_ `virtual EDisplayClusterNodeRole GetClusterRole() const = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Returns the role of the current cluster node.
- L101 _public prototype_ `virtual void AddClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Adds cluster event listener.
- L106 _public prototype_ `virtual void RemoveClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Removes cluster event listener.
- L111 _public prototype_ `virtual void EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Emits JSON cluster event.
- L116 _public prototype_ `virtual void EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Emits binary cluster event.
- L121 _public prototype_ `virtual void SendClusterEventJsonTo(const FString& Address, const int32 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Sends JSON cluster event to a specific target (outside of the cluster).
- L126 _public prototype_ `virtual void SendClusterEventBinaryTo(const FString& Address, const int32 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) = 0;` — `UE_DEPRECATED(5.4, "This function has been moved to UDisplayClusterBlueprintLib.")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now available in the main blueprint functions list under 'nDisplay' section."))` — Sends binary cluster event to a specific target (outside of the cluster).

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/CustomStates/DisplayClusterCustomStateBase.h` (Public)


#### class `UE::nDisplay::Private::FCustomStateBase`  
`class FCustomStateBase : public IDisplayClusterCustomState`  
_L16-83_
- inherits: `IDisplayClusterCustomState`
- desc: Type-independent base class for custom states
- L21 _public prototype_ `FCustomStateBase(const FName& UniqueName, const FName& ClusterNodeId);`
- L22 _public prototype_ `virtual ~FCustomStateBase() = default;`
- L27 _public prototype_ `virtual FName GetName() const override;`
- L28 _public prototype_ `virtual void Lock() const override;`
- L29 _public prototype_ `virtual void Unlock() const override;`
- L39 _protected prototype_ `void ExecuteOnRenderThread(TUniqueFunction<void()> FuncRT);` — Type-independent private implementation of render task scheduler. The main idea of this function is to keep ENQUEUE_RENDER_COMMAND in the private space, and therefore not introduce any new public dependencies on RenderCore.
- L44 _protected function_ `IDisplayClusterClusterManager* GetClusterMgr() const` — Quick access for ClusterMgr cached pointer
- L50 _protected function_ `const FName& GetNodeId() const` — Quick access for this cluster node ID
- L56 _protected function_ `FCriticalSection& GetCritSec() const` — Access to the main access guard of the state instance
- L62 _protected function_ `TSharedRef<FCriticalSection> GetCritSecRef() const` — Access to the main access guard of the state instance
- L70 _private member_ `const FName UniqueName;` — Unique ID of this state
- L73 _private member_ `const FName ClusterNodeId;` — Id of this cluster node to speed up internal operations
- L76 _private member_ `IDisplayClusterClusterManager* ClusterMgr = nullptr;` — DC cluster manager to speed up internal operations
- L82 _private member_ `TSharedRef<FCriticalSection> StateCS;` — Main access guard for this state instance, wrapped in a shared reference to ensure thread-safe sharing.

#### class `UE::nDisplay::Private::TCustomStateData`  
`template <typename TDataType> class TCustomStateData : public FCustomStateBase`  
_L92-245_
- inherits: `FCustomStateBase`
- desc: Custom state data class Provides general control over local/cluster state data. Also manages game and render thread data.
- L98 _public function_ `template <typename... TArgs> TCustomStateData(const FName& InUniqueName, const FName& InNodeId, TArgs&&... Args) : FCustomStateBase(InUniqueName, InNodeId) , ClusterStatesData(MakeShared<TMap<FName, FCustomStateDataHolder<TDataType>>>())`
- L106 _public prototype_ `virtual ~TCustomStateData() = default;`
- L111 _public function_ `const TDataType& GetData() const` — Returns local state data bound to current thread and frame
- L120 _public function_ `template <typename TValue> requires std::convertible_to<TValue, TDataType> void SetData(TValue&& NewData)` — Sets new state data for the next frame.
- L132 _protected function_ `virtual bool IsSetDataAllowed() const` — Ask children whether SetData is allowed for the instance.
- L140 _protected function_ `TDataType& GetThreadData()` — Internal thread sensitive getter of local state data
- L146 _protected function_ `const TDataType& GetThreadData() const` — Internal thread sensitive getter of local state data (const version)
- L152 _protected function_ `TDataType& GetThreadData(const FName& NodeId, bool bCreateIfNotExists = false)` — Internal thread sensitive getter of a specific node state data
- L159 _protected function_ `const TDataType& GetThreadData(const FName& NodeId) const` — Internal thread sensitive getter of a specific node state data (const version)
- L166 _protected function_ `TSet<FName> GetNodes() const` — Returns node IDs available in the storage
- L176 _protected function_ `void AdvanceFrameData_GT()` — Game thread data update
- L185 _protected function_ `void AdvanceFrameData_RT()` — Render thread data update
- L211 _private function_ `template <typename THolderType> static auto& GetThreadDataImpl(THolderType& Holder)` — Internal helper to get data based on the current thread (for const and non-const callers)
- L241 _private member_ `TSharedRef<TMap<FName, FCustomStateDataHolder<TDataType>>> ClusterStatesData;` — Holds data of this state on all nodes. Its content type depends on the concrete state implementation. Wrapped into a TSharedPtr to ensure safe access across threads.
- L244 _private member_ `TDataType NextFrameData{ };` — Data to use on the next frame

#### struct `UE::nDisplay::Private::TCustomStateData::FCustomStateDataHolder`  
`template <typename THolderDataType> struct FCustomStateDataHolder`  
_L228-235_
- desc: Auxiliary structure that holds all necessary data of a single state
- L231 _public member_ `THolderDataType Data { };` — Game thread data
- L234 _public member_ `THolderDataType DataRT { };` — Render thread data

#### struct `UE::nDisplay::Private::TCustomStateFactory`  
`template <typename TDataType> struct TCustomStateFactory`  
_L255-301_
- desc: Factory method implementation for custom state templates Provides a simple way to instantiate custom states of any types. It also performs some additional checks, and automatically registers newly created states.
- L262 _public function_ `template <typename... TArgs> requires std::derived_from<TDataType, FCustomStateBase> static TSharedPtr<TDataType> Create(const FName& InUniqueName, TArgs&&... Args)` — Custom states factory method

#### class `UE::nDisplay::Private::TCustomStateTypeId`  
`template<typename TType> class TCustomStateTypeId`  
_L312-371_
- desc: Type ID generator It's an auxiliary class that provides a way to differentiate various state implementations (template specialization) in runtime without RTTI. It converts the text based function signatures into FName which is quite good for serialization and comparison.
- L317 _public function_ `static const FName& GetTypeId()` — Type getter
- L334 _private function_ `static FName GenerateTypeId()` — Internal type name generator. Extracts the actual TType from the full function signature. For example, full signature might be like this: {Signature=L"class FName __cdecl UE::nDisplay::Private::TCustomStateTypeId<class TDistributedCustomState<struct FMyStruct> >::GenerateTypeId(void)" } The type ID would be: class TDistributedCustomState<struct FMyStruct>

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace nDisplay` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::nDisplay`)
- L200 _function_ `` (scope `UE::nDisplay::Private::TCustomStateData::AdvanceFrameData_RT`)
- L344 _function_ `` (scope `UE::nDisplay::Private::TCustomStateTypeId::GenerateTypeId`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/CustomStates/DisplayClusterCustomStateDistributed.h` (Public)


#### class `TDistributedCustomState`  
`template <typename TDataType> class TDistributedCustomState : public UE::nDisplay::Private::TCustomStateData<TDataType> , public UE::nDisplay::Private::TCustomStateFactory<TDistributedCustomState<TDataType>>`  
_L133-277_
- inherits: `UE::nDisplay::Private::TCustomStateData<TDataType>,UE::nDisplay::Private::TCustomStateFactory<TDistributedCustomState<TDataType>>`
- desc: Distributed custom state This state enables data exchange in any direction within a cluster. By default, any cluster node can access the values of any other node. An additional API is provided to customize data propagation paths in arbitrary ways. GetData() and GetData(NodeId) are thread-sensitive. The data is maintained in separate copies for the game and render threads. Access from other threads is not supported. Distributed states are automatically registered for replication during creation (see the Create() call in the examples below). Once registered, replication within the cluster begins immediately. To stop replication, the state must be explicitly unregistered. This state type has no leader or explicit data source; it is a generic mechanism for data exchange. Data propagation is performed synchronously to preserve determinism, which may introduce update latency. When the state is modified on the game thread, the expected latency is one frame: a value set on frame N becomes visible via GetData() on frame N + 1. If the value is updated before state synchronization, no latency is introduced. When modified on the render thread, the latency may be 2–3 frames, as the value is first propagated to the game thread and then passed back to the render thread. This class uses internal data serialization. Any custom TDataType must provide its own serialization functions. Refer to the examples below for details. +---------------------+       +---------------------+ ¦   NodeA::Value=
- L140 _private typedef_ `using ThisType = TDistributedCustomState<TDataType>;`
- L161 _private function_ `template <typename... TArgs> TDistributedCustomState(const FName& InUniqueName, const FName& InNodeId, TArgs&&... Args) : UE::nDisplay::Private::TCustomStateData<TDataType>(InUniqueName, InNodeId, Forward<TArgs>(Args)...) , UE::nDisplay::Private::TCustomStateFactory<TDistributedCustomState<TDataType>>()` — Private constructor. Only factory method can instantiate this class.
- L168 _public prototype_ `virtual ~TDistributedCustomState() = default;`
- L174 _public function_ `virtual FName GetType() const override`
- L179 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L186 _public function_ `virtual void AdvanceFrame() override`
- L199 _public function_ `virtual bool HasCustomUpstreamConfiguration() const override`
- L205 _public function_ `virtual TSet<FName> GetUpstreams() const`
- L211 _public function_ `virtual void Update(const TMap<FName, TArray<uint8>>& ClusterStates) override`
- L238 _public function_ `const TDataType& GetData(const FName& NodeId) const` — Returns state data of a specific node. The data is bound to current thread and frame.
- L245 _public function_ `TSet<FName> GetAvailableNodes() const` — Returns node IDs available in the storage
- L253 _public function_ `void SetCustomUpstreamsEnabled(bool bEnabled)` — Enable/disable custom upstream configuration
- L264 _public function_ `void SetUpstreams(const TSet<FName>& NewUpstreamNodes)` — Configure upstream nodes that should propagate their updates to this state instance @param NewUpstreamNodes - new set of cluster node IDs
- L273 _private member_ `bool bUseCustomUpstreamConfiguration = false;` — Whether custom upstream configuration is enabled
- L276 _private member_ `TSet<FName> UpstreamNodes;` — Custom upstream cluster node IDs

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/CustomStates/DisplayClusterCustomStateShared.h` (Public)


#### class `TSharedCustomState`  
`template <typename TDataType> class TSharedCustomState : public UE::nDisplay::Private::TCustomStateData<TDataType> , public UE::nDisplay::Private::TCustomStateFactory<TSharedCustomState<TDataType>>`  
_L108-199_
- inherits: `UE::nDisplay::Private::TCustomStateData<TDataType>,UE::nDisplay::Private::TCustomStateFactory<TSharedCustomState<TDataType>>`
- desc: Shared custom state. "Shared" means there is a single source of truth. This implementation always propagates the state data from the primary node to all other nodes. Regardless of which node GetData() is called on, the returned data will always match the primary node's value. Consequently, SetData() is ignored on all non-primary nodes. GetData() is thread-sensitive. The state maintains separate copies for the game and render threads. Access from other threads is not supported. Shared states are automatically registered for replication during creation (see the Create() call in the examples below). Once registered, replication within the cluster begins immediately. To stop replication, the state must be explicitly unregistered. Data propagation is performed synchronously to preserve determinism, which may introduce update latency. When the state is modified on the game thread, the expected latency is one frame: a value set on frame N becomes visible via GetData() on frame N + 1. If the value is updated before state synchronization, no latency is introduced. When updated on the render thread, latency may be 2–3 frames, as the value is first propagated to the game thread and then back to the render thread. This class uses internal data serialization. Any custom TDataType must provide its own serialization functions. Refer to the examples below for details. +----------------+                    +--------------------+ ¦  Primary node  ¦                    ¦   Secondary node   ¦ +--
- L115 _private typedef_ `using ThisType = TSharedCustomState<TDataType>;`
- L129 _private function_ `template <typename... TArgs> TSharedCustomState(const FName& InUniqueName, const FName& InNodeId, TArgs&&... Args) : UE::nDisplay::Private::TCustomStateData<TDataType>(InUniqueName, InNodeId, Forward<TArgs>(Args)...) , UE::nDisplay::Private::TCustomStateFactory<TSharedCustomState<TDataType>>()` — Private constructor. Only factory method can instantiate this class.
- L136 _public prototype_ `virtual ~TSharedCustomState() = default;`
- L142 _public function_ `virtual FName GetType() const override`
- L147 _public function_ `virtual bool ShouldPropagate() const override`
- L153 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L160 _public function_ `virtual void AdvanceFrame() override`
- L176 _public function_ `virtual void Update(const TMap<FName, TArray<uint8>>& ClusterStates) override`
- L194 _protected function_ `virtual bool IsSetDataAllowed() const override final`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/CustomStates/IDisplayClusterCustomState.h` (Public)


#### class `IDisplayClusterCustomState`  
`class IDisplayClusterCustomState`  
_L13-111_
- desc: Custom state interface
- L17 _public prototype_ `virtual ~IDisplayClusterCustomState() = default;`
- L26 _public prototype_ `virtual FName GetName() const = 0;` — Returns custom state's unique name @return Unique state name
- L39 _public function_ `virtual FName GetType() const` — Returns type identificator Custom states are implemented using C++ templates, which allows them to carry arbitrary payload types. Since RTTI is not used, it is not possible to determine at runtime whether two states with the same name also share the same payload type. If such a type mismatch occurs, serialization will fail and the application will likely crash. To prevent this, each state is associated with a unique type ID. @return Type ID
- L49 _public function_ `virtual bool ShouldPropagate() const` — Whether this state should propagate its data to any other cluster nodes @return True if we need to propagate it within a cluster
- L61 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;` — Serialization It's used to serialize data of a custom state into an output buffer @param Ar - An archive to write data in
- L69 _public function_ `virtual bool HasCustomUpstreamConfiguration() const` — Whether this state requires some custom update path. If returns true, then GetUpstreams() will be called next in order to configure data senders. @return - True if has its own list of upstream nodes
- L81 _public function_ `virtual TSet<FName> GetUpstreams() const` — Returns set of node IDs that this custom state is expecting to get updates from. Based on the data propagation technique, this may disable any data senders, even all of them. It can also be used to reduce traffic while replicationg huge blobs. @return - A set of cluster node IDs that should propagate their updates to this instance
- L89 _public function_ `virtual void AdvanceFrame()` — Progress to the next frame
- L100 _public prototype_ `virtual void Update(const TMap<FName, TArray<uint8>>& ClusterStates) = 0;` — Deserialization It's used to deserialize and process post-synchronization response data, and probably update internal data. @param ClusterStates - ClusterNodeId-to-StateData blobs
- L105 _public prototype_ `virtual void Lock() const = 0;` — Lock this state to prevent any changes
- L110 _public prototype_ `virtual void Unlock() const = 0;` — Enable any changes after Lock() call

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/DisplayClusterClusterEvent.h` (Public)


#### struct `FDisplayClusterClusterEventBase`  
`struct FDisplayClusterClusterEventBase`  
_L18-45_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public function_ `FDisplayClusterClusterEventBase() : bIsSystemEvent(false) , bShouldDiscardOnRepeat(true)`
- L29 _public prototype_ `virtual ~FDisplayClusterClusterEventBase() = default;`
- L35 _public member_ `bool bIsSystemEvent = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Is Sytem Event. 'True' is reserved for nDisplay internals."), Category = "NDisplay")` — Is nDisplay internal event(should never be true for end users)
- L39 _public member_ `bool bShouldDiscardOnRepeat = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Should older events with the same Name / Type / Category(for JSON) or ID(for binary) be discarded if a new one received
- L44 _public prototype_ `virtual void Serialize(FArchive& Ar);` — Serialization

#### struct `FDisplayClusterClusterEventJson`  
`struct FDisplayClusterClusterEventJson : public FDisplayClusterClusterEventBase`  
_L52-105_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDisplayClusterClusterEventBase`
- L61 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Event name(used for discarding outdated events)
- L65 _public member_ `FString Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Event type(used for discarding outdated events)
- L69 _public member_ `FString Category;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Event category(used for discarding outdated events)
- L75 _public member_ `TMap<FString, FString> Parameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Event parameters
- L80 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialization
- L90 _public prototype_ `FString ToString(bool bWithParams = false) const;` — String based representation
- L95 _public function_ `FString SerializeToString() const` — `UE_DEPRECATED(5.6, "This function has been deprecated and will be removed soon. Please use 'Serialize' for JSON event serialization.")`
- L101 _public function_ `bool DeserializeFromString(const FString& Arch)` — `UE_DEPRECATED(5.6, "This function has been deprecated and will be removed soon. Please use 'Serialize' for JSON event deserialization.")`

#### struct `FDisplayClusterClusterEventBinary`  
`struct FDisplayClusterClusterEventBinary : public FDisplayClusterClusterEventBase`  
_L112-144_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDisplayClusterClusterEventBase`
- L121 _public member_ `int32 EventId = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Event ID(used for discarding outdated events)
- L125 _public member_ `TArray<uint8> EventData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")` — Binary event data
- L130 _public prototype_ `void SerializeToByteArray(TArray<uint8>& Arch) const;` — Raw serialization
- L133 _public prototype_ `bool DeserializeFromByteArray(const TArray<uint8>& Arch);` — Raw deserialization
- L136 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialization

#### Free symbols / members of external scopes

- L9 _variable_ `constexpr const auto DisplayClusterResetSyncType = TEXT("nDC`
- L83 _function_ `friend FArchive& operator<<(FArchive& Ar, FDisplayClusterClusterEventJson& Instance)` — Serialization
- L139 _function_ `friend FArchive& operator<<(FArchive& Ar, FDisplayClusterClusterEventBinary& Instance)` — Serialization

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/DisplayClusterNetDriverHelper.h` (Public)


#### struct `FDisplayClusterNetDriverHelper`  
`struct FDisplayClusterNetDriverHelper`  
_L18-65_
- reflection: `USTRUCT()`
- L24 _public prototype_ `int32 GetNumberOfClusterNodes() const;` — Returns number of nodes in current cluster
- L27 _public prototype_ `FString GetPrimaryNodeAddress();` — Returns primary node IP address of current cluster
- L34 _public prototype_ `bool RegisterClusterEventsBinaryClient(uint32 СlusterId, const FString& ClientAddress, uint16 ClientPort);` — Creates and stores nDisplay cluster events client using cluster id and primary node parameters @param СlusterId unique identifier of cluster @param ClientAddress primary node IP address @param ClientPort primary node port
- L39 _public prototype_ `bool RemoveClusterEventsBinaryClient(uint32 СlusterId);` — Removes cluster event client for ClusterId @param СlusterId unique identifier of cluster
- L44 _public prototype_ `bool HasClient(uint32 ClusterId);` — Checks if nDisplay cluster events client registered for specified cluster @param СlusterId unique identifier of cluster
- L49 _public prototype_ `static bool GetRequiredArguments(const FURL& URL, const TCHAR*& OutClusterId, const TCHAR*& OutPrimaryNodeId, const TCHAR*& OutPrimaryNodePort, const TCHAR*& OutClusterNodesNum);` — Checks if URL has all required arguments for DisplayClusterNetDriver @param URL Url to check
- L55 _public prototype_ `bool SendCommandToCluster(uint32 СlusterId, const FDisplayClusterClusterEventBinary& NetworkDriverSyncEvent);` — Sends command to nDisplay cluster specified by id @param СlusterId identifier of cluster @param NetworkDriverSyncEvent cluster event binary data
- L60 _public prototype_ `void SendCommandToAllClusters(const FDisplayClusterClusterEventBinary& NetworkDriverSyncEvent);` — Sends command to all nDisplay clusters stored by RegisterClusterEventsBinaryClient @param NetworkDriverSyncEvent cluster event binary data
- L64 _private member_ `TMap<uint32, TSharedPtr<FDisplayClusterClusterEventsBinaryClient>> ClusterEventsBinaryClients;` — nDisplay primary node events clients for sending control messages to clusters

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/IDisplayClusterClusterEventListener.h` (Public)


#### class `UDisplayClusterClusterEventListener`  
`class UDisplayClusterClusterEventListener : public UInterface`  
_L13-22_
- reflection: `UINTERFACE()`
- inherits: `UInterface`
- L19 _public function_ `UDisplayClusterClusterEventListener(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`

#### class `IDisplayClusterClusterEventListener`  
`class IDisplayClusterClusterEventListener`  
_L28-40_
- desc: Interface for cluster event listeners
- L35 _public prototype_ `void OnClusterEventJson(const FDisplayClusterClusterEventJson& Event);` — `UFUNCTION(BlueprintImplementableEvent, Category = "NDisplay")` — React on incoming JSON cluster events
- L39 _public prototype_ `void OnClusterEventBinary(const FDisplayClusterClusterEventBinary& Event);` — `UFUNCTION(BlueprintImplementableEvent, Category = "NDisplay")` — React on incoming binary cluster events

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/IDisplayClusterClusterManager.h` (Public)


#### class `IDisplayClusterClusterManager`  
`class IDisplayClusterClusterManager`  
_L31-147_
- desc: Public cluster manager interface
- L34 _public prototype_ `virtual ~IDisplayClusterClusterManager() = default;`
- L38 _public prototype_ `virtual bool IsPrimary() const = 0;` — Returns true if current node has primary role.
- L40 _public prototype_ `virtual bool IsSecondary() const = 0;` — Returns true if current node has secondary role.
- L42 _public prototype_ `virtual bool IsBackup() const = 0;` — Returns true if current node has backup role.
- L44 _public prototype_ `virtual EDisplayClusterNodeRole GetClusterRole() const = 0;` — Returns cluster node role.
- L46 _public prototype_ `virtual bool HasClusterRole(EDisplayClusterNodeRole Role) const = 0;` — Checks if the node has a specific role.
- L49 _public prototype_ `virtual FString GetPrimaryNodeId() const = 0;` — Returns current primary node ID.
- L52 _public prototype_ `virtual FString GetNodeId() const = 0;` — Returns current cluster node ID.
- L54 _public prototype_ `virtual uint32 GetNodesAmount() const = 0;` — Returns amount of cluster nodes in the cluster.
- L56 _public prototype_ `virtual void GetNodeIds(TArray<FString>& OutNodeIds) const = 0;` — Returns IDs of available cluster nodes.
- L58 _public prototype_ `virtual void GetNodeIds(TSet<FString>& OutNodeIds) const = 0;` — Returns IDs of available cluster nodes.
- L61 _public prototype_ `virtual bool DropClusterNode(const FString& NodeId) = 0;` — Drop specific cluster node
- L64 _public prototype_ `virtual void RegisterSyncObject(IDisplayClusterClusterSyncObject* SyncObj, EDisplayClusterSyncGroup SyncGroup) = 0;` — Registers object to synchronize.
- L66 _public prototype_ `virtual void UnregisterSyncObject(IDisplayClusterClusterSyncObject* SyncObj) = 0;` — Unregisters synchronization object.
- L76 _public prototype_ `virtual bool RegisterCustomState(const FName& UniqueStateName, TSharedPtr<IDisplayClusterCustomState>& StateVariable) = 0;` — Registers custom state for auto-replication @param UniqueStateName - Unique name to distinguish different states @param StateVariable   - A variable that references the state @return True if registered successfully, otherwise false (has been registered already)
- L85 _public prototype_ `virtual bool UnregisterCustomState(const FName& UniqueStateName) = 0;` — Unregisters specific custom state @param UniqueStateName - Unique name to distinguish different states @return True if unregistered successfully, otherwise false (not found)
- L92 _public prototype_ `virtual TSet<FName> GetRegisteredCustomStateNames() const = 0;` — Returns the names of all registered states @return Set of custom state names currently registered
- L99 _public prototype_ `virtual bool IsCustomStateRegistered(const FName& UniqueStateName) const = 0;` — Checks whether a custom state with the specified name has already been registered @return True if such state exists
- L103 _public prototype_ `virtual TSharedRef<IDisplayClusterGenericBarriersClient> CreateGenericBarriersClient() = 0;` — Creates a general purpose barriers interface.
- L111 _public prototype_ `virtual void AddClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener) = 0;` — Registers cluster event listener.
- L114 _public prototype_ `virtual void RemoveClusterEventListener(TScriptInterface<IDisplayClusterClusterEventListener> Listener) = 0;` — Unregisters cluster event listener.
- L117 _public prototype_ `virtual void AddClusterEventJsonListener(const FOnClusterEventJsonListener& Listener) = 0;` — Registers json cluster event listener.
- L120 _public prototype_ `virtual void RemoveClusterEventJsonListener(const FOnClusterEventJsonListener& Listener) = 0;` — Unregisters json cluster event listener.
- L123 _public prototype_ `virtual void AddClusterEventBinaryListener(const FOnClusterEventBinaryListener& Listener) = 0;` — Registers binary cluster event listener.
- L126 _public prototype_ `virtual void RemoveClusterEventBinaryListener(const FOnClusterEventBinaryListener& Listener) = 0;` — Unregisters binary cluster event listener.
- L129 _public prototype_ `virtual void EmitClusterEventJson(const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) = 0;` — Emits JSON cluster event.
- L132 _public prototype_ `virtual void EmitClusterEventBinary(const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) = 0;` — Emits binary cluster event.
- L135 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventJson& Event, bool bPrimaryOnly) = 0;` — Sends JSON cluster event to a specific target (outside of the cluster).
- L138 _public prototype_ `virtual void SendClusterEventTo(const FString& Address, const uint16 Port, const FDisplayClusterClusterEventBinary& Event, bool bPrimaryOnly) = 0;` — Sends binary cluster event to a specific target (outside of the cluster).
- L143 _public function_ `virtual TUniquePtr<IDisplayClusterGenericBarriersClient> CreateGenericBarriersClient(const FString& ClientName)` — `UE_DEPRECATED(5.6, "This API method has been deprecated. Please use 'GetGenericBarriersClient'.")`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClusterEventJson, const FDisplayClusterClusterEventJson& );`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClusterEventJson, const FDisplayClusterClusterEventJson& );`
- L22 _typedef_ `typedef FOnClusterEventJson::FDelegate FOnClusterEventJsonListener;`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClusterEventBinary, const FDisplayClusterClusterEventBinary& );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClusterEventBinary, const FDisplayClusterClusterEventBinary& );`
- L25 _typedef_ `typedef FOnClusterEventBinary::FDelegate FOnClusterEventBinaryListener;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/IDisplayClusterClusterSyncObject.h` (Public)


#### class `IDisplayClusterClusterSyncObject`  
`class IDisplayClusterClusterSyncObject : public IDisplayClusterSerializable , public IDisplayClusterStringSerializable`  
_L12-37_
- inherits: `IDisplayClusterSerializable,IDisplayClusterStringSerializable`
- desc: Synchronizable object interface
- L18 _public prototype_ `virtual ~IDisplayClusterClusterSyncObject() = default;`
- L23 _public prototype_ `virtual bool IsActive() const = 0;` — Whether an object needs to be syncrhonized on current frame
- L26 _public prototype_ `virtual FString GetSyncId() const = 0;` — Unique ID of the object being synchronized
- L29 _public function_ `virtual bool IsDirty() const` — Whether the object's state has changed since last ClearDirty call
- L35 _public function_ `virtual void ClearDirty()` — Resets the dirty flag, marking the state as not yet changed

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Cluster/IDisplayClusterGenericBarriersClient.h` (Public)


#### struct `FGenericBarrierSynchronizationDelegateData`  
`struct FGenericBarrierSynchronizationDelegateData`  
_L11-24_
- desc: Barrier synchonrization callback data
- L14 _public member_ `const FString& BarrierId;` — Barrier ID
- L17 _public member_ `const TMap<FString, FString>& ThreadToNodeMap;` — Associates the caller IDs with the owning cluster nodes (Caller ID - to - cluster node)
- L20 _public member_ `const TMap<FString, TArray<uint8>>& RequestData;` — Binary data provided on sync request (Caller ID - to - data mapping)
- L23 _public member_ `TMap<FString, TArray<uint8>>& ResponseData;` — Binary data to respond (Caller ID - to - data mapping)

#### class `IDisplayClusterGenericBarriersClient`  
`class IDisplayClusterGenericBarriersClient`  
_L30-156_
- desc: Generic barriers client interface
- L34 _public prototype_ `virtual ~IDisplayClusterGenericBarriersClient() = default;`
- L39 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGenericBarrierSynchronizationDelegate, FGenericBarrierSynchronizationDelegateData&);` — Synchronization delegate. It's called on the primary node only.
- L42 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGenericBarrierTimeoutDelegate, const TSet<FString>&);` — Barrier timeout delegate. It's called on the primary node only.
- L55 _public prototype_ `virtual bool CreateBarrier(const FString& BarrierId, const TMap<FString, TSet<FString>>& NodeToSyncCallers, uint32 Timeout) = 0;` — Creates new barrier @param BarrierId         - ID of the new barrier @param NodeToSyncCallers - NodeId-to-CallerId association map @param Timeout           - Barrier synchronization timeout @return true if the barrier was created successfully, or already exists
- L64 _public prototype_ `virtual bool WaitUntilBarrierIsCreated(const FString& BarrierId) = 0;` — Wait until a barrier with specific ID is created and ready to go @param BarrierId - ID of the barrier to wait @return true if created or existed
- L73 _public prototype_ `virtual bool IsBarrierAvailable(const FString& BarrierId) = 0;` — Checks if a specific barrier exists @param BarrierId - ID of the barrier to check @return true if the barrier exists
- L82 _public prototype_ `virtual bool ReleaseBarrier(const FString& BarrierId) = 0;` — Releases specific barrier @param BarrierId - ID of a barrier to release @return true if the barrier was successfully released
- L92 _public prototype_ `virtual bool Synchronize(const FString& BarrierId, const FString& CallerId) = 0;` — Synchronize the calling thread on a specific barrier @param BarrierId - ID of a barrier to use for synchronization @param CallerId  - ID of a synchronization caller (thread) @return true if synchronization succeeded
- L104 _public prototype_ `virtual bool Synchronize(const FString& BarrierId, const FString& CallerId, const TArray<uint8>& RequestData, TArray<uint8>& OutResponseData) = 0;` — Synchronize the calling thread on a specific barrier with custom data @param BarrierId   - ID of a barrier to use for synchronization @param CallerId    - ID of a synchronization caller (thread) @param RequestData - Synchronization request data of the calling thread (caller) @param OutResponseData - [out] Synchronization response data @return true if synchronization succeeded
- L115 _public prototype_ `virtual FOnGenericBarrierSynchronizationDelegate* GetBarrierSyncDelegate(const FString& BarrierId) = 0;` — Returns synchronization delegate of a specific barrier. This delegate is called on the primary node only. @param BarrierId - ID of the barrier @return Synchronization delegate or nullptr if barrier is not available
- L124 _public prototype_ `virtual FOnGenericBarrierTimeoutDelegate* GetBarrierTimeoutDelegate(const FString& BarrierId) = 0;` — Returns timeout delegate of a specific barrier. This delegate is called on the primary node only. @param BarrierId - ID of the barrier @return Timeout delegate or nullptr if barrier is not available
- L129 _public function_ `virtual bool Connect()` — `UE_DEPRECATED(5.6, "This method has been deprecated. There is no need to connect/disconnect anymore.")`
- L135 _public function_ `virtual void Disconnect()` — `UE_DEPRECATED(5.6, "This method has been deprecated. There is no need to connect/disconnect anymore.")`
- L140 _public function_ `virtual bool IsConnected() const` — `UE_DEPRECATED(5.6, "This method has been deprecated. There is no need to connect/disconnect anymore.")`
- L146 _public function_ `virtual FString GetName() const` — `UE_DEPRECATED(5.6, "This method has been deprecated.")`
- L152 _public function_ `virtual bool CreateBarrier(const FString& BarrierId, const TArray<FString>& UniqueThreadMarkers, uint32 Timeout)` — `UE_DEPRECATED(5.6, "This method has been deprecated. Please use a TMap based version of CreateBarrier.")`

#### struct `FDisplayClusterGenericBarriersClientDeleter`  
`struct UE_DEPRECATED(5.6, "No longer used.") FDisplayClusterGenericBarriersClientDeleter`  
_L159-163_
- L161 _public function_ `void operator()(void*)`

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGenericBarrierSynchronizationDelegate, FGenericBarrierSynchronizationDelegateData&);` — Synchronization delegate. It's called on the primary node only.
- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGenericBarrierTimeoutDelegate, const TSet<FString>&);` — Barrier timeout delegate. It's called on the primary node only.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterCameraComponent.h` (Public)


#### enum `EDisplayClusterEyeStereoOffset`  
`enum class EDisplayClusterEyeStereoOffset : uint8`  
_L29-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `None UMETA(DisplayName = "Default")`
- L32 _public enumerator_ `Left UMETA(DisplayName = "Left Eye")`
- L33 _public enumerator_ `Right UMETA(DisplayName = "Right Eye")`

#### enum `EDisplayClusterTargetCameraType`  
`enum class EDisplayClusterTargetCameraType: int32`  
_L38-51_
- reflection: `UENUM()`
- desc: The type of camera used.
- L41 _public enumerator_ `None UMETA(DisplayName = "Disabled")` — No camera used
- L44 _public enumerator_ `ActiveEngineCamera UMETA(DisplayName = "Active Engine Camera")` — Use active engine camera
- L47 _public enumerator_ `ICVFXCameraComponent UMETA(DisplayName = "ICVFX Camera")` — Use camera component from the root actor
- L50 _public enumerator_ `ExternalCineCameraActor UMETA(DisplayName = "Camera Actor")` — Use the CineCamera actor reference.

#### class `UDisplayClusterCameraComponent`  
`class UDisplayClusterCameraComponent : public USceneComponent , public IDisplayClusterComponent`  
_L58-361_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), HideCategories = (Navigation, AssetUserData, LOD, Physics, Cooking, Activation, Tags, Gizmo, Collision, ComponentReplication, Events, Sockets, ComponentTick, Rendering), meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay View Point"))`
- inherits: `USceneComponent,IDisplayClusterComponent`
- desc: 3D point in space used to render nDisplay viewports from
- L65 _public prototype_ `UDisplayClusterCameraComponent(const FObjectInitializer& ObjectInitializer);`
- L74 _public function_ `virtual void GetDesiredView(FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr)` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetDesiredView()'.")` — Return ViewPoint for this component If the component logic supports postprocess, it will also be in the ViewInfo structure. @param InOutViewInfo - ViewInfo data @param OutCustomNearClippingPlane - Custom NCP, or a value less than zero if not defined.
- L83 _public prototype_ `virtual void GetDesiredView(const IDisplayClusterViewportConfiguration& InViewportConfiguration, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) const;` — Return ViewPoint for this component If the component logic supports postprocess, it will also be in the ViewInfo structure. @param InOutViewInfo - ViewInfo data @param OutCustomNearClippingPlane - Custom NCP, or a value less than zero if not defined.
- L86 _public prototype_ `virtual void GetEyePosition(const IDisplayClusterViewportConfiguration& InViewportConfiguration, FVector& OutViewLocation, FRotator& OutViewRotation);` — Returns the position of the observer's eyes in the Stage.
- L91 _public function_ `virtual bool ShouldUseEntireClusterViewports(IDisplayClusterViewportManager* InViewportManager) const` — All cluster viewports that reference this component will be created in the background on the current cluster node if the function returns true.
- L100 _public function_ `virtual IDisplayClusterWarpPolicy* GetWarpPolicy(IDisplayClusterViewportManager* InViewportManager)` — Get the warp policy instance used by this compoenent. From the DC ViewportManager, these policies will be assigned to the viewports that use this viewpoint component.
- L113 _public function_ `virtual TObjectPtr<UMaterial> GetDisplayDeviceMaterial(const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType) const` — Override DisplayDevice material by type for The UDisplayClusterInFrustumFitCameraComponent uses its own material to display additional deformed preview meshes in front of the camera. @param InMeshType     - mesh type @param InMaterialType - the type of material being requested @return nullptr if DisplayDevice material is used.
- L126 _public function_ `virtual void OnUpdateDisplayDeviceMeshAndMaterialInstance(IDisplayClusterViewportPreview& InViewportPreview, const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType, UMeshComponent* InMeshComponent, UMaterialInstanceDynamic* InMeshMaterialInstance) const` — Perform any operations on the mesh and material instance, such as setting parameter values. @param InViewport             - current viewport @param InMeshType             - mesh type @param InMaterialType         - type of material being requested @param InMeshComponent        - mesh component to be updated @param InMeshMaterialInstance - material instance that used on this mesh
- L134 _public prototype_ `virtual void ApplyViewPointComponentPostProcessesToViewport(IDisplayClusterViewport* InViewport);` — Apply the ViewPoint component's post-processes to the viewport. (Outer viewport camera) @param InViewport - viewport to be configured.
- L140 _public prototype_ `virtual UCameraComponent* GetTargetCameraComponent(const IDisplayClusterViewportConfiguration& InViewportConfiguration) const;` — Return a reference to the Camera component, which is used for Outer viewports. return nullptr if the camera is not in use.
- L143 _public prototype_ `virtual bool IsViewPointOverrideCameraPosition() const;` — Returns true if the given viewpoint position should be used as a camera position.
- L146 _public prototype_ `virtual bool CanOverrideEyePosition() const;` — Returns true if the eye position (ViewPoint) inside the DCRa can be overriden.
- L149 _public prototype_ `virtual bool ShouldFollowCameraLocation() const;` — Returns true if ViewPoint should use the camera position instead of the DCRA position when transforming.
- L153 _protected prototype_ `virtual bool GetTargetCameraDesiredViewInternal(const IDisplayClusterViewportConfiguration& InViewportConfiguration, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) const;` — Get view from the referenced camera.
- L156 _protected prototype_ `virtual bool GetEditorPreviewInfo(float DeltaTime, FMinimalViewInfo& ViewOut) override;`
- L157 _protected prototype_ `virtual TSharedPtr<SWidget> GetCustomEditorPreviewWidget() override;`
- L167 _public function_ `float GetInterpupillaryDistance() const` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Get interpupillary distance @return - Interpupillary distance
- L178 _public function_ `void SetInterpupillaryDistance(float Distance)` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Set interpupillary distance @param Distance - New interpupillary distance
- L189 _public function_ `bool GetSwapEyes() const` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Get swap eyes state @return - Eyes swap state. False - normal eyes left|right, true - swapped eyes right|left
- L200 _public function_ `void SetSwapEyes(bool SwapEyes)` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Set swap eyes state @param SwapEyes - New eyes swap state. False - normal eyes left|right, true - swapped eyes right|left
- L211 _public function_ `bool ToggleSwapEyes()` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Toggles eyes swap state @return - New eyes swap state. False - normal eyes left|right, true - swapped eyes right|left
- L222 _public function_ `EDisplayClusterEyeStereoOffset GetStereoOffset() const` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Get stereo offset type @return - Current forced stereo offset type
- L233 _public function_ `void SetStereoOffset(EDisplayClusterEyeStereoOffset InStereoOffset)` — `UFUNCTION(BlueprintCallable, Category = "Stereo")` — Set stereo offset type @param StereoOffset - New forced stereo offset type
- L240 _public prototype_ `EDisplayClusterViewportCameraPostProcessFlags GetCameraPostProcessFlags() const;` — Decodes parameters into flags.
- L243 _public prototype_ `virtual UCameraComponent* GetExternalCineCameraActorComponent() const;` — Returns the camera component from the 'ExternalCameraActor' parameter.
- L247 _protected prototype_ `virtual bool IsActiveEngineCameraBeingUsed() const;` — Returns true if active engine camera is used.
- L250 _protected prototype_ `virtual bool IsICVFXCameraBeingUsed() const;` — Returns true if the `ICVFXCameraComponentName` parameter is used.
- L253 _protected prototype_ `virtual bool IsExternalCameraBeingUsed() const;` — Returns true if the `ExternalCineCameraActor` parameter is used.
- L257 _protected prototype_ `virtual UCameraComponent* GetEditorPreviewCameraComponent();` — Return used camera component.
- L263 _public prototype_ `virtual void SetVisualizationScale(float Scale) override;`
- L264 _public prototype_ `virtual void SetVisualizationEnabled(bool bEnabled) override;`
- L269 _public prototype_ `virtual void OnRegister() override;`
- L274 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L275 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L282 _protected prototype_ `virtual void RefreshVisualRepresentation();` — Refreshes the visual components to match the component state
- L289 _protected member_ `uint8 bEnableGizmo : 1;` — `UPROPERTY(EditAnywhere, Category = "Gizmo")` — Gizmo visibility
- L293 _protected member_ `FVector BaseGizmoScale;` — `UPROPERTY(EditAnywhere, Category = "Gizmo")` — Base gizmo scale
- L297 _protected member_ `float GizmoScaleMultiplier;` — `UPROPERTY(EditAnywhere, Category = "Gizmo", meta = (UIMin = "0", UIMax = "2.0", ClampMin = "0.01", ClampMax = "10.0"))` — Gizmo scale multiplier
- L300 _protected member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY(Transient)`
- L303 _protected member_ `TObjectPtr<UTexture2D> SpriteTexture;` — `UPROPERTY()`
- L309 _public member_ `EDisplayClusterTargetCameraType TargetCameraType = EDisplayClusterTargetCameraType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Source Camera"))` — Type of source camera used.
- L313 _public member_ `FString ICVFXCameraComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "ICVFX Camera", EditCondition = "TargetCameraType==EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))` — The name of the camera component that is used as the PP source.
- L316 _public member_ `uint8 bUseICVFXCameraComponentTracking: 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Follow ICVFX Camera", EditCondition = "TargetCameraType==EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))`
- L320 _public member_ `uint8 bFollowCameraPosition : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Follow Camera", EditCondition = "TargetCameraType!=EDisplayClusterTargetCameraType::ICVFXCameraComponent && TargetCameraType!=EDisplayClusterTargetCameraType::None", EditConditionHides))` — Use camera position for rendering instead of RootActor.
- L324 _public member_ `TSoftObjectPtr<ACineCameraActor> ExternalCineCameraActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Camera Actor", EditCondition = "TargetCameraType==EDisplayClusterTargetCameraType::ExternalCineCameraActor", EditConditionHides))` — Use a specific actor camera instead of a game camera.
- L330 _public member_ `uint8 bEnablePostProcess : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Include Post Process Settings", EditCondition = "TargetCameraType!=EDisplayClusterTargetCameraType::None", EditConditionHides))` — Use the PP settings from the specified camera.
- L334 _public member_ `uint8 bEnableNearClippingPlane : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Include Custom Near Clipping Plane", EditCondition = "TargetCameraType!=EDisplayClusterTargetCameraType::None && TargetCameraType!=EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))` — Use the NearClippingPlane value from the specified cine camera.
- L338 _public member_ `uint8 bEnableDepthOfField : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Include Depth Of Field", EditCondition = "TargetCameraType!=EDisplayClusterTargetCameraType::None && TargetCameraType!=EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))` — Enable the DoF PP settings from the specified camera.
- L342 _public member_ `uint8 bEnableICVFXDepthOfFieldCompensation : 1 = 1;` — `UPROPERTY(BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Include Inner Frustum Depth Of Field Compensation", EditCondition = "TargetCameraType==EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))` — Use the DC Depth-Of-Field settings from the specified ICVFX camera.
- L346 _public member_ `uint8 bEnableICVFXColorGrading : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Include Inner Frustum Color Grading", EditCondition = "TargetCameraType==EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))` — Use the DC ColorGrading from the specified ICVFX camera.
- L350 _public member_ `uint8 bEnableICVFXMotionBlur : 1 = 1;` — `UPROPERTY(BlueprintReadWrite, Category = "Camera Settings", meta = (DisplayName = "Include Inner Frustum Motion Blur", EditCondition = "TargetCameraType==EDisplayClusterTargetCameraType::ICVFXCameraComponent", EditConditionHides))` — Use the DC Motion Blur settings from the specified ICVFX camera.
- L354 _private member_ `float InterpupillaryDistance;` — `UPROPERTY(EditAnywhere, Category = "Stereo")`
- L357 _private member_ `bool bSwapEyes;` — `UPROPERTY(EditAnywhere, Category = "Stereo")`
- L360 _private member_ `EDisplayClusterEyeStereoOffset StereoOffset;` — `UPROPERTY(EditAnywhere, Category = "Stereo")`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterChromakeyCardStageActorComponent.h` (Public)


#### class `UDisplayClusterChromakeyCardStageActorComponent`  
`class UDisplayClusterChromakeyCardStageActorComponent final : public UDisplayClusterStageActorComponent`  
_L16-48_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (DisplayCluster), meta = (DisplayName = "Chromakey Card Stage Actor"), HideCategories=(Physics, Collision, Lighting, Navigation, Cooking, LOD, MaterialParameters, HLOD, RayTracing, TextureStreaming, Mobile))`
- inherits: `UDisplayClusterStageActorComponent`
- desc: Stage Actor Component to be placed in chromakey card actors
- L22 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _public prototype_ `virtual void SetRootActor(ADisplayClusterRootActor* InRootActor) override;`
- L28 _public function_ `const TArray<FSoftComponentReference>& GetICVFXCameras() const` — Retrieve current ICVFX cameras associated with this stage actor
- L37 _public prototype_ `bool IsReferencedByICVFXCamera(const UDisplayClusterICVFXCameraComponent* InCamera) const;` — Checks if the given ICVFX camera has chroma key settings supporting this actor. @param InCamera The ICVFX camera component to compare against. @return true if the ICVFX camera component is referenced by this component.
- L41 _protected prototype_ `void PopulateICVFXOwners();` — Update linked ICVFX cameras based on current settings
- L47 _protected member_ `TArray<FSoftComponentReference> ICVFXCameras;` — `UPROPERTY(EditInstanceOnly, Category = "NDisplay Root Actor", DisplayName = "ICVFX Cameras", meta = (UseComponentPicker, AllowedClasses = "/Script/DisplayCluster.DisplayClusterICVFXCameraComponent", AllowAnyActor))` — Associate this Chromakey Card with the nDisplay configuration actor and ICVFX Camera component(s) specified here. The content will only appear in the ICVFX Editor when this nDisplay configuration is selected.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterICVFXCameraComponent.h` (Public)


#### class `UDisplayClusterICVFXCameraComponent`  
`class UDisplayClusterICVFXCameraComponent : public UCineCameraComponent`  
_L28-235_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), HideCategories = (AssetUserData, Collision, Cooking, ComponentReplication, Events, Physics, Sockets, Activation, Tags, ComponentTick), meta = (BlueprintSpawnableComponent, DisplayName="ICVFX Camera"))`
- inherits: `UCineCameraComponent`
- desc: nDisplay in-camera VFX camera representation
- L34 _public prototype_ `UDisplayClusterICVFXCameraComponent(const FObjectInitializer& ObjectInitializer);`
- L36 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L37 _public prototype_ `virtual void PostLoad() override;`
- L38 _public prototype_ `virtual void PostApplyToComponent() override;`
- L42 _public member_ `FDisplayClusterConfigurationICVFX_CameraSettings CameraSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay)`
- L45 _public prototype_ `virtual bool GetEditorPreviewInfo(float DeltaTime, FMinimalViewInfo& ViewOut) override;`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomEditorPreviewWidget() override;`
- L49 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L56 _public prototype_ `virtual void ApplyICVFXCameraPostProcessesToViewport(IDisplayClusterViewport* InDestViewport, const EDisplayClusterViewportCameraPostProcessFlags InPostProcessingFlags);` — The ICVFXCamera component uses its own PostProcess and applies it to the viewport. @param InViewport - a viewport that need to be configured with a PP settings. @param InPostProcessFlags - Define the PostProcess set that will be used
- L60 _public function_ `FDisplayClusterViewport_CameraMotionBlur GetMotionBlurParameters()` — `UE_DEPRECATED(5.5, "This function has been deprecated. Please use 'FDisplayClusterViewportConfigurationHelpers_Postprocess::GetICVFXCameraMotionBlurParameters()'.")`
- L70 _public prototype_ `UCineCameraComponent* GetActualCineCameraComponent();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ICVFX Camera")` — Return the actual source camera, e.g. the camera component of the referenced cine camera. Use GetCameraView() function to get viewinfo with actual camera position, postprocess and ICVFX postprocess
- L74 _public prototype_ `bool IsICVFXEnabled() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ICVFX Camera")` — Returns true if this camera is active in the current node.
- L77 _public prototype_ `FString GetCameraUniqueId() const;` — Return unique camera name
- L79 _public prototype_ `const FDisplayClusterConfigurationICVFX_CameraSettings& GetCameraSettingsICVFX() const;`
- L84 _public prototype_ `virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& InOutViewInfo) override;` — Obtaining view information for the actual camera, such as the camera component to which the cine-camera is referencing. The data from the CameraSettings variable is used in postprocess settings (EnableCameraPP, OverrideMotionBlur, etc.).
- L87 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface
- L91 _public prototype_ `void SetDepthOfFieldParameters(const FDisplayClusterConfigurationICVFX_CameraDepthOfField& NewDepthOfFieldParams);` — `UFUNCTION(BlueprintCallable, Category = "ICVFX Camera")` — Sets new depth of field parameters and updates the dynamically generated compensation LUT if needed
- L94 _public prototype_ `FIntPoint GetICVFXCameraFrameSize(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Get ICVFX camera frame resolution.
- L97 _public prototype_ `FDisplayClusterShaderParameters_ICVFX::FCameraSettings GetICVFXCameraShaderParameters(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings);` — Get ICVFX camera shader parameters.
- L100 _private prototype_ `void UpdateOverscanEstimatedFrameSize();`
- L108 _public prototype_ `void UpdateICVFXPreviewState();` — update the status of the Editor's ICVFX preview elements
- L111 _public member_ `TSoftObjectPtr<ACineCameraActor> ExternalCameraCachedValue;` — saves the value of external camera reference
- L113 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L114 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L120 _private member_ `FDisplayClusterEditorPropertyReference IsEnabledRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.bEnable"))`
- L123 _private member_ `FDisplayClusterEditorPropertyReference HiddenICVFXViewportsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.HiddenICVFXViewports"))`
- L126 _private member_ `FDisplayClusterEditorPropertyReference UpscalerSettingsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.UpscalerSettings"))`
- L129 _private member_ `FDisplayClusterEditorPropertyReference BufferRatioRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.BufferRatio"))`
- L132 _private member_ `FDisplayClusterEditorPropertyReference CustomFrustumRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (DisplayName = "Inner Frustum Overscan", PropertyPath = "CameraSettings.CustomFrustum"))`
- L135 _private member_ `FDisplayClusterEditorPropertyReference SoftEdgeRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.SoftEdge"))`
- L138 _private member_ `FDisplayClusterEditorPropertyReference BorderRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.Border"))`
- L141 _private member_ `FDisplayClusterEditorPropertyReference FrustumRotationRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.FrustumRotation"))`
- L144 _private member_ `FDisplayClusterEditorPropertyReference FrustumOffsetRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.FrustumOffset"))`
- L147 _private member_ `FDisplayClusterEditorPropertyReference OffCenterProjectionOffsetRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.OffCenterprojectionoffset"))`
- L150 _private member_ `FDisplayClusterEditorPropertyReference GenerateMipsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.RenderSettings.GenerateMips"))`
- L153 _private member_ `FDisplayClusterEditorPropertyReference ExternalCameraActorRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Camera ICVFX", meta = (PropertyPath = "CameraSettings.ExternalCameraActor"))`
- L157 _private member_ `FDisplayClusterEditorPropertyReference CameraDepthOfFieldRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Camera ICVFX", meta = (PropertyPath = "CameraSettings.CameraDepthOfField", DisplayName = "ICVFX Depth of Field"))` — Exposed reference to the camera's inner depth of field settings
- L160 _private member_ `FDisplayClusterEditorPropertyReference CameraMotionBlurRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Camera ICVFX", meta = (PropertyPath = "CameraSettings.CameraMotionBlur", DisplayName = "ICVFX Camera Motion Blur"))`
- L163 _private member_ `FDisplayClusterEditorPropertyReference CameraHideListRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum", meta = (PropertyPath = "CameraSettings.CameraHideList"))`
- L166 _private member_ `FDisplayClusterEditorPropertyReference ChromaKeyEnabledRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CameraSettings.Chromakey.bEnable"))`
- L169 _private member_ `FDisplayClusterEditorPropertyReference ChromakeyTypeRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CameraSettings.Chromakey.ChromakeyType"))`
- L172 _private member_ `FDisplayClusterEditorPropertyReference ChromakeySettingsSourceRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CameraSettings.Chromakey.ChromakeySettingsSource"))`
- L175 _private member_ `FDisplayClusterEditorPropertyReference ChromakeyColorRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CameraSettings.Chromakey.ChromakeyColor"))`
- L178 _private member_ `FDisplayClusterEditorPropertyReference ChromakeyMarkersRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CameraSettings.Chromakey.ChromakeyMarkers"))`
- L181 _private member_ `FDisplayClusterEditorPropertyReference ChromakeyRenderTextureRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CameraSettings.Chromakey.ChromakeyRenderTexture"))`
- L184 _private member_ `FDisplayClusterEditorPropertyReference EnableInnerFrustuOCIORef;` — `UPROPERTY(EditAnywhere, Transient, Category = OCIO, meta = (PropertyPath = "CameraSettings.CameraOCIO.AllNodesOCIOConfiguration.bIsEnabled", DisplayName = "Enable Inner Frustum OCIO"))`
- L187 _private member_ `FDisplayClusterEditorPropertyReference AllNodesOCIOConfigurationRef;` — `UPROPERTY(EditAnywhere, Transient, Category = OCIO, meta = (PropertyPath = "CameraSettings.CameraOCIO.AllNodesOCIOConfiguration.ColorConfiguration", DisplayName = "All Nodes Color Configuration"))`
- L190 _private member_ `FDisplayClusterEditorPropertyReference PerNodeOCIOProfilesRef;` — `UPROPERTY(EditAnywhere, Transient, Category = OCIO, meta = (PropertyPath = "CameraSettings.CameraOCIO.PerNodeOCIOProfiles", DisplayName = "Per-Node OCIO Overrides"))`
- L193 _private member_ `FDisplayClusterEditorPropertyReference EnableInnerFrustumColorGrading;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum Color Grading", meta = (PropertyPath = "CameraSettings.EnableInnerFrustumColorGrading", DisplayName = "Enable Inner Frustum Color Grading"))`
- L196 _private member_ `FDisplayClusterEditorPropertyReference AllNodesColorGradingRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum Color Grading", meta = (PropertyPath = "CameraSettings.AllNodesColorGrading", DisplayName = "All Nodes"))`
- L199 _private member_ `FDisplayClusterEditorPropertyReference PerNodeColorGradingRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Inner Frustum Color Grading", meta = (PropertyPath = "CameraSettings.PerNodeColorGrading"))`
- L202 _private member_ `FDisplayClusterEditorPropertyReference TextureReplacementEnabledRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Texture Replacement", meta = (PropertyPath = "CameraSettings.RenderSettings.Replace.bAllowReplace", DisplayName = "Enable Inner Frustum Texture Replacement", ToolTip = "Set to True to replace the entire inner frustum with the specified texture."))`
- L205 _private member_ `FDisplayClusterEditorPropertyReference SourceTextureRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Texture Replacement", meta = (PropertyPath = "CameraSettings.RenderSettings.Replace.SourceTexture"))`
- L208 _private member_ `FDisplayClusterEditorPropertyReference ShouldUseTextureRegionRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Texture Replacement", meta = (PropertyPath = "CameraSettings.RenderSettings.Replace.bShouldUseTextureRegion"))`
- L211 _private member_ `FDisplayClusterEditorPropertyReference TextureRegionRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Texture Replacement", meta = (PropertyPath = "CameraSettings.RenderSettings.Replace.TextureRegion"))`
- L214 _private member_ `FDisplayClusterEditorPropertyReference MediaRef;` — `UPROPERTY(EditDefaultsOnly, Transient, Category = "Media", meta = (PropertyPath = "CameraSettings.RenderSettings.Media"))`
- L217 _private member_ `FDisplayClusterEditorPropertyReference RenderOrderRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Configuration, meta = (PropertyPath = "CameraSettings.RenderSettings.RenderOrder"))`
- L220 _private member_ `FDisplayClusterEditorPropertyReference CustomFrameSizeRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Configuration, meta = (PropertyPath = "CameraSettings.RenderSettings.CustomFrameSize"))`
- L223 _private member_ `FDisplayClusterEditorPropertyReference RenderTargetRatioRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Configuration, meta = (PropertyPath = "CameraSettings.RenderSettings.AdvancedRenderSettings.RenderTargetRatio"))`
- L226 _private member_ `FDisplayClusterEditorPropertyReference GPUIndexRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Configuration, meta = (PropertyPath = "CameraSettings.RenderSettings.AdvancedRenderSettings.GPUIndex"))`
- L229 _private member_ `FDisplayClusterEditorPropertyReference StereoGPUIndexRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Configuration, meta = (PropertyPath = "CameraSettings.RenderSettings.AdvancedRenderSettings.StereoGPUIndex"))`
- L232 _private member_ `FDisplayClusterEditorPropertyReference StereoModeRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Configuration, meta = (PropertyPath = "CameraSettings.RenderSettings.AdvancedRenderSettings.StereoMode"))`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterLabelComponent.h` (Public)


#### class `UDisplayClusterLabelComponent`  
`class UDisplayClusterLabelComponent : public USceneComponent`  
_L25-97_
- reflection: `UCLASS(transient, meta=(BlueprintSpawnableComponent, DisplayClusterMultiUserInclude))`
- inherits: `USceneComponent`
- desc: A label component specific to nDisplay. Displays a widget with a consistent scale facing the root actor view point. Visible only in scene capture when in the editor or in 3d space on the wall. The component needs to be transient so its settings aren't saved, but should still transact over multi-user.
- L31 _public prototype_ `UDisplayClusterLabelComponent();`
- L34 _public prototype_ `void SetLabelConfiguration(const FDisplayClusterLabelConfiguration& InConfiguration);` — Set the configuration for this label updating multiple properties at once
- L37 _public prototype_ `void SetRootActor(ADisplayClusterRootActor* InActor);` — Set the root actor this label should use when determining transform
- L40 _public prototype_ `void SetWidgetScale(float NewValue);` — Set the widget scale
- L43 _public prototype_ `float GetWidgetScale() const;` — Return the widget scale
- L46 _public prototype_ `void SetLabelFlags(EDisplayClusterLabelFlags InFlags);` — Updates flags for this label
- L49 _public prototype_ `void ClearLabelFlags(EDisplayClusterLabelFlags InFlags);` — Clears all label flags
- L52 _public function_ `EDisplayClusterLabelFlags GetLabelFlags() const` — Retrieve label flags
- L55 _public prototype_ `bool HasAnyLabelFlags(EDisplayClusterLabelFlags InFlags) const;` — Checks for existence of a flag on this label
- L57 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L60 _public prototype_ `virtual void OnRegister() override;`
- L63 _public prototype_ `UWidgetComponent* GetWidgetComponent() const;` — Returns the widget component
- L67 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L72 _protected prototype_ `void UpdateWidgetComponent();` — Updates the widget component text and transform
- L75 _protected prototype_ `void CheckForVisibilityChange();` — Verify the widget visibility matches this component's visibility
- L80 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActor;` — `UPROPERTY()` — The root actor this label needs to know about
- L84 _private member_ `TObjectPtr<UDisplayClusterWidgetComponent> WidgetComponent;` — `UPROPERTY(VisibleAnywhere, Category=LabelText)` — The widget component to display for this label
- L88 _private member_ `TSoftClassPtr<UDisplayClusterLabelWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, Category=LabelText)` — The widget class to apply to the widget component
- L92 _private member_ `float WidgetScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Label, meta = (AllowPrivateAccess))` — A uniform scale to apply to the text which will keep consistency across distance from the label to the root actor view
- L96 _private member_ `EDisplayClusterLabelFlags LabelFlags;` — `UPROPERTY()` — Current flags set for this label component

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterLabelConfiguration.h` (Public)


#### enum `EDisplayClusterLabelFlags`  
`enum class EDisplayClusterLabelFlags : uint8`  
_L13-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `None = 0` — No label flags
- L18 _public enumerator_ `DisplayInGame = 1 << 0` — Label allowed to be displayed in -game
- L20 _public enumerator_ `DisplayInEditor = 1 << 1` — Label allowed to be displayed in editor

#### struct `FDisplayClusterLabelConfiguration`  
`struct FDisplayClusterLabelConfiguration`  
_L25-44_
- desc: Generic args a label can recognize
- L28 _public member_ `TObjectPtr<ADisplayClusterRootActor> RootActor;` — The root actor
- L33 _public member_ `float Scale = 1.f;` — The scale to apply to the label
- L38 _public member_ `bool bVisible = false;` — Should the label be visible
- L43 _public member_ `EDisplayClusterLabelFlags LabelFlags;` — Flags for the label. Can be used to fine-tune visibility settings

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterLightCardStageActorComponent.h` (Public)


#### class `UDisplayClusterLightCardStageActorComponent`  
`class UDisplayClusterLightCardStageActorComponent final : public UDisplayClusterStageActorComponent`  
_L13-16_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (DisplayCluster), meta = (DisplayName = "Light Card Stage Actor"), HideCategories=(Physics, Collision, Lighting, Navigation, Cooking, LOD, MaterialParameters, HLOD, RayTracing, TextureStreaming, Mobile))`
- inherits: `UDisplayClusterStageActorComponent`
- desc: Stage Actor Component to be placed in light card actors

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterOriginComponent.h` (Public)


#### class `UDisplayClusterOriginComponent`  
`class UDisplayClusterOriginComponent : public USceneComponent , public IDisplayClusterComponent`  
_L19-74_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent, DisplayName="NDisplay Origin"))`
- inherits: `USceneComponent,IDisplayClusterComponent`
- desc: nDisplay origin component (mostly for in-Editor visualization)
- L26 _public prototype_ `UDisplayClusterOriginComponent(const FObjectInitializer& ObjectInitializer);`
- L31 _public prototype_ `virtual void SetVisualizationScale(float Scale) override;`
- L32 _public prototype_ `virtual void SetVisualizationEnabled(bool bEnabled) override;`
- L37 _public prototype_ `virtual void OnRegister() override;`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L49 _protected prototype_ `virtual void RefreshVisualRepresentation();` — Refreshes the visual components to match the component state
- L56 _protected member_ `uint8 bEnableGizmo : 1;` — `UPROPERTY(EditAnywhere, Category = "Gizmo")` — Gizmo visibility
- L60 _protected member_ `FVector BaseGizmoScale;` — `UPROPERTY(EditAnywhere, Category = "Gizmo")` — Base gizmo scale
- L64 _protected member_ `float GizmoScaleMultiplier;` — `UPROPERTY(EditAnywhere, Category = "Gizmo", meta = (UIMin = "0", UIMax = "2.0", ClampMin = "0.01", ClampMax = "10.0"))` — Gizmo scale multiplier
- L68 _protected member_ `TObjectPtr<UStaticMesh> ProxyMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gizmo")` — Proxy mesh to render
- L72 _protected member_ `TObjectPtr<UStaticMeshComponent> ProxyMeshComponent;` — `UPROPERTY(Transient)` — Proxy mesh component

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterPreviewShareComponent.h` (Public)


#### enum `EDisplayClusterPreviewShareMode`  
`enum class EDisplayClusterPreviewShareMode`  
_L26-39_
- reflection: `UENUM()`
- desc: Available sharing modes
- L29 _public enumerator_ `None` — Preview share disabled.
- L32 _public enumerator_ `PullActor` — Pull from Source nDisplay Actor (if set)
- L35 _public enumerator_ `Send` — Sends the viewport textures for sharing
- L38 _public enumerator_ `Receive` — Receives textures to replace the viewport textures with

#### enum `EDisplayClusterPreviewShareIcvfxSync`  
`enum class EDisplayClusterPreviewShareIcvfxSync`  
_L43-53_
- reflection: `UENUM()`
- desc: Available Icvfx camera sync types
- L46 _public enumerator_ `None` — Icvfx cameras will not be synced
- L49 _public enumerator_ `PullActor` — Pull from Source nDisplay Actor
- L52 _public enumerator_ `PushActor` — Pushes to source display actor

#### class `UDisplayClusterPreviewShareComponent`  
`class UDisplayClusterPreviewShareComponent : public UActorComponent`  
_L68-220_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent), HideCategories = (Activation, Collision, Cooking))`
- inherits: `UActorComponent`
- desc: nDisplay Viewport preview share component It shares using Shared Memory Media the viewport textures of the parent nDisplay Actor. It should only be added to DisplayClusterRootActor instances, and only one component per instance. The way it works is that the sender generates a unique name for each viewport and captures its texture by getting a pointer to it from the corresponding Preview Component. The receiver will read it using the corresponding media source, and use the Texture Replace functionality in the nDisplay actor viewports to have them used and displayed.
- L76 _public prototype_ `UDisplayClusterPreviewShareComponent(const FObjectInitializer& ObjectInitializer);` — Constructor
- L79 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L80 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L85 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L86 _public prototype_ `virtual void PostLoad() override;`
- L89 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L96 _public prototype_ `void SetMode(EDisplayClusterPreviewShareMode NewMode);` — `UFUNCTION(BlueprintCallable, Category = "Sharing")` — Sets the sharing mode
- L100 _public prototype_ `void SetUniqueName(const FString& NewUniqueName);` — `UFUNCTION(BlueprintCallable, Category = "Sharing")` — Sets the unique name, which should match between sender and receiver of viewport textures
- L108 _protected prototype_ `bool UpdateCustomViewportManager(const ADisplayClusterRootActor* InSrcRootActor);` — Creates or updates a custom rendering for the specified RootActor. Returns nullptr if rendering is not possible, or a reference to a custom viewport manager storing rendered resources.
- L111 _protected prototype_ `virtual void OnRegister() override;`
- L117 _public member_ `EDisplayClusterPreviewShareMode Mode = EDisplayClusterPreviewShareMode::None;` — `UPROPERTY(EditAnywhere, Setter=SetMode, BlueprintSetter=SetMode, Category=Sharing)` — Current sharing mode of this component
- L121 _public member_ `FString UniqueName;` — `UPROPERTY(EditAnywhere, Setter = SetUniqueName, BlueprintSetter = SetUniqueName, Category = Sharing, meta = (EditCondition = "Mode == EDisplayClusterPreviewShareMode::Send || Mode == EDisplayClusterPreviewShareMode::Receive"))` — Current unique name of this component, which should match between sender and receiver of viewport textures
- L125 _public member_ `TSoftObjectPtr<ADisplayClusterRootActor> SourceNDisplayActor;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "Source nDisplay Actor"), Category = Sharing, meta = (EditCondition = "Mode == EDisplayClusterPreviewShareMode::PullActor"))` — The source nDisplay actor to pull the preview from
- L129 _public member_ `EDisplayClusterPreviewShareIcvfxSync IcvfxCamerasSyncType = EDisplayClusterPreviewShareIcvfxSync::PullActor;` — `UPROPERTY(EditAnywhere, Category = Sharing, meta = (EditCondition = "Mode == EDisplayClusterPreviewShareMode::PullActor"))` — Type of Icvfx camera sync to be performed between the Source nDisplay actor and the owner of this component
- L134 _private member_ `TSharedPtr<IDisplayClusterViewportManager, ESPMode::ThreadSafe> CustomViewportManager;` — DC ViewportManager instance for this component Used to perform rendering with custom settings from an external DCRA
- L137 _private prototype_ `void RestoreDefaultPreviewSettings();` — Disabling all special preview renderers and reverting to the default view.
- L140 _private prototype_ `void CloseAllMedia();` — Closes all media related objects (i.e. media captures and media players)
- L143 _private prototype_ `bool AllowedToShare() const;` — True if this component is valid to be actively used for sharing. E.g. CDOs are not considered active.
- L146 _private prototype_ `void ModeChanged();` — Called when the sharing mode was changed, so that it can update its internal state accordingly
- L149 _private prototype_ `FString GenerateViewportKey(const FString& ActorName, const FString& UniqueViewportName) const;` — Generates a string id for the viewport, used as a key to store data about it
- L152 _private prototype_ `FString GenerateMediaUniqueName(const FString& NodeName, const FString& ViewportName) const;` — Generates a Unique Name for the media being shared
- L155 _private prototype_ `void TickSend();` — Logic that should run every tick when in Send mode
- L158 _private prototype_ `void TickReceive();` — Logic that should run every tick when in Receive mode
- L164 _private prototype_ `void TickPullActor(const bool bUseSourceActorSettings);` — Logic that should run every tick when in Pull Actor mode @param bUseSourceActorSettings - Get preview settings from Source nDisplay Actor
- L167 _private prototype_ `void SyncIcvxCamerasFromSourceActor(const ADisplayClusterRootActor* SrcRootActor, const ADisplayClusterRootActor* DstRootActor);` — Syncs the Icvfx cameras from the given source nDisplay actor to the given destination nDisplay actor
- L170 _private prototype_ `void RestoreRootActorOriginalSettings();` — Restores settings in the nDisplay actor that were altered by this component to achieve its intended purpose
- L173 _private prototype_ `void SetTickEnable(const bool bEnable);` — Enables/Disables component ticking
- L177 _private prototype_ `void HandleMapChanged_Editor(UWorld* InWorld, EMapChangeType InMapChangeType);` — Called when the editor map is changed. Used to remove unwanted references to external maps.
- L182 _private function_ `void UnsubscribeFromAllPreviews()` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Unsubcribe from preview of all root actors
- L186 _private function_ `void SubscribeToPreview(ADisplayClusterRootActor* RootActor)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Subscribe for preview of given root actor
- L190 _private function_ `void UnsubscribeFromPreview(ADisplayClusterRootActor* RootActor)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Unsubscribe from preview of given root actor
- L195 _private member_ `TMap<FString, TObjectPtr<UMediaOutput>> MediaOutputs;` — `UPROPERTY(Transient)` — Media Outputs associated with the given viewport unique names
- L199 _private member_ `TMap<FString, TObjectPtr<UMediaCapture>> MediaCaptures;` — `UPROPERTY(Transient)` — Media Captures associated with the given viewport unique names
- L203 _private member_ `TMap<FString, TObjectPtr<UMediaSource>> MediaSources;` — `UPROPERTY(Transient)` — Media Sources associated with the given viewport unique names
- L207 _private member_ `TMap<FString, TObjectPtr<UMediaPlayer>> MediaPlayers;` — `UPROPERTY(Transient)` — Media Players associated with the given viewport unique names
- L211 _private member_ `TMap<FString, TObjectPtr<UMediaTexture>> MediaTextures;` — `UPROPERTY(Transient)` — Media Textures associated with the given viewport unique names
- L215 _private member_ `TMap<FString, TObjectPtr<UTexture>> OriginalSourceTextures;` — `UPROPERTY(Transient)` — Cache of original Texture Replace Source Textures associated with the given viewport unique names. Used when restoring the original state
- L219 _private member_ `TMap<FString, bool> OriginalTextureReplaces;` — `UPROPERTY(Transient)` — Cache of original Texture Replace enable boolean associated with the given viewport unique names. Used when restoring the original state

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterSceneComponentSync.h` (Public)


#### class `UDisplayClusterSceneComponentSync`  
`class UDisplayClusterSceneComponentSync : public USceneComponent , public IDisplayClusterClusterSyncObject`  
_L14-77_
- reflection: `UCLASS(Abstract)`
- inherits: `USceneComponent,IDisplayClusterClusterSyncObject`
- desc: Abstract synchronization component
- L24 _public prototype_ `virtual bool IsActive() const override;`
- L26 _public function_ `virtual FString GetSyncId() const override`
- L31 _public function_ `virtual bool IsDirty() const override`
- L41 _public prototype_ `virtual void SerializeDC(FArchive& Ar) override;`
- L47 _public prototype_ `virtual void BeginPlay() override;`
- L48 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L54 _protected prototype_ `virtual FString GenerateSyncId();` — Generates sync ID of this instance
- L57 _protected function_ `virtual FTransform GetSyncTransform() const` — Lets children provide their transforms for synchronization
- L63 _protected function_ `virtual void SetSyncTransform(const FTransform& t)` — Lets children update thir transforms with new data
- L69 _protected member_ `FVector LastSyncLoc;` — Caching state
- L70 _protected member_ `FRotator LastSyncRot;`
- L71 _protected member_ `FVector LastSyncScale;`
- L76 _private member_ `FString SyncId;` — Unique synchronization ID of this instance

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterSceneComponentSyncParent.h` (Public)


#### class `UDisplayClusterSceneComponentSyncParent`  
`class UDisplayClusterSceneComponentSyncParent : public UDisplayClusterSceneComponentSync`  
_L13-35_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), Blueprintable, meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Sync Parent"))`
- inherits: `UDisplayClusterSceneComponentSync`
- desc: Synchronization component. Synchronizes parent scene component.
- L19 _public prototype_ `UDisplayClusterSceneComponentSyncParent(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual bool IsDirty() const override;`
- L26 _public prototype_ `virtual void ClearDirty() override;`
- L32 _protected prototype_ `virtual FString GenerateSyncId() override;`
- L33 _protected prototype_ `virtual FTransform GetSyncTransform() const override;`
- L34 _protected prototype_ `virtual void SetSyncTransform(const FTransform& t) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterSceneComponentSyncThis.h` (Public)


#### class `UDisplayClusterSceneComponentSyncThis`  
`class UDisplayClusterSceneComponentSyncThis : public UDisplayClusterSceneComponentSync`  
_L13-35_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), Blueprintable, meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Sync This"))`
- inherits: `UDisplayClusterSceneComponentSync`
- desc: Synchronization component. Synchronizes itself
- L19 _public prototype_ `UDisplayClusterSceneComponentSyncThis(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual bool IsDirty() const override;`
- L26 _public prototype_ `virtual void ClearDirty() override;`
- L32 _protected prototype_ `virtual FString GenerateSyncId() override;`
- L33 _protected prototype_ `virtual FTransform GetSyncTransform() const override;`
- L34 _protected prototype_ `virtual void SetSyncTransform(const FTransform& t) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterScreenComponent.h` (Public)


#### class `UDisplayClusterScreenComponent`  
`class UDisplayClusterScreenComponent : public UStaticMeshComponent`  
_L15-50_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Screen"), HideCategories=(StaticMesh, Materials, ComponentTick, Physics, Collision, Lighting, Navigation, VirtualTexture, ComponentReplication, Cooking, LOD, MaterialParameters, HLOD, RayTracing, TextureStreaming, Mobile))`
- inherits: `UStaticMeshComponent`
- desc: Simple projection policy screen component
- L21 _public prototype_ `UDisplayClusterScreenComponent(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `FVector2D GetScreenSize() const;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get screen size"), Category = "NDisplay|Components")` — Return the screen size adjusted by its transform scale.
- L30 _public prototype_ `void SetScreenSize(const FVector2D& Size);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set screen size"), Category = "NDisplay|Components")` — Set screen size (update transform scale).
- L32 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L36 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L39 _protected prototype_ `void UpdateScreenSizeFromScale();` — Updates Size vector when scale is changed explicitly
- L48 _protected member_ `FVector2D Size;` — `UPROPERTY(EditDefaultsOnly, Category = "Screen Size", meta = (DisplayName = "Size", AllowPreserveRatio))` — Adjust the size of the screen.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterStageActorComponent.h` (Public)


#### class `UDisplayClusterStageActorComponent`  
`class UDisplayClusterStageActorComponent : public UActorComponent`  
_L15-31_
- reflection: `UCLASS(Abstract, ClassGroup = (DisplayCluster), meta = (DisplayName = "Stage Actor"), HideCategories=(Physics, Collision, Lighting, Navigation, Cooking, LOD, MaterialParameters, HLOD, RayTracing, TextureStreaming, Mobile))`
- inherits: `UActorComponent`
- desc: Stage Actor Component used to determine root actor ownership
- L21 _public prototype_ `virtual void SetRootActor(ADisplayClusterRootActor* InRootActor);` — Set the Display Cluster Root Actor owner
- L24 _public prototype_ `const TSoftObjectPtr<ADisplayClusterRootActor>& GetRootActor() const;` — Return the root actor owner of the light card
- L30 _protected member_ `TSoftObjectPtr<ADisplayClusterRootActor> RootActor;` — `UPROPERTY(EditInstanceOnly, DisplayName = "nDisplay Root Actor", Category = "NDisplay Root Actor")` — Associate this content with the nDisplay configuration actor specified here. The content will only appear in the ICVFX Editor when this nDisplay configuration is selected.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterStageGeometryComponent.h` (Public)


#### struct `FDisplayClusterStageGeometryMap`  
`struct FDisplayClusterStageGeometryMap`  
_L18-31_
- reflection: `USTRUCT()`
- desc: A geometry map for the stage, which contains a generated texture of the stage geometry's depth and normal vectors
- L24 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY()` — The render target of the geometry map
- L27 _public member_ `TArray<FFloat16Color> GeometryData;` — The raw texture data of the geometry map, which stores the normal vector in the RGB components and the depth in the A component
- L30 _public member_ `FViewMatrices ViewMatrices;` — The view matrices used to render the geometry map

#### class `UDisplayClusterStageGeometryComponent`  
`class UDisplayClusterStageGeometryComponent : public UActorComponent`  
_L35-130_
- reflection: `UCLASS()`
- inherits: `UActorComponent`
- desc: A component that stores the generated geometry map of the stage actor, which is used for placing stage actors (light cards, CCWs, etc) flush to the stage's walls and ceiling
- L41 _private member_ `static const uint32 GeometryMapSize;` — The default size of the geometry map texture
- L44 _private member_ `static const float GeometryMapFOV;` — The field of view to render the geometry map with
- L47 _public prototype_ `UDisplayClusterStageGeometryComponent();`
- L50 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L55 _public function_ `bool IsGeometryMapValid() const` — `UFUNCTION(BlueprintCallable, Category = "NDisplay")` — Gets whether the stage geometry map is valid and usable
- L62 _public prototype_ `void Invalidate(bool bForceImmediateRedraw = false);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay")` — Invalidates and regenerates the cached stage geometry map @param bForceImmediateRedraw Indicates whether the geometry map is regenerated immediately or is queued to redraw on the next tick
- L72 _public prototype_ `bool GetStageDistanceAndNormal(const FVector& InDirection, float& OutDistance, FVector& OutNormal);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay")` — Gets the distance and normal vector (in radial space) of the stage's geometry in the specified world direction @param InDirection The direction in world coordinates to query the stage geometry map @param OutDistance The distance from the stage's default view point to the nearest stage geometry in the specified direction @param OutNormal The normal vector in radial space (with x axis pointing in the direction of the stage's default view point) of the nearest stage geometry in the specified direction @return true if the stage geometry map was successfully queried, otherwise false
- L78 _public function_ `float GetStageBoundingRadius() const` — `UFUNCTION(BlueprintGetter, Category = "NDisplay")` — Gets the bounding radius of the stage's geometry
- L85 _public prototype_ `bool MorphProceduralMesh(UProceduralMeshComponent* InProceduralMeshComponent, bool bSyncMeshLocation = false);` — Morphs the specified procedural mesh to match the stage's geometry map @param InProceduralMeshComponent - The mesh component to morph @param bSyncMeshLocation - When true, the procedural mesh's world location will be synced to the view point's world location
- L89 _private prototype_ `USceneComponent* GetCommonViewPoint() const;` — Gets the parent stage's common view point, or null if none were found
- L92 _private prototype_ `UTextureRenderTarget2D* CreateRenderTarget();` — Creates a new render target that can be used to render the stage's geometry map
- L95 _private prototype_ `void RedrawGeometryMap();` — Redraws the stage's geometry map
- L98 _private prototype_ `void UpdateStageGeometry();` — Updates the stage's current geometry with the renderer
- L101 _private prototype_ `void UpdateStageIsosphere();` — Updates any isosphere that is found on the stage to match the geometry map
- L104 _private prototype_ `void GenerateGeometryMap(bool bIsNorthMap);` — Renders the stage's geometry to the specified geometry map
- L107 _private prototype_ `void GetSceneViewInitOptions(const FVector& ViewDirection, FSceneViewInitOptions& OutViewInitOptions);` — Computes the scene view init options necessary to render the geometry map in the specified view direction
- L112 _private member_ `FDisplayClusterStageGeometryMap NorthGeometryMap;` — `UPROPERTY(Transient)` — The cached geometry map for the stage's northern hemisphere
- L116 _private member_ `FDisplayClusterStageGeometryMap SouthGeometryMap;` — `UPROPERTY(Transient)` — The cached geometry map for the stage's southern hemisphere
- L120 _private member_ `float StageBoundingRadius = 0.0f;` — `UPROPERTY(Transient)` — The cached bounding radius of the stage's geometry
- L123 _private member_ `TSharedPtr<FDisplayClusterMeshProjectionRenderer> Renderer;` — The renderer used to generate the stage's geometry map
- L126 _private member_ `bool bUpdateGeometryMap = false;` — Indicates that the geometry map should be updated on the next tick
- L129 _private member_ `bool bGeometryMapLoaded = false;` — Indicates that the resources for the geometry map have been loaded

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterStageIsosphereComponent.h` (Public)


#### class `UDisplayClusterStageIsosphereComponent`  
`class UDisplayClusterStageIsosphereComponent : public UProceduralMeshComponent`  
_L12-34_
- reflection: `UCLASS()`
- inherits: `UProceduralMeshComponent`
- desc: A procedural mesh component generated by morphing an isosphere to match the stage's geometry map, providing a 3D version of the map that can be ray traced against
- L17 _public prototype_ `UDisplayClusterStageIsosphereComponent(const FObjectInitializer& ObjectInitializer);`
- L19 _public prototype_ `virtual void OnComponentCreated() override;`
- L24 _public prototype_ `void ResetIsosphere();` — Resets the vertices of the mesh component to be an isosphere
- L28 _private prototype_ `bool IsIsosphereMeshValid() const;` — Checks that the isosphere static mesh used when generating the morphed geometry is loaded and has bAllowCPUAccess set to true
- L33 _private member_ `TObjectPtr<UStaticMesh> IsosphereMesh;` — `UPROPERTY(Transient)` — A static mesh containing an isosphere that can be morphed

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterSyncTickComponent.h` (Public)


#### class `UDisplayClusterSyncTickComponent`  
`class UDisplayClusterSyncTickComponent : public UActorComponent`  
_L13-23_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Sync Tick"))`
- inherits: `UActorComponent`
- desc: Helper component to trigger nDisplay sync for Tick sync group
- L19 _public prototype_ `UDisplayClusterSyncTickComponent(const FObjectInitializer& ObjectInitializer);`
- L22 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/DisplayClusterXformComponent.h` (Public)


#### class `UDisplayClusterXformComponent`  
`class UDisplayClusterXformComponent : public USceneComponent , public IDisplayClusterComponent`  
_L19-74_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Transform"))`
- inherits: `USceneComponent,IDisplayClusterComponent`
- desc: nDisplay Transform component
- L26 _public prototype_ `UDisplayClusterXformComponent(const FObjectInitializer& ObjectInitializer);`
- L31 _public prototype_ `virtual void SetVisualizationScale(float Scale) override;`
- L32 _public prototype_ `virtual void SetVisualizationEnabled(bool bEnabled) override;`
- L37 _public prototype_ `virtual void OnRegister() override;`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L49 _protected prototype_ `virtual void RefreshVisualRepresentation();` — Refreshes the visual components to match the component state
- L56 _protected member_ `uint8 bEnableGizmo : 1;` — `UPROPERTY(EditAnywhere, Category = "Gizmo")` — Gizmo visibility
- L60 _protected member_ `FVector BaseGizmoScale;` — `UPROPERTY(EditAnywhere, Category = "Gizmo")` — Base gizmo scale
- L64 _protected member_ `float GizmoScaleMultiplier;` — `UPROPERTY(EditAnywhere, Category = "Gizmo", meta = (UIMin = "0", UIMax = "2.0", ClampMin = "0.01", ClampMax = "10.0"))` — Gizmo scale multiplier
- L68 _protected member_ `TObjectPtr<UStaticMesh> ProxyMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gizmo")` — Proxy mesh to render
- L72 _protected member_ `TObjectPtr<UStaticMeshComponent> ProxyMeshComponent;` — `UPROPERTY(Transient)` — Proxy mesh component

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Components/IDisplayClusterComponent.h` (Public)


#### class `UDisplayClusterComponent`  
`class UDisplayClusterComponent : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IDisplayClusterComponent`  
`class IDisplayClusterComponent`  
_L19-33_
- L26 _public function_ `virtual void SetVisualizationScale(float Scale)` — Changes scale of visualization data (custom viz components, gizmo, etc.)
- L30 _public function_ `virtual void SetVisualizationEnabled(bool bEnabled)` — Activates or deactivates component visualization

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Config/IDisplayClusterConfigManager.h` (Public)


#### class `IDisplayClusterConfigManager`  
`class IDisplayClusterConfigManager`  
_L15-43_
- desc: Public config manager interface
- L18 _public prototype_ `virtual ~IDisplayClusterConfigManager() = default;`
- L22 _public prototype_ `virtual UDisplayClusterConfigurationData* GetConfig() const = 0;` — Returns current config data
- L26 _public prototype_ `virtual FString GetConfigPath() const = 0;` — Returns path of the config file that is currently used
- L29 _public prototype_ `virtual FString GetLocalNodeId() const = 0;` — Returns ID of cluster node that is assigned to this application instance
- L31 _public prototype_ `virtual FString GetPrimaryNodeId() const = 0;` — Returns primary node ID
- L34 _public prototype_ `virtual const UDisplayClusterConfigurationClusterNode* GetPrimaryNode() const = 0;` — Returns primary node configuration data
- L36 _public prototype_ `virtual const UDisplayClusterConfigurationClusterNode* GetLocalNode() const = 0;` — Returns configuration data for cluster node that is assigned to this application instance
- L38 _public prototype_ `virtual const UDisplayClusterConfigurationViewport* GetLocalViewport(const FString& ViewportId) const = 0;` — Returns configuration data for a specified local viewport
- L40 _public prototype_ `virtual bool GetLocalPostprocess(const FString& PostprocessId, FDisplayClusterConfigurationPostprocess& OutPostprocess) const = 0;` — Returns configuration data for a specified local postprocess operation
- L42 _public prototype_ `virtual bool GetLocalProjection(const FString& ViewportId, FDisplayClusterConfigurationProjection& OutProjection) const = 0;` — Returns configuration data for local projection policy

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterChromakeyCardActor.h` (Public)


#### class `ADisplayClusterChromakeyCardActor`  
`class ADisplayClusterChromakeyCardActor : public ADisplayClusterLightCardActor`  
_L12-52_
- reflection: `UCLASS(Blueprintable, NotPlaceable, DisplayName = "Chromakey Card", HideCategories = (Tick, Physics, Collision, Networking, Replication, Cooking, Input, Actor, HLOD))`
- inherits: `ADisplayClusterLightCardActor`
- L16 _public prototype_ `ADisplayClusterChromakeyCardActor(const FObjectInitializer& ObjectInitializer);`
- L19 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L23 _public prototype_ `virtual void PostEditUndo() override;`
- L28 _public prototype_ `virtual void AddToRootActor(ADisplayClusterRootActor* InRootActor) override;`
- L29 _public prototype_ `virtual void RemoveFromRootActor() override;`
- L39 _public prototype_ `bool IsReferencedByICVFXCamera(const UDisplayClusterICVFXCameraComponent* InCamera) const;` — Checks if the given ICVFX camera has chroma key settings supporting this actor. @param InCamera The ICVFX camera component to compare against. @return true if the camera component references this actor.
- L41 _protected prototype_ `void UpdateChromakeySettings();`
- L46 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Called when any UObject has its property changed.
- L50 _private member_ `FDelegateHandle PropertyChangedHandle;` — Handle for UObject property change.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterEnums.h` (Public)


#### enum `EDisplayClusterOperationMode`  
`enum class EDisplayClusterOperationMode : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- desc: Display cluster operation mode
- L17 _public enumerator_ `Cluster = 0`
- L18 _public enumerator_ `Editor`
- L19 _public enumerator_ `Disabled`

#### enum `EDisplayClusterNodeRole`  
`enum class EDisplayClusterNodeRole : uint8`  
_L26-32_
- reflection: `UENUM(BlueprintType)`
- desc: Display cluster node role
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `Primary`
- L30 _public enumerator_ `Secondary`
- L31 _public enumerator_ `Backup`

#### enum `EDisplayClusterSyncGroup`  
`enum class EDisplayClusterSyncGroup : uint8`  
_L39-44_
- reflection: `UENUM(BlueprintType)`
- desc: Display cluster synchronization groups
- L41 _public enumerator_ `PreTick = 0`
- L42 _public enumerator_ `Tick`
- L43 _public enumerator_ `PostTick`

#### enum `EDisplayClusterRunningMode`  
`enum class EDisplayClusterRunningMode : uint8`  
_L49-54_
- desc: UDisplayClusterGameEngine running state.
- L51 _public enumerator_ `Startup = 0`
- L52 _public enumerator_ `Synced`
- L53 _public enumerator_ `WaitingForSync`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterGameEngine.h` (Public)


#### class `UDisplayClusterGameEngine`  
`class UDisplayClusterGameEngine : public UGameEngine`  
_L25-109_
- reflection: `UCLASS()`
- inherits: `UGameEngine`
- desc: Extended game engine
- L30 _private member_ `TObjectPtr<UObject> WorldContextObject = nullptr;`
- L33 _public prototype_ `virtual void Init(class IEngineLoop* InEngineLoop) override;`
- L34 _public prototype_ `virtual void PreExit() override;`
- L35 _public prototype_ `virtual void Tick(float DeltaSeconds, bool bIdleMode) override;`
- L36 _public prototype_ `virtual bool LoadMap(FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error) override;`
- L39 _public function_ `EDisplayClusterOperationMode GetOperationMode() const`
- L47 _public function_ `void ResetForcedIdleMode()` — Resets forced idle mode flag needed for multiplayer connections to tick the engine side to process handshake Used by DisplayClusterNetDriver when all nodes are connected
- L55 _public function_ `virtual bool IsRenderingSuspended() const override` — This override control either we want to trigger the rendering or not on the frame By modifying variable state in BrowseLoadMap when multiplayer connections are being established to prevent Redraw on the client side
- L61 _protected prototype_ `virtual void UpdateTimeAndHandleMaxTickRate() override;`
- L64 _protected prototype_ `virtual bool InitializeInternals();`
- L65 _protected prototype_ `EDisplayClusterOperationMode DetectOperationMode() const;`
- L66 _protected prototype_ `bool GetResolvedNodeId(const UDisplayClusterConfigurationData* ConfigData, FString& NodeId) const;`
- L67 _protected prototype_ `bool ValidateConfigFile(const FString& FilePath);`
- L68 _protected prototype_ `void PreExitImpl();`
- L71 _private prototype_ `bool OutOfSync() const;`
- L72 _private prototype_ `void ReceivedSync(const FString &Level, const FString &NodeId);`
- L74 _private prototype_ `void CheckGameStartBarrier();`
- L75 _private prototype_ `bool CanTick() const;`
- L77 _private prototype_ `bool BarrierAvoidanceOn() const;`
- L79 _private prototype_ `void GameSyncChange(const FDisplayClusterClusterEventJson& InEvent);`
- L83 _private prototype_ `EBrowseReturnVal::Type BrowseLoadMap(FWorldContext& WorldContext, FURL URL, FString& Error);` — Implements custom loading logic to support listening server
- L87 _private prototype_ `void PendingLevelUpdate(FWorldContext& Context, float DeltaSeconds);` — Custom logic to update PendingLevel in order to support listening server
- L90 _private prototype_ `void ModifyCVars();` — Sets up CVars
- L94 _private member_ `FDisplayClusterConfigurationDiagnostics Diagnostics;`
- L96 _private member_ `EDisplayClusterOperationMode OperationMode = EDisplayClusterOperationMode::Disabled;`
- L97 _private member_ `EDisplayClusterRunningMode RunningMode = EDisplayClusterRunningMode::Startup;`
- L99 _private member_ `TMap<FString, TSet<FString>> SyncMap;`
- L105 _private member_ `bool bForcedTickIdleMode = false;` — Flag used to force nodes to skip frame rendering This is needed when multiplayer connections being established in the cluster, system have to wait for all nodes to be connected before proceeding with rendering otherwise cluster will deadlock itself between GT/RT barriers Enforced automatically into true on BrowseLoadMap for multiplayer connections
- L108 _private member_ `bool bIsRenderingSuspended = false;` — Flag used to suspend rendering and avoid Redraw method that leads to barrier lock among multiplayer client nodes, used in MP mode only

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(EBrowseReturnVal::Type, FOnBrowseLoadMap, FWorldContext& WorldContext, FURL URL, FString& Error);`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(EBrowseReturnVal::Type, FOnBrowseLoadMap, FWorldContext& WorldContext, FURL URL, FString& Error);`
- L19 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPengineLevelUpdate, FWorldContext& Context, float DeltaSeconds);`
- L19 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnPengineLevelUpdate, FWorldContext& Context, float DeltaSeconds);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterLightCardActor.h` (Public)


#### enum `EDisplayClusterLightCardMask`  
`enum class EDisplayClusterLightCardMask : uint8`  
_L26-33_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Circle`
- L29 _public enumerator_ `Square`
- L30 _public enumerator_ `UseTextureAlpha`
- L31 _public enumerator_ `Polygon`
- L32 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FLightCardAlphaGradientSettings`  
`struct FLightCardAlphaGradientSettings`  
_L36-55_
- reflection: `USTRUCT(Blueprintable)`
- L42 _public member_ `bool bEnableAlphaGradient = false;` — `UPROPERTY(EditAnywhere, Interp, BlueprintReadWrite, Category = "Appearance")` — Enables/disables alpha gradient effect
- L46 _public member_ `float StartingAlpha = 0;` — `UPROPERTY(EditAnywhere, Interp, BlueprintReadWrite, Category = "Appearance")` — Starting alpha value in the gradient
- L50 _public member_ `float EndingAlpha = 1;` — `UPROPERTY(EditAnywhere, Interp, BlueprintReadWrite, Category = "Appearance")` — Ending alpha value in the gradient
- L54 _public member_ `float Angle = 0;` — `UPROPERTY(EditAnywhere, Interp, BlueprintReadWrite, Category = "Appearance")` — The angle (degrees) determines the gradient direction.

#### class `ADisplayClusterLightCardActor`  
`class ADisplayClusterLightCardActor : public AActor, public IDisplayClusterStageActor`  
_L58-363_
- reflection: `UCLASS(Blueprintable, DisplayName = "Light Card", HideCategories = (Tick, Physics, Collision, Networking, Replication, Cooking, Input, Actor, HLOD))`
- inherits: `AActor,IDisplayClusterStageActor`
- L64 _public member_ `static const float UVPlaneDefaultSize;` — The default size of the projection plane UV light cards are rendered to
- L67 _public member_ `static const float UVPlaneDefaultDistance;` — The default distance from the view of the projection plane UV light cards are rendered to
- L70 _public member_ `static const FName LightCardStageActorComponentName;` — The name used for the stage actor component
- L73 _public prototype_ `ADisplayClusterLightCardActor(const FObjectInitializer& ObjectInitializer);`
- L76 _public prototype_ `virtual void PostLoad() override;`
- L77 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L78 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L79 _public prototype_ `virtual void Destroyed() override;`
- L82 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L83 _public function_ `virtual bool ShouldTickIfViewportsOnly() const override`
- L84 _public prototype_ `virtual FName GetCustomIconName() const override;`
- L88 _public prototype_ `void GetLightCardMeshComponents(TArray<UMeshComponent*>& MeshComponents) const;` — Gets the light card mesh components
- L91 _public prototype_ `UStaticMesh* GetStaticMesh() const;` — Returns the current static mesh used by this light card
- L94 _public function_ `UDisplayClusterLabelComponent* GetLabelComponent() const` — Return the label component
- L97 _public prototype_ `void SetStaticMesh(UStaticMesh* InStaticMesh);` — Sets a new static mesh for the light card
- L100 _public prototype_ `void UpdateLightCardMaterialInstance();` — Updates the card's material instance parameters
- L103 _public prototype_ `void UpdatePolygonTexture();` — Updates the polygon texture from the polygon points
- L106 _public prototype_ `void UpdateLightCardVisibility();` — Updates the light card actor visibility
- L109 _public prototype_ `void UpdateUVIndicator();` — Updates the UV Indicator
- L112 _public prototype_ `void UpdateLightCardPositionToRootActor();` — Sync the position to the root actor
- L115 _public prototype_ `void MakeFlushToWall();` — Makes the light card flush to the wall
- L118 _public prototype_ `void SetIsLightCardFlag(bool bNewFlagValue);` — Configures this light card as a flag
- L121 _public function_ `bool IsLightCardFlag() const` — If this light card is considered a flag
- L124 _public prototype_ `void SetIsUVActor(bool bNewUVValue);` — Configures this light card as a UV actor
- L127 _public prototype_ `void ShowLightCardLabel(const FDisplayClusterLabelConfiguration& InLabelConfiguration);` — Configure light card labels
- L131 _public prototype_ `void ShowLightCardLabel(bool bValue, float ScaleValue, ADisplayClusterRootActor* InRootActor);` — `UE_DEPRECATED(5.3, "Use the ShowLightCardLabel function which accepts FDisplayClusterLabelConfiguration arguments.")` — Show or hide the light card label
- L134 _public prototype_ `void SetWeakRootActorOwner(ADisplayClusterRootActor* InRootActor);` — Set a weak root actor owner. This should be used on legacy light cards that don't have StageActorComponent->RootActor set
- L137 _public prototype_ `void SetRootActorOwner(ADisplayClusterRootActor* InRootActor);` — Set the root actor of the stage actor component
- L140 _public prototype_ `ADisplayClusterRootActor* GetRootActorOwner() const;` — Return the root actor owner of the light card
- L143 _public prototype_ `UDisplayClusterStageActorComponent* GetStageActorComponent() const;` — Retrieve the stage actor component
- L147 _public prototype_ `void AddToLightCardLayer(ADisplayClusterRootActor* InRootActor);` — `UE_DEPRECATED(5.2, "Layers are no longer used for light cards by default, use 'AddToRootActor' instead")` — Add this light card to a light card layer on the given root actor
- L150 _public prototype_ `virtual void AddToRootActor(ADisplayClusterRootActor* InRootActor);` — Add this light card to a root actor
- L153 _public prototype_ `virtual void RemoveFromRootActor();` — Remove this light card from the root actor
- L157 _public prototype_ `virtual void UpdateStageActorTransform() override;` — Updates the Light Card transform based on its positional properties (Lat, Long, etc.)
- L162 _public prototype_ `virtual FTransform GetStageActorTransform(bool bRemoveOrigin = false) const override;` — Gets the transform in world space of the light card component
- L165 _public prototype_ `virtual FBox GetBoxBounds(bool bLocalSpace = false) const override;` — Gets the object oriented bounding box of the light card component
- L167 _public prototype_ `virtual void SetLongitude(double InValue) override;`
- L168 _public prototype_ `virtual double GetLongitude() const override;`
- L170 _public prototype_ `virtual void SetLatitude(double InValue) override;`
- L171 _public prototype_ `virtual double GetLatitude() const override;`
- L173 _public prototype_ `virtual void SetDistanceFromCenter(double InValue) override;`
- L174 _public prototype_ `virtual double GetDistanceFromCenter() const override;`
- L176 _public prototype_ `virtual void SetSpin(double InValue) override;`
- L177 _public prototype_ `virtual double GetSpin() const override;`
- L179 _public prototype_ `virtual void SetPitch(double InValue) override;`
- L180 _public prototype_ `virtual double GetPitch() const override;`
- L182 _public prototype_ `virtual void SetYaw(double InValue) override;`
- L183 _public prototype_ `virtual double GetYaw() const override;`
- L185 _public prototype_ `virtual void SetRadialOffset(double InValue) override;`
- L186 _public prototype_ `virtual double GetRadialOffset() const override;`
- L188 _public prototype_ `virtual bool IsUVActor() const override;`
- L190 _public prototype_ `virtual void SetOrigin(const FTransform& InOrigin) override;`
- L191 _public prototype_ `virtual FTransform GetOrigin() const override;`
- L193 _public prototype_ `virtual void SetScale(const FVector2D& InScale) override;`
- L194 _public prototype_ `virtual FVector2D GetScale() const override;`
- L196 _public function_ `virtual void SetAlwaysFlushToWall(bool bInAlwaysFlushToWall) override`
- L197 _public function_ `virtual bool IsAlwaysFlushToWall() const override`
- L198 _public prototype_ `virtual void SetUVCoordinates(const FVector2D& InUVCoordinates) override;`
- L199 _public prototype_ `virtual FVector2D GetUVCoordinates() const override;`
- L201 _public prototype_ `virtual void GetPositionalProperties(FPositionalPropertyArray& OutPropertyPairs) const override;`
- L208 _public member_ `double DistanceFromCenter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))` — Radius of light card polar coordinates. Does not include the effect of RadialOffset
- L212 _public member_ `double Longitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (UIMin = 0, ClampMin = 0, UIMax = 360, ClampMax = 360, EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))` — Related to the Azimuth of light card polar coordinates
- L216 _public member_ `double Latitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (UIMin = -90, ClampMin = -90, UIMax = 90, ClampMax = 90, EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))` — Related to the Elevation of light card polar coordinates
- L220 _public member_ `FVector2D UVCoordinates = FVector2D(0.5, 0.5);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (DisplayName = "UV Coodinates", EditCondition = "bIsUVLightCard", HideEditConditionToggle, EditConditionHides))` — The UV coordinates of the light card, if it is in UV space
- L224 _public member_ `double Spin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (UIMin = -360, ClampMin = -360, UIMax = 360, ClampMax = 360))` — Roll rotation of light card around its plane axis
- L227 _public member_ `double Pitch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (UIMin = -360, ClampMin = -360, UIMax = 360, ClampMax = 360, EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))`
- L230 _public member_ `double Yaw;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (UIMin = -360, ClampMin = -360, UIMax = 360, ClampMax = 360, EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))`
- L233 _public member_ `FVector2D Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation")`
- L237 _public member_ `double RadialOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))` — Used by the flush constraint to offset the location of the light card form the wall
- L241 _public member_ `bool bAlwaysFlushToWall;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Orientation", meta = (EditCondition = "!bIsUVLightCard", HideEditConditionToggle, EditConditionHides))` — Indicates whether the light card is always made to be flush to a stage wall or not
- L245 _public member_ `EDisplayClusterConfigurationICVFX_PerLightcardRenderMode PerLightcardRenderMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (DisplayName = "Blending Mode"))` — Specify how to render this Light Card Actor in relation to the inner frustum.
- L248 _public member_ `EDisplayClusterLightCardMask Mask;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance")`
- L251 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance")`
- L255 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance")` — Light card color, before any modifier is applied
- L258 _public member_ `float Temperature;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (UIMin = 0, ClampMin = 0, UIMax = 10000, ClampMax = 10000))`
- L261 _public member_ `float Tint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (UIMin = -1, ClampMin = -1, UIMax = 1, ClampMax = 1))`
- L265 _public member_ `float Exposure;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (UIMin = -100, ClampMin = -100, UIMax = 100, ClampMax = 100))` — 2^Exposure color value multiplier
- L269 _public member_ `float Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (UIMin = 0, ClampMin = 0))` — Linear color value multiplier
- L273 _public member_ `float Opacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — Linear alpha multiplier
- L277 _public member_ `float Feathering;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance", meta = (UIMin = 0, ClampMin = 0))` — Feathers in the alpha from the edges
- L281 _public member_ `FLightCardAlphaGradientSettings AlphaGradient;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance")` — Settings related to an alpha gradient effect
- L285 _public member_ `bool bLockToOwningRootActor = true;` — `UPROPERTY()` — A flag that controls whether the light card's location and rotation are locked to its "owning" root actor
- L289 _public member_ `bool bIsUVLightCard = false;` — `UPROPERTY(Getter = IsUVActor, Setter = SetIsUVActor)` — Indicates if the light card exists in 3D space or in UV space
- L293 _public member_ `TArray<FVector2D> Polygon;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Appearance")` — Polygon points when using this type of mask
- L297 _public member_ `TObjectPtr<UTexture> PolygonMask = nullptr;` — `UPROPERTY(Transient)` — Used to flag this light card as a proxy of a "real" light card. Used by the LightCard Editor
- L299 _public function_ `static FName GetExtenderNameToComponentMapMemberName()`
- L306 _protected prototype_ `void CreateComponentsForExtenders();` — Creates components for IDisplayClusterLightCardActorExtender
- L309 _protected prototype_ `void CleanUpComponentsForExtenders();` — Removes components that were added by IDisplayClusterLightCardActorExtender
- L312 _protected prototype_ `void RemoveFromRootActorList(ADisplayClusterRootActor* RootActor);` — Removes this actor from a root actor's ShowOnlyList.Actors, if possible.
- L316 _protected prototype_ `void OnLevelActorDeleted(AActor* DeletedActor);` — Called when a level actor is deleted
- L321 _protected member_ `TObjectPtr<USceneComponent> DefaultSceneRootComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")`
- L324 _protected member_ `TObjectPtr<USpringArmComponent> MainSpringArmComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")`
- L327 _protected member_ `TObjectPtr<USceneComponent> LightCardTransformerComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")`
- L330 _protected member_ `TObjectPtr<UStaticMeshComponent> LightCardComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")`
- L334 _protected member_ `TMap<FName, TObjectPtr<UActorComponent>> ExtenderNameToComponentMap;` — `UPROPERTY(VisibleAnywhere, Category = "Default")` — Components added by the IDisplayLightCardActorExtender
- L337 _protected member_ `TObjectPtr<UDisplayClusterLabelComponent> LabelComponent;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Default")`
- L341 _protected member_ `TObjectPtr<UDisplayClusterStageActorComponent> StageActorComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Default")` — Manages stage actor properties
- L345 _protected member_ `TObjectPtr<UStaticMeshComponent> UVIndicatorComponent;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Default")`
- L350 _protected member_ `bool bIsLightCardFlag = false;` — `UPROPERTY(Getter = IsLightCardFlag, Setter = SetIsLightCardFlag, meta = (AllowPrivateAccess = "true"))` — Indicates this light card should be considered a flag
- L354 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> WeakRootActorOwner;` — Set by DCRA during tick. Meant for legacy light cards that don't have a SoftObjectPtr set
- L357 _private member_ `FVector LastOrbitLocation = FVector::ZeroVector;` — Stores the location relative to the root actor's origin that stage actors like light cards can orbit around
- L361 _private member_ `bool bHadRootActorMismatch = false;` — Set if there was conflicting root actor ownership

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterPlayerInput.h` (Public)


#### class `UDisplayClusterPlayerInput`  
`class UDisplayClusterPlayerInput : public UEnhancedPlayerInput`  
_L17-49_
- reflection: `UCLASS(Within=PlayerController, config=Input, transient)`
- inherits: `UEnhancedPlayerInput`
- desc: An object within PlayerController that processes player input. This one is nDisplay specific implementation. It's responsible for replication of UE native input within a cluster to support simulation determinism. Various input sync policies might be implemented here.
- L23 _public prototype_ `UDisplayClusterPlayerInput();`
- L28 _public prototype_ `virtual void ProcessInputStack(const TArray<UInputComponent*>& InputComponentStack, const float DeltaTime, const bool bGamePaused) override;` — Process the frame's input events given the current input component stack.
- L33 _protected prototype_ `virtual void ProcessPolicy_ReplicatePrimary(const TArray<UInputComponent*>& InputComponentStack, const float DeltaTime, const bool bGamePaused);` — Performs sync logic where all input data from the primary node is replicated to all other nodes
- L38 _protected prototype_ `bool SerializeKeyStateMap(TMap<FString, TArray<uint8>>& OutKeyStateMap);` — Auxiliary function that serializes whole input data into a byte stream
- L41 _protected prototype_ `bool DeserializeKeyStateMap(const TMap<FString, TArray<uint8>>& InKeyStateMap);` — Aux function that deserializes whole input data from a map
- L48 _private member_ `bool bReplicatePrimary;` — Currently we have this bool only wich provides 2 cases: sync or not sync. It covers all functionality currently available . However, this might be refactored one day in order to support multiple input sync policies including custom ones.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterRootActor.h` (Public)


#### class `ADisplayClusterRootActor`  
`class ADisplayClusterRootActor : public AActor`  
_L52-811_
- reflection: `UCLASS(notplaceable, HideCategories=(Replication, Collision, Input, Actor, HLOD, Cooking, Physics, Activation, AssetUserData, ActorTick, Advanced, DataLayers, Events), meta = (DisplayName = "nDisplay Root Actor"))`
- inherits: `AActor`
- desc: VR root. This contains nDisplay VR hierarchy in the game.
- L60 _public prototype_ `ADisplayClusterRootActor(const FObjectInitializer& ObjectInitializer);`
- L61 _public prototype_ `~ADisplayClusterRootActor();`
- L69 _public prototype_ `void InitializeFromConfig(UDisplayClusterConfigurationData* ConfigData);` — Initialializes the instance with specified config data @param ConfigData - Configuration data
- L76 _public prototype_ `void OverrideFromConfig(UDisplayClusterConfigurationData* ConfigData);` — Cherry picking settings from a specified config data @param ConfigData - Configuration data
- L85 _public prototype_ `void UpdateConfigDataInstance(UDisplayClusterConfigurationData* ConfigDataTemplate, bool bForceRecreate = false);` — Update or create the config data object. The config sub object is only instantiated once. Subsequent calls will only update ConfigDataName unless bForceRecreate is true. @param ConfigDataTemplate The config template to use for this actors' config data object. @param bForceRecreate Deep copies properties from the config data template to this actors' config data object.
- L88 _public prototype_ `bool IsPrimaryRootActor() const;` — Returns true if this RootActor is used as the primary RootActor in the DC GameManager.
- L91 _public prototype_ `bool IsPrimaryRootActorForPIE() const;` — Returns true if this RootActor is primary and should be displayed in PIE mode.
- L94 _public prototype_ `bool IsRunningPIE() const;` — Returns true if this RootActor is running in PIE mode.
- L97 _public prototype_ `bool IsRunningGameOrPIE() const;` — Returns true if this RootActor is running in game or in PIE mode.
- L100 _public prototype_ `bool IsRunningDisplayCluster() const;` — Returns true if this RootActor is running in DC mode.
- L103 _public prototype_ `void OverrideRootActorProperties(const FDisplayClusterRootActorPropertyOverrides& InPropertyOverrides);` — Override properties of this root actor.
- L105 _public prototype_ `UDisplayClusterConfigurationData* GetDefaultConfigDataFromAsset() const;`
- L106 _public prototype_ `UDisplayClusterConfigurationData* GetConfigData() const;`
- L109 _public prototype_ `bool GetHiddenInGamePrimitives(TSet<FPrimitiveComponentId>& OutPrimitives);` — Return hidden in game privitives set
- L120 _public prototype_ `bool FindPrimitivesByName(const TArray<FString>& InNames, TSet<FPrimitiveComponentId>& OutPrimitives, bool bForceHide = false);` — Collect UActorComponent primitives by names. Note: Components must have bHiddenInGame set to true. @param InNames       - The names of the primitives to be searched for. @param OutPrimitives - (out) An array with the primitives that were found. @param bForceHide    - (opt) if true, collects components with any value of the bHiddenInGame property. @return true if any primitives were found.
- L122 _public prototype_ `bool IsBlueprint() const;`
- L124 _public function_ `UDisplayClusterSyncTickComponent* GetSyncTickComponent() const`
- L129 _public prototype_ `const FDisplayClusterConfigurationICVFX_StageSettings& GetStageSettings() const;`
- L130 _public prototype_ `const FDisplayClusterConfigurationRenderFrame& GetRenderFrameSettings() const;`
- L133 _public prototype_ `void TickPreviewRenderer();` — The Tick() function that calls the preview renderer for this root actor.
- L139 _public function_ `EDisplayClusterRenderFrameMode GetRenderMode() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Returns the current rendering mode of this DCRA (not a value from configuration). This value can be overridden from DCRenderDevice or other rendering subsystems (e.g. Preview).
- L146 _public function_ `EDisplayClusterRenderFrameMode GetPreviewRenderMode() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Returns the preview rendering mode of this DCRA.
- L155 _protected prototype_ `virtual void BeginPlay() override;`
- L156 _protected prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L157 _protected prototype_ `virtual void PostLoad() override;`
- L158 _protected prototype_ `virtual void PostActorCreated() override;`
- L159 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L160 _protected prototype_ `virtual void BeginDestroy() override;`
- L161 _protected prototype_ `virtual void Destroyed() override;`
- L163 _protected prototype_ `virtual void RerunConstructionScripts() override;`
- L167 _protected prototype_ `void InitializeRootActor();` — Initializes the actor on spawn and load
- L170 _protected prototype_ `bool BuildHierarchy();` — Creates all hierarchy objects declared in a config file
- L173 _protected prototype_ `void SetLightCardOwnership();` — Determine which light card actors are owned by this root actor
- L177 _public prototype_ `bool GetFlushPositionAndNormal(const FVector& WorldPosition, FVector& OutPosition, FVector& OutNormal);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|DCRA")`
- L180 _public prototype_ `bool MakeStageActorFlushToWall(const TScriptInterface<IDisplayClusterStageActor>& StageActor, double DesiredOffsetFromFlush = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|DCRA")`
- L190 _public prototype_ `bool GetDistanceToStageGeometry(const FVector& WorldPosition, const FVector& WorldDirection, float& OutDistance) const;` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Stage")` — Gets the distance from a world position to the stage's geometry along the specified direction, if there is an intersection @param WorldPosition - The world position to measure the distance from @param WorldDirection - The direction to find the distance to the geometry along @param OutDistance - The distance to the stage geometry from the specified point @return True if an intersection point from WorldPosition along WorldDirection was found, false if not
- L193 _public function_ `UDisplayClusterStageGeometryComponent* GetStageGeometryComponent() const` — `UFUNCTION(BlueprintGetter)`
- L196 _public prototype_ `UDisplayClusterCameraComponent* GetDefaultCamera() const;` — `UFUNCTION(BlueprintGetter)`
- L200 _public prototype_ `UDisplayClusterDisplayDeviceBaseComponent* GetDefaultDisplayDevice() const;` — `UFUNCTION(BlueprintGetter)` — Retrieve the default display device, creating it if it doesn't exist
- L203 _public prototype_ `ULineBatchComponent* GetLineBatchComponent() const;` — Retrieve the line batch component.
- L210 _public prototype_ `USceneComponent* GetCommonViewPoint() const;` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|DCRA")` — Get the view point most commonly used by viewports in this cluster. If no viewports override the camera, this returns the default camera, or if there isn't one, the actor's root component.
- L213 _public prototype_ `bool SetReplaceTextureFlagForAllViewports(bool bReplace);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Render")`
- L216 _public prototype_ `bool SetFreezeOuterViewports(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Render")`
- L219 _public function_ `template <typename TComp> TComp* GetComponentByName(const FString& ComponentName) const`
- L244 _public prototype_ `void UpdateProceduralMeshComponentData(const UProceduralMeshComponent* InProceduralMeshComponent = nullptr);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Update ProceduralMeshComponent data"), Category = "NDisplay|Components")` — Update the geometry of the procedural mesh component(s) referenced inside nDisplay @param InProceduralMeshComponent - (optional) Mark the specified procedural mesh component, not all
- L253 _public prototype_ `void SetPreviewEnablePostProcess(const bool bNewPreviewEnablePostProcess);` — `UFUNCTION(BlueprintSetter)` — Blueprint setter for the PreviewEnablePostProcess property. Makes sure preview pipeline is updated properly. @param bNewPreviewEnablePostProcess - Desired new property value.
- L261 _public prototype_ `void SetPreviewEnableHoldoutComposite(const bool bNewPreviewEnableHoldoutComposite);` — `UFUNCTION(BlueprintSetter)` — Blueprint setter for the PreviewEnableHoldoutComposite property. Makes sure preview pipeline is updated properly. @param bNewbPreviewEnableHoldoutComposite - Desired new property value.
- L265 _public prototype_ `IDisplayClusterViewportManager* GetViewportManager() const;` — Get ViewportManager API.
- L268 _public prototype_ `IDisplayClusterViewportManager* GetOrCreateViewportManager();` — Get or Create ViewportManager API.
- L271 _public prototype_ `void RemoveViewportManager();` — Release the viewport manager instance, if it exists.
- L274 _public prototype_ `IDisplayClusterViewportConfiguration* GetViewportConfiguration() const;` — Get ViewportConfiguration API.
- L276 _public function_ `static FName GetCurrentConfigDataMemberName()`
- L283 _private prototype_ `FDisplayClusterViewportManager* GetViewportManagerImpl() const;` — Get ViewportManager API.
- L286 _private prototype_ `void ResetEntireClusterPreviewRendering();` — Reset preview rendering.
- L290 _private member_ `TSharedPtr<FDisplayClusterViewportManager, ESPMode::ThreadSafe> ViewportManagerPtr;` — DC ViewportManager instance for this DCRA
- L299 _private member_ `FDisplayClusterEditorPropertyReference OuterViewportUpscalerSettingsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Viewports, meta = (PropertyPath = "CurrentConfigData.StageSettings.OuterViewportUpscalerSettings", DisplayName = "Default Upscaler Settings"))`
- L302 _private member_ `FDisplayClusterEditorPropertyReference ViewportUpscalerSettingsRef;` — `UPROPERTY(EditInstanceOnly, Transient, Category = Viewports, meta = (DisplayName = "Per-Viewport Upscaling Setting Overrides", PropertyPath = "CurrentConfigData.Cluster.Nodes.Viewports.RenderSettings.UpscalerSettings", ToolTip = "Adjust upscaler settings for an individual viewport."))`
- L305 _private member_ `FDisplayClusterEditorPropertyReference ViewportScreenPercentageMultiplierRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Viewports, meta = (PropertyPath = "CurrentConfigData.RenderFrameSettings.ClusterICVFXOuterViewportBufferRatioMult"))`
- L308 _private member_ `FDisplayClusterEditorPropertyReference ViewportScreenPercentageRef;` — `UPROPERTY(EditInstanceOnly, Transient, Category = Viewports, meta = (DisplayName = "Viewport Screen Percentage", PropertyPath = "CurrentConfigData.Cluster.Nodes.Viewports.RenderSettings.BufferRatio", ToolTip = "Adjust resolution scaling for an individual viewport. Viewport Screen Percentage Multiplier is applied to this value."))`
- L311 _private member_ `FDisplayClusterEditorPropertyReference ViewportOverscanRef;` — `UPROPERTY(EditInstanceOnly, Transient, Category = Viewports, meta = (DisplayName = "Viewport Overscan", PropertyPath = "CurrentConfigData.Cluster.Nodes.Viewports.RenderSettings.Overscan", ToolTip = "Render a larger frame than specified in the configuration to achieve continuity across displays when using post-processing effects."))`
- L314 _private member_ `FDisplayClusterEditorPropertyReference FreezeRenderOuterViewportsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Viewports, meta = (PropertyPath = "CurrentConfigData.StageSettings.bFreezeRenderOuterViewports"))`
- L317 _private member_ `FDisplayClusterEditorPropertyReference ClusterHideListRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Viewports, meta = (PropertyPath = "CurrentConfigData.StageSettings.HideList"))`
- L320 _private member_ `FDisplayClusterEditorPropertyReference OuterHideListRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Viewports, meta = (PropertyPath = "CurrentConfigData.StageSettings.OuterViewportHideList"))`
- L323 _private member_ `FDisplayClusterEditorPropertyReference PerOuterHideListRef;` — `UPROPERTY(EditInstanceOnly, Transient, Category = Viewports, meta = (DisplayName = "Content Hidden Per-Viewport", PropertyPath = "CurrentConfigData.Cluster.Nodes.Viewports.RenderSettings.HiddenContent", ToolTip = "Hide actors from a specific viewport."))`
- L326 _private member_ `FDisplayClusterEditorPropertyReference GlobalInnerFrustumUpscalerSettingsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "In Camera VFX", meta = (PropertyPath = "CurrentConfigData.StageSettings.GlobalInnerFrustumUpscalerSettings", DisplayName = "Default Upscaler Settings"))`
- L329 _private member_ `FDisplayClusterEditorPropertyReference EnableInnerFrustumsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "In Camera VFX", meta = (PropertyPath = "CurrentConfigData.StageSettings.bEnableInnerFrustums"))`
- L332 _private member_ `FDisplayClusterEditorPropertyReference ShowInnerFrustumOverlapsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "In Camera VFX", meta = (PropertyPath = "CurrentConfigData.StageSettings.bEnableInnerFrustumChromakeyOverlap", DisplayName = "Enable Chromakey Overlap"))`
- L335 _private member_ `FDisplayClusterEditorPropertyReference EnableInnerFrustumChromakeyOverlapRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Color Grading", meta = (PropertyPath = "CurrentConfigData.StageSettings.EnableColorGrading"))`
- L338 _private member_ `FDisplayClusterEditorPropertyReference ClusterColorGradingRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Color Grading", meta = (PropertyPath = "CurrentConfigData.StageSettings.EntireClusterColorGrading"))`
- L341 _private member_ `FDisplayClusterEditorPropertyReference PerViewportColorGradingRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Color Grading", meta = (PropertyPath = "CurrentConfigData.StageSettings.PerViewportColorGrading"))`
- L344 _private member_ `FDisplayClusterEditorPropertyReference EnableViewportOCIORef;` — `UPROPERTY(EditAnywhere, Transient, Category = OCIO, meta = (PropertyPath = "CurrentConfigData.StageSettings.ViewportOCIO.AllViewportsOCIOConfiguration.bIsEnabled", DisplayName = "Enable Viewport OCIO"))`
- L347 _private member_ `FDisplayClusterEditorPropertyReference AllViewportColorConfigurationRef;` — `UPROPERTY(EditAnywhere, Transient, Category = OCIO, meta = (PropertyPath = "CurrentConfigData.StageSettings.ViewportOCIO.AllViewportsOCIOConfiguration.ColorConfiguration", DisplayName = "All Viewports Color Configuration"))`
- L350 _private member_ `FDisplayClusterEditorPropertyReference PerViewportOCIOProfilesRef;` — `UPROPERTY(EditAnywhere, Transient, Category = OCIO, meta = (PropertyPath = "CurrentConfigData.StageSettings.ViewportOCIO.PerViewportOCIOProfiles", DisplayName = "Per-Viewport OCIO Overrides"))`
- L353 _private member_ `FDisplayClusterEditorPropertyReference AutoExposureEnabledRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Exposure", meta = (PropertyPath = "CurrentConfigData.StageSettings.AutoExposureSettings.bEnabled"))`
- L356 _private member_ `FDisplayClusterEditorPropertyReference AutoExposureMeteringSettingsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Exposure", meta = (PropertyPath = "CurrentConfigData.StageSettings.AutoExposureSettings.MeteringSettings"))`
- L359 _private member_ `FDisplayClusterEditorPropertyReference AutoExposureExcludeSettingsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Exposure", meta = (PropertyPath = "CurrentConfigData.StageSettings.AutoExposureSettings.ExcludeSettings"))`
- L362 _private member_ `FDisplayClusterEditorPropertyReference GlobalChromakeyColorRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CurrentConfigData.StageSettings.GlobalChromakey.ChromakeyColor"))`
- L365 _private member_ `FDisplayClusterEditorPropertyReference GlobalChromakeyMarkersRef;` — `UPROPERTY(EditAnywhere, Transient, Category = Chromakey, meta = (PropertyPath = "CurrentConfigData.StageSettings.GlobalChromakey.ChromakeyMarkers"))`
- L368 _private member_ `FDisplayClusterEditorPropertyReference EnableLightcardsRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Light Cards", meta = (PropertyPath = "CurrentConfigData.StageSettings.Lightcard.bEnable"))`
- L371 _private member_ `FDisplayClusterEditorPropertyReference LightCardBlendingModeRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Light Cards", meta = (PropertyPath = "CurrentConfigData.StageSettings.Lightcard.Blendingmode", EditConditionPath = "CurrentConfigData.StageSettings.Lightcard.bEnable"))`
- L374 _private member_ `FDisplayClusterEditorPropertyReference LightCardContentRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Light Cards", meta = (PropertyPath = "CurrentConfigData.StageSettings.Lightcard.ShowOnlyList", EditConditionPath = "CurrentConfigData.StageSettings.Lightcard.bEnable"))`
- L377 _private member_ `FDisplayClusterEditorPropertyReference LightcardOCIOModeRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Light Cards", meta = (PropertyPath = "CurrentConfigData.StageSettings.Lightcard.LightcardOCIO.LightcardOCIOMode", DisplayName = "Light Cards OCIO"))`
- L380 _private member_ `FDisplayClusterEditorPropertyReference LightcardAllViewportColorConfigurationRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Light Cards", meta = (PropertyPath = "CurrentConfigData.StageSettings.Lightcard.LightcardOCIO.CustomOCIO.AllViewportsOCIOConfiguration.ColorConfiguration", DisplayName = "All Viewports Color Configuration"))`
- L383 _private member_ `FDisplayClusterEditorPropertyReference LightcardPerViewportOCIOProfilesRef;` — `UPROPERTY(EditAnywhere, Transient, Category = "Light Cards", meta = (PropertyPath = "CurrentConfigData.StageSettings.Lightcard.LightcardOCIO.CustomOCIO.PerViewportOCIOProfiles", DisplayName = "Per-Viewport OCIO Overrides"))`
- L387 _private member_ `FDisplayClusterEditorPropertyReference MediaSettingsRef;` — `UPROPERTY(EditDefaultsOnly, Transient, Category = "Media", meta = (PropertyPath = "CurrentConfigData.MediaSettings"))` — Media
- L397 _private member_ `FName ConfigDataName;` — `UPROPERTY()` — Name of the CurrentConfigData asset. Only required if this is a parent of a DisplayClusterBlueprint. The name is used to lookup the config data as a default sub-object, specifically in packaged builds.
- L405 _private member_ `TObjectPtr<USceneComponent> DisplayClusterRootComponent;` — `UPROPERTY(EditAnywhere, Category = "NDisplay", meta = (HideProperty))` — The root component for our hierarchy. Must have CPF_Edit(such as VisibleDefaultsOnly) on property for Live Link. nDisplay details panel will hide this from actually being visible.
- L411 _private member_ `TObjectPtr<UDisplayClusterCameraComponent> DefaultViewPoint;` — `UPROPERTY(VisibleAnywhere, BlueprintGetter=GetDefaultCamera, Category = "NDisplay|Components")` — Default camera component. It's an outer camera in VP/ICVFX terminology. Always exists on a DCRA instance.
- L417 _private member_ `TObjectPtr<UDisplayClusterSyncTickComponent> SyncTickComponent;` — `UPROPERTY()` — Helper sync component. Performs sync procedure during Tick phase.
- L421 _private member_ `TObjectPtr<UDisplayClusterStageGeometryComponent> StageGeometryComponent;` — `UPROPERTY()` — Component that stores the stage's geometry map, which is used to make objects flush with the stage's walls and ceilings
- L425 _private member_ `TObjectPtr<UDisplayClusterStageIsosphereComponent> StageIsosphereComponent;` — `UPROPERTY()` — Component that stores a 3D representation of the stage's geometry map, which can be used to perform ray traces against the processed stage geometry
- L429 _private member_ `EDisplayClusterOperationMode OperationMode;` — Current operation mode
- L431 _private member_ `float LastDeltaSecondsValue = 0.f;`
- L435 _private prototype_ `template <typename TComp> void GetTypedPrimitives(TSet<FPrimitiveComponentId>& OutPrimitives, const TArray<FString>* InCompNames = nullptr, bool bForceHide = false, bool bCollectChildrenVisualizationComponent = true) const;`
- L440 _public member_ `TArray<FDisplayClusterComponentRef> InnerFrustumPriority;` — `UPROPERTY(EditInstanceOnly, EditFixedSize, Category = "In Camera VFX", meta = (TitleProperty = "Name", DisplayAfter = "ShowInnerFrustumOverlapsRef"))` — Set the priority for inner frustum rendering if there is any overlap when enabling multiple ICVFX cameras.
- L446 _public member_ `TObjectPtr<UDisplayClusterConfigurationData> CurrentConfigData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "NDisplay", meta = (AllowPrivateAccess = "true"))` — If set from the DisplayCluster BP Compiler it will be loaded from the class default subobjects in run-time.
- L450 _public prototype_ `static void AddReferencedObjects(class UObject* InThis, class FReferenceCollector& Collector);` — UObject interface
- L453 _public prototype_ `bool IsInnerFrustumEnabled(const FString& InnerFrustumID) const;`
- L457 _public prototype_ `int GetInnerFrustumPriority(const FString& InnerFrustumID) const;` — Return inner frustum priority by InnerFrustum name (from InnerFrustumPriority property) return -1, if not defined
- L459 _public function_ `float GetWorldDeltaSeconds() const`
- L468 _public prototype_ `FDisplayClusterViewport_PreviewSettings GetPreviewSettings(bool bIgnorePreviewSetttingsSource = false) const;` — Get current settings for preview rendering. @param bIgnorePreviewSetttingsSource - if true, the PreviewSettingsSource is ignored
- L478 _private prototype_ `bool PreparePreviewRendererSettings(FDisplayClusterViewport_PreviewSettings& OutPreviewSettings) const;` — Prepares new preview settings. (Access preview settings as read-only data; does not alter DCRA) @param OutPreviewSettings  Filled with the prepared settings. @return True if preview rendering should proceed, false otherwise.
- L487 _public member_ `bool bPreviewEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Enable Editor Preview"))` — Render the scene and display it as a preview on the nDisplay root actor in the editor.  This will impact editor performance.
- L491 _public member_ `bool bPreviewInGameEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay, meta = (DisplayName = "Enable Preview in Game"))` — Render this DCRA in game for Standalone/Package builds.
- L495 _public member_ `float PreviewRenderTargetRatioMult = 0.25;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Preview Screen Percentage", ClampMin = "0.05", UIMin = "0.05", ClampMax = "1", UIMax = "1"))` — Adjust resolution scaling for the editor preview.
- L499 _public member_ `bool bPreviewEnablePostProcess = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Enable Post Process"), BlueprintSetter = SetPreviewEnablePostProcess)` — Enable PostProcess for preview.
- L511 _public member_ `bool bPreviewEnableHoldoutComposite = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Enable Preview Holdout", EditCondition = "bPreviewEnablePostProcess"), BlueprintSetter = SetPreviewEnableHoldoutComposite)` — Render a preview with postprocessing in the scene using the HoldoutComposite plugin. The `Preview`>`Enable Post Process` option must be set These project settings also need to be set: 1. "Alpha Output" 2. "Support Primitive Alpha Holdout (Deferred)"
- L517 _public member_ `bool bPreviewEnableTSR = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Allow TemporalAA/TSR in Preview"))` — Enable TemporalAA/TSR in preview. Increases memory consumption. This will impact editor performance.
- L521 _public member_ `bool bPreviewEnableOCIO = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Enable OCIO on Preview"))` — Enable OCIO on preview.
- L525 _public member_ `bool bPreviewEnableOverlayMaterial = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay, meta = (DisplayName = "Enable Preview Overlay"))` — Show overlay material on the preview mesh when preview rendering is enabled (UMeshComponent::OverlayMaterial).
- L529 _public member_ `bool bEnablePreviewTechvis = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay)` — Configure the root actor for Techvis rendering with preview components.
- L533 _public member_ `bool bEnablePreviewMesh = true;` — `UPROPERTY(Transient, NonTransactional)` — Enable the use of a preview mesh for the preview for this DCRA.
- L537 _public member_ `bool bEnablePreviewEditableMesh = true;` — `UPROPERTY(Transient, NonTransactional)` — Enable the use of a preview editable mesh for the preview for this DCRA.
- L541 _public member_ `EDisplayClusterConfigurationRootActorPreviewSettingsSource PreviewSetttingsSource = EDisplayClusterConfigurationRootActorPreviewSettingsSource::RootActor;` — `UPROPERTY(Transient, NonTransactional)` — Determines where the preview settings will be retrieved from.
- L545 _public member_ `bool bFreezePreviewRender = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Freeze Editor Preview"))` — Freeze preview render.  This will impact editor performance.
- L549 _public member_ `bool bPreviewICVFXFrustums = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Enable Camera Frustums"))` — Render ICVFX Frustums
- L553 _public member_ `float PreviewICVFXFrustumsFarDistance = 1000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay, meta = (DisplayName = "Camera Frustum Distance"))` — Render ICVFX Frustums
- L557 _public member_ `bool bPreviewInGameRenderFrustum = true;` — `UPROPERTY()` — Enables the use of 'bPreviewICVFXFrustums' in the game.
- L562 _public member_ `FString PreviewNodeId = DisplayClusterConfigurationStrings::gui::preview::PreviewNodeNone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Preview Node"))` — Selectively preview a specific viewport or show all/none.
- L566 _public member_ `EDisplayClusterConfigurationRenderMode RenderMode = EDisplayClusterConfigurationRenderMode::Mono;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Render Mode"))` — Render Mode
- L571 _public member_ `int TickPerFrame = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay, meta = (DisplayName = "Tick Per Frame", ClampMin = "1", UIMin = "1", ClampMax = "200", UIMax = "200"))` — Tick Per Frame
- L575 _public member_ `int ViewportsPerFrame = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay, meta = (DisplayName = "Viewports Per Frame", ClampMin = "1", UIMin = "1", ClampMax = "200", UIMax = "200"))` — Max amount of Viewports Per Frame
- L579 _public member_ `int PreviewMaxTextureDimension = 2048;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", AdvancedDisplay, meta = (DisplayName = "Preview Texture Max Size", ClampMin = "64", UIMin = "64", ClampMax = "4096", UIMax = "4096"))` — The maximum dimension of any internal texture for preview. Use less memory for large preview viewports
- L583 _public member_ `TObjectPtr<UDisplayClusterDisplayDeviceBaseComponent> BasicDisplayDeviceComponent;` — `UPROPERTY(VisibleDefaultsOnly, Category = "Preview", DisplayName = "Basic Display Device")` — The included display device nDisplay provides by default
- L587 _public member_ `FName DefaultDisplayDeviceName;` — `UPROPERTY(EditDefaultsOnly, Category = "Preview", AdvancedDisplay, DisplayName = "Default Display Device")` — Select the default display device class to use when a viewport doesn't have one assigned
- L593 _public member_ `bool bPreviewStageGeometryMesh = false;` — `UPROPERTY(EditInstanceOnly, Category = "Preview", AdvancedDisplay)` — Toggles the visibility of the stage's geometry mesh, a smooth, continuous mesh generated and processed from the stage's geometry
- L599 _protected member_ `mutable TObjectPtr<UDisplayClusterDisplayDeviceBaseComponent> DefaultDisplayDeviceComponent;` — `UPROPERTY(Transient, NonTransactional)` — The default display device to use for preview rendering
- L603 _protected member_ `TObjectPtr<ULineBatchComponent> LineBatcherComponent;` — `UPROPERTY(Transient, NonTransactional)` — Line Batchers. All lines to be drawn in the world, but not inside viewports.
- L607 _protected prototype_ `virtual FName GetInternalDisplayDeviceName() const;` — The name the internal default display device uses.
- L617 _public function_ `void EnableEditorRender(bool bValue)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Enable or disable editor render. Preview components may need to be on for texture overrides, but capture and rendering disabled.
- L621 _public function_ `bool IsEditorRenderEnabled() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — If editor rendering is enabled.
- L624 _public prototype_ `DECLARE_DELEGATE(FOnPreviewUpdated);`
- L628 _public function_ `virtual bool ShouldTickIfViewportsOnly() const override` — We need tick in Editor
- L631 _public function_ `FOnPreviewUpdated& GetOnPreviewGenerated()` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L634 _public function_ `FOnPreviewUpdated& GetOnPreviewDestroyed()` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L638 _public function_ `bool IsPreviewEnabled() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — return true, if preview enabled for this actor
- L642 _public function_ `bool IsPreviewDrawnToScreens() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Gets whether the preview output is displayed onto the stage actor's screen meshes
- L644 _public prototype_ `void Constructor_Editor();`
- L645 _public prototype_ `void Destructor_Editor();`
- L649 _public function_ `void RenderPreview_Editor()` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Perform a rendering of the DCRA preview.
- L651 _public prototype_ `void PostLoad_Editor();`
- L652 _public prototype_ `void PostActorCreated_Editor();`
- L653 _public prototype_ `void EndPlay_Editor(const EEndPlayReason::Type EndPlayReason);`
- L654 _public prototype_ `void BeginDestroy_Editor();`
- L655 _public prototype_ `void Destroyed_Editor();`
- L656 _public prototype_ `void RerunConstructionScripts_Editor();`
- L660 _public function_ `void ResetPreviewComponents_Editor(bool bInRestoreSceneMaterial)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Preview components free referenced meshes and materials
- L663 _public function_ `class UDisplayClusterPreviewComponent* GetPreviewComponent(const FString& NodeId, const FString& ViewportId) const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L666 _public function_ `void UpdatePreviewComponents()` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L668 _public function_ `void ReleasePreviewComponents()` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L680 _public function_ `int32 SubscribeToPostProcessRenderTarget(const uint8* Object)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Enable the use of a post process render target when bPreviewEnablePostProcess is disabled on the actor. The root actor will still display a pre post processed preview. This may increase editor overhead. Retrieve the post process texture from the preview component with GetRenderTargetTexturePostProcess(). @param Object The object subscribing to updates @return The number of subscribers to use post process.
- L689 _public function_ `int32 UnsubscribeFromPostProcessRenderTarget(const uint8* Object)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Unsubscribe a registered object from requiring post process render target updates. @param Object The object subscribing to updates. When the counter is zero post process render targets will not be used. @return The number of subscribers to use post process.
- L693 _public function_ `bool DoObserversNeedPostProcessRenderTarget() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — If one or more observers are subscribed to receive post process preview targets.
- L697 _public function_ `bool ShouldThisFrameOutputPreviewToPostProcessRenderTarget() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — When rendering the preview determine which render target should be used for the current frame.
- L701 _public function_ `void AddPreviewEnableOverride(const uint8* Object)` — `UE_DEPRECATED(5.5, "This function has been deprecated.")` — Force preview rendering to be enabled regardless of the user's setting until a matching RemovePreviewEnableOverride call is made.
- L708 _public function_ `void RemovePreviewEnableOverride(const uint8* Object)` — `UE_DEPRECATED(5.5, "This function has been deprecated.")` — Stop forcing preview rendering to be enabled for this caller. If other objects have called AddPreviewEnableOverride, it will remain forced until they have also removed their overrides.
- L711 _public function_ `float GetPreviewRenderTargetRatioMult() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L717 _public function_ `IDisplayClusterViewport* FindPreviewViewport(const FString& InViewportId) const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L723 _public function_ `void GetPreviewRenderTargetableTextures(const TArray<FString>& InViewportNames, TArray<FTextureRHIRef>& OutTextures)` — `UE_DEPRECATED(5.4, "This function has been deprecated.")`
- L726 _public prototype_ `void UpdateInnerFrustumPriority();`
- L727 _public prototype_ `void ResetInnerFrustumPriority();`
- L729 _public prototype_ `virtual bool IsSelectedInEditor() const override;`
- L730 _public prototype_ `void SetIsSelectedInEditor(bool bValue);`
- L734 _public function_ `virtual bool IsDefaultPreviewEnabled() const override` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Don't show actor preview in the level viewport when DCRA actor is selected, but none of its children are.
- L740 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChainEvent) override;`
- L741 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L742 _protected prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L743 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L746 _protected prototype_ `void HandleAssetReload(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Called when the asset has been reloaded in the editor.
- L749 _protected prototype_ `void OnEndObjectMovement(UObject& InObject);` — Raised when any object is moved within a level. Used to update the stage's geometry map if any of its components have been moved
- L754 _private member_ `bool bIsInteractiveEditingSubobject = false;` — Flag to indicate if the user is currently interacting with a subobject of CurrentConfigData.
- L757 _private member_ `bool bRequiresComponentRefresh = false;` — Flag to indicate if we need to reregister components.
- L759 _private member_ `bool bIsSelectedInEditor = false;`
- L761 _private member_ `TWeakPtr<IDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L764 _private member_ `FOnPreviewUpdated DeprecatedPreviewDelegate;` — UE_DEPRECATED 5.4
- L779 _private prototype_ `void AddRootActorExclusiveLockOwner(const TSharedRef<IDisplayClusterViewportManager, ESPMode::ThreadSafe> InOwner);` — Adds InOwner to the exclusive lock holder set. The DCRA remains locked while at least one live holder is registered. @param InOwner  The viewport manager acquiring the lock.
- L786 _private prototype_ `void RemoveRootActorExclusiveLockOwner(const TSharedRef<IDisplayClusterViewportManager, ESPMode::ThreadSafe> InOwner);` — Removes InOwner from the exclusive lock holder set. @param InOwner  The viewport manager releasing the lock.
- L793 _private prototype_ `void RemoveRootActorExpiredLockOwners();` — Purges stale entries from RootActorExclusiveLockOwners: - Expired weak pointers (holder was destroyed). - Holders that no longer claim the lock (IsRootActorLockedByThis() returns false).
- L802 _private prototype_ `bool IsRootActorExclusivelyLocked() const;` — Returns true while at least one live exclusive lock holder is registered. While locked: - Proxy actors (ICVFX panel, StageApp, etc.) may not use this DCRA. - Default scene preview rendering is disabled. - PIE rendering is disabled.
- L807 _private member_ `TSet<TWeakPtr<IDisplayClusterViewportManager, ESPMode::ThreadSafe>> RootActorExclusiveLockOwners;` — Viewport managers currently holding an exclusive lock on this DCRA. Counterpart query: IDisplayClusterViewportConfiguration::IsRootActorLockedByThis().
- L810 _private member_ `mutable FCriticalSection RootActorExclusiveLockOwnersMutex;` — Mutex for RootActorExclusiveLockOwners.

#### Free symbols / members of external scopes

- L624 _delegate_ `DECLARE_DELEGATE(FOnPreviewUpdated);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterRootActorContainers.h` (Public)


#### struct `FDisplayClusterRootActorPropertyOverrides`  
`struct FDisplayClusterRootActorPropertyOverrides`  
_L11-71_
- desc: Optional overrides of root actor settings.
- L14 _public member_ `TOptional<bool> bPreviewInGameEnable;` — Render this DCRA in game for Standalone/Package builds.
- L17 _public member_ `TOptional<bool> bPreviewInGameRenderFrustum;` — Render ICVFX Frustums in game.
- L20 _public member_ `TOptional<bool> bPreviewEnable;` — Render the scene and display it as a preview on the nDisplay root actor in the editor.  This will impact editor performance.
- L23 _public member_ `TOptional<float> PreviewRenderTargetRatioMult;` — Adjust resolution scaling for the editor preview.
- L26 _public member_ `TOptional<bool> bPreviewEnablePostProcess;` — Enable PostProcess for preview.
- L29 _public member_ `TOptional<bool> bPreviewEnableOCIO;` — Enable OCIO on preview.
- L32 _public member_ `TOptional<bool> bPreviewEnableHoldoutComposite;` — Enables the use of 'HoldoutComposite' plugin for the preview rendering.
- L37 _public member_ `TOptional<bool> bPreviewEnableTSR;` — Enable TemporalAA/TSR in preview. Increases memory consumption. This will impact editor performance.
- L40 _public member_ `TOptional<bool> bPreviewEnableOverlayMaterial;` — Show overlay material on the preview mesh when preview rendering is enabled (UMeshComponent::OverlayMaterial).
- L43 _public member_ `TOptional<bool> bEnablePreviewTechvis;` — Configure the root actor for Techvis rendering with preview components.
- L46 _public member_ `TOptional<bool> bEnablePreviewMesh;` — Enable the use of a preview mesh for the preview for this DCRA.
- L49 _public member_ `TOptional<bool> bEnablePreviewEditableMesh;` — Enable the use of a preview editable mesh for the preview for this DCRA.
- L52 _public member_ `TOptional<EDisplayClusterConfigurationRootActorPreviewSettingsSource> PreviewSetttingsSource;` — Determines where the preview settings will be retrieved from.
- L55 _public member_ `TOptional<bool> bFreezePreviewRender;` — Freeze preview render.  This will impact editor performance.
- L58 _public member_ `TOptional<bool> bPreviewICVFXFrustums;` — Render ICVFX Frustums
- L61 _public member_ `TOptional<float> PreviewICVFXFrustumsFarDistance;` — Render ICVFX Frustums
- L64 _public member_ `TOptional<int32> TickPerFrame;` — Tick Per Frame
- L67 _public member_ `TOptional<int32> ViewportsPerFrame;` — Max amount of Viewports Per Frame
- L70 _public member_ `TOptional<int32> PreviewMaxTextureDimension;` — The maximum dimension of any internal texture for preview. Use less memory for large preview viewports

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterSceneViewExtensions.h` (Public)


#### struct `FDisplayClusterSceneViewExtensionContext`  
`struct FDisplayClusterSceneViewExtensionContext : public FSceneViewExtensionContext`  
_L12-58_
- inherits: `FSceneViewExtensionContext`
- desc: Contains information about the context in which this scene view extension will be used.
- L16 _private function_ `virtual FName GetRTTI() const override`
- L18 _private function_ `virtual bool IsHMDSupported() const override`
- L25 _public function_ `FDisplayClusterSceneViewExtensionContext() : FSceneViewExtensionContext()`
- L29 _public function_ `FDisplayClusterSceneViewExtensionContext( FViewport* InViewport, const TSharedRef<const IDisplayClusterViewport, ESPMode::ThreadSafe>& InDisplayClusterViewport) : FSceneViewExtensionContext(InViewport) , DisplayClusterViewport(InDisplayClusterViewport)`
- L36 _public function_ `FDisplayClusterSceneViewExtensionContext( FSceneInterface* InScene, const TSharedRef<const IDisplayClusterViewport, ESPMode::ThreadSafe>& InDisplayClusterViewport) : FSceneViewExtensionContext(InScene) , DisplayClusterViewport(InDisplayClusterViewport)`
- L44 _public function_ `bool IsSameDisplayClusterViewportConfiguration(const TSharedRef<const IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> InConfigurationRef) const` — Returns true if this viewport context refers to the same configuration.
- L57 _public member_ `const TSharedPtr<const IDisplayClusterViewport, ESPMode::ThreadSafe> DisplayClusterViewport;` — Reference to the DC viewport

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterTestPatternsActor.h` (Public)


#### class `ADisplayClusterTestPatternsActor`  
`class ADisplayClusterTestPatternsActor : public AActor`  
_L30-99_
- reflection: `UCLASS()`
- inherits: `AActor`
- desc: Test patterns actor
- L36 _public prototype_ `ADisplayClusterTestPatternsActor(const FObjectInitializer& ObjectInitializer);`
- L42 _public prototype_ `virtual void BeginPlay() override;`
- L43 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L44 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L67 _protected member_ `TObjectPtr<UPostProcessComponent> PostProcessComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NDisplay")` — Postprocess component
- L70 _protected member_ `TMap<FString, TObjectPtr<UMaterial>> CalibrationPatterns;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay")`
- L73 _private prototype_ `void InitializeMaterials();`
- L74 _private prototype_ `void InitializeInternals();`
- L76 _private prototype_ `void UpdatePattern(const TMap<FString, FString>& Params);`
- L78 _private prototype_ `UMaterialInstanceDynamic* CreateMaterialInstance(const FString& PatternId);`
- L79 _private prototype_ `FWeightedBlendable CreateWeightedBlendable(const FString& PatternId);`
- L80 _private prototype_ `FWeightedBlendable CreateWeightedBlendable(UMaterialInstanceDynamic* DynamicMaterialInstance);`
- L81 _private prototype_ `FPostProcessSettings CreatePPSettings(const FString& PatternId);`
- L82 _private prototype_ `FPostProcessSettings CreatePPSettings(UMaterialInstanceDynamic* DynamicMaterialInstance);`
- L84 _private prototype_ `void SetupMaterialParameters(UMaterialInstanceDynamic* DynamicMaterialInstance, const TMap<FString, FMaterialParameter>& Params) const;`
- L86 _private prototype_ `void OnConsoleVariableChangedPattern(IConsoleVariable* Var);`
- L87 _private prototype_ `void OnClusterEventHandler(const FDisplayClusterClusterEventJson& Event);`
- L91 _private member_ `TMap<FString, FPostProcessSettings> ViewportPPSettings;` — `UPROPERTY(transient)`
- L94 _private member_ `EDisplayClusterOperationMode OperationMode = EDisplayClusterOperationMode::Disabled;` — Current nDisplay operation mode
- L96 _private member_ `FOnClusterEventJsonListener OnClusterEvent;` — Cluster event delegate
- L98 _private member_ `FCriticalSection InternalsSyncScope;`

#### enum `ADisplayClusterTestPatternsActor::EParamType`  
`enum class EParamType`  
_L47-51_
- L49 _public enumerator_ `TypeScalar`
- L50 _public enumerator_ `TypeVector`

#### struct `ADisplayClusterTestPatternsActor::FMaterialParameter`  
`struct FMaterialParameter`  
_L53-62_
- L55 _public function_ `FMaterialParameter(EParamType _Type, const FString& _Value) : Type(_Type) , Value(_Value)`
- L60 _public member_ `EParamType Type;`
- L61 _public member_ `FString Value;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterViewportClient.h` (Public)


#### class `UDisplayClusterViewportClient`  
`class UDisplayClusterViewportClient : public UGameViewportClient`  
_L10-34_
- reflection: `UCLASS()`
- inherits: `UGameViewportClient`
- L16 _public prototype_ `UDisplayClusterViewportClient(FVTableHelper& Helper);`
- L17 _public prototype_ `virtual ~UDisplayClusterViewportClient();`
- L19 _public prototype_ `virtual void Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice = true) override;`
- L20 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* SceneCanvas) override;`
- L22 _public prototype_ `virtual TSharedRef<FSceneViewport> CreateViewport(TSharedPtr<SViewport> InViewportWidget) override;`
- L25 _public function_ `virtual float GetDPIScale() const override` — Always use non-scaled viewports with nDisplay
- L32 _protected prototype_ `bool Draw_PIE(FViewport* InViewport, FCanvas* SceneCanvas);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterWorldSubsystem.h` (Public)


#### class `UDisplayClusterWorldSubsystem`  
`class UDisplayClusterWorldSubsystem : public UWorldSubsystem`  
_L22-34_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- desc: World Subsystem used to react to level and world changes. When Concert reloads the packages, streamed levels are removed and re-added without invoiking LoadMap which circumvents FDisplayClusterGameManager::StartScene method invoked inside LoadMap method of DisplayClusterGameEngine. This causes issues such as not updating references to DisplayClusterRootActor which causes memory corruption, crashes and graphic corruption. This Subsystem is used to react to changes in number of levels used in the current world and forces DisplayClusterModule to refresh all of its managers.
- L27 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L28 _public prototype_ `virtual void Deinitialize() override;`
- L33 _public prototype_ `void OnLevelsChanged();` — Event that is triggered when number of levels is changed.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Game/IDisplayClusterGameManager.h` (Public)


#### class `IDisplayClusterGameManager`  
`class IDisplayClusterGameManager`  
_L19-39_
- desc: Public game manager interface
- L22 _public prototype_ `virtual ~IDisplayClusterGameManager() = default;`
- L28 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor() const = 0;` — @return - Current root actor
- L33 _public prototype_ `virtual UWorld* GetWorld() const = 0;` — @return - Current world
- L38 _public prototype_ `virtual TArray<ADisplayClusterRootActor*> GetAllRootActorsFromWorld(UWorld* InWorld) = 0;` — @return - All root actors in world

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/IDisplayCluster.h` (Public)


#### class `IDisplayCluster`  
`class IDisplayCluster : public IModuleInterface`  
_L21-106_
- inherits: `IModuleInterface`
- desc: Public module interface
- L25 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L28 _public prototype_ `virtual ~IDisplayCluster() = default;`
- L37 _public function_ `static inline IDisplayCluster& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L48 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L60 _public function_ `virtual bool IsModuleInitialized() const` — `UE_DEPRECATED(5.4, "This function has been deprecated and will be removed soon.")` — [DEPRECATED] Checks if the module has been initialized. @return Is initialized
- L70 _public prototype_ `virtual EDisplayClusterOperationMode GetOperationMode() const = 0;` — Returns current operation mode. @return Display Cluster operation mode
- L77 _public prototype_ `virtual IDisplayClusterRenderManager* GetRenderMgr() const = 0;` — Access to the device manager. @return Current device manager or nullptr
- L84 _public prototype_ `virtual IDisplayClusterClusterManager* GetClusterMgr() const = 0;` — Access to the cluster manager. @return Current cluster manager or nullptr
- L91 _public prototype_ `virtual IDisplayClusterConfigManager* GetConfigMgr() const = 0;` — Access to the config manager. @return Current config manager or nullptr
- L98 _public prototype_ `virtual IDisplayClusterGameManager* GetGameMgr() const = 0;` — Access to the game manager. @return Current game manager or nullptr
- L105 _public prototype_ `virtual IDisplayClusterCallbacks& GetCallbacks() = 0;` — Access to the DisplayCluster callbacks API @return Callbacks API

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/IDisplayClusterCallbacks.h` (Public)


#### class `IDisplayClusterCallbacks`  
`class IDisplayClusterCallbacks`  
_L28-167_
- desc: DisplayCluster callbacks API
- L31 _public prototype_ `virtual ~IDisplayClusterCallbacks() = default;`
- L35 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterStartSessionEvent);` — Called on session start
- L36 _public prototype_ `virtual FDisplayClusterStartSessionEvent& OnDisplayClusterStartSession() = 0;`
- L39 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterEndSessionEvent);` — Called on session end
- L40 _public prototype_ `virtual FDisplayClusterEndSessionEvent& OnDisplayClusterEndSession() = 0;`
- L43 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterStartSceneEvent);` — Called on start scene
- L44 _public prototype_ `virtual FDisplayClusterStartSceneEvent& OnDisplayClusterStartScene() = 0;`
- L47 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterEndSceneEvent);` — Called on end scene
- L48 _public prototype_ `virtual FDisplayClusterEndSceneEvent& OnDisplayClusterEndScene() = 0;`
- L51 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterStartFrameEvent, uint64);` — Called on DisplayCluster StartFrame
- L52 _public prototype_ `virtual FDisplayClusterStartFrameEvent& OnDisplayClusterStartFrame() = 0;`
- L55 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterEndFrameEvent, uint64);` — Called on DisplayCluster EndFrame
- L56 _public prototype_ `virtual FDisplayClusterEndFrameEvent& OnDisplayClusterEndFrame() = 0;`
- L59 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterPreTickEvent);` — Called on DisplayCluster PreTick
- L60 _public prototype_ `virtual FDisplayClusterPreTickEvent& OnDisplayClusterPreTick() = 0;`
- L63 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterTickEvent);` — Called on DisplayCluster Tick
- L64 _public prototype_ `virtual FDisplayClusterTickEvent& OnDisplayClusterTick() = 0;`
- L67 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterPostTickEvent);` — Called on DisplayCluster PostTick
- L68 _public prototype_ `virtual FDisplayClusterPostTickEvent& OnDisplayClusterPostTick() = 0;`
- L71 _public prototype_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterCustomPresentSetEvent);` — Callback triggered when custom present handler was created
- L72 _public prototype_ `virtual FDisplayClusterCustomPresentSetEvent& OnDisplayClusterCustomPresentSet() = 0;`
- L75 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterPreSubmitViewFamilies, TArray<FSceneViewFamilyContext*>&);` — Callback triggered before submitting view families to render
- L76 _public prototype_ `virtual FDisplayClusterPreSubmitViewFamilies& OnDisplayClusterPreSubmitViewFamilies() = 0;`
- L79 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterPresentationPreSynchronization_RHIThread, FRHIViewport*);` — Called before presentation synchronization is initiated
- L80 _public prototype_ `virtual FDisplayClusterPresentationPreSynchronization_RHIThread& OnDisplayClusterPresentationPreSynchronization_RHIThread() = 0;`
- L83 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterPresentationPostSynchronization_RHIThread, FRHIViewport*);` — Called after presentation synchronization is completed
- L84 _public prototype_ `virtual FDisplayClusterPresentationPostSynchronization_RHIThread& OnDisplayClusterPresentationPostSynchronization_RHIThread() = 0;`
- L87 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterFramePresentated_RHIThread, bool bNativePresent);` — Called after frame presentation
- L88 _public prototype_ `virtual FDisplayClusterFramePresentated_RHIThread& OnDisplayClusterFramePresented_RHIThread() = 0;`
- L91 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterFailoverNodeDown, const FString&);` — Notifies about cluster node failure. Called from AnyThread.
- L92 _public prototype_ `virtual FDisplayClusterFailoverNodeDown& OnDisplayClusterFailoverNodeDown() = 0;`
- L95 _public prototype_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterFailoverPrimaryNodeChanged, const FString&);` — Notifies about new primary node. Called from AnyThread.
- L96 _public prototype_ `virtual FDisplayClusterFailoverPrimaryNodeChanged& OnDisplayClusterFailoverPrimaryNodeChanged() = 0;`
- L99 _public prototype_ `DECLARE_EVENT_FiveParams(IDisplayClusterCallbacks, FDisplayClusterPostTonemapPass_RenderThread, FRDGBuilder&, const IDisplayClusterViewportProxy*, const FSceneView&, const FPostProcessMaterialInputs&, const uint32);` — Called after tonemap pass (before applying OCIO transformation)
- L100 _public prototype_ `virtual FDisplayClusterPostTonemapPass_RenderThread& OnDisplayClusterPostTonemapPass_RenderThread() = 0;`
- L103 _public prototype_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostRenderViewFamily_RenderThread, FRDGBuilder&, const FSceneViewFamily&, const IDisplayClusterViewportProxy*);` — Called once the ViewFamily of this viewport is rendered
- L104 _public prototype_ `virtual FDisplayClusterPostRenderViewFamily_RenderThread& OnDisplayClusterPostRenderViewFamily_RenderThread() = 0;`
- L107 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPreWarp_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called once before warping all available viewports
- L108 _public prototype_ `virtual FDisplayClusterPreWarp_RenderThread& OnDisplayClusterPreWarp_RenderThread() = 0;`
- L111 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPreWarpViewport_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*);` — Called before warping a specific viewport
- L112 _public prototype_ `virtual FDisplayClusterPreWarpViewport_RenderThread& OnDisplayClusterPreWarpViewport_RenderThread() = 0;`
- L115 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostWarp_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called once after warping all the viewports
- L116 _public prototype_ `virtual FDisplayClusterPostWarp_RenderThread& OnDisplayClusterPostWarp_RenderThread() = 0;`
- L119 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostWarpViewport_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*);` — Called after warping a specific viewport
- L120 _public prototype_ `virtual FDisplayClusterPostWarpViewport_RenderThread& OnDisplayClusterPostWarpViewport_RenderThread() = 0;`
- L123 _public prototype_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostCrossGpuTransfer_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — Called after inter-GPU synchronization
- L124 _public prototype_ `virtual FDisplayClusterPostCrossGpuTransfer_RenderThread& OnDisplayClusterPostCrossGpuTransfer_RenderThread() = 0;`
- L127 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPassthroughMediaCapture_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called to process passthrough media capture
- L128 _public prototype_ `virtual FDisplayClusterPassthroughMediaCapture_RenderThread& OnDisplayClusterPassthroughMediaCapture_RenderThread() = 0;`
- L131 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPassthroughMediaInput_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called to process passthrough media input
- L132 _public prototype_ `virtual FDisplayClusterPassthroughMediaInput_RenderThread& OnDisplayClusterPassthroughMediaInput_RenderThread() = 0;`
- L135 _public prototype_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterProcessLatency_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — Called to let the artificial latency subsystem do its job
- L136 _public prototype_ `virtual FDisplayClusterProcessLatency_RenderThread& OnDisplayClusterProcessLatency_RenderThread() = 0;`
- L139 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostResolveOverridden_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*);` — Called for every viewport that has configured content override
- L140 _public prototype_ `virtual FDisplayClusterPostResolveOverridden_RenderThread& OnDisplayClusterPostResolveOverridden_RenderThread() = 0;`
- L143 _public prototype_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostFrameRender_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — Called in the end of the nD rendering chain, right before updating the backbuffer
- L144 _public prototype_ `virtual FDisplayClusterPostFrameRender_RenderThread& OnDisplayClusterPostFrameRender_RenderThread() = 0;`
- L147 _public prototype_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostBackbufferUpdate_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — (deprecated) Called after backbuffer update
- L149 _public prototype_ `virtual FDisplayClusterPostBackbufferUpdate_RenderThread& OnDisplayClusterPostBackbufferUpdate_RenderThread() = 0;` — `UE_DEPRECATED(5.2, "This event getter has been deprecated. Please use OnDisplayClusterPostBackbufferUpdated_RenderThread()")`
- L152 _public prototype_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostBackbufferUpdated_RenderThread, FRHICommandListImmediate&, FViewport*);` — Called after backbuffer update
- L153 _public prototype_ `virtual FDisplayClusterPostBackbufferUpdated_RenderThread& OnDisplayClusterPostBackbufferUpdated_RenderThread() = 0;`
- L156 _public prototype_ `DECLARE_EVENT_FourParams(IDisplayClusterCallbacks, FDisplayClusterPreProcessIcvfx_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*, FDisplayClusterShaderParameters_WarpBlend&, FDisplayClusterShaderParameters_ICVFX&);` — Called before applying ICVFX shaders
- L157 _public prototype_ `virtual FDisplayClusterPreProcessIcvfx_RenderThread& OnDisplayClusterPreProcessIcvfx_RenderThread() = 0;`
- L165 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDisplayClusterUpdateViewportMediaState, IDisplayClusterViewport*, EDisplayClusterViewportMediaState&);` — The viewport can be used by external media, which affects the internal logic of the viewport. Media must use this callback and return their own media states for this viewport. @param InViewport - this viewport wants to know its media state. @param InOutMediaState - the delegate function should raise the desired media state flags to this variable.
- L166 _public prototype_ `virtual FDisplayClusterUpdateViewportMediaState& OnDisplayClusterUpdateViewportMediaState() = 0;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterStartSessionEvent);` — Called on session start
- L39 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterEndSessionEvent);` — Called on session end
- L43 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterStartSceneEvent);` — Called on start scene
- L47 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterEndSceneEvent);` — Called on end scene
- L51 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterStartFrameEvent, uint64);` — Called on DisplayCluster StartFrame
- L55 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterEndFrameEvent, uint64);` — Called on DisplayCluster EndFrame
- L59 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterPreTickEvent);` — Called on DisplayCluster PreTick
- L63 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterTickEvent);` — Called on DisplayCluster Tick
- L67 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterPostTickEvent);` — Called on DisplayCluster PostTick
- L71 _delegate_ `DECLARE_EVENT(IDisplayClusterCallbacks, FDisplayClusterCustomPresentSetEvent);` — Callback triggered when custom present handler was created
- L75 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterPreSubmitViewFamilies, TArray<FSceneViewFamilyContext*>&);` — Callback triggered before submitting view families to render
- L79 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterPresentationPreSynchronization_RHIThread, FRHIViewport*);` — Called before presentation synchronization is initiated
- L83 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterPresentationPostSynchronization_RHIThread, FRHIViewport*);` — Called after presentation synchronization is completed
- L87 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterFramePresentated_RHIThread, bool bNativePresent);` — Called after frame presentation
- L91 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterFailoverNodeDown, const FString&);` — Notifies about cluster node failure. Called from AnyThread.
- L95 _delegate_ `DECLARE_EVENT_OneParam(IDisplayClusterCallbacks, FDisplayClusterFailoverPrimaryNodeChanged, const FString&);` — Notifies about new primary node. Called from AnyThread.
- L99 _delegate_ `DECLARE_EVENT_FiveParams(IDisplayClusterCallbacks, FDisplayClusterPostTonemapPass_RenderThread, FRDGBuilder&, const IDisplayClusterViewportProxy*, const FSceneView&, const FPostProcessMaterialInputs&, const uint32);` — Called after tonemap pass (before applying OCIO transformation)
- L103 _delegate_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostRenderViewFamily_RenderThread, FRDGBuilder&, const FSceneViewFamily&, const IDisplayClusterViewportProxy*);` — Called once the ViewFamily of this viewport is rendered
- L107 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPreWarp_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called once before warping all available viewports
- L111 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPreWarpViewport_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*);` — Called before warping a specific viewport
- L115 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostWarp_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called once after warping all the viewports
- L119 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostWarpViewport_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*);` — Called after warping a specific viewport
- L123 _delegate_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostCrossGpuTransfer_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — Called after inter-GPU synchronization
- L127 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPassthroughMediaCapture_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called to process passthrough media capture
- L131 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPassthroughMediaInput_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*);` — Called to process passthrough media input
- L135 _delegate_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterProcessLatency_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — Called to let the artificial latency subsystem do its job
- L139 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostResolveOverridden_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*);` — Called for every viewport that has configured content override
- L143 _delegate_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostFrameRender_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — Called in the end of the nD rendering chain, right before updating the backbuffer
- L147 _delegate_ `DECLARE_EVENT_ThreeParams(IDisplayClusterCallbacks, FDisplayClusterPostBackbufferUpdate_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportManagerProxy*, FViewport*);` — (deprecated) Called after backbuffer update
- L152 _delegate_ `DECLARE_EVENT_TwoParams(IDisplayClusterCallbacks, FDisplayClusterPostBackbufferUpdated_RenderThread, FRHICommandListImmediate&, FViewport*);` — Called after backbuffer update
- L156 _delegate_ `DECLARE_EVENT_FourParams(IDisplayClusterCallbacks, FDisplayClusterPreProcessIcvfx_RenderThread, FRHICommandListImmediate&, const IDisplayClusterViewportProxy*, FDisplayClusterShaderParameters_WarpBlend&, FDisplayClusterShaderParameters_ICVFX&);` — Called before applying ICVFX shaders
- L165 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDisplayClusterUpdateViewportMediaState, IDisplayClusterViewport*, EDisplayClusterViewportMediaState&);` — The viewport can be used by external media, which affects the internal logic of the viewport. Media must use this callback and return their own media states for this viewport. @param InViewport - this viewport wants to know its media state. @param InOutMediaState - the delegate function should raise the desired media state flags to this variable.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/IDisplayClusterSerializable.h` (Public)


#### class `IDisplayClusterSerializable`  
`class IDisplayClusterSerializable`  
_L11-40_
- desc: nDisplay serialization interface
- L15 _public prototype_ `virtual ~IDisplayClusterSerializable() = default;`
- L39 _public prototype_ `virtual void SerializeDC(FArchive& Ar) = 0;` — Serialize / deserialize method Like the common UE serialization approach, this one is used for both serialization and deserialization. To avoid any method ambiguity issues with UObject::Serialize, this one has the 'DC' postfix. For example, UObject subobjects that also inherit from IDisplayClusterSerializable, can safely go like this: virtual void SomeUObject::Serialize(FArchive& Ar) override { // Serialization implementation } virtual void SomeUObject::SerializeDC(FArchive& Ar) override { Serialize(Ar); } Or vice versa, call 'SerializeDC' from 'Serialize'.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/IDisplayClusterStringSerializable.h` (Public)


#### class `IDisplayClusterStringSerializable`  
`class IDisplayClusterStringSerializable`  
_L13-32_
- desc: DEPRECATED This interface is deprecated and no longer referenced. Its methods are never invoked and will be removed soon. Refer to the IDisplayClusterSerializable interface, which provides common UE binary serialization.
- L17 _public prototype_ `virtual ~IDisplayClusterStringSerializable() = default;`
- L22 _public function_ `virtual FString SerializeToString() const` — `UE_DEPRECATED(5.8, "This method is deprecated and no longer used. Refer to IDisplayClusterSerializable instead.")`
- L28 _public function_ `virtual bool DeserializeFromString(const FString& ar)` — `UE_DEPRECATED(5.8, "This method is deprecated and no longer used. Refer to IDisplayClusterSerializable instead.")`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Math/DisplayClusterProjectionMath.h` (Public)


#### struct `FDisplayClusterProjectionMath`  
`struct FDisplayClusterProjectionMath`  
_L8-125_
- desc: Math utilities for nDisplay projection and frustum calculations.
- L16 _public function_ `static inline FVector GetStereoEyeOffset(const FRotator& InViewRotation, const float StereoEyeOffsetDistance)` — Calculates the ViewOffset for the eye from the view location. @param InViewRotation           Rotation of the view; used to derive the eye direction. @param StereoEyeOffsetDistance  Distance to the eye from the midpoint between the eyes. @return  Offset vector from the original ViewLocation to the eye.
- L22 _public function_ `static inline void GetNonZeroFrustumRange(double& InOutValue0, double& InOutValue1, double n)` — Ensures the frustum range [InOutValue0, InOutValue1] is at least 1 degree wide at the given near distance.
- L39 _public function_ `template <typename T> static T DegreesToNearPlaneExtent(const T AngleDeg, const T ZNear)` — Converts a frustum angle in degrees to a signed extent on the near plane.
- L46 _public function_ `template <typename T> static T NearPlaneExtentToDegrees(const T NearPlaneExtent, const T ZNear)` — Converts a signed extent on the near plane to a frustum angle in degrees.
- L55 _public function_ `template <typename T> static bool MatricesNearlyEqual(const UE::Math::TMatrix<T>& A, const UE::Math::TMatrix<T>& B, float Tolerance = KINDA_SMALL_NUMBER)` — Returns true if matrices A and B are nearly equal within the given Tolerance.
- L84 _public function_ `template <typename T> static UE::Math::TMatrix<T> MakeAsymmetricProjectionMatrix(const T InLeft, const T InRight, const T InTop, const T InBottom, const T InZNear, const T InZFar)` — Builds a perspective projection matrix from asymmetric near-plane extents (off-axis frustum). Inputs are signed distances from the eye to each frustum edge, measured at the near plane. The result uses Unreal's Z-inverted left-handed convention. @param InLeft    Left edge extent at the near plane (typically negative). @param InRight   Right edge extent at the near plane (typically positive). @param InTop     Top edge extent at the near plane (typically positive). @param InBottom  Bottom edge extent at the near plane (typically negative). @param InZNear   Near clip plane distance (must be > 0). @param InZFar    Far clip plane distance. Pass InZNear to use an unlimited far plane.
- L121 _public function_ `template <typename T> static UE::Math::TMatrix<T> MakeAsymmetricProjectionMatrix(const UE::Math::TVector4<T>& InFrustumExtents, const UE::Math::TVector2<T>& InClipPlanes)` — Builds a perspective projection matrix from asymmetric near-plane extents (off-axis frustum). @param InFrustumExtents  Near-plane extents as (Left, Right, Top, Bottom). @param InClipPlanes      Clip distances as (ZNear, ZFar). Pass ZNear in both components for an unlimited far plane.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Math/MarginSet.h` (Public)


#### enum `UE::Math::EMarginSetSideIndex`  
`enum class EMarginSetSideIndex : uint8`  
_L19-25_
- desc: Enumerates the sides of a margin set by index. Used for indexed access to individual sides (Left, Right, Top, Bottom).
- L21 _public enumerator_ `Left = 0`
- L22 _public enumerator_ `Right = 1`
- L23 _public enumerator_ `Top = 2`
- L24 _public enumerator_ `Bottom = 3`

#### struct `UE::Math::TMarginSet`  
`template<typename T> struct alignas(16) TMarginSet`  
_L32-962_
- desc: TMarginSet is a template struct that stores a set of four directional values: Left, Right, Top, and Bottom.
- L44 _public member_ `T Left;` — +--------------------------+ |           Top            | |        +-------+         | |   Left |       |  Right  | |        +-------+         | |         Bottom           | +--------------------------+
- L45 _public member_ `T Right;`
- L46 _public member_ `T Top;`
- L47 _public member_ `T Bottom;`
- L50 _private member_ `static constexpr int32 NumSides = 4;`
- L58 _public function_ `TMarginSet() : Left(T(0)) , Right(T(0)) , Top(T(0)) , Bottom(T(0))` — Default constructor. The default margin size is zero on all four sides.
- L74 _public function_ `TMarginSet(const U InAll) : Left(static_cast<T>(InAll)) , Right(static_cast<T>(InAll)) , Top(static_cast<T>(InAll)) , Bottom(static_cast<T>(InAll))`
- L90 _public function_ `TMarginSet(const IntType InAll) : Left(static_cast<T>(InAll)) , Right(static_cast<T>(InAll)) , Top(static_cast<T>(InAll)) , Bottom(static_cast<T>(InAll))`
- L106 _public function_ `TMarginSet( const U InLeft, const U InRight, const U InTop, const U InBottom) : Left (static_cast<T>(InLeft)) , Right (static_cast<T>(InRight)) , Top (static_cast<T>(InTop)) , Bottom (static_cast<T>(InBottom))`
- L126 _public function_ `TMarginSet( const IntType InLeft, const IntType InRight, const IntType InTop, const IntType InBottom) : Left (static_cast<T>(InLeft)) , Right (static_cast<T>(InRight)) , Top (static_cast<T>(InTop)) , Bottom (static_cast<T>(InBottom))`
- L146 _public function_ `TMarginSet(const TMarginSet<U>& Other) : Left (static_cast<T>(Other.Left)) , Right (static_cast<T>(Other.Right)) , Top (static_cast<T>(Other.Top)) , Bottom (static_cast<T>(Other.Bottom))`
- L162 _public function_ `TMarginSet(const TMarginSet<IntType>& Other) : Left (static_cast<T>(Other.Left)) , Right (static_cast<T>(Other.Right)) , Top (static_cast<T>(Other.Top)) , Bottom (static_cast<T>(Other.Bottom))`
- L178 _public function_ `TMarginSet(const TVector4<U>& Vec) : Left (static_cast<T>(Vec.X)) , Right (static_cast<T>(Vec.Y)) , Top (static_cast<T>(Vec.Z)) , Bottom (static_cast<T>(Vec.W))`
- L194 _public function_ `TMarginSet(const TIntVector4<IntType>& Vec) : Left (static_cast<T>(Vec.X)) , Right (static_cast<T>(Vec.Y)) , Top (static_cast<T>(Vec.Z)) , Bottom (static_cast<T>(Vec.W))`
- L211 _public function_ `inline operator TVector4<U>() const`
- L229 _public function_ `inline operator TIntVector4<IntType>() const`
- L251 _public function_ `inline TMarginSet& AssignMargins(const TVector4<U>& InVector)`
- L273 _public function_ `template <typename IntType> requires (std::is_integral_v<IntType> && std::is_convertible_v<IntType, T>) inline TMarginSet& AssignMargins(const TIntVector4<IntType>& InVector)` — Assigns margins from a TIntVector4<IntType> to this TMarginSet<T>. Enabled only when: - IntType is an integral type - IntType is convertible to T @param InVector  The TIntVector4<IntType> containing the new margin values. @return          Reference to this TMarginSet<T> after assignment.
- L295 _public function_ `inline TMarginSet<T>& AssignMargins(const TMarginSet<U>& Other)`
- L316 _public function_ `inline TMarginSet<T>& AssignMargins(const TMarginSet<IntType>& Other)`
- L338 _public function_ `inline TMarginSet<T>& AssignMargins(const U InLeft, const U InRight, const U InTop, const U InBottom)`
- L359 _public function_ `inline TMarginSet<T>& AssignMargins( const IntType InLeft, const IntType InRight, const IntType InTop, const IntType InBottom)`
- L384 _public function_ `inline TMarginSet<T> operator*(const IntType InScale) const`
- L406 _public function_ `inline TMarginSet<T> operator*(const U InScale) const`
- L429 _public function_ `inline TMarginSet<T> operator*(const TIntPoint<IntType>& Scale) const`
- L454 _public function_ `inline TMarginSet<T> operator*(const TIntVector2<IntType>& Scale) const`
- L480 _public function_ `inline TMarginSet<T> operator*(const TVector2<U>& Scale) const`
- L504 _public function_ `inline TMarginSet<T> operator/(const U InDivisor) const`
- L532 _public function_ `inline TMarginSet<T> operator/(const TIntPoint<IntType>& Divisor) const`
- L561 _public function_ `inline TMarginSet<T> operator/(const TIntVector2<IntType>& Divisor) const`
- L590 _public function_ `inline TMarginSet<T> operator/(const TVector2<U>& Divisor)`
- L624 _public function_ `void ApplyExpandToRect(TIntRect<IntType>& InOutRect) const`
- L653 _public function_ `void ApplyClampedInsetToRect(TIntRect<IntType>& InOutRect) const`
- L681 _public function_ `[[nodiscard]] inline T& operator[](EMarginSetSideIndex SideIndex)` — Provides indexed access to a margin side value. @param SideIndex  Enum value specifying which margin side to access. @return           Reference to the corresponding side value.
- L705 _public function_ `[[nodiscard]] inline const T& operator[](EMarginSetSideIndex SideIndex) const` — Provides  read-only indexed access to a margin side value. @param SideIndex  Enum value specifying which margin side to access. @return           Const reference to the corresponding side value.
- L730 _public function_ `[[nodiscard]] inline T& operator[](int32 Index)` — Provides indexed access to a margin side value by numeric index. @param Index  Zero-based index of the side to access: 0 = Left, 1 = Right, 2 = Top, 3 = Bottom. @return       Reference to the corresponding side value.
- L745 _public function_ `[[nodiscard]] inline const T& operator[](int32 Index) const` — Provides  read-only indexed access to a margin side value by numeric index. @param Index  Zero-based index of the side to access: 0 = Left, 1 = Right, 2 = Top, 3 = Bottom. @return       Const reference to the corresponding side value.
- L754 _public function_ `[[nodiscard]] inline bool operator==(const TMarginSet& Other) const` — Equality operator
- L761 _public function_ `[[nodiscard]] inline bool operator!=(const TMarginSet& Other) const` — Inequality operator
- L772 _public function_ `[[nodiscard]] inline TMarginSet<int32> GetFloorToInt() const` — Returns a copy of this margin set where all margins floors to the nearest lower int32. @return A TMarginSet<int32> with each value floored.
- L787 _public function_ `[[nodiscard]] inline TMarginSet<int32> GetRoundToInt() const` — Returns a copy of this margin set where all margins rounds to the nearest int32. @return A TMarginSet<int32> with all values rounded.
- L802 _public function_ `[[nodiscard]] inline TMarginSet<int32> GetCeilToInt() const` — Returns a copy of this margin set where all margins ceils to the nearest greater or equal int32. @return A TMarginSet<int32> with each value ceiled.
- L820 _public function_ `[[nodiscard]] inline TMarginSet<T> GetClamped(const T Min, const T Max) const` — Returns a copy of this margin set where all margins clamped the specified [Min, Max] range. @param Min           The minimum allowed value for each margin. @param Max           The maximum allowed value for each margin. @return              A clamped TMarginSet with all values between Min and Max.
- L844 _public function_ `[[nodiscard]] inline TMarginSet<T> GetClampedPerSide(const TMarginSet<T>& MinMargins, const TMarginSet& MaxMargins) const` — Returns a copy of this margin set with each side individually clamped between the corresponding sides of the provided minimum and maximum margins. For each side: - Left   = Clamp(Left,   MinMargins.Left,   MaxMargins.Left) - Right  = Clamp(Right,  MinMargins.Right,  MaxMargins.Right) - Top    = Clamp(Top,    MinMargins.Top,    MaxMargins.Top) - Bottom = Clamp(Bottom, MinMargins.Bottom, MaxMargins.Bottom) @param MinMargins Margin set defining the minimum values per side. @param MaxMargins Margin set defining the maximum values per side. @return A new TMarginSet with each side clamped to its respective range.
- L857 _public function_ `[[nodiscard]] inline bool IsZero() const` — Returns true if all margins are zero.
- L870 _public function_ `[[nodiscard]] inline T GetMin() const` — Returns the minimum value among all four margins (Left, Right, Top, Bottom). @return Smallest margin value.
- L883 _public function_ `[[nodiscard]] inline T GetMax() const` — Returns the maximum value among all four margins (Left, Right, Top, Bottom). @return Largest margin value.
- L897 _public function_ `[[nodiscard]] inline TMarginSet<T> GetMinPerSide(const TMarginSet<T>& In) const` — Returns a copy of this margin set where all margins is the minimum of this margin and another. @param In  The margin set to compare against @return    A new TMarginSet with the smallest values for each side
- L913 _public function_ `[[nodiscard]] inline TMarginSet<T> GetMaxPerSide(const TMarginSet<T>& In) const` — Returns a copy of this margin set where all margins is the maximum of this margin and another. @param In  The margin set to compare against @return    A new TMarginSet with the largest values for each side
- L933 _public function_ `[[nodiscard]] inline TMarginSet<T> GetMaxPerSideIfDefined(const TMarginSet<T>& In) const` — Returns a new margin set where each side is the maximum of: - the current value, or - the input value, if it is non-zero (i.e., treated as defined). This allows selectively overriding margins while skipping undefined (zero) inputs. @param In The input margin set, where zero values are treated as "undefined". @return A new margin set with per-side conditional maximums.
- L953 _public function_ `[[nodiscard]] inline TMarginSet<T> GetMinPerSideIfDefined(const TMarginSet<T>& In) const` — Returns a new margin set where each side is the minimum of: - the current value, or - the input value, if it is non-zero (i.e., treated as defined). This allows selectively overriding margins while skipping undefined (zero) inputs. @param In The input margin set, where zero values are treated as "undefined". @return A new margin set with per-side conditional minimum.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Math` (scope `UE`)
- L967 _typedef_ `using FIntMarginSet = UE::Math::TMarginSet<int32>;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterColorEncoding.h` (Public)


#### enum `EDisplayClusterColorEncoding`  
`enum class EDisplayClusterColorEncoding : uint8`  
_L8-21_
- desc: Color encoding type.
- L11 _public enumerator_ `Linear = 0` — Linear color space
- L14 _public enumerator_ `Gamma` — Gamma encoding based on pow(In, Gamma).
- L17 _public enumerator_ `sRGB` — sRGB color space.
- L20 _public enumerator_ `MediaPQ` — ST2084 gamma with saturation (for special use case of nDisplay MediaIO).

#### enum `EDisplayClusterColorPremultiply`  
`enum class EDisplayClusterColorPremultiply : uint8`  
_L24-34_
- desc: Color premultiply type.
- L27 _public enumerator_ `None = 0` — Color is not changed by alpha.
- L30 _public enumerator_ `Premultiply` — Color is premultiplied by Alpha.
- L33 _public enumerator_ `InvertPremultiply` — Color is premultiplied by (1-Alpha).

#### struct `FDisplayClusterColorEncoding`  
`struct FDisplayClusterColorEncoding`  
_L37-115_
- desc: Color encoding data.
- L40 _public prototype_ `FDisplayClusterColorEncoding() = default;` — Constructors.
- L41 _public function_ `FDisplayClusterColorEncoding( const EDisplayClusterColorEncoding InColorEncoding, const EDisplayClusterColorPremultiply InPremultiply = EDisplayClusterColorPremultiply::None) : Encoding(InColorEncoding), Premultiply(InPremultiply)`
- L45 _public function_ `FDisplayClusterColorEncoding( float InGamma, const EDisplayClusterColorPremultiply InPremultiply = EDisplayClusterColorPremultiply::None) : Encoding(EDisplayClusterColorEncoding::Gamma) , GammaValue(InGamma), Premultiply(InPremultiply)`
- L51 _public function_ `EDisplayClusterColorEncoding GetEqualEncoding() const` — Return equal encoding value.
- L68 _public function_ `inline bool operator==(const FDisplayClusterColorEncoding& In) const` — Returns true if the color encodings are the same.
- L79 _public function_ `inline bool IsEqualsGammaEncoding(const FDisplayClusterColorEncoding& In) const` — Compare only gamma encodings.
- L106 _public member_ `EDisplayClusterColorEncoding Encoding = EDisplayClusterColorEncoding::Gamma;` — Color space encoding type.
- L111 _public member_ `float GammaValue = 0.f;` — The gamma value for the `EDisplayClusterColorEncoding::Gamma`. Zero value means default gamma.
- L114 _public member_ `EDisplayClusterColorPremultiply Premultiply = EDisplayClusterColorPremultiply::None;` — Color premultiply modifiers.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterConditionalState.h` (Public)


#### struct `UE::nDisplay::Core::FConditionalState_NoData`  
`struct FConditionalState_NoData`  
_L14-14_
- desc: Default NoContext template parameter

#### class `UE::nDisplay::Core::FConditionalState`  
`template <typename StateDataType, typename InputDataType, typename ContextDataType = FConditionalState_NoData> class FConditionalState`  
_L42-126_
- desc: Conditional State (generic state machine) Manages abstract states based on an abstract input. [SomeInput] -> [ ? ] -> [SomeState] ^ user provided decision maker Also calls back on every state change. StateDataType: Any type representing a state. It must be a copyable and default-constructible type. InputDataType: The type of input data used to evaluate whether a state transition is required, and if so, which state should be transitioned to. ContextDataType: The type of context data. This represents local storage provided to the decision-making delegate on each evaluation. This data is never modified internally; its usage is entirely up to the user.
- L55 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(StateDataType, FMakeDecisionDelegate, const StateDataType& , const InputDataType& , ContextDataType& );` — Decision making delegate Based on the current state and new input, decides which state to switch on, or remain on the old one @param CurrentState - Current state @param NewInput - The input data that is affecting current state @return New state (may be unchanged)
- L56 _public member_ `FMakeDecisionDelegate OnMakeDecision;`
- L66 _public prototype_ `DECLARE_EVENT_TwoParams(FConditionalState, FOnStateChanged, const StateDataType& , const StateDataType& );` — State change event Called every time the state is changed @param OldState - Previous state @param NewState - New state
- L67 _public member_ `FOnStateChanged OnStateChanged;`
- L71 _public function_ `FConditionalState() : CurrentState(StateDataType()) , ContextData(ContextDataType())`
- L76 _public function_ `FConditionalState(const StateDataType& InInitialState) : CurrentState(InInitialState) , ContextData(ContextDataType())`
- L81 _public function_ `FConditionalState(const StateDataType& InInitialState, const ContextDataType& InContextData) : CurrentState(InInitialState) , ContextData(InContextData)`
- L86 _public prototype_ `virtual ~FConditionalState() = default;`
- L95 _public function_ `void Evaluate(const InputDataType& NewInput)` — Processes incoming input and evaluates whether the current state should change. @param NewInput - Input data used to evaluate a potential state transition
- L114 _public function_ `const StateDataType& GetState() const` — Access to the current state @return Current state
- L122 _private member_ `StateDataType CurrentState;` — Tracks current state
- L125 _private member_ `ContextDataType ContextData;` — User context data

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace nDisplay` (scope `UE`)
- L9 _namespace_ `namespace Core` (scope `UE::nDisplay`)
- L55 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(StateDataType, FMakeDecisionDelegate, const StateDataType& , const InputDataType& , ContextDataType& );` — Decision making delegate Based on the current state and new input, decides which state to switch on, or remain on the old one @param CurrentState - Current state @param NewInput - The input data that is affecting current state @return New state (may be unchanged)
- L66 _delegate_ `DECLARE_EVENT_TwoParams(FConditionalState, FOnStateChanged, const StateDataType& , const StateDataType& );` — State change event Called every time the state is changed @param OldState - Previous state @param NewState - New state

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterConsoleExec.h` (Public)


#### class `FDisplayClusterConsoleExec`  
`class FDisplayClusterConsoleExec`  
_L14-23_
- desc: Auxiliary class. Responsible for executing console commands.
- L19 _public prototype_ `static bool Exec(const FDisplayClusterClusterEventJson& InEvent);` — Runs console commands from JSON cluster events
- L22 _public prototype_ `static bool Exec(const FString& InExecutorName, const FString& InExecCommand);` — Generic console command runner

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterDataCache.h` (Public)


#### class `TDisplayClusterDataCache`  
`template<typename InDataType> class TDisplayClusterDataCache`  
_L13-193_
- desc: Cache template for named data with automatic deletion of unused items after timeout.
- L32 _public typedef_ `typedef InDataType DataType;` — Data type of stored objects The following methods must be implemented in DataType: // Return DataCache timeout in frames. A negative value disables the timeout. static int32 GetDataCacheTimeOutInFrames(); // Return true if DataCache is enabled. static bool IsDataCacheEnabled(); // Method for releasing a cached data item, called before its destructor void ReleaseDataCacheItem(); // Returns the unique name of this texture for DataCache. inline const FString& GetDataCacheName() const;
- L34 _public function_ `virtual ~TDisplayClusterDataCache()`
- L40 _public function_ `static inline FString HashString(const FString& InString)` — Helper to perform the very common case of hashing an FString into a hex representation.
- L46 _public function_ `TSharedPtr<DataType, ESPMode::ThreadSafe> Find(const FString& InUniqueDataName)` — Retrieve an existing object by a unique name.
- L63 _public function_ `void Add(const TSharedPtr<DataType, ESPMode::ThreadSafe>& InDataRef)` — Register a new object.
- L77 _protected function_ `void Release()` — Release the cache
- L86 _protected function_ `void Tick(float DeltaTime)` — When the number of DataRef references drops to 1, these items will be removed after a timeout.
- L125 _protected function_ `inline void UpdateTickableGameObject()` — Create or remove tickable game object.
- L185 _private member_ `TArray<FCachedObject> CachedObjects;` — Cached objects map
- L189 _private member_ `TUniquePtr<FDisplayClusterTickableGameObject> TickableGameObject;` — When CachedObjects is not empty, this ticking object will be created. Also, this object will be deleted when CachedObjects becomes empty.
- L192 _private member_ `FDelegateHandle TickHandle;` — Event delegate container of the Tickable object

#### struct `TDisplayClusterDataCache::FCachedObject`  
`struct FCachedObject`  
_L148-182_
- L150 _public function_ `FCachedObject(const TSharedPtr<DataType, ESPMode::ThreadSafe>& InDataRef) : DataRef(InDataRef)`
- L154 _public function_ `~FCachedObject()`
- L160 _public function_ `void Release()` — Release referenced data.
- L172 _public function_ `inline bool IsNameEqual(const FString& InName) const`
- L178 _public member_ `TSharedPtr<DataType, ESPMode::ThreadSafe> DataRef;` — reference to data
- L181 _public member_ `int32 FramesInCachedState = 0;` — After the data ref counter remains 1, this counter will be incremented every frame

#### Free symbols / members of external scopes

- L51 _function_ `` (scope `TDisplayClusterDataCache::Find`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterHelpers.h` (Public)


#### Free symbols / members of external scopes

- L25 _namespace_ `namespace DisplayClusterHelpers`
- L30 _namespace_ `namespace str` (scope `DisplayClusterHelpers`)
- L32 _function_ `static inline FString BoolToStr(bool bVal, bool bAsWord = true)` (scope `DisplayClusterHelpers::str`)
- L39 _function_ `static void TrimStringValue(FString& InLine, bool bTrimQuotes = true)` (scope `DisplayClusterHelpers::str`)
- L59 _function_ `static FString TrimStringValue(const FString& InLine, bool bTrimQuotes = true)` (scope `DisplayClusterHelpers::str`)
- L69 _function_ `template<typename TVal> static void StrToArray(const FString& InData, const FString& InSeparator, TArray<TVal>& OutData, bool bCullEmpty = true)` (scope `DisplayClusterHelpers::str`) — Parses string items separated by specified separator into array Example: item1, item2,item3  ,  item4 => {item1, item2, item3, item4}
- L95 _function_ `template<typename TVal> static FString ArrayToStr(const TArray<TVal>& InData, const FString& InSeparator = FString(DisplayClusterStrings::common::ArrayValSeparator), bool bAddQuotes = true)` (scope `DisplayClusterHelpers::str`) — Exports array data to a string Example: {item1, item2, item3, item4} => "item1,item2,item3,item4"
- L128 _function_ `template<typename TVal> static void StrToSet(const FString& InData, const FString& InSeparator, TSet<TVal>& OutData, bool bCullEmpty = true)` (scope `DisplayClusterHelpers::str`) — Parses string items separated by specified separator into a set Example: item1, item2, item3, item2, item1  ,  item4 => {item1, item2, item3, item4}
- L139 _function_ `template<typename TVal> static FString SetToStr(const TSet<TVal>& InData, const FString& InSeparator = FString(DisplayClusterStrings::common::ArrayValSeparator), bool bAddQuotes = true)` (scope `DisplayClusterHelpers::str`) — Exports set to a string Example: {item1, item2, item3, item4} => "item1,item2,item3,item4"
- L147 _function_ `template<typename TKey, typename TVal> void StrToMap( const FString& InData, TMap<TKey, TVal>& OutData, const FString& InPairSeparator = FString(DisplayClusterStrings::common::PairSeparator), const FString& InKeyValSeparator = FString(DisplayClusterStrings::common::KeyValSeparator))` (scope `DisplayClusterHelpers::str`) — Parses string of key-value pairs separated by specified separator into map Example: "key1=val1 key2=val2 key3=val3" => {{key1, val2}, {key2, val2}, {key3, val3}}
- L174 _function_ `template<typename TKey, typename TVal> FString MapToStr( const TMap<TKey, TVal>& InData, const FString& InPairSeparator = FString(DisplayClusterStrings::common::PairSeparator), const FString& InKeyValSeparator = FString(DisplayClusterStrings::common::KeyValSeparator), bool bAddQuoutes = true)` (scope `DisplayClusterHelpers::str`) — Exports map data to a string Example: {{key1,val1},{key2,val2},{key3,val3}} => "key1=val1 key2=val2 key3=var3"
- L217 _function_ `template<typename T> static bool ExtractValue(const FString& InLine, const FString& InParamName, T& OutValue, bool bInTrimQuotes = true)` (scope `DisplayClusterHelpers::str`) — Extracts value either from a command line string or any other line that matches the same format Example: extracting value of param2 "param1=value1 param2=value2 param3=value3" => value2
- L239 _function_ `template<typename TVal> static bool ExtractArray(const FString& InLine, const FString& InParamName, const FString& InSeparator, TArray<TVal>& OutValue)` (scope `DisplayClusterHelpers::str`) — Extracts array value either from a command line string or any other line that matches the same format Example: extracting array value of param2 "param1=value1 param2="a,b,c,d" param3=value3" => {a,b,c,d}
- L256 _function_ `template<typename TKey, typename TVal> static bool ExtractMap( const FString& InLine, const FString& InParamName, TMap<TKey, TVal>& OutData, const FString& InPairSeparator = FString(DisplayClusterStrings::common::PairSeparator), const FString& InKeyValSeparator = FString(DisplayClusterStrings::common::KeyValSeparator))` (scope `DisplayClusterHelpers::str`) — Extracts map value either from a command line string or any other line that matches the same format Example: extracting map value of param2 "param1=value1 param2="a:1,b:7,c:22" param3=value3" => {{a,1},{b,7}{c,22}}
- L282 _namespace_ `namespace map` (scope `DisplayClusterHelpers`)
- L286 _function_ `template<typename TVal> bool ExtractValue(const TMap<FString, TVal>& InMap, const FString& InKey, TVal& OutValue, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase)` (scope `DisplayClusterHelpers::map`) — Extracts value from TMap<FString, TVal>, returns true if Ok
- L302 _function_ `template<typename TVal> TVal ExtractValue(const TMap<FString, TVal>& InMap, const FString& InKey, const TVal& DefaultValue, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase)` (scope `DisplayClusterHelpers::map`) — Extracts value from TMap<FString, FString>, returns value if found, otherwise default value
- L310 _function_ `template<typename TReturn> bool ExtractValueFromString(const TMap<FString, FString>& InMap, const FString& InKey, TReturn& OutValue, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase)` (scope `DisplayClusterHelpers::map`) — Extracts value from TMap<FString, FString>, returns true and TReturn converted from string, otherwise false
- L324 _function_ `template<typename TReturn> TReturn ExtractValueFromString(const TMap<FString, FString>& InMap, const FString& InKey, const TReturn& DefaultValue, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase)` (scope `DisplayClusterHelpers::map`) — Extracts value from TMap<FString, FString> and converts it to TReturn. If no value found, the default value is returned
- L337 _function_ `template<typename TVal> bool ExtractArrayFromString( const TMap<FString, FString>& InMap, const FString& InKey, TArray<TVal>& OutArray, const FString& InSeparator = DisplayClusterStrings::common::ArrayValSeparator, bool bCullEmpty = true, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase)` (scope `DisplayClusterHelpers::map`) — Extracts array from sting map value
- L356 _function_ `template<typename TKey, typename TVal> bool ExtractMapFromString( const TMap<FString, FString>& InMap, const FString& InKey, TMap<TKey, TVal>& OutMap, const FString& InPairSeparator = FString(DisplayClusterStrings::common::PairSeparator), const FString& InKeyValSeparator = FString(DisplayClusterStrings::common::KeyValSeparator), ESearchCase::Type SearchCase = ESearchCase::IgnoreCase)` (scope `DisplayClusterHelpers::map`) — Extracts map from sting map value
- L378 _namespace_ `namespace game` (scope `DisplayClusterHelpers`)
- L381 _function_ `template<typename T> static void FindAllActors(UWorld* World, TArray<T*>& Out)` (scope `DisplayClusterHelpers::game`)
- L397 _namespace_ `namespace filesystem` (scope `DisplayClusterHelpers`)
- L401 _function_ `static FString GetFullPathForConfig(const FString& RelativeConfig)` (scope `DisplayClusterHelpers::filesystem`) — This helper function looks for a config file provided with relative path. It uses different base directories that are typically used in different runtime environments.
- L431 _function_ `static TArray<FString> GetOrderedConfigResourceDirs()` (scope `DisplayClusterHelpers::filesystem`) — Get ordered search base dirs for resources.
- L459 _function_ `static FString GetRelativePathForConfigResource(const FString& ResourceFullPath)` (scope `DisplayClusterHelpers::filesystem`) — Getting the relative path to an external file
- L480 _function_ `static FString GetFullPathForConfigResource(const FString& ResourcePath)` (scope `DisplayClusterHelpers::filesystem`)
- L509 _function_ `static FString GetFullPathForThirdPartyDLL(const FString& InRelativePathForThirdPartyDll)` (scope `DisplayClusterHelpers::filesystem`) — Returns the full path to the DLL located in the ThirdParty directory in the nDisplay plugin. @param InRelativePathForThirdPartyDll - relative path to dll from ThirdParty root @return full path to file

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterObjectRef.h` (Public)


#### class `FDisplayClusterActorRef`  
`class FDisplayClusterActorRef`  
_L18-197_
- L21 _public function_ `FDisplayClusterActorRef()`
- L24 _public function_ `FDisplayClusterActorRef(const FDisplayClusterActorRef& InActorRef) : WorldPtr(InActorRef.WorldPtr) , ActorClassName(InActorRef.ActorClassName) , ActorClassPtr(InActorRef.ActorClassPtr) , ActorName(InActorRef.ActorName) , ActorPtr(InActorRef.ActorPtr)`
- L32 _public function_ `virtual ~FDisplayClusterActorRef()`
- L36 _public function_ `bool IsDefinedSceneActor() const`
- L42 _public function_ `const TWeakObjectPtr<AActor> GetSceneActorWeakPtr() const` — Returns the current weak ptr of the scene actor object.
- L55 _public function_ `AActor* GetOrFindSceneActor() const` — Return actor object ptr. For killed object ptr, reset and find actor new object ptr by name and save to [mutable] ActorPtr
- L94 _public function_ `bool SetSceneActor(const AActor* InActor)`
- L121 _public function_ `void ResetSceneActor()`
- L135 _private function_ `bool UpdateWorldPtr() const` — Change mutable WorldPtr for re-created world
- L168 _private function_ `bool UpdateActorClassPtr() const` — Find actor new object ptr by name and save to ActorPtr
- L184 _private member_ `mutable TWeakObjectPtr<UWorld> WorldPtr;` — Save world object ptr
- L187 _private member_ `FString ActorClassName;` — Find actor class object ptr by name and save to ActorClassPtr
- L188 _private member_ `mutable TWeakObjectPtr<UClass> ActorClassPtr;`
- L191 _private member_ `FName ActorName;` — Find actor new object ptr by name and save to ActorPtr
- L192 _private member_ `mutable TWeakObjectPtr<AActor> ActorPtr;`
- L196 _protected member_ `mutable FCriticalSection DataGuard;` — Multi-thread data guard

#### class `FDisplayClusterSceneComponentRef`  
`class FDisplayClusterSceneComponentRef : public FDisplayClusterActorRef`  
_L199-268_
- inherits: `FDisplayClusterActorRef`
- L203 _public function_ `FDisplayClusterSceneComponentRef() : FDisplayClusterActorRef()`
- L207 _public function_ `FDisplayClusterSceneComponentRef(const FDisplayClusterSceneComponentRef& InComponentRef) : FDisplayClusterActorRef(InComponentRef) , ComponentName(InComponentRef.ComponentName) , ComponentPtr(InComponentRef.ComponentPtr)`
- L213 _public function_ `FDisplayClusterSceneComponentRef(USceneComponent* InComponent)`
- L219 _public function_ `bool IsDefinedSceneComponent() const`
- L224 _public function_ `bool IsSceneComponentValid() const`
- L231 _public prototype_ `USceneComponent* GetOrFindSceneComponent() const;` — Return component object ptr. For killed object ptr, reset and find component new object ptr by name and save to [mutable] ComponentPtr
- L233 _public function_ `bool SetSceneComponent(USceneComponent* const InComponent)`
- L249 _public function_ `void ResetSceneComponent()`
- L259 _public function_ `bool IsEqualsComponentName(const FName& InComponentName) const`
- L266 _private member_ `FName ComponentName;` — Find component new object ptr by name and save to ComponentPtr
- L267 _private member_ `mutable TWeakObjectPtr<USceneComponent> ComponentPtr;`

#### struct `FDisplayClusterComponentRef`  
`struct FDisplayClusterComponentRef`  
_L271-289_
- reflection: `USTRUCT(meta = (HideChildren))`
- L275 _public function_ `FDisplayClusterComponentRef()`
- L277 _public function_ `FDisplayClusterComponentRef(const FString& InName)`
- L283 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = Component)`
- L285 _public function_ `FORCEINLINE bool operator==(const FDisplayClusterComponentRef& OtherRef) const`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterStrings.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace DisplayClusterStrings`
- L11 _namespace_ `namespace common` (scope `DisplayClusterStrings`)
- L13 _variable_ `static constexpr const TCHAR* PairSeparator = TEXT(" ")` (scope `DisplayClusterStrings::common`)
- L14 _variable_ `static constexpr const TCHAR* KeyValSeparator = TEXT("=")` (scope `DisplayClusterStrings::common`)
- L15 _variable_ `static constexpr const TCHAR* ArrayValSeparator = TEXT(",")` (scope `DisplayClusterStrings::common`)
- L19 _namespace_ `namespace args` (scope `DisplayClusterStrings`)
- L21 _variable_ `static constexpr const TCHAR* Cluster = TEXT("dc_` (scope `DisplayClusterStrings::args`)
- L22 _variable_ `static constexpr const TCHAR* Node = TEXT("dc_` (scope `DisplayClusterStrings::args`)
- L23 _variable_ `static constexpr const TCHAR* Config = TEXT("dc_` (scope `DisplayClusterStrings::args`)
- L24 _variable_ `static constexpr const TCHAR* NodeList = TEXT("dc_` (scope `DisplayClusterStrings::args`)
- L25 _variable_ `static constexpr const TCHAR* NodeRole = TEXT("dc_` (scope `DisplayClusterStrings::args`)
- L28 _namespace_ `namespace role` (scope `DisplayClusterStrings::args`)
- L30 _variable_ `static constexpr const TCHAR* Primary = TEXT("pri` (scope `DisplayClusterStrings::args::role`)
- L31 _variable_ `static constexpr const TCHAR* Secondary = TEXT("sec` (scope `DisplayClusterStrings::args::role`)
- L32 _variable_ `static constexpr const TCHAR* Backup = TEXT("bac` (scope `DisplayClusterStrings::args::role`)
- L36 _namespace_ `namespace dev` (scope `DisplayClusterStrings::args`)
- L38 _variable_ `static constexpr const TCHAR* QBS = TEXT("qua` (scope `DisplayClusterStrings::args::dev`)
- L39 _variable_ `static constexpr const TCHAR* TB = TEXT("dc_` (scope `DisplayClusterStrings::args::dev`)
- L40 _variable_ `static constexpr const TCHAR* SbS = TEXT("dc_` (scope `DisplayClusterStrings::args::dev`)
- L41 _variable_ `static constexpr const TCHAR* Mono = TEXT("dc_` (scope `DisplayClusterStrings::args::dev`)
- L46 _namespace_ `namespace log` (scope `DisplayClusterStrings`)
- L48 _variable_ `static constexpr const TCHAR* Found = TEXT("fou` (scope `DisplayClusterStrings::log`)
- L49 _variable_ `static constexpr const TCHAR* NotFound = TEXT("not` (scope `DisplayClusterStrings::log`)
- L53 _namespace_ `namespace cluster_events` (scope `DisplayClusterStrings`)
- L56 _variable_ `static constexpr const TCHAR* EventCategory = TEXT("nDi` (scope `DisplayClusterStrings::cluster_events`) — Common system events data
- L57 _variable_ `static constexpr const TCHAR* EventType = TEXT("con` (scope `DisplayClusterStrings::cluster_events`)
- L60 _variable_ `static constexpr const TCHAR* EvtQuitName = TEXT("qui` (scope `DisplayClusterStrings::cluster_events`) — Specific events
- L63 _namespace_ `namespace uri_args` (scope `DisplayClusterStrings`)
- L65 _variable_ `static constexpr const TCHAR* ClusterId = TEXT("Clu` (scope `DisplayClusterStrings::uri_args`)
- L66 _variable_ `static constexpr const TCHAR* PrimaryNodeId = TEXT("Pri` (scope `DisplayClusterStrings::uri_args`)
- L67 _variable_ `static constexpr const TCHAR* PrimaryNodePort = TEXT("Pri` (scope `DisplayClusterStrings::uri_args`)
- L68 _variable_ `static constexpr const TCHAR* ClusterNodesNum = TEXT("Clu` (scope `DisplayClusterStrings::uri_args`)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterTickableGameObject.h` (Public)


#### class `FDisplayClusterTickableGameObject`  
`class FDisplayClusterTickableGameObject : public FTickableGameObject`  
_L11-44_
- inherits: `FTickableGameObject`
- desc: Tickable game object: has an OnTick() callback to start all subscribers
- L14 _public prototype_ `FDisplayClusterTickableGameObject() = default;`
- L15 _public prototype_ `virtual ~FDisplayClusterTickableGameObject() = default;`
- L19 _public prototype_ `DECLARE_EVENT_OneParam(FDisplayClusterTickableGameObject, FTickEvent, float);` — Callback on tick
- L20 _public function_ `FTickEvent& OnTick()`
- L25 _public function_ `virtual bool IsTickableInEditor() const override`
- L30 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L32 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L37 _public function_ `virtual TStatId GetStatId() const override`
- L43 _private member_ `FTickEvent TickEvent;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_EVENT_OneParam(FDisplayClusterTickableGameObject, FTickEvent, float);` — Callback on tick

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Misc/DisplayClusterTypesConverter.h` (Public)


#### class `DisplayClusterTypesConverter`  
`class DisplayClusterTypesConverter`  
_L16-42_
- desc: Auxiliary class with different type conversion functions
- L23 _public prototype_ `template <typename ConvertFrom> static FString ToString(const ConvertFrom& From);`
- L29 _public prototype_ `template <typename ConvertTo> static ConvertTo FromString(const FString& From);`
- L35 _public prototype_ `template <typename ConvertFrom> static FString ToHexString(const ConvertFrom& From);`
- L41 _public prototype_ `template <typename ConvertTo> static ConvertTo FromHexString(const FString& From);`
- L48 _prototype_ `template <> FString DisplayClusterTypesConverter::ToHexString <float>(const float& From);`
- L49 _prototype_ `template <> FString DisplayClusterTypesConverter::ToHexString <float>(const float& From);`
- L55 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FString& From)`
- L59 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const bool& From)`
- L60 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const int8& From)`
- L61 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const uint8& From)`
- L62 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const int32& From)`
- L63 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const uint32& From)`
- L64 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const float& From)`
- L65 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const double& From)`
- L66 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FRotator& From)`
- L69 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FVector& From)` — The TVector::ToString() function uses "%3.3f" which compresses the value. A proprietary function is used to get a full-size float.
- L75 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FVector2D& From)` — The TVector2D::ToString() function uses "%3.3f" which compresses the value. A proprietary function is used to get a full-size float.
- L81 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FTimecode& From)` — We can't just use FTimecode ToString as that loses information.
- L86 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FFrameRate& From)`
- L91 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const FQualifiedFrameTime& From)`
- L96 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const EDisplayClusterOperationMode& From)`
- L111 _function_ `template <> inline FString DisplayClusterTypesConverter::ToString<>(const EDisplayClusterSyncGroup& From)`
- L130 _function_ `template <> inline FString DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L134 _function_ `template <> inline bool DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L135 _function_ `template <> inline int8 DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L136 _function_ `template <> inline uint8 DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L137 _function_ `template <> inline int32 DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L138 _function_ `template <> inline uint32 DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L139 _function_ `template <> inline float DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L140 _function_ `template <> inline double DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L142 _function_ `template <> inline FMatrix DisplayClusterTypesConverter::FromString<>(const FString& From)`
- L190 _function_ `template <> inline FQuat DisplayClusterTypesConverter::FromString<>(const FString& From)`
- L207 _function_ `template <> inline FIntPoint DisplayClusterTypesConverter::FromString<>(const FString& From)`
- L222 _function_ `template <> inline FTimecode DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L243 _function_ `template <> inline FFrameRate DisplayClusterTypesConverter::FromString<> (const FString& From)`
- L261 _function_ `template <> inline FQualifiedFrameTime DisplayClusterTypesConverter::FromString<>(const FString& From)`
- L280 _function_ `template <> inline EDisplayClusterSyncGroup DisplayClusterTypesConverter::FromString<>(const FString& From)`
- L302 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const float& From)`
- L307 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const double& From)`
- L312 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const FVector& From)`
- L320 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const FVector2D& From)`
- L327 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const FRotator& From)`
- L335 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const FMatrix& From)`
- L351 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const FTransform& From)`
- L359 _function_ `template <> inline FString DisplayClusterTypesConverter::ToHexString<>(const FQuat& From)`
- L373 _function_ `template <> inline float DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L381 _function_ `template <> inline double DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L389 _function_ `template <> inline FVector DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L405 _function_ `template <> inline FVector2D DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L420 _function_ `template <> inline FRotator DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L436 _function_ `template <> inline FMatrix DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L484 _function_ `template <> inline FTransform DisplayClusterTypesConverter::FromHexString<>(const FString& From)`
- L502 _function_ `template <> inline FQuat DisplayClusterTypesConverter::FromHexString<>(const FString& From)`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/DisplayClusterRender_MeshComponentTypes.h` (Public)


#### enum `EDisplayClusterRender_MeshComponentProxyDataFunc`  
`enum class EDisplayClusterRender_MeshComponentProxyDataFunc : uint8`  
_L8-12_
- desc: Support special mesh proxy geometry funcs
- L10 _public enumerator_ `Disabled = 0`
- L11 _public enumerator_ `OutputRemapScreenSpace`

#### enum `EDisplayClusterRender_MeshComponentGeometrySource`  
`enum class EDisplayClusterRender_MeshComponentGeometrySource: uint8`  
_L15-23_
- desc: Assigned geometry type
- L17 _public enumerator_ `Disabled = 0`
- L18 _public enumerator_ `StaticMeshComponentRef`
- L19 _public enumerator_ `ProceduralMeshComponentRef`
- L20 _public enumerator_ `ProceduralMeshSection`
- L21 _public enumerator_ `StaticMeshAsset`
- L22 _public enumerator_ `MeshGeometry`

#### struct `FDisplayClusterMeshVertex`  
`struct FDisplayClusterMeshVertex`  
_L26-31_
- desc: The vertex data used to filter a texture.
- L28 _public member_ `FVector4 Position;`
- L29 _public member_ `FVector2D UV;`
- L30 _public member_ `FVector2D UV_Chromakey;`

#### struct `FDisplayClusterMeshUVs`  
`struct FDisplayClusterMeshUVs`  
_L34-71_
- desc: Map source geometry UVs to DCMeshComponent UVs
- L43 _public prototype_ `FDisplayClusterMeshUVs() = default;`
- L45 _public function_ `FDisplayClusterMeshUVs(const int32 InBaseUVIndex, const int32 InChromakeyUVIndex)`
- L51 _public function_ `const int32 operator[](const ERemapTarget RemapTarget) const`
- L58 _public function_ `const int32 GetSourceGeometryUVIndex(const ERemapTarget RemapTarget, const int32 MaxValue, const int32 DefaultValue) const`
- L70 _private member_ `int32 RemapValue[(uint8)ERemapTarget::COUNT] = {INDEX_NONE, INDEX_NONE};`

#### enum `FDisplayClusterMeshUVs::ERemapTarget`  
`enum class ERemapTarget: uint8`  
_L36-41_
- L38 _public enumerator_ `Base = 0`
- L39 _public enumerator_ `Chromakey`
- L40 _public enumerator_ `COUNT`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/DisplayClusterRender_MeshGeometry.h` (Public)


#### enum `EDisplayClusterRender_MeshGeometryFormat`  
`enum class EDisplayClusterRender_MeshGeometryFormat : uint8`  
_L9-12_
- L11 _public enumerator_ `OBJ = 0`

#### enum `EDisplayClusterRender_MeshGeometryCreateType`  
`enum class EDisplayClusterRender_MeshGeometryCreateType : uint8`  
_L14-17_
- L16 _public enumerator_ `Passthrough = 0`

#### class `FDisplayClusterRender_MeshGeometry`  
`class FDisplayClusterRender_MeshGeometry`  
_L20-40_
- L23 _public prototype_ `FDisplayClusterRender_MeshGeometry() = default;`
- L24 _public prototype_ `FDisplayClusterRender_MeshGeometry(EDisplayClusterRender_MeshGeometryCreateType CreateType);`
- L25 _public prototype_ `FDisplayClusterRender_MeshGeometry(const FDisplayClusterRender_MeshGeometry& In);`
- L26 _public prototype_ `~FDisplayClusterRender_MeshGeometry() = default;`
- L30 _public prototype_ `bool LoadFromFile(const FString& FullPathFileName, EDisplayClusterRender_MeshGeometryFormat Format = EDisplayClusterRender_MeshGeometryFormat::OBJ);` — Load geometry from OBJ file
- L32 _public prototype_ `void CreatePassthrough();` — Test purpose: create square geometry
- L35 _public member_ `TArray<FVector> Vertices;`
- L36 _public member_ `TArray<FVector> Normal;`
- L37 _public member_ `TArray<FVector2D> UV;`
- L38 _public member_ `TArray<FVector2D> ChromakeyUV;` — Optional
- L39 _public member_ `TArray<int32> Triangles;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/DisplayClusterRender_ProceduralMeshComponentRef.h` (Public)


#### class `FDisplayClusterRender_ProceduralMeshComponentRef`  
`class FDisplayClusterRender_ProceduralMeshComponentRef : public FDisplayClusterSceneComponentRef`  
_L11-36_
- inherits: `FDisplayClusterSceneComponentRef`
- L15 _public function_ `FDisplayClusterRender_ProceduralMeshComponentRef() : FDisplayClusterSceneComponentRef()`
- L19 _public function_ `FDisplayClusterRender_ProceduralMeshComponentRef(const FDisplayClusterRender_ProceduralMeshComponentRef& In) : FDisplayClusterSceneComponentRef(In) , bIsProceduralMeshGeometryDirty(In.bIsProceduralMeshGeometryDirty)`
- L25 _public prototype_ `UProceduralMeshComponent* GetOrFindProceduralMeshComponent() const;` — Get or find the referenced ProceduralMesh component
- L27 _public prototype_ `bool SetProceduralMeshComponentRef(UProceduralMeshComponent* InProceduralMeshComponent);`
- L28 _public prototype_ `void ResetProceduralMeshComponentRef();`
- L30 _public prototype_ `bool IsProceduralMeshGeometryDirty() const;`
- L31 _public prototype_ `void MarkProceduralMeshGeometryDirty() const;`
- L32 _public prototype_ `void ResetProceduralMeshGeometryDirty() const;`
- L35 _private member_ `mutable bool bIsProceduralMeshGeometryDirty = false;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/DisplayClusterRender_StaticMeshComponentRef.h` (Public)


#### class `FDisplayClusterRender_StaticMeshComponentRef`  
`class FDisplayClusterRender_StaticMeshComponentRef : public FDisplayClusterSceneComponentRef`  
_L11-39_
- inherits: `FDisplayClusterSceneComponentRef`
- L15 _public function_ `FDisplayClusterRender_StaticMeshComponentRef() : FDisplayClusterSceneComponentRef()`
- L19 _public function_ `FDisplayClusterRender_StaticMeshComponentRef(const FDisplayClusterRender_StaticMeshComponentRef& In) : FDisplayClusterSceneComponentRef(In) , bIsStaticMeshGeometryDirty(In.bIsStaticMeshGeometryDirty) , MeshGeometryName(In.MeshGeometryName)`
- L26 _public prototype_ `UStaticMeshComponent* GetOrFindStaticMeshComponent() const;` — Get or find the referenced StaticMesh component
- L28 _public prototype_ `bool SetStaticMeshComponentRef(UStaticMeshComponent* InStaticMeshComponent);`
- L29 _public prototype_ `void ResetStaticMeshComponentRef();`
- L31 _public prototype_ `bool IsStaticMeshGeometryDirty() const;`
- L32 _public prototype_ `void MarkStaticMeshGeometryDirty() const;`
- L33 _public prototype_ `void ResetStaticMeshGeometryDirty() const;`
- L36 _private member_ `mutable bool bIsStaticMeshGeometryDirty = false;`
- L38 _private member_ `FName MeshGeometryName;` — Compares the assigned static mesh geometry by name, and raise for changed [mutable] bIsStaticMeshGeometryDirty

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/IDisplayClusterRender_MeshComponent.h` (Public)


#### class `IDisplayClusterRender_MeshComponent`  
`class IDisplayClusterRender_MeshComponent`  
_L20-186_
- L23 _public prototype_ `virtual ~IDisplayClusterRender_MeshComponent() = default;`
- L35 _public prototype_ `virtual void AssignStaticMeshComponentRefs(UStaticMeshComponent* InStaticMeshComponent, const FDisplayClusterMeshUVs& InUVs, USceneComponent* InOriginComponent = nullptr, int32 InLODIndex = 0) = 0;` — Assign static mesh component and origin to this container Then send geometry from the StaticMesh component to proxy @param InStaticMeshComponent - Pointer to the StaticMesh component with geometry for warp @param InUVs                 - Map source geometry UVs to DCMeshComponent UVs @param InOriginComponent     - (optional) stage origin point component @param InLODIndex            - (optional) use geometry from LOD index
- L46 _public prototype_ `virtual void AssignProceduralMeshComponentRefs(UProceduralMeshComponent* InProceduralMeshComponent, const FDisplayClusterMeshUVs& InUVs, USceneComponent* InOriginComponent = nullptr, const int32 InSectionIndex = 0) = 0;` — Assign procedural mesh component, section index and origin to this container Then send geometry from the ProceduralMesh(SectionIndex) to proxy @param InProceduralMeshComponent - Pointer to the ProceduralMesh component with geometry for warp @param InUVs                     - Map source geometry UVs to DCMeshComponent UVs @param InOriginComponent         - (optional) stage origin point component @param InSectionIndex            - (optional) The section index in ProceduralMesh
- L55 _public prototype_ `virtual void AssignProceduralMeshSection(const FProcMeshSection& InProcMeshSection, const FDisplayClusterMeshUVs& InUVs) = 0;` — Assign procedural mesh section geometry Then send geometry from the ProcMeshSection to proxy @param InProcMeshSection - Pointer to the Proce mesh section geometry @param InUVs             - Map source geometry UVs to DCMeshComponent UVs
- L65 _public prototype_ `virtual void AssignStaticMesh(const UStaticMesh* InStaticMesh, const FDisplayClusterMeshUVs& InUVs, int32 InLODIndex = 0) = 0;` — Assign static mesh geometry Then send geometry from the StaticMesh to proxy @param InStaticMesh - Pointer to the StaticMesh geometry @param InUVs        - Map source geometry UVs to DCMeshComponent UVs @param InLODIndex   - (optional) use geometry from LOD index
- L73 _public prototype_ `virtual void AssignMeshGeometry(const FDisplayClusterRender_MeshGeometry* InMeshGeometry) = 0;` — Assign mesh geometry Then send geometry to proxy @param InMeshGeometry - Pointer to the source geometry data
- L81 _public prototype_ `virtual void AssignMeshGeometry_RenderThread(const FDisplayClusterRender_MeshGeometry* InMeshGeometry, const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc) const = 0;` — Create mesh geometry on render thread (debug purpose) @param InMeshGeometry - Pointer to the source geometry data @param InDataFunc     - Geometry function type
- L87 _public prototype_ `virtual void ReleaseMeshComponent() = 0;` — Release refs, proxy, RHI.
- L93 _public prototype_ `virtual void ReleaseProxyGeometry() = 0;` — Release proxy
- L100 _public prototype_ `virtual USceneComponent* GetOriginComponent() const = 0;` — Get referenced Origin component object @return - pointer to the Origin component
- L107 _public prototype_ `virtual UMeshComponent* GetMeshComponent() const = 0;` — Get referenced Mesh component object @return - pointer to the Mesh component
- L114 _public prototype_ `virtual UStaticMeshComponent* GetStaticMeshComponent() const = 0;` — Get referenced StaticMesh component object @return - pointer to the StaticMesh component
- L121 _public prototype_ `virtual const UStaticMesh* GetStaticMesh() const = 0;` — Get referenced StaticMesh object @return - pointer to the StaticMesh object
- L128 _public prototype_ `virtual UProceduralMeshComponent* GetProceduralMeshComponent() const = 0;` — Get referenced ProceduralMesh component object @return - pointer to the ProceduralMesh component
- L137 _public prototype_ `virtual const FStaticMeshLODResources* GetStaticMeshComponentLODResources(int32 InLODIndex = 0) const = 0;` — Get geometry from assigned StaticMesh component @param LodIndex - (optional) lod index @return - pointer to the static mesh geometry
- L146 _public prototype_ `virtual const FProcMeshSection* GetProceduralMeshComponentSection(const int32 SectionIndex = 0) const = 0;` — Get geometry from assigned ProceduralMesh section by index @param SectionIndex - Geometry source section index @return - pointer to the geometry section data
- L153 _public prototype_ `virtual IDisplayClusterRender_MeshComponentProxy* GetMeshComponentProxy_RenderThread() const = 0;` — Get nDisplay mesh component proxy object @return - pointer to the nDisplay mesh component proxy
- L160 _public prototype_ `virtual void SetGeometryFunc(const EDisplayClusterRender_MeshComponentProxyDataFunc InDataFunc) = 0;` — Set geometry preprocess function. This function change geometry prepared for proxy @param InDataFunc - geometry function type
- L165 _public prototype_ `virtual bool IsMeshComponentRefGeometryDirty() const = 0;` — Return true if referenced component geometry changed
- L170 _public prototype_ `virtual void MarkMeshComponentRefGeometryDirty() const = 0;` — Mark referenced component geometry as changed
- L175 _public prototype_ `virtual void ResetMeshComponentRefGeometryDirty() const = 0;` — Clear referenced component geometry changed flag
- L180 _public prototype_ `virtual bool EqualsMeshComponentName(const FName& InMeshComponentName) const = 0;` — return true, if referenced component name is equal
- L185 _public prototype_ `virtual EDisplayClusterRender_MeshComponentGeometrySource GetGeometrySource() const = 0;` — return assigned geometry source type

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/IDisplayClusterRender_MeshComponentProxy.h` (Public)


#### class `IDisplayClusterRender_MeshComponentProxy`  
`class IDisplayClusterRender_MeshComponentProxy`  
_L10-34_
- L13 _public prototype_ `virtual ~IDisplayClusterRender_MeshComponentProxy() = default;`
- L21 _public prototype_ `virtual bool BeginRender_RenderThread(FRHICommandListImmediate& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit) const = 0;` — Initialize RHI for mesh render return - true, if the mesh can be rendered
- L28 _public prototype_ `virtual bool FinishRender_RenderThread(FRHICommandListImmediate& RHICmdList) const = 0;` — Render mesh geometry return - true, if the mesh rendered
- L33 _public prototype_ `virtual bool IsEnabled_RenderThread() const = 0;` — Return true, if mesh valid and can be rendered

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Containers/IDisplayClusterRender_Texture.h` (Public)


#### class `IDisplayClusterRender_Texture`  
`class IDisplayClusterRender_Texture`  
_L14-58_
- desc: A runtime texture that is created based on data in memory
- L17 _public prototype_ `virtual ~IDisplayClusterRender_Texture() = default;`
- L21 _public prototype_ `virtual TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharePtr from this.
- L22 _public prototype_ `virtual TSharedPtr<const IDisplayClusterRender_Texture, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L36 _public prototype_ `virtual void CreateTexture(const void* InTextureData, const uint32 InComponentDepth, const uint32 InBitDepth, uint32_t InWidth, uint32_t InHeight, bool bInHasCPUAccess = false) = 0;` — Create texture from memory data @param InTextureData    - Pointer to texture data in memory @param InComponentDepth - Components per pixel @param InBitDepth       - Bit per component @param InWidth          - Texture width in pixels @param InHeight         - Texture height in pixels @param bInHasCPUAccess  - has CPU access to texture data, dont release from memory @return - true, if the texture resource was created successfully
- L39 _public prototype_ `virtual bool IsEnabled() const = 0;` — True if the texture resource is initialized.
- L42 _public prototype_ `virtual void* GetData() const = 0;` — Get ptr to resource data in memory (The texture must be created with bInHasCPUAccess set to true).
- L45 _public prototype_ `virtual uint32_t GetWidth() const = 0;` — Get texture width.
- L48 _public prototype_ `virtual uint32_t GetHeight() const = 0;` — Get texture height.
- L51 _public prototype_ `virtual EPixelFormat GetPixelFormat() const = 0;` — Get texture pixel format.
- L54 _public prototype_ `virtual uint32 GetComponentDepth() const = 0;` — Get number of components.
- L57 _public prototype_ `virtual FRHITexture* GetRHITexture() const = 0;` — Get the RHI resource.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Device/IDisplayClusterRenderDevice.h` (Public)


#### class `IDisplayClusterRenderDevice`  
`class IDisplayClusterRenderDevice : public IStereoRendering`  
_L21-84_
- inherits: `IStereoRendering`
- desc: nDisplay render device interface
- L24 _public prototype_ `virtual ~IDisplayClusterRenderDevice() = default;`
- L33 _public function_ `virtual bool Initialize()` — Device initialization @return - true if success
- L39 _public function_ `virtual void StartScene(UWorld* World)` — Called on a scene start to allow a rendering device to initialize any world related content
- L45 _public function_ `virtual void PreTick(float DeltaSeconds)` — Called before scene Tick
- L51 _public function_ `virtual void EndScene()` — Called before unload current level
- L59 _public prototype_ `virtual bool BeginNewFrame(FViewport* InViewport, UWorld* InWorld, FDisplayClusterRenderFrame& OutRenderFrame) = 0;` — Update settings from root actor config data, and build new frame structure This function also updates all viewport settings from config. Must be called before the InitializeNewFrame() function.
- L67 _public prototype_ `virtual void InitializeNewFrame() = 0;` — Initialize internal data to render a new frame Initialize references to DCRA objects. Must be called before viewports start rendering [ This pair of functions InitializeNewFrame\FinalizeNewFrame should always be called together. ]
- L75 _public prototype_ `virtual void FinalizeNewFrame() = 0;` — Finish rendering the frame and compose the viewports for the final RTT (Warp&Blend, OCIO, ICVFX, etc.) Release references to DCRA objects. Must be called after all viewports have been rendered. [ This pair of functions InitializeNewFrame\FinalizeNewFrame should always be called together. ]
- L82 _public prototype_ `virtual IDisplayClusterPresentation* GetPresentation() const = 0;` — Returns current presentation handler @return - nullptr if failed

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Device/IDisplayClusterRenderDeviceFactory.h` (Public)


#### class `IDisplayClusterRenderDeviceFactory`  
`class IDisplayClusterRenderDeviceFactory`  
_L13-27_
- desc: nDisplay rendering device factory interface
- L16 _public prototype_ `virtual ~IDisplayClusterRenderDeviceFactory() = default;`
- L26 _public prototype_ `virtual TSharedPtr<IDisplayClusterRenderDevice, ESPMode::ThreadSafe> Create(const FString& InDeviceType) = 0;` — Creates a rendering device instance @param InDeviceType - device type that has been specified on registering the factory (may be useful if the same factory is responsible for multiple device types) @return - rendering device

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/DisplayDevice/Components/DisplayClusterDisplayDeviceBaseComponent.h` (Public)


#### class `UDisplayClusterDisplayDeviceBaseComponent`  
`class UDisplayClusterDisplayDeviceBaseComponent : public USceneComponent`  
_L27-104_
- reflection: `UCLASS(Abstract, ClassGroup = (DisplayCluster), HideCategories = (Transform, Rendering, Tags, Activation, Cooking, Physics, LOD, AssetUserData, Navigation))`
- inherits: `USceneComponent`
- desc: Display Device Components can be added to nDisplay root actors and assigned to viewport nodes to allow additional processing on the preview material.
- L32 _public prototype_ `UDisplayClusterDisplayDeviceBaseComponent();`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L44 _public prototype_ `virtual TObjectPtr<UMaterial> GetDisplayDeviceMaterial(const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType) const;` — Receive material by type @param InMeshType     - mesh type @param InMaterialType - the type of material being requested
- L54 _public prototype_ `virtual void OnUpdateDisplayDeviceMeshAndMaterialInstance(IDisplayClusterViewportPreview& InViewportPreview, const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType, UMeshComponent* InMeshComponent, UMaterialInstanceDynamic* InMeshMaterialInstance) const;` — Perform any operations on the  material instance, such as setting parameter values. @param InViewportPreview  - current viewport @param InMeshType         - mesh type @param InMaterialType     - type of material being requested @param InMeshComponent - mesh component to be updated @param InMeshMaterialInstance - material instance that used on this mesh
- L60 _public prototype_ `virtual TSharedPtr<IDisplayClusterDisplayDeviceProxy, ESPMode::ThreadSafe> GetDisplayDeviceProxy(IDisplayClusterViewportConfiguration& InConfiguration);` — Update and Get proxy object for rendering thread. @param InConfiguration - current viewport configuration
- L71 _public prototype_ `virtual void SetupSceneView(const IDisplayClusterViewportPreview& InViewportPreview, uint32 ContextNum, FSceneViewFamily& InOutViewFamily, FSceneView& InOutView) const;` — Setup view for this Display Device @param InViewport      - the current viewport @param ContextNum      - context index (eye) @param InOutViewFamily - [In,Out] ViewFamily. @param InOutView       - [In,Out] View. @return - none.
- L79 _protected prototype_ `virtual void UpdateDisplayDeviceProxyImpl(IDisplayClusterViewportConfiguration& InConfiguration);` — Updating the proxy object for the current configuration. If the current configuration does not allow for a display device, this function will remove the DisplayDeviceProxy variable. @param InConfiguration - current viewport configuration
- L82 _protected prototype_ `virtual bool ShouldUseDisplayDevice(IDisplayClusterViewportConfiguration& InConfiguration) const;` — Returns true if the display device should be used for rendering in nDisplay
- L87 _protected member_ `bool bEnableRenderPass = false;` — `UPROPERTY(EditAnywhere, Category=RenderPass)` — If render passes are enabled.
- L91 _protected member_ `TObjectPtr<UMaterial> MeshMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = Material, NoClear)` — The material to assign to the static mesh when preview is disabled.
- L95 _protected member_ `TObjectPtr<UMaterial> PreviewMeshMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category=Material, NoClear)` — The material the preview components will create a material instance from when rendering the nDisplay preview.
- L99 _protected member_ `TObjectPtr<UMaterial> PreviewMeshTechvisMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = Material, NoClear)` — [techvis] The material the preview components will create a material instance from when rendering the nDisplay preview.
- L103 _protected member_ `TSharedPtr<IDisplayClusterDisplayDeviceProxy, ESPMode::ThreadSafe> DisplayDeviceProxy;` — Display device proxy object.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/DisplayDevice/Components/DisplayClusterDisplayDeviceComponent.h` (Public)


#### class `UDisplayClusterDisplayDeviceComponent`  
`class UDisplayClusterDisplayDeviceComponent : public UDisplayClusterDisplayDeviceBaseComponent`  
_L19-44_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Display Device"))`
- inherits: `UDisplayClusterDisplayDeviceBaseComponent`
- desc: Display Device Component with OCIO render pass
- L25 _public prototype_ `UDisplayClusterDisplayDeviceComponent();`
- L28 _public prototype_ `virtual void OnUpdateDisplayDeviceMeshAndMaterialInstance(IDisplayClusterViewportPreview& InViewportPreview, const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType, UMeshComponent* InMeshComponent, UMaterialInstanceDynamic* InMeshMaterialInstance) const override;`
- L29 _public prototype_ `virtual void UpdateDisplayDeviceProxyImpl(IDisplayClusterViewportConfiguration& InConfiguration) override;`
- L35 _protected member_ `float Exposure = 0.f;` — `UPROPERTY(EditAnywhere, Category=Material)` — Adjust the exposure for the emissive input.
- L39 _protected member_ `float Gamma = 1.f;` — `UPROPERTY(EditAnywhere, Category = Material)` — Adjust the gamma for the emissive input.
- L43 _protected member_ `FOpenColorIOColorConversionSettings ColorConversionSettings;` — `UPROPERTY(EditAnywhere, Category = RenderPass, meta = (DisplayAfter="bEnableRenderPass"))` — Color grading settings.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/DisplayDevice/Containers/DisplayClusterDisplayDevice_Enums.h` (Public)


#### enum `EDisplayClusterDisplayDeviceMaterialType`  
`enum class EDisplayClusterDisplayDeviceMaterialType : uint8`  
_L10-17_
- desc: Display Device materials
- L13 _public enumerator_ `PreviewMeshMaterial` — Preview on mesh
- L16 _public enumerator_ `PreviewMeshTechvisMaterial` — Preview on mesh for techvis

#### enum `EDisplayClusterDisplayDeviceMeshType`  
`enum class EDisplayClusterDisplayDeviceMeshType : uint8`  
_L22-33_
- desc: Display Device mesh type
- L25 _public enumerator_ `DefaultMesh = 0` — Default mesh without preview
- L28 _public enumerator_ `PreviewMesh` — Preview mesh
- L31 _public enumerator_ `PreviewEditableMesh` — Preview editable mesh

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/DisplayDevice/IDisplayClusterDisplayDeviceProxy.h` (Public)


#### class `IDisplayClusterDisplayDeviceProxy`  
`class IDisplayClusterDisplayDeviceProxy`  
_L25-115_
- desc: Display Device Proxy object interface [rendering thread]
- L28 _public prototype_ `virtual ~IDisplayClusterDisplayDeviceProxy() = default;`
- L33 _public function_ `virtual bool HasFinalPass_RenderThread() const` — Is final pass used
- L45 _public function_ `virtual bool AddFinalPass_RenderThread(const FDisplayClusterShadersTextureUtilsSettings& InTextureUtilsSettings, const TSharedRef<IDisplayClusterShadersTextureUtils, ESPMode::ThreadSafe>& InTextureUtils) const` — Add render pass at the end of nDisplay pipeline. @param InTextureUtilsSettings - A settings for render @param InTextureUtils         - A container of resources for processing. @return - true if success.
- L51 _public function_ `virtual bool ShouldUsePostProcessPassAfterFXAA() const` — Allow callback OnPostProcessPassAfterFXAA.
- L63 _public function_ `virtual FScreenPassTexture OnPostProcessPassAfterFXAA_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum)` — Callback OnPostProcessPassAfterFXAA. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @param ContextNum   - viewport context index @return - Screen pass texture
- L67 _public function_ `virtual bool ShouldUsePostProcessPassAfterSSRInput() const` — Allow callback OnPostProcessPassAfterSSRInput.
- L79 _public function_ `virtual FScreenPassTexture OnPostProcessPassAfterSSRInput_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum)` — Callback OnPostProcessPassAfterSSRInput. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @param ContextNum   - viewport context index @return - Screen pass texture
- L83 _public function_ `virtual bool ShouldUsePostProcessPassTonemap() const` — Allow callback OnPostProcessPassAfterTonemap.
- L95 _public function_ `virtual FScreenPassTexture OnPostProcessPassAfterTonemap_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum)` — Callback OnPostProcessPassAfterTonemap. @param GraphBuilder - RDG interface @param View         - Scene View @param Inputs       - PP Input resources @param ContextNum   - viewport context index @return - Screen pass texture
- L110 _public function_ `virtual bool AddFinalPass_RenderThread(FRDGBuilder& GraphBuilder, const FDisplayClusterViewport_Context& InViewportContext, FRHITexture* InputTextureRHI, const FIntRect& InputRect, FRHITexture* OutputTextureRHI, const FIntRect& OutputRect) const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Please use 'AddFinalPass_RenderThread()'.")` — Add render pass at the end of nDisplay pipeline. @param GraphBuilder      - RDG interface. @param InViewportContext - DC viewport context. @param InputTextureRHI   - Source texture. @param InputRect         - Source rec. @param OutputTextureRHI  - Destination texture. @param OutputRect        - Destination rec. @return - true if success.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/GUILayer/IDisplayClusterGUILayerController.h` (Public)


#### class `IDisplayClusterGUILayerController`  
`class IDisplayClusterGUILayerController`  
_L16-48_
- desc: GUI controller interface Represents a mediator that controls how Slate/UMG output is rendered to the backbuffer. It also provides access to the texture containing the GUI (the so-called GUI layer).
- L20 _public prototype_ `virtual ~IDisplayClusterGUILayerController() = default;`
- L38 _public prototype_ `virtual EGuiOutputMode GetOutputMode() const = 0;` — Return current operation mode
- L41 _public prototype_ `virtual bool IsEnabled() const = 0;` — Returns true if GUI controller is currently enabled
- L44 _public prototype_ `virtual FIntPoint GetGuiLayerTextureSize() const = 0;` — Returns current GUI layer texture size, or {0, 0} if disabled.
- L47 _public prototype_ `virtual FTextureRHIRef GetGuiLayerTexture_RenderThread() = 0;` — Returns current GUI layer texture if available, otherwise invalid reference

#### enum `IDisplayClusterGUILayerController::EGuiOutputMode`  
`enum class EGuiOutputMode : uint8`  
_L27-33_
- desc: Supported operation modes
- L29 _public enumerator_ `Disabled = 0` — GUI layer controller is completely disabled
- L30 _public enumerator_ `Hidden = 1` — Never render to the output
- L31 _public enumerator_ `Whole = 2` — Render in the output (backbuffer) space like UE natively does
- L32 _public enumerator_ `Propagated = 3` — Per-viewport GUI output

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/IDisplayClusterRenderManager.h` (Public)


#### class `IDisplayClusterRenderManager`  
`class IDisplayClusterRenderManager`  
_L28-228_
- desc: Public render manager interface
- L31 _public prototype_ `virtual ~IDisplayClusterRenderManager() = default;`
- L52 _public prototype_ `virtual IDisplayClusterRenderDevice* GetRenderDevice() const = 0;` — Returns current rendering device @return - nullptr if failed
- L62 _public prototype_ `virtual bool RegisterRenderDeviceFactory(const FString& DeviceType, TSharedPtr<IDisplayClusterRenderDeviceFactory>& Factory) = 0;` — Registers rendering device factory @param DeviceType - Type of rendering device @param Factory    - Factory instance @return - True if success
- L71 _public prototype_ `virtual bool UnregisterRenderDeviceFactory(const FString& DeviceType) = 0;` — Unregisters rendering device factory @param DeviceType - Type of rendering device @return - True if success
- L81 _public prototype_ `virtual bool RegisterSynchronizationPolicyFactory(const FString& SyncPolicyType, TSharedPtr<IDisplayClusterRenderSyncPolicyFactory>& Factory) = 0;` — Registers synchronization policy factory @param SyncPolicyType - Type of synchronization policy @param Factory        - Factory instance @return - True if success
- L90 _public prototype_ `virtual bool UnregisterSynchronizationPolicyFactory(const FString& SyncPolicyType) = 0;` — Unregisters synchronization policy factory @param SyncPolicyType - Type of synchronization policy @return - True if success
- L97 _public prototype_ `virtual TSharedPtr<IDisplayClusterRenderSyncPolicy> GetCurrentSynchronizationPolicy() = 0;` — Returns currently active rendering synchronization policy object @return - Rendering synchronization policy object
- L107 _public prototype_ `virtual bool RegisterProjectionPolicyFactory(const FString& ProjectionType, TSharedPtr<IDisplayClusterProjectionPolicyFactory>& Factory) = 0;` — Registers projection policy factory @param ProjectionType - Type of projection data (MPCDI etc.) @param Factory        - Factory instance @return - True if success
- L116 _public prototype_ `virtual bool UnregisterProjectionPolicyFactory(const FString& ProjectionType) = 0;` — Unregisters projection policy factory @param ProjectionType - Type of projection policy @return - True if success
- L125 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicyFactory> GetProjectionPolicyFactory(const FString& ProjectionType) = 0;` — Returns a projection policy factory of specified type (if it has been registered previously) @param ProjectionType - Projection policy type @return - Projection policy factory pointer or nullptr if not registered
- L132 _public prototype_ `virtual void GetRegisteredProjectionPolicies(TArray<FString>& OutPolicyIDs) const = 0;` — Returns all registered projection policy types @param OutPolicyIDs - (out) array to put registered IDs
- L142 _public prototype_ `virtual bool RegisterPostProcessFactory(const FString& PostProcessType, TSharedPtr<IDisplayClusterPostProcessFactory>& Factory) = 0;` — Registers PostProcess factory @param PostProcessType - Type of PostProcess data @param Factory        - Factory instance @return - True if success
- L151 _public prototype_ `virtual bool UnregisterPostProcessFactory(const FString& PostProcessType) = 0;` — Unregisters PostProcess factory @param PostProcessType - Type of post process @return - True if success
- L160 _public prototype_ `virtual TSharedPtr<IDisplayClusterPostProcessFactory> GetPostProcessFactory(const FString& PostProcessType) = 0;` — Returns a postprocess factory of specified type (if it has been registered previously) @param PostProcessType - PostProcess type @return - PostProcess factory pointer or nullptr if not registered
- L167 _public prototype_ `virtual void GetRegisteredPostProcess(TArray<FString>& OutPostProcessIDs) const = 0;` — Returns all registered postprocess types @param OutPostProcessIDs - (out) array to put registered IDs
- L177 _public prototype_ `virtual bool RegisterWarpPolicyFactory(const FString& InWarpPolicyType, TSharedPtr<IDisplayClusterWarpPolicyFactory>& Factory) = 0;` — Registers warp policy factory @param InWarpPolicyType - Type of warp policy @param Factory          - Factory instance @return - True if success
- L186 _public prototype_ `virtual bool UnregisterWarpPolicyFactory(const FString& InWarpPolicyType) = 0;` — Unregisters warp policy factory ` @param InWarpPolicyType - Type of warp policy @return - True if success
- L195 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpPolicyFactory> GetWarpPolicyFactory(const FString& InWarpPolicyType) = 0;` — Returns a warp policy factory of specified type (if it has been registered previously) @param InWarpPolicyType - Warp policy type @return - Warp policy factory pointer or nullptr if not registered
- L202 _public prototype_ `virtual void GetRegisteredWarpPolicies(TArray<FString>& OutWarpPolicyIDs) const = 0;` — Returns all registered warp policy types @param OutWarpPolicyIDs - (out) array to put registered IDs
- L207 _public prototype_ `virtual TSharedPtr<IDisplayClusterVblankMonitor, ESPMode::ThreadSafe> GetVblankMonitor() = 0;` — Returns V-blank monitor interface
- L212 _public prototype_ `virtual IDisplayClusterViewportManager* GetViewportManager() const = 0;` — @return - Current viewport manager from root actor
- L217 _public prototype_ `virtual TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> CreateMeshComponent() const = 0;` — @return - new mesh component object
- L222 _public prototype_ `virtual TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> GetOrCreateCachedTexture(const FString& InUniqueTextureName) const = 0;` — Get or create a cached texture with unique name
- L227 _public prototype_ `virtual IDisplayClusterGUILayerController& GetGuiLayerController() const = 0;` — Returns GUI layer controller interface

#### struct `IDisplayClusterRenderManager::FDisplayClusterPPInfo`  
`struct FDisplayClusterPPInfo`  
_L35-44_
- desc: Post-process operation wrapper
- L37 _public function_ `FDisplayClusterPPInfo(TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe>& InOperation, int32 InPriority) : Operation(InOperation) , Priority(InPriority)`
- L42 _public member_ `TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe> Operation;`
- L43 _public member_ `int32 Priority;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Monitoring/IDisplayClusterVblankMonitor.h` (Public)


#### class `IDisplayClusterVblankMonitor`  
`class IDisplayClusterVblankMonitor`  
_L11-34_
- desc: V-blank monitor interface
- L14 _public prototype_ `virtual ~IDisplayClusterVblankMonitor() = default;`
- L18 _public prototype_ `virtual bool StartMonitoring() = 0;` — Start monitoring
- L21 _public prototype_ `virtual bool StopMonitoring() = 0;` — Stop monitoring
- L24 _public prototype_ `virtual bool IsMonitoring() = 0;` — Returns true if currently monitoring
- L27 _public prototype_ `virtual bool IsVblankTimeDataAvailable() = 0;` — Returns true if last and next expected V-blank timestamps are known
- L30 _public prototype_ `virtual double GetLastVblankTime() = 0;` — Returns last V-blank timestamp
- L33 _public prototype_ `virtual double GetNextVblankTime() = 0;` — Returns next expected V-blank timestamp

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/PostProcess/IDisplayClusterPostProcess.h` (Public)


#### class `IDisplayClusterPostProcess`  
`class IDisplayClusterPostProcess`  
_L19-175_
- desc: nDisplay post-process interface
- L22 _public prototype_ `virtual ~IDisplayClusterPostProcess() = default;`
- L28 _public prototype_ `virtual const FString& GetId() const = 0;` — Return postprocess name
- L33 _public prototype_ `virtual int32 GetOrder() const = 0;` — Return postprocess order
- L38 _public prototype_ `virtual const FString& GetType() const = 0;` — Return postprocess type
- L43 _public prototype_ `virtual const TMap<FString, FString>& GetParameters() const = 0;` — Return postprocess configuration
- L48 _public function_ `virtual void Tick()` — Update postprocess internal data from game thread
- L58 _public prototype_ `virtual bool IsConfigurationChanged(const struct FDisplayClusterConfigurationPostprocess* InConfigurationPostprocess) const = 0;` — Check postprocess settings changes @param InConfigurationProjectionPolicy - new settings @return - True if found changes
- L64 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewportManager* InViewportManager) = 0;` — Called each time a new game level starts
- L70 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewportManager* InViewportManager) = 0;` — Called when current level is going to be closed (i.e. before loading a new map)
- L76 _public function_ `virtual void HandleSetupNewFrame(IDisplayClusterViewportManager* InViewportManager)` — Called each time a new frame setup
- L83 _public function_ `virtual void HandleBeginNewFrame(IDisplayClusterViewportManager* InViewportManager, FDisplayClusterRenderFrame& InOutRenderFrame)` — Called each time a new frame begin
- L90 _public function_ `virtual void HandleRenderFrameSetup_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy)` — Called each time a render thread multi-viewport composing begin
- L97 _public function_ `virtual void HandleBeginUpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy)` — Called each time a render thread before UpdateFrameResources()
- L103 _public function_ `virtual void HandleUpdateFrameResourcesAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy)` — Called every time the render thread runs after the entire warpblend has completed.
- L110 _public function_ `virtual void HandleEndUpdateFrameResources_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* InViewportManagerProxy)` — Called each time a render thread after UpdateFrameResources()
- L119 _public function_ `virtual bool IsPostProcessViewBeforeWarpBlendRequired() const` — Returns if an interface implementation processes each view region before warp&blend the corresponded function will be called once per viewport @return - true if required
- L129 _public function_ `virtual void PerformPostProcessViewBeforeWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* ViewportProxy) const` — PP operation on a view region before warp&blend (if available for the current projection policy) the corresponded function will be called once per viewport @param RHICmdList - RHI command list @param ViewportProxy - viewport proxy interface
- L138 _public function_ `virtual bool IsPostProcessViewAfterWarpBlendRequired() const` — Returns if an interface implementation processes each view region after warp&blend the corresponded function will be called once per viewport @return - true if required
- L148 _public function_ `virtual void PerformPostProcessViewAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* ViewportProxy) const` — PP operation on a view region after warp&blend (if available for the current projection policy) the corresponded function will be called once per viewport @param RHICmdList - RHI command list @param ViewportProxy - viewport proxy interface
- L156 _public function_ `virtual bool IsPostProcessFrameAfterWarpBlendRequired() const` — Returns if an interface implementation processes output frames after warp&blend @return - true if required
- L164 _public function_ `virtual bool ShouldUseAdditionalFrameTargetableResource() const` — Request additional frame targetable resource from viewport manager @return - true if resource required
- L173 _public function_ `virtual void PerformPostProcessFrameAfterWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const TArray<FRHITexture*>* InFrameTargets = nullptr, const TArray<FRHITexture*>* InAdditionalFrameTargets = nullptr) const` — PP operation on a frame region after warp&blend @param RHICmdList - RHI command list @param FrameTargets - Frame textures array (1 for mono, 2 for stereo)

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/PostProcess/IDisplayClusterPostProcessFactory.h` (Public)


#### class `IDisplayClusterPostProcessFactory`  
`class IDisplayClusterPostProcessFactory`  
_L13-45_
- desc: nDisplay output post process factory interface
- L16 _public prototype_ `virtual ~IDisplayClusterPostProcessFactory() = default;`
- L27 _public prototype_ `virtual TSharedPtr<IDisplayClusterPostProcess, ESPMode::ThreadSafe> Create(const FString& PostProcessId, const struct FDisplayClusterConfigurationPostprocess* InConfigurationPostProcess) = 0;` — Creates a output post process instance @param PostProcessPolicyId - ID of a postprocess @param InConfigurationPostProcess - postprocess configuration @return - Post process instance
- L41 _public function_ `virtual bool CanBeCreated(const FDisplayClusterConfigurationPostprocess* InConfigurationPostProcess) const` — Special rules for creating a PP instance. Note: This function must be called before Create() on the nDisplay side. (useful to avoid unnecessary nDisplay log messages). For example, some postprocess types may use an instance as a singleton. In this case, Create() returns nullptr if the PP instance already exists, and as a result nDisplay issues an error message to the log, and then avoids creating this PP in the future. @param InConfigurationPostProcess - postprocess configuration @return true if a postprocess with this type can be created at this time.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Presentation/IDisplayClusterPresentation.h` (Public)


#### class `IDisplayClusterPresentation`  
`class IDisplayClusterPresentation`  
_L11-15_
- desc: Public display cluster presentation interface
- L14 _public prototype_ `virtual ~IDisplayClusterPresentation() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Projection/IDisplayClusterProjectionPolicy.h` (Public)


#### enum `EDisplayClusterProjectionPolicyFlags`  
`enum class EDisplayClusterProjectionPolicyFlags : uint8`  
_L22-76_
- desc: The type of media usage for the viewport.
- L25 _public enumerator_ `None = 0` — No flags
- L50 _public enumerator_ `UseEyeTracking = 1 << 0` — This projection policy use eye tracking (ViewPoint). This means that the InOutViewLocation and InOutViewRotation arguments in CalculateView() will contain the position of the viewpoint in world space, not the camera. Camera position is the value passed from IStereoRenderingDevice. This value is usually based on the active engine camera, which can be overridden in ISceneViewExtension::SetupViewPoint(). (see FDisplayClusterViewportManagerViewPointExtension::SetupViewPoint()) Most nDisplay projection policies (simple, mesh, easyblend, etc.) ignore this camera position and use their own values or DCRA components to compute the view. In this case, this flag replaces the IDisplayClusterProjectionPolicy::CalculateView() input arguments with the position of the of the DCRA ViewPoint component instead of the camera position. And the projection policy may not implement this logic. (see IDisplayClusterViewport::GetViewPointCameraEye()) Note: On the nDisplay side, the camera position can already be overridden using the ViewPoint position for some cases: UDisplayClusterCameraComponent::GetDesiredView() -> GetTargetCameraDesiredViewInternal() -> IsViewPointOverrideCameraPosition()
- L67 _public enumerator_ `UseLocalSpace = 1 << 1` — Projection policies can use local space and custom geometric units. Therefore, InOutViewLocation and InOutViewRotation must be converted from world space to the projection policy space and back again. The projection policy space is formed from the Origin component and scaling units. see GetOriginComponent(), GetGeometryToMeters(), GetOriginLocationOffsetInGeometryUnits(). This conversion will look like this: World -> ProjectionPolicy ScaleWorldToGeometry = GeometryToMeters / WorldToMeters PrjPolicyLocation = OriginToWorld.InverseTransformPosition(WorldSpaceLocation) * ScaleWorldToGeometry PrjPolicyRotation = OriginToWorld.InverseTransformRotation(WorldSpaceRotation) and vice versa.
- L75 _public enumerator_ `EnableFollowCameraFeature = 1 << 2` — This projection policy supports "Follow Camera" feature. To support this feature, the projection policy must return an output ViewLocation in the DCRA zone. Usually these values are calculated based on objects such as these: ViewPoint component, ICVFXCamera component, CineCamera actor referenced by ICVFXCamera, etc.

#### class `IDisplayClusterProjectionPolicy`  
`class IDisplayClusterProjectionPolicy`  
_L82-600_
- desc: nDisplay projection policy
- L85 _public prototype_ `virtual ~IDisplayClusterProjectionPolicy() = default;`
- L91 _public prototype_ `virtual const FString& GetId() const = 0;` — Return projection policy instance ID
- L96 _public prototype_ `virtual const FString& GetType() const = 0;` — Return projection policy type
- L101 _public prototype_ `virtual const TMap<FString, FString>& GetParameters() const = 0;` — Return projection policy configuration
- L108 _public function_ `virtual USceneComponent* const GetOriginComponent() const` — Return Origin point component used by this viewport This component is used to convert from the local DCRA space to the local projection policy space, which contains the calibrated geometry data used for the warp.
- L116 _public function_ `virtual UCameraComponent* GetCameraComponent() const` — Returns the camera component driving this projection policy, or nullptr if the policy does not use one.
- L128 _public function_ `virtual float GetGeometryToMeters(const IDisplayClusterViewport* InViewport, const float InWorldToMeters) const` — If the projection policy uses a custom scale internally, this function returns that value. The value means how many geometry units are in one meter. @param InViewport      - (in) a owner viewport @param InWorldToMeters - (in) UE world units per meter
- L144 _public function_ `virtual FVector GetOriginLocationOffsetInGeometryUnits(const IDisplayClusterViewport* InViewport) const` — Returns Origin's location in geometry units. The Origin component must be configured in UE units, but the calibration tools use their own units. Therefore, the user must perform calculations to correctly set the location of the Origin component within the UE. Typically, this approach leads to mistakes in the DCRA setup. To avoid this, the projection policy can receive the Origin Location parameter in geometric units. This function returns the value of this parameter. @param InViewport - (in) a owner viewport
- L154 _public function_ `virtual void UpdateProxyData(IDisplayClusterViewport* InViewport)` — Send projection policy game thread data to render thread proxy called once per frame from FDisplayClusterViewportManager::FinalizeNewFrame
- L162 _public function_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport)` — Called each time a new game level starts @param InViewport - a owner viewport
- L172 _public function_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport)` — Called when current level is going to be closed (i.e. before loading a new map) @param InViewport - a owner viewport
- L180 _public function_ `virtual void PostUpdateBaseConfiguration(IDisplayClusterViewport* InViewport) const` — Called after the base configuration is completed, but before the ICVFX @param InViewport - a owner viewport
- L189 _public function_ `virtual void BeginUpdateFrameContexts(IDisplayClusterViewport* InViewport) const` — Called before FDisplayClusterViewport::UpdateFrameContexts() From this function, the policy can override any viewport settings (custom overscan, etc). @param InViewport - a owner viewport
- L197 _public function_ `virtual void EndUpdateFrameContexts(IDisplayClusterViewport* InViewport) const` — Called after FDisplayClusterViewport::UpdateFrameContexts() @param InViewport - a owner viewport
- L205 _public function_ `virtual void SetWarpPolicy(IDisplayClusterWarpPolicy* InWarpPolicy)` — Set warp policy for this projection @param InWarpPolicy - the warp policy instance
- L211 _public function_ `virtual IDisplayClusterWarpPolicy* GetWarpPolicy() const` — Get warp policy
- L219 _public function_ `virtual IDisplayClusterWarpPolicy* GetWarpPolicy_RenderThread() const` — Get warp policy on rendering thread
- L225 _public function_ `virtual bool ShouldUseAdditionalTargetableResource(const IDisplayClusterViewport* InViewport) const` — Handle request for additional render targetable resource inside viewport api for projection policy
- L236 _public function_ `virtual bool ShouldUseSourceTextureWithMips(const IDisplayClusterViewport* InViewport) const` — Returns true if the policy supports input mip-textures. Use a mip texture for smoother deformation on curved surfaces. @return - true, if mip-texture is supported by the policy implementation
- L245 _public function_ `virtual bool ShouldSupportICVFX(const IDisplayClusterViewport* InViewport) const` — Returns true if this policy supports ICVFX rendering @param InViewport - a owner viewport
- L252 _public function_ `virtual bool IsCameraProjectionVisible(const FRotator& InViewRotation, const FVector& InViewLocation, const FMatrix& InProjectionMatrix)` — Return true, if camera projection visible for this viewport geometry ICVFX Performance : if camera frame not visible on this node, disable render for this camera
- L264 _public prototype_ `virtual bool IsConfigurationChanged(const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) const = 0;` — Check projection policy settings changes @param InConfigurationProjectionPolicy - new settings @return - True if found changes
- L273 _public function_ `virtual void SetupProjectionViewPoint(IDisplayClusterViewport* InViewport, const float InDeltaTime, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr)` — Override view from this projection policy @param InViewport                 - a owner viewport @param InDeltaTime                - delta time in current frame @param InOutViewInfo              - ViewInfo data @param OutCustomNearClippingPlane - Custom NCP, or a value less than zero if not defined.
- L277 _public function_ `virtual bool ShouldUseViewPointComponentPostProcesses(IDisplayClusterViewport* InViewport) const` — Returns true if this projection policy should use post-processes from the ViewPoint component.
- L286 _public function_ `virtual void UpdatePostProcessSettings(IDisplayClusterViewport* InViewport)` — Projection policy can override PP @param InViewport - a owner viewport
- L296 _public function_ `virtual void ApplyClippingPlanesOverrides(const IDisplayClusterViewport* InViewport, float& InOutNCP, float& InOutFCP) const` — Projection policy can modify the clipping planes. @param InViewport - (in) a owner viewport @param InOutNCP   - (in, out) Near clipping plane @param InOutFCP   - (in, out) Far clipping plane
- L305 _public function_ `virtual EDisplayClusterProjectionPolicyFlags GetProjectionPolicyFlags(const IDisplayClusterViewport* InViewport, const uint32 InContextNum) const` — Return Projection policy flags @param InViewport   - (in) a owner viewport @param InContextNum - Index of view that is being processed for this viewport
- L323 _public prototype_ `virtual bool CalculateView(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP) = 0;` — Calculate view projection data @param InViewport        - a owner viewport @param InContextNum      - Index of view that is being processed for this viewport @param InOutViewLocation - (in/out) View location with ViewOffset (i.e. left eye pre-computed location) @param InOutViewRotation - (in/out) View rotation @param ViewOffset        - Offset applied ot a camera location that gives us InOutViewLocation (i.e. right offset in world to compute right eye location) @param WorldToMeters     - Current world scale (units (cm) in meter) @param NCP               - Distance to the near clipping plane @param FCP               - Distance to the far  clipping plane @return - True if success
- L333 _public prototype_ `virtual bool GetProjectionMatrix(IDisplayClusterViewport* InViewport, const uint32 InContextNum, FMatrix& OutPrjMatrix) = 0;` — Gets projection matrix @param InViewport   - a owner viewport @param InContextNum - Index of view that is being processed for this viewport @param OutPrjMatrix - (out) projection matrix @return - True if success
- L342 _public function_ `virtual bool IsFrustumRotatedToFitContextSize(IDisplayClusterViewport* InViewport, const uint32 InContextNum)` — Returns true if the frustum has been rotated to fit the context size. @param InViewport   - a owner viewport @param InContextNum - Index of view that is being processed for this viewport @return true is success.
- L354 _public function_ `virtual bool IsFrustumRotatedToFitContextSize_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy, const uint32 InContextNum)` — Returns true if the frustum has been rotated to fit the context size. @param InViewportProxy - The owning viewport proxy @param InContextNum - Index of view that is being processed for this viewport @return True if succeeded.
- L364 _public function_ `virtual bool IsWarpBlendSupported(const IDisplayClusterViewport* InViewport) const` — Returns if a policy provides warp&blend feature @return - True if warp&blend operations are supported by the policy implementation
- L375 _public function_ `virtual bool IsWarpBlendSupported_RenderThread(const IDisplayClusterViewportProxy* InViewportProxy) const` — Returns if a policy provides warp&blend feature ( @return - True if warp&blend operations are supported by the policy implementation
- L388 _public function_ `virtual bool GetCustomRenderTargetSize(const IDisplayClusterViewport* InViewport, FIntPoint& OutRenderTargetSize) const` — This function can override the size of the RenderTarget texture for the viewport. @param InViewport          - viewport to override RTT size. @param OutRenderTargetSize - (out) the desired RTT size. @return is true if the RTT size should be overridden.
- L402 _public function_ `virtual bool ShouldUseAnySizeScaleForRenderTarget(const IDisplayClusterViewport* InViewport) const` — This function controls the RTT size multipliers - if false is returned, all modifiers should be ignored. Here is the list of ignored modifiers: RenderTargetAdaptRatio, RenderTargetRatio, ClusterRenderTargetRatioMult, ClusterICVFXOuterViewportRenderTargetRatioMult, ClusterICVFXInnerViewportRenderTargetRatioMult @param InViewport - the DC viewport.
- L415 _public function_ `virtual void BeginWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy)` — Initializing the projection policy logic for the current frame before applying warp blending. Have to be called only if IsWarpBlendSupported_RenderThread() returns true @param RHICmdList      - RHI commands @param InViewportProxy - viewport proxy
- L426 _public function_ `virtual void ApplyWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy)` — Performs Warp and Blend on the rendering thread Have to be called only if IsWarpBlendSupported_RenderThread() returns true @param RHICmdList      - RHI commands @param InViewportProxy - viewport proxy
- L439 _public function_ `virtual void EndWarpBlend_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy)` — Completing the projection policy logic for the current frame after applying warp blending. Have to be called only if IsWarpBlendSupported_RenderThread() returns true @param ViewIdx      - Index of view that is being processed for this viewport @param RHICmdList   - RHI commands @param SrcTexture   - Source texture @param ViewportRect - Region of the SrcTexture to perform warp&blend operations
- L449 _public function_ `virtual bool GetWarpBlendInterface(TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe>& OutWarpBlendInterface) const` — Return warpblend interface of this policy @param OutWarpBlendInterface - output interface ref @return - true if output interface valid
- L461 _public function_ `virtual bool GetWarpBlendInterface_RenderThread(TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe>& OutWarpBlendInterfaceProxy) const` — Return warpblend interface proxy of this policy @param OutWarpBlendInterfaceProxy - output interface ref @return - true if output interface valid
- L476 _public function_ `virtual bool ResolveInternalRenderTargetResource_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* InViewportProxy, const IDisplayClusterViewportProxy* InSourceViewportProxy)` — Override copying 'InternalRenderTargetResource' to 'InputShaderResource'. The same behavior as for function bellow  is expected: ResolveResources_RenderThread(RHICmdList, InSourceViewportProxy, InSrcResourceType, InDstResourceType); @param InViewportProxy       - This ViewportProxy will get the result @param InSourceViewportProxy - This ViewportProxy will provide the input resource @return - true, if copying is overridden.
- L487 _public function_ `virtual bool HasPreviewMesh(IDisplayClusterViewport* InViewport)` — Ask projection policy instance if it has any mesh based preview @param InViewport - a owner viewport @return - True if mesh based preview is available
- L501 _public function_ `virtual UMeshComponent* GetOrCreatePreviewMeshComponent(IDisplayClusterViewport* InViewport, bool& bOutIsRootActorComponent)` — Build preview mesh This MeshComponent cannot be moved freely. This MeshComponent is attached to the geometry from the real world via Origin. When the screen geometry in the real world changes position, the position of this component must also be changed. @param InViewport - Projection specific parameters. @param bOutIsRootActorComponent - return true, if used custom root actor component. return false, if created unique temporary component
- L511 _public function_ `virtual USceneComponent* const GetPreviewMeshOriginComponent(IDisplayClusterViewport* InViewport) const` — Return Origin point component used by preview mesh @param InViewport - a owner viewport
- L522 _public function_ `virtual bool HasPreviewEditableMesh(IDisplayClusterViewport* InViewport)` — Ask projection policy instance if it has any Editable mesh based preview @param InViewport - a owner viewport @return - True if mesh based preview is available
- L533 _public function_ `virtual UMeshComponent* GetOrCreatePreviewEditableMeshComponent(IDisplayClusterViewport* InViewport)` — Build preview Editable mesh This MeshComponent is a copy of the preview mesh and can be moved freely with the UI visualization. @param InViewport - a owner viewport
- L543 _public function_ `virtual USceneComponent* const GetPreviewEditableMeshOriginComponent(IDisplayClusterViewport* InViewport) const` — Return Origin point component used by preview Editable mesh @param InViewport - a owner viewport
- L552 _public function_ `virtual bool ShouldSupportICVFX() const` — `UE_DEPRECATED(5.3, "This function has been deprecated. Please use 'ShouldSupportICVFX(IDisplayClusterViewport*)'.")` — This policy can support ICVFX rendering
- L565 _public function_ `virtual bool HasPreviewMesh()` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'HasPreviewMesh(IDisplayClusterViewport*)'.")` — Ask projection policy instance if it has any mesh based preview @return - True if mesh based preview is available
- L576 _public function_ `virtual bool IsWarpBlendSupported()` — `UE_DEPRECATED(5.6, "This function has been deprecated. Please use 'IsWarpBlendSupported(IDisplayClusterViewport*) or IsWarpBlendSupported_RenderThread(IDisplayClusterViewportProxy*)'.")` — Returns if a policy provides warp&blend feature @return - True if warp&blend operations are supported by the policy implementation
- L583 _public function_ `virtual bool ShouldUseAdditionalTargetableResource() const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Please use 'ShouldUseAdditionalTargetableResource(IDisplayClusterViewport*).")` — Handle request for additional render targetable resource inside viewport api for projection policy
- L595 _public function_ `virtual bool ShouldUseSourceTextureWithMips() const` — `UE_DEPRECATED(5.6, "This function has been deprecated. Please use 'ShouldUseSourceTextureWithMips(IDisplayClusterViewport*).")` — Returns true if the policy supports input mip-textures. Use a mip texture for smoother deformation on curved surfaces. @return - true, if mip-texture is supported by the policy implementation

#### Free symbols / members of external scopes

- L77 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterProjectionPolicyFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Projection/IDisplayClusterProjectionPolicyFactory.h` (Public)


#### class `IDisplayClusterProjectionPolicyFactory`  
`class IDisplayClusterProjectionPolicyFactory`  
_L13-30_
- desc: nDisplay projection policy factory interface
- L16 _public prototype_ `virtual ~IDisplayClusterProjectionPolicyFactory() = default;`
- L28 _public prototype_ `virtual TSharedPtr<IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe> Create(const FString& ProjectionPolicyId, const struct FDisplayClusterConfigurationProjection* InConfigurationProjectionPolicy) = 0;` — Creates a projection policy instance @param PolicyType - Projection policy type, same as specified on registration (useful if the same factory is registered for multiple projection types) @param ProjectionPolicyId - ID of a policy @param InConfigurationProjectionPolicy - policy configuration @return - Projection policy instance

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Synchronization/IDisplayClusterRenderSyncPolicy.h` (Public)


#### class `IDisplayClusterRenderSyncPolicy`  
`class IDisplayClusterRenderSyncPolicy`  
_L11-60_
- desc: Public render synchronization policy interface
- L14 _public prototype_ `virtual ~IDisplayClusterRenderSyncPolicy() = default;`
- L22 _public function_ `virtual bool Initialize()` — Perform any non-constructor initialization if needed @return - true if initialized successfully
- L30 _public prototype_ `virtual FName GetName() const = 0;` — Returns the name of the sync policy
- L39 _public prototype_ `virtual bool SynchronizeClusterRendering(FRHIViewport* ViewportRHI, int32& InOutSyncInterval) = 0;` — Synchronizes rendering threads in a cluster (optionally presents a frame) @param InOutSyncInterval - Sync interval (VSync) @return - true if we a caller needs to present frame by its own
- L45 _public function_ `virtual bool IsWaitForVBlankFeatureSupported()` — Returns true if policy instance support "WaitForVBlank" feature that is used on the higher levels
- L56 _public function_ `virtual bool WaitForVBlank(FRHIViewport* Viewport)` — Wait unless the next V-blank occurs. This function may be called after IsWaitForVBlankFeatureSupported returned true. Otherwise it will never be called. @return - true if v-blank awaiting was successfull

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Synchronization/IDisplayClusterRenderSyncPolicyFactory.h` (Public)


#### class `IDisplayClusterRenderSyncPolicyFactory`  
`class IDisplayClusterRenderSyncPolicyFactory`  
_L13-27_
- desc: nDisplay rendering synchronization policy factory interface
- L16 _public prototype_ `virtual ~IDisplayClusterRenderSyncPolicyFactory() = default;`
- L26 _public prototype_ `virtual TSharedPtr<IDisplayClusterRenderSyncPolicy> Create(const FString& InPolicyType, const TMap<FString, FString>& Parameters) = 0;` — Creates a rendering device instance @param InPolicyType - Synchronization policy type that has been specified on registering the factory (may be useful if the same factory is responsible for multiple policies types) @return - rendering device

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Upscaler/DisplayClusterUpscalerSettings.h` (Public)


#### enum `EDisplayClusterUpscalerAntiAliasingMethod`  
`enum class EDisplayClusterUpscalerAntiAliasingMethod : uint8`  
_L10-30_
- desc: Determines AntiAliasing method.
- L13 _public enumerator_ `Default = 0` — Use default AA from the project settings
- L16 _public enumerator_ `None` — Disable AA
- L19 _public enumerator_ `FXAA` — Fast Approximate Anti-Aliasing (FXAA)
- L23 _public enumerator_ `MSAA` — Multisample Anti-Aliasing (MSAA) Only supported with forward shading.  MSAA sample count is controlled by r.MSAACount.
- L26 _public enumerator_ `TAA` — Temporal Anti-Aliasing (TAA)
- L29 _public enumerator_ `TSR` — Temporal Super-Resolution (TSR)

#### class `FDisplayClusterUpscalerSettings`  
`class FDisplayClusterUpscalerSettings`  
_L35-53_
- desc: nDisplay Upscaler settings
- L38 _public prototype_ `FDisplayClusterUpscalerSettings() = default;`
- L42 _public member_ `EDisplayClusterUpscalerAntiAliasingMethod AntiAliasingMethod = EDisplayClusterUpscalerAntiAliasingMethod::Default;` — Determines AntiAliasing method.
- L45 _public member_ `FName CustomUpscalerName;` — Custom custom upscaler name
- L48 _public member_ `FInstancedPropertyBag CustomUpscalerSettings;` — Custom upscaler settings
- L52 _public member_ `bool bIsActive = true;` — parameters for the Functor logic(IUpscalerModularFeature::AddSceneViewExtensionIsActiveFunctor()). Enable to use upscaler ViewExtension

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewportFrameData.h` (Public)


#### struct `FDisplayClusterViewportFrameData`  
`struct FDisplayClusterViewportFrameData`  
_L12-38_
- desc: Per-frame snapshot of a viewport's render state: eye contexts and cached camera view info.
- L15 _public function_ `inline void Reset()` — Reset to an empty/uninitialized state, ready to be populated for the next frame.
- L23 _public function_ `inline bool IsEmpty() const` — Returns true if no contexts have been populated for this frame yet.
- L30 _public member_ `uint32 FrameNumber = 0;` — Frame number this snapshot was captured on.
- L34 _public member_ `mutable TArray<FDisplayClusterViewport_Context> Contexts;` — Per-eye render contexts (mono, stereo left, stereo right). mutable: updated by the render thread through the const IDisplayClusterViewportProxy interface.
- L37 _public member_ `TOptional<FMinimalViewInfo> CachedCameraViewInfo;` — Cached camera view info for FDisplayClusterViewport::GetCameraViewPoint().

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewportPreview_Enums.h` (Public)


#### enum `EDisplayClusterViewportPreviewFlags`  
`enum class EDisplayClusterViewportPreviewFlags : uint8`  
_L10-25_
- desc: Runtime configuration from DCRA.
- L12 _public enumerator_ `None = 0`
- L15 _public enumerator_ `HasChangedPreviewRTT = 1 << 0` — the RTT has been changed
- L18 _public enumerator_ `HasValidPreviewRTT = 1 << 1` — This viewport has a valid preview texture.
- L21 _public enumerator_ `HasChangedPreviewMeshMaterialInstance = 1 << 2` — Preview mesh material instance has been changed.
- L24 _public enumerator_ `HasChangedPreviewEditableMeshMaterialInstance = 1 << 3` — Preview editable mesh material instance has been changed.

#### Free symbols / members of external scopes

- L26 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportPreviewFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewportProxy_Context.h` (Public)


#### struct `FDisplayClusterViewportProxy_Context`  
`struct FDisplayClusterViewportProxy_Context`  
_L10-17_
- desc: The viewport proxy context (rendering thread data)
- L13 _public member_ `uint32 ContextNum = 0;` — The number of context
- L16 _public member_ `FString ViewFamilyProfileDescription;` — Profile description from ViewFamily

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_CameraDepthOfField.h` (Public)


#### class `FDisplayClusterViewport_CameraDepthOfField`  
`class FDisplayClusterViewport_CameraDepthOfField`  
_L14-39_
- desc: Settings for the camera depth of field blur.
- L18 _public prototype_ `void SetupSceneView(FSceneView& InOutView) const;` — Sets the appropriate depth of field settings in the scene view
- L21 _public function_ `void BeginUpdateSettings()` — At the beginning of each frame, all settings must be restored to default.
- L29 _public member_ `bool bEnableDepthOfFieldCompensation = false;` — Indicates whether depth of field correction is enabled for the ICVFX camera
- L32 _public member_ `float DistanceToWall = 0.0;` — The distance from the ICVFX camera to the wall it is shooting against
- L35 _public member_ `float DistanceToWallOffset = 0.0;` — An offset applied to the distance to wall value
- L38 _public member_ `TWeakObjectPtr<UTexture2D> CompensationLUT;` — Look-up texture that encodes the specific amount of compensation used for each combination of wall distance and object distance

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_CameraMotionBlur.h` (Public)


#### enum `EDisplayClusterViewport_CameraMotionBlur`  
`enum class EDisplayClusterViewport_CameraMotionBlur : uint8`  
_L10-16_
- desc: Camera motion blur mode.
- L12 _public enumerator_ `Undefined = 0`
- L13 _public enumerator_ `Off`
- L14 _public enumerator_ `On`
- L15 _public enumerator_ `Override`

#### struct `FDisplayClusterViewport_CameraMotionBlur`  
`struct FDisplayClusterViewport_CameraMotionBlur`  
_L21-29_
- desc: Settings for the CameraMotion blur.
- L23 _public member_ `EDisplayClusterViewport_CameraMotionBlur Mode = EDisplayClusterViewport_CameraMotionBlur::Undefined;`
- L25 _public member_ `FVector CameraLocation = FVector::ZeroVector;`
- L26 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;`
- L28 _public member_ `float TranslationScale = 1.f;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_Context.h` (Public)


#### class `FDisplayClusterViewport_Context`  
`class FDisplayClusterViewport_Context`  
_L15-237_
- desc: Viewport context with cahched data and states
- L18 _public function_ `FDisplayClusterViewport_Context(const uint32 InContextNum, const EStereoscopicPass InStereoscopicPass, const int32 InStereoViewIndex) : ContextNum(InContextNum) , StereoscopicPass(InStereoscopicPass) , StereoViewIndex(InStereoViewIndex)`
- L25 _public function_ `inline const FMatrix& GetRenderProjectionMatrix() const` — Returns the effective projection matrix for rendering.
- L33 _public function_ `inline const FVector4& GetRenderNearPlaneExtents() const` — Returns the effective near-plane frustum extents for rendering (X=Left, Y=Right, Z=Top, W=Bottom), in world units.
- L43 _public function_ `inline const FIntRect& GetViewportContentRect() const` — Returns the viewport content rect within the render target, excluding overscan padding.
- L56 _public member_ `uint8 bValidData : 1 = 0;` — True if this ViewData have a valid data.
- L59 _public member_ `uint8 bCalculated : 1 = 0;` — Is this data have been calculated.
- L63 _public member_ `uint8 bOverrideCrossGPUTransfer : 1 = 0;` — Enables nDisplay's native implementation of cross-GPU transfer. This disables cross-GPU transfer by default for nDisplay viewports in FSceneViewFamily structure.
- L66 _public member_ `uint8 bDisableRender : 1 = 0;` — Disable render for this viewport (Overlay)
- L70 _public member_ `const uint32 ContextNum;` — Index of context (eye #)
- L73 _public member_ `EStereoscopicPass StereoscopicPass;` — References to IStereoRendering
- L74 _public member_ `int32 StereoViewIndex;`
- L77 _public member_ `TOptional<FMinimalViewInfo> CachedViewPoint;` — Cached ViewInfo
- L123 _public member_ `FCachedViewData ViewData;` — View data for this context
- L148 _public member_ `FCachedProjectionData ProjectionData;` — Cached projection values This values updated from function FDisplayClusterViewport::CalculateProjectionMatrix()
- L151 _public member_ `float WorldToMeters = 100.f;` — UE scale: how many UE Units in one meter
- L154 _public member_ `float GeometryToMeters = 100.f;` — Geometry scale: how many Geometry Units in one meter
- L158 _public member_ `FTransform OriginToWorld = FTransform::Identity;` — Origin component to world transform This component is defined in the projection policy
- L161 _public member_ `FTransform RootActorToWorld = FTransform::Identity;` — RootActor to world transform
- L164 _public member_ `FVector ViewLocation = FVector::ZeroVector;` — View location used in world space
- L167 _public member_ `FRotator ViewRotation = FRotator::ZeroRotator;` — View rotation used in world space
- L170 _public member_ `FMatrix ProjectionMatrix = FMatrix::Identity;` — Projection Matrix
- L173 _public member_ `FMatrix OverscanProjectionMatrix = FMatrix::Identity;` — Overscan Projection Matrix (internal use)
- L184 _public member_ `} DepthOfField;`
- L187 _public member_ `int32 GPUIndex = INDEX_NONE;` — GPU index for this context render target
- L190 _public member_ `FIntRect OverscanInnerRenderTargetRect;` — Inner rectangle inside RenderTargetRect
- L193 _public member_ `FIntRect RenderTargetRect;` — Location and size on a render target texture
- L196 _public member_ `FIntPoint ContextSize;` — Context size
- L199 _public member_ `FIntRect FrameTargetRect;` — Location and size on a frame target texture
- L202 _public member_ `FIntRect TileDestRect;` — Tile location and size in the source viewport
- L205 _public member_ `float CustomBufferRatio = 1;` — Buffer ratio
- L208 _public member_ `int32 NumMips = 1;` — Mips number for additional MipsShader resources
- L236 _public member_ `FRenderThreadData RenderThreadData;` — This data updated only on rendering thread

#### struct `FDisplayClusterViewport_Context::FCachedViewData`  
`struct FCachedViewData`  
_L79-120_
- L96 _public member_ `FVector CameraOrigin = FVector::ZeroVector;` — Camera location in the world space This value receives nDisplay from IStereoRenderingDevice
- L100 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — Camera rotation in the world space This value receives nDisplay from IStereoRenderingDevice
- L104 _public member_ `FVector EyeOrigin = FVector::ZeroVector;` — The eye location  in the world space This value is used as an argument to IDisplayClusterProjectionPolicy::CalculateView()
- L108 _public member_ `FRotator EyeRotation = FRotator::ZeroRotator;` — The eye rotation in the world space This value is used as an argument to IDisplayClusterProjectionPolicy::CalculateView()
- L112 _public member_ `FVector RenderCameraLocation = FVector::ZeroVector;` — Camera head (pivot) position in world space. Equals RenderLocation minus the stereo eye offset; identical to RenderLocation for mono rendering.
- L116 _public member_ `FVector RenderLocation = FVector::ZeroVector;` — Render eye position in world space; the actual view origin passed to the scene renderer. Differs from RenderCameraLocation by the stereo eye offset in stereo contexts.
- L119 _public member_ `FRotator RenderRotation = FRotator::ZeroRotator;` — View rotation in world space; shared by both the camera head and the render eye.

#### struct `FDisplayClusterViewport_Context::FCachedProjectionData`  
`struct FCachedProjectionData`  
_L126-144_
- desc: Cached projection data
- L128 _public member_ `bool bValid = false;`
- L131 _public member_ `bool bUseOverscan = false;` — Is overscan used
- L135 _public member_ `FVector4 ProjectionAngles;` — Near-plane frustum extents for rendering in world units. ( X=Left, Y=Right, Z=Top, W=Bottom )
- L139 _public member_ `FVector4 OverscanProjectionAngles;` — Near-plane frustum extents for rendering with overscan in world units. ( X=Left, Y=Right, Z=Top, W=Bottom )
- L142 _public member_ `double ZNear = 0.f;` — Clipping planes
- L143 _public member_ `double ZFar = 0.f;`

#### struct `FDisplayClusterViewport_Context::FDepthOfFieldSettings`  
`struct FDepthOfFieldSettings`  
_L176-184_
- desc: Additional data for the Depth of Field (DoF).
- L179 _public member_ `float SensorFocalLength = 0.f;` — Focal length of the Depth of Field effect camera in mm.
- L182 _public member_ `float SqueezeFactor = 1.f;` — This is the squeeze factor for the DOF, which emulates the properties of anamorphic lenses.

#### struct `FDisplayClusterViewport_Context::FRenderThreadData`  
`struct FRenderThreadData`  
_L213-233_
- desc: Viewport context data for rendering thread
- L215 _public function_ `FRenderThreadData() : EngineShowFlags(ESFIM_All0)`
- L220 _public member_ `int32 GPUIndex = INDEX_NONE;` — GPUIndex used to render this context.
- L223 _public member_ `float EngineDisplayGamma = 2.2f;` — Display gamma used to render this context
- L226 _public member_ `FEngineShowFlags EngineShowFlags;` — Engine flags used to render this context
- L229 _public member_ `FDisplayClusterViewport_EyeAdaptationData EyeAdaptationData;` — EyeAdaptation data
- L232 _public member_ `uint32 FrameNumber = 0;` — The value from FSceneViewFamily::FrameNumber

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_CustomFrustumSettings.h` (Public)


#### struct `FDisplayClusterViewport_CustomFrustumSettings`  
`struct FDisplayClusterViewport_CustomFrustumSettings : public FMarginSet`  
_L12-23_
- inherits: `FMarginSet`
- desc: Custom frustum settings of viewport
- L16 _public member_ `uint8 bEnabled : 1 = 0;` — Enable custom frustum
- L19 _public member_ `uint8 bAdaptResolution : 1 = 0;` — Enable adaptive resolution
- L22 _public member_ `EDisplayClusterViewport_FrustumUnit Unit = EDisplayClusterViewport_FrustumUnit::Pixels;` — Units type of values

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_Enums.h` (Public)


#### enum `EDisplayClusterViewportResourceType`  
`enum class EDisplayClusterViewportResourceType : uint8`  
_L10-91_
- desc: Types of DC viewport resources
- L13 _public enumerator_ `Unknown = 0` — Undefined resource type
- L18 _public enumerator_ `InternalRenderTargetEntireRectResource` — This RTT is used to render the scene for the viewport eye context to the specified area on this texture. The mGPU rendering with cross-GPU transfer can be used for this texture. This resource has an area that includes the overscan extension.
- L23 _public enumerator_ `InternalRenderTargetResource` — Same RTT texture resource, but with the final value of the inner area on the texture (after overscan, etc.).
- L33 _public enumerator_ `InputShaderResource` — Unique Viewport contexts shader resource. No regions used at this point The image source for this resource can be: 'InternalRenderTargetResource', 'OverrideTexture', 'OverrideViewport', etc. This is the entry point to the DC rendering pipeline
- L36 _public enumerator_ `MipsShaderResource` — Special resource with mips texture, generated from 'InputShaderResource' after postprocess
- L41 _public enumerator_ `AdditionalTargetableResource` — Additional targetable resource, used by logic (external warpblend, blur, etc) This resource is used as an additional RTT for 'InputShaderResource'. It contains different contents depending on the point in time: 'PostprocessRTT','ViewportOutputRemap','AfterWarpBlend' etc.
- L50 _public enumerator_ `BeforeWarpBlendTargetableResource` — The viewport texture before warpblend (InputShaderResource) This resource is used as the source image for the projection policy.
- L54 _public enumerator_ `AfterWarpBlendTargetableResource` — The viewport texture after warpblend (AdditionalTargetableResource or InputShaderResource). This resource is used as the output image in the projection policy.
- L63 _public enumerator_ `OutputTargetableResource` — This is the entry point into the output texture rendering.('OutputFrameTargetableResource' or 'OutputPreviewTargetableResource') The rendering time of this image in the DC rendering pipeline is right after warp&blend.
- L71 _public enumerator_ `OutputPreviewTargetableResource` — If DCRA uses a preview, this texture will be used instead of 'Frame' textures
- L86 _public enumerator_ `OutputFrameTargetableResource` — This texture contains the results of the DC rendering, and is copied directly to the backbuffer texture at the end of the frame. Each eye is in a separate texture.
- L90 _public enumerator_ `AdditionalFrameTargetableResource` — This resource is used as an additional RTT for 'OutputFrameTargetableResource'. It contains different contents depending on the point in time: 'FramePostprocessRTT','OutputRemap', etc.

#### enum `EDisplayClusterViewportCaptureMode`  
`enum class EDisplayClusterViewportCaptureMode : uint8`  
_L97-110_
- desc: Viewport capture mode This mode affects many viewport rendering settings.
- L100 _public enumerator_ `Default = 0` — Use current scene format, no alpha
- L103 _public enumerator_ `Chromakey` — use small BGRA 8bit texture with alpha for masking
- L106 _public enumerator_ `Lightcard` — use hi-res float texture with alpha for compisiting
- L109 _public enumerator_ `MoviePipeline` — Special hi-res mode for movie pipeline

#### enum `EDisplayClusterViewportOverrideMode`  
`enum class EDisplayClusterViewportOverrideMode : uint8`  
_L116-131_
- desc: Viewport can be overridden by another one. This mode determines how many resources will be overridden.
- L119 _public enumerator_ `None = 0` — Do not override this viewport from the other one (Render viewport; create all resources)
- L123 _public enumerator_ `InternalRTT` — Override internalRTT from the other viewport (Don't render this viewport; Don't create RTT resource) Useful for custom PP on the same InRTT. (OCIO per-viewport\node)
- L127 _public enumerator_ `InternalViewportResources` — Overrides only internal viewport resources The output RTT is not overridden and must use rendering.
- L130 _public enumerator_ `All` — Override all - clone viewport (Dont render; Don't create resources;)

#### enum `EDisplayClusterViewport_FrustumUnit`  
`enum class EDisplayClusterViewport_FrustumUnit: uint8`  
_L136-143_
- desc: Type of unit for frustum
- L139 _public enumerator_ `Pixels = 0` — 1 unit = 1 pixel
- L142 _public enumerator_ `Percent` — 1 unit = 1 per cent

#### enum `EDisplayClusterRootActorType`  
`enum class EDisplayClusterRootActorType : uint8`  
_L148-164_
- desc: Type of DCRA used by configuration
- L151 _public enumerator_ `Preview = 1 << 0` — This DCRA will be used to render previews. The meshes and preview materials are created at runtime.
- L155 _public enumerator_ `Scene = 1 << 1` — A reference to DCRA in the scene, used as a source for math calculations and references. Locations in the scene and math data are taken from this DCRA.
- L158 _public enumerator_ `Configuration = 1 << 2` — Reference to DCRA, used as a source of configuration data from DCRA and its components.
- L163 _public enumerator_ `Any = Preview | Scene | Configuration` — This value can only be used in very specific cases: For function GetRootActor() : Return any of the DCRAs that are not nullptr, in ascending order of type: Preview, Scene, Configuration. For function SetRootActor() : Sets all references to DRCA to the specified value.

#### enum `EDisplayClusterViewportMediaState`  
`enum class EDisplayClusterViewportMediaState : uint8`  
_L170-186_
- desc: The type of media usage for the viewport.
- L173 _public enumerator_ `None = 0` — This viewport does not use media.
- L176 _public enumerator_ `Capture = 1 << 0` — This viewport will be captured by a media device.
- L179 _public enumerator_ `CaptureLateOCIO = 1 << 1` — Custom OCIO transformation is expected on the receiving side
- L182 _public enumerator_ `Input = 1 << 2` — This viewport is overridden by a media device.
- L185 _public enumerator_ `InputLateOCIO = 1 << 3` — Custom OCIO transformation is expected on receiving

#### enum `EDisplayClusterViewportCameraPostProcessFlags`  
`enum class EDisplayClusterViewportCameraPostProcessFlags : uint8`  
_L192-223_
- desc: A set of flags defining the post-process parameters to be received from the camera.
- L195 _public enumerator_ `None = 0` — Ignore all post-processing from the camera.
- L199 _public enumerator_ `EnablePostProcess = 1 << 0` — Use the PP settings from the specified camera. (Supported by Camera, CineCamera and ICVFXCamera components).
- L203 _public enumerator_ `EnableDepthOfField = 1 << 1` — Enable the CineCamera DoF PP settings from the specified camera. (Supported by CineCamera and ICVFXCamera components).
- L207 _public enumerator_ `EnableNearClippingPlane = 1 << 2` — Use the custom NearClippingPlane value from the specified cine camera. (Supported by CineCamera and ICVFXCamera components).
- L211 _public enumerator_ `EnableICVFXColorGrading = 1 << 3` — Use the DC ColorGrading from the specified ICVFX camera. (Supported by ICVFXCamera component only).
- L215 _public enumerator_ `EnableICVFXMotionBlur = 1 << 4` — Use the DC Motion Blur settings from the specified ICVFX camera. (Supported by ICVFXCamera component only).
- L219 _public enumerator_ `EnableICVFXDepthOfFieldCompensation = 1 << 5` — Use the DC Depth-Of-Field settings from the specified ICVFX camera. (Supported by ICVFXCamera component only).
- L222 _public enumerator_ `All = 0xFF` — Apply all possible post-processing from the camera.

#### enum `EDisplayClusterViewportRenderingFlags`  
`enum class EDisplayClusterViewportRenderingFlags : uint8`  
_L229-236_
- desc: Rules for customizing nDisplay views and view families for the renderer.
- L232 _public enumerator_ `None = 0` — No flags
- L235 _public enumerator_ `StereoRendering = 1 << 0` — Stereo rendering: Change screen percentage method to raw output when doing dynamic resolution with VR if not using TAA upsample.

#### enum `EDisplayClusterViewportFlags`  
`enum class EDisplayClusterViewportFlags : uint8`  
_L242-266_
- desc: Viewport usage type flags.
- L245 _public enumerator_ `None = 0` — The standard viewport does not have any special flags.
- L248 _public enumerator_ `TileViewport = 1 << 0` — Tile viewport.
- L251 _public enumerator_ `ICVFX_InnerFrustum = 1 << 1` — ICVFX viewports.
- L252 _public enumerator_ `ICVFX_ChromaKey = 1 << 2`
- L253 _public enumerator_ `ICVFX_LightCard = 1 << 3`
- L254 _public enumerator_ `ICVFX_UVLightCard = 1 << 4`
- L257 _public enumerator_ `ICVFX_Modifier_RenderOverInnerFrustum = 1 << 5` — ICVFX render modifiers.
- L258 _public enumerator_ `ICVFX_Modifier_RenderUnderInnerFrustum = 1 << 6`
- L261 _public enumerator_ `ICVFX_AnyRole = ICVFX_InnerFrustum | ICVFX_ChromaKey | ICVFX_LightCard | ICVFX_UVLightCard` — Combined mask for any ICVFX viewport role (excludes modifiers).

#### Free symbols / members of external scopes

- L165 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterRootActorType);`
- L187 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportMediaState);`
- L224 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportCameraPostProcessFlags);`
- L237 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportRenderingFlags);`
- L267 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_EnumsICVFX.h` (Public)


#### enum `EDisplayClusterViewportICVFXFlags`  
`enum class EDisplayClusterViewportICVFXFlags : uint16`  
_L10-46_
- desc: Runtime configuration from DCRA.
- L12 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Enable = 1 << 0` — Allow to use ICVFX for this viewport (Must be supported by projection policy)
- L18 _public enumerator_ `DisableCamera = 1 << 1` — Disable incamera render to this viewport
- L21 _public enumerator_ `DisableChromakey = 1 << 2` — Disable chromakey render to this viewport
- L24 _public enumerator_ `DisableChromakeyMarkers = 1 << 3` — Disable chromakey markers render to this viewport
- L27 _public enumerator_ `DisableLightcard = 1 << 4` — Disable lightcard render to this viewport
- L30 _public enumerator_ `LightcardAlwaysUnder = 1 << 5` — lightcard render always under the InCamera
- L33 _public enumerator_ `LightcardAlwaysOver = 1 << 6` — lightcard render always over the InCamera
- L36 _public enumerator_ `LightcardUseStageSettings = 1 << 7` — Lightcard rendering mode is determined from the stage settings.
- L39 _public enumerator_ `LightcardRenderModeMask = LightcardAlwaysUnder | LightcardAlwaysOver | LightcardUseStageSettings` — Mask that get only flags that define the light card render mode.
- L42 _public enumerator_ `ReverseCameraPriority = 1 << 8` — The order in which the ICVFX cameras are composited over is reversed. Useful for time-multiplexed displays.
- L45 _public enumerator_ `CameraHasNoTargetViewports = 1 << 9` — Indicates that the In-Camera viewport is not visible because no target viewports are assigned.

#### enum `EDisplayClusterViewportRuntimeICVFXFlags`  
`enum class EDisplayClusterViewportRuntimeICVFXFlags: uint16`  
_L52-74_
- desc: This flag raised only from icvfx manager.
- L54 _public enumerator_ `None = 0`
- L57 _public enumerator_ `Target = 1 << 0` — Enable use icvfx only from projection policy for this viewport.
- L60 _public enumerator_ `InCamera = 1 << 1` — viewport ICVFX usage
- L61 _public enumerator_ `Chromakey = 1 << 2`
- L62 _public enumerator_ `Lightcard = 1 << 3`
- L63 _public enumerator_ `UVLightcard = 1 << 4`
- L66 _public enumerator_ `OverInFrustum = 1 << 5` — Additional flags marking the position of the viewport relative to the in-frustum.
- L67 _public enumerator_ `UnderInFrustum = 1 << 6`
- L70 _public enumerator_ `InternalResource = 1 << 14` — This viewport used as internal icvfx compositing resource (created and deleted inside icvfx logic)
- L73 _public enumerator_ `Unused = 1 << 15` — Mark unused icvfx dynamic viewports

#### Free symbols / members of external scopes

- L47 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportICVFXFlags);`
- L75 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportRuntimeICVFXFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_EyeAdaptation.h` (Public)


#### struct `FDisplayClusterViewport_EyeAdaptationData`  
`struct FDisplayClusterViewport_EyeAdaptationData`  
_L10-23_
- desc: Eye Adaptation data for nDisplay viewport.
- L13 _public function_ `inline bool CanBeUsed() const` — Return true if this data can be used.
- L22 _public member_ `float LastAverageSceneLuminance = 0.0f;` — The last valid average scene luminance for eye adaptation (exposure compensation curve). Contains the value from FSceneView::GetLastAverageSceneLuminance(). The value 0.0f means that there is no luminance data available.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_OverscanSettings.h` (Public)


#### struct `FDisplayClusterViewport_OverscanSettings`  
`struct FDisplayClusterViewport_OverscanSettings : public FMarginSet`  
_L13-58_
- inherits: `FMarginSet`
- desc: Overscan settings of viewport
- L23 _public function_ `inline void SetSymmetricOverscan(const float InOverscanFraction, bool bInOversize)` — Configures symmetric viewport overscan from an overscan fraction. @param InOverscanFraction  Per-side overscan fraction [0..1]. @param bInOversize         If true, the render target is enlarged to fit the overscan; otherwise overscan renders within the existing target.
- L43 _public member_ `uint8 bEnabled : 1 = 0;` — Enable overscan
- L46 _public member_ `uint8 bOversize : 1 = 0;` — Set to True to render at the overscan resolution, set to false to render at the resolution in the configuration and scale for overscan
- L51 _public member_ `uint8 bApplyTileEdgeBlend : 1 = 0;` — Blends the overlapping (overscan) regions between adjacent tiles. The size (in pixels) must be less than or equal to the overscan size, ensuring a smooth transition with no visible seams.
- L54 _public member_ `float TileEdgeBlendPercentage = 0.0f;` — Percentage of the overscan (0.0–1.0) to use for edge blending.
- L57 _public member_ `EDisplayClusterViewport_FrustumUnit Unit = EDisplayClusterViewport_FrustumUnit::Pixels;` — Units type of overscan values

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_PostRenderSettings.h` (Public)


#### class `FDisplayClusterViewport_PostRenderSettings`  
`class FDisplayClusterViewport_PostRenderSettings`  
_L14-41_
- desc: Additional DC viewport rendering settings
- L17 _public function_ `FDisplayClusterViewport_PostRenderSettings()`
- L20 _public function_ `~FDisplayClusterViewport_PostRenderSettings()`
- L23 _public function_ `inline void SetParameters(const FDisplayClusterViewport_PostRenderSettings& InPostRenderSettings)`
- L30 _public function_ `inline void BeginUpdateSettings()`
- L38 _public member_ `FDisplayClusterShaderParameters_Override Replace;`
- L39 _public member_ `FDisplayClusterShaderParameters_PostprocessBlur PostprocessBlur;`
- L40 _public member_ `FDisplayClusterShaderParameters_GenerateMips GenerateMips;`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_PreviewSettings.h` (Public)


#### struct `FDisplayClusterViewport_PreviewSettings`  
`struct FDisplayClusterViewport_PreviewSettings`  
_L12-77_
- desc: Viewport preview-in-scene rendering settings.
- L16 _public member_ `EDisplayClusterRenderFrameMode EntireClusterPreviewRenderMode = EDisplayClusterRenderFrameMode::PreviewInScene;` — The IDisplayClusterViewportManagerPreview::UpdateEntireClusterPreviewRender() function will use this rendering mode For special rendering cases, set a different value, such as EDisplayClusterRenderFrameMode::PreviewProxyHitInScene
- L19 _public member_ `uint8 bPreviewEnable : 1 = 0;` — Render the scene and display it as a preview on the nDisplay root actor in the editor.  This will impact editor performance.
- L22 _public member_ `uint8 bPreviewInGameEnable : 1 = 0;` — Render this DCRA in game for Standalone/Package builds.
- L23 _public member_ `uint8 bPreviewInGameRenderFrustum : 1 = 0;`
- L26 _public member_ `uint8 bPreviewEnableHoldoutComposite : 1 = 1;` — Enables the use of 'HoldoutComposite' plugin for the preview rendering.
- L31 _public member_ `uint8 bPreviewEnableTSR : 1 = 0;` — Enable TemporalAA/TSR in preview. Increases memory consumption. This will impact editor performance.
- L34 _public member_ `uint8 bEnablePreviewTechvis : 1 = 0;` — Preview uses techvis mode for rendering
- L37 _public member_ `uint8 bFreezePreviewRender : 1 = 0;` — Enable/Disable preview rendering. When disabled preview image freeze
- L42 _public member_ `uint8 bPreviewEnablePostProcess : 1 = 0;` — Hack preview gamma. In a scene, PostProcess always renders on top of the preview textures. But in it, PostProcess is also rendered with the flag turned off.
- L45 _public member_ `uint8 bPreviewEnableOCIO : 1 = 0;` — Enable OCIO on preview
- L48 _public member_ `uint8 bPreviewEnableOverlayMaterial : 1 = 1;` — Show overlay material on the preview mesh when preview rendering is enabled (UMeshComponent::OverlayMaterial)
- L51 _public member_ `uint8 bEnablePreviewMesh : 1 = 0;` — Allows you to process preview meshes inside DCRA (get or create a mesh from a projection policy, update materials on the preview mesh, etc.).
- L54 _public member_ `uint8 bEnablePreviewEditableMesh : 1 = 0;` — Allows you to process preview editable meshes inside DCRA (get or create a mesh from a projection policy, update materials on the preview editable mesh, etc.).
- L57 _public member_ `uint8 bPreviewICVFXFrustums : 1 = 0;` — Render ICVFX Frustums
- L60 _public member_ `float PreviewICVFXFrustumsFarDistance = 1000.0f;`
- L63 _public member_ `float PreviewRenderTargetRatioMult = 1.f;` — Preview RTT size multiplier
- L67 _public member_ `int32 PreviewMaxTextureDimension = 2048;` — The maximum dimension of any texture for preview Limit preview textures max size
- L70 _public member_ `int32 TickPerFrame = 1;` — Tick Per Frame
- L73 _public member_ `int32 ViewportsPerFrame = 1;` — Max amount of Viewports Per Frame
- L76 _public member_ `EDisplayClusterRootActorType DisplayDeviceRootActorType = EDisplayClusterRootActorType::Configuration;` — The DisplayDevice component will be obtained from the RootActor with the specified type

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_RenderSettings.h` (Public)


#### class `FDisplayClusterViewport_RenderSettings`  
`class FDisplayClusterViewport_RenderSettings`  
_L18-212_
- desc: nDisplay viewport render settings. These are runtime settings, updated every frame from the cluster configuration.
- L22 _public member_ `FString CameraId;` — Assigned camera. If empty, the currently active camera must be used
- L25 _public member_ `FString DisplayDeviceId;` — Assigned display device. If empty, the currently active display device must be used
- L28 _public member_ `FIntRect Rect;` — Location and size on a backbuffer.
- L32 _public member_ `bool bEnable = true;` — Enable this viewport and related resources rendering
- L35 _public member_ `bool bVisible = true;` — This viewport visible on final frame texture (backbuffer)
- L38 _public member_ `bool bSkipRendering = false;` — Skip rendering for this viewport
- L41 _public member_ `bool bFreezeRendering = false;` — Freeze viewport resources, skip rendering internal viewport resources. But still use it for final compositing
- L44 _public member_ `bool bWarpBlendRenderAlphaChannel = false;` — Render alpha channel from input texture to warp output
- L47 _public member_ `bool bDisableCustomFrustumFeature = false;` — Disable CustomFrustum feature from viewport settings
- L50 _public member_ `FDisplayClusterViewport_CustomFrustumSettings CustomFrustumSettings;` — Viewport custom frustum settings
- L53 _public member_ `bool bDisableFrustumOverscanFeature = false;` — Disable viewport overscan feature from settings
- L56 _public member_ `FDisplayClusterViewport_OverscanSettings OverscanSettings;` — Viewport frustum overscan settings
- L59 _public member_ `FDisplayClusterViewport_TileSettings TileSettings;` — Viewport tile rendering settings
- L62 _public member_ `bool bForceMono = false;` — Useful to render some viewports in mono, then copied to stereo backbuffers identical image
- L69 _public member_ `bool bEnableCrossGPUTransfer = true;` — Enable cross-GPU transfer for this viewport. It may be disabled in some configurations. For example, when using offscreen rendering with TextureShare, cross-gpu transfer can be disabled for this viewport to improve performance, because when transfer is called, it freezes the GPUs until synchronization is reached. (TextureShare uses its own implementation of the crossGPU transfer for the shared textures.)
- L72 _public member_ `int32 GPUIndex = -1;` — Performance, Multi-GPU: Asign GPU for viewport rendering. The Value '-1' used to default gpu mapping
- L75 _public member_ `int32 StereoGPUIndex = -1;` — Performance, Multi-GPU: Customize GPU for stereo mode second view (EYE_RIGHT)
- L78 _public member_ `float BufferRatio = 1;` — Allow ScreenPercentage
- L81 _public member_ `float RenderTargetRatio = 1;` — Performance: Render target base resolution multiplier
- L84 _public member_ `float RenderTargetAdaptRatio = 1;` — Performance: Render target adaptive resolution multiplier
- L87 _public member_ `FDisplayClusterUpscalerSettings UpscalerSettings;` — Upscaler settings
- L90 _public member_ `int32 OverlapOrder = 0;` — Viewport can overlap each other on backbuffer. This value uses to sorting order
- L93 _public member_ `EDisplayClusterViewportCaptureMode CaptureMode = EDisplayClusterViewportCaptureMode::Default;` — Special capture modes (chromakey, lightcard) change RTT format and render flags
- L97 _public function_ `inline void BeginUpdateSettings()` — Resets the viewport settings. This function is called every frame at the beginning of the frame.
- L115 _public function_ `inline void FinishUpdateSettings()` — Finishes setting the viewport in the game thread. Called once per frame at the end.
- L119 _public function_ `inline bool IsViewportHasParent() const` — Returns true if the viewport is assigned to a parent viewport.
- L125 _public function_ `inline const FString& GetParentViewportId() const` — Get the name of the parent viewport.
- L138 _public function_ `inline void AssignParentViewport(const FString& InParentViewportId, const FDisplayClusterViewport_RenderSettings& InParentSettings)` — Assign parent viewport to this. The main idea is copiing some render settings and math from the parent viewport. This is used for a 'link' projection policy to render LC and CK from the same frustum assigned as the parent (outer for LC, incamera for CK). Also, child viewports are only updated when the parent viewport is updated (sorted in ViewportManager/Proxy). @param InParentViewportId - parent viewport name @param InParentSettings   - parent viewport rendering settings.
- L153 _public function_ `inline bool IsViewportOverridden() const` — The viewport can be overridden from another viewport. This function returns true if it is.
- L159 _public function_ `inline EDisplayClusterViewportOverrideMode GetViewportOverrideMode() const` — Getting the override mode that is currently in use.
- L165 _public function_ `inline const FString& GetViewportOverrideId() const` — Get the name of the viewport used as the image source.
- L175 _public function_ `inline void SetViewportOverride(const FString& InViewportOverrideId, const EDisplayClusterViewportOverrideMode InViewportOverrideMode = EDisplayClusterViewportOverrideMode::All)` — Set an override for viewport images from another viewport. @param InViewportOverrideId   - The name of the viewport used as the image source. @param InViewportOverrideMode - Override mode, which defines its rules.
- L182 _public function_ `inline bool HasAnyMediaStates(const EDisplayClusterViewportMediaState InMediaStates) const` — Returns true if the media state of this viewport is set to any of the requested states.
- L188 _public function_ `inline EDisplayClusterViewportMediaState GetMediaStates() const` — Returns current media states.
- L194 _public function_ `inline void AssignMediaStates(const EDisplayClusterViewportMediaState InMediaStates)` — Set media state for this viewport.
- L201 _protected member_ `FString ParentViewportId;` — Parent viewport name
- L204 _protected member_ `FString ViewportOverrideId;` — Override resources from another viewport. The name of the viewport used as the image source.
- L207 _protected member_ `EDisplayClusterViewportOverrideMode ViewportOverrideMode = EDisplayClusterViewportOverrideMode::None;` — Override mode, which defines its rules.
- L211 _protected member_ `EDisplayClusterViewportMediaState MediaState = EDisplayClusterViewportMediaState::None;` — Viewport can be used by external media, and this affects its rules. This variable is always updated at the beginning of each viewport configuration.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_RenderSettingsICVFX.h` (Public)


#### class `FDisplayClusterViewport_RenderSettingsICVFX`  
`class FDisplayClusterViewport_RenderSettingsICVFX`  
_L13-44_
- desc: ICVFX settings for viewport
- L17 _public member_ `EDisplayClusterViewportICVFXFlags Flags = EDisplayClusterViewportICVFXFlags::None;` — ICVFX logic flags
- L20 _public member_ `EDisplayClusterViewportRuntimeICVFXFlags RuntimeFlags = EDisplayClusterViewportRuntimeICVFXFlags::None;` — Internal logic ICVFX flags
- L23 _public member_ `FDisplayClusterShaderParameters_ICVFX ICVFX;` — Compact ICVFX viewport settings
- L26 _public function_ `inline void BeginUpdateSettings()`
- L37 _public function_ `inline void SetParameters(const FDisplayClusterViewport_RenderSettingsICVFX& InParameters)` — Implement copy ref and arrays

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Containers/DisplayClusterViewport_TileSettings.h` (Public)


#### enum `EDisplayClusterViewportTileType`  
`enum class EDisplayClusterViewportTileType: uint8`  
_L12-26_
- desc: Define the viewport type for tile rendering.
- L15 _public enumerator_ `None = 0` — This viewport dont use tile rendering
- L19 _public enumerator_ `Source` — This viewport will be split into several tiled viewports. These tiled viewports will be used for rendering, after which the resulting images will be composited back into this viewport.
- L22 _public enumerator_ `Tile` — One of many tiled viewports that is used to render an image fragment for the Source viewport.
- L25 _public enumerator_ `UnusedTile` — This is an internal type that is used during the process of reallocation in the viewport.

#### enum `EDisplayClusterViewportTileFlags`  
`enum class EDisplayClusterViewportTileFlags : uint8`  
_L31-65_
- desc: Additional tile settings represented as a bitmask
- L33 _public enumerator_ `None = 0`
- L50 _public enumerator_ `AllowUnboundRender = 1 << 0` — 0 |  0  |        0           | EDisplayClusterViewportTileFlags::AllowUnboundRender 0 |  1  |        1           | 1 1 |  0  |        0           | 0 1 |  1  |        0           | 0
- L64 _public enumerator_ `OptimizeTileOverscan = 1 << 1` — Optimize overscan values for edge tiles. Overscan is not applied on the outer edges of the image — only where tiles meet. Example layout (tiles with overscan overlap marked as "++"): +------------+-----------+ | Tile0_0  ++|++ Tile1_0 | |     ++     |     ++    | +------------+-----------+ |     ++     |     ++    | | Tile0_1  ++|++ Tile1_1 | +------------+-----------+

#### struct `FDisplayClusterViewport_TileSettings`  
`struct FDisplayClusterViewport_TileSettings`  
_L72-174_
- desc: nDisplay viewport tile settings. These are runtime settings, updated every frame from the cluster configuration.
- L75 _public prototype_ `FDisplayClusterViewport_TileSettings() = default;`
- L78 _public function_ `FDisplayClusterViewport_TileSettings(const FIntPoint& InSize, const FDisplayClusterViewport_OverscanSettings& InOverscanSettings, const EDisplayClusterViewportTileFlags InTileFlags) : Type(EDisplayClusterViewportTileType::Source) , Size(InSize) , OverscanSettings(InOverscanSettings) , TileFlags(InTileFlags)` — Setup as source.
- L86 _public function_ `FDisplayClusterViewport_TileSettings(const FString& InSourceViewportId, const FIntPoint& InPos, const FIntPoint& InSize, const EDisplayClusterViewportTileFlags InTileFlags) : Type(EDisplayClusterViewportTileType::Tile) , Size(InSize) , Pos(InPos) , SourceViewportId(InSourceViewportId) , TileFlags(InTileFlags)` — Setup as tile.
- L95 _public function_ `EDisplayClusterViewportTileType GetType() const` — Returns the current viewport type for tile rendering.
- L101 _public function_ `bool IsInternalViewport() const` — Return true if this viewport is internal.
- L107 _public function_ `const FIntPoint& GetSize() const` — Get Size value.
- L113 _public function_ `const FIntPoint& GetPos() const` — Get Pos value.
- L119 _public function_ `const FString& GetSourceViewportId() const` — Get SourceViewportId.
- L125 _public function_ `const FDisplayClusterViewport_OverscanSettings& GetOverscanSettings() const` — Get overscan settings for tile rendering.
- L131 _public function_ `EDisplayClusterViewportTileFlags GetTileFlags() const` — Returns tile flags.
- L137 _public function_ `const bool HasAnyTileFlags(const EDisplayClusterViewportTileFlags RequestedTileFlags) const` — Checks if any of specified tile flags are set.
- L143 _public function_ `inline void SetTileStateToBeUsed(bool bUsed)` — Set tile state to be used.
- L158 _private member_ `EDisplayClusterViewportTileType Type = EDisplayClusterViewportTileType::None;` — Define the viewport type for tile rendering.
- L161 _private member_ `FIntPoint Size = FIntPoint::ZeroValue;` — Tile size for the 'source' viewport
- L164 _private member_ `FIntPoint Pos = FIntPoint::ZeroValue;` — Tile index for the 'tile' viewport
- L167 _private member_ `FString SourceViewportId;` — Tile source viewport name
- L170 _private member_ `FDisplayClusterViewport_OverscanSettings OverscanSettings;` — Overscan settings for tile rendering.
- L173 _private member_ `EDisplayClusterViewportTileFlags TileFlags = EDisplayClusterViewportTileFlags::None;` — Extra tile flags

#### Free symbols / members of external scopes

- L66 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterViewportTileFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewport.h` (Public)


#### class `IDisplayClusterViewport`  
`class IDisplayClusterViewport`  
_L29-349_
- desc: nDisplay: Viewport (interface for GameThread)
- L32 _public prototype_ `virtual ~IDisplayClusterViewport() = default;`
- L36 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L37 _public prototype_ `virtual TSharedPtr<const IDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L40 _public prototype_ `virtual TSharedRef<class FDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedRef() = 0;` — Internal functions. Get TSharedRef from Self.
- L41 _public prototype_ `virtual TSharedRef<const class FDisplayClusterViewport, ESPMode::ThreadSafe> ToSharedRef() const = 0;`
- L44 _public prototype_ `virtual EDisplayClusterViewportFlags GetViewportFlags() const = 0;` — Returns the usage flags of the viewport.
- L51 _public prototype_ `virtual FString GetBaseId() const = 0;` — Returns the base viewport identifier (not guaranteed to be unique across ICVFX viewports). Note: For ICVFX viewports returns: - The name of the ICVFX camera for InCamera/Chromakey. - The name of the Outer viewport for Lightcards.
- L54 _public prototype_ `virtual FString GetId() const = 0;` — Returns the unique viewport identifier, guaranteed to be unique across the entire cluster.
- L57 _public prototype_ `virtual FString GetClusterNodeId() const = 0;` — Returns the identifier of the cluster node that owns this viewport.
- L60 _public prototype_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() = 0;` — Get viewport manager configuration interface.
- L63 _public prototype_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const = 0;` — [const] Get viewport manager configuration interface.
- L66 _public prototype_ `virtual const TSharedRef<IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() = 0;` — Get viewport manager configuration interface reference.
- L69 _public prototype_ `virtual const TSharedRef<const IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() const = 0;` — [const] Get viewport manager configuration interface reference.
- L72 _public prototype_ `virtual IDisplayClusterViewportPreview& GetViewportPreview() const = 0;` — Get viewport preview API
- L75 _public prototype_ `virtual TSharedRef<class IDisplayClusterViewportProxy, ESPMode::ThreadSafe> GetViewportProxy() const = 0;` — Get viewport proxy object.
- L78 _public prototype_ `virtual const FDisplayClusterViewport_RenderSettings& GetRenderSettings() const = 0;` — Get main viewport render settings.
- L81 _public prototype_ `virtual const FDisplayClusterViewport_RenderSettingsICVFX& GetRenderSettingsICVFX() const = 0;` — Get ICVFX render settings.
- L84 _public prototype_ `virtual const FDisplayClusterViewport_PostRenderSettings& GetPostRenderSettings() const = 0;` — Get post-render settings.
- L87 _public prototype_ `virtual bool UseSameOCIO(const IDisplayClusterViewport* InViewport) const = 0;` — Returns true if both viewports use the same OCIO.
- L101 _public prototype_ `virtual void CalculateProjectionMatrix(const uint32 InContextNum, float Left, float Right, float Top, float Bottom, float ZNear, float ZFar, bool bIsAnglesInput) = 0;` — Calculate projection matrices for viewport context (also created overscan matrices, etc) @param InContextNum   - viewport eye context index @param Left           - frustum left angle @param Right          - frustum right angle @param Top            - frustum top angle @param Bottom         - frustum bottom angle @param NCP            - Near clipping plane @param FCP            - Far  clipping plane @param bIsAnglesInput - true, if projection angles in degrees
- L112 _public prototype_ `virtual bool CalculateView(const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const float WorldToMeters) = 0;` — Calculate viewport projection @param InContextNum      - viewport eye context index @param InOutViewLocation - (in, out) View location @param InOutViewRotation - (in,out) View rotator @param WorldToMeters     - UE world scale @return - true, if the calculation of the viewport projection is successful.
- L122 _public prototype_ `virtual bool GetProjectionMatrix(const uint32 InContextNum, FMatrix& OutPrjMatrix) = 0;` — Get projection matrix for viewport context @param InContextNum - viewport eye context index @param OutPrjMatrix - (out) Projection  matrix @return true, if projection matrix valid.
- L137 _public prototype_ `virtual bool CalculateViewData(const uint32 InContextNum, const FVector& InViewLocation, const FRotator& InViewRotation, const float WorldToMeters) = 0;` — Calculate View data Updates data within the FDisplayClusterViewport_Context. This function calls IDisplayClusterProjectionPolicy::CalculateView() and IDisplayClusterProjectionPolicy::GetProjectionMatrix(). Note: Called once per frame from IDisplayClusterViewport::CalculateView(). @param InContextNum      - (in) viewport eye context index @param InOutViewLocation - (in) View location @param InOutViewRotation - (in) View rotator @param WorldToMeters     - UE world scale @return true on success
- L145 _public prototype_ `virtual bool SetupViewPoint(const uint32 InContextNum, struct FMinimalViewInfo& InOutViewInfo) = 0;` — Setup viewpoint for this viewport @param InOutViewInfo - [in\out] viewinfo @return - true if there is an internal viewpoint for the given viewport.
- L150 _public prototype_ `virtual class UDisplayClusterCameraComponent* GetViewPointCameraComponent(const EDisplayClusterRootActorType InRootActorType) const = 0;` — Return view point camera component for this viewport. @param InRootActorType - the root type
- L155 _public prototype_ `virtual class UDisplayClusterDisplayDeviceBaseComponent* GetDisplayDeviceComponent(const EDisplayClusterRootActorType InRootActorType) const = 0;` — Return a DisplayDevice component for this viewport. @param InRootActorType - the root type
- L161 _public prototype_ `virtual bool GetViewPointCameraEye(const uint32 InContextNum, FVector& OutViewLocation, FRotator& OutViewRotation, FVector& OutViewOffset) = 0;` — Retrieves the view position from the ViewPoint component used by this viewport. The CalculateView() function receives arguments that may not match this position because they can be overridden. Therefore, projection policies that expect values from the ViewPoint component must use this function to get the correct values.
- L167 _public prototype_ `virtual float GetStereoEyeOffsetDistance(const uint32 InContextNum) = 0;` — Get the distance from the eye to the viewpoint location. @param InContextNum - eye context of this viewport
- L170 _public prototype_ `virtual const TSharedPtr<class IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& GetProjectionPolicy() const = 0;` — Get projection policy ref.
- L173 _public prototype_ `virtual const TArray<FDisplayClusterViewport_Context>& GetContexts() const = 0;` — Get viewport contexts
- L176 _public prototype_ `virtual const TArray<FDisplayClusterViewport_Context>& GetPrevFrameContexts() const = 0;` — Get viewport contexts captured during the previous frame.
- L179 _public prototype_ `virtual const FDisplayClusterViewportFrameData& GetFrameData() const = 0;` — Get the frame data snapshot captured for the current frame.
- L182 _public prototype_ `virtual const FDisplayClusterViewportFrameData& GetPrevFrameData() const = 0;` — Get the frame data snapshot captured during the previous frame.
- L191 _public prototype_ `virtual TSharedPtr<FSceneViewStateReference, ESPMode::ThreadSafe> GetOrCreateViewState(uint32 InContextNum) = 0;` — Returns the ViewState for the specified viewport context, creating it if necessary. @param InContextNum Eye context index for this viewport. @return Shared pointer to the corresponding ViewState, or nullptr if ViewState usage is not allowed for this viewport.
- L197 _public prototype_ `virtual FVector2D GetClippingPlanes() const = 0;` — Get clipping planes used by this viewport @return Clipping planes as FVector2D(ZNear, ZFar)
- L204 _public prototype_ `virtual bool GetOCIOConversionSettings(FOpenColorIOColorConversionSettings& OutOCIOConversionSettings) const = 0;` — Returns OCIO configuration if any set @return true if OCIO is configured
- L209 _public prototype_ `virtual const IDisplayClusterViewport_CustomPostProcessSettings& GetViewport_CustomPostProcessSettings() const = 0;` — [const] Get custom postprocess settings for this viewport.
- L214 _public prototype_ `virtual IDisplayClusterViewport_CustomPostProcessSettings& GetViewport_CustomPostProcessSettings() = 0;` — Get custom postprocess settings for this viewport.
- L219 _public prototype_ `virtual void SetupSceneView(uint32 ContextNum, class UWorld* World, class FSceneViewFamily& InViewFamily, FSceneView& InView) const = 0;` — Setup scene view for rendering specified Context.
- L225 _public prototype_ `virtual void SetRenderSettings(const FDisplayClusterViewport_RenderSettings& InRenderSettings) = 0;` — Change render setting for viewport. This function must be called in a valid moment in time.
- L231 _public prototype_ `virtual void SetContexts(TArray<FDisplayClusterViewport_Context>& InContexts) = 0;` — Change viewport contexts data. This function must be called in a valid moment in time.
- L234 _public prototype_ `static FMatrix MakeProjectionMatrix(float InLeft, float InRight, float InTop, float InBottom, float ZNear, float ZFar);` — Make asymmetrical projection matrix for nDisplay.
- L246 _public prototype_ `static bool GetCameraComponentView(UCameraComponent* InCameraComponent, const float InDeltaTime, const bool bUseCameraPostprocess, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr);` — Get View from CameraComponent @param InCameraComponent          - Ptr to the camera component used for rendering. if this ptr is nullptr, then the active player camera is used @param InDeltaTime                - delta time in current frame @param bUseCameraPostprocess      - If false, then InOutViewInfo.PostProcessBlendWeight is set to 0. @param InOutViewInfo              - ViewPoint data @param OutCustomNearClippingPlane - Custom NCP, or a value less than zero if not defined. @return false if the viewpoint data cannot be retrieved.
- L257 _public prototype_ `static bool GetPlayerCameraView(UWorld* InWorld, const bool bUseCameraPostprocess, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr);` — Get View from current player camera @param InWorld                    - (in)       In this world, an active game camera will be searched for. @param bUseCameraPostprocess      - (in)       if false, then InOutViewInfo.PostProcessBlendWeight is set to 0. @param InOutViewInfo              - (in,out)   ViewPoint data @param OutCustomNearClippingPlane - (opt, out) Custom NCP, or a value less than zero if not defined. @return false if the viewpoint data cannot be retrieved.
- L262 _public function_ `virtual class IDisplayClusterViewportManager& GetOwner() const` — `UE_DEPRECATED(5.3, "This function has beend deprecate. Please use 'GetViewportManager()'.")`
- L282 _public function_ `virtual bool CalculateView(const uint32 InContextNum, FVector& InOutViewLocation, FRotator& InOutViewRotation, const FVector& ViewOffset, const float WorldToMeters, const float NCP, const float FCP)` — `UE_DEPRECATED(5.3, "This function has been deprecated. Please use 'CalculateView()'.")` — Calculate viewport projection (This function has been deprecated.) @param InContextNum      - viewport eye context index @param InOutViewLocation - (in, out) View location @param InOutViewRotation - (in,out) View rotator @param ViewOffset         - eye offset from view location @param WorldToMeters     - UE world scale @param NCP - Near clipping plane @param FCP - Far clipping plane @return - true, if the calculation of the viewport projection is successful.
- L290 _public function_ `virtual class UDisplayClusterCameraComponent* GetViewPointCameraComponent() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetViewPointCameraComponent(EDisplayClusterRootActorType)'.")` — Return view point camera component for this viewport.
- L297 _public function_ `virtual class IDisplayClusterViewportManager* GetViewportManager() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Return the viewport manager that owns this viewport
- L304 _public function_ `virtual class ADisplayClusterRootActor* GetRootActor() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Gets a reference to the DCRA with actual configuration inside.
- L311 _public function_ `virtual EDisplayClusterRenderFrameMode GetRenderMode() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Return current render mode.
- L318 _public function_ `virtual class UWorld* GetCurrentWorld() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Return current world.
- L325 _public function_ `virtual bool IsSceneOpened() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Returns true if the scene is open now (The current world is assigned and DCRA has already initialized for it).
- L332 _public function_ `virtual bool IsCurrentWorldHasAnyType(const EWorldType::Type InWorldType1, const EWorldType::Type InWorldType2 = EWorldType::None, const EWorldType::Type InWorldType3 = EWorldType::None) const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Returns true if the current world type is equal to one of the input types.
- L344 _public function_ `virtual bool SetupViewPoint(struct FMinimalViewInfo& InOutViewInfo)` — `UE_DEPRECATED(5.5, "This function has been deprecated. Please use 'SetupViewPoint()'.")` — Setup viewpoint for this viewport @param InOutViewInfo - [in\out] viewinfo @return - true if there is an internal viewpoint for the given viewport.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportConfiguration.h` (Public)


#### class `IDisplayClusterViewportConfiguration`  
`class IDisplayClusterViewportConfiguration`  
_L20-236_
- desc: Viewport manager configuration.
- L23 _public prototype_ `virtual ~IDisplayClusterViewportConfiguration() = default;`
- L31 _public prototype_ `virtual void SetRootActor(const EDisplayClusterRootActorType InRootActorType, const ADisplayClusterRootActor* InRootActor) = 0;` — Sets a reference to the DCRA's @param InRootActorType - Type of the DCRA @param InRootActor     - a ref to DCRA
- L40 _public prototype_ `virtual void SetExclusiveLockOnRootActors(const bool bLocked) = 0;` — Applies or releases an exclusive lock on all DCRAs currently referenced by this configuration. DCRAs assigned later via SetRootActor() are also locked/unlocked automatically. Counterpart: ADisplayClusterRootActor::IsRootActorExclusivelyLocked(). @param bLocked  When true, locks all referenced DCRAs; when false, releases the lock.
- L48 _public prototype_ `virtual bool IsRootActorLockedByThis(const ADisplayClusterRootActor* InRootActor) const = 0;` — Returns true if this configuration currently holds an exclusive lock on InRootActor. Counterpart: ADisplayClusterRootActor::RootActorExclusiveLockOwners. @param InRootActor  The DCRA to query.
- L55 _public prototype_ `virtual void SetPreviewSettings(const FDisplayClusterViewport_PreviewSettings& InPreviewSettings) = 0;` — Assign new preview settings for rendering previews. @param InPreviewSettings - a new preview settings
- L58 _public prototype_ `virtual const FDisplayClusterViewport_PreviewSettings& GetPreviewSettings() const = 0;` — Gets the current preview settings.
- L68 _public prototype_ `virtual void SetExternalOverscan(bool bInEnable, const float* InOverscanOverride = nullptr) = 0;` — Enables external overscan, bypassing nDisplay's own overscan settings. When enabled, a symmetric overscan is applied from InOverscanOverride, or from FMinimalViewInfo.GetOverscan() when InOverscanOverride is nullptr. @param bInEnable          - When true, nDisplay's own overscan is ignored and the external value is used. @param InOverscanOverride - (opt) Per-side overscan fraction [0..1]. When nullptr, read from FMinimalViewInfo.GetOverscan().
- L75 _public prototype_ `virtual void SetRenderResolutionScale(const float InScale) = 0;` — Scales the render resolution of all viewports uniformly. @param InScale - Resolution scale factor [0..1]. 1.0 = full resolution, 0.5 = half resolution.
- L86 _public prototype_ `virtual bool UpdateConfigurationForClusterNode( EDisplayClusterRenderFrameMode InRenderMode, const UWorld* InWorld, const FString& InClusterNodeId, const uint32* InFrameNumberOverride = nullptr) = 0;` — Update\Create\Delete local node viewports Updating the configuration to render a ClusterNode in the specified mode @param InRenderMode          - Render mode @param InWorld               - ptr to the world to be rendered @param InClusterNodeId       - cluster node for rendering @param InFrameNumberOverride - (opt) If set, use this value instead of GFrameNumber.
- L101 _public prototype_ `virtual bool UpdateConfigurationForViewportsList( EDisplayClusterRenderFrameMode InRenderMode, const UWorld* InWorld, const TArray<FString>& InViewportNames, const uint32* InFrameNumberOverride = nullptr) = 0;` — Update\Create\Delete local node viewports Updating the configuration to render a list of viewports in a given mode @param InRenderMode          - Render mode @param InWorld               - ptr to the world to be rendered @param InViewportNames       - Viewports names for next frame @param InFrameNumberOverride - (opt) If set, use this value instead of GFrameNumber.
- L108 _public prototype_ `virtual void ReleaseConfiguration() = 0;` — Release the current configuration and free resources.
- L112 _public prototype_ `virtual const class IDisplayClusterViewportConfigurationProxy& GetProxy() const = 0;` — Return the configuration proxy object.
- L115 _public prototype_ `virtual IDisplayClusterViewportManager* GetViewportManager() const = 0;` — Return the viewport manager that used by this configuration.
- L120 _public prototype_ `virtual UWorld* GetCurrentWorld() const = 0;` — Gets a reference to the current world being rendered in DCRA
- L123 _public prototype_ `virtual float GetRootActorWorldDeltaSeconds(const EDisplayClusterRootActorType InRootActorType = EDisplayClusterRootActorType::Scene) const = 0;` — Return value from the DCRA function GetWorldDeltaSeconds().
- L131 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor(const EDisplayClusterRootActorType InRootActorType) const = 0;` — Gets a reference to the DCRA by type. If a DCRA with the specified type is not assigned, the default DCRA is used. @param InRootActorType - Type of the DCRA
- L136 _public prototype_ `virtual const UDisplayClusterConfigurationData* GetConfigurationData() const = 0;` — Gets a configuration data from the Configuration RootActor
- L141 _public prototype_ `virtual const FDisplayClusterConfigurationICVFX_StageSettings* GetStageSettings() const = 0;` — Gets a configuration stage settings from the Configuration RootActor
- L146 _public prototype_ `virtual const FDisplayClusterConfigurationRenderFrame* GetConfigurationRenderFrameSettings() const = 0;` — Gets a configuration render settings from the Configuration RootActor
- L151 _public prototype_ `virtual bool IsCurrentWorldHasAnyType( const EWorldType::Type InWorldType1, const EWorldType::Type InWorldType2 = EWorldType::None, const EWorldType::Type InWorldType3 = EWorldType::None ) const = 0;` — Returns true if the current world type is equal to one of the input types.
- L160 _public prototype_ `virtual bool IsRootActorWorldHasAnyType( const EDisplayClusterRootActorType InRootActorType, const EWorldType::Type InWorldType1, const EWorldType::Type InWorldType2 = EWorldType::None, const EWorldType::Type InWorldType3 = EWorldType::None ) const = 0;` — Returns true if the given DCRA has a world type equal to one of the input types.
- L170 _public prototype_ `virtual bool IsSceneOpened() const = 0;` — Returns true if the scene is open now (The current world is assigned and DCRA has already initialized for it).
- L173 _public prototype_ `virtual bool IsICVFXEnabled() const = 0;` — Returns true if ICVFX rendering can be used.
- L181 _public prototype_ `virtual bool IsMediaAvailable() const = 0;` — Returns true if media can be used. Note: DCRA media is available only in cluster mode and should be ignored during preview rendering.
- L184 _public prototype_ `virtual bool IsPreviewRendering() const = 0;` — Returns true if preview rendering mode is used.
- L187 _public prototype_ `virtual bool IsClusterRendering() const = 0;` — Returns true if this DCRA is using cluster rendering.
- L190 _public prototype_ `virtual bool IsMoviePipelineRendering() const = 0;` — Returns true if MoviePipeline is used for rendering.
- L193 _public prototype_ `virtual bool IsTechvisEnabled() const = 0;` — Returns true, if Techvis is used.
- L196 _public prototype_ `virtual bool IsPreviewInGameEnabled() const = 0;` — Returns true if the DCRA preview feature in Standalone/Package builds is used.
- L208 _public prototype_ `virtual bool IsRootActorExclusivelyLocked() const = 0;` — Returns true if this DCRA is under an exclusive lock. While exclusively locked: - No proxy actors may use this DCRA simultaneously. - Default scene preview rendering is disabled. - PIE rendering is disabled. Intended for scenarios where a system (e.g. Movie Render Queue) requires sole ownership of the DCRA without interference.
- L222 _public prototype_ `virtual bool IsClusterNodeRenderingOffscreen() const = 0;` — Checks whether the current cluster node is rendering offscreen (headless). Note: The DCRA can render in both Preview and Runtime Cluster modes at the same time. This is why this function is DCRA-specific rather than global. Usage: - Editor/In-Game Preview: Determined by UDisplayClusterConfigurationClusterNode::bRenderHeadless - Cluster Runtime:        Determined by the "RenderOffscreen" command-line argument @return true if rendering offscreen (headless), false otherwise.
- L225 _public prototype_ `virtual EDisplayClusterRenderFrameMode GetRenderModeForPIE() const = 0;` — Returns the rendering mode for PIE.
- L228 _public prototype_ `virtual const FString& GetClusterNodeId() const = 0;` — Return current cluster node id.
- L231 _public prototype_ `virtual const float GetWorldToMeters() const = 0;` — Return current value for WorldToMeters.
- L234 _public prototype_ `virtual int32 GetViewPerViewportAmount() const = 0;` — Return number of views per viewport.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportConfigurationProxy.h` (Public)


#### class `IDisplayClusterViewportConfigurationProxy`  
`class IDisplayClusterViewportConfigurationProxy`  
_L13-33_
- desc: Viewport manager proxy configuration.
- L16 _public prototype_ `virtual ~IDisplayClusterViewportConfigurationProxy() = default;`
- L20 _public prototype_ `virtual IDisplayClusterViewportManagerProxy* GetViewportManagerProxy_RenderThread() const = 0;` — Return the viewport manager that used by this configuration.
- L23 _public prototype_ `virtual bool IsPreviewRendering_RenderThread() const = 0;` — Returns true if preview rendering mode is used.
- L26 _public prototype_ `virtual bool IsICVFXEnabled_RenderThread() const = 0;` — Returns true if ICVFX rendering can be used.
- L29 _public prototype_ `virtual EDisplayClusterRenderFrameMode GetRenderMode_RenderThread() const = 0;` — Return current render mode.
- L32 _public prototype_ `virtual const FString& GetClusterNodeId_RenderThread() const = 0;` — Return current cluster node id.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportManager.h` (Public)


#### class `IDisplayClusterViewportManager`  
`class IDisplayClusterViewportManager`  
_L26-346_
- desc: nDisplay ViewportManager (interface for GameThread)
- L33 _public prototype_ `virtual void Release() = 0;` — Must be called before the destructor. Because all subsystems connected to this class via WeakPtr will not work when we are in destructor.
- L35 _public prototype_ `virtual ~IDisplayClusterViewportManager() = default;`
- L42 _public prototype_ `static TSharedRef<IDisplayClusterViewportManager, ESPMode::ThreadSafe> CreateViewportManager();` — Static viewport manager instance constructor. This function is needed for external modules that may need their own instance of ViewportManager, which will be used to generate preview images with their own rendering settings.
- L45 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L46 _public prototype_ `virtual TSharedPtr<const IDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L49 _public prototype_ `virtual TSharedRef<class FDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedRef() = 0;` — Internal functions. Get TSharedRef from Self.
- L50 _public prototype_ `virtual TSharedRef<const class FDisplayClusterViewportManager, ESPMode::ThreadSafe> ToSharedRef() const = 0;`
- L53 _public prototype_ `virtual const IDisplayClusterViewportManagerProxy* GetProxy() const = 0;` — Get viewport manager proxy interface.
- L54 _public prototype_ `virtual IDisplayClusterViewportManagerProxy* GetProxy() = 0;`
- L57 _public prototype_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() = 0;` — Get viewport manager configuration interface.
- L58 _public prototype_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const = 0;`
- L61 _public prototype_ `virtual const TSharedRef<IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() = 0;` — Get viewport manager configuration interface reference.
- L62 _public prototype_ `virtual const TSharedRef<const IDisplayClusterViewportConfiguration, ESPMode::ThreadSafe> GetConfigurationRef() const = 0;`
- L66 _public prototype_ `virtual IDisplayClusterViewportManagerPreview& GetViewportManagerPreview() = 0;` — Get viewport manager preview API
- L67 _public prototype_ `virtual const IDisplayClusterViewportManagerPreview& GetViewportManagerPreview() const = 0;`
- L79 _public prototype_ `virtual bool BeginNewFrame(FViewport* InViewport, FDisplayClusterRenderFrame& OutRenderFrame) = 0;` — Initialize new frame for all viewports on game thread, and update context, render resources with viewport new settings And finally build render frame structure and send to render thread proxy viewport objects [Game thread func] @param InViewport          - target viewport @param OutRenderFrame      - output render frame container @return - true, if success
- L86 _public prototype_ `virtual void InitializeNewFrame() = 0;` — Initialize frame for render on game thread [Game thread func]
- L93 _public prototype_ `virtual void FinalizeNewFrame() = 0;` — Finalize frame for render on game thread [Game thread func]
- L106 _public prototype_ `virtual FSceneViewFamily::ConstructionValues CreateViewFamilyConstructionValues( const FDisplayClusterRenderFrameTarget& InFrameTarget, FSceneInterface* InScene, FEngineShowFlags InEngineShowFlags, const bool bInAdditionalViewFamily ) const = 0;` — Create constructor values for viewfamily, using rules [Game thread func] @param InFrameTarget           - frame target @param InScene                 - scene @param InEngineShowFlags       - starting showflags @param bInAdditionalViewFamily - flag indicating this is an additional view family @return - The ConstructionValues object that was created, meant to initialize a view family context.
- L114 _public prototype_ `static void SetupEngineShowFlags(const EDisplayClusterViewportCaptureMode InMode, FEngineShowFlags& InOutEngineShowFlags);` — This function sets the engine flags corresponding to the rendering mode.
- L117 _public prototype_ `static void SetupSceneView(const EDisplayClusterViewportCaptureMode InMode, FSceneViewFamily& InOutViewFamily, FSceneView& InOutView);` — Sets the ViewFamily and SceneView properties correspond to the rendering mode.
- L128 _public prototype_ `virtual void ConfigureViewFamily( const FDisplayClusterRenderFrameTarget& InFrameTarget, const FDisplayClusterRenderFrameTargetViewFamily& InFrameViewFamily, FSceneViewFamilyContext& InOutViewFamily) = 0;` — Initialize view family, using rules [Game thread func] @param InFrameTarget          - frame target @param InFrameViewFamily      - the frame data for the view family @param OutRenderOutViewFamily - (in, out) The view family that will be configured.
- L147 _public prototype_ `virtual void PostConfigureViewFamily( const FDisplayClusterRenderFrameTarget& InFrameTarget, const FDisplayClusterRenderFrameTargetViewFamily& InFrameViewFamily, FSceneViewFamilyContext& InOutViewFamily, const TArray<FSceneView*>& InOutViews, const EDisplayClusterViewportRenderingFlags InRenderingFlags = EDisplayClusterViewportRenderingFlags::None, const float InDPIScale = 1.f) = 0;` — Post-Initialize view family, using rules Should be called after all 'FSceneView' have been added. This function configures the screen percentage. [Game thread func] @param InFrameTarget            - frame target @param InFrameViewFamily        - the frame data for the view family @param InOutRenderOutViewFamily - (in, out) The view family that will be configured. @param InOutViews               - (in, out) The views in the family that will be configured. @param InRenderingFlags         - (in, opt) Rules for customizing nDisplay views and view families for the renderer. @param InDPIScale               - (in, opt ) DPI scale value
- L156 _public prototype_ `virtual void RenderFrame(FViewport* InViewport) = 0;` — Send to render thread.
- L159 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) = 0;` — Add internal DCVM objects to the reference collector.
- L170 _public prototype_ `virtual IDisplayClusterViewport* FindViewport(const FString& InViewportId) const = 0;` — Find viewport object by name [Game thread func] @param ViewportId - Viewport name @return - viewport object ref
- L181 _public prototype_ `virtual IDisplayClusterViewport* FindViewport(const int32 StereoViewIndex, uint32* OutContextNum = nullptr) const = 0;` — Find viewport object and context number by stereoscopic pass index [Game thread func] @param StereoViewIndex - stereoscopic view index @param OutContextNum - context number @return - viewport object ref
- L189 _public prototype_ `virtual const TArrayView<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>> GetCurrentRenderFrameViewports() const = 0;` — Return all exist viewports objects for current cluster node [Game thread func] @return - arrays with viewport objects refs
- L197 _public prototype_ `virtual const TArrayView<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>> GetEntireClusterViewports() const = 0;` — Return entire cluster viewports objects [Game thread func] @return - arrays with viewport objects refs
- L206 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>> GetEntireClusterViewportsForWarpPolicy(const TSharedPtr<IDisplayClusterWarpPolicy>& InWarpPolicy) const = 0;` — Returns the viewports from the entire cluster associated with the specified warp policy [Game thread func] @param InWarpPolicy - The warp policy to get viewports for @return - A list of viewports associated with the warp policy
- L214 _public prototype_ `virtual void MarkComponentGeometryDirty(const FName InComponentName = NAME_None) = 0;` — Mark the geometry of the referenced component(s) as dirty (ProceduralMesh, etc) [Game thread func] @param InComponentName - (optional) Unique component name
- L228 _public prototype_ `virtual class FSceneView* CalcSceneView( class ULocalPlayer* LocalPlayer, class FSceneViewFamily* ViewFamily, FVector& OutViewLocation, FRotator& OutViewRotation, class FViewport* Viewport, class FViewElementDrawer* ViewDrawer, int32 StereoViewIndex) = 0;` — Call LocalPlayer->CalcSceneView() [Game thread func] @param LocalPlayer - local player @param ViewFamily - output view struct @param OutViewLocation - output actor location @param OutViewRotation - output actor rotation @param Viewport - current client viewport @param ViewDrawer - optional drawing in the view @param StereoViewIndex - index of the view when using stereoscopy
- L240 _public function_ `virtual const TArrayView<IDisplayClusterViewport*> GetViewports() const` — `UE_DEPRECATED(5.3, "This function has been deprecated. Please use 'GetCurrentRenderFrameViewports'.")`
- L249 _public function_ `virtual EDisplayClusterRenderFrameMode GetRenderMode() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Return current render mode.
- L255 _public function_ `virtual UWorld* GetCurrentWorld() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")`
- L261 _public function_ `virtual ADisplayClusterRootActor* GetRootActor() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")`
- L271 _public function_ `virtual bool IsSceneOpened() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Returns true if the scene is open now (The current world is assigned and DCRA has already initialized for it). [Game thread func]
- L289 _public function_ `virtual bool UpdateConfiguration(EDisplayClusterRenderFrameMode InRenderMode, const FString& InClusterNodeId, class ADisplayClusterRootActor* InRootActorPtr, const struct FDisplayClusterPreviewSettings* InPreviewSettings = nullptr)` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Update\Create\Delete local node viewports Update ICVFX configuration from root actor components [Game thread func] @param InRenderMode     - Render mode @param InClusterNodeId  - cluster node for rendering @param InRootActorPtr   - reference to RootActor with actual configuration inside @param InPreviewSettings - support preview rendering @return - true, if success
- L306 _public function_ `virtual bool UpdateCustomConfiguration(EDisplayClusterRenderFrameMode InRenderMode, const TArray<FString>& InViewportNames, class ADisplayClusterRootActor* InRootActorPtr)` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfiguration()'.")` — Update\Create\Delete viewports for frame. For rendering outside of cluster nodes Update ICVFX configuration from root actor components [Game thread func] @param InRenderMode    - Render mode @param InViewportNames - Viewports names for next frame @param InRootActorPtr  - reference to RootActor with actual configuration inside @return - true, if success
- L322 _public function_ `virtual bool BeginNewFrame(FViewport* InViewport, UWorld* InWorld, FDisplayClusterRenderFrame& OutRenderFrame)` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'BeginNewFrame()'.")` — Initialize new frame for all viewports on game thread, and update context, render resources with viewport new settings And finally build render frame structure and send to render thread proxy viewport objects [Game thread func] @param InViewport          - target viewport @param OutRenderFrame      - output render frame container @return - true, if success
- L342 _public function_ `virtual bool RenderInEditor(FDisplayClusterRenderFrame& InRenderFrame, FViewport* InViewport, const uint32 InFirstViewportNum, const int32 InViewportsAmount, int32& OutViewportsAmount, bool& bOutFrameRendered)` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetViewportPreview().Render()'.")` — Render in editor (preview) [Game thread func] @param InRenderFrame - render frame setup @param InViewport @param InFirstViewportNum - begin render from this viewport in frame @param InViewportsAmount - max viewports for render @param OutViewportsAmount - total viewport rendered @param bOutFrameRendered - true, if cluster node composition pass done (additional pass after last viewport is rendered) @return - true, if render success

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportManagerPreview.h` (Public)


#### class `IDisplayClusterViewportManagerPreview`  
`class IDisplayClusterViewportManagerPreview`  
_L14-80_
- desc: Viewport manager preview rendering interface
- L17 _public prototype_ `virtual ~IDisplayClusterViewportManagerPreview() = default;`
- L21 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L22 _public prototype_ `virtual TSharedPtr<const IDisplayClusterViewportManagerPreview, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L25 _public prototype_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() = 0;` — Get viewport manager configuration interface.
- L26 _public prototype_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const = 0;`
- L37 _public prototype_ `virtual void UpdateEntireClusterPreviewRender(bool bEnablePreviewRendering) = 0;` — A preview of the entire cluster is rendered using the tick-per-frame and viewport-per-frame settings. This function should be called several times until the entire cluster is rendered. The rendering is distributed over multiple frames to improve performance. The rendering of multiple instances is also distributed to improve performance. Note: When rendering the entire cluster, the CurrentWorld value will always be overridden by the GetWorld() value obtained from SceneRootActor. @param bEnablePreviewRendering - to render or stop rendering.
- L40 _public prototype_ `virtual void ResetEntireClusterPreviewRendering() = 0;` — Reset preview rendering for entire cluster.
- L52 _public prototype_ `virtual bool InitializeClusterNodePreview(const EDisplayClusterRenderFrameMode InRenderMode, UWorld* InWorld, const FString& InClusterNodeId, FViewport* InViewport) = 0;` — Initialization of preview rendering for a cluster node @param InRenderMode    - Rendering mode @param InWorld         - World to render @param InClusterNodeId - cluster node name @param InViewport      - Output viewport @return true if success
- L63 _public prototype_ `virtual int32 RenderClusterNodePreview(const int32 InViewportsAmmount, FViewport* InViewport = nullptr, FCanvas* SceneCanvas = nullptr) = 0;` — Render specified ammount of viewport for current cluster node @param InViewportsAmmount - Total ammount of viewports that should be rendered on this frame INDEX_NONE means render all viewports of this node @param InViewport         - (opt) the dest window @return a value equal to InViewportsAmmount minus the total number of rendered viewports.
- L71 _public prototype_ `virtual const TArray<TSharedPtr<IDisplayClusterViewportPreview, ESPMode::ThreadSafe>> GetEntireClusterPreviewViewports() const = 0;` — Returns all cluster viewport objects that are visible, displayed on the output texture, and used in the preview. [Game thread func] @return - arrays with viewport preview objects refs
- L73 _public prototype_ `DECLARE_DELEGATE(FOnOnEntireClusterPreviewGenerated);`
- L75 _public prototype_ `virtual FOnOnEntireClusterPreviewGenerated& GetOnEntireClusterPreviewGenerated() = 0;` — Rendering preview of the entire cluster node is complete.
- L77 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnOnClusterNodePreviewGenerated, const FString&);`
- L79 _public prototype_ `virtual FOnOnClusterNodePreviewGenerated& GetOnClusterNodePreviewGenerated() = 0;` — Rendering preview of the current cluster node is complete.

#### Free symbols / members of external scopes

- L73 _delegate_ `DECLARE_DELEGATE(FOnOnEntireClusterPreviewGenerated);`
- L77 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOnClusterNodePreviewGenerated, const FString&);`

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportManagerProxy.h` (Public)


#### class `IDisplayClusterViewportManagerProxy`  
`class IDisplayClusterViewportManagerProxy`  
_L11-85_
- desc: nDisplay ViewportManagerProxy (interface for RenderThread)
- L14 _public prototype_ `virtual ~IDisplayClusterViewportManagerProxy() = default;`
- L18 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L19 _public prototype_ `virtual TSharedPtr<const IDisplayClusterViewportManagerProxy, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L22 _public prototype_ `virtual const IDisplayClusterViewportConfigurationProxy& GetConfigurationProxy() const = 0;` — Get viewport manager proxy configuration interface.
- L32 _public prototype_ `virtual IDisplayClusterViewportProxy* FindViewport_RenderThread(const FString& InViewportId) const = 0;` — Find viewport render thread proxy object by name [Rendering thread func] @param ViewportId - Viewport name @return - viewport proxy object ref
- L43 _public prototype_ `virtual IDisplayClusterViewportProxy* FindViewport_RenderThread(const int32 StereoViewIndex, uint32* OutContextNum = nullptr) const = 0;` — Find viewport render thread proxy object and context number by stereoscopic pass index [Rendering thread func] @param StereoViewIndex - stereoscopic view index @param OutContextNum - context number @return - viewport render thread proxy object ref
- L51 _public prototype_ `virtual const TArrayView<TSharedPtr<IDisplayClusterViewportProxy, ESPMode::ThreadSafe>> GetViewports_RenderThread() const = 0;` — Return all exist viewports render thread proxy objects [Rendering thread func] @return - arrays with viewport render thread proxy objects refs
- L63 _public prototype_ `virtual bool GetFrameTargets_RenderThread(TArray<FRHITexture*>& OutFrameResources, TArray<FIntPoint>& OutTargetOffsets, TArray<FRHITexture*>* OutAdditionalFrameResources=nullptr) const = 0;` — Return render frame targets for current frame [Rendering thread func] @param OutRenderFrameTargets - frame RTTs (left, right) @param OutTargetOffsets - frames offset on backbuffer @param OutAdditionalFrameResources - (optional) array with additional render targetable resources (requested externally FDisplayClusterRenderFrameSettings::bShouldUseAdditionalTargetableFrameResource) @return - true if success
- L75 _public prototype_ `virtual bool ResolveFrameTargetToBackBuffer_RenderThread(FRHICommandListImmediate& RHICmdList, const uint32 InContextNum, const int32 DestArrayIndex, FRHITexture* DstBackBuffer, FVector2D WindowSize) const = 0;` — Resolve to backbuffer [Rendering thread func] @param InContextNum - renderframe source context num @param DestArrayIndex - dest array index on backbuffer @param WindowSize - dest backbuffer window size @return - true if success
- L81 _public function_ `virtual EDisplayClusterRenderFrameMode GetRenderMode() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfigurationProxy()'.")` — Return current render mode.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportPreview.h` (Public)


#### class `IDisplayClusterViewportPreview`  
`class IDisplayClusterViewportPreview`  
_L15-54_
- desc: Provides access to the resources used to render the viewport preview.
- L18 _public prototype_ `virtual ~IDisplayClusterViewportPreview() = default;`
- L22 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewportPreview, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L23 _public prototype_ `virtual TSharedPtr<const IDisplayClusterViewportPreview, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L26 _public prototype_ `virtual IDisplayClusterViewportConfiguration& GetConfiguration() = 0;` — Get viewport manager configuration interface.
- L27 _public prototype_ `virtual const IDisplayClusterViewportConfiguration& GetConfiguration() const = 0;`
- L30 _public prototype_ `virtual FString GetId() const = 0;` — Gets the viewport name.
- L33 _public prototype_ `virtual FString GetClusterNodeId() const = 0;` — Gets the cluster node name.
- L36 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> GetOwningViewport() const = 0;` — Returns the viewport that owns this object.
- L39 _public prototype_ `virtual bool HasAnyFlags(const EDisplayClusterViewportPreviewFlags InPreviewFlags) const = 0;` — Returns true if the preview has any of the requested flags.
- L42 _public prototype_ `virtual UTextureRenderTarget2D* GetPreviewTextureRenderTarget2D() const = 0;` — Get viewport preview texture.
- L45 _public prototype_ `virtual UMeshComponent* GetPreviewMeshComponent() const = 0;` — Get viewport preview mesh.
- L48 _public prototype_ `virtual UMeshComponent* GetPreviewEditableMeshComponent() const = 0;` — Get viewport preview editable mesh.
- L52 _public function_ `virtual IDisplayClusterViewport* GetViewport() const` — `UE_DEPRECATED(5.8, "This function is deprecated. Use GetOwningViewport() instead.")` — Deprecated. The base implementation returns nullptr. Use GetOwningViewport() instead.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewportProxy.h` (Public)


#### class `IDisplayClusterViewportProxy`  
`class IDisplayClusterViewportProxy`  
_L26-196_
- desc: nDisplay: ViewportProxy (interface for RenderThread)
- L29 _public prototype_ `virtual ~IDisplayClusterViewportProxy() = default;`
- L33 _public prototype_ `virtual TSharedPtr<IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L34 _public prototype_ `virtual TSharedPtr<const IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L37 _public prototype_ `virtual TSharedRef<IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedRef() = 0;` — Get TSharedRef from self.
- L38 _public prototype_ `virtual TSharedRef<const IDisplayClusterViewportProxy, ESPMode::ThreadSafe> ToSharedRef() const = 0;`
- L41 _public prototype_ `virtual EDisplayClusterViewportFlags GetViewportFlags() const = 0;` — Returns the usage flags of the viewport.
- L48 _public prototype_ `virtual FString GetBaseId() const = 0;` — Returns the base viewport identifier (not guaranteed to be unique across ICVFX viewports). Note: For ICVFX viewports returns: - The name of the ICVFX camera for InCamera/Chromakey. - The name of the Outer viewport for Lightcards.
- L51 _public prototype_ `virtual FString GetId() const = 0;` — Returns the unique viewport identifier, guaranteed to be unique across the entire cluster.
- L54 _public prototype_ `virtual FString GetClusterNodeId() const = 0;` — Returns the identifier of the cluster node that owns this viewport.
- L57 _public prototype_ `virtual const IDisplayClusterViewportConfigurationProxy& GetConfigurationProxy() const = 0;` — Get viewport manager configuration interface.
- L60 _public prototype_ `virtual const TSharedPtr<class IDisplayClusterProjectionPolicy, ESPMode::ThreadSafe>& GetProjectionPolicy_RenderThread() const = 0;` — Get projection policy ref.
- L63 _public prototype_ `virtual const FDisplayClusterViewport_RenderSettings& GetRenderSettings_RenderThread() const = 0;` — Get main viewport render settings.
- L66 _public prototype_ `virtual const FDisplayClusterViewport_RenderSettingsICVFX& GetRenderSettingsICVFX_RenderThread() const = 0;` — Get ICVFX render settings.
- L69 _public prototype_ `virtual const FDisplayClusterViewport_PostRenderSettings& GetPostRenderSettings_RenderThread() const = 0;` — Get post-render settings.
- L72 _public prototype_ `virtual const TArray<FDisplayClusterViewport_Context>& GetContexts_RenderThread() const = 0;` — Return viewport proxy contexts data.
- L75 _public prototype_ `virtual const FDisplayClusterViewportFrameData& GetFrameData_RenderThread() const = 0;` — Get the frame data snapshot captured for the current frame.
- L78 _public prototype_ `virtual const FDisplayClusterViewportFrameData& GetPrevFrameData_RenderThread() const = 0;` — Get the frame data snapshot captured during the previous frame.
- L85 _public prototype_ `virtual FDisplayClusterColorEncoding GetResourceColorEncoding_RenderThread(const EDisplayClusterViewportResourceType InResourceType) const = 0;` — Return color-encoding information for the resource @param InResourceType   - (in) resource type (RTT, Shader, MIPS, etc)
- L94 _public prototype_ `virtual bool GetResources_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources) const = 0;` — Get viewport resources by type @param InResourceType - resource type (RTT, Shader, MIPS, etc) @param OutResources   - [Out] RHI resources array for all contexts @return - true if success
- L104 _public prototype_ `virtual bool GetResourcesWithRects_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources, TArray<FIntRect>& OutRects) const = 0;` — Get viewport resources with rects by type @param InResourceType - resource type (RTT, Shader, MIPS, etc) @param OutResources   - [Out] RHI resources array for all contexts @param OutRects       - [Out] RHI resources rects array for all contexts @return - true if success
- L117 _public prototype_ `virtual bool SetResourcesOverride_RenderThread(const EDisplayClusterViewportResourceType InResourceType, const TArray<FRHITexture*>& InResources, const TArray<FIntRect>* InOptRects = nullptr) const = 0;` — Set a per-frame resource override for the given resource type. The override shadows the normal resource-fetch path for this frame only and is cleared automatically at the start of the next frame. Pass an empty InResources to remove any existing override for InResourceType. @param InResourceType - resource type to override (RTT, Shader, MIPS, etc) @param InResources    - RHI resources to use instead of the viewport's own, one entry per context; pass empty to clear @param InOptRects     - [optional] subrect within each resource; if null, the full texture extent is used @return - true if the override was stored (or cleared) successfully @see GetResourcesOverride_RenderThread
- L128 _public prototype_ `virtual bool GetResourcesOverride_RenderThread(const EDisplayClusterViewportResourceType InResourceType, TArray<FRHITexture*>& OutResources, TArray<FIntRect>* OutOptRects = nullptr) const = 0;` — Get the active per-frame resource override for the given resource type, if one was set this frame via SetResourcesOverride_RenderThread. @param InResourceType - resource type to query (RTT, Shader, MIPS, etc) @param OutResources   - [Out] overriding RHI resources, one entry per context @param OutOptRects    - [optional, Out] subrects for each resource; not written if null @return - true if an override is active for InResourceType this frame @see SetResourcesOverride_RenderThread
- L139 _public prototype_ `virtual bool ResolveResources_RenderThread(FRHICommandListImmediate& RHICmdList, const EDisplayClusterViewportResourceType InputResourceType, const EDisplayClusterViewportResourceType OutputResourceType, const int32 InContextNum = INDEX_NONE) const = 0;` — Copy resource contexts by type @param RHICmdList         - RHIinterface @param InputResourceType  - Input resource type (RTT, Shader, MIPS, etc) @param OutputResourceType - Output resource type (RTT, Shader, MIPS, etc) @param InContextNum       - [optional] the type of context to copy (by default, all contexts are copied). @return - true if success
- L151 _public prototype_ `virtual bool ResolveResources_RenderThread(FRHICommandListImmediate& RHICmdList, IDisplayClusterViewportProxy* InputResourceViewportProxy, const EDisplayClusterViewportResourceType InputResourceType, const EDisplayClusterViewportResourceType OutputResourceType, const int32 InContextNum = INDEX_NONE) const = 0;` — Copy resource contexts by type @param RHICmdList                 - RHIinterface @param InputResourceViewportProxy - The 'InputResourceType' resource will be obtained from this object @param InputResourceType          - Input resource type (RTT, Shader, MIPS, etc) @param OutputResourceType         - Output resource type (RTT, Shader, MIPS, etc) @param InContextNum               - [optional] the type of context to copy (by default, all contexts are copied). @return - true if success
- L157 _public prototype_ `virtual void SetRenderSettings_RenderThread(const FDisplayClusterViewport_RenderSettings& InRenderSettings) const = 0;` — Change render setting for viewport. This function must be called in a valid moment in time.
- L163 _public prototype_ `virtual void SetContexts_RenderThread(const TArray<FDisplayClusterViewport_Context>& InContexts) const = 0;` — Change viewport contexts data. This function must be called in a valid moment in time.
- L169 _public function_ `virtual EDisplayClusterViewportResourceType GetOutputResourceType_RenderThread() const` — `UE_DEPRECATED(5.3, "This function has beend deprecate. Please use the new enumeration values.")` — Return output resource type (support preview, remap, etc).
- L178 _public function_ `virtual EDisplayClusterRenderFrameMode GetRenderMode() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfigurationProxy().GetRenderMode_RenderThread()'.")` — Return current render mode.
- L185 _public function_ `virtual const class IDisplayClusterViewportManagerProxy* GetViewportManagerProxy_RenderThread() const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'GetConfigurationProxy().GetViewportManagerProxy_RenderThread'.")` — Returns ptr to ViewportManagerProxy (the owner of this viewport proxy) if it still exists.
- L192 _public function_ `virtual const struct FDisplayClusterRenderFrameSettings* GetRenderFrameSettings_RenderThread() const` — `UE_DEPRECATED(5.4, "This function has been deprecated.")` — Get render frame settings from viewport proxy owner, if it still exists.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/IDisplayClusterViewport_CustomPostProcessSettings.h` (Public)


#### class `IDisplayClusterViewport_CustomPostProcessSettings`  
`class IDisplayClusterViewport_CustomPostProcessSettings`  
_L13-64_
- desc: DC Viewport Postprocess interface
- L16 _public prototype_ `virtual ~IDisplayClusterViewport_CustomPostProcessSettings() = default;`
- L39 _public prototype_ `virtual void AddCustomPostProcess(const ERenderPass InRenderPass, const FPostProcessSettings& InSettings, float BlendWeight, bool bSingleFrame) = 0;` — Add custom postprocess.
- L42 _public prototype_ `virtual void RemoveCustomPostProcess(const ERenderPass InRenderPass) = 0;` — Deletes the custom postprocess for the specified rendering pass.
- L54 _public prototype_ `virtual bool ApplyCustomPostProcess(IDisplayClusterViewport* InViewport, const uint32 InContextNum, const ERenderPass InRenderPass, FPostProcessSettings& InOutPPSettings, float* InOutBlendWeight = nullptr) const = 0;` — Apply postprocess for the specified rendering pass to the InOutStartPostProcessingSettings. @param InViewport       - DC viewport that is rendered with these settings. @param InContextNum     - Index of view that is being processed for this viewport @param InRenderPass     - PP rendering pass to be used. (The value of 'FinalPerViewport' is ignored.) @param InOutPPSettings  - (in,out) PostProcess settings that need to be changed. @param InOutBlendWeight - (opt, in, out) PostProcess weight parameter that need to be changed. @return true, if the postprocess settings have been overridden.
- L59 _public function_ `virtual bool DoPostProcess(const ERenderPass InRenderPass, struct FPostProcessSettings* OutSettings, float* OutBlendWeight = nullptr) const` — `UE_DEPRECATED(5.5, "This function has been deprecated. Please use 'ApplyCustomPostProcess()'.")` — Override postprocess, if defined.

#### enum `IDisplayClusterViewport_CustomPostProcessSettings::ERenderPass`  
`enum class ERenderPass : uint8`  
_L20-35_
- desc: The viewport's custom PostProcesses are blended in a specific order, which is specified by the values below.
- L23 _public enumerator_ `Start = 0` — These PP settings will be applied when the StartFinalPostprocessSettings() function is called
- L26 _public enumerator_ `Override` — These PP settings will be applied when the OverrideFinalPostprocessSettings() function is called
- L30 _public enumerator_ `Final` — These PP settings will be applied when the EndFinalPostprocessSettings() function is called. The `Final` and `FinalPerViewport` are always applied together.
- L34 _public enumerator_ `FinalPerViewport` — This rendering pass is for the container only, to separate ICVFX ColorGrading into a separate pass. Note: The value is ignored by ApplyCustomPostProcess().

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/Misc/DisplayClusterViewportHelpers.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DisplayClusterViewportHelpers` (scope `UE`)
- L21 _function_ `template<class TComp> TComp* GetRootActorComponentByName(const IDisplayClusterViewportConfiguration& InConfiguration, const EDisplayClusterRootActorType InRootActorType, const FString& InComponentName)` (scope `UE::DisplayClusterViewportHelpers`) — Find a component by name from a RootActor of the specified type. @param InConfiguration - current configuration @param InRootActorType - the search is performed within the DCRA of the given type. @param InComponentName - the name of the component
- L45 _function_ `template<class TComp> TComp* GetOwnerRootActorComponentByName(USceneComponent* ComponentOfRootActor, const FString& InComponentName)` (scope `UE::DisplayClusterViewportHelpers`) — Find a component by name from a RootActor of the specified type. @param ComponentOfRootActor @param InComponentName - the name of the component
- L79 _function_ `template<class TComp> const TComp& GetMatchingComponentFromRootActor(const IDisplayClusterViewportConfiguration& InConfiguration, const EDisplayClusterRootActorType InRootActorType, const TComp& InComponent)` (scope `UE::DisplayClusterViewportHelpers`) — Return the same component (by class and name) from a DCRA of the specified type. If no other component exists, or if the current DCRA type matches the requested one, the input component is returned. @param InRootActorType - the search is performed within the DCRA of the given type. @param InComponent     - The component that is used for the search. @return A component with the same name and class belonging to a DCRA of this type.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/RenderFrame/DisplayClusterRenderFrame.h` (Public)


#### struct `FDisplayClusterRenderFrameTargetView`  
`struct FDisplayClusterRenderFrameTargetView`  
_L19-39_
- desc: nDisplay: DCViewport context for render in UE View
- L22 _public function_ `inline bool IsViewportContextCanBeRendered() const` — Is this viewport context can be rendered.
- L28 _public member_ `uint32 ContextNum = 0;` — Viewport context index for this view
- L31 _public member_ `bool bDisableRender = false;` — Some viewports may skip rendering (for example: overridden)
- L35 _public member_ `bool bFreezeRendering = false;` — In special cases, viewports can reuse an existing RTT image For example: the preview is rendered over several frames, so the already rendered viewports remain "frozen" and can be used during subsequent frames.
- L38 _public member_ `TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> Viewport;` — Viewport game-thread data

#### struct `FDisplayClusterRenderFrameTargetViewFamily`  
`struct FDisplayClusterRenderFrameTargetViewFamily`  
_L44-57_
- desc: nDisplay: A group of DCViewports that can be render within a single viewfamily
- L47 _public member_ `float CustomBufferRatio = 1;` — Customize ScreenPercentage feature for viewfamily
- L50 _public member_ `FDisplayClusterUpscalerSettings UpscalerSettings;` — ViewFamily Upscaler settings
- L53 _public member_ `TArray<FSceneViewExtensionRef> ViewExtensions;` — Extensions that can modify view parameters
- L56 _public member_ `TArray<FDisplayClusterRenderFrameTargetView> Views;` — Viewports, rendered at once for this family

#### struct `FDisplayClusterRenderFrameTarget`  
`struct FDisplayClusterRenderFrameTarget`  
_L63-84_
- desc: nDisplay: Target texture for rendering. Contains structured information on how to render DCViewports via viewfamilies in RTT
- L67 _public member_ `bool bShouldUseRenderTarget = true;` — Discard some RTT (when view render disabled) Also when RTT Atlasing used, this viewports excluded from atlas map (reduce size)
- L70 _public member_ `FIntPoint RenderTargetSize;` — required Render target size (resource can be bigger)
- L74 _public member_ `EDisplayClusterViewportCaptureMode CaptureMode = EDisplayClusterViewportCaptureMode::Default;` — Viewport capture mode This mode affects many viewport rendering settings.
- L77 _public member_ `TSharedPtr<FDisplayClusterViewportResource, ESPMode::ThreadSafe> RenderTargetResource;` — Render target resource ref
- L80 _public member_ `FViewport* Viewport = nullptr;` — UE Viewport used to render
- L83 _public member_ `TArray<FDisplayClusterRenderFrameTargetViewFamily> ViewFamilies;` — Families, rendered on this target

#### class `FDisplayClusterRenderFrame`  
`class FDisplayClusterRenderFrame`  
_L91-112_
- desc: nDisplay: Render frame container The final frame is composed of DCViewports, which are rendered in the correct order on a few RTTs. Contains all information about how to render all DCViewports for the current frame and the settings for it.
- L95 _public function_ `IDisplayClusterViewportManager* GetViewportManager() const` — Returns a pointer to the DCViewportManager used for this frame.
- L102 _public member_ `TArray<FDisplayClusterRenderFrameTarget> RenderTargets;` — Render frame to this targets
- L105 _public member_ `FIntRect FrameRect;` — Frame rect on final backbuffer
- L108 _public member_ `int32 DesiredNumberOfViews = 0;` — Desired numbers of view
- L111 _public member_ `TWeakPtr<IDisplayClusterViewportManager, ESPMode::ThreadSafe> ViewportManagerWeakPtr;` — Ref to the DC Viewport Manager

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Viewport/RenderFrame/DisplayClusterRenderFrameEnums.h` (Public)


#### enum `EDisplayClusterRenderFrameMode`  
`enum class EDisplayClusterRenderFrameMode : uint8`  
_L10-57_
- desc: Defines the rendering output mode.
- L12 _public enumerator_ `Unknown = 0`
- L15 _public enumerator_ `Mono` — Monoscopic rendering to a backbuffer texture.
- L18 _public enumerator_ `Stereo` — Stereoscopic rendering to a layered backbuffer texture (quad-buffer).
- L22 _public enumerator_ `SideBySide` — Stereoscopic rendering packed into one texture: left eye in the left half, right eye in the right half.
- L26 _public enumerator_ `TopBottom` — Stereoscopic rendering packed into one texture: left eye in the top half, right eye in the bottom half.
- L29 _public enumerator_ `PIE_Mono` — Monoscopic rendering in Play In Editor (PIE).
- L33 _public enumerator_ `PIE_SideBySide` — Stereoscopic rendering in PIE packed into one texture: left eye in the left half, right eye in the right half.
- L37 _public enumerator_ `PIE_TopBottom` — Stereoscopic rendering in PIE packed into one texture: left eye in the top half, right eye in the bottom half.
- L40 _public enumerator_ `MRQ_Mono` — Monoscopic rendering for Movie Render Queue (MRQ).
- L43 _public enumerator_ `MRQ_Stereo` — Stereoscopic rendering for Movie Render Queue (MRQ).
- L46 _public enumerator_ `MRG_Mono` — Monoscopic rendering for Movie Render Graph (MRG).
- L49 _public enumerator_ `MRG_Stereo` — Stereoscopic rendering for Movie Render Graph (MRG).
- L52 _public enumerator_ `PreviewInScene` — Rendering mode used for in-scene preview.
- L56 _public enumerator_ `PreviewProxyHitInScene` — ProxyHit rendering mode used for in-scene preview. Not implemented.

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Warp/IDisplayClusterWarpPolicy.h` (Public)


#### class `IDisplayClusterWarpPolicy`  
`class IDisplayClusterWarpPolicy`  
_L19-132_
- desc: Warp policy interface Customize warp math for projection policies. Multiple projections can use the same warp policy.
- L22 _public prototype_ `virtual ~IDisplayClusterWarpPolicy() = default;`
- L26 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L27 _public prototype_ `virtual TSharedPtr<const IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L32 _public prototype_ `virtual const FString& GetId() const = 0;` — Return warp policy instance ID
- L37 _public prototype_ `virtual const FString& GetType() const = 0;` — Return warp policy type
- L46 _public function_ `virtual bool ShouldSupportICVFX(const IDisplayClusterViewport* InViewport) const` — Returns true if this policy supports ICVFX rendering @param InViewport - a owner viewport @return - true if this warp policy supports ICVFX
- L57 _public function_ `virtual void HandleNewFrame(const TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports)` — Handle new frame for viewports group. This function is called once per frame at the beginning, immediately after the viewport setup is complete. @param InViewports - a group of viewports from the entire cluster that use this WarpInterface
- L68 _public function_ `virtual void Tick(IDisplayClusterViewportManager* InViewportManager, float DeltaSeconds)` — Tick function The positions of editable preview components may be updated on each frame. Use this function to handle these updates. @param InViewportManager - Viewport manager interface @param DeltaSeconds      - delta time
- L78 _public function_ `virtual bool ShouldOverrideCalcFrustum(IDisplayClusterViewport* InViewport)` — Should override frustum for viewport context @param InViewport - a owner viewport @param ContextNum - viewport eye context index @return - true, if the CalcFrustumOverrideFunc() function will be used
- L91 _public function_ `virtual bool OverrideCalcFrustum(IDisplayClusterViewport* InViewport, const uint32 ContextNum)` — Override frustum for viewport context This function is called only when the ShouldOverrideCalcFrustum() function returns true @param InViewport - a owner viewport @param ContextNum - viewport eye context index @return - true if frustum is overridden.
- L101 _public function_ `virtual void BeginCalcFrustum(IDisplayClusterViewport* InViewport, const uint32 ContextNum)` — Call before CalcFrustum() @param InViewport - a owner viewport @param ContextNum - viewport eye context index
- L109 _public function_ `virtual void EndCalcFrustum(IDisplayClusterViewport* InViewport, const uint32 ContextNum)` — Call after CalcFrustum() @param InViewport - a owner viewport @param ContextNum - viewport eye context index
- L117 _public function_ `virtual bool HasPreviewEditableMesh(IDisplayClusterViewport* InViewport)` — Ask warp  policy instance if it has any Editable mesh based preview @param InViewport - a owner viewport @return - True if mesh based preview is available
- L130 _public function_ `virtual void OnUpdateDisplayDeviceMeshAndMaterialInstance(IDisplayClusterViewportPreview& InViewportPreview, const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType, UMeshComponent* InMeshComponent, UMaterialInstanceDynamic* InMeshMaterialInstance) const` — Perform any operations on the  mesh and material instance, such as setting parameter values. @param InViewport - current viewport @param InMeshType - mesh type @param InMaterialType - type of material being requested @param InMeshComponent - mesh component to be updated @param InMeshMaterialInstance - material instance that used on this mesh

### `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/Render/Warp/IDisplayClusterWarpPolicyFactory.h` (Public)


#### class `IDisplayClusterWarpPolicyFactory`  
`class IDisplayClusterWarpPolicyFactory`  
_L12-27_
- desc: nDisplay warp policy factory interface
- L15 _public prototype_ `virtual ~IDisplayClusterWarpPolicyFactory() = default;`
- L26 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> Create(const FString& InWarpPolicyType, const FString& InWarpPolicyName) = 0;` — Creates a warp policy instance @param InWarpPolicyType - Warp policy type, same as specified on registration (useful if the same factory is registered for multiple warp policy types) @param InWarpPolicyName - Warp policy name @return - Warp policy instance
