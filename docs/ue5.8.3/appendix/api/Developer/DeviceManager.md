# Developer / DeviceManager

- module root: `Source/Developer/DeviceManager`
- headers: 21; symbols: 220
- symbol kinds: class=20, delegate=4, function=68, macro=8, member=68, prototype=49, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, InputCore, Slate, SlateCore, TargetPlatform, WorkspaceMenuStructure
- PublicIncludePathModuleNames: TargetDeviceServices

### `Source/Developer/DeviceManager/Private/Models/DeviceBrowserFilter.h` (Private)


#### struct `FDeviceBrowserFilterEntry`  
`struct FDeviceBrowserFilterEntry`  
_L18-27_
- desc: An entry in the device browser filter.
- L20 _public member_ `FString PlatformName;`
- L21 _public member_ `FName PlatformLookup;`
- L23 _public function_ `FDeviceBrowserFilterEntry(FString InPlatformName, FName InPlatformLookup) : PlatformName(InPlatformName) , PlatformLookup(InPlatformLookup)`

#### class `FDeviceBrowserFilter`  
`class FDeviceBrowserFilter`  
_L33-221_
- desc: Implements a filter for the device browser's target device service list.
- L43 _public function_ `bool FilterDeviceService(const TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>& DeviceService)` — Filter the specified target device service based on the current filter settings. @param Device The service to filter. @return true if the service passed the filter, false otherwise.
- L69 _public function_ `int32 GetServiceCountPerPlatform(const FString& PlatformName) const` — Get the number of target device services that have the specified platform. @param PlatformName The name of the platform. @return The number of matching services.
- L79 _public function_ `const FText& GetDeviceSearchText() const` — Get the device search string. @return Search string.
- L89 _public function_ `const TArray<TSharedPtr<FDeviceBrowserFilterEntry>> & GetFilteredPlatforms() const` — Return the list of filtered platforms. @return List of platform names.
- L101 _public function_ `bool IsPlatformEnabled(const FString& PlatformName) const` — Check whether the specified platform is enabled in the filter. @param PlatformName The name of the platform to check. @return true if the platform is enabled, false otherwise. @see SetPlatformEnabled
- L111 _public function_ `void ResetFilter(const TArray<ITargetDeviceServicePtr>& DeviceServices)` — Populate the filter from the given list of target device proxies. @param DeviceProxies The list of device proxies to populate the filter from.
- L140 _public function_ `void SetDeviceSearchString(const FText& SearchText)` — Sets the current device search string. @param SearchText The search string.
- L157 _public function_ `void SetPlatformEnabled(const FString& PlatformName, bool Enabled)` — Set the enabled state of the specified device proxy platform. @param PlatformName The name of the platform to enable or disable in the filter. @param Enabled Whether the platform is enabled. @see IsPlatformEnabled
- L179 _public prototype_ `DECLARE_EVENT(FDeviceBrowserFilter, FOnDeviceBrowserFilterChanged);` — Get a delegate to be invoked when the filter state changed. @return The delegate. @see OnFilterReset
- L180 _public function_ `FOnDeviceBrowserFilterChanged& OnFilterChanged()`
- L191 _public prototype_ `DECLARE_EVENT(FDeviceBrowserFilter, FOnDeviceBrowserFilterReset);` — Get a delegate to be invoked when the filter has been reset. @return The delegate. @see OnFilterChanged
- L192 _public function_ `FOnDeviceBrowserFilterReset& OnFilterReset()`
- L200 _private member_ `FText DeviceSearchText;` — The device search string.
- L203 _private member_ `TArray<FString> DisabledPlatforms;` — The list of disabled platforms.
- L206 _private member_ `TMap<FString, int32> OwnerCounters;` — The device counters for owner filters.
- L209 _private member_ `TMap<FString, int32> PlatformCounters;` — The device counters for platform filters.
- L212 _private member_ `TArray<TSharedPtr<FDeviceBrowserFilterEntry>> PlatformList;` — The list of platform filters.
- L217 _private member_ `FOnDeviceBrowserFilterChanged FilterChangedEvent;` — An event delegate that is invoked when the filter state changed.
- L220 _private member_ `FOnDeviceBrowserFilterReset FilterResetEvent;` — An event delegate that is invoked when the filter has been reset.

