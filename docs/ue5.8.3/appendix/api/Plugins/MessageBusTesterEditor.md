# Plugins / MessageBusTesterEditor

- module root: `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor`
- headers: 10; symbols: 198
- symbol kinds: class=14, delegate=2, function=21, member=40, namespace=1, prototype=104, struct=2, typedef=14
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, EditorStyle, InputCore, MessageBusTester, MessageLog, Messaging, Networking, Projects, RenderCore, Settings, Slate, SlateCore, UdpMessaging, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/MessageBusTesterEditorModule.h` (Private)


#### class `FMessageBusTesterEditorModule`  
`class FMessageBusTesterEditorModule : public IMessageBusTesterEditorModule`  
_L35-72_
- inherits: `IMessageBusTesterEditorModule`
- L38 _public prototype_ `virtual void DisplayMessageBusTester() override;`
- L41 _public function_ `static INetworkMessagingExtension* GetMessagingStatistics()`
- L69 _public prototype_ `virtual void StartupModule() override;`
- L70 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMessageBusTesterEditor, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMessageBusTesterEditor, Log, All);`
- L20 _namespace_ `namespace MessageBusTesterHelper`
- L22 _function_ `inline IMessageBusTesterModule& Get()` (scope `MessageBusTesterHelper`)
- L28 _function_ `inline bool IsAvailable()` (scope `MessageBusTesterHelper`)

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/MessageBusTesterEditorStyle.h` (Private)


#### class `FMessageBusTesterEditorStyle`  
`class FMessageBusTesterEditorStyle : public FSlateStyleSet`  
_L10-20_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the MessageBus Tester UI
- L14 _public prototype_ `static FMessageBusTesterEditorStyle& Get();` — Access the singleton instance for this style set
- L18 _private prototype_ `FMessageBusTesterEditorStyle();`
- L19 _private prototype_ `~FMessageBusTesterEditorStyle();`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/SMessageBusTestLogger.h` (Private)


