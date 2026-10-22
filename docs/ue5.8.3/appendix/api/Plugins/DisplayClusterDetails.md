# Plugins / DisplayClusterDetails

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails`
- headers: 12; symbols: 159
- symbol kinds: class=14, delegate=3, function=14, member=41, prototype=82, struct=4, typedef=1
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, ColorCorrectRegions, ColorGradingEditor, Core, CoreUObject, DetailCustomizations, DisplayCluster, DisplayClusterConfiguration, DisplayClusterOperator, EditorStyle, Engine, InputCore, Kismet, PropertyEditor, PropertyPath, Slate, SlateCore, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/DataModelGenerators/DisplayClusterDetailsGenerator_RootActor.h` (Private)


#### class `FDisplayClusterDetailsGenerator_Base`  
`class FDisplayClusterDetailsGenerator_Base : public IDisplayClusterDetailsDataModelGenerator`  
_L19-27_
- inherits: `IDisplayClusterDetailsDataModelGenerator`
- desc: Base generator containing helper functions for DisplayCluster data model generators
- L23 _protected prototype_ `TSharedPtr<IDetailTreeNode> FindPropertyTreeNode(const TSharedRef<IDetailTreeNode>& Node, const FCachedPropertyPath& PropertyPath);` — Recursively searches the detail tree hierarchy for a property detail tree node whose name matches the specified name
- L26 _protected prototype_ `TSharedPtr<IPropertyHandle> FindPropertyHandle(IPropertyRowGenerator& PropertyRowGenerator, const FCachedPropertyPath& PropertyPath);` — Finds a property handle in the specified property row generator whose name matches the specified name

#### class `FDisplayClusterDetailsGenerator_RootActor`  
`class FDisplayClusterDetailsGenerator_RootActor : public FDisplayClusterDetailsGenerator_Base`  
_L30-44_
- inherits: `FDisplayClusterDetailsGenerator_Base`
- desc: Details data model generator for an nDisplay root actor
- L33 _public prototype_ `static TSharedRef<IDisplayClusterDetailsDataModelGenerator> MakeInstance();`
- L36 _public prototype_ `virtual void Initialize(const TSharedRef<class FDisplayClusterDetailsDataModel>& DetailsDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L37 _public prototype_ `virtual void Destroy(const TSharedRef<class FDisplayClusterDetailsDataModel>& DetailsDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L38 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FDisplayClusterDetailsDataModel& OutDetailsDataModel) override;`
- L43 _private member_ `TArray<TWeakObjectPtr<ADisplayClusterRootActor>> RootActors;` — A list of root actors that are being represented by the data model

#### class `FDisplayClusterDetailsGenerator_ICVFXCamera`  
`class FDisplayClusterDetailsGenerator_ICVFXCamera : public FDisplayClusterDetailsGenerator_Base`  
_L47-61_
- inherits: `FDisplayClusterDetailsGenerator_Base`
- desc: Details data model generator for an nDisplay ICVFX camera component
- L50 _public prototype_ `static TSharedRef<IDisplayClusterDetailsDataModelGenerator> MakeInstance();`
- L53 _public prototype_ `virtual void Initialize(const TSharedRef<class FDisplayClusterDetailsDataModel>& InDetailsDataModel, const TSharedRef<IPropertyRowGenerator>& InPropertyRowGenerator) override;`
- L54 _public prototype_ `virtual void Destroy(const TSharedRef<class FDisplayClusterDetailsDataModel>& InDetailsDataModel, const TSharedRef<IPropertyRowGenerator>& InPropertyRowGenerator) override;`
- L55 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FDisplayClusterDetailsDataModel& OutDetailsDataModel) override;`
- L60 _private member_ `TArray<TWeakObjectPtr<UDisplayClusterICVFXCameraComponent>> CameraComponents;` — A list of camera components that are being represented by the data model

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/DisplayClusterDetailsCommands.h` (Private)


#### class `FDisplayClusterDetailsCommands`  
`class FDisplayClusterDetailsCommands : public TCommands<FDisplayClusterDetailsCommands>`  
_L11-24_
- inherits: `TCommands<FDisplayClusterDetailsCommands>`
- desc: Command list for the details drawer
- L15 _public function_ `FDisplayClusterDetailsCommands() : TCommands<FDisplayClusterDetailsCommands>(TEXT("DisplayClusterDetails"), NSLOCTEXT("Contexts", "DisplayClusterDetails", "Display Cluster Details"), NAME_None, FDisplayClusterDetailsStyle::Get().GetStyleSetName())`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> OpenDetailsDrawer;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/DisplayClusterDetailsDataModel.h` (Private)


