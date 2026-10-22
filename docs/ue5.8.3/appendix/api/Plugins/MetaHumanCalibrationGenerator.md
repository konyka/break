# Plugins / MetaHumanCalibrationGenerator

- module root: `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator`
- headers: 11; symbols: 220
- symbol kinds: class=14, delegate=5, enum=1, enumerator=5, function=8, macro=2, member=78, prototype=93, struct=4, typedef=10
- PrivateDependencyModuleNames: CaptureDataEditor, CaptureDataUtils, CaptureUtils, ContentBrowser, ImageCore, ImageWrapper, ImgMedia, InputCore, Json, JsonUtilities, MetaHumanCalibrationCore, MetaHumanCalibrationLib, MetaHumanImageViewer, OpenCV, OpenCVHelper, OutputLog, Projects, SequencerWidgets, SettingsEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationAutoFrameSelector.h` (Private)


#### class `UMetaHumanCalibrationAutoFrameSelector`  
`class UMetaHumanCalibrationAutoFrameSelector : public UObject`  
_L13-23_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- L20 _public prototype_ `TArray<int32> Run(const UFootageCaptureData* InCaptureData, const UMetaHumanCalibrationGeneratorConfig* InConfig, const UMetaHumanCalibrationGeneratorOptions* InOptions);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Frame Selector")`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationBatchLibrary.h` (Private)


#### struct `FMetaHumanCalibrationBatchResult`  
`struct FMetaHumanCalibrationBatchResult`  
_L15-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: Result for a single capture-data asset processed in a batch calibration run.
- L21 _public member_ `TObjectPtr<UFootageCaptureData> CaptureData = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Calibration|Batch")` — The capture data asset that was processed.
- L25 _public member_ `bool bSuccess = false;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Calibration|Batch")` — Whether calibration succeeded for this asset.
- L29 _public member_ `FString ErrorMessage;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Calibration|Batch")` — Error message when bSuccess is false.
- L33 _public member_ `double RMSError = 0.0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Calibration|Batch")` — RMS reprojection error of the generated calibration (lower is better). Zero on failure.
- L37 _public member_ `FString CalibrationAssetPath;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman|Calibration|Batch")` — Content-browser path to the created CameraCalibration asset. Empty on failure.

