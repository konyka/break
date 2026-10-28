# Plugins / WaveformEditorWidgets

- module root: `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets`
- headers: 12; symbols: 246
- symbol kinds: class=12, delegate=11, function=11, macro=8, member=83, prototype=116, typedef=5
- PublicDependencyModuleNames: AudioExtensions, AudioWidgets, ContentBrowser, Core, CoreUObject, DeveloperSettings, EditorStyle, Engine, InputCore, SignalProcessing, Slate, SlateCore, ToolMenus, UMG, WaveformTransformationsWidgets

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Private/SWaveformEditorInputRoutingOverlay.h` (Private)


#### class `SWaveformEditorInputRoutingOverlay`  
`class SWaveformEditorInputRoutingOverlay : public SLeafWidget`  
_L13-44_
- inherits: `SLeafWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWaveformEditorInputRoutingOverlay)`
- L20 _public prototype_ `SLATE_STYLE_ARGUMENT(FSampledSequenceViewerStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<TSharedPtr<SWidget>>& InOverlaidWidgets);`
- L26 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)override;`
- L28 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L32 _public member_ `FPointerEventHandler OnMouseWheelDelegate;`
- L35 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L36 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L38 _private member_ `TArray<TSharedPtr<SWidget>> OverlaidWidgets;`
- L40 _private member_ `const FSampledSequenceViewerStyle* Style = nullptr;`
- L42 _private member_ `float DesiredWidth = 1280.f;`
- L43 _private member_ `float DesiredHeight = 720.f;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Private/WaveformEditorWidgetsSettings.h` (Private)


#### class `UWaveformEditorWidgetsSettings`  
`class UWaveformEditorWidgetsSettings : public UDeveloperSettings`  
_L12-96_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, defaultconfig, meta = (DisplayName = "Waveform Editor Display"))`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `UWaveformEditorWidgetsSettings(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual FName GetCategoryName() const;`
- L24 _public prototype_ `virtual FText GetSectionText() const override;`
- L26 _public prototype_ `virtual FName GetSectionName() const override;`
- L28 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _public prototype_ `static FOnWaveformEditorWidgetsSettingsChanged& OnSettingChanged();`
- L36 _public member_ `FLinearColor PlayheadColor;` — `UPROPERTY(config, EditAnywhere, Category = "Playhead")`
- L39 _public member_ `FLinearColor WaveformColor;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer")`
- L42 _public member_ `float WaveformLineThickness;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer", Meta = (ClampMin = "1", ClampMax = "10"))`
- L45 _public member_ `float SampleMarkersSize;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer", Meta = (ClampMin = "0", ClampMax = "30"))`
- L48 _public member_ `FLinearColor WaveformBackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer")`
- L51 _public member_ `float ZeroCrossingLineThickness;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer", Meta = (ClampMin = "1", ClampMax = "10"))`
- L54 _public member_ `FLinearColor MajorGridColor;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer")`
- L57 _public member_ `FLinearColor MinorGridColor;` — `UPROPERTY(config, EditAnywhere, Category = "Waveform Viewer")`
- L60 _public member_ `FLinearColor RulerBackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category = "Ruler")`
- L63 _public member_ `FLinearColor RulerTicksColor;` — `UPROPERTY(config, EditAnywhere, Category = "Ruler")`
- L66 _public member_ `FLinearColor RulerTextColor;` — `UPROPERTY(config, EditAnywhere, Category = "Ruler")`
- L69 _public member_ `float RulerFontSize;` — `UPROPERTY(config, EditAnywhere, Category = "Ruler", Meta = (ClampMin = "1", ClampMax = "15"))`
- L72 _public member_ `bool ShowLoudnessGrid;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid")`
- L75 _public member_ `bool ShowLoudnessGridDecibelValues;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid")`
- L78 _public member_ `uint8 MaxLoudnessGridDivisions;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid", Meta = (ClampMin = "1", ClampMax = "10"))`
- L81 _public member_ `float LoudnessGridThickness;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid", Meta = (ClampMin = "1", ClampMax = "10"))`
- L84 _public member_ `FLinearColor LoudnessGridColor;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid")`
- L87 _public member_ `FLinearColor LoudnessGridTextColor;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid")`
- L90 _public member_ `float LoudnessGridTextSize;` — `UPROPERTY(config, EditAnywhere, Category = "Loudness Grid", Meta = (ClampMin = "1", ClampMax = "15"))`
- L95 _private member_ `static FOnWaveformEditorWidgetsSettingsChanged SettingsChangedDelegate;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveformEditorWidgetsSettingsChanged, const FName& , const UWaveformEditorWidgetsSettings*);`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveformEditorWidgetsSettingsChanged, const FName& , const UWaveformEditorWidgetsSettings*);`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/STransformedWaveformViewPanel.h` (Public)