#### class `IDisplayClusterDetailsDataModelGenerator`  
`class IDisplayClusterDetailsDataModelGenerator : public TSharedFromThis<IDisplayClusterDetailsDataModelGenerator>`  
_L14-24_
- inherits: `TSharedFromThis<IDisplayClusterDetailsDataModelGenerator>`
- desc: Interface that allows detail data models to be generated for specific UObjects
- L17 _public function_ `virtual ~IDisplayClusterDetailsDataModelGenerator()`
- L19 _public prototype_ `virtual void Initialize(const TSharedRef<class FDisplayClusterDetailsDataModel>& DetailsDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) = 0;`
- L20 _public prototype_ `virtual void Destroy(const TSharedRef<class FDisplayClusterDetailsDataModel>& DetailsDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) = 0;`
- L23 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, class FDisplayClusterDetailsDataModel& OutDetailsDataModel) = 0;` — Called when the details data model should be generated by this generator

#### class `FDisplayClusterDetailsDataModel`  
`class FDisplayClusterDetailsDataModel : public TSharedFromThis<FDisplayClusterDetailsDataModel>`  
_L31-132_
- inherits: `TSharedFromThis<FDisplayClusterDetailsDataModel>`
- desc: A data model that stores the details properties from a UObject, which determines which properties will be displayed in the details panel.
- L36 _public function_ `template<class T> static void RegisterDetailsDataModelGenerator(FGetDetailsDataModelGenerator CreateGeneratorDelegate)` — Registers a new data model generator used to populate a details data model for the specified class
- L44 _private member_ `static TMap<TWeakObjectPtr<UClass>, FGetDetailsDataModelGenerator> RegisteredDataModelGenerators;` — A list of data model generators, indexed by class name, that have been registered
- L80 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDataModelGenerated);`
- L83 _public prototype_ `FDisplayClusterDetailsDataModel();`
- L86 _public function_ `TSharedRef<IPropertyRowGenerator> GetPropertyRowGenerator() const` — Gets the property row generator that was used to generate this data model
- L89 _public prototype_ `TArray<TWeakObjectPtr<UObject>> GetObjects() const;` — Gets the list of objects from which the details properties were generated from
- L92 _public prototype_ `void SetObjects(const TArray<UObject*>& InObjects);` — Sets the objects from which the details properties will be generated
- L95 _public prototype_ `bool HasObjectOfType(const UClass* InClass) const;` — Gets whether the data model has objects of the specified class
- L98 _public prototype_ `void Reset();` — Resets the data model to be empty
- L101 _public prototype_ `void GetDrawerState(FDisplayClusterDetailsDrawerState& OutDrawerState);` — Adds the state of the data model to the specified drawer state
- L104 _public prototype_ `void SetDrawerState(const FDisplayClusterDetailsDrawerState& InDrawerState);` — Sets the state of the data model from the specified drawer state
- L107 _public function_ `FOnDataModelGenerated& OnDataModelGenerated()` — Gets the delegate that is raised when the data model is generated
- L111 _private prototype_ `void InitializeDataModelGenerator(UClass* InClass);` — Initializes any needed data model generators for the specified class
- L114 _private prototype_ `TSharedPtr<IDisplayClusterDetailsDataModelGenerator> GetDataModelGenerator(UClass* InClass) const;` — Attempts to find an instance of a data model generator that can be used for the specified class
- L117 _private prototype_ `void OnPropertyRowGeneratorRefreshed();` — Callback that is raised when the property row generator the data model is generated from has been refreshed
- L121 _public member_ `TArray<FDetailsSection> DetailsSections;` — A list of details sections in the details data model
- L125 _private member_ `TMap<TWeakObjectPtr<UClass>, TSharedPtr<IDisplayClusterDetailsDataModelGenerator>> DataModelGeneratorInstances;` — A list of data model generators that have been created to generate the data model for the current objects
- L128 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The property row generator which manages the property handles of the details objects
- L131 _private member_ `FOnDataModelGenerated OnDataModelGeneratedDelegate;` — Delegate that is raised when the data model has been generated

