# Runtime / InstallBundleManager

- module root: `Source/Runtime/InstallBundleManager`
- headers: 9; symbols: 958
- symbol kinds: class=19, delegate=26, enum=25, enumerator=151, function=98, macro=1, member=266, namespace=5, prototype=309, struct=49, typedef=8, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Core, IoStoreOnDemandCore, Json
- PublicIncludePathModuleNames: Json

### `Source/Runtime/InstallBundleManager/Private/InstallBundleManagerPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInstallBundleManager, Display, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInstallBundleManager, Display, All);`

### `Source/Runtime/InstallBundleManager/Public/BundlePrereqCombinedStatusHelper.h` (Public)


#### class `FInstallBundleCombinedProgressTracker`  
`class FInstallBundleCombinedProgressTracker`  
_L25-105_
- desc: Handles calculating the bundle status by combining progress from all of its Prerequisites. Allows you to display one progress percent that is weighted based on all bundles' values.
- L58 _public prototype_ `FInstallBundleCombinedProgressTracker(bool bAutoTick = true, TUniqueFunction<void(const FCombinedProgress&)> OnTick = nullptr);` — bAutoTick Whehter this tracker should automatically Tick
- L59 _public prototype_ `~FInstallBundleCombinedProgressTracker();`
- L61 _public prototype_ `FInstallBundleCombinedProgressTracker(const FInstallBundleCombinedProgressTracker& Other);`
- L62 _public prototype_ `FInstallBundleCombinedProgressTracker(FInstallBundleCombinedProgressTracker&& Other);`
- L64 _public prototype_ `FInstallBundleCombinedProgressTracker& operator=(const FInstallBundleCombinedProgressTracker& Other);`
- L65 _public prototype_ `FInstallBundleCombinedProgressTracker& operator=(FInstallBundleCombinedProgressTracker&& Other);`
- L68 _public prototype_ `void SetBundlesToTrackFromContentState(const FInstallBundleCombinedContentState& BundleContentState, TArrayView<FName> BundlesToTrack);` — Setup tracking for all bundles required in the supplied BundleContentState
- L71 _public prototype_ `const FCombinedProgress& GetCurrentCombinedProgress() const;` — Get current CombinedBundleStatus for everything setup to track
- L74 _public function_ `void ForceTick()` — Useful for resolving tick order issue
- L77 _private prototype_ `bool Tick(float dt);`
- L78 _private prototype_ `void UpdateBundleCache();`
- L79 _private prototype_ `void UpdateCombinedStatus();`
- L81 _private prototype_ `void SetupDelegates(bool bAutoTick);`
- L82 _private prototype_ `void CleanUpDelegates();`
- L85 _private prototype_ `void OnBundleInstallComplete(FInstallBundleRequestResultInfo CompletedBundleInfo);` — Called so we can track when a bundle is finished
- L86 _private prototype_ `void OnBundleInstallPauseChanged(FInstallBundlePauseInfo PauseInfo);`
- L88 _private prototype_ `void UpdateCombinedProgress();`
- L92 _private member_ `TArray<FName> RequiredBundleNames;` — All bundles we need including pre-reqs
- L95 _private member_ `TMap<FName, FInstallBundleProgress> BundleStatusCache;` — Internal Cache of all bundle statuses to track progress
- L98 _private member_ `TMap<FName, float> CachedBundleWeights;` — Bundle weights that determine what % of the overall install each bundle represents
- L100 _private member_ `FCombinedProgress CurrentCombinedProgress;`
- L102 _private member_ `TWeakPtr<IInstallBundleManager> InstallBundleManager;`
- L103 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L104 _private member_ `TUniqueFunction<void(const FCombinedProgress&)> OnTick;`

#### enum `FInstallBundleCombinedProgressTracker::ECombinedBundleStatus`  
`enum class ECombinedBundleStatus : int32`  
_L30-38_
- desc: Collapses all the bundle manager states into one of a few states so that you can show simple text based on this enum
- L32 _public enumerator_ `Unknown`
- L33 _public enumerator_ `Initializing`
- L34 _public enumerator_ `Updating`
- L35 _public enumerator_ `Finishing`
- L36 _public enumerator_ `Finished`
- L37 _public enumerator_ `Count`

#### struct `FInstallBundleCombinedProgressTracker::FCombinedProgress`  
`struct FCombinedProgress`  
_L41-54_
- desc: provide all our needed combined status information in 1 struct
- L43 _public member_ `float BackgroundDownloadProgressPercent = 0.0f;`
- L44 _public member_ `float InstallOnlyProgressPercent = 0.0f;`
- L45 _public member_ `float ProgressPercent = 0.0f;` — Download and Install progress combined
- L46 _public member_ `int32 InstalledBundlesCount = 0;`
- L47 _public member_ `int32 TotalBundlesCount = 0;`
- L48 _public member_ `TArray<FBuildInstallerStat> Stats;` — Used for additional information about the installs
- L49 _public member_ `ECombinedBundleStatus CombinedStatus = ECombinedBundleStatus::Unknown;`
- L50 _public member_ `EInstallBundlePauseFlags CombinedPauseFlags = EInstallBundlePauseFlags::None;`
- L51 _public member_ `bool bIsPaused = false;`
- L52 _public member_ `bool bDoesCurrentStateSupportPausing = false;`
- L53 _public member_ `bool bBundleRequiresUpdate = false;`

#### Free symbols / members of external scopes

- L107 _prototype_ `const TCHAR* LexToString(FInstallBundleCombinedProgressTracker::ECombinedBundleStatus Status);`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleCache.h` (Public)


#### struct `FInstallBundleCacheInitInfo`  
`struct FInstallBundleCacheInitInfo`  
_L18-22_
- L20 _public member_ `FName CacheName;`
- L21 _public member_ `uint64 Size = 0;`

#### struct `FInstallBundleCacheBundleInfo`  
`struct FInstallBundleCacheBundleInfo`  
_L24-32_
- L26 _public member_ `FName BundleName;`
- L27 _public member_ `uint64 FullInstallSize = 0;` — Total disk footprint when this bundle is fully installed
- L28 _public member_ `uint64 InstallOverheadSize = 0;` — Any extra space required to update the bundle
- L29 _public member_ `uint64 CurrentInstallSize = 0;` — Disk footprint of the bundle in it's current state
- L30 _public member_ `FDateTime TimeStamp = FDateTime::MinValue();` — Last access time for the bundle.  Used for eviction order
- L31 _public member_ `double AgeScalar = 1.0;` — Allow some bundles to "age" slower than others

#### enum `EInstallBundleCacheReserveResult`  
`enum class EInstallBundleCacheReserveResult : int8`  
_L34-40_
- L36 _public enumerator_ `Fail_CacheFull` — Cache is full and it's not possible to evict anything else from the cache
- L37 _public enumerator_ `Fail_NeedsEvict` — Cache is full but it' possible to evict released bundles to make room for this one
- L38 _public enumerator_ `Fail_PendingEvict` — This bundle can't be reserved because it's currently being evicted
- L39 _public enumerator_ `Success` — Bundle was reserved successfully

#### struct `FInstallBundleCacheReserveResult`  
`struct FInstallBundleCacheReserveResult`  
_L42-46_
- L44 _public member_ `TMap<FName, TArray<FInstallBundleSourceType>> BundlesToEvict;`
- L45 _public member_ `EInstallBundleCacheReserveResult Result = EInstallBundleCacheReserveResult::Success;`

#### struct `FInstallBundleCacheFlushResult`  
`struct FInstallBundleCacheFlushResult`  
_L48-51_
- L50 _public member_ `TMap<FName, TArray<FInstallBundleSourceType>> BundlesToEvict;`

#### class `FInstallBundleCache`  
`class FInstallBundleCache : public TSharedFromThis<FInstallBundleCache>`  
_L53-183_
- inherits: `TSharedFromThis<FInstallBundleCache>`
- L56 _public prototype_ `virtual ~FInstallBundleCache();`
- L58 _public prototype_ `void Init(FInstallBundleCacheInitInfo InitInfo);`
- L60 _public function_ `FName GetName() const`
- L63 _public prototype_ `void AddOrUpdateBundle(FInstallBundleSourceType Source, const FInstallBundleCacheBundleInfo& AddInfo);` — Add a bundle to the cache.
- L65 _public prototype_ `void RemoveBundle(FInstallBundleSourceType Source, FName BundleName);`
- L67 _public prototype_ `TOptional<FInstallBundleCacheBundleInfo> GetBundleInfo(FName BundleName) const;`
- L68 _public prototype_ `TOptional<FInstallBundleCacheBundleInfo> GetBundleInfo(FInstallBundleSourceType Source, FName BundleName) const;`
- L71 _public prototype_ `uint64 GetSize() const;` — Return the total size of the cache
- L74 _public prototype_ `uint64 GetUsedSize() const;` — Return the amount of space in use.  This could possbly exceed GetSize() if the cache size is changed or more bundles are added the to cache.
- L76 _public prototype_ `uint64 GetFreeSpace() const;` — Return the amount of free space in the cache, clamped to [0, GetSize()]
- L79 _public prototype_ `FInstallBundleCacheReserveResult Reserve(FName BundleName);` — Called from bundle manager
- L82 _public prototype_ `FInstallBundleCacheFlushResult Flush(FInstallBundleSourceType* Source = nullptr);` — Called from bundle manager, returns all bundles that can be evicted
- L84 _public prototype_ `bool Contains(FName BundleName) const;`
- L85 _public prototype_ `bool Contains(FInstallBundleSourceType Source, FName BundleName) const;`
- L87 _public prototype_ `bool IsReserved(FName BundleName) const;`
- L90 _public prototype_ `bool Release(FName BundleName);` — Called from bundle manager to make the files for this bundle eligible for eviction
- L92 _public prototype_ `bool SetPendingEvict(FName BundleName);`
- L94 _public prototype_ `bool ClearPendingEvict(FName BundleName);`
- L97 _public prototype_ `void HintRequested(FName BundleName, bool bRequested);` — Hint to the cache that this bundle is requested, and we should prefer to evict non-requested bundles if possible
- L99 _public prototype_ `FInstallBundleCacheStats GetStats(EInstallBundleCacheStatsFlags Flags = EInstallBundleCacheStatsFlags::None, bool bVerbose = false) const;`
- L102 _private prototype_ `uint64 GetFreeSpaceInternal(uint64 UsedSize) const;`
- L104 _private prototype_ `void CheckInvariants() const;`
- L106 _private prototype_ `void UpdateCacheInfoFromSourceInfo(FName BundleName);`
- L175 _private member_ `TMap<FName, TMap<FInstallBundleSourceType, FPerSourceBundleCacheInfo>> PerSourceCacheInfo;`
- L178 _private member_ `mutable TMap<FName, FBundleCacheInfo> CacheInfo;` — mutable to allow sorting in const contexts
- L180 _private member_ `uint64 TotalSize = 0;`
- L182 _private member_ `FName CacheName;`

#### struct `FInstallBundleCache::FPerSourceBundleCacheInfo`  
`struct FPerSourceBundleCacheInfo`  
_L109-116_
- L111 _public member_ `uint64 FullInstallSize = 0;`
- L112 _public member_ `uint64 InstallOverheadSize = 0;`
- L113 _public member_ `uint64 CurrentInstallSize = 0;`
- L114 _public member_ `FDateTime TimeStamp = FDateTime::MinValue();`
- L115 _public member_ `double AgeScalar = 1.0;`

#### enum `FInstallBundleCache::ECacheState`  
`enum class ECacheState : uint8`  
_L118-123_
- L120 _public enumerator_ `Released` — Transitions to Reserved or PendingEvict
- L121 _public enumerator_ `Reserved` — Transitions to Released
- L122 _public enumerator_ `PendingEvict` — Transitions to Released

#### struct `FInstallBundleCache::FBundleCacheInfo`  
`struct FBundleCacheInfo`  
_L125-152_
- L127 _public member_ `uint64 FullInstallSize = 0;`
- L128 _public member_ `uint64 InstallOverheadSize = 0;`
- L129 _public member_ `uint64 CurrentInstallSize = 0;`
- L130 _public member_ `FDateTime TimeStamp = FDateTime::MinValue();`
- L131 _public member_ `double AgeScalar = 1.0;`
- L132 _public member_ `ECacheState State = ECacheState::Released;`
- L133 _public member_ `int32 HintReqeustedCount = 0;` — Hint to the cache that this bundle is requested, and we should prefer to evict non-requested bundles if possible
- L135 _public function_ `bool IsHintRequested() const`
- L137 _public function_ `uint64 GetSize() const`

#### struct `FInstallBundleCache::FCacheSortPredicate`  
`struct FCacheSortPredicate`  
_L154-171_
- L156 _public function_ `bool operator()(const FBundleCacheInfo& A, const FBundleCacheInfo& B) const`
- L170 _private member_ `FDateTime Now = FDateTime::UtcNow();`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleManagerInterface.h` (Public)


#### struct `FInstallBundleProgress`  
`struct FInstallBundleProgress`  
_L31-46_
- L33 _public member_ `FName BundleName;`
- L35 _public member_ `EInstallBundleStatus Status = EInstallBundleStatus::Requested;`
- L37 _public member_ `EInstallBundlePauseFlags PauseFlags = EInstallBundlePauseFlags::None;`
- L39 _public member_ `float BackgroundDownload_Percent = 0;`
- L40 _public member_ `float InstallOnly_Percent = 0;`
- L41 _public member_ `float Install_Percent = 0;` — Download and Install progress combined
- L43 _public member_ `TArray<FBuildInstallerStat> Stats;` — Used for additional information about the install
- L45 _public member_ `float Finishing_Percent = 0;`

#### struct `FInstallBundleRequestResultInfo`  
`struct FInstallBundleRequestResultInfo`  
_L48-60_
- L50 _public member_ `FName BundleName;`
- L51 _public member_ `EInstallBundleResult Result = EInstallBundleResult::OK;`
- L52 _public member_ `bool bIsStartup = false;`
- L53 _public member_ `bool bContainsChunks = false;`
- L54 _public member_ `bool bContainsIoStoreOnDemand = false;`
- L55 _public member_ `bool bContentWasInstalled = false;`
- L58 _public member_ `FText OptionalErrorText;` — Currently, these just forward BPT Error info
- L59 _public member_ `FString OptionalErrorCode;`

