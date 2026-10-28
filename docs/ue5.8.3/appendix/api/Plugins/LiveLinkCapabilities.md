# Plugins / LiveLinkCapabilities

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities`
- headers: 7; symbols: 170
- symbol kinds: class=11, delegate=3, enum=2, enumerator=14, function=7, member=46, prototype=74, struct=8, typedef=5
- PrivateDependencyModuleNames: CaptureManagerMediaRW, CoreUObject, Engine, Json, LiveLinkDevice, LiveLinkHubCaptureMessaging, Media, MediaAssets, MediaFrameworkUtilities, MediaProfile, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: CaptureDataConverter, CaptureManagerTakeMetadata, CaptureManagerUnrealEndpoint, CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Ingest/IngestCapability_Events.h` (Public)


#### struct `FIngestCapability_TakeBaseEvent`  
`struct FIngestCapability_TakeBaseEvent : public UE::CaptureManager::FCaptureEvent`  
_L10-19_
- inherits: `UE::CaptureManager::FCaptureEvent`
- L12 _public function_ `FIngestCapability_TakeBaseEvent(int32 InTakeId, FString InName) : FCaptureEvent(MoveTemp(InName)) , TakeId(InTakeId)`
- L18 _public member_ `int32 TakeId;`

#### struct `FIngestCapability_TakeAddedEvent`  
`struct FIngestCapability_TakeAddedEvent : public FIngestCapability_TakeBaseEvent`  
_L21-29_
- inherits: `FIngestCapability_TakeBaseEvent`
- L23 _public member_ `static constexpr FStringView Name = TEXT("Ing`
- L25 _public function_ `explicit FIngestCapability_TakeAddedEvent(int32 InTakeId) : FIngestCapability_TakeBaseEvent(InTakeId, FString(Name))`

#### struct `FIngestCapability_TakeUpdatedEvent`  
`struct FIngestCapability_TakeUpdatedEvent : public FIngestCapability_TakeBaseEvent`  
_L31-39_
- inherits: `FIngestCapability_TakeBaseEvent`
- L33 _public member_ `static constexpr FStringView Name = TEXT("Ing`
- L35 _public function_ `explicit FIngestCapability_TakeUpdatedEvent(int32 InTakeId) : FIngestCapability_TakeBaseEvent(InTakeId, FString(Name))`

#### struct `FIngestCapability_TakeRemovedEvent`  
`struct FIngestCapability_TakeRemovedEvent : public FIngestCapability_TakeBaseEvent`  
_L41-49_
- inherits: `FIngestCapability_TakeBaseEvent`
- L43 _public member_ `static constexpr FStringView Name = TEXT("Ing`
- L45 _public function_ `explicit FIngestCapability_TakeRemovedEvent(int32 InTakeId) : FIngestCapability_TakeBaseEvent(InTakeId, FString(Name))`

#### struct `FIngestCapability_TakeListResetEvent`  
`struct FIngestCapability_TakeListResetEvent : public UE::CaptureManager::FCaptureEvent`  
_L51-59_
- inherits: `UE::CaptureManager::FCaptureEvent`
- L53 _public member_ `static constexpr FStringView Name = TEXT("Ing`
- L55 _public function_ `explicit FIngestCapability_TakeListResetEvent(FString InName) : FCaptureEvent(MoveTemp(InName))`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Ingest/IngestCapability_Options.h` (Public)


#### struct `FIngestCapability_VideoOptions`  
`struct FIngestCapability_VideoOptions`  
_L15-30_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `FString FileNamePrefix;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L23 _public member_ `FString Format;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L26 _public member_ `ECaptureManagerPixelFormat PixelFormat = ECaptureManagerPixelFormat::U8_BGRA;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L29 _public member_ `ECaptureManagerRotation Rotation = ECaptureManagerRotation::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`

#### struct `FIngestCapability_AudioOptions`  
`struct FIngestCapability_AudioOptions`  
_L33-42_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `FString FileNamePrefix;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L41 _public member_ `FString Format;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`

#### class `UIngestCapability_Options`  
`class UIngestCapability_Options : public UObject`  
_L45-65_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L52 _public member_ `FString WorkingDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L55 _public member_ `FString DownloadDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L58 _public member_ `FIngestCapability_VideoOptions Video;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L61 _public member_ `FIngestCapability_AudioOptions Audio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`
- L64 _public member_ `FString UploadHostName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Live Link Device|Ingest")`

