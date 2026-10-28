# Developer / UbaCoordinatorHorde

- module root: `Source/Developer/UbaCoordinatorHorde`
- headers: 6; symbols: 181
- symbol kinds: class=6, delegate=2, enum=3, enumerator=8, function=4, macro=2, member=89, namespace=2, prototype=55, struct=5, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, Core, DesktopPlatform, HTTP, Horde, Json, OpenSSL, SSL, Sockets, XmlParser
- PrivateIncludePathModuleNames: HTTPServer

### `Source/Developer/UbaCoordinatorHorde/Private/UbaHordeAgent.h` (Private)


#### class `FUbaHordeAgent`  
`class FUbaHordeAgent`  
_L13-50_
- L16 _public prototype_ `FUbaHordeAgent(const FHordeRemoteMachineInfo &MachineInfo);`
- L18 _public prototype_ `~FUbaHordeAgent();`
- L21 _public prototype_ `bool BeginCommunication();` — Start spinning the ping thread, and receive/send threads.
- L25 _public prototype_ `bool UploadBinaries(const FString& BundleDirectory, const char* BundleLocator, FEvent* CancelEvent = nullptr);` — Upload the proper executables/binaries. The Locator is just the contents of the bundle ref file. e.g. Locator = abcdef1234567890abcdef1234567890abcdef12@34567890abcdef1234567890#123
- L27 _public prototype_ `void Execute(const char* Exe, const char* const * Args, size_t NumArgs, const char* WorkingDir, const char* const * EnvVars, size_t NumEnvVars, bool bUseWine = false);`
- L29 _public prototype_ `void CloseConnection();`
- L31 _public prototype_ `bool IsValid();`
- L34 _public prototype_ `void Poll(bool LogReports, FString* OutResponseText = nullptr);` — Reads output from the child channel and reports them to the log of the calling process.
- L36 _public function_ `inline const FHordeRemoteMachineInfo& GetMachineInfo() const`
- L43 _private member_ `TUniquePtr<FComputeSocket> HordeComputeSocket;` — For Horde integration. Once all these are initialized, we're good to using UBA
- L44 _private member_ `TUniquePtr<FAgentMessageChannel> AgentChannel;`
- L45 _private member_ `TUniquePtr<FAgentMessageChannel> ChildChannel;`
- L47 _private member_ `bool bIsValid;`
- L48 _private member_ `bool bHasErrors;`
- L49 _private member_ `FHordeRemoteMachineInfo MachineInfo;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUbaHordeAgent, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUbaHordeAgent, Log, All);`

### `Source/Developer/UbaCoordinatorHorde/Private/UbaHordeComputeTransport.h` (Private)


#### class `FUbaHordeComputeTransport`  
`class FUbaHordeComputeTransport final : public FComputeTransport`  
_L9-34_
- inherits: `FComputeTransport`
- L13 _public prototype_ `FUbaHordeComputeTransport(const FHordeRemoteMachineInfo &Info, bool& InHasErrors);` — The constructor just performs a connect.
- L14 _public prototype_ `~FUbaHordeComputeTransport() override final;`
- L17 _public prototype_ `size_t Send(const void* Data, size_t Size) override final;` — Sends data to the remote
- L20 _public prototype_ `size_t Recv(void* Data, size_t Size) override final;` — Receives data from the remote
- L23 _public prototype_ `void MarkComplete() override final;` — Indicates to the remote that no more data will be sent.
- L26 _public prototype_ `void Close() override final;` — Indicates that no more data will be sent or received, and that any blocking reads/writes should stop.
- L28 _public prototype_ `bool IsValid() const override final;`
- L31 _private member_ `FSocket* Socket;`
- L32 _private member_ `bool bIsClosed;`
- L33 _private member_ `bool& bHasErrors;`

### `Source/Developer/UbaCoordinatorHorde/Private/UbaHordeComputeTransportAES.h` (Private)


