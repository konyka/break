# Runtime / Stomp

- module root: `Source/Runtime/Online/Stomp`
- headers: 8; symbols: 153
- symbol kinds: class=6, delegate=11, enum=1, enumerator=3, function=13, macro=1, member=29, prototype=84, struct=1, typedef=4
- PrivateDependencyModuleNames: Core, WebSockets

### `Source/Runtime/Online/Stomp/Private/StompClient.h` (Private)


#### class `FStompClient`  
`class FStompClient : public IStompClient , public FTSTickerObjectBase , public TSharedFromThis<FStompClient>`  
_L16-171_
- inherits: `IStompClient,FTSTickerObjectBase,TSharedFromThis<FStompClient>`
- L23 _public prototype_ `virtual ~FStompClient();`
- L26 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L36 _public prototype_ `virtual void Connect(const FStompHeader& Header=FStompHeader()) override;` — Initiate a client connection to the server. Use this after setting up event handlers or to reconnect after connection errors. @param Header custom headers to send with the initial CONNECT command.
- L43 _public prototype_ `virtual void Disconnect(const FStompHeader& Header=FStompHeader()) override;` — Disconnect from the server. @param Header custom headers to send with the DISCONNECT command.
- L48 _public prototype_ `virtual bool IsConnected() const override;` — Inquire if this instance is connected to a server.
- L53 _public prototype_ `virtual FStompSubscriptionId Subscribe(const FString& Destination, const FStompSubscriptionEvent& EventCallback, const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) override;` — Subscribe to an event
- L58 _public prototype_ `virtual void Unsubscribe(FStompSubscriptionId Subscription, const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) override;` — Unsubscribe from an event
- L63 _public prototype_ `virtual void Send(const FString& Destination, const FStompBuffer& Body, const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) override;` — Emit an event to a destination
- L69 _public prototype_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientConnectedEvent, FStompClientConnectedEvent);` — Delegate called when a connection been established successfully.
- L70 _public function_ `virtual FStompClientConnectedEvent& OnConnected() override`
- L79 _public prototype_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientConnectionErrorEvent, FStompClientConnectionErrorEvent);` — Delegate called when a connection could not be established.
- L80 _public function_ `virtual FStompClientConnectionErrorEvent& OnConnectionError() override`
- L89 _public prototype_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientErrorEvent, FStompClientErrorEvent);` — Delegate called when an error is received from the server.
- L90 _public function_ `virtual FStompClientErrorEvent& OnError() override`
- L99 _public prototype_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientClosedEvent, FStompClientClosedEvent);` — Delegate called when a connection has been closed.
- L100 _public function_ `virtual FStompClientClosedEvent& OnClosed() override`
- L105 _private prototype_ `FStompClient(const FString& Url, const FTimespan& InPingInterval, const FTimespan& InPongInterval, const FString& OptAuthToken);`
- L107 _private prototype_ `FString MakeId(const class FStompFrame& Frame);`
- L108 _private prototype_ `void WriteFrame(class FStompFrame& Frame, const FStompRequestCompleted& CompletionCallback=FStompRequestCompleted());`
- L109 _private prototype_ `void PingServer();`
- L112 _private prototype_ `void HandleWebSocketConnected();` — WS event handlers
- L113 _private prototype_ `void HandleWebSocketConnectionError(const FString& Error);`
- L114 _private prototype_ `void HandleWebSocketConnectionClosed(int32 Status, const FString& Reason, bool bWasClean);`
- L115 _private prototype_ `void HandleWebSocketData(const void* Data, SIZE_T Length, SIZE_T BytesRemaining);`
- L117 _private prototype_ `void HandleIncomingFrame(const uint8* Data, SIZE_T Length);`
- L118 _private prototype_ `void HandleDisconnectCompleted(bool bSuccess, const FString& Error);`
- L121 _private member_ `FStompClientConnectedEvent ConnectedEvent;`
- L122 _private member_ `FStompClientConnectionErrorEvent ConnectionErrorEvent;`
- L123 _private member_ `FStompClientErrorEvent ErrorEvent;`
- L124 _private member_ `FStompClientClosedEvent ClosedEvent;`
- L126 _private member_ `TSharedPtr<IWebSocket> WebSocket;`
- L127 _private member_ `FStompBuffer ReceiveBuffer;`
- L128 _private member_ `FStompHeader ConnectHeader;`
- L129 _private member_ `uint64 IdCounter;`
- L136 _private member_ `TMap<FStompSubscriptionId, FStompSubscriptionEvent> Subscriptions;`
- L137 _private member_ `TMap<FString, FOutstantdingRequestInfo> OutstandingRequests;`
- L141 _private member_ `FTimespan PingInterval, PongInterval;` — "ping" is how often we should send an empty heartbeat packets to the server when inactive "pong" is the minimum how often we should expect activity from the server (counting commands and empty heartbeat frames)
- L141 _private member_ `FTimespan PingInterval, PongInterval;` — "ping" is how often we should send an empty heartbeat packets to the server when inactive "pong" is the minimum how often we should expect activity from the server (counting commands and empty heartbeat frames)
- L142 _private member_ `FDateTime LastSent;`
- L143 _private member_ `FDateTime LastReceivedPacket;`
- L144 _private member_ `FDateTime LastReceivedFrame;`
- L146 _private member_ `bool bReportedNoHeartbeatError;`
- L148 _private member_ `bool bIsConnected;`
- L149 _private member_ `FString SessionId;`
- L150 _private member_ `FString ServerString;`
- L151 _private member_ `FString ProtocolVersion;`
- L166 _private member_ `EAuthStrategy AuthStrategy = EAuthStrategy::None;`

