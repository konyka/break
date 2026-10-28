# Plugins / ConcertTransport

- module root: `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport`
- headers: 25; symbols: 592
- symbol kinds: class=29, delegate=3, enum=10, enumerator=34, function=129, macro=33, member=99, namespace=11, prototype=204, struct=20, typedef=20
- PublicDependencyModuleNames: Core, CoreUObject, MessagingCommon, TraceLog

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Private/ConcertLocalEndpoint.h` (Private)


#### class `FConcertLocalEndpoint`  
`class FConcertLocalEndpoint : public IConcertLocalEndpoint`  
_L24-196_
- inherits: `IConcertLocalEndpoint`
- desc: Implements a local endpoint for Concert
- L30 _public prototype_ `FConcertLocalEndpoint(const FString& InEndpointFriendlyName, const FConcertEndpointSettings& InEndpointSettings, const FConcertTransportLoggerFactory& InLogFactory);`
- L31 _public prototype_ `virtual ~FConcertLocalEndpoint();`
- L33 _public prototype_ `virtual const FConcertEndpointContext& GetEndpointContext() const override;`
- L34 _public prototype_ `virtual TArray<FConcertEndpointContext> GetRemoteEndpoints() const override;`
- L35 _public prototype_ `virtual FMessageAddress GetRemoteAddress(const FGuid& ConcertEndpointId) const override;`
- L37 _public prototype_ `virtual FOnConcertRemoteEndpointConnectionChanged& OnRemoteEndpointConnectionChanged() override;`
- L38 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() override;`
- L41 _protected prototype_ `virtual void InternalAddRequestHandler(const FTopLevelAssetPath& RequestMessageType, const TSharedRef<IConcertRequestHandler>& Handler) override;`
- L42 _protected prototype_ `virtual void InternalAddEventHandler(const FTopLevelAssetPath& EventMessageType, const TSharedRef<IConcertEventHandler>& Handler) override;`
- L44 _protected prototype_ `virtual void InternalRemoveRequestHandler(const FTopLevelAssetPath& RequestMessageType) override;`
- L45 _protected prototype_ `virtual void InternalRemoveEventHandler(const FTopLevelAssetPath& EventMessageType) override;`
- L47 _protected prototype_ `virtual void InternalSubscribeToEvent(const FTopLevelAssetPath& EventMessageType) override;`
- L48 _protected prototype_ `virtual void InternalUnsubscribeFromEvent(const FTopLevelAssetPath& EventMessageType) override;`
- L50 _protected prototype_ `virtual void InternalQueueRequest(const TSharedRef<IConcertRequest>& Request, const FGuid& Endpoint) override;`
- L51 _protected prototype_ `virtual void InternalQueueResponse(const TSharedRef<IConcertResponse>& Response, const FGuid& Endpoint) override;`
- L52 _protected prototype_ `virtual void InternalQueueEvent(const TSharedRef<IConcertEvent>& Event, const FGuid& Endpoint, EConcertMessageFlags Flags) override;`
- L53 _protected prototype_ `virtual void InternalPublishEvent(const TSharedRef<IConcertEvent>& Event) override;`
- L57 _private prototype_ `FConcertRemoteEndpointRef CreateRemoteEndpoint(const FConcertEndpointContext& InEndpointContext, const FDateTime& InLastReceivedMessageTime, const FMessageAddress& InRemoteAddress);` — Create a new remote endpoint and add it to the RemoteEndpoints map
- L60 _private prototype_ `FConcertRemoteEndpointPtr FindRemoteEndpoint(const FGuid& InEndpointId) const;` — Find the remote endpoint with the given ID
- L63 _private prototype_ `FConcertRemoteEndpointPtr FindRemoteEndpoint(const FMessageAddress& InEndpointId) const;` — Find the remote endpoint with the given Message Address
- L66 _private prototype_ `void RemoveRemoteEndpoint(const FMessageAddress& EndpointAddress);` — Remove the remote endpoint with the given Message Address.
- L69 _private prototype_ `bool HandleTick(float DeltaTime);` — Handle the endpoint ticker
- L72 _private prototype_ `void QueueAck(const FConcertMessageContext& ConcertContext);` — Queue an acknowledgment to a specific message
- L75 _private prototype_ `void SendAcks(const TArray<FConcertRemoteEndpointPtr>& InRemoteEndpoints, const FDateTime& UtcNow);` — Send any pending acknowledgments
- L78 _private prototype_ `void SendAck(const FGuid& AcknowledgmentToSend, const FConcertRemoteEndpointRef& RemoteEndpoint, const FDateTime& UtcNow);` — Send any pending acknowledgment to the remote endpoint
- L81 _private prototype_ `void SendEndpointClosed(const FConcertRemoteEndpointRef& RemoteEndpoint, const FDateTime& UtcNow);` — Send a notification to this endpoint that it has been closed on the remote peer (us!)
- L84 _private prototype_ `void PublishMessage(const TSharedRef<IConcertMessage>& Message);` — Publish a message
- L87 _private prototype_ `void SendMessage(const TSharedRef<IConcertMessage>& Message, const FConcertRemoteEndpointRef& RemoteEndpoint, const FDateTime& UtcNow, EConcertMessageFlags Flags = EConcertMessageFlags::None);` — Send a message to a specific remote endpoint
- L90 _private prototype_ `void InternalHandleMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handle an incoming message from the message bus
- L93 _private prototype_ `void InternalHandleBusNotification(const FMessageBusNotification& Notification);` — Handle disconnection notifications coming from MessageBus
- L96 _private prototype_ `void ProcessEndpointDiscovery(const FConcertMessageContext& ConcertContext, const FMessageAddress& InRemoteAddress);` — Process an endpoint discovery message to add a new known remote endpoint
- L99 _private prototype_ `void ProcessReliableHandshake(const FConcertMessageContext& ConcertContext);` — Process a reliable handshake message for a known remote endpoint
- L102 _private prototype_ `void HandleMessage(const FConcertMessageContext& ConcertContext);` — Handle a concert message
- L105 _private prototype_ `void ProcessEvent(const FConcertMessageContext& ConcertContext);` — Process a concert event using a registered event handler
- L108 _private prototype_ `void ProcessRequest(const FConcertMessageContext& ConcertContext);` — Process a concert request using a registered request handler
- L111 _private prototype_ `void ProcessResponse(const FConcertMessageContext& ConcertContext);` — Process a concert response from a remote endpoint
- L114 _private prototype_ `void ProcessAck(const FConcertMessageContext& ConcertContext);` — Process an acknowledgment to a reliable event sent from this endpoint
- L117 _private prototype_ `void QueueReceivedMessage(const FConcertMessageContext& ConcertContext);` — Queue a received message for processing by ProcessQueuedReceivedMessages
- L120 _private prototype_ `void SendPendingMessages(const FConcertRemoteEndpointRef& RemoteEndpoint, const FDateTime& UtcNow);` — Resend pending reliable messages
- L123 _private prototype_ `void SendKeepAlive(const FConcertRemoteEndpointRef& RemoteEndpoint, const FDateTime& UtcNow);` — Send a keep alive message the a remote endpoint
- L126 _private prototype_ `void SendKeepAlives(const FDateTime& UtcNow);` — Send keep alive messages to remote endpoint we haven't sent to in a while.
- L129 _private prototype_ `void TimeoutRemoteEndpoints(const FDateTime& UtcNow);` — Timeout remote endpoint from which we haven't received a message or keep alive in a while
- L132 _private prototype_ `void ProcessQueuedReceivedMessages(const FDateTime& UtcNow);` — Process messages that have been received out of order
- L135 _private prototype_ `void PurgeOldReceivedMessages(const TArray<FConcertRemoteEndpointPtr>& InRemoteEndpoints, const FDateTime& UtcNow);` — Purge old already received messages after a certain period of time
- L138 _private prototype_ `void ResendPendingMessages(const TArray<FConcertRemoteEndpointPtr>& InRemoteEndpoints, const FDateTime& UtcNow);` — Resend pending messages to remote endpoints if need be.
- L141 _private prototype_ `void HandleInboundMessages(const FDateTime& UtcNow);` — Handles the inbound message from MessageBus. Operates on the game thread.
- L144 _private prototype_ `void ProcessKeepAliveMessage(const TSharedPtr<IMessageContext, ESPMode::ThreadSafe>& Context, const FDateTime& UtcNow);` — Updates the last receive time for a KeepAlive message.
- L147 _private prototype_ `void ForcePendingResend();` — Force pending resend on endpoints
- L150 _private member_ `FConcertEndpointContext EndpointContext;` — This context of this endpoint
- L153 _private member_ `uint16 NextReliableChannelId;` — Next reliable channel ID to use when creating a remote endpoint
- L156 _private member_ `mutable FCriticalSection RemoteEndpointsCS;` — Map of remote Endpoints we are sending messages to from this endpoint
- L157 _private member_ `TMap<FGuid, FConcertRemoteEndpointPtr> RemoteEndpoints;`
- L160 _private member_ `mutable FCriticalSection RemoteAddressesCS;` — Array of remote endpoint message addresses that were discovered.
- L161 _private member_ `TArray<FMessageAddress> RemoteAddresses;`
- L164 _private member_ `TQueue<TSharedPtr<IMessageContext, ESPMode::ThreadSafe>, EQueueMode::Spsc> InboundMessages;` — Incoming message bus messages
- L167 _private member_ `TArray<TTuple<FConcertEndpointContext, EConcertRemoteEndpointConnection>> PendingRemoteEndpointConnectionChangedEvents;` — Callback when a remote endpoint connection status changes.
- L168 _private member_ `FOnConcertRemoteEndpointConnectionChanged OnRemoteEndpointConnectionChangedDelegate;`
- L171 _private member_ `FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint OnConcertMessageAcknowledgementReceivedDelegate;` — Callback when a message has been acknowledged by a remote endpoint
- L174 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<IConcertEventHandler>> EventHandlers;` — Registered message handlers that do not generate a response
- L177 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<IConcertRequestHandler>> RequestHandlers;` — Registered message handlers that returns a response
- L180 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to the registered ticker for request and reliable message
- L183 _private member_ `TUniquePtr<FConcertLocalEndpointKeepAliveRunnable> KeepAliveRunnable;` — Runnable thread used to send keep-alive messages even when the game thread is blocked
- L186 _private member_ `bool bIsHandlingMessage;` — True if we are currently handling a message (used to prevent re-entrant behavior if something pumps the task pool while we're handling a message)
- L189 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint we are sending from
- L192 _private member_ `FConcertEndpointSettings Settings;` — Holds the endpoint settings
- L195 _private member_ `FConcertTransportLoggerWrapper Logger;` — Holds the Transport Logger, if any.

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TSharedPtr<FConcertRemoteEndpoint, ESPMode::ThreadSafe> FConcertRemoteEndpointPtr;`
- L19 _typedef_ `typedef TSharedRef<FConcertRemoteEndpoint, ESPMode::ThreadSafe> FConcertRemoteEndpointRef;`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Private/ConcertRemoteEndpoint.h` (Private)


#### class `FConcertRemoteEndpoint`  
`class FConcertRemoteEndpoint : public IConcertRemoteEndpoint`  
_L15-189_
- inherits: `IConcertRemoteEndpoint`
- L18 _public prototype_ `FConcertRemoteEndpoint(const FConcertEndpointContext& InEndpointContext, const uint16 InReliableChannelId, const FDateTime& InLastReceivedMessageTime, const FTimespan& InEndpointTimeoutSpan, const FMessageAddress& InAddress, const IConcertTransportLoggerPtr& InLogger);`
- L20 _public prototype_ `virtual ~FConcertRemoteEndpoint();`
- L22 _public prototype_ `virtual const FConcertEndpointContext& GetEndpointContext() const override;`
- L24 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceived& OnConcertMessageAcknowledgementReceived() override;`
- L27 _public prototype_ `bool HasReliableChannel() const;` — Does this remote endpoint have a reliable channel?
- L30 _public prototype_ `bool IsRegistered() const;` — Is the remote endpoint registered in the underlying bus.
- L33 _public prototype_ `bool IsPendingResend() const;` — Does this remote endpoint needs to resend any of its pending messages.
- L36 _public prototype_ `void ClearPendingResend();` — Clear the pending resend flag.
- L41 _public prototype_ `void QueueMessageToSend(const TSharedRef<IConcertMessage>& Message);` — Queue a message to send to this endpoint reliably
- L46 _public prototype_ `void QueueMessageToReceive(const FConcertMessageContext& Context);` — Queue a message to receive from this endpoint
- L49 _public prototype_ `bool HandleReliableHandshake(const FConcertReliableHandshakeData& InHandshakeRequest, FConcertReliableHandshakeData& OutHandshakeResponse);` — Handle a reliable handshake message for a known remote endpoint
- L52 _public prototype_ `void FillReliableHandshakeResponse(const EConcertReliableHandshakeState InResponseState, FConcertReliableHandshakeData& OutHandshakeResponse) const;` — Fill a reliable handshake response message based on the current state of this endpoint
- L57 _public prototype_ `void QueueAcknowledgmentToSend(const FGuid& MessageId);` — Queue an acknowledgment to send for the given message id
- L62 _public prototype_ `TOptional<FGuid> GetNextAcknowledgmentToSend();` — Get the pending acknowledgment to send on this endpoint, and reset the pending request
- L67 _public prototype_ `void HandleAcknowledgement(const FConcertMessageContext& Context);` — Handle an acknowledgment received from this remote endpoint
- L72 _public prototype_ `void HandleResponse(const FConcertMessageContext& Context);` — Handle a response to a request made to this remote endpoint
- L75 _public prototype_ `void ForwardBusNotification(EMessageBusNotification Notification);` — Pass MessageBus notification to the endpoint
- L78 _public prototype_ `void PurgeOldReceivedMessages(const FDateTime& UtcNow, const FTimespan& PurgeProcessedMessageSpan);` — Purge old already received messages after a certain period of time
- L81 _public function_ `FTimespan GetEndpointTimeoutSpan() const` — Get the Timespan before the remote end point consider us timed out
- L83 _public function_ `void UpdateLastMessageReceivedTime(const FDateTime& Now)`
- L89 _public function_ `FDateTime GetLastReceivedMessageTime() const` — Get the time of last message received from this endpoint.
- L92 _public function_ `FDateTime GetLastSentMessageTime() const` — Get the time of last message sent to this endpoint.
- L95 _public function_ `void SetLastSentMessageTime(const FDateTime& SendTime)` — Set the time of last message sent to this endpoint
- L98 _public function_ `const FMessageAddress& GetAddress() const` — Get the remote endpoint MessageBus address.
- L101 _public function_ `const TArray<TSharedPtr<IConcertMessage>>& GetPendingMessages() const` — Get the list of yet to be acknowledged messages sent to this endpoint.
- L104 _public prototype_ `TSharedPtr<FConcertMessageCapturedContext> GetNextMessageToReceive(const FDateTime& UtcNow);` — Get the next message to handle from the queued list, if any.
- L107 _public function_ `void MarkForResend()` — Forces the resend pending messages flag to be set for this endpoint. This if for debugging use only.
- L114 _private prototype_ `void TimeoutAllMessages();`
- L127 _private function_ `friend inline uint32 GetTypeHash(const FChannelIdAndOrderIndex& Key)`
- L134 _private member_ `TArray<TSharedPtr<IConcertMessage>> PendingMessages;` — Array of messages that we haven't received a response or acknowledgment for yet in the order they were sent
- L137 _private member_ `TMap<FGuid, FDateTime> RecentlyReceivedMessages;` — Map of messages we recently received (message id -> time received)
- L140 _private member_ `TMap<FChannelIdAndOrderIndex, TSharedPtr<FConcertMessageCapturedContext>> QueuedOutOfOrderMessagesToReceive;` — Map of reliable messages that are pending receipt because they arrived out-of-order ((channel id + message order index) -> data)
- L143 _private member_ `TArray<TSharedPtr<FConcertMessageCapturedContext>> QueuedMessagesToReceive;` — Array of messages that are pending receipt
- L146 _private member_ `FConcertEndpointContext EndpointContext;` — This context of this endpoint
- L149 _private member_ `FOnConcertMessageAcknowledgementReceived OnConcertMessageAcknowledgementReceivedDelegate;` — Callback when a message has been acknowledged by this remote endpoint
- L152 _private member_ `uint16 ReliableChannelIdToSend;` — The reliable channel ID to send with reliable messages
- L155 _private member_ `uint16 ReliableChannelIdToReceive;` — The reliable channel ID to receive with reliable messages (default is unreliable, correct value is set during reliable negotiation)
- L158 _private member_ `FDateTime LastAckTime;` — Time of the last acknowledgment we processed
- L161 _private member_ `TAtomic<FTimespan> EndpointTimeoutSpan;` — Time before the Endpoint consider us timed out
- L164 _private member_ `TAtomic<FDateTime> LastReceivedMessageTime;` — Time we last received a message or keep alive from this endpoint
- L167 _private member_ `TAtomic<FDateTime> LastSentMessageTime;` — Time we last sent a message or keep alive to this endpoint
- L170 _private member_ `TAtomic<uint16> NextMessageIndexToSend;` — The next message index to use when sending to this endpoint
- L173 _private member_ `uint16 NextMessageIndexToReceive;` — The next message index we should process when receiving from this endpoint
- L176 _private member_ `TOptional<FGuid> NextAcknowledgmentToSend;` — Next message ID to acknowledge on this endpoint (if any)
- L179 _private member_ `bool bNeedResendPendingMessages;` — Flag indicating if pending messages need to be resent.
- L182 _private member_ `bool bIsRegistered;` — Flag indicating if the endpoint is still registered on the underlying bus.
- L185 _private member_ `FMessageAddress Address;` — Remote Endpoint Address
- L188 _private member_ `FConcertTransportLoggerWrapper Logger;` — Holds the Transport Logger, if any

