# Plugins / CaptureManagerDeviceBlueprint

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerDeviceBlueprint`
- headers: 5; symbols: 93
- symbol kinds: class=5, delegate=11, enum=1, enumerator=9, member=16, namespace=2, prototype=46, struct=2, typedef=1
- PrivateDependencyModuleNames: CaptureManagerCPSClient, CaptureProtocolStack, CaptureUtils
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerDeviceBlueprint/Private/CaptureManagerDeviceBatchDownloadLibrary.h` (Private)


#### struct `FCaptureManagerBatchDownloadResult`  
`struct FCaptureManagerBatchDownloadResult`  
_L19-37_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `FString TakeName;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")`
- L27 _public member_ `bool bSuccess = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")`
- L30 _public member_ `FString TakeDirectoryPath;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")`
- L33 _public member_ `ECaptureManagerDeviceError ErrorCode = ECaptureManagerDeviceError::NoError;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")`
- L36 _public member_ `FText ErrorMessage;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")`

#### class `UCaptureManagerDeviceBatchDownloadLibrary`  
`class UCaptureManagerDeviceBatchDownloadLibrary : public UBlueprintFunctionLibrary`  
_L40-96_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L60 _public prototype_ `static void DownloadDeviceTakesBatch( UCaptureManagerDeviceSession* Session, const TArray<FCaptureManagerDeviceTakeInfo>& Takes, FString DownloadRootDirectory, FCaptureManagerBatchDownloadTakeResult OnTakeSuccess, FCaptureManagerBatchDownloadTakeFailed OnTakeFailed, FCaptureManagerDeviceDownloadProgress OnTakeProgress, FCaptureManagerBatchDownloadComplete OnAllComplete);` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Download Device Takes (Batch)", Keywords = "iphone ipad livelink batch"))` — Download multiple takes sequentially from a connected device. @param Session                Session handle from ConnectToDevice. @param Takes                  Takes to download (from GetDeviceTakes, optionally filtered). @param DownloadRootDirectory  Local directory to download into. Subdirectories are created per take. If a subdirectory already exists it is deleted first. @param OnTakeSuccess          Called on the game thread when each take completes. @param OnTakeFailed           Called on the game thread when each take fails. @param OnTakeProgress         Called on the game thread with download progress (0.0 to 1.0) per take. @param OnAllComplete          Called on the game thread when all takes have been processed.
- L81 _public prototype_ `static TArray<FCaptureManagerBatchDownloadResult> DownloadDeviceTakesBatchSync( UCaptureManagerDeviceSession* Session, const TArray<FCaptureManagerDeviceTakeInfo>& Takes, const FString& DownloadRootDirectory);` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device|Blocking", meta = (DisplayName = "Download Device Takes (Batch)", ReturnDisplayName = "Results", Keywords = "iphone ipad livelink batch"))` — Download multiple takes sequentially from a connected device, blocking until all complete. @param Session                Session handle from ConnectToDevice. @param Takes                  Takes to download (from GetDeviceTakes, optionally filtered). @param DownloadRootDirectory  Local directory to download into. Subdirectories are created per take. If a subdirectory already exists it is deleted first. @return                       Per-take results with success/failure status and paths.
- L95 _public prototype_ `static void CancelBatchDownload(UCaptureManagerDeviceSession* Session);` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Cancel Batch Download", Keywords = "abort stop batch"))` — Cancel a batch download. The current take fails with a Canceled error and remaining takes are skipped. @param Session  Session handle from ConnectToDevice.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FCaptureManagerBatchDownloadTakeResult, UCaptureManagerDeviceSession*, Session, FString, TakeName, FString, TakeDirectoryPath, int32, RemainingCount);`
- L11 _prototype_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FCaptureManagerBatchDownloadTakeResult, UCaptureManagerDeviceSession*, Session, FString, TakeName, FString, TakeDirectoryPath, int32, RemainingCount);`
- L13 _delegate_ `DECLARE_DYNAMIC_DELEGATE_FiveParams(FCaptureManagerBatchDownloadTakeFailed, UCaptureManagerDeviceSession*, Session, FString, TakeName, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage, int32, RemainingCount);`
- L13 _prototype_ `DECLARE_DYNAMIC_DELEGATE_FiveParams(FCaptureManagerBatchDownloadTakeFailed, UCaptureManagerDeviceSession*, Session, FString, TakeName, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage, int32, RemainingCount);`
- L15 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerBatchDownloadComplete, UCaptureManagerDeviceSession*, Session, int32, SucceededCount, int32, FailedCount);`
- L15 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerBatchDownloadComplete, UCaptureManagerDeviceSession*, Session, int32, SucceededCount, int32, FailedCount);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerDeviceBlueprint/Private/CaptureManagerDeviceBlueprintLibrary.h` (Private)


#### class `UCaptureManagerDeviceBlueprintLibrary`  
`class UCaptureManagerDeviceBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L20-199_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L45 _public prototype_ `static void ConnectToDevice( FString DeviceName, FString IpAddress, int32 Port, int32 TimeoutSeconds, FCaptureManagerDeviceConnected OnSuccess, FCaptureManagerDeviceConnectFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Connect to Device", Keywords = "iphone ipad livelink", Port = "14785", TimeoutSeconds = "30"))` — Connect to a device (e.g. LiveLink Face on iPhone/iPad) by IP address. Returns a session handle via OnSuccess, used by all subsequent device operations. Note: The device uses a second port for file transfers, reported during connection. If downloads fail while the connection succeeds, check that this port is also accessible through any firewalls. @param DeviceName      Optional display name for the device. Stored on the session for use in logging and error messages. Defaults to "IP:Port" if empty. @param IpAddress       IP address of the device. @param Port            Default is 14785. @param TimeoutSeconds  Maximum time to wait for connection. @param OnSuccess       Called on the game thread when connected. @param OnFailure       Called on the game thread if the connection fails or times out.
- L64 _public prototype_ `static void GetDeviceTakes( UCaptureManagerDeviceSession* Session, FCaptureManagerDeviceGetTakesResult OnSuccess, FCaptureManagerDeviceGetTakesFailed OnFailure );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Get Device Takes", Keywords = "iphone ipad livelink fetch"))` — Retrieve the list of takes available on a connected device. @param Session    Session handle from ConnectToDevice. @param OnSuccess  Called on the game thread when the fetch succeeds. @param OnFailure  Called on the game thread if the fetch fails.
- L83 _public prototype_ `static void DownloadDeviceTake( UCaptureManagerDeviceSession* Session, FString TakeName, FString DownloadRootDirectory, FCaptureManagerDeviceDownloadResult OnSuccess, FCaptureManagerDeviceDownloadFailed OnFailure, FCaptureManagerDeviceDownloadProgress OnProgress );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Download Device Take", Keywords = "iphone ipad livelink"))` — Download a take from a connected device to a local directory. The downloaded directory can be passed directly to Ingest Live Link Face. @param Session                Session handle from ConnectToDevice. @param TakeName               Name of the take to download (from GetDeviceTakes). @param DownloadRootDirectory  Local directory to download into. A subdirectory named after the take is created automatically. If the subdirectory already exists it is deleted first. @param OnSuccess              Called on the game thread when the download completes. @param OnFailure              Called on the game thread if the download fails. @param OnProgress             Called on the game thread with download progress (0.0 to 1.0).
- L103 _public prototype_ `static bool CancelDeviceDownload( UCaptureManagerDeviceSession* Session, FString TakeName, FText& ErrorMessage);` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Cancel Device Download", Keywords = "abort stop"))` — Cancel an in-flight download by take name. The download's OnFailure callback will fire with a cancellation error. @param Session       Session handle from ConnectToDevice. @param TakeName      Name of the take whose download to cancel. @param ErrorMessage  Populated on failure with a description of why cancellation failed. @return              True if a download for this take was found and cancellation was initiated. False if no active download exists for this take.
- L117 _public prototype_ `static void DisconnectDevice( UCaptureManagerDeviceSession* Session, FCaptureManagerDeviceDisconnected OnComplete );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device", meta = (DisplayName = "Disconnect Device", Keywords = "close"))` — Disconnect from a device and release the session. Cancels any in-flight downloads. Safe to call with a null session. @param Session     Session handle to disconnect. @param OnComplete  Called on the game thread when the session is fully torn down.
- L130 _public prototype_ `static void DisconnectDeviceSync(UCaptureManagerDeviceSession* Session);` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device|Blocking", meta = (DisplayName = "Disconnect Device", Keywords = "close"))` — Disconnect from a device, blocking until teardown is complete. Cancels any in-flight downloads. Safe to call with a null session. @param Session  Session handle to disconnect.
- L150 _public prototype_ `static UCaptureManagerDeviceSession* ConnectToDeviceSync( const FString& DeviceName, const FString& IpAddress, int32 Port, int32 TimeoutSeconds, ECaptureManagerDeviceError& ErrorCode, FText& ErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device|Blocking", meta = (DisplayName = "Connect to Device", ReturnDisplayName = "Session", Keywords = "iphone ipad livelink", Port = "14785", TimeoutSeconds = "30"))` — Connect to a device and block until connected or timed out. Intended for Python scripts and other contexts where blocking is acceptable. @param DeviceName      Optional display name for the device. Defaults to "IP:Port" if empty. @param IpAddress       IP address of the device. @param Port            Default is 14785. @param TimeoutSeconds  Maximum time to wait for connection. @param ErrorCode       Error code on failure. @param ErrorMessage    Error description on failure. @return                Session handle on success, nullptr on failure.
- L171 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> GetDeviceTakesSync( UCaptureManagerDeviceSession* Session, ECaptureManagerDeviceError& ErrorCode, FText& ErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device|Blocking", meta = (DisplayName = "Get Device Takes", ReturnDisplayName = "Takes", Keywords = "iphone ipad livelink fetch"))` — Retrieve the list of takes available on a connected device, blocking until complete. @param Session       Session handle from ConnectToDevice. @param ErrorCode     Error code on failure. @param ErrorMessage  Error description on failure. @return              Array of take info. Empty on failure or if no takes exist.
- L192 _public prototype_ `static FString DownloadDeviceTakeSync( UCaptureManagerDeviceSession* Session, const FString& TakeName, const FString& DownloadRootDirectory, ECaptureManagerDeviceError& ErrorCode, FText& ErrorMessage );` — `UFUNCTION(BlueprintCallable, Category = "CaptureManager|Device|Blocking", meta = (DisplayName = "Download Device Take", ReturnDisplayName = "TakeDirectoryPath", Keywords = "iphone ipad livelink"))` — Download a take from a connected device, blocking until complete. The returned directory can be passed directly to Ingest Live Link Face. @param Session                Session handle from ConnectToDevice. @param TakeName               Name of the take to download (from GetDeviceTakes). @param DownloadRootDirectory  Local directory to download into. A subdirectory named after the take is created automatically. If the subdirectory already exists it is deleted first. @param ErrorCode              Error code on failure. @param ErrorMessage           Error description on failure. @return                       Full path to the downloaded take directory. Empty on failure.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCaptureManagerDeviceConnected, UCaptureManagerDeviceSession*, Session);`
- L10 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCaptureManagerDeviceConnected, UCaptureManagerDeviceSession*, Session);`
- L11 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceConnectFailed, FString, DeviceName, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage);`
- L11 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceConnectFailed, FString, DeviceName, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage);`
- L12 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FCaptureManagerDeviceGetTakesResult, UCaptureManagerDeviceSession*, Session, const TArray<FCaptureManagerDeviceTakeInfo>&, Takes);`
- L12 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FCaptureManagerDeviceGetTakesResult, UCaptureManagerDeviceSession*, Session, const TArray<FCaptureManagerDeviceTakeInfo>&, Takes);`
- L13 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceGetTakesFailed, UCaptureManagerDeviceSession*, Session, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage);`
- L13 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceGetTakesFailed, UCaptureManagerDeviceSession*, Session, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage);`
- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceDownloadResult, UCaptureManagerDeviceSession*, Session, FString, TakeName, FString, TakeDirectoryPath);`
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceDownloadResult, UCaptureManagerDeviceSession*, Session, FString, TakeName, FString, TakeDirectoryPath);`
- L15 _delegate_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FCaptureManagerDeviceDownloadFailed, UCaptureManagerDeviceSession*, Session, FString, TakeName, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage);`
- L15 _prototype_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FCaptureManagerDeviceDownloadFailed, UCaptureManagerDeviceSession*, Session, FString, TakeName, ECaptureManagerDeviceError, ErrorCode, FText, ErrorMessage);`
- L16 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceDownloadProgress, UCaptureManagerDeviceSession*, Session, FString, TakeName, float, Progress);`
- L16 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCaptureManagerDeviceDownloadProgress, UCaptureManagerDeviceSession*, Session, FString, TakeName, float, Progress);`
- L17 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FCaptureManagerDeviceDisconnected);`
- L17 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FCaptureManagerDeviceDisconnected);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerDeviceBlueprint/Private/CaptureManagerDeviceBlueprintModule.h` (Private)


