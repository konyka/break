# Runtime / Messaging

- module root: `Source/Runtime/Messaging`
- headers: 27; symbols: 513
- symbol kinds: class=27, delegate=12, enum=5, enumerator=16, function=60, macro=4, member=129, prototype=243, struct=12, typedef=5
- PublicDependencyModuleNames: Core, CoreUObject, TraceLog

### `Source/Runtime/Messaging/Private/Bridge/MessageAddressBook.h` (Private)


#### class `FMessageAddressBook`  
`class FMessageAddressBook`  
_L13-143_
- desc: Implements an address book that maps message addresses to remote nodes.
- L18 _public function_ `FMessageAddressBook()` — Default constructor.
- L24 _public function_ `~FMessageAddressBook()` — Destructor.
- L37 _public function_ `void Add(const FMessageAddress& Address, const FGuid& NodeId)` — Adds an address to the address book. @Address The message address to add. @NodeId The identifier of the remote node that handles the message address.
- L45 _public function_ `void Clear()` — Clears the address book.
- L58 _public function_ `bool Contains(const FMessageAddress& Address)` — Checks whether this address book contains the given address. @param Address The address to check. @return true if the address is known, false otherwise.
- L71 _public function_ `TArray<FGuid> GetNodesFor(const TArray<FMessageAddress>& Addresses)` — Gets the remote node identifiers for the specified list of message addresses. @param Addresses The address list to retrieve the node identifiers for. @return The list of node identifiers.
- L99 _public function_ `void RemoveAll(TArray<FMessageAddress>& OutRemovedAddresses)` — Removes all known message addresses. To remove only the addresses for a specific remote node, use RemoveNode(). If you are not interested in the removed addresses, use Clear() instead. @param OutRemovedRecipients Will hold a list of recipients that were removed. @see Clear, RemoveNode
- L116 _public function_ `void RemoveNode(const FGuid& NodeId, TArray<FMessageAddress>& OutRemovedAddresses)` — Removes all known message addresses for the specified remote node identifier. @param NodeId The identifier of the remote node to remove. @param OutRemovedRecipients Will hold a list of recipients that were removed. @see Clear, RemoveAllNodes
- L139 _private member_ `FCriticalSection* CriticalSection;` — Holds a critical section to serialize access to the address book entries.
- L142 _private member_ `TMap<FMessageAddress, FGuid> Entries;` — Holds the collection of known addresses and their remote node identifiers.

### `Source/Runtime/Messaging/Private/Bridge/MessageBridge.h` (Private)


#### class `FMessageBridge`  
`class FMessageBridge : public TSharedFromThis<FMessageBridge, ESPMode::ThreadSafe> , public IMessageBridge , public IMessageReceiver , public IMessageSender , protected IMessageTransportHandler`  
_L34-119_
- inherits: `TSharedFromThis<FMessageBridge,ESPMode::ThreadSafe>,IMessageBridge,IMessageReceiver,IMessageSender,IMessageTransportHandler`
- desc: Implements a message bridge. A message bridge is a special message endpoint that connects multiple message buses running in different processes or on different devices. This allows messages that are available in one system to also be available on other systems. Message bridges use an underlying transport layer to channel the messages between two or more systems. Such layers may utilize system specific technologies, such as network sockets or shared memory to communicate with remote bridges. The bridge acts as a map from message addresses to remote nodes and vice versa. @see IMessageBus, IMessageTransport
- L50 _public prototype_ `FMessageBridge( const FMessageAddress InAddress, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InBus, const TSharedRef<IMessageTransport, ESPMode::ThreadSafe>& InTransport );` — Creates and initializes a new instance. @param InAddress The message address for this bridge. @param InBus The message bus that this node is connected to. @param InTransport The transport mechanism to use.
- L57 _public prototype_ `virtual ~FMessageBridge();` — Virtual destructor.
- L63 _public prototype_ `virtual void Disable() override;`
- L64 _public prototype_ `virtual void Enable() override;`
- L65 _public prototype_ `virtual bool IsEnabled() const override;`
- L66 _public prototype_ `virtual FGuid LookupAddress(const FMessageAddress& InAddress) override;`
- L67 _public prototype_ `virtual bool IsSubscribed(const FTopLevelAssetPath& MessageType) const override;`
- L71 _public prototype_ `virtual FName GetDebugName() const override;`
- L72 _public prototype_ `virtual const FGuid& GetRecipientId() const override;`
- L73 _public prototype_ `virtual ENamedThreads::Type GetRecipientThread() const override;`
- L74 _public prototype_ `virtual bool IsLocal() const override;`
- L75 _public prototype_ `virtual void ReceiveMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) override;`
- L81 _public prototype_ `virtual FMessageAddress GetSenderAddress() override;`
- L82 _public prototype_ `virtual void NotifyMessageError(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FString& Error) override;`
- L88 _protected prototype_ `virtual void DiscoverTransportNode(const FGuid& NodeId) override;`
- L89 _protected prototype_ `virtual void ForgetTransportNode(const FGuid& NodeId) override;`
- L90 _protected prototype_ `virtual void ReceiveTransportMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FGuid& NodeId) override;`
- L95 _private prototype_ `void HandleMessageBusShutdown();` — Callback for message bus shutdowns.
- L100 _private member_ `FMessageAddress Address;` — Holds the bridge's address.
- L103 _private member_ `FMessageAddressBook AddressBook;` — Holds the address book.
- L106 _private member_ `TSharedPtr<IMessageBus, ESPMode::ThreadSafe> Bus;` — Holds a reference to the bus that this bridge is attached to.
- L109 _private member_ `bool Enabled;` — Hold a flag indicating whether this endpoint is active.
- L112 _private member_ `const FGuid Id;` — Holds the bridge's unique identifier (for debugging purposes).
- L115 _private member_ `TSharedPtr<IMessageSubscription, ESPMode::ThreadSafe> MessageSubscription;` — Holds the message subscription for outbound messages.
- L118 _private member_ `TSharedPtr<IMessageTransport, ESPMode::ThreadSafe> Transport;` — Holds the message transport object.

### `Source/Runtime/Messaging/Private/Bus/MessageBus.h` (Private)


#### class `FMessageBus`  
`class FMessageBus : public TSharedFromThis<FMessageBus, ESPMode::ThreadSafe> , public IMessageBus`  
_L21-74_
- inherits: `TSharedFromThis<FMessageBus,ESPMode::ThreadSafe>,IMessageBus`
- desc: Implements a message bus.
- L33 _public prototype_ `FMessageBus(FString InName, const TSharedPtr<IAuthorizeMessageRecipients>& InRecipientAuthorizer);` — Creates and initializes a new instance. @param InDebugName The debug name of this message bus. @param InRecipientAuthorizer An optional recipient authorizer.
- L36 _public prototype_ `virtual ~FMessageBus();` — Virtual destructor.
- L42 _public prototype_ `virtual void Forward(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TArray<FMessageAddress>& Recipients, const FTimespan& Delay, const TSharedRef<IMessageSender, ESPMode::ThreadSafe>& Forwarder) override;`
- L43 _public prototype_ `virtual TSharedRef<IMessageTracer, ESPMode::ThreadSafe> GetTracer() override;`
- L44 _public prototype_ `virtual void Intercept(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType) override;`
- L45 _public prototype_ `virtual FOnMessageBusShutdown& OnShutdown() override;`
- L46 _public prototype_ `virtual void Publish(void* Message, UScriptStruct* TypeInfo, EMessageScope Scope, const TMap<FName, FString>& Annotations, const FTimespan& Delay, const FDateTime& Expiration, const TSharedRef<IMessageSender, ESPMode::ThreadSafe>& Publisher) override;`
- L47 _public prototype_ `virtual void Register(const FMessageAddress& Address, const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient) override;`
- L48 _public prototype_ `virtual void Send(void* Message, UScriptStruct* TypeInfo, EMessageFlags Flags, const TMap<FName, FString>& Annotations, const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& Attachment, const TArray<FMessageAddress>& Recipients, const FTimespan& Delay, const FDateTime& Expiration, const TSharedRef<IMessageSender, ESPMode::ThreadSafe>& Sender) override;`
- L49 _public prototype_ `virtual void Shutdown() override;`
- L50 _public prototype_ `virtual TSharedPtr<IMessageSubscription, ESPMode::ThreadSafe> Subscribe(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& MessageType, const FMessageScopeRange& ScopeRange) override;`
- L51 _public prototype_ `virtual void Unintercept(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType) override;`
- L52 _public prototype_ `virtual void Unregister(const FMessageAddress& Address) override;`
- L53 _public prototype_ `virtual void Unsubscribe(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& MessageType) override;`
- L55 _public prototype_ `virtual void AddNotificationListener(const TSharedRef<IBusListener, ESPMode::ThreadSafe>& Listener) override;`
- L56 _public prototype_ `virtual void RemoveNotificationListener(const TSharedRef<IBusListener, ESPMode::ThreadSafe>& Listener) override;`
- L57 _public prototype_ `virtual const FString& GetName() const override;`
- L61 _private member_ `const FString Name;` — The message bus debugging name.
- L64 _private member_ `FMessageRouter* Router;` — Holds the message router.
- L67 _private member_ `FRunnableThread* RouterThread;` — Holds the message router thread.
- L70 _private member_ `TSharedPtr<IAuthorizeMessageRecipients> RecipientAuthorizer;` — Holds the recipient authorizer.
- L73 _private member_ `FOnMessageBusShutdown ShutdownDelegate;` — Holds bus shutdown delegate.

### `Source/Runtime/Messaging/Private/Bus/MessageContext.h` (Private)