#### struct `FStompClient::FOutstantdingRequestInfo`  
`struct FOutstantdingRequestInfo`  
_L131-135_
- L133 _public member_ `FStompRequestCompleted Delegate;`
- L134 _public member_ `FDateTime StartTime;`

#### enum `FStompClient::EAuthStrategy`  
`enum class EAuthStrategy`  
_L154-164_
- desc: Enum to allow safety check to ensure consistent use of API for auth, effectivily a compile-time property
- L157 _public enumerator_ `None` — Not using any auth
- L160 _public enumerator_ `OnConnectionUpgrade` — Auth token is provided on FStompClient construction, and passed in HTTPS request that upgrades connection to WSS
- L163 _public enumerator_ `OnStompConnect` — Auth token is provided on Connect call as Stomp headers to pass in Connect frome

#### Free symbols / members of external scopes

- L69 _delegate_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientConnectedEvent, FStompClientConnectedEvent);` — Delegate called when a connection been established successfully.
- L79 _delegate_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientConnectionErrorEvent, FStompClientConnectionErrorEvent);` — Delegate called when a connection could not be established.
- L89 _delegate_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientErrorEvent, FStompClientErrorEvent);` — Delegate called when an error is received from the server.
- L99 _delegate_ `DECLARE_DERIVED_EVENT(FStompClient, IStompClient::FStompClientClosedEvent, FStompClientClosedEvent);` — Delegate called when a connection has been closed.

### `Source/Runtime/Online/Stomp/Private/StompCommand.h` (Private)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef FName FStompCommand;`
- L13 _macro_ `#define DECLARE_COMMAND(Name) extern const FLazyName Name ## Command`
- L15 _prototype_ `DECLARE_COMMAND(Heartbeat);`
- L16 _prototype_ `DECLARE_COMMAND(Connect);`
- L17 _prototype_ `DECLARE_COMMAND(Connected);`
- L18 _prototype_ `DECLARE_COMMAND(Send);`
- L19 _prototype_ `DECLARE_COMMAND(Subscribe);`
- L20 _prototype_ `DECLARE_COMMAND(Unsubscribe);`
- L21 _prototype_ `DECLARE_COMMAND(Begin);`
- L22 _prototype_ `DECLARE_COMMAND(Commit);`
- L23 _prototype_ `DECLARE_COMMAND(Abort);`
- L24 _prototype_ `DECLARE_COMMAND(Ack);`
- L25 _prototype_ `DECLARE_COMMAND(Nack);`
- L26 _prototype_ `DECLARE_COMMAND(Disconnect);`
- L27 _prototype_ `DECLARE_COMMAND(Message);`
- L28 _prototype_ `DECLARE_COMMAND(Receipt);`
- L29 _prototype_ `DECLARE_COMMAND(Error);`

### `Source/Runtime/Online/Stomp/Private/StompFrame.h` (Private)


#### class `FStompFrame`  
`class FStompFrame`  
_L14-46_
- desc: Class for encoding and parsing stomp frames
- L19 _public prototype_ `FStompFrame(const FStompCommand& Command=HeartbeatCommand, const FStompHeader& Header=FStompHeader(), const FStompBuffer& Body=FStompBuffer());` — Create a frame for sending to the server
- L22 _public prototype_ `FStompFrame(const uint8* Data, SIZE_T Length);` — Parse a frame from the server
- L24 _public function_ `const FStompCommand& GetCommand() const`
- L29 _public function_ `FStompHeader& GetHeader()`
- L34 _public function_ `FStompBuffer& GetBody()`
- L39 _public prototype_ `void Encode(FStompBuffer& Out) const;`
- L41 _private prototype_ `void Decode(const uint8* In, SIZE_T Length);`
- L43 _private member_ `FStompCommand Command;`
- L44 _private member_ `FStompHeader Header;`
- L45 _private member_ `FStompBuffer Body;`

