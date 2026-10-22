# Plugins / AndroidFetchBackgroundDownload

- module root: `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload`
- headers: 8; symbols: 242
- symbol kinds: class=7, delegate=1, enum=1, enumerator=4, function=9, member=91, namespace=16, prototype=104, struct=6, typedef=2, variable=1
- PrivateDependencyModuleNames: AndroidBackgroundService, BackgroundHTTP, BuildSettings, Core, CoreUObject, Engine, Launch

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Private/AndroidJniDownloadUEDownloadWorker.h` (Private)


#### struct `UE::Jni::Download::FUEDownloadWorker`  
`struct FUEDownloadWorker: Java::Lang::FObject`  
_L11-33_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L15 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnWorkerStart(JNIEnv* env, jobject thiz, jstring WorkID);`
- L16 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnWorkerStop(JNIEnv* env, jobject thiz, jstring WorkID);`
- L17 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnProgress(JNIEnv* env, jobject thiz, jstring TaskID, jlong TotalBytesWritten, jlong BytesWrittenSinceLastCall);`
- L18 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnComplete(JNIEnv* env, jobject thiz, jstring TaskID, jboolean bWasSuccess);`
- L19 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnMetrics(JNIEnv* env, jobject thiz, jstring TaskID, jlong TotalBytesDownloaded, jlong DownloadDuration, jlong DownloadStartTimeUTC, jlong DownloadEndTimeUTC);`
- L20 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnAllComplete(JNIEnv* env, jobject thiz, jboolean bDidAllRequestsSucceed);`
- L21 _public prototype_ `static void JNICALL nativeAndroidBackgroundDownloadOnTick(JNIEnv* env, jobject thiz);`
- L23 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnWorkerStart), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnWorkerStop), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnProgress), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnComplete), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnMetrics), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnAllComplete), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundDownloadOnTick) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L9 _namespace_ `namespace Download` (scope `UE::Jni`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Jni` (scope `UE`)
- L38 _variable_ `template struct TInitialize<Download::FUEDownloadWorker>;` (scope `UE::Jni`)

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidDownloadManager.h` (Public)


#### struct `UE::Online::Download::Android::FDownloadManager`  
`struct FDownloadManager: IBackgroundHttpManager`  
_L16-105_
- inherits: `IBackgroundHttpManager`
- L50 _public prototype_ `FDownloadManager();`
- L52 _public prototype_ `virtual void Initialize(bool bClearPreExistingRequestsAtStartup) override;`
- L53 _public prototype_ `virtual void Shutdown() override;`
- L55 _public prototype_ `virtual void AddRequest(const FBackgroundHttpRequestPtr Request) override;`
- L56 _public prototype_ `virtual void RemoveRequest(const FBackgroundHttpRequestPtr Request) override;`
- L57 _public prototype_ `virtual void RequeueRequest(const FBackgroundHttpRequestPtr Request) override;`
- L58 _public prototype_ `virtual void GetActiveDownloadRequestIDs(TSet<FString>& OutActiveIDs) const override;`
- L60 _public prototype_ `virtual void DeleteAllTemporaryFiles() override;`
- L61 _public function_ `virtual bool IsGenericImplementation() const override`
- L63 _public prototype_ `virtual void SetCellularPreference(int32 Value) override;`
- L64 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) override;`
- L66 _public function_ `virtual int GetMaxActiveDownloads() const override`
- L67 _public prototype_ `virtual void SetMaxActiveDownloads(int32 MaxActiveDownloads) override;`
- L69 _public function_ `virtual FString GetTempFileLocationForURL(const FString& URL, const FString& RequestID) override`
- L71 _public prototype_ `virtual void CleanUpDataAfterCompletingRequest(const FBackgroundHttpRequestPtr Request) override;`
- L74 _public prototype_ `void RestartAllDownloads();`
- L78 _private function_ `virtual bool AssociateWithAnyExistingRequest(const FBackgroundHttpRequestPtr Request) override`
- L81 _private prototype_ `void EnqueueRequest(FRequest& Request);`
- L82 _private prototype_ `void CancelRequest(FRequest& Request);`
- L84 _private prototype_ `void OnProgress(const FString& DestinationLocation, int64 TotalBytesWritten, int64 BytesWrittenSinceLastCall) const;`
- L85 _private prototype_ `void OnComplete(const FString& DestinationLocation, bool bDidSucceed, int64 TotalBytesDownloaded, int64 DownloadDuration, int64 DownloadStartTimeUTC, int64 DownloadEndTimeUTC);`
- L86 _private prototype_ `void OnStart(const FString& DestinationLocation, const FString& DebugString, int64 StartTimeUTC) const;`
- L89 _private prototype_ `void DeleteStaleTempFiles() const;`
- L90 _private prototype_ `static void GatherTempFilesOlderThen(TArray<FString>& OutTimedOutTempFilenames,double SecondsToConsiderOld, const TArray<FString>* OptionalFileList = nullptr);`
- L91 _private prototype_ `void GatherTempFilesWithoutURLMappings(TArray<FString>& OutTempFilesMissingURLMappings, TArray<FString>* OptionalFileList = nullptr) const;`
- L92 _private prototype_ `static void GatherAllTempFilenames(TArray<FString>& OutAllTempFilenames, bool bOutputAsFullPaths = false);`
- L93 _private prototype_ `static void ConvertAllTempFilenamesToFullPaths(TArray<FString>& OutFilenamesAsFullPaths, const TArray<FString>& FilenamesToConvertToFullPaths);`
- L96 _private member_ `int MaxActiveDownloads;`
- L98 _private member_ `TMap<FStringView, TSharedPtr<FRequest>> Requests;`
- L100 _private member_ `BackgroundHttpFileHashHelperRef FileHashHelper;`
- L102 _private member_ `FAndroidPlatformBackgroundHttpManager::FAndroidBackgroundHTTPManagerDefaultLocalizedText AndroidBackgroundHTTPManagerDefaultLocalizedText;`

