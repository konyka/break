# Plugins / PixelStreamingServers

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreamingServers`
- headers: 12; symbols: 223
- symbol kinds: class=9, delegate=7, enum=1, enumerator=5, function=12, member=46, namespace=21, prototype=119, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, Engine, Json, Sockets, WebSocketNetworking, WebSockets
- PublicDependencyModuleNames: 

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Internal/SocketUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L9 _prototype_ `extern int GetNextAvailablePort(TOptional<int> StartingPort = FNullOpt(0));` (scope `UE::PixelStreaming`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/CirrusWrapper.h` (Private)


#### class `UE::PixelStreamingServers::FCirrusWrapper`  
`class FCirrusWrapper : public FMonitoredServerBase`  
_L12-28_
- inherits: `FMonitoredServerBase`
- desc: The NodeJS Cirrus signalling server launched as a child process.
- L15 _public prototype_ `FCirrusWrapper() = default;`
- L16 _public prototype_ `virtual ~FCirrusWrapper() = default;`
- L19 _private member_ `TUniquePtr<FWebSocketProbe> Probe;`
- L23 _protected prototype_ `void Stop() override;` — Begin FMonitoredServerBase interface
- L24 _protected prototype_ `TSharedPtr<FMonitoredProcess> LaunchServerProcess(FLaunchArgs& InLaunchArgs, FString ServerAbsPath, TMap<EEndpoint, FURL>& OutEndPoints) override;`
- L25 _protected prototype_ `bool TestConnection() override;`
- L26 _protected prototype_ `FString GetServerResourceDirectory() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreamingServers` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/MonitoredServerBase.h` (Private)


#### class `UE::PixelStreamingServers::FMonitoredServerBase`  
`class FMonitoredServerBase : public FServerBase, public TSharedFromThis<FMonitoredServerBase>`  
_L15-48_
- inherits: `FServerBase,TSharedFromThis<FMonitoredServerBase>`
- desc: Base class for all Pixel Streaming servers that are launched as child processes, e.g. calling some scripts or executables.
- L18 _public prototype_ `virtual ~FMonitoredServerBase();`
- L21 _public prototype_ `virtual void Stop() override;` — Begin IServer
- L22 _public prototype_ `virtual FString GetPathOnDisk() override;`
- L23 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) override;`
- L28 _protected prototype_ `virtual bool LaunchImpl(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndpoints) override;`
- L29 _protected prototype_ `virtual TSharedPtr<FMonitoredProcess> LaunchServerProcess(FLaunchArgs& InLaunchArgs, FString ServerAbsPath, TMap<EEndpoint, FURL>& OutEndpoints) = 0;`
- L35 _protected prototype_ `virtual bool TestConnection() = 0;` — Implemented by derived types. Implementation specific but somehow the server has been tested to see if it ready for connections. @return	True if the server is able to be connected to.
- L40 _protected prototype_ `virtual FString GetServerResourceDirectory() = 0;` — @return	Get the directory after PixelStreaming/Resources/WebServers/{ReturnThisDirectoryName}.
- L42 _protected prototype_ `virtual bool FindServerAbsPath(FLaunchArgs& InLaunchArgs, FString& OutServerAbsPath);`
- L45 _protected member_ `TSharedPtr<FMonitoredProcess> ServerProcess;`
- L46 _protected member_ `FString ServerRootAbsPath;`
- L47 _protected member_ `FDelegateHandle EngineShutdownHandle;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreamingServers` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/PixelStreamingServersLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingServers, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingServers, Log, All);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/PixelStreamingServersModule.h` (Private)


#### class `FPixelStreamingServersModule`  
`class FPixelStreamingServersModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual ~FPixelStreamingServersModule() = default;`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `static FPixelStreamingServersModule& Get();`
- L19 _private member_ `FThreadSafeCounter NextGeneratedPort = 0;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/ServerBase.h` (Private)


#### class `UE::PixelStreamingServers::FServerBase`  
`class FServerBase : public IServer, public FTickableGameObject`  
_L12-62_
- inherits: `IServer,FTickableGameObject`
- desc: Base class for all servers, provides functionality for servers to be polled for readiness while they start up.
- L16 _public prototype_ `FServerBase();`
- L20 _public prototype_ `virtual void Stop() = 0;` — Begin IServer
- L21 _public prototype_ `virtual bool HasLaunched() override;`
- L22 _public prototype_ `virtual bool Launch(FLaunchArgs& InLaunchArgs) override;`
- L23 _public prototype_ `virtual bool IsReady() override;`
- L24 _public prototype_ `virtual bool IsTimedOut() override;`
- L25 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) = 0;`
- L29 _public prototype_ `virtual bool IsTickableWhenPaused() const override;` — Begin FTickableGameObject
- L30 _public prototype_ `virtual bool IsTickableInEditor() const override;`
- L31 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L32 _public prototype_ `virtual bool IsTickable() const override;`
- L33 _public function_ `TStatId GetStatId() const`
- L41 _protected prototype_ `virtual bool TestConnection() = 0;` — Implemented by derived types. Implementation specific but somehow the server has been tested to see if it ready for connections. @return	True if the server is able to be connected to.
- L49 _protected prototype_ `virtual bool LaunchImpl(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndpoints) = 0;` — Implemented by derived types. The actual implementation of how this specified server is launched. @param LaunchArgs	The launch arguments to use. @param OutEndpoints	The output endpoints the user can expect to use with this server. @return True if the server was able to launch.
- L52 _protected member_ `FLaunchArgs LaunchArgs;`
- L53 _protected member_ `bool bHasLaunched = false;`
- L54 _protected member_ `TMap<EEndpoint, FURL> Endpoints;`
- L55 _protected member_ `FThreadSafeBool bIsReady = false;`
- L56 _protected member_ `float PollingStartedSeconds = 0.0f;`
- L57 _protected member_ `float LastReconnectionTimeSeconds = 0.0f;`
- L58 _protected member_ `bool bAllowedToTick = true;`
- L59 _protected member_ `bool bTimedOut = false;`
- L60 _protected member_ `bool bPollUntilReady = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreamingServers` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/ServerUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreamingServers` (scope `UE`)
- L13 _namespace_ `namespace Utils` (scope `UE::PixelStreamingServers`)
- L23 _prototype_ `FString QueryOrSetProcessArgs(FLaunchArgs& LaunchArgs, FString ArgKey, FString FallbackArgValue);` (scope `UE::PixelStreamingServers::Utils`) — Inspects the `LaunchArgs.ProcessArgs` for a string key matching `ArgKey`. We assume `LaunchArgs.ProcessArgs` are passed as `--key=value` in a String. @param LaunchArgs The launch args to get/set the ProcessArgs of. @param ArgKey The key to look for in the `LaunchArgs.ProcessArgs` @param FallbackArgValue If the key does not exist in the `LaunchArgs.ProcessArgs` this value to set for it in-place. @return The extracted/set process arg.
- L33 _prototype_ `TSharedPtr<FMonitoredProcess> LaunchChildProcess(FString ExecutableAbsPath, FString Args, FString LogPrefix, bool bRunAsScript);` (scope `UE::PixelStreamingServers::Utils`) — Launches an executable or script as a child process of Unreal Engine. Note: When running scripts they must be launchable through cmd.exe on Windows or bash on Linux. @param ExecutableAbsPath The absolute path to the executable or script we want to run. @param Args The argument to pass to the child process we are launching. @param LogPrefix If the child process has output the prefix to put on the UE log message for that output. @param bRunAsScript If true the `ExecutableAbsPath` will be passed to cmd/bash.
- L41 _prototype_ `bool GetResourcesDir(FString& OutResourcesDir);` (scope `UE::PixelStreamingServers::Utils`) — Get the absolute path to the Pixel Streaming resources dir (changes based on whether called in editor or not.) In editor this PixelStreaming/Resources in a game this is Samples/PixelStreaming @param OutResourcesDir The absolute path to "resources" dir. @return True if the returned path exists.
- L48 _prototype_ `bool GetWebServersDir(FString& OutWebServersAbsPath);` (scope `UE::PixelStreamingServers::Utils`) — Get the absolute path to the webservers (changes based on whether called in editor or not.) @param OutWebServersAbsPath The absolute path to the webservers. @return True if the returned path exists.
- L57 _prototype_ `bool GetDownloadedServer(FString& OutAbsPath, FString ServerDirectoryName);` (scope `UE::PixelStreamingServers::Utils`) — Attempts to get the absolute path to a downloaded server residing in the /Resources directory of the Pixel Streaming plugin, if it exists. @param OutAbsPath The absolute path of the downloaded server. @param ServerDirectoryName The directory name of the server we should look for under /Resources @return True if the scripts to launch the server exist at this location.
- L64 _prototype_ `TSharedPtr<FMonitoredProcess> DownloadPixelStreamingServers(bool bSkipIfPresent);` (scope `UE::PixelStreamingServers::Utils`) — Download the Pixel Streaming servers using the `get_ps_servers` scripts. @param bSkipIfPresent Servers will not be downloaded if they are already present. @return The child process that is used to download the servers.
- L72 _prototype_ `bool PopulateCirrusEndPoints(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndPoints);` (scope `UE::PixelStreamingServers::Utils`) — Populates the cirrus endpoints by extracting endpoint information from the `InLaunchArgs.ProcessArgs`, and if not found, using defaults. @param InLaunchArgs The launch args containing the process args that we will be inspecting. @param OutEndPoints The end points for the server if we launch it with these launch args. @param return True if the end point was added.
- L79 _prototype_ `FString ToString(FURL Url);` (scope `UE::PixelStreamingServers::Utils`) — Convert a `FURL` into a `FString`. `FURL::ToString()` already exists; however, it appends a problematic trailing slash to the output string. @param Url The url to format into a string. @return The url formatted without a trailing slash (the trailing slash messes up the Websocket clients).
- L86 _prototype_ `FString ToString(TArrayView<uint8> UTF8Bytes);` (scope `UE::PixelStreamingServers::Utils`) — Convert a UTF8 byte array to an FString @param UTF8Bytes Byte array of UTF8 characters. @return A string representation of the byte array.
- L93 _prototype_ `FString ToString(TSharedPtr<FJsonObject> JSONObj);` (scope `UE::PixelStreamingServers::Utils`) — Convert JSON object to FString. @param JSONObj A JSON object. @return The stringified JSON object.
- L100 _prototype_ `TSharedPtr<FJsonObject> ToJSON(const FString& InString);` (scope `UE::PixelStreamingServers::Utils`) — Convert a JSON formatted string into a JSON object, if possible. @param InString The JSON object expressed as a string. @return The output json object or null on failure.

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/SignallingServer.h` (Private)


