# Developer / CollisionAnalyzer

- module root: `Source/Developer/CollisionAnalyzer`
- headers: 8; symbols: 199
- symbol kinds: class=10, delegate=2, enum=5, enumerator=16, function=16, member=69, namespace=5, prototype=74, struct=2
- DynamicallyLoadedModuleNames: DesktopPlatform, MainFrame
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: DesktopPlatform

### `Source/Developer/CollisionAnalyzer/Private/CollisionAnalyzer.h` (Private)


#### struct `FCAQuery`  
`struct FCAQuery`  
_L16-39_
- desc: Stores information about one collision query
- L18 _public prototype_ `FCAQuery();`
- L19 _public prototype_ `~FCAQuery();`
- L21 _public member_ `FVector Start;`
- L22 _public member_ `FVector End;`
- L23 _public member_ `FQuat Rot;`
- L24 _public member_ `ECAQueryType::Type Type;`
- L25 _public member_ `ECAQueryShape::Type Shape;`
- L26 _public member_ `ECAQueryMode::Type Mode;`
- L27 _public member_ `FVector Dims;`
- L28 _public member_ `ECollisionChannel Channel;`
- L29 _public member_ `FCollisionQueryParams Params;`
- L30 _public member_ `FCollisionResponseParams ResponseParams;`
- L31 _public member_ `FCollisionObjectQueryParams ObjectParams;`
- L32 _public member_ `TArray<FHitResult> Results;`
- L33 _public member_ `TArray<FHitResult> TouchAllResults;`
- L34 _public member_ `int32 FrameNum;`
- L35 _public member_ `float CPUTime;`
- L36 _public member_ `int32 ID;` — float						CPUTime;   In ms

#### class `FCollisionAnalyzer`  
`class FCollisionAnalyzer : public ICollisionAnalyzer`  
_L42-109_
- inherits: `ICollisionAnalyzer`
- desc: Actual implementation of CollisionAnalyzer, private inside module
- L46 _public prototype_ `virtual void CaptureQuery( const FVector& Start, const FVector& End, const FQuat& Rot, ECAQueryType::Type QueryType, ECAQueryShape::Type QueryShape, ECAQueryMode::Type QueryMode, const FVector& Dims, ECollisionChannel TraceChannel, const struct FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParams, const FCollisionObjectQueryParams& ObjectParams, const TArray<FHitResult>& Results, const TArray<FHitResult>& TouchAllResults, double CPUTime) override;`
- L63 _public prototype_ `virtual TSharedPtr<SWidget> SummonUI() override;` — Returns a new Collision Analyzer widget.
- L65 _public prototype_ `virtual void TickAnalyzer(UWorld* InWorld) override;`
- L66 _public prototype_ `virtual bool IsRecording() override;`
- L70 _public prototype_ `void SetIsRecording(bool bNewRecording);` — Change the current recording state
- L72 _public prototype_ `int32 GetNumFramesOfRecording();` — Get the current number of frames we have recorded
- L74 _public function_ `FCollisionAnalyzer() : DrawBox(ForceInit) , CurrentFrameNum(0) , bIsRecording(false)`
- L81 _public prototype_ `virtual ~FCollisionAnalyzer() = default;`
- L84 _public member_ `TArray<FCAQuery> Queries;` — All collected query data
- L86 _public member_ `TArray<int32> DrawQueryIndices;` — Indices of queries in Queries array that we want to draw in 3D
- L88 _public member_ `FBox DrawBox;` — AABB to draw in the world
- L90 _public prototype_ `DECLARE_EVENT( FCollisionAnalyzer, FQueriesChangedEvent );`
- L91 _public function_ `FQueriesChangedEvent& OnQueriesChanged()`
- L92 _public function_ `FQueriesChangedEvent& OnQueryAdded()`
- L95 _public prototype_ `void SaveCollisionProfileData(FString ProfileFileName);` — Save current data to a file
- L97 _public prototype_ `void LoadCollisionProfileData(FString ProfileFileName);` — Load data from file
- L101 _private member_ `int32 CurrentFrameNum;` — The current frame number we are on while recording
- L103 _private member_ `bool bIsRecording;` — Whether we are currently recording
- L105 _private member_ `FQueriesChangedEvent QueriesChangedEvent;` — Event called when Queries array changes
- L107 _private member_ `FQueriesChangedEvent QueryAddedEvent;` — Event called when a single query is added to array

