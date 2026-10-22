# Plugins / PixelStreaming2Servers

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers`
- headers: 9; symbols: 194
- symbol kinds: class=6, delegate=7, enum=1, enumerator=4, function=13, member=45, namespace=15, prototype=100, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, Engine, Json, Sockets, WebSocketNetworking, WebSockets
- PublicDependencyModuleNames: 

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Internal/SocketUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L9 _prototype_ `extern int GetNextAvailablePort(TOptional<int> StartingPort = FNullOpt(0));` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Servers, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Servers, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/PixelStreaming2ServersModule.h` (Private)


#### class `FPixelStreaming2ServersModule`  
`class FPixelStreaming2ServersModule : public IModuleInterface`  
_L7-16_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual ~FPixelStreaming2ServersModule() = default;`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `static FPixelStreaming2ServersModule& Get();`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/ServerBase.h` (Private)


#### class `UE::PixelStreaming2Servers::FServerBase`  
`class FServerBase : public IServer, public FTickableGameObject`  
_L12-61_
- inherits: `IServer,FTickableGameObject`
- desc: Base class for all servers, provides functionality for servers to be polled for readiness while they start up.
- L15 _public prototype_ `FServerBase();`
- L19 _public prototype_ `virtual void Stop() = 0;` — Begin IServer
- L20 _public prototype_ `virtual bool HasLaunched() override;`
- L21 _public prototype_ `virtual bool Launch(FLaunchArgs& InLaunchArgs) override;`
- L22 _public prototype_ `virtual bool IsReady() override;`
- L23 _public prototype_ `virtual bool IsTimedOut() override;`
- L24 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) = 0;`
- L28 _public prototype_ `virtual bool IsTickableWhenPaused() const override;` — Begin FTickableGameObject
- L29 _public prototype_ `virtual bool IsTickableInEditor() const override;`
- L30 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L31 _public prototype_ `virtual bool IsAllowedToTick() const override;`
- L32 _public function_ `TStatId GetStatId() const`
- L40 _protected prototype_ `virtual bool TestConnection() = 0;` — Implemented by derived types. Implementation specific but somehow the server has been tested to see if it ready for connections. @return	True if the server is able to be connected to.
- L48 _protected prototype_ `virtual bool LaunchImpl(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndpoints) = 0;` — Implemented by derived types. The actual implementation of how this specified server is launched. @param LaunchArgs	The launch arguments to use. @param OutEndpoints	The output endpoints the user can expect to use with this server. @return True if the server was able to launch.
- L51 _protected member_ `FLaunchArgs LaunchArgs;`
- L52 _protected member_ `bool bHasLaunched = false;`
- L53 _protected member_ `TMap<EEndpoint, FURL> Endpoints;`
- L54 _protected member_ `FThreadSafeBool bIsReady = false;`
- L55 _protected member_ `float PollingStartedSeconds = 0.0f;`
- L56 _protected member_ `float LastReconnectionTimeSeconds = 0.0f;`
- L57 _protected member_ `bool bAllowedToTick = true;`
- L58 _protected member_ `bool bTimedOut = false;`
- L59 _protected member_ `bool bPollUntilReady = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2Servers` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/ServerUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2Servers` (scope `UE`)
- L11 _namespace_ `namespace Utils` (scope `UE::PixelStreaming2Servers`)
- L21 _prototype_ `FString QueryOrSetProcessArgs(FLaunchArgs& LaunchArgs, FString ArgKey, FString FallbackArgValue);` (scope `UE::PixelStreaming2Servers::Utils`) — Inspects the `LaunchArgs.ProcessArgs` for a string key matching `ArgKey`. We assume `LaunchArgs.ProcessArgs` are passed as `--key=value` in a String. @param LaunchArgs The launch args to get/set the ProcessArgs of. @param ArgKey The key to look for in the `LaunchArgs.ProcessArgs` @param FallbackArgValue If the key does not exist in the `LaunchArgs.ProcessArgs` this value to set for it in-place. @return The extracted/set process arg.
- L31 _prototype_ `TSharedPtr<FMonitoredProcess> LaunchChildProcess(FString ExecutableAbsPath, FString Args, FString LogPrefix, bool bRunAsScript);` (scope `UE::PixelStreaming2Servers::Utils`) — Launches an executable or script as a child process of Unreal Engine. Note: When running scripts they must be launchable through cmd.exe on Windows or bash on Linux. @param ExecutableAbsPath The absolute path to the executable or script we want to run. @param Args The argument to pass to the child process we are launching. @param LogPrefix If the child process has output the prefix to put on the UE log message for that output. @param bRunAsScript If true the `ExecutableAbsPath` will be passed to cmd/bash.
- L39 _prototype_ `bool GetResourcesDir(FString& OutResourcesDir);` (scope `UE::PixelStreaming2Servers::Utils`) — Get the absolute path to the Pixel Streaming resources dir (changes based on whether called in editor or not.) In editor this PixelStreaming2/Resources in a game this is Samples/PixelStreaming2 @param OutResourcesDir The absolute path to "resources" dir. @return True if the returned path exists.
- L46 _prototype_ `bool GetWebServersDir(FString& OutWebServersAbsPath);` (scope `UE::PixelStreaming2Servers::Utils`) — Get the absolute path to the webservers (changes based on whether called in editor or not.) @param OutWebServersAbsPath The absolute path to the webservers. @return True if the returned path exists.
- L55 _prototype_ `bool GetDownloadedServer(FString& OutAbsPath, FString ServerDirectoryName);` (scope `UE::PixelStreaming2Servers::Utils`) — Attempts to get the absolute path to a downloaded server residing in the /Resources directory of the Pixel Streaming plugin, if it exists. @param OutAbsPath The absolute path of the downloaded server. @param ServerDirectoryName The directory name of the server we should look for under /Resources @return True if the scripts to launch the server exist at this location.
- L62 _prototype_ `TSharedPtr<FMonitoredProcess> DownloadPixelStreaming2Servers(bool bSkipIfPresent);` (scope `UE::PixelStreaming2Servers::Utils`) — Download the Pixel Streaming servers using the `get_ps_servers` scripts. @param bSkipIfPresent Servers will not be downloaded if they are already present. @return The child process that is used to download the servers.
- L70 _prototype_ `bool PopulateCirrusEndPoints(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndPoints);` (scope `UE::PixelStreaming2Servers::Utils`) — Populates the cirrus endpoints by extracting endpoint information from the `InLaunchArgs.ProcessArgs`, and if not found, using defaults. @param InLaunchArgs The launch args containing the process args that we will be inspecting. @param OutEndPoints The end points for the server if we launch it with these launch args. @param return True if the end point was added.
- L77 _prototype_ `FString ToString(FURL Url);` (scope `UE::PixelStreaming2Servers::Utils`) — Convert a `FURL` into a `FString`. `FURL::ToString()` already exists; however, it appends a problematic trailing slash to the output string. @param Url The url to format into a string. @return The url formatted without a trailing slash (the trailing slash messes up the Websocket clients).
- L84 _prototype_ `FString ToString(TArrayView<uint8> UTF8Bytes);` (scope `UE::PixelStreaming2Servers::Utils`) — Convert a UTF8 byte array to an FString @param UTF8Bytes Byte array of UTF8 characters. @return A string representation of the byte array.
- L91 _prototype_ `FString ToString(TSharedPtr<FJsonObject> JSONObj);` (scope `UE::PixelStreaming2Servers::Utils`) — Convert JSON object to FString. @param JSONObj A JSON object. @return The stringified JSON object.
- L98 _prototype_ `TSharedPtr<FJsonObject> ToJSON(const FString& InString);` (scope `UE::PixelStreaming2Servers::Utils`) — Convert a JSON formatted string into a JSON object, if possible. @param InString The JSON object expressed as a string. @return The output json object or null on failure.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/SignallingServer.h` (Private)


#### class `UE::PixelStreaming2Servers::FSignallingServer`  
`class FSignallingServer : public FServerBase`  
_L16-73_
- inherits: `FServerBase`
- desc: A native C++ implementation of a Pixel Streaming signalling server (similar to cirrus.js). This implementation is missing some features such as SFU and Webserver support. The purpose of this implementation is to have signalling server callable from UE, without bundling Cirrus itself.
- L20 _public prototype_ `FSignallingServer();`
- L21 _public prototype_ `virtual ~FSignallingServer() = default;`
- L24 _public prototype_ `virtual void Stop() override;`
- L25 _public prototype_ `virtual bool TestConnection() override;`
- L26 _public prototype_ `virtual bool LaunchImpl(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndpoints) override;`
- L27 _public prototype_ `virtual FString GetPathOnDisk() override;`
- L28 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) override;`
- L32 _protected prototype_ `TArray<FWebSocketHttpMount> GenerateDirectoriesToServe() const;`
- L33 _protected prototype_ `TSharedRef<FJsonObject> CreateConfigJSON() const;`
- L34 _protected prototype_ `TSharedPtr<FJsonObject> ParseMessage(const FString& InMessage, FString& OutMessageType) const;`
- L36 _protected prototype_ `void SubscribePlayer(uint16 PlayerConnectionId, const FString& StreamerName);`
- L37 _protected prototype_ `void UnsubscribePlayer(uint16 PlayerConnectionId);`
- L39 _protected prototype_ `virtual void SendPlayerMessage(uint16 PlayerId, TSharedPtr<FJsonObject> JSONObj, bool bLog = true);`
- L40 _protected prototype_ `virtual void SendStreamerMessage(uint16 StreamerId, TSharedPtr<FJsonObject> JSONObj, bool bLog = true);`
- L43 _protected prototype_ `virtual void OnStreamerConnected(uint16 ConnectionId);` — event handlers
- L44 _protected prototype_ `virtual void OnStreamerDisconnected(uint16 ConnectionId);`
- L45 _protected prototype_ `virtual void OnStreamerMessage(uint16 ConnectionId, TArrayView<uint8> Message);`
- L46 _protected prototype_ `virtual void OnPlayerConnected(uint16 ConnectionId);`
- L47 _protected prototype_ `virtual void OnPlayerDisconnected(uint16 ConnectionId);`
- L48 _protected prototype_ `virtual void OnPlayerMessage(uint16 ConnectionId, TArrayView<uint8> Message);`
- L51 _protected prototype_ `void OnStreamerIdMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);` — message handlers
- L52 _protected prototype_ `void OnStreamerPingMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L53 _protected prototype_ `void OnStreamerDisconnectMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L54 _protected prototype_ `void OnPlayerPingMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L55 _protected prototype_ `void OnPlayerListStreamersMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L56 _protected prototype_ `void OnPlayerSubscribeMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L57 _protected prototype_ `void OnPlayerUnsubscribeMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L58 _protected prototype_ `void OnPlayerStatsMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L60 _protected prototype_ `EWebsocketConnectionFilterResult FilterConnection(FString Origin, FString ClientIP);`
- L63 _protected member_ `TUniquePtr<FWebSocketProbe> Probe;`
- L64 _protected member_ `TUniquePtr<FWebSocketServerWrapper> StreamersWS;`
- L65 _protected member_ `TUniquePtr<FWebSocketServerWrapper> PlayersWS;`
- L67 _protected member_ `TMap<uint16, uint16> PlayerSubscriptions;`
- L68 _protected member_ `TArray<FString> AllowedOrigins;`
- L70 _protected prototype_ `DECLARE_DELEGATE_TwoParams(FMessageHandler, uint16, TSharedPtr<FJsonObject>);`
- L71 _protected member_ `TMap<FString, FMessageHandler> StreamerMessageHandlers;`
- L72 _protected member_ `TMap<FString, FMessageHandler> PlayerMessageHandlers;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2Servers` (scope `UE`)
- L70 _delegate_ `DECLARE_DELEGATE_TwoParams(FMessageHandler, uint16, TSharedPtr<FJsonObject>);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/WebSocketProbe.h` (Private)


#### class `UE::PixelStreaming2Servers::FWebSocketProbe`  
`class FWebSocketProbe`  
_L18-63_
- desc: A utility class that tries to establish a websocket connection. Useful for testing whether servers have come online yet.
- L21 _private member_ `TSharedRef<IWebSocket> WebSocket;`
- L22 _private member_ `FThreadSafeBool bShouldAttemptReconnect;`
- L23 _private member_ `FThreadSafeBool bCloseRequested;`
- L26 _public function_ `FWebSocketProbe(FURL Url, TArray<FString> Protocols = TArray<FString>()) : WebSocket(FWebSocketsModule::Get().CreateWebSocket(Utils::ToString(Url), Protocols)) , bShouldAttemptReconnect(true) , bCloseRequested(false)`
- L37 _public function_ `void Close()`
- L45 _public function_ `bool IsConnected() const`
- L50 _public function_ `bool Probe()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2Servers` (scope `UE`)
- L31 _function_ `WebSocket->OnConnectionError().AddLambda([Url, &bShouldAttemptReconnect = bShouldAttemptReconnect](const FString& Error) { UE_LOGF(LogPixelStreaming2Servers, Log, "Probing websocket %ls | Msg= \"%ls\" | Retrying...", *Utils::ToString(Url), *Error); bShouldAttemptReconnect = true; });` (scope `UE::PixelStreaming2Servers::FWebSocketProbe::FWebSocketProbe`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Private/WebSocketServerWrapper.h` (Private)


