# Plugins / WaveformTransformationsWidgets

- module root: `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets`
- headers: 9; symbols: 227
- symbol kinds: class=10, delegate=2, enum=2, enumerator=14, function=12, macro=3, member=71, namespace=2, prototype=101, struct=2, typedef=1, variable=7
- PublicDependencyModuleNames: AudioExtensions, AudioWidgets, ContentBrowser, Core, CoreUObject, DeveloperSettings, EditorStyle, Engine, InputCore, PropertyEditor, SignalProcessing, Slate, SlateCore, ToolMenus, UMG, UnrealEd, WaveformTransformations

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Private/WaveformTransformationFadeRenderer.h` (Private)


#### struct `FFadeRegion`  
`struct FFadeRegion`  
_L11-29_
- L13 _public member_ `uint32 FadeInStartX = 0;`
- L14 _public member_ `uint32 FadeInEndX = 0;`
- L15 _public member_ `uint32 FadeOutStartX = 0;`
- L16 _public member_ `uint32 FadeOutEndX = 0;`
- L18 _public member_ `TArray<FVector2D> FadeInCurvePoints;`
- L19 _public member_ `TArray<FVector2D> FadeOutCurvePoints;`
- L21 _public member_ `TRange<float> FadeInStartInteractionXRange = TRange<float>::Inclusive(0.f, 0.f);`
- L22 _public member_ `TRange<float> FadeInEndInteractionXRange = TRange<float>::Inclusive(0.f, 0.f);`
- L23 _public member_ `TRange<float> FadeInStartInteractionYRange = TRange<float>::Inclusive(0.f, 0.f);`
- L24 _public member_ `TRange<float> FadeInEndInteractionYRange = TRange<float>::Inclusive(0.f, 0.f);`
- L25 _public member_ `TRange<float> FadeOutStartInteractionXRange = TRange<float>::Inclusive(0.f, 0.f);`
- L26 _public member_ `TRange<float> FadeOutEndInteractionXRange = TRange<float>::Inclusive(0.f, 0.f);`
- L27 _public member_ `TRange<float> FadeOutStartInteractionYRange = TRange<float>::Inclusive(0.f, 0.f);`
- L28 _public member_ `TRange<float> FadeOutEndInteractionYRange = TRange<float>::Inclusive(0.f, 0.f);`

#### class `FWaveformTransformationFadeRenderer`  
`class FWaveformTransformationFadeRenderer : public FWaveformTransformationRendererBase`  
_L31-95_
- inherits: `FWaveformTransformationRendererBase`
- L34 _public function_ `FWaveformTransformationFadeRenderer() : RoundedBoxBrush(FLinearColor::Green, 2)`
- L35 _public prototype_ `~FWaveformTransformationFadeRenderer();`
- L37 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L38 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L39 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L42 _public prototype_ `virtual FReply OnMouseWheel(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L45 _public prototype_ `virtual void SetWaveformTransformation(TObjectPtr<UWaveformTransformationBase> InTransformation) override;`
- L48 _protected prototype_ `int32 DrawOffsetHandles(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L49 _protected prototype_ `int32 DrawFadeCurves(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L50 _protected prototype_ `void GenerateFadeCurves(const FGeometry& AllottedGeometry);`
- L51 _protected prototype_ `void UpdateInteractionRange(const FGeometry& AllottedGeometry);`
- L53 _protected prototype_ `bool IsCursorInFadeInteractionRange(const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry) const;`
- L55 _protected prototype_ `FText GetPropertyEditedByCurrentInteraction() const;`
- L56 _protected prototype_ `FVector2D GetLocalCursorPosition(const FPointerEvent& MouseEvent, const FGeometry& EventGeometry) const;`
- L57 _protected prototype_ `double ConvertXRatioToTime(const float InRatio) const;`
- L59 _protected member_ `TArray<FFadeRegion> FadeRegions;`
- L61 _protected member_ `double PixelsPerFrame = 0.0;`
- L62 _protected member_ `const float InteractionHandleSize = 30.0f;`
- L63 _protected member_ `FVector2D MousePosition;`
- L64 _protected member_ `int32 TransactionResult = INDEX_NONE;`
- L77 _protected member_ `TPair<EFadeInteractionType, int32> FadeInteractionTypeAndIndex = TPair<EFadeInteractionType, int32>(EFadeInteractionType::None, 0);`
- L79 _protected prototype_ `TPair<EFadeInteractionType, int32> GetInteractionTypeAndIndexFromCursorPosition(const FVector2D& InLocalCursorPosition, const FKey MouseButton, const FGeometry& WidgetGeometry) const;`
- L80 _protected prototype_ `void SetPropertyValueDependingOnInteractionType(const FPointerEvent& MouseEvent, const FGeometry& WidgetGeometry, const EPropertyChangeType::Type ChangeType = EPropertyChangeType::ValueSet);`
- L81 _protected prototype_ `void ShowSelectFadeModeMenuAtCursor(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L82 _protected prototype_ `const FSlateIcon GetFadeModeIcon(const EWaveEditorTransformationFadeMode& FadeMode) const;`
- L84 _protected member_ `const FSlateRoundedBoxBrush RoundedBoxBrush;`
- L86 _protected member_ `TWeakPtr<SWindow> FadeModeMenuWindow = nullptr;`
- L88 _protected member_ `TStrongObjectPtr<UWaveformTransformationFade> StrongFade = nullptr;`
- L90 _protected member_ `FDelegateHandle PopupHandle;`
- L91 _protected member_ `FDelegateHandle ApplicationActivationStateHandle;`
- L93 _protected prototype_ `DECLARE_DELEGATE(FOnFadeModeChanged);`
- L94 _protected member_ `FOnFadeModeChanged OnFadeModeChanged;`

#### enum `FWaveformTransformationFadeRenderer::EFadeInteractionType`  
`enum class EFadeInteractionType : uint8`  
_L66-75_
- L68 _public enumerator_ `None = 0`
- L69 _public enumerator_ `ScrubbingFadeInStart`
- L70 _public enumerator_ `ScrubbingFadeInEnd`
- L71 _public enumerator_ `ScrubbingFadeOutStart`
- L72 _public enumerator_ `ScrubbingFadeOutEnd`
- L73 _public enumerator_ `RightClickFadeIn`
- L74 _public enumerator_ `RightClickFadeOut`

#### Free symbols / members of external scopes

- L93 _delegate_ `DECLARE_DELEGATE(FOnFadeModeChanged);`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Private/WaveformTransformationMarkersRenderer.h` (Private)


#### class `FWaveformTransformationMarkerRenderer`  
`class FWaveformTransformationMarkerRenderer : public FWaveformTransformationRendererBase`  
_L11-106_
- inherits: `FWaveformTransformationRendererBase`
- L14 _public prototype_ `FWaveformTransformationMarkerRenderer();`
- L15 _public prototype_ `~FWaveformTransformationMarkerRenderer();`
- L17 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L18 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L19 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L20 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L21 _public prototype_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L22 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L23 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L25 _public prototype_ `virtual void SetWaveformTransformation(TObjectPtr<UWaveformTransformationBase> InTransformation) override;`
- L28 _private prototype_ `int32 DrawMarkerHandles(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L30 _private prototype_ `void ApplyWidgetSettings(const UWaveformTransformationsWidgetsSettings* Settings);`
- L32 _private prototype_ `void SetLoopColors(const TArray<FLinearColor>& InColors);`
- L34 _private prototype_ `bool IsPositionInInteractionRange(const int64 InFramePosition, const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry) const;`
- L35 _private prototype_ `bool IsPositionInLoopArea(const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry, const FSoundWaveCuePoint* CueMarker, bool IncludeHandleArea = true) const;`
- L36 _private prototype_ `bool IsPositionInLoopHandleArea(const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry, const FSoundWaveCuePoint& CueMarker, bool IsLeftHandle) const;`
- L37 _private prototype_ `bool SetMarkerInInteractionRange(const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry);`
- L38 _private prototype_ `bool SelectLoopArea(const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry);`
- L39 _private prototype_ `void SetActiveLoopRegion(int32 CuePointID);`
- L40 _private prototype_ `void PreviewSelectedLoop();`
- L41 _private prototype_ `void SetIsPreviewingLoopRegion(double InStartTime, double InEndTime, bool bIsPreviewing);`
- L42 _private prototype_ `static FVector2D GetLocalCursorPosition(const FPointerEvent& MouseEvent, const FGeometry& EventGeometry);`
- L44 _private member_ `TArray<TRange<float>> InteractionRanges;`
- L55 _private member_ `MarkerHandle, RightClickMarker, DeselectRegion, } MarkerInteractionType = EMarkerInteractionType::None;`
- L71 _private member_ `} MarkerInInteractionRange;`
- L73 _private prototype_ `EMarkerInteractionType EvaluateInteractionTypeFromCursorPosition(const FVector2D& InLocalCursorPosition, const FGeometry& WidgetGeometry, const FKey MouseButton);`
- L74 _private prototype_ `void SetPropertyValueDependingOnInteractionType(const FPointerEvent& MouseEvent, const FGeometry& WidgetGeometry);`
- L76 _private prototype_ `void ShowConvertToLoopAtMarker(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, FSoundWaveCuePoint* CueToModify);`
- L78 _private member_ `TArray<FSoundWaveCuePoint> CuePoints;`
- L79 _private member_ `TArray<FSoundWaveCuePoint> LoopPoints;`
- L81 _private member_ `TStrongObjectPtr<UWaveCueArray> MarkersArray;`
- L83 _private member_ `double PixelsPerFrame = 0.0;`
- L86 _private member_ `static constexpr float LoopHandlePixelWidth = 7.0f;` — Ensures handles are always visible to a user and we can avoid overlapping handle regions when loop regions are too small, in future consider dynamic relative size based on window size
- L88 _private member_ `FVector2D MousePosition;`
- L89 _private member_ `FSoundWaveCuePoint* MarkerToModify = nullptr;`
- L90 _private member_ `int32 HighlightedCue = INDEX_NONE;`
- L92 _private member_ `FLinearColor MarkerColor = WaveformTransformationWidgetSharedDefaults::DefaultMarkerColor;`
- L93 _private member_ `FLinearColor SelectedMarkerColor = WaveformTransformationWidgetSharedDefaults::DefaultSelectedMarkerColor;`
- L94 _private member_ `TArray<FLinearColor> LoopColors = WaveformTransformationWidgetSharedDefaults::DefaultLoopColors;`
- L95 _private member_ `FLinearColor LabelTextColor = WaveformTransformationWidgetSharedDefaults::DefaultLabelTextColor;`
- L96 _private member_ `float LabelFontSize = WaveformTransformationWidgetSharedDefaults::DefaultLabelFontSize;`
- L98 _private member_ `TStrongObjectPtr<UWaveformTransformationMarkers> StrongMarkersTransformation = nullptr;`
- L99 _private member_ `static const bool bMarkFileDirty = false;`
- L101 _private member_ `FDelegateHandle PopupHandle;`
- L102 _private member_ `FDelegateHandle ApplicationActivationStateHandle;`
- L103 _private member_ `FDelegateHandle OnSettingChangedDelegateHandle;`
- L105 _private member_ `TWeakPtr<SWindow> CreateLoopMenuWindow;`

#### enum `FWaveformTransformationMarkerRenderer::EMarkerInteractionType`  
`enum class EMarkerInteractionType : uint8`  
_L46-55_
- L48 _public enumerator_ `None = 0`
- L49 _public enumerator_ `ScrubbingMarkerHandleRight`
- L50 _public enumerator_ `ScrubbingMarkerHandleLeft`
- L51 _public enumerator_ `LoopHandle`
- L52 _public enumerator_ `MarkerHandle`
- L53 _public enumerator_ `RightClickMarker`
- L54 _public enumerator_ `DeselectRegion`

#### class `FWaveformTransformationMarkerRenderer::FMarkerInInteractionRange`  
`class FMarkerInInteractionRange`  
_L57-71_
- L60 _public prototype_ `void SetMarkerInInteractionRange(FSoundWaveCuePoint* InMarkerPtr, const bool InIsLoopRegionEndMarker = false, int64 GrabXOffset = 0);`
- L61 _public function_ `FSoundWaveCuePoint* GetMarker() const`
- L62 _public prototype_ `void SetMarkerPosition(const float InPosition, bool bIsLeft);`
- L63 _public function_ `void SetMinLoopSize(int64 value)`
- L64 _public function_ `const int64 GetMinLoopSize() const`
- L67 _private member_ `FSoundWaveCuePoint* MarkerPtr = nullptr;`
- L68 _private member_ `bool IsLoopRegionEndMarker = false;`
- L69 _private member_ `int64 GrabOffset = 0;`
- L70 _private member_ `int64 MinLoopSize = UWaveCueArray::MinLoopSize;`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Private/WaveformTransformationTrimFadeRenderer.h` (Private)


