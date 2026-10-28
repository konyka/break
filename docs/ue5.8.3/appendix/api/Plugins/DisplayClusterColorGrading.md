# Plugins / DisplayClusterColorGrading

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading`
- headers: 9; symbols: 101
- symbol kinds: class=11, function=10, member=17, prototype=63
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, ColorCorrectRegions, ColorGradingEditor, Core, CoreUObject, DetailCustomizations, DisplayCluster, DisplayClusterConfiguration, DisplayClusterOperator, EditorStyle, Engine, InputCore, Kismet, ObjectMixerEditor, PropertyEditor, PropertyPath, Slate, SlateCore, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/DataModelGenerators/DisplayClusterColorGradingGenerator_RootActor.h` (Private)


#### class `FDisplayClusterColorGradingGenerator_ColorGradingRenderingSettings`  
`class FDisplayClusterColorGradingGenerator_ColorGradingRenderingSettings : public IColorGradingEditorDataModelGenerator`  
_L19-33_
- inherits: `IColorGradingEditorDataModelGenerator`
- desc: Base generator for any object that needs a color grading data model generated from an FColorGradingRenderingSettings struct
- L23 _protected prototype_ `FColorGradingEditorDataModel::FColorGradingGroup CreateColorGradingGroup(const TSharedPtr<IPropertyHandle>& GroupPropertyHandle, bool bOverrideResetToDefault = false);` — Creates a new color grading group structure from the specified group property handle, which finds and connects the appropriate property handles for the color wheels and details view
- L26 _protected prototype_ `FColorGradingEditorDataModel::FColorGradingElement CreateColorGradingElement(const TSharedPtr<IPropertyHandle>& GroupPropertyHandle, FName ElementPropertyName, FText ElementLabel, bool bOverrideResetToDefault = false);` — Creates a color grading element structure from the specified property handle, whose child properties are expected to be colors with the ColorGradingMode metadata set
- L29 _protected prototype_ `TSharedPtr<IDetailTreeNode> FindPropertyTreeNode(const TSharedRef<IDetailTreeNode>& Node, const FCachedPropertyPath& PropertyPath);` — Recursively searches the detail tree hierarchy for a property detail tree node whose name matches the specified name
- L32 _protected prototype_ `TSharedPtr<IPropertyHandle> FindPropertyHandle(IPropertyRowGenerator& PropertyRowGenerator, const FCachedPropertyPath& PropertyPath);` — Finds a property handle in the specified property row generator whose name matches the specified name

