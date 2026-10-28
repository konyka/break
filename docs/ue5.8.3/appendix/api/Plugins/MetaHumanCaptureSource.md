# Plugins / MetaHumanCaptureSource

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource`
- headers: 33; symbols: 887
- symbol kinds: class=39, delegate=13, enum=10, enumerator=34, function=19, macro=6, member=345, namespace=8, prototype=362, struct=34, typedef=17
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor, CameraCalibrationCore, CaptureDataUtils, DesktopWidgets, ImageWriteQueue, InputCore, Json, MetaHumanCaptureData, MetaHumanCaptureProtocolStack, MetaHumanCore, MetaHumanCoreEditor, MetaHumanFaceContourTracker, MetaHumanPipeline, MetaHumanPipelineCore, NNE, OodleDataCompression, RenderCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine, ImgMedia, MetaHumanCaptureUtils

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/AssetDefinitions/AssetDefinition_MetaHumanCaptureSource.h` (Private)


#### class `UAssetDefinition_MetaHumanCaptureSource`  
`class UAssetDefinition_MetaHumanCaptureSource : public UAssetDefinitionDefault`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/CubicCameraSystemIngest.h` (Private)


#### class `FCubicCameraSystemIngest`  
`class FCubicCameraSystemIngest : public FFileFootageIngest`  
_L12-80_
- inherits: `FFileFootageIngest`
- L17 _public prototype_ `FCubicCameraSystemIngest(const FString& InInputDirectory, bool bInShouldCompressDepthFiles, bool bInCopyImagesToProject, EMetaHumanCaptureDepthPrecisionType InDepthPrecision, EMetaHumanCaptureDepthResolutionType InDepthResolution);`
- L23 _public prototype_ `virtual ~FCubicCameraSystemIngest();`
- L25 _public prototype_ `virtual void RefreshTakeListAsync(TCallback<void> InCallback) override;`
- L28 _public prototype_ `virtual FMetaHumanTakeInfo ReadTake(const FString& InFilePath, const FStopToken& InStopToken, TakeId InNewTakeId) override;`
- L29 _public prototype_ `virtual TResult<void, FMetaHumanCaptureError> CreateAssets(const FMetaHumanTakeInfo& InTakeInfo, const FStopToken& InStopToken, FCreateAssetsData& OutCreateAssetsData) override;`
- L33 _protected member_ `FString Type;`
- L35 _protected member_ `TMap<TakeId, TMap<FString, FCubicCameraInfo>> Cameras;`
- L36 _protected member_ `TMap<TakeId, const FCubicTakeInfo> TakeInfos;`
- L37 _protected member_ `bool bShouldCompressDepthFiles;`
- L38 _protected member_ `bool bCopyImagesToProject;`
- L39 _protected member_ `EMetaHumanCaptureDepthPrecisionType DepthPrecision = EMetaHumanCaptureDepthPrecisionType::Eightieth;`
- L40 _protected member_ `EMetaHumanCaptureDepthResolutionType DepthResolution = EMetaHumanCaptureDepthResolutionType::Full;`
- L42 _protected member_ `int32 CameraCount;`
- L54 _protected typedef_ `using FCameraContextMap = TMap<FString, FCameraContext>;`
- L56 _protected prototype_ `bool CheckResolutions(const FMetaHumanTakeInfo& InTakeInfo, const FCameraCalibration& InCalibrationInfo) const;`
- L58 _protected prototype_ `TResult<FCubicCameraSystemIngest::FCameraContextMap, FMetaHumanCaptureError> PrepareCameraContext(const int32 InTakeIndex, const FCubicTakeInfo::FCameraMap& InCubicCamerasInfo) const;`
- L61 _protected prototype_ `bool PrepareImageSequenceFilePath(const FString& InOriginalFramesPath, const uint32 InFrameCount, FString& OutFilePath, int32& OutOffset)const;`
- L66 _protected prototype_ `TResult<void, FMetaHumanCaptureError> PrepareAssetsForCreation(const FMetaHumanTakeInfo& InTakeInfo, const FCubicTakeInfo& InCubicTakeInfo, const TMap<FString, FCubicCameraInfo>& InTakeCameras, const FCameraContextMap& InTakeCameraContextMap, const FCameraCalibration& InDepthCameraCalibration, FCreateAssetsData& OutCreateAssetsData)const;`
- L74 _protected prototype_ `virtual TResult<void, FMetaHumanCaptureError> IngestFiles(const FStopToken& InStopToken, const FMetaHumanTakeInfo& InTakeInfo, const FCubicTakeInfo& InCubicTakeInfo, const FCameraContextMap& InCameraContextMap, const TMap<FString, FCubicCameraInfo>& InTakeCameras, FCameraCalibration& OutDepthCameraCalibration) = 0;` — override this method in derived classes to do the actual work of ingesting the files

#### struct `FCubicCameraSystemIngest::FCameraContext`  
`struct FCameraContext`  
_L44-52_
- L46 _public member_ `FTimecode Timecode;`
- L47 _public member_ `int32 FirstFrameIndex = 0;`
- L48 _public member_ `int32 FrameOffset = 0;`
- L49 _public member_ `FFrameRate FrameRate;`
- L50 _public member_ `FString FramesPath;`
- L51 _public member_ `int32 FrameCount = 0;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/CubicCameraSystemTakeMetadata.h` (Private)


#### class `FCubicCameraInfo`  
`class FCubicCameraInfo`  
_L11-17_
- L15 _public member_ `FString Name;`
- L16 _public member_ `FCameraCalibration Calibration;`

#### class `FCubicTakeInfo`  
`class FCubicTakeInfo`  
_L19-65_
- L39 _public typedef_ `using FCameraMap = TMap<FString, FCamera>;`
- L48 _public typedef_ `using FAudioArray = TArray<FAudio>;`
- L50 _public member_ `uint32 Version;`
- L51 _public member_ `FString Id;`
- L52 _public member_ `uint32 Take;`
- L53 _public member_ `FString Slate;`
- L54 _public member_ `FString ThumbnailPath;`
- L55 _public member_ `FDateTime Date;`
- L56 _public member_ `DeviceInfo DeviceInfo;`
- L57 _public member_ `FString CalibrationFilePath;`
- L59 _public member_ `FCameraMap CameraMap;`
- L60 _public member_ `FAudioArray AudioArray;`
- L62 _public member_ `FString TakeJsonFilePath;`
- L64 _public prototype_ `FString GetName() const;`

#### struct `FCubicTakeInfo::DeviceInfo`  
`struct DeviceInfo`  
_L22-27_
- L24 _public member_ `FString Model;`
- L25 _public member_ `FString Type;`
- L26 _public member_ `FString Id;`

#### struct `FCubicTakeInfo::FCamera`  
`struct FCamera`  
_L29-38_
- L31 _public member_ `FString UserId;`
- L32 _public member_ `TPair<uint32, uint32> FrameRange;`
- L33 _public member_ `float FrameRate = 0.0f;`
- L34 _public member_ `FString FramesPath;`
- L35 _public member_ `FString StartTimecode;`
- L36 _public member_ `FIntPoint Resolution = FIntPoint::NoneValue;`
- L37 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;`

#### struct `FCubicTakeInfo::FAudio`  
`struct FAudio`  
_L41-47_
- L43 _public member_ `FString UserId;`
- L44 _public member_ `FString StreamPath;`
- L45 _public member_ `float TimecodeRate = 0.0f;`
- L46 _public member_ `FString StartTimecode;`

#### class `FCubicCameraSystemTakeParser`  
`class FCubicCameraSystemTakeParser`  
_L68-91_
- L72 _public prototype_ `static bool ParseCalibrationFile(const FString& InFileName, const FStopToken& InStopToken, TMap<FString, FCubicCameraInfo>& OutCameras);`
- L73 _public prototype_ `static TOptional<FCubicTakeInfo> ParseTakeMetadataFile(const FString& InFileName, const FStopToken& InStopToken);`
- L75 _public prototype_ `static void CubicToMetaHumanTakeInfo( const FString& InFilePath, const FString InOutputDirectory, const FCubicTakeInfo& InCubicTakeInfo, const FStopToken& InStopToken, const TakeId InNewTakeId, const int32 InExpectedCameraCount, const FString& InDeviceType, FMetaHumanTakeInfo& OutTakeInfo, TMap<FString, FCubicCameraInfo>& OutTakeCameras );`
- L88 _private prototype_ `static void LoadCameras(const FCubicTakeInfo& InCubicTakeInfo, FMetaHumanTakeInfo& OutTakeInfo);`
- L89 _private prototype_ `static TArray<TSharedPtr<class FJsonValue>> ParseJsonArrayFromFile(const FString& InFilePath);`
- L90 _private prototype_ `static TSharedPtr<class FJsonObject> ParseJsonObjectFromFile(const FString& InFilePath);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/FileFootageIngest.h` (Private)


#### class `FFileFootageIngest`  
`class FFileFootageIngest : public FFootageIngest`  
_L15-67_
- inherits: `FFootageIngest`
- L20 _public prototype_ `FFileFootageIngest(const FString& InInputDirectory);`
- L21 _public prototype_ `virtual ~FFileFootageIngest();`
- L24 _public prototype_ `virtual void Startup(ETakeIngestMode InMode);`
- L25 _public prototype_ `virtual void Shutdown() override;`
- L26 _public prototype_ `virtual int32 GetNumTakes() const override;`
- L27 _public prototype_ `virtual TArray<TakeId> GetTakeIds() const override;`
- L28 _public prototype_ `virtual FMetaHumanTakeInfo GetTakeInfo(TakeId InId) const override;`
- L29 _public prototype_ `virtual void GetTakes(const TArray<TakeId>& InIdList, TPerTakeCallback<void> InCallback) override;`
- L30 _public prototype_ `virtual void RefreshTakeListAsync(TCallback<void> InCallback) override;`
- L31 _public prototype_ `virtual void CancelProcessing(const TArray<TakeId>& InIdList);`
- L35 _protected member_ `FString InputDirectory;`
- L37 _protected member_ `std::atomic_int32_t CurrId = 0;`
- L38 _protected member_ `mutable FCriticalSection TakeInfoCacheMutex;`
- L39 _protected member_ `TMap<TakeId, FMetaHumanTakeInfo> TakeInfoCache;`
- L40 _protected member_ `TMap<TakeId, FStopToken> TakeIngestStopTokens;`
- L42 _protected member_ `TUniquePtr<FAbortableAsyncTask> RefreshTakeListTask;`
- L45 _protected prototype_ `virtual FMetaHumanTakeInfo ReadTake(const FString& InFilePath, const FStopToken& InStopToken, TakeId InNewTakeId) = 0;` — Functions to be implemented by inheriting class
- L46 _protected prototype_ `virtual TResult<void, FMetaHumanCaptureError> CreateAssets(const FMetaHumanTakeInfo& InTakeInfo, const FStopToken& InStopToken, FCreateAssetsData& OutCreateAssetsData) = 0;`
- L48 _protected prototype_ `void AddTakeInfo(FMetaHumanTakeInfo&& InTakeInfo);`
- L49 _protected prototype_ `FMetaHumanTakeInfo GetCachedTakeInfo(TakeId InId) const;`
- L50 _protected prototype_ `int32 ClearTakeInfoCache();`
- L52 _protected member_ `UE::MetaHuman::Pipeline::FPipeline Pipeline;`
- L53 _protected member_ `int32 TakeIdInPipeline = INVALID_ID;`
- L55 _protected prototype_ `void FrameComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData, TakeId InId);`
- L56 _protected prototype_ `void ProcessComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData, TRetainedRef<TResult<void, FMetaHumanCaptureError>> OutResult);`
- L58 _protected prototype_ `TResult<void, FMetaHumanCaptureError> RunPipeline(const FStopToken& InStopToken, TakeId InId, bool bInShouldRunMultiThreaded);`
- L59 _protected prototype_ `void GetTakesProcessing(const TArray<TakeId>& InTakeIdList, TPerTakeCallback<void> InCallback, const FStopToken& InStopToken);`
- L63 _private prototype_ `void DeleteDataForTake(TakeId InTakeIndex);`
- L64 _private prototype_ `TakeId GenerateNewTakeId();`
- L66 _private prototype_ `TResult<void, FMetaHumanCaptureError> ReadTakeList(const FStopToken& InStopToken);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/FootageIngest.h` (Private)


