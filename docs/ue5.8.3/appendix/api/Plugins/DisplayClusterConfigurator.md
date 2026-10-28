# Plugins / DisplayClusterConfigurator

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator`
- headers: 128; symbols: 2606
- symbol kinds: class=150, delegate=21, enum=10, enumerator=35, externvar=1, function=304, macro=8, member=620, namespace=7, prototype=1394, struct=30, typedef=20, variable=6
- PrivateDependencyModuleNames: AdvancedPreviewScene, AppFramework, ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, CinematicCamera, ClassViewer, ColorGradingEditor, Core, CoreUObject, DesktopPlatform, DisplayCluster, DisplayClusterConfiguration, DisplayClusterModularFeaturesEditor, DisplayClusterProjection, DisplayClusterWarp, EditorFramework, EditorSubsystem, EditorWidgets, Engine, EngineAssetDefinitions, GraphEditor, ImageWrapper, InputCore, Kismet, KismetCompiler, MainFrame, MediaAssets, MediaIOCore, MessageLog, Networking, PinnedCommandList, ProceduralMeshComponent, Projects, PropertyEditor, Serialization, Settings, Slate, SlateCore, StructUtilsEditor, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/AssetDefinition/AssetDefinition_DisplayClusterBlueprint.h` (Private)


#### class `UAssetDefinition_DisplayClusterBlueprint`  
`class UAssetDefinition_DisplayClusterBlueprint : public UAssetDefinition_Blueprint`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public function_ `virtual bool CanImport() const override`
- L20 _public prototype_ `virtual EAssetCommandResult GetSourceFiles(const FAssetSourceFilesArgs& InArgs, TFunctionRef<bool(const FAssetSourceFilesResult& InSourceFile)> SourceFileFunc) const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/ClusterConfiguration/DisplayClusterConfiguratorClusterEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L20 _macro_ `#define NDISPLAY_DEFAULT_CLUSTER_HOST "127.0.0.1"`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DisplayClusterConfiguratorClusterEditorUtils` (scope `UE`)
- L33 _prototype_ `UDisplayClusterConfigurationClusterNode* CreateNewClusterNodeFromDialog(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& Toolkit, UDisplayClusterConfigurationCluster* Cluster, const FDisplayClusterConfigurationRectangle& PresetRect, TSharedPtr<FScopedTransaction>& OutTransaction, FString PresetHost = NDISPLAY_DEFAULT_CLUSTER_HOST);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Creates a new cluster node, presenting a dialog box to allow the user to customize its properties, and adds it to the cluster. @param Toolkit - The blueprint editor toolkit being used. @param Cluster - The initial cluster the user wants to add the cluster node to. @param PresetRect - The initial rectangle to configure the new cluster node with in the dialog box. @param OutTransaction - The transaction created when adding a cluster node. May be null if the user canceled the operation. @param PresetHost - Optional initial host string to configure the new cluster node with in the dialog box. @return The newly created cluster node, or null if the user cancelled out of the dialog box.
- L46 _prototype_ `UDisplayClusterConfigurationViewport* CreateNewViewportFromDialog(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& Toolkit, UDisplayClusterConfigurationClusterNode* ClusterNode, const FDisplayClusterConfigurationRectangle& PresetRect, TSharedPtr<FScopedTransaction>& OutTransaction);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Creates a new viewport, presenting a dialog box to allow the user to customize its properties, and adds it to the user chosen cluster node. @param Toolkit - The blueprint editor toolkit being used. @param ClusterNode - The initial cluster node the user wants to add the viewport to, or null to use the first cluster node in the cluster. @param PresetRect - The initial rectangle to configure the new viewport with in the dialog box. @param OutTransaction - The transaction created when adding a viewport. May be null if the user canceled the operation. @return The newly created viewport, or null if the user cancelled out of the dialog box.
- L54 _prototype_ `bool CanAddNewViewportToToolkit(const TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Checks if a new viewport is allowed to be added by making sure there is a cluster node available. @param InToolkit The toolkit hosting the viewport.
- L63 _prototype_ `void ShowNewClusterItemDialogWindow(TSharedRef<SDisplayClusterConfiguratorNewClusterItemDialog> DialogContent, TSharedPtr<SWidget> ParentElement, FText WindowTitle, FVector2D WindowSize);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Displays a dialog box used to configure new cluster item properties before adding the new item to the cluster configuration. @param DialogContent - The widget to display in the dialog box's main section. @param ParentElement - The UI element to display the dialog box from. If null, will use the active window as a parent. @param WindowTitle - The title displayed at the top of the dialog box. @param WindowSize - The size of the dialog box.
- L70 _prototype_ `TSharedPtr<FDragDropOperation> MakeDragDropOperation(const TArray<UObject*>& SelectedObjects);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Attempts to create an appropriate drag and drop operation for the selected objects. @param SelectedObjects - The objects to create the drag and drop operation for. @return A valid pointer to the drag and drop operation if an operation could be made, and invalid pointer if not.
- L79 _prototype_ `FVector2D FindNextAvailablePositionForClusterNode(UDisplayClusterConfigurationCluster* Cluster, const FString& DesiredHost, const FVector2D& DesiredPosition, const FVector2D& DesiredSize);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Finds the next available position for a cluster node within a host so that the cluster node doesn't overlap any existing nodes. @param Cluster - The cluster to find the position within. @param DesiredHost - The host the cluster node wants to be positioned in. @param DesiredPosition - The desired position of the cluster node. @param DesiredSize - The desired size of the cluster node.
- L87 _prototype_ `FVector2D FindNextAvailablePositionForViewport(UDisplayClusterConfigurationClusterNode* ClusterNode, const FVector2D& DesiredPosition, const FVector2D& DesiredSize);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Finds the next available position for a viewport within a cluster node so that the viewport doesn't overlap any existing viewports. @param ClusterNode - The cluster node to find the position within. @param DesiredPosition - The desired position of the viewport. @param DesiredSize - The desired size of the viewport.
- L93 _prototype_ `void CopyClusterItemsToClipboard(const TArray<UObject*>& ClusterItemsToCopy);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Copies the specified list of cluster items to the clipboard. @param ClusterItemsToCopy - The list of cluster items to copy.
- L100 _prototype_ `bool CanPasteClusterItemsFromClipboard(const TArray<UObject*>& TargetClusterItems, int32& OutNumItems);` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Checks to see if the clipboard contains cluster items that can be pasted into the target cluster items. @param TargetClusterItems - The cluster items to paste the copied cluster items into. @param OutNumItems - The number of cluster items that can be pasted from the clipboard.
- L108 _prototype_ `TArray<UObject*> PasteClusterItemsFromClipboard(const TArray<UObject*>& TargetClusterItems, TOptional<FVector2D> PasteLocation = TOptional<FVector2D>());` (scope `UE::DisplayClusterConfiguratorClusterEditorUtils`) — Pastes any cluster items in the clipboard into the specified target items, if the target items can accept the pasted items. @param TargetClusterItems - The cluster items to paste the copied cluster items into, if compatible. @param PasteLocation - Optional location to paste the cluster items at. @return The pasted cluster items.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/ClusterConfiguration/SDisplayClusterConfiguratorNewClusterItemDialog.h` (Private)


#### struct `FDisplayClusterConfiguratorPresetSize`  
`struct FDisplayClusterConfiguratorPresetSize`  
_L18-42_
- L21 _public member_ `FText DisplayName;`
- L22 _public member_ `FVector2D Size;`
- L24 _public function_ `FDisplayClusterConfiguratorPresetSize() : DisplayName(FText::GetEmpty()), Size(FVector2D::ZeroVector)`
- L29 _public function_ `FDisplayClusterConfiguratorPresetSize(FText InDisplayName, FVector2D InSize) : DisplayName(InDisplayName), Size(InSize)`
- L34 _public function_ `bool operator==(const FDisplayClusterConfiguratorPresetSize& Other) const`
- L40 _public member_ `static const TArray<FDisplayClusterConfiguratorPresetSize> CommonPresets;`
- L41 _public member_ `static const int32 DefaultPreset;`

#### class `SDisplayClusterConfiguratorNewClusterItemDialog`  
`class SDisplayClusterConfiguratorNewClusterItemDialog : public SCompoundWidget`  
_L46-111_
- inherits: `SCompoundWidget`
- L49 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorNewClusterItemDialog) : _ParentWindow() , _ParentItemOptions() , _InitiallySelectedParentItem("") , _PresetItemOptions() , _InitiallySelectedPreset() , _InitialName("") , _MaxWindowHeight(0.0f) , _MaxWindowWidth(0.0f) , _FooterContent()`
- L60 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TArray<FString>, ParentItemOptions) SLATE_ARGUMENT(FString, InitiallySelectedParentItem) SLATE_ARGUMENT(TArray<FDisplayClusterConfiguratorPresetSize>, PresetItemOptions) SLATE_ARGUMENT(FDisplayClusterConfiguratorPresetSize, InitiallySelectedPreset) SLATE_ARGUMENT(FString, InitialName) SLATE_ARGUMENT(float, MaxWindowHeight) SLATE_ARGUMENT(float, MaxWindowWidth) SLATE_ARGUMENT(TSharedPtr<SWidget>, FooterContent) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UObject* InClusterItem);`
- L74 _public prototype_ `void SetParentWindow(TSharedPtr<SWindow> InParentWindow);`
- L76 _public prototype_ `FString GetSelectedParentItem() const;`
- L77 _public prototype_ `FString GetItemName() const;`
- L78 _public prototype_ `bool WasAccepted() const;`
- L81 _private prototype_ `FText GetParentComboBoxSelectedText() const;`
- L82 _private prototype_ `FText GetPresetsComboBoxSelectedText() const;`
- L84 _private prototype_ `FReply OnAddButtonClicked();`
- L85 _private prototype_ `FReply OnCancelButtonClicked();`
- L87 _private prototype_ `FText GetPresetDisplayText(const TSharedPtr<FDisplayClusterConfiguratorPresetSize>& Preset) const;`
- L89 _private prototype_ `void OnSelectedPresetChanged(TSharedPtr<FDisplayClusterConfiguratorPresetSize> SelectedPreset, ESelectInfo::Type SelectionType);`
- L91 _private prototype_ `FOptionalSize GetDetailsMaxDesiredSize() const;`
- L94 _private member_ `TWeakPtr<SWindow> ParentWindow;`
- L95 _private member_ `TSharedPtr<SWidget> FooterContent;`
- L97 _private member_ `TSharedPtr<SWidget> AddCancelButtons;` — The container for the Add and Cancel buttons.
- L98 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L99 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ParentComboBox;`
- L100 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FDisplayClusterConfiguratorPresetSize>>> PresetsComboBox;`
- L101 _private member_ `TSharedPtr<SEditableTextBox> NameTextBox;`
- L103 _private member_ `TArray<TSharedPtr<FString>> ParentItems;`
- L104 _private member_ `TArray<TSharedPtr<FDisplayClusterConfiguratorPresetSize>> PresetItems;`
- L106 _private member_ `FOnPresetChanged OnPresetChanged;`
- L108 _private member_ `float MaxWindowWidth;`
- L109 _private member_ `float MaxWindowHeight;`
- L110 _private member_ `bool bWasAccepted;`

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPresetChanged, FVector2D);`
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPresetChanged, FVector2D);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/ClusterConfiguration/ViewModels/DisplayClusterConfiguratorClusterNodeViewModel.h` (Private)


#### class `FDisplayClusterConfiguratorClusterNodeViewModel`  
`class FDisplayClusterConfiguratorClusterNodeViewModel`  
_L13-26_
- L16 _public prototype_ `FDisplayClusterConfiguratorClusterNodeViewModel(UDisplayClusterConfigurationClusterNode* ClusterNode);`
- L18 _public prototype_ `void SetWindowRect(const FDisplayClusterConfigurationRectangle& NewWindowRect);`
- L19 _public prototype_ `void SetHost(const FString& NewHost);`
- L22 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationClusterNode> ClusterNodePtr;`
- L24 _private prototype_ `PROPERTY_HANDLE(WindowRect);`
- L25 _private prototype_ `PROPERTY_HANDLE(Host);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/ClusterConfiguration/ViewModels/DisplayClusterConfiguratorProjectionPolicyViewModel.h` (Private)


#### class `FDisplayClusterConfiguratorProjectionPolicyViewModel`  
`class FDisplayClusterConfiguratorProjectionPolicyViewModel`  
_L12-26_
- L15 _public prototype_ `FDisplayClusterConfiguratorProjectionPolicyViewModel(UDisplayClusterConfigurationViewport* InViewport);`
- L17 _public prototype_ `void SetPolicyType(const FString& PolicyType);`
- L18 _public prototype_ `void SetIsCustom(bool bIsCustom);`
- L19 _public prototype_ `void SetParameterValue(const FString& ParameterKey, const FString& ParameterValue);`
- L20 _public prototype_ `void ClearParameters();`
- L23 _private member_ `TSharedPtr<ISinglePropertyView> ProjectionPolicyView;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> ProjectionPolicyHandle;`
- L25 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationViewport> ViewportPtr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/ClusterConfiguration/ViewModels/DisplayClusterConfiguratorViewModelMacros.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define PROPERTY_HANDLE(PropertyName) \`
- L9 _macro_ `#define INIT_PROPERTY_HANDLE(ObjectClass, Object, Property) \`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/ClusterConfiguration/ViewModels/DisplayClusterConfiguratorViewportViewModel.h` (Private)


#### class `FDisplayClusterConfiguratorViewportViewModel`  
`class FDisplayClusterConfiguratorViewportViewModel`  
_L15-37_
- desc: Stores property handles for a viewport configuration object that can be used to propagate property changed events through the engine when changing those properties
- L19 _public prototype_ `FDisplayClusterConfiguratorViewportViewModel(UDisplayClusterConfigurationViewport* Viewport);` — Creates a new view model for the specified viewport configuration object
- L22 _public prototype_ `void SetCamera(const FString& NewCamera);` — Sets the camera property of the viewport, propagating the change through property handles and marking the viewport's package as dirty
- L25 _public prototype_ `void SetRegion(const FDisplayClusterConfigurationRectangle& NewRegion);` — Sets the region of the viewport,  propagating the change through property handles and marking the viewport's package as dirty
- L28 _public prototype_ `void SetRemap(const FDisplayClusterConfigurationViewport_RemapData& NewRemap);` — Sets the base remap configuration of the viewport,  propagating the change through property handles and marking the viewport's package as dirty
- L32 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationViewport> ViewportPtr;` — A pointer to the viewport configuration object the view model encapsulates
- L34 _private prototype_ `PROPERTY_HANDLE(Camera);`
- L35 _private prototype_ `PROPERTY_HANDLE(Region);`
- L36 _private prototype_ `PROPERTY_HANDLE(ViewportRemap);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorAssetTypeActions.h` (Private)


#### class `FDisplayClusterConfiguratorAssetTypeActions_Base`  
`class FDisplayClusterConfiguratorAssetTypeActions_Base : public FAssetTypeActions_Blueprint`  
_L8-16_
- inherits: `FAssetTypeActions_Blueprint`
- L11 _public function_ `FDisplayClusterConfiguratorAssetTypeActions_Base(uint32 Categories) : MyAssetCategory(Categories)`
- L12 _public function_ `virtual uint32 GetCategories() override`
- L15 _protected member_ `uint32 MyAssetCategory;`

#### class `FDisplayClusterConfiguratorActorAssetTypeActions`  
`class FDisplayClusterConfiguratorActorAssetTypeActions : public FDisplayClusterConfiguratorAssetTypeActions_Base`  
_L19-29_
- inherits: `FDisplayClusterConfiguratorAssetTypeActions_Base`
- desc: Wrapper just to hide base actor class from being created in the asset browser.
- L22 _public function_ `FDisplayClusterConfiguratorActorAssetTypeActions(EAssetTypeCategories::Type InAssetCategory) : FDisplayClusterConfiguratorAssetTypeActions_Base(InAssetCategory)`
- L25 _public function_ `virtual FText GetName() const override` — FAssetTypeActions_Base
- L26 _public function_ `virtual FColor GetTypeColor() const override`
- L27 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorBlueprintEditor.h` (Private)


#### class `FDisplayClusterConfiguratorBlueprintEditor`  
`class FDisplayClusterConfiguratorBlueprintEditor : public IDisplayClusterConfiguratorBlueprintEditor`  
_L29-275_
- inherits: `IDisplayClusterConfiguratorBlueprintEditor`
- desc: nDisplay editor UI (should call functions on the subsystem or UNDisplayAssetEditor)
- L32 _private typedef_ `using Super = IDisplayClusterConfiguratorBlueprintEditor;`
- L36 _public prototype_ `static void RegisterPanelExtensionFactory();` — Registers any panel extension factories needed for the blueprint editor
- L39 _public prototype_ `static void UnregisterPanelExtensionFactory();` — Unregisters any panel extension factories that were registered for the blueprint editor
- L43 _private prototype_ `static TSharedRef<SWidget> OnExtendAddComponentButton(FWeakObjectPtr ExtensionContext);` — Raised when the blueprint editor's subobject editor is creating extensions next to the Add Component button
- L46 _private member_ `static TArray<TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor>> EditorsRegisteredForPanelExtension;` — A list of instantiated blueprint editors that are queried when the AddComponentButton panel extension is creating widgets
- L49 _public prototype_ `FDisplayClusterConfiguratorBlueprintEditor();`
- L50 _public prototype_ `~FDisplayClusterConfiguratorBlueprintEditor();`
- L54 _public prototype_ `virtual void InitDisplayClusterBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UDisplayClusterBlueprint* Blueprint);`
- L57 _public prototype_ `virtual TArray<UObject*> GetSelectedObjects() const override;`
- L58 _public prototype_ `virtual bool IsObjectSelected(UObject* Obj) const override;`
- L62 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L63 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L64 _public prototype_ `virtual void RefreshEditors(ERefreshBlueprintEditorReason::Type Reason) override;`
- L67 _public prototype_ `virtual void SelectObjects(TArray<UObject*>& InSelectedObjects, bool bFullRefresh = false);`
- L68 _public prototype_ `virtual void SelectAncillaryComponents(const TArray<FString>& ComponentNames);`
- L69 _public prototype_ `virtual void SelectAncillaryViewports(const TArray<FString>& ComponentNames);`
- L71 _public prototype_ `virtual UDisplayClusterConfigurationData* GetEditorData() const;`
- L72 _public prototype_ `virtual FDelegateHandle RegisterOnConfigReloaded(const FOnConfigReloadedDelegate& Delegate);`
- L73 _public prototype_ `virtual void UnregisterOnConfigReloaded(FDelegateHandle DelegateHandle);`
- L74 _public prototype_ `virtual FDelegateHandle RegisterOnObjectSelected(const FOnObjectSelectedDelegate& Delegate);`
- L75 _public prototype_ `virtual void UnregisterOnObjectSelected(FDelegateHandle DelegateHandle);`
- L76 _public prototype_ `virtual FDelegateHandle RegisterOnInvalidateViews(const FOnInvalidateViewsDelegate& Delegate);`
- L77 _public prototype_ `virtual void UnregisterOnInvalidateViews(FDelegateHandle DelegateHandle);`
- L78 _public prototype_ `virtual FDelegateHandle RegisterOnClusterChanged(const FOnClusterChangedDelegate& Delegate);`
- L79 _public prototype_ `virtual void UnregisterOnClusterChanged(FDelegateHandle DelegateHandle);`
- L81 _public prototype_ `virtual void InvalidateViews();`
- L82 _public prototype_ `virtual void ClusterChanged(bool bStructureChange = false);`
- L83 _public prototype_ `virtual void ClearViewportSelection();`
- L86 _public prototype_ `virtual UDisplayClusterConfigurationData* GetConfig() const;` — Retrieve the config data from the CDO.
- L89 _public prototype_ `ADisplayClusterRootActor* GetDefaultRootActor() const;` — Retrieve the CDO being edited.
- L91 _public prototype_ `virtual TSharedRef<IDisplayClusterConfiguratorViewOutputMapping> GetViewOutputMapping() const;`
- L92 _public prototype_ `virtual TSharedRef<IDisplayClusterConfiguratorViewTree> GetViewCluster() const;`
- L94 _public function_ `TSharedPtr<SDockTab> GetViewportTab() const`
- L95 _public function_ `TSharedPtr<FEditorViewportTabContent> GetViewportTabContent() const`
- L97 _public function_ `TSharedPtr<SWidget> GetSCSEditorWrapper() const`
- L99 _public function_ `TSharedPtr<FDisplayClusterConfiguratorToolbar> GetConfiguratorToolbar() const`
- L102 _public prototype_ `TSharedRef<FEditorModeTools> GetModeTools() const;` — Returns mode tools used by this editor instance
- L105 _public prototype_ `void SyncViewports();` — Syncs shared properties between viewports.
- L108 _public prototype_ `void RefreshDisplayClusterPreviewActor();` — Make sure the blueprint preview actor is up to date.
- L111 _public prototype_ `void RestoreLastEditedState();` — Restores previously open documents.
- L114 _public prototype_ `void UpdateXformGizmos();` — Updates the root actor's xform components to match the editor settings.
- L117 _private member_ `TWeakObjectPtr<AActor> CurrentPreviewActor;`
- L119 _private member_ `FDelegateHandle UpdateOutputMappingHandle;`
- L123 _public prototype_ `bool LoadWithOpenFileDialog();` — Load with OpenFileDialog
- L126 _public prototype_ `bool LoadFromFile(const FString& FilePath);` — Load from specified file
- L129 _public prototype_ `bool ExportConfig();` — Save to the same file the config data was read from
- L132 _public prototype_ `bool CanExportConfig() const;` — Verifies config can be saved.
- L135 _public prototype_ `bool SaveToFile(const FString& FilePath);` — Save to a specified file
- L138 _public prototype_ `bool SaveWithOpenFileDialog();` — Save with SaveFileDialog
- L143 _protected function_ `virtual FName GetEditorName() const override`
- L147 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L148 _protected prototype_ `virtual void SaveAsset_Execute() override;`
- L149 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L150 _protected function_ `virtual bool IsTickable() const override`
- L151 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L152 _protected prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L153 _protected prototype_ `virtual void OnClose() override;`
- L154 _protected prototype_ `virtual void Compile() override;`
- L155 _protected prototype_ `virtual void CreateDefaultTabContents(const TArray<UBlueprint*>& InBlueprints) override;`
- L156 _protected prototype_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L161 _protected prototype_ `virtual void OnSelectionUpdated(const TArray<TSharedPtr<class FSubobjectEditorTreeNode>>& SelectedNodes) override;` — Delegate invoked when the selection is changed in the SCS editor widget
- L164 _protected prototype_ `virtual void OnComponentDoubleClicked(TSharedPtr<class FSubobjectEditorTreeNode> Node) override;` — Delegate invoked when an item is double clicked in the SCS editor widget
- L167 _protected prototype_ `void CreateDCSCSEditors();`
- L168 _protected prototype_ `void ShutdownDCSCSEditors();`
- L170 _protected prototype_ `TSharedRef<SWidget> CreateAddComponentButton();`
- L172 _protected prototype_ `void CreateSCSEditorWrapper();`
- L204 _private member_ `ESelectionSource CurrentSelectionSource = ESelectionSource::External;` — Keeps track of the current source of the selection changes that caused OnSelectionUpdated to be invoked.
- L208 _protected prototype_ `void CreateWidgets();`
- L210 _protected prototype_ `void ExtendMenu();`
- L212 _protected prototype_ `void ExtendToolbar();`
- L214 _protected prototype_ `void OnPostCompiled(UBlueprint* InBlueprint);`
- L218 _private prototype_ `void ImportConfig_Clicked();`
- L220 _private prototype_ `void ExportToFile_Clicked();`
- L222 _private prototype_ `void EditConfig_Clicked();`
- L224 _private prototype_ `bool IsExportOnSaveSet() const;`
- L225 _private prototype_ `void ToggleExportOnSaveSetting();`
- L227 _private prototype_ `void ImportMPCDI_Clicked();`
- L230 _private prototype_ `void OnReadOnlyChanged(bool bReadOnly);`
- L231 _private prototype_ `void OnRenameVariable(UBlueprint* Blueprint, UClass* VariableClass, const FName& OldVariableName, const FName& NewVariableName);`
- L232 _private prototype_ `void OnFocusChanged(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);`
- L234 _private prototype_ `void BindCommands();`
- L237 _private member_ `TSharedPtr<FDisplayClusterConfiguratorViewOutputMapping> ViewOutputMapping;`
- L238 _private member_ `TSharedPtr<FDisplayClusterConfiguratorViewCluster> ViewCluster;`
- L241 _private member_ `TSharedPtr<SDockTab> ViewportTab;` — Owner of the viewport.
- L243 _private member_ `TSharedPtr<FEditorViewportTabContent> ViewportTabContent;` — Tracking the active viewports in this editor.
- L245 _private member_ `TSharedPtr<SWidget> SCSEditorWrapper;`
- L247 _private member_ `TSharedPtr<FExtender> MenuExtender;`
- L248 _private member_ `TSharedPtr<FExtender> ToolbarExtender;`
- L251 _private member_ `TSharedRef<FEditorModeTools> SharedModeTools;` — A mode tools instance shared among viewports
- L253 _private member_ `TSharedPtr<FDisplayClusterConfiguratorToolbar> ConfiguratorToolbar;`
- L255 _private member_ `FOnConfigReloaded OnConfigReloaded;`
- L258 _private member_ `FOnObjectSelected OnObjectSelected;` — Delegate for when an item is selected
- L261 _private member_ `FOnInvalidateViews OnInvalidateViews;` — View invalidation delegate
- L263 _private member_ `FOnClearViewportSelection OnClearViewportSelection;`
- L266 _private member_ `FOnClusterChanged OnClusterChanged;` — Delegate which is raised when the cluster configuration is changed.
- L268 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`
- L271 _private member_ `TWeakObjectPtr<UDisplayClusterBlueprint> LoadedBlueprint;` — The currently loaded blueprint.
- L273 _private member_ `FDelegateHandle RenameVariableHandle;`
- L274 _private member_ `FDelegateHandle FocusChangedHandle;`

#### enum `FDisplayClusterConfiguratorBlueprintEditor::ESelectionSource`  
`enum class ESelectionSource`  
_L175-181_
- L177 _public enumerator_ `External`
- L178 _public enumerator_ `Internal`
- L179 _public enumerator_ `Ancillary`
- L180 _public enumerator_ `Refresh`

#### struct `FDisplayClusterConfiguratorBlueprintEditor::FSelectionScope`  
`struct FSelectionScope`  
_L183-199_
- L185 _public function_ `FSelectionScope(FDisplayClusterConfiguratorBlueprintEditor* Editor, ESelectionSource ScopedSelectionSource) : SourceProperty(Editor->CurrentSelectionSource), PreviousValue(Editor->CurrentSelectionSource)`
- L192 _public function_ `~FSelectionScope()`
- L197 _public member_ `ESelectionSource& SourceProperty;`
- L198 _public member_ `ESelectionSource PreviousValue;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorBuildSettings.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DISPLAY_CLUSTER_CONFIGURATOR_BUILD_VIEWER` — It's a viewer in 4.26

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorCommands.h` (Private)


#### class `FDisplayClusterConfiguratorCommands`  
`class FDisplayClusterConfiguratorCommands : public TCommands<FDisplayClusterConfiguratorCommands>`  
_L10-41_
- inherits: `TCommands<FDisplayClusterConfiguratorCommands>`
- L14 _public function_ `FDisplayClusterConfiguratorCommands() : TCommands<FDisplayClusterConfiguratorCommands>(TEXT("DisplayClusterConfigurator"), NSLOCTEXT("Contexts", "DisplayClusterConfigurator", "Display Cluster Configurator"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> Import;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> Export;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> EditConfig;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ExportConfigOnSave;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ImportMPCDI;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> AddNewClusterNode;` — Cluster Configuration commands
- L30 _public member_ `TSharedPtr<FUICommandInfo> AddNewViewport;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ResetCamera;` — Viewport Preview commands
- L34 _public member_ `TSharedPtr<FUICommandInfo> ShowFloor;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ShowGrid;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ShowOrigin;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> EnableAA;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ShowPreview;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> Show3DViewportNames;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowXformGizmos;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorCompiler.h` (Private)


#### class `FDisplayClusterConfiguratorKismetCompiler`  
`class FDisplayClusterConfiguratorKismetCompiler : public IBlueprintCompiler`  
_L9-17_
- inherits: `IBlueprintCompiler`
- L13 _public prototype_ `virtual bool CanCompile(const UBlueprint* Blueprint) override;` — IBlueprintCompiler interface
- L14 _public prototype_ `virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) override;`
- L15 _public prototype_ `virtual bool GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const override;`

#### class `FDisplayClusterConfiguratorKismetCompilerContext`  
`class FDisplayClusterConfiguratorKismetCompilerContext : public FKismetCompilerContext`  
_L19-46_
- inherits: `FKismetCompilerContext`
- L21 _private typedef_ `using Super = FKismetCompilerContext;`
- L24 _public prototype_ `FDisplayClusterConfiguratorKismetCompilerContext(UBlueprint* InBlueprint, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);`
- L29 _protected prototype_ `virtual void SpawnNewClass(const FString& NewClassName) override;` — FKismetCompilerContext interface
- L30 _protected prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* ClassToUse) override;`
- L31 _protected prototype_ `virtual void PreCompile() override;`
- L32 _protected prototype_ `virtual void PostCompile() override;`
- L33 _protected prototype_ `virtual void SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& SubObjectsToSave, UBlueprintGeneratedClass* ClassToClean) override;`
- L34 _protected prototype_ `virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject) override;`
- L40 _protected prototype_ `void ValidateConfiguration();` — Preform pre compile time validation on Display Cluster data.
- L43 _private member_ `class UDisplayClusterBlueprintGeneratedClass* DCGeneratedBP;`
- L45 _private member_ `TArray<UObject*> OldSubObjects;` — Sub-objects which should survive a compile.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorEditorMode.h` (Private)


#### struct `FDisplayClusterEditorModes`  
`struct FDisplayClusterEditorModes`  
_L8-34_
- desc: This is the list of IDs for Display Cluster Editor modes
- L11 _public member_ `static const FName DisplayClusterEditorName;` — App Name
- L14 _public member_ `static const FName DisplayClusterEditorConfigurationMode;` — Mode constants
- L15 _public member_ `static const FName DisplayClusterEditorGraphMode;`
- L17 _public function_ `static FText GetLocalizedMode(const FName InMode)`
- L33 _private function_ `FDisplayClusterEditorModes()`

#### class `FDisplayClusterConfiguratorBlueprintModeBase`  
`class FDisplayClusterConfiguratorBlueprintModeBase : public FBlueprintEditorApplicationMode`  
_L36-51_
- inherits: `FBlueprintEditorApplicationMode`
- L39 _public member_ `static const FName TabID_Log;`
- L40 _public member_ `static const FName TabID_OutputMapping;`
- L41 _public member_ `static const FName TabID_Scene;`
- L42 _public member_ `static const FName TabID_Cluster;`
- L43 _public member_ `static const FName TabID_Viewport;`
- L46 _public prototype_ `FDisplayClusterConfiguratorBlueprintModeBase(TSharedPtr<class FDisplayClusterConfiguratorBlueprintEditor> EditorIn, FName EditorModeIn );`
- L49 _protected member_ `TWeakPtr<class FDisplayClusterConfiguratorBlueprintEditor> Editor;`
- L50 _protected member_ `FWorkflowAllowedTabSet EditorTabFactories;`

#### class `FDisplayClusterConfiguratorEditorConfigurationMode`  
`class FDisplayClusterConfiguratorEditorConfigurationMode : public FDisplayClusterConfiguratorBlueprintModeBase`  
_L53-65_
- inherits: `FDisplayClusterConfiguratorBlueprintModeBase`
- L56 _public prototype_ `FDisplayClusterConfiguratorEditorConfigurationMode(TSharedPtr<class FDisplayClusterConfiguratorBlueprintEditor> EditorIn);`
- L59 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L60 _public prototype_ `virtual void PostActivateMode() override;`
- L64 _protected prototype_ `TSharedPtr<FTabManager::FLayout> BuildDefaultLayout(const FString& LayoutName);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorEditorSubsystem.h` (Private)


#### class `UDisplayClusterConfiguratorEditorSubsystem`  
`class UDisplayClusterConfiguratorEditorSubsystem : public UEditorSubsystem`  
_L14-32_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L20 _public prototype_ `UDisplayClusterBlueprint* ImportAsset(UObject* InParent, const FName& InName, const FString& InFilename);`
- L22 _public prototype_ `bool ReimportAsset(UDisplayClusterBlueprint* InBlueprint);`
- L24 _public prototype_ `UDisplayClusterConfigurationData* ReloadConfig(UDisplayClusterBlueprint* InBlueprint, const FString& InConfigPath);`
- L26 _public prototype_ `bool RenameAssets(const TWeakObjectPtr<UObject>& InAsset, const FString& InNewPackagePath, const FString& InNewName);`
- L28 _public prototype_ `bool SaveConfig(UDisplayClusterConfigurationData* InConfiguratorEditorData, const FString& InConfigPath);`
- L31 _public prototype_ `bool ConfigAsString(UDisplayClusterConfigurationData* InConfiguratorEditorData, FString& OutString) const;` — Convert configuration to string

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(DisplayClusterConfiguratorLog, Log, All);` — Module-wide log categories
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(DisplayClusterConfiguratorLog, Log, All);` — Module-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorModule.h` (Private)


#### class `FDisplayClusterConfiguratorModule`  
`class FDisplayClusterConfiguratorModule : public IDisplayClusterConfigurator`  
_L18-61_
- inherits: `IDisplayClusterConfigurator`
- desc: Display Cluster Configurator editor module
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `void OnPostEngineInit();`
- L29 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() const override` — Gets the extensibility managers for outside entities to extend this editor's menus and toolbars
- L30 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() const override`
- L34 _public prototype_ `virtual const FDisplayClusterConfiguratorCommands& GetCommands() const override;`
- L38 _private prototype_ `void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);`
- L39 _private prototype_ `void RegisterSettings();`
- L40 _private prototype_ `void UnregisterSettings();`
- L41 _private prototype_ `void RegisterCustomLayouts();`
- L42 _private prototype_ `void UnregisterCustomLayouts();`
- L43 _private prototype_ `void RegisterSectionMappings();`
- L44 _private prototype_ `void UnregisterSectionMappings();`
- L46 _private prototype_ `static TSharedPtr<FKismetCompilerContext> GetCompilerForDisplayClusterBP(UBlueprint* BP, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions);`
- L49 _private member_ `TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;`
- L50 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L51 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L52 _private member_ `TSharedPtr<FDisplayClusterConfiguratorToolbarExtensions> ToolbarExtensions;`
- L53 _private member_ `FDisplayClusterConfiguratorKismetCompiler BlueprintCompiler;`
- L54 _private member_ `TArray<FName> RegisteredClassLayoutNames;`
- L55 _private member_ `TArray<FName> RegisteredPropertyLayoutNames;`
- L56 _private member_ `FDelegateHandle FilesLoadedHandle;`
- L57 _private member_ `FDelegateHandle PostEngineInitHandle;`
- L60 _private member_ `static FOnDisplayClusterConfiguratorReadOnlyChanged OnDisplayClusterConfiguratorReadOnlyChanged;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorPropertyUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DisplayClusterConfiguratorPropertyUtils` (scope `UE`)
- L25 _prototype_ `TSharedPtr<ISinglePropertyView> GetPropertyView(UObject* Owner, const FName& FieldName);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Create a temporary property handle for a given property. Call GetPropertyHandle() from here. The property handle will be valid as long as the property view is valid. @param Owner UObject owning the property. @param FieldName The field name of the property. @return A property handle created for this property.
- L35 _function_ `template<typename T> void SetPropertyHandleValue(UObject* Owner, const FName& FieldName, T Value)` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Set the value of a property handle for an object by the field name. @param Owner UObject owning the property. @param FieldName The field name of the property. @param Value The value to the set the property.
- L56 _prototype_ `UObject* AddKeyWithInstancedValueToMap(UObject* MapOwner, const FName& FieldName, const FString& Key, UObject* Value);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Add an instanced object value to a map when the property handle is not available. A temporary handle will be created. This will deep copy the object into the map. @param MapOwner UObject owning the map. @param FieldName The field name of the map property. @param Key The Key to add to the map. @param Value An object instance to add to the map. @return An updated object instance that was added to the map. This will not be the same as the original passed in value.
- L69 _prototype_ `TSharedPtr<IPropertyHandle> AddKeyValueToMap(uint8* MapOwner, TSharedPtr<IPropertyHandle> PropertyHandle, const FString& Key, const FString& Value, EPropertyValueSetFlags::Type SetFlags = EPropertyValueSetFlags::DefaultFlags);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Add a formatted string value to map when the property handle is already available. @param MapOwner The address of the object owning the map. @param PropertyHandle The property handle of the map. @param Key The key value to add. @param Value The formatted string value to add. @param SetFlags How the formatted string value should be set. @return The KeyPair handle added.
- L81 _prototype_ `bool RemoveKeyFromMap(UObject* MapOwner, const FName& FieldName, const FString& Key);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Remove a key from a map without the property handle. A temporary handle will be created. @param MapOwner UObject owning the map. @param FieldName The field name of the map property. @param Key The key to remove from the map. @return True if successfully removed. False otherwise.
- L92 _prototype_ `bool RemoveKeyFromMap(uint8* MapOwner, TSharedPtr<IPropertyHandle> PropertyHandle, const FString& Key);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Remove a key from a map. @param MapOwner Address owning the map. @param PropertyHandle The map property handle. @param Key The key to remove from the map. @return True if successfully removed. False otherwise.
- L100 _prototype_ `bool EmptyMap(uint8* MapOwner, TSharedPtr<IPropertyHandle> PropertyHandle);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Empties a map. @param MapOwner Address owning the map. @param PropertyHandle The map property handle. @return true if successfully emptied; false otherwise.
- L112 _prototype_ `int32 FindMapHandleIndexFromKey(TSharedPtr<IPropertyHandleMap> MapHandle, FScriptMapHelper& MapHelper, const FString& Key);` (scope `UE::DisplayClusterConfiguratorPropertyUtils`) — Find the index to use with the handle or INDEX_NONE. O(n) This is necessary because the ArrayIndex of the handle's internal PropertyNode may not match the index or local index of the map. @param MapHandle A handle to the map. @param MapHelper An FScriptMapHelper initialized to the map property for a given instance. @param Key The key to find the index for. @return The index as defined by the MapHandle.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorStyle.h` (Private)


