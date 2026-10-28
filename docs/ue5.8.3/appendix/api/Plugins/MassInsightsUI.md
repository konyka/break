# Plugins / MassInsightsUI

- module root: `Plugins/MassInsights/Source/MassInsightsUI`
- headers: 10; symbols: 247
- symbol kinds: class=14, delegate=3, enum=1, enumerator=2, function=11, member=87, namespace=31, prototype=88, struct=7, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, MassDeveloper, MassInsightsAnalysis, Slate, SlateCore, TraceInsights, TraceInsightsCore, TraceServices

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsTimingTrack.h` (Private)


#### class `MassInsightsUI::FMassInsightsViewCommands`  
`class FMassInsightsViewCommands : public TCommands<FMassInsightsViewCommands>`  
_L21-30_
- inherits: `TCommands<FMassInsightsViewCommands>`
- L24 _public prototype_ `FMassInsightsViewCommands();`
- L26 _public prototype_ `virtual void RegisterCommands() override;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ShowHideRegionTrack;`

#### class `MassInsightsUI::FMassInsightsSharedState`  
`class FMassInsightsSharedState : public UE::Insights::Timing::ITimingViewExtender, public TSharedFromThis<FMassInsightsSharedState>`  
_L32-57_
- inherits: `UE::Insights::Timing::ITimingViewExtender,TSharedFromThis<FMassInsightsSharedState>`
- L37 _public prototype_ `virtual ~FMassInsightsSharedState() override = default;`
- L42 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L43 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L44 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L45 _public prototype_ `virtual void ExtendOtherTracksFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InOutMenuBuilder) override;`
- L48 _public prototype_ `void ShowHideRegionsTrack();`
- L49 _public function_ `bool IsRegionsTrackVisible() const`
- L51 _public prototype_ `void BindCommands();`
- L54 _private member_ `TSharedPtr<FMassInsightsTrack> MassInsightsTrack;`
- L56 _private member_ `bool bShowHideRegionsTrack = true;`

#### class `MassInsightsUI::FMassInsightsTrack`  
`class FMassInsightsTrack : public FTimingEventsTrack`  
_L59-81_
- inherits: `FTimingEventsTrack`
- L64 _public prototype_ `FMassInsightsTrack(FMassInsightsSharedState& InSharedState);`
- L67 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L68 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L69 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L70 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L71 _public prototype_ `virtual void BuildFilteredDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L72 _public prototype_ `virtual void SetFilterConfigurator(TSharedPtr<UE::Insights::FFilterConfigurator> InFilterConfigurator) override;`
- L75 _protected prototype_ `bool FindRegionEvent(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const UE::Mass::Trace::FRegion&)> InFoundPredicate) const;`
- L78 _private member_ `TSharedPtr<UE::Insights::FFilterConfigurator> FilterConfigurator;`
- L79 _private member_ `FMassInsightsSharedState& SharedState;`
- L80 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> AnalysisSession;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mass` (scope `UE`)
- L11 _namespace_ `namespace Trace` (scope `UE::Mass`)
- L16 _namespace_ `namespace MassInsightsUI`

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/MassInsightsStyle.h` (Private)


#### class `MassInsights::FMassInsightsStyle`  
`class FMassInsightsStyle final : public FSlateStyleSet`  
_L18-43_
- inherits: `FSlateStyleSet`
- L21 _public function_ `FMassInsightsStyle() : FSlateStyleSet("MassInsightsStyle")`
- L33 _public function_ `static FMassInsightsStyle& Get()`
- L39 _public function_ `~FMassInsightsStyle()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace MassInsights`

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/Common.h` (Private)


#### class `MassInsightsUI::FTableCellFormatterTimeHMS`  
`class FTableCellFormatterTimeHMS : public UE::Insights::FTableCellValueFormatter`  
_L16-19_
- inherits: `UE::Insights::FTableCellValueFormatter`
- desc: Formats the value of a table's cell into time HHh MMm SS.SSSSSSs ie. 2h 10m 32.893027s
- L18 _private prototype_ `virtual FText FormatValue(const TOptional<UE::Insights::FTableCellValue>& InValue) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace MassInsightsUI`
- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectedArchetype, uint64);`
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectedArchetype, uint64);` (scope `MassInsightsUI`)

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/SArchetypeDetails.h` (Private)