#### class `FMessageContext`  
`class FMessageContext : public IMessageContext`  
_L16-159_
- inherits: `IMessageContext`
- L22 _public function_ `FMessageContext() : Message(nullptr) , TypeInfo(nullptr)` — Default constructor.
- L44 _public function_ `FMessageContext( void* InMessage, UScriptStruct* InTypeInfo, const TMap<FName, FString>& InAnnotations, const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& InAttachment, const FMessageAddress& InSender, const TArray<FMessageAddress>& InRecipients, EMessageScope InScope, EMessageFlags InFlags, const FDateTime& InTimeSent, const FDateTime& InExpiration, ENamedThreads::Type InSenderThread ) : Annotations(InAnnotations) , Attachment(InAttachment) , Expiration(InExpiration) , Message(InMessage) , Recipients(InRecipients) , Scope(InScope) , Flags(InFlags) , Sender(InSender) , SenderThread(InSenderThread) , TimeSent(InTimeSent) , TypeInfo(InTypeInfo)` — Creates and initializes a new message context. This constructor overload is used for published and sent messages. @param InMessage The message payload. @param InTypeInfo The message's type information. @param InAnnotation The message header to attach to the message. @param InAttachment The binary data to attach to the message. @param InSender The sender's address. @param InRecipients The message recipients. @param InScope The message scope. @param InFlags The message flags. @param InTimeSent The time at which the message was sent. @param InExpiration The message's expiration time. @param InSenderThread The name of the thread from which the message was sent.
- L82 _public function_ `FMessageContext( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext, const FMessageAddress& InForwarder, const TArray<FMessageAddress>& NewRecipients, EMessageScope NewScope, const FDateTime& InTimeForwarded, ENamedThreads::Type InForwarderThread ) : Message(nullptr) , OriginalContext(InContext) , Recipients(NewRecipients) , Scope(NewScope) , Flags(EMessageFlags::None) , Sender(InForwarder) , SenderThread(InForwarderThread) , TimeSent(InTimeForwarded)` — Creates and initializes a new message context from an existing context. This constructor overload is used for forwarded messages. @param InContext The existing context. @param InForwarder The forwarder's address. @param NewRecipients The recipients of the new context. @param NewScope The message's new scope. @param InTimeForwarded The time at which the message was forwarded. @param InForwarderThread The name of the thread from which the message was forwarded.
- L107 _public prototype_ `virtual const TMap<FName, FString>& GetAnnotations() const override;`
- L108 _public prototype_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override;`
- L109 _public prototype_ `virtual const FDateTime& GetExpiration() const override;`
- L110 _public prototype_ `virtual const void* GetMessage() const override;`
- L111 _public prototype_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override;`
- L112 _public prototype_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override;`
- L113 _public prototype_ `virtual const TArray<FMessageAddress>& GetRecipients() const override;`
- L114 _public prototype_ `virtual EMessageScope GetScope() const override;`
- L115 _public prototype_ `virtual EMessageFlags GetFlags() const override;`
- L116 _public prototype_ `virtual const FMessageAddress& GetSender() const override;`
- L117 _public prototype_ `virtual const FMessageAddress& GetForwarder() const override;`
- L118 _public prototype_ `virtual ENamedThreads::Type GetSenderThread() const override;`
- L119 _public prototype_ `virtual const FDateTime& GetTimeForwarded() const override;`
- L120 _public prototype_ `virtual const FDateTime& GetTimeSent() const override;`
- L125 _private member_ `TMap<FName, FString> Annotations;` — Holds the optional message annotations.
- L128 _private member_ `TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> Attachment;` — Holds a pointer to attached binary data.
- L131 _private member_ `FDateTime Expiration;` — Holds the expiration time.
- L134 _private member_ `void* Message;` — Holds the message.
- L137 _private member_ `TSharedPtr<IMessageContext, ESPMode::ThreadSafe> OriginalContext;` — Holds the original message context.
- L140 _private member_ `TArray<FMessageAddress> Recipients;` — Holds the message recipients.
- L143 _private member_ `EMessageScope Scope;` — Holds the message's scope.
- L146 _private member_ `EMessageFlags Flags;` — Holds the message's scope.
- L149 _private member_ `FMessageAddress Sender;` — Holds the sender's identifier.
- L152 _private member_ `ENamedThreads::Type SenderThread;` — Holds the name of the thread from which the message was sent.
- L155 _private member_ `FDateTime TimeSent;` — Holds the time at which the message was sent.
- L158 _private member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;` — Holds the message's type information.

### `Source/Runtime/Messaging/Private/Bus/MessageDispatchTask.h` (Private)


#### class `FMessageDispatchTask`  
`class FMessageDispatchTask`  
_L16-84_
- desc: Implements an asynchronous task for dispatching a message to a recipient.
- L28 _public prototype_ `FMessageDispatchTask( ENamedThreads::Type InThread, TSharedRef<IMessageContext, ESPMode::ThreadSafe> InContext, TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe> InRecipient, TSharedPtr<FMessageTracer, ESPMode::ThreadSafe> InTracer);` — Creates and initializes a new instance. @param InThread The name of the thread to dispatch the message on. @param InContext The context of the message to dispatch. @param InRecipient The message recipient. @param InTracer The message tracer to notify.
- L42 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);` — Performs the actual task. @param CurrentThread The thread that this task is executing on. @param MyCompletionGraphEvent The completion event.
- L49 _public function_ `ENamedThreads::Type GetDesiredThread()` — Returns the name of the thread that this task should run on. @return Thread name.
- L59 _public prototype_ `TStatId GetStatId() const;` — Gets the task's stats tracking identifier. @return Stats identifier.
- L66 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()` — Gets the mode for tracking subsequent tasks. @return Always track subsequent tasks.
- L74 _private member_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> Context;` — Holds the message context.
- L77 _private member_ `TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe> RecipientPtr;` — Holds a reference to the recipient.
- L80 _private member_ `ENamedThreads::Type Thread;` — Holds the name of the thread that the router is running on.
- L83 _private member_ `TWeakPtr<FMessageTracer, ESPMode::ThreadSafe> TracerPtr;` — Holds a pointer to the message tracer.

#### class `FBusNotificationDispatchTask`  
`class FBusNotificationDispatchTask`  
_L90-152_
- desc: Implements an asynchronous task for dispatching a registration notification to a listener.
- L102 _public function_ `FBusNotificationDispatchTask( ENamedThreads::Type InThread, TWeakPtr<IBusListener, ESPMode::ThreadSafe> InListener, FMessageAddress InAddress, EMessageBusNotification InNotification) : Thread(InThread) , ListenerPtr(InListener) , Address(InAddress) , Notification(InNotification)` — Creates and initializes a new instance. @param InThread The name of the thread to dispatch the message on. @param InListener The listener to notify. @param InAddress The address we are notifying about. @param InNotification The notification type being notified.
- L121 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);` — Performs the actual task. @param CurrentThread The thread that this task is executing on. @param MyCompletionGraphEvent The completion event.
- L128 _public function_ `ENamedThreads::Type GetDesiredThread()` — Returns the name of the thread that this task should run on. @return Thread name.
- L133 _public prototype_ `TStatId GetStatId() const;`
- L135 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L142 _private member_ `ENamedThreads::Type Thread;` — Holds the name of the thread that the router is running on.
- L145 _private member_ `TWeakPtr<IBusListener, ESPMode::ThreadSafe> ListenerPtr;` — Holds a reference to the recipient.
- L148 _private member_ `FMessageAddress Address;` — Holds the address we are notifying about.
- L151 _private member_ `EMessageBusNotification Notification;` — Holds the notification type we are notifying about.

### `Source/Runtime/Messaging/Private/Bus/MessageRouter.h` (Private)


#### class `FMessageRouter`  
`class FMessageRouter : public FRunnable , private FSingleThreadRunnable`  
_L26-333_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Implements a topic-based message router.
- L35 _public prototype_ `FMessageRouter();` — Default constructor.
- L38 _public prototype_ `~FMessageRouter();` — Destructor.
- L48 _public function_ `FORCEINLINE void AddInterceptor(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType)` — Adds a message interceptor. @param Interceptor The interceptor to add. @param MessageType The type of messages to intercept.
- L59 _public function_ `FORCEINLINE void AddRecipient(const FMessageAddress& Address, const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient)` — Adds a recipient. @param Address The address of the recipient to add. @param Recipient The recipient.
- L69 _public function_ `FORCEINLINE void AddSubscription(const TSharedRef<IMessageSubscription, ESPMode::ThreadSafe>& Subscription)` — Adds a subscription. @param Subscription The subscription to add.
- L79 _public function_ `FORCEINLINE TSharedRef<IMessageTracer, ESPMode::ThreadSafe> GetTracer()` — Gets the message tracer. @return Weak pointer to the message tracer.
- L90 _public function_ `FORCEINLINE void RemoveInterceptor(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType)` — Removes a message interceptor. @param Interceptor The interceptor to remove. @param MessageType The type of messages to stop intercepting.
- L100 _public function_ `FORCEINLINE void RemoveRecipient(const FMessageAddress& Address)` — Removes a recipient. @param Address The address of the recipient to remove.
- L111 _public function_ `FORCEINLINE void RemoveSubscription(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& MessageType)` — Removes a subscription. @param Subscriber The subscriber to stop routing messages to. @param MessageType The type of message to unsubscribe from (NAME_None = all types).
- L121 _public function_ `FORCEINLINE void RouteMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)` — Routes a message to the specified recipients. @param Context The context of the message to route.
- L132 _public function_ `FORCEINLINE void AddNotificationListener(const TSharedRef<IBusListener, ESPMode::ThreadSafe>& Listener)` — Add a listener to the bus registration events @param Listener The listener to as to the registration notifications
- L142 _public function_ `FORCEINLINE void RemoveNotificationListener(const TSharedRef<IBusListener, ESPMode::ThreadSafe>& Listener)` — Remove a listener to the bus registration events @param Listener The listener to remove from the registration notifications
- L151 _public prototype_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L152 _public prototype_ `virtual bool Init() override;`
- L153 _public prototype_ `virtual uint32 Run() override;`
- L154 _public prototype_ `virtual void Stop() override;`
- L155 _public prototype_ `virtual void Exit() override;`
- L164 _protected prototype_ `FTimespan CalculateWaitTime();` — Calculates the time that the thread will wait for new work. @return Wait time.
- L172 _protected function_ `FORCEINLINE bool EnqueueCommand(CommandDelegate Command)` — Queues up a router command. @param Command The command to queue up. @return true if the command was enqueued, false otherwise.
- L187 _protected prototype_ `void FilterSubscriptions( TArray<TSharedPtr<IMessageSubscription, ESPMode::ThreadSafe>>& Subscriptions, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, TArray<TSharedPtr<IMessageReceiver, ESPMode::ThreadSafe>>& OutRecipients);` — Filters a collection of subscriptions using the given message context. @param Subscriptions The subscriptions to filter. @param Context The message context to filter by. @param OutRecipients Will hold the collection of recipients.
- L198 _protected prototype_ `void FilterRecipients( const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, TArray<TSharedPtr<IMessageReceiver, ESPMode::ThreadSafe>>& OutRecipients);` — Filters recipients from the given message context to gather actual recipients. @param Context The message context to filter by. @param OutRecipients Will hold the collection of recipients.
- L207 _protected prototype_ `void DispatchMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Message);` — Dispatches a single message to its recipients. @param Message The message to dispatch.
- L214 _protected prototype_ `void ProcessCommands();` — Process all queued commands. @see ProcessDelayedMessages
- L221 _protected prototype_ `void ProcessDelayedMessages();` — Processes all delayed messages. @see ProcessCommands
- L227 _protected prototype_ `virtual void Tick() override;`
- L267 _private prototype_ `void HandleAddInterceptor(TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe> Interceptor, FTopLevelAssetPath MessageType);` — Handles adding message interceptors.
- L270 _private prototype_ `void HandleAddRecipient(FMessageAddress Address, TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe> RecipientPtr);` — Handles adding message recipients.
- L273 _private prototype_ `void HandleAddSubscriber(TSharedRef<IMessageSubscription, ESPMode::ThreadSafe> Subscription);` — Handles adding of subscriptions.
- L276 _private prototype_ `void HandleRemoveInterceptor(TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe> Interceptor, FTopLevelAssetPath MessageType);` — Handles the removal of message interceptors.
- L279 _private prototype_ `void HandleRemoveRecipient(FMessageAddress Address);` — Handles the removal of message recipients.
- L282 _private prototype_ `void HandleRemoveSubscriber(TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe> SubscriberPtr, FTopLevelAssetPath MessageType);` — Handles the removal of subscribers.
- L285 _private prototype_ `void HandleRouteMessage(TSharedRef<IMessageContext, ESPMode::ThreadSafe> Context);` — Handles the routing of messages.
- L288 _private prototype_ `void HandleAddListener(TWeakPtr<IBusListener, ESPMode::ThreadSafe> ListenerPtr);` — Handles the addition of a listener.
- L291 _private prototype_ `void HandleRemoveListener(TWeakPtr<IBusListener, ESPMode::ThreadSafe> ListenerPtr);` — Handles the removal of a listener.
- L294 _private prototype_ `void NotifyRegistration(const FMessageAddress& Address, EMessageBusNotification Notification);` — Notify listeners about registration
- L299 _private member_ `TMap<FTopLevelAssetPath, TArray<TSharedPtr<IMessageInterceptor, ESPMode::ThreadSafe>>> ActiveInterceptors;` — Maps message types to interceptors.
- L302 _private member_ `TMap<FMessageAddress, TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe>> ActiveRecipients;` — Maps message addresses to recipients.
- L305 _private member_ `TMap<FTopLevelAssetPath, TArray<TSharedPtr<IMessageSubscription, ESPMode::ThreadSafe>>> ActiveSubscriptions;` — Maps message types to subscriptions.
- L308 _private member_ `TArray<TWeakPtr<IBusListener, ESPMode::ThreadSafe>> ActiveRegistrationListeners;` — Array of active registration listeners.
- L311 _private member_ `TMpscQueue<CommandDelegate> Commands;` — Holds the router command queue.
- L314 _private member_ `FDateTime CurrentTime;` — Holds the current time.
- L317 _private member_ `TArray<FDelayedMessage> DelayedMessages;` — Holds the collection of delayed messages.
- L320 _private member_ `int64 DelayedMessagesSequence;` — Holds a sequence number for delayed messages.
- L323 _private member_ `TAtomic<bool> Stopping;` — Holds a flag indicating that the thread is stopping.
- L326 _private member_ `TSharedRef<FMessageTracer, ESPMode::ThreadSafe> Tracer;` — Holds the message tracer.
- L329 _private member_ `FEvent* WorkEvent;` — Holds an event signaling that work is available.
- L332 _private member_ `bool bAllowDelayedMessaging;` — Whether or not to allow delayed messaging