#### struct `FInstallBundleReleaseRequestResultInfo`  
`struct FInstallBundleReleaseRequestResultInfo`  
_L62-66_
- L64 _public member_ `FName BundleName;`
- L65 _public member_ `EInstallBundleReleaseResult Result = EInstallBundleReleaseResult::OK;`

#### struct `FInstallBundleRequestInfo`  
`struct FInstallBundleRequestInfo`  
_L68-73_
- L70 _public member_ `EInstallBundleRequestInfoFlags InfoFlags = EInstallBundleRequestInfoFlags::None;`
- L71 _public member_ `TArray<FName> BundlesEnqueued;`
- L72 _public member_ `TArray<FInstallBundleRequestResultInfo> BundleResults;`

#### struct `FInstallBundleReleaseRequestInfo`  
`struct FInstallBundleReleaseRequestInfo`  
_L75-79_
- L77 _public member_ `EInstallBundleRequestInfoFlags InfoFlags = EInstallBundleRequestInfoFlags::None;`
- L78 _public member_ `TArray<FName> BundlesEnqueued;`

#### struct `FInstallBundlePauseInfo`  
`struct FInstallBundlePauseInfo`  
_L81-85_
- L83 _public member_ `FName BundleName;`
- L84 _public member_ `EInstallBundlePauseFlags PauseFlags = EInstallBundlePauseFlags::None;`

#### enum `EInstallBundleManagerInitErrorHandlerResult`  
`enum class EInstallBundleManagerInitErrorHandlerResult`  
_L87-92_
- L89 _public enumerator_ `NotHandled` — Defer to the next handler
- L90 _public enumerator_ `Retry` — Try to initialize again
- L91 _public enumerator_ `StopInitialization` — Stop trying to initialize

#### struct `FInstallBundleChunkDownloadInfo`  
`struct FInstallBundleChunkDownloadInfo`  
_L94-102_
- L96 _public member_ `FName BundleName;`
- L97 _public member_ `FString ChunkName;`
- L98 _public member_ `int32 ChunkFileSize;`
- L99 _public member_ `float ChunkDownloadDuration;`
- L100 _public member_ `FDateTime FetchStartTimeUTC;`
- L101 _public member_ `FDateTime FetchEndTimeUTC;`

#### class `IInstallBundleManager`  
`class IInstallBundleManager : public TSharedFromThis<IInstallBundleManager>`  
_L125-253_
- inherits: `TSharedFromThis<IInstallBundleManager>`
- L128 _public member_ `static FInstallBundleManagerInitCompleteMultiDelegate InitCompleteDelegate;`
- L130 _public member_ `static FInstallBundleChunkDownloadMetricsMultiDelegate InstallBundleChunkDownloadMetricsDelegate;` — Called when a content request metrics is available
- L131 _public member_ `static FInstallBundleCompleteMultiDelegate InstallBundleCompleteDelegate;` — Called when a content request is complete
- L132 _public member_ `static FInstallBundlePausedMultiDelegate PausedBundleDelegate;`
- L133 _public member_ `static FInstallBundleReleasedMultiDelegate ReleasedDelegate;` — Called when content release request is complete
- L134 _public member_ `static FInstallBundleManagerOnPatchCheckComplete PatchCheckCompleteDelegate;`
- L135 _public member_ `static FInstallBundleManagerReportingDelegate ReportingDelegate;`
- L136 _public member_ `static FInstallBundleManagerAllDownloadsCompleted AllDownloadsCompletedDelegate;` — Called when all content downloads completed
- L138 _public prototype_ `static TSharedPtr<IInstallBundleManager> GetPlatformInstallBundleManager();`
- L140 _public prototype_ `virtual ~IInstallBundleManager() = default;`
- L142 _public function_ `virtual void Initialize()`
- L144 _public prototype_ `virtual bool HasBundleSource(FInstallBundleSourceType SourceType) const = 0;`
- L146 _public prototype_ `virtual void SetContext(FName ContextName);`
- L147 _public prototype_ `virtual bool CopyReportTo(FInstallManagerBundleReport& Report);`
- L149 _public prototype_ `virtual const TSharedPtr<IInstallBundleSource> GetBundleSource(FInstallBundleSourceType SourceType) const;`
- L152 _public function_ `virtual int32 SelectBundleSubset(const FString& BundleName, TConstArrayView<FString> BundleSubsets) const` — Note: Some bundles sources may call this from a background task, so it should be threadsafe
- L154 _public prototype_ `virtual FDelegateHandle PushInitErrorCallback(FInstallBundleManagerInitErrorHandler Callback) = 0;`
- L155 _public prototype_ `virtual void PopInitErrorCallback() = 0;`
- L156 _public prototype_ `virtual void PopInitErrorCallback(FDelegateHandle Handle) = 0;`
- L157 _public prototype_ `virtual void PopInitErrorCallback(FDelegateUserObjectConst InUserObject) = 0;`
- L159 _public prototype_ `virtual EInstallBundleManagerInitState GetInitState() const = 0;`
- L161 _public prototype_ `TValueOrError<FInstallBundleRequestInfo, EInstallBundleResult> RequestUpdateContent(FName BundleName, EInstallBundleRequestFlags Flags, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging, InstallBundleUtil::FContentRequestSharedContextPtr RequestSharedContext = nullptr);`
- L162 _public prototype_ `virtual TValueOrError<FInstallBundleRequestInfo, EInstallBundleResult> RequestUpdateContent(TArrayView<const FName> BundleNames, EInstallBundleRequestFlags Flags, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging, InstallBundleUtil::FContentRequestSharedContextPtr RequestSharedContext = nullptr) = 0;`
- L164 _public prototype_ `FDelegateHandle GetContentState(FName BundleName, EInstallBundleGetContentStateFlags Flags, bool bAddDependencies, FInstallBundleGetContentStateDelegate Callback, FName RequestTag = NAME_None);`
- L165 _public prototype_ `virtual FDelegateHandle GetContentState(TArrayView<const FName> BundleNames, EInstallBundleGetContentStateFlags Flags, bool bAddDependencies, FInstallBundleGetContentStateDelegate Callback, FName RequestTag = NAME_None) = 0;`
- L166 _public prototype_ `virtual void CancelAllGetContentStateRequestsForTag(FName RequestTag) = 0;`
- L167 _public prototype_ `virtual void CancelAllGetContentStateRequests(FDelegateHandle Handle) = 0;`
- L171 _public prototype_ `FDelegateHandle GetInstallState(FName BundleName, bool bAddDependencies, FInstallBundleGetInstallStateDelegate Callback, FName RequestTag = NAME_None);` — Less expensive version of GetContentState() that only returns install state Synchronous versions return null if bundle manager is not yet initialized
- L172 _public prototype_ `virtual FDelegateHandle GetInstallState(TArrayView<const FName> BundleNames, bool bAddDependencies, FInstallBundleGetInstallStateDelegate Callback, FName RequestTag = NAME_None) = 0;`
- L173 _public prototype_ `TValueOrError<FInstallBundleCombinedInstallState, EInstallBundleResult> GetInstallStateSynchronous(FName BundleName, bool bAddDependencies) const;`
- L174 _public prototype_ `virtual TValueOrError<FInstallBundleCombinedInstallState, EInstallBundleResult> GetInstallStateSynchronous(TArrayView<const FName> BundleNames, bool bAddDependencies) const = 0;`
- L175 _public prototype_ `virtual EInstallBundleResult GetAllMountedBundles(TArray<FName>& OutBundleNames) const = 0;`
- L176 _public prototype_ `virtual EInstallBundleResult GetAllBundlesWithState(EInstallBundleInstallState InstallState, TArray<FName>& OutBundleNames) const = 0;`
- L177 _public prototype_ `virtual void CancelAllGetInstallStateRequestsForTag(FName RequestTag) = 0;`
- L178 _public prototype_ `virtual void CancelAllGetInstallStateRequests(FDelegateHandle Handle) = 0;`
- L180 _public prototype_ `TValueOrError<FInstallBundleReleaseRequestInfo, EInstallBundleResult> RequestReleaseContent(FName ReleaseName, EInstallBundleReleaseRequestFlags Flags, TArrayView<const FName> KeepNames = TArrayView<const FName>(), ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging);`
- L181 _public prototype_ `virtual TValueOrError<FInstallBundleReleaseRequestInfo, EInstallBundleResult> RequestReleaseContent(TArrayView<const FName> ReleaseNames, EInstallBundleReleaseRequestFlags Flags, TArrayView<const FName> KeepNames = TArrayView<const FName>(), ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) = 0;`
- L183 _public prototype_ `EInstallBundleResult FlushCache(FInstallBundleManagerFlushCacheCompleteDelegate Callback, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging);`
- L184 _public prototype_ `virtual EInstallBundleResult FlushCache(FInstallBundleSourceOrCache SourceOrCache, FInstallBundleManagerFlushCacheCompleteDelegate Callback, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) = 0;`
- L188 _public prototype_ `virtual TArray<FInstallBundleCacheStats> GetCacheStats(EInstallBundleCacheDumpToLog DumpToLog, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging);` — `UE_DEPRECATED(5.7, "Use overload with EInstallBundleCacheStatsFlags")`
- L190 _public prototype_ `virtual TOptional<FInstallBundleCacheStats> GetCacheStats(FInstallBundleSourceOrCache SourceOrCache, EInstallBundleCacheDumpToLog DumpToLog, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging);` — `UE_DEPRECATED(5.7, "Use overload with EInstallBundleCacheStatsFlags")`
- L193 _public prototype_ `virtual TArray<FInstallBundleCacheStats> GetCacheStats(EInstallBundleCacheStatsFlags Flags = EInstallBundleCacheStatsFlags::None, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) = 0;`
- L194 _public prototype_ `virtual TOptional<FInstallBundleCacheStats> GetCacheStats(FInstallBundleSourceOrCache SourceOrCache, EInstallBundleCacheStatsFlags Flags = EInstallBundleCacheStatsFlags::None, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) = 0;`
- L196 _public prototype_ `void RequestRemoveContentOnNextInit(FName RemoveName, TArrayView<const FName> KeepNames = TArrayView<const FName>());`
- L197 _public prototype_ `virtual void RequestRemoveContentOnNextInit(TArrayView<const FName> RemoveNames, TArrayView<const FName> KeepNames = TArrayView<const FName>()) = 0;`
- L199 _public prototype_ `void CancelRequestRemoveContentOnNextInit(FName BundleName);`
- L200 _public prototype_ `virtual void CancelRequestRemoveContentOnNextInit(TArrayView<const FName> BundleNames) = 0;`
- L202 _public prototype_ `virtual TArray<FName> GetRequestedRemoveContentOnNextInit() const = 0;`
- L204 _public prototype_ `void CancelUpdateContent(FName BundleName);`
- L205 _public prototype_ `virtual void CancelUpdateContent(TArrayView<const FName> BundleNames) = 0;`
- L207 _public prototype_ `void PauseUpdateContent(FName BundleName);`
- L208 _public prototype_ `virtual void PauseUpdateContent(TArrayView<const FName> BundleNames) = 0;`
- L210 _public prototype_ `void ResumeUpdateContent(FName BundleName);`
- L211 _public prototype_ `virtual void ResumeUpdateContent(TArrayView<const FName> BundleNames) = 0;`
- L213 _public prototype_ `virtual void RequestPausedBundleCallback() = 0;`
- L215 _public prototype_ `virtual TOptional<FInstallBundleProgress> GetBundleProgress(FName BundleName) const = 0;`
- L217 _public prototype_ `virtual EInstallBundleRequestFlags GetModifyableContentRequestFlags() const = 0;`
- L218 _public prototype_ `void UpdateContentRequestFlags(FName BundleName, EInstallBundleRequestFlags AddFlags, EInstallBundleRequestFlags RemoveFlags);`
- L219 _public prototype_ `virtual void UpdateContentRequestFlags(TArrayView<const FName> BundleNames, EInstallBundleRequestFlags AddFlags, EInstallBundleRequestFlags RemoveFlags) = 0;`
- L220 _public prototype_ `virtual void SetCellularPreference(int32 Value) = 0;`
- L221 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) = 0;`
- L225 _public function_ `virtual void UnblockAnyDownloadsWaitingForCellularOptIn()` — Unblocks any pending downloads that are waiting for opting into using cellular data. Semantic wrapper until we get a better API.
- L232 _public prototype_ `virtual void SetCacheSize(FName CacheName, uint64 CacheSize) = 0;`
- L234 _public prototype_ `virtual void StartPatchCheck();`
- L235 _public function_ `virtual void AddEnvironmentWantsPatchCheckBackCompatDelegate(FName Tag, FInstallBundleManagerEnvironmentWantsPatchCheck Delegate)`
- L236 _public function_ `virtual void RemoveEnvironmentWantsPatchCheckBackCompatDelegate(FName Tag)`
- L237 _public prototype_ `virtual bool SupportsEarlyStartupPatching() const = 0;`
- L239 _public prototype_ `virtual bool IsNullInterface() const = 0;`
- L241 _public function_ `virtual void SetErrorSimulationCommands(const FString& CommandLine)`
- L243 _public function_ `virtual TSharedPtr<IAnalyticsProviderET> GetAnalyticsProvider() const`
- L245 _public function_ `virtual void StartSessionPersistentStatTracking(const FString& SessionName, const TArray<FName>& RequiredBundles = TArray<FName>(), const FString& ExpectedAnalyticsID = FString(), bool bForceResetStatData = false, const FInstallBundleCombinedContentState* State = nullptr)`
- L246 _public function_ `virtual void StopSessionPersistentStatTracking(const FString& SessionName)`
- L249 _public function_ `virtual void GetDebugText(TArray<FString>& Output)`
- L252 _public function_ `virtual bool HasEverUpdatedContent() const`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace InstallBundleUtil`
- L28 _typedef_ `using FContentRequestSharedContextPtr = TSharedPtr<FContentRequestSharedContext>;` (scope `InstallBundleUtil`)
- L104 _typedef_ `using FInstallBundleSourceOrCache = TUnion<FInstallBundleSourceType, FName>;`
- L106 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EInstallBundleManagerInitErrorHandlerResult, FInstallBundleManagerInitErrorHandler, EInstallBundleManagerInitResult);`
- L106 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EInstallBundleManagerInitErrorHandlerResult, FInstallBundleManagerInitErrorHandler, EInstallBundleManagerInitResult);`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleManagerInitCompleteMultiDelegate, EInstallBundleManagerInitResult);`
- L107 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleManagerInitCompleteMultiDelegate, EInstallBundleManagerInitResult);`
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleChunkDownloadMetricsMultiDelegate, FInstallBundleChunkDownloadInfo);`
- L109 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleChunkDownloadMetricsMultiDelegate, FInstallBundleChunkDownloadInfo);`
- L110 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleCompleteMultiDelegate, FInstallBundleRequestResultInfo);`
- L110 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleCompleteMultiDelegate, FInstallBundleRequestResultInfo);`
- L111 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundlePausedMultiDelegate, FInstallBundlePauseInfo);`
- L111 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundlePausedMultiDelegate, FInstallBundlePauseInfo);`
- L112 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleReleasedMultiDelegate, FInstallBundleReleaseRequestResultInfo);`
- L112 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleReleasedMultiDelegate, FInstallBundleReleaseRequestResultInfo);`
- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleManagerOnPatchCheckComplete, EInstallBundleManagerPatchCheckResult);`
- L114 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleManagerOnPatchCheckComplete, EInstallBundleManagerPatchCheckResult);`
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleManagerReportingDelegate, const FInstallManagerBundleReport&);`
- L116 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstallBundleManagerReportingDelegate, const FInstallManagerBundleReport&);`
- L118 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FInstallBundleManagerEnvironmentWantsPatchCheck);`
- L118 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FInstallBundleManagerEnvironmentWantsPatchCheck);`
- L120 _delegate_ `DECLARE_DELEGATE_OneParam(FInstallBundleGetInstallStateDelegate, FInstallBundleCombinedInstallState);`
- L120 _prototype_ `DECLARE_DELEGATE_OneParam(FInstallBundleGetInstallStateDelegate, FInstallBundleCombinedInstallState);`
- L122 _delegate_ `DECLARE_DELEGATE(FInstallBundleManagerFlushCacheCompleteDelegate);`
- L122 _prototype_ `DECLARE_DELEGATE(FInstallBundleManagerFlushCacheCompleteDelegate);`
- L123 _delegate_ `DECLARE_DELEGATE(FInstallBundleManagerAllDownloadsCompleted);`
- L123 _prototype_ `DECLARE_DELEGATE(FInstallBundleManagerAllDownloadsCompleted);`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleManagerModule.h` (Public)


#### class `FInstallBundleManagerModule`  
`class FInstallBundleManagerModule : public IModuleInterface`  
_L19-30_
- inherits: `IModuleInterface`
- desc: Currently empty implementation for InstallBundleModule until things are moved in here.
- L23 _public function_ `virtual void StartupModule() override` — IModuleInterface interface
- L27 _public function_ `virtual void ShutdownModule() override`

#### class `IInstallBundleManagerModule`  
`class IInstallBundleManagerModule : public IModuleInterface`  
_L35-53_
- inherits: `IModuleInterface`
- desc: Base Module Interface for InstallBundleManager implementation modules
- L38 _public function_ `virtual void PreUnloadCallback() override`
- L45 _public function_ `TSharedPtr<IInstallBundleManager> GetInstallBundleManager()`
- L51 _protected member_ `TSharedPtr<IInstallBundleManager> InstallBundleManager;`
- L52 _protected member_ `TWeakPtr<IInstallBundleManager> LastInstallBundleManager;`

#### class `TInstallBundleManagerModule`  
`template<class InstallBundleManagerModuleImpl> class TInstallBundleManagerModule : public IInstallBundleManagerModule`  
_L59-81_
- inherits: `IInstallBundleManagerModule`
- desc: Module Interface for InstallBundleManager implementation modules
- L62 _public function_ `virtual void StartupModule() override`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleManagerReporting.h` (Public)