#### struct `FConcertRemoteEndpoint::FChannelIdAndOrderIndex`  
`struct FChannelIdAndOrderIndex`  
_L116-131_
- L118 _public member_ `uint16 ChannelId;`
- L119 _public member_ `uint16 OrderIndex;`
- L121 _public function_ `bool operator==(const FChannelIdAndOrderIndex& Other) const`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Private/Trace/Private/InitEventTracking.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertTrace` (scope `UE`)
- L12 _prototype_ `bool HasSentInitEventToCurrentSession();` (scope `UE::ConcertTrace`) — Checks whether an init event has been sent for the current trace session already.
- L15 _prototype_ `bool ShouldTraceConcertProtocols();` (scope `UE::ConcertTrace`) — @return Whether protocol tracing should generate data.
- L18 _prototype_ `void OnSendInitEvent();` (scope `UE::ConcertTrace`) — Tracks that for the current tracing session, and init event was been sent.

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/ConcertLogGlobal.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_LOG_CONCERT_DEBUG_VERBOSITY_LEVEL Error`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogConcert, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogConcertDebug, UE_LOG_CONCERT_DEBUG_VERBOSITY_LEVEL, All);`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/ConcertMessageContext.h` (Public)


#### struct `FConcertMessageContext`  
`struct FConcertMessageContext`  
_L8-42_
- desc: Context struct for Concert messages
- L11 _public function_ `FConcertMessageContext() : SenderConcertEndpointId() , UtcNow(0) , Message(nullptr) , MessageType(nullptr)` — Construct an empty context
- L20 _public function_ `FConcertMessageContext(const FGuid& InSenderConcertEndpointId, const FDateTime& InUtcNow, const FConcertMessageData* InMessage, const UScriptStruct* InMessageType, const TMap<FName, FString>& InAnnotations) : SenderConcertEndpointId(InSenderConcertEndpointId) , UtcNow(InUtcNow) , Message(InMessage) , MessageType(InMessageType) , Annotations(InAnnotations)` — Construct a context with a reference to the given message data
- L31 _public function_ `template <typename T> const T* GetMessage() const` — Utility to get the message data cast to the correct type
- L37 _public member_ `FGuid SenderConcertEndpointId;`
- L38 _public member_ `FDateTime UtcNow;`
- L39 _public member_ `const FConcertMessageData* Message;`
- L40 _public member_ `const UScriptStruct* MessageType;`
- L41 _public member_ `TMap<FName, FString> Annotations;`

