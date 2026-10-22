# Developer / ProfileVisualizer

- module root: `Source/Developer/ProfileVisualizer`
- headers: 8; symbols: 227
- symbol kinds: class=9, delegate=6, function=28, macro=4, member=72, namespace=2, prototype=94, struct=1, typedef=4, variable=7
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Engine, InputCore, Slate, SlateCore, WorkspaceMenuStructure

### `Source/Developer/ProfileVisualizer/Private/ProfileVisualizerStyle.h` (Private)


#### class `FProfileVisualizerStyle`  
`class FProfileVisualizerStyle`  
_L13-32_
- desc: Declares the Editor's visual style.
- L25 _public prototype_ `static void Initialize();`
- L27 _public prototype_ `static void Shutdown();`
- L29 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L31 _public member_ `static TSharedPtr< FProfileVisualizerStyle::FStyle > StyleInstance;`

#### class `FProfileVisualizerStyle::FStyle`  
`class FStyle : public FSlateStyleSet`  
_L17-23_
- inherits: `FSlateStyleSet`
- L20 _public prototype_ `FStyle();`
- L22 _public prototype_ `void Initialize();`

### `Source/Developer/ProfileVisualizer/Private/SProfileVisualizer.h` (Private)


#### class `SProfileVisualizer`  
`class SProfileVisualizer : public SCompoundWidget`  
_L16-110_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SProfileVisualizer) : _LayoutString() , _ProfileData() , _ProfilerType()`
- L26 _public prototype_ `SLATE_ARGUMENT( FString, LayoutString ) SLATE_ARGUMENT( TSharedPtr< FVisualizerEvent >, ProfileData ) SLATE_ARGUMENT( FText, ProfilerType ) SLATE_ARGUMENT( FText, HeaderMessageText ) SLATE_ARGUMENT( FLinearColor, HeaderMessageTextColor ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L49 _private prototype_ `TSharedRef< SWidget > MakeMainMenu();` — Construct main menu
- L52 _private prototype_ `void FillFileMenu( FMenuBuilder& MenuBuilder );` — Fills the contents of 'File' menu
- L55 _private prototype_ `void FillAppMenu( FMenuBuilder& MenuBuilder );` — Fills the contents of 'Window' menu
- L58 _private prototype_ `void FillHelpMenu( FMenuBuilder& MenuBuilder );` — Fills the contents of 'Help' menu
- L61 _private prototype_ `void RouteEventSelectionChanged( TSharedPtr< FVisualizerEvent > Selection );` — Routes events from events tree tab to bar visualizer tabs
- L64 _private prototype_ `void RouteBarGraphSelectionChanged( TSharedPtr< FVisualizerEvent > Selection );` — Routes events from bar visualizer tab to events tree tabs
- L67 _private prototype_ `void RouteBarGraphExpansionChanged( TSharedPtr< FVisualizerEvent > Selection );` — Routes events from bar visualizer tab to events tree tabs
- L70 _private prototype_ `void RouteBarEventSelectionChanged( int32 Thread, TSharedPtr<FVisualizerEvent> Selection );` — Routes events from bar visualizer tab to events tree tabs
- L73 _private prototype_ `void OnBarGraphContextMenu( TSharedPtr< FVisualizerEvent > Selection, const FPointerEvent& InputEvent );` — Opens a context menu when a bar is right clicked
- L76 _private prototype_ `TSharedRef<SWidget> MakeBarVisualizerContextMenu();` — Creates bar visualizer context menu for opening new events tree tabs
- L79 _private prototype_ `void ShowGraphBarInEventsWindow( int32 WindowIndex );` — Handles creating a new events tree tab from the bar visualizer context menu
- L82 _private member_ `TSharedPtr< SSplitter > MainSplitter;` — Pointer to the main dock area of this widget
- L85 _private member_ `TSharedPtr< SBarVisualizer > BarVisualizer;` — Pointer to the bar visualizer
- L88 _private member_ `TSharedPtr< SEventsTree > EventsTree;` — Pointer to the events visualizer
- L91 _private member_ `TSharedPtr< FVisualizerEvent > ProfileData;` — Profiler results
- L94 _private member_ `TSharedPtr< FVisualizerEvent > SelectedBarGraph;` — Currently selected bar graph
- L97 _private member_ `FText ProfilerType;` — Profiler name
- L100 _private member_ `FText HeaderMessageText;` — Optional header message to display at the top of the profile window
- L103 _private member_ `FLinearColor HeaderMessageTextColor;` — Optional header message text color
- L106 _private prototype_ `FReply OnSaveClicked();` — We just clicked the save button
- L109 _private prototype_ `FReply OnLoadClicked();` — We just clicked the load button

### `Source/Developer/ProfileVisualizer/Public/ProfileVisualizerModule.h` (Public)


#### class `IProfileVisualizerModule`  
`class IProfileVisualizerModule : public IModuleInterface`  
_L9-14_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void DisplayProfileVisualizer( TSharedPtr< FVisualizerEvent > InProfileData, const TCHAR* InProfilerType, const FText& HeaderMessageText = FText::GetEmpty(), const FLinearColor& HeaderMessageTextColor = FLinearColor::White ) = 0;`

### `Source/Developer/ProfileVisualizer/Public/SBarVisualizer.h` (Public)


#### class `SBarVisualizer`  
`class SBarVisualizer : public SCompoundWidget`  
_L25-291_
- inherits: `SCompoundWidget`
- desc: Bars Visualizer. Contains a list of bars for each profiler category
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnBarGraphSelectionChanged, TSharedPtr< FVisualizerEvent > );` — Delegate used when bar graph selection changes
- L33 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnBarGraphExpansionChanged, TSharedPtr< FVisualizerEvent > );` — Delegate used when bar graph expansion changes
- L36 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnBarEventSelectionChanged, int32, TSharedPtr< FVisualizerEvent > );` — Delegate used when a single event on the bar graph is selected
- L39 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnBarGraphContextMenu, TSharedPtr< FVisualizerEvent >, const FPointerEvent& );` — Delegate used when the user right-clicks on a bar graph
- L41 _public function_ `SLATE_BEGIN_ARGS( SBarVisualizer ) : _ProfileData() , _OnBarGraphSelectionChanged() , _OnBarGraphExpansionChanged() , _OnBarEventSelectionChanged() , _OnBarGraphContextMenu()`
- L50 _public prototype_ `SLATE_ATTRIBUTE( TSharedPtr< FVisualizerEvent >, ProfileData ) SLATE_EVENT( FOnBarGraphSelectionChanged, OnBarGraphSelectionChanged ) SLATE_EVENT( FOnBarGraphExpansionChanged, OnBarGraphExpansionChanged ) SLATE_EVENT( FOnBarEventSelectionChanged, OnBarEventSelectionChanged ) SLATE_EVENT( FOnBarGraphContextMenu, OnBarGraphContextMenu ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Profiler results
- L78 _public prototype_ `void HandleEventSelectionChanged( TSharedPtr< FVisualizerEvent > Selection );` — Handles selection change in the events tree @param Selection selected event
- L87 _protected function_ `float GetMaxScrollOffsetFraction() const` — Gets the maximum scroll offset fraction value for the horizontal scrollbar @return Maximum scroll offset fraction
- L97 _protected function_ `float GetMaxGraphOffset() const` — Gets the maximum graph offset value for the graph bars @return Maximum graph offset
- L107 _protected function_ `float GetZoom() const` — Gets the actual zoom level for the graph bars @return Zoom level
- L119 _protected prototype_ `void ScrollBar_OnUserScrolled( float InScrollOffsetFraction );` — Callback for scrolling the horizontal scrollbar @param InScrollOffsetFraction Scrollbar offset fraction
- L126 _protected prototype_ `FText GetZoomLabel() const;` — Constructs the zoom label string based on the current zoom level value. @return Zoom label text
- L133 _protected prototype_ `float GetZoomValue() const;` — Callback used to get the current zoom slider value. @return Zoom slider value
- L140 _protected prototype_ `void OnSetZoomValue( float NewValue );` — Callback used to handle zoom slider @param NewValue New Zoom slider value
- L148 _protected prototype_ `void OnBarGraphSelectionChanged( TSharedPtr< FVisualizerEvent > Selection, ESelectInfo::Type SelectInfo );` — Function called when the currently selected bar graph changes @param Selection Currently selected thread events @param SelectInfo Provides context on how the selection changed
- L156 _protected prototype_ `void OnBarEventSelectionChanged( TSharedPtr< FVisualizerEvent > Selection, ESelectInfo::Type SelectInfo, int32 BarId );` — Function called when the user selects an event bar in the graph @param Selection Currently selected event @param SelectInfo Provides context on how the selection changed
- L164 _protected prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList( TSharedPtr< FVisualizerEvent > InItem, const TSharedRef< STableViewBase >& OwnerTable );` — Generates SGraphBar widget for the threads list @param InItem Graph profile events @param OwnerTable Onwer Table
- L172 _protected prototype_ `void OnGetChildrenForList( TSharedPtr<FVisualizerEvent> InItem, TArray<TSharedPtr<FVisualizerEvent> >& OutChildren);` — Generates children for the specified tree view item @param InItem Graph profile events @param OutChildren child graphs
- L181 _protected prototype_ `FReply OnBarRightClicked( const FGeometry& BarGeometry, const FPointerEvent& MouseEvent, TSharedPtr<FVisualizerEvent> Selection );` — Forwards right-click event to the visualizer main frame @param BarGeometry Graph bar geometry @param MouseEvent Current mouse event @param Selection Selected events
- L189 _protected prototype_ `void ClearBarSelection( TSharedPtr< FVisualizerEvent > GraphEvents, TSharedPtr<FVisualizerEvent> Selection );` — Recursively clears selection on all bar graphs @param GraphEvents Bar Graph events @param Selection Currently selected event
- L192 _protected prototype_ `void CreateDataView();` — Creates filtered data
- L195 _protected prototype_ `void CreateFlattenedData( TSharedPtr< FVisualizerEvent > InData, TArray< TSharedPtr< FVisualizerEvent > >& FlattenedData );` — Creates flattened data view
- L202 _protected prototype_ `void SetViewMode( EVisualizerViewMode::Type InMode );` — Sets the current view mode @param InMode New view mode
- L209 _protected function_ `bool CheckViewMode( EVisualizerViewMode::Type InMode ) const` — Given a view mode checks if it's the currently selected one @param InMode View mode to check
- L215 _protected prototype_ `FReply OnToParentClicked();` — Handles clicking on 'Back to parent' button
- L218 _protected prototype_ `FReply OnHomeClicked();` — Handles clickong on 'Home' button
- L221 _protected prototype_ `void OnBarGeometryChanged( FGeometry Geometry );` — Called when bar graph geometry (size) changes
- L224 _protected prototype_ `FText GetSelectedCategoryName() const;` — Gets the currently displayed hierarchy node name
- L227 _protected prototype_ `EVisibility GetHomeButtonVisibility() const;` — Checks if home button should be visible
- L230 _protected prototype_ `EVisibility GetToParentButtonVisibility() const;` — Checks if 'to parent' button should be visible
- L233 _protected prototype_ `FReply ExpandBar( TSharedPtr<FVisualizerEvent> BarGraphEvents );` — Called when the user clicked bar graph's expand button
- L236 _protected prototype_ `bool IsExpandable( TSharedPtr< FVisualizerEvent > InEvent );` — Checks if the selected event has children with children
- L239 _protected prototype_ `void AdjustTimeline( TSharedPtr< FVisualizerEvent > InEvent );` — Adjusts timeline to match the selected event's start and duration
- L241 _protected prototype_ `TSharedPtr< FVisualizerEvent > FindSelectedEventsParent( TArray< TSharedPtr< FVisualizerEvent > >& BarGraphs, TSharedPtr< FVisualizerEvent > Selection );`
- L244 _protected member_ `TSharedPtr< SListView< TSharedPtr< FVisualizerEvent > > > BarGraphsList;` — A pointer to the ListView of threads graph bars
- L247 _protected member_ `TSharedPtr< FVisualizerEvent > SelectedBarGraph;` — Currently selected bar graph
- L250 _protected member_ `TSharedPtr< FVisualizerEvent > ProfileData;` — Original profiler data
- L253 _protected member_ `TArray< TSharedPtr< FVisualizerEvent > > ProfileDataView;` — Profiler data view (filtered data)
- L256 _protected member_ `TArray< TSharedPtr< SGraphBar > > Graphs;` — List of all SGraphBar widgets in the tree
- L259 _protected member_ `TSharedPtr< STextBlock > ZoomLabel;` — A pointer to the Zoom Label widget
- L262 _protected member_ `TSharedPtr< SScrollBar > ScrollBar;` — A pointer to the horizontal scrollbar widget
- L265 _protected member_ `TSharedPtr< STimeline > Timeline;` — A pointer to the horizontal scrollbar widget
- L268 _protected member_ `float ZoomSliderValue;` — Zoom slider value
- L271 _protected member_ `float ScrollbarOffset;` — Scrollbar offset
- L274 _protected member_ `bool bSuppressBarGraphSelectionChangedDelegate;` — Should the OnBarGraphSelectionChangedDelegate be suppressed to avoid event loops
- L277 _protected member_ `FOnBarGraphSelectionChanged OnBarGraphSelectionChangedDelegate;` — Delegate used when bar graph selection changes
- L280 _protected member_ `FOnBarGraphExpansionChanged OnBarGraphExpansionChangedDelegate;` — Delegate used when bar graph selection changes
- L283 _protected member_ `FOnBarEventSelectionChanged OnBarEventSelectionChangedDelegate;` — Delegate used when single event on the bar graph is selected
- L286 _protected member_ `FOnBarGraphContextMenu OnBarGraphContextMenuDelegate;` — Delegate used when the user right-clicks on a bar graph
- L289 _protected member_ `EVisualizerViewMode::Type ViewMode;` — Bar visualizer view mode

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API PROFILEVISUALIZER_API`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam( FOnBarGraphSelectionChanged, TSharedPtr< FVisualizerEvent > );` — Delegate used when bar graph selection changes
- L33 _delegate_ `DECLARE_DELEGATE_OneParam( FOnBarGraphExpansionChanged, TSharedPtr< FVisualizerEvent > );` — Delegate used when bar graph expansion changes
- L36 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnBarEventSelectionChanged, int32, TSharedPtr< FVisualizerEvent > );` — Delegate used when a single event on the bar graph is selected
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnBarGraphContextMenu, TSharedPtr< FVisualizerEvent >, const FPointerEvent& );` — Delegate used when the user right-clicks on a bar graph

### `Source/Developer/ProfileVisualizer/Public/SEventsTree.h` (Public)


#### class `SEventItem`  
`class SEventItem : public SMultiColumnTableRow< TSharedPtr< FVisualizerEvent > >`  
_L20-63_
- inherits: `SMultiColumnTableRow<TSharedPtr<FVisualizerEvent>>`
- desc: Item used in task graph events list
- L24 _public function_ `SLATE_BEGIN_ARGS( SEventItem ) : _EventName() , _EventDuration(0.0)`
- L30 _public prototype_ `SLATE_ARGUMENT( FString, EventName ) SLATE_ATTRIBUTE( double, EventDuration ) SLATE_END_ARGS() virtual TSharedRef< SWidget > GenerateWidgetForColumn( const FName& ColumnName ) override;`
- L49 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView );` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L53 _private function_ `FText GetDurationText() const`
- L61 _private member_ `FString EventName;`
- L62 _private member_ `TAttribute< double > EventDuration;`

