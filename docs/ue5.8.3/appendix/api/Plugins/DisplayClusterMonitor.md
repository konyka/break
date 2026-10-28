# Plugins / DisplayClusterMonitor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor`
- headers: 12; symbols: 319
- symbol kinds: class=10, delegate=9, enum=5, enumerator=19, function=25, member=88, namespace=27, prototype=105, struct=26, typedef=5
- PrivateDependencyModuleNames: DisplayCluster, DisplayClusterConfiguration, DisplayClusterShaders, Engine, MediaIOCore, NDIMedia, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Messaging, MessagingCommon

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/DisplayClusterMonitorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitor, Log, All);` — Module-wide log categories
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitor, Log, All);` — Module-wide log categories
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitorMsg, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitorMsg, Log, All);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitorProviderMedia, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitorProviderMedia, Log, All);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitorObservableMedia, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMonitorObservableMedia, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/DisplayClusterMonitorModule.h` (Private)


#### class `FDisplayClusterMonitorModule`  
`class FDisplayClusterMonitorModule : public IModuleInterface`  
_L17-54_
- inherits: `IModuleInterface`
- desc: DisplayClusterMonitor module implementation
- L20 _private typedef_ `using FDCMProviderMedia = UE::nDisplay::Monitor::FDisplayClusterMonitorProviderMedia;`
- L24 _public prototype_ `FDisplayClusterMonitorModule() = default;`
- L25 _public prototype_ `virtual ~FDisplayClusterMonitorModule() override = default;`
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L37 _private prototype_ `void StartProviders();` — Starts all observable providers that are managed by this module
- L40 _private prototype_ `void StopProviders();` — Stops all observable providers that are managed by this module
- L45 _private prototype_ `void OnDisplayClusterSessionStart();` — Handles nDisplay session start event to initialize per-session internals
- L48 _private prototype_ `void OnDisplayClusterSessionEnd();` — Handles nDisplay session end event to release per-session internals
- L53 _private member_ `TUniquePtr<FDCMProviderMedia> ProviderMedia;` — Media observables provider

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace nDisplay` (scope `UE`)
- L8 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/DisplayClusterMonitorProviderMedia.h` (Private)


#### class `UE::nDisplay::Monitor::FDisplayClusterMonitorProviderMedia`  
`class FDisplayClusterMonitorProviderMedia : public FDisplayClusterMonitorProviderBase`  
_L20-147_
- inherits: `FDisplayClusterMonitorProviderBase`
- desc: Media observables provider
- L23 _private typedef_ `using Super = FDisplayClusterMonitorProviderBase;`
- L27 _public prototype_ `FDisplayClusterMonitorProviderMedia() = default;`
- L28 _public prototype_ `virtual ~FDisplayClusterMonitorProviderMedia() override = default;`
- L33 _public prototype_ `virtual bool Start() override;`
- L34 _public prototype_ `virtual void Stop() override;`
- L36 _public function_ `virtual FString GetMessengerName() const override`
- L83 _private prototype_ `TSharedPtr<IMediaObservable> CreateObservable(EDCObservableType InType, const FSourceInfo& SourceInfo);` — Factory method to create an observable of specific type
- L88 _private prototype_ `void OnNodeObservablesRequest(const FDCEndpoint& InEndpoint, const FDCMMessage_NodeObservablesRequest& InMessage);` — Handles remote requests to provide the list of available observables
- L91 _private prototype_ `void OnStartSessionRequest(const FDCEndpoint& InEndpoint, const FDCMMessage_StartSessionRequest& InMessage);` — Handles remote requests to start observation sessions
- L94 _private prototype_ `void OnStopSessionRequest(const FDCEndpoint& InEndpoint, const FDCMMessage_StopSessionRequest& InMessage);` — Handles remote requests to stop observation sessions
- L97 _private prototype_ `void OnObservableControlRequest(const FDCEndpoint& InEndpoint, const FDCMMessage_ObservableControlRequest& InMessage);` — Handles session control commands
- L100 _private prototype_ `void OnEndpointLeft(const FDCEndpoint& InEndpoint, const FString& InReason);` — Handles an endpoint leaving the cluster
- L103 _private prototype_ `void OnEndpointTimeout(const FDCEndpoint& InEndpoint);` — Handles an endpoint timeout
- L106 _private prototype_ `void OnEndFrame();` — Handles end frame (game thread)
- L109 _private prototype_ `void OnConsoleCommand(const FDCEndpoint& InSenderEndpoint, const FString& InExecutorName, const FString& InCommand);` — Handles remote console commands
- L114 _private prototype_ `void EvaluateViewport(const TSharedPtr<IDisplayClusterViewport>& InViewport);` — Evaluates regular viewports
- L117 _private prototype_ `void EvaluateICVFXCamera(const TSharedPtr<IDisplayClusterViewport>& InViewport);` — Evaluates ICVFX cameras
- L120 _private prototype_ `void EvaluateICVFXCameraTile(const TSharedPtr<IDisplayClusterViewport>& InViewport);` — Evaluates ICVFX camera tiles
- L123 _private prototype_ `void EvaluateUI();` — Evaluates the GUI layer
- L126 _private prototype_ `void EvaluateBackbuffer();` — Evaluates the backbuffer
- L129 _private prototype_ `void PropagateSourceInfo();` — Propaages data to the monitors
- L132 _private prototype_ `void DeleteClientData(const FMessageAddress& ClientAddress);` — Removes all client's data from internal storage
- L135 _private prototype_ `void StopActiveSessions();` — Terminates all active sessions
- L140 _private member_ `TMap<EDCObservableType, TMap<FString, FSourceInfo>> ActiveSources;` — Currently available observables
- L143 _private member_ `TMap<FMessageAddress, TMap<FGuid, TSharedPtr<IMediaObservable>>> ActiveSessions;` — Per-monitor active observation sessions map <MonitorAddr, <ObservableId, ObservableImpl>>
- L146 _private member_ `FDCMData_NodeObservables LastObservablesInfo;` — The most recent and actual observables evaluation

#### enum `UE::nDisplay::Monitor::FDisplayClusterMonitorProviderMedia::ESourceStatus`  
`enum class ESourceStatus : uint8`  
_L47-57_
- desc: Observable source status
- L50 _public enumerator_ `New` — New source since last evaluation
- L52 _public enumerator_ `Removed` — Removed source
- L54 _public enumerator_ `Unchanged` — Unchanged since last evaluation
- L56 _public enumerator_ `Updated` — The source has been updated since last evaluation

#### struct `UE::nDisplay::Monitor::FDisplayClusterMonitorProviderMedia::FSourceInfo`  
`struct FSourceInfo`  
_L62-78_
- desc: Observable source data
- L65 _public member_ `FGuid Id;` — Observable GUID
- L67 _public member_ `FString DisplayName;` — Display name to use in UI
- L69 _public member_ `FString ResourceName;` — Internal viewport name
- L71 _public member_ `FIntPoint Size;` — Observable texture size
- L73 _public member_ `TOptional<FString> ParentName;` — Parent name (optional, tiles only)
- L75 _public member_ `TOptional<FIntPoint> TilePos;` — Tile position (optional, tiles only)
- L77 _public member_ `ESourceStatus Status = ESourceStatus::New;` — Current evaluation status, updates every frame

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace nDisplay` (scope `UE`)
- L13 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/MediaObservables/IMediaObservable.h` (Private)


#### class `UE::nDisplay::Monitor::IMediaObservable`  
`class IMediaObservable`  
_L16-38_
- desc: Media observable session interface Declares the API of all media observables on the provider side
- L20 _public prototype_ `virtual ~IMediaObservable() = default;`
- L25 _public prototype_ `virtual FGuid GetId() const = 0;` — Returns ID of this observable entity
- L28 _public prototype_ `virtual FString GetName() const = 0;` — Returns display name of this observable entity
- L31 _public prototype_ `virtual FString GetResourceId() const = 0;` — Returns internal name of the viewport resource
- L34 _public prototype_ `virtual bool StartCapture() = 0;` — Start resource capturing
- L37 _public prototype_ `virtual void StopCapture() = 0;` — Stop resource capturing

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace nDisplay` (scope `UE`)
- L9 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/MediaObservables/MediaObservableBackbuffer.h` (Private)


#### class `UE::nDisplay::Monitor::FMediaObservableBackbuffer`  
`class FMediaObservableBackbuffer : public FMediaObservableBase`  
_L18-45_
- inherits: `FMediaObservableBase`
- desc: Backbuffer media observable Responsible for streaming out the backbuffer texture
- L21 _private typedef_ `using Super = FMediaObservableBase;`
- L25 _public prototype_ `FMediaObservableBackbuffer(const FGuid& InObservableId, const FString& InObservableName, const FString& InResourceId);`
- L26 _public prototype_ `virtual ~FMediaObservableBackbuffer() override = default;`
- L31 _public prototype_ `virtual bool StartCapture() override;`
- L32 _public prototype_ `virtual void StopCapture() override;`
- L38 _private prototype_ `virtual FIntPoint GetCaptureSize() const override;` — Returns backbuffer size
- L44 _private prototype_ `void OnPostBackbufferUpdated_RenderThread(FRHICommandListImmediate& RHICmdList, FViewport* Viewport);` — Handles the backbuffer updates. When it's called, we can safely grab the current frame output and stream it out.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace nDisplay` (scope `UE`)
- L11 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/MediaObservables/MediaObservableBase.h` (Private)


#### class `UE::nDisplay::Monitor::FMediaObservableBase`  
`class FMediaObservableBase : public IMediaObservable , public FGCObject`  
_L23-151_
- inherits: `IMediaObservable,FGCObject`
- desc: Abstract media observable class It provides the common media capture functionality, and is used as a base one for all media observable implementations.
- L29 _public prototype_ `FMediaObservableBase(const FGuid& InObservableId, const FString& InObservableName, const FString& InResourceId);`
- L30 _public prototype_ `virtual ~FMediaObservableBase();`
- L36 _public function_ `virtual FGuid GetId() const override final`
- L41 _public function_ `virtual FString GetName() const override final`
- L46 _public function_ `virtual FString GetResourceId() const override final`
- L51 _public prototype_ `virtual bool StartCapture() override;`
- L52 _public prototype_ `virtual void StopCapture() override;`
- L59 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L60 _public function_ `virtual FString GetReferencerName() const override`
- L84 _protected prototype_ `void OnPostClusterTick();` — PostClusterTick event handler. It's used to restart capturing if needed
- L87 _protected prototype_ `bool StartMediaCapture();` — Re-starts media capturing after failure
- L90 _protected prototype_ `virtual FString GenerateMediaSourceName() const;` — Generates kind of unique media ID to use as media source name
- L93 _protected prototype_ `void ExportMediaData_RenderThread(FRDGBuilder& GraphBuilder, const FMediaOutputTextureInfo& TextureInfo);` — Passes capture data request to the capture device
- L96 _protected prototype_ `virtual FIntPoint GetCaptureSize() const = 0;` — Returns capture size
- L99 _protected function_ `UNDIMediaOutput* GetMediaOutput() const` — Returns current media output
- L126 _private member_ `const FGuid ObservableId;` — Observable GUID
- L129 _private member_ `const FString ObservableName;` — Observable name
- L132 _private member_ `const FString ResourceId;` — Internal resource name for this observable
- L135 _private member_ `TObjectPtr<UNDIMediaOutput> MediaOutput;` — NDI media output used for streaming data out
- L138 _private member_ `TObjectPtr<UMediaCapture> MediaCapture;` — Media capture used for this observable
- L141 _private member_ `FIntPoint CustomResolution = FIntPoint::ZeroValue;` — Custom resolution to use on capture side
- L144 _private member_ `bool bWasCaptureStarted = false;` — Used to restart media capture in the case it falls in error
- L147 _private member_ `double LastRestartTimestamp = 0;` — Used to control the rate at which we try to restart the capture
- L150 _private member_ `std::atomic<FIntSize> LastSrcRegionSize{ FIntSize(0, 0) };` — Last region size of the texture being exported.Used to restart the capture when in error.

#### struct `UE::nDisplay::Monitor::FMediaObservableBase::FMediaOutputTextureInfo`  
`struct FMediaOutputTextureInfo`  
_L69-79_
- desc: Media capture data
- L72 _public member_ `FRDGTextureRef Texture = nullptr;` — Texture to capture by a media capture device
- L75 _public member_ `FIntRect Region = { FIntPoint::ZeroValue, FIntPoint::ZeroValue };` — Subregion to capture
- L78 _public prototype_ `bool IsValidData() const;` — Validates if capture request data is valid

#### struct `UE::nDisplay::Monitor::FMediaObservableBase::FIntSize`  
`struct FIntSize`  
_L109-121_
- desc: Trivial version of FIntPoint so that it can be std::atomic
- L111 _public member_ `int32 X = 0;`
- L112 _public member_ `int32 Y = 0;`
- L114 _public function_ `FIntSize(int32 InX, int32 InY) : X(InX), Y(InY)`
- L115 _public function_ `FIntSize(const FIntPoint& IntPoint) : X(IntPoint.X), Y(IntPoint.Y)`
- L117 _public function_ `FIntPoint ToIntPoint()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace nDisplay` (scope `UE`)
- L15 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/MediaObservables/MediaObservablePostRender.h` (Private)