#### struct `FInstallBundleReport`  
`struct FInstallBundleReport : public FJsonSerializable`  
_L9-114_
- inherits: `FJsonSerializable`
- L73 _public typedef_ `using FState = TVariant<FStateUpdatable, FStateUpdating, FStateInstalling, FStateUpdated>;`
- L76 _public member_ `FName BundleName;` — The name of the bundle
- L80 _public member_ `TOptional<FString> SourceVersion;` — A string specifying what content version is being upgraded FROM. The format of this string is specific for the source. NOTE: if there is no known source version, this value should not be set.
- L83 _public member_ `TOptional<FState> State;` — The state of the bundle
- L93 _public prototype_ `JSON_SERIALIZE_OPTIONAL_VARIANT_END();`
- L97 _public prototype_ `uint64 TotalDownloadSize() const;` — Returns the total amount of bytes that will or has been downloaded for this bundle.
- L100 _public prototype_ `uint64 DownloadedBytes() const;` — Returns the amount of downloaded bytes for this bundle, should always be 0 <= x <= TotalDownloadSize()
- L104 _public prototype_ `float InstallationProgress() const;` — Returns a value 0 <= x <= 1 to indicate the installation progress. If the source doesn't support gradual installation progress, this will pop from 0 to 1.
- L107 _public prototype_ `void AddDiscrepancy(uint64 Bytes);` — Adds missing bytes to content size and download progress
- L109 _public function_ `bool IsUnknown() const`
- L110 _public function_ `bool IsUpdatable() const`
- L111 _public function_ `bool IsUpdating() const`
- L112 _public function_ `bool IsInstalling() const`
- L113 _public function_ `bool IsUpdated() const`

#### struct `FInstallBundleReport::FStateUpdatable`  
`struct FStateUpdatable : public FJsonSerializable`  
_L13-21_
- inherits: `FJsonSerializable`
- desc: State that represents an updatable bundle, where a choice can be made to update in the background, or without.
- L16 _public member_ `uint64 DownloadSize;` — The total amount of bytes to download for the bundle

#### struct `FInstallBundleReport::FStateUpdating`  
`struct FStateUpdating : public FJsonSerializable`  
_L24-45_
- inherits: `FJsonSerializable`
- desc: State that represents a bundle that is updating
- L27 _public member_ `uint64 DownloadSize;` — The total amount of bytes that needs to be downloaded for the bundle
- L30 _public member_ `bool bUsesBackgroundDownloads = false;` — Indicates if this bundle is being updated with background downloads or not
- L34 _public member_ `float DownloadProgress = 0;` — Indicates, in a value 0 <= x <= 1 the progress of the downloads. If this value reaches 1, the bundle can be assumed to be installed.
- L37 _public member_ `uint64 BackgroundDownloadedBytes;` — Indicates how many bytes were downloaded in the background

#### struct `FInstallBundleReport::FStateInstalling`  
`struct FStateInstalling : public FJsonSerializable`  
_L47-60_
- inherits: `FJsonSerializable`
- L50 _public member_ `uint64 DownloadedSize;` — The total amount of bytes that have been downloaded for the bundle
- L54 _public member_ `float InstallProgress = 0;` — The progress of the installation, if available, otherwise probably always 0; once the bundle switches to updated state, the InstallProgress is essentially 1

#### struct `FInstallBundleReport::FStateUpdated`  
`struct FStateUpdated : public FJsonSerializable`  
_L63-71_
- inherits: `FJsonSerializable`
- desc: State that represents a fully updated bundle that no longer needs to be updated
- L66 _public member_ `uint64 DownloadedSize;` — The total amount of bytes that have been downloaded for the bundle

#### struct `FInstallBundleSourceReport`  
`struct FInstallBundleSourceReport : public FJsonSerializable`  
_L116-153_
- inherits: `FJsonSerializable`
- L119 _public member_ `FName SourceType;` — The bundle source's type string
- L123 _public member_ `TOptional<FString> TargetVersion;` — A string specifying what content version is being upgrade TO. The format of this string is specific for the source. NOTE: if there is no known target version, this value should not be set.
- L126 _public member_ `TArray<FInstallBundleReport> Bundles;` — Array containing a single bundle report for every bundle this source is handling.
- L136 _public prototype_ `FInstallBundleReport* TryFindBundleReport(FName BundleName);` — Returns pointer to bundle report that's valid as long as Bundles is not modified. Returns nullptr if there is no report yet for the given type.
- L140 _public prototype_ `FInstallBundleReport& FindOrAddBundleReport(FName BundleName);` — Returns a reference to the bundle source report for the given type. It adds one if it doesn't exist yet. The reference is valid as long as SourceReports is not modified.
- L143 _public prototype_ `uint64 TotalDownloadSize() const;` — Returns the total amount of bytes that will or has been downloaded for this bundle source for all bundles
- L146 _public prototype_ `uint64 DownloadedBytes() const;` — Returns the amount of downloaded bytes for this bundle source for all bundles, should always be 0 <= x <= TotalDownloadSize()
- L149 _public prototype_ `int TotalBundleCount() const;` — Returns the total amount of bundles being updated, regardless of their state
- L152 _public prototype_ `int UpdatedBundleCount() const;` — Returns the amount of bundles that has being updated

#### struct `FInstallManagerBundleReport`  
`struct FInstallManagerBundleReport : public FJsonSerializable`  
_L155-233_
- inherits: `FJsonSerializable`
- L167 _public member_ `FName ContextName;` — the context name for this bundle report
- L170 _public member_ `FString SessionId;` — Semi-unique session string, changes every time any bundle source decides to start updating to a new version; generated using UUID
- L174 _public member_ `TOptional<uint32> BackgroundedCount;` — Indicates, if set, how many times the application was backgrounded during the update process for this bundle. If not set, the bundle source does not keep track of this.
- L177 _public member_ `uint32 LoadedCount = 0;` — Indicates how many times this report has been loaded from disk; in other words, indicates how many times the update process was restarted.
- L180 _public member_ `TArray<FInstallBundleSourceReport> SourceReports;` — Array containing a single source report for every unique source bundle the manager knows.
- L192 _public prototype_ `FInstallBundleSourceReport* TryFindBundleSourceReport(const FInstallBundleSourceType& Type);` — Returns pointer to bundle source report that's valid as long as SourceReports is not modified. Returns nullptr if there is no report yet for the given type.
- L196 _public prototype_ `FInstallBundleSourceReport& FindOrAddBundleSourceReport(const FInstallBundleSourceType& Type);` — Returns a reference to the bundle source report for the given type. It adds one if it doesn't exist yet. The reference is valid as long as SourceReports is not modified.
- L200 _public prototype_ `float GetDownloadProgress() const;` — Returns the download progress. This returns a value 0 <= x <= 1.
- L204 _public prototype_ `float GetInstallationProgress() const;` — Returns the overall installation progress, which is separate from the download progress This returns a value 0 <= x <= 1.
- L207 _public prototype_ `uint64 TotalDownloadSize() const;` — Returns the total amount of bytes that will or has been downloaded.
- L210 _public prototype_ `uint64 DownloadedBytes() const;` — Returns the amount of downloaded bytes, should always be 0 <= x <= TotalDownloadSize()
- L213 _public prototype_ `int TotalBundleCount() const;` — Returns the total amount of bundles being updated, regardless of their state
- L216 _public prototype_ `int UpdatedBundleCount() const;` — Returns the amount of bundles that has being updated
- L219 _public prototype_ `FString GetProgressString() const;` — Returns a progress string
- L222 _public prototype_ `FString GetLongProgressString() const;` — Returns a longer progress string with more information
- L225 _public prototype_ `ECombinedStatus GetCombinedStatus() const;` — Returns a combined status of all bundles
- L229 _public prototype_ `TOptional<FString> GetLowestCurrentBundleVersion() const;` — Returns the lowest current versions of any bundle. If any bundle has no such version (in other words, nothing is installed), or if there are no bundles, this returns an empty optional.
- L232 _public prototype_ `TOptional<FString> GetHighestCurrentBundleVersion() const;` — Returns the highest current versions of any bundle. If not a single bundle has a version set, this returns an empty optional.

#### enum `FInstallManagerBundleReport::ECombinedStatus`  
`enum class ECombinedStatus`  
_L157-164_
- L159 _public enumerator_ `Unknown` — if there are no bundle sources, or no bundles, or if at least one bundle is set to unknown
- L160 _public enumerator_ `Updatable` — if none of the above, if all bundles are set to updatable
- L161 _public enumerator_ `Updating` — if none of the above, if at least one bundle is still updating
- L162 _public enumerator_ `Finishing` — if none of the above, if at least one bundle is still installing
- L163 _public enumerator_ `Finished` — if none of the above, all bundles have been updated

#### class `FInstallManagerBundleReportCache`  
`class FInstallManagerBundleReportCache`  
_L237-255_
- L240 _public prototype_ `FInstallManagerBundleReportCache(TArray<TUniquePtr<InstallBundleUtil::FInstallBundleTask>>& AsyncTasks);`
- L243 _public prototype_ `void Load(FInstallManagerBundleReportCacheDoneLoadingDelegate OnLoadCompleteCallback);` — Attempts to load the cached bundle report from disk; calls the delegate when it's done loading.
- L246 _public function_ `const FInstallManagerBundleReport& GetReport() const` — Returns the current report as cached on disk (or last Set)
- L249 _public prototype_ `void SetReport(FInstallManagerBundleReport NewReport);` — Sets the new report, both in memory, as well as flushing it to disk on a separate thread automatically.
- L252 _private member_ `FInstallManagerBundleReport Report;`
- L253 _private member_ `TArray<TUniquePtr<InstallBundleUtil::FInstallBundleTask>>& AsyncTasks;`
- L254 _private member_ `FString ReportFilename;`

#### Free symbols / members of external scopes

