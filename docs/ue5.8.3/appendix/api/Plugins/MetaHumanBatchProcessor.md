# Plugins / MetaHumanBatchProcessor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor`
- headers: 7; symbols: 123
- symbol kinds: class=10, delegate=1, enum=1, enumerator=5, function=2, member=60, namespace=1, prototype=38, struct=5
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor, ContentBrowser, ContentBrowserData, Engine, MetaHumanCore, MetaHumanCoreTech, MetaHumanCoreTechLib, MetaHumanPerformance, MetaHumanPipeline, MetaHumanPipelineCore, MetaHumanSpeech2Face, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Private/MetaHumanBatchLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanBatch, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanBatch, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Private/MetaHumanBatchMenuExtensions.h` (Private)


#### class `FMetaHumanBatchMenuExtensions`  
`class FMetaHumanBatchMenuExtensions`  
_L9-22_
- L12 _public prototype_ `FMetaHumanBatchMenuExtensions();`
- L13 _public prototype_ `~FMetaHumanBatchMenuExtensions();`
- L15 _public prototype_ `void RegisterMenuExtensions();`
- L16 _public prototype_ `void UnregisterMenuExtensions();`
- L19 _private prototype_ `void AddMenuExtensions();`
- L20 _private prototype_ `void AddSoundWaveMenuExtensions();`
- L21 _private prototype_ `void AddPerformanceMenuExtensions();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Private/MetaHumanBatchProcessorModule.h` (Private)


#### class `FMetaHumanBatchProcessorModule`  
`class FMetaHumanBatchProcessorModule : public IModuleInterface`  
_L9-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `TUniquePtr<FMetaHumanBatchMenuExtensions> MetaHumanBatchMenuExtensions;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Private/SMetaHumanBatchExportPathDialog.h` (Private)


#### struct `FCanProcessResult`  
`struct FCanProcessResult`  
_L10-14_
- L12 _public member_ `bool bCanProcess;`
- L13 _public member_ `FText CanProcessText;`

#### class `SMetaHumanBatchExportPathDialog`  
`class SMetaHumanBatchExportPathDialog: public SWindow`  
_L17-61_
- inherits: `SWindow`
- desc: dialog to select path to export to
- L22 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanBatchExportPathDialog)`
- L23 _public prototype_ `SLATE_ARGUMENT(FString, AssetTypeName) SLATE_ARGUMENT(EditorAnimUtils::FNameDuplicationRule*, NameRule) SLATE_ARGUMENT(FString, DefaultFolder) SLATE_ARGUMENT(FString, PrefixHint) SLATE_ATTRIBUTE(FCanProcessResult, CanProcessConditional) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `EAppReturnType::Type ShowModal();` — displays the dialog in a blocking fashion
- L37 _private prototype_ `FReply OnButtonClick(EAppReturnType::Type InButtonID);`
- L40 _private prototype_ `void UpdateExampleText();` — example rename text
- L43 _private prototype_ `FText GetFolderPath() const;` — modify folder output path
- L46 _private prototype_ `static FString ConvertToCleanString(const FText& InToClean);` — remove characters not allowed in asset names
- L48 _private member_ `FText ExampleText;` — The rename rule sample text
- L49 _private member_ `EAppReturnType::Type UserResponse = EAppReturnType::Cancel;`
- L52 _private member_ `EditorAnimUtils::FNameDuplicationRule* NameRule = nullptr;` — the name rule are editing with this pop-up window
- L55 _private member_ `TAttribute<FCanProcessResult> CanProcessConditional;` — Conditional to determine if you can proceed
- L56 _private member_ `bool bCanProcess = true;`
- L57 _private member_ `FText CanProcessText;`
- L59 _private prototype_ `bool CanProcess() const;`
- L60 _private prototype_ `void UpdateCanProcess();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace EditorAnimUtils`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Public/MetaHumanBatchOperation.h` (Public)


