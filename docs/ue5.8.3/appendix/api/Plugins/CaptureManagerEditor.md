# Plugins / CaptureManagerEditor

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor`
- headers: 22; symbols: 443
- symbol kinds: class=24, delegate=13, enum=6, enumerator=15, function=23, member=127, namespace=19, prototype=203, struct=13
- PrivateDependencyModuleNames: CaptureDataConverter, CaptureDataCore, CaptureManagerSettings, CaptureManagerStyle, CaptureManagerTakeMetadata, CaptureManagerUnrealEndpoint, CaptureUtils, ContentBrowser, Engine, ImageCore, InputCore, LiveLinkCapabilities, LiveLinkDevice, LiveLinkEditor, LiveLinkHub, NamingTokens, OutputLog, Projects, Settings, Slate, SlateCore, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, EditorStyle

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/IngestJob.h` (Private)


#### class `UE::CaptureManager::FIngestJob`  
`class FIngestJob`  
_L13-91_
- L53 _public prototype_ `FIngestJob( FGuid InCaptureDeviceId, FTakeId InTakeId, FTakeMetadata InTakeMetadata, EIngestCapability_ProcessConfig InPipelineConfig, FSettings InSettings );`
- L61 _public prototype_ `const FGuid& GetGuid() const;`
- L62 _public prototype_ `FGuid GetCaptureDeviceId() const;`
- L63 _public prototype_ `FTakeId GetTakeId() const;`
- L64 _public prototype_ `const FTakeMetadata& GetTakeMetadata() const;`
- L65 _public prototype_ `EIngestCapability_ProcessConfig GetPipelineConfig() const;`
- L66 _public prototype_ `const FSettings& GetSettings() const;`
- L67 _public prototype_ `FProcessingState GetProcessingState() const;`
- L68 _public prototype_ `double GetProgress() const;`
- L70 _public prototype_ `void SetSettings(FSettings Settings);`
- L71 _public prototype_ `void SetProcessingState(FProcessingState ProcessingState);`
- L72 _public prototype_ `void SetProgress(double Progress);`
- L75 _private member_ `const FGuid JobGuid;`
- L76 _private member_ `const FGuid CaptureDeviceId;`
- L77 _private member_ `const FTakeId TakeId;`
- L78 _private member_ `const FTakeMetadata TakeMetadata;`
- L79 _private member_ `const EIngestCapability_ProcessConfig PipelineConfig;`
- L81 _private member_ `mutable FCriticalSection CriticalSection;`
- L83 _private member_ `FSettings Settings;`
- L86 _private member_ `std::atomic<double> Progress = 0.0;`
- L90 _private member_ `FText ProcessingStateMessage;`

#### enum `UE::CaptureManager::FIngestJob::EProcessingState`  
`enum class EProcessingState : uint32`  
_L16-22_
- L18 _public enumerator_ `Pending = 1`
- L19 _public enumerator_ `Running = 2`
- L20 _public enumerator_ `Complete = 4`
- L21 _public enumerator_ `Aborted = 8`

#### struct `UE::CaptureManager::FIngestJob::FProcessingState`  
`struct FProcessingState`  
_L24-28_
- L26 _public member_ `EProcessingState State;`
- L27 _public member_ `FText Message;`

#### struct `UE::CaptureManager::FIngestJob::FSettings`  
`struct FSettings`  
_L30-51_
- L46 _public member_ `FString WorkingDirectory;`
- L47 _public member_ `FString DownloadFolder;`
- L48 _public member_ `FVideoSettings VideoSettings;`
- L49 _public member_ `FAudioSettings AudioSettings;`
- L50 _public member_ `FString UploadHostName;`

#### struct `UE::CaptureManager::FIngestJob::FSettings::FVideoSettings`  
`struct FVideoSettings`  
_L32-38_
- L35 _public member_ `FString FileNamePrefix;`

#### struct `UE::CaptureManager::FIngestJob::FSettings::FAudioSettings`  
`struct FAudioSettings`  
_L40-44_
- L43 _public member_ `FString FileNamePrefix;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/IngestJobExecutor.h` (Private)


#### class `UE::CaptureManager::FIngestJobExecutor`  
`class FIngestJobExecutor : public FRunnable, public TSharedFromThis<FIngestJobExecutor>`  
_L13-71_
- inherits: `FRunnable,TSharedFromThis<FIngestJobExecutor>`
- L19 _public prototype_ `DECLARE_DELEGATE(FOnComplete);`
- L20 _public prototype_ `DECLARE_DELEGATE_TwoParams(FJobProcessingStateChanged, FGuid, FIngestJob::EProcessingState);`
- L22 _public prototype_ `static TSharedRef<FIngestJobExecutor> Create( FString InExecutorName, TSharedRef<FIngestJobQueue> InProcessingQueue, FOnComplete InOnComplete, FJobProcessingStateChanged InJobProcessingStateChanged );`
- L29 _public prototype_ `FIngestJobExecutor( FPrivateToken InPrivateToken, FString InExecutorName, TSharedRef<FIngestJobQueue> InProcessingQueue, FOnComplete InOnComplete, FJobProcessingStateChanged InJobProcessingStateChanged );`
- L37 _public prototype_ `~FIngestJobExecutor();`
- L39 _public prototype_ `FIngestJobExecutor(const FIngestJobExecutor&) = delete;`
- L40 _public prototype_ `FIngestJobExecutor& operator=(const FIngestJobExecutor&) = delete;`
- L42 _public prototype_ `FIngestJobExecutor(FIngestJobExecutor&&) = delete;`
- L43 _public prototype_ `FIngestJobExecutor operator=(FIngestJobExecutor&&) = delete;`
- L45 _public prototype_ `virtual bool Init() override;`
- L46 _public prototype_ `virtual uint32 Run() override;`
- L47 _public prototype_ `virtual void Stop() override;`
- L48 _public prototype_ `virtual void Exit() override;`
- L50 _public prototype_ `void CancelForDevice(const FGuid& InDeviceId);`
- L59 _private prototype_ `TUniquePtr<FIngestJobExecutor::FRunIngestContext> RunIngest(TSharedRef<FIngestJob> InJob, TSharedRef<TPromise<void>> InPromise);`
- L61 _private member_ `FCriticalSection CriticalSection;`
- L62 _private member_ `FString ExecutorName;`
- L63 _private member_ `TSharedRef<FIngestJobQueue> ProcessingQueue;`
- L64 _private member_ `TUniquePtr<FIngestJobExecutor::FRunIngestContext> RunIngestProcessContext;`
- L65 _private member_ `FOnComplete Complete;`
- L66 _private member_ `FJobProcessingStateChanged JobProcessingStateChanged;`
- L68 _private member_ `std::atomic<bool> bIsRunning;`
- L69 _private member_ `std::atomic<bool> bStopRequested;`
- L70 _private member_ `TUniquePtr<FRunnableThread> Thread;`