#### class `UE::nDisplay::Monitor::FMediaObservablePostRender`  
`class FMediaObservablePostRender : public FMediaObservableBase`  
_L23-53_
- inherits: `FMediaObservableBase`
- desc: PostRender media observable In nDisplay, regular viewports, ICVFX cameras or camera tiles are rendered in a normal way. They all get PostRenderViewFamily callback where we can grab the render output. This observable is responisble exactly for that. It captures the corresponding media data right after it's rendered, and streams out then.
- L26 _private typedef_ `using Super = FMediaObservableBase;`
- L30 _public prototype_ `FMediaObservablePostRender(const FGuid& InObservableId, const FString& InObservableName, const FString& InResourceId);`
- L31 _public prototype_ `virtual ~FMediaObservablePostRender() override = default;`
- L36 _public prototype_ `virtual bool StartCapture() override;`
- L37 _public prototype_ `virtual void StopCapture() override;`
- L45 _protected prototype_ `virtual FIntPoint GetCaptureSize() const override;` — Returns texture size of a viewport assigned to capture (main thread)
- L52 _private prototype_ `void OnPostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamily, const IDisplayClusterViewportProxy* ViewportProxy);` — PostRenderViewFamily callback handler where data is captured right after it's rendered

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace nDisplay` (scope `UE`)
- L12 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Private/MediaObservables/MediaObservableUI.h` (Private)