#### struct `FMessageRouter::FDelayedMessage`  
`struct FDelayedMessage`  
_L232-262_
- desc: Structure for delayed messages.
- L235 _public member_ `TSharedPtr<IMessageContext, ESPMode::ThreadSafe> Context;` — Holds the context of the delayed message.
- L238 _public member_ `int64 Sequence;` — Holds a sequence number used by the delayed message queue.
- L242 _public function_ `FDelayedMessage()` — Default constructor.
- L245 _public function_ `FDelayedMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext, int64 InSequence) : Context(InContext) , Sequence(InSequence)` — Creates and initializes a new instance.
- L251 _public function_ `bool operator<(const FDelayedMessage& Other) const` — Comparison operator for heap sorting.

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE(CommandDelegate) public: FMessageRouter();`

### `Source/Runtime/Messaging/Private/Bus/MessageSubscription.h` (Private)


#### class `FMessageSubscription`  
`class FMessageSubscription : public IMessageSubscription`  
_L18-85_
- inherits: `IMessageSubscription`
- desc: Implements a message subscription. Message subscriptions are used by the message router to determine where to dispatch published messages to. Message subscriptions are created per message type.
- L31 _public function_ `FMessageSubscription(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& InSubscriber, const FTopLevelAssetPath& InMessageType, const FMessageScopeRange& InScopeRange) : Enabled(true) , MessageType(InMessageType) , ScopeRange(InScopeRange) , Subscriber(InSubscriber)` — Creates and initializes a new instance. @param InSubscriber The message subscriber. @param InMessageType The type of messages to subscribe to. @param InReceivingThread The thread on which to receive messages on. @param InScopeRange The message scope range to subscribe to.
- L42 _public function_ `virtual void Disable() override`
- L47 _public function_ `virtual void Enable() override`
- L52 _public function_ `virtual FTopLevelAssetPath GetMessageTypePathName() override`
- L57 _public function_ `virtual const FMessageScopeRange& GetScopeRange() override`
- L62 _public function_ `virtual const TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe>& GetSubscriber() override`
- L67 _public function_ `virtual bool IsEnabled() override`
- L75 _private member_ `bool Enabled;` — Holds a flag indicating whether this subscription is enabled.
- L78 _private member_ `FTopLevelAssetPath MessageType;` — Holds the type of subscribed messages.
- L81 _private member_ `FMessageScopeRange ScopeRange;` — Holds the range of message scopes to subscribe to.
- L84 _private member_ `TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe> Subscriber;` — Holds the subscriber.

### `Source/Runtime/Messaging/Private/Bus/MessageTracer.h` (Private)


#### class `FMessageTracer`  
`class FMessageTracer : public IMessageTracer`  
_L20-214_
- inherits: `IMessageTracer`
- desc: Implements a message bus tracers.
- L26 _public prototype_ `FMessageTracer();` — Default constructor.
- L29 _public prototype_ `virtual ~FMessageTracer();` — Virtual destructor.
- L39 _public prototype_ `void TraceAddedInterceptor(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType);` — Notifies the tracer that a message interceptor has been added to the message bus. @param Interceptor The added interceptor. @param MessageType The type of messages being intercepted.
- L47 _public prototype_ `void TraceAddedRecipient(const FMessageAddress& Address, const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient);` — Notifies the tracer that a message recipient has been added to the message bus. @param Address The address of the added recipient. @param Recipient The added recipient.
- L54 _public prototype_ `void TraceAddedSubscription(const TSharedRef<IMessageSubscription, ESPMode::ThreadSafe>& Subscription);` — Notifies the tracer that a message subscription has been added to the message bus. @param Subscription The added subscription.
- L63 _public prototype_ `void TraceDispatchedMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient, bool Async);` — Notifies the tracer that a message has been dispatched. @param Context The context of the dispatched message. @param Recipient The message recipient. @param Async Whether the message was dispatched asynchronously.
- L71 _public prototype_ `void TraceHandledMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient);` — Notifies the tracer that a message has been handled. @param Context The context of the dispatched message. @param Recipient The message recipient that handled the message.
- L79 _public prototype_ `void TraceInterceptedMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor);` — Notifies the tracer that a message has been intercepted. @param Context The context of the intercepted message. @param Interceptor The interceptor.
- L87 _public prototype_ `void TraceRemovedInterceptor(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType);` — Notifies the tracer that a message interceptor has been removed from the message bus. @param Interceptor The removed interceptor. @param MessageType The type of messages that is no longer being intercepted.
- L94 _public prototype_ `void TraceRemovedRecipient(const FMessageAddress& Address);` — Notifies the tracer that a recipient has been removed from the message bus. @param Address The address of the removed recipient.
- L102 _public prototype_ `void TraceRemovedSubscription(const TSharedRef<IMessageSubscription, ESPMode::ThreadSafe>& Subscription, const FTopLevelAssetPath& MessageType);` — Notifies the tracer that a message subscription has been removed from the message bus. @param Subscriber The removed subscriber. @param MessageType The type of messages no longer being subscribed to.
- L109 _public prototype_ `void TraceRoutedMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Notifies the tracer that a message has been routed. @param Context The context of the routed message.
- L116 _public prototype_ `void TraceSentMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Notifies the tracer that a message has been sent. @param Context The context of the sent message.
- L122 _public prototype_ `virtual void Break() override;`
- L123 _public prototype_ `virtual void Continue() override;`
- L124 _public prototype_ `virtual int32 GetEndpoints(TArray<TSharedPtr<FMessageTracerEndpointInfo>>& OutEndpoints) const override;`
- L125 _public prototype_ `virtual int32 GetMessages(TArray<TSharedPtr<FMessageTracerMessageInfo>>& OutMessages) const override;`
- L126 _public prototype_ `virtual int32 GetMessageTypes(TArray<TSharedPtr<FMessageTracerTypeInfo>>& OutTypes) const override;`
- L127 _public prototype_ `virtual bool HasMessages() const override;`
- L128 _public prototype_ `virtual bool IsBreaking() const override;`
- L129 _public prototype_ `virtual bool IsRunning() const override;`
- L131 _public function_ `DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnMessageAdded, FOnMessageAdded) virtual FOnMessageAdded& OnMessageAdded() override`
- L137 _public function_ `DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnMessagesReset, FOnMessagesReset) virtual FOnMessagesReset& OnMessagesReset() override`
- L143 _public function_ `DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnTypeAdded, FOnTypeAdded) virtual FOnTypeAdded& OnTypeAdded() override`
- L149 _public prototype_ `virtual void Reset() override;`
- L150 _public prototype_ `virtual void Step() override;`
- L151 _public prototype_ `virtual void Stop();`
- L152 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L157 _protected prototype_ `void ResetMessages();` — Resets traced messages.
- L164 _protected prototype_ `bool ShouldBreak(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) const;` — Checks whether the tracer should break on the given message. @param Context The context of the message to consider for breaking.
- L169 _private member_ `TMap<FMessageAddress, TSharedPtr<FMessageTracerEndpointInfo>> AddressesToEndpointInfos;` — Holds the collection of endpoints for known message addresses.
- L172 _private member_ `bool Breaking;` — Holds a flag indicating whether a breakpoint was hit.
- L175 _private member_ `TArray<TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe>> Breakpoints;` — Holds the collection of breakpoints.
- L178 _private member_ `FEvent* ContinueEvent;` — Holds an event signaling that messaging routing can continue.
- L181 _private member_ `TMap<FGuid, TSharedPtr<FMessageTracerInterceptorInfo>> Interceptors;` — The collection of known interceptors.
- L184 _private member_ `TMap<FGuid, TSharedPtr<FMessageTracerEndpointInfo>> RecipientsToEndpointInfos;` — Holds the collection of endpoints for known recipient identifiers.
- L187 _private member_ `TMap<TSharedPtr<IMessageContext, ESPMode::ThreadSafe>, TSharedPtr<FMessageTracerMessageInfo>> MessageInfos;` — Holds the collection of known messages.
- L190 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<FMessageTracerTypeInfo>> MessageTypes;` — Holds the collection of known message types.
- L193 _private member_ `bool ResetPending;` — Holds a flag indicating whether a reset is pending.
- L196 _private member_ `bool Running;` — Holds a flag indicating whether the tracer is running.
- L199 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Handle to the registered TickDelegate.
- L202 _private member_ `TQueue<TFunction<void()>, EQueueMode::Mpsc> Traces;` — Holds the trace actions queue.
- L207 _private member_ `FOnMessageAdded MessagesAddedDelegate;` — Holds a delegate that is executed when a new message has been added to the collection of known messages.
- L210 _private member_ `FOnMessagesReset MessagesResetDelegate;` — Holds a delegate that is executed when the message history has been reset.
- L213 _private member_ `FOnTypeAdded TypeAddedDelegate;` — Holds a delegate that is executed when a new type has been added to the collection of known message types.