#### enum `EBatchOperationStepsFlags`  
`enum class EBatchOperationStepsFlags : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `SoundWaveToPerformance = (1 << 0)` — Create a MetaHuman performance from sound wave asset and set up ready for processing
- L23 _public enumerator_ `ProcessPerformance = (1 << 1)` — Process the MetaHuman performance
- L24 _public enumerator_ `ExportAnimSequence = (1 << 2)` — Export Anim Sequence from processed performance.
- L25 _public enumerator_ `ExportLevelSequence = (1 << 3)` — Export Level Sequence from processed performance.

#### struct `FMetaHumanBatchOperationContext`  
`struct FMetaHumanBatchOperationContext`  
_L31-72_
- desc: Data needed to run a batch operation on a set of speech audio assets to animation
- L35 _public member_ `TArray<TWeakObjectPtr<UObject>> AssetsToProcess;` — The source assets to process
- L38 _public member_ `EBatchOperationStepsFlags BatchStepsFlags = EBatchOperationStepsFlags::None;` — Processing steps to be performed on assets
- L41 _public member_ `EditorAnimUtils::FNameDuplicationRule PerformanceNameRule;` — Rename rules for duplicated assets
- L42 _public member_ `EditorAnimUtils::FNameDuplicationRule ExportedAssetNameRule;`
- L45 _public member_ `bool bOverrideAssets = false;` — Set to override existing output assets, otherwise a unique asset name is created
- L48 _public member_ `bool bGenerateBlinks = true;` — Processing options
- L49 _public member_ `bool bMixAudioChannels = true;`
- L50 _public member_ `uint32 AudioChannelIndex = 0;`
- L51 _public member_ `FAudioDrivenAnimationSolveOverrides AudioDrivenAnimationSolveOverrides;`
- L52 _public member_ `EAudioDrivenAnimationOutputControls AudioDrivenAnimationOutputControls = EAudioDrivenAnimationOutputControls::FullFace;`
- L55 _public member_ `bool bEnableHeadMovement = false;` — Export options
- L56 _public member_ `TEnumAsByte<ERichCurveInterpMode> CurveInterpolation = ERichCurveInterpMode::RCIM_Linear;`
- L57 _public member_ `bool bRemoveRedundantKeys = true;`
- L60 _public member_ `TSoftObjectPtr<UObject> TargetSkeletonOrSkeletalMesh;` — Skeleton or SkelMesh used for exported anim sequence
- L63 _public member_ `bool bExportAudioTrack = true;` — Level sequence export options
- L64 _public member_ `bool bExportCamera = true;`
- L65 _public member_ `TSoftObjectPtr<class UBlueprint> TargetMetaHuman;`
- L68 _public prototype_ `bool IsValid() const;` — Is the data configured in such a way that we could process
- L70 _public prototype_ `bool ValidatePerformanceNameRule() const;`
- L71 _public prototype_ `bool ValidateExportAssetNameRule() const;`

#### class `UMetaHumanBatchOperation`  
`class UMetaHumanBatchOperation : public UObject`  
_L76-107_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Encapsulate ability to process performances from SoundWave assets and into animation
- L83 _public prototype_ `void RunProcess(FMetaHumanBatchOperationContext& InContext);` — Run the process from audio to animation
- L87 _private prototype_ `TObjectPtr<UMetaHumanPerformance> CreatePerformanceFromSoundWave(const FMetaHumanBatchOperationContext& InContext, TObjectPtr<USoundWave> InSoundWave, FScopedSlowTask& InProgress);`
- L88 _private prototype_ `TObjectPtr<UMetaHumanPerformance> GetTransientPerformance(const FMetaHumanBatchOperationContext& InContext, TObjectPtr<USoundWave> InSoundWave);`
- L89 _private prototype_ `void SetupPerformance(const FMetaHumanBatchOperationContext& InContext, TObjectPtr<USoundWave> InSoundWave, TObjectPtr<UMetaHumanPerformance> InPerformance);`
- L90 _private prototype_ `bool ProcessPerformanceAsset(const FMetaHumanBatchOperationContext& InContext, TObjectPtr<UMetaHumanPerformance> InPerformance, FScopedSlowTask& InProgress);`
- L91 _private prototype_ `void ExportAnimationSequence(const FMetaHumanBatchOperationContext& InContext, TObjectPtr<USoundWave> InSourceSoundWave, TObjectPtr<UMetaHumanPerformance> InPerformance, FScopedSlowTask& InProgress);`
- L92 _private prototype_ `void ExportLevelSequence(const FMetaHumanBatchOperationContext& InContext, TObjectPtr<USoundWave> InSourceSoundWave, TObjectPtr<UMetaHumanPerformance> InPerformance, FScopedSlowTask& InProgress);`
- L95 _private prototype_ `void OverwriteExistingAssets(const FMetaHumanBatchOperationContext& InContext, FScopedSlowTask& InProgress);` — Overwrite existing assets
- L97 _private prototype_ `void NotifyResults(const FMetaHumanBatchOperationContext& InContext, FScopedSlowTask& InProgress, bool bInErrorOccurred);` — Notify user of results
- L99 _private prototype_ `void CleanupIfCancelled(const FScopedSlowTask& Progress) const;` — If user cancelled half way, cleanup all new created assets
- L101 _private member_ `TMap<FAssetData, FAssetData> CreatedAssets;`
- L102 _private member_ `TObjectPtr<UMetaHumanPerformance> TransientPerformance;`
- L104 _private member_ `TObjectPtr<USkeleton> ExportSkeleton;`
- L105 _private member_ `TObjectPtr<USkeletalMesh> ExportSkeletalMesh;`
- L106 _private member_ `TObjectPtr<class UBlueprint> ExportMetaHuman;`

#### Free symbols / members of external scopes

- L27 _prototype_ `ENUM_CLASS_FLAGS(EBatchOperationStepsFlags);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Public/MetaHumanSpeechProcessingSettings.h` (Public)


#### struct `FMetaHumanSpeechProcessingSettings`  
`struct FMetaHumanSpeechProcessingSettings`  
_L13-40_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `bool bGenerateBlinks = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings")` — Option to generate blinks
- L24 _public member_ `bool bMixAudioChannels = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings")` — Option to down mix audio channels into single channel before processing
- L28 _public member_ `int32 AudioChannelIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings", meta = (EditCondition = "bMixAudioChannels == false", ClampMin = 0, ClampMax = 64))` — Audio channel used for processing
- L32 _public member_ `EAudioDrivenAnimationOutputControls OutputControls = EAudioDrivenAnimationOutputControls::FullFace;` — `UPROPERTY(EditAnywhere, Category = "Processing Settings", meta = (DisplayName = "Process Mask"))` — Process the full face or a particular subset of controls.
- L36 _public member_ `FAudioDrivenAnimationSolveOverrides SolveOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings", meta = (DisplayName = "Solve Overrides"))` — Overrides for the solve.
- L39 _public member_ `bool bEnableHeadMovement = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")`

