# Plugins / CaptureManagerUnrealEndpoint

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint`
- headers: 8; symbols: 158
- symbol kinds: class=9, delegate=8, enum=1, enumerator=2, function=1, member=44, namespace=8, prototype=82, struct=3
- PrivateDependencyModuleNames: CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureUtils, Engine, LiveLinkHubCaptureMessaging, MessagingCommon
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Private/CaptureManagerUnrealEndpointLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureManagerUnrealEndpoint, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureManagerUnrealEndpoint, Log, All);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Private/DiscoveryRequester.h` (Private)


#### class `UE::CaptureManager::FDiscoveredClient`  
`class FDiscoveredClient`  
_L12-49_
- L16 _public prototype_ `FDiscoveredClient(FGuid InClientID, FString InHostName, FString InIPAddress, uint16 InPort, FMessageAddress InMessageAddress);`
- L22 _public prototype_ `FDiscoveredClient(const FDiscoveredClient& InOther);`
- L23 _public prototype_ `FDiscoveredClient(FDiscoveredClient&& InOther);`
- L25 _public prototype_ `bool IsActive() const;`
- L27 _public prototype_ `FGuid GetClientID() const;`
- L28 _public prototype_ `FString GetHostName() const;`
- L29 _public prototype_ `FString GetIPAddress() const;`
- L30 _public prototype_ `uint16 GetExportPort() const;`
- L31 _public prototype_ `FMessageAddress GetMessageAddress() const;`
- L33 _public prototype_ `void SetLastDiscoveryResponse(double InLastDiscoveryResponse);`
- L39 _private member_ `static constexpr double InactiveTimeout = 20.0f;`
- L41 _private member_ `FGuid ClientID;`
- L42 _private member_ `FString HostName;`
- L43 _private member_ `FString IPAddress;`
- L44 _private member_ `uint16 ExportPort;`
- L46 _private member_ `FMessageAddress MessageAddress;`
- L48 _private member_ `std::atomic<double> LastDiscoveryResponse = 0.0f;`

#### class `UE::CaptureManager::FDiscoveryRequester`  
`class FDiscoveryRequester`  
_L51-72_
- L54 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FClientFound, const FDiscoveredClient& InClient);`
- L55 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FClientLost, const FGuid& InClientId);`
- L57 _public prototype_ `static TUniquePtr<FDiscoveryRequester> Create();`
- L58 _public prototype_ `~FDiscoveryRequester();`
- L60 _public prototype_ `void Start();`
- L61 _public prototype_ `TArray<FDiscoveredClient> GetDiscoveredClients() const;`
- L63 _public prototype_ `FClientFound& ClientFound();`
- L64 _public prototype_ `FClientLost& ClientLost();`
- L69 _private prototype_ `explicit FDiscoveryRequester(TUniquePtr<FImpl> InImpl);`
- L71 _private member_ `TUniquePtr<FImpl> Impl;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubDiscovery, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkHubDiscovery, Log, All);`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L54 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FClientFound, const FDiscoveredClient& InClient);`
- L55 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FClientLost, const FGuid& InClientId);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Private/LiveLinkHubExportClient.h` (Private)