#### class `FFootageIngest`  
`class FFootageIngest : public IFootageIngestAPI , public FTSTickerObjectBase`  
_L16-100_
- inherits: `IFootageIngestAPI,FTSTickerObjectBase`
- L21 _public prototype_ `FFootageIngest();`
- L22 _public prototype_ `virtual ~FFootageIngest();`
- L26 _public prototype_ `virtual void Startup(ETakeIngestMode InMode) override;`
- L28 _public prototype_ `virtual bool IsProcessing() const override;`
- L29 _public prototype_ `virtual void CancelProcessing(const TArray<TakeId>& InIdList) override;`
- L30 _public prototype_ `virtual bool IsCancelling() const override;`
- L31 _public prototype_ `virtual float GetTaskProgress(TakeId InId) const;`
- L32 _public prototype_ `virtual FText GetTaskName(TakeId InId) const;`
- L33 _public prototype_ `virtual void SetTargetPath(const FString& InTargetIngestDirectory, const FString& InTargetPackagePath) override;`
- L36 _public prototype_ `virtual bool Tick(float InDeltaTime) override;`
- L38 _public prototype_ `virtual FOnGetTakesFinished& OnGetTakesFinished() override;`
- L43 _protected function_ `template<typename Functor> void ExecuteFromGameThread(const FString& InName, Functor&& InFunctor)`
- L61 _protected prototype_ `void ProcessTakes(FAbortableAsyncTask::FTaskFunction InProcessTakesFunction);` — @brief Runs a function to process takes. This can be called by derived classes to run a function in either blocking or async modes. @param InTaskType The type of task to be executed. Used to call the appropriate delegates when the task finishes executing @param InProcessTakesFunction A callable to process takes. It receives an abort flag as a parameter that should be checked by implementations that indicates the user requested the task to be cancelled.
- L62 _protected prototype_ `static TOptional<FText> TakeDurationExceedsLimit(float InDurationInSeconds);`
- L69 _private prototype_ `void ProcessTakesFinished();` — @brief Called after a process takes task finishes, being it blocking or async. Calls delegates to notify observers that the task has finished
- L74 _protected member_ `FString TargetIngestBaseDirectory;`
- L75 _protected member_ `FString TargetIngestBasePackagePath;`
- L76 _protected member_ `ETakeIngestMode Mode;`
- L78 _protected member_ `TUniquePtr<FAbortableAsyncTask> ProcessTakesAsyncTask;`
- L80 _protected member_ `FOnGetTakesFinished OnGetTakesFinishedDelegate;`
- L82 _protected member_ `TMap<TakeId, std::atomic<float>> TakeProgress;`
- L83 _protected member_ `TMap<TakeId, std::atomic<int32>> TakeProgressFrameCount;`
- L84 _protected member_ `TMap<TakeId, std::atomic<int32>> TakeProgressTotalFrames;` — not defaulted to zero to prevent divide by zero - numbers should be set to real values before use
- L86 _protected member_ `mutable FCriticalSection TakeProcessNameMutex;`
- L87 _protected member_ `TMap<TakeId, FText> TakeProcessName;`
- L89 _protected member_ `bool bCancelAllRequested = false;`
- L91 _protected prototype_ `void RemoveTakeFromIngestCache(const TakeId InId);`
- L92 _protected prototype_ `void ClearTakesFromIngestCache();`
- L96 _protected member_ `mutable FCriticalSection CurrentIngestedTakeMutex;` — The Take cache for the current execution of GetTakesAsync
- L97 _protected member_ `TArray<FMetaHumanTake> CurrentIngestedTakes;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/HMCArchiveIngest.h` (Private)


#### class `FHMCArchiveIngest`  
`class FHMCArchiveIngest : public FStereoReconstructionSystemIngest`  
_L9-40_
- inherits: `FStereoReconstructionSystemIngest`
- L14 _public prototype_ `FHMCArchiveIngest(const FString& InInputDirectory, bool bInShouldCompressDepthFiles, bool bInCopyImagesToProject, TRange<float> InDepthDistance, EMetaHumanCaptureDepthPrecisionType InDepthPrecision, EMetaHumanCaptureDepthResolutionType InDepthResolution);`
- L22 _public prototype_ `virtual ~FHMCArchiveIngest();`
- L26 _private member_ `static constexpr int32 DepthSaveNodeCount = 4;`
- L27 _private member_ `static constexpr int32 MaxStandardHMCImageSize = 3145728;` — Technoprops resolution = 1536 * 2048
- L32 _protected prototype_ `virtual TResult<void, FMetaHumanCaptureError> IngestFiles(const FStopToken& InStopToken, const FMetaHumanTakeInfo& InTakeInfo, const FCubicTakeInfo& InCubicTakeInfo, const FCameraContextMap& InCameraContextMap, const TMap<FString, FCubicCameraInfo>& InTakeCameras, FCameraCalibration& OutDepthCameraCalibration) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/IFootageIngestAPI.h` (Private)


