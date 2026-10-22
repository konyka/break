# Plugins / MultiUserServer

- module root: `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer`
- headers: 97; symbols: 1537
- symbol kinds: class=102, delegate=38, enum=11, enumerator=32, externvar=4, function=249, macro=1, member=350, namespace=171, prototype=533, struct=15, typedef=31
- DynamicallyLoadedModuleNames: ConcertSyncServer
- PrivateDependencyModuleNames: ApplicationCore, Concert, ConcertServer, ConcertSharedSlate, ConcertSyncCore, ConcertTransport, Core, CoreUObject, EngineSettings, InputCore, Messaging, OutputLog, Projects, Slate, SlateCore, StandaloneRenderer, ToolMenus, ToolWidgets, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: ConcertSyncServer

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/ConcertConsoleCommandExecutor.h` (Private)


#### class `UE::MultiUserServer::FConcertConsoleCommandExecutor`  
`class FConcertConsoleCommandExecutor : public IConsoleCommandExecutor`  
_L12-31_
- inherits: `IConsoleCommandExecutor`
- desc: Executes commands put into the output log
- L16 _public prototype_ `static FName StaticName();`
- L19 _public prototype_ `virtual FName GetName() const override;`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetDescription() const override;`
- L22 _public prototype_ `virtual FText GetHintText() const override;`
- L23 _public prototype_ `virtual void GetSuggestedCompletions(const TCHAR* Input, TArray<FConsoleSuggestion>& Out) override;`
- L24 _public prototype_ `virtual void GetExecHistory(TArray<FString>& Out) override;`
- L25 _public prototype_ `virtual bool Exec(const TCHAR* Input) override;`
- L26 _public prototype_ `virtual bool AllowHotKeyClose() const override;`
- L27 _public prototype_ `virtual bool AllowMultiLine() const override;`
- L28 _public prototype_ `virtual FInputChord GetHotKey() const override;`
- L29 _public prototype_ `virtual FInputChord GetIterateExecutorHotKey() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/ConcertServerStyle.h` (Private)


#### class `FConcertServerStyle`  
`class FConcertServerStyle`  
_L11-27_
- desc: Style data for Insights tools
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L22 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`
- L24 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L25 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/MultiUserServerConsoleVariables.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L7 _namespace_ `namespace ConsoleVariables` (scope `UE::MultiUserServer`)
- L10 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogActivityDependencyGraphOnDelete;` (scope `UE::MultiUserServer::ConsoleVariables`) — When a user requests to delete any activity, log the dependency graph (in GraphViz format)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/MultiUserServerModule.h` (Private)


#### class `UE::MultiUserServer::FConcertServerUIModule`  
`class FConcertServerUIModule : public IMultiUserServerModule`  
_L18-57_
- inherits: `IMultiUserServerModule`
- L22 _public function_ `static inline FConcertServerUIModule& Get()`
- L28 _public function_ `TSharedPtr<FModalWindowManager> GetModalWindowManager() const`
- L31 _public prototype_ `virtual void StartupModule() override ;`
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _public prototype_ `virtual void InitSlateForServer(FConcertSyncServerLoopInitArgs& InitArgs) override;`
- L42 _private member_ `FString MultiUserServerLayoutIni;` — Config path storing layout config.
- L45 _private member_ `TUniquePtr<FConcertConsoleCommandExecutor> CommandExecutor;` — Handles execution of commands
- L48 _private member_ `TSharedPtr<FModalWindowManager> ModalWindowManager;` — Manages fake modal windows
- L51 _private member_ `TSharedPtr<FConcertServerWindowController> WindowController;` — Creates and manages window. Only one instance per application.
- L53 _private prototype_ `void PreInitializeMultiUser();`
- L54 _private prototype_ `void InitializeSlateApplication(TSharedRef<IConcertSyncServer> SyncServer);`
- L56 _private prototype_ `void TickSlate(double Tick);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/ConcertTransportLogSettings.h` (Private)


#### class `UConcertTransportLogSettings`  
`class UConcertTransportLogSettings : public UObject`  
_L12-22_
- reflection: `UCLASS(config = MultiUserServerUserSettings, DefaultConfig)`
- inherits: `UObject`
- L17 _public prototype_ `static UConcertTransportLogSettings* GetSettings();`
- L21 _public member_ `ETimeFormat TimestampTimeFormat = ETimeFormat::Absolute;` — `UPROPERTY(Config)` — How to displayed FConcertLog::Timestamp

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/MultiUserServerColumnVisibilitySettings.h` (Private)


#### class `UMultiUserServerColumnVisibilitySettings`  
`class UMultiUserServerColumnVisibilitySettings : public UObject`  
_L12-80_
- reflection: `UCLASS(Config = MultiUserServerUserSettings, DefaultConfig)`
- inherits: `UObject`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColumnVisibilitySnapshotChanged, const FColumnVisibilitySnapshot& );`
- L19 _public prototype_ `UMultiUserServerColumnVisibilitySettings();`
- L21 _public prototype_ `static UMultiUserServerColumnVisibilitySettings* GetSettings();`
- L23 _public function_ `const FColumnVisibilitySnapshot& GetSessionBrowserColumnVisibility() const`
- L24 _public function_ `void SetSessionBrowserColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L25 _public function_ `FOnColumnVisibilitySnapshotChanged& OnSessionBrowserColumnVisibilityChanged()`
- L27 _public function_ `const FColumnVisibilitySnapshot& GetDeleteActivityDialogColumnVisibility() const`
- L28 _public function_ `void SetDeleteActivityDialogColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L29 _public function_ `FOnColumnVisibilitySnapshotChanged& OnDeleteActivityDialogColumnVisibility()`
- L31 _public function_ `const FColumnVisibilitySnapshot& GetArchivedActivityBrowserColumnVisibility() const`
- L32 _public function_ `void SetArchivedActivityBrowserColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L33 _public function_ `FOnColumnVisibilitySnapshotChanged& OnArchivedActivityBrowserColumnVisibility()`
- L35 _public function_ `const FColumnVisibilitySnapshot& GetLiveActivityBrowserColumnVisibility() const`
- L36 _public function_ `void SetLiveActivityBrowserColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L37 _public function_ `FOnColumnVisibilitySnapshotChanged& OnLiveActivityBrowserColumnVisibility()`
- L39 _public function_ `const FColumnVisibilitySnapshot& GetLiveSessionContentColumnVisibility() const`
- L40 _public function_ `void SetLiveSessionContentColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L41 _public function_ `FOnColumnVisibilitySnapshotChanged& OnLiveSessionContentColumnVisibility()`
- L43 _public function_ `const FColumnVisibilitySnapshot& GetTransportLogColumnVisibility() const`
- L44 _public function_ `void SetTransportLogColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L45 _public function_ `FOnColumnVisibilitySnapshotChanged& OnTransportLogColumnVisibility()`
- L47 _public function_ `const FColumnVisibilitySnapshot& GetPackageTransmissionColumnVisibility() const`
- L48 _public function_ `void SetPackageTransmissionColumnVisibility(FColumnVisibilitySnapshot NewValue)`
- L49 _public function_ `FOnColumnVisibilitySnapshotChanged& OnOnPackageTransmissionColumnVisibilityChanged()`
- L54 _private member_ `FColumnVisibilitySnapshot SessionBrowserColumnVisibility;` — `UPROPERTY(Config)`
- L55 _private member_ `FOnColumnVisibilitySnapshotChanged OnSessionBrowserColumnVisibilityChangedEvent;`
- L58 _private member_ `FColumnVisibilitySnapshot DeleteActivityDialogColumnVisibility;` — `UPROPERTY(Config)`
- L59 _private member_ `FOnColumnVisibilitySnapshotChanged OnDeleteActivityDialogColumnVisibilityEvent;`
- L62 _private member_ `FColumnVisibilitySnapshot ArchivedActivityBrowserColumnVisibility;` — `UPROPERTY(Config)`
- L63 _private member_ `FOnColumnVisibilitySnapshotChanged OnArchivedActivityBrowserColumnVisibilityEvent;`
- L66 _private member_ `FColumnVisibilitySnapshot LiveActivityBrowserColumnVisibility;` — `UPROPERTY(Config)`
- L67 _private member_ `FOnColumnVisibilitySnapshotChanged OnLiveActivityBrowserColumnVisibilityEvent;`
- L70 _private member_ `FColumnVisibilitySnapshot LiveSessionContentColumnVisibility;` — `UPROPERTY(Config)`
- L71 _private member_ `FOnColumnVisibilitySnapshotChanged OnLiveSessionContentColumnVisibilityEvent;`
- L74 _private member_ `FColumnVisibilitySnapshot TransportLogColumnVisibility;` — `UPROPERTY(Config)`
- L75 _private member_ `FOnColumnVisibilitySnapshotChanged OnTransportLogColumnVisibilityEvent;`
- L78 _private member_ `FColumnVisibilitySnapshot PackageTransmissionColumnVisibility;` — `UPROPERTY(Config)`
- L79 _private member_ `FOnColumnVisibilitySnapshotChanged OnPackageTransmissionColumnVisibilityChangedEvent;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColumnVisibilitySnapshotChanged, const FColumnVisibilitySnapshot& );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/MultiUserServerPackageTransmissionSettings.h` (Private)


#### class `UMultiUserServerPackageTransmissionSettings`  
`class UMultiUserServerPackageTransmissionSettings : public UObject`  
_L12-22_
- reflection: `UCLASS(config = MultiUserServerUserSettings, DefaultConfig)`
- inherits: `UObject`
- L17 _public prototype_ `static UMultiUserServerPackageTransmissionSettings* GetSettings();`
- L21 _public member_ `ETimeFormat TimestampTimeFormat = ETimeFormat::Absolute;` — `UPROPERTY(Config)` — How to display FPackageTransmissionEntry::Time

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/MultiUserServerUserPreferences.h` (Private)


#### class `UMultiUserServerUserPreferences`  
`class UMultiUserServerUserPreferences : public UObject`  
_L11-23_
- reflection: `UCLASS(Config = MultiUserServerUserSettings, DefaultConfig)`
- inherits: `UObject`
- L16 _public prototype_ `static UMultiUserServerUserPreferences* GetSettings();`
- L19 _public member_ `bool bWarnUserAboutMuting = true;` — `UPROPERTY(Config)`
- L22 _public member_ `bool bWarnUserAboutUnmuting = true;` — `UPROPERTY(Config)`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Browser/ConcertServerSessionBrowserController.h` (Private)


#### class `UE::MultiUserServer::FConcertServerSessionBrowserController`  
`class FConcertServerSessionBrowserController : public TSharedFromThis<FConcertServerSessionBrowserController>, public IConcertComponent, public IConcertSessionBrowserController`  
_L25-95_
- inherits: `TSharedFromThis<FConcertServerSessionBrowserController>,IConcertComponent,IConcertSessionBrowserController`
- desc: Implements controller in model-view-controller pattern.
- L33 _public prototype_ `int32 GetNumConnectedClients(const FGuid& SessionId) const;`
- L35 _public prototype_ `~FConcertServerSessionBrowserController();`
- L38 _public prototype_ `virtual void Init(const FConcertComponentInitParams& Params) override;`
- L41 _public prototype_ `void OpenTab();`
- L44 _public prototype_ `virtual TArray<FConcertServerInfo> GetServers() const override;`
- L45 _public prototype_ `virtual TArray<FActiveSessionInfo> GetActiveSessions() const override;`
- L46 _public prototype_ `virtual TArray<FArchivedSessionInfo> GetArchivedSessions() const override;`
- L47 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetActiveSessionInfo(const FGuid& AdminEndpoint, const FGuid& SessionId) const override;`
- L48 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetArchivedSessionInfo(const FGuid& AdminEndpoint, const FGuid& SessionId) const override;`
- L50 _public prototype_ `virtual void CreateSession(const FGuid& ServerAdminEndpointId, const FString& SessionName, const FString& ProjectName) override;`
- L51 _public prototype_ `virtual void ArchiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& ArchiveName, const FConcertSessionFilter& SessionFilter) override;`
- L52 _public prototype_ `virtual void RestoreSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& RestoredName, const FConcertSessionFilter& SessionFilter) override;`
- L53 _public function_ `virtual void RenameActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) override`
- L54 _public function_ `virtual void RenameArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) override`
- L55 _public prototype_ `virtual void DeleteSessions(const FGuid& ServerAdminEndpointId, const TArray<FGuid>& SessionIds) override;`
- L58 _public function_ `virtual bool CanRenameActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override` — The server operator always has permission for these actions:
- L59 _public function_ `virtual bool CanRenameArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override`
- L60 _public function_ `virtual bool CanDeleteActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override`
- L61 _public function_ `virtual bool CanDeleteArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const override`
- L62 _public function_ `virtual bool CanEverCreateSessions() const override`
- L68 _private member_ `TSharedPtr<IConcertSyncServer> ServerInstance;` — Server instance we're representing
- L70 _private member_ `TWeakPtr<FConcertServerWindowController> Owner;` — Used to open selected sessions
- L72 _private member_ `TSharedPtr<SConcertServerSessionBrowser> ConcertBrowser;`
- L74 _private prototype_ `TSharedRef<SDockTab> SpawnSessionBrowserTab(const FSpawnTabArgs& Args, TSharedPtr<SWindow> RootWindow);`
- L77 _private function_ `void OnLiveSessionCreated(bool, const IConcertServer&, TSharedRef<IConcertServerSession>)` — Update view when session list changes
- L78 _private function_ `void OnLiveSessionDestroyed(const IConcertServer&, TSharedRef<IConcertServerSession>)`
- L79 _private function_ `void OnArchivedSessionCreated(bool, const IConcertServer&, const FString&, const FConcertSessionInfo&)`
- L80 _private function_ `void OnArchivedSessionDestroyed(const IConcertServer&, const FGuid&)`
- L82 _private prototype_ `void RefreshSessionList();`
- L85 _private prototype_ `void OpenSession(const TSharedPtr<FConcertSessionTreeItem>& SessionItem);` — Session actions
- L86 _private prototype_ `void RenameActiveSessionInternal(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName);`
- L87 _private prototype_ `void RenameArchivedSessionInternal(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName);`
- L88 _private prototype_ `void RenameSessionInternal(const FGuid& SessionId, const FString& NewName, const FConcertSessionInfo& SessionInfo);`
- L89 _private prototype_ `bool DeleteSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, FText& FailureReason);`
- L91 _private prototype_ `TOptional<FString> GetSessionName(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const;`
- L93 _private prototype_ `FAsyncTaskNotificationConfig MakeAsyncNotification(const FText& Title, const FText& Details = FText::GetEmpty());`
- L94 _private prototype_ `void CloseAsyncNotification(FAsyncTaskNotification& Notification, bool bSuccess, const FText& Title, const FText& Details = FText::GetEmpty());`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Browser/SConcertServerSessionBrowser.h` (Private)


#### class `UE::MultiUserServer::SConcertServerSessionBrowser`  
`class SConcertServerSessionBrowser : public SConcertTabViewWithManagerBase`  
_L15-59_
- inherits: `SConcertTabViewWithManagerBase`
- desc: Shows a list of server sessions
- L19 _public member_ `static const FName SessionBrowserTabId;`
- L21 _public function_ `SLATE_BEGIN_ARGS(SConcertServerSessionBrowser)`
- L22 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ConstructUnderMajorTab) SLATE_ARGUMENT(TSharedPtr<SWindow>, ConstructUnderWindow) SLATE_EVENT(FSessionDelegate, DoubleClickLiveSession) SLATE_EVENT(FSessionDelegate, DoubleClickArchivedSession) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FConcertServerSessionBrowserController> InController);`
- L30 _public function_ `void RequestRefreshListNextTick()`
- L31 _public function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L45 _private member_ `TWeakPtr<FConcertServerSessionBrowserController> Controller;` — We can ask the controller about information and notify it about UI events.
- L47 _private member_ `bool bRequestedRefresh = false;`
- L49 _private member_ `TSharedPtr<FText> SearchText;`
- L50 _private member_ `TSharedPtr<SConcertSessionBrowser> SessionBrowser;`
- L52 _private prototype_ `void CreateTabs(const TSharedRef<FTabManager>& InTabManager, const TSharedRef<FTabManager::FLayout>& InLayout, const FArguments& InArgs);`
- L54 _private prototype_ `TSharedRef<SDockTab> SpawnSessionBrowserTab(const FSpawnTabArgs& InTabArgs, FSessionDelegate DoubleClickLiveSession, FSessionDelegate DoubleClickArchivedSession);`
- L55 _private prototype_ `TSharedRef<SWidget> MakeSessionTableView(FSessionDelegate DoubleClickLiveSession, FSessionDelegate DoubleClickArchivedSession);`
- L57 _private prototype_ `void RequestDeleteSession(const TArray<TSharedPtr<FConcertSessionTreeItem>>& SessionItems);`
- L58 _private prototype_ `void DeleteSessionsWithFakeModalQuestion(const FText& Message, const TArray<TSharedPtr<FConcertSessionTreeItem>>& SessionItems);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Graph/SClientNetworkGraphs.h` (Private)


#### class `UE::MultiUserServer::SClientNetworkGraphs`  
`class SClientNetworkGraphs : public SCompoundWidget`  
_L15-39_
- inherits: `SCompoundWidget`
- desc: Displays send and receive graphs
- L19 _public function_ `SLATE_BEGIN_ARGS(SClientNetworkGraphs) : _TimeRange(FTimespan::FromSeconds(15))`
- L23 _public prototype_ `SLATE_ARGUMENT(FTimespan, TimeRange) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<ITransferStatisticsModel> InTransferStatsModel);` — The last x time of traffic to display
- L31 _private member_ `TSharedPtr<ITransferStatisticsModel> TransferStatisticsModel;` — Tells us the data to display
- L33 _private member_ `TMap<EConcertTransferStatistic, TSharedPtr<SNetworkGraph>> Graphs;`
- L35 _private prototype_ `TSharedRef<SWidget> BuildGraphWidgets(const FArguments& InArgs);`
- L36 _private prototype_ `FText GetStatTextValue(EConcertTransferStatistic Stat) const;`
- L38 _private prototype_ `void OnTransferStatisticsUpdated(EConcertTransferStatistic Stat);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Graph/SCurveTimelineView.h` (Private)


#### class `SCurveTimelineView`  
`class SCurveTimelineView : public SCompoundWidget`  
_L18-92_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SCurveTimelineView) : _ViewRange(TRange<double>(0,10)) , _DesiredSize(FVector2D(100.f,20.f)) , _RenderFill(false)`
- L38 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L41 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FTimelineCurveData>, CurveData);` — Data for curve to render
- L44 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, DesiredSize);` — Desired widget size
- L47 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, CurveColor);` — Curve Color
- L50 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, FillColor);` — Fill Color
- L53 _public prototype_ `SLATE_ATTRIBUTE(bool, RenderFill);` — Enable Fill rendering
- L55 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L66 _public function_ `void SetFixedRange(float Min, float Max)` — render the curve with a fixed min/max range, rather than using the min/max from data
- L75 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L76 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L78 _protected prototype_ `int32 PaintCurve(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;`
- L80 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L81 _protected member_ `TAttribute<TSharedPtr<FTimelineCurveData>> CurveData;`
- L82 _protected member_ `TAttribute<FVector2D> DesiredSize;`
- L83 _protected member_ `TAttribute<FLinearColor> CurveColor;`
- L84 _protected member_ `TAttribute<FLinearColor> FillColor;`
- L85 _protected member_ `TAttribute<bool> RenderFill;`
- L87 _protected member_ `const FSlateBrush* WhiteBrush;`
- L89 _protected member_ `bool bUseFixedRange;`
- L90 _protected member_ `float FixedRangeMin;`
- L91 _protected member_ `float FixedRangeMax;`

#### struct `SCurveTimelineView::FTimelineCurveData`  
`struct FTimelineCurveData`  
_L21-30_
- L29 _public member_ `TArray<FCurvePoint> Points;`

#### struct `SCurveTimelineView::FTimelineCurveData::FCurvePoint`  
`struct FCurvePoint`  
_L23-27_
- L25 _public member_ `double Time;`
- L26 _public member_ `float Value;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Graph/SNetworkGraph.h` (Private)


#### class `UE::MultiUserServer::SNetworkGraph`  
`class SNetworkGraph : public SCompoundWidget`  
_L12-88_
- inherits: `SCompoundWidget`
- desc: Displays a graph from a source of floats
- L16 _public prototype_ `DECLARE_DELEGATE(FRequestViewUpdate);`
- L24 _public typedef_ `using FGetGraphData = TFunctionRef<FGraphData(uint32 Index)>;`
- L26 _public function_ `SLATE_BEGIN_ARGS(SNetworkGraph) : _MinimumYAxisRange(FMath::Pow(2.f, 13.f))`
- L31 _public prototype_ `SLATE_ATTRIBUTE(FText, CurrentNetworkValue) SLATE_ATTRIBUTE(FTimespan, DisplayedTimeRange) SLATE_ARGUMENT(FLinearColor, CurveColor) SLATE_ARGUMENT(FLinearColor, FillColor) SLATE_ARGUMENT(uint64, MinimumYAxisRange) SLATE_ARGUMENT(float, TimeSliceSize) SLATE_EVENT(FRequestViewUpdate, RequestViewUpdate) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Displayed at the top-right of the graph, e.g. S: 128 kB
- L48 _public prototype_ `void UpdateView(uint32 Num, FGetGraphData GetDataFunc);` — Updates the graph view to display the given data.
- L53 _private member_ `TAttribute<FTimespan> DisplayedTimeRange;` — All data within the last DisplayedTimeRange.GetTotalSeconds() will be displayed.
- L55 _private member_ `FRequestViewUpdate RequestViewUpdate;` — Called when it has been too long since UpdateView has last been called. Causes UpdateView to be called.
- L58 _private member_ `TSharedPtr<SCurveTimelineView> Graph;` — Renders the graph
- L60 _private member_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;` — The data displayed in Graph
- L63 _private member_ `uint64 MaxDataInDisplayTime;` — Heightest point in CurveData. Used to correctly set y-axis scale
- L65 _private member_ `FDateTime LastViewUpdate;` — Used to regularily request updates if the network does not provide them (e.g. because there just was no traffic).
- L71 _private member_ `uint64 MinimumYAxisRange;` — The graph is constantly scaled to fit the biggest value in the point set. This variable artifically sets the minimum value to which we scale.
- L76 _private member_ `float TimeSliceSize;` — The curve is divided into even segments along the x-axis. This specifies the number of seconds each segment is wide.
- L78 _private member_ `FDateTime TimeBucketAnchor;` — All time slice buckets are relative to this time which is taken when the widget is constructed.
- L81 _private prototype_ `TSharedRef<SWidget> CreateHorizontalLines() const;`
- L82 _private prototype_ `FText GetBytesDisplayText(uint64 Data) const;`
- L85 _private prototype_ `void SetTimerForForceRefresh();` — Updates the graph in an interval of TimeSliceSize in case no network data is received in that time.
- L87 _private function_ `uint64 GetMaxRange() const`

#### struct `UE::MultiUserServer::SNetworkGraph::FGraphData`  
`struct FGraphData`  
_L18-22_
- L20 _public member_ `uint64 Data;`
- L21 _public member_ `FDateTime LocalTime;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE(FRequestViewUpdate);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Item/ClientBrowserItem.h` (Private)


