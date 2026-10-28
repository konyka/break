# Runtime / WebSocketServer

- module root: `Source/Runtime/Online/WebSocketServer`
- headers: 5; symbols: 89
- symbol kinds: class=5, delegate=1, function=9, member=30, prototype=38, struct=3, typedef=3
- PrivateDependencyModuleNames: Core, SSL

### `Source/Runtime/Online/WebSocketServer/Private/LwsWebSocketClientConnection.h` (Private)


#### class `FLwsWebSocketClientConnection`  
`class FLwsWebSocketClientConnection final : public IWebSocketClientConnection , public TSharedFromThis<FLwsWebSocketClientConnection>`  
_L29-62_
- inherits: `IWebSocketClientConnection,TSharedFromThis<FLwsWebSocketClientConnection>`
- desc: ───────────────────────────────────────────────────────────────────────────── Per-connection object — created on ESTABLISHED, destroyed after CLOSED ─────────────────────────────────────────────────────────────────────────────
- L34 _public prototype_ `FLwsWebSocketClientConnection(lws* InWsi, const FString& InPath, FLwsWebSocketServer* InServer);`
- L37 _public prototype_ `virtual void SendText(const FString& Message) override;` — IWebSocketClientConnection
- L38 _public prototype_ `virtual void Close(int32 Code = 1000, const FString& Reason = FString()) override;`
- L39 _public function_ `virtual FString GetPath() const override`
- L43 _public prototype_ `bool LwsThreadFlushAndCheckClose();` — Called on the lws thread from SERVER_WRITEABLE: flush send queue and handle pending close. Returns true if the connection should be closed (caller must return -1 from callback).
- L46 _public prototype_ `void LwsThreadOnClosed();` — Called on the lws thread when LWS_CALLBACK_CLOSED / WSI_DESTROY fires
- L49 _private member_ `FCriticalSection WsiLock;`
- L50 _private member_ `lws* Wsi;` — Nulled on close
- L51 _private member_ `FLwsWebSocketServer* Server;` — Non-owning
- L52 _private member_ `FString Path;`
- L55 _private member_ `TQueue<TArray<uint8>, EQueueMode::Spsc> SendQueue;` — SPSC: game/any thread pushes, lws thread pops
- L58 _private member_ `TAtomic<bool> bCloseRequested { false };` — Close request — set from game thread, read on lws thread
- L59 _private member_ `TAtomic<int32> CloseCode { 1000 };`
- L61 _private member_ `FString CloseReason;` — CloseReason is written once before bCloseRequested is set true; safe to read after

### `Source/Runtime/Online/WebSocketServer/Private/LwsWebSocketServer.h` (Private)