- L235 _delegate_ `DECLARE_DELEGATE(FInstallManagerBundleReportCacheDoneLoadingDelegate);`
- L235 _prototype_ `DECLARE_DELEGATE(FInstallManagerBundleReportCacheDoneLoadingDelegate);`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleSourceInterface.h` (Public)


#### class `IInstallBundleSource`  
`class IInstallBundleSource : public TSharedFromThis<IInstallBundleSource>`  
_L29-170_
- inherits: `TSharedFromThis<IInstallBundleSource>`
- L32 _public prototype_ `virtual ~IInstallBundleSource() = default;`
- L35 _public prototype_ `virtual FInstallBundleSourceType GetSourceType() const = 0;` — Returns a unique id for this source
- L38 _public function_ `virtual float GetSourceWeight() const` — Returns the how this source should be weighted when combined with other sources
- L41 _public function_ `virtual double GetSourceCacheAgeScalar() const` — Returns a value in the [0.1, 1.0] range that allows bundles using this source to age out of the LRU cache more slowly
- L45 _public prototype_ `virtual FInstallBundleSourceInitInfo Init( TSharedRef<InstallBundleUtil::FContentRequestStatsMap> InRequestStats, TSharedPtr<IAnalyticsProviderET> AnalyticsProvider, TSharedPtr<InstallBundleUtil::PersistentStats::FPersistentStatContainerBase> PersistentStatsContainer) = 0;` — Called once by bundle manager after constructing the bundle source Any non-fallback errors returned will cause bundle manager to fail to initialize
- L51 _public prototype_ `virtual void AsyncInit(FInstallBundleSourceInitDelegate Callback) = 0;` — Bundle manager will not call AsyncInit again until the bundle source calls back that it is complete It will be retried indefinitely until init is successful.
- L55 _public prototype_ `virtual void AsyncInit_QueryBundleInfo(FInstallBundleSourceQueryBundleInfoDelegate OnCompleteCallback) = 0;` — Currently only called after AsyncInit initialization. Provides information about bundles this source knows about back to bundle manager.
- L60 _public function_ `virtual void AsyncInit_SetUpdateBundleInfoCallback( FInstallBundleSourceUpdateBundleInfoDelegate UpdateCallback, FInstallBundleLostRelevanceForSourceDelegate LostRelevanceCallback)` — Sets callbacks to Install Bundle Manager for dynamically discovered bundles UpdateCallback - Call to add or update bundle info from this source.  Must be called when there are no requests for the bundle. LostRelevanceCallback - Allows bundle manager to clean up bundles if they are no longer relevant to any source
- L63 _public function_ `virtual void OnBundleInfoPruned(FName InBundleName)`
- L66 _public prototype_ `virtual EInstallBundleManagerInitState GetInitState() const = 0;` — Whether this source has been initialized or not
- L69 _public prototype_ `virtual FString GetContentVersion() const = 0;` — Returns content version in a "<BuildVersion>-<Platform>" format
- L73 _public prototype_ `virtual TSet<FName> GetBundleDependencies(FName InBundleName, TSet<FName>* SkippedUnknownBundles = nullptr) const = 0;` — Finds all dependencies for InBundleName, including InBundleName SkippedUnknownBundles contains any unknown bundles that may have been found
- L77 _public prototype_ `virtual void GetContentState(TArrayView<const FName> BundleNames, EInstallBundleGetContentStateFlags Flags, FInstallBundleGetContentStateDelegate Callback) = 0;` — Gets the state of content on disk BundleNames contains all dependencies and has been deduped
- L82 _public function_ `virtual EInstallBundleSourceBundleSkipReason GetBundleSkipReason(FName BundleName) const` — Allows this bundle source to reject bundle requests early, rather than failing them. This means that client code does not have to wait on these bundles. This may be called anytime after Init, even during AsyncInit
- L97 _public prototype_ `virtual void RequestUpdateContent(FRequestUpdateContentBundleContext BundleContext) = 0;` — Updates content on disk if necessary BundleContexts contains all dependencies and has been deduped
- L112 _public function_ `virtual void RequestReleaseContent(FRequestReleaseContentBundleContext BundleContext)` — Notify bundle source that a bundle has been released If EInstallBundleReleaseRequestFlags::RemoveFilesIfPossible is set, the source should remove content from disk if present The source should set bContentWasRemoved to indicate to bundle manager that the bundle content was uninstalled BundleContexts contains all dependencies and has been deduped Bundle manager will not schedule removes at the same time as updates for the same bundle
- L121 _public function_ `virtual bool RequestRemoveContentOnNextInit(TArrayView<const FName> RemoveNames)` — Returns true if content is scheduled to be removed the next time the source is initialized BundleNames contains all dependencies and has been deduped
- L124 _public function_ `virtual bool CancelRequestRemoveContentOnNextInit(TArrayView<const FName> BundleNames)` — Call to cancel the removal of any content scheduled for removal the next time the source is initialized Returns true if all bundles were canceled
- L126 _public function_ `virtual TArray<FName> GetRequestedRemoveContentOnNextInit() const` — Returns the bundle names of any content that is currently removal the next time the source is initialized
- L129 _public function_ `virtual void CancelBundles(TArrayView<const FName> BundleNames)` — Cancel the install for the specified bundles
- L130 _public function_ `virtual void CancelBundles(TArrayView<const FName> BundleNames, TArray<FName>& OutAdditionalBunldlesToCancel)`
- L133 _public function_ `virtual void UserPauseBundles(TArrayView<const FName> BundleNames)` — User Pause/Resume bundles.
- L134 _public function_ `virtual void UserResumeBundles(TArrayView<const FName> BundleNames)`
- L138 _public function_ `virtual EInstallBundleRequestFlags GetModifyableContentRequestFlags() const` — UpdateContentRequestFlags - Allow some flags to be updated for in flight requests Currently only CheckForCellularDataUsage/CheckForLimitedDataUsage are supported
- L139 _public function_ `virtual void UpdateContentRequestFlags(TArrayView<const FName> BundleNames, EInstallBundleRequestFlags AddFlags, EInstallBundleRequestFlags RemoveFlags)`
- L140 _public function_ `virtual void SetCellularPreference(int32 Value)`
- L141 _public function_ `virtual void SetLimitedDataPreference(int32 Value)`
- L144 _public function_ `virtual TOptional<FInstallBundleSourceProgress> GetBundleProgress(FName BundleName) const` — Derived classes should implement this if their content install will take a significant amount of time
- L147 _public function_ `virtual TArray<FBuildInstallerStat>& GetBundleUpdateStats(FName BundleName)` — Override to return information about a bundle installer
- L149 _public function_ `virtual void CheckForContentPatch(FInstallBundleSourceContentPatchResultDelegate Callback)`
- L152 _public function_ `virtual void SetErrorSimulationCommands(const FString& CommandLine)` — Called by bundle manager to pass through command line options to simulate errors
- L155 _public function_ `virtual void GetDebugText(TArray<FString>& Output)`
- L158 _public function_ `virtual bool SupportsReportingDelegate() const`
- L159 _public function_ `virtual void SetReportingDelegate(FInstallBundleReportingDelegate Delegate)`
- L161 _public function_ `virtual bool SupportsBundleRequestEventDelegates() const`
- L162 _public function_ `virtual void SetBundleRequestStartedDelegate(FInstallBundleRequestStartedDelegate Delegate)`
- L163 _public function_ `virtual void SetBundleRequestCompletedDelegate(FInstallBundleRequestCompletedDelegate Delegate)`
- L166 _public prototype_ `virtual void SetAnalyticsProvider(TSharedPtr<IAnalyticsProviderET> AnalyticsProvider) = 0;` — Called on the game thread whenever a new analytics provider is to be used than the one passed to Init()
- L169 _private member_ `TArray<FBuildInstallerStat> EmptyStats;`

#### struct `IInstallBundleSource::FRequestUpdateContentBundleContext`  
`struct FRequestUpdateContentBundleContext`  
_L84-93_
- L86 _public member_ `FName BundleName;`
- L87 _public member_ `EInstallBundleRequestFlags Flags = EInstallBundleRequestFlags::None;`
- L88 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L89 _public member_ `FInstallBundlePausedDelegate PausedCallback;`
- L90 _public member_ `FInstallBundleCompleteDelegate CompleteCallback;`
- L91 _public member_ `TSharedPtr<InstallBundleUtil::FContentRequestSharedContext> RequestSharedContext;`
- L92 _public member_ `void* StatsCookie = nullptr;`

#### struct `IInstallBundleSource::FRequestReleaseContentBundleContext`  
`struct FRequestReleaseContentBundleContext`  
_L99-105_
- L101 _public member_ `FName BundleName;`
- L102 _public member_ `EInstallBundleReleaseRequestFlags Flags = EInstallBundleReleaseRequestFlags::None;`
- L103 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L104 _public member_ `FInstallBundleRemovedDelegate CompleteCallback;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleSourceInitDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceAsyncInitInfo );`
- L12 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleSourceInitDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceAsyncInitInfo );`
- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleSourceQueryBundleInfoDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceBundleInfoQueryResult );`
- L14 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleSourceQueryBundleInfoDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceBundleInfoQueryResult );`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(EInstallBundleSourceUpdateBundleInfoResult, FInstallBundleSourceUpdateBundleInfoDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceUpdateBundleInfoResult );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(EInstallBundleSourceUpdateBundleInfoResult, FInstallBundleSourceUpdateBundleInfoDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceUpdateBundleInfoResult );`
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleLostRelevanceForSourceDelegate, TSharedRef<IInstallBundleSource> , TSet<FName> );`
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleLostRelevanceForSourceDelegate, TSharedRef<IInstallBundleSource> , TSet<FName> );`
- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleCompleteDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceUpdateContentResultInfo );`
- L18 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleCompleteDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceUpdateContentResultInfo );`
- L19 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundlePausedDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourcePauseInfo );`
- L19 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundlePausedDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourcePauseInfo );`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleRemovedDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceReleaseContentResultInfo );`
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleRemovedDelegate, TSharedRef<IInstallBundleSource> , FInstallBundleSourceReleaseContentResultInfo );`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FInstallBundleReportingDelegate, const FInstallBundleReport&);`
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FInstallBundleReportingDelegate, const FInstallBundleReport&);`
- L24 _delegate_ `DECLARE_DELEGATE_FourParams(FInstallBundleRequestStartedDelegate, const FName& , const FString& , const FString& , const FString& );`
- L24 _prototype_ `DECLARE_DELEGATE_FourParams(FInstallBundleRequestStartedDelegate, const FName& , const FString& , const FString& , const FString& );`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleRequestCompletedDelegate, const FName& , const FBundleRequestCompleteInfo& );`
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleRequestCompletedDelegate, const FName& , const FBundleRequestCompleteInfo& );`
- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FInstallBundleSourceContentPatchResultDelegate, TSharedRef<IInstallBundleSource> , bool );`
- L27 _prototype_ `DECLARE_DELEGATE_TwoParams(FInstallBundleSourceContentPatchResultDelegate, TSharedRef<IInstallBundleSource> , bool );`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleTypes.h` (Public)


#### enum `EInstallBundleSourceType`  
`enum class UE_DEPRECATED(5.5, "Use FInstallBundleSourceType") EInstallBundleSourceType : int`  
_L25-36_
- L27 _public enumerator_ `Bulk`
- L28 _public enumerator_ `Launcher`
- L29 _public enumerator_ `BuildPatchServices`
- L31 _public enumerator_ `Platform`
- L33 _public enumerator_ `GameCustom`
- L34 _public enumerator_ `Streaming`
- L35 _public enumerator_ `Count`

#### class `FInstallBundleSourceType`  
`class FInstallBundleSourceType`  
_L46-75_
- L49 _private member_ `FStringView NameStr;`
- L52 _public prototype_ `explicit FInstallBundleSourceType(FStringView InNameStr);`
- L55 _public prototype_ `FInstallBundleSourceType(EInstallBundleSourceType InLegacySourceType);`
- L58 _public function_ `FStringView GetName() const`
- L59 _public function_ `FString GetNameStr() const`
- L60 _public function_ `const TCHAR* GetNameCStr() const`
- L62 _public function_ `bool IsValid() const`
- L64 _public function_ `bool operator==(const FInstallBundleSourceType Other) const`

#### enum `EInstallBundleManagerInitState`  
`enum class EInstallBundleManagerInitState : int`  
_L78-83_
- L80 _public enumerator_ `NotInitialized`
- L81 _public enumerator_ `Failed`
- L82 _public enumerator_ `Succeeded`

#### enum `EInstallBundleManagerInitResult`  
`enum class EInstallBundleManagerInitResult : int`  
_L85-102_
- L87 _public enumerator_ `OK`
- L88 _public enumerator_ `BuildMetaDataNotFound`
- L89 _public enumerator_ `RemoteBuildMetaDataNotFound`
- L90 _public enumerator_ `BuildMetaDataDownloadError`
- L91 _public enumerator_ `BuildMetaDataParsingError`
- L92 _public enumerator_ `DistributionRootParseError`
- L93 _public enumerator_ `DistributionRootDownloadError`
- L94 _public enumerator_ `ManifestArchiveError`
- L95 _public enumerator_ `ManifestCreationError`
- L96 _public enumerator_ `ManifestDownloadError`
- L97 _public enumerator_ `BackgroundDownloadsIniDownloadError`
- L98 _public enumerator_ `NoInternetConnectionError`
- L99 _public enumerator_ `ConfigurationError`
- L100 _public enumerator_ `ClientPatchRequiredError`
- L101 _public enumerator_ `Count`

#### enum `EInstallBundleInstallState`  
`enum class EInstallBundleInstallState : int`  
_L105-111_
- L107 _public enumerator_ `NotInstalled`
- L108 _public enumerator_ `NeedsUpdate`
- L109 _public enumerator_ `UpToDate`
- L110 _public enumerator_ `Count`

#### struct `FInstallBundleCombinedInstallState`  
`struct FInstallBundleCombinedInstallState`  
_L114-122_
- L116 _public member_ `TMap<FName, EInstallBundleInstallState> IndividualBundleStates;`
- L117 _public member_ `TSet<FName> MountedBundles;`
- L118 _public member_ `TSet<FName> BundlesWithIoStoreOnDemand;`
- L120 _public prototype_ `bool GetAllBundlesHaveState(EInstallBundleInstallState State, TArrayView<const FName> ExcludedBundles = TArrayView<const FName>()) const;`
- L121 _public prototype_ `bool GetAnyBundleHasState(EInstallBundleInstallState State, TArrayView<const FName> ExcludedBundles = TArrayView<const FName>()) const;`

#### struct `FInstallBundleContentState`  
`struct FInstallBundleContentState`  
_L124-129_
- L126 _public member_ `EInstallBundleInstallState State = EInstallBundleInstallState::NotInstalled;`
- L127 _public member_ `float Weight = 0.0f;`
- L128 _public member_ `TMap<FInstallBundleSourceType, FString> Version;`

#### struct `FInstallBundleContentSize`  
`struct FInstallBundleContentSize`  
_L131-159_
- L134 _public member_ `uint64 DownloadSize = 0;` — Size remaining to download
- L136 _public member_ `uint64 SpaceRequiredForInstall = 0;` — Size needed to install the remaining download under GamePersistentDownloadDir
- L138 _public member_ `uint64 SpaceRequiredForInstallOtherDirs = 0;` — Size needed to install the remaining download under other directories than GamePersistentDownloadDir
- L140 _public member_ `uint64 CurrentSizeOnDisk = 0;` — size of bundle currently on disk under GamePersistentDownloadDir
- L142 _public member_ `uint64 CurrentSizeOnDiskOtherDirs = 0;` — size of bundle currently on disk under other directories than GamePersistentDownloadDir
- L144 _public function_ `FInstallBundleContentSize operator+(const FInstallBundleContentSize& Other) const`
- L154 _public function_ `FInstallBundleContentSize& operator+=(const FInstallBundleContentSize& Other)`

#### struct `FInstallBundleCombinedContentState`  
`struct FInstallBundleCombinedContentState`  
_L163-198_
- desc: TODO: Create a per-source version of this struct so that its clear what data bundle sources are responsible for populating.
- L166 _public prototype_ `FInstallBundleCombinedContentState() = default;`
- L167 _public prototype_ `FInstallBundleCombinedContentState(FInstallBundleCombinedContentState&&) = default;`
- L168 _public prototype_ `FInstallBundleCombinedContentState& operator=(FInstallBundleCombinedContentState&&) = default;`
- L169 _public prototype_ `FInstallBundleCombinedContentState(const FInstallBundleCombinedContentState&) = default;`
- L170 _public prototype_ `FInstallBundleCombinedContentState& operator=(const FInstallBundleCombinedContentState&) = default;`
- L171 _public prototype_ `~FInstallBundleCombinedContentState() = default;`
- L174 _public member_ `TMap<FName, FInstallBundleContentState> IndividualBundleStates;`
- L176 _public member_ `TSet<FName> BundlesWithIoStoreOnDemand;` — Bundle Sources don't need to populate this, bundle manager can determine it from init data
- L177 _public member_ `TMap<FInstallBundleSourceType, FString> CurrentVersion;`
- L181 _public member_ `uint64 DownloadSize = 0;` — `UE_DEPRECATED(5.6, "Please switch to using ContentSize")`
- L183 _public member_ `uint64 InstallSize = 0;` — `UE_DEPRECATED(5.6, "Please switch to using ContentSize")`
- L185 _public member_ `uint64 InstallOverheadSize = 0;` — `UE_DEPRECATED(5.6, "Please switch to using ContentSize")`
- L187 _public member_ `uint64 MaxDiskSpaceRequired = 0;` — `UE_DEPRECATED(5.6, "Please switch to using ContentSize")`
- L190 _public member_ `uint64 FreeSpace = 0;`
- L191 _public member_ `FInstallBundleContentSize ContentSize;`
- L194 _public member_ `TOptional<FInstallBundleContentSize> BackgroundDownloadContentSize;` — `UE_DEPRECATED(5.7, "Please switch to using ContentSize")`
- L196 _public prototype_ `bool GetAllBundlesHaveState(EInstallBundleInstallState State, TArrayView<const FName> ExcludedBundles = TArrayView<const FName>()) const;`
- L197 _public prototype_ `bool GetAnyBundleHasState(EInstallBundleInstallState State, TArrayView<const FName> ExcludedBundles = TArrayView<const FName>()) const;`

#### enum `EInstallBundleGetContentStateFlags`  
`enum class EInstallBundleGetContentStateFlags : uint32`  
_L200-205_
- L202 _public enumerator_ `None = 0`
- L203 _public enumerator_ `ForceNoPatching UE_DEPRECATED(5.7, "ForceNoPatching is no longer supported, use uninstall") = (1 << 0)`
- L204 _public enumerator_ `UpdateBundleReports = (1 << 1)` — will update the BundleReport for the involved bundles (see InstallBundleManagerReporting.h and IInstallBundleManager::ReportingDelegate)

#### enum `EInstallBundleRequestInfoFlags`  
`enum class EInstallBundleRequestInfoFlags : int32`  
_L210-222_
- L212 _public enumerator_ `None = 0`
- L213 _public enumerator_ `EnqueuedBundles = (1 << 0)`
- L214 _public enumerator_ `SkippedAlreadyMountedBundles = (1 << 1)`
- L215 _public enumerator_ `SkippedAlreadyUpdatedBundles = (1 << 2)` — Only possible with EInstallBundleRequestFlags::SkipMount
- L216 _public enumerator_ `SkippedAlreadyReleasedBundles = (1 << 3)`
- L217 _public enumerator_ `SkippedAlreadyRemovedBundles = (1 << 4)` — Only possible with EInstallBundleReleaseRequestFlags::RemoveFilesIfPossible
- L218 _public enumerator_ `SkippedUnknownBundles = (1 << 5)`
- L219 _public enumerator_ `SkippedInvalidBundles = (1 << 6)` — Bundle can't be used with this build
- L220 _public enumerator_ `SkippedUnusableLanguageBundles = (1 << 7)` — Can't enqueue language bundles because of current system settings
- L221 _public enumerator_ `SkippedBundlesDueToBundleSource = (1 << 8)` — A bundle source rejected a bundle for some reason

#### enum `EInstallBundleResult`  
`enum class EInstallBundleResult : uint32`  
_L225-240_
- L227 _public enumerator_ `OK`
- L228 _public enumerator_ `FailedPrereqRequiresLatestClient`
- L229 _public enumerator_ `FailedPrereqRequiresLatestContent`
- L230 _public enumerator_ `FailedCacheReserve`
- L231 _public enumerator_ `InstallError`
- L232 _public enumerator_ `InstallerOutOfDiskSpaceError`
- L233 _public enumerator_ `ManifestArchiveError`
- L234 _public enumerator_ `ConnectivityError`
- L235 _public enumerator_ `UserCancelledError`
- L236 _public enumerator_ `InitializationError`
- L237 _public enumerator_ `InitializationPending`
- L238 _public enumerator_ `MetadataError`
- L239 _public enumerator_ `Count`

#### enum `EInstallBundleRequestFlags`  
`enum class EInstallBundleRequestFlags : uint32`  
_L244-259_
- desc: TODO: Should probably be renamed to EInstallBundleRequestUpdateFlags
- L246 _public enumerator_ `None = 0`
- L247 _public enumerator_ `CheckForCellularDataUsage = (1 << 0)`
- L248 _public enumerator_ `UseBackgroundDownloads UE_DEPRECATED(5.7, "UseBackgroundDownloads is no longer supported, done automatically") = (1 << 1)`
- L249 _public enumerator_ `SendNotificationIfDownloadCompletesInBackground = (1 << 2)`
- L250 _public enumerator_ `ForceNoPatching UE_DEPRECATED(5.7, "ForceNoPatching is no longer supported, use uninstall") = (1 << 3)`
- L251 _public enumerator_ `TrackPersistentBundleStats = (1 << 4)`
- L252 _public enumerator_ `SkipMount = (1 << 5)`
- L253 _public enumerator_ `SkipOnDemandTocMount = (1 << 6)`
- L254 _public enumerator_ `AsyncMount = (1 << 7)`
- L255 _public enumerator_ `UpdateBundleReports = (1 << 8)` — will update the BundleReport for the involved bundles (see InstallBundleManagerReporting.h and IInstallBundleManager::ReportingDelegate)
- L256 _public enumerator_ `ExplicitUpdateList = (1 << 9)`
- L257 _public enumerator_ `CheckForLimitedDataUsage = (1 << 10)`
- L258 _public enumerator_ `Defaults = None`

#### enum `EInstallBundleReleaseResult`  
`enum class EInstallBundleReleaseResult : uint32`  
_L262-269_
- L264 _public enumerator_ `OK`
- L265 _public enumerator_ `ManifestArchiveError`
- L266 _public enumerator_ `UserCancelledError`
- L267 _public enumerator_ `MetadataError`
- L268 _public enumerator_ `Count`

#### enum `EInstallBundleReleaseRequestFlags`  
`enum class EInstallBundleReleaseRequestFlags : uint32`  
_L272-278_
- L274 _public enumerator_ `None = 0`
- L275 _public enumerator_ `RemoveFilesIfPossible = (1 << 0)` — Bundle sources must support removal, and bundle must not be part of the source's cache
- L276 _public enumerator_ `ExplicitRemoveList = (1 << 1)` — Only attempt to remove explicitly supplied bundles instead of automatically removing dependencies
- L277 _public enumerator_ `SkipReleaseUnmountOnly = (1 << 2)` — Unmount but leave content referenced. The inverse of EInstallBundleRequestFlags::SkipMount

#### enum `EInstallBundlePauseFlags`  
`enum class EInstallBundlePauseFlags : uint32`  
_L281-288_
- L283 _public enumerator_ `None = 0`
- L284 _public enumerator_ `OnCellularNetwork = (1 << 0)`
- L285 _public enumerator_ `NoInternetConnection = (1 << 1)`
- L286 _public enumerator_ `UserPaused = (1 << 2)`
- L287 _public enumerator_ `OnLimitedDataNetwork = (1 << 3)`

#### enum `EInstallBundleStatus`  
`enum class EInstallBundleStatus : int`  
_L291-298_
- L293 _public enumerator_ `Requested`
- L294 _public enumerator_ `Updating`
- L295 _public enumerator_ `Finishing`
- L296 _public enumerator_ `Ready`
- L297 _public enumerator_ `Count`

#### enum `EInstallBundleManagerPatchCheckResult`  
`enum class EInstallBundleManagerPatchCheckResult : uint32`  
_L301-314_
- L304 _public enumerator_ `NoPatchRequired` — No patch required
- L306 _public enumerator_ `ClientPatchRequired` — Client Patch required to continue
- L308 _public enumerator_ `ContentPatchRequired` — Content Patch required to continue
- L310 _public enumerator_ `NoLoggedInUser` — Logged in user required for a patch check
- L312 _public enumerator_ `PatchCheckFailure` — Patch check failed
- L313 _public enumerator_ `Count`

#### enum `EInstallBundlePriority`  
`enum class EInstallBundlePriority : uint8`  
_L321-327_
- desc: Enum used to describe download priority. Higher priorities will be downloaded first. Note: Should always be kept in High -> Low priority order if adding more Priorities!
- L323 _public enumerator_ `High`
- L324 _public enumerator_ `Normal`
- L325 _public enumerator_ `Low`
- L326 _public enumerator_ `Count`

#### struct `FInstallBundleSourceInitInfo`  
`struct FInstallBundleSourceInitInfo`  
_L331-335_
- L333 _public member_ `EInstallBundleManagerInitResult Result = EInstallBundleManagerInitResult::OK;`
- L334 _public member_ `bool bShouldUseFallbackSource = false;`

#### struct `FInstallBundleSourceAsyncInitInfo`  
`struct FInstallBundleSourceAsyncInitInfo : public FInstallBundleSourceInitInfo`  
_L337-340_
- inherits: `FInstallBundleSourceInitInfo`

#### struct `FInstallBundleSourceUpdateBundleInfo`  
`struct FInstallBundleSourceUpdateBundleInfo`  
_L343-354_
- desc: Bundle Info communicated from bundle source to bundle manager at any time
- L345 _public member_ `FName BundleName;`
- L346 _public member_ `FString BundleNameString;`
- L347 _public member_ `EInstallBundlePriority Priority = EInstallBundlePriority::Low;`
- L348 _public member_ `uint64 FullInstallSize = 0;` — Total disk footprint when this bundle is fully installed
- L349 _public member_ `uint64 InstallOverheadSize = 0;` — Any additional space required to complete installation
- L350 _public member_ `FDateTime LastAccessTime = FDateTime::MinValue();` — If cached, used to decide eviction order
- L351 _public member_ `EInstallBundleInstallState BundleContentState = EInstallBundleInstallState::NotInstalled;` — Whether this bundle is up to date
- L352 _public member_ `bool bIsCached = false;` — Whether this bundle should be cached if this source has a bundle cache
- L353 _public member_ `bool bContainsIoStoreOnDemandToc = false;` — Whether this bundle contains an an IoStoreOnDemand Toc

#### struct `FInstallBundleSourceUpdateBundleInfoResult`  
`struct FInstallBundleSourceUpdateBundleInfoResult`  
_L356-359_
- L358 _public member_ `TMap<FName, FInstallBundleSourceUpdateBundleInfo> SourceBundleInfoMap;`

#### struct `FInstallBundleSourcePersistentBundleInfo`  
`struct FInstallBundleSourcePersistentBundleInfo : FInstallBundleSourceUpdateBundleInfo`  
_L362-367_
- inherits: `FInstallBundleSourceUpdateBundleInfo`
- desc: Persisted Bundle Info communicated from bundle source to bundle manager on startup
- L364 _public member_ `uint64 CurrentInstallSize = 0;` — Disk footprint of the bundle in it's current state
- L365 _public member_ `bool bIsStartup = false;` — Only one startup bundle allowed.  All sources must agree on this.
- L366 _public member_ `bool bDoPatchCheck = false;` — This bundle should do a patch check and fail if it doesn't pas

#### struct `FInstallBundleSourceBundleInfoQueryResult`  
`struct FInstallBundleSourceBundleInfoQueryResult`  
_L369-372_
- L371 _public member_ `TMap<FName, FInstallBundleSourcePersistentBundleInfo> SourceBundleInfoMap;`

#### enum `EInstallBundleSourceUpdateBundleInfoResult`  
`enum class EInstallBundleSourceUpdateBundleInfoResult : uint8`  
_L374-382_
- L376 _public enumerator_ `OK`
- L377 _public enumerator_ `NotInitailized`
- L378 _public enumerator_ `AlreadyMounted`
- L379 _public enumerator_ `AlreadyRequested`
- L380 _public enumerator_ `IllegalCacheStatus`
- L381 _public enumerator_ `Count`

#### struct `FInstallBundleSourceUpdateContentResultInfo`  
`struct FInstallBundleSourceUpdateContentResultInfo`  
_L390-420_
- L392 _public prototype_ `FInstallBundleSourceUpdateContentResultInfo();`
- L393 _public prototype_ `FInstallBundleSourceUpdateContentResultInfo(const FInstallBundleSourceUpdateContentResultInfo&) = delete;`
- L394 _public prototype_ `FInstallBundleSourceUpdateContentResultInfo(FInstallBundleSourceUpdateContentResultInfo&&);`
- L395 _public prototype_ `~FInstallBundleSourceUpdateContentResultInfo();`
- L397 _public member_ `FName BundleName;`
- L398 _public member_ `EInstallBundleResult Result = EInstallBundleResult::OK;`
- L402 _public member_ `FText OptionalErrorText;` — Forward any errors from the underlying implementation for a specific source Currently, these just forward BPT Error info
- L403 _public member_ `FString OptionalErrorCode;`
- L405 _public member_ `TArray<FString> ContentPaths;`
- L406 _public member_ `TArray<FString> AdditionalRootDirs;`
- L408 _public member_ `TSet<FString> NonUFSShaderLibPaths;` — `UE_DEPRECATED(5.6, "All shader libs are now packaged and avialable via UFS")`
- L409 _public member_ `TArray<TUniquePtr<UE::IoStore::FOnDemandMountArgs>> OnDemandMountArgs;`
- L410 _public member_ `FPakMountOptions MountOptions;`
- L411 _public member_ `int32 PakOrder = INDEX_NONE;`
- L412 _public member_ `FString ProjectName;`
- L414 _public member_ `uint64 CurrentInstallSize = 0;`
- L415 _public member_ `FDateTime LastAccessTime = FDateTime::MinValue();` — If cached, used to decide eviction order
- L417 _public member_ `bool bContentWasInstalled = false;` — If true, the source did work to update the content
- L419 _public function_ `bool DidBundleSourceDoWork() const`

#### struct `FInstallBundleSourceReleaseContentResultInfo`  
`struct FInstallBundleSourceReleaseContentResultInfo`  
_L422-432_
- L424 _public member_ `FName BundleName;`
- L425 _public member_ `EInstallBundleReleaseResult Result = EInstallBundleReleaseResult::OK;`
- L427 _public member_ `FDateTime LastAccessTime = FDateTime::MinValue();` — If cached, used to decide eviction order
- L431 _public member_ `bool bContentWasRemoved = false;` — Indicates content was actually removed and bundle manager should consider this bundle as no longer installed.

#### struct `FBuildInstallerStat`  
`struct FBuildInstallerStat`  
_L435-440_
- desc: Useful to store any kind of information about the build installer
- L437 _public member_ `FName BundleName;` — To known which Bundle this stat was for even after all the stats are aggregated
- L438 _public member_ `FName StatName;`
- L439 _public member_ `TVariant<bool, int32, int64, float, double, FString> StatValue;`

#### struct `FInstallBundleSourceProgress`  
`struct FInstallBundleSourceProgress`  
_L442-451_
- L444 _public member_ `FName BundleName;`
- L446 _public member_ `float BackgroundDownload_Percent = 0;`
- L447 _public member_ `float InstallOnly_Percent = -1;` — -1 means the value is not valid and Install_Percent should be used instead
- L448 _public member_ `float Install_Percent = 0;` — Download and Install progress combined
- L450 _public member_ `TArray<FBuildInstallerStat> Stats;` — Used for additional information about the install

#### struct `FInstallBundleSourcePauseInfo`  
`struct FInstallBundleSourcePauseInfo`  
_L453-460_
- L455 _public member_ `FName BundleName;`
- L456 _public member_ `EInstallBundlePauseFlags PauseFlags = EInstallBundlePauseFlags::None;`
- L459 _public member_ `bool bDidPauseChange = false;` — True if the bundle actually transitioned to/from paused, which is different than the flags changing

#### enum `EInstallBundleSourceBundleSkipReason`  
`enum class EInstallBundleSourceBundleSkipReason : uint32`  
_L462-467_
- L464 _public enumerator_ `None = 0`
- L465 _public enumerator_ `LanguageNotCurrent = (1 << 0)` — The platform language must be changed to make it valid to request this bundle
- L466 _public enumerator_ `NotValid = (1 << 1)` — Bundle can't be used with this build

#### struct `FInstallBundleCacheBundleStats`  
`struct FInstallBundleCacheBundleStats`  
_L470-479_
- L472 _public member_ `FName BundleName;`
- L473 _public member_ `uint64 FullInstallSize = 0;`
- L474 _public member_ `uint64 InstallOverheadSize = 0;`
- L475 _public member_ `uint64 CurrentInstallSize = 0;`
- L476 _public member_ `FDateTime TimeStamp = FDateTime::MinValue();`
- L477 _public member_ `double AgeScalar = 1.0;`
- L478 _public member_ `bool bReserved = false;`

#### struct `FInstallBundleCacheStats`  
`struct FInstallBundleCacheStats`  
_L481-490_
- L483 _public member_ `FName CacheName;`
- L484 _public member_ `uint64 MaxSize = 0;`
- L485 _public member_ `uint64 UsedSize = 0;`
- L486 _public member_ `uint64 ReservedSize = 0;`
- L487 _public member_ `uint64 FreeSize = 0;`
- L489 _public member_ `TArray<FInstallBundleCacheBundleStats> BundleStats;` — EInstallBundleCacheStatsFlags::DumpToResults must be used to populate BundleStats

#### enum `EInstallBundleCacheStatsFlags`  
`enum class EInstallBundleCacheStatsFlags : uint8`  
_L492-498_
- L494 _public enumerator_ `None = 0`
- L495 _public enumerator_ `DumpToLog = (1 << 0)`
- L496 _public enumerator_ `CSVFormat = (1 << 1)`
- L497 _public enumerator_ `DumpToResults = (1 << 2)`

#### enum `EInstallBundleCacheDumpToLog`  
`enum class UE_DEPRECATED(5.7, "Use EInstallBundleCacheStatsFlags") EInstallBundleCacheDumpToLog : int8`  
_L501-506_
- L503 _public enumerator_ `None = 0`
- L504 _public enumerator_ `Default`
- L505 _public enumerator_ `CSV`

#### struct `FBundleDecompressionInfo`  
`struct FBundleDecompressionInfo`  
_L510-519_
- desc: TODO: These details shouldn't be in engine code. If you find yourself adding to this struct, please consider refactoring this to pass back a list of FAnalyticsEventAttribute's instead.
- L512 _public member_ `uint64 TotalCompressedBytes{};` — total amount of bytes in compressed files (incl headers)
- L513 _public member_ `uint64 TotalDecompressedBytes{};` — total amount of bytes in decompressed files (incl headers)
- L514 _public member_ `uint64 TotalActuallyReadBytes{};` — total amount of compressed bytes actually read this session (excl headers)
- L515 _public member_ `uint64 TotalActuallyWrittenBytes{};` — total amount of decompressed bytes actually written this session (excl headers)
- L516 _public member_ `double TotalDecompressionReadTime{};` — seconds spent reading compressed bytes this session
- L517 _public member_ `double TotalDecompressionDecompressTime{};` — seconds spent decompressing this session
- L518 _public member_ `double TotalDecompressionWriteTime{};` — seconds spent writing decompressed bytes this session

#### struct `FBundleRequestCompleteInfo`  
`struct FBundleRequestCompleteInfo`  
_L523-539_
- desc: TODO: These details shouldn't be in engine code. If you find yourself adding to this struct, please consider refactoring this to pass back a list of FAnalyticsEventAttribute's instead.
- L525 _public member_ `FString PreviousManifest;`
- L526 _public member_ `FString CurrentManifest;`
- L527 _public member_ `FString OldManifestVersion;`
- L528 _public member_ `FString InstallManifestVersion;`
- L529 _public member_ `FString OldVersionTimeStamp;`
- L530 _public member_ `uint64 TotalDownloadedBytes{};`
- L531 _public member_ `uint64 EstimatedFullDownloadBytes{};`
- L532 _public member_ `FString Result;`
- L533 _public member_ `FString BPTErrorCode;`
- L534 _public member_ `FString DownloadType;`
- L535 _public member_ `FBundleDecompressionInfo BundleDecompressionInfo;`
- L536 _public member_ `double AsyncStartupDelay{};`
- L537 _public member_ `double AsyncExitDelay{};`
- L538 _public member_ `bool AsyncPlacedInBackground{};`

#### Free symbols / members of external scopes

- L22 _macro_ `#define WITH_PLATFORM_INSTALL_BUNDLE_SOURCE 0`
- L38 _prototype_ `ENUM_RANGE_BY_COUNT(EInstallBundleSourceType, EInstallBundleSourceType::Count);`
- L40 _prototype_ `const TCHAR* LexToString(EInstallBundleSourceType Type);` — `UE_DEPRECATED(5.5, "Use FInstallBundleSourceType")`
- L42 _prototype_ `void LexFromString(EInstallBundleSourceType& OutType, const TCHAR* String);` — `UE_DEPRECATED(5.5, "Use FInstallBundleSourceType")`
- L70 _function_ `friend inline uint32 GetTypeHash(FInstallBundleSourceType In)`
- L76 _prototype_ `const TCHAR* LexToString(FInstallBundleSourceType Type);`
- L103 _prototype_ `const TCHAR* LexToString(EInstallBundleManagerInitResult Result);`
- L112 _prototype_ `const TCHAR* LexToString(EInstallBundleInstallState State);`
- L206 _prototype_ `ENUM_CLASS_FLAGS(EInstallBundleGetContentStateFlags);`
- L208 _delegate_ `DECLARE_DELEGATE_OneParam(FInstallBundleGetContentStateDelegate, FInstallBundleCombinedContentState);`
- L208 _prototype_ `DECLARE_DELEGATE_OneParam(FInstallBundleGetContentStateDelegate, FInstallBundleCombinedContentState);`
- L223 _prototype_ `ENUM_CLASS_FLAGS(EInstallBundleRequestInfoFlags);`
- L241 _prototype_ `const TCHAR* LexToString(EInstallBundleResult Result);`
- L270 _prototype_ `const TCHAR* LexToString(EInstallBundleReleaseResult Result);`
- L289 _prototype_ `ENUM_CLASS_FLAGS(EInstallBundlePauseFlags);`
- L299 _prototype_ `const TCHAR* LexToString(EInstallBundleStatus Status);`
- L315 _prototype_ `const TCHAR* LexToString(EInstallBundleManagerPatchCheckResult EnumVal);`
- L328 _prototype_ `const TCHAR* LexToString(EInstallBundlePriority Priority);`
- L329 _prototype_ `bool LexTryParseString(EInstallBundlePriority& OutMode, const TCHAR* InBuffer);`
- L383 _prototype_ `const TCHAR* LexToString(EInstallBundleSourceUpdateBundleInfoResult Result);`
- L385 _namespace_ `namespace UE`
- L385 _namespace_ `namespace IoStore` (scope `UE`)
- L468 _prototype_ `ENUM_CLASS_FLAGS(EInstallBundleSourceBundleSkipReason);`
- L499 _prototype_ `ENUM_CLASS_FLAGS(EInstallBundleCacheStatsFlags);`