#### class `FDisplayClusterConfiguratorStyle`  
`class FDisplayClusterConfiguratorStyle : public FSlateStyleSet`  
_L8-42_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `FDisplayClusterConfiguratorStyle();`
- L12 _public prototype_ `~FDisplayClusterConfiguratorStyle();`
- L14 _public function_ `static FDisplayClusterConfiguratorStyle& Get()`
- L20 _public prototype_ `static void ReloadTextures();`
- L22 _public prototype_ `const FLinearColor& GetDefaultColor(uint32 Index);`
- L25 _private prototype_ `void Initialize();`
- L41 _private member_ `TArray<FCornerColor> DefaultColors;`

#### struct `FDisplayClusterConfiguratorStyle::FCornerColor`  
`struct FCornerColor`  
_L27-39_
- L29 _public function_ `FCornerColor()`
- L32 _public function_ `FCornerColor(const FName& InName, const FLinearColor& InColor) : Name(InName) , Color(InColor)`
- L37 _public member_ `FName Name;`
- L38 _public member_ `FLinearColor Color;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorTabSpawners.h` (Private)


#### struct `FDisplayClusterViewSummoner`  
`struct FDisplayClusterViewSummoner : public FWorkflowTabFactory`  
_L9-16_
- inherits: `FWorkflowTabFactory`
- L11 _public prototype_ `FDisplayClusterViewSummoner(const FName& InIdentifier, TSharedPtr<FDisplayClusterConfiguratorBlueprintEditor> InHostingApp);`
- L13 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const override;`
- L15 _public member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> BlueprintEditor;`

#### struct `FDisplayClusterViewOutputMappingSummoner`  
`struct FDisplayClusterViewOutputMappingSummoner : public FDisplayClusterViewSummoner`  
_L18-23_
- inherits: `FDisplayClusterViewSummoner`
- L20 _public prototype_ `FDisplayClusterViewOutputMappingSummoner(TSharedPtr<FDisplayClusterConfiguratorBlueprintEditor> InHostingApp);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

#### struct `FDisplayClusterViewClusterSummoner`  
`struct FDisplayClusterViewClusterSummoner : public FDisplayClusterViewSummoner`  
_L25-30_
- inherits: `FDisplayClusterViewSummoner`
- L27 _public prototype_ `FDisplayClusterViewClusterSummoner(TSharedPtr<FDisplayClusterConfiguratorBlueprintEditor> InHostingApp);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

#### struct `FDisplayClusterSCSSummoner`  
`struct FDisplayClusterSCSSummoner : public FDisplayClusterViewSummoner`  
_L32-37_
- inherits: `FDisplayClusterViewSummoner`
- L34 _public prototype_ `FDisplayClusterSCSSummoner(TSharedPtr<FDisplayClusterConfiguratorBlueprintEditor> InHostingApp);`
- L36 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

#### struct `FDisplayClusterSCSViewportSummoner`  
`struct FDisplayClusterSCSViewportSummoner : public FDisplayClusterViewSummoner`  
_L39-44_
- inherits: `FDisplayClusterViewSummoner`
- L41 _public prototype_ `FDisplayClusterSCSViewportSummoner(TSharedPtr<FDisplayClusterConfiguratorBlueprintEditor> InHostingApp);`
- L43 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorToolbarExtensions.h` (Private)


#### class `FDisplayClusterConfiguratorToolbarExtensions`  
`class FDisplayClusterConfiguratorToolbarExtensions : public TSharedFromThis<FDisplayClusterConfiguratorToolbarExtensions>`  
_L13-30_
- inherits: `TSharedFromThis<FDisplayClusterConfiguratorToolbarExtensions>`
- desc: Manages any toolbar extensions the nDisplay plugin needs to register with the editor
- L17 _public prototype_ `void RegisterToolbarExtensions();` — Registers any toolbar extensions with the editor
- L20 _public prototype_ `void UnregisterToolbarExtensions();` — Unregisters all registered toolbar extensions
- L23 _private prototype_ `void CreateFreezeViewportsMenu(FToolMenuSection& InSection);`
- L25 _private prototype_ `void UnfreezeAllViewports();`
- L26 _private prototype_ `bool AreAnyViewportsFrozen() const;`
- L28 _private prototype_ `void ToggleFreezeViewports(TWeakObjectPtr<ADisplayClusterRootActor> InRootActor);`
- L29 _private prototype_ `bool AreViewportsFrozen(TWeakObjectPtr<ADisplayClusterRootActor> InRootActor) const;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorUtils.h` (Private)


#### class `FDisplayClusterConfiguratorUtils`  
`class FDisplayClusterConfiguratorUtils`  
_L15-62_
- L20 _public prototype_ `static ADisplayClusterRootActor* GenerateRootActorFromConfigFile(const FString& InFilename);` — Loads a config file into memory and generates a root actor from it.
- L23 _public prototype_ `static ADisplayClusterRootActor* GenerateRootActorFromConfigData(UDisplayClusterConfigurationData* ConfigData);` — Assemble a root actor with components generated.
- L26 _public prototype_ `static UDisplayClusterBlueprint* CreateBlueprintFromRootActor(ADisplayClusterRootActor* RootActor, const FName& BlueprintName, UObject* Package);` — Construct a blueprint with components from an assembled root actor.
- L29 _public prototype_ `static void AddRootActorComponentsToBlueprint(UDisplayClusterBlueprint* Blueprint, ADisplayClusterRootActor* RootActor, const bool bCompile = true, USCS_Node* NewRootNode = nullptr);` — Harvest the root actor's dynamic components into an existing blueprint.
- L32 _public prototype_ `static void RemoveAllComponentsFromBlueprint(UBlueprint* Blueprint);` — Recursively remove all components from a blueprint.
- L35 _public prototype_ `static void RemoveAllChildrenNodes(USCS_Node* InNode);` — Recursively remove all nodes from a node.
- L38 _public prototype_ `static UDisplayClusterBlueprint* FindBlueprintFromObject(UObject* InObject);` — Search up the outer objects for a DisplayCluster Blueprint.
- L41 _public prototype_ `static FDisplayClusterConfiguratorBlueprintEditor* GetBlueprintEditorForObject(UObject* InObject);` — Locate an open Blueprint Editor for the object.
- L44 _public prototype_ `static bool IsPrimaryNodeInConfig(UDisplayClusterConfigurationData* ConfigData);` — Checks if a primary node is present in a config.
- L52 _public prototype_ `static void MarkDisplayClusterBlueprintAsModified(UObject* InObject, const bool bIsStructuralChange);` — Find the blueprint associated with the object and signal it should be recompiled. @param InObject An object that is the blueprint or owned by the blueprint. @param bIsStructuralChange Perform a skeleton recompile of the blueprint.
- L55 _public prototype_ `static FName CreateUniqueName(const FName& TargetName, UClass* ObjectClass, UObject* ObjectOuter);` — Calculate and return a unique name for a given object outer.
- L58 _public function_ `static FString GetImplSuffix()` — Return the "_impl" suffix used for visualization components.
- L61 _public prototype_ `static FString FormatNDisplayComponentName(UClass* ComponentClass);` — Format an nDisplay component name correctly.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/DisplayClusterConfiguratorVersionUtils.h` (Private)


#### class `UDisplayClusterConfiguratorEditorData`  
`class UDisplayClusterConfiguratorEditorData final : public UObject`  
_L21-41_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UObject`
- desc: The original format of the DisplayCluster config data UAsset, used only for importing 4.26 assets.
- L27 _public function_ `UDisplayClusterConfiguratorEditorData()`
- L31 _public member_ `TObjectPtr<class UDisplayClusterConfigurationData> nDisplayConfig;` — `UPROPERTY(Transient)`
- L34 _public member_ `FString PathToConfig;` — `UPROPERTY()`
- L40 _public member_ `bool bConvertedToBlueprint;` — `UPROPERTY()` — True if the original asset is imported but could not be deleted.

#### class `FDisplayClusterConfiguratorVersionUtils`  
`class FDisplayClusterConfiguratorVersionUtils`  
_L43-70_
- L50 _public function_ `static int32 GetCurrentBlueprintVersion()` — Display cluster blueprints are saved with this version number. On plugin load this version is checked against the asset version.
- L53 _public prototype_ `static void UpdateBlueprintsToNewVersion();` — Check all display cluster blueprints and update to a new version if necessary.
- L56 _public prototype_ `static bool IsBlueprintUpToDate(int32 CompareVersion);` — Checks if the blueprint needs an update.
- L59 _public prototype_ `static bool IsBlueprintUpToDate(UDisplayClusterBlueprint* Blueprint);` — Checks if a blueprint is up to date.
- L62 _public prototype_ `static bool IsBlueprintFromNewerPluginVersion(int32 CompareVersion);` — Checks if the blueprint is from a new plugin version than installed.
- L65 _public prototype_ `static void SetToLatestVersion(UBlueprint* Blueprint);` — Sets the version tag of the asset.
- L68 _private prototype_ `static void DismissWrongVersionNotification();`
- L69 _private prototype_ `static void DismissFailedUpdateNotification();`

#### Free symbols / members of external scopes

- L15 _macro_ `#define DISPLAYCLUSTER_BP_VERSION 2`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/MPCDI/DisplayClusterConfiguratorMPCDIImporter.h` (Private)


#### struct `FDisplayClusterConfiguratorMPCDIImporterParams`  
`struct FDisplayClusterConfiguratorMPCDIImporterParams`  
_L17-36_
- desc: Used to pass parameters into the MPCDI importer
- L20 _public member_ `FName ParentComponentName = NAME_None;` — The name of the component to make the parent of the MPCDI geometry
- L23 _public member_ `FName ViewPointComponentName = NAME_None;` — The name of the view point component to link to the viewports. If none is supplied, the default view point is used
- L26 _public member_ `FName OriginComponentName = NAME_None;` — The name of the origin component to link to the MPCDI geometry. If none is supplied, the root component is used
- L29 _public member_ `FIPv4Address HostStartingIPAddress = FIPv4Address::InternalLoopback;` — The IP address to configure the first cluster node with
- L32 _public member_ `bool bIncrementHostIPAddress = true;` — Indicates that the IP address will be incremented for each MPCDI region a cluster node is created for
- L35 _public member_ `bool bCreateStageGeometryComponents = true;` — Indicates if stage geometry components are created to match the MPCDI geometry

#### class `FDisplayClusterConfiguratorMPCDIImporter`  
`class FDisplayClusterConfiguratorMPCDIImporter`  
_L39-106_
- desc: Helper class that can import an MPCDI configuration into an nDisplay config blueprint
- L48 _public prototype_ `static bool ImportMPCDIIntoBlueprint(const FString& InFilePath, UDisplayClusterBlueprint* InBlueprint, const FDisplayClusterConfiguratorMPCDIImporterParams& InParams);` — Imports the specified MPCDI file into the specified nDisplay config blueprint, configurating the blueprint to match the MPCDI file configuration @param InFilePath - The file path to the MPCDI file to import @param InBlueprint - The blueprint to write the MPCDI configuration to @param InParams - The parameters to use when importing the MPCDI config
- L58 _private prototype_ `static USCS_Node* FindOrCreateScreenNodeForRegion(UDisplayClusterBlueprint* InBlueprint, const FString& RegionId, bool& bOutFoundExistingScreen);` — Attempts to find an existing SCS screen node for the specified region, and if one is not found, creates a new node @param InBlueprint - The blueprint to find the node on @param RegionId - The ID of the region to find an existing node for @param bOutFoundExistingScreen - An out param indicating if an existing node was found or not
- L68 _private prototype_ `static void ConfigureScreenComponentFrom2DProfileRegion(UDisplayClusterScreenComponent* InScreenComponent, USceneComponent* InOriginComponent, const FDisplayClusterWarpMPCDIAttributes& InAttributes, const FDisplayClusterConfiguratorMPCDIImporterParams& InParams);` — Configures a screen component to match the configuration of an MPCDI region @param InScreenComponent - The component to configure @param InOriginComponent - The Origin component to configure the screens from @param InAttributes      - The attributes of the region to configure @param InParams          - The import parameters
- L77 _private prototype_ `static UDisplayClusterConfigurationViewport* FindOrCreateViewportForRegion(UDisplayClusterBlueprint* InBlueprint, const FString& RegionId, bool& bOutFoundExistingViewport);` — Attempts to find an existing viewport configuration for the specified region, and if one is not found, creates a new viewport configuration @param InBlueprint - The blueprint to find the viewport on @param RegionId - The ID of the region to find an existing viewport for @param bOutFoundExistingViewport - An out param indicating if an existing viewport was found or not
- L86 _private prototype_ `static void ConfigureViewportFromRegion(UDisplayClusterConfigurationViewport* InViewport, const FDisplayClusterWarpMPCDIAttributes& InAttributes, const FDisplayClusterConfiguratorMPCDIImporterParams& InParams);` — Configures a viewport configuration to match the configuration of an MPCDI region @param InViewport - The viewport configuration to configure @param InAttributes - The attributes of the region to configure @param InParams - The import parameters
- L96 _private prototype_ `static USceneComponent* FindBlueprintSceneComponent(UDisplayClusterBlueprint* InBlueprint, const FName& ComponentName, USCS_Node** OutComponentNode);` — Attempts to find a specified scene component in the blueprint's component hierarchy @param InBlueprint - The blueprint to search @param ComponentName - The name of the component to search for @param OutComponentNode - The corresponding SCS node of the found component if the component was a non-native component @return The found scene component, or nullptr if none was found
- L99 _private prototype_ `static FString GetScreenNameForRegion(const FString& RegionId);` — Creates a screen component name for a region using its ID
- L102 _private prototype_ `static FString GetClusterNodeNameForRegion(const FString& RegionId);` — Creates a cluster node name for a region using its ID
- L105 _private prototype_ `static FString GetViewportNameForRegion(const FString& RegionId);` — Creates a viewport name for a region using its ID

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Settings/DisplayClusterConfiguratorSettings.h` (Private)


#### class `UDisplayClusterConfiguratorEditorSettings`  
`class UDisplayClusterConfiguratorEditorSettings : public UObject`  
_L10-76_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L15 _public prototype_ `UDisplayClusterConfiguratorEditorSettings();`
- L19 _public member_ `FVector EditorDefaultCameraLocation;` — `UPROPERTY(config, EditAnywhere, Category = "Viewport")` — Camera view location when resetting the camera.
- L23 _public member_ `FRotator EditorDefaultCameraRotation;` — `UPROPERTY(config, EditAnywhere, Category = "Viewport")` — Camera view rotation when resetting the camera.
- L27 _public member_ `bool bEditorShowFloor;` — `UPROPERTY(config)` — Shows the floor in the 3d editor viewport.
- L31 _public member_ `bool bEditorShowGrid;` — `UPROPERTY(config)` — Shows the grid in the 3d editor viewport.
- L35 _public member_ `bool bEditorShowWorldOrigin;` — `UPROPERTY(config)` — Displays the world origin at 0, 0, 0
- L39 _public member_ `bool bEditorShowPreview;` — `UPROPERTY(config)` — Shows the preview in editor
- L43 _public member_ `bool bEditorShow3DViewportNames;` — `UPROPERTY(config)` — Shows names of the viewport in 3d space.
- L47 _public member_ `bool bExportOnSave;` — `UPROPERTY(config, EditAnywhere, Category = "Config File")` — Export a config automatically on save. Requires a config initially exported.
- L53 _public member_ `bool bUpdateAssetsOnStartup;` — `UPROPERTY(config, EditAnywhere, Category = "Version Updates")` — Automatically update assets saved by older versions to the most current version. It is strongly recommended to leave this on.
- L59 _public member_ `bool bDisplayAssetUpdateProgress;` — `UPROPERTY(config, EditAnywhere, Category = "Version Updates", meta = (EditCondition = "bUpdateAssetsOnStartup"))` — Display a progress bar when updating assets to a new version.
- L63 _public member_ `float VisXformScale;` — `UPROPERTY(config)` — The visual scale of the Xform static mesh
- L67 _public member_ `bool bShowVisXforms;` — `UPROPERTY(config)` — Whether to show the Xform static mesh
- L71 _public member_ `bool bEditorEnableAA;` — `UPROPERTY(config)` — Anti aliasing in 3d viewport.
- L75 _public member_ `int32 NewAssetIndex;` — `UPROPERTY(config)` — The last position on the new asset dialog box.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DCConfiguratorColorGradingSettingsCustomization.h` (Private)


#### class `FDCConfiguratorColorGradingSettingsCustomization`  
`class FDCConfiguratorColorGradingSettingsCustomization : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L9-24_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Customization that ensures proper reset to default values for the color properties in the nDisplay color grading struct when it is an element of an array
- L12 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L18 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _private member_ `bool bIsArrayMember = false;` — Indicates if the struct being customized by this customization is a member of an array

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DCConfiguratorWhiteBalanceCustomization.h` (Private)


#### class `FDCConfiguratorWhiteBalanceCustomization`  
`class FDCConfiguratorWhiteBalanceCustomization : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L9-24_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Customization that ensures proper reset to default values for the temperature properties in the nDisplay white balance struct when it is an element of an array
- L12 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L18 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _private member_ `bool bIsArrayMember = false;` — Indicates if the struct being customized by this customization is a member of an array

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorCameraOrderCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorCameraOrderCustomization`  
`class FDisplayClusterConfiguratorCameraOrderCustomization final : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L16-45_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the EnforcedCameraOrder TArray<FString> property in FDisplayClusterConfigurationViewport_ICVFX. Displays a dropdown for each array element listing all available ICVFX cameras.
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L24 _public function_ `~FDisplayClusterConfiguratorCameraOrderCustomization()`
- L31 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L33 _protected function_ `virtual bool ShouldShowHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle) const override`
- L38 _private member_ `TSharedPtr<FDisplayClusterConfiguratorNodeSelection> NodeSelectionBuilder;` — The helper object used to generate the custom array widget to display in place of a string list for the EnforcedCameraOrder property
- L41 _private member_ `TSharedPtr<IPropertyHandle> CameraOrderArrayHandle;` — The property handle for the EnforcedCameraOrder array
- L44 _private member_ `bool bCanCustomizeDisplay = false;` — Indicates whether this customizer can customize the array property's display or not

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorClusterDetailsCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorClusterDetailsCustomization`  
`class FDisplayClusterConfiguratorClusterDetailsCustomization final : public FDisplayClusterConfiguratorBaseDetailCustomization`  
_L7-16_
- inherits: `FDisplayClusterConfiguratorBaseDetailCustomization`
- L10 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InLayoutBuilder) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorClusterReferenceListCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorClusterReferenceListCustomization`  
`class FDisplayClusterConfiguratorClusterReferenceListCustomization final : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L14-50_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterConfigurationClusterItemReferenceList type, which displays a dropdown for each array element listing all selectable cluster items.
- L18 _public member_ `static const FName ClusterItemTypeMetadataKey;` — Custom "ClusterItemType" metadata specifier that can be used to specify which cluster item type is displayed in the dropdown menus
- L21 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public function_ `~FDisplayClusterConfiguratorClusterReferenceListCustomization()`
- L33 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L36 _protected function_ `virtual bool ShouldShowHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle) const override`
- L43 _private member_ `TSharedPtr<FDisplayClusterConfiguratorNodeSelection> NodeSelectionBuilder;` — The helper object used to generate the custom array widget to display in place of a string list for the ApplyPostProcessToObjects property
- L46 _private member_ `TSharedPtr<IPropertyHandle> ItemNamesArrayHandle;` — The property handle for the ItemNames array in the FDisplayClusterConfigurationClusterItemReferenceList type
- L49 _private member_ `bool bCanCustomizeDisplay = false;` — Indicates whether this customizer can customize the array property's display or not

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorDataDetailsCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorDataDetailsCustomization`  
`class FDisplayClusterConfiguratorDataDetailsCustomization final : public FDisplayClusterConfiguratorBaseDetailCustomization`  
_L7-16_
- inherits: `FDisplayClusterConfiguratorBaseDetailCustomization`
- L10 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InLayoutBuilder) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorExternalImageTypeCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorExternalImageTypeCustomization`  
`class FDisplayClusterConfiguratorExternalImageTypeCustomization final : public IPropertyTypeCustomization`  
_L9-25_
- inherits: `IPropertyTypeCustomization`
- desc: Type customizer for the FDisplayClusterConfigurationExternalImage type, which replaces the ImagePath text property with a image file picker
- L12 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L24 _private member_ `TSharedPtr<IPropertyHandle> ImagePathHandle;` — Property handle for the FDisplayClusterConfigurationExternalImage.ImagePath property

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorGenerateMipsCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorGenerateMipsCustomization`  
`class FDisplayClusterConfiguratorGenerateMipsCustomization : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L12-29_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterConfigurationPostRender_GenerateMips type, which supports a custom metadata specifier to display a simplified version of the type that excludes advanced properties.
- L19 _public member_ `static const FName SimplifiedMetadataTag;` — Custom "Simplified" metadata specifier, which hides some of the advanced child properties of a FDisplayClusterConfigurationPostRender_GenerateMips property
- L21 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorNodeSelectionCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorNodeSelection`  
`class FDisplayClusterConfiguratorNodeSelection : public TSharedFromThis<FDisplayClusterConfiguratorNodeSelection>`  
_L19-95_
- inherits: `TSharedFromThis<FDisplayClusterConfiguratorNodeSelection>`
- desc: Helper class used to construct and manage a custom array property widget that displays for each element a dropdown containing a list of the display cluster's cluster nodes, viewports, or ICVFX cameras to select from.
- L23 _public member_ `static const FName NAME_ElementToolTip;` — Custom "ElementToolTip" metadata specifier that can be used to specify the tooltip to apply to each element of the displayed array
- L33 _public prototype_ `FDisplayClusterConfiguratorNodeSelection(EOperationMode InMode, ADisplayClusterRootActor* InRootActor, FDisplayClusterConfiguratorBlueprintEditor* InToolkitPtr);`
- L35 _public function_ `~FDisplayClusterConfiguratorNodeSelection()`
- L42 _public prototype_ `ADisplayClusterRootActor* GetRootActor() const;` — Gets the DisplayClusterRootActor that is being edited by the current details panel
- L45 _public prototype_ `UDisplayClusterConfigurationData* GetConfigData() const;` — Gets the cluster configuration data object of the root actor being edited by the current details panel
- L48 _public prototype_ `void CreateArrayBuilder(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder);` — Creates the child array builder that will be used to construct the cluster item selection array elements for the details panel
- L51 _public function_ `FDisplayClusterConfiguratorNodeSelection& IsEnabled(const TAttribute<bool>& InIsEnabled)` — Sets the IsEnabled attribute to use on the array property handle
- L58 _public prototype_ `static EOperationMode GetOperationModeFromProperty(FProperty* Property);` — Inspects the specified property's metadata to determine if the node selection array should show cluster nodes or viewports or icvfx cameras in its dropdown lists
- L61 _public prototype_ `void GenerateSelectionWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);` — Generates a widget to display the currently selected cluster item for the specified element in the array widget and adds it to the details panel
- L66 _protected prototype_ `void ResetOptions();` — Resets the list of cluster items to display in the dropdown lists for each element of the array widget
- L69 _protected prototype_ `TSharedRef<SWidget> MakeOptionComboWidget(TSharedPtr<FString> InItem);` — Constructs the text widget to display in the dropdown menu for the specified item
- L72 _protected prototype_ `void OnOptionSelected(TSharedPtr<FString> InValue, ESelectInfo::Type SelectInfo, TSharedRef<IPropertyHandle> InPropertyHandle);` — Raised when an item within the dropdown menu is selected
- L75 _protected prototype_ `FText GetSelectedOptionText(TSharedRef<IPropertyHandle> InPropertyHandle) const;` — Gets the display text for the currently selected item of the element in the array widget
- L79 _private member_ `TAttribute<bool> IsEnabledAttr;` — A custom attribute to apply to the array widget to determine if it is enabled or not
- L82 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> OptionsComboBox;` — The combo box widget to display for each element in the array widget
- L85 _private member_ `TArray<TSharedPtr<FString>> Options;` — The list of options to display in each combo box's dropdown menu
- L88 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr = nullptr;` — A weak reference to the current display cluster configuration editor, if the selected root actor is being edited as a CDO in a blueprint editor
- L91 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActorPtr;` — A weak reference to the current display cluster root actor that is being edited by the details panel
- L94 _private member_ `EOperationMode OperationMode = ClusterNodes;` — The operation mode which indicates whether to display cluster nodes, viewports, or ICVFX cameras in each element's combo box

#### enum `FDisplayClusterConfiguratorNodeSelection::EOperationMode`  
`enum EOperationMode`  
_L26-31_
- desc: Flag to indicate which cluster item is displayed in the dropdown menus of the elements of the array widget
- L28 _public enumerator_ `Viewports`
- L29 _public enumerator_ `ClusterNodes`
- L30 _public enumerator_ `ICVFXCameras`

#### class `FDisplayClusterConfiguratorOCIOProfileCustomization`  
`class FDisplayClusterConfiguratorOCIOProfileCustomization final : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L98-128_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterConfigurationOCIOProfile type, to customize the ApplyOCIOToObjects list property
- L102 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L107 _public function_ `virtual ~FDisplayClusterConfiguratorOCIOProfileCustomization() override`
- L114 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L115 _protected prototype_ `virtual void SetHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L116 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L121 _private member_ `TSharedPtr<FDisplayClusterConfiguratorNodeSelection> NodeSelection;` — The helper object used to generate the custom array widget to display in place of a string list for the ApplyOCIOToObjects property
- L124 _private member_ `FDisplayClusterConfiguratorNodeSelection::EOperationMode Mode = FDisplayClusterConfiguratorNodeSelection::EOperationMode::Viewports;` — Flag to indicate if the cluster items being displayed in the node selection widgets are viewports or cluster nodes
- L127 _private member_ `bool bIsDefaultDetailsDisplay = false;` — Indicates whether this customizer should display the default details panel instead of customizing the type's properties

#### class `FDisplayClusterConfiguratorPerViewportColorGradingCustomization`  
`class FDisplayClusterConfiguratorPerViewportColorGradingCustomization final : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L132-156_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterConfigurationViewport_PerViewportColorGrading type, to customize the ApplyPostProcessToObjects list property
- L136 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L141 _public function_ `virtual ~FDisplayClusterConfiguratorPerViewportColorGradingCustomization() override`
- L148 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L149 _protected prototype_ `virtual void SetHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L150 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L155 _private member_ `TSharedPtr<FDisplayClusterConfiguratorNodeSelection> NodeSelection;` — The helper object used to generate the custom array widget to display in place of a string list for the ApplyPostProcessToObjects property

#### class `FDisplayClusterConfiguratorPerNodeColorGradingCustomization`  
`class FDisplayClusterConfiguratorPerNodeColorGradingCustomization final : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L160-184_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterConfigurationViewport_PerNodeColorGrading type, to customize the ApplyPostProcessToObjects list property
- L164 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L169 _public function_ `virtual ~FDisplayClusterConfiguratorPerNodeColorGradingCustomization() override`
- L176 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L177 _protected prototype_ `virtual void SetHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L178 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L183 _private member_ `TSharedPtr<FDisplayClusterConfiguratorNodeSelection> NodeSelection;` — The helper object used to generate the custom array widget to display in place of a string list for the ApplyPostProcessToObjects property

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorRectangleCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorRectangleCustomization`  
`class FDisplayClusterConfiguratorRectangleCustomization : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L13-51_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Details panel customization for the FDisplayClusterConfigurationRectangle struct. Allows the rectangle to be displayed in a compound arrangement similar to how vectors can be displayed with their components editable in the header row of the property. Also supports a fixed aspect ratio toggle for the width and height of the rectangle
- L24 _public member_ `static const FName DisplayModeMetadataKey;` — Custom "DisplayMode" meatadata specifier to specify how the FDisplayClusterConfigurationRectangle struct gets displayed
- L27 _public member_ `static const FName FixedAspectRatioPropertyMetadataKey;` — Custom "FixedAspectRatioProperty" metadata specifier to specify a property for indicating if the aspect ratio of the rectangle is fixed
- L29 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L35 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L36 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L40 _private prototype_ `bool GetSizeRatioLocked() const;` — Gets whether the rectangle's aspect ratio is locked
- L43 _private prototype_ `void OnSizeRatioLockToggled(bool bNewValue);` — Raised when the aspect ratio lock is toggled
- L47 _private member_ `TSharedPtr<IPropertyHandle> FixedAspectRatioProperty;` — The property handle of the property to use as the aspect ratio toggle
- L50 _private member_ `EDisplayMode DisplayMode;` — The display mode of the rectangle being displayed

#### enum `FDisplayClusterConfiguratorRectangleCustomization::EDisplayMode`  
`enum EDisplayMode`  
_L17-21_
- desc: The display mode of the rectangle
- L19 _public enumerator_ `Compound`
- L20 _public enumerator_ `Default`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorViewportDetailsCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorViewportDetailsCustomization`  
`class FDisplayClusterConfiguratorViewportDetailsCustomization final : public FDisplayClusterConfiguratorBaseDetailCustomization`  
_L16-77_
- inherits: `FDisplayClusterConfiguratorBaseDetailCustomization`
- desc: Details panel customization for the UDisplayClusterConfigurationViewport object
- L19 _public typedef_ `using Super = FDisplayClusterConfiguratorBaseDetailCustomization;`
- L21 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InLayoutBuilder) override;`
- L32 _private prototype_ `void ResetCameraOptions();` — Rebuilds the list of cameras to show in the dropdown menu of the Camera property widget
- L35 _private prototype_ `TSharedRef<SWidget> CreateCustomCameraWidget();` — Creates a combo box widget to replace the default textbox of the Camera property of the UDisplayClusterConfigurationViewport
- L41 _private prototype_ `TSharedRef<SWidget> MakeCameraOptionComboWidget(TSharedPtr<FString> InItem);` — Creates a text block widget to use to display the specified item in the camera dropdown menu @param InItem - The string item to make the text block for
- L48 _private prototype_ `void OnCameraSelected(TSharedPtr<FString> InCamera, ESelectInfo::Type SelectInfo);` — Raised when a camera is selected from the camera dropdown menu @param InCamera - The camera item that was selected @param SelectionInfo - Flag to indicate through what interface the selection was made
- L51 _private prototype_ `FText GetSelectedCameraText() const;` — Gets the text to display for the currently selected camera
- L54 _private prototype_ `void CustomizeEnforcedCameraOrder(IDetailLayoutBuilder& InLayoutBuilder);` — Customizes the EnforcedCameraOrder array property with camera name dropdowns
- L58 _private member_ `TArray<TSharedPtr<FString>> CameraOptions;` — The list of camera items to display in the dropdown menu
- L61 _private member_ `TSharedPtr<IPropertyHandle> CameraHandle;` — The property handle for the Camera property of the UDisplayClusterConfigurationViewport object
- L64 _private member_ `TSharedPtr<FString> DefaultViewPointComponentNameOption;` — A cached pointer to the "DefaultViewPoint" option that is added to the list of options in the dropdown menu
- L67 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationViewport> ConfigurationViewportPtr;` — A weak reference to the UDisplayClusterConfigurationViewport object being edited by the details panel
- L70 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationData> ConfigurationDataPtr;` — A weak reference to the configratuion data object that owns the selected UDisplayClusterConfigurationViewport object
- L73 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> CameraComboBox;` — The combo box that is being displayed in the details panel for the Camera property
- L76 _private member_ `TSharedPtr<FDisplayClusterConfiguratorNodeSelection> CameraOrderNodeSelection;` — The helper object used to generate the custom array widget for the EnforcedCameraOrder property

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Cluster/DisplayClusterConfiguratorViewportRemapCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorViewportRemapCustomization`  
`class FDisplayClusterConfiguratorViewportRemapCustomization final : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L13-68_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterConfigurationViewport_RemapData struct
- L20 _public member_ `static const FName AngleIntervalMetadataKey;` — Custom "AngleInterval" metadata specifier that can be used to specify if the Angle property of the FDisplayClusterConfigurationViewport_RemapData struct is limited to fixed intervals
- L26 _public member_ `static const FName SimplifiedMetadataTag;` — Custom "Simplified" metadata specifier, which hides some of the advanced child properties of a FDisplayClusterConfigurationViewport_RemapData property
- L29 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates a new instance of the customization
- L36 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L37 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L42 _private prototype_ `void GenerateAnglesList();` — Generates the list of angles to display in the angle dropdown list, based on the angle interval metadata
- L45 _private prototype_ `void SelectionChanged(TSharedPtr<float> InValue, ESelectInfo::Type SelectInfo);` — Raised when an item within the dropdown menu is selected
- L48 _private prototype_ `TSharedRef<SWidget> GenerateWidget(TSharedPtr<float> InItem);` — Constructs the text widget to display in the dropdown menu for the specified item
- L51 _private prototype_ `FText GetSelectedAngleText() const;` — Gets the display text for the currently selected item of the element in the array widget
- L55 _private member_ `TSharedPtr<IPropertyHandle> AnglePropertyHandle;` — The property handle for the Angle property
- L58 _private member_ `TSharedPtr<SComboBox<TSharedPtr<float>>> AnglesComboBox;` — The combo box widget to display for the angle intervals
- L61 _private member_ `TArray<TSharedPtr<float>> AnglesList;` — The list of angles the user is allowed to select from
- L64 _private member_ `float AngleInterval;` — The interval to limit the allowed angle to
- L67 _private member_ `bool bSimplifiedDisplay;` — Indicates that the cusomization should hide the ViewportRegion and OutputRegion properties

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Components/DisplayClusterCameraComponentDetailsCustomization.h` (Private)


#### class `FDisplayClusterCameraComponentDetailsCustomization`  
`class FDisplayClusterCameraComponentDetailsCustomization final : public FDisplayClusterConfiguratorBaseDetailCustomization`  
_L14-84_
- inherits: `FDisplayClusterConfiguratorBaseDetailCustomization`
- desc: Details panel customization for the UDisplayClusterCameraComponent object
- L17 _public typedef_ `using Super = FDisplayClusterConfiguratorBaseDetailCustomization;`
- L19 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L31 _private prototype_ `void RebuildCameraOptions();` — Rebuilds the list of cameras to show in the dropdown menu of the Camera property widget
- L34 _private prototype_ `TSharedRef<SWidget> CreateCustomCameraWidget();` — Creates a combo box widget to replace the default textbox of the Camera property of the UDisplayClusterCameraComponent
- L40 _private prototype_ `TSharedRef<SWidget> MakeCameraOptionComboWidget(TSharedPtr<FString> InItem);` — Creates a text block widget to use to display the specified item in the camera dropdown menu @param InItem - The string item to make the text block for
- L47 _private prototype_ `void OnCameraSelected(TSharedPtr<FString> InCamera, ESelectInfo::Type SelectInfo);` — Raised when a camera is selected from the camera dropdown menu @param InCamera - The camera item that was selected @param SelectionInfo - Flag to indicate through what interface the selection was made
- L50 _private prototype_ `FText GetSelectedCameraText() const;` — Gets the text to display for the currently selected camera
- L53 _private prototype_ `void OnSelectComponentButton() const;` — When select component button is pressed.
- L56 _private prototype_ `FText GetSelectComponentButtonTooltipText() const;` — Return select component button tooltip text.
- L59 _private prototype_ `UClass* GetCameraComponentClass() const;` — Return camera component class.
- L64 _private member_ `TWeakObjectPtr<UDisplayClusterCameraComponent> EditedObject;` — A weak reference to the UDisplayClusterCameraComponent object being edited by the details panel
- L67 _private member_ `IDetailLayoutBuilder* DetailLayout = nullptr;` — Reference to the detail layout builder, used to force refresh the layout
- L71 _private member_ `TArray<TSharedPtr<FString>> CameraOptions;` — The list of camera items to display in the dropdown menu
- L74 _private member_ `TSharedPtr<IPropertyHandle> CameraHandle;` — The property handle for the Camera property of the UDisplayClusterCameraComponent object
- L77 _private member_ `TSharedPtr<FString> NoneOption;` — A cached pointer to the "None" option that is added to the list of options in the dropdown menu
- L80 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> CameraComboBox;` — The combo box that is being displayed in the details panel for the Camera property
- L83 _private member_ `TSharedPtr<SWidget> CameraComboBoxWidged;` — The widged that is being displayed in the details panel for the Camera property

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Components/DisplayClusterConfiguratorScreenComponentDetailsCustomization.h` (Private)


#### struct `FDisplayClusterConfiguratorAspectRatioPresetSize`  
`struct FDisplayClusterConfiguratorAspectRatioPresetSize`  
_L16-49_
- desc: Stores a size preset for the screen that cab be displayed and selected by the user.
- L19 _public function_ `FDisplayClusterConfiguratorAspectRatioPresetSize() : DisplayName(FText::GetEmpty()), Size(FVector2D::ZeroVector)`
- L24 _public function_ `FDisplayClusterConfiguratorAspectRatioPresetSize(FText InDisplayName, FVector2D InSize) : DisplayName(InDisplayName), Size(InSize)`
- L29 _public function_ `bool operator==(const FDisplayClusterConfiguratorAspectRatioPresetSize& Other) const`
- L35 _public function_ `double GetAspectRatio() const` — Calculates the aspect ratio of the preset based on its width and height
- L39 _public member_ `static const TArray<FDisplayClusterConfiguratorAspectRatioPresetSize> CommonPresets;` — A list of common presets of screen sizes
- L42 _public member_ `static const int32 DefaultPreset;` — The index of the preset to default to in the CommonPresets list
- L45 _public member_ `FText DisplayName;` — The display name of the preset
- L48 _public member_ `FVector2D Size;` — The width and height of the preset

#### class `FDisplayClusterConfiguratorScreenDetailsCustomization`  
`class FDisplayClusterConfiguratorScreenDetailsCustomization final : public IDetailCustomization`  
_L52-115_
- inherits: `IDetailCustomization`
- desc: Details panel customization for the UDisplayClusterConfigurationViewport object
- L55 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L62 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L67 _protected prototype_ `FText GetPresetsComboBoxSelectedText() const;` — Gets the text to display for the currently selected size preset of the screen
- L73 _protected prototype_ `FText GetPresetDisplayText(const TSharedPtr<FDisplayClusterConfiguratorAspectRatioPresetSize>& Preset) const;` — Gets the display text of the specified size preset @param Preset - The preset to get the display text for
- L79 _protected prototype_ `FText GetSelectedPresetDisplayText(const TSharedPtr<FDisplayClusterConfiguratorAspectRatioPresetSize>& Preset) const;` — Gets the text to display for the specified preset when it is the currently selected preset @param Preset - The preset to get the display text for when it is the selected preset
- L86 _protected prototype_ `void OnSelectedPresetChanged(TSharedPtr<FDisplayClusterConfiguratorAspectRatioPresetSize> SelectedPreset, ESelectInfo::Type SelectionType);` — Raised when the specified preset is selected from the dropdown menu @param SelectedPreset - The preset that was selected @param SelectionInfo - Flag to indicate through what interface the selection was made
- L93 _protected prototype_ `void GetAspectRatioAndSetDefaultValueForPreset(const FDisplayClusterConfiguratorAspectRatioPresetSize& Preset, FVector2D* OutAspectRatio = nullptr);` — Sets the value to default to on the selected object's archetype, and returns the default value's aspect ratio in the form of width and height. @param Preset - The preset to make the default value on the selected object's archetype @param OutAspectRatio - The aspect ratio, in the form of width and height, of the preset
- L98 _protected prototype_ `void OnSizePropertyChanged();` — Raised when the Size property of the selected screen component is changed
- L102 _private member_ `UDisplayClusterScreenComponent* ScreenComponentPtr = nullptr;` — A pointer to the current screen component being edited by the details panel.
- L105 _private member_ `TArray<TSharedPtr<FDisplayClusterConfiguratorAspectRatioPresetSize>> PresetItems;` — A list of presets to display in the size preset combo box
- L108 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FDisplayClusterConfiguratorAspectRatioPresetSize>>> PresetsComboBox;` — The size presets combo box widget to display in the screen component's details panel
- L111 _private member_ `TSharedPtr<IPropertyHandle> SizeHandlePtr;` — The property handle for the Size property of the selected screen component
- L114 _private member_ `bool bIsCustomAspectRatio = false;` — Indicates whether the user has entered a custom size into the Size property of the selected screen component

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Components/DisplayClusterICVFXCameraComponentDetailsCustomization.h` (Private)