#### class `UE::MultiUserServer::FClientBrowserItem`  
`class FClientBrowserItem : public FConcertBrowserItemCommonImpl`  
_L20-63_
- inherits: `FConcertBrowserItemCommonImpl`
- L24 _public prototype_ `FClientBrowserItem(TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel, TSharedRef<FEndpointToUserNameCache> UserLookup, const FMessageAddress& ClientAddress, const FGuid& MessageNodeId);`
- L26 _public function_ `void OnJoinSession(const FGuid& SessionId)`
- L27 _public function_ `void OnLeaveSession()`
- L28 _public function_ `const TOptional<FGuid>& GetCurrentSession() const`
- L29 _public function_ `const FGuid& GetMessageNodeId() const`
- L31 _public function_ `void OnClientDisconnected()`
- L32 _public function_ `void OnClientReconnected()`
- L34 _public function_ `bool IsDisconnected() const` — Whether this client is no longer connected with the server
- L36 _public prototype_ `virtual FString GetDisplayName() const override;`
- L37 _public prototype_ `virtual FText GetToolTip() const override;`
- L38 _public prototype_ `virtual TSharedRef<ITransferStatisticsModel> GetTransferStatistics() const override;`
- L39 _public prototype_ `virtual TOptional<FMessageTransportStatistics> GetLatestNetworkStatistics() const override;`
- L40 _public prototype_ `virtual bool IsOnline() const override;`
- L44 _private member_ `TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel;`
- L47 _private member_ `TSharedRef<FEndpointToUserNameCache> UserLookup;` — Used to gets the client's name once it becomes available
- L50 _private member_ `TSharedRef<FClientTransferStatisticsModel> TransferStatisticsModel;` — Keeps track of the clients transfer statistics
- L53 _private member_ `FMessageAddress ClientAddress;` — Address of this client as used by the UDP messaging sytem
- L56 _private member_ `FGuid MessageNodeId;` — ID of this client in the UDP messaging system
- L59 _private member_ `TOptional<FGuid> CurrentSession;` — The session this client currently is in
- L62 _private member_ `bool bIsDisconnected = false;` — Whether this client is no longer connected with the server

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<FConcertClientInfo>, FGetClientInfo);`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<FConcertClientInfo>, FGetClientInfo);` (scope `UE::MultiUserServer`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Item/IConcertBrowserItem.h` (Private)


#### enum `UE::MultiUserServer::EConcertBrowserItemDisplayMode`  
`enum class EConcertBrowserItemDisplayMode : uint8`  
_L17-25_
- L20 _public enumerator_ `NetworkGraph = 0` — Displays the sent and read packets
- L22 _public enumerator_ `OutboundSegementTable = 1` — Displays a table showing MessageId, Sent, Acked, and Size updated in realtime for outbound UDP segments.
- L24 _public enumerator_ `InboundSegmentTable = 2` — Displays a table showing MessageId, Received, and Size updated in realtime for inbound UDP segments.

#### class `UE::MultiUserServer::IConcertBrowserItem`  
`class IConcertBrowserItem`  
_L28-52_
- desc: Implemented by items that can be displayed in the Concert Network Browser
- L33 _public prototype_ `virtual FString GetDisplayName() const = 0;` — The title of the thumbnail
- L35 _public prototype_ `virtual FText GetToolTip() const = 0;` — What to display when the thumbnail is hovered
- L37 _public prototype_ `virtual void SetDisplayMode(EConcertBrowserItemDisplayMode Value) = 0;`
- L38 _public prototype_ `virtual EConcertBrowserItemDisplayMode GetDisplayMode() const = 0;`
- L41 _public prototype_ `virtual TSharedRef<ITransferStatisticsModel> GetTransferStatistics() const = 0;` — The network statistics for this item
- L44 _public prototype_ `virtual void AppendSearchTerms(TArray<FString>& SearchTerms) const = 0;` — Adds terms this item can be searched by
- L47 _public prototype_ `virtual TOptional<FMessageTransportStatistics> GetLatestNetworkStatistics() const = 0;` — Gets the latest network statistics for this item if they are available; most likely unavailable when IsOnline returns false.
- L49 _public prototype_ `virtual bool IsOnline() const = 0;` — Whether this client is currently reachable
- L51 _public prototype_ `virtual ~IConcertBrowserItem() = default;`

#### class `UE::MultiUserServer::FConcertBrowserItemCommonImpl`  
`class FConcertBrowserItemCommonImpl : public IConcertBrowserItem`  
_L55-66_
- inherits: `IConcertBrowserItem`
- desc: Util for implementing shared logic.
- L59 _public prototype_ `virtual void SetDisplayMode(EConcertBrowserItemDisplayMode Value) override;`
- L60 _public prototype_ `virtual EConcertBrowserItemDisplayMode GetDisplayMode() const override;`
- L61 _public prototype_ `virtual void AppendSearchTerms(TArray<FString>& SearchTerms) const override;`
- L65 _private member_ `EConcertBrowserItemDisplayMode ItemDisplayMode = EConcertBrowserItemDisplayMode::NetworkGraph;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Item/ServerBrowserItem.h` (Private)


#### class `UE::MultiUserServer::FServerBrowserItem`  
`class FServerBrowserItem : public FConcertBrowserItemCommonImpl`  
_L15-34_
- inherits: `FConcertBrowserItemCommonImpl`
- L19 _public prototype_ `FServerBrowserItem(TSharedRef<IConcertServer> Server, TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel);`
- L21 _public prototype_ `virtual FString GetDisplayName() const override;`
- L22 _public prototype_ `virtual FText GetToolTip() const override;`
- L23 _public prototype_ `virtual TSharedRef<ITransferStatisticsModel> GetTransferStatistics() const override;`
- L24 _public prototype_ `virtual TOptional<FMessageTransportStatistics> GetLatestNetworkStatistics() const override;`
- L25 _public function_ `virtual bool IsOnline() const override`
- L29 _private member_ `TSharedRef<IConcertServer> Server;`
- L30 _private member_ `TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel;`
- L31 _private member_ `TSharedRef<FServerTransferStatisticsModel> ServerTransferStats;`
- L33 _private prototype_ `FMessageTransportStatistics SumUpStats(const TArray<FMessageTransportStatistics>& Stats) const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/ClientBrowserModel.h` (Private)


#### class `UE::MultiUserServer::FClientBrowserModel`  
`class FClientBrowserModel : public IClientBrowserModel`  
_L21-73_
- inherits: `IClientBrowserModel`
- L25 _public prototype_ `FClientBrowserModel(TSharedRef<IConcertServer> InServer, TSharedRef<FEndpointToUserNameCache> ClientInfoCache, TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel);`
- L29 _public prototype_ `virtual TSet<FGuid> GetSessions() const override;`
- L30 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetSessionInfo(const FGuid& SessionID) const override;`
- L31 _public function_ `virtual const TArray<TSharedPtr<FClientBrowserItem>>& GetItems() const override`
- L32 _public prototype_ `virtual void SetKeepClientsAfterDisconnect(bool bNewValue) override;`
- L33 _public function_ `virtual bool ShouldKeepClientsAfterDisconnect() const override`
- L34 _public function_ `virtual FOnClientListChanged& OnClientListChanged() override`
- L35 _public function_ `virtual FOnSessionListChanged& OnSessionCreated() override`
- L36 _public function_ `virtual FOnSessionListChanged& OnSessionDestroyed() override`
- L41 _private typedef_ `using FClientEndpointId = FGuid;`
- L42 _private typedef_ `using FMessageNodeId = FGuid;`
- L44 _private member_ `TSharedRef<IConcertServer> Server;`
- L45 _private member_ `TSharedRef<FEndpointToUserNameCache> ClientInfoCache;`
- L46 _private member_ `TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel;`
- L48 _private member_ `TArray<TSharedPtr<FClientBrowserItem>> Clients;`
- L50 _private member_ `TMap<FClientEndpointId, FMessageNodeId> EndpointToNodeId;` — Needed for when an admin endpoint disconnects - querying won't work anymore then.
- L52 _private member_ `bool bKeepClientsAfterDisconnect = true;`
- L54 _private member_ `FOnClientListChanged OnClientListChangedEvent;`
- L55 _private member_ `FOnSessionListChanged OnSessionCreatedEvent;`
- L56 _private member_ `FOnSessionListChanged OnSessionDestroyedEvent;`
- L59 _private prototype_ `void OnLiveSessionCreated(bool bSuccess, const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession);` — Session events
- L60 _private prototype_ `void OnLiveSessionDestroyed(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession) const;`
- L61 _private prototype_ `void SubscribeToClientConnectionEvents(const TSharedRef<IConcertServerSession>& InLiveSession);`
- L62 _private prototype_ `void UnsubscribeFromClientConnectionEvents(const TSharedRef<IConcertServerSession>& InLiveSession) const;`
- L65 _private prototype_ `void OnClientListUpdated(IConcertServerSession& Session, EConcertClientStatus Status, const FConcertSessionClientInfo& ClientInfo);` — Handle session clients
- L66 _private prototype_ `void OnClientJoinSession(IConcertServerSession& Session, const FGuid& EndpointId);`
- L67 _private prototype_ `void OnClientLeaveSession(IConcertServerSession& Session, const FGuid& EndpointId);`
- L68 _private prototype_ `void UpdateClientSessionId(IConcertServerSession& Session, const FGuid& EndpointId, TOptional<FGuid> SessionId);`
- L70 _private prototype_ `void OnAdminClientEndpointConnectionChanged(const FConcertEndpointContext& Context, EConcertRemoteEndpointConnection ConnectionState);`
- L71 _private prototype_ `void AddClientAdminEndpoint(const FConcertEndpointContext& Context);`
- L72 _private prototype_ `void RemoveClientAdminEndpoint(const FConcertEndpointContext& Context);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/ClientNetworkStatisticsModel.h` (Private)


#### class `UE::MultiUserServer::FClientNetworkStatisticsModel`  
`class FClientNetworkStatisticsModel : public IClientNetworkStatisticsModel`  
_L11-19_
- inherits: `IClientNetworkStatisticsModel`
- desc: Synchronizes the network statistics (the statistics are updated async).
- L16 _public prototype_ `virtual TOptional<FMessageTransportStatistics> GetLatestNetworkStatistics(const FMessageAddress& ClientAddress) const override;`
- L17 _public prototype_ `virtual bool IsOnline(const FMessageAddress& ClientAddress) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/IClientBrowserModel.h` (Private)


#### class `UE::MultiUserServer::IClientBrowserModel`  
`class IClientBrowserModel`  
_L18-48_
- desc: Decouples the UI from the server functions.
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClientListChanged, TSharedPtr<FClientBrowserItem>, EClientUpdateType);`
- L29 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionListChanged, const FGuid& );`
- L32 _public prototype_ `virtual TSet<FGuid> GetSessions() const = 0;` — Gets the IDs of all availabel IDs
- L34 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetSessionInfo(const FGuid& SessionID) const = 0;` — Gets more info about a session returned by GetSessions
- L36 _public prototype_ `virtual const TArray<TSharedPtr<FClientBrowserItem>>& GetItems() const = 0;`
- L38 _public prototype_ `virtual void SetKeepClientsAfterDisconnect(bool bNewValue) = 0;`
- L39 _public prototype_ `virtual bool ShouldKeepClientsAfterDisconnect() const = 0;`
- L42 _public prototype_ `virtual FOnClientListChanged& OnClientListChanged() = 0;` — Called when GeItems() changes its content
- L44 _public prototype_ `virtual FOnSessionListChanged& OnSessionCreated() = 0;`
- L45 _public prototype_ `virtual FOnSessionListChanged& OnSessionDestroyed() = 0;`
- L47 _public prototype_ `virtual ~IClientBrowserModel() = default;`

#### enum `UE::MultiUserServer::IClientBrowserModel::EClientUpdateType`  
`enum class EClientUpdateType : uint8`  
_L22-26_
- L24 _public enumerator_ `Added`
- L25 _public enumerator_ `Removed`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClientListChanged, TSharedPtr<FClientBrowserItem>, EClientUpdateType);`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionListChanged, const FGuid& );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/IClientNetworkStatisticsModel.h` (Private)


#### class `UE::MultiUserServer::IClientNetworkStatisticsModel`  
`class IClientNetworkStatisticsModel`  
_L18-27_
- desc: Decouples the UI from the server functions.
- L22 _public prototype_ `virtual TOptional<FMessageTransportStatistics> GetLatestNetworkStatistics(const FMessageAddress& ClientAddress) const = 0;`
- L24 _public prototype_ `virtual bool IsOnline(const FMessageAddress& ClientAddress) const = 0;` — Whether this client is currently reachable
- L26 _public prototype_ `virtual ~IClientNetworkStatisticsModel() = default;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L30 _namespace_ `namespace NetworkStatistics` (scope `UE::MultiUserServer`)
- L32 _prototype_ `FString FormatIPv4AsString(const TOptional<FMessageTransportStatistics>& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)
- L34 _prototype_ `FString FormatTotalBytesSent(const FMessageTransportStatistics& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)
- L35 _prototype_ `FString FormatTotalBytesReceived(const FMessageTransportStatistics& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)
- L36 _prototype_ `FString FormatAverageRTT(const FMessageTransportStatistics& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)
- L37 _prototype_ `FString FormatBytesInflight(const FMessageTransportStatistics& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)
- L38 _prototype_ `FString FormatWindowSize(const FMessageTransportStatistics& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)
- L39 _prototype_ `FString FormatTotalBytesLost(const FMessageTransportStatistics& Stats);` (scope `UE::MultiUserServer::NetworkStatistics`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/ITransferStatisticsModel.h` (Private)


#### enum `UE::MultiUserServer::EConcertTransferStatistic`  
`enum class EConcertTransferStatistic`  
_L15-21_
- L17 _public enumerator_ `SentToClient`
- L18 _public enumerator_ `ReceivedFromClient`
- L20 _public enumerator_ `Count`

#### struct `UE::MultiUserServer::FConcertTransferSamplePoint`  
`struct FConcertTransferSamplePoint`  
_L26-39_
- L29 _public member_ `FDateTime LocalTime;` — The time these stats were updated
- L32 _public member_ `uint64 BytesTransferred;` — The number of bytes transferred, e.g. sent, received, etc.
- L34 _public prototype_ `FConcertTransferSamplePoint() = default;`
- L35 _public function_ `explicit FConcertTransferSamplePoint(const FDateTime& Time, uint64 BytesTransferred = 0) : LocalTime(Time) , BytesTransferred(BytesTransferred)`

#### class `UE::MultiUserServer::ITransferStatisticsModel`  
`class ITransferStatisticsModel`  
_L42-61_
- desc: Keeps track of a single client's transfer statistics
- L47 _public prototype_ `virtual const TArray<FConcertTransferSamplePoint>& GetTransferStatTimeline(EConcertTransferStatistic StatisticType) const = 0;` — @return Contains the transfer statistics over time. Used for graphs.
- L49 _public prototype_ `virtual const TArray<TSharedPtr<FOutboundTransferStatistics>>& GetOutboundTransferStatsGroupedById() const = 0;` — @return Sorted descending by message ID. Every message ID is unique. Used for list views.
- L51 _public prototype_ `virtual const TArray<TSharedPtr<FInboundTransferStatistics>>& GetInboundTransferStatsGroupedById() const = 0;` — @return Sorted descending by message ID. Every message ID is unique. Used for list views.
- L54 _public prototype_ `virtual FOnTransferTimelineUpdated& OnTransferTimelineUpdated(EConcertTransferStatistic StatisticType) = 0;` — Called when GetTransferStatTimeline changes
- L56 _public prototype_ `virtual FOnTransferGroupsUpdated& OnOutboundTransferGroupsUpdated() = 0;` — Called when GetTransferStatsGroupedById changes
- L58 _public prototype_ `virtual FOnTransferGroupsUpdated& OnInboundTransferGroupsUpdated() = 0;` — Called when GetTransferStatsGroupedById changes
- L60 _public prototype_ `virtual ~ITransferStatisticsModel() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTransferTimelineUpdated);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTransferTimelineUpdated);` (scope `UE::MultiUserServer`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTransferGroupsUpdated);`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTransferGroupsUpdated);` (scope `UE::MultiUserServer`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/Transfer/ClientTransferStatisticsModel.h` (Private)


#### class `UE::MultiUserServer::FClientTransferStatisticsModel`  
`class FClientTransferStatisticsModel : public FTransferStatisticsModelBase`  
_L10-20_
- inherits: `FTransferStatisticsModelBase`
- L14 _public prototype_ `FClientTransferStatisticsModel(const FMessageAddress& ClientAddress);`
- L18 _protected prototype_ `static bool ShouldIncludeOutboundStat(const FOutboundTransferStatistics& Item, const FMessageAddress ClientAddress);`
- L19 _protected prototype_ `static bool ShouldIncludeInboundStat(const FInboundTransferStatistics& Item, const FMessageAddress ClientAddress);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/Transfer/ServerTransferStatisticsModel.h` (Private)


#### class `UE::MultiUserServer::FServerTransferStatisticsModel`  
`class FServerTransferStatisticsModel : public FTransferStatisticsModelBase`  
_L9-20_
- inherits: `FTransferStatisticsModelBase`
- L13 _public function_ `FServerTransferStatisticsModel() : FTransferStatisticsModelBase( TClientTransferStatTracker<FOutboundTransferStatistics>::FShouldInclude::CreateLambda([](const auto&){ return true; }), TClientTransferStatTracker<FInboundTransferStatistics>::FShouldInclude::CreateLambda([](const auto& ){ return true; }) )`
- L16 _public function_ `TClientTransferStatTracker<FOutboundTransferStatistics>::FShouldInclude::CreateLambda([](const auto&){ return true; }), TClientTransferStatTracker<FInboundTransferStatistics>::FShouldInclude::CreateLambda([](const auto& ){ return true; }) )`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Models/Transfer/TransferStatisticsModel.h` (Private)


#### class `UE::MultiUserServer::TClientTransferStatTracker`  
`template<typename TStatBase> class TClientTransferStatTracker`  
_L13-176_
- L31 _private typedef_ `using FMessageId = decltype(FOutboundTransferStatistics::MessageId);`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldInclude, const TStatBase&);`
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(uint64, FStatGetter, const TStatBase&);`
- L38 _public function_ `TClientTransferStatTracker(FShouldInclude ShouldIncludeFunc, FStatGetter StatGetterFunc) : ShouldIncludeFunc(MoveTemp(ShouldIncludeFunc)) , StatGetterFunc(MoveTemp(StatGetterFunc))`
- L43 _public function_ `void OnTransferUpdatedFromThread(TStatBase TransferStatistics)`
- L51 _public function_ `bool Tick(float DeltaTime)`
- L76 _public function_ `FOnTransferTimelineUpdated& GetOnTimelineUpdatedDelegates()`
- L77 _public function_ `FOnTransferGroupsUpdated& GetOnGroupsUpdatedDelegate()`
- L78 _public function_ `const TArray<FConcertTransferSamplePoint>& GetTransferStatisticsTimeline() const`
- L79 _public function_ `const TArray<TSharedPtr<TStatBase>>& GetTransferStatisticsGroupedById() const`
- L83 _private member_ `TSpscQueue<TStatItem> AsyncStatQueue;`
- L85 _private member_ `TArray<FConcertTransferSamplePoint> TransferStatisticsTimeline;`
- L86 _private member_ `TMap<FMessageId, FIncompleteMessageData> IncompleteStatsUntilNow;`
- L88 _private member_ `TArray<TSharedPtr<TStatBase>> TransferStatisticsGroupedById;`
- L89 _private member_ `TMap<FMessageId, FDateTime> LastUpdateGroupUpdates;`
- L91 _private member_ `FOnTransferTimelineUpdated OnTimelineUpdatedDelegates;`
- L92 _private member_ `FOnTransferGroupsUpdated OnGroupsUpdatedDelegate;`
- L94 _private member_ `FShouldInclude ShouldIncludeFunc;`
- L95 _private member_ `FStatGetter StatGetterFunc;`
- L97 _private function_ `static bool IsTooOld(const FDateTime& StatCreationTime, const FDateTime& Now)`
- L103 _private function_ `bool RemoveOldStatTimelines()`
- L128 _private function_ `bool RemoveOldGroupedStats()`
- L145 _private function_ `void UpdateStatTimeline(const TStatBase& TransferStatistics, FConcertTransferSamplePoint& SamplingThisTick)`
- L158 _private function_ `void UpdateGroupedStats(const TStatBase& TransferStatistics)`

#### struct `UE::MultiUserServer::TClientTransferStatTracker::FIncompleteMessageData`  
`struct FIncompleteMessageData`  
_L15-19_
- L17 _public member_ `uint64 BytesTransferredSoFar;`
- L18 _public member_ `FDateTime LastUpdate;`

#### struct `UE::MultiUserServer::TClientTransferStatTracker::TStatItem`  
`struct TStatItem : TStatBase`  
_L21-29_
- inherits: `TStatBase`
- L23 _public member_ `FDateTime LocalTime;`
- L25 _public function_ `TStatItem(const FDateTime& LocalTime, TStatBase Data) : TStatBase(Data) , LocalTime(LocalTime)`

#### class `UE::MultiUserServer::FTransferStatisticsModelBase`  
`class FTransferStatisticsModelBase : public ITransferStatisticsModel`  
_L178-205_
- inherits: `ITransferStatisticsModel`
- L182 _public prototype_ `FTransferStatisticsModelBase( TClientTransferStatTracker<FOutboundTransferStatistics>::FShouldInclude ShouldIncludeOutboundFunc, TClientTransferStatTracker<FInboundTransferStatistics>::FShouldInclude ShouldIncludeInboundFunc );`
- L188 _public prototype_ `virtual const TArray<FConcertTransferSamplePoint>& GetTransferStatTimeline(EConcertTransferStatistic StatisticType) const override;`
- L189 _public function_ `virtual const TArray<TSharedPtr<FOutboundTransferStatistics>>& GetOutboundTransferStatsGroupedById() const override`
- L190 _public function_ `virtual const TArray<TSharedPtr<FInboundTransferStatistics>>& GetInboundTransferStatsGroupedById() const override`
- L191 _public prototype_ `virtual FOnTransferTimelineUpdated& OnTransferTimelineUpdated(EConcertTransferStatistic StatisticType) override;`
- L192 _public function_ `virtual FOnTransferGroupsUpdated& OnOutboundTransferGroupsUpdated() override`
- L193 _public function_ `virtual FOnTransferGroupsUpdated& OnInboundTransferGroupsUpdated() override`
- L197 _private member_ `FTSTicker::FDelegateHandle InboundTickHandle;`
- L198 _private member_ `FTSTicker::FDelegateHandle OutboundTickHandle;`
- L203 _private member_ `TSharedRef<TClientTransferStatTracker<FOutboundTransferStatistics>> OutboundStatTracker;` — These are used for subscribing to INetworkMessagingExtension - therefore they are shared pointers for synchronization purposes Prevents race condition when destructor is called and UDP thread attempts to call the callbacks
- L204 _private member_ `TSharedRef<TClientTransferStatTracker<FInboundTransferStatistics>> InboundStatTracker;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldInclude, const TStatBase&);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(uint64, FStatGetter, const TStatBase&);`
- L162 _function_ `` (scope `UE::MultiUserServer::TClientTransferStatTracker::UpdateGroupedStats`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/SClientNetworkStats.h` (Private)


