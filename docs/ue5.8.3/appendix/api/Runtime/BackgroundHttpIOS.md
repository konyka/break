# Runtime / BackgroundHttpIOS

- module root: `Source/Runtime/Apple/BackgroundHttpIOS`
- headers: 1; symbols: 36
- symbol kinds: class=1, delegate=5, function=1, member=6, prototype=23
- PrivateDependencyModuleNames: BuildSettings
- PublicDependencyModuleNames: BackgroundHTTPFileHash, Core
- PublicIncludePathModuleNames: BackgroundHTTP

### `Source/Runtime/Apple/BackgroundHttpIOS/Public/BackgroundURLSessionHandler.h` (Public)


#### class `FBackgroundURLSessionHandler`  
`class FBackgroundURLSessionHandler`  
_L20-117_
- desc: Interface for wrapping a NSURLSession configured to support background downloading of NSURLSessionDownloadTasks. This exists here as we can have to re-associate with our background session after app launch and need to re-associate with downloads right away before the HttpModule is loaded.
- L27 _public member_ `static const uint64 InvalidDownloadId;` — Value of invalid download id which could be used to compare return value of CreateOrFindDownload.
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadCompleted, const uint64 , const bool );` — `UE_DEPRECATED(5.8, "FBackgroundURLSessionHandler::FOnDownloadCompleted is deprecated. Use FOnDownloadCompletedExtended")` — Will be invoked from didFinishDownloadingToURL or didCompleteWithError.
- L33 _public member_ `static FOnDownloadCompleted OnDownloadCompleted;` — `UE_DEPRECATED(5.8, "FBackgroundURLSessionHandler::FOnDownloadCompleted is deprecated. Use FOnDownloadCompletedExtended")`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadCompletedExtended, const uint64 , EBackgroundHttpRequestCompletionResult );`
- L35 _public member_ `static FOnDownloadCompletedExtended OnDownloadCompletedExtended;`
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDownloadMetrics, const uint64 , const int32 , const float ) UE_DEPRECATED(5.7, "FBackgroundURLSessionHandler::OnDownloadMetrics is deprecated. Use OnDownloadMetricsExtended") static FOnDownloadMetrics OnDownloadMetrics;` — `UE_DEPRECATED(5.7, "FBackgroundURLSessionHandler::FOnDownloadMetrics is deprecated. Use FOnDownloadMetricsExtended")` — Will be invoked from didFinishCollectingMetrics
- L44 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadMetricsExtended, const uint64 , const FBackgroundHttpRequestMetricsExtended );` — Will be invoked from didFinishCollectingMetrics
- L45 _public member_ `static FOnDownloadMetricsExtended OnDownloadMetricsExtended;`
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDownloadsCompletedWhileAppWasNotRunning, const bool );` — Will be invoked from handleEventsForBackgroundURLSession application delegate. Needs to be registered very early, e.g. from static constructor. handleEventsForBackgroundURLSession is only invoked if app was killed by OS while in background and then relaunched to notify that downloads were completed. Is not invoked in any other scenario.
- L51 _public member_ `static FOnDownloadsCompletedWhileAppWasNotRunning OnDownloadsCompletedWhileAppWasNotRunning;`
- L54 _public member_ `static NSMutableDictionary<NSString*,void(^)()>* BackgroundSessionEventCompleteDelegateMap;` — Will be used by IOSAppDelegate and ApplePlatformHttp
- L58 _public prototype_ `static void AllowCellular(bool bAllow);` — Sets if cellular network is allowed to be used for new downloads. Existing downloads will be recreated to reflect new setting value.
- L62 _public prototype_ `static void AllowConstrained(bool bAllow);` — Sets if constrained network is allowed to be used for new downloads. Existing downloads will be recreated to reflect new setting value.
- L69 _public prototype_ `static uint64 CreateOrFindDownload(const TArray<FString>& URLs, const float Priority, BackgroundHttpFileHashHelperRef HelperRef, const uint64 ExpectedResultSize, const FString& RequestID);` — Creates a new download or finds existing download matching URL path. All URL's should have same path and only differ in domain. Priority is a value between 0.0 to 1.0, see NSURLSessionTaskPriorityDefault. HelperRef is optional shared reference to BackgroundHttpFileHashHelperRef. In case of HandleEventsForBackgroundURLSession this subsystem will create it's own reference.
- L71 _public function_ `static uint64 CreateOrFindDownload(const TArray<FString>& URLs, const float Priority, BackgroundHttpFileHashHelperRef HelperRef, const uint64 ExpectedResultSize = 0)` — `UE_DEPRECATED(5.8, "FBackgroundURLSessionHandler::CreateOrFindDownload without RequestID is deprecated.")`
- L73 _public prototype_ `static void PauseDownload(const uint64 DownloadId);`
- L75 _public prototype_ `static void ResumeDownload(const uint64 DownloadId);`
- L78 _public prototype_ `static void CancelDownload(const uint64 DownloadId);` — Cancels and invalidates DownloadId.
- L81 _public prototype_ `static void SetPriority(const uint64 DownloadId, const float Priority);` — Priority is a value between 0.0 to 1.0, see NSURLSessionTaskPriorityDefault.
- L83 _public prototype_ `static uint64 GetCurrentDownloadedBytes(const uint64 DownloadId);`
- L86 _public prototype_ `static void GetActiveDownloadIDs(TSet<uint64>& OutActiveIDs);` — Returns download IDs of tasks currently in NSURLSessionTaskStateRunning state
- L88 _public prototype_ `static bool IsDownloadFinished(const uint64 DownloadId, int32& OutResultHTTPCode, FString& OutTemporaryFilePath);`
- L91 _public prototype_ `static void HandleEventsForBackgroundURLSession(const FString& SessionIdentifier);` — To be used by app delegate, call it from handleEventsForBackgroundURLSession.
- L94 _public prototype_ `static void HandleDidEnterBackground();` — To be used by app delegate, call it from applicationDidEnterBackground
- L97 _public prototype_ `static void HandleWillEnterForeground();` — To be used by app delegate, call it from applicationWillEnterForeground
- L100 _public prototype_ `static void SaveBackgroundHttpFileHashHelperState();` — To be used by ApplePlatformBackgroundHttpManager
- L105 _public prototype_ `static TArray<TTuple<FString, uint32, FString>> GetCDNAnalyticsData();` — Returns an ordered list of CDNs used to issue actual downloads, including AbosluteURL, ResponseTime (in ms) and Status A list of URLS provided to CreateOrFindDownload might change order if CDNReorderingTimeout > 0 to ensure better success rate. List is empty before first CreateOrFindDownload call.
- L108 _public prototype_ `static void GetDownloadDebugText(const uint64 DownloadId, TArray<FString>& Output);`
- L112 _public prototype_ `static void CleanupOldTempDownloads();` — Cleans up temp downloads placed in any subdirectory other than the current build one's
- L116 _public prototype_ `static void ClearPreExistingRequestsAtStartup(bool bEnable);` — Should be called before any other methods to enable clearing any pre-existing downloads when the system starts

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadCompleted, const uint64 , const bool );`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadCompletedExtended, const uint64 , EBackgroundHttpRequestCompletionResult );`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDownloadMetrics, const uint64 , const int32 , const float ) UE_DEPRECATED(5.7, "FBackgroundURLSessionHandler::OnDownloadMetrics is deprecated. Use OnDownloadMetricsExtended") static FOnDownloadMetrics OnDownloadMetrics;`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadMetricsExtended, const uint64 , const FBackgroundHttpRequestMetricsExtended );` — Will be invoked from didFinishCollectingMetrics
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDownloadsCompletedWhileAppWasNotRunning, const bool );` — Will be invoked from handleEventsForBackgroundURLSession application delegate. Needs to be registered very early, e.g. from static constructor. handleEventsForBackgroundURLSession is only invoked if app was killed by OS while in background and then relaunched to notify that downloads were completed. Is not invoked in any other scenario.
