# Runtime / MessagingRpc

- module root: `Source/Runtime/MessagingRpc`
- headers: 11; symbols: 161
- symbol kinds: class=12, delegate=2, function=37, macro=5, member=34, prototype=64, struct=5, typedef=2
- DynamicallyLoadedModuleNames: Messaging
- PrivateIncludePathModuleNames: Messaging
- PublicDependencyModuleNames: Core, CoreUObject, MessagingCommon

### `Source/Runtime/MessagingRpc/Private/MessageRpcClient.h` (Private)


#### class `FMessageRpcClient`  
`class FMessageRpcClient : public IMessageRpcClient`  
_L25-94_
- inherits: `IMessageRpcClient`
- desc: Implements an RPC client.
- L31 _public prototype_ `FMessageRpcClient();` — Default constructor.
- L32 _public prototype_ `FMessageRpcClient(const FString& InDebugName, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);`
- L35 _public prototype_ `virtual ~FMessageRpcClient();` — Virtual destructor.
- L41 _public prototype_ `virtual void Connect(const FMessageAddress& InServerAddress) override;`
- L42 _public prototype_ `virtual void Disconnect() override;`
- L43 _public prototype_ `virtual bool IsConnected() const override;`
- L46 _protected prototype_ `explicit FMessageRpcClient(FMessageEndpointBuilder&& InEndpointBuilder);`
- L54 _protected prototype_ `TSharedPtr<IMessageRpcCall> FindCall(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Find the active RPC call for a received message. @param Context The context of the received message. @return The matching call object, or nullptr if not found.
- L61 _protected prototype_ `void SendCall(const TSharedPtr<IMessageRpcCall>& Call);` — Sends an RPC call to the server. @param Call The RPC call to make.
- L67 _protected prototype_ `virtual void AddCall(const TSharedRef<IMessageRpcCall>& Call) override;`
- L68 _protected prototype_ `virtual void CancelCall(const FGuid& CallId) override;`
- L73 _private prototype_ `void HandleProgressMessage(const FMessageRpcProgress& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FMessageRpcProgress messages.
- L76 _private prototype_ `void HandleRpcMessages(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for handling all message types.
- L79 _private prototype_ `bool HandleTicker(float DeltaTime);` — Callback for the ticker.
- L84 _private member_ `TMap<FGuid, TSharedPtr<IMessageRpcCall>> Calls;` — Active RPC calls.
- L87 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Message endpoint.
- L90 _private member_ `FMessageAddress ServerAddress;` — The RPC server's address.
- L93 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to the registered ticker.

### `Source/Runtime/MessagingRpc/Private/MessageRpcDefines.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define MESSAGE_RPC_TICK_DELAY 0.1f`
- L12 _macro_ `#define MESSAGE_RPC_RETRY_INTERVAL 1.0`
- L17 _macro_ `#define MESSAGE_RPC_RETRY_TIMEOUT 3.0`
- L22 _macro_ `#define MESSAGE_RPC_PROGRESS_INTERVAL (0.25 * MESSAGE_RPC_RETRY_INTERVAL)`

### `Source/Runtime/MessagingRpc/Public/IMessageRpcCall.h` (Public)


#### class `IMessageRpcCall`  
`class IMessageRpcCall`  
_L23-96_
- desc: Interface for RPC calls. Every time an RPC call is made, a request message containing the call parameters is sent to the remote endpoint. While the remote endpoint is executing the call, it may send back progress updates in regular intervals. Once the call is complete, the remote endpoint sends a response message containing the result.
- L33 _public prototype_ `virtual void Complete(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& ResponseContext) = 0;` — Complete the request and set its result, if available. @param ResponseContext The context of the response message. @see TimeOut
- L40 _public prototype_ `virtual const FGuid& GetId() const = 0;` — Get the call's unique identifier. @return Call identifier.
- L47 _public prototype_ `virtual void* GetMessageTemplate() const = 0;` — Get the request message template. @return Pointer to the request message template.
- L54 _public prototype_ `virtual void* ConstructMessage() const = 0;` — Constructs a new message based on the call message template. Ownership of the message belongs to the caller. @return Pointer to the request message.
- L61 _public prototype_ `virtual FDateTime GetLastUpdated() const = 0;` — Get the time at which the request was last updated by the server. @return Update time.
- L68 _public prototype_ `virtual UScriptStruct* GetMessageType() const = 0;` — Get the type of the request message. @return Request message type.
- L75 _public prototype_ `virtual FDateTime GetTimeCreated() const = 0;` — Gets the time at which the request was created. @return Creation time.
- L82 _public prototype_ `virtual void TimeOut() = 0;` — Time out the request. @see Complete
- L90 _public prototype_ `virtual void UpdateProgress(float InCompletion, const FText& InStatusText) = 0;` — Update the current progress. @param InCompletion The new completion percentage. @param InStatusText The new status text.
- L95 _public prototype_ `virtual ~IMessageRpcCall() = default;` — Virtual destructor.

### `Source/Runtime/MessagingRpc/Public/IMessageRpcClient.h` (Public)


#### class `IMessageRpcClient`  
`class IMessageRpcClient`  
_L18-246_
- desc: Interface for RPC clients.
- L183 _public prototype_ `virtual void Connect(const FMessageAddress& InServerAddress) = 0;` — Connect this client to an RPC server. @param InServerAddress The RPC server's message address. @see Disconnect
- L190 _public prototype_ `virtual void Disconnect() = 0;` — Disconnect this client from the RPC server. @see Connect
- L197 _public prototype_ `virtual bool IsConnected() const = 0;` — Whether the MessageRpcClient is currently connected to an RPC server. @return true if the client is connected, false otherwise.
- L209 _public function_ `template<typename RpcType, typename... P> TAsyncResult<typename RpcType::FResult> Call(P... Params)` — Call a remote procedure. @param RpcType The RPC type definition. @param P The call parameter types. @param Params The call parameter list.
- L233 _protected prototype_ `virtual void AddCall(const TSharedRef<IMessageRpcCall>& Call) = 0;` — Add an RPC request. @param Request The call to add.
- L240 _protected prototype_ `virtual void CancelCall(const FGuid& CallId) = 0;` — Cancel the specified RPC call. @param CallId The unique identifier of the call to cancel.
- L245 _public prototype_ `virtual ~IMessageRpcClient() = default;` — Virtual destructor.

#### class `IMessageRpcClient::FCall`  
`class FCall : public IAsyncProgress , public IAsyncTask , public IMessageRpcCall`  
_L21-103_
- inherits: `IAsyncProgress,IAsyncTask,IMessageRpcCall`
- desc: Abstract base class for RPC calls.
- L28 _public function_ `FCall() : State(EAsyncTaskState::Running) , TimeCreated(FDateTime::UtcNow())`
- L35 _public function_ `FSimpleDelegate& OnCancelled()`
- L42 _public function_ `virtual TOptional<float> GetCompletion() override`
- L47 _public function_ `virtual FText GetStatusText() override`
- L52 _public function_ `virtual FSimpleDelegate& OnProgressChanged() override`
- L59 _public function_ `virtual void Cancel() override`
- L65 _public function_ `virtual EAsyncTaskState GetTaskState() override`
- L72 _public function_ `virtual FDateTime GetLastUpdated() const override`
- L77 _public function_ `virtual FDateTime GetTimeCreated() const override`
- L82 _public function_ `virtual void UpdateProgress(float InCompletion, const FText& InStatusText) override`
- L93 _protected member_ `float Completion;`
- L94 _protected member_ `FDateTime LastUpdated;`
- L95 _protected member_ `EAsyncTaskState State;`
- L96 _protected member_ `FText StatusText;`
- L97 _protected member_ `FDateTime TimeCreated;`
- L101 _private member_ `FSimpleDelegate CanceledDelegate;`
- L102 _private member_ `FSimpleDelegate ProgressChangedDelegate;`

#### class `IMessageRpcClient::TCall`  
`template<typename RpcType, typename... P> class TCall : public FCall`  
_L108-173_
- inherits: `FCall`
- desc: Template for RPC requests.
- L113 _public function_ `TCall(const FGuid& CallId, P... Params) : MessageTemplate(new typename RpcType::FRequest(Params...))`
- L119 _public function_ `virtual ~TCall()`
- L124 _public function_ `virtual void Complete(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& ResponseContext) override`
- L138 _public function_ `virtual void* ConstructMessage() const override`
- L143 _public function_ `TFuture<typename RpcType::FResult> GetFuture()`
- L148 _public function_ `virtual const FGuid& GetId() const override`
- L153 _public function_ `virtual void* GetMessageTemplate() const override`
- L158 _public function_ `virtual UScriptStruct* GetMessageType() const override`
- L163 _public function_ `virtual void TimeOut() override`
- L171 _private member_ `TPromise<typename RpcType::FResult> Promise;`
- L172 _private member_ `typename RpcType::FRequest* MessageTemplate;`

#### Free symbols / members of external scopes

- L211 _typedef_ `typedef TCall<RpcType, P...> CallType;` (scope `IMessageRpcClient::Call`)
- L218 _function_ `Call->OnCancelled().BindLambda([this, CallId]() { CancelCall(CallId); });` (scope `IMessageRpcClient::Call`)

### `Source/Runtime/MessagingRpc/Public/IMessageRpcHandler.h` (Public)


#### class `IMessageRpcHandler`  
`class IMessageRpcHandler`  
_L14-30_
- desc: Interface for RPC request handlers.
- L24 _public prototype_ `virtual TSharedRef<IMessageRpcReturn> HandleRequest(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) = 0;` — Handle an RPC request. @param Context The context of the RPC request message. @return An object for the pending RPC return value.
- L29 _public prototype_ `virtual ~IMessageRpcHandler() = default;` — Virtual destructor.

### `Source/Runtime/MessagingRpc/Public/IMessageRpcReturn.h` (Public)


#### class `IMessageRpcReturn`  
`class IMessageRpcReturn`  
_L12-41_
- desc: Interface for RPC return values.
- L17 _public prototype_ `virtual void Cancel() = 0;` — Cancel the computation of the return value.
- L21 _public prototype_ `virtual FRpcMessage* CreateResponseMessage() const = 0;`
- L28 _public prototype_ `virtual UScriptStruct* GetResponseTypeInfo() const = 0;` — Gets the type information for the corresponding RPC response message. @return The message type information.
- L35 _public prototype_ `virtual bool IsReady() const = 0;` — Check whether the return value is ready. @return true if the return value is ready, false otherwise.
- L40 _public prototype_ `virtual ~IMessageRpcReturn() = default;` — Virtual destructor.

### `Source/Runtime/MessagingRpc/Public/IMessageRpcServer.h` (Public)


#### class `IMessageRpcServer`  
`class IMessageRpcServer`  
_L25-165_
- desc: Interface for RPC servers.
- L105 _public function_ `inline void AddHandler(const FName& RequestMessageType, const TSharedRef<IMessageRpcHandler>& Handler)` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use a version of this function that takes an FTopLevelAssetPath as MessageType.")` — Add an RPC request handler. @param Handler The handler to add.
- L115 _public prototype_ `virtual void AddHandler(const FTopLevelAssetPath& RequestMessageType, const TSharedRef<IMessageRpcHandler>& Handler) = 0;` — Add an RPC request handler. @param Handler The handler to add.
- L122 _public prototype_ `virtual const FMessageAddress& GetAddress() const = 0;` — Gets the server's message address. @return Message address.
- L131 _public prototype_ `virtual FOnMessageRpcNoHandler& OnNoHandler() = 0;` — `UE_DEPRECATED(5.1, "Types names are now represented by path names. Please use OnNoHandlerWithPathName.")` — Get a delegate that is executed when a received RPC message has no registered handler. @return The delegate.
- L139 _public prototype_ `virtual FOnMessagePathNameRpcNoHandler& OnNoHandlerWithPathName() = 0;` — Get a delegate that is executed when a received RPC message has no registered handler. @return The delegate.
- L145 _public prototype_ `virtual void SetSendProgressUpdate(bool InSendProgress) = 0;` — Set if the server sends progress updates @param InSendProgress if the server send rpc progress update
- L156 _public function_ `template<typename RpcType, typename HandlerType> void RegisterHandler(HandlerType* Handler, typename THandler<RpcType, HandlerType>::FuncType Func)` — Register an RPC request handler. @param Handler The object that will handle the requests. @param HandlerFunc The object's request handling function.
- L164 _public prototype_ `virtual ~IMessageRpcServer() = default;` — Virtual destructor.

#### class `IMessageRpcServer::TReturn`  
`template<typename RpcType> class TReturn : public IMessageRpcReturn`  
_L29-67_
- inherits: `IMessageRpcReturn`
- desc: Template for RPC results.
- L34 _public function_ `TReturn(TAsyncResult<typename RpcType::FResult>&& InResult) : Result(MoveTemp(InResult))`
- L38 _public function_ `virtual void Cancel() override`
- L48 _public function_ `virtual FRpcMessage* CreateResponseMessage() const override`
- L56 _public function_ `virtual UScriptStruct* GetResponseTypeInfo() const override`
- L61 _public function_ `virtual bool IsReady() const override`
- L66 _public member_ `TAsyncResult<typename RpcType::FResult> Result;`

#### class `IMessageRpcServer::THandler`  
`template<typename RpcType, typename HandlerType> class THandler : public IMessageRpcHandler`  
_L72-95_
- inherits: `IMessageRpcHandler`
- desc: Template for RPC request handlers.
- L77 _public typedef_ `typedef TAsyncResult<typename RpcType::FResult>(HandlerType::*FuncType)(const typename RpcType::FRequest&);`
- L79 _public function_ `THandler( HandlerType* InHandler, FuncType InFunc ) : Handler(InHandler) , Func(InFunc)`
- L86 _public function_ `virtual TSharedRef<IMessageRpcReturn> HandleRequest(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) override`
- L93 _private member_ `HandlerType* Handler;`
- L94 _private member_ `FuncType Func;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessageRpcNoHandler, const FName& ) DECLARE_DELEGATE_OneParam(FOnMessagePathNameRpcNoHandler, const FTopLevelAssetPath& ) class IMessageRpcServer { template<typename RpcType> class TReturn : public IMessageRpcReturn { public: TReturn(TAsyncResult<typename RpcType::FResult>&& InResult) : Result(MoveTemp(InResult)) { } virtual void Cancel() override { auto Task = Result.GetTask(); if (Task.IsValid()) { Task->Cancel(); } } virtual FRpcMessage* CreateResponseMessage() const override { const TFuture<typename RpcType::FResult>& Future = Result.GetFuture(); check(Future.IsReady()); return FMessageEndpoint::MakeMessage<typename RpcType::FResponse>(Future.Get()); } virtual UScriptStruct* GetResponseTypeInfo() const override {`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessagePathNameRpcNoHandler, const FTopLevelAssetPath& ) class IMessageRpcServer { template<typename RpcType> class TReturn : public IMessageRpcReturn { public: TReturn(TAsyncResult<typename RpcType::FResult>&& InResult) : Result(MoveTemp(InResult)) { } virtual void Cancel() override { auto Task = Result.GetTask(); if (Task.IsValid()) { Task->Cancel(); } } virtual FRpcMessage* CreateResponseMessage() const override { const TFuture<typename RpcType::FResult>& Future = Result.GetFuture(); check(Future.IsReady()); return FMessageEndpoint::MakeMessage<typename RpcType::FResponse>(Future.Get()); } virtual UScriptStruct* GetResponseTypeInfo() const override { return RpcType::FResponse::StaticStruct(); }`

### `Source/Runtime/MessagingRpc/Public/IMessagingRpcModule.h` (Public)


#### class `IMessagingRpcModule`  
`class IMessagingRpcModule : public IModuleInterface`  
_L18-59_
- inherits: `IModuleInterface`
- desc: Interface for the MessagingRpc module.
- L28 _public prototype_ `virtual TSharedRef<IMessageRpcClient> CreateRpcClient() = 0;` — Create a client for remote procedure calls. @return The RPC client.
- L37 _public prototype_ `virtual TSharedRef<IMessageRpcClient> CreateRpcClient(const FString& DebugName, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& MessageBus) = 0;` — Create a client for remote procedure calls. @param DebugName The RPC client's endpoint debug name. @param MessageBus The RPC client's endpoint message bus. @return The RPC client.
- L44 _public prototype_ `virtual TSharedRef<IMessageRpcServer> CreateRpcServer() = 0;` — Create a server for remote procedure calls. @return The RPC server.
- L53 _public prototype_ `virtual TSharedRef<IMessageRpcServer> CreateRpcServer(const FString& DebugName, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& MessageBus) = 0;` — Create a server for remote procedure calls. @param DebugName The RPC server's endpoint debug name. @param MessageBus The RPC server's endpoint message bus. @return The RPC server.
- L58 _public prototype_ `virtual ~IMessagingRpcModule() = default;` — Virtual destructor.

### `Source/Runtime/MessagingRpc/Public/MessageRpcMessages.h` (Public)


#### struct `FMessageRpcCancel`  
`struct FMessageRpcCancel`  
_L14-29_
- reflection: `USTRUCT()`
- desc: Message for canceling an RPC call.
- L20 _public member_ `FGuid CallId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Correlation identifier for the RPC call that this message refers to.
- L23 _public function_ `FMessageRpcCancel()` — Default constructor.
- L26 _public function_ `FMessageRpcCancel(const FGuid& InCallId) : CallId(InCallId)` — Creates and initializes a new instance.

#### struct `FMessageRpcProgress`  
`struct FMessageRpcProgress`  
_L34-59_
- reflection: `USTRUCT()`
- desc: Message for updating the progress of an RPC call.
- L40 _public member_ `float Completion;` — `UPROPERTY(EditAnywhere, Category="Message")` — Completion percentage (0.0 to 1.0).
- L44 _public member_ `FGuid CallId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Correlation identifier for the RPC call that this message refers to.
- L48 _public member_ `FString StatusText;` — `UPROPERTY(EditAnywhere, Category="Message")` — Status text.
- L51 _public function_ `FMessageRpcProgress() : Completion(0.0f)` — Default constructor.
- L54 _public function_ `FMessageRpcProgress(const FGuid& InCallId, float InCompletion, const FText& InStatusText) : Completion(InCompletion) , CallId(InCallId) , StatusText(InStatusText.ToString())` — Creates and initializes a new instance.

#### struct `FMessageRpcUnhandled`  
`struct FMessageRpcUnhandled`  
_L64-79_
- reflection: `USTRUCT()`
- desc: Message for notifying RPC clients that a call was not handled by the server.
- L70 _public member_ `FGuid CallId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Correlation identifier for the RPC call that this message refers to.
- L73 _public function_ `FMessageRpcUnhandled()` — Default constructor.
- L76 _public function_ `FMessageRpcUnhandled(const FGuid& InCallId) : CallId(InCallId)` — Creates and initializes a new instance.

### `Source/Runtime/MessagingRpc/Public/MessageRpcServer.h` (Public)


#### class `FMessageRpcServer`  
`class FMessageRpcServer : public IMessageRpcServer`  
_L29-111_
- inherits: `IMessageRpcServer`
- desc: Implements an RPC server.
- L34 _public prototype_ `FMessageRpcServer();` — Default constructor.
- L35 _public prototype_ `FMessageRpcServer(const FString& InDebugName, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);`
- L38 _public prototype_ `virtual ~FMessageRpcServer();` — Virtual destructor.
- L44 _public prototype_ `virtual void AddHandler(const FTopLevelAssetPath& RequestMessageType, const TSharedRef<IMessageRpcHandler>& Handler) override;`
- L45 _public prototype_ `virtual const FMessageAddress& GetAddress() const override;`
- L47 _public prototype_ `virtual FOnMessageRpcNoHandler& OnNoHandler() override;`
- L49 _public prototype_ `virtual FOnMessagePathNameRpcNoHandler& OnNoHandlerWithPathName() override;`
- L50 _public prototype_ `virtual void SetSendProgressUpdate(bool InSendProgress) override;`
- L52 _protected prototype_ `explicit FMessageRpcServer(FMessageEndpointBuilder&& InEndpointBuilder);`
- L63 _protected prototype_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetEndpoint() const;`
- L66 _protected prototype_ `void ProcessCancelation(const FMessageRpcCancel& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Processes an FMessageRpcCancel message.
- L69 _protected prototype_ `void ProcessRequest(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Processes an RPC request message.
- L72 _protected prototype_ `void SendProgress(const FGuid& CallId, const FReturnInfo& ReturnInfo);` — Send a progress message to the RPC client that made the RPC call.
- L75 _protected prototype_ `void SendResult(const FGuid& CallId, const FReturnInfo& ReturnInfo);` — Send a result message to the RPC client that made the RPC call.
- L80 _protected member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Message endpoint.
- L85 _private prototype_ `void HandleMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles all incoming messages.
- L88 _private prototype_ `bool HandleTicker(float DeltaTime);` — Handles the ticker.
- L93 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<IMessageRpcHandler>> Handlers;` — Registered request message handlers.
- L97 _private member_ `FOnMessageRpcNoHandler NoHandlerDelegate;` — Delegate that is executed when a received RPC message has no registered handler.
- L101 _private member_ `FOnMessagePathNameRpcNoHandler NoHandlerDelegateWithPathName;` — Delegate that is executed when a received RPC message has no registered handler.
- L104 _private member_ `TMap<FGuid, FReturnInfo> Returns;` — Collection of pending RPC returns.
- L107 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to the registered ticker.
- L110 _private member_ `bool bSendProgress = true;` — If the server sends progress updates.

#### struct `FMessageRpcServer::FReturnInfo`  
`struct FReturnInfo`  
_L54-61_
- L56 _public member_ `FMessageAddress ClientAddress;`
- L57 _public member_ `FDateTime LastProgressSent;`
- L58 _public member_ `TSharedPtr<IAsyncProgress> Progress;`
- L59 _public member_ `TSharedPtr<IMessageRpcReturn> Return;`
- L60 _public member_ `TSharedPtr<IAsyncTask> Task;`

### `Source/Runtime/MessagingRpc/Public/RpcMessage.h` (Public)


#### struct `FRpcMessage`  
`struct FRpcMessage`  
_L15-25_
- reflection: `USTRUCT()`
- desc: Base type for RPC messages.
- L21 _public member_ `FGuid CallId;` — `UPROPERTY()` — Correlation identifier for the RPC call that this message refers to.
- L24 _public function_ `FRpcMessage()` — Default constructor.

#### Free symbols / members of external scopes

- L28 _macro_ `#define DECLARE_RPC(RpcType, ResultType) \`