#### class `UE::nDisplay::Monitor::FMediaObservableUI`  
`class FMediaObservableUI : public FMediaObservableBase`  
_L20-47_
- inherits: `FMediaObservableBase`
- desc: GUI layer media observable nDisplay has internal solution that allows to draw the overlay UI into a separate texture, then blend it on top of the other viewports. This observable is responsible for straming out the GUI texture only.
- L23 _private typedef_ `using Super = FMediaObservableBase;`
- L27 _public prototype_ `FMediaObservableUI(const FGuid& InObservableId, const FString& InObservableName, const FString& InResourceId);`
- L28 _public prototype_ `virtual ~FMediaObservableUI() override = default;`
- L33 _public prototype_ `virtual bool StartCapture() override;`
- L34 _public prototype_ `virtual void StopCapture() override;`
- L40 _private prototype_ `virtual FIntPoint GetCaptureSize() const override;` — Returns UI layer size
- L46 _private prototype_ `void HandlePostBackbufferUpdated_RenderThread(FRHICommandListImmediate& RHICmdList, FViewport* Viewport);` — It's called, when the backbuffer is already updated for current frame. This also means the GUI texture is ready as well so we can safely grab it.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace nDisplay` (scope `UE`)
- L11 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Public/DisplayClusterMonitorMessenger.h` (Public)


#### class `UE::nDisplay::Monitor::FDCMessenger`  
`class FDCMessenger`  
_L24-376_
- desc: Cluster monitor messenger It's a wrapper around the Message Bus message endpoint that encapsulates some basic functionality like disovery, timeout monitor, callbacks. etc.
- L28 _public prototype_ `FDCMessenger() = default;`
- L29 _public prototype_ `~FDCMessenger();`
- L41 _public prototype_ `bool Start(const FString& InEndpointName, const TSet<EDCMessengerRole>& InEndpointRoles);` — Start messenger with given name and roles @param InEndpointName  - Entity name @param InEndpointRoles - Set of roles for this entity @return - True if started successfully
- L48 _public prototype_ `void Stop(const FString& InReason = FString());` — Stop messenger @param InReason - (optional) The reason for shutting down this entity
- L55 _public function_ `bool IsRunning() const` — Whether the messenger is currently runing @return - True if currently running
- L65 _public prototype_ `FMessageAddress GetAddress() const;` — Returns MessageBus address of this messenger @return - MessageBus address
- L75 _public prototype_ `FMessageAddress GetAddress(const FGuid& InClusterId, const FGuid& InNodeId) const;` — Returns MessageBus address of a spcific residence @param ClusterId - GUID of a cluster @param NodeId    - GUID of a cluster node @return - MessageBus address
- L82 _public prototype_ `const FDCEndpoint& GetEndpointInfo() const;` — Returns this messenger's endpoint info @return - Endpoint information
- L89 _public prototype_ `TConstArrayView<FDCEndpoint> GetDiscoveredEndpoints() const;` — Returns a list of endpoints that have been discovered @return - Discovered endpoints
- L101 _public function_ `template <typename MessageType> requires std::derived_from<MessageType, FDCMMessageBase> void Send(const TArray<FMessageAddress>& InRecipients, const MessageType& InMessage)` — Send message to a list of recipients @param InRecipients - An array of message destinations @param InMessage    - A message to send
- L117 _public function_ `template <typename MessageType> requires std::derived_from<MessageType, FDCMMessageBase> void Send(const TArray<FMessageAddress>& InRecipients, MessageType&& InMessage)` — Send message to a list of recipients (move semantics) @param InRecipients - An array of message destinations @param InMessage    - A message to send
- L134 _public function_ `template <typename MessageType> requires std::derived_from<MessageType, FDCMMessageBase> void SendToRoles(const TSet<EDCMessengerRole>& InEndpointTypes, MessageType&& InMessage)` — Send message to everyone who has any of specified messenger roles @param InEndpointTypes - A set of roles that should receive this message @param InMessage       - A message to send
- L148 _public function_ `template <typename MessageType> requires std::derived_from<MessageType, FDCMMessageBase> void Broadcast(MessageType&& InMessage)` — Broadcast message @note Every cluster monitor messenger will receive it. @param InMessage       - A message to send
- L156 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndpointJoined, const FDCEndpoint& );` — Called every time a new endpoint is discovered
- L157 _public member_ `FOnEndpointJoined OnEndpointJoined;`
- L160 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndpointTimeout, const FDCEndpoint& );` — Called every time a known endpoint is considered unresponsive
- L161 _public member_ `FOnEndpointTimeout OnEndpointTimeout;`
- L164 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEndpointLeft, const FDCEndpoint& , const FString& );` — Called every time a known endpoint reports it's leaving
- L165 _public member_ `FOnEndpointLeft OnEndpointLeft;`
- L168 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnConsoleCommand, const FDCEndpoint& , const FString& , const FString& ) FOnConsoleCommand OnConsoleCommand;` — Called every time a cluster monitor requests local execution of a console command
- L213 _public function_ `template<typename MessageType> requires std::derived_from<MessageType, FDCMMessage> FCustomMessageEvent<MessageType>::FDelegate& OnMessage()` — Generic access to the user delegates Usage: OnMessage<FDCMMessage_Child1>().AddRaw(...); OnMessage<FDCMMessage_Child2>().AddRaw(...); OnMessage<FDCMMessage_Child3>().AddRaw(...);
- L232 _private function_ `void CallUserFunction(const UScriptStruct* MessageTypeInfo, const FDCEndpoint& Endpoint, const FDCMMessage& Message)` — It's an auxiliary function that executes user delegate based on the message type
- L250 _private prototype_ `void SendImpl(const TArray<FMessageAddress>& InRecipients, void* InPayload, UScriptStruct* InType);` — Private implementation of the public templated "Send" function
- L253 _private prototype_ `void SendToRoles(const TSet<EDCMessengerRole>& InEndpointTypes, void* InPayload, UScriptStruct* InType);` — Private implementation of the public templated "SendToRoles" function
- L256 _private prototype_ `void BroadcastImpl(void* InPayload, UScriptStruct* InType);` — Private implementation of the public templated "Broadcast" function
- L261 _private prototype_ `bool Tick(float InDeltaTime);` — Our custom Tick() handler
- L264 _private prototype_ `void TickTask_PulseHearbeat(float InDeltaTime);` — Broadcasts heartbeat pulse
- L267 _private prototype_ `void TickTask_CheckInactiveEndpoints(float InDeltaTime);` — Checks if there are any unresponsive endpoints among the known ones
- L272 _private function_ `FDCEndpoint* GetEndpoint(const FMessageAddress& InAddress)` — Auxiliary function that searches for an endpoint that has the specified MessageBus address
- L278 _private function_ `int32 GetEndpointIdx(const FMessageAddress& InAddress) const` — Auxiliary function that finds the index of an endpoint in the known endpoints array by its MessageBus address
- L287 _private prototype_ `static FGuid MakeDeterministicClusterGuid(const FString& InPrimaryNodeId, const FString& InPrimaryNodeAddr, uint16 InPrimaryExclusiveCommPort);` — Auxiliary function that generates the cluster GUID deterministically. The generated GUID is expected to be the same on every cluster node.
- L292 _private prototype_ `FDCMData_ResidenceDescriptor GetResidenceDescriptor() const;` — Returns residence discriptor of this messenger
- L297 _private prototype_ `void BroadcastJoin();` — Notify everyone this messenger is online
- L300 _private prototype_ `void BroadcastHeartbeat();` — Broadcast hearbeat pulse
- L303 _private prototype_ `void BroadcastLeave(const FString& InShutdownReason);` — Notify everyone this messenger is shutting down
- L308 _private prototype_ `void OnDiscoveryRequest(const FDCMMessage_DiscoveryRequest& InMessage, const TSharedRef<IMessageContext>& InContext);` — Handles discovery requests
- L311 _private prototype_ `void OnDiscoveryResponse(const FDCMMessage_DiscoveryResponse& InMessage, const TSharedRef<IMessageContext>& InContext);` — Handles discovery responses
- L314 _private prototype_ `void OnHeartbeat(const FDCMMessage_Heartbeat& InMessage, const TSharedRef<IMessageContext>& InContext);` — Handles heartbeat notifications
- L317 _private prototype_ `void OnShutdown(const FDCMMessage_Shutdown& InMessage, const TSharedRef<IMessageContext>& InContext);` — Handles endpoints shutdown
- L320 _private prototype_ `void OnExecuteConsoleCommand(const FDCMMessage_ExecuteConsoleCommand& InMessage, const TSharedRef<IMessageContext>& InContext);` — Executes console commands locally
- L323 _private prototype_ `void OnUserMessages(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Handles all user messages
- L328 _private function_ `void UpdateLastActivityTime(const FMessageAddress& InAddress)` — Helper to update the last activity time of an endpoint with the specified address
- L337 _private function_ `void UpdateLastActivityTime(FDCEndpoint& InEndpoint)` — Helper to update the last activity time of the specified endpoint
- L343 _private function_ `static double GetLastActivityTime()` — Activity time provider
- L351 _private member_ `bool bIsRunning = false;` — Whether this messenenger is currently active
- L354 _private member_ `FDCEndpoint ThisEndpoint;` — Endpoint information of this messenger instance
- L357 _private member_ `static TOptional<FDCMData_ResidenceDescriptor> ThisResidence;` — Residence of this UE process
- L360 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;` — MessageBus message endpoint
- L363 _private member_ `TArray<FDCEndpoint> DiscoveredEndpoints;` — All discovered and currently online endpoints
- L366 _private member_ `TMap<UScriptStruct*, TSharedPtr<FCustomMessageEventBase>> UserMessageEvents;` — Message type bound user delegates
- L369 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Custom Tick() delegate handle
- L372 _private member_ `double LastHeartbeatPulseTime = 0.f;` — Last time we sent hearbeat pulse
- L375 _private member_ `uint32 HeartbeatPulseCounter = 0;` — Heartbeat pulse counter. Increments every time with the pulse.

#### struct `UE::nDisplay::Monitor::FDCMessenger::FCustomMessageEventBase`  
`struct FCustomMessageEventBase`  
_L176-182_
- desc: Auxiliary non-templated class to generalize user delegates
- L178 _public prototype_ `virtual ~FCustomMessageEventBase() = default;`
- L181 _public prototype_ `virtual void Broadcast(const FDCEndpoint& Endpoint, const FDCMMessage& Msg) = 0;` — Non-templated (generalized) delegate call

#### struct `UE::nDisplay::Monitor::FDCMessenger::FCustomMessageEvent`  
`template<typename MessageType> requires std::derived_from<MessageType, FDCMMessage> struct FCustomMessageEvent : public FCustomMessageEventBase`  
_L189-201_
- inherits: `FCustomMessageEventBase`
- desc: Universal user delegates wrapper
- L192 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate, const FDCEndpoint&, const MessageType&);` — Actual delegate
- L193 _public member_ `FDelegate Delegate;`
- L196 _public function_ `virtual void Broadcast(const FDCEndpoint& Endpoint, const FDCMMessage& Msg) override` — Callback impplementation

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace nDisplay` (scope `UE`)
- L16 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)
- L156 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndpointJoined, const FDCEndpoint& );` — Called every time a new endpoint is discovered
- L160 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndpointTimeout, const FDCEndpoint& );` — Called every time a known endpoint is considered unresponsive
- L164 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEndpointLeft, const FDCEndpoint& , const FString& );` — Called every time a known endpoint reports it's leaving
- L168 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnConsoleCommand, const FDCEndpoint& , const FString& , const FString& ) FOnConsoleCommand OnConsoleCommand;` — Called every time a cluster monitor requests local execution of a console command
- L192 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate, const FDCEndpoint&, const MessageType&);` — Actual delegate
- L274 _function_ `return DiscoveredEndpoints.FindByPredicate([&InAddress](const FDCEndpoint& EP) { return EP.Address == InAddress; });` (scope `UE::nDisplay::Monitor::FDCMessenger::GetEndpoint`)
- L280 _function_ `return DiscoveredEndpoints.IndexOfByPredicate([&InAddress](const FDCEndpoint& EP) { return EP.Address == InAddress; });` (scope `UE::nDisplay::Monitor::FDCMessenger::GetEndpointIdx`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Public/DisplayClusterMonitorProviderBase.h` (Public)


#### class `UE::nDisplay::Monitor::FDisplayClusterMonitorProviderBase`  
`class FDisplayClusterMonitorProviderBase`  
_L16-42_
- desc: Base class for cluster observable providers
- L20 _public prototype_ `FDisplayClusterMonitorProviderBase();`
- L21 _public prototype_ `virtual ~FDisplayClusterMonitorProviderBase() = default;`
- L26 _public prototype_ `virtual bool Start();` — Start provider activity
- L29 _public prototype_ `virtual void Stop();` — Stop provider activity
- L36 _public prototype_ `virtual FString GetMessengerName() const = 0;` — Get messenger name to use during messenger initialization @return - Messenger name
- L41 _protected member_ `TUniquePtr<FDCMessenger> Messenger;` — The Message Bus messenger

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace nDisplay` (scope `UE`)
- L9 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Public/DisplayClusterMonitorSettings.h` (Public)


#### class `UDisplayClusterMonitorSettings`  
`class UDisplayClusterMonitorSettings : public UObject`  
_L17-65_
- reflection: `UCLASS(Config = Game, DefaultConfig)`
- inherits: `UObject`
- desc: Cluster monitor settings Contains both editor only and runtime cluster monitor settings
- L28 _public member_ `float HeartbeatInterval = 3.f;` — `UPROPERTY(Config, EditAnywhere, Category = "Runtime", meta = (ClampMin = 0.5f, UIMin = 0.5f, ClampMax = 10.f, UIMax = 10.f))` — Heartbeat pulse interval for the messenger. Used to detect unresponsive or crashed nodes.
- L34 _public member_ `float UnresponsiveTimeThreshold = 15.f;` — `UPROPERTY(Config, EditAnywhere, Category = "Runtime", meta = (ClampMin = 10.f, UIMin = 10.f, ClampMax = 30.f, UIMax = 30.f))` — Maximum time, in seconds, without receiving any messages, before an endpoint is considered unresponsive.
- L44 _public member_ `bool bAddNewObservablesToFront = true;` — `UPROPERTY(Config, EditAnywhere, Category = "UI")` — When enabled, new observable viewports appear at the very beginning of the viewport layout. Otherwise, they're added to the end.
- L50 _public member_ `int32 ViewportsInRow = 2;` — `UPROPERTY(Config, EditAnywhere, Category = "UI", meta = (UIMin = 1, ClampMin = 1, UIMax = 8, ClampMax = 8))` — Determines the number of viewports displayed per row
- L56 _public member_ `bool bUseFixedViewportHeight = true;` — `UPROPERTY(Config, EditAnywhere, Category = "UI")` — Whether viewports have fixed height
- L62 _public member_ `float FixedViewportHeight = 500;` — `UPROPERTY(Config, EditAnywhere, Category = "UI")` — The height of viewports when fixed height is used

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Public/DisplayClusterMonitorTypes.h` (Public)


#### enum `EDCMessengerRole`  
`enum class EDCMessengerRole : uint8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- desc: Roles used in the cluster monitor communication network
- L20 _public enumerator_ `ObservablesProvider` — A provider of observables data
- L22 _public enumerator_ `Monitor` — A cluster monitor

#### enum `EDCObservableType`  
`enum class EDCObservableType : uint8`  
_L30-44_
- reflection: `UENUM(BlueprintType)`
- desc: Types of resources that can be observed from outside.
- L33 _public enumerator_ `None` — Invalid/uninitialized type for validation
- L35 _public enumerator_ `Backbuffer` — Node backbuffer
- L37 _public enumerator_ `UI` — UI only
- L39 _public enumerator_ `Viewport` — Outer viewport
- L41 _public enumerator_ `ICVFXCamera` — Inner camera viewport
- L43 _public enumerator_ `ICVFXCameraTile` — Inner camera tile

#### enum `EDCControlCommand`  
`enum class EDCControlCommand : uint8`  
_L51-57_
- reflection: `UENUM(BlueprintType)`
- desc: Observable control command types
- L53 _public enumerator_ `None`
- L54 _public enumerator_ `Play`
- L55 _public enumerator_ `Pause`
- L56 _public enumerator_ `Stop`

#### enum `EDCRequestResult`  
`enum class EDCRequestResult : uint8`  
_L64-69_
- reflection: `UENUM(BlueprintType)`
- desc: Request operation result types
- L66 _public enumerator_ `NoResult`
- L67 _public enumerator_ `Ok`
- L68 _public enumerator_ `Fail`

#### struct `FDCMData_ResidenceDescriptor`  
`struct FDCMData_ResidenceDescriptor`  
_L77-106_
- reflection: `USTRUCT(BlueprintType)`
- desc: Residence of an observable Contains information on a cluster node, and the machine where it's running on
- L85 _public member_ `FGuid ClusterId;` — `UPROPERTY()` — GUID of a cluster that this cluster node belongs to
- L89 _public member_ `FGuid NodeId;` — `UPROPERTY()` — GUID of a cluster node
- L93 _public member_ `FString NodeName;` — `UPROPERTY()` — Cluster node ID
- L97 _public member_ `FString Hostname;` — `UPROPERTY()` — Hostname of a machine where this cluster node is running
- L101 _public member_ `bool bIsPrimary = false;` — `UPROPERTY()` — Whether this cluster node is primary
- L105 _public member_ `bool bIsOffscreen = false;` — `UPROPERTY()` — Whether this cluster node is running offscreen

#### struct `FDCMData_EndpointDescriptor`  
`struct FDCMData_EndpointDescriptor`  
_L113-130_
- reflection: `USTRUCT(BlueprintType)`
- desc: Descriptor of a cluster monitor endpoint
- L121 _public member_ `FGuid Id;` — `UPROPERTY()` — GUID of this endpoint
- L125 _public member_ `FString Name;` — `UPROPERTY()` — Name of this endpoint
- L129 _public member_ `TSet<EDCMessengerRole> Roles;` — `UPROPERTY()` — Set of roles that this endpoint is responsible for

#### struct `FDCEndpoint`  
`struct FDCEndpoint`  
_L137-156_
- reflection: `USTRUCT(BlueprintType)`
- desc: Endpoint information
- L145 _public member_ `FDCMData_ResidenceDescriptor Residence;` — `UPROPERTY()` — Endpoint residence
- L149 _public member_ `FDCMData_EndpointDescriptor Endpoint;` — `UPROPERTY()` — Endpoint descriptor
- L152 _public member_ `FMessageAddress Address;` — Endpoint address (local data only)
- L155 _public member_ `double LastActivityTime = 0;` — Shows how long ago this endpoint was last active (local data only)

#### struct `FDCMData_ObservableInfo`  
`struct FDCMData_ObservableInfo`  
_L163-202_
- reflection: `USTRUCT()`
- desc: Observable resource information
- L167 _public member_ `inline static const FIntPoint InvalidTilePos = { INDEX_NONE, INDEX_NONE };`
- L173 _public member_ `EDCObservableType Type = EDCObservableType::None;` — `UPROPERTY()` — Observable type
- L177 _public member_ `FGuid Id;` — `UPROPERTY()` — Observable GUID
- L181 _public member_ `FString Name;` — `UPROPERTY()` — Observable name
- L185 _public member_ `FIntPoint Resolution = FIntPoint::ZeroValue;` — `UPROPERTY()` — Observable resolution
- L189 _public member_ `FString ParentName;` — `UPROPERTY()` — Observable parent name (optional, used for tiles only)
- L193 _public member_ `FIntPoint TilePos = InvalidTilePos;` — `UPROPERTY()` — Observable tile position (optional, used for tiles only)
- L198 _public function_ `bool IsValid() const` — Validates the major data

#### struct `FDCMData_NodeObservables`  
`struct FDCMData_NodeObservables`  
_L209-230_
- reflection: `USTRUCT()`
- desc: Cluster node information
- L217 _public member_ `TArray<FDCMData_ObservableInfo> ObservablesAdded;` — `UPROPERTY()` — New sources
- L221 _public member_ `TArray<FDCMData_ObservableInfo> ObservablesUpdated;` — `UPROPERTY()` — Sources that have been modified
- L225 _public member_ `TArray<FDCMData_ObservableInfo> ObservablesRemoved;` — `UPROPERTY()` — Sources not available anymore
- L229 _public member_ `TArray<FDCMData_ObservableInfo> ObservablesUnchanged;` — `UPROPERTY()` — Sources that keep running unchanged since last evaluation

#### struct `FDCMMessageBase`  
`struct FDCMMessageBase`  
_L237-240_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base message type for any cluster monitor communication messages

#### struct `FDCMMessage_DiscoveryRequest`  
`struct FDCMMessage_DiscoveryRequest : public FDCMMessageBase`  
_L247-259_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessageBase`
- desc: Discovery request
- L254 _public member_ `FDCMData_ResidenceDescriptor Residence;` — `UPROPERTY()` — Residence of the endpoint that is sending this discovery request
- L258 _public member_ `FDCMData_EndpointDescriptor Endpoint;` — `UPROPERTY()` — Endpoint information of the sender

#### struct `FDCMMessage_DiscoveryResponse`  
`struct FDCMMessage_DiscoveryResponse : public FDCMMessageBase`  
_L266-278_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessageBase`
- desc: Discovery response
- L273 _public member_ `FDCMData_ResidenceDescriptor Residence;` — `UPROPERTY()` — Residence of the endpoint that is sending this response
- L277 _public member_ `FDCMData_EndpointDescriptor Endpoint;` — `UPROPERTY()` — Endpoint information of the responder

#### struct `FDCMMessage_Heartbeat`  
`struct FDCMMessage_Heartbeat : public FDCMMessageBase`  
_L285-289_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessageBase`
- desc: Heartbeat pulse message

#### struct `FDCMMessage_Shutdown`  
`struct FDCMMessage_Shutdown : public FDCMMessageBase`  
_L296-304_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessageBase`
- desc: Shutdown notification
- L303 _public member_ `FString Reason;` — `UPROPERTY()` — Shutdown reason info (optional)

#### struct `FDCMMessage_ExecuteConsoleCommand`  
`struct FDCMMessage_ExecuteConsoleCommand : public FDCMMessageBase`  
_L311-323_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessageBase`
- L318 _public member_ `FString ExecutorName;` — `UPROPERTY()` — Command executor to address the command to
- L322 _public member_ `FString Command;` — `UPROPERTY()` — Console command to run on the receiver side

#### struct `FDCMMessage`  
`struct FDCMMessage : public FDCMMessageBase`  
_L331-335_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessageBase`
- desc: Base message type for any custom messages

#### struct `FDCMMessage_NodeObservablesRequest`  
`struct FDCMMessage_NodeObservablesRequest : public FDCMMessage`  
_L342-346_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Request to get information aobut all available observables

#### struct `FDCMMessage_NodeObservablesResponse`  
`struct FDCMMessage_NodeObservablesResponse : public FDCMMessage`  
_L353-361_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Response with the information about all available observables
- L360 _public member_ `FDCMData_NodeObservables Observables;` — `UPROPERTY()` — Observables information

#### struct `FDCMMessage_NodeObservablesNotification`  
`struct FDCMMessage_NodeObservablesNotification : public FDCMMessage`  
_L368-376_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Broadcast notification with the information about all available observables
- L375 _public member_ `FDCMData_NodeObservables Observables;` — `UPROPERTY()` — Observables information

#### struct `FDCMMessage_StartSessionRequest`  
`struct FDCMMessage_StartSessionRequest : public FDCMMessage`  
_L383-391_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Request to start new observation session
- L390 _public member_ `FGuid ObservableId;` — `UPROPERTY()` — Observable GUID

#### struct `FDCMMessage_StartSessionResponse`  
`struct FDCMMessage_StartSessionResponse : public FDCMMessage`  
_L398-410_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Observation start response/result
- L405 _public member_ `FGuid ObservableId;` — `UPROPERTY()` — Observable GUID
- L409 _public member_ `EDCRequestResult Result = EDCRequestResult::NoResult;` — `UPROPERTY()` — Request result

#### struct `FDCMMessage_StopSessionRequest`  
`struct FDCMMessage_StopSessionRequest : public FDCMMessage`  
_L417-425_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Request to stop an observation session
- L424 _public member_ `FGuid ObservableId;` — `UPROPERTY()` — Observable GUID

#### struct `FDCMMessage_StopSessionResponse`  
`struct FDCMMessage_StopSessionResponse : public FDCMMessage`  
_L432-444_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Observation stop response/result
- L439 _public member_ `FGuid ObservableId;` — `UPROPERTY()` — Observable GUID
- L443 _public member_ `EDCRequestResult Result = EDCRequestResult::NoResult;` — `UPROPERTY()` — Request result

#### struct `FDCMMessage_ObservableControlRequest`  
`struct FDCMMessage_ObservableControlRequest : public FDCMMessage`  
_L451-463_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Observation session control command request
- L458 _public member_ `FGuid ObservableId;` — `UPROPERTY()` — Observable GUID
- L462 _public member_ `EDCControlCommand Command = EDCControlCommand::None;` — `UPROPERTY()` — Control command

#### struct `FDCMMessage_ObservableControlResponse`  
`struct FDCMMessage_ObservableControlResponse : public FDCMMessage`  
_L470-486_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDCMMessage`
- desc: Observation session control response
- L477 _public member_ `FGuid ObservableId;` — `UPROPERTY()` — Observable GUID
- L481 _public member_ `EDCControlCommand Command = EDCControlCommand::None;` — `UPROPERTY()` — Control command
- L485 _public member_ `EDCRequestResult Result = EDCRequestResult::NoResult;` — `UPROPERTY()` — Request result
