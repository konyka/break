# Editor / SkeletalMeshEditor

- module root: `Source/Editor/SkeletalMeshEditor`
- headers: 11; symbols: 253
- symbol kinds: class=13, delegate=5, enum=1, enumerator=3, externvar=11, function=12, macro=3, member=42, namespace=2, prototype=157, struct=4
- PrivateDependencyModuleNames: ActorPickerMode, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, Core, CoreUObject, DesktopPlatform, EditorFramework, EditorInteractiveToolsFramework, EditorSubsystem, Engine, InputCore, InterchangeCore, InterchangeEngine, Kismet, KismetWidgets, MainFrame, PhysicsUtilities, PropertyEditor, RHI, SceneDepthPickerMode, SkeletalMeshUtilitiesCommon, SkeletonEditor, Slate, SlateCore, StatusBar, ToolMenus, TypedElementRuntime, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Persona

### `Source/Editor/SkeletalMeshEditor/Private/MeshHierarchyCmd.h` (Private)


#### class `FMeshHierarchyCmd`  
`class FMeshHierarchyCmd : private FSelfRegisteringExec`  
_L8-13_
- inherits: `FSelfRegisteringExec`
- L12 _protected prototype_ `virtual bool Exec_Editor(UWorld*, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Console commands, see embeded usage statement

### `Source/Editor/SkeletalMeshEditor/Private/SControlRigMappingWindow.h` (Private)


#### class `SControlRigMappingWindow`  
`class SControlRigMappingWindow : public SCompoundWidget`  
_L17-79_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS( SControlRigMappingWindow )`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<class USkeletalMesh>& InEditableMesh, FSimpleMulticastDelegate& InOnPostUndo);`
- L34 _private member_ `TWeakObjectPtr<class USkeletalMesh> EditableSkeletalMeshPtr;` — The editable skeletalmesh
- L37 _private member_ `TSharedPtr<SComboBox< TSharedPtr<class UNodeMappingContainer*> >> MappingOptionBox;` — Combo box for list of mapping selection
- L38 _private member_ `TArray< TSharedPtr<class UNodeMappingContainer*> > MappingOptionBoxList;`
- L41 _private member_ `int32 CurrentlySelectedIndex;` — Currently selected index
- L44 _private member_ `TSharedPtr<SBoneMappingBase> BoneMappingWidget;` — Bone mapping widget
- L47 _private prototype_ `void PostUndo();` — Delegate for undo/redo transaction
- L50 _private prototype_ `TSharedRef<SWidget> HandleMappingOptionBoxGenerateWidget(TSharedPtr<class UNodeMappingContainer*> Item);` — UI Handler for drop down combo box
- L51 _private prototype_ `void HandleMappingOptionBoxSelectionChanged(TSharedPtr<class UNodeMappingContainer*> Item, ESelectInfo::Type SelectInfo);`
- L52 _private prototype_ `FText HandleMappingOptionBoxContentText() const;`
- L55 _private prototype_ `FReply OnAddNodeMappingButtonClicked();` — Button handler
- L56 _private prototype_ `FReply OnDeleteNodeMappingButtonClicked();`
- L57 _private prototype_ `FReply OnRefreshNodeMappingButtonClicked();`
- L61 _private prototype_ `void OnAddNodeMapping();` — Handler for adding new retarget source. It displays the asset picker
- L65 _private prototype_ `void AddNodeMapping(UBlueprint* NewSourceController);`
- L66 _private prototype_ `void OnAssetSelectedFromMeshPicker(const FAssetData& AssetData);`
- L68 _private prototype_ `bool OnShouldFilterAnimAsset(const FAssetData& AssetData) const;` — Delegate to handle filtering of asset pickers
- L70 _private prototype_ `void RefreshList();` — refresh drop down list
- L73 _private prototype_ `void OnBoneMappingChanged(FName NodeName, FName BoneName);` — bone mapping interface
- L74 _private prototype_ `FName GetBoneMapping(FName NodeName);`
- L75 _private prototype_ `const struct FReferenceSkeleton& GetReferenceSkeleton() const;`
- L76 _private prototype_ `void CreateBoneMappingList(const FString& SearchText, TArray< TSharedPtr<FDisplayedBoneMappingInfo> >& BoneMappingList);`
- L78 _private prototype_ `class UNodeMappingContainer* GetCurrentBoneMappingContainer() const;`

### `Source/Editor/SkeletalMeshEditor/Private/SkeletalMeshEditor.h` (Private)


#### class `FSkeletalMeshEditor`  
`class FSkeletalMeshEditor : public ISkeletalMeshEditor, public FGCObject, public FEditorUndoClient, public FTickableEditorObject`  
_L54-260_
- inherits: `ISkeletalMeshEditor,FGCObject,FEditorUndoClient,FTickableEditorObject`
- L57 _public prototype_ `FSkeletalMeshEditor();`
- L59 _public prototype_ `virtual ~FSkeletalMeshEditor();`
- L62 _public prototype_ `void InitSkeletalMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, class USkeletalMesh* InSkeletalMesh);` — Edits the specified Skeleton object
- L65 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;` — FPersonaAssetEditorToolkit
- L66 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L67 _public prototype_ `virtual void PostInitAssetEditor() override;`
- L70 _public function_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const override` — IHasPersonaToolkit interface
- L73 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L74 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L75 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L76 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L77 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L78 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L79 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L81 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder = INDEX_NONE) override;`
- L82 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget) override;`
- L85 _public prototype_ `virtual bool ProcessCommandBindings(const FKeyEvent& InKeyEvent) const override;` — FBaseToolkit overrides
- L88 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L89 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L90 _public prototype_ `virtual void SaveAssetAs_Execute() override;`
- L94 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L95 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L98 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject Interface
- L99 _public prototype_ `virtual TStatId GetStatId() const override;`
- L100 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L103 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L109 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L110 _public function_ `virtual FString GetReferencerName() const override`
- L116 _public function_ `TSharedRef<class ISkeletonTree> GetSkeletonTree() const` — Get the skeleton tree widget
- L119 _public function_ `TSharedRef<class IMorphTargetViewer> GetMorphTargetViewer() const` — Get the MorphTargetViewer widget
- L121 _public prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L123 _public prototype_ `void HandleMeshDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L125 _public prototype_ `void HandleViewportCreated(const TSharedRef<class IPersonaViewport>& InViewport);`
- L127 _public prototype_ `UObject* HandleGetAsset();`
- L129 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);`
- L132 _public function_ `TSharedPtr<IToolkit> GetHostedToolkit() const` — Returns the currently hosted toolkit. Can be invalid if no toolkit is being hosted.
- L134 _public prototype_ `virtual TSharedPtr<ISkeletalMeshEditorBinding> GetBinding() override;`
- L135 _public prototype_ `virtual FSimpleMulticastDelegate& OnPreSaveAsset() override;`
- L136 _public prototype_ `virtual FSimpleMulticastDelegate& OnPreSaveAssetAs() override;`
- L137 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetResetBoneTransformsCommand() override;`
- L138 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetResetAllBonesTransformsCommand() override;`
- L141 _protected prototype_ `void OnBuildViewportInteractions(UViewportInteractionsBehaviorSource* Source) override;`
- L144 _private prototype_ `void HandleObjectSelected(UObject* InObject);`
- L146 _private prototype_ `void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);`
- L161 _private prototype_ `void HandleReimportMesh(const FReimportParameters ReimportParameters);`
- L162 _private prototype_ `TFuture<bool> HandleReimportMeshInternal(const FReimportParameters& ReimportParameters);`
- L164 _private prototype_ `void HandleReimportAllMesh(const FReimportParameters ReimportParameters);`
- L165 _private prototype_ `void HandleReimportAllMeshInternal(const FReimportParameters& ReimportParameters);`
- L170 _private prototype_ `void HandlePostReimport(UObject* InObject, bool bSuccess);` — Refreshes the skeleton tree when our edited mesh is re-imported outside of this editor's own re-import button (Content Browser, scripted, drag-drop, etc.). The in-editor button has its own refresh path inside HandleReimportMeshInternal's OnDone callback.
- L172 _private prototype_ `void HandleOnPreviewSceneSettingsCustomized(IDetailLayoutBuilder& DetailBuilder);`
- L175 _private prototype_ `bool IsMeshSectionSelectionChecked() const;` — Callback for checking whether the UV drawing is switched on.
- L177 _private prototype_ `void HandleMeshClick(HActor* HitProxy, const FViewportClick& Click);`
- L180 _private prototype_ `void FillApplyClothingAssetMenu(FMenuBuilder& MenuBuilder, int32 InLodIndex, int32 InSectionIndex);` — Clothing menu handlers (builds and handles clothing context menu options)
- L181 _private prototype_ `void FillCreateClothingMenu(FMenuBuilder& MenuBuilder, int32 InLodIndex, int32 InSectionIndex);`
- L182 _private prototype_ `void FillCreateClothingLodMenu(FMenuBuilder& MenuBuilder, int32 InLodIndex, int32 InSectionIndex);`
- L183 _private prototype_ `void OnRemoveClothingAssetMenuItemClicked(int32 InLodIndex, int32 InSectionIndex);`
- L184 _private prototype_ `void OnCreateClothingAssetMenuItemClicked(FSkeletalMeshClothBuildParams& Params);`
- L185 _private prototype_ `void OnApplyClothingAssetClicked(UClothingAssetBase* InAssetToApply, int32 InMeshLodIndex, int32 InMeshSectionIndex, int32 InClothLodIndex);`
- L187 _private prototype_ `bool CanApplyClothing(int32 InLodIndex, int32 InSectionIndex);`
- L188 _private prototype_ `bool CanRemoveClothing(int32 InLodIndex, int32 InSectionIndex);`
- L189 _private prototype_ `bool CanCreateClothing(int32 InLodIndex, int32 InSectionIndex);`
- L190 _private prototype_ `bool CanCreateClothingLod(int32 InLodIndex, int32 InSectionIndex);`
- L192 _private prototype_ `void ApplyClothing(UClothingAssetBase* InAsset, int32 InLodIndex, int32 InSectionIndex, int32 InClothingLod);`
- L193 _private prototype_ `void RemoveClothing(int32 InLodIndex, int32 InSectionIndex);`
- L197 _private prototype_ `void OnRemoveSectionFromLodAndBelowMenuItemClicked(int32 LodIndex, int32 SectionIndex);` — Generate LOD sections menu handlers
- L200 _private prototype_ `void RegisterReimportContextMenu(const FName InBaseMenuName, bool bWithDialog);`
- L202 _private prototype_ `static TSharedPtr<FSkeletalMeshEditor> GetSkeletalMeshEditor(const FToolMenuContext& InMenuContext);`
- L205 _private prototype_ `void ExtendMenu();`
- L207 _private prototype_ `void BakeMaterials();`
- L208 _private prototype_ `void ExtendToolbar();`
- L210 _private prototype_ `void BindCommands();`
- L214 _public member_ `FSimpleMulticastDelegate OnPostUndo;` — Multicast delegate fired on global undo/redo
- L217 _public member_ `FSimpleMulticastDelegate OnCurvesChanged;` — Multicast delegate fired on curves changing
- L221 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — The skeleton we are editing
- L224 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender
- L227 _private member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender
- L230 _private member_ `TSharedPtr<class IPersonaToolkit> PersonaToolkit;` — Persona toolkit
- L233 _private member_ `TSharedPtr<class ISkeletonTree> SkeletonTree;` — Skeleton tree
- L236 _private member_ `TSharedPtr<class IMorphTargetViewer> MorphTargetViewer;` — Morph target viewer
- L239 _private member_ `TSharedPtr<class IPersonaViewport> Viewport;` — Viewport
- L242 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Details panel
- L245 _private member_ `TSharedPtr<IToolkit> HostedToolkit;` — The toolkit we're currently hosting.
- L248 _private member_ `TSharedPtr<FWorkspaceItem> SkeletalMeshEditorMenuCategory;` — This is set in ModeUILayer to be the menu category where new tabs are registered to be enabled by the user
- L250 _private member_ `TSharedPtr<FSkeletalMeshEditorModeUILayer> ModeUILayer;`
- L253 _private member_ `TSharedPtr<SSkeletalMeshEditorToolbox> ToolboxWidget;` — The toolbox widget
- L256 _private member_ `TSharedPtr<FSkeletalMeshEditorBinding> Binding;` — Binding to send/receive skeletal mesh modifications
- L258 _private member_ `FSimpleMulticastDelegate OnPreSaveAssetDelegate;`
- L259 _private member_ `FSimpleMulticastDelegate OnPreSaveAssetAsDelegate;`

#### struct `FSkeletalMeshEditor::FReimportParameters`  
`struct FReimportParameters`  
_L148-159_
- L150 _public function_ `FReimportParameters(int32 InSourceFileIndex, bool bInWithNewFile, bool bInReimportWithDialog) : SourceFileIndex(InSourceFileIndex) , bWithNewFile(bInWithNewFile) , bReimportWithDialog(bInReimportWithDialog)`
- L156 _public member_ `int32 SourceFileIndex = INDEX_NONE;`
- L157 _public member_ `bool bWithNewFile = false;`
- L158 _public member_ `bool bReimportWithDialog = false;`

#### class `FSkeletalMeshEditorNotifier`  
`class FSkeletalMeshEditorNotifier: public ISkeletalMeshNotifier`  
_L266-274_
- inherits: `ISkeletalMeshNotifier`
- L269 _public prototype_ `FSkeletalMeshEditorNotifier(TSharedRef<FSkeletalMeshEditor> InEditor);`
- L270 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;`
- L273 _private member_ `TWeakPtr<FSkeletalMeshEditor> Editor;`