#### class `UE::MultiUserServer::SClientNetworkStats`  
`class SClientNetworkStats : public SCompoundWidget`  
_L16-50_
- inherits: `SCompoundWidget`
- desc: Displays statistics about a client connection in a table like format: send, receive, RTT, Inflight, and Loss.
- L20 _public function_ `SLATE_BEGIN_ARGS(SClientNetworkStats)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FText>, HighlightText) SLATE_ATTRIBUTE(TOptional<FMessageTransportStatistics>, NetworkStatistics) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L33 _private member_ `TAttribute<TOptional<FMessageTransportStatistics>> NetworkStatistics;`
- L36 _private member_ `TSharedPtr<FText> HighlightText;` — The text to highlight
- L38 _private member_ `TSharedPtr<STextBlock> SendText;`
- L39 _private member_ `TSharedPtr<STextBlock> ReceiveText;`
- L40 _private member_ `TSharedPtr<STextBlock> RoundTripTimeText;`
- L41 _private member_ `TSharedPtr<STextBlock> InflightText;`
- L42 _private member_ `TSharedPtr<STextBlock> LossText;`
- L43 _private member_ `TSharedPtr<STextBlock> WindowSize;`
- L45 _private prototype_ `void UpdateStatistics(const FMessageTransportStatistics& Statistics) const;`
- L47 _private prototype_ `TSharedRef<SWidget> CreateStatTable();`
- L48 _private prototype_ `void AddStatistic(const TSharedRef<SHorizontalBox>& AddTo, const FText& StatisticName, const FText& StatisticToolTip, TSharedPtr<STextBlock>& AssignTo);`
- L49 _private prototype_ `void AddStatistic(SHorizontalBox::FScopedWidgetSlotArguments& Slot, const FText& StatisticName, const FText& StatisticToolTip, TSharedPtr<STextBlock>& AssignTo);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/SConcertBrowserItem.h` (Private)


#### class `UE::MultiUserServer::SConcertBrowserItem`  
`class SConcertBrowserItem : public SCompoundWidget`  
_L16-51_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SConcertBrowserItem)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FText>, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IConcertBrowserItem> InClientItem);`
- L26 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Updates LastAvailableIp
- L31 _private member_ `TSharedPtr<IConcertBrowserItem> Item;` — What we're displaying
- L34 _private member_ `TSharedPtr<FText> HighlightText;` — The text to highlight
- L36 _private member_ `TSharedPtr<STextBlock> ClientName;`
- L37 _private member_ `TSharedPtr<SClientNetworkStats> NetworkStats;`
- L38 _private member_ `TSharedPtr<STextBlock> ClientIP4;`
- L41 _private member_ `TOptional<FString> LastAvailableIp;` — Stores the IP address once it becomes it available. Used so we can continue displaying it when the client goes offline.
- L43 _private prototype_ `TSharedRef<SWidget> CreateHeader();`
- L44 _private prototype_ `TSharedRef<SWidget> CreateContentArea();`
- L45 _private prototype_ `TSharedRef<SWidget> CreateStats();`
- L46 _private prototype_ `TSharedRef<SWidget> CreateFooter();`
- L48 _private prototype_ `FText GetIpText() const;`
- L50 _private prototype_ `const FSlateBrush* GetBackgroundImage() const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/SConcertNetworkBrowser.h` (Private)


#### class `UE::MultiUserServer::SConcertNetworkBrowser`  
`class SConcertNetworkBrowser : public SCompoundWidget`  
_L32-112_
- inherits: `SCompoundWidget`
- desc: Presents a view of client thumbnails, which include important statistics. Clients can be right-clicked, opening a context menu, and double clicked, opening a new tab with a log view.
- L36 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnClientDoubleClicked, const FGuid& );`
- L37 _public prototype_ `DECLARE_DELEGATE(FOnServerDoubleClicked);`
- L39 _public function_ `SLATE_BEGIN_ARGS(SConcertNetworkBrowser)`
- L41 _public prototype_ `SLATE_NAMED_SLOT(FArguments, RightOfSearch) SLATE_EVENT(FOnServerDoubleClicked, OnServerDoubleClicked) SLATE_EVENT(FOnClientDoubleClicked, OnClientDoubleClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IClientBrowserModel> InBrowserModel, TSharedRef<IClientNetworkStatisticsModel> NetworkStatisticsModel, TSharedRef<IConcertServer> Server);` — Extension point to the right of the search bar
- L49 _public prototype_ `void ShowOnlyClientsFromSession(const FGuid& SessionId);` — Shows only the clients connected to the given session ID
- L53 _private typedef_ `using FSessionId = FGuid;`
- L54 _private typedef_ `using FMessagingNodeId = FGuid;`
- L55 _private typedef_ `using FBrowserItemTextFilter = TTextFilter<const TSharedPtr<IConcertBrowserItem>&>;`
- L58 _private member_ `TSharedPtr<IClientBrowserModel> BrowserModel;` — Retrieves clients and live sessions
- L61 _private member_ `TSet<FSessionId> AllowedSessions;` — Contains the guid of every session we're allowed to display
- L63 _private member_ `bool bShowAllSessions = true;` — Should all sessions be shown?
- L65 _private member_ `bool bShowSessionlessClients = true;` — Should admin endpoints be shown?
- L67 _private member_ `TSharedPtr<FServerBrowserItem> ServerItem;`
- L69 _private member_ `TArray<TSharedPtr<FClientBrowserItem>> DisplayedClientItems;` — Filtered version of IClientBrowserModel::GetItems. Added to DisplayItems.
- L71 _private member_ `TArray<TSharedPtr<IConcertBrowserItem>> DisplayedItems;` — Source array for TileView - fitlered version of IClientBrowserModel::GetItems
- L73 _private member_ `TSharedPtr<STileView<TSharedPtr<IConcertBrowserItem>>> TileView;` — Visualizes all the items
- L76 _private member_ `TSharedPtr<FText> HighlightText;` — Filtering
- L77 _private member_ `TSharedPtr<FBrowserItemTextFilter> SessionFilter;`
- L79 _private member_ `FOnServerDoubleClicked OnServerDoubleClicked;`
- L80 _private member_ `FOnClientDoubleClicked OnClientDoubleClicked;`
- L82 _private prototype_ `TSharedRef<SWidget> CreateSearchArea(const FArguments& InArgs);`
- L83 _private prototype_ `TSharedRef<SWidget> CreateOptionsButton();`
- L84 _private prototype_ `TSharedRef<SWidget> CreateTileView();`
- L86 _private prototype_ `TSharedRef<SWidget> CreateOptionsButtonMenu();`
- L87 _private prototype_ `void ToggleShouldKeepDisconnected();`
- L90 _private prototype_ `void OnSessionCreated(const FGuid& SessionId);` — Model events
- L91 _private prototype_ `void OnSessionDestroyed(const FGuid& SessionId);`
- L92 _private prototype_ `void OnClientListChanged(TSharedPtr<FClientBrowserItem> Item, IClientBrowserModel::EClientUpdateType UpdateType);`
- L95 _private prototype_ `TSharedRef<SWidget> CreateSessionFilterOptionMenu();` — Combo button
- L97 _private prototype_ `FText GetErrorMessageText() const;`
- L100 _private prototype_ `TSharedRef<ITableRow> MakeTileViewWidget(TSharedPtr<IConcertBrowserItem> ClientItem, const TSharedRef<STableViewBase>& OwnerTable);` — TileView events
- L101 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent();`
- L102 _private prototype_ `void AddDisplayModeEntry(FMenuBuilder& MenuBuilder, EConcertBrowserItemDisplayMode DisplayMode, FText Title, FText Tooltip) const;`
- L103 _private prototype_ `void OnListMouseButtonDoubleClick(TSharedPtr<IConcertBrowserItem> ClientItem);`
- L106 _private prototype_ `void AllowAllSessions();` — Filtering
- L107 _private prototype_ `void DisallowAllSessions();`
- L108 _private prototype_ `void UpdateTileViewFromAllowedSessions();`
- L109 _private prototype_ `bool PassesFilter(const TSharedPtr<FServerBrowserItem>& Client) const;`
- L110 _private prototype_ `bool PassesFilter(const TSharedPtr<FClientBrowserItem>& Client) const;`
- L111 _private prototype_ `void GenerateSearchTerms(const TSharedPtr<IConcertBrowserItem>& Client, TArray<FString>& SearchTerms) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClientDoubleClicked, const FGuid& );`
- L37 _delegate_ `DECLARE_DELEGATE(FOnServerDoubleClicked);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Table/SClientInboundTransferStatTable.h` (Private)


#### class `UE::MultiUserServer::SClientInboundTransferStatTable`  
`class SClientInboundTransferStatTable : public SCompoundWidget`  
_L21-40_
- inherits: `SCompoundWidget`
- desc: Displays FOutboundTransferStatistics as they are updated by INetworkMessagingExtension.
- L25 _public function_ `SLATE_BEGIN_ARGS(SClientInboundTransferStatTable)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<ITransferStatisticsModel> InStatsModel);`
- L34 _private member_ `TSharedPtr<ITransferStatisticsModel> StatsModel;` — Tells us when the transfer stats have changed
- L36 _private member_ `TSharedPtr<SListView<TSharedPtr<FInboundTransferStatistics>>> SegmenterListView;` — Displays the transfer stats
- L38 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FInboundTransferStatistics> InStats, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L39 _private prototype_ `void OnTransferStatisticsUpdated() const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Browser/Table/SClientOutboundTransferStatTable.h` (Private)


#### class `UE::MultiUserServer::SClientOutboundTransferStatTable`  
`class SClientOutboundTransferStatTable : public SCompoundWidget`  
_L19-38_
- inherits: `SCompoundWidget`
- desc: Displays FOutboundTransferStatistics as they are updated by INetworkMessagingExtension.
- L23 _public function_ `SLATE_BEGIN_ARGS(SClientOutboundTransferStatTable)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<ITransferStatisticsModel> InStatsModel);`
- L32 _private member_ `TSharedPtr<ITransferStatisticsModel> StatsModel;` — Tells us when the transfer stats have changed
- L34 _private member_ `TSharedPtr<SListView<TSharedPtr<FOutboundTransferStatistics>>> SegmenterListView;` — Displays the transfer stats
- L36 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FOutboundTransferStatistics> InStats, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L37 _private prototype_ `void OnTransferStatisticsUpdated() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/ConcertClientsTabController.h` (Private)


#### class `UE::MultiUserServer::FConcertClientsTabController`  
`class FConcertClientsTabController : public IConcertComponent, public TSharedFromThis<FConcertClientsTabController>`  
_L17-39_
- inherits: `IConcertComponent,TSharedFromThis<FConcertClientsTabController>`
- L22 _public prototype_ `virtual void Init(const FConcertComponentInitParams& Params) override;`
- L26 _public prototype_ `void ShowConnectedClients(const FGuid& SessionId) const;` — Highlights this tab and sets the client filter such that all connected clients of the given session ID are shown.
- L31 _private member_ `TSharedPtr<FGlobalLogSource> LogBuffer;` — Buffers generated logs up to a limit (and overrides oldest logs when buffer is full)
- L33 _private member_ `TSharedPtr<FLogAckTracker> AckTracker;` — Marks logs as acked as the ACKs come in.
- L36 _private member_ `TSharedPtr<SConcertClientsTabView> ClientsView;` — Manages the sub-tabs
- L38 _private prototype_ `TSharedRef<SDockTab> SpawnClientsTab(const FSpawnTabArgs& Args, TSharedPtr<SWindow> RootWindow, TSharedRef<IConcertSyncServer>);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/ConcertLogEntry.h` (Private)


#### enum `EConcertLogAckState`  
`enum class EConcertLogAckState : uint8`  
_L11-23_
- reflection: `UENUM()`
- L14 _public enumerator_ `NotNeeded` — This message does not require any acks
- L16 _public enumerator_ `Ack` — This is an ack
- L18 _public enumerator_ `InProgress` — Still waiting on the ack
- L20 _public enumerator_ `AckReceived` — The ack was received
- L22 _public enumerator_ `AckFailure` — Never received any acks - set after a certain timeout.

#### struct `FConcertLogMetadata`  
`struct FConcertLogMetadata`  
_L27-46_
- reflection: `USTRUCT()`
- desc: Additional properties we display in the UI but that are not in FConcertLog live here.
- L33 _public member_ `EConcertLogAckState AckState = EConcertLogAckState::NotNeeded;` — `UPROPERTY()` — The ack state of this log
- L39 _public member_ `TOptional<FGuid> AckingMessageId;` — Message ID of this log's ACK. If set, implies this log is not an ACK. Valid when AckState == EConcertLogAckState::AckReceived.
- L45 _public member_ `TOptional<TSet<FGuid>> AckedMessageId;` — The Message IDs of the logs we've ACKed. If set, implies this log is an ACK. Valid when AckState == EConcertLogAckState::Ack.

#### struct `FConcertLogEntry`  
`struct FConcertLogEntry`  
_L48-58_
- L51 _public member_ `FConcertLogID LogId;` — Unique log ID. Log IDs grow sequentially.
- L54 _public member_ `FConcertLog Log;` — The log we're describing
- L57 _public member_ `FConcertLogMetadata LogMetaData;` — Additional data to display in the UI

#### Free symbols / members of external scopes

- L8 _typedef_ `using FConcertLogID = uint64;`
- L60 _typedef_ `using FConcertLogEntryFilterFunc = TFunctionRef<bool(const FConcertLogEntry&)>;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_Ack.h` (Private)


#### class `UE::MultiUserServer::FConcertLogFilter_Ack`  
`class FConcertLogFilter_Ack : public TConcertLogFilter_BaseSetSelection<FConcertLogFilter_Ack, EConcertLogAckState>`  
_L11-45_
- inherits: `TConcertLogFilter_BaseSetSelection<FConcertLogFilter_Ack,EConcertLogAckState>`
- desc: Allows only messages that have a selected ACK state
- L15 _public function_ `static TSet<EConcertLogAckState> GetAllOptions()`
- L26 _public function_ `static FString GetOptionDisplayString(const EConcertLogAckState& Item)`
- L40 _public function_ `virtual bool PassesFilter(const FConcertLogEntry& InItem) const override`

#### class `UE::MultiUserServer::FConcertFrontendLogFilter_Ack`  
`class FConcertFrontendLogFilter_Ack : public TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_Ack>`  
_L47-57_
- inherits: `TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_Ack>`
- L51 _public function_ `FConcertFrontendLogFilter_Ack(TSharedRef<FFilterCategory> FilterCategory) : TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_Ack>(MoveTemp(FilterCategory), NSLOCTEXT("UnrealMultiUserUI.Filter.Ack", "Name", "ACKs"))`
- L55 _public function_ `virtual FString GetName() const override`
- L56 _public function_ `virtual FText GetDisplayName() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_BaseSetSelection.h` (Private)


#### class `UE::MultiUserServer::TConcertLogFilter_BaseSetSelection`  
`template<typename TRealFilterImpl, typename TSetType> class TConcertLogFilter_BaseSetSelection : public IFilter<const FConcertLogEntry&>`  
_L22-103_
- inherits: `IFilter<constFConcertLogEntry&>`
- desc: Helper implementation for filters that allow filter based on a finte set of items. Subclasses must implement: - static TSet<TSetType> GetAllOptions(); - static FString GetOptionDisplayString(const TSetType&);
- L24 _private typedef_ `using Super = IFilter<TRealFilterImpl>;`
- L27 _public typedef_ `using TItemType = TSetType;`
- L29 _public function_ `TConcertLogFilter_BaseSetSelection() : AllowedItems(TRealFilterImpl::GetAllOptions())`
- L33 _public function_ `void AllowAll()`
- L42 _public function_ `void DisallowAll()`
- L50 _public function_ `void ToggleAll(const TSet<TSetType>& ToToggle)`
- L70 _public function_ `void AllowItem(const TSetType& MessageTypeName)`
- L78 _public function_ `void DisallowItem(const TSetType& MessageTypeName)`
- L87 _public function_ `bool IsItemAllowed(const TSetType& MessageTypeName) const`
- L91 _public function_ `bool AreAllAllowed() const`
- L95 _public function_ `uint8 GetNumSelected() const`
- L97 _public function_ `virtual FChangedEvent& OnChanged() override`
- L101 _private member_ `TSet<TSetType> AllowedItems;`
- L102 _private member_ `FChangedEvent ChangedEvent;`