#### class `FCaptureManagerDeviceBlueprintModule`  
`class FCaptureManagerDeviceBlueprintModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public prototype_ `void StartupModule() override;`
- L14 _public prototype_ `void ShutdownModule() override;`
- L16 _public prototype_ `void RegisterSession(UCaptureManagerDeviceSession* Session);`
- L17 _public prototype_ `void UnregisterSession(UCaptureManagerDeviceSession* Session);`
- L20 _private member_ `FCriticalSection SessionsMutex;`
- L21 _private member_ `TArray<TStrongObjectPtr<UCaptureManagerDeviceSession>> ActiveSessions;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerDeviceBlueprint/Private/CaptureManagerDeviceSession.h` (Private)


#### enum `ECaptureManagerDeviceError`  
`enum class ECaptureManagerDeviceError : uint8`  
_L17-28_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `NoError UMETA(DisplayName = "No Error")`
- L20 _public enumerator_ `Unknown UMETA(DisplayName = "Unknown")`
- L21 _public enumerator_ `InvalidArgument UMETA(DisplayName = "Invalid Argument")`
- L22 _public enumerator_ `ConnectionTimeout UMETA(DisplayName = "Connection Timeout")`
- L23 _public enumerator_ `Disconnected UMETA(DisplayName = "Disconnected")`
- L24 _public enumerator_ `TakeNotFound UMETA(DisplayName = "Take Not Found")`
- L25 _public enumerator_ `DownloadFailed UMETA(DisplayName = "Download Failed")`
- L26 _public enumerator_ `Canceled UMETA(DisplayName = "Canceled")`
- L27 _public enumerator_ `ProtocolError UMETA(DisplayName = "Protocol Error")`

#### struct `FCaptureManagerDeviceTakeInfo`  
`struct FCaptureManagerDeviceTakeInfo`  
_L32-55_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metadata for a single take on a connected device.
- L38 _public member_ `FString TakeName;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")` — Unique name identifying this take on the device.
- L42 _public member_ `FString Slate;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")` — Slate Name.
- L46 _public member_ `int32 TakeNumber = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")` — Take number within the slate.
- L50 _public member_ `FDateTime DateTime;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")` — When this take was recorded.
- L54 _public member_ `int64 TotalSizeBytes = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "Device")` — Total size of all files in this take, in bytes.