#### class `IFootageIngestAPI`  
`class IFootageIngestAPI : public FCommandHandler, public FCaptureEventSource`  
_L13-56_
- inherits: `FCommandHandler,FCaptureEventSource`
- L23 _public typedef_ `template<typename Type> using TCallback = TManagedDelegate<TResult<Type, FMetaHumanCaptureError>>;`
- L26 _public typedef_ `template<typename Type> using TPerTakeResult = TPair<TakeId, TResult<Type, FMetaHumanCaptureError>>;`
- L29 _public typedef_ `template<typename Type> using TPerTakeCallback = TManagedDelegate<TPerTakeResult<Type>>;`
- L31 _public prototype_ `virtual FOnGetTakesFinished& OnGetTakesFinished() = 0;`
- L33 _public prototype_ `virtual void Startup(ETakeIngestMode InMode = ETakeIngestMode::Async) = 0;`
- L34 _public prototype_ `virtual void SetTargetPath(const FString& InTargetIngestDirectory, const FString& InTargetPackagePath) = 0;`
- L35 _public prototype_ `virtual void Shutdown() = 0;`
- L37 _public prototype_ `virtual bool IsProcessing() const = 0;`
- L39 _public prototype_ `virtual bool IsCancelling() const = 0;`
- L40 _public prototype_ `virtual void CancelProcessing(const TArray<TakeId>& InIdList) = 0;`
- L43 _public prototype_ `virtual float GetTaskProgress(TakeId InId) const = 0;` — Returns the progress of the current task
- L44 _public prototype_ `virtual FText GetTaskName(TakeId InId) const = 0;`
- L46 _public prototype_ `virtual void RefreshTakeListAsync(TCallback<void> InCallback) = 0;`
- L47 _public prototype_ `virtual int32 GetNumTakes() const = 0;`
- L48 _public prototype_ `virtual TArray<TakeId> GetTakeIds() const = 0;`
- L49 _public prototype_ `virtual FMetaHumanTakeInfo GetTakeInfo(TakeId InId) const = 0;`
- L51 _public prototype_ `virtual void GetTakes(const TArray<TakeId>& InIdList, TPerTakeCallback<void> InCallback) = 0;`
- L53 _public prototype_ `virtual ~IFootageIngestAPI() = default;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE(FOnStartupFinished) DECLARE_DELEGATE_OneParam(FOnGetTakesFinished, const TArray<FMetaHumanTake>& InTakes) template<typename Type> using TCallback = TManagedDelegate<TResult<Type, FMetaHumanCaptureError>>;`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetTakesFinished, const TArray<FMetaHumanTake>& InTakes) template<typename Type> using TCallback = TManagedDelegate<TResult<Type, FMetaHumanCaptureError>>;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/LiveLinkFaceConnectionIngest.h` (Private)


#### class `FLiveLinkFaceConnectionIngest`  
`class FLiveLinkFaceConnectionIngest final : public FLiveLinkFaceIngestBase`  
_L10-111_
- inherits: `FLiveLinkFaceIngestBase`
- L15 _public prototype_ `FLiveLinkFaceConnectionIngest(const FString& InDeviceIPAddress, uint16 InDeviceControlPort, bool bInShouldCompressDepthFiles);`
- L22 _public prototype_ `virtual void Startup(ETakeIngestMode InMode) override;`
- L24 _public prototype_ `virtual void Shutdown() override;`
- L25 _public prototype_ `virtual void GetTakes(const TArray<TakeId>& InIdList, TPerTakeCallback<void> InCallback) override;`
- L26 _public prototype_ `virtual void RefreshTakeListAsync(TCallback<void> InCallback) override;`
- L29 _public prototype_ `const FString& GetTakesOriginDirectory() const override;`
- L31 _public prototype_ `virtual bool IsProcessing() const override;`
- L32 _public prototype_ `virtual void CancelProcessing(const TArray<TakeId>& InIdList) override;`
- L42 _private member_ `static constexpr int32 ConnectInterval = 5;` — Seconds
- L44 _private typedef_ `using FFilesMap = TMap<FString, TArray<FGetTakeMetadataResponse::FFileObject>>;`
- L45 _private typedef_ `using FExportMap = TMap<uint32, FString>;` — Take name
- L47 _private prototype_ `void OnProgressReport(const FString& InTakeName, float InProgress);`
- L48 _private prototype_ `void OnExportFinished(const FString& InTakeName, TProtocolResult<void> InResult);`
- L50 _private prototype_ `void OnControlClientDisconnected(const FString& InCause);`
- L52 _private prototype_ `FLiveLinkFaceTakeMetadata CreateTakeMetadata(const FGetTakeMetadataResponse::FTakeObject& InTake);`
- L53 _private prototype_ `FLiveLinkFaceVideoMetadata CreateVideoMetadata(const FGetTakeMetadataResponse::FVideoObject& InVideo);`
- L54 _private prototype_ `FLiveLinkFaceAudioMetadata CreateAudioMetadata(const FGetTakeMetadataResponse::FAudioObject& InAudio);`
- L56 _private prototype_ `void CancelAllExports();`
- L57 _private prototype_ `void CancelCleanup(const FString& InTakeName);`
- L59 _private prototype_ `void StartConnectTimer(bool bInInvokeDelay = false);`
- L60 _private prototype_ `void StopConnectTimer();`
- L61 _private prototype_ `void StartConnectTimer_GameThread(float InInvokeDelay);`
- L62 _private prototype_ `void StopConnectTimer_GameThread();`
- L63 _private prototype_ `void OnConnectTimer();`
- L65 _private prototype_ `void ConnectControlClient(FCommsRequestParams InParams);`
- L66 _private prototype_ `bool CheckIfTakeExists(const FString& InTakeName) const;`
- L67 _private prototype_ `TArray<TakeId> AddTakes(const TArray<FGetTakeMetadataResponse::FTakeObject>& InTakeObjects);`
- L69 _private prototype_ `TProtocolResult<TakeId> FindTakeIdByName(const FString& InTakeName) const;`
- L70 _private prototype_ `void RemoveExportByName(const FString& InTakeName);`
- L72 _private prototype_ `void FetchThumbnails(TArray<TakeId> InIdList);`
- L73 _private prototype_ `TArray<FString> GetTakeNamesByIds(TArray<TakeId> InTakeIds);`
- L75 _private prototype_ `void InvokeGetTakesCallbackFromGameThread();`
- L77 _private prototype_ `bool StartCaptureHandler(TSharedPtr<FBaseCommandArgs> InCommand);`
- L78 _private prototype_ `bool StopCaptureHandler(TSharedPtr<FBaseCommandArgs> InCommand);`
- L80 _private prototype_ `void ClearCachedTakesWithEvent();`
- L82 _private prototype_ `void RegisterForAllEvents();`
- L83 _private prototype_ `void OnEvent(TSharedPtr<FControlUpdate> InEvent);`
- L85 _private prototype_ `void AddTakeByName(const FString& InTakeName);`
- L86 _private prototype_ `void RemoveTakeByName(const FString& InTakeName);`
- L88 _private prototype_ `static bool TakeContainsFiles(const FGetTakeMetadataResponse::FTakeObject& Take, const TArray<FString>& FileNames);`
- L90 _private member_ `FString DeviceIPAddress;`
- L91 _private member_ `uint16 DeviceControlPort;`
- L93 _private member_ `FControlMessenger ControlMessenger;`
- L95 _private member_ `TUniquePtr<FExportClient> ExportClient;`
- L97 _private member_ `mutable FCriticalSection ExportMapMutex;`
- L98 _private member_ `FExportMap ExportMap;`
- L100 _private member_ `TArray<TakeId> CurrentTakeIdList;`
- L102 _private member_ `FFilesMap FilesTakeContainsMap;`
- L104 _private member_ `std::atomic<bool> bIsConnected;`
- L105 _private member_ `FTimerHandle ConnectionTimer;`
- L106 _private member_ `TQueueRunner<FCommsRequestParams> CommsThread;`
- L108 _private member_ `TPerTakeCallback<void> GetTakesCallback;`

#### struct `FLiveLinkFaceConnectionIngest::FCommsRequestParams`  
`struct FCommsRequestParams`  
_L37-40_
- L38 _public member_ `bool bForceFetchingTakeList = false;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/LiveLinkFaceFootageIngest.h` (Private)


#### class `FLiveLinkFaceIngestBase`  
`class FLiveLinkFaceIngestBase : public FFootageIngest`  
_L18-89_
- inherits: `FFootageIngest`
- L23 _public prototype_ `FLiveLinkFaceIngestBase(bool bInShouldCompressDepthFiles);`
- L26 _public prototype_ `virtual void Shutdown() override;`
- L27 _public prototype_ `virtual int32 GetNumTakes() const override;`
- L28 _public prototype_ `virtual TArray<TakeId> GetTakeIds() const override;`
- L29 _public prototype_ `virtual FMetaHumanTakeInfo GetTakeInfo(TakeId InId) const override;`
- L30 _public prototype_ `virtual void GetTakes(const TArray<TakeId>& InTakeIdList, TPerTakeCallback<void> InCallback) override;`
- L31 _public prototype_ `virtual void CancelProcessing(const TArray<TakeId>& InTakeIdList) override;`
- L34 _public prototype_ `virtual const FString& GetTakesOriginDirectory() const = 0;` — Returns the directory from where takes are ingested from. Used to derive the actual path in the Content folder to place the ingested files
- L48 _public prototype_ `virtual void GetTake(TakeId InTaskTakeId, FTakeConversionTaskInfo& OutTaskInfo);` — a virtual method to get an individual take
- L51 _protected prototype_ `static bool IsMetaHumanAnimatorTake(const FString& Directory, const FLiveLinkFaceTakeInfo& TakeInfo);`
- L53 _protected prototype_ `void GetTakesProcessing(const TArray<TakeId>& InTakeIdList, TPerTakeCallback<void> InCallback, const FStopToken& InStopToken);`
- L54 _protected prototype_ `int32 AddTakeInfo(FLiveLinkFaceTakeInfo&& InTakeInfo);`
- L55 _protected prototype_ `FLiveLinkFaceTakeInfo GetLiveLinkFaceTakeInfo(TakeId InId) const;`
- L56 _protected prototype_ `int32 ClearTakeInfoCache();`
- L57 _protected prototype_ `void RemoveTakeFromTakeCache(TakeId InId);`
- L58 _protected prototype_ `FString GetTakeIngestRelativePath(const FLiveLinkFaceTakeInfo& InTakeInfo) const;`
- L60 _protected prototype_ `TArray<FCreateAssetsData> PrepareTakeAssets_GameThread(const TArray<FLiveLinkFaceTakeDataConverter::FConvertResult>& InConvertResult, const TArray<FLiveLinkFaceTakeInfo>& InTakeInfoList);`
- L62 _protected prototype_ `FLiveLinkFaceTakeInfo ReadTake(const FString& CurrentDirectory);`
- L65 _protected member_ `std::atomic_int32_t CurrId = 0;`
- L67 _protected member_ `mutable FCriticalSection TakeInfoCacheMutex;`
- L68 _protected member_ `TMap<TakeId, FLiveLinkFaceTakeInfo> TakeInfoCache;`
- L69 _protected member_ `TMap<TakeId, FStopToken> TakeIngestStopTokens;`
- L70 _protected member_ `bool bShouldCompressDepthFiles;`
- L85 _private prototype_ `int32 CalculateBatchSize(int32 InTakesToProcess);` — ParallelFor uses Background Workers to parallelize its work for each take. We then instantiate 3 threads per each take and we wait until all 3 threads are done. This causes "deadlock" because no more threads can be started to start the per take work, because all take work is waiting for it to end. This function calculates the batch size based on how many threads are currently available. Proper solution would be to not wait until the per take job is finish and therefore remove ParallelFor and use regular for to execute everything. This work requires a redesign of this and all other class that would be affected by this change.
- L87 _private prototype_ `void DeleteDataForTake(TakeId InId);`
- L88 _private prototype_ `TakeId GenerateNewTakeId();`

#### struct `FLiveLinkFaceIngestBase::FTakeConversionTaskInfo`  
`struct FTakeConversionTaskInfo`  
_L37-45_
- desc: Utility struct to hold information on a take conversion task
- L39 _public member_ `FLiveLinkFaceTakeInfo TakeInfo;`
- L40 _public member_ `std::atomic<float> Progress;`
- L41 _public member_ `FLiveLinkFaceTakeDataConverter::FConvertResult Result;`
- L42 _public member_ `bool bCanceled = false;`
- L43 _public member_ `bool bHasErrors = false;`
- L44 _public member_ `FText ErrorText;`

#### class `FLiveLinkFaceArchiveIngest`  
`class FLiveLinkFaceArchiveIngest final : public FLiveLinkFaceIngestBase`  
_L94-115_
- inherits: `FLiveLinkFaceIngestBase`
- L99 _public prototype_ `FLiveLinkFaceArchiveIngest(const FString& InInputDirectory, bool bInShouldCompressDepthFiles);`
- L100 _public prototype_ `virtual ~FLiveLinkFaceArchiveIngest();`
- L103 _public prototype_ `virtual void Startup(ETakeIngestMode InMode) override;`
- L104 _public prototype_ `virtual void Shutdown() override;`
- L105 _public prototype_ `virtual void RefreshTakeListAsync(TCallback<void> InCallback) override;`
- L108 _public prototype_ `const FString& GetTakesOriginDirectory() const override;`
- L111 _private prototype_ `TResult<void, FMetaHumanCaptureError> ReadTakeList(const FStopToken& InStopToken);`
- L113 _private member_ `FString InputDirectory;`
- L114 _private member_ `TUniquePtr<FAbortableAsyncTask> RefreshTakeListTask;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/LiveLinkFaceMetadata.h` (Private)


#### struct `FLiveLinkFaceStaticFileNames`  
`struct FLiveLinkFaceStaticFileNames`  
_L9-18_
- L11 _public member_ `inline static const FString AudioMetadata = "au`
- L12 _public member_ `inline static const FString DepthData = "de`
- L13 _public member_ `inline static const FString DepthMetadata = "de`
- L14 _public member_ `inline static const FString FrameLog = "fr`
- L15 _public member_ `inline static const FString TakeMetadata = "ta`
- L16 _public member_ `inline static const FString Thumbnail = "th`
- L17 _public member_ `inline static const FString VideoMetadata = "vi`

#### struct `FLiveLinkFaceTakeMetadata`  
`struct FLiveLinkFaceTakeMetadata`  
_L20-41_
- L22 _public member_ `int32 Version;`
- L23 _public member_ `FString SlateName;`
- L24 _public member_ `FString AppVersion;`
- L25 _public member_ `FString DeviceModel;`
- L26 _public member_ `FString Subject;`
- L27 _public member_ `FString Identifier;`
- L28 _public member_ `FDateTime Date;`
- L29 _public member_ `int32 TakeNumber;`
- L30 _public member_ `int32 NumFrames;`
- L31 _public member_ `bool bIsCalibrated;`
- L33 _public prototype_ `FString MOVFileName() const;`
- L34 _public prototype_ `TArray<FString> GetMHAFileNames() const;`
- L35 _public prototype_ `TArray<FString> GetCommonFileNames() const;`
- L36 _public prototype_ `TArray<FString> GetARKitFileNames() const;`
- L39 _private prototype_ `FString CommonFileNamePrefix() const;`
- L40 _private prototype_ `TArray<FString> GetCalibratedBlendshapeFileNames() const;`

#### struct `FLiveLinkFaceVideoMetadata`  
`struct FLiveLinkFaceVideoMetadata`  
_L43-50_
- L45 _public member_ `FIntPoint Resolution;`
- L46 _public member_ `float JpegCompressionQuality;`
- L47 _public member_ `FString Quality;`
- L48 _public member_ `EMediaOrientation Orientation;`
- L49 _public member_ `double FrameRate;`

#### struct `FLiveLinkFaceOodleMetadata`  
`struct FLiveLinkFaceOodleMetadata`  
_L52-57_
- L54 _public member_ `FString Compressor;`
- L55 _public member_ `FString CompressionLevel;`
- L56 _public member_ `FString Version;`

#### struct `FLiveLinkFaceDepthMetadata`  
`struct FLiveLinkFaceDepthMetadata`  
_L59-75_
- L61 _public member_ `FIntPoint Resolution;`
- L62 _public member_ `FString Compression;`
- L63 _public member_ `FLiveLinkFaceOodleMetadata OodleInfo;` — If Compression == "Oodle"
- L64 _public member_ `EMediaOrientation Orientation;`
- L65 _public member_ `double FrameRate;`
- L66 _public member_ `float PixelSize;`
- L67 _public member_ `bool bShouldCompressFiles;`
- L70 _public member_ `TArray<float> LensDistortionLookupTable;` — Lens distortion info
- L71 _public member_ `TArray<float> InverseLensDistortionLookupTable;`
- L72 _public member_ `TArray<float> IntrinsicMatrix;`
- L73 _public member_ `FVector2D LensDistortionCenter;`
- L74 _public member_ `FVector2D IntrinsicMatrixReferenceDimensions;`

#### struct `FLiveLinkFaceAudioMetadata`  
`struct FLiveLinkFaceAudioMetadata`  
_L77-83_
- L79 _public member_ `int32 BitsPerChannel;`
- L80 _public member_ `int32 SampleRate;`
- L81 _public member_ `int32 ChannelsPerFrame;`
- L82 _public member_ `int32 FormatFlags;`

