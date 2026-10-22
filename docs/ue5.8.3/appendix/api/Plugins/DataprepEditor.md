# Plugins / DataprepEditor

- module root: `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor`
- headers: 52; symbols: 1449
- symbol kinds: class=73, delegate=14, enum=8, enumerator=29, externvar=1, function=202, macro=1, member=407, namespace=21, prototype=658, struct=14, typedef=20, variable=1
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, Blutility, ContentBrowser, Core, CoreUObject, DataprepCore, DesktopPlatform, EditorFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, Kismet, KismetCompiler, KismetWidgets, Landscape, MainFrame, MeshDescription, MeshUtilities, MeshUtilitiesCommon, MessageLog, Projects, PropertyEditor, RHI, RenderCore, SceneOutliner, Slate, SlateCore, StatsViewer, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/AssetDefinition_DataprepAsset.h` (Private)


#### class `UAssetDefinition_DataprepAssetInterface`  
`class UAssetDefinition_DataprepAssetInterface : public UAssetDefinitionDefault`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L22 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _public function_ `virtual bool CanImport() const override`

#### class `UAssetDefinition_DataprepAsset`  
`class UAssetDefinition_DataprepAsset : public UAssetDefinition_DataprepAssetInterface`  
_L28-38_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataprepAssetInterface`
- L34 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L35 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L36 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

#### class `UAssetDefinition_DataprepAssetInstance`  
`class UAssetDefinition_DataprepAssetInstance : public UAssetDefinition_DataprepAssetInterface`  
_L41-51_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataprepAssetInterface`
- L47 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L48 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L49 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/BlueprintNodes/K2Node_DataprepAction.h` (Private)


#### class `UDEPRECATED_K2Node_DataprepAction`  
`class UDEPRECATED_K2Node_DataprepAction : public UK2Node_DataprepActionCore`  
_L18-55_
- reflection: `UCLASS(MinimalAPI, Deprecated, meta = (DeprecationMessage = "No use of Blueprint with Dataprep."))`
- inherits: `UK2Node_DataprepActionCore`
- L23 _public prototype_ `UDEPRECATED_K2Node_DataprepAction();`
- L26 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L27 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _public function_ `virtual bool ShowPaletteIconOnNode() const override`
- L29 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L31 _public prototype_ `virtual void DestroyNode() override;`
- L32 _public prototype_ `TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L36 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L37 _public prototype_ `virtual FText GetMenuCategory() const;`
- L38 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L39 _public prototype_ `virtual void PostReconstructNode() override;`
- L43 _private prototype_ `UEdGraphPin& GetOutExecutionPin() const;`
- L44 _private prototype_ `UEdGraphPin& GetInObjectsPin() const;`
- L48 _protected member_ `FString ActionTitle;` — `UPROPERTY()`
- L51 _protected member_ `TObjectPtr<UDataprepActionAsset> DataprepAction_DEPRECATED;` — `UPROPERTY()`
- L53 _protected member_ `static const FName ThenPinName;`
- L54 _protected member_ `static const FName InObjectsPinName;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepEditor.h` (Private)


#### class `SDataprepScenePreviewView`  
`class SDataprepScenePreviewView : public SBorder`  
_L50-67_
- inherits: `SBorder`
- L54 _public function_ `FDataprepEditorUtils::FOnKeyDown& OnKeyDown()`
- L56 _public function_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L66 _private member_ `FDataprepEditorUtils::FOnKeyDown OnKeyDownDelegate;`

#### struct `FDataprepSnapshot`  
`struct FDataprepSnapshot`  
_L72-78_
- L74 _public member_ `bool bIsValid;`
- L75 _public member_ `TArray<FSnapshotDataEntry> DataEntries;`
- L77 _public function_ `FDataprepSnapshot() : bIsValid(false)`

#### class `FDataprepEditor`  
`class FDataprepEditor : public FAssetEditorToolkit, public FEditorUndoClient, public FNotifyHook, public FGCObject`  
_L82-362_
- inherits: `FAssetEditorToolkit,FEditorUndoClient,FNotifyHook,FGCObject`
- L85 _public prototype_ `FDataprepEditor();`
- L86 _public prototype_ `virtual ~FDataprepEditor();`
- L88 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDataprepAssetProducerChanged);`
- L90 _public function_ `FOnDataprepAssetProducerChanged& OnDataprepAssetProducerChanged()`
- L95 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDataprepAssetConsumerChanged);`
- L97 _public function_ `FOnDataprepAssetConsumerChanged& OnDataprepAssetConsumerChanged()`
- L102 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L103 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L105 _public prototype_ `void InitDataprepEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UDataprepAssetInterface* InDataprepAssetInterface);`
- L108 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L109 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L110 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L113 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L115 _public function_ `UDataprepAssetInterface* GetDataprepAsset() const`
- L121 _public function_ `bool& GetIsContextSensitive()` — Gets or sets the flag for context sensitivity in the graph action menu
- L124 _public function_ `const TSet<TWeakObjectPtr<UObject>>& GetWorldItemsSelection() const` — Return the selected object from the scene outliner / world preview
- L134 _public prototype_ `void SetWorldObjectsSelection(TSet<TWeakObjectPtr<UObject>>&& NewSelection, EWorldSelectionFrom SelectionFrom = EWorldSelectionFrom::Unknow, bool bSetAsDetailsObject = true);` — Set the selection of the world items
- L137 _public prototype_ `void SetPreviewedObjects(const TArrayView<UDataprepParameterizableObject*>& ObservedObjects);` — Setup the preview system to observe those steps
- L140 _public prototype_ `void ClearPreviewedObjects();` — Clear any ongoing preview from the step preview system for this editor
- L143 _public prototype_ `bool IsPreviewingStep(const UDataprepParameterizableObject* StepObject) const;` — Is the preview system observing this step
- L146 _public prototype_ `int32 GetCountOfPreviewedSteps() const;` — Return the number of steps the preview system is currently previewing
- L149 _public prototype_ `void SyncSelectionToPreviewSystem();` — Select all actors and assets that have status Pass from the preview system
- L152 _public function_ `TWeakPtr<AssetPreviewWidget::SAssetsPreviewWidget> GetAssetPreviewView()` — Return a weak pointer to asset preview view
- L155 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L156 _public prototype_ `virtual FString GetReferencerName() const override;`
- L157 _public prototype_ `virtual bool GetReferencerPropertyName(UObject* Object, FString& OutPropertyName) const override;`
- L159 _public prototype_ `void OnSceneOutlinerSelectionChanged(FSceneOutlinerTreeItemPtr ItemPtr, ESelectInfo::Type SelectionMode);` — Handles change to selection in SceneOutliner
- L162 _public prototype_ `FString GetTransientContentFolder();` — Returns content folder under which all assets are stored after execution of all producers
- L164 _public function_ `UWorld* GetWorld()`
- L170 _private prototype_ `void BindCommands();`
- L171 _private prototype_ `void OnSaveScene();`
- L172 _private prototype_ `void OnBuildWorld();`
- L173 _private prototype_ `void ResetBuildWorld();`
- L174 _private prototype_ `void CleanPreviewWorld();`
- L175 _private prototype_ `void OnExecutePipeline();`
- L176 _private prototype_ `void OnCommitWorld();`
- L179 _private prototype_ `void UpdatePreviewPanels(bool bInclude3dViewport = true);` — Updates asset preview, scene outliner and 3D viewport if applicable
- L181 _private prototype_ `void CreateTabs();`
- L184 _private prototype_ `void RegisterCopyNameAndLabelMenu();` — Scene outliner context menus
- L185 _private prototype_ `void RegisterSelectReferencedAssetsMenu();`
- L186 _private prototype_ `void RegisterSelectReferencingActorsMenu();`
- L188 _private prototype_ `void CreateScenePreviewTab();`
- L190 _private prototype_ `void CreateAssetPreviewTab();`
- L192 _private prototype_ `TSharedRef<SDockTab> SpawnTabAssetPreview(const FSpawnTabArgs& Args);`
- L193 _private prototype_ `TSharedRef<SDockTab> SpawnTabScenePreview(const FSpawnTabArgs& Args);`
- L194 _private prototype_ `TSharedRef<SDockTab> SpawnTabPalette(const FSpawnTabArgs& Args);`
- L195 _private prototype_ `TSharedRef<SDockTab> SpawnTabDetails(const FSpawnTabArgs& Args);`
- L196 _private prototype_ `TSharedRef<SDockTab> SpawnTabDataprep(const FSpawnTabArgs& Args);`
- L197 _private prototype_ `TSharedRef<SDockTab> SpawnTabSceneViewport( const FSpawnTabArgs& Args );`
- L198 _private prototype_ `TSharedRef<SDockTab> SpawnTabStatistics(const FSpawnTabArgs& Args);`
- L199 _private prototype_ `TSharedRef<SDockTab> SpawnTabGraphEditor(const FSpawnTabArgs & Args);`
- L201 _private prototype_ `TSharedRef<FTabManager::FLayout> CreateDataprepLayout();`
- L202 _private prototype_ `TSharedRef<FTabManager::FLayout> CreateDataprepInstanceLayout();`
- L204 _private prototype_ `void TryInvokingDetailsTab(bool bFlash);`
- L207 _private prototype_ `void ExtendMenu();` — Extends the toolbar menu to include static mesh editor options
- L210 _private prototype_ `void ExtendToolBar();` — Builds the Data Prep Editor toolbar.
- L212 _private prototype_ `void CreateDetailsViews();`
- L218 _private prototype_ `void OnPipelineEditorSelectionChanged(const TSet<UObject*>& SelectedNodes);` — Called whenever the selected nodes in the graph editor changes.
- L224 _private prototype_ `void SetDetailsObjects(const TSet<UObject*>& Objects, bool bCanEditProperties);` — Change the objects display by the details panel @param bCanEditProperties Should the details view let the user modify the objects.
- L226 _private prototype_ `bool CanExecutePipeline();`
- L227 _private prototype_ `bool CanBuildWorld();`
- L228 _private prototype_ `bool CanCommitWorld();`
- L230 _private prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L233 _private prototype_ `void TakeSnapshot();` — Create a snapshot of the world and tracked assets
- L236 _private prototype_ `void RestoreFromSnapshot( bool bUpdateViewport = false );` — Recreate preview world from snapshot
- L239 _private prototype_ `void OnDataprepAssetChanged(FDataprepAssetChangeType ChangeType);` — Handles changes in the Dataprep asset
- L242 _private prototype_ `void CleanUpTemporaryDirectories();` — Remove all temporary data remaining from previous runs of the Dataprep editor
- L244 _private prototype_ `bool OnCanExecuteNextStep(UDataprepActionAsset* ActionAsset);`
- L247 _private prototype_ `void OnActionsContextChanged( const UDataprepActionAsset* ActionAsset, bool bWorldChanged, bool bAssetsChanged, const TArray< TWeakObjectPtr<UObject> >& NewAssets );` — Handles change to the content passed to an action
- L250 _private prototype_ `void RefreshColumnsForPreviewSystem();` — Refresh the columns of the scene preview (outliner) and the asset preview
- L253 _private prototype_ `void UpdateDataForPreviewSystem();` — Update the data used by the preview system
- L255 _private prototype_ `void OnStepObjectsAboutToBeDeleted(const TArrayView<UDataprepParameterizableObject*>& StepObject);`
- L257 _private prototype_ `TSharedPtr<SWidget> OnSceneOutlinerContextMenuOpening();`
- L259 _private prototype_ `virtual void PostUndo( bool bSuccess ) override;`
- L260 _private prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L262 _private prototype_ `void CreateGraphEditor();`
- L264 _private prototype_ `void RefreshStatsTab();`
- L270 _private member_ `bool bWorldBuilt;`
- L271 _private member_ `bool bIsFirstRun;`
- L272 _private member_ `bool bPipelineChanged;`
- L273 _private member_ `bool bIsDataprepInstance;`
- L274 _private member_ `TWeakObjectPtr<UDataprepAssetInterface> DataprepAssetInterfacePtr;`
- L276 _private member_ `FOnDataprepAssetProducerChanged DataprepAssetProducerChangedDelegate;`
- L277 _private member_ `FOnDataprepAssetConsumerChanged DataprepAssetConsumerChangedDelegate;`
- L279 _private member_ `TWeakPtr<SDockTab> DetailsTabPtr;`
- L280 _private member_ `TSharedPtr<class SDataprepEditorViewport> SceneViewportView;`
- L281 _private member_ `TSharedPtr<AssetPreviewWidget::SAssetsPreviewWidget> AssetPreviewView;`
- L282 _private member_ `TSharedPtr<SDataprepScenePreviewView> ScenePreviewView;`
- L283 _private member_ `TSharedPtr<SGraphNodeDetailsWidget> DetailsView;`
- L284 _private member_ `TSharedPtr<class SDataprepAssetView > DataprepAssetView;`
- L285 _private member_ `TSharedPtr<SDataprepGraphEditor> GraphEditor;`
- L287 _private member_ `TSharedPtr<class ISceneOutliner> SceneOutliner;`
- L290 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for the pipeline editor
- L291 _private member_ `bool bIsActionMenuContextSensitive;`
- L292 _private member_ `bool bSaveIntermediateBuildProducts;`
- L298 _private member_ `TSet<TWeakObjectPtr<UObject>> WorldItemsSelection;` — Track the user selection from the scene outliner This is referred to the garbage collector as a week reference
- L303 _private member_ `TArray<TWeakObjectPtr<UObject>> Assets;` — All assets tracked for this editor.
- L304 _private member_ `TSet<FSoftObjectPath> CachedAssets;`
- L309 _private member_ `TObjectPtr<UWorld> PreviewWorld;` — The world used to preview the inputs
- L314 _private member_ `TObjectPtr<UPackage> AssetsTransientPackage;` — The package that contains the assets of a dataprep import
- L319 _private member_ `TObjectPtr<UDataprepGraph> DataprepGraph;` — The graph used to manipulate actions and steps
- L321 _private member_ `TSet<class AActor*> DefaultActorsInPreviewWorld;`
- L324 _private member_ `bool bIgnoreCloseRequest;` — flag raised to prevent this editor to be closed
- L327 _private member_ `TArray< DataprepEditorClassDescription > ConsumerDescriptions;` — Array of UClasses deriving from UDataprepContentConsumer
- L330 _private member_ `FString TempDir;` — Temporary folder used to store content from snapshot
- L333 _private member_ `FString SessionID;` — Unique identifier assigned to each opened Dataprep editor to avoid name collision on cached data
- L336 _private member_ `FDataprepSnapshot ContentSnapshot;` — Structure to hold on the content of the latest call to OnBuildWorld
- L339 _private member_ `TMap<FString, UClass*> SnapshotClassesMap;` — Helper member to record classes of assets' sub-objects
- L342 _private member_ `TSharedRef<FDataprepPreviewSystem> PreviewSystem;` — Steps Preview System
- L344 _private member_ `TSharedPtr<FDataprepActionContext> ActionsContext;`
- L346 _private member_ `TSharedPtr<FDataprepStats> PreExecuteStatsPtr;`
- L347 _private member_ `TSharedPtr<FDataprepStats> PostExecuteStatsPtr;`
- L348 _private member_ `TWeakPtr<SDataprepStats> StatsWidgetPtr;`
- L349 _private member_ `TWeakPtr<SDockTab> StatsTabPtr;`
- L352 _private member_ `static const FName ScenePreviewTabId;` — The tab ids for all the tabs used
- L353 _private member_ `static const FName AssetPreviewTabId;`
- L354 _private member_ `static const FName PaletteTabId;`
- L355 _private member_ `static const FName DetailsTabId;`
- L356 _private member_ `static const FName DataprepAssetTabId;`
- L357 _private member_ `static const FName SceneViewportTabId;`
- L358 _private member_ `static const FName DataprepStatisticsTabId;`
- L359 _private member_ `static const FName DataprepGraphEditorTabId;`
- L361 _private member_ `static const FName StatNameDrawCalls;`

#### enum `FDataprepEditor::EWorldSelectionFrom`  
`enum class EWorldSelectionFrom : uint8`  
_L126-131_
- L128 _public enumerator_ `SceneOutliner`
- L129 _public enumerator_ `Viewport`
- L130 _public enumerator_ `Unknow`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ESelectInfo`
- L34 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Dataprep` (scope `UE`)
- L38 _namespace_ `namespace Private` (scope `UE::Dataprep`)
- L45 _namespace_ `namespace AssetPreviewWidget`
- L70 _typedef_ `typedef TTuple< FString, UClass*, EObjectFlags > FSnapshotDataEntry;` — Tuple linking an asset package path, a unique identifier and the UClass of the asset
- L80 _typedef_ `typedef TTuple< UClass*, FText, FText > DataprepEditorClassDescription;`
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDataprepAssetProducerChanged);`
- L95 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDataprepAssetConsumerChanged);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepEditorActions.h` (Private)


#### class `FDataprepEditorCommands`  
`class FDataprepEditorCommands : public TCommands<FDataprepEditorCommands>`  
_L12-47_
- inherits: `TCommands<FDataprepEditorCommands>`
- desc: Unreal DataPrep editor actions
- L16 _public function_ `FDataprepEditorCommands() : TCommands<FDataprepEditorCommands> ( "DataprepEditor",`
- L31 _public member_ `TSharedPtr< FUICommandInfo > SaveScene;`
- L32 _public member_ `TSharedPtr< FUICommandInfo > ShowDatasmithSceneSettings;`
- L33 _public member_ `TSharedPtr< FUICommandInfo > ExecutePipeline;`
- L34 _public member_ `TSharedPtr< FUICommandInfo > CommitWorld;`
- L38 _public member_ `TSharedPtr< FUICommandInfo > CompileGraph;` — Temp code for the nodes development
- L44 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepEditorLogCategory.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataprepEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataprepEditor, Log, All);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepEditorOutlinerMode.h` (Private)


#### struct `DataprepEditorSceneOutlinerUtils::FSynchroniseSelectionToSceneOutliner`  
`struct FSynchroniseSelectionToSceneOutliner`  
_L17-45_
- desc: Use this struct to match the scene outliers selection to a dataprep editor selection
- L19 _public function_ `FSynchroniseSelectionToSceneOutliner(TWeakPtr<FDataprepEditor> InDataprepEditor) : DataprepEditorPtr(InDataprepEditor)`
- L24 _public function_ `bool operator()(const ISceneOutlinerTreeItem& Item) const`
- L44 _private member_ `TWeakPtr<FDataprepEditor> DataprepEditorPtr;`

#### class `FDataprepEditorOutlinerMode`  
`class FDataprepEditorOutlinerMode : public FActorMode`  
_L48-107_
- inherits: `FActorMode`
- L51 _public function_ `FDataprepEditorOutlinerMode(SSceneOutliner* InSceneOutliner, TWeakPtr<FDataprepEditor> InDataprepEditor, TWeakObjectPtr<UWorld> InSpecifiedWorldToDisplay = nullptr) : FActorMode(FActorModeParams(InSceneOutliner, InSpecifiedWorldToDisplay, true, true)) , DataprepEditorPtr(InDataprepEditor)`
- L58 _public function_ `~FDataprepEditorOutlinerMode()`
- L63 _public function_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override`
- L64 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L66 _public function_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override`
- L75 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L78 _private function_ `void OnActorLabelChanged(AActor* InChangedActor)`
- L106 _private member_ `TWeakPtr<FDataprepEditor> DataprepEditorPtr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DataprepEditorSceneOutlinerUtils`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepEditorStyle.h` (Private)


#### class `FDataprepEditorStyle`  
`class FDataprepEditorStyle`  
_L10-55_
- desc: Contains a collection of named properties (StyleSet) that guide the appearance of Datasmith related UI.
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L15 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L17 _public prototype_ `static FName GetStyleSetName();`
- L19 _public function_ `static float GetFloat( FName PropertyName, const ANSICHAR* Specifier = nullptr )`
- L24 _public function_ `static FVector2D GetVector( FName PropertyName, const ANSICHAR* Specifier = nullptr )`
- L29 _public function_ `static const FLinearColor& GetColor( FName PropertyName, const ANSICHAR* Specifier = nullptr )`
- L34 _public function_ `static const FMargin& GetMargin( FName PropertyName, const ANSICHAR* Specifier = nullptr )`
- L39 _public function_ `static const FSlateBrush* GetBrush( FName PropertyName, const ANSICHAR* Specifier = nullptr )`
- L45 _public function_ `template< typename WidgetStyleType > static const WidgetStyleType& GetWidgetStyle( FName PropertyName, const ANSICHAR* Specifier = nullptr )`
- L51 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L54 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepEditorUtils.h` (Private)


#### struct `FDataprepParametrizationActionData`  
`struct FDataprepParametrizationActionData : public FGCObject`  
_L19-39_
- inherits: `FGCObject`
- L21 _public function_ `FDataprepParametrizationActionData(UDataprepAsset& InDataprepAsset, UDataprepParameterizableObject& InObject, const TArray<FDataprepPropertyLink>& InPropertyChain) : FGCObject() , DataprepAsset(&InDataprepAsset) , Object(&InObject) , PropertyChain(InPropertyChain)`
- L28 _public member_ `TObjectPtr<UDataprepAsset> DataprepAsset;`
- L29 _public member_ `TObjectPtr<UDataprepParameterizableObject> Object;`
- L30 _public member_ `TArray<FDataprepPropertyLink> PropertyChain;`
- L32 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L33 _public function_ `virtual FString GetReferencerName() const override`
- L38 _public prototype_ `bool IsValid() const;`

#### class `FDataprepEditorUtils`  
`class FDataprepEditorUtils`  
_L41-86_
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnKeyDown, const FGeometry& , const FKeyEvent& ) static void PopulateMenuForParameterization(FMenuBuilder& MenuBuilder, UDataprepAsset& DataprepAsset, UDataprepParameterizableObject& Object, const TArray<FDataprepPropertyLink>& PropertyChain);`
- L54 _public prototype_ `static FSlateFontInfo GetGlyphFont();`
- L59 _public prototype_ `static TSharedPtr<SWidget> MakeContextMenu(const TSharedPtr<FDataprepParametrizationActionData>& ParameterizationActionData);` — Make a context menu widget to manage parameterization link of a property
- L61 _public prototype_ `static void RegisterBlueprintCallbacks(void* InModule);`
- L67 _public prototype_ `static bool CreateUserDefinedFilter();` — Create new user-defined filter, based on blueprint @return Returns true if the filter was successfully created, false if cancelled
- L73 _public prototype_ `static bool CreateUserDefinedOperation();` — Create new user-defined operation, based on blueprint @return Returns true if the operation was successfully created, false if cancelled
- L79 _public prototype_ `static TSet<UObject*> GetReferencedAssets(const TSet<AActor*>& InActors);` — Get assets referenced by a set of actors. @param InActors	Actors to check for assets
- L85 _public prototype_ `static TSet<TWeakObjectPtr<UObject>> GetActorsReferencingAssets(UWorld* InWorld, const TSet<UObject*>& InAssets);` — Get all actors that reference any asset in the input assets list @param InAssets The set of referenced assets to follow

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnKeyDown, const FGeometry& , const FKeyEvent& ) static void PopulateMenuForParameterization(FMenuBuilder& MenuBuilder, UDataprepAsset& DataprepAsset, UDataprepParameterizableObject& Object, const TArray<FDataprepPropertyLink>& PropertyChain);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepGraph/DataprepGraph.h` (Private)


