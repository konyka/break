# Developer / LogVisualizer

- module root: `Source/Developer/LogVisualizer`
- headers: 33; symbols: 782
- symbol kinds: class=28, delegate=25, function=107, macro=8, member=239, prototype=348, struct=19, typedef=8
- DynamicallyLoadedModuleNames: DesktopPlatform, MainFrame
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, EditorFramework, Engine, InputCore, Json, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: DesktopPlatform
- PublicIncludePathModuleNames: WorkspaceMenuStructure

### `Source/Developer/LogVisualizer/Internal/LogVisualizerStyle.h` (Internal)


#### class `FLogVisualizerStyle`  
`class FLogVisualizerStyle`  
_L14-26_
- desc: Implements the visual style of LogVisualizer.
- L17 _public prototype_ `static void Initialize();`
- L18 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `static const ISlateStyle& Get();`
- L20 _public prototype_ `static FName GetStyleSetName();`
- L23 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L25 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LOGVISUALIZER_API`

### `Source/Developer/LogVisualizer/Internal/SVisualLoggerTableRow.h` (Internal)


#### class `SVisualLoggerTableRow`  
`class SVisualLoggerTableRow : public SMultiColumnTableRow<TSharedPtr<FLogEntryItem>>`  
_L13-71_
- inherits: `SMultiColumnTableRow<TSharedPtr<FLogEntryItem>>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerTableRow)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(FText, FilterText) SLATE_END_ARGS() static const FLazyName ColumnId_CategoryLabel;`
- L23 _public member_ `static const FLazyName ColumnId_VerbosityLabel;`
- L24 _public member_ `static const FLazyName ColumnId_LogLabel;`
- L26 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<FLogEntryItem> InEntryItem)`
- L33 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L63 _public function_ `FText GetFilterText() const`
- L69 _private member_ `TAttribute<FText> FilterText;`
- L70 _private member_ `TSharedPtr<FLogEntryItem> Item;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LOGVISUALIZER_API`

### `Source/Developer/LogVisualizer/Internal/VisualLoggerTypes.h` (Internal)


#### struct `FLogEntryItem`  
`struct FLogEntryItem`  
_L8-16_
- L10 _public member_ `FString Category;`
- L11 _public member_ `FLinearColor CategoryColor = FLinearColor::White;`
- L12 _public member_ `ELogVerbosity::Type Verbosity = ELogVerbosity::Log;`
- L13 _public member_ `FString Line;`
- L14 _public member_ `int64 UserData = 0;`
- L15 _public member_ `FName TagName = NAME_None;`

### `Source/Developer/LogVisualizer/Private/LogVisualizer.h` (Private)
_(no declarations extracted)_

### `Source/Developer/LogVisualizer/Private/SVisualLogger.h` (Private)