#### struct `FCollisionAnalyzerProxyArchive`  
`struct FCollisionAnalyzerProxyArchive : public FNameAsStringProxyArchive`  
_L117-134_
- inherits: `FNameAsStringProxyArchive`
- desc: Local archive that implements FWeakObjectPtr serialisation. In an ideal world we'd combine FNameAsStringProxyArchive and FArchiveUObject in a generic way, but the duplicate inheritance issues aren't worth it here.
- L124 _public function_ `FCollisionAnalyzerProxyArchive(FArchive& InInnerArchive) : FNameAsStringProxyArchive(InInnerArchive)` — Creates and initializes a new instance. @param InInnerArchive The inner archive to proxy.
- L130 _public function_ `virtual FArchive& operator<< (struct FWeakObjectPtr& Value) override`

#### Free symbols / members of external scopes

- L90 _delegate_ `DECLARE_EVENT( FCollisionAnalyzer, FQueriesChangedEvent );`

### `Source/Developer/CollisionAnalyzer/Private/CollisionAnalyzerLog.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCollisionAnalyzer, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCollisionAnalyzer, Log, All);`

### `Source/Developer/CollisionAnalyzer/Private/CollisionAnalyzerStyle.h` (Private)


#### class `FCollisionAnalyzerStyle`  
`class FCollisionAnalyzerStyle`  
_L13-32_
- desc: Declares the Collision Analyzer window's visual style.
- L25 _public prototype_ `static void Initialize();`
- L27 _public prototype_ `static void Shutdown();`
- L29 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L31 _public member_ `static TSharedPtr< FCollisionAnalyzerStyle::FStyle > StyleInstance;`

#### class `FCollisionAnalyzerStyle::FStyle`  
`class FStyle : public FSlateStyleSet`  
_L17-23_
- inherits: `FSlateStyleSet`
- L20 _public prototype_ `FStyle();`
- L22 _public prototype_ `void Initialize();`

### `Source/Developer/CollisionAnalyzer/Private/SCAQueryDetails.h` (Private)


#### class `FCAHitInfo`  
`class FCAHitInfo`  
_L16-34_
- desc: Info about a hit
- L19 _public member_ `FHitResult Result;`
- L20 _public member_ `bool bMiss;`
- L23 _public function_ `static TSharedRef<FCAHitInfo> Make(FHitResult& Result, bool bMiss)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L30 _private function_ `FCAHitInfo(FHitResult& InResult, bool bInMiss) : Result(InResult) , bMiss(bInMiss)`

#### class `SCAQueryDetails`  
`class SCAQueryDetails : public SCompoundWidget`  
_L37-89_
- inherits: `SCompoundWidget`
- desc: Widget to display details about a single query
- L41 _public function_ `SLATE_BEGIN_ARGS(SCAQueryDetails)`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<SCollisionAnalyzer> OwningAnalyzerWidget);`
- L50 _public prototype_ `void SetCurrentQuery(const FCAQuery& NewQuery);` — Set the current query to display
- L52 _public prototype_ `void ClearCurrentQuery();` — Show no query
- L54 _public prototype_ `FCAQuery* GetCurrentQuery();` — Get current query
- L57 _public prototype_ `FText GetStartText() const;` — Get delegates
- L58 _public prototype_ `FText GetEndText() const;`
- L59 _public prototype_ `ECheckBoxState GetShowMissesState() const;`
- L61 _public prototype_ `TSharedRef<ITableRow> ResultListGenerateRow(TSharedPtr<FCAHitInfo> Info, const TSharedRef<STableViewBase>& OwnerTable);` — List delegates
- L62 _public prototype_ `void ResultListSelectionChanged(TSharedPtr<FCAHitInfo> SelectedInfos, ESelectInfo::Type SelectInfo);`
- L64 _public prototype_ `void OnToggleShowMisses(ECheckBoxState InCheckboxState);` — Handler delegates
- L69 _private prototype_ `void UpdateResultList();` — Update ResultList from CurrentQuery
- L71 _private prototype_ `void UpdateDisplayedBox();` — Update the box we are drawing
- L75 _private member_ `TWeakPtr<SCollisionAnalyzer> OwningAnalyzerWidgetPtr;` — Owning SCollisionAnalyzer
- L78 _private member_ `bool bDisplayQuery;` — Are we currently displaying a query
- L80 _private member_ `FCAQuery CurrentQuery;` — Current query we are displaying
- L82 _private member_ `TArray< TSharedPtr<FCAHitInfo> > ResultList;` — Array used by list widget, just a copy of that in CurrentQuery
- L84 _private member_ `bool bShowMisses;`
- L88 _private member_ `TSharedPtr< SListView< TSharedPtr<FCAHitInfo> > > ResultListWidget;`