#### class `FUbaHordeComputeTransportAES`  
`class FUbaHordeComputeTransportAES final : public FComputeTransport`  
_L10-43_
- inherits: `FComputeTransport`
- L14 _public prototype_ `FUbaHordeComputeTransportAES(const FHordeRemoteMachineInfo &Info, TUniquePtr<FComputeTransport>&& InInnerTransport);` — The constructor just performs a connect.
- L15 _public prototype_ `~FUbaHordeComputeTransportAES() override final;`
- L18 _public prototype_ `size_t Send(const void* Data, size_t Size) override final;` — Sends data to the remote
- L21 _public prototype_ `size_t Recv(void* Data, size_t Size) override final;` — Receives data from the remote
- L24 _public prototype_ `void MarkComplete() override final;` — Indicates to the remote that no more data will be sent.
- L27 _public prototype_ `void Close() override final;` — Indicates that no more data will be sent or received, and that any blocking reads/writes should stop.
- L29 _public prototype_ `bool IsValid() const override final;`
- L34 _private prototype_ `uint8* GetAndResizeEncryptedBuffer(int32 Size);`
- L36 _private member_ `FOpenSSLContext* OpenSSLContext;`
- L37 _private member_ `TUniquePtr<FComputeTransport> InnerTransport;`
- L38 _private member_ `TArray<uint8> EncryptedBuffer;`
- L39 _private member_ `TArray<uint8> RemainingData;`
- L40 _private member_ `int32 RemainingDataOffset;`
- L41 _private member_ `FCriticalSection IntermediateBuffersLock;`
- L42 _private member_ `bool bIsClosed;`

### `Source/Developer/UbaCoordinatorHorde/Private/UbaHordeMetaClient.h` (Private)


#### struct `FHordeRemoteMachineInfo`  
`struct FHordeRemoteMachineInfo`  
_L24-65_
- desc: When asking the Horde server for a machine, this will be returned when the HTTP reponse comes back (after a machine request). If the response didn't come through (i.e., Horde was unable to assign a machine or something), then: - Ip will be set to "" - Port will be set to 0xFFFF - Nonce will be all 0
- L39 _public member_ `FString Ip;`
- L40 _public member_ `EUbaHordeConnectionMode ConnectionMode = EUbaHordeConnectionMode::Direct;`
- L41 _public member_ `FString ConnectionAddress;` — Onyl used for relay mode
- L42 _public member_ `uint16 Port = 0;`
- L43 _public member_ `TMap<FString, FPortInfo> Ports;` — Maps compute service names to port/agent-port pairs, e.g. "_horde_compute" -> {Port: 12345, AgentPort: 7000}
- L44 _public member_ `uint16 LogicalCores = 0;`
- L45 _public member_ `EUbaHordeEncryption Encryption = EUbaHordeEncryption::None;`
- L46 _public member_ `uint8 Nonce[HORDE_NONCE_SIZE] = {};`
- L47 _public member_ `uint8 Key[HORDE_KEY_SIZE] = {};`
- L48 _public member_ `TArray<uint8> CertificateData;` — X.509 certificate for SSL connections in Pkcs12 format.
- L49 _public member_ `bool bRunsWindowOS = false;`
- L50 _public member_ `FString LeaseLink;`
- L52 _public member_ `static constexpr uint16 UbaPort = 7001;`
- L53 _public member_ `static constexpr uint16 UbaProxyPort = 7002;`
- L55 _public function_ `const FString& GetConnectionAddress() const`
- L60 _public function_ `FPortInfo GetConnectionPort() const`

#### struct `FHordeRemoteMachineInfo::FPortInfo`  
`struct FPortInfo`  
_L26-37_
- L28 _public prototype_ `FPortInfo() = default;`
- L29 _public function_ `FPortInfo(uint16 InPort, uint16 InAgentPort) : Port(InPort) , AgentPort(InAgentPort)`
- L35 _public member_ `uint16 Port = 0;`
- L36 _public member_ `uint16 AgentPort = 0;`

#### struct `FHordeClusterInfo`  
`struct FHordeClusterInfo`  
_L67-70_
- L69 _public member_ `FString ClusterId = TEXT("def`

#### struct `FHordeCacheServerInfo`  
`struct FHordeCacheServerInfo`  
_L72-77_
- L74 _public member_ `FString CacheEndpoint;` — "ip:port" format, empty if unavailable
- L75 _public member_ `FString CacheSessionKey;` — AES encryption key for cache communication
- L76 _public member_ `bool bWriteAccess = false;`