#### class `UMetaHumanCalibrationBatchLibrary`  
`class UMetaHumanCalibrationBatchLibrary : public UBlueprintFunctionLibrary`  
_L51-113_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for batch camera calibration generation. Provides three levels of API: - BatchGenerateCalibration: Simple interface — just assets and board config. - BatchGenerateCalibrationWithOptions: Advanced interface with per-asset Options. - ConstructDefaultOptionsForCaptureData: Utility to build default Options for a CaptureData asset. Cancellation is supported via the FScopedSlowTask progress dialog.
- L73 _public prototype_ `static UMetaHumanCalibrationGeneratorOptions* ConstructDefaultOptionsForCaptureData( const UFootageCaptureData* CaptureData);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Calibration|Batch", meta = (DisplayName = "Construct Default Options For Capture Data"))` — Construct a default UMetaHumanCalibrationGeneratorOptions for a CaptureData asset. Sets AssetName to CC_<CaptureDataName>, PackagePath to the same directory as the CaptureData asset, AreaOfInterest to full frame bounds per camera, SharpnessThreshold to 5.0, and bAutoSaveAssets to true. SelectedFrames is left empty so that automatic frame selection will be used. The returned Options can be customised before passing to BatchGenerateCalibrationWithOptions. @param CaptureData The capture data asset to configure options for. @return A new Options object with sensible defaults, or nullptr if CaptureData is null.
- L90 _public prototype_ `static TArray<FMetaHumanCalibrationBatchResult> BatchGenerateCalibration( const TArray<UFootageCaptureData*>& CaptureDataAssets, const UMetaHumanCalibrationGeneratorConfig* BoardConfig);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Calibration|Batch", meta = (DisplayName = "Batch Generate Camera Calibration"))` — Run calibration generation across multiple UFootageCaptureData assets with automatic defaults. For each asset, constructs default Options via ConstructDefaultOptionsForCaptureData and runs calibration with automatic frame selection. Output is placed next to each CaptureData asset. This is the simplest entry point for batch processing. @param CaptureDataAssets Footage capture data assets to process. @param BoardConfig      Calibration board pattern configuration (dimensions and square size). @return Per-asset results in input order.
- L109 _public prototype_ `static TArray<FMetaHumanCalibrationBatchResult> BatchGenerateCalibrationWithOptions( const TArray<UFootageCaptureData*>& CaptureDataAssets, const UMetaHumanCalibrationGeneratorConfig* BoardConfig, const TArray<UMetaHumanCalibrationGeneratorOptions*>& OptionsPerAsset);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Calibration|Batch", meta = (DisplayName = "Batch Generate Camera Calibration With Options"))` — Run calibration generation with per-asset Options for full control. Each CaptureData asset is paired with a corresponding Options object. If an Options object has empty SelectedFrames, automatic frame selection is used and the SelectedFrames array on the Options object will be populated. @param CaptureDataAssets Footage capture data assets to process. @param BoardConfig      Calibration board pattern configuration (dimensions and square size). @param OptionsPerAsset  Per-asset options (must be same length as InCaptureDataAssets). @return Per-asset results in input order.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationGenerator.h` (Private)


#### class `UMetaHumanCalibrationGenerator`  
`class UMetaHumanCalibrationGenerator : public UObject`  
_L16-52_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- L22 _public prototype_ `UMetaHumanCalibrationGenerator();`
- L25 _public prototype_ `bool Init(const UMetaHumanCalibrationGeneratorConfig* InConfig);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Generator")`
- L28 _public prototype_ `bool ConfigureCameras(const UFootageCaptureData* InCaptureData);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Generator")`
- L31 _public prototype_ `bool Process(UFootageCaptureData* InCaptureData, const UMetaHumanCalibrationGeneratorOptions* InOptions);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Generator")`
- L34 _public prototype_ `double GetLastRMSError() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Generator")`
- L37 _public prototype_ `FString GetLastError();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Generator")`
- L39 _public prototype_ `bool Reset(const UMetaHumanCalibrationGeneratorConfig* InConfig, const UFootageCaptureData* InCaptureData);`
- L42 _public prototype_ `static bool ExportCalibration(UCameraCalibration* InCameraCalibration, const FDirectoryPath& InPath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Generator")`
- L46 _private member_ `TSharedPtr<UE::Wrappers::FMetaHumanStereoCalibrator> StereoCalibrator;`
- L47 _private member_ `double LastRMSError = 0.0f;`
- L48 _private member_ `FString ErrorMessage;`
- L50 _private member_ `bool bInitialized = false;`
- L51 _private member_ `bool bCamerasConfigured = false;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationGeneratorConfig.h` (Private)


#### class `UMetaHumanCalibrationGeneratorConfig`  
`class UMetaHumanCalibrationGeneratorConfig : public UObject`  
_L15-35_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Options that will used as part of the camera calibration process
- L24 _public member_ `int32 BoardPatternWidth = 11;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = "1", UIMin = "1", ClampMax = "50", UIMax = "50", NoSpinbox = "true"))` — The width of the chessboard used to record the calibration footage.
- L28 _public member_ `int32 BoardPatternHeight = 16;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = "1", UIMin = "1", ClampMax = "50", UIMax = "50", NoSpinbox = "true"))` — The height of the chessboard used to record the calibration footage.
- L32 _public member_ `float BoardSquareSize = 0.75f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Units = "Centimeters"))` — The square size of the chessboard used to record the calibration footage.
- L34 _public prototype_ `TValueOrError<void, FString> CheckConfigValidity() const;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationGeneratorOptions.h` (Private)


