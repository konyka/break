# Plugins / WorkspaceEditor

- module root: `Plugins/Experimental/Workspace/Source/WorkspaceEditor`
- headers: 39; symbols: 794
- symbol kinds: class=35, delegate=8, enum=2, enumerator=4, externvar=10, function=119, macro=7, member=176, namespace=68, prototype=312, struct=22, typedef=30, variable=1
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, ContentBrowser, CoreUObject, DesktopWidgets, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, GraphEditor, InputCore, InteractiveToolsFramework, Json, JsonUtilities, KismetWidgets, PropertyEditor, SceneOutliner, Settings, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets
- PublicDependencyModuleNames: Core, UnrealEd
- PublicIncludePathModuleNames: SceneOutliner

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/AssetDocumentSummoner.h` (Private)


#### struct `UE::Workspace::FAssetDocumentSummoner`  
`struct FAssetDocumentSummoner : public FDocumentTabFactory`  
_L20-64_
- inherits: `FDocumentTabFactory`
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSaveDocumentState, UObject*);` — Delegate called to save the state of a document
- L26 _public prototype_ `FAssetDocumentSummoner(FName InIdentifier, TSharedPtr<FWorkspaceEditor> InHostingApp, bool bInAllowUnsupportedClasses = false);`
- L28 _public prototype_ `void SetAllowedClassPaths(TConstArrayView<FTopLevelAssetPath> InAllowedClassPaths);`
- L32 _private prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;` — FWorkflowTabFactory interface
- L33 _private prototype_ `virtual void OnTabBackgrounded(TSharedPtr<SDockTab> Tab) const override;`
- L34 _private prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L35 _private prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L36 _private prototype_ `virtual bool IsPayloadSupported(TSharedRef<FTabPayload> Payload) const override;`
- L37 _private prototype_ `virtual TAttribute<FText> ConstructTabLabelSuffix(const FWorkflowTabSpawnInfo& Info) const override;`
- L38 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L39 _private prototype_ `virtual const FSlateBrush* GetTabIcon(const FWorkflowTabSpawnInfo& Info) const override;`
- L41 _private function_ `virtual bool IsPayloadValid(TSharedRef<FTabPayload> Payload) const override`
- L51 _private prototype_ `virtual TAttribute<FText> ConstructTabName(const FWorkflowTabSpawnInfo& Info) const override;` — Creates the label for the tab
- L54 _private member_ `TWeakPtr<FWorkspaceEditor> HostingAppPtr;` — The hosting app
- L57 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list
- L60 _private member_ `TArray<FTopLevelAssetPath> AllowedClassPaths;` — Allowed object types
- L63 _private member_ `bool bAllowUnsupportedClasses = false;` — Whether or not to allow objects if AllowedClassPaths does not contain their class

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Workspace` (scope `UE`)
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSaveDocumentState, UObject*);` — Delegate called to save the state of a document

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/DefaultWorkspaceSchema.h` (Private)


#### class `UDefaultWorkspaceSchema`  
`class UDefaultWorkspaceSchema : public UWorkspaceSchema`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UWorkspaceSchema`
- desc: Workspace schema allowing all asset types
- L15 _private function_ `virtual FText GetDisplayName() const` — UWorkspaceSchema interface
- L16 _private function_ `virtual TConstArrayView<FTopLevelAssetPath> GetSupportedAssetClassPaths() const override`
- L17 _private function_ `virtual bool SupportsMultipleAssets() const override`
- L18 _private function_ `virtual bool CanSaveWorkspace() const override`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/GraphDocumentState.h` (Private)


#### struct `FGraphDocumentState`  
`struct FGraphDocumentState : public FWorkspaceDocumentState`  
_L11-28_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceDocumentState`
- desc: Base struct used to persist workspace document state
- L15 _public prototype_ `FGraphDocumentState() = default;`
- L17 _public function_ `FGraphDocumentState(const UObject* InObject, const FWorkspaceOutlinerItemExport& InExport, const UE::Slate::FDeprecateVector2DParameter& InViewLocation, float InZoomAmount) : FWorkspaceDocumentState(InObject, InExport) , ViewLocation(InViewLocation) , ZoomAmount(InZoomAmount)`
- L24 _public member_ `FDeprecateSlateVector2D ViewLocation = FVector2f::Zero();` — `UPROPERTY()`
- L27 _public member_ `float ZoomAmount = 0.f;` — `UPROPERTY()`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/Outliner/WorkspaceOutlinerColumns.h` (Private)


#### class `UE::Workspace::FWorkspaceOutlinerFileStateColumn`  
`class FWorkspaceOutlinerFileStateColumn : public ISceneOutlinerColumn`  
_L16-33_
- inherits: `ISceneOutlinerColumn`
- L19 _public prototype_ `static FName GetID();`
- L21 _public function_ `FWorkspaceOutlinerFileStateColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L22 _public prototype_ `virtual ~FWorkspaceOutlinerFileStateColumn() override = default;`
- L25 _public function_ `virtual FName GetColumnID() override`
- L26 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L27 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L28 _public function_ `virtual bool SupportsSorting() const override`
- L32 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/Outliner/WorkspaceOutlinerHierarchy.h` (Private)


#### class `UE::Workspace::FWorkspaceOutlinerHierarchy`  
`class FWorkspaceOutlinerHierarchy : public ISceneOutlinerHierarchy`  
_L13-32_
- inherits: `ISceneOutlinerHierarchy`
- L16 _public prototype_ `FWorkspaceOutlinerHierarchy(ISceneOutlinerMode* Mode, const TWeakObjectPtr<UWorkspace>& InWorkspace);`
- L17 _public prototype_ `FWorkspaceOutlinerHierarchy(const FWorkspaceOutlinerHierarchy&) = delete;`
- L18 _public prototype_ `FWorkspaceOutlinerHierarchy& operator=(const FWorkspaceOutlinerHierarchy&) = delete;`
- L21 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L22 _public function_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override`
- L23 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L26 _protected prototype_ `void CreateItemsFromAssetData(const FAssetData& AssetData, TArray<FSceneOutlinerTreeItemPtr>& OutItems, TArray<FAssetData>& OutAssets, const FWorkspaceOutlinerItemExport* InParentExport = nullptr) const;`
- L29 _private member_ `TWeakObjectPtr<UWorkspace> WeakWorkspace;`
- L31 _private member_ `mutable TArray<FAssetData> ProcessedAssetData;` — Set of assets referenced by currently from current workspace,(includes UWorkspace::AssetEntries + any expanded asset references)

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/Outliner/WorkspaceOutlinerMode.h` (Private)


#### class `UE::Workspace::FWorkspaceOutlinerMode`  
`class FWorkspaceOutlinerMode : public ISceneOutlinerMode`  
_L13-52_
- inherits: `ISceneOutlinerMode`
- L16 _public prototype_ `FWorkspaceOutlinerMode(SSceneOutliner* InSceneOutliner, const TWeakObjectPtr<UWorkspace>& InWeakWorkspace, const TWeakPtr<IWorkspaceEditor>& InWeakWorkspaceEditor);`
- L20 _public prototype_ `virtual void Rebuild() override;`
- L21 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L22 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L23 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L24 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L25 _public function_ `virtual bool CanCustomizeToolbar() const override`
- L26 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L27 _public prototype_ `virtual bool CanDelete() const override;`
- L28 _public prototype_ `virtual bool CanRename() const override;`
- L29 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L30 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList) override;`
- L31 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L33 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L36 _protected prototype_ `void HandleItemSelection(const FSceneOutlinerItemSelection& Selection) const;`
- L37 _protected prototype_ `void OnWorkspaceModified(UWorkspace* InWorkspace) const;`
- L38 _protected prototype_ `void ResetOutlinerSelection() const;`
- L40 _protected prototype_ `void Open() const;`
- L41 _protected prototype_ `void Delete() const;`
- L42 _protected prototype_ `bool CanDeleteItem(const ISceneOutlinerTreeItem& Item) const;`
- L43 _protected prototype_ `void Rename() const;`
- L45 _protected prototype_ `void OpenItems(TArrayView<const FSceneOutlinerTreeItemPtr> Items) const;`
- L47 _protected prototype_ `void OnAssetRegistryAssetUpdate(const FAssetData& AssetData) const;`
- L49 _private member_ `TWeakObjectPtr<UWorkspace> WeakWorkspace;`
- L50 _private member_ `TWeakPtr<IWorkspaceEditor> WeakWorkspaceEditor;`
- L51 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/Outliner/WorkspaceOutlinerTreeItem.h` (Private)


#### struct `UE::Workspace::FWorkspaceOutlinerTreeItem`  
`struct FWorkspaceOutlinerTreeItem : ISceneOutlinerTreeItem`  
_L11-36_
- inherits: `ISceneOutlinerTreeItem`
- L13 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L19 _public prototype_ `FWorkspaceOutlinerTreeItem(const FItemData& InItemData);`
- L20 _public prototype_ `virtual ~FWorkspaceOutlinerTreeItem() override = default;`
- L23 _public prototype_ `virtual bool IsValid() const override;`
- L24 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L25 _public prototype_ `virtual FString GetDisplayString() const override;`
- L26 _public prototype_ `virtual FText GetToolTipText() const;`
- L27 _public function_ `virtual bool CanInteract() const override`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L29 _public prototype_ `virtual FString GetPackageName() const override;`
- L33 _public member_ `FWorkspaceOutlinerItemExport Export;` — AssetRegistry export this tree item represents in the Outliner
- L35 _public member_ `TSharedPtr<IWorkspaceOutlinerItemDetails> ItemDetails;` — Cached _optional_ details provider for the FWorkspaceOutlinerItemExport its inner data

#### struct `UE::Workspace::FWorkspaceOutlinerTreeItem::FItemData`  
`struct FItemData`  
_L14-17_
- L16 _public member_ `const FWorkspaceOutlinerItemExport& Export;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/SGraphDocument.h` (Private)