#### struct `FLiveLinkFaceTakeInfo`  
`struct FLiveLinkFaceTakeInfo`  
_L85-112_
- L88 _public member_ `FString TakeOriginDirectory;` — The path to the folder where the files for this take are
- L90 _public member_ `TakeId Id = INVALID_ID;`
- L92 _public member_ `TArray<uint8> RawThumbnailData;`
- L93 _public member_ `FLiveLinkFaceTakeMetadata TakeMetadata;`
- L94 _public member_ `FLiveLinkFaceVideoMetadata VideoMetadata;`
- L95 _public member_ `FLiveLinkFaceDepthMetadata DepthMetadata;`
- L96 _public member_ `FLiveLinkFaceAudioMetadata AudioMetadata;`
- L98 _public member_ `TArray<FText> Issues;`
- L100 _public prototype_ `FString GetTakeName() const;`
- L101 _public prototype_ `FString GetTakePath() const;`
- L102 _public prototype_ `FString GetMOVFilePath() const;`
- L103 _public prototype_ `FString GetDepthFilePath() const;`
- L104 _public prototype_ `FString GetFrameLogFilePath() const;`
- L105 _public prototype_ `FString GetCameraCalibrationFilePath() const;`
- L106 _public prototype_ `FString GetOutputDirectory(const FString& InTakesOriginDirectory) const;`
- L107 _public prototype_ `float GetTakeDurationInSeconds() const;`
- L110 _public prototype_ `FMetaHumanTakeInfo ConvertToMetaHumanTakeInfo(const FString& InTakesOriginDirectory) const;`

#### class `FLiveLinkFaceMetadataParser`  
`class FLiveLinkFaceMetadataParser`  
_L114-134_
- L117 _public prototype_ `static EMediaOrientation ParseOrientation(int32 InOrientation = 4);`
- L118 _public prototype_ `static bool ParseVideoMetadata(const FString& InTakeDirectory, FLiveLinkFaceVideoMetadata& OutVideoMetadata);`
- L119 _public prototype_ `static bool ParseDepthMetadata(const FString& InTakeDirectory, FLiveLinkFaceDepthMetadata& OutDepthMetadata);`
- L120 _public prototype_ `static bool ParseAudioMetadata(const FString& InTakeDirectory, FLiveLinkFaceAudioMetadata& OutAudioMetadata);`
- L121 _public prototype_ `static bool ParseTakeInfo(const FString& InTakeDirectory, FLiveLinkFaceTakeInfo& OutTakeInfo);`
- L122 _public prototype_ `static bool ParseThumbnail(const FString& InTakeDirectory, FLiveLinkFaceTakeInfo& OutTakeInfo);`
- L126 _private prototype_ `static TValueOrError<FLiveLinkFaceTakeMetadata, FMetaHumanCaptureError> ParseTakeMetadata(const TSharedPtr<FJsonObject> JsonObject);`
- L127 _private prototype_ `static TOptional<FMetaHumanCaptureError> ParseString(const TSharedPtr<FJsonObject> JsonObject, const FString& Key, FString &OutString);`
- L128 _private prototype_ `static TOptional<FMetaHumanCaptureError> ParseNumber(const TSharedPtr<FJsonObject> JsonObject, const FString& Key, int32 &OutNumber);`
- L129 _private prototype_ `static TOptional<FMetaHumanCaptureError> ParseBool(const TSharedPtr<FJsonObject> JsonObject, const FString& Key, bool &OutBool);`
- L130 _private prototype_ `static FMetaHumanCaptureError CreateErrorForMissingJsonKey(const FString& Key);`
- L132 _private prototype_ `static TArray<TSharedPtr<class FJsonValue>> ParseJsonArrayFromFile(const FString& InFilePath);`
- L133 _private prototype_ `static TSharedPtr<class FJsonObject> ParseJsonObjectFromFile(const FString& InFilePath);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/ResolutionResolver.h` (Private)


#### class `UE::MetaHuman::FResolutionResolver`  
`class FResolutionResolver`  
_L20-45_
- desc: Class used to determine and validate the image resolution for a set of Cubic camera data. Each time a camera is added to the resolver, the internal state is updated and will influence the result of the final Resolve() call. A collective value for the image resolution will only be returned if all of the cameras share the same image resolution.
- L36 _public prototype_ `TValueOrError<FIntPoint, EAddError> Add(const FCubicTakeInfo::FCamera& Camera);`
- L37 _public prototype_ `TValueOrError<FIntPoint, EResolveError> Resolve() const;`
- L40 _private prototype_ `TValueOrError<FIntPoint, EAddError> GetCameraResolution(const FCubicTakeInfo::FCamera& Camera) const;`
- L41 _private prototype_ `TValueOrError<FIntPoint, EAddError> GetResolutionFromSingleImage(const FString& InDirectoryPath) const;`
- L43 _private member_ `FIntPoint CommonResolution = FIntPoint::NoneValue;`
- L44 _private member_ `bool bAllEqual = true;`

#### enum `UE::MetaHuman::FResolutionResolver::EAddError`  
`enum class EAddError`  
_L23-29_
- L25 _public enumerator_ `FramesPathDoesNotExist`
- L26 _public enumerator_ `NoImagesFound`
- L27 _public enumerator_ `ImageLoadFailed`
- L28 _public enumerator_ `InvalidImageWrapper`

#### enum `UE::MetaHuman::FResolutionResolver::EResolveError`  
`enum class EResolveError`  
_L31-34_
- L33 _public enumerator_ `Mismatched`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/StereoReconstructionSystemIngest.h` (Private)


#### class `FStereoReconstructionSystemIngest`  
`class FStereoReconstructionSystemIngest : public FCubicCameraSystemIngest`  
_L9-29_
- inherits: `FCubicCameraSystemIngest`
- L15 _public prototype_ `FStereoReconstructionSystemIngest(const FString& InInputDirectory, bool bInShouldCompressDepthFiles, bool bInCopyImagesToProject, TRange<float> InDepthDistance, EMetaHumanCaptureDepthPrecisionType InDepthPrecision, EMetaHumanCaptureDepthResolutionType InDepthResolution);`
- L23 _public prototype_ `virtual ~FStereoReconstructionSystemIngest();`
- L27 _protected member_ `TRange<float> DepthDistance;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/CommandHandler.h` (Private)


#### class `FCommandHandler`  
`class FCommandHandler`  
_L8-28_
- L12 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FExecutor, TSharedPtr<FBaseCommandArgs>);` — Delegates can't accept move-only object therefore, instead of TUniquePtr we are using TSharedPtr
- L14 _public prototype_ `FCommandHandler() = default;`
- L15 _public prototype_ `virtual ~FCommandHandler() = default;`
- L17 _public prototype_ `bool Execute(TSharedPtr<FBaseCommandArgs> InCommandArgs);`
- L19 _public prototype_ `TArray<FString> GetCommands() const;`
- L22 _protected prototype_ `void RegisterCommand(const FString& InCommandName, FExecutor InExecutor);`
- L27 _private member_ `TMap<FString, FExecutor> Executors;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FExecutor, TSharedPtr<FBaseCommandArgs>);` — Delegates can't accept move-only object therefore, instead of TUniquePtr we are using TSharedPtr

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/ImageSequenceWriter.h` (Private)


#### class `IImageSequenceWriter`  
`class IImageSequenceWriter`  
_L9-18_
- L12 _public prototype_ `virtual bool Open(const FString& InDirPath) = 0;`
- L13 _public prototype_ `virtual bool Append(IMediaTextureSample* InDirPath) = 0;`
- L14 _public prototype_ `virtual void Close() = 0;`
- L15 _public prototype_ `virtual ~IImageSequenceWriter() = default;`
- L17 _public prototype_ `static TSharedPtr<IImageSequenceWriter, ESPMode::ThreadSafe> Create();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/IngestAssetCreator.h` (Private)


#### struct `FCreateAssetsData`  
`struct FCreateAssetsData`  
_L12-54_
- L48 _public member_ `TakeId TakeId;`
- L49 _public member_ `FString PackagePath;`
- L50 _public member_ `TArray<FViewData> Views;`
- L51 _public member_ `TArray<FAudioData> AudioClips;`
- L52 _public member_ `FCalibrationData Calibration;`
- L53 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;`

#### struct `FCreateAssetsData::FImageSequenceData`  
`struct FImageSequenceData`  
_L14-23_
- L16 _public member_ `FString Name;`
- L17 _public member_ `FString SequenceDirectory;`
- L18 _public member_ `double FrameRate = 0;`
- L19 _public member_ `TObjectPtr<class UImgMediaSource> Asset;`
- L20 _public member_ `bool bTimecodePresent = false;`
- L21 _public member_ `FTimecode Timecode = FTimecode(0, 0, 0, 0, false);`
- L22 _public member_ `FFrameRate TimecodeRate = FFrameRate(30, 1);`

#### struct `FCreateAssetsData::FViewData`  
`struct FViewData`  
_L25-29_
- L27 _public member_ `FImageSequenceData Video;`
- L28 _public member_ `FImageSequenceData Depth;`

#### struct `FCreateAssetsData::FAudioData`  
`struct FAudioData`  
_L31-38_
- L33 _public member_ `FString Name;`
- L34 _public member_ `FString WAVFile;`
- L35 _public member_ `TObjectPtr<USoundWave> Asset;`
- L36 _public member_ `TOptional<FTimecode> Timecode;`
- L37 _public member_ `TOptional<FFrameRate> TimecodeRate;`

#### struct `FCreateAssetsData::FCalibrationData`  
`struct FCalibrationData`  
_L40-46_
- L42 _public member_ `FString Name;`
- L43 _public member_ `FString CalibrationFile;`
- L44 _public member_ `TArray<FCameraCalibration> CalibrationData;`
- L45 _public member_ `TObjectPtr<UCameraCalibration> Asset;`

#### class `FIngestAssetCreator`  
`class FIngestAssetCreator`  
_L57-111_
- L60 _public typedef_ `using FPerTakeCallback = IFootageIngestAPI::TPerTakeCallback<void>;`
- L61 _public typedef_ `using FPerTakeResult = IFootageIngestAPI::TPerTakeResult<void>;`
- L63 _public prototype_ `static void CreateAssets_GameThread(TArray<FCreateAssetsData>& InOutCreateAssetDataList, TArray<FMetaHumanTake>& InOutTakeList, FPerTakeCallback InPerTakeCallback);`
- L67 _public prototype_ `static void RemoveAssetsByPath(const FString& InPackagePath);`
- L70 _public function_ `template<class TReturnType> static TReturnType* GetOrCreateAsset(const FString& InTargetPackagePath, const FString& InAssetName)`
- L76 _private member_ `static const FText AudioImportFailedText;`
- L78 _private prototype_ `static void CreateTakeAssets_GameThread(TArray<FCreateAssetsData>& InOutCreateAssetsData, TArray<FMetaHumanTake>& OutTakes, const FPerTakeCallback& InPerTakeCallback);`
- L82 _private prototype_ `static void VerifyIngestedData_GameThread(const TArray<FCreateAssetsData>& InCreateAssetsData, const TArray<FMetaHumanTake>& InTakes, const FPerTakeCallback& InPerTakeCallback);`
- L86 _private prototype_ `static bool CreateTakeAssetViews_GameThread(FCreateAssetsData& InCreateAssetDate, TArray<FMetaHumanTakeView>& OutViews);`
- L89 _private prototype_ `static TResult<void, FMetaHumanCaptureError> AssignAudioAsset(const TObjectPtr<UAssetImportTask>& InAssetImportTask, FMetaHumanTake& OutTake);`
- L90 _private prototype_ `static TResult<void, FMetaHumanCaptureError> AssignCalibrationAsset(const TObjectPtr<UAssetImportTask>& InAssetImportTask, FMetaHumanTake& OutTake);`
- L92 _private prototype_ `static TResult<void, FMetaHumanCaptureError> CheckCreatedTakeAssets_GameThread(const FCreateAssetsData& InCreateAssetsData);`
- L93 _private prototype_ `static TResult<void, FMetaHumanCaptureError> CheckCreatedTakeStruct_GameThread(const FMetaHumanTake& InCreatedTakeStruct, bool bInShouldContainAudio);`
- L95 _private prototype_ `static void DeleteFailedTakes(TArray<int32> InTakesToDelete, TArray<FMetaHumanTake>& OutTakeList, TArray<FCreateAssetsData>& OutCreateAssetDataList);`
- L99 _private prototype_ `static TResult<void, FMetaHumanCaptureError> CheckTakeAssets(const FMetaHumanTake& InTake, bool bInHasAudio);`
- L101 _private prototype_ `static UObject* GetAssetIfExists(const FString& InTargetPackagePath, const FString& InAssetName);`
- L104 _private function_ `template<class TReturnType> static TReturnType* GetAssetIfExists(const FString& InTargetPackagePath, const FString& InAssetName)`
- L109 _private prototype_ `static UObject* GetOrCreateAsset(const FString& InTargetPackagePath, const FString& InAssetName, UClass* InClass);`
- L110 _private prototype_ `static void PrepareSoundWave(const FMetaHumanTake& InMetaHumanTake, const UAssetImportTask* InAssetImportTask, USoundWave* OutSoundWave);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/LiveLinkFaceConnectionExportStreams.h` (Private)