#### class `FDisplayClusterICVFXCameraComponentDetailsCustomization`  
`class FDisplayClusterICVFXCameraComponentDetailsCustomization : public IDetailCustomization`  
_L14-30_
- inherits: `IDetailCustomization`
- desc: Details panel customization for the UDisplayClusterICVFXCameraComponent object
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L21 _protected prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& InLayoutBuilder) override;`
- L26 _protected member_ `TWeakObjectPtr<UDisplayClusterICVFXCameraComponent> EditedObject;` — A weak reference to the UDisplayClusterICVFXCameraComponent object being edited by the details panel
- L29 _protected member_ `IDetailLayoutBuilder* DetailLayout = nullptr;` — Reference to the detail layout builder, used to force refresh the layout

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/DisplayClusterConfiguratorBaseDetailCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorBaseDetailCustomization`  
`class FDisplayClusterConfiguratorBaseDetailCustomization : public IDetailCustomization`  
_L19-76_
- inherits: `IDetailCustomization`
- desc: A base class for details customization of UObjects in nDisplay. Contains support for common custom metadata specifiers.
- L26 _public member_ `static const FName HidePropertyMetaDataKey;` — Metadata specifier used to hide a property from an object's details panel. Used in cases where the property needs to have a Visible or Edit flag (such as being part of a property reference path), but should not show up in the details panel.
- L29 _public member_ `static const FName HidePropertyInstanceOnlyMetaDataKey;` — Similar to the HideProperty metadata specifier, but only hides the property when an instance object is being edited.
- L32 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L38 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InLayoutBuilder) override;` — IDetailCustomization interface
- L39 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InLayoutBuilder) override;`
- L50 _protected prototype_ `virtual void ProcessPropertyMetaData(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailLayoutBuilder& InLayoutBuilder);` — Processes any custom metadata specifiers for the specified property. Called on each child property of the object this details customization is applied to. Override to add additional processing for the object's child properties. @param InPropertyHandle - The property handle to process metadata specifiers on. @param InLayoutBuilder - The detail customization's layout builder.
- L53 _protected prototype_ `IDetailLayoutBuilder* GetLayoutBuilder() const;` — Gets a pointer to the details layout builder used by this customization
- L56 _protected prototype_ `FDisplayClusterConfiguratorBlueprintEditor* GetBlueprintEditor() const;` — Gets a pointer to the blueprint editor
- L59 _protected prototype_ `ADisplayClusterRootActor* GetRootActor() const;` — Gets a pointer to the display cluster root actor being edited by the details panel
- L62 _protected prototype_ `UDisplayClusterConfigurationData* GetConfigData() const;` — Gets a pointer to the display cluster configuration data of the root actor being edited by the details panel
- L65 _protected function_ `bool IsRunningForBlueprintEditor() const` — Gets whether the details panel is being displayed within the cluster configuration blueprint editor
- L69 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr = nullptr;` — A weak reference to the display cluster configuration blueprint editor, if the details panel is being displayed in one
- L72 _protected member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActorPtr;` — A weak reference to the display cluster root actor being edited by the details panel
- L75 _protected member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilder;` — A weak reference to the details layout builder used by this customization

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/DisplayClusterConfiguratorBaseTypeCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorBaseTypeCustomization`  
`class FDisplayClusterConfiguratorBaseTypeCustomization : public IPropertyTypeCustomization`  
_L16-102_
- inherits: `IPropertyTypeCustomization`
- desc: A base class for type customization of UStructs in nDisplay. Contains support for common custom metadata specifiers.
- L24 _public member_ `static const FName NoHeaderMetadataKey;` — Metadata specifier used to indicate that a type should not have a header to encapsulate its properties in a details panel; similar to ShowOnlyInnerProperties, but forces all child properties to be within the category the parent type belongs to, and is applied at any depth within a details panel.
- L27 _public member_ `static const FName HideChildrenMetadataKey;` — Metadata specifier used to indicate that a type should not display any of its child properties in a details panel.
- L30 _public member_ `static const FName SubstitutionsMetadataKey;` — Metadata specifier used specify substitutions to make to the display text of any of this type's child properties.
- L33 _public member_ `static const FName DefaultSubstitutionsMetadataKey;` — Metadata specifier used specify the default substitutions to make to the display text of any of this type's child properties when no substitutions are specified.
- L36 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L42 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L43 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L48 _protected prototype_ `TSharedPtr<IPropertyHandle> GetChildHandleChecked(const TSharedRef<IPropertyHandle>& InPropertyHandle, const FName& ChildPropertyName) const;` — Gets the child property handle from the specified property handle, and performs checks to ensure the child handle is valid.
- L51 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Initializes the type customization just before specifying the type's header, giving the customization the opportunity to initialize anything before generating the customized UI.
- L54 _protected prototype_ `virtual void SetHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Sets the header of the type customization. By default, sets the header to the property's default name and value widget. Override to customize the type's header.
- L57 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Sets the children of the type customization. By default, adds all of the type's children to the customized layout. Override to customize the type's children.
- L60 _protected prototype_ `void AddAllChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder);` — Adds all of the type's children to the customization's child builder.
- L63 _protected prototype_ `void FillSubstitutionMap(const TSharedRef<IPropertyHandle>& InPropertyHandle);` — Fills the substitutiom map to use for any text subsitutions using the metadata of the specified property handle
- L66 _protected prototype_ `void ParseSubstitutions(FFormatNamedArguments& OutSubstitutionsMap, const FString& InSubstitutionsStr) const;` — Parses the specified comma-deliminated substitution string into a list of key-value substitution pairs
- L67 _protected prototype_ `FText ApplySubstitutions(const FText& InText) const;`
- L70 _protected prototype_ `virtual bool ShouldShowHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle) const;` — Gets whether the type should display a header when displayed in a details panel. By default, check's the property's metadata for the NoHeader or ShowOnlyInnerProperties specifier.
- L73 _protected prototype_ `virtual bool ShouldShowChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle) const;` — Gets whether the type should display its children when displayed in a details panel. By default, check's the property's metadata for the HideChildren specifier.
- L76 _protected prototype_ `void RefreshBlueprint();` — Forces the currently edited blueprint to recompile and refresh is configuration
- L79 _protected prototype_ `void ModifyBlueprint();` — Marks the currently edited blueprint as modified
- L82 _protected prototype_ `ADisplayClusterRootActor* FindRootActor() const;` — Attempts to find the display cluster root actor that owns the type being customized.
- L85 _protected prototype_ `FDisplayClusterConfiguratorBlueprintEditor* FindBlueprintEditor() const;` — Attempts to find the blueprint editor editing the selected object, if the object is being edited in a blueprint editor.
- L88 _protected prototype_ `const FString* FindMetaData(TSharedPtr<IPropertyHandle> PropertyHandle, const FName& Key) const;` — Searches the specified property's instanced and default metadata maps for metadata using the specified key
- L92 _protected member_ `TWeakObjectPtr<UObject> EditingObject;` — A weak reference to the object being edited by the details panel
- L95 _protected member_ `TArray<TWeakObjectPtr<UObject>> EditingObjects;` — A list of weak references to the objects being edited by the details panel
- L98 _protected member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;` — A weak reference to the property utilities used by this type customization
- L101 _protected member_ `FFormatNamedArguments SubstitutionsMap;` — A list of substitutions that will be applied to the display text of each child property of the customized type

#### Free symbols / members of external scopes

- L11 _macro_ `#define GET_CHILD_HANDLE(ParentType, ChildName) GetChildHandleChecked(InPropertyHandle, GET_MEMBER_NAME_CHECKED(ParentType, ChildName))`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/DisplayClusterEditorPropertyReferenceTypeCustomization.h` (Private)


#### class `FDisplayClusterEditorPropertyReferenceTypeCustomization`  
`class FDisplayClusterEditorPropertyReferenceTypeCustomization : public IPropertyTypeCustomization`  
_L12-51_
- inherits: `IPropertyTypeCustomization`
- desc: A type customizer that expands a property reference to display the referenced property directly within a details panel.
- L15 _public typedef_ `typedef TPair<FText, TSharedPtr<IPropertyHandle>> FPropertyHandlePair;`
- L18 _public member_ `static const FName PropertyPathMetadataKey;` — Metadata specifier to provide the path to a property to display.
- L21 _public member_ `static const FName EditConditionPathMetadataKey;` — Metadata specifier to provide a path to a property to use as an edit condition.
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _private prototype_ `bool FindPropertyHandles(const FString& PropertyPath, TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L33 _private prototype_ `TSharedPtr<IPropertyHandle> FindPropertyHandle(const FString& PropertyPath, TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L35 _private prototype_ `TSharedPtr<IPropertyHandle> FindRootPropertyHandle(const FString& PropertyPath, TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L36 _private prototype_ `TSharedPtr<IPropertyHandle> GetChildPropertyHandle(const FString& PropertyName, TSharedPtr<IPropertyHandle>& PropertyHandle);`
- L38 _private prototype_ `void OnReferencedPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L40 _private prototype_ `bool IsListType(const TSharedPtr<IPropertyHandle>& PropertyHandle);`
- L42 _private prototype_ `TAttribute<bool> CreateEditConditional() const;`
- L43 _private prototype_ `bool IsEditable() const;`
- L46 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities = nullptr;` — Customization utils instance to trigger GUI update on referenced value changes
- L48 _private member_ `TArray<FPropertyHandlePair> ReferencedPropertyHandles;`
- L49 _private member_ `TArray<TSharedRef<IPropertyHandle>> EditConditionPropertyHandles;`
- L50 _private member_ `bool bIsIteratedList;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/DisplayClusterRootActorDetailsCustomization.h` (Private)


#### class `FDisplayClusterRootActorDetailsCustomization`  
`class FDisplayClusterRootActorDetailsCustomization final : public FDisplayClusterConfiguratorBaseDetailCustomization`  
_L18-51_
- inherits: `FDisplayClusterConfiguratorBaseDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L23 _public prototype_ `~FDisplayClusterRootActorDetailsCustomization();`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InLayoutBuilder) override;` — IDetailCustomization interface
- L31 _private prototype_ `TSharedRef<SWidget> CreateCustomNodeIdWidget();`
- L32 _private prototype_ `bool RebuildNodeIdOptionsList();`
- L33 _private prototype_ `void UpdateNodeIdSelection();`
- L35 _private prototype_ `void OnNodeIdSelected(TSharedPtr<FString> NodeId, ESelectInfo::Type SelectInfo);`
- L36 _private prototype_ `FText GetSelectedNodeIdText() const;`
- L37 _private prototype_ `TSharedRef<SWidget> CreateComboWidget(TSharedPtr<FString> InItem);`
- L39 _private prototype_ `void OnForcePropertyWindowRebuild(UObject* Object);`
- L42 _private member_ `FDelegateHandle ForcePropertyWindowRebuildHandle;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> PreviewNodeIdHandle;`
- L46 _private member_ `TArray<TSharedPtr<FString>> NodeIdOptions;`
- L47 _private member_ `TSharedPtr<FString> NodeIdOptionNone;`
- L48 _private member_ `TSharedPtr<SSearchableComboBox> NodeIdComboBox;`
- L50 _private member_ `bool bMultipleObjectsSelected;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DCConfiguratorBaseMediaCustomization.h` (Private)


#### class `FDCConfiguratorBaseMediaCustomization`  
`class FDCConfiguratorBaseMediaCustomization : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L13-31_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Base customization class. Provides some common functionality for concrete implementations.
- L19 _public prototype_ `virtual ~FDCConfiguratorBaseMediaCustomization() = default;` — Abstract
- L24 _protected prototype_ `void AddResetButton(IDetailChildrenBuilder& ChildBuilder, const FText& ButtonText);` — Builds reset button widget.
- L27 _protected prototype_ `FReply OnResetButtonClicked();` — Handles reset button clicks.
- L30 _protected prototype_ `void MarkDirty();` — Marks package as dirty

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DCConfiguratorClusterNodeMediaCustomization.h` (Private)


#### class `FDCConfiguratorClusterNodeMediaCustomization`  
`class FDCConfiguratorClusterNodeMediaCustomization : public FDCConfiguratorBaseMediaCustomization`  
_L11-30_
- inherits: `FDCConfiguratorBaseMediaCustomization`
- desc: Details panel customization for 'FDisplayClusterConfigurationMediaNodeBackbuffer' struct.
- L16 _private typedef_ `using Super = FDCConfiguratorBaseMediaCustomization;`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L28 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DCConfiguratorICVFXMediaCustomization.h` (Private)


#### class `FDCConfiguratorICVFXMediaCustomization`  
`class FDCConfiguratorICVFXMediaCustomization : public FDCConfiguratorBaseMediaCustomization`  
_L17-49_
- inherits: `FDCConfiguratorBaseMediaCustomization`
- desc: Details panel customization for the FDisplayClusterConfigurationMediaICVFX struct.
- L22 _private typedef_ `using Super = FDCConfiguratorBaseMediaCustomization;`
- L26 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L34 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L40 _private prototype_ `void AddConfigureTilesButton(IDetailChildrenBuilder& ChildBuilder);` — Builds the button widget for tiles configuration.
- L43 _private prototype_ `FReply OnConfigureTilesButtonClicked();` — Handles configure tiles button clicks.
- L48 _private prototype_ `UDisplayClusterConfigurationData* GetConfig() const;` — Returns configuration of a DCRA owning the camera being edited.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DCConfiguratorViewportMediaCustomization.h` (Private)


#### class `FDCConfiguratorViewportMediaCustomization`  
`class FDCConfiguratorViewportMediaCustomization : public FDCConfiguratorBaseMediaCustomization`  
_L11-30_
- inherits: `FDCConfiguratorBaseMediaCustomization`
- desc: Details panel customization for 'FDisplayClusterConfigurationMediaViewport' struct.
- L16 _private typedef_ `using Super = FDCConfiguratorBaseMediaCustomization;`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L28 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DisplayClusterConfiguratorMediaCustomizationBase.h` (Private)


#### class `FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`  
`class FDisplayClusterConfiguratorMediaFullFrameCustomizationBase : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L18-68_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Base class for full frame media input & output customization
- L22 _public prototype_ `FDisplayClusterConfiguratorMediaFullFrameCustomizationBase();`
- L23 _public prototype_ `~FDisplayClusterConfiguratorMediaFullFrameCustomizationBase();`
- L28 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _protected prototype_ `void ModifyMediaObjectParameters();` — Entry point to modify media objects.
- L37 _protected prototype_ `virtual bool PerformMediaInitialization(UObject* Owner, UObject* MediaObject, IDisplayClusterModularFeatureMediaInitializer* Initializer);` — Virtual media initialization depending on media type (full-frame, split, etc.)
- L40 _protected prototype_ `AActor* GetOwningActor() const;` — Returns the actor that owns the object being edited.
- L43 _protected prototype_ `bool GetOwnerData(const UObject* Owner, FMediaObjectOwnerInfo& OutOwnerInfo) const;` — Returns the name of media object's owner.
- L48 _private prototype_ `bool GetOwnerData(const UDisplayClusterICVFXCameraComponent* ICVFXCameraComponent, FMediaObjectOwnerInfo& OutOwnerInfo) const;` — Helper data provider for ICVFX cameras.
- L51 _private prototype_ `bool GetOwnerData(const UDisplayClusterConfigurationViewport* ViewportCfg, FMediaObjectOwnerInfo& OutOwnerInfo) const;` — Helper data provider for viewports.
- L54 _private prototype_ `bool GetOwnerData(const UDisplayClusterConfigurationClusterNode* NodeCfg, FMediaObjectOwnerInfo& OutOwnerInfo) const;` — Helper data provider for cluster nodes.
- L59 _private prototype_ `void OnMediaObjectChanged();` — Handles media source/output change callbacks
- L62 _private prototype_ `void OnAutoConfigureRequested(UObject* EditingObject);` — Auto-configuration requests handler
- L67 _protected member_ `TSharedPtr<IPropertyHandle> MediaObjectHandle;` — MediaSource or MediaOutput property handle, depending on the child implementation.

#### class `FDisplayClusterConfiguratorMediaTileCustomizationBase`  
`class FDisplayClusterConfiguratorMediaTileCustomizationBase : public FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`  
_L75-107_
- inherits: `FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`
- desc: Base class for tiled media input & output customization
- L81 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L89 _protected prototype_ `virtual bool PerformMediaInitialization(UObject* Owner, UObject* MediaObject, IDisplayClusterModularFeatureMediaInitializer* Initializer) override;` — Virtual media initialization depending on media type (full-frame, split, etc.)
- L96 _private prototype_ `FIntPoint GetEditedTilePos() const;` — Returns tile position currently set.
- L101 _private prototype_ `void OnTilePositionChanged();` — Handles tile position change callbacks
- L106 _protected member_ `TSharedPtr<IPropertyHandle> TilePosHandle;` — Tile position property handle.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DisplayClusterConfiguratorMediaCustomizationCVars.h` (Private)


#### Free symbols / members of external scopes

- L9 _externvar_ `extern TAutoConsoleVariable<bool> CVarMediaAutoInitializationEnabled;` — Enable/disable live auto-configuration. Does not affect "auto-configure" button.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DisplayClusterConfiguratorMediaFullFrameCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorMediaFullFrameInputCustomization`  
`class FDisplayClusterConfiguratorMediaFullFrameInputCustomization : public FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`  
_L12-25_
- inherits: `FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`
- desc: Details panel customization for FDisplayClusterConfigurationMediaUniformTileInput struct (input tiles).
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### class `FDisplayClusterConfiguratorMediaFullFrameOutputCustomization`  
`class FDisplayClusterConfiguratorMediaFullFrameOutputCustomization : public FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`  
_L31-44_
- inherits: `FDisplayClusterConfiguratorMediaFullFrameCustomizationBase`
- desc: Details panel customization for FDisplayClusterConfigurationMediaUniformTileOutput struct (output tiles).
- L35 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L42 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DisplayClusterConfiguratorMediaTileCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorMediaInputTileCustomization`  
`class FDisplayClusterConfiguratorMediaInputTileCustomization : public FDisplayClusterConfiguratorMediaTileCustomizationBase`  
_L12-25_
- inherits: `FDisplayClusterConfiguratorMediaTileCustomizationBase`
- desc: Details panel customization for FDisplayClusterConfigurationMediaUniformTileInput struct (input tiles).
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### class `FDisplayClusterConfiguratorMediaOutputTileCustomization`  
`class FDisplayClusterConfiguratorMediaOutputTileCustomization : public FDisplayClusterConfiguratorMediaTileCustomizationBase`  
_L31-44_
- inherits: `FDisplayClusterConfiguratorMediaTileCustomizationBase`
- desc: Details panel customization for FDisplayClusterConfigurationMediaUniformTileOutput struct (output tiles).
- L35 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L42 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/DisplayClusterConfiguratorMediaUtils.h` (Private)


#### class `FDisplayClusterConfiguratorMediaUtils`  
`class FDisplayClusterConfiguratorMediaUtils`  
_L12-44_
- desc: Media customization utilities
- L15 _protected prototype_ `FDisplayClusterConfiguratorMediaUtils();`
- L20 _public prototype_ `static FDisplayClusterConfiguratorMediaUtils& Get();` — Singleton access
- L25 _public function_ `const TArray<IDisplayClusterModularFeatureMediaInitializer*>& GetMediaInitializers() const` — Returns media initializers
- L31 _public prototype_ `DECLARE_EVENT_OneParam(FDisplayClusterConfiguratorMediaUtils, FResetToDefaultsEvent, UObject*);` — Tiled media auto-configuration event
- L32 _public function_ `FResetToDefaultsEvent& OnMediaResetToDefaults()`
- L40 _private member_ `TArray<IDisplayClusterModularFeatureMediaInitializer*> MediaInitializers;` — Media initializers (modular features) available.
- L43 _private member_ `FResetToDefaultsEvent MediaResetToDefaultsEvent;` — Tiled media reset to defaults event

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_EVENT_OneParam(FDisplayClusterConfiguratorMediaUtils, FResetToDefaultsEvent, UObject*);` — Tiled media auto-configuration event

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Media/SMediaTilesConfigurationDialog.h` (Private)


#### struct `FMediaTilesConfigurationDialogParameters`  
`struct FMediaTilesConfigurationDialogParameters`  
_L29-58_
- desc: Tiled media configuration dialog parameters.
- L32 _public member_ `const UDisplayClusterConfigurationData* ConfigData = nullptr;` — Configuration data of a DCRA being edited.
- L35 _public member_ `TObjectPtr<UObject> Owner;` — An object owning the configuration data being edited.
- L38 _public member_ `bool bAutoPreconfigureOutputMapping = true;` — Whether output mapping should be pre-configured automatically.
- L41 _public member_ `FIntPoint* SplitLayout = nullptr;` — Layout ref of a DCRA's entity being edited.
- L44 _public member_ `TArray<FDisplayClusterConfigurationMediaTiledInputGroup>* InputGroups = nullptr;` — Input groups ref of a DCRA's entity being edited.
- L47 _public member_ `TArray<FDisplayClusterConfigurationMediaTiledOutputGroup>* OutputGroups = nullptr;` — Output groups ref of a DCRA's entity being edited.
- L52 _public function_ `bool Validate() const` — Config parameters validation.

#### class `SMediaTilesConfigurationDialog`  
`class SMediaTilesConfigurationDialog : public SWindow`  
_L64-364_
- inherits: `SWindow`
- desc: Configuration dialog for tiled media
- L68 _public function_ `SLATE_BEGIN_ARGS(SMediaTilesConfigurationDialog)`
- L70 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FMediaTilesConfigurationDialogParameters& InParameters);`
- L77 _public prototype_ `bool WasConfigurationCompleted() const;` — Returns true if configuration was completed.
- L82 _private prototype_ `void InitializeInternals();` — Initializes internal data.
- L85 _private prototype_ `bool IsFinishButtonEnabled() const;` — Returns true if 'Finish' button should be active.
- L88 _private prototype_ `void OnFinishButtonClicked();` — 'Finish' button handler.
- L91 _private prototype_ `void OnCancelButtonClicked();` — 'Cancel' button handler.
- L96 _private prototype_ `bool ApplyConfiguration(TArray<FString>& OutErrors, TArray<FString>& OutWarnings);` — Apply configuration entry point.
- L99 _private prototype_ `bool ApplyConfiguration_Multicast(TArray<FString>& OutErrors, TArray<FString>& OutWarnings);` — Apply configuration for 'Multicast' media.
- L102 _private prototype_ `bool ApplyConfiguration_LocalMulticast(TArray<FString>& OutErrors, TArray<FString>& OutWarnings);` — Apply configuration for 'LocalMulticast' media.
- L107 _private prototype_ `void GenerateIssuesFoundMessage(const TArray<FString>& Errors, const TArray<FString>& Warnings, FText& OutMessage) const;` — Helper function to generate a message with the issues found.
- L110 _private prototype_ `bool IsMediaObjectSupported(const UObject* MediaObject) const;` — Helper function to check if specific media object is supported for auto-configuration
- L113 _private prototype_ `bool AreMediaObjectsCompatible(const UObject* InMediaSource, const UObject* InMediaOutput) const;` — Helper function to check if specific media objects are compatible to each other
- L116 _private prototype_ `bool GetMediaPropagationTypes(const UObject* InMediaSource, const UObject* InMediaOutput, EMediaStreamPropagationType& OutPropagationFlags) const;` — Helper function to get media propagation types from a media initializer
- L125 _private prototype_ `TSharedRef<SWidget> PageLayout_Build();` — Builds layout page.
- L128 _private prototype_ `void PageLayout_OnEnter();` — Callback on layout page enter.
- L131 _private prototype_ `bool PageLayout_IsConfigurationValid() const;` — Returns true if layout configuration is valid.
- L134 _private prototype_ `void PageLayout_OnGridCellClicked(const FIntPoint& Tile);` — Cell click handler.
- L137 _private prototype_ `void PageLayout_OnGridCellHovered(const FIntPoint& Tile);` — Cell hover handler.
- L140 _private prototype_ `void PageLayout_OnGridCellUnhovered();` — Cell unhover handler.
- L143 _private prototype_ `void PageLayout_RefreshGridLayout();` — Refresh current cell states.
- L151 _private prototype_ `TSharedRef<SWidget> PageMedia_Build();` — Builds media objects page.
- L154 _private prototype_ `TSharedRef<SWidget> PageMedia_BuildClassPicker(UClass* FilterClass);` — Builds media class picker widget.
- L157 _private prototype_ `bool PageMedia_OnCanShow() const;` — Callback to check if we can switch to the media objects configuration page.
- L160 _private prototype_ `void PageMedia_OnEnter();` — Callback on media objects page enter.
- L163 _private prototype_ `bool PageMedia_IsConfigurationValid() const;` — Returns true if media objects configuration is valid.
- L166 _private prototype_ `void PageMedia_OnMediaSourceChanged(UClass* InNewClass);` — Media source change handler.
- L169 _private prototype_ `void PageMedia_OnMediaOutputChanged(UClass* InNewClass);` — Media output change handler.
- L172 _private prototype_ `void PageMedia_UpdateMessage();` — Updates configuration message/feedback.
- L180 _private prototype_ `TSharedRef<SWidget> PageNodes_Build();` — Builds nodes selection page.
- L183 _private prototype_ `TSharedRef<SWidget> PageNodes_BuildSelSection(const FText& Header, const TSet<FString>& AllowedItems, TSet<FString>& CurrentSelection);` — Builds intput/output section.
- L186 _private prototype_ `TSharedRef<SWidget> PageNodes_BuildNodePicker(const TSet<FString>& AllowedItems, TSet<FString>& CurrentSelection);` — Builds node picker widget for input/output mapping.
- L189 _private prototype_ `FReply PageNodes_OnMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& PointerEvent, bool bOutputSelection);` — Mouse click handler (for context menu).
- L192 _private prototype_ `void PageNodes_CreateContextMenu(const FVector2D& CursorPosition, bool bOutputSelection);` — Mouse click handler (for context menu).
- L195 _private prototype_ `void PageNodes_Menu_OnChangeSelectionAll(bool bOutputSelection, bool bSelected);` — Context menu handler: Select/Deselect All.
- L198 _private prototype_ `void PageNodes_Menu_OnSelectAllExceptOfCounterpart(bool bOutputSelection);` — Context menu handler: Select all items in A that aren't selected in B (A-Bsel).
- L201 _private prototype_ `void PageNodes_Menu_OnDeselectAllFromCounterpart(bool bOutputSelection);` — Context menu handler: Deselect all items in A that are selected in B (Asel-Bsel).
- L204 _private prototype_ `void PageNodes_Menu_OnSelectDeselectAllOnOffscreen(bool bOutputSelection, bool bSelect, bool bOffscreen);` — Context menu handler: Select all onscreen/offscreen nodes.
- L207 _private prototype_ `bool PageNodes_OnCanShow() const;` — Callback to check if we can switch to the nodes selection page.
- L210 _private prototype_ `void PageNodes_OnEnter();` — Callback on nodes selection page enter.
- L213 _private prototype_ `bool PageNodes_IsConfigurationValid() const;` — Returns true if nodes selection is valid.
- L221 _private prototype_ `TSharedRef<SWidget> PageFinalization_Build();` — Builds finalization page.
- L224 _private prototype_ `TSharedRef<SWidget> PageFinalization_BuildOutputTileButtonContent(const FIntPoint& Tile);` — Builds tile button content.
- L227 _private prototype_ `TSharedRef<SWidget> PageFinalization_BuildOutputTileButtonDropdownContent(const FIntPoint& Tile);` — Builds output mapping dropdown content.
- L230 _private prototype_ `bool PageFinalization_OnCanShow() const;` — Callback to check if we can switch to the media groups configuration page.
- L233 _private prototype_ `void PageFinalization_OnEnter();` — Callback on media groups page enter.
- L236 _private prototype_ `void PageFinalization_ResetOutputMapping();` — Reset current output mapping.
- L239 _private prototype_ `void PageFinalization_PresetupOutputs();` — Pre-configures output mapping.
- L242 _private prototype_ `void PageFinalization_PresetupOutputs_LocalMulticast();` — Pre-configures output mapping for local multicast (like SharedMemoryMedia).
- L245 _private prototype_ `void PageFinalization_PresetupOutputs_Multicast();` — Pre-configures output mapping for multicast (like Rivermax).
- L248 _private prototype_ `void PageFinalization_RegenerateGrid();` — Regenerates grid data to match current layout.
- L251 _private prototype_ `bool PageFinalization_IsConfigurationValid() const;` — Returns true if media groups configuration is valid.
- L254 _private prototype_ `void PageFinalization_UpdateTileButtonContent(const FIntPoint& Tile);` — Updates cell content.
- L257 _private prototype_ `FSlateColor PageFinalization_GetButtonColor(const FIntPoint& Tile);` — Returns cell color for its current state.
- L262 _private member_ `static constexpr int32 MaxTilesAmount = 4;` — Tile layout constraints.
- L265 _private member_ `FMediaTilesConfigurationDialogParameters Parameters;` — External configuration parameters.
- L268 _private member_ `TSet<FString> ClusterNodeIds;` — List of all cluster node IDs.
- L271 _private member_ `TSet<FString> OffscreenNodes;` — List of all offscreen nodes.
- L274 _private member_ `TMap<FString, FString> NodeToHostMap;` — Node-to-host map.
- L277 _private member_ `TMap<FString, TSet<FString>> HostToNodesMap;` — Cluster nodes per host.
- L280 _private member_ `bool bConfigurationCompleted = false;` — Whether user completed configuration.
- L283 _private member_ `TSharedPtr<STextBlock> PageHint;` — Page hint.
- L286 _private member_ `TSharedPtr<SWizard> Wizard;` — Wizard widget.
- L290 _private member_ `TMap<FIntPoint, TSharedPtr<SButton>> LayoutGridButtons;` — [Layout] Button widgets representing tile layout.
- L293 _private member_ `const int32 LayoutGridCellSize = 80;` — [Layout] Layout grid cell size.
- L296 _private member_ `FIntPoint Hovered = { -1, -1 };` — [Layout] Current 'hover' postion.
- L299 _private member_ `FIntPoint Accepted = { -1, -1 };` — [Layout] Last 'accepted' position.
- L303 _private member_ `TSharedPtr<SImage> MediaSourceStatusImage;` — [Media] Status image for media source.
- L306 _private member_ `TSharedPtr<SImage> MediaOutputStatusImage;` — [Media] Status image for media output.
- L309 _private member_ `TSharedPtr<STextBlock> MediaSourceStatusText;` — [Media] Status text for media source.
- L312 _private member_ `TSharedPtr<STextBlock> MediaOutputStatusText;` — [Media] Status text for media output.
- L315 _private member_ `TSharedPtr<STextBlock> MediaSourceSelectedName;` — [Media] Currently selected media source name (button text).
- L318 _private member_ `TSharedPtr<STextBlock> MediaOutputSelectedName;` — [Media] Currently selected media output name (button text).
- L321 _private member_ `TStrongObjectPtr<UMediaSource> MediaSource;` — [Media] Media source template choosed by user.
- L324 _private member_ `TStrongObjectPtr<UMediaOutput> MediaOutput;` — [Media] Media output template choosed by user.
- L327 _private member_ `EMediaStreamPropagationType MediaPropagationTypes = static_cast<EMediaStreamPropagationType>(0);` — [Media] Stream propagation type (unicast, multicast, etc.).
- L331 _private member_ `TSet<FString> NodesAllowedForInput;` — [Nodes] Nodes allowed to be picked for input (allowed for receiving).
- L334 _private member_ `TSet<FString> NodesAllowedForOutput;` — [Nodes] Nodes allowed to be picked for output (allowed for sending).
- L337 _private member_ `TSet<FString> InputSelection;` — [Nodes] Input nodes selection.
- L340 _private member_ `TSet<FString> OutputSelection;` — [Nodes] Output nodes selection.
- L344 _private member_ `TSharedPtr<SUniformGridPanel> OutputMappingGrid;` — [Finalization] Output mapping widget.
- L347 _private member_ `const int32 OutputMappingGridCellSize = 150;` — [Finalization] Output mapping grid cell size.
- L363 _private member_ `TMap<FIntPoint, FOutputMappingData> OutputMapping;` — [Finalization] Tile output mapping.

#### struct `SMediaTilesConfigurationDialog::FOutputMappingData`  
`struct FOutputMappingData`  
_L350-360_
- desc: [Finalization] Helper container for output tile mapping.
- L353 _public member_ `TSharedPtr<SComboButton> ButtonWidget;` — A drop-down button widget representing a tile (grid cell)
- L356 _public member_ `TSharedPtr<SVerticalBox> ButtonContentWidget;` — A drop-down content widget for the button above
- L359 _public member_ `TSet<FString> ClusterNodes;` — Cluster nodes associated with this tile (grid cell)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Policies/DisplayClusterConfiguratorPolicyDetailCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorProjectionCustomization`  
`class FDisplayClusterConfiguratorProjectionCustomization final : public FDisplayClusterConfiguratorPolymorphicEntityCustomization`  
_L28-89_
- inherits: `FDisplayClusterConfiguratorPolymorphicEntityCustomization`
- desc: Projection Type Customization
- L32 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L38 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L39 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L43 _protected prototype_ `EVisibility GetCustomRowsVisibility() const;`
- L44 _protected prototype_ `TSharedRef<SWidget> MakeProjectionPolicyOptionComboWidget(TSharedPtr<FString> InItem);`
- L45 _protected prototype_ `void ResetProjectionPolicyOptions();`
- L46 _protected prototype_ `void AddProjectionPolicyRow(IDetailChildrenBuilder& InChildBuilder);`
- L47 _protected prototype_ `void AddCustomPolicyRow(IDetailChildrenBuilder& InChildBuilder);`
- L48 _protected prototype_ `void OnProjectionPolicySelected(TSharedPtr<FString> InPolicy, ESelectInfo::Type SelectInfo);`
- L49 _protected prototype_ `FText GetSelectedProjectionPolicyText() const;`
- L50 _protected prototype_ `FText GetCustomPolicyText() const;`
- L52 _protected prototype_ `const FString& GetCurrentPolicy() const;` — Return either custom policy or selected policy.
- L53 _protected prototype_ `bool IsCustomTypeInConfig() const;`
- L54 _protected prototype_ `void OnTextCommittedInCustomPolicyText(const FText& InValue, ETextCommit::Type CommitType);`
- L55 _protected prototype_ `bool IsPolicyIdenticalAcrossEditedObjects(bool bRequireCustomPolicy = false) const;`
- L57 _private member_ `TSharedPtr<FString> CustomOption;`
- L58 _private member_ `TArray< TSharedPtr<FString> > ProjectionPolicyOptions;`
- L59 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> ProjectionPolicyComboBox;`
- L60 _private member_ `TSharedPtr<SEditableTextBox> CustomPolicyRow;`
- L61 _private member_ `FString CurrentSelectedPolicy;`
- L62 _private member_ `FString CustomPolicy;`
- L63 _private member_ `bool bIsCustomPolicy = false;`
- L69 _private prototype_ `void BuildParametersForPolicy(const FString& Policy, IDetailChildrenBuilder& InChildBuilder);` — Given a policy create all parameters.
- L71 _private prototype_ `void CreateSimplePolicy(UDisplayClusterBlueprint* Blueprint);`
- L72 _private prototype_ `void CreateCameraPolicy(UDisplayClusterBlueprint* Blueprint);`
- L73 _private prototype_ `void CreateMeshPolicy(UDisplayClusterBlueprint* Blueprint);`
- L74 _private prototype_ `void CreateDomePolicy(UDisplayClusterBlueprint* Blueprint);`
- L75 _private prototype_ `void CreateVIOSOPolicy(UDisplayClusterBlueprint* Blueprint);`
- L76 _private prototype_ `void CreateEasyBlendPolicy(UDisplayClusterBlueprint* Blueprint);`
- L77 _private prototype_ `void CreateManualPolicy(UDisplayClusterBlueprint* Blueprint);`
- L78 _private prototype_ `void CreateMPCDIPolicy(UDisplayClusterBlueprint* Blueprint);`
- L79 _private prototype_ `void CreateReferencePolicy(UDisplayClusterBlueprint* Blueprint);`
- L83 _private member_ `TArray<TSharedPtr<FPolicyParameterInfo>> CustomPolicyParameters;` — All custom parameters for the selected policy.
- L87 _private member_ `TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>> ConfigurationViewports;`
- L88 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationViewport> ConfigurationViewportPtr;`