#### class `STransformedWaveformViewPanel`  
`class STransformedWaveformViewPanel : public SCompoundWidget, public IFixedSampledSequenceViewReceiver`  
_L29-110_
- inherits: `SCompoundWidget,IFixedSampledSequenceViewReceiver`
- L32 _public function_ `SLATE_BEGIN_ARGS(STransformedWaveformViewPanel)`
- L34 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_ARGUMENT(TSharedPtr<SWaveformTransformationsOverlay>, TransformationsOverlay) SLATE_ARGUMENT(TSharedPtr<FWaveformEditorZoomController>, ZoomController) SLATE_ARGUMENT(FPointerEventHandler, OnPlayheadOverlayMouseButtonUp) SLATE_ARGUMENT(FPointerEventHandler, OnTimeRulerMouseButtonUp) SLATE_ARGUMENT(FPointerEventHandler, OnTimeRulerMouseButtonDown) SLATE_ARGUMENT(FPointerEventHandler, OnTimeRulerMouseMove) SLATE_ARGUMENT(FPointerEventHandler, OnMouseWheel) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FFixedSampledSequenceView& InView);`
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L54 _public prototype_ `virtual void ReceiveSequenceView(const FFixedSampledSequenceView InView, const uint32 FirstSampleIndex = 0) override;`
- L55 _public prototype_ `void SetPlayheadRatio(const double InRatio);`
- L56 _public prototype_ `void SetPlayheadFramePosition(const int64 FramePosition);`
- L57 _public prototype_ `void ResolveFromFramePosition();`
- L59 _public prototype_ `void SetOnPlayheadOverlayMouseButtonUp(FPointerEventHandler InEventHandler);`
- L60 _public prototype_ `void SetOnTimeRulerMouseButtonUp(FPointerEventHandler InEventHandler);`
- L61 _public prototype_ `void SetOnTimeRulerMouseButtonDown(FPointerEventHandler InEventHandler);`
- L62 _public prototype_ `void SetOnTimeRulerMouseMove(FPointerEventHandler InEventHandler);`
- L63 _public prototype_ `void SetOnMouseWheel(FPointerEventHandler InEventHandler);`
- L65 _public prototype_ `FReply LaunchTimeRulerContextMenu();`
- L67 _public function_ `const int64 GetPlayheadFramePosition()`
- L70 _private prototype_ `void CreateLayout();`
- L72 _private prototype_ `void SetUpGridData();`
- L73 _private prototype_ `void SetupPlayheadOverlay();`
- L74 _private prototype_ `void SetUpTimeRuler(TSharedRef<FWaveformEditorGridData> InGridData);`
- L75 _private prototype_ `void SetUpWaveformViewer(TSharedRef<FWaveformEditorGridData> InGridData, const FFixedSampledSequenceView& InView);`
- L76 _private prototype_ `void SetUpInputRoutingOverlay();`
- L77 _private prototype_ `void SetUpInputOverrides(const FArguments& InArgs);`
- L78 _private prototype_ `void SetUpValueGridOverlay();`
- L79 _private prototype_ `void SetUpBackground();`
- L82 _private prototype_ `void UpdateDisplayUnit(const ESampledSequenceDisplayUnit InDisplayUnit);`
- L83 _private prototype_ `void UpdatePlayheadPosition(const float PaintedWidth);`
- L84 _private prototype_ `void UpdateBackground(const FSampledSequenceViewerStyle UpdatedStyle);`
- L86 _private prototype_ `void OnWaveEditorWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings);`
- L88 _private member_ `TSharedPtr<FWaveformEditorGridData> GridData;`
- L90 _private member_ `TSharedPtr<SFixedSampledSequenceRuler> TimeRuler;`
- L91 _private member_ `TSharedPtr<SFixedSampledSequenceViewer> WaveformViewer;`
- L92 _private member_ `TSharedPtr<SWaveformTransformationsOverlay> WaveformTransformationsOverlay;`
- L93 _private member_ `TSharedPtr<SWaveformEditorInputRoutingOverlay> InputRoutingOverlay;`
- L94 _private member_ `TSharedPtr<SPlayheadOverlay> PlayheadOverlay;`
- L95 _private member_ `TSharedPtr<SSampledSequenceValueGridOverlay> ValueGridOverlay;`
- L96 _private member_ `TSharedPtr<SBorder> BackgroundBorder;`
- L97 _private member_ `TSharedPtr<FWaveformEditorZoomController> ZoomController;`
- L99 _private member_ `float CachedPixelWidth = 0.f;`
- L101 _private member_ `ESampledSequenceDisplayUnit DisplayUnit;`
- L103 _private member_ `FWaveformEditorStyle* WaveformEditorStyle;`
- L105 _private member_ `FFixedSampledSequenceView DataView;`
- L107 _private member_ `double CachedPlayheadRatio = 0.0;`
- L108 _private member_ `int64 CachedPlayheadFramePosition = 0;`
- L109 _private prototype_ `const UWaveformEditorWidgetsSettings* GetWaveformEditorWidgetsSettings();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/SWaveformEditorMessageDialog.h` (Public)


#### class `SWaveformEditorMessageDialog`  
`class SWaveformEditorMessageDialog : public SCompoundWidget`  
_L11-34_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SWaveformEditorMessageDialog)`
- L18 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(FText, MessageToDisplay) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — A reference to the parent window
- L29 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — The parent window of this widget
- L31 _private prototype_ `bool CanPressCloseButton() const;`
- L33 _private prototype_ `FReply OnCloseButtonPressed() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/SWaveformTransformationRenderLayer.h` (Public)


