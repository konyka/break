# Runtime / WebSockets

- module root: `Source/Runtime/Online/WebSockets`
- headers: 12; symbols: 342
- symbol kinds: class=9, delegate=26, enum=3, enumerator=15, function=14, macro=2, member=102, prototype=157, struct=9, typedef=5
- PrivateDependencyModuleNames: Core, HTTP, SSL

### `Source/Runtime/Online/WebSockets/Private/Lws/LwsWebSocket.h` (Private)


#### struct `FLwsSendBuffer`  
`struct FLwsSendBuffer`  
_L27-64_
- desc: Buffer for one outgoing packet
- L35 _public prototype_ `FLwsSendBuffer(const uint8* Data, const SIZE_T Size, const bool bInIsBinary);` — Constructor @param Data pointer to data to fill our buffer with @param Size size of Data @param bInIsBinary Whether or not this should be treated as a binary packet
- L42 _public prototype_ `int32 GetPayloadSize() const;` — Get the actual payload size Payload includes additional room for libwebsockets to use @return payload size
- L48 _public function_ `bool IsDone() const` — Whether we have written our entire payload yet or not @return whether we have written our entire payload yet or not
- L54 _public function_ `bool HasError() const` — Whether we have encountered an error or not @return whether we have encountered an error or not
- L57 _public member_ `const bool bIsBinary;` — Whether or not the packet is a binary packet, if not it is treated as a string
- L59 _public member_ `int32 BytesWritten;` — Number of bytes from Payload already written
- L61 _public member_ `TArray<uint8> Payload;` — Payload of the packet
- L63 _public member_ `bool bHasError;` — Has an error occurred while writing?

#### struct `FLwsReceiveBufferBinary`  
`struct FLwsReceiveBufferBinary`  
_L67-81_
- desc: Buffer for one incoming binary packet
- L75 _public prototype_ `FLwsReceiveBufferBinary(const uint8* Data, const int32 Size, const int32 InBytesRemaining);` — Constructor @param Data pointer to data to fill our buffer with @param Size size of Data @param InBytesRemaining Number of bytes remaining in the packet
- L78 _public member_ `TArray<uint8> Payload;` — Payload received
- L80 _public member_ `const int32 BytesRemaining;` — Number of bytes remaining in the packet

#### struct `FLwsReceiveBufferBinaryFragment`  
`struct FLwsReceiveBufferBinaryFragment`  
_L86-100_
- desc: Buffer for one incoming binary packet fragment
- L94 _public prototype_ `FLwsReceiveBufferBinaryFragment(const uint8* Data, const int32 Size, const bool bInIsLastFragment);` — Constructor @param Data pointer to data to fill our buffer with @param Size size of Data @param bInIsLastFragment Whether or not this is the last fragment
- L97 _public member_ `TArray<uint8> Payload;` — Payload received
- L99 _public member_ `const bool bIsLastFragment;` — Whether or not this is the last fragment

#### struct `FLwsReceiveBufferText`  
`struct FLwsReceiveBufferText`  
_L105-115_
- desc: Buffer for one incoming text packet, fully received
- L111 _public prototype_ `FLwsReceiveBufferText(FString&& InText);` — Constructor @param InText The packet contents
- L114 _public member_ `const FString Text;` — Text packet received

