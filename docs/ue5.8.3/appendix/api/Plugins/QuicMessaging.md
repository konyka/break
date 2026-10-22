# Plugins / QuicMessaging

- module root: `Plugins/Experimental/QuicMessaging/Source/QuicMessaging`
- headers: 10; symbols: 266
- symbol kinds: class=9, delegate=6, enum=4, enumerator=13, function=52, macro=2, member=95, namespace=3, prototype=75, struct=3, typedef=2, variable=2
- DynamicallyLoadedModuleNames: Settings
- PrivateDependencyModuleNames: Cbor, CoreUObject, Json, JsonUtilities, Messaging, MsQuicRuntime, Networking, Projects, Serialization, Sockets, TraceLog
- PrivateIncludePathModuleNames: MessagingCommon, MsQuicRuntime, Settings
- PublicDependencyModuleNames: Core, QuicMessagingTransport

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Private/QuicMessagingPrivate.h` (Private)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogQuicMessaging, VeryVerbose, All);` — Declares a log category for this module.
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogQuicMessaging, VeryVerbose, All);` — Declares a log category for this module.
- L16 _macro_ `#define QUIC_MESSAGING_MAX_ANNOTATIONS 128` — Defines the maximum number of annotations a message can have.
- L19 _macro_ `#define QUIC_MESSAGING_MAX_RECIPIENTS 1024` — Defines the maximum number of recipients a message can have.
- L23 _variable_ `static FString MSQUIC_VERSION = "v2` — Defines the MsQuic version to be used.
- L26 _variable_ `static FString MSQUIC_BINARIES_PATH = "Binaries/ThirdParty` — Defines the MsQuic binaries path.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Private/Serialization/QuicDeserializedMessage.h` (Private)


#### enum `EQuicDeserializedMessageState`  
`enum class EQuicDeserializedMessageState`  
_L22-32_
- desc: Enumerates possibly states of a deserialized message.
- L25 _public enumerator_ `Complete` — The message data is complete.
- L28 _public enumerator_ `Incomplete` — The message data is incomplete.
- L31 _public enumerator_ `Invalid` — The message data is invalid.

#### class `FQuicDeserializedMessage`  
`class FQuicDeserializedMessage : public IMessageContext`  
_L38-222_
- inherits: `IMessageContext`
- desc: Holds deserialized message data.
- L47 _public prototype_ `FQuicDeserializedMessage() = delete;` — Default constructor.
- L52 _public function_ `FQuicDeserializedMessage(FInboundMessage InInboundMessage) : State(EQuicDeserializedMessageState::Incomplete) , InboundMessage(InInboundMessage) , Annotations(TMap<FName, FString>()) , Attachment(nullptr) , Expiration(FDateTime::UtcNow()) , MessageData(nullptr) , Recipients(TArray<FMessageAddress>()) , Scope(EMessageScope::All) , Flags(EMessageFlags::None) , Sender(FMessageAddress()) , TimeSent(FDateTime::UtcNow()) , TypeInfo(nullptr)` — Create and initialize a new instance.
- L68 _public function_ `virtual ~FQuicDeserializedMessage() override` — Virtual destructor.
- L87 _public function_ `EQuicDeserializedMessageState GetState() const` — Gets the state of the message data.
- L95 _public function_ `void UpdateState(EQuicDeserializedMessageState InState)` — Updates the state of this message data.
- L103 _public function_ `FInboundMessage& GetInboundMessage()` — Get the inbound message.
- L112 _public function_ `virtual const TMap<FName, FString>& GetAnnotations() const override`
- L117 _public function_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override`
- L122 _public function_ `virtual const FDateTime& GetExpiration() const override`
- L127 _public function_ `virtual const void* GetMessage() const override`
- L132 _public function_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override`
- L137 _public function_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override`
- L142 _public function_ `virtual const TArray<FMessageAddress>& GetRecipients() const override`
- L147 _public function_ `virtual EMessageScope GetScope() const override`
- L152 _public function_ `virtual EMessageFlags GetFlags() const override`
- L157 _public function_ `virtual const FMessageAddress& GetSender() const override`
- L162 _public function_ `virtual const FMessageAddress& GetForwarder() const override`
- L167 _public function_ `virtual ENamedThreads::Type GetSenderThread() const override`
- L172 _public function_ `virtual const FDateTime& GetTimeForwarded() const override`
- L177 _public function_ `virtual const FDateTime& GetTimeSent() const override`
- L185 _private member_ `EQuicDeserializedMessageState State;` — Holds the deserialized message state.
- L188 _private member_ `FInboundMessage InboundMessage;` — Holds the inbound message.
- L193 _private member_ `TMap<FName, FString> Annotations;` — Holds the optional message annotations.
- L196 _private member_ `TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> Attachment;` — Holds a pointer to attached binary data.
- L199 _private member_ `FDateTime Expiration;` — Holds the expiration time.
- L202 _private member_ `void* MessageData;` — Holds the message.
- L205 _private member_ `TArray<FMessageAddress> Recipients;` — Holds the message recipients.
- L208 _private member_ `EMessageScope Scope;` — Holds the message's scope.
- L211 _private member_ `EMessageFlags Flags;` — Holds the message's flags.
- L214 _private member_ `FMessageAddress Sender;` — Holds the sender's identifier.
- L217 _private member_ `FDateTime TimeSent;` — Holds the time at which the message was sent.
- L220 _private member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;` — Holds the message's type information.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Private/Serialization/QuicSerializationTasks.h` (Private)


