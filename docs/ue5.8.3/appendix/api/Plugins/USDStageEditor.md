# Plugins / USDStageEditor

- module root: `Plugins/Importers/USDImporter/Source/USDStageEditor`
- headers: 14; symbols: 381
- symbol kinds: class=18, delegate=4, enum=2, enumerator=7, function=16, macro=1, member=76, namespace=5, prototype=249, struct=1, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, DesktopWidgets, EditorFramework, Engine, InputCore, LevelEditor, LevelSequence, LiveLinkEditor, LiveLinkInterface, Projects, SceneOutliner, Slate, SlateCore, USDClasses, USDSchemas, USDStage, USDStageEditorViewModels, USDStageImporter, USDUtilities, UnrealEd, UnrealUSDWrapper, WorkspaceMenuStructure

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/SUSDLayersTreeView.h` (Private)


#### class `SUsdLayersTreeView`  
`class SUsdLayersTreeView : public SUsdTreeView<FUsdLayerViewModelRef>`  
_L19-114_
- inherits: `SUsdTreeView<FUsdLayerViewModelRef>`
- L22 _public function_ `SLATE_BEGIN_ARGS(SUsdLayersTreeView)`
- L25 _public prototype_ `SLATE_EVENT(FOnLayerIsolated, OnLayerIsolated) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void Refresh(const UE::FUsdStageWeak& NewStage, const UE::FUsdStageWeak& IsolatedStage = {}, bool bResync = false);`
- L32 _public prototype_ `FReply OnRowDragDetected(const FGeometry& Geometry, const FPointerEvent& PointerEvent);` — Drag and drop interface for our rows
- L33 _public prototype_ `void OnRowDragLeave(const FDragDropEvent& Event);`
- L34 _public prototype_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& Event, EItemDropZone Zone, FUsdLayerViewModelRef Item);`
- L35 _public prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& Event, EItemDropZone Zone, FUsdLayerViewModelRef Item);`
- L38 _public prototype_ `TArray<UE::FSdfLayer> GetSelectedLayers() const;`
- L39 _public prototype_ `void SetSelectedLayers(const TArray<UE::FSdfLayer>& NewSelection);`
- L41 _public prototype_ `void ExportSelectedLayers(const FString& OutputDirectory = {}) const;`
- L43 _public function_ `const UE::FUsdStageWeak& GetStage() const`
- L49 _private prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(FUsdLayerViewModelRef InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L50 _private prototype_ `virtual void OnGetChildren(FUsdLayerViewModelRef InParent, TArray<FUsdLayerViewModelRef>& OutChildren) const override;`
- L52 _private prototype_ `virtual void SetupColumns() override;`
- L54 _private prototype_ `void BuildUsdLayersEntries();`
- L56 _private prototype_ `TSharedPtr<SWidget> ConstructLayerContextMenu();`
- L58 _private prototype_ `bool CanIsolateSelectedLayer() const;`
- L59 _private prototype_ `void OnIsolateSelectedLayer();`
- L61 _private prototype_ `bool CanEditSelectedLayer() const;`
- L62 _private prototype_ `void OnEditSelectedLayer();`
- L64 _private prototype_ `bool CanMuteSelectedLayer() const;`
- L65 _private prototype_ `void OnMuteSelectedLayer();`
- L67 _private prototype_ `void OnClearSelectedLayers();`
- L68 _private prototype_ `bool CanClearSelectedLayers() const;`
- L70 _private prototype_ `void OnReloadSelectedLayers();`
- L71 _private prototype_ `bool CanReloadSelectedLayers() const;`
- L73 _private prototype_ `void OnSaveSelectedLayers();`
- L74 _private prototype_ `bool CanSaveSelectedLayers() const;`
- L76 _private prototype_ `bool CanInsertSubLayer() const;`
- L77 _private prototype_ `void OnAddSubLayer();`
- L78 _private prototype_ `void OnNewSubLayer();`
- L80 _private prototype_ `bool CanRemoveLayer(FUsdLayerViewModelRef LayerItem) const;`
- L81 _private prototype_ `bool CanRemoveSelectedLayers() const;`
- L82 _private prototype_ `void OnRemoveSelectedLayers();`
- L84 _private prototype_ `void RestoreExpansionStates();`
- L96 _public member_ `ELayersTreeViewState bUpdateState = ELayersTreeViewState::NoRefreshNeeded;`
- L100 _public member_ `mutable FRWLock RefreshStateLock;` — Use a lock because some of the notices that will update these refresh variables can be sent from TBB threads
- L104 _private member_ `UE::FUsdStageWeak UsdStage;` — Should always be valid, we keep the one we're given on Refresh()
- L107 _private member_ `UE::FUsdStageWeak IsolatedStage;` — A stage we create based on one of the sublayers of UsdStage
- L110 _private member_ `TMap<FString, bool> TreeItemExpansionStates;` — So that we can store these across refreshes
- L113 _private member_ `FOnLayerIsolated LayerIsolatedDelegate;` — Used so that we can isolate the new layer without coupling to the SUSDStage widget too much

#### enum `SUsdLayersTreeView::ELayersTreeViewState`  
`enum class ELayersTreeViewState : uint8`  
_L90-95_
- L92 _public enumerator_ `NoRefreshNeeded = 0`
- L93 _public enumerator_ `RefreshNeeded = 1`
- L94 _public enumerator_ `ResyncNeeded = 2`

#### Free symbols / members of external scopes

- L14 _typedef_ `using FUsdLayerViewModelRef = TSharedRef<class FUsdLayerViewModel>;`
- L15 _typedef_ `using FUsdLayerViewModelWeak = TWeakPtr<class FUsdLayerViewModel>;`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLayerIsolated, const UE::FSdfLayer&);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLayerIsolated, const UE::FSdfLayer&);`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/SUSDPrimInfo.h` (Private)


#### class `SUsdPrimInfo`  
`class SUsdPrimInfo : public SCompoundWidget`  
_L12-30_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SUsdPrimInfo)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetPrimPath(const UE::FUsdStageWeak& UsdStage, const TCHAR* PrimPath);`
- L25 _private member_ `TSharedPtr<class SUsdObjectFieldList> PropertiesList;`
- L26 _private member_ `TSharedPtr<class SUsdObjectFieldList> PropertyMetadataPanel;`
- L27 _private member_ `TSharedPtr<class SUsdIntegrationsPanel> IntegrationsPanel;`
- L28 _private member_ `TSharedPtr<class SVariantsList> VariantsList;`
- L29 _private member_ `TSharedPtr<class SUsdReferencesList> ReferencesList;`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/SUSDSaveDialog.h` (Private)


#### struct `FUsdSaveDialogRowData`  
`struct FUsdSaveDialogRowData`  
_L16-22_
- L18 _public member_ `bool bSaveLayer = true;`
- L19 _public member_ `UE::FSdfLayerWeak Layer;`
- L20 _public member_ `TArray<UE::FUsdStageWeak> ConsumerStages;`
- L21 _public member_ `TSet<AUsdStageActor*> ConsumerActors;`

#### class `SUsdSaveDialog`  
`class SUsdSaveDialog : public SCompoundWidget`  
_L25-69_
- inherits: `SCompoundWidget`
- desc: Dialog shown to ask if the user wishes to save any dirty USD layer to disk
- L28 _public function_ `SLATE_BEGIN_ARGS(SUsdSaveDialog)`
- L31 _public prototype_ `SLATE_ARGUMENT(TArray<FUsdSaveDialogRowData>, Rows) SLATE_ARGUMENT(FText, DescriptionText) SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow) SLATE_END_ARGS()`
- L45 _public prototype_ `void Construct(const FArguments& InArgs);`
- L46 _public function_ `bool ShouldSave() const`
- L50 _public function_ `bool ShouldPromptAgain() const`
- L56 _private prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L57 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L59 _private prototype_ `TSharedRef<ITableRow> OnGenerateListRow(TSharedPtr<FUsdSaveDialogRowData> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L61 _private prototype_ `FReply Close(bool bProceed);`
- L64 _private member_ `TWeakPtr<SWindow> Window;`
- L65 _private member_ `TArray<TSharedPtr<FUsdSaveDialogRowData>> Rows;`
- L67 _private member_ `bool bPromptAgain = true;`
- L68 _private member_ `bool bProceed = false;`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/SUSDStage.h` (Private)


#### class `SUsdStage`  
`class SUsdStage : public SCompoundWidget`  
_L30-184_
- inherits: `SCompoundWidget`
- L32 _private function_ `SLATE_BEGIN_ARGS(SUsdStage)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `virtual ~SUsdStage();`
- L45 _public prototype_ `void AttachToStageActor(AUsdStageActor* InUsdStageActor, bool bFlashButton = true);` — Attaches to a new stage actor. When bFlashButton is true we will also blink the button on the UI to draw attention to the fact that the actor changed
- L47 _public prototype_ `AUsdStageActor* GetAttachedStageActor() const;`
- L49 _public prototype_ `TArray<UE::FSdfLayer> GetSelectedLayers() const;`
- L50 _public prototype_ `void SetSelectedLayers(const TArray<UE::FSdfLayer>& NewSelection) const;`
- L52 _public prototype_ `TArray<UE::FUsdPrim> GetSelectedPrims() const;`
- L53 _public prototype_ `void SetSelectedPrims(const TArray<UE::FUsdPrim>& NewSelection) const;`
- L55 _public prototype_ `TArray<FString> GetSelectedPropertyNames() const;`
- L56 _public prototype_ `void SetSelectedPropertyNames(const TArray<FString>& NewSelection);`
- L58 _public prototype_ `TArray<FString> GetSelectedPropertyMetadataNames() const;`
- L59 _public prototype_ `void SetSelectedPropertyMetadataNames(const TArray<FString>& NewSelection);`
- L64 _public prototype_ `void FileNew();` — Main menu actions. For all of these, providing an empty path will cause us to pop open a dialog to let the user pick the path instead.
- L65 _public prototype_ `void FileOpen(const FString& FilePath = {});`
- L66 _public prototype_ `void FileSave(const FString& OutputFileIfUnsaved = {});`
- L67 _public prototype_ `void FileExportAllLayers(const FString& OutputDirectory = {});`
- L68 _public prototype_ `void FileExportFlattenedStage(const FString& OutputLayer = {});`
- L69 _public prototype_ `void FileExportFlattenedLayerStack(const FString& OutputLayer = {});`
- L70 _public prototype_ `void FileReload();`
- L71 _public prototype_ `void FileReset();`
- L72 _public prototype_ `void FileClose();`
- L73 _public prototype_ `void ActionsImportWithDialog();`
- L74 _public prototype_ `void ActionsImport(const FString& OutputContentFolder, UUsdStageImportOptions* Options);`
- L75 _public prototype_ `void ActionsRegenerate();`
- L76 _public prototype_ `void ActionsSelectStageActor();`
- L77 _public prototype_ `void ActionsOpenLevelSequence();`
- L78 _public prototype_ `void ExportSelectedLayers(const FString& OutputLayerOrDirectory = {});`
- L81 _protected prototype_ `void SetupStageActorDelegates();`
- L82 _protected prototype_ `void ClearStageActorDelegates();`
- L84 _protected prototype_ `TSharedRef<SWidget> MakeMainMenu();`
- L85 _protected prototype_ `TSharedRef<SWidget> MakeActorPickerMenu();`
- L86 _protected prototype_ `TSharedRef<SWidget> MakeActorPickerMenuContent();`
- L87 _protected prototype_ `TSharedRef<SWidget> MakeIsolateWarningButton();`
- L88 _protected prototype_ `void FillFileMenu(FMenuBuilder& MenuBuilder);`
- L89 _protected prototype_ `void FillActionsMenu(FMenuBuilder& MenuBuilder);`
- L90 _protected prototype_ `void FillOptionsMenu(FMenuBuilder& MenuBuilder);`
- L91 _protected prototype_ `void FillExportSubMenu(FMenuBuilder& MenuBuilder);`
- L92 _protected prototype_ `void FillStageStateSubMenu(FMenuBuilder& MenuBuilder);`
- L93 _protected prototype_ `void FillPayloadsSubMenu(FMenuBuilder& MenuBuilder);`
- L94 _protected prototype_ `void FillPurposesToLoadSubMenu(FMenuBuilder& MenuBuilder);`
- L95 _protected prototype_ `void FillRenderContextSubMenu(FMenuBuilder& MenuBuilder);`
- L96 _protected prototype_ `void FillMaterialPurposeSubMenu(FMenuBuilder& MenuBuilder);`
- L97 _protected prototype_ `void FillRootMotionSubMenu(FMenuBuilder& MenuBuilder);`
- L98 _protected prototype_ `void FillFallbackCollisionTypeMenu(FMenuBuilder& MenuBuilder);`
- L99 _protected prototype_ `void FillSubdivisionLevelSubMenu(FMenuBuilder& MenuBuilder);`
- L100 _protected prototype_ `void FillMetadataSubMenu(FMenuBuilder& MenuBuilder);`
- L101 _protected prototype_ `void FillCollapsingSubMenu(FMenuBuilder& MenuBuilder);`
- L102 _protected prototype_ `void FillShareAssetsSubMenu(FMenuBuilder& MenuBuilder);`
- L103 _protected prototype_ `void FillInterpolationTypeSubMenu(FMenuBuilder& MenuBuilder);`
- L104 _protected prototype_ `void FillSelectionSubMenu(FMenuBuilder& MenuBuilder);`
- L105 _protected prototype_ `void FillNaniteThresholdSubMenu(FMenuBuilder& MenuBuilder);`
- L106 _protected prototype_ `void FillGeometryCacheImportSubMenu(FMenuBuilder& MenuBuilder);`
- L108 _protected prototype_ `void OnLayerIsolated(const UE::FSdfLayer& IsolatedLayer);`
- L110 _protected prototype_ `void OnPrimSelectionChanged(const TArray<FString>& PrimPath);`
- L112 _protected prototype_ `void OpenStage(const TCHAR* FilePath);`
- L114 _protected prototype_ `void RequestLayersTreeViewRefresh();`
- L115 _protected prototype_ `void RequestFullRefresh();`
- L116 _protected prototype_ `void OnSlateTick(float Time);`
- L118 _protected prototype_ `void OnViewportSelectionChanged(UObject* NewSelection);`
- L120 _protected prototype_ `void OnPostPIEStarted(bool bIsSimulating);`
- L121 _protected prototype_ `void OnEndPIE(bool bIsSimulating);`
- L123 _protected prototype_ `int32 GetNaniteTriangleThresholdValue() const;`
- L124 _protected prototype_ `void OnNaniteTriangleThresholdValueChanged(int32 InValue);`
- L125 _protected prototype_ `void OnNaniteTriangleThresholdValueCommitted(int32 InValue, ETextCommit::Type InCommitType);`
- L127 _protected prototype_ `int32 GetSubdivisionLevelValue() const;`
- L128 _protected prototype_ `void OnSubdivisionLevelValueChanged(int32 InValue);`
- L129 _protected prototype_ `void OnSubdivisionLevelValueCommitted(int32 InValue, ETextCommit::Type InCommitType);`
- L131 _protected prototype_ `UE::FUsdStageWeak GetCurrentStage() const;`
- L133 _protected prototype_ `AUsdStageActor* GetStageActorOrCDO() const;`
- L136 _protected member_ `TSharedPtr<class SUsdStageTreeView> UsdStageTreeView;`
- L137 _protected member_ `TSharedPtr<class SUsdPrimInfo> UsdPrimInfoWidget;`
- L138 _protected member_ `TSharedPtr<class SUsdLayersTreeView> UsdLayersTreeView;`
- L140 _protected member_ `FDelegateHandle OnActorLoadedHandle;`
- L141 _protected member_ `FDelegateHandle OnActorDestroyedHandle;`
- L142 _protected member_ `FDelegateHandle OnStageActorPropertyChangedHandle;`
- L143 _protected member_ `FDelegateHandle OnStageChangedHandle;`
- L144 _protected member_ `FDelegateHandle OnStageEditTargetChangedHandle;`
- L145 _protected member_ `FDelegateHandle OnPrimChangedHandle;`
- L146 _protected member_ `FDelegateHandle OnSdfLayersChangedHandle;`
- L147 _protected member_ `FDelegateHandle OnSdfLayerDirtinessChangedHandle;`
- L148 _protected member_ `FDelegateHandle OnViewportSelectionChangedHandle;`
- L149 _protected member_ `FDelegateHandle PostPIEStartedHandle;`
- L150 _protected member_ `FDelegateHandle EndPIEHandle;`
- L152 _protected member_ `FString SelectedPrimPath;`
- L154 _protected member_ `FUsdStageViewModel ViewModel;`
- L156 _protected member_ `FCurveSequence FlashActorPickerCurve;`
- L159 _protected member_ `bool bUpdatingViewportSelection;` — True while we're in the middle of setting the viewport selection from the prim selection
- L162 _protected member_ `bool bUpdatingPrimSelection;` — True while we're in the middle of updating the prim selection from the viewport selection
- L167 _protected member_ `TSharedPtr<ISceneOutliner> ActorPickerMenu;` — We keep this menu alive instead of recreating it every time because it doesn't expose setting/getting/responding to the picked world, which resets every time it is reconstructed (see UE-127879) By keeping it alive it will keep its own state and we just do a full refresh when needed
- L169 _protected member_ `int32 CurrentNaniteThreshold = INT32_MAX;`
- L171 _protected member_ `int32 CurrentSubdivisionLevel = 0;`
- L173 _protected member_ `TArray<TSharedPtr<FString>> MaterialPurposes;`
- L182 _protected member_ `bool bEditorIsShuttingDown = false;` — We use our own bool to track engine exit because we use some tickers to delay work onto the next frame, and during engine shutdown its possible for this delayed work to run *before* IsEngineExitRequested() actually turns true, so we can't check it. If that work continues (and triggers its slate updates and so on), we can run into crashes as we're trying to render slate as the engine shuts down. This bool is set on GEditor->OnEditorClose(), which happens earlier in the shutdown process, and can be used to let our ticker lambdas gracefully early out during those shutdown scenarios.
- L183 _protected member_ `FDelegateHandle OnEditorCloseHandle;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/SUSDStageEditorStyle.h` (Private)


#### class `FUsdStageEditorStyle`  
`class FUsdStageEditorStyle`  
_L9-24_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L17 _public prototype_ `static FName GetStyleSetName();`
- L20 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L23 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/SUSDStageTreeView.h` (Private)


#### class `SUsdStageTreeView`  
`class SUsdStageTreeView : public SUsdTreeView<FUsdPrimViewModelRef>`  
_L28-144_
- inherits: `SUsdTreeView<FUsdPrimViewModelRef>`
- L31 _public function_ `SLATE_BEGIN_ARGS(SUsdStageTreeView)`
- L34 _public prototype_ `SLATE_EVENT(FOnPrimSelectionChanged, OnPrimSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `void Refresh(const UE::FUsdStageWeak& NewStage);`
- L41 _public prototype_ `void RefreshPrim(const FString& PrimPath, bool bResync);`
- L43 _public prototype_ `FUsdPrimViewModelPtr GetItemFromPrimPath(const FString& PrimPath);`
- L45 _public prototype_ `void SetSelectedPrimPaths(const TArray<FString>& PrimPaths);`
- L46 _public prototype_ `void SetSelectedPrims(const TArray<UE::FUsdPrim>& Prims);`
- L47 _public prototype_ `TArray<FString> GetSelectedPrimPaths();`
- L48 _public prototype_ `TArray<UE::FUsdPrim> GetSelectedPrims();`
- L51 _private prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(FUsdPrimViewModelRef InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L52 _private prototype_ `virtual void OnGetChildren(FUsdPrimViewModelRef InParent, TArray<FUsdPrimViewModelRef>& OutChildren) const override;`
- L55 _private function_ `virtual bool SupportsKeyboardFocus() const override` — Required so that we can use the cut/copy/paste/etc. shortcuts
- L59 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L61 _private prototype_ `void ScrollItemIntoView(FUsdPrimViewModelRef TreeItem);`
- L62 _private prototype_ `virtual void OnTreeItemScrolledIntoView(FUsdPrimViewModelRef TreeItem, const TSharedPtr<ITableRow>& Widget) override;`
- L64 _private prototype_ `void OnPrimNameCommitted(const FUsdPrimViewModelRef& TreeItem, const FText& InPrimName);`
- L65 _private prototype_ `void OnPrimNameUpdated(const FUsdPrimViewModelRef& TreeItem, const FText& InPrimName, FText& ErrorMessage);`
- L67 _private prototype_ `virtual void SetupColumns() override;`
- L68 _private prototype_ `TSharedPtr<SWidget> ConstructPrimContextMenu();`
- L70 _private prototype_ `void OnToggleAllPayloads(EPayloadsTrigger PayloadsTrigger);`
- L72 _private prototype_ `void FillDuplicateSubmenu(FMenuBuilder& MenuBuilder);`
- L73 _private prototype_ `void FillCollapsingSubmenu(FMenuBuilder& MenuBuilder);`
- L74 _private prototype_ `void FillAddSchemaSubmenu(FMenuBuilder& MenuBuilder);`
- L75 _private prototype_ `void FillRemoveSchemaSubmenu(FMenuBuilder& MenuBuilder);`
- L77 _private prototype_ `void OnAddChildPrim();`
- L78 _private prototype_ `void OnCutPrim();`
- L79 _private prototype_ `void OnCopyPrim();`
- L80 _private prototype_ `void OnPastePrim();`
- L81 _private prototype_ `void OnDuplicatePrim(EUsdDuplicateType DuplicateType);`
- L82 _private prototype_ `void OnDeletePrim();`
- L83 _private prototype_ `void OnRenamePrim();`
- L84 _private prototype_ `void OnSetCollapsingPreference(UsdUtils::ECollapsingPreference Preference);`
- L86 _private prototype_ `void OnAddReference();`
- L87 _private prototype_ `void OnClearReferences();`
- L89 _private prototype_ `void OnAddPayload();`
- L90 _private prototype_ `void OnClearPayloads();`
- L92 _private prototype_ `void OnApplySchema(FName SchemaName);`
- L93 _private prototype_ `void OnRemoveSchema(FName SchemaName);`
- L94 _private prototype_ `bool CanApplySchema(FName SchemaName);`
- L95 _private prototype_ `bool CanRemoveSchema(FName SchemaName);`
- L97 _private prototype_ `bool CanAddChildPrim() const;`
- L98 _private prototype_ `bool CanPastePrim() const;`
- L99 _private prototype_ `bool DoesPrimExistOnStage() const;`
- L100 _private prototype_ `bool DoesPrimExistOnEditTarget() const;`
- L101 _private prototype_ `bool DoesPrimHaveSpecOnLocalLayerStack() const;`
- L102 _private prototype_ `bool DoesPrimHaveReferenceSpecOnLocalLayerStack() const;`
- L103 _private prototype_ `bool DoesPrimHavePayloadSpecOnLocalLayerStack() const;`
- L104 _private prototype_ `bool DoSelectedPrimsHaveCollapsingPreference(UsdUtils::ECollapsingPreference Preference) const;`
- L106 _private prototype_ `void RequestExpansionStateRestore();`
- L107 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L109 _private prototype_ `void SelectItemsInternal(const TArray<FUsdPrimViewModelRef>& ItemsToSelect);`
- L115 _public member_ `FString PrimPathToSelect;`
- L117 _public member_ `bool bNeedsFullUpdate = false;`
- L122 _public member_ `TArray<TPair<FString, bool>> PrimsToRefresh;` — We append requests to refresh prims on the stage tree view to the end of this array as they arrive, and then perform them all at once during OnSlateTick. Elements map from prim path to whether the update neeeds to be a resync or not.
- L126 _public member_ `mutable FRWLock RefreshStateLock;` — Use a lock because some of the notices that will update these refresh variables can be sent from TBB threads
- L130 _private member_ `UE::FUsdStageWeak UsdStage;` — Should always be valid, we keep the one we're given on Refresh()
- L132 _private member_ `TWeakPtr<FUsdPrimViewModel> PendingRenameItem;`
- L135 _private member_ `UsdUtils::FCaseSensitiveStringSet ExpandedPrimPaths;` — So that we can store these across refreshes
- L136 _private member_ `TOptional<bool> RootWasExpanded;`
- L137 _private member_ `bool bNeedExpansionStateRefresh = false;`
- L139 _private member_ `FOnPrimSelectionChanged OnPrimSelectionChanged;`
- L141 _private member_ `FDelegateHandle PostUndoRedoHandle;`
- L143 _private member_ `TSharedPtr<FUICommandList> UICommandList;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UsdUtils`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPrimSelectionChanged, const TArray<FString>& );`
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPrimSelectionChanged, const TArray<FString>& );`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAddPrim, FString);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAddPrim, FString);`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/USDDragDropOp.h` (Private)