#### class `UE::MultiUserServer::TConcertFrontendLogFilter_BaseSetSelection`  
`template<typename TRealFilterImpl> class TConcertFrontendLogFilter_BaseSetSelection : public TConcertFrontendFilterAggregate<TRealFilterImpl, const FConcertLogEntry&>`  
_L106-166_
- inherits: `TConcertFrontendFilterAggregate<TRealFilterImpl,constFConcertLogEntry&>`
- L108 _private typedef_ `using TItemType = typename TRealFilterImpl::TItemType;`
- L109 _private typedef_ `using Super = TConcertFrontendFilterAggregate<TRealFilterImpl, const FConcertLogEntry&>;`
- L112 _public function_ `TConcertFrontendLogFilter_BaseSetSelection(TSharedRef<FFilterCategory> FilterCategory, FText FilterName) : Super(MoveTemp(FilterCategory))`
- L116 _public function_ `virtual void ExposeEditWidgets(FMenuBuilder& MenuBuilder) override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "UnrealMultiUserUI.BaseSetSelection"`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L123 _function_ `FExecuteAction::CreateLambda([this](){ this->Implementation.AllowAll(); }), FCanExecuteAction::CreateLambda([] { return true; }), FIsActionChecked()), NAME_None, EUserInterfaceActionType::Button );` (scope `UE::MultiUserServer::TConcertFrontendLogFilter_BaseSetSelection::ExposeEditWidgets`)
- L134 _function_ `FExecuteAction::CreateLambda([this](){ this->Implementation.DisallowAll(); }), FCanExecuteAction::CreateLambda([] { return true; }), FIsActionChecked()), NAME_None, EUserInterfaceActionType::Button );` (scope `UE::MultiUserServer::TConcertFrontendLogFilter_BaseSetSelection::ExposeEditWidgets`)
- L149 _function_ `` (scope `UE::MultiUserServer::TConcertFrontendLogFilter_BaseSetSelection::ExposeEditWidgets`)
- L159 _function_ `}), FCanExecuteAction::CreateLambda([]` (scope `UE::MultiUserServer::TConcertFrontendLogFilter_BaseSetSelection::ExposeEditWidgets`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_Client.h` (Private)


#### class `UE::MultiUserServer::FConcertLogFilter_Client`  
`class FConcertLogFilter_Client : public IFilter<const FConcertLogEntry&>`  
_L15-38_
- inherits: `IFilter<constFConcertLogEntry&>`
- desc: Only allows messages from the given clients
- L19 _public function_ `explicit FConcertLogFilter_Client(const FGuid& SingleAllowedId, TSharedRef<FEndpointToUserNameCache> EndpointCache) : AllowedClientMessagingNodeId(SingleAllowedId) , EndpointCache(MoveTemp(EndpointCache))`
- L25 _public prototype_ `virtual bool PassesFilter(const FConcertLogEntry& InItem) const override;`
- L26 _public function_ `virtual FChangedEvent& OnChanged() override`
- L32 _private member_ `FGuid AllowedClientMessagingNodeId;` — Messages to and from the following client endpoint ID are allowed
- L35 _private member_ `TSharedRef<FEndpointToUserNameCache> EndpointCache;` — Translates Concert endpoint Ids to messaging node Ids
- L37 _private member_ `FChangedEvent ChangedEvent;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_MessageAction.h` (Private)


#### class `UE::MultiUserServer::FConcertLogFilter_MessageAction`  
`class FConcertLogFilter_MessageAction : public TConcertLogFilter_BaseSetSelection<FConcertLogFilter_MessageAction, FName>`  
_L12-32_
- inherits: `TConcertLogFilter_BaseSetSelection<FConcertLogFilter_MessageAction,FName>`
- desc: Allows only the selected messages types
- L16 _public function_ `static TSet<FName> GetAllOptions()`
- L21 _public function_ `static FString GetOptionDisplayString(const FName& Item)`
- L27 _public function_ `virtual bool PassesFilter(const FConcertLogEntry& InItem) const override`

#### class `UE::MultiUserServer::FConcertFrontendLogFilter_MessageAction`  
`class FConcertFrontendLogFilter_MessageAction : public TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_MessageAction>`  
_L34-44_
- inherits: `TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_MessageAction>`
- L38 _public function_ `FConcertFrontendLogFilter_MessageAction(TSharedRef<FFilterCategory> FilterCategory) : TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_MessageAction>(MoveTemp(FilterCategory), NSLOCTEXT("UnrealMultiUserUI.Filter.MessageAction", "Name", "Actions"))`
- L42 _public function_ `virtual FString GetName() const override`
- L43 _public function_ `virtual FText GetDisplayName() const override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_MessageType.h` (Private)


#### class `UE::MultiUserServer::FConcertLogFilter_MessageType`  
`class FConcertLogFilter_MessageType : public TConcertLogFilter_BaseSetSelection<FConcertLogFilter_MessageType, FName>`  
_L12-36_
- inherits: `TConcertLogFilter_BaseSetSelection<FConcertLogFilter_MessageType,FName>`
- desc: Allows only the selected messages types
- L16 _public function_ `static TSet<FName> GetAllOptions()`
- L21 _public function_ `static FString GetOptionDisplayString(const FName& Item)`
- L27 _public function_ `virtual bool PassesFilter(const FConcertLogEntry& InItem) const override`
- L35 _private member_ `TSet<FName> AllowedMessageTypeNames;`

#### class `UE::MultiUserServer::FConcertFrontendLogFilter_MessageType`  
`class FConcertFrontendLogFilter_MessageType : public TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_MessageType>`  
_L38-48_
- inherits: `TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_MessageType>`
- L42 _public function_ `FConcertFrontendLogFilter_MessageType(TSharedRef<FFilterCategory> FilterCategory) : TConcertFrontendLogFilter_BaseSetSelection<FConcertLogFilter_MessageType>(MoveTemp(FilterCategory), NSLOCTEXT("UnrealMultiUserUI.Filter.MessageType", "Name", "Message Type"))`
- L46 _public function_ `virtual FString GetName() const override`
- L47 _public function_ `virtual FText GetDisplayName() const override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_Size.h` (Private)


#### enum `UE::MultiUserServer::ESizeFilterMode`  
`enum class ESizeFilterMode`  
_L14-20_
- L17 _public enumerator_ `BiggerThanOrEqual` — Allow logs bigger than or equal to the specified size
- L19 _public enumerator_ `LessThanOrEqual` — Allow logs smaller than or equal to the specified size

#### class `UE::MultiUserServer::FConcertLogFilter_Size`  
`class FConcertLogFilter_Size : public IFilter<const FConcertLogEntry&>`  
_L23-48_
- inherits: `IFilter<constFConcertLogEntry&>`
- desc: Filters based on the log's size
- L28 _public prototype_ `virtual bool PassesFilter(const FConcertLogEntry& InItem) const override;`
- L29 _public function_ `virtual FChangedEvent& OnChanged() override`
- L32 _public prototype_ `void SetOperator(ESizeFilterMode Operator);`
- L33 _public prototype_ `void SetSizeInBytes(uint32 NewSizeInBytes);`
- L34 _public prototype_ `void SetDataUnit(EUnit NewUnit);`
- L36 _public function_ `ESizeFilterMode GetOperator() const`
- L37 _public function_ `uint32 GetSizeInBytes() const`
- L38 _public function_ `EUnit GetDataUnit() const`
- L39 _public function_ `TSet<EUnit> GetAllowedUnits() const`
- L43 _private member_ `ESizeFilterMode FilterMode = ESizeFilterMode::BiggerThanOrEqual;`
- L44 _private member_ `uint32 SizeInBytes = 0;`
- L45 _private member_ `EUnit DataUnit = EUnit::Bytes;`
- L47 _private member_ `FChangedEvent ChangedEvent;`

#### class `UE::MultiUserServer::FConcertFrontendLogFilter_Size`  
`class FConcertFrontendLogFilter_Size : public TConcertFrontendFilterAggregate<FConcertLogFilter_Size, const FConcertLogEntry&>`  
_L50-61_
- inherits: `TConcertFrontendFilterAggregate<FConcertLogFilter_Size,constFConcertLogEntry&>`
- L52 _private typedef_ `using Super = TConcertFrontendFilterAggregate<FConcertLogFilter_Size, const FConcertLogEntry&>;`
- L55 _public prototype_ `FConcertFrontendLogFilter_Size(TSharedRef<FFilterCategory> FilterCategory);`
- L57 _public function_ `virtual FString GetName() const override`
- L58 _public function_ `virtual FText GetDisplayName() const override`
- L60 _public prototype_ `virtual void ExposeEditWidgets(FMenuBuilder& MenuBuilder) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_TextSearch.h` (Private)


#### class `UE::MultiUserServer::FConcertLogFilter_TextSearch`  
`class FConcertLogFilter_TextSearch : public TConcertFilter_TextSearch<const FConcertLogEntry&>`  
_L14-34_
- inherits: `TConcertFilter_TextSearch<constFConcertLogEntry&>`
- L18 _public function_ `FConcertLogFilter_TextSearch(TSharedRef<FConcertLogTokenizer> Tokenizer) : Tokenizer(MoveTemp(Tokenizer))`
- L22 _public function_ `virtual void GenerateSearchTerms(const FConcertLogEntry& InItem, TArray<FString>& OutTerms) const override`
- L33 _private member_ `TSharedRef<FConcertLogTokenizer> Tokenizer;` — Helps in converting FConcertLog members into search terms

#### class `UE::MultiUserServer::FConcertFrontendLogFilter_TextSearch`  
`class FConcertFrontendLogFilter_TextSearch : public TConcertFrontendFilter_TextSearch<FConcertLogFilter_TextSearch, const FConcertLogEntry&>`  
_L37-45_
- inherits: `TConcertFrontendFilter_TextSearch<FConcertLogFilter_TextSearch,constFConcertLogEntry&>`
- desc: Creates a search bar
- L39 _private typedef_ `using Super = TConcertFrontendFilter_TextSearch<FConcertLogFilter_TextSearch, const FConcertLogEntry&>;`
- L42 _public function_ `FConcertFrontendLogFilter_TextSearch(TSharedPtr<FFilterCategory> InCategory, TSharedRef<FConcertLogTokenizer> Tokenizer) : Super(MoveTemp(InCategory), MoveTemp(Tokenizer))`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertFrontendLogFilter_Time.h` (Private)


#### enum `UE::MultiUserServer::ETimeFilter`  
`enum class ETimeFilter`  
_L11-17_
- L14 _public enumerator_ `AllowAfter` — Logs after the indicated time are allowed
- L16 _public enumerator_ `AllowBefore` — Logs before the indicated time are allowed

#### class `UE::MultiUserServer::FConcertLogFilter_Time`  
`class FConcertLogFilter_Time : public IFilter<const FConcertLogEntry&>`  
_L20-46_
- inherits: `IFilter<constFConcertLogEntry&>`
- desc: Filters based on whether a log happened before or after a certain time
- L24 _public prototype_ `FConcertLogFilter_Time(ETimeFilter FilterMode);`
- L26 _public prototype_ `void ResetToInfiniteTime();`
- L29 _public prototype_ `virtual bool PassesFilter(const FConcertLogEntry& InItem) const override;`
- L30 _public function_ `virtual FChangedEvent& OnChanged() override`
- L33 _public function_ `ETimeFilter GetFilterMode() const`
- L34 _public function_ `FDateTime GetTime() const`
- L36 _public prototype_ `void SetFilterMode(ETimeFilter InFilterMode);`
- L37 _public prototype_ `void SetTime(const FDateTime& InTime);`
- L41 _private member_ `ETimeFilter FilterMode;`
- L42 _private member_ `FDateTime Time;`
- L43 _private member_ `FChangedEvent ChangedEvent;`
- L45 _private prototype_ `FDateTime MakeResetTime() const;`

#### class `UE::MultiUserServer::FConcertFrontendLogFilter_Time`  
`class FConcertFrontendLogFilter_Time : public TConcertFrontendFilterAggregate<FConcertLogFilter_Time, const FConcertLogEntry&>`  
_L48-80_
- inherits: `TConcertFrontendFilterAggregate<FConcertLogFilter_Time,constFConcertLogEntry&>`
- L50 _private typedef_ `using Super = TConcertFrontendFilterAggregate<FConcertLogFilter_Time, const FConcertLogEntry&>;`
- L53 _public prototype_ `FConcertFrontendLogFilter_Time(TSharedRef<FFilterCategory> FilterCategory, ETimeFilter TimeFilter);`
- L55 _public function_ `virtual FString GetName() const override`
- L56 _public function_ `virtual FText GetDisplayName() const override`
- L63 _public prototype_ `virtual void ExposeEditWidgets(FMenuBuilder& MenuBuilder) override;`
- L76 _private member_ `ETimeFilter TimeFilter;`
- L78 _private prototype_ `void BuildMonthSubMenu(FMenuBuilder& MenuBuilder);`
- L79 _private prototype_ `TSharedRef<SWidget> CreateDateComponentNumericWidget(ETimeComponent TimeComponent);`

#### enum `UE::MultiUserServer::FConcertFrontendLogFilter_Time::ETimeComponent`  
`enum class ETimeComponent`  
_L67-74_
- L69 _public enumerator_ `Year`
- L70 _public enumerator_ `Day`
- L71 _public enumerator_ `Hour`
- L72 _public enumerator_ `Minute`
- L73 _public enumerator_ `Second`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/ConcertLogFilter_FrontendRoot.h` (Private)


#### class `UE::MultiUserServer::FConcertLogFilter_FrontendRoot`  
`class FConcertLogFilter_FrontendRoot : public TConcertFrontendRootFilter<const FConcertLogEntry&, FConcertFrontendLogFilter_TextSearch>`  
_L18-31_
- inherits: `TConcertFrontendRootFilter<constFConcertLogEntry&,FConcertFrontendLogFilter_TextSearch>`
- desc: A filter that contains multiple UI filters
- L20 _private typedef_ `using Super = TConcertFrontendRootFilter<const FConcertLogEntry&, FConcertFrontendLogFilter_TextSearch>;`
- L23 _public function_ `FConcertLogFilter_FrontendRoot( TSharedRef<FConcertLogTokenizer> Tokenizer, TArray<TSharedRef<TConcertFrontendFilter<const FConcertLogEntry&>>> FrontendFilters, TSharedRef<FFilterCategory> DefaultCategory, const TArray<TSharedRef<IFilter<const FConcertLogEntry&>>>& NonVisualFilters = {} ) : Super(MakeShared<FConcertFrontendLogFilter_TextSearch>(DefaultCategory, MoveTemp(Tokenizer)), MoveTemp(FrontendFilters), NonVisualFilters, DefaultCategory)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L34 _prototype_ `TSharedRef<FConcertLogFilter_FrontendRoot> MakeGlobalLogFilter(TSharedRef<FConcertLogTokenizer> Tokenizer);` (scope `UE::MultiUserServer`) — Creates a filter for the global filter log window
- L42 _prototype_ `TSharedRef<FConcertLogFilter_FrontendRoot> MakeClientLogFilter(TSharedRef<FConcertLogTokenizer> Tokenizer, const FGuid& ClientMessageNodeId, const TSharedRef<FEndpointToUserNameCache>& EndpointCache);` (scope `UE::MultiUserServer`) — Creates a filter for a filter log window intended for a client @param Tokenizer Used for text search @param ClientMessageNodeId The Id of this client's messaging node - this is used to filter messages involving this client @param EndpointCache Needed to filter messages involving this client - converts Concert endpoint Ids to the message node Id

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Filter/FilteredConcertLogList.h` (Private)


#### class `UE::MultiUserServer::FFilteredConcertLogList`  
`class FFilteredConcertLogList`  
_L15-59_
- desc: Applies a filter to a IConcertLogSource as the logs come in.
- L19 _public prototype_ `FFilteredConcertLogList(TSharedRef<IConcertLogSource> InLogSource, TSharedPtr<IFilter<const FConcertLogEntry&>> InOptionalFilter);`
- L20 _public prototype_ `~FFilteredConcertLogList();`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLogListChanged, const TArray<TSharedPtr<FConcertLogEntry>>& );`
- L23 _public function_ `FOnLogListChanged& OnLogListChanged()`
- L25 _public function_ `bool IsBufferFull() const`
- L26 _public function_ `const TArray<TSharedPtr<FConcertLogEntry>>& GetFilteredLogs() const`
- L27 _public function_ `TArray<TSharedPtr<FConcertLogEntry>> GetFilteredLogsWithId(const FGuid& MessageId) const`
- L35 _protected function_ `const TSharedRef<IConcertLogSource>& GetLogSource() const`
- L40 _private member_ `TSharedRef<IConcertLogSource> LogSource;` — Determines where the logs come from
- L43 _private member_ `TSharedPtr<IFilter<const FConcertLogEntry&>> Filter;` — Optional. Filters items from the LogSource
- L46 _private member_ `TArray<TSharedPtr<FConcertLogEntry>> FilteredLogs;` — Contains the items of LogSource with Filter applied.
- L49 _private member_ `TMap<FGuid, TArray<TSharedPtr<FConcertLogEntry>>> MessageIdToLogs;` — Binds message IDs to the logs that have that ID. Logs can share the same ID but have different MessageActions.
- L52 _private member_ `FOnLogListChanged OnLogListChangedEvent;` — Called when the content of FilteredResult changes
- L54 _private prototype_ `void OnLowestLogEntryChanged(FConcertLogID NewLowestValidID);`
- L55 _private prototype_ `void OnNewLogEntryAdded(const TSharedRef<FConcertLogEntry>& NewLogEntry);`
- L56 _private prototype_ `void RebuildFilteredResult();`
- L58 _private prototype_ `void RemoveMessageIdToLogEntry(const TSharedPtr<FConcertLogEntry>& Log);`

#### class `UE::MultiUserServer::FPagedFilteredConcertLogList`  
`class FPagedFilteredConcertLogList : public FFilteredConcertLogList`  
_L62-107_
- inherits: `FFilteredConcertLogList`
- desc: Further sorts the results of FFilteredConcertLogList::Filter into pages, i.e. buckets of logs, useful for limiting elements in a table view.
- L66 _public typedef_ `using FLogsPerPageCount = uint16;`
- L67 _public typedef_ `using FPageCount = uint32;`
- L69 _public prototype_ `FPagedFilteredConcertLogList(TSharedRef<IConcertLogSource> LogSource, TSharedPtr<IFilter<const FConcertLogEntry&>> OptionalFilter, uint16 FLogsPerPageCount = 500);`
- L71 _public function_ `FPageCount GetNumPages() const`
- L72 _public function_ `FPageCount GetCurrentPage() const`
- L73 _public prototype_ `TOptional<FPageCount> GetPageOf(const size_t ItemIndex) const;`
- L74 _public function_ `FLogsPerPageCount GetLogsPerPage() const`
- L75 _public function_ `const TArray<TSharedPtr<FConcertLogEntry>>& GetPageView() const`
- L77 _public prototype_ `void SetLogsPerPage(FLogsPerPageCount NewLogsPerPage);`
- L78 _public prototype_ `void SetPage(const FPageCount PageIndex);`
- L80 _public function_ `FOnLogListChanged& OnPageViewChanged()`
- L86 _private member_ `FLogsPerPageCount LogsPerPage;` — The number of logs to show per page
- L89 _private member_ `FPageCount CurrentPageIndex = 0;` — The index of the current page. Starts at 0.
- L92 _private member_ `TArray<TSharedPtr<FConcertLogEntry>> PageView;` — The filtered logs on the current page
- L95 _private member_ `FOnLogListChanged OnPageViewChangedEvent;` — Called when the content of PageView changes
- L97 _private prototype_ `void HandeOnLogListChanged(const TArray<TSharedPtr<FConcertLogEntry>>& NewFilteredLogList);`
- L98 _private prototype_ `void RepopulatePage();`
- L99 _private prototype_ `void CheckAndConditionallyPopulatePage();`
- L104 _private prototype_ `void ForEachLogIndexOnPage(TFunctionRef<void(size_t FilteredLogIndex)> Callback, FLogsPerPageCount MaxItems = TNumericLimits<FLogsPerPageCount>::Max());` — Given the current page settings (not validated - assumed corrected), calls Callback with each index in GetFilteredLogs() that should be an item on the current page.
- L106 _private prototype_ `TTuple<size_t, size_t> GetLogIndicesForPage() const;` — @return Start and last index in GetFilteredLogs() array to accommodate current page settings

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLogListChanged, const TArray<TSharedPtr<FConcertLogEntry>>& );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/LogScrollingDelegates.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L9 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanScrollToLog, const FGuid& , FConcertLogEntryFilterFunc , FText& );`
- L9 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanScrollToLog, const FGuid& , FConcertLogEntryFilterFunc , FText& );` (scope `UE::MultiUserServer`)
- L10 _delegate_ `DECLARE_DELEGATE_TwoParams(FScrollToLog, const FGuid& , FConcertLogEntryFilterFunc );`
- L10 _prototype_ `DECLARE_DELEGATE_TwoParams(FScrollToLog, const FGuid& , FConcertLogEntryFilterFunc );` (scope `UE::MultiUserServer`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/SConcertTransportLog.h` (Private)


#### class `UE::MultiUserServer::SConcertTransportLog`  
`class SConcertTransportLog : public SCompoundWidget`  
_L32-101_
- inherits: `SCompoundWidget`
- desc: Displays the contents of a IConcertLogSource and has UI for filtering.
- L36 _public member_ `static const FName FirstColumnId;`
- L38 _public function_ `SLATE_BEGIN_ARGS(SConcertTransportLog)`
- L41 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FConcertLogFilter_FrontendRoot>, Filter) SLATE_END_ARGS() virtual ~SConcertTransportLog() override;` — Optional filters to display in UI
- L45 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IConcertLogSource> LogSource, TSharedRef<FEndpointToUserNameCache> InEndpointCache, TSharedRef<FConcertLogTokenizer> InLogTokenizer);`
- L47 _public prototype_ `bool CanScrollToLog(const FGuid& MessageId, FConcertLogEntryFilterFunc FilterFunc) const;`
- L48 _public prototype_ `void ScrollToLog(const FGuid& MessageId, FConcertLogEntryFilterFunc FilterFunc) const;`
- L53 _private member_ `TSharedPtr<SOverlay> EnableLoggingPromptOverlay;` — Used to overlay EnableLoggingPrompt over the tabs
- L55 _private member_ `TSharedPtr<SPromptConcertLoggingEnabled> EnableLoggingPrompt;` — Reminds the user to enable logging
- L57 _private member_ `TSharedPtr<FEndpointToUserNameCache> EndpointCache;`
- L60 _private member_ `TSharedPtr<FPagedFilteredConcertLogList> PagedLogList;` — Sorts the log into pages whilst applying filters
- L62 _private member_ `TSharedPtr<FConcertLogTokenizer> LogTokenizer;` — Used by various systems to convert logs to text
- L64 _private member_ `TSharedPtr<FConcertLogFilter_FrontendRoot> Filter;`
- L67 _private member_ `TSharedPtr<SListView<TSharedPtr<FConcertLogEntry>>> LogView;` — Lists the logs
- L69 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — Header row of LogView
- L72 _private member_ `bool bAutoScroll = true;` — Whether to automatically scroll to new logs as they come in
- L74 _private member_ `bool bIsUpdatingColumnVisibility = false;` — Whether we currently loading the column visibility - prevents infinite event recursion
- L77 _private prototype_ `TSharedRef<SWidget> CreateTableView();` — Table view creation
- L78 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRow();`
- L79 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FConcertLogEntry> Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L81 _private prototype_ `static void ForEachPropertyColumn(TFunctionRef<void(const FProperty& ColumnPropertyId, FName ColumnId)> Callback);`
- L83 _private prototype_ `void RestoreDefaultColumnVisiblities();`
- L84 _private prototype_ `TMap<FName, bool> GetDefaultColumnVisibilities() const;`
- L86 _private prototype_ `TSharedRef<SWidget> CreateViewOptionsMenu();`
- L87 _private prototype_ `void OnFilterMenuChecked();`
- L88 _private prototype_ `void OnPageViewChanged(const TArray<TSharedPtr<FConcertLogEntry>>&);`
- L89 _private prototype_ `void OnColumnVisibilitySettingsChanged(const FColumnVisibilitySnapshot& ColumnSnapshot);`
- L91 _private prototype_ `void OnConcertLoggingEnabledChanged(bool bNewEnabled);`
- L93 _private prototype_ `bool CanScrollToAckLog(const FGuid& MessageId) const;`
- L94 _private prototype_ `bool CanScrollToAckedLog(const FGuid& MessageId) const;`
- L95 _private prototype_ `void ScrollToAckLog(const FGuid& MessageId) const;`
- L96 _private prototype_ `void ScrollToAckedLog(const FGuid& MessageId) const;`
- L97 _private prototype_ `static bool SharedCanScrollToAckLog(const FGuid& MessageId, const FConcertLogEntry& Entry);`
- L98 _private prototype_ `static bool SharedCanScrollToAckedLog(const FGuid& MessageId, const FConcertLogEntry& Entry);`
- L100 _private prototype_ `void ScrollToLog(const int32 LogIndex) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/SConcertTransportLogFooter.h` (Private)


#### class `UE::MultiUserServer::SConcertTransportLogFooter`  
`class SConcertTransportLogFooter : public SCompoundWidget`  
_L16-35_
- inherits: `SCompoundWidget`
- desc: Displays the number of pages and items. Displayed under the table view.
- L20 _public function_ `DECLARE_DELEGATE_OneParam(FExtendContextMenu, FMenuBuilder&) SLATE_BEGIN_ARGS(SConcertTransportLogFooter)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FPagedFilteredConcertLogList> InPagedLogList);`
- L29 _private member_ `TSharedPtr<FPagedFilteredConcertLogList> PagedLogList;` — The model we'll be updating
- L32 _private member_ `TSharedPtr<SSpinBox<FPagedFilteredConcertLogList::FPageCount>> CurrentPage;` — Selects the current page
- L34 _private member_ `TSharedPtr<STextBlock> PageCounterText;` — Displays the number of pages

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FExtendContextMenu, FMenuBuilder&) SLATE_BEGIN_ARGS(SConcertTransportLogFooter) {} SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FPagedFilteredConcertLogList> InPagedLogList);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/SConcertTransportLogRow.h` (Private)


#### class `UE::MultiUserServer::SConcertTransportLogRow`  
`class SConcertTransportLogRow : public SMultiColumnTableRow<TSharedPtr<FConcertLogEntry>>`  
_L17-63_
- inherits: `SMultiColumnTableRow<TSharedPtr<FConcertLogEntry>>`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FScrollToLog, const FGuid& );`
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanScrollToLog, const FGuid& );`
- L24 _public function_ `SLATE_BEGIN_ARGS(SConcertTransportLogRow)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FLinearColor, AvatarColor) SLATE_EVENT(FCanScrollToLog, CanScrollToAckLog) SLATE_EVENT(FCanScrollToLog, CanScrollToAckedLog) SLATE_EVENT(FScrollToLog, ScrollToAckLog) SLATE_EVENT(FScrollToLog, ScrollToAckedLog) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FConcertLogEntry> InLogEntry, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<FConcertLogTokenizer> InTokenizer);`
- L37 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L42 _private member_ `TSharedPtr<FConcertLogEntry> LogEntry;`
- L44 _private member_ `TSharedPtr<FConcertLogTokenizer> Tokenizer;` — Used to convert some members into display strings
- L46 _private member_ `TAttribute<FText> HighlightText;`
- L48 _private member_ `FLinearColor AvatarColor;`
- L49 _private member_ `FCanScrollToLog CanScrollToAckLogFunc;`
- L50 _private member_ `FCanScrollToLog CanScrollToAckedLogFunc;`
- L51 _private member_ `FScrollToLog ScrollToAckLogFunc;`
- L52 _private member_ `FScrollToLog ScrollToAckedLogFunc;`
- L54 _private prototype_ `TSharedRef<SWidget> CreateDefaultColumn(const FName& PropertyName);`
- L56 _private prototype_ `TSharedRef<SWidget> CreateAckColumn(const FName& PropertyName);`
- L57 _private prototype_ `TSharedRef<SWidget> CreateAckInProgressWidget() const;`
- L58 _private prototype_ `TSharedRef<SWidget> CreateAckSuccessWidget() const;`
- L59 _private prototype_ `TSharedRef<SWidget> CreateAckFailureWidget() const;`
- L60 _private prototype_ `TSharedRef<SWidget> CreateAckNotNeededWidget() const;`
- L61 _private prototype_ `TSharedRef<SWidget> CreateAckWidget() const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FScrollToLog, const FGuid& );`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanScrollToLog, const FGuid& );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Source/GlobalLogSource.h` (Private)


#### class `FGlobalLogSource`  
`class FGlobalLogSource : public IConcertLogSource`  
_L18-55_
- inherits: `IConcertLogSource`
- desc: Listens for log events using ConcertTransportEvents::OnConcertServerLogEvent and buffers them. The shared pointers and log entries are allocated in two sequential buffers to improve memory footprint and cache coherency; the footprint is improved because two big chunks of memory is better than many tiny chunks.
- L22 _public prototype_ `FGlobalLogSource(size_t LogCapacity);`
- L26 _public function_ `virtual bool IsBufferFull() const override`
- L27 _public function_ `virtual size_t GetNumLogs() const override`
- L28 _public function_ `virtual const TSharedPtr<FConcertLogEntry>& GetElement_Unchecked(size_t Index) const override`
- L29 _public function_ `virtual FLogEntryIdEvent& OnLowestLogEntryChanged() override`
- L30 _public function_ `virtual FLogEntryEvent& OnLogEntryAdded() override`
- L36 _private member_ `size_t OldestLogEntryIndex = 0;` — The lowest ID in the buffer
- L38 _private member_ `size_t NumberOfLogs = 0;` — The number of logs in the buffer.
- L40 _private member_ `size_t NextIndexToAddTo = 0;` — The next index at which to insert a log entry
- L42 _private member_ `FConcertLogID NextLogID = 0;` — The next log ID to use
- L45 _private member_ `TCircularBuffer<TSharedPtr<FConcertLogEntry>> LogPtrs;` — Contains all logs. The oldest logs are discarded
- L47 _private member_ `TCircularBuffer<FConcertLogEntry> LogEntries;` — The content that the LogPtrs point to. For better cache coherency.
- L50 _private member_ `FLogEntryIdEvent OnLowestEntryChangedEvent;`
- L51 _private member_ `FLogEntryEvent OnLogEntryAddedEvent;`
- L53 _private prototype_ `void OnLogProduced(const IConcertServer&, const FConcertLog& Log);`
- L54 _private prototype_ `void AddLog(const FConcertLog& NewLog);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Source/IConcertLogSource.h` (Private)