#### class `FDisplayClusterConfiguratorRenderSyncPolicyCustomization`  
`class FDisplayClusterConfiguratorRenderSyncPolicyCustomization final : public FDisplayClusterConfiguratorPolymorphicEntityCustomization`  
_L95-154_
- inherits: `FDisplayClusterConfiguratorPolymorphicEntityCustomization`
- desc: Render Sync Type Customization
- L99 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L105 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L106 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L109 _private prototype_ `EVisibility GetCustomRowsVisibility() const;`
- L110 _private prototype_ `EVisibility GetNvidiaPolicyRowsVisibility() const;`
- L112 _private prototype_ `void ResetRenderSyncPolicyOptions();`
- L113 _private prototype_ `void AddRenderSyncPolicyRow(IDetailChildrenBuilder& InChildBuilder);`
- L114 _private prototype_ `void AddNvidiaPolicyRows(IDetailChildrenBuilder& InChildBuilder);`
- L115 _private prototype_ `void AddCustomPolicyRow(IDetailChildrenBuilder& InChildBuilder);`
- L117 _private prototype_ `TSharedRef<SWidget> MakeRenderSyncPolicyOptionComboWidget(TSharedPtr<FString> InItem);`
- L118 _private prototype_ `void OnRenderSyncPolicySelected(TSharedPtr<FString> InPolicy, ESelectInfo::Type SelectInfo);`
- L120 _private prototype_ `FText GetSelectedRenderSyncPolicyText() const;`
- L121 _private prototype_ `FText GetCustomPolicyText() const;`
- L123 _private prototype_ `bool IsCustomTypeInConfig() const;`
- L125 _private prototype_ `int32 GetPolicyTypeIndex(const FString& Type) const;`
- L127 _private prototype_ `void OnTextCommittedInCustomPolicyText(const FText& InValue, ETextCommit::Type CommitType);`
- L129 _private prototype_ `void AddToParameterMap(const FString& Key, const FString& Value);`
- L130 _private prototype_ `void RemoveFromParameterMap(const FString& Key);`
- L133 _private member_ `TSharedPtr<FString> NvidiaOption;`
- L134 _private member_ `TSharedPtr<FString> CustomOption;`
- L136 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationCluster> ConfigurationClusterPtr;`
- L138 _private member_ `TArray<TSharedPtr<FString>> RenderSyncPolicyOptions;`
- L140 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> RenderSyncPolicyComboBox;`
- L141 _private member_ `TSharedPtr<SSpinBox<int32>> SwapGroupSpinBox;`
- L142 _private member_ `TSharedPtr<SSpinBox<int32>> SwapBarrierSpinBox;`
- L144 _private member_ `int32 SwapGroupValue = 0;`
- L145 _private member_ `int32 SwapBarrierValue = 0;`
- L147 _private member_ `TSharedPtr<SEditableTextBox> CustomPolicyRow;`
- L148 _private member_ `bool bIsCustomPolicy = false;`
- L149 _private member_ `FString CustomPolicy;`
- L152 _private member_ `const static FString SwapGroupName;`
- L153 _private member_ `const static FString SwapBarrierName;`

#### class `FDisplayClusterConfiguratorInputSyncPolicyCustomization`  
`class FDisplayClusterConfiguratorInputSyncPolicyCustomization final : public FDisplayClusterConfiguratorPolymorphicEntityCustomization`  
_L159-186_
- inherits: `FDisplayClusterConfiguratorPolymorphicEntityCustomization`
- desc: Input Sync Type Customization
- L163 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L169 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L170 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L173 _private prototype_ `void ResetInputSyncPolicyOptions();`
- L175 _private prototype_ `void AddInputSyncPolicyRow(IDetailChildrenBuilder& InChildBuilder);`
- L177 _private prototype_ `TSharedRef<SWidget> MakeInputSyncPolicyOptionComboWidget(TSharedPtr<FString> InItem);`
- L178 _private prototype_ `void OnInputSyncPolicySelected(TSharedPtr<FString> InPolicy, ESelectInfo::Type SelectInfo);`
- L180 _private prototype_ `FText GetSelectedInputSyncPolicyText() const;`
- L183 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationCluster> ConfigurationClusterPtr;`
- L184 _private member_ `TArray<TSharedPtr<FString>> InputSyncPolicyOptions;`
- L185 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> InputSyncPolicyComboBox;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Policies/DisplayClusterConfiguratorPolicyParameterCustomization.h` (Private)


#### class `FPolicyParameterInfo`  
`class FPolicyParameterInfo : public TSharedFromThis<FPolicyParameterInfo>`  
_L28-102_
- inherits: `TSharedFromThis<FPolicyParameterInfo>`
- desc: Individual policy parameter data base class.
- L31 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EVisibility, FParameterVisible, FText);`
- L34 _public prototype_ `FPolicyParameterInfo( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const FString* InInitialValue = nullptr);`
- L41 _public function_ `virtual ~FPolicyParameterInfo()`
- L44 _public function_ `FText GetParameterDisplayName() const` — The friendly display name for this parameter.
- L47 _public function_ `FText GetParameterTooltip() const` — Gets the tooltip for this parameter.
- L50 _public function_ `void SetParameterTooltip(const FText& NewTooltip)` — Sets the tooltip for this parameter.
- L53 _public function_ `const FString& GetParameterKey() const` — The keu used for the parameter map.
- L56 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) = 0;` — Create the widget representation of this parameter and add it as a child row.
- L59 _public prototype_ `void SetParameterVisibilityDelegate(FParameterVisible InDelegate);` — This delegate will be used to determine visibility.
- L62 _public prototype_ `FText GetOrAddCustomParameterValueText() const;` — Retrieve (or add) the parameter information from the viewport data object.
- L66 _protected prototype_ `bool IsParameterAlreadyAdded() const;` — Checks the data model if the parameter exists.
- L69 _protected prototype_ `bool DoParametersMatchForAllViewports() const;` — Compares all selected viewport values.
- L72 _protected prototype_ `void UpdateCustomParameterValueText(const FString& NewValue, bool bNotify = true) const;` — Update the parameter value in the viewport data object.
- L75 _protected prototype_ `virtual EVisibility IsParameterVisible() const;` — Visibility of this parameter. Uses OnParameterVisibilityCheck to check.
- L79 _protected member_ `TWeakObjectPtr<UDisplayClusterBlueprint> BlueprintOwnerPtr;` — Owning blueprint of this policy.
- L82 _protected member_ `TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>> ConfigurationViewports;` — Viewport owning policy.
- L85 _protected member_ `FDisplayClusterConfiguratorBlueprintEditor* BlueprintEditorPtrCached;` — BP editor found from BlueprintOwner.
- L88 _protected member_ `TSharedPtr<FString> InitialValue;` — Optional initial selected item.
- L91 _protected member_ `FParameterVisible OnParameterVisibilityCheck;` — Used to determine parameter visibility.
- L95 _private member_ `FString ParamDisplayName;` — The display name only for the UI.
- L98 _private member_ `FText ParamTooltip;` — The tooltip to display in the UI
- L101 _private member_ `FString ParamKey;` — The proper title (key) of this parameter.

#### class `FPolicyParameterInfoCombo`  
`class FPolicyParameterInfoCombo : public FPolicyParameterInfo`  
_L107-149_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for combo box picker with custom values.
- L113 _public prototype_ `FPolicyParameterInfoCombo( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const TArray<FString>& InValues, const FString* InInitialItem = nullptr, bool bSort = true);`
- L123 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L127 _public function_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox>& GetCustomParameterValueComboBox()` — The combo box containing all of the options.
- L130 _public function_ `TArray< TSharedPtr<FString> >& GetCustomParameterOptions()` — The options used in the combo box.
- L132 _public prototype_ `void SetOnSelectedDelegate(FOnItemSelected InDelegate);`
- L136 _protected prototype_ `TSharedRef<SWidget> MakeCustomParameterValueComboWidget(TSharedPtr<FString> InItem);` — Widget used for each option.
- L139 _protected prototype_ `void OnCustomParameterValueSelected(TSharedPtr<FString> InValue, ESelectInfo::Type SelectInfo);` — When a custom parameter value option has been selected.
- L143 _protected member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> CustomParameterValueComboBox;` — Current parameters' value combo box.
- L146 _protected member_ `TArray< TSharedPtr<FString> > CustomParameterOptions;` — List of options for the combo value box.
- L148 _protected member_ `FOnItemSelected OnItemSelected;`

#### class `FPolicyParameterInfoComponentCombo`  
`class FPolicyParameterInfoComponentCombo final : public FPolicyParameterInfoCombo`  
_L154-173_
- inherits: `FPolicyParameterInfoCombo`
- desc: Policy info for combo box picker for actor components.
- L157 _public prototype_ `FPolicyParameterInfoComponentCombo( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const TArray<TSubclassOf<UActorComponent>>& InComponentClasses);`
- L165 _public prototype_ `void CreateParameterValues(ADisplayClusterRootActor* RootActor);` — Populate CustomParameterOptions based on this parameter.
- L168 _public function_ `const TArray<TSubclassOf<UActorComponent>>& GetComponentTypes() const` — The type of component this parameter represents.
- L172 _private member_ `TArray<TSubclassOf<UActorComponent>> ComponentTypes;` — A component class to use for creating parameter options.

#### class `FPolicyParameterInfoViewportCombo`  
`class FPolicyParameterInfoViewportCombo final : public FPolicyParameterInfoCombo`  
_L178-197_
- inherits: `FPolicyParameterInfoCombo`
- desc: Policy info for combo box picker for viewports (for Reference projection policy).
- L181 _public prototype_ `FPolicyParameterInfoViewportCombo( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L188 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L192 _public prototype_ `void CreateParameterValues();` — Populate CustomParameterOptions with all viewports except the currently edited ones.
- L196 _private prototype_ `bool AreAllViewportsInSameClusterNode() const;` — Check if all edited viewports belong to the same cluster node.

#### class `FPolicyParameterInfoNumber`  
`template<typename T> class FPolicyParameterInfoNumber final : public FPolicyParameterInfo`  
_L203-282_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for number value.
- L206 _public function_ `FPolicyParameterInfoNumber( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, T InDefaultValue = 0, TOptional<T> InMinValue = TOptional<T>(), TOptional<T> InMaxValue = TOptional<T>()) : FPolicyParameterInfo(InDisplayName, InKey, InBlueprint, InConfigurationViewports)`
- L236 _public function_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override` — FPolicyParameterInfo
- L267 _public function_ `TOptional<T> OnGetValue() const`
- L278 _private member_ `TOptional<T> MinValue;`
- L279 _private member_ `TOptional<T> MaxValue;`
- L280 _private member_ `T NumberValue;`
- L281 _private member_ `bool bIsMultipleValues = false;`

#### class `FPolicyParameterInfoText`  
`class FPolicyParameterInfoText final : public FPolicyParameterInfo`  
_L287-299_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for text value.
- L290 _public prototype_ `FPolicyParameterInfoText( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L297 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo

#### class `FPolicyParameterInfoBool`  
`class FPolicyParameterInfoBool final : public FPolicyParameterInfo`  
_L304-323_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for bool value.
- L307 _public prototype_ `FPolicyParameterInfoBool( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, bool bInvertValue = false );`
- L316 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L320 _private prototype_ `ECheckBoxState IsChecked() const;`
- L322 _private member_ `bool bInvertValue;`

#### class `FPolicyParameterInfoFile`  
`class FPolicyParameterInfoFile final : public FPolicyParameterInfo`  
_L328-352_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for file picker.
- L331 _public function_ `FPolicyParameterInfoFile( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const TArray<FString>& InFileExtensions) : FPolicyParameterInfo(InDisplayName, InKey, InBlueprint, InConfigurationViewports)`
- L342 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L347 _private prototype_ `void OpenSelectFileDialogue();` — Prompts user to select a file.
- L348 _private prototype_ `FReply OnChangePathClicked();`
- L351 _private member_ `TArray<FString> FileExtensions;`

#### class `FPolicyParameterInfoFloatReference`  
`class FPolicyParameterInfoFloatReference : public FPolicyParameterInfo`  
_L357-408_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for modifying float reference, typically in a vector or matrix.
- L360 _public function_ `FPolicyParameterInfoFloatReference( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const FString* InInitialValue = nullptr) : FPolicyParameterInfo(InDisplayName, InKey, InBlueprint, InConfigurationViewports, InInitialValue)`
- L372 _protected prototype_ `virtual void FormatTextAndUpdateParameter() = 0;` — Converts values to text.
- L375 _protected prototype_ `TSharedRef<SWidget> MakeFloatInputWidget(TSharedRef<TOptional<float>>& ProxyValue, const FText& Label, const bool bRotationInDegrees, const FLinearColor& LabelColor, const FLinearColor& LabelBackgroundColor, const float* InMinValue = nullptr, const float* InMaxValue = nullptr);` — Creates SNumericEntryBox<float> widget instance.
- L381 _protected function_ `TOptional<float> OnGetValue(TSharedRef<TOptional<float>> Value) const` — Returns an optional float value.
- L387 _protected function_ `void OnValueCommitted(float NewValue, ETextCommit::Type CommitType, TSharedRef<TOptional<float>> Value)` — Callback that is called when the value changes.
- L397 _protected function_ `static void ResetOrSetCachedValue(TSharedRef<TOptional<float>>& InCachedValue, float InCompareValue)` — Reset or set cached value. This function can be called multiple times when editing a value for a group selection. In this case, when the values in the group differ, a reset is used.

#### class `FPolicyParameterInfoIntReference`  
`class FPolicyParameterInfoIntReference : public FPolicyParameterInfo`  
_L413-463_
- inherits: `FPolicyParameterInfo`
- desc: Policy info for modifying positive int32 reference, typically in a resolution
- L416 _public function_ `FPolicyParameterInfoIntReference( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const FString* InInitialValue = nullptr) : FPolicyParameterInfo(InDisplayName, InKey, InBlueprint, InConfigurationViewports, InInitialValue)`
- L428 _protected prototype_ `virtual void FormatTextAndUpdateParameter() = 0;` — Converts values to text.
- L431 _protected prototype_ `TSharedRef<SWidget> MakeIntInputWidget(TSharedRef<TOptional<int32>>& ProxyValue, const FText& Label, const FLinearColor& LabelColor, const FLinearColor& LabelBackgroundColor, const int32* InMinValue = nullptr, const int32* InMaxValue = nullptr);` — Creates SNumericEntryBox<int32> widget instance.
- L436 _protected function_ `TOptional<int32> OnGetValue(TSharedRef<TOptional<int32>> Value) const` — Returns an optional int32 value.
- L442 _protected function_ `void OnValueCommitted(int32 NewValue, ETextCommit::Type CommitType, TSharedRef<TOptional<int32>> Value)` — Callback that is called when the value changes.
- L452 _protected function_ `static void ResetOrSetCachedValue(TSharedRef<TOptional<int32>>& InCachedValue, int32 InCompareValue)` — Reset or set cached value. This function can be called multiple times when editing a value for a group selection. In this case, when the values in the group differ, a reset is used.

#### class `FPolicyParameterInfoMatrix`  
`class FPolicyParameterInfoMatrix final : public FPolicyParameterInfoFloatReference`  
_L468-501_
- inherits: `FPolicyParameterInfoFloatReference`
- desc: Policy info for matrix.
- L471 _public prototype_ `FPolicyParameterInfoMatrix( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L478 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L482 _private prototype_ `void CustomizeLocation(FDetailWidgetRow& InDetailWidgetRow);`
- L483 _private prototype_ `void CustomizeRotation(FDetailWidgetRow& InDetailWidgetRow);`
- L484 _private prototype_ `void CustomizeScale(FDetailWidgetRow& InDetailWidgetRow);`
- L485 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L488 _private member_ `mutable TSharedRef<TOptional<float>> CachedTranslationX;`
- L489 _private member_ `mutable TSharedRef<TOptional<float>> CachedTranslationY;`
- L490 _private member_ `mutable TSharedRef<TOptional<float>> CachedTranslationZ;`
- L492 _private member_ `mutable TSharedRef<TOptional<float>> CachedRotationYaw;`
- L493 _private member_ `mutable TSharedRef<TOptional<float>> CachedRotationPitch;`
- L494 _private member_ `mutable TSharedRef<TOptional<float>> CachedRotationRoll;`
- L496 _private member_ `mutable TSharedRef<TOptional<float>> CachedScaleX;`
- L497 _private member_ `mutable TSharedRef<TOptional<float>> CachedScaleY;`
- L498 _private member_ `mutable TSharedRef<TOptional<float>> CachedScaleZ;`
- L500 _private member_ `static const FString BaseMatrixString;`

#### class `FPolicyParameterInfo4x4Matrix`  
`class FPolicyParameterInfo4x4Matrix final : public FPolicyParameterInfoFloatReference`  
_L506-547_
- inherits: `FPolicyParameterInfoFloatReference`
- desc: Policy info for 4x4 matrix.
- L509 _public prototype_ `FPolicyParameterInfo4x4Matrix( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const FString* DefaultMatrixString = nullptr);`
- L517 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L521 _private prototype_ `void CustomizeRow(const FText& InHeaderText, TSharedRef<TOptional<float>>& InX, TSharedRef<TOptional<float>>& InY, TSharedRef<TOptional<float>>& InZ, TSharedRef<TOptional<float>>& InW, FDetailWidgetRow& InDetailWidgetRow);`
- L523 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L526 _private member_ `mutable TSharedRef<TOptional<float>> A;`
- L527 _private member_ `mutable TSharedRef<TOptional<float>> B;`
- L528 _private member_ `mutable TSharedRef<TOptional<float>> C;`
- L529 _private member_ `mutable TSharedRef<TOptional<float>> D;`
- L531 _private member_ `mutable TSharedRef<TOptional<float>> E;`
- L532 _private member_ `mutable TSharedRef<TOptional<float>> F;`
- L533 _private member_ `mutable TSharedRef<TOptional<float>> G;`
- L534 _private member_ `mutable TSharedRef<TOptional<float>> H;`
- L536 _private member_ `mutable TSharedRef<TOptional<float>> I;`
- L537 _private member_ `mutable TSharedRef<TOptional<float>> J;`
- L538 _private member_ `mutable TSharedRef<TOptional<float>> K;`
- L539 _private member_ `mutable TSharedRef<TOptional<float>> L;`
- L541 _private member_ `mutable TSharedRef<TOptional<float>> M;`
- L542 _private member_ `mutable TSharedRef<TOptional<float>> N;`
- L543 _private member_ `mutable TSharedRef<TOptional<float>> O;`
- L544 _private member_ `mutable TSharedRef<TOptional<float>> P;`
- L546 _private member_ `static const FString BaseMatrixString;`

#### class `FPolicyParameterInfoRotator`  
`class FPolicyParameterInfoRotator final : public FPolicyParameterInfoFloatReference`  
_L552-574_
- inherits: `FPolicyParameterInfoFloatReference`
- desc: Policy info for rotator.
- L555 _public prototype_ `FPolicyParameterInfoRotator( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L562 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L566 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L569 _private member_ `mutable TSharedRef<TOptional<float>> CachedRotationYaw;`
- L570 _private member_ `mutable TSharedRef<TOptional<float>> CachedRotationPitch;`
- L571 _private member_ `mutable TSharedRef<TOptional<float>> CachedRotationRoll;`
- L573 _private member_ `static const FString BaseRotatorString;`

#### class `FPolicyParameterInfoVector`  
`class FPolicyParameterInfoVector final : public FPolicyParameterInfoFloatReference`  
_L579-601_
- inherits: `FPolicyParameterInfoFloatReference`
- desc: Policy info for vector.
- L582 _public prototype_ `FPolicyParameterInfoVector( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L589 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L593 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L596 _private member_ `mutable TSharedRef<TOptional<float>> CachedVectorX;`
- L597 _private member_ `mutable TSharedRef<TOptional<float>> CachedVectorY;`
- L598 _private member_ `mutable TSharedRef<TOptional<float>> CachedVectorZ;`
- L600 _private member_ `static const FString BaseVectorString;`

#### class `FPolicyParameterInfoFrustumAngle`  
`class FPolicyParameterInfoFrustumAngle final : public FPolicyParameterInfoFloatReference`  
_L606-629_
- inherits: `FPolicyParameterInfoFloatReference`
- desc: Policy info for frustum angle.
- L609 _public prototype_ `FPolicyParameterInfoFrustumAngle( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L616 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L620 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L623 _private member_ `mutable TSharedRef<TOptional<float>> CachedAngleL;`
- L624 _private member_ `mutable TSharedRef<TOptional<float>> CachedAngleR;`
- L625 _private member_ `mutable TSharedRef<TOptional<float>> CachedAngleT;`
- L626 _private member_ `mutable TSharedRef<TOptional<float>> CachedAngleB;`
- L628 _private member_ `static const FString BaseFrustumPlanesString;`

#### class `FPolicyParameterInfoResolution`  
`class FPolicyParameterInfoResolution final : public FPolicyParameterInfoIntReference`  
_L634-655_
- inherits: `FPolicyParameterInfoIntReference`
- desc: Policy info for resolution
- L637 _public prototype_ `FPolicyParameterInfoResolution( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports);`
- L644 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L648 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L651 _private member_ `mutable TSharedRef<TOptional<int32>> CachedX;`
- L652 _private member_ `mutable TSharedRef<TOptional<int32>> CachedY;`
- L654 _private member_ `static const FString BaseResolutionString;`

#### class `FPolicyParameterInfoNormalizedVector2D`  
`class FPolicyParameterInfoNormalizedVector2D final : public FPolicyParameterInfoFloatReference`  
_L660-683_
- inherits: `FPolicyParameterInfoFloatReference`
- desc: Policy information for a normalized vector 2d whose component values must be between 0 and 1.
- L663 _public prototype_ `FPolicyParameterInfoNormalizedVector2D( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const FString* InDefaultValue = nullptr );`
- L672 _public prototype_ `virtual void CreateCustomRowWidget(IDetailChildrenBuilder& InDetailWidgetRow) override;` — FPolicyParameterInfo
- L676 _private prototype_ `virtual void FormatTextAndUpdateParameter() override;`
- L679 _private member_ `mutable TSharedRef<TOptional<float>> CachedX;`
- L680 _private member_ `mutable TSharedRef<TOptional<float>> CachedY;`
- L682 _private member_ `static const FString BaseVectorValueStr;`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EVisibility, FParameterVisible, FText);`
- L110 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, const FString&) public: FPolicyParameterInfoCombo( const FString& InDisplayName, const FString& InKey, UDisplayClusterBlueprint* InBlueprint, const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& InConfigurationViewports, const TArray<FString>& InValues, const FString* InInitialItem = nullptr, bool bSort = true);`
- L258 _function_ `` (scope `FPolicyParameterInfoNumber::CreateCustomRowWidget`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Policies/DisplayClusterConfiguratorPolymorphicEntityCustomization.h` (Private)


#### class `FDisplayClusterConfiguratorPolymorphicEntityCustomization`  
`class FDisplayClusterConfiguratorPolymorphicEntityCustomization : public FDisplayClusterConfiguratorBaseTypeCustomization`  
_L9-24_
- inherits: `FDisplayClusterConfiguratorBaseTypeCustomization`
- desc: Base type customization for any types derived from FDisplayClusterConfigurationPolymorphicEntity
- L13 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _protected member_ `TSharedPtr<IPropertyHandle> TypeHandle;` — The property handle of the Type property of the FDisplayClusterConfigurationPolymorphicEntity type
- L20 _protected member_ `TSharedPtr<IPropertyHandle> ParametersHandle;` — The property handle of the Parameters property of the FDisplayClusterConfigurationPolymorphicEntity type
- L23 _protected member_ `TSharedPtr<IPropertyHandle> IsCustomHandle;` — The property handle of the bIsCustom property of the FDisplayClusterConfigurationPolymorphicEntity type

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Upscaler/DisplayClusterConfigurationUpscalerSettingsDetailCustomization.h` (Private)


#### class `FDisplayClusterConfigurationUpscalerSettingsDetailCustomization`  
`class FDisplayClusterConfigurationUpscalerSettingsDetailCustomization : public IPropertyTypeCustomization`  
_L12-61_
- inherits: `IPropertyTypeCustomization`
- desc: DisplayCluster UI customization for Upscaler Settings.
- L15 _public prototype_ `FDisplayClusterConfigurationUpscalerSettingsDetailCustomization();`
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _protected prototype_ `bool UpdateEditingData(bool bResetBag);` — Initialize EditingDataHandle
- L55 _protected member_ `TArray<TSharedPtr<FUpscalerMethodEntry>> UpscalerMethods;`
- L56 _protected member_ `TSharedPtr<FUpscalerMethodEntry> CurrentUpscalerMethod;`
- L59 _protected member_ `TSharedPtr<IPropertyHandle> MethodNameHandle;` — property handles
- L60 _protected member_ `TSharedPtr<IPropertyHandle> EditingDataHandle;`

#### struct `FDisplayClusterConfigurationUpscalerSettingsDetailCustomization::FUpscalerMethodEntry`  
`struct FUpscalerMethodEntry`  
_L34-53_
- desc: Droplist element with the tooltip text.
- L36 _public prototype_ `FUpscalerMethodEntry() = default;`
- L37 _public function_ `FUpscalerMethodEntry( const FName& InName, const FText& InDisplayName, const FText& InTooltip) : Name(InName), DisplayName(InDisplayName), Tooltip(InTooltip)`
- L46 _public member_ `FName Name;` — Key
- L49 _public member_ `FText DisplayName;` — (opt) The display name shown in the UI. Use 'Name' is this value is empty.
- L52 _public member_ `FText Tooltip;` — (opt) Tooltip text

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Widgets/SDisplayClusterConfigurationSearchableComboBox.h` (Private)


#### class `SDisplayClusterConfigurationSearchableComboBox`  
`class SDisplayClusterConfigurationSearchableComboBox : public SSearchableComboBox`  
_L12-93_
- inherits: `SSearchableComboBox`
- desc: A searchable text combo box Mostly copied from SearchableComboBox, but with extension for dynamically update the Option source list
- L17 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfigurationSearchableComboBox) : _Content() , _ComboBoxStyle(&FAppStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox")) , _ButtonStyle(nullptr) , _ItemStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row")) , _ContentPadding(_ComboBoxStyle->ContentPadding) , _ForegroundColor(FSlateColor::UseStyle()) , _OptionsSource() , _OnSelectionChanged() , _OnGenerateWidget() , _InitiallySelectedItem(nullptr) , _Method() , _MaxListHeight(450.0f) , _HasDownArrow(true) , _SearchVisibility()`
- L35 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FSlateColor, ForegroundColor) SLATE_ARGUMENT(const TArray< TSharedPtr<FString> >*, OptionsSource) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnComboBoxOpening, OnComboBoxOpening) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, CustomScrollbar) SLATE_ARGUMENT(TSharedPtr<FString>, InitiallySelectedItem) SLATE_ARGUMENT(TOptional<EPopupMethod>, Method) SLATE_ARGUMENT(float, MaxListHeight) SLATE_ARGUMENT(bool, HasDownArrow) SLATE_ATTRIBUTE(EVisibility, SearchVisibility) SLATE_END_ARGS()` — Slot for this button's content (optional)
- L88 _public prototype_ `void ResetOptionsSource(const TArray<TSharedPtr<FString>>* NewOptionsSource = nullptr);` — Reset the source in the Combo Box List. The options source is intelligently refreshed based on if the Source is the same or not. @param NewOptionsSource The options data to use. If null the original will be used.
- L92 _protected member_ `const TArray< TSharedPtr<FString> >* DisplayClusterOptionsSource;` — Local version of parent class private variable `OptionsSource`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Details/Widgets/SDisplayClusterConfiguratorComponentPicker.h` (Private)


#### class `SDisplayClusterConfiguratorComponentPicker`  
`class SDisplayClusterConfiguratorComponentPicker : public SCompoundWidget`  
_L18-83_
- inherits: `SCompoundWidget`
- desc: A searchable text combo box for components which allows reading/writing a string value to a property handle. Works with CDOs.
- L22 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorComponentPicker)`
- L24 _public prototype_ `SLATE_ARGUMENT(FText, DefaultOptionText) SLATE_ARGUMENT(TOptional<FString>, DefaultOptionValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSubclassOf<UActorComponent>& InComponentClass, const TWeakObjectPtr<AActor>& InOwningActor, const TSharedPtr<IPropertyHandle>& InPropertyHandle);`
- L41 _private prototype_ `TSharedRef<SWidget> CreateComboBoxWidget();` — Creates a combo box widget to represent components
- L47 _private prototype_ `TSharedRef<SWidget> MakeOptionComboWidget(TSharedPtr<FString> InItem);` — Creates a text block widget to use to display the specified item in the dropdown menu @param InItem - The string item to make the text block for
- L50 _private prototype_ `FText GetSelectedComponentText() const;` — Gets the text to display for the currently selected component
- L57 _private prototype_ `void OnComponentSelected(TSharedPtr<FString> InComponentName, ESelectInfo::Type SelectInfo);` — Raised when a component is selected from the dropdown menu @param InComponentName - The component name that was selected @param SelectInfo - Flag to indicate through what interface the selection was made
- L60 _private prototype_ `void RefreshComponentOptions();` — Rebuilds the list of components to show in the dropdown menu
- L64 _private member_ `TArray<TSharedPtr<FString>> AvailableComponentOptions;` — The list of components to display in the dropdown menu
- L67 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property handle to read/set the component value to
- L70 _private member_ `TSharedPtr<SDisplayClusterConfigurationSearchableComboBox> ComponentComboBox;` — The combo box that is being displayed in the details panel for the component property
- L73 _private member_ `TWeakObjectPtr<AActor> OwningActor;` — The actor containing the components
- L76 _private member_ `TSubclassOf<UActorComponent> ComponentClass;` — The component type for this widget
- L79 _private member_ `FText DefaultOptionText;` — The default option to use
- L82 _private member_ `TOptional<FString> DefaultOptionValue;` — The value to apply when selecting the default option

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/DisplayClusterConfiguratorToolbar.h` (Private)


#### class `FDisplayClusterConfiguratorToolbar`  
`class FDisplayClusterConfiguratorToolbar : public TSharedFromThis<FDisplayClusterConfiguratorToolbar>`  
_L13-29_
- inherits: `TSharedFromThis<FDisplayClusterConfiguratorToolbar>`
- L15 _public function_ `FDisplayClusterConfiguratorToolbar(TSharedPtr<FDisplayClusterConfiguratorBlueprintEditor> InEditor) : Editor(InEditor)`
- L19 _public prototype_ `void AddModesToolbar(TSharedPtr<FExtender> Extender);`
- L22 _protected prototype_ `void FillModesToolbar(FToolBarBuilder& ToolbarBuilder);`
- L23 _protected prototype_ `TSharedRef<SWidget> GenerateExportMenu();`
- L25 _protected prototype_ `FText GetExportPath() const;`
- L28 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> Editor;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/DragDrop/DisplayClusterConfiguratorClusterNodeDragDropOp.h` (Private)


#### class `FDisplayClusterConfiguratorClusterNodeDragDropOp`  
`class FDisplayClusterConfiguratorClusterNodeDragDropOp : public FDisplayClusterConfiguratorValidatedDragDropOp`  
_L13-27_
- inherits: `FDisplayClusterConfiguratorValidatedDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDisplayClusterConfiguratorClusterNodeDragDropOp, FDisplayClusterConfiguratorValidatedDragDropOp) static TSharedRef<FDisplayClusterConfiguratorClusterNodeDragDropOp> New(const TArray<UDisplayClusterConfigurationClusterNode*>& ClusterNodesToDrag);`
- L20 _public function_ `const TArray<TWeakObjectPtr<UDisplayClusterConfigurationClusterNode>>& GetDraggedClusterNodes() const`
- L23 _protected prototype_ `virtual FText GetHoverText() const override;`
- L26 _private member_ `TArray<TWeakObjectPtr<UDisplayClusterConfigurationClusterNode>> DraggedClusterNodes;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/DragDrop/DisplayClusterConfiguratorValidatedDragDropOp.h` (Private)


#### class `FDisplayClusterConfiguratorValidatedDragDropOp`  
`class FDisplayClusterConfiguratorValidatedDragDropOp : public FDecoratedDragDropOp`  
_L10-34_
- inherits: `FDecoratedDragDropOp`
- L13 _public function_ `DRAG_DROP_OPERATOR_TYPE(FDisplayClusterConfiguratorValidatedDragDropOp, FDecoratedDragDropOp) FDisplayClusterConfiguratorValidatedDragDropOp() : bCanBeDropped(true)`
- L21 _protected prototype_ `virtual void Construct() override;`
- L25 _public prototype_ `void SetDropAsInvalid(FText Message = FText::GetEmpty());`
- L26 _public prototype_ `void SetDropAsValid(FText Message = FText::GetEmpty());`
- L27 _public function_ `bool CanBeDropped() const`
- L30 _protected function_ `virtual FText GetHoverText() const`
- L33 _protected member_ `bool bCanBeDropped;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/DragDrop/DisplayClusterConfiguratorViewportDragDropOp.h` (Private)


#### class `FDisplayClusterConfiguratorViewportDragDropOp`  
`class FDisplayClusterConfiguratorViewportDragDropOp : public FDisplayClusterConfiguratorValidatedDragDropOp`  
_L13-27_
- inherits: `FDisplayClusterConfiguratorValidatedDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDisplayClusterConfiguratorViewportDragDropOp, FDisplayClusterConfiguratorValidatedDragDropOp) static TSharedRef<FDisplayClusterConfiguratorViewportDragDropOp> New(const TArray<UDisplayClusterConfigurationViewport*>& ViewportsToDrag);`
- L20 _public function_ `const TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>>& GetDraggedViewports() const`
- L23 _private prototype_ `virtual FText GetHoverText() const override;`
- L26 _private member_ `TArray<TWeakObjectPtr<UDisplayClusterConfigurationViewport>> DraggedViewports;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/IDisplayClusterConfiguratorViewBase.h` (Private)


#### class `IDisplayClusterConfiguratorViewBase`  
`class IDisplayClusterConfiguratorViewBase : public SCompoundWidget`  
_L9-17_
- inherits: `SCompoundWidget`
- L13 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewBase() = default;`
- L16 _public prototype_ `virtual void ConstructChildren(const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Log/DisplayClusterConfiguratorViewLog.h` (Private)


#### class `FDisplayClusterConfiguratorViewLog`  
`class FDisplayClusterConfiguratorViewLog : public IDisplayClusterConfiguratorViewLog`  
_L15-40_
- inherits: `IDisplayClusterConfiguratorViewLog`
- desc: Custom display cluster logging. TODO: Currently not used anywhere in favor of compiler results logging. Leaving in for now because cluster logging options may be needed in the future.
- L19 _public prototype_ `FDisplayClusterConfiguratorViewLog(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L23 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;`
- L27 _public prototype_ `virtual TSharedRef<IMessageLogListing> GetMessageLogListing() const override;`
- L28 _public prototype_ `virtual TSharedRef<IMessageLogListing> CreateLogListing() override;`
- L29 _public prototype_ `virtual void Log(const FText& Message, EVerbosityLevel Verbosity = EVerbosityLevel::Log) override;`
- L33 _private member_ `TSharedPtr<SDisplayClusterConfiguratorViewLog> ViewLog;`
- L35 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L37 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`
- L39 _private member_ `TSharedPtr<SWidget> LogListingWidget;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Log/SDisplayClusterConfiguratorViewLog.h` (Private)


#### class `SDisplayClusterConfiguratorViewLog`  
`class SDisplayClusterConfiguratorViewLog : public SDisplayClusterConfiguratorViewBase , public FEditorUndoClient`  
_L13-34_
- inherits: `SDisplayClusterConfiguratorViewBase,FEditorUndoClient`
- L19 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorViewLog)`
- L25 _public function_ `SDisplayClusterConfiguratorViewLog()`
- L28 _public prototype_ `~SDisplayClusterConfiguratorViewLog();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, const TSharedRef<SWidget>& InListingWidget);`
- L33 _private member_ `TSharedPtr<SWidget> LogListingWidget;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/NewAsset/SDisplayClusterConfiguratorAssetPickerList.h` (Private)


#### class `SDisplayClusterConfiguratorAssetPickerList`  
`class SDisplayClusterConfiguratorAssetPickerList : public SCompoundWidget`  
_L15-36_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorAssetPickerList) : _OnAssetSelected()`
- L21 _public prototype_ `SLATE_EVENT(FOnDisplayClusterAssetSelected, OnAssetSelected) SLATE_END_ARGS() ~SDisplayClusterConfiguratorAssetPickerList();`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);`
- L27 _public function_ `const TArray<FAssetData>& GetSelectedAssets() const`
- L30 _private prototype_ `void OnAssetSelected(const FAssetData& InAssetData);`
- L31 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& InAssetData);`
- L34 _private member_ `FOnDisplayClusterAssetSelected OnAssetSelectedEvent;`
- L35 _private member_ `TArray<FAssetData> SelectedAssets;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDisplayClusterAssetSelected, UDisplayClusterBlueprint*);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDisplayClusterAssetSelected, UDisplayClusterBlueprint*);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/NewAsset/SDisplayClusterConfiguratorNewAssetDialog.h` (Private)


#### class `SDisplayClusterConfiguratorNewAssetDialog`  
`class SDisplayClusterConfiguratorNewAssetDialog : public SWindow`  
_L16-89_
- inherits: `SWindow`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGetSelectedAssetsFromPicker, TArray<FAssetData>& );`
- L20 _public prototype_ `DECLARE_DELEGATE(FOnSelectionConfirmed);`
- L45 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorNewAssetDialog)`
- L47 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FText AssetTypeDisplayName, TArray<FDisplayClusterConfiguratorNewAssetDialogOption> InOptions);`
- L50 _public prototype_ `void GetAssetPicker();`
- L51 _public prototype_ `void ResetStage();`
- L52 _public prototype_ `bool GetUserConfirmedSelection() const;`
- L55 _protected prototype_ `const TArray<FAssetData>& GetSelectedAssets() const;`
- L57 _protected prototype_ `void ConfirmSelection();`
- L58 _protected function_ `int32 GetSelectedObjectIndex() const`
- L61 _protected member_ `TSharedPtr<SBox> AssetSettingsPage;`
- L65 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& Window);`
- L67 _private prototype_ `FSlateColor GetOptionBorderColor(int32 OptionIndex) const;`
- L69 _private prototype_ `ECheckBoxState GetOptionCheckBoxState(int32 OptionIndex) const;`
- L71 _private prototype_ `void OptionCheckBoxStateChanged(ECheckBoxState InCheckBoxState, int32 OptionIndex);`
- L72 _private prototype_ `FSlateColor GetOptionTextColor(int32 OptionIndex) const;`
- L74 _private prototype_ `FReply OnOptionDoubleClicked(const FGeometry& Geometry, const FPointerEvent& PointerEvent, int32 OptionIndex);`
- L76 _private prototype_ `FText GetAssetPickersLabelText() const;`
- L77 _private prototype_ `bool IsOkButtonEnabled() const;`
- L78 _private prototype_ `void OnOkButtonClicked();`
- L79 _private prototype_ `void OnCancelButtonClicked();`
- L80 _private prototype_ `bool HasAssetPage() const;`
- L83 _private member_ `TSharedPtr<SWizard> Wizard;`
- L84 _private member_ `TArray<FDisplayClusterConfiguratorNewAssetDialogOption> Options;`
- L85 _private member_ `int32 SelectedOptionIndex;`
- L86 _private member_ `bool bUserConfirmedSelection;`
- L87 _private member_ `TArray<FAssetData> SelectedAssets;`
- L88 _private member_ `bool bOnAssetStage;`