#### class `SVisualLogger`  
`class SVisualLogger : public SCompoundWidget`  
_L24-160_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SVisualLogger)`
- L36 _public prototype_ `SVisualLogger();` — Default constructor.
- L37 _public prototype_ `virtual ~SVisualLogger();`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);` — Constructs the application. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed.
- L51 _public prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier) const;`
- L52 _public prototype_ `static void FillWindowMenu(FMenuBuilder& MenuBuilder, const TSharedPtr<FTabManager> TabManager);`
- L55 _public prototype_ `void HandleMajorTabPersistVisualState();` — Callback for for when the owner tab's visual state is being persisted.
- L56 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L58 _public prototype_ `void OnNewLogEntry(const FVisualLogDevice::FVisualLogEntryItem& Entry);`
- L59 _public prototype_ `void OnFiltersChanged();`
- L60 _public prototype_ `void OnObjectSelectionChanged(const TArray<FName>& RowNames);`
- L61 _public prototype_ `void OnItemsSelectionChanged(const FVisualLoggerDBRow&, int32);`
- L62 _public prototype_ `void OnNewItemHandler(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L63 _public prototype_ `void UpdateVisibilityForEntry(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L64 _public prototype_ `void OnScrubPositionChanged(double NewScrubPosition, bool bScrubbing);`
- L66 _public prototype_ `void OnFiltersSearchChanged(const FText& Filter);`
- L67 _public prototype_ `void OnLogLineSelectionChanged(TSharedPtr<struct FLogEntryItem> SelectedItem, int64 UserData, FName TagName);`
- L68 _public prototype_ `FReply OnKeyboardRedirection(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L71 _public prototype_ `bool HandleStartRecordingCommandCanExecute() const;`
- L72 _public prototype_ `void HandleStartRecordingCommandExecute();`
- L73 _public prototype_ `bool HandleStartRecordingCommandIsVisible() const;`
- L75 _public prototype_ `bool HandleStopRecordingCommandCanExecute() const;`
- L76 _public prototype_ `void HandleStopRecordingCommandExecute();`
- L77 _public prototype_ `bool HandleStopRecordingCommandIsVisible() const;`
- L79 _public prototype_ `bool HandlePauseCommandCanExecute() const;`
- L80 _public prototype_ `void HandlePauseCommandExecute();`
- L81 _public prototype_ `bool HandlePauseCommandIsVisible() const;`
- L83 _public prototype_ `bool HandleResumeCommandCanExecute() const;`
- L84 _public prototype_ `void HandleResumeCommandExecute();`
- L85 _public prototype_ `bool HandleResumeCommandIsVisible() const;`
- L87 _public prototype_ `bool HandleLoadCommandCanExecute() const;`
- L88 _public prototype_ `void HandleLoadCommandExecute();`
- L90 _public prototype_ `void HandleAutoScrollCommandExecute();`
- L91 _public prototype_ `bool HandleAutoScrollIsChecked() const;`
- L93 _public prototype_ `bool HandleSaveCommandCanExecute() const;`
- L94 _public prototype_ `void HandleSaveCommandExecute();`
- L96 _public prototype_ `void HandleSaveAllCommandExecute();`
- L98 _public prototype_ `void HandleSaveCommand(bool bSaveAllData);`
- L100 _public prototype_ `bool HandleRefreshCommandCanExecute() const;`
- L101 _public prototype_ `void HandleRefreshCommandExecute();`
- L103 _public prototype_ `bool HandleCameraCommandCanExecute() const;`
- L104 _public prototype_ `void HandleCameraCommandExecute();`
- L105 _public prototype_ `bool HandleCameraCommandIsChecked() const;`
- L107 _public function_ `TSharedPtr<SVisualLoggerFilters> GetVisualLoggerFilters()`
- L108 _public prototype_ `void HandleTabManagerPersistLayout(const TSharedRef<FTabManager::FLayout>& LayoutToSave);`
- L110 _public prototype_ `void OnNewWorld(UWorld* NewWorld);`
- L112 _public prototype_ `void OnLevelActorAdded(AActor* Actor);`
- L113 _public prototype_ `void OnLevelActorDeleted(AActor* Actor);`
- L114 _public prototype_ `void OnActorMoved(AActor* Actor);`
- L116 _public prototype_ `void OnSettingsChanged(FName PropertyName);`
- L118 _public prototype_ `void ResetData();`
- L121 _protected prototype_ `void CollectFilterVolumes();`
- L122 _protected prototype_ `void ProcessFilterVolumes();`
- L125 _protected member_ `TSharedRef<FUICommandList> CommandList;` — Holds the list of UI commands.
- L128 _protected member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L131 _protected member_ `TSharedPtr<FVisualLogDevice> InternalDevice;` — Visual Logger device to get and collect logs.
- L133 _protected member_ `TWeakObjectPtr<class AVisualLoggerCameraController> CameraController;`
- L134 _protected member_ `TSharedPtr<struct FVisualLoggerCanvasRenderer> VisualLoggerCanvasRenderer;`
- L136 _protected member_ `mutable TSharedPtr<SVisualLoggerFilters> VisualLoggerFilters;`
- L137 _protected member_ `mutable TSharedPtr<SVisualLoggerView> MainView;`
- L138 _protected member_ `mutable TSharedPtr<SVisualLoggerLogsList> LogsList;`
- L139 _protected member_ `mutable TSharedPtr<SVisualLoggerStatusView> StatusView;`
- L141 _protected member_ `bool bPausedLogger;`
- L142 _protected member_ `TArray<FVisualLogDevice::FVisualLogEntryItem> OnPauseCacheForEntries;`
- L144 _protected member_ `bool bGotHistogramData;`
- L147 _protected member_ `bool bAutoScrollToLastItem;` — Instructs the visual logger to always scrub to the last item
- L149 _protected member_ `mutable bool bAutoScrollingToLastItem;` — Guard value that prevents canceling bAutoScrollToLastItem when we're actually auto-scrubbing (instead of manually scrubbing)
- L152 _protected member_ `FDelegateHandle PostWorldInitializationHandle;`
- L155 _protected member_ `FDelegateHandle DrawOnCanvasDelegateHandle;`
- L156 _protected member_ `TWeakObjectPtr<class UWorld> LastUsedWorld;`
- L159 _protected member_ `TArray<FBox> FilterBoxes;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerBaseWidget.h` (Private)


#### class `SVisualLoggerBaseWidget`  
`class SVisualLoggerBaseWidget : public SCompoundWidget`  
_L13-21_
- inherits: `SCompoundWidget`
- L16 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L17 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerFilterCheckBox.h` (Private)


#### class `SVisualLoggerFilterCheckBox`  
`class SVisualLoggerFilterCheckBox : public SCheckBox`  
_L10-50_
- inherits: `SCheckBox`
- desc: A class for check boxes in the filter list. If you double click a filter check box, you will enable it and disable all others
- L13 _public function_ `void SetOnFilterDoubleClicked(const FOnClicked& NewFilterDoubleClicked)`
- L18 _public function_ `void SetOnFilterMiddleButtonClicked(const FOnClicked& NewFilterMiddleButtonClicked)`
- L23 _public function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L35 _public function_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L48 _private member_ `FOnClicked OnFilterDoubleClicked;`
- L49 _private member_ `FOnClicked OnFilterMiddleButtonClicked;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerFilterWidget.h` (Private)


#### class `SVisualLoggerFilterWidget`  
`class SVisualLoggerFilterWidget : public SCompoundWidget`  
_L17-177_
- inherits: `SCompoundWidget`
- desc: A single filter in the filter list. Can be removed by clicking the remove button on it.
- L20 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFilterRequest, const TSharedRef<SVisualLoggerFilterWidget>&);`
- L21 _public prototype_ `DECLARE_DELEGATE(FOnSimpleRequest);`
- L23 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerFilterWidget)`
- L25 _public prototype_ `SLATE_ARGUMENT(FName, FilterName) SLATE_ARGUMENT(FLinearColor, ColorCategory) SLATE_EVENT(FOnSimpleRequest, OnFilterChanged) SLATE_EVENT(FOnFilterRequest, OnRequestRemove) SLATE_EVENT(FOnFilterRequest, OnRequestEnableOnly) SLATE_EVENT(FOnSimpleRequest, OnRequestDisableAll) SLATE_EVENT(FOnSimpleRequest, OnRequestRemoveAll) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — If this is an front end filter, this is the filter object
- L44 _public prototype_ `FText GetCaptionString() const;` — Caption String getter
- L46 _public prototype_ `FText GetTooltipString() const;` — Tool Tip string getter
- L49 _public prototype_ `void SetEnabled(bool InEnabled);` — Sets whether or not this filter is applied to the combined filter
- L52 _public prototype_ `bool IsEnabled() const;` — Returns true if this filter contributes to the combined filter
- L54 _public function_ `FORCEINLINE FName GetFilterName() const`
- L57 _public function_ `FORCEINLINE FString GetFilterNameAsString() const` — Returns the display name for this filter
- L68 _public function_ `void SetBorderBackgroundColor(FLinearColor InColor)`
- L72 _private prototype_ `void FilterToggled(ECheckBoxState NewState);` — Handler for when the filter checkbox is clicked
- L75 _private function_ `FReply FilterDoubleClicked()` — Handler for when the filter checkbox is double clicked
- L85 _private function_ `FReply FilterMiddleButtonClicked()` — Handler for when the filter checkbox is middle button clicked
- L92 _private prototype_ `TSharedRef<SWidget> GetRightClickMenuContent();` — Handler to create a right click menu
- L95 _private prototype_ `void SetVerbosityFilter(int32 SelectedVerbosityIndex);` — Removes this filter from the filter list
- L97 _private prototype_ `void DisableAllButThis();`
- L99 _private prototype_ `void EnableAllCategories();`
- L101 _private function_ `void RemoveFilter()`
- L108 _private function_ `void EnableOnly()` — Enables only this filter from the filter list
- L115 _private function_ `void DisableAllFilters()` — Disables all active filters in the list
- L118 _private function_ `void RemoveAllFilters()` — Removes all filters in the list
- L121 _private function_ `ECheckBoxState IsChecked() const` — Handler to determine the "checked" state of the filter checkbox
- L124 _private function_ `FSlateColor GetFilterForegroundColor() const` — Handler to determine the color of the checkbox when it is checked
- L127 _private function_ `FMargin GetFilterNamePadding() const` — Handler to determine the padding of the checkbox text when it is pressed
- L130 _private function_ `FSlateColor GetFilterNameColorAndOpacity() const` — Handler to determine the color of the checkbox text when it is hovered
- L137 _private function_ `FSlateColor GetBorderBackgroundColor() const`
- L144 _private member_ `FOnSimpleRequest OnFilterChanged;` — Invoked when the filter toggled
- L147 _private member_ `FOnFilterRequest OnRequestRemove;` — Invoked when a request to remove this filter originated from within this filter
- L150 _private member_ `FOnFilterRequest OnRequestEnableOnly;` — Invoked when a request to enable only this filter originated from within this filter
- L153 _private member_ `FOnSimpleRequest OnRequestDisableAll;` — Invoked when a request to disable all filters originated from within this filter
- L156 _private member_ `FOnSimpleRequest OnRequestRemoveAll;` — Invoked when a request to remove all filters originated from within this filter
- L158 _private member_ `FName FilterName;`
- L160 _private member_ `FLinearColor ColorCategory;`
- L163 _private member_ `TSharedPtr<SVisualLoggerFilterCheckBox> ToggleButtonPtr;` — The button to toggle the filter on or off
- L166 _private member_ `FLinearColor FilterColor;` — The color of the checkbox for this filter
- L169 _private member_ `FLinearColor BorderBackgroundColor;` — Default color for border background
- L172 _private member_ `mutable bool bWasEnabledLastTime;` — hacky to cache data
- L173 _private member_ `mutable ELogVerbosity::Type LastVerbosity;`
- L175 _private member_ `mutable FText CachedCaptionString;`
- L176 _private member_ `mutable FText CachedTooltipString;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFilterRequest, const TSharedRef<SVisualLoggerFilterWidget>&);`
- L21 _delegate_ `DECLARE_DELEGATE(FOnSimpleRequest);`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerFilters.h` (Private)


#### class `SVisualLoggerFilters`  
`class SVisualLoggerFilters : public SVisualLoggerBaseWidget`  
_L22-69_
- inherits: `SVisualLoggerBaseWidget`
- desc: A list of filters currently applied to an asset view.
- L25 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerFilters)`
- L28 _public prototype_ `virtual ~SVisualLoggerFilters();`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);`
- L31 _public prototype_ `uint32 GetCategoryIndex(const FString& InFilterName) const;`
- L32 _public prototype_ `void OnFiltersSearchChanged(const FText& Filter);`
- L33 _public prototype_ `void OnSearchChanged(const FText& Filter);`
- L34 _public prototype_ `bool GraphSubmenuVisibility(const FName MenuName);`
- L35 _public prototype_ `void FilterByTypeClicked(FName InGraphName, FName InDataName);`
- L36 _public prototype_ `bool IsAssetTypeActionsInUse(FName InGraphName, FName InDataName) const;`
- L37 _public prototype_ `void InvalidateCanvas();`
- L38 _public prototype_ `void GraphFilterCategoryClicked(FName MenuCategory);`
- L39 _public prototype_ `bool IsGraphFilterCategoryInUse(FName MenuCategory) const;`
- L40 _public prototype_ `void OnFiltersChanged();`
- L41 _public prototype_ `void ResetData();`
- L42 _public prototype_ `void OnItemSelectionChanged(const struct FVisualLogEntry& EntryItem);`
- L44 _public prototype_ `TSharedRef<SWidget> MakeGraphsFilterMenu();`
- L45 _public prototype_ `void CreateFiltersMenuCategoryForGraph(FMenuBuilder& MenuBuilder, FName MenuCategory) const;`
- L46 _public function_ `bool HasFilters()`
- L51 _protected prototype_ `void AddFilterCategory(FString, ELogVerbosity::Type, bool bMarkAsInUse);`
- L52 _protected prototype_ `void OnFilterCategoryAdded(FString, ELogVerbosity::Type);`
- L53 _protected prototype_ `void OnFilterCategoryRemoved(FString);`
- L54 _protected prototype_ `void OnItemsSelectionChanged(const FVisualLoggerDBRow& ChangedRow, int32 SelectedItemIndex);`
- L56 _protected prototype_ `void OnGraphAddedEvent(const FName& OwnerName, const FName& GraphName);`
- L57 _protected prototype_ `void OnGraphDataNameAddedEvent(const FName& OwnerName, const FName& GraphName, const FName& DataName);`
- L61 _protected member_ `TSharedPtr<SWrapBox> FilterBox;` — The horizontal box which contains all the filters
- L62 _protected member_ `TArray<TSharedRef<SVisualLoggerFilterWidget>> Filters;`
- L63 _protected member_ `TSharedPtr<SComboButton> GraphsFilterCombo;`
- L65 _protected member_ `FString GraphsSearchString;`
- L66 _protected member_ `TMap<FName, TArray<FString> > CachedGraphFilters;`
- L68 _protected member_ `TMap<FName, TArray<FName> > CachedDatasPerGraph;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerLogsList.h` (Private)


#### class `SVisualLoggerLogsList`  
`class SVisualLoggerLogsList : public SVisualLoggerBaseWidget`  
_L19-45_
- inherits: `SVisualLoggerBaseWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerLogsList)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);`
- L26 _public prototype_ `virtual ~SVisualLoggerLogsList();`
- L28 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L30 _public prototype_ `void ResetData();`
- L31 _public prototype_ `void ObjectSelectionChanged(const TArray<FName>& Selection);`
- L32 _public prototype_ `void OnItemSelectionChanged(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L33 _public prototype_ `void OnFiltersChanged();`
- L34 _public prototype_ `void OnFiltersSearchChanged(const FText& Filter);`
- L37 _protected prototype_ `void RegenerateLogEntries();`
- L38 _protected prototype_ `void GenerateLogs(const FVisualLogDevice::FVisualLogEntryItem& EntryItem, bool bGenerateHeader);`
- L39 _protected prototype_ `void LogEntryLineSelectionChanged(TSharedPtr<FLogEntryItem> SelectedItem, ESelectInfo::Type SelectInfo);`
- L40 _protected prototype_ `TSharedRef<ITableRow> LogEntryLinesGenerateRow(TSharedPtr<struct FLogEntryItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _protected member_ `TSharedPtr<SListView<TSharedPtr<struct FLogEntryItem> > > LogsLinesWidget;`
- L44 _protected member_ `TArray<TSharedPtr<struct FLogEntryItem> > CachedLogEntryLines;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerReport.h` (Private)


#### class `SVisualLoggerReport`  
`class SVisualLoggerReport : public SCompoundWidget`  
_L15-35_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerReport)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TArray< TSharedPtr<class SLogVisualizerTimeline> >&, TSharedPtr<class SVisualLoggerView> VisualLoggerView);`
- L24 _public prototype_ `virtual ~SVisualLoggerReport();`
- L27 _protected prototype_ `void GenerateReportText();`
- L30 _protected member_ `TArray< TSharedPtr<class SLogVisualizerTimeline> > SelectedItems;`
- L31 _protected member_ `TArray<TSharedRef<ITextDecorator>> Decorators;`
- L32 _protected member_ `TSharedPtr<class SRichTextBlock> InteractiveRichText;`
- L33 _protected member_ `FText ReportText;`
- L34 _protected member_ `TArray<FString> CollectedEvents;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerSectionOverlay.h` (Private)


#### class `SVisualLoggerSectionOverlay`  
`class SVisualLoggerSectionOverlay : public SCompoundWidget`  
_L18-52_
- inherits: `SCompoundWidget`
- desc: An overlay that displays global information in the section area
- L21 _public function_ `SLATE_BEGIN_ARGS( SVisualLoggerSectionOverlay ) : _DisplayTickLines( true ) , _DisplayScrubPosition( false )`
- L25 _public function_ `SLATE_ATTRIBUTE( bool, DisplayTickLines ) SLATE_ATTRIBUTE( bool, DisplayScrubPosition ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<class FVisualLoggerTimeSliderController> InTimeSliderController)`
- L39 _private prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget Interface
- L40 _private prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L41 _private prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L42 _private prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L43 _private prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L47 _private member_ `TSharedPtr<class FVisualLoggerTimeSliderController> TimeSliderController;` — Controller for manipulating time
- L49 _private member_ `TAttribute<bool> bDisplayScrubPosition;` — Whether or not to display the scrub position
- L51 _private member_ `TAttribute<bool> bDisplayTickLines;` — Whether or not to display tick lines

### `Source/Developer/LogVisualizer/Private/SVisualLoggerStatusView.h` (Private)


#### class `SVisualLoggerStatusView`  
`class SVisualLoggerStatusView : public SVisualLoggerBaseWidget`  
_L17-40_
- inherits: `SVisualLoggerBaseWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerStatusView)`
- L21 _public prototype_ `SLATE_END_ARGS();`
- L23 _public prototype_ `virtual ~SVisualLoggerStatusView();`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);`
- L25 _public prototype_ `void ResetData();`
- L28 _protected prototype_ `void OnObjectSelectionChanged(const TArray<FName>& SelectedRows);`
- L29 _protected prototype_ `void OnItemSelectionChanged(const FVisualLoggerDBRow& DBRow, int32 ItemIndex);`
- L30 _protected prototype_ `void GenerateStatusData(const FVisualLogDevice::FVisualLogEntryItem&, bool bAddHeader);`
- L32 _protected prototype_ `TSharedRef<ITableRow> HandleGenerateLogStatus(TSharedPtr<struct FLogStatusItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L33 _protected prototype_ `void OnLogStatusGetChildren(TSharedPtr<struct FLogStatusItem> InItem, TArray< TSharedPtr<FLogStatusItem> >& OutItems);`
- L34 _protected prototype_ `void OnExpansionChanged(TSharedPtr<FLogStatusItem> Item, bool);`
- L37 _protected member_ `TArray<FString> ExpandedCategories;`
- L38 _protected member_ `TSharedPtr< STreeView< TSharedPtr<FLogStatusItem> > > StatusItemsView;`
- L39 _protected member_ `TArray< TSharedPtr<FLogStatusItem> > StatusItems;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerTab.h` (Private)


#### class `SVisualLoggerTab`  
`class SVisualLoggerTab : public SDockTab`  
_L13-21_
- inherits: `SDockTab`
- L16 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L17 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerTimeSlider.h` (Private)


#### class `SVisualLoggerTimeSlider`  
`class SVisualLoggerTimeSlider : public SCompoundWidget`  
_L14-44_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerTimeSlider) : _MirrorLabels( false )`
- L22 _public prototype_ `SLATE_ARGUMENT( bool, MirrorLabels ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<FVisualLoggerTimeSliderController> InTimeSliderController );` — If we should mirror the labels on the timeline
- L35 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L36 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L37 _protected prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L38 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L39 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L40 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L42 _private member_ `TSharedPtr<FVisualLoggerTimeSliderController> TimeSliderController;`
- L43 _private member_ `bool bMirrorLabels;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerTimeline.h` (Private)


#### class `SLogVisualizerTimeline`  
`class SLogVisualizerTimeline : public SCompoundWidget`  
_L24-84_
- inherits: `SCompoundWidget`
- desc: A list of filters currently applied to an asset view.
- L27 _public function_ `SLATE_BEGIN_ARGS(SLogVisualizerTimeline)`
- L28 _public prototype_ `SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_END_ARGS();`
- L31 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L35 _public function_ `virtual TOptional<bool> OnQueryShowFocus(const EFocusCause InFocusCause) const override`
- L41 _public prototype_ `virtual ~SLogVisualizerTimeline();` — Constructs this widget with InArgs
- L42 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<class FVisualLoggerTimeSliderController> InTimeSliderController, TSharedPtr<class SVisualLoggerTimelinesContainer> InContainer, const FName& InOwnerName, const FName& InOwnerDisplayName, const FName& InOwnerClassName);`
- L44 _public prototype_ `bool IsSelected() const;`
- L45 _public prototype_ `const FSlateBrush* GetBorder() const;`
- L47 _public prototype_ `void OnFiltersChanged();`
- L48 _public prototype_ `void OnSearchChanged(const FText& Filter);`
- L49 _public prototype_ `void OnFiltersSearchChanged(const FText& Filter);`
- L50 _public prototype_ `void UpdateVisibility();`
- L52 _public prototype_ `void AddEntry(const FVisualLogDevice::FVisualLogEntryItem& Entry);`
- L53 _public prototype_ `const TArray<FVisualLogDevice::FVisualLogEntryItem>& GetEntries();`
- L54 _public function_ `FName GetName() const`
- L55 _public function_ `FName GetOwnerClassName() const`
- L56 _public prototype_ `void HandleLogVisualizerSettingChanged(FName Name);`
- L57 _public function_ `TSharedPtr<class SVisualLoggerTimelinesContainer> GetOwner()`
- L60 _public prototype_ `void Goto(float ScrubPosition);` — @todo: This function currently doesn't do anything!
- L62 _public prototype_ `void GotoNextItem();` — @todo: This function currently doesn't do anything!
- L64 _public prototype_ `void GotoPreviousItem();` — @todo: This function currently doesn't do anything!
- L66 _public prototype_ `void MoveCursorByDistance(int32 Distance);` — @todo: This function currently doesn't do anything!
- L69 _protected prototype_ `void OnNewItemHandler(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L70 _protected prototype_ `void OnRowSelectionChanged(const TArray<FName>& RowNames);`
- L73 _protected member_ `TSharedPtr<class SVisualLoggerTimelinesContainer> Owner;`
- L74 _protected member_ `TSharedPtr<class SVisualLoggerTimelineBar> TimelineBar;`
- L75 _protected member_ `TSharedPtr<SMenuAnchor> PopupAnchor;`
- L77 _protected member_ `FName OwnerName;`
- L78 _protected member_ `FName OwnerDisplayName;`
- L79 _protected member_ `FName OwnerClassName;`
- L80 _protected member_ `FString SearchFilter;`
- L83 _protected member_ `FOnGetContent OnGetMenuContent;` — Delegate to execute to get the menu content of this timeline

### `Source/Developer/LogVisualizer/Private/SVisualLoggerTimelineBar.h` (Private)


#### class `SVisualLoggerTimelineBar`  
`class SVisualLoggerTimelineBar : public SLeafWidget`  
_L21-47_
- inherits: `SLeafWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerTimelineBar)`
- L25 _public prototype_ `SLATE_END_ARGS() virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L29 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L34 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L36 _public prototype_ `virtual ~SVisualLoggerTimelineBar();`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FVisualLoggerTimeSliderController> InTimeSliderController, TSharedPtr<class SLogVisualizerTimeline> TimelineOwner);`
- L38 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L39 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L42 _protected member_ `TSharedPtr<class FVisualLoggerTimeSliderController> TimeSliderController;`
- L43 _protected member_ `TWeakPtr<class SLogVisualizerTimeline> TimelineOwner;`
- L44 _protected member_ `FDelegateHandle OnFiltersChangedDelegateHandle;`
- L45 _protected member_ `int32 MouseMoveClosestItemIndex = INDEX_NONE;`
- L46 _protected member_ `bool bToolTipUpdateRequested = false;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerTimelinesContainer.h` (Private)


#### class `SVisualLoggerTimelinesContainer`  
`class SVisualLoggerTimelinesContainer : public SCompoundWidget`  
_L20-90_
- inherits: `SCompoundWidget`
- desc: A list of filters currently applied to an asset view.
- L23 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerTimelinesContainer)`
- L26 _public prototype_ `virtual ~SVisualLoggerTimelinesContainer();`
- L28 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SVisualLoggerView>, TSharedRef<FVisualLoggerTimeSliderController> TimeSliderController);` — Constructs this widget with InArgs
- L35 _public prototype_ `TSharedRef<SWidget> GetRightClickMenuContent();`
- L37 _public prototype_ `void OnTimelineSelected(TSharedPtr<STimelinesBar> Widget);`
- L38 _public prototype_ `void ChangeSelection(TSharedPtr<SLogVisualizerTimeline>, const FPointerEvent& MouseEvent);`
- L39 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L41 _public prototype_ `void OnFiltersChanged();`
- L42 _public prototype_ `void OnSearchChanged(const FText& Filter);`
- L43 _public prototype_ `void OnFiltersSearchChanged(const FText& Filter);`
- L45 _public prototype_ `void ResetData();`
- L47 _public prototype_ `void GenerateReport();`
- L56 _public prototype_ `void SetSelectionState(TSharedPtr<SLogVisualizerTimeline> AffectedNode, bool bSelect, bool bDeselectOtherNodes = true);` — Selects a node in the tree @param AffectedNode			The node to select @param bSelect				Whether or not to select @param bDeselectOtherNodes	Whether or not to deselect all other nodes
- L61 _public function_ `const TArray< TSharedPtr<SLogVisualizerTimeline> >& GetSelectedNodes() const` — @return All currently selected nodes
- L63 _public function_ `const TArray< TSharedPtr<SLogVisualizerTimeline> >& GetAllNodes() const`
- L71 _public prototype_ `bool IsNodeSelected(TSharedPtr<SLogVisualizerTimeline> Node) const;` — Returns whether or not a node is selected @param Node	The node to check for selection @return true if the node is selected
- L74 _protected prototype_ `void OnNewRowHandler(const FVisualLoggerDBRow& DBRow);`
- L75 _protected prototype_ `void OnNewItemHandler(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L76 _protected prototype_ `void OnObjectSelectionChanged(const TArray<FName>& RowNames);`
- L77 _protected prototype_ `void OnRowChangedVisibility(const FName&);`
- L80 _protected member_ `TSharedPtr<SVerticalBox> ContainingBorder;`
- L81 _protected member_ `TSharedPtr<FVisualLoggerTimeSliderController> TimeSliderController;`
- L82 _protected member_ `TSharedPtr<SVisualLoggerView> VisualLoggerView;`
- L84 _protected member_ `TArray<TSharedPtr<SLogVisualizerTimeline> > TimelineItems;`
- L85 _protected member_ `TArray<TSharedPtr<SLogVisualizerTimeline> > CachedSelectedTimelines;`
- L86 _protected member_ `double CachedMinTime;`
- L87 _protected member_ `double CachedMaxTime;`
- L89 _protected member_ `FText CurrentSearchText;`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerToolbar.h` (Private)


