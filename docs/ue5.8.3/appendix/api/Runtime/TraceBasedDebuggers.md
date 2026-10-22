# Runtime / TraceBasedDebuggers

- module root: `Source/Runtime/Experimental/TraceBasedDebuggers`
- headers: 7; symbols: 371
- symbol kinds: class=3, delegate=11, enum=6, enumerator=20, function=48, macro=7, member=116, namespace=14, prototype=127, struct=15, typedef=4
- PublicDependencyModuleNames: Core, CoreUObject, Messaging, MessagingCommon, TraceLog

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/EngineEditorBridge.h` (Public)


#### class `UE::TraceBasedDebuggers::FEngineEditorBridge`  
`class FEngineEditorBridge`  
_L26-112_
- desc: Object that bridges the gap between a given debugger runtime module and the Engine & associated editor. As the debugger runtime module often does not have access to the engine module, this object reacts to events and performs necessary operations the runtime module cannot do directly.
- L31 _public typedef_ `typedef FNoLoggingCategory FLogCategoryAlias;`
- L36 _public prototype_ `FEngineEditorBridge() = delete;`
- L37 _public prototype_ `explicit FEngineEditorBridge(const FLogCategoryAlias& LogCategory);`
- L39 _public prototype_ `virtual ~FEngineEditorBridge() = default;`
- L41 _public prototype_ `void Initialize();`
- L42 _public prototype_ `void TearDown();`
- L44 _public prototype_ `TSharedPtr<FRemoteSessionsManager> GetSessionsManager() const;`
- L53 _public prototype_ `void RegisterRemoteSessionsHandler(TSharedRef<IRemoteSessionsHandler> Handler);` — Derived classes can use this method to register a remote sessions handler that adds support for more message types. Method will ensure if a handler is already registered. The handler will be automatically unregistered from the session manager when the Engine-Editor bridge gets teared down.
- L55 _public function_ `TSharedPtr<IDataRelayTransport> GetTraceRelayTransportInstance()`
- L60 _public function_ `bool IsInitialized() const`
- L65 _public function_ `FSimpleMulticastDelegate& OnEngineEditorBridgeInitialized()`
- L70 _public prototype_ `void SetDataRelayTransportInstance(const TSharedPtr<IDataRelayTransport>& InExternalTraceRelayInstance);`
- L73 _protected prototype_ `void HandleRecordingStarted();`
- L74 _protected prototype_ `void HandleRecordingStopped();`
- L75 _protected prototype_ `void BroadcastSessionStatus() const;`
- L77 _protected function_ `virtual void OnInitializeInternal()`
- L81 _protected function_ `virtual void OnTearDownInternal()`
- L85 _protected function_ `virtual void OnRecordingStartedInternal()`
- L89 _protected function_ `virtual void OnRecordingStoppedInternal()`
- L93 _protected function_ `virtual void BuildRecordingStatusInternal(FRecordingStatusMessage& OutStatusMessage) const`
- L98 _private member_ `TSharedPtr<IDataRelayTransport> RelayTraceDataTransportInstance;`
- L100 _private member_ `static TWeakPtr<FRemoteSessionsManager> SharedRemoteSessionsManager;`
- L101 _private member_ `TSharedRef<FRemoteSessionsManager> RemoteSessionsManager;`
- L103 _private member_ `TSharedPtr<IRemoteSessionsHandler> RemoteSessionsHandler;` — Handler created by derived classes to handle more message types
- L105 _private member_ `const FLogCategoryAlias& LogCategory;`
- L107 _private member_ `FTSTicker::FDelegateHandle RecordingStatusUpdateHandle;`
- L109 _private member_ `FSimpleMulticastDelegate InitializedDelegate;`
- L111 _private member_ `bool bIsInitialized = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEBASEDDEBUGGERS_API`
- L15 _macro_ `#define WITH_TRACE_BASED_DEBUGGERS_EXTERNAL_MESSAGING 0`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/RelayTraceDataWriter.h` (Public)


#### struct `UE::TraceBasedDebuggers::FRelayTraceDataWriter`  
`struct FRelayTraceDataWriter`  
_L23-131_
- desc: Writer object that chunks trace data into smaller bunches and queues them so a relay instance can dequeue and send them over the network later
- L26 _public typedef_ `typedef FNoLoggingCategory FLogCategoryAlias;`
- L31 _public prototype_ `FRelayTraceDataWriter() = delete;`
- L32 _public prototype_ `explicit FRelayTraceDataWriter(const FLogCategoryAlias& LogCategory);`
- L34 _public prototype_ `~FRelayTraceDataWriter();`
- L40 _public prototype_ `void SetMaxBytesPerBunch(uint32 MaxBytes);` — Sets max number of bytes a queued bunch can have @param MaxBytes Greater than zero number of bytes to set as limit
- L46 _public prototype_ `void SetMaxAllowedPendingBytes(uint64 MaxBytes);` — Sets max number of bytes this writer can buffer before overflowing, triggering a close @param MaxBytes number of bytes to set as limit
- L48 _public prototype_ `static bool WriteHelper(UPTRINT WriterHandle, const void* Data, uint32 Size);`
- L50 _public function_ `static void CloseHelper(UPTRINT WriterHandle)`
- L63 _public prototype_ `TOptional<TUniquePtr<FBufferArchive>> DequeuePendingBunch();` — Dequeues a bunch ready to send over the network, if any
- L68 _public prototype_ `int32 NextPendingBunchSize() const;` — Returns the size of the next bunch in the queue
- L73 _public function_ `bool HasPendingBunches() const` — Returns true if we have any data pending to be sent over the network
- L81 _public prototype_ `int64 GetQueuedBytesNum() const;` — returns the number of bytes overall that are in the queue waiting to be sent
- L86 _public prototype_ `void Close();` — Closes this Writer. After this is called, no new data will be processed, but any pending data can still be dequeued and sent over
- L91 _public function_ `bool IsClosed() const` — Returns true if this writer is closed and no new data is being processed
- L96 _public function_ `DECLARE_DELEGATE(FNewDataAvailableDelegate) FNewDataAvailableDelegate& OnNewDataAvailable()`
- L102 _public function_ `FSimpleDelegate& OnDataOverflow()`
- L109 _private member_ `FNewDataAvailableDelegate NewDataAvailableDelegate;`
- L110 _private member_ `FNewDataAvailableDelegate DataOverflowDelegate;`
- L112 _private prototype_ `TUniquePtr<FBufferArchive> CreateBunch();`
- L114 _private prototype_ `bool Write_Internal(const void* Data, uint32 Size);`
- L116 _private prototype_ `bool CanWriteData(uint32 NewDataSize) const;`
- L118 _private member_ `const FLogCategoryAlias& LogCategory;`
- L119 _private member_ `TSpscQueue<TUniquePtr<FBufferArchive>> PendingBunchesToRelay;`
- L120 _private member_ `TUniquePtr<FBufferArchive> CurrentPendingBunch;`
- L121 _private member_ `std::atomic<int32> PendingBunchesCount = 0;`
- L122 _private member_ `std::atomic<bool> bClosed = false;`
- L123 _private member_ `uint32 MaxPendingBytesPerBunch = 0;`
- L124 _private member_ `std::atomic<int64> QueuedBytesNum = 0;`
- L125 _private member_ `uint64 MaxAllowedPendingBytes = 1073741824;`
- L128 _private member_ `int64 TotalBytesWritten = 0;` — Diagnostic counters — logged at Close() to diagnose relay data pipeline issues
- L129 _private member_ `int32 TotalWriteCalls = 0;`
- L130 _private member_ `int32 TotalBunchesCompleted = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TRACEBASEDDEBUGGERS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L96 _delegate_ `DECLARE_DELEGATE(FNewDataAvailableDelegate) FNewDataAvailableDelegate& OnNewDataAvailable() { return NewDataAvailableDelegate; } FSimpleDelegate& OnDataOverflow() { return DataOverflowDelegate; } private: FNewDataAvailableDelegate NewDataAvailableDelegate;`

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/RemoteSessionsManager.h` (Public)