#### Free symbols / members of external scopes

- L179 _delegate_ `DECLARE_EVENT(FDeviceBrowserFilter, FOnDeviceBrowserFilterChanged);` — Get a delegate to be invoked when the filter state changed. @return The delegate. @see OnFilterReset
- L191 _delegate_ `DECLARE_EVENT(FDeviceBrowserFilter, FOnDeviceBrowserFilterReset);` — Get a delegate to be invoked when the filter has been reset. @return The delegate. @see OnFilterChanged

### `Source/Developer/DeviceManager/Private/Models/DeviceDetailsCommands.h` (Private)


#### class `FDeviceDetailsCommands`  
`class FDeviceDetailsCommands : public TCommands<FDeviceDetailsCommands>`  
_L19-70_
- inherits: `TCommands<FDeviceDetailsCommands>`
- desc: The device details commands
- L25 _public function_ `FDeviceDetailsCommands() : TCommands<FDeviceDetailsCommands>( "DeviceDetails", NSLOCTEXT("Contexts", "DeviceDetails", "Device Details"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L37 _public function_ `virtual void RegisterCommands() override`
- L56 _public member_ `TSharedPtr<FUICommandInfo> Claim;` — ownership commands
- L57 _public member_ `TSharedPtr<FUICommandInfo> Release;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> Remove;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> Share;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> Connect;` — connectivity commands
- L63 _public member_ `TSharedPtr<FUICommandInfo> Disconnect;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> PowerOff;` — remote control commands
- L67 _public member_ `TSharedPtr<FUICommandInfo> PowerOffForce;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> PowerOn;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> Reboot;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "DeviceDetailsCommands"`

### `Source/Developer/DeviceManager/Private/Models/DeviceDetailsFeature.h` (Private)


#### struct `FDeviceDetailsFeature`  
`struct FDeviceDetailsFeature`  
_L12-30_
- desc: Implements a view model for the device feature list.
- L15 _public member_ `FString FeatureName;` — The name of the feature.
- L18 _public member_ `bool Available;` — Whether the feature is available.
- L26 _public function_ `FDeviceDetailsFeature(const FString& InFeatureName, bool InAvailable) : FeatureName(InFeatureName) , Available(InAvailable)` — Create and initialize a new instance. @param InFeatureName The name of the feature. @param InAvailable Whether the feature is available.

### `Source/Developer/DeviceManager/Private/Models/DeviceManagerModel.h` (Private)


#### class `FDeviceManagerModel`  
`class FDeviceManagerModel`  
_L16-64_
- desc: Implements a view model for the messaging debugger.
- L25 _public function_ `TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe> GetSelectedDeviceService() const` — Get the device service that is currently selected in the device browser. @return The selected device service.
- L35 _public function_ `void SelectDeviceService(const TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>& DeviceService)` — Select the specified device service (or none if nullptr). @param DeviceService The device service to select.
- L51 _public prototype_ `DECLARE_EVENT(FDeviceManagerModel, FOnSelectedDeviceServiceChanged);` — Get an event delegate that is invoked when the selected device service has changed. @return The event delegate.
- L52 _public function_ `FOnSelectedDeviceServiceChanged& OnSelectedDeviceServiceChanged()`
- L60 _private member_ `TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe> SelectedDeviceService;` — The currently selected target device service.
- L63 _private member_ `FOnSelectedDeviceServiceChanged SelectedDeviceServiceChangedEvent;` — An event delegate that is invoked when the selected message has changed.

#### Free symbols / members of external scopes

- L51 _delegate_ `DECLARE_EVENT(FDeviceManagerModel, FOnSelectedDeviceServiceChanged);` — Get an event delegate that is invoked when the selected device service has changed. @return The event delegate.

### `Source/Developer/DeviceManager/Private/Widgets/Apps/SDeviceApps.h` (Private)


#### class `SDeviceApps`  
`class SDeviceApps : public SCompoundWidget`  
_L18-51_
- inherits: `SCompoundWidget`
- desc: Implements the device details widget.
- L23 _public function_ `SLATE_BEGIN_ARGS(SDeviceApps)`
- L29 _public prototype_ `~SDeviceApps();` — Destructor.
- L39 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDeviceManagerModel>& InModel);` — Constructs the widget. @param InArgs The construction arguments. @param InModel The view model to use.
- L44 _private member_ `TArray<TSharedPtr<FString>> AppList;` — The list of applications deployed to the device.
- L47 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> AppListView;` — The application list view.
- L50 _private member_ `TSharedPtr<FDeviceManagerModel> Model;` — Pointer the device manager's view model.

### `Source/Developer/DeviceManager/Private/Widgets/Apps/SDeviceAppsAppListRow.h` (Private)


#### class `SDeviceAppsAppListRow`  
`class SDeviceAppsAppListRow : public SMultiColumnTableRow<TSharedPtr<FString>>`  
_L24-87_
- inherits: `SMultiColumnTableRow<TSharedPtr<FString>>`
- desc: Implements a row widget for the application list view.
- L29 _public function_ `SLATE_BEGIN_ARGS(SDeviceAppsAppListRow)`
- L39 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs The construction arguments.
- L52 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceAppsAppListRow"`

