# Plugins / DisplayClusterOperator

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator`
- headers: 11; symbols: 200
- symbol kinds: class=11, delegate=9, function=23, member=46, prototype=111
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayCluster, EditorStyle, Engine, InputCore, Kismet, Projects, Slate, SlateCore, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/DisplayClusterOperatorModule.h` (Private)


#### class `FDisplayClusterOperatorModule`  
`class FDisplayClusterOperatorModule : public IDisplayClusterOperator`  
_L15-73_
- inherits: `IDisplayClusterOperator`
- desc: Display Cluster editor module
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAppUnregistered, const FDelegateHandle&) static const FName OperatorPanelTabName;`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `virtual FDelegateHandle RegisterApp(const FOnGetAppInstance& InGetAppInstanceDelegate) override;`
- L32 _public prototype_ `virtual void UnregisterApp(const FDelegateHandle& InHandle) override;`
- L33 _public prototype_ `virtual TSharedRef<IDisplayClusterOperatorViewModel> GetOperatorViewModel() override;`
- L34 _public function_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() override`
- L35 _public function_ `virtual FOnRegisterStatusBarExtensions& OnRegisterStatusBarExtensions() override`
- L36 _public function_ `virtual FOnAppendOperatorPanelCommands& OnAppendOperatorPanelCommands() override`
- L38 _public prototype_ `virtual FName GetPrimaryOperatorExtensionId() override;`
- L39 _public prototype_ `virtual FName GetAuxilliaryOperatorExtensionId() override;`
- L40 _public prototype_ `virtual FName GetDetailsTabId() override;`
- L41 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetOperatorToolBarExtensibilityManager() override`
- L42 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetOperatorMenuExtensibilityManager() override`
- L43 _public prototype_ `virtual void GetRootActorLevelInstances(TArray<ADisplayClusterRootActor*>& OutRootActorInstances) override;`
- L44 _public prototype_ `virtual void ToggleDrawer(const FName DrawerId) override;`
- L45 _public prototype_ `virtual void ForceDismissDrawers() override;`
- L49 _public function_ `const TMap<FDelegateHandle, FOnGetAppInstance>& GetRegisteredApps() const` — Retrieve currently registered app delegates
- L52 _public function_ `FOnAppUnregistered& OnAppUnregistered()` — Broadcast when an app is unregistered
- L55 _private prototype_ `void RegisterTabSpawners();`
- L56 _private prototype_ `void UnregisterTabSpawners();`
- L58 _private prototype_ `TSharedRef<SDockTab> SpawnOperatorPanelTab(const FSpawnTabArgs& SpawnTabArgs);`
- L59 _private prototype_ `void OnOperatorPanelTabClosed(TSharedRef<SDockTab> Tab);`
- L62 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`
- L63 _private member_ `FOnRegisterStatusBarExtensions RegisterStatusBarExtensions;`
- L64 _private member_ `FOnAppendOperatorPanelCommands AppendOperatorPanelCommands;`
- L66 _private member_ `TWeakPtr<SDisplayClusterOperatorPanel> ActiveOperatorPanel;`
- L67 _private member_ `TSharedPtr<FDisplayClusterOperatorViewModel> OperatorViewModel;`
- L68 _private member_ `TSharedPtr<FExtensibilityManager> OperatorToolBarExtensibilityManager;`
- L69 _private member_ `TSharedPtr<FExtensibilityManager> OperatorMenuExtensibilityManager;`
- L71 _private member_ `TMap<FDelegateHandle, FOnGetAppInstance> RegisteredApps;`
- L72 _private member_ `FOnAppUnregistered AppUnregisteredEvent;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAppUnregistered, const FDelegateHandle&) static const FName OperatorPanelTabName;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/DisplayClusterOperatorStyle.h` (Private)


#### class `FDisplayClusterOperatorStyle`  
`class FDisplayClusterOperatorStyle : public FSlateStyleSet`  
_L7-22_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FDisplayClusterOperatorStyle();`
- L11 _public prototype_ `~FDisplayClusterOperatorStyle();`
- L13 _public function_ `static FDisplayClusterOperatorStyle& Get()`
- L20 _private prototype_ `void Initialize();`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/DisplayClusterOperatorViewModel.h` (Private)


#### class `FDisplayClusterOperatorViewModel`  
`class FDisplayClusterOperatorViewModel : public TSharedFromThis<FDisplayClusterOperatorViewModel>, public IDisplayClusterOperatorViewModel`  
_L13-48_
- inherits: `TSharedFromThis<FDisplayClusterOperatorViewModel>,IDisplayClusterOperatorViewModel`
- desc: A view model object that stores any state from the operator panel that should be exposed externally
- L16 _public prototype_ `virtual ~FDisplayClusterOperatorViewModel() = default;`
- L19 _public function_ `virtual bool HasRootActor(bool bEvenIfPendingKill = false) const override`
- L20 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor(bool bEvenIfPendingKill = false) const override;`
- L21 _public prototype_ `virtual void SetRootActor(ADisplayClusterRootActor* InRootActor) override;`
- L22 _public function_ `virtual FOnActiveRootActorChanged& OnActiveRootActorChanged() override`
- L23 _public function_ `virtual const TArray<TWeakObjectPtr<UObject>> GetDetailObjects() override`
- L24 _public prototype_ `virtual void ShowDetailsForObject(UObject* Object) override;`
- L25 _public prototype_ `virtual void ShowDetailsForObjects(const TArray<UObject*>& Objects) override;`
- L26 _public prototype_ `virtual void SelectActors(const TArray<AActor*>& Actors, bool bShouldSelect) override;`
- L27 _public function_ `virtual FOnDetailObjectsChanged& OnDetailObjectsChanged() override`
- L28 _public function_ `virtual FOnOutlinerSelectionChanged& OnOutlinerSelectionChanged() override`
- L29 _public function_ `virtual FOnActorsSelected& OnActorsSelectedExternally() override`
- L30 _public function_ `virtual TSharedPtr<FTabManager> GetTabManager() const override`
- L32 _public function_ `virtual TSharedPtr<FWorkspaceItem> GetWorkspaceMenuGroup() const override`
- L35 _public prototype_ `TSharedRef<FTabManager> CreateTabManager(const TSharedRef<SDockTab>& MajorTabOwner);`
- L36 _public prototype_ `void ResetTabManager();`
- L39 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActor;`
- L40 _private member_ `TArray<TWeakObjectPtr<UObject>> DetailObjects;`
- L41 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L42 _private member_ `TSharedPtr<FWorkspaceItem> WorkspaceItem;`
- L44 _private member_ `FOnActiveRootActorChanged RootActorChanged;`
- L45 _private member_ `FOnDetailObjectsChanged DetailObjectsChanged;`
- L46 _private member_ `FOnActorsSelected ActorsSelectedExternally;`
- L47 _private member_ `FOnOutlinerSelectionChanged OutlinerSelectionChanged;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/SDisplayClusterOperatorPanel.h` (Private)


#### class `SDisplayClusterOperatorPanel`  
`class SDisplayClusterOperatorPanel : public SCompoundWidget`  
_L22-101_
- inherits: `SCompoundWidget`
- desc: The nDisplay operator panel that allows users to edit root actor instances with a variety of tools
- L26 _public member_ `static const FName DetailsTabId;` — The tab ID that the details panel lives in
- L29 _public member_ `static const FName RootActorPanelId;` — The tab ID that the root actor properties panel lives in
- L32 _public member_ `static const FName PrimaryTabExtensionId;` — The ID of the main tab stack that can be extended by external tabs
- L35 _public member_ `static const FName AuxilliaryTabExtensionId;` — The ID of the auxilliary tab stack that can be extended by external tabs; intended for lower-thirds windows like log outputs
- L38 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterOperatorPanel)`
- L41 _public prototype_ `~SDisplayClusterOperatorPanel();`
- L43 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FTabManager>& InTabManager, const TSharedPtr<SWindow>& WindowOwner);`
- L46 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L50 _public prototype_ `void ToggleDrawer(const FName DrawerId);` — Toggles the state of a drawer with the specified ID, closing the drawer if it is open, and opening the drawer if it is closed
- L53 _public prototype_ `void ForceDismissDrawers();` — Forces the operator panel to dismiss any open drawers
- L57 _private prototype_ `void BindCommands();` — Binds any commands to the operator panel's command list, as well as allowing any external modules to register their own commands
- L60 _private prototype_ `TSharedRef<SDockTab> SpawnDetailsTab(const FSpawnTabArgs& Args);` — Creates a tab with the details panel in it
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnRootActorPanelTab(const FSpawnTabArgs& Args);` — Creates a tab with the root actor properties panel in it
- L66 _private prototype_ `void DisplayObjectsInDetailsPanel(const TArray<UObject*>& Objects);` — Raised when something wants to display a list of objects in the operator's details panel
- L69 _private prototype_ `void OnOperatorAppUnregistered(const FDelegateHandle& InHandle);` — Called when app is unregistered
- L73 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the operator's tabs.
- L76 _private member_ `TSharedPtr<FLayoutExtender> LayoutExtender;` — The layout extender used by the operator's layout
- L79 _private member_ `TSharedPtr<SBox> ToolbarContainer;` — The container for the toolbar
- L82 _private member_ `TSharedPtr<SDisplayClusterOperatorToolbar> Toolbar;` — A reference to the operator panel's toolbar widget
- L85 _private member_ `TSharedPtr<class SKismetInspector> DetailsView;` — A reference to the operator panel's details view
- L88 _private member_ `TSharedPtr<SDisplayClusterOperatorRootActorPanel> RootActorPanel;` — A reference to the operator panel's root actor panel
- L91 _private member_ `TSharedPtr<SDisplayClusterOperatorStatusBar> StatusBar;` — A reference to the operator panel's status bar widget
- L94 _private member_ `TSharedPtr<FUICommandList> CommandList;` — A command list for processing commands for the window
- L97 _private member_ `FDelegateHandle DetailObjectsChangedHandle;` — The delegate handle for the operator module's OnDetailObjectsChanged event
- L100 _private member_ `TMap<FDelegateHandle, TSharedRef<IDisplayClusterOperatorApp>> AppInstances;` — Loaded app instances

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/SDisplayClusterOperatorRootActorPanel.h` (Private)


#### class `SDisplayClusterOperatorRootActorPanel`  
`class SDisplayClusterOperatorRootActorPanel : public SCompoundWidget, public FEditorUndoClient`  
_L22-92_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A panel that mimics the appearance of SActorDetails to display the root actor's components and properties in the operator panel
- L27 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterOperatorRootActorPanel)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTabManager> InTabManager, const FName& TabIdentifier);`
- L34 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L35 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L39 _private prototype_ `UObject* GetRootActorContextObject() const;` — Gets the root actor displayed by the subobject editor and the details panel
- L42 _private prototype_ `EVisibility GetSubobjectEditorVisibility() const;` — Gets the visibility of the subobject editor
- L45 _private prototype_ `bool CanEditRootActorComponents() const;` — Gets whether the root actor's components can be edited
- L48 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;` — Determines if a property is visible or not
- L51 _private prototype_ `bool IsPropertyReadOnly(const FPropertyAndParent& PropertyAndParent) const;` — Determines if a property is read only or not
- L54 _private prototype_ `bool IsPropertyEditingEnabled() const;` — Determines if property editing is enabled or not
- L57 _private prototype_ `bool IsBlueprintNotEditable(const UActorComponent* Component) const;` — Determines if the component is set as not editable through its blueprint
- L60 _private prototype_ `EVisibility GetUCSComponentWarningVisibility() const;` — Gets the visibility of the warning label for user compile script generated components
- L63 _private prototype_ `EVisibility GetInheritedComponentWarningVisibility() const;` — Gets the visibility of the warning label for inherited blueprint components
- L66 _private prototype_ `EVisibility GetNativeComponentWarningVisibility() const;` — Gets the visibility of the warning label for native components
- L69 _private prototype_ `void OnComponentBlueprintHyperlinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata);` — Raised when a hyperlink is clicked in the warning labels for components
- L72 _private prototype_ `void OnRootActorChanged(ADisplayClusterRootActor* RootActor);` — Raised when the operator panel's active root actor has been changed
- L75 _private prototype_ `void OnSelectedSubobjectsChanged(const TArray<TSharedPtr<FSubobjectEditorTreeNode>>& SelectedNodes);` — Raised when the selection in the subobject editor is changed
- L78 _private prototype_ `void OnComponentsEdited();` — Raised by the level editor when any components in the world have been edited
- L81 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementObjects);` — Raised when any objects in the editor are being destroyed and replaced with new instances
- L85 _private member_ `TSharedPtr<SSubobjectEditor> SubobjectEditor;` — Subobject editor used to display the components of the root actor
- L88 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Details view widget used to display the actor's properties
- L91 _private member_ `TSharedPtr<IDisplayClusterOperatorViewModel> OperatorViewModel;` — A reference to the operator panel's view model

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/SDisplayClusterOperatorStatusBar.h` (Private)


#### class `SDisplayClusterOperatorStatusBar`  
`class SDisplayClusterOperatorStatusBar : public SCompoundWidget`  
_L12-47_
- inherits: `SCompoundWidget`
- L15 _public member_ `static const FName StatusBarId;`
- L18 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterOperatorStatusBar)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L29 _public prototype_ `void RegisterDrawer(FWidgetDrawerConfig&& Drawer, int32 SlotIndex = INDEX_NONE);` — Registers a new drawer with this status bar. Registering will add a button to open and close the drawer
- L32 _public prototype_ `bool IsDrawerOpened(const FName DrawerId) const;` — Gets whether a drawer with the specified ID is currently open
- L35 _public prototype_ `void OpenDrawer(const FName DrawerId);` — Opens a drawer with the specified ID
- L43 _public prototype_ `bool DismissDrawer(const TSharedPtr<SWidget>& NewlyFocusedWidget);` — Dismisses an open drawer with an animation.  The drawer contents are removed once the animation is complete @param NewlyFocusedWidget Optional widget to focus @return true if any open drawer was dismissed
- L46 _private member_ `TSharedPtr<SWidgetDrawer> WidgetDrawer;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Private/SDisplayClusterOperatorToolbar.h` (Private)


#### class `SDisplayClusterOperatorToolbar`  
`class SDisplayClusterOperatorToolbar : public SCompoundWidget`  
_L20-95_
- inherits: `SCompoundWidget`
- desc: A toolbar widget used by the nDisplay operator panel
- L23 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterOperatorToolbar)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() ~SDisplayClusterOperatorToolbar();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L39 _private prototype_ `TSharedPtr<FString> FillRootActorList(const FString& InitiallySelectedRootActor = TEXT(""));` — Constructs the list of root actors that exist on the current level to use for the root actor picker dropdown. @param InitiallySelectedRootActor - The actor name of the root actor that should be initially selected in the combo box @eturns The pointer to the item in the root actor list to pass to the combo box as the initially selected item
- L42 _private prototype_ `void ClearSelectedRootActor();` — Deselect and clear the current root actor
- L45 _private prototype_ `void OnRootActorChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);` — Raised when the user selects a new root actor from the root actor picker dropdown
- L48 _private prototype_ `void OnBlueprintCompiled(UBlueprint* Blueprint);` — When the root actor blueprint has been compiled
- L51 _private prototype_ `void OnRootActorComboBoxOpening();` — Raised when the root actor picker dropdown is being opened
- L54 _private prototype_ `TSharedRef<SWidget> GenerateRootActorComboBoxWidget(TSharedPtr<FString> InItem) const;` — Creates the widget to display for the specified dropdown item
- L57 _private prototype_ `FText GetRootActorComboBoxText() const;` — Gets the text to display in the combo box for the selected root actor
- L60 _private prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Raised when the user deletes an actor from the level
- L63 _private prototype_ `void HandleMapChanged(UWorld* InWorld, EMapChangeType InMapChangeType);` — When the map changes
- L66 _private prototype_ `void OnPrepareToCleanseEditorObject(UObject* Object);` — Raised when an editor object is going to be cleansed, usually used when a sublevel is about to be removed
- L69 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);` — Raised when any object is transacted
- L73 _private member_ `TSharedPtr<IDisplayClusterOperatorViewModel> ViewModel;` — A reference the the operator panel's view model, which stores the operator panel state
- L76 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list used by the toolbar
- L79 _private member_ `TArray<TSharedPtr<FString>> RootActorList;` — The list of root actor names on the current level to display in the root actor picker dropdown
- L82 _private member_ `TSharedPtr<FString> ActiveRootActorName;` — The name or label of the active actor
- L85 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> RootActorComboBox;` — The combo box widget that allows the uesr to pick the active root actor from
- L88 _private member_ `FDelegateHandle LevelActorDeletedHandle;` — The OnLevelActorDeleted delegate handle
- L91 _private member_ `FDelegateHandle MapChangedHandle;` — The handle to OnMapChanged
- L94 _private member_ `FDelegateHandle OnObjectTransactedHandle;` — Delegate handle for when an object is transacted

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Public/DisplayClusterOperatorStatusBarExtender.h` (Public)