#### class `SEventsTree`  
`class SEventsTree : public SCompoundWidget`  
_L69-286_
- inherits: `SCompoundWidget`
- desc: Profiler events tree. Contains a tree of profiler event for the selected graph bar.
- L74 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnEventSelectionChanged, TSharedPtr< FVisualizerEvent > );` — Delegate used when the selection changes
- L76 _public function_ `SLATE_BEGIN_ARGS( SEventsTree ) : _ProfileData() , _OnEventSelectionChanged()`
- L82 _public prototype_ `SLATE_ATTRIBUTE( TSharedPtr< FVisualizerEvent >, ProfileData ) SLATE_EVENT( FOnEventSelectionChanged, OnEventSelectionChanged ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Profiler data
- L101 _public prototype_ `void HandleBarGraphSelectionChanged( TSharedPtr< FVisualizerEvent > Selection );` — Function called when the currently selected bar graph changes @param Selection Currently selected bar graph
- L108 _public prototype_ `void HandleBarGraphExpansionChanged( TSharedPtr< FVisualizerEvent > Selection );` — Function called when the currently expanded bar graph changes @param Selection Currently expanded bar graph
- L115 _public prototype_ `void HandleBarEventSelectionChanged( int32 Thread, TSharedPtr< FVisualizerEvent > Selection );` — Function called when the user selects an event bar in the graph @param Selection Currently selected event
- L118 _public prototype_ `FString GetTabTitle() const;` — Gets a label for this events tree tab
- L121 _public member_ `static FName NAME_NameColumn;` — Name of 'Name' column
- L124 _public member_ `static FName NAME_DurationColumn;` — Name of 'Duration' column
- L134 _protected prototype_ `void OnEventSelectionChanged( TSharedPtr< FVisualizerEvent > Selection, ESelectInfo::Type SelectInfo );` — Function called when the currently selected event in the list of thread events changes @param Selection Currently selected event @param SelectInfo Provides context on how the selection changed
- L142 _protected prototype_ `TSharedRef< ITableRow > OnGenerateWidgetForEventsList( TSharedPtr< FVisualizerEvent > InItem, const TSharedRef< STableViewBase >& OwnerTable );` — Generates SEventItem widgets for the events tree @param InItem Event to generate SEventItem for @param OwnerTable Owner Table
- L150 _protected prototype_ `void OnGetChildrenForEventsList( TSharedPtr<FVisualizerEvent> InItem, TArray<TSharedPtr<FVisualizerEvent> >& OutChildren );` — Given a profiler event, generates children for it @param InItem Event to generate children for @param OutChildren Generated children
- L157 _protected prototype_ `void OnColumnSortModeChanged( const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode );` — Handles column sorting mode change @param InSortMode New sorting mode
- L162 _protected prototype_ `EColumnSortMode::Type GetColumnSortMode( const FName ColumnId );` — @return Returns the current sort mode of the specified column
- L165 _protected prototype_ `void SortEventsList( void );` — Sorts the selected events tree
- L168 _protected prototype_ `void SortEventsList( TArray< TSharedPtr< FVisualizerEvent > >& Events );` — Recursively sorts the selected events tree
- L171 _protected prototype_ `bool RestoreEventSelection( TArray< TSharedPtr< FVisualizerEvent > >& Events );` — Restores event selection after changes to the tree
- L178 _protected prototype_ `void SetDurationUnits( EVisualizerTimeUnits::Type InUnits );` — Sets 'Duration' column time units @param InUnits New units
- L181 _protected prototype_ `int32 CountEvents( TArray< TSharedPtr< FVisualizerEvent > >& Events );` — Recursively counts all events in the tree
- L184 _protected prototype_ `void CreateSelectedEventsView();` — Given the selected events from the bar graph creates a copy of the selection applying the current view and sorting mode
- L187 _protected prototype_ `TSharedPtr< FVisualizerEvent > CreateSelectedEventsViewRecursively( TSharedPtr< FVisualizerEvent > SourceEvent );` — Helper function for creating a copy of the selected events in a hierarchy
- L190 _protected prototype_ `void CreateSelectedEventsViewRecursivelyAndFlatten( TSharedPtr< FVisualizerEvent > SourceEvent );` — Helper function for creating a copy of the selected events and flattening the hierarchy
- L193 _protected prototype_ `void CreateSelectedEventsViewRecursivelyCoalesced( TArray< TSharedPtr< FVisualizerEvent > >& SourceEvents, TArray< TSharedPtr< FVisualizerEvent > >& CopiedEvents, TSharedPtr< FVisualizerEvent > InParent );` — Helper function for creating a copy of the selected events combining leaves with the same name
- L196 _protected prototype_ `void CreateSelectedEventsViewRecursivelyFlatCoalesced( TArray< TSharedPtr< FVisualizerEvent > >& SourceEvents );` — Helper function for creating a copy of the selected events combining leaves with the same name and flattening the hierarchy
- L199 _protected function_ `bool CheckDurationUnits( EVisualizerTimeUnits::Type InUnits ) const` — Gets the currently selected time units
- L209 _protected prototype_ `void SetViewMode( EVisualizerViewMode::Type InMode );` — Sets the current view mode @param InMode New view mode
- L216 _protected function_ `bool CheckViewMode( EVisualizerViewMode::Type InMode ) const` — Given a view mode checks if it's the currently selected one @param InMode View mode to check
- L226 _protected prototype_ `double GetEventDuration( double InDurationMs ) const;` — Converts ms to currently selected time units. @param InDurationMs duration time in ms.
- L233 _protected prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called by the editable text control when the filter text is changed by the user @param	InFilterText	The new text
- L236 _protected prototype_ `void OnFilterTextCommitted( const FText& InFilterText, ETextCommit::Type CommitInfo );` — Called by the editable text control when a user presses enter or commits their text change
- L239 _protected function_ `bool FilterEvent( TSharedPtr< FVisualizerEvent > InEvent ) const` — Checks if event name passes current filter
- L246 _protected prototype_ `FText GetDurationColumnTitle() const;` — Gets the currently selected time units text
- L249 _protected member_ `TSharedPtr< STreeView< TSharedPtr< FVisualizerEvent > > > EventsListView;` — A pointer to the ListView of profiler events
- L252 _protected member_ `TSharedPtr< FVisualizerEvent > ProfileData;` — Original profiler data
- L255 _protected member_ `TSharedPtr< FVisualizerEvent > SelectedThread;` — Currently selected events for this tree
- L258 _protected member_ `TArray< TSharedPtr< FVisualizerEvent > > SelectedEvents;` — List of events for the currently selected thread
- L261 _protected member_ `TArray< TSharedPtr< FVisualizerEvent > > SelectedEventsView;` — List of events for the currently selected thread
- L264 _protected member_ `TMap< TSharedPtr< FVisualizerEvent >, TSharedPtr< FVisualizerEvent > > ViewToEventsMap;` — Maps the events generated using currently selected view and sorting modes to the source events tree
- L267 _protected member_ `FOnEventSelectionChanged OnEventSelectionChangedDelegate;` — Delegate used to notify when event selection changes
- L270 _protected member_ `FName SortByColumn;` — Specify which column to sort with
- L273 _protected member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode
- L276 _protected member_ `EVisualizerTimeUnits::Type DurationUnits;` — Currently selected time units
- L279 _protected member_ `EVisualizerViewMode::Type ViewMode;` — Currently selected view mode
- L282 _protected member_ `FString FilterText;` — Events filter text
- L285 _protected member_ `bool bSuppressSelectionChangedEvent;` — Suppresses SelectionChanged delegate to avoid event loops between graph visualizer and events tree

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API PROFILEVISUALIZER_API`
- L74 _delegate_ `DECLARE_DELEGATE_OneParam( FOnEventSelectionChanged, TSharedPtr< FVisualizerEvent > );` — Delegate used when the selection changes

### `Source/Developer/ProfileVisualizer/Public/SGraphBar.h` (Public)


#### class `SGraphBar`  
`class SGraphBar : public SLeafWidget`  
_L20-155_
- inherits: `SLeafWidget`
- desc: A graph bar widget.
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnGeometryChanged, FGeometry );` — Delegate used allotted gemetry changes
- L27 _public typedef_ `typedef TSlateDelegates< TSharedPtr< FVisualizerEvent > >::FOnSelectionChanged FOnSelectionChanged;`
- L30 _public function_ `SLATE_BEGIN_ARGS( SGraphBar ) : _OnSelectionChanged()`
- L34 _public prototype_ `SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnGeometryChanged, OnGeometryChanged ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L48 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget interface
- L49 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L50 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L51 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L52 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L60 _public prototype_ `void SetEvents( const FVisualizerEventsArray& InEvents, double InStartTime, double InTotalTime );` — Adds profiler events to draw as bars @param InEvent	Events to draw
- L67 _public function_ `void SetZoom( float InZoom )` — Sets the graph's zoom level @param NewValue	Zoom value, minimum is 1.0
- L77 _public function_ `void SetOffset( float InOffset )` — Sets the graph's offset by which all graph bars should be moved @param NewValue	Offset value
- L87 _public function_ `float GetOffset() const` — Gets the graph's offset value @return Offset value
- L97 _public function_ `FVisualizerEventsArray& GetEvents()` — Gets all events this graph will draw @return List of all events to draw
- L104 _private function_ `FORCEINLINE bool CalculateEventGeometry( FVisualizerEvent* InEvent, const FGeometry& InGeometry, float& OutStartX, float& OutEndX ) const`
- L118 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate to invoke when selection changes.
- L121 _private member_ `const FSlateBrush* BackgroundImage;` — Background image to use for the graph bar
- L124 _private member_ `const FSlateBrush* FillImage;` — Foreground image to use for the graph bar
- L127 _private member_ `const FSlateBrush* SelectedImage;` — Image to be used when drawing selected event
- L130 _private member_ `FVisualizerEventsArray Events;` — List of all events to draw
- L133 _private member_ `double StartTime;` — Start time (0.0 - 1.0)
- L136 _private member_ `double TotalTime;` — End time (0.0 - 1.0)
- L139 _private member_ `float Zoom;` — Current zoom of the graph
- L142 _private member_ `float Offset;` — Current offset of the graph
- L145 _private member_ `int32 LastHoveredEvent;` — Last hovered event index
- L148 _private member_ `FGeometry LastGeometry;` — Last allotted geometry
- L151 _private member_ `FOnGeometryChanged OnGeometryChanged;` — Delegate called when the geometry changes
- L154 _private member_ `static FColor ColorPalette[];` — Color palette for bars coloring

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PROFILEVISUALIZER_API`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam( FOnGeometryChanged, FGeometry );` — Delegate used allotted gemetry changes

### `Source/Developer/ProfileVisualizer/Public/STimeline.h` (Public)


#### class `STimeline`  
`class STimeline : public SCompoundWidget`  
_L18-139_
- inherits: `SCompoundWidget`
- desc: A timeline widget.
- L22 _public function_ `SLATE_BEGIN_ARGS( STimeline ) : _MinValue( 0.0f ) , _MaxValue( 1.0f ) , _FixedLabelSpacing(1.0)`
- L29 _public prototype_ `SLATE_ARGUMENT( float, MinValue ) SLATE_ARGUMENT( float, MaxValue ) SLATE_ARGUMENT( float, FixedLabelSpacing ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Minimum value on the timeline
- L47 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget interface
- L48 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L49 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L50 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L51 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L59 _public function_ `void SetZoom( float InZoom )` — Sets the graph's zoom level @param NewValue	Zoom value, minimum is 1.0
- L64 _public function_ `float GetZoom()`
- L73 _public function_ `void SetOffset( float InOffset )` — Sets the graph's offset by which all graph bars should be moved @param NewValue	Offset value
- L83 _public function_ `float GetOffset() const` — Gets the graph's offset value @return Offset value
- L94 _public function_ `void SetMinMaxValues(float InMin, float InMax)` — Sets the graph's min and max values. @param InMin	New min value. @param InMin	New max value.
- L100 _public function_ `void GetMinMaxValues(float &InMin, float &InMax)`
- L106 _public function_ `void SetDrawingGeometry(const FGeometry& Geometry)`
- L111 _public function_ `FGeometry GetDrawingGeometry() const`
- L119 _private member_ `const FSlateBrush* BackgroundImage;` — Background image to use for the graph bar
- L122 _private member_ `float MinValue;` — Minimum value on the timeline
- L125 _private member_ `float MaxValue;` — Maximum value on the timeline
- L128 _private member_ `float FixedLabelSpacing;` — fixed pixel spacing between centers of labels
- L131 _private member_ `float Zoom;` — Current zoom of the graph
- L134 _private member_ `float Offset;` — Current offset of the graph
- L136 _private member_ `float DrawingOffsetX;`
- L138 _private member_ `FGeometry DrawingGeometry;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PROFILEVISUALIZER_API`

### `Source/Developer/ProfileVisualizer/Public/VisualizerEvents.h` (Public)


#### struct `FVisualizerEvent`  
`struct FVisualizerEvent`  
_L46-93_
- desc: A graph event represented by SGraphBar as a single bar.
- L49 _public member_ `double Start;` — Normalized start time (0.0-1.0) of the event relative to the first event in the profile
- L52 _public member_ `double Duration;` — Normalized duration time (0.0-1.0) of the event.
- L55 _public member_ `double DurationMs;` — Duration of the event in milliseconds
- L58 _public member_ `int32 Category;` — Category this event belongs to (thread/file etc.)
- L61 _public member_ `FString EventName;` — Name of the event.
- L64 _public member_ `bool IsSelected;` — Determines if this event is selected or not.
- L67 _public member_ `uint32 ColorIndex;` — Bar color
- L70 _public member_ `TSharedPtr< FVisualizerEvent > ParentEvent;` — Parent event
- L73 _public member_ `TArray< TSharedPtr< FVisualizerEvent > > Children;` — Child events
- L75 _public function_ `FVisualizerEvent(const double InStart, const double InDuration, const double InDurationMs, const int32 InCategory, const FString& InEventName) : Start( InStart ) , Duration( InDuration ) , DurationMs( InDurationMs ) , Category( InCategory ) , EventName( InEventName ) , IsSelected( false ) , ColorIndex( 0 )`
- L87 _public prototype_ `static TSharedPtr< FVisualizerEvent > LoadVisualizerEvent(FArchive *Ar);`
- L88 _public prototype_ `static void SaveVisualizerEventRecursively(FArchive *Ar, TSharedPtr< FVisualizerEvent > VisualizerEvent);`
- L91 _private prototype_ `static TSharedPtr< FVisualizerEvent > LoadVisualizerEventRecursively(FArchive *Ar, TSharedPtr< FVisualizerEvent > InParentEvent);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace EVisualizerTimeUnits`
- L16 _typedef_ `typedef uint8 Type;` (scope `EVisualizerTimeUnits`)
- L19 _variable_ `const Type Microseconds = 0;` (scope `EVisualizerTimeUnits`) — Microseconds
- L22 _variable_ `const Type Milliseconds = 1;` (scope `EVisualizerTimeUnits`) — Milliseconds
- L25 _variable_ `const Type Seconds = 2;` (scope `EVisualizerTimeUnits`) — Seconds
- L28 _namespace_ `namespace EVisualizerViewMode`
- L30 _typedef_ `typedef uint8 Type;` (scope `EVisualizerViewMode`)
- L33 _variable_ `const Type Hierarchical = 0;` (scope `EVisualizerViewMode`) — Hierarchical
- L36 _variable_ `const Type Flat = 1;` (scope `EVisualizerViewMode`) — Flat
- L39 _variable_ `const Type Coalesced = 2;` (scope `EVisualizerViewMode`) — Coalesced
- L42 _variable_ `const Type FlatCoalesced = 3;` (scope `EVisualizerViewMode`) — FlatCoalesced
- L96 _typedef_ `typedef TArray< TSharedPtr< FVisualizerEvent > > FVisualizerEventsArray;` — Array of graph events.
