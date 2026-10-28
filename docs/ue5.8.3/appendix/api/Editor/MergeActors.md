# Editor / MergeActors

- module root: `Source/Editor/MergeActors`
- headers: 14; symbols: 203
- symbol kinds: class=17, function=23, member=53, prototype=107, struct=3
- DynamicallyLoadedModuleNames: AssetRegistry, ContentBrowser, Documentation, GeometryProcessingInterfaces, MeshMergeUtilities, MeshReductionInterface, MeshUtilities
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, MaterialUtilities, Slate, SlateCore, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, ContentBrowser, Documentation, GeometryProcessingInterfaces, MeshMergeUtilities, MeshReductionInterface, MeshUtilities, PropertyEditor, WorkspaceMenuStructure

### `Source/Editor/MergeActors/Private/MergeActorsTool.h` (Private)


#### class `FMergeActorsTool`  
`class FMergeActorsTool : public IMergeActorsTool`  
_L10-40_
- inherits: `IMergeActorsTool`
- desc: Merge Actors tool base class
- L14 _public prototype_ `bool GetReplaceSourceActors() const override;` — IMergeActorsTool partial implementation
- L16 _public prototype_ `void SetReplaceSourceActors(bool bReplaceSourceActors) override;`
- L18 _public prototype_ `bool RunMergeFromSelection() override;`
- L20 _public prototype_ `bool RunMergeFromWidget() override;`
- L22 _public prototype_ `bool CanMergeFromSelection() const override;`
- L24 _public prototype_ `bool CanMergeFromWidget() const override;`
- L30 _protected prototype_ `virtual bool RunMerge(const FString& PackageName, const TArray<TSharedPtr<FMergeComponentData>>& SelectedComponents) = 0;` — Perform the tool merge operation
- L35 _protected prototype_ `virtual const TArray<TSharedPtr<FMergeComponentData>>& GetSelectedComponentsInWidget() const = 0;` — Returns the selected components from the tool's widget
- L38 _protected member_ `bool bReplaceSourceActors = false;`
- L39 _protected member_ `bool bAllowShapeComponents = true;`

### `Source/Editor/MergeActors/Private/MergeProxyUtils/SMeshProxyCommonDialog.h` (Private)


#### class `SMeshProxyCommonDialog`  
`class SMeshProxyCommonDialog : public SCompoundWidget`  
_L17-85_
- inherits: `SCompoundWidget`
- desc: SMeshProxyCommonDialog
- L20 _public function_ `SLATE_BEGIN_ARGS(SMeshProxyCommonDialog)`
- L28 _public prototype_ `SMeshProxyCommonDialog();`
- L29 _public prototype_ `~SMeshProxyCommonDialog();`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);` — SWidget functions
- L35 _public function_ `const TArray<TSharedPtr<FMergeComponentData>>& GetSelectedComponents() const` — Getter functionality
- L37 _public function_ `const int32 GetNumSelectedMeshComponents() const` — Get number of selected meshes
- L40 _public prototype_ `void Reset();` — Resets the state of the UI and flags it for refreshing
- L44 _protected prototype_ `virtual FText GetPredictedResultsTextInternal() const;` — Predicted results of the merge given the current settings
- L48 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Begin override SCompoundWidget
- L52 _private prototype_ `void CreateSettingsView();` — Creates and sets up the settings view element
- L55 _private prototype_ `TSharedRef<ITableRow> MakeComponentListItemWidget(TSharedPtr<FMergeComponentData> ComponentData, const TSharedRef<STableViewBase>& OwnerTable);` — Delegate for the creation of the list view item's widget
- L58 _private prototype_ `bool GetContentEnabledState() const;` — Delegate to determine whether or not the UI elements should be enabled (determined by number of selected actors / mesh components)
- L61 _private prototype_ `void OnLevelSelectionChanged(UObject* Obj);` — Editor delegates for map and selection changes
- L62 _private prototype_ `void OnMapChange(uint32 MapFlags);`
- L63 _private prototype_ `void OnNewCurrentLevel();`
- L64 _private prototype_ `void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L67 _private prototype_ `FText GetPredictedResultsText() const;` — Delegates for predicted results display
- L70 _private prototype_ `void UpdateSelectedStaticMeshComponents();` — Updates the selection control
- L73 _protected member_ `FComponentSelectionControl ComponentSelectionControl;`
- L76 _protected member_ `TSharedPtr<IDetailsView> SettingsView;` — Settings view ui element ptr
- L79 _protected member_ `bool bRefreshListView;` — List view state tracking data
- L82 _protected member_ `FText MergeStaticMeshComponentsLabel;` — Labels for various parts of the dialog
- L83 _protected member_ `FText SelectedComponentsListBoxToolTip;`
- L84 _protected member_ `FText DeleteUndoLabel;`