### `Source/Developer/DeviceManager/Private/Widgets/Browser/SDeviceBrowser.h` (Private)


#### class `SDeviceBrowser`  
`class SDeviceBrowser : public SCompoundWidget`  
_L30-90_
- inherits: `SCompoundWidget`
- desc: Implements the device browser widget.
- L35 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowser)`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDeviceManagerModel>& InModel, const TSharedRef<ITargetDeviceServiceManager>& InDeviceServiceManager, const TSharedPtr<FUICommandList>& InUICommandList);` — Constructs the widget. @param InArgs The construction arguments. @param InModel The view model to use. @param InDeviceServiceManager The target device service manager to use. @param InUICommandList The UI command list to use.
- L54 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L63 _protected prototype_ `void ReloadDeviceServiceList(bool FullyReload);` — Reloads the list of target device services. @param FullyReload Whether to fully reload the service entries, or only re-apply filtering.
- L68 _private member_ `TArray<TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>> AvailableDeviceServices;` — Holds the list of all available target device services.
- L71 _private member_ `TArray<TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>> DeviceServiceList;` — Holds the list of filtered target device services for display.
- L74 _private member_ `TSharedPtr<SListView<ITargetDeviceServicePtr>> DeviceServiceListView;` — Holds the list view for filtered target device services.
- L77 _private member_ `TSharedPtr<ITargetDeviceServiceManager> DeviceServiceManager;` — Holds a pointer to the target device service manager.
- L80 _private member_ `TSharedPtr<FDeviceBrowserFilter> Filter;` — Holds the filter model.
- L83 _private member_ `TSharedPtr<FDeviceManagerModel> Model;` — Holds a pointer the device manager's view model.
- L86 _private member_ `bool NeedsServiceListRefresh;` — Holds a flag indicating whether the list of target device services needs to be refreshed.
- L89 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Holds a pointer to the command list for controlling the device.

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeviceBrowserSelectionChanged, const ITargetDeviceServicePtr&) class SDeviceBrowser : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SDeviceBrowser) { } SLATE_END_ARGS() public: void Construct(const FArguments& InArgs, const TSharedRef<FDeviceManagerModel>& InModel, const TSharedRef<ITargetDeviceServiceManager>& InDeviceServiceManager, const TSharedPtr<FUICommandList>& InUICommandList); public:` — Delegate type for selection changes in the device browser. The first parameter is the newly selected device service (or nullptr if none was selected).

### `Source/Developer/DeviceManager/Private/Widgets/Browser/SDeviceBrowserContextMenu.h` (Private)


#### class `SDeviceBrowserContextMenu`  
`class SDeviceBrowserContextMenu : public SCompoundWidget`  
_L22-92_
- inherits: `SCompoundWidget`
- desc: Implements a context menu for the device browser list view.
- L27 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowserContextMenu)`
- L38 _public function_ `void Construct(const FArguments& InArgs, const TSharedPtr<FUICommandList>& InUICommandList)` — Construct this widget. @param InArgs The declaration data for this widget. @param InUICommandList The UI command list to use.
- L58 _protected function_ `TSharedRef<SWidget> MakeContextMenu(const TSharedPtr<FUICommandList>& CommandList)` — Build the context menu widget. @return The context menu.

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceBrowserContextMenu"`

