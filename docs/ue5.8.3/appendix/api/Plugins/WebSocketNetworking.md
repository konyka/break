# Plugins / WebSocketNetworking

- module root: `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking`
- headers: 9; symbols: 155
- symbol kinds: class=9, delegate=5, enum=2, enumerator=5, function=14, macro=2, member=33, prototype=81, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, EngineSettings, ImageCore, NetCore, OpenSSL, PacketHandler, Sockets, libWebSockets, zlib
- PublicDependencyModuleNames: Engine

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Private/WebSocket.h` (Private)


#### class `FWebSocket`  
`class FWebSocket : public INetworkingWebSocket`  
_L14-82_
- inherits: `INetworkingWebSocket`
- L20 _public prototype_ `FWebSocket(const FInternetAddr& ServerAddress);` — Initialize as client side socket.
- L24 _public prototype_ `FWebSocket(WebSocketInternalContext* InContext, WebSocketInternal* Wsi);` — Initialize as server side socket.
- L29 _public prototype_ `virtual void SetConnectedCallBack(FWebSocketInfoCallBack CallBack) override;`
- L30 _public prototype_ `virtual void SetErrorCallBack(FWebSocketInfoCallBack CallBack) override;`
- L31 _public prototype_ `virtual void SetReceiveCallBack(FWebSocketPacketReceivedCallBack CallBack) override;`
- L32 _public prototype_ `virtual void SetSocketClosedCallBack(FWebSocketInfoCallBack CallBack) override;`
- L33 _public prototype_ `virtual bool Send(const uint8* Data, uint32 Size, bool bPrependSize = true) override;`
- L34 _public prototype_ `virtual void Tick() override;`
- L35 _public prototype_ `virtual void Flush() override;`
- L36 _public prototype_ `virtual TArray<uint8> GetRawRemoteAddr(int32& OutPort) override;`
- L37 _public prototype_ `virtual FString RemoteEndPoint(bool bAppendPort) override;`
- L38 _public prototype_ `virtual FString LocalEndPoint(bool bAppendPort) override;`
- L39 _public function_ `virtual struct sockaddr_in* GetRemoteAddr() override`
- L40 _public prototype_ `virtual TArray<FString> GetUrlArgs() override;`
- L41 _public prototype_ `virtual FString GetUrlArgByName(const FString& Name) override;`
- L46 _public prototype_ `void HandlePacket();`
- L47 _public prototype_ `void OnReceive(void* Data, uint32 Size);`
- L48 _public prototype_ `void OnRawRecieve(void* Data, uint32 Size);`
- L49 _public prototype_ `void OnRawWebSocketWritable(WebSocketInternal* wsi);`
- L50 _public prototype_ `void OnClose();`
- L55 _public member_ `FWebSocketPacketReceivedCallBack ReceivedCallback;` — /
- L56 _public member_ `FWebSocketInfoCallBack ConnectedCallBack;`
- L57 _public member_ `FWebSocketInfoCallBack ErrorCallBack;`
- L58 _public member_ `FWebSocketInfoCallBack SocketClosedCallback;`
- L61 _public member_ `TArray<uint8> ReceiveBuffer;` — Recv and Send Buffers, serviced during the Tick
- L62 _public member_ `TArray<TArray<uint8>> OutgoingBuffer;`
- L66 _public member_ `WebSocketInternalContext* Context;` — libwebsocket internal context
- L69 _public member_ `WebSocketInternal* Wsi;` — libwebsocket web socket
- L72 _public member_ `WebSocketInternalProtocol* Protocols;` — libwebsocket Protocols that can be serviced by this implemenation
- L74 _public member_ `int SockFd;`
- L76 _public member_ `struct sockaddr_in RemoteAddr;`
- L79 _public member_ `bool IsServerSide;` — Server side socket or client side

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Private/WebSocketNetworkingPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `typedef struct lws_context WebSocketInternalContext;`
- L10 _typedef_ `typedef struct lws WebSocketInternal;`
- L11 _typedef_ `typedef struct lws_protocols WebSocketInternalProtocol;`
- L12 _typedef_ `typedef struct lws_http_mount WebSocketInternalHttpMount;`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketNetworking, Warning, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketNetworking, Warning, All);`

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Private/WebSocketServer.h` (Private)


#### class `FWebSocketServer`  
`class FWebSocketServer : public IWebSocketServer`  
_L9-56_
- inherits: `IWebSocketServer`
- L12 _public prototype_ `FWebSocketServer() = default;`
- L16 _public prototype_ `virtual void EnableHTTPServer(TArray<FWebSocketHttpMount> DirectoriesToServe, bool bSecure, const FWebSocketServerCertificates& Certificates) override;`
- L17 _public prototype_ `virtual bool Init(uint32 Port, FWebSocketClientConnectedCallBack, FString BindAddress = TEXT("")) override;`
- L18 _public prototype_ `virtual void SetFilterConnectionCallback(FWebSocketFilterConnectionCallback InFilterConnectionCallback) override;`
- L19 _public function_ `virtual void SetNetworkProtocol(IWebSocketServer::ENetworkProtocol Protocol) override`
- L20 _public prototype_ `virtual void Tick() override;`
- L21 _public prototype_ `virtual FString Info() override;`
- L24 _public prototype_ `bool IsHttpEnabled() const;`
- L29 _public member_ `FWebSocketClientConnectedCallBack ConnectedCallBack;` — Callback for a new websocket connection to the server
- L32 _public member_ `FWebSocketFilterConnectionCallback FilterConnectionCallback;` — Handler called to filter incoming websocket connections.
- L35 _public member_ `WebSocketInternalContext* Context;` — Internal libwebsocket context
- L38 _public member_ `WebSocketInternalProtocol* Protocols;` — Protocols serviced by this implementation
- L41 _public member_ `uint32 ServerPort;`
- L44 _private member_ `bool bEnableHttp = false;`
- L46 _private member_ `IWebSocketServer::ENetworkProtocol NetworkProtocol = IWebSocketServer::ENetworkProtocol::IPv4;`
- L48 _private member_ `bool bSecure = false;`
- L50 _private member_ `FWebSocketServerCertificates Certificates;`
- L52 _private member_ `TArray<FWebSocketHttpMount> DirectoriesToServe;`
- L53 _private member_ `WebSocketInternalHttpMount* LwsHttpMounts = NULL;`
- L55 _private member_ `char* BindAddress = NULL;`

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/INetworkingWebSocket.h` (Public)