#### struct `UE::CaptureManager::FIngestJobExecutor::FPrivateToken`  
`struct FPrivateToken`  
_L16-16_
- L16 _public prototype_ `struct FPrivateToken`

#### struct `UE::CaptureManager::FIngestJobExecutor::FRunIngestContext`  
`struct FRunIngestContext`  
_L53-57_
- L55 _public member_ `TStrongObjectPtr<ULiveLinkDevice> Device;`
- L56 _public member_ `TStrongObjectPtr<UIngestCapability_ProcessHandle> ProcessHandle;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE(FOnComplete);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FJobProcessingStateChanged, FGuid, FIngestJob::EProcessingState);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/IngestJobProcessor.h` (Private)


#### class `UE::CaptureManager::FIngestJobProcessor`  
`class FIngestJobProcessor: public TSharedFromThis<FIngestJobProcessor>`  
_L13-66_
- inherits: `TSharedFromThis<FIngestJobProcessor>`
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FJobsAdded, TArray<TSharedRef<FIngestJob>>);`
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FJobsRemoved, TArray<FGuid>);`
- L25 _public prototype_ `DECLARE_DELEGATE_TwoParams(FJobProcessingStateChanged, FGuid, FIngestJob::EProcessingState);`
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam(FProcessingStateChanged, EProcessingState);`
- L28 _public prototype_ `static TSharedRef<FIngestJobProcessor> MakeInstance(int32 NumExecutors);`
- L30 _public prototype_ `FIngestJobProcessor(FPrivateToken PrivateToken, int32 NumExecutors);`
- L31 _public prototype_ `~FIngestJobProcessor();`
- L33 _public prototype_ `int32 AddJobs(TArray<TSharedRef<FIngestJob>> IngestJobs);`
- L34 _public prototype_ `uint32 CountQueuedDeviceJobs(const FGuid InDeviceId, const uint32 InJobsToCountFlags);`
- L35 _public prototype_ `int32 RemoveJobsForDevice(const FGuid InDeviceId);`
- L36 _public prototype_ `int32 RemoveJobs(const TArray<FGuid>& JobGuidsToRemove);`
- L37 _public prototype_ `int32 RemoveAllJobs();`
- L38 _public prototype_ `bool SetJobSettings(const FGuid& JobGuid, FIngestJob::FSettings Settings);`
- L40 _public prototype_ `void StartProcessing();`
- L41 _public prototype_ `void StopProcessing();`
- L42 _public prototype_ `void StopProcessingForDevice(const FGuid& InDeviceId);`
- L44 _public prototype_ `bool IsProcessing() const;`
- L45 _public prototype_ `bool IsStopping() const;`
- L47 _public prototype_ `FJobsAdded& OnJobsAdded();`
- L48 _public prototype_ `FJobsRemoved& OnJobsRemoved();`
- L49 _public prototype_ `FJobProcessingStateChanged& OnJobProcessingStateChanged();`
- L50 _public prototype_ `FProcessingStateChanged& OnProcessingStateChanged();`
- L53 _private prototype_ `bool JobCanBeAdded(const FIngestJob& IngestJob) const;`
- L54 _private member_ `mutable FCriticalSection CriticalSection;`
- L56 _private member_ `const int32 NumExecutors;`
- L57 _private member_ `std::atomic<int32> NumExecutorsRunning = 0;`
- L58 _private member_ `TArray<TSharedRef<FIngestJobExecutor>> Executors;`
- L59 _private member_ `TSharedRef<FIngestJobQueue> ProcessingQueue;`
- L60 _private member_ `std::atomic<bool> bStopRequested = false;`
- L62 _private member_ `FJobsAdded JobsAdded;`
- L63 _private member_ `FJobsRemoved JobsRemoved;`
- L64 _private member_ `FJobProcessingStateChanged JobProcessingStateChanged;`
- L65 _private member_ `FProcessingStateChanged ProcessingStateChanged;`

#### struct `UE::CaptureManager::FIngestJobProcessor::FPrivateToken`  
`struct FPrivateToken`  
_L15-15_
- L15 _public prototype_ `struct FPrivateToken`

#### enum `UE::CaptureManager::FIngestJobProcessor::EProcessingState`  
`enum class EProcessingState`  
_L17-21_
- L19 _public enumerator_ `Processing`
- L20 _public enumerator_ `NotProcessing`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FJobsAdded, TArray<TSharedRef<FIngestJob>>);`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FJobsRemoved, TArray<FGuid>);`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FJobProcessingStateChanged, FGuid, FIngestJob::EProcessingState);`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FProcessingStateChanged, EProcessingState);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/IngestJobQueue.h` (Private)


#### class `UE::CaptureManager::FIngestJobQueue`  
`class FIngestJobQueue`  
_L10-37_
- L13 _public prototype_ `TArray<TSharedRef<FIngestJob>> AddJobs(TArray<TSharedRef<FIngestJob>> InIngestJobs);`
- L23 _public prototype_ `TSharedPtr<FIngestJob> ClaimFirstPending(FIngestJob::EProcessingState ProcessingState);` — Find the first pending job in the queue and return it. Since multiple executors may be calling this function at the same time, we must immediately mark the job with a new (non-pending) state, to prevent the same job getting picked up by multiple executors. @param ProcessingState The new state for the returned job (must not be Pending!).
- L25 _public prototype_ `TArray<FGuid> Remove(TArray<FGuid> GuidsToRemove);`
- L26 _public prototype_ `TArray<FGuid> RemoveAll();`
- L27 _public prototype_ `uint32 CountQueuedDeviceJobs(const FGuid InDeviceId, const uint32 InJobsToCountFlags);`
- L28 _public prototype_ `TArray<FGuid> RemoveJobsForDevice(const FGuid InDeviceId);`
- L30 _public prototype_ `bool SetJobSettings(const FGuid& JobGuid, FIngestJob::FSettings InSettings);`
- L33 _private prototype_ `bool JobCanBeAdded(const FIngestJob& JobToCheck) const;`
- L35 _private member_ `FCriticalSection CriticalSection;`
- L36 _private member_ `TArray<TSharedRef<FIngestJob>> Jobs;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/IngestJobSettingsManager.h` (Private)


#### class `UE::CaptureManager::FIngestJobSettingsManager`  
`class FIngestJobSettingsManager`  
_L12-25_
- L15 _public prototype_ `FIngestJobSettingsManager();`
- L17 _public prototype_ `void ApplyJobSpecificSettings(const FGuid& InJobGuid, const FIngestJob::FSettings& InSettings);`
- L18 _public prototype_ `TArray<TWeakObjectPtr<UIngestJobSettings>> GetSettings(const TArray<FGuid>& InJobGuids) const;`
- L20 _public prototype_ `int32 RemoveSettings(const TArray<FGuid>& InJobGuids);`
- L23 _private member_ `mutable FCriticalSection CriticalSection;`
- L24 _private member_ `TArray<TStrongObjectPtr<UIngestJobSettings>> Settings;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/IngestPipelineManager.h` (Private)


#### struct `UE::CaptureManager::FPipelineDetails`  
`struct FPipelineDetails`  
_L13-18_
- L15 _public member_ `FText DisplayName;`
- L16 _public member_ `FText ToolTip;`
- L17 _public member_ `EIngestCapability_ProcessConfig PipelineConfig;`

#### class `UE::CaptureManager::FIngestPipelineManager`  
`class FIngestPipelineManager`  
_L20-33_
- L23 _public prototype_ `FIngestPipelineManager();`
- L25 _public prototype_ `const TArray<FPipelineDetails>& GetPipelines() const;`
- L26 _public prototype_ `TOptional<FPipelineDetails> SelectPipelineByDisplayName(const FText& DisplayName);`
- L27 _public prototype_ `TOptional<FPipelineDetails> GetPipelineByDisplayName(const FText& DisplayName);`
- L28 _public prototype_ `const FPipelineDetails& GetSelectedPipeline() const;`
- L31 _private member_ `FPipelineDetails SelectedPipeline;`
- L32 _private member_ `TArray<FPipelineDetails> Pipelines;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/IngestManagement/UIngestJobSettings.h` (Private)


#### enum `EOutputImageFormat`  
`enum class EOutputImageFormat : uint8`  
_L13-17_
- reflection: `UENUM()`
- L15 _public enumerator_ `JPEG = 0 UMETA(DisplayName = "jpg")`
- L16 _public enumerator_ `PNG UMETA(DisplayName = "png")`

#### enum `EImagePixelFormat`  
`enum class EImagePixelFormat : uint8`  
_L20-24_
- reflection: `UENUM()`
- L22 _public enumerator_ `U8_BGRA = 0 UMETA(DisplayName = "U8 BGRA")`
- L23 _public enumerator_ `U8_Mono UMETA(DisplayName = "U8 Mono")`

#### enum `EImageRotation`  
`enum class EImageRotation : uint8`  
_L27-33_
- reflection: `UENUM()`
- L29 _public enumerator_ `None = 0 UMETA(DisplayName = "None")`
- L30 _public enumerator_ `CW_90 UMETA(DisplayName = "Clockwise 90°")`
- L31 _public enumerator_ `CW_180 UMETA(DisplayName = "Clockwise 180°")`
- L32 _public enumerator_ `CW_270 UMETA(DisplayName = "Clockwise 270°")`

#### enum `EAudioFormat`  
`enum class EAudioFormat : uint8`  
_L36-39_
- reflection: `UENUM()`
- L38 _public enumerator_ `WAV = 0 UMETA(DisplayName = "wav")`

#### class `UIngestJobSettings`  
`class UIngestJobSettings : public UObject`  
_L42-85_
- reflection: `UCLASS()`
- inherits: `UObject`
- L48 _public member_ `FGuid JobGuid;` — `UPROPERTY(AdvancedDisplay)`
- L51 _public member_ `FText DisplayName;` — `UPROPERTY(AdvancedDisplay)`
- L54 _public member_ `FDirectoryPath DownloadFolder;` — `UPROPERTY(AdvancedDisplay)`
- L57 _public member_ `FDirectoryPath WorkingDirectory;` — `UPROPERTY(Category = Conversion, EditAnywhere)`
- L60 _public member_ `EOutputImageFormat ImageFormat;` — `UPROPERTY(Category = "Output|Video", EditAnywhere)`
- L63 _public member_ `FString ImageFileNamePrefix;` — `UPROPERTY(Category = "Output|Video", EditAnywhere)`
- L66 _public member_ `EImagePixelFormat ImagePixelFormat;` — `UPROPERTY(Category = "Output|Video", EditAnywhere)`
- L69 _public member_ `EImageRotation ImageRotation;` — `UPROPERTY(Category = "Output|Video", EditAnywhere)`
- L72 _public member_ `EAudioFormat AudioFormat;` — `UPROPERTY(Category = "Output|Audio", EditAnywhere)`
- L75 _public member_ `FString AudioFileNamePrefix;` — `UPROPERTY(Category = "Output|Audio", EditAnywhere)`
- L78 _public member_ `FString UploadHostName;` — `UPROPERTY(Category = "Upload", EditAnywhere, Meta = (DisplayName = "Host Name", NoResetToDefault))`
- L80 _public prototype_ `UIngestJobSettings(const FObjectInitializer& ObjectInitializer);`
- L84 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/Scripting/ULiveLinkHubCaptureDevice.h` (Private)