#### Free symbols / members of external scopes

- L11 _typedef_ `using EIngestCapability_ImagePixelFormat UE_DEPRECATED(5.8, "Use ECaptureManagerPixelFormat i` — Deprecated type aliases for backward compatibility.
- L12 _typedef_ `using EIngestCapability_ImageRotation UE_DEPRECATED(5.8, "Use ECaptureManagerRotation i` — `UE_DEPRECATED(5.8, "Use ECaptureManagerPixelFormat instead.")` — Deprecated type aliases for backward compatibility.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Ingest/IngestCapability_ProcessHandle.h` (Public)


#### class `FIngestCapability_Error`  
`class FIngestCapability_Error`  
_L17-43_
- L34 _public prototype_ `FIngestCapability_Error(ECode InCode, FString InMessage);`
- L36 _public prototype_ `ECode GetCode() const;`
- L37 _public prototype_ `const FString& GetMessage() const;`
- L41 _private member_ `ECode Code;`
- L42 _private member_ `FString Message;`

#### enum `FIngestCapability_Error::ECode`  
`enum ECode`  
_L21-32_
- L23 _public enumerator_ `Ok = 0`
- L24 _public enumerator_ `AbortedByUser = 1`
- L25 _public enumerator_ `InternalError`
- L26 _public enumerator_ `InvalidArgument`
- L27 _public enumerator_ `DownloaderError`
- L28 _public enumerator_ `UnrealEndpointNotFound`
- L29 _public enumerator_ `UnrealEndpointConnectionTimedOut`
- L30 _public enumerator_ `UnrealEndpointUploadError`
- L31 _public enumerator_ `ConversionError`

#### enum `EIngestCapability_ProcessConfig`  
`enum class EIngestCapability_ProcessConfig : uint8`  
_L46-54_
- reflection: `UENUM(BlueprintType)`
- L48 _public enumerator_ `DownloadStep = 1 << 0 UMETA(Hidden)`
- L49 _public enumerator_ `ConvertAndUploadStep = 1 << 1 UMETA(Hidden)`
- L51 _public enumerator_ `None = 0 UMETA(Hidden)`
- L52 _public enumerator_ `Download = DownloadStep UMETA(DisplayName = "Download", ToolTip = "Download only. Copies data to specified download directory\n\nA Take Archive device can be used to ingest the downloaded take at another time")`
- L53 _public enumerator_ `Ingest = DownloadStep | ConvertAndUploadStep UMETA(DisplayName = "Ingest", ToolTip = "Ingest data to specified UE/UEFN client")`

#### class `UIngestCapability_ProcessResult`  
`class UIngestCapability_ProcessResult : public UObject`  
_L66-86_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L73 _public member_ `FText Message;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Live Link Device|Ingest")`
- L76 _public member_ `int32 Code = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Live Link Device|Ingest")`
- L79 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintCallable, Category = "Live Link Device|Ingest")`
- L82 _public prototype_ `bool IsError() const;` — `UFUNCTION(BlueprintCallable, Category = "Live Link Device|Ingest")`
- L84 _public prototype_ `static UIngestCapability_ProcessResult* Success();`
- L85 _public prototype_ `static UIngestCapability_ProcessResult* Error(FText InMessage, int32 InCode = -1);`

#### class `FIngestCapability_ProcessContext`  
`class FIngestCapability_ProcessContext`  
_L88-123_
- L96 _public prototype_ `explicit FIngestCapability_ProcessContext(int32 InTakeId, EIngestCapability_ProcessConfig InProcessConfig, class ILiveLinkDeviceCapability_Ingest* InOwner, FPrivateToken);`
- L101 _public prototype_ `bool IsDone() const;`
- L103 _public member_ `FProcessFinishReporter ProcessFinishedReporterDynamic;`
- L104 _public member_ `FIngestProcessFinishReporter ProcessFinishedReporter;`
- L106 _public member_ `FProcessProgressReporter ProcessProgressReporterDynamic;`
- L107 _public member_ `FIngestProcessProgressReporter ProcessProgressReporter;`
- L109 _public member_ `int32 TakeId = INDEX_NONE;`
- L113 _private member_ `TStrongObjectPtr<const UIngestCapability_Options> IngestOptions;`
- L114 _private member_ `TSharedPtr<UE::CaptureManager::FTaskProgress> TaskProgress;`
- L115 _private member_ `UE::CaptureManager::FTaskProgress::FTask CurrentTask;`
- L117 _private member_ `EIngestCapability_ProcessConfig ProcessConfig = EIngestCapability_ProcessConfig::None;`
- L118 _private member_ `EIngestCapability_ProcessConfig CurrentStep = EIngestCapability_ProcessConfig::None;`
- L119 _private member_ `int32 NumberOfSteps = 0;`
- L120 _private member_ `class ILiveLinkDeviceCapability_Ingest* Owner;`

#### struct `FIngestCapability_ProcessContext::FPrivateToken`  
`struct FPrivateToken`  
_L92-92_
- L92 _public prototype_ `struct FPrivateToken`

#### class `UIngestCapability_ProcessHandle`  
`class UIngestCapability_ProcessHandle : public UObject`  
_L126-157_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L133 _public prototype_ `int32 GetTakeId() const;` — `UFUNCTION(BlueprintCallable, Category = "Live Link Device|Ingest")`
- L136 _public prototype_ `bool IsDone() const;` — `UFUNCTION(BlueprintCallable, Category = "Live Link Device|Ingest")`
- L139 _public prototype_ `FProcessFinishReporter& OnProcessFinishReporterDynamic();` — `UFUNCTION(BlueprintCallable, Category = "Live Link Device|Ingest")`
- L141 _public prototype_ `FIngestProcessFinishReporter& OnProcessFinishReporter();`
- L144 _public prototype_ `FProcessProgressReporter& OnProcessProgressReporterDynamic();` — `UFUNCTION(BlueprintCallable, Category = "Live Link Device|Ingest")`
- L146 _public prototype_ `FIngestProcessProgressReporter& OnProcessProgressReporter();`
- L150 _private prototype_ `UIngestCapability_ProcessHandle();`
- L152 _private prototype_ `void Initialize(TUniquePtr<FIngestCapability_ProcessContext> InContext);`
- L154 _private member_ `TUniquePtr<FIngestCapability_ProcessContext> Context;`

#### Free symbols / members of external scopes

- L56 _prototype_ `ENUM_CLASS_FLAGS(EIngestCapability_ProcessConfig);`
- L59 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FProcessFinishReporter, const UIngestCapability_ProcessHandle*, ProcessHandle, UIngestCapability_ProcessResult*, IngestProcessResult);`
- L59 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FProcessFinishReporter, const UIngestCapability_ProcessHandle*, ProcessHandle, UIngestCapability_ProcessResult*, IngestProcessResult);` — `UDELEGATE()`
- L60 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FProcessProgressReporter, const UIngestCapability_ProcessHandle*, ProcessHandle, double, Progress);`
- L60 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FProcessProgressReporter, const UIngestCapability_ProcessHandle*, ProcessHandle, double, Progress);`
- L62 _typedef_ `using FIngestProcessProgressReporter = UE::CaptureManager::TManagedDelegate<const UIngestCapability_ProcessHandle*, double>;`
- L63 _typedef_ `using FIngestProcessFinishReporter = UE::CaptureManager::TManagedDelegate<const UIngestCapability_ProcessHandle*, TValueOrError<void, FIngestCapability_Error>>;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Ingest/IngestCapability_TakeInformation.h` (Public)


#### class `UIngestCapability_TakeInformation`  
`class UIngestCapability_TakeInformation : public UObject`  
_L12-36_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L20 _public member_ `FString DeviceName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TakeInfo)`
- L23 _public member_ `FString SlateName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TakeInfo)`
- L26 _public member_ `int32 TakeNumber = -1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TakeInfo)`
- L29 _public member_ `FDateTime DateTime;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TakeInfo)`
- L32 _public function_ `FString GetDateTimeString() const` — `UFUNCTION(BlueprintCallable, Category = TakeInfo)`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Ingest/IngestCapability_UpdateTakeList.h` (Public)


