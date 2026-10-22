# Runtime / BackgroundHTTP

- module root: `Source/Runtime/Online/BackgroundHTTP`
- headers: 27; symbols: 302
- symbol kinds: class=19, delegate=8, enum=2, enumerator=7, function=22, member=57, prototype=173, struct=1, typedef=13
- PublicDependencyModuleNames: ApplicationCore, BackgroundHTTPFileHash, BackgroundHttpIOS, Core, CoreUObject, Engine, HTTP
- PublicIncludePathModuleNames: HTTP

### `Source/Runtime/Online/BackgroundHTTP/Public/Android/AndroidPlatformBackgroundHttp.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FModularFeaturePlatformBackgroundHttp FPlatformBackgroundHttp;` — Android makes use of a modular game feature for it's BackgroundHttp implementation

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttp.h` (Public)


#### Free symbols / members of external scopes

- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackgroundHttp, Display, All);`

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttpManagerImpl.h` (Public)


#### class `FBackgroundHttpManagerImpl`  
`class FBackgroundHttpManagerImpl : public IBackgroundHttpManager , public FTSTickerObjectBase`  
_L24-100_
- inherits: `IBackgroundHttpManager,FTSTickerObjectBase`
- desc: Contains implementation of some common functions that don't vary between implementation
- L29 _public prototype_ `FBackgroundHttpManagerImpl();`
- L30 _public prototype_ `virtual ~FBackgroundHttpManagerImpl();`
- L32 _public prototype_ `virtual void AddRequest(const FBackgroundHttpRequestPtr Request) override;`
- L33 _public prototype_ `virtual void RemoveRequest(const FBackgroundHttpRequestPtr Request) override;`
- L35 _public prototype_ `virtual void Initialize(bool bClearPreExistingRequestsAtStartup) override;`
- L36 _public prototype_ `virtual void Shutdown() override;`
- L38 _public prototype_ `virtual void DeleteAllTemporaryFiles() override;`
- L40 _public prototype_ `virtual int GetMaxActiveDownloads() const override;`
- L41 _public prototype_ `virtual void SetMaxActiveDownloads(int MaxActiveDownloads) override;`
- L44 _public prototype_ `virtual FString GetTempFileLocationForURL(const FString& URL, const FString& RequestID) override;`
- L46 _public prototype_ `virtual void CleanUpDataAfterCompletingRequest(const FBackgroundHttpRequestPtr Request) override;`
- L48 _public prototype_ `virtual void SetCellularPreference(int32 Value) override;`
- L49 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) override;`
- L52 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase implementation
- L55 _protected prototype_ `virtual bool AssociateWithAnyExistingRequest(const FBackgroundHttpRequestPtr Request) override;`
- L57 _protected prototype_ `virtual bool CheckForExistingCompletedDownload(const FBackgroundHttpRequestPtr Request, FString& ExistingFilePathOut, int64& ExistingFileSizeOut);`
- L58 _protected prototype_ `virtual void ActivatePendingRequests();`
- L61 _protected prototype_ `virtual void DeleteStaleTempFiles();` — Different from DeleteAllTemporaryFiles as this doesn't delete all files but rather cleans up specific bad files that have gone stale
- L64 _protected prototype_ `virtual void GatherAllTempFilenames(TArray<FString>& OutAllTempFilenames, bool bOutputAsFullPaths = false) const;` — Gets a list of full filenames for all temp files.
- L67 _protected prototype_ `virtual void ConvertAllTempFilenamesToFullPaths(TArray<FString>& OutFilenamesAsFullPaths, const TArray<FString>& FilenamesToConvertToFullPaths) const;` — Helper function that converts the supplied list of Temp folder filenames to a list that is always all full paths.
- L72 _protected prototype_ `virtual void GatherTempFilesOlderThen(TArray<FString>& OutTimedOutTempFilenames,double SecondsToConsiderOld, TArray<FString>* OptionalFileList = nullptr) const;` — Gather a list of any temp files that have timed out of our BackgroundHTTP settings. SecondsToConsiderOld should be a double representing how many seconds old a temp file needs to be to be returned by this function If OptionalFileListToCheck is empty will check all temp files in the backgroundhttp temp file folder. If supplied only the given file paths are checked
- L76 _protected prototype_ `virtual void GatherTempFilesWithoutURLMappings(TArray<FString>& OutTempFilesMissingURLMappings, TArray<FString>* OptionalFileList = nullptr) const;` — Gather a list of any temp files that have no corresponding URL Mapping entry If OptionalFileListToCheck is empty will check all temp files in the backgroundhttp temp file folder. If supplied only the given file paths are checked
- L79 _protected function_ `virtual BackgroundHttpFileHashHelperRef GetFileHashHelper()` — Gets our FileHashHelper to compute temp file mappings
- L80 _protected function_ `virtual const BackgroundHttpFileHashHelperRef GetFileHashHelper() const`
- L83 _protected prototype_ `virtual int DeleteAllTemporaryFiles(bool Recursively, const TCHAR* FileExtension);` — Returns number of deleted files
- L87 _protected member_ `TArray<FBackgroundHttpRequestPtr> PendingStartRequests;` — List of Background Http requests that we have called AddRequest on, but have not yet started due to platform active download limits
- L88 _protected member_ `FRWLock PendingRequestLock;`
- L91 _protected member_ `TArray<FBackgroundHttpRequestPtr> ActiveRequests;` — List of Background Http requests that are actively being processed
- L92 _protected member_ `mutable FRWLock ActiveRequestLock;`
- L95 _protected member_ `volatile int NumCurrentlyActiveRequests;` — Count of how many requests we have active
- L96 _protected member_ `TAtomic<int> MaxActiveDownloads;`
- L99 _private member_ `BackgroundHttpFileHashHelperRef FileHashHelper;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackgroundHttpManager, Log, All) class FBackgroundHttpFileHashHelper;`

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttpMetrics.h` (Public)


#### struct `FBackgroundHttpRequestMetricsExtended`  
`struct FBackgroundHttpRequestMetricsExtended`  
_L7-13_
- L9 _public member_ `int32 TotalBytesDownloaded;`
- L10 _public member_ `float DownloadDuration;`
- L11 _public member_ `FDateTime FetchStartTimeUTC;`
- L12 _public member_ `FDateTime FetchEndTimeUTC;`

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttpModule.h` (Public)