#### struct `UE::TraceBasedDebuggers::FSessionPing`  
`struct FSessionPing`  
_L32-38_
- reflection: `USTRUCT(MinimalAPI)`
- L37 _public member_ `FGuid ControllerInstanceId;` — `UPROPERTY()`

#### struct `UE::TraceBasedDebuggers::FSessionPong`  
`struct FSessionPong`  
_L41-56_
- reflection: `USTRUCT(MinimalAPI)`
- L46 _public member_ `FGuid InstanceId;` — `UPROPERTY()`
- L49 _public member_ `FGuid SessionId;` — `UPROPERTY()`
- L52 _public member_ `FString SessionName;` — `UPROPERTY()`
- L55 _public member_ `uint8 BuildTargetType = static_cast<uint8>(EBuildTargetType::Unknown);` — `UPROPERTY()`

#### struct `UE::TraceBasedDebuggers::FStopRecordingCommandMessage`  
`struct FStopRecordingCommandMessage`  
_L59-62_
- reflection: `USTRUCT(MinimalAPI)`

#### struct `UE::TraceBasedDebuggers::FRecordingStatusMessage`  
`struct FRecordingStatusMessage`  
_L65-83_
- reflection: `USTRUCT(MinimalAPI)`
- L70 _public member_ `FGuid InstanceId = FGuid();` — `UPROPERTY()`
- L73 _public member_ `FGuid DebuggerId = FGuid();` — `UPROPERTY()`
- L76 _public member_ `FGuid RequesterId = FGuid();` — `UPROPERTY()`
- L79 _public member_ `float ElapsedTime = false;` — `UPROPERTY()`
- L82 _public member_ `int64 BufferedDataBytesSize = 0;` — `UPROPERTY()`

#### struct `UE::TraceBasedDebuggers::FTraceConnectionDetailsMessage`  
`struct FTraceConnectionDetailsMessage`  
_L86-95_
- reflection: `USTRUCT(MinimalAPI)`
- L91 _public member_ `FGuid InstanceId = FGuid();` — `UPROPERTY()`
- L94 _public member_ `FTraceConnectionDetails TraceDetails;` — `UPROPERTY()`

#### struct `UE::TraceBasedDebuggers::FStartRecordingCommandMessage`  
`struct FStartRecordingCommandMessage`  
_L98-113_
- reflection: `USTRUCT(MinimalAPI)`
- L103 _public member_ `FGuid InstanceId = FGuid();` — `UPROPERTY()`
- L106 _public member_ `FString Target;` — `UPROPERTY()`
- L109 _public member_ `ERecordingMode RecordingMode = ERecordingMode::Invalid;` — `UPROPERTY()`
- L112 _public member_ `ETraceTransportMode TransportMode = ETraceTransportMode::Invalid;` — `UPROPERTY()`

#### enum `UE::TraceBasedDebuggers::ERemoteSessionAttributes`  
`enum class ERemoteSessionAttributes`  
_L116-122_
- reflection: `UENUM()`
- L118 _public enumerator_ `None = 0`
- L119 _public enumerator_ `SupportsDataChannelChange = 1 << 0`
- L120 _public enumerator_ `CanExpire = 1 << 1`
- L121 _public enumerator_ `IsMultiSessionWrapper = 1 << 2`

#### struct `UE::TraceBasedDebuggers::IRemoteSessionsHandler`  
`struct IRemoteSessionsHandler : TSharedFromThis<IRemoteSessionsHandler>`  
_L129-144_
- inherits: `TSharedFromThis<IRemoteSessionsHandler>`
- L131 _public prototype_ `virtual ~IRemoteSessionsHandler() = default;`
- L134 _public prototype_ `virtual void OnCreatingMessageEndpoint(const TSharedPtr<FRemoteSessionsManager>&, FMessageEndpointBuilder&) = 0;` — Callback to allow registered sessions handlers to add additional message handlers to the message endpoint builder
- L137 _public prototype_ `virtual void OnSubscribingMessageTypes(const TSharedPtr<FRemoteSessionsManager>&, FMessageEndpoint&) = 0;` — Callback to allow registered sessions handlers to subscribe to specific message types
- L140 _public prototype_ `virtual void OnBuildingFullSessionInfoResponseMessage(FFullSessionInfoResponseMessage&) = 0;` — Callback to allow registered sessions handlers to build the response for a session information request
- L143 _public prototype_ `virtual void OnHandlingFullSessionInfoResponseMessage(const FFullSessionInfoResponseMessage&, const TSharedPtr<FSessionInfo>&) = 0;` — Callback to allow registered sessions handlers to process the response for a session information request

