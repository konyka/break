# Plugins / SourceFilteringEditor

- module root: `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor`
- headers: 20; symbols: 302
- symbol kinds: class=21, delegate=2, function=30, member=75, namespace=2, prototype=170, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, GameplayInsights, InputCore, PropertyPath, Slate, SlateCore, SourceFilteringCore, SourceFilteringTrace, TraceAnalysis, TraceInsights, TraceServices, UnrealEd, WorkspaceMenuStructure

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/ClassFilterObject.h` (Private)


#### class `FClassFilterObject`  
`class FClassFilterObject : public TSharedFromThis<FClassFilterObject>`  
_L7-28_
- inherits: `TSharedFromThis<FClassFilterObject>`
- L10 _public function_ `FClassFilterObject(UClass* InClass, bool bDerivedClasses) : Class(InClass), bIncludeDerived(bDerivedClasses)`
- L12 _public function_ `const FText GetDisplayText() const`
- L22 _public function_ `UClass* GetClass() const`
- L24 _public function_ `bool IncludesDerivedClasses() const`
- L26 _protected member_ `UClass* Class;`
- L27 _protected member_ `bool bIncludeDerived;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/EditorSessionSourceFilterService.h` (Private)


#### class `FEditorSessionSourceFilterService`  
`class FEditorSessionSourceFilterService : public ISessionSourceFilterService, public FGCObject, public FSelfRegisteringEditorUndoClient`  
_L20-108_
- inherits: `ISessionSourceFilterService,FGCObject,FSelfRegisteringEditorUndoClient`
- desc: Editor implementation of ISessionSourceFilterService, interfaces directly with Engine level filtering systems and settings
- L23 _public prototype_ `FEditorSessionSourceFilterService();`
- L24 _public prototype_ `virtual ~FEditorSessionSourceFilterService();`
- L27 _public prototype_ `virtual void PopulateTreeView(FTreeViewDataBuilder& InBuilder) override;` — Begin ISessionSourceFilterService overrides
- L28 _public prototype_ `virtual void AddFilter(const FString& FilterClassName) override;`
- L29 _public prototype_ `virtual void AddFilterToSet(TSharedRef<const IFilterObject> FilterSet, const FString& FilterClassName) override;`
- L30 _public prototype_ `virtual void AddFilterToSet(TSharedRef<const IFilterObject> FilterSet, TSharedRef<const IFilterObject> ExistingFilter) override;`
- L31 _public prototype_ `virtual void MakeFilterSet(TSharedRef<const IFilterObject> ExistingFilter, EFilterSetMode Mode) override;`
- L32 _public prototype_ `virtual void MakeFilterSet(TSharedRef<const IFilterObject> ExistingFilter, TSharedRef<const IFilterObject> ExistingFilterOther) override;`
- L33 _public prototype_ `virtual void MakeTopLevelFilter(TSharedRef<const IFilterObject> Filter) override;`
- L34 _public prototype_ `virtual void RemoveFilter(TSharedRef<const IFilterObject> InFilter) override;`
- L35 _public prototype_ `virtual void SetFilterSetMode(TSharedRef<const IFilterObject> InFilter, EFilterSetMode Mode) override;`
- L36 _public prototype_ `virtual void SetFilterState(TSharedRef<const IFilterObject> InFilter, bool bState) override;`
- L37 _public prototype_ `virtual void ResetFilters() override;`
- L38 _public function_ `virtual FOnSessionStateChanged& GetOnSessionStateChanged() override`
- L39 _public prototype_ `virtual void UpdateFilterSettings(UTraceSourceFilteringSettings* InSettings) override;`
- L40 _public prototype_ `virtual UTraceSourceFilteringSettings* GetFilterSettings() override;`
- L41 _public prototype_ `virtual bool IsActionPending() const override;`
- L42 _public prototype_ `virtual TSharedRef<SWidget> GetFilterPickerWidget(FOnFilterClassPicked InFilterClassPicked) override;`
- L43 _public prototype_ `virtual TSharedRef<SWidget> GetClassFilterPickerWidget(FOnFilterClassPicked InFilterClassPicked) override;`
- L44 _public prototype_ `virtual TSharedPtr<FExtender> GetExtender() override;`
- L45 _public prototype_ `virtual void GetWorldObjects(TArray<TSharedPtr<FWorldObject>>& OutWorldObjects) override;`
- L46 _public prototype_ `virtual void SetWorldTraceability(TSharedRef<FWorldObject> InWorldObject, bool bState) override;`
- L47 _public prototype_ `virtual const TArray<TSharedPtr<IWorldTraceFilter>>& GetWorldFilters() override;`
- L48 _public prototype_ `virtual void AddClassFilter(const FString& ActorClassName) override;`
- L49 _public prototype_ `virtual void RemoveClassFilter(TSharedRef<FClassFilterObject> ClassFilterObject) override;`
- L50 _public prototype_ `virtual void GetClassFilters(TArray<TSharedPtr<FClassFilterObject>>& OutClasses) const override;`
- L51 _public prototype_ `virtual void SetIncludeDerivedClasses(TSharedRef<FClassFilterObject> ClassFilterObject, bool bIncluded) override;`
- L55 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — Begin FEditorUndoClient overrides
- L56 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L57 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const;`
- L61 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Begin FGCObject overrides
- L62 _public function_ `virtual FString GetReferencerName() const override`
- L70 _protected prototype_ `void StateChanged();` — Fires the OnSessionStateChanged delegate, indicating that the contained data has changed
- L73 _protected prototype_ `void OnSaveAsPreset();` — Callback for whenever the user opts to save the current filtering state as a preset
- L76 _protected prototype_ `void OnBlueprintCompiled(UBlueprint* InBlueprint);` — Callback for whenever any Filter instance blueprint class gets (re)compiled
- L79 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementsMap);` — Callback for whenever any Filter blueprint instances are reinstanced
- L82 _protected prototype_ `TSharedRef<IFilterObject> AddFilterObjectToDataBuilder(UDataSourceFilter* Filter, FTreeViewDataBuilder& InBuilder);` — Helper function to populate FTreeViewDataBuilder with a specific FilterObject
- L84 _protected prototype_ `void SetupWorldFilters();`
- L87 _protected prototype_ `void OnAssetsPendingDelete(TArray<UObject*> const& ObjectsForDelete);` — Callback for whenever any Filter instance blueprint class gets deleted
- L90 _protected member_ `TArray<TObjectPtr<UBlueprint>> DelegateRegisteredBlueprints;` — Blueprints on which a OnCompiled calllback has been registered, used to refresh data and repopulate the UI
- L93 _protected member_ `USourceFilterCollection* FilterCollection;` — Filter collection this session represents, retrieved from FTraceSourceFiltering
- L96 _protected member_ `FOnSessionStateChanged OnSessionStateChanged;` — Delegate used to rely data updates to notify anyone interested
- L99 _protected member_ `TSharedPtr<FExtender> Extender;` — UI extender, used to insert preset functionality into STraceSourceFilteringWindow
- L102 _protected member_ `TMap<uint32, const UWorld*> HashToWorld;` — World filtering data
- L103 _protected member_ `TArray<TSharedPtr<IWorldTraceFilter>> WorldFilters;`
- L106 _protected member_ `static FString TransactionContext;` — Transaction context naming for all scoped transactions performed in thsi class

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/FilterDragDropOperation.h` (Private)