#### class `FLwsWebSocketServer`  
`class FLwsWebSocketServer final : public IWebSocketServer , public FRunnable`  
_L17-82_
- inherits: `IWebSocketServer,FRunnable`
- desc: ───────────────────────────────────────────────────────────────────────────── Server — owns the lws_context and service thread ─────────────────────────────────────────────────────────────────────────────
- L22 _public prototype_ `explicit FLwsWebSocketServer(uint32 InPort);`
- L23 _public prototype_ `virtual ~FLwsWebSocketServer();`
- L26 _public prototype_ `virtual bool StartListening() override;` — IWebSocketServer
- L27 _public prototype_ `virtual void StopListening() override;`
- L28 _public function_ `virtual bool IsListening() const override`
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L31 _public function_ `virtual void OnConnected(FWsConnectedHandler Handler) override`
- L32 _public function_ `virtual void OnMessage(FWsMessageHandler Handler) override`
- L33 _public function_ `virtual void OnDisconnected(FWsDisconnectedHandler Handler) override`
- L36 _public prototype_ `void LwsThread_OnEstablished(lws* Wsi, const FString& Path);` — Called from lws thread (via StaticLwsCallback) to enqueue game-thread events
- L37 _public prototype_ `void LwsThread_OnReceive(lws* Wsi, const FString& Message);`
- L38 _public prototype_ `void LwsThread_OnClosed(lws* Wsi);`
- L41 _public prototype_ `void WakeService();` — Wakes the lws service loop (safe to call from any thread)
- L45 _private function_ `virtual bool Init() override` — FRunnable — runs on dedicated lws thread
- L46 _private prototype_ `virtual uint32 Run() override;`
- L47 _private prototype_ `virtual void Stop() override;`
- L48 _private function_ `virtual void Exit() override`
- L50 _private prototype_ `static int StaticLwsCallback(lws* Wsi, lws_callback_reasons Reason, void* UserData, void* Data, size_t Length);`
- L53 _private member_ `uint32 Port;`
- L54 _private member_ `lws_context* LwsContext = nullptr;`
- L55 _private member_ `FRunnableThread* Thread = nullptr;`
- L56 _private member_ `FThreadSafeCounter ExitRequest;`
- L57 _private member_ `bool bListening = false;`
- L59 _private member_ `lws_protocols LwsProtocol[3];` — catch-all ("") + "websocket" + zero terminator
- L66 _private member_ `TQueue<FConnectedEvent, EQueueMode::Mpsc> ConnectedQueue;`
- L67 _private member_ `TQueue<FMessageEvent, EQueueMode::Mpsc> MessageQueue;`
- L68 _private member_ `TQueue<FDisconnectedEvent, EQueueMode::Mpsc> DisconnectedQueue;`
- L71 _private member_ `FWsConnectedHandler ConnectedHandler;` — User-supplied handlers (set from game thread before StartListening)
- L72 _private member_ `FWsMessageHandler MessageHandler;`
- L73 _private member_ `FWsDisconnectedHandler DisconnectedHandler;`
- L76 _private member_ `TArray<TSharedPtr<FLwsWebSocketClientConnection>> Connections;` — All live connections (game thread only — drained from ConnectedQueue/DisconnectedQueue in Tick)
- L80 _private member_ `FCriticalSection ActiveConnectionsLock;` — Map from lws* → shared connection ptr, protected by a lock. Allows lws thread to enqueue message/disconnect events with a valid shared ptr.
- L81 _private member_ `TMap<lws*, TSharedPtr<FLwsWebSocketClientConnection>> ActiveConnections;`

#### struct `FLwsWebSocketServer::FConnectedEvent`  
`struct FConnectedEvent`  
_L62-62_
- desc: Game-thread event queues (MPSC: many lws connections → one game thread)
- L62 _public member_ `struct FConnectedEvent { TSharedPtr<FLwsWebSocketClientConnection> Conn; };` — Game-thread event queues (MPSC: many lws connections → one game thread)

#### struct `FLwsWebSocketServer::FMessageEvent`  
`struct FMessageEvent`  
_L63-63_
- L63 _public member_ `struct FMessageEvent { TSharedPtr<FLwsWebSocketClientConnection> Conn; FString Message; };`
- L63 _public member_ `struct FMessageEvent { TSharedPtr<FLwsWebSocketClientConnection> Conn; FString Message; };`

#### struct `FLwsWebSocketServer::FDisconnectedEvent`  
`struct FDisconnectedEvent`  
_L64-64_
- L64 _public member_ `struct FDisconnectedEvent { TSharedPtr<FLwsWebSocketClientConnection> Conn; };`

### `Source/Runtime/Online/WebSocketServer/Public/IWebSocketClientConnection.h` (Public)


#### class `IWebSocketClientConnection`  
`class IWebSocketClientConnection`  
_L11-24_
- desc: Handle to a single connected WebSocket client. May be held past disconnection; SendText/Close are no-ops after disconnect. All methods are thread-safe.
- L14 _public function_ `virtual ~IWebSocketClientConnection()`
- L17 _public prototype_ `virtual void SendText(const FString& Message) = 0;` — Send a UTF-8 text frame to this client.
- L20 _public prototype_ `virtual void Close(int32 Code = 1000, const FString& Reason = FString()) = 0;` — Initiate a graceful close with the given status code.
- L23 _public prototype_ `virtual FString GetPath() const = 0;` — The URL path from the HTTP Upgrade request (e.g. "/webtests/websocketstests/echo/").