#### class `SDisplayClusterConfiguratorNewAssetDialog::FDisplayClusterConfiguratorNewAssetDialogOption`  
`class FDisplayClusterConfiguratorNewAssetDialogOption`  
_L23-42_
- L26 _public member_ `FText OptionText;`
- L27 _public member_ `FText OptionDescription;`
- L28 _public member_ `FText AssetPickerHeader;`
- L29 _public member_ `TSharedRef<SWidget> AssetPicker;`
- L30 _public member_ `FOnGetSelectedAssetsFromPicker OnGetSelectedAssetsFromPicker;`
- L31 _public member_ `FOnSelectionConfirmed OnSelectionConfirmed;`
- L33 _public function_ `FDisplayClusterConfiguratorNewAssetDialogOption(FText InOptionText, FText InOptionDescription, FText InAssetPickerHeader, FOnGetSelectedAssetsFromPicker InOnGetSelectedAssetsFromPicker, FOnSelectionConfirmed InOnSelecitonConfirmed, TSharedRef<SWidget> InAssetPicker) : OptionText(InOptionText) , OptionDescription(InOptionDescription) , AssetPickerHeader(InAssetPickerHeader) , AssetPicker(InAssetPicker) , OnGetSelectedAssetsFromPicker(InOnGetSelectedAssetsFromPicker) , OnSelectionConfirmed(InOnSelecitonConfirmed)`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetSelectedAssetsFromPicker, TArray<FAssetData>& );`
- L20 _delegate_ `DECLARE_DELEGATE(FOnSelectionConfirmed);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/NewAsset/SDisplayClusterConfiguratorNewBlueprintDialog.h` (Private)


#### class `SDisplayClusterConfiguratorNewBlueprintDialog`  
`class SDisplayClusterConfiguratorNewBlueprintDialog : public SDisplayClusterConfiguratorNewAssetDialog`  
_L14-30_
- inherits: `SDisplayClusterConfiguratorNewAssetDialog`
- desc: A modal dialog to collect information needed to create a new Display Cluster.
- L17 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorNewBlueprintDialog)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `TOptional<FAssetData> GetSelectedSystemAsset() const;`
- L26 _private prototype_ `void GetSelectedProjectSystemAssets(TArray<FAssetData>& OutSelectedAssets);`
- L29 _private member_ `TSharedPtr<SDisplayClusterConfiguratorAssetPickerList> SystemAssetPicker;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Alignment/DisplayClusterConfiguratorHostNodeArrangementHelper.h` (Private)


#### class `FDisplayClusterConfiguratorHostNodeArrangementHelper`  
`class FDisplayClusterConfiguratorHostNodeArrangementHelper`  
_L11-28_
- L14 _public function_ `FDisplayClusterConfiguratorHostNodeArrangementHelper(const FHostNodeArrangementSettings& InArrangementSettings) : ArrangementSettings(InArrangementSettings)`
- L18 _public prototype_ `void PlaceNodes(const TArray<UDisplayClusterConfiguratorHostNode*>& HostNodes);`
- L21 _private prototype_ `UDisplayClusterConfiguratorHostNode* CheckForOverlap(UDisplayClusterConfiguratorHostNode* HostNode, FVector2D DesiredPosition);`
- L24 _private member_ `FHostNodeArrangementSettings ArrangementSettings;`
- L26 _private member_ `TArray<UDisplayClusterConfiguratorHostNode*> ManuallyPlacedNodes;`
- L27 _private member_ `TArray<UDisplayClusterConfiguratorHostNode*> AutomaticallyPlacedNodes;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Alignment/DisplayClusterConfiguratorNodeAlignmentHelper.h` (Private)


#### enum `EAlignmentAnchor`  
`enum class EAlignmentAnchor : uint8`  
_L12-19_
- L14 _public enumerator_ `Center`
- L15 _public enumerator_ `Top`
- L16 _public enumerator_ `Bottom`
- L17 _public enumerator_ `Left`
- L18 _public enumerator_ `Right`

#### struct `FNodeAlignmentAnchors`  
`struct FNodeAlignmentAnchors`  
_L22-38_
- desc: Stores positional anchors that can be used to snap align multiple nodes with each other.
- L25 _public member_ `FVector2D Center;`
- L26 _public member_ `FVector2D Top;`
- L27 _public member_ `FVector2D Bottom;`
- L28 _public member_ `FVector2D Left;`
- L29 _public member_ `FVector2D Right;`
- L33 _public prototype_ `const FVector2D& GetAnchorPosition(EAlignmentAnchor Anchor) const;`
- L34 _public prototype_ `const FVector2D& GetAdjacentAnchorPosition(EAlignmentAnchor Anchor) const;`
- L36 _public prototype_ `FNodeAlignmentAnchors ShiftBy(const FVector2D& Offset);`
- L37 _public prototype_ `FNodeAlignmentAnchors ExpandBy(const FVector2D& SizeChange);`

#### struct `FNodeAlignmentParams`  
`struct FNodeAlignmentParams`  
_L41-69_
- desc: Parameters to customize how nodes can be aligned with other nodes.
- L45 _public member_ `float SnapProximity;` — Distance along snapped axis that snapping occurs.
- L48 _public member_ `float MaxSnapRadius;` — The maximum distance two nodes can be that snapping can occur.
- L51 _public member_ `float SnapAdjacentEdgesPadding;` — Amount of padding to add between nodes when snapping their adjacent edges together.
- L54 _public member_ `bool bCanSnapAdjacentEdges;` — Indicates whether nodes' adjacent edges (e.g. right edge to left edge) should snap.
- L57 _public member_ `bool bCanSnapSameEdges;` — Indicates whether nodes' equivalent edges (e.g top edge to top edge) should snap.
- L60 _public member_ `TSet<EAlignmentAnchor> AnchorsToIgnore;` — A list of anchors that won't be aligned with.
- L62 _public function_ `FNodeAlignmentParams() : SnapProximity(10), MaxSnapRadius(FLT_MAX), SnapAdjacentEdgesPadding(10), bCanSnapAdjacentEdges(true), bCanSnapSameEdges(true)`

#### struct `FNodeAlignment`  
`struct FNodeAlignment`  
_L71-94_
- L74 _public member_ `TWeakObjectPtr<const UDisplayClusterConfiguratorBaseNode> TargetNode;`
- L75 _public member_ `EAlignmentAnchor AlignedAnchor;`
- L76 _public member_ `bool bIsAdjacent;`
- L77 _public member_ `float AlignmentOffset;`
- L79 _public function_ `FNodeAlignment() : TargetNode(nullptr), AlignedAnchor(EAlignmentAnchor::Center), bIsAdjacent(false), AlignmentOffset(0)`
- L86 _public function_ `FNodeAlignment(const UDisplayClusterConfiguratorBaseNode* InTargetNode, EAlignmentAnchor InAlignedAnchor, bool bInIsAdjacent, float InAlignmentOffset) : TargetNode(InTargetNode), AlignedAnchor(InAlignedAnchor), bIsAdjacent(bInIsAdjacent), AlignmentOffset(InAlignmentOffset)`
- L93 _public function_ `bool IsValid() const`

#### struct `FNodeAlignmentPair`  
`struct FNodeAlignmentPair`  
_L96-109_
- L99 _public member_ `FNodeAlignment XAlignment;`
- L100 _public member_ `FNodeAlignment YAlignment;`
- L102 _public function_ `FNodeAlignmentPair(FNodeAlignment InXAlignment, FNodeAlignment InYAlignment) : XAlignment(InXAlignment), YAlignment(InYAlignment)`
- L107 _public prototype_ `FVector2D GetOffset() const;`
- L108 _public prototype_ `bool HasAlignments() const;`

#### struct `FDisplayClusterConfiguratorNodeAlignmentHelper`  
`struct FDisplayClusterConfiguratorNodeAlignmentHelper`  
_L115-139_
- desc: Stores a list of all possible alignment options for a given node to choose from. Each axis stores a separate list of alignments, allowing a node to be aligned two different nodes at the same time, one along each axis.
- L118 _public prototype_ `FDisplayClusterConfiguratorNodeAlignmentHelper(const UDisplayClusterConfiguratorBaseNode* InNodeToAlign, const FNodeAlignmentAnchors& InNodeAnchors, const FNodeAlignmentParams& InAlignmentParams);`
- L120 _public prototype_ `void AddAlignmentsToNode(const UDisplayClusterConfiguratorBaseNode* TargetNode);`
- L121 _public prototype_ `void AddAlignmentsToParent(const UDisplayClusterConfiguratorBaseNode* TargetParent);`
- L123 _public prototype_ `FNodeAlignmentPair GetAlignments() const;`
- L124 _public prototype_ `bool HasAlignments() const;`
- L127 _private prototype_ `void AddAlignment(FNodeAlignment NewAlignment, int32 AlignmentAxis);`
- L129 _private prototype_ `void TryAlignAjacentEdge(const UDisplayClusterConfiguratorBaseNode* TargetNode, EAlignmentAnchor Anchor, bool bIsParent);`
- L130 _private prototype_ `void TryAlignSameEdge(const UDisplayClusterConfiguratorBaseNode* TargetNode, EAlignmentAnchor Anchor, bool bIsParent);`
- L133 _private member_ `TWeakObjectPtr<const UDisplayClusterConfiguratorBaseNode> NodeToAlign;`
- L134 _private member_ `FNodeAlignmentAnchors NodeAnchors;`
- L135 _private member_ `FNodeAlignmentParams AlignmentParams;`
- L137 _private member_ `TArray<FNodeAlignment> XAxisAlignments;`
- L138 _private member_ `TArray<FNodeAlignment> YAxisAlignments;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/DisplayClusterConfiguratorGraph.h` (Private)


#### class `UDisplayClusterConfiguratorGraph`  
`class UDisplayClusterConfiguratorGraph : public UEdGraph`  
_L24-74_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L30 _public prototype_ `void Initialize(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L33 _public prototype_ `virtual void PostEditUndo() override;` — Beign UObject Interface
- L37 _public prototype_ `void Cleanup();` — Cleans up the graph and its nodes.
- L40 _public prototype_ `void Empty();` — Removes all nodes from the graph.
- L43 _public prototype_ `void RebuildGraph();` — Rebuilds the graph using the current cluster configuration.
- L46 _public prototype_ `void TickNodePositions();` — Allows each node on the graph to reposition itself during a tick.
- L49 _public prototype_ `void RefreshNodePositions();` — Recomputes the global positions of all graph nodes.
- L52 _public prototype_ `UDisplayClusterConfiguratorBaseNode* GetNodeFromObject(UObject* InObject);` — Gets the graph node that contains the specified object.
- L55 _public prototype_ `UDisplayClusterConfiguratorCanvasNode* GetRootNode() const;` — @return The root canvas node of the graph.
- L58 _public prototype_ `void ForEachGraphNode(TFunction<void(UDisplayClusterConfiguratorBaseNode* Node)> Predicate);` — Iterates over all nodes in the graph through the node hierarchy and applies the specified predicate.
- L61 _public prototype_ `void ForEachChildNode(UDisplayClusterConfiguratorBaseNode* Node, TFunction<void(UDisplayClusterConfiguratorBaseNode* Node)> Predicate);` — Iterates over the child nodes of the specified node and applies the specified predicate.
- L64 _public function_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> GetToolkit() const` — @return The toolkit used by this graph
- L67 _private prototype_ `UDisplayClusterConfiguratorCanvasNode* BuildCanvasNode(UDisplayClusterConfigurationCluster* ClusterConfig);`
- L68 _private prototype_ `UDisplayClusterConfiguratorHostNode* BuildHostNode(UDisplayClusterConfiguratorBaseNode* ParentNode, FString NodeName, int32 NodeIndex, UDisplayClusterConfigurationHostDisplayData* HostDisplayData);`
- L69 _private prototype_ `UDisplayClusterConfiguratorWindowNode* BuildWindowNode(UDisplayClusterConfiguratorBaseNode* ParentNode, FString NodeName, int32 NodeIndex, UDisplayClusterConfigurationClusterNode* ClusterNodeConfig);`
- L70 _private prototype_ `UDisplayClusterConfiguratorViewportNode* BuildViewportNode(UDisplayClusterConfiguratorBaseNode* ParentNode, FString NodeName, int32 NodeIndex, UDisplayClusterConfigurationViewport* ViewportConfig);`
- L73 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/DisplayClusterConfiguratorGraphSchema.h` (Private)


#### enum `EClusterItemType`  
`enum class EClusterItemType : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `ClusterNode`
- L18 _public enumerator_ `Viewport`

#### struct `FDisplayClusterConfiguratorSchemaAction_NewNode`  
`struct FDisplayClusterConfiguratorSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L22-40_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L27 _public prototype_ `FDisplayClusterConfiguratorSchemaAction_NewNode();`
- L28 _public prototype_ `FDisplayClusterConfiguratorSchemaAction_NewNode(EClusterItemType InItemType, const UE::Slate::FDeprecateVector2DParameter& InPresetSize, FText InDescription, FText InTooltip);`
- L31 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L36 _private member_ `EClusterItemType ItemType;` — `UPROPERTY()`
- L39 _private member_ `FDeprecateSlateVector2D PresetSize;` — `UPROPERTY()`

#### class `UDisplayClusterConfiguratorGraphSchema`  
`class UDisplayClusterConfiguratorGraphSchema : public UEdGraphSchema`  
_L43-51_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L50 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/DisplayClusterConfiguratorOutputMappingCommands.h` (Private)


#### class `FDisplayClusterConfiguratorOutputMappingCommands`  
`class FDisplayClusterConfiguratorOutputMappingCommands : public TCommands<FDisplayClusterConfiguratorOutputMappingCommands>`  
_L10-44_
- inherits: `TCommands<FDisplayClusterConfiguratorOutputMappingCommands>`
- L14 _public function_ `FDisplayClusterConfiguratorOutputMappingCommands() : TCommands<FDisplayClusterConfiguratorOutputMappingCommands>(TEXT("DisplayClusterConfigurator.OutputMapping"), NSLOCTEXT("Contexts", "DisplayClusterConfiguratorOutputMapping", "Display Cluster Configurator Output Mapping"), NAME_None, FDisplayClusterConfiguratorStyle::Get().GetStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ShowWindowInfo;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ShowWindowCorner;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ShowWindowNone;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ToggleOutsideViewports;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleClusterItemOverlap;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ToggleLockClusterNodesInHosts;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ToggleTintViewports;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFit;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> BrowseDocumentation;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ToggleAdjacentEdgeSnapping;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ToggleSameEdgeSnapping;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> FillParentNode;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> SizeToChildNodes;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> RotateViewport90CW;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> RotateViewport90CCW;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> RotateViewport180;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> FlipViewportHorizontal;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> FlipViewportVertical;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ResetViewportTransform;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/DisplayClusterConfiguratorViewOutputMapping.h` (Private)


#### class `FDisplayClusterConfiguratorViewOutputMapping`  
`class FDisplayClusterConfiguratorViewOutputMapping : public IDisplayClusterConfiguratorViewOutputMapping`  
_L16-75_
- inherits: `IDisplayClusterConfiguratorViewOutputMapping`
- L20 _public prototype_ `FDisplayClusterConfiguratorViewOutputMapping(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L21 _public prototype_ `~FDisplayClusterConfiguratorViewOutputMapping();`
- L24 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L25 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;`
- L26 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L30 _public prototype_ `virtual void Cleanup() override;`
- L32 _public function_ `virtual FOnOutputMappingBuilt& GetOnOutputMappingBuiltDelegate() override`
- L33 _public prototype_ `virtual FDelegateHandle RegisterOnOutputMappingBuilt(const FOnOutputMappingBuiltDelegate& Delegate) override;`
- L34 _public prototype_ `virtual void UnregisterOnOutputMappingBuilt(FDelegateHandle DelegateHandle) override;`
- L36 _public function_ `virtual const FOutputMappingSettings& GetOutputMappingSettings() const override`
- L37 _public function_ `virtual FOutputMappingSettings& GetOutputMappingSettings() override`
- L39 _public function_ `virtual const FHostNodeArrangementSettings& GetHostArrangementSettings() const override`
- L40 _public function_ `virtual FHostNodeArrangementSettings& GetHostArrangementSettings() override`
- L42 _public function_ `virtual const FNodeAlignmentSettings& GetNodeAlignmentSettings() const override`
- L43 _public function_ `virtual FNodeAlignmentSettings& GetNodeAlignmentSettings() override`
- L45 _public prototype_ `virtual void FindAndSelectObjects(const TArray<UObject*>& ObjectsToSelect) override;`
- L47 _public prototype_ `virtual void JumpToObject(UObject* InObject) override;`
- L51 _public prototype_ `void RefreshNodePositions();`
- L54 _private prototype_ `void BindCommands();`
- L56 _private prototype_ `void LoadSettings();`
- L57 _private prototype_ `void SaveSettings();`
- L59 _private prototype_ `void ToggleFlag(bool& bFlag);`
- L60 _private prototype_ `ECheckBoxState FlagToCheckBoxState(bool bFlag) const;`
- L63 _private member_ `TSharedPtr<SDisplayClusterConfiguratorViewOutputMapping> ViewOutputMapping;`
- L64 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L65 _private member_ `TSharedPtr<SDisplayClusterConfiguratorGraphEditor> GraphEditor;`
- L66 _private member_ `TStrongObjectPtr<UDisplayClusterConfiguratorGraph> GraphObj;`
- L68 _private member_ `FOutputMappingSettings OutputMappingSettings;`
- L69 _private member_ `FHostNodeArrangementSettings HostArrangementSettings;`
- L70 _private member_ `FNodeAlignmentSettings NodeAlignmentSettings;`
- L72 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L74 _private member_ `FOnOutputMappingBuilt OnOutputMappingBuilt;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/EdNodes/DisplayClusterConfiguratorBaseNode.h` (Private)


#### class `UDisplayClusterConfiguratorBaseNode`  
`class UDisplayClusterConfiguratorBaseNode : public UEdGraphNode , public IDisplayClusterConfiguratorOutputMappingItem`  
_L49-192_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode,IDisplayClusterConfiguratorOutputMappingItem`
- L56 _public prototype_ `virtual void Initialize(const FString& InNodeName, int32 InNodeZIndex, UObject* InObject, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L57 _public function_ `virtual void Cleanup()`
- L60 _public prototype_ `virtual void BeginDestroy() override;`
- L63 _public prototype_ `virtual void PostEditUndo() override;`
- L68 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L69 _public prototype_ `virtual void ResizeNode(const FVector2f& NewSize) override;`
- L70 _public function_ `virtual bool CanDuplicateNode() const override`
- L71 _public function_ `virtual bool CanUserDeleteNode() const override`
- L75 _public prototype_ `virtual void OnSelection() override;`
- L76 _public function_ `virtual UObject* GetObject() const override`
- L77 _public prototype_ `virtual bool IsSelected() override;`
- L81 _public prototype_ `virtual const FString& GetNodeName() const override;`
- L84 _public prototype_ `virtual void SetParent(UDisplayClusterConfiguratorBaseNode* InParent);`
- L85 _public prototype_ `virtual UDisplayClusterConfiguratorBaseNode* GetParent() const;`
- L86 _public prototype_ `virtual void AddChild(UDisplayClusterConfiguratorBaseNode* InChild);`
- L87 _public prototype_ `virtual const TArray<UDisplayClusterConfiguratorBaseNode*>& GetChildren() const;`
- L89 _public prototype_ `virtual FVector2D TransformPointToLocal(FVector2D GlobalPosition) const;`
- L90 _public prototype_ `virtual FVector2D TransformPointToGlobal(FVector2D LocalPosition) const;`
- L91 _public prototype_ `virtual FVector2D TransformSizeToLocal(FVector2D GlobalSize) const;`
- L92 _public prototype_ `virtual FVector2D TransformSizeToGlobal(FVector2D LocalSize) const;`
- L93 _public function_ `virtual FVector2D GetTranslationOffset() const`
- L95 _public prototype_ `virtual FBox2D GetNodeBounds(bool bAsParent = false) const;`
- L96 _public prototype_ `virtual FVector2D GetNodePosition() const;`
- L97 _public prototype_ `virtual FVector2D GetNodeLocalPosition() const;`
- L98 _public prototype_ `virtual FVector2D GetNodeSize() const;`
- L99 _public prototype_ `virtual FVector2D GetNodeLocalSize() const;`
- L100 _public prototype_ `virtual FNodeAlignmentAnchors GetNodeAlignmentAnchors(bool bAsParent = false) const;`
- L101 _public prototype_ `virtual int32 GetNodeLayer(const TSet<UObject*>& SelectionSet, bool bIncludeZIndex = true) const;`
- L102 _public prototype_ `virtual int32 GetAuxiliaryLayer(const TSet<UObject*>& SelectionSet) const;`
- L103 _public function_ `virtual bool IsNodeVisible() const`
- L104 _public function_ `virtual bool IsNodeEnabled() const`
- L105 _public function_ `virtual bool IsNodeUnlocked() const`
- L106 _public function_ `virtual bool IsNodeAutoPositioned() const`
- L107 _public function_ `virtual bool IsNodeAutosized() const`
- L108 _public function_ `virtual bool CanNodeOverlapSiblings() const`
- L109 _public function_ `virtual bool CanNodeExceedParentBounds() const`
- L110 _public function_ `virtual bool CanNodeHaveNegativePosition() const`
- L111 _public function_ `virtual bool CanNodeEncroachChildBounds() const`
- L113 _public prototype_ `virtual void FillParent(bool bRepositionNode = true);`
- L114 _public prototype_ `virtual void SizeToChildren(bool bRepositionNode = true);`
- L116 _public prototype_ `virtual FBox2D GetChildBounds() const;`
- L117 _public prototype_ `virtual FBox2D GetDescendentBounds() const;`
- L118 _public prototype_ `virtual bool IsOutsideParent() const;`
- L119 _public prototype_ `virtual bool IsOutsideParentBoundary() const;`
- L120 _public prototype_ `virtual void UpdateChildNodes();`
- L122 _public function_ `virtual void TickPosition()`
- L124 _public prototype_ `virtual bool IsUserInteractingWithNode(bool bCheckDescendents = false) const;`
- L125 _public function_ `virtual bool IsUserDirectlyInteractingWithNode() const`
- L126 _public function_ `virtual void MarkUserInteractingWithNode(bool bInIsDirectInteraction)`
- L127 _public function_ `virtual void ClearUserInteractingWithNode()`
- L129 _public prototype_ `virtual void UpdateNode();`
- L130 _public prototype_ `virtual void UpdateObject();`
- L131 _public function_ `virtual void DeleteObject()`
- L132 _public prototype_ `virtual bool IsObjectValid() const;`
- L134 _public prototype_ `virtual void OnNodeAligned(bool bUpdateChildren = false);`
- L136 _public prototype_ `virtual bool WillOverlap(UDisplayClusterConfiguratorBaseNode* InNode, const FVector2D& InDesiredOffset = FVector2D::ZeroVector, const FVector2D& InDesiredSizeChange = FVector2D::ZeroVector) const;`
- L137 _public prototype_ `virtual FVector2D FindNonOverlappingOffset(UDisplayClusterConfiguratorBaseNode* InNode, const FVector2D& InDesiredOffset) const;`
- L138 _public prototype_ `virtual FVector2D FindNonOverlappingSize(UDisplayClusterConfiguratorBaseNode* InNode, const FVector2D& InDesiredSize, const bool bFixedApsectRatio) const;`
- L140 _public prototype_ `virtual FVector2D FindNonOverlappingOffsetFromParent(const FVector2D& InDesiredOffset, const TSet<UDisplayClusterConfiguratorBaseNode*>& NodesToIgnore = TSet<UDisplayClusterConfiguratorBaseNode*>());`
- L141 _public prototype_ `virtual FVector2D FindBoundedOffsetFromParent(const FVector2D& InDesiredOffset);`
- L142 _public prototype_ `virtual FVector2D FindNonOverlappingSizeFromParent(const FVector2D& InDesiredSize, const bool bFixedApsectRatio);`
- L143 _public prototype_ `virtual FVector2D FindBoundedSizeFromParent(const FVector2D& InDesiredSize, const bool bFixedApsectRatio);`
- L144 _public prototype_ `virtual FVector2D FindBoundedSizeFromChildren(const FVector2D& InDesiredSize, const bool bFixedApsectRatio);`
- L146 _public prototype_ `virtual FNodeAlignmentPair GetTranslationAlignments(const FVector2D& InOffset, const FNodeAlignmentParams& AlignmentParams, const TSet<UDisplayClusterConfiguratorBaseNode*>& NodesToIgnore = TSet<UDisplayClusterConfiguratorBaseNode*>()) const;`
- L147 _public prototype_ `virtual FNodeAlignmentPair GetResizeAlignments(const FVector2D& InSizeChange, const FNodeAlignmentParams& AlignmentParams, const TSet<UDisplayClusterConfiguratorBaseNode*>& NodesToIgnore = TSet<UDisplayClusterConfiguratorBaseNode*>()) const;`
- L150 _protected function_ `virtual bool CanAlignWithParent() const`
- L151 _protected prototype_ `virtual FNodeAlignmentPair GetAlignments(const FNodeAlignmentAnchors& TransformedAnchors, const FNodeAlignmentParams& AlignmentParams, const TSet<UDisplayClusterConfiguratorBaseNode*>& NodesToIgnore) const;`
- L153 _protected function_ `virtual void WriteNodeStateToObject()`
- L154 _protected function_ `virtual void ReadNodeStateFromObject()`
- L156 _protected prototype_ `virtual float GetViewScale() const;`
- L159 _protected prototype_ `void CleanupChildrenNodes();` — Remove invalid nodes.
- L163 _public function_ `template<class TObjectType> TObjectType* GetObjectChecked() const`
- L171 _public function_ `template<class TParentType> TParentType* GetParentChecked() const`
- L179 _protected member_ `TWeakObjectPtr<UObject> ObjectToEdit;`
- L180 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L182 _protected member_ `TWeakObjectPtr<UDisplayClusterConfiguratorBaseNode> Parent;`
- L185 _protected member_ `TArray<TObjectPtr<UDisplayClusterConfiguratorBaseNode>> Children;` — `UPROPERTY(Transient, NonTransactional)`
- L187 _protected member_ `FString NodeName;`
- L188 _protected member_ `int32 NodeZIndex;`
- L190 _protected member_ `bool bIsUserInteractingWithNode;`
- L191 _protected member_ `bool bIsDirectInteraction;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace DisplayClusterConfiguratorGraphLayers`
- L26 _variable_ `const int32 BaseLayerIndex = 0;` (scope `DisplayClusterConfiguratorGraphLayers`) — Layer size is set to 1000 because the graph nodes rely on SOverlay widgets for rendering, and every slot in an overlay increments the render layer by 10. Using a layer size smaller than 1000 can easily cause elements of nodes to bleed into layers above them. For a similar reason, the ZIndexSize must be big enough to give every node room in the layer to render all of its components without overlapping other nodes.
- L27 _variable_ `const int32 LayerSize = 1000;` (scope `DisplayClusterConfiguratorGraphLayers`)
- L28 _variable_ `const int32 ZIndexSize = 30;` (scope `DisplayClusterConfiguratorGraphLayers`)
- L39 _variable_ `const int32 AuxiliaryLayerIndex = BaseLayerIndex + LayerSize * 4;` (scope `DisplayClusterConfiguratorGraphLayers`) — The auxiliary layer is meant for widgets that are always displayed on top of the viewport layer, such as window titlebars.
- L42 _variable_ `const int32 SelectedLayerIndex = BaseLayerIndex + LayerSize * 5;` (scope `DisplayClusterConfiguratorGraphLayers`) — When a node is selected, a fixed value is added to its layer index to elevate it and its children above the normal layers.
- L45 _variable_ `const int32 OrnamentLayerIndex = SelectedLayerIndex + LayerSize * 5;` (scope `DisplayClusterConfiguratorGraphLayers`) — The ornament layer is meant for widgets such as the resize handler that should sit above everything in the layer stack, even selected items.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/EdNodes/DisplayClusterConfiguratorCanvasNode.h` (Private)


#### class `UDisplayClusterConfiguratorCanvasNode`  
`class UDisplayClusterConfiguratorCanvasNode final : public UDisplayClusterConfiguratorBaseNode`  
_L13-33_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfiguratorBaseNode`
- L20 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L24 _public prototype_ `virtual void TickPosition() override;`
- L25 _public function_ `virtual bool IsNodeAutoPositioned() const`
- L26 _public function_ `virtual bool IsNodeAutosized() const override`
- L29 _public function_ `const FVector2D& GetResolution() const`
- L32 _private member_ `FVector2D Resolution;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/EdNodes/DisplayClusterConfiguratorHostNode.h` (Private)


#### class `UDisplayClusterConfiguratorHostNode`  
`class UDisplayClusterConfiguratorHostNode final : public UDisplayClusterConfiguratorBaseNode`  
_L13-70_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfiguratorBaseNode`
- L19 _public prototype_ `virtual void Initialize(const FString& InNodeName, int32 InNodeZIndex, UObject* InObject, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit) override;`
- L20 _public prototype_ `virtual void Cleanup() override;`
- L23 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L24 _public function_ `virtual bool CanUserDeleteNode() const override`
- L27 _public prototype_ `FLinearColor GetHostColor() const;`
- L28 _public prototype_ `FText GetHostName() const;`
- L29 _public prototype_ `FVector2D GetHostOrigin(bool bInGlobalCoordinates = false) const;`
- L30 _public prototype_ `void SetHostOrigin(const FVector2D& NewOrigin, bool bInGlobalCoordinates = false);`
- L31 _public prototype_ `bool CanUserMoveNode() const;`
- L32 _public prototype_ `bool CanUserResizeNode() const;`
- L35 _public prototype_ `virtual FVector2D TransformPointToLocal(FVector2D GlobalPosition) const override;`
- L36 _public prototype_ `virtual FVector2D TransformPointToGlobal(FVector2D LocalPosition) const override;`
- L37 _public function_ `virtual FVector2D GetTranslationOffset() const override`
- L39 _public prototype_ `virtual FBox2D GetNodeBounds(bool bAsParent = false) const override;`
- L40 _public prototype_ `virtual FNodeAlignmentAnchors GetNodeAlignmentAnchors(bool bAsParent = false) const override;`
- L41 _public prototype_ `virtual bool IsNodeVisible() const override;`
- L42 _public prototype_ `virtual bool IsNodeUnlocked() const override;`
- L43 _public function_ `virtual bool IsNodeAutoPositioned() const`
- L44 _public function_ `virtual bool IsNodeAutosized() const override`
- L45 _public function_ `virtual bool CanNodeOverlapSiblings() const override`
- L46 _public function_ `virtual bool CanNodeEncroachChildBounds() const`
- L48 _public prototype_ `virtual void DeleteObject() override;`
- L51 _protected prototype_ `virtual void WriteNodeStateToObject() override;`
- L52 _protected prototype_ `virtual void ReadNodeStateFromObject() override;`
- L56 _private prototype_ `void OnPostEditChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent);`
- L60 _public member_ `static const FMargin VisualMargin;` — An extra padding around the node to display visual elements like borders
- L63 _public member_ `static const float DefaultSpaceBetweenHosts;` — When host are being programmatically positioned, this is the amount of space to place between hosts
- L66 _public member_ `static const float HorizontalSpanBetweenHosts;` — Total amount of horizontal space between adjacent hosts, including the visual margins of each
- L69 _public member_ `static const float VerticalSpanBetweenHosts;` — Total amount of vertical space between adjacent hosts, including the visual margins of each

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/EdNodes/DisplayClusterConfiguratorViewportNode.h` (Private)


#### class `UDisplayClusterConfiguratorViewportNode`  
`class UDisplayClusterConfiguratorViewportNode final : public UDisplayClusterConfiguratorBaseNode`  
_L19-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDisplayClusterConfiguratorBaseNode`
- L25 _public prototype_ `virtual void Initialize(const FString& InNodeName, int32 InNodeZIndex, UObject* InObject, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit) override;`
- L26 _public prototype_ `virtual void Cleanup() override;`
- L29 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L30 _public prototype_ `virtual void ResizeNode(const FVector2f& NewSize) override;`
- L31 _public function_ `virtual bool CanDuplicateNode() const override`
- L32 _public function_ `virtual bool CanUserDeleteNode() const override`
- L36 _public prototype_ `virtual bool IsNodeVisible() const override;`
- L37 _public prototype_ `virtual bool IsNodeUnlocked() const override;`
- L38 _public function_ `virtual bool CanNodeOverlapSiblings() const override`
- L39 _public function_ `virtual bool CanNodeHaveNegativePosition() const`
- L41 _public prototype_ `virtual void DeleteObject() override;`
- L44 _protected function_ `virtual bool CanAlignWithParent() const override`
- L45 _protected prototype_ `virtual void WriteNodeStateToObject() override;`
- L46 _protected prototype_ `virtual void ReadNodeStateFromObject() override;`
- L51 _public prototype_ `const FDisplayClusterConfigurationRectangle& GetCfgViewportRegion() const;` — Gets the underlying viewport configuration's region
- L54 _public prototype_ `const FDisplayClusterConfigurationViewport_RemapData& GetCfgViewportRemap() const;` — Gets the underlying viewport configuration's base remapping configuration
- L57 _public prototype_ `bool IsFixedAspectRatio() const;` — Gets whether the aspect ratio of the viewport's region is fixed
- L60 _public prototype_ `void RotateViewport(float InRotation);` — Rotates the viewport by the specified angle in degrees
- L63 _public prototype_ `void FlipViewport(bool bFlipHorizontal, bool bFlipVertical);` — Flips the viewport along the specified axis
- L66 _public prototype_ `void ResetTransform();` — Resets the viewport's transform
- L69 _public prototype_ `UTexture* GetPreviewTexture() const;` — Gets the preview texture that has been created for the viewport from the display cluster root actor
- L73 _private prototype_ `void OnPostEditChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent);` — Raised when a property within the viewport configuration object is changed
- L76 _private prototype_ `FMatrix2x2 GetSizeRotationMatrix(float AngleInDegrees) const;` — Gets the "rotation" matrix to use on the viewport's size vector to compute the size of the bounding box encapsulating the rotated viewport
- L79 _private prototype_ `bool IsRotationAngleDegenerate(float AngleInDegrees) const;` — Determines if the specified angle will create a degenerate size rotation matrix that has a determinant of 0, which happens at angles of 45 degree intervals
- L83 _private member_ `TSharedPtr<FDisplayClusterConfiguratorViewportViewModel> ViewportVM;` — The view model used to propagate property change events when the viewport configuration has changed
- L86 _private member_ `float ViewportAspectRatio;` — The current aspect ratio of the viewport's region

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/EdNodes/DisplayClusterConfiguratorWindowNode.h` (Private)


#### class `UDisplayClusterConfiguratorWindowNode`  
`class UDisplayClusterConfiguratorWindowNode final : public UDisplayClusterConfiguratorBaseNode`  
_L14-62_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfiguratorBaseNode`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPreviewImageChanged);`
- L21 _public typedef_ `using FOnPreviewImageChangedDelegate = FOnPreviewImageChanged::FDelegate;`
- L24 _public prototype_ `virtual void Initialize(const FString& InNodeName, int32 InNodeZIndex, UObject* InObject, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit) override;`
- L25 _public prototype_ `virtual void Cleanup() override;`
- L28 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L29 _public function_ `virtual bool CanDuplicateNode() const override`
- L30 _public function_ `virtual bool CanUserDeleteNode() const override`
- L33 _public prototype_ `const FDisplayClusterConfigurationRectangle& GetCfgWindowRect() const;`
- L34 _public prototype_ `FString GetCfgHost() const;`
- L35 _public prototype_ `const FString& GetPreviewImagePath() const;`
- L36 _public prototype_ `bool IsFixedAspectRatio() const;`
- L37 _public prototype_ `bool IsPrimary() const;`
- L39 _public prototype_ `FDelegateHandle RegisterOnPreviewImageChanged(const FOnPreviewImageChangedDelegate& Delegate);`
- L40 _public prototype_ `void UnregisterOnPreviewImageChanged(FDelegateHandle DelegateHandle);`
- L43 _public prototype_ `virtual bool IsNodeVisible() const override;`
- L44 _public prototype_ `virtual bool IsNodeUnlocked() const override;`
- L45 _public function_ `virtual bool CanNodeOverlapSiblings() const override`
- L46 _public prototype_ `virtual bool CanNodeExceedParentBounds() const override;`
- L48 _public prototype_ `virtual void DeleteObject() override;`
- L51 _protected function_ `virtual bool CanAlignWithParent() const override`
- L52 _protected prototype_ `virtual void WriteNodeStateToObject() override;`
- L53 _protected prototype_ `virtual void ReadNodeStateFromObject() override;`
- L57 _private prototype_ `void OnPostEditChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent);`
- L60 _private member_ `TSharedPtr<FDisplayClusterConfiguratorClusterNodeViewModel> ClusterNodeVM;`
- L61 _private member_ `FOnPreviewImageChanged PreviewImageChanged;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPreviewImageChanged);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/GraphNodes/SDisplayClusterConfiguratorBaseNode.h` (Private)


#### class `SAlignmentRuler`  
`class SAlignmentRuler : public SCompoundWidget`  
_L18-48_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAlignmentRuler) : _ColorAndOpacity(FLinearColor::White) , _Orientation(EOrientation::Orient_Horizontal) , _Length(100) , _Thickness(1)`
- L28 _public prototype_ `SLATE_ARGUMENT(FSlateColor, ColorAndOpacity) SLATE_ATTRIBUTE(EOrientation, Orientation) SLATE_ATTRIBUTE(FOptionalSize, Length) SLATE_ATTRIBUTE(FOptionalSize, Thickness) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `void SetOrientation(TAttribute<EOrientation> InOrientation);`
- L37 _public prototype_ `EOrientation GetOrientation() const;`
- L39 _public prototype_ `void SetLength(TAttribute<FOptionalSize> InLength);`
- L40 _public prototype_ `void SetThickness(TAttribute<FOptionalSize> InThickness);`
- L43 _private member_ `TSharedPtr<SBox> BoxWidget;`
- L45 _private member_ `TAttribute<EOrientation> Orientation;`
- L46 _private member_ `TAttribute<FOptionalSize> Length;`
- L47 _private member_ `TAttribute<FOptionalSize> Thickness;`

#### struct `FAlignmentRulerTarget`  
`struct FAlignmentRulerTarget`  
_L50-56_
- L52 _public member_ `TWeakObjectPtr<const UDisplayClusterConfiguratorBaseNode> TargetNode;`
- L53 _public member_ `bool bIsTargetingParent;`
- L54 _public member_ `bool bIsAdjacent;`
- L55 _public member_ `float Position;`

#### class `SDisplayClusterConfiguratorBaseNode`  
`class SDisplayClusterConfiguratorBaseNode : public SGraphNode`  
_L58-172_
- inherits: `SGraphNode`
- L62 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorBaseNode)`
- L64 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDisplayClusterConfiguratorBaseNode* InBaseNode, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L69 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L73 _public prototype_ `virtual void UpdateGraphNode() override;`
- L74 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L75 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L76 _public prototype_ `virtual void EndUserInteraction() const override;`
- L77 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L78 _public prototype_ `virtual bool CanBeSelected(const FVector2f& MousePositionInNode) const override;`
- L79 _public prototype_ `virtual bool ShouldAllowCulling() const override;`
- L80 _public prototype_ `virtual int32 GetSortDepth() const override;`
- L81 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L87 _public prototype_ `virtual void BeginUserInteraction() const;` — Raised whenever the user begins interacting with this node
- L95 _public prototype_ `virtual void SetNodeSize(const FVector2D InLocalSize, bool bFixedAspectRatio);` — Apply new node size @param InLocalSize - Size in local space @param bFixedAspectRatio - Indicates the node should have a fixed aspect ratio
- L100 _public prototype_ `virtual bool IsNodeVisible() const;` — @return true if the node should be visible
- L105 _public prototype_ `virtual bool IsNodeEnabled() const;` — @return true if the node should be enabled
- L110 _public prototype_ `virtual bool IsNodeUnlocked() const;` — @return true if the node should be locked, meaning it can't be selected, moved, or resized
- L115 _public prototype_ `virtual FVector2D GetSize() const;` — @return The intended size of the node, taken from the backing EdGraphNode
- L120 _public function_ `virtual bool CanNodeBeSnapAligned() const` — @return Wether this node can be snap aligned when the user activates snap aligning
- L123 _public function_ `virtual bool CanNodeBeResized() const` — @return Whether this node can be resized using the resize widget.
- L126 _public function_ `virtual float GetNodeMinimumSize() const` — @return The minimum size this node can be resized to.
- L129 _public function_ `virtual float GetNodeMaximumSize() const` — @return The maximum size this node can be resized to.
- L132 _public function_ `virtual bool IsAspectRatioFixed() const` — @return Whether this node's size is fixed to a specific aspect ratio.
- L135 _protected prototype_ `EVisibility GetNodeVisibility() const;`
- L136 _protected prototype_ `EVisibility GetSelectionVisibility() const;`
- L137 _protected prototype_ `TOptional<EMouseCursor::Type> GetCursor() const;`
- L139 _protected prototype_ `virtual int32 GetNodeLogicalLayer() const;`
- L140 _protected prototype_ `virtual int32 GetNodeVisualLayer() const;`
- L142 _protected prototype_ `FVector2f GetReizeHandleOffset() const;`
- L143 _protected prototype_ `EVisibility GetResizeHandleVisibility() const;`
- L145 _protected prototype_ `bool CanSnapAlign() const;`
- L146 _protected prototype_ `void UpdateAlignmentTarget(FAlignmentRulerTarget& OutTarget, const FNodeAlignment& Alignment, bool bIsTargetingParent);`
- L147 _protected prototype_ `void AddAlignmentRulerToOverlay(TArray<FOverlayWidgetInfo>& OverlayWidgets, TSharedPtr<SAlignmentRuler> RulerWidget, const FAlignmentRulerTarget& Target, const FVector2f& WidgetSize) const;`
- L150 _protected function_ `template<class TObjectType> TObjectType* GetGraphNodeChecked() const`
- L158 _protected prototype_ `bool IsGraphNodeValid() const;` — Checks that the graph node this widget displays is valid and has not been destroyed or garbage collected
- L161 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L163 _protected member_ `TSharedPtr<SAlignmentRuler> XAlignmentRuler;`
- L164 _protected member_ `TSharedPtr<SAlignmentRuler> YAlignmentRuler;`
- L167 _protected member_ `mutable FAlignmentRulerTarget XAlignmentTarget;` — These need to be mutable so they can be cleared in the node's EndUserInteraction call, which is a const function
- L168 _protected member_ `mutable FAlignmentRulerTarget YAlignmentTarget;`
- L171 _private member_ `static const float ResizeHandleSize;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/GraphNodes/SDisplayClusterConfiguratorCanvasNode.h` (Private)


