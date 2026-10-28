# Plugins / WebSocketMessaging

- module root: `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging`
- headers: 6; symbols: 125
- symbol kinds: class=6, delegate=1, enum=1, enumerator=2, function=16, member=42, namespace=3, prototype=41, struct=3, typedef=1, variable=9
- PrivateDependencyModuleNames: Cbor, Core, CoreUObject, DiscoveryBeaconReceiver, Engine, Json, JsonUtilities, Messaging, Networking, Serialization, WebSocketNetworking, WebSockets

### `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Private/WebSocketDeserializedMessage.h` (Private)


#### class `FWebSocketDeserializedMessage`  
`class FWebSocketDeserializedMessage : public IMessageContext`  
_L14-102_
- inherits: `IMessageContext`
- L17 _public prototype_ `FWebSocketDeserializedMessage();`
- L21 _public prototype_ `bool ParseJson(const FString& InJson, FString& OutParseError);`
- L23 _public function_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override`
- L28 _public function_ `virtual const FDateTime& GetExpiration() const override`
- L33 _public function_ `virtual const void* GetMessage() const override`
- L38 _public function_ `virtual const TWeakObjectPtr<UScriptStruct, FWeakObjectPtr>& GetMessageTypeInfo() const override`
- L43 _public function_ `virtual const FMessageAddress& GetSender() const override`
- L48 _public function_ `virtual const FDateTime& GetTimeSent() const override`
- L53 _public function_ `virtual const TMap<FName, FString>& GetAnnotations() const override`
- L58 _public function_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override`
- L63 _public function_ `virtual EMessageFlags GetFlags() const override`
- L68 _public function_ `virtual const FMessageAddress& GetForwarder() const override`
- L73 _public function_ `virtual ENamedThreads::Type GetSenderThread() const override`
- L78 _public function_ `virtual const TArray<FMessageAddress, FDefaultAllocator>& GetRecipients() const override`
- L83 _public function_ `virtual const FDateTime& GetTimeForwarded() const override`
- L88 _public function_ `virtual EMessageScope GetScope() const override`
- L94 _protected member_ `FDateTime Expiration;`
- L95 _protected member_ `FDateTime TimeSent;`
- L96 _protected member_ `void* Message;`
- L97 _protected member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;`
- L98 _protected member_ `FMessageAddress Sender;`
- L99 _protected member_ `TMap<FName, FString> Annotations;`
- L100 _protected member_ `TArray<FMessageAddress> Recipients;`
- L101 _protected member_ `EMessageScope Scope;`

### `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Private/WebSocketMessageTransport.h` (Private)


#### struct `FWebSocketMessageConnection`  
`struct FWebSocketMessageConnection`  
_L11-60_
- L13 _public prototype_ `FWebSocketMessageConnection() = delete;`
- L14 _public function_ `FWebSocketMessageConnection(const FString& InUrl, const FGuid& InGuid, const TSharedRef<class IWebSocket, ESPMode::ThreadSafe>& InWebSocketConnection) : Url(InUrl), Guid(InGuid), WebSocketConnection(InWebSocketConnection), WebSocketServerConnection(nullptr), bIsConnecting(true), bDestroyed(false)`
- L25 _public function_ `FWebSocketMessageConnection(const FString& InUrl, const FGuid& InGuid, class INetworkingWebSocket* InWebSocketServerConnection) : Url(InUrl), Guid(InGuid), WebSocketConnection(nullptr), WebSocketServerConnection(InWebSocketServerConnection), bIsConnecting(true), bDestroyed(false)`
- L36 _public prototype_ `bool IsConnected() const;`
- L38 _public prototype_ `void Close();`
- L41 _public member_ `const FString Url;` — The WebSocket url
- L44 _public member_ `const FGuid Guid;` — The message transport Guid
- L47 _public member_ `TSharedPtr<class IWebSocket, ESPMode::ThreadSafe> WebSocketConnection;` — Reference to the client websocket connection
- L50 _public member_ `class INetworkingWebSocket* WebSocketServerConnection;` — Reference to the server websocket connection
- L53 _public member_ `bool bIsConnecting;` — Is the socket still trying to connect?
- L56 _public member_ `bool bDestroyed;` — The socket is about to be destroyed
- L59 _public member_ `FTSTicker::FDelegateHandle RetryHandle;` — Retry timer

#### class `FWebSocketMessageTransport`  
`class FWebSocketMessageTransport : public IMessageTransport, public TSharedFromThis<FWebSocketMessageTransport>`  
_L64-106_
- inherits: `IMessageTransport,TSharedFromThis<FWebSocketMessageTransport>`
- L67 _public prototype_ `FWebSocketMessageTransport();`
- L71 _public prototype_ `virtual FName GetDebugName() const override;`
- L72 _public prototype_ `virtual bool StartTransport(IMessageTransportHandler& InHandler) override;`
- L73 _public prototype_ `virtual void StopTransport() override;`
- L74 _public prototype_ `virtual bool TransportMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext, const TArray<FGuid>& InRecipients) override;`
- L77 _public prototype_ `bool NeedsRestart() const;`
- L79 _public prototype_ `virtual void OnJsonMessage(const FString& InMessage, FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L80 _public prototype_ `virtual void OnConnected(FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L81 _public prototype_ `virtual void OnClosed(int32 InCode, const FString& InReason, bool bInUserClose, FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L82 _public prototype_ `virtual void OnConnectionError(const FString& InMessage, FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L84 _public prototype_ `virtual void RetryConnection(FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L86 _public prototype_ `virtual void ClientConnected(class INetworkingWebSocket* InNetworkingWebSocket);`
- L88 _public prototype_ `virtual bool ServerTick(float InDeltaTime);`
- L90 _public prototype_ `virtual void OnServerJsonMessage(void* InData, int32 InDataSize, FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L91 _public prototype_ `virtual void OnServerConnectionClosed(FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L94 _protected prototype_ `void ForgetTransportNode(FWebSocketMessageConnectionRef InWebSocketMessageConnection);`
- L96 _protected member_ `IMessageTransportHandler* TransportHandler = nullptr;`
- L97 _protected member_ `TMap<FGuid, FWebSocketMessageConnectionRef> WebSocketMessageConnections;`
- L99 _protected member_ `TUniquePtr<class IWebSocketServer> Server;`
- L100 _protected member_ `FTSTicker::FDelegateHandle ServerTickerHandle;`
- L102 _protected member_ `FString LastServerBindAddress;`
- L103 _protected member_ `int32 LastServerPort = INDEX_NONE;`
- L104 _protected member_ `TArray<FString> LastConnectionEndpoints;`
- L105 _protected member_ `TMap<FString, FString> LastHttpHeaders;`

#### Free symbols / members of external scopes

- L62 _typedef_ `using FWebSocketMessageConnectionRef = TSharedRef<FWebSocketMessageConnection, ESPMode::ThreadSafe>;`

### `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Private/WebSocketMessagingBeaconReceiver.h` (Private)


#### struct `FWebSocketMessagingBeaconService`  
`struct FWebSocketMessagingBeaconService`  
_L11-20_
- reflection: `USTRUCT()`
- desc: Service entry
- L16 _public member_ `FString Name;` — `UPROPERTY()`
- L19 _public member_ `int32 Port = 0;` — `UPROPERTY()`

#### struct `FWebSocketMessagingBeaconPayload`  
`struct FWebSocketMessagingBeaconPayload`  
_L24-30_
- reflection: `USTRUCT()`
- desc: Payload of the beacon message used as serialization helper.
- L29 _public member_ `TArray<FWebSocketMessagingBeaconService> Services;` — `UPROPERTY()`

#### class `FWebSocketMessagingBeaconReceiver`  
`class FWebSocketMessagingBeaconReceiver : public FDiscoveryBeaconReceiver`  
_L36-56_
- inherits: `FDiscoveryBeaconReceiver`
- desc: Receives beacon messages from the External Apps and replies with connection information. This allows the apps to detect compatible Unreal instances on the local network and list them for the user.
- L39 _public prototype_ `FWebSocketMessagingBeaconReceiver();`
- L40 _public prototype_ `virtual ~FWebSocketMessagingBeaconReceiver() override = default;`
- L42 _public prototype_ `bool NeedsRestart() const;`
- L45 _public prototype_ `virtual void Startup() override;`
- L48 _protected prototype_ `virtual bool GetDiscoveryAddress(FIPv4Address& OutAddress) const override;`
- L49 _protected prototype_ `virtual int32 GetDiscoveryPort() const override;`
- L50 _protected prototype_ `virtual bool MakeBeaconResponse(uint8 InBeaconProtocolVersion, FArrayReader& InMessageData, FArrayWriter& OutResponseData) const override;`
- L54 _private member_ `FString LastDiscoveryEndpoint;`
- L55 _private member_ `int32 LastDiscoveryPort;`

### `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Private/WebSocketMessagingModule.h` (Private)


#### class `FWebSocketMessagingModule`  
`class FWebSocketMessagingModule : public IWebSocketMessagingModule`  
_L37-65_
- inherits: `IWebSocketMessagingModule`
- desc: Todo: implement INetworkMessagingExtension to expose more service controls.
- L41 _public prototype_ `virtual void StartupModule() override;`
- L42 _public prototype_ `virtual void ShutdownModule() override;`
- L46 _public prototype_ `virtual bool IsTransportRunning() const override;`
- L47 _public prototype_ `virtual int32 GetServerPort() const override;`
- L50 _public prototype_ `virtual bool HandleSettingsSaved();`
- L52 _public prototype_ `virtual void InitializeBridge();`
- L53 _public prototype_ `virtual void ShutdownBridge();`
- L55 _public prototype_ `void InitializeBeaconReceiver();`
- L56 _public prototype_ `void ShutdownBeaconReceiver();`
- L60 _protected member_ `TSharedPtr<class IMessageBridge, ESPMode::ThreadSafe> MessageBridge;` — Holds the message bridge if present.
- L62 _protected member_ `TWeakPtr<FWebSocketMessageTransport, ESPMode::ThreadSafe> TransportWeak;` — Keep track of the transport for access to derived functions.
- L64 _protected member_ `TUniquePtr<FWebSocketMessagingBeaconReceiver> BeaconReceiver;` — Multicast Discovery Beacon Receiver, if present.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketMessaging, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketMessaging, Log, All);`
- L16 _namespace_ `namespace WebSocketMessaging`
- L18 _namespace_ `namespace Tag` (scope `WebSocketMessaging`)
- L20 _variable_ `static constexpr const TCHAR* Sender = TEXT("Sen` (scope `WebSocketMessaging::Tag`)
- L21 _variable_ `static constexpr const TCHAR* Recipients = TEXT("Rec` (scope `WebSocketMessaging::Tag`)
- L22 _variable_ `static constexpr const TCHAR* Expiration = TEXT("Exp` (scope `WebSocketMessaging::Tag`)
- L23 _variable_ `static constexpr const TCHAR* TimeSent = TEXT("Tim` (scope `WebSocketMessaging::Tag`)
- L24 _variable_ `static constexpr const TCHAR* Annotations = TEXT("Ann` (scope `WebSocketMessaging::Tag`)
- L25 _variable_ `static constexpr const TCHAR* Scope = TEXT("Sco` (scope `WebSocketMessaging::Tag`)
- L26 _variable_ `static constexpr const TCHAR* MessageType = TEXT("Mes` (scope `WebSocketMessaging::Tag`)
- L27 _variable_ `static constexpr const TCHAR* Message = TEXT("Mes` (scope `WebSocketMessaging::Tag`)
- L30 _namespace_ `namespace Header` (scope `WebSocketMessaging`)
- L32 _variable_ `static constexpr const TCHAR* TransportId = TEXT("UE-` (scope `WebSocketMessaging::Header`)

### `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Private/WebSocketMessagingSettings.h` (Private)


#### enum `EWebSocketMessagingTransportFormat`  
`enum class EWebSocketMessagingTransportFormat : uint8`  
_L12-16_
- reflection: `UENUM()`
- L14 _public enumerator_ `Json`
- L15 _public enumerator_ `Cbor`

#### class `UWebSocketMessagingSettings`  
`class UWebSocketMessagingSettings : public UObject`  
_L19-95_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L24 _public prototype_ `int32 GetServerPort() const;`
- L28 _public member_ `bool EnableTransport = false;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — Whether the WebSocket transport channel is enabled
- L35 _public member_ `int32 ServerPort = 0;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — Bind the WebSocket server on the specified port (0 disables it) Can be specified on the command line with `-WebSocketMessagingServerPort=`
- L43 _public member_ `FString ServerBindAddress = TEXT("0.0` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The address to bind the websocket server to. 0.0.0.0 will open the connection to everyone on your network, while 127.0.0.1 will only allow local requests to come through.
- L47 _public member_ `EWebSocketMessagingTransportFormat ServerTransportFormat = EWebSocketMessagingTransportFormat::Json;` — `UPROPERTY(Config, EditAnywhere, Category=Transport)` — Format used to serialize the messages on the server's WebSockets.
- L58 _public member_ `bool bMessageSerializationStandardizeCase = true;` — `UPROPERTY(Config, EditAnywhere, Category=Transport, meta=(EditCondition="ServerTransportFormat == EWebSocketMessagingTransportFormat::Json"))` — For Json formatting only: If enabled, the "message" part of the messages will have "standardized case" (see FJsonObjectConverter::StandardizeCase). Mainly, the first character of the field name will be lower case. If disabled, the field names are not modified. For Cbor formatting, the field names are not modified.
- L62 _public member_ `TArray<FString> ConnectToEndpoints;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The WebSocket Urls to connect to (Eg. ws://example.com/xyz)
- L66 _public member_ `TMap<FString, FString> HttpHeaders;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — Additional HTTP headers to set when connecting to endpoints
- L72 _public member_ `bool bEnableDiscoveryListener = false;` — `UPROPERTY(config, EditAnywhere, Category=Discovery)` — Enables the Multicast Service Discovery
- L79 _public member_ `FString DiscoveryEndpoint = "23` — `UPROPERTY(config, EditAnywhere, Category=Discovery, meta=(EditCondition="bEnableDiscoveryListener"))` — The IP endpoint to listen to for multicast discovery messages. The multicast IP address must be in the range 224.0.0.0 to 239.255.255.255.
- L85 _public member_ `int32 DiscoveryPort = 6667;` — `UPROPERTY(config, EditAnywhere, Category=Discovery, meta=(EditCondition="bEnableDiscoveryListener"))` — The port to listen to for app discovery messages.
- L94 _public member_ `EWebSocketMessagingTransportFormat DiscoveryPayloadFormat = EWebSocketMessagingTransportFormat::Json;` — `UPROPERTY(Config, EditAnywhere, Category=Discovery, meta=(EditCondition="bEnableDiscoveryListener"))` — Format used to serialize the discovery beacon payload. The discovery beacon response will have a header followed by the payload. Header Format: 1 byte Protocol Version, 16 bytes Beacon Guid The payload is an array of "services" with name and port per service.

### `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Public/IWebSocketMessagingModule.h` (Public)


#### class `IWebSocketMessagingModule`  
`class IWebSocketMessagingModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- desc: Interface to provide information on the web socket messaging transport.
- L14 _public prototype_ `virtual bool IsTransportRunning() const = 0;` — Returns true if the transport is currently running.
- L17 _public prototype_ `virtual int32 GetServerPort() const = 0;` — Returns the current server port, either from settings or command line.