#### class `UE::Workspace::SGraphDocument`  
`class SGraphDocument : public SCompoundWidget`  
_L19-127_
- inherits: `SCompoundWidget`
- desc: Wrapper widget for a graph editor
- L21 _private function_ `SLATE_BEGIN_ARGS(SGraphDocument)`
- L23 _private prototype_ `SLATE_EVENT(FOnCreateActionMenu, OnCreateActionMenu) SLATE_EVENT(FOnNodeTextCommitted, OnNodeTextCommitted) SLATE_EVENT(FOnGraphSelectionChanged, OnGraphSelectionChanged) SLATE_EVENT(FOnCanPerformActionOnSelectedNodes, OnCanDeleteSelectedNodes) SLATE_EVENT(FOnPerformActionOnSelectedNodes, OnDeleteSelectedNodes) SLATE_EVENT(FOnCanPerformActionOnSelectedNodes, OnCanCutSelectedNodes) SLATE_EVENT(FOnPerformActionOnSelectedNodes, OnCutSelectedNodes) SLATE_EVENT(FOnCanPerformActionOnSelectedNodes, OnCanCopySelectedNodes) SLATE_EVENT(FOnPerformActionOnSelectedNodes, OnCopySelectedNodes) SLATE_EVENT(FOnCanPasteNodes, OnCanPasteNodes) SLATE_EVENT(FOnPasteNodes, OnPasteNodes) SLATE_EVENT(FOnCanPerformActionOnSelectedNodes, OnCanDuplicateSelectedNodes) SLATE_EVENT(FOnDuplicateSelectedNodes, OnDuplicateSelectedNodes) SLATE_EVENT(FSimpleDelegate, OnNavigateHistoryBack) SLATE_EVENT(FSimpleDelegate, OnNavigateHistoryForward) SLATE_EVENT(FOnNodeDoubleClicked, OnNodeDoubleClicked) SLATE_EVENT(FOnCanPerformActionOnSelectedNodes, OnCanOpenInNewTab) SLATE_EVENT(FOnPerformActionOnSelectedNodes, OnOpenInNewTab) SLATE_EVENT(FOnCreateComment, OnCreateComment) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FWorkspaceEditor> InHostingApp, const FWorkspaceDocument& InDocument);`
- L58 _private prototype_ `void BindCommands();`
- L61 _private prototype_ `bool CanDeleteSelectedNodes() const;`
- L62 _private prototype_ `void DeleteSelectedNodes();`
- L64 _private prototype_ `bool CanCutSelectedNodes() const;`
- L65 _private prototype_ `void CutSelectedNodes();`
- L67 _private prototype_ `bool CanCopySelectedNodes() const;`
- L68 _private prototype_ `void CopySelectedNodes();`
- L70 _private prototype_ `bool CanPasteNodes() const;`
- L71 _private prototype_ `void PasteNodes();`
- L73 _private prototype_ `bool CanDuplicateSelectedNodes() const;`
- L74 _private prototype_ `void DuplicateSelectedNodes();`
- L76 _private prototype_ `bool CanSelectAllNodes() const;`
- L77 _private prototype_ `void SelectAllNodes();`
- L79 _private prototype_ `bool CanOpenInNewTab() const;`
- L80 _private prototype_ `void OpenInNewTab();`
- L82 _private prototype_ `void CreateComment();`
- L84 _private prototype_ `bool IsEditable(UEdGraph* InGraph) const;`
- L85 _private prototype_ `void OnResetSelection();`
- L88 _private member_ `UEdGraph* EdGraph = nullptr;` — The graph we are editing
- L89 _private member_ `FWorkspaceDocument Document;`
- L92 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;` — The graph editor we wrap
- L95 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for graphs
- L98 _private member_ `TWeakPtr<FWorkspaceEditor> HostingAppPtr;` — The hosting app
- L101 _private member_ `FOnCanPerformActionOnSelectedNodes OnCanDeleteSelectedNodes;` — Delegate called when we delete nodes
- L102 _private member_ `FOnPerformActionOnSelectedNodes OnDeleteSelectedNodes;`
- L105 _private member_ `FOnCanPerformActionOnSelectedNodes OnCanCutSelectedNodes;` — Cut delegates
- L106 _private member_ `FOnPerformActionOnSelectedNodes OnCutSelectedNodes;`
- L109 _private member_ `FOnCanPerformActionOnSelectedNodes OnCanCopySelectedNodes;` — Copy delegates
- L110 _private member_ `FOnPerformActionOnSelectedNodes OnCopySelectedNodes;`
- L113 _private member_ `FOnCanPasteNodes OnCanPasteNodes;` — Paste delegates
- L114 _private member_ `FOnPasteNodes OnPasteNodes;`
- L117 _private member_ `FOnCanPerformActionOnSelectedNodes OnCanDuplicateSelectedNodes;` — Duplicate delegates
- L118 _private member_ `FOnDuplicateSelectedNodes OnDuplicateSelectedNodes;`
- L121 _private member_ `FOnCanPerformActionOnSelectedNodes OnCanOpenInNewTab;` — Open in new Tab delegates
- L122 _private member_ `FOnPerformActionOnSelectedNodes OnOpenInNewTab;`
- L124 _private member_ `FOnCreateComment OnCreateComment;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Workspace` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/SWorkspacePicker.h` (Private)


#### class `UE::Workspace::SWorkspacePicker`  
`class SWorkspacePicker : public SCompoundWidget, public IWorkspacePicker`  
_L15-52_
- inherits: `SCompoundWidget,IWorkspacePicker`
- L17 _private function_ `DECLARE_DELEGATE_OneParam(FOnWorkspaceSelected, TObjectPtr<UWorkspace>) SLATE_BEGIN_ARGS(SWorkspacePicker)`
- L21 _private prototype_ `SLATE_EVENT(FOnWorkspaceSelected, OnExistingWorkspaceSelected) SLATE_EVENT(FOnWorkspaceSelected, OnNewWorkspaceCreated)`
- L39 _private prototype_ `virtual void ShowModal() override;` — IWorkspacePicker
- L40 _private prototype_ `virtual TObjectPtr<UObject> GetSelectedWorkspace() const override;`
- L43 _private member_ `TArray<FAssetData> WorkspaceAssets;`
- L45 _private member_ `EHintText HintText = EHintText::SelectedAssetIsPartOfMultipleWorkspaces;`
- L47 _private member_ `TSubclassOf<UWorkspaceFactory> WorkspaceFactoryClass;`
- L49 _private member_ `TObjectPtr<UWorkspace> SelectedWorkspace;`
- L51 _private member_ `TWeakPtr<SWindow> WeakWindow;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWorkspaceSelected, TObjectPtr<UWorkspace>) SLATE_BEGIN_ARGS(SWorkspacePicker) {} SLATE_EVENT(FOnWorkspaceSelected, OnExistingWorkspaceSelected) SLATE_EVENT(FOnWorkspaceSelected, OnNewWorkspaceCreated)`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/SWorkspaceTabWrapper.h` (Private)


#### class `UWorkspaceTabMenuContext`  
`class UWorkspaceTabMenuContext : public UObject`  
_L15-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- L20 _public member_ `TWeakPtr<SWorkspaceTabWrapper> TabWrapper;`

#### class `SWorkspaceTabWrapper`  
`class SWorkspaceTabWrapper : public SCompoundWidget`  
_L23-55_
- inherits: `SCompoundWidget`
- L26 _public prototype_ `SWorkspaceTabWrapper() = default;`
- L28 _public function_ `SLATE_BEGIN_ARGS( SWorkspaceTabWrapper )`
- L29 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FTabInfo> InTabInfo, const UE::Workspace::FWorkspaceEditorContext& InEditorContext);`
- L33 _public function_ `TSharedRef<SWidget> GetContent() const`
- L34 _public function_ `TWeakObjectPtr<UObject> GetDocumentObject() const`
- L35 _public function_ `UE::Workspace::FWorkspaceDocument GetDocument() const`
- L38 _protected prototype_ `void RebuildBreadcrumbTrail() const;`
- L39 _protected prototype_ `const FSlateBrush* GetTabIcon() const;`
- L40 _protected prototype_ `EVisibility IsWorkspaceNameVisible() const;`
- L41 _protected prototype_ `FText GetWorkspaceName() const;`
- L43 _protected prototype_ `void ExecuteSave() const;`
- L44 _protected prototype_ `bool CanExecuteSave() const;`
- L45 _protected prototype_ `bool IsSaveButtonVisible() const;`
- L46 _protected prototype_ `void FindObjectInContentBrowser() const;`
- L48 _protected member_ `TSharedPtr<SWidget> Content = nullptr;`
- L49 _protected member_ `TWeakPtr<UE::Workspace::FWorkspaceEditor> WeakWorkspaceEditor = nullptr;`
- L50 _protected member_ `TWeakObjectPtr<UObject> WeakDocumentObject = nullptr;`
- L51 _protected member_ `FWorkspaceOutlinerItemExport Export;`
- L53 _protected member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox = nullptr;`
- L54 _protected member_ `TSharedPtr<SBreadcrumbTrail<TSharedPtr<UE::Workspace::FWorkspaceBreadcrumb>>> BreadcrumbTrail = nullptr;`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/SWorkspaceView.h` (Private)


#### class `UE::Workspace::SWorkspaceView`  
`class SWorkspaceView : public SCompoundWidget`  
_L18-37_
- inherits: `SCompoundWidget`
- L20 _private function_ `SLATE_BEGIN_ARGS(SWorkspaceView)`
- L21 _private prototype_ `SLATE_ATTRIBUTE(bool, CanSaveAll) SLATE_EVENT(FOnClicked, OnSaveAll) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UWorkspace* InWorkspace, TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor);`
- L27 _private prototype_ `void SelectObject(const UObject* InObject) const;`
- L28 _private prototype_ `void SelectExport(const FWorkspaceOutlinerItemExport& InExport) const;`
- L30 _private prototype_ `void GetWorkspaceExportData(FWorkspaceOutlinerItemExport& InOutPartialExport) const;` — Tries to lookup the FWorkspaceOutlinerItemExport path within the outliner, and copies over its TInstancedStruct<FWorkspaceOutlinerItemData> value
- L31 _private prototype_ `void GetHierarchyAssetData(TArray<FAssetData>& OutAssetData) const;`
- L34 _private member_ `UWorkspace* Workspace = nullptr;`
- L35 _private member_ `FWorkspaceOutlinerMode* OutlinerMode = nullptr;`
- L36 _private member_ `TSharedPtr<SWorkspaceOutliner> SceneWorkspaceOutliner;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/Workspace.h` (Private)


#### struct `FWorkspaceAssetRegistryExportEntry`  
`struct FWorkspaceAssetRegistryExportEntry`  
_L45-57_
- reflection: `USTRUCT()`
- desc: Workspace entry used to export to asset registry
- L49 _public prototype_ `FWorkspaceAssetRegistryExportEntry() = default;`
- L51 _public function_ `FWorkspaceAssetRegistryExportEntry(const FSoftObjectPath& InAsset) : Asset(InAsset)`
- L56 _public member_ `FSoftObjectPath Asset;` — `UPROPERTY()`

#### struct `FWorkspaceAssetRegistryExports`  
`struct FWorkspaceAssetRegistryExports`  
_L61-67_
- reflection: `USTRUCT()`
- desc: Workspace used to export to asset registry
- L66 _public member_ `TArray<FWorkspaceAssetRegistryExportEntry> Assets;` — `UPROPERTY()`