#### class `MassInsightsUI::SArchetypeDetails`  
`class SArchetypeDetails : public SCompoundWidget`  
_L25-58_
- inherits: `SCompoundWidget`
- L28 _public prototype_ `SArchetypeDetails();`
- L29 _public function_ `SLATE_BEGIN_ARGS(SArchetypeDetails)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& _args);`
- L34 _public prototype_ `void SetArchetype(uint64 ArchetypeID);`
- L42 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(TSharedPtr<FFragmentListEntry> NodePtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _private prototype_ `void TreeView_OnGetChildren(TSharedPtr<FFragmentListEntry> InParent, TArray<TSharedPtr<FFragmentListEntry>>& OutChildren);`
- L45 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L46 _private prototype_ `void ShowColumn(const FName ColumnId);`
- L48 _private member_ `TSharedPtr<UE::Insights::FTable> Table;`
- L49 _private member_ `uint64 ArchetypeID = 0;`
- L50 _private member_ `bool bArchetypeDirty = true;`
- L51 _private member_ `bool bSortingDirty = true;`
- L52 _private member_ `bool bInvalidArchetype = true;`
- L53 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> Session;`
- L54 _private member_ `TWeakPtr<STreeView<TSharedPtr<FFragmentListEntry>>> ListView;`
- L55 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L56 _private member_ `TArray<TSharedPtr<FFragmentListEntry>> FragmentListData;`
- L57 _private member_ `TArray<TSharedPtr<FFragmentListEntry>> FilteredSortedFragmentList;`

#### struct `MassInsightsUI::SArchetypeDetails::FFragmentListEntry`  
`struct FFragmentListEntry`  
_L37-40_
- L39 _public member_ `const UE::Mass::Trace::FFragmentInfo* Fragment = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mass` (scope `UE`)
- L8 _namespace_ `namespace Trace` (scope `UE::Mass`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Insights` (scope `UE`)
- L18 _namespace_ `namespace TraceServices`
- L23 _namespace_ `namespace MassInsightsUI`

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/SEntityEventAggregationTableView.h` (Private)


#### struct `MassInsights::FEntityEventAggregateRecordHandle`  
`struct FEntityEventAggregateRecordHandle : public UE::Insights::FBaseTreeNode`  
_L21-34_
- inherits: `UE::Insights::FBaseTreeNode`
- L23 _public prototype_ `INSIGHTS_DECLARE_RTTI(FEntityEventAggregateRecordHandle, UE::Insights::FBaseTreeNode);`
- L26 _public prototype_ `explicit FEntityEventAggregateRecordHandle(int32 InRecordIndex);`
- L28 _public prototype_ `virtual const FText GetDisplayName() const override;`
- L29 _public prototype_ `int32 GetRecordIndex() const;`
- L33 _private member_ `int32 RecordIndex;` — Index used to reference event aggregation data

#### class `MassInsights::SEntityEventAggregationTableRow`  
`class SEntityEventAggregationTableRow : public SMultiColumnTableRow< TSharedPtr<FEntityEventAggregateRecordHandle> >`  
_L38-60_
- inherits: `SMultiColumnTableRow<TSharedPtr<FEntityEventAggregateRecordHandle>>`
- L40 _private typedef_ `using Super = SMultiColumnTableRow< TSharedPtr<FEntityEventAggregateRecordHandle> >;`
- L42 _public function_ `SLATE_BEGIN_ARGS(SEntityEventAggregationTableRow)`
- L43 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<UE::Insights::FTable>, TablePtr) SLATE_ARGUMENT(TSharedPtr<FEntityEventAggregateRecordHandle>, RowHandle) SLATE_ARGUMENT(TSharedPtr<SEntityEventAggregationTableView>, ViewModel) SLATE_EVENT(MassInsightsUI::FOnSelectedArchetype, OnArchetypeSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L51 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L54 _private prototype_ `void OnReleasedArchetypeButton(uint64 ArchetypeID);`
- L55 _private member_ `TSharedPtr<UE::Insights::FTable> TablePtr;`
- L56 _private member_ `TWeakPtr<SEntityEventAggregationTableView> AggregationTableView;`
- L57 _private member_ `TSharedPtr<FEntityEventAggregateRecordHandle> RecordHandle;`
- L58 _private member_ `MassInsightsUI::FOnSelectedArchetype OnArchetypeSelected;`

#### struct `MassInsights::FEntityEventSummaryRowSelectedParams`  
`struct FEntityEventSummaryRowSelectedParams`  
_L63-72_
- desc: Struct to make it easier to extend passing parameters to this delegate
- L67 _public member_ `bool IsSelected;` — False if deselected, all fields are undefined on deselection True if selected, all fields should describe the row selected
- L68 _public member_ `uint64 EntityID;`
- L69 _public member_ `double FirstEventTime;`
- L70 _public member_ `double LastEventTime;`
- L71 _public member_ `int64 TotalEvents;`

#### class `MassInsights::SEntityEventAggregationTableView`  
`class SEntityEventAggregationTableView : public SCompoundWidget`  
_L75-144_
- inherits: `SCompoundWidget`
- L79 _public prototype_ `SEntityEventAggregationTableView();`
- L80 _public prototype_ `virtual ~SEntityEventAggregationTableView();`
- L82 _public function_ `SLATE_BEGIN_ARGS(SEntityEventAggregationTableView)`
- L83 _public prototype_ `SLATE_EVENT(MassInsightsUI::FOnSelectedArchetype, OnArchetypeSelected) SLATE_EVENT(FEntityEventContainerRowSelected, OnRowSelected) SLATE_END_ARGS() void Construct(const FArguments& args);`
- L88 _public prototype_ `void Reset();`
- L90 _private prototype_ `void InsightsManager_OnSessionChanged();`
- L91 _private prototype_ `void InsightsManager_OnSessionAnalysisComplete();`
- L93 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(TSharedPtr<FEntityEventAggregateRecordHandle> NodePtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L94 _private prototype_ `void TreeView_OnGetChildren(TSharedPtr<FEntityEventAggregateRecordHandle> InParent, TArray<TSharedPtr<FEntityEventAggregateRecordHandle>>& OutChildren);`
- L96 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L98 _private prototype_ `void IncrementalUpdate();`
- L99 _private prototype_ `void ShowColumn(const FName ColumnId);`
- L100 _private prototype_ `FText GetColumnHeaderText(const FName ColumnId) const;`
- L102 _private prototype_ `FText GetStatusBarText() const;`
- L105 _private member_ `TSharedPtr<UE::Insights::FTable> Table;`
- L106 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> Session;`
- L107 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L109 _private member_ `TSharedPtr<STreeView<TSharedPtr<FEntityEventAggregateRecordHandle>>> TreeView;`
- L110 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L129 _private prototype_ `template<typename MemberPtr> constexpr auto MakeAccessor(MemberPtr Ptr);`
- L131 _private member_ `TArray<FEntityEventAggregationNode> EventAggregationRecords;`
- L133 _private member_ `TMap<uint64, int32> EntityToRecordIndexMap;`
- L135 _private member_ `uint64 EventsProcessed = 0;`
- L136 _private member_ `uint64 EstimatedEventCount = 0;`
- L138 _private member_ `bool bRebuildTree = true;`
- L140 _private member_ `TArray<TSharedPtr<FEntityEventAggregateRecordHandle>> FilteredTreeViewRows;`
- L142 _private member_ `MassInsightsUI::FOnSelectedArchetype OnArchetypeSelected;`
- L143 _private member_ `FEntityEventContainerRowSelected OnRowSelected;`

#### struct `MassInsights::SEntityEventAggregationTableView::FEntityEventAggregationNode`  
`struct FEntityEventAggregationNode`  
_L113-123_
- desc: Collated summary data about the events gathered from the application
- L115 _public member_ `uint64 EntityID;`
- L117 _public member_ `uint64 LastArchetype;` — ID of the last archetype this entity had
- L118 _public member_ `int32 Events = 0;`
- L119 _public member_ `bool bDestroyed = false;`
- L120 _public member_ `double FirstEventTime;`
- L121 _public member_ `double LastEventTime;`
- L122 _public member_ `TSharedPtr<FEntityEventAggregateRecordHandle> RowHandle;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L19 _namespace_ `namespace MassInsights`
- L73 _delegate_ `DECLARE_DELEGATE_OneParam(FEntityEventContainerRowSelected, const FEntityEventSummaryRowSelectedParams&);`
- L73 _prototype_ `DECLARE_DELEGATE_OneParam(FEntityEventContainerRowSelected, const FEntityEventSummaryRowSelectedParams&);` (scope `MassInsights`)

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/SEntityEventsTableView.h` (Private)


#### struct `MassInsightsUI::FOnSelectedEntityEventParams`  
`struct FOnSelectedEntityEventParams`  
_L21-24_
- L23 _public member_ `uint64 ProviderEventIndex;`

#### class `MassInsightsUI::SEntityEventsTableView`  
`class SEntityEventsTableView : public SCompoundWidget`  
_L30-100_
- inherits: `SCompoundWidget`
- desc: Displays a list of events for the given entities between a configured time period
- L33 _public function_ `SLATE_BEGIN_ARGS(SEntityEventsTableView)`
- L34 _public prototype_ `SLATE_EVENT(FOnSelectedEntityEvent, OnEntityEventSelected) SLATE_END_ARGS() SEntityEventsTableView();`
- L39 _public prototype_ `void Construct(const FArguments& args);`
- L40 _public prototype_ `void SetEntities(TConstArrayView<uint64> Entities);`
- L59 _private prototype_ `void InsightsManager_OnSessionChanged();`
- L61 _private prototype_ `void TreeView_OnSelectionChanged(TSharedPtr<FEventNode> EventNode, ESelectInfo::Type Arg) const;`
- L62 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(TSharedPtr<FEventNode> NodePtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L63 _private prototype_ `void TreeView_OnGetChildren(TSharedPtr<FEventNode> InParent, TArray<TSharedPtr<FEventNode>>& OutChildren);`
- L65 _private prototype_ `void IncrementalUpdate();`
- L66 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L67 _private prototype_ `void ShowColumn(const FName ColumnId);`
- L68 _private prototype_ `FText GetColumnHeaderText(const FName ColumnId) const;`
- L70 _private prototype_ `void Reset();`
- L84 _private member_ `TSharedPtr<UE::Insights::FTable> Table;`
- L85 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> Session;`
- L86 _private member_ `TSharedPtr<STreeView<TSharedPtr<FEventNode>>> TreeView;`
- L87 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L89 _private member_ `TArray<TSharedPtr<FEventNode>> Events;`
- L90 _private member_ `TArray<TSharedPtr<FEventNode>> FilteredSortedEvents;`
- L92 _private member_ `bool bRebuildTable = true;`
- L94 _private member_ `uint64 NextEventIndex = 0;` — Keeps track of the incremental progress of events to process
- L96 _private member_ `TArray<uint64> Entities;`
- L98 _private member_ `MassInsightsUI::FOnSelectedArchetype OnArchetypeSelected;`
- L99 _private member_ `FOnSelectedEntityEvent OnEntityEventSelected;`

#### class `MassInsightsUI::SEntityEventsTableView::FEventNode`  
`class FEventNode : public UE::Insights::FBaseTreeNode`  
_L43-55_
- inherits: `UE::Insights::FBaseTreeNode`
- L47 _public prototype_ `explicit FEventNode(uint64 InProviderEntityIndex);`
- L49 _public prototype_ `virtual const FText GetDisplayName() const override;`
- L51 _public prototype_ `uint64 GetProviderEventIndex() const;`
- L54 _private member_ `uint64 ProviderEntityIndex;`

#### struct `MassInsightsUI::SEntityEventsTableView::FEntityEventEntry`  
`struct FEntityEventEntry`  
_L72-82_
- L75 _public member_ `uint64 ProviderEventIndex;` — Handle to link back to the data stored in the provider
- L77 _public member_ `double EventTime;`
- L78 _public member_ `uint64 EntityId;`
- L81 _public member_ `TSharedPtr<FEventNode> Handle;` — To appease treeview

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L19 _namespace_ `namespace MassInsightsUI`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectedEntityEvent, const FOnSelectedEntityEventParams&);`
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectedEntityEvent, const FOnSelectedEntityEventParams&);` (scope `MassInsightsUI`)

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/SFragmentTableRow.h` (Private)


#### struct `MassInsights::FMassFragmentRowNodeData`  
`struct FMassFragmentRowNodeData`  
_L16-22_
- L18 _public member_ `uint64 Id;`
- L19 _public member_ `FString Name;`
- L20 _public member_ `uint32 Size;`
- L21 _public member_ `UE::Mass::Trace::EFragmentType Type;`

#### class `MassInsights::SFragmentTableRow`  
`class SFragmentTableRow : public SMultiColumnTableRow< MassFragmentInfoPtr >`  
_L24-41_
- inherits: `SMultiColumnTableRow<MassFragmentInfoPtr>`
- L26 _private typedef_ `using Super = SMultiColumnTableRow< MassFragmentInfoPtr >;`
- L28 _public function_ `SLATE_BEGIN_ARGS(SFragmentTableRow)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<UE::Insights::FTable>, TablePtr) SLATE_ARGUMENT(MassFragmentInfoPtr, FragmentInfoPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L35 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L38 _private member_ `TSharedPtr<UE::Insights::FTable> TablePtr;`
- L39 _private member_ `MassFragmentInfoPtr FragmentInfoPtr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mass` (scope `UE`)
- L9 _namespace_ `namespace Trace` (scope `UE::Mass`)
- L14 _namespace_ `namespace MassInsights`
- L23 _typedef_ `using MassFragmentInfoPtr = TSharedPtr<FMassFragmentRowNodeData>;` (scope `MassInsights`)

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/SFragmentTableView.h` (Private)


#### class `MassInsights::SFragmentTableView`  
`class SFragmentTableView : public SCompoundWidget`  
_L17-47_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `SFragmentTableView();`
- L21 _public prototype_ `virtual ~SFragmentTableView();`
- L23 _public function_ `SLATE_BEGIN_ARGS(SFragmentTableView)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L29 _private prototype_ `void InsightsManager_OnSessionChanged();`
- L30 _private prototype_ `void InsightsManager_OnSessionAnalysisComplete();`
- L31 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(MassInsights::MassFragmentInfoPtr NodePtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L32 _private prototype_ `void TreeView_OnGetChildren(MassInsights::MassFragmentInfoPtr InParent, TArray<MassInsights::MassFragmentInfoPtr>& OutChildren);`
- L34 _private prototype_ `void Reset();`
- L35 _private prototype_ `void RebuildTree(bool bResync);`
- L36 _private prototype_ `void ShowColumn(const FName ColumnId);`
- L38 _private member_ `TSharedPtr<UE::Insights::FTable> Table;`
- L39 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> Session;`
- L40 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L42 _private member_ `TSharedPtr<STreeView<MassInsights::MassFragmentInfoPtr>> TreeView;`
- L43 _private member_ `TSharedPtr<SHeaderRow> TreeViewHeaderRow;`
- L45 _private member_ `TArray<MassInsights::MassFragmentInfoPtr> FragmentInfos;`
- L46 _private member_ `TArray<MassInsights::MassFragmentInfoPtr> FilteredTreeItems;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L14 _namespace_ `namespace MassInsights`

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUI/Widgets/SMassInsightsAnalysisTab.h` (Private)


#### class `MassInsights::SMassInsightsAnalysisTab`  
`class SMassInsightsAnalysisTab : public SCompoundWidget`  
_L30-63_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS(SMassInsightsAnalysisTab)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `void SetSession( UE::Insights::Timing::ITimingViewSession* InTimingViewSession, const TraceServices::IAnalysisSession* InAnalysisSession);`
- L41 _public prototype_ `bool IsSessionSet() const;`
- L50 _private prototype_ `int32 GetSelectedViewModeIndex() const;`
- L51 _private prototype_ `ECheckBoxState IsViewModeSelected(EViewMode ViewMode) const;`
- L52 _private prototype_ `void OnViewModeCheckStateChange(ECheckBoxState State, EViewMode Mode);`
- L54 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession = nullptr;`
- L55 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L57 _private member_ `TSharedPtr<SFragmentTableView> FragmentTableView;`
- L58 _private member_ `TSharedPtr<SEntityEventAggregationTableView> EntityTimelineTableView;`
- L59 _private member_ `TWeakPtr<MassInsightsUI::SArchetypeDetails> ArchetypesDetails;`
- L60 _private member_ `TWeakPtr<MassInsightsUI::SEntityEventsTableView> TableView;`
- L62 _private member_ `EViewMode ViewMode = EViewMode::EntityEvents;`

#### enum `MassInsights::SMassInsightsAnalysisTab::EViewMode`  
`enum class EViewMode : uint8`  
_L44-48_
- L46 _public enumerator_ `EntityEvents`
- L47 _public enumerator_ `Fragments`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace MassInsightsUI`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Insights` (scope `UE`)
- L17 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L23 _namespace_ `namespace TraceServices`
- L28 _namespace_ `namespace MassInsights`

### `Plugins/MassInsights/Source/MassInsightsUI/Private/MassInsightsUIModule.h` (Private)


#### class `MassInsightsUI::FMassInsightsUIModule`  
`class FMassInsightsUIModule : public IModuleInterface`  
_L19-37_
- inherits: `IModuleInterface`
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `static FMassInsightsUIModule& Get();`
- L29 _public prototype_ `TSharedPtr<MassInsights::SMassInsightsAnalysisTab> GetAnalysisTab();`
- L32 _private prototype_ `void RegisterLayoutExtension(FInsightsMajorTabExtender& Extender);`
- L33 _private member_ `FMassInsightsSharedState TimingViewExtender;`
- L34 _private member_ `TWeakPtr<FTabManager> InsightsTabManager;`
- L36 _private member_ `TWeakPtr<MassInsights::SMassInsightsAnalysisTab> AnalysisTab;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace MassInsights`
- L15 _namespace_ `namespace MassInsightsUI`