### `Source/Developer/DeviceManager/Private/Widgets/Browser/SDeviceBrowserDeviceAdder.h` (Private)


#### class `SDeviceBrowserDeviceAdder`  
`class SDeviceBrowserDeviceAdder : public SCompoundWidget`  
_L21-63_
- inherits: `SCompoundWidget`
- desc: Implements a widget for manually locating target devices.
- L26 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowserDeviceAdder)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ITargetDeviceServiceManager>& InDeviceServiceManager);` — Construct the widget. @param InArgs The construction arguments. @param InDeviceManager The target device manager to use.
- L42 _protected prototype_ `void RefreshPlatformList();` — Refreshes the list of known platforms.
- L47 _private member_ `TSharedPtr<SButton> AddButton;` — The button for adding an unlisted device.
- L50 _private member_ `TSharedPtr<SBox> CustomPlatformWidgetPanel;` — Panel on which custom widget will be placed
- L53 _private member_ `TSharedPtr<SWidget> CustomPlatformWidget;` — Platform customizable widget
- L56 _private member_ `TSharedPtr<ITargetDeviceServiceManager> DeviceServiceManager;` — Holds a pointer to the target device service manager.
- L59 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> PlatformComboBox;` — The platforms combo box.
- L62 _private member_ `TArray<TSharedPtr<FString>> PlatformList;` — The list of known platforms.

### `Source/Developer/DeviceManager/Private/Widgets/Browser/SDeviceBrowserDeviceListRow.h` (Private)


#### class `SDeviceBrowserDeviceListRow`  
`class SDeviceBrowserDeviceListRow : public SMultiColumnTableRow<TSharedPtr<ITargetDeviceProxy>>`  
_L37-228_
- inherits: `SMultiColumnTableRow<TSharedPtr<ITargetDeviceProxy>>`
- desc: Implements a row widget for the device list view.
- L42 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowserDeviceListRow)`
- L54 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Construct the widget. @param InArgs The arguments.
- L70 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L151 _private function_ `FText HandleClaimedText() const` — Callback for getting the text in the 'Claimed' column.
- L164 _private function_ `FText HandleNameText() const` — Callback for getting the text in the 'Name' column.
- L170 _private function_ `void HandleShareCheckBoxStateChanged(ECheckBoxState NewState)` — Callback for changing this row's Share check box state.
- L176 _private function_ `ECheckBoxState HandleShareCheckBoxIsChecked() const` — Callback for getting the state of the 'Share' check box.
- L187 _private function_ `bool HandleShareCheckBoxIsEnabled() const` — Callback for getting the enabled state of the 'Share' check box.
- L193 _private function_ `FText HandleStatusTextBlockText() const` — Callback for getting the status text.
- L211 _private function_ `FSlateColor HandleTextColorAndOpacity() const` — Callback for getting the text color.
- L224 _private member_ `TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe> DeviceService;` — Holds the target device service used to populate this row.
- L227 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight text for the log message.

#### Free symbols / members of external scopes

- L31 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceBrowserDeviceListRow"`

### `Source/Developer/DeviceManager/Private/Widgets/Browser/SDeviceBrowserFilterBar.h` (Private)