#### struct `FExportAnimSequenceSettings`  
`struct FExportAnimSequenceSettings`  
_L43-63_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `bool bOverwriteAssets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Option to override existing output assets. Otherwise, a unique asset name is generated by appending a number at the end of the asset name
- L54 _public member_ `TSoftObjectPtr<UObject> TargetSkeletonOrSkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (AllowedClasses = "/Script/Engine.Skeleton, /Script/Engine.SkeletalMesh"))` — The Skeleton or Skeletal Mesh to be used when recording the Animation Sequence
- L58 _public member_ `TEnumAsByte<ERichCurveInterpMode> CurveInterpolation = ERichCurveInterpMode::RCIM_Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — This defines how values between keys are calculated for curves
- L62 _public member_ `bool bRemoveRedundantKeys = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Whether or not to remove redundant keys, default to true

#### struct `FExportLevelSequenceSettings`  
`struct FExportLevelSequenceSettings`  
_L66-98_
- reflection: `USTRUCT(BlueprintType)`
- L73 _public member_ `bool bOverwriteAssets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Option to override existing output assets. Otherwise, a unique asset name is generated by appending a number at the end of the asset name
- L77 _public member_ `TEnumAsByte<ERichCurveInterpMode> CurveInterpolation = ERichCurveInterpMode::RCIM_Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — This defines how values between keys are calculated for curves
- L81 _public member_ `bool bRemoveRedundantKeys = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Whether or not to remove redundant keys, default to true
- L85 _public member_ `TSoftObjectPtr<class UBlueprint> TargetMetaHumanClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", DisplayName = "Target MetaHuman Class")` — Target actor to be spawned in the exported level sequence
- L89 _public member_ `bool bExportAudioTrack = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Option to export the audio track in the level sequence
- L93 _public member_ `bool bExportCamera = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Option to export the camera track in the level sequence