#### struct `UE::Online::Download::Android::FDownloadManager::FRequest`  
`struct FRequest: FBackgroundHttpRequestImpl`  
_L18-48_
- inherits: `FBackgroundHttpRequestImpl`
- L20 _public prototype_ `virtual bool ProcessRequest() override;`
- L21 _public prototype_ `virtual void CancelRequest() override;`
- L22 _public prototype_ `virtual void PauseRequest() override;`
- L23 _public prototype_ `virtual void ResumeRequest() override;`
- L26 _public prototype_ `virtual void GetDebugText(TArray<FString>& Output) override;`
- L29 _public prototype_ `void RotateURLList();`
- L32 _private prototype_ `int GetPriorityAsAndroidPriority() const;`
- L34 _private member_ `FString DestinationLocation;`
- L36 _private member_ `TWeakPtr<FDownloadManager> Parent;`
- L38 _private member_ `bool bIsPaused = false;`
- L40 _private member_ `int64 DownloadedBytes = 0;`
- L41 _private member_ `double DownloadStartTime = 0.0;`
- L43 _private member_ `FString DebugString;`
- L45 _private member_ `int64 StartTimeUTC = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L9 _namespace_ `namespace Download` (scope `UE::Jni`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L14 _namespace_ `namespace Download` (scope `UE::Online`)
- L14 _namespace_ `namespace Android` (scope `UE::Online::Download`)

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidFetchBackgroundDownloadModule.h` (Public)


#### class `FAndroidFetchBackgroundDownloadModule`  
`class FAndroidFetchBackgroundDownloadModule : public IModuleInterface`  
_L16-25_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _private member_ `TSharedPtr<FAndroidPlatformBackgroundHttpModularFeatureWrapper, ESPMode::ThreadSafe> FeatureWrapper;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidBackgroundService, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidBackgroundService, Log, All);`

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidFetchPlatformBackgroundHttp.h` (Public)


#### class `FAndroidFetchPlatformBackgroundHttp`  
`class FAndroidFetchPlatformBackgroundHttp`  
_L17-58_
- desc: Android specific BackgroundHttp ModularFeature implementation that makes use of AndroidBackgroundService and the Fetch API to perform background downloading.
- L23 _public prototype_ `static void Initialize();` — Platform initialization step
- L28 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L34 _public prototype_ `static FBackgroundHttpManagerPtr CreatePlatformBackgroundHttpManager();` — Creates a platform-specific Background HTTP manager. Un-implemented platforms should create a FGenericPlatformBackgroundHttpManager
- L42 _public prototype_ `static FBackgroundHttpRequestPtr ConstructBackgroundRequest();` — Creates a new Background Http request instance for the current platform that will continue to download when the application is in the background @return request object
- L50 _public prototype_ `static FBackgroundHttpResponsePtr ConstructBackgroundResponse(int32 ResponseCode, const FString& TempFilePath);` — Creates a new Background Http Response instance for the current platform This normally is called by the request and associated with itself. @return response object
- L57 _public prototype_ `static bool CheckRequirementsSupported();` — Allows our underlying Android Background HTTP implementation to check for requirements before we utilize this modular feature @return true if our requirements check succeeded

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidPlatformBackgroundHttpManager.h` (Public)