#### enum `EUsdDragDropOpType`  
`enum class EUsdDragDropOpType`  
_L8-14_
- L10 _public enumerator_ `None`
- L11 _public enumerator_ `Prims`
- L12 _public enumerator_ `Layers`
- L13 _public enumerator_ `Attributes`

#### class `FUsdDragDropOp`  
`class FUsdDragDropOp : public FDecoratedDragDropOp`  
_L16-23_
- inherits: `FDecoratedDragDropOp`
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FUsdDragDropOp, FDecoratedDragDropOp) EUsdDragDropOpType OpType;`
- L22 _public member_ `TSet<TSharedRef<IUsdTreeViewItem>> DraggedItems;`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/USDStageEditorSettings.h` (Private)


#### class `UUsdStageEditorSettings`  
`class UUsdStageEditorSettings : public UObject`  
_L10-22_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L17 _public member_ `bool bSelectionSynced = true;` — `UPROPERTY(config, EditAnywhere, Category = USD)` — Whether our prim selection in SUSDStageTreeView is kept synchronized with the viewport selection
- L21 _public member_ `bool bIsolateLayerSyncedWithEditTarget = true;` — `UPROPERTY(config, EditAnywhere, Category = USD)` — Whether to automatically set a layer as edit target when isolating it

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/Widgets/SUSDIntegrationsPanel.h` (Private)


#### class `UUsdIntegrationsPanelPropertyDummy`  
`class UUsdIntegrationsPanelPropertyDummy : public UObject`  
_L22-34_
- reflection: `UCLASS(Abstract, Transient, MinimalAPI)`
- inherits: `UObject`
- desc: We need an actual UObject and UPROPERTY to use the property editor module and generate one of the standard object picker widgets, so we'll be using the CDO of this class to do that
- L30 _public member_ `TObjectPtr<UObject> AnimBPProperty;` — `UPROPERTY(EditAnywhere, Transient, Category = Dummy, meta = (AllowedClasses = "/Script/Engine.AnimBlueprint"))` — Ideally these would be FSoftObjectPaths, but FPropertyEditorModule doesn't support generating widgets for those properties yet
- L33 _public member_ `TObjectPtr<UObject> ControlRigProperty;` — `UPROPERTY(EditAnywhere, Transient, Category = Dummy, meta = (AllowedClasses = "/Script/ControlRigDeveloper.ControlRigEditorAssetInterface,/Script/ControlRig.ControlRigRuntimeAssetInterface"))`

#### class `SUsdIntegrationsPanelRow`  
`class SUsdIntegrationsPanelRow : public SMultiColumnTableRow<TSharedPtr<UE::FUsdAttribute>>`  
_L38-53_
- inherits: `SMultiColumnTableRow<TSharedPtr<UE::FUsdAttribute>>`
- L41 _public function_ `SLATE_BEGIN_ARGS(SUsdIntegrationsPanelRow)`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<UE::FUsdAttribute> InAttr, const TSharedRef<STableViewBase>& OwnerTable);`
- L49 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L52 _private member_ `TSharedPtr<UE::FUsdAttribute> Attribute;`