#### struct `UE::TraceBasedDebuggers::FRemoteSessionsManager`  
`struct FRemoteSessionsManager : TSharedFromThis<FRemoteSessionsManager>`  
_L147-483_
- inherits: `TSharedFromThis<FRemoteSessionsManager>`
- desc: Object that is able to discover, issue and execute commands back and forth between the trace-based debuggers and client/server/editor instances
- L149 _public prototype_ `FRemoteSessionsManager();`
- L150 _public prototype_ `virtual ~FRemoteSessionsManager();`
- L152 _public prototype_ `void ReInitializeMessagingSystem(const TSharedPtr<IMessageBus>& InMessageBus);`
- L154 _public function_ `FSimpleMulticastDelegate& OnSessionsUpdated()`
- L159 _public function_ `FSessionLifetimeDelegate& OnSessionDiscovered()`
- L164 _public function_ `FSessionLifetimeDelegate& OnSessionExpired()`
- L168 _public prototype_ `void RegisterExternalHandler(TSharedRef<IRemoteSessionsHandler> Handler);`
- L169 _public prototype_ `void UnregisterExternalHandler(TSharedRef<IRemoteSessionsHandler> Handler);`
- L171 _public typedef_ `typedef TFunction<void(const UScriptStruct*)> FVisitorFunction;`
- L177 _public prototype_ `void EnumerateMessageTypes(const FVisitorFunction& InVisitor);` — Enumerate messages types allowed by this module. @param InVisitor
- L182 _public prototype_ `void StartSessionDiscovery(const FGuid& InDebuggerGuid);` — Starts sending ping requests that potential targets (client, servers or other editors) can answer to and report themselves as available
- L184 _public function_ `void StartSessionDiscovery()` — `UE_DEPRECATED(5.8, "Use overload taking a debugger guid")`
- L192 _public prototype_ `void StopSessionDiscovery(const FGuid& InDebuggerGuid);` — Stop sending ping requests to potential targets (client, servers or other editors).
- L194 _public function_ `void StopSessionDiscovery()` — `UE_DEPRECATED(5.8, "Use overload taking a debugger guid")`
- L205 _public function_ `template <typename T> void SendCommand(const FMessageAddress& InDestinationAddress, const T& InMessage)` — Issues a command to the provided address to change the state of a data channel @param InDestinationAddress Message bus address that will execute the command @param InMessage New data channel state to apply in the receiving instance
- L227 _public prototype_ `TWeakPtr<FSessionInfo> GetSessionInfo(FGuid Id);` — Returns the session info object for the provided ID @param Id SessionID
- L232 _public prototype_ `TWeakPtr<FSessionInfo> GetFirstAvailableSingleSessionInfo();` — Returns the first available session info
- L239 _public function_ `template <typename CallbackType> void EnumerateActiveSessions(const CallbackType& Callback)` — Iterates through all active and valid sessions, and executes the provided callback to it. if the callbacks returns false, the iteration will stop
- L260 _public function_ `template <typename T> void PublishMessage(const T& InMessage)` — Broadcast to the network a given message @param InMessage message to broadcast
- L271 _public function_ `FRecordingStateChangeDelegate& OnSessionRecordingStarted()` — Delegate that broadcast when a recording was started in a session (either local or remote)
- L279 _public function_ `FRecordingStateChangeDelegate& OnSessionRecordingStopped()` — Delegate that broadcast when a recording stops in a session (either local or remote)
- L284 _public member_ `static const FString AllRemoteSessionsTargetName;`
- L285 _public member_ `static const FString AllRemoteServersTargetName;`
- L286 _public member_ `static const FString AllRemoteClientsTargetName;`
- L287 _public member_ `static const FString AllSessionsTargetName;`
- L288 _public member_ `static const FString CustomSessionsTargetName;`
- L289 _public member_ `static const FString LocalEditorSessionName;`
- L290 _public member_ `static const FName MessageBusEndpointName;`
- L291 _public member_ `static const FGuid AllRemoteSessionsWrapperGUID;`
- L292 _public member_ `static const FGuid AllRemoteServersWrapperGUID;`
- L293 _public member_ `static const FGuid AllRemoteClientsWrapperGUID;`
- L294 _public member_ `static const FGuid AllSessionsWrapperGUID;`
- L295 _public member_ `static const FGuid CustomSessionsWrapperGUID;`
- L296 _public member_ `static const FGuid InvalidSessionGUID;`
- L297 _public member_ `static const FGuid LocalEditorSessionID;`
- L299 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMessagingInitialized, TSharedPtr<IMessageBus> NewMessageBus, TSharedPtr<FMessageEndpoint> NewEndpoint);`
- L300 _public function_ `FMessagingInitialized& OnMessagingInitialized()`
- L305 _public function_ `TWeakPtr<IMessageBus> GetMessageBusInstance()`
- L310 _public function_ `TWeakPtr<FMessageEndpoint> GetMessageBusEndPoint()`
- L318 _public function_ `static constexpr bool IsController()` — Returns true if this instance has controller capabilities (is either an editor or standalone application, which is also an editor)
- L333 _public prototype_ `bool CanPublishToNetwork(const FTopLevelAssetPath& MessageType) const;` — Returns true if this instance can publish messages to remote endpoints via a network bridge. Checks for a standard bridge (e.g., UdpMessaging via -messaging flag) or a per-type bridge set using SetMessageBridge. @see SetMessageBridge
- L337 _public function_ `template <typename TMessageType> bool CanPublishToNetwork() const` — Templated convenience wrapper for CanPublishToNetwork.
- L346 _public prototype_ `void RegisterExternalSupportedMessageType(const UScriptStruct* ScriptStruct);` — Adds a message type to the list of supported message types for this session system. @param ScriptStruct Message type info
- L352 _public function_ `template <typename TDataType> void RegisterExternalSupportedMessageType()` — Adds a message type to the list of supported message types for this session system.
- L362 _public function_ `FOnSupportedMessageTypesChanged& OnSupportedMessageTypesChanged()` — Delegate broadcast whenever the supported message types list changes. Callers that maintain external message bridges with per-type subscriptions should bind to this delegate to keep bridge subscriptions in sync.
- L373 _public function_ `void SetMessageBridge(const TSharedPtr<IMessageBridge>& InMessageBridge)` — Sets an external message bridge for per-type reachability checks. When set, CanPublishToNetwork queries the bridge's IsSubscribed to determine if a specific message type can reach remote endpoints. @param InMessageBridge The bridge to query, or nullptr to clear.
- L379 _private prototype_ `void Initialize();`
- L380 _private prototype_ `void Shutdown();`
- L382 _private prototype_ `void RegisterBuiltInMessageTypes();`
- L384 _private prototype_ `void InitializeMessagingSystem(const TSharedPtr<IMessageBus>& InMessageBus);`
- L385 _private prototype_ `void ShutdownMessagingSystem();`
- L386 _private prototype_ `void BroadcastSupportedMessageTypes();`
- L392 _private prototype_ `void SendFullSessionStateRequestCommand(const FMessageAddress& InDestinationAddress);` — Sends a request to obtain the full session information to the provided message bus address @param InDestinationAddress
- L398 _private prototype_ `void RegisterSessionInMultiSessionWrapper(const TSharedRef<FSessionInfo>& InSessionInfoRef);` — Registers a session object that is able to control multiple session instances @param InSessionInfoRef Multi Session object
- L404 _private prototype_ `void DeRegisterSessionInMultiSessionWrapper(const TSharedRef<FSessionInfo>& InSessionInfoRef);` — Deregisters a session object that is able to control multiple session instances @param InSessionInfoRef Multi Session object
- L412 _private prototype_ `TSharedPtr<FSessionInfo> CreatedWrapperSessionInfo(FGuid InstanceId, FStringView SessionName);` — Creates a session object that is able to control multiple other session objects. @param InstanceId Instance ID for this object @param SessionName Session name that will be used in the UI @return
- L417 _private prototype_ `TSharedPtr<FMessageEndpoint> CreateEndPoint(const TSharedRef<IMessageBus>& InMessageBus);` — Creates the message bus endpoint this session manager will use
- L419 _private prototype_ `bool Tick(float DeltaTime);`
- L424 _private prototype_ `void SendPing();` — Usually used by the controller. Broadcast to the network this controller exists.
- L431 _private prototype_ `void SendPong(const FSessionPing& InMessage, const TSharedRef<IMessageContext>& InContext);` — Replies directly to the ping sender with a small subset of this instance information. @param InMessage Ping message that was received @param InContext Message context for the received Ping
- L433 _private prototype_ `void HandleSessionPongMessage(const FSessionPong& InMessage, const TSharedRef<IMessageContext>& InContext);`
- L434 _private prototype_ `void HandleSessionPingMessage(const FSessionPing& InMessage, const TSharedRef<IMessageContext>& InContext);`
- L435 _private prototype_ `void HandleRecordingStatusUpdateMessage(const FRecordingStatusMessage& InMessage, const TSharedRef<IMessageContext>& InContext);`
- L436 _private prototype_ `void HandleConnectionDetailsUpdateMessage(const FTraceConnectionDetailsMessage& InMessage, const TSharedRef<IMessageContext>& InContext);`
- L437 _private prototype_ `void HandleFullSessionStateRequestMessage(const FFullSessionInfoRequestMessage& InMessage, const TSharedRef<IMessageContext>& InContext);`
- L438 _private prototype_ `void HandleFullSessionStateResponseMessage(const FFullSessionInfoResponseMessage& InMessage, const TSharedRef<IMessageContext>& InContext);`
- L445 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(ERemoveSessionOptions) void RemoveExpiredSessions(ERemoveSessionOptions Options = ERemoveSessionOptions::None);`
- L449 _private prototype_ `void ProcessPendingMessagesForSession(const FSessionPong& InMessage, const TSharedRef<FSessionInfo>& InSessionInfoPtr);`
- L451 _private member_ `TArray<TSharedRef<IRemoteSessionsHandler>> Handlers;`
- L454 _private member_ `FDateTime LastPingTime;` — Holds the time at which the last ping was sent.
- L457 _private member_ `TWeakPtr<IMessageBus> MessageBusPtr;` — Holds a pointer to the message bus.
- L460 _private member_ `TSharedPtr<FMessageEndpoint> MessageEndpoint;` — Holds the messaging endpoint.
- L462 _private member_ `TMap<FGuid, TSharedPtr<FSessionInfo>> ActiveSessionsById;`
- L463 _private member_ `TMap<FGuid, FRecordingStatusMessage> PendingRecordingStatusMessages;`
- L464 _private member_ `TMap<FGuid, FTraceConnectionDetails> PendingRecordingConnectionDetailsMessages;`
- L466 _private member_ `FSimpleMulticastDelegate SessionsUpdatedDelegate;`
- L467 _private member_ `FSessionLifetimeDelegate SessionDiscoveredDelegate;`
- L468 _private member_ `FSessionLifetimeDelegate SessionExpiredDelegate;`
- L470 _private member_ `FRecordingStateChangeDelegate RecordingStartedDelegate;`
- L471 _private member_ `FRecordingStateChangeDelegate RecordingStoppedDelegate;`
- L473 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L475 _private member_ `FMessagingInitialized MessagingInitializedDelegate;`
- L477 _private member_ `TArray<FGuid> ActiveDebuggersUsingSessionDiscovery;`
- L478 _private member_ `TArray<const UScriptStruct*> SupportedMessageTypes;`
- L479 _private member_ `TSharedPtr<IMessageBridge> CustomMessageBridge;`
- L480 _private member_ `FOnSupportedMessageTypesChanged SupportedMessageTypesChangedDelegate;`
- L482 _private member_ `bool bInitialized = false;`