#### class `FDisplayClusterColorGradingGenerator_RootActor`  
`class FDisplayClusterColorGradingGenerator_RootActor : public FDisplayClusterColorGradingGenerator_ColorGradingRenderingSettings`  
_L36-69_
- inherits: `FDisplayClusterColorGradingGenerator_ColorGradingRenderingSettings`
- desc: Color grading data model generator for an nDisplay root actor
- L39 _public prototype_ `static TSharedRef<IColorGradingEditorDataModelGenerator> MakeInstance();`
- L42 _public prototype_ `virtual void Initialize(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L43 _public prototype_ `virtual void Destroy(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L44 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FColorGradingEditorDataModel& OutColorGradingDataModel) override;`
- L49 _private prototype_ `FReply AddColorGradingGroup();` — OnClick delegate handler for the "+" button that is added to the color grading group toolbar
- L52 _private prototype_ `void DeleteColorGradingGroup(int32 GroupIndex);` — Raised when a color grading group is being deleted
- L55 _private prototype_ `void RenameColorGradingGroup(int32 GroupIndex, const FText& NewName);` — Raised when a color grading group is being renamed
- L58 _private prototype_ `TSharedRef<SWidget> CreateViewportComboBox(int32 PerViewportColorGradingIndex) const;` — Creates the combo box used to display which viewports are part of the specified color grading group
- L61 _private prototype_ `FText GetViewportComboBoxText(int32 PerViewportColorGradingIndex) const;` — Gets the display text for the viewports list combo box for the PerViewportsGroup at the specified index
- L64 _private prototype_ `TSharedRef<SWidget> GetViewportComboBoxMenu(int32 PerViewportColorGradingIndex) const;` — Generates a menu widget for the viewports list combo box for the PerViewportsGroup at the specified index
- L68 _private member_ `TArray<TWeakObjectPtr<ADisplayClusterRootActor>> RootActors;` — A list of root actors that are being represented by the data model

#### class `FDisplayClusterColorGradingGenerator_ICVFXCamera`  
`class FDisplayClusterColorGradingGenerator_ICVFXCamera : public FDisplayClusterColorGradingGenerator_ColorGradingRenderingSettings`  
_L72-105_
- inherits: `FDisplayClusterColorGradingGenerator_ColorGradingRenderingSettings`
- desc: Color grading data model generator for an nDisplay ICVFX camera component
- L75 _public prototype_ `static TSharedRef<IColorGradingEditorDataModelGenerator> MakeInstance();`
- L78 _public prototype_ `virtual void Initialize(const TSharedRef<class FColorGradingEditorDataModel>& InColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& InPropertyRowGenerator) override;`
- L79 _public prototype_ `virtual void Destroy(const TSharedRef<class FColorGradingEditorDataModel>& InColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& InPropertyRowGenerator) override;`
- L80 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FColorGradingEditorDataModel& OutColorGradingDataModel) override;`
- L85 _private prototype_ `FReply AddColorGradingGroup();` — OnClick delegate handler for the "+" button that is added to the color grading group toolbar
- L88 _private prototype_ `void DeleteColorGradingGroup(int32 GroupIndex);` — Raised when a color grading group is being deleted
- L91 _private prototype_ `void RenameColorGradingGroup(int32 GroupIndex, const FText& NewName);` — Raised when a color grading group is being renamed
- L94 _private prototype_ `TSharedRef<SWidget> CreateNodeComboBox(int32 PerNodeColorGradingIndex) const;` — Creates the combo box used to display which nodes are part of the specified color grading group
- L97 _private prototype_ `FText GetNodeComboBoxText(int32 PerNodeColorGradingIndex) const;` — Gets the display text for the nodes list combo box from the specified PerNodesGroup property handle
- L100 _private prototype_ `TSharedRef<SWidget> GetNodeComboBoxMenu(int32 PerNodeColorGradingIndex) const;` — Generates a menu widget for the nodes list combo box for the PerNodesGroup at the specified index
- L104 _private member_ `TArray<TWeakObjectPtr<UDisplayClusterICVFXCameraComponent>> CameraComponents;` — A list of camera components that are being represented by the data model

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/DisplayClusterColorGradingCommands.h` (Private)


#### class `FDisplayClusterColorGradingCommands`  
`class FDisplayClusterColorGradingCommands : public TCommands<FDisplayClusterColorGradingCommands>`  
_L11-24_
- inherits: `TCommands<FDisplayClusterColorGradingCommands>`
- desc: Command list for the color grading drawer
- L15 _public function_ `FDisplayClusterColorGradingCommands() : TCommands<FDisplayClusterColorGradingCommands>(TEXT("DisplayClusterColorGrading"), NSLOCTEXT("Contexts", "DisplayClusterColorGrading", "Display Cluster Color Grading"), NAME_None, FDisplayClusterColorGradingStyle::Get().GetStyleSetName())`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> OpenColorGradingDrawer;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/DisplayClusterColorGradingModule.h` (Private)


#### class `FDisplayClusterColorGradingModule`  
`class FDisplayClusterColorGradingModule : public IDisplayClusterColorGrading`  
_L12-27_
- inherits: `IDisplayClusterColorGrading`
- desc: Display Cluster Color Grading module
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual IDisplayClusterColorGradingDrawerSingleton& GetColorGradingDrawerSingleton() const override;`
- L26 _private member_ `TUniquePtr<FDisplayClusterColorGradingDrawerSingleton> ColorGradingDrawerSingleton;` — The color grading drawer singleton, which manages the color grading drawer widget

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/DisplayClusterColorGradingStyle.h` (Private)


#### class `FDisplayClusterColorGradingStyle`  
`class FDisplayClusterColorGradingStyle final : public FSlateStyleSet`  
_L14-46_
- inherits: `FSlateStyleSet`
- desc: Styleset for the nDisplay color grading UI elements
- L18 _public function_ `FDisplayClusterColorGradingStyle() : FSlateStyleSet("DisplayClusterColorGradingStyle")`
- L36 _public function_ `virtual ~FDisplayClusterColorGradingStyle()`
- L41 _public function_ `static FDisplayClusterColorGradingStyle& Get()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/Drawer/DisplayClusterColorGradingDrawerSingleton.h` (Private)