#### class `FLwsWebSocket`  
`class FLwsWebSocket : public IWebSocket , public TSharedFromThis<FLwsWebSocket>`  
_L121-362_
- inherits: `IWebSocket,TSharedFromThis<FLwsWebSocket>`
- L128 _public prototype_ `virtual ~FLwsWebSocket();` — Destructor
- L131 _public prototype_ `virtual void Connect() override;` — IWebSocket
- L132 _public prototype_ `virtual void Close(const int32 Code = 1000, const FString& Reason = FString()) override;`
- L134 _public function_ `virtual bool IsConnected() override`
- L139 _public prototype_ `virtual void Send(const FString& Data);`
- L140 _public prototype_ `virtual void Send(const void* Data, SIZE_T Size, bool bIsBinary) override;`
- L141 _public prototype_ `virtual void SetTextMessageMemoryLimit(uint64 TextMessageMemoryLimit) override;`
- L144 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketConnectedEvent, FWebSocketConnectedEvent);` — Delegate called when a web socket connection has been established
- L145 _public function_ `virtual FWebSocketConnectedEvent& OnConnected() override`
- L151 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketConnectionErrorEvent, FWebSocketConnectionErrorEvent);` — Delegate called when a web socket connection has errored
- L152 _public function_ `virtual FWebSocketConnectionErrorEvent& OnConnectionError() override`
- L158 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketClosedEvent, FWebSocketClosedEvent);` — Delegate called when a web socket connection has been closed
- L159 _public function_ `virtual FWebSocketClosedEvent& OnClosed() override`
- L165 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketMessageEvent, FWebSocketMessageEvent);` — Delegate called when a web socket text message has been received
- L166 _public function_ `virtual FWebSocketMessageEvent& OnMessage() override`
- L172 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketBinaryMessageEvent, FWebSocketBinaryMessageEvent);` — Delegate called when a web socket binary message has been received
- L173 _public function_ `virtual FWebSocketBinaryMessageEvent& OnBinaryMessage() override`
- L179 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketRawMessageEvent, FWebSocketRawMessageEvent);` — Delegate called when a any web socket message has been received
- L180 _public function_ `virtual FWebSocketRawMessageEvent& OnRawMessage() override`
- L186 _public prototype_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketMessageSentEvent, FWebSocketMessageSentEvent);`
- L187 _public function_ `virtual FWebSocketMessageSentEvent& OnMessageSent() override`
- L193 _public prototype_ `int LwsCallback(lws* Instance, lws_callback_reasons Reason, void* Data, size_t Length);` — Callback on events for our libwebsockets connection
- L198 _public prototype_ `void GameThreadTick();` — Tick on the game thread
- L203 _public prototype_ `void GameThreadFinalize();` — Handle being removed the game thread - trigger our OnClosed/OnConnectionError delegate
- L210 _public prototype_ `bool LwsThreadInitialize(struct lws_context &LwsContext);` — Setup to be run on the libwebsockets thread @param LwsContext libwebsockets context, should only be used when creating a libwebsockets socket @return true if we successfully initialized, false if we are done (should not be ticked on the libwebsockets thread)
- L215 _public prototype_ `void LwsThreadTick();` — Tick on the libwebsockets thread
- L225 _public prototype_ `FLwsWebSocket(FPrivateToken, const FString& Url, const TArray<FString>& Protocols, const FString& UpgradeHeader, uint64 TextMessageMemoryLimit);` — Constructor
- L232 _private prototype_ `void ConnectInternal(struct lws_context &LwsContext);` — Start connecting @param LwsContext libwebsockets context
- L235 _private prototype_ `void SendFromQueue();` — Send data from our pending outgoing queue
- L238 _private prototype_ `void ClearData();` — Clear our queues (does not send / process)
- L244 _private prototype_ `bool WriteBuffer(FLwsSendBuffer& Buffer);` — Write the specified send buffer @return true if the write was successful (not necessarily finished), false if an error occurred
- L249 _private member_ `FTransactionallySafeCriticalSection StateLock;` — Critical section to lock access to state and close request variables
- L271 _private prototype_ `static const TCHAR* ToString(const EState InState);` — Get string representation of EState
- L285 _private member_ `EState State;` — Our current state
- L287 _private member_ `FClosedReason ClosedReason;` — Reason for changing state
- L289 _private member_ `EState LastGameThreadState;` — Last state seen on the game thread
- L304 _private member_ `FCloseRequest CloseRequest;` — Close request from the owner of this web socket, to be processed on the libwebsockets thread
- L307 _private member_ `bool bWasSendQueueEmpty;` — Was the send queue empty last time we checked it on our thread?
- L310 _private member_ `FWebSocketConnectedEvent ConnectedEvent;` — Events
- L311 _private member_ `FWebSocketConnectionErrorEvent ConnectionErrorEvent;`
- L312 _private member_ `FWebSocketClosedEvent ClosedEvent;`
- L313 _private member_ `FWebSocketMessageEvent MessageEvent;`
- L314 _private member_ `FWebSocketBinaryMessageEvent BinaryMessageEvent;`
- L315 _private member_ `FWebSocketRawMessageEvent RawMessageEvent;`
- L316 _private member_ `FWebSocketMessageSentEvent OnMessageSentEvent;`
- L319 _private member_ `struct lws *LwsConnection;` — libwebsockets connection
- L321 _private member_ `FString Url;` — Url we are connecting to
- L323 _private member_ `TArray<FString> Protocols;` — Protocols to use with this connection
- L325 _private member_ `FString UpgradeHeader;` — The upgrade header(s) to send with the upgrade request
- L331 _private member_ `bool bWantsMessageEvents;` — Whether or not OnMessage was bound to when Connect() was called. For performance reasons if nothing was bound at Connect() time, we will never trigger OnMessage
- L336 _private member_ `bool bWantsRawMessageEvents;` — Whether or not OnRawMessage was bound to when Connect() was called. For performance reasons if nothing was bound at Connect() time, we will never trigger OnRawMessage
- L341 _private member_ `bool bWantsBinaryMessageEvents;` — Whether or not OnBinaryMessage was bound to when Connect() was called. For performance reasons if nothing was bound at Connect() time, we will never trigger OnBinaryMessage
- L345 _private member_ `FString ReceiveBuffer;` — Buffer of an incomplete packet received
- L347 _private member_ `TQueue<FLwsReceiveBufferBinaryPtr, EQueueMode::Spsc> ReceiveBinaryQueue;` — Received binary packets, waiting for delegates to be triggered on the game thread
- L349 _private member_ `TQueue<FLwsReceiveBufferBinaryFragmentPtr, EQueueMode::Spsc> ReceiveBinaryFragmentQueue;` — Received fragments of binary packets, waiting for delegates to be triggered on the game thread
- L351 _private member_ `TQueue<FLwsReceiveBufferTextPtr, EQueueMode::Spsc> ReceiveTextQueue;` — Received text packets, waiting for delegates to be triggered on the game thread
- L353 _private member_ `TQueue<FLwsSendBuffer*, EQueueMode::Spsc> SendQueue;` — Pending outgoing packets, populated by the game thread and processed on the libwebsockets thread
- L355 _private member_ `uint64 MaxTextMessageBufferSize;`
- L359 _private member_ `static int32 IncrementingIdentifier;` — Incrementing identifier to give each web socket a unique identifier
- L361 _private member_ `const int32 Identifier;` — Our unique identifier

#### struct `FLwsWebSocket::FPrivateToken`  
`struct FPrivateToken`  
_L219-219_
- desc: Private token only allows members or friends to call MakeShared
- L219 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### enum `FLwsWebSocket::EState`  
`enum class EState : uint8`  
_L252-268_
- desc: Possible state values
- L255 _public enumerator_ `None` — Constructed, nothing to do
- L257 _public enumerator_ `StartConnecting` — Awaiting connection start
- L259 _public enumerator_ `Connecting` — Connecting
- L261 _public enumerator_ `Connected` — Connected
- L263 _public enumerator_ `ClosingByRequest` — Closing (self initiated)
- L265 _public enumerator_ `Closed` — Closed
- L267 _public enumerator_ `Error` — Errored, nothing to do

#### struct `FLwsWebSocket::FClosedReason`  
`struct FClosedReason`  
_L274-282_
- desc: Structure containing reason for entering the close/error state
- L277 _public member_ `FString Reason;` — Descriptive reason for the state change
- L279 _public member_ `uint16 CloseStatus;` — Close status (for State=Closed)
- L281 _public member_ `bool bWasClean;` — Was close clean? (for State=Closed)

#### struct `FLwsWebSocket::FCloseRequest`  
`struct FCloseRequest`  
_L292-301_
- desc: Parameters from a close request from the owner of this web socket
- L295 _public function_ `FCloseRequest() : Code(0), Reason(nullptr)` — Constructor
- L298 _public member_ `int32 Code;` — Code specified when calling Close()
- L300 _public member_ `ANSICHAR *Reason;` — Reason specified when calling Close(), converted to ANSICHAR for libwebsockets

#### Free symbols / members of external scopes

- L83 _typedef_ `typedef TUniquePtr<FLwsReceiveBufferBinary> FLwsReceiveBufferBinaryPtr;`
- L102 _typedef_ `typedef TUniquePtr<FLwsReceiveBufferBinaryFragment> FLwsReceiveBufferBinaryFragmentPtr;`
- L117 _typedef_ `typedef TUniquePtr<FLwsReceiveBufferText> FLwsReceiveBufferTextPtr;`
- L144 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketConnectedEvent, FWebSocketConnectedEvent);` — Delegate called when a web socket connection has been established
- L151 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketConnectionErrorEvent, FWebSocketConnectionErrorEvent);` — Delegate called when a web socket connection has errored
- L158 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketClosedEvent, FWebSocketClosedEvent);` — Delegate called when a web socket connection has been closed
- L165 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketMessageEvent, FWebSocketMessageEvent);` — Delegate called when a web socket text message has been received
- L172 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketBinaryMessageEvent, FWebSocketBinaryMessageEvent);` — Delegate called when a web socket binary message has been received
- L179 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketRawMessageEvent, FWebSocketRawMessageEvent);` — Delegate called when a any web socket message has been received
- L186 _delegate_ `DECLARE_DERIVED_EVENT(FLwsWebSocket, IWebSocket::FWebSocketMessageSentEvent, FWebSocketMessageSentEvent);`
- L364 _typedef_ `typedef TSharedRef<FLwsWebSocket> FLwsWebSocketRef;`

### `Source/Runtime/Online/WebSockets/Private/Lws/LwsWebSocketsManager.h` (Private)


#### class `FLwsWebSocketsManager`  
`class FLwsWebSocketsManager : public IWebSocketsManager , public FRunnable , public FSingleThreadRunnable`  
_L28-141_
- inherits: `IWebSocketsManager,FRunnable,FSingleThreadRunnable`
- L36 _public prototype_ `FLwsWebSocketsManager();` — Default constructor
- L38 _public prototype_ `static FLwsWebSocketsManager& Get();`
- L44 _public prototype_ `void StartProcessingWebSocket(FLwsWebSocket* Socket);` — Start processing a websocket on our thread.  Called by FLwsWebSocket on the game thread. @param Socket websocket to process on our thread
- L50 _public prototype_ `void WakeService();` — Trigger/Wake up the websocket thread to process new requests. Note: This is a no-op if bPollService = true
- L53 _public prototype_ `virtual void InitWebSockets(TArrayView<const FString> Protocols) override;` — IWebSocketsManager
- L54 _public prototype_ `virtual void ShutdownWebSockets() override;`
- L55 _public prototype_ `virtual TSharedRef<IWebSocket> CreateWebSocket(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders) override;`
- L56 _public prototype_ `virtual void UpdateConfigs() override;`
- L61 _private prototype_ `virtual bool Init() override;`
- L62 _private prototype_ `virtual uint32 Run() override;`
- L63 _private prototype_ `virtual void Stop() override;`
- L64 _private prototype_ `virtual void Exit() override;`
- L72 _private function_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override` — FSingleThreadRunnable accessor for ticking this FRunnable when multi-threading is disabled. @return FSingleThreadRunnable Interface for this FRunnable object.
- L74 _private prototype_ `virtual void Tick() override;`
- L78 _private prototype_ `bool GameThreadTick(float DeltaTime);` — Game thread tick to flush events etc
- L80 _private prototype_ `static int StaticCallbackWrapper(lws* Connection, lws_callback_reasons Reason, void* UserData, void* Data, size_t Length);` — Static callback on events for a libwebsockets connection
- L82 _private prototype_ `int CallbackWrapper(lws* Connection, lws_callback_reasons Reason, void* UserData, void* Data, size_t Length);` — Callback on events for a libwebsockets connection
- L86 _private member_ `SSL_CTX* SslContext;` — OpenSSL context
- L89 _private member_ `lws_context* LwsContext;` — libwebsockets context
- L91 _private member_ `TArray<lws_protocols> LwsProtocols;` — array of protocols that we have registered with libwebsockets
- L94 _private member_ `TArray<TSharedRef<FLwsWebSocket>> Sockets;` — Array of all WebSockets we know about.  Shared ref count modifications only occurs on the game thread
- L96 _private member_ `TArray<FLwsWebSocket*> SocketsTickingOnThread;` — Array of all WebSockets we are ticking on our thread
- L98 _private member_ `TQueue<FLwsWebSocket*> SocketsToStart;` — Queue of WebSockets to start processing on our thread
- L100 _private member_ `TQueue<FLwsWebSocket*> SocketsToStop;` — Queue of WebSockets that we are done processing on our thread and want to be removed from our Sockets array
- L102 _private member_ `TArray<FLwsWebSocket*> SocketsDestroyedDuringService;` — Array of WebSockets destroyed during our call to lws_service, to be added to SocketsToStop after lws_service completes
- L105 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — Delegate for callbacks to GameThreadTick
- L108 _private member_ `FDelegateHandle OnChildEndFramePostForkHandle;` — Delegate handle for FCoreDelegates::OnChildEndFramePostFork
- L112 _private member_ `FRunnableThread* Thread;` — Pointer to Runnable Thread
- L115 _private member_ `FThreadSafeCounter ExitRequest;` — signal request to stop and exit thread
- L124 _private member_ `bool bPollService = false;`
- L126 _private member_ `bool bPollService = true;`
- L130 _private member_ `int32 ServiceTimeoutMs = MAX_int32;` — Timeout value in milliseconds to be used by lws_service when bPollService is false
- L133 _private member_ `double ThreadTargetFrameTimeInSeconds = 1.0f / 30.0f;` — Target frame time for our thread's tick
- L135 _private member_ `double ThreadMinimumSleepTimeInSeconds = 0.0f;` — Minimum time to sleep in our thread's tick, even if the sleep makes us exceed our target frame time
- L137 _private member_ `bool bDisableDomainAllowlist = false;`
- L138 _private member_ `bool bDisableCertValidation = false;`