#### class `SWaveformTransformationRenderLayer`  
`class SWaveformTransformationRenderLayer : public SCompoundWidget`  
_L10-37_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SWaveformTransformationRenderLayer)`
- L16 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IWaveformTransformationRenderer> InTransformationRenderer);`
- L21 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L22 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L23 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L24 _public prototype_ `FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L25 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L30 _public prototype_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L36 _private member_ `TSharedPtr<IWaveformTransformationRenderer> TransformationRenderer;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/SWaveformTransformationsOverlay.h` (Public)


#### class `SWaveformTransformationsOverlay`  
`class SWaveformTransformationsOverlay : public SCompoundWidget`  
_L18-53_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SWaveformTransformationsOverlay) : _AnchorsRatioConverter([](const float InRatio) {return InRatio; })`
- L23 _public function_ `: _AnchorsRatioConverter([](const float InRatio) {return InRatio; })`
- L27 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_ARGUMENT(TFunction<float(const float)>, AnchorsRatioConverter) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TArrayView< const FTransformationLayerRenderInfo> InTransformationRenderers, TSharedPtr<FWaveformEditorZoomController> InZoomController);`
- L34 _public prototype_ `void OnLayerChainGenerated(FTransformationLayerRenderInfo* FirstLayerPtr, const int32 NLayers);`
- L35 _public prototype_ `void UpdateLayerConstraints();`
- L37 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _public prototype_ `FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L44 _private prototype_ `void CreateLayout();`
- L45 _private prototype_ `void UpdateAnchors();`
- L47 _private member_ `TSharedPtr<SOverlay> MainOverlayPtr;`
- L48 _private member_ `TArray<TSharedPtr<SWidget>> TransformationLayers;`
- L49 _private member_ `TArray<SConstraintCanvas::FSlot*> LayersSlots;`
- L50 _private member_ `TArrayView<const FTransformationLayerRenderInfo> TransformationRenderers;`
- L51 _private member_ `TFunction<float(const float)> AnchorsRatioConverter;`
- L52 _private member_ `TSharedPtr<FWaveformEditorZoomController> ZoomController;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`
- L16 _typedef_ `using FTransformationLayerRenderInfo = TPair<TSharedPtr<IWaveformTransformationRenderer>, TPair<float,float>>;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformEditorGridData.h` (Public)