#### class `SUsdIntegrationsPanel`  
`class SUsdIntegrationsPanel : public SListView<TSharedPtr<UE::FUsdAttribute>>`  
_L58-75_
- inherits: `SListView<TSharedPtr<UE::FUsdAttribute>>`
- desc: We don't really need a list view here since we'll mostly always know exactly what attributes are going to be displayed here beforehand, but doing so is a simple way of ensuring a consistent look between this panel and the variants/references panels, that *do* need to be lists
- L60 _private function_ `SLATE_BEGIN_ARGS(SUsdIntegrationsPanel)`
- L66 _public prototype_ `void Construct(const FArguments& InArgs);`
- L67 _public prototype_ `void SetPrimPath(const UE::FUsdStageWeak& UsdStage, const TCHAR* PrimPath);`
- L70 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<UE::FUsdAttribute> InAttr, const TSharedRef<STableViewBase>& OwnerTable);`
- L73 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L74 _private member_ `FUsdIntegrationsViewModel ViewModel;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/Widgets/SUSDObjectFieldList.h` (Private)


#### class `SUsdObjectFieldList`  
`class SUsdObjectFieldList : public SListView<TSharedPtr<FUsdObjectFieldViewModel>>`  
_L10-40_
- inherits: `SListView<TSharedPtr<FUsdObjectFieldViewModel>>`
- L13 _public function_ `SLATE_BEGIN_ARGS(SUsdObjectFieldList)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `void SetObjectPath(const UE::FUsdStageWeak& UsdStage, const TCHAR* InObjectPath);`
- L24 _public prototype_ `TArray<FString> GetSelectedFieldNames() const;`
- L25 _public prototype_ `void SetSelectedFieldNames(const TArray<FString>& NewSelection);`
- L27 _public prototype_ `UE::FUsdStageWeak GetUsdStage() const;`
- L28 _public prototype_ `FString GetObjectPath() const;`
- L31 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FUsdObjectFieldViewModel> InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L32 _protected prototype_ `void GenerateFieldList(const UE::FUsdStageWeak& UsdStage, const TCHAR* InObjectPath);`
- L34 _protected prototype_ `void Sort(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L35 _protected prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L38 _private member_ `FUsdObjectFieldsViewModel ViewModel;`
- L39 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/Widgets/SUSDReferencesList.h` (Private)


