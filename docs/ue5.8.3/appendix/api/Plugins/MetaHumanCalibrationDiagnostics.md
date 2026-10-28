# Plugins / MetaHumanCalibrationDiagnostics

- module root: `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics`
- headers: 9; symbols: 202
- symbol kinds: class=12, enum=1, enumerator=5, function=8, macro=2, member=70, namespace=2, prototype=95, struct=6, typedef=1
- PrivateDependencyModuleNames: CaptureDataEditor, CaptureDataUtils, CaptureUtils, ContentBrowser, ImageCore, ImageWrapper, ImgMedia, InputCore, Json, JsonUtilities, MetaHumanCalibrationLib, MetaHumanImageViewer, OpenCV, OpenCVHelper, OutputLog, Projects, SequencerWidgets, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine, MetaHumanCalibrationCore

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/MetaHumanCalibrationDiagnosticsCommands.h` (Private)


#### class `FMetaHumanCalibrationDiagnosticsCommands`  
`class FMetaHumanCalibrationDiagnosticsCommands : public TCommands<FMetaHumanCalibrationDiagnosticsCommands>`  
_L12-54_
- inherits: `TCommands<FMetaHumanCalibrationDiagnosticsCommands>`
- L18 _public function_ `FMetaHumanCalibrationDiagnosticsCommands() : TCommands<FMetaHumanCalibrationDiagnosticsCommands>( "MetaHumanCalibrationDiagnostics", NSLOCTEXT("Contexts", "MetaHumanCalibrationDiagnostics", "MetaHuman Calibration Diagnostics"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L30 _public function_ `virtual void RegisterCommands() override`
- L41 _public member_ `TSharedPtr<FUICommandInfo> SelectAreaOfInterest;` — Enters area of interest selection mode.
- L44 _public member_ `TSharedPtr<FUICommandInfo> ResetView;` — Resets view.
- L47 _public member_ `TSharedPtr<FUICommandInfo> TogglePoints;` — Shows detected points
- L50 _public member_ `TSharedPtr<FUICommandInfo> TogglePerBlockErrors;` — Shows detected points
- L53 _public member_ `TSharedPtr<FUICommandInfo> ToggleAreaOfInterest;` — Shows Area of Interest

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "MetaHumanCalibrationDiagnostics"`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/MetaHumanCalibrationDiagnosticsOptions.h` (Private)


#### class `UMetaHumanCalibrationDiagnosticsOptions`  
`class UMetaHumanCalibrationDiagnosticsOptions : public UObject`  
_L16-52_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Options that will used as part of the camera calibration diagnostics process
- L25 _public member_ `TObjectPtr<UCameraCalibration> CameraCalibration = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")` — Calibration that will be used to run the diagnostics
- L29 _public member_ `TArray<FMetaHumanAreaOfInterest> AreaOfInterestsForCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")` — Area for which the calibration diagnostics will be presented
- L37 _public member_ `double RMSErrorThreshold = 3.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", DisplayName = "RMS Error Threshold")` — Maximum acceptable root mean square (RMS) reprojection error for calibration to be considered valid Note: The points and lines drawn will be colored using an HSL gradient: 0 = green, 1 = red, with intermediate values transitioning smoothly.
- L41 _public member_ `double FeatureMatchErrorThreshold = 5.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")` — Maximum acceptable feature match reprojection error for which the detected points will be considered valid
- L48 _public member_ `double ReprojectionErrorThreshold = 3.0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Options")` — Maximum acceptable reprojection error for detected points to be considered valid Note: The points and lines drawn will be colored using an HSL gradient: 0 = green, 1 = red, with intermediate values transitioning smoothly.
- L51 _public member_ `double RatioThreshold = 0.75;` — `UPROPERTY()`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/Selectors/CalibrationArraySplitter.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L18 _prototype_ `TArray<TArrayView<UCameraCalibration* const>> SplitCalibrationArrayToViews(const TArray<UCameraCalibration*>& SourceArray, int32 InNumberOfChunks);` (scope `UE::MetaHuman`) — Splits a calibration array into roughly-equal contiguous views. The first (SourceArray.Num() % InNumberOfChunks) views get one extra element. InNumberOfChunks is clamped to SourceArray.Num().

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/UMetaHumanRobustFeatureMatcher.h` (Private)


#### struct `FCameraPoints`  
`struct FCameraPoints`  
_L14-20_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- L19 _public member_ `TArray<FVector2D> Points;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman | Calibration Diagnostics")`

#### struct `FDetectedFeatures`  
`struct FDetectedFeatures`  
_L23-40_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- L28 _public member_ `int32 FrameIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman | Calibration Diagnostics")`
- L31 _public member_ `TArray<FVector> Points3d;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman | Calibration Diagnostics")`
- L34 _public member_ `TArray<FCameraPoints> CameraPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman | Calibration Diagnostics")`
- L37 _public member_ `TArray<FCameraPoints> Points3dReprojected;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman | Calibration Diagnostics")`
- L39 _public prototype_ `bool IsValid() const;`

#### class `UMetaHumanRobustFeatureMatcher`  
`class UMetaHumanRobustFeatureMatcher : public UObject`  
_L43-73_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- L48 _public prototype_ `UMetaHumanRobustFeatureMatcher();`
- L51 _public prototype_ `bool Init(UFootageCaptureData* InCaptureData, UMetaHumanCalibrationDiagnosticsOptions* InOptions);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Diagnostics")`
- L54 _public prototype_ `bool DetectFeatures(int64 InFrame);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Diagnostics")`
- L57 _public prototype_ `FDetectedFeatures GetFeatures(int64 InFrame);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Diagnostics")`
- L60 _public prototype_ `TArray<FString> GetImagePaths(const FString& InCameraName);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Diagnostics")`
- L63 _public prototype_ `TArray<FString> GetCameraNames() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Diagnostics")`
- L66 _public prototype_ `TArray<FIntVector2> GetImageSizes() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | Calibration Diagnostics")`
- L70 _private member_ `TMap<FString, TArray<FString>> StereoPairImagePaths;`
- L71 _private member_ `TMap<FString, FIntVector2> StereoPairImageSizes;`
- L72 _private member_ `TSharedPtr<UE::Wrappers::FMetaHumanRobustFeatureMatcher> FeatureMatcher;`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/Utils/MetaHumanCalibrationErrorAnalysis.h` (Private)


#### struct `FFrameCalibrationErrorScore`  
`struct FFrameCalibrationErrorScore`  
_L7-23_
- L10 _public member_ `double TotalErrorScore = 0.0;` — Stores the score from error analysis for the current frame
- L13 _public member_ `double MedianScore = 0.0;` — Stores the median score from error analysis for the current frame
- L16 _public member_ `double RMSScore = 0.0;` — Stores the RMS score from error analysis for the current frame
- L19 _public member_ `double PointCountScore = 0.0;` — Stores the point count score from error analysis for the current frame
- L22 _public member_ `double P90Score = 0.0;` — Stores the P90 score from error analysis for the current frame

#### struct `FCameraCalibrationScore`  
`struct FCameraCalibrationScore`  
_L25-44_
- L28 _public member_ `double MeanTotalScore = 0.0;` — Stores the mean score for the current camera across all selected frames
- L31 _public member_ `double MeanErrorScore = 0.0;` — Stores the mean score from error analysis for the current camera across all selected frames
- L34 _public member_ `double MeanCoverageScore = 0.0;` — Stores the mean score from coverage analysis for the current camera across all selected frames
- L37 _public member_ `TMap<int32, FFrameCalibrationErrorScore> ErrorScorePerFrame;` — Stores the score from error analysis for the current camera per frame
- L40 _public member_ `TMap<int32, double> CoverageScorePerFrame;` — Stores the score from coverage analysis for the current camera per frame
- L43 _public member_ `TMap<int32, double> TotalScorePerFrame;` — Stores the total score for the current camera per frame

#### class `FMetaHumanCalibrationErrorAnalysis`  
`class FMetaHumanCalibrationErrorAnalysis`  
_L46-61_
- L50 _public member_ `static constexpr double MinRMS = 1.0;` — Sensible default
- L52 _public prototype_ `FMetaHumanCalibrationErrorAnalysis(const FMetaHumanCalibrationErrorCalculator& InCalculator, const TArray<int32>& InFrames);`
- L55 _public prototype_ `TMap<FString, FCameraCalibrationScore> Analyze() const;`
- L59 _private member_ `const FMetaHumanCalibrationErrorCalculator& Calculator;`
- L60 _private member_ `TArray<int32> Frames;`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/Utils/MetaHumanCalibrationErrorCalculator.h` (Private)


#### class `FMetaHumanCalibrationErrorCalculator`  
`class FMetaHumanCalibrationErrorCalculator`  
_L14-98_
- L28 _public prototype_ `FMetaHumanCalibrationErrorCalculator(const FVector2D& InCoverageMapSize, const TArray<FString>& InCameraNames, const TArray<FIntVector2>& InImageSizes);`
- L32 _public prototype_ `void SetAreaOfInterestForCamera(const FString& InCameraName, const FBox2D& InAreaOfInterest);`
- L34 _public prototype_ `bool ContainsErrors() const;`
- L35 _public prototype_ `bool ContainsErrors(int32 InFrame) const;`
- L37 _public prototype_ `void Invalidate(TOptional<FVector2D> InCoverageMapSize = TOptional<FVector2D>());`
- L39 _public prototype_ `void Update(const TArray<FDetectedFeatures>& InDetectedFeaturesArray);`
- L40 _public prototype_ `void Update(const FDetectedFeatures& InDetectedFeatures);`
- L42 _public prototype_ `double GetTotalRMSError() const;`
- L43 _public prototype_ `double GetTotalMeanError() const;`
- L45 _public prototype_ `double GetRMSErrorForFrame(int32 InFrameIndex) const;`
- L46 _public prototype_ `double GetMeanErrorForFrame(int32 InFrameIndex) const;`
- L47 _public prototype_ `double GetMedianErrorForFrame(int32 InFrameIndex) const;`
- L48 _public prototype_ `FErrors GetErrorsForFrame(int32 InFrameIndex) const;`
- L50 _public prototype_ `double GetRMSErrorForFrame(const FString& InCameraName, int32 InFrameIndex) const;`
- L51 _public prototype_ `double GetMeanErrorForFrame(const FString& InCameraName, int32 InFrameIndex) const;`
- L52 _public prototype_ `double GetMedianErrorForFrame(const FString& InCameraName, int32 InFrameIndex) const;`
- L53 _public prototype_ `FErrors GetErrorsForFrame(const FString& InCameraName, int32 InFrameIndex) const;`
- L55 _public prototype_ `double GetRMSErrorForBlock(const FString& InCameraName, int32 InBlockIndex, int32 InFrameIndex) const;`
- L56 _public prototype_ `double GetMeanErrorForBlock(const FString& InCameraName, int32 InBlockIndex, int32 InFrameIndex) const;`
- L57 _public prototype_ `double GetMedianErrorForBlock(const FString& InCameraName, int32 InBlockIndex, int32 InFrameIndex) const;`
- L58 _public prototype_ `double GetP90ErrorForBlock(const FString& InCameraName, int32 InBlockIndex, int32 InFrameIndex) const;`
- L59 _public prototype_ `TArray<double> GetErrorArrayForBlock(const FString& InCameraName, int32 InBlockIndex, int32 InFrameIndex) const;`
- L60 _public prototype_ `FErrors GetErrorsForBlock(const FString& InCameraName, int32 InBlockIndex, int32 InFrameIndex) const;`
- L62 _public prototype_ `TArray<int32> GetBlockIndices(const FString& InCameraName) const;`
- L64 _public prototype_ `FVector2D GetBlockSize(const FString& InCameraName) const;`
- L65 _public prototype_ `FBox2D GetBlock(const FString& InCameraName, int32 InBlockIndex) const;`
- L66 _public prototype_ `int32 GetBlockNum() const;`
- L68 _public function_ `TArray<FBox2D> GetAreaOfInterest() const`
- L69 _public function_ `TArray<FIntVector2> GetImageSizes() const`
- L70 _public function_ `TArray<FString> GetCameraNames() const`
- L72 _public prototype_ `void ToggleMarkBlock(const FString& InCameraName, int32 InBlockIndex);`
- L73 _public prototype_ `bool IsBlockMarked(const FString& InCameraName, int32 InBlockIndex) const;`
- L77 _private prototype_ `void Reset();`
- L78 _private prototype_ `void InvalidateForCamera(const FString& InCameraName);`
- L79 _private prototype_ `void ResetForCamera(const FString& InCameraName);`
- L81 _private prototype_ `static FErrors CalculateErrors(const TArray<double>& InErrors);`
- L82 _private prototype_ `static double CalculateMedian(const TArray<double>& InErrors);`
- L83 _private prototype_ `static double CalculateP90(const TArray<double>& InErrors);`
- L85 _private member_ `FVector2D CoverageMapSize;`
- L86 _private member_ `TArray<FString> CameraNames;`
- L87 _private member_ `TArray<FIntVector2> ImageSizes;`
- L88 _private member_ `TArray<FBox2D> AreaOfInterest;`
- L96 _private member_ `TMap<FString, TArray<FBlockInfo>> ArrayOfBlocks;`
- L97 _private member_ `TMap<FString, TMap<int32, TArray<FErrors>>> ErrorsPerCameraPerFramePerBlock;`

#### struct `FMetaHumanCalibrationErrorCalculator::FErrors`  
`struct FErrors`  
_L18-26_
- L20 _public member_ `double RMSError = 0.0;`
- L21 _public member_ `double MeanError = 0.0;`
- L22 _public member_ `double MedianError = 0.0;`
- L23 _public member_ `double P90Error = 0.0;`
- L25 _public member_ `TArray<double> Errors;`

#### struct `FMetaHumanCalibrationErrorCalculator::FBlockInfo`  
`struct FBlockInfo`  
_L90-94_
- L92 _public member_ `FBox2D Box;`
- L93 _public member_ `bool bIsMarked = false;`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/Widgets/SCalibrationDiagnosticsImageViewer.h` (Private)


#### class `IFeatureDetector`  
`class IFeatureDetector`  
_L17-25_
- L21 _public prototype_ `virtual ~IFeatureDetector() = default;`
- L23 _public prototype_ `virtual FDetectedFeatures GetDetectedFeatures(int32 InFrameId) = 0;`
- L24 _public prototype_ `virtual FDetectedFeatures DetectFeatures(int32 InFrameId) = 0;`

#### class `SCalibrationDiagnosticsImageViewer`  
`class SCalibrationDiagnosticsImageViewer : public SCompoundWidget`  
_L27-130_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SCalibrationDiagnosticsImageViewer) : _FootageCaptureData(nullptr) , _Options(nullptr) , _FeatureDetector()`
- L36 _public prototype_ `SLATE_ARGUMENT(UFootageCaptureData*, FootageCaptureData) SLATE_ARGUMENT(UMetaHumanCalibrationDiagnosticsOptions*, Options) SLATE_ARGUMENT(TSharedPtr<IFeatureDetector>, FeatureDetector) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `void SetImages(int32 InFrameId);`
- L45 _public prototype_ `void UpdateState();`
- L46 _public prototype_ `void ResetState();`
- L47 _public prototype_ `void OnClose();`
- L51 _private prototype_ `void OnAddOverlays(FBox2d InUvRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L56 _private prototype_ `void OnImageClicked(FVector2D InMousePoint, FBox2d InUvRegion, FVector2D InWidgetSize, int32 InCameraIndex);`
- L58 _private prototype_ `void ShowDetectedFeatures(FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L60 _private prototype_ `void ShowAreaOfInterest(FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L62 _private prototype_ `void ShowGridMap(FBox2d InUVRegion, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& OutLayerId, int32 InCameraIndex);`
- L65 _private prototype_ `EVisibility ImagesNotFoundVisibility() const;`
- L67 _private prototype_ `void UpdateErrors();`
- L68 _private prototype_ `void CalculateErrors(int32 InFrameIndex, bool bInUpdateUI = true);`
- L70 _private prototype_ `void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L72 _private prototype_ `void OnScrubberValueChanged(float InValue);`
- L74 _private prototype_ `FText HandleDetectButtonText() const;`
- L75 _private prototype_ `FReply OnDetectButtonClicked();`
- L76 _private prototype_ `bool DetectForFrame(int32 InFrame);`
- L77 _private prototype_ `bool IsDetectButtonEnabled() const;`
- L79 _private prototype_ `FText HandleMeanErrorTextBlock() const;`
- L80 _private prototype_ `FText HandleRMSErrorTextBlock() const;`
- L81 _private prototype_ `FSlateColor HandleRMSErrorColor() const;`
- L82 _private prototype_ `FText HandleErrorTextBlock(double InError) const;`
- L83 _private prototype_ `FSlateColor HandleErrorColor(double InError, double InMinValue, double InThreshold) const;`
- L85 _private prototype_ `TSharedPtr<SWidget> GetViewToolbarWidget(int32 InCameraIndex);`
- L86 _private prototype_ `TSharedRef<SWidget> FillDisplayOptionsForViewMenu(int32 InCameraIndex);`
- L87 _private prototype_ `void RegisterCommandHandlers();`
- L99 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EViewOptions);`
- L101 _private prototype_ `void StartAreaOfInterestSelection(int32 InCameraIndex);`
- L102 _private prototype_ `void UpdateAfterSelection(FSlateRect InSlateRect, FBox2d InUvRegion, FVector2D InWidgetSize, int32 InCameraIndex);`
- L103 _private prototype_ `void ResetView(int32 InCameraIndex);`
- L104 _private prototype_ `void ToggleView(int32 InIndex, EViewOptions InView);`
- L105 _private prototype_ `ECheckBoxState IsViewToggled(int32 InIndex, EViewOptions InView) const;`
- L107 _private prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L109 _private member_ `TArray<TSharedPtr<SMetaHumanCalibrationSingleImageViewer>> ImageViewers;`
- L110 _private member_ `TSharedPtr<SMetaHumanImageViewerScrubber> ScrubberSlider;`
- L112 _private member_ `int32 CurrentFrameId;`
- L113 _private member_ `TOptional<int32> PendingValueChange;`
- L115 _private member_ `TArray<int32> DetectedFrames;`
- L117 _private member_ `TUniquePtr<FMetaHumanCalibrationErrorCalculator> Calculator;`
- L119 _private member_ `TMap<int32, TSharedRef<FUICommandList>> CameraToolkitCommands;`
- L120 _private member_ `TMap<int32, EViewOptions> ShowViewOptions;`
- L122 _private member_ `TWeakObjectPtr<UFootageCaptureData> CaptureData;`
- L123 _private member_ `TWeakObjectPtr<UMetaHumanCalibrationDiagnosticsOptions> Options;`
- L124 _private member_ `TSharedPtr<IFeatureDetector> FeatureDetector;`
- L126 _private member_ `TArray<int32> SelectedBlockId;`
- L128 _private member_ `TOptional<double> CurrentFrameRMS;`
- L129 _private member_ `TOptional<double> CurrentFrameMean;`

#### enum `SCalibrationDiagnosticsImageViewer::EViewOptions`  
`enum class EViewOptions : uint8`  
_L89-97_
- L91 _public enumerator_ `Nothing = 0`
- L92 _public enumerator_ `DetectedFeatures = 1 << 0`
- L93 _public enumerator_ `AreaOfInterests = 1 << 1`
- L94 _public enumerator_ `ErrorsPerBlock = 1 << 2`
- L96 _public enumerator_ `All = DetectedFeatures | AreaOfInterests | ErrorsPerBlock`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Private/Widgets/SCalibrationDiagnosticsWindow.h` (Private)


#### class `SCalibrationDiagnosticsWindow`  
`class SCalibrationDiagnosticsWindow : public SCompoundWidget, public IFeatureDetector`  
_L19-56_
- inherits: `SCompoundWidget,IFeatureDetector`
- L22 _public function_ `SLATE_BEGIN_ARGS(SCalibrationDiagnosticsWindow) : _FootageCaptureData(nullptr)`
- L26 _public prototype_ `SLATE_ARGUMENT(UFootageCaptureData*, FootageCaptureData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<SWindow>& InOwningWindow, const TSharedRef<class SDockTab>& InOwningTab);`
- L31 _public prototype_ `void SetImages(int32 InFrameId);`
- L33 _public prototype_ `void OnClose();`
- L37 _private prototype_ `void RegisterImageViewerTabSpawner(TSharedRef<FTabManager> InTabManager, const TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L38 _private prototype_ `void RegisterOptionsTabSpawner(TSharedRef<FTabManager> InTabManager, const TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L40 _private prototype_ `virtual FDetectedFeatures GetDetectedFeatures(int32 InFrameId) override;`
- L41 _private prototype_ `virtual FDetectedFeatures DetectFeatures(int32 InFrameId) override;`
- L43 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L45 _private member_ `TStrongObjectPtr<UFootageCaptureData> CaptureData;`
- L46 _private member_ `TStrongObjectPtr<UMetaHumanCalibrationDiagnosticsOptions> Options;`
- L47 _private member_ `TStrongObjectPtr<UMetaHumanRobustFeatureMatcher> FeatureMatcher;`
- L49 _private member_ `TSharedPtr<SCalibrationDiagnosticsImageViewer> ImageViewer;`
- L50 _private typedef_ `using SMetaHumanCalibrationOptionsWidget = SMetaHumanCalibrationObjectWidget<UMetaHumanCalibrationDiagnosticsOptions>;`
- L51 _private member_ `TSharedPtr<SMetaHumanCalibrationOptionsWidget> OptionsViewer;`
- L53 _private member_ `bool bIsFeatureDetectorInitialized = false;`
- L55 _private member_ `TSharedPtr<FTabManager> TabManager;`

### `Plugins/Experimental/MetaHuman/MetaHumanCalibrationDiagnostics/Source/MetaHumanCalibrationDiagnostics/Public/Selectors/MetaHumanDiagnosticsBasedSelector.h` (Public)


#### class `UMetaHumanFeatureMatcherFrameProvider`  
`class UMetaHumanFeatureMatcherFrameProvider : public UObject`  
_L13-26_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories)`
- inherits: `UObject`
- desc: Frame providers
- L20 _public prototype_ `TArray<int32> GetSelectedFrames() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MetaHuman Calibration")`
- L24 _protected prototype_ `virtual TArray<int32> GetSelectedFrames_Implementation() const PURE_VIRTUAL(UMetaHumanFeatureMatcherFrameProvider::GetSelectedFrames_Implementation, return TArray<int32>(););`

#### class `UMetaHumanManualFrameProvider`  
`class UMetaHumanManualFrameProvider final : public UMetaHumanFeatureMatcherFrameProvider`  
_L29-39_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UMetaHumanFeatureMatcherFrameProvider`
- L36 _public member_ `TArray<int32> SelectedFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman Calibration")`
- L38 _public function_ `virtual TArray<int32> GetSelectedFrames_Implementation() const override`

#### class `UMetaHumanDiagnosticsBasedSelectorSettings`  
`class UMetaHumanDiagnosticsBasedSelectorSettings final : public UMetaHumanCalibrationSelectorSettings`  
_L42-50_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UMetaHumanCalibrationSelectorSettings`
- L49 _public member_ `TObjectPtr<UMetaHumanFeatureMatcherFrameProvider> FrameProvider;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "MetaHuman Calibration")`

#### class `UMetaHumanDiagnosticsBasedSelector`  
`class UMetaHumanDiagnosticsBasedSelector final : public UMetaHumanCalibrationSelector`  
_L53-65_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UMetaHumanCalibrationSelector`
- L59 _public prototype_ `virtual TArray<UCameraCalibration*> OrderCalibrations_Implementation(UFootageCaptureData* InCaptureData, const TArray<UCameraCalibration*>& InCameraCalibrations) const override;`
- L60 _public prototype_ `virtual TSubclassOf<UMetaHumanCalibrationSelectorSettings> GetSettingsClass_Implementation() const override;`
- L64 _private member_ `static constexpr int32 MaxNumberOfThreads = 8;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCALIBRATIONDIAGNOSTICS_API`