### `Source/Runtime/Online/Stomp/Private/StompLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStomp, Warning, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStomp, Warning, All);`

### `Source/Runtime/Online/Stomp/Private/StompMessage.h` (Private)


#### class `FStompMessage`  
`class FStompMessage : public IStompMessage`  
_L15-45_
- inherits: `IStompMessage`
- L20 _public prototype_ `virtual ~FStompMessage() = default;`
- L22 _public prototype_ `virtual void Ack(const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) const override;`
- L23 _public prototype_ `virtual void Nack(const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) const override;`
- L25 _public prototype_ `virtual const FStompHeader& GetHeader() const override;`
- L26 _public prototype_ `virtual FString GetBodyAsString() const override;`
- L27 _public prototype_ `virtual const uint8* GetRawBody() const override;`
- L28 _public prototype_ `virtual SIZE_T GetRawBodyLength() const override;`
- L30 _public prototype_ `virtual FStompSubscriptionId GetSubscriptionId() const override;`
- L31 _public prototype_ `virtual FString GetDestination() const override;`
- L32 _public prototype_ `virtual FString GetMessageId() const override;`
- L33 _public prototype_ `virtual FString GetAckId() const override;`
- L36 _private function_ `FStompMessage(const TSharedRef<FStompClient>& InClient, const TSharedRef<FStompFrame>& InFrame) : ClientPtr(InClient) , Frame(InFrame)`
- L41 _private member_ `TWeakPtr<FStompClient> ClientPtr;`
- L42 _private member_ `TSharedRef<FStompFrame> Frame;`

### `Source/Runtime/Online/Stomp/Public/IStompClient.h` (Public)


#### class `IStompClient`  
`class IStompClient`  
_L15-124_
- L19 _public prototype_ `virtual ~IStompClient() = default;`
- L27 _public prototype_ `virtual void Connect(const FStompHeader& Header=FStompHeader()) = 0;` — Initiate a client connection to the server. Use this after setting up event handlers or to reconnect after connection errors. @param Header custom headers to send with the initial CONNECT command.
- L34 _public prototype_ `virtual void Disconnect(const FStompHeader& Header=FStompHeader()) = 0;` — Disconnect from the server. @param Header custom headers to send with the DISCONNECT command.
- L39 _public prototype_ `virtual bool IsConnected() const = 0;` — Inquire if this instance is connected to a server.
- L48 _public prototype_ `virtual FStompSubscriptionId Subscribe(const FString& Destination, const FStompSubscriptionEvent& EventCallback, const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) = 0;` — Subscribe to an event @param Destination Destination endpoint to subscribe to. @param EventCallback Delegate called when events arrive on this subscription. @param CompletionCallback Delegate called when the request has been acknowledged by the server or if there is an error. @return a handle to the active subscription. Can be passed to Unsubscribe to unsubscribe from the end point.
- L56 _public prototype_ `virtual void Unsubscribe(FStompSubscriptionId Subscription, const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) = 0;` — Unsubscribe from an event @param Subscription The id returned from the call to Subscribe. @param CompletionCallback Delegate called when the request has been acknowledged by the server or if there is an error. @param ResponseCallback Delegate called when the request has been completed.
- L65 _public function_ `virtual void Send(const FString& Destination, const FString& Body, const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted())` — Emit an event to a destination @param Destination The destination endoint of the event. @param Body The event body as string. It will be encoded as UTF8 before sending to the Stomp server. @param Header Custom header values to send along with the data. @param CompletionCallback Delegate called when the request has been acknowledged by the server or if there is an error.
- L80 _public prototype_ `virtual void Send(const FString& Destination, const FStompBuffer& Body, const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) = 0;` — Emit an event to a destination @param Destination The destination endoint of the event. @param Body The event body as a binary blob. @param Header Custom header values to send along with the data. @param CompletionCallback Delegate called when the request has been acknowledged by the server or if there is an error.
- L83 _public function_ `virtual void Send(const FString& Destination, const FString& Body, const FStompRequestCompleted& CompletionCallback)`
- L88 _public function_ `virtual void Send(const FString& Destination, const FStompBuffer& Body, const FStompRequestCompleted& CompletionCallback)`
- L100 _public prototype_ `DECLARE_EVENT_ThreeParams(IStompClient, FStompClientConnectedEvent, const FString& , const FString& , const FString& );` — Delegate called when a connection been established successfully. @param ProtocoVersion The protocol version supported by the server @param SessionId A unique connection identifier. Can be empty depending on the server implementation. @param ServerString A server version string if returned from the server, otherwise empty string.
- L101 _public prototype_ `virtual FStompClientConnectedEvent& OnConnected() = 0;`
- L107 _public prototype_ `DECLARE_EVENT_OneParam(IStompClient, FStompClientConnectionErrorEvent, const FString& );` — Delegate called when a connection could not be established.
- L108 _public prototype_ `virtual FStompClientConnectionErrorEvent& OnConnectionError() = 0;`
- L114 _public prototype_ `DECLARE_EVENT_OneParam(IStompClient, FStompClientErrorEvent, const FString& );` — Delegate called when an error is received from the server.
- L115 _public prototype_ `virtual FStompClientErrorEvent& OnError() = 0;`
- L121 _public prototype_ `DECLARE_EVENT_OneParam(IStompClient, FStompClientClosedEvent, const FString& );` — Delegate called when a connection has been closed.
- L122 _public prototype_ `virtual FStompClientClosedEvent& OnClosed() = 0;`