#### class `IConcertLogSource`  
`class IConcertLogSource`  
_L16-53_
- desc: Describes a source of logs - it is similar to an array but with some changes: - GetElement_Unchecked is used to access elements by index, as usual. - the highest valid index is NumLogs() - 1, as usual. - the lowest valid index is not necessarily 0 but is instead LowestLogIndex(). Implementations can decide to delete the oldest logs if the number of logs grows too high; the implementation will call OnLowestLogEntryChanged when old logs are removed.
- L20 _public prototype_ `virtual ~IConcertLogSource() = default;`
- L23 _public prototype_ `virtual bool IsBufferFull() const = 0;` — @return Whether the maximum number of logs has been reached
- L26 _public prototype_ `virtual size_t GetNumLogs() const = 0;` — @return The number of logs in this source
- L31 _public prototype_ `virtual const TSharedPtr<FConcertLogEntry>& GetElement_Unchecked(size_t Index) const = 0;` — @param Index Satisfies 0 <= Index < NumLogs(). Index 0 is the oldest log. @return The log entry at the given Index - crashes if the index is out of bounds.
- L33 _public function_ `void ForEachLog(TFunctionRef<void(const TSharedPtr<FConcertLogEntry>& Log)> ConsumerFunc) const`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLogEntryIdEvent, FConcertLogID );`
- L48 _public prototype_ `virtual FLogEntryIdEvent& OnLowestLogEntryChanged() = 0;` — Called when the log buffer is about to remove the oldest logs. The event tells the lowest ID that is still valid. Once this event has completed, the log data is overwritten with the latest log data.
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLogEntryEvent, const TSharedRef<FConcertLogEntry>& );`
- L52 _public prototype_ `virtual FLogEntryEvent& OnLogEntryAdded() = 0;` — Called when a new entry has been added to the log buffer.

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLogEntryIdEvent, FConcertLogID );`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLogEntryEvent, const TSharedRef<FConcertLogEntry>& );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Util/ConcertLogTokenizer.h` (Private)


#### class `UE::MultiUserServer::FConcertLogTokenizer`  
`class FConcertLogTokenizer`  
_L14-44_
- desc: Converts members of FConcertLog and FConcertLogMetadata into a string. Used e.g. to make search respect the display settings.
- L18 _public prototype_ `FConcertLogTokenizer(TSharedRef<FEndpointToUserNameCache> EndpointInfoGetter);`
- L21 _public prototype_ `FString Tokenize(const FConcertLog& Data, const FProperty& ConcertLogProperty) const;` — Tokenizes a property of FConcertLog into a string
- L23 _public prototype_ `FString Tokenize(const FConcertLogMetadata& Data, const FProperty& ConcertLogMetadataProperty) const;` — Tokenizes a property of FConcertLogMetadata into a string
- L26 _public prototype_ `FString TokenizeMessageId(const FConcertLog& Data) const;` — ContainerPtr Tokenizers
- L27 _public prototype_ `FString TokenizeTimestamp(const FConcertLog& Data) const;`
- L28 _public prototype_ `FString TokenizeMessageTypeName(const FConcertLog& Data) const;`
- L29 _public prototype_ `FString TokenizeCustomPayloadUncompressedByteSize(const FConcertLog& Data) const;`
- L30 _public prototype_ `FString TokenizeOriginEndpointId(const FConcertLog& Data) const;`
- L31 _public prototype_ `FString TokenizeDestinationEndpointId(const FConcertLog& Data) const;`
- L35 _private typedef_ `using FTokenizeFunc = TFunction<FString(const FConcertLog&)>;`
- L38 _private member_ `TMap<const FProperty*, FTokenizeFunc> TokenizerFunctions;` — Override functions for tokenizing certain properties
- L41 _private member_ `TSharedRef<FEndpointToUserNameCache> EndpointInfoGetter;` — Used so we can look up client and server info (even after client has disconnected)
- L43 _private prototype_ `FString TokenizeUsingPropertyExport(const void* ContainerPtr, const FProperty& ConcertLogProperty) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Util/LogAckTracker.h` (Private)


#### class `FLogAckTracker`  
`class FLogAckTracker`  
_L19-46_
- desc: Tracks ack logs and updates the
- L22 _public prototype_ `FLogAckTracker(TSharedRef<IConcertLogSource> LogSource, TSharedRef<IConcertServer> Server);`
- L23 _public prototype_ `~FLogAckTracker();`
- L28 _private member_ `const TSharedRef<IConcertLogSource> LogSource;` — We analyse & track newly added logs
- L30 _private member_ `TSharedRef<IConcertServer> Server;` — We listen to received ACKs from the server.
- L39 _private member_ `TMap<FGuid, FPendingAckInfo> PendingAckLogs;` — Logs we're waiting on an ACK for
- L42 _private member_ `TMap<FGuid, TSet<FGuid>> AckingMessageToAckedMessages;` — Maps an ACK log to the message IDs it ACKs.
- L44 _private prototype_ `void OnLogEntryProduced(const TSharedRef<FConcertLogEntry>& LogEntry);`
- L45 _private prototype_ `void OnAckProcessed(const FConcertEndpointContext& LocalEndpointId, const FConcertEndpointContext& RemoteEndpointId, const TSharedRef<IConcertMessage>& AckedMessage, const FConcertMessageContext& MessageContext);`

#### struct `FLogAckTracker::FPendingAckInfo`  
`struct FPendingAckInfo`  
_L32-36_
- L35 _public member_ `TArray<TWeakPtr<FConcertLogEntry>> LogEntries;` — There can be several logs with the same Message ID

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Util/MessageActionUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L9 _namespace_ `namespace MessageActionUtils` (scope `UE::MultiUserServer`)
- L12 _prototype_ `TSet<FName> GetAllMessageActionNames();` (scope `UE::MultiUserServer::MessageActionUtils`) — Gets all message action names
- L13 _prototype_ `TSet<EConcertLogMessageAction> GetAllMessageActions();` (scope `UE::MultiUserServer::MessageActionUtils`)
- L15 _prototype_ `FName ConvertActionToName(EConcertLogMessageAction MessageAction);` (scope `UE::MultiUserServer::MessageActionUtils`)
- L16 _prototype_ `FString GetActionDisplayString(EConcertLogMessageAction MessageAction);` (scope `UE::MultiUserServer::MessageActionUtils`)
- L17 _prototype_ `FString GetActionDisplayString(FName MessageActionName);` (scope `UE::MultiUserServer::MessageActionUtils`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Logging/Util/MessageTypeUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L7 _namespace_ `namespace MessageTypeUtils` (scope `UE::MultiUserServer`)
- L10 _prototype_ `TSet<FName> GetAllMessageTypeNames();` (scope `UE::MultiUserServer::MessageTypeUtils`) — Gets all message type names (sub-structs of FConcertMessageData - see FConcertLog::MessageTypeName)
- L12 _prototype_ `TSet<FName> GetAllMessageTypeNames_EventsOnly();` (scope `UE::MultiUserServer::MessageTypeUtils`)
- L13 _prototype_ `TSet<FName> GetAllMessageTypeNames_RequestsOnly();` (scope `UE::MultiUserServer::MessageTypeUtils`)
- L14 _prototype_ `TSet<FName> GetAllMessageTypeNames_ResponseOnlyOnly();` (scope `UE::MultiUserServer::MessageTypeUtils`)
- L15 _prototype_ `TSet<FName> GetAllMessageTypeNames_AcksOnlyOnly();` (scope `UE::MultiUserServer::MessageTypeUtils`)
- L18 _prototype_ `FString SanitizeMessageTypeName(FName MessageTypeName);` (scope `UE::MultiUserServer::MessageTypeUtils`) — Gets a readable version of a message type name

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Filter/PackageTransmissionFilter_FrontendRoot.h` (Private)


#### class `UE::MultiUserServer::FPackageTransmissionFilter_FrontendRoot`  
`class FPackageTransmissionFilter_FrontendRoot : public TConcertFrontendRootFilter<const FPackageTransmissionEntry&, FPackageTransmissionFrontendFilter_TextSearch>`  
_L18-31_
- inherits: `TConcertFrontendRootFilter<constFPackageTransmissionEntry&,FPackageTransmissionFrontendFilter_TextSearch>`
- desc: Root filter displayed in package transmission UI
- L20 _private typedef_ `using Super = TConcertFrontendRootFilter<const FPackageTransmissionEntry&, FPackageTransmissionFrontendFilter_TextSearch>;`
- L23 _public function_ `FPackageTransmissionFilter_FrontendRoot( TSharedRef<FPackageTransmissionEntryTokenizer> Tokenizer, TArray<TSharedRef<TConcertFrontendFilter<const FPackageTransmissionEntry&>>> FrontendFilters, const TArray<TSharedRef<IFilter<const FPackageTransmissionEntry&>>>& NonVisualFilters = {}, TSharedRef<FFilterCategory> DefaultCategory = MakeShared<FFilterCategory>(NSLOCTEXT("UnrealMultiUserServer.TConcertFrontendRootFilter", "DefaultCategoryLabel", "Default"), FText::GetEmpty()) ) : Super(MakeShared<FPackageTransmissionFrontendFilter_TextSearch>(DefaultCategory, MoveTemp(Tokenizer)), MoveTemp(FrontendFilters), NonVisualFilters, DefaultCategory)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L34 _prototype_ `TSharedRef<FPackageTransmissionFilter_FrontendRoot> MakeFilter(TSharedRef<FPackageTransmissionEntryTokenizer> Tokenizer);` (scope `UE::MultiUserServer`) — Creates a filter for the global filter log window

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Filter/PackageTransmissionFrontendFilter_TextSearch.h` (Private)


#### class `UE::MultiUserServer::FPackageTransmissionFilter_TextSearch`  
`class FPackageTransmissionFilter_TextSearch : public TConcertFilter_TextSearch<const FPackageTransmissionEntry&>`  
_L11-36_
- inherits: `TConcertFilter_TextSearch<constFPackageTransmissionEntry&>`
- L15 _public function_ `FPackageTransmissionFilter_TextSearch(TSharedRef<FPackageTransmissionEntryTokenizer> Tokenizer) : Tokenizer(MoveTemp(Tokenizer))`
- L21 _protected function_ `virtual void GenerateSearchTerms(const FPackageTransmissionEntry& InItem, TArray<FString>& OutTerms) const override`
- L35 _private member_ `TSharedRef<FPackageTransmissionEntryTokenizer> Tokenizer;` — Helps in converting FConcertLog members into search terms

#### class `UE::MultiUserServer::FPackageTransmissionFrontendFilter_TextSearch`  
`class FPackageTransmissionFrontendFilter_TextSearch : public TConcertFrontendFilter_TextSearch<FPackageTransmissionFilter_TextSearch, const FPackageTransmissionEntry&>`  
_L38-46_
- inherits: `TConcertFrontendFilter_TextSearch<FPackageTransmissionFilter_TextSearch,constFPackageTransmissionEntry&>`
- L40 _private typedef_ `using Super = TConcertFrontendFilter_TextSearch<FPackageTransmissionFilter_TextSearch, const FPackageTransmissionEntry&>;`
- L43 _public function_ `FPackageTransmissionFrontendFilter_TextSearch(TSharedPtr<FFilterCategory> InCategory, TSharedRef<FPackageTransmissionEntryTokenizer> Tokenizer) : Super(MoveTemp(InCategory), MoveTemp(Tokenizer))`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Model/FilteredPackageTransmissionModel.h` (Private)


#### class `UE::MultiUserServer::FFilteredPackageTransmissionModel`  
`class FFilteredPackageTransmissionModel : public IPackageTransmissionEntrySource`  
_L13-45_
- inherits: `IPackageTransmissionEntrySource`
- L17 _public prototype_ `FFilteredPackageTransmissionModel(TSharedRef<IPackageTransmissionEntrySource> RealSource, TSharedRef<IFilter<const FPackageTransmissionEntry&>> Filter);`
- L21 _public function_ `virtual const TArray<TSharedPtr<FPackageTransmissionEntry>>& GetEntries() override`
- L22 _public prototype_ `virtual TSharedPtr<FPackageTransmissionEntry> GetEntryById(FPackageTransmissionId ID) override;`
- L23 _public function_ `virtual FOnPackageEntriesAdded& OnPackageEntriesAdded() override`
- L24 _public function_ `virtual FOnPackageEntriesModified& OnPackageEntriesModified() override`
- L29 _private member_ `TSharedRef<IPackageTransmissionEntrySource> RealSource;`
- L30 _private member_ `TSharedRef<IFilter<const FPackageTransmissionEntry&>> Filter;`
- L32 _private member_ `FOnPackageEntriesAdded OnPackageEntriesAddedDelegate;`
- L33 _private member_ `FOnPackageEntriesModified OnPackageEntriesModifiedDelegate;`
- L35 _private member_ `TArray<TSharedPtr<FPackageTransmissionEntry>> FilteredEntries;`
- L36 _private member_ `TMap<FPackageTransmissionId, FPackageTransmissionId> RebindRealSourceToFilteredIndex;`
- L38 _private prototype_ `void OnSourceEntriesAdded(uint32 NumAdded);`
- L39 _private prototype_ `void OnSourceEntriesModified(const TSet<FPackageTransmissionId>& ModifiedEntries);`
- L41 _private prototype_ `TOptional<FPackageTransmissionId> TranslatedSourceIndexToFilteredIndex(const FPackageTransmissionId OriginalId) const;`
- L43 _private prototype_ `void ReapplyFilter(bool bSilent);`
- L44 _private prototype_ `void ApplyFilter(bool bSilent = false, int32 StartIndex = 0);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Model/IPackageTransmissionEntrySource.h` (Private)


#### class `UE::MultiUserServer::IPackageTransmissionEntrySource`  
`class IPackageTransmissionEntrySource`  
_L10-28_
- desc: Interfaces for an object that provides access to package transmissions - could be filtered or unfiltered.
- L14 _public prototype_ `virtual const TArray<TSharedPtr<FPackageTransmissionEntry>>& GetEntries() = 0;`
- L17 _public prototype_ `virtual TSharedPtr<FPackageTransmissionEntry> GetEntryById(FPackageTransmissionId ID) = 0;` — @return The entry if valid - nullptr if not valid
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageEntriesAdded, uint32 ) virtual FOnPackageEntriesAdded& OnPackageEntriesAdded() = 0;` — Special version of OnPackageEntryArrayChanged that is called when entries are added. The last NumEntries number of elements in GetEntries are new.
- L24 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageEntriesModified, const TSet<FPackageTransmissionId>& );` — Called when the contents of an entry is changes.
- L25 _public prototype_ `virtual FOnPackageEntriesModified& OnPackageEntriesModified() = 0;`
- L27 _public prototype_ `virtual ~IPackageTransmissionEntrySource() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageEntriesAdded, uint32 ) virtual FOnPackageEntriesAdded& OnPackageEntriesAdded() = 0;` — Special version of OnPackageEntryArrayChanged that is called when entries are added. The last NumEntries number of elements in GetEntries are new.
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageEntriesModified, const TSet<FPackageTransmissionId>& );` — Called when the contents of an entry is changes.

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Model/PackageTransmissionEntry.h` (Private)


#### enum `UE::MultiUserServer::EPackageTransmissionState`  
`enum class EPackageTransmissionState : uint8`  
_L11-19_
- L14 _public enumerator_ `InTransmission` — We were told that the transmission has started and waiting for the destination to receive it.
- L16 _public enumerator_ `ReceivedAndAccepted` — The package was received and the data was not rejected; only the server rejects data.
- L18 _public enumerator_ `Rejected` — The server rejected the update (bad request, client had no lock, multiple clients modified concurrently, etc.)

#### enum `UE::MultiUserServer::EPackageSendDirection`  
`enum class EPackageSendDirection : uint8`  
_L21-25_
- L23 _public enumerator_ `ClientToServer`
- L24 _public enumerator_ `ServerToClient`

#### struct `UE::MultiUserServer::FPackageTransmissionEntry`  
`struct FPackageTransmissionEntry`  
_L38-74_
- desc: Describes the transmission of a single packet from one network point to another. Package transmission to the server happens in two stages: 1. The client announces it is about to send a package - that's when this entry is created 2. The server receives the package data - that's when MessageId is set Package transmission to the client happens in two stages: 1. The server sends all package data to the client - that's when this entry is created 2. The client sends an ACK - that's when MessageID is set
- L41 _public member_ `FPackageTransmissionId TransmissionId;` — Unique ID created by our internal package transmission model - it's internally an array entry (implementation detail -  don't assume it)
- L43 _public member_ `FDateTime LocalStartTime = FDateTime::Now();`
- L44 _public member_ `EPackageTransmissionState TransmissionState = EPackageTransmissionState::InTransmission;`
- L46 _public member_ `EPackageSendDirection SendDirection;`
- L48 _public member_ `FConcertPackageInfo PackageInfo;`
- L49 _public member_ `uint64 Revision;`
- L52 _public member_ `uint64 PackageNumBytes;` — The origin endpoint announced that the package would have this size
- L55 _public member_ `FGuid ClientEndpointId;` — The endpoint ID of the participating client.
- L64 _public member_ `TOptional<FGuid> MessageId;` — The ID of the message that causes the package to be acknowledged. Only set if TransmissionState != EPackageTransmissionState::InTransmission. In the case of sending to a client, it is the acknowledgement message. In the case of receiving from client, it is the message transmitting the sync activity.
- L66 _public function_ `FPackageTransmissionEntry(FPackageTransmissionId TransmissionId, EPackageSendDirection SendDirection, const FConcertPackageInfo& PackageInfo, uint64 Revision, uint64 PackageNumBytes, const FGuid& RemoteEndpointId) : TransmissionId(TransmissionId) , SendDirection(SendDirection) , PackageInfo(PackageInfo) , Revision(Revision) , PackageNumBytes(PackageNumBytes) , ClientEndpointId(RemoteEndpointId)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L9 _typedef_ `using FPackageTransmissionId = uint64;` (scope `UE::MultiUserServer`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Model/PackageTransmissionModel.h` (Private)


#### class `UE::MultiUserServer::FPackageTransmissionModel`  
`class FPackageTransmissionModel : public IPackageTransmissionEntrySource`  
_L20-59_
- inherits: `IPackageTransmissionEntrySource`
- L24 _public prototype_ `FPackageTransmissionModel(TSharedRef<IConcertSyncServer> Server);`
- L28 _public function_ `virtual const TArray<TSharedPtr<FPackageTransmissionEntry>>& GetEntries() override`
- L29 _public function_ `virtual TSharedPtr<FPackageTransmissionEntry> GetEntryById(FPackageTransmissionId ID) override`
- L30 _public function_ `virtual FOnPackageEntriesAdded& OnPackageEntriesAdded() override`
- L31 _public function_ `virtual FOnPackageEntriesModified& OnPackageEntriesModified() override`
- L36 _private member_ `TSharedRef<IConcertSyncServer> Server;`
- L37 _private member_ `TArray<TSharedPtr<FPackageTransmissionEntry>> Entries;`
- L39 _private member_ `FOnPackageEntriesAdded OnPackageEntriesAddedDelegate;`
- L40 _private member_ `FOnPackageEntriesModified OnPackageEntriesModifiedDelegate;`
- L42 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L43 _private member_ `uint32 NumAddedSinceLastTick = 0;`
- L44 _private member_ `TSet<FPackageTransmissionId> ModifiedSinceLastTick;`
- L45 _private member_ `TMap<FGuid, FPackageTransmissionId> InTransmissionToIndex;`
- L47 _private prototype_ `void OnLocalBeginSendPackage(const ConcertSyncCore::ConcertPackageEvents::FConcertBeginSendPackageParams& Args);`
- L48 _private prototype_ `void OnLocalFinishSendPackage(const ConcertSyncCore::ConcertPackageEvents::FConcertFinishSendPackageParams& Args);`
- L49 _private prototype_ `void OnRemoteBeginSendPackage(const ConcertSyncCore::ConcertPackageEvents::FConcertBeginSendPackageParams& Args);`
- L50 _private prototype_ `void OnRemoteFinishSendPackage(const ConcertSyncCore::ConcertPackageEvents::FConcertFinishSendPackageParams& Args);`
- L51 _private prototype_ `void OnRejectRemoteSendPackage(const ConcertSyncCore::ConcertPackageEvents::FConcertRejectSendPackageParams& Args);`
- L53 _private prototype_ `void HandleBeginSend(EPackageSendDirection SendDirection, const ConcertSyncCore::ConcertPackageEvents::FConcertBeginSendPackageParams& Args);`
- L54 _private prototype_ `void HandleFinishSend(EPackageTransmissionState TransmissionState, const ConcertSyncCore::ConcertPackageEvents::FConcertFinishSendPackageParams& Args);`
- L56 _private prototype_ `uint64 DeterminePackageRevision(EPackageSendDirection SendDirection, const ConcertSyncCore::ConcertPackageEvents::FConcertBeginSendPackageParams& Args) const;`
- L58 _private prototype_ `bool Tick(float);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L11 _namespace_ `namespace ConcertPackageEvents` (scope `UE::ConcertSyncCore`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/PackageTransmissionTabController.h` (Private)


#### class `UE::MultiUserServer::FPackageTransmissionTabController`  
`class FPackageTransmissionTabController`  
_L20-47_
- desc: Manages a tab that displays a package transmission model
- L24 _public prototype_ `FPackageTransmissionTabController( FName TabId, TSharedRef<FTabManager> OwningTabManager, TSharedRef<FWorkspaceItem> WorkspaceItem, TSharedRef<FPackageTransmissionModel> TransmissionModel, TSharedRef<FEndpointToUserNameCache> EndpointToUserNameCache, FCanScrollToLog CanScrollToLogDelegate, FScrollToLog ScrollToLogDelegate );`
- L33 _public prototype_ `~FPackageTransmissionTabController();`
- L37 _private member_ `FName TabId;`
- L38 _private member_ `TSharedRef<FTabManager> OwningTabManager;`
- L39 _private member_ `TSharedRef<FPackageTransmissionModel> TransmissionModel;`
- L41 _private member_ `FCanScrollToLog CanScrollToLogDelegate;`
- L42 _private member_ `FScrollToLog ScrollToLogDelegate;`
- L44 _private member_ `TSharedRef<FPackageTransmissionEntryTokenizer> Tokenizer;`
- L46 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& SpawnTabArgs);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/SPackageTransmissionTable.h` (Private)


#### class `UE::MultiUserServer::SPackageTransmissionTable`  
`class SPackageTransmissionTable : public SCompoundWidget`  
_L23-65_
- inherits: `SCompoundWidget`
- desc: Displays sent and received packages in a table
- L27 _public function_ `SLATE_BEGIN_ARGS(SPackageTransmissionTable)`
- L29 _public prototype_ `SLATE_ATTRIBUTE(uint32, TotalUnfilteredNum) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_EVENT(FCanScrollToLog, CanScrollToLog) SLATE_EVENT(FScrollToLog, ScrollToLog) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPackageTransmissionEntrySource> InPackageEntrySource, TSharedRef<FPackageTransmissionEntryTokenizer> InTokenizer);`
- L38 _public prototype_ `TSharedRef<SWidget> CreateViewOptionsButton();`
- L42 _private member_ `TSharedPtr<IPackageTransmissionEntrySource> PackageEntrySource;`
- L43 _private member_ `TSharedPtr<FPackageTransmissionEntryTokenizer> Tokenizer;`
- L45 _private member_ `TAttribute<FText> HighlightText;`
- L46 _private member_ `FCanScrollToLog CanScrollToLogDelegate;`
- L47 _private member_ `FScrollToLog ScrollToLogDelegate;`
- L49 _private member_ `TSharedPtr<SListView<TSharedPtr<FPackageTransmissionEntry>>> TableView;`
- L50 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L52 _private member_ `bool bIsUpdatingColumnVisibility = false;` — Whether we currently loading the column visibility - prevents infinite event recursion
- L55 _private prototype_ `TSharedRef<SWidget> CreateTableView();` — Table view creation
- L56 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRow();`
- L57 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FPackageTransmissionEntry> Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L59 _private prototype_ `void OnColumnVisibilitySettingsChanged(const FColumnVisibilitySnapshot& ColumnSnapshot);`
- L60 _private prototype_ `void RestoreDefaultColumnVisibilities() const;`
- L61 _private prototype_ `TMap<FName, bool> GetDefaultColumnVisibilities() const;`
- L63 _private prototype_ `void OnPackageEntriesModified(const TSet<FPackageTransmissionId>& Set) const;`
- L64 _private prototype_ `void OnPackageArrayChanged(uint32 NumAdded) const;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/SPackageTransmissionTableFooter.h` (Private)