### `Source/Editor/MergeActors/Private/MergeProxyUtils/Utils.h` (Private)


#### struct `FMergeComponentData`  
`struct FMergeComponentData`  
_L12-23_
- desc: Data structure used to keep track of the selected mesh components, and whether or not they should be incorporated in the merge
- L14 _public function_ `FMergeComponentData(UPrimitiveComponent* InPrimComponent) : PrimComponent(InPrimComponent) , bShouldIncorporate(true)`
- L20 _public member_ `TWeakObjectPtr<UPrimitiveComponent> PrimComponent;` — Component extracted from selected actors
- L22 _public member_ `bool bShouldIncorporate;` — Flag determining whether or not this component should be incorporated into the merge

#### struct `FComponentSelectionControl`  
`struct FComponentSelectionControl`  
_L29-56_
- L33 _public prototype_ `TSharedRef<ITableRow> MakeComponentListItemWidget(TSharedPtr<FMergeComponentData> ComponentData, const TSharedRef<STableViewBase>& OwnerTable);` — Delegate for the creation of the list view item's widget
- L36 _public prototype_ `void UpdateSelectedCompnentsAndListBox();`
- L39 _public prototype_ `void StoreCheckBoxState();` — Stores the individual check box states for the currently selected mesh components
- L42 _public prototype_ `void UpdateSelectedStaticMeshComponents();` — Updates SelectedMeshComponent array according to retrieved mesh components from editor selection
- L45 _public member_ `TArray<TSharedPtr<FMergeComponentData>> SelectedComponents;` — List of mesh components extracted from editor selection
- L47 _public member_ `TSharedPtr<SListView<TSharedPtr<FMergeComponentData>>> ComponentsListView;` — List view ui element
- L49 _public member_ `TMap<UPrimitiveComponent*, ECheckBoxState> StoredCheckBoxStates;` — Map of keeping track of checkbox states for each selected component (used to restore state when listview is refreshed)
- L52 _public member_ `int32 NumSelectedMeshComponents = 0;` — Number of selected static mesh components
- L55 _public member_ `bool bAllowShapeComponents = true;` — Allow selection of ShapeComponents

#### Free symbols / members of external scopes

- L25 _prototype_ `void BuildMergeComponentDataFromSelection(TArray<TSharedPtr<FMergeComponentData>>& OutComponentsData, bool bAllowShapeComponents);`
- L26 _prototype_ `void BuildActorsListFromMergeComponentsData(const TArray<TSharedPtr<FMergeComponentData>>& InComponentsData, TArray<AActor*>& OutActors, TArray<ULevel*>* OutLevels = nullptr);`
- L27 _prototype_ `bool GetPackageNameForMergeAction(const FString& DefaultPackageName, FString& OutPackageName);`

### `Source/Editor/MergeActors/Private/MeshApproximationTool/MeshApproximationTool.h` (Private)


#### class `UMeshApproximationSettingsObject`  
`class UMeshApproximationSettingsObject : public UObject`  
_L15-57_
- reflection: `UCLASS(config = Engine)`
- inherits: `UObject`
- desc: Singleton wrapper to allow for using the setting structure in SSettingsView
- L19 _public function_ `UMeshApproximationSettingsObject()`
- L23 _public function_ `static UMeshApproximationSettingsObject* Get()`
- L36 _public function_ `static void Destroy()`
- L52 _protected member_ `static bool bInitialized;`
- L53 _protected member_ `static UMeshApproximationSettingsObject* DefaultSettings;`
- L56 _public member_ `FMeshApproximationSettings Settings;` — `UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties), Category = ApproximationSettings)`