#### class `SVisualLoggerToolbar`  
`class SVisualLoggerToolbar : public SVisualLoggerBaseWidget`  
_L16-45_
- inherits: `SVisualLoggerBaseWidget`
- desc: Implements the messaging debugger toolbar widget.
- L20 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerToolbar)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);` — Construct this widget @param InArgs The declaration data for this widget. @param InStyle The visual style to use for this widget. @param InCommandList The command list to bind to.
- L42 _protected prototype_ `TSharedRef<SWidget> MakeToolbar(const TSharedRef<FUICommandList>& CommandList);` — Creates the toolbar widget. @param CommandList The command list to use for the toolbar buttons. @return The toolbar widget.
- L44 _protected prototype_ `TSharedRef<SWidget> MakeClippingDistanceWidget();`

### `Source/Developer/LogVisualizer/Private/SVisualLoggerView.h` (Private)


#### class `SVisualLoggerView`  
`class SVisualLoggerView : public SVisualLoggerBaseWidget`  
_L18-65_
- inherits: `SVisualLoggerBaseWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SVisualLoggerView) : _ViewRange(TRange<float>(0.0f, 5.0f)) , _ScrubPosition(1.0f)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(TRange<float>, ViewRange) SLATE_ATTRIBUTE(float, ScrubPosition) SLATE_EVENT(FOnFiltersSearchChanged, OnFiltersSearchChanged) SLATE_END_ARGS();` — The current view range (seconds)
- L32 _public prototype_ `virtual ~SVisualLoggerView();`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);`
- L34 _public function_ `float GetAnimationOutlinerFillPercentage() const`
- L40 _public prototype_ `void SetAnimationOutlinerFillPercentage(float FillPercentage);`
- L42 _public prototype_ `TSharedRef<SWidget> MakeSectionOverlay(TSharedRef<class FVisualLoggerTimeSliderController> TimeSliderController, const TAttribute< TRange<float> >& ViewRange, const TAttribute<float>& ScrubPosition, bool bTopOverlay);`
- L43 _public prototype_ `void SetSearchString(FText SearchString);`
- L45 _public prototype_ `void OnFiltersChanged();`
- L46 _public prototype_ `void OnSearchChanged(const FText& Filter);`
- L47 _public prototype_ `void OnFiltersSearchChanged(const FText& Filter);`
- L48 _public prototype_ `void OnSearchSplitterResized();`
- L49 _public prototype_ `void OnChangedClassesFilter();`
- L51 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L52 _public prototype_ `TSharedRef<SWidget> MakeClassesFilterMenu();`
- L53 _public prototype_ `void ResetData();`
- L56 _protected member_ `TSharedPtr<class SVisualLoggerTimelinesContainer> TimelinesContainer;`
- L57 _protected member_ `TSharedPtr<class SSplitter> SearchSplitter;`
- L58 _protected member_ `TSharedPtr<class SScrollBox> ScrollBox;`
- L59 _protected member_ `TSharedPtr<class SSearchBox> SearchBox;`
- L60 _protected member_ `TSharedPtr<class SComboButton> ClassesComboButton;`
- L62 _protected member_ `FDelegateHandle OnFiltersChangedDelegateHandle;`
- L64 _protected member_ `float AnimationOutlinerFillPercentage;`