#### class `UDataprepGraph`  
`class UDataprepGraph : public UEdGraph`  
_L23-37_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- desc: The UDataprepGraph class is used to display the pipeline of a Dataprep asset in a SDataprepGraphEditor.
- L29 _public prototype_ `void Initialize(UDataprepAsset* InDataprepAsset);` — Associate Dataprep asset with graph and add root node
- L31 _public function_ `const UDataprepAsset* GetDataprepAsset() const`
- L32 _public function_ `UDataprepAsset* GetDataprepAsset()`
- L36 _private member_ `TWeakObjectPtr<UDataprepAsset> DataprepAssetPtr;` — Dataprep asset associated with this graph

#### class `UDataprepGraphRecipeNode`  
`class UDataprepGraphRecipeNode : public UEdGraphNode`  
_L44-63_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- desc: The UDataprepGraphRecipeNode is the root graph node from which the associated widget, SDataprepGraphTrackNode, will add all the action nodes and their content
- L50 _public function_ `TSharedPtr<SGraphNode> GetWidget()` — Get/Set associated widget
- L51 _public function_ `void SetWidget(TSharedPtr<SGraphNode> InWidget)`
- L54 _public function_ `virtual bool CanDuplicateNode() const override` — UEdGraphNode implementation
- L55 _public function_ `virtual bool CanUserDeleteNode() const override`
- L62 _private member_ `TWeakPtr<SGraphNode> Widget;` — Associated widget displayed in the Dataprep graph editor

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepGraph/DataprepGraphActionNode.h` (Private)


#### class `UDataprepGraphActionStepNode`  
`class UDataprepGraphActionStepNode : public UEdGraphNode`  
_L20-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- desc: The UDataprepGraphActionStepNode class is used as the UEdGraphNode associated to an SGraphNode in order to display the action's steps in a SDataprepGraphEditor.
- L25 _public prototype_ `UDataprepGraphActionStepNode();`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public function_ `virtual bool ShowPaletteIconOnNode() const override`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `virtual void DestroyNode() override;`
- L35 _public function_ `void Initialize(UDataprepActionAsset* InDataprepActionAsset, int32 InStepIndex)`
- L41 _public function_ `const UDataprepActionAsset* GetDataprepActionAsset() const`
- L42 _public function_ `UDataprepActionAsset* GetDataprepActionAsset()`
- L44 _public function_ `int32 GetStepIndex() const`
- L46 _public prototype_ `const UDataprepActionStep* GetDataprepActionStep() const;`
- L47 _public prototype_ `UDataprepActionStep* GetDataprepActionStep();`
- L51 _protected member_ `TObjectPtr<UDataprepActionAsset> DataprepActionAsset;` — `UPROPERTY()`
- L54 _protected member_ `int32 StepIndex;` — `UPROPERTY()`
- L57 _protected member_ `bool bIsPreviewed = false;` — Is this node currently driving the filter preview

#### class `UDataprepGraphActionNode`  
`class UDataprepGraphActionNode final : public UEdGraphNode`  
_L65-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- desc: The UDataprepGraphActionNode class is used as the UEdGraphNode associated to an SGraphNode in order to display actions in a SDataprepGraphEditor.
- L70 _public prototype_ `UDataprepGraphActionNode();`
- L73 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L74 _public function_ `virtual bool ShowPaletteIconOnNode() const override`
- L75 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L76 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L77 _public prototype_ `virtual void DestroyNode() override;`
- L78 _public prototype_ `TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L79 _public prototype_ `virtual void ResizeNode(const FVector2f& NewSize) override;`
- L82 _public prototype_ `void Initialize(TWeakObjectPtr<UDataprepAsset> InDataprepAssetPtr, UDataprepActionAsset* InDataprepActionAsset, int32 InExecutionOrder);`
- L84 _public function_ `const UDataprepActionAsset* GetDataprepActionAsset() const`
- L85 _public function_ `UDataprepActionAsset* GetDataprepActionAsset()`
- L87 _public function_ `int32 GetExecutionOrder() const`
- L91 _protected member_ `FString ActionTitle;` — `UPROPERTY()`
- L94 _protected member_ `TObjectPtr<UDataprepActionAsset> DataprepActionAsset;` — `UPROPERTY()`
- L97 _protected member_ `TWeakObjectPtr<UDataprepAsset> DataprepAssetPtr;` — `UPROPERTY()`
- L100 _protected member_ `int32 ExecutionOrder;` — `UPROPERTY()`

#### class `UDataprepGraphActionGroupNode`  
`class UDataprepGraphActionGroupNode final : public UEdGraphNode`  
_L104-154_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L109 _public prototype_ `UDataprepGraphActionGroupNode();`
- L112 _public function_ `virtual bool ShowPaletteIconOnNode() const override`
- L113 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L114 _public prototype_ `TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L115 _public prototype_ `virtual void ResizeNode(const FVector2f& NewSize) override;`
- L118 _public prototype_ `void Initialize(TWeakObjectPtr<UDataprepAsset> InDataprepAssetPtr, TArray<UDataprepActionAsset*>& InActions, int32 InExecutionOrder);`
- L120 _public function_ `int32 GetExecutionOrder() const`
- L122 _public prototype_ `int32 GetGroupId() const;`
- L124 _public prototype_ `bool IsGroupEnabled() const;`
- L126 _public function_ `UDataprepActionAsset* GetAction(int32 Index) const`
- L132 _public function_ `UDataprepAsset* GetDataprepAsset()`
- L137 _public function_ `int32 GetActionsCount() const`
- L144 _protected member_ `int32 ExecutionOrder;` — `UPROPERTY()`
- L147 _protected member_ `FString NodeTitle;` — `UPROPERTY()`
- L150 _protected member_ `TArray<TObjectPtr<UDataprepActionAsset>> Actions;` — `UPROPERTY()`
- L153 _protected member_ `TWeakObjectPtr<UDataprepAsset> DataprepAssetPtr;` — `UPROPERTY()`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepGraph/DataprepGraphSchema.h` (Private)


#### class `UDataprepGraphSchema`  
`class UDataprepGraphSchema : public UEdGraphSchema`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L17 _public function_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override` — UEdGraphSchema interface
- L18 _public function_ `virtual FName GetParentContextMenuName() const override`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepStats.h` (Private)


#### struct `FDataprepStats`  
`struct FDataprepStats`  
_L9-71_
- L12 _public member_ `static const FName StatNameTriangles;` — Stat names
- L13 _public member_ `static const FName StatNameVertices;`
- L14 _public member_ `static const FName StatNameNaniteTriangles;`
- L15 _public member_ `static const FName StatNameNaniteVertices;`
- L16 _public member_ `static const FName StatNameTextures;`
- L17 _public member_ `static const FName StatNameTextureSize;`
- L18 _public member_ `static const FName StatNameMeshes;`
- L19 _public member_ `static const FName StatNameSkeletalMeshes;`
- L20 _public member_ `static const FName StatNameMaterials;`
- L21 _public member_ `static const FName StatNameLights;`
- L22 _public member_ `static const FName StatNameActors;`
- L23 _public member_ `static const FName StatNameActorComponents;`
- L25 _public prototype_ `static TSharedPtr<FDataprepStats> GenerateWorldStats(UWorld* InWorld);`
- L27 _public function_ `FDataprepStats()`
- L43 _public function_ `void Set(const FName InStatName, int32 InValue)`
- L49 _public function_ `int32 Get(const FName InStatName) const`
- L58 _public function_ `const TMap<FName, int32>& GetMap() const`
- L63 _public function_ `void AddCount(const FName InStatName, int32 InValue)`
- L70 _private member_ `TMap<FName, int32> StatsMap;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/PreviewSystem/DataprepPreviewAssetColumn.h` (Private)


#### class `FDataprepPreviewAssetColumn`  
`class FDataprepPreviewAssetColumn : public AssetPreviewWidget::IAssetPreviewColumn`  
_L10-43_
- inherits: `AssetPreviewWidget::IAssetPreviewColumn`
- L13 _public prototype_ `FDataprepPreviewAssetColumn(const TSharedRef<FDataprepPreviewSystem>& InPreviewSystem);`
- L14 _public prototype_ `virtual ~FDataprepPreviewAssetColumn() = default;`
- L17 _public function_ `virtual uint8 GetCulumnPositionPriorityIndex() const override`
- L22 _public function_ `virtual FName GetColumnID() const override`
- L27 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<AssetPreviewWidget::SAssetsPreviewWidget>& PreviewWidget) override;`
- L29 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(const AssetPreviewWidget::IAssetTreeItemPtr& TreeItem, const STableRow<AssetPreviewWidget::IAssetTreeItemPtr>& Row, const TSharedRef<AssetPreviewWidget::SAssetsPreviewWidget>& PreviewWidget) override;`
- L31 _public prototype_ `virtual void PopulateSearchStrings(const AssetPreviewWidget::IAssetTreeItemPtr& Item, TArray< FString >& OutSearchStrings, const AssetPreviewWidget::SAssetsPreviewWidget& AssetPreview) const override;`
- L33 _public prototype_ `virtual void SortItems(TArray<AssetPreviewWidget::IAssetTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const override;`
- L35 _public member_ `static const FName ColumnID;`
- L39 _private prototype_ `void OnPreviewSystemIsDoneProcessing();` — Request a sort refresh if this column was the one doing the sorting
- L41 _private member_ `TWeakPtr<AssetPreviewWidget::SAssetsPreviewWidget> PreviewWidgetWeakPtr;`
- L42 _private member_ `TSharedPtr<FDataprepPreviewSystem> PreviewSystem;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/PreviewSystem/DataprepPreviewSceneOutlinerColumn.h` (Private)


#### class `FDataprepPreviewOutlinerColumn`  
`class FDataprepPreviewOutlinerColumn : public ISceneOutlinerColumn`  
_L11-39_
- inherits: `ISceneOutlinerColumn`
- L14 _public prototype_ `FDataprepPreviewOutlinerColumn(ISceneOutliner& SceneOutliner, const TSharedRef<FDataprepPreviewSystem>& PreviewData);`
- L15 _public prototype_ `virtual ~FDataprepPreviewOutlinerColumn() = default;`
- L18 _public prototype_ `virtual FName GetColumnID() override;`
- L20 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L22 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L24 _public prototype_ `virtual void PopulateSearchStrings(const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings) const override;`
- L26 _public function_ `virtual bool SupportsSorting() const override`
- L28 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const override;`
- L30 _public member_ `const static FName ColumnID;`
- L34 _private prototype_ `void OnPreviewSystemIsDoneProcessing();` — Request a sort refresh if this column was the one doing the sorting
- L36 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`
- L38 _private member_ `TSharedPtr<FDataprepPreviewSystem> CachedPreviewData;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/PreviewSystem/DataprepPreviewSystem.h` (Private)


#### enum `EDataprepPreviewStatus`  
`enum class EDataprepPreviewStatus : uint8`  
_L18-25_
- L20 _public enumerator_ `BeingProcessed`
- L21 _public enumerator_ `NotSupported`
- L22 _public enumerator_ `Failed`
- L23 _public enumerator_ `Pass`

#### enum `EDataprepPreviewResultComparison`  
`enum class EDataprepPreviewResultComparison : uint8`  
_L27-32_
- L29 _public enumerator_ `SmallerThan`
- L30 _public enumerator_ `Equal`
- L31 _public enumerator_ `BiggerThan`

#### struct `FDataprepPreviewProcessingResult`  
`struct FDataprepPreviewProcessingResult`  
_L34-51_
- L36 _public function_ `FDataprepPreviewProcessingResult() : Status( EDataprepPreviewStatus::BeingProcessed ) , CurrentProcessingIndex( 0 ) , FetchedData()`
- L42 _public prototype_ `EDataprepPreviewResultComparison CompareFetchedDataTo(const FDataprepPreviewProcessingResult& Other);`
- L44 _public prototype_ `FText GetFetchedDataAsText() const;`
- L46 _public prototype_ `void PopulateSearchStringFromFetchedData(TArray<FString>& OutStrings) const;`
- L48 _public member_ `EDataprepPreviewStatus Status;`
- L49 _public member_ `uint32 CurrentProcessingIndex;`
- L50 _public member_ `FFilterVariantData FetchedData;`

#### class `FDataprepPreviewSystem`  
`class FDataprepPreviewSystem final : public FGCObject, public FTickableEditorObject, public TSharedFromThis<FDataprepPreviewSystem>`  
_L56-177_
- inherits: `FGCObject,FTickableEditorObject,TSharedFromThis<FDataprepPreviewSystem>`
- desc: A class managing the responsibility of processing the data for the preview of the result of a filter
- L59 _public prototype_ `FDataprepPreviewSystem() = default;`
- L60 _public prototype_ `virtual ~FDataprepPreviewSystem();`
- L62 _public prototype_ `FDataprepPreviewSystem(const FDataprepPreviewSystem&) = delete;`
- L63 _public prototype_ `FDataprepPreviewSystem(FDataprepPreviewSystem&&) = delete;`
- L64 _public prototype_ `FDataprepPreviewSystem& operator=(const FDataprepPreviewSystem&) = delete;`
- L65 _public prototype_ `FDataprepPreviewSystem& operator=(FDataprepPreviewSystem&&) = delete;`
- L68 _public prototype_ `void UpdateDataToProcess(const TArrayView<UObject*>& Objects);` — Update the data to process
- L70 _public prototype_ `void SetObservedObjects(const TArrayView<UDataprepParameterizableObject*>& Objects);`
- L72 _public function_ `bool HasObservedObjects() const`
- L75 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L76 _public function_ `virtual FString GetReferencerName() const override`
- L82 _public prototype_ `TSharedPtr<FDataprepPreviewProcessingResult> GetPreviewDataForObject(UObject* Object) const;`
- L85 _public prototype_ `void RestartProcessing();` — Reset the processing from the start
- L88 _public prototype_ `void ClearProcessing();` — Cancel any ongoing processing
- L90 _public prototype_ `bool HasAnObjectObserved(const TArrayView<UDataprepParameterizableObject*>& StepObjects) const;`
- L93 _public prototype_ `bool IsObservingStepObject(const UDataprepParameterizableObject* StepObject) const;` — Is the preview system observing the object
- L96 _public function_ `int32 GetObservedStepsCount() const` — Return the current number of the step observed
- L102 _public prototype_ `void EnsureValidityOfTheObservedObjects();` — Check if the observed object are valid and also check if the observed object are in the right order If an observed object is invalid clear the preview
- L105 _public function_ `DECLARE_EVENT(FDataprepPreviewSystem, FOnPreviewIsDoneProcessing) FOnPreviewIsDoneProcessing& GetOnPreviewIsDoneProcessing()` — Broadcast when the preview system is done processing the data to preview
- L110 _private prototype_ `void IncrementalProcess();`
- L117 _private prototype_ `int32 FillObjectsBuffer(int32 MaximunNumberOfObject);` — Fill the object buffer from the current iterator and update the current progress @param MaximunNumberOfObject Useful if we don't want to fill all the buffer @return the number of object inserted into the buffer
- L122 _private prototype_ `void PrepareFilterBuffers(int32 DesiredSize);` — Ensure that buffer are of the proper size
- L128 _private prototype_ `void PopulateResultFromFilter(int32 NumberOfValidObjects);` — Migrate the result of the filter from the buffer to the preview result map @param NumberOfValidObjects Allow to stop before the end of the buffer it wasn't fully use
- L130 _private prototype_ `void StopTrackingObservedObjects();`
- L132 _private prototype_ `void OnObservedObjectPostEdit(UDataprepParameterizableObject& Object, FPropertyChangedChainEvent& PropertyChangedChainEvent);`
- L137 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L138 _public function_ `virtual bool IsTickable() const override`
- L139 _public prototype_ `virtual TStatId GetStatId() const override;`
- L144 _private member_ `TObjectPtr<UDataprepActionAsset> ObservedActionAsset;` — The action from which the step object are previewed
- L145 _private member_ `FDelegateHandle OnActionStepOrderChangedHandle;`
- L148 _private member_ `TArray<TObjectPtr<UDataprepParameterizableObject>> ObservedSteps;` — The filters previewed
- L151 _private member_ `TMap<TObjectPtr<UDataprepParameterizableObject>,FDelegateHandle> ObservedOnPostEdit;` — The handle for the PostEditEvents of the observed objects
- L154 _private member_ `TMap<TObjectPtr<UObject>, TSharedRef<FDataprepPreviewProcessingResult>> PreviewResult;` — The inprogress or done result
- L156 _private typedef_ `using FResultIterator = decltype(PreviewResult)::TIterator;`
- L164 _private member_ `} CurrentProgress;`
- L166 _private member_ `bool bIsProcessing = false;`
- L169 _private member_ `TArray<UObject*> ObjectsBuffer;` — Buffers of object to process
- L172 _private member_ `TArray<FDataprepSelectionInfo> FilterResultsBuffer;` — Buffer for the filters
- L174 _private member_ `static const int32 IncrementalCount;`
- L176 _private member_ `FOnPreviewIsDoneProcessing OnPreviewIsDoneProcessing;`