#### class `FQuicSerializeMessageTask`  
`class FQuicSerializeMessageTask`  
_L19-99_
- L24 _public prototype_ `FQuicSerializeMessageTask() = delete;`
- L33 _public function_ `FQuicSerializeMessageTask( TSharedRef<IMessageContext, ESPMode::ThreadSafe> InMessageContext, TSharedPtr<FQuicSerializedMessage, ESPMode::ThreadSafe> InSerializedMessage, TSharedPtr<FEvent, ESPMode::ThreadSafe> InCompletionEvent) : MessageContext(InMessageContext) , SerializedMessage(InSerializedMessage) , CompletionEventPtr(InCompletionEvent)` — Creates a new serialize message task. @param InMessageContext The message context @param InSerializedMessage The serialized message @param InCompletionEvent The completion event
- L52 _private prototype_ `void SerializeMessage(FArchive& Archive, EQuicMessageFormat MessageFormat, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext, const EStructSerializerBackendFlags StructSerializerBackendFlags);` — Serializes the message. @param Archive The archive where data will be stored @param MessageFormat The message format @param InMessageContext Shared ref of the message context @param StructSerializerBackendFlags Flags for the struct serializer backend
- L64 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);` — Performs the actual task. @param CurrentThread The thread that this task is executing on @param MyCompletionGraphEvent The completion event
- L72 _public prototype_ `ENamedThreads::Type GetDesiredThread();` — Returns the name of the thread that this task should run on. @return The thread name
- L79 _public prototype_ `TStatId GetStatId() const;` — Gets the task's stats tracking identifier. @return Stats identifier
- L86 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();` — Gets the mode for tracking subsequent tasks. @return Always track subsequent tasks
- L91 _private member_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> MessageContext;` — The context of the message to serialize.
- L94 _private member_ `TSharedPtr<FQuicSerializedMessage, ESPMode::ThreadSafe> SerializedMessage;` — A reference to the serialized message data.
- L97 _private member_ `TWeakPtr<FEvent, ESPMode::ThreadSafe> CompletionEventPtr;` — An event signaling that the message was serialized.

#### class `FQuicDeserializeMessageTask`  
`class FQuicDeserializeMessageTask`  
_L102-177_
- L107 _public prototype_ `FQuicDeserializeMessageTask() = delete;`
- L116 _public function_ `FQuicDeserializeMessageTask( TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> InData, TSharedPtr<FQuicDeserializedMessage, ESPMode::ThreadSafe> InDeserializedMessage, TSharedPtr<FEvent, ESPMode::ThreadSafe> InCompletionEvent) : Data(InData) , DeserializedMessage(InDeserializedMessage) , CompletionEventPtr(InCompletionEvent)` — Creates a new deserialize message task. @param InData The data @param InDeserializedMessage The deserialized message @param InCompletionEvent The completion event
- L132 _private prototype_ `bool DeserializeMessage(FMemoryReader& MessageReader);` — Deserializes the message. @param MessageReader The already initialized message reader
- L142 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);` — Performs the actual task. @param CurrentThread The thread that this task is executing on @param MyCompletionGraphEvent The completion event
- L150 _public prototype_ `ENamedThreads::Type GetDesiredThread();` — Returns the name of the thread that this task should run on. @return The thread name
- L157 _public prototype_ `TStatId GetStatId() const;` — Gets the task's stats tracking identifier. @return Stats identifier
- L164 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();` — Gets the mode for tracking subsequent tasks. @return Always track subsequent tasks
- L169 _private member_ `TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> Data;` — A pointer to the unserialized message data.
- L172 _private member_ `TSharedPtr<FQuicDeserializedMessage, ESPMode::ThreadSafe> DeserializedMessage;` — A pointer to the deserialized message.
- L175 _private member_ `TWeakPtr<FEvent, ESPMode::ThreadSafe> CompletionEventPtr;` — An event signaling that the message was serialized.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Private/Serialization/QuicSerializedMessage.h` (Private)


#### enum `EQuicSerializedMessageState`  
`enum class EQuicSerializedMessageState`  
_L21-31_
- desc: Enumerates possibly states of a serialized message.
- L24 _public enumerator_ `Complete` — The message data is complete.
- L27 _public enumerator_ `Incomplete` — The message data is incomplete.
- L30 _public enumerator_ `Invalid` — The message data is invalid.

