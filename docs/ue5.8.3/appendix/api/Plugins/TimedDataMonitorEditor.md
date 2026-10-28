# Plugins / TimedDataMonitorEditor

- module root: `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor`
- headers: 11; symbols: 275
- symbol kinds: class=12, enum=2, enumerator=5, function=35, macro=1, member=87, namespace=1, prototype=124, typedef=8
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, ContentBrowser, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, LiveLink, LiveLinkInterface, MessageLog, Projects, Settings, Slate, SlateCore, TimeManagement, TimedDataMonitor, UnrealEd, WorkspaceMenuStructure

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/SFrameTime.h` (Private)


#### class `SFrameTime`  
`class SFrameTime : public SLeafWidget`  
_L13-206_
- inherits: `SLeafWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SFrameTime) : _FillImage(FAppStyle::GetBrush(TEXT("WhiteBrush"))) , _BackgroundImage(&FCoreStyle::Get().GetWidgetStyle<FProgressBarStyle>("ProgressBar").BackgroundImage)`
- L22 _public function_ `SLATE_ARGUMENT(TOptional<double>, RefreshRate) SLATE_ARGUMENT(const FSlateBrush*, FillImage) SLATE_ARGUMENT(const FSlateBrush*, BackgroundImage) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L34 _public function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L55 _public function_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override`
- L159 _public function_ `virtual FVector2D ComputeDesiredSize(float) const override`
- L164 _public function_ `virtual bool ComputeVolatility() const override`
- L170 _public function_ `void SetPercent(float InPercent)` — See attribute Percent
- L180 _public function_ `bool PushTransformedClip(FSlateWindowElementList& OutDrawElements, const FGeometry& AllottedGeometry, FVector2D InsetPadding, FVector2D ProgressOrigin, FSlateRect Progress) const` — Returns false if the clipping zone area is zero in which case we should skip drawing
- L200 _public member_ `float CachedFPSFraction = 0.f;`
- L201 _public member_ `TAttribute<float> Percent = 0.f;`
- L202 _public member_ `const FSlateBrush* FillImage = nullptr;`
- L203 _public member_ `const FSlateBrush* BackgroundImage = nullptr;`
- L204 _public member_ `TOptional<double> RefreshRate;`
- L205 _public member_ `double LastUpdateTime = 0.0;`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimedDataGenlock.h` (Private)


#### class `STimedDataGenlock`  
`class STimedDataGenlock : public SCompoundWidget`  
_L13-47_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(STimedDataGenlock)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<STimedDataMonitorPanel> OwnerPanel);`
- L21 _public prototype_ `void RequestRefresh();`
- L22 _public prototype_ `void UpdateCachedValue(float InDeltaTime);`
- L25 _private prototype_ `FText GetStateText() const;`
- L26 _private prototype_ `FSlateColor GetStateColorAndOpacity() const;`
- L27 _private prototype_ `FText GetCustomTimeStepText() const;`
- L29 _private prototype_ `bool IsCustomTimeStepEnabled() const;`
- L30 _private prototype_ `float GetFPSFraction() const;`
- L32 _private function_ `FText GetFPSText() const`
- L33 _private function_ `FText GetDeltaTimeText() const`
- L34 _private function_ `FText GetIdleTimeText() const`
- L36 _private prototype_ `void ShowCustomTimeStepSetting(ECheckBoxState);`
- L37 _private prototype_ `void ReinitializeCustomTimeStep(ECheckBoxState);`
- L40 _private member_ `TWeakPtr<STimedDataMonitorPanel> OwnerPanel;`
- L42 _private member_ `ECustomTimeStepSynchronizationState CachedState;`
- L43 _private member_ `FText CachedCustomTimeStepText;`
- L44 _private member_ `FText CachedFPSText;`
- L45 _private member_ `FText CachedDeltaTimeText;`
- L46 _private member_ `FText CachedIdleTimeText;`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimedDataListView.h` (Private)


#### enum `ETimedDataInputEvaluationOffsetType`  
`enum class ETimedDataInputEvaluationOffsetType : uint8`  
_L22-28_
- reflection: `UENUM()`
- L25 _public enumerator_ `Seconds UMETA(DisplayName = "s")` — The input offset is specified in seconds.
- L27 _public enumerator_ `Frames UMETA(DisplayName = "f")` — The input offset is specified in frames.