#### class `FUbaHordeMetaClient`  
`class FUbaHordeMetaClient final`  
_L81-113_
- desc: This encapsulates the mechanism of talking to the Horde "meta server". The server which can grant us access to remote machines.
- L85 _public typedef_ `using HordeMachinePromise = TPromise<TTuple<FHttpResponsePtr, FHordeRemoteMachineInfo>>;` — We return the HttpResponse in case more information could be used out of it later.
- L86 _public typedef_ `using HordeClusterPromise = TPromise<TTuple<FHttpResponsePtr, FHordeClusterInfo>>;`
- L87 _public typedef_ `using HordeCacheServerPromise = TPromise<TTuple<FHttpResponsePtr, FHordeCacheServerInfo>>;`
- L89 _public prototype_ `FUbaHordeMetaClient() = default;`
- L91 _public prototype_ `bool RefreshHttpClient();`
- L93 _public prototype_ `static FString BuildHordeRequestJsonBody(const FString& PoolId, EUbaHordeConnectionMode ConnectionMode, EUbaHordeEncryption Encryption, const TCHAR* ConditionSuffix = nullptr, bool bExclusiveAccess = true, bool bAllowWine = true);`
- L95 _public prototype_ `TSharedPtr<HordeClusterPromise, ESPMode::ThreadSafe> RequestClusterId(const FString& HordeRequestJsonBody);`
- L105 _public prototype_ `TSharedPtr<HordeMachinePromise, ESPMode::ThreadSafe> RequestMachine(const FString& HordeRequestJsonBody, const TCHAR* ClusterId = nullptr);` — This will make a request to Horde for a remote machine to do work on. Example of actually getting the FHordeRemoteMachineInfo struct: ``` auto Promise = HordeServer.RequestMachine(); auto Future = Promise->GetFuture(); ... // Can to asynchronous work auto Future.Wait(); // Wait for the response to arrive FHordeRemoteMachineInfo MachineInfo = Future.Get().Value;
- L107 _public prototype_ `TSharedPtr<HordeCacheServerPromise, ESPMode::ThreadSafe> RequestCacheServer(const TCHAR* ClusterId = nullptr);`
- L110 _private member_ `FString ServerUrl;`
- L111 _private member_ `TUniquePtr<FHordeHttpClient> HttpClient;`
- L112 _private member_ `std::atomic<bool> bClientNeedsRefresh{ true };`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUbaHorde, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUbaHorde, Log, All);`
- L15 _macro_ `#define HORDE_NONCE_SIZE 64`
- L16 _macro_ `#define HORDE_KEY_SIZE 32`

### `Source/Developer/UbaCoordinatorHorde/Public/UbaHordeAgentManager.h` (Public)