#### class `FDisplayClusterColorGradingDrawerSingleton`  
`class FDisplayClusterColorGradingDrawerSingleton : public IDisplayClusterColorGradingDrawerSingleton`  
_L17-70_
- inherits: `IDisplayClusterColorGradingDrawerSingleton`
- desc: A singleton used to manage and store persistent state for the color grading drawer
- L21 _public member_ `static const FName ColorGradingDrawerId;` — The ID of the color grading drawer when registered with the nDisplay operator panel's status bar
- L24 _public member_ `static const FName ColorGradingDrawerTab;` — The ID of the color grading drawer when docked in the nDisplay operator panel's tab manager
- L27 _public prototype_ `FDisplayClusterColorGradingDrawerSingleton();`
- L28 _public prototype_ `virtual ~FDisplayClusterColorGradingDrawerSingleton();`
- L31 _public prototype_ `virtual void DockColorGradingDrawer() override;` — Docks the color grading drawer in the nDisplay operator window
- L34 _public prototype_ `virtual void RefreshColorGradingDrawers() override;` — Refreshes the UI of any open color grading drawers
- L38 _private prototype_ `TSharedRef<SWidget> CreateDrawerContent(bool bIsInDrawer, bool bCopyStateFromActiveDrawer);` — Creates a new drawer widget to place in a drawer or in a tab
- L41 _private prototype_ `TSharedRef<SDockTab> SpawnColorGradingDrawerTab(const FSpawnTabArgs& SpawnTabArgs);` — Tab spawn delegate handler used to create the drawer tab when the drawer is docked in the operator panel
- L44 _private prototype_ `void ExtendOperatorTabLayout(FLayoutExtender& InExtender);` — Tab extender delegate callback that registers the tab spawner with the operator panel's tab manager
- L47 _private prototype_ `void ExtendOperatorStatusBar(FDisplayClusterOperatorStatusBarExtender& StatusBarExtender);` — Status bar extender delegate callback that registers the drawer spawner with the operator panel's status bar
- L50 _private prototype_ `void AppendOperatorPanelCommands(TSharedRef<FUICommandList> OperatorPanelCommandList);` — Delegate callback that appends the operator panel command list to add color grading drawer commands
- L53 _private prototype_ `void OpenColorGradingDrawer();` — Opens the color grading drawer
- L56 _private prototype_ `void SaveDrawerState(const TSharedPtr<SWidget>& DrawerContent);` — Delegate callback when the drawer is closed to save the drawer state
- L59 _private prototype_ `void OnActiveRootActorChanged(ADisplayClusterRootActor* NewRootActor);` — Delegate callback that is raised when the active root actor of the operator panel has changed
- L62 _private prototype_ `void OnDetailObjectsChanged(const TArray<UObject*>& NewObjects);` — Delegate callback that is raised when the list of objects displayed in the operator panel's details panel has changed
- L66 _private member_ `TWeakPtr<SDisplayClusterColorGradingDrawer> ColorGradingDrawer;` — A weak pointer to the active color grading drawer that is open
- L69 _private member_ `TOptional<FColorGradingPanelState> PreviousColorGradingPanelState;` — The color grading panel state when the last instance of the color grading drawer was dismissed

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/Drawer/SDisplayClusterColorGradingDrawer.h` (Private)


#### class `SDisplayClusterColorGradingDrawer`  
`class SDisplayClusterColorGradingDrawer : public SCompoundWidget, public FEditorUndoClient`  
_L23-82_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Color grading drawer widget, which displays a list of color gradable items, and the color wheel panel
- L26 _public prototype_ `~SDisplayClusterColorGradingDrawer();`
- L28 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterColorGradingDrawer)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bInIsInDrawer);`
- L35 _public prototype_ `void Refresh();` — Refreshes the drawer's UI to match the current state of the level and active root actor
- L38 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L39 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L43 _public prototype_ `FColorGradingPanelState GetColorGradingPanelState() const;` — Gets the state of the color grading panel UI
- L46 _public prototype_ `void SetColorGradingPanelState(const FColorGradingPanelState& InPanelState);` — Sets the state of the color grading panel UI
- L49 _public prototype_ `void SelectOperatorRootActor();` — Sets the color grading panel's selected object to the operator panel's selected root actor
- L53 _private prototype_ `FText GetCurrentLevelName() const;` — Gets the name of the current level the active root actor is in
- L56 _private prototype_ `FText GetCurrentRootActorName() const;` — Gets the name of the active root actor
- L59 _private prototype_ `void OnActiveRootActorChanged(ADisplayClusterRootActor* NewRootActor);` — Raised when the user has changed the active root actor selected in the nDisplay operator panel
- L62 _private prototype_ `UWorld* GetOperatorWorld() const;` — Get the world of the current root actor in the ICVFX panel
- L66 _private member_ `TSharedPtr<IDisplayClusterOperatorViewModel> OperatorViewModel;` — The operator panel's view model
- L69 _private member_ `TSharedPtr<SColorGradingPanel> MainPanel;` — The panel containing the color grading wheels or object details
- L72 _private member_ `bool bIsInDrawer = false;` — Gets whether this widget is in a drawer or docked in a tab
- L75 _private member_ `bool bRefreshOnNextTick = false;` — Indicates that the drawer should refresh itself on the next tick
- L78 _private member_ `bool bUpdateDataModelOnSelectionChanged = true;` — Indicates if the color grading data model should update when a list item selection has changed
- L81 _private member_ `FDelegateHandle ActiveRootActorChangedHandle;` — Delegate handle for the OnActiveRootActorChanged delegate

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Private/SelectionInterface/DisplayClusterObjectMixerSelectionInterface.h` (Private)


#### class `FDisplayClusterObjectMixerSelectionInterface`  
`class FDisplayClusterObjectMixerSelectionInterface : public IObjectMixerSelectionInterface`  
_L10-34_
- inherits: `IObjectMixerSelectionInterface`
- desc: Provides an interface for the ObjectMixer to access DisplayCluster operator panel selections
- L14 _public prototype_ `FDisplayClusterObjectMixerSelectionInterface();`
- L18 _public prototype_ `virtual void SelectActors(const TArray<AActor*>& InSelectedActors, bool bShouldSelect, bool bSelectEvenIfHidden) override;`
- L19 _public prototype_ `virtual void SelectComponents(const TArray<UActorComponent*>& InSelectedComponents, bool bShouldSelect, bool bSelectEvenIfHidden) override;`
- L20 _public function_ `virtual void SelectSubObjects(const TArray<UObject*>& InSelectedSubObjects, bool bShouldSelect, bool bSelectEvenIfHidden) override`
- L21 _public prototype_ `virtual TArray<AActor*> GetSelectedActors() const override;`
- L22 _public prototype_ `virtual TArray<UActorComponent*> GetSelectedComponents() const override;`
- L23 _public function_ `virtual TArray<UObject*> GetSelectedSubObjects() const override`
- L24 _public function_ `virtual FOnSelectionChanged& OnSelectionChanged() override`
- L28 _private prototype_ `void OnOutlinerSelectionChanged(const TArray<AActor*>& Actors);`
- L30 _private member_ `FOnSelectionChanged SelectionChanged;`
- L33 _private member_ `TArray<AActor*> SelectedActors;` — Last reported list of actors selected in the operator panel's outliner

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Public/IDisplayClusterColorGrading.h` (Public)


#### class `IDisplayClusterColorGrading`  
`class IDisplayClusterColorGrading : public IModuleInterface`  
_L14-45_
- inherits: `IModuleInterface`
- desc: Display Cluster Color Grading module interface
- L17 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L20 _public prototype_ `virtual ~IDisplayClusterColorGrading() = default;`
- L28 _public function_ `static inline IDisplayClusterColorGrading& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _public prototype_ `virtual IDisplayClusterColorGradingDrawerSingleton& GetColorGradingDrawerSingleton() const = 0;` — Gets the singleton used to manage the color grading drawer

### `Plugins/Runtime/nDisplay/Source/DisplayClusterColorGrading/Public/IDisplayClusterColorGradingDrawerSingleton.h` (Public)


#### class `IDisplayClusterColorGradingDrawerSingleton`  
`class IDisplayClusterColorGradingDrawerSingleton`  
_L8-16_
- desc: A singleton used to manage and store persistent state for the color grading drawer
- L12 _public prototype_ `virtual void DockColorGradingDrawer() = 0;` — Docks the color grading drawer in the nDisplay operator window
- L15 _public prototype_ `virtual void RefreshColorGradingDrawers() = 0;` — Refreshes the UI of any open color grading drawers