#### class `UMetaHumanCalibrationGeneratorOptions`  
`class UMetaHumanCalibrationGeneratorOptions : public UObject`  
_L16-82_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Options that will used as part of the camera calibration process
- L25 _public member_ `FString AssetName = TEXT("CC_` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (ContentDir))` — Name of the Camera Calibration asset.
- L29 _public member_ `FDirectoryPath PackagePath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (ContentDir))` — Content Browser path where the Lens Files and Camera Calibration assets will be created.
- L33 _public member_ `bool bAutoSaveAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")` — Automatically save created assets.
- L37 _public member_ `TArray<int32> SelectedFrames;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Options")` — Frames selected for the calibration process
- L47 _public member_ `int32 SampleRate_DEPRECATED = 30;` — `UE_DEPRECATED(5.7, "SampleRate is deprecated. Use automatic frame selection to obtain the list of frames.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "SampleRate is deprecated. Use automatic frame selection to obtain the list of frames."))` — Rate at which the camera calibration process will sample frames. Example: 30 will use every 30th frame. Note: Low sample rates will take longer for processing to complete.
- L52 _public member_ `int32 BoardPatternWidth_DEPRECATED = 10;` — `UE_DEPRECATED(5.7, "Board Pattern Width is deprecated. Use UMetaHumanCalibrationGeneratorConfig object.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Board Pattern Width is deprecated. Use UMetaHumanCalibrationGeneratorConfig object."))` — The width of the chessboard used to record the calibration footage.
- L57 _public member_ `int32 BoardPatternHeight_DEPRECATED = 15;` — `UE_DEPRECATED(5.7, "Board Pattern Height is deprecated. Use UMetaHumanCalibrationGeneratorConfig object.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Board Pattern Height is deprecated. Use UMetaHumanCalibrationGeneratorConfig object."))` — The width of the chessboard used to record the calibration footage.
- L62 _public member_ `float BoardSquareSize_DEPRECATED = 0.75f;` — `UE_DEPRECATED(5.7, "Board Square Size is deprecated. Use UMetaHumanCalibrationGeneratorConfig object.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Board Square Size is deprecated. Use UMetaHumanCalibrationGeneratorConfig object."))` — The square size of the chessboard used to record the calibration footage.
- L68 _public member_ `float SharpnessThreshold = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")` — Value represents the allowed blurriness (in pixels) of the frame that will be used for calibration process. If the frame has estimated blurriness higher than this threshold, the frame will be discarded.
- L71 _public member_ `TArray<FMetaHumanAreaOfInterest> AreaOfInterestsForCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L73 _public prototype_ `TValueOrError<void, FString> CheckOptionsValidity() const;`
- L78 _private prototype_ `void SetSelectedFrames(TArray<int32> InSelectedFrames);` — `UFUNCTION(BlueprintCallable, Category = "Options")`
- L81 _private prototype_ `bool IsSelectedFramesEmpty() const;` — `UFUNCTION()`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationGeneratorState.h` (Private)


#### class `FMetaHumanCalibrationGeneratorState`  
`class FMetaHumanCalibrationGeneratorState`  
_L12-18_
- L16 _public member_ `TStrongObjectPtr<UMetaHumanCalibrationGeneratorConfig> Config;`
- L17 _public member_ `TStrongObjectPtr<UMetaHumanCalibrationGeneratorOptions> Options;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/MetaHumanCalibrationPatternDetector.h` (Private)