#### class `FLiveLinkHubExportClient`  
`class FLiveLinkHubExportClient : public TSharedFromThis<FLiveLinkHubExportClient>`  
_L23-93_
- inherits: `TSharedFromThis<FLiveLinkHubExportClient>`
- L28 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnDataUploaded, const FGuid& InTakeUploadId, FUploadVoidResult InResult);`
- L39 _public prototype_ `FLiveLinkHubExportClient(FGuid InClientId, FOnDataUploaded InOnDataUploaded);`
- L40 _public prototype_ `~FLiveLinkHubExportClient();`
- L42 _public prototype_ `void AddTakeForUpload(const FTakeUploadParams& TakeUploadParams, const FString& InTakeDirectory, const FTakeMetadata& InTakeMetadata);`
- L46 _public prototype_ `void AbortCurrentTakeUpload();`
- L48 _public prototype_ `int32 GetTaskCount() const;`
- L49 _public prototype_ `bool HasTasks() const;`
- L73 _private prototype_ `FUploadVoidResult SendTakeHeader(const FTakeUploadParams& InTakeUploadParams, const FTakeMetadata& InTake, const uint64 InTotalLength);`
- L74 _private prototype_ `FUploadVoidResult SendFile(const FString& InFileName, const FString& InFilePath, const UE::CaptureManager::FStopToken& InStopToken);`
- L75 _private prototype_ `FUploadVoidResult SendFileHeader(const FString& InFileName, const FString& InFilePath);`
- L76 _private prototype_ `FUploadVoidResult SendFileData(const FString& InFilePath, const UE::CaptureManager::FStopToken& InStopToken);`
- L78 _private prototype_ `uint64 GetTotalSizeBytes(const FString& InTakeStorage) const;`
- L80 _private prototype_ `void OnUploadTake(TUniquePtr<FTransferContext> InTransferContext);`
- L81 _private prototype_ `bool RestartConnection(const FString& InIpAddress, uint16 InPort);`
- L82 _private prototype_ `bool Disconnect();`
- L84 _private member_ `FGuid ClientId;`
- L85 _private member_ `FOnDataUploaded OnDataUploaded;`
- L87 _private member_ `std::atomic<int32> TaskCounter = 0;`
- L88 _private member_ `UE::CaptureManager::FStopRequester StopRequester;`
- L89 _private member_ `TUniquePtr<UE::CaptureManager::FTcpClient> TcpClient;`
- L90 _private member_ `UE::CaptureManager::TQueueRunner<TUniquePtr<FTransferContext>> UploadQueueRunner;`
- L92 _private member_ `IFileManager& FileManager;`

#### struct `FLiveLinkHubExportClient::FTakeUploadParams`  
`struct FTakeUploadParams`  
_L30-37_
- L32 _public member_ `FGuid CaptureSourceId;`
- L33 _public member_ `FString CaptureSourceName;`
- L34 _public member_ `FGuid TakeUploadId;`
- L35 _public member_ `FString IpAddress;`
- L36 _public member_ `uint16 Port = 0;`

#### struct `FLiveLinkHubExportClient::FTransferContext`  
`struct FTransferContext`  
_L53-71_
- L55 _public function_ `FTransferContext(const FTakeUploadParams& InTakeUploadParams, FString InTakeStorage, FTakeMetadata InTakeMetadata, uint64 InTotalSizeBytes) : TakeUploadParams(InTakeUploadParams) , TakeStorage(MoveTemp(InTakeStorage)) , TakeMetadata(MoveTemp(InTakeMetadata)) , TotalSizeBytes(InTotalSizeBytes)`
- L66 _public member_ `FTakeUploadParams TakeUploadParams;`
- L68 _public member_ `FString TakeStorage;`
- L69 _public member_ `FTakeMetadata TakeMetadata;`
- L70 _public member_ `uint64 TotalSizeBytes;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace CaptureManager` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDataUploaded, const FGuid& InTakeUploadId, FUploadVoidResult InResult);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Private/LiveLinkHubExportManager.h` (Private)


#### class `FLiveLinkHubExportManager`  
`class FLiveLinkHubExportManager`  
_L7-35_
- L11 _public prototype_ `FLiveLinkHubExportManager(FGuid InClientId, FLiveLinkHubExportClient::FOnDataUploaded InDataUploaded, uint64 InDefaultNumberOfWorkers = DefaultNumberOfWorkers);`
- L15 _public prototype_ `~FLiveLinkHubExportManager();`
- L17 _public prototype_ `[[nodiscard]] int32 ExportTake(const FLiveLinkHubExportClient::FTakeUploadParams& InTakeUploadParams, const FString& InTakeDirectory, const FTakeMetadata& InTakeMetadata);`
- L21 _public prototype_ `bool AbortExport(int32 InWorkerId);`
- L23 _public prototype_ `FGuid GetClientId() const;`
- L27 _private member_ `static const uint64 DefaultNumberOfWorkers = 2;`
- L29 _private prototype_ `int32 GetPreferredWorkerIndex() const;`
- L31 _private member_ `FGuid ClientId;`
- L33 _private member_ `FCriticalSection Mutex;`
- L34 _private member_ `TArray<TSharedPtr<FLiveLinkHubExportClient>> Workers;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Private/UCaptureManagerUnrealEndpointManager.h` (Private)