#### class `UE::MultiUserServer::SPackageTransmissionTableFooter`  
`class SPackageTransmissionTableFooter : public SCompoundWidget`  
_L15-33_
- inherits: `SCompoundWidget`
- desc: Contains all UI for displaying package transmission, including filters, the table, and view options.
- L19 _public function_ `DECLARE_DELEGATE_OneParam(FExtendContextMenu, FMenuBuilder&) SLATE_BEGIN_ARGS(SPackageTransmissionTableFooter)`
- L23 _public prototype_ `SLATE_EVENT(FExtendContextMenu, ExtendViewOptions) SLATE_ATTRIBUTE(uint32, TotalUnfilteredNum) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPackageTransmissionEntrySource> InPackageEntrySource);`
- L31 _private member_ `TSharedPtr<IPackageTransmissionEntrySource> PackageEntrySource;`
- L32 _private member_ `TAttribute<uint32> TotalUnfilteredNum;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FExtendContextMenu, FMenuBuilder&) SLATE_BEGIN_ARGS(SPackageTransmissionTableFooter) {} SLATE_EVENT(FExtendContextMenu, ExtendViewOptions) SLATE_ATTRIBUTE(uint32, TotalUnfilteredNum) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPackageTransmissionEntrySource> InPackageEntrySource);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/SPackageTransmissionTableRow.h` (Private)


#### class `UE::MultiUserServer::SPackageTransmissionTableRow`  
`class SPackageTransmissionTableRow : public SMultiColumnTableRow<TSharedPtr<FPackageTransmissionEntry>>`  
_L21-70_
- inherits: `SMultiColumnTableRow<TSharedPtr<FPackageTransmissionEntry>>`
- L25 _public member_ `static const FName TimeColumn;`
- L26 _public member_ `static const FName OriginColumn;`
- L27 _public member_ `static const FName DestinationColumn;`
- L28 _public member_ `static const FName SizeColumn;`
- L29 _public member_ `static const FName RevisionColumn;`
- L30 _public member_ `static const FName PackagePathColumn;`
- L31 _public member_ `static const FName PackageNameColumn;`
- L32 _public member_ `static const FName TransmissionStateColumn;`
- L34 _public member_ `static const TArray<FName> AllColumns;`
- L35 _public member_ `static const TMap<FName, FText> ColumnsDisplayText;`
- L37 _public function_ `SLATE_BEGIN_ARGS(SPackageTransmissionTableRow)`
- L39 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_EVENT(FCanScrollToLog, CanScrollToLog) SLATE_EVENT(FScrollToLog, ScrollToLog) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FPackageTransmissionEntry> InPackageEntry, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<FPackageTransmissionEntryTokenizer> InTokenizer);`
- L47 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L52 _private member_ `TSharedPtr<FPackageTransmissionEntry> PackageEntry;`
- L53 _private member_ `TSharedPtr<FPackageTransmissionEntryTokenizer> Tokenizer;`
- L55 _private member_ `TAttribute<FText> HighlightText;`
- L56 _private member_ `FCanScrollToLog CanScrollToLogDelegate;`
- L57 _private member_ `FScrollToLog ScrollToLogDelegate;`
- L59 _private prototype_ `TSharedRef<SWidget> CreateTransmissionStateColumn() const;`
- L61 _private prototype_ `TSharedRef<SWidget> CreateTransmissionInProgressWidget() const;`
- L62 _private prototype_ `TSharedRef<SWidget> CreateTransmissionSuccessWidget() const;`
- L63 _private prototype_ `TSharedRef<SWidget> CreateTransmissionFailureWidget() const;`
- L64 _private prototype_ `TSharedRef<SWidget> SharedCreateTransmissionCompletedWidget(EPackageTransmissionState AllowedTransmissionState, const FSlateBrush* ImageBrush) const;`
- L66 _private function_ `bool CanScrollToLog() const`
- L67 _private prototype_ `bool CanScrollToLog(FText& ErrorMessage) const;`
- L68 _private prototype_ `void ScrollToLog() const;`
- L69 _private prototype_ `bool SharedFilterLogEntry(const FConcertLogEntry& Entry) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/SPackageTransmissionView.h` (Private)


#### class `UE::MultiUserServer::SPackageTransmissionView`  
`class SPackageTransmissionView : public SCompoundWidget`  
_L18-42_
- inherits: `SCompoundWidget`
- desc: Contains all UI for displaying package transmission, including filters, the table, and view options.
- L22 _public function_ `SLATE_BEGIN_ARGS(SPackageTransmissionView)`
- L24 _public prototype_ `SLATE_EVENT(FCanScrollToLog, CanScrollToLog) SLATE_EVENT(FScrollToLog, ScrollToLog) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPackageTransmissionEntrySource> InPackageEntrySource, TSharedRef<FPackageTransmissionEntryTokenizer> InTokenizer);`
- L32 _private member_ `TSharedPtr<IPackageTransmissionEntrySource> PackageEntrySource;`
- L34 _private member_ `TSharedPtr<FPackageTransmissionFilter_FrontendRoot> RootFilter;`
- L35 _private member_ `TSharedPtr<FFilteredPackageTransmissionModel> FilteredModel;`
- L37 _private member_ `FCanScrollToLog CanScrollToLogDelegate;`
- L38 _private member_ `FScrollToLog ScrollToLogDelegate;`
- L40 _private prototype_ `TSharedRef<SWidget> CreateOptionsButton();`
- L41 _private prototype_ `TSharedRef<SWidget> CreateOptionsButtonMenu();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/PackageTransmission/Util/PackageTransmissionEntryTokenizer.h` (Private)


#### class `UE::MultiUserServer::FPackageTransmissionEntryTokenizer`  
`class FPackageTransmissionEntryTokenizer`  
_L14-32_
- desc: Helps with printing FPackageTransmissionEntry to text so text search can search exactly what is displayed in the UI.
- L18 _public prototype_ `FPackageTransmissionEntryTokenizer(TSharedRef<FEndpointToUserNameCache> EndpointInfoGetter);`
- L20 _public prototype_ `FString TokenizeTime(const FPackageTransmissionEntry& Entry) const;`
- L21 _public prototype_ `FString TokenizeOrigin(const FPackageTransmissionEntry& Entry) const;`
- L22 _public prototype_ `FString TokenizeDestination(const FPackageTransmissionEntry& Entry) const;`
- L23 _public prototype_ `FString TokenizeSize(const FPackageTransmissionEntry& Entry) const;`
- L24 _public prototype_ `FString TokenizeRevision(const FPackageTransmissionEntry& Entry) const;`
- L25 _public prototype_ `FString TokenizePackagePath(const FPackageTransmissionEntry& Entry) const;`
- L26 _public prototype_ `FString TokenizePackageName(const FPackageTransmissionEntry& Entry) const;`
- L31 _private member_ `TSharedRef<FEndpointToUserNameCache> EndpointInfoGetter;` — Used so we can look up client and server info (even after client has disconnected)

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/SConcertClientsTabView.h` (Private)


#### class `UE::MultiUserServer::SConcertClientsTabView`  
`class SConcertClientsTabView : public SConcertTabViewWithManagerBase`  
_L28-83_
- inherits: `SConcertTabViewWithManagerBase`
- desc: Manages the UI logic of the Clients tab
- L32 _public member_ `static const FName ClientBrowserTabId;`
- L33 _public member_ `static const FName GlobalLogTabId;`
- L34 _public member_ `static const FName PackageTransmissionTabId;`
- L36 _public function_ `SLATE_BEGIN_ARGS(SConcertClientsTabView)`
- L38 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ConstructUnderMajorTab) SLATE_ARGUMENT(TSharedPtr<SWindow>, ConstructUnderWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FName InStatusBarID, TSharedRef<IConcertSyncServer> InServer, TSharedRef<FGlobalLogSource> InLogBuffer);`
- L44 _public prototype_ `void ShowConnectedClients(const FGuid& SessionId) const;`
- L45 _public prototype_ `void OpenGlobalLogTab() const;`
- L46 _public prototype_ `void CloseGlobalLogTab() const;`
- L47 _public prototype_ `void OpenClientLogTab(const FGuid& ClientMessageNodeId) const;`
- L50 _public prototype_ `bool CanScrollToLog(const FGuid& MessageId, FConcertLogEntryFilterFunc FilterFunc, FText& ErrorMessage) const;` — Whether it is possible to call ScrollToLog.
- L52 _public prototype_ `void ScrollToLog(const FGuid& MessageId, FConcertLogEntryFilterFunc FilterFunc) const;` — Scrolls to the log in the server log tab.
- L54 _public prototype_ `bool IsGlobalLogOpen() const;`
- L55 _public prototype_ `TSharedPtr<SDockTab> GetGlobalLogTab() const;`
- L60 _private member_ `TSharedPtr<IConcertSyncServer> Server;` — Used to look up client info
- L62 _private member_ `TSharedPtr<FGlobalLogSource> LogBuffer;` — Buffers all logs globally
- L65 _private member_ `TSharedPtr<FEndpointToUserNameCache> ClientInfoCache;` — Caches client info so it remains available even after a client disconnects
- L67 _private member_ `TSharedPtr<FConcertLogTokenizer> LogTokenizer;` — Used by various systems to convert logs to text
- L70 _private member_ `TSharedPtr<FPackageTransmissionModel> PackageTransmissionModel;` — Knows about when packages are sent and received by the server
- L71 _private member_ `TSharedPtr<FPackageTransmissionTabController> MainPackageTransmissionTab;`
- L73 _private member_ `TSharedPtr<SConcertNetworkBrowser> ClientBrowser;`
- L76 _private member_ `TSharedPtr<SConcertTransportLog> GlobalTransportLog;` — The widget inside of the server log tab
- L78 _private prototype_ `void CreateTabs(const TSharedRef<FTabManager>& InTabManager, const TSharedRef<FTabManager::FLayout>& InLayout, const FArguments& InArgs);`
- L79 _private prototype_ `TSharedRef<SDockTab> SpawnClientBrowserTab(const FSpawnTabArgs& InTabArgs);`
- L80 _private prototype_ `TSharedRef<SDockTab> SpawnGlobalLogTab(const FSpawnTabArgs& InTabArgs);`
- L82 _private prototype_ `TSharedRef<SWidget> CreateOpenGlobalLogButton() const;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/SPromptConcertLoggingEnabled.h` (Private)


#### class `SPromptConcertLoggingEnabled`  
`class SPromptConcertLoggingEnabled : public SCompoundWidget`  
_L8-16_
- inherits: `SCompoundWidget`
- desc: Placed in an overlay, reminds the user to execute Concert.EnableLogging if logging is not enabled.
- L12 _public function_ `SLATE_BEGIN_ARGS(SPromptConcertLoggingEnabled)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Clients/Util/EndpointToUserNameCache.h` (Private)


#### class `FEndpointToUserNameCache`  
`class FEndpointToUserNameCache`  
_L23-76_
- desc: Responsible for keeping hold of client info even when the client disconnects. Client info is removed server-side upon disconnect but logs need their display info.
- L28 _public typedef_ `using FNodeEndpointId = FGuid;` — ID used by the messaging system - corresponds to an IP address.
- L30 _public prototype_ `FEndpointToUserNameCache(TSharedRef<IConcertServer> Server);`
- L31 _public prototype_ `~FEndpointToUserNameCache();`
- L33 _public prototype_ `bool IsServerEndpoint(const FGuid& EndpointId) const;`
- L35 _public prototype_ `TOptional<FConcertClientInfo> GetClientInfo(const FGuid& EndpointId) const;` — Gets the client info given from any endpoint ID (any ID of a FConcertRemoteEndpoint)
- L37 _public prototype_ `TOptional<FConcertClientInfo> GetClientInfoFromNodeId(const FNodeEndpointId& EndpointId) const;` — Gets the client info given from any endpoint node ID (the ID from the messaging system node - corresponds to IP address).
- L40 _public prototype_ `TOptional<FNodeEndpointId> TranslateEndpointIdToNodeId(const FGuid& EndpointId) const;` — Translates a Concert endpoint Id to the corresponding messaging node Id
- L43 _public prototype_ `FString GetEndpointDisplayString(const FGuid& EndpointId) const;` — Gets either the client's name or "Server" depending on type of endpoint this is
- L48 _private member_ `TSharedRef<IConcertServer> Server;` — Used to unsubscribe when we're destroyed
- L50 _private member_ `TSet<TWeakPtr<IConcertServerSession>> SubscribedToSessions;` — Used to unsubscribe when we're destroyed
- L58 _private member_ `TMap<FNodeEndpointId, FConcertClientInfo> CachedClientData;` — The client info we're caching. Concert may generate multiple endpoint IDs for a single remote machine. However, the remote node ID is always unique and is retrieved by querying the UDP backend (see GetNodeIdFromMessagingBackend).
- L64 _private member_ `TMap<FGuid, FNodeEndpointId> CachedConcertEndpointToNodeEndpoints;` — Keeps track of past endpoints IDs that may now no longer be valid. Every time a client joins a session, a new endpoint ID is generated for that client. It becomes impossible to lookup old concert endpoint IDs without this mapping
- L66 _private prototype_ `void OnLiveSessionCreated(bool bSuccess, const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession);`
- L67 _private prototype_ `void OnLiveSessionDestroyed(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession);`
- L68 _private prototype_ `void OnClientInfoChanged(IConcertServerSession& Session, EConcertClientStatus ConnectionStatus, const FConcertSessionClientInfo& ClientInfo);`
- L70 _private prototype_ `void OnAdminEndpointConnectionChanged(const FConcertEndpointContext& ConcertEndpointContext, EConcertRemoteEndpointConnection ConcertRemoteEndpointConnection);`
- L72 _private prototype_ `void RegisterLiveSession(const TSharedRef<IConcertServerSession>& InLiveSession);`
- L73 _private prototype_ `void CacheClientInfo(const IConcertServerSession& Session, const FConcertSessionClientInfo& ClientInfo);`
- L75 _private prototype_ `FNodeEndpointId GetNodeIdFromMessagingBackend(const FMessageAddress& MessageAddress) const;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/HistoryEdition/SActivityDependencyDialog.h` (Private)


#### class `UE::MultiUserServer::SActivityDependencyDialog`  
`class SActivityDependencyDialog : public SCustomDialog`  
_L20-72_
- inherits: `SCustomDialog`
- desc: Base dialog for perform actions activity dependencies, notably for deleting and muting activities.
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FConfirmDependencyAction, const TSet<FActivityID>& ) DECLARE_DELEGATE_RetVal_TwoParams(FText, FGetFinalInclusionResultText, const int64 , bool );`
- L27 _public function_ `SLATE_BEGIN_ARGS(SActivityDependencyDialog)`
- L29 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FText, Description) SLATE_ARGUMENT(FText, PerformActionButtonLabel) SLATE_EVENT(FConfirmDependencyAction, OnConfirmAction) SLATE_EVENT(SActivityDependencyView::FAnalyseActivities, AnalyseActivities) SLATE_EVENT(FGetFinalInclusionResultText, GetFinalInclusionResultText) SLATE_EVENT(SActivityDependencyView::FShouldShowActivity, ShouldShowActivity) SLATE_ARGUMENT(TArray<FActivityColumn>, AdditionalColumns) SLATE_ATTRIBUTE(FText, ConfirmDialogTitle) SLATE_ATTRIBUTE(FText, ConfirmDialogMessage) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FGuid& SessionId, const TSharedRef<IConcertSyncServer>& SyncServer, TSet<FActivityID> InBaseActivities);`
- L61 _private member_ `TSharedPtr<SActivityDependencyView> DependencyView;`
- L63 _private member_ `FConfirmDependencyAction OnConfirmActionFunc;`
- L64 _private member_ `FGetFinalInclusionResultText GetFinalInclusionResultTextFunc;`
- L66 _private member_ `TAttribute<FText> ConfirmDialogTitle;`
- L67 _private member_ `TAttribute<FText> ConfirmDialogMessage;`
- L69 _private prototype_ `TSharedRef<SWidget> CreateBody(const FArguments& InArgs, const FGuid& InSessionId, const TSharedRef<IConcertSyncServer>& InSyncServer, TSet<FActivityID> InBaseActivities);`
- L71 _private prototype_ `void OnConfirmPressed();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FConfirmDependencyAction, const TSet<FActivityID>& ) DECLARE_DELEGATE_RetVal_TwoParams(FText, FGetFinalInclusionResultText, const int64 , bool );`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FGetFinalInclusionResultText, const int64 , bool );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/HistoryEdition/SActivityDependencyView.h` (Private)


#### class `UE::MultiUserServer::SActivityDependencyView`  
`class SActivityDependencyView : public SCompoundWidget`  
_L20-77_
- inherits: `SCompoundWidget`
- desc: A view for displaying activity dependencies. Each row has a checkbox. Useful for actions, such as deleting, muting, and unmuting. Adds additional dependencies depending on what optional dependencies are checked.
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FAbstractSessionHistoryController>, FCreateSessionHistoryController, const SSessionHistory::FArguments& ) DECLARE_DELEGATE_RetVal_TwoParams(ConcertSyncCore::FHistoryAnalysisResult, FAnalyseActivities, const ConcertSyncCore::FActivityDependencyGraph&, const TSet<FActivityID>& );`
- L26 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldShowActivity, const FConcertSyncActivity );`
- L27 _public function_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FGetCheckboxToolTip, const int64& , bool ) SLATE_BEGIN_ARGS(SActivityDependencyView)`
- L32 _public prototype_ `SLATE_ARGUMENT(TSet<FActivityID>, BaseActivities) SLATE_EVENT(FCreateSessionHistoryController, CreateSessionHistoryController) SLATE_EVENT(FAnalyseActivities, AnalyseActivities) SLATE_EVENT(FShouldShowActivity, ShouldShowActivity) SLATE_EVENT(FGetCheckboxToolTip, GetCheckboxToolTip) SLATE_ARGUMENT(TArray<FActivityColumn>, AdditionalColumns) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ConcertSyncCore::FActivityDependencyGraph InDependencyGraph);` — The activities this view is based on. Always checked.
- L51 _public prototype_ `bool IsChecked(FActivityID ActivityID) const;` — @return Whether the given activity ID is checked
- L52 _public prototype_ `TSet<FActivityID> GetSelection() const;`
- L57 _private member_ `TSharedPtr<FAbstractSessionHistoryController> SessionHistoryController;` — Used to render the rows
- L60 _private member_ `ConcertSyncCore::FActivityDependencyGraph DependencyGraph;` — Built once on construction.
- L63 _private member_ `TSet<FActivityID> BaseActivities;` — The activities this view is based on. Always checked.
- L64 _private member_ `TSet<FActivityID> UserSelectedActivities;`
- L67 _private member_ `ConcertSyncCore::FHistoryAnalysisResult Selection;` — The current selection. Updated every time something is checked.
- L69 _private member_ `FAnalyseActivities AnalyseActivitiesDelegate;`
- L70 _private member_ `FShouldShowActivity ShouldShowActivity;`
- L71 _private member_ `FGetCheckboxToolTip GetCheckboxToolTipDelegate;`
- L73 _private prototype_ `void OnCheckBoxStateChanged(const FActivityID ActivityId, bool bIsChecked);`
- L74 _private prototype_ `TSharedPtr<SWidget> CreateCheckboxOverlay(TWeakPtr<SMultiColumnTableRow<TSharedPtr<FConcertSessionActivity>>> Row, TWeakPtr<FConcertSessionActivity> Activity, const FName& ColumnName);`
- L76 _private prototype_ `bool CanRemoveMandatorySelection(const FActivityID ActivityID) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FAbstractSessionHistoryController>, FCreateSessionHistoryController, const SSessionHistory::FArguments& ) DECLARE_DELEGATE_RetVal_TwoParams(ConcertSyncCore::FHistoryAnalysisResult, FAnalyseActivities, const ConcertSyncCore::FActivityDependencyGraph&, const TSet<FActivityID>& );`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(ConcertSyncCore::FHistoryAnalysisResult, FAnalyseActivities, const ConcertSyncCore::FActivityDependencyGraph&, const TSet<FActivityID>& );`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldShowActivity, const FConcertSyncActivity );`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FGetCheckboxToolTip, const int64& , bool ) SLATE_BEGIN_ARGS(SActivityDependencyView) {} SLATE_ARGUMENT(TSet<FActivityID>, BaseActivities) SLATE_EVENT(FCreateSessionHistoryController, CreateSessionHistoryController) SLATE_EVENT(FAnalyseActivities, AnalyseActivities) SLATE_EVENT(FShouldShowActivity, ShouldShowActivity) SLATE_EVENT(FGetCheckboxToolTip, GetCheckboxToolTip) SLATE_ARGUMENT(TArray<FActivityColumn>, AdditionalColumns) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ConcertSyncCore::FActivityDependencyGraph InDependencyGraph);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/HistoryEdition/SDeleteActivityDependenciesDialog.h` (Private)


#### class `UE::MultiUserServer::SDeleteActivityDependenciesDialog`  
`class SDeleteActivityDependenciesDialog : public SActivityDependencyDialog`  
_L16-29_
- inherits: `SActivityDependencyDialog`
- desc: Displayed when a user asks to delete an activity.
- L19 _public function_ `SLATE_BEGIN_ARGS(SDeleteActivityDependenciesDialog)`
- L22 _public prototype_ `SLATE_EVENT(SActivityDependencyDialog::FConfirmDependencyAction, OnConfirmDeletion) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FGuid& SessionId, const TSharedRef<IConcertSyncServer>& SyncServer, TSet<FActivityID> InBaseActivities);` — Called when the user confirms the deletion of the activities.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/HistoryEdition/SMuteActivityDependenciesDialog.h` (Private)


#### class `UE::MultiUserServer::SMuteActivityDependenciesDialog`  
`class SMuteActivityDependenciesDialog : public SActivityDependencyDialog`  
_L16-46_
- inherits: `SActivityDependencyDialog`
- desc: Displayed when a user asks to delete an activity.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMuteActivityDependenciesDialog) : _MuteOperation(EMuteOperation::Mute)`
- L29 _public prototype_ `SLATE_EVENT(SActivityDependencyDialog::FConfirmDependencyAction, OnConfirmMute) SLATE_ARGUMENT(EMuteOperation, MuteOperation) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FGuid& InSessionId, const TSharedRef<IConcertSyncServer>& InSyncServer, TSet<FActivityID> InBaseActivities);` — Called when the user confirms the muting of the activities.
- L42 _private member_ `TWeakPtr<IConcertSyncServer> SyncServer;`
- L43 _private member_ `FGuid SessionId;`
- L45 _private prototype_ `bool IsMuted(const int64 ActivityId);`

#### enum `UE::MultiUserServer::SMuteActivityDependenciesDialog::EMuteOperation`  
`enum class EMuteOperation`  
_L19-23_
- L21 _public enumerator_ `Mute`
- L22 _public enumerator_ `Unmute`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SConcertTabViewBase.h` (Private)


#### class `SConcertTabViewBase`  
`class SConcertTabViewBase : public SCompoundWidget`  
_L13-27_
- inherits: `SCompoundWidget`
- desc: Utility base class for all content that is displayed in an entire major tab. This class handles shared logic, such as creating a status bar. If the content uses a tab manager, use SConcertTabViewWithManagedBase.
- L17 _public function_ `SLATE_BEGIN_ARGS(SConcertTabViewBase)`
- L19 _public prototype_ `SLATE_NAMED_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FName InStatusBarId);` — The tab's content

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SConcertTabViewWithManagerBase.h` (Private)