#### struct `FConcertMessageCapturedContext`  
`struct FConcertMessageCapturedContext`  
_L44-61_
- L47 _public prototype_ `explicit FConcertMessageCapturedContext(const FConcertMessageContext& InContext);`
- L48 _public prototype_ `~FConcertMessageCapturedContext();`
- L50 _public prototype_ `FConcertMessageCapturedContext(const FConcertMessageCapturedContext& Other) = delete;`
- L51 _public prototype_ `const FConcertMessageCapturedContext& operator=(const FConcertMessageCapturedContext& Other) = delete;`
- L53 _public prototype_ `FConcertMessageCapturedContext(FConcertMessageCapturedContext&& Other);`
- L54 _public prototype_ `const FConcertMessageCapturedContext& operator=(FConcertMessageCapturedContext&& Other);`
- L56 _public member_ `FConcertMessageContext CapturedContext;`
- L59 _private prototype_ `void MallocCapturedContextMessage(const FConcertMessageData* InMessage, const UScriptStruct* InMessageType);`
- L60 _private prototype_ `void FreeCapturedContextMessage();`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/ConcertTransportMessages.h` (Public)


#### enum `EConcertMessageFlags`  
`enum class EConcertMessageFlags : uint8`  
_L13-21_
- reflection: `UENUM()`
- desc: Message Flags when sent
- L16 _public enumerator_ `None = 0` — No special flags
- L18 _public enumerator_ `ReliableOrdered = 1<<0` — Guarantee that this message is received by the client(s) and processed in the order they were sent
- L20 _public enumerator_ `UniqueId = 1<<1` — Message sent with this flag should be uniquely identifiable across clients.

#### enum `EConcertResponseCode`  
`enum class EConcertResponseCode : uint8`  
_L26-40_
- reflection: `UENUM()`
- desc: Response codes to a sent request
- L29 _public enumerator_ `Pending` — The response code is still pending.
- L31 _public enumerator_ `Success` — The request data was valid. A response was generated.
- L33 _public enumerator_ `Failed` — The request data was valid, but the request failed. A response was generated.
- L35 _public enumerator_ `InvalidRequest` — The request data was invalid. No response was generated.
- L37 _public enumerator_ `UnknownRequest` — The request type was unknown on the target instance. No response was generated.
- L39 _public enumerator_ `TimedOut` — The request failed to reach the target instance. No response was generated.

#### enum `EConcertReliableHandshakeState`  
`enum class EConcertReliableHandshakeState : uint8`  
_L44-52_
- reflection: `UENUM()`
- desc: Handshake codes used during reliable channel negotiation
- L47 _public enumerator_ `None` — Handshake initialization state
- L49 _public enumerator_ `Negotiate` — Handshake is being negotiated
- L51 _public enumerator_ `Success` — Handshake was successfully negotiated

#### enum `EConcertMessageVersion`  
`enum class EConcertMessageVersion : uint32`  
_L56-63_
- reflection: `UENUM()`
- desc: Versioning for concert message protocol
- L58 _public enumerator_ `BeforeVersioning = 0`
- L59 _public enumerator_ `Initial`
- L61 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L62 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FConcertMessageData`  
`struct FConcertMessageData`  
_L67-112_
- reflection: `USTRUCT()`
- desc: Base class for all message data sent through concert
- L71 _public function_ `FConcertMessageData() : MessageOrderIndex(0) , ChannelId(UnreliableChannelId)`
- L77 _public prototype_ `virtual ~FConcertMessageData() = default;`
- L79 _public function_ `bool IsReliable() const`
- L84 _public function_ `EConcertMessageFlags GetMessageFlags() const`
- L89 _public function_ `virtual bool IsSafeToHandle() const`
- L96 _public member_ `FGuid ConcertEndpointId;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — ID of the Endpoint this was sent from
- L100 _public member_ `FGuid MessageId;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — ID of the message
- L104 _public member_ `uint16 MessageOrderIndex;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — Order index of the message (for ordering reliable messages, used when ChannelId != UnreliableChannelId)
- L108 _public member_ `uint16 ChannelId;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — ID of the channel this message was sent from
- L111 _public member_ `static const uint16 UnreliableChannelId = 0;` — Constant to represent a unreliable channel ID

#### struct `FConcertEventData`  
`struct FConcertEventData : public FConcertMessageData`  
_L116-119_
- reflection: `USTRUCT()`
- inherits: `FConcertMessageData`
- desc: Base struct for all concert event messages

#### struct `FConcertRequestData`  
`struct FConcertRequestData : public FConcertMessageData`  
_L123-126_
- reflection: `USTRUCT()`
- inherits: `FConcertMessageData`
- desc: Base struct for all concert request messages

#### struct `FConcertResponseData`  
`struct FConcertResponseData : public FConcertMessageData`  
_L130-162_
- reflection: `USTRUCT()`
- inherits: `FConcertMessageData`
- desc: Base struct for all concert request response messages
- L134 _public function_ `FConcertResponseData() : ResponseCode(EConcertResponseCode::Pending)`
- L139 _public function_ `FConcertResponseData(EConcertResponseCode InResponseCode) : ResponseCode(InResponseCode)`
- L146 _public function_ `template <typename ResponseType> static FORCEINLINE TFuture<ResponseType> AsFuture(ResponseType&& ResponseData)` — Utility to get resolved response data as a future
- L153 _public member_ `FGuid RequestMessageId;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — ID of the request message we're responding to
- L157 _public member_ `EConcertResponseCode ResponseCode;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — Response code for the response
- L161 _public member_ `FText Reason;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — If the code isn't successful, a reason for it

#### struct `FConcertEndpointDiscoveryEvent`  
`struct FConcertEndpointDiscoveryEvent : public FConcertEventData`  
_L166-173_
- reflection: `USTRUCT()`
- inherits: `FConcertEventData`
- desc: Special event message base struct that is also caught by the endpoint to discover remote endpoint before passing it to handlers
- L172 _public member_ `EConcertMessageVersion ConcertProtocolVersion = EConcertMessageVersion::BeforeVersioning;` — `UPROPERTY()` — Holds the concert messages protocol version, default initialize to `BeforeVersioning` to handle message sent from older protocol.

#### struct `FConcertEndpointClosedData`  
`struct FConcertEndpointClosedData : public FConcertMessageData`  
_L177-180_
- reflection: `USTRUCT()`
- inherits: `FConcertMessageData`
- desc: Message send when an endpoint is closed on a remote peer

#### struct `FConcertReliableHandshakeData`  
`struct FConcertReliableHandshakeData : public FConcertEndpointDiscoveryEvent`  
_L184-203_
- reflection: `USTRUCT()`
- inherits: `FConcertEndpointDiscoveryEvent`
- desc: Handshake used to negotiate a reliable channel between endpoints (also uses the ReliableChannelId from the base message)
- L190 _public member_ `EConcertReliableHandshakeState HandshakeState = EConcertReliableHandshakeState::None;` — `UPROPERTY()` — State of the handshake
- L194 _public member_ `uint16 ReliableChannelId = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — Channel ID we're going to send reliable messages of
- L198 _public member_ `uint16 NextMessageIndex = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — The next message index that the remote endpoint is going to send
- L202 _public member_ `int64 EndpointTimeoutTick = 0;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Concert Message")` — It's a timespan encoded in ticks. EndpointTimeoutTick represent the time it takes for the sending endpoint to consider another endpoint timed out

#### struct `FConcertAckData`  
`struct FConcertAckData : public FConcertMessageData`  
_L207-218_
- reflection: `USTRUCT()`
- inherits: `FConcertMessageData`
- desc: Acknowledgment messages to reliable events
- L213 _public member_ `int64 AckSendTimeTicks = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — Time when this acknowledgment was sent (UTC)
- L217 _public member_ `FGuid SourceMessageId;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category="Concert Message")` — ID of the source message we're acknowledging

#### struct `FConcertKeepAlive`  
`struct FConcertKeepAlive : public FConcertMessageData`  
_L222-225_
- reflection: `USTRUCT()`
- inherits: `FConcertMessageData`
- desc: Keep alive message

#### struct `FConcertSendResendPending`  
`struct FConcertSendResendPending`  
_L229-232_
- reflection: `USTRUCT()`
- desc: Force the endpoint to resend pending packages.

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_CLASS_FLAGS(EConcertMessageFlags);`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/ConcertTransportSettings.h` (Public)


#### struct `FConcertEndpointSettings`  
`struct FConcertEndpointSettings`  
_L11-32_
- reflection: `USTRUCT()`
- L15 _public function_ `FConcertEndpointSettings() : bEnableLogging(false) , PurgeProcessedMessageDelaySeconds(30) , RemoteEndpointTimeoutSeconds(60)`
- L23 _public member_ `bool bEnableLogging;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Endpoint Settings")` — Enable detailed message logging for Concert endpoints
- L27 _public member_ `int32 PurgeProcessedMessageDelaySeconds;` — `UPROPERTY(config, EditAnywhere, DisplayName="Purge Processed Message Delay", AdvancedDisplay, Category="Endpoint Settings", meta=(ForceUnits=s))` — The timespan at which retained processed messages are purged on Concert endpoints
- L31 _public member_ `int32 RemoteEndpointTimeoutSeconds;` — `UPROPERTY(config, EditAnywhere, DisplayName="Remote Endpoint Timeout", AdvancedDisplay, Category="Endpoint Settings", meta=(ForceUnits=s, ClampMin=4, UIMin=4))` — The timespan at which remote endpoints that haven't sent a message are considered stale

#### class `UConcertEndpointConfig`  
`class UConcertEndpointConfig : public UObject`  
_L35-42_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L41 _public member_ `FConcertEndpointSettings EndpointSettings;` — `UPROPERTY(config, EditAnywhere, Category="Endpoint Settings", meta=(ShowOnlyInnerProperties))`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IConcertEndpoint.h` (Public)


#### struct `FConcertEndpointContext`  
`struct FConcertEndpointContext`  
_L16-29_
- desc: Context information for a Concert endpoint
- L19 _public function_ `FString ToString() const` — Convert this endpoint context into a string in the form "{FriendlyName} ({Id})"
- L25 _public member_ `FGuid EndpointId;` — ID of this endpoint
- L28 _public member_ `FString EndpointFriendlyName;` — Friendly name of this endpoint (not guaranteed to be unique)

#### enum `EConcertRemoteEndpointConnection`  
`enum class EConcertRemoteEndpointConnection : uint8`  
_L34-42_
- desc: Remote endpoint connection statuses when broadcasting changes
- L37 _public enumerator_ `Discovered` — The remote endpoint was discovered.
- L39 _public enumerator_ `TimedOut` — The remote endpoint timed-out.
- L41 _public enumerator_ `ClosedRemotely` — The remote endpoint was closed by the remote peer.

#### class `IConcertRemoteEndpoint`  
`class IConcertRemoteEndpoint`  
_L54-82_
- desc: Interface representing a remote endpoint that you can send to reliably or not from a local Concert endpoint
- L58 _public prototype_ `virtual ~IConcertRemoteEndpoint() = default;` — Virtual destructor
- L61 _public prototype_ `virtual const FConcertEndpointContext& GetEndpointContext() const = 0;` — Get the context for this remote endpoint
- L64 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceived& OnConcertMessageAcknowledgementReceived() = 0;` — Callback when a message has been acknowledged by this remote endpoint
- L70 _protected function_ `static void SetMessageOrderIndex(const TSharedRef<IConcertMessage>& Message, uint16 OrderIndex)` — Set the message order index, for friend class
- L78 _protected function_ `static void SetMessageChannelId(const TSharedRef<IConcertMessage>& Message, uint16 ChannelId)` — Set the message channel ID, for friend class