#### class `INetworkingWebSocket`  
`class INetworkingWebSocket`  
_L8-36_
- L11 _public prototype_ `virtual ~INetworkingWebSocket() = default;`
- L16 _public prototype_ `virtual void SetConnectedCallBack(FWebSocketInfoCallBack CallBack) = 0;` — /
- L17 _public prototype_ `virtual void SetErrorCallBack(FWebSocketInfoCallBack CallBack) = 0;`
- L18 _public prototype_ `virtual void SetReceiveCallBack(FWebSocketPacketReceivedCallBack CallBack) = 0;`
- L19 _public prototype_ `virtual void SetSocketClosedCallBack(FWebSocketInfoCallBack CallBack) = 0;`
- L22 _public prototype_ `virtual bool Send(const uint8* Data, uint32 Size, bool bPrependSize = true) = 0;` — Send raw data to remote end point.
- L25 _public prototype_ `virtual void Tick() = 0;` — service libwebsocket.
- L27 _public prototype_ `virtual void Flush() = 0;` — service libwebsocket until outgoing buffer is empty
- L30 _public prototype_ `virtual TArray<uint8> GetRawRemoteAddr(int32& OutPort) = 0;` — Helper functions to describe end points.
- L31 _public prototype_ `virtual FString RemoteEndPoint(bool bAppendPort) = 0;`
- L32 _public prototype_ `virtual FString LocalEndPoint(bool bAppendPort) = 0;`
- L33 _public prototype_ `virtual struct sockaddr_in* GetRemoteAddr() = 0;`
- L34 _public prototype_ `virtual TArray<FString> GetUrlArgs() = 0;`
- L35 _public prototype_ `virtual FString GetUrlArgByName(const FString& Name) = 0;`

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/IWebSocketNetworkingModule.h` (Public)


#### class `IWebSocketNetworkingModule`  
`class IWebSocketNetworkingModule : public IModuleInterface`  
_L16-35_
- inherits: `IModuleInterface`
- desc: Interface for the WebSocketNetworking module.
- L20 _public prototype_ `virtual ~IWebSocketNetworkingModule() = default;`
- L27 _public prototype_ `virtual TUniquePtr<IWebSocketServer> CreateServer() = 0;` — Create a WebSocket server. @return A new WebSocket server, or nullptr if the server couldn't be created.
- L34 _public prototype_ `virtual TSharedPtr<INetworkingWebSocket> CreateConnection(const class FInternetAddr& ServerAddress) = 0;` — Create a WebSocket client connection. @return A new WebSocket client connection, or nullptr if the connection couldn't be created.

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/IWebSocketServer.h` (Public)