### `Source/Developer/LogVisualizer/Private/VisualLoggerCameraController.h` (Private)


#### class `AVisualLoggerCameraController`  
`class AVisualLoggerCameraController : public ADebugCameraController`  
_L12-41_
- reflection: `UCLASS(config=Input, hidedropdown)`
- inherits: `ADebugCameraController`
- L15 _public prototype_ `DECLARE_DELEGATE_OneParam(FActorSelectedDelegate, class AActor*);`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FLogEntryIterationDelegate, int32);`
- L21 _public member_ `TWeakObjectPtr<class AActor> PickedActor;` — `UPROPERTY()`
- L23 _public prototype_ `virtual void PostInitializeComponents() override;`
- L25 _public prototype_ `static AVisualLoggerCameraController* EnableCamera(UWorld* InWorld);`
- L26 _public prototype_ `static void DisableCamera(UWorld* InWorld);`
- L27 _public prototype_ `static bool IsEnabled(UWorld* InWorld);`
- L29 _public prototype_ `virtual void Select( FHitResult const& Hit ) override;`
- L31 _public prototype_ `void ShowNextEntry();`
- L32 _public prototype_ `void ShowPrevEntry();`
- L34 _public member_ `static TWeakObjectPtr<AVisualLoggerCameraController> Instance;`
- L36 _public member_ `FActorSelectedDelegate OnActorSelected;`
- L37 _public member_ `FLogEntryIterationDelegate OnIterateLogEntries;`
- L40 _protected prototype_ `virtual void SetupInputComponent() override;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FActorSelectedDelegate, class AActor*);`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FLogEntryIterationDelegate, int32);`

### `Source/Developer/LogVisualizer/Private/VisualLoggerCanvasRenderer.h` (Private)


#### struct `FVisualLoggerCanvasRenderer`  
`struct FVisualLoggerCanvasRenderer`  
_L11-47_
- L28 _public member_ `TMap<FName, FGraphData> CollectedGraphs;`
- L31 _public prototype_ `FVisualLoggerCanvasRenderer();`
- L32 _public prototype_ `~FVisualLoggerCanvasRenderer();`
- L34 _public prototype_ `void DrawOnCanvas(class UCanvas* Canvas, class APlayerController*);`
- L35 _public prototype_ `void OnItemSelectionChanged(const FVisualLoggerDBRow& ChangedRow, int32 SelectedItemIndex);`
- L36 _public prototype_ `void ObjectSelectionChanged(const TArray<FName>& RowNames);`
- L37 _public function_ `void DirtyCachedData()`
- L38 _public prototype_ `void ResetData();`
- L41 _protected prototype_ `void DrawHistogramGraphs(class UCanvas* Canvas, class APlayerController* );`
- L44 _private member_ `bool bDirtyData;`
- L45 _private member_ `FVisualLogEntry SelectedEntry;`
- L46 _private member_ `TMap<FString, TArray<FString> > UsedGraphCategories;`

#### struct `FVisualLoggerCanvasRenderer::FGraphLineData`  
`struct FGraphLineData`  
_L13-18_
- L15 _public member_ `FName DataName;`
- L16 _public member_ `FVector2D LeftExtreme, RightExtreme;`
- L16 _public member_ `FVector2D LeftExtreme, RightExtreme;`
- L17 _public member_ `TArray<FVector2D> Samples;`

#### struct `FVisualLoggerCanvasRenderer::FGraphData`  
`struct FGraphData`  
_L20-26_
- L22 _public function_ `FGraphData() : Min(FVector2D(FLT_MAX, FLT_MAX)), Max(FVector2D(-FLT_MAX, -FLT_MAX))`
- L24 _public member_ `FVector2D Min, Max;`
- L24 _public member_ `FVector2D Min, Max;`
- L25 _public member_ `TMap<FName, FGraphLineData> GraphLines;`

### `Source/Developer/LogVisualizer/Private/VisualLoggerCommands.h` (Private)