#### enum `UE::TraceBasedDebuggers::FRemoteSessionsManager::ERemoveSessionOptions`  
`enum class ERemoveSessionOptions : uint8`  
_L440-444_
- L442 _public enumerator_ `None = 0`
- L443 _public enumerator_ `ForceRemoveAll = 1 << 0`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TRACEBASEDDEBUGGERS_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRecordingStateChangeDelegate, const TSharedPtr<FSessionInfo>&);`
- L125 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRecordingStateChangeDelegate, const TSharedPtr<FSessionInfo>&);` (scope `UE::TraceBasedDebuggers`)
- L126 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSessionLifetimeDelegate, const TSharedPtr<FSessionInfo>&);`
- L126 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSessionLifetimeDelegate, const TSharedPtr<FSessionInfo>&);` (scope `UE::TraceBasedDebuggers`)
- L127 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSupportedMessageTypesChanged, TConstArrayView<const UScriptStruct*>);`
- L127 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSupportedMessageTypesChanged, TConstArrayView<const UScriptStruct*>);` (scope `UE::TraceBasedDebuggers`)
- L299 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMessagingInitialized, TSharedPtr<IMessageBus> NewMessageBus, TSharedPtr<FMessageEndpoint> NewEndpoint);`

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/SessionInfo.h` (Public)