#### struct `FLiveLinkHubTakeMetadata`  
`struct FLiveLinkHubTakeMetadata`  
_L14-27_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `TObjectPtr<UIngestCapability_TakeInformation> Metadata;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Metadata)`
- L22 _public member_ `int32 TakeId = 0;` — `UPROPERTY()`
- L26 _public member_ `FGuid SessionId;` — Identifies which start/stop session this information belongs to, to ensure the TakeId is still valid

#### struct `FLiveLinkHubFetchTakesResult`  
`struct FLiveLinkHubFetchTakesResult`  
_L30-39_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public member_ `TObjectPtr<UIngestCapability_ProcessResult> Status;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Result)`
- L38 _public member_ `TArray<FLiveLinkHubTakeMetadata> Takes;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Result)`

#### class `ULiveLinkHubCaptureDeviceFactory`  
`class ULiveLinkHubCaptureDeviceFactory : public UObject`  
_L42-50_
- reflection: `UCLASS()`
- inherits: `UObject`
- L49 _public prototype_ `ULiveLinkHubCaptureDevice* CreateDeviceByClass(FString InName, UClass* InDeviceClass, ULiveLinkDeviceSettings* Settings);` — `UFUNCTION(BlueprintCallable, Category = "Ingest | Creator")`

#### class `ULiveLinkHubCaptureDevice`  
`class ULiveLinkHubCaptureDevice : public UObject`  
_L53-85_
- reflection: `UCLASS()`
- inherits: `UObject`
- L58 _public prototype_ `ULiveLinkHubCaptureDevice();`
- L59 _public prototype_ `~ULiveLinkHubCaptureDevice();`
- L62 _public prototype_ `UIngestCapability_ProcessResult* Start(int32 InTimeoutSeconds);` — `UFUNCTION(BlueprintCallable, Category = Ingest)`
- L65 _public prototype_ `UIngestCapability_ProcessResult* Stop();` — `UFUNCTION(BlueprintCallable, Category = Ingest)`
- L68 _public prototype_ `UIngestCapability_ProcessResult* IngestTake(const FLiveLinkHubTakeMetadata& InTake, const UIngestCapability_Options* InConversionSettings) const;` — `UFUNCTION(BlueprintCallable, Category = Ingest)`
- L71 _public prototype_ `UIngestCapability_ProcessResult* DownloadTake(const FLiveLinkHubTakeMetadata& InTake, const FString& InDownloadDirectory) const;` — `UFUNCTION(BlueprintCallable, Category = Ingest)`
- L74 _public prototype_ `FLiveLinkHubFetchTakesResult FetchTakes() const;` — `UFUNCTION(BlueprintCallable, Category = Ingest)`
- L77 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)`
- L82 _private member_ `TPimplPtr<FImpl> ImplPtr;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/CaptureManagerPanelController.h` (Private)


#### class `FCaptureManagerPanelController`  
`class FCaptureManagerPanelController : public TSharedFromThis<FCaptureManagerPanelController, ESPMode::ThreadSafe>`  
_L38-93_
- inherits: `TSharedFromThis<FCaptureManagerPanelController,ESPMode::ThreadSafe>`
- L45 _public prototype_ `static TSharedPtr<FCaptureManagerPanelController> MakeInstance();`
- L47 _public prototype_ `explicit FCaptureManagerPanelController(FPrivateToken InPrivateToken);`
- L48 _public prototype_ `~FCaptureManagerPanelController();`
- L50 _public prototype_ `TSharedPtr<STakesView> GetTakesView() const;`
- L52 _public prototype_ `TSharedRef<UE::CaptureManager::SIngestJobProcessor> GetIngestJobProcessorWidget() const;`
- L53 _public prototype_ `TSharedRef<SWidget> GetIngestJobDetailsWidget() const;`
- L54 _public prototype_ `TSharedRef<UE::CaptureManager::FIngestPipelineManager> GetIngestPipelineManager() const;`
- L55 _public prototype_ `TSharedRef<UE::CaptureManager::FIngestJobSettingsManager> GetIngestJobSettingsManager() const;`
- L57 _public prototype_ `TObjectPtr<ULiveLinkDevice> GetCaptureDevice(FGuid InDeviceId) const;`
- L58 _public prototype_ `TArray<TObjectPtr<ULiveLinkDevice>> GetCaptureDevices() const;`
- L60 _public prototype_ `TSharedRef<FUpdateTakeListManager> GetUpdateTakeListManager() const;`
- L64 _private prototype_ `void OnDeviceSelectionChanged(ULiveLinkDevice* InDevice);`
- L65 _private prototype_ `void OnDeviceAdded(FGuid InDeviceId, ULiveLinkDevice* InDevice);`
- L66 _private prototype_ `void OnDeviceRemoved(FGuid InDeviceId, ULiveLinkDevice* InDevice);`
- L67 _private prototype_ `void OnReachableEvent(ELiveLinkDeviceConnectionStatus InStatus, FGuid InDeviceId);`
- L69 _private prototype_ `void CreateViews();`
- L70 _private prototype_ `void CreateIngestManagementViews();`
- L71 _private prototype_ `TSharedRef<IDetailsView> CreateIngestJobDetailsView();`
- L73 _private prototype_ `void OnJobsAdded(TArray<TSharedRef<UE::CaptureManager::FIngestJob>> IngestJobs);`
- L74 _private prototype_ `void OnJobsRemoved(const TArray<FGuid> JobGuids);`
- L75 _private prototype_ `void OnProcessingStateChanged(UE::CaptureManager::FIngestJobProcessor::EProcessingState ProcessingState);`
- L76 _private prototype_ `void OnFinishedEditingJobProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L77 _private prototype_ `void OnIngestJobSelectionChanged(const TArray<FGuid>& InJobGuids);`
- L79 _private member_ `TSharedPtr<FTakesView> TakesView;`
- L80 _private member_ `TMap<FGuid, TStrongObjectPtr<class UConnectionStatusChangedObject>> ConnectionStatusChangedDelegates;`
- L82 _private member_ `TMap<FGuid, bool> SourcesReachableMap;`
- L84 _private member_ `TSharedRef<UE::CaptureManager::FIngestPipelineManager> IngestPipelineManager;`
- L85 _private member_ `TSharedRef<UE::CaptureManager::FUnrealEndpointManager> UnrealEndpointManager;`
- L86 _private member_ `TSharedRef<UE::CaptureManager::FIngestJobSettingsManager> IngestJobSettingsManager;`
- L87 _private member_ `TSharedPtr<UE::CaptureManager::SIngestJobProcessor> IngestJobProcessorWidget;`
- L88 _private member_ `TSharedPtr<IDetailsView> IngestJobDetailsView;`
- L89 _private member_ `FDelegateHandle FinishedChangingPropertiesHandle;`
- L90 _private member_ `FDelegateHandle DeviceSelectionChangedHandle;`
- L92 _private member_ `TSharedPtr<FUpdateTakeListManager> UpdateTakeListManager;`