#### Free symbols / members of external scopes

- L131 _delegate_ `DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnMessageAdded, FOnMessageAdded) virtual FOnMessageAdded& OnMessageAdded() override { return MessagesAddedDelegate; } DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnMessagesReset, FOnMessagesReset) virtual FOnMessagesReset& OnMessagesReset() override { return MessagesResetDelegate; } DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnTypeAdded, FOnTypeAdded) virtual FOnTypeAdded& OnTypeAdded() override { return TypeAddedDelegate; } virtual void Reset() override;`
- L137 _delegate_ `DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnMessagesReset, FOnMessagesReset) virtual FOnMessagesReset& OnMessagesReset() override { return MessagesResetDelegate; } DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnTypeAdded, FOnTypeAdded) virtual FOnTypeAdded& OnTypeAdded() override { return TypeAddedDelegate; } virtual void Reset() override;`
- L143 _delegate_ `DECLARE_DERIVED_EVENT(FMessageTracer, IMessageTracer::FOnTypeAdded, FOnTypeAdded) virtual FOnTypeAdded& OnTypeAdded() override { return TypeAddedDelegate; } virtual void Reset() override;`

### `Source/Runtime/Messaging/Public/IAuthorizeMessageRecipients.h` (Public)


#### class `IAuthorizeMessageRecipients`  
`class IAuthorizeMessageRecipients`  
_L19-110_
- desc: Interface for classes that authorize message subscriptions.
- L31 _public function_ `virtual bool AuthorizeInterceptor(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FName& MessageType)` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as MessageType.")` — Authorizes a request to intercept messages of the specified type. @param Interceptor The message interceptor to authorize. @param MessageType The type of messages to intercept. @return true if the request was authorized, false otherwise.
- L43 _public prototype_ `virtual bool AuthorizeInterceptor(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType) = 0;` — Authorizes a request to intercept messages of the specified type. @param Interceptor The message interceptor to authorize. @param MessageType The type of messages to intercept. @return true if the request was authorized, false otherwise.
- L52 _public prototype_ `virtual bool AuthorizeRegistration(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient, const FMessageAddress& Address) = 0;` — Authorizes a request to register the specified recipient. @param Recipient The recipient to register. @param Address The recipient's address. @return true if the request was authorized, false otherwise.
- L62 _public function_ `virtual bool AuthorizeSubscription(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FName& TopicPattern)` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as TopicPattern.")` — Authorizes a request to add a subscription for the specified topic pattern. @param Subscriber The subscriber. @param TopicPattern The message topic pattern to subscribe to. @return true if the request is authorized, false otherwise.
- L74 _public prototype_ `virtual bool AuthorizeSubscription(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& TopicPattern) = 0;` — Authorizes a request to add a subscription for the specified topic pattern. @param Subscriber The subscriber. @param TopicPattern The message topic pattern to subscribe to. @return true if the request is authorized, false otherwise.
- L82 _public prototype_ `virtual bool AuthorizeUnregistration(const FMessageAddress& Address) = 0;` — Authorizes a request to unregister the specified recipient. @param Address The address of the recipient to unregister. @return true if the request was authorized, false otherwise.
- L92 _public function_ `virtual bool AuthorizeUnsubscription(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FName& TopicPattern)` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as TopicPattern.")` — Authorizes a request to remove a subscription for the specified topic pattern. @param Subscriber The subscriber. @param TopicPattern The message topic pattern to unsubscribe from. @return true if the request is authorized, false otherwise.
- L104 _public prototype_ `virtual bool AuthorizeUnsubscription(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& TopicPattern) = 0;` — Authorizes a request to remove a subscription for the specified topic pattern. @param Subscriber The subscriber. @param TopicPattern The message topic pattern to unsubscribe from. @return true if the request is authorized, false otherwise.
- L109 _public prototype_ `virtual ~IAuthorizeMessageRecipients() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageAttachment.h` (Public)


#### class `IMessageAttachment`  
`class IMessageAttachment`  
_L23-40_
- desc: Interface for message attachments. Message attachments are optional bulk data objects that can be attached to a message, such as files or memory buffers. Transferring attachments within the same process is very efficient and amounts to copying a pointer to the data. On the other hand, sending message attachments to applications running in other processes or on other computers may - depending on their size - take a considerable amount of time, because they need to be serialized and transferred. For this reason, attachments are transferred separately from messages in such cases. NOTE: Message attachments are not fully implemented yet. In particular, transferring attachments over a network does not work yet. This API may change in the near future, so please use with care. @see IMessageContext
- L34 _public prototype_ `virtual FArchive* CreateReader() = 0;` — Creates an archive reader to the data. The caller is responsible for deleting the returned object. @return An archive reader.
- L39 _public prototype_ `virtual ~IMessageAttachment() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageBridge.h` (Public)


#### class `IMessageBridge`  
`class IMessageBridge`  
_L21-71_
- desc: Interface for message bridges. A message bridge connects a message bus with another messaging system. It is really just a regular message endpoint connected to a message bus that translates sent and received messages between the bus and some underlying transport technology. The transport technology is usually implemented in the form of a Message Transport Plug-in, such as the UdpMessaging plug-in that ships with Unreal Engine. The most common use case for message bridges is to connect two Unreal Engine message buses running in separate processes or en different computers. Another common use case is to connect an Unreal Engine message bus to an entirely different messaging system that is not based on Unreal Engine. Message bridge instances can be created with the IMessagingModule.CreateBridge method.
- L33 _public prototype_ `virtual void Disable() = 0;` — Disables this bridge. A disabled bridge will not receive any subscribed messages until it is enabled again. Bridges should be created in a disabled state by default and explicitly enabled. @see Enable, IsEnabled
- L43 _public prototype_ `virtual void Enable() = 0;` — Enables this bridge. An activated bridge will receive subscribed messages. Bridges should be created in a disabled state by default and explicitly enabled. @see Disable, IsEnabled
- L51 _public prototype_ `virtual bool IsEnabled() const = 0;` — Checks whether the bridge is currently enabled. @return true if the bridge is enabled, false otherwise. @see Disable, Enable
- L59 _public prototype_ `virtual FGuid LookupAddress(const FMessageAddress& InAddress) = 0;` — Provides the endpoint guid for the given address. @param MessageAddress to find remote endpoint guid. @return FGuid which may be invalid.
- L65 _public prototype_ `virtual bool IsSubscribed(const FTopLevelAssetPath& MessageType) const = 0;` — @param MessageType The type of message to check. @return True if the bridge is subscribed to the parameter MessageType.
- L70 _public prototype_ `virtual ~IMessageBridge() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageBus.h` (Public)