#### class `UMetaHumanSpeechToPerformance`  
`class UMetaHumanSpeechToPerformance : public UObject`  
_L101-117_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L109 _public member_ `TSoftObjectPtr<UObject> VisualizationMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings", meta = (AllowedClasses = "/Script/Engine.Skeleton, /Script/Engine.SkeletalMesh"))` — The visualization mesh to be set in the MetaHuman performances
- L112 _public member_ `FMetaHumanSpeechProcessingSettings ProcessingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings", meta = (ShowOnlyInnerProperties))`
- L116 _public member_ `bool bOverwriteAssets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Option to override existing output assets. Otherwise, a unique asset name is generated by appending a number at the end of the asset name

#### class `UMetaHumanExportAnimSequenceSettings`  
`class UMetaHumanExportAnimSequenceSettings : public UObject`  
_L120-128_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L127 _public member_ `FExportAnimSequenceSettings ExportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (ShowOnlyInnerProperties))`

#### class `UMetaHumanSpeechToAnimSequenceProcessingSettings`  
`class UMetaHumanSpeechToAnimSequenceProcessingSettings : public UObject`  
_L132-143_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L139 _public member_ `FMetaHumanSpeechProcessingSettings ProcessingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings", meta = (ShowOnlyInnerProperties))`
- L142 _public member_ `FExportAnimSequenceSettings ExportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (ShowOnlyInnerProperties))`

#### class `UMetaHumanExportLevelSequenceSettings`  
`class UMetaHumanExportLevelSequenceSettings : public UObject`  
_L147-155_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L154 _public member_ `FExportLevelSequenceSettings ExportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (ShowOnlyInnerProperties))`

#### class `UMetaHumanSpeechToLevelSequenceSettings`  
`class UMetaHumanSpeechToLevelSequenceSettings : public UObject`  
_L158-168_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L164 _public member_ `FMetaHumanSpeechProcessingSettings ProcessingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Settings", meta = (ShowOnlyInnerProperties))`
- L167 _public member_ `FExportLevelSequenceSettings ExportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (ShowOnlyInnerProperties))`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanBatchProcessor/Public/SMetaHumanSpeechProcessingSettings.h` (Public)


#### class `SMetaHumanSpeechToAnimProcessingSettings`  
`class SMetaHumanSpeechToAnimProcessingSettings : public SCompoundWidget`  
_L10-37_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanSpeechToAnimProcessingSettings)`
- L15 _public prototype_ `SLATE_ARGUMENT(UObject*, Settings) SLATE_ATTRIBUTE(bool, CanProcessConditional) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `EAppReturnType::Type ShowModel();`
- L23 _public prototype_ `bool CanProcess() const;`
- L25 _public prototype_ `FReply ProcessClicked();`
- L26 _public prototype_ `FReply CancelClicked();`
- L29 _public member_ `TObjectPtr<UObject> SettingsObject;`
- L30 _public member_ `TAttribute<bool> CanProcessConditional;`
- L33 _private prototype_ `void RequestDestroyWindow();`
- L35 _private member_ `TWeakPtr<SWindow> DialogWindow;`
- L36 _private member_ `EAppReturnType::Type UserResponse = EAppReturnType::Cancel;`