#### class `FFilterDragDropOp`  
`class FFilterDragDropOp : public FDragDropOperation`  
_L12-86_
- inherits: `FDragDropOperation`
- L15 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FFilterDragDropOp, FDragDropOperation) TWeakPtr<class IFilterObject> FilterObject;`
- L20 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override` — The widget decorator to use
- L48 _public function_ `FText GetHoverText() const`
- L53 _public function_ `FText GetIconText() const`
- L58 _public function_ `void SetIconText(FText InText)`
- L63 _public function_ `void SetText(FText InText)`
- L68 _public function_ `void Reset()`
- L74 _public function_ `static TSharedRef<FFilterDragDropOp> New(TSharedRef<class IFilterObject> InFilterObject)`
- L84 _private member_ `FText IconText;`
- L85 _private member_ `FText Text;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/FilterObject.h` (Private)


#### class `FFilterObject`  
`class FFilterObject : public IFilterObject`  
_L11-31_
- inherits: `IFilterObject`
- L14 _public prototype_ `FFilterObject(IDataSourceFilterInterface& InFilter, TSharedRef<ISessionSourceFilterService> InSessionFilterService);`
- L17 _public prototype_ `virtual FText GetDisplayText() const;` — Begin IFilterObject overrides
- L18 _public prototype_ `virtual FText GetToolTipText() const;`
- L19 _public prototype_ `virtual UObject* GetFilter() const;`
- L20 _public prototype_ `virtual bool IsFilterEnabled() const;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SWrapBox> ParentWrapBox) const;`
- L22 _public prototype_ `virtual FReply HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L23 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L24 _public prototype_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) override;`
- L29 _protected member_ `TWeakInterfacePtr<IDataSourceFilterInterface> WeakInterface;` — Weak interface pointer retrieved from Data Source Filter instance this object represents
- L30 _protected member_ `TSharedPtr<ISessionSourceFilterService> SessionFilterService;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/FilterSetObject.h` (Private)