#### class `FMeshApproximationTool`  
`class FMeshApproximationTool : public FMergeActorsTool`  
_L62-88_
- inherits: `FMergeActorsTool`
- desc: Mesh Proxy Tool
- L67 _public prototype_ `FMeshApproximationTool();`
- L68 _public prototype_ `~FMeshApproximationTool();`
- L71 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — IMergeActorsTool interface
- L72 _public prototype_ `virtual FName GetIconName() const override;`
- L73 _public prototype_ `virtual FText GetToolNameText() const override;`
- L74 _public prototype_ `virtual FText GetTooltipText() const override;`
- L75 _public prototype_ `virtual FString GetDefaultPackageName() const override;`
- L78 _protected prototype_ `virtual bool RunMerge(const FString& PackageName, const TArray<TSharedPtr<FMergeComponentData>>& SelectedComponents) override;`
- L79 _protected prototype_ `virtual const TArray<TSharedPtr<FMergeComponentData>>& GetSelectedComponentsInWidget() const override;`
- L84 _protected member_ `TSharedPtr<SMeshApproximationDialog> ProxyDialog;` — Pointer to the mesh merging dialog containing settings for the merge
- L87 _protected member_ `UMeshApproximationSettingsObject* SettingsObject;` — Pointer to singleton settings object

### `Source/Editor/MergeActors/Private/MeshApproximationTool/SMeshApproximationDialog.h` (Private)


#### class `SMeshApproximationDialog`  
`class SMeshApproximationDialog : public SMeshProxyCommonDialog`  
_L21-43_
- inherits: `SMeshProxyCommonDialog`
- L24 _public function_ `SLATE_BEGIN_ARGS(SMeshApproximationDialog)`
- L31 _public prototype_ `SMeshApproximationDialog();`
- L32 _public prototype_ `~SMeshApproximationDialog();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, FMeshApproximationTool* InTool);` — SWidget functions
- L39 _private member_ `FMeshApproximationTool* Tool;` — Owning mesh merging tool
- L42 _private member_ `UMeshApproximationSettingsObject* ProxySettings;` — Cached pointer to mesh merging setting singleton object

### `Source/Editor/MergeActors/Private/MeshInstancingTool/MeshInstancingTool.h` (Private)


#### class `UMeshInstancingSettingsObject`  
`class UMeshInstancingSettingsObject : public UObject`  
_L17-60_
- reflection: `UCLASS(config = Engine)`
- inherits: `UObject`
- desc: Singleton wrapper to allow for using the setting structure in SSettingsView
- L21 _public function_ `UMeshInstancingSettingsObject()`
- L25 _public function_ `static UMeshInstancingSettingsObject* Get()`
- L37 _public function_ `static void Destroy()`
- L53 _protected member_ `static bool bInitialized;`
- L55 _protected member_ `static UMeshInstancingSettingsObject* DefaultSettings;` — This is a singleton, duplicate default object
- L59 _public member_ `FMeshInstancingSettings Settings;` — `UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties), Category = MergeSettings)`

#### class `FMeshInstancingTool`  
`class FMeshInstancingTool : public FMergeActorsTool`  
_L65-94_
- inherits: `FMergeActorsTool`
- desc: Mesh Instancing Tool
- L71 _public prototype_ `FMeshInstancingTool();`
- L72 _public prototype_ `~FMeshInstancingTool();`
- L75 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — IMergeActorsTool interface
- L76 _public prototype_ `virtual FName GetIconName() const override;`
- L77 _public prototype_ `virtual FText GetToolNameText() const override;`
- L78 _public prototype_ `virtual FText GetTooltipText() const override;`
- L79 _public prototype_ `virtual FString GetDefaultPackageName() const override;`
- L82 _public prototype_ `FText GetPredictedResultsText();` — Runs the merging logic to determine predicted results
- L85 _protected prototype_ `virtual bool RunMerge(const FString& PackageName, const TArray<TSharedPtr<FMergeComponentData>>& SelectedComponents) override;`
- L86 _protected prototype_ `virtual const TArray<TSharedPtr<FMergeComponentData>>& GetSelectedComponentsInWidget() const override;`
- L90 _private member_ `TSharedPtr<SMeshInstancingDialog> InstancingDialog;` — Pointer to the mesh instancing dialog containing settings for the merge
- L93 _private member_ `UMeshInstancingSettingsObject* SettingsObject;` — Pointer to singleton settings object