#### class `FVisualLoggerCommands`  
`class FVisualLoggerCommands : public TCommands<FVisualLoggerCommands>`  
_L11-56_
- inherits: `TCommands<FVisualLoggerCommands>`
- L16 _public function_ `FVisualLoggerCommands() : TCommands<FVisualLoggerCommands>("VisualLogger", NSLOCTEXT("Contexts", "VisualLogger", "Visual Logger"), NAME_None, "LogVisualizerStyle")` — Default constructor.
- L24 _public function_ `virtual void RegisterCommands() override`
- L43 _public member_ `TSharedPtr<FUICommandInfo> StartRecording;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> StopRecording;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> Pause;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> Resume;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> FreeCamera;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> LoadFromVLog;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> SaveToVLog;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> SaveAllToVLog;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> ToggleGraphs;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> ResetData;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> Refresh;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> AutoScroll;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> HideEmpty;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "FVisualLoggerCommands"`

### `Source/Developer/LogVisualizer/Private/VisualLoggerDatabase.h` (Private)


#### struct `FVisualLoggerDBEvents`  
`struct FVisualLoggerDBEvents`  
_L12-35_
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FItemSelectionChangedEvent, const FVisualLoggerDBRow&, int32);`
- L15 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNewItemEvent, const FVisualLoggerDBRow&, int32);`
- L16 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FNewRowEvent, const FVisualLoggerDBRow&);`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowSelectionChangedEvent, const TArray<FName>&);`
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowChangedVisibilityEvent, const FName&);`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowRemovedEvent, const FName&);`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphChangedVisibilityEvent, const FName&);`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphAddedEvent, const FName&, const FName&);`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGraphDataNameAddedEvent, const FName&, const FName&, const FName&);`
- L25 _public member_ `FNewItemEvent OnNewItem;`
- L26 _public member_ `FItemSelectionChangedEvent OnItemSelectionChanged;`
- L27 _public member_ `FNewRowEvent OnNewRow;`
- L28 _public member_ `FOnRowSelectionChangedEvent OnRowSelectionChanged;`
- L29 _public member_ `FOnRowChangedVisibilityEvent OnRowChangedVisibility;`
- L30 _public member_ `FOnRowRemovedEvent OnRowRemoved;`
- L32 _public member_ `FOnGraphChangedVisibilityEvent OnGraphChangedVisibilityEvent;`
- L33 _public member_ `FOnGraphAddedEvent OnGraphAddedEvent;`
- L34 _public member_ `FOnGraphDataNameAddedEvent OnGraphDataNameAddedEvent;`

#### struct `FVisualLoggerDBRow`  
`struct FVisualLoggerDBRow`  
_L37-86_
- L40 _public function_ `FVisualLoggerDBRow(FVisualLoggerDBEvents& InEvents, const FName& InOwnerName, const FName& InOwnerDisplayName, const FName& InOwnerClassName) : DBEvents(InEvents) , OwnerName(InOwnerName) , OwnerDisplayName(InOwnerDisplayName) , OwnerClassName(InOwnerClassName)`
- L47 _public function_ `const FName& GetOwnerName() const`
- L48 _public function_ `const FName& GetOwnerDisplayName() const`
- L49 _public function_ `const FName& GetOwnerClassName() const`
- L51 _public prototype_ `void AddItem(const FVisualLogDevice::FVisualLogEntryItem& NewItem);`
- L52 _public function_ `const TArray<FVisualLogDevice::FVisualLogEntryItem>& GetItems() const`
- L54 _public prototype_ `void MoveTo(int32 Index);`
- L55 _public prototype_ `const FVisualLogDevice::FVisualLogEntryItem& GetCurrentItem() const;`
- L56 _public function_ `int32 GetCurrentItemIndex() const`
- L58 _public function_ `bool IsRowVisible() const`
- L63 _public prototype_ `void SetItemVisibility(int32 ItemIndex, bool IsVisible);`
- L64 _public function_ `bool IsItemVisible(int32 ItemIndex) const`
- L65 _public function_ `int32 GetNumberOfHiddenItems() const`
- L66 _public function_ `void SetHiddenBySearchFilter(const bool bInHiddenBySearchFilter)`
- L72 _public prototype_ `int32 GetClosestItem(double Time) const;`
- L73 _public prototype_ `int32 GetClosestItem(double Time, double ScrubTime) const;`
- L76 _protected member_ `FVisualLoggerDBEvents& DBEvents;`
- L77 _protected member_ `FName OwnerName;`
- L78 _protected member_ `FName OwnerDisplayName;`
- L79 _protected member_ `FName OwnerClassName;`
- L80 _protected member_ `int32 CurrentItemIndex = INDEX_NONE;`
- L82 _protected member_ `TArray<FVisualLogDevice::FVisualLogEntryItem> Items;`
- L83 _protected member_ `TBitArray<> HiddenItems;`
- L84 _protected member_ `int32 NumHiddenItems = 0;`
- L85 _protected member_ `bool bHiddenBySearchFilter = false;`

#### struct `FVisualLoggerDatabase`  
`struct FVisualLoggerDatabase`  
_L88-129_
- L90 _public typedef_ `typedef TArray<FVisualLoggerDBRow>::TConstIterator FConstRowIterator;`
- L91 _public typedef_ `typedef TArray<FVisualLoggerDBRow>::TIterator FRowIterator;`
- L93 _public prototype_ `static FVisualLoggerDatabase& Get();`
- L94 _public prototype_ `static void Initialize();`
- L95 _public prototype_ `static void Shutdown();`
- L97 _public prototype_ `void Reset();`
- L98 _public function_ `FVisualLoggerDBEvents& GetEvents()`
- L100 _public function_ `int32 NumberOfRows()`
- L101 _public prototype_ `void AddItem(const FVisualLogDevice::FVisualLogEntryItem& NewItem);`
- L102 _public function_ `FConstRowIterator GetConstRowIterator() const`
- L103 _public function_ `FRowIterator GetRowIterator()`
- L105 _public prototype_ `bool ContainsRowByName(FName InName);`
- L106 _public prototype_ `FVisualLoggerDBRow& GetRowByName(FName InName);`
- L108 _public prototype_ `void SelectRow(FName InName, bool bDeselectOtherNodes = false);`
- L109 _public prototype_ `void DeselectRow(FName InName);`
- L110 _public function_ `bool IsRowSelected(FName InName) const`
- L111 _public prototype_ `const TArray<FName>& GetSelectedRows() const;`
- L113 _public function_ `bool IsRowVisible(FName RowName) const`
- L114 _public prototype_ `void SetRowVisibility(FName RowName, bool IsVisible);`
- L116 _public prototype_ `void RemoveRow(FName RowName);`
- L119 _protected member_ `TArray<FVisualLoggerDBRow> Rows;`
- L120 _protected member_ `TMap<FName, int32> RowNameToIndex;`
- L121 _protected member_ `TArray<FName> SelectedRows;`
- L122 _protected member_ `TArray<FName> HiddenRows;`
- L124 _protected member_ `FVisualLoggerDBEvents DBEvents;`
- L127 _private member_ `static TSharedPtr< struct FVisualLoggerDatabase > StaticInstance;`

#### struct `FVisualLoggerGraphData`  
`struct FVisualLoggerGraphData`  
_L131-138_
- L133 _public member_ `FName DataName;`
- L134 _public member_ `TArray<FVector2D> Samples;`
- L135 _public member_ `TArray<double> TimeStamps;`
- L137 _public function_ `FVisualLoggerGraphData(FName InDataName) : DataName(InDataName)`

#### struct `FVisualLoggerGraph`  
`struct FVisualLoggerGraph`  
_L140-166_
- L142 _public typedef_ `typedef TArray<FVisualLoggerGraphData>::TConstIterator FConstDataIterator;`
- L143 _public typedef_ `typedef TArray<FVisualLoggerGraphData>::TIterator FDataIterator;`
- L145 _public function_ `FVisualLoggerGraph(FName InOwnerName) : OwnerName(InOwnerName)`
- L147 _public function_ `FName GetOwnerName() const`
- L148 _public function_ `FName GetGraphName() const`
- L149 _public function_ `void SetGraphName(FName InGraphName)`
- L151 _public prototype_ `bool IsDataVisible(FName DataName) const;`
- L152 _public prototype_ `void SetDataVisibility(FName DataName, bool IsVisible);`
- L154 _public function_ `bool ContainsDataByName(FName DataName) const`
- L155 _public prototype_ `FVisualLoggerGraphData& FindOrAddDataByName(FName DataName);`
- L157 _public function_ `FConstDataIterator GetConstDataIterator() const`
- L158 _public function_ `FDataIterator GetDataIterator()`
- L161 _protected member_ `FName OwnerName;`
- L162 _protected member_ `FName GraphName;`
- L163 _protected member_ `TArray<FVisualLoggerGraphData> DataGraphs;`
- L164 _protected member_ `TMap<FName, int32> DataNameToIndex;`
- L165 _protected member_ `TArray<FName> HiddenGraphs;`

#### struct `FVisualLoggerGraphsDatabase`  
`struct FVisualLoggerGraphsDatabase`  
_L168-212_
- desc: histogram graphs database as separate structure to optimize access and category filters
- L178 _public typedef_ `typedef TArray<FVisualLoggerGraph>::TConstIterator FConstGraphIterator;`
- L179 _public typedef_ `typedef TArray<FVisualLoggerGraph>::TIterator FGraphIterator;`
- L181 _public typedef_ `typedef TMap<FName, FVisualLoggerGraphHelper>::TConstIterator FConstOwnersIterator;`
- L182 _public typedef_ `typedef TMap<FName, FVisualLoggerGraphHelper>::TIterator FOwnersIterator;`
- L184 _public prototype_ `static FVisualLoggerGraphsDatabase& Get();`
- L185 _public prototype_ `static void Initialize();`
- L186 _public prototype_ `static void Shutdown();`
- L187 _public prototype_ `void Reset();`
- L189 _public prototype_ `void AddItem(const FVisualLogDevice::FVisualLogEntryItem& NewItem);`
- L191 _public prototype_ `bool IsGraphVisible(FName OwnerName, FName GraphName);`
- L192 _public prototype_ `void SetGraphVisibility(FName OwnerName, FName GraphName, bool IsVisible);`
- L194 _public prototype_ `bool ContainsGraphByName(FName OwnerName, FName GraphName);`
- L195 _public prototype_ `FVisualLoggerGraph& GetGraphByName(FName OwnerName, FName GraphName);`
- L196 _public function_ `bool ContainsHistogramGraphs() const`
- L198 _public prototype_ `const TArray<FVisualLoggerGraph>& GetGraphsByOwnerName(FName OwnerName);`
- L200 _public function_ `FConstGraphIterator GetConstGraphsIterator(FName OwnerName)`
- L201 _public function_ `FGraphIterator GetGraphsIterator(FName OwnerName)`
- L203 _public function_ `FConstOwnersIterator GetConstOwnersIterator()`
- L204 _public function_ `FOwnersIterator GetOwnersIterator()`
- L207 _protected member_ `TMap<FName, FVisualLoggerGraphHelper> OwnerNameToGraphs;`
- L208 _protected member_ `TArray<FName> HiddenGraphs;` — encoded as "OwnerName$GraphName" for simplicity.
- L211 _private member_ `static TSharedPtr< struct FVisualLoggerGraphsDatabase > StaticInstance;`

#### struct `FVisualLoggerGraphsDatabase::FVisualLoggerGraphHelper`  
`struct FVisualLoggerGraphHelper`  
_L171-175_
- L173 _public member_ `TArray<FVisualLoggerGraph> AllGraphs;`
- L174 _public member_ `TMap<FName, int32> GraphNameToIndex;`

#### struct `FVisualLoggerEditorInterface`  
`struct FVisualLoggerEditorInterface : public IVisualLoggerEditorInterface`  
_L214-230_
- inherits: `IVisualLoggerEditorInterface`
- L216 _public function_ `static IVisualLoggerEditorInterface* Get()`
- L218 _public prototype_ `const FName& GetRowClassName(FName RowName) const override;`
- L219 _public prototype_ `int32 GetSelectedItemIndex(FName RowName) const override;`
- L220 _public prototype_ `const TArray<FVisualLogDevice::FVisualLogEntryItem>& GetRowItems(FName RowName) override;`
- L221 _public prototype_ `const FVisualLogDevice::FVisualLogEntryItem& GetSelectedItem(FName RowName) const override;`
- L223 _public prototype_ `const TArray<FName>& GetSelectedRows() const override;`
- L224 _public prototype_ `bool IsRowVisible(FName RowName) const override;`
- L225 _public prototype_ `bool IsItemVisible(FName RowName, int32 ItemIndex) const override;`
- L226 _public prototype_ `UWorld* GetWorld() const override;`
- L227 _public prototype_ `AActor* GetHelperActor(UWorld* InWorld = nullptr) const override;`
- L229 _public prototype_ `bool MatchCategoryFilters(const FString& String, ELogVerbosity::Type Verbosity = ELogVerbosity::All) override;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FItemSelectionChangedEvent, const FVisualLoggerDBRow&, int32);`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNewItemEvent, const FVisualLoggerDBRow&, int32);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FNewRowEvent, const FVisualLoggerDBRow&);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowSelectionChangedEvent, const TArray<FName>&);`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowChangedVisibilityEvent, const FName&);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowRemovedEvent, const FName&);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGraphChangedVisibilityEvent, const FName&);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGraphAddedEvent, const FName&, const FName&);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGraphDataNameAddedEvent, const FName&, const FName&, const FName&);`

### `Source/Developer/LogVisualizer/Private/VisualLoggerHUD.h` (Private)


#### class `AVisualLoggerHUD`  
`class AVisualLoggerHUD : public ADebugCameraHUD`  
_L14-25_
- reflection: `UCLASS(hidedropdown)`
- inherits: `ADebugCameraHUD`
- L18 _private member_ `FFontRenderInfo TextRenderInfo;`
- L20 _private prototype_ `virtual bool DisplayMaterials( float X, float& Y, float DY, UMeshComponent* MeshComp ) override;`
- L23 _private prototype_ `virtual void PostRender() override;`

### `Source/Developer/LogVisualizer/Private/VisualLoggerRenderingActor.h` (Private)


#### class `AVisualLoggerRenderingActor`  
`class AVisualLoggerRenderingActor : public AVisualLoggerRenderingActorBase`  
_L23-45_
- reflection: `UCLASS(MinimalAPI, config = Engine, NotBlueprintable, Transient, notplaceable, AdvancedClassDisplay)`
- inherits: `AVisualLoggerRenderingActorBase`
- L27 _public prototype_ `virtual ~AVisualLoggerRenderingActor();`
- L28 _public prototype_ `void ResetRendering();`
- L29 _public prototype_ `void ObjectVisibilityChanged(const FName& RowName);`
- L30 _public prototype_ `void ObjectSelectionChanged(const TArray<FName>& Selection);`
- L31 _public prototype_ `void OnItemSelectionChanged(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L33 _public prototype_ `virtual void IterateDebugShapes(TFunction<void(const FTimelineDebugShapes&) > Callback) override;`
- L34 _public prototype_ `virtual bool MatchCategoryFilters(const FName& CategoryName, ELogVerbosity::Type Verbosity) const override;`
- L36 _private prototype_ `void OnFiltersChanged();`
- L38 _private member_ `TArray<FName> CachedRowSelection;`
- L39 _private member_ `TMap<FName, FTimelineDebugShapes> DebugShapesPerRow;`
- L42 _private prototype_ `void AddDebugRendering();`
- L43 _private member_ `FTimelineDebugShapes TestDebugShapes;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LOGVISUALIZER_API`
- L11 _macro_ `#define VLOG_TEST_DEBUG_RENDERING 0` — enable adding some hard coded shapes to the VisualLoggerRenderingActor for testing
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, class AActor*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, class AActor*);`

### `Source/Developer/LogVisualizer/Private/VisualLoggerRenderingComponent.h` (Private)


#### class `UVisualLoggerRenderingComponent`  
`class UVisualLoggerRenderingComponent : public UDebugDrawComponent`  
_L12-26_
- reflection: `UCLASS(ClassGroup = Debug)`
- inherits: `UDebugDrawComponent`
- desc: Primitive component used to draw visual logger data on level
- L17 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L18 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L21 _public prototype_ `void SetFarClippingDistance(double Distance);` — Allows to override the far clipping distance for all the log elements by this actor :
- L22 _public function_ `double GetFarClippingDistance() const`
- L25 _protected member_ `double FarClippingDistance = 0.0;`

### `Source/Developer/LogVisualizer/Private/VisualLoggerTimeSliderController.h` (Private)


#### struct `FVisualLoggerTimeSliderArgs`  
`struct FVisualLoggerTimeSliderArgs`  
_L14-56_
- L16 _public function_ `DECLARE_DELEGATE_OneParam( FOnRangeChanged, TRange<double> ) DECLARE_DELEGATE_TwoParams( FOnScrubPositionChanged, double, bool ) FVisualLoggerTimeSliderArgs() : ScrubPosition(0.) , ViewRange(TRange<double>(0., 5.)) , ClampRange(TRange<double>(0., 5.)) , AllowZoom(true) , CursorSize(0.05f)`
- L28 _public member_ `TAttribute<double> ScrubPosition;` — The scrub position
- L31 _public member_ `FOnScrubPositionChanged OnScrubPositionChanged;` — Called when the scrub position changes
- L34 _public member_ `FSimpleDelegate OnBeginScrubberMovement;` — Called right before the scrubber begins to move
- L37 _public member_ `FSimpleDelegate OnEndScrubberMovement;` — Called right after the scrubber handle is released by the user
- L40 _public member_ `TAttribute< TRange<double> > ViewRange;` — View time range
- L43 _public member_ `TAttribute< TRange<double> > ClampRange;` — Clamp time range
- L46 _public member_ `FOnRangeChanged OnViewRangeChanged;` — Called when the view range changes
- L49 _public member_ `TAttribute<double> TimeSnapInterval;` — Attribute defining the time snap interval
- L52 _public member_ `bool AllowZoom;` — If we are allowed to zoom
- L55 _public member_ `TAttribute< float > CursorSize;` — Cursor range for data like histogram graphs, etc.

#### class `FVisualLoggerTimeSliderController`  
`class FVisualLoggerTimeSliderController`  
_L62-136_
- desc: A time slider controller for sequencer Draws and manages time data for a Sequencer
- L65 _public prototype_ `FVisualLoggerTimeSliderController(const FVisualLoggerTimeSliderArgs& InArgs);`
- L76 _public prototype_ `double DetermineOptimalSpacing(double InPixelsPerInput, uint32 MinTick, float MinTickSpacing) const;` — Determines the optimal spacing between tick marks in the slider for a given pixel density Increments until a minimum amount of slate units specified by MinTick is reached @param InPixelsPerInput	The density of pixels between each input @param MinTick			The minimum slate units per tick allowed @param MinTickSpacing	The minimum tick spacing in time units allowed @return the optimal spacing in time units
- L77 _public prototype_ `void SetTimesliderArgs(const FVisualLoggerTimeSliderArgs& InArgs);`
- L79 _public prototype_ `int32 OnPaintTimeSlider( bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;`
- L80 _public prototype_ `FReply OnMouseButtonDown( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );`
- L81 _public prototype_ `FReply OnMouseButtonUp( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );`
- L82 _public prototype_ `FReply OnMouseMove( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );`
- L83 _public prototype_ `FReply OnMouseWheel( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );`
- L84 _public function_ `FCursorReply OnCursorQuery( TSharedRef<const SWidget> WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const`
- L89 _public prototype_ `int32 OnPaintSectionView( const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, bool bDisplayTickLines, bool bDisplayScrubPosition ) const;` — Draws major tick lines in the section view
- L90 _public function_ `FVisualLoggerTimeSliderArgs& GetTimeSliderArgs()`
- L97 _public prototype_ `void CommitScrubPosition(double NewValue, bool bIsScrubbing );` — Call this method when the user's interaction has changed the scrub position @param NewValue				Value resulting from the user's interaction @param bIsScrubbing			True if done via scrubbing, false if just releasing scrubbing
- L99 _public prototype_ `void SetExternalScrollbar(TSharedRef<SScrollBar> Scrollbar);`
- L100 _public prototype_ `void SetTimeRange(double MinValue, double MaxValue);`
- L101 _public prototype_ `void SetClampRange(double MinValue, double MaxValue);`
- L102 _public function_ `bool IsPanning()`
- L104 _public prototype_ `double GetTimeAtCursorPosition(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L117 _private prototype_ `void DrawTicks( FSlateWindowElementList& OutDrawElements, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs ) const;` — Draws time tick marks @param OutDrawElements	List to add draw elements to @param RangeToScreen		Time range to screen space converter @param InArgs			Parameters for drawing the tick lines
- L118 _private prototype_ `void HorizontalScrollBar_OnUserScrolled(float ScrollOffset);`
- L120 _private member_ `FVisualLoggerTimeSliderArgs TimeSliderArgs;`
- L122 _private member_ `const FSlateBrush* ScrubHandleUp;` — Brush for drawing an upwards facing scrub handle
- L124 _private member_ `const FSlateBrush* ScrubHandleDown;` — Brush for drawing a downwards facing scrub handle
- L126 _private member_ `const FSlateBrush* CursorBackground;` — Brush for drawing cursor background to visualize corsor size
- L128 _private member_ `double DistanceDragged;` — Total mouse delta during dragging
- L130 _private member_ `bool bDraggingScrubber;` — If we are dragging the scrubber
- L132 _private member_ `bool bPanning;` — If we are currently panning the panel
- L134 _private member_ `TSharedPtr<SScrollBar> Scrollbar;` — /
- L135 _private member_ `FVector2f SoftwareCursorPosition;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam( FOnRangeChanged, TRange<double> ) DECLARE_DELEGATE_TwoParams( FOnScrubPositionChanged, double, bool ) FVisualLoggerTimeSliderArgs() : ScrubPosition(0.) , ViewRange(TRange<double>(0., 5.)) , ClampRange(TRange<double>(0., 5.)) , AllowZoom(true) , CursorSize(0.05f) {} TAttribute<double> ScrubPosition;`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnScrubPositionChanged, double, bool ) FVisualLoggerTimeSliderArgs() : ScrubPosition(0.) , ViewRange(TRange<double>(0., 5.)) , ClampRange(TRange<double>(0., 5.)) , AllowZoom(true) , CursorSize(0.05f) {} TAttribute<double> ScrubPosition;`

### `Source/Developer/LogVisualizer/Public/ILogVisualizer.h` (Public)


#### class `ILogVisualizer`  
`class ILogVisualizer : public IModuleInterface, public IModularFeature`  
_L9-12_
- inherits: `IModuleInterface,IModularFeature`

### `Source/Developer/LogVisualizer/Public/LogVisualizerPublic.h` (Public)


#### struct `FVisualLoggerEvents`  
`struct FVisualLoggerEvents`  
_L27-33_
- L29 _public member_ `FOnFiltersChanged OnFiltersChanged;`
- L30 _public member_ `FOnLogLineSelectionChanged OnLogLineSelectionChanged;`
- L31 _public member_ `FOnKeyboardEvent OnKeyboardEvent;`
- L32 _public member_ `FGetAnimationOutlinerFillPercentageFunc GetAnimationOutlinerFillPercentageFunc;`

#### struct `FLogVisualizer`  
`struct FLogVisualizer`  
_L36-92_
- L39 _public prototype_ `void Reset();` — LogVisualizer interface
- L41 _public prototype_ `FLinearColor GetColorForCategory(int32 Index) const;`
- L42 _public prototype_ `FLinearColor GetColorForCategory(const FString& InFilterName) const;`
- L43 _public prototype_ `UWorld* GetWorld(UObject* OptionalObject = nullptr);`
- L44 _public function_ `FVisualLoggerEvents& GetEvents()`
- L46 _public function_ `void SetCurrentVisualizer(TSharedPtr<class SVisualLogger> Visualizer)`
- L48 _public function_ `void SetAnimationOutlinerFillPercentage(float FillPercentage)`
- L49 _public function_ `float GetAnimationOutlinerFillPercentage()`
- L58 _public prototype_ `int32 GetNextItem(FName RowName, int32 MoveDistance = 1);`
- L59 _public prototype_ `int32 GetPreviousItem(FName RowName, int32 MoveDistance = 1);`
- L62 _public prototype_ `void GotoNextItem(FName RowName, int32 MoveDistance = 1);` — @todo: This function currently doesn't do anything!
- L64 _public prototype_ `void GotoPreviousItem(FName RowName, int32 MoveDistance = 1);` — @todo: This function currently doesn't do anything!
- L65 _public prototype_ `void GotoFirstItem(FName RowName);`
- L66 _public prototype_ `void GotoLastItem(FName RowName);`
- L67 _public prototype_ `void GotoLastItemAnyRow();`
- L69 _public prototype_ `void UpdateCameraPosition(FName Rowname, int32 ItemIndes);`
- L71 _public prototype_ `void SeekToTime(float Time);`
- L74 _public prototype_ `static void Initialize();` — Static access
- L75 _public prototype_ `static void Shutdown();`
- L76 _public prototype_ `static FLogVisualizer& Get();`
- L79 _protected function_ `TSharedPtr<FVisualLoggerTimeSliderController> GetTimeSliderController()`
- L81 _protected member_ `static TSharedPtr< struct FLogVisualizer > StaticInstance;`
- L83 _protected member_ `TSharedPtr<FVisualLoggerTimeSliderController> TimeSliderController;`
- L84 _protected member_ `FVisualLoggerEvents VisualLoggerEvents;`
- L85 _protected member_ `TWeakPtr<class SVisualLogger> CurrentVisualizer;`
- L86 _protected member_ `float AnimationOutlinerFillPercentage;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LOGVISUALIZER_API`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFiltersSearchChanged, const FText&);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFiltersSearchChanged, const FText&);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFiltersChanged);` — DECLARE_DELEGATE(FOnFiltersChanged);
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFiltersChanged);` — DECLARE_DELEGATE(FOnFiltersChanged);
- L23 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnLogLineSelectionChanged, TSharedPtr<struct FLogEntryItem> , int64 , FName );`
- L23 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnLogLineSelectionChanged, TSharedPtr<struct FLogEntryItem> , int64 , FName );`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnKeyboardEvent, const FGeometry& , const FKeyEvent& );`
- L24 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnKeyboardEvent, const FGeometry& , const FKeyEvent& );`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal(float, FGetAnimationOutlinerFillPercentageFunc);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal(float, FGetAnimationOutlinerFillPercentageFunc);`