#### struct `FCaptureManagerPanelController::FPrivateToken`  
`struct FPrivateToken`  
_L42-42_
- desc: Private token only allows members or friends to call MakeShared
- L42 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace CaptureManager` (scope `UE`)
- L36 _namespace_ `namespace ESelectInfo`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/CaptureSourceVirtualAsset.h` (Private)


#### class `UCaptureSourceVirtualAsset`  
`class UCaptureSourceVirtualAsset : public UObject`  
_L10-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `FGuid Id;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/IngestJobSettingsCustomization.h` (Private)


#### class `FIngestJobSettingsCustomization`  
`class FIngestJobSettingsCustomization : public IDetailCustomization`  
_L8-19_
- inherits: `IDetailCustomization`
- L11 _public prototype_ `~FIngestJobSettingsCustomization();`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L18 _private prototype_ `FIngestJobSettingsCustomization();`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/LiveLinkHubCaptureManagerMode.h` (Private)


#### class `FLiveLinkHubCaptureManagerMode`  
`class FLiveLinkHubCaptureManagerMode : public FLiveLinkHubApplicationMode`  
_L24-44_
- inherits: `FLiveLinkHubApplicationMode`
- L27 _public prototype_ `FLiveLinkHubCaptureManagerMode(TSharedPtr<FLiveLinkHubApplicationBase> App);`
- L28 _public prototype_ `virtual ~FLiveLinkHubCaptureManagerMode();`
- L31 _public function_ `virtual FSlateIcon GetModeIcon() const override`
- L36 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetStatusBarWidgets_Impl() override;`
- L39 _private prototype_ `FText GetDiscoveredClientsText() const;`
- L42 _private member_ `TSharedRef<UE::CaptureManager::FUnrealEndpointManager> UnrealEndpointManager;`
- L43 _private member_ `TSharedPtr<class FCaptureManagerPanelController> CaptureManagerPanelController;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/SIngestJobProcessor.h` (Private)