#### class `SDeviceBrowserFilterBar`  
`class SDeviceBrowserFilterBar : public SCompoundWidget`  
_L20-58_
- inherits: `SCompoundWidget`
- desc: Implements the device browser filter bar widget.
- L25 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowserFilterBar)`
- L31 _public function_ `SDeviceBrowserFilterBar() : Filter(nullptr)` — Default constructor.
- L36 _public prototype_ `~SDeviceBrowserFilterBar();` — Destructor.
- L46 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FDeviceBrowserFilter> InFilter);` — Construct this widget. @param InArgs The declaration data for this widget. @param InFilter The filter model to use.
- L51 _private member_ `TSharedPtr<FDeviceBrowserFilter> Filter;` — Pointer to the filter model.
- L54 _private member_ `TSharedPtr<SSearchBox> FilterStringTextBox;` — The filter string text box.
- L57 _private member_ `TSharedPtr<SListView<TSharedPtr<FDeviceBrowserFilterEntry>>> PlatformListView;` — The platform filters list view.

### `Source/Developer/DeviceManager/Private/Widgets/Browser/SDeviceBrowserTooltip.h` (Private)


#### class `SDeviceBrowserTooltip`  
`class SDeviceBrowserTooltip : public SToolTip`  
_L20-48_
- inherits: `SToolTip`
- desc: Implements a tool tip for widget the device browser.
- L25 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowserTooltip)`
- L37 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<ITargetDeviceService, ESPMode::ThreadSafe>& InDeviceService)` — Construct the widget. @param InArgs The construction arguments. @param InDeviceServiceManager The target device service manager to use. @param InDeviceManagerState The optional device manager view state.

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceBrowserTooltip"`

### `Source/Developer/DeviceManager/Private/Widgets/Details/SDeviceDetails.h` (Private)


#### class `SDeviceDetails`  
`class SDeviceDetails : public SCompoundWidget`  
_L21-60_
- inherits: `SCompoundWidget`
- desc: Implements the device details widget.
- L26 _public function_ `SLATE_BEGIN_ARGS(SDeviceDetails)`
- L32 _public prototype_ `~SDeviceDetails();` — Destructor.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDeviceManagerModel>& InModel);` — Construct the widget. @param InArgs The construction arguments. @param InModel The view model to use.
- L47 _private member_ `TArray<TSharedPtr<FDeviceDetailsFeature>> FeatureList;` — The list of device features.
- L50 _private member_ `TSharedPtr<SListView<TSharedPtr<FDeviceDetailsFeature>> > FeatureListView;` — The device's feature list view.
- L53 _private member_ `TSharedPtr<FDeviceManagerModel> Model;` — Pointer the device manager's view model.
- L56 _private member_ `TSharedPtr<SDeviceQuickInfo> QuickInfo;` — The quick information widget.
- L59 _private member_ `TSharedPtr<SBox> CustomPlatformWidgetPanel;` — Panel on which custom widget will be placed

### `Source/Developer/DeviceManager/Private/Widgets/Details/SDeviceDetailsFeatureListRow.h` (Private)


#### class `SDeviceDetailsFeatureListRow`  
`class SDeviceDetailsFeatureListRow : public SMultiColumnTableRow<TSharedPtr<FDeviceDetailsFeature>>`  
_L24-106_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDeviceDetailsFeature>>`
- desc: Implements a row widget for the device feature list.
- L29 _public function_ `SLATE_BEGIN_ARGS(SDeviceDetailsFeatureListRow)`
- L41 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FDeviceDetailsFeature>& InFeature)` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L56 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L89 _private function_ `FSlateColor HandleTextColorAndOpacity() const` — Callback for getting the text color.
- L102 _private member_ `TSharedPtr<FDeviceDetailsFeature> Feature;` — Pointer to the device feature to be shown in this row.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceDetailsFeatureListRow"`

### `Source/Developer/DeviceManager/Private/Widgets/Processes/SDeviceProcesses.h` (Private)