#### class `UE::PixelStreamingServers::FSignallingServer`  
`class FSignallingServer : public FServerBase`  
_L19-73_
- inherits: `FServerBase`
- desc: A native C++ implementation of a Pixel Streaming signalling server (similar to cirrus.js). This implementation is missing some features such as SFU, matchmaker, and Webserver support. The purpose of this implementation is to have signalling server callable from UE, without bundling Cirrus itself.
- L23 _public prototype_ `FSignallingServer();`
- L24 _public prototype_ `virtual ~FSignallingServer() = default;`
- L27 _public prototype_ `virtual void Stop() override;`
- L28 _public prototype_ `virtual bool TestConnection() override;`
- L29 _public prototype_ `virtual bool LaunchImpl(FLaunchArgs& InLaunchArgs, TMap<EEndpoint, FURL>& OutEndpoints) override;`
- L30 _public prototype_ `virtual FString GetPathOnDisk() override;`
- L31 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) override;`
- L35 _protected prototype_ `TArray<FWebSocketHttpMount> GenerateDirectoriesToServe() const;`
- L36 _protected prototype_ `TSharedRef<FJsonObject> CreateConfigJSON() const;`
- L37 _protected prototype_ `TSharedPtr<FJsonObject> ParseMessage(const FString& InMessage, FString& OutMessageType) const;`
- L39 _protected prototype_ `void SubscribePlayer(uint16 PlayerConnectionId, const FString& StreamerName);`
- L40 _protected prototype_ `void UnsubscribePlayer(uint16 PlayerConnectionId);`
- L42 _protected prototype_ `virtual void SendPlayerMessage(uint16 PlayerId, TSharedPtr<FJsonObject> JSONObj);`
- L43 _protected prototype_ `virtual void SendStreamerMessage(uint16 StreamerId, TSharedPtr<FJsonObject> JSONObj);`
- L46 _protected prototype_ `virtual void OnStreamerConnected(uint16 ConnectionId);` — event handlers
- L47 _protected prototype_ `virtual void OnStreamerDisconnected(uint16 ConnectionId);`
- L48 _protected prototype_ `virtual void OnStreamerMessage(uint16 ConnectionId, TArrayView<uint8> Message);`
- L49 _protected prototype_ `virtual void OnPlayerConnected(uint16 ConnectionId);`
- L50 _protected prototype_ `virtual void OnPlayerDisconnected(uint16 ConnectionId);`
- L51 _protected prototype_ `virtual void OnPlayerMessage(uint16 ConnectionId, TArrayView<uint8> Message);`
- L54 _protected prototype_ `void OnStreamerIdMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);` — message handlers
- L55 _protected prototype_ `void OnStreamerPingMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L56 _protected prototype_ `void OnStreamerDisconnectMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L57 _protected prototype_ `void OnPlayerListStreamersMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L58 _protected prototype_ `void OnPlayerSubscribeMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L59 _protected prototype_ `void OnPlayerUnsubscribeMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L60 _protected prototype_ `void OnPlayerStatsMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L61 _protected prototype_ `void OnPlayerPingMessage(uint16 ConnectionId, TSharedPtr<FJsonObject> JSONObj);`
- L64 _protected member_ `TUniquePtr<FWebSocketProbe> Probe;`
- L65 _protected member_ `TUniquePtr<FWebSocketServerWrapper> StreamersWS;`
- L66 _protected member_ `TUniquePtr<FWebSocketServerWrapper> PlayersWS;`
- L68 _protected member_ `TMap<uint16, uint16> PlayerSubscriptions;`
- L70 _protected prototype_ `DECLARE_DELEGATE_TwoParams(FMessageHandler, uint16, TSharedPtr<FJsonObject>);`
- L71 _protected member_ `TMap<FString, FMessageHandler> StreamerMessageHandlers;`
- L72 _protected member_ `TMap<FString, FMessageHandler> PlayerMessageHandlers;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreamingServers` (scope `UE`)
- L70 _delegate_ `DECLARE_DELEGATE_TwoParams(FMessageHandler, uint16, TSharedPtr<FJsonObject>);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/SignallingServerLegacy.h` (Private)


#### class `UE::PixelStreamingServers::FSignallingServerLegacy`  
`class FSignallingServerLegacy : public FSignallingServer`  
_L15-23_
- inherits: `FSignallingServer`
- desc: A signalling server that matches the signalling protocol and features of the 4.26/4.27 Cirrus signalling server. While we don't want people to use this it is useful to keep around for tests to prevent breaking changes while those servers are still being used by some users.
- L18 _protected prototype_ `virtual void SendPlayerMessage(uint16 PlayerId, TSharedPtr<FJsonObject> JSONObj) override;`
- L19 _protected prototype_ `virtual void SendStreamerMessage(uint16 StreamerId, TSharedPtr<FJsonObject> JSONObj) override;`
- L21 _protected prototype_ `virtual void OnStreamerConnected(uint16 ConnectionId) override;`
- L22 _protected prototype_ `virtual void OnPlayerMessage(uint16 ConnectionId, TArrayView<uint8> Message) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreamingServers` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/WebSocketProbe.h` (Private)