#### class `FFileStream`  
`class FFileStream : public FBaseStream`  
_L7-40_
- inherits: `FBaseStream`
- L11 _public prototype_ `DECLARE_DELEGATE_TwoParams(FReportProgress, const FString& InTakeName, float InProgress);`
- L12 _public prototype_ `DECLARE_DELEGATE_TwoParams(FExportFinished, const FString& InTakeName, TProtocolResult<void> InResult);`
- L14 _public prototype_ `FFileStream(FString InBaseDir, FString InTakeName, uint64 InSize);`
- L16 _public prototype_ `virtual bool StartFile(const FString& InTakeName, const FString& InFileName) override;`
- L18 _public prototype_ `virtual bool ProcessData(const FString& InTakeName, const FString& InFileName, const TConstArrayView<uint8>& InData) override;`
- L19 _public prototype_ `virtual bool FinishFile(const FString& InTakeName, const FString& InFileName, const TStaticArray<uint8, 16>& InHash) override;`
- L21 _public prototype_ `virtual void Done(TProtocolResult<void> InResult) override;`
- L23 _public prototype_ `void SetExportFinished(FExportFinished InExportFinished);`
- L24 _public prototype_ `void SetProgressHandler(FReportProgress InReportProgress);`
- L28 _private prototype_ `void ReportProgressStep(const FString& InFileName, const uint32 InArrivedSize);`
- L30 _private member_ `FString BaseDir;`
- L31 _private member_ `FString TakeName;`
- L32 _private member_ `TUniquePtr<FArchive> Writer;`
- L33 _private member_ `TUniquePtr<FMD5> MD5Generator;`
- L35 _private member_ `uint64 TotalExportExpectedSize;`
- L36 _private member_ `uint64 TotalExportArrivedSize;`
- L38 _private member_ `FExportFinished OnExportFinished;`
- L39 _private member_ `FReportProgress OnReportProgress;`

#### class `FDataStream`  
`class FDataStream : public FBaseStream`  
_L42-63_
- inherits: `FBaseStream`
- L45 _public typedef_ `using FData = TArray<uint8>;`
- L47 _public prototype_ `DECLARE_DELEGATE_TwoParams(FFileExportFinished, const FString& InTakeName, TProtocolResult<FData> InDataResult);`
- L49 _public prototype_ `FDataStream();`
- L51 _public prototype_ `bool StartFile(const FString& InTakeName, const FString& InFileName) override;`
- L52 _public prototype_ `bool ProcessData(const FString& InTakeName, const FString& InFileName, const TConstArrayView<uint8>& InData) override;`
- L53 _public prototype_ `bool FinishFile(const FString& InTakeName, const FString& InFileName, const TStaticArray<uint8, 16>& InHash) override;`
- L55 _public prototype_ `void Done(TProtocolResult<void> InResult) override;`
- L57 _public prototype_ `void SetExportFinished(FFileExportFinished InFileExportFinished);`
- L61 _private member_ `FData Data;`
- L62 _private member_ `FFileExportFinished FileExportFinished;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_TwoParams(FReportProgress, const FString& InTakeName, float InProgress);`
- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FExportFinished, const FString& InTakeName, TProtocolResult<void> InResult);`
- L47 _delegate_ `DECLARE_DELEGATE_TwoParams(FFileExportFinished, const FString& InTakeName, TProtocolResult<FData> InDataResult);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/LiveLinkFaceTakeDataConverter.h` (Private)


#### class `FIngestTask`  
`class FIngestTask : public FNonAbandonableTask`  
_L11-37_
- inherits: `FNonAbandonableTask`
- L15 _public prototype_ `DECLARE_DELEGATE_TwoParams(FTaskHandler, const FIngestTask& InThisTask, const FStopToken& InStopToken);`
- L17 _public function_ `FIngestTask(int32 InId, FTaskHandler InTaskHandler, const FStopToken& InStopToken) : Id(InId) , TaskHandler(MoveTemp(InTaskHandler)) , StopToken(InStopToken)`
- L24 _public function_ `TStatId GetStatId() const`
- L29 _public function_ `void DoWork()`
- L34 _public member_ `int32 Id;`
- L35 _public member_ `FTaskHandler TaskHandler;`
- L36 _public member_ `const FStopToken& StopToken;`

#### class `FLiveLinkFaceTakeDataConverter`  
`class FLiveLinkFaceTakeDataConverter`  
_L39-154_
- L42 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnProgress, const float);`
- L44 _public typedef_ `using FOnFinished = TDelegate<void(TResult<void, FMetaHumanCaptureError>)>;`
- L47 _public prototype_ `virtual ~FLiveLinkFaceTakeDataConverter() = default;`
- L70 _public prototype_ `virtual FConvertResult Convert(const FStopToken& InStopToken);`
- L71 _public prototype_ `virtual bool Initialize(const FConvertParams& InConvertParams);`
- L73 _public function_ `FOnFinished& OnFinished()`
- L78 _public function_ `FOnProgress& OnProgress()`
- L85 _protected prototype_ `void ConvertMovToWav(const FIngestTask& InTask, const FStopToken& InStopToken);` — Steps to perform the task
- L86 _protected prototype_ `bool ConvertVideoToImageSequenceImplementation(const FIngestTask& InTask, const FStopToken& InStopToken);`
- L87 _protected member_ `double TotalProgressForImageSequence = 1.0;`
- L88 _protected prototype_ `void ConvertVideoToImageSequence(const FIngestTask& InTask, const FStopToken& InStopToken);`
- L89 _protected prototype_ `void ConvertVideoToDepth(const FIngestTask& InTask, const FStopToken& InStopToken);`
- L114 _protected prototype_ `void ExecuteAsyncTasks(const FStopToken& InStopToken);`
- L118 _protected prototype_ `void BuildVideoDepthSyncMap(const TArray<TPair<double, bool>>& InVideoFrameTimeInSeconds, const TArray<TPair<double, bool>>& InDepthFrameTimeInSeconds);` — Video - depth synchronization
- L121 _protected prototype_ `void NotifyProgress(float InProgress);`
- L123 _protected prototype_ `void NotifyFailure(FMetaHumanCaptureError InError);`
- L125 _protected prototype_ `void NotifySuccess();`
- L127 _protected prototype_ `void OnAsyncTaskProgressUpdate(const FIngestTask& InTask, float InAsyncTaskProgress);`
- L129 _protected prototype_ `void ParseFrameLog(TArray<TPair<double, bool>>& OutVideoFrameTimeInSeconds, TArray<TPair<double, bool>>& OutDepthFrameTimeInSeconds);`
- L132 _protected member_ `bool bInitialized = false;`
- L133 _protected member_ `FConvertParams ConvertParams;`
- L135 _protected member_ `FLiveLinkFaceTakeInfo TakeInfo;`
- L136 _protected member_ `FString TargetIngestDirectory;`
- L137 _protected member_ `FString TargetIngestPackagePath;`
- L139 _protected member_ `FString TargetWAVFilePath;`
- L140 _protected member_ `FString TargetVideoSequenceDirectory;`
- L141 _protected member_ `FString TargetDepthSequenceDirectory;`
- L143 _protected member_ `FTimecode VideoTimecode;`
- L144 _protected member_ `FTimecode AudioTimecode;`
- L145 _protected member_ `FFrameRate TimecodeRate;`
- L147 _protected member_ `FOnFinished OnFinishedDelegate;`
- L148 _protected member_ `FOnProgress OnProgressDelegate;`
- L151 _protected member_ `TArray<TTuple<int32, int32, bool>> VideoDepthSyncMap;` — (Video frame index, Depth frame index, sync'd) synchronizing pairs
- L152 _protected member_ `TArray<FFrameRange> CaptureExcludedFrames;`
- L153 _protected member_ `TArray<std::atomic<float>> AsyncTaskProgresses;`

#### struct `FLiveLinkFaceTakeDataConverter::FConvertParams`  
`struct FConvertParams`  
_L49-54_
- L51 _public member_ `FLiveLinkFaceTakeInfo TakeInfo;`
- L52 _public member_ `FString TargetIngestDirectory;`
- L53 _public member_ `FString TargetIngestPackagePath;`

#### struct `FLiveLinkFaceTakeDataConverter::FConvertResult`  
`struct FConvertResult`  
_L56-68_
- L58 _public member_ `FString TargetIngestPackagePath;`
- L59 _public member_ `FString ImageSequenceDirectory;`
- L60 _public member_ `FString DepthSequenceDirectory;`
- L61 _public member_ `FString WAVFilePath;`
- L62 _public member_ `bool bVideoTimecodePresent = false;`
- L63 _public member_ `FTimecode VideoTimecode;`
- L64 _public member_ `bool bAudioTimecodePresent = false;`
- L65 _public member_ `FTimecode AudioTimecode;`
- L66 _public member_ `FFrameRate TimecodeRate;`
- L67 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;`

#### class `FLiveLinkFaceTakeDataConverter::FrameLogEntry`  
`class FrameLogEntry`  
_L91-112_
- L94 _public member_ `static const char VideoType = 'V';`
- L95 _public member_ `static const char DepthType = 'D';`
- L96 _public member_ `static const char AudioType = 'A';`
- L97 _public member_ `static const char InvalidType = '\0';`
- L99 _public prototype_ `FrameLogEntry() = default;`
- L100 _public prototype_ `static bool Parse(const FString& InLogLine, FrameLogEntry& OutLogEntry);`
- L102 _public prototype_ `char EntryType();`
- L103 _public prototype_ `int64 FrameIndex();`
- L104 _public prototype_ `double Time();`
- L105 _public prototype_ `bool Timecode(FTimecode& OutTimecode);`
- L106 _public prototype_ `bool IsDroppedFrame();`
- L109 _private prototype_ `FrameLogEntry(TArray<FString>&& InTokens);`
- L111 _private member_ `TArray<FString> Tokens;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FTaskHandler, const FIngestTask& InThisTask, const FStopToken& InStopToken);`
- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProgress, const float);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/MetaHumanDepthConverter.h` (Private)


#### struct `FFrameHeader`  
`struct FFrameHeader`  
_L15-33_
- L28 _public member_ `EFrameType FrameType;`
- L29 _public member_ `char TimeCode[15];`
- L30 _public member_ `int64 TimeValue;`
- L31 _public member_ `int32 TimeScale;`
- L32 _public member_ `uint32 PayloadLength;`