#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FString FStompSubscriptionId;`
- L9 _typedef_ `typedef TMap<FName,FString> FStompHeader;`
- L10 _typedef_ `typedef TArray<uint8> FStompBuffer;`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FStompSubscriptionEvent, const IStompMessage& );`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FStompSubscriptionEvent, const IStompMessage& );`
- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FStompRequestCompleted, bool , const FString& );`
- L13 _prototype_ `DECLARE_DELEGATE_TwoParams(FStompRequestCompleted, bool , const FString& );`
- L100 _delegate_ `DECLARE_EVENT_ThreeParams(IStompClient, FStompClientConnectedEvent, const FString& , const FString& , const FString& );` — Delegate called when a connection been established successfully. @param ProtocoVersion The protocol version supported by the server @param SessionId A unique connection identifier. Can be empty depending on the server implementation. @param ServerString A server version string if returned from the server, otherwise empty string.
- L107 _delegate_ `DECLARE_EVENT_OneParam(IStompClient, FStompClientConnectionErrorEvent, const FString& );` — Delegate called when a connection could not be established.
- L114 _delegate_ `DECLARE_EVENT_OneParam(IStompClient, FStompClientErrorEvent, const FString& );` — Delegate called when an error is received from the server.
- L121 _delegate_ `DECLARE_EVENT_OneParam(IStompClient, FStompClientClosedEvent, const FString& );` — Delegate called when a connection has been closed.

### `Source/Runtime/Online/Stomp/Public/IStompMessage.h` (Public)


#### class `IStompMessage`  
`class IStompMessage`  
_L11-35_
- L14 _public prototype_ `virtual void Ack(const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) const = 0;`
- L15 _public prototype_ `virtual void Nack(const FStompHeader& Header=FStompHeader(), const FStompRequestCompleted& CompletionCallback = FStompRequestCompleted()) const = 0;`
- L16 _public function_ `virtual void Ack(const FStompRequestCompleted& CompletionCallback) const`
- L20 _public function_ `virtual void Nack(const FStompRequestCompleted& CompletionCallback) const`
- L25 _public prototype_ `virtual const FStompHeader& GetHeader() const = 0;`
- L26 _public prototype_ `virtual FString GetBodyAsString() const = 0;`
- L27 _public prototype_ `virtual const uint8* GetRawBody() const = 0;`
- L28 _public prototype_ `virtual SIZE_T GetRawBodyLength() const = 0;`
- L30 _public prototype_ `virtual FStompSubscriptionId GetSubscriptionId() const = 0;`
- L31 _public prototype_ `virtual FString GetDestination() const = 0;`
- L32 _public prototype_ `virtual FString GetMessageId() const = 0;`
- L33 _public prototype_ `virtual FString GetAckId() const = 0;`

### `Source/Runtime/Online/Stomp/Public/StompModule.h` (Public)


#### class `FStompModule`  
`class FStompModule : public IModuleInterface`  
_L15-60_
- inherits: `IModuleInterface`
- desc: Module for Stomp over WebSockets
- L29 _public prototype_ `static FStompModule& Get();` — Singleton-like access to this module's interface - this is just for convenience! Beware of calling this during the shutdown phase, since yuor module might have been unloaded already. @return Returns singleton instance
- L38 _public prototype_ `TSharedRef<IStompClient> CreateClient(const FString& Url, const FString& OptAuthToken = FString());` — Instantiates a new Stomp-over-websockets connection and returns it. @param Url The URL to which to connect; this should be the URL to which the WebSocket server will respond with Stomp protocol data. @return new IStompClient instance
- L49 _private prototype_ `virtual void StartupModule() override;` — Called when Stomp module is loaded Initialize implementation specific parts of Stomp handling
- L55 _private prototype_ `virtual void ShutdownModule() override;` — Called when Stomp module is unloaded Shutdown implementation specific parts of Stomp handling
- L59 _private member_ `static FStompModule* Singleton;` — singleton for the module while loaded and available