#### class `UWorkspace`  
`class UWorkspace : public UObject`  
_L70-177_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L94 _private prototype_ `bool AddAsset(UObject* InAsset, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "Workspace")` — Adds an asset to the workspace @return true if the asset was added
- L95 _private prototype_ `bool AddAsset(const FAssetData& InAsset, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);`
- L100 _private prototype_ `bool AddAssets(const TArray<UObject*>& InAssets, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "Workspace")` — Adds assets to the workspace @return true if an asset was added
- L101 _private prototype_ `bool AddAssets(TConstArrayView<FAssetData> InAssets, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);`
- L106 _private prototype_ `bool RemoveAsset(UObject* InAsset, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "Workspace")` — Removes an asset from the workspace @return true if the asset was removed
- L107 _private prototype_ `bool RemoveAsset(const FAssetData& InAsset, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);`
- L112 _private prototype_ `bool RemoveAssets(TArray<UObject*> InAssets, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);` — `UFUNCTION(BlueprintCallable, Category = "Workspace")` — Removes assets from the workspace @return true if the asset was removed
- L113 _private prototype_ `bool RemoveAssets(TConstArrayView<FAssetData> InAssets, bool bSetupUndoRedo = true, bool bPrintPythonCommand = true);`
- L115 _private prototype_ `bool IsAssetSupported(const FAssetData& InAsset);`
- L117 _private prototype_ `UWorkspaceSchema* GetSchema() const;`
- L119 _private prototype_ `void LoadState() const;`
- L120 _private prototype_ `void SaveState() const;`
- L121 _private prototype_ `UWorkspaceState* GetState() const;`
- L123 _private prototype_ `void ReportError(const TCHAR* InMessage) const;`
- L125 _private prototype_ `void BroadcastModified();`
- L130 _private prototype_ `UObject* GetRootAsset() const;` — Returns the "root asset" that this workspace was created for. Returns nullptr if the schema does not support a root asset. Root assets cannot be removed from the workspace.
- L133 _private prototype_ `void GetAssets(TArray<TObjectPtr<UObject>>& OutAssets) const;` — Returns all contained Asset objects
- L135 _private prototype_ `TConstArrayView<FAssetData> GetAssetDataEntriesView(bool bRefresh = false) const;` — Returns all contained AssetData entries
- L138 _private prototype_ `bool HasValidEntries() const;` — Returns whether or not the workspace contains _any_ valid UWorkspaceAssetEntry
- L141 _private prototype_ `virtual void PostLoad() override;` — UObject interface
- L142 _private prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L143 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L144 _private function_ `virtual bool IsEditorOnly() const override`
- L145 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L146 _private prototype_ `virtual bool Rename(const TCHAR* NewName = nullptr, UObject* NewOuter = nullptr, ERenameFlags Flags = REN_None) override;`
- L147 _private prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L149 _private prototype_ `void PostLoadExternalPackages();`
- L153 _private member_ `TArray<TSoftObjectPtr<UObject>> Assets_DEPRECATED;` — `UPROPERTY()` — All of the assets referenced by this workspace
- L157 _private member_ `TArray<TObjectPtr<UWorkspaceAssetEntry>> AssetEntries;` — `UPROPERTY(transient)` — All of the assets in-directly referenced by this workspace
- L159 _private member_ `mutable TArray<FAssetData> EntriesAssetData;`
- L163 _private member_ `TSubclassOf<UWorkspaceSchema> SchemaClass;` — `UPROPERTY(AssetRegistrySearchable)` — Schema for this workspace
- L167 _private member_ `mutable TObjectPtr<UWorkspaceState> State = nullptr;` — `UPROPERTY(Transient)` — State of the workspace, persisted to json
- L171 _private member_ `FGuid Guid;` — `UPROPERTY()` — Guid for persistent identification of this workspace
- L174 _private member_ `UE::Workspace::FOnWorkspaceModified ModifiedDelegate;` — Delegate to subscribe to modifications
- L176 _private member_ `bool bSuspendNotifications = false;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Workspace` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace UAF` (scope `UE`)
- L31 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Workspace` (scope `UE`)
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWorkspaceModified, UWorkspace* );` — A delegate for subscribing / reacting to workspace modifications.
- L39 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWorkspaceModified, UWorkspace* );` (scope `UE::Workspace`) — A delegate for subscribing / reacting to workspace modifications.

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceAssetDefinition.h` (Private)


#### class `UAssetDefinition_Workspace`  
`class UAssetDefinition_Workspace : public UAssetDefinitionDefault`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L19 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;`
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L23 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public function_ `virtual bool ShouldSaveExternalPackages() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AssetDefinitions"`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceAssetEditor.h` (Private)


#### class `UWorkspaceAssetEditor`  
`class UWorkspaceAssetEditor : public UAssetEditor`  
_L12-27_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- L16 _public prototype_ `void SetObjectToEdit(UWorkspace* InWorkspace);`
- L17 _public prototype_ `UWorkspace* GetObjectToEdit();`
- L21 _protected prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjectsToEdit) override;` — For standalone workspace, the workspace itself will be returned otherwise the underlying assets will be returned
- L22 _protected prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L26 _private member_ `TObjectPtr<UWorkspace> ObjectToEdit;` — `UPROPERTY()`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceAssetEntry.h` (Private)


#### class `UWorkspaceAssetEntry`  
`class UWorkspaceAssetEntry : public UObject`  
_L12-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `static const FName ExportsAssetRegistryTag;`
- L18 _public prototype_ `virtual bool IsAsset() const override;`
- L19 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L22 _public member_ `TSoftObjectPtr<UObject> Asset;` — `UPROPERTY()`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceAssetEntryAssetDefinition.h` (Private)


#### class `UAssetDefinition_WorkspaceAssetEntry`  
`class UAssetDefinition_WorkspaceAssetEntry : public UAssetDefinitionDefault`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override;`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceAssetReferenceItemDetails.h` (Private)


#### class `UE::Workspace::FWorkspaceAssetReferenceOutlinerItemDetails`  
`class FWorkspaceAssetReferenceOutlinerItemDetails : public IWorkspaceOutlinerItemDetails`  
_L13-81_
- inherits: `IWorkspaceOutlinerItemDetails`
- L16 _public prototype_ `virtual ~FWorkspaceAssetReferenceOutlinerItemDetails() override = default;`
- L18 _public function_ `static TSharedPtr<IWorkspaceOutlinerItemDetails> GetInnerDetails(const FWorkspaceOutlinerItemExport& Export)`
- L31 _public function_ `static const FWorkspaceOutlinerItemExport& GetInnerExport(const FWorkspaceOutlinerItemExport& Export)`
- L39 _public function_ `virtual FString GetDisplayString(const FWorkspaceOutlinerItemExport& Export) const override`
- L49 _public function_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override`
- L63 _public function_ `virtual FSlateColor GetItemColor(const FWorkspaceOutlinerItemExport& Export) const override`
- L77 _public function_ `virtual bool IsExpandedByDefault() const override`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceAssetViewportClient.h` (Private)


#### class `UE::Workspace::FWorkspaceAssetViewportClient`  
`class FWorkspaceAssetViewportClient : public FEditorViewportClient`  
_L10-23_
- inherits: `FEditorViewportClient`
- L13 _public function_ `FWorkspaceAssetViewportClient(FEditorModeTools* InModeTools, const TSharedPtr<FAdvancedPreviewScene>& InPreviewScene) : FEditorViewportClient(InModeTools, InPreviewScene.Get()) , AdvancedPreviewScene(InPreviewScene)`
- L20 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FEditorViewportClient interface
- L22 _public member_ `TSharedPtr<FAdvancedPreviewScene> AdvancedPreviewScene = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceEditor.h` (Private)


#### class `UE::Workspace::FWorkspaceEditor`  
`class FWorkspaceEditor : public IWorkspaceEditor, public FGCObject`  
_L44-192_
- inherits: `IWorkspaceEditor,FGCObject`
- L47 _public prototype_ `FWorkspaceEditor(UWorkspaceAssetEditor* InOwningAssetEditor);`
- L48 _public function_ `virtual ~FWorkspaceEditor() override`
- L61 _private prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — FBaseAssetToolkit interface
- L62 _private prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L63 _private prototype_ `virtual FName GetToolkitFName() const override;`
- L64 _private prototype_ `virtual FText GetBaseToolkitName() const override;`
- L65 _private prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L66 _private prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L67 _private prototype_ `virtual void CreateWidgets() override;`
- L68 _private prototype_ `virtual void PostInitAssetEditor() override;`
- L69 _private prototype_ `virtual void InitToolMenuContext(FToolMenuContext& InMenuContext) override;`
- L70 _private prototype_ `virtual void SaveAsset_Execute() override;`
- L71 _private prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L72 _private prototype_ `virtual void OnClose() override;`
- L73 _private prototype_ `virtual void RegisterToolbar() override;`
- L74 _private prototype_ `virtual bool ShouldReopenEditorForSavedAsset(const UObject* Asset) const override;`
- L75 _private prototype_ `virtual void RemoveEditingObject(UObject* Object) override;`
- L76 _private prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L77 _private prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L80 _private prototype_ `virtual void GetSaveableObjects(TArray<UObject*>& OutObjects) const override;` — FAssetEditorToolkit interface
- L81 _private prototype_ `virtual bool CanSaveAsset() const override;`
- L82 _private prototype_ `virtual FText GetTabSuffix() const override;`
- L83 _private prototype_ `virtual FText GetToolkitName() const override;`
- L84 _private prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L85 _private prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L86 _private prototype_ `virtual FLinearColor GetDefaultTabColor() const override;`
- L87 _private prototype_ `virtual void FindInContentBrowser_Execute() override;`
- L88 _private prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L89 _private prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L92 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L93 _private function_ `virtual FString GetReferencerName() const override`
- L99 _private prototype_ `virtual void OpenAssets(TConstArrayView<FAssetData> InAssets) override;` — IWorkspaceEditor interface
- L100 _private prototype_ `virtual void OpenExports(TConstArrayView<FWorkspaceOutlinerItemExport> InExports, TOptional<FDocumentTracker::EOpenDocumentCause> OpenCauseOverride) override;`
- L101 _private prototype_ `virtual void OpenObjects(TConstArrayView<UObject*> InObjects, TOptional<FDocumentTracker::EOpenDocumentCause> OpenCauseOverride) override;`
- L102 _private prototype_ `virtual void GetOpenedAssetsOfClass(TSubclassOf<UObject> InClass, TArray<UObject*>& OutObjects) const override;`
- L103 _private prototype_ `virtual void GetAssets(TArray<FAssetData>& OutAssets, bool bIncludeAssetReferences = false) const override;`
- L104 _private prototype_ `virtual void CloseObjects(TConstArrayView<UObject*> InObjects) override;`
- L105 _private prototype_ `virtual void SetDetailsObjects(const TArray<UObject*>& InObjects) override;`
- L106 _private prototype_ `virtual void RefreshDetails() override;`
- L107 _private prototype_ `virtual UWorkspaceSchema* GetSchema() const override;`
- L108 _private prototype_ `virtual bool GetOutlinerSelection(TArray<FWorkspaceOutlinerItemExport>& OutExports) const override;`
- L109 _private prototype_ `virtual FOnOutlinerSelectionChanged& OnOutlinerSelectionChanged() override;`
- L110 _private prototype_ `virtual void SetGlobalSelection(FGlobalSelectionId SelectionId, FOnClearGlobalSelection OnClearSelectionDelegate) override;`
- L111 _private prototype_ `virtual const FWorkspaceDocument& GetFocusedDocumentOfClass(const TObjectPtr<UClass> AssetClass) const override;`
- L112 _private prototype_ `virtual FOnFocusedDocumentChanged& OnFocusedDocumentChanged() override;`
- L113 _private prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() override;`
- L114 _private prototype_ `virtual UObject* GetWorkspaceAsset() const override;`
- L115 _private prototype_ `virtual FString GetPackageName() const override;`
- L116 _private prototype_ `virtual const FWorkspaceDocument& GetFocusedWorkspaceDocument() const override;`
- L117 _private prototype_ `virtual void SetSceneDescription(TObjectPtr<UWorkspaceViewportSceneDescription> InSceneDescription) override;`
- L118 _private prototype_ `virtual UWorkspaceViewportSceneDescription* GetSceneDescription() const override;`
- L119 _private prototype_ `virtual UObject* GetFocusedAsset() const override;`
- L121 _private prototype_ `void ReinitViewportScene();`
- L123 _private prototype_ `void HandleOutlinerSelectionChanged(TConstArrayView<FWorkspaceOutlinerItemExport> InExports);`
- L125 _private prototype_ `void BindCommands();`
- L127 _private prototype_ `void ExtendMenu() const;`
- L129 _private prototype_ `void ExtendToolbar() const;`
- L131 _private prototype_ `void CloseDocumentTab(const UObject* DocumentID) const;`
- L133 _private prototype_ `bool InEditingMode() const;`
- L135 _private prototype_ `void RestoreEditedObjectState();`
- L137 _private prototype_ `void SaveEditedObjectState() const;`
- L139 _private prototype_ `TSharedPtr<SDockTab> OpenDocument(const UObject* InForObject, FDocumentTracker::EOpenDocumentCause InCause);`
- L140 _private prototype_ `TSharedPtr<SDockTab> OpenDocument(const UObject* InForObject, const FWorkspaceOutlinerItemExport& InExport, FDocumentTracker::EOpenDocumentCause InCause);`
- L142 _private prototype_ `void RecordDocumentState(const TInstancedStruct<FWorkspaceDocumentState>& InState) const;`
- L144 _private prototype_ `void SetFocusedDocument(const UE::Workspace::FWorkspaceDocument& Document);`
- L146 _private prototype_ `void NavigateBack() const;`
- L147 _private prototype_ `void NavigateForward() const;`
- L149 _private prototype_ `void SaveAssetEntries();`
- L150 _private prototype_ `bool AreAssetEntriesModified() const;`
- L152 _private prototype_ `bool IsViewportPinned() const;`
- L155 _private prototype_ `void OnProvideAdditionalCrashContext(FCrashContextExtendedWriter& CrashContextExtendedWriter) const;`
- L159 _private member_ `TObjectPtr<UWorkspace> Workspace = nullptr;` — The asset being edited
- L162 _private member_ `TSharedPtr<FDocumentTracker> DocumentManager;` — Document tracker
- L164 _private member_ `TSharedPtr<SWorkspaceView> WorkspaceView;`
- L166 _private member_ `TMap<FName, TSharedPtr<FWorkspaceEditorModeUILayer>> ModeUILayers;`
- L167 _private member_ `TArray<TSharedPtr<class IToolkit>> HostedToolkits;`
- L170 _private member_ `FWorkflowAllowedTabSet TabFactories;` — Tabs to be registered into the Workspace
- L172 _private member_ `bool bSavingTransientWorkspace = false;`
- L173 _private member_ `bool bSavingWorkspace = false;`
- L174 _private member_ `bool bSavingAssetEntries = false;`
- L175 _private member_ `bool bClosingDown = false;`
- L176 _private member_ `bool bSettingFocusedDocument = false;`
- L178 _private member_ `TArray<TPair<FGlobalSelectionId, FOnClearGlobalSelection>> GlobalSelections;`
- L179 _private member_ `FOnOutlinerSelectionChanged OnOutlinerSelectionChangedDelegate;`
- L180 _private member_ `bool bSelectionScopeCleared = true;`
- L181 _private member_ `int32 SelectionScopeDepth = 0;`
- L183 _private member_ `TArray<FWorkspaceOutlinerItemExport> LastSelectedExports;`
- L184 _private member_ `FOnFocusedDocumentChanged OnFocusedDocumentChangedDelegate;`
- L185 _private member_ `TSharedPtr<FWorkspaceItem> EditorMenuCategory;`
- L187 _private member_ `TOptional<FWorkspaceDocument> LastDocument;`
- L189 _private member_ `TUniquePtr<IWorkspaceViewportController> ActiveViewportController;`
- L190 _private member_ `TObjectPtr<UWorkspaceViewportSceneDescription> SceneDescription;`
- L191 _private member_ `FSoftObjectPath ViewportPinnedAssetPath;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Workspace` (scope `UE`)
- L33 _namespace_ `namespace WorkspaceModes` (scope `UE::Workspace`)
- L35 _externvar_ `extern const FName WorkspaceEditor;` (scope `UE::Workspace::WorkspaceModes`)
- L38 _namespace_ `namespace WorkspaceTabs` (scope `UE::Workspace`)
- L40 _externvar_ `extern const FName Details;` (scope `UE::Workspace::WorkspaceTabs`)
- L41 _externvar_ `extern const FName WorkspaceView;` (scope `UE::Workspace::WorkspaceTabs`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceEditorCommands.h` (Private)