#### class `UCaptureManagerUnrealEndpointManager`  
`class UCaptureManagerUnrealEndpointManager : public UObject`  
_L11-35_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: This class wraps an underlying Unreal Endpoint Manager so that python and blueprints can make use of it.
- L16 _public prototype_ `UCaptureManagerUnrealEndpointManager();`
- L17 _public prototype_ `~UCaptureManagerUnrealEndpointManager();`
- L21 _public prototype_ `void Start();` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkHub|CaptureManager|UnrealEndpointManager")` — Starts the endpoint manager and the discovery of unreal endpoints.
- L25 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkHub|CaptureManager|UnrealEndpointManager")` — Stops the endpoint manager.
- L30 _public prototype_ `bool WaitForEndpointByHostName(const FString& InHostName, int32 InTimeoutMS);` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkHub|CaptureManager|UnrealEndpointManager")` — Waits for an endpoint with a particular host name to be discovered or a timeout is reached. returns true if the host was found, false if the timeout was exceeded
- L34 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Public/CaptureManagerUnrealEndpoint.h` (Public)


#### class `UE::CaptureManager::FTakeUploadTask`  
`UE_INTERNAL class FTakeUploadTask`  
_L16-48_
- desc: @brief An immutable container for upload task information, also provides a place to tie into update delegates.
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FUploadProgressed, double);`
- L20 _public prototype_ `DECLARE_DELEGATE_TwoParams(FUploadComplete, const FString& InMessage, int32 InStatusCode);`
- L22 _public prototype_ `FTakeUploadTask( FGuid InTaskID, FGuid InCaptureSourceID, FString InCaptureSourceName, FString InDataDirectory, FTakeMetadata InMetadata );`
- L30 _public prototype_ `const FGuid& GetTaskID() const;`
- L31 _public prototype_ `const FGuid& GetCaptureSourceID() const;`
- L32 _public prototype_ `const FString& GetCaptureSourceName() const;`
- L33 _public prototype_ `const FString& GetDataDirectory() const;`
- L34 _public prototype_ `const FTakeMetadata& GetTakeMetadata() const;`
- L36 _public prototype_ `FUploadProgressed& Progressed();`
- L37 _public prototype_ `FUploadComplete& Complete();`
- L40 _private member_ `const FGuid TaskID;`
- L41 _private member_ `const FGuid CaptureSourceID;`
- L42 _private member_ `const FString CaptureSourceName;`
- L43 _private member_ `const FString DataDirectory;`
- L44 _private member_ `const FTakeMetadata TakeMetadata;`
- L46 _private member_ `FUploadProgressed ProgressedDelegate;`
- L47 _private member_ `FUploadComplete CompleteDelegate;`

#### struct `UE::CaptureManager::FUnrealEndpointInfo`  
`UE_INTERNAL struct FUnrealEndpointInfo`  
_L50-57_
- L52 _public member_ `FGuid EndpointID;`
- L53 _public member_ `FMessageAddress MessageAddress;`
- L54 _public member_ `FString IPAddress;`
- L55 _public member_ `FString HostName;`
- L56 _public member_ `int32 ImportServicePort = 0;`

#### class `UE::CaptureManager::FUnrealEndpoint`  
`UE_INTERNAL class FUnrealEndpoint`  
_L67-125_
- desc: @brief An ingest endpoint (UE/UEFN instance) for the Capture Manager.
- L76 _public prototype_ `explicit FUnrealEndpoint(FUnrealEndpointInfo InEndpointInfo);`
- L77 _public prototype_ `~FUnrealEndpoint();`
- L84 _public prototype_ `void StartConnection();` — @brief Starts the connection to the endpoint (if not already started). This function returns before the connection is made, use WaitForConnectionState to block until the connection is established.
- L91 _public prototype_ `void StopConnection();` — @brief Stops the connection to the endpoint (if not already stopped). This function returns before the connection is stopped, use WaitForConnectionState to block until the connection is terminated.
- L96 _public prototype_ `void Retire();` — @brief Permanently retires the endpoint and stops the connection. This prevents further API calls from functioning.
- L103 _public prototype_ `bool WaitForConnectionState(EConnectionState InConnectionState, int32 InTimeoutMs) const;` — @brief Blocks until either the connection is made or the timeout is exceeded. @returns true if the connection is ready, false if the timeout was exceeded.
- L110 _public prototype_ `bool AddTakeUploadTask(TUniquePtr<FTakeUploadTask> InTakeUploadTask);` — @brief Adds a take upload task to the queue for this endpoint. @returns true if successful, false if errors occurred.
- L115 _public prototype_ `void CancelTakeUploadTask(FGuid InTakeUploadTask);` — @brief Cancels the upload task with the supplied task ID.
- L120 _public prototype_ `FUnrealEndpointInfo GetInfo() const;` — @returns Information about the unreal endpoint.
- L124 _private member_ `TSharedPtr<FImpl> Impl;`