#### struct `FDisplayClusterDetailsDataModel::FDetailsSubsection`  
`struct FDetailsSubsection`  
_L49-59_
- desc: Stores data used to generate a details subsection, which is a selectable element in a details section that modifies which properties are displayed in the section
- L52 _public member_ `FText DisplayName;` — The display name of the subsection
- L55 _public member_ `FOnGetDetailCustomizationInstance DetailCustomizationDelegate;` — A delegate that creates the details customization for the details subsection
- L58 _public member_ `TArray<FName> Categories;` — A list of categories to display in the detail subsection

#### struct `FDisplayClusterDetailsDataModel::FDetailsSection`  
`struct FDetailsSection`  
_L62-78_
- desc: Stores data used to generate a details section in the drawer, which displays a specific subset of properties from the selected objects
- L65 _public member_ `FText DisplayName = FText::GetEmpty();` — The display name of the details section
- L68 _public member_ `TSharedPtr<IPropertyHandle> EditConditionPropertyHandle = nullptr;` — The handle of the property that controls the editing condition of the properties in the details group
- L71 _public member_ `TArray<FDetailsSubsection> Subsections;` — A list of selectable subsections to display in the details view
- L74 _public member_ `FOnGetDetailCustomizationInstance DetailCustomizationDelegate;` — A delegate that creates the details customization for the details section
- L77 _public member_ `TArray<FName> Categories;` — A list of categories to display in the detail subsection

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IDisplayClusterDetailsDataModelGenerator>, FGetDetailsDataModelGenerator);`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IDisplayClusterDetailsDataModelGenerator>, FGetDetailsDataModelGenerator);`
- L80 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDataModelGenerated);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/DisplayClusterDetailsModule.h` (Private)


#### class `FDisplayClusterDetailsModule`  
`class FDisplayClusterDetailsModule : public IDisplayClusterDetails`  
_L12-27_
- inherits: `IDisplayClusterDetails`
- desc: Module which adds the In-Camera VFX details drawer to the ICVFX panel
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual IDisplayClusterDetailsDrawerSingleton& GetDetailsDrawerSingleton() const override;`
- L26 _private member_ `TUniquePtr<FDisplayClusterDetailsDrawerSingleton> DetailsDrawerSingleton;` — The details drawer singleton, which manages the details drawer widget

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/DisplayClusterDetailsStyle.h` (Private)


#### class `FDisplayClusterDetailsStyle`  
`class FDisplayClusterDetailsStyle final : public FSlateStyleSet`  
_L14-44_
- inherits: `FSlateStyleSet`
- desc: Styleset for the nDisplay details UI elements
- L18 _public function_ `FDisplayClusterDetailsStyle() : FSlateStyleSet("DisplayClusterDetailsStyle")`
- L34 _public function_ `virtual ~FDisplayClusterDetailsStyle()`
- L39 _public function_ `static FDisplayClusterDetailsStyle& Get()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/Drawer/DisplayClusterDetailsDrawerSingleton.h` (Private)


#### class `FDisplayClusterDetailsDrawerSingleton`  
`class FDisplayClusterDetailsDrawerSingleton : public IDisplayClusterDetailsDrawerSingleton`  
_L17-70_
- inherits: `IDisplayClusterDetailsDrawerSingleton`
- desc: A singleton used to manage and store persistent state for the details drawer
- L21 _public member_ `static const FName DetailsDrawerId;` — The ID of the details drawer when registered with the nDisplay operator panel's status bar
- L24 _public member_ `static const FName DetailsDrawerTab;` — The ID of the details drawer when docked in the nDisplay operator panel's tab manager
- L27 _public prototype_ `FDisplayClusterDetailsDrawerSingleton();`
- L28 _public prototype_ `virtual ~FDisplayClusterDetailsDrawerSingleton();`
- L31 _public prototype_ `virtual void DockDetailsDrawer() override;` — Docks the details drawer in the nDisplay operator window
- L34 _public prototype_ `virtual void RefreshDetailsDrawers(bool bPreserveDrawerState) override;` — Refreshes the UI of any open details drawers
- L38 _private prototype_ `TSharedRef<SWidget> CreateDrawerContent(bool bIsInDrawer, bool bCopyStateFromActiveDrawer);` — Creates a new drawer widget to place in a drawer or in a tab
- L41 _private prototype_ `TSharedRef<SDockTab> SpawnDetailsDrawerTab(const FSpawnTabArgs& SpawnTabArgs);` — Tab spawn delegate handler used to create the drawer tab when the drawer is docked in the operator panel
- L44 _private prototype_ `void ExtendOperatorTabLayout(FLayoutExtender& InExtender);` — Tab extender delegate callback that registers the tab spawner with the operator panel's tab manager
- L47 _private prototype_ `void ExtendOperatorStatusBar(FDisplayClusterOperatorStatusBarExtender& StatusBarExtender);` — Status bar extender delegate callback that registers the drawer spawner with the operator panel's status bar
- L50 _private prototype_ `void AppendOperatorPanelCommands(TSharedRef<FUICommandList> OperatorPanelCommandList);` — Delegate callback that appends the operator panel command list to add details drawer commands
- L53 _private prototype_ `void OpenDetailsDrawer();` — Opens the details drawer
- L56 _private prototype_ `void SaveDrawerState(const TSharedPtr<SWidget>& DrawerContent);` — Delegate callback when the drawer is closed to save the drawer state
- L59 _private prototype_ `void OnActiveRootActorChanged(ADisplayClusterRootActor* NewRootActor);` — Delegate callback that is raised when the active root actor of the operator panel has changed
- L62 _private prototype_ `void OnDetailObjectsChanged(const TArray<UObject*>& NewObjects);` — Delegate callback that is raised when the list of objects displayed in the operator panel's details panel has changed
- L66 _private member_ `TWeakPtr<SDisplayClusterDetailsDrawer> DetailsDrawer;` — A weak pointer to the active details drawer that is open
- L69 _private member_ `TOptional<FDisplayClusterDetailsDrawerState> PreviousDrawerState;` — The drawer state when the last instance of the details drawer was dismissed

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/Drawer/DisplayClusterDetailsDrawerState.h` (Private)