#### class `UE::Workspace::FWorkspaceAssetEditorCommands`  
`class FWorkspaceAssetEditorCommands : public TCommands<FWorkspaceAssetEditorCommands>`  
_L11-21_
- inherits: `TCommands<FWorkspaceAssetEditorCommands>`
- L14 _public prototype_ `FWorkspaceAssetEditorCommands();`
- L15 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> NavigateBackward;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> NavigateForward;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> SaveAssetEntries;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> Open;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceEditorModeUILayer.h` (Private)


#### class `FWorkspaceEditorModeUILayer`  
`class FWorkspaceEditorModeUILayer : public FAssetEditorModeUILayer`  
_L9-20_
- inherits: `FAssetEditorModeUILayer`
- L12 _public prototype_ `FWorkspaceEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L13 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L14 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L15 _public prototype_ `virtual TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`
- L17 _public prototype_ `void SetModeMenuCategory(const TSharedPtr<FWorkspaceItem>& MenuCategoryIn);`
- L19 _protected member_ `TSharedPtr<FWorkspaceItem> MenuCategory;`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceEditorModule.h` (Private)


#### class `UE::Workspace::FWorkspaceEditorModule`  
`class FWorkspaceEditorModule : public IWorkspaceEditorModule`  
_L23-100_
- inherits: `IWorkspaceEditorModule`
- L27 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L30 _private prototype_ `virtual void RegisterObjectDocumentType(const FTopLevelAssetPath& InClassPath, const FObjectDocumentArgs& InParams) override;` — IWorkspaceModule interface
- L31 _private prototype_ `virtual void UnregisterObjectDocumentType(const FTopLevelAssetPath& InClassPath) override;`
- L32 _private prototype_ `virtual void RegisterDocumentSubObjectType(const FTopLevelAssetPath& InClassPath, const FDocumentSubObjectArgs& InParams) override;`
- L33 _private prototype_ `virtual void UnregisterDocumentSubObjectType(const FTopLevelAssetPath& InClassPath) override;`
- L34 _private prototype_ `virtual FObjectDocumentArgs CreateGraphDocumentArgs(const FGraphDocumentWidgetArgs& InArgs) override;`
- L35 _private prototype_ `virtual IWorkspaceEditor* OpenWorkspaceForObject(UObject* InObject, EOpenWorkspaceMethod InOpenMethod, const TSubclassOf<UWorkspaceFactory> WorkSpaceFactoryClass) override;`
- L36 _private prototype_ `virtual FOnRegisterDetailCustomizations& OnRegisterWorkspaceDetailsCustomization() override;`
- L37 _private prototype_ `virtual void RegisterWorkspaceItemDetails(const FOutlinerItemDetailsId& InItemDetailsId, TSharedPtr<IWorkspaceOutlinerItemDetails> InItemDetails) override;`
- L38 _private prototype_ `virtual void UnregisterWorkspaceItemDetails(const FOutlinerItemDetailsId& InItemDetails) override;`
- L39 _private function_ `virtual FOnRegisterTabs& OnRegisterTabsForEditor() override`
- L40 _private function_ `virtual FOnExtendTabs& OnExtendTabs() override`
- L41 _private function_ `virtual FOnExtendToolMenuContext& OnExtendToolMenuContext() override`
- L42 _private prototype_ `virtual TSharedPtr<IWorkspacePicker> CreateWorkspacePicker(const IWorkspacePicker::FConfig& Config) const override;`
- L43 _private prototype_ `virtual void RegisterViewportControllerFactory(const UClass* InClassPath, const FWorkspaceViewportControllerFactory InControllerFactory) override;`
- L44 _private prototype_ `virtual void UnregisterViewportControllerFactory(const UClass* InClassPath) override;`
- L48 _private prototype_ `TUniquePtr<IWorkspaceViewportController> CreateViewportController(const UClass* InClassPath) const;` — Create a new viewport controller for a given asset class if a controller has been registered * Can return nullptr
- L51 _private prototype_ `const FObjectDocumentArgs* FindObjectDocumentType(const FWorkspaceDocument& Document) const;` — Find an existing registered object document type. Note this redirects based on FObjectDocumentArgs::OnRedirectWorkspaceContext
- L54 _private prototype_ `const FDocumentSubObjectArgs* FindDocumentSubObjectType(const UObject* InObject) const;` — Find an existing registered document sub-object type.
- L57 _private prototype_ `TArray<FTopLevelAssetPath> GetAllowedObjectTypesForArea(FName InSpawnLocation) const;` — Find the set of allowed object types for the specified spawn location
- L60 _private prototype_ `static bool GetExportedAssetsForWorkspace(const FAssetData& InWorkspaceAsset, FWorkspaceAssetRegistryExports& OutExports);` — Get the exported set of assets in asset registry tags for a workspace's FAssetData
- L63 _private prototype_ `void ApplyWorkspaceDetailsCustomization(const TWeakPtr<IWorkspaceEditor>& Editor, TSharedPtr<IDetailsView>& DetailsView) const;` — Applies any previously registered details-view customizations
- L65 _private member_ `TMap<FTopLevelAssetPath, FObjectDocumentArgs> ObjectDocumentArgs;`
- L67 _private member_ `TMap<FName, FWorkspaceViewportControllerFactory> ViewportControllerFactories;`
- L69 _private member_ `TMap<FName, TSet<FTopLevelAssetPath>> DocumentAreaMap;`
- L71 _private member_ `TMap<FTopLevelAssetPath, FDocumentSubObjectArgs> DocumentSubObjectArgs;`
- L73 _private member_ `static TMap<FOutlinerItemDetailsId, TSharedPtr<IWorkspaceOutlinerItemDetails>> OutlinerItemDetails;`
- L74 _private prototype_ `static TSharedPtr<IWorkspaceOutlinerItemDetails> GetOutlinerItemDetails(const FOutlinerItemDetailsId& DetailId);`
- L77 _private member_ `FOnRegisterDetailCustomizations OnRegisterDetailCustomizations;` — Event called to allow external clients to register details customizations
- L80 _private member_ `FOnRegisterTabs RegisterTabsForEditor;` — Event called to allow external clients to register additional tabs for the specified editor
- L83 _private member_ `FOnExtendTabs ExtendTabsForEditor;` — Event called to allow external clients to extend the tab layout for the specified editor
- L86 _private member_ `FOnExtendToolMenuContext ExtendToolMenuContext;` — Event called to allow external clients to add details to the ToolMenuContext used for the toolbar and context menus

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Workspace` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceGroupItemDetails.h` (Private)


#### class `UE::Workspace::FWorkspaceGroupOutlinerItemDetails`  
`class FWorkspaceGroupOutlinerItemDetails : public IWorkspaceOutlinerItemDetails`  
_L13-36_
- inherits: `IWorkspaceOutlinerItemDetails`
- L16 _public prototype_ `virtual ~FWorkspaceGroupOutlinerItemDetails() override = default;`
- L18 _public function_ `virtual FString GetDisplayString(const FWorkspaceOutlinerItemExport& Export) const override`
- L24 _public function_ `virtual bool HandleSelected(const FToolMenuContext& ToolMenuContext) const override`
- L26 _public function_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override`
- L32 _public function_ `virtual bool IsExpandedByDefault() const override`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceState.h` (Private)


#### class `UWorkspaceState`  
`class UWorkspaceState : public UObject`  
_L18-55_
- reflection: `UCLASS()`
- inherits: `UObject`
- L22 _private prototype_ `UWorkspaceState();`
- L25 _private prototype_ `static FString GetWorkspacePath(const UWorkspace* InWorkspace);` — Generate a file path used to persist workspace state
- L28 _private prototype_ `void SaveToJson(const UWorkspace* InWorkspace);` — Save this workspace state to JSON
- L31 _private prototype_ `void LoadFromJson(const UWorkspace* InWorkspace);` — Load this workspace state from JSON
- L34 _private prototype_ `void HandleAssetRenamed(const FAssetData& InAssetData, const FString& InOldName);` — Update soft object paths to any assets we reference
- L37 _private function_ `void SetUserState(FInstancedStruct&& InUserState)` — Accessors for user state
- L38 _private function_ `const FInstancedStruct& GetUserState() const`
- L42 _private member_ `FSoftObjectPath WorkspacePath;` — `UPROPERTY()` — Path to the workspace we are persisting, to allow files to be more easily parsed out
- L46 _private member_ `FInstancedStruct UserState;` — `UPROPERTY()` — User workspace state
- L50 _private member_ `TArray<TInstancedStruct<FWorkspaceDocumentState>> DocumentStates;` — `UPROPERTY()` — All the workspace documents we are persisting

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Private/WorkspaceViewportMenuContext.h` (Private)


