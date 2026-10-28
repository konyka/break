# Developer / CookOnTheFlyNetServer

- module root: `Source/Developer/CookOnTheFlyNetServer`
- headers: 4; symbols: 117
- symbol kinds: class=7, delegate=4, enum=1, enumerator=2, function=15, member=30, namespace=2, prototype=55, struct=1
- PrivateDependencyModuleNames: TargetPlatform
- PublicDependencyModuleNames: CookOnTheFly, Core, Networking, Sockets

### `Source/Developer/CookOnTheFlyNetServer/Internal/CookOnTheFlyNetServer.h` (Internal)


#### enum `UE::Cook::ECookOnTheFlyNetworkServerProtocol`  
`enum class ECookOnTheFlyNetworkServerProtocol : uint32`  
_L20-24_
- L22 _public enumerator_ `Tcp`
- L23 _public enumerator_ `Platform`

#### struct `UE::Cook::FCookOnTheFlyNetworkServerOptions`  
`struct FCookOnTheFlyNetworkServerOptions`  
_L26-36_
- L29 _public member_ `ECookOnTheFlyNetworkServerProtocol Protocol = ECookOnTheFlyNetworkServerProtocol::Tcp;` — Server protocol
- L32 _public member_ `int32 Port = INDEX_NONE;` — The port number to bind to (-1 = default port, 0 = any available port)
- L35 _public member_ `TArray<ITargetPlatform*> TargetPlatforms;` — Active target platform(s)

#### class `UE::Cook::ICookOnTheFlyClientConnection`  
`class ICookOnTheFlyClientConnection`  
_L38-48_
- L41 _public prototype_ `virtual ~ICookOnTheFlyClientConnection() = default;`
- L43 _public prototype_ `virtual FName GetPlatformName() const = 0;`
- L44 _public prototype_ `virtual const ITargetPlatform* GetTargetPlatform() const = 0;`
- L45 _public prototype_ `virtual bool GetIsSingleThreaded() const = 0;`
- L46 _public prototype_ `virtual bool SendMessage(const FCookOnTheFlyMessage& Message) = 0;`
- L47 _public prototype_ `virtual void SetZenInfo(const FString& InProjectId, const FString& InOplogId, const FString& InHostName, uint16 InHostPort) = 0;`