### `Source/Runtime/Online/WebSocketServer/Public/IWebSocketServer.h` (Public)


#### class `IWebSocketServer`  
`class IWebSocketServer`  
_L18-43_
- desc: A WebSocket server listening on a single port. Handlers are invoked on the game thread.
- L21 _public function_ `virtual ~IWebSocketServer()`
- L24 _public prototype_ `virtual bool StartListening() = 0;` — Begin accepting connections. Returns false if binding failed.
- L27 _public prototype_ `virtual void StopListening() = 0;` — Stop accepting new connections and close all existing ones.
- L30 _public prototype_ `virtual bool IsListening() const = 0;` — Returns true if currently listening.
- L33 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Called every frame on the game thread to dispatch pending events.
- L36 _public prototype_ `virtual void OnConnected(FWsConnectedHandler Handler) = 0;` — Register a handler for new connections. Replaces any previous handler.
- L39 _public prototype_ `virtual void OnMessage(FWsMessageHandler Handler) = 0;` — Register a handler for incoming text messages. Replaces any previous handler.
- L42 _public prototype_ `virtual void OnDisconnected(FWsDisconnectedHandler Handler) = 0;` — Register a handler for disconnections. Replaces any previous handler.

#### Free symbols / members of external scopes

- L8 _typedef_ `using FWsConnectedHandler = TFunction<void(TSharedRef<IWebSocketClientConnection>)>;` — Called when a new client connects.
- L10 _typedef_ `using FWsMessageHandler = TFunction<void(TSharedRef<IWebSocketClientConnection>, const FString&)>;` — Called when a client sends a text message.
- L12 _typedef_ `using FWsDisconnectedHandler = TFunction<void(TSharedRef<IWebSocketClientConnection>)>;` — Called when a client disconnects (clean or error).

### `Source/Runtime/Online/WebSocketServer/Public/WebSocketServerModule.h` (Public)


#### class `FWebSocketServerModule`  
`class FWebSocketServerModule : public IModuleInterface , public FTSTickerObjectBase`  
_L21-59_
- inherits: `IModuleInterface,FTSTickerObjectBase`
- desc: Module that manages WebSocket servers. Usage: TSharedPtr<IWebSocketServer> Server = FWebSocketServerModule::Get().GetWebSocketServer(8001); Server->OnMessage([](TSharedRef<IWebSocketClientConnection> C, const FString& M){ C->SendText(M); }); FWebSocketServerModule::Get().StartAllServers();
- L26 _public prototype_ `FWebSocketServerModule();`
- L27 _public prototype_ `virtual ~FWebSocketServerModule();`
- L30 _public prototype_ `static bool IsAvailable();` — Returns true if the module is loaded and ready.
- L33 _public prototype_ `static FWebSocketServerModule& Get();` — Singleton access. Loads the module if needed.
- L39 _public prototype_ `TSharedPtr<IWebSocketServer> GetWebSocketServer(uint32 Port);` — Returns (or creates) an IWebSocketServer for the given port. Bind handlers before calling StartAllServers().
- L42 _public prototype_ `void StartAllServers();` — Start all servers (idempotent).
- L45 _public prototype_ `void StopAllServers();` — Stop all servers.
- L48 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L49 _public prototype_ `virtual void ShutdownModule() override;`
- L52 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase — drives game-thread event dispatch
- L55 _private member_ `static FWebSocketServerModule* Singleton;`
- L57 _private member_ `TMap<uint32, TSharedPtr<IWebSocketServer>> Servers;`
- L58 _private member_ `bool bServersEnabled = false;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketServer, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketServer, Log, All);`