#### class `FUbaHordeAgentManager`  
`class FUbaHordeAgentManager`  
_L14-83_
- L17 _public prototype_ `FUbaHordeAgentManager(const FString& InWorkingDir, const FString& BinariesPath);`
- L18 _public prototype_ `~FUbaHordeAgentManager();`
- L20 _public prototype_ `void SetTargetCoreCount(uint32 Count);`
- L22 _public typedef_ `using FAddClientCallback = bool(void* UserData, const uba::tchar* Ip, uint16 Port, const uba::tchar* Crypto16Characters);`
- L23 _public prototype_ `void SetAddClientCallback(FAddClientCallback* Callback, void* UserData);`
- L25 _public typedef_ `using FUpdateStatusCallback = void(void* UserData, const TCHAR* Status);`
- L26 _public prototype_ `void SetUpdateStatusCallback(FUpdateStatusCallback* Callback, void* UserData);`
- L29 _public prototype_ `int32 GetAgentCount() const;` — Returns the number of agents currently handled by this agent manager.
- L32 _public prototype_ `uint32 GetActiveCoreCount() const;` — Returns the active number of cores allocated across all agents.
- L36 _public prototype_ `bool RequestCacheServer(FString& OutCacheEndpoint, FString& OutCacheSessionKey, bool& bOutWriteAccess);` — Requests a UBA cache server from Horde. Returns true if a cache server was assigned. OutCacheEndpoint will be in "ip:port" format. OutCacheSessionKey is the AES encryption key.
- L45 _private prototype_ `void RequestAgent();`
- L46 _private prototype_ `void ThreadAgent(FHordeAgentWrapper& Wrapper);`
- L47 _private prototype_ `void UpdateStatus(const TCHAR* Status);`
- L49 _private member_ `FString WorkingDir;`
- L50 _private member_ `FString BinariesPath;`
- L52 _private member_ `TUniquePtr<FUbaHordeMetaClient> HordeMetaClient;`
- L54 _private member_ `FCriticalSection BundleRefPathsLock;`
- L55 _private member_ `TArray<FString> BundleRefPaths;`
- L57 _private member_ `mutable FCriticalSection AgentsLock;`
- L58 _private member_ `TArray<TUniquePtr<FHordeAgentWrapper>> Agents;`
- L60 _private member_ `TAtomic<uint64> LastRequestFailTime;`
- L61 _private member_ `TAtomic<uint32> TargetCoreCount;`
- L62 _private member_ `TAtomic<uint32> EstimatedCoreCount;`
- L63 _private member_ `TAtomic<uint32> ActiveCoreCount;`
- L64 _private member_ `TAtomic<uint32> AgentsActive;`
- L65 _private member_ `TAtomic<uint32> AgentsRequesting;`
- L66 _private member_ `TAtomic<uint32> AgentsInProgress;`
- L67 _private member_ `TAtomic<bool> bAskForAgents;`
- L69 _private member_ `FAddClientCallback* AddClientCallback = nullptr;`
- L70 _private member_ `void* AddClientUserData = nullptr;`
- L72 _private member_ `FCriticalSection UpdateStatusLock;`
- L73 _private member_ `FString UpdateStatusText;`
- L74 _private member_ `uint32 UpdateStatusAgentsInProgress = 0;`
- L75 _private member_ `uint32 UpdateStatusAgentsActive = 0;`
- L76 _private member_ `uint32 UpdateStatusAgentsRequesting = 0;`
- L77 _private member_ `bool UpdateHadFailTime = false;`
- L78 _private member_ `FUpdateStatusCallback* UpdateStatusCallback = nullptr;`
- L79 _private member_ `void* UpdateStatusUserData = nullptr;`
- L81 _private prototype_ `FUbaHordeAgentManager(const FUbaHordeAgentManager&) = delete;`
- L82 _private prototype_ `void operator=(const FUbaHordeAgentManager&) = delete;`

#### struct `FUbaHordeAgentManager::FHordeAgentWrapper`  
`struct FHordeAgentWrapper`  
_L39-43_
- L41 _public member_ `FThread Thread;`
- L42 _public member_ `FEvent* ShouldExit;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`

### `Source/Developer/UbaCoordinatorHorde/Public/UbaHordeConfig.h` (Public)


#### enum `EUbaHordeEncryption`  
`enum class EUbaHordeEncryption`  
_L11-15_
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `AES`

#### enum `EUbaHordeConnectionMode`  
`enum class EUbaHordeConnectionMode`  
_L17-22_
- L19 _public enumerator_ `Direct`
- L20 _public enumerator_ `Tunnel`
- L21 _public enumerator_ `Relay`

#### enum `EUbaHordeEnabledMode`  
`enum class EUbaHordeEnabledMode`  
_L24-29_
- L26 _public enumerator_ `Disabled`
- L27 _public enumerator_ `EnabledForBuildMachineOnly`
- L28 _public enumerator_ `Enabled`