#### struct `UE::TraceBasedDebuggers::FFullSessionInfoRequestMessage`  
`struct FFullSessionInfoRequestMessage`  
_L16-19_
- reflection: `USTRUCT(MinimalAPI)`

#### struct `UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage`  
`struct FFullSessionInfoResponseMessage`  
_L22-63_
- reflection: `USTRUCT(MinimalAPI)`
- L27 _public function_ `template <typename DataType> DataType* GetDebuggerData()`
- L40 _public function_ `template <typename DataType> const DataType* GetDebuggerData() const`
- L53 _public member_ `FGuid InstanceId;` — `UPROPERTY()`
- L56 _public member_ `FGuid DebuggerId = FGuid();` — `UPROPERTY()`
- L59 _public member_ `TArray<FInstancedStruct> DebuggerSpecificData;` — `UPROPERTY()`
- L62 _public member_ `FGuid RecordingRequesterId = FGuid();` — `UPROPERTY()`

#### enum `UE::TraceBasedDebuggers::ERemoteSessionReadyState`  
`enum class ERemoteSessionReadyState : uint8`  
_L66-72_
- reflection: `UENUM()`
- L69 _public enumerator_ `Ready` — The session is ready to execute commands
- L71 _public enumerator_ `Busy` — We are executing a command in the session we expect to take a while without hearing anything from the target.

#### struct `UE::TraceBasedDebuggers::FSessionInfo`  
`struct FSessionInfo`  
_L77-163_
- desc: Session object that contains all the information needed to communicate with a remote instance, and the state of that instance
- L79 _public function_ `explicit FSessionInfo() : InstanceId(FGuid()), SessionTypeAttributes(ERemoteSessionAttributes::CanExpire | ERemoteSessionAttributes::SupportsDataChannelChange)`
- L84 _public prototype_ `virtual ~FSessionInfo() = default;`
- L88 _protected function_ `explicit FSessionInfo(ERemoteSessionAttributes InSessionTypeAttributes) : SessionTypeAttributes(InSessionTypeAttributes)`
- L95 _public function_ `template <typename DataType> DataType* GetDebuggerData()`
- L109 _public function_ `template <typename DataType> void SetDebuggerData(DataType&& NewSessionData)` — Append or update data associated to a given debugger type
- L121 _public member_ `FGuid InstanceId;`
- L122 _public member_ `FString SessionName;`
- L123 _public member_ `FMessageAddress Address;`
- L124 _public member_ `FDateTime LastPingTime;`
- L125 _public member_ `EBuildTargetType BuildTargetType = EBuildTargetType::Unknown;`
- L126 _public member_ `ERemoteSessionReadyState ReadyState = ERemoteSessionReadyState::Ready;`
- L128 _public member_ `FRecordingStatusMessage LastKnownRecordingState;`
- L130 _public prototype_ `const FTraceConnectionDetails& GetTraceConnectionDetails();`
- L133 _public prototype_ `virtual bool IsAnyDebuggerRecording() const;` — @return Whether any debugger is currently recording, regardless of its type, or by which application instance it was requested
- L140 _public prototype_ `virtual bool IsRecording(const FGuid& DebuggerTypeId) const;` — Indicates whether a given debugger type has an active recording requested by the current application instance. @param DebuggerTypeId The identifier of the debugger type @return Whether the provided debugger type id is currently recording
- L142 _public prototype_ `virtual uint64 GetBufferedBytesNum() const;`
- L144 _public function_ `ERemoteSessionAttributes GetSessionTypeAttributes() const`
- L149 _public prototype_ `void SetReceivedBytesPerSecond(uint64 InNewBytesPerSecond);`
- L150 _public prototype_ `uint64 GetReceivedBytesPerSecond() const;`
- L154 _protected member_ `TArray<FInstancedStruct> DebuggerSpecificSessionData;`
- L156 _protected member_ `FTraceConnectionDetails LastKnownConnectionDetails;`
- L158 _protected member_ `uint64 ReceivedBytesPerSecond = 0;`
- L160 _protected member_ `const ERemoteSessionAttributes SessionTypeAttributes;`

#### struct `UE::TraceBasedDebuggers::FMultiSessionInfo`  
`struct FMultiSessionInfo : FSessionInfo`  
_L169-198_
- inherits: `FSessionInfo`
- desc: Session object that is able to control and provide information about multiple session objects. Used so the UI can use the same API to control multiple sessions like it does for single sessions.
- L171 _public function_ `explicit FMultiSessionInfo() : FSessionInfo(ERemoteSessionAttributes::IsMultiSessionWrapper)`
- L175 _public prototype_ `virtual ~FMultiSessionInfo() override = default;`
- L177 _public prototype_ `virtual bool IsRecording(const FGuid& DebuggerTypeId) const override;`
- L178 _public prototype_ `virtual bool IsAnyDebuggerRecording() const override;`
- L180 _public prototype_ `virtual uint64 GetBufferedBytesNum() const override;`
- L183 _public function_ `template<typename TCallback> void EnumerateInnerSessions(const TCallback& Callback) const`
- L197 _public member_ `TMap<FGuid, TWeakPtr<FSessionInfo>> InnerSessionsByInstanceID;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TRACEBASEDDEBUGGERS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/TraceBasedDebuggerRuntime.h` (Public)