### `Source/Editor/MergeActors/Private/MeshInstancingTool/SMeshInstancingDialog.h` (Private)


#### class `SMeshInstancingDialog`  
`class SMeshInstancingDialog : public SMeshProxyCommonDialog`  
_L19-46_
- inherits: `SMeshProxyCommonDialog`
- desc: SMeshInstancingDialog
- L22 _public function_ `SLATE_BEGIN_ARGS(SMeshInstancingDialog)`
- L30 _public prototype_ `SMeshInstancingDialog();`
- L31 _public prototype_ `~SMeshInstancingDialog();`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, FMeshInstancingTool* InTool);` — SWidget functions
- L38 _protected prototype_ `FText GetPredictedResultsTextInternal() const override;`
- L42 _private member_ `FMeshInstancingTool* Tool;` — Owning mesh instancing tool
- L45 _private member_ `UMeshInstancingSettingsObject* InstancingSettings;` — Cached pointer to mesh instancing setting singleton object

### `Source/Editor/MergeActors/Private/MeshMergingTool/MeshMergingTool.h` (Private)


#### class `UMeshMergingSettingsObject`  
`class UMeshMergingSettingsObject : public UObject`  
_L17-65_
- reflection: `UCLASS(config = Engine)`
- inherits: `UObject`
- desc: Singleton wrapper to allow for using the setting structure in SSettingsView
- L21 _public function_ `UMeshMergingSettingsObject()`
- L30 _public function_ `static UMeshMergingSettingsObject* Get()`
- L43 _public function_ `static void Destroy()`
- L59 _protected member_ `static UMeshMergingSettingsObject* DefaultSettings;`
- L60 _protected member_ `static bool bInitialized;`
- L64 _public member_ `FMeshMergingSettings Settings;` — `UPROPERTY(editanywhere, meta = (ShowOnlyInnerProperties), Category = MergeSettings)`

#### class `FMeshMergingTool`  
`class FMeshMergingTool : public FMergeActorsTool`  
_L70-96_
- inherits: `FMergeActorsTool`
- desc: Mesh Merging Tool
- L76 _public prototype_ `FMeshMergingTool();`
- L77 _public prototype_ `~FMeshMergingTool();`
- L80 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — IMergeActorsTool interface
- L81 _public prototype_ `virtual FName GetIconName() const override;`
- L82 _public prototype_ `virtual FText GetToolNameText() const override;`
- L83 _public prototype_ `virtual FText GetTooltipText() const override;`
- L84 _public prototype_ `virtual FString GetDefaultPackageName() const override;`
- L87 _protected prototype_ `virtual bool RunMerge(const FString& PackageName, const TArray<TSharedPtr<FMergeComponentData>>& SelectedComponents) override;`
- L88 _protected prototype_ `virtual const TArray<TSharedPtr<FMergeComponentData>>& GetSelectedComponentsInWidget() const override;`
- L92 _private member_ `TSharedPtr<SMeshMergingDialog> MergingDialog;` — Pointer to the mesh merging dialog containing settings for the merge
- L95 _private member_ `UMeshMergingSettingsObject* SettingsObject;` — Pointer to singleton settings object

### `Source/Editor/MergeActors/Private/MeshMergingTool/SMeshMergingDialog.h` (Private)


#### class `SMeshMergingDialog`  
`class SMeshMergingDialog : public SMeshProxyCommonDialog`  
_L20-43_
- inherits: `SMeshProxyCommonDialog`
- desc: SMeshMergingDialog
- L23 _public function_ `SLATE_BEGIN_ARGS(SMeshMergingDialog)`
- L31 _public prototype_ `SMeshMergingDialog();`
- L32 _public prototype_ `~SMeshMergingDialog();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, FMeshMergingTool* InTool);` — SWidget functions
- L39 _private member_ `FMeshMergingTool* Tool;` — Owning mesh merging tool
- L42 _private member_ `UMeshMergingSettingsObject* MergeSettings;` — Cached pointer to mesh merging setting singleton object

### `Source/Editor/MergeActors/Private/MeshProxyTool/MeshProxyTool.h` (Private)


#### class `UMeshProxySettingsObject`  
`class UMeshProxySettingsObject : public UObject`  
_L15-57_
- reflection: `UCLASS(config = Engine)`
- inherits: `UObject`
- desc: Singleton wrapper to allow for using the setting structure in SSettingsView
- L19 _public function_ `UMeshProxySettingsObject()`
- L23 _public function_ `static UMeshProxySettingsObject* Get()`
- L36 _public function_ `static void Destroy()`
- L52 _protected member_ `static bool bInitialized;`
- L53 _protected member_ `static UMeshProxySettingsObject* DefaultSettings;`
- L56 _public member_ `FMeshProxySettings Settings;` — `UPROPERTY(editanywhere, meta = (ShowOnlyInnerProperties), Category = ProxySettings)`

#### class `FMeshProxyTool`  
`class FMeshProxyTool : public FMergeActorsTool`  
_L62-88_
- inherits: `FMergeActorsTool`
- desc: Mesh Proxy Tool
- L67 _public prototype_ `FMeshProxyTool();`
- L68 _public prototype_ `~FMeshProxyTool();`
- L71 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;` — IMergeActorsTool interface
- L72 _public prototype_ `virtual FName GetIconName() const override;`
- L73 _public prototype_ `virtual FText GetToolNameText() const override;`
- L74 _public prototype_ `virtual FText GetTooltipText() const override;`
- L75 _public prototype_ `virtual FString GetDefaultPackageName() const override;`
- L78 _protected prototype_ `virtual bool RunMerge(const FString& PackageName, const TArray<TSharedPtr<FMergeComponentData>>& SelectedComponents) override;`
- L79 _protected prototype_ `virtual const TArray<TSharedPtr<FMergeComponentData>>& GetSelectedComponentsInWidget() const override;`
- L84 _protected member_ `TSharedPtr<SMeshProxyDialog> ProxyDialog;` — Pointer to the mesh merging dialog containing settings for the merge
- L87 _protected member_ `UMeshProxySettingsObject* SettingsObject;` — Pointer to singleton settings object