#### class `FUbaHordeConfig`  
`class FUbaHordeConfig`  
_L32-115_
- desc: UBA/Horde configuration structure. This is meant to match the C# version UnrealBuildTool.UnrealBuildAcceleratorHordeConfig.
- L35 _public member_ `static const TCHAR* ClusterDefault;`
- L36 _public member_ `static const TCHAR* ClusterAuto;`
- L39 _public member_ `FString Provider;` — Selected Horde provider, e.g. "Uba.Provider.Horde" by default
- L42 _public member_ `bool bIsProviderEnabled = false;` — Specifies whether UBA/Horde is enabled for the current session. By default disabled.
- L45 _public member_ `FString HordePool;` — Horde pool name.
- L48 _public member_ `FString HordeServer;` — URI of the Horde server.
- L51 _public member_ `FString HordeToken;` — Authentication token for the Horde server.
- L54 _public member_ `FString HordeCondition;` — Requirements for the Horde agent to assign.
- L57 _public member_ `FString HordeCluster = FUbaHordeConfig::ClusterDefault;` — Compute cluster ID to use in Horde. Set to "_auto" to let Horde server resolve a suitable cluster. By default "default".
- L60 _public member_ `FString HordeHost;` — Which IP address UBA server should assign to agents.
- L63 _public member_ `FString UbaSentryUrl;` — Optional sentry URL to send UBA data to.
- L66 _public member_ `int32 HordeMaxCores = 2048;` — Maxmium number of CPU cores allowed to be used by build session.
- L69 _public member_ `int32 HordeMaxWorkers = 64;` — Maximum workers allowed to be used by build session.
- L72 _public member_ `int32 MaxParallelActions = -1;` — Maximum number of local CPU cores allowed to be used by build session. By default -1, which indicates to use as many CPU cores as the local machine can provide.
- L75 _public member_ `bool bHordeAllowWine = true;` — Allow use of POSIX/Wine. Only applicable to Horde agents running Linux. Can still be ignored if Wine executable is not set on agent.
- L78 _public member_ `EUbaHordeConnectionMode HordeConnectionMode = EUbaHordeConnectionMode::Direct;` — Specifies how to connect to the remote machine. Relay mode implies encrypted connections.
- L81 _public member_ `EUbaHordeEncryption HordeEncryption = EUbaHordeEncryption::None;` — Specifies transport layer encryption. Currently only AES encryption is supported.
- L84 _public prototype_ `const FString& GetHordePool() const;` — Returns the active Horde pool depending on override settings and current desktop platform.
- L87 _public prototype_ `static const FUbaHordeConfig& Get();` — Returns the global UBA/Horde configuration and initializes it from a list of XML files on the first call.
- L92 _public member_ `FString DefaultHordePool;` — `UE_DEPRECATED(5.6, "Use HordePool instead.")`
- L95 _public member_ `FString OverrideHordePool;` — `UE_DEPRECATED(5.6, "Use HordePool instead.")`
- L98 _public member_ `FString WindowsHordePool;` — `UE_DEPRECATED(5.6, "Use HordePool instead. Windows specific pool can be set via [Uba.Provider.Horde]:Pool in Config/Win64/BaseEngine.ini")`
- L101 _public member_ `FString MacHordePool;` — `UE_DEPRECATED(5.6, "Use HordePool instead. Mac specific pool can be set via [Uba.Provider.Horde]:Pool in Config/Mac/BaseEngine.ini")`
- L104 _public member_ `FString LinuxHordePool;` — `UE_DEPRECATED(5.6, "Use HordePool instead. Linux specific pool can be set via [Uba.Provider.Horde]:Pool in Config/Linux/BaseEngine.ini")`
- L107 _public member_ `EUbaHordeEnabledMode HordeEnabled = EUbaHordeEnabledMode::Disabled;` — `UE_DEPRECATED(5.6, "Use bIsProviderEnabled instead")`
- L110 _public prototype_ `bool IsHordeEnabled() const;` — `UE_DEPRECATED(5.6, "Use bIsProviderEnabled instead")`
- L113 _private prototype_ `void Initialize();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L117 _prototype_ `const TCHAR* LexToString(EUbaHordeConnectionMode InConnectionMode);`
- L118 _prototype_ `bool LexFromString(EUbaHordeConnectionMode& OutConnectionMode, const TCHAR* InString);`
- L120 _prototype_ `const TCHAR* LexToString(EUbaHordeEncryption InEncryption);`
- L121 _prototype_ `bool LexFromString(EUbaHordeEncryption& OutEncryption, const TCHAR* InString);`
- L123 _prototype_ `const TCHAR* LexToString(EUbaHordeEnabledMode InEnabledMode);`
- L124 _prototype_ `bool LexFromString(EUbaHordeEnabledMode& OutEnabledMode, const TCHAR* InString);`