#### class `FQuicSerializedMessage`  
`class FQuicSerializedMessage`  
_L37-147_
- desc: Holds serialized message data.
- L42 _public prototype_ `FQuicSerializedMessage() = delete;`
- L45 _public function_ `FQuicSerializedMessage(EQuicMessageFormat InMessageFormat, EMessageFlags InFlags, TArray<FGuid> InRecipients, EQuicMessageType InMessageType, TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> InDataPtr, TSharedRef<IMessageContext, ESPMode::ThreadSafe> InMessageContext) : DataPtr(InDataPtr) , MessageContext(InMessageContext) , State(EQuicSerializedMessageState::Incomplete) , Flags(InFlags) , Format(InMessageFormat) , Recipients(InRecipients) , MessageType(InMessageType)` — Default constructor
- L63 _public function_ `TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> GetDataPtr()` — Get the pointer to the data.
- L71 _public function_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> GetMessageContext()` — Get the message context.
- L79 _public function_ `EQuicSerializedMessageState GetState() const` — Gets the state of the message data.
- L87 _public function_ `void UpdateState(EQuicSerializedMessageState InState)` — Updates the state of this message data.
- L95 _public function_ `EMessageFlags GetFlags() const` — Get the message flags.
- L103 _public function_ `EQuicMessageFormat GetFormat() const` — Get the format used to encode the message
- L111 _public function_ `TArray<FGuid> GetRecipients() const` — Get the message recipients.
- L119 _public function_ `EQuicMessageType GetMessageType() const` — Get the message type.
- L127 _private member_ `TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> DataPtr;` — Holds the serialized data.
- L130 _private member_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> MessageContext;` — Holds the message context.
- L133 _private member_ `EQuicSerializedMessageState State;` — Holds the message data state.
- L136 _private member_ `EMessageFlags Flags;` — Holds message flags, captured from context.
- L139 _private member_ `EQuicMessageFormat Format;` — The format used to serialize the message.
- L142 _private member_ `TArray<FGuid> Recipients;` — Holds the message recipients.
- L145 _private member_ `EQuicMessageType MessageType;` — Holds the message type.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Private/Transport/QuicMessageProcessor.h` (Private)


#### class `FQuicMessageProcessor`  
`class FQuicMessageProcessor : public FRunnable , private FSingleThreadRunnable`  
_L64-248_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Implements a message processor for QUIC messages.
- L74 _public prototype_ `FQuicMessageProcessor();` — Creates and initializes a new message processor.
- L77 _public prototype_ `virtual ~FQuicMessageProcessor();` — Virtual destructor.
- L86 _public prototype_ `void ProcessInboundMessage(const FInboundMessage InboundMessage);` — Prepares and enqueues an inbound message for deserialization. @param InboundMessage The inbound message
- L97 _public prototype_ `bool ProcessOutboundMessage( const TSharedRef<IMessageContext, ESPMode::ThreadSafe> MessageContext, const TArray<FGuid>& Recipients, const EQuicMessageType MessageType);` — Prepares and enqueues an outbound message for serialization. @param MessageContext The message to serialize @param Recipients The recipient nodes ids @param MessageType The message type @return Whether the message could be enqueued
- L106 _private prototype_ `void ConsumeMessages();` — Consume messages and create task to serialize and deserialize messages.
- L113 _public prototype_ `void UpdateSerialization();` — Updates message serialization tasks.
- L121 _public prototype_ `FQuicPayloadPtr SerializeMessageHeader(FMessageHeader& InMessageHeader) const;` — Serializes a message header. @param InMessageHeader The message header to serialize @return The serialized message header
- L129 _public prototype_ `FMessageHeader DeserializeMessageHeader(FQuicPayloadPtr InHeaderData) const;` — Deserializes a message header. @param InHeaderData The message header data to deserialize @return The deserialized message header
- L138 _public prototype_ `void WaitAsyncTaskCompletion();` — Waits for all serialization tasks fired by this processor to complete. Expected to be called when the application exit to prevent serialized (UStruct) object to being use after the UObject system is shutdown.
- L147 _public function_ `DECLARE_DELEGATE_TwoParams(FOnMessageDeserialized, FQuicDeserializedMessagePtr , FGuid ) FOnMessageDeserialized& OnMessageDeserialized()` — Returns a delegate that is executed when a message has been deserialized. @return The delegate.
- L158 _public function_ `DECLARE_DELEGATE_OneParam(FOnMessageSerialized, FQuicSerializedMessagePtr ) FOnMessageSerialized& OnMessageSerialized()` — Returns a delegate that is executed when a message has been serialized. @return The delegate.
- L168 _public prototype_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L169 _public function_ `virtual bool Init() override`
- L170 _public prototype_ `virtual uint32 Run() override;`
- L171 _public prototype_ `virtual void Stop() override;`
- L172 _public function_ `virtual void Exit() override`
- L178 _protected function_ `virtual void Tick() override`
- L183 _private member_ `bool bStopping;` — Holds a flag indicating that the thread is stopping.
- L186 _private member_ `bool bIsInitialized;` — Holds a flag indicating if the processor is initialized.
- L189 _private member_ `EQuicMessageFormat MessageFormat;` — The configured message format (from UQuicMessagingSettings).
- L192 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L195 _private member_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> SerializeWorkEvent;` — Holds an event signaling that outbound messages need to be processed.
- L198 _private member_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> DeserializeWorkEvent;` — Holds an event signaling that inbound messages need to be processed.
- L203 _private member_ `bool bUpdatingSerialization;` — Holds a flag indicating if the processor is updating serialization.
- L206 _private member_ `const FTimespan SerializationInterval = 10000;` — Holds the interval for message de/serialization.
- L209 _private member_ `double LastSerialization = FPlatformTime::Seconds();` — Holds timestamp of last de/serialization.
- L212 _private member_ `uint32 SerializeTaskId = 0;` — Holds the current serialize task id.
- L215 _private member_ `uint32 DeserializeTaskId = 0;` — Holds the current deserialize task id.
- L218 _private member_ `TMap<uint32, FQuicSerializedMessagePtr> PendingSerializeMessages;` — Holds pending serialized messages.
- L221 _private member_ `TMap<uint32, FQuicDeserializedMessagePtr> PendingDeserializeMessages;` — Holds pending deserialized messages.
- L226 _private member_ `bool bConsumingMessages = false;` — Flag indicating if messages are currently being consumed.
- L229 _private member_ `const FTimespan ConsumeInterval = 10000;` — Holds the interval for message consume.
- L232 _private member_ `double LastConsumed = FPlatformTime::Seconds();` — Holds the timestamp of when messages have last been consumed.
- L235 _private member_ `TQueue<FQuicSerializedMessagePtr> SerializeMessagesQueue;` — Queue that holds serialized messages.
- L238 _private member_ `TQueue<FQuicDeserializedMessagePtr> DeserializeMessagesQueue;` — Queue that holds deserialized messages.
- L243 _private member_ `FOnMessageDeserialized MessageDeserializedDelegate;` — Holds a delegate to be invoked when a message has been deserialized.
- L246 _private member_ `FOnMessageSerialized MessageSerializedDelegate;` — Holds a delegate to be invoked when a message has been serialized.

#### Free symbols / members of external scopes

- L42 _typedef_ `using FQuicDeserializedMessagePtr = TSharedPtr<FQuicDeserializedMessage, ESPMode::ThreadSafe>;` — @note: The delegate macro recognizes the ThreadSafe TSharedPtr as two arguments.
- L43 _typedef_ `using FQuicSerializedMessagePtr = TSharedPtr<FQuicSerializedMessage, ESPMode::ThreadSafe>;`
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace Private` (scope `UE`)
- L46 _namespace_ `namespace MessageProcessor` (scope `UE::Private`)
- L52 _prototype_ `FOnOutboundTransferDataUpdated& OnOutboundUpdated();` (scope `UE::Private::MessageProcessor`) — Global delegate for handling outbound processor updates.
- L57 _prototype_ `FOnInboundTransferDataUpdated& OnInboundUpdated();` (scope `UE::Private::MessageProcessor`) — Global delegate for handling inbound processor updates.
- L147 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMessageDeserialized, FQuicDeserializedMessagePtr , FGuid ) FOnMessageDeserialized& OnMessageDeserialized() { return MessageDeserializedDelegate; } DECLARE_DELEGATE_OneParam(FOnMessageSerialized, FQuicSerializedMessagePtr ) FOnMessageSerialized& OnMessageSerialized() { return MessageSerializedDelegate; } public:` — Returns a delegate that is executed when a message has been deserialized. @return The delegate.
- L158 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessageSerialized, FQuicSerializedMessagePtr ) FOnMessageSerialized& OnMessageSerialized() { return MessageSerializedDelegate; } public:` — Returns a delegate that is executed when a message has been serialized. @return The delegate.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Private/Transport/QuicMessageTransport.h` (Private)


#### class `FQuicMessageTransport`  
`class FQuicMessageTransport : public TSharedFromThis<FQuicMessageTransport, ESPMode::ThreadSafe> , public IMessageTransport`  
_L42-316_
- inherits: `TSharedFromThis<FQuicMessageTransport,ESPMode::ThreadSafe>,IMessageTransport`
- desc: Implements a message transport technology using mvfst with QUIC.
- L49 _public prototype_ `FQuicMessageTransport() = delete;` — Default constructor.
- L58 _public prototype_ `FQuicMessageTransport(const bool bInIsClient, const TSharedRef<FQuicEndpointConfig> InEndpointConfig, TArray<FIPv4Endpoint> InStaticEndpoints);` — Creates and initializes a new transport instance. @param bInIsClient Whether the transport is in client mode @param InEndpointConfig The endpoint config @param InStaticEndpoints The static endpoints
- L63 _public prototype_ `virtual ~FQuicMessageTransport();` — Virtual destructor.
- L66 _public prototype_ `void OnAppPreExit();` — Notifies the transport that the application is about to exit.
- L75 _public prototype_ `void AddStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Add a static server endpoint to the transport. @param InEndpoint The static endpoint to add
- L82 _public prototype_ `void RemoveStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Remove a static server endpoint from the transport. @param InEndpoint The static endpoint to remove
- L87 _public prototype_ `TArray<FIPv4Endpoint> GetListeningAddresses() const;` — Get the IPv4Endpoint listening addresses.
- L93 _public prototype_ `TArray<FIPv4Endpoint> GetKnownEndpoints() const;` — Get the known endpoints that are in active communication with the QUIC transport. This is information known by the EndpointManager.
- L100 _public prototype_ `FMessageTransportStatistics GetLatestStatistics(FGuid NodeId) const;` — Get the latest network/transport statistics for a node. @param NodeId The node ID
- L109 _public prototype_ `void SetMaxAuthenticationMessageSize(const uint32 MaxBytes) const;` — Set the maximum authentication message size. @param MaxBytes The maximum message size in bytes
- L118 _public prototype_ `TOptional<FGuid> GetNodeId(const FIPv4Endpoint& RemoteEndpoint) const;` — Get the NodeId of the remote endpoint. @param RemoteEndpoint The remote endpoint address @return Optional FGuid if the node was found
- L125 _public prototype_ `bool IsNodeAuthenticated(const FGuid& NodeId) const;` — Check if a node is authenticated. @param NodeId The node identifier
- L132 _public prototype_ `void SetNodeAuthenticated(const FGuid& NodeId);` — Mark a node as authenticated. @param NodeId The node identifier
- L139 _public prototype_ `void DisconnectNode(const FGuid& NodeId) const;` — Disconnect a node. @param NodeId The node identifier
- L150 _public prototype_ `void SetConnectionCooldown( const bool bEnabled, const uint32 MaxAttempts, const uint32 PeriodSeconds, const uint32 CooldownSeconds, const uint32 CooldownMaxSeconds) const;` — Set the connection cooldown. @param bEnabled Whether the cooldown should be enabled @param MaxAttempts Maximum number of attempts @param PeriodSeconds Time period for maximum number of attempts in seconds @param CooldownSeconds Duration of the cooldown in seconds @param CooldownMaxSeconds Max duration of the cooldown in seconds
- L162 _public function_ `DECLARE_DELEGATE(FOnError) FOnError& OnTransportError()` — Returns a delegate that is exectued when a connection error happened. @return The delegate @note this delegate is executed from the main thread by the task graph
- L172 _public prototype_ `bool RestartTransport();` — Restart the transport using the same Transport handler @return true if the restart was successful
- L176 _public prototype_ `virtual FName GetDebugName() const override;`
- L178 _public prototype_ `virtual bool StartTransport(IMessageTransportHandler& Handler) override;`
- L180 _public prototype_ `virtual void StopTransport() override;`
- L182 _public prototype_ `virtual bool TransportMessage( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TArray<FGuid>& Recipients) override;`
- L194 _public prototype_ `bool TransportAuthMessage( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FGuid& Recipient);` — Transport an authentication message. @param Context The message context @param Recipient The message recipient
- L204 _public prototype_ `bool TransportAuthResponseMessage( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FGuid& Recipient);` — Transport an authentication response message. @param Context The message context @param Recipient The message recipient
- L214 _public prototype_ `FOnQuicMetaMessageReceived& OnMetaMessageReceived();` — Delegate that notifies bound functions when a meta / authentication message has been received. @return The delegate
- L220 _public prototype_ `FOnQuicClientConnectionChanged& OnClientConnectionChanged();` — Delegate that notifies bound functions when a client has connected to or disconnected from a remote endpoint (QuicServer).
- L227 _private prototype_ `void HandleProcessorMessageDeserialized( const TSharedPtr<FQuicDeserializedMessage, ESPMode::ThreadSafe> DeserializedMessage, const FGuid NodeId) const;` — Handles deserialized transport messages.
- L234 _private prototype_ `void HandleProcessorMessageSerialized( TSharedPtr<FQuicSerializedMessage, ESPMode::ThreadSafe> SerializedMessage);` — Handles serialized transport messages.
- L242 _private prototype_ `void HandleManagerMessageDelivered(const uint32 MessageId);` — Handles delivered messages.
- L247 _private prototype_ `void HandleManagerMessageReceived(const FInboundMessage InboundMessage);` — Handles received transport messages.
- L252 _private prototype_ `FQuicPayloadPtr HandleManagerSerializeHeader(FMessageHeader& MessageHeader);` — Handles message headers that need to be serialized.
- L257 _private prototype_ `FMessageHeader HandleManagerDeserializeHeader(FQuicPayloadPtr HeaderData);` — Handles message headers that need to be deserialized.
- L262 _private prototype_ `void HandleManagerNodeDiscovered(const FGuid& DiscoveredNodeId);` — Handles discovered transport endpoints.
- L267 _private prototype_ `void HandleManagerNodeLost(const FGuid& LostNodeId);` — Handles lost transport endpoints.
- L272 _private prototype_ `void HandleClientConnectionChange( const FGuid& NodeId, const FIPv4Endpoint& RemoteEndpoint, const EQuicClientConnectionChange ConnectionState);` — Handles client connection changes.
- L279 _private member_ `TFuture<void> ErrorFuture;` — Holds any pending restart requests.
- L282 _private member_ `FOnError TransportErrorDelegate;` — Holds the transport error delegate.
- L285 _private member_ `TUniquePtr<FQuicMessageProcessor> MessageProcessor = nullptr;` — Holds the message processor.
- L288 _private member_ `IMessageTransportHandler* TransportHandler = nullptr;` — Message transport handler.
- L291 _private member_ `TUniquePtr<FQuicEndpointManager> EndpointManager = nullptr;` — Holds the endpoint manager.
- L294 _private member_ `EEndpointMode EndpointMode = EEndpointMode::Client;` — Flag indicating the endpoint mode.
- L297 _private member_ `TSharedRef<FQuicEndpointConfig> EndpointConfig;` — Holds the QuicEndpoint config.
- L300 _private member_ `TSet<FIPv4Endpoint> StaticEndpoints;` — Holds the static endpoints.
- L305 _private member_ `uint32 SerializedMessageId = 0;` — Current id for serialized messages.
- L308 _private member_ `TMap<uint32, TSharedPtr<FQuicSerializedMessage, ESPMode::ThreadSafe>> SerializedMessages;` — Holds serialized messages.
- L311 _private member_ `FOnQuicMetaMessageReceived OnQuicMetaMessageDelegate;` — Holds the meta message received delegate.
- L314 _private member_ `FOnQuicClientConnectionChanged OnQuicClientConnectionChangedDelegate;` — Holds the client connection changed delegate.

#### Free symbols / members of external scopes

- L162 _delegate_ `DECLARE_DELEGATE(FOnError) FOnError& OnTransportError() { return TransportErrorDelegate; } bool RestartTransport();` — Returns a delegate that is exectued when a connection error happened. @return The delegate @note this delegate is executed from the main thread by the task graph

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Public/IQuicNetworkMessagingExtension.h` (Public)