#### enum `UE::CaptureManager::FUnrealEndpoint::EConnectionState`  
`enum class EConnectionState`  
_L70-74_
- L72 _public enumerator_ `Disconnected`
- L73 _public enumerator_ `Connected`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FUploadProgressed, double);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FUploadComplete, const FString& InMessage, int32 InStatusCode);`
- L62 _prototype_ `UE_INTERNAL FString UnrealEndpointInfoToString(const FUnrealEndpointInfo& InEndpointInfo);` (scope `UE::CaptureManager`) — @brief Converts an endpoint info object into a string, useful for logging

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Public/CaptureManagerUnrealEndpointManager.h` (Public)


#### class `UE::CaptureManager::FUnrealEndpointManager`  
`UE_INTERNAL class FUnrealEndpointManager`  
_L17-72_
- desc: @brief Detects and manages ingest endpoints (UE/UEFN instances) for the Capture Manager.
- L20 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FEndpointsChanged);`
- L22 _public prototype_ `FUnrealEndpointManager();`
- L23 _public prototype_ `~FUnrealEndpointManager();`
- L28 _public prototype_ `void Start();` — @brief Start discovering endpoints.
- L33 _public prototype_ `void Stop();` — @brief Stop discovering endpoints.
- L40 _public prototype_ `TOptional<TWeakPtr<FUnrealEndpoint>> WaitForEndpoint(TFunction<bool(const FUnrealEndpoint&)> InPredicate, int32 InTimeoutMS);` — @brief Blocks until an endpoint matching the given predicate is discovered or the timeout (in milliseconds) is reached. @returns An optional containing a weak pointer to the endpoint if it was discovered else the optional will be empty.
- L47 _public prototype_ `TOptional<TWeakPtr<FUnrealEndpoint>> FindEndpointByPredicate(TFunction<bool(const FUnrealEndpoint&)> InPredicate);` — @brief Finds a discovered endpoint matching the given predicate. @returns An optional containing a weak pointer to the endpoint if it is found else the optional will be empty.
- L52 _public prototype_ `TArray<TWeakPtr<FUnrealEndpoint>> FindEndpointsByPredicate(TFunction<bool(const FUnrealEndpoint&)> InPredicate);` — @returns A list of weak pointers to the discovered endpoints which match the predicate.
- L57 _public prototype_ `TArray<TWeakPtr<FUnrealEndpoint>> GetEndpoints();` — @returns A list of weak pointers to the discovered endpoints.
- L62 _public prototype_ `int32 GetNumEndpoints() const;` — @returns The number of discovered endpoints
- L67 _public prototype_ `FEndpointsChanged& EndpointsChanged();` — @returns A delegate which fires whenever the discovered endpoints have changed.
- L71 _private member_ `TPimplPtr<FImpl> Impl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)
- L20 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FEndpointsChanged);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerUnrealEndpoint/Public/CaptureManagerUnrealEndpointModule.h` (Public)


#### class `FCaptureManagerUnrealEndpointModule`  
`class FCaptureManagerUnrealEndpointModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `TSharedRef<UE::CaptureManager::FUnrealEndpointManager> GetEndpointManager() const;`
- L17 _public prototype_ `TOptional<TSharedRef<UE::CaptureManager::FUnrealEndpointManager>> GetEndpointManagerIfValid() const;`
- L20 _private member_ `TSharedPtr<UE::CaptureManager::FUnrealEndpointManager> EndpointManager;`
