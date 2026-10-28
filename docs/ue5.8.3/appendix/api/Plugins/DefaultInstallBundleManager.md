# Plugins / DefaultInstallBundleManager

- module root: `Plugins/Experimental/DefaultInstallBundleManager/Source`
- headers: 7; symbols: 690
- symbol kinds: class=11, delegate=1, enum=12, enumerator=53, function=42, macro=9, member=232, namespace=6, prototype=274, struct=18, typedef=32
- PrivateDependencyModuleNames: AnalyticsET, ApplicationCore, Core, IoStoreOnDemandCore, Json, PakFile, PlatformDLC, RenderCore
- PublicDependencyModuleNames: InstallBundleManager, PatchCheck

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Private/DefaultInstallBundleManagerPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define LOG_INSTALL_BUNDLE_MAN(Verbosity, Format, ...) UE_LOG(LogDefaultInstallBundleManager, Verbosity, Format, ##__VA_ARGS__)`
- L11 _macro_ `#define LOG_INSTALL_BUNDLE_MAN_OVERRIDE(InVerbosityOverride, Verbosity, Format, ...) \`

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Public/DefaultInstallBundleManager.h` (Public)


#### class `FDefaultInstallBundleManager`  
`class FDefaultInstallBundleManager : public IInstallBundleManager`  
_L27-846_
- inherits: `IInstallBundleManager`
- L41 _protected typedef_ `using EContentRequestBatch = FContentRequestBatchNS::Enum;`
- L55 _protected typedef_ `using EContentReleaseRequestBatch = FContentReleaseRequestBatchNS::Enum;`
- L79 _protected function_ `bool StateSignifiesNeedsInstall(EBundleState StateIn)`
- L220 _protected prototype_ `EBundleState GetBundleStatus(const FBundleInfo& BundleInfo) const;` — GetBundleStatus protects erroneous accesses of the bundle status before initialization is complete by throwing an assert
- L221 _protected prototype_ `void SetBundleStatus(FBundleInfo& BundleInfo, EBundleState InBundleState);`
- L222 _protected prototype_ `bool GetMustWaitForPSOCache(const FBundleInfo& BundleInfo) const;`
- L223 _protected prototype_ `uint32 GetInitialShaderPrecompiles(const FBundleInfo& BundleInfo) const;`
- L224 _protected prototype_ `void SetMustWaitForPSOCache(FBundleInfo& BundleInfo, uint32 InNumPSOPrecompilesRemaining);`
- L261 _protected typedef_ `using FGetContentStateRequestRef = TSharedRef<FGetContentStateRequest>;`
- L262 _protected typedef_ `using FGetContentStateRequestPtr = TSharedPtr<FGetContentStateRequest>;`
- L294 _protected typedef_ `using FGetInstallStateRequestRef = TSharedRef<FGetInstallStateRequest>;`
- L295 _protected typedef_ `using FGetInstallStateRequestPtr = TSharedPtr<FGetInstallStateRequest>;`
- L347 _protected typedef_ `using FCacheEvictionRequestorRef = TSharedRef<FCacheEvictionRequestor>;`
- L348 _protected typedef_ `using FCacheEvictionRequestorPtr = TSharedPtr<FCacheEvictionRequestor>;`
- L349 _protected typedef_ `using FCacheEvictionRequestorWeakPtr = TWeakPtr<FCacheEvictionRequestor>;`
- L376 _protected typedef_ `using FCacheFlushRequestRef = TSharedRef<FCacheFlushRequest>;`
- L377 _protected typedef_ `using FCacheFlushRequestPtr = TSharedPtr<FCacheFlushRequest>;`
- L378 _protected typedef_ `using FCacheFlushRequestWeakPtr = TWeakPtr<FCacheFlushRequest>;`
- L439 _protected typedef_ `using FContentRequestRef = TSharedRef<FContentRequest>;`
- L440 _protected typedef_ `using FContentRequestPtr = TSharedPtr<FContentRequest>;`
- L441 _protected typedef_ `using FContentRequestWeakPtr = TWeakPtr<FContentRequest>;`
- L489 _protected typedef_ `using FContentReleaseRequestRef = TSharedRef<FContentReleaseRequest>;`
- L490 _protected typedef_ `using FContentReleaseRequestPtr = TSharedPtr<FContentReleaseRequest>;`
- L491 _protected typedef_ `using FContentReleaseRequestWeakPtr = TWeakPtr<FContentReleaseRequest>;`
- L497 _protected typedef_ `using FContentPatchCheckSharedContextRef = TSharedRef<FContentPatchCheckSharedContext>;`
- L500 _public typedef_ `typedef TUniqueFunction<TSharedPtr<IInstallBundleSource>(FInstallBundleSourceType)> FInstallBundleSourceFactoryFunction;`
- L503 _public function_ `FDefaultInstallBundleManager(const TCHAR* InConfigBaseName, FInstallBundleSourceFactoryFunction InBundleSourceFactory = nullptr) : FDefaultInstallBundleManager(MoveTemp(InBundleSourceFactory))` — `UE_DEPRECATED(5.4, "GInstallBundleManagerIni is deprecated, use InstallBundle.ini hierarchy instead.")`
- L507 _public prototype_ `FDefaultInstallBundleManager(FInstallBundleSourceFactoryFunction InBundleSourceFactory = nullptr);`
- L508 _public prototype_ `FDefaultInstallBundleManager(const FDefaultInstallBundleManager& Other) = delete;`
- L509 _public prototype_ `FDefaultInstallBundleManager& operator=(const FDefaultInstallBundleManager& Other) = delete;`
- L511 _public prototype_ `virtual ~FDefaultInstallBundleManager();`
- L513 _public prototype_ `virtual void Initialize() override;`
- L517 _protected prototype_ `bool Tick(float dt);`
- L519 _protected prototype_ `EInstallBundleManagerInitErrorHandlerResult HandleAsyncInitError(EInstallBundleManagerInitResult InitResultError);`
- L521 _protected prototype_ `void TickInit();`
- L523 _protected prototype_ `void TickGetContentState();`
- L525 _protected prototype_ `void TickGetInstallState();`
- L527 _protected prototype_ `FInstallBundleCombinedInstallState GetInstallStateInternal(TArrayView<const FName> BundleNames) const;`
- L529 _protected prototype_ `void CacheHintRequested(FContentRequestRef Request, bool bRequested);`
- L531 _protected prototype_ `void CheckPrereqHasNoPendingCancels(FContentRequestRef Request);`
- L533 _protected prototype_ `void CheckPrereqHasNoPendingCancels(FContentReleaseRequestRef Request);`
- L535 _protected prototype_ `void CheckPrereqHasNoPendingReleaseRequests(FContentRequestRef Request);`
- L537 _protected prototype_ `void CheckPrereqHasNoPendingUpdateRequests(FContentReleaseRequestRef Request);`
- L539 _protected prototype_ `void CheckPrereqLatestClient(FContentRequestRef Request);`
- L541 _protected prototype_ `void HandlePatchInformationReceived(EInstallBundleManagerPatchCheckResult Result, FContentRequestRef Request);`
- L543 _protected prototype_ `void DetermineSteps(FContentRequestRef Request);`
- L545 _protected prototype_ `void DetermineSteps(FContentReleaseRequestRef Request);`
- L547 _protected prototype_ `void AddRequestToInitialBatch(FContentRequestRef Request);`
- L549 _protected prototype_ `void AddRequestToInitialBatch(FContentReleaseRequestRef Request);`
- L551 _protected prototype_ `void ReserveCache(FContentRequestRef Request);`
- L553 _protected prototype_ `void TryReserveCache(FContentRequestRef Request);`
- L555 _protected prototype_ `void RequestEviction(FCacheEvictionRequestorRef Requestor);`
- L557 _protected prototype_ `void CacheEvictionComplete(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourceReleaseContentResultInfo InResultInfo);`
- L558 _protected prototype_ `void CacheEvictionComplete(TSharedRef<IInstallBundleSource> Source, const FInstallBundleSourceReleaseContentResultInfo& InResultInfo, FCacheEvictionRequestorRef Requestor);`
- L560 _protected prototype_ `void UpdateBundleSources(FContentRequestRef Request);`
- L562 _protected prototype_ `void UpdateBundleSourceComplete(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourceUpdateContentResultInfo InResultInfo, FContentRequestRef Request);`
- L564 _protected prototype_ `void UpdateBundleSourcePause(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourcePauseInfo InPauseInfo, FContentRequestRef Request);`
- L566 _protected prototype_ `void UpdateBundleSources(FContentReleaseRequestRef Request);`
- L568 _protected prototype_ `void UpdateBundleSourceReleaseComplete(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourceReleaseContentResultInfo InResultInfo, FContentReleaseRequestRef Request);`
- L570 _protected prototype_ `void MountPaks(FContentRequestRef Request);`
- L572 _protected prototype_ `static bool MountPaksInList(TArrayView<TPair<FString, FPakMountOptions>> Paths, TValueOrError<void, UE::UnifiedError::FError>& OutResult, ELogVerbosity::Type LogVerbosityOverride, const int32 PakOrder = INDEX_NONE);`
- L574 _protected prototype_ `void UnmountPaks(FContentReleaseRequestRef Request);`
- L576 _protected prototype_ `virtual bool AllowIoStoreOnDemandMount(FContentRequestRef Request, const FBundleInfo& BundleInfo);`
- L578 _protected prototype_ `virtual TArray<TPair<FString, FPakMountOptions>> GetPakMountList(FContentRequestRef Request, const FBundleInfo& BundleInfo);`
- L580 _protected function_ `virtual void OnPaksMountingInternal(FContentRequestRef Request, FBundleInfo& BundleInfo)`
- L581 _protected function_ `virtual void OnPaksMountedInternal(FContentRequestRef Request, FBundleInfo& BundleInfo)`
- L582 _protected function_ `virtual void OnPaksUnmountedInternal(FContentReleaseRequestRef Request, FBundleInfo& BundleInfo)`
- L584 _protected prototype_ `void WaitForShaderCache(FContentRequestRef Request);`
- L586 _protected prototype_ `void FinishRequest(FContentRequestRef Request);`
- L588 _protected prototype_ `void FinishRequest(FContentReleaseRequestRef Request);`
- L590 _protected prototype_ `void TickUpdatePrereqs();`
- L592 _protected prototype_ `void TickReleasePrereqs();`
- L594 _protected prototype_ `void TickContentRequests();`
- L596 _protected prototype_ `void TickReserveCache();`
- L598 _protected prototype_ `void TickCacheFlush();`
- L600 _protected prototype_ `void TickWaitForShaderCache();`
- L602 _protected prototype_ `void TickPauseStatus(bool bForceCallback);`
- L604 _protected prototype_ `void TickAsyncIOTasks();`
- L606 _protected prototype_ `void TickReleaseRequests();`
- L608 _protected prototype_ `void TickPruneBundleInfo();`
- L610 _protected prototype_ `bool TickReporting(float dt);`
- L612 _protected prototype_ `void IterateContentRequests(TFunctionRef<bool(const FContentRequestRef& QueuedRequest)> OnFound);`
- L613 _protected prototype_ `void IterateReleaseRequests(TFunctionRef<bool(const FContentReleaseRequestRef& QueuedRequest)> OnFound);`
- L615 _protected prototype_ `void IterateContentRequestsForBundle(FName BundleName, TFunctionRef<bool(const FContentRequestRef& QueuedRequest)> OnFound);`
- L616 _protected prototype_ `void IterateReleaseRequestsForBundle(FName BundleName, TFunctionRef<bool(const FContentReleaseRequestRef& QueuedRequest)> OnFound);`
- L618 _protected prototype_ `TSet<FName> GetBundleDependencies(FName InBundleName, bool* bSkippedUnknownBundles = nullptr) const;`
- L620 _protected prototype_ `TSet<FName> GetBundleDependencies(TArrayView<const FName> InBundleNames, bool* bSkippedUnknownBundles = nullptr) const;`
- L622 _protected prototype_ `TSet<FName> GatherBundlesForRequest(TArrayView<const FName> InBundleNames, EInstallBundleRequestInfoFlags& OutFlags);`
- L624 _protected prototype_ `TSet<FName> GatherBundlesForRequest(TArrayView<const FName> InBundleNames);`
- L626 _protected prototype_ `FInstallBundleSourceType GetBundleSourceFallback(FInstallBundleSourceType Type) const;`
- L628 _protected prototype_ `EInstallBundleSourceUpdateBundleInfoResult OnUpdateBundleInfoFromSource(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourceUpdateBundleInfoResult Result);`
- L629 _protected prototype_ `void OnBundleLostRelevanceForSource(TSharedRef<IInstallBundleSource> Source, TSet<FName> BundleNames);`
- L631 _protected prototype_ `void StartClientPatchCheck();`
- L632 _protected prototype_ `void StartContentPatchCheck();`
- L633 _protected prototype_ `void HandleClientPatchCheck(EPatchCheckResult Result);`
- L634 _protected prototype_ `void HandleBundleSourceContentPatchCheck(TSharedRef<IInstallBundleSource> Source, bool bContentPatchRequired, FContentPatchCheckSharedContextRef Context);`
- L635 _protected prototype_ `void HandleContentPatchCheck(FContentPatchCheckSharedContextRef Context);`
- L637 _protected prototype_ `bool CancelUpdateContentInternal(TArrayView<const FName> BundleNames);`
- L638 _protected prototype_ `bool CancelReleaseContentInternal(TArrayView<const FName> BundleNames);`
- L640 _protected prototype_ `void OnChunkDownloadMetrics(FInstallBundleChunkDownloadInfo ChunkDownloadInfo);`
- L644 _public prototype_ `virtual bool HasBundleSource(FInstallBundleSourceType SourceType) const override;`
- L646 _public prototype_ `virtual const TSharedPtr<IInstallBundleSource> GetBundleSource(FInstallBundleSourceType SourceType) const override;`
- L648 _public prototype_ `virtual void SetContext(FName ContextName) override;`
- L649 _public prototype_ `virtual bool CopyReportTo(FInstallManagerBundleReport& Report) override;`
- L651 _public prototype_ `virtual FDelegateHandle PushInitErrorCallback(FInstallBundleManagerInitErrorHandler Callback) override;`
- L652 _public prototype_ `virtual void PopInitErrorCallback() override;`
- L653 _public prototype_ `virtual void PopInitErrorCallback(FDelegateHandle Handle) override;`
- L654 _public prototype_ `virtual void PopInitErrorCallback(FDelegateUserObjectConst InUserObject) override;`
- L656 _public prototype_ `virtual EInstallBundleManagerInitState GetInitState() const override;`
- L658 _public prototype_ `virtual TValueOrError<FInstallBundleRequestInfo, EInstallBundleResult> RequestUpdateContent(TArrayView<const FName> InBundleNames, EInstallBundleRequestFlags Flags, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging, InstallBundleUtil::FContentRequestSharedContextPtr RequestSharedContext = nullptr) override;`
- L660 _public prototype_ `virtual FDelegateHandle GetContentState(TArrayView<const FName> InBundleNames, EInstallBundleGetContentStateFlags Flags, bool bAddDependencies, FInstallBundleGetContentStateDelegate Callback, FName RequestTag = TEXT("None")) overr`
- L662 _public prototype_ `virtual void CancelAllGetContentStateRequestsForTag(FName RequestTag) override;`
- L663 _public prototype_ `virtual void CancelAllGetContentStateRequests(FDelegateHandle Handle) override;`
- L665 _public prototype_ `virtual FDelegateHandle GetInstallState(TArrayView<const FName> BundleNames, bool bAddDependencies, FInstallBundleGetInstallStateDelegate Callback, FName RequestTag = NAME_None) override;`
- L667 _public prototype_ `virtual TValueOrError<FInstallBundleCombinedInstallState, EInstallBundleResult> GetInstallStateSynchronous(TArrayView<const FName> BundleNames, bool bAddDependencies) const override;`
- L668 _public prototype_ `virtual EInstallBundleResult GetAllMountedBundles(TArray<FName>& OutBundleNames) const override;`
- L669 _public prototype_ `virtual EInstallBundleResult GetAllBundlesWithState(EInstallBundleInstallState InstallState, TArray<FName>& OutBundleNames) const override;`
- L671 _public prototype_ `virtual void CancelAllGetInstallStateRequestsForTag(FName RequestTag) override;`
- L672 _public prototype_ `virtual void CancelAllGetInstallStateRequests(FDelegateHandle Handle) override;`
- L674 _public prototype_ `virtual TValueOrError<FInstallBundleReleaseRequestInfo, EInstallBundleResult> RequestReleaseContent(TArrayView<const FName> ReleaseNames, EInstallBundleReleaseRequestFlags Flags, TArrayView<const FName> KeepNames = TArrayView<const FName>(), ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) override;`
- L676 _public prototype_ `virtual EInstallBundleResult FlushCache(FInstallBundleSourceOrCache SourceOrCache, FInstallBundleManagerFlushCacheCompleteDelegate Callback, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) override;`
- L678 _public prototype_ `virtual TArray<FInstallBundleCacheStats> GetCacheStats(EInstallBundleCacheStatsFlags Flags = EInstallBundleCacheStatsFlags::None, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) override;`
- L679 _public prototype_ `virtual TOptional<FInstallBundleCacheStats> GetCacheStats(FInstallBundleSourceOrCache SourceOrCache, EInstallBundleCacheStatsFlags Flags = EInstallBundleCacheStatsFlags::None, ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging) override;`
- L681 _public prototype_ `virtual void RequestRemoveContentOnNextInit(TArrayView<const FName> RemoveNames, TArrayView<const FName> KeepNames = TArrayView<const FName>()) override;`
- L683 _public prototype_ `virtual void CancelRequestRemoveContentOnNextInit(TArrayView<const FName> BundleName) override;`
- L685 _public prototype_ `virtual TArray<FName> GetRequestedRemoveContentOnNextInit() const override;`
- L687 _public prototype_ `virtual void CancelUpdateContent(TArrayView<const FName> BundleNames) override;`
- L689 _public prototype_ `virtual void PauseUpdateContent(TArrayView<const FName> BundleNames) override;`
- L691 _public prototype_ `virtual void ResumeUpdateContent(TArrayView<const FName> BundleNames) override;`
- L693 _public prototype_ `virtual void RequestPausedBundleCallback() override;`
- L695 _public prototype_ `virtual TOptional<FInstallBundleProgress> GetBundleProgress(FName BundleName) const override;`
- L697 _public prototype_ `virtual EInstallBundleRequestFlags GetModifyableContentRequestFlags() const override;`
- L698 _public prototype_ `virtual void UpdateContentRequestFlags(TArrayView<const FName> BundleNames, EInstallBundleRequestFlags AddFlags, EInstallBundleRequestFlags RemoveFlags) override;`
- L699 _public prototype_ `virtual void SetCellularPreference(int32 Value) override;`
- L700 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) override;`
- L702 _public prototype_ `virtual void SetCacheSize(FName CacheName, uint64 CacheSize) override;`
- L704 _public prototype_ `virtual void StartPatchCheck() override;`
- L705 _public prototype_ `virtual void AddEnvironmentWantsPatchCheckBackCompatDelegate(FName Tag, FInstallBundleManagerEnvironmentWantsPatchCheck Delegate) override;`
- L706 _public prototype_ `virtual void RemoveEnvironmentWantsPatchCheckBackCompatDelegate(FName Tag) override;`
- L707 _public prototype_ `virtual bool SupportsEarlyStartupPatching() const override;`
- L709 _public prototype_ `virtual bool IsNullInterface() const override;`
- L711 _public prototype_ `virtual void SetErrorSimulationCommands(const FString& CommandLine) override;`
- L714 _public prototype_ `void SetCommandLineOverrides(const FString& CommandLine);` — For overrides that we need to handle even when in a shipping build
- L716 _public prototype_ `virtual TSharedPtr<IAnalyticsProviderET> GetAnalyticsProvider() const override;`
- L718 _public prototype_ `virtual void StartSessionPersistentStatTracking(const FString& SessionName, const TArray<FName>& RequiredBundles = TArray<FName>(), const FString& ExpectedAnalyticsID = FString(), bool bForceResetStatData = false, const FInstallBundleCombinedContentState* State = nullptr) override;`
- L719 _public prototype_ `virtual void StopSessionPersistentStatTracking(const FString& SessionName) override;`
- L722 _public prototype_ `virtual void GetDebugText(TArray<FString>& Output) override;`
- L725 _public function_ `virtual bool HasEverUpdatedContent() const`
- L729 _protected prototype_ `void StartBundlePersistentStatTracking(TSharedRef<FContentRequest> ContentRequest, const FString& ExpectedAnalyticsID = FString(), bool bForceResetStatData = false);` — Special version of these to wrap our calls to PersistentStats
- L730 _protected prototype_ `void StopBundlePersistentStatTracking(TSharedRef<FContentRequest> ContentRequest);`
- L731 _protected prototype_ `void PersistentTimingStatsBegin(TSharedRef<FContentRequest> ContentRequest, InstallBundleUtil::PersistentStats::ETimingStatNames TimerStatName);`
- L732 _protected prototype_ `void PersistentTimingStatsEnd(TSharedRef<FContentRequest> ContentRequest, InstallBundleUtil::PersistentStats::ETimingStatNames TimerStatName);`
- L734 _protected prototype_ `TArray<TSharedPtr<IInstallBundleSource>> GetEnabledBundleSourcesForRequest(FContentRequestRef Request) const;`
- L735 _protected prototype_ `virtual TArray<TSharedPtr<IInstallBundleSource>> GetEnabledBundleSourcesForRequest(const FBundleInfo& BundleInfo) const;`
- L739 _protected prototype_ `EInstallBundleManagerInitResult Init_DefaultBundleSources();`
- L740 _protected prototype_ `EInstallBundleManagerInitResult Init_TryCreateBundleSources(TArray<FInstallBundleSourceType> SourcesToCreate, TArray<TSharedPtr<IInstallBundleSource>>* OutNewSources = nullptr);`
- L742 _protected prototype_ `FInstallBundleSourceType FindFallbackSource(FInstallBundleSourceType SourceType);`
- L743 _protected prototype_ `void AsyncInit_InitBundleSources();`
- L744 _protected prototype_ `void AsyncInit_OnBundleSourceInitComplete(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourceAsyncInitInfo InInitInfo);`
- L745 _protected prototype_ `void AsyncInit_InitBundleCaches();`
- L746 _protected prototype_ `void AsyncInit_InitPersistentReportCache();`
- L747 _protected prototype_ `void AsyncInit_QueryBundleInfo();`
- L748 _protected prototype_ `void AsyncInit_OnQueryBundleInfoComplete(TSharedRef<IInstallBundleSource> Source, FInstallBundleSourceBundleInfoQueryResult Result);`
- L749 _protected prototype_ `void AsyncInit_OnQueryBundleInfoComplete_HandleClientPatchCheck(EPatchCheckResult Result);`
- L750 _protected prototype_ `void AsyncInit_SetUpdateBundleInfoCallback();`
- L751 _protected prototype_ `void AsyncInit_CreateAnalyticsSession();`
- L752 _protected prototype_ `void AsyncInit_FireInitAnlaytic(bool bCanRetry);`
- L754 _protected prototype_ `void StatsBegin(const InstallBundleUtil::FContentRequestStatsKey& Key);`
- L755 _protected prototype_ `void StatsEnd(const InstallBundleUtil::FContentRequestStatsKey& Key);`
- L756 _protected prototype_ `void StatsBegin(const InstallBundleUtil::FContentRequestStatsKey& Key, EContentRequestState State);`
- L757 _protected prototype_ `void StatsEnd(const InstallBundleUtil::FContentRequestStatsKey& Key, EContentRequestState State, uint64 DataSize = 0);`
- L758 _protected prototype_ `void LogStats(const InstallBundleUtil::FContentRequestStatsKey& Key, ELogVerbosity::Type LogVerbosityOverride);`
- L761 _protected member_ `FTSTicker::FDelegateHandle TickHandle;`
- L762 _protected member_ `FTSTicker::FDelegateHandle ReportingHandle;`
- L763 _protected member_ `FDelegateHandle AsyncInit_PatchCheckHandle;`
- L764 _protected member_ `FDelegateHandle PatchCheckHandle;`
- L765 _protected member_ `UE::IoStore::IOnDemandIoStore* OnDemandIoStore = nullptr;`
- L766 _protected member_ `FInstallBundleSourceFactoryFunction InstallBundleSourceFactory;`
- L768 _protected member_ `TMap<FName, FBundleInfo> BundleInfoMap;`
- L769 _protected member_ `TSet<FName> BundlesInfosToPrune;`
- L771 _protected member_ `TMap<FInstallBundleSourceType, TSharedPtr<IInstallBundleSource>> BundleSources;`
- L772 _protected member_ `TMap<FInstallBundleSourceType, FInstallBundleSourceType> BundleSourceFallbacks;`
- L774 _protected member_ `TMap<FName, TSharedRef<FInstallBundleCache>> BundleCaches;`
- L775 _protected member_ `TMap<FInstallBundleSourceType, FName> BundleSourceCaches;`
- L776 _protected member_ `TMap<FName, uint64> BundleCacheSizeOverrides;`
- L778 _protected member_ `TMap<TTuple<FInstallBundleSourceType, FName>, TArray<FCacheEvictionRequestorRef>> PendingCacheEvictions;` — (Source, Bundle) -> List of requestors
- L779 _protected member_ `TMap<TTuple<FName, FName>, TArray<FInstallBundleSourceType>> CachesPendingEvictToSources;` — (Cache, Bundle) -> List of Sources
- L782 _protected member_ `TMap<FInstallBundleSourceType, TOptional<FInstallBundleSourceAsyncInitInfo>> BundleSourceInitResults;` — Only used during Init
- L783 _protected member_ `TMap<FInstallBundleSourceType, FInstallBundleSourceBundleInfoQueryResult> BundleSourceBundleInfoQueryResults;`
- L786 _protected member_ `EInstallBundleManagerInitState InitState = EInstallBundleManagerInitState::NotInitialized;` — Init
- L787 _protected member_ `EInstallBundleManagerInitResult InitResult = EInstallBundleManagerInitResult::OK;`
- L788 _protected member_ `TArray<FInstallBundleManagerInitErrorHandler> InitErrorHandlerStack;`
- L789 _protected member_ `TArray<TSharedPtr<IInstallBundleSource>> BundleSourcesToDelete;`
- L790 _protected member_ `EAsyncInitStep InitStep = EAsyncInitStep::None;`
- L791 _protected member_ `EAsyncInitStep LastInitStep = EAsyncInitStep::None;`
- L792 _protected member_ `EAsyncInitStepResult InitStepResult = EAsyncInitStepResult::Done;`
- L793 _protected member_ `bool bUnrecoverableInitError = false;`
- L794 _protected member_ `bool bIsCurrentlyInAsyncInit = false;`
- L795 _protected member_ `double LastInitRetryTimeSeconds = 0.0;`
- L796 _protected member_ `double InitRetryTimeDeltaSeconds = 0.0;`
- L799 _protected member_ `TArray<FGetContentStateRequestRef> GetContentStateRequests;` — Content State Requests
- L800 _protected member_ `TArray<FGetInstallStateRequestRef> GetInstallStateRequests;`
- L803 _protected member_ `TArray<FContentRequestRef> ContentRequests[EContentRequestBatch::Count];` — Content Requests
- L806 _protected member_ `TArray<FContentReleaseRequestRef> ContentReleaseRequests[EContentReleaseRequestBatch::Count];` — Content Release Requests
- L809 _protected member_ `TArray<FCacheFlushRequestRef> CacheFlushRequests;` — Cache Flush Requests
- L811 _protected member_ `TSharedRef<InstallBundleManagerUtil::FPersistentStatContainer> PersistentStats;`
- L813 _protected member_ `TArray<TUniquePtr<InstallBundleUtil::FInstallBundleTask>> AsyncIOTasks;`
- L815 _protected member_ `bool bIsCheckingForPatch = false;`
- L816 _protected member_ `bool bDelayCheckingForContentPatch = false;`
- L820 _protected member_ `bool bSimulateClientNotLatest = false;` — Error Simulation
- L821 _protected member_ `bool bSimulateContentNotLatest = false;`
- L826 _protected member_ `bool bOverrideCommand_SkipPatchCheck = false;` — Not included in INSTALL_BUNDLE_ALLOW_ERROR_SIMULATION as we want to provide this functionality even on ship builds
- L828 _protected member_ `bool bHasEverUpdatedContent = false;`
- L831 _protected member_ `bool bPersistentStateDirty = false;` — Persistent update state
- L832 _protected member_ `FName ContextName;`
- L833 _protected member_ `FInstallManagerBundleReport PersistentState;`
- L834 _protected member_ `FInstallManagerBundleReportCache PersistentStateCache;` — must be declared after AsyncIOTasks
- L838 _protected member_ `TSharedPtr<IAnalyticsProviderET> AnalyticsProvider;` — Analytics
- L839 _protected member_ `TSharedRef<InstallBundleUtil::FContentRequestStatsMap> StatsMap;`
- L840 _protected member_ `TMap<FName, FBundleRequestCompleteInfo> BundleRequestCompleteInfoMap;` — BundleName as key
- L841 _protected member_ `TMap<FName, TArray<FInstallBundleChunkDownloadInfo> > ChunkDownloadInfoMap;` — BundleName as key
- L845 _protected prototype_ `void SetAnalyticsProvider(TSharedPtr<IAnalyticsProviderET> NewAnalyticsProvider);` — Only to be called on the game thread, updates already initialized bundles with the new analytics provider, and sets the new provider internally.

#### struct `FDefaultInstallBundleManager::FContentRequestBatchNS`  
`struct FContentRequestBatchNS`  
_L31-40_
- desc: Strongly Typed enums do not work well for this thing's use case

#### enum `FDefaultInstallBundleManager::FContentRequestBatchNS::Enum`  
`enum Enum : int`  
_L33-39_
- L35 _public enumerator_ `Requested`
- L36 _public enumerator_ `Cache`
- L37 _public enumerator_ `Install`
- L38 _public enumerator_ `Count`

#### struct `FDefaultInstallBundleManager::FContentReleaseRequestBatchNS`  
`struct FContentReleaseRequestBatchNS`  
_L46-54_
- desc: Strongly Typed enums do not work well for this thing's use case

#### enum `FDefaultInstallBundleManager::FContentReleaseRequestBatchNS::Enum`  
`enum Enum : int`  
_L48-53_
- L50 _public enumerator_ `Requested`
- L51 _public enumerator_ `Release`
- L52 _public enumerator_ `Count`

#### enum `FDefaultInstallBundleManager::EBundleState`  
`enum class EBundleState : int`  
_L59-66_
- L61 _public enumerator_ `NotInstalled`
- L62 _public enumerator_ `NeedsUpdate`
- L63 _public enumerator_ `NeedsMount`
- L64 _public enumerator_ `Mounted`
- L65 _public enumerator_ `Count`

#### enum `FDefaultInstallBundleManager::EAsyncInitStep`  
`enum class EAsyncInitStep : int`  
_L84-95_
- L86 _public enumerator_ `None`
- L87 _public enumerator_ `InitBundleSources`
- L88 _public enumerator_ `InitBundleCaches`
- L89 _public enumerator_ `InitPersisentReportCache`
- L90 _public enumerator_ `QueryBundleInfo`
- L91 _public enumerator_ `SetUpdateBundleInfoCallback`
- L92 _public enumerator_ `CreateAnalyticsSession`
- L93 _public enumerator_ `Finishing`
- L94 _public enumerator_ `Count`

#### enum `FDefaultInstallBundleManager::EAsyncInitStepResult`  
`enum class EAsyncInitStepResult : int`  
_L114-118_
- L116 _public enumerator_ `Waiting`
- L117 _public enumerator_ `Done`

#### enum `FDefaultInstallBundleManager::EBundlePrereqs`  
`enum class EBundlePrereqs : int`  
_L120-129_
- L122 _public enumerator_ `CacheHintRequested`
- L123 _public enumerator_ `RequiresLatestClient`
- L124 _public enumerator_ `HasNoPendingCancels`
- L125 _public enumerator_ `HasNoPendingReleaseRequests`
- L126 _public enumerator_ `HasNoPendingUpdateRequests`
- L127 _public enumerator_ `DetermineSteps`
- L128 _public enumerator_ `Count`

#### struct `FDefaultInstallBundleManager::FBundleSourceRelevance`  
`struct FBundleSourceRelevance`  
_L146-152_
- L148 _public member_ `FInstallBundleSourceType SourceType;`
- L149 _public member_ `bool bIsRelevant = true;`
- L151 _public function_ `bool operator==(const FBundleSourceRelevance& Other) const`

#### struct `FDefaultInstallBundleManager::FBundleContentPaths`  
`struct FBundleContentPaths`  
_L154-161_
- L156 _public member_ `TArray<TPair<FString, FPakMountOptions>> ContentPaths;`
- L157 _public member_ `TArray<FString> AdditionalRootDirs;`
- L158 _public member_ `FString ProjectName;`
- L159 _public member_ `int32 PakOrder = INDEX_NONE;`
- L160 _public member_ `bool bContainsChunks = false;`

#### struct `FDefaultInstallBundleManager::FBundleInfo`  
`struct FBundleInfo`  
_L164-217_
- L167 _public function_ `EBundleState GetBundleStatus(const FDefaultInstallBundleManager& BundleMan) const`
- L173 _public function_ `void SetBundleStatus(const FDefaultInstallBundleManager& BundleMan, EBundleState InBundleState)`
- L179 _public function_ `bool GetMustWaitForPSOCache(const FDefaultInstallBundleManager& BundleMan) const`
- L185 _public function_ `uint32 GetInitialShaderPrecompiles(const FDefaultInstallBundleManager& BundleMan) const`
- L191 _public function_ `void SetMustWaitForPSOCache(const FDefaultInstallBundleManager& BundleMan, uint32 InNumPSOPrecompilesRemaining)`
- L202 _private member_ `EBundleState BundleStatus = EBundleState::NotInstalled;`
- L203 _private member_ `uint32 InitialShaderPrecompiles = 0;`
- L205 _public member_ `FString BundleNameString;` — Since FNames do not preserve casing
- L206 _public member_ `TArray<EBundlePrereqs> Prereqs;`
- L207 _public member_ `TArray<FBundleSourceRelevance> ContributingSources;` — Sources contributing to this bundle info
- L208 _public member_ `FBundleContentPaths ContentPaths;` — Only valid if BundleStatus >= NeedsMount
- L209 _public member_ `EInstallBundlePriority Priority = EInstallBundlePriority::Low;`
- L211 _private member_ `bool bWaitForPSOCache = false;`
- L213 _public member_ `bool bReleaseRequired = false;` — A bundle source may have done install work so expects a release call
- L214 _public member_ `bool bIsStartup = false;`
- L215 _public member_ `bool bContainsIoStoreOnDemandTocs = false;`
- L216 _public member_ `bool bMountedOnDemandTocs = false;`

#### struct `FDefaultInstallBundleManager::FGetContentStateRequest`  
`struct FGetContentStateRequest`  
_L226-260_
- L228 _public member_ `TMap<FInstallBundleSourceType, FInstallBundleCombinedContentState> BundleSourceContentStates;`
- L230 _public member_ `TArray<FName> BundleNames;`
- L232 _public member_ `EInstallBundleGetContentStateFlags Flags = EInstallBundleGetContentStateFlags::None;`
- L234 _public member_ `bool Started = false;`
- L235 _public member_ `bool bCancelled = false;`
- L238 _public member_ `FName RequestTag;` — Used to track an individual request so that it can be canceled
- L240 _public function_ `void SetCallback(FInstallBundleGetContentStateDelegate NewCallback)`
- L245 _public function_ `void ExecCallbackIfValid(FInstallBundleCombinedContentState BundleState)`
- L253 _public function_ `const FDelegateHandle GetCallbackDelegateHandle()`
- L259 _private member_ `FInstallBundleGetContentStateDelegate Callback;`

#### struct `FDefaultInstallBundleManager::FGetInstallStateRequest`  
`struct FGetInstallStateRequest`  
_L264-293_
- L266 _public member_ `TArray<FName> BundleNames;`
- L268 _public member_ `bool bCancelled = false;`
- L271 _public member_ `FName RequestTag;` — Used to track an individual request so that it can be canceled
- L273 _public function_ `void SetCallback(FInstallBundleGetInstallStateDelegate NewCallback)`
- L278 _public function_ `void ExecCallbackIfValid(FInstallBundleCombinedInstallState BundleState)`
- L286 _public function_ `const FDelegateHandle GetCallbackDelegateHandle()`
- L292 _private member_ `FInstallBundleGetInstallStateDelegate Callback;`

#### enum `FDefaultInstallBundleManager::EContentRequestStepResult`  
`enum class EContentRequestStepResult : int`  
_L297-301_
- L299 _public enumerator_ `Waiting`
- L300 _public enumerator_ `Done`

#### enum `FDefaultInstallBundleManager::EContentRequestState`  
`enum class EContentRequestState : int`  
_L303-313_
- L305 _public enumerator_ `ReservingCache`
- L306 _public enumerator_ `FinishingCache`
- L307 _public enumerator_ `UpdatingBundleSources`
- L308 _public enumerator_ `Mounting`
- L309 _public enumerator_ `WaitingForShaderCache`
- L310 _public enumerator_ `Finishing`
- L311 _public enumerator_ `CleaningUp`
- L312 _public enumerator_ `Count`

#### enum `FDefaultInstallBundleManager::ECacheEvictionRequestorType`  
`enum class ECacheEvictionRequestorType : int`  
_L331-335_
- L333 _public enumerator_ `CacheFlush`
- L334 _public enumerator_ `ContentRequest`

#### struct `FDefaultInstallBundleManager::FCacheEvictionRequestor`  
`struct FCacheEvictionRequestor`  
_L337-346_
- L339 _public member_ `TMap<FName, TArray<FInstallBundleSourceType>> BundlesToEvictFromSourcesMap;`
- L341 _public prototype_ `virtual ~FCacheEvictionRequestor() = default;`
- L343 _public prototype_ `virtual FString GetEvictionRequestorName() const = 0;`
- L344 _public prototype_ `virtual ECacheEvictionRequestorType GetEvictionRequestorType() const = 0;`
- L345 _public prototype_ `virtual ELogVerbosity::Type GetLogVerbosityOverride() const = 0;`

#### struct `FDefaultInstallBundleManager::FCacheFlushRequest`  
`struct FCacheFlushRequest : FCacheEvictionRequestor`  
_L351-375_
- inherits: `FCacheEvictionRequestor`
- L353 _public member_ `FInstallBundleSourceOrCache SourceOrCache;` — Bundles are evicted from all caches, but we gather them from only this one if set
- L354 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L356 _public member_ `FInstallBundleManagerFlushCacheCompleteDelegate Callback;`
- L358 _public function_ `virtual FString GetEvictionRequestorName() const override`
- L373 _public function_ `virtual ECacheEvictionRequestorType GetEvictionRequestorType() const override`
- L374 _public function_ `virtual ELogVerbosity::Type GetLogVerbosityOverride() const override`

#### struct `FDefaultInstallBundleManager::FContentRequest`  
`struct FContentRequest : FCacheEvictionRequestor`  
_L380-438_
- inherits: `FCacheEvictionRequestor`
- L382 _public prototype_ `~FContentRequest();`
- L384 _public member_ `int32 iStep = INDEX_NONE;`
- L385 _public member_ `EContentRequestStepResult StepResult = EContentRequestStepResult::Done;`
- L386 _public member_ `TArray<EContentRequestState> Steps;`
- L387 _public member_ `TStaticArray<int32, EContentRequestBatch::Count> iOnCanceledStep{ InPlace, INDEX_NONE };`
- L389 _public member_ `int32 iPrereq = INDEX_NONE;`
- L390 _public member_ `TArray<EBundlePrereqs> Prereqs;`
- L391 _public member_ `FDelegateHandle CheckLastestClientDelegateHandle;`
- L393 _public member_ `EInstallBundleRequestFlags Flags = EInstallBundleRequestFlags::None;`
- L395 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L397 _public member_ `bool bShouldSendAnalytics = true;`
- L398 _public member_ `bool bIsCanceled = false;`
- L399 _public member_ `bool bFinishWhenCanceled = true;` — Whether to run cleanup and callback when canceled
- L400 _public member_ `bool bDidCacheHintRequested = false;` — Whether this request hinted to the bundle caches that the bundle was requested
- L401 _public member_ `bool bContentWasInstalled = false;`
- L402 _public member_ `FName BundleName;`
- L404 _public member_ `EInstallBundleResult Result = EInstallBundleResult::OK;`
- L406 _public member_ `EInstallBundlePauseFlags LastSentPauseFlags = EInstallBundlePauseFlags::None;`
- L407 _public member_ `TMap<FInstallBundleSourceType, EInstallBundlePauseFlags> SourcePauseFlags;`
- L408 _public member_ `bool bForcePauseCallback = false;`
- L410 _public member_ `EInstallBundleCacheReserveResult LastCacheReserveResult = EInstallBundleCacheReserveResult::Success;`
- L413 _public member_ `int RequiredSourceRequestResultsCount = 0;` — how many results we are expected to have in the SourceRequestResults array
- L415 _public member_ `TMap<FInstallBundleSourceType, FInstallBundleSourceUpdateContentResultInfo> SourceRequestResults;` — completion results from each bundle source
- L417 _public member_ `TArray<TUniquePtr<UE::IoStore::FOnDemandMountArgs>> OnDemandMountArgs;`
- L419 _public member_ `FText OptionalErrorText;`
- L420 _public member_ `FString OptionalErrorCode;`
- L422 _public member_ `TMap<FInstallBundleSourceType, FInstallBundleSourceProgress> CachedSourceProgress;`
- L424 _public member_ `InstallBundleUtil::FContentRequestSharedContextPtr RequestSharedContext;`
- L427 _public member_ `TOptional<InstallBundleUtil::FInstallBundleManagerKeepAwake> KeepAwake;` — If needed, Keep the engine awake while process requests
- L430 _public member_ `TOptional<InstallBundleUtil::FInstallBundleManagerScreenSaverControl> ScreenSaveControl;` — If needed, Banish screen savers
- L432 _public function_ `virtual FString GetEvictionRequestorName() const override`
- L433 _public function_ `virtual ECacheEvictionRequestorType GetEvictionRequestorType() const override`
- L434 _public function_ `virtual ELogVerbosity::Type GetLogVerbosityOverride() const override`
- L436 _public function_ `void* GetStatsCookie() const`
- L437 _public function_ `InstallBundleUtil::FContentRequestStatsKey GetStatsKey() const`

#### enum `FDefaultInstallBundleManager::EContentReleaseRequestState`  
`enum class EContentReleaseRequestState : int`  
_L443-450_
- L445 _public enumerator_ `Unmounting`
- L446 _public enumerator_ `UpdatingBundleSources`
- L447 _public enumerator_ `Finishing`
- L448 _public enumerator_ `CleaningUp`
- L449 _public enumerator_ `Count`

#### struct `FDefaultInstallBundleManager::FContentReleaseRequest`  
`struct FContentReleaseRequest`  
_L465-488_
- L467 _public member_ `EContentRequestStepResult StepResult = EContentRequestStepResult::Done;`
- L468 _public member_ `TArray<EContentReleaseRequestState> Steps;`
- L469 _public member_ `int32 iStep = INDEX_NONE;`
- L470 _public member_ `TStaticArray<int32, EContentReleaseRequestBatch::Count> iOnCanceledStep{ InPlace, INDEX_NONE };`
- L472 _public member_ `TArray<EBundlePrereqs> Prereqs;`
- L473 _public member_ `int32 iPrereq = INDEX_NONE;`
- L475 _public member_ `EInstallBundleReleaseRequestFlags Flags = EInstallBundleReleaseRequestFlags::None;`
- L477 _public member_ `EInstallBundleReleaseResult Result = EInstallBundleReleaseResult::OK;`
- L479 _public member_ `FName BundleName;`
- L481 _public member_ `TMap<FInstallBundleSourceType, TOptional<FInstallBundleSourceReleaseContentResultInfo>> SourceReleaseRequestResults;`
- L482 _public member_ `TMap<FInstallBundleSourceType, TOptional<FInstallBundleSourceReleaseContentResultInfo>> SourceRemoveRequestResults;`
- L484 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L486 _public member_ `bool bIsCanceled = false;`
- L487 _public member_ `bool bFinishWhenCanceled = true;` — Whether to run cleanup and callback when canceled

#### struct `FDefaultInstallBundleManager::FContentPatchCheckSharedContext`  
`struct FContentPatchCheckSharedContext`  
_L493-496_
- L495 _public member_ `TMap<FInstallBundleSourceType, bool> Results;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DEFAULTINSTALLBUNDLEMANAGER_API`
- L18 _macro_ `#define INSTALL_BUNDLE_ENABLE_ANALYTICS (!WITH_EDITOR)`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace IoStore` (scope `UE`)
- L67 _function_ `friend const TCHAR* LexToString(FDefaultInstallBundleManager::EBundleState Val)`
- L97 _function_ `friend const TCHAR* LexToString(FDefaultInstallBundleManager::EAsyncInitStep Val)`
- L131 _function_ `friend const TCHAR* LexToString(EBundlePrereqs Val)`
- L315 _function_ `friend const TCHAR* LexToString(EContentRequestState Val)`
- L452 _function_ `friend const TCHAR* LexToString(EContentReleaseRequestState Val)`
- L849 _prototype_ `ENUM_RANGE_BY_COUNT(FDefaultInstallBundleManager::EContentRequestBatch, FDefaultInstallBundleManager::EContentRequestBatch::Count);`
- L851 _prototype_ `const TCHAR* LexToString(FDefaultInstallBundleManager::EContentRequestBatch Val);`
- L854 _prototype_ `ENUM_RANGE_BY_COUNT(FDefaultInstallBundleManager::EContentReleaseRequestBatch, FDefaultInstallBundleManager::EContentReleaseRequestBatch::Count);`
- L856 _prototype_ `const TCHAR* LexToString(FDefaultInstallBundleManager::EContentReleaseRequestBatch Val);`

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Public/InstallBundleManagerUtil.h` (Public)


#### class `InstallBundleManagerUtil::FContentBuildMetaData`  
`class FContentBuildMetaData : public FJsonSerializable`  
_L60-77_
- inherits: `FJsonSerializable`
- L64 _public prototype_ `JSON_MCI_VALUE(AppName);`
- L65 _public prototype_ `JSON_MCI_VALUE(BuildVersion);`
- L66 _public prototype_ `JSON_MCI_VALUE(Platform);`
- L67 _public prototype_ `JSON_MCI_VALUE(ManifestPath);`
- L68 _public prototype_ `JSON_MCI_VALUE(ManifestHash);`
- L72 _public member_ `FString AppName;`
- L73 _public member_ `FString BuildVersion;`
- L74 _public member_ `FString Platform;`
- L75 _public member_ `FString ManifestPath;`
- L76 _public member_ `FString ManifestHash;`

#### class `InstallBundleManagerUtil::FPersistentStatContainer`  
`class FPersistentStatContainer : public InstallBundleUtil::PersistentStats::FPersistentStatContainerBase`  
_L82-209_
- inherits: `InstallBundleUtil::PersistentStats::FPersistentStatContainerBase`
- L85 _public prototype_ `FPersistentStatContainer();`
- L86 _public prototype_ `virtual ~FPersistentStatContainer();`
- L89 _public prototype_ `void AddRequiredBundlesForSession(const FString& SessionName, const TArray<FName>& BundleNames);` — Adds the BundleNames to the given session's RequiredBundle list
- L91 _public prototype_ `void UpdateForContentState(const FInstallBundleCombinedContentState& ContentState, const FString& SessionName);`
- L92 _public prototype_ `void UpdateForBundleSource(const FInstallBundleSourceUpdateContentResultInfo& BundleSourceResult, FInstallBundleSourceType SourceType, const FString& BundleName);`
- L95 _private prototype_ `void SendEnteringBackgroundAnalytic();`
- L96 _private prototype_ `void SendEnteringForegroundAnalytic();`
- L155 _private prototype_ `FPersistentStatsInformation CalculatePersistentStatsInformationForSession(const FString& SessionName);` — Creates an FPersistentStatsInformation struct to pass into analytics
- L180 _private member_ `TMap<FString, FSessionAnalyticsData> SessionAnalyticsDataMap;`
- L193 _private member_ `TMap<FString, FBundleAnalyticsData> BundleAnalyticsDataMap;`
- L196 _public member_ `FString BundleSourcesThatDidWork;`
- L200 _public prototype_ `virtual void StartSessionPersistentStatTracking(const FString& SessionName, const TArray<FName>& RequiredBundles = TArray<FName>(), const FString& ExpectedAnalyticsID = FString(), bool bForceResetStatData = false) override;`
- L201 _public prototype_ `virtual void StopSessionPersistentStatTracking(const FString& SessionName, bool bStopAllActiveTimers = true) override;`
- L203 _public prototype_ `virtual void RemoveSessionStats(const FString& SessionName) override;`
- L204 _public prototype_ `virtual void RemoveBundleStats(FName BundleName) override;`
- L207 _protected prototype_ `virtual void OnApp_EnteringBackground() override;`
- L208 _protected prototype_ `virtual void OnApp_EnteringForeground() override;`

#### struct `InstallBundleManagerUtil::FPersistentStatContainer::FPersistentStatsInformation`  
`struct FPersistentStatsInformation`  
_L100-151_
- desc: Helper struct to contain the information from a StatSession to pass into analytics cleaner
- L103 _public member_ `FString SessionName;`
- L104 _public member_ `FString RequiredBundleNames;`
- L105 _public member_ `FString BundleStats;`
- L107 _public member_ `int NumBackgrounded;`
- L108 _public member_ `int NumResumedFromBackground;`
- L109 _public member_ `int NumResumedFromLaunch;`
- L111 _public member_ `double RealTotalTime;`
- L112 _public member_ `double ActiveTotalTime;`
- L113 _public member_ `double EstimatedTotalBGTime;`
- L114 _public member_ `double RealChunkDBDownloadTime;`
- L115 _public member_ `double ActiveChunkDBDownloadTime;`
- L116 _public member_ `double EstimatedBackgroundChunkDBDownloadTime;`
- L117 _public member_ `double ActiveInstallTime;`
- L118 _public member_ `double EstimatedBGInstallTime;`
- L119 _public member_ `double ActivePSOTime;`
- L120 _public member_ `double EstimatedBGPSOTime;`
- L122 _public member_ `bool bRequiresDownload;`
- L123 _public member_ `bool bRequiresInstall;`
- L125 _public member_ `FString BundleSourcesThatDidWork;`
- L127 _public function_ `FPersistentStatsInformation() : SessionName() , RequiredBundleNames() , BundleStats() , NumBackgrounded(0) , NumResumedFromBackground(0) , NumResumedFromLaunch(0) , RealTotalTime(0.) , ActiveTotalTime(0.) , EstimatedTotalBGTime(0.) , RealChunkDBDownloadTime(0.) , ActiveChunkDBDownloadTime(0.) , EstimatedBackgroundChunkDBDownloadTime(0.) , ActiveInstallTime(0.) , EstimatedBGInstallTime(0.) , ActivePSOTime(0.) , EstimatedBGPSOTime(0.) , bRequiresDownload(false) , bRequiresInstall(false) , BundleSourcesThatDidWork()`
- L150 _public prototype_ `void FillOutAnalyticsArrayWithData(TArray<FAnalyticsEventAttribute>& OutAnalyticsArray) const;` — Puts this FPersistentStatsInformation's data into the provided analytics array

#### struct `InstallBundleManagerUtil::FPersistentStatContainer::FSessionAnalyticsData`  
`struct FSessionAnalyticsData`  
_L160-179_
- desc: Helper struct to store data needed for our analytics
- L163 _public member_ `bool bRequiresDownload;`
- L164 _public member_ `bool bRequiresInstall;`
- L165 _public member_ `bool bShouldSendBGAnalyticsSessionMap;`
- L167 _public function_ `FSessionAnalyticsData() : bRequiresDownload(false) , bRequiresInstall(false) , bShouldSendBGAnalyticsSessionMap(false)`
- L173 _public function_ `void ResetShouldSendBGAnalytics()`

#### struct `InstallBundleManagerUtil::FPersistentStatContainer::FBundleAnalyticsData`  
`struct FBundleAnalyticsData`  
_L183-192_
- desc: Helper struct to store data needed for our analytics on bundle persistent stats
- L187 _public member_ `TSet<FInstallBundleSourceType> BundleSourcesThatDidWorkMap;` — Store if each bundle source type did any work for this bundle. If its in this map it did work.
- L189 _public function_ `FBundleAnalyticsData() : BundleSourcesThatDidWorkMap()`

#### struct `InstallBundleManagerAnalytics::FBundleHeartbeatStats`  
`struct FBundleHeartbeatStats`  
_L214-226_
- L216 _public member_ `FName BundleName;`
- L217 _public member_ `FString LastStatusText{ TEXT("Unkno`
- L219 _public member_ `float Finishing_Percent = 0.0f;`
- L220 _public member_ `float Install_Percent = 0.0f;`
- L222 _public member_ `EInstallBundleResult LastErrorResult = EInstallBundleResult::OK;`
- L223 _public member_ `EInstallBundlePauseFlags PauseFlags = EInstallBundlePauseFlags::None;`
- L225 _public member_ `bool bIsComplete = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DEFAULTINSTALLBUNDLEMANAGER_API`
- L12 _macro_ `#define INSTALL_BUNDLE_ALLOW_ERROR_SIMULATION (!UE_BUILD_SHIPPING)`
- L15 _macro_ `#define WITH_PLATFORM_DLC_INSTALL_BUNDLE_SOURCE 0`
- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDefaultInstallBundleManager, Display, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDefaultInstallBundleManager, Display, All);`
- L27 _namespace_ `namespace InstallBundleManagerUtil`
- L29 _prototype_ `TSharedPtr<IInstallBundleSource> MakeBundleSource(FInstallBundleSourceType Type);` (scope `InstallBundleManagerUtil`)
- L32 _prototype_ `IPlatformChunkInstall* GetPlatformChunkInstall();` (scope `InstallBundleManagerUtil`)
- L35 _prototype_ `TSharedPtr<IInstallBundleSource> MakePlatformBundleSource();` (scope `InstallBundleManagerUtil`) — `UE_DEPRECATED(5.8, "Implement InstallBundleManagerUtil::GetPlatformChunkInstall instead.")`
- L39 _prototype_ `TSharedPtr<IPlatformDLC> GetPlatformDLC();` (scope `InstallBundleManagerUtil`)
- L44 _prototype_ `TSharedPtr<FQueuedThreadPool, ESPMode::ThreadSafe> GetJournalThreadPool();` (scope `InstallBundleManagerUtil`) — `UE_DEPRECATED(5.4, "Use UE::Tasks::FPipe instead.")` — Returns a thread pool with one thread suitible for running in-order journal tasks
- L48 _prototype_ `bool LoadBundleSourceBundleInfoFromConfig(FInstallBundleSourceType SourceType, const FConfigFile& InstallBundleConfig, const FString& Section, FInstallBundleSourcePersistentBundleInfo& OutInfo);` (scope `InstallBundleManagerUtil`) — Fills out a FInstallBundleSourceBundleInfo from the specified config section Returns false if the provided config section is not a bundle definition section.
- L52 _prototype_ `TSet<FName> GetBundleDependenciesFromConfig(FName InBundleName, TSet<FName>* SkippedUnknownBundles );` (scope `InstallBundleManagerUtil`) — Traverses bundle config sections and loads all dependencies for InBundleName, including InBundleName Sets bSkippedUnknownBundles if a config section for InBundleName or a dependency can't be found.
- L55 _prototype_ `void GetAllUpToDateBundlesFromConfg(const FConfigFile& InstallBundleConfig, TArray<FName>& OutBundles);` (scope `InstallBundleManagerUtil`) — adds all the known up to date bundles to the output array.
- L59 _macro_ `#define JSON_MCI_VALUE(var) JSON_SERIALIZE(#var, var)` — This class is a helper for parsing the buildinfo meta json file that should be either loadable from apk/ipa bundle or can be requested from CDN. It will eventually be completely replaced by, possible key-value lookup from apk/ipa bundle, or by a call to FN service backend to request similar info.
- L80 _prototype_ `void LogBundleRequestStats(const InstallBundleUtil::FContentRequestStatsKey& Key, const InstallBundleUtil::FContentRequestStats& RequestStats, ELogVerbosity::Type LogVerbosityOverride);` (scope `InstallBundleManagerUtil`)
- L212 _namespace_ `namespace InstallBundleManagerAnalytics`
- L237 _prototype_ `void FireEvent_InitBundleManagerComplete(IAnalyticsProviderET* AnalyticsProvider, const bool bCanRetry, const FString InitResultString);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.InitComplete @Trigger Bundle Manager finished async initialization @Type Client @EventParam CanRetry Bool True if initialization can be retried if it failed @EventParam InitResultString String Result code @Comments
- L252 _prototype_ `void FireEvent_BundleManagerCacheStats(IAnalyticsProviderET* AnalyticsProvider, const FInstallBundleCacheStats& Stats);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.CacheStats @Trigger Bundle Manager finished async initialization successfully @Type Client @EventParam CacheName (string) @EventParam MaxSize (uint64) Configured size of the cache @EventParam UsedSize (uint64) Amount of the cache used by bundles associated with this cache @EventParam ReservedSize (uint64) Amount the cache taken up bundles that cannot be evicted @EventParam FreeSize (uint64) Amount of the cache not being used @Comments Values may represent content that is not yet committed to or removed from the disk
- L261 _prototype_ `void FireEvent_InitBundleSourceBulkComplete(IAnalyticsProviderET* AnalyticsProvider, const FString InitResultString);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.InitBundleSourceBulkComplete @Trigger Bundle Manager finished async initialization @Type Client @EventParam InitResultString String Result code @Comments
- L271 _prototype_ `void FireEvent_InitBundleSourcePlayGoComplete(IAnalyticsProviderET* AnalyticsProvider, const FString InitResultString);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.InitBundleSourcePlayGoComplete @Trigger Bundle Manager finished async initialization @Type Client @EventParam InitResultString String Result code @Comments
- L281 _prototype_ `void FireEvent_InitBundleSourceIntelligentDeliveryComplete(IAnalyticsProviderET* AnalyticsProvider, const FString InitResultString);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.InitBundleSourceIntelligentDeliveryComplete @Trigger Bundle Manager finished async initialization @Type Client @EventParam InitResultString String Result code @Comments
- L291 _prototype_ `void FireEvent_InitBundleSourcePlatformChunkInstallComplete(IAnalyticsProviderET* AnalyticsProvider, const FString InitResultString);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.FireEvent_InitBundleSourcePlatformChunkInstallComplete @Trigger Bundle Manager finished async initialization @Type Client @EventParam InitResultString String Result code @Comments
- L300 _prototype_ `void FireEvent_InitBundleSourcePlatformDLCComplete(IAnalyticsProviderET* AnalyticsProvider, const FString InitResultString);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.FireEvent_InitBundleSourcePlatformDLCComplete @Trigger Bundle Manager finished async initialization @Type Client @EventParam InitResultString String Result code @Comments
- L318 _prototype_ `void FireEvent_BundleLatestClientCheckComplete(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, bool bSkippedCheck, FString SkipReason, bool bShouldPatch, bool bRequestFailed);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleLatestClientCheckComplete @Type Client @EventParam BundleName (string) String Name of bundle being installed. @EventParam AppVersion (string) Version of the client app @EventParam SkippedCheck (bool) True if the check was skipped @EventParam SkipReason (string) If skipped, the reason @EventParam ShouldPatch (bool) True if we are going to proceed with patching content @EventParam RequestFailed (bool) True if the patch check request failed @Comments
- L335 _prototype_ `void FireEvent_BundleRequestStarted(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleRequestStarted @Trigger Fired when a bundle request is started @Type Client @EventParam BundleName (string) String Name of bundle being installed.
- L351 _prototype_ `void FireEvent_BundleRequestStartedDetailed(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, const FString& PreviousManifest, const FString& CurrentManifest, const FString& CurrentVersion);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleRequestStartedDetailed @Trigger Fired when a bundle request is started, including more details from implementation @Type Client @EventParam BundleName (string) String Name of bundle being installed. @EventParam PreviousManifest (string) Manifest version information for currently installed version @EventParam CurrentManifest (string) Manifest version information for version we are going to patch to @EventParam CurrentVersion (string) Content version information for version we are going to patch to
- L368 _prototype_ `void FireEvent_BundleRequestComplete(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, bool bDidInstall, const FString& Result, const InstallBundleUtil::FContentRequestStats& TimingStats);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleRequestComplete @Trigger Fired after an install bundle request is completed @Type Client @EventParam BundleName (string) String Name of bundle being installed. @EventParam DidInstall (bool) True if the bundle was installed successfully @EventParam Result (string) Result of the request @EventParam TimingStates (double) A variable number of stats based on what bundle manager steps were run. Fields end in "_Time"
- L399 _prototype_ `void FireEvent_BundleRequestCompleteDetailed(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, bool bDidInstall, const FString& Result, const InstallBundleUtil::FContentRequestStats& TimingStats, const FBundleRequestCompleteInfo& RequestCompleteInfo, const TArray<FInstallBundleChunkDownloadInfo>* ChunkDownloadInfos);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleRequestCompleteDetailed @Trigger Fired after an install bundle request is completed, including more details from implementation @Type Client @EventParam BundleName (string) String Name of bundle being installed. @EventParam DidInstall (bool) True if the bundle was installed successfully @EventParam Result (string) Result of the request @EventParam TimingStates (double) A variable number of stats based on what bundle manager steps were run. Fields end in "_Time" @EventParam PreviousManfest (string) Manifest version information for currently installed version @EventParam CurrentManifest (string) Manifest version information for version we are going to patch to @EventParam PreviousVersion (string) Content version information for currently installed version @EventParam CurrentVersion (string) Content version information for version we are going to patch to @EventParam PreviousVersionTimeStamp (string) Timestamp of when the previous version as installed @EventParam TotalDownloadedBytes (uint64) Total bytes downloaded @EventParam EstimatedFullDownloadBytes (uint64) Estimated bytes that needed download @EventParam BPTErrorCode (string) Any BPT Error @EventParam DownloadType (string) Type of download @EventParam AsyncStartupDelay (double) How long (in seconds) before the async install task starts @EventParam AsyncExitDelay (double) How long (in seconds) before the async OnComplete is processed @EventParam AsyncPlacedInBackground (bool) True if ap
- L419 _prototype_ `void FireEvent_BundleReleaseRequestStarted(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, bool bRemoveFilesIfPossible, bool bUnmountOnly);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleReleaseRequestStarted @Trigger Fired when a bundle release request is started @Type Client @EventParam BundleName (string) String Name of bundle. @EventParam RemoveFilesIfPossible (bool) True if this request will try to clean up files. @EventParam UnmountOnly (bool) True if this request is only for unmount
- L436 _prototype_ `void FireEvent_BundleReleaseRequestComplete(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, bool bRemoveFilesIfPossible, bool bUnmountOnly, const FString& Result);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleReleaseRequestComplete @Trigger Fired when a bundle release request is complete @Type Client @EventParam BundleName (string) String Name of bundle. @EventParam RemoveFilesIfPossible (bool) True if this request will try to clean up files. @EventParam UnmountOnly (bool) True if this request is only for unmount @EventParam Result (string) Result of the request
- L455 _prototype_ `void FireEvent_BundleEvictedFromCache(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, const FString& BundleSource, FDateTime LastAccessTime, const FString& Result);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleEvictedFromCache @Trigger Fired after a cached bundle's content has been removed from disk @Type Client @EventParam BundleName (string) Name of bundle. @EventParam BundleSource (string) Source the bundle's content was removed from @EventParam LastAccessTime (string) Format yyyy.mm.dd-hh.mm.ss, last access time for the BundleSource specified. @EventParam BundleAgeHours (double) Amount of time in hours bundle content has been installed, measured from LastAccessTime. @EventParam Result (string) Result of the request, OK or an error code
- L471 _prototype_ `void FireEvent_BundleCacheHit(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, const FString& BundleSource);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleCacheHit @Trigger Fired after a cached bundle's source completes it's update @Type Client @EventParam BundleName (string) Name of bundle. @EventParam BundleSource (string) Source of the bundle's content
- L485 _prototype_ `void FireEvent_BundleCacheMiss(IAnalyticsProviderET* AnalyticsProvider, const FString& BundleName, const FString& BundleSource, bool bPatchRequired);` (scope `InstallBundleManagerAnalytics`) — @EventName InstallBundleManager.BundleCacheMiss @Trigger Fired after a cached bundle's source completes it's update @Type Client @EventParam BundleName (string) Name of bundle. @EventParam BundleSource (string) Source the bundle's content @EventParam PatchRequired (bool) If true, this miss was because we had to patch the bundle.  If false, the miss was because the bundle was not in the cache
- L523 _prototype_ `void FireEvent_PersistentPatchStats_StartPatching(IAnalyticsProviderET* AnalyticsProvider, const InstallBundleManagerUtil::FPersistentStatContainer::FPersistentStatsInformation& PersistentStatInformation);` (scope `InstallBundleManagerAnalytics`) — @EventName PersistentPatchStats.StartPatching @Trigger Fired whenever we begin patching for a particular session on every update start for each launch of the app. @Type Client @EventParam SessionName (string) Name of the session these stats correspond too. @EventParam RequiredBundleNames (string) List of bundles that were required to be patched as part of this session. @EventParam BundleStats (string) JSON array of all of the stats data for all bundles in the RequiredBundleNames array for this session. @EventParam NumBackgrounded (int) Number of times the application was backgrounded during this patch. @EventParam NumResumedFromBackground (int) Number of times the patch was resumed from returning to foreground from background (does not count initial app launches). @EventParam NumResumedFromLaunch (int) Number of times the patch was resumed from launching the app fresh (instead of from coming back from background). @EventParam RealTotalTime (double) @EventParam ActiveTotalTime (double) @EventParam EstimatedTotalBGTime (double) @EventParam RealChunkDBDownloadTime (double) @EventParam ActiveChunkDBDownloadTime (double) @EventParam EstimatedBackgroundChunkDBDownloadTime (double) @EventParam ActiveInstallTime (double) @EventParam EstimatedBGInstallTime (double) @EventParam ActivePSOTime (double) @EventParam EstimatedBGPSOTime (double) @EventParam bRequiresInstall (bool) If the update will require some amount of install work @EventParam bRequiresDownload (bool) If the update will r
- L560 _prototype_ `void FireEvent_PersistentPatchStats_EndPatching(IAnalyticsProviderET* AnalyticsProvider, const InstallBundleManagerUtil::FPersistentStatContainer::FPersistentStatsInformation& PersistentStatInformation);` (scope `InstallBundleManagerAnalytics`) — @EventName PersistentPatchStats.EndPatching @Trigger Fired whenever we have finished patching for a particular session @Type Client @EventParam SessionName (string) Name of the session these stats correspond too. @EventParam RequiredBundleNames (string) List of bundles that were required to be patched as part of this session. @EventParam BundleStats (string) JSON array of all of the stats data for all bundles in the RequiredBundleNames array for this session. @EventParam NumBackgrounded (int) Number of times the application was backgrounded during this patch. @EventParam NumResumedFromBackground (int) Number of times the patch was resumed from returning to foreground from background (does not count initial app launches). @EventParam NumResumedFromLaunch (int) Number of times the patch was resumed from launching the app fresh (instead of from coming back from background). @EventParam RealTotalTime (double) @EventParam ActiveTotalTime (double) @EventParam EstimatedTotalBGTime (double) @EventParam RealChunkDBDownloadTime (double) @EventParam ActiveChunkDBDownloadTime (double) @EventParam EstimatedBackgroundChunkDBDownloadTime (double) @EventParam ActiveInstallTime (double) @EventParam EstimatedBGInstallTime (double) @EventParam ActivePSOTime (double) @EventParam EstimatedBGPSOTime (double) @EventParam bRequiresInstall (bool) If the update will require some amount of install work @EventParam bRequiresDownload (bool) If the update will require downloading some chunk data @EventPar
- L597 _prototype_ `void FireEvent_PersistentPatchStats_Background(IAnalyticsProviderET* AnalyticsProvider, const InstallBundleManagerUtil::FPersistentStatContainer::FPersistentStatsInformation& PersistentStatInformation);` (scope `InstallBundleManagerAnalytics`) — @EventName PersistentPatchStats.Background @Trigger Fired whenever we background the app during the patching process @Type Client @EventParam SessionName (string) Name of the session these stats correspond too. @EventParam RequiredBundleNames (string) List of bundles that were required to be patched as part of this session. @EventParam BundleStats (string) JSON array of all of the stats data for all bundles in the RequiredBundleNames array for this session. @EventParam NumBackgrounded (int) Number of times the application was backgrounded during this patch. @EventParam NumResumedFromBackground (int) Number of times the patch was resumed from returning to foreground from background (does not count initial app launches). @EventParam NumResumedFromLaunch (int) Number of times the patch was resumed from launching the app fresh (instead of from coming back from background). @EventParam RealTotalTime (double) @EventParam ActiveTotalTime (double) @EventParam EstimatedTotalBGTime (double) @EventParam RealChunkDBDownloadTime (double) @EventParam ActiveChunkDBDownloadTime (double) @EventParam EstimatedBackgroundChunkDBDownloadTime (double) @EventParam ActiveInstallTime (double) @EventParam EstimatedBGInstallTime (double) @EventParam ActivePSOTime (double) @EventParam EstimatedBGPSOTime (double) @EventParam bRequiresInstall (bool) If the update will require some amount of install work @EventParam bRequiresDownload (bool) If the update will require downloading some chunk data @EventParam
- L634 _prototype_ `void FireEvent_PersistentPatchStats_Foreground(IAnalyticsProviderET* AnalyticsProvider, const InstallBundleManagerUtil::FPersistentStatContainer::FPersistentStatsInformation& PersistentStatInformation);` (scope `InstallBundleManagerAnalytics`) — @EventName PersistentPatchStats.Foreground @Trigger Fired whenever we return from background into the foreground during the patching process @Type Client @EventParam SessionName (string) Name of the session these stats correspond too. @EventParam RequiredBundleNames (string) List of bundles that were required to be patched as part of this session. @EventParam BundleStats (string) JSON array of all of the stats data for all bundles in the RequiredBundleNames array for this session. @EventParam NumBackgrounded (int) Number of times the application was backgrounded during this patch. @EventParam NumResumedFromBackground (int) Number of times the patch was resumed from returning to foreground from background (does not count initial app launches). @EventParam NumResumedFromLaunch (int) Number of times the patch was resumed from launching the app fresh (instead of from coming back from background). @EventParam RealTotalTime (double) @EventParam ActiveTotalTime (double) @EventParam EstimatedTotalBGTime (double) @EventParam RealChunkDBDownloadTime (double) @EventParam ActiveChunkDBDownloadTime (double) @EventParam EstimatedBackgroundChunkDBDownloadTime (double) @EventParam ActiveInstallTime (double) @EventParam EstimatedBGInstallTime (double) @EventParam ActivePSOTime (double) @EventParam EstimatedBGPSOTime (double) @EventParam bRequiresInstall (bool) If the update will require some amount of install work @EventParam bRequiresDownload (bool) If the update will require downloading som

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Public/InstallBundleSourceBulk.h` (Public)


#### class `FInstallBundleSourceBulk`  
`class FInstallBundleSourceBulk : public IInstallBundleSource`  
_L12-106_
- inherits: `IInstallBundleSource`
- L15 _public prototype_ `FInstallBundleSourceBulk();`
- L16 _public prototype_ `FInstallBundleSourceBulk(const FInstallBundleSourceBulk& Other) = delete;`
- L17 _public prototype_ `FInstallBundleSourceBulk& operator=(const FInstallBundleSourceBulk& Other) = delete;`
- L18 _public prototype_ `virtual ~FInstallBundleSourceBulk();`
- L21 _private prototype_ `bool Tick(float dt);`
- L23 _private prototype_ `void TickInit();`
- L26 _private prototype_ `void AsyncInit_FireInitAnlaytic();` — Init
- L27 _private prototype_ `void AsyncInit_MakeBundlesForBulkBuild();`
- L30 _protected prototype_ `virtual EInstallBundleInstallState GetBundleInstallState(FName BundleName);`
- L34 _public prototype_ `virtual FInstallBundleSourceType GetSourceType() const override;`
- L35 _public function_ `virtual float GetSourceWeight() const override` — Low weight since all this source does in mount
- L37 _public prototype_ `virtual FInstallBundleSourceInitInfo Init( TSharedRef<InstallBundleUtil::FContentRequestStatsMap> InRequestStats, TSharedPtr<IAnalyticsProviderET> AnalyticsProvider, TSharedPtr<InstallBundleUtil::PersistentStats::FPersistentStatContainerBase> PersistentStatsContainer) override;`
- L41 _public prototype_ `virtual void AsyncInit(FInstallBundleSourceInitDelegate Callback) override;`
- L43 _public prototype_ `virtual void AsyncInit_QueryBundleInfo(FInstallBundleSourceQueryBundleInfoDelegate Callback) override;`
- L45 _public prototype_ `virtual EInstallBundleManagerInitState GetInitState() const override;`
- L47 _public prototype_ `virtual FString GetContentVersion() const override;`
- L49 _public prototype_ `virtual TSet<FName> GetBundleDependencies(FName InBundleName, TSet<FName>* SkippedUnknownBundles ) const override;`
- L51 _public prototype_ `virtual void GetContentState(TArrayView<const FName> BundleNames, EInstallBundleGetContentStateFlags Flags, FInstallBundleGetContentStateDelegate Callback) override;`
- L53 _public prototype_ `virtual void RequestUpdateContent(FRequestUpdateContentBundleContext BundleContext) override;`
- L55 _public prototype_ `virtual void SetErrorSimulationCommands(const FString& CommandLine) override;`
- L57 _public function_ `virtual void SetAnalyticsProvider(TSharedPtr<IAnalyticsProviderET> NewAnalyticsProvider) override`
- L65 _public prototype_ `static bool TryLoadBulkBuildBundleMetadata(TArray<FString>& InOutFileList, TMap<FName, TArray<FString>>& InOutBulkBuildBundles);` — Function that loads BulkBundleBuild information from a generated BulkBuildBundleIni instead of applying reg-ex at runtime Returns true if BulkBundleBuild.ini existed and was parsed successfully, false otherwise Removes any loaded entries from InOutFileList
- L68 _public prototype_ `static void SerializeBulkBuildBundleMetadata(const TMap<FName, TArray<FString>>& BulkBuildBundles);` — Serialize out our BulkBundleBuild information to a BulkBundleBuild.ini file for future runs to not have to parse this information
- L74 _protected function_ `virtual void FilterContentBundlePaths(const FRequestUpdateContentBundleContext& BundleContext, TArray<FString>& InOutContentPaths)` — Optionally used to modify what ContentPaths are returned in the base implementation of RequestUpdateContent
- L77 _protected member_ `FTSTicker::FDelegateHandle TickHandle;`
- L94 _protected member_ `EInstallBundleManagerInitState InitState = EInstallBundleManagerInitState::NotInitialized;`
- L95 _protected member_ `EInstallBundleManagerInitResult InitResult = EInstallBundleManagerInitResult::OK;`
- L96 _protected member_ `EAsyncInitStep InitStep = EAsyncInitStep::None;`
- L97 _protected member_ `EAsyncInitStep LastInitStep = EAsyncInitStep::None;`
- L98 _protected member_ `EAsyncInitStepResult InitStepResult = EAsyncInitStepResult::Done;`
- L99 _protected member_ `bool bRetryInit = false;`
- L100 _protected member_ `FInstallBundleSourceInitDelegate OnInitCompleteCallback;`
- L101 _protected member_ `TArray<TUniquePtr<InstallBundleUtil::FInstallBundleTask>> InitAsyncTasks;`
- L103 _protected member_ `TMap<FName, TArray<FString>> BulkBuildBundles;` — BundleName -> Files
- L105 _protected member_ `TSharedPtr<IAnalyticsProviderET> AnalyticsProvider;`

#### enum `FInstallBundleSourceBulk::EAsyncInitStep`  
`enum class EAsyncInitStep : int`  
_L79-85_
- L81 _public enumerator_ `None`
- L82 _public enumerator_ `MakeBundlesForBulkBuild`
- L83 _public enumerator_ `Finishing`
- L84 _public enumerator_ `Count`

#### enum `FInstallBundleSourceBulk::EAsyncInitStepResult`  
`enum class EAsyncInitStepResult : int`  
_L88-92_
- L90 _public enumerator_ `Waiting`
- L91 _public enumerator_ `Done`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DEFAULTINSTALLBUNDLEMANAGER_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace IoStore` (scope `UE`)

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Public/InstallBundleSourcePlatformBase.h` (Public)


#### class `FInstallBundleSourcePlatformBase`  
`class FInstallBundleSourcePlatformBase : public IInstallBundleSource`  
_L13-71_
- inherits: `IInstallBundleSource`
- L17 _public prototype_ `FInstallBundleSourcePlatformBase();`
- L18 _public prototype_ `FInstallBundleSourcePlatformBase(const FInstallBundleSourcePlatformBase& Other) = delete;`
- L19 _public prototype_ `FInstallBundleSourcePlatformBase& operator=(const FInstallBundleSourcePlatformBase& Other) = delete;`
- L20 _public prototype_ `virtual ~FInstallBundleSourcePlatformBase();`
- L25 _public prototype_ `virtual FInstallBundleSourceType GetSourceType() const override;`
- L27 _public prototype_ `virtual FInstallBundleSourceInitInfo Init( TSharedRef<InstallBundleUtil::FContentRequestStatsMap> InRequestStats, TSharedPtr<IAnalyticsProviderET> AnalyticsProvider, TSharedPtr<InstallBundleUtil::PersistentStats::FPersistentStatContainerBase> InPersistentStatsContainer) override;`
- L33 _public prototype_ `virtual void AsyncInit_QueryBundleInfo(FInstallBundleSourceQueryBundleInfoDelegate Callback) override;`
- L35 _public prototype_ `virtual EInstallBundleManagerInitState GetInitState() const override;`
- L37 _public prototype_ `virtual FString GetContentVersion() const override;`
- L39 _public prototype_ `virtual TSet<FName> GetBundleDependencies(FName InBundleName, TSet<FName>* SkippedUnknownBundles ) const override;`
- L41 _public function_ `virtual void SetAnalyticsProvider(TSharedPtr<IAnalyticsProviderET> NewAnalyticsProvider) override`
- L47 _protected prototype_ `virtual bool QueryPersistentBundleInfo(FInstallBundleSourcePersistentBundleInfo& SourceBundleInfo) const = 0;`
- L50 _protected function_ `template<typename T> inline void StatsBegin(const InstallBundleUtil::FContentRequestStatsKey& Key, T State)`
- L56 _protected function_ `template<typename T> inline void StatsEnd(const InstallBundleUtil::FContentRequestStatsKey& Key, T State, uint64 DataSize = 0)`
- L61 _protected member_ `TSharedPtr<IAnalyticsProviderET> AnalyticsProvider;`
- L63 _protected member_ `TSharedPtr<InstallBundleUtil::FContentRequestStatsMap> RequestStats;`
- L65 _protected member_ `TSharedPtr<InstallBundleUtil::PersistentStats::FPersistentStatContainerBase> PersistentStatsContainer;`
- L67 _protected member_ `EInstallBundleManagerInitState InitState = EInstallBundleManagerInitState::NotInitialized;`
- L69 _protected member_ `TArray<TPair<FString, TArray<FRegexPattern>>> BundleRegexList;` — BundleName -> FileRegex
- L70 _protected member_ `TArray<TPair<FString, TArray<FRegexPattern>>> BundleSubsetRegexList;`

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Public/InstallBundleSourcePlatformChunkInstall.h` (Public)


#### class `FInstallBundleSourcePlatformChunkInstall`  
`class FInstallBundleSourcePlatformChunkInstall : public FInstallBundleSourcePlatformBase`  
_L12-113_
- inherits: `FInstallBundleSourcePlatformBase`
- L38 _private typedef_ `using FContentRequestRef = TSharedRef<FContentRequest, ESPMode::ThreadSafe>;`
- L39 _private typedef_ `using FContentRequestPtr = TSharedPtr<FContentRequest, ESPMode::ThreadSafe>;`
- L40 _private typedef_ `using FContentRequestWeakPtr = TWeakPtr<FContentRequest, ESPMode::ThreadSafe>;`
- L52 _private typedef_ `using FContentReleaseRequestRef = TSharedRef<FContentReleaseRequest, ESPMode::ThreadSafe>;`
- L53 _private typedef_ `using FContentReleaseRequestPtr = TSharedPtr<FContentReleaseRequest, ESPMode::ThreadSafe>;`
- L54 _private typedef_ `using FContentReleaseRequestWeakPtr = TWeakPtr<FContentReleaseRequest, ESPMode::ThreadSafe>;`
- L58 _public prototype_ `FInstallBundleSourcePlatformChunkInstall( IPlatformChunkInstall* InPlatformChunkInstall);`
- L59 _public prototype_ `FInstallBundleSourcePlatformChunkInstall(const FInstallBundleSourcePlatformChunkInstall& Other) = delete;`
- L60 _public prototype_ `FInstallBundleSourcePlatformChunkInstall& operator=(const FInstallBundleSourcePlatformChunkInstall& Other) = delete;`
- L61 _public prototype_ `virtual ~FInstallBundleSourcePlatformChunkInstall();`
- L65 _private prototype_ `bool Tick(float dt);`
- L67 _private prototype_ `void TickUpdateChunkOrder();`
- L71 _public prototype_ `virtual FInstallBundleSourceInitInfo Init( TSharedRef<InstallBundleUtil::FContentRequestStatsMap> InRequestStats, TSharedPtr<IAnalyticsProviderET> AnalyticsProvider, TSharedPtr<InstallBundleUtil::PersistentStats::FPersistentStatContainerBase> InPersistentStatsContainer) override;`
- L76 _public prototype_ `virtual void AsyncInit(FInstallBundleSourceInitDelegate Callback) override;`
- L78 _public prototype_ `virtual void GetContentState(TArrayView<const FName> BundleNames, EInstallBundleGetContentStateFlags Flags, FInstallBundleGetContentStateDelegate Callback) override;`
- L80 _public prototype_ `virtual EInstallBundleSourceBundleSkipReason GetBundleSkipReason(FName BundleName) const override;`
- L82 _public prototype_ `virtual void RequestUpdateContent(FRequestUpdateContentBundleContext Context) override;`
- L84 _public prototype_ `virtual void RequestReleaseContent(FRequestReleaseContentBundleContext BundleContext) override;`
- L86 _public prototype_ `virtual void CancelBundles(TArrayView<const FName> BundleNames) override;`
- L88 _public prototype_ `virtual TOptional<FInstallBundleSourceProgress> GetBundleProgress(FName BundleName) const override;`
- L91 _protected prototype_ `virtual bool QueryPersistentBundleInfo(FInstallBundleSourcePersistentBundleInfo& SourceBundleInfo) const override;`
- L93 _protected prototype_ `void OnNamedChunkInstall(const FNamedChunkCompleteCallbackParam& Param);`
- L95 _protected prototype_ `FName GetNamedChunkForBundle(FName BundleName) const;`
- L98 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L99 _private member_ `FDelegateHandle NamedChunkInstallDelegateHandle;`
- L101 _private member_ `TMap<FName, FBundleInfo> BundleInfoMap;`
- L102 _private member_ `TSet<FName> NamedChunks;`
- L104 _private member_ `TArray<FContentRequestRef> ContentRequests;`
- L105 _private member_ `TArray<FContentReleaseRequestRef> ContentReleaseRequests;`
- L107 _private member_ `TArray<TUniquePtr<InstallBundleUtil::FInstallBundleTask>> GeneralAsyncTasks;`
- L109 _private member_ `IPlatformChunkInstall* PlatformChunkInstall;`
- L111 _private member_ `bool bChunkOrderDirty = false;`
- L112 _private member_ `bool bIsUpdatingChunkOrder = false;`

#### struct `FInstallBundleSourcePlatformChunkInstall::FBundleInfo`  
`struct FBundleInfo`  
_L17-24_
- desc: Internal Types
- L20 _public member_ `EInstallBundlePriority Priority = EInstallBundlePriority::Low;`
- L22 _public member_ `FName NamedChunk;`
- L23 _public member_ `TArray<FString> FilePaths;`

#### class `FInstallBundleSourcePlatformChunkInstall::FContentRequest`  
`class FContentRequest`  
_L27-37_
- L30 _public member_ `FName BundleName;`
- L31 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L32 _public member_ `bool bInProgress = true;`
- L33 _public member_ `bool bCancelled = false;`
- L35 _public member_ `TArray<FString> ContentPaths;`
- L36 _public member_ `FInstallBundleCompleteDelegate CompleteCallback;`

#### class `FInstallBundleSourcePlatformChunkInstall::FContentReleaseRequest`  
`class FContentReleaseRequest`  
_L42-51_
- L45 _public member_ `FName BundleName;`
- L46 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L47 _public member_ `bool bInProgress = true;`
- L48 _public member_ `bool bFailed = false;`
- L50 _public member_ `FInstallBundleRemovedDelegate CompleteCallback;`

### `Plugins/Experimental/DefaultInstallBundleManager/Source/Public/InstallBundleSourcePlatformDLC.h` (Public)


#### class `FInstallBundleSourcePlatformDLC`  
`class FInstallBundleSourcePlatformDLC : public FInstallBundleSourcePlatformBase`  
_L12-120_
- inherits: `FInstallBundleSourcePlatformBase`
- L40 _private typedef_ `using FDLCContentRequestRef = TSharedRef<FDLCContentRequest, ESPMode::ThreadSafe>;`
- L41 _private typedef_ `using FDLCContentRequestPtr = TSharedPtr<FDLCContentRequest, ESPMode::ThreadSafe>;`
- L42 _private typedef_ `using FDLCContentRequestWeakPtr = TWeakPtr<FDLCContentRequest, ESPMode::ThreadSafe>;`
- L55 _private typedef_ `using FDLCContentReleaseRequestRef = TSharedRef<FDLCContentReleaseRequest, ESPMode::ThreadSafe>;`
- L56 _private typedef_ `using FDLCContentReleaseRequestPtr = TSharedPtr<FDLCContentReleaseRequest, ESPMode::ThreadSafe>;`
- L57 _private typedef_ `using FDLCContentReleaseRequestWeakPtr = TWeakPtr<FDLCContentReleaseRequest, ESPMode::ThreadSafe>;`
- L61 _public prototype_ `FInstallBundleSourcePlatformDLC( TSharedPtr<IPlatformDLC> InPlatformDLC);`
- L62 _public prototype_ `FInstallBundleSourcePlatformDLC(const FInstallBundleSourcePlatformDLC& Other) = delete;`
- L63 _public prototype_ `FInstallBundleSourcePlatformDLC& operator=(const FInstallBundleSourcePlatformDLC& Other) = delete;`
- L64 _public prototype_ `virtual ~FInstallBundleSourcePlatformDLC();`
- L66 _public prototype_ `virtual FInstallBundleSourceType GetSourceType() const override;`
- L70 _private prototype_ `bool Tick(float dt);`
- L74 _public prototype_ `virtual FInstallBundleSourceInitInfo Init( TSharedRef<InstallBundleUtil::FContentRequestStatsMap> InRequestStats, TSharedPtr<IAnalyticsProviderET> AnalyticsProvider, TSharedPtr<InstallBundleUtil::PersistentStats::FPersistentStatContainerBase> InPersistentStatsContainer) override;`
- L79 _public prototype_ `virtual void AsyncInit(FInstallBundleSourceInitDelegate Callback) override;`
- L81 _public prototype_ `virtual void GetContentState(TArrayView<const FName> BundleNames, EInstallBundleGetContentStateFlags Flags, FInstallBundleGetContentStateDelegate Callback) override;`
- L83 _public prototype_ `virtual EInstallBundleSourceBundleSkipReason GetBundleSkipReason(FName BundleName) const override;`
- L85 _public prototype_ `virtual void RequestUpdateContent(FRequestUpdateContentBundleContext Context) override;`
- L87 _public prototype_ `virtual void RequestReleaseContent(FRequestReleaseContentBundleContext BundleContext) override;`
- L89 _public prototype_ `virtual void CancelBundles(TArrayView<const FName> BundleNames) override;`
- L91 _public prototype_ `virtual TOptional<FInstallBundleSourceProgress> GetBundleProgress(FName BundleName) const override;`
- L94 _protected prototype_ `virtual bool QueryPersistentBundleInfo(FInstallBundleSourcePersistentBundleInfo& SourceBundleInfo) const override;`
- L96 _protected prototype_ `void OnDLCNotification(FName DLCName, IPlatformDLC::ENotification Notification, bool bSuccess);`
- L98 _protected prototype_ `TArray<FString> GetContentPathsForDLC( FName DLCName, FName BundleName );`
- L100 _protected prototype_ `FName GetDLCNameForBundle(FName BundleName) const;`
- L104 _protected function_ `virtual FPlatformUserId GetDLCStoreUserId() const` — Override to return the platform user to pass to SetStoreUser before each download.
- L106 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L107 _private member_ `FDelegateHandle DLCNotificationDelegateHandle;`
- L109 _private member_ `TMap<FName, FBundleInfo> BundleInfoMap;`
- L110 _private member_ `TMap<FName, TArray<FString>> BundleToSubsetMap;`
- L111 _private member_ `TSet<FName> DLCNames;`
- L112 _private member_ `TArray<FString> PakSearchDirs;`
- L114 _private member_ `TArray<FDLCContentRequestRef> ContentRequests;`
- L115 _private member_ `TArray<FDLCContentReleaseRequestRef> ContentReleaseRequests;`
- L117 _private member_ `TArray<TUniquePtr<InstallBundleUtil::FInstallBundleTask>> GeneralAsyncTasks;`
- L119 _private member_ `TSharedPtr<IPlatformDLC> PlatformDLC;`

#### struct `FInstallBundleSourcePlatformDLC::FBundleInfo`  
`struct FBundleInfo`  
_L17-27_
- desc: Internal Types
- L20 _public member_ `EInstallBundlePriority Priority = EInstallBundlePriority::Low;`
- L22 _public member_ `FName DLCName;`
- L24 _public member_ `bool bHasSetFilePaths = false;`
- L25 _public member_ `bool bContainsIoStoreOnDemandToc = false;`
- L26 _public member_ `TArray<FString> FilePaths;`

#### class `FInstallBundleSourcePlatformDLC::FDLCContentRequest`  
`class FDLCContentRequest`  
_L30-39_
- L33 _public member_ `FName BundleName;`
- L34 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L35 _public member_ `bool bInProgress = true;`
- L36 _public member_ `bool bCancelled = false;`
- L38 _public member_ `FInstallBundleCompleteDelegate CompleteCallback;`

#### class `FInstallBundleSourcePlatformDLC::FDLCContentReleaseRequest`  
`class FDLCContentReleaseRequest`  
_L44-54_
- L47 _public member_ `FName BundleName;`
- L48 _public member_ `ELogVerbosity::Type LogVerbosityOverride = ELogVerbosity::NoLogging;`
- L49 _public member_ `bool bInProgress = true;`
- L50 _public member_ `bool bFailed = false;`
- L51 _public member_ `bool bUninstallRequested = false;`
- L53 _public member_ `FInstallBundleRemovedDelegate CompleteCallback;`