#### class `IConcertLocalEndpoint`  
`class IConcertLocalEndpoint`  
_L97-339_
- desc: Interface representing a local endpoint you can send from either reliably or not for Concert
- L101 _public prototype_ `virtual ~IConcertLocalEndpoint() = default;` — Virtual destructor
- L104 _public prototype_ `virtual const FConcertEndpointContext& GetEndpointContext() const = 0;` — Get the context for this endpoint.
- L107 _public prototype_ `virtual TArray<FConcertEndpointContext> GetRemoteEndpoints() const = 0;` — Gets all remote endpoints connected to this local endpoint.
- L110 _public prototype_ `virtual FMessageAddress GetRemoteAddress(const FGuid& ConcertEndpointId) const = 0;` — Gets the remote address of a client or the server. If ConcertEndpointId is not valid, the result's IsValid return false.
- L113 _public prototype_ `virtual FOnConcertRemoteEndpointConnectionChanged& OnRemoteEndpointConnectionChanged() = 0;` — Callback when a remote endpoint connection changes.
- L116 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() = 0;` — Callback when a message has been acknowledged by a remote endpoint
- L125 _public function_ `template<typename RequestType, typename ResponseType> TFuture<ResponseType> SendRequest(const RequestType& Request, const FGuid& Endpoint)` — Send a request to a remote endpoint @param Request : the request to send, needs to be a UStruct that derives from FConcertRequestData @param Endpoint : the remote endpoint Id to send to @return A future of the response for the request
- L146 _public typedef_ `typedef TConcertEvent<EventType> ConcertEventType;`
- L147 _public member_ `TSharedRef<ConcertEventType> EventRef = MakeShared<ConcertEventType>(Event);`
- L149 _public prototype_ `EventRef.Get().SetAnnotations(MoveTemp(Annotations));`
- L150 _public prototype_ `InternalQueueEvent(EventRef, Endpoint, Flags);`
- L158 _public function_ `template<typename EventType> void PublishEvent(const EventType& Event)` — Publish an event, other remote endpoint need to subscribe to the event to receive it @param Event : the event to publish, needs to be a UStruct that derives from FConcertEventData
- L172 _public function_ `template<typename RequestType, typename ResponseType> void RegisterRequestHandler(typename TConcertFunctionRequestHandler<ResponseType>::FFuncType Func)` — Register an handler for request received by this endpoint @param Func	  : Function to handle the request of type RequestType
- L184 _public function_ `template<typename RequestType, typename ResponseType, typename HandlerType> void RegisterRequestHandler(HandlerType* Handler, typename TConcertRawRequestHandler<ResponseType, HandlerType>::FFuncType Func)` — Register an handler for request received by this endpoint @param Handler : Pointer for the handler @param Func	  : Member function of the Handler to handle the request of type RequestType
- L194 _public function_ `template<typename RequestType> void UnregisterRequestHandler()` — Unregister the handler for request received by this endpoint of type RequestType
- L205 _public function_ `template<typename EventType> void RegisterEventHandler(typename TConcertFunctionEventHandler::FFuncType Func)` — Register an handler for event received by this endpoint @param Func	  : Function to handle the event of type EventType
- L217 _public function_ `template<typename EventType, typename HandlerType> void RegisterEventHandler(HandlerType* Handler, typename TConcertRawEventHandler<HandlerType>::FFuncType Func)` — Register an handler for event received by this endpoint @param Handler : Pointer for the handler @param Func	  : Member function of the Handler to handle the event of type EventType
- L227 _public function_ `template<typename EventType> void UnregisterEventHandler()` — Unregister the handler for event received by this endpoint of type EventType
- L239 _public function_ `template<typename EventType, typename HandlerType> void SubscribeEventHandler(HandlerType* Handler, typename TConcertRawEventHandler<HandlerType>::FFuncType Func)` — Subscribe an handler for event received by this endpoint, this will handle published event @param Handler : Pointer for the handler @param Func	  : Member function of the Handler to handle the event of type EventType
- L252 _public function_ `template<typename EventType> void UnsubscribeEventHandler()` — Unregister the handler for event received by this endpoint of type EventType
- L267 _protected function_ `void SetMessageSendingInfo(const TSharedRef<IConcertMessage>& Message)` — Set message ID and sender ID
- L274 _protected function_ `void SetResponseSendingInfo(const TSharedRef<IConcertResponse>& Response, const FGuid& RequestMessageId)` — Set message ID and sender ID
- L283 _protected prototype_ `virtual void InternalAddRequestHandler(const FTopLevelAssetPath& RequestMessageType, const TSharedRef<IConcertRequestHandler>& Handler) = 0;` — Add a Request Handler
- L288 _protected prototype_ `virtual void InternalRemoveRequestHandler(const FTopLevelAssetPath& RequestMessageType) = 0;` — Remove an Request Handler
- L293 _protected prototype_ `virtual void InternalAddEventHandler(const FTopLevelAssetPath& EventMessageType, const TSharedRef<IConcertEventHandler>& Handler) = 0;` — Add an Event Handler
- L298 _protected prototype_ `virtual void InternalRemoveEventHandler(const FTopLevelAssetPath& EventMessageType) = 0;` — Remove an Event Handler
- L303 _protected prototype_ `virtual void InternalSubscribeToEvent(const FTopLevelAssetPath& EventMessageType) = 0;` — Subscribe to an Event
- L308 _protected prototype_ `virtual void InternalUnsubscribeFromEvent(const FTopLevelAssetPath& EventMessageType) = 0;` — Unsubscribe from an Event
- L316 _protected prototype_ `virtual void InternalQueueRequest(const TSharedRef<IConcertRequest>& Request, const FGuid& Endpoint) = 0;` — Queue a request to be sent to a remote endpoint @param Request : the type erased request @param Endpoint : the remote endpoint Id to send to @return A future of the response for the request
- L324 _protected prototype_ `virtual void InternalQueueResponse(const TSharedRef<IConcertResponse>& Response, const FGuid& Endpoint) = 0;` — Queue a response to be sent back to a remote endpoint @param Response : the type erased response @param Endpoint : the remote endpoint Id to send to @return A future of the response for the request
- L332 _protected prototype_ `virtual void InternalQueueEvent(const TSharedRef<IConcertEvent>& Event, const FGuid& Endpoint, EConcertMessageFlags Flags) = 0;` — Queue an event to be sent to a remote endpoint @param Event : the type erased event @param Endpoint : the remote endpoint Id to send to Flags : flags for the event (i.e.: is the event reliable)
- L338 _protected prototype_ `virtual void InternalPublishEvent(const TSharedRef<IConcertEvent>& Event) = 0;` — Publish an event to any listening endpoints @param Event : the type erased event

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertMessageAcknowledgementReceived, const FConcertEndpointContext& , const TSharedRef<IConcertMessage>& , const FConcertMessageContext& );`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertMessageAcknowledgementReceived, const FConcertEndpointContext& , const TSharedRef<IConcertMessage>& , const FConcertMessageContext& );`
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertRemoteEndpointConnectionChanged, const FConcertEndpointContext&, EConcertRemoteEndpointConnection);`
- L85 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertRemoteEndpointConnectionChanged, const FConcertEndpointContext&, EConcertRemoteEndpointConnection);`
- L86 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint, const FConcertEndpointContext& , const FConcertEndpointContext& , const TSharedRef<IConcertMessage>& , const FConcertMessageContext& );`
- L86 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint, const FConcertEndpointContext& , const FConcertEndpointContext& , const TSharedRef<IConcertMessage>& , const FConcertMessageContext& );`
- L128 _typedef_ `typedef TConcertRequest<RequestType, ResponseType> ConcertRequestType;` (scope `IConcertLocalEndpoint::SendRequest`)
- L161 _typedef_ `typedef TConcertEvent<EventType> ConcertEventType;` (scope `IConcertLocalEndpoint::PublishEvent`)
- L341 _typedef_ `typedef TSharedPtr<IConcertLocalEndpoint> IConcertLocalEndpointPtr;` — TODO: need thread safe?

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IConcertMessageHandler.h` (Public)


#### class `IConcertRequestHandler`  
`class IConcertRequestHandler`  
_L14-25_
- desc: Interface for Concert Endpoint request handler
- L17 _public prototype_ `virtual ~IConcertRequestHandler() = default;`
- L24 _public prototype_ `virtual TFuture<TSharedPtr<IConcertResponse>> HandleRequest(const FConcertMessageContext& Context) const = 0;` — Handle the request from the context passed @param Context the concert message context, the message needs to be casted @return a shared ptr to a Concert Response

#### class `IConcertEventHandler`  
`class IConcertEventHandler`  
_L30-40_
- desc: Interface for Concert Endpoint event handler
- L33 _public prototype_ `virtual ~IConcertEventHandler() = default;`
- L39 _public prototype_ `virtual void HandleEvent(const FConcertMessageContext& Context) const = 0;` — Handle the request from the context passed @param Context the concert message context, the message needs to be casted

#### class `TConcertFunctionEventHandler`  
`class TConcertFunctionEventHandler : public IConcertEventHandler`  
_L45-64_
- inherits: `IConcertEventHandler`
- desc: Implementation of Concert Endpoint event handler using a TFunction
- L49 _public typedef_ `typedef TFunction<void(const FConcertMessageContext&)> FFuncType;` — Type definition for function pointers that are compatible with Event of this TConcertRawEventHandler.
- L51 _public function_ `TConcertFunctionEventHandler(FFuncType InFunc) : Func(MoveTemp(InFunc))`
- L54 _public prototype_ `virtual ~TConcertFunctionEventHandler() = default;`
- L56 _public function_ `virtual void HandleEvent(const FConcertMessageContext& Context) const`
- L63 _private member_ `FFuncType Func;`