#### class `FSkeletalMeshEditorBinding`  
`class FSkeletalMeshEditorBinding: public ISkeletalMeshEditorBinding`  
_L280-292_
- inherits: `ISkeletalMeshEditorBinding`
- L283 _public prototype_ `FSkeletalMeshEditorBinding(TSharedRef<FSkeletalMeshEditor> InEditor);`
- L285 _public prototype_ `virtual TSharedPtr<ISkeletalMeshNotifier> GetNotifier() override;`
- L286 _public prototype_ `virtual NameFunction GetNameFunction() override;`
- L287 _public prototype_ `virtual TArray<FName> GetSelectedBones() const override;`
- L290 _private member_ `TWeakPtr<FSkeletalMeshEditor> Editor;`
- L291 _private member_ `TSharedPtr<FSkeletalMeshEditorNotifier> Notifier;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace SkeletalMeshEditorModes`
- L36 _externvar_ `extern const FName SkeletalMeshEditorMode;` (scope `SkeletalMeshEditorModes`) — Mode identifiers
- L39 _namespace_ `namespace SkeletalMeshEditorTabs`
- L42 _externvar_ `extern const FName DetailsTab;` (scope `SkeletalMeshEditorTabs`) — Tab identifiers
- L43 _externvar_ `extern const FName SkeletonTreeTab;` (scope `SkeletalMeshEditorTabs`)
- L44 _externvar_ `extern const FName ViewportTab;` (scope `SkeletalMeshEditorTabs`)
- L45 _externvar_ `extern const FName AdvancedPreviewTab;` (scope `SkeletalMeshEditorTabs`)
- L46 _externvar_ `extern const FName AssetDetailsTab;` (scope `SkeletalMeshEditorTabs`)
- L47 _externvar_ `extern const FName MorphTargetsTab;` (scope `SkeletalMeshEditorTabs`)
- L48 _externvar_ `extern const FName MeshDetailsTab;` (scope `SkeletalMeshEditorTabs`)
- L49 _externvar_ `extern const FName AnimationMappingTab;` (scope `SkeletalMeshEditorTabs`)
- L50 _externvar_ `extern const FName CurveMetadataTab;` (scope `SkeletalMeshEditorTabs`)
- L51 _externvar_ `extern const FName FindReplaceTab;` (scope `SkeletalMeshEditorTabs`)