### `Source/Developer/LogVisualizer/Public/LogVisualizerSessionSettings.h` (Public)


#### class `ULogVisualizerSessionSettings`  
`class ULogVisualizerSessionSettings : public UObject`  
_L17-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L23 _public member_ `bool bEnableGraphsVisualization;` — `UPROPERTY(EditAnywhere, Category = "VisualLogger")` — Whether to show trivial logs, i.e. the ones with only one entry.
- L25 _public prototype_ `DECLARE_EVENT_OneParam(ULogVisualizerSessionSettings, FSettingChangedEvent, FName );`
- L26 _public function_ `FSettingChangedEvent& OnSettingChanged()`
- L30 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _private member_ `FSettingChangedEvent SettingChangedEvent;` — Holds an event delegate that is executed when a setting has changed.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LOGVISUALIZER_API`
- L25 _delegate_ `DECLARE_EVENT_OneParam(ULogVisualizerSessionSettings, FSettingChangedEvent, FName );`

### `Source/Developer/LogVisualizer/Public/LogVisualizerSettings.h` (Public)


#### struct `FCategoryFilter`  
`struct FCategoryFilter`  
_L24-44_
- reflection: `USTRUCT()`
- L28 _public function_ `FCategoryFilter() : LogVerbosity(ELogVerbosity::Type::NoLogging) , Enabled(0) , bIsInUse(0)`
- L35 _public member_ `FString CategoryName;` — `UPROPERTY(config)`
- L38 _public member_ `int32 LogVerbosity;` — `UPROPERTY(config)`
- L41 _public member_ `uint32 Enabled : 1;` — `UPROPERTY(config)`
- L43 _public member_ `uint32 bIsInUse : 1;`

#### struct `FVisualLoggerFiltersData`  
`struct FVisualLoggerFiltersData`  
_L47-62_
- reflection: `USTRUCT()`
- L52 _public member_ `FString SearchBoxFilter;` — `UPROPERTY(config)`
- L55 _public member_ `FString ObjectNameFilter;` — `UPROPERTY(config)`
- L58 _public member_ `TArray<FCategoryFilter> Categories;` — `UPROPERTY(config)`
- L61 _public member_ `TArray<FString> SelectedClasses;` — `UPROPERTY(config)`

#### struct `FVisualLoggerFilters`  
`struct FVisualLoggerFilters : public FVisualLoggerFiltersData`  
_L65-138_
- reflection: `USTRUCT()`
- inherits: `FVisualLoggerFiltersData`
- L70 _public member_ `FOnFilterCategoryAdded OnFilterCategoryAdded;`
- L71 _public member_ `FOnFilterCategoryRemoved OnFilterCategoryRemoved;`
- L73 _public prototype_ `static FVisualLoggerFilters& Get();`
- L74 _public prototype_ `static void Initialize();`
- L75 _public prototype_ `static void Shutdown();`
- L77 _public prototype_ `void Reset();`
- L78 _public prototype_ `void InitWith(const FVisualLoggerFiltersData& NewFiltersData);`
- L81 _public prototype_ `bool ShouldDisplayLine(const FVisualLogLine& Line, const bool bSearchInsideLogs) const;` — @return whether given log line should be displayed
- L87 _public prototype_ `bool ShouldDisplayCategory(FName Name, ELogVerbosity::Type Verbosity = ELogVerbosity::All) const;` — This is the preferred version to determine if a category should be displayed base on its name. @return whether given category name represents a log category we allow to be displayed at given Verbosity
- L95 _public prototype_ `bool ShouldDisplayCategoryByString(FStringView String, ELogVerbosity::Type Verbosity = ELogVerbosity::All) const;` — @return whether given String represents a log category we allow to be displayed at given Verbosity @note this function relies on case-insensitive string comparison and is slower than the FName based version that should be used when the category name is directly accessible. @see ShouldDisplayCategory
- L98 _public function_ `bool IsStringMatchingSearchFilter(const FStringView String) const` — @return whether given String is a case-insensitive match to the active search filter
- L103 _public function_ `void SetSearchString(FString InString)`
- L108 _public function_ `FString GetSearchString() const`
- L113 _public prototype_ `void AddCategory(FString InName, ELogVerbosity::Type InVerbosity);`
- L114 _public prototype_ `void RemoveCategory(FString InName);`
- L115 _public prototype_ `FCategoryFilter& GetCategoryByName(const FString& InName);`
- L116 _public prototype_ `FCategoryFilter& GetCategoryByName(const FName& InName);`
- L118 _public prototype_ `void DeactivateAllButThis(const FString& InName);`
- L119 _public prototype_ `void EnableAllCategories();`
- L121 _public prototype_ `bool MatchObjectName(FString String);`
- L122 _public prototype_ `void SelectObject(FString ObjectName);`
- L123 _public prototype_ `void RemoveObjectFromSelection(FString ObjectName);`
- L124 _public prototype_ `const TArray<FString>& GetSelectedObjects() const;`
- L126 _public prototype_ `void DisableGraphData(FName GraphName, FName DataName, bool SetAsDisabled);`
- L127 _public prototype_ `bool IsGraphDataDisabled(FName GraphName, FName DataName);`
- L130 _protected prototype_ `void OnNewItemHandler(const FVisualLoggerDBRow& BDRow, int32 ItemIndex);`
- L133 _private member_ `static TSharedPtr<FVisualLoggerFilters> StaticInstance;`
- L134 _private member_ `TMap<FName, FCategoryFilter*> FastCategoryFilterMap;`
- L135 _private member_ `TArray<FName> DisabledGraphDatas;`

#### class `ULogVisualizerSettings`  
`class ULogVisualizerSettings : public UObject`  
_L143-247_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L149 _public prototype_ `DECLARE_EVENT_OneParam(ULogVisualizerSettings, FSettingChangedEvent, FName );`
- L150 _public function_ `FSettingChangedEvent& OnSettingChanged()`
- L157 _public member_ `bool bIgnoreTrivialLogs;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to show trivial logs, i.e. the ones with only one entry.
- L161 _public member_ `int32 TrivialLogsThreshold;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger", meta = (EditCondition = "bIgnoreTrivialLogs", ClampMin = "0", ClampMax = "10", UIMin = "0", UIMax = "10"))` — Threshold for trivial Logs
- L165 _public member_ `bool bStickToRecentData;` — `UE_DEPRECATED(5.6, "This is now controlled by the auto-scroll button in the tool")` — `UPROPERTY()`
- L169 _public member_ `bool bResetDataWithNewSession;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to reset current data or not for each new session.
- L173 _public member_ `bool bShowHistogramLabelsOutside;` — `UPROPERTY(VisibleAnywhere, config, Category = "VisualLogger")` — Whether to show histogram labels inside graph or outside. Property disabled for now.
- L177 _public member_ `float DefaultCameraDistance;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger", meta = (ClampMin = "10", ClampMax = "1000", UIMin = "10", UIMax = "1000"))` — Camera distance used to setup location during reaction on log item double click
- L181 _public member_ `bool bSearchInsideLogs;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to search/filter categories or to get text vlogs into account too
- L185 _public member_ `bool bUseFilterVolumes;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to only show events occuring within one of visual logger filter volumes currently in the level
- L189 _public member_ `FColor GraphsBackgroundColor;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Background color for 2d graphs visualization
- L193 _public member_ `bool bPersistentFilters;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to store all filter settings on exit
- L197 _public member_ `bool bDrawExtremesOnGraphs;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to extreme values on graph (data has to be provided for extreme values)
- L201 _public member_ `bool bConstrainGraphToLocalMinMax;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Graphs will be scaled around local Min/Max values (values being displayed) rather than all historic data
- L205 _public member_ `bool bUsePlayersOnlyForPause;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to use PlayersOnly during Pause or not
- L209 _public member_ `bool bLogNavOctreeOnStop;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — Whether to dump Navigation Octree on Stop recording or not
- L214 _public member_ `bool bForceUniqueLogNames;` — `UPROPERTY(EditAnywhere, config, Category = "VisualLogger")` — controls how we generate log names. When set to TRUE there's a lot lower chance of name conflict, but it's more expensive
- L218 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L221 _public prototype_ `class UMaterial* GetDebugMeshMaterial();`
- L223 _public prototype_ `void SavePersistentData();`
- L225 _public prototype_ `void ClearPersistentData();`
- L227 _public prototype_ `void LoadPersistentData();`
- L229 _public prototype_ `void ConfigureVisLog();`
- L233 _protected member_ `FVisualLoggerFiltersData PersistentFilters;` — `UPROPERTY(config)`
- L237 _protected member_ `TObjectPtr<UMaterial> DebugMeshMaterialFakeLight;` — `UPROPERTY()` — A material used to render debug meshes with kind of flat shading, mostly used by Visual Logger tool.
- L241 _protected member_ `FString DebugMeshMaterialFakeLightName;` — `UPROPERTY(config)` — @todo document
- L245 _private member_ `FSettingChangedEvent SettingChangedEvent;` — Holds an event delegate that is executed when a setting has changed.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFilterCategoryAdded, FString, ELogVerbosity::Type);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFilterCategoryAdded, FString, ELogVerbosity::Type);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilterCategoryRemoved, FString);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilterCategoryRemoved, FString);`
- L149 _delegate_ `DECLARE_EVENT_OneParam(ULogVisualizerSettings, FSettingChangedEvent, FName );`

### `Source/Developer/LogVisualizer/Public/VisualLoggerRenderingActorBase.h` (Public)


#### class `AVisualLoggerRenderingActorBase`  
`class AVisualLoggerRenderingActorBase : public AActor`  
_L22-78_
- reflection: `UCLASS(MinimalAPI, config = Engine, NotBlueprintable, Transient, notplaceable, AdvancedClassDisplay)`
- inherits: `AActor`
- L26 _public prototype_ `virtual ~AVisualLoggerRenderingActorBase();`
- L61 _public function_ `virtual void IterateDebugShapes(TFunction<void(const FTimelineDebugShapes&) > Callback)` — Iterate over each active FTimelineDebugShapes, and call callback
- L62 _public function_ `virtual bool MatchCategoryFilters(const FName& CategoryName, ELogVerbosity::Type Verbosity) const`
- L65 _public function_ `virtual bool IsSelectable() const override`
- L69 _public prototype_ `void SetFarClippingDistance(double Distance);` — Allows to override the far clipping distance for all the log elements by this actor :
- L70 _public prototype_ `double GetFarClippingDistance() const;`
- L74 _protected prototype_ `void GetDebugShapes(const FVisualLogEntry& EntryItem, bool bAddEntryLocationPointer, FTimelineDebugShapes& OutDebugShapes);`
- L77 _protected member_ `UVisualLoggerRenderingComponent* RenderingComponent = nullptr;`

#### struct `AVisualLoggerRenderingActorBase::FTimelineDebugShapes`  
`struct FTimelineDebugShapes`  
_L28-58_
- L30 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> Lines;`
- L31 _public member_ `TArray<FDebugRenderSceneProxy::FCircle> Circles;`
- L32 _public member_ `TArray<FDebugRenderSceneProxy::FCone> Cones;`
- L33 _public member_ `TArray<FDebugRenderSceneProxy::FDebugBox> Boxes;`
- L34 _public member_ `TArray<FDebugRenderSceneProxy::FSphere> Points;`
- L35 _public member_ `TArray<FDebugRenderSceneProxy::FMesh> Meshes;`
- L36 _public member_ `TArray<FDebugRenderSceneProxy::FText3d> Texts;`
- L37 _public member_ `TArray<FDebugRenderSceneProxy::FWireCylinder> Cylinders;`
- L38 _public member_ `TArray<FDebugRenderSceneProxy::FCapsule> Capsules;`
- L39 _public member_ `TArray<FDebugRenderSceneProxy::FArrowLine> Arrows;`
- L40 _public member_ `TArray<FDebugRenderSceneProxy::FCoordinateSystem> CoordinateSystems;`
- L41 _public member_ `TArray<FVector> LogEntriesPath;`
- L43 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LOGVISUALIZER_API`