### `Source/Runtime/InstallBundleManager/Public/InstallBundleUtils.h` (Public)


#### struct `InstallBundleUtil::FConfigMountOptions`  
`struct FConfigMountOptions`  
_L49-52_
- L51 _public member_ `bool bWithSoftReferences = false;`

#### class `InstallBundleUtil::FInstallBundleManagerKeepAwake`  
`class FInstallBundleManagerKeepAwake : public FEmbeddedKeepAwake`  
_L129-136_
- inherits: `FEmbeddedKeepAwake`
- desc: Keep the engine awake via RAII when running as an embedded app
- L131 _private member_ `static FName Tag;`
- L132 _private member_ `static FName TagWithRendering;`
- L134 _public function_ `FInstallBundleManagerKeepAwake(bool bNeedsRendering = false) : FEmbeddedKeepAwake(bNeedsRendering ? TagWithRendering : Tag, bNeedsRendering)`

#### class `InstallBundleUtil::FInstallBundleManagerScreenSaverControl`  
`class FInstallBundleManagerScreenSaverControl`  
_L138-169_
- L140 _private member_ `static bool bDidDisableScreensaver;`
- L141 _private member_ `static int DisableCount;`
- L143 _private prototype_ `static void IncDisable();`
- L144 _private prototype_ `static void DecDisable();`
- L147 _public function_ `FInstallBundleManagerScreenSaverControl()`
- L152 _public function_ `~FInstallBundleManagerScreenSaverControl()`
- L157 _public function_ `FInstallBundleManagerScreenSaverControl(const FInstallBundleManagerScreenSaverControl& Other)`
- L161 _public prototype_ `FInstallBundleManagerScreenSaverControl(FInstallBundleManagerScreenSaverControl&& Other) = default;`
- L163 _public prototype_ `FInstallBundleManagerScreenSaverControl& operator=(const FInstallBundleManagerScreenSaverControl& Other) = default;`
- L164 _public function_ `FInstallBundleManagerScreenSaverControl& operator=(FInstallBundleManagerScreenSaverControl&& Other)`