### `Source/Editor/SkeletalMeshEditor/Private/SkeletalMeshEditorCommands.h` (Private)


#### class `FSkeletalMeshEditorCommands`  
`class FSkeletalMeshEditorCommands : public TCommands<FSkeletalMeshEditorCommands>`  
_L15-41_
- inherits: `TCommands<FSkeletalMeshEditorCommands>`
- L18 _public function_ `FSkeletalMeshEditorCommands() : TCommands<FSkeletalMeshEditorCommands>(TEXT("SkeletalMeshEditor"), NSLOCTEXT("Contexts", "SkeletalMeshEditor", "Skeletal Mesh Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ReimportMesh;` — reimport
- L28 _public member_ `TSharedPtr<FUICommandInfo> ReimportMeshWithNewFile;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ReimportAllMesh;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ReimportAllMeshWithNewFile;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ReimportWithDialog;` — reimport with dialog
- L36 _public member_ `TSharedPtr<FUICommandInfo> BakeMaterials;` — bake materials for this skeletal mesh
- L39 _public member_ `TSharedPtr< FUICommandInfo > ResetBoneTransforms;` — Reset bones transforms
- L40 _public member_ `TSharedPtr< FUICommandInfo > ResetAllBonesTransforms;`

### `Source/Editor/SkeletalMeshEditor/Private/SkeletalMeshEditorMode.h` (Private)