### `Source/Runtime/Online/WebSockets/Private/PlatformWebSocket.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `typedef WEBSOCKETS_MANAGER_PLATFORM_CLASS FPlatformWebSocketsManager;`

### `Source/Runtime/Online/WebSockets/Private/WinHttp/Support/WinHttpConnectionWebSocket.h` (Private)


#### class `FWinHttpConnectionWebSocket`  
`class FWinHttpConnectionWebSocket : public FWinHttpConnectionHttp`  
_L16-140_
- inherits: `FWinHttpConnectionHttp`
- L20 _public prototype_ `static TSharedPtr<FWinHttpConnectionWebSocket, ESPMode::ThreadSafe> CreateWebSocketConnection( FWinHttpSession& Session, const FString& RequestUrl, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders);`
- L26 _public prototype_ `virtual ~FWinHttpConnectionWebSocket() = default;`
- L27 _public prototype_ `FWinHttpConnectionWebSocket(const FWinHttpConnectionWebSocket& Other) = delete;`
- L28 _public prototype_ `FWinHttpConnectionWebSocket(FWinHttpConnectionWebSocket&& Other) = delete;`
- L29 _public prototype_ `FWinHttpConnectionWebSocket& operator=(const FWinHttpConnectionWebSocket& Other) = delete;`
- L30 _public prototype_ `FWinHttpConnectionWebSocket& operator=(FWinHttpConnectionWebSocket&& Other) = delete;`
- L33 _public prototype_ `virtual bool IsValid() const override;`
- L34 _public prototype_ `virtual void PumpMessages() override;`
- L35 _public prototype_ `virtual void PumpStates() override;`
- L40 _public prototype_ `void SetWebSocketConnectedHandler(FWinHttpConnectionWebSocketOnConnected&& Handler);`
- L41 _public prototype_ `void SetWebSocketMessageHandler(FWinHttpConnectionWebSocketOnMessage&& Handler);`
- L42 _public prototype_ `void SetWebSocketClosedHandler(FWinHttpConnectionWebSocketOnClosed&& Handler);`
- L51 _public prototype_ `bool IsConnected() const;` — Check if our connection has been fully established. If this returns true, it's safe to start sending messages. @return True if our connection is active and fully established, false otherwise
- L61 _public prototype_ `bool SendMessage(EWebSocketMessageType MessageType, TArray<uint8>&& Message);` — Sends a websocket message if we are in a connected state. Delivery is not gaurenteed even if this returns true. @param MessageType The type of message being sent @param Message The message to send to the peer
- L69 _public prototype_ `bool CloseConnection(const uint16 Code, const FString& Reason);` — Gracefully request the connection to close with the provided code and reason. @param Code The close code to send to the server @param Reason The reason we are closing
- L72 _protected prototype_ `FWinHttpConnectionWebSocket( FWinHttpSession& Session, const FString& RequestUrl, const bool bIsSecure, const FString& Domain, const TOptional<uint16> Port, const FString& PathAndQuery, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders);`
- L82 _protected prototype_ `bool IsReadInProgress() const;`
- L83 _protected prototype_ `void ReadData(const int32 MaxMessagesToRead);`
- L84 _protected prototype_ `bool IsWriteInProgress() const;`
- L85 _protected prototype_ `void WriteData(const int32 MaxMessagesToWrite);`
- L88 _protected prototype_ `virtual bool FinishRequest(const EHttpRequestStatus::Type FinalState) override;`
- L89 _protected prototype_ `virtual void HandleHeadersAvailable() override;`
- L90 _protected prototype_ `virtual void HandleHandleClosing() override;`
- L94 _protected prototype_ `void HandleWebSocketReadComplete(const uint32 BytesRead, const EWebSocketMessageType MessageType, const bool bIsFragment);` — Async Events
- L95 _protected prototype_ `void HandleWebSocketWriteComplete(const uint32 BytesWritten, const EWebSocketMessageType MessageType);`
- L96 _protected prototype_ `void HandleWebSocketCloseComplete();`
- L97 _protected prototype_ `void HandleWebSocketRequestError(const int32 WebSocketOperationId, const uint32 ErrorCode);`
- L114 _private prototype_ `void HandleWebSocketStatusCallback(HINTERNET ResourceHandle, EWinHttpCallbackStatus Status, void* StatusInformation, uint32 StatusInformationLength);` — Handle receiving WebSocket status callbacks from WinHttp @param ResourceHandle The handle of the resource which generated this Status @param InternetStatus The event that is being triggered @param StatusInformation Pointer to optional data for this event, if there is any @param StatusInformationLength The length of data available to read in StatusInformation or 0 if not used
- L120 _protected member_ `FWinHttpHandle WebSocketHandle;`
- L122 _protected member_ `TOptional<EWebSocketMessageType> ReceiveFragmentMessageType;`
- L123 _protected member_ `TArray<uint8> ReceiveBuffer;`
- L124 _protected member_ `int32 ReceiveBufferBytesWritten = 0;`
- L125 _protected member_ `bool bWebSocketReadInProgress = false;`
- L127 _protected member_ `TQueue<TUniquePtr<FPendingWebSocketMessage>, EQueueMode::Spsc> SentMessagesQueue;`
- L128 _protected member_ `TUniquePtr<FPendingWebSocketMessage> PendingMessage;`
- L129 _protected member_ `bool bWebSocketWriteInProgress = false;`
- L131 _protected member_ `FWinHttpConnectionWebSocketOnConnected OnConnectedHandler;`
- L132 _protected member_ `bool bHasPendingConnectedEvent = false;`
- L134 _protected member_ `FWinHttpConnectionWebSocketOnMessage OnMessageHandler;`
- L135 _protected member_ `TQueue<FPendingWebSocketMessage, EQueueMode::Spsc> ReceieveMessageQueue;`
- L137 _protected member_ `FWinHttpConnectionWebSocketOnClosed OnClosedHandler;`
- L138 _protected member_ `TOptional<FWebSocketCloseInfo> SentCloseInfo;`
- L139 _protected member_ `TOptional<FWebSocketCloseInfo> ReceivedCloseInfo;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE(FWinHttpConnectionWebSocketOnConnected);`
- L12 _prototype_ `DECLARE_DELEGATE(FWinHttpConnectionWebSocketOnConnected);`
- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FWinHttpConnectionWebSocketOnMessage, EWebSocketMessageType , TArray<uint8>& );`
- L13 _prototype_ `DECLARE_DELEGATE_TwoParams(FWinHttpConnectionWebSocketOnMessage, EWebSocketMessageType , TArray<uint8>& );`
- L14 _delegate_ `DECLARE_DELEGATE_ThreeParams(FWinHttpConnectionWebSocketOnClosed, uint16 , const FString& , bool );`
- L14 _prototype_ `DECLARE_DELEGATE_ThreeParams(FWinHttpConnectionWebSocketOnClosed, uint16 , const FString& , bool );`

### `Source/Runtime/Online/WebSockets/Private/WinHttp/Support/WinHttpWebSocketErrorHelper.h` (Private)


#### class `FWinHttpWebSocketErrorHelper`  
`class FWinHttpWebSocketErrorHelper`  
_L9-57_
- L17 _public prototype_ `static void LogWinHttpWebSocketCompleteUpgradeFailure(const uint32 ErrorCode);` — Log that an WinHttpWebSocketCompleteUpgrade call failed with the specified ErrorCode @param ErrorCode The error that occured
- L24 _public prototype_ `static void LogWinHttpWebSocketReceiveFailure(const uint32 ErrorCode);` — Log that an WinHttpWebSocketReceive call failed with the specified ErrorCode @param ErrorCode The error that occured
- L31 _public prototype_ `static void LogWinHttpWebSocketSendFailure(const uint32 ErrorCode);` — Log that an WinHttpWebSocketSend call failed with the specified ErrorCode @param ErrorCode The error that occured
- L38 _public prototype_ `static void LogWinHttpWebSocketCloseFailure(const uint32 ErrorCode);` — Log that an WinHttpWebSocketClose call failed with the specified ErrorCode @param ErrorCode The error that occured
- L45 _public prototype_ `static void LogWinHttpWebSocketShutdownFailure(const uint32 ErrorCode);` — Log that an WinHttpWebSocketShutdown call failed with the specified ErrorCode @param ErrorCode The error that occured
- L52 _public prototype_ `static void LogWinHttpWebSocketQueryCloseStatusFailure(const uint32 ErrorCode);` — Log that an WinHttpWebSocketQueryCloseStatus call failed with the specified ErrorCode @param ErrorCode The error that occured
- L56 _private prototype_ `FWinHttpWebSocketErrorHelper() = delete;` — This class should not be instantiated

### `Source/Runtime/Online/WebSockets/Private/WinHttp/Support/WinHttpWebSocketTypes.h` (Private)


#### enum `EWebSocketMessageType`  
`enum class EWebSocketMessageType : uint8`  
_L17-21_
- desc: Structure to represent if a WebSocket message is UTF8 or Binary
- L19 _public enumerator_ `Binary`
- L20 _public enumerator_ `Utf8`

#### struct `FPendingWebSocketMessage`  
`struct FPendingWebSocketMessage`  
_L31-42_
- desc: Structure to hold a websocket message to be read or sent
- L33 _public prototype_ `FPendingWebSocketMessage() = default;`
- L34 _public prototype_ `FPendingWebSocketMessage(EWebSocketMessageType InMessageType, TArray<uint8>&& InData);`
- L35 _public prototype_ `FPendingWebSocketMessage(EWebSocketMessageType InMessageType, const TArray<uint8>& InData);`
- L39 _public member_ `EWebSocketMessageType MessageType = EWebSocketMessageType::Binary;` — The type of message Data is
- L41 _public member_ `TArray<uint8> Data;` — The actual payload of the message

#### struct `FWebSocketCloseInfo`  
`struct FWebSocketCloseInfo`  
_L47-57_
- desc: Structure to hold information related to close messages from the server or from the client
- L49 _public prototype_ `FWebSocketCloseInfo(uint16 InCode, FString&& InReason);`
- L50 _public prototype_ `FWebSocketCloseInfo(uint16 InCode, const FString& InReason);`
- L54 _public member_ `uint16 Code = 0u;` — Numeric code on the status of the closure
- L56 _public member_ `FString Reason;` — String reason on why the connection was closed

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_WEBSOCKET_CLOSE_NORMAL_CLOSURE 1000` — Status code for sucessful websocket closure
- L12 _macro_ `#define UE_WEBSOCKET_CLOSE_APP_FAILURE 1006` — Status code for application-failure websocket closure
- L26 _prototype_ `const TCHAR* LexToString(const EWebSocketMessageType MessageType);` — Convert a WebSocketMessageType into a string for logging