#### class `SConcertTabViewWithManagerBase`  
`class SConcertTabViewWithManagerBase : public SConcertTabViewBase`  
_L11-55_
- inherits: `SConcertTabViewBase`
- desc: Base class for tab views that create sub-tabs.
- L15 _public prototype_ `DECLARE_DELEGATE_TwoParams(FCreateTabs, const TSharedRef<FTabManager>& , const TSharedRef<FTabManager::FLayout>& );`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FCreateWindowMenu, FMenuBarBuilder&);`
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOverlayTabs, const TSharedRef<SWidget>& );`
- L19 _public function_ `SLATE_BEGIN_ARGS(SConcertTabViewWithManagerBase)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ConstructUnderMajorTab) SLATE_ARGUMENT(TSharedPtr<SWindow>, ConstructUnderWindow) SLATE_EVENT(FCreateTabs, CreateTabs) SLATE_EVENT(FCreateWindowMenu, CreateMenuBar) SLATE_EVENT(FOverlayTabs, OverlayTabs) SLATE_ARGUMENT(FName, LayoutName) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FName InStatusBarId);` — Which major tab to construct the sub-tabs under.
- L42 _protected function_ `TSharedPtr<FTabManager> GetTabManager() const`
- L47 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L49 _private prototype_ `TSharedRef<SWidget> CreateTabs(const FArguments& InArgs);`
- L50 _private prototype_ `void FillInDefaultMenuItems(FMenuBarBuilder MenuBarBuilder);`
- L51 _private prototype_ `void FillWindowMenu(FMenuBuilder& MenuBuilder);`
- L52 _private prototype_ `void FillDebugMenu(FMenuBuilder& MenuBuilder);`
- L54 _private prototype_ `void AddIconWindow();`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FCreateTabs, const TSharedRef<FTabManager>& , const TSharedRef<FTabManager::FLayout>& );`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FCreateWindowMenu, FMenuBarBuilder&);`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOverlayTabs, const TSharedRef<SWidget>& );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Archived/ArchivedConcertSessionTab.h` (Private)


#### class `FArchivedConcertSessionTab`  
`class FArchivedConcertSessionTab : public FConcertSessionTabBase`  
_L16-56_
- inherits: `FConcertSessionTabBase`
- desc: Manages the tab for an archived session.
- L20 _public prototype_ `FArchivedConcertSessionTab(FGuid InspectedSessionID, TSharedRef<IConcertSyncServer> SyncServer, TAttribute<TSharedRef<SWindow>> ConstructUnderWindow);`
- L25 _protected prototype_ `virtual void CreateDockContent(const TSharedRef<SDockTab>& InDockTab) override;`
- L26 _protected prototype_ `virtual const FSlateBrush* GetTabIconBrush() const override;`
- L27 _protected function_ `virtual void OnOpenTab() override`
- L33 _private member_ `const FGuid InspectedSessionID;` — The inspected session's ID
- L36 _private member_ `const TSharedRef<IConcertSyncServer> SyncServer;` — Used later to construct Inspector
- L39 _private member_ `const TAttribute<TSharedRef<SWindow>> ConstructUnderWindow;` — Used later to obtain the window into which to add the tab
- L41 _private member_ `TSharedPtr<FArchivedSessionHistoryController> HistoryController;`
- L44 _private member_ `TSharedPtr<SConcertArchivedSessionTabView> Inspector;` — Displays session
- L46 _private prototype_ `void OnRequestDeleteActivities(const TSet<TSharedRef<FConcertSessionActivity>>& ActivitiesToDelete) const;`
- L47 _private prototype_ `FCanPerformActionResult CanDeleteActivities(const TSet<TSharedRef<FConcertSessionActivity>>& ActivitiesToDelete) const;`
- L49 _private prototype_ `void OnRequestMuteActivities(const TSet<TSharedRef<FConcertSessionActivity>>& ActivitiesToMute) const;`
- L50 _private prototype_ `FCanPerformActionResult CanMuteActivities(const TSet<TSharedRef<FConcertSessionActivity>>& ActivitiesToDelete) const;`
- L52 _private prototype_ `void OnRequestUnmuteActivities(const TSet<TSharedRef<FConcertSessionActivity>>& ActivitiesToDelete) const;`
- L53 _private prototype_ `FCanPerformActionResult CanUnmuteActivities(const TSet<TSharedRef<FConcertSessionActivity>>& ActivitiesToDelete) const;`
- L55 _private prototype_ `void SpawnDialogForMutingOrUnmuting(bool bShouldMute, const TSet<TSharedRef<FConcertSessionActivity>>& Activities) const;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Archived/ArchivedSessionHistoryController.h` (Private)


#### class `FArchivedSessionHistoryController`  
`class FArchivedSessionHistoryController : public FServerSessionHistoryControllerBase`  
_L8-21_
- inherits: `FServerSessionHistoryControllerBase`
- desc: Manages SSessionHistory by using IConcertSyncServer::GetArchivedSessionDatabase for retrieving the session database.
- L12 _protected prototype_ `FArchivedSessionHistoryController(FGuid SessionId, TSharedRef<IConcertSyncServer> SyncServer, SSessionHistory::FArguments Arguments);`
- L15 _protected prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetSessionDatabase(const FGuid& InSessionId) const override;`
- L20 _private member_ `const TSharedRef<IConcertSyncServer> SyncServer;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L26 _prototype_ `TSharedPtr<FArchivedSessionHistoryController> CreateForInspector(FGuid SessionId, TSharedRef<IConcertSyncServer> SyncServer, SSessionHistory::FArguments Arguments);` (scope `UE::MultiUserServer`) — Creates a controller that is supposed to use UMultiUserServerUserSettings::GetArchivedActivityBrowserColumnVisibility
- L29 _prototype_ `TSharedPtr<FArchivedSessionHistoryController> CreateForDeletionDialog(FGuid SessionId, TSharedRef<IConcertSyncServer> SyncServer, SSessionHistory::FArguments Arguments);` (scope `UE::MultiUserServer`) — Creates a controller that is supposed to use  UMultiUserServerUserSettings::GetDeleteActivityDialogColumnVisibility

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Archived/SConcertArchivedSessionTabView.h` (Private)


#### class `SConcertArchivedSessionTabView`  
`class SConcertArchivedSessionTabView : public SConcertTabViewWithManagerBase`  
_L13-51_
- inherits: `SConcertTabViewWithManagerBase`
- desc: Designed as content for a tab. Displays information about an archived session.
- L17 _public member_ `static const FName HistoryTabId;`
- L19 _public function_ `SLATE_BEGIN_ARGS(SConcertArchivedSessionTabView)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ConstructUnderMajorTab) SLATE_ARGUMENT(TSharedPtr<SWindow>, ConstructUnderWindow) SLATE_EVENT(SEditableSessionHistory::FMakeSessionHistory, MakeSessionHistory) SLATE_EVENT(SEditableSessionHistory::FCanPerformActionOnActivities, CanDeleteActivities) SLATE_EVENT(SEditableSessionHistory::FRequestActivitiesAction, DeleteActivities) SLATE_EVENT(SEditableSessionHistory::FCanPerformActionOnActivities, CanMuteActivities) SLATE_EVENT(SEditableSessionHistory::FRequestActivitiesAction, MuteActivities) SLATE_EVENT(SEditableSessionHistory::FCanPerformActionOnActivities, CanUnmuteActivities) SLATE_EVENT(SEditableSessionHistory::FRequestActivitiesAction, UnmuteActivities) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FName InStatusBarID);`
- L39 _private member_ `TSharedPtr<SEditableSessionHistory> SessionHistory;`
- L41 _private prototype_ `void CreateTabs(const TSharedRef<FTabManager>& InTabManager, const TSharedRef<FTabManager::FLayout>& InLayout, const FArguments& InArgs);`
- L42 _private prototype_ `TSharedRef<SDockTab> SpawnActivityHistory(const FSpawnTabArgs& Args, SEditableSessionHistory::FMakeSessionHistory FMakeSessionHistory, SEditableSessionHistory::FCanPerformActionOnActivities CanDeleteActivities, SEditableSessionHistory::FRequestActivitiesAction DeleteActivities, SEditableSessionHistory::FCanPerformActionOnActivities CanMuteActivities, SEditableSessionHistory::FRequestActivitiesAction MuteActivities, SEditableSessionHistory::FCanPerformActionOnActivities CanUnmuteActivities, SEditableSessionHistory::FRequestActivitiesAction UnmuteActivities );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/ConcertSessionTabBase.h` (Private)


#### class `FConcertSessionTabBase`  
`class FConcertSessionTabBase : public TSharedFromThis<FConcertSessionTabBase>`  
_L14-48_
- inherits: `TSharedFromThis<FConcertSessionTabBase>`
- desc: Shared functionality for a tab that manages a session
- L18 _public prototype_ `FConcertSessionTabBase(FGuid InspectedSessionID, TSharedRef<IConcertSyncServer> SyncServer);`
- L19 _public prototype_ `virtual ~FConcertSessionTabBase();`
- L22 _public prototype_ `void OpenSessionTab();` — Opens or draws attention to the given tab
- L26 _protected prototype_ `virtual void CreateDockContent(const TSharedRef<SDockTab>& DockTab) = 0;`
- L27 _protected prototype_ `virtual const FSlateBrush* GetTabIconBrush() const = 0;`
- L28 _protected prototype_ `virtual void OnOpenTab() = 0;`
- L30 _protected function_ `FGuid GetSessionID() const`
- L32 _protected function_ `FString GetTabId() const` — Generates a tab ID for FTabManager::InsertNewDocumentTab
- L33 _protected function_ `const TSharedRef<IConcertSyncServer>& GetSyncServer() const`
- L38 _private member_ `FGuid InspectedSessionID;` — The ID of the session this tab is managing
- L41 _private member_ `const TSharedRef<IConcertSyncServer> SyncServer;` — Used to look up session name
- L44 _private member_ `TSharedPtr<SDockTab> DockTab;` — The tab containing the UI for InspectedSession
- L47 _private prototype_ `void EnsureInitDockTab();` — Inits DockTab if it has not yet been inited

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Live/LiveConcertSessionTab.h` (Private)


#### class `FLiveConcertSessionTab`  
`class FLiveConcertSessionTab : public FConcertSessionTabBase`  
_L19-54_
- inherits: `FConcertSessionTabBase`
- desc: Manages the tab that contains the UI for a session. It has access to the controllers and views needed for displaying a session.
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FShowConnectedClients, const TSharedRef<IConcertServerSession>&);`
- L25 _public prototype_ `FLiveConcertSessionTab(TSharedRef<IConcertServerSession> InspectedSession, TSharedRef<IConcertSyncServer> SyncServer, TAttribute<TSharedRef<SWindow>> ConstructUnderWindow, FShowConnectedClients OnConnectedClientsClicked );`
- L34 _protected prototype_ `virtual void CreateDockContent(const TSharedRef<SDockTab>& InDockTab) override;`
- L35 _protected prototype_ `virtual const FSlateBrush* GetTabIconBrush() const override;`
- L36 _protected prototype_ `virtual void OnOpenTab() override;`
- L42 _private member_ `const TSharedRef<IConcertServerSession> InspectedSession;` — The session being inspected
- L45 _private member_ `TAttribute<TSharedRef<SWindow>> ConstructUnderWindow;` — Used to determine owning window during construction
- L48 _private member_ `FShowConnectedClients OnConnectedClientsClicked;` — Shows all connected clients for this session
- L51 _private member_ `const TSharedRef<FLiveServerSessionHistoryController> SessionHistoryController;` — Manages the session history widget
- L53 _private member_ `const TSharedRef<FConcertSessionPackageViewerController> PackageViewerController;` — Manages the package viewer widget

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FShowConnectedClients, const TSharedRef<IConcertServerSession>&);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Live/LiveServerSessionHistoryController.h` (Private)


#### class `FLiveServerSessionHistoryController`  
`class FLiveServerSessionHistoryController : public FServerSessionHistoryControllerBase`  
_L16-35_
- inherits: `FServerSessionHistoryControllerBase`
- desc: Manages SSessionHistory by using IConcertSyncServer::GetLiveSessionDatabase for retrieving the session database.
- L20 _public prototype_ `FLiveServerSessionHistoryController(TSharedRef<IConcertServerSession> InspectedSession, TSharedRef<IConcertSyncServer> SyncServer);`
- L26 _protected prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetSessionDatabase(const FGuid& InSessionId) const override;`
- L31 _private member_ `TSharedRef<IConcertSyncServer> SyncServer;`
- L33 _private prototype_ `void OnSessionProduced(const FConcertSyncActivity& ProducedActivity);`
- L34 _private prototype_ `void OnActivityListColumnVisibilitySettingsUpdated(const FColumnVisibilitySnapshot& NewValue);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Live/PackageViewer/ConcertSessionPackageViewerController.h` (Private)


#### class `FConcertSessionPackageViewerController`  
`class FConcertSessionPackageViewerController : public TSharedFromThis<FConcertSessionPackageViewerController>`  
_L20-46_
- inherits: `TSharedFromThis<FConcertSessionPackageViewerController>`
- desc: Manages SConcertSessionPackageViewer for a server.
- L24 _public prototype_ `FConcertSessionPackageViewerController(TSharedRef<IConcertServerSession> InspectedSession, TSharedRef<IConcertSyncServer> SyncServer);`
- L25 _public prototype_ `~FConcertSessionPackageViewerController();`
- L27 _public prototype_ `void ReloadActivities() const;`
- L28 _public function_ `TSharedRef<SConcertSessionPackageViewer> GetPackageViewer() const`
- L32 _private member_ `TSharedRef<IConcertServerSession> InspectedSession;`
- L33 _private member_ `TSharedRef<IConcertSyncServer> SyncServer;`
- L36 _private member_ `TSharedRef<SConcertSessionPackageViewer> PackageViewer;` — The widget being managed
- L38 _private prototype_ `TSharedRef<SConcertSessionPackageViewer> MakePackageViewer() const;`
- L40 _private prototype_ `TOptional<FConcertClientInfo> GetClientInfo(FGuid ClientId) const;`
- L41 _private prototype_ `bool GetPackageEvent(const FConcertSessionActivity& Activity, FConcertSyncPackageEventMetaData& OutPackageEvent) const;`
- L42 _private prototype_ `TOptional<int64> GetSizeOfPackageEvent(const FConcertSessionActivity& Activity) const;`
- L43 _private prototype_ `void OnSessionProduced(const FConcertSyncActivity& ProducedActivity) const;`
- L45 _private prototype_ `void OnSessionContentColumnVisibilitySettingsUpdated(const FColumnVisibilitySnapshot& NewValue);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Live/PackageViewer/PackageViewerColumns.h` (Private)


#### enum `UE::MultiUserServer::PackageViewerColumns::EPredefinedPackageColumnOrder`  
`enum class EPredefinedPackageColumnOrder : int32`  
_L19-24_
- L21 _public enumerator_ `PackageUpdateType = static_cast<int32>(ConcertSharedSlate::ActivityColumn::EPredefinedColumnOrder::AvatarColor) - 1`
- L22 _public enumerator_ `Size = static_cast<int32>(ConcertSharedSlate::ActivityColumn::EPredefinedColumnOrder::ClientName) + 1`
- L23 _public enumerator_ `Version = Size + 1`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L12 _namespace_ `namespace PackageViewerColumns` (scope `UE::MultiUserServer`)
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<EConcertPackageUpdateType>, FGetPackageUpdateType, const FConcertSessionActivity& );`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<EConcertPackageUpdateType>, FGetPackageUpdateType, const FConcertSessionActivity& );` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<int64>, FGetNumericValueFromPackageActivity, const FConcertSessionActivity& );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<int64>, FGetNumericValueFromPackageActivity, const FConcertSessionActivity& );` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L16 _typedef_ `using FGetSizeOfPackageActivity = FGetNumericValueFromPackageActivity;` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L17 _typedef_ `using FGetVersionOfPackageActivity = FGetNumericValueFromPackageActivity;` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L26 _externvar_ `extern const FName PackageUpdateTypeColumnId;` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L27 _externvar_ `extern const FName SizeColumnId;` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L28 _externvar_ `extern const FName VersionColumnId;` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L30 _prototype_ `FActivityColumn PackageUpdateTypeColumn(FGetPackageUpdateType GetPackageUpdateTypeFunc);` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L31 _prototype_ `FActivityColumn SizeColumn(FGetSizeOfPackageActivity GetEventDataFunc);` (scope `UE::MultiUserServer::PackageViewerColumns`)
- L32 _prototype_ `FActivityColumn VersionColumn(FGetVersionOfPackageActivity GetEventDataFunc);` (scope `UE::MultiUserServer::PackageViewerColumns`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Live/PackageViewer/SConcertSessionPackageViewer.h` (Private)


#### class `SConcertSessionPackageViewer`  
`class SConcertSessionPackageViewer : public SCompoundWidget`  
_L15-54_
- inherits: `SCompoundWidget`
- desc: Displays package activities that happened in a concert session.
- L19 _public function_ `SLATE_BEGIN_ARGS(SConcertSessionPackageViewer)`
- L20 _public prototype_ `SLATE_EVENT(SConcertSessionActivities::FGetPackageEvent, GetPackageEvent) SLATE_EVENT(SConcertSessionActivities::FGetActivityClientInfoFunc, GetClientInfo) SLATE_EVENT(UE::MultiUserServer::PackageViewerColumns::FGetSizeOfPackageActivity, GetSizeOfPackageActivity) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `void ResetActivityList();`
- L28 _public prototype_ `void AppendActivity(FConcertSessionActivity Activity);`
- L30 _public prototype_ `void OnColumnVisibilitySettingsChanged(const FColumnVisibilitySnapshot& ColumnSnapshot);`
- L34 _private member_ `TSharedPtr<SConcertSessionActivities> ActivityListView;`
- L37 _private member_ `TSharedPtr<FConcertSessionActivitiesOptions> ActivityListViewOptions;` — Controls the activity list view options
- L40 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The widget used to enter the text to search.
- L43 _private member_ `FText SearchedText;` — The searched text to highlight.
- L45 _private prototype_ `TOptional<EConcertPackageUpdateType> GetPackageActivityUpdateType(const FConcertSessionActivity& Activity, SConcertSessionActivities::FGetPackageEvent GetPackageEventFunc) const;`
- L46 _private prototype_ `TOptional<int64> GetVersionOfPackageActivity(const FConcertSessionActivity& Activity, SConcertSessionActivities::FGetPackageEvent GetPackageEventFunc) const;`
- L49 _private prototype_ `void OnSearchTextChanged(const FText& InSearchText);` — Invoked when the text in the search box widget changes.
- L51 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType);` — Invoked when the text in the search box widget is committed.
- L53 _private prototype_ `FText HighlightSearchedText() const;` — Returns the text to highlight when the search bar has a text set.

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/Live/SConcertLiveSessionTabView.h` (Private)


#### class `SConcertLiveSessionTabView`  
`class SConcertLiveSessionTabView : public SConcertTabViewWithManagerBase`  
_L22-62_
- inherits: `SConcertTabViewWithManagerBase`
- desc: Designed to be the content of a tab showing: - activity history (transactions stored on the server as well as who made those transactions) - session content (list of session data saved during a Multi-user session) - connection monitor (details about the connected clients on the given session and network info) Implements view in model-view-controller pattern.
- L44 _public member_ `static const FName HistoryTabId;`
- L45 _public member_ `static const FName SessionContentTabId;`
- L47 _public function_ `SLATE_BEGIN_ARGS(SConcertLiveSessionTabView)`
- L48 _public prototype_ `SLATE_NAMED_SLOT(FArguments, StatusBar) SLATE_EVENT(FSimpleDelegate, OnConnectedClientsClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FRequiredWidgets& InRequiredArgs, FName StatusBarId);`
- L57 _private prototype_ `TSharedRef<SWidget> CreateTabs(const TSharedRef<FTabManager>& InTabManager, const TSharedRef<FTabManager::FLayout>& InLayout, const FRequiredWidgets& InRequiredArgs);` — Spawn tabs
- L58 _private prototype_ `TSharedRef<SDockTab> SpawnActivityHistory(const FSpawnTabArgs& Args, TSharedRef<SSessionHistory> SessionHistory);`
- L59 _private prototype_ `TSharedRef<SDockTab> SpawnSessionContent(const FSpawnTabArgs& Args, TSharedRef<SConcertSessionPackageViewer> PackageViewer);`
- L61 _private prototype_ `TSharedRef<SWidget> CreateToolbar(const FArguments& InArgs);`

#### struct `SConcertLiveSessionTabView::FRequiredWidgets`  
`struct FRequiredWidgets`  
_L26-42_
- L28 _public member_ `TSharedRef<SDockTab> ConstructUnderMajorTab;`
- L29 _public member_ `TSharedRef<SWindow> ConstructUnderWindow;`
- L30 _public member_ `TSharedRef<SSessionHistory> SessionHistory;`
- L31 _public member_ `TSharedRef<SConcertSessionPackageViewer> PackageViewer;`
- L33 _public function_ `FRequiredWidgets(TSharedRef<SDockTab> ConstructUnderMajorTab, TSharedRef<SWindow> ConstructUnderWindow, TSharedRef<SSessionHistory> SessionHistoryController, TSharedRef<SConcertSessionPackageViewer> PackageViewerController) : ConstructUnderMajorTab(MoveTemp(ConstructUnderMajorTab)) , ConstructUnderWindow(MoveTemp(ConstructUnderWindow)) , SessionHistory(MoveTemp(SessionHistoryController)) , PackageViewer(MoveTemp(PackageViewerController))`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/ServerSessionHistoryControllerBase.h` (Private)