#### class `SDeviceProcesses`  
`class SDeviceProcesses : public SCompoundWidget`  
_L25-94_
- inherits: `SCompoundWidget`
- desc: Implements the device details widget.
- L30 _public function_ `SLATE_BEGIN_ARGS(SDeviceProcesses)`
- L36 _public prototype_ `~SDeviceProcesses();` — Destructor.
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDeviceManagerModel>& InModel);` — Construct the widget. @param InArgs The construction arguments. @param InModel The view model to use.
- L48 _public typedef_ `typedef TMap<int64, TSharedPtr<FDeviceProcessesProcessTreeNode>> ProcessMapType;`
- L57 _protected prototype_ `void ReloadProcessList(bool FullyReload);` — Reload the list of processes. @param FullyReload true reload all entries, false to refresh the existing entries.
- L59 _protected prototype_ `void UpdateProcessTree();`
- L62 _protected prototype_ `EActiveTimerReturnType UpdateProcessList(double InCurrentTime, float InDeltaTime);` — Periodically refreshes the process list.
- L67 _private prototype_ `bool HandleProcessesBoxIsEnabled() const;` — Callback for getting the enabled state of the processes panel.
- L70 _private prototype_ `FReply HandleTerminateProcessButtonClicked();` — Callback for clicking the 'Terminate Process' button.
- L75 _private member_ `FDateTime LastProcessListRefreshTime;` — Holds the time at which the process list was last refreshed.
- L78 _private member_ `TSharedPtr<FDeviceManagerModel> Model;` — Holds a pointer the device manager's view model.
- L81 _private member_ `TArray<TSharedPtr<FDeviceProcessesProcessTreeNode>> ProcessList;` — Holds the filtered list of processes running on the device.
- L84 _private member_ `ProcessMapType ProcessMap;` — Holds the collection of process nodes.
- L87 _private member_ `TSharedPtr<STreeView<TSharedPtr<FDeviceProcessesProcessTreeNode>>> ProcessTreeView;` — Holds the application tree view.
- L90 _private member_ `TArray<FTargetDeviceProcessInfo> RunningProcesses;` — Holds the collection of processes running on the device.
- L93 _private member_ `bool ShowProcessTree;` — Holds a flag indicating whether the process list should be shown as a tree instead of a list.

### `Source/Developer/DeviceManager/Private/Widgets/Processes/SDeviceProcessesProcessListRow.h` (Private)


#### class `SDeviceProcessesProcessListRow`  
`class SDeviceProcessesProcessListRow : public SMultiColumnTableRow<TSharedPtr<FDeviceProcessesProcessTreeNode>>`  
_L29-141_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDeviceProcessesProcessTreeNode>>`
- desc: Implements a row widget for the process list view.
- L34 _public function_ `SLATE_BEGIN_ARGS(SDeviceProcessesProcessListRow)`
- L45 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Construct the widget. @param InArgs The arguments.
- L57 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L140 _private member_ `TSharedPtr<FDeviceProcessesProcessTreeNode> Node;` — The name of the process.

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceProcessesProcessListRow"`

### `Source/Developer/DeviceManager/Private/Widgets/Processes/SDeviceProcessesProcessTreeNode.h` (Private)


