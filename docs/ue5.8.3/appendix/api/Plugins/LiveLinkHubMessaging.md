# Plugins / LiveLinkHubMessaging

- module root: `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging`
- headers: 9; symbols: 242
- symbol kinds: class=12, delegate=7, enum=5, enumerator=14, externvar=1, function=46, macro=4, member=81, namespace=4, prototype=51, struct=15, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LiveLink, LiveLinkInterface, Messaging, Settings, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: LiveLinkMessageBusFramework, TimeManagement

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Private/LiveLinkHubConnectionManager.h` (Private)


#### class `FLiveLinkHubConnectionManager`  
`class FLiveLinkHubConnectionManager`  
_L142-298_
- desc: This utitlity is meant to be run on an unreal engine instance to look for livelink hub connections and to automatically create the message bus source for it.
- L145 _public prototype_ `DECLARE_DELEGATE_RetVal(ELiveLinkTopologyMode, FOnGetTopologyMode);`
- L146 _public prototype_ `DECLARE_DELEGATE_RetVal(FLiveLinkHubInstanceId, FOnGetInstanceId);`
- L147 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDiscoveryRequest, const FMessageAddress& );`
- L150 _public function_ `FLiveLinkHubConnectionManager(ELiveLinkTopologyMode InMode, FOnGetTopologyMode OnGetTopologyMode, FOnGetInstanceId OnGetInstanceId, FOnDiscoveryRequest OnDiscoveryRequest) : GetTopologyModeDelegate(OnGetTopologyMode) , GetInstanceIdDelegate(OnGetInstanceId) , DiscoveryRequestDelegate(OnDiscoveryRequest)`
- L161 _public function_ `~FLiveLinkHubConnectionManager()`
- L178 _private function_ `void StartDiscovery()` — Add a discovery request and start polling for results.
- L191 _private function_ `FTimerManager* GetTimerManager() const` — Get the timer manager either from the editor or the current world.
- L208 _private function_ `void LookForLiveLinkHubConnection()` — Parse the poll results of the discovery manager and create a livelinkhub messagebus source if applicable.
- L240 _private function_ `void AddLiveLinkSource(const FProviderPollResultPtr& PollResult)` — Create a messagebus source
- L281 _private function_ `void PostLoadMap(UWorld*)` — Handler called when a map changes, used to register the ConnectionUpdateTimer.
- L288 _private member_ `FTimerHandle ConnectionUpdateTimer;` — Handle to the timer used to check for livelink hub providers.
- L290 _private member_ `FOnGetTopologyMode GetTopologyModeDelegate;` — Get the mode for this connection manager.
- L292 _private member_ `FOnGetInstanceId GetInstanceIdDelegate;` — Get the instance id (Only relevant if this is running inside of livelinkhub.
- L294 _private member_ `FOnDiscoveryRequest DiscoveryRequestDelegate;` — Delegate called when we've received a Pong from a LiveLinkHub instance (that's built after 5.7 to support discovery).
- L296 _private member_ `bool bEnableReconnectingToStaleSource = true;` — Whether to allow reconnecting to stale LLH sources.