#### class `UE::PixelStreamingServers::FWebSocketProbe`  
`class FWebSocketProbe`  
_L20-66_
- desc: A utility class that tries to establish a websocket connection. Useful for testing whether servers have come online yet.
- L23 _private member_ `TSharedRef<IWebSocket> WebSocket;`
- L24 _private member_ `FThreadSafeBool bShouldAttemptReconnect;`
- L25 _private member_ `FThreadSafeBool bIsClosing = false;`
- L28 _public function_ `FWebSocketProbe(FURL Url, TArray<FString> Protocols = TArray<FString>()) : WebSocket(FWebSocketsModule::Get().CreateWebSocket(Utils::ToString(Url), Protocols)) , bShouldAttemptReconnect(true) , bIsClosing(false)`
- L39 _public function_ `void Close()`
- L48 _public function_ `bool IsConnected() const`
- L53 _public function_ `bool Probe()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreamingServers` (scope `UE`)
- L33 _function_ `WebSocket->OnConnectionError().AddLambda([Url, &bShouldAttemptReconnect = bShouldAttemptReconnect](const FString& Error) { UE_LOGF(LogPixelStreamingServers, Log, "Probing websocket %ls | Msg= \"%ls\" | Retrying...", *Utils::ToString(Url), *Error); bShouldAttemptReconnect = true; });` (scope `UE::PixelStreamingServers::FWebSocketProbe::FWebSocketProbe`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Private/WebSocketServerWrapper.h` (Private)


#### struct `UE::PixelStreamingServers::FWebSocketConnection`  
`struct FWebSocketConnection`  
_L18-37_
- L21 _public prototype_ `FWebSocketConnection(INetworkingWebSocket* InSocketConnection);`
- L22 _public prototype_ `~FWebSocketConnection();`
- L23 _public prototype_ `uint16 GetId() const;`
- L24 _public prototype_ `TArray<FString> GetUrlArgs() const;`
- L25 _public prototype_ `bool Send(FString Message) const;`
- L26 _public prototype_ `void SetCallbacks();`
- L29 _public member_ `FWebSocketPacketReceivedCallBack OnPacketReceivedCallback;`
- L30 _public member_ `FWebSocketInfoCallBack OnClosedCallback;`
- L33 _private member_ `static FThreadSafeCounter IdGenerator;`
- L34 _private member_ `uint16 Id;`
- L35 _private member_ `TArray<FString> UrlArgs;`
- L36 _private member_ `INetworkingWebSocket* SocketConnection;`

#### class `UE::PixelStreamingServers::FWebSocketServerWrapper`  
`class FWebSocketServerWrapper : public FTickableGameObject`  
_L39-98_
- inherits: `FTickableGameObject`
- L42 _public prototype_ `FWebSocketServerWrapper();`
- L43 _public prototype_ `virtual ~FWebSocketServerWrapper();`
- L44 _public prototype_ `void EnableWebServer(TArray<FWebSocketHttpMount> InDirectoriesToServe);`
- L45 _public prototype_ `bool Launch(uint16 Port);`
- L46 _public prototype_ `void Stop();`
- L47 _public prototype_ `bool IsLaunched() const;`
- L48 _public prototype_ `bool HasConnections() const;`
- L49 _public prototype_ `bool Close(uint16 ConnectionId);`
- L55 _public prototype_ `bool Send(uint16 ConnectionId, FString Message) const;` — Send message to a particular websocket connection. Note: This message is sent as binary using the websocket protocol because of the WS implementation that is used. @return True if the message able to be sent.
- L56 _public prototype_ `bool Send(const FString& ConnectionName, FString Message) const;`
- L57 _public prototype_ `bool GetFirstConnection(uint16& OutConnectionId) const;`
- L58 _public function_ `TMap<uint16, TUniquePtr<FWebSocketConnection>>& GetConnections()`
- L60 _public prototype_ `void NameConnection(uint16 ConnectionId, const FString& Name);`
- L61 _public prototype_ `void RemoveName(const FString& Name);`
- L62 _public prototype_ `bool GetNamedConnection(const FString& Name, uint16& OutConnectionId) const;`
- L63 _public prototype_ `TArray<FString> GetConnectionNames() const;`
- L66 _public function_ `virtual bool IsTickableWhenPaused() const` — Begin FTickableGameObject
- L67 _public function_ `virtual bool IsTickableInEditor() const`
- L68 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L69 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L70 _public function_ `TStatId GetStatId() const`
- L73 _public function_ `int32 Count() const`
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWebSocketConnection, uint16 );`
- L77 _public member_ `FOnNewWebSocketConnection OnOpenConnection;`
- L79 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClosedWebSocketConnection, uint16 );`
- L80 _public member_ `FOnClosedWebSocketConnection OnClosedConnection;`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMessageWebSocketConnection, uint16 , TArrayView<uint8> );`
- L83 _public member_ `FOnMessageWebSocketConnection OnMessage;`
- L86 _protected prototype_ `virtual void OnConnectionOpened(INetworkingWebSocket* Socket);`
- L87 _protected prototype_ `virtual void OnPacketReceived(void* Data, int32 Size, uint16 ConnectionId);`
- L88 _protected prototype_ `virtual void OnConnectionClosed(uint16 ConnectionId);`
- L91 _private member_ `FThreadSafeBool bLaunched;`
- L92 _private member_ `TUniquePtr<IWebSocketServer> WSServer;`
- L93 _private member_ `FWebSocketClientConnectedCallBack OnClientConnectedCallback;`
- L94 _private member_ `TMap<uint16, TUniquePtr<FWebSocketConnection>> Connections;`
- L95 _private member_ `TMap<FString, uint16> NamedConnections;`
- L96 _private member_ `bool bEnableWebServer = false;`
- L97 _private member_ `TArray<FWebSocketHttpMount> DirectoriesToServe;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreamingServers` (scope `UE`)
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWebSocketConnection, uint16 );`
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClosedWebSocketConnection, uint16 );`
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMessageWebSocketConnection, uint16 , TArrayView<uint8> );`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingServers/Public/PixelStreamingServers.h` (Public)