#### class `TConcertRawEventHandler`  
`template<typename HandlerType> class TConcertRawEventHandler : public IConcertEventHandler`  
_L70-92_
- inherits: `IConcertEventHandler`
- desc: Implementation of Concert Endpoint event handler using a raw member function pointer
- L74 _public typedef_ `typedef void (HandlerType::*FFuncType)(const FConcertMessageContext&);` — Type definition for function pointers that are compatible with Event of this TConcertRawEventHandler.
- L76 _public function_ `TConcertRawEventHandler(HandlerType* InHandler, FFuncType InFunc) : Handler(InHandler) , Func(InFunc)`
- L82 _public prototype_ `virtual ~TConcertRawEventHandler() = default;`
- L84 _public function_ `virtual void HandleEvent(const FConcertMessageContext& Context) const`
- L90 _private member_ `HandlerType* Handler;`
- L91 _private member_ `FFuncType Func;`

#### class `TConcertFunctionRequestHandler`  
`template<typename ResponseType> class TConcertFunctionRequestHandler : public IConcertRequestHandler`  
_L98-120_
- inherits: `IConcertRequestHandler`
- desc: Implementation of Concert Endpoint request handler using TFunction
- L102 _public typedef_ `typedef TFunction<TFuture<ResponseType>(const FConcertMessageContext&)> FFuncType;` — Type definition for function pointers that are compatible with Request of this TConcertRawRequestHandler.
- L104 _public function_ `TConcertFunctionRequestHandler(FFuncType InFunc) : Func(MoveTemp(InFunc))`
- L107 _public prototype_ `virtual ~TConcertFunctionRequestHandler() = default;`
- L109 _public function_ `virtual TFuture<TSharedPtr<IConcertResponse>> HandleRequest(const FConcertMessageContext& Context) const`
- L119 _private member_ `FFuncType Func;`

#### class `TConcertRawRequestHandler`  
`template<typename ResponseType, typename HandlerType> class TConcertRawRequestHandler : public IConcertRequestHandler`  
_L126-152_
- inherits: `IConcertRequestHandler`
- desc: Implementation of Concert Endpoint request handler using a raw member function pointer
- L130 _public typedef_ `typedef TFuture<ResponseType>(HandlerType::*FFuncType)(const FConcertMessageContext&);` — Type definition for function pointers that are compatible with Event of this TConcertRawRequestHandler.
- L132 _public function_ `TConcertRawRequestHandler(HandlerType* InHandler, FFuncType InFunc) : Handler(InHandler) , Func(InFunc)`
- L138 _public prototype_ `virtual ~TConcertRawRequestHandler() = default;`
- L140 _public function_ `virtual TFuture<TSharedPtr<IConcertResponse>> HandleRequest(const FConcertMessageContext& Context) const`
- L150 _private member_ `HandlerType* Handler;`
- L151 _private member_ `FFuncType Func;`

#### Free symbols / members of external scopes

- L113 _function_ `` (scope `TConcertFunctionRequestHandler::HandleRequest`)
- L144 _function_ `` (scope `TConcertRawRequestHandler::HandleRequest`)

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IConcertMessages.h` (Public)


#### enum `EConcertMessageType`  
`enum class EConcertMessageType`  
_L11-19_
- desc: Types of Concert Messages
- L14 _public enumerator_ `Event` — Message is a event
- L16 _public enumerator_ `Request` — Message is a request
- L18 _public enumerator_ `Response` — Message is a response

#### enum `EConcertMessageState`  
`enum class EConcertMessageState`  
_L22-32_
- desc: States of Concert Messages
- L25 _public enumerator_ `Pending` — Message has been sent and is awaiting a response
- L27 _public enumerator_ `Acknowledged` — Message has received its acknowledgment response, but is not yet complete
- L29 _public enumerator_ `Completed` — Message has received its acknowledgment response and was completed
- L31 _public enumerator_ `TimedOut` — Message timed out

#### class `IConcertMessage`  
`class IConcertMessage`  
_L35-100_
- desc: Abstract for Concert Message
- L38 _public prototype_ `virtual ~IConcertMessage() = default;`
- L41 _public prototype_ `virtual FGuid GetMessageId() const = 0;` — Get the ID of the message
- L44 _public prototype_ `virtual uint16 GetMessageOrderIndex() const = 0;` — Get the order index of the message (for ordering reliable messages, used when ChannelId != UnreliableChannelId)
- L47 _public prototype_ `virtual uint16 GetChannelId() const = 0;` — Get the ID of the channel this message was sent from
- L50 _public prototype_ `virtual bool IsReliable() const = 0;` — Get is the message is flagged a reliable
- L53 _public prototype_ `virtual EConcertMessageType GetType() const = 0;` — Get the message type
- L56 _public prototype_ `virtual EConcertMessageState GetState() const = 0;` — Get the message state
- L59 _public prototype_ `virtual const FGuid& GetSenderId() const = 0;` — Get the Concert Endpoint Id of the sender
- L62 _public prototype_ `virtual FDateTime GetCreationDate() const = 0;` — Get the Creation time of the message
- L65 _public prototype_ `virtual void* ConstructMessage() const = 0;` — Construct this message data, allocates memory
- L68 _public prototype_ `virtual UScriptStruct* GetMessageType() const = 0;` — Get the message type of the data allocated with ConstructMessage
- L71 _public prototype_ `virtual const void* GetMessageTemplate() const = 0;` — Get the template of the message that will be created with ConstructMessage
- L74 _public prototype_ `virtual void Acknowledge(const FConcertMessageContext& ConcertContext) = 0;` — Acknowledge the message
- L77 _public prototype_ `virtual void TimeOut() = 0;` — Timeout the message
- L80 _public prototype_ `virtual void SetAnnotations(TMap<FName, FString> Annotations) = 0;` — Annotations associated with this message.
- L83 _public prototype_ `virtual const TMap<FName, FString>& GetAnnotations() const = 0;` — Annotations for sending across message bus
- L90 _protected prototype_ `virtual void SetMessageId(const FGuid& MessageId) = 0;` — Set the ID of the message. Call before ConstructMessage.
- L93 _protected prototype_ `virtual void SetOrderIndex(uint16 OrderIndex) = 0;` — Set the order index of the message (for ordering reliable messages, used when ChannelId != UnreliableChannelId). Call before ConstructMessage.
- L96 _protected prototype_ `virtual void SetChannelId(uint16 Channel) = 0;` — Set the ID of the channel this message was sent from. Call before ConstructMessage.
- L99 _protected prototype_ `virtual void SetSenderId(const FGuid& SenderId) = 0;` — Set the Concert Endpoint Id of the sender. Call before ConstructMessage.

#### class `IConcertEvent`  
`class IConcertEvent : public IConcertMessage`  
_L103-112_
- inherits: `IConcertMessage`
- desc: Abstract class for Concert Event
- L106 _public prototype_ `virtual ~IConcertEvent() = default;`
- L108 _public function_ `virtual EConcertMessageType GetType() const override`

#### class `IConcertRequest`  
`class IConcertRequest : public IConcertMessage`  
_L115-124_
- inherits: `IConcertMessage`
- desc: Abstract class for Concert Request
- L118 _public prototype_ `virtual ~IConcertRequest() = default;`
- L120 _public function_ `virtual EConcertMessageType GetType() const override`

#### class `IConcertResponse`  
`class IConcertResponse : public IConcertMessage`  
_L127-142_
- inherits: `IConcertMessage`
- desc: Abstract class for Concert Response
- L130 _public prototype_ `virtual ~IConcertResponse() = default;`
- L132 _public function_ `virtual EConcertMessageType GetType() const override`
- L141 _protected prototype_ `virtual void SetRequestMessageId(const FGuid& RequestMessageId) = 0;` — Set the ID of the request this response is for

#### class `TConcertMessage`  
`template<typename MessageBase, typename MessageType> class TConcertMessage : public MessageBase`  
_L148-262_
- inherits: `MessageBase`
- desc: Implements common portion of Concert Message
- L152 _public function_ `TConcertMessage(const MessageType& Message) : CreationDate(FDateTime::UtcNow()) , MessageState(EConcertMessageState::Pending) , MessageTemplate(Message)`
- L159 _public function_ `TConcertMessage(MessageType&& Message) : CreationDate(FDateTime::UtcNow()) , MessageState(EConcertMessageState::Pending) , MessageTemplate(MoveTemp(Message))`
- L166 _public prototype_ `virtual ~TConcertMessage() = default;`
- L168 _public function_ `virtual FGuid GetMessageId() const`
- L173 _public function_ `virtual uint16 GetMessageOrderIndex() const`
- L178 _public function_ `virtual uint16 GetChannelId() const`
- L183 _public function_ `virtual bool IsReliable() const override`
- L188 _public function_ `virtual EConcertMessageState GetState() const override`
- L193 _public function_ `virtual const FGuid& GetSenderId() const override`
- L198 _public function_ `virtual FDateTime GetCreationDate() const override`
- L203 _public function_ `virtual void* ConstructMessage() const override`
- L208 _public function_ `virtual UScriptStruct* GetMessageType() const override`
- L213 _public function_ `virtual const void* GetMessageTemplate() const override`
- L218 _public function_ `virtual void Acknowledge(const FConcertMessageContext& ConcertContext) override`
- L223 _public function_ `virtual void TimeOut() override`
- L228 _public function_ `virtual void SetAnnotations(TMap<FName, FString> InAnnotations) override`
- L233 _public function_ `virtual const TMap<FName, FString>& GetAnnotations() const override`
- L238 _protected function_ `virtual void SetMessageId(const FGuid& MessageId) override`
- L243 _protected function_ `virtual void SetOrderIndex(uint16 OrderIndex) override`
- L248 _protected function_ `virtual void SetChannelId(uint16 Channel) override`
- L253 _protected function_ `virtual void SetSenderId(const FGuid& SenderId) override`
- L258 _protected member_ `TMap<FName, FString> Annotations;`
- L259 _protected member_ `FDateTime CreationDate;`
- L260 _protected member_ `EConcertMessageState MessageState;`
- L261 _protected member_ `MessageType MessageTemplate;`

#### class `TConcertEvent`  
`template<typename EventType> class TConcertEvent : public TConcertMessage<IConcertEvent, EventType>`  
_L265-278_
- inherits: `TConcertMessage<IConcertEvent,EventType>`
- L269 _public function_ `TConcertEvent(const EventType& Event) : TConcertMessage<IConcertEvent, EventType>(Event)`
- L273 _public function_ `TConcertEvent(EventType&& Event) : TConcertMessage<IConcertEvent, EventType>(MoveTemp(Event))`
- L277 _public prototype_ `virtual ~TConcertEvent() = default;`

#### class `TConcertRequest`  
`template<typename RequestType, typename ResponseType> class TConcertRequest : public TConcertMessage<IConcertRequest, RequestType>`  
_L281-350_
- inherits: `TConcertMessage<IConcertRequest,RequestType>`
- L286 _public function_ `TConcertRequest(const RequestType& Request) : TConcertMessage<IConcertRequest, RequestType>(Request)`
- L290 _public function_ `TConcertRequest(RequestType&& Request) : TConcertMessage<IConcertRequest, RequestType>(MoveTemp(Request))`
- L294 _public prototype_ `virtual ~TConcertRequest() = default;`
- L296 _public function_ `TFuture<ResponseType> GetFuture()`
- L301 _public function_ `virtual void Acknowledge(const FConcertMessageContext& ConcertContext) override`
- L336 _public function_ `virtual void TimeOut() override`
- L349 _private member_ `TPromise<ResponseType> Promise;`

#### class `TConcertResponse`  
`template<typename ResponseType> class TConcertResponse : public TConcertMessage<IConcertResponse, ResponseType>`  
_L353-383_
- inherits: `TConcertMessage<IConcertResponse,ResponseType>`
- L357 _public function_ `TConcertResponse(const ResponseType& Response) : TConcertMessage<IConcertResponse, ResponseType>(Response)`
- L363 _public function_ `TConcertResponse(ResponseType&& Response) : TConcertMessage<IConcertResponse, ResponseType>(MoveTemp(Response))`
- L369 _public prototype_ `virtual ~TConcertResponse() = default;`
- L372 _protected function_ `virtual void SetRequestMessageId(const FGuid& RequestMessageId) override`
- L379 _private function_ `void ValidateResponseCode()` — Set the response code to successful if the response generator left it pending

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IConcertTransportLogger.h` (Public)