#### class `SUsdReferenceRow`  
`class SUsdReferenceRow : public SMultiColumnTableRow<TSharedPtr<FUsdReference>>`  
_L12-28_
- inherits: `SMultiColumnTableRow<TSharedPtr<FUsdReference>>`
- L15 _public function_ `SLATE_BEGIN_ARGS(SUsdReferenceRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FUsdReference> InReference, const TSharedRef<STableViewBase>& OwnerTable);`
- L23 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L26 _private member_ `FString PrimPath;`
- L27 _private member_ `TSharedPtr<FUsdReference> Reference;`

#### class `SUsdReferencesList`  
`class SUsdReferencesList : public SListView<TSharedPtr<FUsdReference>>`  
_L30-54_
- inherits: `SListView<TSharedPtr<FUsdReference>>`
- L32 _private function_ `SLATE_BEGIN_ARGS(SUsdReferencesList)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `void SetPrimPath(const UE::FUsdStageWeak& UsdStage, const TCHAR* PrimPath);`
- L42 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FUsdReference> InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _protected prototype_ `TSharedPtr<SWidget> ConstructLayerContextMenu();`
- L45 _protected prototype_ `bool CanRemoveReference() const;`
- L46 _protected prototype_ `void RemoveReference();`
- L48 _protected prototype_ `bool CanReloadReference() const;`
- L49 _protected prototype_ `void ReloadReference();`
- L52 _private member_ `FUsdReferencesViewModel ViewModel;`
- L53 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/Widgets/SUSDVariantSetsList.h` (Private)