#### class `STimedDataInputTableRow`  
`class STimedDataInputTableRow : public SMultiColumnTableRow<FTimedDataInputTableRowDataPtr>`  
_L40-89_
- inherits: `SMultiColumnTableRow<FTimedDataInputTableRowDataPtr>`
- L42 _private typedef_ `using Super = SMultiColumnTableRow<FTimedDataInputTableRowDataPtr>;`
- L45 _public function_ `SLATE_BEGIN_ARGS(STimedDataInputTableRow)`
- L46 _public prototype_ `SLATE_ARGUMENT(FTimedDataInputTableRowDataPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwerTableView, const TSharedRef<STimedDataInputListView>& OwnerTreeView);`
- L52 _public prototype_ `void UpdateCachedValue();`
- L55 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L57 _private prototype_ `ECheckBoxState GetEnabledCheckState() const;`
- L58 _private prototype_ `void OnEnabledCheckStateChanged(ECheckBoxState NewState);`
- L60 _private prototype_ `FText GetStateGlyphs() const;`
- L61 _private prototype_ `FSlateColor GetStateColorAndOpacity() const;`
- L63 _private prototype_ `FText GetDescription() const;`
- L64 _private prototype_ `double GetFloatEvaluationOffset() const;`
- L65 _private prototype_ `int32 GetIntEvaluationOffset() const;`
- L66 _private prototype_ `FText GetEvaluationOffsetText() const;`
- L67 _private prototype_ `void SetEvaluationOffset(double NewValue, ETextCommit::Type CommitType);`
- L68 _private prototype_ `void SetEvaluationOffset(int32 NewValue, ETextCommit::Type CommitType);`
- L69 _private prototype_ `int32 GetBufferSize() const;`
- L70 _private prototype_ `FText GetBufferSizeText() const;`
- L71 _private prototype_ `void SetBufferSize(int32 NewValue, ETextCommit::Type CommitType);`
- L72 _private prototype_ `bool CanEditBufferSize() const;`
- L73 _private prototype_ `int32 GetCurrentSampleCount() const;`
- L74 _private prototype_ `TSharedRef<SWidget> OnEvaluationImageBuildMenu();`
- L75 _private prototype_ `const FSlateBrush* GetEvaluationImage() const;`
- L76 _private prototype_ `void SetInputEvaluationType(ETimedDataInputEvaluationType EvaluationType);`
- L79 _private prototype_ `FText GetBufferUnderflowCount() const;` — Queries about buffer stats to display
- L80 _private prototype_ `FText GetBufferOverflowCount() const;`
- L81 _private prototype_ `FText GetFrameDroppedCount() const;`
- L83 _private prototype_ `void OnEvaluationOffsetTypeChanged(int32 NewValue, ESelectInfo::Type);`
- L86 _private member_ `FTimedDataInputTableRowDataPtr Item;`
- L87 _private member_ `TSharedPtr<STimedDataInputListView> OwnerTreeView;`
- L88 _private member_ `TSharedPtr<STimingDiagramWidget> DiagramWidget;`