#### class `FWebSocketHttpMount`  
`class FWebSocketHttpMount`  
_L14-51_
- desc: Represents a directory on disk that can be mapped to a url route and served. For example we may wish to map `C:/www/Public` to `/` of our webserver.
- L21 _public function_ `void SetPathOnDisk(const FString& InPathOnDisk)` — Sets the absolute path on disk to the directory we wish to serve. @param InPathOnDisk The absolute path to the directory.
- L27 _public function_ `void SetWebPath(const FString& InWebPath)` — Sets The web url path to use for this mount, e.g. /images . @param InWebPath The web url path we will map the directory to, e.g. /images.
- L33 _public function_ `void SetDefaultFile(const FString& InDefaultFile)` — Sets a file to serve when the root web path is requested. @param InDefaultFile The file to serve when the root web path is request, e.g. index.html.
- L35 _public function_ `const char* GetPathOnDisk()`
- L36 _public function_ `const char* GetWebPath()`
- L37 _public function_ `const char* GetDefaultFile()`
- L38 _public function_ `bool HasDefaultFile()`
- L44 _private member_ `std::string PathOnDisk;` — The absolute path on disk to directory we wish to serve.
- L47 _private member_ `std::string WebPath;` — The web url path to use for this mount, e.g. /images
- L50 _private member_ `std::string DefaultFile = "in` — When the root of the `WebPath` is requested, without a file, we can serve this file, e.g. index.html

#### class `FWebSocketServerCertificates`  
`class FWebSocketServerCertificates`  
_L53-79_
- L60 _public function_ `void SetCertificateFilePath(const FString& InCertificateFilePath)` — Sets the absolute path on disk to the file containing the SSL certificate. @param InCertificateFilePath The absolute path to the file.
- L66 _public function_ `void SetPrivateKeyFilePath(const FString& InPrivateKeyFilePath)` — Sets the absolute path on disk to the file containing the SSL private key. @param InPrivateKeyFilePath The absolute path to the file.
- L68 _public function_ `const char* GetCertificateFilePath()`
- L69 _public function_ `const char* GetPrivateKeyFilePath()`
- L75 _private member_ `std::string CertificateFilePath;` — The absolute path to the certificate file
- L78 _private member_ `std::string PrivateKeyFilePath;` — The absolute path to the private key file

#### class `IWebSocketServer`  
`class IWebSocketServer`  
_L81-133_
- L92 _public prototype_ `virtual ~IWebSocketServer() = default;`
- L102 _public prototype_ `virtual void EnableHTTPServer(TArray<FWebSocketHttpMount> DirectoriesToServe, bool bSecure = false, const FWebSocketServerCertificates& Certificates = FWebSocketServerCertificates()) = 0;` — Extends the websocket server to additionally serve static content from on-disk directories using HTTP or HTTPS. These HTTP or HTTPS requests will use the same port as the one specified for websocket use in `Init`. Note: This function will not start the webserver, call `Init` to start the websocket/webserver. @param DirectoriesToServe The directories for the Webserver to serve. @param bSecure Should the HTTP server serve the directories over HTTPS @param Certificates FWebSocketServerCertificates containing paths to SSL certificates required when serving over HTTPS
- L111 _public prototype_ `virtual bool Init(uint32 Port, FWebSocketClientConnectedCallBack ClientConnectedCallback, FString BindAddress = TEXT("")) = 0;` — Initialize the server and start listening for messages. @param Port the port to handle websockets messages on. @param ClientConnectedCallback the handler called when a client has connected. @param BindAddress Which address the server should bind to. If left empty, the server will bind to all interfaces. @return whether the initialization was successful.
- L117 _public prototype_ `virtual void SetFilterConnectionCallback(FWebSocketFilterConnectionCallback InFilterConnectionCallback) = 0;` — Set a filter callback, used to reject connections based on the origin header. @param FilterConnectionCallback handler called to filter the connection.
- L126 _public function_ `virtual void SetNetworkProtocol(ENetworkProtocol Protocol)` — Set which network protocols the server should listen on. Must be called before Init(). Default: IPv4 only. IPv4       - listen on 0.0.0.0 (IPv4 only) IPv6       - listen on :: (IPv6 only, IPV6_V6ONLY=1) IPv4|IPv6  - listen on :: (dual-stack, IPV6_V6ONLY=0)
- L129 _public prototype_ `virtual void Tick() = 0;` — Tick the server.
- L132 _public prototype_ `virtual FString Info() = 0;` — Describe this libwebsocket server

