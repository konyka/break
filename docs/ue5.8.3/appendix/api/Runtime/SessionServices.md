# Runtime / SessionServices

- module root: `Source/Runtime/SessionServices`
- headers: 14; symbols: 374
- symbol kinds: class=13, delegate=18, enum=2, enumerator=12, function=30, member=108, prototype=180, struct=10, typedef=1
- PrivateDependencyModuleNames: CoreUObject, EngineMessages, SessionMessages
- PrivateIncludePathModuleNames: Messaging, MessagingCommon
- PublicDependencyModuleNames: Core

### `Source/Runtime/SessionServices/Private/SessionInfo.h` (Private)


#### class `FSessionInfo`  
`class FSessionInfo : public TSharedFromThis<FSessionInfo> , public ISessionInfo`  
_L20-113_
- inherits: `TSharedFromThis<FSessionInfo>,ISessionInfo`
- desc: Implements a class to maintain all info related to a game session
- L32 _public prototype_ `FSessionInfo(const FGuid& InSessionId, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);` — Creates and initializes a new instance. @param InSessionId The session's identifier. @param InMessageBus The message bus to use.
- L42 _public prototype_ `void UpdateFromMessage(const FEngineServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Updates this session info with the data in the specified message. @param Message The message containing engine information. @param Context The message context.
- L50 _public prototype_ `void UpdateFromMessage(const FSessionServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Updates this session info with the data in the specified message. @param Message The message containing session information. @param Context The message context.
- L56 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<ISessionInstanceInfo>>& OutInstances) const override;`
- L57 _public prototype_ `virtual const FDateTime& GetLastUpdateTime() const override;`
- L58 _public prototype_ `virtual const int32 GetNumInstances() const override;`
- L59 _public prototype_ `virtual const FGuid& GetSessionId() const override;`
- L60 _public prototype_ `virtual const FString& GetSessionName() const override;`
- L61 _public prototype_ `virtual const FString& GetSessionOwner() const override;`
- L62 _public prototype_ `virtual const bool IsStandalone() const override;`
- L64 _public function_ `DECLARE_DERIVED_EVENT(FSessionInfo, ISessionInfo::FInstanceDiscoveredEvent, FInstanceDiscoveredEvent) virtual FInstanceDiscoveredEvent& OnInstanceDiscovered() override`
- L70 _public function_ `DECLARE_DERIVED_EVENT(FSessionInfo, ISessionInfo::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override`
- L76 _public prototype_ `virtual void Terminate() override;`
- L81 _private prototype_ `void HandleLogReceived(const TSharedRef<ISessionInstanceInfo>& Instance, const TSharedRef<FSessionLogMessage>& LogMessage);` — Handles received log messages.
- L86 _private member_ `TMap<FMessageAddress, TSharedPtr<FSessionInstanceInfo>> Instances;` — Holds the list of engine instances that belong to this session.
- L89 _private member_ `FDateTime LastUpdateTime;` — Holds the time at which the last pong was received.
- L92 _private member_ `TWeakPtr<IMessageBus, ESPMode::ThreadSafe> MessageBusPtr;` — Holds a weak pointer to the message bus.
- L95 _private member_ `FGuid SessionId;` — Holds the session identifier.
- L98 _private member_ `FString SessionName;` — Holds the session name.
- L101 _private member_ `FString SessionOwner;` — Holds the name of the user who launched the session.
- L104 _private member_ `bool Standalone;` — Whether the session is local.
- L109 _private member_ `FInstanceDiscoveredEvent InstanceDiscoveredEvent;` — Holds a delegate to be invoked when a new instance has been discovered.
- L112 _private member_ `FLogReceivedEvent LogReceivedEvent;` — Holds a delegate to be invoked when an instance received a log message.

#### Free symbols / members of external scopes

- L64 _delegate_ `DECLARE_DERIVED_EVENT(FSessionInfo, ISessionInfo::FInstanceDiscoveredEvent, FInstanceDiscoveredEvent) virtual FInstanceDiscoveredEvent& OnInstanceDiscovered() override { return InstanceDiscoveredEvent; } DECLARE_DERIVED_EVENT(FSessionInfo, ISessionInfo::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override { return LogReceivedEvent; } virtual void Terminate() override;`
- L70 _delegate_ `DECLARE_DERIVED_EVENT(FSessionInfo, ISessionInfo::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override { return LogReceivedEvent; } virtual void Terminate() override;`

### `Source/Runtime/SessionServices/Private/SessionInstanceInfo.h` (Private)


#### class `FSessionInstanceInfo`  
`class FSessionInstanceInfo : public TSharedFromThis<FSessionInstanceInfo> , public ISessionInstanceInfo`  
_L21-206_
- inherits: `TSharedFromThis<FSessionInstanceInfo>,ISessionInstanceInfo`
- desc: Implements a class to maintain all info related to a game instance in a session
- L28 _public function_ `FSessionInstanceInfo()` — Default constructor.
- L31 _public prototype_ `virtual ~FSessionInstanceInfo();` — Destructor.
- L40 _public prototype_ `FSessionInstanceInfo(const FGuid& InInstanceId, const TSharedRef<ISessionInfo>& InOwner, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);` — Creates and initializes a new instance. @param InInstanceId The instance's identifier. @param InOwner The session that owns this instance. @param InMessageBus The message bus to use.
- L50 _public prototype_ `void UpdateFromMessage(const FEngineServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Updates this instance info with the data in the specified message. @param Message The message containing engine information. @param Context The message context.
- L58 _public prototype_ `void UpdateFromMessage(const FSessionServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Updates this instance info with the data in the specified message. @param Message The message containing instance information. @param Context The message context.
- L64 _public prototype_ `virtual void ExecuteCommand(const FString& CommandString) override;`
- L66 _public function_ `virtual const FString& GetBuildDate() const override`
- L71 _public function_ `virtual const FString& GetCurrentLevel() const override`
- L76 _public function_ `virtual const FString& GetDeviceName() const override`
- L81 _public function_ `virtual int32 GetEngineVersion() const override`
- L86 _public function_ `virtual const FGuid& GetInstanceId() const override`
- L91 _public function_ `virtual const FString& GetInstanceName() const override`
- L96 _public function_ `virtual const FString& GetInstanceType() const override`
- L101 _public function_ `virtual const FDateTime& GetLastUpdateTime() const override`
- L106 _public function_ `virtual const TArray<TSharedPtr<FSessionLogMessage>>& GetLog() override`
- L111 _public function_ `virtual TSharedPtr<ISessionInfo> GetOwnerSession() override`
- L116 _public function_ `virtual const FString& GetPlatformName() const override`
- L121 _public function_ `virtual float GetWorldTimeSeconds() const override`
- L126 _public function_ `virtual bool IsAuthorized() const override`
- L131 _public prototype_ `DECLARE_DERIVED_EVENT(FSessionInstanceInfo, ISessionInstanceInfo::FLogReceivedEvent, FLogReceivedEvent);`
- L132 _public function_ `virtual FLogReceivedEvent& OnLogReceived() override`
- L137 _public function_ `virtual bool PlayHasBegun() const override`
- L142 _public prototype_ `virtual void Terminate() override;`
- L147 _private prototype_ `void HandleSessionLogMessage(const FSessionServiceLog& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FSessionServiceLog messages.
- L152 _private member_ `FMessageAddress ApplicationAddress;` — Holds the message bus address of the application instance.
- L155 _private member_ `bool Authorized = false;` — Whether the current user is authorized to interact with this instance.
- L158 _private member_ `FString BuildDate;` — Holds the instance's build date.
- L161 _private member_ `FString CurrentLevel;` — Holds the instance's current level.
- L164 _private member_ `FString DeviceName;` — Holds the device name.
- L167 _private member_ `FMessageAddress EngineAddress;` — Holds the message bus address of the engine instance.
- L170 _private member_ `int32 EngineVersion = 0;` — Holds the instance's engine version.
- L173 _private member_ `bool HasBegunPlay = false;` — Holds a flag indicating whether the game has begun.
- L176 _private member_ `FGuid InstanceId;` — Holds the instance identifier.
- L179 _private member_ `FString InstanceName;` — Holds the instance name.
- L182 _private member_ `FString InstanceType;` — Holds the instance type (i.e. game, editor etc.)
- L185 _private member_ `FDateTime LastUpdateTime;` — Holds the time at which the last pong was received.
- L188 _private member_ `TArray<TSharedPtr<FSessionLogMessage>> LogMessages;` — Holds the collection of received log messages.
- L191 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L194 _private member_ `TWeakPtr<ISessionInfo> Owner;` — Holds a reference to the session that owns this instance.
- L197 _private member_ `FString PlatformName;` — Holds the name of the platform that the instance is running on.
- L200 _private member_ `float WorldTimeSeconds = 0.0f;` — Holds the instance's current game world time.
- L205 _private member_ `FLogReceivedEvent LogReceivedEvent;` — Holds an event delegate that is executed when a log message was received from the remote session.

#### Free symbols / members of external scopes

- L131 _delegate_ `DECLARE_DERIVED_EVENT(FSessionInstanceInfo, ISessionInstanceInfo::FLogReceivedEvent, FLogReceivedEvent);`

### `Source/Runtime/SessionServices/Private/SessionManager.h` (Private)


#### class `FSessionManager`  
`class FSessionManager : public TSharedFromThis<FSessionManager> , public ISessionManager`  
_L23-168_
- inherits: `TSharedFromThis<FSessionManager>,ISessionManager`
- desc: Implement the session manager
- L34 _public prototype_ `FSessionManager(const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);` — Creates and initializes a new instance. @param InMessageBus The message bus to use.
- L37 _public prototype_ `~FSessionManager();` — Destructor
- L43 _public prototype_ `virtual void AddOwner(const FString& InOwner) override;`
- L44 _public prototype_ `virtual const TArray<TSharedPtr<ISessionInstanceInfo>>& GetSelectedInstances() const override;`
- L45 _public prototype_ `virtual const TSharedPtr<ISessionInfo>& GetSelectedSession() const override;`
- L46 _public prototype_ `virtual void GetSessions(TArray<TSharedPtr<ISessionInfo>>& OutSessions) const override;`
- L47 _public prototype_ `virtual bool IsInstanceSelected(const TSharedRef<ISessionInstanceInfo>& Instance) const override;`
- L49 _public function_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FCanSelectSessionEvent, FCanSelectSessionEvent) virtual FCanSelectSessionEvent& OnCanSelectSession() override`
- L55 _public function_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FInstanceSelectionChangedEvent, FInstanceSelectionChangedEvent) virtual FInstanceSelectionChangedEvent& OnInstanceSelectionChanged() override`
- L61 _public function_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override`
- L67 _public function_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FSelectedSessionChangedEvent, FSelectedSessionChangedEvent) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() override`
- L73 _public prototype_ `virtual FSimpleMulticastDelegate& OnSessionsUpdated() override;`
- L74 _public prototype_ `virtual FSimpleMulticastDelegate& OnSessionInstanceUpdated() override;`
- L75 _public prototype_ `virtual void RemoveOwner(const FString& InOwner) override;`
- L76 _public prototype_ `virtual bool SelectSession(const TSharedPtr<ISessionInfo>& Session) override;`
- L77 _public prototype_ `virtual bool SetInstanceSelected(const TSharedRef<ISessionInstanceInfo>& Instance, bool Selected) override;`
- L86 _protected prototype_ `void FindExpiredSessions(const FDateTime& Now);` — Finds and removes sessions that haven't been updated in a while. @param Now The current time.
- L93 _protected prototype_ `bool IsValidOwner(const FString& Owner);` — Checks whether the specified owner is valid. @return true if the owner is valid, false otherwise.
- L96 _protected prototype_ `void RefreshSessions();` — Refresh the sessions based on the owner filter list.
- L99 _protected prototype_ `void SendPing();` — Pings all sessions on the network.
- L104 _private prototype_ `void HandleEnginePongMessage(const FEngineServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for handling FSessionServicePong messages.
- L107 _private prototype_ `void HandleLogReceived(const TSharedRef<ISessionInfo>& Session, const TSharedRef<ISessionInstanceInfo>& Instance, const TSharedRef<FSessionLogMessage>& Message);` — Callback received log entries.
- L110 _private prototype_ `void HandleSessionPongMessage(const FSessionServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for handling FSessionServicePong messages.
- L113 _private prototype_ `bool HandleTicker(float DeltaTime);` — Callback for ticks from the ticker.
- L115 _private prototype_ `virtual TSharedPtr<ISessionInstanceInfo> GetInstance(const FGuid& Id) const override;`
- L120 _private member_ `FGuid AutomationControllerAddress;` — The address of the automation controller to where we can forward any automation workers found.
- L123 _private member_ `FDateTime LastPingTime;` — Holds the time at which the last ping was sent.
- L126 _private member_ `TWeakPtr<IMessageBus, ESPMode::ThreadSafe> MessageBusPtr;` — Holds a pointer to the message bus.
- L129 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint.
- L132 _private member_ `TArray<TSharedPtr<ISessionInstanceInfo>> SelectedInstances;` — Holds the list of currently selected instances.
- L135 _private member_ `TSharedPtr<ISessionInfo> SelectedSession;` — Holds a reference to the currently selected session.
- L138 _private member_ `TMap<FGuid, TSharedPtr<FSessionInfo>> Sessions;` — Holds the collection of discovered sessions.
- L143 _private member_ `FCanSelectSessionEvent CanSelectSessionDelegate;` — Holds a delegate to be invoked before a session is selected.
- L146 _private member_ `FInstanceSelectionChangedEvent InstanceSelectionChangedDelegate;` — Holds a delegate to be invoked when an instance changes its selection state.
- L149 _private member_ `TArray<FString> FilteredOwners;` — Owner filter list.
- L152 _private member_ `FLogReceivedEvent LogReceivedEvent;` — Holds a delegate to be invoked when the selected session received a log message.
- L155 _private member_ `FSelectedSessionChangedEvent SelectedSessionChangedEvent;` — Holds a delegate to be invoked when the selected session changed.
- L158 _private member_ `FSimpleMulticastDelegate SessionsUpdatedDelegate;` — Holds a delegate to be invoked when the session list was updated.
- L161 _private member_ `FSimpleMulticastDelegate SessionInstanceUpdatedDelegate;` — Holds a delegate to be invoked when a session instance is updated.
- L164 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Holds a delegate to be invoked when the widget ticks.
- L167 _private member_ `float PingInterval;` — Holds current ping interval.

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FCanSelectSessionEvent, FCanSelectSessionEvent) virtual FCanSelectSessionEvent& OnCanSelectSession() override { return CanSelectSessionDelegate; } DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FInstanceSelectionChangedEvent, FInstanceSelectionChangedEvent) virtual FInstanceSelectionChangedEvent& OnInstanceSelectionChanged() override { return InstanceSelectionChangedDelegate; } DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override { return LogReceivedEvent; } DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FSelectedSessionChangedEvent, FSelectedSessionChangedEvent) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() override { return SelectedSessionChangedEvent; } virtual FSimpleMulticastDelegate& OnSessionsUpdated() override;`
- L55 _delegate_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FInstanceSelectionChangedEvent, FInstanceSelectionChangedEvent) virtual FInstanceSelectionChangedEvent& OnInstanceSelectionChanged() override { return InstanceSelectionChangedDelegate; } DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override { return LogReceivedEvent; } DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FSelectedSessionChangedEvent, FSelectedSessionChangedEvent) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() override { return SelectedSessionChangedEvent; } virtual FSimpleMulticastDelegate& OnSessionsUpdated() override;`
- L61 _delegate_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FLogReceivedEvent, FLogReceivedEvent) virtual FLogReceivedEvent& OnLogReceived() override { return LogReceivedEvent; } DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FSelectedSessionChangedEvent, FSelectedSessionChangedEvent) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() override { return SelectedSessionChangedEvent; } virtual FSimpleMulticastDelegate& OnSessionsUpdated() override;`
- L67 _delegate_ `DECLARE_DERIVED_EVENT(FSessionManager, ISessionManager::FSelectedSessionChangedEvent, FSelectedSessionChangedEvent) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() override { return SelectedSessionChangedEvent; } virtual FSimpleMulticastDelegate& OnSessionsUpdated() override;`

### `Source/Runtime/SessionServices/Private/SessionService.h` (Private)


#### class `FSessionService`  
`class FSessionService : public FOutputDevice , public ISessionService`  
_L19-113_
- inherits: `FOutputDevice,ISessionService`
- desc: Implements an application session service.
- L30 _public prototype_ `FSessionService(const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);` — Creates and initializes a new instance. @param InMessageBus The message bus to use.
- L33 _public prototype_ `virtual ~FSessionService();` — Virtual destructor.
- L39 _public function_ `virtual void Serialize(const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override`
- L48 _public function_ `virtual bool IsRunning() override`
- L53 _public prototype_ `virtual bool Start() override;`
- L54 _public prototype_ `virtual void Stop() override;`
- L65 _protected prototype_ `void SendLog(const TCHAR* Data, ELogVerbosity::Type Verbosity = ELogVerbosity::Log, const class FName& Category = "Log` — Sends a log message to subscribed recipients. @param Data The log message data. @param Verbosity The verbosity type. @param Category The log category.
- L73 _protected prototype_ `void SendNotification(const TCHAR* NotificationText, const FMessageAddress& Recipient);` — Sends a notification to the specified recipient. @param NotificationText The notification text. @param Recipient The recipient's message address.
- L81 _protected prototype_ `void SendPong(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FString& UserName);` — Publishes a ping response. @param Context The context of the received Ping message. @param UserName The name of the user that sent the ping.
- L86 _private prototype_ `void HandleMessageEndpointShutdown();` — Handles message bus shutdowns.
- L89 _private prototype_ `void HandleSessionLogSubscribeMessage(const FSessionServiceLogSubscribe& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FSessionServiceLogSubscribe messages.
- L92 _private prototype_ `void HandleSessionLogUnsubscribeMessage(const FSessionServiceLogUnsubscribe& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FSessionServiceLogUnsubscribe messages.
- L95 _private prototype_ `void HandleSessionPingMessage(const FSessionServicePing& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FSessionServicePing messages.
- L100 _private member_ `TArray<FMessageAddress> LogSubscribers;` — Holds the list of log subscribers.
- L103 _private member_ `FCriticalSection LogSubscribersLock;` — Holds a critical section for the log subscribers array.
- L106 _private member_ `TWeakPtr<IMessageBus, ESPMode::ThreadSafe> MessageBusPtr;` — Holds a weak pointer to the message bus.
- L109 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L112 _private member_ `bool IsInSendLog;` — Set to true while in SendLog, used to avoid recursion

### `Source/Runtime/SessionServices/Private/TraceController.h` (Private)


#### class `FTraceController`  
`class FTraceController : public ITraceController`  
_L20-99_
- inherits: `ITraceController`
- desc: Interface to control other sessions tracing.
- L23 _public prototype_ `FTraceController(const TSharedRef<IMessageBus>& InMessageBus);`
- L27 _private prototype_ `virtual void SendDiscoveryRequest(const FGuid& SessionId, const FGuid& InstanceId) const override;`
- L28 _private prototype_ `virtual void SendDiscoveryRequest() override;`
- L29 _private prototype_ `virtual void SendStatusUpdateRequest() override;`
- L30 _private prototype_ `virtual void SendChannelUpdateRequest() override;`
- L31 _private prototype_ `virtual void SendSettingsUpdateRequest() override;`
- L32 _private prototype_ `virtual bool HasAvailableInstance(const FGuid& InstanceId) override;`
- L33 _private prototype_ `virtual bool IsActive(FGuid InstanceId, double TimeoutSec = 5.0f) const override;`
- L34 _private prototype_ `virtual bool HasCapability(FGuid InstanceId, FStringView Name) override;`
- L35 _private prototype_ `virtual void WithInstance(FGuid InstanceId, FCallback Func) override;`
- L37 _private prototype_ `DECLARE_DERIVED_EVENT(FTraceController, ITraceController::FStatusReceivedEvent, FStatusReceivedEvent);`
- L38 _private function_ `virtual FStatusReceivedEvent& OnStatusReceived() override`
- L43 _private prototype_ `DECLARE_DERIVED_EVENT(FTraceController, ITraceController::FSecureResponseEvent, FSecureResponseEvent);`
- L44 _private function_ `virtual FSecureResponseEvent& OnSecureResponse() override`
- L50 _private prototype_ `void OnNotification(const FMessageBusNotification& MessageBusNotification);` — Message handlers
- L51 _private prototype_ `void OnDiscoveryResponse(const FTraceControlDiscovery& Message, const TSharedRef<IMessageContext>& Context);`
- L52 _private prototype_ `void OnStatus(const FTraceControlStatus& Message, const TSharedRef<IMessageContext>& Context);`
- L53 _private prototype_ `void OnChannelsDesc(const FTraceControlChannelsDesc& Message, const TSharedRef<IMessageContext>& Context);`
- L54 _private prototype_ `void OnChannelsStatus(const FTraceControlChannelsStatus& Message, const TSharedRef<IMessageContext>& Context);`
- L55 _private prototype_ `void OnSettings(const FTraceControlSettings& Message, const TSharedRef<IMessageContext>& Context);`
- L56 _private prototype_ `static void UpdateStatus(const FTraceControlStatus& Message, FTraceStatus& Status);`
- L57 _private prototype_ `void OnSecureResponse(const FTraceControlSecureResponse& Message, const TSharedRef<IMessageContext>& Context);`
- L75 _private member_ `TWeakPtr<IMessageBus> MessageBus;` — Needed to create command instances when new sessions are discovered. We don't need a ref counted pointer to the message bus.
- L78 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;` — Our own endpoint for messages
- L81 _private member_ `FMessageAddress TraceControlAddress;` — Address of the runtime endpoint for trace controls
- L84 _private member_ `FStatusReceivedEvent StatusReceivedEvent;` — Event for status updates on any session
- L87 _private member_ `FSecureResponseEvent SecureResponse;` — Event for secure connection responses
- L90 _private member_ `mutable FRWLock InstancesLock;` — Lock to protect access to Instances list
- L93 _private member_ `TMap<FMessageAddress, FTracingInstance> Instances;` — Known instances with an active trace service
- L96 _private member_ `TMap<FGuid, FMessageAddress> InstanceToAddress;` — Secondary lookup from instance -> address

#### struct `FTraceController::FTracingInstance`  
`struct FTracingInstance`  
_L61-69_
- L63 _public member_ `FTraceStatus Status;`
- L64 _public member_ `FTraceControllerCommands Commands;`
- L65 _public member_ `FDateTime LastMessageTimestamp;`
- L67 _public prototype_ `FTracingInstance(const TSharedRef<IMessageBus>& InMessageBus, FMessageAddress Service, FTraceController* Controller);`
- L68 _public prototype_ `FTracingInstance() = delete;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DERIVED_EVENT(FTraceController, ITraceController::FStatusReceivedEvent, FStatusReceivedEvent);`
- L43 _delegate_ `DECLARE_DERIVED_EVENT(FTraceController, ITraceController::FSecureResponseEvent, FSecureResponseEvent);`

### `Source/Runtime/SessionServices/Private/TraceControllerCommands.h` (Private)


#### class `FTraceControllerCommands`  
`class FTraceControllerCommands : public ITraceControllerCommands`  
_L15-54_
- inherits: `ITraceControllerCommands`
- desc: Logic for sending commands to a specific remote trace service.
- L18 _public prototype_ `FTraceControllerCommands(const TSharedPtr<IMessageBus>& MessageBus, FMessageAddress Service, class FTraceController* Controller);`
- L21 _public prototype_ `void OnChannelsDesc(const FTraceControlChannelsDesc& Message);`
- L25 _private prototype_ `virtual void SetChannels(TConstArrayView<FStringView> ChannelsToEnable, TConstArrayView<FStringView> ChannelsToDisable) override;` — ITraceController interface
- L26 _private prototype_ `virtual void SetChannels(TConstArrayView<FString> ChannelsToEnable, TConstArrayView<FString> ChannelsToDisable) override;`
- L27 _private prototype_ `virtual void Send(FStringView Host, FStringView Channels, bool bExcludeTail) override;`
- L28 _private prototype_ `virtual void File(FStringView File, FStringView Channels, bool bExcludeTail, bool bTruncateFile) override;`
- L29 _private prototype_ `virtual void Stop() override;`
- L30 _private prototype_ `virtual void SnapshotSend(FStringView Host) override;`
- L31 _private prototype_ `virtual void SnapshotFile(FStringView File) override;`
- L32 _private prototype_ `virtual void Pause() override;`
- L33 _private prototype_ `virtual void Resume() override;`
- L34 _private prototype_ `virtual void Bookmark(FStringView Label) override;`
- L35 _private prototype_ `virtual void Screenshot(FStringView Name, bool bShowUI) override;`
- L36 _private prototype_ `virtual void SetStatNamedEventsEnabled(bool bEnabled) override;`
- L37 _private prototype_ `virtual void SendSecure(FStringView Channels, bool bExcludeTail) override;`
- L38 _private prototype_ `virtual void SendStatusUpdateRequest() override;`
- L39 _private prototype_ `virtual void SendChannelUpdateRequest() override;`
- L40 _private prototype_ `virtual void SendSettingsUpdateRequest() override;`
- L44 _private member_ `FMessageAddress ServiceAddress;` — Address of the remote trace service to control
- L47 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;` — Our own endpoint for messages
- L50 _private member_ `TMap<uint64, uint32> SettableChannels;` — List of channels (hash of their name) that is possible to set (not read-only).
- L53 _private member_ `int32 ChannelCount = 0;` — The current known channel count.

### `Source/Runtime/SessionServices/Public/ISessionInfo.h` (Public)


#### class `ISessionInfo`  
`class ISessionInfo`  
_L13-95_
- desc: Interface for game instances.
- L22 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<ISessionInstanceInfo>>& OutInstances) const = 0;` — Gets a read-only collection of all instances that belong to this session. @param OutInstances Will hold the collection of instances.
- L29 _public prototype_ `virtual const FDateTime& GetLastUpdateTime() const = 0;` — Gets the time at which the last update was received from this instance. @return The receive time.
- L36 _public prototype_ `virtual const int32 GetNumInstances() const = 0;` — Gets the number of engine instances that are part of the session. @return The number of engine instances.
- L43 _public prototype_ `virtual const FGuid& GetSessionId() const = 0;` — Gets the session identifier. @return Session identifier.
- L50 _public prototype_ `virtual const FString& GetSessionName() const = 0;` — Gets the name of the session. @return Session name.
- L57 _public prototype_ `virtual const FString& GetSessionOwner() const = 0;` — Gets the name of the user that owns the session. @return User name.
- L66 _public prototype_ `virtual const bool IsStandalone() const = 0;` — Checks whether this is a standalone session. A session is standalone if has not been created from the Launcher. @return true if this is a standalone session, false otherwise.
- L71 _public prototype_ `virtual void Terminate() = 0;` — Terminates the session.
- L80 _public prototype_ `DECLARE_EVENT_TwoParams(ISessionInfo, FInstanceDiscoveredEvent, const TSharedRef<ISessionInfo>& , const TSharedRef<ISessionInstanceInfo>& ) virtual FInstanceDiscoveredEvent& OnInstanceDiscovered() = 0;` — A delegate that is executed when a new instance has been discovered. @return The delegate.
- L88 _public prototype_ `DECLARE_EVENT_ThreeParams(ISessionInfo, FLogReceivedEvent, const TSharedRef<ISessionInfo>& , const TSharedRef<ISessionInstanceInfo>& , const TSharedRef<FSessionLogMessage>& );` — A delegate that is executed when a new log message has been received. @return The delegate.
- L89 _public prototype_ `virtual FLogReceivedEvent& OnLogReceived() = 0;`
- L94 _public prototype_ `virtual ~ISessionInfo() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L80 _delegate_ `DECLARE_EVENT_TwoParams(ISessionInfo, FInstanceDiscoveredEvent, const TSharedRef<ISessionInfo>& , const TSharedRef<ISessionInstanceInfo>& ) virtual FInstanceDiscoveredEvent& OnInstanceDiscovered() = 0;` — A delegate that is executed when a new instance has been discovered. @return The delegate.
- L88 _delegate_ `DECLARE_EVENT_ThreeParams(ISessionInfo, FLogReceivedEvent, const TSharedRef<ISessionInfo>& , const TSharedRef<ISessionInstanceInfo>& , const TSharedRef<FSessionLogMessage>& );` — A delegate that is executed when a new log message has been received. @return The delegate.

### `Source/Runtime/SessionServices/Public/ISessionInstanceInfo.h` (Public)


#### class `ISessionInstanceInfo`  
`class ISessionInstanceInfo`  
_L13-139_
- desc: Interface for game instances.
- L22 _public prototype_ `virtual void ExecuteCommand( const FString& CommandString ) = 0;` — Executes a console command on this engine instance. @param CommandString The command to execute.
- L29 _public prototype_ `virtual const FString& GetBuildDate() const = 0;` — Gets instance's build date. @return The build date string.
- L36 _public prototype_ `virtual const FString& GetCurrentLevel() const = 0;` — Gets the name of the level that the instance is currently running. @return The name of the level.
- L43 _public prototype_ `virtual const FString& GetDeviceName() const = 0;` — Gets the name of the device that this instance is running on. @return The device name string.
- L50 _public prototype_ `virtual int32 GetEngineVersion() const = 0;` — Gets the instance's engine version number. @return Engine version.
- L57 _public prototype_ `virtual const FGuid& GetInstanceId() const = 0;` — Gets the instance identifier. @return Instance identifier.
- L64 _public prototype_ `virtual const FString& GetInstanceName() const = 0;` — Gets the name of this instance. @return The instance name string.
- L71 _public prototype_ `virtual const FString& GetInstanceType() const = 0;` — Gets the instance type (i.e. Editor or Game). @return The game instance type string.
- L78 _public prototype_ `virtual const FDateTime& GetLastUpdateTime() const = 0;` — Gets the time at which the last update was received from this instance. @return The receive time.
- L85 _public prototype_ `virtual const TArray<TSharedPtr<FSessionLogMessage>>& GetLog() = 0;` — Gets the collection of log entries received from this instance. @return Log entries.
- L92 _public prototype_ `virtual TSharedPtr<ISessionInfo> GetOwnerSession() = 0;` — Gets a reference to the session that owns this instance. @return Owner session.
- L99 _public prototype_ `virtual const FString& GetPlatformName() const = 0;` — Gets the name of the platform that the instance is running on. @return Platform name string.
- L106 _public prototype_ `virtual float GetWorldTimeSeconds() const = 0;` — Gets the instance's current game world time. @return World time in seconds.
- L113 _public prototype_ `virtual bool IsAuthorized() const = 0;` — Check whether the current user is authorized to interact with this instance. @return true if the user is authorized, false otherwise.
- L120 _public prototype_ `virtual bool PlayHasBegun() const = 0;` — Checks whether this instance has already begun game play. @return true if game play has begun, false otherwise.
- L123 _public prototype_ `virtual void Terminate() = 0;` — Terminates the instance.
- L132 _public prototype_ `DECLARE_EVENT_TwoParams(ISessionInstanceInfo, FLogReceivedEvent, const TSharedRef<ISessionInstanceInfo>&, const TSharedRef<FSessionLogMessage>&);` — Gets an event delegate that is executed when a new log message has been received. @return The delegate.
- L133 _public prototype_ `virtual FLogReceivedEvent& OnLogReceived() = 0;`
- L138 _public prototype_ `virtual ~ISessionInstanceInfo() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L132 _delegate_ `DECLARE_EVENT_TwoParams(ISessionInstanceInfo, FLogReceivedEvent, const TSharedRef<ISessionInstanceInfo>&, const TSharedRef<FSessionLogMessage>&);` — Gets an event delegate that is executed when a new log message has been received. @return The delegate.

### `Source/Runtime/SessionServices/Public/ISessionManager.h` (Public)


#### class `ISessionManager`  
`class ISessionManager`  
_L13-137_
- desc: Interface for the session manager.
- L22 _public prototype_ `virtual void AddOwner( const FString& InOwner ) = 0;` — Adds an owner whose sessions we are interested in @param InOwner Session owner we want to view sessions from
- L29 _public prototype_ `virtual const TArray<TSharedPtr<ISessionInstanceInfo>>& GetSelectedInstances() const = 0;` — Gets the collection of currently selected engine instances. @return The selected instances.
- L36 _public prototype_ `virtual const TSharedPtr<ISessionInfo>& GetSelectedSession() const = 0;` — Get the selected session - as chosen in the session browser @return The session ID selected
- L43 _public prototype_ `virtual void GetSessions( TArray<TSharedPtr<ISessionInfo>>& OutSessions ) const = 0;` — Gets the list of all discovered sessions. @param OutSessions Will hold the collection of sessions.
- L52 _public prototype_ `virtual TSharedPtr<ISessionInstanceInfo> GetInstance(const FGuid& Id) const = 0;` — Attempts to retrieve an instance by it's unique instance id. @param Id Instance id @return Instance if it exist, otherwise a nullptr
- L59 _public prototype_ `virtual bool IsInstanceSelected( const TSharedRef<ISessionInstanceInfo>& Instance ) const = 0;` — Checks whether the given instance is currently selected. @return true if the instance is selected, false otherwise.
- L66 _public prototype_ `virtual void RemoveOwner( const FString& InOwner ) = 0;` — Removes an owner whose sessions we are no longer interested in @param InOwner Session owner we want to remove
- L74 _public prototype_ `virtual bool SelectSession( const TSharedPtr<ISessionInfo>& Session ) = 0;` — Selects the specified session. @param Session The session to the select (can be NULL to select none). @return true if the session was selected, false otherwise.
- L83 _public prototype_ `virtual bool SetInstanceSelected( const TSharedRef<ISessionInstanceInfo>& Instance, bool Selected ) = 0;` — Marks the specified item as selected or unselected. @param Instance The instance to mark. @param Selected Whether the instance should be selected (true) or unselected (false). @return true if the instance was selected, false otherwise.
- L92 _public prototype_ `DECLARE_EVENT_TwoParams(ISessionManager, FCanSelectSessionEvent, const TSharedPtr<ISessionInfo>& , bool& ) virtual FCanSelectSessionEvent& OnCanSelectSession() = 0;` — Returns a delegate that is executed before a session is being selected. @return The delegate.
- L100 _public prototype_ `DECLARE_EVENT_TwoParams(ISessionManager, FInstanceSelectionChangedEvent, const TSharedPtr<ISessionInstanceInfo>& , bool ) virtual FInstanceSelectionChangedEvent& OnInstanceSelectionChanged() = 0;` — Returns a delegate that is executed when an instance changes its selection state. @return The delegate.
- L108 _public prototype_ `DECLARE_EVENT_ThreeParams(ISessionManager, FLogReceivedEvent, const TSharedRef<ISessionInfo>& , const TSharedRef<ISessionInstanceInfo>& , const TSharedRef<FSessionLogMessage>& );` — Returns a delegate that is executed when the selected session received a log message from one of its instances. @return The delegate.
- L109 _public prototype_ `virtual FLogReceivedEvent& OnLogReceived() = 0;`
- L116 _public prototype_ `DECLARE_EVENT_OneParam(ISessionManager, FSelectedSessionChangedEvent, const TSharedPtr<ISessionInfo>& ) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() = 0;` — Returns a delegate that is executed when the selected session changed. @return The delegate.
- L124 _public prototype_ `virtual FSimpleMulticastDelegate& OnSessionsUpdated() = 0;` — Returns a delegate that is executed when the list of sessions has changed. @return The delegate.
- L131 _public prototype_ `virtual FSimpleMulticastDelegate& OnSessionInstanceUpdated() = 0;` — Returns a delegate that is executed when a session instance is updated. @return The delegate.
- L136 _public prototype_ `virtual ~ISessionManager() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L92 _delegate_ `DECLARE_EVENT_TwoParams(ISessionManager, FCanSelectSessionEvent, const TSharedPtr<ISessionInfo>& , bool& ) virtual FCanSelectSessionEvent& OnCanSelectSession() = 0;` — Returns a delegate that is executed before a session is being selected. @return The delegate.
- L100 _delegate_ `DECLARE_EVENT_TwoParams(ISessionManager, FInstanceSelectionChangedEvent, const TSharedPtr<ISessionInstanceInfo>& , bool ) virtual FInstanceSelectionChangedEvent& OnInstanceSelectionChanged() = 0;` — Returns a delegate that is executed when an instance changes its selection state. @return The delegate.
- L108 _delegate_ `DECLARE_EVENT_ThreeParams(ISessionManager, FLogReceivedEvent, const TSharedRef<ISessionInfo>& , const TSharedRef<ISessionInstanceInfo>& , const TSharedRef<FSessionLogMessage>& );` — Returns a delegate that is executed when the selected session received a log message from one of its instances. @return The delegate.
- L116 _delegate_ `DECLARE_EVENT_OneParam(ISessionManager, FSelectedSessionChangedEvent, const TSharedPtr<ISessionInfo>& ) virtual FSelectedSessionChangedEvent& OnSelectedSessionChanged() = 0;` — Returns a delegate that is executed when the selected session changed. @return The delegate.

### `Source/Runtime/SessionServices/Public/ISessionService.h` (Public)


#### class `ISessionService`  
`class ISessionService`  
_L10-41_
- desc: Interface for application session services.
- L20 _public prototype_ `virtual bool IsRunning() = 0;` — Checks whether the service is running. @return true if the service is running, false otherwise. @see Start, Stop
- L28 _public prototype_ `virtual bool Start() = 0;` — Starts the service. @return true if the service was started, false otherwise. @see IsRunning, Stop
- L35 _public prototype_ `virtual void Stop() = 0;` — Stops the service. @see IsRunning, Start
- L40 _public prototype_ `virtual ~ISessionService() = default;` — Virtual destructor.

### `Source/Runtime/SessionServices/Public/ISessionServicesModule.h` (Public)


#### class `ISessionServicesModule`  
`class ISessionServicesModule : public IModuleInterface`  
_L15-46_
- inherits: `IModuleInterface`
- desc: Interface for session core modules.
- L26 _public prototype_ `virtual TSharedPtr<ISessionManager> GetSessionManager() = 0;` — Gets the session manager. @return The session manager. @see GetSessionService
- L34 _public prototype_ `virtual TSharedPtr<ISessionService> GetSessionService() = 0;` — Gets the session service. @return The session service. @see GetSessionManager
- L40 _public prototype_ `virtual TSharedPtr<ITraceController> GetTraceController() = 0;` — Get the trace controller
- L45 _public prototype_ `virtual ~ISessionServicesModule() = default;` — Virtual destructor.

### `Source/Runtime/SessionServices/Public/ITraceController.h` (Public)


#### struct `FTraceStatus`  
`struct FTraceStatus`  
_L16-145_
- desc: Describes the state of a single remote instance with Trace.
- L107 _public member_ `FGuid SessionId;` — Session id of the process we're controlling
- L109 _public member_ `FGuid InstanceId;` — Instance id of the process we're controlling
- L111 _public member_ `bool bIsTracing = false;` — If tracing is active
- L113 _public member_ `bool bIsPaused = false;` — If tracing is paused
- L115 _public member_ `bool bAreStatNamedEventsEnabled = false;` — If stats are emitted as named events
- L117 _public member_ `FString Endpoint;` — Endpoint of active trace
- L119 _public member_ `FGuid SessionGuid;` — Session identifier for the trace.
- L121 _public member_ `FGuid TraceGuid;` — Unique identifier for the trace
- L123 _public member_ `FSettings Settings;` — Settings
- L125 _public member_ `TMap<uint32, FChannel> Channels;` — State of channels
- L127 _public member_ `FStats Stats;` — Stats
- L129 _public member_ `FDateTime StatusTimestamp;` — Timestamp when the state of the trace was captured
- L131 _public member_ `ETraceSystemStatus TraceSystemStatus;` — The status of the trace system.
- L133 _public function_ `bool HasChannel(FStringView ChannelName) const`

#### enum `FTraceStatus::EUpdateType`  
`enum class EUpdateType : uint8`  
_L21-28_
- desc: Update types
- L23 _public enumerator_ `Status = 1 << 0`
- L24 _public enumerator_ `Settings = 1 << 1`
- L25 _public enumerator_ `ChannelsDesc = 1 << 2`
- L26 _public enumerator_ `ChannelsStatus = 1 << 3`
- L27 _public enumerator_ `All = Status|Settings|ChannelsDesc|ChannelsStatus`

#### enum `FTraceStatus::ETraceSystemStatus`  
`enum class ETraceSystemStatus : uint8`  
_L30-40_
- L32 _public enumerator_ `NotAvailable`
- L33 _public enumerator_ `Available`
- L34 _public enumerator_ `TracingToServer`
- L35 _public enumerator_ `TracingToFile`
- L36 _public enumerator_ `TracingToSecureNetwork`
- L37 _public enumerator_ `TracingToCustomRelay`
- L39 _public enumerator_ `NumValues`

#### struct `FTraceStatus::FChannelPreset`  
`struct FChannelPreset`  
_L42-54_
- L44 _public function_ `FChannelPreset(const FString& InName, const FString& InChannels, bool bInIsReadOnly) : Name(InName) , ChannelList(InChannels) , bIsReadOnly(bInIsReadOnly)`
- L51 _public member_ `FString Name;`
- L52 _public member_ `FString ChannelList;`
- L53 _public member_ `bool bIsReadOnly;`

#### struct `FTraceStatus::FCapability`  
`struct FCapability`  
_L56-59_
- L58 _public member_ `FString Name;`

#### struct `FTraceStatus::FSettings`  
`struct FSettings`  
_L61-73_
- L64 _public member_ `bool bUseWorkerThread;` — If worker thread is used or TraceLog is pumped on end frame.
- L66 _public member_ `bool bUseImportantCache;` — If important cache is enabled
- L68 _public member_ `uint32 TailSizeBytes;` — Size of tail buffer
- L70 _public member_ `TArray<FChannelPreset> ChannelPresets;` — The channel presets defined by the process.
- L72 _public member_ `TArray<FCapability> Capabilities;` — Capabilities of the target

#### struct `FTraceStatus::FChannel`  
`struct FChannel`  
_L75-88_
- L78 _public member_ `FString Name;` — Channel name
- L80 _public member_ `FString Description;` — Description string
- L82 _public member_ `uint32 Id;` — Remote system id. This may be unique per machine.
- L84 _public member_ `bool bEnabled;` — If channel is currently enabled
- L87 _public member_ `bool bReadOnly;` — If it's possible to toggle channel. Read only channels must be set on process start using command line arguments.

#### struct `FTraceStatus::FStats`  
`struct FStats`  
_L90-104_
- L93 _public member_ `uint64 BytesSent;` — Number of bytes sent to server or file.
- L95 _public member_ `uint64 BytesTraced;` — Number of (uncompressed) bytes traced from process.
- L97 _public member_ `uint64 MemoryUsed;` — Total memory used by TraceLog
- L99 _public member_ `uint32 CacheAllocated;` — Allocated memory for important events
- L101 _public member_ `uint32 CacheUsed;` — Memory used for important events
- L103 _public member_ `uint32 CacheWaste;` — Wasted space for important events cache

#### struct `FSecureConnection`  
`struct FSecureConnection`  
_L149-156_
- L151 _public member_ `FString Host;`
- L152 _public member_ `uint16 Port;`
- L153 _public member_ `TArray<uint8> AuthorizationToken;`
- L154 _public member_ `TArray<uint8> CertificateAuthority;`
- L155 _public member_ `FString Identity;`

#### class `ITraceController`  
`class ITraceController`  
_L177-268_
- desc: Interface for monitoring known trace service instances. ITraceController is a singleton which tracks all known instances and provides callback for status updates and interfaces to issue commands to one or more remote instances. Example usage: ``` // I've found the session instance that we want to control FGuid InstanceId = ...; // Get the controller TSharedPtr<ITraceController> TraceController = SessionServicesModule.GetTraceController(); // To control just a single instance use the session instance id. TraceController->WithInstance(InstanceId, [](const FTraceStatus& Status, ITraceControllerCommands& Commands){ Commands.Send("localhost", "audio,audiomixer,bookmark,log"); Commands.Bookmark("My remote bookmark"); }); ```
- L181 _public prototype_ `virtual ~ITraceController() = default;`
- L188 _public prototype_ `virtual void SendDiscoveryRequest(const FGuid& SessionId, const FGuid& InstanceId) const = 0;` — Request to discover a specific instance @param SessionId Session id of the instance @param InstanceId Instance id
- L193 _public prototype_ `virtual void SendDiscoveryRequest() = 0;` — Request to discover all instances
- L199 _public prototype_ `virtual void SendStatusUpdateRequest() = 0;` — `UE_DEPRECATED(5.8, "Use the version from ITraceControllerCommands as this one can cause high traffic when used used in large networks.")` — Request update of the status from all sessions and instances.
- L205 _public prototype_ `virtual void SendChannelUpdateRequest() = 0;` — `UE_DEPRECATED(5.8, "Use the version from ITraceControllerCommands as this one can cause high traffic when used used in large networks.")` — Request update of channel status from all sessions and instances.
- L211 _public prototype_ `virtual void SendSettingsUpdateRequest() = 0;` — `UE_DEPRECATED(5.8, "Use the version from ITraceControllerCommands as this one can cause high traffic when used used in large networks.")` — Request update of setting state from all sessions and instances.
- L216 _public prototype_ `DECLARE_EVENT_ThreeParams(ITraceController, FStatusReceivedEvent, const FTraceStatus&, FTraceStatus::EUpdateType, ITraceControllerCommands&);` — Generic event for updates of status
- L223 _public prototype_ `virtual FStatusReceivedEvent& OnStatusReceived() = 0;` — Event triggered whenever status is updated for any known session. A reference to the status and what has changed is provided along with a structure to issue commands.
- L226 _public prototype_ `DECLARE_EVENT_TwoParams(ITraceController, FSecureResponseEvent, const FTraceStatus&, const FSecureConnection&) virtual FSecureResponseEvent& OnSecureResponse() = 0;`
- L236 _public prototype_ `virtual bool HasAvailableInstance(const FGuid& InstanceId) = 0;` — Return true if an instance with the provided Id exists and has been discovered.
- L243 _public prototype_ `virtual bool IsActive(FGuid InstanceId, double TimeoutSec = 5.0f) const = 0;` — Returns true if the last message received for a specific instance is newer than TimeoutSec. @param InstanceId The id of the instance to check. @param TimeoutSec The maximum number of seconds that must have passed since the last message for it to be considered active.
- L245 _public typedef_ `typedef TFunction<void(const FTraceStatus&, ITraceControllerCommands&)> FCallback;`
- L252 _public prototype_ `virtual void WithInstance(FGuid InstanceId, FCallback Func) = 0;` — Execute a function on a specific session. @param InstanceId InstanceId to issue command to @param Func Functor to execute
- L261 _public prototype_ `virtual bool HasCapability(FGuid InstanceId, FStringView Name) = 0;` — Queries a session about a specific capability. @param InstanceId InstanceId to query @param Name Name of capability @return True if session lists capability, false otherwise
- L267 _public prototype_ `static TSharedPtr<ITraceController> Create(TSharedPtr<class IMessageBus>& MessageBus);` — Create an instance using a custom message bus @param MessageBus Message bus the controller will use

#### Free symbols / members of external scopes

- L147 _prototype_ `ENUM_CLASS_FLAGS(FTraceStatus::EUpdateType);`
- L216 _delegate_ `DECLARE_EVENT_ThreeParams(ITraceController, FStatusReceivedEvent, const FTraceStatus&, FTraceStatus::EUpdateType, ITraceControllerCommands&);` — Generic event for updates of status
- L226 _delegate_ `DECLARE_EVENT_TwoParams(ITraceController, FSecureResponseEvent, const FTraceStatus&, const FSecureConnection&) virtual FSecureResponseEvent& OnSecureResponse() = 0;`

### `Source/Runtime/SessionServices/Public/ITraceControllerCommands.h` (Public)


#### class `ITraceControllerCommands`  
`class ITraceControllerCommands`  
_L11-119_
- desc: Interface to send commands to a single remote trace service.
- L15 _public prototype_ `virtual ~ITraceControllerCommands() = default;`
- L22 _public prototype_ `virtual void SetChannels(TConstArrayView<FStringView> ChannelsToEnable, TConstArrayView<FStringView> ChannelsToDisable) = 0;` — Enables or disables channels by name @param ChannelsToEnable  List of channels to enable @param ChannelsToDisable List of channels to disable
- L29 _public prototype_ `virtual void SetChannels(TConstArrayView<FString> ChannelsToEnable, TConstArrayView<FString> ChannelsToDisable) = 0;` — Enables or disables channels by name @param ChannelsToEnable  List of channels to enable @param ChannelsToDisable List of channels to disable
- L37 _public prototype_ `virtual void Send(FStringView Host, FStringView Channels, bool bExcludeTail = false) = 0;` — Start a trace on selected instances to the provided host, using a set of channels. @param Host Host to send the trace to @param Channels Comma separated list of channels to enable @param bExcludeTail If the tail (circular buffer of recent events) should be included
- L46 _public prototype_ `virtual void File(FStringView File, FStringView Channels, bool bExcludeTail = false, bool bTruncateFile = false) = 0;` — Start a trace on selected instances to a file on the instance, using a set of channels. @param File Path on the instance. ".utrace" will be appended @param Channels Comma separated list of channels to enable @param bExcludeTail If the tail (circular buffer of recent events) should be included @param bTruncateFile If the file should be truncated (if already exists)
- L55 _public prototype_ `virtual void SendSecure(FStringView Channels, bool bExcludeTail = false) = 0;` — Start a trace on selected instance using a secure connection. The initiator is required to connect to the port using the options specified in the response. @param Channels Comma separated list of channels to enable @param bExcludeTail If the tail (circular buffer of recent events) should be included
- L62 _public prototype_ `virtual void SnapshotSend(FStringView Host) = 0;` — On selected instances, make a snapshot of the tail (circular buffer of recent events) and send to the provided host. @param Host Host to send the trace to
- L69 _public prototype_ `virtual void SnapshotFile(FStringView File) = 0;` — On selected instances, make a snapshot of the tail (circular buffer of recent events) and save to a file. @param File Path on the instance. ".utrace" will be appended
- L74 _public prototype_ `virtual void Pause() = 0;` — Pause tracing by muting all (non-readonly) channels.
- L79 _public prototype_ `virtual void Resume() = 0;` — Resume tracing (from paused) by enabling the previously enabled channels.
- L84 _public prototype_ `virtual void Stop() = 0;` — Stop active trace.
- L90 _public prototype_ `virtual void Bookmark(FStringView Label) = 0;` — Insert bookmark into the trace. @param Label Label of bookmark
- L97 _public prototype_ `virtual void Screenshot(FStringView Name, bool bShowUI) = 0;` — Insert screenshot into the trace. @param Name Name of the screenshot @param bShowUI If the UI should be visible in the image
- L103 _public prototype_ `virtual void SetStatNamedEventsEnabled(bool bEnabled) = 0;` — Set the StatNamedEvents flag. @param bEnabled The value to assign to the StatNamedEvents flag.
- L108 _public prototype_ `virtual void SendStatusUpdateRequest() = 0;` — Request update of the status.
- L113 _public prototype_ `virtual void SendChannelUpdateRequest() = 0;` — Request update of channel status.
- L118 _public prototype_ `virtual void SendSettingsUpdateRequest() = 0;` — Request update of setting state.

### `Source/Runtime/SessionServices/Public/SessionLogMessage.h` (Public)


#### struct `FSessionLogMessage`  
`struct FSessionLogMessage`  
_L11-68_
- desc: Structure for log messages.
- L14 _public member_ `FName Category;` — Holds the log category.
- L17 _public member_ `FGuid InstanceId;` — Holds the identifier of the engine instance that generated this log message.
- L20 _public member_ `FString InstanceName;` — Holds the name of the engine instance that generated this log message.
- L23 _public member_ `FString Text;` — Holds the message text.
- L26 _public member_ `FDateTime Time;` — Holds the time at which the message was generated.
- L29 _public member_ `double TimeSeconds;` — Holds the number of seconds from the start of the instance at which the message was generated.
- L32 _public member_ `ELogVerbosity::Type Verbosity;` — Holds the verbosity type.
- L46 _public function_ `FSessionLogMessage(const FGuid& InInstanceId, const FString& InInstanceName, float InTimeSeconds, const FString& InText, ELogVerbosity::Type InVerbosity, const FName& InCategory) : Category(InCategory) , InstanceId(InInstanceId) , InstanceName(InInstanceName) , Text((InCategory != NAME_None) ? InCategory.ToString() + TEXT(": ") + InText : InText) , Time(FDateTime::Now()) , TimeSeconds(InTimeSeconds) , Verbosity(InVerbosity)` — Creates and initializes a new instance. @param InInstanceId The identifier of the instance that generated the log message. @param InInstanceName The name of the engine instance that generated the log message. @param InTimeSeconds The number of seconds from the start of the instance at which the message was generated. @param InText The message text. @param InVerbosity The verbosity type. @param InCategory The log category.

#### struct `FSessionLogMessage::TimeComparer`  
`struct TimeComparer`  
_L61-67_
- desc: Implements a predicate to compare two log messages by log time.
- L63 _public function_ `bool operator()(const TSharedPtr<FSessionLogMessage>& A, const TSharedPtr<FSessionLogMessage>& B) const`