#### class `FWaveformEditorGridData`  
`class FWaveformEditorGridData : public IFixedSampledSequenceGridService`  
_L17-43_
- inherits: `IFixedSampledSequenceGridService`
- L20 _public prototype_ `explicit FWaveformEditorGridData(const uint32 InTotalFrames, const uint32 InSampleRateHz, const float InGridSizePixels = 1.f, const FSlateFontInfo* InTicksTimeFont = nullptr);`
- L22 _public prototype_ `void UpdateDisplayRange(const TRange<uint32> InDisplayRange);`
- L23 _public prototype_ `bool UpdateGridMetrics(const float InGridSizePixels);`
- L24 _public prototype_ `virtual const FFixedSampledSequenceGridMetrics GetGridMetrics() const override;`
- L25 _public prototype_ `void SetTicksTimeFont(const FSlateFontInfo* InNewFont);`
- L26 _public prototype_ `const float SnapPositionToClosestFrame(const float InPixelPosition) const;`
- L27 _public prototype_ `const int64 GetFramePositionFromRatio(double Ratio) const;`
- L28 _public prototype_ `const double GetRatioFromFramePosition(int64 FramePosition) const;`
- L29 _public prototype_ `const bool IsFramePositionInDisplayRange(int64 FramePosition) const;`
- L31 _public function_ `const TRange<uint32> GetDisplayRange()`
- L33 _public member_ `FOnWaveformEditorGridUpdated OnGridMetricsUpdated;`
- L36 _private member_ `FFixedSampledSequenceGridMetrics GridMetrics;`
- L37 _private member_ `uint32 TotalFrames = 0;`
- L38 _private member_ `TRange<uint32> DisplayRange;`
- L40 _private member_ `float GridSizePixels = 0.f;`
- L41 _private member_ `const FSlateFontInfo* TicksTimeFont = nullptr;`
- L42 _private member_ `FFrameRate GridFrameRate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWaveformEditorGridUpdated) struct FSlateFontInfo;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformEditorSequenceDataProvider.h` (Public)