### `Source/Editor/MergeActors/Private/MeshProxyTool/SMeshProxyDialog.h` (Private)


#### class `SMeshProxyDialog`  
`class SMeshProxyDialog : public SMeshProxyCommonDialog`  
_L21-43_
- inherits: `SMeshProxyCommonDialog`
- L24 _public function_ `SLATE_BEGIN_ARGS(SMeshProxyDialog)`
- L31 _public prototype_ `SMeshProxyDialog();`
- L32 _public prototype_ `~SMeshProxyDialog();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, FMeshProxyTool* InTool);` — SWidget functions
- L39 _private member_ `FMeshProxyTool* Tool;` — Owning mesh merging tool
- L42 _private member_ `UMeshProxySettingsObject* ProxySettings;` — Cached pointer to mesh merging setting singleton object

### `Source/Editor/MergeActors/Private/SMergeActorsToolbar.h` (Private)


#### class `SMergeActorsToolbar`  
`class SMergeActorsToolbar : public SCompoundWidget`  
_L18-101_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SMergeActorsToolbar)`
- L23 _public prototype_ `SLATE_ARGUMENT(TArray<IMergeActorsTool*>, ToolsToRegister) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public function_ `SMergeActorsToolbar() : CurrentlySelectedTool(0)` — Constructor
- L39 _public prototype_ `virtual ~SMergeActorsToolbar();` — Destructor
- L42 _public prototype_ `void AddTool(IMergeActorsTool* Tool);` — Add a new tool to the toolbar
- L45 _public prototype_ `void RemoveTool(IMergeActorsTool* Tool);` — Remove an existing tool from the toolbar
- L59 _private prototype_ `TSharedRef<SWidget> MakeWidgetFromEntry(TSharedPtr<FDropDownItem> InItem);` — Called to create the combo box entries
- L62 _private prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when the level actor selection changes
- L65 _private prototype_ `void OnToolSelectionChanged(TSharedPtr<FDropDownItem> NewSelection, ESelectInfo::Type SelectInfo);` — Called when the currently selected tool changes
- L68 _private prototype_ `FReply OnMergeActorsClicked();` — Called when the Merge Actors button is clicked
- L71 _private prototype_ `bool GetContentEnabledState() const;` — Determine whether the widget content is enabled or not
- L74 _private prototype_ `void UpdateToolbar();` — Update the toolbar container based on the currently registered tools
- L77 _private prototype_ `void UpdateInlineContent();` — Updates the inline content widget for the current tool
- L82 _private member_ `TArray<IMergeActorsTool*> RegisteredTools;` — List of registered tool instances
- L85 _private member_ `int32 CurrentlySelectedTool;` — Index of currently selected tool
- L88 _private member_ `TArray<UObject*> SelectedObjects;` — List of currently selected objects
- L91 _private member_ `bool bIsContentEnabled;` — Whether the merge actors tool panel is enabled or not
- L94 _private member_ `TArray< TSharedPtr<FDropDownItem> > ToolDropDownEntries;` — List of register tool names
- L97 _private member_ `TSharedPtr<SBorder> ToolbarContainer;` — The container holding the toolbar
- L100 _private member_ `TSharedPtr<SBox> InlineContentHolder;` — Inline content area for different tool modes