#### class `FFilterSetObject`  
`class FFilterSetObject : public IFilterObject`  
_L12-46_
- inherits: `IFilterObject`
- L15 _public prototype_ `FFilterSetObject(IDataSourceFilterSetInterface& InFilterSet, IDataSourceFilterInterface& InFilter, const TArray<TSharedPtr<IFilterObject>>& InChildFilters, TSharedRef<ISessionSourceFilterService> InSessionFilterService);`
- L18 _public prototype_ `virtual FText GetDisplayText() const;` — Begin IFilterObject overrides
- L19 _public prototype_ `virtual FText GetToolTipText() const;`
- L20 _public prototype_ `virtual UObject* GetFilter() const;`
- L21 _public prototype_ `virtual bool IsFilterEnabled() const;`
- L22 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SWrapBox> ParentWrapBox) const;`
- L23 _public prototype_ `virtual FReply HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L24 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L25 _public prototype_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) override;`
- L30 _protected prototype_ `void AddFilterSetModeWidget(TSharedRef<SWrapBox> ParentWrapBox) const;` — Adds appropriate Filter Set operation widget to the provided SWrapBox
- L34 _protected member_ `TWeakInterfacePtr<IDataSourceFilterInterface> WeakFilter;` — Weak filter interface pointer retrieved from Data Source Filter instance this object represents
- L36 _protected member_ `TWeakInterfacePtr<IDataSourceFilterSetInterface> WeakFilterSet;` — Weak filter set interface pointer retrieved from Data Source Filter instance this object represents
- L39 _protected member_ `TArray<TSharedPtr<IFilterObject>> ChildFilters;` — Any filter objects which are part of this set
- L42 _protected member_ `TSharedPtr<ISessionSourceFilterService> SessionFilterService;` — Session filter service which is responsible for generating this object
- L45 _protected member_ `const UEnum* FilterSetModeEnumPtr;` — Cached pointer to UEnum representing EFilterSetMode

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/IFilterObject.h` (Private)