#### class `SMessageBusTesterLogEntryTableRow`  
`class SMessageBusTesterLogEntryTableRow : public SMultiColumnTableRow<FMessageBusTesterLogEntryPtr>`  
_L19-39_
- inherits: `SMultiColumnTableRow<FMessageBusTesterLogEntryPtr>`
- L21 _private typedef_ `using Super = SMultiColumnTableRow<FMessageBusTesterLogEntryPtr>;`
- L24 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTesterLogEntryTableRow)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FMessageBusTesterLogEntry>, LogEntry) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTable);`
- L31 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L33 _private prototype_ `FText GetSourceTester() const;`
- L34 _private prototype_ `FText GetLogMessage() const;`
- L35 _private prototype_ `FSlateColor GetLogMessageTextColor() const;`
- L38 _private member_ `TWeakPtr<FMessageBusTesterLogEntry> LogEntry;`

#### class `SMessageBusTestLogger`  
`class SMessageBusTestLogger : public SCompoundWidget`  
_L42-68_
- inherits: `SCompoundWidget`
- L45 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTestLogger)`
- L49 _public prototype_ `virtual ~SMessageBusTestLogger();`
- L52 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L55 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L59 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FMessageBusTesterLogEntry> InLogEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L60 _private prototype_ `void OnNewLogReceived(TSharedRef<FMessageBusTesterLogEntry> NewLog);`
- L61 _private prototype_ `void OnLogCleared();`
- L62 _private prototype_ `FReply OnLogClearedClicked();`
- L66 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageBusTesterLogEntry>>> LogEntriesListView;`
- L67 _private member_ `TArray<TSharedPtr<FMessageBusTesterLogEntry>> LogEntries;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FMessageBusTesterLogEntryPtr = TSharedPtr<FMessageBusTesterLogEntry>;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/SMessageBusTestNetwork.h` (Private)


#### struct `FSegmenterRowData`  
`struct FSegmenterRowData`  
_L22-65_
- L24 _public function_ `FSegmenterRowData(const FOutboundTransferStatistics& InStats) : Stats(InStats)`
- L30 _public function_ `bool operator < (const FSegmenterRowData &Other) const`
- L36 _public function_ `bool operator == (const FOutboundTransferStatistics& Other) const`
- L41 _public function_ `FSegmenterRowData& operator=(const FOutboundTransferStatistics& InStats)`
- L48 _public function_ `double ComputeTransferRate() const`
- L62 _public member_ `FDateTime AddTime;`
- L63 _public member_ `FDateTime UpdateTime;`
- L64 _public member_ `FOutboundTransferStatistics Stats;`

#### class `SMessageBusTesterSegmentersTableRow`  
`class SMessageBusTesterSegmentersTableRow : public SMultiColumnTableRow<TSharedRef<FSegmenterRowData>>`  
_L67-89_
- inherits: `SMultiColumnTableRow<TSharedRef<FSegmenterRowData>>`
- L69 _private typedef_ `using Super = SMultiColumnTableRow<TSharedRef<FSegmenterRowData>>;`
- L72 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTesterSegmentersTableRow)`
- L73 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSegmenterRowData>, Segmenter) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwerTableView);`
- L80 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L82 _private prototype_ `FText GetMessageId() const;`
- L83 _private prototype_ `FText GetSentSegments() const;`
- L84 _private prototype_ `FText GetAckSegments() const;`
- L85 _private prototype_ `FText GetSize() const;`
- L86 _private prototype_ `FText GetDataRate() const;`
- L88 _private member_ `TWeakPtr<FSegmenterRowData> Segmenter;`

#### class `SMessageBusTestNetwork`  
`class SMessageBusTestNetwork : public SCompoundWidget`  
_L94-135_
- inherits: `SCompoundWidget`
- desc: Panel used to show stage monitoring data
- L97 _public prototype_ `virtual ~SMessageBusTestNetwork();`
- L100 _private typedef_ `using Super = SCompoundWidget;`
- L103 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTestNetwork)`
- L104 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L108 _public prototype_ `FText GetIPAddress() const;`
- L109 _public prototype_ `FText GetAverageRTT() const;`
- L110 _public prototype_ `FText GetWindowSize() const;`
- L111 _public prototype_ `FText GetSegmentsInFlight() const;`
- L112 _public prototype_ `FText GetBytesSent() const;`
- L113 _public prototype_ `FText GetSegmentsLost() const;`
- L115 _public prototype_ `FMessageTransportStatistics GetStats() const;`
- L116 _public prototype_ `void SetNetworkViewData(TWeakPtr<FDiscoveredTesterTableRowData> View);`
- L118 _public typedef_ `using FSegmenterStatsArray = TArray<TSharedPtr<FSegmenterRowData>>;`
- L119 _public prototype_ `const FSegmenterStatsArray* GetSegmenterListSource() const;`
- L121 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L124 _private prototype_ `void HandleSegmenterUpdated(FOutboundTransferStatistics InStats);`
- L126 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FSegmenterRowData> InLogEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L128 _private member_ `TWeakPtr<FDiscoveredTesterTableRowData> Item;`
- L130 _private member_ `TSharedPtr<SListView<TSharedPtr<FSegmenterRowData>>> SegmenterListView;`
- L132 _private member_ `TMap<FGuid, FSegmenterStatsArray> AllSegmenters;`
- L134 _private member_ `TSpscQueue<FOutboundTransferStatistics> OutboundStats;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/SMessageBusTestPlan.h` (Private)


#### class `SMessageBusTestPlan`  
`class SMessageBusTestPlan : public SCompoundWidget`  
_L25-44_
- inherits: `SCompoundWidget`
- L28 _public prototype_ `virtual ~SMessageBusTestPlan() = default;`
- L31 _private typedef_ `using Super = SCompoundWidget;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTestPlan)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _private prototype_ `FReply OnStartTestClicked();`
- L42 _private prototype_ `FReply OnStopTestClicked();`
- L43 _private prototype_ `FReply OnAddPayloadClicked();`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/SMessageBusTesterPanel.h` (Private)