#### struct `FDisplayClusterDetailsDrawerState`  
`struct FDisplayClusterDetailsDrawerState`  
_L9-16_
- desc: Stores the state of the drawer UI that can be reloaded in cases where the drawer or any of its elements are reloaded (such as when the drawer is reopened or docked)
- L12 _public member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — The objects that are selected in the list
- L15 _public member_ `TArray<int32> SelectedDetailsSubsections;` — Indicates which subsections were selected for each section in the details panel

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/Drawer/SDisplayClusterDetailsDrawer.h` (Private)


#### class `SDisplayClusterDetailsDrawer`  
`class SDisplayClusterDetailsDrawer : public SCompoundWidget, public FEditorUndoClient`  
_L24-123_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Details drawer widget, which displays a list of color gradable items, and the color wheel panel
- L27 _public prototype_ `~SDisplayClusterDetailsDrawer();`
- L29 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterDetailsDrawer)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bInIsInDrawer);`
- L36 _public prototype_ `void Refresh(bool bPreserveDrawerState = false);` — Refreshes the drawer's UI to match the current state of the level and active root actor, optionally preserving UI state
- L39 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L43 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L44 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L48 _public prototype_ `FDisplayClusterDetailsDrawerState GetDrawerState() const;` — Gets the state of the drawer UI
- L51 _public prototype_ `void SetDrawerState(const FDisplayClusterDetailsDrawerState& InDrawerState);` — Sets the state of the drawer UI
- L54 _public prototype_ `void SetDrawerStateToDefault();` — Sets the state of the drawer UI to its default value, which is to have the nDisplay stage actor selected
- L58 _private prototype_ `TSharedRef<SWidget> CreateDockInLayoutButton();` — Creates the button used to dock the drawer in the operator panel
- L61 _private prototype_ `void BindBlueprintCompiledDelegate(const UClass* Class);` — Binds a callback to the BlueprintCompiled delegate of the specified class
- L64 _private prototype_ `void UnbindBlueprintCompiledDelegate(const UClass* Class);` — Unbinds a callback to the BlueprintCompiled delegate of the specified class
- L67 _private prototype_ `void RefreshObjectList();` — Refreshes the object list, filling it with the current editable objects from the root actor and world
- L70 _private prototype_ `void SetDetailsDataModelObjects(const TArray<UObject*>& Objects);` — Updates the details data model with the specified list of objects
- L73 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Raised when the editor replaces any UObjects with new instantiations, usually when actors have been recompiled from blueprints
- L76 _private prototype_ `void OnLevelActorAdded(AActor* Actor);` — Raised when an actor is added to the current level
- L79 _private prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Raised when an actor has been deleted from the currnent level
- L82 _private prototype_ `void OnBlueprintCompiled(UBlueprint* Blueprint);` — Raised when the specified blueprint has been recompiled
- L85 _private prototype_ `void OnActiveRootActorChanged(ADisplayClusterRootActor* NewRootActor);` — Raised when the user has changed the active root actor selected in the nDisplay operator panel
- L88 _private prototype_ `void OnDetailsDataModelGenerated();` — Raised when the details data model has been generated
- L91 _private prototype_ `void OnListSelectionChanged(TSharedRef<SDisplayClusterDetailsObjectList> SourceList, FDisplayClusterDetailsListItemRef SelectedItem, ESelectInfo::Type SelectInfo);` — Raised when the user has selected a new item in any of the drawer's list views
- L94 _private prototype_ `FReply DockInLayout();` — Raised when the "Dock in Layout" button has been clicked
- L98 _private member_ `TSharedPtr<IDisplayClusterOperatorViewModel> OperatorViewModel;` — The operator panel's view model
- L101 _private member_ `TSharedPtr<SDisplayClusterDetailsObjectList> ObjectListView;` — List view of editable objects being displayed in the drawer's list panel
- L104 _private member_ `TArray<FDisplayClusterDetailsListItemRef> ObjectItemList;` — Source list for the details object widget
- L107 _private member_ `TSharedPtr<SDisplayClusterDetailsPanel> DetailsPanel;` — Panel containing selected object's details
- L110 _private member_ `TSharedPtr<FDisplayClusterDetailsDataModel> DetailsDataModel;` — The data model for the currently selected objects
- L113 _private member_ `bool bIsInDrawer = false;` — Gets whether this widget is in a drawer or docked in a tab
- L116 _private member_ `bool bRefreshOnNextTick = false;` — Indicates that the drawer should refresh itself on the next tick
- L119 _private member_ `bool bUpdateDataModelOnSelectionChanged = true;` — Indicates if the details data model should update when a list item selection has changed
- L122 _private member_ `FDelegateHandle ActiveRootActorChangedHandle;` — Delegate handle for the OnActiveRootActorChanged delegate

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/SDisplayClusterDetailsObjectList.h` (Private)


#### struct `FDisplayClusterDetailsListItem`  
`struct FDisplayClusterDetailsListItem`  
_L19-34_
- desc: A structure to store references to color gradable actors and components
- L22 _public member_ `TWeakObjectPtr<AActor> Actor;` — The actor that is color gradable
- L25 _public member_ `TWeakObjectPtr<UActorComponent> Component;` — The component that is color gradable
- L27 _public function_ `FDisplayClusterDetailsListItem(AActor* InActor, UActorComponent* InComponent = nullptr) : Actor(InActor) , Component(InComponent)`
- L33 _public prototype_ `bool operator<(const FDisplayClusterDetailsListItem& Other) const;` — Less than operator overload that compares list items alphabetically by their display names

#### class `SDisplayClusterDetailsObjectList`  
`class SDisplayClusterDetailsObjectList : public SCompoundWidget`  
_L39-74_
- inherits: `SCompoundWidget`
- desc: Displays a list of color gradable items
- L42 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSelectionChanged, TSharedRef<SDisplayClusterDetailsObjectList>, FDisplayClusterDetailsListItemRef, ESelectInfo::Type);`
- L45 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterDetailsObjectList)`
- L46 _public prototype_ `SLATE_ARGUMENT(const TArray<FDisplayClusterDetailsListItemRef>*, DetailsItemsSource) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L53 _public prototype_ `void RefreshList();` — Refreshes the list, updating the UI to reflect the current state of the source items list
- L56 _public prototype_ `TArray<FDisplayClusterDetailsListItemRef> GetSelectedItems();` — Gets a list of currently selected items
- L59 _public prototype_ `void SetSelectedItems(const TArray<FDisplayClusterDetailsListItemRef>& InSelectedItems);` — Selects the specified list of items
- L63 _private prototype_ `TSharedRef<ITableRow> GenerateListItemRow(FDisplayClusterDetailsListItemRef Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generates the table row widget for the specified list item
- L66 _private prototype_ `void OnSelectionChanged(FDisplayClusterDetailsListItemRef SelectedItem, ESelectInfo::Type SelectInfo);` — Raised when the internal list view's selection has changed
- L70 _private member_ `TSharedPtr<SListView<FDisplayClusterDetailsListItemRef>> ListView;` — Internal list view used to display the list of color gradable items
- L73 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;` — A delegate that is raised when the list of selected items is changed

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef TSharedPtr<FDisplayClusterDetailsListItem> FDisplayClusterDetailsListItemRef;`
- L42 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSelectionChanged, TSharedRef<SDisplayClusterDetailsObjectList>, FDisplayClusterDetailsListItemRef, ESelectInfo::Type);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Private/SDisplayClusterDetailsPanel.h` (Private)