#### struct `FDataprepPreviewSystem::(anonymous)`  
``  
_L160-164_

#### Free symbols / members of external scopes

- L105 _delegate_ `DECLARE_EVENT(FDataprepPreviewSystem, FOnPreviewIsDoneProcessing) FOnPreviewIsDoneProcessing& GetOnPreviewIsDoneProcessing() { return OnPreviewIsDoneProcessing; } private: void IncrementalProcess();` — Broadcast when the preview system is done processing the data to preview
- L161 _member_ `int32 CurrentFilterIndex;` (scope `FDataprepPreviewSystem::__anone47e71730108`)
- L162 _member_ `int32 CurrentObjectProcessed;` (scope `FDataprepPreviewSystem::__anone47e71730108`)
- L163 _member_ `TUniquePtr<FResultIterator> Iterator;` (scope `FDataprepPreviewSystem::__anone47e71730108`)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepAllMenuActionCollector.h` (Private)


#### class `FDataprepAllMenuActionCollector`  
`class FDataprepAllMenuActionCollector : public IDataprepMenuActionCollector`  
_L13-18_
- inherits: `IDataprepMenuActionCollector`
- desc: Help collecting all the dataprep specific menu action (operations and filters)
- L16 _public prototype_ `virtual TArray<TSharedPtr<FDataprepSchemaAction>> CollectActions() override;`
- L17 _public prototype_ `virtual bool ShouldAutoExpand() override;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepDragDropOp.h` (Private)


#### class `FDataprepDragDropOp`  
`class FDataprepDragDropOp : public FGraphEditorDragDropAction`  
_L30-126_
- inherits: `FGraphEditorDragDropAction`
- desc: The Dataprep drag and drop is a specialized  drag and drop that can interact with the dataprep action nodes. When dropped on a dataprep action node it will do a callback on the Dataprep Graph Operation. If dropped on a compatible graph, the dataprep drag and drop operation will create a new dataprep action node and execute the callback that new node
- L33 _public prototype_ `FDataprepDragDropOp();`
- L35 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDataprepDragDropOp, FGraphEditorDragDropAction) static TSharedRef<FDataprepDragDropOp> New(TSharedRef<FDataprepSchemaAction> InAction);`
- L38 _public prototype_ `static TSharedRef<FDataprepDragDropOp> New(FDataprepGraphOperation&& GraphOperation);`
- L39 _public prototype_ `static TSharedRef<FDataprepDragDropOp> New(const TSharedRef<SDataprepGraphTrackNode>& InTrackNode, const TSharedRef<SDataprepGraphActionStepNode>& InDraggedNode);`
- L40 _public prototype_ `static TSharedRef<FDataprepDragDropOp> New(UDataprepActionStep* InActionStep);`
- L42 _public prototype_ `void SetHoveredDataprepActionContext(TOptional<FDataprepSchemaActionContext> Context);`
- L44 _public prototype_ `virtual FReply DroppedOnDataprepActionContext(const FDataprepSchemaActionContext& Context);`
- L47 _public prototype_ `virtual void HoverTargetChanged() override;` — FGraphEditorDragDropAction Interface
- L48 _public prototype_ `virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L49 _public prototype_ `virtual void OnDragged (const class FDragDropEvent& DragDropEvent ) override;`
- L50 _public prototype_ `virtual EVisibility GetIconVisible() const;`
- L51 _public prototype_ `virtual EVisibility GetErrorIconVisible() const;`
- L52 _public prototype_ `virtual void Construct() override;`
- L61 _public prototype_ `FReply DoDropOnTrack(UDataprepAsset* TargetDataprepAsset, int32 InsertIndex);` — Executes drop on track. A new action will inserted at the specified index. @param InsertIndex Index at which to insert the new action. The action will be inserted at the end if the index is not a valid one @return FReply::handled.
- L64 _public prototype_ `void SetPreDropConfirmation(FDataprepPreDropConfirmation && Confirmation);` — Allow to add an extra step to the drag and drop before doing the dropping
- L67 _public prototype_ `UDataprepGraphActionStepNode* GetDropTargetNode() const;` — Returns action step node targeted for the drop
- L69 _public function_ `void SetTrackNode(const TSharedPtr<SDataprepGraphTrackNode>& InTrackNodePtr)`
- L74 _public function_ `bool IsValidDrop()`
- L77 _protected typedef_ `typedef FGraphEditorDragDropAction Super;`
- L79 _protected prototype_ `bool DoDropOnDataprepActionContext(const FDataprepSchemaActionContext& Context);`
- L82 _protected prototype_ `FReply DoDropOnActionStep(UDataprepGraphActionStepNode* TargetActionStepNode);` — Executes drop on existing action step
- L85 _protected prototype_ `FReply DoDropOnActionAsset(UDataprepGraphActionNode* TargetActionNode);` — Executes drop on existing action step
- L87 _protected prototype_ `virtual void HoverTargetChangedWithNodes();`
- L89 _protected member_ `TOptional<FDataprepSchemaActionContext> HoveredDataprepActionContext;`
- L91 _protected member_ `FDataprepPreDropConfirmation DataprepPreDropConfirmation;`
- L92 _protected member_ `FDataprepGraphOperation DataprepGraphOperation;`
- L95 _private prototype_ `FText GetMessageText();`
- L97 _private prototype_ `const FSlateBrush* GetIcon() const;`
- L105 _private prototype_ `void DropStepFromPanel(UDataprepActionAsset* TargetActionAsset, int32 InsertIndex = INDEX_NONE);` — Drop a step from the Operation panel to an action. The step will be added or inserted. @param TargetActionAsset Action on which the insertion will be performed @param InsertIndex Index at which the insertion must occur in the existing list of steps. An index of -1 will trigger an addition.
- L108 _private typedef_ `typedef TTuple<TWeakObjectPtr<UDataprepActionAsset>,int32,TWeakObjectPtr<UDataprepActionStep>> FDraggedStepEntry;`
- L111 _private member_ `TWeakPtr<SDataprepGraphTrackNode> TrackNodePtr;` — Graph panel associated with the Dataprep graph editor
- L114 _private member_ `TArray<TSharedRef<SDataprepGraphActionStepNode>> DraggedNodeWidgets;` — Array of action steps being dragged
- L117 _private member_ `TArray<FDraggedStepEntry> DraggedSteps;` — Array of action steps being dragged
- L120 _private member_ `FVector2D DecoratorAdjust;` — Offset information for the decorator widget
- L123 _private member_ `FText LastMessageText;` — Cache last displayed text message
- L125 _private member_ `bool bDropTargetItself;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FDataprepGraphOperation, const FDataprepSchemaActionContext& ) DECLARE_DELEGATE_TwoParams( FDataprepPreDropConfirmation, const FDataprepSchemaActionContext& , TFunction<void ()> ) class FDataprepDragDropOp : public FGraphEditorDragDropAction { public: FDataprepDragDropOp(); DRAG_DROP_OPERATOR_TYPE(FDataprepDragDropOp, FGraphEditorDragDropAction) static TSharedRef<FDataprepDragDropOp> New(TSharedRef<FDataprepSchemaAction> InAction); static TSharedRef<FDataprepDragDropOp> New(FDataprepGraphOperation&& GraphOperation); static TSharedRef<FDataprepDragDropOp> New(const TSharedRef<SDataprepGraphTrackNode>& InTrackNode, const TSharedRef<SDataprepGraphActionStepNode>& InDraggedNode); static TSharedRef<FDataprepDragDropOp> New(UDataprepActionStep* InActionStep); void SetHoveredDataprepActionContext(TOptional<FDataprepSchemaActionContext> Context); virtual FReply DroppedOnDataprepActionContext(const FDataprepSchemaActionContext& Context);` — Return true if there was a modification that require a transaction
- L23 _delegate_ `DECLARE_DELEGATE_TwoParams( FDataprepPreDropConfirmation, const FDataprepSchemaActionContext& , TFunction<void ()> ) class FDataprepDragDropOp : public FGraphEditorDragDropAction { public: FDataprepDragDropOp(); DRAG_DROP_OPERATOR_TYPE(FDataprepDragDropOp, FGraphEditorDragDropAction) static TSharedRef<FDataprepDragDropOp> New(TSharedRef<FDataprepSchemaAction> InAction); static TSharedRef<FDataprepDragDropOp> New(FDataprepGraphOperation&& GraphOperation); static TSharedRef<FDataprepDragDropOp> New(const TSharedRef<SDataprepGraphTrackNode>& InTrackNode, const TSharedRef<SDataprepGraphActionStepNode>& InDraggedNode); static TSharedRef<FDataprepDragDropOp> New(UDataprepActionStep* InActionStep); void SetHoveredDataprepActionContext(TOptional<FDataprepSchemaActionContext> Context); virtual FReply DroppedOnDataprepActionContext(const FDataprepSchemaActionContext& Context);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepFilterMenuActionCollector.h` (Private)


#### class `FDataprepFilterMenuActionCollector`  
`class FDataprepFilterMenuActionCollector : public IDataprepMenuActionCollector`  
_L16-29_
- inherits: `IDataprepMenuActionCollector`
- desc: Help collecting all the dataprep filter menu action
- L19 _public prototype_ `virtual TArray<TSharedPtr<FDataprepSchemaAction>> CollectActions() override;`
- L20 _public prototype_ `virtual bool ShouldAutoExpand() override;`
- L22 _public member_ `int32 GroupingPriority = 0;`
- L24 _public member_ `static const FText FilterCategory;`
- L27 _private prototype_ `TSharedPtr<FDataprepSchemaAction> CreateMenuActionFromClass(UClass& Class, UDataprepFilter& Filter);`
- L28 _private prototype_ `TSharedPtr<FDataprepSchemaAction> CreateMenuActionFromClass(UDataprepFilterNoFetcher& Filter);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepMenuActionCollectorUtils.h` (Private)


#### enum `DataprepMenuActionCollectorUtils::EDataprepMenuActionCategory`  
`enum EDataprepMenuActionCategory`  
_L26-31_
- L28 _public enumerator_ `Filter = 1`
- L29 _public enumerator_ `SelectionTransform`
- L30 _public enumerator_ `Operation`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace DataprepMenuActionCollectorUtils`
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FDataprepSchemaAction>, FOnCreateMenuAction, UClass&);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FDataprepSchemaAction>, FOnCreateMenuAction, UClass&);` (scope `DataprepMenuActionCollectorUtils`)
- L20 _prototype_ `TArray<TSharedPtr<FDataprepSchemaAction>> GatherMenuActionForDataprepClass(UClass& Class, FOnCreateMenuAction OnValidClassFound, bool bIncludeBaseClass = false);` (scope `DataprepMenuActionCollectorUtils`) — Utils to gather the menu action from a base class @param Class The base class from which we want to create the actions @param OnValidClassFound Callback to generate the menu action from the class @param bIncludeBaseClass Should we take into account the base class (Class)
- L22 _prototype_ `TArray<UClass*> GetNativeChildClasses(UClass&);` (scope `DataprepMenuActionCollectorUtils`)
- L24 _variable_ `constexpr EClassFlags NonDesiredClassFlags = CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Abstract;` (scope `DataprepMenuActionCollectorUtils`)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepOperationMenuActionCollector.h` (Private)


#### class `FDataprepOperationMenuActionCollector`  
`class FDataprepOperationMenuActionCollector : public IDataprepMenuActionCollector`  
_L13-22_
- inherits: `IDataprepMenuActionCollector`
- desc: Help collecting all the dataprep operation menu action
- L16 _public prototype_ `virtual TArray<TSharedPtr<FDataprepSchemaAction>> CollectActions() override;`
- L17 _public prototype_ `virtual bool ShouldAutoExpand() override;`
- L19 _public member_ `static const FText OperationCategory;`
- L21 _private prototype_ `TSharedPtr<FDataprepSchemaAction> CreateMenuActionFromClass(UClass& Class);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepSchemaAction.h` (Private)


#### struct `FDataprepSchemaActionContext`  
`struct FDataprepSchemaActionContext`  
_L12-29_
- desc: This is the context on which a dataprep menu action will operate.
- L15 _public function_ `FDataprepSchemaActionContext() : DataprepActionPtr() , DataprepActionStepPtr() , StepIndex( INDEX_NONE )`
- L22 _public member_ `TWeakObjectPtr<class UDataprepActionAsset> DataprepActionPtr;` — The action targeted
- L25 _public member_ `TWeakObjectPtr<class UDataprepActionStep> DataprepActionStepPtr;` — The step targeted
- L28 _public member_ `int32 StepIndex;` — Index of the step targeted (only valid if there is a action step otherwise should be INDEX_NONE)

#### struct `FDataprepSchemaAction`  
`struct FDataprepSchemaAction : public FEdGraphSchemaAction`  
_L48-84_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: The DataprepSchemaAction is the data structure used to populate the Dataprep action menu and the Dataprep palette
- L53 _public function_ `static FName StaticGetTypeId()` — Simple type info.
- L54 _public function_ `virtual FName GetTypeId() const`
- L56 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnExecuteAction, const FDataprepSchemaActionContext& );`
- L58 _public function_ `FDataprepSchemaAction()`
- L64 _public member_ `FString GeneratedClassObjectPath;` — If the class associated with this action is blueprint generated, this is its path
- L66 _public member_ `FText ActionCategory;`
- L78 _public prototype_ `FDataprepSchemaAction(FText InActionCategory, FText InMenuDescription, FText InToolTip, const int32 InGrouping, FText InKeywords, const FOnExecuteAction& InAction, int32 InSectionID = 0);` — Create a DataprepSchemaAction @param InActionCategory The category in which the action will be displayed @param InMenuDescription The text displayed in the menu for this action @param InToolTip The tooltip that should be displayed for this action @param InGrouping This is a priority number that allow to override the alphabetical order. (higher value == higher in the list) @param InKeywords Allow to add some extra text for the search to match on @param InAction The function that will be executed if this action is selected @param InSectionID The section where this action belongs
- L80 _public prototype_ `bool ExecuteAction(const FDataprepSchemaActionContext& Context);`
- L83 _private member_ `FOnExecuteAction Action;`

#### Free symbols / members of external scopes

- L31 _function_ `bool inline operator==(const FDataprepSchemaActionContext& Left, const FDataprepSchemaActionContext& Right)`
- L38 _function_ `bool inline operator!=(const FDataprepSchemaActionContext& Left, const FDataprepSchemaActionContext& Right)`
- L56 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExecuteAction, const FDataprepSchemaActionContext& );`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepSchemaActionUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DataprepSchemaActionUtils`
- L10 _function_ `template<class GraphNodeClass> GraphNodeClass* SpawnEdGraphNode(UEdGraph& ParentGraph, const FVector2D& Location)` (scope `DataprepSchemaActionUtils`)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/DataprepSelectionTransformMenuActionCollector.h` (Private)


#### class `FDataprepSelectionTransformMenuActionCollector`  
`class FDataprepSelectionTransformMenuActionCollector : public IDataprepMenuActionCollector`  
_L13-23_
- inherits: `IDataprepMenuActionCollector`
- desc: Help collecting all the dataprep selection transform menu action
- L16 _public prototype_ `virtual TArray<TSharedPtr<FDataprepSchemaAction>> CollectActions() override;`
- L17 _public prototype_ `virtual bool ShouldAutoExpand() override;`
- L19 _public member_ `int32 GroupingPriority = 0;`
- L22 _private prototype_ `TSharedPtr<FDataprepSchemaAction> CreateMenuActionFromClass(UClass& Class);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/SchemaActions/IDataprepMenuActionCollector.h` (Private)