#### class `UWorkspaceViewportMenuContext`  
`class UWorkspaceViewportMenuContext : public UObject`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `TAttribute<bool> bIsPinned;`
- L19 _public member_ `TAttribute<FSoftObjectPath> PreviewAssetPath;`
- L20 _public member_ `FSimpleDelegate OnPinnedClicked;`
- L23 _public member_ `TObjectPtr<UWorkspaceViewportSceneDescription> SceneDescription;` — `UPROPERTY()`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/IWorkspaceEditor.h` (Public)


#### struct `UE::Workspace::FWorkspaceEditorSelectionScope`  
`struct FWorkspaceEditorSelectionScope`  
_L27-33_
- desc: RAII helper allowing for a multi-widget selection scope within a WorkspaceEditor instance
- L29 _public prototype_ `FWorkspaceEditorSelectionScope(const TSharedPtr<class IWorkspaceEditor>& InWorkspaceEditor);`
- L30 _public prototype_ `~FWorkspaceEditorSelectionScope();`
- L32 _public member_ `TWeakPtr<class IWorkspaceEditor> WeakWorkspaceEditor;`

#### class `UE::Workspace::IWorkspaceEditor`  
`class IWorkspaceEditor : public FBaseAssetToolkit`  
_L35-114_
- inherits: `FBaseAssetToolkit`
- L38 _public function_ `IWorkspaceEditor(UAssetEditor* InOwningAssetEditor) : FBaseAssetToolkit(InOwningAssetEditor)`
- L41 _public prototype_ `virtual void OpenAssets(TConstArrayView<FAssetData> InAssets) = 0;` — Open the supplied assets for editing within the workspace editor
- L44 _public prototype_ `virtual void OpenExports(TConstArrayView<FWorkspaceOutlinerItemExport> InExports, TOptional<FDocumentTracker::EOpenDocumentCause> OpenCauseOverride = TOptional<FDocumentTracker::EOpenDocumentCause>()) = 0;` — Open the supplied exports for editing within the workspace editor
- L47 _public prototype_ `virtual void OpenObjects(TConstArrayView<UObject*> InObjects, TOptional<FDocumentTracker::EOpenDocumentCause> OpenCauseOverride = TOptional<FDocumentTracker::EOpenDocumentCause>()) = 0;` — Open the supplied objects for editing within the workspace editor
- L50 _public prototype_ `virtual void GetOpenedAssetsOfClass(TSubclassOf<UObject> InClass, TArray<UObject*>& OutObjects) const = 0;` — Get the current set of opened (loaded) assets of the specified class
- L53 _public function_ `void GetOpenedAssets(TArray<UObject*>& OutObjects) const` — Get the current set of opened (loaded) assets
- L57 _public function_ `template<typename AssetClass> void GetOpenedAssets(TArray<UObject*>& OutObjects) const` — Get the current set of opened (loaded) assets
- L60 _public prototype_ `virtual void GetAssets(TArray<FAssetData>& OutAssets, bool bIncludeAssetReferences = false) const = 0;` — Get the current set of assets in this workspace editor
- L63 _public prototype_ `virtual void CloseObjects(TConstArrayView<UObject*> InObjects) = 0;` — Close the supplied objects if they are open for editing within the workspace editor
- L66 _public prototype_ `virtual void SetDetailsObjects(const TArray<UObject*>& InObjects) = 0;` — Show the supplied objects in the workspace editor details panel
- L69 _public prototype_ `virtual void RefreshDetails() = 0;` — Refresh the workspace editor details panel
- L72 _public prototype_ `virtual UWorkspaceSchema* GetSchema() const = 0;` — Exposes the editor WorkspaceSchema
- L75 _public prototype_ `virtual void SetGlobalSelection(FGlobalSelectionId SelectionId, FOnClearGlobalSelection OnClearSelectionDelegate) = 0;` — Set the _current_ global selection (last SWidget with selection set) with delegate to clear it selection on next SetGlobalSelection()
- L78 _public prototype_ `virtual const FWorkspaceDocument& GetFocusedDocumentOfClass(const TObjectPtr<UClass> InClass) const = 0;` — Get the currently focused document. @return unset if the class does not match or no document is focused
- L81 _public prototype_ `virtual const FWorkspaceDocument& GetFocusedWorkspaceDocument() const = 0;` — Returns the currently focused workspace document (last user activated tab), unset in case of none is focused
- L84 _public prototype_ `virtual FOnFocusedDocumentChanged& OnFocusedDocumentChanged() = 0;` — Multicast delegate broadcast whenever the document focus of the WorkspaceEditor changes
- L88 _public prototype_ `virtual bool GetOutlinerSelection(TArray<FWorkspaceOutlinerItemExport>& OutExports) const = 0;` — Get the current single selection of the outliner. @return true if a single selection is active
- L91 _public typedef_ `using FOnOutlinerSelectionChanged = TMulticastDelegate<void(TConstArrayView<FWorkspaceOutlinerItemExport> InExports)>;` — Delegate fired when selection changes in the workspace outliner
- L92 _public prototype_ `virtual FOnOutlinerSelectionChanged& OnOutlinerSelectionChanged() = 0;`
- L95 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() = 0;` — Retrieves the common DetailsView widget
- L98 _public prototype_ `virtual UObject* GetWorkspaceAsset() const = 0;` — Returns the workspace asset
- L101 _public prototype_ `virtual FString GetPackageName() const = 0;` — Returns the name of the package where the workspace is located
- L104 _public function_ `static FName GetWorkspaceEditorToolkitName()` — Name of EditorToolkit, used for testing against FAssetEditorToolkit::GetToolkitFName
- L107 _public prototype_ `virtual void SetSceneDescription(TObjectPtr<UWorkspaceViewportSceneDescription> InSceneDescription) = 0;` — Set a new scene description config
- L110 _public prototype_ `virtual UWorkspaceViewportSceneDescription* GetSceneDescription() const = 0;` — Get the current scene description config
- L113 _public prototype_ `virtual UObject* GetFocusedAsset() const = 0;` — Gets the currently focused asset's UObject

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WORKSPACEEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Workspace` (scope `UE`)
- L19 _typedef_ `typedef TWeakPtr<SWidget> FGlobalSelectionId;` (scope `UE::Workspace`)
- L20 _typedef_ `using FOnClearGlobalSelection = FSimpleDelegate;` (scope `UE::Workspace`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusedDocumentChanged, const FWorkspaceDocument&);`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusedDocumentChanged, const FWorkspaceDocument&);` (scope `UE::Workspace`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/IWorkspaceEditorModule.h` (Public)


#### struct `UE::Workspace::FWorkspaceDocument`  
`struct FWorkspaceDocument`  
_L52-73_
- L54 _public member_ `FWorkspaceOutlinerItemExport Export;`
- L55 _public member_ `UObject* Object = nullptr;`
- L57 _public prototype_ `FWorkspaceDocument() = default;`
- L58 _public prototype_ `FWorkspaceDocument(const FWorkspaceOutlinerItemExport& InExport, UObject* InObject);`
- L60 _public function_ `bool operator==(const FWorkspaceDocument& InOther) const`
- L66 _public function_ `UObject* GetObject() const`
- L69 _public function_ `template<class ObjectClass> ObjectClass* GetTypedObject() const`
- L72 _public function_ `template<class ObjectClass> ObjectClass* GetTypedObjectChecked() const`

#### struct `UE::Workspace::FWorkspaceEditorContext`  
`struct FWorkspaceEditorContext`  
_L76-87_
- desc: Context passed to workspace editor delegates
- L78 _public prototype_ `FWorkspaceEditorContext(const TSharedRef<IWorkspaceEditor>& InWorkspaceEditor, const FWorkspaceDocument& InDocument);`
- L79 _public prototype_ `FWorkspaceEditorContext(const TSharedRef<IWorkspaceEditor>& InWorkspaceEditor, UObject* InObject, const FWorkspaceOutlinerItemExport& InExport);`
- L80 _public prototype_ `FWorkspaceEditorContext() = delete;`
- L83 _public member_ `TSharedRef<IWorkspaceEditor> WorkspaceEditor;` — The current workspace editor
- L86 _public member_ `FWorkspaceDocument Document;` — The document (object + export) being edited

#### struct `UE::Workspace::FWorkspaceBreadcrumb`  
`struct FWorkspaceBreadcrumb : TSharedFromThis<FWorkspaceBreadcrumb>`  
_L89-100_
- inherits: `TSharedFromThis<FWorkspaceBreadcrumb>`
- L91 _public typedef_ `using FOnGetBreadcrumbLabel = TDelegate<TAttribute<FText>()>;`
- L92 _public typedef_ `using FOnBreadcrumbClicked = TDelegate<void()>;`
- L93 _public typedef_ `using FCanSaveBreadcrumb = TDelegate<bool()>;`
- L94 _public typedef_ `using FOnSaveBreadcrumb = TDelegate<void()>;`
- L96 _public member_ `FOnGetBreadcrumbLabel OnGetLabel;`
- L97 _public member_ `FOnBreadcrumbClicked OnClicked;`
- L98 _public member_ `FCanSaveBreadcrumb CanSave;`
- L99 _public member_ `FOnSaveBreadcrumb OnSave;`

#### struct `UE::Workspace::FObjectDocumentArgs`  
`struct FObjectDocumentArgs`  
_L121-160_
- desc: Arguments used to make document widgets for objects
- L123 _public prototype_ `FObjectDocumentArgs() = default;`
- L125 _public function_ `FObjectDocumentArgs(const FOnMakeDocumentWidget& InOnMakeDocumentWidget, FName InSpawnLocation = WorkspaceTabs::TopMiddleDocumentArea) : OnMakeDocumentWidget(InOnMakeDocumentWidget) , SpawnLocation(InSpawnLocation)`
- L130 _public function_ `FObjectDocumentArgs(const FOnRedirectWorkspaceContext& InOnRedirectWorkspaceContext) : OnRedirectWorkspaceContext(InOnRedirectWorkspaceContext)`
- L135 _public member_ `FOnRedirectWorkspaceContext OnRedirectWorkspaceContext;` — Delegate called to redirect the context to another document object (e.g. a subobject)
- L138 _public member_ `FOnMakeDocumentWidget OnMakeDocumentWidget;` — Delegate called to generate a widget for the supplied object
- L141 _public member_ `FOnGetDocumentState OnGetDocumentState;` — Delegate called to build a struct used to store the document's state
- L144 _public member_ `FOnSetDocumentState OnSetDocumentState;` — Delegate called to use a struct to restore the document's state
- L147 _public member_ `FOnGetTabIcon OnGetTabIcon;` — Delegate called to get the tab icon to display. If this is unset, the icon will default to the asset icon for the class
- L150 _public member_ `FOnGetTabName OnGetTabName;` — Delegate called to get the tab name to display. If this is unset, the object's name will be used
- L153 _public member_ `FName SpawnLocation = WorkspaceTabs::TopMiddleDocumentArea;` — Where to spawn the widget in the workspace layout - e.g. one of WorkspaceTabs
- L156 _public member_ `FOnGetDocumentBreadcrumbTrail OnGetDocumentBreadcrumbTrail;` — Delegate called to get the bread crumb trail for this document tab
- L159 _public member_ `FEditorModeID DocumentEditorMode = NAME_None;` — EditorMode ID to be associated with this asset, will be used to try and activate matching editor mode when this asset is focused

