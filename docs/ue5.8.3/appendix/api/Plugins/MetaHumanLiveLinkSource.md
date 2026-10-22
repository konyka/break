# Plugins / MetaHumanLiveLinkSource

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSource`
- headers: 5; symbols: 68
- symbol kinds: class=6, delegate=1, enum=1, enumerator=3, function=1, member=20, prototype=36
- PrivateDependencyModuleNames: Core, CoreUObject, MetaHumanCoreTech, Projects, RenderCore, Slate, SlateCore
- PublicDependencyModuleNames: Engine, LiveLink, LiveLinkInterface

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSource/Private/MetaHumanLiveLinkSourceModule.h` (Private)


#### class `FMetaHumanLiveLinkSourceModule`  
`class FMetaHumanLiveLinkSourceModule : public IModuleInterface`  
_L7-16_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSource/Public/MetaHumanLiveLinkSourceBlueprint.h` (Public)


#### class `UMetaHumanLiveLinkSourceBlueprint`  
`class UMetaHumanLiveLinkSourceBlueprint : public UObject`  
_L12-32_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- L19 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubjectAdded, FLiveLinkSubjectKey, Subject);`
- L22 _public member_ `FOnSubjectAdded SubjectAdded;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "MetaHuman Live Link")`
- L25 _public prototype_ `virtual void PostInitProperties() override;` — PostInitProperties override.
- L29 _private prototype_ `void OnSubjectChanged();`
- L31 _private member_ `TArray<FLiveLinkSubjectKey> Subjects;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubjectAdded, FLiveLinkSubjectKey, Subject);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSource/Public/MetaHumanLiveLinkSourceStyle.h` (Public)