#### class `SDisplayClusterConfiguratorCanvasNode`  
`class SDisplayClusterConfiguratorCanvasNode : public SDisplayClusterConfiguratorBaseNode`  
_L16-47_
- inherits: `SDisplayClusterConfiguratorBaseNode`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorCanvasNode)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDisplayClusterConfiguratorCanvasNode* InNode, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L27 _public prototype_ `virtual void UpdateGraphNode() override;`
- L28 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L29 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L30 _public prototype_ `virtual FVector2f GetPosition2f() const override;`
- L31 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L35 _public function_ `virtual bool CanNodeBeResized() const`
- L39 _private prototype_ `const FSlateBrush* GetSelectedBrush() const;`
- L40 _private prototype_ `FMargin GetBackgroundPosition() const;`
- L41 _private prototype_ `FText GetCanvasSizeText() const;`
- L44 _private member_ `TSharedPtr<SWidget> CanvasSizeTextWidget;`
- L46 _private member_ `FMargin CanvasPadding;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/GraphNodes/SDisplayClusterConfiguratorHostNode.h` (Private)


#### class `SDisplayClusterConfiguratorHostNode`  
`class SDisplayClusterConfiguratorHostNode : public SDisplayClusterConfiguratorBaseNode`  
_L10-54_
- inherits: `SDisplayClusterConfiguratorBaseNode`
- L16 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorHostNode) : _BorderThickness(FMargin(1))`
- L19 _public prototype_ `SLATE_ARGUMENT(FMargin, BorderThickness) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDisplayClusterConfiguratorHostNode* InHostNode, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L25 _public prototype_ `virtual void UpdateGraphNode() override;`
- L26 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L27 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L28 _public prototype_ `virtual FVector2f GetPosition2f() const override;`
- L32 _public prototype_ `virtual void SetNodeSize(const FVector2D InLocalSize, bool bFixedAspectRatio) override;`
- L33 _public function_ `virtual bool CanNodeBeSnapAligned() const override`
- L34 _public prototype_ `virtual bool CanNodeBeResized() const;`
- L38 _private prototype_ `FMargin GetBackgroundPosition() const;`
- L39 _private prototype_ `FMargin GetNodeOriginPosition() const;`
- L40 _private prototype_ `int32 GetNodeOriginLayerOffset() const;`
- L42 _private prototype_ `EVisibility GetHostNameVisibility() const;`
- L43 _private prototype_ `FText GetHostNameText() const;`
- L44 _private prototype_ `FText GetHostIPText() const;`
- L45 _private prototype_ `FText GetHostResolutionText() const;`
- L47 _private prototype_ `FSlateColor GetBorderColor() const;`
- L48 _private prototype_ `FSlateColor GetTextColor() const;`
- L50 _private prototype_ `EVisibility GetLockIconVisibility() const;`
- L53 _private member_ `FMargin BorderThickness;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/GraphNodes/SDisplayClusterConfiguratorViewportNode.h` (Private)


#### class `SDisplayClusterConfiguratorViewportNode`  
`class SDisplayClusterConfiguratorViewportNode : public SDisplayClusterConfiguratorBaseNode`  
_L18-72_
- inherits: `SDisplayClusterConfiguratorBaseNode`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorViewportNode)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDisplayClusterConfiguratorViewportNode* InViewportNode, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L31 _public prototype_ `virtual void UpdateGraphNode() override;`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L36 _public prototype_ `virtual bool IsNodeVisible() const override;`
- L37 _public function_ `virtual bool CanNodeBeSnapAligned() const override`
- L38 _public function_ `virtual bool CanNodeBeResized() const`
- L39 _public prototype_ `virtual float GetNodeMinimumSize() const override;`
- L40 _public prototype_ `virtual float GetNodeMaximumSize() const override;`
- L41 _public prototype_ `virtual bool IsAspectRatioFixed() const override;`
- L42 _public prototype_ `virtual void BeginUserInteraction() const override;`
- L43 _public prototype_ `virtual void EndUserInteraction() const override;`
- L47 _private prototype_ `FSlateColor GetBackgroundColor() const;`
- L48 _private prototype_ `const FSlateBrush* GetBackgroundBrush() const;`
- L49 _private prototype_ `TOptional<FSlateRenderTransform> GetBackgroundRenderTransform() const;`
- L50 _private prototype_ `const FSlateBrush* GetNodeShadowBrush() const;`
- L51 _private prototype_ `const FSlateBrush* GetBorderBrush() const;`
- L52 _private prototype_ `FSlateColor GetTextBoxColor() const;`
- L53 _private prototype_ `FSlateColor GetTextColor() const;`
- L54 _private prototype_ `FText GetPositionAndSizeText() const;`
- L55 _private prototype_ `FText GetTransformText() const;`
- L56 _private prototype_ `EVisibility GetTransformTextVisibility() const;`
- L57 _private prototype_ `FMargin GetBackgroundPosition() const;`
- L58 _private prototype_ `FMargin GetAreaResizeHandlePosition() const;`
- L59 _private prototype_ `bool IsViewportLocked() const;`
- L60 _private prototype_ `EVisibility GetLockIconVisibility() const;`
- L62 _private prototype_ `void UpdatePreviewTexture();`
- L65 _private member_ `FSlateBrush BackgroundActiveBrush;`
- L66 _private member_ `TSharedPtr<SImage> BackgroundImage;`
- L68 _private member_ `UTexture* CachedTexture;`
- L71 _private member_ `mutable bool bIsManagingPreviewTexture = false;` — If this object is managing the preview texture, such as through resizing.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/GraphNodes/SDisplayClusterConfiguratorWindowNode.h` (Private)


#### class `SDisplayClusterConfiguratorWindowNode`  
`class SDisplayClusterConfiguratorWindowNode : public SDisplayClusterConfiguratorBaseNode`  
_L17-78_
- inherits: `SDisplayClusterConfiguratorBaseNode`
- L24 _public prototype_ `~SDisplayClusterConfiguratorWindowNode();`
- L26 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorWindowNode)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDisplayClusterConfiguratorWindowNode* InWindowNode, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L35 _public prototype_ `virtual void UpdateGraphNode() override;`
- L36 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L37 _public prototype_ `virtual FVector2f GetPosition2f() const override;`
- L41 _public function_ `virtual bool CanNodeBeSnapAligned() const override`
- L42 _public function_ `virtual bool CanNodeBeResized() const`
- L43 _public prototype_ `virtual bool IsAspectRatioFixed() const override;`
- L46 _protected prototype_ `virtual int32 GetNodeLogicalLayer() const override;`
- L50 _private prototype_ `TSharedRef<SWidget> CreateBackground(const TAttribute<FSlateColor>& ColorAndOpacity);`
- L52 _private prototype_ `const FSlateBrush* GetBorderBrush() const;`
- L53 _private prototype_ `int32 GetBorderLayerOffset() const;`
- L54 _private prototype_ `const FSlateBrush* GetNodeShadowBrush() const;`
- L55 _private prototype_ `FMargin GetBackgroundPosition() const;`
- L56 _private prototype_ `FSlateColor GetCornerColor() const;`
- L57 _private prototype_ `FSlateColor GetTextColor() const;`
- L58 _private prototype_ `FVector2D GetPreviewImageSize() const;`
- L59 _private prototype_ `EVisibility GetPreviewImageVisibility() const;`
- L60 _private prototype_ `int32 GetNodeTitleLayerOffset() const;`
- L61 _private prototype_ `EVisibility GetNodeInfoVisibility() const;`
- L62 _private prototype_ `EVisibility GetCornerImageVisibility() const;`
- L64 _private prototype_ `bool CanShowInfoWidget() const;`
- L65 _private prototype_ `bool CanShowCornerImageWidget() const;`
- L66 _private prototype_ `bool IsClusterNodeLocked() const;`
- L68 _private prototype_ `void OnPreviewImageChanged();`
- L71 _private member_ `TSharedPtr<SDisplayClusterConfiguratorExternalImage> PreviewImageWidget;`
- L73 _private member_ `FVector2D WindowScaleFactor;`
- L75 _private member_ `FDelegateHandle ImageChangedHandle;`
- L77 _private member_ `bool bLayerAboveViewports = false;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/SDisplayClusterConfiguratorGraphEditor.h` (Private)


#### enum `ENodeAlignment`  
`enum class ENodeAlignment : uint8`  
_L28-36_
- L30 _public enumerator_ `Top`
- L31 _public enumerator_ `Middle`
- L32 _public enumerator_ `Bottom`
- L33 _public enumerator_ `Left`
- L34 _public enumerator_ `Center`
- L35 _public enumerator_ `Right`

#### class `SDisplayClusterConfiguratorGraphEditor`  
`class SDisplayClusterConfiguratorGraphEditor : public SGraphEditor , public FEditorUndoClient`  
_L38-134_
- inherits: `SGraphEditor,FEditorUndoClient`
- L43 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorGraphEditor) : _GraphToEdit(nullptr)`
- L47 _public prototype_ `SLATE_ARGUMENT(UEdGraph*, GraphToEdit) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, const TSharedRef<FDisplayClusterConfiguratorViewOutputMapping>& InViewOutputMapping);`
- L55 _public prototype_ `~SDisplayClusterConfiguratorGraphEditor();`
- L58 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L62 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L63 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L66 _public prototype_ `void FindAndSelectObjects(const TArray<UObject*>& ObjectsToSelect);`
- L67 _public prototype_ `void JumpToObject(UObject* InObject);`
- L69 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const`
- L72 _private prototype_ `void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);`
- L73 _private prototype_ `void OnNodeDoubleClicked(UEdGraphNode* ClickedNode);`
- L74 _private prototype_ `void OnObjectSelected();`
- L75 _private prototype_ `void OnConfigReloaded();`
- L76 _private prototype_ `void OnClusterChanged();`
- L77 _private prototype_ `void RebuildGraph();`
- L80 _private prototype_ `FActionMenuContent OnCreateNodeOrPinMenu(UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, FMenuBuilder* MenuBuilder, bool bIsDebugging);` — Callback to create contextual menu for graph nodes in graph panel
- L81 _private prototype_ `void BindCommands();`
- L83 _private prototype_ `void AddNewClusterNode();`
- L84 _private prototype_ `bool CanAddNewClusterNode() const;`
- L86 _private prototype_ `void AddNewViewport();`
- L87 _private prototype_ `bool CanAddNewViewport() const;`
- L89 _private prototype_ `void BrowseDocumentation();`
- L91 _private prototype_ `void DeleteSelectedNodes();`
- L92 _private prototype_ `bool CanDeleteNodes() const;`
- L94 _private prototype_ `void CopySelectedNodes();`
- L95 _private prototype_ `bool CanCopyNodes() const;`
- L97 _private prototype_ `void CutSelectedNodes();`
- L98 _private prototype_ `bool CanCutNodes() const;`
- L100 _private prototype_ `void PasteNodes();`
- L101 _private prototype_ `bool CanPasteNodes() const;`
- L103 _private prototype_ `void DuplicateNodes();`
- L104 _private prototype_ `bool CanDuplicateNodes() const;`
- L106 _private prototype_ `bool CanAlignNodes() const;`
- L107 _private prototype_ `void AlignNodes(ENodeAlignment Alignment);`
- L109 _private prototype_ `bool CanFillParentNode() const;`
- L110 _private prototype_ `void FillParentNode();`
- L112 _private prototype_ `bool CanSizeToChildNodes() const;`
- L113 _private prototype_ `void SizeToChildNodes();`
- L115 _private prototype_ `bool CanTransformNode() const;`
- L116 _private prototype_ `void RotateNode(float InRotation);`
- L117 _private prototype_ `void FlipNode(bool bFlipHorizontal, bool bFlipVertical);`
- L118 _private prototype_ `void ResetNodeTransform();`
- L120 _private prototype_ `void SortNodes();`
- L123 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L125 _private member_ `TWeakObjectPtr<UDisplayClusterConfiguratorGraph> ClusterConfiguratorGraph;`
- L127 _private member_ `TWeakPtr<FDisplayClusterConfiguratorViewOutputMapping> ViewOutputMappingPtr;`
- L130 _private member_ `bool bSelectionSetDirectly;` — Indicates if the graph's SelectedNodesChange event was invoked from user action or changed directly through code.
- L133 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The nodes menu command list

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/SDisplayClusterConfiguratorViewOutputMapping.h` (Private)


#### class `SDisplayClusterConfiguratorViewOutputMapping`  
`class SDisplayClusterConfiguratorViewOutputMapping : public SDisplayClusterConfiguratorViewBase , public FEditorUndoClient`  
_L18-74_
- inherits: `SDisplayClusterConfiguratorViewBase,FEditorUndoClient`
- L23 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorViewOutputMapping)`
- L29 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, const TSharedRef<SDisplayClusterConfiguratorGraphEditor>& InGraphEditor, const TSharedRef<FDisplayClusterConfiguratorViewOutputMapping> InViewOutputMapping);`
- L36 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L37 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L41 _private prototype_ `FGeometry MakeGeometryWindowLocal(const FGeometry& WidgetGeometry) const;`
- L43 _private prototype_ `EVisibility GetRulerVisibility() const;`
- L46 _private prototype_ `TSharedRef<SWidget> CreateOverlayUI();` — Creates graph controls
- L48 _private prototype_ `void BindCommands();`
- L50 _private prototype_ `FText GetCursorPositionText() const;`
- L52 _private prototype_ `EVisibility GetCursorPositionTextVisibility() const;`
- L54 _private prototype_ `float GetViewScale() const;`
- L55 _private prototype_ `FText GetViewScaleText() const;`
- L57 _private prototype_ `float GetDPIScale() const;`
- L60 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L62 _private member_ `TWeakPtr<SDisplayClusterConfiguratorGraphEditor> GraphEditorPtr;`
- L64 _private member_ `TWeakPtr<FDisplayClusterConfiguratorViewOutputMapping> ViewOutputMappingPtr;`
- L66 _private member_ `TSharedPtr<SDPIScaler> PreviewSurface;`
- L68 _private member_ `TSharedPtr<SDisplayClusterConfiguratorRuler> TopRuler;`
- L70 _private member_ `TSharedPtr<SDisplayClusterConfiguratorRuler> SideRuler;`
- L73 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The graph toolbar command list

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Widgets/SDisplayClusterConfiguratorExternalImage.h` (Private)


#### class `SDisplayClusterConfiguratorExternalImage`  
`class SDisplayClusterConfiguratorExternalImage : public SCompoundWidget`  
_L12-45_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorExternalImage) : _MaxImageSize(FVector2D(128.0f)) , _MinImageSize(FVector2D(64.0f)) , _ShowShadow(true)`
- L20 _public prototype_ `SLATE_ARGUMENT(FString, ImagePath) SLATE_ATTRIBUTE(FVector2D, MaxImageSize) SLATE_ATTRIBUTE(FVector2D, MinImageSize) SLATE_ARGUMENT(bool, ShowShadow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public function_ `const FString& GetImagePath() const`
- L29 _public prototype_ `void SetImagePath(const FString& NewImagePath);`
- L32 _private prototype_ `void LoadImage();`
- L34 _private prototype_ `FVector2D GetConstrainedImageSize() const;`
- L36 _private prototype_ `const FSlateBrush* GetImageBrush() const;`
- L37 _private prototype_ `FOptionalSize GetImageWidth() const;`
- L38 _private prototype_ `FOptionalSize GetImageHeight() const;`
- L41 _private member_ `TSharedPtr<FSlateDynamicImageBrush> ImageBrush;`
- L42 _private member_ `FString ImagePath;`
- L43 _private member_ `TAttribute<FVector2D> MaxImageSize;`
- L44 _private member_ `TAttribute<FVector2D> MinImageSize;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Widgets/SDisplayClusterConfiguratorExternalImagePicker.h` (Private)


#### class `SDisplayClusterConfiguratorExternalImagePicker`  
`class SDisplayClusterConfiguratorExternalImagePicker : public SCompoundWidget`  
_L14-36_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorExternalImagePicker)`
- L18 _public prototype_ `SLATE_ARGUMENT(FString, ImagePath) SLATE_ARGUMENT(TArray<FString>, Extensions) SLATE_EVENT(FOnImagePathPicked, OnImagePathPicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _private prototype_ `FReply OpenFileDialog();`
- L27 _private prototype_ `void ResetToDefault();`
- L28 _private prototype_ `bool DiffersFromDefault() const;`
- L31 _private member_ `TSharedPtr<SDisplayClusterConfiguratorExternalImage> ExternalImage;`
- L33 _private member_ `TArray<FString> Extensions;`
- L35 _private member_ `FOnImagePathPicked OnImagePathPicked;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnImagePathPicked, const FString&);`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FOnImagePathPicked, const FString&);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Widgets/SDisplayClusterConfiguratorLayeringBox.h` (Private)


#### class `SDisplayClusterConfiguratorLayeringBox`  
`class SDisplayClusterConfiguratorLayeringBox : public SBox`  
_L15-38_
- inherits: `SBox`
- desc: An SBox that allows an offset to be added to the box's content when being painted, giving more control over what layer the content gets rendered at. It also has the ability to draw a shadow that is appropriately layered behind the box.
- L18 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorLayeringBox) : _LayerOffset(0) , _ShadowBrush(FAppStyle::GetNoBrush()) , _ShadowSize(FVector2D(12.0f))`
- L23 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(int32, LayerOffset) SLATE_ATTRIBUTE(const FSlateBrush*, ShadowBrush) SLATE_ARGUMENT(FVector2D, ShadowSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L35 _private member_ `TAttribute<int32> LayerOffset;`
- L36 _private member_ `FInvalidatableBrushAttribute ShadowBrush;`
- L37 _private member_ `FVector2D ShadowSize;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Widgets/SDisplayClusterConfiguratorOutputMappingToolbar.h` (Private)


#### class `SDisplayClusterConfiguratorOutputMappingToolbar`  
`class SDisplayClusterConfiguratorOutputMappingToolbar : public SViewportToolBar`  
_L16-76_
- inherits: `SViewportToolBar`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorOutputMappingToolbar)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_ARGUMENT(TSharedPtr<FExtender>, Extenders) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FDisplayClusterConfiguratorViewOutputMapping>& InViewOutputMapping);`
- L32 _public prototype_ `TSharedRef< SWidget > MakeToolBar(const TSharedPtr< FExtender > InExtenders);` — Static: Creates a widget for the main tool bar @return	New widget
- L35 _private prototype_ `TSharedRef<SWidget> MakeWindowDisplayMenu();`
- L36 _private prototype_ `FText GetWindowDisplayText() const;`
- L38 _private prototype_ `TSharedRef<SWidget> MakeTransformMenu();`
- L40 _private prototype_ `TSharedRef<SWidget> MakeSnappingMenu();`
- L42 _private prototype_ `bool IsSnappingEnabled() const;`
- L44 _private prototype_ `bool IsAdjacentEdgeSnappingEnabled() const;`
- L45 _private prototype_ `TOptional<int> GetAdjacentEdgePadding() const;`
- L46 _private prototype_ `void SetAdjacentEdgePadding(int NewPadding);`
- L48 _private prototype_ `TOptional<int> GetSnapProximity() const;`
- L49 _private prototype_ `void SetSnapProximity(int NewSnapProximity);`
- L51 _private prototype_ `TSharedRef<SWidget> MakeAdvancedMenu();`
- L53 _private prototype_ `void MakeHostArrangementTypeSubMenu(FMenuBuilder& MenuBuilder);`
- L54 _private prototype_ `bool IsHostArrangementTypeChecked(EHostArrangementType ArrangementType) const;`
- L55 _private prototype_ `void SetHostArrangementType(EHostArrangementType ArrangementType);`
- L57 _private prototype_ `TOptional<int> GetHostWrapThreshold() const;`
- L58 _private prototype_ `void SetHostWrapThreshold(int NewWrapThreshold);`
- L60 _private prototype_ `TOptional<int> GetHostGridSize() const;`
- L61 _private prototype_ `void SetHostGridSize(int NewGridSize);`
- L63 _private prototype_ `TSharedRef<SWidget> MakeViewScaleMenu();`
- L65 _private prototype_ `bool IsViewScaleChecked(int32 Index) const;`
- L66 _private prototype_ `void SetViewScale(int32 Index);`
- L67 _private prototype_ `FText GetViewScaleText() const;`
- L71 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list
- L72 _private member_ `TWeakPtr<FDisplayClusterConfiguratorViewOutputMapping> ViewOutputMappingPtr;`
- L75 _private member_ `static const TArray<float> ViewScales;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Widgets/SDisplayClusterConfiguratorResizer.h` (Private)


#### class `SDisplayClusterConfiguratorResizer`  
`class SDisplayClusterConfiguratorResizer : public SCompoundWidget`  
_L14-52_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorResizer) : _MinimumSize(0) , _MaximumSize(FLT_MAX) , _IsFixedAspectRatio(false)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(float, MinimumSize) SLATE_ATTRIBUTE(float, MaximumSize) SLATE_ATTRIBUTE(bool, IsFixedAspectRatio) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, const TSharedRef<SDisplayClusterConfiguratorBaseNode>& InBaseNode);`
- L32 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L34 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _private prototype_ `float GetDPIScale() const;`
- L39 _private prototype_ `bool IsAspectRatioFixed() const;`
- L42 _private member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L43 _private member_ `TWeakPtr<SDisplayClusterConfiguratorBaseNode> BaseNodePtr;`
- L44 _private member_ `TSharedPtr<FScopedTransaction> ScopedTransaction;`
- L46 _private member_ `bool bResizing;`
- L47 _private member_ `float CurrentAspectRatio;`
- L49 _private member_ `TAttribute<float> MinimumSize;`
- L50 _private member_ `TAttribute<float> MaximumSize;`
- L51 _private member_ `TAttribute<bool> IsFixedAspectRatio;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/OutputMapping/Widgets/SDisplayClusterConfiguratorRuler.h` (Private)


#### class `SDisplayClusterConfiguratorRuler`  
`class SDisplayClusterConfiguratorRuler : public SCompoundWidget`  
_L13-97_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorRuler) : _Orientation(Orient_Horizontal) , _OnMouseButtonDown()`
- L24 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L47 _public prototype_ `float DetermineOptimalSpacing(float InPixelsPerInput, uint32 MinTick, float MinTickSpacing) const;` — Determines the optimal spacing between tick marks in the slider for a given pixel density Increments until a minimum amount of slate units specified by MinTick is reached @param InPixelsPerInput	The density of pixels between each input @param MinTick			The minimum slate units per tick allowed @param MinTickSpacing	The minimum tick spacing in time units allowed @return the optimal spacing in time units
- L56 _public prototype_ `void SetRuling(FVector2D AbsoluteOrigin, float SlateToUnitScale);` — Sets the rules to use when rendering the ruler. @param AbsoluteOrigin The origin of the ruler in absolute window space. @param SlateToUnitScale The scaler applied to slate units to get the same number of units currently being displayed by the rule marks.
- L63 _public prototype_ `void SetCursor(TOptional<FVector2D> AbsoluteCursor);` — Sets the cursor position in window absolute space. @param AbsoluteCursor The position of the cursor in absolute window space.
- L67 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L68 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L69 _protected prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L70 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L71 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L72 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L80 _private prototype_ `int32 DrawTicks(FSlateWindowElementList& OutDrawElements, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs) const;` — Draws the ticks on the track
- L84 _private member_ `EOrientation Orientation;` — The orientation of the ruler
- L87 _private member_ `FVector2D AbsoluteOrigin;` — The absolute origin of the document being measured.  The 0 on the ruler will start here.
- L90 _private member_ `TOptional<FVector2D> AbsoluteCursor;` — The absolute position of the cursor so that little lines can be drawn showing the cursors position on the ruler.
- L93 _private member_ `float SlateToUnitScale;` — The current conversion from Slate Pixel To Unit Size.
- L96 _private member_ `FPointerEventHandler MouseButtonDownHandler;` — The public event we expose when the mouse button is pressed onto the ruler.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/SCSEditor/SDisplayClusterConfiguratorComponentCombo.h` (Private)


#### class `SDisplayClusterConfiguratorComponentClassCombo`  
`class SDisplayClusterConfiguratorComponentClassCombo : public SCompoundWidget`  
_L11-85_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS( SDisplayClusterConfiguratorComponentClassCombo ) : _IncludeText(true)`
- L18 _public prototype_ `SLATE_ATTRIBUTE(bool, IncludeText) SLATE_EVENT( FSubobjectClassSelected, OnSubobjectClassSelected ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `~SDisplayClusterConfiguratorComponentClassCombo();`
- L28 _public prototype_ `void ClearSelection();` — Clear the current combo list selection
- L33 _public prototype_ `void GenerateFilteredComponentList();` — Updates the filtered list of component names.
- L35 _public prototype_ `FText GetCurrentSearchString() const;`
- L41 _public prototype_ `void OnSearchBoxTextChanged( const FText& InSearchText );` — Called when the user changes the text in the search box. @param InSearchText The new search string.
- L44 _public prototype_ `void OnSearchBoxTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Callback when the user commits the text in the searchbox
- L46 _public prototype_ `void OnAddComponentSelectionChanged( FComponentClassComboEntryPtr InItem, ESelectInfo::Type SelectInfo );`
- L48 _public prototype_ `TSharedRef<ITableRow> GenerateAddComponentRow( FComponentClassComboEntryPtr Entry, const TSharedRef<STableViewBase> &OwnerTable ) const;`
- L51 _public prototype_ `void UpdateComponentClassList();` — Update list of component classes
- L55 _protected prototype_ `void GenerateComponentClassList();` — Generate the source component list to use for nDisplay.
- L57 _protected prototype_ `FText GetFriendlyComponentName(FComponentClassComboEntryPtr Entry) const;`
- L59 _protected prototype_ `TSharedRef<SToolTip> GetComponentToolTip(FComponentClassComboEntryPtr Entry) const;`
- L61 _protected member_ `FSubobjectClassSelected OnSubobjectClassSelected;`
- L63 _protected member_ `TArray<FComponentClassComboEntryPtr>* ComponentClassListPtr;`
- L66 _protected member_ `TArray<FComponentClassComboEntryPtr> ComponentClassList;` — List of component class names used by combo box
- L69 _protected member_ `TArray<FComponentClassComboEntryPtr> FilteredComponentClassList;` — List of component class names, filtered by the current search string
- L72 _protected member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;` — The current search string
- L75 _protected member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box control - part of the combo drop down
- L78 _protected member_ `TSharedPtr<class SPositiveActionButton> AddNewButton;` — The Add combo button.
- L81 _protected member_ `TSharedPtr< SListView<FComponentClassComboEntryPtr> > ComponentClassListView;` — The component list control - part of the combo drop down
- L84 _protected member_ `int32 PrevSelectedIndex;` — Cached selection index used to skip over unselectable items

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/SDisplayClusterConfiguratorViewBase.h` (Private)


#### class `SDisplayClusterConfiguratorViewBase`  
`class SDisplayClusterConfiguratorViewBase : public IDisplayClusterConfiguratorViewBase`  
_L13-36_
- inherits: `IDisplayClusterConfiguratorViewBase`
- L18 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorViewBase) : _Padding(FMargin(0)) , _Content()`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L32 _public prototype_ `virtual void ConstructChildren(const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;`
- L35 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/Cluster/DisplayClusterConfiguratorViewCluster.h` (Private)


#### class `FDisplayClusterConfiguratorViewCluster`  
`class FDisplayClusterConfiguratorViewCluster : public FDisplayClusterConfiguratorViewTree`  
_L10-79_
- inherits: `FDisplayClusterConfiguratorViewTree`
- L21 _public prototype_ `FDisplayClusterConfiguratorViewCluster(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& Toolkit);`
- L24 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L29 _public prototype_ `virtual void ConstructColumns(TArray<SHeaderRow::FColumn::FArguments>& OutColumnArgs) override;`
- L31 _public prototype_ `virtual void FillContextMenu(FMenuBuilder& MenuBuilder) override;`
- L32 _public prototype_ `virtual void BindPinnableCommands(FUICommandList_Pinnable& CommandList) override;`
- L33 _public function_ `virtual bool ShowAddNewButton() const override`
- L34 _public prototype_ `virtual void FillAddNewMenu(FMenuBuilder& MenuBuilder) override;`
- L35 _public prototype_ `virtual FText GetCornerText() const override;`
- L39 _private prototype_ `void OnClusterChanged();`
- L41 _private prototype_ `void CutSelectedNodes();`
- L42 _private prototype_ `bool CanCutSelectedNodes() const;`
- L44 _private prototype_ `void CopySelectedNodes();`
- L45 _private prototype_ `bool CanCopySelectedNodes() const;`
- L47 _private prototype_ `void PasteNodes();`
- L48 _private prototype_ `bool CanPasteNodes() const;`
- L50 _private prototype_ `void DuplicateSelectedNodes();`
- L51 _private prototype_ `bool CanDuplicateSelectedNodes() const;`
- L53 _private prototype_ `void DeleteSelectedNodes();`
- L54 _private prototype_ `bool CanDeleteSelectedNodes() const;`
- L56 _private prototype_ `void RenameSelectedNode();`
- L57 _private prototype_ `bool CanRenameSelectedNode() const;`
- L59 _private prototype_ `void HideSelected();`
- L60 _private prototype_ `bool CanHideSelected() const;`
- L62 _private prototype_ `void ShowSelected();`
- L63 _private prototype_ `bool CanShowSelected() const;`
- L65 _private prototype_ `void ShowSelectedOnly();`
- L66 _private prototype_ `bool CanShowSelectedOnly() const;`
- L68 _private prototype_ `void ShowAll();`
- L70 _private prototype_ `void SetAsPrimary();`
- L71 _private prototype_ `bool CanSetAsPrimary() const;`
- L73 _private prototype_ `void AddNewClusterNode(FVector2D PresetSize);`
- L74 _private prototype_ `bool CanAddNewClusterNode() const;`
- L76 _private prototype_ `void AddNewViewport(FVector2D PresetSize);`
- L77 _private prototype_ `bool CanAddNewViewport() const;`

#### struct `FDisplayClusterConfiguratorViewCluster::Columns`  
`struct Columns`  
_L14-19_
- L16 _public member_ `static const FName Host;`
- L17 _public member_ `static const FName Visible;`
- L18 _public member_ `static const FName Enabled;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/Cluster/DisplayClusterConfiguratorViewClusterBuilder.h` (Private)


#### class `FDisplayClusterConfiguratorViewClusterBuilder`  
`class FDisplayClusterConfiguratorViewClusterBuilder : public FDisplayClusterConfiguratorTreeBuilder`  
_L9-23_
- inherits: `FDisplayClusterConfiguratorTreeBuilder`
- L13 _public prototype_ `FDisplayClusterConfiguratorViewClusterBuilder(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L16 _public prototype_ `virtual void Build(FDisplayClusterConfiguratorTreeBuilderOutput& Output) override;`
- L20 _private prototype_ `void AddCluster(FDisplayClusterConfiguratorTreeBuilderOutput& Output, UDisplayClusterConfigurationData* InConfigurationTempConfig, UObject* InObjectToEdit);`
- L21 _private prototype_ `void AddClusterNodes(FDisplayClusterConfiguratorTreeBuilderOutput& Output, UDisplayClusterConfigurationData* InConfigurationTempConfig, UObject* InObjectToEdit);`
- L22 _private prototype_ `void AddClusterNodeViewport(FDisplayClusterConfiguratorTreeBuilderOutput& Output, UDisplayClusterConfigurationData* InConfigurationTempConfig, const FString& NodeId, const FString& ParentNodeId, UObject* InObjectToEdit);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/Cluster/TreeItems/DisplayClusterConfiguratorTreeItemCluster.h` (Private)


#### class `FDisplayClusterConfiguratorTreeItemCluster`  
`class FDisplayClusterConfiguratorTreeItemCluster : public FDisplayClusterConfiguratorTreeItem`  
_L11-55_
- inherits: `FDisplayClusterConfiguratorTreeItem`
- L15 _public prototype_ `NDISPLAY_TREE_ITEM_TYPE(FDisplayClusterConfiguratorTreeItemCluster, FDisplayClusterConfiguratorTreeItem) FDisplayClusterConfiguratorTreeItemCluster(const FName& InName, const TSharedRef<IDisplayClusterConfiguratorViewTree>& InViewTree, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, UObject* InObjectToEdit, FString InIconStyle, bool InbRoot = false);`
- L25 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, TSharedPtr<ITableRow> TableRow, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;`
- L26 _public prototype_ `virtual void OnItemDoubleClicked() override;`
- L27 _public prototype_ `virtual void OnMouseEnter() override;`
- L28 _public prototype_ `virtual void OnMouseLeave() override;`
- L29 _public prototype_ `virtual bool IsHovered() const override;`
- L31 _public function_ `virtual FName GetRowItemName() const override`
- L32 _public function_ `virtual FString GetIconStyle() const override`
- L36 _protected function_ `virtual bool CanClusterItemBeHidden() const`
- L37 _protected function_ `virtual bool CanClusterItemBeLocked() const`
- L38 _protected function_ `virtual bool IsClusterItemGrouped() const`
- L40 _protected function_ `virtual bool IsClusterItemVisible() const`
- L41 _protected function_ `virtual bool IsClusterItemUnlocked() const`
- L43 _protected function_ `virtual void ToggleClusterItemVisibility()`
- L44 _protected function_ `virtual void ToggleClusterItemLock()`
- L46 _protected function_ `virtual FSlateColor GetClusterItemGroupColor() const`
- L47 _protected function_ `virtual FReply OnClusterItemGroupClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L49 _protected prototype_ `EVisibility GetVisibleButtonVisibility() const;`
- L50 _protected prototype_ `EVisibility GetLockButtonVisibility() const;`
- L53 _protected member_ `FName Name;`
- L54 _protected member_ `FString IconStyle;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/Cluster/TreeItems/DisplayClusterConfiguratorTreeItemClusterNode.h` (Private)


#### class `FDisplayClusterConfiguratorTreeItemClusterNode`  
`class FDisplayClusterConfiguratorTreeItemClusterNode : public FDisplayClusterConfiguratorTreeItemCluster`  
_L12-66_
- inherits: `FDisplayClusterConfiguratorTreeItemCluster`
- L16 _public prototype_ `NDISPLAY_TREE_ITEM_TYPE(FDisplayClusterConfiguratorTreeItemClusterNode, FDisplayClusterConfiguratorTreeItemCluster) FDisplayClusterConfiguratorTreeItemClusterNode(const FName& InName, const TSharedRef<IDisplayClusterConfiguratorViewTree>& InViewTree, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, UObject* InObjectToEdit, UDisplayClusterConfigurationHostDisplayData* InHostObject);`
- L24 _public prototype_ `UDisplayClusterConfigurationHostDisplayData* GetHostDisplayData();`
- L25 _public prototype_ `void SelectHostDisplayData();`
- L27 _public prototype_ `void SetVisible(bool bIsVisible);`
- L28 _public prototype_ `void SetUnlocked(bool bIsUnlocked);`
- L31 _public prototype_ `virtual void DeleteItem() const override;`
- L32 _public function_ `virtual bool CanHideItem() const override`
- L33 _public function_ `virtual void SetItemHidden(bool bIsHidden)`
- L35 _public prototype_ `virtual FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L37 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L38 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override;`
- L39 _public prototype_ `virtual FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override;`
- L42 _protected prototype_ `virtual void FillItemColumn(TSharedPtr<SHorizontalBox> Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;`
- L43 _protected prototype_ `virtual void OnDisplayNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo) override;`
- L45 _protected function_ `virtual bool CanClusterItemBeHidden() const override`
- L46 _protected function_ `virtual bool CanClusterItemBeLocked() const override`
- L47 _protected function_ `virtual bool IsClusterItemGrouped() const override`
- L49 _protected prototype_ `virtual bool IsClusterItemVisible() const override;`
- L50 _protected prototype_ `virtual bool IsClusterItemUnlocked() const override;`
- L52 _protected prototype_ `virtual void ToggleClusterItemVisibility() override;`
- L53 _protected prototype_ `virtual void ToggleClusterItemLock() override;`
- L55 _protected prototype_ `virtual FSlateColor GetClusterItemGroupColor() const override;`
- L56 _protected prototype_ `virtual FReply OnClusterItemGroupClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L61 _private prototype_ `EVisibility GetPrimaryLabelVisibility() const;`
- L62 _private prototype_ `bool CanDropViewports(TSharedPtr<FDisplayClusterConfiguratorViewportDragDropOp> ViewportDragDropOp, FText& OutErrorMessage) const;`
- L65 _private member_ `TWeakObjectPtr<UDisplayClusterConfigurationHostDisplayData> HostObject;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/Cluster/TreeItems/DisplayClusterConfiguratorTreeItemHost.h` (Private)


#### class `FDisplayClusterConfiguratorTreeItemHost`  
`class FDisplayClusterConfiguratorTreeItemHost : public FDisplayClusterConfiguratorTreeItemCluster`  
_L11-61_
- inherits: `FDisplayClusterConfiguratorTreeItemCluster`
- L15 _public prototype_ `NDISPLAY_TREE_ITEM_TYPE(FDisplayClusterConfiguratorTreeItemHost, FDisplayClusterConfiguratorTreeItemCluster) FDisplayClusterConfiguratorTreeItemHost(const FName& InName, const TSharedRef<IDisplayClusterConfiguratorViewTree>& InViewTree, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, UObject* InObjectToEdit);`
- L23 _public prototype_ `virtual void Initialize() override;`
- L24 _public prototype_ `virtual void DeleteItem() const override;`
- L26 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L27 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L28 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override;`
- L29 _public prototype_ `virtual FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override;`
- L31 _public prototype_ `virtual FName GetAttachName() const override;`
- L33 _public function_ `virtual bool CanDuplicateItem() const override`
- L34 _public function_ `virtual bool CanHideItem() const override`
- L35 _public prototype_ `virtual void SetItemHidden(bool bIsHidden);`
- L38 _protected prototype_ `virtual void FillItemColumn(TSharedPtr<SHorizontalBox> Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;`
- L39 _protected prototype_ `virtual void OnDisplayNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo) override;`
- L41 _protected function_ `virtual bool CanClusterItemBeHidden() const override`
- L42 _protected function_ `virtual bool CanClusterItemBeLocked() const override`
- L43 _protected function_ `virtual bool IsClusterItemGrouped() const override`
- L45 _protected prototype_ `virtual bool IsClusterItemVisible() const override;`
- L46 _protected prototype_ `virtual bool IsClusterItemUnlocked() const override;`
- L48 _protected prototype_ `virtual void ToggleClusterItemVisibility() override;`
- L49 _protected prototype_ `virtual void ToggleClusterItemLock() override;`
- L51 _protected prototype_ `virtual FSlateColor GetClusterItemGroupColor() const override;`
- L52 _protected prototype_ `virtual FReply OnClusterItemGroupClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _private prototype_ `FText GetHostAddress() const;`
- L58 _private prototype_ `bool CanDropClusterNodes(TSharedPtr<FDisplayClusterConfiguratorClusterNodeDragDropOp> ClusterNodeDragDropOp, FText& OutErrorMessage) const;`
- L60 _private prototype_ `void OnPostEditChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/Cluster/TreeItems/DisplayClusterConfiguratorTreeItemViewport.h` (Private)


#### class `FDisplayClusterConfiguratorTreeItemViewport`  
`class FDisplayClusterConfiguratorTreeItemViewport : public FDisplayClusterConfiguratorTreeItemCluster`  
_L10-57_
- inherits: `FDisplayClusterConfiguratorTreeItemCluster`
- L14 _public prototype_ `NDISPLAY_TREE_ITEM_TYPE(FDisplayClusterConfiguratorTreeItemViewport, FDisplayClusterConfiguratorTreeItemCluster) FDisplayClusterConfiguratorTreeItemViewport(const FName& InName, const TSharedRef<IDisplayClusterConfiguratorViewTree>& InViewTree, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, UObject* InObjectToEdit);`
- L21 _public prototype_ `void SetVisible(bool bIsVisible);`
- L22 _public prototype_ `void SetUnlocked(bool bIsUnlocked);`
- L25 _public prototype_ `virtual void OnSelection() override;`
- L27 _public prototype_ `virtual void DeleteItem() const override;`
- L28 _public function_ `virtual bool CanHideItem() const override`
- L29 _public function_ `virtual void SetItemHidden(bool bIsHidden)`
- L31 _public prototype_ `virtual FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override;`
- L33 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L34 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override;`
- L35 _public prototype_ `virtual FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override;`
- L38 _protected prototype_ `virtual void OnDisplayNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo) override;`
- L40 _protected function_ `virtual bool CanClusterItemBeHidden() const override`
- L41 _protected function_ `virtual bool CanClusterItemBeLocked() const override`
- L42 _protected function_ `virtual bool IsClusterItemGrouped() const override`
- L44 _protected prototype_ `virtual bool IsClusterItemVisible() const override;`
- L45 _protected prototype_ `virtual bool IsClusterItemUnlocked() const override;`
- L47 _protected prototype_ `virtual void ToggleClusterItemVisibility() override;`
- L48 _protected prototype_ `virtual void ToggleClusterItemLock() override;`
- L50 _protected prototype_ `virtual FSlateColor GetClusterItemGroupColor() const override;`
- L51 _protected prototype_ `virtual FReply OnClusterItemGroupClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L55 _private prototype_ `FSlateColor GetHostColor() const;`
- L56 _private prototype_ `FReply OnHostClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/DisplayClusterConfiguratorTreeBuilder.h` (Private)