#### struct `UE::Workspace::FDocumentSubObjectArgs`  
`struct FDocumentSubObjectArgs`  
_L163-171_
- desc: Arguments used to open documents for specific subobject types
- L166 _public member_ `FOnGetDocumentForSubObject OnGetDocumentForSubObject;` — Delegate called to get a document to open for a document's subobject (e.g. a UEdGraphNode could return its containing UEdGraph)
- L170 _public member_ `FOnPostDocumentOpenedForSubObject OnPostDocumentOpenedForSubObject;` — Delegate called after a document is opened to process the supplied subobject (e.g. focus it). The widget supplied is the document widget provided via OnMakeDocumentWidget (or a SGraphEditor for FGraphDocumentWidgetArgs)

#### struct `UE::Workspace::FGraphDocumentWidgetArgs`  
`struct FGraphDocumentWidgetArgs`  
_L196-233_
- desc: Arguments used to make document widgets for graphs
- L199 _public member_ `FName SpawnLocation = WorkspaceTabs::TopMiddleDocumentArea;` — Where to spawn the widget in the workspace layout - e.g. one of WorkspaceTabs
- L201 _public member_ `FOnCreateActionMenu OnCreateActionMenu;`
- L203 _public member_ `FOnNodeTextCommitted OnNodeTextCommitted;`
- L205 _public member_ `FOnCanPerformActionOnSelectedNodes OnCanCutSelectedNodes;`
- L206 _public member_ `FOnPerformActionOnSelectedNodes OnCutSelectedNodes;`
- L208 _public member_ `FOnCanPerformActionOnSelectedNodes OnCanCopySelectedNodes;`
- L209 _public member_ `FOnPerformActionOnSelectedNodes OnCopySelectedNodes;`
- L211 _public member_ `FOnCanPasteNodes OnCanPasteNodes;`
- L212 _public member_ `FOnPasteNodes OnPasteNodes;`
- L214 _public member_ `FOnCanPerformActionOnSelectedNodes OnCanDeleteSelectedNodes;`
- L215 _public member_ `FOnPerformActionOnSelectedNodes OnDeleteSelectedNodes;`
- L217 _public member_ `FOnCanPerformActionOnSelectedNodes OnCanDuplicateSelectedNodes;`
- L218 _public member_ `FOnDuplicateSelectedNodes OnDuplicateSelectedNodes;`
- L220 _public member_ `FOnCanPerformActionOnSelectedNodes OnCanSelectAllNodes;`
- L221 _public member_ `FOnPerformActionOnSelectedNodes OnSelectAllNodes;`
- L223 _public member_ `FOnGraphSelectionChanged OnGraphSelectionChanged;`
- L225 _public member_ `FOnNodeDoubleClicked OnNodeDoubleClicked;`
- L227 _public member_ `FOnGraphDocumentCreated OnGraphDocumentCreated;`
- L229 _public member_ `FOnCanPerformActionOnSelectedNodes OnCanOpenInNewTab;`
- L230 _public member_ `FOnPerformActionOnSelectedNodes OnOpenInNewTab;`
- L232 _public member_ `FOnCreateComment OnCreateComment;`

#### enum `UE::Workspace::EOpenWorkspaceMethod`  
`enum class EOpenWorkspaceMethod : int32`  
_L236-245_
- desc: Enum describing how to open a workspace
- L241 _public enumerator_ `Default` — If the asset is already used in a workspace, open that (if not already opened) If the asset is already used in more than one workspace, let the user choose the workspace to open it in If the asset is not yet in a workspace, create a default workspace, add the asset and open the workspace
- L244 _public enumerator_ `AlwaysOpenNewWorkspace` — Always open a new workspace asset and add the asset to it