#### class `FAndroidPlatformBackgroundHttpManager`  
`class FAndroidPlatformBackgroundHttpManager : public FBackgroundHttpManagerImpl`  
_L34-233_
- inherits: `FBackgroundHttpManagerImpl`
- desc: Manages Background Http request that are currently being processed if we are on an Android Platform
- L38 _public prototype_ `FAndroidPlatformBackgroundHttpManager();`
- L39 _public function_ `virtual ~FAndroidPlatformBackgroundHttpManager()`
- L45 _public prototype_ `virtual void Initialize(bool bClearPreExistingRequestsAtStartup) override;`
- L46 _public prototype_ `virtual void Shutdown() override;`
- L47 _public prototype_ `virtual void SetCellularPreference(int32 Value) override;`
- L48 _public prototype_ `virtual void SetLimitedDataPreference(int32 Value) override;`
- L49 _public function_ `virtual bool IsGenericImplementation() const override`
- L50 _public prototype_ `bool Tick(float DeltaTime);`
- L53 _protected prototype_ `virtual void ActivatePendingRequests() override;`
- L56 _public prototype_ `void PauseRequest(FBackgroundHttpRequestPtr Request);`
- L57 _public prototype_ `void ResumeRequest(FBackgroundHttpRequestPtr Request);`
- L58 _public prototype_ `void CancelRequest(FBackgroundHttpRequestPtr Request);`
- L61 _public prototype_ `static bool HandleRequirementsCheck();`
- L65 _public prototype_ `static bool HandleConfigRulesSettings();` — Returns true if the ConfigRules settings allow us to use this feature or false if it should be disabled based on those settings. Also cleans up work if appropriate based on settings.
- L68 _public member_ `static const FString BackgroundHTTPWorkID;` — Used to identify/schedule BackgroundHTTP work through our UEDownloadWorker
- L71 _protected prototype_ `void UpdateRequestProgress();`
- L73 _protected prototype_ `FAndroidBackgroundHttpRequestPtr FindRequestByDestinationLocation(const FString& DestinationLocation);`
- L74 _protected prototype_ `void HandlePendingCompletes();`
- L76 _protected prototype_ `void HandleJavaWorkerReconciliation();`
- L78 _protected prototype_ `const FString GetFullFileNameForDownloadDescriptionList() const;`
- L81 _protected prototype_ `void Java_OnWorkerStart(FString WorkID, jobject UnderlyingWorker);` — Handlers for our download progressing in the underlying java implementation so that we can bubble it up to UE code.
- L82 _protected prototype_ `void Java_OnWorkerStop(FString WorkID, jobject UnderlyingWorker);`
- L83 _protected prototype_ `void Java_OnDownloadProgress(jobject UnderlyingWorker, FString DestinationLocation, int64_t TotalBytesWritten, int64_t BytesWrittenSinceLastCall);`
- L84 _protected prototype_ `void Java_OnDownloadComplete(jobject UnderlyingWorker, FString DestinationLocation, bool bWasSuccess);`
- L85 _protected prototype_ `void Java_OnDownloadMetrics(jobject UnderlyingWorker, FString DestinationLocation, int64_t TotalBytesDownloaded, int64_t DownloadDuration, int64_t DownloadStartTimeUTC, int64_t DownloadEndTimeUTC);`
- L86 _protected prototype_ `void Java_OnAllDownloadsComplete(jobject UnderlyingWorker, bool bDidAllRequestsSucceed);`
- L87 _protected prototype_ `void Java_OnTick(JNIEnv* Env, jobject UnderlyingWorker);`
- L92 _protected prototype_ `void ForceCompleteAllUnderlyingJavaActiveRequestsWithError();` — Helper function that completes any un-completed requests in the underlying java tracking layer so that they will complete on the next Tick. Mostly used to help when the underlying java error hits a failure. Ensures when any request isn't actually completed when called
- L96 _protected prototype_ `bool HasUnderlyingJavaCompletedRequest(FBackgroundHttpRequestPtr Request);` — Helper function to determine if a background http request was completed in the underlying layer but is still in our ActiveRequests lists as its pending being a complete being sent on our game thread tick
- L97 _protected prototype_ `bool HasUnderlyingJavaCompletedRequest(FAndroidBackgroundHttpRequestPtr Request);`
- L100 _protected prototype_ `void MarkUnderlyingJavaRequestAsCompleted(FBackgroundHttpRequestPtr Request, bool bSuccess = true );` — Flag our underlying request as completed in a thread-safe way as this needs to be able to called on the background worker thread or game thread
- L101 _protected prototype_ `void MarkUnderlyingJavaRequestAsCompleted(FAndroidBackgroundHttpRequestPtr Request, bool bSuccess = true);`
- L105 _protected member_ `TArray<FString> RequestsToPauseByID_GT;` — Array used to store Pause/Resume/Cancel requests in a thread-safe non-locking way. This way we can utilize the _Java lists in our Java_OnTick without worrying about blocking the java thread
- L106 _protected member_ `TArray<FString> RequestsToPauseByID_Java;`
- L107 _protected member_ `TArray<FString> RequestsToResumeByID_GT;`
- L108 _protected member_ `TArray<FString> RequestsToResumeByID_Java;`
- L109 _protected member_ `TArray<FString> RequestsToCancelByID_GT;`
- L110 _protected member_ `TArray<FString> RequestsToCancelByID_Java;`
- L114 _protected member_ `volatile int32 bHasPendingCompletes;` — Used to flag if we have any downloads completed in our ActiveRequests list that are completed in java but waiting to send their completion handler on the GameThread
- L118 _protected member_ `volatile int32 bIsModifyingPauseList;` — Used to ensure that we can skip past the Pause/Resume/Cancel sections if one of the threads is using them Don't want to just use RWLocks as we can't block the WorkerThread
- L119 _protected member_ `volatile int32 bIsModifyingResumeList;`
- L120 _protected member_ `volatile int32 bIsModifyingCancelList;`
- L123 _protected member_ `volatile int32 bHasPendingExpectedWorkStart;` — Tracks if we are expecting a worker to start
- L126 _protected member_ `volatile int32 bShouldForceWorkerRequeue;` — If for some reason we should force requeuing all active work even if there are no current PendingDownloadRequests
- L131 _protected member_ `volatile int32 bWorkerHadTerminalFinish;` — If we need to reconcile the state of our underlying requests as we have terminally finished our work and want to make sure all work is correctly set to finish.
- L134 _protected prototype_ `void HandleRequestsWaitingOnJavaThreadsafety();` — Rechecks any _GT lists to try and move them to _Java lists if its safe to do so
- L136 _protected prototype_ `void OnNetworkConnectionChanged(ENetworkConnectionType ConnectionType);`
- L137 _protected member_ `FDelegateHandle OnNetworkConnectionChangedDelegateHandle;`
- L139 _protected member_ `int32 CellularPreference = 0;`
- L150 _protected prototype_ `static const FString LexToString(EAndroidBackgroundDownloadConfigRulesSetting Setting);`
- L151 _protected prototype_ `static EAndroidBackgroundDownloadConfigRulesSetting LexParseString(const FString* Setting);`
- L153 _protected prototype_ `static EAndroidBackgroundDownloadConfigRulesSetting GetAndroidBackgroundDownloadConfigRulesSetting();`
- L156 _protected member_ `static const FString AndroidBackgroundDownloadConfigRulesSettingKey;` — Key in ConfigRules to use to load the value of the EAndroidBackgroundDownloadConfigRulesSetting
- L186 _protected member_ `FAndroidBackgroundHTTPManagerDefaultLocalizedText AndroidBackgroundHTTPManagerDefaultLocalizedText;`
- L215 _private member_ `static FJavaClassInfo JavaInfo;`
- L225 _private member_ `TOptional<FJobStopData> JobStopData;`
- L230 _protected member_ `static volatile int32 bHasManagerScheduledBGWork;` — We only want to respond to certain broadcast java-side work if we have scheduled BGWork otherwise it could be stale work from a previous executables run that would look like an error state (Requests we haven't queued yet, etc)

#### enum `FAndroidPlatformBackgroundHttpManager::EAndroidBackgroundDownloadConfigRulesSetting`  
`enum class EAndroidBackgroundDownloadConfigRulesSetting : uint8`  
_L142-148_
- desc: Used to determine the state of AndroidBackgroundHTTP in our configrules
- L144 _public enumerator_ `Unknown` — Either the value was not set, or was set to something besides these expected values
- L145 _public enumerator_ `Enabled` — Enabled in config rules
- L146 _public enumerator_ `Disabled` — Disabled in our config rules.
- L147 _public enumerator_ `Count` — Count of enum values

#### struct `FAndroidPlatformBackgroundHttpManager::FAndroidBackgroundHTTPManagerDefaultLocalizedText`  
`struct FAndroidBackgroundHTTPManagerDefaultLocalizedText`  
_L161-184_
- desc: Since our manager could be loaded before UObjects, we have to manually parse some default PolyglotTextData from special .ini entries This struct hold that data and handles some simple parsing for us
- L163 _public prototype_ `FAndroidBackgroundHTTPManagerDefaultLocalizedText();`
- L165 _public member_ `FPolyglotTextData DefaultNotificationText_Title;`
- L166 _public member_ `FPolyglotTextData DefaultNotificationText_Content;`
- L167 _public member_ `FPolyglotTextData DefaultNotificationText_Complete;`
- L168 _public member_ `FPolyglotTextData DefaultNotificationText_Cancel;`
- L169 _public member_ `FPolyglotTextData DefaultNotificationText_NoInternet;`
- L170 _public member_ `FPolyglotTextData DefaultNotificationText_AirplaneMode;`
- L171 _public member_ `FPolyglotTextData DefaultNotificationText_DataSaverEnabled;`
- L172 _public member_ `FPolyglotTextData DefaultNotificationText_WaitingForCellular;`
- L173 _public member_ `FPolyglotTextData DefaultNotificationText_Approve;`
- L176 _public prototype_ `void InitFromIniSettings(const FString& ConfigFileName);`
- L180 _private prototype_ `void ParsePolyglotTextItem(FPolyglotTextData& TextDataOut, const FString& LocTextKey, TArray<FString>& TextEntryList);` — Fills out a FPolyglotTextData with data from the supplied text entry parsed from the config.ini
- L183 _private prototype_ `void ForceValidPolyglotText(FPolyglotTextData& TextDataOut, const FString& DebugPolyglotTextName);` — Helper that Checks for valid Polyglot text, and if it fails sets up a PolyglotText item that will pass IsValid() but represents a failed parse.

#### struct `FAndroidPlatformBackgroundHttpManager::FJavaClassInfo`  
`struct FJavaClassInfo`  
_L191-213_
- desc: struct holding all our Java class, method, and field information in one location. Must call initialize on this before it is useful. Future calls to Initialize will not recalculate information
- L193 _public member_ `bool bHasInitialized = false;`
- L195 _public member_ `jclass UEDownloadWorkerClass;`
- L196 _public member_ `jclass DownloadDescriptionClass;`
- L198 _public member_ `jmethodID GameThreadIsActive;`
- L200 _public member_ `jmethodID CreateArrayStaticMethod;` — Necessary JNI methods we will need to create our DownloadDescriptions
- L201 _public member_ `jmethodID WriteDownloadDescriptionListToFileMethod;`
- L202 _public member_ `jmethodID CreateDownloadDescriptionFromJsonMethod;`
- L204 _public prototype_ `void Initialize();`
- L206 _public function_ `FJavaClassInfo() : UEDownloadWorkerClass(0) , DownloadDescriptionClass(0) , GameThreadIsActive(0) , CreateArrayStaticMethod(0) , WriteDownloadDescriptionListToFileMethod(0)`

#### struct `FAndroidPlatformBackgroundHttpManager::FJobStopData`  
`struct FJobStopData`  
_L217-224_
- L219 _public member_ `FDateTime StartTime = FDateTime::UtcNow();`
- L220 _public member_ `int32 LastReportedSecs = 0;`
- L221 _public function_ `double GetWaitTimeInSeconds() const`

#### class `FAndroidNativeDownloadWorkerParameterKeys`  
`class FAndroidNativeDownloadWorkerParameterKeys`  
_L236-269_
- desc: WARNING: These values MUST stay in sync with their values in DownloadWorkerParameterKeys.java!
- L239 _public member_ `static const FString DOWNLOAD_DESCRIPTION_LIST_KEY;`
- L240 _public member_ `static const FString DOWNLOAD_MAX_CONCURRENT_REQUESTS_KEY;`
- L242 _public member_ `static const FString NOTIFICATION_CHANNEL_ID_KEY;`
- L243 _public member_ `static const FString NOTIFICATION_CHANNEL_NAME_KEY;`
- L244 _public member_ `static const FString NOTIFICATION_CHANNEL_IMPORTANCE_KEY;`
- L246 _public member_ `static const FString NOTIFICATION_ID_KEY;`
- L247 _public member_ `static const int NOTIFICATION_DEFAULT_ID_KEY;`
- L249 _public member_ `static const FString CELLULAR_HANDLE_KEY;`
- L251 _public member_ `static const FString NOTIFICATION_CONTENT_TITLE_KEY;`
- L252 _public member_ `static const FString NOTIFICATION_CONTENT_TEXT_KEY;`
- L253 _public member_ `static const FString NOTIFICATION_CONTENT_CANCEL_DOWNLOAD_TEXT_KEY;`
- L254 _public member_ `static const FString NOTIFICATION_CONTENT_NO_INTERNET_TEXT_KEY;`
- L255 _public member_ `static const FString NOTIFICATION_CONTENT_AIRPLANE_MODE_TEXT_KEY;`
- L256 _public member_ `static const FString NOTIFICATION_CONTENT_DATA_SAVER_ENABLED_TEXT_KEY;`
- L257 _public member_ `static const FString NOTIFICATION_CONTENT_COMPLETE_TEXT_KEY;`
- L258 _public member_ `static const FString NOTIFICATION_CONTENT_WAITING_FOR_CELLULAR_TEXT_KEY;`
- L259 _public member_ `static const FString NOTIFICATION_CONTENT_APPROVE_TEXT_KEY;`
- L261 _public member_ `static const FString NOTIFICATION_RESOURCE_CANCEL_ICON_NAME;`
- L262 _public member_ `static const FString NOTIFICATION_RESOURCE_CANCEL_ICON_TYPE;`
- L263 _public member_ `static const FString NOTIFICATION_RESOURCE_CANCEL_ICON_PACKAGE;`
- L265 _public member_ `static const FString NOTIFICATION_RESOURCE_SMALL_ICON_NAME;`
- L266 _public member_ `static const FString NOTIFICATION_RESOURCE_SMALL_ICON_TYPE;`
- L267 _public member_ `static const FString NOTIFICATION_RESOURCE_SMALL_ICON_PACKAGE;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Online` (scope `UE`)
- L26 _namespace_ `namespace Download` (scope `UE::Online`)
- L26 _namespace_ `namespace Android` (scope `UE::Online::Download`)
- L271 _typedef_ `typedef TSharedPtr<FAndroidPlatformBackgroundHttpManager, ESPMode::ThreadSafe> FAndroidPlatformBackgroundHttpManagerPtr;`

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidPlatformBackgroundHttpModularFeatureWrapper.h` (Public)


#### class `FAndroidPlatformBackgroundHttpModularFeatureWrapper`  
`class FAndroidPlatformBackgroundHttpModularFeatureWrapper : public IBackgroundHttpModularFeature`  
_L18-39_
- inherits: `IBackgroundHttpModularFeature`
- desc: Re-routes our modular feature calls to our AndroidFetch BackgroundHttp
- L24 _public prototype_ `virtual void Initialize() override;`
- L25 _public prototype_ `virtual void Shutdown() override;`
- L26 _public prototype_ `virtual FBackgroundHttpManagerPtr CreatePlatformBackgroundHttpManager() override;`
- L27 _public prototype_ `virtual FBackgroundHttpRequestPtr ConstructBackgroundRequest() override;`
- L28 _public prototype_ `virtual FBackgroundHttpResponsePtr ConstructBackgroundResponse(int32 ResponseCode, const FString& TempFilePath) override;`
- L29 _public prototype_ `virtual FString GetDebugModuleName() const override;`
- L34 _public prototype_ `void RegisterAsModularFeature();` — Handles registering / unregistering as a modular feature when appropriate If requirements are not supported we will fail to register and thus fallthrough to generic behaviour
- L35 _public prototype_ `void UnregisterAsModularFeature();`
- L38 _public prototype_ `static bool AreRequirementsSupported();` — If we actually support everything needed to use this feature

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidPlatformBackgroundHttpRequest.h` (Public)


#### class `FAndroidPlatformBackgroundHttpRequest`  
`class FAndroidPlatformBackgroundHttpRequest : public FBackgroundHttpRequestImpl`  
_L13-56_
- inherits: `FBackgroundHttpRequestImpl`
- desc: Contains implementation of Android specific background http requests
- L17 _public prototype_ `FAndroidPlatformBackgroundHttpRequest();`
- L18 _public function_ `virtual ~FAndroidPlatformBackgroundHttpRequest()`
- L20 _public prototype_ `virtual void PauseRequest() override;`
- L21 _public prototype_ `virtual void ResumeRequest() override;`
- L22 _public prototype_ `virtual void CancelRequest() override;`
- L24 _public prototype_ `FString ToJSon() const;`
- L26 _public prototype_ `FString GetDestinationLocation() const;`
- L28 _public prototype_ `void UpdateDownloadProgress(int64_t TotalDownloaded, int64_t DownloadedSinceLastUpdate);`
- L29 _public prototype_ `void SendDownloadProgressUpdate();`
- L32 _private prototype_ `int GetPriorityAsAndroidPriority() const;`
- L37 _private member_ `static const FStringView URLKey;` — NOTE: These must match the keys used in the DownloadDescription.java file in The AndroidBackgoundService module! We use these keys to convert our request into a DownloadDescription on the java side through JSON serialization!
- L38 _private member_ `static const FStringView RequestIDKey;`
- L39 _private member_ `static const FStringView DestinationLocationKey;`
- L40 _private member_ `static const FStringView MaxRetryCountKey;`
- L41 _private member_ `static const FStringView IndividualURLRetryCountKey;`
- L42 _private member_ `static const FStringView RequestPriorityKey;`
- L43 _private member_ `static const FStringView GroupIDKey;`
- L44 _private member_ `static const FStringView bHasCompletedKey;`
- L45 _private member_ `static const FStringView bIsPausedKey;`
- L46 _private member_ `static const FStringView TotalBytesNeededKey;`
- L49 _private member_ `mutable FString DestinationLocation;`
- L50 _private member_ `volatile int32 bIsPaused;`
- L51 _private member_ `volatile int32 bIsCompleted;`
- L52 _private member_ `volatile int64 DownloadProgress;`
- L53 _private member_ `volatile int64 DownloadProgressSinceLastUpdateSent;`

#### Free symbols / members of external scopes

- L58 _typedef_ `typedef TSharedPtr<class FAndroidPlatformBackgroundHttpRequest, ESPMode::ThreadSafe> FAndroidBackgroundHttpRequestPtr;`

### `Plugins/Online/Android/AndroidFetchBackgroundDownload/Source/AndroidFetchBackgroundDownload/Public/AndroidPlatformBackgroundHttpResponse.h` (Public)


#### class `FAndroidPlatformBackgroundHttpResponse`  
`class FAndroidPlatformBackgroundHttpResponse : public FBackgroundHttpResponseImpl`  
_L11-17_
- inherits: `FBackgroundHttpResponseImpl`
- desc: Contains implementation of some common functions that don't vary between implementation
- L16 _public prototype_ `FAndroidPlatformBackgroundHttpResponse(int32 ResponseCode, const FString& TempContentFilePath);` — Provide constructor to create an already