#### class `UIngestCapability_UpdateTakeListCallback`  
`class UIngestCapability_UpdateTakeListCallback : public UObject`  
_L19-29_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public member_ `FUpdateTakeListCallback DynamicCallback;` — `UPROPERTY(EditAnywhere, Category = "Live Link Device|Ingest")`
- L28 _public member_ `FIngestUpdateTakeListCallback Callback;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FUpdateTakeListCallback, TArray<int32>, TakeIdentifiers);`
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FUpdateTakeListCallback, TArray<int32>, TakeIdentifiers);` — `UDELEGATE()`
- L16 _typedef_ `using FIngestUpdateTakeListCallback = UE::CaptureManager::TManagedDelegate<TArray<int32>>;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Ingest/LiveLinkDeviceCapability_Ingest.h` (Public)


#### class `ULiveLinkDeviceCapability_Ingest`  
`class ULiveLinkDeviceCapability_Ingest : public ULiveLinkDeviceCapability`  
_L21-36_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `ULiveLinkDeviceCapability`
- L27 _public member_ `const FName Column_IngestSupport;`
- L29 _public function_ `ULiveLinkDeviceCapability_Ingest() : Column_IngestSupport(RegisterTableColumn("IngestSupport"))`
- L34 _public prototype_ `virtual SHeaderRow::FColumn::FArguments& GenerateHeaderForColumn(const FName InColumnId, SHeaderRow::FColumn::FArguments& InArgs) override;`
- L35 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidgetForColumn(const FName InColumnId, const FLiveLinkDeviceWidgetArguments& InArgs, ULiveLinkDevice* InDevice) override;`