#### struct `InstallBundleUtil::FInstallBundleSuppressAnalytics`  
`struct FInstallBundleSuppressAnalytics : FNoncopyable`  
_L172-184_
- inherits: `FNoncopyable`
- desc: Helper to safely suppress installer analytics that will restore previous state when going out of scope
- L174 _public prototype_ `FInstallBundleSuppressAnalytics();`
- L175 _public prototype_ `~FInstallBundleSuppressAnalytics();`
- L177 _public prototype_ `void Enable();`
- L178 _public prototype_ `void Disable();`
- L180 _public prototype_ `static bool IsEnabled();`
- L183 _private member_ `bool bIsEnabled;`

#### class `InstallBundleUtil::FInstallBundleWork`  
`class FInstallBundleWork : public FNonAbandonableTask`  
_L186-220_
- inherits: `FNonAbandonableTask`
- L189 _public prototype_ `FInstallBundleWork() = default;`
- L191 _public function_ `FInstallBundleWork(TUniqueFunction<void()> InWork, TUniqueFunction<void()> InOnComplete) : WorkFunc(MoveTemp(InWork)) , OnCompleteFunc(MoveTemp(InOnComplete))`
- L196 _public function_ `void DoWork()`
- L204 _public function_ `void CallOnComplete()`
- L212 _public function_ `inline TStatId GetStatId() const`
- L218 _private member_ `TUniqueFunction<void()> WorkFunc;`
- L219 _private member_ `TUniqueFunction<void()> OnCompleteFunc;`

#### struct `InstallBundleUtil::FContentRequestStateStats`  
`struct FContentRequestStateStats`  
_L237-248_
- L239 _public member_ `double StartTime = 0.0;`
- L240 _public member_ `double EndTime = 0.0;`
- L241 _public member_ `uint64 DataSize = 0;`
- L242 _public member_ `bool bOpen = true;`
- L244 _public function_ `double GetElapsedTime() const`

#### struct `InstallBundleUtil::FContentRequestStats`  
`struct FContentRequestStats`  
_L250-261_
- L252 _public member_ `double StartTime = 0.0;`
- L253 _public member_ `double EndTime = 0.0;`
- L254 _public member_ `bool bOpen = true;`
- L255 _public member_ `TMap<FString, FContentRequestStateStats> StateStats;`
- L257 _public function_ `double GetElapsedTime() const`