#### class `UE::CaptureManager::SIngestJobProcessor`  
`class SIngestJobProcessor : public SCompoundWidget`  
_L15-73_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FSelectionChanged, const TArray<FGuid>&);`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FJobsAdded, TArray<TSharedRef<FIngestJob>>);`
- L20 _public prototype_ `DECLARE_DELEGATE_OneParam(FJobsRemoved, TArray<FGuid>);`
- L21 _public prototype_ `DECLARE_DELEGATE_TwoParams(FJobProcessingStateChanged, FGuid, FIngestJob::EProcessingState);`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FProcessingStateChanged, FIngestJobProcessor::EProcessingState);`
- L24 _public function_ `SLATE_BEGIN_ARGS(SIngestJobProcessor)`
- L25 _public function_ `SLATE_ARGUMENT_DEFAULT(int32, NumExecutors)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _public prototype_ `bool IsProcessing() const;`
- L31 _public prototype_ `int32 AddJobs(TArray<TSharedRef<FIngestJob>> Jobs);`
- L32 _public prototype_ `bool SetJobSettings(const FGuid& JobGuid, FIngestJob::FSettings JobSettings);`
- L33 _public prototype_ `uint32 CountQueuedDeviceJobs(const FGuid InDeviceId, const uint32 InJobsToCountFlags);`
- L34 _public prototype_ `int32 RemoveJobsForDevice(const FGuid InDeviceId);`
- L35 _public prototype_ `void Stop(const FGuid InDeviceId);`
- L37 _public prototype_ `FSelectionChanged& OnSelectionChanged();`
- L38 _public prototype_ `FJobsAdded& OnJobsAdded();`
- L39 _public prototype_ `FJobsRemoved& OnJobsRemoved();`
- L40 _public prototype_ `FJobProcessingStateChanged& OnJobProcessingStateChanged();`
- L41 _public prototype_ `FProcessingStateChanged& OnProcessingStateChanged();`
- L44 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedRef<FIngestJob> InJob, const TSharedRef<STableViewBase>& InOwnerTable);`
- L46 _private prototype_ `void HandleJobsAdded(TArray<TSharedRef<FIngestJob>> IngestJobs);`
- L47 _private prototype_ `void HandleJobsRemoved(TArray<FGuid> RemovedGuids);`
- L48 _private prototype_ `void HandleJobProcessingStateChanged(const FGuid JobGuid, FIngestJob::EProcessingState ProcessingState);`
- L49 _private prototype_ `void HandleProcessingStateChanged(FIngestJobProcessor::EProcessingState ProcessingState);`
- L50 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FIngestJob> InJobEntry, ESelectInfo::Type InSelectInfo);`
- L52 _private prototype_ `bool ClearButtonIsEnabled() const;`
- L53 _private prototype_ `bool StartButtonIsEnabled() const;`
- L54 _private prototype_ `bool StopButtonIsEnabled() const;`
- L56 _private prototype_ `static bool IsThirdPartyEncoderConfigured();`
- L57 _private prototype_ `EVisibility GetThirdPartyEncoderWarningVisibility() const;`
- L59 _private prototype_ `FReply OnClearButtonClicked();`
- L60 _private prototype_ `FReply OnStartButtonClicked();`
- L61 _private prototype_ `FReply OnStopButtonClicked();`
- L63 _private member_ `FCriticalSection CriticalSection;`
- L64 _private member_ `TArray<TSharedRef<FIngestJob>> IngestJobs;`
- L65 _private member_ `TSharedPtr<SListView<TSharedRef<FIngestJob>>> IngestJobsView;`
- L66 _private member_ `TSharedPtr<FIngestJobProcessor> IngestJobProcessor;`
- L68 _private member_ `FSelectionChanged SelectionChanged;`
- L69 _private member_ `FJobsAdded JobsAdded;`
- L70 _private member_ `FJobsRemoved JobsRemoved;`
- L71 _private member_ `FJobProcessingStateChanged JobProcessingStateChanged;`
- L72 _private member_ `FProcessingStateChanged ProcessingStateChanged;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CaptureManager` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FSelectionChanged, const TArray<FGuid>&);`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FJobsAdded, TArray<TSharedRef<FIngestJob>>);`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FJobsRemoved, TArray<FGuid>);`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FJobProcessingStateChanged, FGuid, FIngestJob::EProcessingState);`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FProcessingStateChanged, FIngestJobProcessor::EProcessingState);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/SIngestSelectableUnrealEndpoint.h` (Private)


#### class `SIngestSelectableUnrealEndpoint`  
`class SIngestSelectableUnrealEndpoint : public SCompoundWidget`  
_L10-37_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SIngestSelectableUnrealEndpoint)`
- L14 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_END_ARGS() SIngestSelectableUnrealEndpoint();`
- L18 _public prototype_ `~SIngestSelectableUnrealEndpoint();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`
- L23 _private prototype_ `TArray<TSharedRef<UE::CaptureManager::FUnrealEndpointInfo>> GetLatestEndpointInfos();`
- L24 _private prototype_ `void SetEndpointInfos(TArray<TSharedRef<UE::CaptureManager::FUnrealEndpointInfo>> InEndpointInfos);`
- L25 _private prototype_ `void UpdateTargetEndpointInfo();`
- L26 _private prototype_ `void OnPropertyChanged();`
- L28 _private member_ `TSharedRef<UE::CaptureManager::FUnrealEndpointManager> UnrealEndpointManager;`
- L29 _private member_ `TArray<TSharedRef<UE::CaptureManager::FUnrealEndpointInfo>> EndpointInfos;`
- L30 _private member_ `TSharedPtr<UE::CaptureManager::FUnrealEndpointInfo> TargetEndpointInfo;`
- L32 _private member_ `TSharedPtr<FString> TargetHostName;`
- L33 _private member_ `FString LocalHostName;`
- L34 _private member_ `TSharedPtr<SComboBox<TSharedRef<UE::CaptureManager::FUnrealEndpointInfo>>> ComboBox;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L36 _private member_ `FDelegateHandle EndpointsChangedDelegateHandle;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/SStatusBarView.h` (Private)


