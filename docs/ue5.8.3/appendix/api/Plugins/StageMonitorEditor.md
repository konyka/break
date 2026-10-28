# Plugins / StageMonitorEditor

- module root: `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor`
- headers: 8; symbols: 210
- symbol kinds: class=11, delegate=1, enum=1, enumerator=7, function=8, member=48, namespace=1, prototype=124, struct=1, typedef=8
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, EditorStyle, Engine, GameplayTags, InputCore, Json, LevelEditor, Projects, Slate, SlateCore, StageDataCore, StageMonitor, StageMonitorCommon, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/SStageMonitorPanel.h` (Private)


#### class `SStageMonitorPanel`  
`class SStageMonitorPanel : public SCompoundWidget`  
_L19-120_
- inherits: `SCompoundWidget`
- desc: Panel used to show stage monitoring data
- L22 _public prototype_ `virtual ~SStageMonitorPanel() = default;`
- L24 _public prototype_ `static void RegisterNomadTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L25 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L26 _public prototype_ `static TSharedPtr<SStageMonitorPanel> GetPanelInstance();`
- L29 _private typedef_ `using Super = SCompoundWidget;`
- L30 _private member_ `static TWeakPtr<SStageMonitorPanel> PanelInstance;`
- L31 _private member_ `static FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SStageMonitorPanel)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _private prototype_ `TSharedRef<SWidget> MakeToolbarWidget();` — Make the toolbar widgets
- L45 _private prototype_ `FReply OnClearClicked();` — Handles clear everything button clicked
- L48 _private prototype_ `void OnClearEntriesClicked();` — Clears all entries from the current session
- L51 _private prototype_ `void OnClearUnresponsiveProvidersClicked();` — Clears all unresponsive providers
- L54 _private prototype_ `TSharedRef<SWidget> OnClearBuildMenu();` — Builds a menu for specific clearing option
- L57 _private prototype_ `FReply OnShowProjectSettingsClicked();` — Handles StageMonitor settings button clicked
- L60 _private prototype_ `FReply OnLoadSessionClicked();` — Handles load session button clicked
- L63 _private prototype_ `FReply OnSaveSessionClicked();` — Handles save session button clicked
- L66 _private prototype_ `FSlateColor GetStageStatus() const;` — Get the stage status
- L69 _private prototype_ `FText GetStageActiveStateReasonText() const;` — Get the top reason why the stage is considered active
- L72 _private prototype_ `FText GetMonitorStatus() const;` — Returns the monitor status whether it's actively listening for data providers or not
- L75 _private prototype_ `ECheckBoxState IsMonitorActive() const;` — Returns whether the monitor is active or not for checkbox state
- L78 _private prototype_ `void OnMonitorStateChanged(ECheckBoxState NewState);` — Callback when user toggles the monitor state switch
- L81 _private prototype_ `FText GetCurrentSessionInfo() const;` — Returns information about the displayed session
- L84 _private prototype_ `void OnStageMonitorSessionLoaded();` — Callback when a requested session was loaded
- L87 _private prototype_ `void OnStageMonitorSessionSaved();` — Callback when a save session request was completed
- L90 _private prototype_ `ECheckBoxState GetViewMode() const;` — Returns whether we're displaying live session or loaded one
- L93 _private prototype_ `void OnViewModeChanged(ECheckBoxState NewState);` — Called when view mode switch is clicked
- L96 _private prototype_ `void RefreshDisplayedSession();` — Updates UI when a new session was loaded or live mode is activated
- L99 _private prototype_ `EVisibility GetThrobberVisibility() const;` — When waiting for loading/saving session display the throbber
- L102 _private prototype_ `FReply OnCancelRequest();` — Used to cancel loading or saving that is in progress
- L107 _private member_ `TSharedPtr<SDataProviderListView> DataProviderList;` — Used to show all providers with their frame data
- L110 _private member_ `TSharedPtr<SDataProviderActivities> DataProviderActivities;` — Used to show every activities received by the monitor
- L113 _private member_ `TSharedPtr<IStageMonitorSession> CurrentSession;` — Session shown by the monitor editor
- L116 _private member_ `bool bIsShowingLiveSession = true;` — Driven by the toggle switch from the UI. Keeps wheter we are showing live data or imported
- L119 _private member_ `bool bIsWaitingForAsyncResult = false;` — When we request saving or loading, this will be true to show update UI

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/StageMessageTypeDetailCustomization.h` (Private)