#### class `IDataprepMenuActionCollector`  
`class IDataprepMenuActionCollector`  
_L13-24_
- desc: The DataprepActionCollector is an interface for the SDataprepActionMenu
- L17 _public function_ `virtual ~IDataprepMenuActionCollector()`
- L20 _public prototype_ `virtual TArray<TSharedPtr<FDataprepSchemaAction>> CollectActions() = 0;` — The function that will be called to collect all the actions
- L23 _public prototype_ `virtual bool ShouldAutoExpand() = 0;` — Should the categories be auto expended

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepAssetView.h` (Private)


#### class `SDataprepAssetView`  
`class SDataprepAssetView : public SCompoundWidget`  
_L23-63_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SDataprepAssetView)`
- L27 _public prototype_ `SLATE_ARGUMENT(FDataprepImportProducers, DataprepImportProducersDelegate) SLATE_ARGUMENT(FDataprepImportProducersEnabled, DataprepImportProducersEnabledDelegate) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepAssetInterface* InDataprepAssetPtr);`
- L33 _public prototype_ `~SDataprepAssetView();`
- L36 _private prototype_ `void OnNewConsumerSelected( TSharedPtr<FString> NewConsumer, ESelectInfo::Type SelectInfo);`
- L39 _private prototype_ `void OnDataprepAssetChanged(FDataprepAssetChangeType ChangeType);` — Handles changes in the Dataprep asset
- L41 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForCategoryTree( TSharedRef<EDataprepCategory> InTreeNode, const TSharedRef<STableViewBase>& InOwnerTable );`
- L42 _private function_ `void OnGetChildrenForCategoryTree( TSharedRef<EDataprepCategory> InTreeNode, TArray< TSharedRef<EDataprepCategory> >& OutChildren )`
- L44 _private member_ `TArray<TSharedRef< EDataprepCategory >> Categories;`
- L47 _private member_ `TWeakObjectPtr<UDataprepAssetInterface> DataprepAssetInterfacePtr;`
- L48 _private member_ `TSharedPtr<SDataprepProducersWidget> ProducersWidget;`
- L49 _private member_ `TSharedPtr< STextBlock > CheckBox;`
- L50 _private member_ `TArray< TSharedPtr< FString > > ConsumerDescriptionList;`
- L51 _private member_ `TMap< TSharedPtr< FString >, UClass* > ConsumerDescriptionMap;`
- L52 _private member_ `TSharedPtr< FString > SelectedConsumerDescription;`
- L53 _private member_ `TSharedPtr< SWidget > ConsumerSelector;`
- L54 _private member_ `bool bIsChecked;`
- L56 _private member_ `FDataprepImportProducers DataprepImportProducersDelegate;`
- L57 _private member_ `FDataprepImportProducersEnabled DataprepImportProducersEnabledDelegate;`
- L60 _private member_ `TSharedPtr< FDetailColumnSizeData > ColumnSizeData;` — Container used by all splitters in the details view, so that they move in sync
- L62 _private member_ `FDelegateHandle OnParameterizationWasEdited;`

#### class `SGraphNodeDetailsWidget`  
`class SGraphNodeDetailsWidget : public SCompoundWidget`  
_L66-126_
- inherits: `SCompoundWidget`
- desc: Inspired from SKismetInspector class
- L69 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeDetailsWidget)`
- L73 _public prototype_ `void Construct(const FArguments& InArgs);`
- L75 _public prototype_ `void ShowDetailsObjects(const TArray<UObject*>& Objects);`
- L77 _public function_ `void SetCanEditProperties(bool bInCanEditProperties)`
- L78 _public function_ `bool GetCanEditProperties() const`
- L79 _public function_ `const TArray< TWeakObjectPtr<UObject> >& GetObjectsShowInDetails() const`
- L82 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L87 _private prototype_ `void UpdateFromObjects(const TArray<UObject*>& PropertyObjects, bool bSelfUpdate = false);` — Update the inspector window to show information on the supplied objects
- L90 _private prototype_ `void AddPropertiesRecursive(FProperty* Property);` — Add this property and all its child properties to SelectedObjectProperties
- L92 _private prototype_ `void OnSCSEditorTreeViewSelectionChanged(const TArray<TSharedPtr<FSubobjectEditorTreeNode>>& SelectedNodes);`
- L96 _private member_ `TSharedPtr<IDetailsView> PropertyView;` — Property viewing widget
- L99 _private member_ `TSharedPtr<SBorder> ContextualEditingBorderWidget;` — Border widget that wraps a dynamic context-sensitive widget for editing objects that the property window is displaying
- L102 _private member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;` — Selected objects for this detail view
- L105 _private member_ `TSet<TWeakFieldPtr<FProperty> > SelectedObjectProperties;` — Set of object properties that should be visible
- L108 _private member_ `TSharedPtr<SSplitter> DetailsSplitter;` — The splitter that divides object properties and components tree
- L111 _private member_ `TSharedPtr<SSubobjectEditor> SubobjectEditor;` — Component tree
- L114 _private member_ `TSharedPtr<class FDataprepSCSEditorUICustomization> SubobjectEditorUICustomization;` — Customize how the component tree looks like
- L117 _private member_ `AActor* SelectedActor;` — The first actor in the currently selected objects
- L120 _private member_ `bool bRefreshOnTick;` — When TRUE, the SGraphNodeDetailsWidget needs to refresh the details view on Tick
- L122 _private member_ `bool bCanEditProperties;`
- L125 _private member_ `TArray<UObject*> RefreshPropertyObjects;` — Holds the property objects that need to be displayed by the inspector starting on the next tick

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/DataprepActionWidgetsUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DataprepActionWidgetsUtils`
- L14 _function_ `template<class EnumType> void GenerateListEntriesFromEnum(TArray<TSharedPtr<TTuple<FText, FText, int32>>>& Entries)` (scope `DataprepActionWidgetsUtils`) — Fill an array with the reflexions data of a Enum for a SComboBox or others. The Tuple can described as the following (Displayed text, Tooltip and a mapping for the UEnum)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepActionBlock.h` (Private)


#### class `SDataprepActionBlock`  
`class SDataprepActionBlock : public SCompoundWidget`  
_L13-79_
- inherits: `SCompoundWidget`
- desc: The SDataprepActionBlock is the base class that is used for the block that compose a dataprep action
- L15 _private function_ `SLATE_BEGIN_ARGS(SDataprepActionBlock)`
- L16 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDataprepSchemaActionContext>& DataprepActionContext);`
- L21 _private function_ `virtual FVector2D ComputeDesiredSize(float) const override` — SWidget Interface
- L31 _private prototype_ `virtual FSlateColor GetOutlineColor() const;` — Return the outline color
- L36 _public prototype_ `TSharedRef<SWidget> GetBlockTitleWidget();` — Return the block title
- L41 _public prototype_ `virtual TSharedRef<SWidget> GetTitleWidget();` — Return the title widget
- L48 _protected prototype_ `virtual FText GetBlockTitle() const;` — Return the block title. This is used in the implementation of SDataprepActionBlock::GetTitleWidget
- L53 _protected prototype_ `TSharedRef<SWidget> GetTitleBackgroundWidget();` — Get title background widget
- L58 _protected prototype_ `virtual TSharedRef<SWidget> GetContentWidget();` — Return the content widget
- L63 _protected prototype_ `TSharedRef<SWidget> GetContentBackgroundWidget();` — Get content background widget
- L69 _protected prototype_ `virtual void PopulateMenuBuilder(class FMenuBuilder& MenuBuilder);` — Populate the right click menu by overriding this function. Call the parent implementation if you want the full menu.
- L76 _private prototype_ `void DeleteStep();` — Delete this step
- L78 _private member_ `TSharedPtr<FDataprepSchemaActionContext> DataprepActionContext;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepActionSteps.h` (Private)


#### class `SDataprepActionStep`  
`class SDataprepActionStep : public SCompoundWidget`  
_L16-36_
- inherits: `SCompoundWidget`
- desc: The widget that display and manage zone where a action step is displayed
- L19 _public function_ `SLATE_BEGIN_ARGS(SDataprepActionStep)`
- L20 _public prototype_ `SLATE_END_ARGS();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDataprepSchemaActionContext>& InStepData);`
- L25 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — SWidget Interface
- L26 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L28 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L29 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L30 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L35 _private member_ `TSharedPtr<FDataprepSchemaActionContext> StepData;`

#### class `SDataprepActionSteps`  
`class SDataprepActionSteps : public SCompoundWidget`  
_L41-61_
- inherits: `SCompoundWidget`
- desc: This is the widget that display the steps of dataprep action
- L44 _public function_ `SLATE_BEGIN_ARGS(SDataprepActionSteps)`
- L45 _public prototype_ `SLATE_END_ARGS();`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, UDataprepActionAsset* InDataprepAction);`
- L51 _private prototype_ `void OnStepsOrderChanged();`
- L54 _private prototype_ `void Refresh();` — Update the display of the steps
- L56 _private member_ `TWeakObjectPtr<UDataprepActionAsset> DataprepActionPtr;`
- L58 _private member_ `TSharedPtr<class SVerticalBox> StepsList;`
- L60 _private member_ `TArray<TSharedPtr<FDataprepSchemaActionContext>> Steps;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepBoolFilter.h` (Private)


#### class `SDataprepBoolFilter`  
`class SDataprepBoolFilter : public SCompoundWidget`  
_L9-15_
- inherits: `SCompoundWidget`
- L11 _private function_ `SLATE_BEGIN_ARGS(SDataprepBoolFilter)`
- L12 _private prototype_ `SLATE_END_ARGS();`
- L14 _private prototype_ `void Construct(const FArguments& InArgs, UDataprepBoolFilter& InFilter);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepFilter.h` (Private)


#### class `SDataprepFilter`  
`class SDataprepFilter : public SDataprepActionBlock, public FGCObject`  
_L15-56_
- inherits: `SDataprepActionBlock,FGCObject`
- L18 _public function_ `SLATE_BEGIN_ARGS(SDataprepFilter) : _IsPreviewed(false)`
- L21 _public prototype_ `SLATE_ARGUMENT( bool, IsPreviewed ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepFilter& InFilter, const TSharedRef<FDataprepSchemaActionContext>& InDataprepActionContext);`
- L26 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L31 _protected prototype_ `virtual FSlateColor GetOutlineColor() const override;` — SDataprepActionBlock interface
- L32 _protected prototype_ `virtual FText GetBlockTitle() const override;`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> GetTitleWidget() override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> GetContentWidget() override;`
- L35 _protected prototype_ `virtual void PopulateMenuBuilder(class FMenuBuilder& MenuBuilder) override;`
- L40 _private prototype_ `void InverseFilter();`
- L42 _private prototype_ `FText GetTooltipText() const;`
- L45 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L46 _private function_ `virtual FString GetReferencerName() const override`
- L51 _private member_ `TSharedPtr<class SDataprepDetailsView> DetailsView;`
- L53 _private member_ `TObjectPtr<UDataprepFilter> Filter = nullptr;`
- L55 _private member_ `bool bIsPreviewed;`

#### class `SDataprepFilterNoFetcher`  
`class SDataprepFilterNoFetcher : public SDataprepActionBlock, public FGCObject`  
_L58-99_
- inherits: `SDataprepActionBlock,FGCObject`
- L61 _public function_ `SLATE_BEGIN_ARGS(SDataprepFilterNoFetcher) : _IsPreviewed(false)`
- L64 _public prototype_ `SLATE_ARGUMENT( bool, IsPreviewed ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepFilterNoFetcher& InFilter, const TSharedRef<FDataprepSchemaActionContext>& InDataprepActionContext);`
- L69 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L74 _protected prototype_ `virtual FSlateColor GetOutlineColor() const override;` — SDataprepActionBlock interface
- L75 _protected prototype_ `virtual FText GetBlockTitle() const override;`
- L76 _protected prototype_ `virtual TSharedRef<SWidget> GetTitleWidget() override;`
- L77 _protected prototype_ `virtual TSharedRef<SWidget> GetContentWidget() override;`
- L78 _protected prototype_ `virtual void PopulateMenuBuilder(class FMenuBuilder& MenuBuilder) override;`
- L83 _private prototype_ `void InverseFilter();`
- L85 _private prototype_ `FText GetTooltipText() const;`
- L88 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L89 _private function_ `virtual FString GetReferencerName() const override`
- L94 _private member_ `TSharedPtr<class SDataprepDetailsView> DetailsView;`
- L96 _private member_ `TObjectPtr<UDataprepFilterNoFetcher> Filter = nullptr;`
- L98 _private member_ `bool bIsPreviewed;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepFloatFilter.h` (Private)


#### class `SDataprepFloatFilter`  
`class SDataprepFloatFilter : public SCompoundWidget, public FGCObject`  
_L20-85_
- inherits: `SCompoundWidget,FGCObject`
- L22 _private function_ `SLATE_BEGIN_ARGS(SDataprepFloatFilter)`
- L23 _private prototype_ `SLATE_END_ARGS();`
- L25 _private prototype_ `void Construct(const FArguments& InArgs, UDataprepFloatFilter& InFilter);`
- L27 _private prototype_ `virtual ~SDataprepFloatFilter();`
- L32 _private prototype_ `void UpdateVisualDisplay();` — Refresh the ui
- L35 _private typedef_ `using FListEntry = TTuple<FText, FText, int32>;` — The string matching option for the combo box (Displayed text, Tooltip, mapping for the UEnum)
- L38 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForMatchingCriteria(TSharedPtr<FListEntry> ListEntry) const;` — Those function are for the float matching criteria display
- L39 _private prototype_ `FText GetSelectedCriteriaText() const;`
- L40 _private prototype_ `FText GetSelectedCriteriaTooltipText() const;`
- L41 _private prototype_ `void OnSelectedCriteriaChanged(TSharedPtr<FListEntry> ListEntry, ESelectInfo::Type SelectionType);`
- L42 _private prototype_ `void OnCriteriaComboBoxOpenning();`
- L43 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForMatchingCriteria();`
- L46 _private prototype_ `float GetEqualValue() const;` — Those functions are for the float that will be compare against the fetched float
- L47 _private prototype_ `void OnEqualValueChanged(float NewEqualValue);`
- L48 _private prototype_ `void OnEqualValueComitted(float NewEqualValue, ETextCommit::Type CommitType);`
- L49 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForEqualValue();`
- L50 _private prototype_ `void ExtendContextMenuForEqualValueBox(FMenuBuilder& MenuBuilder);`
- L53 _private prototype_ `EVisibility GetToleranceRowVisibility() const;` — Those function are for the tolerance display
- L54 _private prototype_ `float GetTolerance() const;`
- L55 _private prototype_ `void OnToleranceChanged(float NewTolerance);`
- L56 _private prototype_ `void OnToleranceComitted(float NewTolerance, ETextCommit::Type CommitType);`
- L57 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForTolerance();`
- L58 _private prototype_ `void ExtendContextMenuForToleranceBox(FMenuBuilder& MenuBuilder);`
- L61 _private prototype_ `void OnParameterizationStatusForObjectsChanged(const TSet<UObject*>* Objects);` — Event for dataprep parameterization
- L64 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L65 _private function_ `virtual FString GetReferencerName() const override`
- L71 _private member_ `float OldEqualValue;`
- L72 _private member_ `float OldTolerance;`
- L74 _private member_ `TObjectPtr<UDataprepFloatFilter> Filter;`
- L76 _private member_ `TArray<TSharedPtr<FListEntry>> FloatMatchingOptions;`
- L78 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FListEntry>>> FloatMatchingCriteriaWidget;`
- L80 _private member_ `TSharedPtr<FDataprepParametrizationActionData> MatchingCriteriaParameterizationActionData;`
- L81 _private member_ `TSharedPtr<FDataprepParametrizationActionData> EqualValueParameterizationActionData;`
- L82 _private member_ `TSharedPtr<FDataprepParametrizationActionData> ToleranceParameterizationActionData;`
- L84 _private member_ `FDelegateHandle OnParameterizationStatusForObjectsChangedHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
- L9 _namespace_ `namespace ETextCommit`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepGraphActionNode.h` (Private)


#### class `SDataprepGraphBaseActionNode`  
`class SDataprepGraphBaseActionNode : public SGraphNodeResizable`  
_L20-81_
- inherits: `SGraphNodeResizable`
- desc: Base class for graph action nodes
- L23 _public prototype_ `void Initialize(TWeakPtr<FDataprepEditor> InDataprepEditor, int32 InExecutionOrder, UEdGraphNode* InNode);`
- L25 _public function_ `virtual void SetParentTrackNode(TSharedPtr<SDataprepGraphTrackNode> InParentTrackNode)`
- L30 _public prototype_ `virtual UDataprepActionAsset* GetDataprepAction() = 0;`
- L32 _public function_ `virtual bool IsActionGroup() const`
- L34 _public function_ `TSharedPtr<SDataprepGraphTrackNode> GetParentTrackNode()`
- L36 _public function_ `int32 GetExecutionOrder() const`
- L38 _public prototype_ `virtual void UpdateExecutionOrder() = 0;`
- L41 _public prototype_ `void UpdateProxyNode(const FVector2D& Position);` — Update the proxy node with relative position in track node
- L43 _public prototype_ `FMargin GetOuterPadding() const;`
- L46 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface
- L50 _public prototype_ `virtual FVector2D ComputeDesiredSize(float f) const override;`
- L54 _public prototype_ `virtual FVector2f GetNodeMinimumSize2f() const override;`
- L55 _public prototype_ `virtual FVector2f GetNodeMaximumSize2f() const override;`
- L62 _protected member_ `TSharedPtr<SDataprepGraphActionProxyNode> ProxyNodePtr;` — Pointer to the proxy SGraphNode inserted in the graph panel
- L65 _protected member_ `TWeakPtr<SDataprepGraphTrackNode> ParentTrackNodePtr;` — Pointer to the SDataprepGraphTrackNode displayed in the graph editor
- L68 _protected member_ `TWeakPtr<FDataprepEditor> DataprepEditor;` — A optional ptr to a dataprep editor
- L71 _protected member_ `int32 ExecutionOrder;` — Order in which the associated action will be executed by the Dataprep asset
- L74 _protected member_ `int32 DraggedIndex;` — Index of step node being dragged
- L77 _public member_ `static float DefaultWidth;`
- L78 _public member_ `static float DefaultHeight;`
- L80 _public prototype_ `static TSharedRef<SWidget> CreateBackground(const TAttribute<FSlateColor>& ColorAndOpacity);`

#### class `SDataprepGraphActionNode`  
`class SDataprepGraphActionNode : public SDataprepGraphBaseActionNode`  
_L87-154_
- inherits: `SDataprepGraphBaseActionNode`
- desc: The SDataprepGraphActionNode class is the SGraphNode associated to an UDataprepGraphActionNode to display the action's steps in a SDataprepGraphEditor.
- L90 _public function_ `SLATE_BEGIN_ARGS(SDataprepGraphActionNode)`
- L91 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FDataprepEditor>, DataprepEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepGraphActionNode* InActionNode);`
- L97 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L98 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L99 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L100 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L101 _public prototype_ `virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;`
- L102 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L106 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L107 _public prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L108 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L109 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L113 _public prototype_ `virtual void UpdateExecutionOrder() override;` — SDataprepGraphBaseActionNode interface
- L114 _public function_ `virtual UDataprepActionAsset* GetDataprepAction() override`
- L115 _public prototype_ `virtual void SetParentTrackNode(TSharedPtr<SDataprepGraphTrackNode> InParentTrackNode) override;`
- L119 _public prototype_ `FSlateColor GetInsertColor(int32 Index);` — Callback used by insert nodes to determine their background color
- L122 _public prototype_ `void SetDraggedIndex(int32 Index);` — Set index of step node being dragged
- L125 _public function_ `int32 GetHoveredIndex()` — Get/Set index of step node being hovered
- L126 _public prototype_ `void SetHoveredIndex(int32 Index);`
- L130 _private prototype_ `void OnStepsChanged();` — Callback to handle changes on array of steps in action
- L133 _private prototype_ `void PopulateActionStepListWidget();` — Reconstructs the list of widgets associated with the action's steps
- L135 _private prototype_ `FText GetBottomWidgetText() const;`
- L139 _private member_ `TWeakObjectPtr<class UDataprepActionAsset> DataprepActionPtr;` — Weak pointer to the associated action asset
- L142 _private member_ `TSharedPtr<SVerticalBox> ActionStepListWidgetPtr;` — Pointer to widget containing all the SDataprepGraphActionStepNode representing the associated action's steps
- L145 _private member_ `TArray<TSharedPtr<SDataprepGraphActionStepNode>> ActionStepGraphNodes;` — Array of pointers to the SDataprepGraphActionStepNode representing the associated action's steps
- L148 _private member_ `int32 InsertIndex;` — Index of insert widget to be highlighted
- L151 _private member_ `TArray<TStrongObjectPtr<UDataprepGraphActionStepNode>> EdGraphStepNodes;` — Array of strong pointers to the UEdGraphNodes created for the action's steps
- L153 _private member_ `TSharedPtr<class SButton> ExpandActionButton;`

#### class `SDataprepGraphActionGroupNode`  
`class SDataprepGraphActionGroupNode : public SDataprepGraphBaseActionNode`  
_L158-213_
- inherits: `SDataprepGraphBaseActionNode`
- L161 _public function_ `SLATE_BEGIN_ARGS(SDataprepGraphActionGroupNode)`
- L162 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FDataprepEditor>, DataprepEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepGraphActionGroupNode* InActionNode);`
- L168 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L169 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L170 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L171 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L172 _public prototype_ `virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;`
- L173 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L177 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L178 _public prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L179 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L180 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L184 _public prototype_ `virtual void SetParentTrackNode(TSharedPtr<SDataprepGraphTrackNode> InParentTrackNode) override;` — SDataprepGraphBaseActionNode interface
- L185 _public function_ `virtual bool IsActionGroup() const override`
- L186 _public prototype_ `virtual void UpdateExecutionOrder() override;`
- L190 _public function_ `virtual UDataprepActionAsset* GetDataprepAction()` — Return first action
- L195 _public function_ `UDataprepActionAsset* GetAction(int32 InIndex)`
- L200 _public prototype_ `int32 GetNumActions() const;`
- L203 _private prototype_ `void PopulateActionsListWidget();`
- L206 _private member_ `TSharedPtr<SVerticalBox> ActionsListWidgetPtr;` — Pointer to widget containing all the SDataprepGraphActionNode representing the associated actions in the group
- L209 _private member_ `TArray<TSharedPtr<SDataprepGraphActionNode>> ActionGraphNodes;` — Array of pointers to the SDataprepGraphActionNode representing the associated actions
- L212 _private member_ `TArray<TStrongObjectPtr<UDataprepGraphActionNode>> EdGraphActionNodes;` — Array of strong pointers to the UEdGraphNodes created for the action's steps

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepGraphActionStepNode.h` (Private)