#### enum `IWebSocketServer::ENetworkProtocol`  
`enum class ENetworkProtocol : uint8`  
_L85-90_
- desc: Bitmask of network protocols the server should listen on.
- L87 _public enumerator_ `None = 0`
- L88 _public enumerator_ `IPv4 = 1 << 0`
- L89 _public enumerator_ `IPv6 = 1 << 1`

#### Free symbols / members of external scopes

- L135 _prototype_ `ENUM_CLASS_FLAGS(IWebSocketServer::ENetworkProtocol);`

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/WebSocketConnection.h` (Public)


#### class `UWebSocketConnection`  
`class UWebSocketConnection : public UNetConnection`  
_L12-35_
- reflection: `UCLASS(MinimalAPI, transient, config = Engine)`
- inherits: `UNetConnection`
- L16 _private member_ `class INetworkingWebSocket* WebSocket;`
- L19 _private prototype_ `virtual void InitBase(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L20 _private prototype_ `virtual void InitRemoteConnection(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, const class FInternetAddr& InRemoteAddr, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L21 _private prototype_ `virtual void InitLocalConnection(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L22 _private prototype_ `virtual void LowLevelSend(void* Data, int32 CountBits, FOutPacketTraits& Traits) override;`
- L23 _private prototype_ `FString LowLevelGetRemoteAddress(bool bAppendPort = false) override;`
- L24 _private prototype_ `FString LowLevelDescribe() override;`
- L25 _private prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L26 _private prototype_ `virtual void FinishDestroy();`
- L27 _private prototype_ `virtual void ReceivedRawPacket(void* Data,int32 Count);`
- L31 _private prototype_ `void SetWebSocket(INetworkingWebSocket* InWebSocket);`
- L32 _private prototype_ `INetworkingWebSocket* GetWebSocket();`
- L34 _private member_ `bool bChallengeHandshake = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WEBSOCKETNETWORKING_API`

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/WebSocketNetDriver.h` (Public)


#### class `UWebSocketNetDriver`  
`class UWebSocketNetDriver : public UNetDriver`  
_L18-76_
- reflection: `UCLASS(MinimalAPI, transient, config = Engine)`
- inherits: `UNetDriver`
- L24 _private member_ `int32 WebSocketPort;` — `UPROPERTY(Config)` — WebSocket server port
- L27 _private prototype_ `virtual bool IsAvailable() const override;`
- L28 _private prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;`
- L29 _private prototype_ `virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;`
- L30 _private prototype_ `virtual bool InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) override;`
- L31 _private prototype_ `virtual void TickDispatch(float DeltaTime) override;`
- L32 _private prototype_ `virtual void LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits, FOutPacketTraits& Traits) override;`
- L33 _private prototype_ `virtual FString LowLevelGetNetworkNumber() override;`
- L34 _private prototype_ `virtual void LowLevelDestroy() override;`
- L35 _private prototype_ `virtual bool IsNetResourceValid(void) override;`
- L38 _private prototype_ `virtual class ISocketSubsystem* GetSocketSubsystem() override;` — stub implementation because for websockets we don't use any underlying socket sub system.
- L44 _private prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar = *GLog) override;`
- L51 _private prototype_ `bool HandleSocketsCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld);` — Exec command handlers
- L54 _private prototype_ `class UWebSocketConnection* GetServerConnection();` — @return connection to server
- L60 _private member_ `IWebSocketServer* WebSocketServer;`
- L66 _private prototype_ `void OnWebSocketClientConnected(INetworkingWebSocket*);` — to the server.
- L73 _private prototype_ `void OnWebSocketServerConnected();` — to the client.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WEBSOCKETNETWORKING_API`

### `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/WebSocketNetworkingDelegates.h` (Public)


#### enum `EWebsocketConnectionFilterResult`  
`enum class EWebsocketConnectionFilterResult : uint8`  
_L9-13_
- L11 _public enumerator_ `ConnectionAccepted`
- L12 _public enumerator_ `ConnectionRefused`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE(FWebSocketInfoCallBack);`
- L15 _prototype_ `DECLARE_DELEGATE(FWebSocketInfoCallBack);`
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FWebSocketPacketReceivedCallBack, void* , int32 );`
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FWebSocketPacketReceivedCallBack, void* , int32 );`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FWebSocketClientConnectedCallBack, INetworkingWebSocket* );`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FWebSocketClientConnectedCallBack, INetworkingWebSocket* );`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(EWebsocketConnectionFilterResult, FWebSocketFilterConnectionCallback, FString , FString );`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(EWebsocketConnectionFilterResult, FWebSocketFilterConnectionCallback, FString , FString );`