#### struct `UE::PixelStreamingServers::FLaunchArgs`  
`struct FLaunchArgs`  
_L24-40_
- desc: Configuration to control behaviour when launching any of the Pixel Streaming servers.
- L27 _public member_ `FString ProcessArgs = TEXT("");` — Arguments passed to the actual server when its process is started.
- L30 _public member_ `bool bPollUntilReady = false;` — If true poll until ready
- L33 _public member_ `float ReconnectionTimeoutSeconds = 30.0f;` — Reconnection timeout in seconds
- L36 _public member_ `float ReconnectionIntervalSeconds = 2.0f;` — Reconnect interval in seconds.
- L39 _public member_ `TOptional<FString> ServerBinaryOverridePath;` — Path the server binary to run instead of launching server by running scripts

#### enum `UE::PixelStreamingServers::EEndpoint`  
`enum class EEndpoint`  
_L45-61_
- desc: Endpoints for the various Pixel Streaming servers.
- L48 _public enumerator_ `Signalling_Streamer` — The websocket signalling url between the server and the UE streamer - e.g. ws://localhost:8888
- L51 _public enumerator_ `Signalling_Players` — The websocket signalling url between the server and the players (aka. web browsers) - e.g. ws://localhost:80
- L54 _public enumerator_ `Signalling_Matchmaker` — The websocket signalling url between the server and the matchmaker server - e.g. ws://localhost:9999
- L57 _public enumerator_ `Signalling_SFU` — The websocket signalling url between the server and the SFU server - e.g. ws://localhost:8889
- L60 _public enumerator_ `Signalling_Webserver` — The http url for the webserver hosted within the signalling server - e.g. http://localhost