#### class `ILiveLinkDeviceCapability_Ingest`  
`class ILiveLinkDeviceCapability_Ingest : public ILiveLinkDeviceCapability #if CPP , public UE::CaptureManager::FCaptureEventSource #endif`  
_L38-114_
- inherits: `ILiveLinkDeviceCapability,UE::CaptureManager::FCaptureEventSource`
- L48 _public prototype_ `ILiveLinkDeviceCapability_Ingest();`
- L51 _public prototype_ `UIngestCapability_ProcessHandle* CreateIngestProcess(int32 InTakeId, EIngestCapability_ProcessConfig InProcessConfig);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L54 _public prototype_ `void RunIngestProcess(UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InOptions);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L57 _public prototype_ `void CancelIngestProcess(const UIngestCapability_ProcessHandle* InProcessHandle);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L60 _public prototype_ `void UpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L63 _public prototype_ `void RequestAbortUpdateTakeList();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L66 _public prototype_ `UIngestCapability_TakeInformation* GetTakeInformation(int32 InTakeId) const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L69 _public prototype_ `TArray<int32> GetTakeIdentifiers() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Ingest")`
- L71 _public prototype_ `UIngestCapability_ProcessHandle* CreateIngestProcess_Implementation(int32 InTakeId, EIngestCapability_ProcessConfig InProcessConfig);`
- L72 _public prototype_ `void RunIngestProcess_Implementation(UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InOptions);`
- L73 _public prototype_ `virtual void CancelIngestProcess_Implementation(const UIngestCapability_ProcessHandle* InProcessHandle) PURE_VIRTUAL(ILiveLinkDeviceCapability_Ingest::CancelIngestProcess_Implementation);`
- L75 _public prototype_ `void UpdateTakeList_Implementation(UIngestCapability_UpdateTakeListCallback* InCallback);`
- L76 _public prototype_ `void RequestAbortUpdateTakeList_Implementation();`
- L78 _public prototype_ `UIngestCapability_TakeInformation* GetTakeInformation_Implementation(int32 InTakeId) const;`
- L79 _public prototype_ `TArray<int32> GetTakeIdentifiers_Implementation() const;`
- L81 _public prototype_ `TOptional<FTakeMetadata> GetTakeMetadata(int32 InTakeId) const;`
- L85 _protected prototype_ `void ExecuteProcessFinishedReporter(const UIngestCapability_ProcessHandle* InProcessHandle, TValueOrError<void, FIngestCapability_Error> InMaybeError);`
- L86 _protected prototype_ `void ExecuteProcessProgressReporter(const UIngestCapability_ProcessHandle* InProcessHandle, double InProgress);`
- L87 _protected prototype_ `void ExecuteUpdateTakeListCallback(UIngestCapability_UpdateTakeListCallback* InCallback, const TArray<int32>& InTakeIdentifiers);`
- L89 _protected prototype_ `int32 AddTake(FTakeMetadata InTakeMetadata);`
- L90 _protected prototype_ `void RemoveTake(int32 InTakeId);`
- L91 _protected prototype_ `void RemoveAllTakes();`
- L92 _protected prototype_ `bool UpdateTake(int32 InTakeId, FTakeMetadata InTakeMetadata);`
- L93 _protected prototype_ `bool IsUpdateTakeListAbortRequested() const;`
- L97 _private prototype_ `void ExecuteProcessTotalProgressReporter(const UIngestCapability_ProcessHandle* InProcessHandle, double InProgress);`
- L99 _private prototype_ `void RunIngestProcess(const UIngestCapability_ProcessHandle* InProcessHandle);`
- L101 _private prototype_ `virtual void RunDownloadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) = 0;`
- L102 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) = 0;`
- L103 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) = 0;`
- L105 _private member_ `UE::CaptureManager::FStopRequester StopRequester;`
- L106 _private member_ `UE::CaptureManager::FStopToken StopToken;`
- L108 _private member_ `mutable FCriticalSection TakeMetadataMutex;`
- L109 _private member_ `TMap<int32, FTakeMetadata> TakeMetadataMap;`
- L111 _private member_ `std::atomic_int32_t CurrentTakeId = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/LiveLinkCapabilities/Public/Streaming/LiveLinkDeviceCapability_Streaming.h` (Public)