#### class `UCaptureManagerDeviceSession`  
`class UCaptureManagerDeviceSession : public UObject`  
_L59-104_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Represents a connection to a device. Obtained from UCaptureManagerDeviceBlueprintLibrary and passed to all device operations.
- L68 _public prototype_ `~UCaptureManagerDeviceSession();`
- L72 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Device")` — Display name for this device. Defaults to "IP:Port" on connect. Set to a friendly name if desired.
- L74 _public prototype_ `bool Connect(const FString& IpAddress, int32 Port, int32 TimeoutSeconds, ECaptureManagerDeviceError& OutErrorCode, FText& OutErrorMessage);`
- L75 _public prototype_ `void Disconnect();`
- L77 _public prototype_ `bool FetchTakes(TArray<FCaptureManagerDeviceTakeInfo>& OutTakes, ECaptureManagerDeviceError& OutErrorCode, FText& OutErrorMessage);`
- L79 _public typedef_ `using FOnDownloadProgress = TFunction<void(float Progress)>;`
- L80 _public prototype_ `bool DownloadTake(const FString& TakeName, const FString& DownloadRootDirectory, FString& OutTakeDirectory, ECaptureManagerDeviceError& OutErrorCode, FText& OutErrorMessage, FOnDownloadProgress OnProgress = nullptr);`
- L82 _public prototype_ `bool CancelDownload(const FString& TakeName, FText& OutErrorMessage);`
- L84 _public prototype_ `void CancelAllDownloads();`
- L85 _public prototype_ `bool IsDownloadCancelRequested() const;`
- L86 _public prototype_ `void ClearDownloadCancelRequest();`
- L89 _public prototype_ `bool IsConnected() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Device")`
- L96 _private prototype_ `TSharedPtr<FImpl, ESPMode::ThreadSafe> AcquireImpl() const;` — Returns the current FImpl, or null if disconnected. Does not prevent Disconnect() from proceeding.
- L99 _private prototype_ `UE::CaptureManager::FScopedOperation AcquireImplForOperation() const;` — Returns a scoped handle that keeps an operation in-flight so Disconnect() waits for it to finish. The operation is automatically released when the handle is destroyed.
- L101 _private member_ `mutable FCriticalSection ImplMutex;`
- L102 _private member_ `TSharedPtr<FImpl, ESPMode::ThreadSafe> Impl;`
- L103 _private member_ `bool bConnectCanceled = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerDeviceBlueprint/Private/CaptureManagerDeviceTakeFiltersLibrary.h` (Private)