#### class `FBackgroundHttpModule`  
`class FBackgroundHttpModule : public IModuleInterface`  
_L15-71_
- inherits: `IModuleInterface`
- desc: Module for Http Background request implementations
- L25 _public prototype_ `static FBackgroundHttpModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public prototype_ `static FBackgroundHttpRequestPtr CreateBackgroundRequest();` — Creates a BackgroundRequest through the appropriate platform-layer. @return SharedRef to the new BackgroundRequest.
- L39 _public prototype_ `FBackgroundHttpManagerPtr GetBackgroundHttpManager();` — Gets the current BackgroundHttpManager from the appropriate platform layer. @return SharedPtr to the BackgroundHttpManager.
- L46 _public prototype_ `static void ClearPreExistingRequestsAtStartup(bool bEnable);` — Sets whether or not the background downloader's temporary files are to be wiped clean at startup. Can only be set before the first call to GetBackgroundHttpManager().
- L53 _public prototype_ `virtual void StartupModule() override;` — Called when Background Http module is loaded
- L58 _public prototype_ `virtual void ShutdownModule() override;` — Called when Background Http module is unloaded
- L62 _private member_ `FBackgroundHttpManagerPtr BackgroundHttpManager;` — Keeps track of Background Http requests while they are being processed.
- L65 _private member_ `static FBackgroundHttpModule* Singleton;` — Singleton for the module while loaded and available.
- L70 _private member_ `static bool bClearPreExistingRequestsAtStartup;` — Setting representing whether or not all pre-existing requests are to be removed at startup. False by default. Use ClearPreExistingRequestsAtStartup(bool) to change.

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttpNotificationObject.h` (Public)


#### class `FBackgroundHttpNotificationObject`  
`class FBackgroundHttpNotificationObject : public TSharedFromThis<FBackgroundHttpNotificationObject, ESPMode::ThreadSafe>`  
_L12-47_
- inherits: `TSharedFromThis<FBackgroundHttpNotificationObject,ESPMode::ThreadSafe>`
- L16 _public prototype_ `FBackgroundHttpNotificationObject(FText InNotificationTitle, FText InNotificationBody, FText InNotificationAction, const FString& InNotificationActivationString, bool InNotifyOnlyOnFullSuccess);`
- L17 _public prototype_ `FBackgroundHttpNotificationObject(FText InNotificationTitle, FText InNotificationBody, FText InNotificationAction, const FString& InNotificationActivationString, bool InNotifyOnlyOnFullSuccess, bool bOnlySendNotificationInBackground, int32 InIdOverride, bool bUnused = false);`
- L18 _public prototype_ `~FBackgroundHttpNotificationObject();`
- L20 _public prototype_ `void NotifyOfDownloadResult(bool bWasSuccess);`
- L23 _private prototype_ `void OnApp_EnteringBackground();`
- L24 _private prototype_ `void OnApp_EnteringForeground();`
- L27 _private member_ `FText NotificationTitle;`
- L28 _private member_ `FText NotificationAction;`
- L29 _private member_ `FText NotificationBody;`
- L30 _private member_ `FString NotificationActivationString;`
- L32 _private member_ `bool bOnlySendNotificationInBackground;`
- L33 _private member_ `bool bNotifyOnlyOnFullSuccess;`
- L35 _private member_ `volatile bool bIsInBackground;`
- L36 _private member_ `volatile int32 NumFailedDownloads;`
- L38 _private member_ `int32 IdOverride;`
- L40 _private member_ `class ILocalNotificationService* PlatformNotificationService;`
- L42 _private member_ `FDelegateHandle OnApp_EnteringForegroundHandle;`
- L43 _private member_ `FDelegateHandle OnApp_EnteringBackgroundHandle;`
- L46 _private function_ `FBackgroundHttpNotificationObject()` — No default constructor

#### Free symbols / members of external scopes