#### class `FMetaHumanCalibrationPatternDetector`  
`class FMetaHumanCalibrationPatternDetector`  
_L13-68_
- L21 _public typedef_ `using FDetectedFrame = TMap<FString, TArray<FVector2D>>;`
- L22 _public typedef_ `using FDetectedFrames = TMap<int32, FDetectedFrame>;`
- L37 _public prototype_ `DECLARE_DELEGATE_OneParam(FProgressReporter, double);`
- L39 _public typedef_ `using FFramePaths = TPair<FString, FString>;`
- L40 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<FFramePaths>, FOnFailureFrameProvider, const FFramePaths&, int32);`
- L42 _public prototype_ `static TUniquePtr<FMetaHumanCalibrationPatternDetector> CreateFromExistingCalibrator(TSharedPtr<UE::Wrappers::FMetaHumanStereoCalibrator> InStereoCalibrator);`
- L43 _public prototype_ `static TUniquePtr<FMetaHumanCalibrationPatternDetector> CreateFromNew(const FPatternInfo& InBoardInfo, const TArray<FCameraInfo>& InCameras, float InScale);`
- L45 _public prototype_ `FMetaHumanCalibrationPatternDetector(FPrivateToken, TSharedPtr<UE::Wrappers::FMetaHumanStereoCalibrator> InStereoCalibrator, TOptional<float> InScale = {});`
- L47 _public prototype_ `void SetOnProgressReporter(FProgressReporter InProgressReporter);`
- L48 _public prototype_ `void SetMaximumNumberOfThreads(int32 InMaximumNumberOfThreads);`
- L49 _public prototype_ `void SetStopToken(UE::CaptureManager::FStopToken InStopToken);`
- L51 _public prototype_ `FDetectedFrames DetectPatterns(const TPair<FString, FString>& InCameraNames, const TPair<TArray<FString>, TArray<FString>>& InFilteredFrames, float InSharpnessThreshold, FOnFailureFrameProvider InOnFailureFrameProvider = nullptr);`
- L56 _public prototype_ `TOptional<FDetectedFrame> DetectPattern(const TPair<FString, FString>& InCameraNames, const TPair<FString, FString>& InFramePath, float InSharpnessThreshold);`
- L62 _private member_ `TSharedPtr<UE::Wrappers::FMetaHumanStereoCalibrator> StereoCalibrator;`
- L63 _private member_ `TOptional<float> Scale;`
- L65 _private member_ `FProgressReporter ProgressReporter;`
- L66 _private member_ `int32 MaximumNumberOfThreads = 4;`
- L67 _private member_ `TOptional<UE::CaptureManager::FStopToken> StopToken;`

#### struct `FMetaHumanCalibrationPatternDetector::FPrivateToken`  
`struct FPrivateToken`  
_L17-17_

#### struct `FMetaHumanCalibrationPatternDetector::FPatternInfo`  
`struct FPatternInfo`  
_L24-29_
- L26 _public member_ `int32 Width;`
- L27 _public member_ `int32 Height;`
- L28 _public member_ `float SquareSize;`

#### struct `FMetaHumanCalibrationPatternDetector::FCameraInfo`  
`struct FCameraInfo`  
_L31-35_
- L33 _public member_ `FString Name;`
- L34 _public member_ `FIntVector2 Dimensions;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FProgressReporter, double);`
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<FFramePaths>, FOnFailureFrameProvider, const FFramePaths&, int32);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/Settings/MetaHumanCalibrationGeneratorSettings.h` (Private)