#### class `SStatusBarView`  
`class SStatusBarView : public SCompoundWidget`  
_L7-29_
- inherits: `SCompoundWidget`
- L10 _public function_ `SLATE_BEGIN_ARGS(SStatusBarView)`
- L13 _public prototype_ `virtual ~SStatusBarView() override;`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, FName InStatusBarId);`
- L17 _public prototype_ `void UpdateConnectionState(bool InState);`
- L20 _private prototype_ `TSharedRef<SWidgetDrawer> MakeWidgetDrawer(FName StatusBarId);`
- L22 _private prototype_ `FText GetConnectionStateText() const;`
- L23 _private prototype_ `FText GetStatusToolTip() const;`
- L24 _private prototype_ `FSlateColor GetStatusColor() const;`
- L26 _private member_ `TSharedPtr<SWidgetDrawer> WidgetDrawer;`
- L28 _private member_ `bool IsConnected;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/TUniqueObjectPtr.h` (Private)


#### class `TUniqueObjectPtr`  
`template<class T> class TUniqueObjectPtr`  
_L11-81_
- L17 _public function_ `TUniqueObjectPtr() : Object(nullptr)`
- L22 _public function_ `TUniqueObjectPtr(T* InObject) : Object(InObject)`
- L27 _public function_ `~TUniqueObjectPtr()`
- L37 _public prototype_ `TUniqueObjectPtr(const TUniqueObjectPtr<T>& InOther) = delete;`
- L38 _public prototype_ `TUniqueObjectPtr<T>& operator=(const TUniqueObjectPtr<T>& InOther) = delete;`
- L40 _public prototype_ `TUniqueObjectPtr(TUniqueObjectPtr<T>&& InOther) = default;`
- L41 _public prototype_ `TUniqueObjectPtr<T>& operator=(TUniqueObjectPtr<T>&& InOther) = default;`
- L43 _public function_ `const T& operator*() const`
- L48 _public function_ `T& operator*()`
- L53 _public function_ `const T* operator->() const`
- L58 _public function_ `T* operator->()`
- L63 _public function_ `T* Get()`
- L68 _public function_ `const T* Get() const`
- L73 _public function_ `bool IsValid() const`
- L80 _private member_ `TStrongObjectPtr<T> Object;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/TakeThumbnail.h` (Private)


#### class `FTakeThumbnail`  
`class FTakeThumbnail : public FGCObject`  
_L8-46_
- inherits: `FGCObject`
- L11 _public member_ `FString ThumbnailPath;`
- L13 _public member_ `TSharedPtr<FSlateBrush> SlateBrush;`
- L14 _public member_ `TObjectPtr<class UTexture2D> Texture = nullptr;`
- L15 _public member_ `bool IsLoaded = false;`
- L17 _public function_ `FTakeThumbnail()`
- L24 _public function_ `FTakeThumbnail(UTexture2D* InTexture)`
- L31 _public function_ `virtual ~FTakeThumbnail()`
- L37 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L42 _public function_ `virtual FString GetReferencerName() const override`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/TakeThumbnailRenderer.h` (Private)