#### class `SDataprepGraphActionStepNode`  
`class SDataprepGraphActionStepNode : public SGraphNode`  
_L21-95_
- inherits: `SGraphNode`
- desc: The SDataprepGraphActionStepNode class is the SGraphNode associated to an UDataprepGraphActionStepNode to display the step of an action in a SDataprepGraphEditor.
- L24 _public function_ `SLATE_BEGIN_ARGS(SDataprepGraphActionStepNode)`
- L25 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FDataprepEditor>, DataprepEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepGraphActionStepNode* InActionStepNode, const TSharedPtr<SDataprepGraphActionNode>& InParent);`
- L31 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — SWidget interface
- L32 _public prototype_ `FReply OnMouseButtonUp( const FGeometry & MyGeometry, const FPointerEvent & MouseEvent ) override;`
- L33 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent) override;`
- L34 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L38 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L39 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L40 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L41 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L42 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L43 _public function_ `virtual bool IsNameReadOnly () const override`
- L44 _public function_ `virtual FSlateRect GetTitleRect() const override`
- L47 _public function_ `int32 GetStepIndex() const`
- L48 _public function_ `void SetStepIndex( int32 InStepIndex )`
- L51 _public prototype_ `virtual TSharedPtr<SWidget> GetStepTitleWidget() const;` — Returns a pointer to a widget displaying only the title of the action step
- L53 _public prototype_ `void SetParentTrackNode(TSharedPtr<SDataprepGraphTrackNode> InParentTrackNode);`
- L55 _public function_ `TWeakPtr<SDataprepGraphActionNode> GetParentNode() const`
- L61 _private prototype_ `FSlateColor GetBorderBackgroundColor() const;` — Returns a color depending whether the action step is selected or not
- L65 _private prototype_ `FSlateColor GetDragAndDropColor() const;` — Returns a color depending whether the action step is hovered or not
- L67 _private prototype_ `FSlateColor GetBlockOverlayColor() const;`
- L69 _private prototype_ `FMargin GetBlockPadding();`
- L70 _private prototype_ `FMargin GetBlockDisabledPadding();`
- L72 _private prototype_ `FMargin GetArrowPadding();`
- L74 _private prototype_ `bool IsLastStep() const;`
- L76 _private prototype_ `bool IsSelected() const;`
- L78 _private prototype_ `EVisibility GetDisabledOverlayVisbility() const;`
- L82 _private member_ `TSharedPtr<SDataprepActionBlock> ActionStepBlockPtr;` — Pointer to the widget displaying the actual filter or operation
- L85 _private member_ `int32 StepIndex;` — Index of the represented action step in the list of the parent action
- L88 _private member_ `TWeakPtr<SDataprepGraphTrackNode> ParentTrackNodePtr;` — Pointer to the SDataprepGraphTrackNode displayed in the graph editor
- L91 _private member_ `TWeakPtr<SDataprepGraphActionNode> ParentNodePtr;` — Pointer to the SDataprepGraphTrackNode displayed in the graph editor
- L94 _private member_ `TWeakPtr<FDataprepEditor> DataprepEditor;` — Optional pointer to the dataprep asset

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepGraphEditor.h` (Private)


#### class `FDataprepGraphNodeFactory`  
`class FDataprepGraphNodeFactory : public FGraphNodeFactory, public TSharedFromThis<FDataprepGraphNodeFactory>`  
_L26-41_
- inherits: `FGraphNodeFactory,TSharedFromThis<FDataprepGraphNodeFactory>`
- L29 _public prototype_ `virtual ~FDataprepGraphNodeFactory() = default;`
- L32 _public function_ `template<class DataprepEditorPtrType> FDataprepGraphNodeFactory(DataprepEditorPtrType&& InDataprepEditor) : DataprepEditor(Forward<DataprepEditorPtrType>(InDataprepEditor))`
- L37 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateNodeWidget(UEdGraphNode* InNode) override;` — Create a widget for the supplied node
- L40 _private member_ `TWeakPtr<FDataprepEditor> DataprepEditor;`

#### class `FDataprepGraphEditorNodeFactory`  
`class FDataprepGraphEditorNodeFactory : public FGraphPanelNodeFactory`  
_L43-47_
- inherits: `FGraphPanelNodeFactory`
- L46 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

#### class `SDataprepGraphEditor`  
`class SDataprepGraphEditor : public SGraphEditor`  
_L53-181_
- inherits: `SGraphEditor`
- desc: The SDataprepGraphEditor class is a specialization of SGraphEditor to display and manipulate the actions of a Dataprep asset
- L56 _public function_ `SLATE_BEGIN_ARGS(SDataprepGraphEditor) : _AdditionalCommands( static_cast<FUICommandList*>(nullptr) ) , _GraphToEdit(nullptr)`
- L61 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FUICommandList>, AdditionalCommands ) SLATE_ARGUMENT( TSharedPtr<SWidget>, TitleBar ) SLATE_ATTRIBUTE( FGraphAppearanceInfo, Appearance ) SLATE_ARGUMENT( UEdGraph*, GraphToEdit ) SLATE_ARGUMENT( FGraphEditorEvents, GraphEvents) SLATE_ARGUMENT( TSharedPtr<FDataprepEditor>, DataprepEditor ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepAsset* InDataprepAsset);`
- L72 _public prototype_ `virtual void CacheDesiredSize(float InLayoutScaleMultiplier) override;` — SWidget overrides
- L73 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L74 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L75 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L76 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L77 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L81 _public prototype_ `virtual void NotifyGraphChanged() override;` — SGraphEditor overrides
- L85 _public prototype_ `void OnDataprepAssetActionChanged(UObject* InObject, FDataprepAssetChangeType ChangeType);` — Called when a change has occurred in the set of the Dataprep asset's actions
- L88 _public prototype_ `static void RegisterFactories();` — Register/un-register the association between Dataprep's UEdGraph classes and SgraphNode classes
- L89 _public prototype_ `static void UnRegisterFactories();`
- L92 _public prototype_ `void OnRenameNode();` — Set of methods necessary for copy/paste of action nodes
- L93 _public prototype_ `bool CanRenameNode() const;`
- L95 _public function_ `bool CanSelectAllNodes() const`
- L97 _public prototype_ `void DeleteSelectedNodes();`
- L98 _public prototype_ `bool CanDeleteNodes() const;`
- L100 _public prototype_ `void CopySelectedNodes();`
- L101 _public prototype_ `bool CanCopyNodes() const;`
- L103 _public prototype_ `void CutSelectedNodes();`
- L104 _public prototype_ `bool CanCutNodes() const;`
- L106 _public prototype_ `void PasteNodes();`
- L107 _public prototype_ `bool CanPasteNodes() const;`
- L109 _public prototype_ `void DuplicateNodes();`
- L110 _public prototype_ `bool CanDuplicateNodes() const;`
- L112 _public prototype_ `void DeleteSelectedDuplicatableNodes();`
- L116 _public prototype_ `TSet<UObject*> GetSelectedActorsAndAssets();` — Get the selection of viewport/outliner actors as well as assets from the asset preview tab
- L119 _public prototype_ `bool OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);` — Set of callbacks to rename an action node
- L120 _public prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L124 _public prototype_ `FActionMenuContent OnCreateActionMenu(UEdGraph* InGraph, const FVector2D& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — `UE_DEPRECATED(5.6, "Please use the version of the function accepting FVector2f.")` — Callback to create contextual menu on graph panel
- L125 _public prototype_ `FActionMenuContent OnCreateActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);`
- L128 _public prototype_ `FActionMenuContent OnCreateNodeOrPinMenu(UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, FMenuBuilder* MenuBuilder, bool bIsDebugging);` — Callback to create contextual menu for graph nodes in graph panel
- L131 _public prototype_ `void OnCollectCustomActions(TArray<TSharedPtr<FDataprepSchemaAction>>& OutActions);` — Callback from the contextual menu to create any entries outside of the action collector
- L133 _public prototype_ `void CreateFilterFromSelection(UDataprepActionAsset* InTargetAction, const TSet< UObject* >& InAssetAndActorSelection);`
- L137 _private prototype_ `void UpdateLayout( const UE::Slate::FDeprecateVector2DParameter& LocalSize, const UE::Slate::FDeprecateVector2DParameter& Location, float ZoomAmount );` — Recompute the layout of the displayed graph after a pan, resize and/or zoom
- L139 _private prototype_ `void BuildCommandList();`
- L143 _private member_ `mutable bool bIsComplete;` — When false, indicates the graph editor has not been drawn yet
- L146 _private member_ `FDeprecateSlateVector2D LastLocalSize;` — Last size of the window displaying the graph's canvas
- L149 _private member_ `FDeprecateSlateVector2D LastLocation;` — Last location of the upper left corner of the visible section of the graph's canvas
- L152 _private member_ `float LastZoomAmount;` — Last zoom factor applied to the graph's canvas
- L155 _private member_ `FSlateRect WorkingArea;` — Dimensions of pipeline being displayed
- L158 _private member_ `TWeakObjectPtr<UDataprepAsset> DataprepAssetPtr;` — The dataprep asset associated with this graph
- L161 _private member_ `mutable TWeakPtr<SDataprepGraphTrackNode> TrackGraphNodePtr;` — Size of graph being displayed
- L164 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list associated with this graph editor
- L166 _private member_ `bool bCachedControlKeyDown;`
- L170 _private member_ `static const float TopPadding;` — #ueent_wip: Will be moved to the Dataprep editor's style
- L171 _private member_ `static const float BottomPadding;`
- L172 _private member_ `static const float HorizontalPadding;`
- L175 _private member_ `static TSharedPtr<FDataprepGraphEditorNodeFactory> NodeFactory;` — Factory to create the associated SGraphNode classes for Dataprep graph's UEdGraph classes
- L178 _private member_ `TWeakPtr<FDataprepEditor> DataprepEditor;` — The Dataprep editor that owns the graph

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepGraphTrackNode.h` (Private)


#### class `FDragDropActionNode`  
`class FDragDropActionNode : public FDragDropOperation`  
_L25-47_
- inherits: `FDragDropOperation`
- L28 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDragDropActionNode, FDragDropOperation) static TSharedRef<FDragDropActionNode> New(const TSharedRef<SDataprepGraphTrackNode>& InTrackNodePtr, const TSharedRef<SDataprepGraphBaseActionNode>& InDraggedNode);`
- L32 _public function_ `virtual ~FDragDropActionNode()`
- L35 _public function_ `virtual void OnDrop( bool bDropWasHandled, const FPointerEvent& MouseEvent ) override` — FDragDropOperation interface
- L36 _public function_ `virtual void OnDragged( const class FDragDropEvent& DragDropEvent ) override`
- L37 _public function_ `virtual FCursorReply OnCursorQuery() override`
- L38 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L39 _public function_ `virtual FVector2D GetDecoratorPosition() const override`
- L40 _public function_ `virtual void SetDecoratorVisibility(bool bVisible) override`
- L41 _public function_ `virtual bool IsExternalOperation() const override`
- L42 _public function_ `virtual bool IsWindowlessOperation() const override`
- L46 _private member_ `TSharedPtr<FDragDropActionNode> Impl;`

#### class `SDataprepGraphTrackNode`  
`class SDataprepGraphTrackNode : public SGraphNode`  
_L53-185_
- inherits: `SGraphNode`
- desc: The SDataprepGraphTrackNode class is a specialization of SGraphNode to handle the actions of a Dataprep asset
- L56 _public function_ `SLATE_BEGIN_ARGS(SDataprepGraphTrackNode)`
- L57 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FGraphNodeFactory>, NodeFactory) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepGraphRecipeNode* InNode);`
- L63 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L67 _public function_ `virtual bool CanBeSelected(const FVector2f& ) const override` — SNodePanel::SNode interface
- L71 _public prototype_ `virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;`
- L72 _public prototype_ `virtual void MoveTo( const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true ) override;`
- L73 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L74 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L75 _public function_ `virtual bool ShouldAllowCulling() const override`
- L79 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface
- L80 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L83 _public function_ `UDataprepAsset* GetDataprepAsset()`
- L84 _public function_ `const UDataprepAsset* GetDataprepAsset() const`
- L86 _public prototype_ `void OnControlKeyChanged(bool bControlKeyDown);`
- L89 _public prototype_ `void OnStartNodeDrag(const TSharedRef<SDataprepGraphBaseActionNode>& ActionNode);` — Initiates the horizontal drag of an action node
- L95 _public prototype_ `void OnEndNodeDrag(bool bDoDrop);` — Terminates the horizontal drag of an action node @param bDoDrop Indicates if the drop must be done
- L101 _public prototype_ `bool OnNodeDragged( TSharedPtr<SDataprepGraphBaseActionNode>& ActionNodePtr, const FVector2D& DragScreenSpacePosition, const FVector2D& ScreenSpaceDelta);` — Updates the position of other action nodes based on the position of the incoming node @return True if the action node was actually dragged
- L104 _public prototype_ `void OnActionsOrderChanged();` — Update the execution order of the actions and call ReArrangeActionNodes
- L107 _public prototype_ `bool RefreshLayout();` — Recomputes the position of each action node
- L110 _public prototype_ `FSlateRect Update();` — Recompute the boundaries of the graph based on the new size and/or the new zoom factor in graph panel
- L113 _public prototype_ `void RequestRename(const UEdGraphNode* Node);` — Start editing of action asset associated to input EdGraphNode
- L119 _public prototype_ `void RequestViewportPan(const FVector2D& ScreenSpacePosition);` — Change the view position of the panel based on input screen space position @Note: Replaces SGrpahPanel::RequestDeferredPan which perform the change one frame too early
- L122 _public prototype_ `void UpdateProxyNode(TSharedRef<SDataprepGraphBaseActionNode> ActioNodePtr, const FVector2D& ScreenSpacePosition);` — Helper to set the position of the graph nodes registered to the graph panel
- L125 _public member_ `static FVector2D TrackAnchor;` — Miscellaneous values used in the display
- L128 _public prototype_ `int32 GetActionIndex(int32 NodeIndex) const;` — Get action from node index, taking into account grouping
- L131 _public prototype_ `int32 GetNumActions(int32 NodeIndex) const;` — Get the number of actions from node index. Group nodes can have more than 1 action
- L134 _private prototype_ `FVector2D ComputePanAmount(const FVector2D& ScreenSpacePosition, float MaxPanSpeed = 200.f);`
- L138 _private member_ `TSharedPtr<SDataprepGraphTrackWidget> TrackWidgetPtr;` — Pointer to the widget displaying the track
- L141 _private member_ `TArray<TSharedPtr<SDataprepGraphBaseActionNode>> ActionNodes;` — Array of action node's widgets
- L144 _private member_ `TWeakObjectPtr<UDataprepAsset> DataprepAssetPtr;` — Weak pointer to the Dataprep asset holding the displayed actions
- L147 _private member_ `FVector2D AbscissaRange;` — Range for abscissa of action nodes used during drag-and-drop
- L150 _private member_ `bool bNodeDragging;` — Indicates a drag is happening
- L153 _private member_ `bool bNodeDragJustStarted;` — Indicates a drag has started.
- L156 _private member_ `float LastDragDirection;` — Indicates a drag has started.
- L162 _private member_ `bool bSkipNextDragUpdate;` — Indicates to skip the next mouse position update during a drag @remark Set to true when FSlateApplication::SetCursorPos has been called
- L165 _private member_ `FVector2D LastSetCursorPosition;` — Cached of the last position the software cursor was set to
- L171 _private member_ `bool bSkipRefreshLayout;` — Indicates to skip the next refresh of the track widget layout @remark Set to true when SNodePanel::RestoreViewSettings has been called
- L174 _private member_ `bool bCursorLeftOnLeft;` — Indicates whether the mouse pointer left the graph panel on the left
- L177 _private member_ `bool bCursorLeftOnRight;` — Indicates whether the mouse pointer left the graph panel on the right
- L180 _private member_ `TArray<TStrongObjectPtr<UEdGraphNode>> EdGraphActionNodes;` — Array of strong pointers to the UEdGraphNodes created for the Dataprep asset's actions
- L182 _private member_ `TSharedPtr<FGraphNodeFactory> NodeFactory;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepIntegerFilter.h` (Private)


#### class `SDataprepIntegerFilter`  
`class SDataprepIntegerFilter : public SCompoundWidget, public FGCObject`  
_L20-94_
- inherits: `SCompoundWidget,FGCObject`
- L22 _private function_ `SLATE_BEGIN_ARGS(SDataprepIntegerFilter)`
- L23 _private prototype_ `SLATE_END_ARGS();`
- L25 _private prototype_ `void Construct(const FArguments& InArgs, UDataprepIntegerFilter& InFilter);`
- L27 _private prototype_ `virtual ~SDataprepIntegerFilter();`
- L32 _private prototype_ `void UpdateVisualDisplay();` — Refresh the ui
- L35 _private typedef_ `using FListEntry = TTuple<FText, FText, int32>;` — The string matching option for the combo box (Displayed text, Tooltip, mapping for the UEnum)
- L38 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForMatchingCriteria(TSharedPtr<FListEntry> ListEntry) const;` — Those function are for the float matching criteria display
- L39 _private prototype_ `FText GetSelectedCriteriaText() const;`
- L40 _private prototype_ `FText GetSelectedCriteriaTooltipText() const;`
- L41 _private prototype_ `void OnSelectedCriteriaChanged(TSharedPtr<FListEntry> ListEntry, ESelectInfo::Type SelectionType);`
- L42 _private prototype_ `void OnCriteriaComboBoxOpenning();`
- L43 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForMatchingCriteria();`
- L46 _private prototype_ `int GetEqualValue() const;` — Those functions are for the int that will be compare against the fetched int
- L47 _private prototype_ `void OnEqualValueChanged(int NewEqualValue);`
- L48 _private prototype_ `void OnEqualValueComitted(int NewEqualValue, ETextCommit::Type CommitType);`
- L49 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForEqualValue();`
- L50 _private prototype_ `void ExtendContextMenuForEqualValueBox(FMenuBuilder& MenuBuilder);`
- L52 _private prototype_ `int GetFromValue() const;`
- L53 _private prototype_ `void OnFromValueChanged(int NewEqualValue);`
- L54 _private prototype_ `void OnFromValueComitted(int NewEqualValue, ETextCommit::Type CommitType);`
- L55 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForFromValue();`
- L56 _private prototype_ `void ExtendContextMenuForFromValueBox(FMenuBuilder& MenuBuilder);`
- L58 _private prototype_ `int GetToValue() const;`
- L59 _private prototype_ `void OnToValueChanged(int NewEqualValue);`
- L60 _private prototype_ `void OnToValueComitted(int NewEqualValue, ETextCommit::Type CommitType);`
- L61 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForToValue();`
- L62 _private prototype_ `void ExtendContextMenuForToValueBox(FMenuBuilder& MenuBuilder);`
- L65 _private prototype_ `void OnParameterizationStatusForObjectsChanged(const TSet<UObject*>* Objects);` — Event for dataprep parameterization
- L68 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L69 _private function_ `virtual FString GetReferencerName() const override`
- L75 _private prototype_ `EVisibility GetSingleValueVisibility() const;`
- L76 _private prototype_ `EVisibility GetDoubleValueVisibility() const;`
- L78 _private member_ `float OldEqualValue;`
- L79 _private member_ `float OldFromValue;`
- L80 _private member_ `float OldToValue;`
- L82 _private member_ `TObjectPtr<UDataprepIntegerFilter> Filter;`
- L84 _private member_ `TArray<TSharedPtr<FListEntry>> IntMatchingOptions;`
- L86 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FListEntry>>> IntMatchingCriteriaWidget;`
- L88 _private member_ `TSharedPtr<FDataprepParametrizationActionData> MatchingCriteriaParameterizationActionData;`
- L89 _private member_ `TSharedPtr<FDataprepParametrizationActionData> EqualValueParameterizationActionData;`
- L90 _private member_ `TSharedPtr<FDataprepParametrizationActionData> FromValueParameterizationActionData;`
- L91 _private member_ `TSharedPtr<FDataprepParametrizationActionData> ToValueParameterizationActionData;`
- L93 _private member_ `FDelegateHandle OnParameterizationStatusForObjectsChangedHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
- L9 _namespace_ `namespace ETextCommit`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepObjectSelectionFilter.h` (Private)


#### class `SDataprepObjectSelectionFilter`  
`class SDataprepObjectSelectionFilter : public SCompoundWidget, public FGCObject`  
_L17-35_
- inherits: `SCompoundWidget,FGCObject`
- L19 _private function_ `SLATE_BEGIN_ARGS(SDataprepObjectSelectionFilter)`
- L20 _private prototype_ `SLATE_END_ARGS();`
- L22 _private prototype_ `void Construct(const FArguments& InArgs, UDataprepObjectSelectionFilter& InFilter);`
- L26 _private member_ `TObjectPtr<UDataprepObjectSelectionFilter> Filter;`
- L29 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L30 _private function_ `virtual FString GetReferencerName() const override`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepOperation.h` (Private)