#### class `UE::PixelStreamingServers::IServer`  
`class IServer`  
_L71-119_
- desc: Interface for all Pixel Streaming servers.
- L74 _public prototype_ `virtual ~IServer() = default;`
- L77 _public prototype_ `virtual void Stop() = 0;` — Immediately stops the server.
- L82 _public prototype_ `virtual FString GetPathOnDisk() = 0;` — @return	The absolute path to the root directory that the server was launched from.
- L87 _public prototype_ `virtual bool HasLaunched() = 0;` — @return	True if the server has been launched. Note: Launched does not necessarily mean it is connectible yet. Bind to OnReady for that.
- L94 _public prototype_ `virtual bool Launch(FLaunchArgs& InLaunchArgs) = 0;` — Launch the server in a child process using the supplied launch arguments. @param LaunchArgs	The launch arguments to control how the server is launched, including what args to pass to the child process. @return True if the server was able to start launching, this can fail when launching child process servers where files must exist on disk.
- L99 _public prototype_ `virtual bool IsReady() = 0;` — @return	True if the server has been connected to and is ready for new connections.
- L104 _public prototype_ `virtual bool IsTimedOut() = 0;` — @return	True if the server has timed out while trying to establish a connection.
- L110 _public prototype_ `virtual void GetNumStreamers(TFunction<void(uint16)> OnNumStreamersReceived) = 0;` — Asynchronously queries the numbers of streamers connected to the signalling server. @param OnNumStreamersReceived	Callback fired when the query for the number of streamers returns.
- L114 _public member_ `FOnReady OnReady;` — Delegate fired when the server is ready for connections, first parameter is a map of all supported endpoints and their urls.
- L116 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFailedToReady);`
- L118 _public member_ `FOnFailedToReady OnFailedToReady;` — Can fire when the server is unable to be contacted or connecting to it timed out.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PixelStreamingServers` (scope `UE`)
- L64 _typedef_ `typedef TMap<EEndpoint, FURL> FEndpoints;` (scope `UE::PixelStreamingServers`)
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReady, const FEndpoints& );`
- L65 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReady, const FEndpoints& );` (scope `UE::PixelStreamingServers`)
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFailedToReady);`
- L129 _prototype_ `TSharedPtr<IServer> MakeCirrusServer();` (scope `UE::PixelStreamingServers`) — Creates a NodeJS Cirrus signalling server by launching it as a child process. Note: Calling this method does not launch the server. You should call Launch() yourself once you have bound to appropriate delegates such as OnReady. @return	The Cirrus signalling server wrapped in a server object for simple management.
- L137 _prototype_ `TSharedPtr<IServer> MakeSignallingServer();` (scope `UE::PixelStreamingServers`) — Creates a native C++ signalling server (similar to cirrus.js) with no dependencies launched inside the Unreal Engine process. Note: Calling this method does not launch the server. You should call Launch() yourself once you have bound to appropriate delegates such as OnReady. @return	The embedded signalling server.
- L145 _prototype_ `TSharedPtr<IServer> MakeLegacySignallingServer();` (scope `UE::PixelStreamingServers`) — Creates a native C++ signalling server (matching signalling functionality of cirrus.js from legacy versions, pre UE5) with no dependencies launched inside the Unreal Engine process. Note: Calling this method does not launch the server. You should call Launch() yourself once you have bound to appropriate delegates such as OnReady. @return	The embedded signalling server.
- L152 _prototype_ `TSharedPtr<FMonitoredProcess> DownloadPixelStreamingServers(bool bSkipIfPresent);` (scope `UE::PixelStreamingServers`) — Download the Pixel Streaming servers using the `get_ps_servers` scripts. @param bSkipIfPresent Servers will not be downloaded if they are already present. @return The child process that is used to download the servers.