#### struct `UE::PixelStreaming2Servers::FWebSocketConnection`  
`struct FWebSocketConnection`  
_L13-32_
- L16 _public prototype_ `FWebSocketConnection(INetworkingWebSocket* InSocketConnection);`
- L17 _public prototype_ `~FWebSocketConnection();`
- L18 _public prototype_ `uint16 GetId() const;`
- L19 _public prototype_ `TArray<FString> GetUrlArgs() const;`
- L20 _public prototype_ `bool Send(FString Message) const;`
- L21 _public prototype_ `void SetCallbacks();`
- L24 _public member_ `FWebSocketPacketReceivedCallBack OnPacketReceivedCallback;`
- L25 _public member_ `FWebSocketInfoCallBack OnClosedCallback;`
- L28 _private member_ `static FThreadSafeCounter IdGenerator;`
- L29 _private member_ `uint16 Id;`
- L30 _private member_ `TArray<FString> UrlArgs;`
- L31 _private member_ `INetworkingWebSocket* SocketConnection;`

#### class `UE::PixelStreaming2Servers::FWebSocketServerWrapper`  
`class FWebSocketServerWrapper : public FTickableGameObject`  
_L34-99_
- inherits: `FTickableGameObject`
- L37 _public prototype_ `FWebSocketServerWrapper();`
- L38 _public prototype_ `virtual ~FWebSocketServerWrapper();`
- L39 _public prototype_ `void EnableWebServer(TArray<FWebSocketHttpMount> InDirectoriesToServe, bool bServeHttps, const FWebSocketServerCertificates& Certificates);`
- L40 _public prototype_ `void SetFilterConnectionCallback(FWebSocketFilterConnectionCallback InFilterConnectionCallback);`
- L41 _public function_ `void SetNetworkProtocol(IWebSocketServer::ENetworkProtocol Protocol)`
- L42 _public prototype_ `bool Launch(uint16 Port);`
- L43 _public prototype_ `void Stop();`
- L44 _public prototype_ `bool IsLaunched() const;`
- L45 _public prototype_ `bool HasConnections() const;`
- L46 _public prototype_ `bool Close(uint16 ConnectionId);`
- L52 _public prototype_ `bool Send(uint16 ConnectionId, FString Message) const;` — Send message to a particular websocket connection. Note: This message is sent as binary using the websocket protocol because of the WS implementation that is used. @return True if the message able to be sent.
- L53 _public prototype_ `bool Send(const FString& ConnectionName, FString Message) const;`
- L54 _public prototype_ `bool GetFirstConnection(uint16& OutConnectionId) const;`
- L55 _public function_ `TMap<uint16, TUniquePtr<FWebSocketConnection>>& GetConnections()`
- L57 _public prototype_ `void NameConnection(uint16 ConnectionId, const FString& Name);`
- L58 _public prototype_ `void RemoveName(const FString& Name);`
- L59 _public prototype_ `bool GetNamedConnection(const FString& Name, uint16& OutConnectionId) const;`
- L60 _public prototype_ `TArray<FString> GetConnectionNames() const;`
- L63 _public function_ `virtual bool IsTickableWhenPaused() const` — Begin FTickableGameObject
- L64 _public function_ `virtual bool IsTickableInEditor() const`
- L65 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L66 _public function_ `virtual bool IsAllowedToTick() const`
- L67 _public function_ `TStatId GetStatId() const`
- L70 _public function_ `int32 Count() const`
- L73 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWebSocketConnection, uint16 );`
- L74 _public member_ `FOnNewWebSocketConnection OnOpenConnection;`
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClosedWebSocketConnection, uint16 );`
- L77 _public member_ `FOnClosedWebSocketConnection OnClosedConnection;`
- L79 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMessageWebSocketConnection, uint16 , TArrayView<uint8> );`
- L80 _public member_ `FOnMessageWebSocketConnection OnMessage;`
- L83 _protected prototype_ `virtual void OnConnectionOpened(INetworkingWebSocket* Socket);`
- L84 _protected prototype_ `virtual void OnPacketReceived(void* Data, int32 Size, uint16 ConnectionId);`
- L85 _protected prototype_ `virtual void OnConnectionClosed(uint16 ConnectionId);`
- L88 _private member_ `FThreadSafeBool bLaunched;`
- L89 _private member_ `TUniquePtr<IWebSocketServer> WSServer;`
- L90 _private member_ `FWebSocketClientConnectedCallBack OnClientConnectedCallback;`
- L91 _private member_ `TMap<uint16, TUniquePtr<FWebSocketConnection>> Connections;`
- L92 _private member_ `TMap<FString, uint16> NamedConnections;`
- L93 _private member_ `bool bEnableWebServer = false;`
- L94 _private member_ `IWebSocketServer::ENetworkProtocol NetworkProtocol = IWebSocketServer::ENetworkProtocol::IPv4;`
- L95 _private member_ `bool bServeHttps = false;`
- L96 _private member_ `FWebSocketServerCertificates Certificates;`
- L97 _private member_ `TArray<FWebSocketHttpMount> DirectoriesToServe;`
- L98 _private member_ `FWebSocketFilterConnectionCallback FilterConnectionCallback;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2Servers` (scope `UE`)
- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWebSocketConnection, uint16 );`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClosedWebSocketConnection, uint16 );`
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMessageWebSocketConnection, uint16 , TArrayView<uint8> );`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Servers/Public/PixelStreaming2Servers.h` (Public)


#### struct `UE::PixelStreaming2Servers::FLaunchArgs`  
`struct FLaunchArgs`  
_L22-35_
- desc: Configuration to control behaviour when launching any of the Pixel Streaming servers.
- L25 _public member_ `FString ProcessArgs = TEXT("");` — Arguments passed to the actual server when its process is started.
- L28 _public member_ `bool bPollUntilReady = false;` — If true poll until ready
- L31 _public member_ `float ReconnectionTimeoutSeconds = 30.0f;` — Reconnection timeout in seconds
- L34 _public member_ `float ReconnectionIntervalSeconds = 2.0f;` — Reconnect interval in seconds.

#### enum `UE::PixelStreaming2Servers::EEndpoint`  
`enum class EEndpoint`  
_L40-53_
- desc: Endpoints for the various Pixel Streaming servers.
- L43 _public enumerator_ `Signalling_Streamer` — The websocket signalling url between the server and the UE streamer - e.g. ws://localhost:8888
- L46 _public enumerator_ `Signalling_Players` — The websocket signalling url between the server and the players (aka. web browsers) - e.g. ws://localhost:80
- L49 _public enumerator_ `Signalling_SFU` — The websocket signalling url between the server and the SFU server - e.g. ws://localhost:8889
- L52 _public enumerator_ `Signalling_Webserver` — The http url for the webserver hosted within the signalling server - e.g. http://localhost

#### class `UE::PixelStreaming2Servers::IServer`  
`class IServer`  
_L63-113_
- desc: Interface for all Pixel Streaming servers.
- L66 _public prototype_ `virtual ~IServer() = default;`
- L71 _public prototype_ `virtual void Stop() = 0;` — Immediately stops the server.
- L76 _public prototype_ `virtual FString GetPathOnDisk() = 0;` — @return	The absolute path to the root directory that the server was launched from.
- L81 _public prototype_ `virtual bool HasLaunched() = 0;` — @return	True if the server has been launched. Note: Launched does not necessarily mean it is connectible yet. Bind to OnReady for that.
- L88 _public prototype_ `virtual bool Launch(FLaunchArgs& InLaunchArgs) = 0;` — Launch the server in a child process using the supplied launch arguments. @param LaunchArgs	The launch arguments to control how the server is launched, including what args to pass to the child process. @return True if the server was able to start launching, this can fail when launching child process servers where files must exist on disk.
- L93 _public prototype_ `virtual bool IsReady() = 0;` — @return	True if the server has been connected to and is ready for new connections.
- L98 _public prototype_ `virtual bool IsTimedOut() = 0;` — @return	True if the server has timed out while trying to establish a connection.
- L104 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) = 0;` — Asynchronously queries the numbers of streamers connected to the signalling server. @param OnNumStreamersReceived	Callback fired when the query for the number of streamers returns.
- L108 _public member_ `FOnReady OnReady;` — Delegate fired when the server is ready for connections, first parameter is a map of all supported endpoints and their urls.
- L110 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFailedToReady);`
- L112 _public member_ `FOnFailedToReady OnFailedToReady;` — Can fire when the server is unable to be contacted or connecting to it timed out.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PixelStreaming2Servers` (scope `UE`)
- L56 _typedef_ `typedef TMap<EEndpoint, FURL> FEndpoints;` (scope `UE::PixelStreaming2Servers`)
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReady, const FEndpoints& );`
- L57 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReady, const FEndpoints& );` (scope `UE::PixelStreaming2Servers`)
- L110 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFailedToReady);`
- L122 _prototype_ `TSharedPtr<IServer> MakeSignallingServer();` (scope `UE::PixelStreaming2Servers`) — Creates a native C++ signalling server (similar to cirrus.js) with no dependencies launched inside the Unreal Engine process. Note: Calling this method does not launch the server. You should call Launch() yourself once you have bound to appropriate delegates such as OnReady. @return	The embedded signalling server.
- L129 _prototype_ `TSharedPtr<FMonitoredProcess> DownloadPixelStreaming2Servers(bool bSkipIfPresent);` (scope `UE::PixelStreaming2Servers`) — Download the Pixel Streaming servers using the `get_ps_servers` scripts. @param bSkipIfPresent Servers will not be downloaded if they are already present. @return The child process that is used to download the servers.