#### class `IQuicNetworkMessagingExtension`  
`class IQuicNetworkMessagingExtension : public INetworkMessagingExtension`  
_L17-120_
- inherits: `INetworkMessagingExtension`
- desc: Interface for the messaging module network extension Plugins or modules implementing messaging transport for MessageBus can implement this modular feature to provide control on the service it provides.
- L27 _public prototype_ `virtual FGuid GetEndpointGuid() = 0;` — Get the generated Guid for this instance. @return The Guid
- L34 _public prototype_ `virtual void SetMaxAuthenticationMessageSize(const uint32 MaxBytes) = 0;` — Set the maximum size an authentication message can have. @param MaxBytes The maximum message size in bytes
- L43 _public prototype_ `virtual TOptional<FGuid> GetNodeId(const FString& RemoteEndpoint) = 0;` — Get the NodeId of the remote endpoint. @param RemoteEndpoint The remote endpoint address:port @return Optional FGuid if the node was found
- L51 _public prototype_ `virtual bool IsNodeAuthenticated(const FGuid& NodeId) const = 0;` — Check if this node is authenticated. @param NodeId The node identifier @return Whether the node is authenticated
- L58 _public prototype_ `virtual void SetNodeAuthenticated(const FGuid& NodeId) = 0;` — Set this node as authenticated. @param NodeId The node identifier
- L65 _public prototype_ `virtual void DisconnectNode(const FGuid& NodeId) = 0;` — Disconnect a node. @param NodeId The node identifier
- L76 _public prototype_ `virtual void SetConnectionCooldown( const bool bEnabled, const uint32 MaxAttempts, const uint32 PeriodSeconds, const uint32 CooldownSeconds, const uint32 CooldownMaxSeconds) = 0;` — Set the connection cooldown. @param bEnabled Whether the cooldown should be enabled @param MaxAttempts Maximum number of attempts @param PeriodSeconds Time period for maximum number of attempts in seconds @param CooldownSeconds Duration of the cooldown in seconds @param CooldownMaxSeconds Max duration of the cooldown in seconds
- L88 _public prototype_ `virtual bool TransportAuthMessage( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FGuid& Recipient) = 0;` — Transport authentication message to endpoint. @param Context The message context @param Recipient Guid of message recipient @return Whether the message was sent
- L100 _public prototype_ `virtual bool TransportAuthResponseMessage( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FGuid& Recipient) = 0;` — Transport authentication response message to endpoint. @param Context The message context @param Recipient Guid of message recipient @return Whether the message was sent
- L110 _public prototype_ `virtual FOnQuicMetaMessageReceived& OnQuicMetaMessageReceived() = 0;` — Delegate that notifies bound functions when a meta / authentication message has been received. @return The delegate
- L118 _public prototype_ `virtual FOnQuicClientConnectionChanged& OnQuicClientConnectionChanged() = 0;` — Delegate that notifies bound functions when a QuicClient has connected to or disconnected from a remote endpoint (QuicServer). @return The delegate

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Public/QuicTransportMessages.h` (Public)


#### struct `FQuicMetaMessage`  
`struct FQuicMetaMessage`  
_L16-24_
- reflection: `USTRUCT()`
- L22 _public member_ `FGuid SenderNodeId;` — `UPROPERTY(VisibleAnywhere, Category = "QuicTransportMessage")`

#### struct `FQuicAuthMessage`  
`struct FQuicAuthMessage : public FQuicMetaMessage`  
_L28-36_
- reflection: `USTRUCT()`
- inherits: `FQuicMetaMessage`
- L34 _public member_ `FString Payload;` — `UPROPERTY(VisibleAnywhere, Category = "QuicTransportMessage")`

#### struct `FQuicAuthResponseMessage`  
`struct FQuicAuthResponseMessage : public FQuicMetaMessage`  
_L40-51_
- reflection: `USTRUCT()`
- inherits: `FQuicMetaMessage`
- L46 _public member_ `bool bAuthSuccessful;` — `UPROPERTY(VisibleAnywhere, Category = "QuicTransportMessage")`
- L49 _public member_ `FString Reason;` — `UPROPERTY(VisibleAnywhere, Category = "QuicTransportMessage")`

#### class `FQuicMetaMessageContext`  
`class FQuicMetaMessageContext : public IMessageContext`  
_L54-115_
- inherits: `IMessageContext`
- L61 _public function_ `template <typename MessageType> explicit FQuicMetaMessageContext(MessageType* InMessage) : Message(InMessage) , TypeInfo(InMessage->StaticStruct())`
- L66 _public function_ `~FQuicMetaMessageContext()`
- L85 _public function_ `virtual const TMap<FName, FString>& GetAnnotations() const override`
- L86 _public function_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override`
- L87 _public function_ `virtual const FDateTime& GetExpiration() const override`
- L88 _public function_ `virtual const void* GetMessage() const override`
- L89 _public function_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override`
- L90 _public function_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override`
- L91 _public function_ `virtual const TArray<FMessageAddress>& GetRecipients() const override`
- L92 _public function_ `virtual EMessageScope GetScope() const override`
- L93 _public function_ `virtual EMessageFlags GetFlags() const override`
- L94 _public function_ `virtual const FMessageAddress& GetSender() const override`
- L95 _public function_ `virtual const FMessageAddress& GetForwarder() const override`
- L96 _public function_ `virtual ENamedThreads::Type GetSenderThread() const override`
- L97 _public function_ `virtual const FDateTime& GetTimeForwarded() const override`
- L98 _public function_ `virtual const FDateTime& GetTimeSent() const override`
- L102 _private member_ `TMap<FName, FString> Annotations = TMap<FName, FString>();`
- L103 _private member_ `TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> Attachment = nullptr;`
- L104 _private member_ `FDateTime Expiration = FDateTime::MaxValue();`
- L105 _private member_ `void* Message;`
- L106 _private member_ `TSharedPtr<IMessageContext, ESPMode::ThreadSafe> OriginalContext = nullptr;`
- L107 _private member_ `TArray<FMessageAddress> Recipients = TArray<FMessageAddress>();`
- L108 _private member_ `EMessageScope Scope = EMessageScope::Network;`
- L109 _private member_ `EMessageFlags Flags = EMessageFlags::Reliable;`
- L110 _private member_ `FMessageAddress Sender = FMessageAddress::NewAddress();`
- L111 _private member_ `ENamedThreads::Type SenderThread = ENamedThreads::AnyThread;`
- L112 _private member_ `FDateTime TimeSent = FDateTime::Now();`
- L113 _private member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnQuicMetaMessageReceived, const FGuid , const TSharedRef<IMessageContext>& );`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnQuicMetaMessageReceived, const FGuid , const TSharedRef<IMessageContext>& );`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Public/QuicTransportNotifications.h` (Public)


#### enum `EQuicClientConnectionState`  
`enum class EQuicClientConnectionState : uint8`  
_L15-22_
- desc: Enumerates QuicClient connection state to the remote endpoint.
- L18 _public enumerator_ `Connected` — Client connected to remote endpoint.
- L21 _public enumerator_ `Disconnected` — Client disconnected from remote endpoint.

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnQuicClientConnectionChanged, const FGuid& , const FIPv4Endpoint& , const EQuicClientConnectionState );` — Delegate informing bound functions when a QuicClient has connected to or disconnected from a remote endpoint (QuicServer).
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnQuicClientConnectionChanged, const FGuid& , const FIPv4Endpoint& , const EQuicClientConnectionState );` — Delegate informing bound functions when a QuicClient has connected to or disconnected from a remote endpoint (QuicServer).

### `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Public/Shared/QuicMessagingSettings.h` (Public)


#### enum `EQuicMessageFormat`  
`enum class EQuicMessageFormat : uint8`  
_L15-37_
- reflection: `UENUM()`
- desc: Defines the Quic message format available (how the message data is encoded).
- L18 _public enumerator_ `None = 0 UMETA(Hidden)` — No format specified. Legacy - Not exposed to user.
- L21 _public enumerator_ `Json UMETA(Hidden)` — JSON format specified. Legacy - Not exposed to user.
- L24 _public enumerator_ `TaggedProperty UMETA(Hidden)` — Tagged property format specified. Legacy - Not exposed to user.
- L30 _public enumerator_ `CborPlatformEndianness UMETA(DisplayName="CBOR (Platform Endianness)")` — Quic messages are encoded in CBOR, using the platform endianness. This is the fastest and preferred option, but the CBOR data will not be readable by an external standard-compliant CBOR parser if generated from a little endian platform. If the data needs to be consumed outside the Unreal Engine, consider using CborStandardEndianness format instead.
- L36 _public enumerator_ `CborStandardEndianness UMETA(DisplayName="CBOR (Standard Endianness)")` — Quic messages are encoded in CBOR, using the CBOR standard-complinant endianness (big endian). It will perform slower on a little-endian platform, but the data will be readable by standard CBOR parsers. Useful if the Quic messages needs to be analyzed/consumed outside the Unreal Engine.

#### class `UQuicMessagingSettings`  
`class UQuicMessagingSettings : public UObject`  
_L40-186_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L55 _public member_ `bool EnabledByDefault = false;` — `UPROPERTY(config, EditAnywhere, Category = Availability)` — Whether Quic messaging is enabled by default. If false -messaging will need to be added to the commandline when running non-editor builds. (Note - in Shipping builds ALLOW_QUIC_MESSAGING_SHIPPING=1 must also be defined in TargetRules for messaging to be available with or without this setting)
- L62 _public member_ `bool EnableTransport = true;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — Whether the Quic transport channel is enabled. Can be specified on the command line with `-QUICMESSAGING_TRANSPORT_ENABLE=`
- L66 _public member_ `bool bAutoRepair = true;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — Whether the Quic transport channel should try to auto repair when in error.
- L72 _public member_ `bool bIsClient = true;` — `UPROPERTY(config)` — Whether the QUIC transport endpoint is a client (true) or a server (false)
- L78 _public member_ `bool bEncryption = true;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Whether encryption should be used after the quic handshake
- L84 _public member_ `uint32 DiscoveryTimeoutSeconds = 10;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Timeout in seconds when the remote endpoint cannot be discovered.
- L90 _public member_ `bool bAuthEnabled = false;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Whether server side authentication is enabled
- L96 _public member_ `uint32 MaxAuthenticationMessageSize = 8000;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Maximum authentication message size for server side authentication
- L102 _public member_ `bool bConnectionCooldownEnabled = true;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Whether server has a cooldown for connection attempts.
- L108 _public member_ `uint32 ConnectionCooldownMaxAttempts = 5;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Maximum number of connection attempts until the cooldown is triggered.
- L114 _public member_ `uint32 ConnectionCooldownPeriodSeconds = 30;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Time period in seconds within which the maximum attempts must happen.
- L120 _public member_ `uint32 ConnectionCooldownSeconds = 60;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Connection cooldown in seconds used with exponential backoff.
- L126 _public member_ `uint32 ConnectionCooldownMaxSeconds = 3600;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Maximum connection cooldown in seconds for exponential backoff.
- L132 _public member_ `bool bClientVerificationEnabled = true;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Whether the QUIC client should verify the server certificate
- L138 _public member_ `FString QuicServerCertificate = "";` — `UPROPERTY(config)` — Server certificate to encrypt QUIC transport
- L144 _public member_ `FString QuicServerPrivateKey = "";` — `UPROPERTY(config)` — Server private key to encrypt QUIC transport
- L150 _public member_ `FGuid EndpointGuid;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Guid of this endpoint
- L154 _public member_ `uint32 AutoRepairAttemptLimit = 10;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — The number of consecutive attempt the auto repair routine will try to repair.
- L158 _public member_ `bool bStopServiceWhenAppDeactivates = true;` — `UPROPERTY(config)` — Whether to stop the transport service when the application deactivates, and restart it when the application is reactivated
- L171 _public member_ `FString UnicastEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The IP endpoint to listen to and send packets from. The format is IP_ADDRESS:PORT_NUMBER. 0.0.0.0:0 will bind to the default network adapter on Windows, and all available network adapters on other operating systems. Specifying an interface IP here, will use that interface for multicasting and static endpoint *might* also reach this client through <unicast ip:multicast port> Specifying both the IP and Port will allow usage of static endpoint to reach this client Can be specified on the command line with `-QUICMESSAGING_TRANSPORT_UNICAST=`
- L175 _public member_ `EQuicMessageFormat MessageFormat = EQuicMessageFormat::CborPlatformEndianness;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The format used to serialize the Quic message payload.
- L184 _public member_ `TArray<FString> StaticEndpoints;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — The IP endpoints of static devices. Use this setting to reach devices on other subnets, such as mobile phones on a WiFi network. The format is IP_ADDRESS:PORT_NUMBER.