#### class `FWaveformEditorSequenceDataProvider`  
`class FWaveformEditorSequenceDataProvider : public IFixedSampledSequenceViewProvider, public TSharedFromThis<FWaveformEditorSequenceDataProvider>`  
_L54-114_
- inherits: `IFixedSampledSequenceViewProvider,TSharedFromThis<FWaveformEditorSequenceDataProvider>`
- L58 _public prototype_ `FWaveformEditorSequenceDataProvider(TObjectPtr<USoundWave> InSoundWave);`
- L60 _public prototype_ `virtual FFixedSampledSequenceView RequestSequenceView(const TRange<double> DataRatioRange) override;`
- L64 _public prototype_ `void GenerateLayersChain();` — Should be called when the waveform transformation chain is changed
- L68 _public prototype_ `void UpdateRenderElements();` — Should be called when the transformations parameters are changed
- L70 _public prototype_ `TArrayView<const FTransformationRenderLayerInfo> GetTransformLayers() const;`
- L72 _public prototype_ `const TRange<double> GetTransformedWaveformBounds() const;`
- L74 _public function_ `const TArray<float>& GetTransformedPCMData() const`
- L77 _public member_ `FOnLayersChainGenerated OnLayersChainGenerated;` — Called when a new layer chain of transformations UI is created
- L80 _public member_ `FOnRenderElementsUpdated OnRenderElementsUpdated;` — Called when the different render elements are updated
- L83 _public member_ `FOnDataViewGenerated OnDataViewGenerated;` — Called when new data view is generated
- L86 _private prototype_ `void GenerateSequenceDataInternal();`
- L88 _private prototype_ `void UpdateTransformedWaveformBounds(const uint32 FirstEditedSample, const uint32 LastEditedSample, const uint32 NumOriginalSamples);`
- L90 _private prototype_ `void CreateDurationHighlightLayer();`
- L92 _private prototype_ `TArray<Audio::FTransformationPtr> CreateTransformations() const;`
- L93 _private prototype_ `const bool CanChainChangeFileLength(const TArray<Audio::FTransformationPtr>& TransformationArray) const;`
- L95 _private member_ `TArray<TObjectPtr<UWaveformTransformationBase>> TransformationsToRender;`
- L96 _private member_ `TArray<FTransformationRenderLayerInfo> RenderLayers;`
- L98 _private member_ `TObjectPtr<USoundWave> SoundWaveToRender = nullptr;`
- L101 _private member_ `TArray<uint8> ImportedRawPCMData;` — Imported Soundwave Data
- L102 _private member_ `uint16 ImportedNumChannels;`
- L103 _private member_ `uint32 ImportedSampleRate;`
- L105 _private member_ `TArray<float> TransformedPCMData;`
- L107 _private member_ `TUniquePtr<FWaveformTransformationRenderLayerFactory> LayersFactory = nullptr;`
- L108 _private member_ `TSharedPtr<FWaveformTransformationDurationRenderer> DurationHiglightLayer = nullptr;`
- L110 _private member_ `uint32 NumOriginalWaveformFrames = 0;`
- L113 _private member_ `TRange<double> TransformedWaveformBounds = TRange<double>::Inclusive(0, 1);` — The bounds of the transformed waveform in relation to the original

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`
- L18 _typedef_ `using FTransformationLayerConstraints = TPair<float, float>;`
- L19 _typedef_ `using FTransformationRenderLayerInfo = TPair<TSharedPtr<IWaveformTransformationRenderer>, FTransformationLayerConstraints>;`
- L20 _typedef_ `using FTransformationToPropertiesPair = TPair<TObjectPtr<UWaveformTransformationBase>, TArray<TSharedRef<IPropertyHandle>>>;`
- L21 _typedef_ `using FTransformationsToPropertiesArray = TArray<FTransformationToPropertiesPair>;`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTransformationsPropertiesRequired, FTransformationsToPropertiesArray& ) DECLARE_MULTICAST_DELEGATE(FOnRenderElementsUpdated) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDataViewGenerated, FFixedSampledSequenceView, const uint32 ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLayersChainGenerated, FTransformationRenderLayerInfo* , const int32 )`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRenderElementsUpdated) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDataViewGenerated, FFixedSampledSequenceView, const uint32 ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLayersChainGenerated, FTransformationRenderLayerInfo* , const int32 )`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDataViewGenerated, FFixedSampledSequenceView, const uint32 ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLayersChainGenerated, FTransformationRenderLayerInfo* , const int32 )`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLayersChainGenerated, FTransformationRenderLayerInfo* , const int32 )`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformEditorStyle.h` (Public)