#### enum `FFrameHeader::EFrameType`  
`enum class EFrameType : uint8`  
_L17-26_
- L19 _public enumerator_ `TakeMetadata = 0`
- L20 _public enumerator_ `VideoMetadata = 1`
- L21 _public enumerator_ `DepthMetadata = 2`
- L22 _public enumerator_ `AudioMetadata = 3`
- L23 _public enumerator_ `VideoData = 4`
- L24 _public enumerator_ `DepthData = 5`
- L25 _public enumerator_ `AudioData = 6`

#### struct `FWriteDepthContext`  
`struct FWriteDepthContext`  
_L36-44_
- L38 _public member_ `TSharedPtr<class IImageWrapper> ImageWrapper;`
- L39 _public member_ `FString ExrSequencePath;`
- L40 _public member_ `FIntPoint OutputSize;`
- L41 _public member_ `TArray<float> RotatedDepthBuffer;`
- L42 _public member_ `int32 FrameIndex;`
- L43 _public member_ `bool bShouldCompressFiles;`

#### class `FDepthWriteError`  
`class FDepthWriteError`  
_L46-64_
- L50 _public prototype_ `FDepthWriteError() = default;`
- L51 _public prototype_ `FDepthWriteError(FString InMessage);`
- L53 _public prototype_ `FDepthWriteError(const FDepthWriteError& InOther) = default;`
- L54 _public prototype_ `FDepthWriteError(FDepthWriteError&& InOther) = default;`
- L56 _public prototype_ `FDepthWriteError& operator=(const FDepthWriteError& InOther) = default;`
- L57 _public prototype_ `FDepthWriteError& operator=(FDepthWriteError&& InOther) = default;`
- L59 _public prototype_ `const FString& GetMessage() const;`
- L63 _private member_ `FString Message;`

#### class `FDepthWriterTask`  
`class FDepthWriterTask : public IImageWriteTaskBase`  
_L68-101_
- inherits: `IImageWriteTaskBase`
- L71 _public typedef_ `using DepthWriteResult = TResult<int32, FDepthWriteError>;`
- L73 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnWriteComplete, DepthWriteResult InResult);`
- L74 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnWrite, const FWriteDepthContext& InDepthContext, FOnWriteComplete InCallback);`
- L76 _public function_ `FDepthWriterTask()`
- L80 _public function_ `FDepthWriterTask(FWriteDepthContext InWriteDepthContext, FOnWrite InOnWrite, FOnWriteComplete InOnWriteComplete) : WriteDepthContext(MoveTemp(InWriteDepthContext)) , OnWrite(MoveTemp(InOnWrite)) , OnWriteComplete(MoveTemp(InOnWriteComplete))`
- L87 _public function_ `virtual bool RunTask() override`
- L94 _public function_ `virtual void OnAbandoned() override`
- L98 _public member_ `FWriteDepthContext WriteDepthContext;`
- L99 _public member_ `FOnWrite OnWrite;`
- L100 _public member_ `FOnWriteComplete OnWriteComplete;`

#### class `FDepthConverter`  
`class FDepthConverter final`  
_L104-149_
- desc: Depth Converter
- L107 _public prototype_ `FDepthConverter(bool bInShouldCompressFiles);`
- L108 _public prototype_ `~FDepthConverter();`
- L110 _public prototype_ `bool Open(const FString& InDepthFilePath, const FString& InExrSequencePath);`
- L111 _public prototype_ `void SetGeometry(FIntPoint InSize, EMediaOrientation InOrientation);`
- L114 _public prototype_ `bool Next();` — Jump to the next frame.
- L117 _public prototype_ `void WriteAsync(FDepthWriterTask::FOnWriteComplete InOnWriteComplete);` — Save the current frame to the next exr file in the image sequence.
- L118 _public prototype_ `void WaitAsync();`
- L119 _public prototype_ `bool Write();`
- L120 _public prototype_ `void Close();`
- L122 _public prototype_ `const FText& GetError() const;`
- L125 _protected member_ `FString DepthFilePath;`
- L126 _protected member_ `FString ExrSequencePath;`
- L127 _protected member_ `TUniquePtr<class IFileHandle> ReadHandle;`
- L128 _protected member_ `FIntPoint InputSize;`
- L129 _protected member_ `FIntPoint OutputSize;`
- L130 _protected member_ `EMediaOrientation Orientation;`
- L131 _protected member_ `TArray<uint8> CompressedDepthBuffer;`
- L132 _protected member_ `TArray<int16> DepthBuffer;`
- L133 _protected member_ `TArray<float> RotatedDepthBuffer;`
- L134 _protected member_ `FText ErrorText;`
- L135 _protected member_ `int FrameIndex;`
- L136 _protected member_ `bool bShouldCompressFiles;`
- L138 _protected member_ `static constexpr float TrueDepthResolutionPerCentimeter = 80.0f;`
- L141 _private member_ `class IImageWrapperModule& ImageWrapperModule;`
- L142 _private member_ `class IImageWriteQueue& ImageWriteQueue;`
- L144 _private prototype_ `bool Decompress();`
- L145 _private prototype_ `void Transform();`
- L146 _private prototype_ `FDepthVoidResult WriteToFile(const FWriteDepthContext& InWriteDepthContext);`
- L148 _private prototype_ `void OnWriteHandler(const FWriteDepthContext& InWriteDepthContext, FDepthWriterTask::FOnWriteComplete InOnWriteComplete);`

#### Free symbols / members of external scopes

- L66 _typedef_ `using FDepthVoidResult = TResult<void, FDepthWriteError>;`
- L73 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWriteComplete, DepthWriteResult InResult);`
- L74 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnWrite, const FWriteDepthContext& InDepthContext, FOnWriteComplete InCallback);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/MetaHumanMediaSourceReader.h` (Private)


#### class `IMetaHumanMediaAudioSourceReader`  
`class IMetaHumanMediaAudioSourceReader`  
_L12-25_
- L15 _public prototype_ `virtual ~IMetaHumanMediaAudioSourceReader() = default;`
- L17 _public prototype_ `virtual bool Open(const FString& URL) = 0;`
- L18 _public prototype_ `virtual FTimespan GetTotalDuration() const = 0;`
- L19 _public prototype_ `virtual IMediaAudioSample* Next() = 0;` — The sample is valid till the next call to Next() or Close()
- L20 _public prototype_ `virtual EMediaAudioSampleFormat GetFormat() const = 0;`
- L21 _public prototype_ `virtual uint32 GetSampleRate() const = 0;`
- L22 _public prototype_ `virtual uint32 GetChannels() const = 0;`
- L23 _public prototype_ `virtual void Close() = 0;`
- L24 _public prototype_ `static TSharedPtr<IMetaHumanMediaAudioSourceReader, ESPMode::ThreadSafe> Create();`

#### class `IMetaHumanMediaVideoSourceReader`  
`class IMetaHumanMediaVideoSourceReader`  
_L27-40_
- L30 _public prototype_ `virtual ~IMetaHumanMediaVideoSourceReader() = default;`
- L32 _public prototype_ `virtual bool Open(const FString& URL) = 0;`
- L33 _public prototype_ `virtual FTimespan GetTotalDuration() const = 0;`
- L34 _public prototype_ `virtual IMediaTextureSample* Next() = 0;` — The sample is valid till the next call to Next() or Close()
- L35 _public prototype_ `virtual FIntPoint GetDim() const = 0;`
- L36 _public prototype_ `virtual EMediaTextureSampleFormat GetFormat() const = 0;`
- L37 _public prototype_ `virtual void SetDefaultOrientation(EMediaOrientation InOrientation) = 0;` — Used if the orientation couldn't be determined from the video
- L38 _public prototype_ `virtual void Close() = 0;`
- L39 _public prototype_ `static TSharedPtr<IMetaHumanMediaVideoSourceReader, ESPMode::ThreadSafe> Create();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/MetaHumanStringUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `bool MetaHumanStringContainsWhitespace(const FString& InString);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/FootageIngest/Utils/MetaHumanWaveFileWriter.h` (Private)


#### class `IMetaHumanWaveFileWriter`  
`class IMetaHumanWaveFileWriter`  
_L7-17_
- L10 _public prototype_ `virtual bool Open(const FString& WavFilename, int32 SampleRate, int32 NumChannels, int32 BitsPerSample) = 0;`
- L11 _public prototype_ `virtual bool Append(class IMediaAudioSample* Sample) = 0;`
- L12 _public prototype_ `virtual bool Close() = 0;`
- L14 _public prototype_ `virtual ~IMetaHumanWaveFileWriter() = default;`
- L16 _public prototype_ `static TSharedPtr<IMetaHumanWaveFileWriter> Create();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/MetaHumanCaptureSourceAutoReimport.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _prototype_ `TArray<FAutoReimportDirectoryConfig> CaptureSourceUpdateAutoReimportExclusion( const FString& InSourceDirectory, const FString& InWildcard, const TArray<FAutoReimportDirectoryConfig>& InDirectoryConfigs );` (scope `UE::MetaHuman`) — Note: This function is duplicated in the MetaHumanDepthGenerator module. The intention is to consolidate these functions in future.
- L19 _prototype_ `bool CaptureSourceDirectoryConfigsAreDifferent( const TArray<FAutoReimportDirectoryConfig>& Lhs, const TArray<FAutoReimportDirectoryConfig>& Rhs );` (scope `UE::MetaHuman`) — Note: This function is duplicated in the MetaHumanDepthGenerator module. The intention is to consolidate these functions in future.

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/MetaHumanCaptureSourceFactoryNew.h` (Private)


#### class `UMetaHumanCaptureSourceFactoryNew`  
`class UMetaHumanCaptureSourceFactoryNew : public UFactory`  
_L11-23_
- reflection: `UCLASS(HideCategories = Object)`
- inherits: `UFactory`
- L17 _public prototype_ `UMetaHumanCaptureSourceFactoryNew();`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L21 _public prototype_ `virtual FText GetToolTip() const override;`

#### class `UMetaHumanCaptureSourceSyncFactoryNew`  
`class UMetaHumanCaptureSourceSyncFactoryNew : public UFactory`  
_L26-36_
- reflection: `UCLASS(HideCategories = Object)`
- inherits: `UFactory`
- L32 _public prototype_ `UMetaHumanCaptureSourceSyncFactoryNew();`
- L35 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Private/MetaHumanCaptureSourceLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCaptureSource, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCaptureSource, Log, All);`
- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanIngestAssetCreator, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanIngestAssetCreator, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/Commands/BaseCommand.h` (Public)


#### class `FBaseCommandArgs`  
`FBaseCommandArgs`  
_L10-21_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- L13 _public prototype_ `FBaseCommandArgs(const FString& InName);`
- L14 _public prototype_ `virtual ~FBaseCommandArgs() = default;`
- L16 _public prototype_ `const FString& GetCommandName() const;`
- L20 _private member_ `FString CommandName;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTURESOURCE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/Commands/LiveLinkFaceConnectionCommands.h` (Public)


#### class `FStartCaptureCommandArgs`  
`FStartCaptureCommandArgs : public FBaseCommandArgs`  
_L13-31_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FBaseCommandArgs`
- L16 _public member_ `static const FString CommandName;`
- L18 _public prototype_ `FStartCaptureCommandArgs(FString InSlateName, uint16 InTakeNumber, TOptional<FString> InSubject = TOptional<FString>(), TOptional<FString> InScenario = TOptional<FString>(), TOptional<TArray<FString>> InTags = TOptional<TArray<FString>>());`
- L24 _public prototype_ `virtual ~FStartCaptureCommandArgs() override = default;`
- L26 _public member_ `FString SlateName;`
- L27 _public member_ `uint16 TakeNumber;`
- L28 _public member_ `TOptional<FString> Subject;`
- L29 _public member_ `TOptional<FString> Scenario;`
- L30 _public member_ `TOptional<TArray<FString>> Tags;`