#### class `UE::TraceBasedDebuggers::FRuntimeModule`  
`class FRuntimeModule`  
_L25-255_
- L28 _private typedef_ `typedef FNoLoggingCategory FLogCategoryAlias;`
- L34 _protected prototype_ `FRuntimeModule() = delete;`
- L35 _protected prototype_ `explicit FRuntimeModule(const FLogCategoryAlias& InLogCategory, const FGuid& InDebuggerTypeID);`
- L37 _protected prototype_ `virtual ~FRuntimeModule();`
- L43 _protected prototype_ `bool TryRecordOnStartup();` — Parses the command line arguments for <AutoRecordCommand>, if set, then start recording if the command is found. @return Whether the recording was started.
- L57 _public prototype_ `void StartRecording(TConstArrayView<FString> Args);` — Starts a recording by starting a Trace session. It will stop any existing trace session. @param Args : Arguments array usually provided by the commandline. Used to determine if we want to record to file or a local trace server. Available options are: - "" (default): trace to file using GenerateRecordingFileName - "File": trace to file using GenerateRecordingFileName - "-tracefile [FILENAME]": trace to file using either the optional [FILENAME] or GenerateRecordingFileName - "Server [ADDRESS]": trace server using either the optional [ADDRESS] or local host (i.e., "127.0.0.1") - "-tracehost [ADDRESS]": trace server using either the optional [ADDRESS] or local host (i.e., "127.0.0.1") @see GenerateRecordingFileName
- L64 _public prototype_ `void StartRecording(const FStartRecordingCommandMessage& InRecordingStartCommand);`
- L67 _public prototype_ `void StopRecording();` — Stops an active recording
- L70 _public function_ `bool IsRecording() const` — Returns true if we are currently recording trace data for the current debugger
- L76 _public function_ `const FGuid& GetRecordingRequesterId() const` — @return Unique identifier of the application instance that requested the current recording, if active.
- L82 _public function_ `const FGuid& GetDebuggerId() const` — @return Unique identifier for the current debugger type
- L93 _public prototype_ `void GenerateRecordingFileName(FString& OutFileName) const;` — Finds a valid file name for a new file for Trace recording. The file name is built using the following format: <DebuggerName>-<ProjectName>-<BuildTargetType>-<DateTime> where <DebuggerName> is provided by the derived classes.
- L96 _public prototype_ `FTraceConnectionDetails GetCurrentTraceConnectionDetails() const;` — Return the current connection details for the underlying trace session
- L99 _public function_ `float GetAccumulatedRecordingTime() const` — Returns the accumulated recording time in seconds since the recording started
- L105 _public prototype_ `int64 GetBufferedDataBytesSize() const;` — Returns the accumulated current send buffer size used by the relay transport system - This should be used for logging or UI feedback only
- L113 _public prototype_ `bool WaitForTraceChannelsEnabled(float MaxWaitTimeSeconds);` — Blocks the calling thread until trace channels have been enabled after a recording has started, or until the timeout expires. Intended for use on the game thread to synchronize PIE startup with asynchronous trace channel enablement. @param MaxWaitTimeSeconds Maximum time to wait in seconds before giving up. @return true if channels were enabled within the timeout, false otherwise.
- L115 _public function_ `FSimpleMulticastDelegate& OnTraceConnectionDetailsUpdated()`
- L124 _public prototype_ `void RegisterExternalRelayExecutor(const FRelayTraceDataDelegate& InExternalRelayExecutor);` — Registers an external handler that will be in charge of relaying the traced data to a remote instance if the relay transport mode is selected @param InExternalRelayExecutor Delegate that will be executed to relay data to a remote debugger instance, periodically
- L130 _public prototype_ `void RegisterExternalRelayOverflowHandler(const FSimpleDelegate& InExternalRelayOverflowHandler);` — Registers an external handler that will be in charge handling what happens when the Relay writer overflows @param InExternalRelayOverflowHandler Delegate that will be executed when the Relay writer overflows
- L135 _public prototype_ `void UnregisterExternalRelayOverflowHandler();` — Unbinds the delegate to an external relay overflow handler
- L140 _public prototype_ `void UnregisterCurrentExternalRelayExecutor();` — Unbinds the delegate to an external relay executor
- L146 _public prototype_ `void RegisterExternalTraceStatusProvider(const FExternalTraceConnectionStatusDelegate& InExternalTraceStatusCallback);` — Registers an external handler that will be in charge of providing the trace status if the recording mode is set to Relay @param InExternalTraceStatusCallback Delegate that will be executed to get the trace status, periodically
- L151 _public prototype_ `void UnregisterExternalTraceStatusProvider();` — Unbinds the delegate to the current external trace status provider
- L158 _public prototype_ `void RegisterExternalRelayBufferSizeProvider(const FExternalRelayBufferQueueSizeDelegate& InExternalRelayBufferSizeCallback);` — Registers an external handler that will provide information about any external send buffer the current relay transport implementation might be using, if any. This is used for UI metrics. To handle buffer overflows, use RegisterExternalRelayOverflowHandler @param InExternalRelayBufferSizeCallback
- L163 _public prototype_ `void UnregisterExternalRelayBufferSizeProvider();` — Unbinds the delegate to the current external Relay buffer size provider
- L165 _public function_ `FRelayTraceDataWriter* GetRelayTraceWriterInstance() const`
- L171 _protected prototype_ `virtual void OnRecordingStartingInternal();`
- L172 _protected prototype_ `virtual void OnRecordingStartedInternal();`
- L173 _protected prototype_ `virtual void OnRecordingStartFailedInternal(const FText& FailureReason);`
- L174 _protected prototype_ `virtual void OnRecordingStoppedInternal();`
- L176 _protected prototype_ `virtual void OnEnableRequiredTraceChannelsInternal();`
- L182 _protected member_ `FString DebuggerName;` — Prefix provided by the derived classes used by GenerateRecordingFileName using the following format "<DebuggerName>-<ProjectName>-<BuildTargetName>-<DateTime>.utrace"
- L187 _protected member_ `FString AutoRecordCommand;` — Command line provided by the derived classes used during initialization to start recording or not.
- L193 _protected member_ `FString HostAddressCommand = TEXT("Deb` — Command line that derived classes can override and used during initialization to specify the address of the host. e.g., -<HostAddressCommand>=x.x.x.x where 'HostAddressCommand' is set to 'DebuggerHost' by default.
- L195 _protected member_ `const FLogCategoryAlias& LogCategory;`
- L199 _private prototype_ `void HandleRelayOverflow();`
- L201 _private prototype_ `void RelayTraceData() const;`
- L203 _private prototype_ `void SetupRelayDataPumpDelegates();`
- L204 _private prototype_ `void ClearRelayDataPumpDelegates();`
- L207 _private prototype_ `void StopTrace();` — Stops the current Trace session
- L210 _private prototype_ `bool RecordingTimerTick(float DeltaTime);` — Queues a full Capture of the simulation on the next frame
- L212 _private prototype_ `void HandleTraceConnectionEstablished();`
- L218 _private prototype_ `void HandleTraceStopRequest(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);` — Used to handle stop requests to the active trace session that were not done by us That is a possible scenario because Trace is shared by other In-Editor tools
- L220 _private prototype_ `bool WaitForTraceSessionDisconnect();`
- L222 _private prototype_ `void EnableRequiredTraceChannels();`
- L223 _private prototype_ `void SaveAndDisabledCurrentEnabledTraceChannels();`
- L224 _private prototype_ `void RestoreTraceChannelsToPreRecordingState();`
- L226 _private member_ `FTSTicker::FDelegateHandle RecordingTimerHandle;`
- L227 _private member_ `FTSTicker::FDelegateHandle RelayExecutorTickerHandle;`
- L229 _private member_ `FDelegateHandle OnConnectionDelegateHandle;`
- L230 _private member_ `FDelegateHandle OnTraceStoppedDelegateHandle;`
- L232 _private member_ `TUniquePtr<FRelayTraceDataWriter> RelayWriter;`
- L234 _private member_ `FSimpleMulticastDelegate TraceConnectionDetailsUpdatedDelegate;`
- L235 _private member_ `FSimpleDelegate ExternalRelayOverflowHandlerDelegate;`
- L236 _private member_ `FRelayTraceDataDelegate ExternalRelayExecutorDelegate;`
- L237 _private member_ `FExternalRelayBufferQueueSizeDelegate ExternalRelayBufferSizeProviderDelegate;`
- L238 _private member_ `FExternalTraceConnectionStatusDelegate ExternalTraceStatusDelegate;`
- L240 _private member_ `TMap<FString, bool> OriginalTraceChannelsState;`
- L243 _private member_ `FGuid DebuggerGuid;` — Unique identifier of the debugger type associated to this instance
- L248 _private member_ `float AccumulatedRecordingTime = 0.0f;`
- L250 _private member_ `ETraceTransportMode CurrentTransportMode = ETraceTransportMode::Invalid;`
- L251 _private member_ `bool bRequestedStop = false;`
- L254 _private member_ `FEventRef TraceChannelsEnabledEvent{EEventMode::ManualReset};` — Event signaled when HandleTraceConnectionEstablished completes and trace channels are enabled

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TRACEBASEDDEBUGGERS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE(FRecordingStateChangedDelegate) DECLARE_MULTICAST_DELEGATE_OneParam(FRecordingStartFailedDelegate, const FText&) DECLARE_DELEGATE_OneParam(FRelayTraceDataDelegate, FRelayTraceDataWriter&) DECLARE_DELEGATE_RetVal(FTraceConnectionDetails, FExternalTraceConnectionStatusDelegate) DECLARE_DELEGATE_RetVal(uint64, FExternalRelayBufferQueueSizeDelegate) class FRuntimeModule { #if NO_LOGGING typedef FNoLoggingCategory FLogCategoryAlias; #else typedef FLogCategoryBase FLogCategoryAlias; #endif protected: FRuntimeModule() = delete; explicit FRuntimeModule(const FLogCategoryAlias& InLogCategory, const FGuid& InDebuggerTypeID); virtual ~FRuntimeModule(); bool TryRecordOnStartup(); public: void StartRecording(TConstArrayView<FString> Args);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRecordingStartFailedDelegate, const FText&) DECLARE_DELEGATE_OneParam(FRelayTraceDataDelegate, FRelayTraceDataWriter&) DECLARE_DELEGATE_RetVal(FTraceConnectionDetails, FExternalTraceConnectionStatusDelegate) DECLARE_DELEGATE_RetVal(uint64, FExternalRelayBufferQueueSizeDelegate) class FRuntimeModule { #if NO_LOGGING typedef FNoLoggingCategory FLogCategoryAlias; #else typedef FLogCategoryBase FLogCategoryAlias; #endif protected: FRuntimeModule() = delete; explicit FRuntimeModule(const FLogCategoryAlias& InLogCategory, const FGuid& InDebuggerTypeID); virtual ~FRuntimeModule(); bool TryRecordOnStartup(); public: void StartRecording(TConstArrayView<FString> Args); /**`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FRelayTraceDataDelegate, FRelayTraceDataWriter&) DECLARE_DELEGATE_RetVal(FTraceConnectionDetails, FExternalTraceConnectionStatusDelegate) DECLARE_DELEGATE_RetVal(uint64, FExternalRelayBufferQueueSizeDelegate) class FRuntimeModule { #if NO_LOGGING typedef FNoLoggingCategory FLogCategoryAlias; #else typedef FLogCategoryBase FLogCategoryAlias; #endif protected: FRuntimeModule() = delete; explicit FRuntimeModule(const FLogCategoryAlias& InLogCategory, const FGuid& InDebuggerTypeID); virtual ~FRuntimeModule(); bool TryRecordOnStartup(); public: void StartRecording(TConstArrayView<FString> Args); /** * Starts a recording by starting a Trace session. It will stop any existing trace session`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(FTraceConnectionDetails, FExternalTraceConnectionStatusDelegate) DECLARE_DELEGATE_RetVal(uint64, FExternalRelayBufferQueueSizeDelegate) class FRuntimeModule { #if NO_LOGGING typedef FNoLoggingCategory FLogCategoryAlias; #else typedef FLogCategoryBase FLogCategoryAlias; #endif protected: FRuntimeModule() = delete; explicit FRuntimeModule(const FLogCategoryAlias& InLogCategory, const FGuid& InDebuggerTypeID); virtual ~FRuntimeModule(); bool TryRecordOnStartup(); public: void StartRecording(TConstArrayView<FString> Args); /** * Starts a recording by starting a Trace session. It will stop any existing trace session * @param InRecordingStartCommand : Used to determine if we want to record to file or a local trace server among other settings`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(uint64, FExternalRelayBufferQueueSizeDelegate) class FRuntimeModule { #if NO_LOGGING typedef FNoLoggingCategory FLogCategoryAlias; #else typedef FLogCategoryBase FLogCategoryAlias; #endif protected: FRuntimeModule() = delete; explicit FRuntimeModule(const FLogCategoryAlias& InLogCategory, const FGuid& InDebuggerTypeID); virtual ~FRuntimeModule(); bool TryRecordOnStartup(); public: void StartRecording(TConstArrayView<FString> Args);`

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/TraceBasedDebuggerTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TRACEBASEDDEBUGGERS_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceBasedDebuggers, Log, All);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L15 _prototype_ `extern EBuildTargetType GetBuildTargetType();` (scope `UE::TraceBasedDebuggers`)