#### class `FDisplayClusterOperatorStatusBarExtender`  
`class FDisplayClusterOperatorStatusBarExtender`  
_L11-27_
- desc: An extender that can be passed to external modules to allow them to extend the operator panel's status bar
- L20 _public prototype_ `void AddWidgetDrawer(const FWidgetDrawerConfig& InWidgetDrawerConfig, int32 SlotIndex = INDEX_NONE);` — Adds a new widget drawer to the status bar @param InWidgetDrawerConfig - The widget drawer config to create the widget drawer from @param SlotIndex - An optional slot index of the widget drawer to add, which determines where the button for the widget drawer is placed on the status bar
- L23 _public prototype_ `void RegisterExtensions(TSharedRef<SDisplayClusterOperatorStatusBar> StatusBar);` — Registers any status bar extensions with the specified status bar
- L26 _private member_ `TArray<TPair<int32, FWidgetDrawerConfig>> WidgetDrawers;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Public/IDisplayClusterOperator.h` (Public)


#### class `IDisplayClusterOperator`  
`class IDisplayClusterOperator : public IModuleInterface`  
_L21-96_
- inherits: `IModuleInterface`
- desc: Display Cluster Operator module interface
- L24 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L26 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L27 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterStatusBarExtensions, FDisplayClusterOperatorStatusBarExtender&);`
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAppendOperatorPanelCommands, TSharedRef<FUICommandList>) DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IDisplayClusterOperatorApp>, FOnGetAppInstance, TSharedRef<IDisplayClusterOperatorViewModel>);`
- L32 _public prototype_ `virtual ~IDisplayClusterOperator() = default;`
- L40 _public function_ `static inline IDisplayClusterOperator& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L50 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L56 _public prototype_ `virtual FDelegateHandle RegisterApp(const FOnGetAppInstance& InGetAppInstanceDelegate) = 0;` — Register an app with the operator panel
- L59 _public prototype_ `virtual void UnregisterApp(const FDelegateHandle& InHandle) = 0;` — Unregisters an app from the operator panel
- L62 _public prototype_ `virtual TSharedRef<IDisplayClusterOperatorViewModel> GetOperatorViewModel() = 0;` — Gets the operator panel's view model, which stores any state used by the operator panel
- L65 _public prototype_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() = 0;` — Gets the event handler that is raised when the operator panel processes extensions to its layout
- L68 _public prototype_ `virtual FOnRegisterStatusBarExtensions& OnRegisterStatusBarExtensions() = 0;` — Gets the event handler that is raised when the operator panel processes extensions to its status bar
- L71 _public prototype_ `virtual FOnAppendOperatorPanelCommands& OnAppendOperatorPanelCommands() = 0;` — Gets the event handler that is raised when the operator panel binds commands to its command list
- L74 _public prototype_ `virtual FName GetPrimaryOperatorExtensionId() = 0;` — Gets the extension ID for the main window region that can be used to add tabs to the operator panel
- L77 _public prototype_ `virtual FName GetAuxilliaryOperatorExtensionId() = 0;` — Gets the extension ID for the auxilliary window region intended for lower-thirds windows (e.g log output) that can be used to add tabs to the operator panel
- L80 _public prototype_ `virtual FName GetDetailsTabId() = 0;` — Gets the tab ID used for the details panel
- L83 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetOperatorToolBarExtensibilityManager() = 0;` — Gets the extensibility manager for the operator panel's toolbar
- L86 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetOperatorMenuExtensibilityManager() = 0;` — Gets the extensibility manager for the operator panel's menu bar
- L89 _public prototype_ `virtual void GetRootActorLevelInstances(TArray<ADisplayClusterRootActor*>& OutRootActorInstances) = 0;` — Gets a list of all nDisplay root actor instances that are on the currently loaded level
- L92 _public prototype_ `virtual void ToggleDrawer(const FName DrawerId) = 0;` — Toggles the state of a drawer with the specified ID, closing the drawer if it is open, and opening the drawer if it is closed
- L95 _public prototype_ `virtual void ForceDismissDrawers() = 0;` — Forces the operator panel to dismiss any open drawers

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterStatusBarExtensions, FDisplayClusterOperatorStatusBarExtender&);`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAppendOperatorPanelCommands, TSharedRef<FUICommandList>) DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IDisplayClusterOperatorApp>, FOnGetAppInstance, TSharedRef<IDisplayClusterOperatorViewModel>);`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IDisplayClusterOperatorApp>, FOnGetAppInstance, TSharedRef<IDisplayClusterOperatorViewModel>);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Public/IDisplayClusterOperatorApp.h` (Public)


#### class `IDisplayClusterOperatorApp`  
`class IDisplayClusterOperatorApp : public TSharedFromThis<IDisplayClusterOperatorApp>`  
_L7-11_
- inherits: `TSharedFromThis<IDisplayClusterOperatorApp>`
- L10 _public prototype_ `virtual ~IDisplayClusterOperatorApp() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterOperator/Public/IDisplayClusterOperatorViewModel.h` (Public)


#### class `IDisplayClusterOperatorViewModel`  
`class IDisplayClusterOperatorViewModel`  
_L14-61_
- desc: Interface for a view model object that stores any state from the operator panel that should be exposed externally
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveRootActorChanged, ADisplayClusterRootActor*);`
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDetailObjectsChanged, const TArray<UObject*>&);`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutlinerSelectionChanged, const TArray<AActor*>&);`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActorsSelected, const TArray<AActor*>&, bool bShouldSelect);`
- L24 _public prototype_ `virtual bool HasRootActor(bool bEvenIfPendingKill = false) const = 0;` — Gets whether the view model has been populated with a valid root actor
- L27 _public prototype_ `virtual ADisplayClusterRootActor* GetRootActor(bool bEvenIfPendingKill = false) const = 0;` — Gets the root actor that is actively being edited by the operator panel
- L30 _public prototype_ `virtual void SetRootActor(ADisplayClusterRootActor* InRootActor) = 0;` — Sets the root actor that is actively being edited by the operator panel
- L33 _public prototype_ `virtual FOnActiveRootActorChanged& OnActiveRootActorChanged() = 0;` — Gets the event handler that is raised when the operator panel changes the root actor being operated on
- L36 _public prototype_ `virtual const TArray<TWeakObjectPtr<UObject>> GetDetailObjects() = 0;` — Gets the list of objects being displayed in the operator's details panel
- L39 _public prototype_ `virtual void ShowDetailsForObject(UObject* Object) = 0;` — Displays the properties of the specified object in the operator's details panel
- L42 _public prototype_ `virtual void ShowDetailsForObjects(const TArray<UObject*>& Objects) = 0;` — Displays the properties of the specified object in the operator's details panel
- L45 _public prototype_ `virtual void SelectActors(const TArray<AActor*>& Actors, bool bShouldSelect) = 0;` — Selects the specified actors in the operator's outliner panel, or if bShouldSelect is false, deselects them
- L48 _public prototype_ `virtual FOnDetailObjectsChanged& OnDetailObjectsChanged() = 0;` — Gets the event handler that is raised when the objects being displayed in the operator's details panel are changed
- L51 _public prototype_ `virtual FOnOutlinerSelectionChanged& OnOutlinerSelectionChanged() = 0;` — Gets the event handler that is raised when the actors selected in the operator's outliner panel are changed
- L54 _public prototype_ `virtual FOnActorsSelected& OnActorsSelectedExternally() = 0;` — Gets the event handler that is raised when actors are selected from outside the operator itself, i.e. directly from this view model
- L57 _public prototype_ `virtual TSharedPtr<FTabManager> GetTabManager() const = 0;` — Gets the tab manager of the active operator panel, if there is an open operator panel
- L60 _public prototype_ `virtual TSharedPtr<FWorkspaceItem> GetWorkspaceMenuGroup() const = 0;` — Gets the registered workspace menu group

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveRootActorChanged, ADisplayClusterRootActor*);`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDetailObjectsChanged, const TArray<UObject*>&);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutlinerSelectionChanged, const TArray<AActor*>&);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActorsSelected, const TArray<AActor*>&, bool bShouldSelect);`