#### class `UE::Cook::ICookOnTheFlyNetworkServer`  
`class ICookOnTheFlyNetworkServer`  
_L50-67_
- L53 _public prototype_ `virtual ~ICookOnTheFlyNetworkServer() = default;`
- L55 _public prototype_ `DECLARE_EVENT_OneParam(ICookOnTheFlyNetworkServer, FClientConnectionEvent, ICookOnTheFlyClientConnection&);`
- L56 _public prototype_ `virtual FClientConnectionEvent& OnClientConnected() = 0;`
- L57 _public prototype_ `virtual FClientConnectionEvent& OnClientDisconnected() = 0;`
- L59 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FHandleRequestDelegate, ICookOnTheFlyClientConnection&, const FCookOnTheFlyRequest&);`
- L60 _public prototype_ `virtual FHandleRequestDelegate& OnRequest(ECookOnTheFlyMessage MessageType) = 0;`
- L62 _public prototype_ `virtual bool Start() = 0;`
- L63 _public prototype_ `virtual bool IsReadyToAcceptConnections(void) const = 0;`
- L64 _public prototype_ `virtual bool GetAddressList(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) const = 0;`
- L65 _public prototype_ `virtual FString GetSupportedProtocol() const = 0;`
- L66 _public prototype_ `virtual int32 NumConnections() const = 0;`

#### class `UE::Cook::ICookOnTheFlyNetworkServerModule`  
`class ICookOnTheFlyNetworkServerModule : public IModuleInterface`  
_L69-76_
- inherits: `IModuleInterface`
- L73 _public prototype_ `virtual ~ICookOnTheFlyNetworkServerModule() = default;`
- L75 _public prototype_ `virtual TSharedPtr<ICookOnTheFlyNetworkServer> CreateServer(const FCookOnTheFlyNetworkServerOptions& Options) = 0;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCookOnTheFlyNetworkServer, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCookOnTheFlyNetworkServer, Log, All);`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cook` (scope `UE`)
- L55 _delegate_ `DECLARE_EVENT_OneParam(ICookOnTheFlyNetworkServer, FClientConnectionEvent, ICookOnTheFlyClientConnection&);`
- L59 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FHandleRequestDelegate, ICookOnTheFlyClientConnection&, const FCookOnTheFlyRequest&);`

### `Source/Developer/CookOnTheFlyNetServer/Private/CookOnTheFlyNetServerBase.h` (Private)


#### class `FCookOnTheFlyClientConnectionBase`  
`class FCookOnTheFlyClientConnectionBase : public UE::Cook::ICookOnTheFlyClientConnection , private FRunnable`  
_L10-95_
- inherits: `UE::Cook::ICookOnTheFlyClientConnection,FRunnable`
- L15 _public prototype_ `FCookOnTheFlyClientConnectionBase(FCookOnTheFlyNetworkServerBase& InOwner);`
- L16 _public prototype_ `virtual ~FCookOnTheFlyClientConnectionBase();`
- L18 _public function_ `FName GetPlatformName() const override`
- L23 _public function_ `const ITargetPlatform* GetTargetPlatform() const`
- L28 _public function_ `bool GetIsSingleThreaded() const`
- L33 _public function_ `void SetZenInfo(const FString& InProjectId, const FString& InOplogId, const FString& InHostName, uint16 InHostPort)`
- L41 _public prototype_ `bool Initialize();`
- L43 _public prototype_ `bool SendMessage(const UE::Cook::FCookOnTheFlyMessage& Message) override;`
- L45 _public function_ `bool IsRunning()`
- L50 _public function_ `void Disconnect()`
- L56 _private function_ `virtual void OnInit()`
- L58 _private function_ `virtual bool Init() override`
- L64 _private prototype_ `virtual uint32 Run() override;`
- L66 _private function_ `virtual void Stop() override`
- L71 _private function_ `virtual void OnExit()`
- L73 _private function_ `virtual void Exit() override`
- L79 _private prototype_ `bool ProcessPayload(FArchive& Payload);`
- L80 _private prototype_ `virtual bool ReceivePayload(FArrayReader& Payload) = 0;`
- L81 _private prototype_ `virtual bool SendPayload(const TArray<uint8>& Out) = 0;`
- L83 _private member_ `FCookOnTheFlyNetworkServerBase& Owner;`
- L84 _private member_ `FName PlatformName;`
- L85 _private member_ `ITargetPlatform* TargetPlatform = nullptr;`
- L86 _private member_ `bool bIsSingleThreaded = false;`
- L87 _private member_ `TAtomic<bool> bStopRequested{ false };`
- L88 _private member_ `TAtomic<bool> bRunning{ true };`
- L89 _private member_ `FRunnableThread* WorkerThread = nullptr;`
- L90 _private member_ `bool bClientConnectedBroadcasted = false;`
- L92 _private member_ `FString ZenProjectId;`
- L93 _private member_ `FString ZenHostName;`
- L94 _private member_ `uint16 ZenHostPort = 0;`

#### class `FCookOnTheFlyNetworkServerBase`  
`class FCookOnTheFlyNetworkServerBase : public UE::Cook::ICookOnTheFlyNetworkServer`  
_L97-125_
- inherits: `UE::Cook::ICookOnTheFlyNetworkServer`
- L103 _public prototype_ `FCookOnTheFlyNetworkServerBase(const TArray<ITargetPlatform*>& InActiveTargetPlatforms);`
- L105 _public prototype_ `bool ProcessRequest(FCookOnTheFlyClientConnectionBase& Connection, const UE::Cook::FCookOnTheFlyRequest& Request);`
- L107 _public prototype_ `DECLARE_DERIVED_EVENT(FCookOnTheFlyNetworkServerBase, UE::Cook::ICookOnTheFlyNetworkServer::FClientConnectionEvent, FClientConnectionEvent);`
- L108 _public function_ `FClientConnectionEvent& OnClientConnected() override`
- L113 _public function_ `FClientConnectionEvent& OnClientDisconnected() override`
- L118 _public prototype_ `FHandleRequestDelegate& OnRequest(UE::Cook::ECookOnTheFlyMessage MessageType) override;`
- L121 _private member_ `FClientConnectionEvent ClientConnectedEvent;`
- L122 _private member_ `FClientConnectionEvent ClientDisconnectedEvent;`
- L123 _private member_ `TMap<UE::Cook::ECookOnTheFlyMessage, FHandleRequestDelegate> Handlers;`
- L124 _private member_ `TArray<ITargetPlatform*> ActiveTargetPlatforms;`

#### Free symbols / members of external scopes

- L107 _delegate_ `DECLARE_DERIVED_EVENT(FCookOnTheFlyNetworkServerBase, UE::Cook::ICookOnTheFlyNetworkServer::FClientConnectionEvent, FClientConnectionEvent);`

### `Source/Developer/CookOnTheFlyNetServer/Private/PlatformProtocolServer.h` (Private)


#### class `FCookOnTheFlyServerPlatformProtocol`  
`class FCookOnTheFlyServerPlatformProtocol : public FRunnable , public FCookOnTheFlyNetworkServerBase`  
_L22-84_
- inherits: `FRunnable,FCookOnTheFlyNetworkServerBase`
- desc: This class wraps the server thread and network connection. It uses ITargetDeviceSocket to exchanging data with the connected targets. This interface is an abstraction for direct pc-target communication as provided by the platforms. IPlatformHostCommunication/IPlatformHostSocket are the corresponding interfaces used on the game side. This implementation is based on FNetworkFileServer (the TCP-based server).
- L33 _public prototype_ `FCookOnTheFlyServerPlatformProtocol(const TArray<ITargetPlatform*>& TargetPlatforms);` — Creates and initializes a new instance. @param InFileServerOptions Network file server options
- L38 _public prototype_ `~FCookOnTheFlyServerPlatformProtocol();` — Destructor.
- L44 _public prototype_ `virtual uint32 Run() override;`
- L45 _public prototype_ `virtual void Stop() override;`
- L46 _public prototype_ `virtual void Exit() override;`
- L54 _public prototype_ `virtual bool IsReadyToAcceptConnections() const override;`
- L55 _public prototype_ `virtual bool GetAddressList(TArray<TSharedPtr<FInternetAddr> >& OutAddresses) const override;`
- L56 _public prototype_ `virtual FString GetSupportedProtocol() const override;`
- L57 _public prototype_ `virtual int32 NumConnections() const override;`
- L58 _public prototype_ `virtual bool Start() override;`
- L63 _private prototype_ `void UpdateConnections();`
- L64 _private prototype_ `void AddConnectionsForNewDevices();`
- L65 _private prototype_ `void AddConnectionsForNewDevices(ITargetPlatform* TargetPlatform);`
- L66 _private prototype_ `void RemoveClosedConnections();`
- L71 _private member_ `TArray<ITargetPlatform*> TargetPlatforms;` — File server options
- L74 _private member_ `FRunnableThread* Thread;` — Holds the server thread object.
- L77 _private member_ `TArray<FConnectionThreaded*> Connections;` — Holds the list of all client connections.
- L80 _private member_ `std::atomic<bool> StopRequested;` — Holds a flag indicating whether the thread should stop executing
- L83 _private member_ `std::atomic<bool> Running;` — Is the Listener thread up and running.

### `Source/Developer/CookOnTheFlyNetServer/Private/TCPServer.h` (Private)


#### class `FCookOnTheFlyServerTCP`  
`class FCookOnTheFlyServerTCP : public FRunnable , public FCookOnTheFlyNetworkServerBase`  
_L16-80_
- inherits: `FRunnable,FCookOnTheFlyNetworkServerBase`
- desc: This class wraps the server thread and network connection
- L27 _public prototype_ `FCookOnTheFlyServerTCP(int32 InPort, const TArray<ITargetPlatform*>& InTargetPlatforms);` — Creates and initializes a new instance. @param InFileServerOptions Network file server options
- L32 _public prototype_ `~FCookOnTheFlyServerTCP();` — Destructor.
- L38 _public function_ `virtual bool Init() override`
- L43 _public prototype_ `virtual uint32 Run() override;`
- L45 _public function_ `virtual void Stop() override`
- L50 _public prototype_ `virtual void Exit() override;`
- L54 _public prototype_ `virtual bool IsReadyToAcceptConnections(void) const override;`
- L55 _public prototype_ `virtual bool GetAddressList(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) const override;`
- L56 _public prototype_ `virtual FString GetSupportedProtocol() const override;`
- L57 _public prototype_ `virtual int32 NumConnections() const override;`
- L58 _public prototype_ `virtual bool Start() override;`
- L61 _private member_ `int32 Port;`
- L64 _private member_ `FSocket* Socket;` — Holds the server (listening) socket.
- L67 _private member_ `FRunnableThread* Thread;` — Holds the server thread object.
- L70 _private member_ `TArray<class FCookOnTheFlyClientConnectionTCP*> Connections;` — Holds the list of all client connections.
- L73 _private member_ `FThreadSafeCounter StopRequested;` — Holds a flag indicating whether the thread should stop executing
- L76 _private member_ `FThreadSafeCounter Running;` — Is the Listner thread up and running.
- L79 _private member_ `TSharedPtr<FInternetAddr> ListenAddr;` — Holds the address that the server is bound to.