#### class `SUsdVariantRow`  
`class SUsdVariantRow : public SMultiColumnTableRow<TSharedPtr<FUsdVariantSetViewModel>>`  
_L10-39_
- inherits: `SMultiColumnTableRow<TSharedPtr<FUsdVariantSetViewModel>>`
- L13 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnVariantSelectionChanged, const TSharedRef<FUsdVariantSetViewModel>&, const TSharedPtr<FString>&);`
- L16 _public function_ `SLATE_BEGIN_ARGS(SUsdVariantRow) : _OnVariantSelectionChanged()`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FUsdVariantSetViewModel> InVariantSet, const TSharedRef<STableViewBase>& OwnerTable);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L31 _protected member_ `FOnVariantSelectionChanged OnVariantSelectionChanged;`
- L34 _protected prototype_ `void OnSelectionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L37 _private member_ `FString PrimPath;`
- L38 _private member_ `TSharedPtr<FUsdVariantSetViewModel> VariantSet;`

#### class `SVariantsList`  
`class SVariantsList : public SListView<TSharedPtr<FUsdVariantSetViewModel>>`  
_L41-60_
- inherits: `SListView<TSharedPtr<FUsdVariantSetViewModel>>`
- L43 _private function_ `SLATE_BEGIN_ARGS(SVariantsList)`
- L49 _public prototype_ `void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `void SetPrimPath(const UE::FUsdStageWeak& UsdStage, const TCHAR* InPrimPath);`
- L53 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FUsdVariantSetViewModel> InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L55 _protected prototype_ `void OnVariantSelectionChanged(const TSharedRef<FUsdVariantSetViewModel>& VariantSet, const TSharedPtr<FString>& NewValue);`
- L58 _private member_ `FUsdVariantSetsViewModel ViewModel;`
- L59 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVariantSelectionChanged, const TSharedRef<FUsdVariantSetViewModel>&, const TSharedPtr<FString>&);`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Public/USDStageEditorBlueprintLibrary.h` (Public)


#### class `UUsdStageEditorBlueprintLibrary`  
`class UUsdStageEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L17-218_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "UsdStageEditorLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of functions that can be used from scripting to interact with the USD Stage Editor UI
- L27 _public prototype_ `static bool OpenStageEditor();` — `UFUNCTION(BlueprintCallable, Category = "USD|Stage Editor")` — Opens the the USD Stage Editor window, or focus it in case it is already open. @return True if a stage editor window is now opened and available.
- L34 _public prototype_ `static bool CloseStageEditor();` — `UFUNCTION(BlueprintCallable, Category = "USD|Stage Editor")` — Closes the USD Stage Editor window if it is opened. Does nothing in case it is already closed. @return True if a stage editor window was closed by this action.
- L41 _public prototype_ `static bool IsStageEditorOpened();` — `UFUNCTION(BlueprintCallable, Category = "USD|Stage Editor")` — Checks to see if an USD Stage Editor window is currently opened. @return True if a stage editor window is now opened and available.
- L49 _public prototype_ `static AUsdStageActor* GetAttachedStageActor();` — `UFUNCTION(BlueprintCallable, Category = "USD|Stage Actor")` — Gets which actor is currently attached to the USD Stage Editor, if any. May return nullptr in case no actor is attached. @return The attached stage actor.
- L58 _public prototype_ `static bool SetAttachedStageActor(AUsdStageActor* NewActor);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stage Actor")` — Sets which actor is currently attached to the USD Stage Editor. Provide None/nullptr to clear the attached stage actor. @param NewActor - The actor to select @return True in case the new actor was attached to the USD Stage Editor.
- L65 _public prototype_ `static TArray<FString> GetSelectedLayerIdentifiers();` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Returns the full identifiers of all layers that are currently selected on the USD Stage Editor. @return The list of identifiers (e.g. ["c:/MyFolder/root.usda", "c:/MyFolder/sublayer.usda"])
- L74 _public prototype_ `static void SetSelectedLayerIdentifiers(const TArray<FString>& NewSelection);` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Sets the USD Stage Editor layer selection to all occurences of the layers with identifiers in NewSelection. Provide an empty array to clear the selection. @param NewSelection - The list of identifiers to select (e.g. ["c:/MyFolder/root.usda", "c:/MyFolder/sublayer.usda"])
- L81 _public prototype_ `static TArray<FString> GetSelectedPrimPaths();` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Returns the full paths to all prims currently selected on the USD Stage Editor. @return The paths of selected prims (e.g. ["/ParentPrim/Mesh", "/Root"])
- L89 _public prototype_ `static void SetSelectedPrimPaths(const TArray<FString>& NewSelection);` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Sets the USD Stage Editor prim selection to the prims with paths contained in NewSelection. Provide an empty array to clear the selection. @param NewSelection - The list of prim paths to select (e.g. ["/ParentPrim/Mesh", "/Root"])
- L96 _public prototype_ `static TArray<FString> GetSelectedPropertyNames();` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Returns the names of the currently selected properties on the right panel of the USD Stage Editor. @return The names of selected properties (e.g. ["points", "displayColor"])
- L104 _public prototype_ `static void SetSelectedPropertyNames(const TArray<FString>& NewSelection);` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Sets the USD Stage Editor property selection to the properties with names contained in NewSelection. Provide an empty array to clear the selection. @param NewSelection - The list of property names to select (e.g. ["points", "displayColor"])
- L112 _public prototype_ `static TArray<FString> GetSelectedPropertyMetadataNames();` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Returns the names of the currently selected property metadata entries on the right panel of the USD Stage Editor. @return The names of selected metadata (e.g. ["documentation", "typeName"])
- L120 _public prototype_ `static void SetSelectedPropertyMetadataNames(const TArray<FString>& NewSelection);` — `UFUNCTION(BlueprintCallable, Category = "USD|Selection")` — Sets the USD Stage Editor property metadata selection to the entries with names contained in NewSelection. Provide an empty array to clear the selection. @param NewSelection - The list of property names to select (e.g. ["documentation", "typeName"])
- L127 _public prototype_ `static void FileNew();` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Creates a new memory-only layer and opens an USD Stage with that layer as its root. Corresponds to the "File -> New" action on the USD Stage Editor menu bar.
- L136 _public prototype_ `static void FileOpen(const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Opens an USD Stage from a file on disk. Corresponds to the "File -> Open" action on the USD Stage Editor menu bar. @param FilePath - File path to the USD layer to open (e.g. "C:/Folder/MyFile.usda"). If this path is the empty string a dialog will be shown to let the user pick the file.
- L147 _public prototype_ `static void FileSave(const FString& OutputFilePathIfUnsaved);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Saves the currently opened USD Stage back to disk, or to a new file in case it hasn't been saved yet. Corresponds to the "File -> Save" action on the USD Stage Editor menu bar. @param OutputFilePathIfUnsaved - File path (e.g. "C:/Folder/MyFile.usda") to use when the currently opened stage hasn't been saved yet. If this path is the empty string a dialog will be shown to let the user pick the file.
- L157 _public prototype_ `static void FileExportAllLayers(const FString& OutputDirectory);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Exports all layers of the currently opened USD Stage to brand new files in a new location. Corresponds to the "File -> Export -> All Layers" action on the USD Stage Editor menu bar. @param OutputDirectory - Directory path (e.g. "C:/ExportFolder/") to receive the exported files. If this path is the empty string a dialog will be shown to let the user pick the directory.
- L166 _public prototype_ `static void FileExportFlattenedStage(const FString& OutputLayer);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Exports the currently opened USD Stage to a single "flattened" USD layer. Corresponds to the "File -> Export -> Flattened stage" action on the USD Stage Editor menu bar. @param OutputLayer - File path (e.g. "C:/ExportFolder/out.usda") to export the flattened layer to. If this path is the empty string a dialog will be shown to let the user pick the file.
- L175 _public prototype_ `static void FileExportFlattenedLayerStack(const FString& OutputLayer);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Exports the currently opened USD Stage to a single "flattened" USD layer. Corresponds to the "File -> Export -> Flattened layer stack" action on the USD Stage Editor menu bar. @param OutputLayer - File path (e.g. "C:/ExportFolder/out.usda") to export the flattened layer to. If this path is the empty string a dialog will be shown to let the user pick the file.
- L182 _public prototype_ `static void FileReload();` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Reloads all layers of the current USD Stage. Corresponds to the "File -> Reload" action on the USD Stage Editor menu bar.
- L189 _public prototype_ `static void FileReset();` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Resets the state of the current USD Stage (which layers are muted, the current edit target, etc.). Corresponds to the "File -> Reset state" action on the USD Stage Editor menu bar.
- L196 _public prototype_ `static void FileClose();` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Closes the currently opened USD Stage (by clearing the attached Stage Actor's RootLayer property). Corresponds to the "File -> Close" action on the USD Stage Editor menu bar.
- L207 _public prototype_ `static void ActionsImport(const FString& OutputContentFolder, UUsdStageImportOptions* Options);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Imports the currently opened USD Stage into persistent UE assets, actors and components on the level. Corresponds to the "Actions -> Import" action on the USD Stage Editor menu bar. @param OutputContentFolder - Content path (e.g. "/Game/Imports") to receive the imported assets. If this path is the empty string a dialog will be shown to let the user pick the folder. @papam Options - Options object to use for the import.
- L217 _public prototype_ `static void ExportSelectedLayers(const FString& OutputDirectory);` — `UFUNCTION(BlueprintCallable, Category = "USD|Menu Actions")` — Exports the currently selected layers on the USD Stage Editor to brand new files in a new location. Corresponds to right-clicking selected layers on the USD Stage Editor and picking "Export". @param OutputDirectory - Directory path (e.g. "C:/ExportFolder/") to receive the exported files. If this path is the empty string a dialog will be shown to let the user pick the directory.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDSTAGEEDITOR_API`

### `Plugins/Importers/USDImporter/Source/USDStageEditor/Public/USDStageEditorModule.h` (Public)


#### class `IUsdStageEditorModule`  
`class IUsdStageEditorModule : public IModuleInterface`  
_L18-58_
- inherits: `IModuleInterface`
- L26 _public prototype_ `bool OpenStageEditor() const;`
- L27 _public prototype_ `bool CloseStageEditor() const;`
- L28 _public prototype_ `bool IsStageEditorOpened() const;`
- L30 _public prototype_ `AUsdStageActor* GetAttachedStageActor() const;`
- L31 _public prototype_ `bool SetAttachedStageActor(AUsdStageActor* NewActor) const;`
- L33 _public prototype_ `TArray<UE::FSdfLayer> GetSelectedLayers() const;`
- L34 _public prototype_ `void SetSelectedLayers(const TArray<UE::FSdfLayer>& NewSelection) const;`
- L36 _public prototype_ `TArray<UE::FUsdPrim> GetSelectedPrims() const;`
- L37 _public prototype_ `void SetSelectedPrims(const TArray<UE::FUsdPrim>& NewSelection) const;`
- L39 _public prototype_ `TArray<FString> GetSelectedPropertyNames() const;`
- L40 _public prototype_ `void SetSelectedPropertyNames(const TArray<FString>& NewSelection) const;`
- L42 _public prototype_ `TArray<FString> GetSelectedPropertyMetadataNames() const;`
- L43 _public prototype_ `void SetSelectedPropertyMetadataNames(const TArray<FString>& NewSelection) const;`
- L47 _public prototype_ `void FileNew() const;` — For all of these, providing an empty path will cause us to pop open a dialog to let the user pick the path instead.
- L48 _public prototype_ `void FileOpen(const FString& FilePath) const;`
- L49 _public prototype_ `void FileSave(const FString& OutputFilePathIfUnsaved) const;`
- L50 _public prototype_ `void FileExportAllLayers(const FString& OutputDirectory) const;`
- L51 _public prototype_ `void FileExportFlattenedStage(const FString& OutputLayer) const;`
- L52 _public prototype_ `void FileExportFlattenedLayerStack(const FString& OutputLayer) const;`
- L53 _public prototype_ `void FileReload() const;`
- L54 _public prototype_ `void FileReset() const;`
- L55 _public prototype_ `void FileClose() const;`
- L56 _public prototype_ `void ActionsImport(const FString& OutputContentFolder, UUsdStageImportOptions* Options) const;`
- L57 _public prototype_ `void ExportSelectedLayers(const FString& OutputLayerOrDirectory) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