#### class `IMessageBus`  
`class IMessageBus`  
_L113-316_
- desc: Interface for message buses. A message bus is the main logical component to facilitate communication between (possibly distributed) parts of an application using Message Passing as its underlying architectural pattern. It allows registered sender and recipient objects, subsequently referred to as Message Endpoints, to exchange structured data in the form of user defined messages[1]. Depending on their usage, messages are classified into a number of types, such as commands, events and documents. In Unreal Engine, all these messages are modeled with regular built-in or user defined UStructs that may either be empty or contain data in the form of FProperty fields[2]. Before being dispatched, messages are internally wrapped into so called Message Context objects (IMessageContext) that contain additional information about a message, such as when it was sent and the sender and recipients. The sending and receiving of messages is not limited to message endpoints within the same thread or process, but may be extended to other applications running on the same computer or on other computers connected to a network with so called Message Transport Plug-ins, such as the UdpMessaging plug-in that ships with Unreal Engine. The main goal of a message bus is to hide the technical details of the underlying transport mechanisms, so that users can focus on implementing their distributed applications rather than worrying about how data gets from one endpoint to another. A message bus makes it loo
- L128 _public prototype_ `virtual void Forward(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TArray<FMessageAddress>& Recipients, const FTimespan& Delay, const TSharedRef<IMessageSender, ESPMode::ThreadSafe>& Forwarder) = 0;` — Forwards a previously received message. Messages can only be forwarded to endpoints within the same process. @param Context The context of the message to forward. @param Recipients The list of message recipients to forward the message to. @param Delay The deferral time. @param Forwarder The sender that forwards the message. @see Publish, Send
- L135 _public prototype_ `virtual TSharedRef<IMessageTracer, ESPMode::ThreadSafe> GetTracer() = 0;` — Gets the message bus tracer. @return Weak pointer to the tracer object.
- L145 _public prototype_ `virtual void Intercept(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FName& MessageType);` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as MessageType.")` — Adds an interceptor for messages of the specified type. @param Interceptor The interceptor. @param MessageType The type of messages to intercept. @see Unintercept
- L154 _public prototype_ `virtual void Intercept(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType) = 0;` — Adds an interceptor for messages of the specified type. @param Interceptor The interceptor. @param MessageType The type of messages to intercept. @see Unintercept
- L171 _public prototype_ `virtual void Publish(void* Message, UScriptStruct* TypeInfo, EMessageScope Scope, const TMap<FName, FString>& Annotations, const FTimespan& Delay, const FDateTime& Expiration, const TSharedRef<IMessageSender, ESPMode::ThreadSafe>& Publisher) = 0;` — Sends a message to subscribed recipients. The bus takes over ownership of the message's memory. It must NOT be freed by the caller. @param Message The message to publish. @param TypeInfo The message's type information. @param Scope The message scope. @param Annotations An optional message annotations header. @param Delay The delay after which to send the message. @param Expiration The time at which the message expires. @param Publisher The message publisher. @see Forward, Send
- L180 _public prototype_ `virtual void Register(const FMessageAddress& Address, const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Recipient) = 0;` — Registers a message recipient with the message bus. @param Address The address of the recipient to register. @param Recipient The message recipient. @see Unregister
- L199 _public prototype_ `virtual void Send(void* Message, UScriptStruct* TypeInfo, EMessageFlags Flags, const TMap<FName, FString>& Annotations, const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& Attachment, const TArray<FMessageAddress>& Recipients, const FTimespan& Delay, const FDateTime& Expiration, const TSharedRef<IMessageSender, ESPMode::ThreadSafe>& Sender) = 0;` — Sends a message to multiple recipients. The bus takes over ownership of the message's memory. It must NOT be freed by the caller. @param Message The message to send. @param TypeInfo The message's type information. @param Flags The message flags. @param Annotations An optional message annotations header. @param Attachment The binary data to attach to the message. @param Recipients The list of message recipients. @param Delay The delay after which to send the message. @param Expiration The time at which the message expires. @param Sender The message sender. @see Forward, Publish
- L206 _public prototype_ `virtual void Shutdown() = 0;` — Shuts down the message bus. @see OnShutdown
- L221 _public prototype_ `virtual TSharedPtr<IMessageSubscription, ESPMode::ThreadSafe> Subscribe(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FName& MessageType, const TRange<EMessageScope>& ScopeRange);` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as MessageType.")` — Adds a subscription for published messages of the specified type. Subscriptions allow message consumers to receive published messages from the message bus. The returned interface can be used to query the subscription's details and its enabled state. @param Subscriber The subscriber wishing to receive the messages. @param MessageType The type of messages to subscribe to (NAME_All = subscribe to all message types). @param ScopeRange The range of message scopes to include in the subscription. @return The added subscription, or nullptr if the subscription failed. @see Unsubscribe
- L235 _public prototype_ `virtual TSharedPtr<IMessageSubscription, ESPMode::ThreadSafe> Subscribe(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& MessageType, const TRange<EMessageScope>& ScopeRange) = 0;` — Adds a subscription for published messages of the specified type. Subscriptions allow message consumers to receive published messages from the message bus. The returned interface can be used to query the subscription's details and its enabled state. @param Subscriber The subscriber wishing to receive the messages. @param MessageType The type of messages to subscribe to (IMessageBus::PATHNAME_All = subscribe to all message types). @param ScopeRange The range of message scopes to include in the subscription. @return The added subscription, or nullptr if the subscription failed. @see Unsubscribe
- L245 _public prototype_ `virtual void Unintercept(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FName& MessageType);` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as MessageType.")` — Removes an interceptor for messages of the specified type. @param Interceptor The interceptor to remove. @param MessageType The type of messages to stop intercepting. @see Intercept
- L254 _public prototype_ `virtual void Unintercept(const TSharedRef<IMessageInterceptor, ESPMode::ThreadSafe>& Interceptor, const FTopLevelAssetPath& MessageType) = 0;` — Removes an interceptor for messages of the specified type. @param Interceptor The interceptor to remove. @param MessageType The type of messages to stop intercepting. @see Intercept
- L262 _public prototype_ `virtual void Unregister(const FMessageAddress& Address) = 0;` — Unregisters a message recipient from the message bus. @param Address The address of the recipient to unregister. @see Register
- L272 _public prototype_ `virtual void Unsubscribe(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FName& MessageType);` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as MessageType.")` — Cancels the specified message subscription. @param Subscriber The subscriber wishing to stop receiving the messages. @param MessageType The type of messages to unsubscribe from (NAME_All = all types). @see Subscribe
- L281 _public prototype_ `virtual void Unsubscribe(const TSharedRef<IMessageReceiver, ESPMode::ThreadSafe>& Subscriber, const FTopLevelAssetPath& MessageType) = 0;` — Cancels the specified message subscription. @param Subscriber The subscriber wishing to stop receiving the messages. @param MessageType The type of messages to unsubscribe from (IMessageBus::PATHNAME_All = all types). @see Subscribe
- L287 _public prototype_ `virtual void AddNotificationListener(const TSharedRef<IBusListener, ESPMode::ThreadSafe>& Listener) = 0;` — Add a listener to the bus notifications @param Listener The listener to as to the registration notifications
- L293 _public prototype_ `virtual void RemoveNotificationListener(const TSharedRef<IBusListener, ESPMode::ThreadSafe>& Listener) = 0;` — Remove a listener to the bus notifications @param Listener The listener to remove from the registration notifications
- L298 _public prototype_ `virtual const FString& GetName() const = 0;` — @return The name of this message bus.
- L308 _public prototype_ `virtual FOnMessageBusShutdown& OnShutdown() = 0;` — Returns a delegate that is executed when the message bus is shutting down. @return The delegate. @see Shutdown
- L310 _public member_ `static const FTopLevelAssetPath PATHNAME_All;`
- L315 _public prototype_ `virtual ~IMessageBus() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMessageBusShutdown);` — Delegate type for message bus shutdowns.
- L31 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMessageBusShutdown);` — Delegate type for message bus shutdowns.

### `Source/Runtime/Messaging/Public/IMessageBusListener.h` (Public)


#### enum `EMessageBusNotification`  
`enum class EMessageBusNotification : uint8`  
_L9-13_
- L11 _public enumerator_ `Registered = 0`
- L12 _public enumerator_ `Unregistered`

#### class `IBusListener`  
`class IBusListener`  
_L26-48_
- desc: Interface for message bus listener. Classes that implement this interface are able to receive notifications from a message bus. A bus listener will receive a call to its appropriate IBusListener.Notify* method for dispatched notifications it is listening to. This interface provides a rather low-level mechanism for listening to notification. Instead of implementing it, Most users will want to use an instance of see FMessageEndpoint, which provides a much more convenient way of listening to bus notifications. @see FMessageEndpoint, IMessageBus
- L29 _public prototype_ `virtual ~IBusListener() = default;`
- L38 _public prototype_ `virtual ENamedThreads::Type GetListenerThread() const = 0;` — Gets the name of the thread on which to receive notifications. If the listener's Notify[*] methods are thread-safe, return ThreadAny for best performance. @return Name of the listener thread.
- L47 _public prototype_ `virtual void NotifyRegistration(const FMessageAddress& Address, EMessageBusNotification Notification) = 0;` — Notify a registration event from the bus This is called when a receiver is registered or unregistered from the bus. @param Address The address of the recipient that just un/registered from the bus. @param Notification The even type, either `Registered` or `Unregistered`

### `Source/Runtime/Messaging/Public/IMessageContext.h` (Public)


#### struct `FMessageAddress`  
`struct FMessageAddress`  
_L25-148_
- desc: Structure for message endpoint addresses.
- L30 _public function_ `FMessageAddress()` — Default constructor (no initialization).
- L76 _public function_ `void Invalidate()` — Invalidates the GUID. @see IsValid
- L87 _public function_ `bool IsValid() const` — Checks whether this message address is valid or not. @return true if valid, false otherwise. @see Invalidate
- L98 _public function_ `FString ToString() const` — Converts this GUID to its string representation. @return The string representation. @see Parse
- L123 _public function_ `static FMessageAddress NewAddress()` — Returns a new message address. @return A new address.
- L139 _public function_ `static bool Parse(const FString& String, FMessageAddress& OutAddress)` — Converts a string to a message address. @param String The string to convert. @param OutAddress Will contain the parsed address. @return true if the string was converted successfully, false otherwise. @see ToString
- L147 _private member_ `FGuid UniqueId;` — Holds a unique identifier.

#### enum `EMessageScope`  
`enum class EMessageScope : uint8`  
_L166-183_
- desc: Enumerates scopes for published messages. The scope determines to which endpoints a published message will be delivered. By default, messages will be published to everyone on the local network (Subnet), but it is often useful to restrict the group of recipients to more local scopes, or to widen it to a larger audience outside the local network. For example, if a message is to be handled only by subscribers in the same application, the scope should be set to Process. If messages need to be published between different networks (i.e. between LAN and WLAN), it should be set to Network instead. Scopes only apply to published messages. Messages that are being sent to specific recipients will always be delivered, regardless of the endpoint locations.
- L169 _public enumerator_ `Thread` — Deliver to subscribers in the same thread.
- L172 _public enumerator_ `Process` — Deliver to subscribers in the same process.
- L175 _public enumerator_ `Network` — Deliver to subscribers on the network.
- L182 _public enumerator_ `All` — Deliver to all subscribers. Note: This must be the last value in this enumeration.

#### enum `EMessageFlags`  
`enum class EMessageFlags : uint32`  
_L185-195_
- L188 _public enumerator_ `None = 0` — No special flags
- L191 _public enumerator_ `Reliable = 1 << 0` — Guarantee that this message is delivered
- L194 _public enumerator_ `Traced = 1 << 1` — Trace this object through the transport on message bus. Only supported if the underlying transport handles the flag.

#### class `IMessageContext`  
`class IMessageContext`  
_L224-397_
- desc: Interface for message contexts. Messages are delivered inside message contexts, which store the message itself plus additional data associated with the message. Recipients of a message are usually interested in data that describes the message, such as its origin or when it expires. They may also be interested in optional out-of-band binary data that is attached to the message. The sender's address (IMessageContext.GetSender) is often needed to send a reply message to a message sender, i.e. in response to a published message. The message attachment (IMessageContext.GetAttachment) is an optional bundle of binary bulk data that is transferred independently from the message itself and allows for transferring larger amounts of data that would otherwise clog up the messaging system. In case a message was forwarded by another endpoint, the context of the original sender can be accessed using the IMessageContext.GetOriginalContext method. @see IMessageAttachment
- L233 _public prototype_ `virtual const TMap<FName, FString>& GetAnnotations() const = 0;` — Gets the optional message annotations. @return Message header collection.
- L240 _public prototype_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const = 0;` — Gets the message attachment, if present. @return A pointer to the message attachment, or nullptr if no attachment is present.
- L247 _public prototype_ `virtual const FDateTime& GetExpiration() const = 0;` — Gets the date and time at which the message expires. @return Expiration time.
- L255 _public prototype_ `virtual const void* GetMessage() const = 0;` — Gets the message data. @return A pointer to the message data. @see GetAttachment, GetMessageType, GetMessageTypeInfo
- L263 _public prototype_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const = 0;` — Gets the message's type information. @return Message type information. @see GetMessage, GetMessageType
- L270 _public prototype_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const = 0;` — Returns the original message context in case the message was forwarded. @return The original message context, or nullptr if the message wasn't forwarded.
- L278 _public prototype_ `virtual const TArray<FMessageAddress>& GetRecipients() const = 0;` — Gets the list of message recipients. @return Message recipients. @see GetSender
- L285 _public prototype_ `virtual EMessageScope GetScope() const = 0;` — Gets the scope to which the message was sent. @return The message scope.
- L292 _public prototype_ `virtual EMessageFlags GetFlags() const = 0;` — Gets the scope to which the message was sent. @return The message scope.
- L300 _public prototype_ `virtual const FMessageAddress& GetSender() const = 0;` — Gets the sender's address. @return Sender address. @see GetRecipients, GetSenderThread
- L308 _public prototype_ `virtual const FMessageAddress& GetForwarder() const = 0;` — Gets the forwarder's address. @note Identical to GetSender if the message wasn't forwarded. @return Forwarder address. @see GetSender, GetRecipients, GetSenderThread
- L316 _public prototype_ `virtual ENamedThreads::Type GetSenderThread() const = 0;` — Gets the name of the thread from which the message was sent. @return Sender threat name. @see GetSender
- L324 _public prototype_ `virtual const FDateTime& GetTimeForwarded() const = 0;` — Gets the time at which the message was forwarded. @return Time forwarded. @see GetTimeSent, IsForwarded
- L332 _public prototype_ `virtual const FDateTime& GetTimeSent() const = 0;` — Gets the time at which the message was sent. @return Time sent. @see GetTimeForwarded
- L343 _public function_ `FName GetMessageType() const` — `UE_DEPRECATED(5.1, "Type names are now represented by path names. Please use GetMessageTypePathName.")` — Gets the name of the message type. @return Message type name. @see GetMessage, GetMessageTypeInfo
- L360 _public function_ `FTopLevelAssetPath GetMessageTypePathName() const` — Gets the path name of the message type. @return Message type path name. @see GetMessage, GetMessageTypeInfo
- L377 _public function_ `bool IsForwarded() const` — Checks whether this is a forwarded message. @return true if the message was forwarded, false otherwise. @see GetOriginalContext, GetTimeForwarded, IsValid
- L388 _public function_ `bool IsValid() const` — Checks whether this context is valid. @return true if the context is valid, false otherwise. @see IsForwarded
- L396 _public prototype_ `virtual ~IMessageContext() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L41 _function_ `friend bool operator==(const FMessageAddress& X, const FMessageAddress& Y)` — Compares two message addresses for equality. @param X The first address to compare. @param Y The second address to compare. @return true if the addresses are equal, false otherwise.
- L53 _function_ `friend bool operator!=(const FMessageAddress& X, const FMessageAddress& Y)` — Compares two message addresses for inequality. @param X The first address to compare. @param Y The second address to compare. @return true if the addresses are not equal, false otherwise.
- L64 _function_ `friend FArchive& operator<<(FArchive& Ar, FMessageAddress& A)` — Serializes a message address from or into an archive. @param Ar The archive to serialize from or into. @param G The address to serialize.
- L111 _function_ `friend uint32 GetTypeHash(const FMessageAddress& Address)` — Calculates the hash for a message address. @param Address The address to calculate the hash for. @return The hash.
- L196 _prototype_ `ENUM_CLASS_FLAGS(EMessageFlags);`
- L200 _typedef_ `typedef TRange<EMessageScope> FMessageScopeRange;` — Type definition for message scope ranges.
- L203 _typedef_ `typedef TRangeBound<EMessageScope> FMessageScopeRangeBound;` — Type definition for message scope range bounds.

### `Source/Runtime/Messaging/Public/IMessageHandler.h` (Public)


#### class `IMessageHandler`  
`class IMessageHandler`  
_L13-28_
- desc: Interface for message handlers.
- L22 _public prototype_ `virtual void HandleMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) = 0;` — Handles the specified message. @param Context The context of the message to handle.
- L27 _public prototype_ `virtual ~IMessageHandler() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageInterceptor.h` (Public)


#### class `IMessageInterceptor`  
`class IMessageInterceptor`  
_L15-47_
- desc: Interface for message interceptors.
- L25 _public prototype_ `virtual FName GetDebugName() const = 0;` — Gets the interceptor's name (for debugging purposes). @return The debug name. @see GetInterceptorId
- L33 _public prototype_ `virtual const FGuid& GetInterceptorId() const = 0;` — Gets the interceptor's unique identifier (for debugging purposes). @return The interceptor's identifier. @see GetDebugName
- L41 _public prototype_ `virtual bool InterceptMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) = 0;` — Intercepts a message before it is being passed to the message router. @param Context The context of the message to intercept. @return true if the message was intercepted and should not be routed, false otherwise.
- L46 _public prototype_ `virtual ~IMessageInterceptor() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageReceiver.h` (Public)


#### class `IMessageReceiver`  
`class IMessageReceiver`  
_L25-93_
- desc: Interface for message recipients. Classes that implement this interface are able to receive messages from a message bus. A message recipient will receive a call to its IMessageReceiver.ReceiveMessage method for each message that was sent directly to it (via IMessageBus.Send) and for each published message (via IMessageBus.Publish) that it subscribed to (via IMessageBus.Subscribe). This interface provides a rather low-level mechanism for receiving messages. Instead of implementing it, Most users will want to use an instance of see FMessageEndpoint, which provides a much more convenient way of sending and receiving messages. @see FMessageEndpoint, IMessageBus, IMessageSender
- L35 _public prototype_ `virtual FName GetDebugName() const = 0;` — Gets the recipient's name (for debugging purposes). @return The debug name. @see GetRecipientId, GetRecipientThread
- L43 _public prototype_ `virtual const FGuid& GetRecipientId() const = 0;` — Gets the recipient's unique identifier (for debugging purposes). @return The recipient's identifier. @see GetDebugName, GetRecipientThread
- L53 _public prototype_ `virtual ENamedThreads::Type GetRecipientThread() const = 0;` — Gets the name of the thread on which to receive messages. If the recipient's ReceiveMessage() is thread-safe, return ThreadAny for best performance. @return Name of the receiving thread. @see GetDebugName, GetRecipientId
- L64 _public prototype_ `virtual bool IsLocal() const = 0;` — Checks whether this recipient represents a local endpoint. Local recipients are located in the current thread or process. Recipients located in other processes on the same machine or on remote machines are considered remote. @return true if this recipient is local, false otherwise. @see IsRemote
- L71 _public prototype_ `virtual void ReceiveMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) = 0;` — Handles the given message. @param Context Will hold the context of the received message.
- L84 _public function_ `bool IsRemote() const` — Checks whether this recipient represents a remote endpoint. Local recipients are located in the current thread or process. Recipients located in other processes on the same machine or on remote machines are considered remote. @return true if this recipient is remote, false otherwise. @see IsLocal
- L92 _public prototype_ `virtual ~IMessageReceiver() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageSender.h` (Public)


#### class `IMessageSender`  
`class IMessageSender`  
_L27-50_
- desc: Interface for message senders. Classes that implement this interface are able to send messages on a message bus. Each message sender must be uniquely identifiable with a message address that is returned by the IMessageSender.GetSenderAddress method. It is recommended that implementors of this interface generate a GUID for each instance, which must not change throughout the lifetime of the instance. The sending of messages is accomplished with the IMessageBus.Forward, IMessageBus.Publish and IMessageBus.Send methods. In case an error occurs during the sending of a message, the IMessageSender.NotifyMessageError method will be called. This interface provides a rather low-level mechanism for receiving messages. Instead of implementing it, Most users will want to use an instance of FMessageEndpoint, which provides a much more convenient way of sending and receiving messages. @see FMessageEndpoint, IMessageBus, IMessageReceiver
- L36 _public prototype_ `virtual FMessageAddress GetSenderAddress() = 0;` — Gets the sender's address. @return The message address.
- L44 _public prototype_ `virtual void NotifyMessageError(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FString& Error) = 0;` — Notifies the sender of errors. @param Context The context of the message that generated the error. @param Error The error string.
- L49 _public prototype_ `virtual ~IMessageSender() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageSubscription.h` (Public)


#### class `IMessageSubscription`  
`class IMessageSubscription`  
_L24-90_
- desc: Interface for message subscriptions. This interface provides access to a message subscription that was previously created with the IMessageBus.Subscribe method. It can be used to query the subscription's details using the various getters and modify its enabled state using the IMessageSubscription.Enable and IMessageSubscription.Disable methods. A subscription that is disabled will cause a message endpoint to stop receiving messages for the subscribed message type. However, the subscription is merely disabled and not removed.
- L33 _public prototype_ `virtual void Disable() = 0;` — Disables the subscription. @see Enable, IsEnabled
- L40 _public prototype_ `virtual void Enable() = 0;` — Enables the subscription. @see Disable, IsEnabled
- L49 _public function_ `inline FName GetMessageType()` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use GetMessageTypePathName.")` — Gets the type of subscribed messages. @return Message type. @see GetScopeRange, GetSubscriber
- L60 _public prototype_ `virtual FTopLevelAssetPath GetMessageTypePathName() = 0;` — Gets the type of subscribed messages. @return Message type. @see GetScopeRange, GetSubscriber
- L68 _public prototype_ `virtual const TRange<EMessageScope>& GetScopeRange() = 0;` — Gets the range of subscribed message scopes. @return Message scope range. @see GetMessageType, GetSubscriber
- L76 _public prototype_ `virtual const TWeakPtr<IMessageReceiver, ESPMode::ThreadSafe>& GetSubscriber() = 0;` — Gets the subscriber. @return The subscriber. @see GetMessageType, GetScopeRange
- L84 _public prototype_ `virtual bool IsEnabled() = 0;` — Checks whether the subscription is enabled. @return true if the subscription is enabled, false otherwise. @see Enable, Disable
- L89 _public prototype_ `virtual ~IMessageSubscription() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageTracer.h` (Public)