#### class `InstallBundleUtil::FContentRequestStatsKey`  
`class FContentRequestStatsKey`  
_L263-286_
- L266 _private member_ `FName BundleName;`
- L267 _private member_ `void* Cookie = nullptr;`
- L270 _public function_ `FContentRequestStatsKey(FName InBundleName, void* InCookie) : BundleName(InBundleName), Cookie(InCookie)`
- L274 _public function_ `FName GetBundleName() const`
- L275 _public function_ `void* GetCookie() const`
- L277 _public function_ `[[nodiscard]] bool operator==(const FContentRequestStatsKey& Other) const`

#### class `InstallBundleUtil::FContentRequestStatsMap`  
`class FContentRequestStatsMap`  
_L288-323_
- L291 _private member_ `TMap<FContentRequestStatsKey, FContentRequestStats> StatsMap;`
- L294 _public prototype_ `void StatsBegin(const FContentRequestStatsKey& Key);`
- L295 _public prototype_ `void StatsEnd(const FContentRequestStatsKey& Key);`
- L296 _public prototype_ `void StatsBegin(const FContentRequestStatsKey& Key, const TCHAR* State);`
- L297 _public prototype_ `void StatsEnd(const FContentRequestStatsKey& Key, const TCHAR* State, uint64 DataSize = 0);`
- L298 _public prototype_ `void StatsReset(const FContentRequestStatsKey& Key);`
- L300 _public function_ `const FContentRequestStats* FindStats(const FContentRequestStatsKey& Key) const`
- L305 _public function_ `const FContentRequestStats& FindStatsChecked(const FContentRequestStatsKey& Key) const`
- L311 _public function_ `void StatsBegin(FName BundleName)` — `UE_DEPRECATED(5.7, "Use FContentRequestStatsKey version")`
- L313 _public function_ `void StatsEnd(FName BundleName)` — `UE_DEPRECATED(5.7, "Use FContentRequestStatsKey version")`
- L315 _public function_ `void StatsBegin(FName BundleName, const TCHAR* State)` — `UE_DEPRECATED(5.7, "Use FContentRequestStatsKey version")`
- L317 _public function_ `void StatsEnd(FName BundleName, const TCHAR* State, uint64 DataSize = 0)` — `UE_DEPRECATED(5.7, "Use FContentRequestStatsKey version")`
- L319 _public function_ `void StatsReset(FName BundleName)` — `UE_DEPRECATED(5.7, "Use FContentRequestStatsKey version")`
- L322 _public function_ `const TMap<FContentRequestStatsKey, FContentRequestStats>& GetMap()` — `UE_DEPRECATED(5.7, "Use FindStats and FindStatsChecked")`

#### enum `InstallBundleUtil::PersistentStats::ETimingStatNames`  
`enum class ETimingStatNames : uint8`  
_L332-347_
- desc: Stats used to store timing information in FPersistentTimerData format _Real stats account for total time since a stat was started regardless of the app's state (shutdown, in foreground, etc.) _FG stats account for time while the app is active _BG stats are an estimate of time while the app is inactive (backgrounded, closed, etc.) *_BG stats are an estimate as we can not account for unexpected crashes, etc.
- L334 _public enumerator_ `TotalTime_Real`
- L335 _public enumerator_ ``
- L336 _public enumerator_ ``
- L337 _public enumerator_ ``
- L338 _public enumerator_ ``
- L339 _public enumerator_ ``
- L340 _public enumerator_ ``
- L341 _public enumerator_ ``
- L342 _public enumerator_ ``
- L343 _public enumerator_ ``
- L344 _public enumerator_ ``
- L345 _public enumerator_ ``
- L346 _public enumerator_ `` — should always be final entry

#### enum `InstallBundleUtil::PersistentStats::ECountStatNames`  
`enum class ECountStatNames : uint8`  
_L350-356_
- desc: Stats used to store count information in an int format
- L352 _public enumerator_ `NumResumedFromBackground`
- L353 _public enumerator_ ``
- L354 _public enumerator_ ``
- L355 _public enumerator_ `` — should always be final entry

#### class `InstallBundleUtil::PersistentStats::FPersistentTimerData`  
`class FPersistentTimerData : public FJsonSerializable`  
_L375-391_
- inherits: `FJsonSerializable`
- L384 _public function_ `FPersistentTimerData() : LastUpdateTime(0.) , CurrentValue(0.)`
- L389 _public member_ `double LastUpdateTime;`
- L390 _public member_ `double CurrentValue;`

#### class `InstallBundleUtil::PersistentStats::FPersistentStatsBase`  
`class FPersistentStatsBase : public FJsonSerializable`  
_L395-486_
- inherits: `FJsonSerializable`
- desc: Both ContentRequests and Individual Bundles use this to track data respective to themselves. Keeps us from having to write serialization / loading data for both cases that would be the same
- L406 _public function_ `virtual ~FPersistentStatsBase()`
- L409 _public prototype_ `void StatsBegin(const FString& ExpectedAnalyticsID, bool bForceResetData = false);` — Tries to load persistent stats from disk and determine if we need to resume our previous persistent session or start a new one
- L413 _public prototype_ `void StatsEnd(bool bStopAllActiveTimers = true);` — Tries to set this stat pool as "inactive". By default also stop all active timers. NOTE: If you don't stop all active timers future calls to UpdateTimingStat will still increment this value and save it off!
- L415 _public prototype_ `bool IsTimingStatStarted(ETimingStatNames StatToUpdate) const;`
- L416 _public prototype_ `void StartTimingStat(ETimingStatNames StatToUpdate);`
- L417 _public prototype_ `void StopTimingStat(ETimingStatNames StatToUpdate, bool UpdateTimerOnStop = true);`
- L418 _public prototype_ `void UpdateTimingStat(ETimingStatNames StatToUpdate);`
- L420 _public prototype_ `void UpdateAllActiveTimers();`
- L421 _public prototype_ `void StopAllActiveTimers();`
- L423 _public function_ `bool IsActive() const`
- L424 _public function_ `bool IsDirty() const`
- L426 _public prototype_ `void IncrementCountStat(PersistentStats::ECountStatNames StatToUpdate);`
- L428 _public prototype_ `bool HasTimingStat(ETimingStatNames StatToCheck) const;`
- L429 _public prototype_ `bool HasCountStat(ECountStatNames StatToCheck) const;`
- L431 _public prototype_ `const FPersistentTimerData* GetTimingStatData(ETimingStatNames StatToGet) const;`
- L432 _public prototype_ `const int* GetCountStatData(ECountStatNames StatToGet) const;`
- L436 _public prototype_ `bool SaveStatsToDisk();` — Saves the persistent stat data to disk in the location returned by GetFullPathForStatFile() Returns True if that save succeeds and false otherwise.
- L440 _public prototype_ `bool LoadStatsFromDisk();` — Function that allows you to load stats from disk. Returns true if stats were either loaded from disk now, or previously were loaded from disk. NOTE: This does not begin stat collection, so you should still call StatsBegin on this before handling any stats!
- L443 _protected prototype_ `void ResetStats(const FString& NewAnalyticsSessionID);`
- L449 _protected prototype_ `void OnLoadingDataFromDisk();` — Called after we load data but before we process any of it. Useful for fixing up the data loaded from disk before it changes or is acted upon by anything else NOTE: A call to LoadStatsFromDisk will not necessarily call this! It will only be called when data is actually pulled from the disk, and its possible to skip pulling data from the disk!
- L452 _protected prototype_ `void HandleTimerStatsAfterDataLoad();` — Helper to try and reconcile offline and active timers after we load data from disk
- L455 _protected function_ `FPersistentStatsBase() : TimingStatsMap() , CountStatMap() , AnalyticsSessionID() , bIsActive(false) , bIsDirty(false) , bHasLoadedFromDisk(false)` — Protected so we can only construct the derived versions of this Base class
- L467 _protected member_ `TMap<FString, FPersistentTimerData> TimingStatsMap;` — Serialized Stat Data
- L468 _protected member_ `TMap<FString, int> CountStatMap;`
- L469 _protected member_ `FString AnalyticsSessionID;`
- L472 _protected member_ `bool bIsActive;` — We don't serialize these as they are tracking behavior and not stats
- L473 _protected member_ `bool bIsDirty;`
- L475 _protected member_ `bool bHasLoadedFromDisk;`
- L480 _public prototype_ `static const FString GetBaseExpectedAnalyticsID();` — Helper function that generates a basic ExpectedAnalyticsID from device and UE information
- L485 _public prototype_ `virtual const FString GetFullPathForStatFile() const = 0;` — Returns Full Path to look for our persistent stat cache

#### class `InstallBundleUtil::PersistentStats::FBundlePersistentStats`  
`class FBundlePersistentStats : public FPersistentStatsBase`  
_L489-518_
- inherits: `FPersistentStatsBase`
- desc: Each bundles persistent stats
- L502 _private prototype_ `FBundlePersistentStats() = delete;` — Remove default constructor as we require a BundleName in the constructor
- L505 _private member_ `FString BundleName;` — Used in our full path and should signify the FString version of the FName of this bundle we are tracking
- L508 _public function_ `FBundlePersistentStats(FName BundleNameIn) : BundleName(BundleNameIn.ToString())`
- L513 _public prototype_ `virtual ~FBundlePersistentStats() = default;`
- L517 _public prototype_ `virtual const FString GetFullPathForStatFile() const override;`

#### class `InstallBundleUtil::PersistentStats::FSessionPersistentStats`  
`class FSessionPersistentStats : public FPersistentStatsBase`  
_L521-564_
- inherits: `FPersistentStatsBase`
- desc: Tracks a set of bundles and stats for a named session. This way you can have stats across multiple bundle installs grouped by some naming convention
- L534 _private prototype_ `FSessionPersistentStats() = delete;` — Remove default constructor as we require a ContentRequestName in the constructor
- L537 _private member_ `FString SessionName;` — Used in our full path and should signify some identifier for a given ContentRequest
- L540 _private member_ `TArray<FString> RequiredBundles;` — Used to keep track of all bundles that are part of this content request
- L543 _public function_ `FSessionPersistentStats(const FString& ContentRequestNameIn) : SessionName(ContentRequestNameIn) , RequiredBundles()`
- L549 _public prototype_ `virtual ~FSessionPersistentStats() = default;`
- L551 _public prototype_ `void AddRequiredBundles(const TArray<FString>& RequiredBundlesToAdd);`
- L552 _public prototype_ `void AddRequiredBundles(const TArray<FName>& RequiredBundlesToAdd);`
- L556 _public prototype_ `void ResetRequiredBundles(const TArray<FString>& NewRequiredBundles = TArray<FString>());` — Removes all Required Bundle Names except the ones in the NewRequiredBundlesList. If no NewRequiredBundlesList is supplied, just erases all RequiredBundles. This includes ones loaded from the persistent cache from previous runs. This re-saves the persistent cache file so they will be removed completely.
- L559 _public prototype_ `void GetRequiredBundles(TArray<FString>& OutRequiredBundles) const;` — Populates the passed in TArray with all the required bundles' names
- L563 _public prototype_ `virtual const FString GetFullPathForStatFile() const override;`