#### class `UMetaHumanCalibrationGeneratorSettings`  
`class UMetaHumanCalibrationGeneratorSettings : public UObject`  
_L14-70_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FCoverageMapChanged);`
- L24 _public member_ `float ScaleFactor = 1.0;` — `UPROPERTY(config, EditAnywhere, Category = "Visualization", meta = (ClampMin = "0.1", UIMin = "0.1", ClampMax = "1.0", UIMax = "1.0", NoSpinbox = "true"))` — Image scaling factor applied during grid detection for display purposes only. This does not affect the accuracy of grid detection during calibration generation
- L28 _public member_ `int32 NumberOfPointsThreshold = 50;` — `UPROPERTY(config, EditAnywhere, Category = "Visualization", meta = (ClampMin = "1", UIMin= "1"))` — Maximum number of points for which the block from the grid is considered covered 100%
- L32 _public member_ `FIntVector2 CoverageMap = FIntVector2(8, 8);` — `UPROPERTY(config, EditAnywhere, Category = "Visualization", meta = (ClampMin = "1", UIMin = "1", ClampMax = "64", UIMax = "64", NoSpinbox = "true"))` — Size of the map to be used for getting an estimate of the coverage of the chessboard in the footage
- L36 _public member_ `int32 AutomaticFrameSelectionSampleRate = 10;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Selection", meta = (ClampMin = "1", UIMin = "1"))` — The parameter used to determine which frames will be involved in the automatic frame selection (N-th frame)
- L40 _public member_ `int32 TargetNumberOfFrames = 30;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Selection")` — The number of frames that will be an output from the automatic frame selection process
- L44 _public member_ `int32 MinimumPointsPerBlock = 5;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Selection", meta = (ClampMin = "1", UIMin = "1"))` — Minimum number of points for which the block from the grid will be considerd occupied for a single frame
- L48 _public member_ `FIntVector2 AutomaticFrameSelectionCoverageMap = FIntVector2(6, 8);` — `UPROPERTY(config, EditAnywhere, Category = "Frame Selection", meta = (ClampMin = "1", UIMin = "1", ClampMax = "64", UIMax = "64", NoSpinbox = "true"))` — Size of the map for getting an estimate of the coverage for the automated frame selection process
- L52 _public member_ `FString LastConfigUsed;` — `UPROPERTY(config)` — Last config used to perform the calibration process
- L54 _public function_ `FCoverageMapChanged& OnCoverageMapChanged()`
- L61 _private function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override final`
- L69 _private member_ `FCoverageMapChanged CoverageMapChanged;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE(FCoverageMapChanged);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/Utils/MetaHumanCalibrationAutoFrameSelection.h` (Private)


#### class `FMetaHumanCalibrationAutoFrameSelection`  
`class FMetaHumanCalibrationAutoFrameSelection`  
_L12-30_
- L16 _public typedef_ `using FDetectedFrame = FMetaHumanCalibrationPatternDetector::FDetectedFrame;`
- L17 _public typedef_ `using FPatternInfo = FMetaHumanCalibrationPatternDetector::FPatternInfo;`
- L19 _public prototype_ `FMetaHumanCalibrationAutoFrameSelection(TPair<FString, FString> InCameraNames, TPair<FIntVector2, FIntVector2> InImageSizes, TPair<FBox2D, FBox2D> InAreasOfInterest);`
- L23 _public prototype_ `TArray<int32> RunSelection(const FPatternInfo& InPattern, const TMap<int32, FDetectedFrame>& InDetectedFrames);`
- L29 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/Widgets/SMetaHumanCalibrationGeneratorWindow.h` (Private)


