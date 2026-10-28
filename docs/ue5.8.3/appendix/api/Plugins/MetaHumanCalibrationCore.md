# Plugins / MetaHumanCalibrationCore

- module root: `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore`
- headers: 12; symbols: 190
- symbol kinds: class=13, delegate=5, enum=1, enumerator=3, function=13, macro=11, member=30, namespace=5, prototype=102, struct=2, typedef=5
- PrivateDependencyModuleNames: CaptureDataEditor, CaptureDataUtils, CaptureUtils, ContentBrowser, ImageCore, ImageWrapper, ImgMedia, InputCore, Json, JsonUtilities, MetaHumanCalibrationLib, MetaHumanCaptureData, MetaHumanImageViewer, OpenCV, OpenCVHelper, OutputLog, Projects, SequencerWidgets, SettingsEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/MetaHumanAreaOfInterest.h` (Public)


#### struct `FMetaHumanAreaOfInterest`  
`struct FMetaHumanAreaOfInterest`  
_L16-30_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- L21 _public member_ `FVector2D TopLeft = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L24 _public member_ `FVector2D BottomRight = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L26 _public prototype_ `FSlateRect GetSlateRect() const;`
- L27 _public prototype_ `void SetFromSlateRect(const FSlateRect& InSlateRect);`
- L28 _public prototype_ `FBox2D GetBox2D() const;`
- L29 _public prototype_ `void SetFromBox2D(const FBox2D& InBox);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Selectors/MetaHumanCalibrationSelector.h` (Public)


#### class `UMetaHumanCalibrationSelectorSettings`  
`class UMetaHumanCalibrationSelectorSettings : public UObject`  
_L17-20_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI, Abstract)`
- inherits: `UObject`

#### class `UMetaHumanCalibrationSelector`  
`class UMetaHumanCalibrationSelector : public UObject`  
_L23-64_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract)`
- inherits: `UObject`
- L30 _public prototype_ `UCameraCalibration* SelectCalibration(UFootageCaptureData* CaptureData, const TArray<UCameraCalibration*>& CameraCalibrations) const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure = false, Category = "MetaHuman Calibration")`
- L33 _public prototype_ `TArray<UCameraCalibration*> OrderCalibrations(UFootageCaptureData* CaptureData, const TArray<UCameraCalibration*>& CameraCalibrations) const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure = false, Category = "MetaHuman Calibration")`
- L36 _public prototype_ `TSubclassOf<UMetaHumanCalibrationSelectorSettings> GetSettingsClass() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MetaHuman Calibration")`
- L39 _public function_ `void SetSettings(UMetaHumanCalibrationSelectorSettings* Settings)` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Calibration")`
- L43 _protected prototype_ `virtual UCameraCalibration* SelectCalibration_Implementation(UFootageCaptureData* InCaptureData, const TArray<UCameraCalibration*>& InCameraCalibrations) const;`
- L45 _protected prototype_ `virtual TArray<UCameraCalibration*> OrderCalibrations_Implementation(UFootageCaptureData* InCaptureData, const TArray<UCameraCalibration*>& InCameraCalibrations) const PURE_VIRTUAL(UMetaHumanCalibrationSelector::OrderCalibrations_Implementation, return TArray<UCameraCalibration*>(););`
- L47 _protected prototype_ `virtual TSubclassOf<UMetaHumanCalibrationSelectorSettings> GetSettingsClass_Implementation() const PURE_VIRTUAL(UMetaHumanCalibrationSelector::GetSettingsClass_Implementation, return nullptr;);`
- L54 _public function_ `template<typename T = UMetaHumanCalibrationSelectorSettings> requires UE::CDerivedFrom<T, UMetaHumanCalibrationSelectorSettings> const T* GetSettings() const`
- L58 _public function_ `template<typename T = UMetaHumanCalibrationSelectorSettings> requires UE::CDerivedFrom<T, UMetaHumanCalibrationSelectorSettings> T* GetSettings()`
- L63 _private member_ `TObjectPtr<UMetaHumanCalibrationSelectorSettings> SelectorSettings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Selectors/MetaHumanTimecodeBasedSelector.h` (Public)