#### enum `EMessageTracerBreakpointState`  
`enum class EMessageTracerBreakpointState`  
_L21-34_
- desc: Enumerates tracer breakpoint states.
- L24 _public enumerator_ `Disabled` — The breakpoint is disabled.
- L27 _public enumerator_ `Enabled` — The breakpoint is enabled.
- L30 _public enumerator_ `EnabledIn` — The breakpoint is enabled for incoming messages.
- L33 _public enumerator_ `EnabledOut` — The breakpoint is enabled for outgoing messages.

#### enum `EMessageTracerDispatchTypes`  
`enum class EMessageTracerDispatchTypes`  
_L40-50_
- desc: Enumerates message dispatch types.
- L43 _public enumerator_ `Direct` — The message is being dispatched directly.
- L46 _public enumerator_ `Pending` — The message hasn't been dispatched yet.
- L49 _public enumerator_ `TaskGraph` — The message is being dispatched using the task graph system.

#### struct `FMessageTracerBreakpoint`  
`struct FMessageTracerBreakpoint`  
_L56-69_
- desc: Structure for tracer breakpoints.
- L59 _public member_ `FMessageAddress BreakOnRecipient;` — Recipient address to break on.
- L62 _public member_ `FMessageAddress BreakOnSender;` — Sender address to break on.
- L65 _public member_ `int64 HitCount;` — How many times the breakpoint was hit.
- L68 _public member_ `EMessageTracerBreakpointState State;` — The breakpoint's enabled state.

#### struct `FMessageTracerDispatchState`  
`struct FMessageTracerDispatchState`  
_L75-94_
- desc: Structure for message dispatch states.
- L78 _public member_ `double DispatchLatency;` — Holds the dispatch latency (in seconds).
- L81 _public member_ `EMessageTracerDispatchTypes DispatchType;` — Holds the message's dispatch type for the specified endpoint.
- L84 _public member_ `TSharedPtr<FMessageTracerEndpointInfo> EndpointInfo;` — Holds the endpoint to which the message was or is being dispatched.
- L87 _public member_ `ENamedThreads::Type RecipientThread;` — The thread on which the endpoint receives messages.
- L90 _public member_ `double TimeDispatched;` — Holds the time at which the message was dispatched.
- L93 _public member_ `double TimeHandled;` — Holds the time at which the message was actually handled (0.0 = not handled yet).

#### struct `FMessageTracerAddressInfo`  
`struct FMessageTracerAddressInfo`  
_L100-110_
- desc: Structure for a recipient's address information.
- L103 _public member_ `FMessageAddress Address;` — Holds a recipient's message address.
- L106 _public member_ `double TimeRegistered;` — Holds the time at which this address was registered.
- L109 _public member_ `double TimeUnregistered;` — Holds the time at which this address was unregistered.

#### struct `FMessageTracerEndpointInfo`  
`struct FMessageTracerEndpointInfo`  
_L116-132_
- desc: Structure for message endpoint debug information.
- L119 _public member_ `TMap<FMessageAddress, TSharedPtr<FMessageTracerAddressInfo>> AddressInfos;` — Holds the recipient's address information.
- L122 _public member_ `FName Name;` — Holds the recipient's human readable name.
- L125 _public member_ `TArray<TSharedPtr<FMessageTracerMessageInfo>> ReceivedMessages;` — Holds the list of messages received by this recipient.
- L128 _public member_ `bool Remote;` — Holds a flag indicating whether this is a remote recipient.
- L131 _public member_ `TArray<TSharedPtr<FMessageTracerMessageInfo>> SentMessages;` — Holds the list of messages sent by this recipient.