#### class `FSkeletalMeshEditorMode`  
`class FSkeletalMeshEditorMode : public FApplicationMode`  
_L17-32_
- inherits: `FApplicationMode`
- L20 _public prototype_ `FSkeletalMeshEditorMode( TSharedRef<FWorkflowCentricApplication> InHostingApp, TSharedRef<class ISkeletonTree> InSkeletonTree, TSharedRef<class IMorphTargetViewer> InMorphTargetViewer );`
- L27 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L31 _protected prototype_ `TSharedRef<class FWorkflowTabFactory> CreateMeshControllerMappingTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TWeakObjectPtr<class USkeletalMesh>& InEditingMesh, FSimpleMulticastDelegate& OnPostUndo) const;` — Mesh interface class

#### struct `FMeshPropertiesSummoner`  
`struct FMeshPropertiesSummoner : public FWorkflowTabFactory`  
_L34-50_
- inherits: `FWorkflowTabFactory`
- L36 _public prototype_ `FMeshPropertiesSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, FOnGetAsset InOnGetAsset);`
- L39 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L42 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L49 _private member_ `FOnGetAsset OnGetAsset;`

#### struct `FMeshControllerMappingTabSummoner`  
`struct FMeshControllerMappingTabSummoner : public FWorkflowTabFactory`  
_L55-68_
- inherits: `FWorkflowTabFactory`
- L58 _public prototype_ `FMeshControllerMappingTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TWeakObjectPtr<class USkeletalMesh>& InEditingMesh, FSimpleMulticastDelegate& InOnPostUndo);`
- L60 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L63 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;` — Create a tooltip widget for the tab
- L66 _private member_ `TWeakObjectPtr<class USkeletalMesh> SkeletalMesh;`
- L67 _private member_ `FSimpleMulticastDelegate& OnPostUndo;`

### `Source/Editor/SkeletalMeshEditor/Private/SkeletalMeshEditorModeUILayer.h` (Private)


#### class `USkeletalMeshEditorUISubsystem`  
`class USkeletalMeshEditorUISubsystem : public UAssetEditorUISubsystem`  
_L13-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetEditorUISubsystem`
- desc: Interchange layer to manage built in tab locations within the editor's layout.
- L18 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L19 _public prototype_ `virtual void Deinitialize() override;`
- L20 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`

#### class `FSkeletalMeshEditorModeUILayer`  
`class FSkeletalMeshEditorModeUILayer : public FAssetEditorModeUILayer`  
_L25-38_
- inherits: `FAssetEditorModeUILayer`
- desc: Handles the hosting of additional toolkits, such as the mode toolkit, within the Skeletal Mesh Editor 's toolkit.
- L28 _public function_ `FSkeletalMeshEditorModeUILayer(const IToolkitHost* InToolkitHost) : FAssetEditorModeUILayer(InToolkitHost)`
- L29 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L30 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L32 _public prototype_ `virtual TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`
- L34 _public prototype_ `void SetModeMenuCategory(TSharedPtr<FWorkspaceItem> InMenuCategory);`
- L37 _protected member_ `TSharedPtr<FWorkspaceItem> SkeletalMeshEditorMenuCategory;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SKELETALMESHEDITOR_API`

### `Source/Editor/SkeletalMeshEditor/Public/ISkeletalMeshEditor.h` (Public)


#### class `ISkeletalMeshEditor`  
`class ISkeletalMeshEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit`  
_L11-20_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit`
- L14 _public prototype_ `virtual TSharedPtr<ISkeletalMeshEditorBinding> GetBinding() = 0;`
- L15 _public prototype_ `virtual FSimpleMulticastDelegate& OnPreSaveAsset() = 0;`
- L16 _public prototype_ `virtual FSimpleMulticastDelegate& OnPreSaveAssetAs() = 0;`
- L18 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetResetBoneTransformsCommand() = 0;`
- L19 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetResetAllBonesTransformsCommand() = 0;`

### `Source/Editor/SkeletalMeshEditor/Public/ISkeletalMeshEditorModule.h` (Public)


#### class `ISkeletalMeshEditorModule`  
`class ISkeletalMeshEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L14-31_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L18 _public prototype_ `virtual TSharedRef<ISkeletalMeshEditor> CreateSkeletalMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class USkeletalMesh* InSkeletalMesh) = 0;` — Creates a new skeleton editor instance
- L21 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FSkeletalMeshEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<ISkeletalMeshEditor> );` — Get all toolbar extenders
- L22 _public prototype_ `virtual TArray<FSkeletalMeshEditorToolbarExtender>& GetAllSkeletalMeshEditorToolbarExtenders() = 0;`
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSkeletalMeshEditorInitialized, TWeakPtr<ISkeletalMeshEditor>);` — Add callback after editor has been initialized
- L26 _public prototype_ `virtual TArray<FOnSkeletalMeshEditorInitialized>& GetPostEditorInitDelegates() = 0;`
- L29 _public prototype_ `DECLARE_EVENT_OneParam(FExampleCharacterFXEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);` — Used by the EditorUISubsystem
- L30 _public prototype_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() = 0;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshEditor, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshEditor, Log, All);`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FSkeletalMeshEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<ISkeletalMeshEditor> );` — Get all toolbar extenders
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSkeletalMeshEditorInitialized, TWeakPtr<ISkeletalMeshEditor>);` — Add callback after editor has been initialized
- L29 _delegate_ `DECLARE_EVENT_OneParam(FExampleCharacterFXEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);` — Used by the EditorUISubsystem

### `Source/Editor/SkeletalMeshEditor/Public/SkeletalMeshClothingSystemUtilities.h` (Public)