#### class `FLiveLinkHubConnectionManager`  
`class FLiveLinkHubConnectionManager`  
_L300-302_
- L145 _public prototype_ `DECLARE_DELEGATE_RetVal(ELiveLinkTopologyMode, FOnGetTopologyMode);`
- L146 _public prototype_ `DECLARE_DELEGATE_RetVal(FLiveLinkHubInstanceId, FOnGetInstanceId);`
- L147 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDiscoveryRequest, const FMessageAddress& );`
- L150 _public function_ `FLiveLinkHubConnectionManager(ELiveLinkTopologyMode InMode, FOnGetTopologyMode OnGetTopologyMode, FOnGetInstanceId OnGetInstanceId, FOnDiscoveryRequest OnDiscoveryRequest) : GetTopologyModeDelegate(OnGetTopologyMode) , GetInstanceIdDelegate(OnGetInstanceId) , DiscoveryRequestDelegate(OnDiscoveryRequest)`
- L161 _public function_ `~FLiveLinkHubConnectionManager()`
- L178 _private function_ `void StartDiscovery()` — Add a discovery request and start polling for results.
- L191 _private function_ `FTimerManager* GetTimerManager() const` — Get the timer manager either from the editor or the current world.
- L208 _private function_ `void LookForLiveLinkHubConnection()` — Parse the poll results of the discovery manager and create a livelinkhub messagebus source if applicable.
- L240 _private function_ `void AddLiveLinkSource(const FProviderPollResultPtr& PollResult)` — Create a messagebus source
- L281 _private function_ `void PostLoadMap(UWorld*)` — Handler called when a map changes, used to register the ConnectionUpdateTimer.
- L288 _private member_ `FTimerHandle ConnectionUpdateTimer;` — Handle to the timer used to check for livelink hub providers.
- L290 _private member_ `FOnGetTopologyMode GetTopologyModeDelegate;` — Get the mode for this connection manager.
- L292 _private member_ `FOnGetInstanceId GetInstanceIdDelegate;` — Get the instance id (Only relevant if this is running inside of livelinkhub.
- L294 _private member_ `FOnDiscoveryRequest DiscoveryRequestDelegate;` — Delegate called when we've received a Pong from a LiveLinkHub instance (that's built after 5.7 to support discovery).
- L296 _private member_ `bool bEnableReconnectingToStaleSource = true;` — Whether to allow reconnecting to stale LLH sources.

#### Free symbols / members of external scopes

- L30 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogLiveLinkHubConnectionManager, Log, All);`
- L32 _namespace_ `namespace LiveLinkHubConnectionManager`
- L35 _prototype_ `template <typename T> concept CHasAnnotations = requires(const T& t)` (scope `LiveLinkHubConnectionManager`)
- L37 _function_ `static void SendAnalyticsConnectionEstablished()` (scope `LiveLinkHubConnectionManager`)
- L47 _function_ `static ELiveLinkTopologyMode GetPollResultTopologyMode(const FProviderPollResultPtr& PollResult)` (scope `LiveLinkHubConnectionManager`)
- L73 _function_ `template<CHasAnnotations T> static bool CanConnectTo(const FString& MachineName, const T& ObjectWithAnnotations, const FLiveLinkHubInstanceId& InstanceId)` (scope `LiveLinkHubConnectionManager`)
- L112 _function_ `static bool ShouldAcceptConnectionFrom(ELiveLinkTopologyMode InHostMode, const FProviderPollResultPtr& InPollResult, const FLiveLinkHubInstanceId& InstanceId)` (scope `LiveLinkHubConnectionManager`) — Returns whether this connection manager should accept connection requests from this poll result.
- L138 _delegate_ `DECLARE_DELEGATE_RetVal(ELiveLinkTopologyMode, FGetTopologyMode);`
- L138 _prototype_ `DECLARE_DELEGATE_RetVal(ELiveLinkTopologyMode, FGetTopologyMode);`
- L139 _delegate_ `DECLARE_DELEGATE_RetVal(FLiveLinkHubInstanceId, FGetInstanceId);`
- L139 _prototype_ `DECLARE_DELEGATE_RetVal(FLiveLinkHubInstanceId, FGetInstanceId);`
- L145 _delegate_ `DECLARE_DELEGATE_RetVal(ELiveLinkTopologyMode, FOnGetTopologyMode);`
- L146 _delegate_ `DECLARE_DELEGATE_RetVal(FLiveLinkHubInstanceId, FOnGetInstanceId);`
- L147 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDiscoveryRequest, const FMessageAddress& );`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Private/LiveLinkHubControlChannel.h` (Private)