### `Source/Runtime/Experimental/TraceBasedDebuggers/Public/TraceDataRelayTransport.h` (Public)


#### enum `UE::TraceBasedDebuggers::ERecordingMode`  
`enum class ERecordingMode : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `Invalid`
- L16 _public enumerator_ `Live`
- L17 _public enumerator_ `File`

#### enum `UE::TraceBasedDebuggers::ETraceTransportMode`  
`enum class ETraceTransportMode : uint8`  
_L22-33_
- reflection: `UENUM()`
- desc: Available transport modes for the Trace Data produced by the trace-based debuggers
- L24 _public enumerator_ `Invalid UMETA(Hidden)`
- L26 _public enumerator_ `FileSystem UMETA(Hidden)` — The data will be traced directly to a file in the local file system
- L28 _public enumerator_ `TraceServer UMETA(Hidden)` — Data will be traced to the selected trace store server
- L30 _public enumerator_ `Direct` — Data will be traced directly to the editor, accessible via sockets
- L32 _public enumerator_ `Relay` — Data will be traced via the trace relay system using a custom transport, like normal UE Networking or a direct socket connection

#### struct `UE::TraceBasedDebuggers::FTraceConnectionDetails`  
`struct FTraceConnectionDetails`  
_L37-79_
- reflection: `USTRUCT()`
- desc: Structure containing the info necessary to connect to a trace session and start receiving data
- L41 _public prototype_ `FTraceConnectionDetails() = default;`
- L43 _public function_ `void MarkAsValid()`
- L48 _public function_ `bool IsValid() const`
- L55 _public member_ `FGuid TraceGuid;` — `UPROPERTY()` — ID used to find the active trace session in the trace system
- L59 _public member_ `FGuid SessionGuid;` — `UPROPERTY()` — ID from the trace-based debugger remote session from which this connection details come from
- L63 _public member_ `FString TraceTarget;` — `UPROPERTY()` — Address of the trace server or editor in direct trace mode that will receive the trace data
- L67 _public member_ `uint16 Port = 0;` — `UPROPERTY()` — Port number used for the trace connection, if any
- L71 _public member_ `ETraceTransportMode TransportMode = ETraceTransportMode::Invalid;` — `UPROPERTY()` — How the data is being transported to the editor (Trace Server, Custom Relay, Direct, etc.)
- L75 _public member_ `TArray<uint8> CertAuth;` — `UPROPERTY()` — Encoded SSL certificate for the trace connection, if any
- L78 _public member_ `bool bIsValid = false;` — `UPROPERTY()`

#### struct `UE::TraceBasedDebuggers::FRelayConnectionInfo`  
`struct FRelayConnectionInfo`  
_L84-99_
- reflection: `USTRUCT()`
- desc: Structure containing the details necessary to connect to a relay instance
- L90 _public member_ `FString Address;` — `UPROPERTY()` — Relay IP address
- L94 _public member_ `uint16 Port = 0;` — `UPROPERTY()` — Relay port
- L98 _public member_ `TArray<uint8> CertificateAuthority;` — `UPROPERTY()` — Encoded SSL certificate

#### enum `UE::TraceBasedDebuggers::EConnectionAttemptResult`  
`enum class EConnectionAttemptResult : uint8`  
_L106-112_
- desc: Possible connection attempt results
- L108 _public enumerator_ `NotStarted`
- L109 _public enumerator_ `InProgress`
- L110 _public enumerator_ `Success`
- L111 _public enumerator_ `Failed`

#### class `UE::TraceBasedDebuggers::IDataRelayTransport`  
`class IDataRelayTransport`  
_L117-134_
- desc: Interface for any trace-based debugger relay transport implementation
- L120 _public prototype_ `virtual ~IDataRelayTransport() = default;`
- L122 _public prototype_ `virtual void Initialize() = 0;`
- L123 _public prototype_ `virtual void Shutdown() = 0;`
- L125 _public prototype_ `DECLARE_DELEGATE_OneParam(FProcessReceivedRelayDataDelegate, const TConstArrayView<uint8> DataPacket);`
- L126 _public prototype_ `virtual void RegisterRelayDataReceiverForSessionID(FGuid RemoteSessionID, const FProcessReceivedRelayDataDelegate& InProcessDataDelegate) = 0;`
- L127 _public prototype_ `virtual void UnregisterRelayDataReceiverForSessionID(FGuid RemoteSessionID) = 0;`
- L129 _public prototype_ `virtual void RelayTraceDataFromWriter(FRelayTraceDataWriter& InRelayTraceDataWriter) = 0;`
- L131 _public prototype_ `virtual FRelayConnectionInfo GetConnectionInfo() = 0;`
- L132 _public prototype_ `virtual EConnectionAttemptResult ConnectToRelay(FGuid RemoteSessionID, const FRelayConnectionInfo ConnectionInfo) = 0;`
- L133 _public prototype_ `virtual EConnectionAttemptResult GetConnectionAttemptResult(FGuid RemoteSessionID) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L125 _delegate_ `DECLARE_DELEGATE_OneParam(FProcessReceivedRelayDataDelegate, const TConstArrayView<uint8> DataPacket);`