#### class `SMessageBusTesterPanel`  
`class SMessageBusTesterPanel : public SCompoundWidget`  
_L26-81_
- inherits: `SCompoundWidget`
- desc: Main panel for Message Bus tester.
- L29 _public prototype_ `virtual ~SMessageBusTesterPanel();`
- L31 _public prototype_ `static FName GetTabName();`
- L32 _public prototype_ `static void RegisterNomadTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L33 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L34 _public prototype_ `static TSharedPtr<SMessageBusTesterPanel> GetPanelInstance();`
- L37 _private typedef_ `using Super = SCompoundWidget;`
- L38 _private member_ `static TWeakPtr<SMessageBusTesterPanel> PanelInstance;`
- L39 _private member_ `static FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L42 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTesterPanel)`
- L43 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _public prototype_ `void HandleSelectionChange(FDiscoveredTesterTableRowDataPtr RowData);`
- L51 _private prototype_ `TSharedRef<SWidget> MakeToolbarWidget();` — Make the toolbar widgets
- L54 _private prototype_ `FText GetStartStopButtonTooltip();` — Get the tooltip text for the stop / start toolbar button.
- L57 _private prototype_ `FLinearColor GetStartStopButtonColor();` — Get the start stop button color.
- L60 _private prototype_ `FReply OnStartStopClicked();` — Handles start / stop button clicked
- L63 _private prototype_ `FReply OnClearClicked();` — Handles clear everything button clicked
- L66 _private prototype_ `FReply OnShowProjectSettingsClicked();` — Handles message bus tester settings button clicked
- L69 _private prototype_ `FText GetTesterStatus() const;` — Returns tester status
- L71 _private prototype_ `FReply OnStartTestClicked();`
- L72 _private prototype_ `FReply OnStopTestClicked();`
- L73 _private prototype_ `FReply OnAddPayloadClicked();`
- L77 _private member_ `TSharedPtr<SMessageBusTestNetwork> NetworkView;`
- L78 _private member_ `TSharedPtr<SDiscoveredTesterListView> DiscoveredTestersList;`
- L79 _private member_ `TSharedPtr<SMessageBusTestPlan> TestPlan;`
- L80 _private member_ `TSharedPtr<SMessageBusTestLogger> Logger;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/Widgets/SAddTestPlanEntryDialog.h` (Private)


#### class `SAddTestPlanEntryDialog`  
`class SAddTestPlanEntryDialog : public SCompoundWidget`  
_L9-44_
- inherits: `SCompoundWidget`
- L12 _private typedef_ `using Super = SCompoundWidget;`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAddTestPlanEntryDialog)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `static void OpenDialog();`
- L28 _private prototype_ `FReply OnAddEntryClicked();` — Called when Add button is clicked
- L31 _private prototype_ `FReply OnCancelClicked();` — Called when Cancel button is clicked
- L33 _private prototype_ `TSharedRef<SWidget> MakeButtonsWidget();`
- L36 _private prototype_ `void CloseDialog();` — Closes this dialog
- L38 _private prototype_ `void AddEntry() const;`
- L41 _private member_ `FTestPlanItem TestPlanItem;`
- L43 _private member_ `static TWeakPtr<SWindow> AddPointDialogWindow;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/Widgets/SDiscoveredTesterListView.h` (Private)


#### struct `FDiscoveredTesterTableRowData`  
`struct FDiscoveredTesterTableRowData : TSharedFromThis<FDiscoveredTesterTableRowData>`  
_L23-50_
- inherits: `TSharedFromThis<FDiscoveredTesterTableRowData>`
- desc: FDiscoveredTesterTableRowData
- L25 _public prototype_ `FDiscoveredTesterTableRowData(const FGuid& InIdentifier, const FTesterInstanceDescriptor& InDescriptor, const FMessageAddress& InAddress);`
- L28 _public prototype_ `void UpdateCachedValues();` — Fetch latest information for the associated data provider
- L31 _public prototype_ `FText GetNetSummary();` — Get a summary of current network statistics.
- L34 _public function_ `const FMessageTransportStatistics& LatestStats()` — Return the current network statistics.
- L40 _public member_ `FGuid Identifier;`
- L41 _public member_ `FTesterInstanceDescriptor Descriptor;`
- L43 _public member_ `FGuid EndpointIdentifier;`
- L44 _public member_ `FMessageAddress Address;`
- L46 _public member_ `FMessageTransportStatistics Statistics;`
- L47 _public member_ `EDiscoveredTesterConnectionState CachedConnectionState;`
- L48 _public member_ `EMessageBusTesterState CachedTestingState;`
- L49 _public member_ `FKeepAliveStatistics CachedKeepAliveStatistics;`

#### class `SDiscoveredTesterTableRow`  
`class SDiscoveredTesterTableRow : public SMultiColumnTableRow<FDiscoveredTesterTableRowDataPtr>`  
_L59-94_
- inherits: `SMultiColumnTableRow<FDiscoveredTesterTableRowDataPtr>`
- L61 _private typedef_ `using Super = SMultiColumnTableRow<FDiscoveredTesterTableRowDataPtr>;`
- L64 _public function_ `SLATE_BEGIN_ARGS(SDiscoveredTesterTableRow)`
- L65 _public prototype_ `SLATE_ARGUMENT(FDiscoveredTesterTableRowDataPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwerTableView);`
- L73 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Handles creation of each columns widget
- L76 _private prototype_ `FText GetConnectionStateGlyphs() const;` — Getters to populate the UI
- L77 _private prototype_ `FSlateColor GetConnectionStateColorAndOpacity() const;`
- L78 _private prototype_ `FText GetTestingStateGlyphs() const;`
- L79 _private prototype_ `FSlateColor GetTestingStateColorAndOpacity() const;`
- L80 _private prototype_ `FText GetMachineName() const;`
- L81 _private prototype_ `FText GetProcessId() const;`
- L82 _private prototype_ `FText GetFriendlyName() const;`
- L83 _private prototype_ `FText GetNetStats() const;`
- L84 _private prototype_ `FText GetReliableKeepAliveStats() const;`
- L85 _private prototype_ `FText GetUnreliableKeepAliveStats() const;`
- L90 _private member_ `FDiscoveredTesterTableRowDataPtr Item;` — Item to display
- L93 _private member_ `double LastRefreshTime = 0.0;` — Last time we refreshed the UI

#### class `SDiscoveredTesterListView`  
`class SDiscoveredTesterListView : public SListView<FDiscoveredTesterTableRowDataPtr>`  
_L101-151_
- inherits: `SListView<FDiscoveredTesterTableRowDataPtr>`
- L103 _private typedef_ `using Super = SListView<FDiscoveredTesterTableRowDataPtr>;`
- L106 _public function_ `SLATE_BEGIN_ARGS(SDiscoveredTesterListView)`
- L107 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L112 _public prototype_ `virtual ~SDiscoveredTesterListView();` — Cleanup ourselves
- L115 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Used to refresh cached values shown in UI
- L120 _public function_ `FOnSelectionChangedNetworkItem& OnSelectionChanged()` — Delegate that is called whenever the selection is changed on the network list.
- L126 _public prototype_ `void RebuildDiscoveredTesterList();` — Rebuild provider list from scratch
- L131 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FDiscoveredTesterTableRowDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a new row for the listview using the Item data
- L134 _private prototype_ `void HandleSelectionChanged(FDiscoveredTesterTableRowDataPtr, ESelectInfo::Type );` — Handler for when the list view selection changes.
- L136 _private prototype_ `void OnDiscoveredTesterListChanged();`
- L141 _private member_ `TArray<FDiscoveredTesterTableRowDataPtr> ListItemsSource;`
- L142 _private member_ `TArray<TWeakPtr<SDiscoveredTesterTableRow>> ListRowWidgets;`
- L145 _private member_ `bool bRebuildListRequested = false;` — Used to cache if list needs to be refreshed or not
- L148 _private member_ `double LastRefreshTime = 0.0;` — Timestamp when we last refreshed UI
- L150 _private member_ `FOnSelectionChangedNetworkItem SelectionChangeEvent;`

#### Free symbols / members of external scopes

- L53 _typedef_ `using FDiscoveredTesterTableRowDataPtr = TSharedPtr<FDiscoveredTesterTableRowData>;`
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChangedNetworkItem, FDiscoveredTesterTableRowDataPtr);`
- L96 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChangedNetworkItem, FDiscoveredTesterTableRowDataPtr);`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Private/Widgets/SMessageBusTestPlanListView.h` (Private)