#### class `SDataprepOperation`  
`class SDataprepOperation : public SDataprepActionBlock, public FGCObject`  
_L12-39_
- inherits: `SDataprepActionBlock,FGCObject`
- L14 _private function_ `SLATE_BEGIN_ARGS(SDataprepOperation)`
- L15 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepOperation* InOperation, const TSharedRef<FDataprepSchemaActionContext>& InDataprepActionContext);`
- L22 _protected prototype_ `virtual FSlateColor GetOutlineColor() const override;` — SDataprepActionBlock interface
- L23 _protected prototype_ `virtual FText GetBlockTitle() const override;`
- L24 _protected prototype_ `virtual TSharedRef<SWidget> GetContentWidget() override;`
- L29 _private prototype_ `FText GetTooltipText() const;`
- L32 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L33 _private function_ `virtual FString GetReferencerName() const override`
- L38 _private member_ `TObjectPtr<UDataprepOperation> Operation;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepSelectionTransform.h` (Private)


#### class `SDataprepSelectionTransform`  
`class SDataprepSelectionTransform : public SDataprepActionBlock, public FGCObject`  
_L12-39_
- inherits: `SDataprepActionBlock,FGCObject`
- L14 _private function_ `SLATE_BEGIN_ARGS(SDataprepSelectionTransform)`
- L15 _private prototype_ `SLATE_END_ARGS();`
- L17 _private prototype_ `void Construct(const FArguments& InArgs, UDataprepSelectionTransform* InTransform, const TSharedRef<FDataprepSchemaActionContext>& InDataprepActionContext);`
- L22 _protected prototype_ `virtual FSlateColor GetOutlineColor() const override;` — SDataprepActionBlock interface
- L23 _protected prototype_ `virtual FText GetBlockTitle() const override;`
- L24 _protected prototype_ `virtual TSharedRef<SWidget> GetContentWidget() override;`
- L29 _private prototype_ `FText GetTooltipText() const;`
- L32 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L33 _private function_ `virtual FString GetReferencerName() const override`
- L38 _private member_ `TObjectPtr<UDataprepSelectionTransform> SelectionTransform;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepGraph/SDataprepStringFilter.h` (Private)


#### class `SDataprepStringFilter`  
`template <class FilterType> class SDataprepStringFilter : public SCompoundWidget, public FGCObject`  
_L21-81_
- inherits: `SCompoundWidget,FGCObject`
- L23 _private function_ `SLATE_BEGIN_ARGS(SDataprepStringFilter)`
- L24 _private prototype_ `SLATE_END_ARGS();`
- L26 _private prototype_ `void Construct(const FArguments& InArgs, FilterType& InFilter);`
- L28 _private prototype_ `virtual ~SDataprepStringFilter();`
- L32 _private prototype_ `void UpdateVisualDisplay();`
- L35 _private typedef_ `using FListEntry = TTuple<FText, FText, int32>;` — The string matching option for the combo box ( Displayed text, Tooltip, mapping for the UEnum)
- L38 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForMatchingCriteria(TSharedPtr<FListEntry> ListEntry) const;` — Those function are for the string matching criteria display
- L39 _private prototype_ `FText GetSelectedCriteriaText() const;`
- L40 _private prototype_ `FText GetSelectedCriteriaTooltipText() const;`
- L41 _private prototype_ `void OnSelectedCriteriaChanged(TSharedPtr<FListEntry> ListEntry, ESelectInfo::Type SelectionType);`
- L42 _private prototype_ `void OnCriteriaComboBoxOpenning();`
- L43 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForMatchingCriteria();`
- L44 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForMatchInArray();`
- L47 _private prototype_ `FText GetUserString() const;` — This function is for the string that will be compare against the fetched string
- L48 _private prototype_ `void OnUserStringChanged(const FText& NewText);`
- L49 _private prototype_ `void OnUserStringComitted(const FText& NewText, ETextCommit::Type CommitType);`
- L50 _private prototype_ `void OnUserStringArrayPropertyChanged(UDataprepParameterizableObject& Object, FPropertyChangedChainEvent& PropertyChangedChainEvent);`
- L51 _private prototype_ `FReply OnMatchInArrayClicked();`
- L53 _private prototype_ `void ExtendContextMenuForUserStringBox(FMenuBuilder& MenuBuilder);`
- L54 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuForUserString();`
- L56 _private prototype_ `void OnParameterizationStatusForObjectsChanged(const TSet<UObject*>* Objects);`
- L59 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L60 _private function_ `virtual FString GetReferencerName() const override`
- L66 _private member_ `FString OldUserString;`
- L68 _private member_ `TObjectPtr<FilterType> Filter;`
- L70 _private member_ `TArray<TSharedPtr<FListEntry>> StringMatchingOptions;`
- L72 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FListEntry>>> StringMatchingCriteriaWidget;`
- L74 _private member_ `TSharedPtr<FDataprepParametrizationActionData> MatchingCriteriaParameterizationActionData;`
- L75 _private member_ `TSharedPtr<FDataprepParametrizationActionData> UserStringParameterizationActionData;`
- L76 _private member_ `TSharedPtr<FDataprepParametrizationActionData> MatchInArrayParameterizationActionData;`
- L78 _private member_ `FDelegateHandle OnParameterizationStatusForObjectsChangedHandle;`
- L80 _private member_ `FDelegateHandle OnUserStringArrayPostEditHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
- L9 _namespace_ `namespace ETextCommit`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/DataprepWidgets.h` (Private)


#### class `DataprepWidgetUtils::SConstrainedBox`  
`class SConstrainedBox : public SCompoundWidget`  
_L28-50_
- inherits: `SCompoundWidget`
- desc: Helper class to force a widget to fill in a space. Copied from SDetailSingleItemRow.cpp
- L31 _public function_ `SLATE_BEGIN_ARGS(SConstrainedBox)`
- L32 _public function_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L43 _public function_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override`

#### enum `EDataprepCategory`  
`enum class EDataprepCategory`  
_L53-58_
- L55 _public enumerator_ `Producers`
- L56 _public enumerator_ `Consumers`
- L57 _public enumerator_ `Parameterization`

#### class `SDataprepCategoryWidget`  
`class SDataprepCategoryWidget : public STableRow< TSharedPtr< EDataprepCategory > >`  
_L62-82_
- inherits: `STableRow<TSharedPtr<EDataprepCategory>>`
- L66 _public function_ `SLATE_BEGIN_ARGS(SDataprepCategoryWidget)`
- L67 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(TSharedPtr< SWidget >, TitleDetail) SLATE_ARGUMENT(TSharedPtr< FDetailColumnSizeData >, ColumnSizeData) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef< SWidget > InContent, const TSharedRef<STableViewBase>& InOwnerTableView );`
- L74 _public function_ `virtual int32 DoesItemHaveChildren() const override`
- L75 _public function_ `virtual bool IsItemExpanded() const override`
- L76 _public prototype_ `virtual void ToggleExpansion() override;`
- L78 _public prototype_ `const FSlateBrush* GetBackgroundImage() const;`
- L80 _private member_ `bool bIsExpanded = true;`
- L81 _private member_ `TSharedPtr< SWidget > CategoryContent;`

#### class `SDataprepDetailsView`  
`class SDataprepDetailsView : public SCompoundWidget, public FGCObject`  
_L84-215_
- inherits: `SCompoundWidget,FGCObject`
- L86 _private typedef_ `using Super = SCompoundWidget;`
- L89 _public function_ `SLATE_BEGIN_ARGS(SDataprepDetailsView) : _Object( nullptr ) , _Spacing(0) , _ColumnPadding(false) , _ResizableColumn(true)`
- L103 _public prototype_ `void Construct(const FArguments& InArgs);`
- L105 _public prototype_ `~SDataprepDetailsView();`
- L107 _public prototype_ `void SetObjectToDisplay(UObject& Object);`
- L109 _public prototype_ `void ForceRefresh();`
- L112 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L113 _public function_ `virtual FString GetReferencerName() const override`
- L119 _public function_ `static int32 GetDesiredWidth()`
- L120 _public function_ `static void SetDesiredWidth(int32 InDesiredWidth)`
- L126 _protected function_ `virtual FVector2D ComputeDesiredSize(float) const override` — #ueent_todo: This is temporary until we find a better solution to the splitter issue See SConstrainedBox's trick in cpp file
- L135 _private prototype_ `void Construct();` — Fills up the details view with the detail nodes created by the property row manager
- L138 _private prototype_ `void AddWidgets( const TArray< TSharedRef< class IDetailTreeNode > >& DetailTree, int32& Index, float LeftPadding, const FDataprepParameterizationContext& ParameterizationContext, bool bChildNodes = false );` — Add widgets held by array of DetailTreeNode objects
- L148 _private prototype_ `void CreateDefaultWidget(int32 Index, TSharedPtr< SWidget >& NameWidget, TSharedPtr< SWidget >& ValueWidget, float LeftPadding, const FDataprepParameterizationContext& ParameterizationContext, bool bAddExpander = false, bool bChildNode = false );` — Inserts a generic widget for a property row into the grid panel @param Index						Row index in the grid panel @param NameWidget				The widget used in the name column @param ValueWidget				The widget used in the value column @param LeftPadding				The Padding on the left of the row @param ParameterizationContext	Parameterization context of the associated property
- L151 _private prototype_ `void OnPropertyChanged( const struct FPropertyChangedEvent& InEvent );` — Callback to track property changes on array properties
- L154 _private prototype_ `void OnObjectReplaced(const TMap<UObject*, UObject*>& ReplacementObjectMap);` — Callback used to detect the existence of a new object to display after a reinstancing process
- L156 _private prototype_ `void OnDataprepParameterizationStatusForObjectsChanged(const TSet<UObject*>* Objects);`
- L158 _private prototype_ `void OnObjectTransacted(UObject* Object, const class FTransactionObjectEvent& TransactionObjectEvent);`
- L162 _private member_ `TSharedPtr< class IPropertyRowGenerator > Generator;` — Row generator applied on detailed object
- L165 _private member_ `TObjectPtr<UObject> DetailedObject;` — Object to be detailed
- L167 _private member_ `UDataprepStringFilterMatchingArray* StringArrayDetailedObject;`
- L170 _private member_ `TObjectPtr<UDataprepParameterizableObject> DetailedObjectAsParameterizable;` — Not null if the detailed object is parameterizable
- L173 _private member_ `TSet< TSharedPtr< IPropertyHandle > > TrackedProperties;` — Array properties tracked for changes
- L176 _private member_ `FDelegateHandle OnPropertyChangedHandle;` — Delegate handle to track property changes on array properties
- L179 _private member_ `FDelegateHandle OnObjectReplacedHandle;` — Delegate handle to track new object after a re-instancing process
- L182 _private member_ `FDelegateHandle OnObjectTransactedHandle;` — Delegate handle to track when a object was transacted
- L185 _private member_ `TSharedPtr< FDetailColumnSizeData > ColumnSizeData;` — Points to the currently used column size data. Can be provided via argument as well.
- L191 _private member_ `TWeakObjectPtr<UDataprepAsset> DataprepAssetForParameterization;` — Pointer to a Dataprep asset used by the parameterization system. It should be nullptr when the parameterization shouldn't be shown
- L194 _private member_ `FDelegateHandle OnDataprepParameterizationStatusForObjectsChangedHandle;` — Callback used when parameterization has changed
- L197 _private member_ `float Spacing;` — Spacing between rows of the SDataprepDetailsView. 0 by default.
- L203 _private member_ `bool bColumnPadding;` — Indicates if two columns should be added This is useful when the SDataprepDetailsView widget is used along the Producers widget
- L208 _private member_ `bool bResizableColumn;` — Indicates if the name and value widgets have a splitter and can be resized
- L211 _private member_ `TSharedPtr<SGridPanel> GridPanel;` — Grid panel storing the row widgets
- L214 _private member_ `static int32 DesiredWidth;`

#### class `SDataprepContextMenuOverride`  
`class SDataprepContextMenuOverride : public SCompoundWidget`  
_L220-234_
- inherits: `SCompoundWidget`
- desc: This is widget simply exist to open contextual menu
- L223 _public function_ `SLATE_BEGIN_ARGS(SDataprepContextMenuOverride)`
- L224 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, DefaultSlot) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L230 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L233 _private member_ `FOnContextMenuOpening OnContextMenuOpening;`

#### class `SDataprepInstanceParentWidget`  
`class SDataprepInstanceParentWidget : public SCompoundWidget`  
_L237-272_
- inherits: `SCompoundWidget`
- desc: Widget to expose parent asset of a Dataprep instance
- L240 _public function_ `SLATE_BEGIN_ARGS(SDataprepInstanceParentWidget)`
- L241 _public prototype_ `SLATE_ARGUMENT(TSharedPtr< FDetailColumnSizeData >, ColumnSizeData) SLATE_ARGUMENT(UDataprepAssetInstance*, DataprepInstance) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L248 _private prototype_ `void SetDataprepInstanceParent(const FAssetData& InAssetData);`
- L249 _private prototype_ `FString GetDataprepInstanceParent() const;`
- L250 _private prototype_ `bool ShouldFilterAsset(const FAssetData& InAssetData);`
- L253 _private function_ `void OnLeftColumnResized(float InNewWidth)` — Callbacks to update splitter
- L259 _private function_ `float OnGetLeftColumnWidth() const`
- L260 _private function_ `float OnGetRightColumnWidth() const`
- L261 _private function_ `void OnSetColumnWidth(float InWidth)`
- L265 _private member_ `TWeakObjectPtr<UDataprepAssetInstance> DataprepInstancePtr;` — Weak pointer on DataprepAsset instance
- L268 _private member_ `TSharedPtr< FDetailColumnSizeData > ColumnSizeData;` — Helps sync column resizing with another part of the UI
- L271 _private member_ `float ColumnWidth;` — Relative width to control splitters.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace DataprepWidgetUtils`
- L25 _prototype_ `TSharedRef<SWidget> CreateParameterRow( TSharedPtr<SWidget> ParameterWidget );` (scope `DataprepWidgetUtils`)
- L60 _typedef_ `typedef STreeView< TSharedRef<EDataprepCategory> > SDataprepCategoryTree;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/Parameterization/SDataprepLinkToParameter.h` (Private)