#### class `SDisplayClusterDetailsPanel`  
`class SDisplayClusterDetailsPanel : public SCompoundWidget`  
_L15-50_
- inherits: `SCompoundWidget`
- desc: A panel that displays several property details views based on the details data model
- L19 _public member_ `static const int32 MaxNumDetailsSections = 3;` — The maximum number of details sections that are allowed to be displayed at the same time
- L22 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterDetailsPanel)`
- L23 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDisplayClusterDetailsDataModel>, DetailsDataModelSource) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void Refresh();` — Refreshes the details panel to reflect the current state of the details data model
- L32 _public prototype_ `void GetDrawerState(FDisplayClusterDetailsDrawerState& OutDrawerState);` — Adds the state of the details panel to the specified drawer state
- L35 _public prototype_ `void SetDrawerState(const FDisplayClusterDetailsDrawerState& InDrawerState);` — Sets the state of the details panel from the specified drawer state
- L39 _private prototype_ `void FillDetailsSections();` — Fills the details sections based on the current state of the details data model
- L42 _private prototype_ `EVisibility GetDetailsSectionVisibility(int32 SectionIndex) const;` — Gets the visibility state of the specified details section
- L46 _private member_ `TSharedPtr<FDisplayClusterDetailsDataModel> DetailsDataModel;` — The details data model that the panel is displaying
- L48 _private member_ `TArray<TSharedPtr<SDetailsSectionView>> DetailsSectionViews;`
- L49 _private member_ `TSharedPtr<SSplitter> Splitter;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Public/IDisplayClusterDetails.h` (Public)


#### class `IDisplayClusterDetails`  
`class IDisplayClusterDetails : public IModuleInterface`  
_L14-45_
- inherits: `IModuleInterface`
- desc: Display Cluster Details module interface
- L17 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L20 _public prototype_ `virtual ~IDisplayClusterDetails() = default;`
- L28 _public function_ `static inline IDisplayClusterDetails& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _public prototype_ `virtual IDisplayClusterDetailsDrawerSingleton& GetDetailsDrawerSingleton() const = 0;` — Gets the singleton used to manage the details drawer

### `Plugins/Runtime/nDisplay/Source/DisplayClusterDetails/Public/IDisplayClusterDetailsDrawerSingleton.h` (Public)


#### class `IDisplayClusterDetailsDrawerSingleton`  
`class IDisplayClusterDetailsDrawerSingleton`  
_L8-16_
- desc: A singleton used to manage and store persistent state for the details drawer
- L12 _public prototype_ `virtual void DockDetailsDrawer() = 0;` — Docks the details drawer in the nDisplay operator window
- L15 _public prototype_ `virtual void RefreshDetailsDrawers(bool bPreserveDrawerState) = 0;` — Refreshes the UI of any open details drawers