#### class `UTakeThumbnailRenderer`  
`class UTakeThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L13-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L18 _public prototype_ `virtual bool CanVisualizeAsset(UObject* InObject) override;`
- L19 _public prototype_ `virtual void Draw(UObject* InObject, int32 InX, int32 InY, uint32 InWidth, uint32 InHeight, FRenderTarget* InRenderTarget, FCanvas* InCanvas, bool bInAdditionalViewFamily) override;`
- L20 _public prototype_ `virtual void BeginDestroy() override;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/TakeVirtualAsset.h` (Private)


#### class `UTakeVirtualAsset`  
`class UTakeVirtualAsset : public UObject`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public function_ `UTakeVirtualAsset()`
- L18 _public function_ `UTakeVirtualAsset(FGuid InCaptureDeviceId, UE::CaptureManager::FTakeId InTakeId, FTakeMetadata InMetadata) : CaptureDeviceId(InCaptureDeviceId) , TakeId(InTakeId) , Metadata(MoveTemp(InMetadata))`
- L25 _public member_ `FGuid CaptureDeviceId;`
- L26 _public member_ `UE::CaptureManager::FTakeId TakeId;`
- L27 _public member_ `FTakeMetadata Metadata;`
- L28 _public member_ `FTakeThumbnail Thumbnail;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/TakesView.h` (Private)


#### class `STakesView`  
`class STakesView : public SCompoundWidget`  
_L35-78_
- inherits: `SCompoundWidget`
- L38 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnAddTakesToIngestQueue, const TArray<TObjectPtr<UTakeVirtualAsset>>&, const UIngestJobSettings&);`
- L39 _public prototype_ `DECLARE_DELEGATE(FOnRefreshTakes);`
- L41 _public function_ `SLATE_BEGIN_ARGS(STakesView)`
- L42 _public prototype_ `SLATE_ARGUMENT(FAssetPickerConfig, TakesPickerConfig) SLATE_EVENT(FOnAddTakesToIngestQueue, OnAddTakesToIngestQueue) SLATE_EVENT(FOnRefreshTakes, OnRefreshTakes) SLATE_END_ARGS() STakesView();`
- L48 _public prototype_ `~STakesView() = default;`
- L50 _public prototype_ `void Construct( const FArguments& InArgs, TSharedRef<UE::CaptureManager::FIngestPipelineManager> InIngestPipelineManager, TSharedRef<UE::CaptureManager::FIngestJobSettingsManager> IngestJobsSettingsManager, TUniquePtr<FGetCurrentSelectionDelegate> GetCurrentSelectionDelegate );`
- L56 _public prototype_ `void SetAddToQueueButtonEnabled(bool bIsEnabled);`
- L57 _public prototype_ `void UpdateTakeListStarted();`
- L58 _public prototype_ `void UpdateTakeListFinished();`
- L61 _private prototype_ `FReply OnRefreshButtonClicked();`
- L62 _private prototype_ `FReply OnAddToQueueButtonClicked();`
- L63 _private prototype_ `TSharedRef<SWidget> OnGeneratePipelineNameWidget(TSharedRef<FText> InText);`
- L64 _private prototype_ `void OnPipelineSelectionChanged(TSharedPtr<FText> InText, ESelectInfo::Type InSelectType);`
- L65 _private prototype_ `TArray<TObjectPtr<UTakeVirtualAsset>> GetSelectedTakeAssets() const;`
- L67 _private member_ `TUniquePtr<FGetCurrentSelectionDelegate> GetCurrentSelectionDelegate;`
- L68 _private member_ `TSharedPtr<SPositiveActionButton> RefreshButton;`
- L69 _private member_ `FOnRefreshTakes OnRefreshTakes;`
- L70 _private member_ `TSharedPtr<SPositiveActionButton> AddToQueueButton;`
- L71 _private member_ `FOnAddTakesToIngestQueue OnAddTakesToIngestQueue;`
- L72 _private member_ `TSharedPtr<SHorizontalBox> LoadingBox;`
- L74 _private member_ `TSharedPtr<UE::CaptureManager::FIngestPipelineManager> IngestPipelineManager;`
- L75 _private member_ `TArray<TSharedRef<FText>> PipelineNames;`
- L76 _private member_ `UE::CaptureManager::FPipelineDetails CurrentPipeline;`
- L77 _private member_ `TSharedPtr<UE::CaptureManager::FIngestJobSettingsManager> IngestJobSettingsManager;`