#### class `FDisplayClusterConfiguratorTreeBuilder`  
`class FDisplayClusterConfiguratorTreeBuilder : public IDisplayClusterConfiguratorTreeBuilder`  
_L13-26_
- inherits: `IDisplayClusterConfiguratorTreeBuilder`
- L17 _public prototype_ `FDisplayClusterConfiguratorTreeBuilder(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit);`
- L20 _public prototype_ `virtual void Initialize(const TSharedRef<IDisplayClusterConfiguratorViewTree>& InConfiguratorTree) override;`
- L24 _protected member_ `TWeakPtr<IDisplayClusterConfiguratorViewTree> ConfiguratorTreePtr;`
- L25 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/DisplayClusterConfiguratorTreeItem.h` (Private)


#### class `FDisplayClusterConfiguratorTreeItem`  
`class FDisplayClusterConfiguratorTreeItem : public IDisplayClusterConfiguratorTreeItem`  
_L14-123_
- inherits: `IDisplayClusterConfiguratorTreeItem`
- L20 _public function_ `FDisplayClusterConfiguratorTreeItem( const TSharedRef<IDisplayClusterConfiguratorViewTree>& InViewTree, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, UObject* InObjectToEdit, bool InbRoot) : ViewTreePtr(InViewTree) , ToolkitPtr(InToolkit) , FilterResult(EDisplayClusterConfiguratorTreeFilterResult::Shown) , ObjectToEdit(InObjectToEdit) , bRoot(InbRoot)`
- L34 _public function_ `virtual void OnSelection() override`
- L35 _public function_ `virtual UObject* GetObject() const override`
- L36 _public prototype_ `virtual bool IsSelected() override;`
- L41 _public function_ `virtual void Initialize() override`
- L42 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, const TAttribute<FText>& InFilterText) override;`
- L43 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, TSharedPtr<ITableRow> TableRow, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;`
- L44 _public function_ `virtual TSharedRef<SWidget> GenerateInlineEditWidget(const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override`
- L45 _public function_ `virtual bool HasInlineEditor() const override`
- L46 _public function_ `virtual void ToggleInlineEditorExpansion() override`
- L47 _public function_ `virtual bool IsInlineEditorExpanded() const override`
- L48 _public function_ `virtual FName GetAttachName() const override`
- L49 _public function_ `virtual FString GetIconStyle() const override`
- L50 _public prototype_ `virtual void GetParentObjectsRecursive(TArray<UObject*>& OutObjects) const override;`
- L51 _public prototype_ `virtual void GetChildrenObjectsRecursive(TArray<UObject*>& OutObjects) const override;`
- L52 _public prototype_ `virtual bool CanRenameItem() const override;`
- L53 _public prototype_ `virtual void RequestRename() override;`
- L54 _public prototype_ `virtual bool CanDeleteItem() const override;`
- L55 _public function_ `virtual void DeleteItem() const override`
- L56 _public prototype_ `bool CanDuplicateItem() const override;`
- L57 _public function_ `virtual bool CanHideItem() const override`
- L58 _public function_ `virtual void SetItemHidden(bool bIsHidden)`
- L60 _public function_ `virtual void OnItemDoubleClicked() override`
- L61 _public function_ `virtual void OnMouseEnter() override`
- L62 _public function_ `virtual void OnMouseLeave() override`
- L63 _public function_ `virtual bool IsHovered() const override`
- L64 _public prototype_ `virtual bool IsChildOfRecursive(const TSharedRef<IDisplayClusterConfiguratorTreeItem>& InParentTreeItem) const override;`
- L65 _public function_ `virtual bool IsRoot() const`
- L66 _public function_ `virtual FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L67 _public function_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) override`
- L68 _public function_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override`
- L69 _public function_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override`
- L70 _public function_ `virtual FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) override`
- L71 _public function_ `virtual FReply HandleDrop(FDragDropEvent const& DragDropEvent) override`
- L72 _public function_ `virtual TSharedPtr<IDisplayClusterConfiguratorTreeItem> GetParent() const override`
- L73 _public function_ `virtual void SetParent(TSharedPtr<IDisplayClusterConfiguratorTreeItem> InParent) override`
- L74 _public function_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& GetChildren() override`
- L75 _public function_ `virtual const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& GetChildrenConst() const`
- L76 _public function_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& GetFilteredChildren() override`
- L77 _public function_ `virtual TSharedRef<IDisplayClusterConfiguratorViewTree> GetConfiguratorTree() const override`
- L78 _public prototype_ `virtual EDisplayClusterConfiguratorTreeFilterResult ApplyFilter(const TSharedPtr<FTextFilterExpressionEvaluator>& TextFilter) override;`
- L79 _public function_ `virtual EDisplayClusterConfiguratorTreeFilterResult GetFilterResult() const override`
- L80 _public function_ `virtual void SetFilterResult(EDisplayClusterConfiguratorTreeFilterResult InResult) override`
- L81 _public function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L82 _public function_ `virtual bool IsInitiallyExpanded() const override`
- L86 _protected prototype_ `virtual void FillItemColumn(TSharedPtr<SHorizontalBox> Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected);`
- L88 _protected prototype_ `virtual bool IsReadOnly() const;`
- L89 _protected function_ `virtual void OnDisplayNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo)`
- L91 _protected prototype_ `virtual FText GetRowItemText() const;`
- L94 _protected function_ `template<class TObjectType> TObjectType* GetObjectChecked() const`
- L103 _protected member_ `TWeakPtr<IDisplayClusterConfiguratorTreeItem> Parent;` — The parent of this item
- L106 _protected member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> Children;` — The children of this item
- L109 _protected member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> FilteredChildren;` — The filtered children of this item
- L111 _protected member_ `TWeakPtr<IDisplayClusterConfiguratorViewTree> ViewTreePtr;`
- L113 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L116 _protected member_ `EDisplayClusterConfiguratorTreeFilterResult FilterResult;` — The current filter result
- L118 _protected member_ `TWeakObjectPtr<UObject> ObjectToEdit;`
- L120 _protected member_ `bool bRoot;`
- L122 _protected member_ `TSharedPtr<SInlineEditableTextBlock> DisplayNameTextBlock;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/DisplayClusterConfiguratorTreeViewCommands.h` (Private)


#### class `FDisplayClusterConfiguratorTreeViewCommands`  
`class FDisplayClusterConfiguratorTreeViewCommands : public TCommands<FDisplayClusterConfiguratorTreeViewCommands>`  
_L11-35_
- inherits: `TCommands<FDisplayClusterConfiguratorTreeViewCommands>`
- L15 _public function_ `FDisplayClusterConfiguratorTreeViewCommands() : TCommands<FDisplayClusterConfiguratorTreeViewCommands> ( TEXT("ConfiguratorViewTree"),`
- L27 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L29 _public member_ `TSharedPtr<FUICommandInfo> ShowAll;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ShowSelectedOnly;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ShowSelected;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> HideSelected;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SetAsPrimary;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/DisplayClusterConfiguratorViewTree.h` (Private)


#### class `FDisplayClusterConfiguratorViewTree`  
`class FDisplayClusterConfiguratorViewTree : public IDisplayClusterConfiguratorViewTree , public FEditorUndoClient`  
_L18-108_
- inherits: `IDisplayClusterConfiguratorViewTree,FEditorUndoClient`
- L23 _public prototype_ `FDisplayClusterConfiguratorViewTree(const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& Toolkit);`
- L24 _public prototype_ `virtual ~FDisplayClusterConfiguratorViewTree();`
- L28 _public function_ `virtual void PostUndo(bool bSuccess) override`
- L29 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L33 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L34 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() override;`
- L35 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L37 _public function_ `virtual bool GetIsEnabled() const override`
- L41 _public prototype_ `virtual void RebuildTree() override;`
- L42 _public prototype_ `virtual UDisplayClusterConfigurationData* GetEditorData() const override;`
- L43 _public prototype_ `virtual void ConstructColumns(TArray<SHeaderRow::FColumn::FArguments>& OutColumnArgs) override;`
- L45 _public prototype_ `virtual void SetHoveredItem(const TSharedRef<IDisplayClusterConfiguratorTreeItem>& InTreeItem) override;`
- L46 _public prototype_ `virtual void ClearHoveredItem() override;`
- L47 _public prototype_ `virtual TSharedPtr<IDisplayClusterConfiguratorTreeItem> GetHoveredItem() const override;`
- L48 _public prototype_ `virtual void SetSelectedItems(const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InTreeItems) override;`
- L49 _public prototype_ `virtual void ClearSelection() override;`
- L50 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> GetSelectedItems() const override;`
- L51 _public prototype_ `virtual void GetSelectedObjects(TArray<UObject*>& OutObjects) const override;`
- L52 _public prototype_ `virtual void FindAndSelectObjects(const TArray<UObject*>& ObjectsToSelect) override;`
- L53 _public prototype_ `virtual void Filter(const FDisplayClusterConfiguratorTreeFilterArgs& InArgs, const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InItems, TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& OutFilteredItems) override;`
- L54 _public prototype_ `virtual void Sort(const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InItems, TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& OutSortedItems) override;`
- L56 _public prototype_ `virtual FDelegateHandle RegisterOnHoveredItemSet(const FOnHoveredItemSetDelegate& Delegate) override;`
- L57 _public prototype_ `virtual void UnregisterOnHoveredItemSet(FDelegateHandle DelegateHandle) override;`
- L58 _public prototype_ `virtual FDelegateHandle RegisterOnHoveredItemCleared(const FOnHoveredItemClearedDelegate& Delegate) override;`
- L59 _public prototype_ `virtual void UnregisterOnHoveredItemCleared(FDelegateHandle DelegateHandle) override;`
- L61 _public function_ `virtual void FillContextMenu(FMenuBuilder& MenuBuilder) override`
- L62 _public function_ `virtual void BindPinnableCommands(FUICommandList_Pinnable& CommandList) override`
- L63 _public function_ `virtual bool ShowAddNewButton() const override`
- L64 _public function_ `virtual void FillAddNewMenu(FMenuBuilder& MenuBuilder) override`
- L65 _public function_ `virtual bool ShowFilterOptionsButton() const override`
- L66 _public function_ `virtual void FillFilterOptionsMenu(FMenuBuilder& MenuBuilder) override`
- L67 _public function_ `virtual bool ShowViewOptionsButton() const override`
- L68 _public function_ `virtual void FillViewOptionsMenu(FMenuBuilder& MenuBuilder) override`
- L69 _public function_ `virtual FText GetCornerText() const override`
- L73 _protected prototype_ `virtual void OnConfigReloaded();`
- L74 _protected prototype_ `virtual void OnObjectSelected();`
- L76 _protected prototype_ `virtual EDisplayClusterConfiguratorTreeFilterResult FilterItem(const TSharedPtr<IDisplayClusterConfiguratorTreeItem>& InItem, const FDisplayClusterConfiguratorTreeFilterArgs& InArgs, TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& OutFilteredItems);`
- L79 _protected prototype_ `virtual void SortItem(const TSharedPtr<IDisplayClusterConfiguratorTreeItem>& InItem);` — Applies the current sort configuration to the specified item, sorting the item's children as necessary
- L82 _protected prototype_ `virtual EColumnSortMode::Type GetSortMode(const FName InColumnId) const;` — Gets the current sort mode for the specified column
- L85 _protected prototype_ `virtual void OnSort(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);` — Raised when a column in the tree view is sorted
- L88 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L91 _protected member_ `TSharedPtr<FDisplayClusterConfiguratorTreeBuilder> TreeBuilder;` — The builder we use to construct the tree
- L93 _protected member_ `TWeakPtr<IDisplayClusterConfiguratorTreeItem> HoveredTreeItemPtr;`
- L95 _protected member_ `FOnHoveredItemSet OnHoveredItemSet;`
- L97 _protected member_ `FOnHoveredItemCleared OnHoveredItemCleared;`
- L99 _protected member_ `TSharedPtr<SDisplayClusterConfiguratorViewTree> ViewTree;`
- L101 _protected member_ `bool bEnabled;`
- L104 _protected member_ `FName SortedColumn;` — The name of the column in the tree view that is currently being sorted
- L107 _protected member_ `EColumnSortMode::Type SortMode;` — The current sort mode of the column being sorted in the tree view

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/SDisplayClusterConfiguratorTreeItemRow.h` (Private)


#### class `SDisplayClusterConfiguratorTreeItemRow`  
`class SDisplayClusterConfiguratorTreeItemRow : public SMultiColumnTableRow<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>`  
_L18-68_
- inherits: `SMultiColumnTableRow<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorTreeItemRow)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IDisplayClusterConfiguratorTreeItem>, Item) SLATE_ATTRIBUTE(FText, FilterText);` — The item for this row
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L35 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L39 _public prototype_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;`
- L43 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L44 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L48 _private prototype_ `bool ShouldAppearHovered() const;`
- L50 _private prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L52 _private prototype_ `void HandleDragEnter(const FDragDropEvent& DragDropEvent);`
- L54 _private prototype_ `void HandleDragLeave(const FDragDropEvent& DragDropEvent);`
- L56 _private prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem);`
- L58 _private prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem);`
- L60 _private prototype_ `virtual FReply HandleDrop(FDragDropEvent const& DragDropEvent);`
- L64 _private member_ `TWeakPtr<IDisplayClusterConfiguratorTreeItem> Item;` — The item this row is holding
- L67 _private member_ `TAttribute<FText> FilterText;` — Text the user typed into the search box - used for text highlighting

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/TreeViews/SDisplayClusterConfiguratorViewTree.h` (Private)


#### class `SDisplayClusterConfiguratorViewTree`  
`class SDisplayClusterConfiguratorViewTree : public SDisplayClusterConfiguratorViewBase , public FEditorUndoClient`  
_L33-209_
- inherits: `SDisplayClusterConfiguratorViewBase,FEditorUndoClient`
- L40 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorViewTree)`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDisplayClusterConfiguratorBlueprintEditor>& InToolkit, const TSharedRef<IDisplayClusterConfiguratorTreeBuilder>& InBuilder, const TSharedRef<IDisplayClusterConfiguratorViewTree>& ViewTreePtr, const FDisplayClusterConfiguratorTreeArgs& InTreeArgs = FDisplayClusterConfiguratorTreeArgs());`
- L54 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L58 _public function_ `virtual void PostUndo(bool bSuccess) override`
- L59 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L63 _public prototype_ `virtual void Refresh();`
- L66 _public prototype_ `virtual void CreateTreeColumns();` — Creates the tree control and then populates
- L69 _public prototype_ `void RebuildTree();` — Function to build the Config tree widgets from the source config object
- L72 _public prototype_ `virtual void ApplySortAndFilter();` — Apply sorting and filtering to the tree
- L75 _public prototype_ `virtual void SetInitialExpansionState();` — Set the initial expansion state of the tree items
- L78 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> GetSelectedItems() const;` — @return A list of all selected items in the tree view
- L83 _public prototype_ `virtual void SetSelectedItems(const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InTreeItems);` — Sets the currently selected items in the tree view @param InTreeItems - The items to select
- L86 _public prototype_ `virtual void ClearSelection();` — Clears the current selection in the tree view
- L89 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> GetAllItemsFlattened() const;` — @return A list of all items in the tree view, flattened out into a single array
- L93 _protected prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(TSharedPtr<IDisplayClusterConfiguratorTreeItem> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info
- L96 _protected prototype_ `virtual void GetFilteredChildren(TSharedPtr<IDisplayClusterConfiguratorTreeItem> InInfo, TArray< TSharedPtr<IDisplayClusterConfiguratorTreeItem> >& OutChildren);` — Get all children for a given entry in the list
- L99 _protected prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu();` — Called to display context menu when right clicking on the widget
- L102 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDisplayClusterConfiguratorTreeItem> Selection, ESelectInfo::Type SelectInfo);` — Callback function to be called when selection changes in the tree view widget.
- L105 _protected function_ `virtual void OnItemScrolledIntoView(TSharedPtr<IDisplayClusterConfiguratorTreeItem> InItem, const TSharedPtr<ITableRow>& InWidget)` — Callback when an item is scrolled into view, handling calls to rename items
- L108 _protected prototype_ `virtual void OnTreeDoubleClick(TSharedPtr<IDisplayClusterConfiguratorTreeItem> InItem);` — Callback for when the user double-clicks on an item in the tree
- L111 _protected prototype_ `virtual void SetTreeItemExpansionRecursive(TSharedPtr<IDisplayClusterConfiguratorTreeItem> TreeItem, bool bInExpansionState) const;` — Handle recursive expansion/contraction of the tree
- L114 _protected prototype_ `virtual void BindCommands();` — Binds the commands in FDisplayClusterConfiguratorViewTreeCommands to functions in this class
- L117 _protected function_ `virtual void HandlePackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent)` — Handle package reloading
- L120 _protected prototype_ `virtual void OnFilterTextChanged(const FText& SearchText);` — Filters the SListView when the user changes the search text box (NameFilterBox)
- L122 _protected prototype_ `virtual void OnConfigReloaded();`
- L126 _protected prototype_ `virtual EVisibility GetAddNewComboButtonVisibility() const;` — @return The visibility of the "Add New" combo button
- L132 _protected prototype_ `virtual TSharedRef<SWidget> CreateAddNewMenuContent();` — Raised when creating the "Add New" combo button menu @return The widget to show in the menu
- L135 _protected prototype_ `virtual EVisibility GetFilterOptionsComboButtonVisibility() const;` — @return The visibility of the filter options combo button
- L141 _protected prototype_ `virtual TSharedRef<SWidget> CreateFilterMenuContent();` — Raised when creating the filter options combo button menu @return The widget to show in the menu
- L144 _protected prototype_ `virtual FText GetFilterMenuTooltip() const;` — @return The current text for the filter button tooltip
- L147 _protected prototype_ `virtual EVisibility GetViewOptionsComboButtonVisibility() const;` — @return The visibility of the "View Options" combo button
- L153 _protected prototype_ `virtual TSharedRef<SWidget> CreateViewOptionsMenuContent();` — Raised when creating the "View Options" combo button menu @return The widget to show in the menu
- L158 _protected prototype_ `virtual FText GetCornerText() const;` — @return The watermark text to display in the bottom right corner
- L162 _protected member_ `FText FilterText;` — Current text typed into NameFilterBox
- L165 _protected member_ `TSharedPtr<SOverlay> TreeHolder;` — Widget user to hold the item tree
- L168 _protected member_ `TSharedPtr<STreeView<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>> ConfigTreeView;` — Widget used to display the items hierarchy
- L171 _protected member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> Items;` — A tree of unfiltered items
- L174 _protected member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> LinearItems;` — A "mirror" of the tree as a flat array for easier searching
- L177 _protected member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> FilteredItems;` — Filtered view of the items tree. This is what is actually used in the tree widget
- L180 _protected member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilterPtr;` — Compiled filter search terms.
- L183 _protected member_ `EDisplayClusterConfiguratorTreeMode Mode;` — The mode that this item tree is in
- L186 _protected member_ `TSharedPtr<SComboButton> FilterComboButton;` — Hold onto the filter combo button to set its foreground color
- L189 _protected member_ `TSharedPtr<SSearchBox> NameFilterBox;` — SSearchBox to filter the tree
- L192 _protected member_ `TSharedPtr<FExtender> Extenders;` — Extenders for menus
- L195 _protected member_ `TSharedPtr<FUICommandList_Pinnable> UICommandList;` — Commands that are bound to delegates
- L198 _protected member_ `TSharedPtr<IPinnedCommandList> PinnedCommands;` — Pinned commands panel
- L201 _protected member_ `FName ContextName;` — Context name used to persist settings
- L204 _protected member_ `TWeakPtr<IDisplayClusterConfiguratorTreeBuilder> BuilderPtr;` — The builder we use to construct the tree
- L206 _protected member_ `TWeakPtr<FDisplayClusterConfiguratorBlueprintEditor> ToolkitPtr;`
- L208 _protected member_ `TWeakPtr<IDisplayClusterConfiguratorViewTree> ViewTreePtr;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Viewport/DisplayClusterConfiguratorSCSEditorViewport.h` (Private)


#### class `SDisplayClusterConfiguratorSCSEditorViewport`  
`class SDisplayClusterConfiguratorSCSEditorViewport : public SAssetEditorViewport`  
_L11-74_
- inherits: `SAssetEditorViewport`
- L13 _private function_ `SLATE_BEGIN_ARGS(SDisplayClusterConfiguratorSCSEditorViewport)`
- L14 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<FBlueprintEditor>, BlueprintEditor) SLATE_ARGUMENT(TSharedPtr<SDockTab>, OwningTab) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);`
- L20 _private prototype_ `~SDisplayClusterConfiguratorSCSEditorViewport();`
- L25 _private prototype_ `void Invalidate();` — Invalidates the viewport client
- L33 _private prototype_ `void RequestRefresh(bool bResetCamera = false, bool bRefreshNow = false);` — Request a refresh of the preview scene/world. Will recreate actors as needed. @param bResetCamera If true, the camera will be reset to its default position based on the preview. @param bRefreshNow If true, the preview will be refreshed immediately. Otherwise, it will be deferred until the next tick (default behavior).
- L38 _private prototype_ `void OnComponentSelectionChanged();` — Called when the selected component changes in the SCS editor.
- L40 _private prototype_ `void SetOwnerTab(TSharedRef<SDockTab> Tab);`
- L41 _private prototype_ `TSharedPtr<SDockTab> GetOwnerTab() const;`
- L42 _private function_ `TSharedPtr<FDisplayClusterConfiguratorSCSEditorViewportClient> GetDisplayClusterViewportClient() const`
- L46 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L47 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L48 _protected prototype_ `virtual void BindCommands() override;`
- L49 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L50 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L51 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L57 _protected prototype_ `virtual void OnFocusViewportToSelection() override;` — Focuses the viewport on the currently selected components
- L61 _private prototype_ `EActiveTimerReturnType DeferredUpdatePreview(double InCurrentTime, float InDeltaTime, bool bResetCamera);` — One-off active timer to update the preview
- L64 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;`
- L65 _private member_ `TSharedPtr<FDisplayClusterConfiguratorSCSEditorViewportClient> ViewportClient;`
- L68 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer (for updating the preview) is registered
- L71 _private member_ `TWeakPtr<SDockTab> OwnerTab;` — The owner dock tab for this viewport.
- L73 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Viewport/DisplayClusterConfiguratorSCSEditorViewportClient.h` (Private)


#### class `FDisplayClusterConfiguratorSCSEditorViewportClient`  
`class FDisplayClusterConfiguratorSCSEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FDisplayClusterConfiguratorSCSEditorViewportClient>`  
_L16-254_
- inherits: `FEditorViewportClient,TSharedFromThis<FDisplayClusterConfiguratorSCSEditorViewportClient>`
- L25 _public prototype_ `FDisplayClusterConfiguratorSCSEditorViewportClient(TWeakPtr<class FBlueprintEditor>& InBlueprintEditorPtr, FPreviewScene* InPreviewScene, const TSharedRef<SDisplayClusterConfiguratorSCSEditorViewport>& InSCSEditorViewport);` — Constructor. @param InBlueprintEditorPtr A weak reference to the Blueprint Editor context. @param InPreviewScene The preview scene to use.
- L31 _public prototype_ `virtual ~FDisplayClusterConfiguratorSCSEditorViewportClient();` — Destructor.
- L34 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FEditorViewportClient interface
- L35 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L36 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L37 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L38 _public prototype_ `virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L39 _public prototype_ `virtual bool InputWidgetDelta(FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override;`
- L40 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L41 _public prototype_ `virtual void TrackingStopped() override;`
- L42 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L43 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L44 _public prototype_ `virtual bool OnTransformCanceled(const FGizmoState& InState) override;`
- L45 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L46 _public prototype_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override;`
- L47 _public prototype_ `virtual void SetWidgetCoordSystemSpace(ECoordSystem NewCoordSystem) override;`
- L48 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L49 _public prototype_ `virtual FMatrix GetWidgetCoordSystem() const override;`
- L50 _public function_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override`
- L51 _public prototype_ `virtual const FEditorViewportCameraSpeedSettings& GetCameraSpeedSettings() const override;`
- L52 _public prototype_ `virtual void SetCameraSpeedSettings(const FEditorViewportCameraSpeedSettings& InCameraSpeedSettings) override;`
- L58 _public prototype_ `HHitProxy* GetHitProxyWithoutGizmos(int32 X, int32 Y);` — Gets the hit proxy at the specified viewport coordinates when viewport gizmos such as the axis widget are filtered out.
- L65 _public prototype_ `void InvalidatePreview(bool bResetCamera = true);` — Recreates the preview scene and invalidates the owning viewport. @param bResetCamera Whether or not to reset the camera after recreating the preview scene.
- L70 _public prototype_ `void SyncEditorSettings();` — Syncs local properties to editor settings.
- L77 _public prototype_ `void SetCameraToComponent(USceneComponent* InComponent);` — Sets the local scene camera to the exact component location & rotation. @param InComponent The component with the transform to match the view to.
- L82 _public prototype_ `void ResetCamera();` — Resets the camera position
- L89 _public function_ `bool GetRealtimePreview() const` — Determines whether or not realtime preview is enabled. @return true if realtime preview is enabled, false otherwise.
- L97 _public prototype_ `void ToggleRealtimePreview();` — Toggles realtime preview on/off.
- L102 _public prototype_ `void FocusViewportToSelection();` — Focuses the viewport on the selected components
- L107 _public prototype_ `bool GetShowFloor() const;` — Returns true if the floor is currently visible in the viewport
- L112 _public prototype_ `void ToggleShowFloor();` — Will toggle the floor's visibility in the viewport
- L117 _public prototype_ `bool GetShowGrid();` — Returns true if the grid is currently visible in the viewport
- L122 _public prototype_ `void ToggleShowGrid();` — Will toggle the grid's visibility in the viewport
- L127 _public prototype_ `void SyncShowGrid();` — Syncs the local grid option with our global grid setting.
- L132 _public prototype_ `void ToggleShowOrigin();` — Shows the world origin location.
- L137 _public prototype_ `bool GetShowOrigin() const;` — Returns true if the world origin is shown.
- L142 _public prototype_ `bool GetEnableAA() const;` — Returns true if AA enabled.
- L147 _public prototype_ `void ToggleEnableAA();` — Enables or disables AA.
- L152 _public prototype_ `void ToggleShowPreview();` — Shows the preview components.
- L157 _public prototype_ `bool GetShowPreview() const;` — Returns true if preview components are visible.
- L162 _public prototype_ `void SyncShowPreview();` — Syncs local preview with global preview setting.
- L167 _public prototype_ `bool GetShowViewportNames() const;` — Display viewport names under preview components.
- L172 _public prototype_ `void ToggleShowViewportNames();` — Toggle whether to display viewport names or not.
- L177 _public prototype_ `bool CanToggleViewportNames() const;` — Requires previews enabled.
- L180 _public prototype_ `TOptional<float> GetPreviewResolutionScale() const;` — @return The current preview scale.
- L183 _public prototype_ `void SetPreviewResolutionScale(float InScale);` — Sets the preview scale.
- L186 _public prototype_ `TOptional<float> GetXformGizmoScale() const;` — @return The current xform gizmo scale.
- L189 _public prototype_ `void SetXformGizmoScale(float InScale);` — Sets the current xform gizmo scale.
- L192 _public prototype_ `bool IsShowingXformGizmos() const;` — @return Whether xform gizmos are being shown
- L195 _public prototype_ `void ToggleShowXformGizmos();` — Toggle whether to display xform gizmos or not.
- L200 _public prototype_ `AActor* GetPreviewActor() const;` — Gets the current preview actor instance.
- L206 _protected prototype_ `void BeginTransaction(const FText& Description);` — Initiates a transaction.
- L211 _protected prototype_ `void EndTransaction();` — Ends the current transaction, if one exists.
- L216 _protected prototype_ `void RefreshPreviewBounds();` — Updates preview bounds and floor positioning
- L221 _protected prototype_ `void DisplayViewportInformation(FSceneView& SceneView, FCanvas& Canvas);` — Displays relevant viewport information.
- L224 _protected member_ `UE::Widget::EWidgetMode WidgetMode;`
- L225 _protected member_ `ECoordSystem WidgetCoordSystem;`
- L228 _protected member_ `TWeakPtr<class FDisplayClusterConfiguratorBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the editor hosting the viewport
- L231 _protected member_ `FBoxSphereBounds PreviewActorBounds;` — The full bounds of the preview scene (encompasses all visible components)
- L234 _protected member_ `bool bIsManipulating;` — If true then we are manipulating a specific property or component
- L237 _protected member_ `FScopedTransaction* ScopedTransaction;` — The current transaction for undo/redo
- L240 _protected member_ `UStaticMeshComponent* EditorFloorComp;` — Floor static mesh component
- L243 _protected member_ `UDisplayClusterWorldOriginComponent* WorldOriginComponent;` — World origin static mesh component
- L246 _protected member_ `bool bIsSimulateEnabled;` — If true, the physics simulation gets ticked
- L248 _protected member_ `UStaticMeshComponent* SkyComponent;`
- L249 _protected member_ `UMaterialInstanceConstant* InstancedSkyMaterial;`
- L250 _protected member_ `UPostProcessComponent* PostProcessComponent;`
- L251 _protected member_ `UAssetViewerSettings* DefaultSettings;`
- L253 _protected member_ `int32 CurrentProfileIndex;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Views/Viewport/DisplayClusterWorldOriginComponent.h` (Private)


#### class `UDisplayClusterWorldOriginComponent`  
`class UDisplayClusterWorldOriginComponent : public UStaticMeshComponent`  
_L14-21_
- reflection: `UCLASS(ClassGroup = (DisplayCluster))`
- inherits: `UStaticMeshComponent`
- desc: Display cluster world origin component (for in-Editor visualization)
- L20 _public prototype_ `UDisplayClusterWorldOriginComponent();`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/ClusterConfiguration/DisplayClusterConfiguratorClusterUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DisplayClusterConfiguratorClusterUtils` (scope `UE`)
- L22 _prototype_ `UDisplayClusterConfigurationClusterNode* AddClusterNodeToCluster(UDisplayClusterConfigurationClusterNode* ClusterNode, UDisplayClusterConfigurationCluster* Cluster, FString NewClusterNodeName = "");` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Adds a cluster node to a cluster, removing it from its current cluster if it belongs to one. @param ClusterNode - The cluster node to add @param Cluster - The cluster to add the cluster node to @param NewClusterNodeName - Optional name to add the new cluster node under in the cluster. If not supplied, the cluster node's current name is used, if possible. @return An updated pointer to the cluster node added to the cluster.
- L29 _prototype_ `bool RemoveClusterNodeFromCluster(UDisplayClusterConfigurationClusterNode* ClusterNode);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Removes a cluster node from the cluster that owns it. The owning cluster is retrieved using the cluster node's Outer. @param ClusterNode - The cluster node to remove @returns true if the cluster node was successfully removed from its owning cluster
- L37 _prototype_ `bool RenameClusterNode(UDisplayClusterConfigurationClusterNode* ClusterNode, FString NewClusterNodeName);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Renames a cluster node, which involves changing the key that the cluster node is stored under in its parent cluster. @param ClusterNode - The cluster node to rename @param NewClusterNodeName - The desired name to change to. The final name will be a unique-ified version of this name. @return true if the cluster node was successfully renamed
- L44 _prototype_ `bool SetClusterNodeAsPrimary(UDisplayClusterConfigurationClusterNode* ClusterNode);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Sets the cluster node as the primary node. @param ClusterNode - The cluster node to set as the primary node @return true if the cluster node was successfully set as the primary node
- L51 _prototype_ `bool IsClusterNodePrimary(UDisplayClusterConfigurationClusterNode* ClusterNode);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Determines if a cluster node is the primary node in its cluster. @param ClusterNode - The cluster node to check. @return true if the node is the primary; otherwise, false.
- L60 _prototype_ `UDisplayClusterConfigurationViewport* AddViewportToClusterNode(UDisplayClusterConfigurationViewport* Viewport, UDisplayClusterConfigurationClusterNode* ClusterNode, FString NewViewportName = "");` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Adds a viewport to a cluster node, removing it from its current cluster node if it belongs to one. @param Viewport - The viewport to add @param ClusterNode - The cluster node to add the viewport to @param NewViewportName - Optional name to add the new viewport under in the cluster node. If not supplied, the viewport's current name is used, if possible. @return An updated pointer to the viewport added to the cluster.
- L67 _prototype_ `bool RemoveViewportFromClusterNode(UDisplayClusterConfigurationViewport* Viewport);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Removes a viewport from the cluster node that owns it. The owning cluster node is retrieved using the viewport's Outer. @param Viewport - The viewport to remove @returns true if the viewport was successfully removed from its owning cluster
- L75 _prototype_ `bool RenameViewport(UDisplayClusterConfigurationViewport* Viewport, FString NewViewportName);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Renames a viewport, which involves changing the key that the viewport is stored under in its parent cluster node. @param Viewport - The viewport to rename @param NewViewportName - The desired name to change to. The final name will be a unique-ified version of this name. @return true if the viewport was successfully renamed
- L83 _prototype_ `UDisplayClusterConfigurationHostDisplayData* FindOrCreateHostDisplayData(UDisplayClusterConfigurationCluster* Cluster, FString HostIPAddress);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Attempts to find a preexisting display data object for the specified host, and if one can't be found, creates a new one. @param Cluster - The cluster to find the host display data object in @param HostIPAddress - The IP address of the host to find the display data for @return The display data that was found or created
- L90 _prototype_ `bool RemoveUnusedHostDisplayData(UDisplayClusterConfigurationCluster* Cluster);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Removes all host display data objects from the cluster that aren't being used by any of the cluster nodes. @param Cluster - The cluster to clean up the host display data for @return true if any host display data was removed; otherwise, false
- L99 _prototype_ `FString GetUniqueNameForHost(FString InitialName, UDisplayClusterConfigurationCluster* ParentCluster, bool bAddZero = false);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Gets a unique name for a host owned by the specified cluster. @param InitialName - The initial name the host wants @param ParentCluster - The cluster the host belongs to @param bAddZero - Whether to add an "_0" to the initial name if it is unique @returns A unique name for the host
- L106 _prototype_ `FString GetAddressForHost(UDisplayClusterConfigurationHostDisplayData* HostDisplayData);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Gets the address of a host using its host display data. @param HostDisplayData - The display data of the host to get the address for @return The address of the host, or an empty string if no host address was found
- L114 _prototype_ `bool RemoveHost(UDisplayClusterConfigurationCluster* Cluster, FString Host);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Removes all cluster nodes and host display data from the cluster for the specified host. @param Cluster - The cluster to remove the host from. @param Host - The host to remove. @return true if any cluster nodes or host display data was removed; otherwise, false
- L121 _prototype_ `UDisplayClusterConfigurationHostDisplayData* GetHostDisplayDataForClusterNode(UDisplayClusterConfigurationClusterNode* ClusterNode);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Attempts to get the host display data for the host of a cluster node. @param ClusterNode - The cluster node whose host to get the display data for. @return The display data for the cluster node's host, or null if no display data was found.
- L127 _prototype_ `FString GetClusterNodeName(UDisplayClusterConfigurationClusterNode* ClusterNode);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Gets the name that the cluster node is stored under in its parent cluster. @return The cluster node's storage name
- L136 _prototype_ `FString GetUniqueNameForClusterNode(FString InitialName, UDisplayClusterConfigurationCluster* ParentCluster, bool bAddZero = false);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Gets a unique name for a cluster node owned by the specified cluster. @param InitialName - The initial name the cluster node wants @param ParentCluster - The cluster the cluster node belongs to @param bAddZero - Whether to add an "_0" to the initial name if it is unique @returns A unique name for the cluster node
- L142 _prototype_ `FString GetViewportName(UDisplayClusterConfigurationViewport* Viewport);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Gets the name that the viewport is stored under in its parent cluster node. @return The viewport's storage name
- L151 _prototype_ `FString GetUniqueNameForViewport(FString InitialName, UDisplayClusterConfigurationClusterNode* ParentClusterNode, bool bAddZero = false);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Gets a unique name for a viewport owned by the specified cluster node. @param InitialName - The initial name the viewport wants @param ParentClusterNode - The cluster node the viewport belongs to @param bAddZero - Whether to add an "_0" to the initial name if it is unique @returns A unique name for the viewport
- L158 _prototype_ `void SortClusterNodesByHost(const TMap<FString, UDisplayClusterConfigurationClusterNode*>& InClusterNodes, TMap<FString, TMap<FString, UDisplayClusterConfigurationClusterNode*>>& OutSortedNodes);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Sorts a list of cluster nodes by their host. @param InClusterNodes - The list of nodes to sort @param OutSortedNodes - The sorted nodes, indexed by the Host property of the cluster nodes
- L165 _prototype_ `void SortClusterNodesByHost(const TMap<FString, TObjectPtr<UDisplayClusterConfigurationClusterNode>>& InClusterNodes, TMap<FString, TMap<FString, UDisplayClusterConfigurationClusterNode*>>& OutSortedNodes);` (scope `UE::DisplayClusterConfiguratorClusterUtils`) — Sorts a list of cluster nodes by their host. @param InClusterNodes - The list of nodes to sort @param OutSortedNodes - The sorted nodes, indexed by the Host property of the cluster nodes

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/DisplayClusterConfiguratorFactory.h` (Public)