#### class `FDeviceProcessesProcessTreeNode`  
`class FDeviceProcessesProcessTreeNode`  
_L16-105_
- desc: Implements a node for the process tree view.
- L25 _public function_ `FDeviceProcessesProcessTreeNode(const FTargetDeviceProcessInfo& InProcessInfo) : ProcessInfo(InProcessInfo)` — Create and initializes a new instance. @param InProcessInfo The node's process information.
- L37 _public function_ `void AddChild(const TSharedPtr<FDeviceProcessesProcessTreeNode>& Child)` — Add a child process node to this node. @param The child node to add. @see ClearChildren, GetChildren
- L47 _public function_ `void ClearChildren()` — Clear the collection of child nodes. @see AddChild, GetChildren
- L58 _public function_ `const TArray<TSharedPtr<FDeviceProcessesProcessTreeNode>>& GetChildren()` — Get the child nodes. @return Child nodes. @see GetParent
- L69 _public function_ `const TSharedPtr<FDeviceProcessesProcessTreeNode>& GetParent()` — Get the parent node. @return Parent node. @see GetChildren, SetParent
- L79 _public function_ `const FTargetDeviceProcessInfo& GetProcessInfo() const` — Get the node's process information. @return The process information.
- L90 _public function_ `void SetParent(const TSharedPtr<FDeviceProcessesProcessTreeNode>& Node)` — Set the parent node. @param Node The parent node to set. @see GetParent
- L98 _private member_ `TArray<TSharedPtr<FDeviceProcessesProcessTreeNode>> Children;` — The child process nodes.
- L101 _private member_ `TSharedPtr<FDeviceProcessesProcessTreeNode> Parent;` — Pointer to the parent node.
- L104 _private member_ `FTargetDeviceProcessInfo ProcessInfo;` — The process information.

### `Source/Developer/DeviceManager/Private/Widgets/SDeviceManager.h` (Private)


#### class `SDeviceManager`  
`class SDeviceManager : public SCompoundWidget`  
_L22-145_
- inherits: `SCompoundWidget`
- desc: Implements the device manager front-end widget.
- L27 _public function_ `SLATE_BEGIN_ARGS(SDeviceManager)`
- L33 _public prototype_ `SDeviceManager();` — Default constructor.
- L45 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ITargetDeviceServiceManager>& InDeviceServiceManager, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);` — Construct the widget. @param InArgs The Slate argument list. @param InDeviceServiceManager The target device manager to use. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed.
- L52 _protected prototype_ `void BindCommands();` — Bind the device commands on our toolbar.
- L60 _protected prototype_ `static void FillWindowMenu(FMenuBuilder& MenuBuilder, const TSharedPtr<FTabManager> TabManager);` — Fill the Window menu with menu items. @param MenuBuilder The multi-box builder that should be filled with content for this pull-down menu. @param TabManager A Tab Manager from which to populate tab spawner menu items.
- L68 _protected prototype_ `bool ValidateDeviceAction(const ITargetDeviceRef& Device) const;` — Validate actions on the specified device. @param Device The device to perform an action on. @return true if actions on the device are permitted, false otherwise.
- L73 _private prototype_ `bool HandleClaimActionCanExecute();` — Callback for determining whether the 'Claim' action can execute.
- L76 _private prototype_ `void HandleClaimActionExecute();` — Callback for executing the 'Claim' action.
- L79 _private prototype_ `bool HandleConnectActionCanExecute();` — Callback for determining whether the "Connect" action can execute.
- L82 _private prototype_ `void HandleConnectActionExecute();` — Callback for executing the "Connect" action.
- L85 _private prototype_ `bool HandleDisconnectActionCanExecute();` — Callback for determining whether the "Disconnect" action can execute.
- L88 _private prototype_ `void HandleDisconnectActionExecute();` — Callback for executing the "Disconnect" action.
- L91 _private prototype_ `bool HandlePowerOffActionCanExecute();` — Callback for determining whether the 'Power Off' action can execute.
- L94 _private prototype_ `void HandlePowerOffActionExecute(bool Force);` — Callback for executing the 'Power Off' action.
- L97 _private prototype_ `bool HandlePowerOnActionCanExecute();` — Callback for determining whether the 'Power On' action can execute.
- L100 _private prototype_ `void HandlePowerOnActionExecute();` — Callback for executing the 'Power On' action.
- L103 _private prototype_ `bool HandleRebootActionCanExecute();` — Callback for determining whether the 'Reboot' action can execute.
- L106 _private prototype_ `void HandleRebootActionExecute();` — Callback for executing the 'Reboot' action.
- L109 _private prototype_ `bool HandleReleaseActionCanExecute();` — Callback for determining whether the 'Release' action can execute.
- L112 _private prototype_ `void HandleReleaseActionExecute();` — Callback for executing the 'Release' action.
- L115 _private prototype_ `bool HandleRemoveActionCanExecute();` — Callback for determining whether the 'Remove' action can execute.
- L118 _private prototype_ `void HandleRemoveActionExecute();` — Callback for executing the 'Remove' action.
- L121 _private prototype_ `bool HandleShareActionCanExecute();` — Callback for determining whether the 'Share' action can execute.
- L124 _private prototype_ `void HandleShareActionExecute();` — Callback for executing the 'Share' action.
- L127 _private prototype_ `bool HandleShareActionIsChecked();` — Callback for determining the checked state of the 'Share' action.
- L130 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);` — Callback for spawning tabs.
- L135 _private member_ `TSharedPtr<ITargetDeviceServiceManager> DeviceServiceManager;` — Holds the target device service manager.
- L138 _private member_ `TSharedRef<FDeviceManagerModel> Model;` — Holds the device manager's view model.
- L141 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L144 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — The command list for controlling the device.