#### struct `FSkeletalMeshClothingSystemUtilities`  
`struct FSkeletalMeshClothingSystemUtilities`  
_L14-21_
- desc: Editor utilities for managing skeletal mesh clothing assets
- L17 _public prototype_ `static bool AssignClothingToSection(USkeletalMesh* SkeletalMesh, UClothingAssetBase* ClothingAsset, int32 SkeletalMeshLodIndex, int32 SkeletalMeshSection, int32 ClothingLodIndex, FString* ErrorMessage);` — Assign a clothing asset to a skeletal mesh section. Returns success.
- L20 _public prototype_ `static bool RemoveClothingFromSection(USkeletalMesh* SkeletalMesh, int32 SkeletalMeshLodIndex, int32 SkeletalMeshSection, FString* ErrorMessage);` — Remove the clothing from a skeletal mesh section. Returns success.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SKELETALMESHEDITOR_API`

### `Source/Editor/SkeletalMeshEditor/Public/SkeletalMeshEditorContextMenuContext.h` (Public)


#### class `USkeletalMeshEditorContextMenuContext`  
`class USkeletalMeshEditorContextMenuContext : public UObject`  
_L10-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L16 _public member_ `int32 LodIndex = INDEX_NONE;` — The LOD index that was clicked
- L19 _public member_ `int32 SectionIndex = INDEX_NONE;` — The section index that was clicked

### `Source/Editor/SkeletalMeshEditor/Public/SkeletalMeshEditorSubsystem.h` (Public)


#### enum `ESkelSubSysQueryCurvesMetatdataNamesFilter`  
`enum class ESkelSubSysQueryCurvesMetatdataNamesFilter : uint8`  
_L24-32_
- reflection: `UENUM(BlueprintType)`
- desc: Blueprint enum to query skeleton curves
- L27 _public enumerator_ `All` — Query all metadata curves
- L29 _public enumerator_ `MorphTargetOnly` — Query only morph target metadata curves
- L31 _public enumerator_ `MaterialOnly` — Query only material metadata curves

#### class `USkeletalMeshEditorSubsystem`  
`class USkeletalMeshEditorSubsystem : public UEditorSubsystem`  
_L39-391_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: USkeletalMeshEditorSubsystem Subsystem for exposing skeletal mesh functionality to scripts
- L44 _public prototype_ `USkeletalMeshEditorSubsystem();`
- L57 _public prototype_ `static bool RegenerateLOD(USkeletalMesh* SkeletalMesh, int32 NewLODCount = 0, bool bRegenerateEvenIfImported = false, bool bGenerateBaseLOD = false);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities", meta = (ScriptMethod))` — Regenerate LODs of the mesh @param SkeletalMesh	The mesh that will regenerate LOD @param NewLODCount	Set valid value (>0) if you want to change LOD count. Otherwise, it will use the current LOD and regenerate @param bRegenerateEvenIfImported	If this is true, it only regenerate even if this LOD was imported before If false, it will regenerate for only previously auto generated ones @param bGenerateBaseLOD If this is true and there is some reduction data, the base LOD will be reduce according to the settings @return	true if succeed. If mesh reduction is not available this will return false.
- L66 _public prototype_ `int32 GetNumVerts(USkeletalMesh* SkeletalMesh, int32 LODIndex);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get number of mesh vertices for an LOD of a Skeletal Mesh @param SkeletalMesh		Mesh to get number of vertices from. @param LODIndex			Index of the mesh LOD. @return Number of vertices. Returns 0 if invalid mesh or LOD index.
- L75 _public prototype_ `int32 GetNumSections(USkeletalMesh* SkeletalMesh, int32 LODIndex);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get number of sections for a LOD of a Skeletal Mesh @param SkeletalMesh		Mesh to get number of vertices from. @param LODIndex			Index of the mesh LOD. @return Number of sections. Returns INDEX_NONE if invalid mesh or LOD index.
- L86 _public prototype_ `bool GetSectionRecomputeTangent(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, bool& bOutRecomputeTangent);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get bRecomputeTangent from a section of a LOD of a Skeletal Mesh @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param bOutRecomputeTangent	The function will set the bRecomputeTangent used by the section @return false if invalid mesh or LOD index or section index.
- L97 _public prototype_ `bool SetSectionRecomputeTangent(USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, const bool bRecomputeTangent);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Set bRecomputeTangent for a section of a LOD of a Skeletal Mesh. @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param bRecomputeTangent	The function will set the bRecomputeTangent used by the section @return false if invalid mesh or LOD index or section index.
- L108 _public prototype_ `bool GetSectionRecomputeTangentsVertexMaskChannel(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, uint8& OutRecomputeTangentsVertexMaskChannel);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get RecomputeTangentsVertexMaskChannel from a section of a LOD of a Skeletal Mesh @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param OutRecomputeTangentsVertexMaskChannel	The function will set the RecomputeTangentsVertexMaskChannel used by the section @return false if invalid mesh or LOD index or section index.
- L119 _public prototype_ `bool SetSectionRecomputeTangentsVertexMaskChannel(USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, const uint8 RecomputeTangentsVertexMaskChannel);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Set RecomputeTangentsVertexMaskChannel for a section of a LOD of a Skeletal Mesh. @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param RecomputeTangentsVertexMaskChannel	The function will set the RecomputeTangentsVertexMaskChannel used by the section @return false if invalid mesh or LOD index or section index.
- L130 _public prototype_ `bool GetSectionCastShadow(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, bool& bOutCastShadow);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get bCastShadow from a section of a LOD of a Skeletal Mesh @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param bOutCastShadow	The function will set the bCastShadow used by the section @return false if invalid mesh or LOD index or section index.
- L141 _public prototype_ `bool SetSectionCastShadow(USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, const bool bCastShadow);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Set bCastShadow for a section of a LOD of a Skeletal Mesh. @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param bCastShadow	The function will set the bCastShadow used by the section @return false if invalid mesh or LOD index or section index.
- L152 _public prototype_ `bool GetSectionVisibleInRayTracing(const USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, bool& bOutVisibleInRayTracing);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get bVisibleInRayTracing from a section of a LOD of a Skeletal Mesh @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param bOutVisibleInRayTracing	The function will set the bVisibleInRayTracing used by the section @return false if invalid mesh or LOD index or section index.
- L163 _public prototype_ `bool SetSectionVisibleInRayTracing(USkeletalMesh* SkeletalMesh, const int32 LODIndex, const int32 SectionIndex, const bool bVisibleInRayTracing);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Set bVisibleInRayTracing for a section of a LOD of a Skeletal Mesh. @param SkeletalMesh			Mesh to get number of vertices from. @param LodIndex				Index of the mesh LOD. @param SectionIndex			Index of the LOD section. @param bVisibleInRayTracing	The function will set the bVisibleInRayTracing used by the section @return false if invalid mesh or LOD index or section index.
- L172 _public prototype_ `UMaterialInterface* GetMaterialSlotOverlayMaterial(const USkeletalMesh* SkeletalMesh, const int32 SlotIndex);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get the overlay material for a material slot in a Skeletal Mesh. @param SkeletalMesh			Mesh to get material overlay from. @param SlotIndex				Index of the skeletal mesh material slot. @return the material interface or null if there is no overlay material.
- L182 _public prototype_ `bool SetMaterialSlotOverlayMaterial(USkeletalMesh* SkeletalMesh, const int32 SlotIndex, UMaterialInterface* NewSectionOverlayMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Set the overlay material for a material slot in a Skeletal Mesh. @param SkeletalMesh			Mesh to set material overlay to. @param SlotIndex				Index of the skeletal mesh material slot. @param NewSectionOverlayMaterial	The function will set the OverlayMaterial used by the slot @return false if invalid mesh or material slot index is invalid.
- L190 _public prototype_ `UMaterialInterface* GetSkeletalMeshOverlayMaterial(const USkeletalMesh* SkeletalMesh);` — `UFUNCTION(BlueprintPure, Category = "Skeletal Mesh Utilities")` — Get the overlay material for a Skeletal Mesh. @param SkeletalMesh			Mesh to get the material overlay from. @return the material interface or null if there is no material.
- L199 _public prototype_ `bool SetSkeletalMeshOverlayMaterial(USkeletalMesh* SkeletalMesh, UMaterialInterface* NewOverlayMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Set the overlay material for a Skeletal Mesh. @param SkeletalMesh					Mesh to set material overlay to. @param NewOverlayMaterial		the OverlayMaterial we set for the skeletal mesh @return false if invalid mesh.
- L209 _public prototype_ `int32 GetLODMaterialSlot(USkeletalMesh* SkeletalMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities")` — Gets the material slot used for a specific LOD section. @param	SkeletalMesh		SkeletalMesh to get the material index from. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section. @return  MaterialSlotIndex	Index of the material slot used by the section or INDEX_NONE in case of error.
- L218 _public prototype_ `static bool RenameSocket(USkeletalMesh* SkeletalMesh, FName OldName, FName NewName);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities", meta = (ScriptMethod))` — Rename a socket within a skeleton @param SkeletalMesh	The mesh inside which we are renaming a socket @param OldName       The old name of the socket @param NewName		The new name of the socket @return true if the renaming succeeded.
- L226 _public prototype_ `static bool RemoveSocket(USkeletalMesh* SkeletalMesh, FName SocketName);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities", meta = (ScriptMethod))` — Remove a socket from a skeletal mesh @param SkeletalMesh	The mesh from which we are removing a socket @param SocketName    The name of the socket to remove @return true if the removal succeeded.
- L234 _public prototype_ `static FName GetBoneParent(const USkeletalMesh* SkeletalMesh, FName BoneName);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities", meta = (ScriptMethod))` — Get the parent bone name of a bone in a skeletal mesh. @param SkeletalMesh  The mesh to query. @param BoneName      The name of the bone to query. @return The name of the parent bone, or NAME_None if the bone is the root or does not exist.
- L242 _public prototype_ `static TArray<FName> GetBoneChildren(const USkeletalMesh* SkeletalMesh, FName BoneName);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh Utilities", meta = (ScriptMethod))` — Get the direct children of a bone in a skeletal mesh. @param SkeletalMesh  The mesh to query. @param BoneName      The name of the bone to query. @return An array of bone names that are direct children of the given bone.
- L252 _public prototype_ `static int32 GetLODCount(USkeletalMesh* SkeletalMesh);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Retrieve the number of LOD contain in the specified skeletal mesh. @param SkeletalMesh: The static mesh we import or re-import a LOD. @return The LOD number.
- L264 _public prototype_ `static int32 ImportLOD(USkeletalMesh* BaseMesh, const int32 LODIndex, const FString& SourceFilename);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Import or re-import a LOD into the specified base mesh. If the LOD do not exist it will import it and add it to the base static mesh. If the LOD already exist it will re-import the specified LOD. @param BaseSkeletalMesh: The static mesh we import or re-import a LOD. @param LODIndex: The index of the LOD to import or re-import. Valid value should be between 0 and the base skeletal mesh LOD number. Invalid value will return INDEX_NONE @param SourceFilename: The fbx source filename. If we are re-importing an existing LOD, it can be empty in this case it will use the last import file. Otherwise it must be an existing fbx file. @return The index of the LOD that was imported or re-imported. Will return INDEX_NONE if anything goes bad.
- L275 _public prototype_ `static bool RemoveLODs(USkeletalMesh* BaseMesh, const TArray<int32> ToRemoveLODs);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh", meta=(ScriptName="RemoveLods;RemoveLODs"))` — Remove all the specified LODs. This function will remove all the valid LODs in the list. Valid LOD is any LOD greater then 0 that exist in the skeletalmesh. We cannot remove the base LOD 0. @param SkeletalMesh	The mesh inside which we are renaming a socket @param ToRemoveLODs	The LODs we need to remove @return true if the successfully remove all the LODs. False otherwise, but evedn if it return false it will have removed all valid LODs.
- L287 _public prototype_ `static bool StripLODGeometry(USkeletalMesh* SkeletalMesh, const int32 LODIndex, UTexture2D* TextureMask, const float Threshold);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — This function will strip all triangle in the specified LOD that don't have any UV area pointing on a black pixel in the TextureMask. We use the UVChannel 0 to find the pixels in the texture. @Param SkeletalMesh: The skeletalmesh we want to optimize @Param LODIndex: The LOD we want to optimize @Param TextureMask: The texture containing the stripping mask. non black pixel strip triangle, black pixel keep them. @Param Threshold: The threshold we want when comparing the texture value with zero.
- L297 _public prototype_ `static bool ReimportAllCustomLODs(USkeletalMesh* SkeletalMesh);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh", meta=(ScriptName="ReimportAllCustomLods;ReimportAllCustomLODs"))` — Re-import the specified skeletal mesh and all the custom LODs. @param SkeletalMesh: is the skeletal mesh we import or re-import a LOD. @return true if re-import works, false otherwise see log for explanation.
- L306 _public prototype_ `static void GetLodBuildSettings(const USkeletalMesh* SkeletalMesh, const int32 LodIndex, FSkeletalMeshBuildSettings& OutBuildOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Copy the build options with the specified LOD build settings. @param SkeletalMesh - Mesh to process. @param LodIndex - The LOD we get the reduction settings. @param OutBuildOptions - The build settings where we copy the build options.
- L315 _public prototype_ `static void SetLodBuildSettings(USkeletalMesh* SkeletalMesh, const int32 LodIndex, const FSkeletalMeshBuildSettings& BuildOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Set the LOD build options for the specified LOD index. @param SkeletalMesh - Mesh to process. @param LodIndex - The LOD we will apply the build settings. @param BuildOptions - The build settings we want to apply to the LOD.
- L325 _public prototype_ `static UPhysicsAsset* CreatePhysicsAsset(USkeletalMesh* SkeletalMesh, bool bSetToMesh = true, int32 LodIndex = 0);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — This function creates a PhysicsAsset for the given SkeletalMesh with the same settings as if it were created through FBX import @Param SkeletalMesh: The SkeletalMesh we want to create the PhysicsAsset for @Param bSetToMesh: If true the created physics asset will be used by the skeletal mesh. @Param LodIndex: Use the specified LOD to create the physics asset.
- L336 _public prototype_ `static bool IsPhysicsAssetCompatible(USkeletalMesh* TargetMesh, UPhysicsAsset* PhysicsAsset);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Checks whether a physics asset is compatible with the given SkeletalMesh @param TargetMesh The mesh to test for compatibility @param PhysicsAsset The PhysicsAsset to test for compatibility @return Whether the physics asset is compatible with the target SkeletalMesh
- L349 _public prototype_ `static bool AssignPhysicsAsset(USkeletalMesh* TargetMesh, UPhysicsAsset* PhysicsAsset);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Assigns a PhysicsAsset to the given SkeletalMesh if it is compatible. Passing nullptr / None as the physics asset will always succeed and will clear the physics asset assignment for the target SkeletalMesh @param TargetMesh The mesh to attempt to assign the PhysicsAsset to @param PhysicsAsset The physics asset to assign to the provided mesh (or nullptr/None) @return Whether the physics asset was successfully assigned to the mesh
- L359 _public prototype_ `static bool SetMorphTargetsToGeneratedByEngine(USkeletalMesh* TargetMesh, const TArray<FString>& OptionalNames);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Set morph targets has generated by engine. @param TargetMesh The mesh to convert morph targets to generated by engine. @param OptionalNames The names of morph targets to convert. If the array is empty all morph will be converted. @return Return true if the target mesh was modified, false otherwise.
- L368 _public prototype_ `static void SetMorphTargetsToGeneratedByEngineForAllSkeletalMesh(const TArray<FString>& OptionalNames, const TArray<FName>& OptionalPaths);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Set morph targets has generated by engine for all skeletalmesh in the content. @param OptionalNames The names of morph targets to convert. If the array is empty all morph will be converted. @param OptionalPaths The paths list use to filter the research of the skeletal meshes. If the array is empty we will find all skeletal meshes.
- L377 _public prototype_ `static void GetMorphTargetsGeneratedByEngine(USkeletalMesh* TargetMesh, TArray<FName>& OutNames);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Get morph targets marked as generated by engine. @param TargetMesh The mesh to get morph targets. @param OutNames - Receive the names of morph targets marked as generated by engine
- L381 _public prototype_ `static void SetAllowCPUAccess(USkeletalMesh* TargetMesh, bool bAllowCPUAccess);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | SkeletalMesh")` — Sets Skeletal Mesh Flag bAllowCPUAccess on all LOD levels.
- L390 _public prototype_ `static void GetSkeletonCurveMetaDataNames(const USkeleton* TargetSkeleton, TArray<FName>& OutNames, ESkelSubSysQueryCurvesMetatdataNamesFilter Filter);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Skeleton")` — Retrieve all curve metadata name from the skeleton. @param TargetSkeleton The skeleton we query the data from. @param OutNames - Receive all the name of the curves that has metadata in the skeleton.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SKELETALMESHEDITOR_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshEditorSubsystem, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshEditorSubsystem, Log, All);`