#### struct `FMessageTracerInterceptorInfo`  
`struct FMessageTracerInterceptorInfo`  
_L138-151_
- desc: Structure for message interceptor debug information.
- L141 _public member_ `FName Name;` — Holds the interceptor's human readable name.
- L144 _public member_ `TArray<TSharedPtr<FMessageTracerMessageInfo>> InterceptedMessages;` — Holds the list of messages intercepted by this interceptor.
- L147 _public member_ `double TimeRegistered;` — Holds the time at which this interceptor was registered.
- L150 _public member_ `double TimeUnregistered;` — Holds the time at which this interceptor was unregistered.

#### struct `FMessageTracerMessageInfo`  
`struct FMessageTracerMessageInfo`  
_L157-179_
- desc: Structure for message debug information.
- L160 _public member_ `TSharedPtr<IMessageContext, ESPMode::ThreadSafe> Context;` — Holds a pointer to the message context.
- L163 _public member_ `TMap<TSharedPtr<FMessageTracerEndpointInfo>, TSharedPtr<FMessageTracerDispatchState>> DispatchStates;` — Holds the message's dispatch states per endpoint.
- L166 _public member_ `bool Intercepted;` — Whether the message was intercepted.
- L169 _public member_ `TSharedPtr<FMessageTracerEndpointInfo> SenderInfo;` — Pointer to the sender's endpoint information.
- L172 _public member_ `double TimeRouted;` — Holds the time at which the message was routed (0.0 = pending).
- L175 _public member_ `double TimeSent;` — Holds the time at which the message was sent.
- L178 _public member_ `TSharedPtr<FMessageTracerTypeInfo> TypeInfo;` — Pointer to the message's type information.

#### struct `FMessageTracerTypeInfo`  
`struct FMessageTracerTypeInfo`  
_L185-196_
- desc: Structure for message type debug information.
- L188 _public member_ `TArray<TSharedPtr<FMessageTracerMessageInfo>> Messages;` — Holds the collection of messages of this type.
- L192 _public member_ `FName TypeName;` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use TypePathName.")` — Holds a name of the message type.
- L195 _public member_ `FTopLevelAssetPath TypePathName;` — Holds a path name of the message type.

#### class `IMessageTracer`  
`class IMessageTracer`  
_L206-331_
- desc: Interface for message tracers. This interface provides access to the message tracer that is built into a message bus. Message tracers are able to monitor and record all activities on a message bus. This includes the sending and receiving of messages, the registering and unregistering of message endpoints and interceptors and adding and removal of subscriptions.
- L215 _public prototype_ `virtual void Break() = 0;` — Breaks message routing. @see Continue, IsBreaking, Step
- L222 _public prototype_ `virtual void Continue() = 0;` — Starts the tracer or continues message routing from the current breakpoint. @see Break, Step
- L230 _public prototype_ `virtual bool IsBreaking() const = 0;` — Checks whether the tracer is currently at a breakpoint. @return true if at breakpoint, false otherwise. @see Break, IsRunning
- L238 _public prototype_ `virtual bool IsRunning() const = 0;` — Checks whether the tracer is currently running. @return true if the tracer is running, false otherwise. @see Continue, IsBreaking, Stop
- L241 _public prototype_ `virtual void Reset() = 0;` — Resets the tracer.
- L248 _public prototype_ `virtual void Step() = 0;` — Steps the tracer to the next message. @see Break, Continue, Stop
- L255 _public prototype_ `virtual void Stop() = 0;` — Stops the tracer. @see Continue, IsRunning, Step
- L263 _public prototype_ `virtual bool Tick(float DeltaTime) = 0;` — Ticks the tracer. @param DeltaTime The time in seconds since the last tick. @return true if any events were processed.
- L273 _public prototype_ `virtual int32 GetEndpoints(TArray<TSharedPtr<FMessageTracerEndpointInfo>>& OutEndpoints) const = 0;` — Gets the list of known message endpoints. @param OutEndpoints Will contain the list of endpoints. @return The number of endpoints returned.
- L280 _public prototype_ `virtual int32 GetMessages(TArray<TSharedPtr<FMessageTracerMessageInfo>>& OutMessages) const = 0;` — Gets the collection of known messages. @return The messages.
- L289 _public prototype_ `virtual int32 GetMessageTypes(TArray<TSharedPtr<FMessageTracerTypeInfo>>& OutTypes) const = 0;` — Gets the list of known message types filtered by name. @param NameFilter The name substring to filter with. @param OutTypes Will contain the list of message types. @return The number of message types returned.
- L296 _public prototype_ `virtual bool HasMessages() const = 0;` — Checks whether there are any messages in the history. @return true if there are messages, false otherwise.
- L300 _public typedef_ `typedef TSharedRef<FMessageTracerMessageInfo> FMessageTracerMessageInfoRef;`
- L301 _public typedef_ `typedef TSharedRef<FMessageTracerTypeInfo> FMessageTracerTypeInfoRef;`
- L308 _public prototype_ `DECLARE_EVENT_OneParam(IMessageTracer, FOnMessageAdded, FMessageTracerMessageInfoRef) virtual FOnMessageAdded& OnMessageAdded() = 0;` — A delegate that is executed when the collection of known messages has changed. @return The delegate.
- L316 _public prototype_ `DECLARE_EVENT(IMessageTracer, FOnMessagesReset) virtual FOnMessagesReset& OnMessagesReset() = 0;` — A delegate that is executed when the message history has been reset. @return The delegate.
- L324 _public prototype_ `DECLARE_EVENT_OneParam(IMessageTracer, FOnTypeAdded, FMessageTracerTypeInfoRef) virtual FOnTypeAdded& OnTypeAdded() = 0;` — A delegate that is executed when the collection of known messages types has changed. @return The delegate.
- L330 _protected prototype_ `virtual ~IMessageTracer() = default;` — Hidden destructor. The life time of a message tracer is managed by the message bus.

#### Free symbols / members of external scopes

- L308 _delegate_ `DECLARE_EVENT_OneParam(IMessageTracer, FOnMessageAdded, FMessageTracerMessageInfoRef) virtual FOnMessageAdded& OnMessageAdded() = 0;` — A delegate that is executed when the collection of known messages has changed. @return The delegate.
- L316 _delegate_ `DECLARE_EVENT(IMessageTracer, FOnMessagesReset) virtual FOnMessagesReset& OnMessagesReset() = 0;` — A delegate that is executed when the message history has been reset. @return The delegate.
- L324 _delegate_ `DECLARE_EVENT_OneParam(IMessageTracer, FOnTypeAdded, FMessageTracerTypeInfoRef) virtual FOnTypeAdded& OnTypeAdded() = 0;` — A delegate that is executed when the collection of known messages types has changed. @return The delegate.

### `Source/Runtime/Messaging/Public/IMessageTracerBreakpoint.h` (Public)


#### class `IMessageTracerBreakpoint`  
`class IMessageTracerBreakpoint`  
_L15-38_
- desc: Interface for message tracer breakpoints. @see IMessageTracer
- L24 _public prototype_ `virtual bool IsEnabled() const = 0;` — Checks whether this breakpoint is enabled. @return true if the breakpoint is enabled, false otherwise.
- L32 _public prototype_ `virtual bool ShouldBreak(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) const = 0;` — Checks whether the tracer should break on the given message. @param Context The context of the message to break on. @return true if the tracer should break, false otherwise.
- L37 _protected prototype_ `virtual ~IMessageTracerBreakpoint() = default;` — Hidden destructor.

### `Source/Runtime/Messaging/Public/IMessageTransport.h` (Public)


#### class `IMessageTransport`  
`class IMessageTransport`  
_L20-60_
- desc: Interface for message transport technologies. Licensees can implement this interface to add support for custom message transport technologies that are not supported out of the box, i.e. custom network protocols or APIs.
- L29 _public prototype_ `virtual FName GetDebugName() const = 0;` — Gets the name of this transport (for debugging purposes). @return The debug name.
- L38 _public prototype_ `virtual bool StartTransport(IMessageTransportHandler& Handler) = 0;` — Starts up the message transport. @param Handler The handler of inbound transport messages and events. @return Whether the transport was started successfully. @see StopTransport
- L45 _public prototype_ `virtual void StopTransport() = 0;` — Shuts down the message transport. @see StartTransport
- L54 _public prototype_ `virtual bool TransportMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TArray<FGuid>& Recipients) = 0;` — Transports the given message data to the specified network nodes. @param Context The context of the message to transport. @param Recipients The transport nodes to send the message to. @return true if the message is being transported, false otherwise.
- L59 _protected prototype_ `virtual ~IMessageTransport() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessageTransportHandler.h` (Public)


#### class `IMessageTransportHandler`  
`class IMessageTransportHandler`  
_L32-64_
- desc: Interface for message transport event handlers. This interface is typically implemented by message bridges and other classes that manage a message transport and wish to receive messages from it. This interface also notifies implementors of discovered and lost transport nodes. A transport node is the internal representation of a remote message endpoint that may exist in a different process or on a different computer. The actual implementation of these nodes depends on the transport layer. It may be a network socket connection, a named pipe, or some other communication technology. Each transport node gets a globally unique identifier that can be used by a message bridge to translate local message addresses to remote message endpoints. When a message endpoint on the message bus sends a message to a specific message address that represents a remote endpoint, the message bridge maps the address to a transport identifier, which is then mapped again to the corresponding connection in the transport layer. @see IMessageBridge, IMessageBus, IMessageContext, IMessageTransport
- L42 _public prototype_ `virtual void DiscoverTransportNode(const FGuid& NodeId) = 0;` — Called by message transports when a transport node has been discovered. @param NodeId The identifier of the discovered transport node. @see ForgetTransportNode
- L50 _public prototype_ `virtual void ForgetTransportNode(const FGuid& NodeId) = 0;` — Called by message transports when a transport node has been lost. @param NodeId The identifier of the lost transport node. @see DiscoverTransportNode
- L58 _public prototype_ `virtual void ReceiveTransportMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FGuid& NodeId) = 0;` — Called by message transports when a message was received. @param Context The context of the received message. @param NodeId The identifier of the transport node that received the message.
- L63 _public prototype_ `virtual ~IMessageTransportHandler() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/IMessagingModule.h` (Public)