#### class `FMetaHumanLiveLinkSourceStyle`  
`class FMetaHumanLiveLinkSourceStyle : public FSlateStyleSet`  
_L9-21_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `static FMetaHumanLiveLinkSourceStyle& Get();`
- L15 _public prototype_ `static void Register();`
- L16 _public prototype_ `static void Unregister();`
- L20 _private prototype_ `FMetaHumanLiveLinkSourceStyle();`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSource/Public/MetaHumanLiveLinkSubjectSettings.h` (Public)


#### class `UMetaHumanLiveLinkSubjectSettings`  
`class UMetaHumanLiveLinkSubjectSettings : public ULiveLinkHubSubjectSettings`  
_L15-136_
- reflection: `UCLASS(BlueprintType)`
- inherits: `ULiveLinkHubSubjectSettings`
- L21 _public prototype_ `UMetaHumanLiveLinkSubjectSettings();`
- L23 _public prototype_ `virtual void PostLoad() override;`
- L26 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L38 _public member_ `bool bIsLiveProcessing = false;` — `UPROPERTY(Transient)` — The bIsLiveProcessing flag will be set to true when the settings are being used by a subject that is producing live data. This is the typical case, eg VideoSubjectSettings being used by a VideoSubject class. The bIsLiveProcessing flag will be set to false when the settings are being used by a subject that is playing back pre-recorded data. This will be the case when using Take Recorder. In this case we should hide all controls that would attempt to change the Live Link data being produced, eg head translation on/off, since these will not apply to pre-recorded data.
- L41 _public member_ `int32 CaptureNeutralsProperty = 0;` — `UPROPERTY(EditAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — A dummy property thats customized to a button
- L45 _public member_ `TArray<FName> Properties;` — `UPROPERTY(EditAnywhere, Category = "Controls|Calibration", meta = (ToolTip = "The properties to calibrate.", EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Calibration
- L48 _public prototype_ `void SetCalibrationProperties(UPARAM(DisplayName = "Properties") const TArray<FName>& InPr` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L51 _public prototype_ `void GetCalibrationProperties(UPARAM(DisplayName = "Properties") TArray<FName>& OutProperti` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L54 _public member_ `float Alpha = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Controls|Calibration", meta = (ClampMin = 0, ClampMax = 1, EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L57 _public prototype_ `void SetCalibrationAlpha(UPARAM(DisplayName = "Alpha") float InAl` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L60 _public prototype_ `void GetCalibrationAlpha(UPARAM(DisplayName = "Alpha") float& OutAlpha) c` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L63 _public member_ `TArray<float> NeutralFrame;` — `UPROPERTY(EditAnywhere, Category = "Controls|Calibration", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L66 _public prototype_ `void SetCalibrationNeutralFrame(UPARAM(DisplayName = "NeutralFrame") const TArray<float>& InNe` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L69 _public prototype_ `void GetCalibrationNeutralFrame(UPARAM(DisplayName = "NeutralFrame") TArray<float>& OutNeutralF` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L72 _public member_ `int32 CaptureNeutralFrameCountdown = -1;` — `UPROPERTY(EditAnywhere, Category = "Controls|Calibration", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L76 _public member_ `TObjectPtr<UMetaHumanRealtimeSmoothingParams> Parameters;` — `UPROPERTY(EditAnywhere, Category = "Controls|Smoothing", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Smoothing
- L79 _public prototype_ `void SetSmoothing(UMetaHumanRealtimeSmoothingParams* Smoothing);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L82 _public prototype_ `void GetSmoothing(UMetaHumanRealtimeSmoothingParams*& Smoothing) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L88 _public member_ `FVector NeutralHeadTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Controls|Head Pose", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Head translation
- L91 _public prototype_ `void SetNeutralHeadTranslation(UPARAM(DisplayName = "NeutralHeadTranslation") const FVector& InNe` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L94 _public prototype_ `void GetNeutralHeadTranslation(UPARAM(DisplayName = "NeutralHeadTranslation") FVector& OutNeutralH` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L98 _public member_ `FRotator NeutralHeadOrientation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "Controls|Head Pose", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Head orientation
- L101 _public prototype_ `void SetNeutralHeadOrientation(UPARAM(DisplayName = "NeutralHeadOrientation") const FRotator& InNe` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L104 _public prototype_ `void GetNeutralHeadOrientation(UPARAM(DisplayName = "NeutralHeadOrientation") FRotator& OutNeutralH` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L107 _public member_ `FTransform NeutralHeadPoseInverse = FTransform::Identity;` — `UPROPERTY()`
- L110 _public member_ `int32 CaptureNeutralHeadPoseCountdown = -1;` — `UPROPERTY(EditAnywhere, Category = "Controls|Head Pose", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L113 _public prototype_ `virtual void CaptureNeutrals();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L116 _public prototype_ `virtual void CaptureNeutralFrame();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L119 _public prototype_ `virtual void CaptureNeutralHeadPose();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L122 _public function_ `virtual void CaptureNeutralHeadTranslation()` — `UE_DEPRECATED(5.7, "CaptureNeutralHeadTranslation() is deprecated. Use CaptureNeutralHeadPose() instead.")`
- L126 _public member_ `int32 CaptureNeutralHeadTranslationCountdown = -1;` — `UE_DEPRECATED(5.7, "CaptureNeutralHeadTranslationCountdown is deprecated. Use CaptureNeutralHeadPoseCountdown instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "CaptureNeutralHeadTranslationCountdown is deprecated. Use CaptureNeutralHeadPoseCountdown instead."))`
- L128 _public prototype_ `bool PreProcess(const FLiveLinkBaseStaticData& InStaticData, FLiveLinkBaseFrameData& InOutFrameData);`
- L132 _private member_ `TSharedPtr<FMetaHumanRealtimeCalibration> Calibration;`
- L134 _private member_ `TSharedPtr<FMetaHumanRealtimeSmoothing> Smoothing;`
- L135 _private member_ `double LastTime = 0;`

#### enum `EMetaHumanLiveLinkHeadPoseMode`  
`enum class EMetaHumanLiveLinkHeadPoseMode : uint8`  
_L141-146_
- reflection: `UENUM(meta = (Bitmask, BitmaskEnum))`
- L143 _public enumerator_ `None = 0`
- L144 _public enumerator_ `CameraRelativeTranslation = 1 << 0`
- L145 _public enumerator_ `Orientation = 1 << 1`

#### Free symbols / members of external scopes

- L147 _prototype_ `ENUM_CLASS_FLAGS(EMetaHumanLiveLinkHeadPoseMode);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSource/Public/MetaHumanSmoothingPreProcessor.h` (Public)


#### class `UMetaHumanSmoothingPreProcessor`  
`class UMetaHumanSmoothingPreProcessor : public ULiveLinkFramePreProcessor`  
_L12-60_
- reflection: `UCLASS(meta=(DisplayName="MetaHuman Smoothing"))`
- inherits: `ULiveLinkFramePreProcessor`
- L35 _public prototype_ `UMetaHumanSmoothingPreProcessor();`
- L40 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L47 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L48 _public prototype_ `virtual FWorkerSharedPtr FetchWorker() override;`
- L54 _public member_ `TObjectPtr<UMetaHumanRealtimeSmoothingParams> Parameters;` — `UPROPERTY(EditAnywhere, Category="Smoothing")` — Smoothing parameters
- L59 _private member_ `TSharedPtr<FMetaHumanSmoothingPreProcessorWorker, ESPMode::ThreadSafe> Worker;` — The worker object instance

#### class `UMetaHumanSmoothingPreProcessor::FMetaHumanSmoothingPreProcessorWorker`  
`class FMetaHumanSmoothingPreProcessorWorker : public ILiveLinkFramePreProcessorWorker, public FMetaHumanRealtimeSmoothing`  
_L18-33_
- inherits: `ILiveLinkFramePreProcessorWorker,FMetaHumanRealtimeSmoothing`
- L21 _public prototype_ `FMetaHumanSmoothingPreProcessorWorker(const TMap<FName, FMetaHumanRealtimeSmoothingParam>& InSmoothingParams);`
- L25 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override;`
- L26 _public prototype_ `virtual bool PreProcessFrame(const FLiveLinkStaticDataStruct& InStaticData, FLiveLinkFrameDataStruct& InOutFrame) override;`
- L32 _private member_ `double LastTime = 0;`