#### class `UCaptureManagerDeviceTakeFiltersLibrary`  
`class UCaptureManagerDeviceTakeFiltersLibrary : public UBlueprintFunctionLibrary`  
_L11-103_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> FilterTakesBySlate( const TArray<FCaptureManagerDeviceTakeInfo>& Takes, FString SlatePattern, bool bExclude = false);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Filter Takes (Slate)", ReturnDisplayName = "FilteredTakes", Keywords = "wildcard exclude"))` — Filter takes by slate name. Supports * wildcard. Case-insensitive.
- L37 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> FilterTakesByDateRange( const TArray<FCaptureManagerDeviceTakeInfo>& Takes, FDateTime AfterDateTime, FDateTime BeforeDateTime);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Filter Takes (Date Range)", ReturnDisplayName = "FilteredTakes", Keywords = "time before after range"))` — Filter takes by date range. Either bound can be omitted - leave the pin unconnected in Blueprint, or pass FDateTime() in C++.
- L51 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> GetLatestTakes( const TArray<FCaptureManagerDeviceTakeInfo>& Takes, int32 Count);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Get Latest Takes", ReturnDisplayName = "Takes", Keywords = "recent last newest", Count = "1"))` — Return the N most recent takes, sorted newest first. Pass 1 to get the single latest take. Pass 0 or negative to return all takes sorted.
- L64 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> GetOldestTakes( const TArray<FCaptureManagerDeviceTakeInfo>& Takes, int32 Count);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Get Oldest Takes", ReturnDisplayName = "Takes", Keywords = "oldest first earliest", Count = "1"))` — Return the N oldest takes, sorted oldest first. Pass 1 to get the single oldest take. Pass 0 or negative to return all takes sorted.
- L77 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> GetLargestTakes( const TArray<FCaptureManagerDeviceTakeInfo>& Takes, int32 Count);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Get Largest Takes", ReturnDisplayName = "Takes", Keywords = "size bytes biggest", Count = "1"))` — Return the N largest takes by total file size, sorted largest first. Pass 1 to get the single largest take. Pass 0 or negative to return all takes sorted.
- L90 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> GetSmallestTakes( const TArray<FCaptureManagerDeviceTakeInfo>& Takes, int32 Count);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Get Smallest Takes", ReturnDisplayName = "Takes", Keywords = "size bytes smallest least", Count = "1"))` — Return the N smallest takes by total file size, sorted smallest first. Pass 1 to get the single smallest take. Pass 0 or negative to return all takes sorted.
- L102 _public prototype_ `static TArray<FCaptureManagerDeviceTakeInfo> GetLatestSlate(const TArray<FCaptureManagerDeviceTakeInfo>& Takes);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CaptureManager|Device|Filters", meta = (DisplayName = "Get Latest Slate", ReturnDisplayName = "Takes", Keywords = "recent last newest current"))` — Return all takes from the most recent slate. Finds the newest take, then returns every take with the same slate name.