#### class `FMetaHumanCalibrationWindowCommands`  
`class FMetaHumanCalibrationWindowCommands : public TCommands<FMetaHumanCalibrationWindowCommands>`  
_L27-72_
- inherits: `TCommands<FMetaHumanCalibrationWindowCommands>`
- L33 _public function_ `FMetaHumanCalibrationWindowCommands() : TCommands<FMetaHumanCalibrationWindowCommands>( "MetaHumanCalibration", NSLOCTEXT("Contexts", "MetaHumanCalibration", "MetaHuman Calibration"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L45 _public function_ `virtual void RegisterCommands() override`
- L59 _public member_ `TSharedPtr<FUICommandInfo> OpenConfig;` — Open an existing config.
- L62 _public member_ `TSharedPtr<FUICommandInfo> SaveConfig;` — Save config.
- L65 _public member_ `TSharedPtr<FUICommandInfo> RunCalibration;` — Run calibration.
- L68 _public member_ `TSharedPtr<FUICommandInfo> RunAutoFrameSelection;` — Run automatic frame selection.
- L71 _public member_ `TSharedPtr<FUICommandInfo> OpenSettings;` — Open project settings.

#### class `UMetaHumanCalibrationMenuContext`  
`class UMetaHumanCalibrationMenuContext : public UObject`  
_L75-82_
- reflection: `UCLASS()`
- inherits: `UObject`
- L81 _public member_ `TWeakPtr<class SMetaHumanCalibrationGeneratorWindow> Widget;`

#### class `SMetaHumanCalibrationGeneratorWindow`  
`class SMetaHumanCalibrationGeneratorWindow : public SCompoundWidget`  
_L84-156_
- inherits: `SCompoundWidget`
- L89 _public member_ `static const FName CalibrationMainMenuName;`
- L91 _public prototype_ `SMetaHumanCalibrationGeneratorWindow();`
- L93 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCalibrationGeneratorWindow) : _CaptureData(nullptr)`
- L98 _public prototype_ `SLATE_ARGUMENT(UFootageCaptureData*, CaptureData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SWindow>& OwningWindow, const TSharedRef<class SDockTab>& OwningTab);`
- L104 _public prototype_ `void OnClose();`
- L107 _private prototype_ `void ResetState();`
- L109 _private prototype_ `FString GetDefaultPackagePath() const;`
- L110 _private prototype_ `FString GetDefaultAssetName() const;`
- L111 _private prototype_ `void OnFrameSelectionChanged(int32 InFrame);`
- L113 _private prototype_ `void RegisterToolbar(class UToolMenu* InToolbarMenu);`
- L114 _private prototype_ `TSharedPtr<SWidget> GenerateToolbarWidget(class UToolMenu* InToolbarMenu);`
- L115 _private prototype_ `void RegisterCommandHandlers();`
- L117 _private prototype_ `void SetConfig(UMetaHumanCalibrationGeneratorConfig* InConfig);`
- L118 _private prototype_ `void OpenConfig();`
- L119 _private prototype_ `void SaveConfig();`
- L120 _private prototype_ `void RunCalibration();`
- L121 _private prototype_ `bool CanRunCalibration() const;`
- L122 _private prototype_ `void ShowCalibrationRMS(bool bInSuccess);`
- L123 _private prototype_ `void RunAutomaticFrameSelection();`
- L124 _private prototype_ `void OpenSettings();`
- L126 _private prototype_ `FMetaHumanCalibrationPatternDetector::FDetectedFrame DetectForFrame(int32 InFrame);`
- L127 _private prototype_ `FMetaHumanCalibrationPatternDetector::FDetectedFrame DetectForFrame(const TArray<FMetaHumanCalibrationPatternDetector::FCameraInfo>& InCameras, const TPair<FString, FString>& InPath);`
- L130 _private prototype_ `void OnDetailsPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L132 _private prototype_ `void RegisterImageViewerTabSpawner(TSharedRef<FTabManager> InTabManager, const TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L133 _private prototype_ `void RegisterOptionsTabSpawner(TSharedRef<FTabManager> InTabManager, const TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L134 _private prototype_ `void RegisterConfigTabSpawner(TSharedRef<FTabManager> InTabManager, const TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L136 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L137 _private prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L139 _private typedef_ `using SMetaHumanCalibrationConfigWidget = SMetaHumanCalibrationObjectWidget<UMetaHumanCalibrationGeneratorConfig>;`
- L140 _private typedef_ `using SMetaHumanCalibrationOptionsWidget = SMetaHumanCalibrationObjectWidget<UMetaHumanCalibrationGeneratorOptions>;`
- L142 _private member_ `TSharedPtr<SMetaHumanCalibrationImageViewer> ImageViewer;`
- L143 _private member_ `TSharedPtr<SMetaHumanCalibrationOptionsWidget> OptionsTab;`
- L144 _private member_ `TSharedPtr<SMetaHumanCalibrationConfigWidget> ConfigTab;`
- L145 _private member_ `TSharedPtr<SWidget> Toolbar;`
- L147 _private member_ `TStrongObjectPtr<UFootageCaptureData> CaptureData;`
- L149 _private member_ `TSharedRef<FUICommandList> ToolkitUICommandList;`
- L150 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L152 _private member_ `TStrongObjectPtr<UMetaHumanCalibrationGenerator> Engine;`
- L153 _private member_ `TSharedPtr<FMetaHumanCalibrationGeneratorState> State;`
- L155 _private member_ `std::atomic_bool bIsProcessing = false;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define LOCTEXT_NAMESPACE "MetaHumanCalibration"`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/Widgets/SMetaHumanCalibrationImageViewer.h` (Private)


#### class `FMetaHumanCalibrationViewCommands`  
`class FMetaHumanCalibrationViewCommands : public TCommands<FMetaHumanCalibrationViewCommands>`  
_L24-67_
- inherits: `TCommands<FMetaHumanCalibrationViewCommands>`
- L30 _public function_ `FMetaHumanCalibrationViewCommands() : TCommands<FMetaHumanCalibrationViewCommands>( "MetaHumanCalibrationView", NSLOCTEXT("Contexts", "MetaHumanCalibrationView", "MetaHuman Calibration View"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L42 _public function_ `virtual void RegisterCommands() override`
- L54 _public member_ `TSharedPtr<FUICommandInfo> SelectAreaOfInterest;` — Enters area of interest selection mode.
- L57 _public member_ `TSharedPtr<FUICommandInfo> ResetView;` — Resets view.
- L60 _public member_ `TSharedPtr<FUICommandInfo> ToggleCoverage;` — Toggle coverage.
- L63 _public member_ `TSharedPtr<FUICommandInfo> ToggleDetectedPoints;` — Toggle detected points and lines.
- L66 _public member_ `TSharedPtr<FUICommandInfo> ToggleAreaOfInterest;` — Toggle the area of interest rectangle

#### class `SMetaHumanCalibrationImageViewer`  
`class SMetaHumanCalibrationImageViewer : public SCompoundWidget`  
_L69-176_
- inherits: `SCompoundWidget`
- L73 _public prototype_ `DECLARE_DELEGATE_OneParam(FFrameSelected, int32);`
- L75 _public typedef_ `using FPairString = TPair<FString, FString>;`
- L76 _public typedef_ `using FPairArray = TPair<TArray<FString>, TArray<FString>>;`
- L77 _public typedef_ `using FPairVector = TPair<FIntVector2, FIntVector2>;`
- L78 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FMetaHumanCalibrationPatternDetector::FDetectedFrame, FDetectForFrame, int32) SLATE_BEGIN_ARGS(SMetaHumanCalibrationImageViewer) : _FootageCaptureData(nullptr)`
- L85 _public prototype_ `SLATE_ARGUMENT(UFootageCaptureData*, FootageCaptureData) SLATE_ARGUMENT(TWeakPtr<FMetaHumanCalibrationGeneratorState>, State) SLATE_EVENT(FFrameSelected, FrameSelected) SLATE_EVENT(FDetectForFrame, DetectForFrame) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SWindow>& OwningWindow, const TSharedRef<class SDockTab>& OwningTab);`
- L93 _public prototype_ `void OnClose();`
- L95 _public prototype_ `void ResetView();`
- L96 _public prototype_ `void ResetState();`
- L98 _public prototype_ `void SelectCurrentFrame();`
- L99 _public prototype_ `void NextFrame(int32 InStep = 1);`
- L100 _public prototype_ `void PreviousFrame(int32 InStep = 1);`
- L102 _public prototype_ `void SetDetectedPointsForFrame(int32 InFrame, FMetaHumanCalibrationPatternDetector::FDetectedFrame InDetectedFrame);`
- L104 _public prototype_ `FPairString GetCameraNames() const;`
- L105 _public prototype_ `FPairVector GetFrameDimensions() const;`
- L106 _public prototype_ `FPairString GetFramePath(int32 InFrame) const;`
- L107 _public prototype_ `FPairArray GetFramePaths() const;`
- L110 _private prototype_ `void InvalidateCounter();`
- L112 _private prototype_ `void AddOverlay(FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L113 _private prototype_ `void ShowCoverage(FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L115 _private prototype_ `void ShowSingleFrameDetectedPoints(const FMetaHumanCalibrationPatternDetector::FDetectedFrame& InDetectedFrame, FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L118 _private prototype_ `void ShowAreaOfInterest(FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L121 _private prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L123 _private prototype_ `void UpdateImages(const int32 InFrameNumber);`
- L125 _private prototype_ `void OnScrubberValueChanged(float InValue);`
- L127 _private prototype_ `FReply OnFrameSelectedClicked();`
- L128 _private prototype_ `void SelectFrame(int32 InFrame);`
- L129 _private prototype_ `FMetaHumanCalibrationPatternDetector::FDetectedFrame RunDetectForFrame(int32 InFrame);`
- L130 _private prototype_ `const FSlateBrush* GetSelectFrameButtonImage() const;`
- L132 _private prototype_ `FReply OnNextSelectedFrameClicked();`
- L133 _private prototype_ `FReply OnPreviousSelectedFrameClicked();`
- L134 _private prototype_ `bool IsPreviousNextButtonEnabled() const;`
- L135 _private prototype_ `FReply OnResetButtonClicked();`
- L137 _private prototype_ `TSharedPtr<SWidget> GetViewToolbarWidget(int32 InCameraIndex);`
- L138 _private prototype_ `void RegisterCommandHandlers();`
- L150 _private prototype_ `void StartAreaOfInterestSelection(int32 InCameraIndex);`
- L151 _private prototype_ `void UpdateAfterSelection(FSlateRect InSlateRect, FBox2d InUvRegion, FVector2D InWidgetSize, int32 InCameraIndex);`
- L152 _private prototype_ `void ResetView(int32 InCameraIndex);`
- L153 _private prototype_ `void ToggleView(int32 InIndex, EViewOptions InView);`
- L154 _private prototype_ `ECheckBoxState IsViewToggled(int32 InIndex, EViewOptions InView) const;`
- L156 _private prototype_ `TSharedRef<SWidget> FillDisplayOptionsForViewMenu(int32 InCameraIndex);`
- L158 _private member_ `TWeakObjectPtr<UFootageCaptureData> CaptureData;`
- L159 _private member_ `TWeakPtr<FMetaHumanCalibrationGeneratorState> State;`
- L161 _private member_ `TArray<TSharedPtr<SMetaHumanCalibrationSingleImageViewer>> SingleImageViewers;`
- L162 _private member_ `TMap<int32, FMetaHumanCalibrationPatternDetector::FDetectedFrame> DetectedPointsForSelectedFrames;`
- L164 _private member_ `TSharedPtr<SMetaHumanImageViewerScrubber> ScrubberSlider;`
- L166 _private member_ `TOptional<int32> PendingValueChange;`
- L167 _private member_ `FFrameSelected FrameSelected;`
- L168 _private member_ `FDetectForFrame DetectForFrame;`
- L170 _private member_ `TUniquePtr<FMetaHumanChessboardPointCounter> ChessboardPointCounter;`
- L171 _private member_ `TMap<int32, TSharedRef<FUICommandList>> CameraToolkitCommands;`
- L173 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EViewOptions);`
- L175 _private member_ `TMap<int32, EViewOptions> ShowViewOptions;`

#### enum `SMetaHumanCalibrationImageViewer::EViewOptions`  
`enum class EViewOptions : uint8`  
_L140-148_
- L142 _public enumerator_ `Nothing = 0`
- L143 _public enumerator_ `Coverage = 1 << 0`
- L144 _public enumerator_ `DetectedPoints = 1 << 1`
- L145 _public enumerator_ `AreaOfInterest = 1 << 2`
- L147 _public enumerator_ `All = Coverage | DetectedPoints | AreaOfInterest`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "MetaHumanCalibrationViewer"`
- L73 _delegate_ `DECLARE_DELEGATE_OneParam(FFrameSelected, int32);`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FMetaHumanCalibrationPatternDetector::FDetectedFrame, FDetectForFrame, int32) SLATE_BEGIN_ARGS(SMetaHumanCalibrationImageViewer) : _FootageCaptureData(nullptr) { } SLATE_ARGUMENT(UFootageCaptureData*, FootageCaptureData) SLATE_ARGUMENT(TWeakPtr<FMetaHumanCalibrationGeneratorState>, State) SLATE_EVENT(FFrameSelected, FrameSelected) SLATE_EVENT(FDetectForFrame, DetectForFrame) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SWindow>& OwningWindow, const TSharedRef<class SDockTab>& OwningTab);`