#### class `UDisplayClusterConfiguratorFactory`  
`class UDisplayClusterConfiguratorFactory : public UFactory`  
_L15-56_
- reflection: `UCLASS(MinimalApi)`
- inherits: `UFactory`
- L21 _public prototype_ `UDisplayClusterConfiguratorFactory();`
- L22 _public prototype_ `~UDisplayClusterConfiguratorFactory();`
- L25 _public prototype_ `virtual bool ConfigureProperties() override;`
- L26 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L28 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L30 _public prototype_ `virtual bool DoesSupportClass(UClass* Class) override;`
- L31 _public prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L32 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& InFilename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L33 _public function_ `virtual bool FactoryCanImport(const FString& Filename) override`
- L34 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L35 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L39 _public prototype_ `static void SetupNewBlueprint(UDisplayClusterBlueprint* NewBlueprint);` — Create initial config data and components.
- L42 _public prototype_ `static void SetupInitialBlueprintDocuments(UDisplayClusterBlueprint* NewBlueprint);` — Perform one time setup of open documents.
- L44 _private prototype_ `void OnConfigureNewAssetRequest(UFactory* InFactory);`
- L49 _private member_ `TSubclassOf<class ADisplayClusterRootActor> ParentClass;` — `UPROPERTY()` — The parent class of the created blueprint
- L52 _private member_ `TObjectPtr<UDisplayClusterBlueprint> BlueprintToCopy;` — `UPROPERTY(Transient)`
- L54 _private member_ `FDelegateHandle OnConfigureNewAssetRequestHandle;`
- L55 _private member_ `bool bIsConfigureNewAssetRequest;`

#### class `UDisplayClusterConfiguratorReimportFactory`  
`class UDisplayClusterConfiguratorReimportFactory : public UDisplayClusterConfiguratorFactory , public FReimportHandler`  
_L59-73_
- reflection: `UCLASS(MinimalApi)`
- inherits: `UDisplayClusterConfiguratorFactory,FReimportHandler`
- L65 _private prototype_ `UDisplayClusterConfiguratorReimportFactory();`
- L68 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L69 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L70 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L71 _private prototype_ `virtual int32 GetPriority() const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/IDisplayClusterConfigurator.h` (Public)


#### class `IDisplayClusterConfigurator`  
`class IDisplayClusterConfigurator : public IModuleInterface`  
_L17-52_
- inherits: `IModuleInterface`
- desc: Configurator editor module
- L21 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L24 _public prototype_ `virtual ~IDisplayClusterConfigurator() = default;`
- L33 _public function_ `static inline IDisplayClusterConfigurator& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L43 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L49 _public prototype_ `virtual const FDisplayClusterConfiguratorCommands& GetCommands() const = 0;`
- L50 _public prototype_ `virtual TSharedPtr<class FExtensibilityManager> GetMenuExtensibilityManager() const = 0;`
- L51 _public prototype_ `virtual TSharedPtr<class FExtensibilityManager> GetToolBarExtensibilityManager() const = 0;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisplayClusterConfiguratorReadOnlyChanged, bool );` — Read only delegate
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisplayClusterConfiguratorReadOnlyChanged, bool );` — Read only delegate
- L12 _typedef_ `using FOnDisplayClusterConfiguratorReadOnlyChangedDelegate = FOnDisplayClusterConfiguratorReadOnlyChanged::FDelegate;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/IDisplayClusterConfiguratorBlueprintEditor.h` (Public)


#### class `IDisplayClusterConfiguratorBlueprintEditor`  
`class IDisplayClusterConfiguratorBlueprintEditor : public FBlueprintEditor`  
_L11-34_
- inherits: `FBlueprintEditor`
- desc: TODO: Remove this completely, don't expose the BP Editor outside of the configuration module.
- L15 _public prototype_ `virtual ~IDisplayClusterConfiguratorBlueprintEditor() = default;`
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnConfigReloaded);`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnObjectSelected);`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInvalidateViews);`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnClearViewportSelection);`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnClusterChanged);`
- L24 _public typedef_ `using FOnConfigReloadedDelegate = FOnConfigReloaded::FDelegate;`
- L25 _public typedef_ `using FOnObjectSelectedDelegate = FOnObjectSelected::FDelegate;`
- L26 _public typedef_ `using FOnInvalidateViewsDelegate = FOnInvalidateViews::FDelegate;`
- L27 _public typedef_ `using FOnClearViewportSelectionDelegate = FOnClearViewportSelection::FDelegate;`
- L28 _public typedef_ `using FOnClusterChangedDelegate = FOnClusterChanged::FDelegate;`
- L31 _public prototype_ `virtual TArray<UObject*> GetSelectedObjects() const = 0;`
- L33 _public prototype_ `virtual bool IsObjectSelected(UObject* Obj) const = 0;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnConfigReloaded);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnObjectSelected);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInvalidateViews);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnClearViewportSelection);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnClusterChanged);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/Details/IDisplayClusterConfiguratorViewDetails.h` (Public)


#### class `IDisplayClusterConfiguratorViewDetails`  
`class IDisplayClusterConfiguratorViewDetails : public IDisplayClusterConfiguratorView`  
_L8-13_
- inherits: `IDisplayClusterConfiguratorView`
- L12 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewDetails() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/IDisplayClusterConfiguratorBuilder.h` (Public)


#### class `IDisplayClusterConfiguratorBuilder`  
`class IDisplayClusterConfiguratorBuilder : public TSharedFromThis<IDisplayClusterConfiguratorBuilder>`  
_L7-12_
- inherits: `TSharedFromThis<IDisplayClusterConfiguratorBuilder>`
- L11 _public prototype_ `virtual ~IDisplayClusterConfiguratorBuilder() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/IDisplayClusterConfiguratorItem.h` (Public)


#### class `IDisplayClusterConfiguratorItem`  
`class IDisplayClusterConfiguratorItem : public TSharedFromThis<IDisplayClusterConfiguratorItem>`  
_L8-21_
- inherits: `TSharedFromThis<IDisplayClusterConfiguratorItem>`
- L12 _public prototype_ `virtual ~IDisplayClusterConfiguratorItem() = default;`
- L16 _public prototype_ `virtual UObject* GetObject() const = 0;` — Get the object represented by this item, if any
- L18 _public prototype_ `virtual void OnSelection() = 0;`
- L20 _public prototype_ `virtual bool IsSelected() = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/IDisplayClusterConfiguratorView.h` (Public)


#### class `IDisplayClusterConfiguratorView`  
`class IDisplayClusterConfiguratorView : public TSharedFromThis<IDisplayClusterConfiguratorView>`  
_L10-22_
- inherits: `TSharedFromThis<IDisplayClusterConfiguratorView>`
- L14 _public prototype_ `virtual ~IDisplayClusterConfiguratorView() = default;`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() = 0;`
- L18 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;`
- L20 _public function_ `virtual void SetEnabled(bool bInEnabled)`
- L21 _public function_ `virtual bool GetIsEnabled() const`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/Log/IDisplayClusterConfiguratorViewLog.h` (Public)


#### class `IDisplayClusterConfiguratorViewLog`  
`class IDisplayClusterConfiguratorViewLog : public IDisplayClusterConfiguratorView`  
_L9-29_
- inherits: `IDisplayClusterConfiguratorView`
- L13 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewLog() = default;`
- L24 _public prototype_ `virtual TSharedRef<IMessageLogListing> GetMessageLogListing() const = 0;`
- L26 _public prototype_ `virtual TSharedRef<IMessageLogListing> CreateLogListing() = 0;`
- L28 _public prototype_ `virtual void Log(const FText& Message, EVerbosityLevel Verbosity = EVerbosityLevel::Log) = 0;`

#### enum `IDisplayClusterConfiguratorViewLog::EVerbosityLevel`  
`enum class EVerbosityLevel`  
_L16-21_
- L18 _public enumerator_ `Log`
- L19 _public enumerator_ `Warning`
- L20 _public enumerator_ `Error`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/OutputMapping/IDisplayClusterConfiguratorOutputMappingBuilder.h` (Public)


#### class `IDisplayClusterConfiguratorOutputMappingBuilder`  
`class IDisplayClusterConfiguratorOutputMappingBuilder : public IDisplayClusterConfiguratorBuilder`  
_L14-33_
- inherits: `IDisplayClusterConfiguratorBuilder`
- desc: The Interface for generation of nodes from config
- L18 _public prototype_ `virtual ~IDisplayClusterConfiguratorOutputMappingBuilder() = default;`
- L28 _public prototype_ `virtual void Build() = 0;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> GetCanvasWidget() const = 0;`
- L32 _public prototype_ `virtual const TArray<TSharedPtr<IDisplayClusterConfiguratorOutputMappingSlot>>& GetAllSlots() const = 0;`

#### struct `IDisplayClusterConfiguratorOutputMappingBuilder::FSlot`  
`struct FSlot`  
_L21-26_
- L23 _public member_ `static const FName Canvas;`
- L24 _public member_ `static const FName Window;`
- L25 _public member_ `static const FName Viewport;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/OutputMapping/IDisplayClusterConfiguratorOutputMappingItem.h` (Public)


#### class `IDisplayClusterConfiguratorOutputMappingItem`  
`class IDisplayClusterConfiguratorOutputMappingItem : public IDisplayClusterConfiguratorItem`  
_L12-20_
- inherits: `IDisplayClusterConfiguratorItem`
- desc: The Interface holsd object and setting from Details View
- L16 _public prototype_ `virtual ~IDisplayClusterConfiguratorOutputMappingItem() = default;`
- L19 _public prototype_ `virtual const FString& GetNodeName() const = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/OutputMapping/IDisplayClusterConfiguratorViewOutputMapping.h` (Public)


#### struct `FOutputMappingSettings`  
`struct FOutputMappingSettings`  
_L9-34_
- L11 _public member_ `bool bShowRuler;`
- L12 _public member_ `bool bShowWindowInfo;`
- L13 _public member_ `bool bShowWindowCornerImage;`
- L14 _public member_ `bool bShowOutsideViewports;`
- L15 _public member_ `bool bAllowClusterItemOverlap;`
- L16 _public member_ `bool bKeepClusterNodesInHosts;`
- L17 _public member_ `bool bLockViewports;`
- L18 _public member_ `bool bLockClusterNodes;`
- L19 _public member_ `bool bTintSelectedViewports;`
- L20 _public member_ `float ViewScale;`
- L22 _public function_ `FOutputMappingSettings() : bShowRuler(true), bShowWindowInfo(true), bShowWindowCornerImage(true), bShowOutsideViewports(false), bAllowClusterItemOverlap(false), bKeepClusterNodesInHosts(true), bLockViewports(false), bLockClusterNodes(false), bTintSelectedViewports(true), ViewScale(1.0f)`

#### enum `EHostArrangementType`  
`enum class EHostArrangementType : uint8`  
_L36-42_
- L38 _public enumerator_ `Horizontal`
- L39 _public enumerator_ `Vertical`
- L40 _public enumerator_ `Wrap`
- L41 _public enumerator_ `Grid`

#### struct `FHostNodeArrangementSettings`  
`struct FHostNodeArrangementSettings`  
_L44-55_
- L46 _public member_ `EHostArrangementType ArrangementType;`
- L47 _public member_ `float WrapThreshold;`
- L48 _public member_ `int GridSize;`
- L50 _public function_ `FHostNodeArrangementSettings() : ArrangementType(EHostArrangementType::Wrap), WrapThreshold(5400), GridSize(4)`

#### struct `FNodeAlignmentSettings`  
`struct FNodeAlignmentSettings`  
_L57-71_
- L59 _public member_ `int32 SnapProximity;`
- L60 _public member_ `int32 AdjacentEdgesSnapPadding;`
- L62 _public member_ `bool bSnapAdjacentEdges;`
- L63 _public member_ `bool bSnapSameEdges;`
- L65 _public function_ `FNodeAlignmentSettings() : SnapProximity(25), AdjacentEdgesSnapPadding(0), bSnapAdjacentEdges(true), bSnapSameEdges(true)`

#### class `IDisplayClusterConfiguratorViewOutputMapping`  
`class IDisplayClusterConfiguratorViewOutputMapping : public IDisplayClusterConfiguratorView`  
_L76-106_
- inherits: `IDisplayClusterConfiguratorView`
- desc: The Interface for controll the Output Mapping Мiew
- L80 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewOutputMapping() = default;`
- L83 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOutputMappingBuilt);`
- L85 _public typedef_ `using FOnOutputMappingBuiltDelegate = FOnOutputMappingBuilt::FDelegate;`
- L88 _public prototype_ `virtual void Cleanup() = 0;`
- L90 _public prototype_ `virtual const FOutputMappingSettings& GetOutputMappingSettings() const = 0;`
- L91 _public prototype_ `virtual FOutputMappingSettings& GetOutputMappingSettings() = 0;`
- L93 _public prototype_ `virtual const FHostNodeArrangementSettings& GetHostArrangementSettings() const = 0;`
- L94 _public prototype_ `virtual FHostNodeArrangementSettings& GetHostArrangementSettings() = 0;`
- L96 _public prototype_ `virtual const FNodeAlignmentSettings& GetNodeAlignmentSettings() const = 0;`
- L97 _public prototype_ `virtual FNodeAlignmentSettings& GetNodeAlignmentSettings() = 0;`
- L99 _public prototype_ `virtual FOnOutputMappingBuilt& GetOnOutputMappingBuiltDelegate() = 0;`
- L100 _public prototype_ `virtual FDelegateHandle RegisterOnOutputMappingBuilt(const FOnOutputMappingBuiltDelegate& Delegate) = 0;`
- L101 _public prototype_ `virtual void UnregisterOnOutputMappingBuilt(FDelegateHandle DelegateHandle) = 0;`
- L103 _public prototype_ `virtual void FindAndSelectObjects(const TArray<UObject*>& ObjectsToSelect) = 0;`
- L105 _public prototype_ `virtual void JumpToObject(UObject* InObject) = 0;`

#### Free symbols / members of external scopes

- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOutputMappingBuilt);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/TreeViews/IDisplayClusterConfiguratorTreeBuilder.h` (Public)


#### struct `FDisplayClusterConfiguratorTreeBuilderOutput`  
`struct FDisplayClusterConfiguratorTreeBuilderOutput`  
_L12-82_
- desc: Output struct for builders to use
- L14 _public function_ `FDisplayClusterConfiguratorTreeBuilderOutput(TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InItems, TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InLinearItems) : Items(InItems) , LinearItems(InLinearItems)`
- L26 _public prototype_ `void Add(const TSharedPtr<IDisplayClusterConfiguratorTreeItem>& InItem, const FName& InParentName, TArrayView<const FName> InParentTypes, bool bAddToHead = false);` — Add an item to the output @param	InItem			The item to add @param	InParentName	The name of the item's parent @param	InParentTypes	The types of items to search. If this is empty all items will be searched. @param	bAddToHead		Whether to add the item to the start or end of the parent's children array
- L35 _public function_ `void Add(const TSharedPtr<IDisplayClusterConfiguratorTreeItem>& InItem, const FName& InParentName, std::initializer_list<FName> InParentTypes, bool bAddToHead = false)` — Add an item to the output @param	InItem			The item to add @param	InParentName	The name of the item's parent @param	InParentTypes	The types of items to search. If this is empty all items will be searched. @param	bAddToHead		Whether to add the item to the start or end of the parent's children array
- L47 _public prototype_ `void Add(const TSharedPtr<IDisplayClusterConfiguratorTreeItem>& InItem, const FName& InParentName, const FName& InParentType, bool bAddToHead = false);` — Add an item to the output @param	InItem			The item to add @param	InParentName	The name of the item's parent @param	InParentType	The type of items to search. If this is NAME_None all items will be searched. @param	bAddToHead		Whether to add the item to the start or end of the parent's children array
- L55 _public prototype_ `TSharedPtr<IDisplayClusterConfiguratorTreeItem> Find(const FName& InName, TArrayView<const FName> InTypes) const;` — Find the item with the specified name @param	InName	The item's name @param	InTypes	The types of items to search. If this is empty all items will be searched. @return the item found, or an invalid ptr if it was not found.
- L63 _public function_ `TSharedPtr<IDisplayClusterConfiguratorTreeItem> Find(const FName& InName, std::initializer_list<FName> InTypes) const` — Find the item with the specified name @param	InName	The item's name @param	InTypes	The types of items to search. If this is empty all items will be searched. @return the item found, or an invalid ptr if it was not found.
- L74 _public prototype_ `TSharedPtr<IDisplayClusterConfiguratorTreeItem> Find(const FName& InName, const FName& InType) const;` — Find the item with the specified name @param	InName	The item's name @param	InType	The type of items to search. If this is NAME_None all items will be searched. @return the item found, or an invalid ptr if it was not found.
- L78 _private member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& Items;` — The items that are built by this builder
- L81 _private member_ `TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& LinearItems;` — A linearized list of all items in OutItems (for easier searching)

#### class `IDisplayClusterConfiguratorTreeBuilder`  
`class IDisplayClusterConfiguratorTreeBuilder : public IDisplayClusterConfiguratorBuilder`  
_L87-102_
- inherits: `IDisplayClusterConfiguratorBuilder`
- desc: Interface to implement to provide custom build logic to tree views
- L91 _public prototype_ `virtual ~IDisplayClusterConfiguratorTreeBuilder() = default;`
- L95 _public prototype_ `virtual void Initialize(const TSharedRef<IDisplayClusterConfiguratorViewTree>& InConfiguratorTree) = 0;` — Setup this builder with links to the tree
- L101 _public prototype_ `virtual void Build(FDisplayClusterConfiguratorTreeBuilderOutput& Output) = 0;` — Build an array of item tree items to display in the tree. @param	Output			The items that are built by this builder

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/TreeViews/IDisplayClusterConfiguratorTreeItem.h` (Public)


#### enum `EDisplayClusterConfiguratorTreeFilterResult`  
`enum class EDisplayClusterConfiguratorTreeFilterResult : uint8`  
_L22-35_
- L25 _public enumerator_ `Hidden` — Hide the item
- L28 _public enumerator_ `ShownDescendant` — Show the item because child items were shown
- L31 _public enumerator_ `Shown` — Show the item
- L34 _public enumerator_ `ShownHighlighted` — Show the item and highlight search text

#### class `IDisplayClusterConfiguratorTreeItem`  
`class IDisplayClusterConfiguratorTreeItem : public IDisplayClusterConfiguratorItem`  
_L44-185_
- inherits: `IDisplayClusterConfiguratorItem`
- L48 _public prototype_ `virtual ~IDisplayClusterConfiguratorTreeItem() = default;`
- L51 _public prototype_ `NDISPLAY_TREE_BASE_ITEM_TYPE(IDisplayClusterConfiguratorTreeItem) virtual void Initialize() = 0;`
- L57 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, const TAttribute<FText>& InFilterText) = 0;` — Builds the table row widget to display this info
- L66 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, TSharedPtr<ITableRow> TableRow, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) = 0;` — Builds a widget for the specified column. @param ColumnName - The name of the column to build the widget for. @param TableRow - The table row the widget is being generated for. @param FilterText - The current filter being applied to the tree view. @param InIsSelected - The FIsSelected delegate for the current table row.
- L69 _public prototype_ `virtual TSharedRef< SWidget > GenerateInlineEditWidget(const TAttribute<FText>& FilterText, FIsSelected InIsSelected) = 0;` — Builds the slate widget for any inline data editing
- L72 _public prototype_ `virtual bool HasInlineEditor() const = 0;` — @return true if the item has an in-line editor widget
- L75 _public prototype_ `virtual void ToggleInlineEditorExpansion() = 0;` — Toggle the expansion state of the inline editor
- L78 _public prototype_ `virtual bool IsInlineEditorExpanded() const = 0;` — Get the expansion state of the inline editor
- L81 _public prototype_ `virtual FName GetRowItemName() const = 0;` — Get the name of the item that this row represents
- L84 _public prototype_ `virtual FString GetIconStyle() const = 0;` — Get the style for image icon
- L87 _public prototype_ `virtual FName GetAttachName() const = 0;` — Return the name used to attach to this item
- L90 _public prototype_ `virtual bool CanRenameItem() const = 0;` — @return true if this item can be renamed
- L93 _public prototype_ `virtual void RequestRename() = 0;` — Requests a rename on the the tree row item
- L96 _public prototype_ `virtual bool CanDeleteItem() const = 0;` — @return true if this item can be deleted
- L99 _public prototype_ `virtual void DeleteItem() const = 0;` — Deletes the tree row item and its backing object.
- L102 _public prototype_ `virtual bool CanDuplicateItem() const = 0;` — @return true if this item can be duplicated
- L105 _public prototype_ `virtual bool CanHideItem() const = 0;` — @return true if this item can be hidden
- L108 _public prototype_ `virtual void SetItemHidden(bool bIsHidden) = 0;` — Sets the item's visibility
- L111 _public prototype_ `virtual void GetParentObjectsRecursive(TArray<UObject*>& OutObjects) const = 0;` — Get the objects of all parents of this item
- L114 _public prototype_ `virtual void GetChildrenObjectsRecursive(TArray<UObject*>& OutObjects) const = 0;` — Get all Children object
- L117 _public prototype_ `virtual void OnItemDoubleClicked() = 0;` — Handler for when the user double clicks on this item in the tree
- L120 _public prototype_ `virtual void OnMouseEnter() = 0;` — Handler for when the user enter the mouse on this item in the tree
- L123 _public prototype_ `virtual void OnMouseLeave() = 0;` — Handler for when the user leave the mouse on this item in the tree
- L126 _public prototype_ `virtual bool IsHovered() const = 0;` — Return true if tree item is hovered
- L129 _public prototype_ `virtual bool IsRoot() const = 0;` — Return true if that is root tree item
- L132 _public prototype_ `virtual bool IsChildOfRecursive(const TSharedRef<IDisplayClusterConfiguratorTreeItem>& InParentTreeItem) const = 0;` — Return true if this item is a child of the given parent tree item
- L135 _public prototype_ `virtual FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;` — Handle a drag and drop detected event
- L138 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop enter event
- L141 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) = 0;` — Handle a drag and drop leave event
- L144 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) = 0;` — Handles the CanAcceptDrop callback for the tree item
- L147 _public prototype_ `virtual FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, TSharedPtr<IDisplayClusterConfiguratorTreeItem> TargetItem) = 0;` — Handle Accep drag and drop drop event
- L150 _public prototype_ `virtual FReply HandleDrop(FDragDropEvent const& DragDropEvent) = 0;` — Handle a drag and drop drop event
- L153 _public prototype_ `virtual TSharedPtr<IDisplayClusterConfiguratorTreeItem> GetParent() const = 0;` — Get this item's parent
- L156 _public prototype_ `virtual void SetParent(TSharedPtr<IDisplayClusterConfiguratorTreeItem> InParent) = 0;` — Set this item's parent
- L159 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& GetChildren() = 0;` — The array of children for this item
- L162 _public prototype_ `virtual const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& GetChildrenConst() const = 0;` — The const array of children for this item
- L165 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& GetFilteredChildren() = 0;` — The filtered array of children for this item
- L168 _public prototype_ `virtual TSharedRef<IDisplayClusterConfiguratorViewTree> GetConfiguratorTree() const = 0;` — The owning view tree
- L175 _public prototype_ `virtual EDisplayClusterConfiguratorTreeFilterResult ApplyFilter(const TSharedPtr<FTextFilterExpressionEvaluator>& TextFilter) = 0;` — Applies the specified text filter to the tree item and returns the results @param TextFilter - The filter to apply @return The results of applying the filter to this tree item
- L178 _public prototype_ `virtual EDisplayClusterConfiguratorTreeFilterResult GetFilterResult() const = 0;` — Get the current filter result
- L181 _public prototype_ `virtual void SetFilterResult(EDisplayClusterConfiguratorTreeFilterResult InResult) = 0;` — Set the current filter result
- L184 _public prototype_ `virtual bool IsInitiallyExpanded() const = 0;` — Get whether this item begins expanded or not

#### Free symbols / members of external scopes

- L38 _macro_ `#define NDISPLAY_TREE_BASE_ITEM_TYPE(TYPE) \`
- L187 _macro_ `#define NDISPLAY_TREE_ITEM_TYPE(TYPE, BASE) \`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/TreeViews/IDisplayClusterConfiguratorViewTree.h` (Public)


#### enum `EDisplayClusterConfiguratorTreeMode`  
`enum class EDisplayClusterConfiguratorTreeMode`  
_L19-23_
- L21 _public enumerator_ `Editor`
- L22 _public enumerator_ `Picker`

#### struct `FDisplayClusterConfiguratorTreeArgs`  
`struct FDisplayClusterConfiguratorTreeArgs`  
_L25-40_
- L27 _public function_ `FDisplayClusterConfiguratorTreeArgs() : Mode(EDisplayClusterConfiguratorTreeMode::Editor) , ContextName(TEXT("ConfiguratorTree"))`
- L33 _public member_ `TSharedPtr<IDisplayClusterConfiguratorTreeBuilder> Builder;` — Optional builder to allow for custom tree construction
- L36 _public member_ `EDisplayClusterConfiguratorTreeMode Mode;` — The mode that this items tree is in
- L39 _public member_ `FName ContextName;` — Context name used to persist settings

#### struct `FDisplayClusterConfiguratorTreeFilterArgs`  
`struct FDisplayClusterConfiguratorTreeFilterArgs`  
_L44-56_
- desc: Basic filter used when re-filtering the tree
- L46 _public function_ `FDisplayClusterConfiguratorTreeFilterArgs(TSharedPtr<FTextFilterExpressionEvaluator> InTextFilter) : TextFilter(InTextFilter) , bFlattenHierarchyOnFilter(false)`
- L52 _public member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;` — The text filter we are using, if any
- L55 _public member_ `bool bFlattenHierarchyOnFilter;` — Whether to flatten the hierarchy so filtered items appear in a linear list

#### class `IDisplayClusterConfiguratorViewTree`  
`class IDisplayClusterConfiguratorViewTree : public IDisplayClusterConfiguratorView`  
_L61-228_
- inherits: `IDisplayClusterConfiguratorView`
- desc: Base interface for editor tree view
- L65 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewTree() = default;`
- L68 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHoveredItemSet, const TSharedRef<IDisplayClusterConfiguratorTreeItem>&);`
- L69 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnHoveredItemCleared);`
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemsSelected, const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>&);`
- L71 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionCleared);`
- L73 _public typedef_ `using FOnHoveredItemSetDelegate = FOnHoveredItemSet::FDelegate;`
- L74 _public typedef_ `using FOnHoveredItemClearedDelegate = FOnHoveredItemCleared::FDelegate;`
- L75 _public typedef_ `using FOnItemsSelectedDelegate = FOnItemsSelected::FDelegate;`
- L76 _public typedef_ `using FOnSelectionClearedDelegate = FOnSelectionCleared::FDelegate;`
- L90 _public prototype_ `virtual void RebuildTree() = 0;` — Rebuild the tree from the config
- L95 _public prototype_ `virtual UDisplayClusterConfigurationData* GetEditorData() const = 0;` — @return The Editor editing UObject
- L101 _public prototype_ `virtual void ConstructColumns(TArray<SHeaderRow::FColumn::FArguments>& OutColumnArgs) = 0;` — Generates a list of columns to add to the tree view. @param OutColumnArgs - The list of column arguments to construct the columns from.
- L108 _public prototype_ `virtual void SetHoveredItem(const TSharedRef<IDisplayClusterConfiguratorTreeItem>& InTreeItem) = 0;` — Sets currently hovered tree item @param InTreeItem	 hovered tree item
- L113 _public prototype_ `virtual void ClearHoveredItem() = 0;` — Remove hovered Item from this tree
- L118 _public prototype_ `virtual TSharedPtr<IDisplayClusterConfiguratorTreeItem> GetHoveredItem() const = 0;` — @return The hovered tree item
- L125 _public prototype_ `virtual void SetSelectedItems(const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InTreeItems) = 0;` — Sets currently selected tree items @param InTreeItems - List of selected tree items
- L130 _public prototype_ `virtual void ClearSelection() = 0;` — Removes all tree items from list of selected items
- L135 _public prototype_ `virtual TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>> GetSelectedItems() const = 0;` — @return The list of currently selected tree items
- L138 _public prototype_ `virtual void GetSelectedObjects(TArray<UObject*>& OutObjects) const = 0;` — Gets the objects that are currently selected in the tree view.
- L144 _public prototype_ `virtual void FindAndSelectObjects(const TArray<UObject*>& ObjectsToSelect) = 0;` — Finds any tree items that represent the specified objects and selects them. @param ObjectsToSelect - The objects to select
- L152 _public prototype_ `virtual void Filter(const FDisplayClusterConfiguratorTreeFilterArgs& InArgs, const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InItems, TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& OutFilteredItems) = 0;` — Filters the specified list of items based on the filter arguments, and outputs the filtered list. @param InArgs - The filtering arguments @param InItems - The list of items to filter @param OutFilteredItems - The output list of items that matched the filter
- L159 _public prototype_ `virtual void Sort(const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& InItems, TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>& OutSortedItems) = 0;` — Sorts the specified list of items based on the current sort configuration and outputs the sorted list. @param InItems - The list of items to sort @param OutSortedItems - The output list of sorted items
- L164 _public prototype_ `virtual FDelegateHandle RegisterOnHoveredItemSet(const FOnHoveredItemSetDelegate& Delegate) = 0;` — Register the hovered tree item delegate
- L169 _public prototype_ `virtual void UnregisterOnHoveredItemSet(FDelegateHandle DelegateHandle) = 0;` — Remove the hovered tree item delegate
- L174 _public prototype_ `virtual FDelegateHandle RegisterOnHoveredItemCleared(const FOnHoveredItemClearedDelegate& Delegate) = 0;` — Register clear hovered tree item delegate
- L179 _public prototype_ `virtual void UnregisterOnHoveredItemCleared(FDelegateHandle DelegateHandle) = 0;` — Unregister clear hovered tree item delegate
- L186 _public prototype_ `virtual void FillContextMenu(FMenuBuilder& MenuBuilder) = 0;` — Raised when the context menu is being shown for an item in the tree view. @param MenuBuilder - The menu builder of the context menu
- L192 _public prototype_ `virtual void BindPinnableCommands(FUICommandList_Pinnable& CommandList) = 0;` — Raised on tree view creation when binding UI commands @param CommandList - The command list to bind commands to
- L197 _public prototype_ `virtual bool ShowAddNewButton() const = 0;` — @return true if the tree view should show an "Add New" button in its top bar
- L202 _public prototype_ `virtual void FillAddNewMenu(FMenuBuilder& MenuBuilder) = 0;` — Raised when the "Add New" combo button is clicked and its menu is being opened
- L207 _public prototype_ `virtual bool ShowFilterOptionsButton() const = 0;` — @return true if the tree view should show a filter options button in its top bar
- L212 _public prototype_ `virtual void FillFilterOptionsMenu(FMenuBuilder& MenuBuilder) = 0;` — Raised when the filter options combo button is clicked and its menu is being opened
- L217 _public prototype_ `virtual bool ShowViewOptionsButton() const = 0;` — @return true if the tree view should show a "View Options" button in its bottom bar
- L222 _public prototype_ `virtual void FillViewOptionsMenu(FMenuBuilder& MenuBuilder) = 0;` — Raised when the "View Options" combo button is clicked and its menu is being opened
- L227 _public prototype_ `virtual FText GetCornerText() const = 0;` — @return The watermark text to display in the bottom right corner of the tree view

#### struct `IDisplayClusterConfiguratorViewTree::Columns`  
`struct Columns`  
_L81-85_
- desc: Type of the tree item
- L83 _public member_ `static const FName Item;`
- L84 _public member_ `static const FName Group;`

#### Free symbols / members of external scopes

- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHoveredItemSet, const TSharedRef<IDisplayClusterConfiguratorTreeItem>&);`
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnHoveredItemCleared);`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemsSelected, const TArray<TSharedPtr<IDisplayClusterConfiguratorTreeItem>>&);`
- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionCleared);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/Viewport/IDisplayClusterConfiguratorPreviewScene.h` (Public)


#### class `IDisplayClusterConfiguratorPreviewScene`  
`class IDisplayClusterConfiguratorPreviewScene : public FAdvancedPreviewScene`  
_L9-19_
- inherits: `FAdvancedPreviewScene`
- L14 _public function_ `IDisplayClusterConfiguratorPreviewScene(ConstructionValues CVS) : FAdvancedPreviewScene(CVS)` — Constructor only here to pass ConstructionValues to base constructor
- L18 _public prototype_ `virtual ~IDisplayClusterConfiguratorPreviewScene() = default;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/Viewport/IDisplayClusterConfiguratorViewViewport.h` (Public)


#### class `IDisplayClusterConfiguratorViewViewport`  
`class IDisplayClusterConfiguratorViewViewport : public IDisplayClusterConfiguratorView`  
_L10-18_
- inherits: `IDisplayClusterConfiguratorView`
- L14 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewViewport() = default;`
- L17 _public prototype_ `virtual TSharedRef<IDisplayClusterConfiguratorPreviewScene> GetPreviewScene() const = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Public/Views/Viewport/IDisplayClusterConfiguratorViewportBuilder.h` (Public)


#### class `IDisplayClusterConfiguratorViewportBuilder`  
`class IDisplayClusterConfiguratorViewportBuilder : public IDisplayClusterConfiguratorBuilder`  
_L8-18_
- inherits: `IDisplayClusterConfiguratorBuilder`
- L12 _public prototype_ `virtual ~IDisplayClusterConfiguratorViewportBuilder() = default;`
- L15 _public prototype_ `virtual void BuildViewport() = 0;`
- L17 _public prototype_ `virtual void ClearViewportSelection() = 0;`