### `Source/Runtime/Online/WebSockets/Private/WinHttp/WinHttpWebSocket.h` (Private)


#### enum `EWebSocketConnectionState`  
`enum class EWebSocketConnectionState : uint8`  
_L14-28_
- L17 _public enumerator_ `NotStarted` — We have not started a connection yet
- L19 _public enumerator_ `Connecting` — We are in the process of connecting
- L21 _public enumerator_ `Connected` — We have an active valid connection
- L23 _public enumerator_ `FailedToConnect` — We failed to connect (or couldn't connect) last time we tried
- L25 _public enumerator_ `Disconnected` — We were forcefully disconnected from a valid connection
- L27 _public enumerator_ `Closed` — We gracefully disconnected from a valid connection

#### class `FWinHttpWebSocket`  
`class FWinHttpWebSocket : public IWebSocket , public TSharedFromThis<FWinHttpWebSocket>`  
_L32-97_
- inherits: `IWebSocket,TSharedFromThis<FWinHttpWebSocket>`
- L37 _public prototype_ `FWinHttpWebSocket(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders);`
- L38 _public prototype_ `virtual ~FWinHttpWebSocket();`
- L41 _public prototype_ `virtual void Connect() override final;`
- L42 _public prototype_ `virtual void Close(const int32 Code = 1000, const FString& Reason = FString()) override final;`
- L43 _public prototype_ `virtual bool IsConnected() override final;`
- L44 _public prototype_ `virtual void Send(const FString& Data) override final;`
- L45 _public prototype_ `virtual void Send(const void* Data, SIZE_T Size, bool bIsBinary) override final;`
- L46 _public prototype_ `virtual void SetTextMessageMemoryLimit(uint64 TextMessageMemoryLimit) override final;`
- L47 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketConnectedEvent, FWebSocketConnectedEvent);`
- L48 _public prototype_ `virtual FWebSocketConnectedEvent& OnConnected() override final;`
- L49 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketConnectionErrorEvent, FWebSocketConnectionErrorEvent);`
- L50 _public prototype_ `virtual FWebSocketConnectionErrorEvent& OnConnectionError() override final;`
- L51 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketClosedEvent, FWebSocketClosedEvent);`
- L52 _public prototype_ `virtual FWebSocketClosedEvent& OnClosed() override final;`
- L53 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketMessageEvent, FWebSocketMessageEvent);`
- L54 _public prototype_ `virtual FWebSocketMessageEvent& OnMessage() override final;`
- L55 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketRawMessageEvent, FWebSocketRawMessageEvent);`
- L56 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketBinaryMessageEvent, FWebSocketBinaryMessageEvent);`
- L57 _public prototype_ `virtual FWebSocketBinaryMessageEvent& OnBinaryMessage() override final;`
- L58 _public prototype_ `virtual FWebSocketRawMessageEvent& OnRawMessage() override final;`
- L59 _public prototype_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketMessageSentEvent, FWebSocketMessageSentEvent);`
- L60 _public prototype_ `virtual FWebSocketMessageSentEvent& OnMessageSent() override final;`
- L64 _protected prototype_ `void HandleSessionCreated(FWinHttpSession* HttpSessionPtr);`
- L65 _protected prototype_ `void HandleCloseComplete(const EWebSocketConnectionState NewState, const uint16 Code, const FString& Reason);`
- L68 _protected prototype_ `void GameThreadTick();` — FHttpConnectionWebSocket Callback Handling
- L71 _protected prototype_ `void HandleWebSocketConnected();`
- L72 _protected prototype_ `void HandleWebSocketMessage(EWebSocketMessageType MessageType, TArray<uint8>& MessagePayload);`
- L73 _protected prototype_ `void HandleWebSocketClosed(uint16 Code, const FString& Reason, bool bGracefulDisconnect);`
- L77 _protected member_ `FString Url;`
- L78 _protected member_ `TArray<FString> Protocols;`
- L79 _protected member_ `TMap<FString, FString> UpgradeHeaders;`
- L81 _protected member_ `EWebSocketConnectionState State = EWebSocketConnectionState::NotStarted;`
- L82 _protected member_ `bool bSessionCreationInProgress = false;`
- L83 _protected member_ `bool bCloseRequested = false;`
- L84 _protected member_ `TOptional<int32> QueuedCloseCode;`
- L85 _protected member_ `TOptional<FString> QueuedCloseReason;`
- L86 _protected member_ `TSharedPtr<FWinHttpConnectionWebSocket, ESPMode::ThreadSafe> WebSocket;`
- L88 _protected member_ `FWebSocketConnectedEvent OnConnectedHandler;`
- L89 _protected member_ `FWebSocketConnectionErrorEvent OnErrorHandler;`
- L90 _protected member_ `FWebSocketClosedEvent OnClosedHandler;`
- L91 _protected member_ `FWebSocketMessageEvent OnMessageHandler;`
- L92 _protected member_ `FWebSocketBinaryMessageEvent BinaryMessageHandler;`
- L93 _protected member_ `FWebSocketRawMessageEvent OnRawMessageHandler;`
- L94 _protected member_ `FWebSocketMessageSentEvent OnMessageSentHandler;`

#### Free symbols / members of external scopes

- L30 _prototype_ `const TCHAR* LexToString(const EWebSocketConnectionState);`
- L47 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketConnectedEvent, FWebSocketConnectedEvent);`
- L49 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketConnectionErrorEvent, FWebSocketConnectionErrorEvent);`
- L51 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketClosedEvent, FWebSocketClosedEvent);`
- L53 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketMessageEvent, FWebSocketMessageEvent);`
- L55 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketRawMessageEvent, FWebSocketRawMessageEvent);`
- L56 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketBinaryMessageEvent, FWebSocketBinaryMessageEvent);`
- L59 _delegate_ `DECLARE_DERIVED_EVENT(FWinHttpWebSocket, IWebSocket::FWebSocketMessageSentEvent, FWebSocketMessageSentEvent);`

### `Source/Runtime/Online/WebSockets/Private/WinHttp/WinHttpWebSocketsManager.h` (Private)


#### class `FWinHttpWebSocketsManager`  
`class FWinHttpWebSocketsManager : public IWebSocketsManager`  
_L14-37_
- inherits: `IWebSocketsManager`
- L18 _public prototype_ `virtual ~FWinHttpWebSocketsManager() = default;`
- L21 _public prototype_ `virtual void InitWebSockets(TArrayView<const FString> Protocols) override;`
- L22 _public prototype_ `virtual void ShutdownWebSockets() override;`
- L23 _public prototype_ `virtual TSharedRef<IWebSocket> CreateWebSocket(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders) override;`
- L27 _protected prototype_ `bool GameThreadTick(float DeltaTime);`
- L29 _protected prototype_ `void InitHttpManager();`
- L32 _protected member_ `FTSTicker::FDelegateHandle TickHandle;`
- L34 _protected member_ `FWinHttpHttpManager* WinHttpHttpManager = nullptr;`
- L36 _protected member_ `TArray<TWeakPtr<FWinHttpWebSocket>> ActiveWebSockets;`

### `Source/Runtime/Online/WebSockets/Public/IWebSocket.h` (Public)


#### class `IWebSocket`  
`class IWebSocket`  
_L6-102_
- L10 _public prototype_ `virtual ~IWebSocket() = default;`
- L16 _public prototype_ `virtual void Connect() = 0;` — Initiate a client connection to the server. Use this after setting up event handlers or to reconnect after connection errors.
- L23 _public prototype_ `virtual void Close(int32 Code = 1000, const FString& Reason = FString()) = 0;` — Close the current connection. @param Code Numeric status code explaining why the connection is being closed. Default is 1000. See WebSockets spec for valid codes. @param Reason Human readable string explaining why the connection is closing.
- L28 _public prototype_ `virtual bool IsConnected() = 0;` — Inquire if this web socket instance is connected to a server.
- L34 _public prototype_ `virtual void Send(const FString& Data) = 0;` — Transmit data over the connection. @param Data data to be sent as a UTF-8 encoded string.
- L42 _public prototype_ `virtual void Send(const void* Data, SIZE_T Size, bool bIsBinary = false) = 0;` — Transmit data over the connection. @param Data raw binary data to be sent. @param Size number of bytes to send. @param bIsBinary set to true to send binary frame to the peer instead of text.
- L49 _public prototype_ `virtual void SetTextMessageMemoryLimit(uint64 TextMessageMemoryLimit) = 0;` — Optionally change memory limit for receiving UTF-8 text on this socket. Default from config TextMessageMemoryLimit under [WebSockets] or 1MB. @param TextMessageMemoryLimit new buffer size upper limit in bytes.
- L55 _public prototype_ `DECLARE_EVENT(IWebSocket, FWebSocketConnectedEvent);` — Delegate called when a web socket connection has been established successfully.
- L56 _public prototype_ `virtual FWebSocketConnectedEvent& OnConnected() = 0;`
- L62 _public prototype_ `DECLARE_EVENT_OneParam(IWebSocket, FWebSocketConnectionErrorEvent, const FString& );` — Delegate called when a web socket connection could not be established.
- L63 _public prototype_ `virtual FWebSocketConnectionErrorEvent& OnConnectionError() = 0;`
- L69 _public prototype_ `DECLARE_EVENT_ThreeParams(IWebSocket, FWebSocketClosedEvent, int32 , const FString& , bool );` — Delegate called when a web socket connection has been closed.
- L70 _public prototype_ `virtual FWebSocketClosedEvent& OnClosed() = 0;`
- L77 _public prototype_ `DECLARE_EVENT_OneParam(IWebSocket, FWebSocketMessageEvent, const FString& );` — Delegate called when a web socket text message has been received. Assumes the payload is encoded as UTF8. For binary data, bind to OnRawMessage instead.
- L78 _public prototype_ `virtual FWebSocketMessageEvent& OnMessage() = 0;`
- L84 _public prototype_ `DECLARE_EVENT_ThreeParams(IWebSocket, FWebSocketBinaryMessageEvent, const void* , SIZE_T , bool );` — Delegate called when web socket binary data has been received. bIsLastFragment will be true if it is the last fragment of the current packet.
- L85 _public prototype_ `virtual FWebSocketBinaryMessageEvent& OnBinaryMessage() = 0;`
- L93 _public prototype_ `DECLARE_EVENT_ThreeParams(IWebSocket, FWebSocketRawMessageEvent, const void* , SIZE_T , SIZE_T );` — Delegate called when any web socket data has been received. May be called multiple times for a message if the message was split into multiple frames. This is called for every web socket fragment. BytesRemaining is the number of bytes left in the current fragment.
- L94 _public prototype_ `virtual FWebSocketRawMessageEvent& OnRawMessage() = 0;`
- L100 _public prototype_ `DECLARE_EVENT_OneParam(IWebSocket, FWebSocketMessageSentEvent, const FString& );` — Delegate called when a web socket text message has been sent. Assume UTF-8 encoding.
- L101 _public prototype_ `virtual FWebSocketMessageSentEvent& OnMessageSent() = 0;`

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_EVENT(IWebSocket, FWebSocketConnectedEvent);` — Delegate called when a web socket connection has been established successfully.
- L62 _delegate_ `DECLARE_EVENT_OneParam(IWebSocket, FWebSocketConnectionErrorEvent, const FString& );` — Delegate called when a web socket connection could not be established.
- L69 _delegate_ `DECLARE_EVENT_ThreeParams(IWebSocket, FWebSocketClosedEvent, int32 , const FString& , bool );` — Delegate called when a web socket connection has been closed.
- L77 _delegate_ `DECLARE_EVENT_OneParam(IWebSocket, FWebSocketMessageEvent, const FString& );` — Delegate called when a web socket text message has been received. Assumes the payload is encoded as UTF8. For binary data, bind to OnRawMessage instead.
- L84 _delegate_ `DECLARE_EVENT_ThreeParams(IWebSocket, FWebSocketBinaryMessageEvent, const void* , SIZE_T , bool );` — Delegate called when web socket binary data has been received. bIsLastFragment will be true if it is the last fragment of the current packet.
- L93 _delegate_ `DECLARE_EVENT_ThreeParams(IWebSocket, FWebSocketRawMessageEvent, const void* , SIZE_T , SIZE_T );` — Delegate called when any web socket data has been received. May be called multiple times for a message if the message was split into multiple frames. This is called for every web socket fragment. BytesRemaining is the number of bytes left in the current fragment.
- L100 _delegate_ `DECLARE_EVENT_OneParam(IWebSocket, FWebSocketMessageSentEvent, const FString& );` — Delegate called when a web socket text message has been sent. Assume UTF-8 encoding.