#### class `FLiveLinkHubControlChannel`  
`class FLiveLinkHubControlChannel : public TSharedFromThis<FLiveLinkHubControlChannel>`  
_L23-534_
- inherits: `TSharedFromThis<FLiveLinkHubControlChannel>`
- desc: Utility class that acts as a bridge between a LiveLinkHub Provider and a UE Client (or LLH instance) while handling backwards compatibility with previous versions of LLH Provider. The control channel can be set in Global mode, where it acts as a
- L34 _public member_ `EChannelMode ChannelMode;` — What mode this channel is acting in.
- L37 _public function_ `FLiveLinkHubControlChannel(EChannelMode InChannelMode) : ChannelMode(InChannelMode)`
- L42 _public function_ `~FLiveLinkHubControlChannel()`
- L48 _public function_ `void Initialize(FGuid SourceId = FGuid())` — Initializes the endpoint (when in Global mode) and registers callbacks.
- L80 _public function_ `void SetEndpoint(TSharedPtr<FMessageEndpoint> InEndpoint)` — Overrides the endpoint, allows LLHMessageBusSource to pass messages using its own endpoint.
- L86 _public function_ `FMessageAddress GetAddress() const` — Get the address of the MessageEndpoint held by this channel.
- L98 _public function_ `void InitializeMessageEndpoint(FMessageEndpoint::Builder& Builder)` — Registers the necessary handlers with the endpoint builder.
- L141 _public function_ `void SendBeacon(const FMessageAddress& RemoteAddress) const` — Informs a LLH instance that this endpoint exists in order to create an entry in their MessageBus AddressBook.
- L159 _public function_ `void OnSourceShutdown(const TSharedPtr<FLiveLinkHubMessageBusSource>& InSource)` — Called by FLiveLinkHubMessageBusSource to ensure we disconnect the remote provider when that source is shutdown. @note We can't use the LiveLink OnSourceRemoved because the source ptr would be invalid by then.
- L180 _public function_ `FLiveLinkClientInfoMessage CreateLiveLinkClientInfo() const` — Gather information about this client to put in a client info struct.
- L214 _public typedef_ `using FAuxRequestDelegate = TTSDelegate<bool(const FLiveLinkHubAuxChannelRequestMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext)>;` — Returning false from this delegate will respond to the sender with FLiveLinkHubAuxChannelRejectMessage.
- L215 _public member_ `FAuxRequestDelegate OnAuxRequest;`
- L219 _private function_ `void Shutdown()` — Unregister callbacks.
- L234 _private function_ `FGuid FindStaleLiveLinkHubSource(const FLiveLinkHubDiscoveryMessage& IncomingMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) const` — Checks if an incoming LiveLinkHub discovery should replace existing sources. Returns the GUID of any existing source that should be removed, or invalid GUID if none. This method is only called after confirming the incoming connection is a LiveLinkHub provider.
- L286 _private function_ `template <typename MessageType> void Handle(const MessageType& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Templated method to dispatch messages using template specialization.
- L293 _private function_ `template <> void Handle(const FLiveLinkHubDisconnectMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Handle message telling this source to disconnect.
- L311 _private function_ `template <> void Handle(const FLiveLinkHubCustomTimeStepSettings& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Handle a custom time step settings message and update the engine's custom time step settings accordingly.
- L318 _private function_ `template <> void Handle(const FLiveLinkHubTimecodeSettings& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Handle a timecode settings message and update the engine's timecode settings accordingly.
- L325 _private function_ `template <> void Handle(const FLiveLinkHubSourceEvaluationModeMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Handle a source evaluation mode message — apply the hub's preferred mode to the relevant hub source(s) on this client.
- L371 _private function_ `template <> void Handle(const FLiveLinkHubDiscoveryMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Handle a FLiveLinkHubDiscoveryMessage settings message and update the engine's timecode settings accordingly.
- L491 _private function_ `template<> void Handle(const FLiveLinkHubAuxChannelRequestMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext)` — Handle aux channel requests by delegating to the provided callback.
- L510 _private function_ `void OnMapChanged(UWorld* World, EMapChangeType ChangeType)` — Handler called on map changed to update the livelink hub.
- L518 _private member_ `TSharedPtr<FMessageEndpoint> Endpoint;` — MessageBus endpoint used to transmit control messages.
- L521 _private member_ `TSet<FGuid> DisconnectingSources;` — Track sources in the process of disconnecting.
- L524 _private member_ `FString Hostname = FPlatformProcess::ComputerName();` — Name of this machine.
- L527 _private member_ `TArray<FMessageAddress> TrackedProviders;` — List of providers we've discovered.
- L530 _private member_ `FGuid CachedSourceId;` — When acting in Source mode, this is the ID of the source that owns this channel.
- L533 _private member_ `bool bInitialized = false;` — Flag to prevent initializing channel that's already initialized.

#### enum `FLiveLinkHubControlChannel::EChannelMode`  
`enum class EChannelMode : uint8`  
_L27-31_
- desc: Defines the operational mode of control channel.
- L29 _public enumerator_ `Global` — Channel is owned by LiveLinkHubMessagingModule and handles all control messages directly.
- L30 _public enumerator_ `Source` — Channel is owned by a LiveLinkHubMessageBusSource to support the V1 Discovery Protocol.

#### Free symbols / members of external scopes

- L111 _function_ `` (scope `FLiveLinkHubControlChannel::InitializeMessageEndpoint`)
- L334 _function_ `` (scope `FLiveLinkHubControlChannel::Handle`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Private/LiveLinkHubMessageBusSource.h` (Private)


#### class `FLiveLinkHubMessageBusSource`  
`class FLiveLinkHubMessageBusSource : public FLiveLinkMessageBusSource, public TSharedFromThis<FLiveLinkHubMessageBusSource>`  
_L13-48_
- inherits: `FLiveLinkMessageBusSource,TSharedFromThis<FLiveLinkHubMessageBusSource>`
- desc: LiveLink Message bus source that is connected to a livelink hub.
- L16 _public prototype_ `FLiveLinkHubMessageBusSource(const FText& InSourceType, const FText& InSourceMachineName, const FMessageAddress& InConnectionAddress, double InMachineTimeOffset, int32 InDiscoveryProtocolVersion = 2);`
- L18 _public function_ `FGuid GetSourceId() const` — Get the ID for this source. Only valid after ReceiveClient has been invoked.
- L20 _public function_ `FMessageAddress GetConnectionAddress() const` — Get the address of the connected provider.
- L22 _public function_ `void SetControlChannel(TSharedPtr<FLiveLinkHubControlChannel> InControlChannel)` — The control channel to use for sending control messages to the provider.
- L26 _protected prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L27 _protected prototype_ `virtual void InitializeAndPushStaticData_AnyThread(FName SubjectName, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkSubjectKey& SubjectKey, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, UScriptStruct* MessageTypeInfo) override;`
- L28 _protected prototype_ `virtual double GetDeadSourceTimeout() const override;`
- L29 _protected function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override`
- L30 _protected prototype_ `virtual bool RequestSourceShutdown() override;`
- L32 _protected prototype_ `virtual void InitializeMessageEndpoint(FMessageEndpointBuilder& EndpointBuilder);` — This lets child classes the opportunity to add custom message handlers to the endpoint builder
- L33 _protected prototype_ `virtual void PostInitializeMessageEndpoint(const TSharedPtr<FMessageEndpoint>& Endpoint);`
- L37 _protected prototype_ `virtual void SendConnectMessage() override;` — Send connect message to the provider and start the heartbeat emitter
- L41 _private member_ `FMessageAddress CachedConnectionAddress;` — Cached ConnectionAddress that stays valid after a call to RequestSourceShutdown.
- L44 _private member_ `TSharedPtr<FLiveLinkHubControlChannel> ControlChannel;` — Used to communicate with a LLH provider built before 5.7.
- L47 _private member_ `int32 DiscoveryProtocolVersion = 2;` — Keeps track of what discovery protocol the connected provider is using.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Private/LiveLinkHubMessageBusSourceFactory.h` (Private)


#### class `ULiveLinkHubMessageBusSourceFactory`  
`class ULiveLinkHubMessageBusSourceFactory : public ULiveLinkMessageBusSourceFactory`  
_L15-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULiveLinkMessageBusSourceFactory`
- L21 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L22 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L23 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L24 _public prototype_ `virtual bool IsEnabled() const override;`
- L29 _protected prototype_ `virtual TSharedPtr<class FLiveLinkMessageBusSource> MakeSource(const FText& Name, const FText& MachineName, const FMessageAddress& Address, double TimeOffset) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKHUBMESSAGING_API`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Private/LiveLinkHubMessagingModule.h` (Private)


#### class `FLiveLinkHubMessagingModule`  
`class FLiveLinkHubMessagingModule : public ILiveLinkHubMessagingModule`  
_L18-92_
- inherits: `ILiveLinkHubMessagingModule`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public function_ `virtual FOnHubConnectionEstablished& OnConnectionEstablished() override`
- L33 _public prototype_ `virtual void SetHostTopologyMode(ELiveLinkTopologyMode InMode) override;`
- L34 _public prototype_ `virtual FLiveLinkHubInstanceId GetInstanceId() const override;`
- L35 _public prototype_ `virtual void SetInstanceId(const FLiveLinkHubInstanceId& Id) override;`
- L36 _public prototype_ `virtual ELiveLinkTopologyMode GetHostTopologyMode() const override;`
- L37 _public prototype_ `virtual bool RegisterAuxChannelRequestHandler(UScriptStruct* InRequestTypeStruct, FAuxChannelRequestHandlerFunc&& InHandlerFunc) override;`
- L38 _public prototype_ `virtual bool UnregisterAuxChannelRequestHandler(UScriptStruct* InRequestTypeStruct) override;`
- L42 _public prototype_ `TSharedPtr<class FLiveLinkHubControlChannel> GetControlChannel();` — Used by the LiveLinkHubMessageBusSource to acquire a control channel when it's created.
- L49 _private prototype_ `bool OnFilterMessageBusSource(UClass* FactoryClass, TSharedPtr<struct FProviderPollResult, ESPMode::ThreadSafe> PollResult);` — Note: Invoked on the UI (Game) thread. Filter invoked by the messagebus source factory to filter out sources in the creation panel.
- L52 _private prototype_ `void OnDiscoveryRequest(const struct FMessageAddress& RemoteAddress) const;` — Handle a discovery request from LLH to populate its address book with the ControlEndpoint's address.
- L55 _private prototype_ `bool OnAuxRequest(const FLiveLinkHubAuxChannelRequestMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Handle aux channel request messages.
- L58 _private prototype_ `void RegisterSettings();` — Register settings related to LiveLinkHub messaging.
- L61 _private prototype_ `void UnregisterSettings();` — Unregister settings related to LiveLinkHub messaging.
- L64 _private member_ `bool bUseConnectionManager;`
- L68 _private member_ `TPimplPtr<FLiveLinkHubConnectionManager> ConnectionManager;` — Manages the connection to the live link hub.
- L72 _private member_ `FDelegateHandle SourceFilterDelegate;` — Handle to the delegate used to filter message bus sources.
- L75 _private member_ `FOnHubConnectionEstablished ConnectionEstablishedDelegate;` — Delegate called when the connection between a livelink hub and the editor is established.
- L78 _private member_ `mutable FCriticalSection InstanceInfoLock;` — Lock to access the instance info struct.
- L86 _private member_ `} InstanceInfo;`
- L89 _private member_ `TSharedPtr<class FLiveLinkHubControlChannel> ControlChannel;` — Control channel used to communicate with LLH Providers built on 5.7+.
- L91 _private member_ `TMap<const UScriptStruct*, FAuxChannelRequestHandlerFunc> AuxChannelRequestHandlers;`

#### struct `FLiveLinkHubMessagingModule::FInstanceInfo`  
`struct FInstanceInfo`  
_L80-86_
- L83 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::Hub;` — Topology Mode for this host.
- L85 _public member_ `FLiveLinkHubInstanceId Id = FLiveLinkHubInstanceId(FGuid());` — Instance ID for this host.

#### Free symbols / members of external scopes

- L11 _macro_ `#define WITH_LIVELINK_DISCOVERY_MANAGER_THREAD 1`

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Public/ILiveLinkHubMessagingModule.h` (Public)


#### class `FLiveLinkHubInstanceId`  
`class FLiveLinkHubInstanceId`  
_L25-36_
- L28 _public prototype_ `explicit FLiveLinkHubInstanceId(FGuid Guid);`
- L29 _public prototype_ `explicit FLiveLinkHubInstanceId(FStringView NamedId);`
- L31 _public prototype_ `FString ToString() const;`
- L35 _private member_ `TVariant<FGuid, FString> Id;` — Variant holding the actual instance ID.

#### class `ILiveLinkHubMessagingModule`  
`class ILiveLinkHubMessagingModule : public IModuleInterface`  
_L39-94_
- inherits: `IModuleInterface`
- L43 _public prototype_ `virtual FOnHubConnectionEstablished& OnConnectionEstablished() = 0;` — Delegate called when a connection is established to a livelink hub.
- L46 _public prototype_ `virtual void SetHostTopologyMode(ELiveLinkTopologyMode InMode) = 0;` — Set the topology mode for this host. This will dictate to what apps it can connect to.
- L49 _public prototype_ `virtual ELiveLinkTopologyMode GetHostTopologyMode() const = 0;` — Get the topology mode for this host.
- L52 _public prototype_ `virtual void SetInstanceId(const FLiveLinkHubInstanceId& Id) = 0;` — Set the instance ID for this connection manager, used to detect if it's trying to connect to itself.
- L55 _public prototype_ `virtual FLiveLinkHubInstanceId GetInstanceId() const = 0;` — Get the ID for this running instance. Returns an empty guid if this isn't running as part of LiveLinkHub.
- L57 _public typedef_ `using FAuxChannelRequestHandlerFunc = TUniqueFunction<void( const FLiveLinkHubAuxChannelRequestMessage&, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& )>;`
- L64 _public function_ `template<typename RequestType UE_REQUIRES(std::is_base_of_v<FLiveLinkHubAuxChannelRequestMessage, RequestType>)> bool RegisterAuxChannelRequestHandler(TUniqueFunction<void(const RequestType&, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)>&& InHandlerFunc)` — Register a callback to be invoked when a peer attempts to negotiate an auxiliary endpoint.
- L83 _public function_ `template<typename RequestType UE_REQUIRES(std::is_base_of_v<FLiveLinkHubAuxChannelRequestMessage, RequestType>)> bool UnregisterAuxChannelRequestHandler()` — Unregister an existing auxiliary endpoint handler.
- L89 _public prototype_ `virtual bool RegisterAuxChannelRequestHandler(UScriptStruct* InRequestTypeStruct, FAuxChannelRequestHandlerFunc&& InHandlerFunc) = 0;` — Register a callback to be invoked when a peer attempts to negotiate an auxiliary endpoint.
- L92 _public prototype_ `virtual bool UnregisterAuxChannelRequestHandler(UScriptStruct* InRequestTypeStruct) = 0;` — Unregister an existing auxiliary endpoint handler.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LIVELINKHUBMESSAGING_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHubConnectionEstablished, FGuid SourceId);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHubConnectionEstablished, FGuid SourceId);`
- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubMessaging, Display, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubMessaging, Display, All);`
- L74 _function_ `` (scope `ILiveLinkHubMessagingModule::RegisterAuxChannelRequestHandler`)

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Public/LiveLinkHubMessageBusSourceSettings.h` (Public)


#### class `ULiveLinkHubMessageBusSourceSettings`  
`class ULiveLinkHubMessageBusSourceSettings : public ULiveLinkMessageBusSourceSettings`  
_L11-15_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULiveLinkMessageBusSourceSettings`
- desc: Class used to allow customizing the default behavior of LiveLinkHub sources and more generally to allow quickly identifying if a source is a LLH instance.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Public/LiveLinkHubMessages.h` (Public)


#### enum `ELiveLinkHubAutoConnectMode`  
`enum class ELiveLinkHubAutoConnectMode : uint8`  
_L23-28_
- reflection: `UENUM()`
- desc: Whether if and how LiveLinkHub should auto-connect to UE clients on the network.
- L25 _public enumerator_ `Disabled UMETA(ToolTip = "Don't add any clients automatically.")`
- L26 _public enumerator_ `All UMETA(ToolTip = "Add any client that was found on the network, unless it doesn't match one of the filters.")`
- L27 _public enumerator_ `LocalOnly UMETA(ToolTip = "Add any client running on this machine, overriding any current filter.")`

#### struct `FLiveLinkHubMessageAnnotation`  
`struct FLiveLinkHubMessageAnnotation`  
_L33-52_
- desc: List of LiveLinkHub annotations.
- L39 _public member_ `static FName ProviderTypeAnnotation;` — Annotation put on MessageBus messages to indicate the type of provider used. Absence of provider type means that the message comes from a regular LiveLinkProvider.
- L42 _public member_ `static FName AutoConnectModeAnnotation;` — Annotation to indicate if this source should be automatically added to the list of LiveLink sources.
- L45 _public member_ `static FName IdAnnotation;` — Instance ID annotation used to identify the running LLH instance.
- L51 _public member_ `static FName ExplicitConnectAnnotation;` — Marks a discovery message as a user-driven explicit connect request (e.g. clicking an entry in the LLH "Add Client" menu). Receivers honoring this annotation must bypass the AutoConnect filter so the connection proceeds even when AutoConnect is Disabled.

#### class `ULiveLinkHubCustomTimeStep`  
`class ULiveLinkHubCustomTimeStep : public ULiveLinkCustomTimeStep`  
_L61-64_
- reflection: `UCLASS(Hidden)`
- inherits: `ULiveLinkCustomTimeStep`

#### class `ULiveLinkHubTimecodeCustomTimeStep`  
`class ULiveLinkHubTimecodeCustomTimeStep : public UTimecodeCustomTimeStep`  
_L67-70_
- reflection: `UCLASS(Hidden)`
- inherits: `UTimecodeCustomTimeStep`

#### enum `ELiveLinkHubCustomTimeStepKind`  
`enum class ELiveLinkHubCustomTimeStepKind : uint8`  
_L74-82_
- reflection: `UENUM()`
- desc: Kind of custom time step the hub is asking the editor client to apply.
- L77 _public enumerator_ `Reset` — No hub-owned custom time step should be active.
- L79 _public enumerator_ `LiveLink` — Client should construct a ULiveLinkHubCustomTimeStep from the LiveLink fields.
- L81 _public enumerator_ `Timecode` — Client should construct a ULiveLinkHubTimecodeCustomTimeStep from the Timecode fields.

#### struct `FLiveLinkHubCustomTimeStepSettings`  
`struct FLiveLinkHubCustomTimeStepSettings`  
_L85-134_
- reflection: `USTRUCT()`
- L91 _public member_ `bool bResetCustomTimeStep = false;` — `UPROPERTY()` — If this is true, the engine custom time step will be reset. Kept in sync with Kind == Reset.
- L95 _public member_ `ELiveLinkHubCustomTimeStepKind Kind = ELiveLinkHubCustomTimeStepKind::Reset;` — `UPROPERTY()` — Which concrete custom time step class the receiver should construct.
- L99 _public member_ `bool bLockStepMode = true;` — `UPROPERTY()` — Corresponds to the lock step mode in ULiveLinkCustomTimeStep. Used when Kind == LiveLink.
- L103 _public member_ `uint32 FrameRateDivider = 1;` — `UPROPERTY()` — Corresponds to the frame rate divider in ULiveLinkCustomTimeStep. Used when Kind == LiveLink.
- L107 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY()` — If we are locking the editor frame rate to the subject then this property holds that subject name. Used when Kind == LiveLink.
- L111 _public member_ `FFrameRate CustomTimeStepRate = FFrameRate(60, 1);` — `UPROPERTY()` — Desired frame rate to lock the editor. This corresponds to the LiveLinkDataRate in ULiveLinkCustomTimeStep. Used when Kind == LiveLink.
- L115 _public member_ `bool bErrorIfFrameAreNotConsecutive = false;` — `UPROPERTY()` — Corresponds to bErrorIfFrameAreNotConsecutive in UTimecodeCustomTimeStep. Used when Kind == Timecode.
- L119 _public member_ `bool bErrorIfTimecodeProviderChanged = false;` — `UPROPERTY()` — Corresponds to bErrorIfTimecodeProviderChanged in UTimecodeCustomTimeStep. Used when Kind == Timecode.
- L123 _public member_ `bool bIgnoreSubframes = false;` — `UPROPERTY()` — Corresponds to bIgnoreSubframes in UTimecodeCustomTimeStep. Used when Kind == Timecode.
- L127 _public member_ `float MaxDeltaTime = 0.5f;` — `UPROPERTY()` — Corresponds to MaxDeltaTime in UTimecodeCustomTimeStep. Used when Kind == Timecode.
- L130 _public prototype_ `void AssignCustomTimeStepToEngine() const;` — Assign the frame lock settings to the engine.
- L133 _public prototype_ `static FLiveLinkHubCustomTimeStepSettings FromCustomTimeStep(const UEngineCustomTimeStep* InCustomTimeStep);` — Create settings from a UEngineCustomTimeStep object. Returns reset settings if the object is null or not a supported type.

#### enum `ELiveLinkHubTimecodeSource`  
`enum class ELiveLinkHubTimecodeSource`  
_L137-147_
- reflection: `UENUM()`
- L140 _public enumerator_ `NotDefined` — Not defined by the Hub and thus should use the default system settings.
- L143 _public enumerator_ `SystemTimeEditor` — Using system time of the editor.
- L146 _public enumerator_ `UseSubjectName` — Using the provided subject name

#### struct `FLiveLinkHubTimecodeSettings`  
`struct FLiveLinkHubTimecodeSettings`  
_L151-194_
- reflection: `USTRUCT()`
- desc: Special message to communicate / override time code used by the connected editor.
- L157 _public member_ `ELiveLinkHubTimecodeSource Source = ELiveLinkHubTimecodeSource::NotDefined;` — `UPROPERTY()` — Source time code value.  If it is not defined then we use the default time code provider in the engine.
- L161 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY()` — Name of the subject to map timecode if Source == ELiveLinkHubTimecodeSource::UseSubjectName
- L165 _public member_ `FFrameRate DesiredFrameRate = FFrameRate(60, 1);` — `UPROPERTY()` — Desired frame rate to set if Source == ELiveLinkHubTimecodeSource::SystemTimeEditor.
- L172 _public member_ `float FrameDelay = 0.f;` — `UPROPERTY()` — Number of frames to subtract from the qualified frame time when GetDelayedQualifiedFrameTime or GetDelayedTimecode is called. @see GetDelayedQualifiedFrameTime, GetDelayedTimecode
- L176 _public member_ `int32 BufferSize = 2;` — `UPROPERTY()` — The number of frame to keep in memory. The provider will not be synchronized until the buffer is full at least once.
- L183 _public member_ `ELiveLinkTimecodeProviderEvaluationType EvaluationType = ELiveLinkTimecodeProviderEvaluationType::Latest;` — `UPROPERTY()` — How timecode should be evaluated. @Note: This will be overridden while a Live Link Hub recording is playing.
- L187 _public member_ `TOptional<ELiveLinkTimecodeProviderEvaluationType> OverrideEvaluationType;` — `UPROPERTY(Transient)` — If set, this will override the timecode evaluation type.
- L190 _public prototype_ `void AssignTimecodeSettingsAsProviderToEngine() const;` — Assign the settings to a new timecode provider and override the current engine settings.
- L193 _public prototype_ `static FLiveLinkHubTimecodeSettings FromTimecodeProvider(const UTimecodeProvider* InTimecodeProvider);` — Create settings from a UTimecodeProvider object. Returns NotDefined settings if the object is null or not a supported type.

#### struct `FLiveLinkHubSourceEvaluationModeMessage`  
`struct FLiveLinkHubSourceEvaluationModeMessage`  
_L201-215_
- reflection: `USTRUCT()`
- desc: Sent by LiveLinkHub to override the evaluation mode of the hub Live Link source on the connected client. The hub's preferred mode is authoritative: the client overwrites any local Mode on its hub source settings.
- L207 _public member_ `ELiveLinkSourceMode Mode = ELiveLinkSourceMode::EngineTime;` — `UPROPERTY()` — Mode to apply on the client's hub Live Link source(s).
- L214 _public member_ `FGuid SourceGuid;` — `UPROPERTY()` — Target source to apply the mode to on the client. If invalid, the client applies the mode to every hub source reachable from the sender of this message.

#### enum `ELiveLinkClientStatus`  
`enum class ELiveLinkClientStatus`  
_L219-224_
- reflection: `UENUM()`
- desc: Status of a UE client connected to a live link hub.
- L221 _public enumerator_ `Connected`
- L222 _public enumerator_ `Disconnected` — Connected,   Default state of a UE client.
- L223 _public enumerator_ `Recording` — Disconnected,   Client is not connected to the hub.

#### struct `FLiveLinkClientInfoMessage`  
`struct FLiveLinkClientInfoMessage`  
_L228-263_
- reflection: `USTRUCT()`
- desc: Information related to an unreal client that is connecting to a livelink hub instance.
- L234 _public member_ `FString LongName;` — `UPROPERTY()` — Full name used to identify this client. (ie.UEFN_sessionID_LDN_WSYS_9999)
- L238 _public member_ `ELiveLinkClientStatus Status = ELiveLinkClientStatus::Disconnected;` — `UPROPERTY()` — Status of the client, ie. is it actively doing a take record at the moment?
- L242 _public member_ `FString Hostname;` — `UPROPERTY()` — Name of the host of the UE client
- L246 _public member_ `FString ProjectName;` — `UPROPERTY()` — Name of the current project.
- L250 _public member_ `FString CurrentLevel;` — `UPROPERTY()` — Name of the current level opened.
- L254 _public member_ `FString LiveLinkInstanceName;` — `UPROPERTY()` — If this is representing a LiveLinkHub instance in Hub mode, this holds the LiveLink provider name, otherwise it's empty.
- L258 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::UnrealClient;` — `UPROPERTY()` — Whether the client is a hub or an unreal instance.
- L262 _public member_ `int32 LiveLinkVersion = ILiveLinkClient::LIVELINK_VERSION;` — `UPROPERTY()` — LiveLink Version in use by this client.

#### struct `FLiveLinkHubConnectMessage`  
`struct FLiveLinkHubConnectMessage`  
_L267-282_
- reflection: `USTRUCT()`
- desc: Special connection message used when connecting to a livelink hub that contains information about this client.
- L273 _public member_ `FLiveLinkClientInfoMessage ClientInfo;` — `UPROPERTY()` — Client information to forward to the hub
- L277 _public member_ `FString ControlEndpoint;` — `UPROPERTY()` — MessageBus Address of the control endpoint (Address of the LiveLinkHubMessagingModule's ControlChannel).
- L281 _public member_ `FGuid SourceGuid;` — `UPROPERTY()` — ID of the message bus source.

#### struct `FLiveLinkHubBeaconMessage`  
`struct FLiveLinkHubBeaconMessage`  
_L286-309_
- reflection: `USTRUCT()`
- desc: Sent by UE/LLH to LLH instances to force them to populate their MessageBus AddressBook with the ControlEndpoint's address.
- L292 _public member_ `ELiveLinkTopologyMode TopologyMode = ELiveLinkTopologyMode::Hub;` — `UPROPERTY()` — Mode of the client that's sending this message.
- L296 _public member_ `FString Hostname = FPlatformProcess::ComputerName();` — `UPROPERTY()` — Name of the machine that sent the beacon.
- L300 _public member_ `FString ProjectName;` — `UPROPERTY()` — Name of the project of the client sending this message.
- L304 _public member_ `FString LevelName;` — `UPROPERTY()` — Name of the level of the client sending this message.
- L308 _public member_ `FGuid InstanceId = FApp::GetInstanceId();` — `UPROPERTY()` — Unique ID for a given client process.

#### struct `FLiveLinkHubDisconnectMessage`  
`struct FLiveLinkHubDisconnectMessage`  
_L313-329_
- reflection: `USTRUCT()`
- desc: Special connection message used to tell a UE client or Hub that they should disconnect themselves.
- L319 _public member_ `FString ProviderName;` — `UPROPERTY()` — Name of the provider to disconnect.
- L323 _public member_ `FString MachineName;` — `UPROPERTY()` — Name of the machine that hosts the provider.
- L327 _public member_ `FGuid SourceGuid;` — `UPROPERTY()` — Id of the source to disconnect.

#### struct `FLiveLinkHubDiscoveryMessage`  
`struct FLiveLinkHubDiscoveryMessage`  
_L333-374_
- reflection: `USTRUCT()`
- desc: Discovery message used by LiveLinkHubConnectionManager to find providers to connect to.
- L337 _public prototype_ `FLiveLinkHubDiscoveryMessage() = default;`
- L339 _public function_ `FLiveLinkHubDiscoveryMessage(FString InProviderName, ELiveLinkTopologyMode InMode, const FLiveLinkHubInstanceId& InInstanceId) : ProviderName(MoveTemp(InProviderName)) , Mode(InMode) , InstanceId(InInstanceId.ToString()) , DiscoveryProtocolVersion(2)`
- L349 _public member_ `FString ProviderName;` — `UPROPERTY()` — Name of the provider to connect.
- L353 _public member_ `ELiveLinkTopologyMode Mode = ELiveLinkTopologyMode::Hub;` — `UPROPERTY()` — Name of the provider to connect.
- L357 _public member_ `FString MachineName = FPlatformProcess::ComputerName();` — `UPROPERTY()` — Name of the machine that hosts the provider.
- L361 _public member_ `FString InstanceId;` — `UPROPERTY()` — Unique ID for this provider.
- L365 _public member_ `double CreationTime = FPlatformTime::Seconds();` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — Creation time used to calculate the machine time offset.
- L369 _public member_ `int32 LiveLinkVersion = ILiveLinkClient::LIVELINK_VERSION;` — `UPROPERTY()` — LiveLink Version in use by this client.
- L373 _public member_ `int32 DiscoveryProtocolVersion = 1;` — `UPROPERTY()` — LiveLink Discovery Protocol Version in use. Defaults to 1 when deserializing for backwards compatibility.

#### struct `FLiveLinkHubAuxChannelBaseMessage`  
`struct FLiveLinkHubAuxChannelBaseMessage`  
_L378-389_
- reflection: `USTRUCT()`
- desc: Base for control messages for negotiating auxiliary channel endpoints.
- L384 _public member_ `int32 AuxProtocolVersion = 1;` — `UPROPERTY()` — Aux channel version.
- L388 _public member_ `FGuid ChannelId;` — `UPROPERTY()` — Identifier for the channel.

#### struct `FLiveLinkHubAuxChannelRequestMessage`  
`struct FLiveLinkHubAuxChannelRequestMessage : public FLiveLinkHubAuxChannelBaseMessage`  
_L399-402_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkHubAuxChannelBaseMessage`
- desc: Sent to LLH control endpoint to negotiate additional auxiliary endpoints. Subclass this struct to specialize it for your channel type, then: 1) Register a handler for your derived channel request type via ILiveLinkHubMessagingModule::RegisterAuxChannelRequestHandler. 2) Send a channel request via ILiveLinkHubClientsModel::RequestAuxiliaryChannel.

#### struct `FLiveLinkHubAuxChannelAcceptMessage`  
`struct FLiveLinkHubAuxChannelAcceptMessage : public FLiveLinkHubAuxChannelBaseMessage`  
_L406-409_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkHubAuxChannelBaseMessage`
- desc: Send this from your aux channel handler in response to an accepted request.

#### struct `FLiveLinkHubAuxChannelRejectMessage`  
`struct FLiveLinkHubAuxChannelRejectMessage : public FLiveLinkHubAuxChannelBaseMessage`  
_L416-419_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkHubAuxChannelBaseMessage`
- desc: Send this from your aux channel handler in response to a rejected request. Also sent by the framework if no handler was registered for the request type.

#### struct `FLiveLinkHubAuxChannelCloseMessage`  
`struct FLiveLinkHubAuxChannelCloseMessage : public FLiveLinkHubAuxChannelBaseMessage`  
_L423-426_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkHubAuxChannelBaseMessage`
- desc: Send this to close an existing aux channel.

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API LIVELINKHUBMESSAGING_API`
- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace LiveLinkHub` (scope `UE`)
- L54 _namespace_ `namespace Private` (scope `UE::LiveLinkHub`)
- L57 _externvar_ `extern const FName LiveLinkHubProviderType;` (scope `UE::LiveLinkHub::Private`) — LiveLink Hub provider type used to identify messages coming from a LiveLinkProvider that lives on a LiveLink Hub.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Public/LiveLinkHubMessagingSettings.h` (Public)


#### class `ULiveLinkHubMessagingSettings`  
`class ULiveLinkHubMessagingSettings : public UObject`  
_L14-114_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the messaging protocol of LiveLinkHub.
- L20 _public function_ `ULiveLinkHubMessagingSettings()`
- L44 _public member_ `bool bAllowReceivingFromUnreal = false;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkHub")` — Whether to allow the hub to receive LiveLink data from an unreal instance. (Useful if Unreal is using Live Link Broadcast components)
- L48 _public function_ `virtual void PostInitProperties() override`
- L62 _public function_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)`
- L86 _public function_ `bool CanReceiveFrom(ELiveLinkTopologyMode LHSMode, ELiveLinkTopologyMode RHSMode) const` — Whether an instance with the LHS mode can act as a Source for the RHS mode instance.
- L95 _public function_ `bool CanTransmitTo(ELiveLinkTopologyMode LHSMode, ELiveLinkTopologyMode RHSMode) const` — Whether an instance with the LHS mode can act as a Provider for the RHS mode instance.
- L107 _private member_ `TMultiMap<ELiveLinkTopologyMode, ELiveLinkTopologyMode> CanReceiveFrom_Map;` — Map of possible connections. Left side can receive a connection from right side.
- L113 _private member_ `TMultiMap<ELiveLinkTopologyMode, ELiveLinkTopologyMode> CanTransmitTo_Map;` — Map of possible connections. Left side can transmit data to a client from right side.