#### class `IFilterObject`  
`class IFilterObject : public TSharedFromThis<IFilterObject>`  
_L16-44_
- inherits: `TSharedFromThis<IFilterObject>`
- desc: Interface for any FilterObject representation throughout the Filtering UI
- L19 _public prototype_ `virtual ~IFilterObject() = default;`
- L22 _public prototype_ `virtual FText GetDisplayText() const = 0;` — Return the display text to be displayed for this object
- L25 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Return the tooltip to be displayed for this object
- L28 _public prototype_ `virtual UObject* GetFilter() const = 0;` — Return Filter UObject
- L31 _public prototype_ `virtual bool IsFilterEnabled() const = 0;` — Return whether or not this filter object is currently enabled
- L34 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SWrapBox> ParentWrapBox) const = 0;` — Generate widget representing this object
- L37 _public prototype_ `virtual FReply HandleDragEnter(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop enter event
- L40 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop leave event
- L43 _public prototype_ `virtual FReply HandleDrop(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop drop event

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/ISessionSourceFilterService.h` (Private)


#### class `IWorldTraceFilter`  
`class IWorldTraceFilter : public TSharedFromThis<IWorldTraceFilter>`  
_L25-32_
- inherits: `TSharedFromThis<IWorldTraceFilter>`
- desc: Interface for implementing a World filter, setting whether or not a specific UWorld and its contained objects can Trace out data (events)
- L28 _public prototype_ `virtual ~IWorldTraceFilter() = default;`
- L29 _public prototype_ `virtual FText GetDisplayText() = 0;`
- L30 _public prototype_ `virtual FText GetToolTipText() = 0;`
- L31 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget() = 0;`

#### class `ISessionSourceFilterService`  
`class ISessionSourceFilterService : public TSharedFromThis<ISessionSourceFilterService>`  
_L35-113_
- inherits: `TSharedFromThis<ISessionSourceFilterService>`
- desc: Interface providing interaction with an running instance's its Trace and World Filtering systems
- L38 _public prototype_ `virtual ~ISessionSourceFilterService() = default;`
- L41 _public prototype_ `virtual FOnSessionStateChanged& GetOnSessionStateChanged() = 0;` — Delegate which gets broadcast-ed whenever the contained data (state) changes
- L44 _public prototype_ `virtual bool IsActionPending() const = 0;` — Returns whether or not a request action is pending complete
- L47 _public prototype_ `virtual void AddFilter(const FString& FilterClassName) = 0;` — Adds a Filter instance of the provided UClass name
- L50 _public prototype_ `virtual void RemoveFilter(TSharedRef<const IFilterObject> InFilter) = 0;` — Removes a specific Filter (Set) instance
- L53 _public prototype_ `virtual void AddFilterToSet(TSharedRef<const IFilterObject> FilterSet, const FString& FilterClassName) = 0;` — Add a Filter instance, of the provided UClass name, to the specified Filter Set instance
- L56 _public prototype_ `virtual void AddFilterToSet(TSharedRef<const IFilterObject> FilterSet, TSharedRef<const IFilterObject> ExistingFilter) = 0;` — Add a specific Filter instance to the specified Filter Set instance
- L59 _public prototype_ `virtual void MakeTopLevelFilter(TSharedRef<const IFilterObject> Filter) = 0;` — Moves the specific filter to root level in the filtering tree
- L62 _public prototype_ `virtual void MakeFilterSet(TSharedRef<const IFilterObject> ExistingFilter, EFilterSetMode Mode) = 0;` — Creates a new Filter Set instance, with the provided filter mode, replacing and containing the specific Filter instance
- L65 _public prototype_ `virtual void MakeFilterSet(TSharedRef<const IFilterObject> ExistingFilter, TSharedRef<const IFilterObject> ExistingFilterOther) = 0;` — Creates a new Filter Set instance, with default AND filter mode, replacing and containing the specific Filter instances
- L68 _public prototype_ `virtual void SetFilterState(TSharedRef<const IFilterObject> InFilter, bool bState) = 0;` — Sets the state of a specific Filter instance, true= enabled; false= disabled
- L71 _public prototype_ `virtual void SetFilterSetMode(TSharedRef<const IFilterObject> InFilter, EFilterSetMode Mode) = 0;` — Sets the Filtering Mode for a specific Filter Set instance
- L74 _public prototype_ `virtual void ResetFilters() = 0;` — Resets the complete filtering tree, removing all Filter instances
- L77 _public prototype_ `virtual void UpdateFilterSettings(UTraceSourceFilteringSettings* InSettings) = 0;` — Updates the Filtering Settings for this specific session
- L80 _public prototype_ `virtual UTraceSourceFilteringSettings* GetFilterSettings() = 0;` — Retrieves the current state of the Filtering Settings for this specific session
- L83 _public prototype_ `virtual void PopulateTreeView(FTreeViewDataBuilder& InBuilder) = 0;` — Request to populate a TreeView using the filter (set) hierarchy
- L86 _public prototype_ `virtual TSharedRef<SWidget> GetFilterPickerWidget(FOnFilterClassPicked InFilterClassPicked) = 0;` — Returns a slate widget used for picking a Filter class, which will execute the passed in delegate on selection/completion
- L89 _public prototype_ `virtual TSharedRef<SWidget> GetClassFilterPickerWidget(FOnFilterClassPicked InFilterClassPicked) = 0;` — Returns a slate widget used for picking AActor derived UClass, which will execute the passed in delegate on selection/completion
- L92 _public prototype_ `virtual TSharedPtr<FExtender> GetExtender() = 0;` — Returns an FExtender instance which is incorporated anytime a context menu (MenuBuilder) is created
- L95 _public prototype_ `virtual void GetWorldObjects(TArray<TSharedPtr<FWorldObject>>& OutWorldObjects) = 0;` — Returns an FWorldObject for each active UWorld instance
- L97 _public prototype_ `virtual void SetWorldTraceability(TSharedRef<FWorldObject> InWorldObject, bool bState) = 0;` — Sets whether or not the UWorld represented by InWorldObject is traceable
- L100 _public prototype_ `virtual const TArray<TSharedPtr<IWorldTraceFilter>>& GetWorldFilters() = 0;` — Returns all currently available World Trace filters
- L103 _public prototype_ `virtual void AddClassFilter(const FString& ActorClassName) = 0;` — Add a class filter, used to filter AActors on a high-level
- L106 _public prototype_ `virtual void RemoveClassFilter(TSharedRef<FClassFilterObject> ClassFilterObject) = 0;` — Removes a specific Class Filter instance
- L109 _public prototype_ `virtual void GetClassFilters(TArray<TSharedPtr<FClassFilterObject>>& OutClasses) const = 0;` — Returns all Class filters
- L112 _public prototype_ `virtual void SetIncludeDerivedClasses(TSharedRef<FClassFilterObject> ClassFilterObject, bool bIncluded) = 0;` — Updating whether or not classes derived from the filter class should be included when applying filtering

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFilterClassPicked, FString );`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFilterClassPicked, FString );`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSessionStateChanged);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSessionStateChanged);`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SClassTraceFilteringWidget.h` (Private)


#### class `SClassTraceFilteringWidget`  
`class SClassTraceFilteringWidget : public SCompoundWidget`  
_L12-38_
- inherits: `SCompoundWidget`
- L16 _public function_ `SClassTraceFilteringWidget()` — Default constructor.
- L17 _public prototype_ `virtual ~SClassTraceFilteringWidget() = default;`
- L19 _public function_ `SLATE_BEGIN_ARGS(SClassTraceFilteringWidget)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `void SetSessionFilterService(TSharedPtr<ISessionSourceFilterService> InSessionFilterService);`
- L25 _protected prototype_ `void ConstructClassFilterPickerButton();`
- L26 _protected prototype_ `void RefreshClassFilterData();`
- L29 _protected member_ `TSharedPtr<ISessionSourceFilterService> SessionFilterService;` — Session service used to retrieve state and request filtering changes
- L32 _protected member_ `TArray<TSharedPtr<FClassFilterObject>> ClassFilterObjects;` — Latest set of retrieved Class Filter Objects from SessionFilterService
- L35 _protected member_ `TSharedPtr<SWrapBox> ClassFiltersWrapBox;` — Wrap box that will contain the class filter object widgets
- L37 _protected member_ `TSharedPtr<SComboButton> AddClassFilterButton;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SFilterObjectWidget.h` (Private)