#### class `STimedDataInputListView`  
`class STimedDataInputListView : public STreeView<FTimedDataInputTableRowDataPtr>`  
_L95-132_
- inherits: `STreeView<FTimedDataInputTableRowDataPtr>`
- L97 _private typedef_ `using Super = STreeView<FTimedDataInputTableRowDataPtr>;`
- L100 _public function_ `SLATE_BEGIN_ARGS(STimedDataInputListView)`
- L101 _public prototype_ `SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<STimedDataMonitorPanel> OwnerPanel);`
- L105 _public prototype_ `virtual ~STimedDataInputListView();`
- L107 _public prototype_ `void RequestRefresh();`
- L108 _public prototype_ `void UpdateCachedValue();`
- L109 _public prototype_ `void MarkSettingsDirty();`
- L111 _public prototype_ `FTimedDataMonitorInputIdentifier GetSelectedInputIdentifier() const;`
- L114 _private prototype_ `void RequestRebuildSources();`
- L115 _private prototype_ `void RebuildSources();`
- L117 _private prototype_ `ECheckBoxState GetAllEnabledCheckState() const;`
- L118 _private prototype_ `void OnToggleAllEnabledCheckState(ECheckBoxState CheckBoxState);`
- L119 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FTimedDataInputTableRowDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L120 _private prototype_ `void ReleaseListViewWidget(const TSharedRef<ITableRow>& Row);`
- L121 _private prototype_ `void GetChildrenForInfo(FTimedDataInputTableRowDataPtr InItem, TArray<FTimedDataInputTableRowDataPtr>& OutChildren);`
- L122 _private prototype_ `void OnSelectionChanged(FTimedDataInputTableRowDataPtr InItem, ESelectInfo::Type SelectInfo);`
- L123 _private prototype_ `bool OnIsSelectableOrNavigable(FTimedDataInputTableRowDataPtr InItem) const;`
- L127 _private member_ `TWeakPtr<STimedDataMonitorPanel> OwnerPanel;`
- L129 _private member_ `TArray<FTimedDataInputTableRowDataPtr> ListItemsSource;`
- L130 _private member_ `TArray<TWeakPtr<STimedDataInputTableRow>> ListRowWidgets;`
- L131 _private member_ `bool bRebuildListRequested = true;`

#### Free symbols / members of external scopes

- L34 _typedef_ `using FTimedDataInputTableRowDataPtr = TSharedPtr<FTimedDataInputTableRowData>;`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimedDataMonitorBufferVisualizer.h` (Private)


#### class `STimedDataMonitorBufferVisualizer`  
`class STimedDataMonitorBufferVisualizer : public SCompoundWidget`  
_L16-45_
- inherits: `SCompoundWidget`
- desc: Implements the contents of the viewer tab in the TimecodeSynchronizer editor.
- L19 _private typedef_ `using Super = SCompoundWidget;`
- L22 _public function_ `SLATE_BEGIN_ARGS(STimedDataMonitorBufferVisualizer)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `virtual ~STimedDataMonitorBufferVisualizer();`
- L29 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _private prototype_ `void RequestRefresh();`
- L33 _private prototype_ `void RebuiltListItemsSource();`
- L34 _private prototype_ `TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FTimedDataMonitorBuffervisualizerItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L35 _private prototype_ `void ReleaseListViewWidget(const TSharedRef<ITableRow>&);`
- L38 _private member_ `TSharedPtr<STimedDataMonitorBufferVisualizerListView> ListViewWidget;`
- L39 _private member_ `TArray<TWeakPtr<STimedDataMonitorBufferVisualizerRow>> ListRowWidgets;`
- L40 _private member_ `TArray<TSharedPtr<FTimedDataMonitorBuffervisualizerItem>> ListItemsSource;`
- L43 _private member_ `double LastRefreshPlatformSeconds = 0.0;`
- L44 _private member_ `bool bRefreshRequested = true;`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimedDataMonitorPanel.h` (Private)