#### class `FWaveformTransformationTrimFadeRenderer`  
`class FWaveformTransformationTrimFadeRenderer : public FWaveformTransformationFadeRenderer`  
_L11-27_
- inherits: `FWaveformTransformationFadeRenderer`
- L15 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L16 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L17 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L18 _public prototype_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L20 _public prototype_ `virtual void SetWaveformTransformation(TObjectPtr<UWaveformTransformationBase> InTransformation) override;`
- L24 _private prototype_ `void SetPropertyValueDependingOnInteractionType(const FPointerEvent& MouseEvent, const FGeometry& WidgetGeometry, const EPropertyChangeType::Type ChangeType = EPropertyChangeType::ValueSet);`
- L26 _private member_ `TStrongObjectPtr<UWaveformTransformationTrimFade> StrongTrimFade = nullptr;`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Private/WaveformTransformationsWidgetsSettings.h` (Private)


#### class `UWaveformTransformationsWidgetsSettings`  
`class UWaveformTransformationsWidgetsSettings : public UDeveloperSettings`  
_L21-62_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, defaultconfig, meta = (DisplayName = "Waveform Transformations Display"))`
- inherits: `UDeveloperSettings`
- L27 _public prototype_ `UWaveformTransformationsWidgetsSettings(const FObjectInitializer& ObjectInitializer);`
- L30 _public prototype_ `virtual FName GetCategoryName() const;`
- L32 _public prototype_ `virtual FName GetSectionName() const override;`
- L35 _public prototype_ `virtual FText GetSectionText() const override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public prototype_ `virtual void PostEditUndo() override;`
- L41 _public prototype_ `static FOnWaveformTransformationsWidgetsSettingsChanged& OnSettingChanged();`
- L47 _public member_ `FLinearColor MarkerColor;` — `UPROPERTY(config, EditAnywhere, Category = "Markers")` — Set the color of your Waveform Markers
- L51 _public member_ `TArray<FLinearColor> LoopColors;` — `UPROPERTY(config, EditAnywhere, Category = "Markers")` — A list of colors so marker regions can have different colors
- L54 _public member_ `FLinearColor LabelTextColor;` — `UPROPERTY(config, EditAnywhere, Category = "Markers")`
- L57 _public member_ `float LabelFontSize;` — `UPROPERTY(config, EditAnywhere, Category = "Markers", Meta = (ClampMin = "1", ClampMax = "15"))`
- L61 _private member_ `static FOnWaveformTransformationsWidgetsSettingsChanged SettingsChangedDelegate;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveformTransformationsWidgetsSettingsChanged, const FName& , const UWaveformTransformationsWidgetsSettings*);`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveformTransformationsWidgetsSettingsChanged, const FName& , const UWaveformTransformationsWidgetsSettings*);`
- L11 _namespace_ `namespace WaveformTransformationWidgetSharedDefaults`
- L13 _variable_ `const FLinearColor DefaultMarkerColor = FLinearColor(1.f, 0.9f, 0, 0.5f);` (scope `WaveformTransformationWidgetSharedDefaults`)
- L14 _variable_ `const FLinearColor DefaultSelectedMarkerColor = FLinearColor(1.f, 0.9f, 0, 1.f);` (scope `WaveformTransformationWidgetSharedDefaults`)
- L15 _variable_ `const TArray<FLinearColor> DefaultLoopColors = { FLinearColor(0.8f, 0.6f, 1.f, 0.75f), FLinearColor(0.2f, 0.7f, 1.f, 0.75f) };` (scope `WaveformTransformationWidgetSharedDefaults`)
- L16 _variable_ `const FLinearColor DefaultLabelTextColor = FLinearColor(0.9f, 0.9f, 0.9f, 1.f);` (scope `WaveformTransformationWidgetSharedDefaults`)
- L17 _variable_ `const float DefaultLabelFontSize = 10.f;` (scope `WaveformTransformationWidgetSharedDefaults`)

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Public/IWaveformTransformationRenderer.h` (Public)


#### struct `FWaveformTransformationRenderInfo`  
`struct FWaveformTransformationRenderInfo`  
_L21-28_
- L23 _public member_ `float SampleRate = 0.f;`
- L24 _public member_ `int32 NumChannels = 0;`
- L25 _public member_ `int64 StartFrameOffset = 0;` — the first frame this transformation can act upon
- L26 _public member_ `uint32 TotalNumSamples = 0;` — the number of total samples in the original waveform
- L27 _public member_ `uint32 NumSamplesAvailable = 0;` — the number of samples available to the transformation

#### class `IWaveformTransformationRenderer`  
`class IWaveformTransformationRenderer`  
_L30-56_
- L33 _public prototype_ `virtual ~IWaveformTransformationRenderer() = default;`
- L36 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const = 0;` — SWidget interceptor methods
- L37 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) = 0;`
- L38 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L39 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L40 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(SWidget& OwnerWidget, const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) = 0;`
- L41 _public prototype_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L42 _public prototype_ `virtual FReply OnMouseWheel(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L43 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L44 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) = 0;`
- L45 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const = 0;`
- L46 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) = 0;`
- L49 _public prototype_ `virtual void SetTransformationWaveInfo(const FWaveformTransformationRenderInfo& InWaveInfo) = 0;` — Gets info about the transformation being rendered
- L51 _public prototype_ `virtual void SetWaveformTransformation(TObjectPtr<UWaveformTransformationBase> InTransformation) = 0;`
- L55 _public prototype_ `virtual void SetPropertyHandles(const TArray<TSharedRef<IPropertyHandle>>& InPropertyHandles) = 0;` — Gets the transformations properties. IPropertyHandle is used to get/set properties to have full support of change notifiers, editor undo ecc

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Public/WaveformTransformationDurationRenderer.h` (Public)


#### class `FWaveformTransformationDurationRenderer`  
`class FWaveformTransformationDurationRenderer : public FWaveformTransformationRendererBase`  
_L19-29_
- inherits: `FWaveformTransformationRendererBase`
- L22 _public prototype_ `explicit FWaveformTransformationDurationRenderer(const uint32 InOriginalWaveformNumFrames);`
- L24 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L25 _public prototype_ `void SetOriginalWaveformFrames(const uint32 NumFrames);`
- L28 _private member_ `uint32 OriginalWaveformNumFrames = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONSWIDGETS_API`
- L13 _namespace_ `namespace WaveformTransformationDurationHiglightParams`
- L15 _variable_ `const FLazyName BackgroundBrushName = TEXT("Whi` (scope `WaveformTransformationDurationHiglightParams`)
- L16 _variable_ `const FLinearColor BoxColor = FLinearColor(0.f, 0.f, 0.f, 0.7f);` (scope `WaveformTransformationDurationHiglightParams`)

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Public/WaveformTransformationRendererBase.h` (Public)


#### class `FWaveformTransformationRendererBase`  
`class FWaveformTransformationRendererBase : public IWaveformTransformationRenderer`  
_L11-68_
- inherits: `IWaveformTransformationRenderer`
- L14 _public prototype_ `FWaveformTransformationRendererBase() = default;`
- L16 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L17 _public function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L18 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L19 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L20 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(SWidget& OwnerWidget, const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L21 _public prototype_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L22 _public prototype_ `virtual FReply OnMouseWheel(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L23 _public function_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L24 _public function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override`
- L25 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L26 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L28 _public prototype_ `virtual void SetTransformationWaveInfo(const FWaveformTransformationRenderInfo& InWaveInfo) override;`
- L29 _public function_ `virtual void SetWaveformTransformation(TObjectPtr<UWaveformTransformationBase> InTransformation) override`
- L32 _public prototype_ `virtual void SetPropertyHandles(const TArray<TSharedRef<IPropertyHandle>>& InPropertyHandles) override;` — `UE_DEPRECATED(5.7, "PropertyHandles have been deprecated.")`
- L36 _protected prototype_ `TSharedPtr<IPropertyHandle> GetPropertyHandle(const FName& PropertyName) const;` — `UE_DEPRECATED(5.7, "PropertyHandles have been deprecated.")`
- L40 _protected function_ `T GetPropertyValue(const TSharedPtr<IPropertyHandle>& PropertyHandle)` — `UE_DEPRECATED(5.7, "PropertyHandles have been deprecated.")`
- L50 _protected function_ `void SetPropertyValue(const FName& PropertyName, const T Value, const EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags)` — `UE_DEPRECATED(5.7, "PropertyHandles have been deprecated.")`
- L56 _protected prototype_ `int32 BeginTransaction(const TCHAR* TransactionContext, const FText& Description, UObject* PrimaryObject);`
- L57 _protected prototype_ `int32 EndTransaction();`
- L59 _protected member_ `FWaveformTransformationRenderInfo TransformationWaveInfo;`
- L61 _protected member_ `static constexpr float InteractionPixelXDelta = 10;`
- L62 _protected member_ `static constexpr float InteractionRatioYDelta = 0.07f;`
- L63 _protected member_ `static constexpr float MouseWheelStep = 0.1f;`
- L67 _private member_ `TArray<TSharedRef<IPropertyHandle>> CachedPropertyHandles;` — `UE_DEPRECATED(5.7, "PropertyHandles have been deprecated.")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONSWIDGETS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Public/WaveformTransformationRendererMapper.h` (Public)


#### class `FWaveformTransformationRendererMapper`  
`class FWaveformTransformationRendererMapper`  
_L11-39_
- L15 _public prototype_ `static FWaveformTransformationRendererMapper& Get();` — Access the singleton instance for mapper
- L16 _public prototype_ `static void Init();`
- L19 _public function_ `template<typename ConcreteRendererType> bool RegisterRenderer(const UClass* SupportedTransformation)`
- L31 _public prototype_ `void UnregisterRenderer(const UClass* SupportedTransformation);`
- L33 _public prototype_ `FWaveformTransformRendererInstantiator* GetRenderer(const UClass* WaveformTransformationClass);`
- L36 _private member_ `static TUniquePtr<FWaveformTransformationRendererMapper> Instance;`
- L38 _private member_ `TMap<const UClass*, FWaveformTransformRendererInstantiator> TransformationsTypeMap;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONSWIDGETS_API`
- L9 _typedef_ `using FWaveformTransformRendererInstantiator = TFunction<TSharedPtr<IWaveformTransformationRenderer>()>;`
- L22 _function_ `` (scope `FWaveformTransformationRendererMapper::RegisterRenderer`)

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Public/WaveformTransformationsWidgetsModule.h` (Public)


#### class `FWaveformTransformationsWidgetsModule`  
`class FWaveformTransformationsWidgetsModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L11 _private prototype_ `virtual void ShutdownModule() override;`