#### class `IConcertTransportLogger`  
`class IConcertTransportLogger`  
_L18-93_
- desc: Logging interface for Concert Transport layer
- L29 _public prototype_ `virtual ~IConcertTransportLogger() = default;` — Virtual destructor
- L32 _public prototype_ `virtual bool IsLogging() const = 0;` — Is this log currently logging?
- L35 _public prototype_ `virtual void StartLogging() = 0;` — Start logging
- L38 _public prototype_ `virtual void StopLogging() = 0;` — Stop logging
- L41 _public prototype_ `virtual void FlushLog() = 0;` — Flush the log, processing any pending entries
- L44 _public prototype_ `virtual void LogTimeOut(const TSharedRef<IConcertMessage>& Message, const FGuid& EndpointId, const FDateTime& UtcNow) = 0;` — Log a timeout for a Message sent to EndpointId
- L47 _public prototype_ `virtual void LogSendAck(const FConcertAckData& AckData, const FGuid& DestEndpoint) = 0;` — Log an acknowledgment sent to the destination endpoint
- L50 _public prototype_ `virtual void LogSendEndpointClosed(const FConcertEndpointClosedData& EndpointClosedData, const FGuid& DestEndpoint, const FDateTime& UtcNow) = 0;` — Log an endpoint being closed on the remote peer (us!)
- L53 _public prototype_ `virtual void LogSendReliableHandshake(const FConcertReliableHandshakeData& ReliableHandshakeData, const FGuid& DestEndpoint, const FDateTime& UtcNow) = 0;` — Log a reliable handshake sent to the destination endpoint
- L56 _public prototype_ `virtual void LogReceiveReliableHandshake(const FConcertReliableHandshakeData& ReliableHandshakeData, const FGuid& DestEndpoint, const FDateTime& UtcNow) = 0;` — Log a reliable handshake received from the source endpoint
- L59 _public prototype_ `virtual void LogPublish(const TSharedRef<IConcertMessage>& Message) = 0;` — Log the publication of Message
- L62 _public prototype_ `virtual void LogSend(const TSharedRef<IConcertMessage>& Message, const FGuid& DestEndpoint) = 0;` — Log the sending of Message to DestEndpoint
- L65 _public prototype_ `virtual void LogMessageReceived(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log a message received from this ConcertContext
- L68 _public prototype_ `virtual void LogMessageQueued(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log a message queued from this ConcertContext
- L71 _public prototype_ `virtual void LogMessageDiscarded(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint, const EMessageDiscardedReason Reason) = 0;` — Log a message discarded from this ConcertContext
- L74 _public prototype_ `virtual void LogProcessEvent(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log an event processed from this ConcertContext
- L77 _public prototype_ `virtual void LogProcessRequest(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log a request processed from this ConcertContext
- L80 _public prototype_ `virtual void LogProcessResponse(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log a response processed from this ConcertContext
- L83 _public prototype_ `virtual void LogProcessAck(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log a acknowledgment processed from this ConcertContext
- L86 _public prototype_ `virtual void LogRemoteEndpointDiscovery(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) = 0;` — Log the discovery of a remote endpoint with EndpointId
- L89 _public prototype_ `virtual void LogRemoteEndpointTimeOut(const FGuid& EndpointId, const FDateTime& UtcNow) = 0;` — Log a remote endpoint with EndpointId being considered stale or timed out
- L92 _public prototype_ `virtual void LogRemoteEndpointClosure(const FGuid& EndpointId, const FDateTime& UtcNow) = 0;` — Log a remote endpoint with EndpointId being as being closed

#### enum `IConcertTransportLogger::EMessageDiscardedReason`  
`enum class EMessageDiscardedReason : uint8`  
_L21-26_
- L23 _public enumerator_ `NotRequired`
- L24 _public enumerator_ `AlreadyProcessed`
- L25 _public enumerator_ `UnknownEndpoint`

#### class `FConcertTransportLoggerWrapper`  
`class FConcertTransportLoggerWrapper`  
_L98-283_
- desc: Wrapper class around a IConcertTransportLogger pointer
- L101 _public function_ `FConcertTransportLoggerWrapper(const IConcertTransportLoggerPtr& InLogger) : Logger(InLogger)`
- L106 _public function_ `IConcertTransportLoggerPtr GetLogger() const`
- L111 _public function_ `bool IsLogging() const`
- L116 _public function_ `void StartLogging() const`
- L124 _public function_ `void StopLogging() const`
- L132 _public function_ `void FlushLog() const`
- L140 _public function_ `void LogTimeOut(const TSharedRef<IConcertMessage>& Message, const FGuid& EndpointId, const FDateTime& UtcNow) const`
- L148 _public function_ `void LogSendAck(const FConcertAckData& AckData, const FGuid& DestEndpoint) const`
- L156 _public function_ `void LogSendEndpointClosed(const FConcertEndpointClosedData& EndpointClosedData, const FGuid& DestEndpoint, const FDateTime& UtcNow) const`
- L164 _public function_ `void LogSendReliableHandshake(const FConcertReliableHandshakeData& ReliableHandshakeData, const FGuid& DestEndpoint, const FDateTime& UtcNow)`
- L172 _public function_ `void LogReceiveReliableHandshake(const FConcertReliableHandshakeData& ReliableHandshakeData, const FGuid& SrcEndpoint, const FDateTime& UtcNow)`
- L180 _public function_ `void LogPublish(const TSharedRef<IConcertMessage>& Message) const`
- L188 _public function_ `void LogSend(const TSharedRef<IConcertMessage>& Message, const FGuid& DestEndpoint) const`
- L196 _public function_ `void LogMessageReceived(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L204 _public function_ `void LogMessageQueued(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L212 _public function_ `void LogMessageDiscarded(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint, const IConcertTransportLogger::EMessageDiscardedReason Reason) const`
- L220 _public function_ `void LogProcessEvent(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L228 _public function_ `void LogProcessRequest(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L236 _public function_ `void LogProcessResponse(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L244 _public function_ `void LogProcessAck(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L252 _public function_ `void LogRemoteEndpointDiscovery(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) const`
- L260 _public function_ `void LogRemoteEndpointTimeOut(const FGuid& EndpointId, const FDateTime& UtcNow) const`
- L268 _public function_ `void LogRemoteEndpointClosure(const FGuid& EndpointId, const FDateTime& UtcNow) const`
- L276 _public function_ `void Reset()`
- L282 _private member_ `IConcertTransportLoggerPtr Logger;`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IConcertTransportLoggerPtr.h` (Public)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedRef<IConcertTransportLogger, ESPMode::ThreadSafe> IConcertTransportLoggerRef;`
- L12 _typedef_ `typedef TSharedPtr<IConcertTransportLogger, ESPMode::ThreadSafe> IConcertTransportLoggerPtr;`
- L17 _typedef_ `typedef TFunction<IConcertTransportLoggerRef(const FConcertEndpointContext&)> FConcertTransportLoggerFactory;` — Factory function used to create a concrete instance of IConcertTransportLogger.

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IConcertTransportModule.h` (Public)


#### class `IConcertEndpointProvider`  
`class IConcertEndpointProvider`  
_L16-23_
- desc: Interface for an Endpoint Provider
- L19 _public prototype_ `virtual ~IConcertEndpointProvider() = default;`
- L22 _public prototype_ `virtual TSharedPtr<IConcertLocalEndpoint> CreateLocalEndpoint(const FString& InEndpointFriendlyName, const FConcertEndpointSettings& InEndpointSettings, const FConcertTransportLoggerFactory& InLogFactory) const = 0;`

#### class `IConcertTransportModule`  
`class IConcertTransportModule : public IModuleInterface`  
_L28-56_
- inherits: `IModuleInterface`
- desc: Interface for the Concert Transport module.
- L37 _public function_ `static inline IConcertTransportModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L48 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L55 _public prototype_ `virtual TSharedPtr<IConcertEndpointProvider> CreateEndpointProvider() const = 0;` — Create a local transport endpoint

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IdentifierTable/ConcertIdentifierTable.h` (Public)


#### struct `TConcertIdentifierTable_CaseSensitivePlainNameKeyFuncs`  
`template <typename ValueType> struct TConcertIdentifierTable_CaseSensitivePlainNameKeyFuncs : BaseKeyFuncs<ValueType, FName, false>`  
_L12-26_
- inherits: `BaseKeyFuncs<ValueType,FName,false>`
- desc: Key functions that compare FName instances by only their display string (to perform a case-sensitive plain string comparison)
- L14 _public function_ `static FORCEINLINE const FName& GetSetKey(const TPair<FName, ValueType>& Element)`
- L18 _public function_ `static FORCEINLINE bool Matches(const FName& A, const FName& B)`
- L22 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FName& Key)`

#### class `FConcertLocalIdentifierTable`  
`class FConcertLocalIdentifierTable`  
_L29-81_
- desc: Cache of identifiers (currently names) that have been serialized locally and should be sent along with the serialized data
- L32 _public prototype_ `FConcertLocalIdentifierTable() = default;`
- L33 _public prototype_ `explicit FConcertLocalIdentifierTable(const FConcertLocalIdentifierState& InState);`
- L38 _public member_ `static FConcertLocalIdentifierTable* ForceFNameTableIndex;` — Constant used to force names to serialize as their FName table index value (non-portable!)
- L43 _public prototype_ `bool HasMappings() const;` — Does this table have any mappings in it?
- L48 _public prototype_ `int32 MapName(const FName& InName);` — Map the given name to its identifier index.
- L54 _public prototype_ `bool UnmapName(const int32 InIndex, FName& OutName) const;` — Unmap the given name from its identifier index (or NAME_None). @return true if the name was unmapped, false if the name wasn't mapped (OutName will be set to NAME_None).
- L59 _public prototype_ `bool HasName(const int32 InIndex) const;` — Is the given identifier index mapped?
- L64 _public prototype_ `bool HasName(const FName& InName, int32* OutIndexPtr = nullptr) const;` — Is the given name mapped?
- L69 _public prototype_ `void SetState(const FConcertLocalIdentifierState& InState);` — Set the state of this identifier table.
- L74 _public prototype_ `void GetState(FConcertLocalIdentifierState& OutState) const;` — Get the state of this identifier table.
- L78 _private member_ `TArray<FName> MappedNames;` — Array of locally mapped names
- L80 _private member_ `TMap<FName, int32, FDefaultSetAllocator, TConcertIdentifierTable_CaseSensitivePlainNameKeyFuncs<int32>> NameToMappedIndex;` — Map of known names to their index in MappedNames (name -> index)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONCERTTRANSPORT_API`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IdentifierTable/ConcertIdentifierTableData.h` (Public)


#### struct `FConcertLocalIdentifierState`  
`struct FConcertLocalIdentifierState`  
_L9-30_
- reflection: `USTRUCT()`
- L13 _public function_ `void Reset(const int32 NewSize = 0)`
- L18 _public function_ `void Empty(const int32 Slack = 0)`
- L23 _public function_ `bool IsEmpty() const`
- L29 _public member_ `TArray<FString> MappedNames;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IdentifierTable/ConcertIdentifierTablePtr.h` (Public)


#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TSharedRef<FConcertLocalIdentifierTable, ESPMode::ThreadSafe> FConcertLocalIdentifierTableRef;`
- L10 _typedef_ `typedef TSharedPtr<FConcertLocalIdentifierTable, ESPMode::ThreadSafe> FConcertLocalIdentifierTablePtr;`
- L11 _typedef_ `typedef TSharedRef<const FConcertLocalIdentifierTable, ESPMode::ThreadSafe> FConcertLocalIdentifierTableConstRef;`
- L12 _typedef_ `typedef TSharedPtr<const FConcertLocalIdentifierTable, ESPMode::ThreadSafe> FConcertLocalIdentifierTableConstPtr;`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/IdentifierTable/ConcertTransportArchives.h` (Public)


#### class `FConcertIdentifierWriter`  
`class FConcertIdentifierWriter : public FMemoryWriter`  
_L14-32_
- inherits: `FMemoryWriter`
- desc: Archive for writing identifiers (currently names) in a way that avoids duplication by caching them against their internal key, which can then be mapped over the network
- L17 _public prototype_ `FConcertIdentifierWriter(FConcertLocalIdentifierTable* InLocalIdentifierTable, TArray<uint8>& InBytes, bool bIsPersistent = false);`
- L22 _public prototype_ `virtual FArchive& operator<<(FName& Name) override;`
- L23 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& AssetPtr) override;`
- L24 _public prototype_ `virtual FString GetArchiveName() const override;`
- L28 _protected function_ `FConcertLocalIdentifierTable* GetLocalIdentifierTable() const`
- L31 _private member_ `FConcertLocalIdentifierTable* LocalIdentifierTable;`

#### class `FConcertIdentifierReader`  
`class FConcertIdentifierReader : public FMemoryReader`  
_L35-53_
- inherits: `FMemoryReader`
- desc: Archive for reading identifiers (currently names) in a way that avoids duplication by caching them against their internal key, which can then be mapped over the network
- L38 _public prototype_ `FConcertIdentifierReader(const FConcertLocalIdentifierTable* InLocalIdentifierTable, const TArray<uint8>& InBytes, bool bIsPersistent = false);`
- L43 _public prototype_ `virtual FArchive& operator<<(FName& Name) override;`
- L44 _public prototype_ `FArchive& operator<<(FSoftObjectPath& AssetPtr) override;`
- L45 _public prototype_ `virtual FString GetArchiveName() const override;`
- L49 _protected function_ `const FConcertLocalIdentifierTable* GetLocalIdentifierTable() const`
- L52 _private member_ `const FConcertLocalIdentifierTable* LocalIdentifierTable;`

#### class `FConcertIdentifierRewriter`  
`class FConcertIdentifierRewriter : public FMemoryArchive`  
_L56-106_
- inherits: `FMemoryArchive`
- desc: Archive for rewriting identifiers (currently names) so that they belong to a different identifier table
- L59 _public prototype_ `FConcertIdentifierRewriter(const FConcertLocalIdentifierTable* InLocalIdentifierTable, FConcertLocalIdentifierTable* InRewriteIdentifierTable, TArray<uint8>& InBytes, bool bIsPersistent = false);`
- L64 _public prototype_ `virtual FArchive& operator<<(FName& Name) override;`
- L65 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& AssetPtr) override;`
- L66 _public prototype_ `virtual int64 TotalSize() override final;`
- L67 _public prototype_ `virtual void Serialize(void* Data, int64 Num) override final;`
- L68 _public prototype_ `virtual FString GetArchiveName() const override;`
- L72 _protected function_ `const FConcertLocalIdentifierTable* GetLocalIdentifierTable() const`
- L73 _protected function_ `FConcertLocalIdentifierTable* GetRewriteIdentifierTable() const`
- L76 _protected function_ `template <typename T> void RewriteData(const int64 OldDataOffset, const int64 OldDataSize, T& NewData)`
- L102 _private member_ `const FConcertLocalIdentifierTable* LocalIdentifierTable = nullptr;`
- L103 _private member_ `FConcertLocalIdentifierTable* RewriteIdentifierTable = nullptr;`
- L104 _private member_ `TArray<uint8>& Bytes;`
- L105 _private member_ `TArray<uint8> ScratchBytes;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTTRANSPORT_API`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Scratchpad/ConcertScratchpad.h` (Public)


#### class `FConcertScratchpad`  
`class FConcertScratchpad`  
_L10-125_
- desc: Scratchpad of id -> value pairs corresponding to a particular client
- L20 _private typedef_ `typedef TSharedPtr<IScratchpadValue, ESPMode::ThreadSafe> IScratchpadValuePtr;`
- L48 _public prototype_ `bool HasValue(const FName& InId) const;` — Does the scratchpad have a value for the given key?
- L54 _public function_ `template <typename T> void SetValue(const FName& InId, const T& InValue)` — Set the scratchpad value associated with the given key.
- L63 _public function_ `template <typename T> void SetValue(const FName& InId, T&& InValue)` — Set the scratchpad value associated with the given key.
- L72 _public function_ `template <typename T> T* GetValue(const FName& InId)` — Get the scratchpad value associated with the given key (if any).
- L82 _public function_ `template <typename T> const T* GetValue(const FName& InId) const` — Get the scratchpad value associated with the given key (if any).
- L92 _public function_ `template <typename T> T& GetValueChecked(const FName& InId)` — Get the scratchpad value associated with the given key, or assert if missing.
- L103 _public function_ `template <typename T> const T& GetValueChecked(const FName& InId) const` — Get the scratchpad value associated with the given key, or assert if missing.
- L114 _private prototype_ `void InternalSetValue(const FName& InId, IScratchpadValuePtr&& InValue);` — Set the internal scratchpad value associated with the given key.
- L119 _private prototype_ `IScratchpadValuePtr InternalGetValue(const FName& InId) const;` — Get the internal scratchpad value associated with the given key (if any).
- L122 _private member_ `mutable FCriticalSection ScratchpadValuesCS;` — Critical section protecting concurrent access to ScratchpadValues
- L124 _private member_ `TMap<FName, IScratchpadValuePtr> ScratchpadValues;` — Map of values (id -> value)

#### struct `FConcertScratchpad::IScratchpadValue`  
`struct IScratchpadValue`  
_L14-19_
- desc: Scratchpad value interface
- L16 _public prototype_ `virtual ~IScratchpadValue() = default;`
- L17 _public prototype_ `virtual void* GetValuePtr() = 0;`
- L18 _public prototype_ `virtual const void* GetValuePtr() const = 0;`

#### struct `FConcertScratchpad::TScratchpadValue`  
`template <typename T> struct TScratchpadValue : public IScratchpadValue`  
_L24-42_
- inherits: `IScratchpadValue`
- desc: Scratchpad value implementation
- L26 _public function_ `explicit TScratchpadValue(T&& InValue) : Value(Forward<T>(InValue))`
- L31 _public function_ `virtual void* GetValuePtr() override`
- L36 _public function_ `virtual const void* GetValuePtr() const override`
- L41 _public member_ `T Value;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTTRANSPORT_API`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Scratchpad/ConcertScratchpadPtr.h` (Public)


#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TSharedRef<FConcertScratchpad, ESPMode::ThreadSafe> FConcertScratchpadRef;`
- L10 _typedef_ `typedef TSharedPtr<FConcertScratchpad, ESPMode::ThreadSafe> FConcertScratchpadPtr;`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Trace/ConcertProtocolTrace.h` (Public)


#### enum `UE::ConcertTrace::EProtocolSuite`  
`enum class EProtocolSuite : uint8`  
_L41-47_
- L43 _public enumerator_ `Unknown`
- L46 _public enumerator_ `Replication` — The traces are related to the replication system

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace ConcertTrace` (scope `UE`)
- L49 _function_ `FORCEINLINE uint8 ProtocolSuiteToInt(EProtocolSuite Id)` (scope `UE::ConcertTrace`)
- L52 _prototype_ `bool IsTracing(EProtocolSuite Id);` (scope `UE::ConcertTrace`) — @return Whether the given protocol is currently being traced
- L54 _function_ `FORCEINLINE bool IsTracingReplication()` (scope `UE::ConcertTrace`) — @return Whether replication is currently being traced.
- L67 _macro_ `#define CONCERT_TRACE_INIT(EndpointIdAsTOptional, InEndpointDisplayFString, IsServer) INTERNAL_CONCERT_TRACE_INIT(EndpointIdAsTOptional, InEndpointDisplayFString, IsServer)` — Event that is emitted when a trace is started in the local instance. @param InEndpointIdAsTOptional TOptional<FGuid> that identifies the local instance endpoint ID in the active session. This should always be set if started via ConcertInsightsSynchronizedTrace. May be unset when the trace is conventionally started by user. @param IsServer Whether the local instance is the server
- L81 _macro_ `#define CONCERT_TRACE_OBJECT_SCOPE(EventName, ObjectPath, SequenceId, ProtocolId) INTERNAL_CONCERT_TRACE_OBJECT_SCOPE(EventName, ObjectPath, SequenceId, ProtocolId)` — Logs an event with a start an end time. In Insights, this will show a track that begins at the current time and ends when the scope terminates. Supports nesting. @param EventName The name of the event to show @param ObjectPath The object this event pertains to. Events with the same ObjectPath and SequenceID are grouped in one track. @param SequenceId Which change to associate this event to (use-case defined). Events with the same ObjectPath and SequenceID are grouped in one track. @param ProtocolId The protocol to group this event under.
- L84 _macro_ `#define CONCERT_TRACE_OBJECT_TRANSMISSION_START(DestinationEndpointId, ObjectPath, SequenceId, ProtocolId) INTERNAL_CONCERT_TRACE_OBJECT_TRANSMISSION_START(DestinationEndpointId, ObjectPath, SequenceId, ProtocolId)` — Traces that the local endpoint has handed the object's sequence data to message bus. The time from now until CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE is visualized as transit time.
- L86 _macro_ `#define CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE(ObjectPath, SequenceId, ProtocolId) INTERNAL_CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE(ObjectPath, SequenceId, ProtocolId)` — Traces that the local endpoint has received the object's sequence data. The time from now the previous CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE until now is visualized as transit time.
- L88 _macro_ `#define CONCERT_TRACE_OBJECT_SINK(SinkName, ObjectPath, SequenceId, ProtocolId) INTERNAL_CONCERT_TRACE_OBJECT_SINK(SinkName, ObjectPath, SequenceId, ProtocolId)` — The object's data has been fully processed. End of the object track.
- L105 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_SCOPE(EventName, ObjectPath, SequenceId) CONCERT_TRACE_OBJECT_SCOPE(EventName, ObjectPath, SequenceId, ProtocolSuiteToInt(UE::ConcertTrace::EProtocolSuite::Replication))` — Logs an event with a start an end time. In Insights, this will show a track that begins at the current time and ends at the start time of the next event. Supports nesting. @param EventName The name of the event to show @param ObjectPath The object this event pertains to. @param SequenceId Determined by sending client and passed along to all other endpoints.
- L108 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_TRANSMISSION_START(DestinationEndpointId, ObjectPath, SequenceId) CONCERT_TRACE_OBJECT_TRANSMISSION_START(DestinationEndpointId, ObjectPath, SequenceId, ProtocolSuiteToInt(UE::ConcertTrace::EProtocol` — Traces that the local endpoint has handed the object's sequence data to message bus. The time from now until CONCERT_TRACE_REPLICATION_OBJECT_TRANSMISSION_RECEIVE is visualized as transit time.
- L110 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_TRANSMISSION_RECEIVE(ObjectPath, SequenceId) CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE(ObjectPath, SequenceId, ProtocolSuiteToInt(UE::ConcertTrace::EProtocolSuite::Replication))` — Traces that the local endpoint has received the object's sequence data. The time from now the previous CONCERT_TRACE_REPLICATION_OBJECT_TRANSMISSION_START until now is visualized as transit time.
- L112 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_SINK(SinkName, ObjectPath, SequenceId) CONCERT_TRACE_OBJECT_SINK(SinkName, ObjectPath, SequenceId, ProtocolSuiteToInt(UE::ConcertTrace::EProtocolSuite::Replication))` — The object's data has been fully processed. End of the object track.
- L115 _macro_ `#define CONCERT_TRACE_INIT(EndpointIdAsTOptional, InEndpointDisplayFString, IsServer)`
- L116 _macro_ `#define CONCERT_TRACE_OBJECT_SCOPE(EventName, ObjectPath, SequenceId, ProtocolId)`
- L117 _macro_ `#define CONCERT_TRACE_OBJECT_EVENT(EventName, ObjectPath, SequenceId, ProtocolId)`
- L118 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_SCOPE(EventName, ObjectPath, SequenceId)`
- L119 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_EVENT(EventName, ObjectPath, SequenceId)`
- L120 _macro_ `#define CONCERT_TRACE_OBJECT_TRANSMISSION_START(DestinationEndpointId, ObjectPath, SequenceId, ProtocolId)`
- L121 _macro_ `#define CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE(ObjectPath, SequenceId, ProtocolId)`
- L122 _macro_ `#define CONCERT_TRACE_OBJECT_SINK(ObjectPath, SequenceId, ProtocolId)`
- L123 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_TRANSMISSION_START(DestinationEndpointId, ObjectPath, SequenceId)`
- L124 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_TRANSMISSION_RECEIVE(ObjectPath, SequenceId)`
- L125 _macro_ `#define CONCERT_TRACE_REPLICATION_OBJECT_SINK(SinkName, ObjectPath, SequenceId)`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Trace/ConcertTrace.h` (Public)


#### Free symbols / members of external scopes

- L15 _macro_ `# define SCOPED_CONCERT_TRACE(TraceName) TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(TraceName, ConcertChannel)`
- L17 _macro_ `# define SCOPED_CONCERT_TRACE(TraceName)`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Trace/ConcertTraceConfig.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `# define UE_CONCERT_TRACE_ENABLED 1`
- L12 _macro_ `# define UE_CONCERT_TRACE_ENABLED 0`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Trace/Private/ConcertProtocolTraceInternal.h` (Public)


#### enum `UE::ConcertTrace::EConcertTraceVersion`  
`enum class EConcertTraceVersion : uint8`  
_L14-22_
- desc: Sent as part of the Init event for backwards compatibility.
- L17 _public enumerator_ `Initial = 0` — Initial version of Concert Insights.
- L20 _public enumerator_ `LatestPlusOne` — Add new entries above
- L21 _public enumerator_ `Latest = LatestPlusOne - 1`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertTrace` (scope `UE`)
- L24 _prototype_ `void Init(const TOptional<FGuid>& LocalEndpointId, const FString& ClientDisplayName, bool bIsServer);` (scope `UE::ConcertTrace`)
- L25 _prototype_ `void LogTransmissionStart(uint8 Protocol, uint32 SequenceId, const FSoftObjectPath& ObjectPath, const FGuid& TargetEndpointId);` (scope `UE::ConcertTrace`)
- L26 _prototype_ `void LogTransmissionReceive(uint8 Protocol, uint32 SequenceId, const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertTrace`)
- L27 _prototype_ `void LogSink(uint8 Protocol, uint32 SequenceId, const ANSICHAR* SinkName, const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertTrace`)
- L30 _macro_ `#define INTERNAL_CONCERT_TRACE_INIT(InEndpointIdTOptional, InEndpointDisplayFString, InIsServer) UE::ConcertTrace::Init(InEndpointIdTOptional, InEndpointDisplayFString, InIsServer);`
- L32 _macro_ `#define INTERNAL_CONCERT_TRACE_OBJECT_SCOPE(InEventName, InObjectPath, InSequenceId, InProtocolId) UE::ConcertTrace::FConcertScopedObjectTrace UE_JOIN(TheScope, __LINE__)(InProtocolId, InSequenceId, #InEventName, InObjectPath);`
- L34 _macro_ `#define INTERNAL_CONCERT_TRACE_OBJECT_TRANSMISSION_START(InDestinationEndpointId, InObjectPath, InSequenceId, InProtocolId) UE::ConcertTrace::LogTransmissionStart(InProtocolId, InSequenceId, InObjectPath, InDestinationEndpointId);`
- L35 _macro_ `#define INTERNAL_CONCERT_TRACE_OBJECT_TRANSMISSION_RECEIVE(InObjectPath, InSequenceId, InProtocolId) UE::ConcertTrace::LogTransmissionReceive(InProtocolId, InSequenceId, InObjectPath);`
- L36 _macro_ `#define INTERNAL_CONCERT_TRACE_OBJECT_SINK(InSinkName, InObjectPath, InSequenceId, InProtocolId) UE::ConcertTrace::LogSink(InProtocolId, InSequenceId, #InSinkName, InObjectPath);`

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Trace/Private/ConcertReplicationSequenceContext.h` (Public)


#### struct `UE::ConcertTrace::Private::FConcertReplicationSequenceContext`  
`struct FConcertReplicationSequenceContext`  
_L10-16_
- L12 _public member_ `FSoftObjectPath Object;`
- L13 _public member_ `int32 FrameNumber;`
- L15 _public function_ `FString ToString() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertTrace` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::ConcertTrace`)

### `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/Trace/Private/ConcertScopedObjectTrace.h` (Public)


#### class `UE::ConcertTrace::FConcertScopedObjectTrace`  
`class FConcertScopedObjectTrace : public FNoncopyable`  
_L15-28_
- inherits: `FNoncopyable`
- L17 _private member_ `const bool bShouldTrace;`
- L19 _private member_ `const uint8 Protocol;`
- L20 _private member_ `const uint32 SequenceId;`
- L21 _private member_ `const ANSICHAR* EventName;`
- L22 _private member_ `const FSoftObjectPath ObjectPath;`
- L26 _public prototype_ `FConcertScopedObjectTrace(uint8 InProtocol, uint32 InSequenceId, const ANSICHAR* InEventName, FSoftObjectPath InObjectPath);`
- L27 _public prototype_ `~FConcertScopedObjectTrace();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertTrace` (scope `UE`)