#### class `FStopCaptureCommandArgs`  
`FStopCaptureCommandArgs: public FBaseCommandArgs`  
_L34-46_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FBaseCommandArgs`
- L37 _public member_ `static const FString CommandName;`
- L39 _public prototype_ `FStopCaptureCommandArgs(bool bInShouldFetchTake = true);`
- L41 _public prototype_ `virtual ~FStopCaptureCommandArgs() override = default;`
- L45 _public member_ `bool bShouldFetchTake;` — Introduced as a solution to the current async code and object lifecycle. Should be removed when a proper design is in place.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCAPTURESOURCE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/IpAddressDetailsCustomization.h` (Public)


#### struct `FDeviceAddress`  
`FDeviceAddress`  
_L13-19_
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- L18 _public member_ `FString IpAddress;` — `UPROPERTY(EditAnywhere, Category = DeviceAddress)`

#### class `FIpAddressDetailsCustomization`  
`class FIpAddressDetailsCustomization : public IPropertyTypeCustomization`  
_L21-39_
- inherits: `IPropertyTypeCustomization`
- L24 _public prototype_ `FIpAddressDetailsCustomization();`
- L26 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _private prototype_ `FText OnGetDeviceAddress() const;`
- L33 _private prototype_ `bool OnDeviceAddressVerify(const FText& InText, FText& OutErrorText);`
- L34 _private prototype_ `void OnDeviceAddressCommited(const FText& InText, ETextCommit::Type CommitInfo);`
- L35 _private prototype_ `bool IsReadOnly() const;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> DeviceAddressProperty;`
- L38 _private member_ `TRange<int32> IpAddressRange;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/MetaHumanCaptureError.h` (Public)


#### enum `EMetaHumanCaptureError`  
`enum EMetaHumanCaptureError`  
_L9-18_
- L11 _public enumerator_ `InvalidArguments`
- L12 _public enumerator_ `AbortedByUser`
- L13 _public enumerator_ `InvalidErrorCode`
- L14 _public enumerator_ `CommunicationError`
- L15 _public enumerator_ `NotFound`
- L16 _public enumerator_ `InternalError`
- L17 _public enumerator_ `Warning`

#### class `FMetaHumanCaptureError`  
`FMetaHumanCaptureError`  
_L22-36_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- desc: This is designed to be used with TResult, which is why there is no "NoError" code
- L26 _public prototype_ `FMetaHumanCaptureError();`
- L27 _public prototype_ `FMetaHumanCaptureError(EMetaHumanCaptureError InCode, FString InMessage = TEXT(""));`
- L29 _public prototype_ `const FString& GetMessage() const;`
- L30 _public prototype_ `EMetaHumanCaptureError GetCode() const;`
- L34 _private member_ `EMetaHumanCaptureError Code;`
- L35 _private member_ `FString Message;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTURESOURCE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/MetaHumanCaptureEvents.h` (Public)