#### class `FTakesView`  
`class FTakesView`  
_L80-117_
- L83 _public prototype_ `FTakesView(TWeakPtr<FCaptureManagerPanelController> InController);`
- L85 _public prototype_ `void CaptureDeviceStarted(FGuid InCaptureDeviceId);`
- L86 _public prototype_ `void CaptureDeviceStopped(FGuid InCaptureDeviceId);`
- L87 _public prototype_ `void CaptureDeviceAdded(ULiveLinkDevice* InDevice);`
- L88 _public prototype_ `void CaptureDeviceRemoved(ULiveLinkDevice* InDevice);`
- L89 _public prototype_ `void DeviceSelectionChanged(ULiveLinkDevice* InDevice);`
- L91 _public member_ `TSharedPtr<STakesView> TakesTileView;`
- L93 _private prototype_ `void CreateTakesView();`
- L94 _private member_ `TWeakPtr<FCaptureManagerPanelController> PanelController;`
- L96 _private member_ `TMap<FGuid, TArray<TUniqueObjectPtr<UTakeVirtualAsset>>> CaptureDeviceTakesMap;`
- L97 _private member_ `TWeakObjectPtr<ULiveLinkDevice> SelectedItem;`
- L99 _private member_ `FRefreshAssetViewDelegate RefreshTakesViewDelegate;`
- L100 _private member_ `FSyncToAssetsDelegate SyncToDevicesDelegate;`
- L102 _private prototype_ `TArray<FAssetData> CreateTakeAssetsDataForCaptureDevice(TOptional<FString> InCaptureDeviceName = TOptional<FString>());`
- L103 _private prototype_ `TArray<FAssetData> CreateTakeAssetsData(const TArray<TObjectPtr<UTakeVirtualAsset>>& InSelectedCaptureDevicesTakesArray);`
- L105 _private prototype_ `void AddTakesToIngestQueue(const TArray<TObjectPtr<UTakeVirtualAsset>>& InTakeAssets, const UIngestJobSettings& InJobPreset);`
- L106 _private prototype_ `void Refresh();`
- L107 _private prototype_ `void RefreshSingleDevice(TObjectPtr<ULiveLinkDevice> InDevice);`
- L108 _private prototype_ `void RefreshAllDevices();`
- L109 _private prototype_ `void UpdateTakeListCallback(TArray<UE::CaptureManager::FTakeId> InTakeIds, FGuid InCaptureDeviceId);`
- L110 _private prototype_ `void ResetTakesCache(FGuid InCaptureDeviceId);`
- L112 _private prototype_ `TArray<TUniqueObjectPtr<UTakeVirtualAsset>> MakeTakeObjects(FGuid InCaptureDeviceId, TOptional<TArray<UE::CaptureManager::FTakeId>> InTakeIds = TOptional<TArray<UE::CaptureManager::FTakeId>>());`
- L114 _private prototype_ `TOptional<FTakeThumbnail> CreateThumbnail(const FTakeThumbnailData& InThumbnailData);`
- L116 _private prototype_ `FName MakeUniqueTakeName(FTakeMetadata TakeInfo, UPackage* Package);`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace CaptureManager` (scope `UE`)
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAddTakesToIngestQueue, const TArray<TObjectPtr<UTakeVirtualAsset>>&, const UIngestJobSettings&);`
- L39 _delegate_ `DECLARE_DELEGATE(FOnRefreshTakes);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Private/UI/UpdateTakeListManager.h` (Private)


#### class `FUpdateTakeListManager`  
`class FUpdateTakeListManager`  
_L13-39_
- L21 _public prototype_ `static TSharedPtr<FUpdateTakeListManager> Create();`
- L23 _public prototype_ `FUpdateTakeListManager(FPrivate InToken);`
- L24 _public prototype_ `~FUpdateTakeListManager();`
- L26 _public prototype_ `void UpdateTakeListForDevice(FGuid InDeviceId, FIngestUpdateTakeListCallback InCallback);`
- L36 _private prototype_ `static void UpdateTakeListForDevice_Private(FQueueRunnerContext InContext);`
- L38 _private member_ `UE::CaptureManager::TQueueRunner<FQueueRunnerContext> QueueRunner;`

#### struct `FUpdateTakeListManager::FPrivate`  
`struct FPrivate`  
_L17-17_
- L17 _public prototype_ `struct FPrivate`

#### struct `FUpdateTakeListManager::FQueueRunnerContext`  
`struct FQueueRunnerContext`  
_L30-34_
- L32 _public member_ `FGuid DeviceId;`
- L33 _public member_ `FIngestUpdateTakeListCallback Callback;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerEditor/Public/CaptureManagerEditorModule.h` (Public)


#### class `FCaptureManagerEditorModule`  
`class FCaptureManagerEditorModule : public IModuleInterface, public ILiveLinkHubApplicationModeFactory`  
_L10-19_
- inherits: `IModuleInterface,ILiveLinkHubApplicationModeFactory`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public prototype_ `virtual TSharedRef<FLiveLinkHubApplicationMode> CreateLiveLinkHubAppMode(TSharedPtr<class FLiveLinkHubApplicationBase> InApp) override;`