#### class `SDataprepLinkToParameter`  
`class SDataprepLinkToParameter : public SCompoundWidget`  
_L17-67_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDataprepLinkToParameter)`
- L21 _public prototype_ `SLATE_END_ARGS();`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDataprepParametrizationActionData>& InParameterizationActionData);`
- L27 _private prototype_ `TSharedRef<class ITableRow> OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<class STableViewBase>& OwnerTable);`
- L29 _private prototype_ `void OnSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type SelectionType);`
- L31 _private prototype_ `void OnTextChanged(const FText& Text);`
- L33 _private prototype_ `void OnTextCommited(const FText& Text, ETextCommit::Type CommitType);`
- L35 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L38 _private prototype_ `bool SetErrorMessage();` — Return true if there is a error
- L41 _private member_ `TSharedPtr<FDataprepParametrizationActionData> ParameterizationActionData;` — The information that will be used to create the binding
- L43 _private member_ `TSharedPtr<FString> CreateNewOption;`
- L44 _private member_ `TArray<TSharedPtr<FString>> UnfilteredSuggestions;`
- L47 _private member_ `TArray<TSharedPtr<FString>> ShownItems;` — The items currently shown
- L50 _private member_ `TSet<FString> InvalidNames;` — The names that can be use because they are used for other property types
- L52 _private member_ `TSet<FString> ValidExistingNames;`
- L54 _private member_ `TSharedPtr<class SEditableTextBox> TextBox;`
- L55 _private member_ `TSharedPtr<class SListView<TSharedPtr<FString>>> SuggestionList;`
- L58 _private member_ `FString ParameterName;` — The current parameter name entered by the user
- L60 _private member_ `static FText EmptyNameErrorText;`
- L61 _private member_ `static FText InvalidNameErrorText;`
- L63 _private member_ `static FText LinkToParameterTransactionText;`
- L66 _private member_ `bool bHadFirstTick = false;` — Minor hack to set the focus on the text box

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
- L9 _namespace_ `namespace ETextCommit`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/Parameterization/SDataprepParameterizationLinkIcon.h` (Private)


#### class `SDataprepParameterizationLinkIcon`  
`class SDataprepParameterizationLinkIcon : public SCompoundWidget`  
_L15-22_
- inherits: `SCompoundWidget`
- desc: This is widget serves to display some information about a binded property to the dataprep parameterization
- L18 _public function_ `SLATE_BEGIN_ARGS(SDataprepParameterizationLinkIcon)`
- L19 _public prototype_ `SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, UDataprepAsset* DataprepAsset, UDataprepParameterizableObject* Object, const TArray<FDataprepPropertyLink>& PropertyChain);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SAssetsPreviewWidget.h` (Private)


#### class `AssetPreviewWidget::IAssetPreviewColumn`  
`class IAssetPreviewColumn : public TSharedFromThis< IAssetPreviewColumn >`  
_L33-52_
- inherits: `TSharedFromThis<IAssetPreviewColumn>`
- desc: Interface for a column of the asset preview
- L36 _public prototype_ `virtual ~IAssetPreviewColumn() = default;`
- L39 _public prototype_ `virtual uint8 GetCulumnPositionPriorityIndex() const = 0;` — A index for the desired position column. The higher index end up on left.
- L41 _public prototype_ `virtual FName GetColumnID() const = 0;`
- L43 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<SAssetsPreviewWidget>& PreviewWidget) = 0;`
- L45 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(const IAssetTreeItemPtr& TreeItem, const STableRow<IAssetTreeItemPtr>& Row, const TSharedRef<SAssetsPreviewWidget>& PreviewWidget) = 0;`
- L49 _public function_ `virtual void PopulateSearchStrings(const IAssetTreeItemPtr& Item, TArray< FString >& OutSearchStrings, const SAssetsPreviewWidget& AssetPreview) const` — Optionally overridden interface methods
- L51 _public function_ `virtual void SortItems(TArray<IAssetTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const`

#### class `AssetPreviewWidget::SAssetsPreviewWidget`  
`class SAssetsPreviewWidget : public SCompoundWidget`  
_L59-185_
- inherits: `SCompoundWidget`
- L62 _public function_ `SLATE_BEGIN_ARGS(SAssetsPreviewWidget)`
- L66 _public prototype_ `void Construct(const FArguments& InArgs);`
- L68 _public prototype_ `void SetAssetsList(const TArray< TWeakObjectPtr< UObject > >& InAssetsList, const FString& InPathToReplace, const FString& InSubstitutePath);`
- L69 _public prototype_ `void ClearAssetList();`
- L71 _public prototype_ `void RequestSort();`
- L73 _public function_ `FOnSelectionChanged& OnSelectionChanged()`
- L74 _public function_ `FOnContextMenu& OnContextMenu()`
- L75 _public function_ `FDataprepEditorUtils::FOnKeyDown& OnKeyDown()`
- L77 _public prototype_ `FText OnGetHighlightText() const;`
- L79 _public function_ `const TSharedPtr< STreeView< IAssetTreeItemPtr > > GetTreeView() const`
- L84 _public prototype_ `TSharedPtr<IAssetPreviewColumn> GetColumn(FName ColumnID) const;`
- L86 _public prototype_ `void AddColumn(TSharedRef<IAssetPreviewColumn> Column);`
- L88 _public prototype_ `void RemoveColumn(FName ColumnID);`
- L91 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L94 _public prototype_ `TArray<FString> GetItemsName(const TWeakObjectPtr<UObject>& Asset) const;`
- L96 _public prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L98 _public prototype_ `void SelectMatchingItems(const TSet<UObject*>& InAssets);`
- L100 _public prototype_ `TSet<UObject*> GetSelectedAssets() const;`
- L102 _public prototype_ `void SetSelectedAssets(TSet<UObject*> InSelectionSet, ESelectInfo::Type SelectionInfo);`
- L104 _public function_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L117 _private prototype_ `void ExpandAllFolders();`
- L119 _private prototype_ `void Sort(TArray<IAssetTreeItemPtr>& InItems) const;`
- L121 _private prototype_ `FString GetItemPath(const TWeakObjectPtr<UObject>& Asset) const;`
- L123 _private prototype_ `TSharedRef< class ITableRow > MakeRowWidget(IAssetTreeItemPtr InItem, const TSharedRef< class STableViewBase >& OwnerTable);`
- L124 _private prototype_ `void OnGetChildren(IAssetTreeItemPtr InParent, TArray<IAssetTreeItemPtr>& OutChildren) const;`
- L126 _private prototype_ `void OnSearchBoxChanged(const FText& InSearchText);`
- L127 _private prototype_ `void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);`
- L129 _private prototype_ `void OnSetExpansionRecursive(const IAssetTreeItemPtr InTreeNode, bool bInIsItemExpanded);`
- L131 _private prototype_ `void OnSelectionChangedInternal(IAssetTreeItemPtr ItemSelected, ESelectInfo::Type SelectionType);`
- L133 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L135 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpeningInternal();`
- L137 _private prototype_ `void SetupColumns();`
- L139 _private prototype_ `void UpdateColumns();`
- L141 _private prototype_ `void Refresh();`
- L148 _private prototype_ `FAssetTreeFolderItemPtr FindOrCreateParentsItem(const TArrayView<FString>& ParentNames);` — Find or create the parents chain @param ParentNames the names of the parents for the top to bottom @return the immediate parent
- L151 _private prototype_ `bool DoesPassFilter(const FAssetTreeAssetItemPtr& AssetItem) const;` — For now we only filter the assets items
- L154 _private member_ `TArray<IAssetTreeItemPtr> RootItems;` — The root items displayed
- L155 _private member_ `TMap<FString, FAssetTreeFolderItemPtr> NameToRootFolder;`
- L158 _private member_ `TArray<FAssetTreeAssetItemPtr> UnFilteredAssets;` — The list of asset unfiltered
- L159 _private member_ `int32 CurrentProcessingAssetIndex = 0;`
- L161 _private member_ `TSharedPtr< STreeView< IAssetTreeItemPtr > > TreeView;`
- L162 _private member_ `TSharedPtr< SHeaderRow > HeaderRow;`
- L164 _private member_ `FText FilterText;`
- L165 _private member_ `FString PathPrefixToRemove;`
- L166 _private member_ `FString SubstitutePath;`
- L168 _private member_ `TMap<FName, TSharedRef<IAssetPreviewColumn>> Columns;`
- L170 _private member_ `TArray<TSharedRef<IAssetPreviewColumn>> PendingColumnsToAdd;`
- L171 _private member_ `TArray<FName> PendingColumnsToRemove;`
- L173 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;`
- L174 _private member_ `FOnContextMenu OnContextMenuDelegate;`
- L175 _private member_ `FDataprepEditorUtils::FOnKeyDown OnKeyDownDelegate;`
- L177 _private member_ `FName SortingColumn;`
- L178 _private member_ `EColumnSortMode::Type SortingMode;`
- L181 _private member_ `TArray<FString> FilterStrings;` — The string used for the filtering
- L183 _private member_ `bool bIsSortDirty = false;`
- L184 _private member_ `bool bRequestedRefresh = false;`

#### struct `AssetPreviewWidget::IAssetTreeItem`  
`struct IAssetTreeItem`  
_L187-193_
- L189 _public prototype_ `virtual ~IAssetTreeItem() = default;`
- L191 _public member_ `FString Name;`
- L192 _public prototype_ `virtual bool IsFolder() const = 0;`

#### struct `AssetPreviewWidget::FAssetTreeAssetItem`  
`struct FAssetTreeAssetItem : public IAssetTreeItem`  
_L195-203_
- inherits: `IAssetTreeItem`
- L197 _public function_ `virtual bool IsFolder() const final`
- L202 _public member_ `TWeakObjectPtr< UObject > AssetPtr;`

#### struct `AssetPreviewWidget::FAssetTreeFolderItem`  
`struct FAssetTreeFolderItem : public IAssetTreeItem`  
_L205-218_
- inherits: `IAssetTreeItem`
- L207 _public function_ `virtual bool IsFolder() const final`
- L213 _public member_ `TMap<FString, FAssetTreeFolderItemPtr> NameToFolder;` — This is used to accelerate the construction of the tree in the set assets function
- L216 _public member_ `TArray<IAssetTreeItemPtr> Folders;` — Childrens
- L217 _public member_ `TArray<IAssetTreeItemPtr> Assets;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AssetPreviewWidget`
- L18 _typedef_ `using IAssetTreeItemPtr = TSharedPtr<IAssetTreeItem>;` (scope `AssetPreviewWidget`)
- L19 _typedef_ `using IAssetTreeItemWeakPtr = TWeakPtr<IAssetTreeItem>;` (scope `AssetPreviewWidget`)
- L22 _typedef_ `using FAssetTreeAssetItemPtr = TSharedPtr<FAssetTreeAssetItem>;` (scope `AssetPreviewWidget`)
- L25 _typedef_ `using FAssetTreeFolderItemPtr = TSharedPtr<FAssetTreeFolderItem>;` (scope `AssetPreviewWidget`)
- L54 _typedef_ `using FAssetPreviewColumn = TSharedRef<IAssetPreviewColumn>;` (scope `AssetPreviewWidget`)
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, TSet< UObject* > ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnContextMenu, TSet< UObject* > ) class SAssetsPreviewWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SAssetsPreviewWidget) {} SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); void SetAssetsList(const TArray< TWeakObjectPtr< UObject > >& InAssetsList, const FString& InPathToReplace, const FString& InSubstitutePath); void ClearAssetList(); void RequestSort(); FOnSelectionChanged& OnSelectionChanged() { return OnSelectionChangedDelegate; } FOnContextMenu& OnContextMenu() { return OnContextMenuDelegate; } FDataprepEditorUtils::FOnKeyDown& OnKeyDown() { return OnKeyDownDelegate; } FText OnGetHighlightText() const; const TSharedPtr< STreeView< IAssetTreeItemPtr > > GetTreeView() const { return TreeView; } TSharedPtr<IAssetPreviewColumn> GetColumn(FName ColumnID) const; void AddColumn(TSharedRef<IAssetPreviewColumn> Column); void RemoveColumn(FName ColumnID);`
- L57 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnContextMenu, TSet< UObject* > ) class SAssetsPreviewWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SAssetsPreviewWidget) {} SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); void SetAssetsList(const TArray< TWeakObjectPtr< UObject > >& InAssetsList, const FString& InPathToReplace, const FString& InSubstitutePath); void ClearAssetList(); void RequestSort(); FOnSelectionChanged& OnSelectionChanged() { return OnSelectionChangedDelegate; } FOnContextMenu& OnContextMenu() { return OnContextMenuDelegate; } FDataprepEditorUtils::FOnKeyDown& OnKeyDown() { return OnKeyDownDelegate; } FText OnGetHighlightText() const; const TSharedPtr< STreeView< IAssetTreeItemPtr > > GetTreeView() const { return TreeView; } TSharedPtr<IAssetPreviewColumn> GetColumn(FName ColumnID) const; void AddColumn(TSharedRef<IAssetPreviewColumn> Column); void RemoveColumn(FName ColumnID);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SDataprepActionMenu.h` (Private)


#### class `SDataprepActionMenu`  
`class SDataprepActionMenu : public SCompoundWidget`  
_L25-82_
- inherits: `SCompoundWidget`
- desc: The SDataprepActionMenu is the action menu used in Dataprep. Because of the IDataprepMenuActionCollector this can use for different actions. (example: Add an operation to dataprep action or Add a action to dataprep)
- L28 _public function_ `DECLARE_DELEGATE_OneParam( FOnCollectCustomActions, TArray< TSharedPtr<FDataprepSchemaAction> >& ) SLATE_BEGIN_ARGS(SDataprepActionMenu) : _TransactionText() , _DataprepActionContext() , _GraphObj(nullptr) , _NewNodePosition() , _DraggedFromPins() , _OnClosedCallback()`
- L38 _public prototype_ `SLATE_ATTRIBUTE( FText, TransactionText ) SLATE_ARGUMENT( FDataprepSchemaActionContext, DataprepActionContext ) SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( FOnCollectCustomActions, OnCollectCustomActions ) SLATE_END_ARGS();`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, TUniquePtr<IDataprepMenuActionCollector> InMenuActionCollector);`
- L49 _public prototype_ `TSharedPtr<class SEditableTextBox> GetFilterTextBox();`
- L51 _public prototype_ `virtual ~SDataprepActionMenu();`
- L55 _private prototype_ `void CollectActions(FGraphActionListBuilderBase& OutActions);`
- L57 _private prototype_ `void OnActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedActions, ESelectInfo::Type InSelectionType);`
- L59 _private prototype_ `TSharedRef<SExpanderArrow> OnCreateCustomRowExpander(const FCustomExpanderData& InCustomExpanderData) const;`
- L64 _private prototype_ `bool ShouldCreateNewNode() const;` — Should this action menu create a new node before executing the user selected action
- L67 _private member_ `TAttribute<FText> TransactionTextGetter;`
- L69 _private member_ `TUniquePtr<IDataprepMenuActionCollector> MenuActionCollector;`
- L70 _private member_ `TSharedPtr<class SGraphActionMenu> ActionMenu;`
- L73 _private member_ `FDataprepSchemaActionContext Context;` — The context on which this action menu was created
- L76 _private member_ `UEdGraph* GraphObj;` — Will be nullptr if this menu shouldn't modify the graph
- L77 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L78 _private member_ `FVector2D NewNodePosition;`
- L80 _private member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L81 _private member_ `FOnCollectCustomActions OnCollectCustomActions;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCollectCustomActions, TArray< TSharedPtr<FDataprepSchemaAction> >& ) SLATE_BEGIN_ARGS(SDataprepActionMenu) : _TransactionText() , _DataprepActionContext() , _GraphObj(nullptr) , _NewNodePosition() , _DraggedFromPins() , _OnClosedCallback() {} SLATE_ATTRIBUTE( FText, TransactionText ) SLATE_ARGUMENT( FDataprepSchemaActionContext, DataprepActionContext ) SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( FOnCollectCustomActions, OnCollectCustomActions ) SLATE_END_ARGS();`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SDataprepEditorViewport.h` (Private)


#### class `UCustomStaticMeshComponent`  
`class UCustomStaticMeshComponent : public UStaticMeshComponent`  
_L33-53_
- reflection: `UCLASS()`
- inherits: `UStaticMeshComponent`
- desc: Custom class deriving from UStaticMeshComponent to allow the display of individual meshes in wireframe @note: This technique was inspired from USkinnedMeshComponent
- L39 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L43 _public member_ `FPrototypeOrientedBox MeshProperties;`
- L44 _public member_ `bool bShouldBeInstanced;`
- L48 _protected member_ `bool bForceWireframe;`
- L49 _protected member_ `int32 MeshColorIndex;`

#### class `FDataprepEditorViewportCommands`  
`class FDataprepEditorViewportCommands : public TCommands<FDataprepEditorViewportCommands>`  
_L55-91_
- inherits: `TCommands<FDataprepEditorViewportCommands>`
- L58 _public function_ `FDataprepEditorViewportCommands() : TCommands<FDataprepEditorViewportCommands>( TEXT("DataprepEditorViewport"),`
- L69 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L73 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> SetShowBounds;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> SetShowNaniteFallback;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> ApplyOriginalMaterial;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> ApplyBackFaceMaterial;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> ApplyXRayMaterial;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> ApplyPerMeshMaterial;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> ApplyReflectionMaterial;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> ApplyOutlineSelection;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> ApplyXRaySelection;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> ApplyWireframeMode;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> ShowOOBs;`

#### class `SDataprepEditorViewportToolbar`  
`class SDataprepEditorViewportToolbar : public SCommonEditorViewportToolbarBase`  
_L94-119_
- inherits: `SCommonEditorViewportToolbarBase`
- desc: In-viewport toolbar widget used in the Dataprep editor
- L97 _public function_ `SLATE_BEGIN_ARGS(SDataprepEditorViewportToolbar)`
- L98 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider);`
- L103 _public prototype_ `virtual TSharedRef<SWidget> GenerateShowMenu() const override;` — SCommonEditorViewportToolbarBase interface
- L104 _public prototype_ `virtual void ExtendLeftAlignedToolbarSlots(TSharedPtr<SHorizontalBox> MainBoxPtr, TSharedPtr<SViewportToolBar> ParentToolBarPtr) const override;`
- L108 _public prototype_ `virtual bool IsViewModeSupported(EViewModeIndex ViewModeIndex) const override;` — SViewportToolBar interface
- L113 _private prototype_ `TSharedRef<SWidget> GenerateRenderingMenu() const;` — Generates the toolbar rendering menu content
- L117 _private prototype_ `TSharedRef<SWidget> GenerateExperimentalMenu() const;` — Generates the toolbar experimental menu content

#### class `FDataprepEditorViewportClient`  
`class FDataprepEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FDataprepEditorViewportClient>`  
_L121-145_
- inherits: `FEditorViewportClient,TSharedFromThis<FDataprepEditorViewportClient>`
- L124 _public prototype_ `FDataprepEditorViewportClient(const TSharedRef<SEditorViewport>& InDataprepEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);`
- L125 _public function_ `~FDataprepEditorViewportClient()`
- L128 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;` — FEditorViewportClient interface
- L129 _public prototype_ `virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L130 _public prototype_ `virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;`
- L134 _public prototype_ `virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;` — FViewElementDrawer interface
- L135 _public prototype_ `virtual void Draw(FViewport* Viewport,FCanvas* Canvas) override;`
- L141 _private member_ `FAdvancedPreviewScene* AdvancedPreviewScene;` — Stored pointer to the preview scene in which the preview mesh component are shown
- L144 _private member_ `SDataprepEditorViewport* DataprepEditorViewport;` — Stored pointer to the viewport in which the preview mesh component are shown

#### class `SDataprepEditorViewport`  
`class SDataprepEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L147-413_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L150 _public function_ `SLATE_BEGIN_ARGS( SDataprepEditorViewport )`
- L151 _public prototype_ `SLATE_ARGUMENT( UWorld*, WorldToPreview) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDataprepEditor> InDataprepEditor);`
- L156 _public prototype_ `SDataprepEditorViewport();`
- L157 _public prototype_ `~SDataprepEditorViewport();`
- L160 _public prototype_ `void UpdateScene();` — UpdateScene the viewport with the current content of the editor's preview world
- L163 _public prototype_ `void FocusViewportOnScene();` — Move the camera so that we can see the full scene
- L166 _public prototype_ `void ClearScene();` — Delete all the rendering data created by the viewport for display
- L169 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L170 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L171 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L174 _public prototype_ `void SelectActors( const TArray< AActor* >& SelectedActors );`
- L177 _public prototype_ `void SetActorVisibility(AActor* SceneActor, bool bInVisibility);` — Change visibility of preview mesh components
- L180 _public prototype_ `static void LoadDefaultSettings();` — Load the settings affecting the viewport, i.e. environment map
- L183 _public prototype_ `static void ReleaseDefaultMaterials();` — Release the materials used for the different rendering options in the viewport
- L185 _public function_ `int32 GetDrawCallsAverage() const`
- L192 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L193 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L194 _protected prototype_ `virtual void BindCommands() override;`
- L195 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L196 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L197 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L237 _private function_ `bool IsAPreviewComponent( const UStaticMeshComponent* Component ) const` — Returns true if the given mesh component is part of the mesh components to preview
- L240 _private prototype_ `void ClearSelection(bool bNotify = false);` — Clear the selection and if required notify
- L243 _private prototype_ `void SetSelection( UStaticMeshComponent* Component );` — Set the selection to this preview mesh component and calls UpdateSelection
- L246 _private prototype_ `void AddToSelection( UStaticMeshComponent* Component );` — Add this preview mesh component to the selection and calls UpdateSelection
- L249 _private prototype_ `void RemoveFromSelection( UStaticMeshComponent* Component );` — Remove this preview mesh component from the selection and calls UpdateSelection
- L252 _private function_ `bool IsSelected( UStaticMeshComponent* Component ) const` — Return if preview mesh component is part of the selection
- L258 _private prototype_ `void UpdateSelection(bool bNotify = true);` — Applies the selection material on all selected mesh components. If none is selected, applies current rendering material
- L261 _private prototype_ `void InitializeDefaultMaterials();` — Initialize the materials used for the different rendering options
- L264 _private prototype_ `void SetRenderingMaterial(ERenderingMaterialType InRenderingMaterial);` — Set the material to apply on the preview mesh components
- L267 _private function_ `bool IsRenderingMaterialApplied(ERenderingMaterialType InRenderingMaterialType) const` — Returns true if the rendering material is currently used
- L275 _private prototype_ `void ApplyRenderingMaterial();` — Modifies materials used on all the preview static mesh components based on value of RenderingMaterialType
- L282 _private prototype_ `UMaterialInterface* GetRenderingMaterial( UStaticMeshComponent* PreviewMeshComponent );` — Returns a pointer to the material interface to used on a preview static mesh component based on value of RenderingMaterialType @param PreviewMeshComponent	The preview static mesh component @remark Returns null pointer if RenderingMaterialType is equal to ERenderingMaterialType::OriginalRenderingMaterial
- L284 _private prototype_ `void ToggleWireframeRenderingMode();`
- L286 _private function_ `bool IsWireframeRenderingModeOn()`
- L288 _private prototype_ `void UpdateOverlayText();`
- L290 _private prototype_ `void UpdatePerfStats();`
- L293 _private prototype_ `void ToggleShowOrientedBox();`
- L295 _private function_ `bool IsShowOrientedBoxOn()`
- L299 _private prototype_ `void SetSelectionMode(ESelectionModeType InSelectionMode);` — Set the selection mode
- L302 _private function_ `bool IsSetSelectionModeApplied(ESelectionModeType InSelectionMode)` — Check if a given selection mode is active
- L305 _private prototype_ `bool IsComponentSelected(const UPrimitiveComponent* PrimitiveComponent);` — Returns true if the given primitive component is part of the selection set
- L308 _private prototype_ `void SetShowNaniteFallback(bool bShow);` — Sets the show Nanite flag
- L311 _private function_ `void ToggleShowNaniteFallback()` — Callback for toggling the show Nanite flag.
- L314 _private function_ `bool IsSetShowNaniteFallbackChecked() const` — Callback for checking the Nanite show flag.
- L317 _private function_ `bool IsShowNaniteFallbackVisible() const` — Callback for checking whether the Nanite show entry should be displayed.
- L319 _private prototype_ `AActor* CreateActor(USceneComponent* ParentComponent, const TCHAR* ActorName);`
- L323 _private member_ `TSharedPtr< FAdvancedPreviewScene > PreviewScene;` — The scene for this viewport
- L326 _private member_ `TSharedPtr<class FDataprepEditorViewportClient> EditorViewportClient;` — Editor viewport client
- L328 _private member_ `TSharedPtr<FExtender> Extender;`
- L331 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L334 _private member_ `UWorld* WorldToPreview;` — World containing the data to preview
- L337 _private member_ `TWeakObjectPtr<USceneComponent> RootActorComponent;` — Root component of the viewport world's root actor.
- L340 _private member_ `TWeakObjectPtr<AActor> MovableActor;` — Actor to hold onto all 'Movable' preview mesh components
- L343 _private member_ `TWeakObjectPtr<AActor> StaticActor;` — Actor to hold onto all 'Static' preview mesh components
- L346 _private member_ `TArray< TWeakObjectPtr< UStaticMeshComponent > > PreviewMeshComponents;` — Array of static mesh components added to the preview scene for display.
- L349 _private member_ `TMap< UStaticMeshComponent*, UStaticMeshComponent* > MeshComponentsMapping;` — Mapping between scene's static mesh component and preview's one
- L352 _private member_ `TMap< UStaticMeshComponent*, UStaticMeshComponent* > MeshComponentsReverseMapping;` — Mapping between preview's static mesh component and scene's one
- L355 _private member_ `TSet<UStaticMeshComponent*> SelectedPreviewComponents;` — Array of selected static mesh components
- L358 _private member_ `float SceneUniformScale;` — Scale factor applied to better navigate through the scene
- L361 _private member_ `FBox SceneBounds;` — Bounding box of the uniformly scaled scene
- L363 _private member_ `ERenderingMaterialType RenderingMaterialType;`
- L365 _private member_ `ESelectionModeType CurrentSelectionMode;`
- L368 _private member_ `bool bWireframeRenderingMode;` — Indicates if wireframe mode is on or off
- L371 _private member_ `static TStrongObjectPtr<UMaterial> PreviewMaterial;` — Material used to create utility material instances
- L374 _private member_ `static TStrongObjectPtr<UMaterial> XRayMaterial;` — Stylized XRay Material
- L377 _private member_ `static TStrongObjectPtr<UMaterial> BackFaceMaterial;` — Material used to display front facing triangle in green and back facing one in red
- L380 _private member_ `static TStrongObjectPtr<UMaterialInstanceConstant> TransparentMaterial;` — Transparent material instance used to display non-selected meshes
- L383 _private member_ `static TStrongObjectPtr<UMaterial> ReflectionMaterial;` — Fully reflective material used to display surface discontinuity
- L386 _private member_ `static TStrongObjectPtr<UMaterial> PerMeshMaterial;` — Materials used to display each mesh component in a different color
- L387 _private member_ `static TArray<TStrongObjectPtr<UMaterialInstanceConstant>> PerMeshMaterialInstances;`
- L389 _private member_ `TWeakPtr<FDataprepEditor> DataprepEditor;`
- L392 _private member_ `TSharedPtr<SVerticalBox> OverlayTextVerticalBox;` — Pointer to the vertical box into which the overlay text items are added
- L393 _private member_ `TSharedPtr<STextBlock> FPSText;`
- L394 _private member_ `TSharedPtr<STextBlock> DrawCallsText;`
- L397 _private member_ `const int32 DrawCallsUpdateInterval = 20;` — Draw calls smoothing
- L398 _private member_ `int32 DrawCallsAccumulator = 0;`
- L399 _private member_ `int32 CurrentDrawCalls = 0;`
- L400 _private member_ `int32 AverageDrawCalls = 0;`
- L403 _private member_ `static int32 AssetViewerProfileIndex;` — Index of the profile to use in the preview scene
- L406 _private member_ `bool bShowOrientedBox;`
- L409 _private member_ `bool bCanShowNaniteFallbackMenu = false;`
- L410 _private member_ `bool bShowNaniteFallbackMenuChecked = false;`