#### class `IMessagingModule`  
`class IMessagingModule : public IModuleInterface`  
_L25-109_
- inherits: `IModuleInterface`
- desc: Interface for messaging modules. @see IMessageBridge, IMessageBus
- L28 _private typedef_ `using FMessageBusWeakPtr = TWeakPtr<IMessageBus, ESPMode::ThreadSafe>;`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageBusStartupOrShutdown, FMessageBusWeakPtr);`
- L34 _public prototype_ `virtual FOnMessageBusStartupOrShutdown& OnMessageBusStartup() = 0;` — Event triggered when a message bus is started.
- L37 _public prototype_ `virtual FOnMessageBusStartupOrShutdown& OnMessageBusShutdown() = 0;` — Event triggered when a message bus is shutdown.
- L51 _public prototype_ `virtual TSharedPtr<IMessageBridge, ESPMode::ThreadSafe> CreateBridge(const FMessageAddress& Address, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& Bus, const TSharedRef<IMessageTransport, ESPMode::ThreadSafe>& Transport) = 0;` — Creates a new message bridge. Message bridges translate messages between a message bus and another means of message transportation, such as network sockets. @param Address The bridge's address on the message bus. @param Bus The message bus to attach the bridge to. @param Transport The message transport technology to use. @return The new message bridge, or nullptr if the bridge couldn't be created. @see CreateBus
- L60 _public prototype_ `virtual TSharedPtr<IMessageBus, ESPMode::ThreadSafe> CreateBus(const TSharedPtr<IAuthorizeMessageRecipients>& RecipientAuthorizer = nullptr) = 0;` — Creates a new message bus. @param RecipientAuthorizer An optional recipient authorizer. @return The new message bus, or nullptr if the bus couldn't be created. @see CreateBridge
- L70 _public prototype_ `virtual TSharedPtr<IMessageBus, ESPMode::ThreadSafe> CreateBus(FString InName, const TSharedPtr<IAuthorizeMessageRecipients>& RecipientAuthorizer = nullptr) = 0;` — Creates a new message bus. @param Name The name of this message bus. @param RecipientAuthorizer An optional recipient authorizer. @return The new message bus, or nullptr if the bus couldn't be created. @see CreateBridge
- L77 _public prototype_ `virtual TSharedPtr<IMessageBus, ESPMode::ThreadSafe> GetDefaultBus() const = 0;` — Gets the default message bus if it has been initialized. @return The default bus.
- L85 _public prototype_ `virtual TArray<TSharedRef<IMessageBus, ESPMode::ThreadSafe>> GetAllBuses() const = 0;` — Gets all message buses that were created by this module via the #CreateBus method that are still valid. @return All message buses.
- L95 _public function_ `static IMessagingModule& Get()` — Gets a reference to the messaging module instance. @return A reference to the Messaging module. @todo gmp: better implementation using dependency injection.
- L108 _public prototype_ `virtual ~IMessagingModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMessaging, Log, All);` — Log category for message bus code
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMessaging, Log, All);` — Log category for message bus code
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageBusStartupOrShutdown, FMessageBusWeakPtr);`

### `Source/Runtime/Messaging/Public/IMutableMessageContext.h` (Public)


#### class `IMutableMessageContext`  
`class IMutableMessageContext : public IMessageContext`  
_L22-89_
- inherits: `IMessageContext`
- desc: Interface for mutable message contexts.
- L32 _public prototype_ `virtual void AddRecipient(const FMessageAddress& Recipient) = 0;` — Adds a message address to the recipient list. @param Recipient The address of the recipient to add.
- L39 _public prototype_ `virtual void SetAttachment(const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& InAttachment) = 0;` — Sets the optional message attachment. @param InAttachment The attachment to set.
- L47 _public prototype_ `virtual void SetMessage(void* InMessage, UScriptStruct* InTypeInfo) = 0;` — Sets the message. @param InMessage The message to set. @param InTypeInfo The message's type information.
- L54 _public prototype_ `virtual void SetExpiration(const FDateTime& InExpiration) = 0;` — Sets the date and time at which the message expires. @param InExpiration Expiration date and time.
- L62 _public prototype_ `virtual void SetHeader(const FName& Key, const FString& Value) = 0;` — Sets the value of the header with the specified key. @param Key The header key. @param Value The header value.
- L69 _public prototype_ `virtual void SetScope(EMessageScope InScope) = 0;` — Sets the message scope. @param InScope The message scope.
- L76 _public prototype_ `virtual void SetSender(const FMessageAddress& InSender) = 0;` — Sets the address of the message's sender. @param InSender The message sender's address.
- L83 _public prototype_ `virtual void SetTimeSent(const FDateTime& InTimeSent) = 0;` — Sets the date and time at which the message was sent. @param InTimeSent Send date and time.
- L88 _public prototype_ `virtual ~IMutableMessageContext() = default;` — Virtual destructor.

### `Source/Runtime/Messaging/Public/INetworkMessagingExtension.h` (Public)


#### struct `FMessageTransportStatistics`  
`struct FMessageTransportStatistics`  
_L14-51_
- desc: General information on transport health per Node Id.
- L17 _public member_ `uint64 TotalBytesSent = 0;` — Total number of bytes sent to the destination endpoint.
- L20 _public member_ `uint64 TotalBytesLost = 0;` — Total number of bytes lost to the destination endpoint.
- L23 _public member_ `uint64 TotalBytesReceived = 0;` — Total number of bytes received from endpoint.
- L26 _public member_ `uint64 BytesInflight = 0;` — Number of bytes currently in flight waiting for.
- L29 _public member_ `uint64 PacketsSent = 0;` — Total number of packets sent to the destination.
- L32 _public member_ `uint64 PacketsLost = 0;` — Total number of packets lost to the destination.
- L35 _public member_ `uint64 PacketsAcked = 0;` — Number of packets acknowledged.
- L38 _public member_ `uint64 PacketsReceived = 0;` — Number of packets received from this endpoint.
- L41 _public member_ `uint64 PacketsInFlight = 0;` — Current packets in flight waiting for
- L44 _public member_ `uint32 WindowSize = 0;` — The size of our sending window (as indicated by the transport).
- L47 _public member_ `FTimespan AverageRTT{0};` — Computed average Round-trip time to receive data from connected endpoint.
- L50 _public member_ `FString IPv4AsString;` — IPv4 address as a string value.

#### struct `FOutboundTransferStatistics`  
`struct FOutboundTransferStatistics`  
_L54-79_
- desc: Per-node per-message transfer statistics.
- L57 _public member_ `FGuid DestinationId;` — Unique Id for the target.
- L60 _public member_ `int32 MessageId;` — Monotonically increasing ID for each message sent across the network.
- L63 _public member_ `uint64 BytesToSend;` — Total bytes to send for the given MessageId
- L66 _public member_ `uint64 BytesSent;` — Total bytes sent thus far.
- L69 _public member_ `uint64 BytesAcknowledged;` — Total number of bytes acknowledge by the destination.
- L72 _public member_ `bool bIsReliable;` — Indicate if the message is reliably sent.
- L75 _public member_ `bool bTraced;` — Indicates this was a traced packet.
- L78 _public member_ `bool bComplete;` — Indicates if the message has been completely sent. In unreliable case, it means that all bytes have been sent. In the reliable case, it means it has been fully acknowledged.

#### struct `FInboundTransferStatistics`  
`struct FInboundTransferStatistics`  
_L82-104_
- desc: Per-node per-message transfer statistics.
- L85 _public member_ `FGuid OriginId;` — Unique Id for the target.
- L88 _public member_ `int32 MessageId;` — Message Id that uniquely identifies the inbound message. If MessageId == -1 then this message is not reliably sent or is not segmented over multiple packets.
- L91 _public member_ `uint64 BytesToReceive;` — Total bytes to send for the given MessageId
- L94 _public member_ `int32 BytesReceived;` — Total bytes sent thus far.
- L97 _public member_ `bool bWasReliablySent;` — Was the message reliable.
- L100 _public member_ `bool bTraced;` — True, if this was a traced packet
- L103 _public member_ `bool bComplete;` — True, if we have fully received the message

#### class `INetworkMessagingExtension`  
`class INetworkMessagingExtension : public IModularFeature`  
_L115-199_
- inherits: `IModularFeature`
- desc: Interface for the messaging module network extension Plugins or modules implementing messaging transport for MessageBus can implement this modular feature to provide control on the service it provides.
- L119 _public member_ `static FName ModularFeatureName;` — The modular feature name to get the messaging extension.
- L124 _public prototype_ `virtual FName GetName() const = 0;` — Get the name of this messaging extension.
- L130 _public prototype_ `virtual bool IsSupportEnabled() const = 0;` — Indicate if support is available for this extension @return true if the service can be successfully started.
- L137 _public prototype_ `virtual void RestartServices() = 0;` — Start or restart this messaging extension service for MessageBus using its current running configuration which might include modifications to endpoints @see AddEndpoint, RemoveEndpoint
- L143 _public prototype_ `virtual TArray<FString> GetListeningAddresses() const = 0;` — The list of network addresses that we are currently listening on.  The string must be in the form of <address:port>
- L148 _public prototype_ `virtual bool CanProvideNetworkStatistics() const = 0;` — Indicates if this network messaging interface can return network statistics.
- L153 _public prototype_ `virtual FMessageTransportStatistics GetLatestNetworkStatistics(FGuid NodeId) const = 0;` — Return the current network counters for the given Node endpoint
- L158 _public prototype_ `virtual FGuid GetNodeIdFromAddress(const FMessageAddress& MessageAddress) const = 0;` — Return the node ID corresponding to MessageAddress
- L164 _public prototype_ `virtual FOnOutboundTransferDataUpdated& OnOutboundTransferUpdatedFromThread() = 0;` — Delegate invoked when any transmission statistics are updated for outbound nodes (sent). This delegate may get called from another thread. Please consider thread safety when receiving this delegate.
- L170 _public prototype_ `virtual FOnInboundTransferDataUpdated& OnInboundTransferUpdatedFromThread() = 0;` — Delegate invoked when any transmission statistics are update for inbound (received). This delegate may get called from another thread. Please consider thread safety when receiving this delegate.
- L178 _public prototype_ `virtual void ShutdownServices() = 0;` — Shutdown this messaging extension services for MessageBus and remove any configuration modification. Using RestartServices after ShutdownServices will start the service with an unaltered configuration @see RestartServices
- L184 _public prototype_ `virtual TArray<FString> GetKnownEndpoints() const = 0;` — Returns the list of internet addresses known by the transport. The addresses are in the form of <address:port>
- L191 _public prototype_ `virtual void AddEndpoint(const FString& InEndpoint) = 0;` — Add an endpoint to the running configuration of this messaging service This change is transient and does not modified saved configuration. @param InEndpoint the endpoint string to add to the running service, should be in the form <ipv4:port>.
- L198 _public prototype_ `virtual void RemoveEndpoint(const FString& InEndpoint) = 0;` — Remove a static endpoint from the running configuration of the UDP messaging service This change is transient and does not modified saved configuration. @param InEndpoint the endpoint to remove from the running service, should be in the form <ipv4:port>.

#### Free symbols / members of external scopes

- L107 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnOutboundTransferDataUpdated, FOutboundTransferStatistics);`
- L107 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnOutboundTransferDataUpdated, FOutboundTransferStatistics);`
- L108 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnInboundTransferDataUpdated, FInboundTransferStatistics);`
- L108 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnInboundTransferDataUpdated, FInboundTransferStatistics);`

### `Source/Runtime/Messaging/Public/MessagingTrace.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `# define MESSAGINGTRACE_ENABLED 1`
- L12 _macro_ `# define MESSAGINGTRACE_ENABLED 0`
- L23 _macro_ `#define SCOPED_MESSAGING_TRACE(TraceName) TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(TraceName, MessagingChannel)`
- L27 _macro_ `#define SCOPED_MESSAGING_TRACE(...)`