#### class `FStageMessageTypeDetailCustomization`  
`class FStageMessageTypeDetailCustomization : public IPropertyTypeCustomization`  
_L9-27_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L17 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;` — IDetailCustomization interface
- L18 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L21 _private prototype_ `TSharedRef<SWidget> HandleSourceComboButtonMenuContent();`
- L26 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the structure property we're editing

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/StageMonitorEditorModule.h` (Private)


#### class `FStageMonitorEditorModule`  
`class FStageMonitorEditorModule : public IModuleInterface`  
_L11-26_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private prototype_ `void RegisterCustomizations();` — Registers detail customization for stage monitoring types
- L25 _private prototype_ `void UnregisterCustomizations();` — Unregisters registered customizations

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStageMonitorEditor, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStageMonitorEditor, Log, All);`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/StageMonitorEditorSettings.h` (Private)


#### class `UStageMonitorEditorSettings`  
`class UStageMonitorEditorSettings : public UObject`  
_L13-26_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UObject`
- desc: Settings for the editor aspect of the StageMonitoring plugin modules.
- L21 _public member_ `float RefreshRate = 0.2f;` — `UPROPERTY(Config, EditAnywhere, Category = "UI", meta = (ClampMin = 0.0f))` — Refresh rate in seconds for the StageMonitor panel.
- L25 _public member_ `FString ColumnVisibilitySettings;` — `UPROPERTY(Config)` — Stores the state of the visibility settings in JSON format.

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/StageMonitorEditorStyle.h` (Private)