#### enum `SDataprepEditorViewport::ERenderingMaterialType`  
`enum class ERenderingMaterialType : uint8`  
_L200-209_
- L202 _public enumerator_ `OriginalRenderingMaterial`
- L203 _public enumerator_ `BackFaceRenderingMaterial`
- L204 _public enumerator_ `XRayRenderingMaterial`
- L205 _public enumerator_ `UVStretchRenderingMaterial`
- L206 _public enumerator_ `PerMeshRenderingMaterial`
- L207 _public enumerator_ `ReflectionRenderingMaterial`
- L208 _public enumerator_ `MaxRenderingMaterial`

#### enum `SDataprepEditorViewport::ESelectionModeType`  
`enum class ESelectionModeType : uint8`  
_L211-216_
- L213 _public enumerator_ `OutlineSelectionMode`
- L214 _public enumerator_ `XRaySelectionMode`
- L215 _public enumerator_ `MaxSelectionMode`

#### enum `SDataprepEditorViewport::ERenderingMode`  
`enum class ERenderingMode : uint8`  
_L218-223_
- L220 _public enumerator_ `NormalRenderingMode`
- L221 _public enumerator_ `WireframeRenderingMode`
- L222 _public enumerator_ `MaxRenderingMode`

#### struct `SDataprepEditorViewport::FOverlayTextItem`  
`struct FOverlayTextItem`  
_L226-234_
- desc: Struct defining the text and its style of each item in the overlay widget
- L228 _public function_ `explicit FOverlayTextItem(const FText& InText, const FName& InStyle = "TextBlock.ShadowedText") : Text(InText), Style(InStyle)`
- L232 _public member_ `FText Text;`
- L233 _public member_ `FName Style;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SDataprepPalette.h` (Private)


#### class `SDataprepPalette`  
`class SDataprepPalette : public SGraphPalette`  
_L11-60_
- inherits: `SGraphPalette`
- L14 _public function_ `SLATE_BEGIN_ARGS(SDataprepPalette)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;` — SGraphPalette Interface
- L23 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;`
- L24 _protected prototype_ `virtual FReply OnActionDragged(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions, const FPointerEvent& MouseEvent) override;`
- L29 _private prototype_ `TSharedRef<class SExpanderArrow> OnCreateCustomRowExpander(const FCustomExpanderData& InCustomExpanderData) const;` — CallBack from the GraphActionMenu for when the custom row expender is created
- L32 _private prototype_ `void AddAssetFromAssetRegistry(const FAssetData& InAddedAssetData);` — Callback from the Asset Registry when a new asset is added.
- L35 _private prototype_ `void RemoveAssetFromRegistry(const FAssetData& InRemoveddAssetData);` — Callback from the Asset Registry when an asset is removed.
- L38 _private prototype_ `void RenameAssetFromRegistry(const FAssetData& InRenamedAssetData, const FString& InNewName);` — Callback from the Asset Registry when an asset is renamed.
- L40 _private prototype_ `void RefreshAssetInRegistry(const FAssetData& InAssetData);`
- L42 _private prototype_ `FText GetFilterText() const;`
- L44 _private prototype_ `TSharedRef<SWidget> CreateBackground(const TAttribute<FSlateColor>& ColorAndOpacity);`
- L46 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L48 _private prototype_ `FText OnGetSectionTitle(int32 InSection);`
- L50 _private prototype_ `FSlateColor OnGetWidgetColor(FLinearColor InDefaultColor, FIsSelected InIsActionSelectedDelegate);`
- L52 _private prototype_ `TSharedRef<SWidget> ConstructAddActionMenu();`
- L53 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L54 _private member_ `TSharedPtr<SSearchBox> FilterBox;`
- L57 _private member_ `FText AllCategory;` — The options for the category selection
- L58 _private member_ `FText SelectorsCategory;`
- L59 _private member_ `FText OperationsCategory;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SDataprepPreviewRow.h` (Private)


#### class `SDataprepPreviewRow`  
`class SDataprepPreviewRow : public SCompoundWidget`  
_L12-29_
- inherits: `SCompoundWidget`
- desc: The widget to display the result of the filter preview
- L15 _public function_ `SLATE_BEGIN_ARGS(SDataprepPreviewRow)`
- L16 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS();`
- L19 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDataprepPreviewProcessingResult>& InPreviewData);`
- L22 _private prototype_ `FText GetIcon() const;`
- L24 _private prototype_ `FText GetLabel() const;`
- L26 _private prototype_ `FSlateColor GetTextColor() const;`
- L28 _private member_ `TSharedPtr<FDataprepPreviewProcessingResult> PreviewData;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SDataprepProducersWidget.h` (Private)


#### class `FContentProducerEntry`  
`class FContentProducerEntry`  
_L16-42_
- L19 _public prototype_ `FContentProducerEntry(int32 InProducerIndex, UDataprepAssetProducers* InAssetProducersPtr);`
- L21 _public function_ `bool HasValidData()`
- L26 _public function_ `UDataprepContentProducer* GetProducer()`
- L31 _public function_ `bool WillBeRun()`
- L33 _public prototype_ `void ToggleProducer();`
- L35 _public prototype_ `void RemoveProducer();`
- L37 _public member_ `FString Label;`
- L38 _public member_ `int32 ProducerIndex;`
- L39 _public member_ `bool bIsEnabled;`
- L40 _public member_ `bool bIsSuperseded;`
- L41 _public member_ `TWeakObjectPtr<UDataprepAssetProducers> AssetProducersPtr;`

#### class `SDataprepProducersTableRow`  
`class SDataprepProducersTableRow : public STableRow<FContentProducerEntryRef>`  
_L48-65_
- inherits: `STableRow<FContentProducerEntryRef>`
- desc: Represents a row in the VariantManager's tree views and list views
- L51 _public function_ `SLATE_BEGIN_ARGS(SDataprepProducersTableRow)`
- L52 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<FContentProducerEntry>& InNode, TSharedRef< FDetailColumnSizeData > InColumnSizeData);`
- L56 _public prototype_ `TSharedRef<SWidget> GetInputMainWidget( TSharedRef< FDetailColumnSizeData > ColumnSizeData );`
- L58 _public function_ `TSharedPtr<FContentProducerEntry> GetDisplayNode() const`
- L64 _private member_ `mutable TWeakPtr<FContentProducerEntry> Node;`

#### class `SDataprepProducersTreeView`  
`class SDataprepProducersTreeView : public STreeView<FContentProducerEntryRef>`  
_L67-93_
- inherits: `STreeView<FContentProducerEntryRef>`
- L71 _public function_ `SLATE_BEGIN_ARGS(SDataprepProducersTreeView)`
- L72 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataprepAssetProducers* InAssetProducersPtr, TSharedRef< FDetailColumnSizeData > InColumnSizeData );`
- L76 _public prototype_ `int32 GetDisplayIndexOfNode(FContentProducerEntryRef InNode);`
- L79 _public prototype_ `void Refresh();` — Caches the nodes the VariantManagerNodeTree is using and refreshes the display
- L82 _protected prototype_ `void OnExpansionChanged(FContentProducerEntryRef InItem, bool bIsExpanded);`
- L83 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(FContentProducerEntryRef InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L84 _protected prototype_ `void OnGetChildren(FContentProducerEntryRef InParent, TArray<FContentProducerEntryRef>& OutChildren) const;`
- L87 _private prototype_ `void BuildProducerEntries();`
- L90 _private member_ `TWeakObjectPtr<UDataprepAssetProducers> AssetProducersPtr;`
- L91 _private member_ `TArray<FContentProducerEntryRef> RootNodes;`
- L92 _private member_ `TSharedPtr< FDetailColumnSizeData > ColumnSizeData;`

#### class `SDataprepProducersWidget`  
`class SDataprepProducersWidget : public SCompoundWidget`  
_L99-131_
- inherits: `SCompoundWidget`
- L103 _public function_ `SLATE_BEGIN_ARGS(SDataprepProducersWidget)`
- L104 _public prototype_ `SLATE_ARGUMENT(TSharedPtr< FDetailColumnSizeData >, ColumnSizeData) SLATE_ARGUMENT(FDataprepImportProducers, DataprepImportProducersDelegate) SLATE_ARGUMENT(FDataprepImportProducersEnabled, DataprepImportProducersEnabledDelegate) SLATE_END_ARGS() ~SDataprepProducersWidget();`
- L111 _public prototype_ `void Construct(const FArguments& InArgs, UDataprepAssetProducers* InAssetProducersPtr);`
- L113 _public prototype_ `TSharedRef<SWidget> CreateAddProducerMenuWidget();`
- L115 _public function_ `void Refresh()`
- L117 _public function_ `TSharedPtr<SWidget> GetAddNewMenu()`
- L120 _protected prototype_ `void OnAddProducer( UClass* ProducerClass );`
- L123 _private prototype_ `void OnDataprepProducersChanged(FDataprepAssetChangeType ChangeType, int32 Index);`
- L126 _private member_ `TSharedPtr<SWidget> AddNewMenu;`
- L127 _private member_ `TWeakObjectPtr<UDataprepAssetProducers> AssetProducersPtr;`
- L128 _private member_ `TSharedPtr<SDataprepProducersTreeView> TreeView;`
- L129 _private member_ `FDataprepImportProducers DataprepImportProducersDelegate;`
- L130 _private member_ `FDataprepImportProducersEnabled DataprepImportProducersEnabledDelegate;`

#### class `FDataprepAssetProducersDetails`  
`class FDataprepAssetProducersDetails : public IDetailCustomization`  
_L134-144_
- inherits: `IDetailCustomization`
- desc: Customization of the details of the Datasmith Scene for the data prep editor.
- L137 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L140 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized
- L143 _private prototype_ `TSharedRef<SWidget> CreateWidget(UDataprepAssetProducers* Producers);`

#### Free symbols / members of external scopes

- L44 _typedef_ `typedef TSharedRef<FContentProducerEntry> FContentProducerEntryRef;`
- L45 _typedef_ `typedef TSharedPtr<FContentProducerEntry> FContentProducerEntryPtr;`
- L96 _delegate_ `DECLARE_DELEGATE(FDataprepImportProducers);` — Delegates for producers import
- L96 _prototype_ `DECLARE_DELEGATE(FDataprepImportProducers);` — Delegates for producers import
- L97 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FDataprepImportProducersEnabled);`
- L97 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FDataprepImportProducersEnabled);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/Widgets/SDataprepStats.h` (Private)


#### struct `FDataprepStat`  
`struct FDataprepStat`  
_L12-25_
- L14 _public function_ `FDataprepStat(const FText& InName, const TAttribute<int32>& InPreExecuteCount = TAttribute<int32>(), const TAttribute<int32>& InPostExecuteCount = TAttribute<int32>())`
- L21 _public member_ `FText StatName;`
- L23 _public member_ `TAttribute<int32> PreExecuteCount;`
- L24 _public member_ `TAttribute<int32> PostExecuteCount;`

#### class `SDataprepStats`  
`class SDataprepStats : public SCompoundWidget`  
_L29-63_
- inherits: `SCompoundWidget`
- L40 _public typedef_ `typedef TSharedPtr<FStatListEntry> FStatListEntryPtr;`
- L41 _public typedef_ `typedef SListView<FStatListEntryPtr> FDataprepStatListView;`
- L43 _public function_ `SLATE_BEGIN_ARGS(SDataprepStats)`
- L44 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `void AddStat(const FName& InStatName, const FName& InStatCategory, const FDataprepStat& InStat);`
- L50 _public prototype_ `FDataprepStatPtr GetStat(const FName& InStatName);`
- L52 _public prototype_ `void SetStats(const TSharedPtr<FDataprepStats>& InStats, bool bIsPreExecute);`
- L54 _public prototype_ `void ClearStats(bool bInClearPreExecuteStats, bool bInClearPostExecuteStats);`
- L57 _private member_ `TArray<FStatListEntryPtr> ListEntries;`
- L60 _private member_ `TMap<FName, int32> StatCountsMap;` — Counts by category name
- L62 _private member_ `TSharedPtr<FDataprepStatListView> StatsListView;`

#### struct `SDataprepStats::FStatListEntry`  
`struct FStatListEntry`  
_L32-38_
- L34 _public member_ `FName StatName;`
- L35 _public member_ `FName StatCategory;`
- L36 _public member_ `FLinearColor BgColor;`
- L37 _public member_ `FDataprepStatPtr StatPtr;`

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedPtr<FDataprepStat> FDataprepStatPtr;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Public/DataprepEditorMenu.h` (Public)


#### class `UDataprepEditorContextMenuContext`  
`class UDataprepEditorContextMenuContext : public UObject`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public member_ `TArray< TObjectPtr<UObject> > SelectedObjects;` — `UPROPERTY()`
- L20 _public member_ `TObjectPtr<class UDataprepAssetInterface> DataprepAsset;` — `UPROPERTY()`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Public/DataprepEditorModule.h` (Public)


#### class `IDataprepEditorModule`  
`class IDataprepEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L23-49_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Data preparation editor module interface
- L31 _public function_ `static inline IDataprepEditorModule& Get()` — Singleton-like access to IDatasmithContentEditorModule @return Returns DatasmithContent singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L46 _public prototype_ `virtual TSharedRef<SWidget> CreateDataprepProducersWidget(UDataprepAssetProducers* AssetProducers) = 0;`
- L47 _public prototype_ `virtual TSharedRef<SWidget> CreateDataprepDetailsView(UObject* ObjectToDetail) = 0;`

#### Free symbols / members of external scopes

- L16 _externvar_ `extern const FName DataprepEditorAppIdentifier;`
- L18 _macro_ `#define DATAPREPEDITOR_MODULE_NAME TEXT("DataprepEditor")`