#### struct `FNewTakesAddedEvent`  
`FNewTakesAddedEvent : public FCaptureEvent`  
_L12-25_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FCaptureEvent`
- L14 _public member_ `inline static const FString Name = TEXT("New`
- L16 _public member_ `TArray<TakeId> NewTakes;`
- L18 _public function_ `FNewTakesAddedEvent(TArray<TakeId> InNewTakes) : FCaptureEvent(Name), NewTakes(MoveTemp(InNewTakes))`
- L22 _public function_ `FNewTakesAddedEvent(TakeId InNewTake) : FCaptureEvent(Name), NewTakes({ InNewTake })`

#### struct `FTakesRemovedEvent`  
`FTakesRemovedEvent : public FCaptureEvent`  
_L28-41_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FCaptureEvent`
- L30 _public member_ `inline static const FString Name = TEXT("Tak`
- L32 _public member_ `TArray<TakeId> TakesRemoved;`
- L34 _public function_ `FTakesRemovedEvent(TArray<TakeId> InTakesRemoved) : FCaptureEvent(Name), TakesRemoved(MoveTemp(InTakesRemoved))`
- L38 _public function_ `FTakesRemovedEvent(TakeId InTakeRemoved) : FCaptureEvent(Name), TakesRemoved({ InTakeRemoved })`

#### struct `FThumbnailChangedEvent`  
`FThumbnailChangedEvent : public FCaptureEvent`  
_L44-53_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FCaptureEvent`
- L46 _public member_ `inline static const FString Name = TEXT("Thu`
- L48 _public member_ `TakeId ChangedTake;`
- L50 _public function_ `FThumbnailChangedEvent(TakeId InChangedTake) : FCaptureEvent(Name), ChangedTake(InChangedTake)`

#### struct `FConnectionChangedEvent`  
`FConnectionChangedEvent : public FCaptureEvent`  
_L56-72_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FCaptureEvent`
- L58 _public member_ `inline static const FString Name = TEXT("Con`
- L67 _public member_ `EState ConnectionState;`
- L69 _public function_ `FConnectionChangedEvent(EState InConnectionState) : FCaptureEvent(Name), ConnectionState(InConnectionState)`

#### enum `FConnectionChangedEvent::EState`  
`enum class EState`  
_L60-65_
- L62 _public enumerator_ `Unknown = 0`
- L63 _public enumerator_ `Connected`
- L64 _public enumerator_ `Disconnected`

#### struct `FRecordingStatusChangedEvent`  
`FRecordingStatusChangedEvent : public FCaptureEvent`  
_L75-84_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FCaptureEvent`
- L77 _public member_ `inline static const FString Name = TEXT("Rec`
- L79 _public member_ `bool bIsRecording;`
- L81 _public function_ `FRecordingStatusChangedEvent(bool bInIsRecording) : FCaptureEvent(Name), bIsRecording(bInIsRecording)`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/MetaHumanCaptureIngester.h` (Public)


#### struct `UE::MetaHuman::FIngesterParams`  
`FIngesterParams`  
_L20-45_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- L22 _public prototype_ `FIngesterParams( EMetaHumanCaptureSourceType InCaptureSourceType, FDirectoryPath InStoragePath, FDeviceAddress InDeviceAddress, uint16 InDeviceControlPort, bool InShouldCompressDepthFiles, bool InCopyImagesToProject, float InMinDistance, float InMaxDistance, EMetaHumanCaptureDepthPrecisionType InDepthPrecision, EMetaHumanCaptureDepthResolutionType InDepthResolution );`
- L35 _public member_ `EMetaHumanCaptureSourceType CaptureSourceType;`
- L36 _public member_ `FDirectoryPath StoragePath;`
- L37 _public member_ `FDeviceAddress DeviceAddress;`
- L38 _public member_ `uint16 DeviceControlPort;`
- L39 _public member_ `bool ShouldCompressDepthFiles;`
- L40 _public member_ `bool CopyImagesToProject;`
- L41 _public member_ `float MinDistance;`
- L42 _public member_ `float MaxDistance;`
- L43 _public member_ `EMetaHumanCaptureDepthPrecisionType DepthPrecision;`
- L44 _public member_ `EMetaHumanCaptureDepthResolutionType DepthResolution;`

#### class `UE::MetaHuman::FIngester`  
`FIngester : public FCaptureEventSource`  
_L48-95_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `FCaptureEventSource`
- L51 _public typedef_ `using FRefreshCallback = TManagedDelegate<FMetaHumanCaptureVoidResult>;`
- L52 _public typedef_ `using FGetTakesCallbackPerTake = TManagedDelegate<FMetaHumanCapturePerTakeVoidResult>;`
- L54 _public prototype_ `explicit FIngester(FIngesterParams InIngesterParams);`
- L55 _public prototype_ `virtual ~FIngester();`
- L57 _public prototype_ `void SetParams(FIngesterParams InIngesterParams);`
- L59 _public prototype_ `bool CanStartup() const;`
- L60 _public prototype_ `bool CanIngestTakes() const;`
- L61 _public prototype_ `bool CanCancel() const;`
- L67 _public prototype_ `void Startup(ETakeIngestMode InMode = ETakeIngestMode::Async);` — @brief Startup the footage ingest API. Get information on the available takes based on the type of this Capture Source @param bSynchronous If true, this will be a blocking function. Useful when initializing from blueprints or python
- L68 _public prototype_ `void Refresh(FRefreshCallback InCallback);`
- L70 _public prototype_ `void SetTargetPath(const FString& InTargetIngestDirectory, const FString& InTargetFolderAssetPath);`
- L71 _public prototype_ `void Shutdown();`
- L72 _public prototype_ `bool IsProcessing() const;`
- L73 _public prototype_ `bool IsCancelling() const;`
- L75 _public prototype_ `void CancelProcessing(const TArray<TakeId>& InTakeIdList);`
- L76 _public prototype_ `int32 GetNumTakes() const;`
- L77 _public prototype_ `TArray<TakeId> GetTakeIds() const;`
- L78 _public prototype_ `bool GetTakeInfo(TakeId InTakeId, FMetaHumanTakeInfo& OutTakeInfo) const;`
- L80 _public prototype_ `bool GetTakes(const TArray<TakeId>& InTakeIdList, FGetTakesCallbackPerTake InCallback);`
- L81 _public prototype_ `TOptional<float> GetProcessingProgress(TakeId InTakeId) const;`
- L82 _public prototype_ `FText GetProcessName(TakeId InTakeId) const;`
- L83 _public prototype_ `bool ExecuteCommand(class TSharedPtr<class FBaseCommandArgs> InCommand);`
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetTakesFinished, const TArray<FMetaHumanTake>& InTakes) FOnGetTakesFinished OnGetTakesFinishedDelegate;`
- L88 _public prototype_ `EMetaHumanCaptureSourceType GetCaptureSourceType() const;`
- L91 _private prototype_ `void ProxyEvent(TSharedPtr<const FCaptureEvent> Event);`
- L93 _private member_ `TUniquePtr<class IFootageIngestAPI> FootageIngestAPI;`
- L94 _private member_ `FIngesterParams Params;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCAPTURESOURCE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MetaHuman` (scope `UE`)
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetTakesFinished, const TArray<FMetaHumanTake>& InTakes) FOnGetTakesFinished OnGetTakesFinishedDelegate;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/MetaHumanCaptureSource.h` (Public)


#### enum `EMetaHumanCaptureSourceType`  
`EMetaHumanCaptureSourceType : uint8`  
_L22-28_
- reflection: `UENUM(meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- desc: Capture Source Asset Type
- L24 _public enumerator_ `Undefined UMETA(DisplayName = "Undefined")`
- L25 _public enumerator_ `LiveLinkFaceConnection UMETA(DisplayName = "LiveLinkFace Connection")`
- L26 _public enumerator_ `LiveLinkFaceArchives UMETA(DisplayName = "LiveLinkFace Archives")`
- L27 _public enumerator_ `HMCArchives UMETA(DisplayName = "Stereo HMC Archives")`

#### enum `EMetaHumanCaptureDepthPrecisionType`  
`enum class EMetaHumanCaptureDepthPrecisionType : uint8`  
_L31-35_
- reflection: `UENUM()`
- L33 _public enumerator_ `Eightieth UMETA(DisplayName = "0.125 mm")` — Fraction of a cm
- L34 _public enumerator_ `Full`

#### enum `EMetaHumanCaptureDepthResolutionType`  
`enum class EMetaHumanCaptureDepthResolutionType : uint8`  
_L38-43_
- reflection: `UENUM()`
- L40 _public enumerator_ `Full`
- L41 _public enumerator_ `Half`
- L42 _public enumerator_ `Quarter`

#### struct `FMetaHumanCaptureVoidResult`  
`struct FMetaHumanCaptureVoidResult`  
_L47-67_
- desc: DEPRECATED: This functionality is now available in the CaptureManager/CaptureManagerDevices module.
- L55 _public member_ `bool bIsValid = true;` — `UPROPERTY(VisibleAnywhere, Category = "Capture Void Result")`
- L58 _public member_ `int32 Code = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Capture Void Result")`
- L61 _public member_ `FString Message = TEXT("");` — `UPROPERTY(VisibleAnywhere, Category = "Capture Void Result")`
- L65 _public prototype_ `void SetResult(TResult<void, FMetaHumanCaptureError> InResult);`

#### struct `FMetaHumanCapturePerTakeVoidResult`  
`struct FMetaHumanCapturePerTakeVoidResult`  
_L71-83_
- desc: DEPRECATED: This functionality is now available in the CaptureManager/CaptureManagerDevices module.
- L79 _public member_ `FMetaHumanCaptureVoidResult Result;` — `UPROPERTY(VisibleAnywhere, Category = "Capture Per Take Void Result")`
- L82 _public member_ `int32 TakeId = INVALID_ID;` — `UPROPERTY(VisibleAnywhere, Category = "Capture Per Take Void Result")`

#### class `UMetaHumanCaptureSource`  
`UMetaHumanCaptureSource : public UObject`  
_L97-168_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `UObject`
- desc: Capture Source Asset An asset representing a physical device or an archive that can be used to import the footage data into Unreal Editor. A footage of live performance, in combination with a Skeletal Mesh obtained through MetaHuman Identity asset toolkit. Used in MetaHuman Performance asset to generate an Animation Sequence by automatically tracking facial features of the actor in the performance
- L104 _public member_ `EMetaHumanCaptureSourceType CaptureSourceType = EMetaHumanCaptureSourceType::Undefined;` — `UPROPERTY(EditAnywhere, Category = "Capture Source")`
- L108 _public member_ `FDirectoryPath StoragePath;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchives || CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchivesRGB || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives", EditConditionHides))`
- L111 _public member_ `FString DeviceAddress_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has changed its type"))`
- L115 _public member_ `FDeviceAddress DeviceIpAddress;` — `UPROPERTY(EditAnywhere, DisplayName = "Device Address", Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceConnection", EditConditionHides))`
- L119 _public member_ `uint16 DeviceControlPort = 14785;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceConnection", EditConditionHides))`
- L122 _public member_ `uint16 ExportListeningPort_DEPRECATED = 8000;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property isn't used anymore as the port is being provided automatically by the OS"))`
- L126 _public member_ `bool ShouldCompressDepthFiles = true;` — `UPROPERTY(/*EditAnywhere, DisplayName = "Compress Depth Files", Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchives || CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceConnection", EditConditionHides)*/)` — TODO: Expose this parameter once uncompressed EXR's are supported
- L129 _public member_ `bool CopyImagesToProject = true;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives", EditConditionHides))`
- L137 _public member_ `float MinDistance = 10.0;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "The minimum cm from the camera expected for valid depth information.\n Depth information closer than this will be ignored to help filter out noise.", ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives", EditConditionHides))`
- L145 _public member_ `float MaxDistance = 25.0;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "The maximum cm from the camera expected for valid depth information.\n Depth information beyond this will be ignored to help filter out noise.", ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives", EditConditionHides))`
- L152 _public member_ `EMetaHumanCaptureDepthPrecisionType DepthPrecision = EMetaHumanCaptureDepthPrecisionType::Eightieth;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "Precision of the calculated depth data. Full precision is more accurate, but requires more disk space to store.", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchivesRGB ", EditConditionHides))`
- L158 _public member_ `EMetaHumanCaptureDepthResolutionType DepthResolution = EMetaHumanCaptureDepthResolutionType::Full;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "Resolution scaling applied to the calculated depth data. Full resolution is more accurate, but requires more disk space to store.", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives", EditConditionHides))`
- L164 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L167 _private prototype_ `virtual void PostLoad();`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METAHUMANCAPTURESOURCE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/MetaHumanCaptureSourceSync.h` (Public)


#### class `UMetaHumanCaptureSourceSync`  
`UMetaHumanCaptureSourceSync : public UObject`  
_L18-149_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- inherits: `UObject`
- L23 _public prototype_ `UMetaHumanCaptureSourceSync();`
- L24 _public prototype_ `UMetaHumanCaptureSourceSync(FVTableHelper& Helper);`
- L25 _public prototype_ `virtual ~UMetaHumanCaptureSourceSync();`
- L28 _public prototype_ `bool CanStartup() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L31 _public prototype_ `bool CanIngestTakes() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L34 _public prototype_ `bool CanCancel() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L41 _public prototype_ `void Startup();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")` — @brief Startup the MetaHuman|Footage Ingest API. Get information on the available takes based on the type of this Capture Source @param bSynchronous If true, this will be a blocking function. Useful when initializing from blueprints or python
- L45 _public prototype_ `TArray<FMetaHumanTakeInfo> Refresh();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L49 _public prototype_ `void SetTargetPath(const FString& InTargetIngestDirectory, const FString& InTargetFolderAssetPath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L52 _public prototype_ `void Shutdown();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L55 _public prototype_ `bool IsProcessing() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L58 _public prototype_ `bool IsCancelling() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L61 _public prototype_ `void CancelProcessing(const TArray<int32>& InTakeIdList);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L64 _public prototype_ `int32 GetNumTakes() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L67 _public prototype_ `TArray<int32> GetTakeIds() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L71 _public prototype_ `bool GetTakeInfo(int32 InTakeId, FMetaHumanTakeInfo& OutTakeInfo) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L74 _public prototype_ `TArray<FMetaHumanTake> GetTakes(const TArray<int32>& InTakeIdList);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Footage Ingest API")`
- L80 _public member_ `EMetaHumanCaptureSourceType CaptureSourceType = EMetaHumanCaptureSourceType::Undefined;` — `UPROPERTY(EditAnywhere, Category = "Capture Source")`
- L84 _public member_ `FDirectoryPath StoragePath;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchives || CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchivesRGB || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives", EditConditionHides))`
- L87 _public member_ `FString DeviceAddress_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has changed its type"))`
- L91 _public member_ `FDeviceAddress DeviceIpAddress;` — `UPROPERTY(EditAnywhere, DisplayName = "Device Address", Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceConnection", EditConditionHides))`
- L95 _public member_ `uint16 DeviceControlPort = 14785;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceConnection", EditConditionHides))`
- L98 _public member_ `uint16 ExportListeningPort_DEPRECATED = 8000;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property isn't used anymore as the port is being provided automatically by the OS"))`
- L102 _public member_ `bool ShouldCompressDepthFiles = true;` — `UPROPERTY(/*EditAnywhere, DisplayName = "Compress Depth Files", Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchives || CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceConnection", EditConditionHides)*/)` — TODO: Expose this parameter once uncompressed EXR's are supported
- L105 _public member_ `bool CopyImagesToProject = true;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives", EditConditionHides))`
- L113 _public member_ `float MinDistance = 10.0;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "The minimum cm from the camera expected for valid depth information.\n Depth information closer than this will be ignored to help filter out noise.", ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives", EditConditionHides))`
- L121 _public member_ `float MaxDistance = 25.0;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "The maximum cm from the camera expected for valid depth information.\n Depth information beyond this will be ignored to help filter out noise.", ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives", EditConditionHides))`
- L128 _public member_ `EMetaHumanCaptureDepthPrecisionType DepthPrecision = EMetaHumanCaptureDepthPrecisionType::Eightieth;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "Precision of the calculated depth data. Full precision is more accurate, but requires more disk space to store.", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchivesRGB || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives", EditConditionHides))`
- L134 _public member_ `EMetaHumanCaptureDepthResolutionType DepthResolution = EMetaHumanCaptureDepthResolutionType::Full;` — `UPROPERTY(EditAnywhere, Category = "Capture Source", meta = (ToolTip = "Resolution scaling applied to the calculated depth data. Full resolution is more accurate, but requires more disk space to store.", EditCondition = "CaptureSourceType == EMetaHumanCaptureSourceType::HMCArchives || CaptureSourceType == EMetaHumanCaptureSourceType::LiveLinkFaceArchivesRGB || CaptureSourceType == EMetaHumanCaptureSourceType::MonoArchives", EditConditionHides))`
- L138 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L143 _private member_ `TUniquePtr<UE::MetaHuman::FIngester> Ingester;`
- L147 _private member_ `TObjectPtr<UMetaHumanCaptureSource> MetaHumanCaptureSource;` — `UPROPERTY(Transient)` — Do not expose this property to the editor or blueprints, it is only for garbage collection purposes.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCAPTURESOURCE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureSource/Public/MetaHumanTakeData.h` (Public)


#### enum `ETakeIngestMode`  
`ETakeIngestMode : uint8`  
_L16-20_
- reflection: `UENUM(meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- desc: Enum that describes how the operations of the capture source should be executed
- L18 _public enumerator_ `Async`
- L19 _public enumerator_ `Blocking`

#### enum `(anonymous)`  
`enum`  
_L23-23_

#### struct `FMetaHumanTakeInfo`  
`struct FMetaHumanTakeInfo`  
_L27-80_
- desc: DEPRECATED: This functionality is now available in the CaptureManager/CaptureManagerDevices module.
- L35 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L38 _public member_ `int32 Id = INVALID_ID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L41 _public member_ `int32 NumFrames = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L44 _public member_ `double FrameRate = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L47 _public member_ `int32 TakeNumber = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L50 _public member_ `FIntPoint Resolution = FIntPoint::NoneValue;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L53 _public member_ `FIntPoint DepthResolution = FIntPoint::NoneValue;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L56 _public member_ `FDateTime Date;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L59 _public member_ `int32 NumStreams = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L62 _public member_ `FString DeviceModel;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L66 _public member_ `TSet<FString> Tags;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")` — A list of tags that describe this take, if any
- L70 _public member_ `TMap<FString, FString> Metadata;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")` — Any data we want to have on a per-take basis
- L73 _public member_ `TArray<uint8> RawThumbnailData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L76 _public member_ `FString OutputDirectory;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`
- L79 _public member_ `TArray<FText> Issues;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take Info")`

#### struct `FMetaHumanTakeView`  
`FMetaHumanTakeView`  
_L84-111_
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- L89 _public member_ `TObjectPtr<class UImgMediaSource> Video;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L92 _public member_ `bool bVideoTimecodePresent = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L95 _public member_ `FTimecode VideoTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L98 _public member_ `FFrameRate VideoTimecodeRate;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L101 _public member_ `TObjectPtr<class UImgMediaSource> Depth;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L104 _public member_ `bool bDepthTimecodePresent = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L107 _public member_ `FTimecode DepthTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`
- L110 _public member_ `FFrameRate DepthTimecodeRate;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take View")`

#### struct `FMetaHumanTake`  
`FMetaHumanTake`  
_L115-144_
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module"))`
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")`
- L120 _public member_ `int32 TakeId = INVALID_ID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L124 _public member_ `TArray<FMetaHumanTakeView> Views;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L128 _public member_ `TObjectPtr<class UCameraCalibration> CameraCalibration;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L131 _public member_ `TObjectPtr<class USoundWave> Audio;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L134 _public member_ `bool bAudioTimecodePresent = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L137 _public member_ `FTimecode AudioTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L140 _public member_ `FFrameRate AudioTimecodeRate;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`
- L143 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Take")`

#### Free symbols / members of external scopes

- L22 _typedef_ `using TakeId = int32;`
- L23 _enumerator_ `enum { INVALID_ID = -1 }; USTRUCT(BlueprintType, meta = (Deprecated = "5.7", DeprecationMessage = "MetaHumanAnimator/MetaHumanCaptureSource is deprecated. This functionality is now available in the CaptureManager/CaptureManagerDevices module")) struct FMetaHumanTakeInfo { GENERATED_BODY()` (scope `__anon2a9c6f970103`)