#### class `SFilterObjectRowWidget`  
`class SFilterObjectRowWidget : public STableRow<TSharedPtr<IFilterObject>>`  
_L10-29_
- inherits: `STableRow<TSharedPtr<IFilterObject>>`
- L12 _private function_ `SLATE_BEGIN_ARGS(SFilterObjectRowWidget)`
- L13 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<IFilterObject> InObject);`
- L16 _private prototype_ `virtual ~SFilterObjectRowWidget() = default;`
- L19 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Begin STableRow<TSharedPtr<IFilterObject>> overrides
- L20 _private prototype_ `virtual void OnDragEnter(FGeometry const& MyGeometry, FDragDropEvent const& DragDropEvent) override;`
- L21 _private prototype_ `virtual void OnDragLeave(FDragDropEvent const& DragDropEvent) override;`
- L22 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L23 _private prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L28 _protected member_ `TSharedPtr<IFilterObject> Object;` — Filter object this row represents

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SSourceFilteringTreeview.h` (Private)


#### class `SSourceFilteringTreeView`  
`class SSourceFilteringTreeView : public STreeView<TSharedPtr<IFilterObject>>`  
_L11-27_
- inherits: `STreeView<TSharedPtr<IFilterObject>>`
- desc: Simple treeview derived widget , main purpose is to implement drag-and-drop capabilities
- L14 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SUserTraceFilteringWidget> InOwner);`
- L18 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Begin STreeView<TSharedPtr<IFilterObject>> overrides
- L19 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L20 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L21 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L22 _protected prototype_ `virtual int32 GetNumItemsBeingObserved() const override;`
- L26 _protected member_ `TWeakPtr<SUserTraceFilteringWidget> Owner;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/STraceSourceFilteringWidget.h` (Private)


#### class `STraceSourceFilteringWidget`  
`class STraceSourceFilteringWidget : public SCompoundWidget`  
_L22-89_
- inherits: `SCompoundWidget`
- L26 _public function_ `STraceSourceFilteringWidget() : FilteringSettings(nullptr)` — Default constructor.
- L29 _public prototype_ `virtual ~STraceSourceFilteringWidget();` — Virtual destructor.
- L31 _public function_ `SLATE_BEGIN_ARGS(STraceSourceFilteringWidget)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Begin SCompoundWidget overrides
- L42 _protected prototype_ `void ConstructMenuBox();`
- L44 _protected prototype_ `TSharedRef<SWidget> OnGetOptionsMenu();`
- L47 _protected prototype_ `void SetCurrentAnalysisSession(uint32 SessionHandle, TSharedRef<const TraceServices::IAnalysisSession> AnalysisSession);` — Callback for whenever a different analysis session (store) has been retrieved
- L50 _protected prototype_ `bool HasValidFilterSession() const;` — Returns whether or not a valid ISessionSourceFilterService is available / set
- L53 _protected prototype_ `EVisibility GetThrobberVisibility() const;` — Returns visibility state for SThrobber, used to indicate pending filter session request
- L56 _protected prototype_ `bool ShouldWidgetsBeEnabled() const;` — Returns whether or not the contained widgets should be enabled, determined by having a valid session and no pending request
- L59 _protected prototype_ `void RefreshFilteringData();` — Refreshes the filtering data and state, using SessionFilterService, represented by this widget
- L62 _protected prototype_ `void SaveFilteringSettings();` — Save current UTraceSourceFilteringSettings state to INI files
- L65 _protected prototype_ `void AddExpandableArea(const FText& AreaName, TSharedRef<SWidget> AreaWidget);` — Adds an expandable area widget to ContentBox
- L68 _protected member_ `TSharedPtr<SHorizontalBox> MenuBox;` — Slate widget containing the Add Filter and Options widgets, used for disabling/enabling according to the session state
- L71 _protected member_ `TSharedPtr<SVerticalBox> ContentBox;` — Vertical box contain the individual expandable areas
- L74 _protected member_ `TSharedPtr<ISessionSourceFilterService> SessionFilterService;` — Filter session instance, used to retrieve data and communicate with connected application
- L77 _protected member_ `TSharedPtr<SWorldTraceFilteringWidget> WorldFilterWidget;` — Widget used for filtering UWorld's traceability on the connected filter session
- L80 _protected member_ `TSharedPtr<SClassTraceFilteringWidget> ClassFilterWidget;` — Widget used for filtering AActors when applying user filters for a given UWorld
- L82 _protected member_ `TSharedPtr<SUserTraceFilteringWidget> UserFilterWidget;` — Widget used for setting up User Filters applied to actor within a given UWorld
- L85 _protected member_ `FDateTime SyncTimestamp;` — Timestamp at which the treeview data was last retrieved from SessionFilterService
- L88 _protected member_ `UTraceSourceFilteringSettings* FilteringSettings;` — Cached pointer to Filtering Settings retrieved from SessionFilterService

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SUserTraceFilteringWidget.h` (Private)


#### class `SUserTraceFilteringWidget`  
`class SUserTraceFilteringWidget : public SCompoundWidget`  
_L15-65_
- inherits: `SCompoundWidget`
- L20 _public function_ `SUserTraceFilteringWidget()` — Default constructor.
- L21 _public prototype_ `virtual ~SUserTraceFilteringWidget() = default;`
- L23 _public function_ `SLATE_BEGIN_ARGS(SUserTraceFilteringWidget)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `void SetSessionFilterService(TSharedPtr<ISessionSourceFilterService> InSessionFilterService);`
- L30 _protected prototype_ `void ConstructTreeview();`
- L31 _protected prototype_ `void ConstructInstanceDetailsView();`
- L32 _protected prototype_ `void ConstructUserFilterPickerButton();`
- L34 _protected prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L36 _protected prototype_ `void RefreshUserFilterData();`
- L39 _protected prototype_ `void SaveTreeviewState();` — Saves and restores the current selection and expansion state of FilterTreeView
- L40 _protected prototype_ `void RestoreTreeviewState();`
- L43 _protected member_ `TSharedPtr<ISessionSourceFilterService> SessionFilterService;` — Session service used to retrieve state and request filtering changes
- L46 _protected member_ `TSharedPtr<SComboButton> AddUserFilterButton;` — Slate widget used to add filter instances to the session
- L49 _protected member_ `TArray<TSharedPtr<IFilterObject>> FilterObjects;` — Data used to populate the Filter Treeview
- L50 _protected member_ `TMap<TSharedPtr<IFilterObject>, TArray<TSharedPtr<IFilterObject>>> ParentToChildren;`
- L51 _protected member_ `TArray<TSharedPtr<IFilterObject>> FlatFilterObjects;`
- L54 _protected member_ `TArray<int32> ExpandedFilters;` — Used to store hash values of, treeview expanded and selected, filter instances when refreshing the treeview data
- L55 _protected member_ `TArray<int32> SelectedFilters;`
- L59 _protected member_ `TSharedPtr<SSourceFilteringTreeView> FilterTreeView;` — Treeview used to display all currently represented Filters
- L63 _protected member_ `TSharedPtr<IDetailsView> FilterInstanceDetailsView;` — Details view, used for displaying selected Filter UProperties

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SWorldObjectWidget.h` (Private)


#### class `SWorldObjectRowWidget`  
`class SWorldObjectRowWidget : public STableRow<TSharedPtr<FWorldObject>>`  
_L13-27_
- inherits: `STableRow<TSharedPtr<FWorldObject>>`
- desc: Table row representing a UWorld instance, as a FWorldObject, within SWorldFilterWidget
- L15 _private function_ `SLATE_BEGIN_ARGS(SWorldObjectRowWidget)`
- L16 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<FWorldObject> InWorldObject, TSharedPtr<ISessionSourceFilterService> InFilterService);`
- L19 _private prototype_ `virtual ~SWorldObjectRowWidget() = default;`
- L23 _protected member_ `TSharedPtr<FWorldObject> WorldObject;` — The World object that this tree item represents
- L26 _protected member_ `TSharedPtr<ISessionSourceFilterService> FilterService;` — Session service that has generated this object

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SWorldTraceFilteringWidget.h` (Private)


#### class `SWorldTraceFilteringWidget`  
`class SWorldTraceFilteringWidget : public SCompoundWidget`  
_L15-43_
- inherits: `SCompoundWidget`
- L19 _public function_ `SWorldTraceFilteringWidget()` — Default constructor.
- L21 _public prototype_ `virtual ~SWorldTraceFilteringWidget() = default;`
- L23 _public function_ `SLATE_BEGIN_ARGS(SWorldTraceFilteringWidget)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `void SetSessionFilterService(TSharedPtr<ISessionSourceFilterService> InSessionFilterService);`
- L29 _protected prototype_ `void RefreshWorldData();`
- L32 _protected member_ `TSharedPtr<ISessionSourceFilterService> SessionFilterService;` — Session service used to retrieve state and request filtering changes
- L35 _protected member_ `TArray<TSharedPtr<FWorldObject>> WorldObjects;` — Latest set of retrieve World Objects from SessionFilterService
- L38 _protected member_ `TSharedPtr<SListView<TSharedPtr<FWorldObject>>> WorldListView;` — Listview widget used to display WorldObjects
- L40 _protected member_ `TSharedPtr<SHorizontalBox> FiltersContainerBox;`
- L41 _protected member_ `TSharedPtr<SVerticalBox> FiltersLabelBox;`
- L42 _protected member_ `TSharedPtr<SVerticalBox> FiltersWidgetBox;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SourceFilterService.h` (Private)