### `Source/Developer/DeviceManager/Private/Widgets/Shared/SDeviceQuickInfo.h` (Private)


#### class `SDeviceQuickInfo`  
`class SDeviceQuickInfo : public SCompoundWidget`  
_L28-317_
- inherits: `SCompoundWidget`
- desc: Implements a tool tip for widget the device browser.
- L33 _public function_ `SLATE_BEGIN_ARGS(SDeviceQuickInfo)`
- L49 _public function_ `void Construct(const FArguments& InArgs)` — Construct the widget. @param InArgs The construction arguments. @param InDeviceServiceManager The target device service manager to use. @param InDeviceManagerState The optional device manager view state.
- L182 _public function_ `void SetDeviceService(const TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>& InDeviceService)` — Set the device service whose information is being shown. @param InDeviceService The device service to show.
- L190 _private function_ `FText HandleDeviceIdText() const` — Callback for getting the device's unique identifier.
- L205 _private function_ `FText HandleDeviceNameText() const` — Callback for getting the name of the shown device.
- L221 _private function_ `FText HandleIsDefaultText() const` — Callback for getting the text that indicates whether the shown device is the platform's default device.
- L239 _private function_ `FText HandleOperatingSystemText() const` — Callback for getting the make and model of the shown device.
- L260 _private function_ `const FSlateBrush* HandlePlatformIcon() const` — Callback for getting the icon of the device's platform.
- L275 _private function_ `FText HandlePlatformNameText() const` — Callback for getting the name of the device's platform.
- L291 _private function_ `FText HandleStatusText() const` — Callback for getting the status of the device.
- L316 _private member_ `TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe> DeviceService;` — The service for the device whose details are being shown.

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "SDeviceQuickInfo"`

### `Source/Developer/DeviceManager/Private/Widgets/Toolbar/SDeviceToolbar.h` (Private)


#### class `SDeviceToolbar`  
`class SDeviceToolbar : public SCompoundWidget`  
_L15-38_
- inherits: `SCompoundWidget`
- desc: Implements the device toolbar widget.
- L20 _public function_ `SLATE_BEGIN_ARGS(SDeviceToolbar)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDeviceManagerModel>& InModel, const TSharedPtr<FUICommandList>& InUICommandList);` — Constructs the widget. @param InArgs The construction arguments. @param InModel The view model to use. @param InUICommandList The UI command list to use.
- L37 _private member_ `TSharedPtr<FDeviceManagerModel> Model;` — Pointer the device manager's view model.

### `Source/Developer/DeviceManager/Public/IDeviceManagerModule.h` (Public)


#### class `IDeviceManagerModule`  
`class IDeviceManagerModule : public IModuleInterface`  
_L17-34_
- inherits: `IModuleInterface`
- desc: Interface for device manager modules.
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateDeviceManager(const TSharedRef<ITargetDeviceServiceManager>& DeviceServiceManager, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow) = 0;` — Create a device manager widget. @param DeviceServiceManager The target device manager to use. @return The new widget.
- L33 _public prototype_ `virtual ~IDeviceManagerModule() = default;` — Virtual destructor.