#### class `SMessageBusTestPlanTableRow`  
`class SMessageBusTestPlanTableRow : public SMultiColumnTableRow<FMessageBusTestPlanTableRowDataPtr>`  
_L22-51_
- inherits: `SMultiColumnTableRow<FMessageBusTestPlanTableRowDataPtr>`
- L24 _private typedef_ `using Super = SMultiColumnTableRow<FMessageBusTestPlanTableRowDataPtr>;`
- L27 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTestPlanTableRow)`
- L28 _public prototype_ `SLATE_ARGUMENT(FMessageBusTestPlanTableRowDataPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwerTableView);`
- L36 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Handles creation of each columns widget
- L38 _private prototype_ `FReply OnRemoveEntryClicked();`
- L41 _private prototype_ `FText GetPayloadSize() const;` — Getters to populate the UI
- L42 _private prototype_ `FText GetInterval() const;`
- L47 _private member_ `FMessageBusTestPlanTableRowDataPtr Item;` — Item to display
- L50 _private member_ `double LastRefreshTime = 0.0;` — Last time we refreshed the UI

#### class `SMessageBusTestPlanListView`  
`class SMessageBusTestPlanListView : public SListView<FMessageBusTestPlanTableRowDataPtr>`  
_L57-92_
- inherits: `SListView<FMessageBusTestPlanTableRowDataPtr>`
- L59 _private typedef_ `using Super = SListView<FMessageBusTestPlanTableRowDataPtr>;`
- L62 _public prototype_ `virtual ~SMessageBusTestPlanListView();`
- L64 _public function_ `SLATE_BEGIN_ARGS(SMessageBusTestPlanListView)`
- L65 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L70 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Used to refresh cached values shown in UI
- L75 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FMessageBusTestPlanTableRowDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a new row for the listview using the Item data
- L77 _private prototype_ `void OnMessageBusTestPlanChanged();`
- L80 _private prototype_ `void RebuildMessageBusTestPlanList();` — Rebuild list from scratch
- L84 _private member_ `TArray<FMessageBusTestPlanTableRowDataPtr> ListItemsSource;`
- L85 _private member_ `TArray<TWeakPtr<SMessageBusTestPlanTableRow>> ListRowWidgets;`
- L88 _private member_ `bool bRebuildListRequested = false;` — Used to cache if list needs to be refreshed or not
- L91 _private member_ `double LastRefreshTime = 0.0;` — Timestamp when we last refreshed UI

#### Free symbols / members of external scopes

- L16 _typedef_ `using FMessageBusTestPlanTableRowDataPtr = TSharedPtr<FMessageBusTestPlanTableRowData>;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTesterEditor/Public/IMessageBusTesterEditorModule.h` (Public)


#### class `IMessageBusTesterEditorModule`  
`class IMessageBusTesterEditorModule : public IModuleInterface`  
_L7-11_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void DisplayMessageBusTester() = 0;`