#### class `FSourceFilterService`  
`class FSourceFilterService`  
_L14-19_
- L18 _public prototype_ `static TSharedRef<ISessionSourceFilterService> GetFilterServiceForSession(uint32 InHandle, TSharedRef<const TraceServices::IAnalysisSession> AnalysisSession);` — Retrieves the ISessionSourceFilterService for the provided Trace Session Handle

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SourceFilterStyle.h` (Private)


#### class `FSourceFilterStyle`  
`class FSourceFilterStyle`  
_L10-29_
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static const ISlateStyle& Get();`
- L17 _public prototype_ `static const FName& GetStyleSetName();`
- L18 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L24 _private member_ `static FSlateBrush* FilterBrush;`
- L25 _private member_ `static FSlateBrush* FilterSetBrush;`
- L27 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;` — Singleton instances of this style.
- L28 _private member_ `static FTextBlockStyle NormalText;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/SourceFilteringEditorModule.h` (Private)


#### class `FSourceFilteringEditorModule`  
`class FSourceFilteringEditorModule : public IModuleInterface`  
_L13-44_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public member_ `static FString SourceFiltersIni;`
- L22 _protected prototype_ `void RegisterLayoutExtensions(FInsightsMajorTabExtender& InOutExtender);`
- L24 _protected prototype_ `void ToggleSourceFilteringVisibility();`
- L25 _protected prototype_ `bool IsSourceFilteringVisibile();`
- L27 _protected member_ `TSharedPtr<FTabManager> InsightsTabManager;`
- L28 _protected member_ `bool bIsSourceFilterTabOpen = false;`
- L38 _protected member_ `TArray<FPendingFilterDeletion> PendingDeletions;`
- L41 _protected prototype_ `void HandleAssetDeleted(UObject* DeletedObject);` — Callbacks to handle blueprint source filter class deletion
- L42 _protected prototype_ `void OnAssetsPendingDelete(TArray<UObject*> const& ObjectsForDelete);`

#### struct `FSourceFilteringEditorModule::FPendingFilterDeletion`  
`struct FPendingFilterDeletion`  
_L32-37_
- desc: Keeps track of any source filters due to be removed because their class (blueprint) is due to be deleted
- L34 _public member_ `class UDataSourceFilter* FilterWithDeletedClass;`
- L35 _public member_ `class UDataSourceFilter* ReplacementFilter;`
- L36 _public member_ `const UObject* ToDeleteFilterClassObject;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/TreeViewBuilder.h` (Private)


#### struct `FTreeViewDataBuilder`  
`struct FTreeViewDataBuilder`  
_L10-26_
- desc: Helper structure allowing a ISessionSourceFilterService to populate the data use to generate the SSourceFilteringTreeView in STraceSourceFilteringWidget
- L12 _public function_ `FTreeViewDataBuilder(TArray<TSharedPtr<IFilterObject>>& InFilterObjects, TMap<TSharedPtr<IFilterObject>, TArray<TSharedPtr<IFilterObject>>>& InParentToChildren, TArray<TSharedPtr<IFilterObject>>& InFlatFilterObjects) : FilterObjects(InFilterObjects), ParentToChildren(InParentToChildren), FlatFilterObjects(InFlatFilterObjects)`
- L15 _public prototype_ `void AddFilterObject(TSharedRef<IFilterObject> FilterObject);` — Add a root-level filter
- L17 _public prototype_ `void AddChildFilterObject(TArray<TSharedPtr<IFilterObject>> FilterObjects, TSharedRef<IFilterObject> ParentObject);` — Add a set of child-filters for a, previously added, parent filter
- L21 _protected member_ `TArray<TSharedPtr<IFilterObject>>& FilterObjects;` — Root-level filter objects
- L23 _protected member_ `TMap<TSharedPtr<IFilterObject>, TArray<TSharedPtr<IFilterObject>>>& ParentToChildren;` — Parent / child filter(s) mapping
- L25 _protected member_ `TArray<TSharedPtr<IFilterObject>>& FlatFilterObjects;` — Flat list of all the filter objects contained in both FilterObjects and ParentToChildren

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/WorldFilters.h` (Private)