#### class `InstallBundleUtil::PersistentStats::FPersistentStatContainerBase`  
`class FPersistentStatContainerBase`  
_L567-696_
- desc: Helper class to handle holding a collection of Bundle and Session stats.
- L570 _public prototype_ `FPersistentStatContainerBase();`
- L571 _public prototype_ `virtual ~FPersistentStatContainerBase();`
- L574 _public prototype_ `void InitializeBase();` — NOTE! These 2 functions are not virtual as we call them in the construct/deconstructor!
- L575 _public prototype_ `void ShutdownBase();`
- L580 _public prototype_ `virtual void StartBundlePersistentStatTracking(FName BundleName, const FString& ExpectedAnalyticsID = FString(), bool bForceResetStatData = false);` — Starts Bundle Persistent Stat Tracking for the given BundleName. Will automatically load applicable data from the disk and reset that cache if the ExpectedAnalyticsID doesn't match the one previously serialized. Uses FInstallBundleStatsContainerBase::GetBaseExpectedAnalyticsID if an ExpectedAnalyticsID is not passed in or empty
- L585 _public prototype_ `virtual void StartSessionPersistentStatTracking(const FString& SessionName, const TArray<FName>& RequiredBundles = TArray<FName>(), const FString& ExpectedAnalyticsID = FString(), bool bForceResetStatData = false);` — Starts Session Persistent Stat Tracking under the given SessionName. Will automatically load applicable data from the disk and reset that cache if the ExpectedAnalyticsID doesn't match the one previously serialized. Uses FInstallBundleStatsContainerBase::GetBaseExpectedAnalyticsID if an ExpectedAnalyticsID is not passed in or empty
- L587 _public prototype_ `virtual void StopBundlePersistentStatTracking(FName BundleName, bool bStopAllActiveTimers = true);`
- L588 _public prototype_ `virtual void StopSessionPersistentStatTracking(const FString& SessionName, bool bStopAllActiveTimers = true);`
- L590 _public prototype_ `virtual void StartBundlePersistentStatTimer(FName BundleName, ETimingStatNames TimerToStart);`
- L591 _public prototype_ `virtual void StartSessionPersistentStatTimer(const FString& SessionName, ETimingStatNames TimerToStart);`
- L593 _public prototype_ `virtual void StopBundlePersistentStatTimer(FName BundleName, ETimingStatNames TimerToStop);`
- L594 _public prototype_ `virtual void StopSessionPersistentStatTimer(const FString& SessionName, ETimingStatNames TimerToStop);`
- L596 _public prototype_ `virtual void UpdateBundlePersistentStatTimer(FName BundleName, ETimingStatNames TimerToUpdate);`
- L597 _public prototype_ `virtual void UpdateSessionPersistentStatTimer(const FString& SessionName, ETimingStatNames TimerToUpdate);`
- L599 _public prototype_ `virtual void IncrementBundlePersistentCounter(FName BundleName, ECountStatNames CounterToUpdate);`
- L600 _public prototype_ `virtual void IncrementSessionPersistentCounter(const FString& SessionName, ECountStatNames CounterToUpdate);`
- L602 _public prototype_ `virtual const FBundlePersistentStats* GetBundleStat(FName BundleName) const;`
- L603 _public prototype_ `virtual const FSessionPersistentStats* GetSessionStat(const FString& SessionName) const;`
- L605 _public prototype_ `virtual void SaveAllDirtyStatsToDisk();`
- L608 _public prototype_ `virtual void RemoveSessionStats(const FString& SessionName);` — Deletes persistent stat information from our stats for this Session/Bundle to reduce memory useage
- L609 _public prototype_ `virtual void RemoveBundleStats(FName BundleName);`
- L612 _protected prototype_ `virtual bool Tick(float dt);`
- L613 _protected prototype_ `virtual void ResetTimerUpdate();`
- L614 _protected prototype_ `virtual void ResetDirtyStatUpdate();`
- L616 _protected prototype_ `virtual void UpdateAllBundlesActiveTimers();`
- L617 _protected prototype_ `virtual void UpdateAllSessionActiveTimers();`
- L619 _protected prototype_ `virtual void OnApp_EnteringBackground();`
- L620 _protected prototype_ `virtual void OnApp_EnteringForeground();`
- L622 _protected prototype_ `virtual void OnBackground_HandleBundleStats();`
- L623 _protected prototype_ `virtual void OnForeground_HandleBundleStats();`
- L624 _protected prototype_ `virtual void OnBackground_HandleSessionStats();`
- L625 _protected prototype_ `virtual void OnForeground_HandleSessionStats();`
- L629 _protected prototype_ `virtual void OnTimerStartedForStat(FPersistentStatsBase& BundleStatForTimer, ETimingStatNames TimerStarted);` — Called whenever we start a timer NOTE: doesn't get called by timer's being Start/Stopped for bShouldAutoHandleFGBGStats
- L633 _protected prototype_ `virtual void OnTimerStoppedForStat(FPersistentStatsBase& BundleStatForTimer, ETimingStatNames TimerStarted);` — Called whenever we stop a timer NOTE: doesn't get called by timer's being Start/Stopped for bShouldAutoHandleFGBGStats
- L637 _protected prototype_ `virtual void UpdateStatsForBackground(FPersistentStatsBase& StatToUpdate);` — Stops active foreground timers when going to background and starts applicable background version Also increments background counters
- L641 _protected prototype_ `virtual void UpdateStatsForForeground(FPersistentStatsBase& StatToUpdate);` — Stops active background timers and resumes applicable foreground timers Also increments foreground counters
- L647 _protected prototype_ `virtual void LoadRequiredBundleDataFromDiskForSession(const FString& SessionName);` — Goes through this Session's RequiredBundles and loads data from disk for those bundles. Allows us to make sure we have full data in memory from disk without having to know the previous runs AnalyticsID to call StatsBegin on that bundle. NOTE: You should still call StatsBegin on the listed bundles before Starting/Incrementing/ETC any analytics! This just ensures that the previous run data exists for this given session!
- L650 _protected member_ `TMap<FName, FBundlePersistentStats> PerBundlePersistentStatMap;`
- L651 _protected member_ `TMap<FString, FSessionPersistentStats> SessionPersistentStatMap;`
- L653 _protected member_ `FTSTicker::FDelegateHandle TickHandle;`
- L654 _protected member_ `FDelegateHandle OnApp_EnteringForegroundHandle;`
- L655 _protected member_ `FDelegateHandle OnApp_EnteringBackgroundHandle;`
- L659 _protected member_ `float TimerAutoUpdateTimeRemaining;` — internal counter used to track when we need to run our timer update during tick. Requires bShouldAutoUpdateTimersInTick to be set to true to effect anything. reset to TimerAutoUpdateRate whenever we trigger the auto update.
- L663 _protected member_ `float TimerDirtyStatUpdateTimeRemaining;` — internal counter used to track when we need to update all of our dirty stats. Requires bShouldSaveDirtyStatsOnTick to be set to true to effect anything. reset to TimerAutoUpdateRate whenever we trigger the dirty stat update
- L677 _protected member_ `bool bShouldAutoUpdateTimersInTick;` — These settings determine if we auto-update our Timer stats on a tick. Without an auto-update timers would only update on Start / Stop potentially leaving us vulnerable to dropping a lot of timing information in the event of a crash. By setting these values you ensure your data is accurate to some interval. bShouldAutoUpdateTimersInTick -- Determines if the auto update feature is on at all. Rate of auto timer updates is determined by TimerAutoUpdateRate. TimerAutoUpdateRate -- Determines the rate we trigger the update in seconds. <=0 means update every tick.
- L678 _protected member_ `float TimerAutoUpdateRate;`
- L688 _protected member_ `bool bShouldSaveDirtyStatsOnTick;` — These settings determine how we handle saving our stats to disk. Outside of these settings, stats ALWAYS try to save to disk on Start or End, but these settings let us also configure other times we may want to save the data to disk. bShouldSaveDirtyStatsOnTick -- If this is set to true then all stats that have bIsDirty set to true will try to save to disk every X seconds. Update rate determined by DirtyStatSaveToDiskRate This way we will not update a given stat more then once a tick to disk. DirtyStatSaveToDiskRate -- Determines how often we update our dirty stats in seconds. <=0 means update every tick.
- L689 _protected member_ `float DirtyStatSaveToDiskRate;`
- L695 _protected member_ `bool bShouldAutoHandleFGBGStats;` — Determines if we should automatically Start,Stop,and Update the _FG and _BG versions of our timer stats. If true you only have to call Start/Stop on the _Real versions of all timers and we will automatically Start and Stop the _FG and _BG timers when going to background or returning to foreground to keep their data accurate.

#### struct `InstallBundleUtil::IBundleSourceContentRequestSharedContext`  
`struct IBundleSourceContentRequestSharedContext`  
_L699-702_
- L701 _public prototype_ `virtual ~IBundleSourceContentRequestSharedContext() = default;`

#### struct `InstallBundleUtil::FContentRequestSharedContext`  
`struct FContentRequestSharedContext`  
_L704-716_
- L706 _public prototype_ `FContentRequestSharedContext() = default;`
- L707 _public prototype_ `FContentRequestSharedContext(const FContentRequestSharedContext& Other) = delete;`
- L708 _public prototype_ `FContentRequestSharedContext(FContentRequestSharedContext&& Other) = default;`
- L709 _public prototype_ `FContentRequestSharedContext& operator=(const FContentRequestSharedContext& Other) = delete;`
- L710 _public prototype_ `FContentRequestSharedContext& operator=(FContentRequestSharedContext&& Other) = default;`
- L712 _public member_ `TMap<FInstallBundleSourceType, TUniquePtr<IBundleSourceContentRequestSharedContext>> BundleSourceSharedContext;`
- L715 _public member_ `TArray<FName> RequestedBundles;` — (Optional) - can be used to pass a list of requested bundles to IInstallBundleSource implementations

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace InstallBundleUtil`
- L32 _prototype_ `FString GetAppVersion();` (scope `InstallBundleUtil`) — Returns the app version in the same format as BPS versions
- L34 _prototype_ `bool HasInternetConnection(ENetworkConnectionType ConnectionType);` (scope `InstallBundleUtil`)
- L36 _prototype_ `bool SplitHostUrl(const FStringView Url, FStringView& OutHost, FStringView& OutRemainder);` (scope `InstallBundleUtil`)
- L38 _prototype_ `const TCHAR* GetInstallBundlePauseReason(EInstallBundlePauseFlags Flags);` (scope `InstallBundleUtil`)
- L40 _prototype_ `const FString& GetInstallBundleSectionPrefix();` (scope `InstallBundleUtil`)
- L42 _prototype_ `const FString& GetInstallBundleSubsetSectionPrefix();` (scope `InstallBundleUtil`)
- L44 _prototype_ `bool GetConfiguredBundleSources(TArray<FString>& OutSources, TMap<FString, FString>& OutFallbackSources);` (scope `InstallBundleUtil`)
- L47 _prototype_ `bool HasInstallBundleInConfig(const FString& BundleName);` (scope `InstallBundleUtil`) — returns true if the given BundleName exists in the InstallBundle.ini config
- L54 _prototype_ `bool GetMountOptionsFromConfig(const FStringView BundleName, FConfigMountOptions& OutMountOptions);` (scope `InstallBundleUtil`)
- L57 _prototype_ `bool AllInstallBundlePredicate(const FConfigFile& InstallBundleConfig, const FString& Section);` (scope `InstallBundleUtil`) — Returns true
- L60 _prototype_ `bool IsPlatformInstallBundlePredicate(const FConfigFile& InstallBundleConfig, const FString& Section);` (scope `InstallBundleUtil`) — Returns true if this bundle should be included in a platform package
- L64 _prototype_ `TArray<TPair<FString, TArray<FRegexPattern>>> LoadBundleRegexFromConfig( const FConfigFile& InstallBundleConfig, TFunctionRef<bool(const FConfigFile& InstallBundleConfig, const FString& Section)> SectionPredicate = AllInstallBundlePredicate);` (scope `InstallBundleUtil`) — Returns an ordered regex list used to map files to bundles SectionPredicate can be used to exclude non-relavent bundles from the list
- L69 _prototype_ `TArray<TPair<FString, TArray<FRegexPattern>>> LoadBundleSubsetRegexFromConfig( const FConfigFile& InstallBundleConfig);` (scope `InstallBundleUtil`) — Returns an ordered regex list used to map files to bundle subsets
- L73 _prototype_ `bool MatchBundleRegex( const TArray<TPair<FString, TArray<FRegexPattern>>>& BundleRegexList, const FString& Path, FString& OutBundleName);` (scope `InstallBundleUtil`) — Finds a matching install bundle for a given path
- L79 _prototype_ `bool MatchBundleSubsetRegex( const FString& BundleSubset, const TArray<TPair<FString, TArray<FRegexPattern>>>& BundleSubsetRegexList, const FString& Path);` (scope `InstallBundleUtil`) — Return true for a matching install bundle subset for a given path
- L84 _variable_ `constexpr float MinimumBundleWeight = 0.05f;` (scope `InstallBundleUtil`)
- L88 _function_ `template<class EnumType> constexpr auto& CastAsUnderlying(EnumType &Type)` (scope `InstallBundleUtil`) — It would really be nice to have these in core
- L91 _typedef_ `using UnderType = std::underlying_type_t<EnumType>;` (scope `InstallBundleUtil::CastAsUnderlying`)
- L96 _function_ `template<class EnumType> constexpr const auto& CastAsUnderlying(const EnumType &Type)` (scope `InstallBundleUtil`)
- L104 _function_ `template<class EnumType> constexpr auto CastToUnderlying(EnumType Type)` (scope `InstallBundleUtil`)
- L107 _typedef_ `using UnderType = std::underlying_type_t<EnumType>;` (scope `InstallBundleUtil::CastToUnderlying`)
- L112 _function_ `template<typename EnumType, typename StringArrType, EnumType EnumCount = EnumType::Count> const TCHAR* TLexToString(EnumType E, const StringArrType& Strings)` (scope `InstallBundleUtil`)
- L222 _typedef_ `using FInstallBundleTask = FAsyncTask<FInstallBundleWork>;` (scope `InstallBundleUtil`)
- L223 _typedef_ `using FAutoDeleteInstallBundleTask = FAutoDeleteAsyncTask<FInstallBundleWork>;` (scope `InstallBundleUtil`)
- L225 _prototype_ `void StartInstallBundleAsyncIOTask(TUniqueFunction<void()> WorkFunc);` (scope `InstallBundleUtil`)
- L227 _prototype_ `void StartInstallBundleAsyncIOTask(FQueuedThreadPool* ThreadPool, TUniqueFunction<void()> WorkFunc);` (scope `InstallBundleUtil`)
- L229 _prototype_ `void StartInstallBundleAsyncIOTask(TArray<TUniquePtr<FInstallBundleTask>>& Tasks, TUniqueFunction<void()> WorkFunc, TUniqueFunction<void()> OnComplete);` (scope `InstallBundleUtil`)
- L231 _prototype_ `void StartInstallBundleAsyncIOTask(FQueuedThreadPool* ThreadPool, TArray<TUniquePtr<FInstallBundleTask>>& Tasks, TUniqueFunction<void()> WorkFunc, TUniqueFunction<void()> OnComplete);` (scope `InstallBundleUtil`)
- L233 _prototype_ `void FinishInstallBundleAsyncIOTasks(TArray<TUniquePtr<FInstallBundleTask>>& Tasks);` (scope `InstallBundleUtil`)
- L235 _prototype_ `void CleanupInstallBundleAsyncIOTasks(TArray<TUniquePtr<FInstallBundleTask>>& Tasks);` (scope `InstallBundleUtil`)
- L282 _function_ `[[nodiscard]] friend uint32 GetTypeHash(const FContentRequestStatsKey& Key)` (scope `InstallBundleUtil`)
- L325 _namespace_ `namespace PersistentStats` (scope `InstallBundleUtil`)
- L358 _prototype_ `const FString& LexToString(ETimingStatNames InType);` (scope `InstallBundleUtil::PersistentStats`)
- L359 _prototype_ `const FString& LexToString(ECountStatNames InType);` (scope `InstallBundleUtil::PersistentStats`)
- L362 _prototype_ `bool IsTimerReal(ETimingStatNames InTimer);` (scope `InstallBundleUtil::PersistentStats`) — Returns if the timer is in the _Real set
- L364 _prototype_ `bool IsTimerFG(ETimingStatNames InTimer);` (scope `InstallBundleUtil::PersistentStats`) — Returns if the timer is in the _FG set
- L366 _prototype_ `bool IsTimerBG(ETimingStatNames InTimer);` (scope `InstallBundleUtil::PersistentStats`) — Returns if the timer is in the _BG set
- L369 _prototype_ `ETimingStatNames GetAssociatedRealTimerName(ETimingStatNames InTimerType);` (scope `InstallBundleUtil::PersistentStats`) — Gets the _Real timer when supplied with the corresponding _FG or _BG timer name
- L371 _prototype_ `ETimingStatNames GetAssociatedFGTimerName(ETimingStatNames InTimerType);` (scope `InstallBundleUtil::PersistentStats`) — Gets the _FG timer when supplied with the corresponding _Real or _BG timer name
- L373 _prototype_ `ETimingStatNames GetAssociatedBGTimerName(ETimingStatNames InTimerType);` (scope `InstallBundleUtil::PersistentStats`) — Gets the _BG timer when supplied with the corresponding _Real or _FG timer name
- L717 _typedef_ `using FContentRequestSharedContextPtr = TSharedPtr<FContentRequestSharedContext>;` (scope `InstallBundleUtil`)