#### class `UE::Workspace::IWorkspaceEditorModule`  
`class IWorkspaceEditorModule : public IModuleInterface`  
_L247-295_
- inherits: `IModuleInterface`
- L251 _public prototype_ `virtual IWorkspaceEditor* OpenWorkspaceForObject(UObject* InObject, EOpenWorkspaceMethod InOpenMethod, const TSubclassOf<UWorkspaceFactory> WorkSpaceFactoryClass = UWorkspaceFactory::StaticClass()) = 0;` — Open an object inside a workspace editor.
- L254 _public prototype_ `virtual void RegisterObjectDocumentType(const FTopLevelAssetPath& InClassPath, const FObjectDocumentArgs& InArgs) = 0;` — Register a widget factory method to spawn for a particular class
- L257 _public prototype_ `virtual void UnregisterObjectDocumentType(const FTopLevelAssetPath& InClassPath) = 0;` — Unregister a widget factory method to spawn for a particular class
- L260 _public prototype_ `virtual void RegisterDocumentSubObjectType(const FTopLevelAssetPath& InClassPath, const FDocumentSubObjectArgs& InParams) = 0;` — Register a document subobject - an object that opens in the context of another outer document (e.g. A UEdGraphNode in a UEdGraph)
- L263 _public prototype_ `virtual void UnregisterDocumentSubObjectType(const FTopLevelAssetPath& InClassPath) = 0;` — Unregister a document subobject - an object that opens in the context of another outer document (e.g. A UEdGraphNode in a UEdGraph)
- L266 _public prototype_ `virtual FObjectDocumentArgs CreateGraphDocumentArgs(const FGraphDocumentWidgetArgs& InArgs) = 0;` — Make the required args for a document widget for a UEdGraph
- L269 _public prototype_ `DECLARE_EVENT_TwoParams(IWorkspaceEditorModule, FOnRegisterDetailCustomizations, const TWeakPtr<IWorkspaceEditor>&, TSharedPtr<IDetailsView>&);` — Event to allow registering details customizations
- L270 _public prototype_ `virtual FOnRegisterDetailCustomizations& OnRegisterWorkspaceDetailsCustomization() = 0;`
- L272 _public prototype_ `virtual void RegisterWorkspaceItemDetails(const FOutlinerItemDetailsId& InDetailsId, TSharedPtr<IWorkspaceOutlinerItemDetails> InDetails) = 0;`
- L273 _public prototype_ `virtual void UnregisterWorkspaceItemDetails(const FOutlinerItemDetailsId& InDetailsId) = 0;`
- L276 _public prototype_ `DECLARE_EVENT_ThreeParams(IWorkspaceEditorModule, FOnRegisterTabs, FWorkflowAllowedTabSet& TabFactories, const TSharedRef<FTabManager>&, TSharedPtr<IWorkspaceEditor>);` — Event to allow registering tabs to other elements
- L277 _public prototype_ `virtual FOnRegisterTabs& OnRegisterTabsForEditor() = 0;`
- L280 _public prototype_ `DECLARE_EVENT_TwoParams(IWorkspaceEditorModule, FOnExtendTabs, FLayoutExtender&, TSharedPtr<IWorkspaceEditor>);` — Event to allow extending the layout
- L281 _public prototype_ `virtual FOnExtendTabs& OnExtendTabs() = 0;`
- L284 _public prototype_ `DECLARE_EVENT_TwoParams(IWorkspaceEditorModule, FOnExtendToolMenuContext, TSharedPtr<IWorkspaceEditor>, FToolMenuContext&);` — Event to allow extending the FToolMenuContext
- L285 _public prototype_ `virtual FOnExtendToolMenuContext& OnExtendToolMenuContext() = 0;`
- L287 _public prototype_ `virtual TSharedPtr<IWorkspacePicker> CreateWorkspacePicker(const IWorkspacePicker::FConfig& Config) const = 0;`
- L291 _public prototype_ `virtual void RegisterViewportControllerFactory(const UClass* InClass, const FWorkspaceViewportControllerFactory InControllerFactory) = 0;` — Register a viewport controller factory for a given asset class * Viewport controllers are created per viewport
- L294 _public prototype_ `virtual void UnregisterViewportControllerFactory(const UClass* InClass) = 0;` — Unregister the viewport controller factory for a given asset class

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API WORKSPACEEDITOR_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace Workspace` (scope `UE`)
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Workspace` (scope `UE`)
- L41 _namespace_ `namespace WorkspaceTabs` (scope `UE::Workspace`)
- L43 _externvar_ `extern const FName TopLeftDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L44 _externvar_ `extern const FName BottomLeftDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L45 _externvar_ `extern const FName TopMiddleDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L46 _externvar_ `extern const FName BottomMiddleDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L47 _externvar_ `extern const FName TopRightDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L48 _externvar_ `extern const FName BottomRightDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L49 _externvar_ `extern const FName RightSidebarDocumentArea;` (scope `UE::Workspace::WorkspaceTabs`)
- L102 _typedef_ `using FOnRedirectWorkspaceContext = TDelegate<UObject*(const FWorkspaceDocument&)>;` (scope `UE::Workspace`)
- L104 _typedef_ `using FOnMakeDocumentWidget = TDelegate<TSharedRef<SWidget>(const FWorkspaceEditorContext&)>;` (scope `UE::Workspace`)
- L106 _typedef_ `using FOnGetTabIcon = TDelegate<const FSlateBrush*(const FWorkspaceEditorContext&)>;` (scope `UE::Workspace`)
- L108 _typedef_ `using FOnGetTabName = TDelegate<TAttribute<FText>(const FWorkspaceEditorContext&)>;` (scope `UE::Workspace`)
- L110 _typedef_ `using FOnGetDocumentState = TDelegate<TInstancedStruct<FWorkspaceDocumentState>(const FWorkspaceEditorContext&, TSharedRef<SWidget>)>;` (scope `UE::Workspace`)
- L112 _typedef_ `using FOnSetDocumentState = TDelegate<void(const FWorkspaceEditorContext&, TSharedRef<SWidget>, const TInstancedStruct<FWorkspaceDocumentState>&)>;` (scope `UE::Workspace`)
- L114 _typedef_ `using FOnGetDocumentBreadcrumbTrail = TDelegate<void(const FWorkspaceEditorContext&, TArray<TSharedPtr<FWorkspaceBreadcrumb>>&)>;` (scope `UE::Workspace`)
- L116 _typedef_ `using FOnGetDocumentForSubObject = TDelegate<UObject*(const UObject*)>;` (scope `UE::Workspace`)
- L118 _typedef_ `using FOnPostDocumentOpenedForSubObject = TDelegate<void(const FWorkspaceEditorContext&, TSharedRef<SWidget>, UObject*)>;` (scope `UE::Workspace`)
- L173 _typedef_ `using FOnGraphSelectionChanged = TDelegate<void(const FWorkspaceEditorContext&, const FGraphPanelSelectionSet&)>;` (scope `UE::Workspace`)
- L175 _typedef_ `using FOnCreateActionMenu = TDelegate<FActionMenuContent(const FWorkspaceEditorContext&, UEdGraph*, const FVector2D&, const TArray<UEdGraphPin*>&, bool, SGraphEditor::FActionMenuClosed)>;` (scope `UE::Workspace`)
- L177 _typedef_ `using FOnNodeTextCommitted = TDelegate<void(const FWorkspaceEditorContext&, const FText&, ETextCommit::Type, UEdGraphNode*)>;` (scope `UE::Workspace`)
- L179 _typedef_ `using FOnCanPerformActionOnSelectedNodes = TDelegate<bool(const FWorkspaceEditorContext&, const FGraphPanelSelectionSet&)>;` (scope `UE::Workspace`)
- L180 _typedef_ `using FOnPerformActionOnSelectedNodes = TDelegate<void(const FWorkspaceEditorContext&, const FGraphPanelSelectionSet&)>;` (scope `UE::Workspace`)
- L182 _typedef_ `using FOnCanPasteNodes = TDelegate<bool(const FWorkspaceEditorContext&, const FString&)>;` (scope `UE::Workspace`)
- L183 _typedef_ `using FOnPasteNodes = TDelegate<void(const FWorkspaceEditorContext&, const FVector2D&, const FString&)>;` (scope `UE::Workspace`)
- L185 _typedef_ `using FOnDuplicateSelectedNodes = TDelegate<void(const FWorkspaceEditorContext&, const FVector2D&, const FGraphPanelSelectionSet&)>;` (scope `UE::Workspace`)
- L187 _typedef_ `using FOnGetWorkspaceDetailCustomizationInstance = TDelegate<TSharedRef<IDetailCustomization>(TWeakPtr<IWorkspaceEditor>)>;` (scope `UE::Workspace`)
- L189 _typedef_ `using FOnNodeDoubleClicked = TDelegate<void(const FWorkspaceEditorContext&, const UEdGraphNode* InNode)>;` (scope `UE::Workspace`)
- L191 _typedef_ `using FOnGraphDocumentCreated = TDelegate<void(const FWorkspaceEditorContext&, TSharedPtr<SWidget> InGraphWidget)>;` (scope `UE::Workspace`)
- L193 _typedef_ `using FOnCreateComment = TDelegate<void(const FWorkspaceEditorContext&, const FVector2f&)>;` (scope `UE::Workspace`)
- L269 _delegate_ `DECLARE_EVENT_TwoParams(IWorkspaceEditorModule, FOnRegisterDetailCustomizations, const TWeakPtr<IWorkspaceEditor>&, TSharedPtr<IDetailsView>&);` — Event to allow registering details customizations
- L276 _delegate_ `DECLARE_EVENT_ThreeParams(IWorkspaceEditorModule, FOnRegisterTabs, FWorkflowAllowedTabSet& TabFactories, const TSharedRef<FTabManager>&, TSharedPtr<IWorkspaceEditor>);` — Event to allow registering tabs to other elements
- L280 _delegate_ `DECLARE_EVENT_TwoParams(IWorkspaceEditorModule, FOnExtendTabs, FLayoutExtender&, TSharedPtr<IWorkspaceEditor>);` — Event to allow extending the layout
- L284 _delegate_ `DECLARE_EVENT_TwoParams(IWorkspaceEditorModule, FOnExtendToolMenuContext, TSharedPtr<IWorkspaceEditor>, FToolMenuContext&);` — Event to allow extending the FToolMenuContext

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/IWorkspaceOutlinerItemDetails.h` (Public)


#### class `UE::Workspace::IWorkspaceOutlinerItemDetails`  
`class IWorkspaceOutlinerItemDetails : public TSharedFromThis<IWorkspaceOutlinerItemDetails>`  
_L22-58_
- inherits: `TSharedFromThis<IWorkspaceOutlinerItemDetails>`
- L25 _public prototype_ `virtual ~IWorkspaceOutlinerItemDetails() = default;`
- L26 _public function_ `virtual FString GetDisplayString(const FWorkspaceOutlinerItemExport& Export) const`
- L31 _public function_ `virtual FText GetToolTipText(const FWorkspaceOutlinerItemExport& Export) const`
- L36 _public function_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const`
- L37 _public function_ `virtual FSlateColor GetItemColor(const FWorkspaceOutlinerItemExport& Export) const`
- L38 _public function_ `virtual bool HandleDoubleClick(const FToolMenuContext& ToolMenuContext) const`
- L39 _public function_ `virtual bool CanDelete(const FWorkspaceOutlinerItemExport& Export) const`
- L40 _public function_ `virtual void Delete(TConstArrayView<FWorkspaceOutlinerItemExport> Exports) const`
- L41 _public function_ `virtual bool CanRename(const FWorkspaceOutlinerItemExport& Export) const`
- L42 _public function_ `virtual void Rename(const FWorkspaceOutlinerItemExport& Export, const FText& InName) const`
- L43 _public function_ `virtual bool ValidateName(const FWorkspaceOutlinerItemExport& Export, const FText& InName, FText& OutErrorMessage) const`
- L44 _public function_ `virtual UPackage* GetPackage(const FWorkspaceOutlinerItemExport& Export) const`
- L56 _public function_ `virtual bool HandleSelected(const FToolMenuContext& ToolMenuContext) const`
- L57 _public function_ `virtual bool IsExpandedByDefault() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "IWorkspaceOutlinerItemDetails"`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L16 _typedef_ `typedef FName FOutlinerItemDetailsId;` (scope `UE::Workspace`)
- L17 _function_ `static FOutlinerItemDetailsId MakeOutlinerDetailsId(const FWorkspaceOutlinerItemExport& InExport)` (scope `UE::Workspace`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/IWorkspacePicker.h` (Public)


#### class `UE::Workspace::IWorkspacePicker`  
`class IWorkspacePicker`  
_L12-32_
- L15 _public prototype_ `virtual ~IWorkspacePicker() = default;`
- L29 _public prototype_ `virtual void ShowModal() = 0;`
- L31 _public prototype_ `virtual TObjectPtr<UObject> GetSelectedWorkspace() const = 0;`

#### enum `UE::Workspace::IWorkspacePicker::EHintText`  
`enum class EHintText`  
_L17-21_
- L19 _public enumerator_ `SelectedAssetIsPartOfMultipleWorkspaces`
- L20 _public enumerator_ `CreateOrUseExistingWorkspace`

#### struct `UE::Workspace::IWorkspacePicker::FConfig`  
`struct FConfig`  
_L23-27_
- L25 _public member_ `EHintText HintText = EHintText::SelectedAssetIsPartOfMultipleWorkspaces;`
- L26 _public member_ `TSubclassOf<UWorkspaceFactory> WorkspaceFactoryClass = UWorkspaceFactory::StaticClass();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/SWorkspaceViewport.h` (Public)


#### class `UE::Workspace::SWorkspaceViewport`  
`class SWorkspaceViewport : public SAssetEditorViewport, public ICommonEditorViewportToolbarInfoProvider, public FGCObject`  
_L14-51_
- inherits: `SAssetEditorViewport,ICommonEditorViewportToolbarInfoProvider,FGCObject`
- L17 _public function_ `SLATE_BEGIN_ARGS(SWorkspaceViewport)`
- L18 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FAssetEditorToolkit>, AssetEditorToolkit) SLATE_ARGUMENT(TSharedPtr<FEditorViewportClient>, ViewportClient) SLATE_ARGUMENT(UWorkspaceViewportSceneDescription*, SceneDescription) SLATE_ATTRIBUTE(FSoftObjectPath, PreviewAssetPath) SLATE_ATTRIBUTE(bool, bIsPinned) SLATE_EVENT(FSimpleDelegate, OnPinnedClicked) SLATE_END_ARGS() TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit = nullptr;`
- L28 _public prototype_ `void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;` — SEditorViewport interface
- L32 _public prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L35 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L36 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L37 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L39 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L40 _public function_ `virtual FString GetReferencerName() const override`
- L46 _private member_ `TAttribute<FSoftObjectPath> PreviewAssetPath;`
- L47 _private member_ `TAttribute<bool> bIsPinned;`
- L48 _private member_ `FSimpleDelegate OnPinnedClicked;`
- L50 _private member_ `TObjectPtr<UWorkspaceViewportSceneDescription> SceneDescription;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WORKSPACEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceAssetRegistryInfo.h` (Public)


#### struct `FWorkspaceOutlinerItemData`  
`struct FWorkspaceOutlinerItemData`  
_L10-15_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FWorkspaceOutlinerItemData() = default;`

#### struct `FOutlinerItemPath`  
`struct FOutlinerItemPath`  
_L18-72_
- reflection: `USTRUCT()`
- L25 _protected member_ `TArray<FName> PathSegments;` — `UPROPERTY()`
- L28 _public function_ `static FOutlinerItemPath MakePath(const FSoftObjectPath& InSoftObjectPath)`
- L35 _public function_ `FOutlinerItemPath AppendSegment(const FName& InSegment) const`
- L42 _public function_ `FOutlinerItemPath RemoveSegment() const`

#### struct `FWorkspaceOutlinerItemExport`  
`struct FWorkspaceOutlinerItemExport`  
_L75-384_
- reflection: `USTRUCT()`
- L79 _public prototype_ `FWorkspaceOutlinerItemExport() = default;`
- L81 _public function_ `FWorkspaceOutlinerItemExport(const FName InIdentifier, const FSoftObjectPath& InObjectPath)`
- L87 _public function_ `FWorkspaceOutlinerItemExport(const FName InIdentifier, const FWorkspaceOutlinerItemExport& InParent) : Path(InParent.Path.AppendSegment(InIdentifier))`
- L92 _public function_ `FWorkspaceOutlinerItemExport(const FName InIdentifier, const FWorkspaceOutlinerItemExport& InParent, const TInstancedStruct<FWorkspaceOutlinerItemData>& InData) : Path(InParent.Path.AppendSegment(InIdentifier)) , Data(InData)`
- L98 _public function_ `bool operator==(const FWorkspaceOutlinerItemExport& Other) const`
- L106 _protected member_ `FOutlinerItemPath Path;` — `UPROPERTY()` — Full 'path' to item this instance represents, expected to take form of AssetPath follow by a set of identifier names
- L109 _protected member_ `TInstancedStruct<FWorkspaceOutlinerItemData> Data;` — `UPROPERTY()`
- L111 _public function_ `FName GetIdentifier() const`
- L122 _public function_ `FName GetParentIdentifier() const`
- L135 _public function_ `template<typename AssetClass> AssetClass* GetFirstAssetOfType() const`
- L159 _public function_ `template<typename AssetClass> AssetClass* GetFirstObjectOfType() const`
- L197 _public function_ `FSoftObjectPath GetFirstAssetPath() const` — Returns the first FSoftObjectPath found in segments, starting from the end. e.g. "SoftObjectPath" - "Foo" - "SoftObjectPathTwo" - "Bar" will return SoftObjectPathTwo
- L219 _public function_ `FSoftObjectPath GetFirstValidObjectPath(bool bForceLoad = true) const` — Tries to get the first valid path to an object - taking into account the Identifier might point to a subobject To verify validity, it may try to load the object if bForceLoad == true (default)
- L258 _public function_ `FSoftObjectPath GetTopLevelAssetPath() const` — Returns the first path segment as a FSoftObjectPath. e.g: - "SoftObjectPath" - "Foo" - "SoftObjectPathTwo" - "Bar" will return SoftObjectPath - "Foo" - "SoftObjectPath" - "SoftObjectPathTwo" - "Bar" will return FSoftObjectPath()
- L272 _public function_ `void GetAssetPaths(TArray<FSoftObjectPath>& OutAssetPaths) const` — Returns all valid FSoftObjectPaths found in path segments, starting from the end. e.g: - "SoftObjectPath" - "Foo" - "SoftObjectPathTwo" - "Bar" will return "SoftObjectPathTwo", "SoftObjectPath" - "Foo" - "SoftObjectPath" - "SoftObjectPathTwo" - "Bar" will also return "SoftObjectPathTwo", "SoftObjectPath"
- L290 _public function_ `template<typename AssetClass> void GetAssetsOfType(TArray<AssetClass*>& OutAssets, bool bForceLoad = true) const` — Returns all valid UObject-based assets found, and (optionally) loaded, in path segments, starting from the end. e.g: - "SoftObjectPath" - "Foo" - "SoftObjectPathTwo" - "Bar" will return "SoftObjectPath" and "SoftObjectPathTwo" if their class matches AssetClass
- L313 _public function_ `void GetExports(TArray<FWorkspaceOutlinerItemExport>& OutExports) const` — Returns all valid FWorkspaceOutlinerItemExports found in path segments, starting from the end. e.g: - "SoftObjectPath" - "Foo" - "SoftObjectPathTwo" - "Bar" will return "SoftObjectPath" - "Bar" , "SoftObjectPathTwo" - "Foo"
- L335 _public function_ `FWorkspaceOutlinerItemExport GetRelativeAssetExport(const FSoftObjectPath& InAssetPath) const` — Returns relative export to the provided InAssetPath - "SoftObjectPath" - "Foo" - "SoftObjectPathTwo" - "Bar" will return "SoftObjectPath" - "Foo" when passed "SoftObjectPathTwo" or an empty export when passed "SoftObjectPath"
- L356 _public function_ `FString GetFullPath() const`
- L368 _public function_ `uint32 GetParentHash() const` — Remove identifier segment to retrieve parent path hash
- L371 _public function_ `bool HasData() const` — Returns whether Data has any instanced struct setup
- L373 _public function_ `const TInstancedStruct<FWorkspaceOutlinerItemData>& GetData() const`
- L374 _public function_ `TInstancedStruct<FWorkspaceOutlinerItemData>& GetData()`
- L382 _public prototype_ `FWorkspaceOutlinerItemExport& GetResolvedExport();` — Returns the inner ReferredExport from the item data only valid for asset references, otherwise will return *this
- L383 _public prototype_ `const FWorkspaceOutlinerItemExport& GetResolvedExport() const;`

#### struct `FWorkspaceOutlinerAssetReferenceItemData`  
`struct FWorkspaceOutlinerAssetReferenceItemData : public FWorkspaceOutlinerItemData`  
_L387-410_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- L391 _public prototype_ `FWorkspaceOutlinerAssetReferenceItemData() = default;`
- L394 _public member_ `FSoftObjectPath ReferredObjectPath;` — `UPROPERTY()`
- L397 _public member_ `FWorkspaceOutlinerItemExport ReferredExport;` — `UPROPERTY()`
- L401 _public member_ `bool bShouldExpandReference = true;` — `UPROPERTY()` — Whether this asset reference should be expanded in the Workspace outliner
- L404 _public member_ `bool bRecursiveReference = false;` — `UPROPERTY()`
- L406 _public function_ `static bool IsAssetReference(const FWorkspaceOutlinerItemExport& InExport)`

#### struct `FWorkspaceOutlinerGroupItemData`  
`struct FWorkspaceOutlinerGroupItemData : public FWorkspaceOutlinerItemData`  
_L413-429_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- L417 _public prototype_ `FWorkspaceOutlinerGroupItemData() = default;`
- L420 _public member_ `FString GroupName;` — `UPROPERTY()`
- L423 _public member_ `FSlateBrush GroupIcon;` — `UPROPERTY()`
- L425 _public function_ `static bool IsGroupItem(const FWorkspaceOutlinerItemExport& InExport)`

#### struct `FWorkspaceOutlinerItemExports`  
`struct FWorkspaceOutlinerItemExports`  
_L439-447_
- reflection: `USTRUCT()`
- L443 _public prototype_ `FWorkspaceOutlinerItemExports() = default;`
- L446 _public member_ `TArray<FWorkspaceOutlinerItemExport> Exports;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L52 _function_ `friend uint32 GetTypeHash(const FOutlinerItemPath& Path)`
- L376 _function_ `friend uint32 GetTypeHash(const FWorkspaceOutlinerItemExport& Export)`
- L431 _namespace_ `namespace UE`
- L431 _namespace_ `namespace Workspace` (scope `UE`)
- L434 _variable_ `static const FLazyName ExportsWorkspaceItemsRegistryTag = TEXT("Wor` (scope `UE::Workspace`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceDocumentState.h` (Public)


#### struct `FWorkspaceDocumentState`  
`struct FWorkspaceDocumentState`  
_L10-31_
- reflection: `USTRUCT()`
- desc: Base struct used to persist workspace document state
- L14 _public prototype_ `FWorkspaceDocumentState() = default;`
- L16 _public function_ `explicit FWorkspaceDocumentState(const UObject* InObject, const FWorkspaceOutlinerItemExport& InExport) : Object(InObject), Export(InExport)`
- L21 _public member_ `FSoftObjectPath Object;` — `UPROPERTY()`
- L25 _public member_ `FWorkspaceOutlinerItemExport Export;` — `UPROPERTY()` — Export provided when opening object

#### Free symbols / members of external scopes

- L27 _function_ `friend bool operator==(const FWorkspaceDocumentState& LHS, const FWorkspaceDocumentState& RHS)`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceDragDropOperation.h` (Public)


#### class `FWorkspaceDragDropOp`  
`class FWorkspaceDragDropOp : public FDecoratedDragDropOp`  
_L11-39_
- inherits: `FDecoratedDragDropOp`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FWorkspaceDragDropOp, FDecoratedDragDropOp) TArray<FAssetData> AssetDatas;`
- L19 _public function_ `void Init(const TArray<FAssetData>& InAssetDatas)`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceFactory.h` (Public)


#### class `UWorkspaceFactory`  
`class UWorkspaceFactory : public UFactory`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UFactory`
- L26 _protected prototype_ `UWorkspaceFactory();`
- L29 _protected function_ `void SetSchemaClass(TSubclassOf<UWorkspaceSchema> InSchemaClass)` — Set the schema class for workspaces produced with this factory
- L32 _private prototype_ `virtual bool ConfigureProperties() override;`
- L33 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L34 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`
- L40 _private member_ `TSubclassOf<UWorkspaceSchema> SchemaClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WORKSPACEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceItemMenuContext.h` (Public)


#### class `UWorkspaceItemMenuContext`  
`class UWorkspaceItemMenuContext : public UObject`  
_L13-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public member_ `TArray<FWorkspaceOutlinerItemExport> SelectedExports;`
- L18 _public member_ `TArray<FSceneOutlinerTreeItemPtr> SelectedItems;`
- L19 _public member_ `TWeakPtr<FUICommandList> WeakCommandList;`

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceSchema.h` (Public)


#### class `UWorkspaceSchema`  
`class UWorkspaceSchema : public UObject`  
_L19-50_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Workspace schema to configure workspace assets to specific use cases
- L25 _public function_ `virtual FText GetDisplayName() const PURE_VIRTUAL(UWorkspaceSchema::GetDisplayName, return FText::GetEmpty(); )` — Get the name to display for workspace assets that use this schema
- L34 _public function_ `virtual void OnLoadWorkspaceState(TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor, const FInstancedStruct& InWorkspaceState) const` — Called after loading workspace state. InWorkspaceState is an instanced struct that holds user-defined persistent workspace state. Struct is not guaranteed to be valid.
- L37 _public function_ `virtual bool SupportsViewport() const` — Whether workspaces using this schema can spawn viewport tabs.
- L40 _public function_ `virtual TObjectPtr<UWorkspaceViewportSceneDescription> CreateSceneDescription() const` — Create a new object containing the required data to construct a scene for this type of workspace
- L43 _public function_ `virtual bool SupportsMultipleAssets() const` — Whether workspaces using this schema can add more assets to the workspace besides the root-level asset
- L46 _public function_ `virtual bool HasPersistentRootAsset() const` — Whether workspaces using this schema has a root-level asset that always exists in the workspace
- L49 _public function_ `virtual bool CanSaveWorkspace() const` — Whether workspaces using this schema can be saved as an asset

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceTabPayload.h` (Public)


#### struct `UE::Workspace::FTabPayload_WorkspaceDocument`  
`struct FTabPayload_WorkspaceDocument : FTabPayload`  
_L11-72_
- inherits: `FTabPayload`
- L13 _public member_ `static const FName DocumentPayloadName;`
- L15 _public function_ `static TSharedRef<FTabPayload_WorkspaceDocument> Make(const UObject* DocumentID, const FWorkspaceOutlinerItemExport& InExport)`
- L21 _public function_ `static TSharedRef<FTabPayload_WorkspaceDocument> Make(const UObject* DocumentID)`
- L27 _public function_ `template <typename CastType> static CastType* CastChecked(TSharedRef<FTabPayload> Payload)`
- L35 _public function_ `static const FWorkspaceOutlinerItemExport& GetExport(const TSharedRef<FTabPayload> Payload)`
- L42 _public function_ `virtual bool IsEqual(const TSharedRef<FTabPayload>& OtherPayload) const override` — Determine if another payload is the same as this one
- L54 _public function_ `virtual bool IsValid() const override`
- L59 _public function_ `virtual ~FTabPayload_WorkspaceDocument() override`
- L62 _private function_ `FTabPayload_WorkspaceDocument(UObject* InDocumentID, const FWorkspaceOutlinerItemExport& InExport) : FTabPayload(DocumentPayloadName) , DocumentID(InDocumentID) , Export(InExport)`
- L70 _private member_ `TWeakObjectPtr<UObject> DocumentID;`
- L71 _private member_ `FWorkspaceOutlinerItemExport Export;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceViewportController.h` (Public)


#### class `UE::Workspace::IWorkspaceViewportController`  
`class IWorkspaceViewportController`  
_L14-37_
- L17 _public prototype_ `virtual ~IWorkspaceViewportController() = default;`
- L35 _public prototype_ `virtual void OnEnter(const FViewportContext& InContext) = 0;`
- L36 _public prototype_ `virtual void OnExit(FAdvancedPreviewScene* PreviewScene) = 0;`

#### class `UE::Workspace::IWorkspaceViewportController::FViewportContext`  
`class FViewportContext : public FGCObject`  
_L19-33_
- inherits: `FGCObject`
- L22 _public member_ `FAdvancedPreviewScene* PreviewScene;`
- L23 _public member_ `TObjectPtr<UObject> OutlinerObject;`
- L24 _public member_ `TObjectPtr<UWorkspaceViewportSceneDescription> SceneDescription;`
- L27 _public function_ `virtual FString GetReferencerName() const override` — FGCObject interface
- L28 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)
- L39 _typedef_ `using FWorkspaceViewportControllerFactory = TFunctionRef<TUniquePtr<IWorkspaceViewportController>()>;` (scope `UE::Workspace`)

### `Plugins/Experimental/Workspace/Source/WorkspaceEditor/Public/WorkspaceViewportSceneDescription.h` (Public)


#### class `UWorkspaceViewportSceneDescription`  
`class UWorkspaceViewportSceneDescription : public UObject`  
_L12-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public prototype_ `FSimpleMulticastDelegate& GetOnConfigChanged();`
- L20 _protected prototype_ `void BroadcastOnConfigChanged();`
- L23 _private member_ `FSimpleMulticastDelegate OnConfigChanged;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WORKSPACEEDITOR_API`