#### struct `SMergeActorsToolbar::FDropDownItem`  
`struct FDropDownItem`  
_L49-56_
- L51 _public prototype_ `FDropDownItem(const FText& InName, const FName& InIconName, const FText& InDescription);`
- L53 _public member_ `FText Name;`
- L54 _public member_ `FName IconName;`
- L55 _public member_ `FText Description;`

### `Source/Editor/MergeActors/Public/IMergeActorsModule.h` (Public)


#### class `IMergeActorsModule`  
`class IMergeActorsModule : public IModuleInterface`  
_L13-40_
- inherits: `IModuleInterface`
- desc: Merge Actors module interface
- L21 _public function_ `static inline IMergeActorsModule& Get()` — Get reference to the Merge Actors module instance
- L29 _public prototype_ `virtual bool RegisterMergeActorsTool(TUniquePtr<IMergeActorsTool> Tool) = 0;` — Register an IMergeActorsTool with the module, passing ownership to it
- L34 _public prototype_ `virtual bool UnregisterMergeActorsTool(IMergeActorsTool* Tool) = 0;` — Unregister an IMergeActorsTool with the module
- L39 _public prototype_ `virtual void GetRegisteredMergeActorsTools(TArray<IMergeActorsTool*>& OutTools) = 0;` — Get currently registered list of MergeActors tools

### `Source/Editor/MergeActors/Public/IMergeActorsTool.h` (Public)


#### class `IMergeActorsTool`  
`class IMergeActorsTool`  
_L10-80_
- desc: Merge Actors tool interface
- L16 _public prototype_ `virtual ~IMergeActorsTool() = default;` — Virtual destructor
- L21 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;` — Gets the widget instance associated with this tool
- L26 _public prototype_ `virtual FName GetIconName() const = 0;` — Get the name of the icon displayed in the Merge Actors toolbar
- L31 _public prototype_ `virtual FText GetToolNameText() const = 0;` — Get tool name text to be displayed in the menus & Merge Actors toolbar
- L36 _public prototype_ `virtual FText GetTooltipText() const = 0;` — Get Tooltip text displayed in the Merge Actors toolbar
- L41 _public prototype_ `virtual FString GetDefaultPackageName() const = 0;` — Get default name for the merged asset package
- L46 _public prototype_ `virtual bool GetReplaceSourceActors() const = 0;` — Checks if the Replace Source Actors option is selected
- L53 _public prototype_ `virtual void SetReplaceSourceActors(bool bReplaceSourceActors) = 0;` — Changes the Replace Source Actors option @param whether to replace the source actors or not
- L60 _public prototype_ `virtual bool RunMergeFromSelection() = 0;` — Perform merge operation from the current selection @return true if the merge succeeded
- L65 _public prototype_ `virtual bool RunMergeFromWidget() = 0;` — Perform merge operation from the selection in the Merge Actors panel
- L72 _public prototype_ `virtual bool CanMergeFromSelection() const = 0;` — Checks if merge operation is valid from the current selection @return true if merge can be executed
- L79 _public prototype_ `virtual bool CanMergeFromWidget() const = 0;` — Checks if merge operation is valid from the current selection @return true if merge can be executed