#### class `UMetaHumanTimecodeBasedSelector`  
`class UMetaHumanTimecodeBasedSelector final : public UMetaHumanCalibrationSelector`  
_L12-19_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UMetaHumanCalibrationSelector`
- L17 _public prototype_ `virtual TArray<UCameraCalibration*> OrderCalibrations_Implementation(UFootageCaptureData* InCaptureData, const TArray<UCameraCalibration*>& InCameraCalibrations) const override;`
- L18 _public prototype_ `virtual TSubclassOf<UMetaHumanCalibrationSelectorSettings> GetSettingsClass_Implementation() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Style/MetaHumanCalibrationStyle.h` (Public)


#### class `FMetaHumanCalibrationStyle`  
`class FMetaHumanCalibrationStyle : public FSlateStyleSet`  
_L9-17_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `FMetaHumanCalibrationStyle();`
- L16 _public prototype_ `static FMetaHumanCalibrationStyle& Get();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Utils/MetaHumanCalibrationAreaSelection.h` (Public)


#### class `FMetaHumanCalibrationAreaSelection`  
`class FMetaHumanCalibrationAreaSelection : public FDelayedDrag`  
_L10-26_
- inherits: `FDelayedDrag`
- L16 _public prototype_ `void OnStart(const FVector2D& InStartingPosition);`
- L17 _public prototype_ `void OnUpdate(const FVector2D& InNewPosition);`
- L18 _public prototype_ `FSlateRect OnEnd(const FVector2D& InLastPosition);`
- L20 _public prototype_ `void OnDraw(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId) const;`
- L24 _private member_ `FVector2D StartingPosition;`
- L25 _private member_ `FSlateRect AreaOfInterest;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Utils/MetaHumanCalibrationFrameResolver.h` (Public)


#### struct `FMetaHumanCalibrationFramePaths`  
`struct FMetaHumanCalibrationFramePaths`  
_L12-16_
- L14 _public member_ `FString FirstCamera;`
- L15 _public member_ `FString SecondCamera;`

#### class `FMetaHumanCalibrationFrameResolver`  
`class FMetaHumanCalibrationFrameResolver`  
_L18-65_
- L37 _public prototype_ `static TOptional<FMetaHumanCalibrationFrameResolver> CreateFromCaptureData(const UFootageCaptureData* InCaptureData);`
- L39 _public prototype_ `FMetaHumanCalibrationFrameResolver(const FCameraDescriptor& InFirstCamera, const FCameraDescriptor& InSecondCamera);`
- L46 _public prototype_ `bool GetFramePathsForCameraIndex(int32 InCameraIndex, TArray<FString>& OutFramePaths) const;` — @brief Gets the paths to all the frames for the specified camera index. @returns true if the camera index is valid and false otherwise.
- L52 _public prototype_ `bool GetCalibrationFramePathsForFrameIndex(int32 InFrameIndex, FMetaHumanCalibrationFramePaths& OutCalibrationFrame) const;` — @brief Gets the calibration frame paths for the specified frame index. @returns true if the frame index is valid and false otherwise.
- L55 _public prototype_ `TArray<FMetaHumanCalibrationFramePaths> GetCalibrationFramePaths() const;` — @brief Gets the calibration frame paths for every frame
- L58 _public prototype_ `bool HasFrames() const;` — @returns true if the resolver has frames.
- L62 _private prototype_ `FMetaHumanCalibrationFrameResolver(const UFootageCaptureData* InCaptureData);`
- L64 _private member_ `TArray<FMetaHumanCalibrationFramePaths> CalibrationFramePaths;`

#### class `FMetaHumanCalibrationFrameResolver::FCameraDescriptor`  
`class FCameraDescriptor`  
_L21-35_
- L25 _public prototype_ `FCameraDescriptor(TArray<FString> InImagePaths, FTimecode InTimecode, FFrameRate InFrameRate);`
- L27 _public prototype_ `const TArray<FString>& GetImagePaths() const;`
- L28 _public prototype_ `FTimecode GetTimecode() const;`
- L29 _public prototype_ `FFrameRate GetFrameRate() const;`
- L32 _private member_ `const TArray<FString> ImagePaths;`
- L33 _private member_ `const FTimecode Timecode;`
- L34 _private member_ `const FFrameRate FrameRate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Utils/MetaHumanCalibrationNotificationManager.h` (Public)


#### class `FMetaHumanCalibrationNotificationManager`  
`class FMetaHumanCalibrationNotificationManager : public TSharedFromThis<FMetaHumanCalibrationNotificationManager>`  
_L10-25_
- inherits: `TSharedFromThis<FMetaHumanCalibrationNotificationManager>`
- L15 _public prototype_ `void NotificationOnBegin(const FText& InInfoText);`
- L16 _public prototype_ `void NotificationOnEnd(bool bIsSuccess, TOptional<FText> InSubInfoText = TOptional<FText>());`
- L20 _private prototype_ `void NotificationOnBegin_GameThread(const FText& InInfoText);`
- L21 _private prototype_ `void NotificationOnEnd_GameThread(bool bIsSuccess, TOptional<FText> InSubInfoText);`
- L23 _private member_ `FCriticalSection Mutex;`
- L24 _private member_ `TSharedPtr<SNotificationItem> CurrentNotification;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Utils/MetaHumanCalibrationUtils.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L17 _namespace_ `namespace Image` (scope `UE::MetaHuman`)
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilteringPredicate, int32);`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilteringPredicate, int32);` (scope `UE::MetaHuman::Image`)
- L22 _prototype_ `TArray<FString> GetImagePaths(TObjectPtr<UImgMediaSource> InImgMediaSource);` (scope `UE::MetaHuman::Image`)
- L23 _prototype_ `FString GetStringFromTimespan(const FTimespan& InTimespan);` (scope `UE::MetaHuman::Image`)
- L24 _prototype_ `TOptional<FImage> GetGrayscaleImage(const FString& InFullImagePath);` (scope `UE::MetaHuman::Image`)
- L25 _prototype_ `TArray64<uint8> GetGrayscaleImageData(const FString& InFullImagePath);` (scope `UE::MetaHuman::Image`)
- L26 _prototype_ `TOptional<FImage> GetImage(const FString& InFullImagePath);` (scope `UE::MetaHuman::Image`)
- L27 _prototype_ `TArray64<uint8> GetImageData(const FString& InFullImagePath);` (scope `UE::MetaHuman::Image`)
- L29 _prototype_ `TPair<TArray<FString>, TArray<FString>> FilterFramePaths(const UFootageCaptureData* InCaptureData, FFilteringPredicate InPredicate);` (scope `UE::MetaHuman::Image`)
- L30 _prototype_ `TPair<TArray<FString>, TArray<FString>> FilterFramePaths(const TPair<TArray<FString>, TArray<FString>>& InImagePaths, FFilteringPredicate InPredicate);` (scope `UE::MetaHuman::Image`)
- L32 _prototype_ `TArray<int32> FilterFrameIndices(const TPair<TArray<FString>, TArray<FString>>& InImagePaths, FFilteringPredicate InPredicate);` (scope `UE::MetaHuman::Image`)
- L36 _function_ `template<typename Predicate> TPair<TArray<FString>, TArray<FString>> FilterFramePaths(const UFootageCaptureData* InCaptureData, Predicate&& InPredicate)` (scope `UE::MetaHuman::Image`)
- L42 _function_ `template<typename Predicate> TPair<TArray<FString>, TArray<FString>> FilterFramePaths(const TPair<TArray<FString>, TArray<FString>>& InImagePaths, Predicate&& InPredicate)` (scope `UE::MetaHuman::Image`)
- L49 _function_ `template<typename Predicate> TArray<int32> FilterFrameIndices(const TPair<TArray<FString>, TArray<FString>>& InImagePaths, Predicate&& InPredicate)` (scope `UE::MetaHuman::Image`)
- L55 _prototype_ `FString GetCameraId(TObjectPtr<const UObject> InObject);` (scope `UE::MetaHuman::Image`)
- L59 _namespace_ `namespace Points` (scope `UE::MetaHuman`)
- L62 _prototype_ `void ScalePointsInPlace(TArray<FVector2D>& InPoints, float InScale);` (scope `UE::MetaHuman::Points`)
- L64 _prototype_ `FVector2D MapTexturePointToLocalWidgetSpace(const FVector2D& InPoint, const FVector2D& InTextureSize, const FBox2D& InUV, const FVector2D& InWidgetSize);` (scope `UE::MetaHuman::Points`)
- L69 _prototype_ `FVector2D MapWidgetPointToTextureSpace(const FVector2D& InWidgetPoint, const FVector2D& InWidgetSize, const FBox2D& InUV, const FVector2D& InTextureSize);` (scope `UE::MetaHuman::Points`)
- L74 _prototype_ `FVector2D MapTextureSizeToLocalWidgetSize(const FVector2D& InBeginPoint, const FVector2D& InCurrentSize, const FVector2D& InTextureSize, const FBox2D& InUV, const FVector2D& InWidgetSize);` (scope `UE::MetaHuman::Points`)
- L80 _prototype_ `FVector2D MapRealTextureSizeToLocalWidgetSize(const FVector2D& InBeginPoint, const FVector2D& InCurrentSize, const FVector2D& InTextureSize, const FBox2D& InUV, const FVector2D& InWidgetSize);` (scope `UE::MetaHuman::Points`)
- L86 _prototype_ `bool IsOutsideWidgetBounds(const FVector2D& ScaledPoint, const FVector2D& WidgetSize);` (scope `UE::MetaHuman::Points`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Utils/MetaHumanChessboardPointCounter.h` (Public)


#### class `FMetaHumanChessboardPointCounter`  
`class FMetaHumanChessboardPointCounter`  
_L13-54_
- L17 _public typedef_ `using FPoints = TArray<FVector2D>;`
- L18 _public typedef_ `using FFramePointsMap = TMap<int32, FPoints>;`
- L19 _public typedef_ `using FFramePerCameraPoints = TMap<FString, FPoints>;`
- L20 _public typedef_ `using FFramePerCameraPointsArray = TArray<FFramePerCameraPoints>;`
- L21 _public typedef_ `using FFramePerCameraPointsMap = TMap<int32, FFramePerCameraPoints>;`
- L23 _public prototype_ `FMetaHumanChessboardPointCounter(const FVector2D& InCoverageMapSize, const TPair<FString, FString>& InCameraNames, const TPair<FIntVector2, FIntVector2>& InImageSizes);`
- L27 _public prototype_ `void Invalidate(TOptional<FVector2D> InCoverageMapSize = TOptional<FVector2D>());`
- L28 _public prototype_ `void Invalidate(const FFramePerCameraPointsArray& InFrameArray, TOptional<FVector2D> InCoverageMapSize = TOptional<FVector2D>());`
- L30 _public prototype_ `void Update(const FString& InCameraName, const FPoints& InFramePoints);`
- L31 _public prototype_ `void Update(const FString& InCameraName, const FFramePointsMap& InFramePointsMap);`
- L32 _public prototype_ `void Update(const FFramePerCameraPoints& InFramePerCameraPoints);`
- L33 _public prototype_ `void Update(const FFramePerCameraPointsArray& InFramePerCameraArray);`
- L34 _public prototype_ `void Update(const FFramePerCameraPointsMap& InFramePerCameraMap);`
- L36 _public prototype_ `TArray<int32> GetBlockIndices(const FString& InCameraName);`
- L37 _public prototype_ `TArray<int32> GetOccupiedBlockIndices(const FString& InCameraName, int32 InOccupancyThreshold = 0);`
- L38 _public prototype_ `TMap<int32, int32> GetOccupiedBlockIndicesAndCount(const FString& InCameraName, int32 InOccupancyThreshold = 0);`
- L40 _public prototype_ `TOptional<int32> GetCountForBlock(const FString& InCameraName, int32 InBlockIndex) const;`
- L41 _public prototype_ `FVector2D GetBlockSize() const;`
- L42 _public prototype_ `FBox2D GetBlock(const FString& InCameraName, int32 InBlockIndex);`
- L46 _private prototype_ `void InvalidateForCamera(const FString& InCamera, const FIntVector2& InImageSize);`
- L48 _private member_ `FVector2D CoverageMapSize;`
- L49 _private member_ `TPair<FString, FString> CameraNames;`
- L50 _private member_ `TPair<FIntVector2, FIntVector2> ImageSizes;`
- L52 _private member_ `TMap<FString, TArray<FBox2D>> ArrayOfBlocks;`
- L53 _private member_ `TMap<FString, TArray<int32>> NumberOfPointsPerBlock;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Widgets/SMetaHumanCalibrationObjectWidget.h` (Public)


#### class `SMetaHumanCalibrationObjectWidget`  
`template<class FObjectType> class SMetaHumanCalibrationObjectWidget : public SCompoundWidget`  
_L14-80_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectChanged, const FPropertyChangedEvent&);`
- L20 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCalibrationObjectWidget) : _Object(nullptr) , _OnObjectChanged(nullptr)`
- L26 _public function_ `SLATE_ARGUMENT(TWeakObjectPtr<FObjectType>, Object) SLATE_EVENT(FOnObjectChanged, OnObjectChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L59 _public function_ `void Reset(TWeakObjectPtr<FObjectType> InObject)`
- L66 _public function_ `void Refresh()`
- L73 _private function_ `void OnDetailsPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent)`
- L78 _private member_ `FOnObjectChanged OnObjectChanged;`
- L79 _private member_ `TSharedPtr<IDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectChanged, const FPropertyChangedEvent&);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Widgets/SMetaHumanImageViewerScrubber.h` (Public)


#### enum `EFrameState::Type`  
`enum Type`  
_L15-20_
- L17 _public enumerator_ `Ok = 0`
- L18 _public enumerator_ `Bad = 1`
- L19 _public enumerator_ `Neutral = 2`

#### class `IFrameStateProvider`  
`class IFrameStateProvider`  
_L24-31_
- L28 _public prototype_ `virtual ~IFrameStateProvider() = default;`
- L29 _public prototype_ `virtual const TMap<int32, EFrameState::Type>& GetFrameStates() const = 0;`
- L30 _public prototype_ `virtual int32 GetNumberOfFrames() const = 0;`

#### class `SMetaHumanImageViewerScrubber`  
`class SMetaHumanImageViewerScrubber : public SCompoundWidget, public IFrameStateProvider`  
_L33-85_
- inherits: `SCompoundWidget,IFrameStateProvider`
- L37 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanImageViewerScrubber) : _OnValueChanged() , _Style() , _NumberOfFrames(0) , _FrameRate(0.0) , _AllowVisualization(true)`
- L46 _public prototype_ `SLATE_EVENT(FOnFloatValueChanged, OnValueChanged) SLATE_STYLE_ARGUMENT(FSliderStyle, Style) SLATE_ARGUMENT(int32, NumberOfFrames) SLATE_ARGUMENT(double, FrameRate) SLATE_ARGUMENT(bool, AllowVisualization) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L56 _public prototype_ `void SetFrameStates(const TMap<int32, EFrameState::Type>& InFrameStates);`
- L57 _public prototype_ `void SetFrameState(int32 InFrameNumber, EFrameState::Type InFrameState);`
- L58 _public prototype_ `void RemoveFrameState(int32 InFrameNumber);`
- L59 _public prototype_ `void RemoveFrameStates();`
- L62 _public prototype_ `float GetValue() const;` — SSlider API
- L63 _public prototype_ `void SetValue(float InValue);`
- L64 _public prototype_ `void SetMinAndMaxValues(float InMinValue, float InMaxValue);`
- L66 _public prototype_ `virtual int32 GetNumberOfFrames() const override;`
- L67 _public prototype_ `virtual const TMap<int32, EFrameState::Type>& GetFrameStates() const override;`
- L71 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L72 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L73 _private prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& InCaptureLostEvent) override;`
- L74 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L77 _private prototype_ `FText HandleTimerTextBlock() const;`
- L78 _private prototype_ `FText HandleFrameTextBlock() const;`
- L79 _private prototype_ `FText HandleFrameRateBlock() const;`
- L81 _private member_ `TSharedPtr<SSlider> Scrubber;`
- L83 _private member_ `TMap<int32, EFrameState::Type> FrameStates;`
- L84 _private member_ `double FrameRate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`
- L12 _namespace_ `namespace EFrameState`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationCore/Public/Widgets/SMetaHumanSingleImageViewer.h` (Public)


