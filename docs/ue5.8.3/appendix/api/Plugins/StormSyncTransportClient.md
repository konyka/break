# Plugins / StormSyncTransportClient

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient`
- headers: 9; symbols: 207
- symbol kinds: class=8, delegate=9, enum=1, enumerator=4, function=12, member=47, prototype=122, struct=2, typedef=2
- PrivateDependencyModuleNames: Engine, Json, JsonUtilities, Networking, Sockets, StormSyncCore
- PublicDependencyModuleNames: Core, CoreUObject, StormSyncTransportCore

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/Services/StormSyncPullMessageService.h` (Private)


#### class `FStormSyncPullMessageService`  
`class FStormSyncPullMessageService : public IStormSyncTransportMessageService`  
_L28-98_
- inherits: `IStormSyncTransportMessageService`
- desc: Message service handler for pull related messages This service handles all "pull" related messages and message bus / tcp transaction. Example use case: Client 1 wants to pull some assets from Client 2 1. Client 1 sends a PullRequest message (FStormSyncTransportPullRequest, via RequestPullPackages()) 2. Client 2 receives PullRequest message (via HandlePullRequestMessage()) 2.1 Client 2 compares the list of file dependency states in incoming message against local file states 2.2 Client 2 prepares a response with a list of "modifiers" 2.3 Client 2 opens a tcp connection and sends a buffer with all the files with mismatched state 2.4 Client 2, on tcp transfer completion, sends a final PullResponse message to Client 1 3. Client 1 receives the PullResponse message from Client 2, and invokes the stored delegate in phase 1. from the GUID that was passed back to back from message to message
- L31 _public prototype_ `explicit FStormSyncPullMessageService(TSharedPtr<IStormSyncTransportLocalEndpoint, ESPMode::ThreadSafe> InLocalEndpoint);`
- L32 _public prototype_ `virtual ~FStormSyncPullMessageService();`
- L35 _public prototype_ `virtual void InitializeMessageEndpoint(FMessageEndpointBuilder& InEndpointBuilder) override;`
- L39 _public prototype_ `void RequestPullPackages(const FMessageAddress& InRemoteAddress, const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FOnStormSyncPullComplete& InDoneDelegate);` — Sends a pull synchronization request to the passed in remote address, and waits for the remote to respond triggering the completion delegate
- L42 _public prototype_ `void AbortPullRequest(const FGuid& InPullRequestId);` — Abort a request using the GUID previously obtained via a call to RequestPullPackages
- L45 _private member_ `TWeakPtr<IStormSyncTransportLocalEndpoint> LocalEndpointWeak;` — Holds the client local endpoint.
- L48 _private member_ `FCriticalSection HandlersCriticalSection;` — Critical section preventing multiple threads from adding / removing handlers simultaneously
- L51 _private member_ `TMap<FGuid, FOnStormSyncPullComplete> PendingResponseHandlers;` — Handlers awaiting their resultant message bus response
- L54 _private prototype_ `void AddResponseHandler(const FGuid& InId, const FOnStormSyncPullComplete& InDelegate);` — Helper to register a completion delegate protected by a critical section
- L57 _private prototype_ `void HandlePullRequestMessage(const FStormSyncTransportPullRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPushRequest messages
- L60 _private prototype_ `void HandlePullResponseMessage(const FStormSyncTransportPullResponse& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPullResponse messages
- L63 _private prototype_ `void HandleTransferComplete(const FStormSyncTransportPullResponse InResponseMessage, const FMessageAddress InRemoteAddress) const;` — Callback handler when sending tcp buffer to handle transfer completion
- L70 _private prototype_ `void SendPullResponse(const FStormSyncTransportPullResponse& InResponsePayload, const FMessageAddress& InRemoteAddress) const;` — Helper to send a PullResponse to the specified remote address recipient. If the response message is tagged with the proper GUID, remote will invoke the stored delegate (if any) with the response.
- L77 _private prototype_ `bool ValidateIncomingPullMessage(const FStormSyncTransportPullRequest& InMessage, FText& OutErrorText) const;` — Prior to preparing a buffer to send, this method can be used to validate an incoming message and return an error in case of: - Missing package names on disk (remote wants to pull an asset that doesn't exist on this editor instance)
- L86 _private prototype_ `static FStormSyncTransportPullResponse CreatePullResponsePayload(const FStormSyncTransportPullRequest& InPullMessage, const bool bInWithModifiers = false);` — Helper to create a pull response payload and initialize its field based on incoming pull message @param InPullMessage Incoming pull message to use to initialize field of payload @param bInWithModifiers When set to true, payload modifiers will be filled (careful, this operation might be slow and may be better to be called within an async task)
- L89 _private prototype_ `static FStormSyncTransportPullResponse CreatePullResponsePayload(const TArray<FName>& InPackageNames, const FStormSyncPackageDescriptor& InPackageDescriptor);` — Static helper to create a new response payload, in case of an early error during the request phase
- L94 _private prototype_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const;` — Returns message endpoint associated with local endpoint
- L97 _private prototype_ `TSharedPtr<FStormSyncTransportClientEndpoint> GetLocalEndpoint() const;` — Returns local endpoint from locally cached WeakPtr

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/Services/StormSyncPushMessageService.h` (Private)


#### class `FStormSyncPushMessageService`  
`class FStormSyncPushMessageService : public IStormSyncTransportMessageService`  
_L13-66_
- inherits: `IStormSyncTransportMessageService`
- desc: Message service handler for push related messages
- L16 _public prototype_ `explicit FStormSyncPushMessageService(TSharedPtr<IStormSyncTransportLocalEndpoint, ESPMode::ThreadSafe> InLocalEndpoint);`
- L20 _public prototype_ `virtual void InitializeMessageEndpoint(FMessageEndpointBuilder& InEndpointBuilder) override;`
- L24 _public prototype_ `void RequestPushPackages(const FMessageAddress& InRemoteAddress, const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FOnStormSyncPushComplete& InDoneDelegate);` — Sends a push synchronization request to the passed in remote address, and waits for the remote to respond triggering the completion delegate
- L27 _public prototype_ `void AbortPushRequest(const FGuid& InPushRequestId);` — Abort a request using the GUID previously obtained via a call to RequestPushPackages
- L31 _private member_ `TWeakPtr<IStormSyncTransportLocalEndpoint> LocalEndpointWeak;` — Holds the client local endpoint.
- L34 _private member_ `FCriticalSection HandlersCriticalSection;` — Critical section preventing multiple threads from adding / removing handlers simultaneously
- L37 _private member_ `TMap<FGuid, FOnStormSyncPushComplete> PendingResponseHandlers;` — Handlers awaiting their resultant message bus response
- L40 _private prototype_ `void AddResponseHandler(const FGuid& InId, const FOnStormSyncPushComplete& InDelegate);` — Helper to register a completion delegate protected by a critical section
- L43 _private prototype_ `void HandlePushRequestMessage(const FStormSyncTransportPushRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPushRequest messages
- L46 _private prototype_ `void HandlePushResponseMessage(const FStormSyncTransportPushResponse& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPushResponse messages
- L49 _private prototype_ `void HandleTransferComplete(const FStormSyncTransportPushResponse InResponseMessage);` — Callback handler when sending tcp buffer to handle transfer completion
- L56 _private prototype_ `void InvokePendingResponseHandler(const TSharedPtr<FStormSyncTransportPushResponse, ESPMode::ThreadSafe>& InResponseMessage);` — Helper to invoke a pending response handler based on the provided message (and ID) If a previously stored delegate is matching the message ID in PendingResponseHandlers, it will be invoked and cleaned up.
- L59 _private prototype_ `static FStormSyncTransportPushResponse CreatePushResponsePayload(const TArray<FName>& InPackageNames, const FStormSyncPackageDescriptor& InPackageDescriptor);` — Static helper to create a new response payload, in case of an early error during the request phase
- L62 _private prototype_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const;` — Returns message endpoint associated with local endpoint
- L65 _private prototype_ `TSharedPtr<FStormSyncTransportClientEndpoint> GetLocalEndpoint() const;` — Returns local endpoint from locally cached WeakPtr

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/Services/StormSyncStatusMessageService.h` (Private)


#### class `FStormSyncStatusMessageService`  
`class FStormSyncStatusMessageService : public IStormSyncTransportMessageService`  
_L12-54_
- inherits: `IStormSyncTransportMessageService`
- desc: Message service handler for status related messages
- L15 _public prototype_ `explicit FStormSyncStatusMessageService(TSharedPtr<IStormSyncTransportLocalEndpoint, ESPMode::ThreadSafe> InLocalEndpoint);`
- L19 _public prototype_ `virtual void InitializeMessageEndpoint(FMessageEndpointBuilder& InEndpointBuilder) override;`
- L23 _public prototype_ `void RequestStatus(const FMessageAddress& InRemoteAddress, const TArray<FName>& InPackageNames, const FOnStormSyncRequestStatusComplete& DoneDelegate);` — Request a status from the given remote address. The given delegate will be called when the response comes in
- L26 _public prototype_ `void AbortStatusRequest(const FGuid& InStatusRequestId);` — Abort a request using the GUID previously obtained via a call to RequestStatus
- L30 _private member_ `TWeakPtr<IStormSyncTransportLocalEndpoint> LocalEndpointWeak;` — Holds the client local endpoint.
- L33 _private member_ `TMap<FGuid, FOnStormSyncRequestStatusComplete> PendingStatusResponseHandlers;` — Handlers awaiting their resultant message bus response
- L36 _private member_ `FCriticalSection HandlersCriticalSection;` — Critical section preventing multiple threads from adding / removing handlers simultaneously
- L39 _private prototype_ `void AddResponseHandler(const FGuid& InId, const FOnStormSyncRequestStatusComplete& InDelegate);` — Helper to register a completion delegate protected by a critical section
- L42 _private prototype_ `void HandleStatusPing(const FStormSyncTransportStatusPing& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);` — TODO: Why do we have receive a message first
- L45 _private prototype_ `void HandleStatusRequest(const FStormSyncTransportStatusRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);` — Callback handler to receive status requests
- L48 _private prototype_ `void HandleStatusResponse(const FStormSyncTransportStatusResponse& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);` — Callback handler to receive status responses
- L51 _private prototype_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const;` — Returns message endpoint associated with local endpoint
- L53 _private prototype_ `TSharedPtr<IStormSyncTransportLocalEndpoint> GetLocalEndpoint() const;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/Socket/StormSyncTransportClientSocket.h` (Private)


#### class `FStormSyncTransportClientSocket`  
`class FStormSyncTransportClientSocket : public FRunnable, public TSharedFromThis<FStormSyncTransportClientSocket>`  
_L15-277_
- inherits: `FRunnable,TSharedFromThis<FStormSyncTransportClientSocket>`
- desc: Implements a TCP message tunnel connection. Mainly used to send a raw buffer serialized from StormSyncCoreUtils methods to transfer a content spak on a remote instance.
- L51 _public prototype_ `explicit FStormSyncTransportClientSocket(const FIPv4Endpoint& InEndpoint);` — Creates and initializes a new instance. @param InEndpoint The IP endpoint of the remote listener
- L54 _public prototype_ `virtual ~FStormSyncTransportClientSocket();` — Virtual destructor.
- L57 _public prototype_ `void StartTransport();` — Starts processing of the connection. Needs to be called immediately after construction
- L60 _public prototype_ `void StopTransport();` — Stops processing of the connection
- L63 _public prototype_ `bool IsTransportRunning() const;` — Returns whether processing of the connection is currently active
- L66 _public prototype_ `virtual bool Init() override;`
- L67 _public prototype_ `virtual void Stop() override;`
- L68 _public prototype_ `virtual uint32 Run() override;`
- L76 _public prototype_ `bool Tick(FString& StopReason);` — Main tick handler and throttled by Run(). Listens for incoming data on our connected socket. Returns false if RequestEngineExit was called.
- L79 _public prototype_ `bool TryReconnect();` — Attempts to reconnect to configured endpoint
- L86 _public prototype_ `bool Connect();` — Create the tcp socket and tries to establish connection on the configured endpoint. @return true if we wera able to connect
- L89 _public prototype_ `void CloseSocket(const bool bShouldTriggerEvent = false);` — Explicitly close the underlying socket (usually prior to reconnecting)
- L92 _public prototype_ `bool IsConnected() const;` — Returns whether socket is valid and connection status is ok
- L99 _public prototype_ `void SendBuffer(const FStormSyncBuffer& InBuffer);` — Main utility method to send a buffer over the tcp connection (Connection must have been established before using Connect()) @param InBuffer The raw buffer to send
- L106 _public prototype_ `EConnectionState GetConnectionState() const;` — Gets the current state of the connection. @return EConnectionState current state.
- L113 _public prototype_ `static FString GetReadableConnectionState(EConnectionState State);` — Returns a human readable string from a connection state @param State the state to convert to string
- L120 _public function_ `FStormSyncOnConnectionClosed& OnConnectionClosed()` — Gets the delegate which will be called whenever the underlying socket is closed @return FOnConnectionClosedEvent delegate
- L127 _public function_ `FStormSyncOnConnectionStateChanged& OnConnectionStateChanged()` — Gets the delegate which will be called whenever the connection state changes @return FStormSyncOnConnectionStateChanged delegate
- L134 _public function_ `FStormSyncOnReceivedSize& OnReceivedSizeDelegate()` — Gets the delegate which will be called whenever we get back size received by the remote endpoint @return FStormSyncOnConnectionStateChanged delegate
- L141 _public function_ `FStormSyncOnTransferComplete& OnTransferComplete()` — Gets the delegate which will be called whenever remote fully received the buffer, indicating transfer is complete @return FStormSyncOnConnectionStateChanged delegate
- L148 _public function_ `FIPv4Endpoint GetRemoteEndpoint() const` — Gets the IP address and port of the remote connection @return FIPv4Endpoint remote connection's IP address and port
- L155 _public function_ `uint64 GetTotalBytesReceived() const` — Gets the total number of bytes received from this connection. @return Number of bytes.
- L162 _public function_ `uint64 GetTotalBytesSent() const` — Gets the total number of bytes sent on this connection. @return Number of bytes.
- L169 _public function_ `bool IsSending() const` — Are we currently sending data on this connection ? Sending new data should only be allowed if we're not busy sending already on this connection.
- L173 _private member_ `static constexpr const TCHAR* SocketDescription = TEXT("sto` — The socket description when used with FTcpSocketBuilder
- L179 _private member_ `const int32 SocketBufferSize = 4 * 1024 * 1024;` — Default to roughly 4 Mb. Socket Send / Receive Buffer Size
- L182 _private member_ `const double SocketWaitForReadTimeSeconds = 1.0;` — Maximum amount of time to wait when we block waiting for read on the underlying socket
- L185 _private member_ `const double SocketWaitForWriteTimeSeconds = 2.0;` — Maximum amount of time to wait when we block waiting for write on the underlying socket
- L188 _private member_ `EConnectionState ConnectionState;` — Current connection state
- L191 _private member_ `FIPv4Endpoint RemoteEndpoint;` — Holds the IP address (and port) that the socket will be bound to.
- L194 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L197 _private member_ `FSocket* Socket;` — Holds the connection socket.
- L200 _private member_ `std::atomic<bool> bStopping = true;` — For the thread
- L203 _private member_ `int32 TotalBytes = 0;` — Represents the total number of bytes for a buffer that is sent to a remote
- L206 _private member_ `int32 CurrentBytes = 0;` — Represents the number of bytes received for a buffer on a remote
- L209 _private member_ `uint64 TotalBytesReceived = 0;` — Holds the total number of bytes received from the connection.
- L212 _private member_ `uint64 TotalBytesSent = 0;` — Holds the total number of bytes sent to the connection.
- L215 _private member_ `uint32 ConnectionRetryDelay;` — Delay before re-establishing connection if it drops, 0 disables
- L218 _private member_ `FStormSyncOnConnectionClosed ConnectionClosedDelegate;` — Delegate trigger when underlying socket is closed
- L221 _private member_ `FStormSyncOnConnectionStateChanged ConnectionStateChangedDelegate;` — Connection state changed delegate
- L224 _private member_ `FStormSyncOnReceivedSize ReceivedSizeDelegate;` — Delegate triggered when receiving back from server the total amount of bytes received so far
- L227 _private member_ `FStormSyncOnTransferComplete TransferCompleteDelegate;` — Delegate triggered when server responds back with transfer complete packet
- L230 _private member_ `const UStormSyncTransportSettings* Settings;` — Cached version of plugin settings
- L233 _private member_ `bool bSending = false;` — Are we currently sending data on this connection
- L243 _private prototype_ `bool Send(const uint8* Data, uint32 Size, bool bPrependSize = true);` — Main utility method to send an arbitrary data buffer over the tcp socket. If bPrependSize is set to true (the default), the raw size of the buffer is sent as an "header" in the tcp stream, so that remote knows how many bytes it's gonna receive. Connection must have been established before using Connect().
- L246 _private prototype_ `bool BlockingSend(const uint8* Data, int32 BytesToSend);` — Try to send data, but if all data is not sent in one go, block on send until data is sent or an error occurs
- L254 _private prototype_ `void ParseIncomingBytes(const int32 InNumBytesRead, const TArray<uint8>& InBytes);` — Called from Tick and handles an incoming chunk of data. We expect server to respond with the overall number of bytes it received so far, which we use here to update the notification widget progress bar.
- L264 _private prototype_ `bool ParseIncomingMessage(const FString& InMessage, const FIPv4Endpoint& InEndpoint);` — Parses an incoming message from server (JSON serialized struct). It is right now: - (state) used on connection, while we wait for server to respond with a FStormSyncTransportTcpStatePacket indicating connection was successful. - (size) used when remote is receiving bytes, responding back with the total amount of bytes received so far. On "size" packets, the ReceivedSizeDelegate is triggered with the amount of bytes received.
- L267 _private prototype_ `void UpdateConnectionState(EConnectionState InNewState);` — Updates connection state and triggers delegate if it changed
- L270 _private prototype_ `static FString GetSocketReadableErrorCode();` — Internal helper returning a formatted string with last error encountered by underlying socket subsystem (Format: ErrorCodeString (ErrorCode))
- L273 _private prototype_ `static FString GetSocketReadableConnectionState(ESocketConnectionState InState);` — Internal helper returning a formatted string with current socket connection state (Format: State (Description))
- L276 _private member_ `FCriticalSection SendCriticalSection;` — Critical section preventing multiple threads from sending simultaneously

#### enum `FStormSyncTransportClientSocket::EConnectionState`  
`enum EConnectionState`  
_L31-44_
- desc: Connection state
- L34 _public enumerator_ `State_Connecting` — Initial state before establishing any connection to remote
- L37 _public enumerator_ `State_Connected` — Connected and ready to send buffers over the connection
- L40 _public enumerator_ `State_DisconnectReconnectPending` — Disconnected with reconnect pending, state after a reconnect w/o having received anything new yet
- L43 _public enumerator_ `State_Closed` — Disconnected

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FStormSyncOnConnectionClosed, const FIPv4Endpoint&) DECLARE_DELEGATE(FStormSyncOnConnectionStateChanged) DECLARE_DELEGATE_OneParam(FStormSyncOnReceivedSize, const int32) DECLARE_DELEGATE(FStormSyncOnTransferComplete) enum EConnectionState {` — Event delegate that is executed when socket is closed
- L22 _delegate_ `DECLARE_DELEGATE(FStormSyncOnConnectionStateChanged) DECLARE_DELEGATE_OneParam(FStormSyncOnReceivedSize, const int32) DECLARE_DELEGATE(FStormSyncOnTransferComplete) enum EConnectionState {` — Delegate type for announcing a connection state change
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FStormSyncOnReceivedSize, const int32) DECLARE_DELEGATE(FStormSyncOnTransferComplete) enum EConnectionState {` — Delegate type triggered when the underlying socket receives data back from remote, representing the raw size received so far
- L28 _delegate_ `DECLARE_DELEGATE(FStormSyncOnTransferComplete) enum EConnectionState {` — Delegate type triggered when the underlying socket receives transfer_complete packet from remote, indicating transfer is done

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/StormSyncTransportClientEndpoint.h` (Private)


#### struct `FStormSyncSendingBufferPayload`  
`struct FStormSyncSendingBufferPayload`  
_L20-34_
- desc: Struct payload for StartSendingBuffer() async operation
- L22 _public member_ `bool bSuccess = true;`
- L23 _public member_ `FText ErrorText;`
- L25 _public prototype_ `FStormSyncSendingBufferPayload() = default;`
- L26 _public function_ `~FStormSyncSendingBufferPayload()`
- L29 _public function_ `explicit FStormSyncSendingBufferPayload(const FText& ErrorText) : bSuccess(false) , ErrorText(ErrorText)`

#### class `FStormSyncTransportClientEndpoint`  
`class FStormSyncTransportClientEndpoint : public IStormSyncTransportClientLocalEndpoint`  
_L41-151_
- inherits: `IStormSyncTransportClientLocalEndpoint`
- desc: Implements a local endpoint for Storm Sync Client.
- L44 _public prototype_ `FStormSyncTransportClientEndpoint();`
- L48 _public prototype_ `void InitializeMessaging(const FString& InEndpointFriendlyName = TEXT("Clie` — Initializes the message endpoint.
- L51 _public prototype_ `void ShutdownMessaging();` — Initializes the message endpoint.
- L55 _public prototype_ `virtual bool IsRunning() const override;` — Returns whether message endpoint is currently active
- L58 _public prototype_ `virtual TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const override;` — Returns underlying message endpoint
- L62 _public prototype_ `virtual void RequestStatus(const FMessageAddress& InRemoteAddress, const TArray<FName>& InPackageNames, const FOnStormSyncRequestStatusComplete& InDoneDelegate) const override;`
- L63 _public prototype_ `virtual void RequestPushPackages(const FMessageAddress& InRemoteAddress, const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FOnStormSyncPushComplete& InDoneDelegate) const override;`
- L64 _public prototype_ `virtual void RequestPullPackages(const FMessageAddress& InRemoteAddress, const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FOnStormSyncPullComplete& InDoneDelegate) const override;`
- L65 _public prototype_ `virtual void AbortStatusRequest(const FGuid& InStatusRequestId) const override;`
- L66 _public prototype_ `virtual void AbortPushRequest(const FGuid& InPushRequestId) const override;`
- L67 _public prototype_ `virtual void AbortPullRequest(const FGuid& InPullRequestId) const override;`
- L87 _public prototype_ `void StartSendingBuffer(const FStormSyncTransportSyncResponse& InMessage, TSharedPtr<FStormSyncTransportClientSocket>& OutActiveConnection, const FOnStormSyncSendBufferCallback& InDoneDelegate = FOnStormSyncSendBufferCallback());` — Async operation to initialize a new tcp connection based on the provided sync response (either a push or pull case) Will attempt to: - Find the best suited remote tcp address to connect to based on provided message HostAddress and Adapters - Creates a new buffer based on the provided message sync modifiers - Starts sending buffer via tcp to the remote storm sync tcp server address The InDoneDelegate callback can be used to gather any errors that can arise during the process. It will be invoked with a payload (FStormSyncSendingBufferPayload) describing the error in case of errors, or simply with an empty payload marked as "success" in case of no errors. @param InMessage The sync response message to initialize the tcp connection and create the pak buffer from (should include info such remote network host / adapters, a list of sync modifiers, etc.) @param OutActiveConnection Will be filled with a shared ptr to the underlying active socket connection (FStormSyncTransportClientSocket) @param InDoneDelegate An optional callback that can be used to be notified about completion (with error or success payload)
- L101 _private member_ `TMap<FIPv4Endpoint, TSharedPtr<FStormSyncTransportClientSocket>> Connections;` — Map of currently connected and active clients used to send a raw buffer over tcp
- L108 _private member_ `TWeakPtr<IMessageBus, ESPMode::ThreadSafe> MessageBusPtr;` — Holds a weak pointer to the message bus. @note Since we're using the default message bus, this might be not necessary
- L111 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L114 _private member_ `TSharedPtr<FStormSyncStatusMessageService, ESPMode::ThreadSafe> StatusService;` — Status message service handler
- L117 _private member_ `TSharedPtr<FStormSyncPushMessageService, ESPMode::ThreadSafe> PushService;` — Push message service handler
- L120 _private member_ `TSharedPtr<FStormSyncPullMessageService, ESPMode::ThreadSafe> PullService;` — Pull message service handler
- L123 _private prototype_ `TSharedPtr<FStormSyncTransportClientSocket> GetOrCreateClientSocket(const FString& InAddress);` — Helper to return a currently active connection or create a new one
- L126 _private prototype_ `TSharedPtr<FStormSyncTransportClientSocket> GetActiveConnection(const FString& InHostAddress, const TArray<FString>& InHostAdapterAddresses);` — Goes over connected clients and returns the first successful connection based on host address and possible adapters config from remote
- L129 _private prototype_ `static TArray<FName> GetPackageNamesFromModifierInfos(const TArray<FStormSyncFileModifierInfo>& InModifierInfos);` — Transforms a list of modifier infos into their Package Name equivalent
- L132 _private prototype_ `void HandlePongMessage(const FStormSyncTransportPongMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPongMessage messages
- L135 _private prototype_ `void SendTcpBuffer(const FString& InAddress, const FStormSyncBuffer& InBuffer);` — Forwards sending of raw buffer over a tcp connection
- L138 _private prototype_ `void OnConnectionClosedForSocket(const FIPv4Endpoint& InEndpoint);` — Handler for when a tcp socket is closing
- L141 _private prototype_ `void OnConnectionStateChanged(TSharedPtr<FStormSyncTransportClientSocket> InConnection);` — Handler for when a connection state changes
- L144 _private prototype_ `void OnConnectionReceivedBytes(const int32 InReceivedSize, const FString InConnectionAddress);` — Handler for a connection receiving bytes
- L147 _private prototype_ `void OnTransferComplete(const FString InConnectionAddress);` — Handler for a connection done with tcp transfer
- L150 _private member_ `FCriticalSection ConnectionsCriticalSection;` — Critical section preventing multiple threads from adding / removing simultaneously

#### struct `FStormSyncTransportClientEndpoint::FAsyncBufferPayload`  
`struct FAsyncBufferPayload`  
_L91-98_
- desc: Internal payload struct to gather CreatePakBuffer() result, that is usually run in a background thread
- L93 _public member_ `bool bSuccess = true;`
- L94 _public member_ `FText ErrorText;`
- L95 _public member_ `TArray<uint8> PakBuffer;`
- L97 _public prototype_ `FAsyncBufferPayload() = default;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using IMessageBusPtr = TSharedPtr<IMessageBus, ESPMode::ThreadSafe>;`
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStormSyncSendBufferCallback, const TSharedPtr<FStormSyncSendingBufferPayload>&) class FStormSyncTransportClientEndpoint : public IStormSyncTransportClientLocalEndpoint { public: FStormSyncTransportClientEndpoint(); virtual ~FStormSyncTransportClientEndpoint() override; void InitializeMessaging(const FString& InEndpointFriendlyName = TEXT("Client")); void ShutdownMessaging();`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/StormSyncTransportClientLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncClient, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncClient, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Private/StormSyncTransportClientModule.h` (Private)


#### class `FStormSyncTransportClientModule`  
`class FStormSyncTransportClientModule : public IStormSyncTransportClientModule`  
_L15-81_
- inherits: `IStormSyncTransportClientModule`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `virtual void StartClientEndpoint(const FString& InEndpointFriendlyName) override;`
- L23 _public prototype_ `virtual TSharedPtr<IStormSyncTransportClientLocalEndpoint> CreateClientLocalEndpoint(const FString& InEndpointFriendlyName) const override;`
- L24 _public prototype_ `virtual FString GetClientEndpointMessageAddressId() const override;`
- L25 _public prototype_ `virtual FMessageEndpointSharedPtr GetClientMessageEndpoint() const override;`
- L26 _public prototype_ `virtual void SynchronizePackages(const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames) const override;`
- L27 _public prototype_ `virtual void PushPackages(const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FMessageAddress& InMessageAddress, const FOnStormSyncPushComplete& InDoneDelegate) const override;`
- L28 _public prototype_ `virtual void PullPackages(const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FMessageAddress& InMessageAddress, const FOnStormSyncPullComplete& InDoneDelegate) const override;`
- L29 _public prototype_ `virtual void RequestPackagesStatus(const FMessageAddress& InRemoteAddress, const TArray<FName>& InPackageNames, const FOnStormSyncRequestStatusComplete& InDoneDelegate) const override;`
- L34 _private prototype_ `void RegisterConsoleCommands();` — Called from StartupModule and sets up console commands for the plugin via IConsoleManager
- L37 _private prototype_ `void UnregisterConsoleCommands();` — Called from ShutdownModule and clears out previously registered console commands
- L40 _private prototype_ `void OnPostEngineInit();` — Event handler to kick in operations once engine is fully initialized (to publish a client connect message)
- L43 _private prototype_ `void PublishStatusPingMessage() const;` — Publish the client endpoint's ping message.
- L46 _private prototype_ `void OnWakeup();` — Handler for wake up event.
- L49 _private prototype_ `void ExecuteStartClient(const TArray<FString>& InArgs);` — Command handler for starting the client.
- L52 _private prototype_ `void ExecutePing(const TArray<FString>& InArgs);` — Command handler for ping command
- L55 _private prototype_ `void ExecuteSyncPak(const TArray<FString>& InArgs);` — Command handler for sync pak command
- L58 _private prototype_ `void ExecuteDebug(const TArray<FString>& InArgs);` — Command handler for displaying debug info.
- L61 _private prototype_ `void ExecuteDebugPing(const TArray<FString>& InArgs);` — Command handler for sending a status ping.
- L64 _private prototype_ `static FStormSyncPackageDescriptor CreatePackageDescriptorFromCommandLine(const FString& InArgv);` — Returns a new package descriptor pulling info from command line options
- L68 _private member_ `static constexpr const TCHAR* DefaultPakName = TEXT("Syn` — The name of the ava pak to use when none is provided from command line arguments
- L71 _private member_ `static constexpr const TCHAR* DefaultClientEndpointName = TEXT("Cli` — Default client endpoint name.
- L74 _private member_ `TSharedPtr<IStormSyncTransportClientLocalEndpoint, ESPMode::ThreadSafe> ClientEndpoint;` — Our message endpoint provider
- L77 _private member_ `TArray<IConsoleObject*> ConsoleCommands;` — References of registered console commands via IConsoleManager
- L80 _private member_ `bool bEngineInitComplete = false;` — Indicates when the engine init is complete. This is used to know when pending messages can be published.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Public/IStormSyncTransportClientLocalEndpoint.h` (Public)


#### class `IStormSyncTransportClientLocalEndpoint`  
`class IStormSyncTransportClientLocalEndpoint : public IStormSyncTransportLocalEndpoint`  
_L15-35_
- inherits: `IStormSyncTransportLocalEndpoint`
- desc: Local Endpoint interface for Storm Sync Client
- L19 _public prototype_ `virtual void RequestStatus(const FMessageAddress& InRemoteAddress, const TArray<FName>& InPackageNames, const FOnStormSyncRequestStatusComplete& InDoneDelegate) const = 0;` — Request a status from the given remote address. The given delegate will be called when the response comes in
- L22 _public prototype_ `virtual void RequestPushPackages(const FMessageAddress& InRemoteAddress, const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FOnStormSyncPushComplete& InDoneDelegate) const = 0;` — Sends a push request message to the given remote address. The given delegate will be called when the response comes in
- L25 _public prototype_ `virtual void RequestPullPackages(const FMessageAddress& InRemoteAddress, const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FOnStormSyncPullComplete& InDoneDelegate) const = 0;` — Sends a pull request message to the given remote address. The given delegate will be called when the response comes in
- L28 _public prototype_ `virtual void AbortStatusRequest(const FGuid& InStatusRequestId) const = 0;` — Abort a request using the GUID previously obtained via a call to RequestStatus
- L31 _public prototype_ `virtual void AbortPushRequest(const FGuid& InPushRequestId) const = 0;` — Abort a request using the GUID previously obtained via a call to RequestPushPackages
- L34 _public prototype_ `virtual void AbortPullRequest(const FGuid& InPullRequestId) const = 0;` — Abort a request using the GUID previously obtained via a call to RequestPullPackages

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStormSyncRequestStatusComplete, const TSharedPtr<FStormSyncTransportStatusResponse>&);`
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStormSyncRequestStatusComplete, const TSharedPtr<FStormSyncTransportStatusResponse>&);`
- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStormSyncPushComplete, const TSharedPtr<FStormSyncTransportPushResponse>&);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStormSyncPushComplete, const TSharedPtr<FStormSyncTransportPushResponse>&);`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStormSyncPullComplete, const TSharedPtr<FStormSyncTransportPullResponse>&);`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStormSyncPullComplete, const TSharedPtr<FStormSyncTransportPullResponse>&);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportClient/Public/IStormSyncTransportClientModule.h` (Public)


#### class `IStormSyncTransportClientModule`  
`class IStormSyncTransportClientModule : public IModuleInterface`  
_L15-64_
- inherits: `IModuleInterface`
- L24 _public function_ `static inline IStormSyncTransportClientModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L42 _public prototype_ `virtual void StartClientEndpoint(const FString& InEndpointFriendlyName) = 0;` — Start transport client endpoint
- L45 _public prototype_ `virtual TSharedPtr<IStormSyncTransportClientLocalEndpoint> CreateClientLocalEndpoint(const FString& InEndpointFriendlyName) const = 0;` — `UE_DEPRECATED(5.5, "Use StartClientEndpoint() instead.")`
- L48 _public prototype_ `virtual FString GetClientEndpointMessageAddressId() const = 0;` — Returns Message Address UID for client endpoint if it is currently running, empty string otherwise
- L51 _public prototype_ `virtual FMessageEndpointSharedPtr GetClientMessageEndpoint() const = 0;` — Returns Message Address UID for client endpoint if it is currently running, empty string otherwise
- L54 _public prototype_ `virtual void SynchronizePackages(const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& PackageNames) const = 0;` — Broadcast a synchronization request on all storm sync connected devices
- L57 _public prototype_ `virtual void PushPackages(const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FMessageAddress& InMessageAddress, const FOnStormSyncPushComplete& InDoneDelegate = FOnStormSyncPushComplete()) const = 0;` — Send a synchronization (push) request on a specific storm sync connected device
- L60 _public prototype_ `virtual void PullPackages(const FStormSyncPackageDescriptor& InPackageDescriptor, const TArray<FName>& InPackageNames, const FMessageAddress& InMessageAddress, const FOnStormSyncPullComplete& InDoneDelegate = FOnStormSyncPullComplete()) const = 0;` — Send a synchronization (pull) request on a specific storm sync connected device
- L63 _public prototype_ `virtual void RequestPackagesStatus(const FMessageAddress& InRemoteAddress, const TArray<FName>& InPackageNames, const FOnStormSyncRequestStatusComplete& InDoneDelegate) const = 0;` — Sends a status request

#### Free symbols / members of external scopes

- L13 _typedef_ `using FMessageEndpointSharedPtr = TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe>;`