### `Source/Developer/CollisionAnalyzer/Private/SCAQueryTableRow.h` (Private)


#### class `SCAQueryTableRow`  
`class SCAQueryTableRow : public SMultiColumnTableRow< TSharedPtr<class FQueryTreeItem> >`  
_L13-38_
- inherits: `SMultiColumnTableRow<TSharedPtr<classFQueryTreeItem>>`
- desc: Implements a row widget for query list.
- L17 _public function_ `SLATE_BEGIN_ARGS(SCAQueryTableRow)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L30 _public prototype_ `FText GetTotalTimeText() const;` — delegate
- L35 _private member_ `TSharedPtr<class FQueryTreeItem> Item;` — Tree item
- L37 _private member_ `TWeakPtr<SCollisionAnalyzer> OwnerAnalyzerWidgetPtr;` — Analyzer widget that owns us

### `Source/Developer/CollisionAnalyzer/Private/SCollisionAnalyzer.h` (Private)


#### class `FQueryTreeItem`  
`class FQueryTreeItem`  
_L17-72_
- L21 _public member_ `bool bIsGroup;` — Bool to indicate whether this is a group or a leaf individual query entry
- L24 _public member_ `FName GroupName;` — If a group
- L25 _public member_ `int32 FrameNum;`
- L26 _public member_ `float TotalCPUTime;`
- L27 _public member_ `TArray<TSharedPtr<FQueryTreeItem> > QueriesInGroup;`
- L30 _public member_ `int32 QueryIndex;` — If a leaf (single query entry)
- L32 _public function_ `static TSharedRef<FQueryTreeItem> MakeGroup(FName InGroupName, int32 InFrameNum)`
- L38 _public function_ `static TSharedRef<FQueryTreeItem> MakeQuery(int32 InQueryIndex)`
- L45 _public function_ `void UpdateTotalCPUTime(FCollisionAnalyzer* Analyzer)` — Recalculate the totaly CPU time for this group
- L65 _private function_ `FQueryTreeItem(bool bInIsGroup, FName InGroupName, int32 InFrameNum, float InTotalCPUTime, int32 InQueryIndex) : bIsGroup(bInIsGroup) , GroupName(InGroupName) , FrameNum(InFrameNum) , TotalCPUTime(InTotalCPUTime) , QueryIndex(InQueryIndex)`

#### enum `EQueryGroupMode::Type`  
`enum Type`  
_L76-82_
- L78 _public enumerator_ `Ungrouped`
- L79 _public enumerator_ `ByFrameNum`
- L80 _public enumerator_ `ByTag`
- L81 _public enumerator_ `ByOwnerTag`

#### enum `EQuerySortMode::Type`  
`enum Type`  
_L87-91_
- L89 _public enumerator_ `ByID`
- L90 _public enumerator_ `ByTime`

#### class `SCollisionAnalyzer`  
`class SCollisionAnalyzer : public SCompoundWidget`  
_L95-214_
- inherits: `SCompoundWidget`
- desc: Main CollisionAnalyzer UI widget
- L99 _public function_ `SLATE_BEGIN_ARGS(SCollisionAnalyzer)`
- L101 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCollisionAnalyzer* InAnalyzer);`
- L105 _public prototype_ `virtual ~SCollisionAnalyzer();`
- L108 _public prototype_ `const FSlateBrush* GetRecordButtonBrush() const;` — Get delegates
- L109 _public prototype_ `FText GetStatusText() const;`
- L110 _public prototype_ `ECheckBoxState GetDrawRecentState() const;`
- L111 _public prototype_ `ECheckBoxState GetGroupByFrameState() const;`
- L112 _public prototype_ `ECheckBoxState GetGroupByTagState() const;`
- L113 _public prototype_ `ECheckBoxState GetGroupByOwnerState() const;`
- L114 _public prototype_ `EColumnSortMode::Type GetIDSortMode() const;`
- L115 _public prototype_ `EColumnSortMode::Type GetTimeSortMode() const;`
- L117 _public prototype_ `FReply OnRecordButtonClicked();` — Handler delegates
- L118 _public prototype_ `FReply OnLoadButtonClicked();`
- L119 _public prototype_ `FReply OnSaveButtonClicked();`
- L120 _public prototype_ `void OnDrawRecentChanged(ECheckBoxState NewState);`
- L121 _public prototype_ `void OnGroupByFrameChanged(ECheckBoxState NewState);`
- L122 _public prototype_ `void OnGroupByTagChanged(ECheckBoxState NewState);`
- L123 _public prototype_ `void OnGroupByOwnerChanged(ECheckBoxState NewState);`
- L124 _public prototype_ `void FilterTextCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);`
- L125 _public prototype_ `void OnSortByChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode);`
- L127 _public prototype_ `TSharedRef<ITableRow> QueryTreeGenerateRow(TSharedPtr<FQueryTreeItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Table delegates
- L128 _public prototype_ `void OnGetChildrenForQueryGroup( TSharedPtr<FQueryTreeItem> InItem, TArray<TSharedPtr<FQueryTreeItem> >& OutChildren );`
- L129 _public prototype_ `void QueryTreeSelectionChanged(TSharedPtr<FQueryTreeItem> SelectedItem, ESelectInfo::Type SelectInfo);`
- L132 _public prototype_ `static FString QueryShapeToString(ECAQueryShape::Type QueryShape);` — Util to convert a query shape to a string
- L135 _public prototype_ `static FString QueryTypeToString(ECAQueryType::Type QueryType);` — Util to convert a query type to a string
- L138 _public prototype_ `static FString QueryModeToString(ECAQueryMode::Type QueryMode);` — Util to convert a query mode to a string
- L141 _public member_ `FCollisionAnalyzer* Analyzer;` — Pointer to the analyzer object we want to show ui for
- L144 _public member_ `EQueryGroupMode::Type GroupBy;` — Current way that we are grouping queries
- L146 _public member_ `EQuerySortMode::Type SortBy;` — Current way we are sorting queries
- L148 _public member_ `EColumnSortMode::Type SortDirection;` — Current way we are setting ID sort direction
- L151 _private prototype_ `void OnQueriesChanged();` — Called when the queries array in the CollisionAnalyzer change
- L153 _private prototype_ `void OnQueryAdded();` — Called when a single query is added
- L155 _private prototype_ `void RebuildFilteredList();` — Regenerate the VisibleQueries list based on current filter
- L157 _private prototype_ `void AddQueryToGroupedQueries(int32 NewQueryIndex, bool bPerformSort);` — Add a Query to
- L159 _private prototype_ `TSharedPtr<FQueryTreeItem> FindQueryGroup(FName InGroupName, int32 InFrameNum);` — Find a group by name or framenum
- L161 _private prototype_ `void UpdateDrawnQueries();` — Update list of queries to draw in 3D
- L163 _private prototype_ `void UpdateFilterInfo();` — Update filtering members from entry widgets
- L166 _private prototype_ `bool ShouldDisplayQuery(const FCAQuery& Query);` — See if a particular query passes the current filter
- L172 _private member_ `TArray<TSharedPtr<FQueryTreeItem> > GroupedQueries;` — Index into Analyzer->Queries array for entries you want to show.
- L174 _private member_ `int32 TotalNumQueries;` — Total number of queries in analyzer database
- L176 _private member_ `TArray<int32> RecentQueries;` — Set of of most recent queries
- L179 _private member_ `bool bDrawRecentQueries;` — If we should draw new queries that pass the filter right away
- L181 _private member_ `int32 FrameFilterNum;`
- L182 _private member_ `FString TagFilterString;`
- L183 _private member_ `FString OwnerFilterString;`
- L184 _private member_ `float MinCPUFilterTime;`
- L189 _private member_ `TSharedPtr<STreeView<TSharedPtr<FQueryTreeItem> > > QueryTreeWidget;` — Main query list widget
- L191 _private member_ `TSharedPtr<SCAQueryDetails> QueryDetailsWidget;` — Widget for display details on a specific query
- L193 _private member_ `TSharedPtr<SEditableTextBox> FrameFilterBox;` — Box to filter to a specific frame
- L195 _private member_ `TSharedPtr<SEditableTextBox> TagFilterBox;` — Box to filter to a specific tag
- L197 _private member_ `TSharedPtr<SEditableTextBox> OwnerFilterBox;` — Box to filter to a specific owner
- L199 _private member_ `TSharedPtr<SEditableTextBox> TimeFilterBox;` — Box to filter by time
- L203 _public member_ `static const FName IDColumnName;`
- L204 _public member_ `static const FName FrameColumnName;`
- L205 _public member_ `static const FName TypeColumnName;`
- L206 _public member_ `static const FName ShapeColumnName;`
- L207 _public member_ `static const FName ModeColumnName;`
- L208 _public member_ `static const FName TagColumnName;`
- L209 _public member_ `static const FName OwnerColumnName;`
- L210 _public member_ `static const FName NumBlockColumnName;`
- L211 _public member_ `static const FName NumTouchColumnName;`
- L212 _public member_ `static const FName TimeColumnName;`

#### Free symbols / members of external scopes

- L74 _namespace_ `namespace EQueryGroupMode`
- L85 _namespace_ `namespace EQuerySortMode`

### `Source/Developer/CollisionAnalyzer/Public/CollisionAnalyzerModule.h` (Public)


#### class `FCollisionAnalyzerModule`  
`class FCollisionAnalyzerModule : public IModuleInterface`  
_L12-38_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public function_ `static ICollisionAnalyzer* Get()` — Gets the debugger singleton or returns NULL
- L29 _private function_ `virtual ICollisionAnalyzer* GetSingleton() const`
- L35 _private prototype_ `TSharedRef<class SDockTab> SpawnCollisionAnalyzerTab(const FSpawnTabArgs& Args);` — Spawns the Collision Analyzer tab in an SDockTab
- L37 _private member_ `ICollisionAnalyzer* CollisionAnalyzer;`

### `Source/Developer/CollisionAnalyzer/Public/ICollisionAnalyzer.h` (Public)


#### enum `ECAQueryType::Type`  
`enum Type`  
_L16-21_
- L18 _public enumerator_ `Raycast`
- L19 _public enumerator_ `GeomSweep`
- L20 _public enumerator_ `GeomOverlap`

#### enum `ECAQueryShape::Type`  
`enum Type`  
_L27-33_
- L29 _public enumerator_ `Sphere`
- L30 _public enumerator_ `Box`
- L31 _public enumerator_ `Capsule`
- L32 _public enumerator_ `Convex`

#### enum `ECAQueryMode::Type`  
`enum Type`  
_L39-44_
- L41 _public enumerator_ `Test`
- L42 _public enumerator_ `Single`
- L43 _public enumerator_ `Multi`

#### class `ICollisionAnalyzer`  
`class ICollisionAnalyzer`  
_L47-78_
- L51 _public prototype_ `virtual ~ICollisionAnalyzer() = default;` — Virtual destructor
- L54 _public prototype_ `virtual void CaptureQuery( const FVector& Start, const FVector& End, const FQuat& Rot, ECAQueryType::Type QueryType, ECAQueryShape::Type QueryShape, ECAQueryMode::Type QueryMode, const FVector& Dims, ECollisionChannel TraceChannel, const struct FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParams, const FCollisionObjectQueryParams& ObjectParams, const TArray<FHitResult>& Results, const TArray<FHitResult>& TouchAllResults, double CPUTime) = 0;`
- L71 _public prototype_ `virtual TSharedPtr<SWidget> SummonUI() = 0;` — Returns a new Collision Analyzer widget.
- L74 _public prototype_ `virtual void TickAnalyzer(UWorld* InWorld) = 0;`
- L77 _public prototype_ `virtual bool IsRecording() = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ECAQueryType`
- L25 _namespace_ `namespace ECAQueryShape`
- L37 _namespace_ `namespace ECAQueryMode`