#### class `FWorldTypeTraceFilter`  
`class FWorldTypeTraceFilter : public IWorldTraceFilter`  
_L10-31_
- inherits: `IWorldTraceFilter`
- desc: World filter implementation, that marks Worlds as traceable according to their EWorldType
- L13 _public prototype_ `FWorldTypeTraceFilter(const TFunction<void(uint8, bool)>& InOnSetWorldTypeFilterState, const TFunction<bool(uint8)>& InOnGetWorldTypeFilterState);`
- L16 _public prototype_ `virtual FText GetDisplayText() override;` — Begin IWorldTraceFilter Overrides
- L17 _public prototype_ `virtual FText GetToolTipText() override;`
- L18 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget() override;`
- L22 _protected prototype_ `void SaveSettings();` — Load / save any settings to config that should be persistent between editor sessions
- L23 _protected prototype_ `void LoadSettings();`
- L26 _protected member_ `TFunction<void(uint8, bool)> OnSetWorldTypeFilterState;`
- L27 _protected member_ `TFunction<bool(uint8)> OnGetWorldTypeFilterState;`
- L29 _protected member_ `FText WorldTypeFilterName;`
- L30 _protected member_ `TArray<TPair<FText, TArray<uint8>>> WorldTypeFilterValues;`

#### class `FWorldNetModeTraceFilter`  
`class FWorldNetModeTraceFilter : public IWorldTraceFilter`  
_L34-54_
- inherits: `IWorldTraceFilter`
- desc: World filter implementation, that marks Worlds as traceable according to their ENetMode
- L37 _public prototype_ `FWorldNetModeTraceFilter(const TFunction<void(uint8, bool)>& InOnSetWorldNetModeFilterState, const TFunction<bool(uint8)>& InOnGetWorldNetModeFilterState);`
- L40 _public prototype_ `virtual FText GetDisplayText() override;` — Begin IWorldTraceFilter Overrides
- L41 _public prototype_ `virtual FText GetToolTipText() override;`
- L42 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget() override;`
- L46 _protected prototype_ `void SaveSettings();` — Load / save any settings to config that should be persistent between editor sessions
- L47 _protected prototype_ `void LoadSettings();`
- L49 _protected member_ `TFunction<void(uint8, bool)> OnSetWorldNetModeFilterState;`
- L50 _protected member_ `TFunction<bool(uint8)> OnGetWorldNetModeFilterState;`
- L52 _protected member_ `FText WorldNetModeFilterName;`
- L53 _protected member_ `TArray<TPair<FText, TArray<uint8>>> WorldNetModeFilterValues;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringEditor/Private/WorldObject.h` (Private)


#### class `FWorldObject`  
`class FWorldObject : public TSharedFromThis<FWorldObject>`  
_L8-23_
- inherits: `TSharedFromThis<FWorldObject>`
- desc: Object representing an UWorld and its filtering state
- L11 _public function_ `FWorldObject(const FString& InName, uint8 InWorldType, bool bState, uint32 InHash) : Name(InName), WorldType(InWorldType), bCanOutputData(bState), Hash(InHash)`
- L13 _public function_ `const FText GetDisplayText() const`
- L14 _public function_ `const FString& GetName() const`
- L15 _public function_ `bool CanOutputData() const`
- L16 _public function_ `const uint32 GetHash() const`
- L18 _protected member_ `FString Name;`
- L20 _protected member_ `uint8 WorldType;` — Corresponds to EWorldType in Engine
- L21 _protected member_ `bool bCanOutputData;`
- L22 _protected member_ `uint32 Hash;`