#### class `STimedDataMonitorPanel`  
`class STimedDataMonitorPanel : public SCompoundWidget`  
_L30-125_
- inherits: `SCompoundWidget`
- L33 _public prototype_ `static void RegisterNomadTabSpawner(TSharedPtr<FTabManager> TabManager, TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L34 _public prototype_ `static void UnregisterNomadTabSpawner(TSharedPtr<FTabManager> TabManager);`
- L35 _public prototype_ `static TSharedPtr<STimedDataMonitorPanel> GetPanelInstance();`
- L36 _public member_ `static const FName TabName;`
- L39 _private typedef_ `using Super = SCompoundWidget;`
- L40 _private member_ `static TWeakPtr<STimedDataMonitorPanel> WidgetInstance;`
- L43 _public function_ `SLATE_BEGIN_ARGS(STimedDataMonitorPanel)`
- L44 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L50 _public function_ `void RequestRefresh()`
- L53 _public function_ `void MarkSettingsDirty()` — Flags that monitored input settings have been modified and need saving.
- L59 _private prototype_ `FReply OnCalibrateClicked();`
- L60 _private prototype_ `TSharedRef<SWidget> OnCalibrateBuildMenu();`
- L61 _private prototype_ `FText GetCalibrateButtonTooltip() const;`
- L62 _private prototype_ `const FSlateBrush* GetCalibrateButtonImage() const;`
- L63 _private prototype_ `FText GetCalibrateButtonText() const;`
- L64 _private prototype_ `FReply OnResetErrorsClicked();`
- L65 _private prototype_ `TSharedRef<SWidget> OnResetBuildMenu();`
- L66 _private prototype_ `void OnResetBufferStatClicked();`
- L67 _private prototype_ `bool IsResetBufferStatChecked() const;`
- L68 _private prototype_ `void OnClearMessageClicked();`
- L69 _private prototype_ `bool IsClearMessageChecked() const;`
- L70 _private prototype_ `void OnResetAllEvaluationTimeClicked();`
- L71 _private prototype_ `bool IsResetEvaluationChecked() const;`
- L72 _private prototype_ `FReply OnShowBuffersClicked();`
- L73 _private prototype_ `FReply OnGeneralUserSettingsClicked();`
- L74 _private prototype_ `FSlateColor GetEvaluationStateColorAndOpacity() const;`
- L75 _private prototype_ `FText GetEvaluationStateText() const;`
- L76 _private prototype_ `TSharedPtr<SWidget> OnDataListConstructContextMenu();`
- L77 _private prototype_ `bool IsSourceListSectionValid() const;`
- L78 _private prototype_ `void ApplyTimeCorrectionOnSelection();`
- L79 _private prototype_ `void ResetTimeCorrectionOnSelection();`
- L81 _private prototype_ `EVisibility ShowMessageLog() const;`
- L82 _private prototype_ `EVisibility ShowEditorPerformanceThrottlingWarning() const;`
- L83 _private prototype_ `FReply DisableEditorPerformanceThrottling();`
- L85 _private prototype_ `EVisibility GetThrobberVisibility() const;`
- L87 _private prototype_ `void BuildCalibrationArray();`
- L88 _private prototype_ `void CalibrateWithTimecode();`
- L89 _private prototype_ `void CalibrateWithTimecodeCompleted(FTimedDataMonitorCalibrationResult);`
- L90 _private prototype_ `void ApplyTimeCorrectionAll();`
- L91 _private prototype_ `ETimedDataMonitorTimeCorrectionReturnCode ApplyTimeCorrection(const FTimedDataMonitorInputIdentifier& InputIndentifier);`
- L92 _private prototype_ `FReply OnCancelCalibration();`
- L95 _private prototype_ `FReply OnSavePreset();` — Saves the tracked preset and modified input settings, or falls back to Save As if no preset is tracked.
- L97 _private prototype_ `void OnSaveAsPreset();` — Opens a Save As dialog to create a new Live Link preset and saves all input settings.
- L99 _private prototype_ `void CollectInputSettingsPackages(TArray<UPackage*>& OutPackages);` — Collects packages from all monitored inputs that have a settings object (e.g. media sources).
- L101 _private prototype_ `const FSlateBrush* GetSaveButtonBrush() const;` — Returns Icons.SaveChanged when dirty, Icons.Save otherwise.
- L103 _private prototype_ `FLiveLinkClient* GetLiveLinkClient() const;` — Returns the Live Link client from modular features, or nullptr.
- L106 _private member_ `TSharedPtr<STimedDataGenlock> TimedDataGenlockWidget;`
- L107 _private member_ `TSharedPtr<STimedDataTimecodeProvider> TimedDataTimecodeWidget;`
- L108 _private member_ `TSharedPtr<STimedDataInputListView> TimedDataSourceList;`
- L109 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`
- L111 _private member_ `static const int32 CalibrationArrayCount = (int32)ETimedDataMonitorEditorCalibrationType::Max;`
- L112 _private member_ `FUIAction CalibrationUIAction[CalibrationArrayCount];`
- L113 _private member_ `FSlateIcon CalibrationSlateIcon[CalibrationArrayCount];`
- L114 _private member_ `FText CalibrationName[CalibrationArrayCount];`
- L115 _private member_ `FText CalibrationTooltip[CalibrationArrayCount];`
- L117 _private member_ `ETimedDataMonitorEvaluationState CachedGlobalEvaluationState;`
- L119 _private member_ `TUniquePtr<FTimedDataMonitorCalibration> MonitorCalibration;`
- L121 _private member_ `bool bRefreshRequested = true;`
- L123 _private member_ `bool bSettingsDirty = false;` — True when monitored input settings have been modified since last save.
- L124 _private member_ `double LastCachedValueUpdateTime = 0.0;`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimedDataNumericEntryBox.h` (Private)


#### class `STimedDataNumericEntryBox`  
`template<class NumericType> class STimedDataNumericEntryBox : public SCompoundWidget`  
_L16-369_
- inherits: `SCompoundWidget`
- L19 _private typedef_ `using Super = SCompoundWidget;`
- L20 _private typedef_ `using FOnValueCommitted = typename SNumericEntryBox<NumericType>::FOnValueCommitted;`
- L23 _public function_ `SLATE_BEGIN_ARGS(STimedDataNumericEntryBox) : _Value(0) , _SuffixWidget(SNullWidget::NullWidget) , _CanEdit(true) , _Amount(0) , _ShowAmount(false) , _TextStyle(&FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>(TEXT("NormalText"))) , _ComboButton(true) , _ControlModifierOffset(10)`
- L45 _public prototype_ `SLATE_ATTRIBUTE(NumericType, Value) SLATE_ARGUMENT(TOptional<NumericType>, MinValue) SLATE_ARGUMENT(TOptional<NumericType>, MaxValue) SLATE_ARGUMENT(FText, EditLabel) SLATE_ARGUMENT(TSharedRef<SWidget>, SuffixWidget) SLATE_ARGUMENT(bool, CanEdit);`
- L51 _public prototype_ `SLATE_ATTRIBUTE(NumericType, Amount);`
- L52 _public prototype_ `SLATE_ARGUMENT(bool, ShowAmount);`
- L64 _public function_ `void Construct(const FArguments& InArgs)`
- L166 _private function_ `FText GetValueText() const`
- L178 _private function_ `TSharedRef<SWidget> OnCreateEditMenu()`
- L257 _private function_ `void CloseComboButton(ECheckBoxState InNewState)`
- L265 _private function_ `void OnValueCommittedCallback(NumericType NewValue, ETextCommit::Type CommitType)`
- L290 _private function_ `FReply OnMinusClicked()`
- L308 _private function_ `FReply OnPlusClicked()`
- L325 _private function_ `NumericType GetModifierKeyOffset() const`
- L350 _private member_ `TAttribute<NumericType> Value;`
- L351 _private member_ `TAttribute<NumericType> Amount;`
- L352 _private member_ `NumericType CachedValue;`
- L353 _private member_ `TSharedPtr<SNumericEntryBox<NumericType>> EntryBox;`
- L354 _private member_ `TOptional<NumericType> MinValue;`
- L355 _private member_ `TOptional<NumericType> MaxValue;`
- L356 _private member_ `FText EditLabel;`
- L357 _private member_ `TSharedRef<SWidget> SuffixWidget = SNullWidget::NullWidget;`
- L358 _private member_ `bool bShowAmount;`
- L359 _private member_ `FOnValueCommitted OnValueCommitted;`
- L360 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L361 _private member_ `bool bComboButton = true;`
- L362 _private member_ `bool bCloseRequested = false;`
- L363 _private member_ `TSharedPtr<SWidget> EditMenuContent;`
- L364 _private member_ `NumericType AltOffset;`
- L365 _private member_ `NumericType ShiftOffset;`
- L366 _private member_ `NumericType ControlOffset;`
- L367 _private member_ `TAttribute<FText> MinusButtonToolTip;`
- L368 _private member_ `TAttribute<FText> PlusButtonToolTip;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "TimeDataNumericEntryBox"`
- L208 _function_ `` (scope `STimedDataNumericEntryBox::OnCreateEditMenu`)
- L286 _function_ `GEditor->GetTimerManager()->SetTimer(Handle, [this](){ FSlateApplication::Get().SetKeyboardFocus(EntryBox); }, InRate, InbLoop);` (scope `STimedDataNumericEntryBox::OnValueCommittedCallback`)

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimedDataTimecodeProvider.h` (Private)