#### class `ULiveLinkDeviceCapability_Streaming`  
`class ULiveLinkDeviceCapability_Streaming : public ULiveLinkDeviceCapability`  
_L12-34_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `ULiveLinkDeviceCapability`
- L19 _public prototype_ `ULiveLinkDeviceCapability_Streaming() = default;`
- L22 _public prototype_ `virtual void OnDeviceSubsystemInitialized();` — Called at completion of Live Link device subsystem initialization.
- L25 _public prototype_ `virtual void OnDeviceSubsystemDeinitializing();` — Called at the beginning of Live Link device subsystem de-initialization.
- L27 _public prototype_ `virtual SHeaderRow::FColumn::FArguments& GenerateHeaderForColumn(const FName InColumnId, SHeaderRow::FColumn::FArguments& InArgs) override;`
- L28 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidgetForColumn(const FName InColumnId, const FLiveLinkDeviceWidgetArguments& InArgs, ULiveLinkDevice* InDevice) override;`
- L32 _private prototype_ `void OnDeviceAdded(FGuid InGuid, ULiveLinkDevice* InDevice);`
- L33 _private prototype_ `void OnDeviceRemoved(FGuid InGuid, ULiveLinkDevice* InDevice);`

#### class `ILiveLinkDeviceCapability_Streaming`  
`class ILiveLinkDeviceCapability_Streaming : public ILiveLinkDeviceCapability`  
_L36-76_
- inherits: `ILiveLinkDeviceCapability`
- L43 _public prototype_ `ILiveLinkDeviceCapability_Streaming();`
- L46 _public prototype_ `void StartStreaming();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Streaming")`
- L47 _public prototype_ `void StartStreaming_Implementation();`
- L50 _public prototype_ `void StopStreaming();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Streaming")`
- L51 _public prototype_ `void StopStreaming_Implementation();`
- L54 _public prototype_ `bool IsStreaming() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Streaming")`
- L55 _public prototype_ `bool IsStreaming_Implementation() const;`
- L58 _public prototype_ `class UMediaSource* GetMediaSource() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Live Link Device|Streaming")`
- L59 _public prototype_ `class UMediaSource* GetMediaSource_Implementation() const;`
- L63 _protected prototype_ `void SetMediaSourceName(const FString& InName);`
- L64 _protected prototype_ `void SetMediaSource(class UMediaSource* InMediaSource);`
- L65 _protected prototype_ `void DeleteMediaSource();`
- L69 _private prototype_ `void Init();`
- L70 _private prototype_ `void Deinit();`
- L75 _private member_ `TSharedPtr<FImpl> Impl;`