#### class `SMetaHumanCalibrationSingleImageViewer`  
`class SMetaHumanCalibrationSingleImageViewer : public SMetaHumanImageViewer`  
_L13-62_
- inherits: `SMetaHumanImageViewer`
- L16 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnAddOverlays, FBox2d, const FGeometry&, FSlateWindowElementList&, int32&);`
- L17 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnImageClick, FVector2D, FBox2d, FVector2D);`
- L19 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCalibrationSingleImageViewer)`
- L23 _public prototype_ `SLATE_ARGUMENT(TArray<FString>, Images) SLATE_EVENT(FOnAddOverlays, OnAddOverlays) SLATE_EVENT(FOnImageClick, OnImageClick) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `void SetImages(TArray<FString> InImages);`
- L31 _public prototype_ `void ShowImage(int32 InImageIndex);`
- L33 _public prototype_ `FIntVector2 GetImageSize() const;`
- L34 _public prototype_ `int32 GetImageNum() const;`
- L35 _public prototype_ `FString GetImagePath(int32 InImageIndex) const;`
- L36 _public prototype_ `const TArray<FString>& GetImagePaths() const;`
- L38 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FAreaSelectionEnded, FSlateRect, FBox2d, FVector2D);`
- L39 _public prototype_ `void StartSelecting(FAreaSelectionEnded InOnSelectionEnded);`
- L41 _public prototype_ `bool IsSelecting() const;`
- L45 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L46 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L47 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L50 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;` — Paint callback
- L54 _private member_ `TArray<FString> Images;`
- L55 _private member_ `FOnAddOverlays OnAddOverlays;`
- L56 _private member_ `FOnImageClick OnImageClick;`
- L57 _private member_ `FSlateBrush CameraImageViewerBrush;`
- L58 _private member_ `TStrongObjectPtr<UTexture2D> CameraImageTexture;`
- L60 _private member_ `TOptional<FMetaHumanCalibrationAreaSelection> DraggingArea;`
- L61 _private member_ `FAreaSelectionEnded OnSelectionEnded;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCALIBRATIONCORE_API`
- L16 _delegate_ `DECLARE_DELEGATE_FourParams(FOnAddOverlays, FBox2d, const FGeometry&, FSlateWindowElementList&, int32&);`
- L17 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnImageClick, FVector2D, FBox2d, FVector2D);`
- L38 _delegate_ `DECLARE_DELEGATE_ThreeParams(FAreaSelectionEnded, FSlateRect, FBox2d, FVector2D);`