#### class `STimedDataTimecodeProvider`  
`class STimedDataTimecodeProvider : public SCompoundWidget`  
_L16-52_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(STimedDataTimecodeProvider)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<STimedDataMonitorPanel> OwnerPanel);`
- L24 _public prototype_ `void RequestRefresh();`
- L25 _public prototype_ `void UpdateCachedValue();`
- L29 _private prototype_ `FText GetStateText() const;`
- L30 _private prototype_ `FSlateColor GetStateColorAndOpacity() const;`
- L31 _private function_ `FText GetTimecodeProviderText() const`
- L32 _private function_ `FText GetTimecodeText() const`
- L33 _private function_ `FText GetSystemTimeText() const`
- L34 _private prototype_ `FText GetTooltipText() const;`
- L36 _private prototype_ `float GetTimecodeFrameDelay() const;`
- L37 _private prototype_ `void SetTimecodeFrameDelay(float Offset, ETextCommit::Type);`
- L38 _private prototype_ `bool IsTimecodeOffsetEnabled() const;`
- L40 _private prototype_ `void ShowTimecodeProviderSetting(ECheckBoxState);`
- L41 _private prototype_ `void ReinitializeTimecodeProvider(ECheckBoxState);`
- L44 _private member_ `TWeakPtr<STimedDataMonitorPanel> OwnerPanel;`
- L46 _private member_ `FText CachedTimecode;`
- L47 _private member_ `FText CachedSystemTime;`
- L48 _private member_ `FText CachedTimecodeProvider;`
- L49 _private member_ `TOptional<FQualifiedFrameTime> CachedFrameTimeOptional;`
- L50 _private member_ `double CachedPlatformSeconds;`
- L51 _private member_ `ETimecodeProviderSynchronizationState CachedState;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ETextCommit`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/STimingDiagramWidget.h` (Private)