#### class `FWaveformEditorStyle`  
`class FWaveformEditorStyle : public FSlateStyleSet`  
_L16-45_
- inherits: `FSlateStyleSet`
- L21 _public prototype_ `FWaveformEditorStyle();`
- L22 _public prototype_ `~FWaveformEditorStyle();`
- L24 _public member_ `static FName StyleName;`
- L27 _public prototype_ `static FWaveformEditorStyle& Get();` — Access the singleton instance for this style set
- L28 _public prototype_ `static void Init();`
- L30 _public member_ `static FOnNewPlayheadOverlayStyle OnNewPlayheadOverlayStyle;`
- L31 _public member_ `static FOnNewTimeRulerStyle OnNewTimeRulerStyle;`
- L32 _public member_ `static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle;`
- L33 _public member_ `static FOnNewWaveformViewerStyle OnNewWaveformViewerStyle;`
- L36 _private member_ `static TUniquePtr<FWaveformEditorStyle> StyleInstance;`
- L38 _private prototype_ `static const UWaveformEditorWidgetsSettings* GetWidgetsSettings();`
- L39 _private prototype_ `static void OnWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings);`
- L41 _private prototype_ `static FFixedSampleSequenceRulerStyle CreateTimeRulerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings);`
- L42 _private prototype_ `static FPlayheadOverlayStyle CreatePlayheadOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings);`
- L43 _private prototype_ `static FSampledSequenceValueGridOverlayStyle CreateValueGridOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings);`
- L44 _private prototype_ `static FSampledSequenceViewerStyle CreateWaveformViewerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings);`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewPlayheadOverlayStyle, FPlayheadOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewTimeRulerStyle, FFixedSampleSequenceRulerStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewValueGridOverlayStyle, FSampledSequenceValueGridOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) class FWaveformEditorStyle : public FSlateStyleSet { public: FWaveformEditorStyle(); ~FWaveformEditorStyle(); static FName StyleName; static FWaveformEditorStyle& Get(); static void Init(); static FOnNewPlayheadOverlayStyle OnNewPlayheadOverlayStyle; static FOnNewTimeRulerStyle OnNewTimeRulerStyle; static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle; static FOnNewWaveformViewerStyle OnNewWaveformViewerStyle; private: static TUniquePtr<FWaveformEditorStyle> StyleInstance; static const UWaveformEditorWidgetsSettings* GetWidgetsSettings(); static void OnWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings); static FFixedSampleSequenceRulerStyle CreateTimeRulerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FPlayheadOverlayStyle CreatePlayheadOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceValueGridOverlayStyle CreateValueGridOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceViewerStyle CreateWaveformViewerStyleFromSettings(const UWavef`
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewTimeRulerStyle, FFixedSampleSequenceRulerStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewValueGridOverlayStyle, FSampledSequenceValueGridOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) class FWaveformEditorStyle : public FSlateStyleSet { public: FWaveformEditorStyle(); ~FWaveformEditorStyle(); static FName StyleName; static FWaveformEditorStyle& Get(); static void Init(); static FOnNewPlayheadOverlayStyle OnNewPlayheadOverlayStyle; static FOnNewTimeRulerStyle OnNewTimeRulerStyle; static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle; static FOnNewWaveformViewerStyle OnNewWaveformViewerStyle; private: static TUniquePtr<FWaveformEditorStyle> StyleInstance; static const UWaveformEditorWidgetsSettings* GetWidgetsSettings(); static void OnWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings); static FFixedSampleSequenceRulerStyle CreateTimeRulerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FPlayheadOverlayStyle CreatePlayheadOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceValueGridOverlayStyle CreateValueGridOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceViewerStyle CreateWaveformViewerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); };`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewValueGridOverlayStyle, FSampledSequenceValueGridOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) class FWaveformEditorStyle : public FSlateStyleSet { public: FWaveformEditorStyle(); ~FWaveformEditorStyle(); static FName StyleName; static FWaveformEditorStyle& Get(); static void Init(); static FOnNewPlayheadOverlayStyle OnNewPlayheadOverlayStyle; static FOnNewTimeRulerStyle OnNewTimeRulerStyle; static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle; static FOnNewWaveformViewerStyle OnNewWaveformViewerStyle; private: static TUniquePtr<FWaveformEditorStyle> StyleInstance; static const UWaveformEditorWidgetsSettings* GetWidgetsSettings(); static void OnWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings); static FFixedSampleSequenceRulerStyle CreateTimeRulerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FPlayheadOverlayStyle CreatePlayheadOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceValueGridOverlayStyle CreateValueGridOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceViewerStyle CreateWaveformViewerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); };`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) class FWaveformEditorStyle : public FSlateStyleSet { public: FWaveformEditorStyle(); ~FWaveformEditorStyle(); static FName StyleName; static FWaveformEditorStyle& Get(); static void Init(); static FOnNewPlayheadOverlayStyle OnNewPlayheadOverlayStyle; static FOnNewTimeRulerStyle OnNewTimeRulerStyle; static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle; static FOnNewWaveformViewerStyle OnNewWaveformViewerStyle; private: static TUniquePtr<FWaveformEditorStyle> StyleInstance; static const UWaveformEditorWidgetsSettings* GetWidgetsSettings(); static void OnWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings); static FFixedSampleSequenceRulerStyle CreateTimeRulerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FPlayheadOverlayStyle CreatePlayheadOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceValueGridOverlayStyle CreateValueGridOverlayStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); static FSampledSequenceViewerStyle CreateWaveformViewerStyleFromSettings(const UWaveformEditorWidgetsSettings& InSettings); };`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformEditorWidgetsModule.h` (Public)


#### class `FWaveformEditorWidgetsModule`  
`class FWaveformEditorWidgetsModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformEditorZoomController.h` (Public)


#### class `FWaveformEditorZoomController`  
`class FWaveformEditorZoomController`  
_L16-54_
- L19 _public function_ `SLATE_BEGIN_ARGS(FWaveformEditorZoomController)`
- L24 _public prototype_ `FWaveformEditorZoomController(TSharedPtr<FSparseSampledSequenceTransportCoordinator> TransportCoordinator);`
- L26 _public prototype_ `void ZoomIn();`
- L27 _public prototype_ `bool CanZoomIn() const;`
- L28 _public prototype_ `void ZoomOut();`
- L29 _public prototype_ `bool CanZoomOut() const;`
- L30 _public prototype_ `void ZoomByDelta(const float Delta);`
- L32 _public prototype_ `float GetZoomRatio() const;`
- L34 _public prototype_ `void CheckBounds(const FGeometry& AllottedGeometry);`
- L35 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L36 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L37 _public prototype_ `FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L39 _public member_ `FOnZoomRatioChanged OnZoomRatioChanged;`
- L42 _private prototype_ `void ApplyZoom();`
- L43 _private prototype_ `float ConvertZoomLevelToLogRatio() const;`
- L45 _private member_ `float ZoomLevelInitValue = 1.f;`
- L46 _private member_ `float ZoomLevel = ZoomLevelInitValue;`
- L47 _private member_ `float ZoomLevelStep = 2.f;`
- L48 _private member_ `const uint32 LogRatioBase = 100;`
- L50 _private member_ `bool bIsScrolling = false;`
- L51 _private member_ `float LocalCursorXPosition = 0.0f;`
- L53 _private member_ `TSharedPtr<FSparseSampledSequenceTransportCoordinator> TransportController = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoomRatioChanged, const float );`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoomRatioChanged, const float );`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Public/WaveformTransformationRenderLayerFactory.h` (Public)


#### class `FWaveformTransformationRenderLayerFactory`  
`class FWaveformTransformationRenderLayerFactory`  
_L14-23_
- L17 _public prototype_ `~FWaveformTransformationRenderLayerFactory() = default;`
- L19 _public prototype_ `TSharedPtr<IWaveformTransformationRenderer> Create(TObjectPtr<UWaveformTransformationBase> InTransformationToRender);`
- L22 _public prototype_ `TSharedPtr<IWaveformTransformationRenderer> Create(TObjectPtr<UWaveformTransformationBase> InTransformationToRender, TArray<TSharedRef<IPropertyHandle>>& TransformationsProperties);` — `UE_DEPRECATED(5.7, "TransformationsProperties in Create has been deprecated.")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WAVEFORMEDITORWIDGETS_API`