#### class `FServerSessionHistoryControllerBase`  
`class FServerSessionHistoryControllerBase : public FAbstractSessionHistoryController`  
_L19-44_
- inherits: `FAbstractSessionHistoryController`
- desc: Abstract base class providing most functionality for managing SSessionHistory on the server. Subclasses control which session database is used: archived or live.
- L23 _public prototype_ `FServerSessionHistoryControllerBase(FGuid SessionId, SSessionHistory::FArguments Arguments = SSessionHistory::FArguments());`
- L28 _protected prototype_ `virtual void GetActivities(int64 MaximumNumberOfActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, TArray<FConcertSessionActivity>& OutFetchedActivities) const override;`
- L29 _protected prototype_ `virtual bool GetPackageEvent(const FConcertSessionActivity& Activity, FConcertSyncPackageEventMetaData& OutPackageEvent) const override;`
- L30 _protected prototype_ `virtual TFuture<TOptional<FConcertSyncTransactionEvent>> GetTransactionEvent(const FConcertSessionActivity& Activity) const override;`
- L34 _protected prototype_ `virtual TOptional<FConcertSyncSessionDatabaseNonNullPtr> GetSessionDatabase(const FGuid& InSessionId) const = 0;` — Subclasses control which types of transaction are displayed: archived or live
- L36 _protected function_ `const FGuid& GetSessionId() const`
- L41 _private member_ `FGuid SessionId;` — The ID of the managed session
- L43 _private prototype_ `TFuture<TOptional<FConcertSyncTransactionEvent>> FindOrRequestTransactionEvent(const FConcertSyncSessionDatabase& Database, const int64 TransactionEventId) const;`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/SessionTabs/ServerUndoHistoryReflectionDataProvider.h` (Private)


#### class `UE::MultiUserServer::FServerUndoHistoryReflectionDataProvider`  
`class FServerUndoHistoryReflectionDataProvider : public ConcertSharedSlate::IConcertReflectionDataProvider`  
_L10-28_
- inherits: `ConcertSharedSlate::IConcertReflectionDataProvider`
- L15 _public prototype_ `virtual void SetTransactionContext(const FConcertTransactionEventBase& InTransaction) override;`
- L19 _public prototype_ `virtual bool HasClassDisplayName(const FSoftClassPath& ClassPath) const override;`
- L20 _public prototype_ `virtual TOptional<FString> GetClassDisplayName(const FSoftClassPath& ClassPath) const override;`
- L21 _public function_ `virtual bool SupportsGetPropertyReflectionData() const override`
- L22 _public function_ `virtual TOptional<UndoHistory::FPropertyReflectionData> GetPropertyReflectionData(const FSoftClassPath& ClassPath, FName PropertyName) const override`
- L27 _private member_ `FConcertTransactionEventBase TransactionContext;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/StatusBar/SConcertStatusBar.h` (Private)


#### class `SConcertStatusBar`  
`class SConcertStatusBar : public SCompoundWidget`  
_L9-25_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SConcertStatusBar)`
- L16 _public prototype_ `~SConcertStatusBar();`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, FName StatusBarId);`
- L22 _private member_ `TSharedPtr<SWidgetDrawer> WidgetDrawer;`
- L24 _private prototype_ `TSharedRef<SWidgetDrawer> MakeWidgetDrawer(FName StatusBarId);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/Filter/ConcertFilterUtils.h` (Private)


#### struct `UE::ConcertFilterUtils::TRadialMenuBuilder`  
`template<typename TSelectableItem> struct TRadialMenuBuilder`  
_L15-86_
- desc: @param TSelectableItem Must be (efficiently) copyable
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FItemToText, const TSelectableItem& Item);`
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectItem, const TSelectableItem& Item);`
- L26 _public function_ `static void AddRadialSubMenu( FMenuBuilder& MenuBuilder, TAttribute<FText> LabelAttribute, TAttribute<TSelectableItem> SelectedItemAttribute, TAttribute<TArray<TSelectableItem>> ItemsAttribute, FItemToText DisplayNameDelegate, FOnSelectItem OnSelectItemDelegate, const float ForcedWidth = 100.f)` — Adds a menu entry from which the user can choose an item from a list. This function acts as abstraction: UX is evolving and there are two options considered 1. (What we're doing now) create a sub menu. 2. Create a combo button widget. Regardless of what we choose in the future, this function abstracts the above so only this function needs to be adjusted if we change the UX - instead of changing the call sites.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertFilterUtils` (scope `UE`)
- L11 _prototype_ `TSharedRef<SWidget> SetMenuWidgetWidth(const TSharedRef<SWidget>& Widget, bool bNeedsPaddingFromSubmenuRightArrow = true, const float ForcedWidth = 100.f, const float SubMenuIconRightPadding = 15.f);` (scope `UE::ConcertFilterUtils`) — Used for widgets you add using FMenuBuilder::AddSubMenu or FMenuBuilder::AddWidget. This makes sure that the widgets have the same width (for consistent visuals).
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FItemToText, const TSelectableItem& Item);`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectItem, const TSelectableItem& Item);`
- L55 _function_ `.Text_Lambda([SelectedItemAttribute, DisplayNameDelegate](){ return DisplayNameDelegate.Execute(SelectedItemAttribute.Get()); }) ] , false, ForcedWidth) ];` (scope `UE::ConcertFilterUtils::TRadialMenuBuilder::AddRadialSubMenu`)
- L64 _function_ `` (scope `UE::ConcertFilterUtils::TRadialMenuBuilder::AddRadialSubMenu`)
- L72 _function_ `FExecuteAction::CreateLambda([OnSelectItemDelegate, Item](){ OnSelectItemDelegate.Execute(Item); }), FCanExecuteAction::CreateLambda([] { return true; }), FIsActionChecked::CreateLambda([SelectedItemAttribute, Item](){ return Item == SelectedItemAttribute.Get(); })), NAME_None, EUserInterfaceActionType::RadioButton );` (scope `UE::ConcertFilterUtils::TRadialMenuBuilder::AddRadialSubMenu::__anon50406e240202`)
- L75 _function_ `}), FCanExecuteAction::CreateLambda([]` (scope `UE::ConcertFilterUtils::TRadialMenuBuilder::AddRadialSubMenu::__anon50406e240202`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/Filter/ConcertFrontendFilter.h` (Private)


#### class `UE::MultiUserServer::TConcertFrontendFilter`  
`template<typename TFilterType> class TConcertFrontendFilter : public FFilterBase<TFilterType>, public TSharedFromThis<TConcertFrontendFilter<TFilterType>>`  
_L15-42_
- inherits: `FFilterBase<TFilterType>,TSharedFromThis<TConcertFrontendFilter<TFilterType>>`
- desc: A filter that is intended to be displayed in the UI. Every filter has one widget displaying it.
- L22 _public function_ `TConcertFrontendFilter(TSharedPtr<FFilterCategory> InCategory) : FFilterBase<TFilterType>(MoveTemp(InCategory))`
- L27 _public function_ `virtual void ExposeEditWidgets(FMenuBuilder& MenuBuilder)` — Exposes widgets with which the filter can be edited.
- L29 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder)`
- L35 _public function_ `virtual FText GetToolTipText() const`
- L36 _public function_ `virtual FLinearColor GetColor() const`
- L37 _public function_ `virtual FName GetIconName() const`
- L38 _public function_ `virtual bool IsInverseFilter() const`
- L39 _public function_ `virtual void ActiveStateChanged(bool bActive)`
- L40 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const`
- L41 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString)`

#### class `UE::MultiUserServer::TConcertFrontendFilterAggregate`  
`template<typename TConcertFilterImpl, typename TFilterType, typename TWidgetType = SWidget> class TConcertFrontendFilterAggregate : public TConcertFrontendFilter<TFilterType>`  
_L52-75_
- inherits: `TConcertFrontendFilter<TFilterType>`
- desc: Helper class to implement filters Intended pattern: 1. Subclass TConcertFilter<TFilterType> and implement filter logic in TConcertFilterImpl, e.g. text search. This will act as a "model" in MVC. 2. Subclass TConcertFrontendLogFilterAggregate and handle creating UI in it. This will act as a "View" in MVC.
- L54 _private typedef_ `using Super = TConcertFrontendFilter<TFilterType>;`
- L58 _public function_ `virtual bool PassesFilter(TFilterType InItem) const final override`
- L64 _protected function_ `template<typename... TArg> TConcertFrontendFilterAggregate(TSharedPtr<FFilterCategory> InCategory, TArg&&... Arg) : Super(MoveTemp(InCategory)) , Implementation(Forward<TArg>(Arg)...)`
- L74 _protected member_ `TConcertFilterImpl Implementation;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L69 _function_ `` (scope `UE::MultiUserServer::TConcertFrontendFilterAggregate::TConcertFrontendFilterAggregate`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/Filter/ConcertFrontendFilter_TextSearch.h` (Private)


#### class `UE::MultiUserServer::TConcertFilter_TextSearch`  
`template<typename TFilterType> class TConcertFilter_TextSearch : public IFilter<TFilterType>`  
_L17-54_
- inherits: `IFilter<TFilterType>`
- desc: Allows advanced search by text. Implements Adapter pattern to wrap TTextFilter.
- L21 _public function_ `TConcertFilter_TextSearch() : TextFilter(MakeTextFilter())`
- L30 _public function_ `TSharedRef<TTextFilter<TFilterType>> MakeTextFilter() const`
- L36 _public function_ `virtual bool PassesFilter(TFilterType InItem) const override`
- L37 _public function_ `virtual typename IFilter<TFilterType>::FChangedEvent& OnChanged() override`
- L40 _public function_ `void SetRawFilterText(const FText& InFilterText)`
- L41 _public function_ `TSharedRef<TTextFilter<TFilterType>> GetTextFilter() const`
- L46 _protected prototype_ `virtual void GenerateSearchTerms(TFilterType InItem, TArray<FString>& OutTerms) const = 0;` — Parses InItem into a bunch of strings that can be searched
- L51 _private member_ `TSharedRef<TTextFilter<TFilterType>> TextFilter;` — Does the actual string search
- L53 _private member_ `typename IFilter<TFilterType>::FChangedEvent OnChangedEvent;`

#### class `UE::MultiUserServer::TConcertFrontendFilter_TextSearch`  
`template<typename TTextSearchFilterType , typename TFilterType> class TConcertFrontendFilter_TextSearch : public TConcertFrontendFilterAggregate<TTextSearchFilterType, TFilterType, SFilterSearchBox>`  
_L58-87_
- inherits: `TConcertFrontendFilterAggregate<TTextSearchFilterType,TFilterType,SFilterSearchBox>`
- desc: Creates a search bar
- L60 _private typedef_ `using Super = TConcertFrontendFilterAggregate<TTextSearchFilterType, TFilterType, SFilterSearchBox>;`
- L64 _public function_ `template<typename... TArg> TConcertFrontendFilter_TextSearch(TSharedPtr<FFilterCategory> InCategory, TArg&&... Arg) : Super(MoveTemp(InCategory), Forward<TArg>(Arg)...)`
- L76 _public function_ `virtual FString GetName() const override`
- L77 _public function_ `virtual FText GetDisplayName() const override`
- L79 _public function_ `const FText& GetSearchText() const`
- L80 _public function_ `TSharedRef<SFilterSearchBox> GetSearchBox() const`
- L81 _public function_ `TSharedRef<TTextFilter<TFilterType>> MakeTextFilter() const`
- L85 _private member_ `FText SearchText;`
- L86 _private member_ `TSharedPtr<SFilterSearchBox> SearchBox;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L25 _function_ `` (scope `UE::MultiUserServer::TConcertFilter_TextSearch::TConcertFilter_TextSearch`)
- L70 _function_ `` (scope `UE::MultiUserServer::TConcertFrontendFilter_TextSearch::TConcertFrontendFilter_TextSearch`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/Filter/ConcertRootFrontendFilter.h` (Private)


#### struct `UE::MultiUserServer::FFilterWidgetArgs`  
`struct FFilterWidgetArgs`  
_L14-21_
- L16 _public member_ `TSharedPtr<SWidget> _RightOfSearchBar;`
- L17 _public member_ `FMargin _RightOfSearchBarPadding{ 4.f, 0.f, 4.f, 0.f };`
- L19 _public function_ `FFilterWidgetArgs& RightOfSearchBar(TSharedPtr<SWidget> Widget)`
- L20 _public function_ `FFilterWidgetArgs& RightOfSearchBarPadding(FMargin Widget)`

#### class `UE::MultiUserServer::TConcertFrontendRootFilter`  
`template<typename TFilterType, typename TTextSearchFilterType> class TConcertFrontendRootFilter : public IFilter<TFilterType>, public TSharedFromThis<TConcertFrontendRootFilter<TFilterType, TTextSearchFilterType>>`  
_L25-145_
- inherits: `IFilter<TFilterType>,TSharedFromThis<TConcertFrontendRootFilter<TFilterType,TTextSearchFilterType>>`
- desc: A filter that contains multiple UI filters
- L32 _public function_ `TConcertFrontendRootFilter( TSharedRef<TTextSearchFilterType> InTextSearchFilter, TArray<TSharedRef<TConcertFrontendFilter<TFilterType>>> InFrontendFilters, TArray<TSharedRef<IFilter<TFilterType>>> InNonVisualFilters = {}, TSharedRef<FFilterCategory> InDefaultCategory = MakeShared<FFilterCategory>(NSLOCTEXT("UnrealMultiUserServer.TConcertFrontendRootFilter", "DefaultCategoryLabel", "Default"), FText::GetEmpty()) ) : DefaultCategory(MoveTemp(InDefaultCategory)) , TextSearchFilter(MoveTemp(InTextSearchFilter)) , NonVisualFilters(MoveTemp(InNonVisualFilters))`
- L63 _public function_ `TSharedRef<SWidget> BuildFilterWidgets(const FFilterWidgetArgs& InArgs = {})` — Builds the widget view for all contained filters
- L109 _public function_ `virtual bool PassesFilter(TFilterType InItem) const override`
- L120 _public function_ `virtual typename IFilter<TFilterType>::FChangedEvent& OnChanged() override`
- L123 _public function_ `FORCEINLINE const TSharedRef<TTextSearchFilterType>& GetTextSearchFilter() const`
- L124 _public function_ `FORCEINLINE TSharedRef<FFilterCategory> GetDefaultCategory() const`
- L129 _private member_ `TSharedRef<FFilterCategory> DefaultCategory;` — The default category that filters are added to
- L131 _private member_ `TSharedPtr<SConcertFilterBar<TFilterType>> FilterBar;` — Displays the currently active filters
- L134 _private member_ `TSharedRef<TTextSearchFilterType> TextSearchFilter;` — The text search filter. Also in AllFilters. Separate variable to build search bar in new line.
- L137 _private member_ `TArray<TSharedRef<IFilter<TFilterType>>> NonVisualFilters;` — Filters that are combined using logical AND.
- L139 _private function_ `void BroadcastOnChanged()`
- L144 _private member_ `typename IFilter<TFilterType>::FChangedEvent OnChangedEvent;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L45 _function_ `` (scope `UE::MultiUserServer::TConcertFrontendRootFilter::TConcertFrontendRootFilter`)
- L115 _function_ `NonVisualFilters, [&InItem](const TSharedRef<IFilter<TFilterType>>& AndFilter)` (scope `UE::MultiUserServer::TConcertFrontendRootFilter::PassesFilter`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/Filter/SConcertFilterBar.h` (Private)


#### class `UConcertFilterBarContext`  
`class UConcertFilterBarContext : public UObject`  
_L14-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPopulateMenu, UToolMenu*);`
- L20 _public member_ `FOnPopulateMenu PopulateMenu;`

#### class `UE::MultiUserServer::SConcertFilterBar`  
`template<typename TFilterType> class SConcertFilterBar : public SBasicFilterBar<TFilterType>`  
_L26-144_
- inherits: `SBasicFilterBar<TFilterType>`
- L28 _private typedef_ `using Super = SBasicFilterBar<TFilterType>;`
- L31 _public typedef_ `using FOnFilterChanged = typename SBasicFilterBar<TFilterType>::FOnFilterChanged;`
- L32 _public typedef_ `using FCreateTextFilter = typename SBasicFilterBar<TFilterType>::FCreateTextFilter;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SConcertFilterBar)`
- L38 _public function_ `SLATE_EVENT(SConcertFilterBar<TFilterType>::FOnFilterChanged, OnFilterChanged) SLATE_ARGUMENT(TArray<TSharedRef<TConcertFrontendFilter<TFilterType>>>, CustomFilters) SLATE_ARGUMENT(FCreateTextFilter, CreateTextFilter) SLATE_ARGUMENT(TSharedPtr<SFilterSearchBox>, FilterSearchBox) SLATE_END_ARGS() void Construct(const FArguments& InArgs)` — Delegate for when filters have changed
- L73 _private function_ `virtual TSharedRef<SWidget> MakeAddFilterMenu() override`
- L98 _private function_ `void HandlePopulateAddFilterMenu(UToolMenu* InMenu)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopulateMenu, UToolMenu*);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L60 _function_ `Algo::Transform(InArgs._CustomFilters, TransformedCustomFilters, [](const TSharedRef<TConcertFrontendFilter<TFilterType>>& Item){ return Item; });` (scope `UE::MultiUserServer::SConcertFilterBar::SLATE_EVENT`)
- L83 _function_ `` (scope `UE::MultiUserServer::SConcertFilterBar::MakeAddFilterMenu`)
- L112 _function_ `` (scope `UE::MultiUserServer::SConcertFilterBar::HandlePopulateAddFilterMenu`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/SDoNotShowAgainDialog.h` (Private)


#### class `UE::MultiUserServer::SDoNotShowAgainDialog`  
`class SDoNotShowAgainDialog : public SCustomDialog`  
_L13-32_
- inherits: `SCustomDialog`
- desc: Text message with a "Do not show again" checkbox.
- L17 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnClosed, bool );`
- L19 _public function_ `SLATE_BEGIN_ARGS(SDoNotShowAgainDialog)`
- L21 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(TArray<FButton>, Buttons) SLATE_NAMED_SLOT(FArguments, Content) SLATE_EVENT(FOnClosed, DoNotShowAgainCallback) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private member_ `TSharedPtr<SCheckBox> DoNotShowAgainCheckbox;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClosed, bool );`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Widgets/Util/SMultiUserIcons.h` (Private)


#### class `SMultiUserIcons`  
`class SMultiUserIcons : public SCompoundWidget`  
_L10-24_
- inherits: `SCompoundWidget`
- desc: Shows all multi user server icons
- L14 _public function_ `SLATE_BEGIN_ARGS(SMultiUserIcons)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _private prototype_ `void AddHeader(const TSharedRef<SVerticalBox>& VerticalBox, FText Text);`
- L23 _private prototype_ `void AddCategory(const TSharedRef<SVerticalBox>& VerticalBox, FText Text, const TArray<FName>& IconNames);`

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Window/ConcertServerTabs.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ConcertServerTabs`
- L10 _prototype_ `FName GetSessionBrowserTabId();` (scope `ConcertServerTabs`)
- L11 _prototype_ `FName GetClientsTabID();` (scope `ConcertServerTabs`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Window/ConcertServerWindowController.h` (Private)


#### struct `UE::MultiUserServer::FConcertServerWindowInitParams`  
`struct FConcertServerWindowInitParams`  
_L21-36_
- L24 _public member_ `TSharedRef<IConcertSyncServer> Server;` — The server that the window is supposed to manage
- L27 _public member_ `FString MultiUserServerLayoutIni;` — Config path for server layout ini
- L30 _public member_ `TArray<TSharedRef<IConcertComponent>> AdditionalConcertComponents;` — Additional modular concert features to enable
- L32 _public function_ `FConcertServerWindowInitParams(TSharedRef<IConcertSyncServer> Server, FString MultiUserServerLayoutIni = FString()) : Server(Server) , MultiUserServerLayoutIni(MoveTemp(MultiUserServerLayoutIni))`

#### class `UE::MultiUserServer::FConcertServerWindowController`  
`class FConcertServerWindowController : public TSharedFromThis<FConcertServerWindowController>`  
_L39-92_
- inherits: `TSharedFromThis<FConcertServerWindowController>`
- desc: Responsible for creating the Slate window for the server. Implements controller in the model-view-controller pattern.
- L43 _public prototype_ `FConcertServerWindowController(const FConcertServerWindowInitParams& Params);`
- L44 _public prototype_ `~FConcertServerWindowController();`
- L46 _public prototype_ `TSharedRef<SWindow> CreateWindow();`
- L47 _public function_ `TSharedPtr<SWindow> GetRootWindow() const`
- L50 _public prototype_ `void OpenSessionTab(const FGuid& SessionId);` — Opens or draws attention to the tab for the given live or archived session ID
- L53 _public prototype_ `void DestroySessionTab(const FGuid& SessionId);` — Destroys the tab associated with this live or archived session ID.
- L58 _private member_ `FString MultiUserServerLayoutIni;` — The ini file to use for saving the layout
- L60 _private member_ `TSharedPtr<FTabManager::FLayout> PersistentLayout;` — Holds the current layout for saving later.
- L62 _private member_ `TSharedRef<IConcertSyncServer> ServerInstance;`
- L65 _private member_ `TSharedPtr<SWindow> RootWindow;` — The main window being managed
- L66 _private member_ `TMap<FGuid, TSharedRef<FConcertSessionTabBase>> RegisteredSessions;`
- L69 _private member_ `TSharedRef<FConcertServerSessionBrowserController> SessionBrowserController;` — Manages the session browser
- L71 _private member_ `TSharedRef<FConcertClientsTabController> ClientsController;` — Manages the view of connected clients
- L73 _private member_ `TArray<TSharedRef<IConcertComponent>> ConcertComponents;` — Additional external concert components
- L75 _private prototype_ `void InitComponents(const TSharedRef<FTabManager::FStack>& MainArea);`
- L78 _private prototype_ `TSharedPtr<FConcertSessionTabBase> GetOrRegisterSessionTab(const FGuid& SessionId);` — Gets the manager for a session tab if the session ID is valid
- L80 _private prototype_ `void RegisterForSessionDestructionEvents();`
- L81 _private prototype_ `void UnregisterFromSessionDestructionEvents() const;`
- L82 _private prototype_ `void OnLiveSessionDestroyed(const IConcertServer&, TSharedRef<IConcertServerSession> InLiveSession);`
- L83 _private prototype_ `void OnArchivedSessionDestroyed(const IConcertServer&, const FGuid& InArchivedSessionId);`
- L85 _private prototype_ `void ShowConnectedClients(const TSharedRef<IConcertServerSession>& ServerSession);`
- L87 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& Window);`
- L88 _private prototype_ `void SaveLayout() const;`
- L91 _private prototype_ `void SaveTabManagerLayout();` — Saves the layout of the global tab manager (on shutdown).

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Window/IConcertComponent.h` (Private)


#### struct `UE::MultiUserServer::FConcertComponentInitParams`  
`struct FConcertComponentInitParams`  
_L13-29_
- L16 _public member_ `TSharedRef<IConcertSyncServer> Server;` — The server being managed
- L19 _public member_ `TSharedRef<FConcertServerWindowController> WindowController;` — Manages the server slate application
- L22 _public member_ `TSharedRef<FTabManager::FStack> MainStack;` — The root area of the main window layout. Add tabs to this.
- L24 _public function_ `FConcertComponentInitParams(TSharedRef<IConcertSyncServer> Server, TSharedRef<FConcertServerWindowController> WindowController, TSharedRef<FTabManager::FStack> MainStack) : Server(MoveTemp(Server)) , WindowController(MoveTemp(WindowController)) , MainStack(MoveTemp(MainStack))`

#### class `UE::MultiUserServer::IConcertComponent`  
`class IConcertComponent`  
_L32-40_
- desc: Provides the base interface for elements in the concert server UI.
- L36 _public prototype_ `virtual ~IConcertComponent() = default;`
- L39 _public function_ `virtual void Init(const FConcertComponentInitParams& Params)` — Initialises the component, e.g. registering tab spawners, etc.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Window/ModalWindowManager.h` (Private)


#### class `UE::MultiUserServer::FModalWindowManager`  
`class FModalWindowManager`  
_L18-39_
- desc: Manages "fake" modal windows because the server cannot use "true" modal windows. True modal windows block the main thread which is not an option because the server must continue responding to networked requests.
- L22 _public prototype_ `FModalWindowManager(const TSharedRef<SWindow>& MainWindow);`
- L24 _public prototype_ `void ShowFakeModalWindow(const TSharedRef<SCustomDialog>& Dialog);`
- L27 _public prototype_ `void PushWindow(const TSharedRef<SWindow>& Window);` — Called when a new fake modal window should be tracked on top of all windows.
- L29 _public prototype_ `void PopWindow();` — Called when a fake modal window should no longer be tracked, i.e. when it is closed.
- L33 _private member_ `TArray<TWeakPtr<SWindow>> WindowStack;`
- L36 _private member_ `bool bRootWindowIsValid = true;` — Modal windows can only be added when this is true
- L38 _private prototype_ `void OnMainWindowActivated();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MultiUserServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Public/IMultiUserServerModule.h` (Public)


#### class `IMultiUserServerModule`  
`class IMultiUserServerModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- L22 _public function_ `static inline IMultiUserServerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L40 _public prototype_ `virtual void InitSlateForServer(FConcertSyncServerLoopInitArgs& InitArgs) = 0;` — Set-up callbacks for creating Slate UI when the MU server is started. Called before the server loop is initialized.