#### class `STimingDiagramWidget`  
`class STimingDiagramWidget : public SCompoundWidget`  
_L14-53_
- inherits: `SCompoundWidget`
- L17 _private typedef_ `using Super = SCompoundWidget;`
- L20 _public function_ `SLATE_BEGIN_ARGS(STimingDiagramWidget) : _ShowFurther(false) , _ShowMean(true) , _ShowSigma(false) , _ShowSnapshot(false) , _UseNiceBrush(false) , _SizePerSeconds(100)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, bool bIsInput);`
- L41 _public prototype_ `void UpdateCachedValue();`
- L44 _private prototype_ `FText GetTooltipText() const;`
- L45 _private prototype_ `void UpdateSampleTimes(const TArray<FTimedDataChannelSampleTime>& FrameDataTimes, ETimedDataInputEvaluationType EvaluationType);`
- L49 _private member_ `TSharedPtr<STimingDiagramWidgetGraphic> GraphicWidget;` — Identifier of the channel this widget is associated to
- L50 _private member_ `FTimedDataMonitorChannelIdentifier ChannelIdentifier;`
- L51 _private member_ `FTimedDataMonitorInputIdentifier InputIdentifier;`
- L52 _private member_ `bool bIsInput;`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/TimedDataMonitorEditorSettings.h` (Private)


#### enum `ETimedDataMonitorEditorCalibrationType`  
`enum class ETimedDataMonitorEditorCalibrationType`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `CalibrateWithTimecode = 0`
- L15 _public enumerator_ `TimeCorrection = 1`
- L16 _public enumerator_ `Max = 2`

#### class `UTimedDataMonitorEditorSettings`  
`class UTimedDataMonitorEditorSettings : public UObject`  
_L21-100_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UObject`
- L28 _public member_ `FTimedDataMonitorCalibrationParameters CalibrationSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Calibration")` — Option to use when calibrating from the UI.
- L32 _public member_ `FTimedDataMonitorTimeCorrectionParameters TimeCorrectionSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Calibration")` — Option to use when calibrating from the UI.
- L36 _public member_ `float RefreshRate = 0.2f;` — `UPROPERTY(Config, EditAnywhere, Category ="UI", meta=(ClampMin=0.0f))` — At which speed we should update the Timed Data Monitor UI.
- L40 _public member_ `bool bDrawFrameTimesInBufferVisualization = true;` — `UPROPERTY(Config, EditAnywhere, Category = "UI")` — Whether or not to draw vertical bars delineating each frame in the buffer of a channel
- L44 _public member_ `bool bUseAccurateFrameTimesInBufferVisualization = false;` — `UPROPERTY(Config, EditAnywhere, Category = "UI", meta = (EditCondition = "bDrawFrameTimesInBufferVisualization"))` — If true, accurate world times will be used to draw frame times. If false, a constant frame interval is used
- L47 _public member_ `bool bOverrideNumberOfStandardDeviationToShow;` — `UPROPERTY(Config, AdvancedDisplay, EditAnywhere, Category = "UI", meta = (InlineEditConditionToggle = true))`
- L54 _public member_ `int32 OverrideNumberOfStandardDeviationToShow = 5;` — `UPROPERTY(Config, AdvancedDisplay, EditAnywhere, Category = "UI", meta = (ClampMin = 0, ClampMax = 5, EditCondition = "bOverrideNumberOfStandardDeviationToShow"))` — When displaying the buffer widget, how many STD should we show. By default, it will show the value used for Calibration or Time Correction.
- L60 _public member_ `double FrameTimeWarnThreshold = 0.85;` — `UPROPERTY(Config, EditAnywhere, Category = "UI", meta = (ClampMin = 0, ClampMax = 2))` — The threshold at which to display the frame time as orange.
- L66 _public member_ `double TargetFrameTimePercent = 0.8;` — `UPROPERTY(Config, EditAnywhere, Category = "UI", meta = (ClampMin = 0, ClampMax = 1))` — The percent at which to display the target frame time in the frame time indicator.
- L69 _public member_ `ETimedDataMonitorEditorCalibrationType LastCalibrationType = ETimedDataMonitorEditorCalibrationType::CalibrateWithTimecode;` — `UPROPERTY(Config)`
- L73 _public member_ `bool bResetBufferStatEnabled = true;` — `UPROPERTY(Config, EditAnywhere, Category = "UI|Reset")` — The Reset button will reset the buffer errors count.
- L77 _public member_ `bool bClearMessageEnabled = true;` — `UPROPERTY(Config, EditAnywhere, Category = "UI|Reset")` — The Reset button will clear the messages list.
- L81 _public member_ `bool bResetEvaluationTimeEnabled = false;` — `UPROPERTY(Config, EditAnywhere, Category = "UI|Reset")` — The Reset button will set the evaluation time of all input to 0.
- L84 _public function_ `int32 GetNumberOfStandardDeviationForUI() const`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/TimedDataMonitorEditorStyle.h` (Private)


#### class `FTimedDataMonitorEditorStyle`  
`class FTimedDataMonitorEditorStyle : public FSlateStyleSet`  
_L10-23_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the monitor UI
- L14 _public prototype_ `static FTimedDataMonitorEditorStyle& Get();` — Access the singleton instance for this style set
- L16 _public member_ `static const FName NAME_TimecodeBrush;`
- L17 _public member_ `static const FName NAME_PlatformTimeBrush;`
- L18 _public member_ `static const FName NAME_NoEvaluationBrush;`
- L21 _private prototype_ `FTimedDataMonitorEditorStyle();`
- L22 _private prototype_ `~FTimedDataMonitorEditorStyle();`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Public/TimedDataMonitorEditorModule.h` (Public)


#### class `FTimedDataMonitorEditorModule`  
`class FTimedDataMonitorEditorModule : public IModuleInterface`  
_L12-27_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `void RegisterNomadTabSpawner(TSharedPtr<FTabManager> TabManager);` — Register a tab spawner for the TimedDataMonitorPanel.
- L21 _public prototype_ `void UnregisterNomadTabSpawner(TSharedPtr<FTabManager> TabManager);` — Unregister a tab spawner for the TimedDataMonitorPanel.
- L23 _public prototype_ `void DisplayTimedDataMonitorPanel(TSharedPtr<FTabManager> TabManager);` — Try invoking the TimedDataMonitor tab.
- L26 _private member_ `FDelegateHandle LevelEditorTabManagerChangedHandle;` — Handle to the delegate used to register the tab spawner when the level editor tab manager changes.