- L49 _typedef_ `typedef TSharedPtr<FBackgroundHttpNotificationObject, ESPMode::ThreadSafe> FBackgroundHttpNotificationObjectPtr;`

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttpRequestImpl.h` (Public)


#### enum `EBackgroundHttpRequestCompletionResult`  
`enum class EBackgroundHttpRequestCompletionResult`  
_L15-20_
- L17 _public enumerator_ `Success`
- L18 _public enumerator_ `GenericError`
- L19 _public enumerator_ `OutOfDiskSpaceError`

#### class `FBackgroundHttpRequestImpl`  
`class FBackgroundHttpRequestImpl : public IBackgroundHttpRequest`  
_L25-92_
- inherits: `IBackgroundHttpRequest`
- desc: Contains implementation of some common functions that don't have to vary between implementation
- L29 _public prototype_ `FBackgroundHttpRequestImpl();`
- L30 _public prototype_ `virtual ~FBackgroundHttpRequestImpl() = default;`
- L33 _public prototype_ `virtual void OnBackgroundDownloadComplete();` — This should be called from the platform level when a BG download finishes.
- L36 _public prototype_ `virtual bool ProcessRequest() override;` — IBackgroundHttpRequest
- L37 _public prototype_ `virtual void CancelRequest() override;`
- L38 _public prototype_ `virtual void RequeueRequest() override;`
- L39 _public prototype_ `virtual void PauseRequest() override;`
- L40 _public prototype_ `virtual void ResumeRequest() override;`
- L41 _public prototype_ `virtual void SetURLAsList(const TArray<FString>& URLs, int NumRetriesToAttempt) override;`
- L42 _public prototype_ `virtual const TArray<FString>& GetURLList() const override;`
- L43 _public prototype_ `virtual void SetExpectedResultSize(const uint64 ExpectedSize) override;`
- L44 _public prototype_ `virtual uint64 GetExpectedResultSize() const override;`
- L45 _public prototype_ `virtual void SetCompleteNotification(FBackgroundHttpNotificationObjectPtr DownloadCompleteNotificationObjectIn) override;`
- L46 _public prototype_ `virtual void CompleteWithExistingResponseData(FBackgroundHttpResponsePtr BackgroundResponse) override;`
- L47 _public prototype_ `virtual FBackgroundHttpRequestCompleteDelegate& OnProcessRequestComplete() override;`
- L48 _public prototype_ `virtual FBackgroundHttpProgressUpdateDelegate& OnProgressUpdated() override;`
- L50 _public prototype_ `virtual FBackgroundHttpRequestMetricsDelegate& OnRequestMetrics() override;` — `UE_DEPRECATED(5.7, "FBackgroundHttpRequestImpl::OnRequestMetrics is deprecated, please use OnRequestMetricsExtended instead.")`
- L51 _public prototype_ `virtual FBackgroundHttpRequestMetricsExtendedDelegate& OnRequestMetricsExtended() override;`
- L52 _public prototype_ `virtual const FBackgroundHttpResponsePtr GetResponse() const override;`
- L53 _public prototype_ `virtual const FString& GetRequestID() const override;`
- L54 _public prototype_ `virtual void SetRequestID(const FString& NewRequestID) override;`
- L55 _public prototype_ `virtual bool HandleDelayedProcess() override;`
- L56 _public prototype_ `virtual EBackgroundHTTPPriority GetRequestPriority() const override;`
- L57 _public prototype_ `virtual void SetRequestPriority(EBackgroundHTTPPriority NewPriority) override;`
- L58 _public function_ `virtual bool HasSeenOutOfDiskSpaceError() const override`
- L61 _public prototype_ `virtual void NotifyNotificationObjectOfComplete(const bool bWasSuccess);` — `UE_DEPRECATED(5.8, "FBackgroundHttpRequestImpl::NotifyNotificationObjectOfComplete(bool) is deprecated, please use NotifyNotificationObjectOfComplete(EBackgroundHttpRequestCompletionResult) instead.")`
- L62 _public prototype_ `virtual void NotifyNotificationObjectOfComplete(EBackgroundHttpRequestCompletionResult Result);`
- L65 _public prototype_ `virtual void NotifyRequestMetricsAvailable(const int32 TotalBytesDownloaded, const float DownloadDuration);` — `UE_DEPRECATED(5.7, "FBackgroundHttpRequestImpl::NotifyRequestMetricsAvailable is deprecated, please use NotifyRequestMetricsExtendedAvailable instead.")`
- L66 _public prototype_ `virtual void NotifyRequestMetricsExtendedAvailable(const FBackgroundHttpRequestMetricsExtended ExtendedMetrics);`
- L69 _public prototype_ `virtual void SetMetrics(const int32 TotalBytesDownloaded, const float DownloadDuration) override;` — `UE_DEPRECATED(5.7, "FBackgroundHttpRequestImpl::SetMetrics is deprecated, please use SetMetricsExtended instead.")`
- L70 _public prototype_ `virtual void SetMetricsExtended(const FBackgroundHttpRequestMetricsExtended ExtendedMetrics) override;`
- L73 _protected member_ `UE::FMutex DownloadCompleteMutex;`
- L74 _protected member_ `TSharedPtr<FBackgroundHttpNotificationObject, ESPMode::ThreadSafe> DownloadCompleteNotificationObject;`
- L75 _protected member_ `FBackgroundHttpResponsePtr Response;`
- L76 _protected member_ `TArray<FString> URLList;`
- L77 _protected member_ `FString RequestID;`
- L78 _protected member_ `int NumberOfTotalRetries;`
- L79 _protected member_ `EBackgroundHTTPPriority RequestPriority;`
- L80 _protected member_ `uint64 ExpectedResultSize;`
- L82 _protected member_ `bool bHasSeenOutOfDiskSpaceError = false;`
- L84 _protected typedef_ `using FDownloadMetricsInfo = FBackgroundHttpRequestMetricsExtended;`
- L86 _protected member_ `TOptional<FDownloadMetricsInfo> OptionalMetricsInfo;`
- L88 _protected member_ `FBackgroundHttpRequestCompleteDelegate HttpRequestCompleteDelegate;`
- L89 _protected member_ `FBackgroundHttpProgressUpdateDelegate HttpProgressUpdateDelegate;`
- L90 _protected member_ `FBackgroundHttpRequestMetricsDelegate HttpRequestMetricsDelegate;`
- L91 _protected member_ `FBackgroundHttpRequestMetricsExtendedDelegate HttpRequestMetricsExtendedDelegate;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackgroundHttpRequest, Log, All) enum class EBackgroundHttpRequestCompletionResult { Success, GenericError, OutOfDiskSpaceError, };`

### `Source/Runtime/Online/BackgroundHTTP/Public/BackgroundHttpResponseImpl.h` (Public)


#### class `FBackgroundHttpResponseImpl`  
`class FBackgroundHttpResponseImpl : public IBackgroundHttpResponse`  
_L12-27_
- inherits: `IBackgroundHttpResponse`
- desc: Contains implementation of some common functions that don't vary between implementation
- L16 _public prototype_ `FBackgroundHttpResponseImpl();`
- L17 _public prototype_ `FBackgroundHttpResponseImpl(FString InTempContentFilePath, int32 InResponseCode);`
- L18 _public prototype_ `virtual ~FBackgroundHttpResponseImpl() override = default;`
- L21 _public prototype_ `virtual int32 GetResponseCode() const override;` — IHttpBackgroundResponse
- L22 _public prototype_ `virtual const FString& GetTempContentFilePath() const override;`
- L25 _protected member_ `FString TempContentFilePath;`
- L26 _protected member_ `int32 ResponseCode;`

### `Source/Runtime/Online/BackgroundHTTP/Public/GenericPlatform/GenericPlatformBackgroundHttp.h` (Public)


#### class `FGenericPlatformBackgroundHttp`  
`class FGenericPlatformBackgroundHttp`  
_L18-52_
- desc: Generic version of Background Http implementations for platforms that don't need a special implementation Intended usage is to use FPlatformBackgroundHttp instead of FGenericPlatformHttp On platforms without a specific implementation, you should still use FPlatformBackgroundHttp and it will call into these functions
- L24 _public prototype_ `static void Initialize();` — Platform initialization step
- L29 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L35 _public prototype_ `static FBackgroundHttpManagerPtr CreatePlatformBackgroundHttpManager();` — Creates a platform-specific Background HTTP manager. Un-implemented platforms should create a FGenericPlatformBackgroundHttpManager
- L43 _public prototype_ `static FBackgroundHttpRequestPtr ConstructBackgroundRequest();` — Creates a new Background Http request instance for the current platform that will continue to download when the application is in the background @return request object
- L51 _public prototype_ `static FBackgroundHttpResponsePtr ConstructBackgroundResponse(int32 ResponseCode, const FString& TempFilePath);` — Creates a new Background Http Response instance for the current platform This normally is called by the request and associated with itself. @return response object

### `Source/Runtime/Online/BackgroundHTTP/Public/GenericPlatform/GenericPlatformBackgroundHttpManager.h` (Public)


#### class `FGenericPlatformBackgroundHttpManager`  
`class FGenericPlatformBackgroundHttpManager : public FBackgroundHttpManagerImpl`  
_L13-19_
- inherits: `FBackgroundHttpManagerImpl`
- desc: Manages Background Http request that are currently being processed if no platform specific implementation has been made.
- L17 _public function_ `virtual bool IsGenericImplementation() const override`
- L18 _public prototype_ `virtual ~FGenericPlatformBackgroundHttpManager();`

### `Source/Runtime/Online/BackgroundHTTP/Public/GenericPlatform/GenericPlatformBackgroundHttpRequest.h` (Public)


#### class `FGenericPlatformBackgroundHttpRequest`  
`class FGenericPlatformBackgroundHttpRequest : public FBackgroundHttpRequestImpl`  
_L17-74_
- inherits: `FBackgroundHttpRequestImpl`
- desc: Contains implementation of some common functions that don't vary between implementation
- L22 _public prototype_ `FGenericPlatformBackgroundHttpRequest();`
- L23 _public prototype_ `virtual ~FGenericPlatformBackgroundHttpRequest();`
- L26 _public prototype_ `virtual bool HandleDelayedProcess() override;` — IHttpBackgroundHttpRequest
- L27 _public prototype_ `virtual void CompleteWithExistingResponseData(FBackgroundHttpResponsePtr BackgroundResponse) override;`
- L28 _public prototype_ `virtual void CancelRequest() override;`
- L73 _protected member_ `TUniquePtr<FGenericPlatformBackgroundHttpWrapper> RequestWrapper;`

#### class `FGenericPlatformBackgroundHttpRequest::FGenericPlatformBackgroundHttpWrapper`  
`class FGenericPlatformBackgroundHttpWrapper`  
_L34-71_
- desc: In the default implementation we actually use HTTPRequests instead of HttpBackgroundRequests. This class handles wrapping some of the HttpBackgroundRequest only functionality (such as request lists and notification objects) so they work with non-background HttpRequests
- L37 _public prototype_ `FGenericPlatformBackgroundHttpWrapper(FBackgroundHttpRequestPtr Request, int MaxRetriesToAttempt);`
- L38 _public prototype_ `~FGenericPlatformBackgroundHttpWrapper();`
- L40 _public prototype_ `void MakeRequest();`
- L41 _public prototype_ `void HttpRequestComplete(FHttpRequestPtr HttpRequestIn, FHttpResponsePtr HttpResponse, bool bSuccess);`
- L45 _private prototype_ `bool HasRetriesRemaining() const;`
- L46 _private prototype_ `void UpdateHttpProgress(FHttpRequestPtr UnderlyingHttpRequest, uint64 BytesSent, uint64 BytesReceived);`
- L48 _private prototype_ `void CleanUpHttpRequest();`
- L52 _private prototype_ `const FString GetURLForCurrentRetryNumber();` — Gets the current URL the HTTP Request should use by comparing the URLList in the background request to the current retry number. Returns empty FString if we are "out of" retries (CurrentRetryNumber > MaxRetries) or if no valid URL.
- L55 _private function_ `FGenericPlatformBackgroundHttpWrapper()` — Don't want to provide default implementation. Must provide an IHttpBackgroundRequest to wrap in public constructor
- L58 _private member_ `TWeakPtr<class IBackgroundHttpRequest, ESPMode::ThreadSafe> OriginalRequest;` — Reference to the creating request
- L61 _private member_ `TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;` — Current Http Request being processed by this wrapper
- L64 _private member_ `int32 CurrentRetryNumber;` — Tracking retry number we are currently on
- L67 _private member_ `int32 MaxRetries;` — Max number of retries we should do
- L70 _private member_ `uint64 LastProgressUpdateBytes;` — How many bytes we had last time we sent progress updates

### `Source/Runtime/Online/BackgroundHTTP/Public/GenericPlatform/GenericPlatformBackgroundHttpResponse.h` (Public)


#### class `FGenericPlatformBackgroundHttpResponse`  
`class FGenericPlatformBackgroundHttpResponse : public FBackgroundHttpResponseImpl`  
_L13-22_
- inherits: `FBackgroundHttpResponseImpl`
- desc: Contains implementation of some common functions that don't vary between implementation
- L18 _public prototype_ `FGenericPlatformBackgroundHttpResponse(int32 ResponseCode, const FString& TempContentFilePath);` — Provide constructor to create an already
- L21 _public prototype_ `FGenericPlatformBackgroundHttpResponse(FHttpRequestPtr HttpRequestIn, FHttpResponsePtr HttpResponse, bool bSuccess);` — Provide constuctor to create a request from underlying HttpRequest information

### `Source/Runtime/Online/BackgroundHTTP/Public/IOS/ApplePlatformBackgroundHttp.h` (Public)


#### class `FApplePlatformBackgroundHttp`  
`class FApplePlatformBackgroundHttp`  
_L16-50_
- desc: Apple specific Background Http implementations Intended usage is to use FPlatformBackgroundHttp
- L22 _public prototype_ `static void Initialize();` — Platform initialization step
- L27 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L33 _public prototype_ `static FBackgroundHttpManagerPtr CreatePlatformBackgroundHttpManager();` — Creates a platform-specific Background HTTP manager. Un-implemented platforms should create a FGenericPlatformBackgroundHttpManager
- L41 _public prototype_ `static FBackgroundHttpRequestPtr ConstructBackgroundRequest();` — Creates a new Background Http request instance for the current platform that will continue to download when the application is in the background @return request object
- L49 _public prototype_ `static FBackgroundHttpResponsePtr ConstructBackgroundResponse(int32 ResponseCode, const FString& TempFilePath);` — Creates a new Background Http Response instance for the current platform This normally is called by the request and associated with itself. @return response object

#### Free symbols / members of external scopes

- L53 _typedef_ `typedef FApplePlatformBackgroundHttp FPlatformBackgroundHttp;` — Setup Platform Implementation calls to point here at the Apple Implementation

### `Source/Runtime/Online/BackgroundHTTP/Public/IOS/ApplePlatformBackgroundHttpManager.h` (Public)


#### class `FApplePlatformBackgroundHttpManager`  
`class FApplePlatformBackgroundHttpManager : public FBackgroundHttpManagerImpl`  
_L18-42_
- inherits: `FBackgroundHttpManagerImpl`
- desc: Manages Background Http request that are currently being processed if we are on an Apple Platform
- L22 _public prototype_ `FApplePlatformBackgroundHttpManager();`
- L23 _public prototype_ `virtual ~FApplePlatformBackgroundHttpManager();`
- L25 _public prototype_ `virtual void Initialize(bool bClearPreExistingRequestsAtStartup) override;`
- L26 _public prototype_ `virtual void AddRequest(const FBackgroundHttpRequestPtr Request) override;`
- L27 _public prototype_ `virtual void RemoveRequest(const FBackgroundHttpRequestPtr Request) override;`
- L28 _public prototype_ `virtual void RequeueRequest(const FBackgroundHttpRequestPtr Request) override;`
- L29 _public prototype_ `virtual void GetActiveDownloadRequestIDs(TSet<FString>& OutActiveIDs) const override;`
- L30 _public prototype_ `virtual void SetCellularPreference(int32 Value) override;`
- L31 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) override;`
- L32 _public function_ `virtual bool IsGenericImplementation() const override`
- L33 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L36 _private member_ `TArray<FBackgroundHttpRequestPtr> PendingRemoveRequests;`
- L37 _private member_ `FRWLock PendingRemoveRequestLock;`
- L38 _private member_ `FDelegateHandle OnDownloadCompletedHandle;`
- L39 _private member_ `FDelegateHandle OnDownloadMetricsExtendedHandle;`
- L40 _private prototype_ `void OnDownloadCompletedExtended(const uint64 DownloadId, EBackgroundHttpRequestCompletionResult Result);`
- L41 _private prototype_ `void OnDownloadMetricsExtended(const uint64 DownloadId, const FBackgroundHttpRequestMetricsExtended MetricsExtended);`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TWeakPtr<FApplePlatformBackgroundHttpRequest,ESPMode::ThreadSafe> FBackgroundHttpURLMappedRequestPtr;`
- L13 _delegate_ `DECLARE_DELEGATE(FIOSBackgroundHttpPostSessionWorkCallback);`
- L13 _prototype_ `DECLARE_DELEGATE(FIOSBackgroundHttpPostSessionWorkCallback);`

### `Source/Runtime/Online/BackgroundHTTP/Public/IOS/ApplePlatformBackgroundHttpRequest.h` (Public)


#### class `FApplePlatformBackgroundHttpRequest`  
`class FApplePlatformBackgroundHttpRequest : public FBackgroundHttpRequestImpl`  
_L11-46_
- inherits: `FBackgroundHttpRequestImpl`
- desc: Contains implementation of Apple specific background http requests
- L15 _public prototype_ `FApplePlatformBackgroundHttpRequest();`
- L16 _public prototype_ `virtual ~FApplePlatformBackgroundHttpRequest() = default;`
- L18 _public prototype_ `virtual void PauseRequest() override;`
- L19 _public prototype_ `virtual void ResumeRequest() override;`
- L22 _public prototype_ `virtual void GetDebugText(TArray<FString>& Output) override;`
- L26 _protected function_ `void SetInternalDownloadId(uint64 Id)`
- L27 _protected function_ `uint64 GetInternalDownloadId() const`
- L29 _protected prototype_ `void UpdateProgress();`
- L30 _protected prototype_ `void ResetProgressTracking();`
- L31 _protected prototype_ `void RotateURLList();`
- L33 _protected prototype_ `static float BackgroundRequestPriorityToNSURLSessionPriority(const EBackgroundHTTPPriority Priority);`
- L34 _protected function_ `float GetNSURLSessionPriority() const`
- L41 _private member_ `uint64 DownloadId;`
- L43 _private member_ `uint64 LastReportedDownloadedBytes = 0;`
- L45 _private member_ `int MetricsWaitCounter = -1;`

#### Free symbols / members of external scopes

- L48 _typedef_ `typedef TSharedPtr<class FApplePlatformBackgroundHttpRequest, ESPMode::ThreadSafe> FAppleBackgroundHttpRequestPtr;`

### `Source/Runtime/Online/BackgroundHTTP/Public/IOS/ApplePlatformBackgroundHttpResponse.h` (Public)


#### class `FApplePlatformBackgroundHttpResponse`  
`class FApplePlatformBackgroundHttpResponse : public FBackgroundHttpResponseImpl`  
_L11-17_
- inherits: `FBackgroundHttpResponseImpl`
- desc: Contains implementation of some common functions that don't vary between implementation
- L16 _public prototype_ `FApplePlatformBackgroundHttpResponse(int32 ResponseCode, const FString& TempContentFilePath);` — Provide constructor to create an already

### `Source/Runtime/Online/BackgroundHTTP/Public/IOS/IOSPlatformBackgroundHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/BackgroundHTTP/Public/Interfaces/IBackgroundHttpManager.h` (Public)


#### class `IBackgroundHttpManager`  
`class IBackgroundHttpManager : public TSharedFromThis<IBackgroundHttpManager>`  
_L9-118_
- inherits: `TSharedFromThis<IBackgroundHttpManager>`
- L13 _public prototype_ `virtual ~IBackgroundHttpManager() = default;`
- L18 _public prototype_ `virtual void Initialize(bool bClearPreExistingRequestsAtStartup) = 0;` — Initialize
- L23 _public prototype_ `virtual void Shutdown() = 0;` — Shutdown
- L31 _public prototype_ `virtual void AddRequest(const FBackgroundHttpRequestPtr Request) = 0;` — Adds a Background Http request instance to the manager for tracking Manager should always have a list of requests currently being processed @param Request - the request object to add
- L39 _public prototype_ `virtual void RemoveRequest(const FBackgroundHttpRequestPtr Request) = 0;` — Removes a Background Http request instance from the manager Presumably it is done being processed @param Request - the request object to remove
- L48 _public function_ `virtual void RequeueRequest(const FBackgroundHttpRequestPtr Request)` — Re-queues an active request by canceling the current platform download and creating a fresh one. Unlike CancelRequest+ProcessRequest, this is safe on all platforms as it avoids deferred removal races. The URL list is rotated so the retry hits a different CDN. @param Request - the request object to re-queue
- L57 _public prototype_ `virtual void DeleteAllTemporaryFiles() = 0;` — Function to remove all temporary files used by the system to store completed downloads. This should be called when there are no active background downloads that we care about to regain disk space from background downloads that may no longer be relevant (IE: downloads that were never moved after completion) but are still on disk.
- L60 _public prototype_ `virtual bool IsGenericImplementation() const = 0;` — Returns whether or not this is a platform specific implementation
- L67 _public prototype_ `virtual int GetMaxActiveDownloads() const = 0;` — Function that returns how many active BackgroundHttpRequests we should have actively downloading at once. @return int Number of downloads we should have active at once.
- L74 _public prototype_ `virtual void SetMaxActiveDownloads(int MaxActiveDownloads) = 0;` — Function that sets how many active BackgroundHttpRequests we should have actively downloading at once. @param MaxActiveDownloads the maximum number of downloads that should be active at once
- L80 _public prototype_ `virtual FString GetTempFileLocationForURL(const FString& URL, const FString& RequestID) = 0;` — Function that returns an FString fullpath where we would expect the given URL's temp part of the given RequestID to be located
- L82 _public function_ `FString GetTempFileLocationForURL(const FString& URL)` — `UE_DEPRECATED(5.8, "Please use GetTempFileLocationForURL with added RequestID argument instead")`
- L88 _public prototype_ `virtual void CleanUpDataAfterCompletingRequest(const FBackgroundHttpRequestPtr Request) = 0;` — Function that cleans up any persistent data after we have completed a reqeust. Should really never be calling this outside of a BackgroundHTTP class
- L93 _public prototype_ `virtual void SetCellularPreference(int32 Value) = 0;` — Setting cellular network preference
- L98 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) = 0;` — Setting limited data network preference
- L105 _public function_ `virtual void GetActiveDownloadRequestIDs(TSet<FString>& OutActiveIDs) const` — Returns the set of RequestIDs that are actively being downloaded by the platform. Requests queued by the platform (waiting for a concurrency slot) are excluded. Default implementation returns empty set (treats no requests as confirmed active).
- L117 _protected prototype_ `virtual bool AssociateWithAnyExistingRequest(const FBackgroundHttpRequestPtr Request) = 0;` — Designed to be called internally by AddRequest to associate our incoming request with any previously completed background downloads (might have completed before this app launch, or carried over from a previous application launch and be running without any other information. @param Request - The request to check for any existing request matches on. @return bool - true if we found an existing request and associated with it. false otherwise.

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef TSharedPtr<class IBackgroundHttpManager, ESPMode::ThreadSafe> FBackgroundHttpManagerPtr;`

### `Source/Runtime/Online/BackgroundHTTP/Public/Interfaces/IBackgroundHttpModularFeature.h` (Public)


#### class `IBackgroundHttpModularFeature`  
`class IBackgroundHttpModularFeature : public IModularFeature`  
_L22-34_
- inherits: `IModularFeature`
- desc: This version of BackgroundHttp is designed to be used by any platform that relies on a ModularFeature to override the BackgroundHttp behavior. If no modular feature is found, we fall back on the GenericPlatform implementation to provide functionality
- L26 _public prototype_ `virtual void Initialize() = 0;` — Virtual methods for all PlatformBackgroundHttp required functions
- L27 _public prototype_ `virtual void Shutdown() = 0;`
- L28 _public prototype_ `virtual FBackgroundHttpManagerPtr CreatePlatformBackgroundHttpManager() = 0;`
- L29 _public prototype_ `virtual FBackgroundHttpRequestPtr ConstructBackgroundRequest() = 0;`
- L30 _public prototype_ `virtual FBackgroundHttpResponsePtr ConstructBackgroundResponse(int32 ResponseCode, const FString& TempFilePath) = 0;`
- L33 _public prototype_ `virtual FString GetDebugModuleName() const = 0;` — Should return the name of the Plugin/Module that causes this ModularFeature to be registered.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackgroundHttpModularFeature, Log, All) class IBackgroundHttpModularFeature : public IModularFeature { public:`

### `Source/Runtime/Online/BackgroundHTTP/Public/Interfaces/IBackgroundHttpRequest.h` (Public)


#### enum `EBackgroundHTTPPriority`  
`enum class EBackgroundHTTPPriority : uint8`  
_L56-62_
- desc: Enum used to describe download priority. Higher priorities will be downloaded first. Note: Should always be kept in High -> Low priority order if adding more Priorities!
- L58 _public enumerator_ `High`
- L59 _public enumerator_ ``
- L60 _public enumerator_ ``
- L61 _public enumerator_ ``

#### class `IBackgroundHttpRequest`  
`class IBackgroundHttpRequest : public TSharedFromThis<IBackgroundHttpRequest, ESPMode::ThreadSafe>`  
_L106-291_
- inherits: `TSharedFromThis<IBackgroundHttpRequest,ESPMode::ThreadSafe>`
- desc: Interface for Http requests (created using FHttpFactory)
- L118 _public prototype_ `virtual void SetURLAsList(const TArray<FString>& URLs, int NumRetriesToAttempt) = 0;` — Sets up a list of URLs to automatically fall through as each one fails. Must be called before ProcessRequest. @param URLs list of URLs. Eg: download.epicgames.com/downloadfilehere.txt, download2.epicgames.com/downloadfilehere.txt, download3.epicgames/downloadfilehere.txt @param NumRetriesToAttempt How many times we want to fall through and try different URLS. Loops back to the beginning of the list if NumRetries > URLs.Num()
- L126 _public prototype_ `virtual const TArray<FString>& GetURLList() const = 0;` — Gets the current URL List that this background request is currently processing. @return List of URLs as FStrings
- L136 _public function_ `virtual void SetExpectedResultSize(const uint64 ExpectedSize)` — Sets expected result size for the request, might be used by the implementation to check file size before invoking completion notification. Must be called before ProcessRequest. @param ExpectedSize expected file size in bytes, 0 to disable the check. Default value is 0.
- L144 _public function_ `virtual uint64 GetExpectedResultSize() const` — Returns expected result size for the request, set by SetExpectedResultSize. @return Expected result size in bytes.
- L156 _public prototype_ `virtual void SetCompleteNotification(FBackgroundHttpNotificationObjectPtr DownloadCompleteNotificationObject) = 0;` — Sets an FHTTPRequestDownloadNotificationObject to be mapped to this HTTPRequest. This request will keep the particular FHttpRequestDownloadNotificationObject reference until it completes. To use this function make sure you keep a reference to the supplied DownloadNotificationObject until you have created all the different IHTTPRequest that you would like to use it. Then delete your reference. Once all references are removed (by each Request completing) a callback set on the DownloadCompleteDelegateObject will be called @param DownloadCompleteDelegateObject The particular download complete delegate object
- L163 _public prototype_ `virtual void CompleteWithExistingResponseData(FBackgroundHttpResponsePtr BackgroundResponse) = 0;` — Function used to complete an IHttpBackgroundRequest from an external source, passing it in a pre-existing response data. @param BackgroundReponse, A SharedRef to the already existing IHttpBackgroundResponse we want to base this tasks' Response off of.
- L168 _public prototype_ `virtual FBackgroundHttpRequestCompleteDelegate& OnProcessRequestComplete() = 0;` — Delegate called when the request is complete. See FBackgroundHttpRequestCompleteDelegate
- L173 _public prototype_ `virtual FBackgroundHttpProgressUpdateDelegate& OnProgressUpdated() = 0;` — Delegate called when the request has a progress update.
- L179 _public prototype_ `virtual FBackgroundHttpRequestMetricsDelegate& OnRequestMetrics() = 0;` — `UE_DEPRECATED(5.7, "IBackgroundHttpRequest::OnRequestMetrics is deprecated, please use IBackgroundHttpRequest::OnRequestMetricsExtended instead.")` — Delegate called when the request's metrics were calculated
- L184 _public prototype_ `virtual FBackgroundHttpRequestMetricsExtendedDelegate& OnRequestMetricsExtended() = 0;` — Delegate called when the request's extended metrics were calculated
- L191 _public function_ `virtual void SetMetrics(const int32 TotalBytesDownloaded, const float DownloadDuration)` — `UE_DEPRECATED(5.7, "IBackgroundHttpRequest::SetMetrics is deprecated, please use IBackgroundHttpRequest::SetMetricsExtended instead.")` — Set metrics for analytics event
- L196 _public function_ `virtual void SetMetricsExtended(const FBackgroundHttpRequestMetricsExtended ExtendedMetrics)` — Set extended metrics for analytics event
- L206 _public prototype_ `virtual bool ProcessRequest() = 0;` — Called to begin processing the request. OnProcessRequestComplete delegate is always called when the request completes or on error if it is bound. A request can be re-used but not while still being processed. @return if the request was successfully started.
- L216 _public prototype_ `virtual bool HandleDelayedProcess() = 0;` — Called by certain platform's implementation when we have to wait for the BackgroundHttpManager / PlatformBackgroundHttp to do some work before we can finish our ProcessRequest call. Should only be called by different platform layers. NOTE: Should really only be called by the BackgroundHttpManager! You are probably looking for ProcessRequest. @return if the request was successfully handled.
- L221 _public prototype_ `virtual void CancelRequest() = 0;` — Called to cancel a request that is still being processed
- L227 _public function_ `virtual void RequeueRequest()` — Re-queues a request by canceling the current platform download and creating a fresh one. Rotates the URL list so the retry hits a different CDN. Safe to call on active requests.
- L232 _public prototype_ `virtual void PauseRequest() = 0;` — Called to pause a request that is still being processed
- L237 _public prototype_ `virtual void ResumeRequest() = 0;` — Called to resume a request that was previously paused
- L244 _public prototype_ `virtual const FBackgroundHttpResponsePtr GetResponse() const = 0;` — Get the associated Response @return the response
- L251 _public prototype_ `virtual const FString& GetRequestID() const = 0;` — Gets the associated RequestID for this BackgroundDownload. @return The RequestID
- L259 _public prototype_ `virtual void SetRequestID(const FString& NewRequestID) = 0;` — Sets the associated RequestID for this BackgroundDownload. Useful as we associate a background downlaod with multiple URLs, so this provides an easier way to identify the download with 1 string instead of checking multiple URLs. @param NewRequestID FString to set the Request ID to.
- L266 _public prototype_ `virtual EBackgroundHTTPPriority GetRequestPriority() const = 0;` — Gets the associated Requeset's Priority for Background Downloadings. Where possible, we attempt to finish downloads in lowest-priority first order. @return The request Priority
- L273 _public prototype_ `virtual void SetRequestPriority(EBackgroundHTTPPriority NewPriority) = 0;` — Sets the associated Requeset's Priority for Background Downloadings. Where possible, we attempt to finish downloads in lowest-priority first order. @param uint32 describing priority of this download. Lower happens first and thus 0 is the highest priority.
- L278 _public prototype_ `virtual ~IBackgroundHttpRequest() = default;` — Destructor for overrides
- L283 _public function_ `virtual bool HasSeenOutOfDiskSpaceError() const` — Returns whether or not this request has seen an out of disk space error at least once.
- L289 _public function_ `virtual void GetDebugText(TArray<FString>& Output)` — Returns debug text for download screen to help troubleshoot download issues

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedPtr<class IBackgroundHttpRequest, ESPMode::ThreadSafe> FBackgroundHttpRequestPtr;`
- L15 _typedef_ `typedef TSharedPtr<class IBackgroundHttpResponse, ESPMode::ThreadSafe> FBackgroundHttpResponsePtr;`
- L16 _typedef_ `typedef TSharedPtr<class IBackgroundHttpManager, ESPMode::ThreadSafe> FBackgroundHttpManagerPtr;`
- L26 _delegate_ `DECLARE_DELEGATE_TwoParams(FBackgroundHttpRequestCompleteDelegate, FBackgroundHttpRequestPtr , bool );` — Delegate called when a Background Http request completes @param Request original Background Http request that started things @param Response response received from the server if a successful connection was established
- L26 _prototype_ `DECLARE_DELEGATE_TwoParams(FBackgroundHttpRequestCompleteDelegate, FBackgroundHttpRequestPtr , bool );` — Delegate called when a Background Http request completes @param Request original Background Http request that started things @param Response response received from the server if a successful connection was established
- L35 _delegate_ `DECLARE_DELEGATE_ThreeParams(FBackgroundHttpProgressUpdateDelegate, FBackgroundHttpRequestPtr , int32 , int32 );` — Delegate Called when a Background Http request updates its progress @param Request Background Http Request that is updating its progress @param TotalBytesWritten Amount of data we have written so far. Total Figure. @param BytesWrittenSinceLastUpdate Amount of data we have written since our last call to this delegate.
- L35 _prototype_ `DECLARE_DELEGATE_ThreeParams(FBackgroundHttpProgressUpdateDelegate, FBackgroundHttpRequestPtr , int32 , int32 );` — Delegate Called when a Background Http request updates its progress @param Request Background Http Request that is updating its progress @param TotalBytesWritten Amount of data we have written so far. Total Figure. @param BytesWrittenSinceLastUpdate Amount of data we have written since our last call to this delegate.
- L43 _delegate_ `DECLARE_DELEGATE_ThreeParams(FBackgroundHttpRequestMetricsDelegate, FBackgroundHttpRequestPtr , int32 , float );` — Delegate called when a Background Http request metrics are ready @param Request Background Http Request for which the metrics were calculated @param TotalBytesDownloaded The count of bytes downloaded in this request @param DownloadDuration The duration of the download in seconds
- L43 _prototype_ `DECLARE_DELEGATE_ThreeParams(FBackgroundHttpRequestMetricsDelegate, FBackgroundHttpRequestPtr , int32 , float );` — Delegate called when a Background Http request metrics are ready @param Request Background Http Request for which the metrics were calculated @param TotalBytesDownloaded The count of bytes downloaded in this request @param DownloadDuration The duration of the download in seconds
- L50 _delegate_ `DECLARE_DELEGATE_TwoParams(FBackgroundHttpRequestMetricsExtendedDelegate, FBackgroundHttpRequestPtr , FBackgroundHttpRequestMetricsExtended );` — Delegate called when a Background Http request extended metrics are ready @param Request Background Http Request for which the metrics were calculated @param BackgroundHttpRequestMetricsExtended struct containing all the metrics
- L50 _prototype_ `DECLARE_DELEGATE_TwoParams(FBackgroundHttpRequestMetricsExtendedDelegate, FBackgroundHttpRequestPtr , FBackgroundHttpRequestMetricsExtended );` — Delegate called when a Background Http request extended metrics are ready @param Request Background Http Request for which the metrics were calculated @param BackgroundHttpRequestMetricsExtended struct containing all the metrics
- L64 _function_ `inline const TCHAR* LexToString(EBackgroundHTTPPriority InType)`
- L83 _function_ `inline bool LexTryParseString(EBackgroundHTTPPriority& OutMode, const TCHAR* InBuffer)`

### `Source/Runtime/Online/BackgroundHTTP/Public/Interfaces/IBackgroundHttpResponse.h` (Public)


#### class `IBackgroundHttpResponse`  
`class IBackgroundHttpResponse`  
_L10-33_
- desc: Interface for Http Background Responses
- L19 _public prototype_ `virtual int32 GetResponseCode() const = 0;` — Gets the response code returned by the requested server. See EHttpResponseCodes for known response codes. Same as HttpRequest (non-background) @return the response code.
- L27 _public prototype_ `virtual const FString& GetTempContentFilePath() const = 0;` — Gets the file name that our temporary content file will be stored in. HttpBackgroundRequests Download their files to a temp location and this can be used to get at the temporary file on disk and move it to your desired location. @return FString representing the FilePath to the temporary file.
- L32 _public prototype_ `virtual ~IBackgroundHttpResponse() = default;` — Destructor for overrides

### `Source/Runtime/Online/BackgroundHTTP/Public/Linux/LinuxPlatformBackgroundHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/BackgroundHTTP/Public/Mac/MacPlatformBackgroundHttp.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FGenericPlatformBackgroundHttp FPlatformBackgroundHttp;` — Currently no implementation on Mac

### `Source/Runtime/Online/BackgroundHTTP/Public/PlatformBackgroundHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/BackgroundHTTP/Public/PlatformWithModularFeature/ModularFeaturePlatformBackgroundHttp.h` (Public)


#### class `FModularFeaturePlatformBackgroundHttp`  
`class FModularFeaturePlatformBackgroundHttp`  
_L20-64_
- desc: This version of BackgroundHttp is designed to be used by any platform that relies on a ModularFeature to override the BackgroundHttp behavior. If no modular feature is found, we fall back on the GenericPlatform implementation to provide functionality
- L26 _public prototype_ `static void Initialize();` — Platform initialization step
- L31 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L37 _public prototype_ `static FBackgroundHttpManagerPtr CreatePlatformBackgroundHttpManager();` — Creates a platform-specific Background HTTP manager. Un-implemented platforms should create a FGenericPlatformBackgroundHttpManager
- L45 _public prototype_ `static FBackgroundHttpRequestPtr ConstructBackgroundRequest();` — Creates a new Background Http request instance for the current platform that will continue to download when the application is in the background @return request object
- L53 _public prototype_ `static FBackgroundHttpResponsePtr ConstructBackgroundResponse(int32 ResponseCode, const FString& TempFilePath);` — Creates a new Background Http Response instance for the current platform This normally is called by the request and associated with itself. @return response object
- L56 _public prototype_ `static FName GetModularFeatureName();`
- L59 _protected prototype_ `static void CacheModularFeature();`
- L62 _private member_ `static IBackgroundHttpModularFeature* CachedModularFeature;`
- L63 _private member_ `static bool bHasCheckedForModularFeature;`

### `Source/Runtime/Online/BackgroundHTTP/Public/Unix/UnixPlatformBackgroundHttp.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FGenericPlatformBackgroundHttp FPlatformBackgroundHttp;` — Currently no implementation on Unix

### `Source/Runtime/Online/BackgroundHTTP/Public/Windows/WindowsPlatformBackgroundHttp.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FGenericPlatformBackgroundHttp FPlatformBackgroundHttp;` — Currently no implementation on Windows