### `Source/Runtime/Online/WebSockets/Public/IWebSocketsManager.h` (Public)


#### class `IWebSocketsManager`  
`class IWebSocketsManager`  
_L10-43_
- L17 _public prototype_ `virtual void InitWebSockets(TArrayView<const FString> Protocols) = 0;` — Web sockets start-up: call before creating any web sockets
- L23 _public prototype_ `virtual void ShutdownWebSockets() = 0;` — Web sockets teardown: call at shutdown, in particular after all use of SSL has finished
- L32 _public prototype_ `virtual TSharedRef<IWebSocket> CreateWebSocket(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders) = 0;` — Instantiates a new web socket for the current platform @param Url The URL to which to connect; this should be the URL to which the WebSocket server will respond. @param Protocols a list of protocols the client will handle. @return new IWebSocket instance
- L37 _public prototype_ `virtual ~IWebSocketsManager() = default;` — Virtual destructor
- L42 _public function_ `virtual void UpdateConfigs()` — Update configuration. Called when config has been updated and we need to apply any changes.

### `Source/Runtime/Online/WebSockets/Public/WebSocketsLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSockets, Warning, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSockets, Warning, All);`

### `Source/Runtime/Online/WebSockets/Public/WebSocketsModule.h` (Public)


#### class `FWebSocketsModule`  
`class FWebSocketsModule : public IModuleInterface`  
_L21-104_
- inherits: `IModuleInterface`
- desc: Module for web socket implementations
- L28 _public function_ `FWebSocketsModule() #if WITH_WEBSOCKETS : WebSocketsManager(nullptr) #endif` — FWebSocketModule
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWebSocketCreated, const TSharedPtr<class IWebSocket>& , const TArray<FString>& , const FString& );` — Delegate fired when a web socket is created. @param WebSocket Reference to newly created web socket @param Protocols Array of protocols on web socket @param Url Url the web socket is connected to
- L43 _public member_ `FOnWebSocketCreated OnWebSocketCreated;`
- L52 _public prototype_ `static FWebSocketsModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L76 _private prototype_ `static FString BuildUpgradeHeader(const TMap<FString, FString>& Headers);`
- L84 _private prototype_ `virtual void StartupModule() override;` — Called when WebSockets module is loaded Initialize implementation specific parts of WebSockets handling
- L90 _private prototype_ `virtual void ShutdownModule() override;` — Called when WebSockets module is unloaded Shutdown implementation specific parts of WebSockets handling
- L94 _private member_ `IWebSocketsManager* WebSocketsManager;` — Manages active web sockets
- L99 _private prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);` — Delegate for config file changes.
- L103 _private member_ `static FWebSocketsModule* Singleton;` — singleton for the module while loaded and available

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWebSocketCreated, const TSharedPtr<class IWebSocket>& , const TArray<FString>& , const FString& );` — Delegate fired when a web socket is created. @param WebSocket Reference to newly created web socket @param Protocols Array of protocols on web socket @param Url Url the web socket is connected to