#### class `FStageMonitorEditorStyle`  
`class FStageMonitorEditorStyle : public FSlateStyleSet`  
_L10-20_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the StageMonitor UI
- L14 _public prototype_ `static FStageMonitorEditorStyle& Get();` — Access the singleton instance for this style set
- L18 _private prototype_ `FStageMonitorEditorStyle();`
- L19 _private prototype_ `~FStageMonitorEditorStyle();`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/Widgets/SDataProviderActivities.h` (Private)


#### class `SDataProviderActivitiesTableRow`  
`class SDataProviderActivitiesTableRow : public SMultiColumnTableRow<FDataProviderActivityPtr>`  
_L28-52_
- inherits: `SMultiColumnTableRow<FDataProviderActivityPtr>`
- L30 _private typedef_ `using Super = SMultiColumnTableRow<FDataProviderActivityPtr>;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SDataProviderActivitiesTableRow)`
- L34 _public prototype_ `SLATE_ARGUMENT(FDataProviderActivityPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwerTableView, TWeakPtr<IStageMonitorSession> InSession);`
- L41 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L43 _private prototype_ `FText GetTimecode() const;`
- L44 _private prototype_ `FText GetStageName() const;`
- L45 _private prototype_ `FText GetMessageType() const;`
- L46 _private prototype_ `FText GetDescription() const;`
- L49 _private member_ `FDataProviderActivityPtr Item;`
- L50 _private member_ `FStageInstanceDescriptor Descriptor;`
- L51 _private member_ `TWeakPtr<IStageMonitorSession> Session;`

#### class `SDataProviderActivities`  
`class SDataProviderActivities : public SCompoundWidget`  
_L58-108_
- inherits: `SCompoundWidget`
- L60 _private typedef_ `using Super = SCompoundWidget;`
- L63 _public function_ `SLATE_BEGIN_ARGS(SDataProviderActivities)`
- L64 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SStageMonitorPanel> OwnerPanel, const TWeakPtr<IStageMonitorSession>& InSession);`
- L67 _public prototype_ `virtual ~SDataProviderActivities();`
- L70 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L74 _public prototype_ `void RequestRebuild();` — Request a full rebuild of the list entries
- L77 _public prototype_ `void RequestRefresh();` — Request a refresh of the list widget.
- L80 _public prototype_ `void RefreshMonitorSession(const TWeakPtr<IStageMonitorSession>& NewSession);` — Refreshes session used to fetch data
- L83 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(FDataProviderActivityPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L84 _private prototype_ `void OnListViewSelectionChanged(FDataProviderActivityPtr InActivity, ESelectInfo::Type SelectInfo);`
- L85 _private prototype_ `void OnNewStageActivity(FDataProviderActivityPtr NewActivity);`
- L86 _private prototype_ `void InsertActivity(FDataProviderActivityPtr Activity);`
- L87 _private prototype_ `void OnActivityFilterChanged();`
- L88 _private prototype_ `void ReloadActivityHistory();`
- L89 _private prototype_ `void OnStageDataCleared();`
- L92 _private prototype_ `void AttachToMonitorSession(const TWeakPtr<IStageMonitorSession>& NewSession);` — Bind useful delegate to the active session
- L95 _private member_ `TWeakPtr<SStageMonitorPanel> OwnerPanel;`
- L96 _private member_ `TWeakPtr<IStageMonitorSession> Session;`
- L97 _private member_ `TSharedPtr<SListView<FDataProviderActivityPtr>> ActivityList;`
- L99 _private member_ `TArray<FDataProviderActivityPtr> Activities;`
- L100 _private member_ `TArray<FDataProviderActivityPtr> FilteredActivities;`
- L101 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L102 _private member_ `TSharedPtr<SDataProviderActivityFilter> ActivityFilter;`
- L104 _private member_ `int32 FramesSinceLastListRefresh = 0;`
- L106 _private member_ `bool bRebuildRequested = false;`
- L107 _private member_ `bool bRefreshRequested = false;`

#### Free symbols / members of external scopes

- L22 _typedef_ `using FDataProviderActivityPtr = TSharedPtr<FStageDataEntry>;`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/Widgets/SDataProviderActivityFilter.h` (Private)


#### struct `FDataProviderActivityFilterSettings`  
`struct FDataProviderActivityFilterSettings`  
_L22-60_
- reflection: `USTRUCT()`
- desc: Filter settings used live and also load/saved to ini config
- L31 _public member_ `TArray<TObjectPtr<UScriptStruct>> ExistingPeriodicTypes;` — `UPROPERTY()` — Periodic message structure type. Used to detect new types that would be filtered out automatically
- L35 _public member_ `TArray<TObjectPtr<UScriptStruct>> RestrictedTypes;` — `UPROPERTY()` — Message types that are filtered
- L39 _public member_ `TArray<FName> RestrictedProviders;` — `UPROPERTY()` — Providers that are filtered using their friendly name
- L43 _public member_ `TArray<FName> RestrictedRoles;` — `UPROPERTY()` — Roles that are filtered using their friendly name
- L47 _public member_ `TArray<FName> RestrictedSources;` — `UPROPERTY()` — Critical state sources that are filtered
- L51 _public member_ `bool bEnableCriticalStateFilter = false;` — `UPROPERTY()` — Global critical state filter state
- L55 _public member_ `bool bEnableTimeFilter = true;` — `UPROPERTY()` — Should time filtering (timecode age) be enabled
- L59 _public member_ `uint32 MaxMessageAgeInMinutes = 30;` — `UPROPERTY()` — How far back in time should we display messages

#### class `FDataProviderActivityFilter`  
`class FDataProviderActivityFilter`  
_L66-95_
- L69 _public prototype_ `FDataProviderActivityFilter(TWeakPtr<IStageMonitorSession> InSession);`
- L72 _public prototype_ `bool DoesItPass(TSharedPtr<FStageDataEntry>& Entry) const;` — Returns true if the entry passes the current filter
- L73 _public prototype_ `void FilterActivities(const TArray<TSharedPtr<FStageDataEntry>>& InUnfilteredActivities, TArray<TSharedPtr<FStageDataEntry>>& OutFilteredActivities) const;`
- L76 _public member_ `FDataProviderActivityFilterSettings FilterSettings;`
- L77 _public member_ `TWeakPtr<IStageMonitorSession> Session;`
- L80 _public member_ `mutable TMap<FString, TArray<FName>> CachedRoleStringToArray;` — Cache of stringified roles to array of roles to avoid parsing into array constantly
- L94 _private prototype_ `EFilterResult FilterActivity(const TSharedPtr<FStageDataEntry>& Entries) const;`

#### enum `FDataProviderActivityFilter::EFilterResult`  
`enum class EFilterResult : uint8`  
_L83-92_
- L85 _public enumerator_ `InvalidEntry`
- L86 _public enumerator_ `FailRestrictedTypes`
- L87 _public enumerator_ `FailRestrictedProviders`
- L88 _public enumerator_ `FailRestrictedCriticalState`
- L89 _public enumerator_ `FailMaxAge`
- L90 _public enumerator_ `FailRestrictedRoles`
- L91 _public enumerator_ `Pass`

#### class `SDataProviderActivityFilter`  
`class SDataProviderActivityFilter : public SCompoundWidget`  
_L101-206_
- inherits: `SCompoundWidget`
- L103 _private typedef_ `using Super = SCompoundWidget;`
- L106 _public function_ `SLATE_BEGIN_ARGS(SDataProviderActivityFilter)`
- L107 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnActivityFilterChanged) SLATE_END_ARGS() ~SDataProviderActivityFilter();`
- L111 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<IStageMonitorSession>& InSession);`
- L114 _public function_ `const FDataProviderActivityFilter& GetActivityFilter() const` — Returns the activity filter
- L117 _public prototype_ `void RefreshMonitorSession(const TWeakPtr<IStageMonitorSession>& NewSession);` — Refreshes session used to fetch data and update UI
- L122 _private prototype_ `void ToggleProviderFilter(FName ProviderName);` — Toggles state of provider filter
- L125 _private prototype_ `bool IsProviderFiltered(FName ProviderName) const;` — Returns true if provider is currently filtered out
- L128 _private prototype_ `void ToggleDataTypeFilter(UScriptStruct* Type);` — Toggles state of data type filter
- L131 _private prototype_ `bool IsDataTypeFiltered(UScriptStruct* Type) const;` — Returns true if data type is currently filtered out
- L134 _private prototype_ `void ToggleCriticalStateSourceFilter(FName Source);` — Toggles state of critical state source filter
- L137 _private prototype_ `bool IsCriticalStateSourceFiltered(FName Source) const;` — Returns true if critical state source is currently filtered out
- L140 _private prototype_ `void ToggleCriticalSourceEnabledFilter();` — Toggles whether critical source filtering is enabled or not
- L143 _private prototype_ `void ToggleTimeFilterEnabled(ECheckBoxState CheckboxState);` — Toggle whether time filtering is enabled.
- L146 _private prototype_ `bool IsCriticalSourceFilteringEnabled() const;` — Returns true if filtering by critical state source enabled
- L149 _private prototype_ `bool IsTimeFilterEnabled() const;` — Returns true if filtering by message age is enabled.
- L152 _private prototype_ `TSharedRef<SWidget> MakeAddFilterMenu();` — Create the AddFilter menu when combo button is clicked. Different filter types will be submenus
- L155 _private prototype_ `void CreateMessageTypeFilterMenu(FMenuBuilder& MenuBuilder);` — Creates the menu listing the different message types filter
- L158 _private prototype_ `void CreateProviderFilterMenu(FMenuBuilder& MenuBuilder);` — Creates the menu listing the different providers filter
- L161 _private prototype_ `void ToggleRoleFilter(FName RoleName);` — Toggles state of role filter
- L164 _private prototype_ `bool IsRoleFiltered(FName RoleName) const;` — Returns true if role is currently filtered out
- L167 _private prototype_ `void CreateRoleFilterMenu(FMenuBuilder& MenuBuilder);` — Creates the menu listing the different roles filter
- L170 _private prototype_ `void CreateCriticalStateSourceFilterMenu(FMenuBuilder& MenuBuilder);` — Create the menu listing all critical state sources
- L173 _private prototype_ `void CreateTimeFilterMenu(FMenuBuilder& MenuBuilder);` — Create a menu listing the options for filtering message based on their age.
- L176 _private prototype_ `void AttachToMonitorSession(const TWeakPtr<IStageMonitorSession>& NewSession);` — Binds this widget to some session callbacks
- L179 _private prototype_ `ECheckBoxState IsTimeFilterChecked() const;` — Returns whether the time filter checkbox should be checked or not.
- L182 _private prototype_ `TOptional<uint32> GetMaxMessageAge() const;` — Return the max age in minutes where messages should be filtered out.
- L185 _private prototype_ `void OnMaxMessageAgeChanged(uint32 NewMax);` — Handle modifying the maximum message age.
- L188 _private prototype_ `void OnMaxMessageAgeCommitted(uint32 NewMax, ETextCommit::Type);` — Handle setting the new maximum message age.
- L191 _private prototype_ `void LoadSettings();` — Load filtering settings from ini
- L194 _private prototype_ `void SaveSettings();` — Save filtering settings from ini
- L199 _private member_ `TUniquePtr<FDataProviderActivityFilter> CurrentFilter;` — Current state of the provider data filter
- L202 _private member_ `FSimpleDelegate OnActivityFilterChanged;` — Delegate fired when filter changed
- L205 _private member_ `TWeakPtr<IStageMonitorSession> Session;` — Weakptr to the current session we're sourcing info from

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ETextCommit`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/Widgets/SDataProviderListView.h` (Private)


#### class `SDataProviderTableRow`  
`class SDataProviderTableRow : public SMultiColumnTableRow<FDataProviderTableRowDataPtr>`  
_L17-62_
- inherits: `SMultiColumnTableRow<FDataProviderTableRowDataPtr>`
- L19 _private typedef_ `using Super = SMultiColumnTableRow<FDataProviderTableRowDataPtr>;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDataProviderTableRow)`
- L23 _public prototype_ `SLATE_ARGUMENT(FDataProviderTableRowDataPtr, Item) SLATE_ARGUMENT(float, Padding) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwerTableView);`
- L31 _public prototype_ `FText GetStateGlyphs() const;` — Getters to populate the UI
- L32 _public prototype_ `FSlateColor GetStateColorAndOpacity() const;`
- L33 _public prototype_ `FText GetStatus() const;`
- L34 _public prototype_ `FText GetStatusToolTip() const;`
- L35 _public prototype_ `FText GetTimecode() const;`
- L36 _public prototype_ `FText GetMachineName() const;`
- L37 _public prototype_ `FText GetProcessId() const;`
- L38 _public prototype_ `FText GetStageName() const;`
- L39 _public prototype_ `FText GetRoles() const;`
- L40 _public prototype_ `FText GetAverageFPS() const;`
- L41 _public prototype_ `FText GetEstimatedMaxFPS() const;`
- L42 _public prototype_ `FText GetIdleTime() const;`
- L43 _public prototype_ `FText GetGameThreadTiming() const;`
- L44 _public prototype_ `FText GetGameThreadWaitTiming() const;`
- L45 _public prototype_ `FText GetRenderThreadTiming() const;`
- L46 _public prototype_ `FText GetRenderThreadWaitTiming() const;`
- L47 _public prototype_ `FText GetGPUTiming() const;`
- L48 _public prototype_ `FText GetGPUMem() const;`
- L49 _public prototype_ `FText GetCPUMem() const;`
- L50 _public prototype_ `FText GetAssetsLeftToCompile() const;`
- L51 _public prototype_ `FText GetToolTipText() const;`
- L55 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Handles creation of each columns widget
- L58 _private member_ `FDataProviderTableRowDataPtr Item;` — Item to display
- L61 _private member_ `double LastRefreshTime = 0.0;` — Last time we refreshed the UI

#### class `SDataProviderListView`  
`class SDataProviderListView : public SListView<FDataProviderTableRowDataPtr>`  
_L68-139_
- inherits: `SListView<FDataProviderTableRowDataPtr>`
- L70 _private typedef_ `using Super = SListView<FDataProviderTableRowDataPtr>;`
- L73 _public function_ `SLATE_BEGIN_ARGS(SDataProviderListView)`
- L74 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IStageMonitorSession>& InSession);`
- L79 _public prototype_ `void RefreshMonitorSession(TWeakPtr<IStageMonitorSession> NewSession);` — Updates the session this widget is currently sourcing data from
- L82 _public prototype_ `virtual ~SDataProviderListView();` — Cleanup ourselves
- L85 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Used to refresh cached values shown in UI
- L90 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FDataProviderTableRowDataPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a new row for the listview using the Item data
- L93 _private prototype_ `void OnStageMonitoringMachineListChanged();` — Callback triggered when provider list changed
- L96 _private prototype_ `void RebuildDataProviderList();` — Rebuild provider list from scratch
- L99 _private prototype_ `void AttachToMonitorSession(const TWeakPtr<IStageMonitorSession>& NewSession);` — Binds to the current session desired delegates
- L102 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Returns sort method for a given column name
- L105 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Called when sort mode changed for a given column
- L108 _private prototype_ `void SortProviderList();` — Sorts provider list based on active column sort mode
- L113 _private prototype_ `void SetDefaultColumnVisibilities();` — Set the default column visibility state.
- L116 _private member_ `TArray<FDataProviderTableRowDataPtr> ListItemsSource;` — Widget and data containing info about what's shown in the listview
- L117 _private member_ `TArray<TWeakPtr<SDataProviderTableRow>> ListRowWidgets;`
- L120 _private member_ `TWeakPtr<IStageMonitorSession> Session;` — Pointer to the stage session data
- L123 _private member_ `bool bRebuildListRequested = false;` — Used to cache if list needs to be refreshed or not
- L126 _private member_ `double LastRefreshTime = 0.0;` — Timestamp when we last refreshed UI
- L129 _private member_ `FName SortedColumnName;` — Currently sorted column name
- L132 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;` — Sort mode for the currently sorted column
- L135 _private member_ `TMap<FString, TArray<FString>> CachedRoleStringToArray;` — Cache of stringified roles to array of roles to avoid parsing into array constantly
- L138 _private member_ `bool bUpdatingColumnVisibility = false;` — Boolean guard to prevent reentrant updates to the column visibility state.

#### Free symbols / members of external scopes

- L12 _typedef_ `using FDataProviderTableRowDataPtr = TSharedPtr<FDataProviderTableRowData>;`
